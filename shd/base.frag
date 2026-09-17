#version 460 core

in vec2 vUV;
out vec4 FragColor;

uniform vec2  uResolution;
uniform float uTime;
uniform vec3  uCamPos;

// ---------------------------------------------------------------------
// Signed distance functions
// ---------------------------------------------------------------------
float sdSphere(vec3 p, float r) {
    return length(p) - r;
}

float sdBox(vec3 p, vec3 b) {
    vec3 q = abs(p) - b;
    return length(max(q, 0.0)) + min(max(q.x, max(q.y, q.z)), 0.0);
}

float sdPlane(vec3 p, float y) {
    return p.y - y;
}

// Smooth minimum, for blending shapes together
float smin(float a, float b, float k) {
    float h = clamp(0.5 + 0.5 * (b - a) / k, 0.0, 1.0);
    return mix(b, a, h) - k * h * (1.0 - h);
}

// ---------------------------------------------------------------------
// Scene: returns distance and a material id packed in .w-ish way
// (kept simple: separate distance + id via out params)
// ---------------------------------------------------------------------
float map(vec3 p, out int matId) {
    // animated sphere bobbing in place
    vec3 spherePos = p - vec3(0.0, 1.0 + 0.3 * sin(uTime * 1.5), 0.0);
    float sphere = sdSphere(spherePos, 1.0);

    // orbiting smaller box, blended into the sphere
    vec3 boxPos = p - vec3(2.2 * cos(uTime), 1.0, 2.2 * sin(uTime));
    float box = sdBox(boxPos, vec3(0.5));

    float blended = smin(sphere, box, 0.6);

    float plane = sdPlane(p, 0.0);

    float d = min(blended, plane);
    matId = (d == plane) ? 0 : 1; // 0 = ground, 1 = blob

    return d;
}

// Overload without material id, for shadow/normal marching
float mapDist(vec3 p) {
    int dummy;
    return map(p, dummy);
}

// ---------------------------------------------------------------------
// Normals via central differences of the SDF
// ---------------------------------------------------------------------
vec3 calcNormal(vec3 p) {
    const vec2 e = vec2(1e-3, 0.0);
    return normalize(vec3(
        mapDist(p + e.xyy) - mapDist(p - e.xyy),
        mapDist(p + e.yxy) - mapDist(p - e.yxy),
        mapDist(p + e.yyx) - mapDist(p - e.yyx)
    ));
}

// ---------------------------------------------------------------------
// Raymarching core loop
// ---------------------------------------------------------------------
#define MAX_STEPS 128
#define MAX_DIST  100.0
#define SURF_DIST 1e-3

float rayMarch(vec3 ro, vec3 rd, out int matId) {
    float t = 0.0;
    matId = -1;
    for (int i = 0; i < MAX_STEPS; i++) {
        vec3 p = ro + rd * t;
        float d = map(p, matId);
        if (d < SURF_DIST || t > MAX_DIST) break;
        t += d;
    }
    return t;
}

// Soft shadow: marches from the surface toward the light,
// tracking the minimum ratio of distance to travelled distance.
float softShadow(vec3 ro, vec3 rd, float mint, float maxt, float k) {
    float res = 1.0;
    float t = mint;
    for (int i = 0; i < 64 && t < maxt; i++) {
        float h = mapDist(ro + rd * t);
        if (h < 0.001) return 0.0;
        res = min(res, k * h / t);
        t += h;
    }
    return clamp(res, 0.0, 1.0);
}

// ---------------------------------------------------------------------
// Shading
// ---------------------------------------------------------------------
vec3 shade(vec3 p, vec3 n, vec3 rd, int matId) {
    vec3 lightPos = vec3(4.0, 6.0, -2.0);
    vec3 l = normalize(lightPos - p);

    float diff = max(dot(n, l), 0.0);
    float shadow = softShadow(p + n * 0.01, l, 0.02, 20.0, 16.0);

    vec3 baseColor = (matId == 0) ? vec3(0.35, 0.35, 0.4)   // ground
                                   : vec3(0.9, 0.35, 0.2);   // blob

    // simple checker pattern on the ground for scale/motion cues
    if (matId == 0) {
        vec2 c = floor(p.xz);
        float checker = mod(c.x + c.y, 2.0);
        baseColor *= mix(0.7, 1.0, checker);
    }

    vec3 ambient = 0.08 * baseColor;
    vec3 diffuse = baseColor * diff * shadow;

    // cheap specular
    vec3 viewDir = -rd;
    vec3 halfVec = normalize(l + viewDir);
    float spec = pow(max(dot(n, halfVec), 0.0), 32.0) * shadow;

    return ambient + diffuse + vec3(spec);
}

void main() {
    vec2 uv = (vUV - 0.5) * 2.0;
    uv.x *= uResolution.x / uResolution.y;

    // Camera: look at the origin from uCamPos
    vec3 ro = uCamPos;
    vec3 target = vec3(0.0, 1.0, 0.0);

    vec3 forward = normalize(target - ro);
    vec3 right   = normalize(cross(vec3(0.0, 1.0, 0.0), forward));
    vec3 up      = cross(forward, right);

    float fov = 1.5;
    vec3 rd = normalize(uv.x * right + uv.y * up + fov * forward);

    int matId;
    float t = rayMarch(ro, rd, matId);

    vec3 col;
    if (matId >= 0 && t < MAX_DIST) {
        vec3 p = ro + rd * t;
        vec3 n = calcNormal(p);
        col = shade(p, n, rd, matId);
        // simple distance fog
        col = mix(col, vec3(0.05, 0.06, 0.08), 1.0 - exp(-0.0015 * t * t));
    } else {
        // background gradient
        col = mix(vec3(0.05, 0.06, 0.09), vec3(0.15, 0.17, 0.22), uv.y * 0.5 + 0.5);
    }

    // gamma correction
    col = pow(col, vec3(1.0 / 2.2));
    FragColor = vec4(col, 1.0);
}

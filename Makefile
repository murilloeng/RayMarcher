#compiler
CXX = g++
INCS = -I ..
WARS = -Wall -Werror
LIBS = -l GL -l glfw
CXXFLAGS = -std=c++20 -fPIC -pipe -fopenmp -MT $@ -MMD -MP -MF $(subst .o,.d, $@) $(DEFS) $(INCS) $(WARS)

#mode
ifneq ($(m), r)
	mode = debug
	CXXFLAGS += -ggdb3
else
	mode = release
	CXXFLAGS += -Ofast
endif

#profiling
ifeq ($(p), 1)
	LNKFLAGS += -pg
	CXXFLAGS += -pg
	prof_dir = profiling/
endif

#output
out = dist/$(prof_dir)$(mode)/ray_marcher.out

#sources
src := $(sort $(shell find -path './src/*.cpp'))

#objects
obj = $(sort $(subst ./src/, build/$(prof_dir)$(mode)/, $(addsuffix .o, $(basename $(src)))))

#dependencies
dep = $(subst .o,.d, $(obj))

#rules
all : exe

run : exe
	./$(out)

debug : exe
	gdb ./$(out)

exe : $(out)
	@echo 'executable build - $(mode): complete!'

$(out) : $(obj)
	@mkdir -p $(dir $@)
	@$(CXX) $(LNKFLAGS) -o $(out) $(obj) $(LIBS)
	@echo 'executable - $(mode): $@'

build/$(prof_dir)$(mode)/%.o : src/%.cpp build/$(prof_dir)$(mode)/%.d
	@echo 'compiling - $(mode): $<'
	@mkdir -p $(dir $@) && rm -rf $@
	@$(CXX) $(CXXFLAGS) -c $< -o $@

$(dep) : ;

-include $(dep)

clean :
	@rm -rf dist/$(mode)
	@rm -rf build/$(mode)
	@echo 'clean - $(mode): complete!'

print-% :
	@echo $* = $($*)

.PHONY : all clean print-%
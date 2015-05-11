OUTFILE := planet-gen

FILES_C = $(shell find src -type f -name '*.cpp')
FILES_H = $(shell find src -type f -name '*.hpp')
FILES_O = $(foreach file, $(FILES_C), $(patsubst src/%, obj/%, $(patsubst %.cpp, %.o, $(file))))

COMPILE_FLAGS := -Wall -lGL -lglut

.PHONY: all clean run

all:	$(OUTFILE)

# %.o:	src/%.cpp src/%.hpp

# The compilation stage. This outputs object files.
#$(FILES_O):	$(FILES_CPP) obj/.dirstamp
#	g++ -c $(FILES_CPP) $(COMPILE_FLAGS)

obj/%.o:	src/%.cpp src/%.hpp obj/.dirstamp
	-mkdir -p $(dir $@)
	g++ -c $< -o $@ $(COMPILE_FLAGS)

# Here we link our object files to the libraries in LINK_FLAGS and create a binary
$(OUTFILE):	$(FILES_O) obj/.dirstamp
	g++ $(FILES_O) -o $(OUTFILE) $(LINK_FLAGS)

# For updating the temporary obj directory, which holds object files.
# See http://stackoverflow.com/questions/3477418/suppress-make-rule-error-output.
obj/.dirstamp:
	mkdir -p obj
	touch $@

run:	$(OUTFILE)
	./$(OUTFILE)

clean:
	-$(RM) $(OUTFILE)
	-$(RM) -rf obj

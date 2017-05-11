CXX := g++
CXXFLAGS := -c -g -std=c++11 -Wall -Wextra
LD := g++
LDFLAGS := -lsfml-system -lsfml-window -lsfml-graphics -lsfml-audio

EXE := raycast
OBJ := obj/main.o

all: $(EXE)

clean:
	rm -f $(OBJ) $(EXE)

$(EXE): obj/ $(OBJ)
	@echo "Linking executable"
	$(LD) $(LDFLAGS) $(OBJ) -o $@

obj/:
	@echo "Creating $@"
	mkdir $@

obj/%.o: src/%.cc src/%.h
	@echo "CXX $<"
	@$(CXX) $(CXXFLAGS) $< -o $@

obj/%.o: src/%.cc
	@echo "CXX $<"
	@$(CXX) $(CXXFLAGS) $< -o $@

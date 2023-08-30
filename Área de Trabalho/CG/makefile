CXX = g++
CXXFLAGS = -Wall
LDFLAGS = -lSDL2

SRC_DIR = src
TARGET_DIR = build
SRC_FILES = $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES = $(patsubst $(SRC_DIR)/%.cpp, obj/%.o, $(SRC_FILES))

# Use "make TARGET=myprogram MAIN_SRC=main.cpp" to specify these variables
TARGET ?= tarefa1
MAIN_SRC ?= tarefa1.cpp

MAIN_OBJ = obj/$(TARGET).o

$(TARGET_DIR)/$(TARGET): $(OBJ_FILES) $(MAIN_OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

obj/%.o: $(SRC_DIR)/%.cpp | obj
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(MAIN_OBJ): $(MAIN_SRC) | obj
	$(CXX) $(CXXFLAGS) -c -o $@ $<

obj:
	mkdir -p obj

clean:
	rm -rf obj
	rm build/*

.PHONY: clean
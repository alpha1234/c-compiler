CFLAGS=-std=c++14 -g
CXX_FLAGS = $(CFLAGS)
CC=g++
BIN=main

BUILD_DIR = ./build

CPP = compiler.cpp common.cpp preprocessor.cpp lex.cpp $(file)

OBJ = $(CPP:%.cpp=$(BUILD_DIR)/%.o)
DEP = $(OBJ:%.o=%.d)

$(BIN) : $(OBJ)
	mkdir -p $(@D)
	$(CXX) $(CXX_FLAGS) $^ -o $@

-include $(DEP)

$(BUILD_DIR)/%.o : %.cpp
	mkdir -p $(@D)
	$(CXX) $(CXX_FLAGS) -MMD -c $< -o $@

.PHONY : clean
clean :
	-rm $(BIN) $(OBJ) $(DEP)


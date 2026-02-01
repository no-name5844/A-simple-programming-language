# Makefile for simple programming language interpreter

# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -Wall -g

# Target executable
TARGET = main.exe

# Library target
LIBRARY = libInterpreter.lib

# Source files
MAIN_SRC = main.cpp
INTERPRETER_SRC = Interpreter.cpp

# Header files
HDRS = main.hpp Interpreter.hpp

# Object files
MAIN_OBJ = $(MAIN_SRC:.cpp=.o)
INTERPRETER_OBJ = $(INTERPRETER_SRC:.cpp=.o)

# Default target
all: $(TARGET)

# Link target executable
$(TARGET): $(MAIN_OBJ) $(INTERPRETER_OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $(MAIN_OBJ) $(INTERPRETER_OBJ)

# Compile library
library: $(LIBRARY)

$(LIBRARY): $(INTERPRETER_OBJ)
	ar rcs $@ $^

# Phony targets
.PHONY: all clean library

# Compile source files to object files
%.o: %.cpp $(HDRS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean target
clean:
	del /f $(MAIN_OBJ) $(INTERPRETER_OBJ) $(TARGET) $(LIBRARY)

# Phony targets
.PHONY: all clean
# Makefile for CPSC 3620 Brute Force Closest Point Project

# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -std=c++17 -Wall -Wextra -O2

# Directories
SRC_DIR = src
INCLUDE_DIR = include
TEXTFILES_DIR = textfiles
BIN_DIR = bin

# Source and header files
MAIN_SRC = $(SRC_DIR)/controller.cpp
BRUTEFORCE_SRC = $(SRC_DIR)/bruteforce.cc
BRUTEFORCE_HDR = $(INCLUDE_DIR)/bruteforce.h
SHARED_SRC = $(SRC_DIR)/shared.cc
SHARED_HDR = $(INCLUDE_DIR)/shared.h
DIVIDEANDCONQUER_SRC = $(SRC_DIR)/divideconquer.cc
DIVIDEANDCONQUER_HDR = $(INCLUDE_DIR)/divideconquer.h
CREATE_SRC = $(SRC_DIR)/create.cc
CREATE_HDR = $(INCLUDE_DIR)/create.h

# Executable names
MAIN_EXEC = $(BIN_DIR)/ClosestPoint
CREATE_EXEC = $(BIN_DIR)/CreateTextFiles

# All text files to be generated/used
TEXTFILES = $(TEXTFILES_DIR)/output100.txt \
            $(TEXTFILES_DIR)/output200.txt \
            $(TEXTFILES_DIR)/output300.txt \
            $(TEXTFILES_DIR)/output400.txt \
            $(TEXTFILES_DIR)/output500.txt \
            $(TEXTFILES_DIR)/output600.txt \
            $(TEXTFILES_DIR)/output700.txt \
            $(TEXTFILES_DIR)/output800.txt \
            $(TEXTFILES_DIR)/output900.txt \
            $(TEXTFILES_DIR)/output1000.txt \
            $(TEXTFILES_DIR)/output1500.txt \
            $(TEXTFILES_DIR)/output2000.txt \
            $(TEXTFILES_DIR)/output2500.txt \
            $(TEXTFILES_DIR)/output3000.txt \
            $(TEXTFILES_DIR)/output4000.txt \
            $(TEXTFILES_DIR)/output5000.txt \
            $(TEXTFILES_DIR)/output6000.txt \
            $(TEXTFILES_DIR)/output7000.txt \
            $(TEXTFILES_DIR)/output8000.txt \
            $(TEXTFILES_DIR)/output9000.txt \
            $(TEXTFILES_DIR)/output100000.txt

# Ensure required directories exist
$(shell mkdir -p $(BIN_DIR) $(TEXTFILES_DIR))

# Default target
all: $(MAIN_EXEC) $(CREATE_EXEC) generate_textfiles

# Compile the main executable
$(MAIN_EXEC): $(MAIN_SRC) $(BRUTEFORCE_SRC) $(DIVIDEANDCONQUER_SRC) $(BRUTEFORCE_HDR) $(DIVIDEANDCONQUER_HDR) $(SHARED_SRC) $(SHARED_HDR)
	$(CXX) $(CXXFLAGS) -o $@ $(MAIN_SRC) $(BRUTEFORCE_SRC) $(DIVIDEANDCONQUER_SRC) $(SHARED_SRC)

# Compile the text file generator
$(CREATE_EXEC): $(CREATE_SRC) $(CREATE_HDR) 
	$(CXX) $(CXXFLAGS) -o $@ $^

# Generate all text files
generate_textfiles: $(CREATE_EXEC)
	$(CREATE_EXEC)

# Run the main program
run: $(MAIN_EXEC)
	./$(MAIN_EXEC)

# Clean up build files and generated text files
clean:
	rm -rf $(BIN_DIR) $(TEXTFILES_DIR)/*.txt

# Phony targets
.PHONY: all clean run generate_textfiles
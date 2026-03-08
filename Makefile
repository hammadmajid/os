# Compiler and flags
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17

# Find all directories containing .cpp files (excluding hidden directories)
SRC_DIRS = $(sort $(dir $(wildcard */*.cpp)))

# Find all .cpp files in all directories
SOURCES = $(wildcard */*.cpp)

# Create executable paths (same directory as source, no extension)
EXECUTABLES = $(SOURCES:.cpp=)

# Default target: compile all
all: $(EXECUTABLES)
	@echo "Compilation complete!"
	@echo "Compiled $(words $(EXECUTABLES)) executable(s) from $(words $(SRC_DIRS)) directory(ies)"

# Pattern rule to compile each .cpp file independently
%: %.cpp
	@echo "Compiling $< -> $@"
	$(CXX) $(CXXFLAGS) $< -o $@

# Clean target: remove all executables
clean:
	@echo "Cleaning executables..."
	rm -f $(EXECUTABLES)
	@echo "Clean complete!"

# List all source files and directories
list:
	@echo "Directories with C++ files:"
	@echo "$(SRC_DIRS)" | tr ' ' '\n'
	@echo ""
	@echo "Source files found:"
	@echo "$(SOURCES)" | tr ' ' '\n'
	@echo ""
	@echo "Executables to be created:"
	@echo "$(EXECUTABLES)" | tr ' ' '\n'

# Phony targets
.PHONY: all clean list help

# Help target
help:
	@echo "Makefile for compiling C++ files independently"
	@echo ""
	@echo "This Makefile automatically finds and compiles all .cpp files"
	@echo "in any subdirectory (e.g., week-1/, week-2/, project/, etc.)"
	@echo ""
	@echo "Targets:"
	@echo "  all     - Compile all .cpp files in all directories (default)"
	@echo "  clean   - Remove all compiled executables"
	@echo "  list    - List all source files and directories"
	@echo "  help    - Show this help message"
	@echo ""
	@echo "Current status:"
	@echo "  Directories: $(words $(SRC_DIRS))"
	@echo "  Source files: $(words $(SOURCES))"

# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.14

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/local/Cellar/cmake/3.14.4/bin/cmake

# The command to remove a file.
RM = /usr/local/Cellar/cmake/3.14.4/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/kmoy001/libCellML

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/kmoy001/libCellML

# Utility rule file for clean_coverage.

# Include the progress variables for this target.
include tests/CMakeFiles/clean_coverage.dir/progress.make

tests/CMakeFiles/clean_coverage:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/Users/kmoy001/libCellML/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Clean old coverage data"
	cd /Users/kmoy001/libCellML/tests && find /Users/kmoy001/libCellML/src/CMakeFiles/cellml.dir -type f -name '*.gcda' -print | xargs /bin/rm -f

clean_coverage: tests/CMakeFiles/clean_coverage
clean_coverage: tests/CMakeFiles/clean_coverage.dir/build.make

.PHONY : clean_coverage

# Rule to build all files generated by this target.
tests/CMakeFiles/clean_coverage.dir/build: clean_coverage

.PHONY : tests/CMakeFiles/clean_coverage.dir/build

tests/CMakeFiles/clean_coverage.dir/clean:
	cd /Users/kmoy001/libCellML/tests && $(CMAKE_COMMAND) -P CMakeFiles/clean_coverage.dir/cmake_clean.cmake
.PHONY : tests/CMakeFiles/clean_coverage.dir/clean

tests/CMakeFiles/clean_coverage.dir/depend:
	cd /Users/kmoy001/libCellML && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/kmoy001/libCellML /Users/kmoy001/libCellML/tests /Users/kmoy001/libCellML /Users/kmoy001/libCellML/tests /Users/kmoy001/libCellML/tests/CMakeFiles/clean_coverage.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : tests/CMakeFiles/clean_coverage.dir/depend


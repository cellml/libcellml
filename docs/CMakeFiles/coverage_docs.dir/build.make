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

# Utility rule file for coverage_docs.

# Include the progress variables for this target.
include docs/CMakeFiles/coverage_docs.dir/progress.make

docs/CMakeFiles/coverage_docs:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/Users/kmoy001/libCellML/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Running coverage tests with html output"
	cd /Users/kmoy001/libCellML/docs && /usr/local/Cellar/cmake/3.14.4/bin/cmake -E make_directory /Users/kmoy001/libCellML/docs/html/coverage/
	cd /Users/kmoy001/libCellML/docs && /usr/local/Frameworks/Python.framework/Versions/3.7/bin/python3.7 /Users/kmoy001/libCellML/tests/gcovr.py --exclude-unreachable-branches -r /Users/kmoy001/libCellML/src/CMakeFiles/cellml.dir --filter=/Users/kmoy001/libCellML/src --html --html-details --output=/Users/kmoy001/libCellML/docs/html/coverage/index.html --gcov-executable=/usr/bin/gcov

coverage_docs: docs/CMakeFiles/coverage_docs
coverage_docs: docs/CMakeFiles/coverage_docs.dir/build.make

.PHONY : coverage_docs

# Rule to build all files generated by this target.
docs/CMakeFiles/coverage_docs.dir/build: coverage_docs

.PHONY : docs/CMakeFiles/coverage_docs.dir/build

docs/CMakeFiles/coverage_docs.dir/clean:
	cd /Users/kmoy001/libCellML/docs && $(CMAKE_COMMAND) -P CMakeFiles/coverage_docs.dir/cmake_clean.cmake
.PHONY : docs/CMakeFiles/coverage_docs.dir/clean

docs/CMakeFiles/coverage_docs.dir/depend:
	cd /Users/kmoy001/libCellML && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/kmoy001/libCellML /Users/kmoy001/libCellML/docs /Users/kmoy001/libCellML /Users/kmoy001/libCellML/docs /Users/kmoy001/libCellML/docs/CMakeFiles/coverage_docs.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : docs/CMakeFiles/coverage_docs.dir/depend


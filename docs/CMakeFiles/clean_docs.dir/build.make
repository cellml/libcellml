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

# Utility rule file for clean_docs.

# Include the progress variables for this target.
include docs/CMakeFiles/clean_docs.dir/progress.make

docs/CMakeFiles/clean_docs:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/Users/kmoy001/libCellML/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Cleaning documentation"
	cd /Users/kmoy001/libCellML/docs && /usr/local/Cellar/cmake/3.14.4/bin/cmake -E remove_directory /Users/kmoy001/libCellML/docs/html
	cd /Users/kmoy001/libCellML/docs && /usr/local/Cellar/cmake/3.14.4/bin/cmake -E remove_directory /Users/kmoy001/libCellML/docs/_doctrees

clean_docs: docs/CMakeFiles/clean_docs
clean_docs: docs/CMakeFiles/clean_docs.dir/build.make

.PHONY : clean_docs

# Rule to build all files generated by this target.
docs/CMakeFiles/clean_docs.dir/build: clean_docs

.PHONY : docs/CMakeFiles/clean_docs.dir/build

docs/CMakeFiles/clean_docs.dir/clean:
	cd /Users/kmoy001/libCellML/docs && $(CMAKE_COMMAND) -P CMakeFiles/clean_docs.dir/cmake_clean.cmake
.PHONY : docs/CMakeFiles/clean_docs.dir/clean

docs/CMakeFiles/clean_docs.dir/depend:
	cd /Users/kmoy001/libCellML && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/kmoy001/libCellML /Users/kmoy001/libCellML/docs /Users/kmoy001/libCellML /Users/kmoy001/libCellML/docs /Users/kmoy001/libCellML/docs/CMakeFiles/clean_docs.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : docs/CMakeFiles/clean_docs.dir/depend


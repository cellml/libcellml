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

# Include any dependencies generated for this target.
include tests/gtest/CMakeFiles/gtest.dir/depend.make

# Include the progress variables for this target.
include tests/gtest/CMakeFiles/gtest.dir/progress.make

# Include the compile flags for this target's objects.
include tests/gtest/CMakeFiles/gtest.dir/flags.make

tests/gtest/CMakeFiles/gtest.dir/src/gtest-all.cc.o: tests/gtest/CMakeFiles/gtest.dir/flags.make
tests/gtest/CMakeFiles/gtest.dir/src/gtest-all.cc.o: tests/gtest/src/gtest-all.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/kmoy001/libCellML/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object tests/gtest/CMakeFiles/gtest.dir/src/gtest-all.cc.o"
	cd /Users/kmoy001/libCellML/tests/gtest && /Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/gtest.dir/src/gtest-all.cc.o -c /Users/kmoy001/libCellML/tests/gtest/src/gtest-all.cc

tests/gtest/CMakeFiles/gtest.dir/src/gtest-all.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/gtest.dir/src/gtest-all.cc.i"
	cd /Users/kmoy001/libCellML/tests/gtest && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/kmoy001/libCellML/tests/gtest/src/gtest-all.cc > CMakeFiles/gtest.dir/src/gtest-all.cc.i

tests/gtest/CMakeFiles/gtest.dir/src/gtest-all.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/gtest.dir/src/gtest-all.cc.s"
	cd /Users/kmoy001/libCellML/tests/gtest && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/kmoy001/libCellML/tests/gtest/src/gtest-all.cc -o CMakeFiles/gtest.dir/src/gtest-all.cc.s

# Object files for target gtest
gtest_OBJECTS = \
"CMakeFiles/gtest.dir/src/gtest-all.cc.o"

# External object files for target gtest
gtest_EXTERNAL_OBJECTS =

tests/gtest/libgtest.dylib: tests/gtest/CMakeFiles/gtest.dir/src/gtest-all.cc.o
tests/gtest/libgtest.dylib: tests/gtest/CMakeFiles/gtest.dir/build.make
tests/gtest/libgtest.dylib: tests/gtest/CMakeFiles/gtest.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/kmoy001/libCellML/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX shared library libgtest.dylib"
	cd /Users/kmoy001/libCellML/tests/gtest && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/gtest.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
tests/gtest/CMakeFiles/gtest.dir/build: tests/gtest/libgtest.dylib

.PHONY : tests/gtest/CMakeFiles/gtest.dir/build

tests/gtest/CMakeFiles/gtest.dir/clean:
	cd /Users/kmoy001/libCellML/tests/gtest && $(CMAKE_COMMAND) -P CMakeFiles/gtest.dir/cmake_clean.cmake
.PHONY : tests/gtest/CMakeFiles/gtest.dir/clean

tests/gtest/CMakeFiles/gtest.dir/depend:
	cd /Users/kmoy001/libCellML && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/kmoy001/libCellML /Users/kmoy001/libCellML/tests/gtest /Users/kmoy001/libCellML /Users/kmoy001/libCellML/tests/gtest /Users/kmoy001/libCellML/tests/gtest/CMakeFiles/gtest.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : tests/gtest/CMakeFiles/gtest.dir/depend


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

# Utility rule file for variable_swig_compilation.

# Include the progress variables for this target.
include src/bindings/python/CMakeFiles/variable_swig_compilation.dir/progress.make

src/bindings/python/CMakeFiles/variable_swig_compilation: src/bindings/python/CMakeFiles/variable.dir/variablePYTHON.stamp


src/bindings/python/CMakeFiles/variable.dir/variablePYTHON.stamp: src/bindings/interface/variable.i
src/bindings/python/CMakeFiles/variable.dir/variablePYTHON.stamp: src/bindings/interface/variable.i
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/Users/kmoy001/libCellML/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Swig compile ../interface/variable.i for python"
	cd /Users/kmoy001/libCellML/src/bindings/python && /usr/local/Cellar/cmake/3.14.4/bin/cmake -E make_directory /Users/kmoy001/libCellML/src/bindings/python/swig_generated_python_files /Users/kmoy001/libCellML/src/bindings/python/swig_intermediaries
	cd /Users/kmoy001/libCellML/src/bindings/python && /usr/local/Cellar/cmake/3.14.4/bin/cmake -E touch /Users/kmoy001/libCellML/src/bindings/python/CMakeFiles/variable.dir/variablePYTHON.stamp
	cd /Users/kmoy001/libCellML/src/bindings/python && /usr/local/Cellar/cmake/3.14.4/bin/cmake -E env SWIG_LIB=/usr/local/Cellar/swig/4.0.0/share/swig/4.0.0 /usr/local/bin/swig -python -I/Users/kmoy001/libCellML/src/api -I/Users/kmoy001/libCellML/src/api -outdir /Users/kmoy001/libCellML/src/bindings/python/swig_generated_python_files -c++ -o /Users/kmoy001/libCellML/src/bindings/python/swig_intermediaries/variablePYTHON_wrap.cxx /Users/kmoy001/libCellML/src/bindings/interface/variable.i

variable_swig_compilation: src/bindings/python/CMakeFiles/variable_swig_compilation
variable_swig_compilation: src/bindings/python/CMakeFiles/variable.dir/variablePYTHON.stamp
variable_swig_compilation: src/bindings/python/CMakeFiles/variable_swig_compilation.dir/build.make

.PHONY : variable_swig_compilation

# Rule to build all files generated by this target.
src/bindings/python/CMakeFiles/variable_swig_compilation.dir/build: variable_swig_compilation

.PHONY : src/bindings/python/CMakeFiles/variable_swig_compilation.dir/build

src/bindings/python/CMakeFiles/variable_swig_compilation.dir/clean:
	cd /Users/kmoy001/libCellML/src/bindings/python && $(CMAKE_COMMAND) -P CMakeFiles/variable_swig_compilation.dir/cmake_clean.cmake
.PHONY : src/bindings/python/CMakeFiles/variable_swig_compilation.dir/clean

src/bindings/python/CMakeFiles/variable_swig_compilation.dir/depend:
	cd /Users/kmoy001/libCellML && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/kmoy001/libCellML /Users/kmoy001/libCellML/src/bindings/python /Users/kmoy001/libCellML /Users/kmoy001/libCellML/src/bindings/python /Users/kmoy001/libCellML/src/bindings/python/CMakeFiles/variable_swig_compilation.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/bindings/python/CMakeFiles/variable_swig_compilation.dir/depend


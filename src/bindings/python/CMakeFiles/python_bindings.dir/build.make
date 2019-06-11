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

# Utility rule file for python_bindings.

# Include the progress variables for this target.
include src/bindings/python/CMakeFiles/python_bindings.dir/progress.make

src/bindings/python/CMakeFiles/python_bindings: src/bindings/python/libcellml/_component.so
src/bindings/python/CMakeFiles/python_bindings: src/bindings/python/libcellml/_componententity.so
src/bindings/python/CMakeFiles/python_bindings: src/bindings/python/libcellml/_error.so
src/bindings/python/CMakeFiles/python_bindings: src/bindings/python/libcellml/_entity.so
src/bindings/python/CMakeFiles/python_bindings: src/bindings/python/libcellml/_enumerations.so
src/bindings/python/CMakeFiles/python_bindings: src/bindings/python/libcellml/_importsource.so
src/bindings/python/CMakeFiles/python_bindings: src/bindings/python/libcellml/_importedentity.so
src/bindings/python/CMakeFiles/python_bindings: src/bindings/python/libcellml/_logger.so
src/bindings/python/CMakeFiles/python_bindings: src/bindings/python/libcellml/_model.so
src/bindings/python/CMakeFiles/python_bindings: src/bindings/python/libcellml/_namedentity.so
src/bindings/python/CMakeFiles/python_bindings: src/bindings/python/libcellml/_orderedentity.so
src/bindings/python/CMakeFiles/python_bindings: src/bindings/python/libcellml/_parser.so
src/bindings/python/CMakeFiles/python_bindings: src/bindings/python/libcellml/_printer.so
src/bindings/python/CMakeFiles/python_bindings: src/bindings/python/libcellml/_reset.so
src/bindings/python/CMakeFiles/python_bindings: src/bindings/python/libcellml/_specificationrule.so
src/bindings/python/CMakeFiles/python_bindings: src/bindings/python/libcellml/_units.so
src/bindings/python/CMakeFiles/python_bindings: src/bindings/python/libcellml/_validator.so
src/bindings/python/CMakeFiles/python_bindings: src/bindings/python/libcellml/_variable.so
src/bindings/python/CMakeFiles/python_bindings: src/bindings/python/libcellml/_version.so
src/bindings/python/CMakeFiles/python_bindings: src/bindings/python/libcellml/_when.so


python_bindings: src/bindings/python/CMakeFiles/python_bindings
python_bindings: src/bindings/python/CMakeFiles/python_bindings.dir/build.make
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold "Finalise preparation of libCellML Python bindings."
	cd /Users/kmoy001/libCellML/src/bindings/python && /usr/local/Cellar/cmake/3.14.4/bin/cmake -DLIBCELLML_PYTHON_PACKAGE_DIR=/Users/kmoy001/libCellML/src/bindings/python/libcellml -DTARGET_FILE_NAME_cellml=libcellmld.0.2.0.dylib -DTARGET_FILE_NAME_component=_component.so -DTARGET_FILE_NAME_componententity=_componententity.so -DTARGET_FILE_NAME_error=_error.so -DTARGET_FILE_NAME_entity=_entity.so -DTARGET_FILE_NAME_enumerations=_enumerations.so -DTARGET_FILE_NAME_importsource=_importsource.so -DTARGET_FILE_NAME_importedentity=_importedentity.so -DTARGET_FILE_NAME_logger=_logger.so -DTARGET_FILE_NAME_model=_model.so -DTARGET_FILE_NAME_namedentity=_namedentity.so -DTARGET_FILE_NAME_orderedentity=_orderedentity.so -DTARGET_FILE_NAME_parser=_parser.so -DTARGET_FILE_NAME_printer=_printer.so -DTARGET_FILE_NAME_reset=_reset.so -DTARGET_FILE_NAME_specificationrule=_specificationrule.so -DTARGET_FILE_NAME_units=_units.so -DTARGET_FILE_NAME_validator=_validator.so -DTARGET_FILE_NAME_variable=_variable.so -DTARGET_FILE_NAME_version=_version.so -DTARGET_FILE_NAME_when=_when.so -P /Users/kmoy001/libCellML/src/bindings/python/finalise_python_package.cmake
	cd /Users/kmoy001/libCellML/src/bindings/python && /usr/local/Cellar/cmake/3.14.4/bin/cmake -E copy_if_different /Users/kmoy001/libCellML/src/libcellmld.0.2.0.dylib /Users/kmoy001/libCellML/src/bindings/python/libcellml
	cd /Users/kmoy001/libCellML/src/bindings/python && /usr/local/Cellar/cmake/3.14.4/bin/cmake -E copy_directory /Users/kmoy001/libCellML/src/bindings/python/swig_generated_python_files /Users/kmoy001/libCellML/src/bindings/python/libcellml
.PHONY : python_bindings

# Rule to build all files generated by this target.
src/bindings/python/CMakeFiles/python_bindings.dir/build: python_bindings

.PHONY : src/bindings/python/CMakeFiles/python_bindings.dir/build

src/bindings/python/CMakeFiles/python_bindings.dir/clean:
	cd /Users/kmoy001/libCellML/src/bindings/python && $(CMAKE_COMMAND) -P CMakeFiles/python_bindings.dir/cmake_clean.cmake
.PHONY : src/bindings/python/CMakeFiles/python_bindings.dir/clean

src/bindings/python/CMakeFiles/python_bindings.dir/depend:
	cd /Users/kmoy001/libCellML && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/kmoy001/libCellML /Users/kmoy001/libCellML/src/bindings/python /Users/kmoy001/libCellML /Users/kmoy001/libCellML/src/bindings/python /Users/kmoy001/libCellML/src/bindings/python/CMakeFiles/python_bindings.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/bindings/python/CMakeFiles/python_bindings.dir/depend


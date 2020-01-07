cmake_minimum_required(VERSION 3.10.2)
# Delete the previous cache and configured files from this directory before configuring again
# I don't know why it doesn't work ... TODO
file(REMOVE [CMakeCache.txt Makefile cmake_install.cmake modelToSolve.cpp *.h])
file(REMOVE_RECURSE [CMakeFiles])

set(INPUT "" CACHE FILEPATH "Please enter the base name of the generated files to solve (without extension) using the syntax -DINPUT=your_filename")

if("${INPUT}" STREQUAL "")
        message(FATAL_ERROR "Please enter the base name of the generated files to solve (without extension) using the syntax -DINPUT=your_filename")
endif()

get_filename_component(INPUTNAME ${INPUT} NAME)
get_filename_component(INPUTDIR ${INPUT} DIRECTORY)

set(PROJECT_NAME solve_${INPUTNAME})

project(${PROJECT_NAME} VERSION 0.1.0)

if(EXISTS "${INPUTDIR}/${INPUTNAME}.c")
        configure_file("${INPUTDIR}/${INPUTNAME}.c" "${CMAKE_BINARY_DIR}/modelToSolve.cpp" COPYONLY)
elseif(EXISTS "${INPUTDIR}/${INPUTNAME}.cpp")
        configure_file("${INPUTDIR}/${INPUTNAME}.cpp" "${CMAKE_BINARY_DIR}/modelToSolve.cpp" COPYONLY)
endif()

configure_file("${INPUTDIR}/${INPUTNAME}.h" "${CMAKE_BINARY_DIR}/modelToSolve.h" COPYONLY)
configure_file("${INPUTDIR}/${INPUTNAME}.h" "${CMAKE_BINARY_DIR}/${INPUTNAME}.h" COPYONLY)
# TODO This line is a workaround because at present the generator expects the header file to be called "model.h"
# We don't want users to have to modify the generated code, so until there's a better way for users to set
# this in the API, this should stay here.  Yes, it's super-clumsy :(
configure_file("${INPUTDIR}/${INPUTNAME}.h" "${CMAKE_BINARY_DIR}/model.h" COPYONLY)

set (PROJECT_SRC
        simpleSolver.cpp
        modelToSolve.cpp
     )

add_executable(${PROJECT_NAME} ${PROJECT_SRC})

message("")
message("1) First use 'make -j' to build the executable")
message("2) Then solve by running: ./${PROJECT_NAME} with the arguments:")
message("  -n  step_total")
message("  -dt step_size")
message("")

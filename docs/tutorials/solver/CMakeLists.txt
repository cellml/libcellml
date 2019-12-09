cmake_minimum_required(VERSION 3.10.2)
set(INPUT "" CACHE STRING  "Enter the base name of the .c and .h files output from the generator.")
if("${INPUT}" STREQUAL "")
        message(FATAL_ERROR "Please enter the base name of the generated files to solve (without extension) using the syntax -DINPUT=your_filename")
endif()

set(PROJECT_NAME solve_${INPUT})

project(${PROJECT_NAME} VERSION 0.1.0)
set(libCellML_DIR "../../libcellml/install/lib/cmake/libCellML")
find_package(libCellML REQUIRED)

configure_file(${INPUT}.cpp "modelToSolve.cpp" COPYONLY)
configure_file(${INPUT}.h "modelToSolve.h" COPYONLY)

set (PROJECT_SRC
        simpleSolver.cpp
        modelToSolve.cpp
     )

add_executable(${PROJECT_NAME} ${PROJECT_SRC})
target_link_libraries(${PROJECT_NAME}  PUBLIC cellml)

message("")
message("1) First use 'make -j ${PROJECT_NAME}' to build the file for running")
message("2) Then solve by running: ./${PROJECT_NAME} with the arguments:")
message("  -n  step_total")
message("  -dt step_size")
message("")

cmake_minimum_required(VERSION 3.10.2)
set(INPUT "" CACHE FILEPATH  "Enter the base name of the .c and .h files output from the generator.")

get_filename_component(INPUTNAME ${INPUT} NAME)
get_filename_component(INPUTDIR ${INPUT} DIRECTORY)

if("${INPUT}" STREQUAL "")
        message(FATAL_ERROR "Please enter the base name of the generated files to solve (without extension) using the syntax -DINPUT=your_filename")
endif()

set(PROJECT_NAME solve_${INPUTNAME})

project(${PROJECT_NAME} VERSION 0.1.0)
set(libCellML_DIR "../../libcellml/install/lib/cmake/libCellML")
find_package(libCellML REQUIRED)


if(EXISTS "${INPUTDIR}/${INPUTNAME}.cpp")
        configure_file("${INPUTDIR}/${INPUTNAME}.cpp" "${CMAKE_BINARY_DIR}/modelToSolve.cpp" COPYONLY)
elseif(EXISTS "${INPUTDIR}/${INPUTNAME}.c")
        configure_file("${INPUTDUR}/${INPUTNAME}.c" "${CMAKE_BINARY_DIR}/modelToSolve.cpp" COPYONLY)
endif()

configure_file(${INPUTDIR}/${INPUTNAME}.h "${CMAKE_BINARY_DIR}/modelToSolve.h" COPYONLY)
configure_file(${INPUTDIR}/${INPUTNAME}.h "${CMAKE_BINARY_DIR}/${INPUTNAME}.h" COPYONLY)

set (PROJECT_SRC
        simpleSolver.cpp
        modelToSolve.cpp
     )

add_executable(${PROJECT_NAME} ${PROJECT_SRC})
target_link_libraries(${PROJECT_NAME}  PUBLIC cellml)

message("")
message("1) First use 'make -j' to build the executable")
message("2) Then solve by running: ./${PROJECT_NAME} with the arguments:")
message("  -n  step_total")
message("  -dt step_size")
message("")

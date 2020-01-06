cmake_minimum_required(VERSION 3.10.2)
set(PROJECT_NAME tutorial7)

project(${PROJECT_NAME} VERSION 0.1.0)
set(libCellML_DIR "../../../../install/lib/cmake/libCellML")
find_package(libCellML REQUIRED)

set (PROJECT_SRC
        ${PROJECT_NAME}.cpp
        ../utilities/tutorial_utilities.cpp
     )

add_executable(${PROJECT_NAME}  ${PROJECT_SRC})
target_link_libraries(${PROJECT_NAME}  PUBLIC cellml)

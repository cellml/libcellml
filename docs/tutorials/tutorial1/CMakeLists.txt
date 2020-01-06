cmake_minimum_required(VERSION 3.10.2)
set(PROJECT_NAME tutorial1)

project(${PROJECT_NAME} VERSION 0.1.0)
set(INSTALL_PREFIX "" CACHE PATH "Please enter the path to the libCellML install directory using the syntax -DINSTALL_PREFIX=your_path")
set(libCellML_DIR "${INSTALL_PREFIX}/lib/cmake/libCellML")
find_package(libCellML REQUIRED)

set (PROJECT_SRC
        ${PROJECT_NAME}.cpp
     )

add_executable(${PROJECT_NAME}  ${PROJECT_SRC})
target_link_libraries(${PROJECT_NAME}  PUBLIC cellml)

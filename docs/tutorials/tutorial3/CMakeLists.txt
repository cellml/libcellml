cmake_minimum_required(VERSION 3.10.2)
set(PROJECT_NAME tutorial3)
set(INSTALL_PREFIX "" CACHE PATH "Please enter the path to the libCellML install directory using the syntax -DINSTALL_PREFIX=your_path")
set(libCellML_DIR "${INSTALL_PREFIX}/lib/cmake/libCellML")
find_package(libCellML REQUIRED)

project(${PROJECT_NAME} VERSION 0.1.0)
set (PROJECT_SRC
        ${PROJECT_NAME}.cpp
        ../utilities/tutorial_utilities.cpp
     )
add_executable(${PROJECT_NAME}  ${PROJECT_SRC})
target_link_libraries(${PROJECT_NAME}  PUBLIC cellml)




set(COMPLETE_PROJECT_NAME ${PROJECT_NAME}_complete)
project(${COMPLETE_PROJECT_NAME} VERSION 0.1.0)

set (COMPLETE_PROJECT_SRC
        ${COMPLETE_PROJECT_NAME}.cpp
        ../utilities/tutorial_utilities.cpp
     )

add_executable(${COMPLETE_PROJECT_NAME}  ${COMPLETE_PROJECT_SRC})
target_link_libraries(${COMPLETE_PROJECT_NAME}  PUBLIC cellml)

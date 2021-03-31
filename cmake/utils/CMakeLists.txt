cmake_minimum_required(VERSION 3.18.0)

find_package(ZLIB REQUIRED)

set(MATHML_DTD_LOCATION "${PROJECT_SOURCE_DIR}/src/dtds/mathml2/xhtml-math11-f.dtd")
configure_file(compress.in.h compress.h)

add_executable(compress EXCLUDE_FROM_ALL compress.cpp compress.h)
target_include_directories(compress PRIVATE ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR})
if(TARGET zlib)
  target_link_libraries(compress PRIVATE zlib)
else()
  target_link_libraries(compress ${ZLIB_LIBRARIES})
  target_include_directories(compress PRIVATE ${ZLIB_INCLUDE_DIRS})
endif()

add_custom_command(OUTPUT mathmldtd.h
    COMMAND compress
    COMMAND ${CMAKE_COMMAND} -P "${PROJECT_SOURCE_DIR}/cmake/binary_to_char_array.cmake" "${CMAKE_CURRENT_BINARY_DIR}/compressed.dat"
    DEPENDS compress)

add_custom_target(create_mathml_dtd_header
    DEPENDS mathmldtd.h
    COMMENT "Create mathmldtd header file.")

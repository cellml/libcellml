
# Set the test name, 'test_' will be prepended to the
# name set here
set(CURRENT_TEST parser)
# Set a category name to enable running commands like:
#    ctest -R <category-label>
# which will run the tests matching this category-label.
# Can be left empty (or just not set)
set(${CURRENT_TEST}_CATEGORY misc)
list(APPEND LIBCELLML_TESTS ${CURRENT_TEST})
# Using absolute path relative to this file
set(${CURRENT_TEST}_SRCS
  ${CMAKE_CURRENT_LIST_DIR}/parser.cpp
  ${CMAKE_CURRENT_LIST_DIR}/file_parser.cpp
)
#set(${CURRENT_TEST}_HDRS
#  ${CMAKE_CURRENT_LIST_DIR}/<test_header_files.h>
#)


set(CELLML_SINE_MODEL_RESOURCE "${CMAKE_CURRENT_SOURCE_DIR}/resources/sine_approximations.xml")
set(CELLML_SINE_IMPORTS_MODEL_RESOURCE "${CMAKE_CURRENT_SOURCE_DIR}/resources/sine_approximations_import.xml")
set(CELLML_ORD_MODEL_RESOURCE "${CMAKE_CURRENT_SOURCE_DIR}/resources/Ohara_Rudy_2011.cellml")
set(CELLML_INVALID_MODEL_RESOURCE "${CMAKE_CURRENT_SOURCE_DIR}/resources/invalid_cellml_2.0.xml")



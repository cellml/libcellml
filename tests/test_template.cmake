
# Set the test name, 'test_' will be prepended to the
# name set here
set(CURRENT_TEST <test-name>)
# Set a category name to enable running commands like:
#    ctest -R <category-label>
# which will run the tests matching this category-label.
# Can be left empty (or just not set)
set(CURRENT_CATEGORY <category-label>)
list(APPEND YAWOT_TESTS ${CURRENT_TEST})
# Remember this is relative to the CMakeLists.txt file in 
# the tests directory
set(${CURRENT_TEST}_SRCS
  ${CURRENT_TEST}/<test_source_files.cpp>
)
set(${CURRENT_TEST}_HDRS
  ${CURRENT_TEST}/<test_header_files.h>
)



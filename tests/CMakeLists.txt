
# include gtest so we can make use of the gtest_main target
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/gtest-1.7.0)

# Any tests included here must append the test name
# to the LIBCELLML_TESTS list.  Any source files for the
# test must be set to <test_name>_SRCS, likewise for
# header files <test_name>_HDRS.
include(version/tests.cmake)

# Cycle through all the tests 'included' above
set(TEST_LIST)
foreach(TEST ${LIBCELLML_TESTS})
  set(CURRENT_TEST test_${TEST})
  if(CURRENT_CATEGORY)
    set(CURRENT_CATEGORY "${CURRENT_CATEGORY}_")
  endif()
  add_executable(${CURRENT_TEST} ${${TEST}_SRCS} ${${TEST}_HDRS})
  target_link_libraries(${CURRENT_TEST} cellml gtest_main)
#  if(LIBCELLML_TREAT_WARNINGS_AS_ERRORS)
#    target_warnings_as_errors(${CURRENT_TEST})
#  endif()

  add_test(${CURRENT_CATEGORY}unit_${CURRENT_TEST} ${CURRENT_TEST})
  list(APPEND TEST_LIST ${CURRENT_TEST})
  unset(CURRENT_CATEGORY)
endforeach()

if(LIBCELLML_COVERAGE)
  # Prepare for test coverage by generating the gcov note files
  # and creating an output directory for the data files
  add_custom_target(prepare_coverage
    COMMAND find ${GCOV_ANALYSIS_PATH} -type f -name '*.gcda' -print | xargs /bin/rm -f
    COMMAND ctest > /dev/null
    COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_CURRENT_BINARY_DIR}/gcov
    COMMENT "Prepare for coverage tests")

  add_custom_target(coverage
    COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/gcovcoverage.py ${GCOV_ANALYSIS_PATH} ${GCOV_PREFIX_PATH} ${GCOV_BUILD_PREFIX_PATH}
    DEPENDS ${TEST_LIST} prepare_coverage
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/gcov
    COMMENT "Running coverage tests")
endif()

if(LIBCELLML_MEMCHECK)
  add_custom_target(prepare_memcheck
    COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_CURRENT_BINARY_DIR}/memcheck
    COMMENT "Prepare for memcheck tests")

  add_custom_target(memcheck
    COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/valgrindmemcheck.py ${CMAKE_CURRENT_BINARY_DIR} ${TEST_LIST}
    DEPENDS ${TEST_LIST} prepare_memcheck
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/memcheck
    COMMENT "Running memcheck tests")
endif()


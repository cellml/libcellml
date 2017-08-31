
# include gtest so we can make use of the gtest_main target
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/gtest-1.7.0)
if(APPLE)
  set_target_properties(gtest gtest_main PROPERTIES MACOSX_RPATH ON)
endif()
set_target_properties(gtest gtest_main PROPERTIES FOLDER gtest)
mark_as_advanced(gtest_disable_pthreads)
mark_as_advanced(gtest_force_shared_crt)

# Any tests included here must append the test name
# to the LIBCELLML_TESTS list.  Any source files for the
# test must be set to <test_name>_SRCS, likewise for
# header files <test_name>_HDRS.
include(component/tests.cmake)
include(connection/tests.cmake)
include(coverage/tests.cmake)
include(math/tests.cmake)
include(model/tests.cmake)
include(parser/tests.cmake)
include(printer/tests.cmake)
include(units/tests.cmake)
include(validator/tests.cmake)
include(variable/tests.cmake)
include(version/tests.cmake)

set(test_path)
list(APPEND test_path $ENV{PATH} $<TARGET_FILE_DIR:cellml>)
# Cycle through all the tests 'included' above
set(TEST_LIST)
foreach(TEST ${LIBCELLML_TESTS})
  set(CURRENT_TEST test_${TEST})
  set(CURRENT_CATEGORY ${${TEST}_CATEGORY})
  if(CURRENT_CATEGORY)
    set(CURRENT_CATEGORY "${CURRENT_CATEGORY}_")
  endif()
  add_executable(${CURRENT_TEST} ${${TEST}_SRCS} ${${TEST}_HDRS})
  target_include_directories(${CURRENT_TEST} PUBLIC ${CMAKE_CURRENT_BINARY_DIR})
  target_link_libraries(${CURRENT_TEST} cellml gtest_main)

  set_target_properties(${CURRENT_TEST} PROPERTIES
    CXX_STANDARD 11
    CXX_STANDARD_REQUIRED ON
    FOLDER tests)

#  if(LIBCELLML_TREAT_WARNINGS_AS_ERRORS)
#    target_warnings_as_errors(${CURRENT_TEST})
#  endif()

  add_test(${CURRENT_CATEGORY}unit_${CURRENT_TEST} ${CURRENT_TEST})

  list(APPEND TEST_LIST ${CURRENT_TEST})
  unset(CURRENT_CATEGORY)
endforeach()


if(LIBCELLML_COVERAGE)
  # Clean away old gcov arc files
  add_custom_target(clean_coverage
    COMMAND find ${GCOV_ANALYSIS_PATH} -type f -name '*.gcda' -print | xargs /bin/rm -f
    COMMENT "Clean old coverage data")

  # Prepare for test coverage by generating the gcov note files
  add_custom_target(prepare_coverage
    DEPENDS clean_coverage ${TEST_LIST}
    COMMAND ctest > /dev/null
    COMMENT "Prepare for coverage tests")

  add_custom_target(coverage
    COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/gcovr.py -r ${GCOV_ANALYSIS_PATH} --filter=${GCOV_PREFIX_PATH} --gcov-executable=${GCOV_EXE}
    DEPENDS prepare_coverage
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    COMMENT "Running coverage tests")

  add_custom_target(coverage_branches
    COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/gcovr.py -k -b --exclude-unreachable-branches -r ${GCOV_ANALYSIS_PATH} --filter=${GCOV_PREFIX_PATH}.* --gcov-executable=${GCOV_EXE}
    DEPENDS prepare_coverage
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    COMMENT "Running coverage tests with branches output")
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

include(test_resources.cmake)

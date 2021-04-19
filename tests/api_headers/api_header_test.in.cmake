
add_executable(${CURRENT_TEST} ${TEST_SRC})
target_link_libraries(${CURRENT_TEST} cellml gtest_main)

set_target_properties(${CURRENT_TEST} PROPERTIES
  CXX_STANDARD 11
  CXX_STANDARD_REQUIRED ON
  FOLDER tests)

add_test(NAME api_header_inclusion_${CURRENT_TEST} COMMAND ${CURRENT_TEST})

if(MSVC)
  if(HAVE_LIBXML2_CONFIG)
	set_tests_properties(api_header_inclusion_${CURRENT_TEST}
	PROPERTIES ENVIRONMENT "PATH=$<TARGET_FILE_DIR:cellml>\;$<TARGET_FILE_DIR:gtest_main>\;$<TARGET_FILE_DIR:xml2>")
  else()
	# The libxml2 dll must be on the path otherwise the tests will not be able to run.
	set_tests_properties(api_header_inclusion_${CURRENT_TEST}
	PROPERTIES ENVIRONMENT "PATH=$<TARGET_FILE_DIR:cellml>\;$<TARGET_FILE_DIR:gtest_main>")
  endif()
endif()

list(APPEND TEST_LIST ${CURRENT_TEST})

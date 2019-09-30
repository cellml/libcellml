
add_executable(${CURRENT_TEST} ${TEST_SRC})
target_link_libraries(${CURRENT_TEST} cellml gtest_main)

set_target_properties(${CURRENT_TEST} PROPERTIES
  CXX_STANDARD 11
  CXX_STANDARD_REQUIRED ON
  FOLDER tests)

add_test(NAME api_header_inclusion_${CURRENT_TEST} COMMAND ${CURRENT_TEST})

list(APPEND TEST_LIST ${CURRENT_TEST})

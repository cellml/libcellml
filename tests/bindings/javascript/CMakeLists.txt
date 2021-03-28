
set(TEST_SRCS
  analyser.test.js
  model.test.js
  version.test.js
)

foreach(_TEST ${TEST_SRCS})
  configure_file(${_TEST} ${_TEST} COPYONLY)
endforeach()

file(RELATIVE_PATH _RELATIVE_PATH ${CMAKE_CURRENT_BINARY_DIR} ${PROJECT_BINARY_DIR}/src/bindings/javascript/)

set(TEST_PACKAGE_JSON "{
  \"name\": \"libcellml.js-test\",
  \"version\": \"${PROJECT_VERSION}\",
  \"description\": \"Tests for libcellml.js\",
  \"main\": \"index.js\",
  \"scripts\": {
    \"test\": \"jest\"
  },
  \"author\": \"\",
  \"license\": \"Apache-2.0\",
  \"devDependencies\": {
    \"jest\": \"^26.6.3\"
  },
  \"dependencies\": {
      \"libcellml.js\": \"file:${_RELATIVE_PATH}\"
    }
}
")

file(WRITE "${CMAKE_CURRENT_BINARY_DIR}/package.json" "${TEST_PACKAGE_JSON}")

add_custom_command(
    OUTPUT "package-lock.json"
    COMMAND ${NPM_EXE} install)

add_custom_target(install_modules DEPENDS "package-lock.json;libcellml;libcellml.common")

add_custom_target(jest_test COMMAND ${NPM_EXE} run test DEPENDS "install_modules")
set(_TEST_NAME javascript_api_tests)
add_test(NAME ${_TEST_NAME} COMMAND ${CMAKE_COMMAND} --build . --target jest_test)

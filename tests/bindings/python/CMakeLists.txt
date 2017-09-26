
set(TEST_SRCS
  test_component.py
  test_component_entity.py
  test_entity.py
  test_error.py
  test_import_source.py
  test_imported_entity.py
  test_logger.py
  test_model.py
  test_named_entity.py
  test_parser.py
  test_printer.py
  test_units.py
  test_variable.py
  test_validator.py
)

foreach(_TEST ${TEST_SRCS})
  file(COPY ${_TEST} DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
  get_filename_component(_TEST_NAME ${_TEST} NAME_WE)
  set(_TEST_NAME python_${_TEST_NAME})
  add_test(NAME ${_TEST_NAME} COMMAND ${PYTHON_EXECUTABLE} ${_TEST})
  if (WIN32)
    if (TARGET xml2)
      set(GEN_EXP_XML2_TARGET_FILE_DIR "\;\$<TARGET_FILE_DIR:xml2>")
    endif ()
    set_tests_properties(${_TEST_NAME} PROPERTIES
      ENVIRONMENT "PATH=$<TARGET_FILE_DIR:cellml>\;$<TARGET_FILE_DIR:_entity>${GEN_EXP_XML2_TARGET_FILE_DIR}\;%PATH%;PYTHONPATH=${PROJECT_BINARY_DIR}/src/bindings/python/$<CONFIG>")
  else ()
    set_tests_properties(${_TEST_NAME} PROPERTIES
      ENVIRONMENT "PYTHONPATH=${PROJECT_BINARY_DIR}/src/bindings/python")
  endif ()
  set_property(DIRECTORY APPEND PROPERTY ADDITIONAL_MAKE_CLEAN_FILES
    ${CMAKE_CURRENT_BINARY_DIR}/${_TEST}c
    ${CMAKE_CURRENT_BINARY_DIR}/${_TEST})
endforeach()

set_property(DIRECTORY APPEND PROPERTY ADDITIONAL_MAKE_CLEAN_FILES
    ${CMAKE_CURRENT_BINARY_DIR}/__pycache__)

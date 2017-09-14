
set(TEST_SRCS
    test_basics.py
    test_component.py
    test_component_entity.py
    test_entity.py
    test_imported_entity.py
    test_named_entity.py)

foreach(_TEST ${TEST_SRCS})
    file(COPY ${_TEST} DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
    get_filename_component(_TEST_NAME ${_TEST} NAME_WE)
    string(SUBSTRING ${_TEST_NAME} 5 -1 _TEST_NAME)
    set(_TEST_NAME python_test_${_TEST_NAME})
    add_test(NAME ${_TEST_NAME} COMMAND ${PYTHON_EXECUTABLE} ${_TEST})
    set_tests_properties(${_TEST_NAME} PROPERTIES
        ENVIRONMENT "PYTHONPATH=${PROJECT_BINARY_DIR}/src/bindings/python")
    set_property(DIRECTORY APPEND PROPERTY ADDITIONAL_MAKE_CLEAN_FILES
        ${CMAKE_CURRENT_BINARY_DIR}/${_TEST}c
        ${CMAKE_CURRENT_BINARY_DIR}/${_TEST})
endforeach()

set_property(DIRECTORY APPEND PROPERTY ADDITIONAL_MAKE_CLEAN_FILES
    ${CMAKE_CURRENT_BINARY_DIR}/__pycache__)


set(CELLML_SINE_MODEL_RESOURCE "${CMAKE_CURRENT_SOURCE_DIR}/resources/sine_approximations.xml")
set(CELLML_SINE_IMPORTS_MODEL_RESOURCE "${CMAKE_CURRENT_SOURCE_DIR}/resources/sine_approximations_import.xml")
set(CELLML_COMPLEX_ENCAPSULATION_MODEL_RESOURCE "${CMAKE_CURRENT_SOURCE_DIR}/resources/complex_encapsulation.xml")
set(CELLML_ORD_MODEL_RESOURCE "${CMAKE_CURRENT_SOURCE_DIR}/resources/Ohara_Rudy_2011.cellml")
set(CELLML_A_PLUS_B_MODEL_RESOURCE "${CMAKE_CURRENT_SOURCE_DIR}/resources/a_plus_b.cellml")
set(CELLML_INVALID_MODEL_RESOURCE "${CMAKE_CURRENT_SOURCE_DIR}/resources/invalid_cellml_2.0.xml")

set(TEST_RESOURCE_HEADER ${CMAKE_CURRENT_BINARY_DIR}/test_resources.h)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/test_resources.h.in ${TEST_RESOURCE_HEADER})

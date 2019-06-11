# CMake generated Testfile for 
# Source directory: /Users/kmoy001/libCellML/tests/bindings/python
# Build directory: /Users/kmoy001/libCellML/tests/bindings/python
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(python_test_component "/usr/local/Frameworks/Python.framework/Versions/3.7/bin/python3.7" "test_component.py")
set_tests_properties(python_test_component PROPERTIES  ENVIRONMENT "PYTHONPATH=/Users/kmoy001/libCellML/src/bindings/python" _BACKTRACE_TRIPLES "/Users/kmoy001/libCellML/tests/bindings/python/CMakeLists.txt;28;add_test;/Users/kmoy001/libCellML/tests/bindings/python/CMakeLists.txt;0;")
add_test(python_test_component_entity "/usr/local/Frameworks/Python.framework/Versions/3.7/bin/python3.7" "test_component_entity.py")
set_tests_properties(python_test_component_entity PROPERTIES  ENVIRONMENT "PYTHONPATH=/Users/kmoy001/libCellML/src/bindings/python" _BACKTRACE_TRIPLES "/Users/kmoy001/libCellML/tests/bindings/python/CMakeLists.txt;28;add_test;/Users/kmoy001/libCellML/tests/bindings/python/CMakeLists.txt;0;")
add_test(python_test_entity "/usr/local/Frameworks/Python.framework/Versions/3.7/bin/python3.7" "test_entity.py")
set_tests_properties(python_test_entity PROPERTIES  ENVIRONMENT "PYTHONPATH=/Users/kmoy001/libCellML/src/bindings/python" _BACKTRACE_TRIPLES "/Users/kmoy001/libCellML/tests/bindings/python/CMakeLists.txt;28;add_test;/Users/kmoy001/libCellML/tests/bindings/python/CMakeLists.txt;0;")
add_test(python_test_error "/usr/local/Frameworks/Python.framework/Versions/3.7/bin/python3.7" "test_error.py")
set_tests_properties(python_test_error PROPERTIES  ENVIRONMENT "PYTHONPATH=/Users/kmoy001/libCellML/src/bindings/python" _BACKTRACE_TRIPLES "/Users/kmoy001/libCellML/tests/bindings/python/CMakeLists.txt;28;add_test;/Users/kmoy001/libCellML/tests/bindings/python/CMakeLists.txt;0;")
add_test(python_test_import_source "/usr/local/Frameworks/Python.framework/Versions/3.7/bin/python3.7" "test_import_source.py")
set_tests_properties(python_test_import_source PROPERTIES  ENVIRONMENT "PYTHONPATH=/Users/kmoy001/libCellML/src/bindings/python" _BACKTRACE_TRIPLES "/Users/kmoy001/libCellML/tests/bindings/python/CMakeLists.txt;28;add_test;/Users/kmoy001/libCellML/tests/bindings/python/CMakeLists.txt;0;")
add_test(python_test_imported_entity "/usr/local/Frameworks/Python.framework/Versions/3.7/bin/python3.7" "test_imported_entity.py")
set_tests_properties(python_test_imported_entity PROPERTIES  ENVIRONMENT "PYTHONPATH=/Users/kmoy001/libCellML/src/bindings/python" _BACKTRACE_TRIPLES "/Users/kmoy001/libCellML/tests/bindings/python/CMakeLists.txt;28;add_test;/Users/kmoy001/libCellML/tests/bindings/python/CMakeLists.txt;0;")
add_test(python_test_logger "/usr/local/Frameworks/Python.framework/Versions/3.7/bin/python3.7" "test_logger.py")
set_tests_properties(python_test_logger PROPERTIES  ENVIRONMENT "PYTHONPATH=/Users/kmoy001/libCellML/src/bindings/python" _BACKTRACE_TRIPLES "/Users/kmoy001/libCellML/tests/bindings/python/CMakeLists.txt;28;add_test;/Users/kmoy001/libCellML/tests/bindings/python/CMakeLists.txt;0;")
add_test(python_test_model "/usr/local/Frameworks/Python.framework/Versions/3.7/bin/python3.7" "test_model.py")
set_tests_properties(python_test_model PROPERTIES  ENVIRONMENT "PYTHONPATH=/Users/kmoy001/libCellML/src/bindings/python" _BACKTRACE_TRIPLES "/Users/kmoy001/libCellML/tests/bindings/python/CMakeLists.txt;28;add_test;/Users/kmoy001/libCellML/tests/bindings/python/CMakeLists.txt;0;")
add_test(python_test_named_entity "/usr/local/Frameworks/Python.framework/Versions/3.7/bin/python3.7" "test_named_entity.py")
set_tests_properties(python_test_named_entity PROPERTIES  ENVIRONMENT "PYTHONPATH=/Users/kmoy001/libCellML/src/bindings/python" _BACKTRACE_TRIPLES "/Users/kmoy001/libCellML/tests/bindings/python/CMakeLists.txt;28;add_test;/Users/kmoy001/libCellML/tests/bindings/python/CMakeLists.txt;0;")
add_test(python_test_ordered_entity "/usr/local/Frameworks/Python.framework/Versions/3.7/bin/python3.7" "test_ordered_entity.py")
set_tests_properties(python_test_ordered_entity PROPERTIES  ENVIRONMENT "PYTHONPATH=/Users/kmoy001/libCellML/src/bindings/python" _BACKTRACE_TRIPLES "/Users/kmoy001/libCellML/tests/bindings/python/CMakeLists.txt;28;add_test;/Users/kmoy001/libCellML/tests/bindings/python/CMakeLists.txt;0;")
add_test(python_test_parser "/usr/local/Frameworks/Python.framework/Versions/3.7/bin/python3.7" "test_parser.py")
set_tests_properties(python_test_parser PROPERTIES  ENVIRONMENT "PYTHONPATH=/Users/kmoy001/libCellML/src/bindings/python" _BACKTRACE_TRIPLES "/Users/kmoy001/libCellML/tests/bindings/python/CMakeLists.txt;28;add_test;/Users/kmoy001/libCellML/tests/bindings/python/CMakeLists.txt;0;")
add_test(python_test_printer "/usr/local/Frameworks/Python.framework/Versions/3.7/bin/python3.7" "test_printer.py")
set_tests_properties(python_test_printer PROPERTIES  ENVIRONMENT "PYTHONPATH=/Users/kmoy001/libCellML/src/bindings/python" _BACKTRACE_TRIPLES "/Users/kmoy001/libCellML/tests/bindings/python/CMakeLists.txt;28;add_test;/Users/kmoy001/libCellML/tests/bindings/python/CMakeLists.txt;0;")
add_test(python_test_reset "/usr/local/Frameworks/Python.framework/Versions/3.7/bin/python3.7" "test_reset.py")
set_tests_properties(python_test_reset PROPERTIES  ENVIRONMENT "PYTHONPATH=/Users/kmoy001/libCellML/src/bindings/python" _BACKTRACE_TRIPLES "/Users/kmoy001/libCellML/tests/bindings/python/CMakeLists.txt;28;add_test;/Users/kmoy001/libCellML/tests/bindings/python/CMakeLists.txt;0;")
add_test(python_test_units "/usr/local/Frameworks/Python.framework/Versions/3.7/bin/python3.7" "test_units.py")
set_tests_properties(python_test_units PROPERTIES  ENVIRONMENT "PYTHONPATH=/Users/kmoy001/libCellML/src/bindings/python" _BACKTRACE_TRIPLES "/Users/kmoy001/libCellML/tests/bindings/python/CMakeLists.txt;28;add_test;/Users/kmoy001/libCellML/tests/bindings/python/CMakeLists.txt;0;")
add_test(python_test_variable "/usr/local/Frameworks/Python.framework/Versions/3.7/bin/python3.7" "test_variable.py")
set_tests_properties(python_test_variable PROPERTIES  ENVIRONMENT "PYTHONPATH=/Users/kmoy001/libCellML/src/bindings/python" _BACKTRACE_TRIPLES "/Users/kmoy001/libCellML/tests/bindings/python/CMakeLists.txt;28;add_test;/Users/kmoy001/libCellML/tests/bindings/python/CMakeLists.txt;0;")
add_test(python_test_validator "/usr/local/Frameworks/Python.framework/Versions/3.7/bin/python3.7" "test_validator.py")
set_tests_properties(python_test_validator PROPERTIES  ENVIRONMENT "PYTHONPATH=/Users/kmoy001/libCellML/src/bindings/python" _BACKTRACE_TRIPLES "/Users/kmoy001/libCellML/tests/bindings/python/CMakeLists.txt;28;add_test;/Users/kmoy001/libCellML/tests/bindings/python/CMakeLists.txt;0;")
add_test(python_test_version "/usr/local/Frameworks/Python.framework/Versions/3.7/bin/python3.7" "test_version.py")
set_tests_properties(python_test_version PROPERTIES  ENVIRONMENT "PYTHONPATH=/Users/kmoy001/libCellML/src/bindings/python" _BACKTRACE_TRIPLES "/Users/kmoy001/libCellML/tests/bindings/python/CMakeLists.txt;28;add_test;/Users/kmoy001/libCellML/tests/bindings/python/CMakeLists.txt;0;")
add_test(python_test_when "/usr/local/Frameworks/Python.framework/Versions/3.7/bin/python3.7" "test_when.py")
set_tests_properties(python_test_when PROPERTIES  ENVIRONMENT "PYTHONPATH=/Users/kmoy001/libCellML/src/bindings/python" _BACKTRACE_TRIPLES "/Users/kmoy001/libCellML/tests/bindings/python/CMakeLists.txt;28;add_test;/Users/kmoy001/libCellML/tests/bindings/python/CMakeLists.txt;0;")
add_test(python_test_docstrings "/usr/local/Frameworks/Python.framework/Versions/3.7/bin/python3.7" "test_docstrings.py")
set_tests_properties(python_test_docstrings PROPERTIES  ENVIRONMENT "PYTHONPATH=/Users/kmoy001/libCellML/src/bindings/python" _BACKTRACE_TRIPLES "/Users/kmoy001/libCellML/tests/bindings/python/CMakeLists.txt;28;add_test;/Users/kmoy001/libCellML/tests/bindings/python/CMakeLists.txt;0;")

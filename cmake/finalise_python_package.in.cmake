
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/__init__.py ${LIBCELLML_PYTHON_PACKAGE_DIR}/__init__.py)
configure_file(${SETUP_PRE_GEN_PY_FILE} ${LIBCELLML_PYTHON_PACKAGE_DIR}/../setup.py)

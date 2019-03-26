# Copyright libCellML Contributors
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#    http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.cmake_minimum_required (VERSION 3.1)

if(SPHINX_FOUND)
  set(SPHINX_DOCS_TARGET project_docs)

  if(NOT DEFINED SPHINX_THEME)
    set(SPHINX_THEME theme)
  endif()

  if(NOT DEFINED SPHINX_THEME_DIR)
    set(SPHINX_THEME_DIR "${CMAKE_CURRENT_SOURCE_DIR}")
  endif()

  string(TIMESTAMP SPHINX_YEAR "%Y")

  # configured documentation tools and intermediate build results
  set(BINARY_BUILD_DIR "${CMAKE_CURRENT_BINARY_DIR}/_build")

  # Sphinx cache with pickled ReST documents
  set(SPHINX_CACHE_DIR "${CMAKE_CURRENT_BINARY_DIR}/_doctrees")

  # HTML output directory
  set(SPHINX_HTML_DIR "${CMAKE_CURRENT_BINARY_DIR}/html")

  configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/conf.py.in"
    "${BINARY_BUILD_DIR}/conf.py"
    @ONLY)

  add_custom_target(${SPHINX_DOCS_TARGET}
    COMMAND ${SPHINX_EXECUTABLE}
        -q -b html
        -c "${BINARY_BUILD_DIR}"
        -d "${SPHINX_CACHE_DIR}"
        "${CMAKE_CURRENT_SOURCE_DIR}"
        "${SPHINX_HTML_DIR}"
    COMMENT "Building HTML documentation with Sphinx")
endif()

if(DOXYGEN_FOUND)
  set(DOXYGEN_DOCS_TARGET api_docs)
  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/doxy.config.in ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile @ONLY)
  add_custom_target(${DOXYGEN_DOCS_TARGET}
    COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_CURRENT_BINARY_DIR}/html/code/
    COMMAND ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile

	# These need to be added to the Doxyfile which is generated, but the mechanism for adding (via the set(DOXYGEN_ALIASES)) doesn't seem to work.  Issue logged here: https://gitlab.kitware.com/cmake/cmake/issues/17489
	
	# ALIASES                = "cellml2_2=\xrefitem CellML2_2 \"CellML2_2\" \"CellML 2.0: 2. General Matters \"" 
	# ALIASES				   += "cellml2_3=\xrefitem CellML2_3 \"CellML2_3\" \"CellML 2.0: 3. Data representation \"" 
	# ALIASES				   += "cellml2_4=\xrefitem CellML2_4 \"CellML2_4\" \"CellML 2.0: 4. Model elements \""
	# ALIASES				   += "cellml2_5=\xrefitem CellML2_5 \"CellML2_5\" \"CellML 2.0: 5. Import elements \""
	# ALIASES				   += "cellml2_6=\xrefitem CellML2_6 \"CellML2_6\" \"CellML 2.0: 6. Import-units elements \""
	# ALIASES				   += "cellml2_7=\xrefitem CellML2_7 \"CellML2_7\" \"CellML 2.0: 7. Import-component elements \""
	# ALIASES				   += "cellml2_8=\xrefitem CellML2_8 \"CellML2_8\" \"CellML 2.0: 8. Units elements \""
	# ALIASES				   += "cellml2_9=\xrefitem CellML2_9 \"CellML2_9\" \"CellML 2.0: 9. Unit elements \""
	# ALIASES				   += "cellml2_10=\xrefitem CellML2_10 \"CellML2_10\" \"CellML 2.0: 10. Component elements \""
	# ALIASES				   += "cellml2_11=\xrefitem CellML2_11 \"CellML2_11\" \"CellML 2.0: 11. Variable elements \""
	# ALIASES				   += "cellml2_12=\xrefitem CellML2_12 \"CellML2_12\" \"CellML 2.0: 12. Reset elements \""
	# ALIASES				   += "cellml2_13=\xrefitem CellML2_13 \"CellML2_13\" \"CellML 2.0: 13. When elements \""
	# ALIASES				   += "cellml2_14=\xrefitem CellML2_14 \"CellML2_14\" \"CellML 2.0: 14. Math elements \""
	# ALIASES				   += "cellml2_15=\xrefitem CellML2_15 \"CellML2_15\" \"CellML 2.0: 15. Encapsulation elements \""
	# ALIASES				   += "cellml2_16=\xrefitem CellML2_16 \"CellML2_16\" \"CellML 2.0: 16. Component-ref elements \""
	# ALIASES				   += "cellml2_17=\xrefitem CellML2_17 \"CellML2_17\" \"CellML 2.0: 17. Connection elements \""
	# ALIASES				   += "cellml2_18=\xrefitem CellML2_18 \"CellML2_18\" \"CellML 2.0: 18. Map-variables elements \""
	# ALIASES				   += "cellml2_19=\xrefitem CellML2_19 \"CellML2_19\" \"CellML 2.0: 19. Interpretation of CellML models \""

    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    COMMENT "Generating API documentation with Doxygen" VERBATIM)
endif()

if(LIBCELLML_COVERAGE)
  set(COVERAGE_DOCS_TARGET coverage_docs)
  add_custom_target(${COVERAGE_DOCS_TARGET}
    COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_CURRENT_BINARY_DIR}/html/coverage/
    COMMAND ${CMAKE_SOURCE_DIR}/tests/gcovr.py --exclude-unreachable-branches -r ${GCOV_ANALYSIS_PATH} --filter=${GCOV_PREFIX_PATH} --html --html-details --output=${CMAKE_CURRENT_BINARY_DIR}/html/coverage/index.html --gcov-executable=${GCOV_EXE}
    DEPENDS prepare_coverage
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    COMMENT "Running coverage tests with html output")
endif()

if(SPHINX_FOUND OR DOXYGEN_FOUND OR LIBCELLML_COVERAGE)
  add_custom_target(docs
    DEPENDS ${SPHINX_DOCS_TARGET} ${DOXYGEN_DOCS_TARGET} ${COVERAGE_DOCS_TARGET}
    COMMENT "Generating documentation")
  add_custom_target(clean_docs
    COMMAND ${CMAKE_COMMAND} -E remove_directory ${CMAKE_CURRENT_BINARY_DIR}/html
    COMMAND ${CMAKE_COMMAND} -E remove_directory ${CMAKE_CURRENT_BINARY_DIR}/_doctrees
    COMMENT "Cleaning documentation")
endif()


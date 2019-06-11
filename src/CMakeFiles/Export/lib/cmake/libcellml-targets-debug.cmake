#----------------------------------------------------------------
# Generated CMake target import file for configuration "Debug".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "cellml" for configuration "Debug"
set_property(TARGET cellml APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(cellml PROPERTIES
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/libcellmld.0.2.0.dylib"
  IMPORTED_SONAME_DEBUG "@rpath/libcellmld.0.2.0.dylib"
  )

list(APPEND _IMPORT_CHECK_TARGETS cellml )
list(APPEND _IMPORT_CHECK_FILES_FOR_cellml "${_IMPORT_PREFIX}/lib/libcellmld.0.2.0.dylib" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)


# Make the SWIG generated Python interface modules more portable by using rpath for the the Python dynamic library.
string(REPLACE "${LIST_SEPARATOR}" ";" SHARED_OBJECT_MODULES "${SHARED_OBJECT_MODULES}")
foreach(_M ${SHARED_OBJECT_MODULES})
  execute_process(COMMAND ${INSTALL_NAME_TOOL_EXE} -change "/Library/Frameworks/Python.framework/Versions/${Python_VERSION_MAJOR}.${Python_VERSION_MINOR}/Python" @rpath/${Python_VERSION_MAJOR}.${Python_VERSION_MINOR}/Python ${_M})
endforeach()


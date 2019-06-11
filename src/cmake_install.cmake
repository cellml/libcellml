# Install script for directory: /Users/kmoy001/libCellML/src

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Debug")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES "/Users/kmoy001/libCellML/src/libcellmld.0.2.0.dylib")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libcellmld.0.2.0.dylib" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libcellmld.0.2.0.dylib")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/Library/Developer/CommandLineTools/usr/bin/strip" -x "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libcellmld.0.2.0.dylib")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES "/Users/kmoy001/libCellML/src/libcellmld.dylib")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libcellmld.dylib" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libcellmld.dylib")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/Library/Developer/CommandLineTools/usr/bin/strip" -x "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libcellmld.dylib")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/libcellml" TYPE FILE FILES
    "/Users/kmoy001/libCellML/src/api/libcellml/component.h"
    "/Users/kmoy001/libCellML/src/api/libcellml/componententity.h"
    "/Users/kmoy001/libCellML/src/api/libcellml/entity.h"
    "/Users/kmoy001/libCellML/src/api/libcellml/enumerations.h"
    "/Users/kmoy001/libCellML/src/api/libcellml/error.h"
    "/Users/kmoy001/libCellML/src/api/libcellml/importedentity.h"
    "/Users/kmoy001/libCellML/src/api/libcellml/importsource.h"
    "/Users/kmoy001/libCellML/src/api/libcellml/logger.h"
    "/Users/kmoy001/libCellML/src/api/libcellml/model.h"
    "/Users/kmoy001/libCellML/src/api/libcellml/namedentity.h"
    "/Users/kmoy001/libCellML/src/api/libcellml/orderedentity.h"
    "/Users/kmoy001/libCellML/src/api/libcellml/parser.h"
    "/Users/kmoy001/libCellML/src/api/libcellml/printer.h"
    "/Users/kmoy001/libCellML/src/api/libcellml/reset.h"
    "/Users/kmoy001/libCellML/src/api/libcellml/specificationrules.h"
    "/Users/kmoy001/libCellML/src/api/libcellml/types.h"
    "/Users/kmoy001/libCellML/src/api/libcellml/units.h"
    "/Users/kmoy001/libCellML/src/api/libcellml/validator.h"
    "/Users/kmoy001/libCellML/src/api/libcellml/variable.h"
    "/Users/kmoy001/libCellML/src/api/libcellml/version.h"
    "/Users/kmoy001/libCellML/src/api/libcellml/when.h"
    "/Users/kmoy001/libCellML/src/api/libcellml/exportdefinitions.h"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/libcellml/module" TYPE FILE FILES "/Users/kmoy001/libCellML/src/api/libcellml/module/libcellml")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/libcellml-targets.cmake")
    file(DIFFERENT EXPORT_FILE_CHANGED FILES
         "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/libcellml-targets.cmake"
         "/Users/kmoy001/libCellML/src/CMakeFiles/Export/lib/cmake/libcellml-targets.cmake")
    if(EXPORT_FILE_CHANGED)
      file(GLOB OLD_CONFIG_FILES "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/libcellml-targets-*.cmake")
      if(OLD_CONFIG_FILES)
        message(STATUS "Old export file \"$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/libcellml-targets.cmake\" will be replaced.  Removing files [${OLD_CONFIG_FILES}].")
        file(REMOVE ${OLD_CONFIG_FILES})
      endif()
    endif()
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake" TYPE FILE FILES "/Users/kmoy001/libCellML/src/CMakeFiles/Export/lib/cmake/libcellml-targets.cmake")
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake" TYPE FILE FILES "/Users/kmoy001/libCellML/src/CMakeFiles/Export/lib/cmake/libcellml-targets-debug.cmake")
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xDevelx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake" TYPE FILE FILES
    "/Users/kmoy001/libCellML/libcellml-config.cmake"
    "/Users/kmoy001/libCellML/libcellml-config-version.cmake"
    )
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("/Users/kmoy001/libCellML/src/bindings/cmake_install.cmake")

endif()



set(SOURCE_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/component.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/componententity.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/entity.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/importedentity.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/importsource.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/issue.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/logger.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/model.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/namedentity.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/parser.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/printer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/reset.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/units.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/validator.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/variable.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/version.cpp
)

add_executable(libcellml ${SOURCE_FILES})

target_link_libraries(libcellml PRIVATE cellml)

set_target_properties(libcellml PROPERTIES
  CXX_STANDARD 11
  CXX_STANDARD_REQUIRED ON
  CXX_VISIBILITY_PRESET hidden
  VISIBILITY_INLINES_HIDDEN 1
  LINK_FLAGS "--bind -s 'EXPORT_NAME=\"libCellML\"' -s EXPORT_ES6=1 -s MODULARIZE=1 -s USE_ES6_IMPORT_META=0"
  COMPILE_FLAGS "-s ASSERTIONS=1"
)

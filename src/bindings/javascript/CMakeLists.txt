
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

add_library(javascript-bindings OBJECT ${SOURCE_FILES})

target_link_libraries(javascript-bindings PUBLIC cellml)

set_target_properties(javascript-bindings PROPERTIES
  CXX_STANDARD 11
  CXX_STANDARD_REQUIRED ON
  CXX_VISIBILITY_PRESET hidden
  VISIBILITY_INLINES_HIDDEN 1
  COMPILE_FLAGS "-s ASSERTIONS=1"
)

add_executable(libcellml $<TARGET_OBJECTS:javascript-bindings>)

target_link_libraries(libcellml PUBLIC javascript-bindings)

set_target_properties(libcellml PROPERTIES
  LINK_FLAGS "--bind -s 'EXPORT_NAME=\"libCellML\"' -s EXPORT_ES6=1 -s MODULARIZE=1 -s USE_ES6_IMPORT_META=0  -s ALLOW_MEMORY_GROWTH=1"
)

add_executable(libcellml.common $<TARGET_OBJECTS:javascript-bindings>)

target_link_libraries(libcellml.common PUBLIC javascript-bindings)

set_target_properties(libcellml.common PROPERTIES
  LINK_FLAGS "--bind -s 'EXPORT_NAME=\"libCellML\"' -s MODULARIZE=1 -s ALLOW_MEMORY_GROWTH=1"
)

set(_PACKAGE_JSON "\{
  \"name\": \"libcellml.js\",
  \"version\": \"${PROJECT_VERSION}\",
  \"description\": \"libcellml.js javascript web assembly for libCellML.\",
  \"main\": \"libcellml.js\",
  \"files\": [\"libcellml.common.js\", \"libcellml.common.wasm\", \"libcellml.js\", \"libcellml.wasm\"],
  \"author\": \"libCellML Developers <developers@libcellml.org>\",
  \"repository\": \"https://github.com/cellml/libcellml\",
  \"license\": \"Apache-2.0\"
}
")

file(WRITE "${CMAKE_CURRENT_BINARY_DIR}/package.json" "${_PACKAGE_JSON}")

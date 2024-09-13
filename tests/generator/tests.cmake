set(CURRENT_TEST generator)
set(${CURRENT_TEST}_CATEGORY io)

list(APPEND LIBCELLML_TESTS ${CURRENT_TEST})

set(${CURRENT_TEST}_SRCS
  ${CMAKE_CURRENT_LIST_DIR}/generator.cpp
  ${CMAKE_CURRENT_LIST_DIR}/generatorprofile.cpp
)

set(${CURRENT_TEST}_HDRS
  ${CMAKE_CURRENT_LIST_DIR}/generator.macros.h
  ${CMAKE_CURRENT_LIST_DIR}/generator.models.h
)

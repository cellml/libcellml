
#include <emscripten/bind.h>

#include "libcellml/enums.h"

using namespace emscripten;


EMSCRIPTEN_BINDINGS(libcellml_enums) {
    enum_<libcellml::CellmlElementType>("CellmlElementType")
        .value("COMPONENT", libcellml::CellmlElementType::COMPONENT)
        .value("COMPONENT_REF", libcellml::CellmlElementType::COMPONENT_REF)
        .value("CONNECTION", libcellml::CellmlElementType::CONNECTION)
        .value("ENCAPSULATION", libcellml::CellmlElementType::ENCAPSULATION)
        .value("IMPORT", libcellml::CellmlElementType::IMPORT)
        .value("MAP_VARIABLES", libcellml::CellmlElementType::MAP_VARIABLES)
        .value("MATH", libcellml::CellmlElementType::MATH)
        .value("MODEL", libcellml::CellmlElementType::MODEL)
        .value("RESET", libcellml::CellmlElementType::RESET)
        .value("RESET_VALUE", libcellml::CellmlElementType::RESET_VALUE)
        .value("TEST_VALUE", libcellml::CellmlElementType::TEST_VALUE)
        .value("UNDEFINED", libcellml::CellmlElementType::UNDEFINED)
        .value("UNIT", libcellml::CellmlElementType::UNIT)
        .value("UNITS", libcellml::CellmlElementType::UNITS)
        .value("VARIABLE", libcellml::CellmlElementType::VARIABLE)
    ;

    function("cellmlElementTypeAsString", &libcellml::cellmlElementTypeAsString);
}

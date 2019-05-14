
#include <emscripten/bind.h>

#include "libcellml/enumerations.h"

using namespace emscripten;


EMSCRIPTEN_BINDINGS(libcellml_enumerations) {
    enum_<libcellml::Prefix>("Prefix")
        .value("ATTO", libcellml::Prefix::ATTO)
        .value("CENTI", libcellml::Prefix::CENTI)
        .value("DECA", libcellml::Prefix::DECA)
        .value("DECI", libcellml::Prefix::DECI)
        .value("EXA", libcellml::Prefix::EXA)
        .value("FEMTO", libcellml::Prefix::FEMTO)
        .value("GIGA", libcellml::Prefix::GIGA)
        .value("HECTO", libcellml::Prefix::HECTO)
        .value("KILO", libcellml::Prefix::KILO)
        .value("MEGA", libcellml::Prefix::MEGA)
        .value("MICRO", libcellml::Prefix::MICRO)
        .value("MILLI", libcellml::Prefix::MILLI)
        .value("NANO", libcellml::Prefix::NANO)
        .value("PETA", libcellml::Prefix::PETA)
        .value("PICO", libcellml::Prefix::PICO)
        .value("TERA", libcellml::Prefix::TERA)
        .value("YOCTO", libcellml::Prefix::YOCTO)
        .value("YOTTA", libcellml::Prefix::YOTTA)
        .value("ZEPTO", libcellml::Prefix::ZEPTO)
        .value("ZETTA", libcellml::Prefix::ZETTA)
    ;
}

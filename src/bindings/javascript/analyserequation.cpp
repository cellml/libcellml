#include <emscripten/bind.h>
#include <emscripten/emscripten.h>

#include "libcellml/analyserequation.h"

using namespace emscripten;

EMSCRIPTEN_BINDINGS(libcellml_analyserequation)
{
    enum_<libcellml::AnalyserEquation::Type>("AnalyserEquation.Type")
        .value("TRUE_CONSTANT", libcellml::AnalyserEquation::Type::TRUE_CONSTANT)
        .value("VARIABLE_BASED_CONSTANT", libcellml::AnalyserEquation::Type::VARIABLE_BASED_CONSTANT)
        .value("RATE", libcellml::AnalyserEquation::Type::RATE)
        .value("ALGEBRAIC", libcellml::AnalyserEquation::Type::ALGEBRAIC)
        .value("EXTERNAL", libcellml::AnalyserEquation::Type::EXTERNAL)
    ;

    class_<libcellml::AnalyserEquation>("AnalyserEquation")
        .smart_ptr<std::shared_ptr<libcellml::AnalyserEquation>>("AnalyserEquation")
        .function("type", &libcellml::AnalyserEquation::type)
        .function("ast", &libcellml::AnalyserEquation::ast)
        .function("dependencies", &libcellml::AnalyserEquation::dependencies)
        .function("isStateRateBased", &libcellml::AnalyserEquation::isStateRateBased)
        .function("variable", &libcellml::AnalyserEquation::variable)
    ;

    EM_ASM(
        Module['AnalyserEquation']['Type'] = Module['AnalyserEquation.Type'];
        delete Module['AnalyserEquation.Type'];
    );
}

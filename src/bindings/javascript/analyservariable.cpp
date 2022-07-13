
#include <emscripten/bind.h>
#include <emscripten/emscripten.h>

#include "libcellml/analyservariable.h"

using namespace emscripten;

EMSCRIPTEN_BINDINGS(libcellml_analyservariable)
{
    enum_<libcellml::AnalyserVariable::Type>("AnalyserVariable.Type")
        .value("VARIABLE_OF_INTEGRATION", libcellml::AnalyserVariable::Type::VARIABLE_OF_INTEGRATION)
        .value("STATE", libcellml::AnalyserVariable::Type::STATE)
        .value("CONSTANT", libcellml::AnalyserVariable::Type::CONSTANT)
        .value("COMPUTED_CONSTANT", libcellml::AnalyserVariable::Type::COMPUTED_CONSTANT)
        .value("ALGEBRAIC", libcellml::AnalyserVariable::Type::ALGEBRAIC)
        .value("EXTERNAL", libcellml::AnalyserVariable::Type::EXTERNAL)
    ;

    class_<libcellml::AnalyserVariable>("AnalyserVariable")
        .smart_ptr<std::shared_ptr<libcellml::AnalyserVariable>>("AnalyserVariable")
        .function("type", &libcellml::AnalyserVariable::type)
        .function("index", &libcellml::AnalyserVariable::index)
        .function("initialisingVariable", &libcellml::AnalyserVariable::initialisingVariable)
        .function("variable", &libcellml::AnalyserVariable::variable)
        .function("equation", &libcellml::AnalyserVariable::equation)
    ;

    EM_ASM(
        Module['AnalyserVariable']['Type'] = Module['AnalyserVariable.Type'];
        delete Module['AnalyserVariable.Type'];
    );

}

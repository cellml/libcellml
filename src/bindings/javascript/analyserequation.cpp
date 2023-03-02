/*
Copyright libCellML Contributors

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/

#include <emscripten/bind.h>
#include <emscripten/emscripten.h>

#include "libcellml/analyserequation.h"

using namespace emscripten;

EMSCRIPTEN_BINDINGS(libcellml_analyserequation)
{
    enum_<libcellml::AnalyserEquation::Type>("AnalyserEquation.Type")
        .value("TRUE_CONSTANT", libcellml::AnalyserEquation::Type::TRUE_CONSTANT)
        .value("VARIABLE_BASED_CONSTANT", libcellml::AnalyserEquation::Type::VARIABLE_BASED_CONSTANT)
        .value("ODE", libcellml::AnalyserEquation::Type::ODE)
        .value("NLA", libcellml::AnalyserEquation::Type::NLA)
        .value("ALGEBRAIC", libcellml::AnalyserEquation::Type::ALGEBRAIC)
        .value("EXTERNAL", libcellml::AnalyserEquation::Type::EXTERNAL)
    ;

    class_<libcellml::AnalyserEquation>("AnalyserEquation")
        .smart_ptr<std::shared_ptr<libcellml::AnalyserEquation>>("AnalyserEquation")
        .function("type", &libcellml::AnalyserEquation::type)
        .class_function("typeAsString", &libcellml::AnalyserEquation::typeAsString)
        .function("ast", &libcellml::AnalyserEquation::ast)
        .function("dependencyCount", &libcellml::AnalyserEquation::dependencyCount)
        .function("dependencies", &libcellml::AnalyserEquation::dependencies)
        .function("dependency", &libcellml::AnalyserEquation::dependency)
        .function("isStateRateBased", &libcellml::AnalyserEquation::isStateRateBased)
        .function("variableCount", &libcellml::AnalyserEquation::variableCount)
        .function("variables", &libcellml::AnalyserEquation::variables)
        .function("variable", &libcellml::AnalyserEquation::variable)
    ;

    EM_ASM(
        Module['AnalyserEquation']['Type'] = Module['AnalyserEquation.Type'];
        delete Module['AnalyserEquation.Type'];
    );
}

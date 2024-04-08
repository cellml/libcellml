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

#include "libcellml/interpreter.h"

using namespace emscripten;

EMSCRIPTEN_BINDINGS(libcellml_interpreter)
{
    class_<libcellml::Interpreter>("Interpreter")
        .smart_ptr_constructor("Interpreter", &libcellml::Interpreter::create)
        .function("model", &libcellml::Interpreter::model)
        .function("setModel", &libcellml::Interpreter::setModel)
        .function("initialiseVariables", &libcellml::Interpreter::initialiseVariables)
        .function("computeComputedConstants", &libcellml::Interpreter::computeComputedConstants)
        .function("computeRates", &libcellml::Interpreter::computeRates)
        .function("computeVariables", &libcellml::Interpreter::computeVariables)
    ;
}
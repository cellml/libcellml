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

#include "libcellml/generatorcontext.h"

using namespace emscripten;

EMSCRIPTEN_BINDINGS(libcellml_generatorcontext)
{
    class_<libcellml::GeneratorContext, base<libcellml::Logger>>("GeneratorContext")
        .smart_ptr_constructor("GeneratorContext", &libcellml::GeneratorContext::create)
        .function("isTrackedVariable", &libcellml::GeneratorContext::isTrackedVariable)
        .function("isUntrackedVariable", &libcellml::GeneratorContext::isUntrackedVariable)
        .function("trackVariable", &libcellml::GeneratorContext::trackVariable)
        .function("untrackVariable", &libcellml::GeneratorContext::untrackVariable)
        .function("trackAllConstants", &libcellml::GeneratorContext::trackAllConstants)
        .function("untrackAllConstants", &libcellml::GeneratorContext::untrackAllConstants)
        .function("trackAllComputedConstants", &libcellml::GeneratorContext::trackAllComputedConstants)
        .function("untrackAllComputedConstants", &libcellml::GeneratorContext::untrackAllComputedConstants)
        .function("trackAllAlgebraicVariables", &libcellml::GeneratorContext::trackAllAlgebraicVariables)
        .function("untrackAllAlgebraicVariables", &libcellml::GeneratorContext::untrackAllAlgebraicVariables)
        .function("trackAllVariables", &libcellml::GeneratorContext::trackAllVariables)
        .function("untrackAllVariables", &libcellml::GeneratorContext::untrackAllVariables)
        .function("trackedConstantCount", &libcellml::GeneratorContext::trackedConstantCount)
        .function("untrackedConstantCount", &libcellml::GeneratorContext::untrackedConstantCount)
        .function("trackedComputedConstantCount", &libcellml::GeneratorContext::trackedComputedConstantCount)
        .function("untrackedComputedConstantCount", &libcellml::GeneratorContext::untrackedComputedConstantCount)
        .function("trackedAlgebraicCount", &libcellml::GeneratorContext::trackedAlgebraicCount)
        .function("untrackedAlgebraicCount", &libcellml::GeneratorContext::untrackedAlgebraicCount)
        .function("trackedVariableCount", &libcellml::GeneratorContext::trackedVariableCount)
        .function("untrackedVariableCount", &libcellml::GeneratorContext::untrackedVariableCount)
    ;
}

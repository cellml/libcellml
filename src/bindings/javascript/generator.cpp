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

#include "libcellml/analyserequationast.h"
#include "libcellml/generator.h"
#include "libcellml/generatorprofile.h"

using namespace emscripten;

EMSCRIPTEN_BINDINGS(libcellml_generator)
{
    class_<libcellml::Generator>("Generator")
        .smart_ptr_constructor("Generator", &libcellml::Generator::create)
        .function("profile", &libcellml::Generator::profile)
        .function("setProfile", &libcellml::Generator::setProfile)
        .function("isTrackedVariable", &libcellml::Generator::isTrackedVariable)
        .function("isUntrackedVariable", &libcellml::Generator::isUntrackedVariable)
        .function("trackVariable", &libcellml::Generator::trackVariable)
        .function("untrackVariable", &libcellml::Generator::untrackVariable)
        .function("trackAllConstants", &libcellml::Generator::trackAllConstants)
        .function("untrackAllConstants", &libcellml::Generator::untrackAllConstants)
        .function("trackAllComputedConstants", &libcellml::Generator::trackAllComputedConstants)
        .function("untrackAllComputedConstants", &libcellml::Generator::untrackAllComputedConstants)
        .function("trackAllAlgebraic", &libcellml::Generator::trackAllAlgebraic)
        .function("untrackAllAlgebraic", &libcellml::Generator::untrackAllAlgebraic)
        .function("trackAllVariables", &libcellml::Generator::trackAllVariables)
        .function("untrackAllVariables", &libcellml::Generator::untrackAllVariables)
        .function("trackedConstantCount", &libcellml::Generator::trackedConstantCount)
        .function("untrackedConstantCount", &libcellml::Generator::untrackedConstantCount)
        .function("trackedComputedConstantCount", &libcellml::Generator::trackedComputedConstantCount)
        .function("untrackedComputedConstantCount", &libcellml::Generator::untrackedComputedConstantCount)
        .function("trackedAlgebraicCount", &libcellml::Generator::trackedAlgebraicCount)
        .function("untrackedAlgebraicCount", &libcellml::Generator::untrackedAlgebraicCount)
        .function("trackedExternalCount", &libcellml::Generator::trackedExternalCount)
        .function("untrackedExternalCount", &libcellml::Generator::untrackedExternalCount)
        .function("trackedVariableCount", &libcellml::Generator::trackedVariableCount)
        .function("untrackedVariableCount", &libcellml::Generator::untrackedVariableCount)
        .function("interfaceCode", &libcellml::Generator::interfaceCode)
        .function("implementationCode", &libcellml::Generator::implementationCode)
        .class_function("equationCode", select_overload<std::string(const libcellml::AnalyserEquationAstPtr &)>(&libcellml::Generator::equationCode))
        .class_function("equationCodeByProfile", select_overload<std::string(const libcellml::AnalyserEquationAstPtr &, const libcellml::GeneratorProfilePtr &)>(&libcellml::Generator::equationCode))
    ;
}

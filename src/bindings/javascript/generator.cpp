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
#include "libcellml/generatorcontext.h"
#include "libcellml/generatorprofile.h"

using namespace emscripten;

EMSCRIPTEN_BINDINGS(libcellml_generator)
{
    class_<libcellml::Generator, base<libcellml::Logger>>("Generator")
        .smart_ptr_constructor("Generator", &libcellml::Generator::create)
        .function("context", &libcellml::Generator::context)
        .function("setContext", &libcellml::Generator::setContext)
        .function("profile", &libcellml::Generator::profile)
        .function("setProfile", &libcellml::Generator::setProfile)
        .function("isTrackedVariable", &libcellml::Generator::isTrackedVariable) //---GRY--- TO BE DELETED.
        .function("isUntrackedVariable", &libcellml::Generator::isUntrackedVariable) //---GRY--- TO BE DELETED.
        .function("trackVariable", &libcellml::Generator::trackVariable) //---GRY--- TO BE DELETED.
        .function("untrackVariable", &libcellml::Generator::untrackVariable) //---GRY--- TO BE DELETED.
        .function("trackAllConstants", &libcellml::Generator::trackAllConstants) //---GRY--- TO BE DELETED.
        .function("untrackAllConstants", &libcellml::Generator::untrackAllConstants) //---GRY--- TO BE DELETED.
        .function("trackAllComputedConstants", &libcellml::Generator::trackAllComputedConstants) //---GRY--- TO BE DELETED.
        .function("untrackAllComputedConstants", &libcellml::Generator::untrackAllComputedConstants) //---GRY--- TO BE DELETED.
        .function("trackAllAlgebraicVariables", &libcellml::Generator::trackAllAlgebraicVariables) //---GRY--- TO BE DELETED.
        .function("untrackAllAlgebraicVariables", &libcellml::Generator::untrackAllAlgebraicVariables) //---GRY--- TO BE DELETED.
        .function("trackAllVariables", &libcellml::Generator::trackAllVariables) //---GRY--- TO BE DELETED.
        .function("untrackAllVariables", &libcellml::Generator::untrackAllVariables) //---GRY--- TO BE DELETED.
        .function("trackedConstantCount", &libcellml::Generator::trackedConstantCount) //---GRY--- TO BE DELETED.
        .function("untrackedConstantCount", &libcellml::Generator::untrackedConstantCount) //---GRY--- TO BE DELETED.
        .function("trackedComputedConstantCount", &libcellml::Generator::trackedComputedConstantCount) //---GRY--- TO BE DELETED.
        .function("untrackedComputedConstantCount", &libcellml::Generator::untrackedComputedConstantCount) //---GRY--- TO BE DELETED.
        .function("trackedAlgebraicCount", &libcellml::Generator::trackedAlgebraicCount) //---GRY--- TO BE DELETED.
        .function("untrackedAlgebraicCount", &libcellml::Generator::untrackedAlgebraicCount) //---GRY--- TO BE DELETED.
        .function("trackedVariableCount", &libcellml::Generator::trackedVariableCount) //---GRY--- TO BE DELETED.
        .function("untrackedVariableCount", &libcellml::Generator::untrackedVariableCount) //---GRY--- TO BE DELETED.
        .function("interfaceCode", &libcellml::Generator::interfaceCode)
        .function("implementationCode", &libcellml::Generator::implementationCode)
        .class_function("equationCode", select_overload<std::string(const libcellml::AnalyserEquationAstPtr &)>(&libcellml::Generator::equationCode))
        .class_function("equationCodeByProfile", select_overload<std::string(const libcellml::AnalyserEquationAstPtr &, const libcellml::GeneratorProfilePtr &)>(&libcellml::Generator::equationCode))
    ;
}

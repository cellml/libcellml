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

#include "libcellml/generator.h"

using namespace emscripten;

EMSCRIPTEN_BINDINGS(libcellml_generator)
{
    class_<libcellml::Generator>("Generator")
        .smart_ptr_constructor("Generator", &libcellml::Generator::create)
        .function("profile", &libcellml::Generator::profile)
        .function("setProfile", &libcellml::Generator::setProfile)
        .function("model", &libcellml::Generator::model)
        .function("setModel", &libcellml::Generator::setModel)
        .function("interfaceCode", &libcellml::Generator::interfaceCode)
        .function("implementationCode", &libcellml::Generator::implementationCode)
    ;
}

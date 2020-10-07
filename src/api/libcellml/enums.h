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

#pragma once

#include <memory>

namespace libcellml {

/**
 * @brief The CellMLReferenceType enum class.
 *
 */
enum class CellMLReferenceType
{
    COMPONENT,
    COMPONENT_REF,
    CONNECTION,
    ENCAPSULATION,
    IMPORT,
    MAP_VARIABLES,
    MATHML,
    MODEL,
    RESET,
    RESET_VALUE,
    TEST_VALUE,
    UNDEFINED,
    UNIT,
    UNITS,
    VARIABLE,
};

} // namespace libcellml

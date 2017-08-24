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

namespace libcellml {

/**
 * @brief The SpecificationRule enum class.
 *
 * Enum describing the specification rules that are used
 * for validation. 
 */
enum class SpecificationRule
{
    UNDEFINED,
    MODEL_ELEMENT,
    MODEL_NAME,
    MODEL_CHILD,
    IMPORT_HREF,
    IMPORT_CHILD,
    IMPORT_CIRCULAR,
    IMPORT_UNITS_NAME,
    IMPORT_UNITS_REF,
    IMPORT_COMPONENT_NAME,
    IMPORT_COMPONENT_REF,
    UNITS_NAME,
    UNITS_MODEL_UNIQUE,
    UNITS_COMPONENT_UNIQUE,
    UNITS_STANDARD,
    UNITS_BASE,
    UNITS_CHILD,
    UNIT_UNITS_REF,
    UNIT_DIGRAPH,
    UNIT_CIRCULAR_REF,
    UNIT_ATTRIBUTE,
    UNIT_PREFIX,
    UNIT_MULTIPLIER,
    UNIT_EXPONENT,
    COMPONENT_NAME,
    COMPONENT_CHILD,
    VARIABLE_ATTRIBUTE,
    VARIABLE_NAME,
    VARIABLE_UNITS,
    VARIABLE_INTERFACE,
    VARIABLE_INITIAL_VALUE,
    ENCAPSULATION_COMPONENT_REF,
    COMPONENT_REF_COMPONENT,
    COMPONENT_REF_CHILD,
    ENCAPSULATION_COMPONENT_REF_CHILD,
    CONNECTION_CHILD,
    CONNECTION_MAP_COMPONENTS,
    CONNECTION_MAP_VARIABLES,
    MAP_COMPONENTS_COMPONENT1,
    MAP_COMPONENTS_COMPONENT2,
    MAP_VARIABLES_VARIABLE1,
    MAP_VARIABLES_VARIABLE2
};

}

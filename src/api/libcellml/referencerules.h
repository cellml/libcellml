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
 * @brief The ReferenceRule enum class.
 *
 * Enum describing the specification rules that are used
 * for validation.
 */
enum class ReferenceRule
{
    UNDEFINED,
    // Specification errors.
    DATA_REPR_IDENTIFIER_UNICODE,
    DATA_REPR_IDENTIFIER_LATIN_ALPHANUM,
    DATA_REPR_IDENTIFIER_AT_LEAST_ONE_ALPHANUM,
    DATA_REPR_IDENTIFIER_BEGIN_EURO_NUM,
    DATA_REPR_IDENTIFIER_IDENTICAL,
    DATA_REPR_NNEG_INT_BASE10,
    DATA_REPR_NNEG_INT_EURO_NUM,
    MODEL_ELEMENT,
    MODEL_NAME,
    MODEL_CHILD,
    MODEL_MORE_THAN_ONE_ENCAPSULATION,
    IMPORT_HREF,
    IMPORT_CHILD,
    IMPORT_CIRCULAR,
    IMPORT_UNITS_NAME,
    IMPORT_UNITS_REF,
    IMPORT_COMPONENT_NAME,
    IMPORT_COMPONENT_REF,
    UNITS_NAME,
    UNITS_NAME_UNIQUE,
    UNITS_STANDARD,
    UNITS_CHILD,
    UNIT_UNITS_REF,
    UNIT_DIGRAPH,
    UNIT_CIRCULAR_REF,
    UNIT_OPTIONAL_ATTRIBUTE,
    UNIT_PREFIX,
    UNIT_MULTIPLIER,
    UNIT_EXPONENT,
    COMPONENT_NAME,
    COMPONENT_CHILD,
    VARIABLE_NAME,
    VARIABLE_UNITS,
    VARIABLE_INTERFACE,
    VARIABLE_INITIAL_VALUE,
    RESET_CHILD,
    RESET_ORDER,
    RESET_VARIABLE_REFERENCE,
    RESET_TEST_VARIABLE_REFERENCE,
    RESET_TEST_VALUE,
    RESET_RESET_VALUE,
    MATH_MATHML,
    MATH_CHILD,
    MATH_CI_VARIABLE_REFERENCE,
    MATH_CN_UNITS_ATTRIBUTE,
    ENCAPSULATION_COMPONENT_REF,
    COMPONENT_REF_COMPONENT_ATTRIBUTE,
    COMPONENT_REF_CHILD,
    COMPONENT_REF_ENCAPSULATION,
    CONNECTION_COMPONENT1,
    CONNECTION_COMPONENT2,
    CONNECTION_UNIQUE_TRANSITIVE,
    CONNECTION_MAP_VARIABLES,
    MAP_VARIABLES_VARIABLE1,
    MAP_VARIABLES_VARIABLE2,
    MAP_VARIABLES_UNIQUE
    // Code generation errors go here ... TODO
};

} // namespace libcellml

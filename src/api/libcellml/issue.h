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

#include <string>

#include "libcellml/exportdefinitions.h"
#include "libcellml/types.h"

namespace libcellml {

/**
 * @brief The Issue class
 *
 * Base class for issues used with logger derived classes.
 */
class LIBCELLML_EXPORT Issue
{
    friend class Analyser;
    friend class Annotator;
    friend class Importer;
    friend class Parser;
    friend class Validator;

public:
    virtual ~Issue(); /**< Destructor, @private. */
    Issue(const Issue &rhs) = delete; /**< Copy constructor, @private. */
    Issue(Issue &&rhs) noexcept = delete; /**< Move constructor, @private. */
    Issue &operator=(Issue rhs) = delete; /**< Assignment operator, @private. */

    /**
     * @brief The issue Level enum class.
     *
     * Enum to describe the level of severity that a given issue has.
     */
    enum class Level
    {
        ERROR,
        WARNING,
        MESSAGE
    };

    /**
     * @brief The issue Reference enum class.
     *
     * Enum to describe the rule which the issue addresses.
     */
    enum class ReferenceRule
    {
        UNDEFINED,

        // Specification errors.
        XML,
        XML_ID_ATTRIBUTE,
        DATA_REPR_IDENTIFIER_UNICODE,
        DATA_REPR_IDENTIFIER_LATIN_ALPHANUM,
        DATA_REPR_IDENTIFIER_AT_LEAST_ONE_ALPHANUM,
        DATA_REPR_IDENTIFIER_BEGIN_EURO_NUM,
        DATA_REPR_IDENTIFIER_IDENTICAL,
        DATA_REPR_INT_BASE10,
        DATA_REPR_INT_SIGN,
        DATA_REPR_INT_DIGIT,
        DATA_REPR_BASIC_REAL_BASE10,
        DATA_REPR_BASIC_REAL_SIGN,
        DATA_REPR_BASIC_REAL_DECIMAL,
        DATA_REPR_BASIC_REAL_DIGIT,
        DATA_REPR_REAL_BASE10,
        DATA_REPR_REAL_SIGNIFICAND,
        DATA_REPR_REAL_EXPONENT,
        MODEL_ELEMENT,
        MODEL_NAME,
        MODEL_CHILD,
        MODEL_MORE_THAN_ONE_ENCAPSULATION,
        IMPORT_ATTRIBUTE,
        IMPORT_HREF,
        IMPORT_CHILD,
        IMPORT_EQUIVALENT,
        IMPORT_UNITS_NAME,
        IMPORT_UNITS_NAME_UNIQUE,
        IMPORT_UNITS_REF,
        IMPORT_COMPONENT_NAME,
        IMPORT_COMPONENT_NAME_UNIQUE,
        IMPORT_COMPONENT_COMPONENT_REF,
        UNITS_ATTRIBUTE,
        UNITS_NAME,
        UNITS_NAME_UNIQUE,
        UNITS_STANDARD,
        UNITS_CHILD,
        UNIT_ATTRIBUTE,
        UNIT_UNITS_REF,
        UNIT_CIRCULAR_REF,
        UNIT_OPTIONAL_ATTRIBUTE,
        UNIT_PREFIX,
        UNIT_MULTIPLIER,
        UNIT_EXPONENT,
        COMPONENT_ATTRIBUTE,
        COMPONENT_NAME,
        COMPONENT_NAME_UNIQUE,
        COMPONENT_CHILD,
        VARIABLE_ATTRIBUTE,
        VARIABLE_CHILD,
        VARIABLE_NAME,
        VARIABLE_NAME_UNIQUE,
        VARIABLE_UNITS,
        VARIABLE_INTERFACE,
        VARIABLE_INITIAL_VALUE,
        RESET_ATTRIBUTE,
        RESET_VARIABLE_REF,
        RESET_TEST_VARIABLE_REF,
        RESET_ORDER,
        RESET_CHILD,
        RESET_TEST_VALUE,
        RESET_RESET_VALUE,
        MATH_MATHML,
        MATH_CHILD,
        MATH_CI_VARIABLE_REF,
        MATH_CN_UNITS,
        MATH_CN_BASE10,
        MATH_CN_FORMAT,
        ENCAPSULATION_ATTRIBUTE,
        ENCAPSULATION_CHILD,
        COMPONENT_REF_COMPONENT,
        COMPONENT_REF_CHILD,
        CONNECTION_ATTRIBUTE,
        CONNECTION_COMPONENT1,
        CONNECTION_COMPONENT2,
        CONNECTION_EXCLUDE_SELF,
        CONNECTION_UNIQUE,
        CONNECTION_CHILD,
        MAP_VARIABLES_ATTRIBUTE,
        MAP_VARIABLES_VARIABLE1,
        MAP_VARIABLES_VARIABLE2,
        MAP_VARIABLES_UNIQUE,
        MAP_VARIABLES_AVAILABLE_INTERFACE,

        // Issues not present in the normative specification:
        MAP_VARIABLES_IDENTICAL_UNIT_REDUCTION,
        INVALID_ARGUMENT,

        // Importer class issues:
        IMPORTER_ERROR_IMPORTING_UNITS,
        IMPORTER_MISSING_FILE,
        IMPORTER_MISSING_COMPONENT,
        IMPORTER_MISSING_UNITS,
        IMPORTER_NULL_MODEL,

        // Analyser issues:
        ANALYSER_UNITS,
        ANALYSER_UNLINKED_UNITS,
        ANALYSER_VARIABLE_INITIALISED_MORE_THAN_ONCE,
        ANALYSER_VARIABLE_NON_CONSTANT_INITIALISATION,
        ANALYSER_VOI_INITIALISED,
        ANALYSER_VOI_SEVERAL,
        ANALYSER_ODE_NOT_FIRST_ORDER,
        ANALYSER_VARIABLE_UNUSED,
        ANALYSER_STATE_NOT_INITIALISED,
        ANALYSER_VARIABLE_COMPUTED_MORE_THAN_ONCE,
        ANALYSER_EXTERNAL_VARIABLE_DIFFERENT_MODEL,
        ANALYSER_EXTERNAL_VARIABLE_VOI,
        ANALYSER_EXTERNAL_VARIABLE_USE_PRIMARY_VARIABLE,

        // Annotator issues:
        ANNOTATOR_ID_NOT_FOUND,
        ANNOTATOR_ID_NOT_UNIQUE,
        ANNOTATOR_NO_MODEL,
        ANNOTATOR_INCONSISTENT_TYPE,
        ANNOTATOR_NULL_MODEL,

        // Placeholder for further references:
        UNSPECIFIED
    };

    /**
     * @brief Get the description for this issue.
     *
     * Get the @c std::string description for why this issue was raised.
     *
     * @return The @c std::string description of the issue.
     */
    std::string description() const;

    /**
     * @brief Get the level of this issue.
     *
     * Get the @c Issue::Level of this issue. If no level has been set for
     * this issue, will return Level::ERROR.
     *
     * @return The @c Issue::Level set for this issue.
     */
    Level level() const;

    /**
     * @brief Get the @c enum ReferenceRule of this issue.
     *
     * Get the @c enum @c ReferenceRule value of this issue. If no reference
     * rule has been set for this issue, return ReferenceRule::UNDEFINED.
     *
     * @return The @c ReferenceRule for this issue.
     */
    ReferenceRule referenceRule() const;

    /**
     * @brief Get the item for this issue.
     *
     * Get the item for this issue as an @ref AnyCellmlElementPtr.
     *
     * @return The @ref AnyCellmlElementPtr for this issue.
     */
    AnyCellmlElementPtr item() const;

    /**
     * @brief Get the @c url of this issue.
     *
     * Get the @c url to which the user should refer for more information on this issue.
     *
     * @return The @c url for this issue.
     */
    std::string url() const;

    /**
     * @brief Get the @c std::string heading associated with the @c enum ReferenceRule for this issue.
     *
     * Get the @c std::string libCellML Reference heading associated with the @c enum ReferenceRule
     * for this issue. If no rule has been set for this issue, will return an empty string.
     *
     * @return The @c std::string libCellML Reference heading relevant to this issue.
     */
    std::string referenceHeading() const;

private:
    Issue(); /**< Constructor, @private. */

    struct IssueImpl; /**< Forward declaration for pImpl idiom, @private. */
    IssueImpl *mPimpl; /**< Private member to implementation pointer, @private. */
};

} // namespace libcellml

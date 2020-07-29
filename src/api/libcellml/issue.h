/*
Copyright 2016 University of Auckland

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
public:
    virtual ~Issue(); /**< Destructor */
    Issue(const Issue &rhs) = delete; /**< Copy constructor */
    Issue(Issue &&rhs) noexcept = delete; /**< Move constructor */
    Issue &operator=(Issue rhs) = delete; /**< Assignment operator */

    /**
     * @brief Create an @c Issue object.
     *
     * Factory method to create an @c Issue.  Can create a
     * blank issue with::
     *
     *   IssuePtr issue = libcellml::Issue::create();
     *
     * or an issue with one of the following types as a parameter::
     *
     *   - libcellml::ComponentPtr
     *   - libcellml::ImportSourcePtr
     *   - libcellml::ModelPtr
     *   - libcellml::ResetPtr
     *   - libcellml::UnitsPtr
     *   - libcellml::VariablePtr
     *
     * The default values for the enumerations are::
     *
     *   - libcellml::Issue::Cause::UNDEFINED;
     *   - libcellml::Issue::Level::ERROR;
     *   - libcellml::Issue::ReferenceRule::UNDEFINED;
     *
     * @return A smart pointer to an @c Issue object.
     */
    static IssuePtr create() noexcept;

    /**
     * @overload
     */
    static IssuePtr create(const ComponentPtr &component) noexcept;

    /**
     * @overload
     */
    static IssuePtr create(const ImportSourcePtr &importSource) noexcept;

    /**
     * @overload
     */
    static IssuePtr create(const ModelPtr &model) noexcept;

    /**
     * @overload
     */
    static IssuePtr create(const ResetPtr &reset) noexcept;

    /**
     * @overload
     */
    static IssuePtr create(const UnitsPtr &units) noexcept;

    /**
     * @overload
     */
    static IssuePtr create(const VariablePtr &variable) noexcept;

    /**
     * @brief The issue Cause enum class.
     *
     * Enum to describe the cause of issue a given issue is.
     */
    enum class Cause
    {
        COMPONENT,
        CONNECTION,
        ENCAPSULATION,
        GENERATOR,
        IMPORT,
        MATHML,
        MODEL,
        RESET,
        UNDEFINED,
        UNITS,
        VARIABLE,
        XML
    };

    /**
     * @brief The issue Level enum class.
     *
     * Enum to describe the level of severity that a given issue has.
     */
    enum class Level
    {
        ERROR,
        WARNING,
        HINT,
        INFORMATION
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
        IMPORT_HREF,
        IMPORT_CHILD,
        IMPORT_EQUIVALENT,
        IMPORT_UNITS_NAME,
        IMPORT_UNITS_NAME_UNIQUE,
        IMPORT_UNITS_REF,
        IMPORT_COMPONENT_NAME,
        IMPORT_COMPONENT_NAME_UNIQUE,
        IMPORT_COMPONENT_COMPONENT_REF,
        UNITS_NAME,
        UNITS_NAME_UNIQUE,
        UNITS_STANDARD,
        UNITS_CHILD,
        UNIT_UNITS_REF,
        UNIT_CIRCULAR_REF,
        UNIT_OPTIONAL_ATTRIBUTE,
        UNIT_PREFIX,
        UNIT_MULTIPLIER,
        UNIT_EXPONENT,
        COMPONENT_NAME,
        COMPONENT_NAME_UNIQUE,
        COMPONENT_CHILD,
        VARIABLE_NAME,
        VARIABLE_NAME_UNIQUE,
        VARIABLE_UNITS,
        VARIABLE_INTERFACE,
        VARIABLE_INITIAL_VALUE,
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
        ENCAPSULATION_CHILD,
        COMPONENT_REF_COMPONENT,
        COMPONENT_REF_CHILD,
        CONNECTION_COMPONENT1,
        CONNECTION_COMPONENT2,
        CONNECTION_EXCLUDE_SELF,
        CONNECTION_UNIQUE,
        CONNECTION_CHILD,
        MAP_VARIABLES_VARIABLE1,
        MAP_VARIABLES_VARIABLE2,
        MAP_VARIABLES_UNIQUE,

        // Issues not present in the normative specification:
        MAP_VARIABLES_IDENTICAL_UNIT_REDUCTION
    };

    /**
     * @brief Set the description for this issue.
     *
     * Set the @c std::string @p description for why this issue was raised.
     *
     * @param description The @c std::string issue description to set.
     */
    void setDescription(const std::string &description);

    /**
     * @brief Get the description for this issue.
     *
     * Get the @c std::string description for why this issue was raised.
     *
     * @return The @c std::string description of the issue.
     */
    std::string description() const;

    /**
     * @brief Set the cause of this issue.
     *
     * Set the @p cause of this issue from the options available in
     * @c Issue::Cause.
     *
     * @param cause The @c Issue::Cause to set.
     */
    void setCause(Cause cause);

    /**
     * @brief Get the cause of this issue.
     *
     * Get the @c cause of this issue. If no cause has been set for
     * this issue, will return Cause::UNDEFINED.
     *
     * @return The @c Issue::Cause set for this issue.
     */
    Cause cause() const;

    /**
     * @brief Set the level of this issue.
     *
     * Set the @p level of this issue from the options available in
     * @c Issue::Level.
     *
     * @param level The @c Issue::Level to set.
     */
    void setLevel(Level level);

    /**
     * @brief Get the level of this issue.
     *
     * Get the @c level of this issue. If no level has been set for
     * this issue, will return Level::ERROR.
     *
     * @return The @c Issue::Level set for this issue.
     */
    Level level() const;

    /**
     * @brief Set the @c enum ReferenceRule of this issue.
     *
     * Set the @p referenceRule of this issue from the options available in
     * the @c ReferenceRule @c enum.
     *
     * @param referenceRule The @c ReferenceRule to set.
     */
    void setReferenceRule(ReferenceRule referenceRule);

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

    /**
     * @brief Set the component for this component issue.
     *
     * Set the @p component that this component issue is relevant to.
     *
     * @param component A pointer to the component that this component issue is relevant to.
     */
    void setComponent(const ComponentPtr &component);

    /**
     * @brief Get the component for this issue.
     *
     * Get the component that this issue is relevant to.
     *
     * @return A pointer to the component that this issue was raised on. If no
     * component has been set for this issue, return a @c nullptr.
     */
    ComponentPtr component() const;

    /**
     * @brief Set the @p import source for this issue.
     *
     * Set the @c ImportSourcePtr @p importSource object that this issue is
     * relevant to.
     *
     * @param importSource A pointer to the import source that this issue is
     * relevant to.
     */
    void setImportSource(const ImportSourcePtr &importSource);

    /**
     * @brief Get the import source for this issue.
     *
     * Get the @c ImportSourcePtr import source for this issue.
     *
     * @return A pointer to the import source this issue was raised on. If no
     * import source has been set for this issue, return a @c nullptr.
     */
    ImportSourcePtr importSource() const;

    /**
     * @brief Set the @p model for this issue.
     *
     * Set the @p model that this issue is relevant to.
     *
     * @param model A pointer to the model that this issue is relevant to.
     */
    void setModel(const ModelPtr &model);

    /**
     * @brief Get the model for this issue.
     *
     * Get the model that this issue is relevant to.
     *
     * @return A pointer to the model that this issue was raised on.
     * If no model has been set for this issue, return a @c nullptr.
     */
    ModelPtr model() const;

    /**
     * @brief Set the units for this issue.
     *
     * Set the @p units that this issue is relevant to.
     *
     * @param units A pointer to the units this issue is relevant to.
     */
    void setUnits(const UnitsPtr &units);

    /**
     * @brief Get the units for this issue.
     *
     * Get the units that this issue is relevant to.
     *
     * @return A pointer to the units that this issue was raised on.
     * If no units has been set for this issue, return a @c nullptr.
     */
    UnitsPtr units() const;

    /**
     * @brief Set the variable for this issue.
     *
     * Set the @p variable that this issue is relevant to.
     *
     * @param variable A pointer to the variable this issue is relevant to.
     */
    void setVariable(const VariablePtr &variable);

    /**
     * @brief Get the variable for this issue.
     *
     * Get the variable that this issue is relevant to.
     *
     * @return A pointer to the variable this variable issue was raised on.
     * If no variable has been set for this issue, return a @c nullptr.
     */
    VariablePtr variable() const;

    /**
     * @brief Set the reset for this issue.
     *
     * Set the @p reset that this issue is relevant to.
     *
     * @param reset A pointer to the reset this issue is relevant to.
     */
    void setReset(const ResetPtr &reset);

    /**
     * @brief Get the reset for this issue.
     *
     * Get the reset that this issue is relevant to.
     *
     * @return A pointer to the reset this reset issue was raised on.
     * If no reset has been set for this issue, return a @c nullptr.
     */
    ResetPtr reset() const;

private:
    Issue(); /**< Constructor */

    /**
     * @brief Constructs an Issue for the component.
     *
     * Convenience constructor for creating an issue for the component.
     *
     * @param component The component the issue references.
     */
    explicit Issue(const ComponentPtr &component);

    /**
     * @brief Constructs an Issue for the import source.
     *
     * Convenience constructor for creating an issue for the import source.
     *
     * @param importSource The import source the issue references.
     */
    explicit Issue(const ImportSourcePtr &importSource);

    /**
     * @brief Constructs an Issue for the model.
     *
     * Convenience constructor for creating an issue for the model.
     *
     * @param model The model the issue references.
     */
    explicit Issue(const ModelPtr &model);

    /**
     * @brief Constructs an Issue for the reset.
     *
     * Convenience constructor for creating an issue for the reset.
     *
     * @param reset The reset the issue references.
     */
    explicit Issue(const ResetPtr &reset);

    /**
     * @brief Constructs an Issue for the units.
     *
     * Convenience constructor for creating an issue for the units.
     *
     * @param units The units the issue references.
     */
    explicit Issue(const UnitsPtr &units);

    /**
     * @brief Constructs an Issue for the variable.
     *
     * Convenience constructor for creating an issue for the variable.
     *
     * @param variable The variable the issue references.
     */
    explicit Issue(const VariablePtr &variable);

    struct IssueImpl; /**< Forward declaration for pImpl idiom. */
    IssueImpl *mPimpl; /**< Private member to implementation pointer */
};

} // namespace libcellml

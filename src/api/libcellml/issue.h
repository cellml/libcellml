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

#include <any>
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
     *   auto issue = libcellml::Issue::create();
     *
     * or an issue with one of the following types as a parameter::
     *
     *   - libcellml::ComponentPtr (defaults the item type to CellMLElement::COMPONENT);
     *   - libcellml::ImportSourcePtr (defaults the item type to CellMLElement::IMPORT);
     *   - libcellml::ModelPtr (defaults the item type to CellMLElement::MODEL);
     *   - libcellml::ResetPtr (defaults the item type to CellMLElement::RESET);
     *   - libcellml::UnitItem (defaults the item type to CellMLElement::UNIT);
     *   - libcellml::UnitsPtr (defaults the item type to CellMLElement::UNITS);
     *   - libcellml::VariablePair (defaults the item type to CellMLElement::MAP_VARIABLES);
     *   - libcellml::VariablePtr (defaults the item type to CellMLElement::VARIABLE); or
     *   - libcellml::CellMLElement, std::any.
     *
     * The default values for the enumerations are::
     *
     *   - libcellml::Issue::Level::ERROR;
     *   - libcellml::Issue::ReferenceRule::UNDEFINED;
     *
     * @return A smart pointer to an @c Issue object.
     */
    static IssuePtr create() noexcept;

    /**
     * @overload
     */
    static IssuePtr create(const ComponentPtr &component, CellMLElement type = CellMLElement::COMPONENT) noexcept;

    /**
     * @overload
     */
    static IssuePtr create(const ImportSourcePtr &importSource) noexcept;

    /**
     * @overload
     */
    static IssuePtr create(const ModelPtr &model, CellMLElement type = CellMLElement::MODEL) noexcept;

    /**
     * @overload
     */
    static IssuePtr create(const ResetPtr &reset, CellMLElement type = CellMLElement::RESET) noexcept;

    /**
     * @overload
     */
    static IssuePtr create(const UnitsPtr &units) noexcept;

    /**
     * @overload
     */
    static IssuePtr create(const VariablePtr &variable) noexcept;

    /**
     * @overload
     */
    static IssuePtr create(const VariablePair &variablePair, CellMLElement type = CellMLElement::MAP_VARIABLES) noexcept;

    /**
     * @overload
     */
    static IssuePtr create(const UnitItem &unitItem) noexcept;

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

        // Placeholder for further references:
        NOT_SPECIFIED
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
     * @brief Set the component relevant to this issue.
     *
     * The internal type will be set to @c CellMLElement::COMPONENT.
     *
     * @param component A @c ComponentPtr relevant to this issue.
     */
    void setComponent(const ComponentPtr &component);

    /**
     * Get the component relevant to this issue.
     *
     * @return A @c Component relevant to this issue, or
     *         a @c nullptr if the internal type is not @c CellMLElement::COMPONENT.
     */
    ComponentPtr component() const;

    /**
     * @brief Set the import source for this issue.
     *
     * The internal type will be set to @c CellMLElement::IMPORT.
     *
     * @param importSource A @c ImportSourcePtr relevant to this issue.
     */
    void setImportSource(const ImportSourcePtr &importSource);

    /**
     * Get the import source relevant to this issue.
     *
     * @return An @c ImportSourcePtr relevant to this issue, or
     *         a @c nullptr if the internal type is not @c CellMLElement::IMPORT.
     */
    ImportSourcePtr importSource() const;

    /**
     * @brief Set the model for this issue.
     *
     * The internal type will be set to @c CellMLElement::MODEL.
     *
     * @param model A @c ModelPtr relevant to this issue.
     */
    void setModel(const ModelPtr &model);

    /**
     * Get the model relevant to this issue.
     *
     * @return A @c ModelPtr relevant to this issue, or
     *         a @c nullptr if the internal type is not @c CellMLElement::MODEL.
     */
    ModelPtr model() const;

    /**
     * @brief Set the units for this issue.
     *
     * The internal type will be set to @c CellMLElement::UNITS.
     *
     * @param units A @c UnitsPtr relevant to this issue.
     */
    void setUnits(const UnitsPtr &units);

    /**
     * Get the units relevant to this issue.
     *
     * @return A @c UnitsPtr relevant to this issue, or
     *         a @c nullptr if the internal type is not @c CellMLElement::UNITS.
     */
    UnitsPtr units() const;

    /**
     * @brief Set the variable for this issue.
     *
     * The internal type will be set to @c CellMLElement::VARIABLE.
     *
     * @param variable A @c VariablePtr relevant to this issue.
     */
    void setVariable(const VariablePtr &variable);

    /**
     * Get the variable relevant to this issue.
     *
     * @return A @c VariablePtr relevant to this issue, or
     *         a @c nullptr if the internal type is not @c CellMLElement::VARIABLE.
     */
    VariablePtr variable() const;

    /**
     * @brief Set the reset for this issue.
     *
     * The internal type will be set to @c CellMLElement::RESET.
     *
     * @param reset A @c ResetPtr relevant to this issue.
     */
    void setReset(const ResetPtr &reset);

    /**
     * Get the reset relevant to this issue.
     *
     * @return A @c ResetPtr relevant to this issue, or @c nullptr
     *         if the internal type is not @c CellMLElement::RESET.
     */
    ResetPtr reset() const;

    /**
     * @brief Set the component whose MathML is relevant to this issue.
     *
     * The internal type will be set to @c CellMLElement::MATHML.
     *
     * @param component The @c ComponentPtr whose MathML is relevant to this issue.
     */
    void setMath(const ComponentPtr &component);

    /**
     * Get the component whose MathML is relevant to this issue.
     *
     * @return A @c ComponentPtr whose MathML is relevant to this issue, or @c nullptr
     *         if the internal type is not @c CellMLElement::MATHML.
     */
    ComponentPtr math() const;

    /**
     * @brief Set the connection relevant to this issue.
     *
     * The internal type will be set to @c CellMLElement::CONNECTION.
     *
     * @param pair The @c VariablePair whose connection is relevant to this issue.
     */
    void setConnection(const VariablePair &pair);

    /**
     * Get the connection relevant to this issue.
     *
     * @return A @c VariablePair representing the connection relevant to this issue,
     *         or @c std::pair(nullptr,nullptr) if the internal type is not @c CellMLElement::CONNECTION.
     */
    VariablePair connection() const;

    /**
     * @brief Set the variable mapping relevant to this issue.
     *
     * The internal type will be set to @c CellMLElement::MAP_VARIABLES.
     *
     * @param pair The @c VariablePair whose equivalence is relevant to this issue.
     */
    void setMapVariables(const VariablePair &pair);

    /**
     * Get the equivalent variable pair relevant to this issue.
     *
     * @return A @c VariablePair representing the variable equivalence relevant to this issue,
     *         or @c std::pair(nullptr,nullptr) if the internal type is not @c CellMLElement::MAP_VARIABLES.
     */
    VariablePair mapVariables() const;

    /**
     * @brief Set the reset whose reset value is relevant to this issue.
     *
     * The internal type will be set to @c CellMLElement::RESET_VALUE.
     *
     * @param reset A @c ResetPtr whose reset value is relevant to this issue.
     */
    void setResetValue(const ResetPtr &reset);

    /**
     * Get the reset whose reset value is relevant to this issue.
     *
     * @return A @c ResetPtr whose reset value is relevant to this issue,
     *         or @c nullptr if the internal type is not @c CellMLElement::RESET_VALUE.
     */
    ResetPtr resetValue() const;

    /**
     * @brief Set the reset whose test value is relevant to this issue.
     *
     * The internal type will be set to @c CellMLElement::TEST_VALUE.
     *
     * @param reset A @c ResetPtr whose test value is relevant to this issue.
     */
    void setTestValue(const ResetPtr &reset);

    /**
     * Get the reset whose test value is relevant to this issue.
     *
     * @return A @c ResetPtr whose test value is relevant to this issue,
     *         or @c nullptr if the internal type is not @c CellMLElement::MAP_VARIABLES.
     */
    ResetPtr testValue() const;

    /**
     * @brief Set the @c UnitItem whose relevant to this issue.
     *
     * The internal type will be set to @c CellMLElement::UNIT.
     *
     * @param unit A @c UnitItem relevant to this issue.
     */
    void setUnit(const UnitItem &unit);

    /**
     * Get the unit relevant to this issue.
     *
     * @return A @c UnitItem relevant to this issue,
     *         or @c std::pair(nullptr,0) if the internal type is not @c CellMLElement::UNIT.
     */
    UnitItem unit() const;

    /**
     * @brief Set the @c ModelPtr whose encapsulation is relevant to this issue.
     *
     * The internal type will be set to @c CellMLElement::ENCAPSULATION.
     *
     * @param model A @c ModelPtr whose encapsulation is relevant to this issue.
     */
    void setEncapsulation(const ModelPtr &model);

    /**
     * Get the @c ModelPtr whose encapsulation is relevant to this issue.
     *
     * @return A @c ModelPtr whose encapsulation relevant to this issue,
     *         or @c nullptr if the internal type is not @c CellMLElement::ENCAPSULATION.
     */
    ModelPtr encapsulation() const;

    /**
     * @brief Set the @c ComponentPtr whose encapsulation position is relevant to this issue.
     *
     * The internal type will be set to @c CellMLElement::COMPONENT_REF.
     *
     * @param component A @c ComponentPtr whose encapsulation position is relevant to this issue.
     */
    void setComponentRef(const ComponentPtr &component);

    /**
     * Get the @c ComponentPtr whose encapsulation is relevant to this issue.
     *
     * @return A @c ComponentPtr whose encapsulation relevant to this issue,
     *         or @c nullptr if the internal type is not @c CellMLElement::COMPONENT_REF.
     */
    ComponentPtr componentRef() const;

    /**
     * @brief Get the @ref CellMLElement enum for the stored item.
     *
     * Get the @ref CellMLElement enum for the stored item.
     *
     * @return The @ref CellMLElement enum for the stored item, or @ref CellMLElement::UNDEFINED if none.
     */
    CellMLElement itemType() const;

    /**
     * @brief Set an @c std::any item relevant to this issue.
     *
     * Set an @c std::any item relevant to this issue.
     *
     * @param item An @c std::any item relevant to this issue.
     * @param type An @c CellMLElement enum.
     */
    void setItem(CellMLElement type, const std::any &item);

    /**
     * Get the stored item as an @c std::any item.
     *
     * Get the stored item as an @c std::any item.
     * Note that the stored @ref CellMLElement can be retrieved using itemType().
     *
     * @return A @c std::any item related to this issue.
     */
    std::any item() const;

    /**
     * @brief Clear the stored item.
     *
     * Clear the issue returning it to its initial state.
     */
    void clear();

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

    /**
     * @brief Constructs an Issue for the unit.
     *
     * Convenience constructor for creating an issue for the unit.
     *
     * @param unit The unit the issue references.
     */
    explicit Issue(const UnitItem &unit);

    struct IssueImpl; /**< Forward declaration for pImpl idiom. */
    IssueImpl *mPimpl; /**< Private member to implementation pointer */
};

} // namespace libcellml

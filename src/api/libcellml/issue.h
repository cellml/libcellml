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

#include "libcellml/exportdefinitions.h"
#include "libcellml/specificationrules.h"
#include "libcellml/types.h"

#include <string>

namespace libcellml {

/**
 * @brief The Issue class
 *
 * Base class for issues used with logger derived classes.
 */
class LIBCELLML_EXPORT Issue
{
public:
    Issue(); /**< Constructor */
    virtual ~Issue(); /**< Destructor */
    Issue(const Issue &rhs); /**< Copy constructor */
    Issue(Issue &&rhs) noexcept; /**< Move constructor */
    Issue &operator=(Issue rhs); /**< Assignment operator */

    /**
     * @brief Constructs an Issue for the model.
     *
     * Convienence constructor for creating an issue for the model.
     *
     * @param model The model the issue references.
     */
    explicit Issue(const ModelPtr &model);

    /**
     * @brief Constructs an Issue for the when.
     *
     * Convienence constructor for creating an issue for the when.
     *
     * @param when The when the issue references.
     */
    explicit Issue(const WhenPtr &when);

    /**
     * @brief Constructs an Issue for the component.
     *
     * Convienence constructor for creating an issue for the component.
     *
     * @param component The component the issue references.
     */
    explicit Issue(const ComponentPtr &component);

    /**
     * @brief Constructs an Issue for the import source.
     *
     * Convienence constructor for creating an issue for the import source.
     *
     * @param importSource The import source the issue references.
     */
    explicit Issue(const ImportSourcePtr &importSource);

    /**
     * @brief Constructs an Issue for the units.
     *
     * Convienence constructor for creating an issue for the units.
     *
     * @param units The units the issue references.
     */
    explicit Issue(const UnitsPtr &units);

    /**
     * @brief Constructs an Issue for the variable.
     *
     * Convienence constructor for creating an issue for the variable.
     *
     * @param variable The variable the issue references.
     */
    explicit Issue(const VariablePtr &variable);

    /**
     * @brief Constructs an Issue for the reset.
     *
     * Convienence constructor for creating an issue for the reset.
     *
     * @param reset The reset the issue references.
     */
    explicit Issue(const ResetPtr &reset);

    /**
     * @brief The issue Cause enum class.
     *
     * Enum to describe the cause of a given issue.
     */
    enum class Cause
    {
        COMPONENT,
        CONNECTION,
        ENCAPSULATION,
        IMPORT,
        MATHML,
        MODEL,
        RESET,
        UNDEFINED,
        UNITS,
        VARIABLE,
        WHEN,
        XML
    };

    /**
     * @brief The issue Type enum class
     * 
     * Enum to describe the type of the issue
     */
    enum class Type
    {
        ERROR,
        WARNING,
        HINT
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
     * @brief Check whether the cause of this issue matches the argument cause.
     *
     * Returns @c true if the @p cause matches the the @c Issue::Cause for this
     * issue and @c false otherwise.
     *
     * @return @c true if the @p cause matches the the @c Issue::Cause for this
     * issue and @c false otherwise.
     */
    bool isCause(Cause cause) const;

    /**
     * @brief Set the @c enum SpecificationRule of this issue.
     *
     * Set the @p rule of this issue from the options available in
     * the @c SpecificationRule @c enum.
     *
     * @param rule The @c SpecificationRule to set.
     */
    void setRule(SpecificationRule rule);

    /**
     * @brief Get the @c enum SpecificationRule of this issue.
     *
     * Get the @c enum @c SpecificationRule value @p rule of this issue. If
     * no rule has been set for this issue, will return SpecificationRule::UNDEFINED.
     *
     * @return The @c SpecificationRule for this issue.
     */
    SpecificationRule rule() const;

    /**
     * @brief Set the type of this issue.
     *
     * Set the @p type of this issue from the options available in
     * @c Issue::Type.
     *
     * @param type The @c Issue::Type to set.
     */
    void setType(Type type);

    /**
     * @brief Get the type of this issue.
     *
     * Get the @c type of this issue. If no type has been set for
     * this issue, will return Type::FATAL.
     *
     * @return The @c Issue::Type set for this issue.
     */
    Type type() const;

    /**
     * @brief Check whether the type of this issue matches the argument type.
     *
     * Returns @c true if the @p type matches the the @c Issue::type for this
     * issue and @c false otherwise.
     *
     * @return @c true if the @p type matches the the @c Issue::type for this
     * issue and @c false otherwise.
     */
    bool isType(Type type) const;

    /**
     * @brief Get the @c std::string heading associated with the @c enum SpecificationRule for this issue.
     *
     * Get the @c std::string CellML 2.0 Specification heading associated with the @c enum SpecificationRule
     * for this issue. If no rule has been set for this issue, will return an empty string.
     *
     * @return The @c std::string referencing the CellML 2.0 Specification heading relevant to this issue.
     */
    std::string specificationHeading() const;

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

    /**
     * @brief Set the when for this issue.
     *
     * Set the @p when that this issue is relevant to.
     *
     * @param when A pointer to the when this issue is relevant to.
     */
    void setWhen(const WhenPtr &when);

    /**
     * @brief Get the when for this issue.
     *
     * Get the when that this issue is relevant to.
     *
     * @return A pointer to the when this when issue was raised on.
     * If no when has been set for this issue, return a @c nullptr.
     */
    WhenPtr when() const;

private:
    void swap(Issue &rhs); /**< Swap method required for C++ 11 move semantics. */

    struct IssueImpl; /**< Forward declaration for pImpl idiom. */
    IssueImpl *mPimpl; /**< Private member to implementation pointer */
};

} // namespace libcellml

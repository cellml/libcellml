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
 * Base class for errors used with logger derived classes.
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
     * Convienence constructor for creating an error for the model.
     *
     * @param model The model the error references.
     */
    explicit Issue(const ModelPtr &model);

    /**
     * @brief Constructs an Issue for the when.
     *
     * Convienence constructor for creating an error for the when.
     *
     * @param when The when the error references.
     */
    explicit Issue(const WhenPtr &when);

    /**
     * @brief Constructs an Issue for the component.
     *
     * Convienence constructor for creating an error for the component.
     *
     * @param component The component the error references.
     */
    explicit Issue(const ComponentPtr &component);

    /**
     * @brief Constructs an Issue for the import source.
     *
     * Convienence constructor for creating an error for the import source.
     *
     * @param importSource The import source the error references.
     */
    explicit Issue(const ImportSourcePtr &importSource);

    /**
     * @brief Constructs an Issue for the units.
     *
     * Convienence constructor for creating an error for the units.
     *
     * @param units The units the error references.
     */
    explicit Issue(const UnitsPtr &units);

    /**
     * @brief Constructs an Issue for the variable.
     *
     * Convienence constructor for creating an error for the variable.
     *
     * @param variable The variable the error references.
     */
    explicit Issue(const VariablePtr &variable);

    /**
     * @brief Constructs an Issue for the reset.
     *
     * Convienence constructor for creating an error for the reset.
     *
     * @param reset The reset the error references.
     */
    explicit Issue(const ResetPtr &reset);

    /**
     * @brief The error Kind enum class.
     *
     * Enum to describe the kind of error a given error is.
     */
    enum class Kind
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
     * @brief The error Level enum class
     * 
     * Enum to describe the level of the error
     */
    enum class Level
    {
        UNDEFINED,
        FATAL,
        WARNING,
        FUTURE_ERROR,
        INFORMATION
    };

    /**
     * @brief Set the description for this error.
     *
     * Set the @c std::string @p description for why this error was raised.
     *
     * @param description The @c std::string error description to set.
     */
    void setDescription(const std::string &description);

    /**
     * @brief Get the description for this error.
     *
     * Get the @c std::string description for why this error was raised.
     *
     * @return The @c std::string description of the error.
     */
    std::string description() const;

    /**
     * @brief Set the kind of this error.
     *
     * Set the @p kind of this error from the options available in
     * @c Issue::Kind.
     *
     * @param kind The @c Issue::Kind to set.
     */
    void setKind(Kind kind);

    /**
     * @brief Get the kind of this error.
     *
     * Get the @c kind of this error. If no kind has been set for
     * this error, will return Kind::UNDEFINED.
     *
     * @return The @c Issue::Kind set for this error.
     */
    Kind kind() const;

    /**
     * @brief Check whether the kind of this error matches the argument kind.
     *
     * Returns @c true if the @p kind matches the the @c Issue::Kind for this
     * error and @c false otherwise.
     *
     * @return @c true if the @p kind matches the the @c Issue::Kind for this
     * error and @c false otherwise.
     */
    bool isKind(Kind kind) const;

    /**
     * @brief Set the @c enum SpecificationRule of this error.
     *
     * Set the @p rule of this error from the options available in
     * the @c SpecificationRule @c enum.
     *
     * @param rule The @c SpecificationRule to set.
     */
    void setRule(SpecificationRule rule);

    /**
     * @brief Get the @c enum SpecificationRule of this error.
     *
     * Get the @c enum @c SpecificationRule value @p rule of this error. If
     * no rule has been set for this error, will return SpecificationRule::UNDEFINED.
     *
     * @return The @c SpecificationRule for this error.
     */
    SpecificationRule rule() const;

    /**
     * @brief Set the level of this error.
     *
     * Set the @p level of this error from the options available in
     * @c Issue::Level.
     *
     * @param level The @c Issue::Level to set.
     */
    void setLevel(Level level);

    /**
     * @brief Get the level of this error.
     *
     * Get the @c level of this error. If no level has been set for
     * this error, will return Level::FATAL.
     *
     * @return The @c Issue::Level set for this error.
     */
    Level level() const;

    /**
     * @brief Check whether the level of this error matches the argument level.
     *
     * Returns @c true if the @p level matches the the @c Issue::level for this
     * error and @c false otherwise.
     *
     * @return @c true if the @p level matches the the @c Issue::level for this
     * error and @c false otherwise.
     */
    bool isLevel(Level level) const;

    /**
     * @brief Get the @c std::string heading associated with the @c enum SpecificationRule for this error.
     *
     * Get the @c std::string CellML 2.0 Specification heading associated with the @c enum SpecificationRule
     * for this error. If no rule has been set for this error, will return an empty string.
     *
     * @return The @c std::string referencing the CellML 2.0 Specification heading relevant to this error.
     */
    std::string specificationHeading() const;

    /**
     * @brief Set the component for this component error.
     *
     * Set the @p component that this component error is relevant to.
     *
     * @param component A pointer to the component that this component error is relevant to.
     */
    void setComponent(const ComponentPtr &component);

    /**
     * @brief Get the component for this error.
     *
     * Get the component that this error is relevant to.
     *
     * @return A pointer to the component that this error was raised on. If no
     * component has been set for this error, return a @c nullptr.
     */
    ComponentPtr component() const;

    /**
     * @brief Set the @p import source for this error.
     *
     * Set the @c ImportSourcePtr @p importSource object that this error is
     * relevant to.
     *
     * @param importSource A pointer to the import source that this error is
     * relevant to.
     */
    void setImportSource(const ImportSourcePtr &importSource);

    /**
     * @brief Get the import source for this error.
     *
     * Get the @c ImportSourcePtr import source for this error.
     *
     * @return A pointer to the import source this error was raised on. If no
     * import source has been set for this error, return a @c nullptr.
     */
    ImportSourcePtr importSource() const;

    /**
     * @brief Set the @p model for this error.
     *
     * Set the @p model that this error is relevant to.
     *
     * @param model A pointer to the model that this error is relevant to.
     */
    void setModel(const ModelPtr &model);

    /**
     * @brief Get the model for this error.
     *
     * Get the model that this error is relevant to.
     *
     * @return A pointer to the model that this error was raised on.
     * If no model has been set for this error, return a @c nullptr.
     */
    ModelPtr model() const;

    /**
     * @brief Set the units for this error.
     *
     * Set the @p units that this error is relevant to.
     *
     * @param units A pointer to the units this error is relevant to.
     */
    void setUnits(const UnitsPtr &units);

    /**
     * @brief Get the units for this error.
     *
     * Get the units that this error is relevant to.
     *
     * @return A pointer to the units that this error was raised on.
     * If no units has been set for this error, return a @c nullptr.
     */
    UnitsPtr units() const;

    /**
     * @brief Set the variable for this error.
     *
     * Set the @p variable that this error is relevant to.
     *
     * @param variable A pointer to the variable this error is relevant to.
     */
    void setVariable(const VariablePtr &variable);

    /**
     * @brief Get the variable for this error.
     *
     * Get the variable that this error is relevant to.
     *
     * @return A pointer to the variable this variable error was raised on.
     * If no variable has been set for this error, return a @c nullptr.
     */
    VariablePtr variable() const;

    /**
     * @brief Set the reset for this error.
     *
     * Set the @p reset that this error is relevant to.
     *
     * @param reset A pointer to the reset this error is relevant to.
     */
    void setReset(const ResetPtr &reset);

    /**
     * @brief Get the reset for this error.
     *
     * Get the reset that this error is relevant to.
     *
     * @return A pointer to the reset this reset error was raised on.
     * If no reset has been set for this error, return a @c nullptr.
     */
    ResetPtr reset() const;

    /**
     * @brief Set the when for this error.
     *
     * Set the @p when that this error is relevant to.
     *
     * @param when A pointer to the when this error is relevant to.
     */
    void setWhen(const WhenPtr &when);

    /**
     * @brief Get the when for this error.
     *
     * Get the when that this error is relevant to.
     *
     * @return A pointer to the when this when error was raised on.
     * If no when has been set for this error, return a @c nullptr.
     */
    WhenPtr when() const;

private:
    void swap(Issue &rhs); /**< Swap method required for C++ 11 move semantics. */

    struct IssueImpl; /**< Forward declaration for pImpl idiom. */
    IssueImpl *mPimpl; /**< Private member to implementation pointer */
};

} // namespace libcellml

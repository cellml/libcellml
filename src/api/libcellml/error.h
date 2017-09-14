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
#include "libcellml/specificationrules.h"
#include "libcellml/types.h"

namespace libcellml {

/**
 * @brief The Error class
 *
 * Base class for errors used with logger derived classes.
 */
class LIBCELLML_EXPORT Error
{
public:
    Error(); /**< Constructor */
    ~Error(); /**< Destructor */
    Error(const Error& rhs); /**< Copy constructor */
    Error(Error &&rhs); /**< Move constructor */
    Error& operator=(Error rhs); /**< Assignment operator */

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
        UNDEFINED,
        UNITS,
        VARIABLE,
        XML
    };

    /**
     * @brief Set the description for this error.
     *
     * Set the @c std::string @p description for why this error was raised.
     *
     * @param description The @c std::string error description to set.
     */
    void setDescription(const std::string& description);

    /**
     * @brief Get the description for this error.
     *
     * Get the @c std::string description for why this error was raised.
     *
     * @return The @c std::string description of the error.
     */
    std::string getDescription() const;

    /**
     * @brief Set the kind of this error.
     *
     * Set the @p kind of this error from the options available in
     * @c Error::Kind.
     *
     * @param kind The @c Error::Kind to set.
     */
    void setKind(Kind kind);

    /**
     * @brief Get the kind of this error.
     *
     * Get the @c kind of this error. If no kind has been set for
     * this error, will return Kind::UNDEFINED.
     *
     * @return The @c Error::Kind set for this error.
     */
    Kind getKind() const;

    /**
     * @brief Check whether the kind of this error matches the argument kind.
     *
     * Returns @c true if the @p kind matches the the @c Error::Kind for this
     * error and @c false otherwise.
     *
     * @return @c true if the @p kind matches the the @c Error::Kind for this
     * error and @c false otherwise.
     */
    bool isKind(const Kind &kind) const;

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
    SpecificationRule getRule() const;

    /**
     * @brief Get the @c std::string heading associated with the @c enum SpecificationRule for this error.
     *
     * Get the @c std::string CellML 2.0 Specification heading associated with the @c enum SpecificationRule
     * for this error. If no rule has been set for this error, will return an empty string.
     *
     * @return The @c std::string referencing the CellML 2.0 Specification heading relevant to this error.
     */
    std::string getSpecificationHeading() const;

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
    ComponentPtr getComponent() const;

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
    ImportSourcePtr getSourceImport() const;

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
    ModelPtr getModel() const;

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
    UnitsPtr getUnits() const;

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
    VariablePtr getVariable() const;

private:
    void swap(Error &rhs); /**< Swap method required for C++ 11 move semantics. */

    struct ErrorImpl; /**< Forward declaration for pImpl idiom. */
    ErrorImpl *mPimpl; /**< Private member to implementation pointer */
};

}

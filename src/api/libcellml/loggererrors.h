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

#ifndef LIBCELLML_LIBCELLML_LOGGERERRORS_H_
#define LIBCELLML_LIBCELLML_LOGGERERRORS_H_

#include <string>

#include "libcellml/libcellml_export.h"
#include "libcellml/types.h"

namespace libcellml {

/**
 * @brief The Error class
 *
 * Base class for errors used with the logger class.
 */
class LIBCELLML_EXPORT Error
{
public:
    /**
     * @brief Set the description for this error.
     *
     * Set the @c std::string @p description for why this error was raised.
     *
     * @param description The @c std::string error description to set.
     */
    void setDescription(const std::string& description)
    {
        mDescription = description;
    }

    /**
     * @brief Get the description for this error.
     *
     * Get the @c std::string description for why this error was raised.
     *
     * @return The @c std::string description of the error.
     */
    std::string getDescription() const
    {
        return mDescription;
    }

    /**
     * @brief Set the component for this component error.
     *
     * Set the @p component that this component error is relevant to.
     *
     * @param component A pointer to the component that this component error is relevant to.
     */
    void setComponent(const ComponentPtr component)
    {
        mComponent = component;
    }

    /**
     * @brief Get the component for this error.
     *
     * Get the component that this error is relevant to.
     *
     * @return A pointer to the component that this error was raised on. If no
     * component has been set for this error, return a @c nullptr.
     */
    ComponentPtr getComponent()
    {
        return mComponent;
    }

    /**
     * @brief Get a @c const reference to the component for this error.
     *
     * Returns a @c const reference to the component that this
     * error is relevant to.
     *
     * @overload
     *
     * @return A @c const reference to the component that this
     * error was raised on. If no component has been set for this
     * error, return a @c nullptr.
     */
    const ComponentPtr& getComponent() const
    {
        return mComponent;
    }

    /**
     * @brief Set the @p import for this error.
     *
     * Set the @c ImportPtr @p import object that this error is relevant to.
     *
     * @param import A pointer to the import that this error is relevant to.
     */
    void setImport(const ImportPtr import)
    {
        mImport = import;
    }

    /**
     * @brief Get the import for this error.
     *
     * Get the @c ImportPtr import for this error.
     *
     * @return A pointer to the import this error was raised on. If no import
     * has been set for this error, return a @c nullptr.
     */
    ImportPtr getImport()
    {
        return mImport;
    }

    /**
     * @brief Get a @c const reference to the import for this error.
     *
     * Returns a @c const reference to the import that this
     * error is relevant to.
     *
     * @overload
     *
     * @return A @c const reference to the import that this
     * error was raised on. If no import has been set for this error,
     * return a @c nullptr.
     */
    const ImportPtr& getImport() const
    {
        return mImport;
    }

    /**
     * @brief Set the @p model for this error.
     *
     * Set the @p model that this error is relevant to.
     *
     * @param model A pointer to the model that this error is relevant to.
     */
    void setModel(const ModelPtr model)
    {
        mModel = model;
    }

    /**
     * @brief Get the model for this error.
     *
     * Get the model that this error is relevant to.
     *
     * @return A pointer to the model that this error was raised on.
     * If no model has been set for this error, return a @c nullptr.
     */
    ModelPtr getModel()
    {
        return mModel;
    }

    /**
     * @brief Get a @c const reference to the model for this error.
     *
     * Returns a @c const reference to the model that this
     * error is relevant to.
     *
     * @overload
     *
     * @return A @c const reference to the model that this
     * error was raised on. If no model has been set for this error,
     * return a @c nullptr.
     */
    const ModelPtr& getModel() const
    {
        return mModel;
    }

    /**
     * @brief Set the units for this error.
     *
     * Set the @p units that this error is relevant to.
     *
     * @param units A pointer to the units this error is relevant to.
     */
    void setUnits(const UnitsPtr units)
    {
        mUnits = units;
    }

    /**
     * @brief Get the units for this error.
     *
     * Get the units that this error is relevant to.
     *
     * @return A pointer to the units that this error was raised on.
     * If no units has been set for this error, return a @c nullptr.
     */
    UnitsPtr getUnits()
    {
        return mUnits;
    }

    /**
     * @brief Get a @c const reference to the units for this error.
     *
     * Returns a @c const reference to the units that this
     * error is relevant to.
     *
     * @overload
     *
     * @return A @c const reference to the units that this
     * error was raised on. If no units has been set for this error,
     * return a @c nullptr.
     */
    const UnitsPtr& getUnits() const
    {
        return mUnits;
    }

    /**
     * @brief Set the variable for this error.
     *
     * Set the @p variable that this error is relevant to.
     *
     * @param variable A pointer to the variable this error is relevant to.
     */
    void setVariable(const VariablePtr variable)
    {
        mVariable = variable;
    }

    /**
     * @brief Get the variable for this error.
     *
     * Get the variable that this error is relevant to.
     *
     * @return A pointer to the variable this variable error was raised on.
     * If no variable has been set for this error, return a @c nullptr.
     */
    VariablePtr getVariable()
    {
        return mVariable;
    }

    /**
     * @brief Get a @c const reference to the variable for this error.
     *
     * Returns a @c const reference to the variable that this
     * error is relevant to.
     *
     * @overload
     *
     * @return A @c const reference to the variable that this
     * error was raised on. If no variable has been set for this
     * error, return a @c nullptr.
     */
    const VariablePtr& getVariable() const
    {
        return mVariable;
    }

private:
    std::string mDescription; /**< The string description for why this entity error raised. */

    ComponentPtr mComponent; /**< Pointer to the component that the error occurred in. */
    ImportPtr mImport; /**< Pointer to the import that the error occurred in. */
    ModelPtr mModel; /**< Pointer to the model that the error occurred in. */
    UnitsPtr mUnits; /**< Pointer to the units that the error occurred in. */
    VariablePtr mVariable; /**< Pointer to the variable that the error occurred in. */
};

typedef std::shared_ptr<Error> ErrorPtr; /**< Type definition for shared error pointer. */

}

#endif /* LIBCELLML_LIBCELLML_LOGGERERROS_H_ */



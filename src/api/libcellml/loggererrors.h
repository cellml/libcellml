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
 * @brief The EntityError class
 *
 * Base class for errors used with the logger class.
 */
class LIBCELLML_EXPORT EntityError
{
public:
    virtual ~EntityError() {} /**< Virtual destructor to enable dynamic_cast to derived types. */

    /**
     * @brief Set the description for this entity error.
     *
     * Set the @c std::string @p description for why this entity error was raised.
     *
     * @param description The @c std::string error description to set.
     */
    void setDescription(const std::string& description)
    {
        mDescription = description;
    }

    /**
     * @brief Get the description for this entity error.
     *
     * Get the @c std::string description for why this entity error was raised.
     *
     * @return The @c std::string description of the error.
     */
    std::string getDescription() const
    {
        return mDescription;
    }

protected:
    std::string mDescription; /**< The string description for why this entity error raised. */
};

/**
 * @brief The ImportError class.
 *
 * ImportError class for all import loggable errors.
 */
class ImportError: public EntityError
{
public:
    /**
     * @brief Set the @p import for this import error.
     *
     * Set the @c ImportPtr @p import object that this import error is relevant to.
     *
     * @param import A pointer to the import that this import error is relevant to.
     */
    void setImport(const ImportPtr import)
    {
        mImport = import;
    }

    /**
     * @brief Get the import for this import error.
     *
     * Get the @c ImportPtr import for this import error.
     *
     * @return A pointer to the import this import error was raised on.
     */
    ImportPtr getImport()
    {
        return mImport;
    }

    /**
     * @brief Get a @c const reference to the import for this error.
     *
     * Returns a @c const reference to the import that this import
     * error is relevant to.
     *
     * @overload
     *
     * @return A @c const reference to the import that this
     * import error was raised on.
     */
    const ImportPtr& getImport() const
    {
        return mImport;
    }

private:
    ImportPtr mImport; /**< Pointer to the import that the error occurred in. */
};

/**
 * @brief The VariableError class.
 *
 * VariableError class for all variable loggable errors.
 */
class VariableError: public EntityError
{
public:
    /**
     * @brief Set the component for this variable error.
     *
     * Set the @p component this variable error is associated with.
     * This is likely the parent component the variable is
     * expected to be contained within.
     *
     * @param component A pointer to the component that this variable error is relevant to.
     */
    void setComponent(const ComponentPtr component)
    {
        mComponent = component;
    }

    /**
     * @brief Get the component for this variable error.
     *
     * Get the component this variable error is associated with.
     * This is likely the parent component the variable is expected
     * to be contained within.
     *
     * @return A pointer to the component this variable error is relevant to.
     */
    ComponentPtr getComponent()
    {
        return mComponent;
    }

    /**
     * @brief Get a @c const reference to the component for this variable error.
     *
     * Returns a @c const reference to the component that this variable
     * error is associated with. This is likely the parent component the
     * variable is expected to be contained within.
     *
     * @overload
     *
     * @return A @c const reference to the component that this
     * variable error is relevant to.
     */
    const ComponentPtr& getComponent() const
    {
        return mComponent;
    }

    /**
     * @brief Set the variable for this variable error.
     *
     * Set the @p variable that this variable error is relevant to.
     *
     * @param variable A pointer to the variable this variable error is relevant to.
     */
    void setVariable(const VariablePtr variable)
    {
        mVariable = variable;
    }

    /**
     * @brief Get the variable for this variable error.
     *
     * Get the variable that this variable error is relevant to.
     *
     * @return A pointer to the variable this variable error was raised on.
     */
    VariablePtr getVariable()
    {
        return mVariable;
    }

    /**
     * @brief Get a @c const reference to the variable for this error.
     *
     * Returns a @c const reference to the variable that this variable
     * error is relevant to.
     *
     * @overload
     *
     * @return A @c const reference to the variable that this
     * variable error was raised on.
     */
    const VariablePtr& getVariable() const
    {
        return mVariable;
    }

private:
    VariablePtr mVariable; /**< Pointer to the variable that the error occurred in. */
    ComponentPtr mComponent; /**< Pointer to the component associated with this VariableError. */
};

/**
 * @brief The UnitsError class.
 *
 * The UnitsError class.
 */
class UnitsError: public EntityError
{
public:
    /**
     * @brief Set the units for this units error.
     *
     * Set the @p units that this units error is relevant to.
     *
     * @param units A pointer to the units this units error is relevant to.
     */
    void setUnits(const UnitsPtr units)
    {
        mUnits = units;
    }

    /**
     * @brief Get the units for this units error.
     *
     * Get the units that this units error is relevant to.
     *
     * @return A pointer to the units that this units error was raised on.
     */
    UnitsPtr getUnits()
    {
        return mUnits;
    }

    /**
     * @brief Get a @c const reference to the units for this error.
     *
     * Returns a @c const reference to the units that this units
     * error is relevant to.
     *
     * @overload
     *
     * @return A @c const reference to the units that this
     * units error was raised on.
     */
    const UnitsPtr& getUnits() const
    {
        return mUnits;
    }

private:
    UnitsPtr mUnits; /**< Pointer to the units that the error occurred in. */
};

/**
 * @brief The ComponentError class.
 *
 * The ComponentError class.
 */
class ComponentError: public EntityError
{
public:
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
     * @brief Get the component for this component error.
     *
     * Get the component that this component error is relevant to.
     *
     * @return A pointer to the component that this component error was raised on.
     */
    ComponentPtr getComponent()
    {
        return mComponent;
    }

    /**
     * @brief Get a @c const reference to the component for this error.
     *
     * Returns a @c const reference to the component that this component
     * error is relevant to.
     *
     * @overload
     *
     * @return A @c const reference to the component that this
     * component error was raised on.
     */
    const ComponentPtr& getComponent() const
    {
        return mComponent;
    }

private:
    ComponentPtr mComponent; /**< Pointer to the component that the error occurred in. */
};

/**
 * @brief The ModelError class.
 *
 * The ModelError class.
 */
class ModelError: public EntityError
{
public:
    /**
     * @brief Set the @p model for this model error.
     *
     * Set the @p model that this model error is relevant to.
     *
     * @param model A pointer to the model that this model error is relevant to.
     */
    void setModel(const ModelPtr model)
    {
        mModel = model;
    }

    /**
     * @brief Get the model for this model error.
     *
     * Get the model that this model error is relevant to.
     *
     * @return A pointer to the model that this model error was raised on.
     */
    ModelPtr getModel()
    {
        return mModel;
    }

    /**
     * @brief Get a @c const reference to the model for this error.
     *
     * Returns a @c const reference to the model that this model
     * error is relevant to.
     *
     * @overload
     *
     * @return A @c const reference to the model that this
     * model error was raised on.
     */
    const ModelPtr& getModel() const
    {
        return mModel;
    }

private:
    ModelPtr mModel;
};

typedef std::shared_ptr<ComponentError> ComponentErrorPtr; /**< Type definition for shared component error pointer. */
typedef std::shared_ptr<EntityError> EntityErrorPtr; /**< Type definition for shared entity error pointer. */
typedef std::shared_ptr<ImportError> ImportErrorPtr; /**< Type definition for shared import error pointer. */
typedef std::shared_ptr<ModelError> ModelErrorPtr; /**< Type definition for shared model error pointer. */
typedef std::shared_ptr<UnitsError> UnitsErrorPtr; /**< Type definition for shared units error pointer. */
typedef std::shared_ptr<VariableError> VariableErrorPtr; /**< Type definition for shared variable error pointer. */

}

#endif /* LIBCELLML_LIBCELLML_LOGGERERROS_H_ */



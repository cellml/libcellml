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

#include <libcellml/libcellml_export.h>
#include <libcellml/types.h>

namespace libcellml {

/**
 * @brief The EntityError class
 *
 * Base class for errors used with the logger class.
 */
class LIBCELLML_EXPORT EntityError
{
public:
    /**
     * @brief Set the description for this entity error.
     *
     * Set the @c std::string @p description for this entity error as
     * raised by the parser.
     *
     * @param description The @c std::string description to set.
     */
    void setDescription(const std::string& description) { mDescription = description; }

    /**
     * @brief Get the description for this entity error.
     *
     * Get the @c std::string description for this entity error
     * raised by the parser.
     *
     * @return The @c std::string description of the error.
     */
    std::string getDescription() const { return mDescription; }

protected:
    std::string mDescription; /**< The string description of this entity error raised by the parser. */
};

class EntityElementError: public EntityError
{
};

/**
 * @brief The NamedEntityError class
 *
 * NamedEntityError class for all nameable loggable errors.
 */
class NamedEntityError: public EntityError
{
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
     * @brief Set the @p import for this ImportError.
     *
     * Set the @c ImportPtr @p import object for this ImportError.
     *
     * @param import A pointer to the import to set.
     */
    void setImport(ImportPtr import) { mImport = import; }

    /**
     * @brief Get the import for this ImportError.
     *
     * Get the @c ImportPtr import for this ImportError.
     *
     * @return A pointer to the import.
     */
    ImportPtr getImport() const { return mImport; }

private:
    ImportPtr mImport; /**< Pointer to the import that the error occurred in. */
};

/**
 * @brief The VariableError class.
 *
 * VariableError class for all variable loggable errors.
 */
class VariableError: public NamedEntityError
{
public:
    /**
     * @brief Set the component for the VariableError.
     *
     * Set the @p component this @c VariableError is associated with.
     * This is likely the parent component the variable is
     * expected to be contained within.
     *
     * @param component A pointer to the component that this @c VariableError is relevant to.
     */
    void setComponent(ComponentPtr component) { mComponent = component; }

    /**
     * @brief Get the component for the VariableError.
     *
     * Get the component this @c VariableError is associated with.
     * This is likely the parent component the variable is expected
     * to be contained within.
     *
     * @return A pointer to the component this @VariableError is relevant to.
     */
    ComponentPtr getComponent() const { return mComponent; }

    /**
     * @brief Set the variable for this VariableError.
     *
     * Set the @p variable that this @c VariableError is relevant to.
     *
     * @param variable A pointer to the variable this @c VariableError was raised on.
     */
    void setVariable(VariablePtr variable) { mVariable = variable; }

    /**
     * @brief Get the variable for this VariableError.
     *
     * Get the variable that this @c VariableError is relevant to.
     *
     * @return A pointer to the variable this @c VariableError was raised on.
     */
    VariablePtr getVariable() const { return mVariable; }

private:
    VariablePtr mVariable; /**< Pointer to the variable that the error occurred in. */
    ComponentPtr mComponent; /**< Pointer to the component associated with this VariableError. */
};

/**
 * @brief The ImportedEntityError class.
 *
 * The ImportedEntityError class.
 */
class ImportedEntityError: public NamedEntityError
{
};

/**
 * @brief The UnitsError class.
 *
 * The UnitsError class.
 */
class UnitsError: public ImportedEntityError
{
public:
    /**
     * @brief Set the units for this UnitsError.
     *
     * Set the @p units that this @c UnitsError is relevant to.
     *
     * @param units A pointer to the units to set.
     */
    void setUnits(UnitsPtr units) { mUnits = units; }

    /**
     * @brief Get the units for this UnitsError.
     *
     * Get the units that this @c UnitsError is relevant to.
     *
     * @return A pointer to the units that this @c UnitsError was raised on.
     */
    UnitsPtr getUnits() const { return mUnits; }

private:
    UnitsPtr mUnits; /**< Pointer to the units that the error occurred in. */
};

/**
 * @brief The ComponentEntityError class.
 *
 * The ComponentEntityError class.
 */
class ComponentEntityError: public ImportedEntityError
{
};

/**
 * @brief The ComponentError class.
 *
 * The ComponentError class.
 */
class ComponentError: public ComponentEntityError
{
public:
    /**
     * @brief Set the component for this @c ComponentError.
     *
     * Set the @p component that this @c ComponentError is relevant to.
     *
     * @param component A pointer to the component that this @c ComponentError was raised on.
     */
    void setComponent(ComponentPtr component) { mComponent = component; }

    /**
     * @brief Get the component for this @c ComponentError.
     *
     * Get the component that this @c ComponentError is relevant to.
     *
     * @return A pointer to the component that this @ComponentError was raised on.
     */
    ComponentPtr getComponent() const { return mComponent; }

private:
    ComponentPtr mComponent; /**< Pointer to the component that the error occurred in. */
};

/**
 * @brief The ModelError class.
 *
 * The ModelError class.
 */
class ModelError: public ComponentEntityError
{
public:
    /**
     * @brief Set the @p model for this @c ModelError.
     *
     * Set the @p model that this @c ModelError is relevant to.
     *
     * @param model A pointer to the model that this @c ModelError was raised on.
     */
    void setModel(ModelPtr model) { mModel = model; }

    /**
     * @brief Get the model for this @c ModelError.
     *
     * Get the model that this @c ModelError is relevant to.
     *
     * @return A pointer to the model that this @c ModelError was raised on.
     */
    ModelPtr getModel() const { return mModel; }

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



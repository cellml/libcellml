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
     * Get the @c std::string description for this entity error as
     * raised by the parser.
     *
     * @return The @c std::string description of the error.
     */
    std::string getDescription() const { return mDescription; }

protected:
    std::string mDescription; /**< The string descriptin of this entity error raised by the parser. */
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
     * @brief Set the import for this ImportError.
     *
     * Set the import for this ImportError.
     *
     * @param c A pointer to the import to set.
     */
    void setImport(ImportPtr import) { mImport = import; }

    /**
     * @brief Get the import for this ImportError.
     *
     * Get the import for this ImportError.
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
     * Set the component for the VariableError.
     *
     * @param c A pointer to the component to set.
     */
    void setComponent(ComponentPtr c) { mComponent = c; }

    /**
     * @brief Get the component for the VariableError.
     *
     * Get the component for this VariableError.
     *
     * @return A pointer to the component.
     */
    ComponentPtr getComponent() const { return mComponent; }

    /**
     * @brief Set the variable for this VariableError.
     *
     * Set the variable for this VariableError.
     *
     * @param c A pointer to the variable to set.
     */
    void setVariable(VariablePtr v) { mVariable = v; }

    /**
     * @brief Get the variable for this VariableError.
     *
     * Get the variable for this VariableError.
     *
     * @return A pointer to the variable.
     */
    VariablePtr getVariable() const { return mVariable; }

private:
    VariablePtr mVariable; /**< Pointer to the variable that the error occurred in. */
    ComponentPtr mComponent; /**< Pointer to the component that the variable belongs to. */
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
     * @brief Set the units for the UnitsError.
     *
     * Set the units for the UnitsError.
     *
     * @param u A pointer to the units to set.
     */
    void setUnits(UnitsPtr u) { mUnits = u; }

    /**
     * @brief Get the units for the UnitsError.
     *
     * Get the units for the UnitsError.
     *
     * @return A pointer to the units.
     */
    UnitsPtr getUnits() const { return mUnits; }

private:
    UnitsPtr mUnits;
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
     * @brief Set the component for the @c ComponentError.
     *
     * Set the component for this @c ComponentError.
     *
     * @param c A pointer to the component to set.
     */
    void setComponent(ComponentPtr c) { mComponent = c; }

    /**
     * @brief Get the component for the @c ComponentError.
     *
     * Get the component for this @c ComponentError.
     *
     * @return A pointer to the component.
     */
    ComponentPtr getComponent() const { return mComponent; }

private:
    ComponentPtr mComponent;
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
     * @brief Set the @p model for the @c ModelError.
     *
     * Set the @p model for this @c ModelError.
     *
     * @param model A pointer to the model to set.
     */
    void setModel(ModelPtr model) { mModel = model; }

    /**
     * @brief Get the model for the @c ModelError.
     *
     * Get the model for this @c ModelError.
     *
     * @return A pointer to the model.
     */
    ModelPtr getModel() const { return mModel; }

private:
    ModelPtr mModel;
};

typedef std::shared_ptr<EntityError> EntityErrorPtr; /**< Type definition for shared entity error pointer. */
typedef std::shared_ptr<VariableError> VariableErrorPtr; /**< Type definition for shared variable error pointer. */
typedef std::shared_ptr<UnitsError> UnitsErrorPtr; /**< Type definition for shared units error pointer. */
typedef std::shared_ptr<ComponentError> ComponentErrorPtr; /**< Type definition for shared component error pointer. */
typedef std::shared_ptr<ModelError> ModelErrorPtr; /**< Type definition for shared model error pointer. */
typedef std::shared_ptr<ImportError> ImportErrorPtr; /**< Type definition for shared model error pointer. */

}

#endif /* LIBCELLML_LIBCELLML_LOGGERERROS_H_ */



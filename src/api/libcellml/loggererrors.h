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
     * @brief Serialise the error message.
     *
     * Serialise the error to a @c std::string.
     *
     * @return A @c std::string representation of the error.
     */
    std::string serialise() const { return doSerialisation(); }

    /**
     * @brief Set the type of this attribute or element entity.
     *
     * Set the type of the element or attribute entity.
     *
     * @param value The @c std::string value to set.
     */
    void setType(const std::string& type) { mType = type; }

    /**
     * @brief Get the type of this attribute or element entity.
     *
     * Get the type of this element or attribute entity.
     *
     * @return The @c std::string representation of the type.
     */
    std::string getType() const { return mType; }

    /**
     * @brief Set label referring to the parent of this entity.
     *
     * Set a label to give information about the parent of this
     * element or attribute entity.
     *
     * @param value The @c std::string label to set.
     */
    void setParentLabel(const std::string& label) { mParentLabel = label; }

    /**
     * @brief Get a label referring to the parent of this entity.
     *
     * Get a label with information about the parent of this
     * element or attribute entity.
     *
     * @return label The @c std::string label.
     */
    std::string getParentLabel() const { return mParentLabel; }

    /**
     * @brief Set the value of the attribute.
     *
     * Set the value of the attribute.
     *
     * @param value The @c std::string value to set.
     */
    void setValue(const std::string& value) { mValue = value; }

    /**
     * @brief Get the value of the attribute.
     *
     * Get the value of the attribute.
     *
     * @return The @c std::string representation of the value.
     */
    std::string getValue() const { return mValue; }

protected:
    /**
     * @brief Virtual method for serialising error.
     *
     * Virtual method for serialising the error to a @c std::string.
     *
     * @return @c std::string representation of the object.
     */
    virtual std::string doSerialisation() const;

    std::string mType; /**< Element or attribute type for this entity represented as a @c std::string. */
    std::string mParentLabel; /**< Parent entity label represented as a @c std::string. */
    std::string mValue; /**< Attribute value represented as a @c std::string. */
};

class EntityElementError: public EntityError
{
protected:
    virtual std::string doSerialisation() const; /**< Virtual override method for doing serialisation. */
};

/**
 * @brief The NamedEntityError class
 *
 * NamedEntityError class for all nameable loggable errors.
 */
class NamedEntityError: public EntityError
{
public:
    /**
     * @brief Set the name for the error.
     *
     * Method to set the name attribute of the error.
     *
     * @param name A @c std::string to represent the name.
     */
    void setName(const std::string& name) { mName = name; }

    /**
     * @brief Get the name of the error.
     *
     * Method to get the name attribute of the error.
     *
     * @return  @c std::string representation of the error.
     */
    std::string getName() const { return mName; }

private:
    std::string mName; /**< Name attribute represented as a @c std::string. */
};

/**
 * @brief The ImportError class.
 *
 * ImportError class for all import loggable errors.
 */
class ImportError: public EntityError
{

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
     * @brief Set the variable for the VariableError.
     *
     * Set the variable for the VariableError.
     *
     * @param v A pointer to the variable to set.
     */
    void setVariable(VariablePtr v) { mVariable = v; }

    /**
     * @brief Get the variable the error applies to.
     *
     * Get the variable the error applies to.
     *
     * @return A pointer
     */
    VariablePtr getVariable() const { return mVariable; }

protected:
    virtual std::string doSerialisation() const; /**< Virtual override method for doing serialisation. */

private:
    VariablePtr mVariable; /**< Pointer to the variable that the error occurred in. */
    ComponentPtr mComponent; /**< Pointer to the component that the variable belongs to. */
};

/**
 * @brief The VariableElementError class.
 *
 * The VariableElementError class.
 */
class VariableElementError: public VariableError
{

};

/**
 * @brief The VariableAttributeError class.
 *
 * The VariableAttributeError class.
 */
class VariableAttributeError: public VariableElementError
{
protected:
    virtual std::string doSerialisation() const; /**< Virtual override method for doing serialisation. */
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
 * @brief The UnitsElementError class.
 *
 * The UnitsElementError class.
 */
class UnitsElementError: public UnitsError
{
protected:
    virtual std::string doSerialisation() const; /**< Virtual override method for doing serialisation. */
};

/**
 * @brief The UnitsAttributeError class.
 *
 * The UnitsAttributeError class.
 */
class UnitsAttributeError: public UnitsElementError
{
protected:
    virtual std::string doSerialisation() const; /**< Virtual override method for doing serialisation. */
};

/**
 * @brief The UnitsBaseUnitAttributeError class.
 *
 * The UnitsBaseUnitAttributeError class.
 */
class UnitsBaseUnitAttributeError: public UnitsAttributeError
{
protected:
    virtual std::string doSerialisation() const; /**< Virtual override method for doing serialisation. */
};

/**
 * @brief The UnitsExponentAttributeError class.
 *
 * The UnitsExponentAttributeError class.
 */
class UnitsExponentAttributeError: public UnitsAttributeError
{
protected:
    virtual std::string doSerialisation() const; /**< Virtual override method for doing serialisation. */
};

/**
 * @brief The UnitsMultiplierAttributeError class.
 *
 * The UnitsMultiplierAttributeError class.
 */
class UnitsMultiplierAttributeError: public UnitsAttributeError
{
protected:
    virtual std::string doSerialisation() const; /**< Virtual override method for doing serialisation. */
};

/**
 * @brief The UnitsOffsetAttributeError class.
 *
 * The UnitsOffsetAttributeError class.
 */
class UnitsOffsetAttributeError: public UnitsAttributeError
{
protected:
    virtual std::string doSerialisation() const; /**< Virtual override method for doing serialisation. */
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
 * @brief The ComponentElementError class.
 *
 * The ComponentElementError class.
 */
class ComponentElementError: public ComponentError
{
protected:
    virtual std::string doSerialisation() const; /**< Virtual override method for doing serialisation. */
};

/**
* @brief The ComponentAttributeError class.
*
* The ComponentAttributeError class.
*/
class ComponentAttributeError: public ComponentElementError
{
protected:
    virtual std::string doSerialisation() const; /**< Virtual override method for doing serialisation. */
};

/**
 * @brief The ModelError class.
 *
 * The ModelError class.
 */
class ModelError: public ComponentEntityError
{
public:
    void setDescription(const std::string& description) { mDescription = description; }

protected:
    virtual std::string doSerialisation() const; /**< Virtual override method for doing serialisation. */

private:
    std::string mDescription;
};

typedef std::shared_ptr<EntityError> EntityErrorPtr; /**< Type definition for shared entity error pointer. */
typedef std::shared_ptr<VariableError> VariableErrorPtr; /**< Type definition for shared variable error pointer. */
typedef std::shared_ptr<UnitsError> UnitsErrorPtr; /**< Type definition for shared units error pointer. */
typedef std::shared_ptr<ComponentError> ComponentErrorPtr; /**< Type definition for shared component error pointer. */
typedef std::shared_ptr<ComponentElementError> ComponentElementErrorPtr; /**< Type definition for shared component element error pointer. */
typedef std::shared_ptr<ComponentAttributeError> ComponentAttributeErrorPtr; /**< Type definition for shared component attribute error pointer. */
typedef std::shared_ptr<ModelError> ModelErrorPtr; /**< Type definition for shared model error pointer. */
typedef std::shared_ptr<UnitsElementError> UnitsElementErrorPtr; /**< Type definition for shared units element error pointer. */
typedef std::shared_ptr<UnitsAttributeError> UnitsAttributeErrorPtr; /**< Type definition for shared units attribute error pointer. */
typedef std::shared_ptr<UnitsBaseUnitAttributeError> UnitsBaseUnitAttributeErrorPtr; /**< Type definition for shared units base unit attribute error pointer. */
typedef std::shared_ptr<UnitsExponentAttributeError> UnitsExponentAttributeErrorPtr; /**< Type definition for shared units exponent attribute error pointer. */
typedef std::shared_ptr<UnitsMultiplierAttributeError> UnitsMultiplierAttributeErrorPtr; /**< Type definition for shared units multiplier attribute error pointer. */
typedef std::shared_ptr<UnitsOffsetAttributeError> UnitsOffsetAttributeErrorPtr; /**< Type definition for shared units offset attribute error pointer. */
typedef std::shared_ptr<EntityElementError> EntityElementErrorPtr; /**< Type definition for shared entity element error pointer. */
typedef std::shared_ptr<VariableAttributeError> VariableAttributeErrorPtr; /**< Type definition for shared variable attribute error pointer. */

}

#endif /* LIBCELLML_LIBCELLML_LOGGERERROS_H_ */



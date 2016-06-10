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

protected:
    /**
     * @brief Virtual method for serialising error.
     *
     * Virtual method for serialising the error to a @c std::string.
     *
     * @return @c std::string representation of the object.
     */
    virtual std::string doSerialisation() const;
};

class EntityElementError: public EntityError
{
public:
    void setElementType(const std::string& element_type) { mElementType = element_type; }
    std::string getElementType() const { return mElementType; }
    void setParentLabel(const std::string& label) { mLabel = label; }
    std::string getParentLabel() const { return mLabel; }

    virtual std::string doSerialisation() const; /**< Virtual override method for doing serialisation. */

private:
    std::string mElementType; /**< Element type attribute represented as a @c std::string. */
    std::string mLabel; /**< Label attribute represented as a @c std::string. */
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

protected:
    virtual std::string doSerialisation() const; /**< Virtual override method for doing serialisation. */

private:
    ComponentPtr mComponent; /**< Pointer to the component. */
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
 * @brief The UnitsAttributeError class.
 *
 * The UnitsAttributeError class.
 */
class UnitsAttributeError: public UnitsError
{
public:
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

private:
    std::string mValue;
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

};

/**
 * @brief The ModelError class.
 *
 * The ModelError class.
 */
class ModelError: public ComponentEntityError
{

};

typedef std::shared_ptr<EntityError> EntityErrorPtr; /**< Type definition for shared entity error pointer. */
typedef std::shared_ptr<VariableError> VariableErrorPtr; /**< Type definition for shared variable error pointer. */
typedef std::shared_ptr<UnitsError> UnitsErrorPtr; /**< Type definition for shared units error pointer. */
typedef std::shared_ptr<UnitsBaseUnitAttributeError> UnitsBaseUnitAttributeErrorPtr; /**< Type definition for shared units base unit attribute error pointer. */
typedef std::shared_ptr<UnitsExponentAttributeError> UnitsExponentAttributeErrorPtr; /**< Type definition for shared units exponent attribute error pointer. */
typedef std::shared_ptr<UnitsMultiplierAttributeError> UnitsMultiplierAttributeErrorPtr; /**< Type definition for shared units multiplier attribute error pointer. */
typedef std::shared_ptr<UnitsOffsetAttributeError> UnitsOffsetAttributeErrorPtr; /**< Type definition for shared units offset attribute error pointer. */
typedef std::shared_ptr<EntityElementError> EntityElementErrorPtr; /**< Type definition for shared entity element error pointer. */

}

#endif /* LIBCELLML_LIBCELLML_LOGGERERROS_H_ */



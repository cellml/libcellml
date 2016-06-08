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

#ifndef LIBCELLML_LIBCELLML_LOGGER_H_
#define LIBCELLML_LIBCELLML_LOGGER_H_

#include <string>

#include <libcellml/libcellml_export.h>
#include <libcellml/types.h>

namespace libcellml {

/**
 * @brief The Logger class.
 *
 * Base class for all serialisable libCellML classes.
 */
class LIBCELLML_EXPORT Logger
{
public:
    Logger(); /**< Constructor */
    ~Logger(); /**< Destructor */
    Logger(const Logger &rhs); /**< Copy constructor */
    Logger(Logger &&rhs); /**< Move constructor */
    Logger& operator=(Logger rhs); /**< Assignment operator */

    /**
     * @brief Clear the errors from the logger.
     *
     * Clear the errors from the logger.
     */
    void clearErrors();

    /**
     * @brief addError
     * @param err
     */
    void addError(EntityErrorPtr err);

    /**
     * @brief Get the number of errors.
     *
     * Return the number of errors currently stored in the logger.
     *
     * @return The number of errors.
     */
    size_t errorCount() const;

    /**
     * @brief Get error at index.
     *
     * Returns a reference to an error at the index @p index.  If the  index
     * is not valid a @c std::out_of_range exception is thrown.
     *
     * @param index The index of the error to return (zero-based).
     *
     * @return A reference to the error at the given index.
     */
    EntityErrorPtr getError(size_t index);

private:
    void swap(Logger &rhs); /**< Swap method required for C++ 11 move semantics. */

    struct LoggerImpl; /**< Forward declaration for pImpl idiom. */
    LoggerImpl* mPimpl; /**< Private member to implementation pointer */
};

/**
 * @brief The EntityError class
 *
 * Base class for errors used with the logger class.
 */
class EntityError
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

}

#endif /* LIBCELLML_LIBCELLML_ENTITY_H_ */



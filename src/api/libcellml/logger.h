/*
Copyright 2015 University of Auckland

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

    void clearErrors();

    void addError(EntityErrorPtr err);

    size_t errorCount() const;

    EntityErrorPtr getError(size_t index);

private:
    void swap(Logger &rhs); /**< Swap method required for C++ 11 move semantics. */

    struct LoggerImpl; /**< Forward declaration for pImpl idiom. */
    LoggerImpl* mPimpl; /**< Private member to implementation pointer */
};

class EntityError
{
public:
    std::string serialise() const { return doSerialisation(); }

protected:
    virtual std::string doSerialisation() const;
};

class NamedEntityError: public EntityError
{
public:
    void setName(const std::string& name) { mName = name; }
    std::string getName() const { return mName; }

private:
    std::string mName;
};

class ImportError: public EntityError
{

};

class VariableError: public NamedEntityError
{
public:
    void setComponent(ComponentPtr c) { mComponent = c; }

protected:
    virtual std::string doSerialisation() const;

private:
    ComponentPtr mComponent;
};

class ImportedEntityError: public NamedEntityError
{

};

class UnitsError: public ImportedEntityError
{

};

class ComponentEntityError: public ImportedEntityError
{

};

class ComponentError: public ComponentEntityError
{

};

class ModelError: public ComponentEntityError
{

};

}

#endif /* LIBCELLML_LIBCELLML_ENTITY_H_ */



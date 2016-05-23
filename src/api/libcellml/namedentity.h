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

#ifndef LIBCELLML_LIBCELLML_NAMEABLE_H
#define LIBCELLML_LIBCELLML_NAMEABLE_H

#include <string>

#include "libcellml/libcellml_export.h"
#include "libcellml/types.h"
#include "libcellml/entity.h"

namespace libcellml {

/**
 * @brief The NamedEntity class.
 *
 * Base class for all nameable libCellML classes.
 */
class LIBCELLML_EXPORT NamedEntity: public Entity
{
public:
    NamedEntity(); /**< Constructor */
    ~NamedEntity(); /**< Destructor */
    NamedEntity(const NamedEntity &rhs); /**< Copy constructor */
    NamedEntity(NamedEntity &&rhs); /**< Move constructor */
    NamedEntity& operator=(NamedEntity n); /**< Assignment operator */

    /**
     * @brief Set the name for the Entity.
     *
     * This method sets the name parameter of the Entity.  It does not check
     * the validity of the name.
     *
     * @param name A string to represent the name.
     */
    void setName(const std::string &name);

    /**
     * @brief Get the name of the Entity.
     *
     * Gets the name of the Entity as a string.
     *
     * @return @c std::string representation of the Entity name.
     */
    std::string getName() const;

private:
    void swap(NamedEntity &rhs); /**< Swap method required for C++ 11 move semantics. */

    std::string mName; /**< Entity name represented as a std::string. */
};

}

#endif // LIBCELLML_LIBCELLML_NAMEABLE_H


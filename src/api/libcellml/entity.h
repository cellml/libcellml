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

#ifndef LIBCELLML_LIBCELLML_ENTITY_H_
#define LIBCELLML_LIBCELLML_ENTITY_H_

#include <string>

#include "libcellml/libcellml_export.h"
#include "libcellml/enumerations.h"
#include "libcellml/types.h"

namespace libcellml {

/**
 * @brief The Entity class.
 *
 * Base class for all serialisable libCellML classes.
 */
class LIBCELLML_EXPORT Entity
{
public:
    Entity(); /**< Constructor */
    ~Entity(); /**< Destructor */
    Entity(const Entity &rhs); /**< Copy constructor */
    Entity(Entity &&rhs); /**< Move constructor */
    Entity& operator=(Entity e); /**< Assignment operator */

    /**
     * @brief Serialise entity to @c std::string.
     *
     * @param format The format to serialise the object to.
     *
     * @return @c std::string representation of the object.
     */
    std::string serialise(Format format) const;

    /**
     * @brief Returns the parent of the CellML Entity.
     *
     * @return A pointer to the entities parent if it has one,
     * otherwise the null pointer.
     */
    void *getParent() const;

    /**
     * @brief Sets the model as the parent of this entity.
     *
     * Set the parent of the entity to the model given.
     *
     * @param parent A raw pointer to a cellml::Model.
     */
    void setParent(Model *parent);

    /**
     * @brief Sets the component as the parent of this entity.
     *
     * Set the parent of the entity to the component given.
     *
     * @overload
     *
     * @param parent A raw pointer to a cellml::Component.
     */
    void setParent(Component *parent);

    /**
     * @brief Clear the pointer to the parent entity.
     *
     * Clears the pointer to the parent entity.
     */
    void clearParent();

    /**
     * @brief Test to see if the given component is a parent.
     *
     * Tests the given raw component pointer to determine if the entity or
     * any of its parent entities already has this component as a parent.
     * This allows for a test against creating cycles. If the given component
     * is a parent of the current entity then the result is @c true otherwise the
     * result is false.
     *
     * @param c The raw pointer to the component to test against.
     *
     * @return @c true if the entity has the given component as a parent, @c false otherwise.
     */
    bool hasParent(Component *c) const;

private:
    /**
     * @brief Virtual serialise method to be implemented by derived classes.
     *
     * Virtual serialise method for serialising a CellML object to a @c std::string.
     *
     * @param format The format to serialise the object to.
     *
     * @return @c std::string representation of the object.
     */
    virtual std::string doSerialisation(Format format) const;

    void swap(Entity &rhs); /**< Swap method required for C++ 11 move semantics. */

    Model *mParentModel; /**< Pointer to parent model. */
    Component *mParentComponent; /**< Pointer to component model. */
};

}

#endif /* LIBCELLML_LIBCELLML_ENTITY_H_ */



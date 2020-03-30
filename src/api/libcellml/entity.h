/*
Copyright libCellML Contributors

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

#pragma once

#include <string>

#include "libcellml/exportdefinitions.h"
#include "libcellml/types.h"

namespace libcellml {

/**
 * @brief The Entity class.
 *
 * Base class for all libCellML core classes.
 */
class LIBCELLML_EXPORT Entity
{
public:
    virtual ~Entity(); /**< Destructor */
    Entity(const Entity &rhs) = delete; /**< Copy constructor */
    Entity(Entity &&rhs) noexcept = delete; /**< Move constructor */
    Entity &operator=(Entity rhs) = delete; /**< Assignment operator */

    /**
     * @brief Set the @p id document identifier for this entity.
     *
     * Set the @p id document identifier for this entity using a @c std::string.
     *
     * @sa id
     *
     * @param id The @c std::string document identifier to set.
     */
    void setId(const std::string &id);

    /**
     * @brief Get the document identifier for this entity.
     *
     * Get the string corresponding with the @c id document identifier for this entity.
     * If no @c id has been set, returns an empty string.
     *
     * @sa setId
     *
     * @return The @c std::string document identifier for this entity.
     */
    std::string id() const;

    /**
     * @brief Returns the parent of the CellML Entity.
     *
     * @return A pointer to the entity's parent if it has one,
     * otherwise it returns the null pointer.
     */
    EntityPtr parent() const;

    /**
     * @brief Sets the entity as the parent of this entity.
     *
     * Set the parent of the entity to the entity given.
     *
     * @param parent An @c Entity.
     */
    void setParent(const EntityPtr &parent);

    /**
     * @brief Clear the pointer to the parent entity.
     *
     * Clears the pointer to the parent entity.
     */
    void removeParent();

    /**
     * @brief Test to see if the given entity has a parent.
     *
     * Tests the given entity to determine if the entity has a parent.
     * If the entity has a parent then @c true is returned otherwise
     * @c false is returned.m
     *
     * @return @c true if this entity has a parent, @c false otherwise.
     */
    bool hasParent() const;

    /**
     * @brief Test to see if the given entity is an ancestor of this entity.
     *
     * Tests the given entity to determine if the entity or
     * any of its parent entities already has this entity as a parent.
     * This allows for a test against creating cycles. If the given entity
     * is a parent of the current entity then the result is @c true otherwise the
     * result is false.
     *
     * @param component The entity to test against.
     *
     * @return @c true if this entity has the given entity as a parent, @c false otherwise.
     */
    bool hasAncestor(const EntityPtr &entity) const;

protected:
    Entity(); /**< Constructor */

private:
    struct EntityImpl;
    EntityImpl *mPimpl;
};

} // namespace libcellml

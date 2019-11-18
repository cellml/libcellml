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

#include "libcellml/entity.h"

#include "libcellml/component.h"
#include "libcellml/componententity.h"

namespace libcellml {

using EntityWeakPtr = std::weak_ptr<Entity>; /**< Type definition for weak entity pointer. */

/**
 * @brief The Entity::EntityImpl struct.
 *
 * The private implementation for the Entity class.
 */
struct Entity::EntityImpl
{
    EntityWeakPtr mParent; /**< Pointer to parent. */
    std::string mId; /**< String document identifier for this entity. */
};

Entity::Entity()
    : mPimpl(new EntityImpl())
{
    mPimpl->mParent = {};
}

Entity::~Entity()
{
    delete mPimpl;
}

void Entity::setId(const std::string &id)
{
    mPimpl->mId = id;
}

std::string Entity::id() const
{
    return mPimpl->mId;
}

EntityPtr Entity::parent() const
{
    return mPimpl->mParent.lock();
}

void Entity::setParent(const EntityPtr &parent)
{
    mPimpl->mParent = parent;
}

void Entity::removeParent()
{
    mPimpl->mParent = {};
}

bool Entity::hasParent() const
{
    bool hasParent = false;
    EntityPtr parent = mPimpl->mParent.lock();
    if (parent) {
        hasParent = true;
    }

    return hasParent;
}

bool Entity::hasAncestor(const EntityPtr &entity) const
{
    bool hasAncestor = false;
    EntityPtr parent = mPimpl->mParent.lock();
    if (parent == entity) {
        hasAncestor = true;
    } else if (parent) {
        hasAncestor = parent->hasAncestor(entity);
    }

    return hasAncestor;
}

} // namespace libcellml

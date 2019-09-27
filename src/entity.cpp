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

#include "libcellml/component.h"
#include "libcellml/componententity.h"
#include "libcellml/entity.h"
#include "libcellml/model.h"

namespace libcellml {

using ModelWeakPtr = std::weak_ptr<Model>; /**< Type definition for weak model pointer. */
using ComponentWeakPtr = std::weak_ptr<Component>; /**< Type definition for weak component pointer. */
using EntityWeakPtr = std::weak_ptr<Entity>;

/**
 * @brief The Entity::EntityImpl struct.
 *
 * The private implementation for the Entity class.
 */
struct Entity::EntityImpl
{
    EntityWeakPtr mParent;

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

Entity::Entity(const Entity &rhs)
    : mPimpl(new EntityImpl())
{
    mPimpl->mParent = rhs.mPimpl->mParent;
    mPimpl->mId = rhs.mPimpl->mId;
}

Entity::Entity(Entity &&rhs) noexcept
    : mPimpl(rhs.mPimpl)
{
    rhs.mPimpl = nullptr;
}

Entity &Entity::operator=(Entity rhs)
{
    rhs.swap(*this);
    return *this;
}

void Entity::swap(Entity &rhs)
{
    std::swap(mPimpl, rhs.mPimpl);
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

void Entity::clearParent()
{
    mPimpl->mParent = {};
}

bool Entity::hasParent(const EntityPtr &entity) const
{
    bool hasParent = false;
    EntityPtr parent = mPimpl->mParent.lock();
    if (parent == entity) {
        hasParent = true;
    }

    return hasParent;
}

bool Entity::hasAncestor(const EntityPtr &entity) const
{
    bool hasParent = false;
    EntityPtr parent = mPimpl->mParent.lock();
    if (parent == entity) {
        hasParent = true;
    } else if (parent) {
        hasParent = parent->hasAncestor(entity);
    }

    return hasParent;
}

} // namespace libcellml

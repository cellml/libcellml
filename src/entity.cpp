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

#include "entity_p.h"

namespace libcellml {

Entity::Entity()
    : mPimpl(new EntityPrivate())
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

bool Entity::equal(const EntityPtr &other) const
{
    return doEqual(other);
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

bool Entity::doEqual(const EntityPtr &other) const
{
    if (other == nullptr) {
        return false;
    }
    return mPimpl->mId == other->id();
}

} // namespace libcellml

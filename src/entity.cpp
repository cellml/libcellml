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

struct Entity::EntityImpl
{
    Model *mParentModel; /**< Pointer to parent model. */
    Component *mParentComponent; /**< Pointer to component model. */
    std::string mId; /**< String document identifier for this entity. */
};

Entity::Entity()
    : mPimpl(new EntityImpl())
{
    mPimpl->mParentModel = nullptr;
    mPimpl->mParentComponent = nullptr;
}

Entity::~Entity()
{
    delete mPimpl;
}

Entity::Entity(const Entity& rhs)
    : mPimpl(new EntityImpl())
{
    mPimpl->mParentComponent = rhs.mPimpl->mParentComponent;
    mPimpl->mParentModel = rhs.mPimpl->mParentModel;
    mPimpl->mId = rhs.mPimpl->mId;
}

Entity::Entity(Entity &&rhs)
    : mPimpl(rhs.mPimpl)
{
    rhs.mPimpl = nullptr;
}

Entity& Entity::operator=(Entity e)
{
    e.swap(*this);
    return *this;
}

void Entity::swap(Entity &rhs)
{
    std::swap(this->mPimpl, rhs.mPimpl);
}

void Entity::setId(const std::string &id)
{
    mPimpl->mId = id;
}

std::string Entity::getId() const
{
    return mPimpl->mId;
}

void *Entity::getParent() const {
    void *parent = nullptr;
    if (mPimpl->mParentComponent) {
        parent = mPimpl->mParentComponent;
    } else if (mPimpl->mParentModel) {
        parent = mPimpl->mParentModel;
    }
    return parent;
}

void Entity::setParent(Component *parent) {
    mPimpl->mParentComponent = parent;
}

void Entity::setParent(Model *parent) {
    mPimpl->mParentModel = parent;
}

void Entity::clearParent() {
    mPimpl->mParentComponent = nullptr;
    mPimpl->mParentModel = nullptr;
}

bool Entity::hasParent(Component *c) const
{
    bool hasParent = false;
    if (mPimpl->mParentComponent == c) {
        hasParent = true;
    } else if (mPimpl->mParentComponent) {
        hasParent = mPimpl->mParentComponent->hasParent(c);
    }

    return hasParent;
}

}

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

#include "libcellml/entity.h"

#include "libcellml/component.h"
#include "libcellml/componententity.h"

namespace libcellml {

Entity::Entity()
    : mParentModel(nullptr)
    , mParentComponent(nullptr)
{
}

Entity::~Entity()
{
}

Entity::Entity(const Entity& rhs)
{
    mParentComponent = rhs.mParentComponent;
    mParentModel = rhs.mParentModel;
}

Entity::Entity(Entity &&rhs)
{
    mParentComponent = std::move(rhs.mParentComponent);
    mParentModel = std::move(rhs.mParentModel);
}

Entity& Entity::operator=(Entity e)
{
    e.swap(*this);
    return *this;
}

void Entity::swap(Entity &rhs)
{
    std::swap(this->mParentComponent, rhs.mParentComponent);
    std::swap(this->mParentModel, rhs.mParentModel);
}

std::string Entity::doSerialisation(Format /* format */) const
{
    return "";
}

std::string Entity::serialise(Format format) const
{
    return doSerialisation(format);
}

void *Entity::getParent() const {
    void *parent = 0;
    if (mParentComponent) {
        parent = mParentComponent;
    } else if (mParentModel) {
        parent = mParentModel;
    }
    return parent;
}

void Entity::setParent(Component *parent) {
    mParentComponent = parent;
}

void Entity::setParent(Model *parent) {
    mParentModel = parent;
}

void Entity::clearParent() {
    mParentComponent = nullptr;
    mParentModel = nullptr;
}

bool Entity::hasParent(Component *c) const
{
    bool hasParent = false;
    if (mParentComponent == c) {
        hasParent = true;
    } else if (mParentComponent) {
        hasParent = mParentComponent->hasParent(c);
    }

    return hasParent;
}

}

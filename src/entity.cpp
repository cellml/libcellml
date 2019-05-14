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
#include "libcellml/model.h"

namespace libcellml {

typedef std::weak_ptr<Model> ModelWeakPtr; /**< Type definition for weak model pointer. */
typedef std::weak_ptr<Component> ComponentWeakPtr; /**< Type definition for weak component pointer. */

/**
 * @brief The Entity::EntityImpl struct.
 *
 * The private implementation for the Entity class.
 */
struct Entity::EntityImpl
{
    ModelWeakPtr mParentModel; /**< Pointer to parent model. */
    ComponentWeakPtr mParentComponent; /**< Pointer to component model. */
    std::string mId; /**< String document identifier for this entity. */
};

Entity::Entity()
    : mPimpl(new EntityImpl())
{
    mPimpl->mParentModel = {};
    mPimpl->mParentComponent = {};
}

Entity::~Entity()
{
    delete mPimpl;
}

Entity::Entity(const Entity &rhs)
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
    std::swap(mPimpl, rhs.mPimpl);
}

void Entity::setId(const std::string &id)
{
    mPimpl->mId = id;
}

std::string Entity::getId() const
{
    return mPimpl->mId;
}

ModelPtr Entity::getParentModel() const {
    return mPimpl->mParentModel.lock();
}

ComponentPtr Entity::getParentComponent() const {
    return mPimpl->mParentComponent.lock();
}

void Entity::setParent(ComponentPtr parent) {
    mPimpl->mParentComponent = parent;
}

void Entity::setParent(ModelPtr parent) {
    mPimpl->mParentModel = parent;
}

void Entity::clearParent() {
    mPimpl->mParentComponent = {};
    mPimpl->mParentModel = {};
}

bool Entity::hasParent(ComponentPtr c) const
{
    bool hasParent = false;
    ComponentPtr parentComponent = mPimpl->mParentComponent.lock();
    if (parentComponent == c) {
        hasParent = true;
    } else if (parentComponent) {
        hasParent = parentComponent->hasParent(c);
    }

    return hasParent;
}

}

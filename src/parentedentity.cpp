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

using ParentedEntityWeakPtr = std::weak_ptr<ParentedEntity>; /**< Type definition for weak entity pointer. */

/**
 * @brief The Entity::EntityImpl struct.
 *
 * The private implementation for the Entity class.
 */
struct ParentedEntity::ParentedEntityImpl
{
    ParentedEntityWeakPtr mParent; /**< Pointer to parent. */
};

ParentedEntity::ParentedEntity()
    : mPimpl(new ParentedEntityImpl())
{
    mPimpl->mParent = {};
}

ParentedEntity::~ParentedEntity()
{
    delete mPimpl;
}

ParentedEntityPtr ParentedEntity::parent() const
{
    return mPimpl->mParent.lock();
}

void ParentedEntity::setParent(const ParentedEntityPtr &parent)
{
    mPimpl->mParent = parent;
}

void ParentedEntity::removeParent()
{
    mPimpl->mParent = {};
}

bool ParentedEntity::hasParent() const
{
    bool hasParent = false;
    EntityPtr parent = mPimpl->mParent.lock();
    if (parent) {
        hasParent = true;
    }

    return hasParent;
}

bool ParentedEntity::hasAncestor(const ParentedEntityPtr &entity) const
{
    bool hasAncestor = false;
    ParentedEntityPtr parent = mPimpl->mParent.lock();
    if (parent == entity) {
        hasAncestor = true;
    } else if (parent) {
        hasAncestor = parent->hasAncestor(entity);
    }

    return hasAncestor;
}

} // namespace libcellml

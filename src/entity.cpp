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
    std::string mId; /**< String document identifier for this entity. */
};

Entity::Entity()
    : mPimpl(new EntityImpl())
{
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

void Entity::removeId()
{
    mPimpl->mId = "";
}

bool Entity::equals(const EntityPtr &other) const
{
    return doEquals(other);
}

bool Entity::doEquals(const EntityPtr &other) const
{
    if (other == nullptr) {
        return false;
    }
    return mPimpl->mId == other->id();
}

} // namespace libcellml

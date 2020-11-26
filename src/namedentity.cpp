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

#include "libcellml/namedentity.h"

#include "libcellml/component.h"
#include "libcellml/componententity.h"

namespace libcellml {

/**
 * @brief The NamedEntity::NamedEntityImpl struct.
 *
 * The private implementation for the NamedEntity class.
 */
struct NamedEntity::NamedEntityImpl
{
    std::string mName; /**< Entity name represented as a std::string. */
};

NamedEntity::NamedEntity()
    : mPimpl(new NamedEntityImpl())
{
}

NamedEntity::~NamedEntity()
{
    delete mPimpl;
}

bool NamedEntity::doEqual(const EntityPtr &other) const
{
    auto namedEntity = std::dynamic_pointer_cast<NamedEntity>(other);
    if (namedEntity) {
        return name() == namedEntity->name();
    }
    return false;
}

void NamedEntity::setName(const std::string &name)
{
    mPimpl->mName = name;
}

std::string NamedEntity::name() const
{
    return mPimpl->mName;
}

} // namespace libcellml

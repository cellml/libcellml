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

#include "libcellml/entity.h"

namespace libcellml {

using EntityWeakPtr = std::weak_ptr<Entity>; /**< Type definition for weak entity pointer. */

/**
 * @brief The EntityPrivate class.
 *
 * The private implementation for the Entity class.
 */
class EntityPrivate
{
public:
    virtual ~EntityPrivate() {};
    EntityWeakPtr mParent; /**< Pointer to parent. */
    std::string mId; /**< String document identifier for this entity. */
};

}

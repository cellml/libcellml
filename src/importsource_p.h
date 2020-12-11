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

#include "libcellml/namedentity.h"

#include "entity_p.h"
#include "internaltypes.h"

namespace libcellml {

using ImportedEntityWeakPtr = std::weak_ptr<ImportedEntity>;

/**
 * @brief The ImportSource::ImportSourceImpl struct.
 *
 * The private implementation for the ImportSource class.
 */
class ImportSourcePrivate : public EntityPrivate
{
public:
    std::string mUrl;
    ModelWeakPtr mModel;
    std::vector<size_t> mComponents;
    std::vector<size_t> mUnits;
    std::vector<ImportedEntityWeakPtr> mImports;

    void removeItem(std::vector<ImportedEntityWeakPtr>::iterator &it);
};

}

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

#include "libcellml/model.h"

namespace libcellml {

/**
 * @brief The Model::ModelImpl struct.
 *
 * This struct is the private implementation struct for the Model class.  Separating
 * the implementation from the definition allows for greater flexibility when
 * distributing the code.
 */
struct Model::ModelImpl
{
    std::vector<UnitsPtr> mUnits;

    std::vector<UnitsPtr>::const_iterator findUnits(const std::string &name) const;
    std::vector<UnitsPtr>::const_iterator findUnits(const UnitsPtr &units) const;

    bool equalUnits(const ModelPtr &other) const;

    bool linkComponentVariableUnits(const ComponentPtr &component,
                                    std::vector<IssuePtr> &issueList);
    bool traverseTreeLinkingUnits(const ComponentEntityPtr &componentEntity);
    bool traverseTreeLinkingUnits(const ComponentEntityPtr &componentEntity,
                                  std::vector<IssuePtr> &issueList);
};

} // namespace libcellml

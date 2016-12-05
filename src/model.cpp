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

#include "libcellml/model.h"

#include <map>
#include <stack>
#include <utility>
#include <vector>

#include "libcellml/component.h"
#include "libcellml/import.h"
#include "libcellml/variable.h"

namespace libcellml {

Model::Model()
{
}

Model::~Model()
{
}

Model::Model(const Model& rhs)
    : ComponentEntity(rhs)
{
}

Model::Model(Model &&rhs)
    : ComponentEntity(std::move(rhs))
{
}

Model& Model::operator=(Model m)
{
    ComponentEntity::operator= (m);
    return *this;
}

void Model::doAddComponent(const ComponentPtr &c)
{
    // Check for cycles.
    if (!hasParent(c.get())) {
        c->setParent(this);
        ComponentEntity::doAddComponent(c);
    }
}

}

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

#include "commonutils.h"

#include <limits>

#include "libcellml/component.h"
#include "libcellml/model.h"

#ifndef TEST_UTILS
namespace libcellml {
#endif

libcellml::ModelPtr owningModel(const libcellml::ParentedEntityConstPtr &entity)
{
    auto parent = entity->parent();
    while (parent != nullptr) {
        auto model = std::dynamic_pointer_cast<libcellml::Model>(parent);
        if (model != nullptr) {
            return model;
        }
        parent = parent->parent();
    }

    return nullptr;
}

libcellml::ComponentPtr owningComponent(const libcellml::ParentedEntityConstPtr &entity)
{
    return std::dynamic_pointer_cast<libcellml::Component>(entity->parent());
}

double epsilon()
{
    static const double epsilonValue = 100.0 * std::numeric_limits<double>::epsilon();

    return epsilonValue;
    // Note: ideally, we would be returning std::numeric_limits<double>::epsilon() which is approximately 2.220446e-16,
    //       but we need to use a slightly larger value to account for the fact that we want to be able to compare
    //       numbers from SymEngine.
}

#ifndef TEST_UTILS
} // namespace libcellml
#endif

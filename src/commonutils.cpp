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

#include <cmath>

#include "libcellml/component.h"
#include "libcellml/model.h"

#ifndef TEST_UTILS
namespace libcellml {
#endif

libcellml::ModelPtr owningModel(const libcellml::ParentedEntityConstPtr &entity)
{
    auto model = std::dynamic_pointer_cast<libcellml::Model>(entity->parent());
    auto component = owningComponent(entity);
    while ((model == nullptr) && (component != nullptr)) {
        model = std::dynamic_pointer_cast<libcellml::Model>(component->parent());
        component = owningComponent(component);
    }

    return model;
}

libcellml::ComponentPtr owningComponent(const libcellml::ParentedEntityConstPtr &entity)
{
    return std::dynamic_pointer_cast<libcellml::Component>(entity->parent());
}

uint64_t ulpsDistance(double a, double b)
{
    static const auto max = std::numeric_limits<uint64_t>::max();

    // Max distance for NaN.
    if (std::isnan(a) || std::isnan(b)) {
        return max;
    }

    // If one's infinite and they're not equal, max distance.
    if (std::isinf(a) != std::isinf(b)) {
        return max;
    }

    static const int SIZE_OF_DOUBLE = sizeof(double);

    uint64_t ia;
    uint64_t ib;
    memcpy(&ia, &a, SIZE_OF_DOUBLE);
    memcpy(&ib, &b, SIZE_OF_DOUBLE);

    // Return the absolute value of the distance in ULPs.
    uint64_t distance = max;
    if (ia < ib) {
        distance = ib + ~ia + 1;
    } else {
        distance = ia + ~ib + 1;
    }
    return distance;
}

bool areNearlyEqual(double a, double b)
{
    static const double fixedEpsilon = std::numeric_limits<double>::epsilon();
    static const ptrdiff_t ulpsEpsilon = 1;

    if (fabs(a - b) <= fixedEpsilon) {
        return true;
    }

    // If they are not the same sign then return false.
    if ((a < 0.0) != (b < 0.0)) {
        return false;
    }

    return ulpsDistance(a, b) <= ulpsEpsilon;
}

#ifndef TEST_UTILS
} // namespace libcellml
#endif

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

#include <string>

#include "libcellml/exportdefinitions.h"
#include "libcellml/entity.h"
#include "libcellml/types.h"

namespace libcellml {

/**
 * @brief The When class.
 * Class for When.
 */
class LIBCELLML_EXPORT When: public Entity
{
public:
    When(); /**< Constructor */
    ~When(); /**< Destructor */
    When(const When &rhs); /**< Copy constructor */
    When(When &&rhs); /**< Move constructor */
    When& operator=(When n); /**< Assignment operator */

private:
    void swap(When &rhs); /**< Swap method required for C++ 11 move semantics. */

    struct WhenImpl; /**< Forward declaration for pImpl idiom. */
    WhenImpl *mPimpl; /**< Private member to implementation pointer */
};

}

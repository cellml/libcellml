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
 * @brief The Reset class.
 * Class for Reset.
 */
class LIBCELLML_EXPORT Reset: public Entity
{
public:
    Reset(); /**< Constructor */
    ~Reset(); /**< Destructor */
    Reset(const Reset &rhs); /**< Copy constructor */
    Reset(Reset &&rhs); /**< Move constructor */
    Reset& operator=(Reset n); /**< Assignment operator */

    /**
     * @brief Set the order for this reset.
     *
     * Sets the order that for this reset.
     *
     * @param order The order to set.
     */
    void setOrder(int order);

    /**
     * @brief Get the order for this reset.
     *
     * Returns the order of this reset.
     *
     * @return The order.
     */
    int getOrder() const;

private:
    void swap(Reset &rhs); /**< Swap method required for C++ 11 move semantics. */

    struct ResetImpl; /**< Forward declaration for pImpl idiom. */
    ResetImpl *mPimpl; /**< Private member to implementation pointer */
};

}

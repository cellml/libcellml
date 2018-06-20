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
#include "libcellml/exportdefinitions.h"

namespace libcellml {

/**
 * @brief The OrderedEntity class.
 *
 * Base class for all nameable libCellML classes.
 */
class LIBCELLML_EXPORT OrderedEntity: public Entity
{
public:
    OrderedEntity(); /**< Constructor */
    ~OrderedEntity(); /**< Destructor */
    OrderedEntity(const OrderedEntity &rhs); /**< Copy constructor */
    OrderedEntity(OrderedEntity &&rhs); /**< Move constructor */
    OrderedEntity& operator=(OrderedEntity n); /**< Assignment operator */

    /**
     * @brief Set the order of this entity.
     *
     * Sets the order for this entity.
     *
     * @param order The order to set.
     */
    void setOrder(int order);

    /**
     * @brief Get the order of this entity.
     *
     * Returns the order of this entity.
     *
     * @return The order.
     */
    int getOrder() const;

    /**
     * @brief Mark the order as unset.
     *
     * Marks the order value as unset .
     */
    void unsetOrder();

    /**
     * @brief Test to determine whether the order is set or unset.
     *
     * Returns whether the order value is in a set state or not.
     *
     * @return @c true if the order is set, @c false otherwise.
     */
    bool isOrderSet();

private:
    void swap(OrderedEntity &rhs); /**< Swap method required for C++ 11 move semantics. */

    struct OrderedEntityImpl; /**< Forward declaration for pImpl idiom. */
    OrderedEntityImpl *mPimpl; /**< Private member to implementation pointer. */

};

}

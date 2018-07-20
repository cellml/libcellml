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

#include "libcellml/orderedentity.h"

#include <utility>

namespace libcellml {

/**
 * @brief The OrderedEntity::OrderedEntityImpl struct.
 *
 * The private implementation for the OrderedEntity class.
 */
struct OrderedEntity::OrderedEntityImpl
{
    int mOrder;
    bool mOrderSet;
};

OrderedEntity::OrderedEntity()
    : mPimpl(new OrderedEntityImpl())
{
    mPimpl->mOrder = 0;
    mPimpl->mOrderSet = false;
}

OrderedEntity::~OrderedEntity()
{
    delete mPimpl;
}

OrderedEntity::OrderedEntity(const OrderedEntity &rhs)
    : Entity(rhs)
    , mPimpl(new OrderedEntityImpl())
{
    mPimpl->mOrder = rhs.mPimpl->mOrder;
    mPimpl->mOrderSet = rhs.mPimpl->mOrderSet;
}

OrderedEntity::OrderedEntity(OrderedEntity &&rhs)
    :  Entity(std::move(rhs))
    , mPimpl(rhs.mPimpl)
{
    rhs.mPimpl = nullptr;
}

OrderedEntity& OrderedEntity::operator=(OrderedEntity e)
{
    Entity::operator= (e);
    e.swap(*this);
    return *this;
}

void OrderedEntity::swap(OrderedEntity &rhs)
{
    std::swap(this->mPimpl, rhs.mPimpl);
}

void OrderedEntity::setOrder(int order)
{
    mPimpl->mOrder = order;
    mPimpl->mOrderSet = true;
}

int OrderedEntity::getOrder() const
{
    return mPimpl->mOrder;
}

void OrderedEntity::unsetOrder()
{
    mPimpl->mOrderSet = false;
}

bool OrderedEntity::isOrderSet()
{
    return mPimpl->mOrderSet;
}

}

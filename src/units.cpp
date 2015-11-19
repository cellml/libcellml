/*
Copyright 2015 University of Auckland

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.Some license of other
*/
#include "libcellml/units.h"

namespace libcellml {

/**
 * @brief The Units::UnitsImpl struct.
 * The private implementation for the Units class.
 */
struct Units::UnitsImpl
{
};

Units::Units()
    : mPimpl(new UnitsImpl())
{
}

Units::~Units()
{
    delete mPimpl;
}

Units::Units(const Units& rhs)
    : NamedEntity(rhs)
    , mPimpl(new UnitsImpl())
{
}

Units::Units(Units &&rhs)
    : NamedEntity(std::move(rhs))
    , mPimpl(rhs.mPimpl)
{
    rhs.mPimpl = nullptr;
}

Units& Units::operator=(Units e)
{
    NamedEntity::operator= (e);
    e.swap(*this);
    return *this;
}

void Units::swap(Units &rhs)
{
    std::swap(this->mPimpl, rhs.mPimpl);
}

bool Units::isBaseUnit() const
{
    return false;
}

void Units::setBaseUnit(bool /* state */)
{

}

void Units::addUnit(const std::string & /* units */, PREFIXES /* prefix */, double /* exponent */,
             double /* multiplier */, double /* offset */)
{

}

void Units::addUnit(const std::string & /* units */, int /* prefix */, double /* exponent */,
             double /* multiplier */, double /* offset */)
{

}

void Units::addUnit(const std::string & /* units */, PREFIXES /* prefix */)
{

}

void Units::addUnit(const std::string & /* units */, int /* prefix */)
{

}

void Units::addUnit(const std::string & /*units */, double /* exponent */)
{

}

void Units::addUnit(const std::string & /* units */)
{

}

}

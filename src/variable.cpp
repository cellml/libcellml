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
#include "libcellml/variable.h"

#include "libcellml/units.h"


namespace libcellml {

/**
 * @brief The Variable::VariableImpl struct.
 * The private implementation for the Variable class.
 */
struct Variable::VariableImpl
{
    double mInitialValue;
    UnitsPtr mUnits;
};

Variable::Variable()
    : mPimpl(new VariableImpl())
{
}

Variable::~Variable()
{
    delete mPimpl;
}

Variable::Variable(const Variable& rhs)
    : NamedEntity(rhs)
    , mPimpl(new VariableImpl())
{
}

Variable::Variable(Variable &&rhs)
    : NamedEntity(std::move(rhs))
    , mPimpl(rhs.mPimpl)
{
    rhs.mPimpl = nullptr;
}

Variable& Variable::operator=(Variable e)
{
    NamedEntity::operator= (e);
    e.swap(*this);
    return *this;
}

void Variable::swap(Variable &rhs)
{
    std::swap(this->mPimpl, rhs.mPimpl);
}

std::string Variable::doSerialisation(FORMATS format) const
{
    std::string repr = "";
    if (format == FORMAT_XML) {
        repr += "<variable";
        if (getName().length()) {
            repr += " name=\"" + getName() + "\"";
            if (getUnits() != nullptr) {
                repr += " units=\"" + getUnits()->getName() + "\"";
            }
        }
        repr += "/>";
    }
    return repr;
}

void Variable::setUnits(const UnitsPtr &u)
{
    mPimpl->mUnits = u;
}

UnitsPtr Variable::getUnits() const
{
    return mPimpl->mUnits;
}

}

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
limitations under the License.
*/

#include "libcellml/import.h"

namespace libcellml {

/**
 * @brief The Import::ImportImpl struct.
 *
 * The private implementation for the Import class.
 */
struct Import::ImportImpl
{
    std::string mReference;
};

Import::Import()
    : mPimpl(new ImportImpl())
{
}

Import::~Import()
{
    delete mPimpl;
}

Import::Import(const Import& rhs)
    : Entity(rhs)
    , mPimpl(new ImportImpl())
{
    mPimpl->mReference = rhs.mPimpl->mReference;
}

Import::Import(Import &&rhs)
    : Entity(std::move(rhs))
    , mPimpl(rhs.mPimpl)
{
    rhs.mPimpl = nullptr;
}

Import& Import::operator=(Import e)
{
    Entity::operator= (e);
    e.swap(*this);
    return *this;
}

void Import::swap(Import &rhs)
{
    std::swap(this->mPimpl, rhs.mPimpl);
}

void Import::setSource(const std::string &reference)
{
    mPimpl->mReference = reference;
}

std::string Import::getSource() const
{
    return mPimpl->mReference;
}

}

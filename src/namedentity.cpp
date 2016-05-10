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
#include "libcellml/namedentity.h"

#include "libcellml/component.h"
#include "libcellml/componententity.h"

namespace libcellml {

NamedEntity::NamedEntity()
    : mName("")
{
}

NamedEntity::~NamedEntity()
{
}

NamedEntity::NamedEntity(const NamedEntity& rhs)
    : Entity(rhs)
{
    mName = rhs.mName;
}

NamedEntity::NamedEntity(NamedEntity &&rhs)
    : Entity(std::move(rhs))
{
    mName = std::move(rhs.mName);
}

NamedEntity& NamedEntity::operator=(NamedEntity n)
{
    Entity::operator= (n);
    n.swap(*this);
    return *this;
}

void NamedEntity::setName(const std::string &name) {
    mName = name;
}

std::string NamedEntity::getName() const {
    return mName;
}

void NamedEntity::swap(NamedEntity &rhs)
{
    std::swap(this->mName, rhs.mName);
}

}

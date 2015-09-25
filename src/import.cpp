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

#include "libcellml/import.h"

namespace libcellml {

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

}

Import::Import(const Import& rhs)
    : Entity(rhs)
{

}

Import::Import(Import &&rhs)
    : Entity(std::move(rhs))
{

}

Import& Import::operator=(Import m)
{
    Entity::operator= (m);
    return *this;
}

std::string Import::doSerialisation(libcellml::CELLML_FORMATS format) const
{
    std::string repr = "";
    if (format == CELLML_FORMAT_XML) {
    }

    return repr;
}

void Import::setSource(const std::string &/*reference*/)
{

}

}

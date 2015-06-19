
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

#include "libcellml/component.h"

namespace libcellml {

/**
 * @brief The private implementation for the Component class.
 * This struct is the private implementation struct for the Component class.  Separating
 * the implementation from the definition allows for greater flexibility when
 * distributing the code.
 */
struct Component::ComponentImpl
{
    ComponentImpl(){}
    ~ComponentImpl(){}
    ComponentImpl(const ComponentImpl&) = delete;
    ComponentImpl& operator=(const ComponentImpl&) = delete;
};

// Interface class Model implementation
Component::Component()
    : mPimpl(new Component::ComponentImpl)
{
}

Component::~Component()
{
}

Component::Component(Component&& rhs)
    : Nameable(rhs)
    , mPimpl(std::move(rhs.mPimpl))
{
}

Component& Component::operator=(Component&& rhs)
{
    mPimpl = std::move(rhs.mPimpl);
    return *this;
}

std::string Component::serialise(libcellml::CELLML_FORMATS format) const
{
    std::string repr = "";
    if (format == CELLML_FORMAT_XML) {
    }

    return repr;
}

void Component::addComponent(Component &/* c */)
{

}

}


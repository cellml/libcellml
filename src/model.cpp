
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

#include "libcellml/model.h"

#include <vector>

#include <iostream>
namespace libcellml {

/**
 * @brief The private implementation for the Model class.
 * This struct is the private implementation struct for the Model class.  Separating
 * the implementation from the definition allows for greater flexibility when
 * distributing the code.
 */
struct Model::ModelImpl
{
    std::vector<Component> mComponents;
};

// Interface class Model implementation
Model::Model()
    : mPimpl(new ModelImpl())
{
}

Model::~Model()
{
    delete mPimpl;
}

Model::Model(const Model& rhs)
    : Nameable(rhs)
    , mPimpl(new ModelImpl())
{
    std::cout << "Model copy" << std::endl;
    mPimpl->mComponents = rhs.mPimpl->mComponents;
}

Model& Model::operator=(const Model& c)
{
    std::cout << "Model assign" << std::endl;
    mPimpl = c.mPimpl;
    return *this;
}

Model::Model(Model&& rhs)
    : Nameable(rhs)
    , mPimpl(std::move(rhs.mPimpl))
{
    std::cout << "Model move constructor" << std::endl;
}

Model& Model::operator=(Model&& rhs)
{
    mPimpl = std::move(rhs.mPimpl);
    return *this;
}

std::string Model::serialise(libcellml::CELLML_FORMATS format) const
{
    std::string repr = "";
    if (format == CELLML_FORMAT_XML) {
        repr += "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n<model xmlns=\"http://www.cellml.org/cellml/1.2#\"";
        if (getName().length()) {
            repr += " name=\"" + getName() + "\"";
        }
        repr += ">";
        for(std::vector<Component>::size_type i = 0; i != mPimpl->mComponents.size(); i++) {
            repr += mPimpl->mComponents[i].serialise(format);
        }
        repr += "</model>";
    }

    return repr;
}

void Model::addComponent(const Component& c)
{
    mPimpl->mComponents.push_back(c);
}

}


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

#include <assert.h>
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
    std::vector<Component>::iterator findComponent(const std::string& name);
    std::vector<Component> mComponents;
};

std::vector<Component>::iterator Model::ModelImpl::findComponent(const std::string& name)
{
    return std::find_if(mComponents.begin(), mComponents.end(),
                        [=](const Component& c) -> bool {return c.getName() == name;});
}

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
    mPimpl->mComponents = rhs.mPimpl->mComponents;
}

Model& Model::operator=(Model m)
{
    m.swap(*this);
    return *this;
}

void Model::swap(Model &rhs)
{
    std::swap(mName, rhs.mName);
    std::swap(mPimpl, rhs.mPimpl);
}

Model::Model(Model&& rhs)
    : Nameable()
    , mPimpl(rhs.mPimpl)
{
    mName = std::move(rhs.mName);
    rhs.mPimpl = nullptr;
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

void Model::removeComponent(const std::string& name)
{
    auto result = mPimpl->findComponent(name);
    if(result != mPimpl->mComponents.end()) {
        mPimpl->mComponents.erase(result);
    } else {
        throw std::out_of_range("Named component not found.");
    }
}

void Model::removeComponent(size_t index)
{
    if (index < mPimpl->mComponents.size()) {
        mPimpl->mComponents.erase(mPimpl->mComponents.begin() + index);
    } else {
        throw std::out_of_range("Index out of range.");
    }
}

size_t Model::componentCount() const
{
    return mPimpl->mComponents.size();
}

bool Model::containsComponent(const std::string& name)
{
    auto result = mPimpl->findComponent(name);
    return result != mPimpl->mComponents.end();
}

Component& Model::getComponent(size_t index)
{
    return mPimpl->mComponents.at(index);
}

const Component& Model::getComponent(size_t index) const
{
    return mPimpl->mComponents.at(index);
}

Component Model::takeComponent(size_t index)
{
    Component c = mPimpl->mComponents.at(index);
    removeComponent(index);
    return c;
}

Component Model::takeComponent(const std::string & name)
{
    auto result = mPimpl->findComponent(name);
    size_t index = result - mPimpl->mComponents.begin();
    return takeComponent(index);
}

void Model::replaceComponent(size_t index, const Component& c)
{
    removeComponent(index);
    mPimpl->mComponents.insert(mPimpl->mComponents.begin() + index, c);
}

void Model::replaceComponent(const std::string& name, const Component& c)
{
    auto result = mPimpl->findComponent(name);
    size_t index = result - mPimpl->mComponents.begin();
    replaceComponent(index, c);
}

}

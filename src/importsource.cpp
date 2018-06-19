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

#include "libcellml/importsource.h"

#include <sstream>
#include <fstream>

#include "libcellml/model.h"
#include "libcellml/component.h"
#include "libcellml/parser.h"

namespace libcellml {

/**
 * @brief The ImportSource::ImportSourceImpl struct.
 *
 * The private implementation for the ImportSource class.
 */
struct ImportSource::ImportSourceImpl
{
    std::string mReference;
    libcellml::ModelPtr mSourceModel;
};

ImportSource::ImportSource()
    : mPimpl(new ImportSourceImpl())
{
    mPimpl->mSourceModel = nullptr;
}

ImportSource::~ImportSource()
{
    delete mPimpl;
}

ImportSource::ImportSource(const ImportSource& rhs)
    : Entity(rhs)
    , mPimpl(new ImportSourceImpl())
{
    mPimpl->mReference = rhs.mPimpl->mReference;
    mPimpl->mSourceModel = rhs.mPimpl->mSourceModel;
}

ImportSource::ImportSource(ImportSource &&rhs)
    : Entity(std::move(rhs))
    , mPimpl(rhs.mPimpl)
{
    rhs.mPimpl = nullptr;
}

ImportSource& ImportSource::operator=(ImportSource e)
{
    Entity::operator= (e);
    e.swap(*this);
    return *this;
}

void ImportSource::swap(ImportSource &rhs)
{
    std::swap(this->mPimpl, rhs.mPimpl);
}

void ImportSource::setSource(const std::string &reference)
{
    mPimpl->mReference = reference;
}

std::string ImportSource::getSource() const
{
    return mPimpl->mReference;
}

void ImportSource::resolveImport(ModelPtr model)
{
    mPimpl->mSourceModel = model;
}

ModelPtr ImportSource::getResolvingModel() const
{
    return mPimpl->mSourceModel;
}

bool ImportSource::isResolved() const
{
    return mPimpl->mSourceModel != nullptr;
}

std::string resolvePath(const std::string& filename, const std::string& base)
{
    // we can be naive here as we know what we are dealing with
    std::string path = base.substr(0, base.find_last_of('/')+1) + filename;
    return path;
}

size_t importedChildrenCount(libcellml::ComponentPtr parent)
{
    size_t numberImportedChildren = 0;
    for (size_t n = 0; n < parent->componentCount();  ++n)
    {
        libcellml::ComponentPtr c = parent->getComponent(n);
        if (c->isImport()) {
            ++numberImportedChildren;
        }
        numberImportedChildren += importedChildrenCount(c);
    }
    return numberImportedChildren;
}

size_t countUnresolvedC(libcellml::ComponentPtr component)
{
    size_t count = 0;
    if (component->isImport()) {
        libcellml::ImportSourcePtr imp = component->getImportSource();
        if (!imp->isResolved()) {
            ++count;
        }
        else {
            libcellml::ModelPtr iModel = imp->getResolvingModel();
            count += unresolvedImportedComponentsCount(iModel);
        }
    }
    return count;
}

size_t countUnresolvedComponents(libcellml::ComponentPtr component)
{
    size_t count = countUnresolvedC(component);
    for (size_t n = 0; n < component->componentCount();  ++n)
    {
        libcellml::ComponentPtr c = component->getComponent(n);
        count += countUnresolvedComponents(c);
    }
    return count;
}

size_t unresolvedImportedComponentsCount(libcellml::ModelPtr model)
{
    size_t count = 0;
    for (size_t m = 0; m < model->componentCount();  ++m)
    {
        libcellml::ComponentPtr c = model->getComponent(m);
        count += countUnresolvedComponents(c);
    }
    return count;
}

void resolveComponent(libcellml::ComponentPtr component,
                             const std::string& baseFile)
{
    if (component->isImport()) {
        libcellml::ImportSourcePtr imp = component->getImportSource();
        if (! imp->isResolved()) {
            std::string url = resolvePath(imp->getSource(), baseFile);
            std::ifstream t(url);
            std::stringstream buffer;
            buffer << t.rdbuf();
            libcellml::Parser p;
            libcellml::ModelPtr model = p.parseModel(buffer.str());
            if (model) {
                imp->resolveImport(model);
                resolveImportedComponents(model, url);
            }
        }
    }
}

void resolveComponents(libcellml::ComponentPtr component,
                              const std::string& baseFile)
{
    resolveComponent(component, baseFile);
    for (size_t n = 0; n < component->componentCount();  ++n)
    {
        libcellml::ComponentPtr c = component->getComponent(n);
        resolveComponents(c, baseFile);
    }
}

void resolveImportedComponents(libcellml::ModelPtr model,
                                      const std::string& baseFile)
{
    for (size_t n = 0; n < model->componentCount();  ++n)
    {
        libcellml::ComponentPtr c = model->getComponent(n);
        resolveComponents(c, baseFile);
    }
}



}

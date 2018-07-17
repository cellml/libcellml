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

#include "libcellml/component.h"
#include "libcellml/model.h"
#include "libcellml/parser.h"
#include "libcellml/units.h"

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

void ImportSource::setSource(const std::string &source)
{
    mPimpl->mReference = source;
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

/**
 * @brief Resolve the path of the given filename using the given base.
 *
 * Resolves the full path to the given @p filename using the @p base.
 *
 * This function is only intended to work with local files.  It may not
 * work with bases that use the 'file://' prefix.
 *
 * @param filename The @c std::string relative path from the base path.
 * @param base The @c std::string location on local disk for determining the full path from.
 * @return The full path from the @p base location to the @p filename
 */
std::string resolvePath(const std::string& filename, const std::string& base)
{
    // we can be naive here as we know what we are dealing with
    std::string path = base.substr(0, base.find_last_of('/')+1) + filename;
    return path;
}

/**
 * @brief Count the imported children of the given @c Component.
 *
 * Recursivley count the number of imported children from the given @c Component.
 *
 * @param parent The @c Component to count the imported children in.
 * @return The number of imported children the given @c Component has.
 */
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

size_t countUnresolvedComponent(libcellml::ComponentPtr component)
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
    size_t count = countUnresolvedComponent(component);
    for (size_t n = 0; n < component->componentCount();  ++n)
    {
        libcellml::ComponentPtr c = component->getComponent(n);
        count += countUnresolvedComponents(c);
    }
    return count;
}

size_t importedComponentsCount(libcellml::ModelPtr model)
{
    size_t nImportedComponents = 0;
    for (size_t n = 0; n < model->componentCount();  ++n)
    {
        libcellml::ComponentPtr c = model->getComponent(n);
        if (c->isImport()) {
            ++nImportedComponents;
        }
        nImportedComponents += libcellml::importedChildrenCount(c);
    }

    return nImportedComponents;
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

size_t importedUnitsCount(libcellml::ModelPtr model)
{
    size_t nImportedUnits = 0;
    for (size_t n = 0; n < model->unitsCount();  ++n)
    {
        libcellml::UnitsPtr u = model->getUnits(n);
        if (u->isImport()) {
            ++nImportedUnits;
        }
    }

    return nImportedUnits;
}

size_t unresolvedImportedUnitsCount(libcellml::ModelPtr model)
{
    size_t count = 0;
    for (size_t m = 0; m < model->unitsCount();  ++m)
    {
        libcellml::UnitsPtr u = model->getUnits(m);
        if (u->isImport()) {
            libcellml::ImportSourcePtr imp = u->getImportSource();
            if (!imp->isResolved()) {
                ++count;
            }
        }
    }

    return count;
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

void resolveUnits(libcellml::UnitsPtr units, const std::string& baseFile)
{
    if (units->isImport()) {
        libcellml::ImportSourcePtr imp = units->getImportSource();
        if (! imp->isResolved()) {
            std::string url = resolvePath(imp->getSource(), baseFile);
            std::ifstream t(url);
            std::stringstream buffer;
            buffer << t.rdbuf();
            libcellml::Parser p;
            libcellml::ModelPtr model = p.parseModel(buffer.str());
            if (model) {
                imp->resolveImport(model);
                resolveImportedUnits(model, url);
            }
        }
    }
}

void resolveImportedUnits(libcellml::ModelPtr model,
                          const std::string& baseFile)
{
    for (size_t n = 0; n < model->unitsCount();  ++n)
    {
        libcellml::UnitsPtr u = model->getUnits(n);
        resolveUnits(u, baseFile);
    }
}

}

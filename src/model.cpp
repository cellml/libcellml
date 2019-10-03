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

#include "libcellml/component.h"
#include "libcellml/importsource.h"
#include "libcellml/model.h"
#include "libcellml/parser.h"
#include "libcellml/units.h"
#include "libcellml/variable.h"

#include <algorithm>
#include <fstream>
#include <map>
#include <sstream>
#include <stack>
#include <utility>
#include <vector>
#include <iostream>


namespace libcellml {

/**
 * @brief The Model::ModelImpl struct.
 *
 * This struct is the private implementation struct for the Model class.  Separating
 * the implementation from the definition allows for greater flexibility when
 * distributing the code.
 */
struct Model::ModelImpl
{
    std::vector<UnitsPtr> mUnits;

    std::vector<UnitsPtr>::iterator findUnits(const std::string &name);
    std::vector<UnitsPtr>::iterator findUnits(const UnitsPtr &units);
};

std::vector<UnitsPtr>::iterator Model::ModelImpl::findUnits(const std::string &name)
{
    return std::find_if(mUnits.begin(), mUnits.end(),
                        [=](const UnitsPtr &u) -> bool { return u->name() == name; });
}

std::vector<UnitsPtr>::iterator Model::ModelImpl::findUnits(const UnitsPtr &units)
{
    return std::find_if(mUnits.begin(), mUnits.end(),
                        [=](const UnitsPtr &u) -> bool { return u == units; });
}

Model::Model()
    : mPimpl(new ModelImpl())
{
}

Model::~Model()
{
    delete mPimpl;
}

Model::Model(const Model &rhs)
    : ComponentEntity(rhs)
#ifndef SWIG
    , std::enable_shared_from_this<Model>(rhs)
#endif
    , mPimpl(new ModelImpl())
{
    mPimpl->mUnits = rhs.mPimpl->mUnits;
}

Model::Model(Model &&rhs) noexcept
    : ComponentEntity(std::move(rhs))
    , mPimpl(rhs.mPimpl)
{
    rhs.mPimpl = nullptr;
}

Model &Model::operator=(Model rhs)
{
    ComponentEntity::operator=(rhs);
    rhs.swap(*this);
    return *this;
}

void Model::swap(Model &rhs)
{
    std::swap(mPimpl, rhs.mPimpl);
}

void Model::doAddComponent(const ComponentPtr &component)
{
    // Check for cycles.
    if (!hasAncestor(component)) {
        component->setParent(shared_from_this());
        ComponentEntity::doAddComponent(component);
    }
}

void Model::addUnits(const UnitsPtr &units)
{
    mPimpl->mUnits.push_back(units);
}

bool Model::removeUnits(size_t index)
{
    bool status = false;
    if (index < mPimpl->mUnits.size()) {
        mPimpl->mUnits.erase(mPimpl->mUnits.begin() + int64_t(index));
        status = true;
    }

    return status;
}

bool Model::removeUnits(const std::string &name)
{
    bool status = false;
    auto result = mPimpl->findUnits(name);
    if (result != mPimpl->mUnits.end()) {
        mPimpl->mUnits.erase(result);
        status = true;
    }

    return status;
}

bool Model::removeUnits(const UnitsPtr &units)
{
    bool status = false;
    auto result = mPimpl->findUnits(units);
    if (result != mPimpl->mUnits.end()) {
        mPimpl->mUnits.erase(result);
        status = true;
    }

    return status;
}

void Model::removeAllUnits()
{
    mPimpl->mUnits.clear();
}

bool Model::hasUnits(const std::string &name) const
{
    return mPimpl->findUnits(name) != mPimpl->mUnits.end();
}

bool Model::hasUnits(const UnitsPtr &units) const
{
    return mPimpl->findUnits(units) != mPimpl->mUnits.end();
}

UnitsPtr Model::units(size_t index) const
{
    UnitsPtr units = nullptr;
    if (index < mPimpl->mUnits.size()) {
        units = mPimpl->mUnits.at(index);
    }

    return units;
}

UnitsPtr Model::units(const std::string &name) const
{
    UnitsPtr units = nullptr;
    auto result = mPimpl->findUnits(name);
    if (result != mPimpl->mUnits.end()) {
        units = *result;
    }

    return units;
}

UnitsPtr Model::takeUnits(size_t index)
{
    UnitsPtr units = nullptr;
    if (index < mPimpl->mUnits.size()) {
        units = mPimpl->mUnits.at(index);
        removeUnits(index);
        units->clearParent();
    }

    return units;
}

UnitsPtr Model::takeUnits(const std::string &name)
{
    return takeUnits(size_t(mPimpl->findUnits(name) - mPimpl->mUnits.begin()));
}

bool Model::replaceUnits(size_t index, const UnitsPtr &units)
{
    bool status = false;
    if (removeUnits(index)) {
        mPimpl->mUnits.insert(mPimpl->mUnits.begin() + int64_t(index), units);
        status = true;
    }

    return status;
}

bool Model::replaceUnits(const std::string &name, const UnitsPtr &units)
{
    return replaceUnits(size_t(mPimpl->findUnits(name) - mPimpl->mUnits.begin()), units);
}

bool Model::replaceUnits(const UnitsPtr &oldUnits, const UnitsPtr &newUnits)
{
    return replaceUnits(size_t(mPimpl->findUnits(oldUnits) - mPimpl->mUnits.begin()), newUnits);
}

size_t Model::unitsCount() const
{
    return mPimpl->mUnits.size();
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
std::string resolvePath(const std::string &filename, const std::string &base)
{
    // We can be naive here as we know what we are dealing with
    std::string path = base.substr(0, base.find_last_of('/') + 1) + filename;
    return path;
}

void resolveImport(const ImportedEntityPtr &importedEntity,
                   const std::string &baseFile)
{
    if (importedEntity->isImport()) {
        ImportSourcePtr importSource = importedEntity->importSource();
        if (!importSource->hasModel()) {
            std::string url = resolvePath(importSource->url(), baseFile);
            std::ifstream file(url);
            if (file.good()) {
                std::stringstream buffer;
                buffer << file.rdbuf();
                Parser parser;
                ModelPtr model = parser.parseModel(buffer.str());
                importSource->setModel(model);
                model->resolveImports(url);
            }
        }
    }
}

void resolveComponentImports(const ComponentEntityPtr &parentComponentEntity,
                             const std::string &baseFile)
{
    for (size_t n = 0; n < parentComponentEntity->componentCount(); ++n) {
        libcellml::ComponentPtr component = parentComponentEntity->component(n);
        if (component->isImport()) {
            resolveImport(component, baseFile);
        } else {
            resolveComponentImports(component, baseFile);
        }
    }
}

void Model::resolveImports(const std::string &baseFile)
{
    for (size_t n = 0; n < unitsCount(); ++n) {
        libcellml::UnitsPtr units = Model::units(n);
        resolveImport(units, baseFile);
    }
    resolveComponentImports(shared_from_this(), baseFile);
}

bool isUnresolvedImport(const ImportedEntityPtr &importedEntity)
{
    bool unresolvedImport = false;
    if (importedEntity->isImport()) {
        ImportSourcePtr importedSource = importedEntity->importSource();
        if (!importedSource->hasModel()) {
            unresolvedImport = true;
        }
    }
    return unresolvedImport;
}

bool hasUnresolvedComponentImports(const ComponentEntityPtr &parentComponentEntity);

bool doHasUnresolvedComponentImports(const ComponentPtr &component)
{
    bool unresolvedImports = false;
    if (component->isImport()) {
        unresolvedImports = isUnresolvedImport(component);
        if (!unresolvedImports) {
            // Check that the imported component can import all it needs from its model.
            ImportSourcePtr importedSource = component->importSource();
            if (importedSource->hasModel()) {
                ModelPtr importedModel = importedSource->model();
                ComponentPtr importedComponent = importedModel->component(component->importReference());
                unresolvedImports = doHasUnresolvedComponentImports(importedComponent);
            }
        }
    } else {
        unresolvedImports = hasUnresolvedComponentImports(component);
    }
    return unresolvedImports;
}

bool hasUnresolvedComponentImports(const ComponentEntityPtr &parentComponentEntity)
{
    bool unresolvedImports = false;
    for (size_t n = 0; n < parentComponentEntity->componentCount() && !unresolvedImports; ++n) {
        libcellml::ComponentPtr component = parentComponentEntity->component(n);
        unresolvedImports = doHasUnresolvedComponentImports(component);
    }
    return unresolvedImports;
}

bool Model::hasUnresolvedImports()
{
    bool unresolvedImports = false;
    for (size_t n = 0; n < unitsCount() && !unresolvedImports; ++n) {
        libcellml::UnitsPtr units = Model::units(n);
        unresolvedImports = isUnresolvedImport(units);
    }
    if (!unresolvedImports) {
        unresolvedImports = hasUnresolvedComponentImports(shared_from_this());
    }
    return unresolvedImports;
}


bool flattenComponent(ComponentPtr& component)
{
	ComponentPtr src = component->importSource()->model()->component(component->importReference());
	std::cout << "Flatening component: " << component->name() << "; using the source component: " << src->name() << std::endl;
	std::cout << "Number of variables in component to flatten: " << int(component->variableCount()) << std::endl;

	return true;
}

bool Model::flatten()
{
	for (size_t n = 0; n < this->componentCount(); ++n) {
		libcellml::ComponentPtr component = this->component(n);
		if (component->isImport()) {
			flattenComponent(component);
		}
	}
	return true;
}

} // namespace libcellml

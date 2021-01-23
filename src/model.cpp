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

#include "libcellml/model.h"

#include <algorithm>
#include <fstream>
#include <map>
#include <sstream>
#include <stack>
#include <utility>
#include <vector>

#include "libcellml/component.h"
#include "libcellml/importsource.h"
#include "libcellml/parser.h"
#include "libcellml/units.h"
#include "libcellml/variable.h"

#include "internaltypes.h"
#include "utilities.h"
#include "xmldoc.h"
#include "xmlutils.h"

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
    std::vector<ImportSourceWeakPtr> mImports;

    std::vector<UnitsPtr>::iterator findUnits(const std::string &name);
    std::vector<UnitsPtr>::iterator findUnits(const UnitsPtr &units);

    void cleanExpiredImportSources();
};

std::vector<UnitsPtr>::iterator Model::ModelImpl::findUnits(const std::string &name)
{
    return std::find_if(mUnits.begin(), mUnits.end(),
                        [=](const UnitsPtr &u) -> bool { return u->name() == name; });
}

std::vector<UnitsPtr>::iterator Model::ModelImpl::findUnits(const UnitsPtr &units)
{
    auto result = std::find(mUnits.begin(), mUnits.end(), units);
    if (result != mUnits.end()) {
        return result;
    }
    return std::find_if(mUnits.begin(), mUnits.end(),
                        [=](const UnitsPtr &u) -> bool { return units->name().empty() ? false : u->name() == units->name() && Units::equivalent(u, units); });
}

Model::Model()
    : mPimpl(new ModelImpl())
{
}

Model::Model(const std::string &name)
    : mPimpl(new ModelImpl())
{
    setName(name);
}

ModelPtr Model::create() noexcept
{
    return std::shared_ptr<Model> {new Model {}};
}

ModelPtr Model::create(const std::string &name) noexcept
{
    return std::shared_ptr<Model> {new Model {name}};
}

Model::~Model()
{
    delete mPimpl;
}

void registerPossibleImportSource(const ModelPtr &model, const ComponentPtr &component)
{
    if (component->isImport()) {
        model->addImportSource(component->importSource());
    }
    for (size_t index = 0; index < component->componentCount(); ++index) {
        registerPossibleImportSource(model, component->component(index));
    }
}

bool Model::doAddComponent(const ComponentPtr &component)
{
    if (component->hasParent()) {
        auto parent = component->parent();
        removeComponentFromEntity(parent, component);
    }
    component->setParent(shared_from_this());

    registerPossibleImportSource(shared_from_this(), component);

    return ComponentEntity::doAddComponent(component);
}

bool Model::addUnits(const UnitsPtr &units)
{
    if (units == nullptr) {
        return false;
    }

    // Prevent adding multiple times to list.
    if (hasUnits(units)) {
        return false;
    }

    // Prevent adding to multiple models: move units to this model.
    if (units->hasParent()) {
        auto otherParent = std::dynamic_pointer_cast<Model>(units->parent());
        otherParent->removeUnits(units);
    }
    mPimpl->mUnits.push_back(units);
    units->setParent(shared_from_this());

    if (units->isImport()) {
        addImportSource(units->importSource());
    }
    return true;
}

bool Model::removeUnits(size_t index)
{
    bool status = false;
    if (index < mPimpl->mUnits.size()) {
        auto units = *(mPimpl->mUnits.begin() + ptrdiff_t(index));
        units->removeParent();
        mPimpl->mUnits.erase(mPimpl->mUnits.begin() + ptrdiff_t(index));
        status = true;
    }

    return status;
}

bool Model::removeUnits(const std::string &name)
{
    bool status = false;
    auto result = mPimpl->findUnits(name);
    if (result != mPimpl->mUnits.end()) {
        auto units = (*result);
        units->removeParent();
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
        units->removeParent();
        mPimpl->mUnits.erase(result);
        status = true;
    }

    return status;
}

void Model::removeAllUnits()
{
    for (const auto &u : mPimpl->mUnits) {
        u->removeParent();
    }
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
        units->removeParent();
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

        if (units->isImport()) {
            addImportSource(units->importSource());
        }
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


void Model::ModelImpl::cleanExpiredImportSources()
{
    mImports.erase(std::remove_if(mImports.begin(), mImports.end(), [=](const ImportSourceWeakPtr &importSourceWeak) -> bool { return importSourceWeak.expired(); }), mImports.end());
}

bool Model::hasImportSource(const ImportSourcePtr &importSrc) const
{
    return std::find_if(mPimpl->mImports.begin(), mPimpl->mImports.end(),
                            [=](const ImportSourceWeakPtr &importSourceWeak) -> bool { return importSrc == importSourceWeak.lock(); }) != mPimpl->mImports.end();
}

bool Model::addImportSource(const ImportSourcePtr &importSrc)
{
    if (importSrc == nullptr) {
        return false;
    }
    if (hasImportSource(importSrc)) {
        return false;
    }
    auto otherModel = owningModel(importSrc);
    if (otherModel != nullptr) {
        otherModel->removeImportSource(importSrc);
    }
    importSrc->setParent(shared_from_this());
    // Add an entirely separate copy to the model's list.
    mPimpl->mImports.push_back(importSrc);
    return true;
}

size_t Model::importSourceCount() const
{
    mPimpl->cleanExpiredImportSources();
    return mPimpl->mImports.size();
}

ImportSourcePtr Model::importSource(size_t index) const
{
    mPimpl->cleanExpiredImportSources();

    ImportSourcePtr importSrc = nullptr;
    if (index < mPimpl->mImports.size()) {
        importSrc = mPimpl->mImports.at(index).lock();
    }

    return importSrc;
}

bool Model::removeImportSource(size_t index)
{
    auto importSrc = importSource(index);
    return removeImportSource(importSrc);
}

bool Model::removeImportSource(const ImportSourcePtr &importSrc)
{
    mPimpl->cleanExpiredImportSources();

    bool status = false;
    auto result = std::find_if(mPimpl->mImports.begin(), mPimpl->mImports.end(),
                               [=](const ImportSourceWeakPtr &importSourceWeak) -> bool { return importSrc == importSourceWeak.lock(); });
    if (result != mPimpl->mImports.end()) {
        importSrc->removeParent();
        mPimpl->mImports.erase(result);
        status = true;
    }
    return status;
}

bool Model::removeAllImportSources()
{
    for (const auto &imp : mPimpl->mImports) {
        auto importSrc = imp.lock();
        if (importSrc != nullptr) {
            importSrc->removeParent();
        }
    }
    mPimpl->mImports.clear();
    return true;
}

bool Model::linkUnits()
{
    return traverseComponentEntityTreeLinkingUnits(shared_from_this());
}

bool traverseComponentTreeForUnlinkedUnits(const ComponentPtr &component)
{
    bool unlinkedUnits = areComponentVariableUnitsUnlinked(component);
    for (size_t index = 0; index < component->componentCount() && !unlinkedUnits; ++index) {
        auto c = component->component(index);
        unlinkedUnits = traverseComponentTreeForUnlinkedUnits(c);
    }
    return unlinkedUnits;
}

bool Model::hasUnlinkedUnits()
{
    bool unlinkedUnits = false;
    for (size_t index = 0; index < componentCount() && !unlinkedUnits; ++index) {
        auto c = component(index);
        unlinkedUnits = traverseComponentTreeForUnlinkedUnits(c);
    }
    return unlinkedUnits;
}

bool Model::hasUnresolvedImports() const
{
    bool unresolvedImports = false;
    for (size_t n = 0; n < unitsCount() && !unresolvedImports; ++n) {
        unresolvedImports = !units(n)->isResolved();
    }
    for (size_t n = 0; (n < componentCount()) && !unresolvedImports; ++n) {
        unresolvedImports = !component(n)->isResolved();
    }
    return unresolvedImports;
}

bool hasComponentImports(const ComponentEntityConstPtr &componentEntity)
{
    bool importsPresent = false;
    for (size_t n = 0; (n < componentEntity->componentCount()) && !importsPresent; ++n) {
        libcellml::ComponentPtr childComponent = componentEntity->component(n);
        importsPresent = childComponent->isImport();
        if (!importsPresent) {
            importsPresent = hasComponentImports(childComponent);
        }
    }
    return importsPresent;
}

bool Model::hasImports() const
{
    bool importsPresent = false;
    for (size_t n = 0; (n < unitsCount()) && !importsPresent; ++n) {
        libcellml::UnitsPtr units = Model::units(n);
        if (units->isImport()) {
            importsPresent = true;
        }
    }

    if (!importsPresent) {
        importsPresent = hasComponentImports(shared_from_this());
    }

    return importsPresent;
}

void fixComponentUnits(const ModelPtr &model, const ComponentPtr &component)
{
    for (size_t v = 0; v < component->variableCount(); ++v) {
        auto variable = component->variable(v);
        if (variable->units() != nullptr) {
            // Find the units in the model and switch out.
            auto units = model->units(variable->units()->name());
            if (units != nullptr) {
                variable->setUnits(units);
            }
        }
    }
    for (size_t c = 0; c < component->componentCount(); ++c) {
        fixComponentUnits(model, component->component(c));
    }
}

ModelPtr Model::clone() const
{
    auto m = create();

    m->setId(id());
    m->setName(name());

    m->setEncapsulationId(encapsulationId());

    for (size_t index = 0; index < mPimpl->mUnits.size(); ++index) {
        m->addUnits(units(index)->clone());
    }

    for (size_t index = 0; index < componentCount(); ++index) {
        m->addComponent(component(index)->clone());
    }

    for (size_t index = 0; index < m->componentCount(); ++index) {
        fixComponentUnits(m, m->component(index));
    }

    // Remove all import sources from the cloned model as they will
    // have lost their associations.  The proper associated imports
    // will be copied below.
    m->removeAllImportSources();

    auto originalImportedUnits = getImportedUnits(shared_from_this());
    auto clonedImportedUnits = getImportedUnits(m);

    auto originalImportedComponents = getImportedComponents(shared_from_this());
    auto clonedImportedComponents = getImportedComponents(m);

    for (size_t index = 0; index < importSourceCount(); ++index) {
        auto originalImportSource = importSource(index);
        auto clonedImportSource = originalImportSource->clone();
        m->addImportSource(clonedImportSource);

        // Reset import associations for units.
        for (size_t indexUnits = 0; indexUnits < originalImportedUnits.size(); ++indexUnits) {
            auto originalUnits = originalImportedUnits.at(indexUnits);
            if (originalUnits->importSource() == originalImportSource) {
                clonedImportedUnits.at(indexUnits)->setImportSource(clonedImportSource);
            }
        }

        // Reset import associations for components.
        for (size_t indexComponents = 0; indexComponents < originalImportedComponents.size(); ++indexComponents) {
            auto originalComponent = originalImportedComponents.at(indexComponents);
            if (originalComponent->importSource() == originalImportSource) {
                clonedImportedComponents.at(indexComponents)->setImportSource(clonedImportSource);
            }
        }
    }

    // Generate equivalence map starting from the models components.
    EquivalenceMap map;
    IndexStack indexStack;
    for (size_t index = 0; index < componentCount(); ++index) {
        indexStack.push_back(index);
        auto c = component(index);
        recordVariableEquivalences(c, map, indexStack);
        generateEquivalenceMap(c, map, indexStack);
        indexStack.pop_back();
    }
    applyEquivalenceMapToModel(map, m);

    return m;
}

bool Model::fixVariableInterfaces()
{
    VariablePtrs variables;

    for (size_t index = 0; index < componentCount(); ++index) {
        findAllVariablesWithEquivalences(component(index), variables);
    }

    bool allOk = true;
    for (const auto &variable : variables) {
        Variable::InterfaceType interfaceType = determineInterfaceType(variable);
        if (interfaceType == Variable::InterfaceType::NONE) {
            allOk = false;
        } else if (!variable->permitsInterfaceType(interfaceType)) {
            variable->setInterfaceType(interfaceType);
        }
    }

    return allOk;
}

} // namespace libcellml

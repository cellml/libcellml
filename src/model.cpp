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

#include "utilities.h"

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
                        [=](const UnitsPtr &u) -> bool { return units->name().empty() ? false : u->name() == units->name(); });
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

bool Model::doAddComponent(const ComponentPtr &component)
{
    if (component->hasParent()) {
        auto parent = component->parent();
        removeComponentFromEntity(parent, component);
    }
    component->setParent(shared_from_this());
    return ComponentEntity::doAddComponent(component);
}

void Model::addUnits(const UnitsPtr &units)
{
    mPimpl->mUnits.push_back(units);
    units->setParent(shared_from_this());
}

bool Model::removeUnits(size_t index)
{
    bool status = false;
    if (index < mPimpl->mUnits.size()) {
        auto units = *(mPimpl->mUnits.begin() + int64_t(index));
        units->removeParent();
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
        (*result)->removeParent();
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
                ParserPtr parser = Parser::create();
                ModelPtr model = parser->parseModel(buffer.str());
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

using IndexStack = std::vector<size_t>; /**< Type definition for tracking indicies. */
using EquivalenceMap = std::map<IndexStack, std::vector<IndexStack>>; /**< Type definition for map of variable equivalences defined over model. */

size_t getComponentIndexInComponentEntity(const ComponentEntityPtr &componentParent, const ComponentEntityPtr &component)
{
    size_t index = 0;
    bool found = false;
    while (index < componentParent->componentCount() && !found) {
        if (componentParent->component(index) == component) {
            found = true;
        } else {
            ++index;
        }
    }

    return index;
}

IndexStack reverseEngineerIndexStack(const VariablePtr &variable)
{
    IndexStack indexStack;
    ComponentPtr component = std::dynamic_pointer_cast<Component>(variable->parent());
    indexStack.push_back(getVariableIndexInComponent(component, variable));

    ComponentEntityPtr parent = component;
    ComponentEntityPtr grandParent = std::dynamic_pointer_cast<ComponentEntity>(parent->parent());
    while (grandParent != nullptr) {
        indexStack.push_back(getComponentIndexInComponentEntity(grandParent, parent));
        parent = grandParent;
        grandParent = std::dynamic_pointer_cast<ComponentEntity>(grandParent->parent());
    }

    std::reverse(std::begin(indexStack), std::end(indexStack));

    return indexStack;
}

void recordVariableEquivalences(const ComponentPtr &component, EquivalenceMap &equivalenceMap, IndexStack &indexStack)
{
    for (size_t index = 0; index < component->variableCount(); ++index) {
        auto variable = component->variable(index);
        for (size_t j = 0; j < variable->equivalentVariableCount(); ++j) {
            if (j == 0) {
                indexStack.push_back(index);
            }
            auto equivalentVariable = variable->equivalentVariable(j);
            auto equivalentVariableIndexStack = reverseEngineerIndexStack(equivalentVariable);
            if (equivalenceMap.count(indexStack) == 0) {
                equivalenceMap[indexStack] = std::vector<IndexStack>();
            }
            equivalenceMap[indexStack].push_back(equivalentVariableIndexStack);
        }
        if (variable->equivalentVariableCount() > 0) {
            indexStack.pop_back();
        }
    }
}

void generateEquivalenceMap(const ComponentPtr &component, EquivalenceMap &map, IndexStack &indexStack)
{
    for (size_t index = 0; index < component->componentCount(); ++index) {
        indexStack.push_back(index);
        auto c = component->component(index);
        recordVariableEquivalences(c, map, indexStack);
        generateEquivalenceMap(c, map, indexStack);
        indexStack.pop_back();
    }
}

VariablePtr getVariableLocatedAt(const IndexStack &stack, const ModelPtr &model)
{
    ComponentPtr component;
    for (size_t index = 0; index < stack.size() - 1; ++index) {
        if (index == 0) {
            component = model->component(stack.at(index));
        } else {
            component = component->component(stack.at(index));
        }
    }

    return component->variable(stack.back());
}

void makeEquivalence(const IndexStack &stack1, const IndexStack &stack2, const ModelPtr &model)
{
    auto v1 = getVariableLocatedAt(stack1, model);
    auto v2 = getVariableLocatedAt(stack2, model);
    Variable::addEquivalence(v1, v2);
}

void applyEquivalenceMapToModel(const EquivalenceMap &map, const ModelPtr &model)
{
    for (const auto &iter : map) {
        auto key = iter.first;
        auto vector = iter.second;
        for (auto vectorIter = vector.begin(); vectorIter < vector.end(); ++vectorIter) {
            makeEquivalence(key, *vectorIter, model);
        }
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

} // namespace libcellml

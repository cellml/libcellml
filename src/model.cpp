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
                        [=](const UnitsPtr &u) -> bool { return units->name().empty() ? false : u->name() == units->name() && Units::dimensionallyEquivalent(u, units); });
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

void linkComponentVariableUnits(const ComponentPtr &component)
{
    for (size_t index = 0; index < component->variableCount(); ++index) {
        auto v = component->variable(index);
        auto u = v->units();
        if (u != nullptr) {
            auto model = owningModel(u);
            if (model == nullptr && !isStandardUnitName(u->name())) {
                model = owningModel(component);
                auto modelUnits = model->units(u->name());
                if (modelUnits == nullptr) {
                    model->addUnits(u);
                    modelUnits = u;
                }
                v->setUnits(modelUnits);
            }
        }
    }
}

void traverseComponentTreeLinkingUnits(const ComponentPtr &component)
{
    linkComponentVariableUnits(component);
    for (size_t index = 0; index < component->componentCount(); ++index) {
        auto c = component->component(index);
        traverseComponentTreeLinkingUnits(c);
    }
}

void Model::linkUnits()
{
    for (size_t index = 0; index < componentCount(); ++index) {
        auto c = component(index);
        traverseComponentTreeLinkingUnits(c);
    }
}

bool areComponentVariableUnitsUnlinked(const ComponentPtr &component)
{
    bool unlinked = false;
    for (size_t index = 0; index < component->variableCount() && !unlinked; ++index) {
        auto v = component->variable(index);
        auto u = v->units();
        if (u != nullptr) {
            auto model = owningModel(u);
            unlinked = model == nullptr && !isStandardUnitName(u->name());
        }
    }

    return unlinked;
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
 *
 * @return The full path from the @p base location to the @p filename
 */
std::string resolvePath(const std::string &filename, const std::string &base)
{
    // We can be naive here as we know what we are dealing with
    std::string path = base.substr(0, base.find_last_of('/') + 1) + filename;
    return path;
}

bool resolveImport(const ImportedEntityPtr &importedEntity,
                   const std::string &destination,
                   const std::string &baseFile,
                   std::vector<std::tuple<std::string, std::string, std::string>> &history,
                   std::vector<IssuePtr> &issues)
{
    if (importedEntity->isImport()) {
        ImportSourcePtr importSource = importedEntity->importSource();
        auto h = std::make_tuple(destination, importedEntity->importReference(), importSource->url());
        if (std::find(history.begin(), history.end(), h) != history.end()) {
            history.emplace_back(h);
            return false;
        }
        history.emplace_back(h);

        if (!importSource->hasModel()) {
            std::string url = resolvePath(importSource->url(), baseFile);
            std::ifstream file(url);

            if (file.good()) {
                std::stringstream buffer;
                buffer << file.rdbuf();
                ParserPtr parser = Parser::create();
                ModelPtr model = parser->parseModel(buffer.str());
                // KRM Remove all components from the model *except* the one we want to import.  This is to
                // prevent the call to resolve imports in the new model from trying to resolve *all* the components
                // in the new model when it doesn't need to ... it will still import all the units though ..
                for (size_t c = 0; c < model->componentCount(); ++c) {
                    auto component = model->component(c);
                    if (component->name() != importedEntity->importReference()) {
                        component->removeParent();
                    }
                }
                importSource->setModel(model);
                return model->resolveImports(url, history, issues);
            }
        }
    }
    return true;
}

bool resolveComponentImports(const ComponentEntityPtr &parentComponentEntity,
                             const std::string &baseFile,
                             std::vector<std::tuple<std::string, std::string, std::string>> &history,
                             std::vector<IssuePtr> &issues)
{
    bool noErrors = true;
    for (size_t n = 0; n < parentComponentEntity->componentCount(); ++n) {
        libcellml::ComponentPtr component = parentComponentEntity->component(n);
        if (component->isImport()) {
            if (!resolveImport(component, component->name(), baseFile, history, issues)) {
                if (!history.empty()) {
                    std::string msg = "Cyclic dependencies were found when attempting to resolve components. The dependency loop is:\n";
                    std::string spacer = "    ";
                    for (auto &h : history) {
                        msg += spacer + "component '" + std::get<0>(h) + "' imports '" + std::get<1>(h) + "' from '" + std::get<2>(h);
                        spacer = "',\n    ";
                    }
                    msg += "'.";
                    auto issue = Issue::create();
                    issue->setDescription(msg);
                    issue->setLevel(libcellml::Issue::Level::WARNING);
                    issues.push_back(issue);
                    std::vector<std::tuple<std::string, std::string, std::string>>().swap(history);
                }
                noErrors = false;
            }
        } else {
            if (!resolveComponentImports(component, baseFile, history, issues)) {
                noErrors = false;
            }
        }
    }
    return noErrors;
}

bool Model::resolveImports(const std::string &baseFile, std::vector<std::tuple<std::string, std::string, std::string>> &history, std::vector<libcellml::IssuePtr> &issues)
{
    for (size_t n = 0; n < unitsCount(); ++n) {
        libcellml::UnitsPtr units = Model::units(n);

        if ((!resolveImport(units, units->name(), baseFile, history, issues)) && (!history.empty())) {
            std::string msg = "Cyclic dependencies were found when attempting to resolve units in model '" + this->name() + ". The dependency loop is:\n    ";
            std::string spacer = "    ";
            for (auto &h : history) {
                msg += spacer + "(" + std::get<0>(h) + ", " + std::get<1>(h) + ", " + std::get<2>(h) + ")\n";
                spacer = " -> ";
            }
            auto issue = Issue::create();
            issue->setDescription(msg);
            issue->setLevel(libcellml::Issue::Level::WARNING);
            issue->setModel(shared_from_this());
            issues.push_back(issue);
            std::vector<std::tuple<std::string, std::string, std::string>>().swap(history);
            return false;
        }
    }
    return resolveComponentImports(shared_from_this(), baseFile, history, issues);
}

void Model::resolveImports(const std::string &baseFile)
{
    std::vector<libcellml::IssuePtr> issues = {};
    std::vector<std::tuple<std::string, std::string, std::string>> history = {};
    if (!resolveImports(baseFile, history, issues)) {
        for (auto &issue : issues) {
            addIssue(issue);
        }
    }
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

bool hasUnresolvedComponentImports(const ComponentEntityConstPtr &parentComponentEntity);

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
                if (importedComponent == nullptr) {
                    unresolvedImports = true;
                } else {
                    unresolvedImports = doHasUnresolvedComponentImports(importedComponent);
                }
            }
        }
    } else {
        unresolvedImports = hasUnresolvedComponentImports(component);
    }
    return unresolvedImports;
}

bool hasUnresolvedComponentImports(const ComponentEntityConstPtr &parentComponentEntity)
{
    bool unresolvedImports = false;
    for (size_t n = 0; n < parentComponentEntity->componentCount() && !unresolvedImports; ++n) {
        libcellml::ComponentPtr component = parentComponentEntity->component(n);
        unresolvedImports = doHasUnresolvedComponentImports(component);
    }
    return unresolvedImports;
}

bool Model::hasUnresolvedImports() const
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

bool hasComponentImports(const ComponentEntityConstPtr &componentEntity)
{
    bool importsPresent = false;
    for (size_t n = 0; n < componentEntity->componentCount() && !importsPresent; ++n) {
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
    for (size_t n = 0; n < unitsCount() && !importsPresent; ++n) {
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

IndexStack reverseEngineerIndexStack(const ComponentPtr &component)
{
    auto dummyVariable = Variable::create();
    component->addVariable(dummyVariable);
    IndexStack indexStack = reverseEngineerIndexStack(dummyVariable);
    indexStack.pop_back();
    component->removeVariable(dummyVariable);

    return indexStack;
}

IndexStack rebaseIndexStack(const IndexStack &stack, const IndexStack &originStack, const IndexStack &destinationStack)
{
    auto rebasedStack = stack;

    rebasedStack.resize(originStack.size(), SIZE_MAX);
    if (rebasedStack == originStack) {
        rebasedStack = destinationStack;
        auto offsetIt = stack.begin() + static_cast<int64_t>(originStack.size());
        rebasedStack.insert(rebasedStack.end(), offsetIt, stack.end());
    } else {
        rebasedStack.clear();
    }

    return rebasedStack;
}

EquivalenceMap rebaseEquivalenceMap(const EquivalenceMap &map, const IndexStack &originStack, const IndexStack &destinationStack)
{
    EquivalenceMap rebasedMap;
    for (const auto &entry : map) {
        auto key = entry.first;
        auto rebasedKey = rebaseIndexStack(key, originStack, destinationStack);
        if (!rebasedKey.empty()) {
            auto vector = entry.second;
            std::vector<IndexStack> rebasedVector;
            for (const auto &stack : vector) {
                auto rebasedTarget = rebaseIndexStack(stack, originStack, destinationStack);
                if (!rebasedTarget.empty()) {
                    rebasedVector.push_back(rebasedTarget);
                }
            }

            if (!rebasedVector.empty()) {
                rebasedMap[rebasedKey] = rebasedVector;
            }
        }
    }

    return rebasedMap;
}

void componentNames(const ComponentPtr &component, NameList &names)
{
    for (size_t index = 0; index < component->componentCount(); ++index) {
        auto c = component->component(index);
        names.push_back(c->name());
        componentNames(c, names);
    }
}

NameList componentNames(const ModelPtr &model)
{
    NameList names;
    for (size_t index = 0; index < model->componentCount(); ++index) {
        auto component = model->component(index);
        names.push_back(component->name());
        componentNames(component, names);
    }
    return names;
}

ComponentNameMap createComponentNamesMap(const ComponentPtr &component)
{
    ComponentNameMap nameMap;
    for (size_t index = 0; index < component->componentCount(); ++index) {
        auto c = component->component(index);
        nameMap[c->name()] = c;
        ComponentNameMap childrenNameMap = createComponentNamesMap(c);
        nameMap.insert(childrenNameMap.begin(), childrenNameMap.end());
    }

    return nameMap;
}

void flattenComponent(const ComponentEntityPtr &parent, const ComponentPtr &component, size_t index)
{
    if (component->isImport()) {
        auto model = owningModel(component);
        auto importSource = component->importSource();
        auto importModel = importSource->model();
        auto importedComponent = importModel->component(component->importReference());

        // Determine names of components already in use.
        NameList compNames = componentNames(model);

        // Determine the stack for the destination component.
        IndexStack destinationComponentBaseIndexStack = reverseEngineerIndexStack(component);

        // Determine the stack for the source component.
        IndexStack importedComponentBaseIndexStack = reverseEngineerIndexStack(importedComponent);

        // Generate equivalence map for the source component.
        EquivalenceMap map;
        recordVariableEquivalences(importedComponent, map, importedComponentBaseIndexStack);
        generateEquivalenceMap(importedComponent, map, importedComponentBaseIndexStack);

        // Rebase the generated equivalence map from the source component to the destination component.
        auto rebasedMap = rebaseEquivalenceMap(map, importedComponentBaseIndexStack, destinationComponentBaseIndexStack);

        // Take a copy of the imported component which will be used to replace the import defined in this model.
        auto importedComponentCopy = importedComponent->clone();
        importedComponentCopy->setName(component->name());

        // Temporarily add component to new model to find units used.
        auto tempModel = Model::create();
        tempModel->addComponent(importedComponentCopy);
        tempModel->linkUnits();
        std::vector<UnitsPtr> requiredUnits;
        for (size_t i = 0; i < tempModel->unitsCount(); ++i) {
            auto u = tempModel->units(i);
            requiredUnits.push_back(u);
        }

        // Make a map of component name to component pointer.
        ComponentNameMap newComponentNames = createComponentNamesMap(importedComponentCopy);
        for (const auto &entry : newComponentNames) {
            std::string newName = entry.first;
            size_t count = 1;
            while (std::find(compNames.begin(), compNames.end(), newName) != compNames.end()) {
                newName += "_" + convertToString(count++);
            }
            if (newName != entry.first) {
                entry.second->setName(newName);
            }
        }

        // If the component 'component' has variables then they are equivalent variables and they
        // need to be exchanged with the real variables from the component 'importedComponent'.
        for (size_t i = 0; i < component->variableCount(); ++i) {
            auto placeholderVariable = component->variable(i);
            for (size_t j = 0; j < placeholderVariable->equivalentVariableCount(); ++j) {
                auto localModelVariable = placeholderVariable->equivalentVariable(j);
                auto importedComponentVariable = importedComponentCopy->variable(placeholderVariable->name());
                Variable::removeEquivalence(placeholderVariable, localModelVariable);
                Variable::addEquivalence(importedComponentVariable, localModelVariable);
            }
        }
        parent->replaceComponent(index, importedComponentCopy);

        // Apply the rebased equivalence map onto the modified model.
        applyEquivalenceMapToModel(rebasedMap, model);

        // Copy over units used in imported component to this model.
        for (const auto &u : requiredUnits) {
            if (!model->hasUnits(u)) {
                size_t count = 0;
                while (!model->hasUnits(u) && model->hasUnits(u->name())) {
                    auto name = u->name();
                    name += "_" + convertToString(++count);
                    u->setName(name);
                }
                model->addUnits(u);
            }
        }
    }
}

void flattenComponentTree(const ComponentEntityPtr &parent, const ComponentPtr &component, size_t componentIndex)
{
    flattenComponent(parent, component, componentIndex);

    for (size_t index = 0; index < component->componentCount(); ++index) {
        auto c = component->component(index);
        flattenComponentTree(component, c, index);
    }
}

void Model::flatten()
{
    if (hasUnresolvedImports()) {
        return;
    }

    while (hasImports()) {
        // Go through Units and instantiate any imported Units.
        for (size_t index = 0; index < unitsCount(); ++index) {
            auto u = units(index);
            if (u->isImport()) {
                auto importedUnits = u->importSource()->model()->units(u->importReference());
                auto importedUnitsCopy = importedUnits->clone();
                importedUnitsCopy->setName(u->name());
                replaceUnits(index, importedUnitsCopy);
            }
        }

        // Go through Components and instatiate any imported Components
        for (size_t index = 0; index < componentCount(); ++index) {
            auto c = component(index);
            flattenComponentTree(shared_from_this(), c, index);
        }
    }
}

} // namespace libcellml

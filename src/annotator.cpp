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

#include "libcellml/annotator.h"

#include <algorithm>
#include <sstream>
#include <unordered_map>

#include "libcellml/component.h"
#include "libcellml/importsource.h"
#include "libcellml/model.h"
#include "libcellml/namedentity.h"
#include "libcellml/printer.h"
#include "libcellml/reset.h"
#include "libcellml/types.h"
#include "libcellml/units.h"
#include "libcellml/variable.h"

#include "internaltypes.h"
#include "namespaces.h"
#include "utilities.h"

namespace libcellml {

struct Annotator::AnnotatorImpl
{
    Annotator *mAnnotator = nullptr;
    ItemList mIdList;
    ModelPtr mModel = nullptr;
    size_t mCounter = 0xb4da55;
    size_t mHash = 0;
    bool mIsBuilt = false;

    std::string makeUniqueId();
    void doSetAllAutomaticIds();
    void doSetModelIds();
    void doSetImportSourceIds();
    void doSetUnitsIds();
    void doSetUnitIds();
    void doSetComponentIds(const ComponentPtr &parent);
    void doSetVariableIds(const ComponentPtr &parent);
    void doSetResetIds(const ComponentPtr &parent);
    void doSetResetValueIds(const ComponentPtr &parent);
    void doSetTestValueIds(const ComponentPtr &parent);
    void doSetEncapsulationIds();
    void doSetConnectionIds(const ComponentPtr &parent);
    void doSetMapVariablesIds(const ComponentPtr &parent);
    void doSetComponentRefIds(const ComponentPtr &parent);
    void doClearComponentIds(const ComponentPtr &component);

    size_t getHash();
    void updateHash();
    void doUpdateComponentHash(ComponentPtr &component, std::string &idsString);
};

Annotator::Annotator()
    : mPimpl(new AnnotatorImpl())
{
    mPimpl->mAnnotator = this;
    mPimpl->mIdList = std::multimap<std::string, AnyItem>();
    mPimpl->mCounter = 0xb4da55;
    mPimpl->mHash = 0;
    mPimpl->mIsBuilt = false;
}

Annotator::~Annotator()
{
    delete mPimpl;
}

AnnotatorPtr Annotator::create() noexcept
{
    return std::shared_ptr<Annotator> {new Annotator {}};
}

void listComponentIdsAndItems(const ComponentPtr &component, ItemList &idList)
{
    std::string id = component->id();
    if (!id.empty()) {
        idList.insert(std::make_pair(id, std::make_pair(Annotator::Type::COMPONENT, component)));
    }
    // Imports.
    if (component->isImport() && component->importSource() != nullptr) {
        id = component->importSource()->id();
        if (!id.empty()) {
            idList.insert(std::make_pair(id, std::make_pair(Annotator::Type::IMPORT, component->importSource())));
        }
    }
    // Component reference in encapsulation structure.
    id = component->encapsulationId();
    if (!id.empty()) {
        idList.insert(std::make_pair(id, std::make_pair(Annotator::Type::COMPONENT_REF, component)));
    }
    // Variables.
    for (size_t v = 0; v < component->variableCount(); ++v) {
        id = component->variable(v)->id();
        if (!id.empty()) {
            idList.insert(std::make_pair(id, std::make_pair(Annotator::Type::VARIABLE, component->variable(v))));
        }
        for (size_t e = 0; e < component->variable(v)->equivalentVariableCount(); ++e) {
            // Equivalent variable mappings.
            id = Variable::equivalenceMappingId(component->variable(v), component->variable(v)->equivalentVariable(e));
            if (!id.empty()) {
                // Check whether this connection has already been recorded.  Since connections could be recorded from either
                // side this is a separate check for duplicates.  We can't rely on the variables having names to set an order
                // either.
                bool found = false;
                if (idList.count(id) != 0) {
                    // Get the range of items with this id:
                    auto rangePair = idList.equal_range(id);
                    for (auto it = rangePair.first; it != rangePair.second; ++it) {
                        // Make sure it's also a MAP_VARIABLES item.
                        if (it->second.first == Annotator::Type::MAP_VARIABLES) {
                            auto testPair = std::any_cast<VariablePair>(it->second.second);
                            if ((testPair.first == component->variable(v)->equivalentVariable(e)) && (testPair.second == component->variable(v))) {
                                found = true;
                            }
                        }
                    }
                }
                if (!found) {
                    idList.insert(std::make_pair(id, std::make_pair(Annotator::Type::MAP_VARIABLES, std::make_pair(component->variable(v), component->variable(v)->equivalentVariable(e)))));
                }
            }

            // Connections.
            id = Variable::equivalenceConnectionId(component->variable(v), component->variable(v)->equivalentVariable(e));
            if (!id.empty()) {
                // Check whether this connection has already been recorded.  Since connections could be recorded from either
                // side this is a separate check for duplicates.  We can't rely on the variables having names to set an order
                // either.
                bool found = false;
                if (idList.count(id) != 0) {
                    // Get the range of items with this id:
                    auto rangePair = idList.equal_range(id);
                    for (auto it = rangePair.first; it != rangePair.second; ++it) {
                        // Make sure it's also a CONNECTION item.
                        if (it->second.first == Annotator::Type::CONNECTION) {
                            auto testPair = std::any_cast<VariablePair>(it->second.second);
                            if ((owningComponent(testPair.first) == owningComponent(component->variable(v)->equivalentVariable(e))) && (owningComponent(testPair.second) == owningComponent(component->variable(v)))) {
                                found = true;
                            } else if ((owningComponent(testPair.second) == owningComponent(component->variable(v)->equivalentVariable(e))) && (owningComponent(testPair.first) == owningComponent(component->variable(v)))) {
                                found = true;
                            }
                        }
                    }
                }
                if (!found) {
                    idList.insert(std::make_pair(id, std::make_pair(Annotator::Type::CONNECTION, std::make_pair(component->variable(v), component->variable(v)->equivalentVariable(e)))));
                }
            }
        }
    }
    // Resets.
    for (size_t r = 0; r < component->resetCount(); ++r) {
        id = component->reset(r)->id();
        if (!id.empty()) {
            idList.insert(std::make_pair(id, std::make_pair(Annotator::Type::RESET, component->reset(r))));
        }
        id = component->reset(r)->testValueId();
        if (!id.empty()) {
            idList.insert(std::make_pair(id, std::make_pair(Annotator::Type::TEST_VALUE, component->reset(r))));
            // idList.insert(std::make_pair(id, std::make_pair(Annotator::Type::TEST_VALUE, component->reset(r)->testValue())));
        }
        id = component->reset(r)->resetValueId();
        if (!id.empty()) {
            idList.insert(std::make_pair(id, std::make_pair(Annotator::Type::RESET_VALUE, component->reset(r))));
            // idList.insert(std::make_pair(id, std::make_pair(Annotator::Type::RESET_VALUE, component->reset(r)->resetValue())));
        }
    }

    for (size_t c = 0; c < component->componentCount(); ++c) {
        listComponentIdsAndItems(component->component(c), idList);
    }
}

ItemList listIdsAndItems(const ModelPtr &model)
{
    // Collect all existing ids in a list and return. NB can't use a map or a set as we need to be able to print
    // invalid models (with duplicated ids) too.

    ItemList idList;
    // Model.
    std::string id = model->id();
    if (!id.empty()) {
        idList.insert(std::make_pair(id, std::make_pair(Annotator::Type::MODEL, model)));
    }

    // Units.
    for (size_t u = 0; u < model->unitsCount(); ++u) {
        id = model->units(u)->id();
        if (!id.empty()) {
            idList.insert(std::make_pair(id, std::make_pair(Annotator::Type::UNITS, model->units(u))));
        }
        for (size_t i = 0; i < model->units(u)->unitCount(); ++i) {
            std::string prefix;
            std::string reference;
            double exponent;
            double multiplier;
            model->units(u)->unitAttributes(i, reference, prefix, exponent, multiplier, id);
            if (!id.empty()) {
                idList.insert(std::make_pair(id, std::make_pair(Annotator::Type::UNIT, std::make_pair(model->units(u), i))));
            }
        }
        if (model->units(u)->isImport() && model->units(u)->importSource() != nullptr) {
            id = model->units(u)->importSource()->id();
            idList.insert(std::make_pair(id, std::make_pair(Annotator::Type::IMPORT, model->units(u)->importSource())));
        }
    }
    // Components.
    for (size_t c = 0; c < model->componentCount(); ++c) {
        listComponentIdsAndItems(model->component(c), idList);
    }
    // Encapsulation.
    id = model->encapsulationId();
    if (!id.empty()) {
        idList.insert(std::make_pair(id, std::make_pair(Annotator::Type::ENCAPSULATION, model)));
    }

    return idList;
}

void Annotator::build(const ModelPtr &model)
{
    removeAllIssues();
    mPimpl->mIdList.clear();
    mPimpl->mIdList = listIdsAndItems(model);

    // KRM not sure that we need this now that we can handle duplicates more cleanly?
    for (auto it = mPimpl->mIdList.begin(), end = mPimpl->mIdList.end(); it != end; it = mPimpl->mIdList.upper_bound(it->first)) {
        auto id = it->first;
        if (mPimpl->mIdList.count(id) > 1) {
            auto issue = libcellml::Issue::create();
            issue->setDescription("The id '" + id + "' occurs " + std::to_string(mPimpl->mIdList.count(id)) + " times in the model.");
            issue->setLevel(Issue::Level::WARNING);
            addIssue(issue);
        }
    }

    mPimpl->mModel = model;
    mPimpl->mHash = mPimpl->getHash();
    mPimpl->mIsBuilt = true;
}

AnyItem Annotator::item(const std::string &id)
{
    AnyItem i;
    if (!isBuilt()) {
        auto issue = libcellml::Issue::create();
        issue->setDescription("The Annotator is out-of-date with the stored model.  Please use the build function before attempting to access items by their id.");
        issue->setLevel(libcellml::Issue::Level::ERROR);
        addIssue(issue);
        i = std::make_pair(Annotator::Type::ISSUE, issue);
        return i;
    }
    if (mPimpl->mIdList.empty()) {
        // Setting the error message to be the same as below.
        auto issue = libcellml::Issue::create();
        issue->setDescription("Could not find an item with an id of '" + id + "' in the model.");
        issue->setLevel(libcellml::Issue::Level::WARNING);
        addIssue(issue);
        i = std::make_pair(Annotator::Type::ISSUE, issue);
        return i;
    }

    // Check whether the id has been duplicated in the model.
    if (!isUnique(id, true)) {
        // Get the issue created inside the isUnique function and return it.
        auto c = issue(issueCount() - 1);
        i = std::make_pair(Annotator::Type::ISSUE, c);
        return i;
    }
    return item(id, 0);
}

AnyItem Annotator::item(const std::string &id, size_t index)
{
    // Retrieve the item from the idList.
    if (index >= mPimpl->mIdList.count(id)) {
        auto issue = libcellml::Issue::create();
        issue->setDescription("There are " + std::to_string(duplicateCount(id)) + " items with an id of '" + id + "'. The supplied index " + std::to_string(index) + " is out of range.");
        issue->setLevel(libcellml::Issue::Level::WARNING);
        addIssue(issue);
        auto i = std::make_pair(Annotator::Type::ISSUE, issue);
        // Adding the requested id string and this issue to the map, so that future requests (ie: to the .second)
        // will return the same IssuePtr rather than creating a new one.
        mPimpl->mIdList.insert(std::make_pair(id, i));
        return std::move(i);
    }
    return std::move(items(id)[index]);
}

bool Annotator::isUnique(const std::string &id, bool raiseError = false)
{
    if (mPimpl->mIdList.count(id) > 1) {
        if (raiseError) {
            auto issue = libcellml::Issue::create();
            issue->setDescription("The id '" + id + "' occurs " + std::to_string(mPimpl->mIdList.count(id)) + " times in the model so a unique item cannot be located.");
            issue->setLevel(libcellml::Issue::Level::WARNING);
            addIssue(issue);
        }
        return false;
    }
    return true;
}

std::vector<AnyItem> Annotator::items(const std::string &id)
{
    std::vector<AnyItem> items;
    auto range = mPimpl->mIdList.equal_range(id);
    for (auto it = range.first; it != range.second; ++it) {
        items.push_back(it->second);
    }
    return items;
}

// For bindings, we can't use the <any> type.  This means that we have to provide
// separate functions that will iterate through items with the same id, regardless of
// their type.
// void Annotator::setTemporaryIdForBindings(const std::string &id)
// {
//     mPimpl->mTemporaryId = id;
//     mPimpl->mTemporaryItems = mPimpl->mIdList.equal_range(id);
// }

// void Annotator::unsetTemporaryIdForBindings(){
//     mPimpl->mTemporaryId = "";
//     mPimpl->mTemporaryItems = nullptr;
// }

std::vector<std::string> Annotator::duplicateIds()
{
    std::vector<std::string> ids;
    for (auto i = mPimpl->mIdList.begin(), end = mPimpl->mIdList.end(); i != end; i = mPimpl->mIdList.upper_bound(i->first)) {
        ids.push_back(i->first);
    }
    return ids;
}

ComponentPtr Annotator::component(const std::string &id)
{
    if (!isUnique(id, true)) {
        return nullptr;
    }
    return component(id, 0);
}

VariablePtr Annotator::variable(const std::string &id)
{
    if (!isUnique(id, true)) {
        return nullptr;
    }
    return variable(id, 0);
}

ModelPtr Annotator::model(const std::string &id)
{
    if (!isUnique(id, true)) {
        return nullptr;
    }
    return model(id, 0);
}

UnitsPtr Annotator::units(const std::string &id)
{
    if (!isUnique(id, true)) {
        return nullptr;
    }
    return units(id, 0);
}

ImportSourcePtr Annotator::importSource(const std::string &id)
{
    if (!isUnique(id, true)) {
        return nullptr;
    }
    return importSource(id, 0);
}

ResetPtr Annotator::reset(const std::string &id)
{
    if (!isUnique(id, true)) {
        return nullptr;
    }
    return reset(id, 0);
}

VariablePair Annotator::connection(const std::string &id)
{
    if (!isUnique(id, true)) {
        return std::make_pair(nullptr, nullptr);
    }
    return connection(id, 0);
}

VariablePair Annotator::mapVariables(const std::string &id)
{
    if (!isUnique(id, true)) {
        return std::make_pair(nullptr, nullptr);
    }
    return mapVariables(id, 0);
}

UnitItem Annotator::unit(const std::string &id)
{
    if (!isUnique(id, true)) {
        return std::make_pair(nullptr, 0);
    }
    return unit(id, 0);
}

ComponentPtr Annotator::componentRef(const std::string &id)
{
    if (!isUnique(id, true)) {
        return nullptr;
    }
    return componentRef(id, 0);
}

ResetPtr Annotator::testValue(const std::string &id)
{
    if (!isUnique(id, true)) {
        return nullptr;
    }
    return testValue(id, 0);
}

ResetPtr Annotator::resetValue(const std::string &id)
{
    if (!isUnique(id, true)) {
        return nullptr;
    }
    return resetValue(id, 0);
}

ComponentPtr Annotator::component(const std::string &id, size_t index)
{
    if (!isBuilt()) {
        auto issue = libcellml::Issue::create();
        issue->setDescription("The Annotator is out-of-date with the stored model.  Please use the build function before attempting to access items by their id.");
        issue->setLevel(libcellml::Issue::Level::ERROR);
        addIssue(issue);
        return nullptr;
    }
    if (index >= duplicateCount(id)) {
        auto issue = libcellml::Issue::create();
        issue->setDescription("There are " + std::to_string(duplicateCount(id)) + " items with an id of '" + id + "'. The supplied index " + std::to_string(index) + " is out of range.");
        issue->setLevel(libcellml::Issue::Level::ERROR);
        addIssue(issue);
        return nullptr;
    }
    auto i = items(id).at(index);
    try {
        return std::any_cast<ComponentPtr>(i.second);
    } catch (std::bad_any_cast &e) {
        (void)e;
        return nullptr;
    }
}

VariablePtr Annotator::variable(const std::string &id, size_t index)
{
    if (!isBuilt()) {
        auto issue = libcellml::Issue::create();
        issue->setDescription("The Annotator is out-of-date with the stored model.  Please use the build function before attempting to access items by their id.");
        issue->setLevel(libcellml::Issue::Level::ERROR);
        addIssue(issue);
        return nullptr;
    }
    if (index >= duplicateCount(id)) {
        auto issue = libcellml::Issue::create();
        issue->setDescription("There are " + std::to_string(duplicateCount(id)) + " items with an id of '" + id + "'. The supplied index " + std::to_string(index) + " is out of range.");
        issue->setLevel(libcellml::Issue::Level::ERROR);
        addIssue(issue);
        return nullptr;
    }
    auto i = items(id).at(index);
    try {
        return std::any_cast<VariablePtr>(i.second);
    } catch (std::bad_any_cast &e) {
        (void)e;
        return nullptr;
    }
}

ModelPtr Annotator::model(const std::string &id, size_t index)
{
    if (!isBuilt()) {
        auto issue = libcellml::Issue::create();
        issue->setDescription("The Annotator is out-of-date with the stored model.  Please use the build function before attempting to access items by their id.");
        issue->setLevel(libcellml::Issue::Level::ERROR);
        addIssue(issue);
        return nullptr;
    }
    if (index >= duplicateCount(id)) {
        auto issue = libcellml::Issue::create();
        issue->setDescription("There are " + std::to_string(duplicateCount(id)) + " items with an id of '" + id + "'. The supplied index " + std::to_string(index) + " is out of range.");
        issue->setLevel(libcellml::Issue::Level::ERROR);
        addIssue(issue);
        return nullptr;
    }
    auto i = items(id).at(index);
    try {
        return std::any_cast<ModelPtr>(i.second);
    } catch (std::bad_any_cast &e) {
        (void)e;
        return nullptr;
    }
}

ModelPtr Annotator::encapsulation(const std::string &id)
{
    if (!isUnique(id, true)) {
        return nullptr;
    }
    return encapsulation(id, 0);
}

ModelPtr Annotator::encapsulation(const std::string &id, size_t index)
{
    if (!isBuilt()) {
        auto issue = libcellml::Issue::create();
        issue->setDescription("The Annotator is out-of-date with the stored model.  Please use the build function before attempting to access items by their id.");
        issue->setLevel(libcellml::Issue::Level::ERROR);
        addIssue(issue);
        return nullptr;
    }
    if (index >= duplicateCount(id)) {
        auto issue = libcellml::Issue::create();
        issue->setDescription("There are " + std::to_string(duplicateCount(id)) + " items with an id of '" + id + "'. The supplied index " + std::to_string(index) + " is out of range.");
        issue->setLevel(libcellml::Issue::Level::ERROR);
        addIssue(issue);
        return nullptr;
    }
    auto i = items(id).at(index);
    try {
        return std::any_cast<ModelPtr>(i.second);
    } catch (std::bad_any_cast &e) {
        (void)e;
        return nullptr;
    }
}

UnitsPtr Annotator::units(const std::string &id, size_t index)
{
    if (!isBuilt()) {
        auto issue = libcellml::Issue::create();
        issue->setDescription("The Annotator is out-of-date with the stored model.  Please use the build function before attempting to access items by their id.");
        issue->setLevel(libcellml::Issue::Level::ERROR);
        addIssue(issue);
        return nullptr;
    }
    if (index >= duplicateCount(id)) {
        auto issue = libcellml::Issue::create();
        issue->setDescription("There are " + std::to_string(duplicateCount(id)) + " items with an id of '" + id + "'. The supplied index " + std::to_string(index) + " is out of range.");
        issue->setLevel(libcellml::Issue::Level::ERROR);
        addIssue(issue);
        return nullptr;
    }
    auto i = items(id).at(index);
    try {
        return std::any_cast<UnitsPtr>(i.second);
    } catch (std::bad_any_cast &e) {
        (void)e;
        return nullptr;
    }
}

ImportSourcePtr Annotator::importSource(const std::string &id, size_t index)
{
    if (!isBuilt()) {
        auto issue = libcellml::Issue::create();
        issue->setDescription("The Annotator is out-of-date with the stored model.  Please use the build function before attempting to access items by their id.");
        issue->setLevel(libcellml::Issue::Level::ERROR);
        addIssue(issue);
        return nullptr;
    }
    if (index >= duplicateCount(id)) {
        auto issue = libcellml::Issue::create();
        issue->setDescription("There are " + std::to_string(duplicateCount(id)) + " items with an id of '" + id + "'. The supplied index " + std::to_string(index) + " is out of range.");
        issue->setLevel(libcellml::Issue::Level::ERROR);
        addIssue(issue);
        return nullptr;
    }
    auto i = items(id).at(index);
    try {
        return std::any_cast<ImportSourcePtr>(i.second);
    } catch (std::bad_any_cast &e) {
        (void)e;
        return nullptr;
    }
}

ResetPtr Annotator::reset(const std::string &id, size_t index)
{
    if (!isBuilt()) {
        auto issue = libcellml::Issue::create();
        issue->setDescription("The Annotator is out-of-date with the stored model.  Please use the build function before attempting to access items by their id.");
        issue->setLevel(libcellml::Issue::Level::ERROR);
        addIssue(issue);
        return nullptr;
    }
    if (index >= duplicateCount(id)) {
        auto issue = libcellml::Issue::create();
        issue->setDescription("There are " + std::to_string(duplicateCount(id)) + " items with an id of '" + id + "'. The supplied index " + std::to_string(index) + " is out of range.");
        issue->setLevel(libcellml::Issue::Level::ERROR);
        addIssue(issue);
        return nullptr;
    }
    auto i = items(id).at(index);
    try {
        return std::any_cast<ResetPtr>(i.second);
    } catch (std::bad_any_cast &e) {
        (void)e;
        return nullptr;
    }
}

VariablePair Annotator::connection(const std::string &id, size_t index)
{
    if (!isBuilt()) {
        auto issue = libcellml::Issue::create();
        issue->setDescription("The Annotator is out-of-date with the stored model.  Please use the build function before attempting to access items by their id.");
        issue->setLevel(libcellml::Issue::Level::ERROR);
        addIssue(issue);
        return std::make_pair(nullptr, nullptr);
    }
    if (index >= duplicateCount(id)) {
        auto issue = libcellml::Issue::create();
        issue->setDescription("There are " + std::to_string(duplicateCount(id)) + " items with an id of '" + id + "'. The supplied index " + std::to_string(index) + " is out of range.");
        issue->setLevel(libcellml::Issue::Level::ERROR);
        addIssue(issue);
        return std::make_pair(nullptr, nullptr);
    }
    auto i = items(id).at(index);
    try {
        return std::any_cast<VariablePair>(i.second);
    } catch (std::bad_any_cast &e) {
        (void)e;
        return std::make_pair(nullptr, nullptr);
    }
}

VariablePair Annotator::mapVariables(const std::string &id, size_t index)
{
    if (!isBuilt()) {
        auto issue = libcellml::Issue::create();
        issue->setDescription("The Annotator is out-of-date with the stored model.  Please use the build function before attempting to access items by their id.");
        issue->setLevel(libcellml::Issue::Level::ERROR);
        addIssue(issue);
        return std::make_pair(nullptr, nullptr);
    }
    if (index >= duplicateCount(id)) {
        auto issue = libcellml::Issue::create();
        issue->setDescription("There are " + std::to_string(duplicateCount(id)) + " items with an id of '" + id + "'. The supplied index " + std::to_string(index) + " is out of range.");
        issue->setLevel(libcellml::Issue::Level::ERROR);
        addIssue(issue);
        return std::make_pair(nullptr, nullptr);
    }
    auto i = items(id).at(index);

    try {
        return std::any_cast<VariablePair>(i.second);
    } catch (std::bad_any_cast &e) {
        (void)e;
        return std::make_pair(nullptr, nullptr);
    }
}

UnitItem Annotator::unit(const std::string &id, size_t index)
{
    if (!isBuilt()) {
        auto issue = libcellml::Issue::create();
        issue->setDescription("The Annotator is out-of-date with the stored model.  Please use the build function before attempting to access items by their id.");
        issue->setLevel(libcellml::Issue::Level::ERROR);
        addIssue(issue);
        return std::make_pair(nullptr, 0);
    }
    if (index >= duplicateCount(id)) {
        auto issue = libcellml::Issue::create();
        issue->setDescription("There are " + std::to_string(duplicateCount(id)) + " items with an id of '" + id + "'. The supplied index " + std::to_string(index) + " is out of range.");
        issue->setLevel(libcellml::Issue::Level::ERROR);
        addIssue(issue);
        return std::make_pair(nullptr, 0);
    }
    auto i = items(id).at(index);
    try {
        return std::any_cast<UnitItem>(i.second);
    } catch (std::bad_any_cast &e) {
        (void)e;
        return std::make_pair(nullptr, -1);
    }
}

ComponentPtr Annotator::componentRef(const std::string &id, size_t index)
{
    if (!isBuilt()) {
        auto issue = libcellml::Issue::create();
        issue->setDescription("The Annotator is out-of-date with the stored model.  Please use the build function before attempting to access items by their id.");
        issue->setLevel(libcellml::Issue::Level::ERROR);
        addIssue(issue);
        return nullptr;
    }
    if (index >= duplicateCount(id)) {
        auto issue = libcellml::Issue::create();
        issue->setDescription("There are " + std::to_string(duplicateCount(id)) + " items with an id of '" + id + "'. The supplied index " + std::to_string(index) + " is out of range.");
        issue->setLevel(libcellml::Issue::Level::ERROR);
        addIssue(issue);
        return nullptr;
    }
    auto i = items(id).at(index);
    try {
        return std::any_cast<ComponentPtr>(i.second);
    } catch (std::bad_any_cast &e) {
        (void)e;
        return nullptr;
    }
}

ResetPtr Annotator::testValue(const std::string &id, size_t index)
{
    if (!isBuilt()) {
        auto issue = libcellml::Issue::create();
        issue->setDescription("The Annotator is out-of-date with the stored model.  Please use the build function before attempting to access items by their id.");
        issue->setLevel(libcellml::Issue::Level::ERROR);
        addIssue(issue);
        return nullptr;
    }
    if (index >= duplicateCount(id)) {
        auto issue = libcellml::Issue::create();
        issue->setDescription("There are " + std::to_string(duplicateCount(id)) + " items with an id of '" + id + "'. The supplied index " + std::to_string(index) + " is out of range.");
        issue->setLevel(libcellml::Issue::Level::ERROR);
        addIssue(issue);
        return nullptr;
    }
    auto i = items(id).at(index);
    try {
        return std::any_cast<ResetPtr>(i.second);
    } catch (std::bad_any_cast &e) {
        (void)e;
        return nullptr;
    }
}

ResetPtr Annotator::resetValue(const std::string &id, size_t index)
{
    if (!isBuilt()) {
        auto issue = libcellml::Issue::create();
        issue->setDescription("The Annotator is out-of-date with the stored model.  Please use the build function before attempting to access items by their id.");
        issue->setLevel(libcellml::Issue::Level::ERROR);
        addIssue(issue);
        return nullptr;
    }
    if (index >= duplicateCount(id)) {
        auto issue = libcellml::Issue::create();
        issue->setDescription("There are " + std::to_string(duplicateCount(id)) + " items with an id of '" + id + "'. The supplied index " + std::to_string(index) + " is out of range.");
        issue->setLevel(libcellml::Issue::Level::ERROR);
        addIssue(issue);
        return nullptr;
    }
    auto i = items(id).at(index);
    try {
        return std::any_cast<ResetPtr>(i.second);
    } catch (std::bad_any_cast &e) {
        (void)e;
        return nullptr;
    }
}

void Annotator::clearAllIds()
{
    if (mPimpl->mModel == nullptr) {
        auto issue = Issue::create();
        issue->setDescription("The Annotator does not have a model stored; no action has been taken.");
        issue->setLevel(Issue::Level::ERROR);
        addIssue(issue);
        return;
    }

    mPimpl->mModel->setId("");
    for (size_t i = 0; i < mPimpl->mModel->importSourceCount(); ++i) {
        mPimpl->mModel->importSource(i)->setId("");
    }
    for (size_t i = 0; i < mPimpl->mModel->unitsCount(); ++i) {
        mPimpl->mModel->units(i)->setId("");
        for (size_t j = 0; j < mPimpl->mModel->units(i)->unitCount(); ++j) {
            mPimpl->mModel->units(i)->setUnitId(j, "");
        }
    }
    for (size_t i = 0; i < mPimpl->mModel->componentCount(); ++i) {
        mPimpl->doClearComponentIds(mPimpl->mModel->component(i));
    }
    mPimpl->mModel->setEncapsulationId("");

    mPimpl->mIdList.clear();
    // Set to true even though it hasn't been built, as technically the library
    // is up-to-date with the model, even though it's empty.
    mPimpl->mHash = 0;
    removeAllIssues();
}

void Annotator::clearAllIds(ModelPtr &model)
{
    // Helper function so that you don't have to build an annotation library
    // for a model you're going to wipe anyway.
    if (model == nullptr) {
        return;
    }
    mPimpl->mModel = model;
    clearAllIds();
}

void Annotator::AnnotatorImpl::doClearComponentIds(const ComponentPtr &component)
{
    component->setEncapsulationId("");
    component->setId("");
    for (size_t i = 0; i < component->variableCount(); ++i) {
        component->variable(i)->setId("");
        for (size_t j = 0; j < component->variable(i)->equivalentVariableCount(); ++j) {
            Variable::setEquivalenceConnectionId(component->variable(i), component->variable(i)->equivalentVariable(j), "");
            Variable::setEquivalenceMappingId(component->variable(i), component->variable(i)->equivalentVariable(j), "");
        }
    }
    for (size_t i = 0; i < component->resetCount(); ++i) {
        component->reset(i)->setId("");
        component->reset(i)->setResetValueId("");
        component->reset(i)->setTestValueId("");
    }
    for (size_t i = 0; i < component->componentCount(); ++i) {
        doClearComponentIds(component->component(i));
    }
}

bool Annotator::assignAllIds()
{
    // Add automatically generated id strings to every item (excepting MathML) in the model which
    // can be annotated.
    if (mPimpl->mModel == nullptr) {
        auto issue = Issue::create();
        issue->setDescription("The Annotator does not have any Model stored; no action has been taken.");
        issue->setLevel(Issue::Level::ERROR);
        addIssue(issue);
        return false;
    }

    clearAllIds();
    mPimpl->doSetAllAutomaticIds();
    build(mPimpl->mModel);
    return true;
}

bool Annotator::assignAllIds(ModelPtr &model)
{
    // Helper function so that the users don't have to build a model library when they're
    // about to overwrite it all anyway.
    if (model == nullptr) {
        auto issue = Issue::create();
        issue->setDescription("The Model supplied is a nullptr. No action has been taken.");
        issue->setLevel(Issue::Level::ERROR);
        return false;
    }
    mPimpl->mModel = model;
    return assignAllIds();
}

bool Annotator::assignIds(Annotator::Type type)
{
    bool changed = false;
    switch (type) {
    case Annotator::Type::COMPONENT:
        for (size_t c = 0; c < mPimpl->mModel->componentCount(); ++c) {
            mPimpl->doSetComponentIds(mPimpl->mModel->component(c));
        }
        changed = true;
        break;
    case Annotator::Type::COMPONENT_REF:
        for (size_t c = 0; c < mPimpl->mModel->componentCount(); ++c) {
            mPimpl->doSetComponentRefIds(mPimpl->mModel->component(c));
        }
        changed = true;
        break;
    case Annotator::Type::CONNECTION:
        for (size_t c = 0; c < mPimpl->mModel->componentCount(); ++c) {
            mPimpl->doSetConnectionIds(mPimpl->mModel->component(c));
        }
        changed = true;
        break;
    case Annotator::Type::ENCAPSULATION:
        mPimpl->doSetEncapsulationIds();
        changed = true;
        break;
    case Annotator::Type::IMPORT:
        mPimpl->doSetImportSourceIds();
        changed = true;
        break;
    case Annotator::Type::MAP_VARIABLES:
        for (size_t c = 0; c < mPimpl->mModel->componentCount(); ++c) {
            mPimpl->doSetMapVariablesIds(mPimpl->mModel->component(c));
        }
        changed = true;
        break;
    case Annotator::Type::MODEL:
        mPimpl->doSetModelIds();
        changed = true;
        break;
    case Annotator::Type::RESET:
        for (size_t c = 0; c < mPimpl->mModel->componentCount(); ++c) {
            mPimpl->doSetResetIds(mPimpl->mModel->component(c));
        }
        changed = true;
        break;
    case Annotator::Type::RESET_VALUE:
        for (size_t c = 0; c < mPimpl->mModel->componentCount(); ++c) {
            mPimpl->doSetResetValueIds(mPimpl->mModel->component(c));
        }
        changed = true;
        break;
    case Annotator::Type::TEST_VALUE:
        for (size_t c = 0; c < mPimpl->mModel->componentCount(); ++c) {
            mPimpl->doSetTestValueIds(mPimpl->mModel->component(c));
        }
        changed = true;
        break;
    case Annotator::Type::UNIT:
        mPimpl->doSetUnitIds();
        changed = true;
        break;
    case Annotator::Type::UNITS:
        mPimpl->doSetUnitsIds();
        changed = true;
        break;
    case Annotator::Type::VARIABLE:
        for (size_t c = 0; c < mPimpl->mModel->componentCount(); ++c) {
            mPimpl->doSetVariableIds(mPimpl->mModel->component(c));
        }
        changed = true;
        break;
    case Annotator::Type::ISSUE:
        break;
    }
    build(mPimpl->mModel);
    return changed;
}

void Annotator::AnnotatorImpl::doSetImportSourceIds()
{
    // Import items.
    for (size_t i = 0; i < mModel->importSourceCount(); ++i) {
        auto is = mModel->importSource(i);
        if (is->id().empty()) {
            auto id = makeUniqueId();
            is->setId(id);
            mIdList.insert(std::make_pair(id, std::make_pair(Annotator::Type::IMPORT, is)));
        }
    }
}

void Annotator::AnnotatorImpl::doSetUnitsIds()
{
    // Units and unit items.
    for (size_t u = 0; u < mModel->unitsCount(); ++u) {
        auto us = mModel->units(u);
        if (us->id().empty()) {
            auto id = makeUniqueId();
            us->setId(id);
            mIdList.insert(std::make_pair(id, std::make_pair(Annotator::Type::UNITS, us)));
        }
    }
}

void Annotator::AnnotatorImpl::doSetUnitIds()
{
    for (size_t u = 0; u < mModel->unitsCount(); ++u) {
        auto us = mModel->units(u);
        for (size_t i = 0; i < us->unitCount(); i++) {
            if (us->unitId(i).empty()) {
                auto id = makeUniqueId();
                us->setUnitId(i, id);
                mIdList.insert(std::make_pair(id, std::make_pair(Annotator::Type::UNIT, std::make_pair(us, i))));
            }
        }
    }
}

void Annotator::AnnotatorImpl::doSetComponentIds(const ComponentPtr &parent)
{
    if (parent->id().empty()) {
        auto id = makeUniqueId();
        parent->setId(id);
        mIdList.insert(std::make_pair(id, std::make_pair(Annotator::Type::COMPONENT, parent)));
    }
    for (size_t c = 0; c < parent->componentCount(); ++c) {
        if (parent->component(c)->id().empty()) {
            auto id = makeUniqueId();
            parent->component(c)->setId(id);
            mIdList.insert(std::make_pair(id, std::make_pair(Annotator::Type::COMPONENT, parent->component(c))));
        }
        doSetComponentIds(parent->component(c));
    }
}

void Annotator::AnnotatorImpl::doSetVariableIds(const ComponentPtr &parent)
{
    for (size_t v = 0; v < parent->variableCount(); ++v) {
        if (parent->variable(v)->id().empty()) {
            auto id = makeUniqueId();
            parent->variable(v)->setId(id);
            mIdList.insert(std::make_pair(id, std::make_pair(Annotator::Type::VARIABLE, parent->variable(v))));
        }
    }
    for (size_t c = 0; c < parent->componentCount(); ++c) {
        doSetVariableIds(parent->component(c));
    }
}

void Annotator::AnnotatorImpl::doSetResetIds(const ComponentPtr &parent)
{
    for (size_t r = 0; r < parent->resetCount(); ++r) {
        if (parent->reset(r)->id().empty()) {
            auto id = makeUniqueId();
            parent->reset(r)->setId(id);
            mIdList.insert(std::make_pair(id, std::make_pair(Annotator::Type::RESET, parent->reset(r))));
        }
    }
    for (size_t c = 0; c < parent->componentCount(); ++c) {
        doSetResetIds(parent->component(c));
    }
}

void Annotator::AnnotatorImpl::doSetResetValueIds(const ComponentPtr &parent)
{
    for (size_t r = 0; r < parent->resetCount(); ++r) {
        if (parent->reset(r)->resetValueId().empty()) {
            auto id = makeUniqueId();
            parent->reset(r)->setResetValueId(id);
            mIdList.insert(std::make_pair(id, std::make_pair(Annotator::Type::RESET_VALUE, parent->reset(r))));
        }
    }
    for (size_t c = 0; c < parent->componentCount(); ++c) {
        doSetResetValueIds(parent->component(c));
    }
}

void Annotator::AnnotatorImpl::doSetTestValueIds(const ComponentPtr &parent)
{
    for (size_t r = 0; r < parent->resetCount(); ++r) {
        if (parent->reset(r)->testValueId().empty()) {
            auto id = makeUniqueId();
            parent->reset(r)->setTestValueId(id);
            mIdList.insert(std::make_pair(id, std::make_pair(Annotator::Type::TEST_VALUE, parent->reset(r))));
        }
    }
    for (size_t c = 0; c < parent->componentCount(); ++c) {
        doSetTestValueIds(parent->component(c));
    }
}

void Annotator::AnnotatorImpl::doSetConnectionIds(const ComponentPtr &parent)
{
    for (size_t v = 0; v < parent->variableCount(); ++v) {
        auto v1 = parent->variable(v);
        for (size_t e = 0; e < v1->equivalentVariableCount(); ++e) {
            auto v2 = v1->equivalentVariable(e);
            if (Variable::equivalenceConnectionId(v1, v2).empty()) {
                auto id = makeUniqueId();
                Variable::setEquivalenceConnectionId(v1, v2, id);
                auto v1v2 = std::make_pair(v1, v2);
                mIdList.insert(std::make_pair(id, std::make_pair(Annotator::Type::CONNECTION, v1v2)));
            }
        }
    }
    for (size_t c = 0; c < parent->componentCount(); ++c) {
        doSetConnectionIds(parent->component(c));
    }
}

void Annotator::AnnotatorImpl::doSetMapVariablesIds(const ComponentPtr &parent)
{
    for (size_t v = 0; v < parent->variableCount(); ++v) {
        auto v1 = parent->variable(v);
        for (size_t e = 0; e < v1->equivalentVariableCount(); ++e) {
            auto v2 = v1->equivalentVariable(e);
            if (Variable::equivalenceMappingId(v1, v2).empty()) {
                auto id = makeUniqueId();
                Variable::setEquivalenceMappingId(v1, v2, id);
                auto v1v2 = std::make_pair(v1, v2);
                mIdList.insert(std::make_pair(id, std::make_pair(Annotator::Type::MAP_VARIABLES, v1v2)));
            }
        }
    }
    for (size_t c = 0; c < parent->componentCount(); ++c) {
        doSetMapVariablesIds(parent->component(c));
    }
}

void Annotator::AnnotatorImpl::doSetComponentRefIds(const ComponentPtr &parent)
{
    if (parent->encapsulationId().empty() && parent->componentCount() > 0) {
        auto id = makeUniqueId();
        parent->setEncapsulationId(id);
        mIdList.insert(std::make_pair(id, std::make_pair(Annotator::Type::COMPONENT_REF, parent)));
    }
    for (size_t c = 0; c < parent->componentCount(); ++c) {
        if (parent->component(c)->encapsulationId().empty()) {
            auto id = makeUniqueId();
            parent->component(c)->setEncapsulationId(id);
            mIdList.insert(std::make_pair(id, std::make_pair(Annotator::Type::COMPONENT_REF, parent->component(c))));
        }
        doSetComponentRefIds(parent->component(c));
    }
}

void Annotator::AnnotatorImpl::doSetEncapsulationIds()
{
    if (mModel->encapsulationId().empty()) {
        auto id = makeUniqueId();
        mModel->setEncapsulationId(id);
        mIdList.insert(std::make_pair(id, std::make_pair(Annotator::Type::ENCAPSULATION, mModel)));
    }
}

void Annotator::AnnotatorImpl::doSetModelIds()
{
    if (mModel->id().empty()) {
        auto id = makeUniqueId();
        mModel->setId(id);
        mIdList.insert(std::make_pair(id, std::make_pair(Annotator::Type::MODEL, mModel)));
    }
}

void Annotator::AnnotatorImpl::doSetAllAutomaticIds()
{
    doSetModelIds();
    doSetImportSourceIds();
    doSetUnitsIds();
    doSetUnitIds();
    for (size_t c = 0; c < mModel->componentCount(); ++c) {
        doSetComponentIds(mModel->component(c));
        doSetVariableIds(mModel->component(c));
        doSetResetIds(mModel->component(c));
        doSetResetValueIds(mModel->component(c));
        doSetTestValueIds(mModel->component(c));
        doSetConnectionIds(mModel->component(c));
        doSetMapVariablesIds(mModel->component(c));
        doSetComponentRefIds(mModel->component(c));
    }
    doSetEncapsulationIds();
}

std::string Annotator::AnnotatorImpl::makeUniqueId()
{
    // Because the hexadecimal counter starts high enough that it will always have a letter as the first character,
    // we don't need to prefix it with any other string to be valid.  This is stored in the mCounter variable
    // so that "holes" in the automatic id list are not filled; they will always build from the previous
    // maximum value.

    std::stringstream stream;
    stream << std::hex << mCounter;
    std::string id = stream.str();
    stream.str(std::string());

    while (mIdList.count(id) != 0) {
        ++mCounter;
        stream << std::hex << mCounter;
        id = stream.str();
        stream.str(std::string());
    }
    // NB: This is only as unique as the information in mIdList permits.  That array must be updated
    // outside this function.
    return id;
}

// bool Annotator::repairNonUniqueIds()
// {
//     bool changed = false;
//     ComponentPtr component;
//     ModelPtr model;
//     ImportSourcePtr importSource;
//     VariablePtr variable;
//     UnitsPtr units;
//     ResetPtr reset;
//     VariablePair variablePair;
//     UnitItem unitItem;
//     // Function to go through duplicated ids and rename them uniquely.
//     for (auto i = mPimpl->mIdList.begin(), end = mPimpl->mIdList.end(); i != end; i = mPimpl->mIdList.upper_bound(i->first)) {
//         auto id = i->first;
//         if (mPimpl->mIdList.count(id) > 1) {
//             auto range = mPimpl->mIdList.equal_range(id);
//             // ++range.first;
//             for (auto it = range.first; it != range.second; ++it) {
//                 switch (it->second.first) {
//                 case Annotator::Type::COMPONENT:
//                     component = std::any_cast<ComponentPtr>(it->second.second);
//                     id = mPimpl->makeUniqueId();
//                     component->setId(id);
//                     mPimpl->mIdList.insert(std::make_pair(id, std::make_pair(Annotator::Type::COMPONENT, component)));
//                     changed = true;
//                     break;
//                 case Annotator::Type::COMPONENT_REF:
//                     component = std::any_cast<ComponentPtr>(it->second.second);
//                     id = mPimpl->makeUniqueId();
//                     component->setEncapsulationId(id);
//                     mPimpl->mIdList.insert(std::make_pair(id, std::make_pair(Annotator::Type::COMPONENT_REF, component)));
//                     changed = true;
//                     break;
//                 case Annotator::Type::CONNECTION:
//                     variablePair = std::any_cast<VariablePair>(it->second.second);
//                     id = mPimpl->makeUniqueId();
//                     Variable::setEquivalenceConnectionId(variablePair.first, variablePair.second, id);
//                     mPimpl->mIdList.insert(std::make_pair(id, std::make_pair(Annotator::Type::CONNECTION, variablePair)));
//                     changed = true;
//                     break;
//                 case Annotator::Type::ENCAPSULATION:
//                     model = std::any_cast<ModelPtr>(it->second.second);
//                     id = mPimpl->makeUniqueId();
//                     model->setEncapsulationId(id);
//                     mPimpl->mIdList.insert(std::make_pair(id, std::make_pair(Annotator::Type::ENCAPSULATION, model)));
//                     changed = true;
//                     break;
//                 case Annotator::Type::IMPORT:
//                     importSource = std::any_cast<ImportSourcePtr>(it->second.second);
//                     id = mPimpl->makeUniqueId();
//                     importSource->setId(id);
//                     mPimpl->mIdList.insert(std::make_pair(id, std::make_pair(Annotator::Type::IMPORT, importSource)));
//                     changed = true;
//                     break;
//                 case Annotator::Type::MAP_VARIABLES:
//                     variablePair = std::any_cast<VariablePair>(it->second.second);
//                     id = mPimpl->makeUniqueId();
//                     Variable::setEquivalenceMappingId(variablePair.first, variablePair.second, id);
//                     mPimpl->mIdList.insert(std::make_pair(id, std::make_pair(Annotator::Type::MAP_VARIABLES, variablePair)));
//                     changed = true;
//                     break;
//                 case Annotator::Type::MODEL:
//                     model = std::any_cast<ModelPtr>(it->second.second);
//                     id = mPimpl->makeUniqueId();
//                     model->setId(id);
//                     mPimpl->mIdList.insert(std::make_pair(id, std::make_pair(Annotator::Type::MODEL, model)));
//                     changed = true;
//                     break;
//                 case Annotator::Type::RESET:
//                     reset = std::any_cast<ResetPtr>(it->second.second);
//                     id = mPimpl->makeUniqueId();
//                     reset->setId(id);
//                     mPimpl->mIdList.insert(std::make_pair(id, std::make_pair(Annotator::Type::RESET_VALUE, reset)));
//                     changed = true;
//                     break;
//                 case Annotator::Type::RESET_VALUE:
//                     reset = std::any_cast<ResetPtr>(it->second.second);
//                     id = mPimpl->makeUniqueId();
//                     reset->setResetValueId(id);
//                     mPimpl->mIdList.insert(std::make_pair(id, std::make_pair(Annotator::Type::RESET_VALUE, reset)));
//                     changed = true;
//                     break;
//                 case Annotator::Type::TEST_VALUE:
//                     reset = std::any_cast<ResetPtr>(it->second.second);
//                     id = mPimpl->makeUniqueId();
//                     reset->setTestValueId(id);
//                     mPimpl->mIdList.insert(std::make_pair(id, std::make_pair(Annotator::Type::TEST_VALUE, reset)));
//                     changed = true;
//                     break;
//                 case Annotator::Type::UNIT:
//                     unitItem = std::any_cast<UnitItem>(it->second.second);
//                     id = mPimpl->makeUniqueId();
//                     unitItem.first->setUnitId(unitItem.second, id);
//                     mPimpl->mIdList.insert(std::make_pair(id, std::make_pair(Annotator::Type::UNIT, unitItem)));
//                     changed = true;
//                     break;
//                 case Annotator::Type::UNITS:
//                     units = std::any_cast<UnitsPtr>(it->second.second);
//                     id = mPimpl->makeUniqueId();
//                     units->setId(id);
//                     mPimpl->mIdList.insert(std::make_pair(id, std::make_pair(Annotator::Type::UNITS, units)));
//                     changed = true;
//                     break;
//                 case Annotator::Type::VARIABLE:
//                     variable = std::any_cast<VariablePtr>(it->second.second);
//                     id = mPimpl->makeUniqueId();
//                     variable->setId(id);
//                     mPimpl->mIdList.insert(std::make_pair(id, std::make_pair(Annotator::Type::VARIABLE, variable)));
//                     changed = true;
//                     break;
//                 }
//             }
//         }
//     }
//     // Clean out records and rebuild.
//     if (changed || (issueCount() > 0)) {
//         build(mPimpl->mModel);
//     }
//     return changed;
// }

std::string Annotator::assignComponentId(const ComponentPtr &component)
{
    auto oldId = component->id();
    auto type = Annotator::Type::COMPONENT;
    std::string id;

    if (owningModel(component) != mPimpl->mModel) {
        return id;
    }
    // NB: the id must be created before the old one is removed from the idList to prevent the
    // reuse of previously allocated ids.
    id = mPimpl->makeUniqueId();
    if (!oldId.empty()) {
        auto range = mPimpl->mIdList.equal_range(oldId);
        for (auto it = range.first; it != range.second; ++it) {
            if ((it->second.first == type) && (std::any_cast<ComponentPtr>(it->second.second) == component)) {
                mPimpl->mIdList.erase(it);
                break;
            }
        }
    }
    component->setId(id);
    mPimpl->mIdList.insert(std::make_pair(id, std::make_pair(type, component)));
    mPimpl->updateHash();
    return id;
}

std::string Annotator::assignComponentRefId(const ComponentPtr &component)
{
    auto oldId = component->encapsulationId();
    auto type = Annotator::Type::COMPONENT_REF;
    std::string id;

    if (owningModel(component) != mPimpl->mModel) {
        return id;
    }

    id = mPimpl->makeUniqueId();
    if (!oldId.empty()) {
        auto range = mPimpl->mIdList.equal_range(oldId);
        for (auto it = range.first; it != range.second; ++it) {
            if ((it->second.first == type) && (std::any_cast<ComponentPtr>(it->second.second) == component)) {
                mPimpl->mIdList.erase(it);
                break;
            }
        }
    }
    component->setEncapsulationId(id);
    mPimpl->mIdList.insert(std::make_pair(id, std::make_pair(type, component)));
    mPimpl->updateHash();
    return id;
}

std::string Annotator::assignConnectionId(const VariablePair &variablePair)
{
    auto oldId = Variable::equivalenceConnectionId(variablePair.first, variablePair.second);
    auto type = Annotator::Type::CONNECTION;
    std::string id;

    if (owningModel(variablePair.first) != mPimpl->mModel || owningModel(variablePair.second) != mPimpl->mModel) {
        return id;
    }

    id = mPimpl->makeUniqueId();
    if (!oldId.empty()) {
        auto range = mPimpl->mIdList.equal_range(oldId);
        for (auto it = range.first; it != range.second; ++it) {
            if (it->second.first == type) {
                auto testPair = std::any_cast<VariablePair>(it->second.second);
                if ((owningComponent(testPair.first) == owningComponent(variablePair.first) || owningComponent(testPair.first) == owningComponent(variablePair.second)) && (owningComponent(testPair.second) == owningComponent(variablePair.first) || owningComponent(testPair.second) == owningComponent(variablePair.second))) {
                    mPimpl->mIdList.erase(it);
                    break;
                }
            }
        }
    }
    Variable::setEquivalenceConnectionId(variablePair.first, variablePair.second, id);
    mPimpl->mIdList.insert(std::make_pair(id, std::make_pair(type, variablePair)));
    mPimpl->updateHash();
    return id;
}

std::string Annotator::assignEncapsulationId(const ModelPtr &model)
{
    auto oldId = model->encapsulationId();
    auto type = Annotator::Type::ENCAPSULATION;
    std::string id;

    if (model != mPimpl->mModel) {
        return id;
    }

    id = mPimpl->makeUniqueId();

    if (!oldId.empty()) {
        auto range = mPimpl->mIdList.equal_range(oldId);
        for (auto it = range.first; it != range.second; ++it) {
            if ((it->second.first == type) && (std::any_cast<ModelPtr>(it->second.second) == model)) {
                mPimpl->mIdList.erase(it);
                break;
            }
        }
    }
    model->setEncapsulationId(id);
    mPimpl->mIdList.insert(std::make_pair(id, std::make_pair(type, model)));
    mPimpl->updateHash();
    return id;
}

std::string Annotator::assignImportSourceId(const ImportSourcePtr &importSource)
{
    auto oldId = importSource->id();
    auto type = Annotator::Type::IMPORT;
    std::string id;

    if (owningModel(importSource) != mPimpl->mModel) {
        return id;
    }

    id = mPimpl->makeUniqueId();

    if (!oldId.empty()) {
        auto range = mPimpl->mIdList.equal_range(oldId);
        for (auto it = range.first; it != range.second; ++it) {
            if ((it->second.first == type) && (std::any_cast<ImportSourcePtr>(it->second.second) == importSource)) {
                mPimpl->mIdList.erase(it);
                break;
            }
        }
    }
    importSource->setId(id);
    mPimpl->mIdList.insert(std::make_pair(id, std::make_pair(type, importSource)));
    mPimpl->updateHash();
    return id;
}

std::string Annotator::assignMapVariablesId(const VariablePair &variablePair)
{
    auto oldId = Variable::equivalenceMappingId(variablePair.first, variablePair.second);
    auto type = Annotator::Type::MAP_VARIABLES;
    std::string id;

    if (owningModel(variablePair.first) != mPimpl->mModel || owningModel(variablePair.second) != mPimpl->mModel) {
        return id;
    }

    id = mPimpl->makeUniqueId();

    if (!oldId.empty()) {
        auto range = mPimpl->mIdList.equal_range(oldId);
        for (auto it = range.first; it != range.second; ++it) {
            if (it->second.first == type) {
                auto testPair = std::any_cast<VariablePair>(it->second.second);
                if (((testPair.first == variablePair.first) && (testPair.second == variablePair.second)) || ((testPair.first == variablePair.second) && (testPair.second == variablePair.first))) {
                    mPimpl->mIdList.erase(it);
                    break;
                }
            }
        }
    }
    Variable::setEquivalenceMappingId(variablePair.first, variablePair.second, id);
    mPimpl->mIdList.insert(std::make_pair(id, std::make_pair(type, variablePair)));
    mPimpl->updateHash();
    return id;
}

std::string Annotator::assignModelId(const ModelPtr &model)
{
    auto oldId = model->id();
    auto type = Annotator::Type::MODEL;
    std::string id;

    if (model != mPimpl->mModel) {
        return id;
    }

    id = mPimpl->makeUniqueId();

    if (!oldId.empty()) {
        auto range = mPimpl->mIdList.equal_range(oldId);
        auto it = range.first;
        // There will only be one model, and it will always be the first in the list of items with its id.
        if ((it->second.first == type) && (std::any_cast<ModelPtr>(it->second.second) == model)) {
            mPimpl->mIdList.erase(it);
        }
    }

    model->setId(id);
    mPimpl->mIdList.insert(std::make_pair(id, std::make_pair(type, model)));
    mPimpl->updateHash();
    return id;
}

std::string Annotator::assignResetId(const ResetPtr &reset)
{
    auto oldId = reset->id();
    auto type = Annotator::Type::RESET;
    std::string id;

    if (owningModel(reset) != mPimpl->mModel) {
        return id;
    }

    id = mPimpl->makeUniqueId();

    if (!oldId.empty()) {
        auto range = mPimpl->mIdList.equal_range(oldId);
        for (auto it = range.first; it != range.second; ++it) {
            if ((it->second.first == type) && (std::any_cast<ResetPtr>(it->second.second) == reset)) {
                mPimpl->mIdList.erase(it);
                break;
            }
        }
    }
    reset->setId(id);
    mPimpl->mIdList.insert(std::make_pair(id, std::make_pair(type, reset)));
    mPimpl->updateHash();
    return id;
}

std::string Annotator::assignResetValueId(const ResetPtr &reset)
{
    auto oldId = reset->resetValueId();
    auto type = Annotator::Type::RESET_VALUE;
    std::string id;

    if (owningModel(reset) != mPimpl->mModel) {
        return id;
    }

    id = mPimpl->makeUniqueId();

    if (!oldId.empty()) {
        auto range = mPimpl->mIdList.equal_range(oldId);
        for (auto it = range.first; it != range.second; ++it) {
            if ((it->second.first == type) && (std::any_cast<ResetPtr>(it->second.second) == reset)) {
                mPimpl->mIdList.erase(it);
                break;
            }
        }
    }

    reset->setResetValueId(id);
    mPimpl->mIdList.insert(std::make_pair(id, std::make_pair(type, reset)));
    mPimpl->updateHash();
    return id;
}

std::string Annotator::assignTestValueId(const ResetPtr &reset)
{
    auto oldId = reset->testValueId();
    auto type = Annotator::Type::TEST_VALUE;
    std::string id;

    if (owningModel(reset) != mPimpl->mModel) {
        return id;
    }

    id = mPimpl->makeUniqueId();

    if (!oldId.empty()) {
        auto range = mPimpl->mIdList.equal_range(oldId);
        for (auto it = range.first; it != range.second; ++it) {
            if ((it->second.first == type) && (std::any_cast<ResetPtr>(it->second.second) == reset)) {
                mPimpl->mIdList.erase(it);
                break;
            }
        }
    }

    reset->setTestValueId(id);
    mPimpl->mIdList.insert(std::make_pair(id, std::make_pair(type, reset)));
    mPimpl->updateHash();
    return id;
}

std::string Annotator::assignUnitId(const UnitItem &unitItem)
{
    auto oldId = unitItem.first->unitId(unitItem.second);
    auto type = Annotator::Type::UNIT;
    std::string id;

    if (owningModel(unitItem.first) != mPimpl->mModel) {
        return id;
    }

    id = mPimpl->makeUniqueId();

    if (!oldId.empty()) {
        auto range = mPimpl->mIdList.equal_range(oldId);
        for (auto it = range.first; it != range.second; ++it) {
            if ((it->second.first == type) && (std::any_cast<UnitItem>(it->second.second).first == unitItem.first) && std::any_cast<UnitItem>(it->second.second).second == unitItem.second) {
                mPimpl->mIdList.erase(it);
                break;
            }
        }
    }

    unitItem.first->setUnitId(unitItem.second, id);
    mPimpl->mIdList.insert(std::make_pair(id, std::make_pair(type, unitItem)));
    mPimpl->updateHash();
    return id;
}

std::string Annotator::assignUnitsId(const UnitsPtr &units)
{
    auto oldId = units->id();
    auto type = Annotator::Type::UNITS;
    std::string id;

    if (owningModel(units) != mPimpl->mModel) {
        return id;
    }

    id = mPimpl->makeUniqueId();

    if (!oldId.empty()) {
        auto range = mPimpl->mIdList.equal_range(oldId);
        for (auto it = range.first; it != range.second; ++it) {
            if ((it->second.first == type) && (std::any_cast<UnitsPtr>(it->second.second) == units)) {
                mPimpl->mIdList.erase(it);
                break;
            }
        }
    }

    units->setId(id);
    mPimpl->mIdList.insert(std::make_pair(id, std::make_pair(type, units)));
    mPimpl->updateHash();
    return id;
}

std::string Annotator::assignVariableId(const VariablePtr &variable)
{
    auto oldId = variable->id();
    auto type = Annotator::Type::VARIABLE;
    std::string id;

    if (owningModel(variable) != mPimpl->mModel) {
        return id;
    }

    id = mPimpl->makeUniqueId();

    if (!oldId.empty()) {
        auto range = mPimpl->mIdList.equal_range(oldId);
        for (auto it = range.first; it != range.second; ++it) {
            if ((it->second.first == type) && (std::any_cast<VariablePtr>(it->second.second) == variable)) {
                mPimpl->mIdList.erase(it);
                break;
            }
        }
    }

    variable->setId(id);
    mPimpl->mIdList.insert(std::make_pair(id, std::make_pair(type, variable)));
    mPimpl->updateHash();
    return id;
}

std::string Annotator::assignId(const AnyItem &item)
{
    ComponentPtr component;
    ModelPtr model;
    ImportSourcePtr importSource;
    VariablePtr variable;
    UnitsPtr units;
    ResetPtr reset;
    VariablePair variablePair;
    UnitItem unitItem;
    std::string oldId;
    std::string id;

    switch (item.first) {
    case Annotator::Type::COMPONENT:
        component = std::any_cast<ComponentPtr>(item.second);
        id = assignComponentId(component);
        break;

    case Annotator::Type::COMPONENT_REF:
        component = std::any_cast<ComponentPtr>(item.second);
        id = assignComponentRefId(component);
        break;

    case Annotator::Type::CONNECTION:
        variablePair = std::any_cast<VariablePair>(item.second);
        id = assignConnectionId(variablePair);
        break;

    case Annotator::Type::ENCAPSULATION:
        model = std::any_cast<ModelPtr>(item.second);
        id = assignEncapsulationId(model);
        break;

    case Annotator::Type::IMPORT:
        importSource = std::any_cast<ImportSourcePtr>(item.second);
        id = assignImportSourceId(importSource);
        break;

    case Annotator::Type::MAP_VARIABLES:
        variablePair = std::any_cast<VariablePair>(item.second);
        id = assignMapVariablesId(variablePair);
        break;

    case Annotator::Type::MODEL:
        model = std::any_cast<ModelPtr>(item.second);
        id = assignModelId(model);
        break;

    case Annotator::Type::RESET:
        reset = std::any_cast<ResetPtr>(item.second);
        id = assignResetId(reset);
        break;

    case Annotator::Type::RESET_VALUE:
        reset = std::any_cast<ResetPtr>(item.second);
        id = assignResetValueId(reset);
        break;

    case Annotator::Type::TEST_VALUE:
        reset = std::any_cast<ResetPtr>(item.second);
        id = assignTestValueId(reset);
        break;

    case Annotator::Type::UNIT:
        unitItem = std::any_cast<UnitItem>(item.second);
        id = assignUnitId(unitItem);
        break;

    case Annotator::Type::UNITS:
        units = std::any_cast<UnitsPtr>(item.second);
        id = assignUnitsId(units);
        break;

    case Annotator::Type::VARIABLE:
        variable = std::any_cast<VariablePtr>(item.second);
        id = assignVariableId(variable);
        break;
    }
    return id;
}

std::string Annotator::assignId(Annotator::Type type, const ModelPtr &item)
{
    std::string id;
    if (type == Annotator::Type::MODEL) {
        id = assignModelId(item);
    } else if (type == Annotator::Type::ENCAPSULATION) {
        id = assignEncapsulationId(item);
    }
    return id;
}

std::string Annotator::assignId(Annotator::Type type, const ComponentPtr &item)
{
    std::string id;
    if (type == Annotator::Type::COMPONENT) {
        id = assignComponentId(item);
    } else if (type == Annotator::Type::COMPONENT_REF) {
        id = assignComponentRefId(item);
    }
    return id;
}

std::string Annotator::assignId(Annotator::Type type, const ResetPtr &item)
{
    std::string id;

    if (type == Annotator::Type::RESET) {
        id = assignResetId(item);
    }

    else if (type == Annotator::Type::RESET_VALUE) {
        id = assignResetValueId(item);
    }

    else if (type == Annotator::Type::TEST_VALUE) {
        id = assignTestValueId(item);
    }
    return id;
}

std::string Annotator::assignId(Annotator::Type type, const UnitsPtr &item)
{
    std::string id;
    if (type == Annotator::Type::UNITS) {
        id = assignUnitsId(item);
    }
    return id;
}

std::string Annotator::assignId(Annotator::Type type, const ImportSourcePtr &item)
{
    std::string id;
    if (type == Annotator::Type::IMPORT) {
        id = assignImportSourceId(item);
    }
    return id;
}

std::string Annotator::assignId(Annotator::Type type, const UnitsPtr &units, size_t index)
{
    std::string id;
    if (type == Annotator::Type::UNIT) {
        UnitItem item;
        item.first = units;
        item.second = index;
        id = assignUnitId(item);
    }
    return id;
}

std::string Annotator::assignId(Annotator::Type type, const UnitItem &item)
{
    std::string id;
    if (type == Annotator::Type::UNIT) {
        id = assignUnitId(item);
    }
    return id;
}

std::string Annotator::assignId(Annotator::Type type, const VariablePtr &item)
{
    std::string id;
    if (type == Annotator::Type::VARIABLE) {
        id = assignVariableId(item);
    }
    return id;
}

std::string Annotator::assignId(Annotator::Type type, const VariablePair &pair)
{
    std::string id;
    if (type == Annotator::Type::MAP_VARIABLES) {
        id = assignMapVariablesId(pair);
    } else if (type == Annotator::Type::CONNECTION) {
        id = assignConnectionId(pair);
    }
    return id;
}

std::string Annotator::assignId(Annotator::Type type, const VariablePtr &item1, const VariablePtr &item2)
{
    // Overloaded so that bindings work better.
    std::string id;
    VariablePair item;
    if (type == Annotator::Type::MAP_VARIABLES) {
        item.first = item1;
        item.second = item2;
        id = assignMapVariablesId(item);
    } else if (type == Annotator::Type::CONNECTION) {
        item.first = item1;
        item.second = item2;
        id = assignConnectionId(item);
    }
    return id;
}

static const std::map<Annotator::Type, std::string> typeToString = {
    {Annotator::Type::COMPONENT, "component"},
    {Annotator::Type::COMPONENT_REF, "component_ref"},
    {Annotator::Type::CONNECTION, "connection"},
    {Annotator::Type::ENCAPSULATION, "encapsulation"},
    {Annotator::Type::IMPORT, "import"},
    {Annotator::Type::MAP_VARIABLES, "map_variables"},
    {Annotator::Type::MODEL, "model"},
    {Annotator::Type::RESET, "reset"},
    {Annotator::Type::RESET_VALUE, "reset_value"},
    {Annotator::Type::TEST_VALUE, "test_value"},
    {Annotator::Type::UNIT, "unit"},
    {Annotator::Type::UNITS, "units"},
    {Annotator::Type::VARIABLE, "variable"},
    {Annotator::Type::ISSUE, "issue"}};

std::string Annotator::typeString(const Annotator::Type &type)
{
    return typeToString.at(type);
}

std::string Annotator::typeString(const std::uint64_t &type)
{
    return typeToString.at(static_cast<Annotator::Type>(type));
}

size_t Annotator::duplicateCount(const std::string &id)
{
    return mPimpl->mIdList.count(id);
}

void Annotator::AnnotatorImpl::doUpdateComponentHash(ComponentPtr &component, std::string &idsString)
{
    for (size_t i = 0; i < component->variableCount(); ++i) {
        idsString += "v" + std::to_string(i) + component->variable(i)->id();
    }

    for (size_t i = 0; i < component->resetCount(); ++i) {
        auto reset = component->reset(i);
        idsString += "r" + std::to_string(i) + reset->id() + reset->resetValueId() + reset->testValueId();
    }

    // Note that MathML ids are not yet included.

    for (size_t i = 0; i < component->componentCount(); ++i) {
        auto child = component->component(i);
        idsString += "c" + std::to_string(i) + child->id() + child->encapsulationId();
        doUpdateComponentHash(child, idsString);
    }
}

size_t Annotator::AnnotatorImpl::getHash()
{
    // Serialise the stored model into a (very) simplified string of id-ed items, and create a hash.
    std::string idsString;
    idsString += "m" + mModel->id() + mModel->encapsulationId();

    for (size_t u = 0; u < mModel->importSourceCount(); ++u) {
        auto import = mModel->importSource(u);
        idsString += "i" + std::to_string(u) + import->id();
    }

    for (size_t u = 0; u < mModel->unitsCount(); ++u) {
        auto units = mModel->units(u);
        idsString += "U" + std::to_string(u) + units->id();
        for (size_t i = 0; i < units->unitCount(); ++i) {
            idsString += "u" + std::to_string(i) + units->unitId(i);
        }
    }

    for (size_t u = 0; u < mModel->componentCount(); ++u) {
        auto component = mModel->component(u);
        idsString += "c" + std::to_string(u) + component->id();
        idsString += "cr" + std::to_string(u) + component->encapsulationId();
        doUpdateComponentHash(component, idsString);
    }

    std::hash<std::string> hasher;
    return hasher(idsString);
}

bool Annotator::isBuilt()
{
    if (mPimpl->mModel == nullptr) {
        return false;
    }
    // If we already know it's out of date, return false.
    if (!mPimpl->mIsBuilt) {
        return false;
    }
    // If we don't know, then test the hash.
    mPimpl->mIsBuilt = mPimpl->mHash == mPimpl->getHash();
    return mPimpl->mIsBuilt;
}

void Annotator::AnnotatorImpl::updateHash()
{
    // If the build is already out of date, do nothing.
    if (!mIsBuilt) {
        return;
    }
    // If the build was fine before, the model and the idList are in sync,
    // we just need to update the stored hash.
    mHash = getHash();
}

} // namespace libcellml

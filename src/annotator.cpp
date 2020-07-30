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
    bool isBuilt = false;
    ModelPtr mModel = nullptr;
    size_t mCounter = 0xb4da55;

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
};

Annotator::Annotator()
    : mPimpl(new AnnotatorImpl())
{
    mPimpl->mAnnotator = this;
    mPimpl->mIdList = std::multimap<std::string, AnyItem>();
    mPimpl->isBuilt = false;
    mPimpl->mCounter = 0xb4da55;
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
    mPimpl->isBuilt = false;
    removeAllIssues();
    mPimpl->mIdList.clear();
    mPimpl->mIdList = listIdsAndItems(model);

    for (auto it = mPimpl->mIdList.begin(), end = mPimpl->mIdList.end(); it != end; it = mPimpl->mIdList.upper_bound(it->first)) {
        auto id = it->first;
        if (mPimpl->mIdList.count(id) > 1) {
            auto issue = libcellml::Issue::create();
            issue->setDescription("The id '" + id + "' occurs " + std::to_string(mPimpl->mIdList.count(id)) + " times in the model.");
            issue->setLevel(Issue::Level::WARNING);
            addIssue(issue);
        }
    }

    mPimpl->isBuilt = true;
    mPimpl->mModel = model;
}

AnyItem Annotator::item(const std::string &id)
{
    AnyItem item;
    if (!mPimpl->isBuilt) {
        auto issue = libcellml::Issue::create();
        issue->setDescription("Please call the Annotator::build function before attempting to access items by their id.");
        issue->setLevel(libcellml::Issue::Level::ERROR);
        addIssue(issue);
        item = std::make_pair(Annotator::Type::ISSUE, issue);
        return item;
    }
    if (mPimpl->mIdList.empty()) {
        // Setting the error message to be the same as below.
        auto issue = libcellml::Issue::create();
        issue->setDescription("Could not find an item with an id of '" + id + "' in the model.");
        issue->setLevel(libcellml::Issue::Level::WARNING);
        addIssue(issue);
        item = std::make_pair(Annotator::Type::ISSUE, issue);
        return item;
    }

    // Check whether the id has been duplicated in the model.
    if (mPimpl->mIdList.count(id) > 1) {
        auto issue = libcellml::Issue::create();
        issue->setDescription("The id '" + id + "' occurs " + std::to_string(mPimpl->mIdList.count(id)) + " times in the model so a unique item cannot be located.");
        issue->setLevel(libcellml::Issue::Level::WARNING);
        addIssue(issue);
        item = std::make_pair(Annotator::Type::ISSUE, issue);
        return item;
    }

    // Retrieve the item from the idList.
    ItemList::iterator it;
    it = mPimpl->mIdList.find(id);

    if (it == mPimpl->mIdList.end()) {
        auto issue = libcellml::Issue::create();
        issue->setDescription("Could not find an item with an id of '" + id + "' in the model.");
        issue->setLevel(libcellml::Issue::Level::WARNING);
        addIssue(issue);
        item = std::make_pair(Annotator::Type::ISSUE, issue);
        // Adding the requested id string and this issue to the map, so that future requests (ie: to the .second)
        // will return the same IssuePtr rather than creating a new one.
        mPimpl->mIdList.insert(std::make_pair(id, item));
        return item;
    }
    return it->second;
}

ComponentPtr Annotator::component(const std::string &id)
{
    auto i = item(id);
    try {
        return std::any_cast<ComponentPtr>(i.second);
    } catch (std::bad_any_cast &e) {
        (void)e;
        return nullptr;
    }
}

VariablePtr Annotator::variable(const std::string &id)
{
    auto i = item(id);
    try {
        return std::any_cast<VariablePtr>(i.second);
    } catch (std::bad_any_cast &e) {
        (void)e;
        return nullptr;
    }
}

ModelPtr Annotator::model(const std::string &id)
{
    auto i = item(id);
    try {
        return std::any_cast<ModelPtr>(i.second);
    } catch (std::bad_any_cast &e) {
        (void)e;
        return nullptr;
    }
}

UnitsPtr Annotator::units(const std::string &id)
{
    auto i = item(id);
    try {
        return std::any_cast<UnitsPtr>(i.second);
    } catch (std::bad_any_cast &e) {
        (void)e;
        return nullptr;
    }
}

ImportSourcePtr Annotator::importSource(const std::string &id)
{
    auto i = item(id);
    try {
        return std::any_cast<ImportSourcePtr>(i.second);
    } catch (std::bad_any_cast &e) {
        (void)e;
        return nullptr;
    }
}

ResetPtr Annotator::reset(const std::string &id)
{
    auto i = item(id);
    try {
        return std::any_cast<ResetPtr>(i.second);
    } catch (std::bad_any_cast &e) {
        (void)e;
        return nullptr;
    }
}

VariablePair Annotator::connection(const std::string &id)
{
    auto i = item(id);
    try {
        return std::any_cast<VariablePair>(i.second);
    } catch (std::bad_any_cast &e) {
        (void)e;
        return std::make_pair(nullptr, nullptr);
    }
}

VariablePair Annotator::mapVariables(const std::string &id)
{
    auto i = item(id);
    try {
        return std::any_cast<VariablePair>(i.second);
    } catch (std::bad_any_cast &e) {
        (void)e;
        return std::make_pair(nullptr, nullptr);
    }
}

UnitItem Annotator::unit(const std::string &id)
{
    auto i = item(id);
    try {
        return std::any_cast<UnitItem>(i.second);
    } catch (std::bad_any_cast &e) {
        (void)e;
        return std::make_pair(nullptr, -1);
    }
}

ComponentPtr Annotator::componentRef(const std::string &id)
{
    auto i = item(id);
    try {
        return std::any_cast<ComponentPtr>(i.second);
    } catch (std::bad_any_cast &e) {
        (void)e;
        return nullptr;
    }
}

ResetPtr Annotator::testValue(const std::string &id)
{
    auto i = item(id);
    try {
        return std::any_cast<ResetPtr>(i.second);
    } catch (std::bad_any_cast &e) {
        (void)e;
        return nullptr;
    }
}

ResetPtr Annotator::resetValue(const std::string &id)
{
    auto i = item(id);
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
    mPimpl->isBuilt = true;  
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

bool Annotator::assignComponentId(const ComponentPtr &component)
{
    auto oldId = component->id();
    auto type = Annotator::Type::COMPONENT;

    if (owningModel(component) != mPimpl->mModel) {
        return false;
    }

    if (oldId.empty()) {
        auto id = mPimpl->makeUniqueId();
        component->setId(id);
        mPimpl->mIdList.insert(std::make_pair(id, std::make_pair(type, component)));
        return true;
    }

    // if (mPimpl->mIdList.count(oldId) > 1) {
    auto range = mPimpl->mIdList.equal_range(oldId);
    for (auto it = range.first; it != range.second; ++it) {
        if ((it->second.first == type) && (std::any_cast<ComponentPtr>(it->second.second) == component)) {
            auto id = mPimpl->makeUniqueId();
            mPimpl->mIdList.erase(it);
            component->setId(id);
            mPimpl->mIdList.insert(std::make_pair(id, std::make_pair(type, component)));
            return true;
        }
    }
    // }
    return false;
}

bool Annotator::assignComponentRefId(const ComponentPtr &component)
{
    auto oldId = component->encapsulationId();
    auto type = Annotator::Type::COMPONENT_REF;

    if (owningModel(component) != mPimpl->mModel) {
        return false;
    }

    if (oldId.empty()) {
        auto id = mPimpl->makeUniqueId();
        component->setEncapsulationId(id);
        mPimpl->mIdList.insert(std::make_pair(id, std::make_pair(type, component)));
        return true;
    }

    // if (!oldId.empty() && mPimpl->mIdList.count(oldId) > 1) {
    auto range = mPimpl->mIdList.equal_range(oldId);
    for (auto it = range.first; it != range.second; ++it) {
        if ((it->second.first == type) && (std::any_cast<ComponentPtr>(it->second.second) == component)) {
            auto id = mPimpl->makeUniqueId();
            mPimpl->mIdList.erase(it);
            component->setEncapsulationId(id);
            mPimpl->mIdList.insert(std::make_pair(id, std::make_pair(type, component)));
            return true;
        }
    }
    // }
    return false;
}

bool Annotator::assignConnectionId(const VariablePair &variablePair)
{
    auto oldId = Variable::equivalenceConnectionId(variablePair.first, variablePair.second);
    auto type = Annotator::Type::CONNECTION;

    if (owningModel(variablePair.first) != mPimpl->mModel || owningModel(variablePair.second) != mPimpl->mModel) {
        return false;
    }

    if (oldId.empty()) {
        auto id = mPimpl->makeUniqueId();
        Variable::setEquivalenceConnectionId(variablePair.first, variablePair.second, id);
        mPimpl->mIdList.insert(std::make_pair(id, std::make_pair(type, variablePair)));
        return true;
    }

    // if (!oldId.empty() && mPimpl->mIdList.count(oldId) > 1) {
    auto range = mPimpl->mIdList.equal_range(oldId);
    for (auto it = range.first; it != range.second; ++it) {
        if (it->second.first == type) {
            auto testPair = std::any_cast<VariablePair>(it->second.second);
            if ((owningComponent(testPair.first) == owningComponent(variablePair.first) || owningComponent(testPair.first) == owningComponent(variablePair.second)) && (owningComponent(testPair.second) == owningComponent(variablePair.first) || owningComponent(testPair.second) == owningComponent(variablePair.second))) {
                auto id = mPimpl->makeUniqueId();
                mPimpl->mIdList.erase(it);
                Variable::setEquivalenceConnectionId(variablePair.first, variablePair.second, id);
                mPimpl->mIdList.insert(std::make_pair(id, std::make_pair(type, variablePair)));
                return true;
            }
        }
    }
    // }
    return false;
}

bool Annotator::assignEncapsulationId(const ModelPtr &model)
{
    auto oldId = model->encapsulationId();
    auto type = Annotator::Type::ENCAPSULATION;

    if (model != mPimpl->mModel) {
        return false;
    }

    if (oldId.empty()) {
        auto id = mPimpl->makeUniqueId();
        model->setEncapsulationId(id);
        mPimpl->mIdList.insert(std::make_pair(id, std::make_pair(type, model)));
        return true;
    }

    // if (!oldId.empty() && mPimpl->mIdList.count(oldId) > 1) {
    auto range = mPimpl->mIdList.equal_range(oldId);
    for (auto it = range.first; it != range.second; ++it) {
        if ((it->second.first == type) && (std::any_cast<ModelPtr>(it->second.second) == model)) {
            auto id = mPimpl->makeUniqueId();
            mPimpl->mIdList.erase(it);
            model->setEncapsulationId(id);
            mPimpl->mIdList.insert(std::make_pair(id, std::make_pair(type, model)));
            return true;
        }
    }
    // }
    return false;
}

bool Annotator::assignImportSourceId(const ImportSourcePtr &importSource)
{
    auto oldId = importSource->id();
    auto type = Annotator::Type::IMPORT;

    if (owningModel(importSource) != mPimpl->mModel) {
        return false;
    }

    if (oldId.empty()) {
        auto id = mPimpl->makeUniqueId();
        importSource->setId(id);
        mPimpl->mIdList.insert(std::make_pair(id, std::make_pair(type, importSource)));
        return true;
    }

    // if (!oldId.empty() && mPimpl->mIdList.count(oldId) > 1) {
    auto range = mPimpl->mIdList.equal_range(oldId);
    for (auto it = range.first; it != range.second; ++it) {
        if ((it->second.first == type) && (std::any_cast<ImportSourcePtr>(it->second.second) == importSource)) {
            auto id = mPimpl->makeUniqueId();
            mPimpl->mIdList.erase(it);
            importSource->setId(id);
            mPimpl->mIdList.insert(std::make_pair(id, std::make_pair(type, importSource)));
            return true;
        }
    }
    // }
    return false;
}

bool Annotator::assignMapVariablesId(const VariablePair &variablePair)
{
    auto oldId = Variable::equivalenceMappingId(variablePair.first, variablePair.second);
    auto type = Annotator::Type::MAP_VARIABLES;

    if (owningModel(variablePair.first) != mPimpl->mModel || owningModel(variablePair.second) != mPimpl->mModel) {
        return false;
    }

    if (oldId.empty()) {
        auto id = mPimpl->makeUniqueId();
        Variable::setEquivalenceMappingId(variablePair.first, variablePair.second, id);
        mPimpl->mIdList.insert(std::make_pair(id, std::make_pair(type, variablePair)));
        return true;
    }

    // if (!oldId.empty() && mPimpl->mIdList.count(oldId) > 1) {
    auto range = mPimpl->mIdList.equal_range(oldId);
    for (auto it = range.first; it != range.second; ++it) {
        if (it->second.first == type) {
            auto testPair = std::any_cast<VariablePair>(it->second.second);
            if (((testPair.first == variablePair.first) && (testPair.second == variablePair.second)) || ((testPair.first == variablePair.second) && (testPair.second == variablePair.first))) {
                auto id = mPimpl->makeUniqueId();
                mPimpl->mIdList.erase(it);
                Variable::setEquivalenceMappingId(variablePair.first, variablePair.second, id);
                mPimpl->mIdList.insert(std::make_pair(id, std::make_pair(type, variablePair)));
                return true;
            }
        }
    }
    // }
    return false;
}

bool Annotator::assignModelId(const ModelPtr &model)
{
    auto oldId = model->id();
    auto type = Annotator::Type::MODEL;

    if (model != mPimpl->mModel) {
        return false;
    }

    if (oldId.empty()) {
        auto id = mPimpl->makeUniqueId();
        model->setId(id);
        mPimpl->mIdList.insert(std::make_pair(id, std::make_pair(type, model)));
        return true;
    }

    // if (!oldId.empty() && mPimpl->mIdList.count(oldId) > 1) {
    auto range = mPimpl->mIdList.equal_range(oldId);
    for (auto it = range.first; it != range.second; ++it) {
        if ((it->second.first == type) && (std::any_cast<ModelPtr>(it->second.second) == model)) {
            auto id = mPimpl->makeUniqueId();
            mPimpl->mIdList.erase(it);
            model->setId(id);
            mPimpl->mIdList.insert(std::make_pair(id, std::make_pair(type, model)));
            return true;
        }
    }
    // }
    return false;
}

bool Annotator::assignResetId(const ResetPtr &reset)
{
    auto oldId = reset->id();
    auto type = Annotator::Type::RESET;

    if (owningModel(reset) != mPimpl->mModel) {
        return false;
    }

    if (oldId.empty()) {
        auto id = mPimpl->makeUniqueId();
        reset->setId(id);
        mPimpl->mIdList.insert(std::make_pair(id, std::make_pair(type, reset)));
        return true;
    }

    // if (!oldId.empty() && mPimpl->mIdList.count(oldId) > 1) {
    auto range = mPimpl->mIdList.equal_range(oldId);
    for (auto it = range.first; it != range.second; ++it) {
        if ((it->second.first == type) && (std::any_cast<ResetPtr>(it->second.second) == reset)) {
            auto id = mPimpl->makeUniqueId();
            mPimpl->mIdList.erase(it);
            reset->setId(id);
            mPimpl->mIdList.insert(std::make_pair(id, std::make_pair(type, reset)));
            return true;
        }
    }
    // }
    return false;
}

bool Annotator::assignResetValueId(const ResetPtr &reset)
{
    auto oldId = reset->resetValueId();
    auto type = Annotator::Type::RESET_VALUE;

    if (owningModel(reset) != mPimpl->mModel) {
        return false;
    }

    if (oldId.empty()) {
        auto id = mPimpl->makeUniqueId();
        reset->setResetValueId(id);
        mPimpl->mIdList.insert(std::make_pair(id, std::make_pair(type, reset)));
        return true;
    }

    // if (!oldId.empty() && mPimpl->mIdList.count(oldId) > 1) {
    auto range = mPimpl->mIdList.equal_range(oldId);
    for (auto it = range.first; it != range.second; ++it) {
        if ((it->second.first == type) && (std::any_cast<ResetPtr>(it->second.second) == reset)) {
            auto id = mPimpl->makeUniqueId();
            mPimpl->mIdList.erase(it);
            reset->setResetValueId(id);
            mPimpl->mIdList.insert(std::make_pair(id, std::make_pair(type, reset)));
            return true;
        }
    }
    // }
    return false;
}

bool Annotator::assignTestValueId(const ResetPtr &reset)
{
    auto oldId = reset->testValueId();
    auto type = Annotator::Type::TEST_VALUE;

    if (owningModel(reset) != mPimpl->mModel) {
        return false;
    }

    if (oldId.empty()) {
        auto id = mPimpl->makeUniqueId();
        reset->setTestValueId(id);
        mPimpl->mIdList.insert(std::make_pair(id, std::make_pair(type, reset)));
        return true;
    }

    // if (!oldId.empty() && mPimpl->mIdList.count(oldId) > 1) {
    auto range = mPimpl->mIdList.equal_range(oldId);
    for (auto it = range.first; it != range.second; ++it) {
        if ((it->second.first == type) && (std::any_cast<ResetPtr>(it->second.second) == reset)) {
            auto id = mPimpl->makeUniqueId();
            mPimpl->mIdList.erase(it);
            reset->setTestValueId(id);
            mPimpl->mIdList.insert(std::make_pair(id, std::make_pair(type, reset)));
            return true;
        }
    }
    // }
    return false;
}

bool Annotator::assignUnitId(const UnitItem &unitItem)
{
    auto oldId = unitItem.first->unitId(unitItem.second);
    auto type = Annotator::Type::UNIT;

    if (owningModel(unitItem.first) != mPimpl->mModel) {
        return false;
    }

    if (oldId.empty()) {
        auto id = mPimpl->makeUniqueId();
        unitItem.first->setUnitId(unitItem.second, id);
        mPimpl->mIdList.insert(std::make_pair(id, std::make_pair(type, unitItem)));
        return true;
    }

    // if (!oldId.empty() && mPimpl->mIdList.count(oldId) > 1) {
    auto range = mPimpl->mIdList.equal_range(oldId);
    for (auto it = range.first; it != range.second; ++it) {
        if ((it->second.first == type) && (std::any_cast<UnitItem>(it->second.second).first == unitItem.first) && std::any_cast<UnitItem>(it->second.second).second == unitItem.second) {
            auto id = mPimpl->makeUniqueId();
            mPimpl->mIdList.erase(it);
            unitItem.first->setUnitId(unitItem.second, id);
            mPimpl->mIdList.insert(std::make_pair(id, std::make_pair(type, unitItem)));
            return true;
        }
    }
    // }
    return false;
}

bool Annotator::assignUnitsId(const UnitsPtr &units)
{
    auto oldId = units->id();
    auto type = Annotator::Type::UNITS;

    if (owningModel(units) != mPimpl->mModel) {
        return false;
    }

    if (oldId.empty()) {
        auto id = mPimpl->makeUniqueId();
        units->setId(id);
        mPimpl->mIdList.insert(std::make_pair(id, std::make_pair(type, units)));
        return true;
    }

    // if (!oldId.empty() && mPimpl->mIdList.count(oldId) > 1) {
    auto range = mPimpl->mIdList.equal_range(oldId);
    for (auto it = range.first; it != range.second; ++it) {
        if ((it->second.first == type) && (std::any_cast<UnitsPtr>(it->second.second) == units)) {
            auto id = mPimpl->makeUniqueId();
            mPimpl->mIdList.erase(it);
            units->setId(id);
            mPimpl->mIdList.insert(std::make_pair(id, std::make_pair(type, units)));
            return true;
        }
    }
    // }
    return false;
}

bool Annotator::assignVariableId(const VariablePtr &variable)
{
    auto oldId = variable->id();
    auto type = Annotator::Type::VARIABLE;

    if (owningModel(variable) != mPimpl->mModel) {
        return false;
    }

    if (oldId.empty()) {
        auto id = mPimpl->makeUniqueId();
        variable->setId(id);
        mPimpl->mIdList.insert(std::make_pair(id, std::make_pair(type, variable)));
        return true;
    }

    // if (!oldId.empty() && mPimpl->mIdList.count(oldId) > 1) {
    auto range = mPimpl->mIdList.equal_range(oldId);
    for (auto it = range.first; it != range.second; ++it) {
        if ((it->second.first == type) && (std::any_cast<VariablePtr>(it->second.second) == variable)) {
            auto id = mPimpl->makeUniqueId();
            mPimpl->mIdList.erase(it);
            variable->setId(id);
            mPimpl->mIdList.insert(std::make_pair(id, std::make_pair(type, variable)));
            return true;
        }
    }
    // }
    return false;
}

bool Annotator::assignId(const AnyItem &item)
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
        return assignComponentId(component);

    case Annotator::Type::COMPONENT_REF:
        component = std::any_cast<ComponentPtr>(item.second);
        return assignComponentRefId(component);

    case Annotator::Type::CONNECTION:
        variablePair = std::any_cast<VariablePair>(item.second);
        return assignConnectionId(variablePair);

    case Annotator::Type::ENCAPSULATION:
        model = std::any_cast<ModelPtr>(item.second);
        return assignEncapsulationId(model);

    case Annotator::Type::IMPORT:
        importSource = std::any_cast<ImportSourcePtr>(item.second);
        return assignImportSourceId(importSource);

    case Annotator::Type::MAP_VARIABLES:
        variablePair = std::any_cast<VariablePair>(item.second);
        return assignMapVariablesId(variablePair);

    case Annotator::Type::MODEL:
        model = std::any_cast<ModelPtr>(item.second);
        return assignModelId(model);

    case Annotator::Type::RESET:
        reset = std::any_cast<ResetPtr>(item.second);
        return assignResetId(reset);

    case Annotator::Type::RESET_VALUE:
        reset = std::any_cast<ResetPtr>(item.second);
        return assignResetValueId(reset);

    case Annotator::Type::TEST_VALUE:
        reset = std::any_cast<ResetPtr>(item.second);
        return assignTestValueId(reset);

    case Annotator::Type::UNIT:
        unitItem = std::any_cast<UnitItem>(item.second);
        return assignUnitId(unitItem);

    case Annotator::Type::UNITS:
        units = std::any_cast<UnitsPtr>(item.second);
        return assignUnitsId(units);

    case Annotator::Type::VARIABLE:
        variable = std::any_cast<VariablePtr>(item.second);
        return assignVariableId(variable);
    }
    return false;
}

bool Annotator::assignId(Annotator::Type type, const ModelPtr &item)
{
    if (type == Annotator::Type::MODEL) {
        return assignModelId(item);
    }
    if (type == Annotator::Type::ENCAPSULATION) {
        return assignEncapsulationId(item);
    }
    return false;
}

bool Annotator::assignId(Annotator::Type type, const ComponentPtr &item)
{
    if (type == Annotator::Type::COMPONENT) {
        return assignComponentId(item);
    }
    if (type == Annotator::Type::COMPONENT_REF) {
        return assignComponentRefId(item);
    }
    return false;
}

bool Annotator::assignId(Annotator::Type type, const ResetPtr &item)
{
    if (type == Annotator::Type::RESET) {
        return assignResetId(item);
    }

    if (type == Annotator::Type::RESET_VALUE) {
        return assignResetValueId(item);
    }

    if (type == Annotator::Type::TEST_VALUE) {
        return assignTestValueId(item);
    }
    return false;
}

bool Annotator::assignId(Annotator::Type type, const UnitsPtr &item)
{
    if (type == Annotator::Type::UNITS) {
        return assignUnitsId(item);
    }
    return false;
}

bool Annotator::assignId(Annotator::Type type, const ImportSourcePtr &item)
{
    if (type == Annotator::Type::IMPORT) {
        return assignImportSourceId(item);
    }
    return false;
}

bool Annotator::assignId(Annotator::Type type, const UnitsPtr &units, size_t index)
{
    // Overloaded so that bindings work better.
    if (type == Annotator::Type::UNIT) {
        UnitItem item;
        item.first = units;
        item.second = index;
        return assignUnitId(item);
    }
    return false;
}

bool Annotator::assignId(Annotator::Type type, const UnitItem &item)
{
    if (type == Annotator::Type::UNIT) {
        return assignUnitId(item);
    }
    return false;
}

bool Annotator::assignId(Annotator::Type type, const VariablePtr &item)
{
    if (type == Annotator::Type::VARIABLE) {
        return assignVariableId(item);
    }
    return false;
}

bool Annotator::assignId(Annotator::Type type, const VariablePair &item)
{
    if (type == Annotator::Type::MAP_VARIABLES) {
        return assignMapVariablesId(item);
    }
    if (type == Annotator::Type::CONNECTION) {
        return assignConnectionId(item);
    }
    return false;
}

bool Annotator::assignId(Annotator::Type type, const VariablePtr &item1, const VariablePtr &item2)
{
    // Overloaded so that bindings work better.
    VariablePair item;
    if (type == Annotator::Type::MAP_VARIABLES) {
        item.first = item1;
        item.second = item2;
        return assignMapVariablesId(item);
    }
    if (type == Annotator::Type::CONNECTION) {
        item.first = item1;
        item.second = item2;
        return assignConnectionId(item);
    }
    return false;
}

} // namespace libcellml

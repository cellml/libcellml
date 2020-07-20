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
};

Annotator::Annotator()
    : mPimpl(new AnnotatorImpl())
{
    mPimpl->mAnnotator = this;
    mPimpl->mIdList = std::map<std::string, AnyItem>();
    mPimpl->isBuilt = false;
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
                idList.insert(std::make_pair(id, std::make_pair(Annotator::Type::MAP_VARIABLES, std::make_pair(component->variable(v), component->variable(v)->equivalentVariable(e)))));
            }
            // Connections.
            id = Variable::equivalenceConnectionId(component->variable(v), component->variable(v)->equivalentVariable(e));
            if (!id.empty()) {
                idList.insert(std::make_pair(id, std::make_pair(Annotator::Type::CONNECTION, std::make_pair(component->variable(v), component->variable(v)->equivalentVariable(e)))));
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
        idList.insert(std::make_pair(id, std::make_pair(Annotator::Type::ENCAPSULATION, std::string())));
    }

    return idList;
}

void Annotator::build(const ModelPtr &model)
{
    mPimpl->isBuilt = false;
    removeAllIssues();
    mPimpl->mIdList.clear();
    mPimpl->mIdList = listIdsAndItems(model);
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
        issue->setDescription("Could not find an item with id='" + id + "' in the model.");
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
        issue->setDescription("Could not find an item with id='" + id + "' in the model.");
        issue->setLevel(libcellml::Issue::Level::WARNING);
        addIssue(issue);
        item = std::make_pair(Annotator::Type::ISSUE, issue);
        // Adding the requested id string and this issue to the map, so that future requests (ie: to the .second)
        // will return the same IssuePtr rather than creating a new one.
        mPimpl->mIdList.insert(std::make_pair(id, item));
        return item;
    }
    return mPimpl->mIdList[id];
}

ComponentPtr Annotator::component(const std::string &id)
{
    auto i = item(id);
    try {
        auto j = std::any_cast<ComponentPtr>(i.second);
        return j;
    } catch (std::bad_any_cast &e) {
        (void)e;
        return nullptr;
    }
}

VariablePtr Annotator::variable(const std::string &id)
{
    auto i = item(id);
    try {
        auto j = std::any_cast<VariablePtr>(i.second);
        return j;
    } catch (std::bad_any_cast &e) {
        (void)e;
        return nullptr;
    }
}

ModelPtr Annotator::model(const std::string &id)
{
    auto i = item(id);
    try {
        auto j = std::any_cast<ModelPtr>(i.second);
        return j;
    } catch (std::bad_any_cast &e) {
        (void)e;
        return nullptr;
    }
}

UnitsPtr Annotator::units(const std::string &id)
{
    auto i = item(id);
    try {
        auto j = std::any_cast<UnitsPtr>(i.second);
        return j;
    } catch (std::bad_any_cast &e) {
        (void)e;
        return nullptr;
    }
}

ImportSourcePtr Annotator::importSource(const std::string &id)
{
    auto i = item(id);
    try {
        auto j = std::any_cast<ImportSourcePtr>(i.second);
        return j;
    } catch (std::bad_any_cast &e) {
        (void)e;
        return nullptr;
    }
}

ResetPtr Annotator::reset(const std::string &id)
{
    auto i = item(id);
    try {
        auto j = std::any_cast<ResetPtr>(i.second);
        return j;
    } catch (std::bad_any_cast &e) {
        (void)e;
        return nullptr;
    }
}

VariablePair Annotator::connection(const std::string &id)
{
    auto i = item(id);
    try {
        auto j = std::any_cast<VariablePair>(i.second);
        return j;
    } catch (std::bad_any_cast &e) {
        (void)e;
        return std::make_pair(nullptr, nullptr);
    }
}

VariablePair Annotator::mapVariables(const std::string &id)
{
    auto i = item(id);
    try {
        auto j = std::any_cast<VariablePair>(i.second);
        return j;
    } catch (std::bad_any_cast &e) {
        (void)e;
        return std::make_pair(nullptr, nullptr);
    }
}

UnitItem Annotator::unit(const std::string &id)
{
    auto i = item(id);
    try {
        auto j = std::any_cast<UnitItem>(i.second);
        return j;
    } catch (std::bad_any_cast &e) {
        (void)e;
        return std::make_pair(nullptr, -1);
    }
}

ComponentPtr Annotator::componentRef(const std::string &id)
{
    auto i = item(id);
    try {
        auto j = std::any_cast<ComponentPtr>(i.second);
        return j;
    } catch (std::bad_any_cast &e) {
        (void)e;
        return nullptr;
    }
}

ResetPtr Annotator::testValue(const std::string &id)
{
    auto i = item(id);
    try {
        auto j = std::any_cast<ResetPtr>(i.second);
        return j;
    } catch (std::bad_any_cast &e) {
        (void)e;
        return nullptr;
    }
}

ResetPtr Annotator::resetValue(const std::string &id)
{
    auto i = item(id);
    try {
        auto j = std::any_cast<ResetPtr>(i.second);
        return j;
    } catch (std::bad_any_cast &e) {
        (void)e;
        return nullptr;
    }
}

} // namespace libcellml

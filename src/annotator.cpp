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

    std::string makeUniqueId();
    void doSetAllAutomaticIds();
    void doSetModelId();
    void doSetImportSourceIds();
    void doSetUnitsIds();
    void doSetUnitIds();
    void doSetComponentIds(const ComponentPtr &parent);
    void doSetVariableIds(const ComponentPtr &parent);
    void doSetResetIds(const ComponentPtr &parent);
    void doSetResetValueIds(const ComponentPtr &parent);
    void doSetTestValueIds(const ComponentPtr &parent);
    void doSetEncapsulationId();
    void doSetConnectionIds(const ComponentPtr &parent);
    void doSetMapVariablesIds(const ComponentPtr &parent);
    void doSetComponentRefIds(const ComponentPtr &parent);
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

bool Annotator::setAutomaticIds()
{
    // Add automatically generated id strings to every item (excepting MathML) in the model which
    // can be annotated.
    if (!mPimpl->isBuilt || mPimpl->mModel == nullptr) {
        auto i = Issue::create();
        i->setDescription("Please call the Annotator::build function before attempting to automatically create id strings.");
        i->setLevel(Issue::Level::ERROR);
        addIssue(i);
        return false;
    }
    mPimpl->doSetAllAutomaticIds();
    return true;
}

bool Annotator::setAutomaticIds(Annotator::Type type)
{
    switch (type) {
    case Annotator::Type::COMPONENT:
        for (size_t c = 0; c < mPimpl->mModel->componentCount(); ++c) {
            mPimpl->doSetComponentIds(mPimpl->mModel->component(c));
        }
        return true;
    case Annotator::Type::COMPONENT_REF:
        for (size_t c = 0; c < mPimpl->mModel->componentCount(); ++c) {
            mPimpl->doSetComponentRefIds(mPimpl->mModel->component(c));
        }
        return true;
    case Annotator::Type::CONNECTION:
        for (size_t c = 0; c < mPimpl->mModel->componentCount(); ++c) {
            mPimpl->doSetConnectionIds(mPimpl->mModel->component(c));
        }
        return true;
    case Annotator::Type::ENCAPSULATION:
        mPimpl->doSetEncapsulationId();
        return true;
    case Annotator::Type::IMPORT:
        mPimpl->doSetImportSourceIds();
        return true;
    case Annotator::Type::ISSUE:
        break;
    case Annotator::Type::MAP_VARIABLES:
        for (size_t c = 0; c < mPimpl->mModel->componentCount(); ++c) {
            mPimpl->doSetMapVariablesIds(mPimpl->mModel->component(c));
        }
        return true;
    case Annotator::Type::MODEL:
        mPimpl->doSetModelId();
        return true;
    case Annotator::Type::RESET:
        for (size_t c = 0; c < mPimpl->mModel->componentCount(); ++c) {
            mPimpl->doSetResetIds(mPimpl->mModel->component(c));
        }
        return true;
    case Annotator::Type::RESET_VALUE:
        for (size_t c = 0; c < mPimpl->mModel->componentCount(); ++c) {
            mPimpl->doSetResetValueIds(mPimpl->mModel->component(c));
        }
        return true;
    case Annotator::Type::TEST_VALUE:
        for (size_t c = 0; c < mPimpl->mModel->componentCount(); ++c) {
            mPimpl->doSetTestValueIds(mPimpl->mModel->component(c));
        }
        return true;
    case Annotator::Type::UNIT:
        mPimpl->doSetUnitIds();
        return true;
    case Annotator::Type::UNITS:
        mPimpl->doSetUnitsIds();
        return true;
    case Annotator::Type::VARIABLE:
        for (size_t c = 0; c < mPimpl->mModel->componentCount(); ++c) {
            mPimpl->doSetVariableIds(mPimpl->mModel->component(c));
        }
        return true;
    }
    return false;
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

void Annotator::AnnotatorImpl::doSetEncapsulationId()
{
    if (mModel->encapsulationId().empty()) {
        auto id = makeUniqueId();
        mModel->setEncapsulationId(id);
        mIdList.insert(std::make_pair(id, std::make_pair(Annotator::Type::ENCAPSULATION, mModel)));
    }
}

void Annotator::AnnotatorImpl::doSetModelId()
{
    if (mModel->id().empty()) {
        auto id = makeUniqueId();
        mModel->setId(id);
        mIdList.insert(std::make_pair(id, std::make_pair(Annotator::Type::MODEL, mModel)));
    }
}

void Annotator::AnnotatorImpl::doSetAllAutomaticIds()
{
    std::string id;
    // Traverse the model's entities and add ids where they are currently missing.
    if (mModel->id().empty()) {
        id = makeUniqueId();
        mModel->setId(id);
        mIdList.insert(std::make_pair(id, std::make_pair(Annotator::Type::MODEL, mModel)));
    }

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

    doSetEncapsulationId();
}

std::string Annotator::AnnotatorImpl::makeUniqueId()
{
    // Because the hexadecimal counter starts high enough that it will always have a letter as the first character,
    // we don't need to prefix it with any other string to be valid.
    int counter = 0xb4da55;
    std::stringstream stream;
    stream << std::hex << counter;
    std::string id = stream.str();
    stream.str(std::string());

    while (mIdList.count(id) != 0) {
        ++counter;
        stream << std::hex << counter;
        id = stream.str();
        stream.str(std::string());
    }
    // NB: This is only as unique as the information in mIdList permits.  That array must be updated
    // outside this function.
    return id;
}

} // namespace libcellml

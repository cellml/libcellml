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

using ItemList = std::multimap<std::string, AnyItem>;

AnyItem convertToShared(const AnyItem &item)
{
    AnyItem converted = std::make_pair(CellMLElement::UNDEFINED, nullptr);

    auto type = item.first;
    if (type == CellMLElement::COMPONENT || type == CellMLElement::COMPONENT_REF) {
        auto component = std::any_cast<ComponentWeakPtr>(item.second).lock();
        if (component) {
            converted.first = item.first;
            converted.second = component;
        }
    } else if (type == CellMLElement::CONNECTION || type == CellMLElement::MAP_VARIABLES) {
        auto weakVariablePair = std::any_cast<VariableWeakPair>(item.second);
        auto variable1 = weakVariablePair.first.lock();
        auto variable2 = weakVariablePair.second.lock();
        if (variable1 && variable2) {
            converted.first = item.first;
            converted.second = std::make_pair(variable1, variable2);
        }
    } else if (type == CellMLElement::ENCAPSULATION || type == CellMLElement::MODEL) {
        auto model = std::any_cast<ModelWeakPtr>(item.second).lock();
        if (model) {
            converted.first = item.first;
            converted.second = model;
        }
    } else if (type == CellMLElement::IMPORT) {
        auto importSource = std::any_cast<ImportSourceWeakPtr>(item.second).lock();
        if (importSource) {
            converted.first = item.first;
            converted.second = importSource;
        }
    } else if (type == CellMLElement::RESET || type == CellMLElement::RESET_VALUE || type == CellMLElement::TEST_VALUE) {
        auto reset = std::any_cast<ResetWeakPtr>(item.second).lock();
        if (reset) {
            converted.first = item.first;
            converted.second = reset;
        }
    } else if (type == CellMLElement::UNIT) {
        auto weakUnitItem = std::any_cast<UnitWeakItem>(item.second);
        auto units = weakUnitItem.first.lock();
        if (units) {
            converted.first = item.first;
            converted.second = std::make_pair(units, weakUnitItem.second);
        }
    } else if (type == CellMLElement::UNITS) {
        auto units = std::any_cast<UnitsWeakPtr>(item.second).lock();
        if (units) {
            converted.first = item.first;
            converted.second = units;
        }
    } else if (type == CellMLElement::VARIABLE) {
        auto variable = std::any_cast<VariableWeakPtr>(item.second).lock();
        if (variable) {
            converted.first = item.first;
            converted.second = variable;
        }
    }

    return converted;
}

AnyItem convertToWeak(const AnyItem &item)
{
    AnyItem converted = std::make_pair(item.first, nullptr);

    auto type = item.first;
    if (type == CellMLElement::COMPONENT || type == CellMLElement::COMPONENT_REF) {
        ComponentWeakPtr weakComponent = std::any_cast<ComponentPtr>(item.second);
        converted.second = weakComponent;
    } else if (type == CellMLElement::CONNECTION || type == CellMLElement::MAP_VARIABLES) {
        auto variablePair = std::any_cast<VariablePair>(item.second);
        VariableWeakPtr weakVariable1 = variablePair.first;
        VariableWeakPtr weakVariable2 = variablePair.second;
        converted.second = std::make_pair(weakVariable1, weakVariable2);
    } else if (type == CellMLElement::ENCAPSULATION || type == CellMLElement::MODEL) {
        auto model = std::any_cast<ModelPtr>(item.second);
        ModelWeakPtr weakModel = model;
        converted.second = weakModel;
    } else if (type == CellMLElement::IMPORT) {
        auto importSource = std::any_cast<ImportSourcePtr>(item.second);
        ImportSourceWeakPtr weakImportSource = importSource;
        converted.second = weakImportSource;
    } else if (type == CellMLElement::RESET || type == CellMLElement::RESET_VALUE || type == CellMLElement::TEST_VALUE) {
        auto reset = std::any_cast<ResetPtr>(item.second);
        ResetWeakPtr weakReset = reset;
        converted.second = weakReset;
    } else if (type == CellMLElement::UNIT) {
        auto unitItem = std::any_cast<UnitItem>(item.second);
        UnitsWeakPtr weakUnits = unitItem.first;
        converted.second = std::make_pair(weakUnits, unitItem.second);
    } else if (type == CellMLElement::UNITS) {
        auto units = std::any_cast<UnitsPtr>(item.second);
        UnitsWeakPtr weakUnits = units;
        converted.second = weakUnits;
    } else if (type == CellMLElement::VARIABLE) {
        auto variable = std::any_cast<VariablePtr>(item.second);
        VariableWeakPtr weakVariable = variable;
        converted.second = weakVariable;
    }

    return converted;
}

static const std::map<CellMLElement, std::string> typeToString = {
    {CellMLElement::COMPONENT, "component"},
    {CellMLElement::COMPONENT_REF, "component_ref"},
    {CellMLElement::CONNECTION, "connection"},
    {CellMLElement::ENCAPSULATION, "encapsulation"},
    {CellMLElement::IMPORT, "import"},
    {CellMLElement::MAP_VARIABLES, "map_variables"},
    {CellMLElement::MODEL, "model"},
    {CellMLElement::RESET, "reset"},
    {CellMLElement::RESET_VALUE, "reset_value"},
    {CellMLElement::TEST_VALUE, "test_value"},
    {CellMLElement::UNDEFINED, "undefined"},
    {CellMLElement::UNIT, "unit"},
    {CellMLElement::UNITS, "units"},
    {CellMLElement::VARIABLE, "variable"}};

struct Annotator::AnnotatorImpl
{
    Annotator *mAnnotator = nullptr;
    ItemList mIdList;
    ModelWeakPtr mModel;
    size_t mCounter = 0xb4da55;
    size_t mHash = 0;

    void update();
    void buildIdList();

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

    std::string setComponentRelatedId(const ComponentPtr &component, CellMLElement type);
    std::string setModelRelatedId(const ModelPtr &model, CellMLElement type);
    std::string setResetRelatedId(const ResetPtr &reset, CellMLElement type);

    bool exists(const std::string &id, size_t index) const;

    size_t generateHash();
    void updateHash();
    void doUpdateComponentHash(ComponentPtr &component, std::string &idsString);

    void addIssueNoModel() const;
    void addInvalidArgument(CellMLElement type) const;
    void addIssueNotFound(const std::string &id) const;
    void addIssueNonUnique(const std::string &id) const;
};

Annotator::Annotator()
    : mPimpl(new AnnotatorImpl())
{
    mPimpl->mAnnotator = this;
    mPimpl->mIdList = std::multimap<std::string, AnyItem>();
}

Annotator::~Annotator()
{
    delete mPimpl;
}

AnnotatorPtr Annotator::create() noexcept
{
    return std::shared_ptr<Annotator> {new Annotator {}};
}

template<typename T, typename U>
inline bool equals(const std::weak_ptr<T> &t, const std::weak_ptr<U> &u)
{
    return !t.owner_before(u) && !u.owner_before(t);
}

void listComponentIdsAndItems(const ComponentPtr &component, ItemList &idList)
{
    std::string id = component->id();
    if (!id.empty()) {
        auto entry = convertToWeak(std::make_pair(CellMLElement::COMPONENT, component));
        idList.insert(std::make_pair(id, entry));
    }
    // Imports.
    ImportSourcePtr importSource = component->importSource();
    if (component->isImport() && importSource != nullptr) {
        ImportSourceWeakPtr weakImportSource = importSource;
        id = importSource->id();
        if (!id.empty()) {
            auto entry = convertToWeak(std::make_pair(CellMLElement::IMPORT, importSource));
            idList.insert(std::make_pair(id, entry));
        }
    }
    // Component reference in encapsulation structure.
    id = component->encapsulationId();
    if (!id.empty()) {
        auto entry = convertToWeak(std::make_pair(CellMLElement::COMPONENT_REF, component));
        idList.insert(std::make_pair(id, entry));
    }
    // Variables.
    for (size_t v = 0; v < component->variableCount(); ++v) {
        VariablePtr variable = component->variable(v);
        VariableWeakPtr weakVariable = variable;
        id = variable->id();
        if (!id.empty()) {
            auto entry = convertToWeak(std::make_pair(CellMLElement::VARIABLE, variable));
            idList.insert(std::make_pair(id, entry));
        }
        for (size_t e = 0; e < variable->equivalentVariableCount(); ++e) {
            // Equivalent variable mappings.
            VariablePtr equivalentVariable = variable->equivalentVariable(e);
            VariableWeakPtr weakEquivalentVariable = equivalentVariable;
            id = Variable::equivalenceMappingId(variable, equivalentVariable);
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
                        if (it->second.first == CellMLElement::MAP_VARIABLES) {
                            auto testPair = std::any_cast<VariableWeakPair>(it->second.second);
                            if (equals(testPair.first, weakEquivalentVariable) && equals(testPair.second, weakVariable)) {
                                found = true;
                            }
                        }
                    }
                }
                if (!found) {
                    auto entry = convertToWeak(std::make_pair(CellMLElement::MAP_VARIABLES, std::make_pair(variable, equivalentVariable)));
                    idList.insert(std::make_pair(id, entry));
                }
            }

            // Connections.
            id = Variable::equivalenceConnectionId(variable, equivalentVariable);
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
                        if (it->second.first == CellMLElement::CONNECTION) {
                            auto testPair = std::any_cast<VariableWeakPair>(it->second.second);
                            if ((owningComponent(testPair.first.lock()) == owningComponent(equivalentVariable)) && (owningComponent(testPair.second.lock()) == owningComponent(variable))) {
                                found = true;
                            } else if ((owningComponent(testPair.second.lock()) == owningComponent(equivalentVariable)) && (owningComponent(testPair.first.lock()) == owningComponent(variable))) {
                                found = true;
                            }
                        }
                    }
                }
                if (!found) {
                    auto entry = convertToWeak(std::make_pair(CellMLElement::CONNECTION, std::make_pair(variable, equivalentVariable)));
                    idList.insert(std::make_pair(id, entry));
                }
            }
        }
    }
    // Resets.
    for (size_t r = 0; r < component->resetCount(); ++r) {
        ResetPtr reset = component->reset(r);
        ResetWeakPtr weakReset = reset;
        id = reset->id();
        if (!id.empty()) {
            auto entry = convertToWeak(std::make_pair(CellMLElement::RESET, reset));
            idList.insert(std::make_pair(id, entry));
        }
        id = reset->testValueId();
        if (!id.empty()) {
            auto entry = convertToWeak(std::make_pair(CellMLElement::TEST_VALUE, reset));
            idList.insert(std::make_pair(id, entry));
        }
        id = reset->resetValueId();
        if (!id.empty()) {
            auto entry = convertToWeak(std::make_pair(CellMLElement::RESET_VALUE, reset));
            idList.insert(std::make_pair(id, entry));
        }
    }

    for (size_t c = 0; c < component->componentCount(); ++c) {
        listComponentIdsAndItems(component->component(c), idList);
    }
}

ItemList listIdsAndItems(const ModelPtr &model)
{
    // Collect all existing ids in a list and return.
    //    auto model = weakModel.lock();
    ItemList idList;
    // Model.
    std::string id = model->id();
    if (!id.empty()) {
        auto entry = convertToWeak(std::make_pair(CellMLElement::MODEL, model));
        idList.insert(std::make_pair(id, entry));
    }

    // Units.
    for (size_t u = 0; u < model->unitsCount(); ++u) {
        UnitsPtr units = model->units(u);
        UnitsWeakPtr weakUnits = units;
        id = units->id();
        if (!id.empty()) {
            auto entry = convertToWeak(std::make_pair(CellMLElement::UNITS, units));
            idList.insert(std::make_pair(id, entry));
        }
        for (size_t i = 0; i < units->unitCount(); ++i) {
            std::string prefix;
            std::string reference;
            double exponent;
            double multiplier;
            units->unitAttributes(i, reference, prefix, exponent, multiplier, id);
            if (!id.empty()) {
                auto entry = convertToWeak(std::make_pair(CellMLElement::UNIT, std::make_pair(units, i)));
                idList.insert(std::make_pair(id, entry));
            }
        }
        if (units->isImport() && units->importSource() != nullptr) {
            ImportSourcePtr importSource = units->importSource();
            ImportSourceWeakPtr weakImportSource = importSource;
            id = importSource->id();
            auto entry = convertToWeak(std::make_pair(CellMLElement::IMPORT, importSource));
            idList.insert(std::make_pair(id, entry));
        }
    }

    // Components.
    for (size_t c = 0; c < model->componentCount(); ++c) {
        listComponentIdsAndItems(model->component(c), idList);
    }

    // Encapsulation.
    id = model->encapsulationId();
    if (!id.empty()) {
        auto entry = convertToWeak(std::make_pair(CellMLElement::ENCAPSULATION, model));
        idList.insert(std::make_pair(id, entry));
    }

    return idList;
}

std::string Annotator::typeAsString(CellMLElement type)
{
    return typeToString.at(type);
}

void Annotator::AnnotatorImpl::buildIdList()
{
    mIdList.clear();
    mIdList = listIdsAndItems(mModel.lock());
}

void Annotator::AnnotatorImpl::update()
{
    size_t hash = generateHash();
    if (mHash != hash) {
        buildIdList();
        mHash = hash;
    }
}

void Annotator::setModel(const ModelPtr &model)
{
    removeAllIssues();
    mPimpl->mModel = model;
    mPimpl->buildIdList();
    mPimpl->mHash = mPimpl->generateHash();
}

void Annotator::AnnotatorImpl::addIssueNotFound(const std::string &id) const
{
    auto issue = Issue::create();
    issue->setDescription("Could not find an item with an id of '" + id + "' in the model.");
    issue->setLevel(Issue::Level::WARNING);
    mAnnotator->addIssue(issue);
}

void Annotator::AnnotatorImpl::addIssueNonUnique(const std::string &id) const
{
    auto issue = Issue::create();
    issue->setDescription("The id '" + id + "' occurs " + std::to_string(mIdList.count(id)) + " times in the model so a unique item cannot be located.");
    issue->setLevel(Issue::Level::WARNING);
    mAnnotator->addIssue(issue);
}

void Annotator::AnnotatorImpl::addIssueNoModel() const
{
    auto issue = Issue::create();
    issue->setDescription("This Annotator object does not have a model to work with.");
    issue->setLevel(Issue::Level::ERROR);
    mAnnotator->addIssue(issue);
}

void Annotator::AnnotatorImpl::addInvalidArgument(CellMLElement type) const
{
    auto issue = Issue::create();
    issue->setDescription("The given type '" + typeAsString(type) + "' is invalid for this method.");
    issue->setLevel(Issue::Level::ERROR);
    mAnnotator->addIssue(issue);
}

bool Annotator::AnnotatorImpl::exists(const std::string &id, size_t index) const
{
    bool exists = true;
    if (!mAnnotator->hasModel()) {
        addIssueNoModel();
        exists = false;
    } else if (mIdList.count(id) <= index || mIdList.count(id) == 0) {
        addIssueNotFound(id);
        exists = false;
    }

    return exists;
}

AnyItem Annotator::item(const std::string &id)
{
    auto retrieved = item(id, 0);
    if (retrieved.first != CellMLElement::UNDEFINED && !isUnique(id)) {
        mPimpl->addIssueNonUnique(id);
    }
    return retrieved;
}

AnyItem Annotator::item(const std::string &id, size_t index)
{
    return mPimpl->exists(id, index) ? std::move(items(id)[index]) : std::make_pair(CellMLElement::UNDEFINED, nullptr);
}

bool Annotator::isUnique(const std::string &id)
{
    return mPimpl->mIdList.count(id) == 1;
}

std::vector<AnyItem> Annotator::items(const std::string &id)
{
    mPimpl->update();
    std::vector<AnyItem> items;
    auto range = mPimpl->mIdList.equal_range(id);
    for (auto it = range.first; it != range.second; ++it) {
        items.push_back(convertToShared(it->second));
    }
    return items;
}

std::vector<std::string> Annotator::duplicateIds()
{
    std::vector<std::string> ids;
    for (auto i = mPimpl->mIdList.begin(), end = mPimpl->mIdList.end(); i != end; i = mPimpl->mIdList.upper_bound(i->first)) {
        auto next = i;
        next++;
        if ((next != end) && (next->first == i->first) && !i->first.empty()) {
            ids.push_back(i->first);
        }
    }
    return ids;
}

std::vector<std::string> Annotator::ids()
{
    std::vector<std::string> ids;
    for (auto i = mPimpl->mIdList.begin(), end = mPimpl->mIdList.end(); i != end; i = mPimpl->mIdList.upper_bound(i->first)) {
        if (!i->first.empty()) {
            ids.push_back(i->first);
        }
    }
    return ids;
}

std::multimap<std::string, CellMLElement> Annotator::dictionary()
{
    std::multimap<std::string, CellMLElement> dict;
    for (auto &i : mPimpl->mIdList) {
        dict.insert(std::make_pair(i.first, i.second.first));
    }
    return dict;
}

ComponentPtr Annotator::component(const std::string &id)
{
    return component(id, 0);
}

VariablePtr Annotator::variable(const std::string &id)
{
    return variable(id, 0);
}

ModelPtr Annotator::model(const std::string &id)
{
    return model(id, 0);
}

ModelPtr Annotator::encapsulation(const std::string &id)
{
    return encapsulation(id, 0);
}

UnitsPtr Annotator::units(const std::string &id)
{
    return units(id, 0);
}

ImportSourcePtr Annotator::importSource(const std::string &id)
{
    return importSource(id, 0);
}

ResetPtr Annotator::reset(const std::string &id)
{
    return reset(id, 0);
}

VariablePair Annotator::connection(const std::string &id)
{
    return connection(id, 0);
}

VariablePair Annotator::mapVariables(const std::string &id)
{
    return mapVariables(id, 0);
}

UnitItem Annotator::unit(const std::string &id)
{
    return unit(id, 0);
}

ComponentPtr Annotator::componentRef(const std::string &id)
{
    return componentRef(id, 0);
}

ResetPtr Annotator::testValue(const std::string &id)
{
    return testValue(id, 0);
}

ResetPtr Annotator::resetValue(const std::string &id)
{
    return resetValue(id, 0);
}

ComponentPtr Annotator::component(const std::string &id, size_t index)
{
    mPimpl->update();
    ComponentPtr component = nullptr;
    if (mPimpl->exists(id, index)) {
        auto i = items(id).at(index);
        try {
            component = std::any_cast<ComponentPtr>(i.second);
        } catch (std::bad_any_cast &) {
        }
    }
    return component;
}

ComponentPtr Annotator::componentRef(const std::string &id, size_t index)
{
    return component(id, index);
}

VariablePtr Annotator::variable(const std::string &id, size_t index)
{
    mPimpl->update();
    VariablePtr variable = nullptr;
    if (mPimpl->exists(id, index)) {
        auto i = items(id).at(index);
        try {
            variable = std::any_cast<VariablePtr>(i.second);
        } catch (std::bad_any_cast &e) {
            (void)e;
        }
    }

    return variable;
}

ModelPtr Annotator::model(const std::string &id, size_t index)
{
    mPimpl->update();
    ModelPtr model = nullptr;
    if (mPimpl->exists(id, index)) {
        auto i = items(id).at(index);
        try {
            model = std::any_cast<ModelPtr>(i.second);
        } catch (std::bad_any_cast &e) {
            (void)e;
        }
    }

    return model;
}

ModelPtr Annotator::encapsulation(const std::string &id, size_t index)
{
    return model(id, index);
}

UnitsPtr Annotator::units(const std::string &id, size_t index)
{
    mPimpl->update();
    UnitsPtr units = nullptr;
    if (mPimpl->exists(id, index)) {
        auto i = items(id).at(index);
        try {
            units = std::any_cast<UnitsPtr>(i.second);
        } catch (std::bad_any_cast &e) {
            (void)e;
        }
    }
    return units;
}

ImportSourcePtr Annotator::importSource(const std::string &id, size_t index)
{
    mPimpl->update();
    ImportSourcePtr importSource = nullptr;
    if (mPimpl->exists(id, index)) {
        auto i = items(id).at(index);
        try {
            importSource = std::any_cast<ImportSourcePtr>(i.second);
        } catch (std::bad_any_cast &e) {
            (void)e;
        }
    }

    return importSource;
}

ResetPtr Annotator::reset(const std::string &id, size_t index)
{
    mPimpl->update();
    ResetPtr reset = nullptr;
    if (mPimpl->exists(id, index)) {
        auto i = items(id).at(index);
        try {
            reset = std::any_cast<ResetPtr>(i.second);
        } catch (std::bad_any_cast &e) {
            (void)e;
        }
    }
    return reset;
}

ResetPtr Annotator::testValue(const std::string &id, size_t index)
{
    return reset(id, index);
}

ResetPtr Annotator::resetValue(const std::string &id, size_t index)
{
    return reset(id, index);
}

VariablePair Annotator::connection(const std::string &id, size_t index)
{
    mPimpl->update();
    VariablePair pair = std::make_pair(nullptr, nullptr);
    if (mPimpl->exists(id, index)) {
        auto i = items(id).at(index);
        try {
            pair = std::any_cast<VariablePair>(i.second);
        } catch (std::bad_any_cast &e) {
            (void)e;
        }
    }

    return pair;
}

VariablePair Annotator::mapVariables(const std::string &id, size_t index)
{
    return connection(id, index);
}

UnitItem Annotator::unit(const std::string &id, size_t index)
{
    mPimpl->update();
    UnitItem unitItem = std::make_pair(nullptr, 0);
    if (mPimpl->exists(id, index)) {
        auto i = items(id).at(index);
        try {
            unitItem = std::any_cast<UnitItem>(i.second);
        } catch (std::bad_any_cast &e) {
            (void)e;
        }
    }

    return unitItem;
}

void Annotator::clearAllIds()
{
    auto model = mPimpl->mModel.lock();
    if (model) {
        model->setId("");
        for (size_t i = 0; i < model->importSourceCount(); ++i) {
            model->importSource(i)->setId("");
        }
        for (size_t i = 0; i < model->unitsCount(); ++i) {
            model->units(i)->setId("");
            for (size_t j = 0; j < model->units(i)->unitCount(); ++j) {
                model->units(i)->setUnitId(j, "");
            }
        }
        for (size_t i = 0; i < model->componentCount(); ++i) {
            mPimpl->doClearComponentIds(model->component(i));
        }
        model->setEncapsulationId("");

        mPimpl->mIdList.clear();
        mPimpl->mHash = 0;
    } else {
        mPimpl->addIssueNoModel();
    }
}

void Annotator::clearAllIds(ModelPtr &model)
{
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
    bool assigned = false;
    auto model = mPimpl->mModel.lock();
    if (model) {
        mPimpl->doSetAllAutomaticIds();
        assigned = true;
    } else {
        mPimpl->addIssueNoModel();
    }

    return assigned;
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

bool Annotator::assignIds(CellMLElement type)
{
    auto model = mPimpl->mModel.lock();
    bool changed = false;
    if (model) {
        changed = true;
        switch (type) {
        case CellMLElement::COMPONENT:
            for (size_t index = 0; index < model->componentCount(); ++index) {
                mPimpl->doSetComponentIds(model->component(index));
            }
            break;
        case CellMLElement::COMPONENT_REF:
            for (size_t index = 0; index < model->componentCount(); ++index) {
                mPimpl->doSetComponentRefIds(model->component(index));
            }
            break;
        case CellMLElement::CONNECTION:
            for (size_t index = 0; index < model->componentCount(); ++index) {
                mPimpl->doSetConnectionIds(model->component(index));
            }
            break;
        case CellMLElement::ENCAPSULATION:
            mPimpl->doSetEncapsulationIds();
            break;
        case CellMLElement::IMPORT:
            mPimpl->doSetImportSourceIds();
            break;
        case CellMLElement::MAP_VARIABLES:
            for (size_t index = 0; index < model->componentCount(); ++index) {
                mPimpl->doSetMapVariablesIds(model->component(index));
            }
            break;
        case CellMLElement::MODEL:
            mPimpl->doSetModelIds();
            break;
        case CellMLElement::RESET:
            for (size_t index = 0; index < model->componentCount(); ++index) {
                mPimpl->doSetResetIds(model->component(index));
            }
            break;
        case CellMLElement::RESET_VALUE:
            for (size_t index = 0; index < model->componentCount(); ++index) {
                mPimpl->doSetResetValueIds(model->component(index));
            }
            break;
        case CellMLElement::TEST_VALUE:
            for (size_t index = 0; index < model->componentCount(); ++index) {
                mPimpl->doSetTestValueIds(model->component(index));
            }
            break;
        case CellMLElement::UNIT:
            mPimpl->doSetUnitIds();
            break;
        case CellMLElement::UNITS:
            mPimpl->doSetUnitsIds();
            break;
        case CellMLElement::VARIABLE:
            for (size_t index = 0; index < model->componentCount(); ++index) {
                mPimpl->doSetVariableIds(model->component(index));
            }
            break;
        case CellMLElement::MATHML:
        case CellMLElement::UNDEFINED:
            changed = false;
            break;
        }
        setModel(model);
    } else {
        mPimpl->addIssueNoModel();
    }
    return changed;
}

void Annotator::AnnotatorImpl::doSetImportSourceIds()
{
    // Import items.
    auto model = mModel.lock();
    for (size_t i = 0; i < model->importSourceCount(); ++i) {
        auto is = model->importSource(i);
        if (is->id().empty()) {
            auto id = makeUniqueId();
            is->setId(id);
            auto entry = convertToWeak(std::make_pair(CellMLElement::IMPORT, is));
            mIdList.insert(std::make_pair(id, entry));
        }
    }
}

void Annotator::AnnotatorImpl::doSetUnitsIds()
{
    // Units and unit items.
    auto model = mModel.lock();
    for (size_t u = 0; u < model->unitsCount(); ++u) {
        auto us = model->units(u);
        if (us->id().empty()) {
            auto id = makeUniqueId();
            us->setId(id);
            auto entry = convertToWeak(std::make_pair(CellMLElement::UNITS, us));
            mIdList.insert(std::make_pair(id, entry));
        }
    }
}

void Annotator::AnnotatorImpl::doSetUnitIds()
{
    auto model = mModel.lock();
    for (size_t u = 0; u < model->unitsCount(); ++u) {
        auto us = model->units(u);
        for (size_t i = 0; i < us->unitCount(); i++) {
            if (us->unitId(i).empty()) {
                auto id = makeUniqueId();
                us->setUnitId(i, id);
                auto entry = convertToWeak(std::make_pair(CellMLElement::UNIT, std::make_pair(us, i)));
                mIdList.insert(std::make_pair(id, entry));
            }
        }
    }
}

void Annotator::AnnotatorImpl::doSetComponentIds(const ComponentPtr &parent)
{
    if (parent->id().empty()) {
        auto id = makeUniqueId();
        parent->setId(id);
        auto entry = convertToWeak(std::make_pair(CellMLElement::COMPONENT, parent));
        mIdList.insert(std::make_pair(id, entry));
    }
    for (size_t c = 0; c < parent->componentCount(); ++c) {
        if (parent->component(c)->id().empty()) {
            auto id = makeUniqueId();
            parent->component(c)->setId(id);
            auto entry = convertToWeak(std::make_pair(CellMLElement::COMPONENT, parent->component(c)));
            mIdList.insert(std::make_pair(id, entry));
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
            auto entry = convertToWeak(std::make_pair(CellMLElement::VARIABLE, parent->variable(v)));
            mIdList.insert(std::make_pair(id, entry));
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
            auto entry = convertToWeak(std::make_pair(CellMLElement::RESET, parent->reset(r)));
            mIdList.insert(std::make_pair(id, entry));
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
            auto entry = convertToWeak(std::make_pair(CellMLElement::RESET_VALUE, parent->reset(r)));
            mIdList.insert(std::make_pair(id, entry));
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
            auto entry = convertToWeak(std::make_pair(CellMLElement::TEST_VALUE, parent->reset(r)));
            mIdList.insert(std::make_pair(id, entry));
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
                auto entry = convertToWeak(std::make_pair(CellMLElement::CONNECTION, v1v2));
                mIdList.insert(std::make_pair(id, entry));
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
                auto entry = convertToWeak(std::make_pair(CellMLElement::MAP_VARIABLES, v1v2));
                mIdList.insert(std::make_pair(id, entry));
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
        auto entry = convertToWeak(std::make_pair(CellMLElement::COMPONENT_REF, parent));
        mIdList.insert(std::make_pair(id, entry));
    }
    for (size_t c = 0; c < parent->componentCount(); ++c) {
        if (parent->component(c)->encapsulationId().empty()) {
            auto id = makeUniqueId();
            parent->component(c)->setEncapsulationId(id);
            auto entry = convertToWeak(std::make_pair(CellMLElement::COMPONENT_REF, parent->component(c)));
            mIdList.insert(std::make_pair(id, entry));
        }
        doSetComponentRefIds(parent->component(c));
    }
}

void Annotator::AnnotatorImpl::doSetEncapsulationIds()
{
    auto model = mModel.lock();
    if (model->encapsulationId().empty()) {
        auto id = makeUniqueId();
        model->setEncapsulationId(id);
        auto entry = convertToWeak(std::make_pair(CellMLElement::ENCAPSULATION, model));
        mIdList.insert(std::make_pair(id, entry));
    }
}

void Annotator::AnnotatorImpl::doSetModelIds()
{
    auto model = mModel.lock();
    if (model->id().empty()) {
        auto id = makeUniqueId();
        model->setId(id);
        auto entry = convertToWeak(std::make_pair(CellMLElement::MODEL, model));
        mIdList.insert(std::make_pair(id, entry));
    }
}

void Annotator::AnnotatorImpl::doSetAllAutomaticIds()
{
    doSetModelIds();
    doSetImportSourceIds();
    doSetUnitsIds();
    doSetUnitIds();
    auto model = mModel.lock();
    for (size_t index = 0; index < model->componentCount(); ++index) {
        auto component = model->component(index);
        doSetComponentIds(component);
        doSetVariableIds(component);
        doSetResetIds(component);
        doSetResetValueIds(component);
        doSetTestValueIds(component);
        doSetConnectionIds(component);
        doSetMapVariablesIds(component);
        doSetComponentRefIds(component);
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

std::string Annotator::AnnotatorImpl::setComponentRelatedId(const ComponentPtr &component, CellMLElement type)
{
    auto oldId = component->id();
    if (type == CellMLElement::COMPONENT_REF) {
        oldId = component->encapsulationId();
    }

    std::string id;

    if (owningModel(component) != mModel.lock()) {
        return id;
    }

    ComponentWeakPtr weakComponent = component;
    // NB: the id must be created before the old one is removed from the idList to prevent the
    // reuse of previously allocated ids.
    id = makeUniqueId();
    if (!oldId.empty()) {
        auto range = mIdList.equal_range(oldId);
        for (auto it = range.first; it != range.second; ++it) {
            if ((it->second.first == type) && equals(std::any_cast<ComponentWeakPtr>(it->second.second), weakComponent)) {
                mIdList.erase(it);
                break;
            }
        }
    }
    if (type == CellMLElement::COMPONENT_REF) {
        component->setEncapsulationId(id);
    } else {
        component->setId(id);
    }

    mIdList.insert(std::make_pair(id, std::make_pair(type, weakComponent)));
    //    mPimpl->updateHash();
    return id;
}

std::string Annotator::assignComponentId(const ComponentPtr &component)
{
    return mPimpl->setComponentRelatedId(component, CellMLElement::COMPONENT);
}

std::string Annotator::assignComponentRefId(const ComponentPtr &component)
{
    return mPimpl->setComponentRelatedId(component, CellMLElement::COMPONENT_REF);
}

std::string Annotator::assignConnectionId(const VariablePair &variablePair)
{
    auto oldId = Variable::equivalenceConnectionId(variablePair.first, variablePair.second);
    auto type = CellMLElement::CONNECTION;
    auto model = mPimpl->mModel.lock();
    std::string id;

    if (owningModel(variablePair.first) != model || owningModel(variablePair.second) != model) {
        return id;
    }

    VariableWeakPtr weakVariable1 = variablePair.first;
    VariableWeakPtr weakVariable2 = variablePair.second;
    VariableWeakPair weakVariablePair = std::make_pair(weakVariable1, weakVariable2);

    id = mPimpl->makeUniqueId();
    if (!oldId.empty()) {
        auto range = mPimpl->mIdList.equal_range(oldId);
        for (auto it = range.first; it != range.second; ++it) {
            if (it->second.first == type) {
                auto testPair = std::any_cast<VariableWeakPair>(it->second.second);
                if ((owningComponent(testPair.first.lock()) == owningComponent(variablePair.first) || owningComponent(testPair.first.lock()) == owningComponent(variablePair.second)) && (owningComponent(testPair.second.lock()) == owningComponent(variablePair.first) || owningComponent(testPair.second.lock()) == owningComponent(variablePair.second))) {
                    mPimpl->mIdList.erase(it);
                    break;
                }
            }
        }
    }
    Variable::setEquivalenceConnectionId(variablePair.first, variablePair.second, id);
    mPimpl->mIdList.insert(std::make_pair(id, std::make_pair(type, weakVariablePair)));
    //    mPimpl->updateHash();
    return id;
}

std::string Annotator::assignMapVariablesId(const VariablePair &variablePair)
{
    auto oldId = Variable::equivalenceMappingId(variablePair.first, variablePair.second);
    auto type = CellMLElement::MAP_VARIABLES;
    std::string id;
    auto model = mPimpl->mModel.lock();

    if (owningModel(variablePair.first) != model || owningModel(variablePair.second) != model) {
        return id;
    }

    VariableWeakPtr weakVariable1 = variablePair.first;
    VariableWeakPtr weakVariable2 = variablePair.second;
    VariableWeakPair weakVariablePair = std::make_pair(weakVariable1, weakVariable2);

    id = mPimpl->makeUniqueId();

    if (!oldId.empty()) {
        auto range = mPimpl->mIdList.equal_range(oldId);
        for (auto it = range.first; it != range.second; ++it) {
            if (it->second.first == type) {
                auto testPair = std::any_cast<VariableWeakPair>(it->second.second);
                if ((equals(testPair.first, weakVariable1) && equals(testPair.second, weakVariable2)) || (equals(testPair.first, weakVariable2) && equals(testPair.second, weakVariable1))) {
                    mPimpl->mIdList.erase(it);
                    break;
                }
            }
        }
    }
    Variable::setEquivalenceMappingId(variablePair.first, variablePair.second, id);
    mPimpl->mIdList.insert(std::make_pair(id, std::make_pair(type, weakVariablePair)));
    //    mPimpl->updateHash();
    return id;
}

std::string Annotator::AnnotatorImpl::setModelRelatedId(const ModelPtr &model, CellMLElement type)
{
    auto oldId = model->id();
    if (type == CellMLElement::ENCAPSULATION) {
        oldId = model->encapsulationId();
    }
    std::string id;

    if (model != mModel.lock()) {
        return id;
    }

    ModelWeakPtr weakModel = model;
    id = makeUniqueId();

    if (!oldId.empty()) {
        auto range = mIdList.equal_range(oldId);
        auto it = range.first;
        // There will only be one model, and it will always be the first in the list of items with its id.
        if ((it->second.first == type) && equals(std::any_cast<ModelWeakPtr>(it->second.second), weakModel)) {
            mIdList.erase(it);
        }
    }

    if (type == CellMLElement::ENCAPSULATION) {
        model->setEncapsulationId(id);
    } else {
        model->setId(id);
    }
    mIdList.insert(std::make_pair(id, std::make_pair(type, weakModel)));
    //    mPimpl->updateHash();
    return id;
}

std::string Annotator::assignModelId(const ModelPtr &model)
{
    return mPimpl->setModelRelatedId(model, CellMLElement::MODEL);
}

std::string Annotator::assignEncapsulationId(const ModelPtr &model)
{
    return mPimpl->setModelRelatedId(model, CellMLElement::ENCAPSULATION);
}

std::string Annotator::assignImportSourceId(const ImportSourcePtr &importSource)
{
    auto oldId = importSource->id();
    auto type = CellMLElement::IMPORT;
    std::string id;

    if (owningModel(importSource) != mPimpl->mModel.lock()) {
        return id;
    }

    ImportSourceWeakPtr weakImportSource = importSource;
    id = mPimpl->makeUniqueId();

    if (!oldId.empty()) {
        auto range = mPimpl->mIdList.equal_range(oldId);
        for (auto it = range.first; it != range.second; ++it) {
            if ((it->second.first == type) && equals(std::any_cast<ImportSourceWeakPtr>(it->second.second), weakImportSource)) {
                mPimpl->mIdList.erase(it);
                break;
            }
        }
    }
    importSource->setId(id);
    mPimpl->mIdList.insert(std::make_pair(id, std::make_pair(type, weakImportSource)));
    //    mPimpl->updateHash();
    return id;
}

std::string Annotator::AnnotatorImpl::setResetRelatedId(const ResetPtr &reset, CellMLElement type)
{
    auto oldId = reset->id();
    if (type == CellMLElement::RESET_VALUE) {
        oldId = reset->resetValueId();
    } else if (type == CellMLElement::TEST_VALUE) {
        oldId = reset->testValueId();
    }
    std::string id;

    if (owningModel(reset) != mModel.lock()) {
        return id;
    }

    ResetWeakPtr weakReset = reset;

    id = makeUniqueId();

    if (!oldId.empty()) {
        auto range = mIdList.equal_range(oldId);
        for (auto it = range.first; it != range.second; ++it) {
            if ((it->second.first == type) && equals(std::any_cast<ResetWeakPtr>(it->second.second), weakReset)) {
                mIdList.erase(it);
                break;
            }
        }
    }
    if (type == CellMLElement::RESET_VALUE) {
        reset->setResetValueId(id);
    } else if (type == CellMLElement::TEST_VALUE) {
        reset->setTestValueId(id);
    } else {
        reset->setId(id);
    }
    mIdList.insert(std::make_pair(id, std::make_pair(type, weakReset)));
    //    mPimpl->updateHash();
    return id;
}

std::string Annotator::assignResetId(const ResetPtr &reset)
{
    return mPimpl->setResetRelatedId(reset, CellMLElement::RESET);
}

std::string Annotator::assignResetValueId(const ResetPtr &reset)
{
    return mPimpl->setResetRelatedId(reset, CellMLElement::RESET_VALUE);
}

std::string Annotator::assignTestValueId(const ResetPtr &reset)
{
    return mPimpl->setResetRelatedId(reset, CellMLElement::TEST_VALUE);
}

std::string Annotator::assignUnitId(const UnitItem &unitItem)
{
    auto oldId = unitItem.first->unitId(unitItem.second);
    auto type = CellMLElement::UNIT;
    std::string id;

    if (owningModel(unitItem.first) != mPimpl->mModel.lock()) {
        return id;
    }

    UnitsWeakPtr weakUnits = unitItem.first;
    UnitWeakItem weakUnitItem = std::make_pair(weakUnits, unitItem.second);

    id = mPimpl->makeUniqueId();

    if (!oldId.empty()) {
        auto range = mPimpl->mIdList.equal_range(oldId);
        for (auto it = range.first; it != range.second; ++it) {
            if ((it->second.first == type) && equals(std::any_cast<UnitWeakItem>(it->second.second).first, weakUnits) && std::any_cast<UnitWeakItem>(it->second.second).second == unitItem.second) {
                mPimpl->mIdList.erase(it);
                break;
            }
        }
    }

    unitItem.first->setUnitId(unitItem.second, id);
    mPimpl->mIdList.insert(std::make_pair(id, std::make_pair(type, weakUnitItem)));
    //    mPimpl->updateHash();
    return id;
}

std::string Annotator::assignUnitsId(const UnitsPtr &units)
{
    auto oldId = units->id();
    auto type = CellMLElement::UNITS;
    std::string id;

    if (owningModel(units) != mPimpl->mModel.lock()) {
        return id;
    }

    UnitsWeakPtr weakUnits = units;

    id = mPimpl->makeUniqueId();

    if (!oldId.empty()) {
        auto range = mPimpl->mIdList.equal_range(oldId);
        for (auto it = range.first; it != range.second; ++it) {
            if ((it->second.first == type) && equals(std::any_cast<UnitsWeakPtr>(it->second.second), weakUnits)) {
                mPimpl->mIdList.erase(it);
                break;
            }
        }
    }

    units->setId(id);
    mPimpl->mIdList.insert(std::make_pair(id, std::make_pair(type, weakUnits)));
    mPimpl->updateHash();
    return id;
}

std::string Annotator::assignVariableId(const VariablePtr &variable)
{
    auto oldId = variable->id();
    auto type = CellMLElement::VARIABLE;
    std::string id;

    if (owningModel(variable) != mPimpl->mModel.lock()) {
        return id;
    }

    VariableWeakPtr weakVariable = variable;

    id = mPimpl->makeUniqueId();

    if (!oldId.empty()) {
        auto range = mPimpl->mIdList.equal_range(oldId);
        for (auto it = range.first; it != range.second; ++it) {
            if ((it->second.first == type) && equals(std::any_cast<VariableWeakPtr>(it->second.second), weakVariable)) {
                mPimpl->mIdList.erase(it);
                break;
            }
        }
    }

    variable->setId(id);
    mPimpl->mIdList.insert(std::make_pair(id, std::make_pair(type, weakVariable)));
    //    mPimpl->updateHash();
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
    case CellMLElement::COMPONENT:
        component = std::any_cast<ComponentPtr>(item.second);
        id = assignComponentId(component);
        break;

    case CellMLElement::COMPONENT_REF:
        component = std::any_cast<ComponentPtr>(item.second);
        id = assignComponentRefId(component);
        break;

    case CellMLElement::CONNECTION:
        variablePair = std::any_cast<VariablePair>(item.second);
        id = assignConnectionId(variablePair);
        break;

    case CellMLElement::ENCAPSULATION:
        model = std::any_cast<ModelPtr>(item.second);
        id = assignEncapsulationId(model);
        break;

    case CellMLElement::IMPORT:
        importSource = std::any_cast<ImportSourcePtr>(item.second);
        id = assignImportSourceId(importSource);
        break;

    case CellMLElement::MAP_VARIABLES:
        variablePair = std::any_cast<VariablePair>(item.second);
        id = assignMapVariablesId(variablePair);
        break;

    case CellMLElement::MODEL:
        model = std::any_cast<ModelPtr>(item.second);
        id = assignModelId(model);
        break;

    case CellMLElement::RESET:
        reset = std::any_cast<ResetPtr>(item.second);
        id = assignResetId(reset);
        break;

    case CellMLElement::RESET_VALUE:
        reset = std::any_cast<ResetPtr>(item.second);
        id = assignResetValueId(reset);
        break;

    case CellMLElement::TEST_VALUE:
        reset = std::any_cast<ResetPtr>(item.second);
        id = assignTestValueId(reset);
        break;

    case CellMLElement::UNIT:
        unitItem = std::any_cast<UnitItem>(item.second);
        id = assignUnitId(unitItem);
        break;

    case CellMLElement::UNITS:
        units = std::any_cast<UnitsPtr>(item.second);
        id = assignUnitsId(units);
        break;

    case CellMLElement::VARIABLE:
        variable = std::any_cast<VariablePtr>(item.second);
        id = assignVariableId(variable);
        break;
    case CellMLElement::MATHML:
    case CellMLElement::UNDEFINED:
        break;
    }
    return id;
}

std::string Annotator::assignId(const ModelPtr &item, CellMLElement type)
{
    std::string id;
    if (type == CellMLElement::MODEL) {
        id = assignModelId(item);
    } else if (type == CellMLElement::ENCAPSULATION) {
        id = assignEncapsulationId(item);
    } else {
        mPimpl->addInvalidArgument(type);
    }
    return id;
}

std::string Annotator::assignId(const ComponentPtr &item, CellMLElement type)
{
    std::string id;
    if (type == CellMLElement::COMPONENT) {
        id = assignComponentId(item);
    } else if (type == CellMLElement::COMPONENT_REF) {
        id = assignComponentRefId(item);
    } else {
        mPimpl->addInvalidArgument(type);
    }
    return id;
}

std::string Annotator::assignId(const ResetPtr &item, CellMLElement type)
{
    std::string id;

    if (type == CellMLElement::RESET) {
        id = assignResetId(item);
    } else if (type == CellMLElement::RESET_VALUE) {
        id = assignResetValueId(item);
    } else if (type == CellMLElement::TEST_VALUE) {
        id = assignTestValueId(item);
    } else {
        mPimpl->addInvalidArgument(type);
    }
    return id;
}

std::string Annotator::assignId(const UnitsPtr &item)
{
    return assignUnitsId(item);
}

std::string Annotator::assignId(const ImportSourcePtr &item)
{
    return assignImportSourceId(item);
}

std::string Annotator::assignId(const UnitsPtr &units, size_t index)
{
    UnitItem item;
    item.first = units;
    item.second = index;
    return assignUnitId(item);
}

std::string Annotator::assignId(const UnitItem &item)
{
    return assignUnitId(item);
}

std::string Annotator::assignId(const VariablePtr &item)
{
    return assignVariableId(item);
}

std::string Annotator::assignId(const VariablePair &pair, CellMLElement type)
{
    std::string id;
    if (type == CellMLElement::MAP_VARIABLES) {
        id = assignMapVariablesId(pair);
    } else if (type == CellMLElement::CONNECTION) {
        id = assignConnectionId(pair);
    } else {
        mPimpl->addInvalidArgument(type);
    }
    return id;
}

std::string Annotator::assignId(const VariablePtr &item1, const VariablePtr &item2, CellMLElement type)
{
    // Overloaded so that bindings work better.
    std::string id;
    VariablePair item;
    if (type == CellMLElement::MAP_VARIABLES) {
        item.first = item1;
        item.second = item2;
        id = assignMapVariablesId(item);
    } else if (type == CellMLElement::CONNECTION) {
        item.first = item1;
        item.second = item2;
        id = assignConnectionId(item);
    } else {
        mPimpl->addInvalidArgument(type);
    }
    return id;
}

size_t Annotator::duplicateCount(const std::string &id)
{
    return mPimpl->mIdList.count(id);
}

void Annotator::AnnotatorImpl::doUpdateComponentHash(ComponentPtr &component, std::string &idsString)
{
    for (size_t i = 0; i < component->variableCount(); ++i) {
        idsString += "v=" + std::to_string(i) + component->variable(i)->id();
    }

    for (size_t i = 0; i < component->resetCount(); ++i) {
        auto reset = component->reset(i);
        idsString += "r=" + std::to_string(i) + reset->id() + "rv=" + reset->resetValueId() + "tv=" + reset->testValueId();
    }

    // Note that MathML ids are not yet included.

    for (size_t i = 0; i < component->componentCount(); ++i) {
        auto child = component->component(i);
        idsString += "c=" + std::to_string(i) + child->id() + "ce=" + child->encapsulationId();
        doUpdateComponentHash(child, idsString);
    }
}

size_t Annotator::AnnotatorImpl::generateHash()
{
    // Serialise the stored model into a (very) simplified string of id-ed items, and create a hash.
    size_t hash = 0;
    auto model = mModel.lock();
    if (model) {
        std::string idsString;
        idsString += "m=" + model->id() + "me=" + model->encapsulationId();

        for (size_t u = 0; u < model->importSourceCount(); ++u) {
            auto import = model->importSource(u);
            idsString += "i=" + std::to_string(u) + import->id();
        }

        for (size_t u = 0; u < model->unitsCount(); ++u) {
            auto units = model->units(u);
            idsString += "U=" + std::to_string(u) + units->id();
            for (size_t i = 0; i < units->unitCount(); ++i) {
                idsString += "u=" + std::to_string(i) + units->unitId(i);
            }
        }

        for (size_t u = 0; u < model->componentCount(); ++u) {
            auto component = model->component(u);
            idsString += "c=" + std::to_string(u) + component->id();
            idsString += "cr=" + std::to_string(u) + component->encapsulationId();
            doUpdateComponentHash(component, idsString);
        }

        std::hash<std::string> hasher;
        hash = hasher(idsString);
    }
    return hash;
}

bool Annotator::hasModel() const
{
    return !mPimpl->mModel.expired();
}

ModelPtr Annotator::model() const
{
    return mPimpl->mModel.lock();
}

void Annotator::AnnotatorImpl::updateHash()
{
    mHash = generateHash();
}

} // namespace libcellml

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
    AnyItem converted = std::make_pair(CellmlElementType::UNDEFINED, nullptr);

    auto type = item.first;
    if ((type == CellmlElementType::COMPONENT)
        || (type == CellmlElementType::COMPONENT_REF)) {
        auto component = std::any_cast<ComponentWeakPtr>(item.second).lock();
        if (component != nullptr) {
            converted.first = item.first;
            converted.second = component;
        }
    } else if ((type == CellmlElementType::CONNECTION)
               || (type == CellmlElementType::MAP_VARIABLES)) {
        // Connection and map variables are not held as weak pointers.
        auto variablePair = std::any_cast<VariablePairPtr>(item.second);
        if (variablePair && variablePair->isValid()) {
            converted.first = item.first;
            converted.second = variablePair;
        }
    } else if ((type == CellmlElementType::ENCAPSULATION)
               || (type == CellmlElementType::MODEL)) {
        auto model = std::any_cast<ModelWeakPtr>(item.second).lock();
        if (model != nullptr) {
            converted.first = item.first;
            converted.second = model;
        }
    } else if (type == CellmlElementType::IMPORT) {
        auto importSource = std::any_cast<ImportSourceWeakPtr>(item.second).lock();
        if (importSource != nullptr) {
            converted.first = item.first;
            converted.second = importSource;
        }
    } else if ((type == CellmlElementType::RESET)
               || (type == CellmlElementType::RESET_VALUE)
               || (type == CellmlElementType::TEST_VALUE)) {
        auto reset = std::any_cast<ResetWeakPtr>(item.second).lock();
        if (reset != nullptr) {
            converted.first = item.first;
            converted.second = reset;
        }
    } else if (type == CellmlElementType::UNIT) {
        // Unit references are not held as weak pointers.
        auto unitItem = std::any_cast<UnitPtr>(item.second);
        if (unitItem != nullptr && unitItem->isValid()) {
            converted.first = item.first;
            converted.second = unitItem;
        }
    } else if (type == CellmlElementType::UNITS) {
        auto units = std::any_cast<UnitsWeakPtr>(item.second).lock();
        if (units != nullptr) {
            converted.first = item.first;
            converted.second = units;
        }
    } else if (type == CellmlElementType::VARIABLE) {
        auto variable = std::any_cast<VariableWeakPtr>(item.second).lock();
        if (variable != nullptr) {
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
    if ((type == CellmlElementType::COMPONENT)
        || (type == CellmlElementType::COMPONENT_REF)) {
        ComponentWeakPtr weakComponent = std::any_cast<ComponentPtr>(item.second);
        converted.second = weakComponent;
    } else if ((type == CellmlElementType::CONNECTION)
               || (type == CellmlElementType::MAP_VARIABLES)) {
        // We don'te store a weak pointer for connections or map variables because the
        // map is the owner of these objects.
        // VariableWeakPair variablePair = std::any_cast<VariablePairPtr>(item.second);
        converted.second = item.second;
    } else if ((type == CellmlElementType::ENCAPSULATION)
               || (type == CellmlElementType::MODEL)) {
        auto model = std::any_cast<ModelPtr>(item.second);
        ModelWeakPtr weakModel = model;
        converted.second = weakModel;
    } else if (type == CellmlElementType::IMPORT) {
        auto importSource = std::any_cast<ImportSourcePtr>(item.second);
        ImportSourceWeakPtr weakImportSource = importSource;
        converted.second = weakImportSource;
    } else if ((type == CellmlElementType::RESET)
               || (type == CellmlElementType::RESET_VALUE)
               || (type == CellmlElementType::TEST_VALUE)) {
        auto reset = std::any_cast<ResetPtr>(item.second);
        ResetWeakPtr weakReset = reset;
        converted.second = weakReset;
    } else if (type == CellmlElementType::UNIT) {
        // We don't store a weak pointer for unit because the map is the owner of the
        // Unit object.
        converted.second = item.second;
    } else if (type == CellmlElementType::UNITS) {
        UnitsWeakPtr weakUnits = std::any_cast<UnitsPtr>(item.second);
        converted.second = weakUnits;
    } else if (type == CellmlElementType::VARIABLE) {
        auto variable = std::any_cast<VariablePtr>(item.second);
        VariableWeakPtr weakVariable = variable;
        converted.second = weakVariable;
    }

    return converted;
}

static const std::map<CellmlElementType, std::string> typeToString = {
    {CellmlElementType::COMPONENT, "component"},
    {CellmlElementType::COMPONENT_REF, "component_ref"},
    {CellmlElementType::CONNECTION, "connection"},
    {CellmlElementType::ENCAPSULATION, "encapsulation"},
    {CellmlElementType::IMPORT, "import"},
    {CellmlElementType::MAP_VARIABLES, "map_variables"},
    {CellmlElementType::MODEL, "model"},
    {CellmlElementType::RESET, "reset"},
    {CellmlElementType::RESET_VALUE, "reset_value"},
    {CellmlElementType::TEST_VALUE, "test_value"},
    {CellmlElementType::UNDEFINED, "undefined"},
    {CellmlElementType::UNIT, "unit"},
    {CellmlElementType::UNITS, "units"},
    {CellmlElementType::VARIABLE, "variable"}};

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

    std::string id(const AnyItem &item);
    std::string setAutoId(const AnyItem &item);
    bool isOwnedByModel(const AnyItem &item) const;
    void removeId(const AnyItem &item, const std::string &id);
    void setId(const AnyItem &item, const std::string &id);
    bool itemsEqual(const AnyItem &itemWeak, const AnyItem &itemShared);
    bool validItem(const AnyItem &item);

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

    bool exists(const std::string &id, size_t index) const;

    size_t generateHash();
    void doUpdateComponentHash(const ComponentPtr &component, std::string &idsString);

    void addIssueNoModel() const;
    void addInvalidArgument(CellmlElementType type) const;
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
        auto entry = convertToWeak(std::make_pair(CellmlElementType::COMPONENT, component));
        idList.insert(std::make_pair(id, entry));
    }
    // Imports.
    ImportSourcePtr importSource = component->importSource();
    if (component->isImport() && (importSource != nullptr)) {
        id = importSource->id();
        if (!id.empty()) {
            auto entry = convertToWeak(std::make_pair(CellmlElementType::IMPORT, importSource));
            idList.insert(std::make_pair(id, entry));
        }
    }
    // Component reference in encapsulation structure.
    id = component->encapsulationId();
    if (!id.empty()) {
        auto entry = convertToWeak(std::make_pair(CellmlElementType::COMPONENT_REF, component));
        idList.insert(std::make_pair(id, entry));
    }
    // Variables.
    for (size_t v = 0; v < component->variableCount(); ++v) {
        VariablePtr variable = component->variable(v);
        VariableWeakPtr weakVariable = variable;
        id = variable->id();
        if (!id.empty()) {
            auto entry = convertToWeak(std::make_pair(CellmlElementType::VARIABLE, variable));
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
                        if (it->second.first == CellmlElementType::MAP_VARIABLES) {
                            auto testPair = std::any_cast<VariablePairPtr>(it->second.second);
                            if (testPair) {
                                VariableWeakPtr varaible1Weak = testPair->variable1();
                                VariableWeakPtr varaible2Weak = testPair->variable2();
                                if (equals(varaible1Weak, weakEquivalentVariable) && equals(varaible2Weak, weakVariable)) {
                                    found = true;
                                }
                            }
                        }
                    }
                }
                if (!found) {
                    auto entry = convertToWeak(std::make_pair(CellmlElementType::MAP_VARIABLES, VariablePair::create(variable, equivalentVariable)));
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
                        if (it->second.first == CellmlElementType::CONNECTION) {
                            auto testPair = std::any_cast<VariablePairPtr>(it->second.second);
                            if (testPair) {
                                if ((owningComponent(testPair->variable1()) == owningComponent(equivalentVariable)) && (owningComponent(testPair->variable2()) == owningComponent(variable))) {
                                    found = true;
                                } else if ((owningComponent(testPair->variable2()) == owningComponent(equivalentVariable)) && (owningComponent(testPair->variable1()) == owningComponent(variable))) {
                                    found = true;
                                }
                            }
                        }
                    }
                }
                if (!found) {
                    auto entry = convertToWeak(std::make_pair(CellmlElementType::CONNECTION, VariablePair::create(variable, equivalentVariable)));
                    idList.insert(std::make_pair(id, entry));
                }
            }
        }
    }
    // Resets.
    for (size_t r = 0; r < component->resetCount(); ++r) {
        ResetPtr reset = component->reset(r);
        id = reset->id();
        if (!id.empty()) {
            auto entry = convertToWeak(std::make_pair(CellmlElementType::RESET, reset));
            idList.insert(std::make_pair(id, entry));
        }
        id = reset->testValueId();
        if (!id.empty()) {
            auto entry = convertToWeak(std::make_pair(CellmlElementType::TEST_VALUE, reset));
            idList.insert(std::make_pair(id, entry));
        }
        id = reset->resetValueId();
        if (!id.empty()) {
            auto entry = convertToWeak(std::make_pair(CellmlElementType::RESET_VALUE, reset));
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
        auto entry = convertToWeak(std::make_pair(CellmlElementType::MODEL, model));
        idList.insert(std::make_pair(id, entry));
    }

    // Units.
    for (size_t u = 0; u < model->unitsCount(); ++u) {
        UnitsPtr units = model->units(u);
        id = units->id();
        if (!id.empty()) {
            auto entry = convertToWeak(std::make_pair(CellmlElementType::UNITS, units));
            idList.insert(std::make_pair(id, entry));
        }
        for (size_t i = 0; i < units->unitCount(); ++i) {
            std::string prefix;
            std::string reference;
            double exponent;
            double multiplier;
            units->unitAttributes(i, reference, prefix, exponent, multiplier, id);
            if (!id.empty()) {
                auto entry = convertToWeak(std::make_pair(CellmlElementType::UNIT, Unit::create(units, i)));
                idList.insert(std::make_pair(id, entry));
            }
        }
        if (units->isImport() && units->importSource() != nullptr) {
            ImportSourcePtr importSource = units->importSource();
            id = importSource->id();
            if (!id.empty()) {
                auto entry = convertToWeak(std::make_pair(CellmlElementType::IMPORT, importSource));
                idList.insert(std::make_pair(id, entry));
            }
        }
    }

    // Components.
    for (size_t c = 0; c < model->componentCount(); ++c) {
        listComponentIdsAndItems(model->component(c), idList);
    }

    // Encapsulation.
    id = model->encapsulationId();
    if (!id.empty()) {
        auto entry = convertToWeak(std::make_pair(CellmlElementType::ENCAPSULATION, model));
        idList.insert(std::make_pair(id, entry));
    }

    return idList;
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
    issue->setReferenceRule(Issue::ReferenceRule::ANNOTATOR_ID_NOT_FOUND);
    mAnnotator->addIssue(issue);
}

void Annotator::AnnotatorImpl::addIssueNonUnique(const std::string &id) const
{
    auto issue = Issue::create();
    issue->setDescription("The id '" + id + "' occurs " + std::to_string(mIdList.count(id)) + " times in the model so a unique item cannot be located.");
    issue->setLevel(Issue::Level::WARNING);
    issue->setReferenceRule(Issue::ReferenceRule::ANNOTATOR_ID_NOT_UNIQUE);
    mAnnotator->addIssue(issue);
}

void Annotator::AnnotatorImpl::addIssueNoModel() const
{
    auto issue = Issue::create();
    issue->setDescription("This Annotator object does not have a model to work with.");
    issue->setLevel(Issue::Level::ERROR);
    issue->setReferenceRule(Issue::ReferenceRule::ANNOTATOR_NO_MODEL);
    mAnnotator->addIssue(issue);
}

void Annotator::AnnotatorImpl::addInvalidArgument(CellmlElementType type) const
{
    auto issue = Issue::create();
    auto description = "The item is internally inconsistent: the enum type '" + cellmlElementTypeAsString(type) + "' cannot be used with the stored item.";
    issue->setDescription(description);
    issue->setLevel(Issue::Level::ERROR);
    issue->setReferenceRule(Issue::ReferenceRule::ANNOTATOR_INCONSISTENT_TYPE);
    mAnnotator->addIssue(issue);
}

bool Annotator::AnnotatorImpl::exists(const std::string &id, size_t index) const
{
    if (!mAnnotator->hasModel()) {
        addIssueNoModel();
        return false;
    }
    if ((mIdList.count(id) <= index) || (mIdList.count(id) == 0)) {
        addIssueNotFound(id);
        return false;
    }
    return true;
}

AnyItem Annotator::item(const std::string &id)
{
    AnyItem retrieved = std::make_pair(CellmlElementType::UNDEFINED, nullptr);
    auto num = itemCount(id);
    if (num == 1) {
        retrieved = item(id, 0);
    } else if (num == 0) {
        mPimpl->addIssueNotFound(id);
    } else {
        mPimpl->addIssueNonUnique(id);
    }
    return retrieved;
}

AnyItem Annotator::item(const std::string &id, size_t index)
{
    return mPimpl->exists(id, index) ? std::move(items(id)[index]) : std::make_pair(CellmlElementType::UNDEFINED, nullptr);
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
        ++next;
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

ComponentPtr Annotator::component(const std::string &id)
{
    if (hasModel()) {
        auto num = itemCount(id);
        if (num == 1) {
            return component(id, 0);
        }
        if (num == 0) {
            mPimpl->addIssueNotFound(id);
        } else {
            mPimpl->addIssueNonUnique(id);
        }
    } else {
        mPimpl->addIssueNoModel();
    }
    return nullptr;
}

VariablePtr Annotator::variable(const std::string &id)
{
    if (hasModel()) {
        auto num = itemCount(id);
        if (num == 1) {
            return variable(id, 0);
        }
        if (num == 0) {
            mPimpl->addIssueNotFound(id);
        } else {
            mPimpl->addIssueNonUnique(id);
        }
    } else {
        mPimpl->addIssueNoModel();
    }
    return nullptr;
}

ModelPtr Annotator::model(const std::string &id)
{
    if (hasModel()) {
        auto num = itemCount(id);
        if (num == 1) {
            return model(id, 0);
        }
        if (num == 0) {
            mPimpl->addIssueNotFound(id);
        } else {
            mPimpl->addIssueNonUnique(id);
        }
    } else {
        mPimpl->addIssueNoModel();
    }
    return nullptr;
}

ModelPtr Annotator::encapsulation(const std::string &id)
{
    if (hasModel()) {
        auto num = itemCount(id);
        if (num == 1) {
            return encapsulation(id, 0);
        }
        if (num == 0) {
            mPimpl->addIssueNotFound(id);
        } else {
            mPimpl->addIssueNonUnique(id);
        }
    } else {
        mPimpl->addIssueNoModel();
    }
    return nullptr;
}

UnitsPtr Annotator::units(const std::string &id)
{
    if (hasModel()) {
        auto num = itemCount(id);
        if (num == 1) {
            return units(id, 0);
        }
        if (num == 0) {
            mPimpl->addIssueNotFound(id);
        } else {
            mPimpl->addIssueNonUnique(id);
        }
    } else {
        mPimpl->addIssueNoModel();
    }
    return nullptr;
}

ImportSourcePtr Annotator::importSource(const std::string &id)
{
    if (hasModel()) {
        auto num = itemCount(id);
        if (num == 1) {
            return importSource(id, 0);
        }
        if (num == 0) {
            mPimpl->addIssueNotFound(id);
        } else {
            mPimpl->addIssueNonUnique(id);
        }
    } else {
        mPimpl->addIssueNoModel();
    }
    return nullptr;
}

ResetPtr Annotator::reset(const std::string &id)
{
    if (hasModel()) {
        auto num = itemCount(id);
        if (num == 1) {
            return reset(id, 0);
        }
        if (num == 0) {
            mPimpl->addIssueNotFound(id);
        } else {
            mPimpl->addIssueNonUnique(id);
        }
    } else {
        mPimpl->addIssueNoModel();
    }
    return nullptr;
}

VariablePairPtr Annotator::connection(const std::string &id)
{
    if (hasModel()) {
        auto num = itemCount(id);
        if (num == 1) {
            return connection(id, 0);
        }
        if (num == 0) {
            mPimpl->addIssueNotFound(id);
        } else {
            mPimpl->addIssueNonUnique(id);
        }
    } else {
        mPimpl->addIssueNoModel();
    }
    return nullptr;
}

VariablePairPtr Annotator::mapVariables(const std::string &id)
{
    if (hasModel()) {
        auto num = itemCount(id);
        if (num == 1) {
            return mapVariables(id, 0);
        }
        if (num == 0) {
            mPimpl->addIssueNotFound(id);
        } else {
            mPimpl->addIssueNonUnique(id);
        }
    } else {
        mPimpl->addIssueNoModel();
    }
    return nullptr;
}

UnitPtr Annotator::unit(const std::string &id)
{
    if (hasModel()) {
        auto num = itemCount(id);
        if (num == 1) {
            return unit(id, 0);
        }
        if (num == 0) {
            mPimpl->addIssueNotFound(id);
        } else {
            mPimpl->addIssueNonUnique(id);
        }
    } else {
        mPimpl->addIssueNoModel();
    }
    return nullptr;
}

ComponentPtr Annotator::componentRef(const std::string &id)
{
    if (hasModel()) {
        auto num = itemCount(id);
        if (num == 1) {
            return componentRef(id, 0);
        }
        if (num == 0) {
            mPimpl->addIssueNotFound(id);
        } else {
            mPimpl->addIssueNonUnique(id);
        }
    } else {
        mPimpl->addIssueNoModel();
    }
    return nullptr;
}

ResetPtr Annotator::testValue(const std::string &id)
{
    if (hasModel()) {
        auto num = itemCount(id);
        if (num == 1) {
            return testValue(id, 0);
        }
        if (num == 0) {
            mPimpl->addIssueNotFound(id);
        } else {
            mPimpl->addIssueNonUnique(id);
        }
    } else {
        mPimpl->addIssueNoModel();
    }
    return nullptr;
}

ResetPtr Annotator::resetValue(const std::string &id)
{
    if (hasModel()) {
        auto num = itemCount(id);
        if (num == 1) {
            return resetValue(id, 0);
        }
        if (num == 0) {
            mPimpl->addIssueNotFound(id);
        } else {
            mPimpl->addIssueNonUnique(id);
        }
    } else {
        mPimpl->addIssueNoModel();
    }
    return nullptr;
}

ComponentPtr Annotator::component(const std::string &id, size_t index)
{
    mPimpl->update();
    if (mPimpl->exists(id, index)) {
        auto i = items(id).at(index);
        try {
            return std::any_cast<ComponentPtr>(i.second);
        } catch (std::bad_any_cast &) {
        }
    }
    return nullptr;
}

ComponentPtr Annotator::componentRef(const std::string &id, size_t index)
{
    return component(id, index);
}

VariablePtr Annotator::variable(const std::string &id, size_t index)
{
    mPimpl->update();
    if (mPimpl->exists(id, index)) {
        auto i = items(id).at(index);
        try {
            return std::any_cast<VariablePtr>(i.second);
        } catch (std::bad_any_cast &) {
        }
    }

    return nullptr;
}

ModelPtr Annotator::model(const std::string &id, size_t index)
{
    mPimpl->update();
    if (mPimpl->exists(id, index)) {
        auto i = items(id).at(index);
        try {
            return std::any_cast<ModelPtr>(i.second);
        } catch (std::bad_any_cast &) {
        }
    }

    return nullptr;
}

ModelPtr Annotator::encapsulation(const std::string &id, size_t index)
{
    return model(id, index);
}

UnitsPtr Annotator::units(const std::string &id, size_t index)
{
    mPimpl->update();
    if (mPimpl->exists(id, index)) {
        auto i = items(id).at(index);
        try {
            return std::any_cast<UnitsPtr>(i.second);
        } catch (std::bad_any_cast &) {
        }
    }
    return nullptr;
}

ImportSourcePtr Annotator::importSource(const std::string &id, size_t index)
{
    mPimpl->update();
    if (mPimpl->exists(id, index)) {
        auto i = items(id).at(index);
        try {
            return std::any_cast<ImportSourcePtr>(i.second);
        } catch (std::bad_any_cast &) {
        }
    }

    return nullptr;
}

ResetPtr Annotator::reset(const std::string &id, size_t index)
{
    mPimpl->update();
    if (mPimpl->exists(id, index)) {
        auto i = items(id).at(index);
        try {
            return std::any_cast<ResetPtr>(i.second);
        } catch (std::bad_any_cast &) {
        }
    }
    return nullptr;
}

ResetPtr Annotator::testValue(const std::string &id, size_t index)
{
    return reset(id, index);
}

ResetPtr Annotator::resetValue(const std::string &id, size_t index)
{
    return reset(id, index);
}

VariablePairPtr Annotator::connection(const std::string &id, size_t index)
{
    mPimpl->update();
    if (mPimpl->exists(id, index)) {
        auto i = items(id).at(index);
        try {
            return std::any_cast<VariablePairPtr>(i.second);
        } catch (std::bad_any_cast &) {
        }
    }

    return nullptr;
}

VariablePairPtr Annotator::mapVariables(const std::string &id, size_t index)
{
    return connection(id, index);
}

UnitPtr Annotator::unit(const std::string &id, size_t index)
{
    mPimpl->update();
    if (mPimpl->exists(id, index)) {
        auto i = items(id).at(index);
        try {
            return std::any_cast<UnitPtr>(i.second);
        } catch (std::bad_any_cast &) {
        }
    }

    return nullptr;
}

void Annotator::clearAllIds()
{
    auto model = mPimpl->mModel.lock();
    if (model != nullptr) {
        model->removeId();
        for (size_t i = 0; i < model->unitsCount(); ++i) {
            auto units = model->units(i);
            units->removeId();
            if (units->isImport()) {
                units->importSource()->removeId();
            }
            for (size_t j = 0; j < units->unitCount(); ++j) {
                units->setUnitId(j, "");
            }
        }
        for (size_t i = 0; i < model->componentCount(); ++i) {
            mPimpl->doClearComponentIds(model->component(i));
        }
        model->removeEncapsulationId();

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
    component->removeEncapsulationId();
    component->removeId();
    if (component->isImport()) {
        component->importSource()->removeId();
    }
    for (size_t i = 0; i < component->variableCount(); ++i) {
        auto variable = component->variable(i);
        variable->removeId();
        for (size_t j = 0; j < variable->equivalentVariableCount(); ++j) {
            Variable::setEquivalenceConnectionId(variable, variable->equivalentVariable(j), "");
            Variable::setEquivalenceMappingId(variable, variable->equivalentVariable(j), "");
        }
    }
    for (size_t i = 0; i < component->resetCount(); ++i) {
        auto reset = component->reset(i);
        reset->removeId();
        reset->removeResetValueId();
        reset->removeTestValueId();
    }
    for (size_t i = 0; i < component->componentCount(); ++i) {
        doClearComponentIds(component->component(i));
    }
}

bool Annotator::assignAllIds()
{
    auto model = mPimpl->mModel.lock();
    if (model != nullptr) {
        mPimpl->doSetAllAutomaticIds();
        return true;
    }
    mPimpl->addIssueNoModel();
    return false;
}

bool Annotator::assignAllIds(ModelPtr &model)
{
    if (model == nullptr) {
        auto issue = Issue::create();
        issue->setDescription("The Model supplied is a nullptr. No action has been taken.");
        issue->setLevel(Issue::Level::ERROR);
        issue->setReferenceRule(Issue::ReferenceRule::ANNOTATOR_NULL_MODEL);
        return false;
    }
    setModel(model);
    return assignAllIds();
}

bool Annotator::assignIds(CellmlElementType type)
{
    auto model = mPimpl->mModel.lock();
    bool changed = false;
    if (model != nullptr) {
        changed = true;
        switch (type) {
        case CellmlElementType::COMPONENT:
            for (size_t index = 0; index < model->componentCount(); ++index) {
                mPimpl->doSetComponentIds(model->component(index));
            }
            break;
        case CellmlElementType::COMPONENT_REF:
            for (size_t index = 0; index < model->componentCount(); ++index) {
                mPimpl->doSetComponentRefIds(model->component(index));
            }
            break;
        case CellmlElementType::CONNECTION:
            for (size_t index = 0; index < model->componentCount(); ++index) {
                mPimpl->doSetConnectionIds(model->component(index));
            }
            break;
        case CellmlElementType::ENCAPSULATION:
            mPimpl->doSetEncapsulationIds();
            break;
        case CellmlElementType::IMPORT:
            mPimpl->doSetImportSourceIds();
            break;
        case CellmlElementType::MAP_VARIABLES:
            for (size_t index = 0; index < model->componentCount(); ++index) {
                mPimpl->doSetMapVariablesIds(model->component(index));
            }
            break;
        case CellmlElementType::MODEL:
            mPimpl->doSetModelIds();
            break;
        case CellmlElementType::RESET:
            for (size_t index = 0; index < model->componentCount(); ++index) {
                mPimpl->doSetResetIds(model->component(index));
            }
            break;
        case CellmlElementType::RESET_VALUE:
            for (size_t index = 0; index < model->componentCount(); ++index) {
                mPimpl->doSetResetValueIds(model->component(index));
            }
            break;
        case CellmlElementType::TEST_VALUE:
            for (size_t index = 0; index < model->componentCount(); ++index) {
                mPimpl->doSetTestValueIds(model->component(index));
            }
            break;
        case CellmlElementType::UNIT:
            mPimpl->doSetUnitIds();
            break;
        case CellmlElementType::UNITS:
            mPimpl->doSetUnitsIds();
            break;
        case CellmlElementType::VARIABLE:
            for (size_t index = 0; index < model->componentCount(); ++index) {
                mPimpl->doSetVariableIds(model->component(index));
            }
            break;
        case CellmlElementType::MATH:
        case CellmlElementType::UNDEFINED:
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
    auto importSources = getAllImportSources(model);
    for (auto &importSource : importSources) {
        if (importSource->id().empty()) {
            auto id = makeUniqueId();
            importSource->setId(id);
            auto entry = convertToWeak(std::make_pair(CellmlElementType::IMPORT, importSource));
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
            auto entry = convertToWeak(std::make_pair(CellmlElementType::UNITS, us));
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
                auto entry = convertToWeak(std::make_pair(CellmlElementType::UNIT, Unit::create(us, i)));
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
        auto entry = convertToWeak(std::make_pair(CellmlElementType::COMPONENT, parent));
        mIdList.insert(std::make_pair(id, entry));
    }
    for (size_t c = 0; c < parent->componentCount(); ++c) {
        if (parent->component(c)->id().empty()) {
            auto id = makeUniqueId();
            parent->component(c)->setId(id);
            auto entry = convertToWeak(std::make_pair(CellmlElementType::COMPONENT, parent->component(c)));
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
            auto entry = convertToWeak(std::make_pair(CellmlElementType::VARIABLE, parent->variable(v)));
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
            auto entry = convertToWeak(std::make_pair(CellmlElementType::RESET, parent->reset(r)));
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
            auto entry = convertToWeak(std::make_pair(CellmlElementType::RESET_VALUE, parent->reset(r)));
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
            auto entry = convertToWeak(std::make_pair(CellmlElementType::TEST_VALUE, parent->reset(r)));
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
                auto v1v2 = VariablePair::create(v1, v2);
                auto entry = convertToWeak(std::make_pair(CellmlElementType::CONNECTION, v1v2));
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
                auto v1v2 = VariablePair::create(v1, v2);
                auto entry = convertToWeak(std::make_pair(CellmlElementType::MAP_VARIABLES, v1v2));
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
        auto entry = convertToWeak(std::make_pair(CellmlElementType::COMPONENT_REF, parent));
        mIdList.insert(std::make_pair(id, entry));
    }
    for (size_t c = 0; c < parent->componentCount(); ++c) {
        if (parent->component(c)->encapsulationId().empty()) {
            auto id = makeUniqueId();
            parent->component(c)->setEncapsulationId(id);
            auto entry = convertToWeak(std::make_pair(CellmlElementType::COMPONENT_REF, parent->component(c)));
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
        auto entry = convertToWeak(std::make_pair(CellmlElementType::ENCAPSULATION, model));
        mIdList.insert(std::make_pair(id, entry));
    }
}

void Annotator::AnnotatorImpl::doSetModelIds()
{
    auto model = mModel.lock();
    if (model->id().empty()) {
        auto id = makeUniqueId();
        model->setId(id);
        auto entry = convertToWeak(std::make_pair(CellmlElementType::MODEL, model));
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

std::string Annotator::AnnotatorImpl::id(const AnyItem &item)
{
    std::string id;
    CellmlElementType type = item.first;
    if (type == CellmlElementType::UNIT) {
        auto unitItem = std::any_cast<UnitPtr>(item.second);
        id = unitItem->units()->unitId(unitItem->index());
    } else if (type == CellmlElementType::MODEL) {
        id = std::any_cast<ModelPtr>(item.second)->id();
    } else if (type == CellmlElementType::RESET) {
        id = std::any_cast<ResetPtr>(item.second)->id();
    } else if (type == CellmlElementType::UNITS) {
        id = std::any_cast<UnitsPtr>(item.second)->id();
    } else if (type == CellmlElementType::IMPORT) {
        id = std::any_cast<ImportSourcePtr>(item.second)->id();
    } else if (type == CellmlElementType::VARIABLE) {
        id = std::any_cast<VariablePtr>(item.second)->id();
    } else if (type == CellmlElementType::COMPONENT) {
        id = std::any_cast<ComponentPtr>(item.second)->id();
    } else if (type == CellmlElementType::CONNECTION) {
        auto variablePair = std::any_cast<VariablePairPtr>(item.second);
        id = Variable::equivalenceConnectionId(variablePair->variable1(), variablePair->variable2());
    } else if (type == CellmlElementType::TEST_VALUE) {
        id = std::any_cast<ResetPtr>(item.second)->testValueId();
    } else if (type == CellmlElementType::RESET_VALUE) {
        id = std::any_cast<ResetPtr>(item.second)->resetValueId();
    } else if (type == CellmlElementType::COMPONENT_REF) {
        id = std::any_cast<ComponentPtr>(item.second)->encapsulationId();
    } else if (type == CellmlElementType::ENCAPSULATION) {
        id = std::any_cast<ModelPtr>(item.second)->encapsulationId();
    } else if (type == CellmlElementType::MAP_VARIABLES) {
        auto variablePair = std::any_cast<VariablePairPtr>(item.second);
        id = Variable::equivalenceMappingId(variablePair->variable1(), variablePair->variable2());
    }
    return id;
}

void Annotator::AnnotatorImpl::setId(const AnyItem &item, const std::string &id)
{
    CellmlElementType type = item.first;
    if (type == CellmlElementType::UNIT) {
        auto unitItem = std::any_cast<UnitPtr>(item.second);
        unitItem->units()->setUnitId(unitItem->index(), id);
    } else if (type == CellmlElementType::MODEL) {
        std::any_cast<ModelPtr>(item.second)->setId(id);
    } else if (type == CellmlElementType::RESET) {
        std::any_cast<ResetPtr>(item.second)->setId(id);
    } else if (type == CellmlElementType::UNITS) {
        std::any_cast<UnitsPtr>(item.second)->setId(id);
    } else if (type == CellmlElementType::IMPORT) {
        std::any_cast<ImportSourcePtr>(item.second)->setId(id);
    } else if (type == CellmlElementType::VARIABLE) {
        std::any_cast<VariablePtr>(item.second)->setId(id);
    } else if (type == CellmlElementType::COMPONENT) {
        std::any_cast<ComponentPtr>(item.second)->setId(id);
    } else if (type == CellmlElementType::CONNECTION) {
        auto variablePair = std::any_cast<VariablePairPtr>(item.second);
        Variable::setEquivalenceConnectionId(variablePair->variable1(), variablePair->variable2(), id);
    } else if (type == CellmlElementType::TEST_VALUE) {
        std::any_cast<ResetPtr>(item.second)->setTestValueId(id);
    } else if (type == CellmlElementType::RESET_VALUE) {
        std::any_cast<ResetPtr>(item.second)->setResetValueId(id);
    } else if (type == CellmlElementType::COMPONENT_REF) {
        std::any_cast<ComponentPtr>(item.second)->setEncapsulationId(id);
    } else if (type == CellmlElementType::ENCAPSULATION) {
        std::any_cast<ModelPtr>(item.second)->setEncapsulationId(id);
    } else if (type == CellmlElementType::MAP_VARIABLES) {
        auto variablePair = std::any_cast<VariablePairPtr>(item.second);
        Variable::setEquivalenceMappingId(variablePair->variable1(), variablePair->variable2(), id);
    }
}

bool Annotator::AnnotatorImpl::isOwnedByModel(const AnyItem &item) const
{
    bool modelBased = false;
    CellmlElementType type = item.first;
    auto model = mModel.lock();
    if (type == CellmlElementType::UNIT) {
        modelBased = owningModel(std::any_cast<UnitPtr>(item.second)->units()) == model;
    } else if ((type == CellmlElementType::MODEL)
               || (type == CellmlElementType::ENCAPSULATION)) {
        modelBased = std::any_cast<ModelPtr>(item.second) == model;
    } else if ((type == CellmlElementType::RESET)
               || (type == CellmlElementType::TEST_VALUE)
               || (type == CellmlElementType::RESET_VALUE)) {
        modelBased = owningModel(std::any_cast<ResetPtr>(item.second)) == model;
    } else if (type == CellmlElementType::UNITS) {
        modelBased = owningModel(std::any_cast<UnitsPtr>(item.second)) == model;
    } else if (type == CellmlElementType::IMPORT) {
        modelBased = true;
    } else if (type == CellmlElementType::VARIABLE) {
        modelBased = owningModel(std::any_cast<VariablePtr>(item.second)) == model;
    } else if ((type == CellmlElementType::COMPONENT)
               || (type == CellmlElementType::COMPONENT_REF)) {
        modelBased = owningModel(std::any_cast<ComponentPtr>(item.second)) == model;
    } else if ((type == CellmlElementType::CONNECTION)
               || (type == CellmlElementType::MAP_VARIABLES)) {
        auto variablePair = std::any_cast<VariablePairPtr>(item.second);
        modelBased = owningModel(variablePair->variable1()) == model && owningModel(variablePair->variable2()) == model;
    }
    return modelBased;
}

bool Annotator::AnnotatorImpl::itemsEqual(const AnyItem &itemWeak, const AnyItem &itemShared)
{
    bool itemsEqual = false;
    auto item = convertToWeak(itemShared);
    CellmlElementType type = itemWeak.first;
    if (type == CellmlElementType::UNIT) {
        // Unit is not actually stored as a weak pointer so we can compare shared pointers directly.
        itemsEqual = (std::any_cast<UnitPtr>(itemWeak.second) == std::any_cast<UnitPtr>(itemShared.second));
    } else if ((type == CellmlElementType::MODEL)
               || (type == CellmlElementType::ENCAPSULATION)) {
        itemsEqual = equals(std::any_cast<ModelWeakPtr>(itemWeak.second), std::any_cast<ModelWeakPtr>(item.second));
    } else if ((type == CellmlElementType::RESET)
               || (type == CellmlElementType::TEST_VALUE)
               || (type == CellmlElementType::RESET_VALUE)) {
        itemsEqual = equals(std::any_cast<ResetWeakPtr>(itemWeak.second), std::any_cast<ResetWeakPtr>(item.second));
    } else if (type == CellmlElementType::UNITS) {
        itemsEqual = equals(std::any_cast<UnitsWeakPtr>(itemWeak.second), std::any_cast<UnitsWeakPtr>(item.second));
    } else if (type == CellmlElementType::IMPORT) {
        itemsEqual = equals(std::any_cast<ImportSourceWeakPtr>(itemWeak.second), std::any_cast<ImportSourceWeakPtr>(item.second));
    } else if (type == CellmlElementType::VARIABLE) {
        itemsEqual = equals(std::any_cast<VariableWeakPtr>(itemWeak.second), std::any_cast<VariableWeakPtr>(item.second));
    } else if ((type == CellmlElementType::COMPONENT)
               || (type == CellmlElementType::COMPONENT_REF)) {
        itemsEqual = equals(std::any_cast<ComponentWeakPtr>(itemWeak.second), std::any_cast<ComponentWeakPtr>(item.second));
    } else if ((type == CellmlElementType::CONNECTION)
               || (type == CellmlElementType::MAP_VARIABLES)) {
        // Variable pairs are not stored as a weak pointer so we can compare shared pointers directly.
        auto pair1 = std::any_cast<VariablePairPtr>(itemWeak.second);
        auto pair2 = std::any_cast<VariablePairPtr>(item.second);
        itemsEqual = pair1 == pair2;
    }
    return itemsEqual;
}

bool Annotator::AnnotatorImpl::validItem(const AnyItem &item)
{
    CellmlElementType type = item.first;
    if (type == CellmlElementType::UNIT) {
        try {
            if (std::any_cast<UnitPtr>(item.second)->units() != nullptr) {
                return true;
            }
        } catch (std::bad_any_cast &) {
            return false;
        }
    } else if ((type == CellmlElementType::MODEL)
               || (type == CellmlElementType::ENCAPSULATION)) {
        try {
            if (std::any_cast<ModelPtr>(item.second) != nullptr) {
                return true;
            }
        } catch (std::bad_any_cast &) {
            return false;
        }
    } else if ((type == CellmlElementType::RESET)
               || (type == CellmlElementType::TEST_VALUE)
               || (type == CellmlElementType::RESET_VALUE)) {
        try {
            if (std::any_cast<ResetPtr>(item.second) != nullptr) {
                return true;
            }
        } catch (std::bad_any_cast &) {
            return false;
        }
    } else if (type == CellmlElementType::UNITS) {
        try {
            if (std::any_cast<UnitsPtr>(item.second) != nullptr) {
                return true;
            }
        } catch (std::bad_any_cast &) {
            return false;
        }
    } else if (type == CellmlElementType::IMPORT) {
        try {
            if (std::any_cast<ImportSourcePtr>(item.second) != nullptr) {
                return true;
            }
        } catch (std::bad_any_cast &) {
            return false;
        }
    } else if (type == CellmlElementType::VARIABLE) {
        try {
            if (std::any_cast<VariablePtr>(item.second) != nullptr) {
                return true;
            }
        } catch (std::bad_any_cast &) {
            return false;
        }
    } else if ((type == CellmlElementType::COMPONENT)
               || (type == CellmlElementType::COMPONENT_REF)) {
        try {
            if (std::any_cast<ComponentPtr>(item.second) != nullptr) {
                return true;
            }
        } catch (std::bad_any_cast &) {
            return false;
        }
    } else if ((type == CellmlElementType::CONNECTION)
               || (type == CellmlElementType::MAP_VARIABLES)) {
        try {
            auto pair = std::any_cast<VariablePairPtr>(item.second);
            if ((pair->variable1() != nullptr) && (pair->variable2() != nullptr)) {
                return true;
            }
        } catch (std::bad_any_cast &) {
            return false;
        }
    }
    return false;
}

void Annotator::AnnotatorImpl::removeId(const AnyItem &item, const std::string &id)
{
    auto range = mIdList.equal_range(id);
    for (auto it = range.first; it != range.second; ++it) {
        if ((it->second.first == item.first) && itemsEqual(it->second, item)) {
            mIdList.erase(it);
            break;
        }
    }
}

std::string Annotator::AnnotatorImpl::setAutoId(const AnyItem &item)
{
    std::string newId;
    if (validItem(item)) {
        if (mModel.lock() != nullptr) {
            auto oldId = id(item);

            if (!isOwnedByModel(item)) {
                return newId;
            }

            update();
            newId = makeUniqueId();

            if (!oldId.empty()) {
                removeId(item, oldId);
            }

            setId(item, newId);
            mIdList.insert(std::make_pair(newId, convertToWeak(item)));
        } else {
            addIssueNoModel();
        }
    } else {
        addInvalidArgument(item.first);
    }
    return newId;
}

std::string Annotator::assignComponentId(const ComponentPtr &component)
{
    return mPimpl->setAutoId(std::make_pair(CellmlElementType::COMPONENT, component));
}

std::string Annotator::assignComponentRefId(const ComponentPtr &component)
{
    return mPimpl->setAutoId(std::make_pair(CellmlElementType::COMPONENT_REF, component));
}

std::string Annotator::assignConnectionId(const VariablePairPtr &variablePair)
{
    return mPimpl->setAutoId(std::make_pair(CellmlElementType::CONNECTION, variablePair));
}

std::string Annotator::assignMapVariablesId(const VariablePairPtr &variablePair)
{
    return mPimpl->setAutoId(std::make_pair(CellmlElementType::MAP_VARIABLES, variablePair));
}

std::string Annotator::assignModelId(const ModelPtr &model)
{
    return mPimpl->setAutoId(std::make_pair(CellmlElementType::MODEL, model));
}

std::string Annotator::assignEncapsulationId(const ModelPtr &model)
{
    return mPimpl->setAutoId(std::make_pair(CellmlElementType::ENCAPSULATION, model));
}

std::string Annotator::assignImportSourceId(const ImportSourcePtr &importSource)
{
    return mPimpl->setAutoId(std::make_pair(CellmlElementType::IMPORT, importSource));
}

std::string Annotator::assignResetId(const ResetPtr &reset)
{
    return mPimpl->setAutoId(std::make_pair(CellmlElementType::RESET, reset));
}

std::string Annotator::assignResetValueId(const ResetPtr &reset)
{
    return mPimpl->setAutoId(std::make_pair(CellmlElementType::RESET_VALUE, reset));
}

std::string Annotator::assignTestValueId(const ResetPtr &reset)
{
    return mPimpl->setAutoId(std::make_pair(CellmlElementType::TEST_VALUE, reset));
}

std::string Annotator::assignUnitId(const UnitPtr &unitItem)
{
    return mPimpl->setAutoId(std::make_pair(CellmlElementType::UNIT, unitItem));
}

std::string Annotator::assignUnitsId(const UnitsPtr &units)
{
    return mPimpl->setAutoId(std::make_pair(CellmlElementType::UNITS, units));
}

std::string Annotator::assignVariableId(const VariablePtr &variable)
{
    return mPimpl->setAutoId(std::make_pair(CellmlElementType::VARIABLE, variable));
}

std::string Annotator::assignId(const AnyItem &item)
{
    return mPimpl->setAutoId(item);
}

std::string Annotator::assignId(const ModelPtr &model, CellmlElementType type)
{
    return mPimpl->setAutoId(std::make_pair(type, model));
}

std::string Annotator::assignId(const ComponentPtr &component, CellmlElementType type)
{
    return mPimpl->setAutoId(std::make_pair(type, component));
}

std::string Annotator::assignId(const ResetPtr &reset, CellmlElementType type)
{
    return mPimpl->setAutoId(std::make_pair(type, reset));
}

std::string Annotator::assignId(const UnitsPtr &units)
{
    return mPimpl->setAutoId(std::make_pair(CellmlElementType::UNITS, units));
}

std::string Annotator::assignId(const ImportSourcePtr &importSource)
{
    return mPimpl->setAutoId(std::make_pair(CellmlElementType::IMPORT, importSource));
}

std::string Annotator::assignId(const UnitsPtr &units, size_t index)
{
    return mPimpl->setAutoId(std::make_pair(CellmlElementType::UNIT, Unit::create(units, index)));
}

std::string Annotator::assignId(const UnitPtr &unitItem)
{
    return mPimpl->setAutoId(std::make_pair(CellmlElementType::UNIT, unitItem));
}

std::string Annotator::assignId(const VariablePtr &variable)
{
    return mPimpl->setAutoId(std::make_pair(CellmlElementType::VARIABLE, variable));
}

std::string Annotator::assignId(const VariablePairPtr &pair, CellmlElementType type)
{
    return mPimpl->setAutoId(std::make_pair(type, pair));
}

std::string Annotator::assignId(const VariablePtr &variable1, const VariablePtr &variable2, CellmlElementType type)
{
    return mPimpl->setAutoId(std::make_pair(type, VariablePair::create(variable1, variable2)));
}

size_t Annotator::itemCount(const std::string &id)
{
    return mPimpl->mIdList.count(id);
}

void Annotator::AnnotatorImpl::doUpdateComponentHash(const ComponentPtr &component, std::string &idsString)
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
    if (model != nullptr) {
        std::string idsString;
        size_t i;
        idsString += "m=" + model->id() + "me=" + model->encapsulationId();

        auto importSources = getAllImportSources(model);
        i = 0;
        for (auto &importSource : importSources) {
            idsString += "i=" + std::to_string(++i) + importSource->id();
        }

        for (i = 0; i < model->unitsCount(); ++i) {
            auto units = model->units(i);
            idsString += "U=" + std::to_string(i) + units->id();
            for (size_t j = 0; j < units->unitCount(); ++j) {
                idsString += "u=" + std::to_string(j) + units->unitId(j);
            }
        }

        for (i = 0; i < model->componentCount(); ++i) {
            auto component = model->component(i);
            idsString += "c=" + std::to_string(i) + component->id();
            idsString += "cr=" + std::to_string(i) + component->encapsulationId();
            doUpdateComponentHash(component, idsString);
        }

        hash = std::hash<std::string> {}(idsString);
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

} // namespace libcellml

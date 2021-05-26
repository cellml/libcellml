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

#include "anycellmlelement_p.h"
#include "internaltypes.h"
#include "issue_p.h"
#include "namespaces.h"
#include "utilities.h"

namespace libcellml {

size_t realIndex(size_t index)
{
    return index == std::numeric_limits<size_t>::max() ? size_t(0) : index;
}

using ItemList = std::multimap<std::string, AnyCellmlElementPtr>;

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

    AnyCellmlElementPtr convertToWeak(const AnyCellmlElementPtr &item);
    AnyCellmlElementPtr convertToShared(const AnyCellmlElementPtr &item);

    void listComponentIdsAndItems(const ComponentPtr &component, ItemList &idList);
    ItemList listIdsAndItems(const ModelPtr &model);

    void update();
    void buildIdList();

    std::string makeUniqueId();

    std::string id(const AnyCellmlElementPtr &item);
    std::string setAutoId(const AnyCellmlElementPtr &item);
    bool isOwnedByModel(const AnyCellmlElementPtr &item) const;
    void removeId(const AnyCellmlElementPtr &item, const std::string &id);
    void setId(const AnyCellmlElementPtr &item, const std::string &id);
    bool itemsEqual(const AnyCellmlElementPtr &itemWeak, const AnyCellmlElementPtr &itemShared);
    bool validItem(const AnyCellmlElementPtr &item);

    void doSetAllAutomaticIds();
    void doSetModelIds();
    void doSetImportSourceIds();
    void doSetUnitsIds();
    void doSetUnitsItemIds();
    void doSetComponentIds(const ComponentPtr &parent);
    void doSetVariableIds(const ComponentPtr &parent);
    void doSetResetIds(const ComponentPtr &parent);
    void doSetResetValueIds(const ComponentPtr &parent);
    void doSetTestValueIds(const ComponentPtr &parent);
    void doSetEncapsulationIds();
    void doSetConnectionIds(const ComponentPtr &parent);
    void doSetMapVariablesIds(const ComponentPtr &parent);
    void doSetComponentEncapsulationIds(const ComponentPtr &parent);
    void doClearComponentIds(const ComponentPtr &component);

    /**
     * @brief Test to determine if the given @p id at the given @p index exists.
     *
     * Test to determine if the given @p id at the given @p index exists.  Returns @c true
     * if the item does exist at the @p index and @c false otherwise.
     *
     * Logs the following errors (if encountered):
     *  - missing model,
     *  - no id; or
     *  - duplicate ids.
     *
     * @param id A @c std::string representing the @p id to retrieve.
     * @param index The index of the item with @p id.
     *
     * @return @c true if the @p id exists at @p index, @c false otherwise.
     */
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
    mPimpl->mIdList = std::multimap<std::string, AnyCellmlElementPtr>();
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

void Annotator::AnnotatorImpl::listComponentIdsAndItems(const ComponentPtr &component, ItemList &idList)
{
    std::string id = component->id();
    if (!id.empty()) {
        auto entry = AnyCellmlElement::AnyCellmlElementImpl::create();
        entry->mPimpl->setComponent(component);
        idList.insert(std::make_pair(id, convertToWeak(entry)));
    }
    // Imports.
    ImportSourcePtr importSource = component->importSource();
    if (component->isImport() && (importSource != nullptr)) {
        id = importSource->id();
        if (!id.empty()) {
            auto entry = AnyCellmlElement::AnyCellmlElementImpl::create();
            entry->mPimpl->setImportSource(importSource);
            idList.insert(std::make_pair(id, convertToWeak(entry)));
        }
    }
    // Component reference in encapsulation structure.
    id = component->encapsulationId();
    if (!id.empty()) {
        auto entry = AnyCellmlElement::AnyCellmlElementImpl::create();
        entry->mPimpl->setComponentRef(component);
        idList.insert(std::make_pair(id, convertToWeak(entry)));
    }
    // Variables.
    for (size_t v = 0; v < component->variableCount(); ++v) {
        VariablePtr variable = component->variable(v);
        VariableWeakPtr weakVariable = variable;
        id = variable->id();
        if (!id.empty()) {
            auto entry = AnyCellmlElement::AnyCellmlElementImpl::create();
            entry->mPimpl->setVariable(variable);
            idList.insert(std::make_pair(id, convertToWeak(entry)));
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
                    // Get the range of items with this identifier:
                    auto rangePair = idList.equal_range(id);
                    for (auto it = rangePair.first; it != rangePair.second; ++it) {
                        // Make sure it's also a MAP_VARIABLES item.
                        if (it->second->type() == CellmlElementType::MAP_VARIABLES) {
                            auto testPair = it->second->variablePair();
                            if (testPair) {
                                VariableWeakPtr variable1Weak = testPair->variable1();
                                VariableWeakPtr variable2Weak = testPair->variable2();
                                if (equals(variable1Weak, weakEquivalentVariable) && equals(variable2Weak, weakVariable)) {
                                    found = true;
                                }
                            }
                        }
                    }
                }
                if (!found) {
                    auto entry = AnyCellmlElement::AnyCellmlElementImpl::create();
                    entry->mPimpl->setMapVariables(variable, equivalentVariable);
                    idList.insert(std::make_pair(id, convertToWeak(entry)));
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
                    // Get the range of items with this identifier:
                    auto rangePair = idList.equal_range(id);
                    for (auto it = rangePair.first; it != rangePair.second; ++it) {
                        // Make sure it's also a CONNECTION item.
                        if (it->second->type() == CellmlElementType::CONNECTION) {
                            auto testPair = it->second->variablePair();
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
                    auto entry = AnyCellmlElement::AnyCellmlElementImpl::create();
                    entry->mPimpl->setConnection(variable, equivalentVariable);
                    idList.insert(std::make_pair(id, convertToWeak(entry)));
                }
            }
        }
    }
    // Resets.
    for (size_t r = 0; r < component->resetCount(); ++r) {
        ResetPtr reset = component->reset(r);
        id = reset->id();
        if (!id.empty()) {
            auto entry = AnyCellmlElement::AnyCellmlElementImpl::create();
            entry->mPimpl->setReset(reset);
            idList.insert(std::make_pair(id, convertToWeak(entry)));
        }
        id = reset->testValueId();
        if (!id.empty()) {
            auto entry = AnyCellmlElement::AnyCellmlElementImpl::create();
            entry->mPimpl->setTestValue(reset);
            idList.insert(std::make_pair(id, convertToWeak(entry)));
        }
        id = reset->resetValueId();
        if (!id.empty()) {
            auto entry = AnyCellmlElement::AnyCellmlElementImpl::create();
            entry->mPimpl->setResetValue(reset);
            idList.insert(std::make_pair(id, convertToWeak(entry)));
        }
    }

    for (size_t c = 0; c < component->componentCount(); ++c) {
        listComponentIdsAndItems(component->component(c), idList);
    }
}

ItemList Annotator::AnnotatorImpl::listIdsAndItems(const ModelPtr &model)
{
    // Collect all existing identifiers in a list and return.
    //    auto model = weakModel.lock();
    ItemList idList;
    // Model.
    std::string id = model->id();
    if (!id.empty()) {
        auto entry = AnyCellmlElement::AnyCellmlElementImpl::create();
        entry->mPimpl->setModel(model);
        idList.insert(std::make_pair(id, convertToWeak(entry)));
    }

    // Units.
    for (size_t u = 0; u < model->unitsCount(); ++u) {
        UnitsPtr units = model->units(u);
        id = units->id();
        if (!id.empty()) {
            auto entry = AnyCellmlElement::AnyCellmlElementImpl::create();
            entry->mPimpl->setUnits(units);
            idList.insert(std::make_pair(id, convertToWeak(entry)));
        }
        for (size_t i = 0; i < units->unitCount(); ++i) {
            std::string prefix;
            std::string reference;
            double exponent;
            double multiplier;
            units->unitAttributes(i, reference, prefix, exponent, multiplier, id);
            if (!id.empty()) {
                auto entry = AnyCellmlElement::AnyCellmlElementImpl::create();
                entry->mPimpl->setUnitsItem(UnitsItem::create(units, i));
                idList.insert(std::make_pair(id, convertToWeak(entry)));
            }
        }
        if (units->isImport() && units->importSource() != nullptr) {
            ImportSourcePtr importSource = units->importSource();
            id = importSource->id();
            if (!id.empty()) {
                auto entry = AnyCellmlElement::AnyCellmlElementImpl::create();
                entry->mPimpl->setImportSource(importSource);
                idList.insert(std::make_pair(id, convertToWeak(entry)));
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
        auto entry = AnyCellmlElement::AnyCellmlElementImpl::create();
        entry->mPimpl->setEncapsulation(model);
        idList.insert(std::make_pair(id, convertToWeak(entry)));
    }

    return idList;
}

AnyCellmlElementPtr Annotator::AnnotatorImpl::convertToWeak(const AnyCellmlElementPtr &item)
{
    auto converted = AnyCellmlElement::AnyCellmlElementImpl::create();
    auto type = item->type();

    converted->mPimpl->mType = type;

    if ((type == CellmlElementType::COMPONENT)
        || (type == CellmlElementType::COMPONENT_REF)) {
        ComponentWeakPtr weakComponent = item->component();
        converted->mPimpl->mItem = weakComponent;
    } else if ((type == CellmlElementType::CONNECTION)
               || (type == CellmlElementType::MAP_VARIABLES)) {
        // We don't store a weak pointer for connections / map variables because
        // the map is the owner of the VariablePair object.
        converted->mPimpl->mItem = item->variablePair();
    } else if ((type == CellmlElementType::ENCAPSULATION)
               || (type == CellmlElementType::MODEL)) {
        ModelWeakPtr weakModel = item->model();
        converted->mPimpl->mItem = weakModel;
    } else if (type == CellmlElementType::IMPORT) {
        ImportSourceWeakPtr weakImportSource = item->importSource();
        converted->mPimpl->mItem = weakImportSource;
    } else if ((type == CellmlElementType::RESET)
               || (type == CellmlElementType::RESET_VALUE)
               || (type == CellmlElementType::TEST_VALUE)) {
        ResetWeakPtr weakReset = item->reset();
        converted->mPimpl->mItem = weakReset;
    } else if (type == CellmlElementType::UNIT) {
        // We don't store a weak pointer for units item because the map is the
        // owner of the UnitsItem object.
        converted->mPimpl->mItem = item->unitsItem();
    } else if (type == CellmlElementType::UNITS) {
        UnitsWeakPtr weakUnits = item->units();
        converted->mPimpl->mItem = weakUnits;
    } else if (type == CellmlElementType::VARIABLE) {
        VariableWeakPtr weakVariable = item->variable();
        converted->mPimpl->mItem = weakVariable;
    }

    return converted;
}

AnyCellmlElementPtr Annotator::AnnotatorImpl::convertToShared(const AnyCellmlElementPtr &item)
{
    auto converted = AnyCellmlElement::AnyCellmlElementImpl::create();
    auto type = item->type();

    if ((type == CellmlElementType::COMPONENT)
        || (type == CellmlElementType::COMPONENT_REF)) {
        auto component = std::any_cast<ComponentWeakPtr>(item->mPimpl->mItem).lock();
        if (component != nullptr) {
            converted->mPimpl->setComponent(component, type);
        }
    } else if ((type == CellmlElementType::CONNECTION)
               || (type == CellmlElementType::MAP_VARIABLES)) {
        // Connections and map variables are not held as weak pointers.
        auto variablePair = item->variablePair();
        if ((variablePair != nullptr) && variablePair->isValid()) {
            converted->mPimpl->setVariablePair(variablePair, type);
        }
    } else if ((type == CellmlElementType::ENCAPSULATION)
               || (type == CellmlElementType::MODEL)) {
        auto model = std::any_cast<ModelWeakPtr>(item->mPimpl->mItem).lock();
        if (model != nullptr) {
            converted->mPimpl->setModel(model, type);
        }
    } else if (type == CellmlElementType::IMPORT) {
        auto importSource = std::any_cast<ImportSourceWeakPtr>(item->mPimpl->mItem).lock();
        if (importSource != nullptr) {
            converted->mPimpl->setImportSource(importSource);
        }
    } else if (type == CellmlElementType::RESET) {
        auto reset = std::any_cast<ResetWeakPtr>(item->mPimpl->mItem).lock();
        if (reset != nullptr) {
            converted->mPimpl->setReset(reset);
        }
    } else if (type == CellmlElementType::RESET_VALUE) {
        auto reset = std::any_cast<ResetWeakPtr>(item->mPimpl->mItem).lock();
        if (reset != nullptr) {
            converted->mPimpl->setResetValue(reset);
        }
    } else if (type == CellmlElementType::TEST_VALUE) {
        auto reset = std::any_cast<ResetWeakPtr>(item->mPimpl->mItem).lock();
        if (reset != nullptr) {
            converted->mPimpl->setTestValue(reset);
        }
    } else if (type == CellmlElementType::UNIT) {
        // Unit items are not held as weak pointers.
        auto unitsItem = item->unitsItem();
        if ((unitsItem != nullptr) && unitsItem->isValid()) {
            converted->mPimpl->setUnitsItem(unitsItem);
        }
    } else if (type == CellmlElementType::UNITS) {
        auto units = std::any_cast<UnitsWeakPtr>(item->mPimpl->mItem).lock();
        if (units != nullptr) {
            converted->mPimpl->setUnits(units);
        }
    } else if (type == CellmlElementType::VARIABLE) {
        auto variable = std::any_cast<VariableWeakPtr>(item->mPimpl->mItem).lock();
        if (variable != nullptr) {
            converted->mPimpl->setVariable(variable);
        }
    }

    return converted;
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
    auto issue = Issue::IssueImpl::create();
    issue->mPimpl->setDescription("Could not find an item with an identifier of '" + id + "' in the model.");
    issue->mPimpl->setLevel(Issue::Level::WARNING);
    issue->mPimpl->setReferenceRule(Issue::ReferenceRule::ANNOTATOR_ID_NOT_FOUND);
    mAnnotator->addIssue(issue);
}

void Annotator::AnnotatorImpl::addIssueNonUnique(const std::string &id) const
{
    auto issue = Issue::IssueImpl::create();
    issue->mPimpl->setDescription("The identifier '" + id + "' occurs " + std::to_string(mIdList.count(id)) + " times in the model so a unique item cannot be located.");
    issue->mPimpl->setLevel(Issue::Level::WARNING);
    issue->mPimpl->setReferenceRule(Issue::ReferenceRule::ANNOTATOR_ID_NOT_UNIQUE);
    mAnnotator->addIssue(issue);
}

void Annotator::AnnotatorImpl::addIssueNoModel() const
{
    auto issue = Issue::IssueImpl::create();
    issue->mPimpl->setDescription("This Annotator object does not have a model to work with.");
    issue->mPimpl->setReferenceRule(Issue::ReferenceRule::ANNOTATOR_NO_MODEL);
    mAnnotator->addIssue(issue);
}

void Annotator::AnnotatorImpl::addInvalidArgument(CellmlElementType type) const
{
    auto issue = Issue::IssueImpl::create();
    auto description = "The item is internally inconsistent: the enum type '" + cellmlElementTypeAsString(type) + "' cannot be used with the stored item.";
    issue->mPimpl->setDescription(description);
    issue->mPimpl->setReferenceRule(Issue::ReferenceRule::ANNOTATOR_INCONSISTENT_TYPE);
    mAnnotator->addIssue(issue);
}

bool Annotator::AnnotatorImpl::exists(const std::string &id, size_t index) const
{
    if (!mAnnotator->hasModel()) {
        addIssueNoModel();
        return false;
    }


    auto count = mAnnotator->itemCount(id);
    if (count == 1) {
        return true;
    }
    if (index == std::numeric_limits<size_t>::max()) {
        index = 0;
        if (count > 1) {
            addIssueNonUnique(id);
        }
    }
    if (count <= index) {
        addIssueNotFound(id);
        return false;
    }

    return true;
}

AnyCellmlElementPtr Annotator::item(const std::string &id, size_t index)
{
    auto privateIndex = realIndex(index);
    return mPimpl->exists(id, index) ? std::move(items(id)[privateIndex]) : AnyCellmlElement::AnyCellmlElementImpl::create();
}

bool Annotator::isUnique(const std::string &id)
{
    return mPimpl->mIdList.count(id) == 1;
}

std::vector<AnyCellmlElementPtr> Annotator::items(const std::string &id)
{
    mPimpl->update();
    std::vector<AnyCellmlElementPtr> items;
    auto range = mPimpl->mIdList.equal_range(id);
    for (auto it = range.first; it != range.second; ++it) {
        items.push_back(mPimpl->convertToShared(it->second));
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

ComponentPtr Annotator::component(const std::string &id, size_t index)
{
    mPimpl->update();
    if (mPimpl->exists(id, index)) {
        auto privateIndex = realIndex(index);
        auto i = items(id).at(privateIndex);
        return i->component();
    }
    return nullptr;
}

VariablePtr Annotator::variable(const std::string &id, size_t index)
{
    mPimpl->update();
    if (mPimpl->exists(id, index)) {
        auto privateIndex = realIndex(index);
        auto i = items(id).at(privateIndex);
        return i->variable();
    }
    return nullptr;
}

ModelPtr Annotator::model(const std::string &id, size_t index)
{
    mPimpl->update();
    if (mPimpl->exists(id, index)) {
        auto privateIndex = realIndex(index);
        auto i = items(id).at(privateIndex);
        return i->model();
    }
    return nullptr;
}

ModelPtr Annotator::encapsulation(const std::string &id, size_t index)
{
    mPimpl->update();
    if (mPimpl->exists(id, index)) {
        auto privateIndex = realIndex(index);
        auto i = items(id).at(privateIndex);
        return i->model();
    }
    return nullptr;
}

ComponentPtr Annotator::componentEncapsulation(const std::string &id, size_t index)
{
    mPimpl->update();
    if (mPimpl->exists(id, index)) {
        auto privateIndex = realIndex(index);
        auto i = items(id).at(privateIndex);
        return i->component();
    }
    return nullptr;
}

UnitsPtr Annotator::units(const std::string &id, size_t index)
{
    mPimpl->update();
    if (mPimpl->exists(id, index)) {
        auto privateIndex = realIndex(index);
        auto i = items(id).at(privateIndex);
        return i->units();
    }
    return nullptr;
}

ImportSourcePtr Annotator::importSource(const std::string &id, size_t index)
{
    mPimpl->update();
    if (mPimpl->exists(id, index)) {
        auto privateIndex = realIndex(index);
        auto i = items(id).at(privateIndex);
        return i->importSource();
    }
    return nullptr;
}

ResetPtr Annotator::reset(const std::string &id, size_t index)
{
    mPimpl->update();
    if (mPimpl->exists(id, index)) {
        auto privateIndex = realIndex(index);
        auto i = items(id).at(privateIndex);
        return i->reset();
    }
    return nullptr;
}

ResetPtr Annotator::testValue(const std::string &id, size_t index)
{
    mPimpl->update();
    if (mPimpl->exists(id, index)) {
        auto privateIndex = realIndex(index);
        auto i = items(id).at(privateIndex);
        return i->reset();
    }
    return nullptr;
}

ResetPtr Annotator::resetValue(const std::string &id, size_t index)
{
    mPimpl->update();
    if (mPimpl->exists(id, index)) {
        auto privateIndex = realIndex(index);
        auto i = items(id).at(privateIndex);
        return i->reset();
    }
    return nullptr;
}

VariablePairPtr Annotator::mapVariables(const std::string &id, size_t index)
{
    mPimpl->update();
    if (mPimpl->exists(id, index)) {
        auto privateIndex = realIndex(index);
        auto i = items(id).at(privateIndex);
        return i->variablePair();
    }
    return nullptr;
}

VariablePairPtr Annotator::connection(const std::string &id, size_t index)
{
    mPimpl->update();
    if (mPimpl->exists(id, index)) {
        auto privateIndex = realIndex(index);
        auto i = items(id).at(privateIndex);
        return i->variablePair();
    }
    return nullptr;
}

UnitsItemPtr Annotator::unitsItem(const std::string &id, size_t index)
{
    mPimpl->update();
    if (mPimpl->exists(id, index)) {
        auto privateIndex = realIndex(index);
        auto i = items(id).at(privateIndex);
        return i->unitsItem();
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
        auto issue = Issue::IssueImpl::create();
        issue->mPimpl->setDescription("The Model supplied is a nullptr. No action has been taken.");
        issue->mPimpl->setReferenceRule(Issue::ReferenceRule::ANNOTATOR_NULL_MODEL);
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
                mPimpl->doSetComponentEncapsulationIds(model->component(index));
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
            mPimpl->doSetUnitsItemIds();
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
            auto entry = AnyCellmlElement::AnyCellmlElementImpl::create();
            entry->mPimpl->setImportSource(importSource);
            mIdList.insert(std::make_pair(id, convertToWeak(entry)));
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
            auto entry = AnyCellmlElement::AnyCellmlElementImpl::create();
            entry->mPimpl->setUnits(us);
            mIdList.insert(std::make_pair(id, convertToWeak(entry)));
        }
    }
}

void Annotator::AnnotatorImpl::doSetUnitsItemIds()
{
    auto model = mModel.lock();
    for (size_t u = 0; u < model->unitsCount(); ++u) {
        auto us = model->units(u);
        for (size_t i = 0; i < us->unitCount(); i++) {
            if (us->unitId(i).empty()) {
                auto id = makeUniqueId();
                us->setUnitId(i, id);
                auto entry = AnyCellmlElement::AnyCellmlElementImpl::create();
                entry->mPimpl->setUnitsItem(UnitsItem::create(us, i));
                mIdList.insert(std::make_pair(id, convertToWeak(entry)));
            }
        }
    }
}

void Annotator::AnnotatorImpl::doSetComponentIds(const ComponentPtr &parent)
{
    if (parent->id().empty()) {
        auto id = makeUniqueId();
        parent->setId(id);
        auto entry = AnyCellmlElement::AnyCellmlElementImpl::create();
        entry->mPimpl->setComponent(parent);
        mIdList.insert(std::make_pair(id, convertToWeak(entry)));
    }
    for (size_t c = 0; c < parent->componentCount(); ++c) {
        if (parent->component(c)->id().empty()) {
            auto id = makeUniqueId();
            parent->component(c)->setId(id);
            auto entry = AnyCellmlElement::AnyCellmlElementImpl::create();
            entry->mPimpl->setComponent(parent->component(c));
            mIdList.insert(std::make_pair(id, convertToWeak(entry)));
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
            auto entry = AnyCellmlElement::AnyCellmlElementImpl::create();
            entry->mPimpl->setVariable(parent->variable(v));
            mIdList.insert(std::make_pair(id, convertToWeak(entry)));
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
            auto entry = AnyCellmlElement::AnyCellmlElementImpl::create();
            entry->mPimpl->setReset(parent->reset(r));
            mIdList.insert(std::make_pair(id, convertToWeak(entry)));
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
            auto entry = AnyCellmlElement::AnyCellmlElementImpl::create();
            entry->mPimpl->setResetValue(parent->reset(r));
            mIdList.insert(std::make_pair(id, convertToWeak(entry)));
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
            auto entry = AnyCellmlElement::AnyCellmlElementImpl::create();
            entry->mPimpl->setTestValue(parent->reset(r));
            mIdList.insert(std::make_pair(id, convertToWeak(entry)));
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
                auto entry = AnyCellmlElement::AnyCellmlElementImpl::create();
                entry->mPimpl->setConnection(v1, v2);
                mIdList.insert(std::make_pair(id, convertToWeak(entry)));
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
                auto entry = AnyCellmlElement::AnyCellmlElementImpl::create();
                entry->mPimpl->setMapVariables(v1, v2);
                mIdList.insert(std::make_pair(id, convertToWeak(entry)));
            }
        }
    }
    for (size_t c = 0; c < parent->componentCount(); ++c) {
        doSetMapVariablesIds(parent->component(c));
    }
}

void Annotator::AnnotatorImpl::doSetComponentEncapsulationIds(const ComponentPtr &parent)
{
    if (parent->encapsulationId().empty() && parent->componentCount() > 0) {
        auto id = makeUniqueId();
        parent->setEncapsulationId(id);
        auto entry = AnyCellmlElement::AnyCellmlElementImpl::create();
        entry->mPimpl->setComponentRef(parent);
        mIdList.insert(std::make_pair(id, convertToWeak(entry)));
    }
    for (size_t c = 0; c < parent->componentCount(); ++c) {
        if (parent->component(c)->encapsulationId().empty()) {
            auto id = makeUniqueId();
            parent->component(c)->setEncapsulationId(id);
            auto entry = AnyCellmlElement::AnyCellmlElementImpl::create();
            entry->mPimpl->setComponentRef(parent->component(c));
            mIdList.insert(std::make_pair(id, convertToWeak(entry)));
        }
        doSetComponentEncapsulationIds(parent->component(c));
    }
}

void Annotator::AnnotatorImpl::doSetEncapsulationIds()
{
    auto model = mModel.lock();
    if (model->encapsulationId().empty()) {
        auto id = makeUniqueId();
        model->setEncapsulationId(id);
        auto entry = AnyCellmlElement::AnyCellmlElementImpl::create();
        entry->mPimpl->setEncapsulation(model);
        mIdList.insert(std::make_pair(id, convertToWeak(entry)));
    }
}

void Annotator::AnnotatorImpl::doSetModelIds()
{
    auto model = mModel.lock();
    if (model->id().empty()) {
        auto id = makeUniqueId();
        model->setId(id);
        auto entry = AnyCellmlElement::AnyCellmlElementImpl::create();
        entry->mPimpl->setModel(model);
        mIdList.insert(std::make_pair(id, convertToWeak(entry)));
    }
}

void Annotator::AnnotatorImpl::doSetAllAutomaticIds()
{
    doSetModelIds();
    doSetImportSourceIds();
    doSetUnitsIds();
    doSetUnitsItemIds();
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
        doSetComponentEncapsulationIds(component);
    }
    doSetEncapsulationIds();
}

std::string Annotator::AnnotatorImpl::makeUniqueId()
{
    // Because the hexadecimal counter starts high enough that it will always have a letter as the first character,
    // we don't need to prefix it with any other string to be valid.  This is stored in the mCounter variable
    // so that "holes" in the automatic identifier list are not filled; they will always build from the previous
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
    // Note: this is only as unique as the information in mIdList permits.  That array must be updated
    // outside this function.
    return id;
}

std::string Annotator::AnnotatorImpl::id(const AnyCellmlElementPtr &item)
{
    std::string id;
    CellmlElementType type = item->type();
    if (type == CellmlElementType::COMPONENT) {
        id = item->component()->id();
    } else if (type == CellmlElementType::COMPONENT_REF) {
        id = item->component()->encapsulationId();
    } else if (type == CellmlElementType::CONNECTION) {
        auto variablePair = item->variablePair();
        id = Variable::equivalenceConnectionId(variablePair->variable1(), variablePair->variable2());
    } else if (type == CellmlElementType::ENCAPSULATION) {
        id = item->model()->encapsulationId();
    } else if (type == CellmlElementType::IMPORT) {
        id = item->importSource()->id();
    } else if (type == CellmlElementType::MAP_VARIABLES) {
        auto variablePair = item->variablePair();
        id = Variable::equivalenceMappingId(variablePair->variable1(), variablePair->variable2());
    } else if (type == CellmlElementType::MODEL) {
        id = item->model()->id();
    } else if (type == CellmlElementType::RESET) {
        id = item->reset()->id();
    } else if (type == CellmlElementType::RESET_VALUE) {
        id = item->reset()->resetValueId();
    } else if (type == CellmlElementType::TEST_VALUE) {
        id = item->reset()->testValueId();
    } else if (type == CellmlElementType::UNIT) {
        auto unitItem = item->unitsItem();
        id = unitItem->units()->unitId(unitItem->index());
    } else if (type == CellmlElementType::UNITS) {
        id = item->units()->id();
    } else if (type == CellmlElementType::VARIABLE) {
        id = item->variable()->id();
    }
    return id;
}

void Annotator::AnnotatorImpl::setId(const AnyCellmlElementPtr &item, const std::string &id)
{
    CellmlElementType type = item->type();
    if (type == CellmlElementType::COMPONENT) {
        item->component()->setId(id);
    } else if (type == CellmlElementType::COMPONENT_REF) {
        item->component()->setEncapsulationId(id);
    } else if (type == CellmlElementType::CONNECTION) {
        auto variablePair = item->variablePair();
        Variable::setEquivalenceConnectionId(variablePair->variable1(), variablePair->variable2(), id);
    } else if (type == CellmlElementType::ENCAPSULATION) {
        item->model()->setEncapsulationId(id);
    } else if (type == CellmlElementType::IMPORT) {
        item->importSource()->setId(id);
    } else if (type == CellmlElementType::MAP_VARIABLES) {
        auto variablePair = item->variablePair();
        Variable::setEquivalenceMappingId(variablePair->variable1(), variablePair->variable2(), id);
    } else if (type == CellmlElementType::MODEL) {
        item->model()->setId(id);
    } else if (type == CellmlElementType::RESET) {
        item->reset()->setId(id);
    } else if (type == CellmlElementType::RESET_VALUE) {
        item->reset()->setResetValueId(id);
    } else if (type == CellmlElementType::TEST_VALUE) {
        item->reset()->setTestValueId(id);
    } else if (type == CellmlElementType::UNIT) {
        auto unitsItem = item->unitsItem();
        unitsItem->units()->setUnitId(unitsItem->index(), id);
    } else if (type == CellmlElementType::UNITS) {
        item->units()->setId(id);
    } else if (type == CellmlElementType::VARIABLE) {
        item->variable()->setId(id);
    }
}

bool Annotator::AnnotatorImpl::isOwnedByModel(const AnyCellmlElementPtr &item) const
{
    bool modelBased = false;
    CellmlElementType type = item->type();
    auto model = mModel.lock();
    if ((type == CellmlElementType::COMPONENT)
        || (type == CellmlElementType::COMPONENT_REF)) {
        modelBased = owningModel(item->component()) == model;
    } else if ((type == CellmlElementType::CONNECTION)
               || (type == CellmlElementType::MAP_VARIABLES)) {
        auto variablePair = item->variablePair();
        modelBased = (owningModel(variablePair->variable1()) == model)
                     && (owningModel(variablePair->variable2()) == model);
    } else if ((type == CellmlElementType::ENCAPSULATION)
               || (type == CellmlElementType::MODEL)) {
        modelBased = item->model() == model;
    } else if (type == CellmlElementType::IMPORT) {
        modelBased = true;
    } else if (type == CellmlElementType::RESET) {
        modelBased = owningModel(item->reset()) == model;
    } else if (type == CellmlElementType::RESET_VALUE) {
        modelBased = owningModel(item->reset()) == model;
    } else if (type == CellmlElementType::TEST_VALUE) {
        modelBased = owningModel(item->reset()) == model;
    } else if (type == CellmlElementType::UNIT) {
        modelBased = owningModel(item->unitsItem()->units()) == model;
    } else if (type == CellmlElementType::UNITS) {
        modelBased = owningModel(item->units()) == model;
    } else if (type == CellmlElementType::VARIABLE) {
        modelBased = owningModel(item->variable()) == model;
    }
    return modelBased;
}

bool Annotator::AnnotatorImpl::itemsEqual(const AnyCellmlElementPtr &itemWeak, const AnyCellmlElementPtr &itemShared)
{
    bool itemsEqual = false;
    auto item = convertToWeak(itemShared);
    CellmlElementType type = itemWeak->type();
    if ((type == CellmlElementType::COMPONENT)
        || (type == CellmlElementType::COMPONENT_REF)) {
        itemsEqual = equals(std::any_cast<ComponentWeakPtr>(itemWeak->mPimpl->mItem),
                            std::any_cast<ComponentWeakPtr>(item->mPimpl->mItem));
    } else if ((type == CellmlElementType::CONNECTION)
               || (type == CellmlElementType::MAP_VARIABLES)) {
        // Connections and map variables are not stored as a weak pointer so we can compare
        // shared pointers directly.
        itemsEqual = itemWeak->variablePair() == item->variablePair();
    } else if ((type == CellmlElementType::ENCAPSULATION)
               || (type == CellmlElementType::MODEL)) {
        itemsEqual = equals(std::any_cast<ModelWeakPtr>(itemWeak->mPimpl->mItem),
                            std::any_cast<ModelWeakPtr>(item->mPimpl->mItem));
    } else if (type == CellmlElementType::IMPORT) {
        itemsEqual = equals(std::any_cast<ImportSourceWeakPtr>(itemWeak->mPimpl->mItem),
                            std::any_cast<ImportSourceWeakPtr>(item->mPimpl->mItem));
    } else if ((type == CellmlElementType::RESET)
               || (type == CellmlElementType::RESET_VALUE)
               || (type == CellmlElementType::TEST_VALUE)) {
        itemsEqual = equals(std::any_cast<ResetWeakPtr>(itemWeak->mPimpl->mItem),
                            std::any_cast<ResetWeakPtr>(item->mPimpl->mItem));
    } else if (type == CellmlElementType::UNIT) {
        // Unit is not actually stored as a weak pointer so we can compare shared pointers directly.
        itemsEqual = itemWeak->unitsItem() == itemShared->unitsItem();
    } else if (type == CellmlElementType::UNITS) {
        itemsEqual = equals(std::any_cast<UnitsWeakPtr>(itemWeak->mPimpl->mItem),
                            std::any_cast<UnitsWeakPtr>(item->mPimpl->mItem));
    } else if (type == CellmlElementType::VARIABLE) {
        itemsEqual = equals(std::any_cast<VariableWeakPtr>(itemWeak->mPimpl->mItem),
                            std::any_cast<VariableWeakPtr>(item->mPimpl->mItem));
    }
    return itemsEqual;
}

bool Annotator::AnnotatorImpl::validItem(const AnyCellmlElementPtr &item)
{
    CellmlElementType type = item->type();
    if ((type == CellmlElementType::COMPONENT)
        || (type == CellmlElementType::COMPONENT_REF)) {
        if (item->component() != nullptr) {
            return true;
        }
    } else if ((type == CellmlElementType::CONNECTION)
               || (type == CellmlElementType::MAP_VARIABLES)) {
        auto variablePair = item->variablePair();
        if ((variablePair != nullptr)
            && (variablePair->variable1() != nullptr)
            && (variablePair->variable2() != nullptr)) {
            return true;
        }
    } else if ((type == CellmlElementType::ENCAPSULATION)
               || (type == CellmlElementType::MODEL)) {
        if (item->model() != nullptr) {
            return true;
        }
    } else if (type == CellmlElementType::IMPORT) {
        if (item->importSource() != nullptr) {
            return true;
        }
    } else if (type == CellmlElementType::RESET) {
        if (item->reset() != nullptr) {
            return true;
        }
    } else if (type == CellmlElementType::RESET_VALUE) {
        if (item->reset() != nullptr) {
            return true;
        }
    } else if (type == CellmlElementType::TEST_VALUE) {
        if (item->reset() != nullptr) {
            return true;
        }
    } else if (type == CellmlElementType::UNIT) {
        auto unitsItem = item->unitsItem();
        if ((unitsItem != nullptr) && (unitsItem->units() != nullptr)) {
            return true;
        }
    } else if (type == CellmlElementType::UNITS) {
        if (item->units() != nullptr) {
            return true;
        }
    } else if (type == CellmlElementType::VARIABLE) {
        if (item->variable() != nullptr) {
            return true;
        }
    }
    return false;
}

void Annotator::AnnotatorImpl::removeId(const AnyCellmlElementPtr &item, const std::string &id)
{
    auto range = mIdList.equal_range(id);
    for (auto it = range.first; it != range.second; ++it) {
        if ((it->second->type() == item->type()) && itemsEqual(it->second, item)) {
            mIdList.erase(it);
            break;
        }
    }
}

std::string Annotator::AnnotatorImpl::setAutoId(const AnyCellmlElementPtr &item)
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
        addInvalidArgument(item->type());
    }
    return newId;
}

std::string Annotator::assignId(const ModelPtr &model, CellmlElementType type)
{
    auto entry = AnyCellmlElement::AnyCellmlElementImpl::create();
    entry->mPimpl->setModel(model, type);
    return mPimpl->setAutoId(entry);
}

std::string Annotator::assignId(const ComponentPtr &component, CellmlElementType type)
{
    auto entry = AnyCellmlElement::AnyCellmlElementImpl::create();
    entry->mPimpl->setComponent(component, type);
    return mPimpl->setAutoId(entry);
}

std::string Annotator::assignId(const ResetPtr &reset, CellmlElementType type)
{
    auto entry = AnyCellmlElement::AnyCellmlElementImpl::create();
    entry->mPimpl->setReset(reset, type);
    return mPimpl->setAutoId(entry);
}

std::string Annotator::assignId(const ImportSourcePtr &importSource)
{
    auto entry = AnyCellmlElement::AnyCellmlElementImpl::create();
    entry->mPimpl->setImportSource(importSource);
    return mPimpl->setAutoId(entry);
}

std::string Annotator::assignId(const UnitsPtr &units)
{
    auto entry = AnyCellmlElement::AnyCellmlElementImpl::create();
    entry->mPimpl->setUnits(units);
    return mPimpl->setAutoId(entry);
}

std::string Annotator::assignId(const UnitsPtr &units, size_t index)
{
    auto entry = AnyCellmlElement::AnyCellmlElementImpl::create();
    entry->mPimpl->setUnitsItem(UnitsItem::create(units, index));
    return mPimpl->setAutoId(entry);
}

std::string Annotator::assignId(const UnitsItemPtr &unitsItem)
{
    auto entry = AnyCellmlElement::AnyCellmlElementImpl::create();
    entry->mPimpl->setUnitsItem(unitsItem);
    return mPimpl->setAutoId(entry);
}

std::string Annotator::assignId(const VariablePtr &variable)
{
    auto entry = AnyCellmlElement::AnyCellmlElementImpl::create();
    entry->mPimpl->setVariable(variable);
    return mPimpl->setAutoId(entry);
}

std::string Annotator::assignId(const VariablePairPtr &pair, CellmlElementType type)
{
    auto entry = AnyCellmlElement::AnyCellmlElementImpl::create();
    entry->mPimpl->setVariablePair(pair, type);
    return mPimpl->setAutoId(entry);
}

std::string Annotator::assignId(const VariablePtr &variable1, const VariablePtr &variable2, CellmlElementType type)
{
    auto entry = AnyCellmlElement::AnyCellmlElementImpl::create();
    entry->mPimpl->setVariablePair(variable1, variable2, type);
    return mPimpl->setAutoId(entry);
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

    // Note that MathML identifiers are not yet included.

    for (size_t i = 0; i < component->componentCount(); ++i) {
        auto child = component->component(i);
        idsString += "c=" + std::to_string(i) + child->id() + "ce=" + child->encapsulationId();
        doUpdateComponentHash(child, idsString);
    }
}

size_t Annotator::AnnotatorImpl::generateHash()
{
    // Serialise the stored model into a (very) simplified string of identifier-based items, and create a hash.
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

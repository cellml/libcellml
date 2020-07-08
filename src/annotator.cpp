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
        idList.insert(std::make_pair(id, std::make_pair(0, component)));
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
        auto issue = libcellml::Issue::create();
        issue->setDescription("The id map is empty; the supplied model has no id attributes.");
        issue->setLevel(libcellml::Issue::Level::ERROR);
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

// ComponentPtr Annotator::component(const std::string &id)
// {
//     auto i = item(id);
//     try {
//         auto j = std::any_cast<ComponentPtr>(i.second);
//         return j;
//     } catch (std::bad_any_cast &e) {
//         (void)e;
//         return nullptr;
//     }
// }

// VariablePtr Annotator::variable(const std::string &id)
// {
//     auto i = item(id);
//     try {
//         auto j = std::any_cast<VariablePtr>(i.second);
//         return j;
//     } catch (std::bad_any_cast &e) {
//         (void)e;
//         return nullptr;
//     }
// }

// ModelPtr Annotator::model(const std::string &id)
// {
//     auto i = item(id);
//     try {
//         auto j = std::any_cast<ModelPtr>(i.second);
//         return j;
//     } catch (std::bad_any_cast &e) {
//         (void)e;
//         return nullptr;
//     }
// }

// UnitsPtr Annotator::units(const std::string &id)
// {
//     auto i = item(id);
//     try {
//         auto j = std::any_cast<UnitsPtr>(i.second);
//         return j;
//     } catch (std::bad_any_cast &e) {
//         (void)e;
//         return nullptr;
//     }
// }

// ImportSourcePtr Annotator::import(const std::string &id)
// {
//     auto i = item(id);
//     try {
//         auto j = std::any_cast<ImportSourcePtr>(i.second);
//         return j;
//     } catch (std::bad_any_cast &e) {
//         (void)e;
//         return nullptr;
//     }
// }

// ResetPtr Annotator::reset(const std::string &id)
// {
//     auto i = item(id);
//     try {
//         auto j = std::any_cast<ResetPtr>(i.second);
//         return j;
//     } catch (std::bad_any_cast &e) {
//         (void)e;
//         return nullptr;
//     }
// }

// VariablePair Annotator::connection(const std::string &id)
// {
//     auto i = item(id);
//     try {
//         auto j = std::any_cast<VariablePair>(i.second);
//         return j;
//     } catch (std::bad_any_cast &e) {
//         (void)e;
//         return std::make_pair(nullptr, nullptr);
//     }
// }

// VariablePair Annotator::map_variables(const std::string &id)
// {
//     auto i = item(id);
//     try {
//         auto j = std::any_cast<VariablePair>(i.second);
//         return j;
//     } catch (std::bad_any_cast &e) {
//         (void)e;
//         return std::make_pair(nullptr, nullptr);
//     }
// }

// UnitItem Annotator::unit(const std::string &id)
// {
//     auto i = item(id);
//     try {
//         auto j = std::any_cast<UnitItem>(i.second);
//         return j;
//     } catch (std::bad_any_cast &e) {
//         (void)e;
//         return std::make_pair(nullptr, -1);
//     }
// }

// ComponentPtr Annotator::component_ref(const std::string &id)
// {
//     auto i = item(id);
//     try {
//         auto j = std::any_cast<ComponentPtr>(i.second);
//         return j;
//     } catch (std::bad_any_cast &e) {
//         (void)e;
//         return nullptr;
//     }
// }

// std::string Annotator::math(const std::string &id)
// {
//     auto i = item(id);
//     try {
//         auto j = std::any_cast<std::string>(i.second);
//         return j;
//     } catch (std::bad_any_cast &e) {
//         (void)e;
//         return "";
//     }
// }

// std::string Annotator::test_value(const std::string &id)
// {
//     auto i = item(id);
//     try {
//         auto j = std::any_cast<std::string>(i.second);
//         return j;
//     } catch (std::bad_any_cast &e) {
//         (void)e;
//         return "";
//     }
// }

// std::string Annotator::reset_value(const std::string &id)
// {
//     auto i = item(id);
//     try {
//         auto j = std::any_cast<std::string>(i.second);
//         return j;
//     } catch (std::bad_any_cast &e) {
//         (void)e;
//         return "";
//     }
// }

int componentIndex(const ModelPtr &model, const ComponentPtr &component)
{
    if (model == nullptr) {
        return -1;
    }
    for (size_t i = 0; i < model->componentCount(); ++i) {
        if (model->component(i) == component) {
            return static_cast<int>(i);
        }
    }
    return -1;
}

int componentIndex(const ComponentPtr &parent, const ComponentPtr &component)
{
    if (parent == nullptr) {
        return -1;
    }
    for (size_t i = 0; i < parent->componentCount(); ++i) {
        if (parent->component(i) == component) {
            return static_cast<int>(i);
        }
    }
    return -1;
}

int variableIndex(const ComponentPtr &component, const VariablePtr &variable)
{
    if (component == nullptr) {
        return -1;
    }
    for (size_t i = 0; i < component->variableCount(); ++i) {
        if (component->variable(i) == variable) {
            return static_cast<int>(i);
        }
    }
    return -1;
}

int equivalentVariableIndex(const VariablePtr &variable1, const VariablePtr &variable2)
{
    if (variable1 == nullptr) {
        return -1;
    }
    for (size_t i = 0; i < variable1->equivalentVariableCount(); ++i) {
        if (variable1->equivalentVariable(i) == variable2) {
            return static_cast<int>(i);
        }
    }
    return -1;
}

int resetIndex(const ComponentPtr &component, const ResetPtr &reset)
{
    if (component == nullptr) {
        return -1;
    }
    for (size_t i = 0; i < component->resetCount(); ++i) {
        if (component->reset(i) == reset) {
            return static_cast<int>(i);
        }
    }
    return -1;
}

int unitsIndex(const ModelPtr &model, const UnitsPtr &units)
{
    if (model == nullptr) {
        return -1;
    }
    for (size_t i = 0; i < model->unitsCount(); ++i) {
        if (model->units(i) == units) {
            return static_cast<int>(i);
        }
    }
    return -1;
}

int issueIndex(const Annotator *annotator, const IssuePtr &issue)
{
    if (annotator == nullptr) {
        return -1;
    }
    for (size_t i = 0; i < annotator->issueCount(); ++i) {
        if (annotator->issue(i) == issue) {
            return static_cast<int>(i);
        }
    }
    return -1;
}

void traceComponentAncestry(const ModelPtr &model, const ComponentPtr &component, std::vector<size_t> &indexList);
void traceComponentIndices(const ModelPtr &model, const ComponentPtr &component, std::vector<size_t> &indexList);

void traceComponentAncestry(const ModelPtr &model, const ComponentPtr &component, std::vector<size_t> &indexList)
{
    auto parent = owningComponent(component);
    int index = componentIndex(parent, component);
    if (index < 0) {
        traceComponentAncestry(model, parent, indexList);
    } else {
        indexList.push_back(static_cast<size_t>(index));
        // Now have to go the other way ...
    }
}

void traceVariableIndices(const ModelPtr &model, const VariablePtr &variable, std::vector<size_t> &indexList)
{
    auto component = owningComponent(variable);
    auto index = variableIndex(component, variable);
    if (index >= 0) {
        indexList.push_back(static_cast<size_t>(index));
        traceComponentIndices(model, component, indexList);
    } else {
        std::vector<size_t>().swap(indexList);
    }
}

void traceResetIndices(const ModelPtr &model, const ResetPtr &reset, std::vector<size_t> &indexList)
{
    auto component = owningComponent(reset);
    if (owningModel(component) != model) {
        // Error:
        std::vector<size_t>().swap(indexList);
        return;
    }

    auto index = resetIndex(component, reset);
    if (index < 0) {
        // Error: reset not found in this component, messed up parentage
        std::vector<size_t>().swap(indexList);
        return;
    }

    indexList.push_back(static_cast<size_t>(index));
    traceComponentIndices(model, component, indexList);
}

void traceUnitsIndices(const ModelPtr &model, const UnitsPtr &units, std::vector<size_t> &indexList)
{
    int index = unitsIndex(model, units);
    if (index >= 0) {
        indexList.push_back(static_cast<size_t>(index));
    } else {
        std::vector<size_t>().swap(indexList);
    }
}

void traceUnitIndices(const ModelPtr &model, const UnitItem &units, std::vector<size_t> &indexList)
{
    indexList.push_back(units.second);
    int index = unitsIndex(model, units.first);
    if (index >= 0) {
        indexList.push_back(static_cast<size_t>(index));
    } else {
        std::vector<size_t>().swap(indexList);
    }
}

void traceMapVariablesIndices(const ModelPtr &model, const VariablePair &p, std::vector<size_t> &indexList)
{
    traceVariableIndices(model, p.first, indexList);
    int index = equivalentVariableIndex(p.first, p.second);
    if (index >= 0) {
        indexList.push_back(static_cast<size_t>(index));
    } else {
        std::vector<size_t>().swap(indexList);
    }
}

void traceComponentIndices(const ModelPtr &model, const ComponentPtr &component, std::vector<size_t> &indexList)
{
    ComponentPtr c;
    if (!model->containsComponent(component, true)) {
        // Component does not exist in model anywhere, return empty list.
        std::vector<size_t>().swap(indexList);
        return;
    }
    c = component;
    do {
        auto p = c->parent();
        if (p == model) {
            auto index = componentIndex(model, c);
            indexList.push_back(static_cast<size_t>(index));
            c = nullptr;
        } else {
            auto index = componentIndex(owningComponent(c), c);
            indexList.push_back(static_cast<size_t>(index));
            c = owningComponent(c);
        }
    } while (c != nullptr);
}

std::pair<Annotator::Type, std::vector<size_t>> Annotator::indicesToItem(const std::string &id)
{
    std::pair<Annotator::Type, std::vector<size_t>> recipe;
    std::vector<size_t> indexList;
    AnyItem item = mPimpl->mAnnotator->item(id);

    // Construct the recipe for finding this item in the real world outside this function ...
    switch (item.first) {
    case Annotator::Type::MODEL:
    case Annotator::Type::IMPORT: // TODO: not sure how to best describe imports?? Skipping at the moment until #652 is resolved.
    case Annotator::Type::ENCAPSULATION:
        recipe.first = static_cast<Annotator::Type>(item.first);
        break;
    case Annotator::Type::COMPONENT:
    case Annotator::Type::COMPONENT_REF:
        recipe.first = static_cast<Annotator::Type>(item.first);
        traceComponentIndices(mPimpl->mModel, std::any_cast<ComponentPtr>(item.second), recipe.second);
        std::reverse(recipe.second.begin(), recipe.second.end());
        break;
    case Annotator::Type::VARIABLE:
        recipe.first = static_cast<Annotator::Type>(item.first);
        traceVariableIndices(mPimpl->mModel, std::any_cast<VariablePtr>(item.second), recipe.second);
        std::reverse(recipe.second.begin(), recipe.second.end());
        break;
    case Annotator::Type::RESET:
    case Annotator::Type::RESET_VALUE:
    case Annotator::Type::TEST_VALUE:
        recipe.first = static_cast<Annotator::Type>(item.first);
        traceResetIndices(mPimpl->mModel, std::any_cast<ResetPtr>(item.second), recipe.second);
        std::reverse(recipe.second.begin(), recipe.second.end());
        break;
    case Annotator::Type::UNITS:
        recipe.first = static_cast<Annotator::Type>(item.first);
        traceUnitsIndices(mPimpl->mModel, std::any_cast<UnitsPtr>(item.second), recipe.second);
        std::reverse(recipe.second.begin(), recipe.second.end());
        break;
    case Annotator::Type::UNIT:
        recipe.first = static_cast<Annotator::Type>(item.first);
        traceUnitIndices(mPimpl->mModel, std::any_cast<UnitItem>(item.second), recipe.second);
        std::reverse(recipe.second.begin(), recipe.second.end());
        break;
    case Annotator::Type::MAP_VARIABLES:
    case Annotator::Type::CONNECTION:
        recipe.first = static_cast<Annotator::Type>(item.first);
        traceMapVariablesIndices(mPimpl->mModel, std::any_cast<VariablePair>(item.second), recipe.second);
        std::reverse(recipe.second.begin(), recipe.second.end());
        break;
    case Annotator::Type::ISSUE:
        recipe.first = static_cast<Annotator::Type>(item.first);
        recipe.second = std::vector<size_t>();
        int index = issueIndex(mPimpl->mAnnotator, std::any_cast<IssuePtr>(item.second));
        if (index >= 0) {
            recipe.second.push_back(static_cast<size_t>(index));
        }
        break;
    }
    return recipe;
}

std::string Annotator::instructions(const std::string &id)
{
    size_t index;
    std::string instructions;
    std::vector<size_t> indexList;
    AnyItem item = mPimpl->mAnnotator->item(id);

    switch (item.first) {
    case Annotator::Type::MODEL:
        instructions = "Model";
        break;

    case Annotator::Type::IMPORT: // TODO: not sure how to best describe imports?? Skipping at the moment until #652 is resolved.
        instructions = "Can't deal with imports yet.";
        break;

    case Annotator::Type::ENCAPSULATION:
        instructions = "Model encapsulation";
        break;

    case Annotator::Type::COMPONENT:
        traceComponentIndices(mPimpl->mModel, std::any_cast<ComponentPtr>(item.second), indexList);
        std::reverse(indexList.begin(), indexList.end());
        if (!indexList.empty()) {
            instructions = "Component: model";
            for (const auto &i : indexList) {
                instructions += "->component(" + std::to_string(i) + ")";
            }
        }
        break;

    case Annotator::Type::COMPONENT_REF:
        traceComponentIndices(mPimpl->mModel, std::any_cast<ComponentPtr>(item.second), indexList);
        std::reverse(indexList.begin(), indexList.end());
        if (!indexList.empty()) {
            instructions = "Component position in encapsulation hierarchy: model";
            for (const auto &i : indexList) {
                instructions += "->component(" + std::to_string(i) + ")";
            }
        }
        break;

    case Annotator::Type::VARIABLE:
        traceVariableIndices(mPimpl->mModel, std::any_cast<VariablePtr>(item.second), indexList);
        std::reverse(indexList.begin(), indexList.end());

        if (!indexList.empty()) {
            index = indexList.back();
            indexList.pop_back();
            instructions = "Variable: model";
            for (const auto &i : indexList) {
                instructions += "->component(" + std::to_string(i) + ")";
            }
            instructions += "->variable(" + std::to_string(index) + ")";
        }
        break;

    case Annotator::Type::RESET:
        traceResetIndices(mPimpl->mModel, std::any_cast<ResetPtr>(item.second), indexList);
        std::reverse(indexList.begin(), indexList.end());

        if (!indexList.empty()) {
            index = indexList.back();
            indexList.pop_back();
            instructions = "Reset: model";
            for (const auto &i : indexList) {
                instructions += "->component(" + std::to_string(i) + ")";
            }
            instructions += "->reset(" + std::to_string(index) + ")";
        }
        break;

    case Annotator::Type::RESET_VALUE:
        traceResetIndices(mPimpl->mModel, std::any_cast<ResetPtr>(item.second), indexList);
        std::reverse(indexList.begin(), indexList.end());

        if (!indexList.empty()) {
            index = indexList.back();
            indexList.pop_back();
            instructions = "Reset value: model";
            for (const auto &i : indexList) {
                instructions += "->component(" + std::to_string(i) + ")";
            }
            instructions += "->reset(" + std::to_string(index) + ")->resetValue()";
        }
        break;

    case Annotator::Type::TEST_VALUE:
        traceResetIndices(mPimpl->mModel, std::any_cast<ResetPtr>(item.second), indexList);
        std::reverse(indexList.begin(), indexList.end());

        if (!indexList.empty()) {
            index = indexList.back();
            indexList.pop_back();
            instructions = "Test value: model";
            for (const auto &i : indexList) {
                instructions += "->component(" + std::to_string(i) + ")";
            }
            instructions += "->reset(" + std::to_string(index) + ")->testValue()";
        }
        break;

    case Annotator::Type::UNITS:
        traceUnitsIndices(mPimpl->mModel, std::any_cast<UnitsPtr>(item.second), indexList);
        std::reverse(indexList.begin(), indexList.end());

        if (!indexList.empty()) {
            instructions = "Units: model->units(" + std::to_string(indexList.at(0)) + ")";
        }
        break;

    case Annotator::Type::UNIT:
        traceUnitIndices(mPimpl->mModel, std::any_cast<UnitItem>(item.second), indexList);
        std::reverse(indexList.begin(), indexList.end());

        if (!indexList.empty()) {
            instructions = "Unit in Units: model->units(" + std::to_string(indexList.at(0)) + ")";
            instructions += "->unit(" + std::to_string(indexList.at(1)) + ")";
        }
        break;

    case Annotator::Type::MAP_VARIABLES:

        traceVariableIndices(mPimpl->mModel, std::any_cast<VariablePair>(item.second).first, indexList);
        std::reverse(indexList.begin(), indexList.end());

        if (!indexList.empty()) {
            index = indexList.back();
            indexList.pop_back();
            instructions += "Variable equivalence between: \n";
            instructions += "  model";
            for (const auto &i : indexList) {
                instructions += "->component(" + std::to_string(i) + ")";
            }
            instructions += "->variable(" + std::to_string(index) + ")\n";

            traceVariableIndices(mPimpl->mModel, std::any_cast<VariablePair>(item.second).second, indexList);
            std::reverse(indexList.begin(), indexList.end());

            index = indexList.back();
            indexList.pop_back();
            instructions += "  model";
            for (const auto &i : indexList) {
                instructions += "->component(" + std::to_string(i) + ")";
            }
            instructions += "->variable(" + std::to_string(index) + ")";
        }
        break;

    case Annotator::Type::CONNECTION:
        traceVariableIndices(mPimpl->mModel, std::any_cast<VariablePair>(item.second).first, indexList);
        std::reverse(indexList.begin(), indexList.end());

        if (!indexList.empty()) {
            index = indexList.back();
            indexList.pop_back();
            instructions += "Connection caused by the variable equivalence between: \n";
            instructions += "  model";
            for (const auto &i : indexList) {
                instructions += "->component(" + std::to_string(i) + ")";
            }
            instructions += "->variable(" + std::to_string(index) + ")\n";

            traceVariableIndices(mPimpl->mModel, std::any_cast<VariablePair>(item.second).second, indexList);
            std::reverse(indexList.begin(), indexList.end());

            index = indexList.back();
            indexList.pop_back();
            instructions += "  model";
            for (const auto &i : indexList) {
                instructions += "->component(" + std::to_string(i) + ")";
            }
            instructions += "->variable(" + std::to_string(index) + ")";
        }
        break;

    case Annotator::Type::ISSUE:
        auto issue = std::any_cast<IssuePtr>(item.second);
        instructions = issue->description();
        break;
    }
    return instructions;
}

} // namespace libcellml

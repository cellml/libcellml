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
#include <variant>

#include "libcellml/component.h"
#include "libcellml/importsource.h"
#include "libcellml/model.h"
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
    ItemInfoMap mMap;
};

Annotator::Annotator()
    : mPimpl(new AnnotatorImpl())
{
    mPimpl->mAnnotator = this;
}

Annotator::~Annotator()
{
    delete mPimpl;
}

AnnotatorPtr Annotator::create() noexcept
{
    return std::shared_ptr<Annotator> {new Annotator {}};
}
/*

// std::vector<ComponentPtr> serialiseComponents(const ModelPtr &model)
// {
//     std::vector<ComponentPtr> components;
//     for (size_t c = 0; c < model->componentCount(); ++c) {
//         addToComponentList(model->component(c), components);
//     }
//     return components;
// }

// void addToComponentList(const ComponentPtr &component, std::vector<ComponentPtr> &components)
// {
//     components.push_back(component);
//     for (size_t c = 0; c < component->componentCount(); ++c) {
//         addToComponentList(component->component(c), components);
//     }
// }

// std::vector<VariablePtr> serialiseVariables(const ModelPtr &model)
// {
//     std::vector<VariablePtr> variables;
//     for (size_t c = 0; c < model->componentCount(); ++c) {
//         addToVariableList(model->component(c), variables);
//     }
//     return variables;
// }

// void addToVariableList(const ComponentPtr &component, std::vector<VariablePtr> &variables)
// {
//     for (size_t v = 0; v < component->variableCount(); ++v) {
//         variables.push_back(component->variable(v));
//     }

//     for (size_t c = 0; c < component->componentCount(); ++c) {
//         addToVariableList(component->component(c), variables);
//     }
// }

// std::vector<ResetPtr> serialiseResets(const ModelPtr &model)
// {
//     std::vector<ResetPtr> resets;
//     for (size_t c = 0; c < model->componentCount(); ++c) {
//         addToResetList(model->component(c), resets);
//     }
//     return resets;
// }

// void addToResetList(const ComponentPtr &component, std::vector<ResetPtr> &resets)
// {
//     for (size_t r = 0; r < component->resetCount(); ++r) {
//         resets.push_back(component->reset(r));
//     }

//     for (size_t c = 0; c < component->componentCount(); ++c) {
//         addToResetList(component->component(c), resets);
//     }
// }

// std::vector<ImportSourcePtr> serialiseImportSources(const ModelPtr &model)
// {
//     std::vector<ImportSourcePtr> imports;
//     for (size_t c = 0; c < model->componentCount(); ++c) {
//         addToImportSourceList(model->component(c), imports);
//     }
//     return imports;
// }

// void addToImportSourceList(const ComponentPtr &component, std::vector<ImportSourcePtr> &imports)
// {
//     if (component->isImport()) {
//         imports.push_back(component->importSource());
//     }

//     for (size_t c = 0; c < component->componentCount(); ++c) {
//         addToImportSourceList(component->component(c), imports);
//     }
// }

// ItemInfo makeIdItem(const ComponentPtr &item)
// {
//     return std::make_pair(item->id(), std::make_pair(typeid(item).name(), std::dynamic_pointer_cast<Entity>(item)));
// }

// ItemInfo makeIdItem(const VariablePtr &item)
// {
//     return std::make_pair(item->id(), std::make_pair(typeid(item).name(), std::dynamic_pointer_cast<Entity>(item)));
// }

// ItemInfo makeIdItem(const ResetPtr &item)
// {
//     return std::make_pair(item->id(), std::make_pair(typeid(item).name(), std::dynamic_pointer_cast<Entity>(item)));
// }

// ItemInfo makeIdItem(const UnitsPtr &item)
// {
//     return std::make_pair(item->id(), std::make_pair(typeid(item).name(), std::dynamic_pointer_cast<Entity>(item)));
// }

// ItemInfo makeIdItem(const ImportSourcePtr &item)
// {
//     return std::make_pair(item->id(), std::make_pair(typeid(item).name(), std::dynamic_pointer_cast<Entity>(item)));
// }

// ItemInfo makeIdItem(const ModelPtr &item)
// {
//     return std::make_pair(item->id(), std::make_pair(typeid(item).name(), std::dynamic_pointer_cast<Entity>(item)));
// }

*/

void build(const ModelPtr &model)
{

}

void buildIdMapComponent(const ComponentPtr &component, ItemInfoMap &idMap)
{
    // Add component to map.
    if (!component->id().empty()) {
        idMap.at('component')->insert(makeIdItem(component));
    }

    // Add import source to map.
    if (component->isImport() && !component->importSource()->id().empty()) {
        idMap.insert(makeIdItem(component->importSource()));
    }

    // Add variables to map.
    for (size_t v = 0; v < component->variableCount(); ++v) {
        if (!component->variable(v)->id().empty()) {
            idMap.insert(makeIdItem(component->variable(v)));
        }
    }

    // Add reset to map.
    for (size_t r = 0; r < component->resetCount(); ++r) {
        if (!component->reset(r)->id().empty()) {
            idMap.insert(makeIdItem(component->reset(r)));
        }
    }

    // Start recursion through child components.
    for (size_t c = 0; c < component->componentCount(); ++c) {
        buildIdMapComponent(component->component(c), idMap);
    }
}

ItemInfoMap buildRecipeMap(const ModelPtr &model)
{
    RecipeMap recipeMap;

    // Add model.
    if (!model->id().empty()) {
        idMap.insert(makeIdItem(model));
    }

    // Add units.
    for (size_t u = 0; u < model->unitsCount(); ++u) {
        if (!model->units(u)->id().empty()) {
            idMap.insert(makeIdItem(model->units(u)));
        }
    }

    // Start recursion through encapsulation hierarchy.
    for (size_t c = 0; c < model->componentCount(); ++c) {
        buildIdMapComponent(model->component(c), idMap);
    }
    return idMap;
}

// void Annotator::build(const ModelPtr &model)
// {
//     mPimpl->mMap = buildIdMap(model);
// }
#if 0
ItemInfo makeIdItem(const ComponentPtr &item)
{
    AnnotatorItemStruct u;
    u.component = item;
    u.type = typeid(item).name();
    // return std::make_pair(item->id(), std::make_pair("component", u));
    return std::make_pair(item->id(), u);
}

ItemInfo makeIdItem(const VariablePtr &item)
{
    AnnotatorItemStruct u;
    u.variable = item;
    u.type = typeid(item).name();
    // return std::make_pair(item->id(), std::make_pair("variable", u));
    return std::make_pair(item->id(), u);
}

ItemInfo makeIdItem(const ResetPtr &item)
{
    AnnotatorItemStruct u;
    u.reset = item;
    u.type = typeid(item).name();
    // return std::make_pair(item->id(), std::make_pair("reset", u));
    return std::make_pair(item->id(), u);
}

ItemInfo makeIdItem(const UnitsPtr &item)
{
    AnnotatorItemStruct u;
    u.units = item;
    u.type = typeid(item).name();
    // return std::make_pair(item->id(), std::make_pair("units", u));
    return std::make_pair(item->id(), u);
}

ItemInfo makeIdItem(const ImportSourcePtr &item)
{
    AnnotatorItemStruct u;
    u.importSource = item;
    u.type = typeid(item).name();

    return std::make_pair(item->id(), u);
}

ItemInfo makeIdItem(const ModelPtr &item)
{
    AnnotatorItemStruct u;
    u.model = item;
    u.type = typeid(item).name();
    return std::make_pair(item->id(), u);
    // return std::make_pair(item->id(), std::make_pair(typeid(item).name(), std::dynamic_pointer_cast<Entity>(item)));
}

void buildIdMapComponent(const ComponentPtr &component, ItemInfoMap &idMap)
{
    // Add component to map.
    if (!component->id().empty()) {
        idMap.insert(makeIdItem(component));
    }

    // Add import source to map.
    if (component->isImport() && !component->importSource()->id().empty()) {
        idMap.insert(makeIdItem(component->importSource()));
    }

    // Add variables to map.
    for (size_t v = 0; v < component->variableCount(); ++v) {
        if (!component->variable(v)->id().empty()) {
            idMap.insert(makeIdItem(component->variable(v)));
        }
    }

    // Add reset to map.
    for (size_t r = 0; r < component->resetCount(); ++r) {
        if (!component->reset(r)->id().empty()) {
            idMap.insert(makeIdItem(component->reset(r)));
        }
    }

    // Start recursion through child components.
    for (size_t c = 0; c < component->componentCount(); ++c) {
        buildIdMapComponent(component->component(c), idMap);
    }
}

ItemInfoMap buildIdMap(const ModelPtr &model)
{
    ItemInfoMap idMap;

    // Add model.
    if (!model->id().empty()) {
        idMap.insert(makeIdItem(model));
    }

    // Add units.
    for (size_t u = 0; u < model->unitsCount(); ++u) {
        if (!model->units(u)->id().empty()) {
            idMap.insert(makeIdItem(model->units(u)));
        }
    }

    // Start recursion through encapsulation hierarchy.
    for (size_t c = 0; c < model->componentCount(); ++c) {
        buildIdMapComponent(model->component(c), idMap);
    }
    return idMap;
}

void Annotator::build(const ModelPtr &model)
{
    mPimpl->mMap = buildIdMap(model);
}

AnnotatorItemStruct Annotator::itemFromId(const std::string &id)
{
    AnnotatorItemStruct item;
    auto num = mPimpl->mMap.count(id);
    if (num < 1) {
        IssuePtr issue = Issue::create();
        issue->setDescription("Element with id '" + id + "' is not found in the model.");
        issue->setReferenceRule(Issue::ReferenceRule::ANNOTATOR_NO_ID);
        issue->setLevel(Issue::Level::WARNING);
        mPimpl->mAnnotator->addIssue(issue);
        return item;
    }
    if (num > 1) {
        IssuePtr issue = Issue::create();
        issue->setDescription("Multiple elements (" + std::to_string(num) + ") with id '" + id + "' have been found in the model.");
        issue->setReferenceRule(Issue::ReferenceRule::ANNOTATOR_DUPLICATE_ID);
        issue->setLevel(Issue::Level::WARNING);
        mPimpl->mAnnotator->addIssue(issue);
        return item;
    }

    return mPimpl->mMap.find(id)->second;
}

std::string Annotator::typeFromId(const std::string &id)
{
    // ItemInfo = std::pair<std::string,std::pair<std::string, EntityPtr>>

    auto num = mPimpl->mMap.count(id);
    if (num < 1) {
        IssuePtr issue = Issue::create();
        issue->setDescription("Element with id '" + id + "' is not found in the model.");
        issue->setReferenceRule(Issue::ReferenceRule::ANNOTATOR_NO_ID);
        issue->setLevel(Issue::Level::WARNING);
        mPimpl->mAnnotator->addIssue(issue);
        return "";
    }
    if (num > 1) {
        IssuePtr issue = Issue::create();
        issue->setDescription("Multiple elements (" + std::to_string(num) + ") with id '" + id + "' have been found in the model.");
        issue->setReferenceRule(Issue::ReferenceRule::ANNOTATOR_DUPLICATE_ID);
        issue->setLevel(Issue::Level::WARNING);
        mPimpl->mAnnotator->addIssue(issue);
        return "";
    }
    return mPimpl->mMap.find(id)->second.type;
}
#endif
} // namespace libcellml

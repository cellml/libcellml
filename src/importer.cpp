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

#include "libcellml/importer.h"

#include <algorithm>
#include <cmath>
#include <fstream>
#include <libxml/uri.h>
#include <sstream>
#include <stdexcept>

#include "libcellml/component.h"
#include "libcellml/importsource.h"
#include "libcellml/model.h"
#include "libcellml/parser.h"
#include "libcellml/reset.h"
#include "libcellml/units.h"
#include "libcellml/variable.h"

#include "namespaces.h"
#include "utilities.h"
#include "xmldoc.h"
#include "xmlutils.h"

namespace libcellml {

/**
 * @brief The Importer::ImporterImpl struct.
 *
 * This struct is the private implementation struct for the Importer class.  Separating
 * the implementation from the definition allows for greater flexibility when
 * distributing the code.
 */
struct Importer::ImporterImpl
{
    enum class Type
    {
        UNITS,
        COMPONENT
    };

    Importer *mImporter = nullptr;

    ImportLibrary mLibrary;
    std::vector<std::string> mLibraryIndex;
    std::vector<std::pair<std::string, std::string>> mExternals;

    bool resolveImport(const ImportedEntityPtr &importedEntity,
                       const std::string &destination, Type type,
                       const std::string &baseFile,
                       std::vector<std::tuple<std::string, std::string, std::string>> &history);

    bool resolveComponentImports(const ComponentEntityPtr &parentComponentEntity,
                                 const std::string &baseFile,
                                 std::vector<std::tuple<std::string, std::string, std::string>> &history);

    bool doResolveImports(ModelPtr &model, const std::string &baseFile,
                          std::vector<std::tuple<std::string, std::string, std::string>> &history);

    void generateCyclicDependenciesIssues(const ModelPtr &model, Type type,
                                          std::vector<std::tuple<std::string, std::string, std::string>> &history) const;
};

Importer::Importer()
    : mPimpl(new ImporterImpl())
{
    mPimpl->mImporter = this;
}

ImporterPtr Importer::create() noexcept
{
    return std::shared_ptr<Importer> {new Importer {}};
}

Importer::~Importer()
{
    delete mPimpl;
}

bool checkUnitsForCycles(ModelPtr &model, std::vector<std::tuple<std::string, std::string, std::string>> &history)
{
    // Check through model for overlap with the current history so we can report cycles properly.
    for (size_t u = 0; u < model->unitsCount(); ++u) {
        auto units = model->units(u);
        if (units->isImport()) {
            auto importSource = units->importSource();
            auto h = std::make_tuple(units->name(), units->importReference(), importSource->url());
            if (std::find(history.begin(), history.end(), h) != history.end()) {
                history.emplace_back(h);
                return false;
            }
        }
    }
    return true;
}

bool checkComponentForCycles(ModelPtr &model, std::vector<std::tuple<std::string, std::string, std::string>> &history)
{
    for (size_t c = 0; c < model->componentCount(); ++c) {
        auto component = model->component(c);
        if (component->isImport()) {
            auto importSource = component->importSource();
            auto h = std::make_tuple(component->name(), component->importReference(), importSource->url());
            if (std::find(history.begin(), history.end(), h) != history.end()) {
                history.emplace_back(h);
                return false;
            }
        }
    }
    return true;
}

bool Importer::ImporterImpl::doResolveImports(ModelPtr &model, const std::string &baseFile,
                                              std::vector<std::tuple<std::string, std::string, std::string>> &history)
{
    for (size_t n = 0; n < model->unitsCount(); ++n) {
        auto units = model->units(n);
        if (!resolveImport(units, units->name(), Type::UNITS, baseFile, history) && !history.empty()) {
            generateCyclicDependenciesIssues(model, Type::UNITS, history);
            return false;
        }
    }
    return resolveComponentImports(model, baseFile, history);
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
    // We can be naive here as we know what we are dealing with.
    std::string path = base.substr(0, base.find_last_of('/') + 1) + filename;
    return path;
}

bool Importer::ImporterImpl::resolveImport(const ImportedEntityPtr &importedEntity,
                                           const std::string &destination,
                                           Type type,
                                           const std::string &baseFile,
                                           std::vector<std::tuple<std::string, std::string, std::string>> &history)
{
    if (importedEntity->isImport()) {
        auto importSource = importedEntity->importSource();
        auto h = std::make_tuple(destination, importedEntity->importReference(), importSource->url());

        // Check for cyclical dependencies using the entire tuple contents.
        if (std::find(history.begin(), history.end(), h) != history.end()) {
            history.emplace_back(h);
            return false;
        }
        history.emplace_back(h);

        // Only parse import if it doesn't already exist in our importer library.
        if (!importSource->hasModel()) {
            std::string url = importSource->url();
            if (mLibrary.count(url) == 0) {
                url = resolvePath(importSource->url(), baseFile);
            }
            if (mLibrary.count(url) == 0) {
                // If the URL has not been resolved into a model in this library, parse it and save.
                std::ifstream file(url);
                if (!file.good()) {
                    return false;
                }
                std::stringstream buffer;
                buffer << file.rdbuf();
                auto parser = Parser::create();
                auto model = parser->parseModel(buffer.str());
                importSource->setModel(model);

                // Save the pair of model and URL to the library map.
                mLibrary.insert(std::make_pair(url, model));

                // Save the imported model to a list of external dependencies.
                mExternals.emplace_back(std::make_pair(url, importedEntity->importReference()));
                return doResolveImports(model, url, history);
            }
            // If it has, then pass the previous model instance to the import source.
            auto model = mLibrary[url];
            importSource->setModel(model);
            if (type == Type::COMPONENT) {
                return checkComponentForCycles(model, history);
            }
            return checkUnitsForCycles(model, history);
        }
    }
    return true;
}

void Importer::ImporterImpl::generateCyclicDependenciesIssues(const ModelPtr &model,
                                                              Type type,
                                                              std::vector<std::tuple<std::string, std::string, std::string>> &history) const
{
    std::string msg = "Cyclic dependencies were found when attempting to resolve "
                      + std::string((type == Type::UNITS) ? "units" : "components") + " in model '"
                      + model->name() + "'. The dependency loop is:\n";
    std::tuple<std::string, std::string, std::string> h;
    auto hSize = history.size();
    std::string typeString = (type == Type::UNITS) ? "units" : "component";
    for (size_t i = 0; i < hSize; ++i) {
        h = history[i];
        msg += " - " + typeString + " '" + std::get<0>(h) + "' is imported from '" + std::get<1>(h) + "' in '" + std::get<2>(h) + "'";
        if (i != hSize - 1) {
            msg += ";";
            if (i == hSize - 2) {
                msg += " and";
            }
            msg += "\n";
        } else {
            msg += ".";
        }
    }
    auto issue = Issue::create();
    issue->setDescription(msg);
    issue->setLevel(Issue::Level::WARNING);
    issue->setCause(ItemType::IMPORT);
    mImporter->addIssue(issue);
    std::vector<std::tuple<std::string, std::string, std::string>>().swap(history);
}

bool Importer::ImporterImpl::resolveComponentImports(const ComponentEntityPtr &parentComponentEntity,
                                                     const std::string &baseFile,
                                                     std::vector<std::tuple<std::string, std::string, std::string>> &history)
{
    bool noErrors = true;
    for (size_t n = 0; n < parentComponentEntity->componentCount(); ++n) {
        auto component = parentComponentEntity->component(n);
        if (component->isImport()) {
            if (!resolveImport(component, component->name(), Type::COMPONENT, baseFile, history)) {
                if (!history.empty()) {
                    generateCyclicDependenciesIssues(owningModel(component), Type::COMPONENT, history);
                }
                noErrors = false;
            }
        }
        if (!resolveComponentImports(component, baseFile, history)) {
            noErrors = false;
        }
    }
    return noErrors;
}

void Importer::resolveImports(ModelPtr &model, const std::string &baseFile)
{
    std::vector<std::tuple<std::string, std::string, std::string>> history = {};
    mPimpl->doResolveImports(model, baseFile, history);
}

void clearComponentImports(const ComponentPtr &component)
{
    if (component->isImport()) {
        component->importSource()->setModel(nullptr);
    }
    for (size_t c = 0; c < component->componentCount(); ++c) {
        clearComponentImports(component->component(c));
    }
}

void Importer::clearImports(ModelPtr &model)
{
    // Clear the models from all import sources in the model.
    for (size_t u = 0; u < model->unitsCount(); ++u) {
        auto mu = model->units(u);
        if (mu->isImport()) {
            mu->importSource()->setModel(nullptr);
        }
    }
    for (size_t c = 0; c < model->componentCount(); ++c) {
        clearComponentImports(model->component(c));
    }
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
        for (size_t i = 0; i < component->componentCount(); ++i) {
            importedComponentCopy->addComponent(component->component(i));
        }

        // Get list of required units from component's variables.
        std::vector<UnitsPtr> requiredUnits = unitsUsed(importModel, importedComponentCopy);

        // Add all required units to a model so referenced units can be resolved.
        auto requiredUnitsModel = Model::create();
        for (const auto &units : requiredUnits) {
            // Cloning units present elsewhere so that they don't get moved by the addUnits function.
            if (units->parent() == nullptr) {
                requiredUnitsModel->addUnits(units);
            } else {
                auto cloned = units->clone();
                requiredUnitsModel->addUnits(cloned);
            }
        }

        // Make a map of component name to component pointer.
        ComponentNameMap newComponentNames = createComponentNamesMap(importedComponentCopy);
        for (const auto &entry : newComponentNames) {
            std::string newName = entry.first;
            size_t count = 0;
            while (std::find(compNames.begin(), compNames.end(), newName) != compNames.end()) {
                newName += "_" + convertToString(++count);
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
        std::map<std::string, std::string> unitsNamesToReplace;
        for (const auto &u : requiredUnits) {
            if (!model->hasUnits(u)) {
                auto orignalName = u->name();
                size_t count = 0;
                while (!model->hasUnits(u) && model->hasUnits(u->name())) {
                    auto name = u->name();
                    name += "_" + convertToString(++count);
                    u->setName(name);
                }
                model->addUnits(u);
                if (orignalName != u->name()) {
                    unitsNamesToReplace[orignalName] = u->name();
                }
            }
        }
        findAndReplaceComponentsCnUnitsNames(importedComponentCopy, unitsNamesToReplace);
    }
}

void flattenComponentTree(const ComponentEntityPtr &parent, const ComponentPtr &component, size_t componentIndex)
{
    flattenComponent(parent, component, componentIndex);
    auto flattenedComponent = parent->component(componentIndex);
    for (size_t index = 0; index < flattenedComponent->componentCount(); ++index) {
        auto c = flattenedComponent->component(index);
        flattenComponentTree(flattenedComponent, c, index);
    }
}

ModelPtr Importer::flattenModel(const ModelPtr &model)
{
    if (model->hasUnresolvedImports()) {
        return nullptr;
    }
    auto flatModel = model->clone();

    while (flatModel->hasImports()) {
        // Go through Units and instantiate any imported Units.
        for (size_t index = 0; index < flatModel->unitsCount(); ++index) {
            auto u = flatModel->units(index);
            if (u->isImport()) {
                auto importedUnits = u->importSource()->model()->units(u->importReference());
                auto importedUnitsCopy = importedUnits->clone();
                importedUnitsCopy->setName(u->name());
                flatModel->replaceUnits(index, importedUnitsCopy);
            }
        }

        // Go through Components and instantiate any imported Components.
        for (size_t index = 0; index < flatModel->componentCount(); ++index) {
            auto c = flatModel->component(index);
            flattenComponentTree(flatModel, c, index);
        }
    }

    flatModel->linkUnits();
    return flatModel;
}

size_t Importer::libraryCount()
{
    return mPimpl->mLibrary.size();
}

ModelPtr Importer::library(const std::string &key)
{
    if (mPimpl->mLibrary.count(key) != 0) {
        return mPimpl->mLibrary[key];
    }
    return nullptr;
}

ModelPtr Importer::library(const size_t &index)
{
    if (index >= mPimpl->mLibrary.size()) {
        return nullptr;
    }
    auto it = mPimpl->mLibrary.begin();
    size_t i = 0;
    while (i < index) {
        ++it;
        ++i;
    }
    return it->second;
}

bool Importer::addModel(const ModelPtr &model, const std::string &key)
{
    if (mPimpl->mLibrary.count(key) != 0) {
        // If the key already exists in the library, do nothing.
        return false;
    }
    mPimpl->mLibrary.insert(std::make_pair(key, model));
    return true;
}

bool Importer::replaceModel(const ModelPtr &model, const std::string &key)
{
    if (mPimpl->mLibrary.count(key) == 0) {
        // If the key is not found, do nothing.
        return false;
    }
    mPimpl->mLibrary[key] = model;
    return true;
}

size_t Importer::externalDependencyCount() const
{
    return mPimpl->mExternals.size();
}

std::pair<std::string, std::string> Importer::externalDependency(size_t index) const
{
    if (index < mPimpl->mExternals.size()) {
        return mPimpl->mExternals.at(index);
    }
    return std::make_pair("", "");
}

} // namespace libcellml

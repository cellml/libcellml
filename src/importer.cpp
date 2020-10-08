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

    IssuePtr makeIssueCyclicDependency(const ModelPtr &model, Type type,
                                       std::vector<std::tuple<std::string, std::string, std::string>> &history) const;

    bool fetchModel(const ImportSourcePtr &importSource, const std::string &baseFile);
    bool fetchImportSource(const ImportSourcePtr &importSource, Type type, const std::string &baseFile, std::vector<std::tuple<std::string, std::string, std::string>> &history);

    bool fetchComponent(const ComponentPtr &importComponent, const std::string &baseFile, std::vector<std::tuple<std::string, std::string, std::string>> &history);
    bool fetchUnits(const UnitsPtr &importUnits, const std::string &baseFile, std::vector<std::tuple<std::string, std::string, std::string>> &history);
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

bool checkForCycles(ModelPtr &model, std::vector<std::tuple<std::string, std::string, std::string>> &history)
{
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
std::string directoryPath(const std::string &filename)
{
    // We can be naive here as we know what we are dealing with.
    return filename.substr(0, filename.find_last_of('/') + 1);
}

std::string resolvePath(const std::string &filename, const std::string &base)
{
    return directoryPath(base) + filename;
}

bool Importer::ImporterImpl::fetchModel(const ImportSourcePtr &importSource, const std::string &baseFile)
{
    std::string url = importSource->url();
    if (mLibrary.count(url) == 0) {
        url = resolvePath(importSource->url(), baseFile);
    }

    ModelPtr model;
    if (mLibrary.count(url) == 0) {
        // If the URL has not ever been resolved into a model in this library, with or
        // without baseFile, parse it and save.
        std::ifstream file(url);
        if (!file.good()) {
            auto issue = Issue::create();
            issue->setDescription("The attempt to resolve imports with the model at '" + url + "' failed: the file could not be opened.");
            issue->setImportSource(importSource);
            issue->setReferenceRule(Issue::ReferenceRule::UNSPECIFIED);
            mImporter->addIssue(issue);
            return false;
        }
        std::stringstream buffer;
        buffer << file.rdbuf();
        auto parser = Parser::create();
        model = parser->parseModel(buffer.str());
        mLibrary.insert(std::make_pair(url, model));
    } else {
        model = mLibrary[url];
    }
    importSource->setModel(model);
    return true;
}

bool Importer::ImporterImpl::fetchImportSource(const ImportSourcePtr &importSource, Type type, const std::string &baseFile, std::vector<std::tuple<std::string, std::string, std::string>> &history)
{
    // If the model has never been retrieved, get it and add to library.
    if (!importSource->hasModel()) {
        if (!fetchModel(importSource, baseFile)) {
            return false;
        }
    }
    // Check for cycles.
    std::string url = importSource->url();
    if (mLibrary.count(url) == 0) {
        url = resolvePath(url, baseFile);
    }
    auto model = mLibrary[url];
    if (!checkForCycles(model, history)) {
        auto issue = makeIssueCyclicDependency(model, type, history);
        issue->setImportSource(importSource);
        mImporter->addIssue(issue);
        return false;
    }
    return true;
}

bool Importer::ImporterImpl::fetchComponent(const ComponentPtr &importComponent, const std::string &baseFile, std::vector<std::tuple<std::string, std::string, std::string>> &history)
{
    // Given the importComponent, check whether it has been resolved previously.  If so, return.
    // If not, check for model, and parse/instantiate/add to library if needed.
    // If model exists, resolve component's requirements, including child components and units required.

    if (!importComponent->requiresImports() || importComponent->isResolved()) {
        return true;
    }

    if (!importComponent->isImport()) {
        // This component is not an import, but a descendant is.
        for (size_t c = 0; c < importComponent->componentCount(); ++c) {
            if (!fetchComponent(importComponent->component(c), baseFile, history)) {
                return false;
            }
        }
        return true;
    }

    history.emplace_back(std::make_tuple(importComponent->name(), importComponent->importReference(), importComponent->importSource()->url()));
    if (!fetchImportSource(importComponent->importSource(), Type::COMPONENT, baseFile, history)) {
        return false;
    }

    // Check that the model instance in the library has resolved all of the required dependencies.
    auto sourceModel = importComponent->importSource()->model();
    auto sourceComponent = sourceModel->component(importComponent->importReference());
    if (sourceComponent != nullptr) {
        // Check whether the sourceComponent is itself an import. Note that the file path passed in
        // here must be the path to the sourceModel, rather than the path to the previous import, so that
        // the chain always tests local to the importing model first.
        auto newBase = baseFile + directoryPath(importComponent->importSource()->url());

        // Fetch this component, if needed.
        if (!fetchComponent(sourceComponent, newBase, history)) {
            return false;
        }

        // Fetch any components encapsulated inside the imported component.
        for (size_t c = 0; c < sourceComponent->componentCount(); ++c) {
            if (!fetchComponent(sourceComponent->component(c), newBase, history)) {
                return false;
            }
        }

        // Fetch any units needed by this component.
        for (const auto &unitName : unitsNamesUsed(sourceComponent)) {
            auto units = sourceModel->units(unitName);
            if (units == nullptr) {
                auto issue = Issue::create();
                issue->setDescription("Import of component '" + importComponent->name() + "' from '" + importComponent->importReference() + "' requires units named '" + unitName + "' which cannot be found.");
                issue->setComponent(importComponent);
                issue->setReferenceRule(Issue::ReferenceRule::UNSPECIFIED);
                mImporter->addIssue(issue);
                return false;
            }
            if (!fetchUnits(units, newBase, history)) {
                return false;
            }
        }
    } else {
        auto issue = Issue::create();
        issue->setDescription("Import of component '" + importComponent->name() + "' from '" + importComponent->importSource()->url() + "' requires component named '" + importComponent->importReference() + "' which cannot be found.");
        issue->setComponent(importComponent);
        issue->setReferenceRule(Issue::ReferenceRule::UNSPECIFIED);
        mImporter->addIssue(issue);
        return false;
    }

    importComponent->setResolved(true);
    return true;
}

bool Importer::ImporterImpl::fetchUnits(const UnitsPtr &importUnits, const std::string &baseFile, std::vector<std::tuple<std::string, std::string, std::string>> &history)
{
    if (!importUnits->isImport() || importUnits->isResolved()) {
        return true;
    }

    history.emplace_back(std::make_tuple(importUnits->name(), importUnits->importReference(), importUnits->importSource()->url()));
    if (!fetchImportSource(importUnits->importSource(), Type::UNITS, baseFile, history)) {
        return false;
    }

    // Check Unit children for reliance on imported Units items.
    auto sourceModel = importUnits->importSource()->model();
    auto sourceUnits = sourceModel->units(importUnits->importReference());

    if (sourceUnits != nullptr) {
        auto newBase = baseFile + directoryPath(importUnits->importSource()->url());

        // Check whether the sourceUnits are themselves an import.
        if (!fetchUnits(sourceUnits, newBase, history)) {
            return false;
        }

        for (size_t u = 0; u < sourceUnits->unitCount(); ++u) {
            std::string reference;
            std::string prefix;
            std::string id;
            double exponent;
            double multiplier;
            sourceUnits->unitAttributes(u, reference, prefix, exponent, multiplier, id);
            if (isStandardUnitName(reference)) {
                continue;
            }
            auto sourceUnit = sourceModel->units(reference);
            if (sourceUnit == nullptr) {
                auto issue = Issue::create();
                issue->setDescription("Import of units '" + importUnits->name() + "' from '" + importUnits->importSource()->url() + "' requires units named '" + importUnits->importReference() + "', which relies on child units named '" + reference + "', which cannot be found.");
                issue->setUnits(sourceUnits);
                issue->setReferenceRule(Issue::ReferenceRule::UNSPECIFIED);
                mImporter->addIssue(issue);
                return false;
            }
            if (sourceUnit->isImport() && !sourceUnit->isResolved()) {
                if (!fetchUnits(sourceUnit, newBase, history)) {
                    return false;
                }
            }
        }
    } else {
        auto issue = Issue::create();
        issue->setDescription("Import of units '" + importUnits->name() + "' from '" + importUnits->importSource()->url() + "' requires units named '" + importUnits->importReference() + "' which cannot be found.");
        issue->setUnits(importUnits);
        issue->setReferenceRule(Issue::ReferenceRule::UNSPECIFIED);
        mImporter->addIssue(issue);
        return false;
    }

    importUnits->setResolved(true);
    return true;
}

IssuePtr Importer::ImporterImpl::makeIssueCyclicDependency(const ModelPtr &model,
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
    issue->setReferenceRule(Issue::ReferenceRule::IMPORT_EQUIVALENT);
    std::vector<std::tuple<std::string, std::string, std::string>>().swap(history);
    return issue;
}

bool Importer::resolveImports(ModelPtr &model, const std::string &baseFile)
{
    std::vector<std::tuple<std::string, std::string, std::string>> history = {};
    bool status = true;
    clearImports(model);

    for (size_t i = 0; i < model->importSourceCount(); ++i) {
        auto imp = model->importSource(i);
        for (size_t u = 0; u < imp->unitsCount(); ++u) {
            if (!mPimpl->fetchUnits(imp->units(u), baseFile, history)) {
                status = false;
            }
        }
        for (size_t c = 0; c < imp->componentCount(); ++c) {
            if (!mPimpl->fetchComponent(imp->component(c), baseFile, history)) {
                status = false;
            }
        }
    }
    return status;
}

void clearComponentImports(const ComponentPtr &component)
{
    if (component->isImport()) {
        component->importSource()->setModel(nullptr);
        component->setResolved(false);
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
            mu->setResolved(false);
        }
    }
    for (size_t c = 0; c < model->componentCount(); ++c) {
        clearComponentImports(model->component(c));
    }
}

void flattenComponent(const ComponentEntityPtr &parent, ComponentPtr &component, size_t index)
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

        // Apply the re-based equivalence map onto the modified model.
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

        // Remove the component from the import source.
        importSource->removeComponent(component);
    }
}

void flattenComponentTree(const ComponentEntityPtr &parent, ComponentPtr &component, size_t componentIndex)
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
                auto importSource = u->importSource();
                auto importedUnits = importSource->model()->units(u->importReference());
                auto importedUnitsCopy = importedUnits->clone();
                importedUnitsCopy->setName(u->name());
                flatModel->replaceUnits(index, importedUnitsCopy);
                importSource->removeUnits(u);
            }
        }

        // Go through Components and instantiate any imported Components.
        for (size_t index = 0; index < flatModel->componentCount(); ++index) {
            auto c = flatModel->component(index);
            flattenComponentTree(flatModel, c, index);
        }
    }

    flatModel->linkUnits();

    for (int i = int(flatModel->importSourceCount()) - 1; i >= 0; --i) {
        auto importSource = flatModel->importSource(size_t(i));
        if ((importSource->unitsCount() == 0) && (importSource->componentCount() == 0)) {
            flatModel->removeImportSource(importSource);
        }
    }

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

std::string Importer::key(const size_t &index)
{
    if (index >= mPimpl->mLibrary.size()) {
        return "";
    }
    auto it = mPimpl->mLibrary.begin();
    size_t i = 0;
    while (i < index) {
        ++it;
        ++i;
    }
    return it->first;
}

} // namespace libcellml

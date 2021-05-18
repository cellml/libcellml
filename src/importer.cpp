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

#include "anycellmlelement_p.h"
#include "issue_p.h"
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

    std::vector<ImportSourcePtr> mImports;
    std::vector<ImportSourcePtr>::const_iterator findImportSource(const ImportSourcePtr &importSource) const;

    std::string resolvingUrl(const ImportSourcePtr &importSource) const;
    std::string modelUrl(const ModelPtr &model) const;

    bool fetchComponent(const ComponentPtr &importComponent, const std::string &baseFile, History &history);
    bool fetchModel(const ImportSourcePtr &importSource, const std::string &baseFile);
    bool fetchImportSource(const ImportSourcePtr &importSource, const std::string &baseFile);
    bool fetchUnits(const UnitsPtr &importUnits, const std::string &baseFile, History &history);

    bool checkForImportCycles(const ImportSourcePtr &importSource, const History &history, const HistoryEpochPtr &h, const std::string &action) const;
    bool checkUnitsForCycles(const UnitsPtr &units, History &history) const;
    bool checkComponentForCycles(const ComponentPtr &component, History &history);

    bool hasImportCycles(const ModelPtr &model);
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

std::vector<ImportSourcePtr>::const_iterator Importer::ImporterImpl::findImportSource(const ImportSourcePtr &importSource) const
{
    return std::find_if(mImports.begin(), mImports.end(),
                        [=](const ImportSourcePtr &importSrc) -> bool { return importSource->equals(importSrc); });
}

std::string Importer::ImporterImpl::modelUrl(const ModelPtr &model) const
{
    for (const auto &entry : mLibrary) {
        if (entry.second == model) {
            return entry.first;
        }
    }

    return ORIGIN_MODEL_REF;
}

std::string Importer::ImporterImpl::resolvingUrl(const ImportSourcePtr &importSource) const
{
    auto model = importSource->model();
    if (model == nullptr) {
        return importSource->url();
    }

    return modelUrl(model);
}

bool Importer::ImporterImpl::checkUnitsForCycles(const UnitsPtr &units, History &history) const
{
    // Even if these units are not imported, they might have imported children.
    if (!units->isImport()) {
        for (size_t u = 0; u < units->unitCount(); ++u) {
            std::string ref;
            std::string prefix;
            std::string id;
            double multiplier;
            double exponent;

            units->unitAttributes(u, ref, prefix, exponent, multiplier, id);
            // If the child units are imported, check them too.
            auto model = owningModel(units);
            if ((model != nullptr) && model->hasUnits(ref)) {
                if (checkUnitsForCycles(model->units(ref), history)) {
                    return true;
                }
            }
        }
        return false;
    }

    // If they are imported, then they can't have any child unit elements anyway.
    std::string resolvingUrl = ImporterImpl::resolvingUrl(units->importSource());
    auto unitsModel = owningModel(units);
    auto h = createHistoryEpoch(units, modelUrl(unitsModel), resolvingUrl);

    if (checkForImportCycles(units->importSource(), history, h, "flatten")) {
        return true;
    }

    history.push_back(h);

    // If the dependencies have not been recorded already, then check it.
    auto model = units->importSource()->model();
    if (model == nullptr) {
        auto issue = Issue::IssueImpl::create();
        issue->mPimpl->setDescription("Units '" + units->name() + "' requires a model imported from '" + resolvingUrl + "' which is not available in the importer.");
        issue->mPimpl->mItem->mPimpl->setImportSource(units->importSource());
        issue->mPimpl->setReferenceRule(Issue::ReferenceRule::IMPORTER_NULL_MODEL);
        mImporter->addIssue(issue);
        return true;
    }
    auto importedUnits = model->units(units->importReference());
    if (importedUnits == nullptr) {
        auto issue = Issue::IssueImpl::create();
        issue->mPimpl->setDescription("Units '" + units->name() + "' imports units named '" + units->importReference() + "' from the model imported from '" + resolvingUrl + "'. The units could not be found.");
        issue->mPimpl->mItem->mPimpl->setImportSource(units->importSource());
        issue->mPimpl->setReferenceRule(Issue::ReferenceRule::IMPORTER_MISSING_UNITS);
        mImporter->addIssue(issue);
        return true;
    }

    return checkUnitsForCycles(importedUnits, history);
}

bool Importer::ImporterImpl::checkComponentForCycles(const ComponentPtr &component, History &history)
{
    std::string resolvingUrl = ImporterImpl::resolvingUrl(component->importSource());
    auto componentModel = owningModel(component);
    auto h = createHistoryEpoch(component, modelUrl(componentModel), resolvingUrl);

    if (checkForImportCycles(component->importSource(), history, h, "flatten")) {
        return true;
    }

    history.push_back(h);

    // If the dependencies have not been recorded already, then check it.
    if (component->isImport()) {
        auto model = component->importSource()->model();
        if (model == nullptr) {
            auto issue = Issue::IssueImpl::create();
            issue->mPimpl->setDescription("Component '" + component->name() + "' requires a model imported from '" + resolvingUrl + "' which is not available in the importer.");
            issue->mPimpl->mItem->mPimpl->setImportSource(component->importSource());
            issue->mPimpl->setReferenceRule(Issue::ReferenceRule::IMPORTER_NULL_MODEL);
            mImporter->addIssue(issue);
            return true;
        }
        auto importedComponent = model->component(component->importReference(), true);
        if (importedComponent == nullptr) {
            auto issue = Issue::IssueImpl::create();
            issue->mPimpl->setDescription("Component '" + component->name() + "' imports a component named '" + component->importReference() + "' from the model imported from '" + resolvingUrl + "'. The component could not be found.");
            issue->mPimpl->mItem->mPimpl->setImportSource(component->importSource());
            issue->mPimpl->setReferenceRule(Issue::ReferenceRule::IMPORTER_MISSING_COMPONENT);
            mImporter->addIssue(issue);
            return true;
        }

        if (importedComponent->isImport() && checkComponentForCycles(importedComponent, history)) {
            return true;
        }
    }

    return false;
}

bool Importer::ImporterImpl::hasImportCycles(const ModelPtr &model)
{
    History history;

    for (const UnitsPtr &units : getImportedUnits(model)) {
        history.clear();
        if (checkUnitsForCycles(units, history)) {
            return true;
        }
    }

    for (const ComponentPtr &component : getImportedComponents(model)) {
        history.clear();
        if (checkComponentForCycles(component, history)) {
            return true;
        }
    }

    return false;
}

std::string directoryPath(const std::string &filename)
{
    // We can be naive here as we know what we are dealing with.
    return filename.substr(0, filename.find_last_of('/') + 1);
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
            auto issue = Issue::IssueImpl::create();
            issue->mPimpl->setDescription("The attempt to resolve imports with the model at '" + url + "' failed: the file could not be opened.");
            issue->mPimpl->mItem->mPimpl->setImportSource(importSource);
            issue->mPimpl->setReferenceRule(Issue::ReferenceRule::IMPORTER_MISSING_FILE);
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

bool Importer::ImporterImpl::checkForImportCycles(const ImportSourcePtr &importSource, const History &history, const HistoryEpochPtr &h, const std::string &action) const
{
    if (libcellml::checkForImportCycles(history, h)) {
        auto cyclicHistory = history;
        cyclicHistory.push_back(h);
        auto description = formDescriptionOfCyclicDependency(cyclicHistory, action);
        auto issue = Issue::IssueImpl::create();
        issue->mPimpl->setDescription(description);
        issue->mPimpl->mItem->mPimpl->setImportSource(importSource);
        issue->mPimpl->setReferenceRule(Issue::ReferenceRule::IMPORT_EQUIVALENT);
        mImporter->addIssue(issue);
        return true;
    }

    return false;
}

bool Importer::ImporterImpl::fetchImportSource(const ImportSourcePtr &importSource, const std::string &baseFile)
{
    // If the model has never been retrieved, get it and add to library.
    if (!importSource->hasModel()) {
        if (!fetchModel(importSource, baseFile)) {
            return false;
        }
    }

    return true;
}

bool Importer::ImporterImpl::fetchComponent(const ComponentPtr &importComponent, const std::string &baseFile, History &history)
{
    // Given the importComponent, check whether it has been resolved previously.  If so, return.
    // If not, check for model, and parse/instantiate/add to library if needed.
    // If model exists, resolve component's requirements, including child components and units required.

    if (!importComponent->requiresImports()) {
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

    if (!fetchImportSource(importComponent->importSource(), baseFile)) {
        return false;
    }

    std::string resolvingUrl = ImporterImpl::resolvingUrl(importComponent->importSource());
    auto importComponentModel = owningModel(importComponent);
    auto h = createHistoryEpoch(importComponent, modelUrl(importComponentModel), resolvingUrl);

    if (checkForImportCycles(importComponent->importSource(), history, h, "resolve")) {
        return false;
    }

    history.push_back(h);

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
                auto issue = Issue::IssueImpl::create();
                issue->mPimpl->setDescription("Import of component '" + importComponent->name() + "' from '" + resolvingUrl + "' requires units named '" + unitName + "' which cannot be found.");
                issue->mPimpl->mItem->mPimpl->setComponent(importComponent);
                issue->mPimpl->setReferenceRule(Issue::ReferenceRule::IMPORTER_MISSING_COMPONENT);
                mImporter->addIssue(issue);
                return false;
            }
            if (!fetchUnits(units, newBase, history)) {
                return false;
            }
        }
    } else {
        auto issue = Issue::IssueImpl::create();
        issue->mPimpl->setDescription("Import of component '" + importComponent->name() + "' from '" + resolvingUrl + "' requires component named '" + importComponent->importReference() + "' which cannot be found.");
        issue->mPimpl->mItem->mPimpl->setComponent(importComponent);
        issue->mPimpl->setReferenceRule(Issue::ReferenceRule::IMPORTER_MISSING_COMPONENT);
        mImporter->addIssue(issue);
        return false;
    }

    history.pop_back();
    return true;
}

bool Importer::ImporterImpl::fetchUnits(const UnitsPtr &importUnits, const std::string &baseFile, History &history)
{
    if (!importUnits->isImport()) {
        return true;
    }

    if (!fetchImportSource(importUnits->importSource(), baseFile)) {
        return false;
    }

    std::string resolvingUrl = ImporterImpl::resolvingUrl(importUnits->importSource());
    auto unitsModel = owningModel(importUnits);
    auto h = createHistoryEpoch(importUnits, modelUrl(unitsModel), resolvingUrl);

    if (checkForImportCycles(importUnits->importSource(), history, h, "resolve")) {
        return false;
    }

    history.push_back(h);

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
                auto issue = Issue::IssueImpl::create();
                issue->mPimpl->setDescription("Import of units '" + importUnits->name() + "' from '" + resolvingUrl + "' requires units named '" + importUnits->importReference() + "', which relies on child units named '" + reference + "', which cannot be found.");
                issue->mPimpl->mItem->mPimpl->setUnits(sourceUnits);
                issue->mPimpl->setReferenceRule(Issue::ReferenceRule::IMPORTER_MISSING_UNITS);
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
        auto issue = Issue::IssueImpl::create();
        issue->mPimpl->setDescription("Import of units '" + importUnits->name() + "' from '" + resolvingUrl + "' requires units named '" + importUnits->importReference() + "' which cannot be found.");
        issue->mPimpl->mItem->mPimpl->setUnits(importUnits);
        issue->mPimpl->setReferenceRule(Issue::ReferenceRule::IMPORTER_MISSING_UNITS);
        mImporter->addIssue(issue);
        return false;
    }

    history.pop_back();
    return true;
}

bool Importer::resolveImports(ModelPtr &model, const std::string &baseFile)
{
    bool status = true;
    History history;

    clearImports(model);

    for (const UnitsPtr &units : getImportedUnits(model)) {
        history.clear();
        if (!mPimpl->fetchUnits(units, baseFile, history)) {
            // Get the last issue recorded and change its object to be the top-level importing item.
            issue(issueCount() - 1)->mPimpl->mItem->mPimpl->setUnits(units);
            status = false;
        }
    }

    for (const ComponentPtr &component : getImportedComponents(model)) {
        history.clear();
        if (!mPimpl->fetchComponent(component, baseFile, history)) {
            issue(issueCount() - 1)->mPimpl->mItem->mPimpl->setComponent(component);
            status = false;
        }
    }

    return status;
}

void clearComponentImports(const ComponentPtr &component)
{
    if (component->isImport()) {
        component->importSource()->removeModel();
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
            mu->importSource()->removeModel();
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
        IndexStack destinationComponentBaseIndexStack = indexStackOf(component);

        // Determine the stack for the source component.
        IndexStack importedComponentBaseIndexStack = indexStackOf(importedComponent);

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
                auto originalName = u->name();
                size_t count = 0;
                while (!model->hasUnits(u) && model->hasUnits(u->name())) {
                    auto name = u->name();
                    name += "_" + convertToString(++count);
                    u->setName(name);
                }
                model->addUnits(u);
                if (originalName != u->name()) {
                    unitsNamesToReplace.emplace(originalName, u->name());
                }
            }
        }
        findAndReplaceComponentsCnUnitsNames(importedComponentCopy, unitsNamesToReplace);
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
    ModelPtr flatModel;
    if (model == nullptr) {
        auto issue = Issue::IssueImpl::create();
        issue->mPimpl->setReferenceRule(Issue::ReferenceRule::INVALID_ARGUMENT);
        issue->mPimpl->setDescription("The model is null.");
        addIssue(issue);

        return flatModel;
    }

    if (mPimpl->hasImportCycles(model)) {
        return flatModel;
    }

    flatModel = model->clone();

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

void Importer::removeAllModels()
{
    mPimpl->mLibrary.clear();
}

bool Importer::hasImportSource(const ImportSourcePtr &importSource) const
{
    return mPimpl->findImportSource(importSource) != mPimpl->mImports.end();
}

bool Importer::addImportSource(const ImportSourcePtr &importSource)
{
    if (importSource == nullptr) {
        return false;
    }

    // Prevent adding the same import source.
    if (std::find_if(mPimpl->mImports.begin(), mPimpl->mImports.end(),
                     [=](const ImportSourcePtr &importSrc) -> bool { return importSource == importSrc; })
        != mPimpl->mImports.end()) {
        return false;
    }

    mPimpl->mImports.push_back(importSource);
    return true;
}

size_t Importer::importSourceCount() const
{
    return mPimpl->mImports.size();
}

ImportSourcePtr Importer::importSource(size_t index) const
{
    ImportSourcePtr importSrc = nullptr;
    if (index < mPimpl->mImports.size()) {
        importSrc = mPimpl->mImports.at(index);
    }

    return importSrc;
}

bool Importer::removeImportSource(size_t index)
{
    auto importSrc = importSource(index);
    return removeImportSource(importSrc);
}

bool Importer::removeImportSource(const ImportSourcePtr &importSource)
{
    bool status = false;
    auto result = mPimpl->findImportSource(importSource);
    if (result != mPimpl->mImports.end()) {
        mPimpl->mImports.erase(result);
        status = true;
    }
    return status;
}

bool Importer::removeAllImportSources()
{
    mPimpl->mImports.clear();
    return true;
}

} // namespace libcellml

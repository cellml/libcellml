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

#include "libcellml/validator.h"

#include <algorithm>
#include <cmath>
#include <libxml/uri.h>
#include <stdexcept>

#include "libcellml/component.h"
#include "libcellml/importsource.h"
#include "libcellml/model.h"
#include "libcellml/reset.h"
#include "libcellml/units.h"
#include "libcellml/variable.h"

#include "namespaces.h"
#include "utilities.h"
#include "xmldoc.h"
#include "xmlutils.h"

namespace libcellml {

/**
* @brief Validate that equivalent variable pairs in the @p model
* have equivalent units.
* Any errors will be logged in the @c Validator.
*
* Any difference in base units is reported as an error in the @c Validator, but the multiplier difference does not trigger a validator error.
* Where the base units are equivalent, the multiplier may be interpreted as units_of_v1 = (10^multiplier)*units_of_v2
*
* @param model The model containing the variables.
* @param v1 The variable which may contain units.
* @param v2 The equivalent variable which may contain units.
* @param hints String containing error messages to be passed back to the calling function for logging.
* @param multiplier Double returning the effective multiplier mismatch between the units.
*/
bool unitsAreEquivalent(const ModelPtr &model, const VariablePtr &v1, const VariablePtr &v2, std::string &hints, double &multiplier);

/**
* @brief Utility function used by unitsAreEquivalent to compare base units of two variables.
*
* @param model The model containing the variables.
* @param unitMap A list of the exponents of base variables.
* @param uName String name of the current variable being investigated.
* @param standardList Nested map of the conversion between built-in units and the base units they contain.
* @param uExp Exponent of the current unit in its parent.
* @param direction Specify whether we want to increment (1) or decrement (-1).
*/
void updateBaseUnitCount(const ModelPtr &model,
                         std::map<std::string, double> &unitMap,
                         double &multiplier,
                         const std::string &uName,
                         double uExp, double logMult, int direction);

/**
 * @brief The Validator::ValidatorImpl struct.
 *
 * The private implementation for the Validator class.
 */
struct Validator::ValidatorImpl
{
    Validator *mValidator = nullptr;

    /**
     * @brief Validate the given name is unique in the model.
     *
     * The @p name is checked against known names in @p names. If
     * the @p name already exists an issue is added to the validator
     * with the model passed to the issue for further reference.
     *
     * @param model The model the name is used in.
     * @param name The name of the component to validate.
     * @param names The list of component names already used in the model.
     */
    void validateUniqueName(const ModelPtr &model, const std::string &name, std::vector<std::string> &names) const;

    /**
     * @brief Validate the @p component using the CellML 2.0 Specification.
     *
     * Validate the given @p component and its encapsulated entities using
     * the CellML 2.0 Specification. Any issues will be logged in the @c Validator.
     *
     * @param component The component to validate.
     */
    void validateComponent(const ComponentPtr &component);

    /**
     * @brief Validate an imported component.
     *
     * Validates the imported @p component.  Any issues will be
     * logged to the @c Validator.
     *
     * @sa validateComponent
     *
     * @param component The imported component to validate.
     */
    void validateImportedComponent(const ComponentPtr &component) const;

    /**
     * @brief Validate the component tree of the given @p component.
     *
     * Validate the given compoment and all child components of the component.
     *
     * @param model The model the @p component comes from.
     * @param component The @c Component to validate.
     * @param componentNames The list of already used component names used
     * to track repeated component names.
     */
    void validateComponentTree(const ModelPtr &model, const ComponentPtr &component, std::vector<std::string> &componentNames);

    /**
     * @brief Validate the @p units using the CellML 2.0 Specification.
     *
     * Validate the given @p units and its encapsulated entities using
     * the CellML 2.0 Specification. Any issues will be logged in the @c Validator.
     *
     * @param units The units to validate.
     * @param unitsNames A vector list of the name attributes of the @p units and its siblings.
     */
    void validateUnits(const UnitsPtr &units, const std::vector<std::string> &unitsNames) const;

    /**
     * @brief Validate the variable connections in the @p model using the CellML 2.0 Specification.
     *
     * Validate the variable connections in the given @p model using
     * the CellML 2.0 Specification. Any issues will be logged in the @c Validator.
     *
     * @param model The model which may contain variable connections to validate.
     */
    void validateConnections(const ModelPtr &model) const;

    /**
     * @brief Validate the units of the given variables equivalent variables.
     *
     * Validate that the variables that are equivalent to the given variable all
     * have compatible units.
     *
     * @param model The model for which the variable and model belong.
     * @param variable The variable to validate.
     * @param alreadyReported A list of variable pointer pairs.
     */
    void validateEquivalenceUnits(const ModelPtr &model, const VariablePtr &variable, VariableMap &alreadyReported) const;

    /**
     * @brief Validate the structure of the variables equivalences.
     *
     * Validate the structure of the variables equivalences.
     *
     * @param variable The variable to validate.
     */
    void validateEquivalenceStructure(const VariablePtr &variable) const;

    /**
     * @brief Validate the variable interface type.
     *
     * Validate the interface type for the given variable.
     *
     * @param variable The variable to validate.
     * @param alreadyReported A list of variable pointer pairs.
     */
    void validateVariableInterface(const VariablePtr &variable, VariableMap &alreadyReported) const;

    /**
     * @brief Check if the provided @p name is a valid CellML identifier.
     *
     * Checks if the provided @p name is a valid CellML identifier according
     * to the CellML 2.0 specification. This requires a non-zero length Unicode
     * character sequence containing basic Latin alphanumeric characters or
     * underscores that does not begin with a number.
     *
     * @param name The @c std::string name to check the validity of.
     *
     * @return @c true if @name is a valid CellML identifier and @c false otherwise.
     */
    bool isCellmlIdentifier(const std::string &name) const;

    /**
     * @brief Validate the @c unit at index @c index from @p units using the CellML 2.0 Specification.
     *
     * Validate the @c unit at index @c index from @p units using
     * the CellML 2.0 Specification. Any issues will be logged in the @c Validator.
     *
     * @param index The index of the @c unit to validate from @p units.
     * @param units The units to validate.
     * @param unitsNames A vector list of the name attributes of the @p units and its siblings.
     */
    void validateUnitsUnit(size_t index, const UnitsPtr &units, const std::vector<std::string> &unitsNames) const;

    /**
     * @brief Validate the @p variable using the CellML 2.0 Specification.
     *
     * Validate the given @p variable using the CellML 2.0 Specification.
     * Any issues will be logged in the @c Validator.
     *
     * @param variable The variable to validate.
     * @param variableNames A vector list of the name attributes of the @p variable and its siblings.
     */
    void validateVariable(const VariablePtr &variable, const std::vector<std::string> &variableNames) const;

    /**
     * @brief Validate the @p reset using the CellML 2.0 Specification.
     *
     * Examine the @p reset for conformance to the CellML 2.0 specification.  Any
     * issues will be logged in the @c Validator.
     *
     * @param reset The reset to validate.
     * @param component The component the reset belongs to.
     */
    void validateReset(const ResetPtr &reset, const ComponentPtr &component);

    /**
     * @brief Validate the math @p input @c std::string.
     *
     * Validate the math @p input @c std::string using the CellML 2.0 Specification and
     * the W3C MathML DTD. Any issues will be logged in the @c Validator.
     *
     * @param input The math @c std::string to validate.
     * @param component The component containing the math @c std::string to be validated.
     */
    void validateMath(const std::string &input, const ComponentPtr &component);

    /**
     * @brief Traverse the node tree for invalid MathML elements.
     *
     * Traverse the Xml node tree checking that all MathML elements are listed in the
     * supported MathML elements table from the CellML specification 2.0 document.
     *
     * @param node The node to check children and sibling nodes.
     * @param component The component the MathML belongs to.
     */
    void validateMathMLElements(const XmlNodePtr &node, const ComponentPtr &component);

    void validateAndCleanCnNode(const XmlNodePtr &node, const ComponentPtr &component) const;
    void validateAndCleanCiNode(const XmlNodePtr &node, const ComponentPtr &component, const std::vector<std::string> &variableNames) const;
    bool validateCnUnits(const ComponentPtr &component, const std::string &unitsName, const std::string &textNode) const;

    /**
     * @brief Validate CellML variables and units in MathML @c ci and @c cn variables. Removes CellML units from the @p node.
     *
     * Validates CellML variables found in MathML @c ci elements. Validates @c cellml:units
     * attributes found on @c cn elements and removes them from the @c XmlNode @p node to leave MathML that may then
     * be validated using the MathML DTD.
     *
     * @param node The @c XmlNode to validate CellML entities on and remove @c cellml:units from.
     * @param component The component that the math @c XmlNode @p node is contained within.
     * @param variableNames A @c vector list of the names of variables found within the @p component.
     */
    void validateAndCleanMathCiCnNodes(XmlNodePtr &node, const ComponentPtr &component, const std::vector<std::string> &variableNames);

    /**
     * @brief Check if the provided @p node is a supported MathML element.
     *
     * Checks if the provided @p node is one of the supported MathML elements defined in the table
     * of supported MathML elements from the CellML specification version 2.0 document.
     *
     * @param node The @c XmlNode node to check against the list of supported MathML elements.
     * @return @c true if @node is a supported MathML element and @c false otherwise.
     */
    bool isSupportedMathMLElement(const XmlNodePtr &node);

    /**
    * @brief Checks dependency hierarchies of units in the model.
    *
    * @param model The model containing the units to be tested.
    */
    void validateNoUnitsAreCyclic(const ModelPtr &model);

    /**
    * @brief Utility function called recursively by validateNoUnitsAreCyclic.
    *
    * @param model The model containing the units to be tested.
    * @param parent The current @c Units pointer to test.
    * @param history A vector of the chained dependencies. Cyclic variables exist where the first and last units are equal.
    * @param errorList An array of loops, returned so that the reported issues are not too repetitive.
    */
    void checkUnitForCycles(const ModelPtr &model, const UnitsPtr &parent,
                            std::vector<std::string> &history,
                            std::vector<std::vector<std::string>> &errorList);
};

Validator::Validator()
    : mPimpl(new ValidatorImpl())
{
    mPimpl->mValidator = this;
}

Validator::~Validator()
{
    delete mPimpl;
}

ValidatorPtr Validator::create() noexcept
{
    return std::shared_ptr<Validator> {new Validator {}};
}

void Validator::validateModel(const ModelPtr &model)
{
    // Clear any pre-existing issues in ths validator instance.
    removeAllIssues();
    // Check for a valid name attribute.
    if (!mPimpl->isCellmlIdentifier(model->name())) {
        IssuePtr issue = Issue::create();
        issue->setDescription("Model does not have a valid name attribute.");
        issue->setModel(model);
        issue->setReferenceRule(Issue::ReferenceRule::MODEL_NAME);
        addIssue(issue);
    }
    // Check for components in this model.
    if (model->componentCount() > 0) {
        std::vector<std::string> componentNames;
        for (size_t i = 0; i < model->componentCount(); ++i) {
            ComponentPtr component = model->component(i);
            mPimpl->validateComponentTree(model, component, componentNames);
        }
    }
    // Check for units in this model.
    if (model->unitsCount() > 0) {
        std::vector<std::string> unitsNames;
        std::vector<std::string> unitsRefs;
        std::vector<std::string> unitsImportSources;
        for (size_t i = 0; i < model->unitsCount(); ++i) {
            UnitsPtr units = model->units(i);
            std::string unitsName = units->name();
            if (!unitsName.empty()) {
                if (units->isImport()) {
                    // Check for a units_ref.
                    std::string unitsRef = units->importReference();
                    std::string importSource = units->importSource()->url();
                    bool foundImportIssue = false;
                    if (!mPimpl->isCellmlIdentifier(unitsRef)) {
                        IssuePtr issue = Issue::create();
                        issue->setDescription("Imported units '" + unitsName + "' does not have a valid units_ref attribute.");
                        issue->setUnits(units);
                        issue->setReferenceRule(Issue::ReferenceRule::IMPORT_UNITS_REF);
                        addIssue(issue);
                        foundImportIssue = true;
                    }
                    // Check for a xlink:href.
                    // TODO: check this id against the XLink spec (see CellML Spec 5.1.1).
                    if (importSource.empty()) {
                        IssuePtr issue = Issue::create();
                        issue->setDescription("Import of units '" + unitsName + "' does not have a valid locator xlink:href attribute.");
                        issue->setImportSource(units->importSource());
                        issue->setReferenceRule(Issue::ReferenceRule::IMPORT_HREF);
                        addIssue(issue);
                        foundImportIssue = true;
                    }
                    // Check if we already have another import from the same source with the same units_ref.
                    // (This looks for matching entries at the same position in the source and ref vectors).
                    if (!unitsImportSources.empty() && (!foundImportIssue)) {
                        auto usedImportSource = std::find(unitsImportSources.begin(), unitsImportSources.end(), importSource);
                        auto usedImportSourceAt = usedImportSource - unitsImportSources.begin();
                        auto usedUnitsRefs = std::find(unitsRefs.begin(), unitsRefs.end(), unitsRef);
                        auto usedUnitsRefsAt = usedUnitsRefs - unitsRefs.begin();
                        if ((usedImportSource != unitsImportSources.end()) && (usedUnitsRefs != unitsRefs.end()) && (usedUnitsRefsAt == usedImportSourceAt)) {
                            IssuePtr issue = Issue::create();
                            issue->setDescription("Model '" + model->name() + "' contains multiple imported units from '" + importSource + "' with the same units_ref attribute '" + unitsRef + "'.");
                            issue->setModel(model);
                            issue->setReferenceRule(Issue::ReferenceRule::IMPORT_UNITS_REF);
                            addIssue(issue);
                        }
                    }
                    // Push back the unique sources and refs.
                    unitsImportSources.push_back(importSource);
                    unitsRefs.push_back(unitsRef);
                }
                // Check for duplicate units names in this model.
                if (std::find(unitsNames.begin(), unitsNames.end(), unitsName) != unitsNames.end()) {
                    IssuePtr issue = Issue::create();
                    issue->setDescription("Model '" + model->name() + "' contains multiple units with the name '" + unitsName + "'. Valid units names must be unique to their model.");
                    issue->setModel(model);
                    issue->setReferenceRule(Issue::ReferenceRule::UNITS_NAME_UNIQUE);
                    addIssue(issue);
                }
                unitsNames.push_back(unitsName);
            }
        }
        for (size_t i = 0; i < model->unitsCount(); ++i) {
            // Validate units.
            UnitsPtr units = model->units(i);
            mPimpl->validateUnits(units, unitsNames);
        }
    }

    // Check that unit relationships are not cyclical.
    if (model->unitsCount() > 0) {
        mPimpl->validateNoUnitsAreCyclic(model);
    }

    // Validate any connections / variable equivalence networks in the model.
    mPimpl->validateConnections(model);
}

void Validator::ValidatorImpl::validateUniqueName(const ModelPtr &model, const std::string &name, std::vector<std::string> &names) const
{
    if (!name.empty()) {
        if (std::find(names.begin(), names.end(), name) != names.end()) {
            IssuePtr issue = Issue::create();
            issue->setDescription("Model '" + model->name() + "' contains multiple components with the name '" + name + "'. Valid component names must be unique to their model.");
            issue->setModel(model);
            mValidator->addIssue(issue);
        } else {
            names.push_back(name);
        }
    }
}

void Validator::ValidatorImpl::validateComponentTree(const ModelPtr &model, const ComponentPtr &component, std::vector<std::string> &componentNames)
{
    validateUniqueName(model, component->name(), componentNames);
    for (size_t i = 0; i < component->componentCount(); ++i) {
        auto childComponent = component->component(i);
        validateComponentTree(model, childComponent, componentNames);
    }
    if (component->isImport()) {
        validateImportedComponent(component);
    } else {
        validateComponent(component);
    }
}

void Validator::ValidatorImpl::validateImportedComponent(const ComponentPtr &component) const
{
    if (!isCellmlIdentifier(component->name())) {
        IssuePtr issue = Issue::create();
        issue->setComponent(component);
        issue->setDescription("Imported component does not have a valid name attribute.");
        issue->setReferenceRule(Issue::ReferenceRule::IMPORT_COMPONENT_NAME);
        mValidator->addIssue(issue);
    }

    // Check for a component_ref; assumes imported if the import source is not null.
    std::string componentRef = component->importReference();
    std::string importSource = component->importSource()->url();
    std::string componentName = component->name();

    if (!isCellmlIdentifier(componentRef)) {
        IssuePtr issue = Issue::create();
        issue->setDescription("Imported component '" + componentName + "' does not have a valid component_ref attribute.");
        issue->setComponent(component);
        issue->setReferenceRule(Issue::ReferenceRule::IMPORT_COMPONENT_REF);
        mValidator->addIssue(issue);
    }
    if (importSource.empty()) {
        IssuePtr issue = Issue::create();
        issue->setDescription("Import of component '" + componentName + "' does not have a valid locator xlink:href attribute.");
        issue->setImportSource(component->importSource());
        issue->setReferenceRule(Issue::ReferenceRule::IMPORT_HREF);
        mValidator->addIssue(issue);
    } else {
        xmlURIPtr uri = xmlParseURI(importSource.c_str());
        if (uri == nullptr) {
            IssuePtr issue = Issue::create();
            issue->setDescription("Import of component '" + componentName + "' has an invalid URI in the href attribute.");
            issue->setImportSource(component->importSource());
            issue->setReferenceRule(Issue::ReferenceRule::IMPORT_HREF);
            mValidator->addIssue(issue);

        } else {
            xmlFreeURI(uri);
        }
    }
}

void Validator::ValidatorImpl::validateComponent(const ComponentPtr &component)
{
    // Check for a valid name attribute.
    if (!isCellmlIdentifier(component->name())) {
        IssuePtr issue = Issue::create();
        issue->setComponent(component);
        issue->setDescription("Component does not have a valid name attribute.");
        issue->setReferenceRule(Issue::ReferenceRule::COMPONENT_NAME);
        mValidator->addIssue(issue);
    }
    // Check for variables in this component.
    std::vector<std::string> variableNames;
    if (component->variableCount() > 0) {
        // Check for duplicate variable names and construct vector of valid names in case
        // we have a variable initial_value set by reference.
        for (size_t i = 0; i < component->variableCount(); ++i) {
            std::string variableName = component->variable(i)->name();
            if (!variableName.empty()) {
                if (std::find(variableNames.begin(), variableNames.end(), variableName) != variableNames.end()) {
                    IssuePtr issue = Issue::create();
                    issue->setDescription("Component '" + component->name() + "' contains multiple variables with the name '" + variableName + "'. Valid variable names must be unique to their component.");
                    issue->setComponent(component);
                    issue->setReferenceRule(Issue::ReferenceRule::VARIABLE_NAME);
                    mValidator->addIssue(issue);
                }
                variableNames.push_back(variableName);
            }
        }
        // Validate variable(s).
        for (size_t i = 0; i < component->variableCount(); ++i) {
            VariablePtr variable = component->variable(i);
            validateVariable(variable, variableNames);
        }
    }
    // Check for resets in this component
    for (size_t i = 0; i < component->resetCount(); ++i) {
        ResetPtr reset = component->reset(i);
        validateReset(reset, component);
    }

    // Validate math through the private implementation (for XML handling).
    if (!component->math().empty()) {
        validateMath(component->math(), component);
    }
}

void Validator::ValidatorImpl::validateUnits(const UnitsPtr &units, const std::vector<std::string> &unitsNames) const
{
    // Check for a valid name attribute.
    if (!isCellmlIdentifier(units->name())) {
        IssuePtr issue = Issue::create();
        issue->setUnits(units);
        if (units->isImport()) {
            issue->setDescription("Imported units does not have a valid name attribute.");
            issue->setReferenceRule(Issue::ReferenceRule::IMPORT_UNITS_NAME);
        } else {
            issue->setDescription("Units does not have a valid name attribute.");
            issue->setReferenceRule(Issue::ReferenceRule::UNITS_NAME);
        }
        mValidator->addIssue(issue);
    } else {
        // Check for a matching standard units.
        if (isStandardUnitName(units->name())) {
            IssuePtr issue = Issue::create();
            issue->setDescription("Units is named '" + units->name() + "' which is a protected standard unit name.");
            issue->setUnits(units);
            issue->setReferenceRule(Issue::ReferenceRule::UNITS_STANDARD);
            mValidator->addIssue(issue);
        }
    }
    if (units->unitCount() > 0) {
        for (size_t i = 0; i < units->unitCount(); ++i) {
            validateUnitsUnit(i, units, unitsNames);
        }
    }
}

void Validator::ValidatorImpl::validateUnitsUnit(size_t index, const UnitsPtr &units, const std::vector<std::string> &unitsNames) const
{
    // Validate the unit at the given index.
    std::string reference;
    std::string prefix;
    std::string id;
    double exponent;
    double multiplier;

    units->unitAttributes(index, reference, prefix, exponent, multiplier, id);
    if (isCellmlIdentifier(reference)) {
        if ((std::find(unitsNames.begin(), unitsNames.end(), reference) == unitsNames.end()) && (!isStandardUnitName(reference))) {
            IssuePtr issue = Issue::create();
            issue->setDescription("Units reference '" + reference + "' in units '" + units->name() + "' is not a valid reference to a local units or a standard unit type.");
            issue->setUnits(units);
            issue->setReferenceRule(Issue::ReferenceRule::UNIT_UNITS_REF);
            mValidator->addIssue(issue);
        }
    } else {
        IssuePtr issue = Issue::create();
        issue->setDescription("Unit in units '" + units->name() + "' does not have a valid units reference.");
        issue->setUnits(units);
        issue->setReferenceRule(Issue::ReferenceRule::UNIT_UNITS_REF);
        mValidator->addIssue(issue);
    }
    if (!prefix.empty()) {
        if (!isStandardPrefixName(prefix)) {
            if (!isCellMLInteger(prefix)) {
                IssuePtr issue = Issue::create();
                issue->setDescription("Prefix '" + prefix + "' of a unit referencing '" + reference + "' in units '" + units->name() + "' is not a valid integer or an SI prefix.");
                issue->setUnits(units);
                issue->setReferenceRule(Issue::ReferenceRule::UNIT_PREFIX);
                mValidator->addIssue(issue);
            } else {
                try {
                    int test = std::stoi(prefix);
                    (void)test;
                } catch (std::out_of_range &) {
                    IssuePtr issue = Issue::create();
                    issue->setDescription("Prefix '" + prefix + "' of a unit referencing '" + reference + "' in units '" + units->name() + "' is out of the integer range.");
                    issue->setUnits(units);
                    issue->setReferenceRule(Issue::ReferenceRule::UNIT_PREFIX);
                    mValidator->addIssue(issue);
                }
            }
        }
    }
}

void Validator::ValidatorImpl::validateVariable(const VariablePtr &variable, const std::vector<std::string> &variableNames) const
{
    // Check for a valid name attribute.
    if (!isCellmlIdentifier(variable->name())) {
        IssuePtr issue = Issue::create();
        issue->setDescription("Variable does not have a valid name attribute.");
        issue->setVariable(variable);
        issue->setReferenceRule(Issue::ReferenceRule::VARIABLE_NAME);
        mValidator->addIssue(issue);
    }
    // Check for a valid units attribute.
    std::string unitsName = variable->units() != nullptr ? variable->units()->name() : "";
    if (!isCellmlIdentifier(unitsName)) {
        IssuePtr issue = Issue::create();
        issue->setDescription("Variable '" + variable->name() + "' does not have a valid units attribute.");
        issue->setVariable(variable);
        issue->setReferenceRule(Issue::ReferenceRule::VARIABLE_UNITS);
        mValidator->addIssue(issue);
    } else if (!isStandardUnitName(unitsName)) {
        ComponentPtr component = owningComponent(variable);
        ModelPtr model = owningModel(component);
        if ((model != nullptr) && !model->hasUnits(variable->units())) {
            IssuePtr issue = Issue::create();
            issue->setDescription("Variable '" + variable->name() + "' in component '" + component->name() + "' has a units reference '" + unitsName + "' which is neither standard nor defined in the parent model.");
            issue->setVariable(variable);
            issue->setReferenceRule(Issue::ReferenceRule::VARIABLE_UNITS);
            mValidator->addIssue(issue);
        }
    }
    // Check for a valid interface attribute.
    if (!variable->interfaceType().empty()) {
        std::string interfaceType = variable->interfaceType();
        if ((interfaceType != "public") && (interfaceType != "private") && (interfaceType != "none") && (interfaceType != "public_and_private")) {
            IssuePtr issue = Issue::create();
            issue->setDescription("Variable '" + variable->name() + "' has an invalid interface attribute value '" + interfaceType + "'.");
            issue->setVariable(variable);
            issue->setReferenceRule(Issue::ReferenceRule::VARIABLE_INTERFACE);
            mValidator->addIssue(issue);
        }
    }
    // Check for a valid initial value attribute.
    if (!variable->initialValue().empty()) {
        std::string initialValue = variable->initialValue();
        // Check if initial value is a variable reference
        if (!(std::find(variableNames.begin(), variableNames.end(), initialValue) != variableNames.end())) {
            // Otherwise, check that the initial value can be converted to a double
            if (!isCellMLReal(initialValue)) {
                IssuePtr issue = Issue::create();
                issue->setDescription("Variable '" + variable->name() + "' has an invalid initial value '" + initialValue + "'. Initial values must be a real number string or a variable reference.");
                issue->setVariable(variable);
                issue->setReferenceRule(Issue::ReferenceRule::VARIABLE_INITIAL_VALUE);
                mValidator->addIssue(issue);
            }
        }
    }
}

void Validator::ValidatorImpl::validateReset(const ResetPtr &reset, const ComponentPtr &component)
{
    bool noOrder = false;
    bool noVariable = false;
    bool noTestVariable = false;
    bool noTestValue = false;
    bool noResetValue = false;
    bool varOutsideComponent = false;
    bool testVarOutsideComponent = false;
    std::string varParentName;
    std::string testVarParentName;

    std::string description = "Reset in component '" + component->name() + "' ";

    if (reset->isOrderSet()) {
        description += "with order '" + convertToString(reset->order()) + "', ";
    } else {
        noOrder = true;
    }

    if (reset->variable() == nullptr) {
        noVariable = true;
    } else {
        description += "with variable '" + reset->variable()->name() + "', ";
        auto var = reset->variable();
        auto varParent = owningComponent(var);
        varParentName = varParent->name();
        if (varParentName != component->name()) {
            varOutsideComponent = true;
        }
    }

    if (reset->testVariable() == nullptr) {
        noTestVariable = true;
    } else {
        description += "with test_variable '" + reset->testVariable()->name() + "', ";

        auto var = reset->testVariable();
        auto varParent = owningComponent(var);
        testVarParentName = varParent->name();
        if (testVarParentName != component->name()) {
            testVarOutsideComponent = true;
        }
    }

    // Check that the contents of test_value and reset_value are valid MathML
    std::string testValueString = reset->testValue();
    std::string resetValueString = reset->resetValue();

    if ((testValueString.empty()) || (std::all_of(testValueString.begin(), testValueString.end(), isspace))) {
        noTestValue = true;
    } else {
        validateMath(testValueString, component);
    }
    if ((resetValueString.empty()) || (std::all_of(resetValueString.begin(), resetValueString.end(), isspace))) {
        noResetValue = true;
    } else {
        validateMath(resetValueString, component);
    }

    if (noOrder) {
        IssuePtr issue = Issue::create();
        issue->setDescription(description + "does not have an order set.");
        issue->setComponent(component);
        issue->setReferenceRule(Issue::ReferenceRule::RESET_ORDER);
        mValidator->addIssue(issue);
    }
    if (noVariable) {
        IssuePtr issue = Issue::create();
        issue->setDescription(description + "does not reference a variable.");
        issue->setReset(reset);
        issue->setReferenceRule(Issue::ReferenceRule::RESET_VARIABLE_REFERENCE);
        mValidator->addIssue(issue);
    }
    if (noTestVariable) {
        IssuePtr issue = Issue::create();
        issue->setDescription(description + "does not reference a test_variable.");
        issue->setReset(reset);
        issue->setReferenceRule(Issue::ReferenceRule::RESET_TEST_VARIABLE_REFERENCE);
        mValidator->addIssue(issue);
    }
    if (noTestValue) {
        IssuePtr issue = Issue::create();
        issue->setDescription(description + "does not have a test_value specified.");
        issue->setReset(reset);
        issue->setReferenceRule(Issue::ReferenceRule::RESET_TEST_VALUE);
        mValidator->addIssue(issue);
    }
    if (noResetValue) {
        IssuePtr issue = Issue::create();
        issue->setDescription(description + "does not have a reset_value specified.");
        issue->setReset(reset);
        issue->setReferenceRule(Issue::ReferenceRule::RESET_RESET_VALUE);
        mValidator->addIssue(issue);
    }
    if (varOutsideComponent) {
        IssuePtr issue = Issue::create();
        issue->setDescription(description + "refers to a variable '" + reset->variable()->name() + "' in a different component '" + varParentName + "'.");
        issue->setReset(reset);
        issue->setReferenceRule(Issue::ReferenceRule::RESET_VARIABLE_REFERENCE);
        mValidator->addIssue(issue);
    }
    if (testVarOutsideComponent) {
        IssuePtr issue = Issue::create();
        issue->setDescription(description + "refers to a test_variable '" + reset->testVariable()->name() + "' in a different component '" + testVarParentName + "'.");
        issue->setReset(reset);
        issue->setReferenceRule(Issue::ReferenceRule::RESET_TEST_VARIABLE_REFERENCE);
        mValidator->addIssue(issue);
    }
}

void Validator::ValidatorImpl::validateMath(const std::string &input, const ComponentPtr &component)
{
    // Parse as XML first.
    std::vector<XmlDocPtr> docs = multiRootXml(input);
    for (const auto &doc : docs) {
        // Copy any XML parsing issues into the common validator issue handler.
        if (doc->xmlErrorCount() > 0) {
            for (size_t i = 0; i < doc->xmlErrorCount(); ++i) {
                IssuePtr issue = Issue::create();
                issue->setDescription("LibXml2 error: " + doc->xmlError(i));
                issue->setCause(Issue::Cause::XML);
                mValidator->addIssue(issue);
            }
        }
        XmlNodePtr node = doc->rootNode();
        if (node == nullptr) {
            IssuePtr issue = Issue::create();
            issue->setDescription("Could not get a valid XML root node from the math on component '" + component->name() + "'.");
            issue->setCause(Issue::Cause::XML);
            issue->setComponent(component);
            mValidator->addIssue(issue);
            return;
        }
        if (!node->isMathmlElement("math")) {
            IssuePtr issue = Issue::create();
            issue->setDescription("Math root node is of invalid type '" + node->name() + "' on component '" + component->name() + "'. A valid math root node should be of type 'math'.");
            issue->setComponent(component);
            issue->setCause(Issue::Cause::XML);
            mValidator->addIssue(issue);
            return;
        }

        XmlNodePtr nodeCopy = node;
        std::vector<std::string> variableNames;
        for (size_t i = 0; i < component->variableCount(); ++i) {
            std::string variableName = component->variable(i)->name();
            if (std::find(variableNames.begin(), variableNames.end(), variableName) == variableNames.end()) {
                variableNames.push_back(variableName);
            }
        }

        validateMathMLElements(nodeCopy, component);

        // Iterate through ci/cn elements and remove cellml units attributes.
        XmlNodePtr mathNode = node;
        validateAndCleanMathCiCnNodes(node, component, variableNames);

        // Remove the cellml namespace definition.
        if (mathNode->hasNamespaceDefinition(CELLML_2_0_NS)) {
            mathNode->removeNamespaceDefinition(CELLML_2_0_NS);
        }

        // Get the MathML string with cellml:units attributes and namespace already removed.
        std::string cleanMathml = mathNode->convertToString();

        // Parse/validate the clean math string with the W3C MathML DTD.
        XmlDocPtr mathmlDoc = std::make_shared<XmlDoc>();
        mathmlDoc->parseMathML(cleanMathml);
        // Copy any MathML validation errors into the common validator error handler.
        if (mathmlDoc->xmlErrorCount() > 0) {
            for (size_t i = 0; i < mathmlDoc->xmlErrorCount(); ++i) {
                IssuePtr issue = Issue::create();
                issue->setDescription("W3C MathML DTD error: " + mathmlDoc->xmlError(i));
                issue->setComponent(component);
                issue->setCause(Issue::Cause::MATHML);
                mValidator->addIssue(issue);
            }
        }
    }
}

bool Validator::ValidatorImpl::validateCnUnits(const ComponentPtr &component, const std::string &unitsName, const std::string &textNode) const
{
    if (isCellmlIdentifier(unitsName)) {
        return true;
    }

    IssuePtr issue = Issue::create();
    issue->setDescription("Math cn element with the value '" + textNode + "' does not have a valid cellml:units attribute.");
    issue->setComponent(component);
    issue->setCause(Issue::Cause::MATHML);
    mValidator->addIssue(issue);

    return false;
}

std::string text(const XmlNodePtr &node)
{
    if (node != nullptr) {
        if (node->isText()) {
            return node->convertToStrippedString();
        }
    }
    return {};
}

void Validator::ValidatorImpl::validateAndCleanCnNode(const XmlNodePtr &node, const ComponentPtr &component) const
{
    // Get cellml:units attribute.
    XmlAttributePtr attribute = node->firstAttribute();
    std::string unitsName;
    XmlAttributePtr unitsAttribute = nullptr;
    std::vector<XmlAttributePtr> cellmlAttributesToRemove;
    while (attribute) {
        if (!attribute->value().empty()) {
            if (attribute->isCellmlType("units")) {
                unitsName = attribute->value();
                unitsAttribute = attribute;
                cellmlAttributesToRemove.push_back(attribute);
            } else if (attribute->inNamespaceUri(CELLML_2_0_NS)) {
                cellmlAttributesToRemove.push_back(attribute);
                IssuePtr issue = Issue::create();
                issue->setDescription("Math " + node->name() + " element has an invalid attribute type '" + attribute->name() + "' in the cellml namespace.  Attribute 'units' is the only CellML namespace attribute allowed.");
                issue->setComponent(component);
                issue->setCause(Issue::Cause::MATHML);
                mValidator->addIssue(issue);
            }
        }
        attribute = attribute->next();
    }

    XmlNodePtr childNode = node->firstChild();
    std::string textInNode = text(childNode);
    // Check that cellml:units has been set.
    bool checkUnitsIsInModel = validateCnUnits(component, unitsName, textInNode);

    // Check that a specified units is valid.
    if (checkUnitsIsInModel) {
        // Check for a matching units in this model.
        ModelPtr model = owningModel(component);
        if (!model->hasUnits(unitsName)) {
            // Check for a matching standard units.
            if (!isStandardUnitName(unitsName)) {
                IssuePtr issue = Issue::create();
                issue->setDescription("Math has a " + node->name() + " element with a cellml:units attribute '" + unitsName + "' that is not a valid reference to units in the model '" + model->name() + "' or a standard unit.");
                issue->setComponent(component);
                issue->setCause(Issue::Cause::MATHML);
                mValidator->addIssue(issue);
            }
        }
    }
    // Now that we've validated this XML node's cellml:units attribute, remove it from the node.
    // This is done so we can validate a "clean" MathML string using the MathML DTD. The math
    // string stored on the component will not be affected.
    for (const auto &cellmlAttribute : cellmlAttributesToRemove) {
        cellmlAttribute->removeAttribute();
    }
    if (node->hasNamespaceDefinition(CELLML_2_0_NS)) {
        node->removeNamespaceDefinition(CELLML_2_0_NS);
    }
}

void Validator::ValidatorImpl::validateAndCleanCiNode(const XmlNodePtr &node, const ComponentPtr &component, const std::vector<std::string> &variableNames) const
{
    XmlNodePtr childNode = node->firstChild();
    std::string textInNode = text(childNode);
    if (!textInNode.empty()) {
        // Check whether we can find this text as a variable name in this component.
        if (std::find(variableNames.begin(), variableNames.end(), textInNode) == variableNames.end()) {
            IssuePtr issue = Issue::create();
            issue->setDescription("MathML ci element has the child text '" + textInNode + "' which does not correspond with any variable names present in component '" + component->name() + "'.");
            issue->setComponent(component);
            issue->setCause(Issue::Cause::MATHML);
            mValidator->addIssue(issue);
        }
    }
}

void Validator::ValidatorImpl::validateAndCleanMathCiCnNodes(XmlNodePtr &node, const ComponentPtr &component, const std::vector<std::string> &variableNames)
{
    if (node->isMathmlElement("cn")) {
        validateAndCleanCnNode(node, component);
    } else if (node->isMathmlElement("ci")) {
        validateAndCleanCiNode(node, component, variableNames);
    }
    // Check children for ci/cn.
    XmlNodePtr childNode = node->firstChild();
    if (childNode != nullptr) {
        validateAndCleanMathCiCnNodes(childNode, component, variableNames);
    }
    // Check siblings for ci/cn.
    node = node->next();
    if (node != nullptr) {
        validateAndCleanMathCiCnNodes(node, component, variableNames);
    }
}

void Validator::ValidatorImpl::validateMathMLElements(const XmlNodePtr &node, const ComponentPtr &component)
{
    XmlNodePtr childNode = node->firstChild();
    if (childNode != nullptr) {
        if (!childNode->isComment() && !childNode->isText() && !isSupportedMathMLElement(childNode)) {
            IssuePtr issue = Issue::create();
            issue->setDescription("Math has a '" + childNode->name() + "' element that is not a supported MathML element.");
            issue->setComponent(component);
            issue->setCause(Issue::Cause::MATHML);
            mValidator->addIssue(issue);
        }
        validateMathMLElements(childNode, component);
    }

    XmlNodePtr nextNode = node->next();
    if (nextNode != nullptr) {
        if (!nextNode->isComment() && !nextNode->isText() && !isSupportedMathMLElement(nextNode)) {
            IssuePtr issue = Issue::create();
            issue->setDescription("Math has a '" + nextNode->name() + "' element that is not a supported MathML element.");
            issue->setComponent(component);
            issue->setCause(Issue::Cause::MATHML);
            mValidator->addIssue(issue);
        }
        validateMathMLElements(nextNode, component);
    }
}

/**
 * @brief Test to see if the given variables are reachable from their parent components.
 *
 * Determine if the variables parents are reachable from one another.  That is they either
 * have a parent/child relationship or a sibling relationship in the model's component
 * hierarchy.
 *
 * Both variables must have a valid parent.
 *
 * @param variable1 The first variable.
 * @param variable2 The second variable.
 *
 * @return @c true if the parents of the given variables are reachable in the model component
 * hierarchy, @c false otherwise.
 */
bool reachableEquivalence(const VariablePtr &variable1, const VariablePtr &variable2)
{
    auto parent1 = variable1->parent();
    auto parent2 = variable2->parent();

    return isEntityChildOf(parent1, parent2)
           || isEntityChildOf(parent2, parent1)
           || areEntitiesSiblings(parent1, parent2);
}

bool interfaceTypeIsCompatible(Variable::InterfaceType interfaceTypeMinimumRequired, const std::string &interfaceTypeCompatibleWith)
{
    std::string interfaceTypeMinimumRequiredString = interfaceTypeToString.find(interfaceTypeMinimumRequired)->second;
    return interfaceTypeCompatibleWith.find(interfaceTypeMinimumRequiredString) != std::string::npos;
}

void Validator::ValidatorImpl::validateVariableInterface(const VariablePtr &variable, VariableMap &alreadyReported) const
{
    Variable::InterfaceType interfaceType = determineInterfaceType(variable);
    auto component = owningComponent(variable);
    std::string componentName = component->name();
    if (interfaceType == Variable::InterfaceType::NONE) {
        for (size_t index = 0; index < variable->equivalentVariableCount(); ++index) {
            const auto equivalentVariable = variable->equivalentVariable(index);
            auto equivalentComponent = owningComponent(equivalentVariable);
            if (equivalentComponent != nullptr && !reachableEquivalence(variable, equivalentVariable)) {
                VariablePair reversePair = std::make_pair(equivalentVariable, variable);
                auto it = std::find(alreadyReported.begin(), alreadyReported.end(), reversePair);
                if (it == alreadyReported.end()) {
                    VariablePair pair = std::make_pair(variable, equivalentVariable);
                    alreadyReported.push_back(pair);
                    std::string equivalentComponentName = equivalentComponent->name();

                    IssuePtr err = Issue::create();
                    err->setDescription("The equivalence between '" + variable->name() + "' in component '" + componentName + "'  and '" + equivalentVariable->name() + "' in component '" + equivalentComponentName + "' is invalid. Component '" + componentName + "' and '" + equivalentComponentName + "' are neither siblings nor in a parent/child relationship.");
                    err->setVariable(variable);
                    err->setCause(Issue::Cause::CONNECTION);
                    mValidator->addIssue(err);
                }
            }
        }
    } else {
        auto interfaceTypeString = variable->interfaceType();
        if (!interfaceTypeIsCompatible(interfaceType, interfaceTypeString)) {
            IssuePtr err = Issue::create();
            if (interfaceTypeString.empty()) {
                err->setDescription("Variable '" + variable->name() + "' in component '" + componentName + "' has no interface type set. The interface type required is '" + interfaceTypeToString.find(interfaceType)->second + "'.");
            } else {
                err->setDescription("Variable '" + variable->name() + "' in component '" + componentName + "' has an interface type set to '" + interfaceTypeString + "' which is not the correct interface type for this variable. The interface type required is '" + interfaceTypeToString.find(interfaceType)->second + "'.");
            }
            err->setVariable(variable);
            err->setCause(Issue::Cause::CONNECTION);
            mValidator->addIssue(err);
        }
    }
}

void Validator::ValidatorImpl::validateEquivalenceUnits(const ModelPtr &model, const VariablePtr &variable, VariableMap &alreadyReported) const
{
    std::string hints;
    for (size_t index = 0; index < variable->equivalentVariableCount(); ++index) {
        auto equivalentVariable = variable->equivalentVariable(index);
        double multiplier = 0.0;
        if (!unitsAreEquivalent(model, variable, equivalentVariable, hints, multiplier)) {
            VariablePair reversePair = std::make_pair(equivalentVariable, variable);
            auto it = std::find(alreadyReported.begin(), alreadyReported.end(), reversePair);
            if (it == alreadyReported.end()) {
                VariablePair pair = std::make_pair(variable, equivalentVariable);
                ComponentPtr parent1 = owningComponent(variable);
                ComponentPtr parent2 = owningComponent(equivalentVariable);
                alreadyReported.push_back(pair);
                auto unitsName = variable->units() == nullptr ? "" : variable->units()->name();
                auto equivalentUnitsName = equivalentVariable->units() == nullptr ? "" : equivalentVariable->units()->name();
                IssuePtr err = Issue::create();
                err->setDescription("Variable '" + variable->name() + "' in component '" + parent1->name() + "' has units of '" + unitsName + "' and an equivalent variable '" + equivalentVariable->name() + "' in component '" + parent2->name() + "' with non-matching units of '" + equivalentUnitsName + "'. The mismatch is: " + hints);
                err->setModel(model);
                err->setCause(Issue::Cause::UNITS);
                err->setReferenceRule(Issue::ReferenceRule::MAP_VARIABLES_IDENTICAL_UNIT_REDUCTION);
                mValidator->addIssue(err);
            }
        }
    }
}

void Validator::ValidatorImpl::validateEquivalenceStructure(const VariablePtr &variable) const
{
    for (size_t index = 0; index < variable->equivalentVariableCount(); ++index) {
        auto equivalentVariable = variable->equivalentVariable(index);
        if (equivalentVariable->hasEquivalentVariable(variable)) {
            auto component = owningComponent(equivalentVariable);
            if (component == nullptr) {
                IssuePtr err = Issue::create();
                err->setDescription("Variable '" + equivalentVariable->name() + "' is an equivalent variable to '" + variable->name() + "' but '" + equivalentVariable->name() + "' has no parent component.");
                err->setVariable(equivalentVariable);
                err->setCause(Issue::Cause::CONNECTION);
                mValidator->addIssue(err);
            }
        }
    }
}

void Validator::ValidatorImpl::validateConnections(const ModelPtr &model) const
{
    VariableMap interfaceErrorsAlreadyReported;
    VariableMap equivalentUnitErrorsAlreadyReported;

    VariablePtrs variables;

    for (size_t index = 0; index < model->componentCount(); ++index) {
        findAllVariablesWithEquivalences(model->component(index), variables);
    }

    for (const VariablePtr &variable : variables) {
        validateVariableInterface(variable, interfaceErrorsAlreadyReported);
        validateEquivalenceUnits(model, variable, equivalentUnitErrorsAlreadyReported);
        validateEquivalenceStructure(variable);
    }
}

bool Validator::ValidatorImpl::isSupportedMathMLElement(const XmlNodePtr &node)
{
    return (node->namespaceUri() == MATHML_NS)
           && std::find(supportedMathMLElements.begin(), supportedMathMLElements.end(), node->name()) != supportedMathMLElements.end();
}

bool Validator::ValidatorImpl::isCellmlIdentifier(const std::string &name) const
{
    bool result = true;
    // One or more alphabetic characters.
    if (!name.empty()) {
        // Does not start with numeric character.
        if (isdigit(name[0]) != 0) {
            result = false;
            IssuePtr issue = Issue::create();
            issue->setDescription("CellML identifiers must not begin with a European numeric character [0-9].");
            issue->setReferenceRule(Issue::ReferenceRule::DATA_REPR_IDENTIFIER_BEGIN_EURO_NUM);
            mValidator->addIssue(issue);
        } else {
            // Basic Latin alphanumeric characters and underscores.
            if (name.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_") != std::string::npos) {
                result = false;
                IssuePtr issue = Issue::create();
                issue->setDescription("CellML identifiers must not contain any characters other than [a-zA-Z0-9_].");
                issue->setReferenceRule(Issue::ReferenceRule::DATA_REPR_IDENTIFIER_LATIN_ALPHANUM);
                mValidator->addIssue(issue);
            }
        }
    } else {
        result = false;
        IssuePtr issue = Issue::create();
        issue->setDescription("CellML identifiers must contain one or more basic Latin alphabetic characters.");
        issue->setReferenceRule(Issue::ReferenceRule::DATA_REPR_IDENTIFIER_AT_LEAST_ONE_ALPHANUM);
        mValidator->addIssue(issue);
    }
    return result;
}

bool unitsAreEquivalent(const ModelPtr &model,
                        const VariablePtr &v1,
                        const VariablePtr &v2,
                        std::string &hints,
                        double &multiplier)
{
    std::map<std::string, double> unitMap = {};

    for (const auto &baseUnits : baseUnitsList) {
        unitMap[baseUnits] = 0.0;
    }

    std::string ref;
    hints = "";
    multiplier = 0.0;

    if (v1->units() == nullptr || v2->units() == nullptr) {
        return false;
    }

    if (model->hasUnits(v1->units()->name())) {
        UnitsPtr u1 = Units::create();
        u1 = model->units(v1->units()->name());
        updateBaseUnitCount(model, unitMap, multiplier, u1->name(), 1, 0, 1);
    } else if (unitMap.find(v1->units()->name()) != unitMap.end()) {
        ref = v1->units()->name();
        unitMap.at(ref) += 1.0;
    } else if (isStandardUnitName(v1->units()->name())) {
        updateBaseUnitCount(model, unitMap, multiplier, v1->units()->name(), 1, 0, 1);
    }

    if (model->hasUnits(v2->units()->name())) {
        UnitsPtr u2 = Units::create();
        u2 = model->units(v2->units()->name());
        updateBaseUnitCount(model, unitMap, multiplier, u2->name(), 1, 0, -1);
    } else if (unitMap.find(v2->units()->name()) != unitMap.end()) {
        ref = v2->units()->name();
        unitMap.at(v2->units()->name()) -= 1.0;
    } else if (isStandardUnitName(v2->units()->name())) {
        updateBaseUnitCount(model, unitMap, multiplier, v2->units()->name(), 1, 0, -1);
    }

    // Remove "dimensionless" from base unit testing.
    unitMap.erase("dimensionless");

    bool status = true;
    for (const auto &basePair : unitMap) {
        if (basePair.second != 0.0) {
            std::string num = std::to_string(basePair.second);
            num.erase(num.find_last_not_of('0') + 1, num.length());
            if (num.back() == '.') {
                num.pop_back();
            }
            hints += basePair.first + "^" + num + ", ";
            status = false;
        }
    }

    if (multiplier != 0.0) {
        // NB: multiplication issues are only reported when there is a base issue mismatch too, does not trigger it alone.
        // The multiplication mismatch will be returned through the multiplier argument in all cases.

        std::string num = std::to_string(multiplier);
        num.erase(num.find_last_not_of('0') + 1, num.length());
        if (num.back() == '.') {
            num.pop_back();
        }
        hints += "multiplication factor of 10^" + num + ", ";
    }

    // Remove the final trailing comma from the hints string.
    if (hints.length() > 2) {
        hints.pop_back();
        hints.back() = '.';
    }

    return status;
}

void updateBaseUnitCount(const ModelPtr &model,
                         std::map<std::string, double> &unitMap,
                         double &multiplier,
                         const std::string &uName,
                         double uExp, double logMult,
                         int direction)
{
    if (model->hasUnits(uName)) {
        UnitsPtr u = model->units(uName);
        if (!u->isBaseUnit()) {
            std::string ref;
            std::string pre;
            std::string id;
            double exp;
            double mult;
            double expMult;
            for (size_t i = 0; i < u->unitCount(); ++i) {
                u->unitAttributes(i, ref, pre, exp, expMult, id);
                mult = std::log10(expMult);
                if (!isStandardUnitName(ref)) {
                    updateBaseUnitCount(model, unitMap, multiplier, ref, exp * uExp, logMult + mult * uExp + standardPrefixList.at(pre) * uExp, direction);
                } else {
                    for (const auto &iter : standardUnitsList.at(ref)) {
                        unitMap.at(iter.first) += direction * (iter.second * exp * uExp);
                    }
                    multiplier += direction * (logMult + (standardMultiplierList.at(ref) + mult + standardPrefixList.at(pre)) * exp);
                }
            }
        } else if (unitMap.find(uName) == unitMap.end()) {
            unitMap.emplace(std::pair<std::string, double>(uName, direction * uExp));
            multiplier += direction * logMult;
        }
    } else if (isStandardUnitName(uName)) {
        for (const auto &iter : standardUnitsList.at(uName)) {
            unitMap.at(iter.first) += direction * (iter.second * uExp);
        }
        multiplier += direction * (logMult + standardMultiplierList.at(uName));
    }
}

void Validator::ValidatorImpl::validateNoUnitsAreCyclic(const ModelPtr &model)
{
    std::vector<std::string> history;
    std::vector<std::vector<std::string>> issueList;

    for (size_t i = 0; i < model->unitsCount(); ++i) {
        // Test each units' dependencies for presence of self in tree.
        UnitsPtr u = model->units(i);
        history.push_back(u->name());
        checkUnitForCycles(model, u, history, issueList);
        // Have to delete this each time to prevent reinitialisation with previous base variables.
        std::vector<std::string>().swap(history);
    }

    if (!issueList.empty()) {
        std::vector<std::map<std::string, bool>> reportedIssueList;
        for (auto &issues : issueList) {
            std::map<std::string, bool> hash;

            for (auto &e : issues) {
                hash.insert(std::pair<std::string, bool>(e, true));
            }

            // Only return as issue if this combo has not been reported already.
            if (std::find(reportedIssueList.begin(), reportedIssueList.end(), hash) == reportedIssueList.end()) {
                IssuePtr issue = Issue::create();
                std::string des = "'";
                for (size_t j = 0; j < issues.size() - 1; ++j) {
                    des += issues[j] + "' -> '";
                }
                des += issues[issues.size() - 1] + "'";
                issue->setDescription("Cyclic units exist: " + des);
                issue->setModel(model);
                issue->setCause(Issue::Cause::UNITS);
                mValidator->addIssue(issue);
                reportedIssueList.push_back(hash);
            }
            std::map<std::string, bool>().swap(hash);
        }
    }
}

void Validator::ValidatorImpl::checkUnitForCycles(const ModelPtr &model, const UnitsPtr &parent,
                                                  std::vector<std::string> &history,
                                                  std::vector<std::vector<std::string>> &errorList)
{
    if (parent->isBaseUnit()) {
        return;
    }

    // Recursive function to check for self-referencing in unit definitions.
    std::string id;
    std::string ref;
    std::string prefix;
    double exp;
    double mult;

    // Take history, and copy it for each new branch.
    for (size_t i = 0; i < parent->unitCount(); ++i) {
        parent->unitAttributes(i, ref, prefix, exp, mult, id);
        if (std::find(history.begin(), history.end(), ref) != history.end()) {
            history.push_back(ref);
            // Print to error output *only* when the first and last units are the same
            // otherwise we get lasso shapes reported.
            if (history.front() == history.back()) {
                errorList.push_back(history);
            }
        } else {
            // Step into dependencies if they are not built-in units.
            if (model->hasUnits(ref)) {
                UnitsPtr child = model->units(ref);
                history.push_back(ref);
                // Making a copy of the history vector to this point.
                std::vector<std::string> child_history(history);
                checkUnitForCycles(model, child, child_history, errorList);
                std::vector<std::string>().swap(child_history);
            }
        }
    }
}

} // namespace libcellml

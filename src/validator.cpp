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

#include "namespaces.h"
#include "utilities.h"
#include "xmldoc.h"

#include "libcellml/component.h"
#include "libcellml/error.h"
#include "libcellml/importsource.h"
#include "libcellml/model.h"
#include "libcellml/reset.h"
#include "libcellml/units.h"
#include "libcellml/validator.h"
#include "libcellml/variable.h"
#include "libcellml/when.h"

#include <map>
#include <regex>
#include <sstream>
#include <string>
#include <vector>

namespace libcellml {

/**
 * @brief The Validator::ValidatorImpl struct.
 *
 * The private implementation for the Validator class.
 */
struct Validator::ValidatorImpl
{
    Validator *mValidator;

    /**
     * @brief Validate the @p component using the CellML 2.0 Specification.
     *
     * Validate the given @p component and its encapsulated entities using
     * the CellML 2.0 Specification. Any errors will be logged in the @c Validator.
     *
     * @param component The component to validate.
     */
    void validateComponent(const ComponentPtr &component);

    /**
     * @brief Validate the @p units using the CellML 2.0 Specification.
     *
     * Validate the given @p units and its encapsulated entities using
     * the CellML 2.0 Specification. Any errors will be logged in the @c Validator.
     *
     * @param units The units to validate.
     * @param unitsNames A vector list of the name attributes of the @p units and its siblings.
     */
    void validateUnits(const UnitsPtr &units, const std::vector<std::string> &unitsNames);

    /**
     * @brief Validate the variable connections in the @p model using the CellML 2.0 Specification.
     *
     * Validate the variable connections in the given @p model using
     * the CellML 2.0 Specification. Any errors will be logged in the @c Validator.
     *
     * @param model The model which may contain variable connections to validate.
     */
    void validateConnections(const ModelPtr &model);

    /**
     * @brief Check if the provided @p name is a valid CellML identifier.
     *
     * Checks if the provided @p name is a valid CellML identifier according
     * to the CellML 2.0 specification. This requires a non-zero length Unicode
     * character sequence containing basic Latin alphanumeric characters or
     * underscores that does not start with a number.
     *
     * @param name The @c std::string name to check the validity of.
     *
     * @return @c true if @name is a valid CellML identifier and @c false otherwise.
     */
    bool isCellmlIdentifier(const std::string &name);

    /**
     * @brief Validate the @c unit at index @c index from @p units using the CellML 2.0 Specification.
     *
     * Validate the @c unit at index @c index from @p units using
     * the CellML 2.0 Specification. Any errors will be logged in the @c Validator.
     *
     * @param index The index of the @c unit to validate from @p units.
     * @param units The units to validate.
     * @param unitsNames A vector list of the name attributes of the @p units and its siblings.
     */
    void validateUnitsUnit(size_t index, const UnitsPtr &units, const std::vector<std::string> &unitsNames);

    /**
     * @brief Validate the @p variable using the CellML 2.0 Specification.
     *
     * Validate the given @p variable using the CellML 2.0 Specification.
     * Any errors will be logged in the @c Validator.
     *
     * @param variable The variable to validate.
     * @param variableNames A vector list of the name attributes of the @p variable and its siblings.
     */
    void validateVariable(const VariablePtr &variable, const std::vector<std::string> &variableNames);

    /**
     * @brief Validate the @p reset using the CellML 2.0 Specification.
     *
     * Examine the @p reset for conformance to the CellML 2.0 specification.  Any
     * errors will be logged in the @c Validator.
     *
     * @param reset The reset to validate.
     * @param component The component the reset belongs to.
     */
    void validateReset(const ResetPtr &reset, const ComponentPtr &component);

    /**
     * @brief Validate the @p when using the CellML 2.0 specification.
     *
     * Examine the @p when for conformance to the CellML 2.0 specification.  Any
     * errors will be logged in the @c Validator.
     *
     * @param when The when to validate.
     * @param reset The reset the when belongs to.
     * @param component The component the reset belongs to.
     */
    void validateWhen(const WhenPtr &when, const ResetPtr &reset, const ComponentPtr &component);

    /**
     * @brief Validate the math @p input @c std::string.
     *
     * Validate the math @p input @c std::string using the CellML 2.0 Specification and
     * the W3C MathML DTD. Any errors will be logged in the @c Validator.
     *
     * @param input The math @c std::string to validate.
     * @param component The component containing the math @c std::string to be validated.
     */
    void validateMath(const std::string &input, const ComponentPtr &component);

    /**
     * @brief Populate @p bvarNames with new variables declared in MathML @c bvar elements.
     *
     * Populate @p bvarNames with new variables declared in MathML @c bvar elements found within
     * the XmlNode @p node.
     *
     * @param node The @c XmlNode to search for @c bvar element names.
     * @param bvarNames The @c std::string @c vector to populate with MathML @c bvar element names.
     */
    void gatherMathBvarVariableNames(XmlNodePtr &node, std::vector<std::string> &bvarNames);

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

    /**
     * @brief Validate CellML variables and units in MathML @c ci and @c cn variables. Removes CellML units from the @p node.
     *
     * Validates CellML variables found in MathML @c ci elements and new variables from @c bvar elements. Validates @c cellml:units
     * attributes found on @c ci and @c cn elements and removes them from the @c XmlNode @p node to leave MathML that may then
     * be validated using the MathML DTD.
     *
     * @param node The @c XmlNode to validate CellML entities on and remove @c cellml:units from.
     * @param component The component that the math @c XmlNode @p node is contained within.
     * @param variableNames A @c vector list of the names of variables found within the @p component.
     * @param bvarNames A @c vector list of the names of new MathML @c bvar variables in this @c XmlNode @p node.
     */
    void validateAndCleanMathCiCnNodes(XmlNodePtr &node, const ComponentPtr &component, const std::vector<std::string> &variableNames, const std::vector<std::string> &bvarNames);

    /**
     * @brief Remove the @c std::string @p pattern from the @c std::string @p input.
     *
     * Remove all occurrences of the @c std::string @p pattern from the @c std::string @p input.
     *
     * @param input The @c std::string to remove all occurrences of the @p pattern from.
     * @param pattern The @c std::string to remove from the @c std::string @p input.
     */
    void removeSubstring(std::string &input, const std::string &pattern);

    /**
     * @brief Check if the provided @p name is a standard unit.
     *
     * Checks if the provided @p name is one of the standard units in the
     * @c Units::StandardUnit @c enum. Returns @c true if @name is a standard unit
     * and @c false otherwise.
     *
     * @param name The @c std::string name to check against the list of standard units.
     *
     * @return @c true if @name is a standard unit and @c false otherwise.
     */
    bool isStandardUnitName(const std::string &name);

    /**
     * @brief Check if the provided @p name is a standard prefix.
     *
     * Checks if the provided @p name is one of the standard prefixes in the
     * @c Prefix @c enum. Returns @c true if @name is a standard prefix
     * and @c false otherwise.
     *
     * @param name The @c std::string name to check against the list of standard prefixes.
     *
     * @return @c true if @name is a standard prefix and @c false otherwise.
     */
    bool isStandardPrefixName(const std::string &name);

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

Validator::Validator(const Validator &rhs)
    : Logger(rhs)
    , mPimpl(new ValidatorImpl())
{
    mPimpl->mValidator = rhs.mPimpl->mValidator;
}

Validator::Validator(Validator &&rhs) noexcept
    : Logger(std::move(rhs))
    , mPimpl(rhs.mPimpl)
{
    rhs.mPimpl = nullptr;
}

Validator &Validator::operator=(Validator rhs)
{
    Logger::operator=(rhs);
    rhs.swap(*this);
    return *this;
}

void Validator::swap(Validator &rhs)
{
    std::swap(this->mPimpl, rhs.mPimpl);
}

void Validator::validateModel(const ModelPtr &model)
{
    // Clear any pre-existing errors in ths validator instance.
    clearErrors();
    // Check for a valid name attribute.
    if (!mPimpl->isCellmlIdentifier(model->name())) {
        ErrorPtr err = std::make_shared<Error>();
        err->setDescription("Model does not have a valid name attribute.");
        err->setModel(model);
        err->setRule(SpecificationRule::MODEL_NAME);
        addError(err);
    }
    // Check for components in this model.
    if (model->componentCount() > 0) {
        std::vector<std::string> componentNames;
        std::vector<std::string> componentRefs;
        std::vector<std::string> componentImportSources;
        for (size_t i = 0; i < model->componentCount(); ++i) {
            ComponentPtr component = model->component(i);
            // Check for duplicate component names in this model.
            std::string componentName = component->name();
            if (!componentName.empty()) {
                if (component->isImport()) {
                    // Check for a component_ref.
                    std::string componentRef = component->importReference();
                    std::string importSource = component->importSource()->url();
                    bool foundImportError = false;
                    if (!mPimpl->isCellmlIdentifier(componentRef)) {
                        ErrorPtr err = std::make_shared<Error>();
                        err->setDescription("Imported component '" + componentName + "' does not have a valid component_ref attribute.");
                        err->setComponent(component);
                        err->setRule(SpecificationRule::IMPORT_COMPONENT_REF);
                        addError(err);
                        foundImportError = true;
                    }
                    // Check for a xlink:href.
                    // TODO: check this id against the XLink spec (see CellML Spec 5.1.1).
                    if (importSource.empty()) {
                        ErrorPtr err = std::make_shared<Error>();
                        err->setDescription("Import of component '" + componentName + "' does not have a valid locator xlink:href attribute.");
                        err->setImportSource(component->importSource());
                        err->setRule(SpecificationRule::IMPORT_HREF);
                        addError(err);
                        foundImportError = true;
                    }
                    // Check if we already have another import from the same source with the same component_ref.
                    // (This looks for matching entries at the same position in the source and ref vectors).
                    if (!componentImportSources.empty() && (!foundImportError)) {
                        if ((std::find(componentImportSources.begin(), componentImportSources.end(), importSource) - componentImportSources.begin())
                            == (std::find(componentRefs.begin(), componentRefs.end(), componentRef) - componentRefs.begin())) {
                            ErrorPtr err = std::make_shared<Error>();
                            err->setDescription("Model '" + model->name() + "' contains multiple imported components from '" + importSource + "' with the same component_ref attribute '" + componentRef + "'.");
                            err->setModel(model);
                            err->setRule(SpecificationRule::IMPORT_COMPONENT_REF);
                            addError(err);
                        }
                    }
                    // Push back the unique sources and refs.
                    componentImportSources.push_back(importSource);
                    componentRefs.push_back(componentRef);
                }
                if (std::find(componentNames.begin(), componentNames.end(), componentName) != componentNames.end()) {
                    ErrorPtr err = std::make_shared<Error>();
                    err->setDescription("Model '" + model->name() + "' contains multiple components with the name '" + componentName + "'. Valid component names must be unique to their model.");
                    err->setModel(model);
                    addError(err);
                }
                componentNames.push_back(componentName);
            }
            // Validate component.
            mPimpl->validateComponent(component);
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
                    bool foundImportError = false;
                    if (!mPimpl->isCellmlIdentifier(unitsRef)) {
                        ErrorPtr err = std::make_shared<Error>();
                        err->setDescription("Imported units '" + unitsName + "' does not have a valid units_ref attribute.");
                        err->setUnits(units);
                        err->setRule(SpecificationRule::IMPORT_UNITS_REF);
                        addError(err);
                        foundImportError = true;
                    }
                    // Check for a xlink:href.
                    // TODO: check this id against the XLink spec (see CellML Spec 5.1.1).
                    if (importSource.empty()) {
                        ErrorPtr err = std::make_shared<Error>();
                        err->setDescription("Import of units '" + unitsName + "' does not have a valid locator xlink:href attribute.");
                        err->setImportSource(units->importSource());
                        err->setRule(SpecificationRule::IMPORT_HREF);
                        addError(err);
                        foundImportError = true;
                    }
                    // Check if we already have another import from the same source with the same units_ref.
                    // (This looks for matching enties at the same position in the source and ref vectors).
                    if (!unitsImportSources.empty() && (!foundImportError)) {
                        if ((std::find(unitsImportSources.begin(), unitsImportSources.end(), importSource) - unitsImportSources.begin())
                            == (std::find(unitsRefs.begin(), unitsRefs.end(), unitsRef) - unitsRefs.begin())) {
                            ErrorPtr err = std::make_shared<Error>();
                            err->setDescription("Model '" + model->name() + "' contains multiple imported units from '" + importSource + "' with the same units_ref attribute '" + unitsRef + "'.");
                            err->setModel(model);
                            err->setRule(SpecificationRule::IMPORT_UNITS_REF);
                            addError(err);
                        }
                    }
                    // Push back the unique sources and refs.
                    unitsImportSources.push_back(importSource);
                    unitsRefs.push_back(unitsRef);
                }
                // Check for duplicate units names in this model.
                if (std::find(unitsNames.begin(), unitsNames.end(), unitsName) != unitsNames.end()) {
                    ErrorPtr err = std::make_shared<Error>();
                    err->setDescription("Model '" + model->name() + "' contains multiple units with the name '" + unitsName + "'. Valid units names must be unique to their model.");
                    err->setModel(model);
                    err->setRule(SpecificationRule::UNITS_NAME_UNIQUE);
                    addError(err);
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
    // Validate any connections / variable equivalence networks in the model.
    mPimpl->validateConnections(model);
}

void Validator::ValidatorImpl::validateComponent(const ComponentPtr &component)
{
    // Check for a valid name attribute.
    if (!isCellmlIdentifier(component->name())) {
        ErrorPtr err = std::make_shared<Error>();
        err->setComponent(component);
        if (component->isImport()) {
            err->setDescription("Imported component does not have a valid name attribute.");
            err->setRule(SpecificationRule::IMPORT_COMPONENT_NAME);
        } else {
            err->setDescription("Component does not have a valid name attribute.");
            err->setRule(SpecificationRule::COMPONENT_NAME);
        }
        mValidator->addError(err);
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
                    ErrorPtr err = std::make_shared<Error>();
                    err->setDescription("Component '" + component->name() + "' contains multiple variables with the name '" + variableName + "'. Valid variable names must be unique to their component.");
                    err->setComponent(component);
                    err->setRule(SpecificationRule::VARIABLE_NAME);
                    mValidator->addError(err);
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
    if (component->resetCount() > 0) {
        // Check for duplicate order values in resets
        std::vector<int> resetOrders;
        for (size_t i = 0; i < component->resetCount(); ++i) {
            ResetPtr reset = component->reset(i);
            int resetOrder = reset->order();
            if (reset->isOrderSet()) {
                if (std::find(resetOrders.begin(), resetOrders.end(), resetOrder) != resetOrders.end()) {
                    ErrorPtr err = std::make_shared<Error>();
                    err->setDescription("Component '" + component->name() + "' contains multiple resets with order '" + convertIntToString(resetOrder) + "'.");
                    err->setComponent(component);
                    err->setRule(SpecificationRule::RESET_ORDER);
                    mValidator->addError(err);
                } else {
                    resetOrders.push_back(resetOrder);
                }
            }
        }

        for (size_t i = 0; i < component->resetCount(); ++i) {
            ResetPtr reset = component->reset(i);
            validateReset(reset, component);
        }
    }
    // Validate math through the private implementation (for XML handling).
    if (!component->math().empty()) {
        validateMath(component->math(), component);
    }
}

void Validator::ValidatorImpl::validateUnits(const UnitsPtr &units, const std::vector<std::string> &unitsNames)
{
    // Check for a valid name attribute.
    // TODO: Check for valid base unit reduction (see 17.3)
    if (!isCellmlIdentifier(units->name())) {
        ErrorPtr err = std::make_shared<Error>();
        err->setUnits(units);
        if (units->isImport()) {
            err->setDescription("Imported units does not have a valid name attribute.");
            err->setRule(SpecificationRule::IMPORT_UNITS_NAME);
        } else {
            err->setDescription("Units does not have a valid name attribute.");
            err->setRule(SpecificationRule::UNITS_NAME);
        }
        mValidator->addError(err);
    } else {
        // Check for a matching standard units.
        if (isStandardUnitName(units->name())) {
            ErrorPtr err = std::make_shared<Error>();
            err->setDescription("Units is named '" + units->name() + "', which is a protected standard unit name.");
            err->setUnits(units);
            err->setRule(SpecificationRule::UNITS_STANDARD);
            mValidator->addError(err);
        }
    }
    if (units->unitCount() > 0) {
        // Validate each unit in units.
        for (size_t i = 0; i < units->unitCount(); ++i) {
            validateUnitsUnit(i, units, unitsNames);
        }
    }
}

void Validator::ValidatorImpl::validateUnitsUnit(size_t index, const UnitsPtr &units, const std::vector<std::string> &unitsNames)
{
    // Validate the unit at the given index.
    std::string reference;
    std::string prefix;
    std::string id;
    double exponent;
    double multiplier;
    units->getUnitAttributes(index, reference, prefix, exponent, multiplier, id);
    if (isCellmlIdentifier(reference)) {
        if ((std::find(unitsNames.begin(), unitsNames.end(), reference) == unitsNames.end()) && (!isStandardUnitName(reference))) {
            ErrorPtr err = std::make_shared<Error>();
            err->setDescription("Units reference '" + reference + "' in units '" + units->name() + "' is not a valid reference to a local units or a standard unit type.");
            err->setUnits(units);
            err->setRule(SpecificationRule::UNIT_UNITS_REF);
            mValidator->addError(err);
        }
    } else {
        ErrorPtr err = std::make_shared<Error>();
        err->setDescription("Unit in units '" + units->name() + "' does not have a valid units reference.");
        err->setUnits(units);
        err->setRule(SpecificationRule::UNIT_UNITS_REF);
        mValidator->addError(err);
    }
    if (!prefix.empty()) {
        // If the prefix is not in the list of valid prefix names, check if it is a real number.
        if (!isStandardPrefixName(prefix)) {
            if (!isCellMLReal(prefix)) {
                ErrorPtr err = std::make_shared<Error>();
                err->setDescription("Prefix '" + prefix + "' of a unit referencing '" + reference + "' in units '" + units->name() + "' is not a valid real number or a SI prefix.");
                err->setUnits(units);
                err->setRule(SpecificationRule::UNIT_PREFIX);
                mValidator->addError(err);
            }
        }
    }
}

void Validator::ValidatorImpl::validateVariable(const VariablePtr &variable, const std::vector<std::string> &variableNames)
{
    // Check for a valid name attribute.
    if (!isCellmlIdentifier(variable->name())) {
        ErrorPtr err = std::make_shared<Error>();
        err->setDescription("Variable does not have a valid name attribute.");
        err->setVariable(variable);
        err->setRule(SpecificationRule::VARIABLE_NAME);
        mValidator->addError(err);
    }
    // Check for a valid units attribute.
    if (!isCellmlIdentifier(variable->getUnits())) {
        ErrorPtr err = std::make_shared<Error>();
        err->setDescription("Variable '" + variable->name() + "' does not have a valid units attribute.");
        err->setVariable(variable);
        err->setRule(SpecificationRule::VARIABLE_UNITS);
        mValidator->addError(err);
    } else if (!isStandardUnitName(variable->getUnits())) {
        auto component = static_cast<Component *>(variable->parent());
        auto model = static_cast<Model *>(component->parent());
        if ((model != nullptr) && !model->hasUnits(variable->getUnits())) {
            ErrorPtr err = std::make_shared<Error>();
            err->setDescription("Variable '" + variable->name() + "' has an invalid units reference '" + variable->getUnits() + "' that does not correspond with a standard unit or units in the variable's parent component or model.");
            err->setVariable(variable);
            err->setRule(SpecificationRule::VARIABLE_UNITS);
            mValidator->addError(err);
        }
    }
    // Check for a valid interface attribute.
    if (!variable->getInterfaceType().empty()) {
        std::string interfaceType = variable->getInterfaceType();
        if ((interfaceType != "public") && (interfaceType != "private") && (interfaceType != "none") && (interfaceType != "public_and_private")) {
            ErrorPtr err = std::make_shared<Error>();
            err->setDescription("Variable '" + variable->name() + "' has an invalid interface attribute value '" + interfaceType + "'.");
            err->setVariable(variable);
            err->setRule(SpecificationRule::VARIABLE_INTERFACE);
            mValidator->addError(err);
        }
    }
    // Check for a valid initial value attribute.
    if (!variable->getInitialValue().empty()) {
        std::string initialValue = variable->getInitialValue();
        // Check if initial value is a variable reference
        if (!(std::find(variableNames.begin(), variableNames.end(), initialValue) != variableNames.end())) {
            // Otherwise, check that the initial value can be converted to a double
            if (!isCellMLReal(initialValue)) {
                ErrorPtr err = std::make_shared<Error>();
                err->setDescription("Variable '" + variable->name() + "' has an invalid initial value '" + initialValue + "'. Initial values must be a real number string or a variable reference.");
                err->setVariable(variable);
                err->setRule(SpecificationRule::VARIABLE_INITIAL_VALUE);
                mValidator->addError(err);
            }
        }
    }
}

void Validator::ValidatorImpl::validateReset(const ResetPtr &reset, const ComponentPtr &component)
{
    std::string orderString;
    if (reset->isOrderSet()) {
        orderString = "with order '" + convertIntToString(reset->order()) + "'";
    } else {
        orderString = "does not have an order set,";
    }

    std::string variableString;
    std::string variableContinuation;
    if (reset->getVariable() == nullptr) {
        variableString = "does not reference a variable";
        variableContinuation = ",";
        ErrorPtr err = std::make_shared<Error>();
        err->setDescription("Reset in component '" + component->name() + "' " + orderString + " " + variableString + ".");
        err->setReset(reset);
        err->setRule(SpecificationRule::RESET_VARIABLE_REFERENCE);
        mValidator->addError(err);
    } else {
        variableString = "referencing variable '" + reset->getVariable()->name() + "'";
    }

    if (!reset->isOrderSet()) {
        ErrorPtr err = std::make_shared<Error>();
        err->setDescription("Reset in component '" + component->name() + "' " + orderString + " " + variableString + ".");
        err->setComponent(component);
        err->setRule(SpecificationRule::RESET_ORDER);
        mValidator->addError(err);
    }

    if (reset->whenCount() > 0) {
        // Check for duplicate when order values.
        std::vector<int> whenOrders;
        for (size_t i = 0; i < reset->whenCount(); ++i) {
            WhenPtr when = reset->getWhen(i);
            if (when->isOrderSet()) {
                int whenOrder = when->order();
                if (std::find(whenOrders.begin(), whenOrders.end(), whenOrder) != whenOrders.end()) {
                    ErrorPtr err = std::make_shared<Error>();
                    err->setDescription("Reset in component '" + component->name() + "' " + orderString + " " + variableString + variableContinuation + " has multiple whens with order '" + convertIntToString(whenOrder) + "'.");
                    err->setComponent(component);
                    err->setRule(SpecificationRule::RESET_ORDER);
                    mValidator->addError(err);
                } else {
                    whenOrders.push_back(whenOrder);
                }
            }
        }
        for (size_t i = 0; i < reset->whenCount(); ++i) {
            WhenPtr when = reset->getWhen(i);
            validateWhen(when, reset, component);
        }
    } else {
        ErrorPtr err = std::make_shared<Error>();
        err->setDescription("Reset in component '" + component->name() + "' " + orderString + " " + variableString + variableContinuation + " does not have at least one child When.");
        err->setReset(reset);
        err->setRule(SpecificationRule::RESET_CHILD);
        mValidator->addError(err);
    }
}

void Validator::ValidatorImpl::validateWhen(const WhenPtr &when, const ResetPtr &reset, const ComponentPtr &component)
{
    std::string orderString;
    std::string resetOrderString;
    std::string resetVariableString;
    std::string resetVariableContinuation;
    if (when->isOrderSet()) {
        orderString = "with order '" + convertIntToString(when->order()) + "'";
    } else {
        orderString = "does not have an order set,";
    }

    if (reset->isOrderSet()) {
        resetOrderString = "with order '" + convertIntToString(reset->order()) + "'";
    } else {
        resetOrderString = "which does not have an order set,";
    }

    if (reset->getVariable() == nullptr) {
        resetVariableString = "which does not reference a variable";
        resetVariableContinuation = ",";
    } else {
        resetVariableContinuation = "";
        resetVariableString = "referencing variable '" + reset->getVariable()->name() + "'";
    }

    if (!when->isOrderSet()) {
        ErrorPtr err = std::make_shared<Error>();
        err->setDescription("When in reset " + resetOrderString + " " + resetVariableString + resetVariableContinuation + " does not have an order set.");
        err->setWhen(when);
        err->setRule(SpecificationRule::WHEN_ORDER);
        mValidator->addError(err);
    }

    if (!when->getCondition().empty()) {
        validateMath(when->getCondition(), component);
    } else {
        ErrorPtr err = std::make_shared<Error>();
        err->setDescription("When in reset " + resetOrderString + " " + resetVariableString + resetVariableContinuation + " " + orderString + " does not have a MathML condition set.");
        err->setWhen(when);
        err->setRule(SpecificationRule::WHEN_CHILD);
        mValidator->addError(err);
    }

    if (!when->getValue().empty()) {
        validateMath(when->getValue(), component);
    } else {
        ErrorPtr err = std::make_shared<Error>();
        err->setDescription("When in reset " + resetOrderString + " " + resetVariableString + resetVariableContinuation + " " + orderString + " does not have a MathML value set.");
        err->setWhen(when);
        err->setRule(SpecificationRule::WHEN_CHILD);
        mValidator->addError(err);
    }
}

void Validator::ValidatorImpl::validateMath(const std::string &input, const ComponentPtr &component)
{
    XmlDocPtr doc = std::make_shared<XmlDoc>();
    // Parse as XML first.
    doc->parse(input);
    // Copy any XML parsing errors into the common validator error handler.
    if (doc->xmlErrorCount() > 0) {
        for (size_t i = 0; i < doc->xmlErrorCount(); ++i) {
            ErrorPtr err = std::make_shared<Error>();
            err->setDescription(doc->getXmlError(i));
            err->setKind(Error::Kind::XML);
            mValidator->addError(err);
        }
    }
    XmlNodePtr node = doc->getRootNode();
    if (node == nullptr) {
        ErrorPtr err = std::make_shared<Error>();
        err->setDescription("Could not get a valid XML root node from the math on component '" + component->name() + "'.");
        err->setKind(Error::Kind::XML);
        err->setComponent(component);
        mValidator->addError(err);
        return;
    }
    if (!node->isMathmlElement("math")) {
        ErrorPtr err = std::make_shared<Error>();
        err->setDescription("Math root node is of invalid type '" + node->name() + "' on component '" + component->name() + "'. A valid math root node should be of type 'math'.");
        err->setComponent(component);
        err->setKind(Error::Kind::XML);
        mValidator->addError(err);
        return;
    }
    XmlNodePtr nodeCopy = node;
    std::vector<std::string> bvarNames;
    std::vector<std::string> variableNames;
    for (size_t i = 0; i < component->variableCount(); ++i) {
        std::string variableName = component->variable(i)->name();
        if (std::find(variableNames.begin(), variableNames.end(), variableName) == variableNames.end()) {
            variableNames.push_back(variableName);
        }
    }

    validateMathMLElements(nodeCopy, component);
    // Get the bvar names in this math element.
    // TODO: may want to do this with XPath instead...
    gatherMathBvarVariableNames(nodeCopy, bvarNames);
    // Check that no variable names match new bvar names.
    for (const std::string &variableName : variableNames) {
        if (std::find(bvarNames.begin(), bvarNames.end(), variableName) != bvarNames.end()) {
            ErrorPtr err = std::make_shared<Error>();
            err->setDescription("Math in component '" + component->name() + "' contains '" + variableName + "' as a bvar ci element but it is already a variable name.");
            err->setComponent(component);
            err->setKind(Error::Kind::MATHML);
            mValidator->addError(err);
        }
    }
    // Iterate through ci/cn elements and remove cellml units attributes.
    XmlNodePtr mathNode = node;
    validateAndCleanMathCiCnNodes(node, component, variableNames, bvarNames);
    // Get the MathML string (with cellml:units attributes already removed) and remove the CellML namespace.
    // While the removeSubstring() approach for removing the cellml namespace before validating with the MathML DTD
    // is not ideal, libxml does not appear to have a better way to remove a namespace declaration from the tree.
    std::string cellml2NamespaceString = std::string(" xmlns:cellml=\"http://www.cellml.org/cellml/2.0#\"");
    std::string cleanMathml = mathNode->convertToString();
    removeSubstring(cleanMathml, cellml2NamespaceString);

    // Parse/validate the clean math string with the W3C MathML DTD.
    XmlDocPtr mathmlDoc = std::make_shared<XmlDoc>();
    mathmlDoc->parseMathML(cleanMathml);
    // Copy any MathML validation errors into the common validator error handler.
    if (mathmlDoc->xmlErrorCount() > 0) {
        for (size_t i = 0; i < mathmlDoc->xmlErrorCount(); ++i) {
            ErrorPtr err = std::make_shared<Error>();
            err->setDescription(mathmlDoc->getXmlError(i));
            err->setComponent(component);
            err->setKind(Error::Kind::MATHML);
            mValidator->addError(err);
        }
    }
}

void Validator::ValidatorImpl::validateAndCleanMathCiCnNodes(XmlNodePtr &node, const ComponentPtr &component, const std::vector<std::string> &variableNames,
                                                             const std::vector<std::string> &bvarNames)
{
    XmlNodePtr childNode = node->firstChild();
    std::string textNode;
    bool ciType = node->isMathmlElement("ci");
    bool cnType = node->isMathmlElement("cn");
    if (ciType || cnType) {
        if (childNode != nullptr) {
            if (childNode->isText()) {
                textNode = childNode->convertToStrippedString();
                if (!textNode.empty()) {
                    if (ciType) {
                        // Check whether we can find this text as a variable name in this component.
                        if ((std::find(variableNames.begin(), variableNames.end(), textNode) == variableNames.end()) && (std::find(bvarNames.begin(), bvarNames.end(), textNode) == bvarNames.end())) {
                            ErrorPtr err = std::make_shared<Error>();
                            err->setDescription("MathML ci element has the child text '" + textNode + "', which does not correspond with any variable names present in component '" + component->name() + "' and is not a variable defined within a bvar element.");
                            err->setComponent(component);
                            err->setKind(Error::Kind::MATHML);
                            mValidator->addError(err);
                        }
                    }
                } else {
                    ErrorPtr err = std::make_shared<Error>();
                    err->setDescription("MathML " + node->name() + " element has an empty child element.");
                    err->setComponent(component);
                    err->setKind(Error::Kind::MATHML);
                    mValidator->addError(err);
                }
            }
        } else {
            ErrorPtr err = std::make_shared<Error>();
            err->setDescription("MathML " + node->name() + " element has no child.");
            err->setComponent(component);
            err->setKind(Error::Kind::MATHML);
            mValidator->addError(err);
        }
        // Get cellml:units attribute.
        XmlAttributePtr attribute = node->firstAttribute();
        std::string unitsName;
        XmlAttributePtr unitsAttribute = nullptr;
        while (attribute) {
            if (!attribute->getValue().empty()) {
                if (attribute->isCellmlType("units")) {
                    unitsName = attribute->getValue();
                    unitsAttribute = attribute;
                } else {
                    ErrorPtr err = std::make_shared<Error>();
                    err->setDescription("Math " + node->name() + " element has an invalid attribute type '" + attribute->getName() + "' in the cellml namespace.");
                    err->setComponent(component);
                    err->setKind(Error::Kind::MATHML);
                    mValidator->addError(err);
                }
            }
            attribute = attribute->getNext();
        }

        bool checkUnitsIsInComponent = false;
        // Check that cellml:units has been set.
        if (ciType) {
            if (unitsAttribute != nullptr) {
                ErrorPtr err = std::make_shared<Error>();
                err->setDescription("Math ci element with value '" + textNode + "' has a cellml:units attribute with name '" + unitsAttribute->getValue() + "'.");
            }
        } else if (cnType) {
            if (isCellmlIdentifier(unitsName)) {
                checkUnitsIsInComponent = true;
            } else {
                ErrorPtr err = std::make_shared<Error>();
                err->setDescription("Math cn element with the value '" + textNode + "' does not have a valid cellml:units attribute.");
                err->setComponent(component);
                err->setKind(Error::Kind::MATHML);
                mValidator->addError(err);
            }
        }

        // Check that a specified units is valid.
        if (checkUnitsIsInComponent) {
            // Check for a matching units in this component.
            auto model = static_cast<Model *>(component->parent());
            if (!model->hasUnits(unitsName)) {
                // Check for a matching standard units.
                if (!isStandardUnitName(unitsName)) {
                    ErrorPtr err = std::make_shared<Error>();
                    err->setDescription("Math has a " + node->name() + " element with a cellml:units attribute '" + unitsName + "' that is not a valid reference to units in component '" + component->name() + "' or a standard unit.");
                    err->setComponent(component);
                    err->setKind(Error::Kind::MATHML);
                    mValidator->addError(err);
                }
            }
        }
        // Now that we've validated this XML node's cellml:units attribute, remove it from the node.
        // This is done so we can validate a "clean" MathML string using the MathML DTD. The math
        // string stored on the component will not be affected.
        if (unitsAttribute) {
            unitsAttribute->removeAttribute();
        }
    } else {
        // Check children for ci/cn elements.
        if (childNode != nullptr) {
            validateAndCleanMathCiCnNodes(childNode, component, variableNames, bvarNames);
        }
    }
    // Check siblings for ci/cn.
    node = node->next();
    if (node != nullptr) {
        validateAndCleanMathCiCnNodes(node, component, variableNames, bvarNames);
    }
}

void Validator::ValidatorImpl::validateMathMLElements(const XmlNodePtr &node, const ComponentPtr &component)
{
    XmlNodePtr childNode = node->firstChild();
    if (childNode != nullptr) {
        if (!childNode->isComment() && !childNode->isText() && !isSupportedMathMLElement(childNode)) {
            ErrorPtr err = std::make_shared<Error>();
            err->setDescription("Math has a '" + childNode->name() + "' element" + " that is not a supported MathML element.");
            err->setComponent(component);
            err->setKind(Error::Kind::MATHML);
            mValidator->addError(err);
        }
        validateMathMLElements(childNode, component);
    }

    XmlNodePtr nextNode = node->next();
    if (nextNode != nullptr) {
        if (!nextNode->isComment() && !nextNode->isText() && !isSupportedMathMLElement(nextNode)) {
            ErrorPtr err = std::make_shared<Error>();
            err->setDescription("Math has a '" + nextNode->name() + "' element" + " that is not a supported MathML element.");
            err->setComponent(component);
            err->setKind(Error::Kind::MATHML);
            mValidator->addError(err);
        }
        validateMathMLElements(nextNode, component);
    }
}

void Validator::ValidatorImpl::gatherMathBvarVariableNames(XmlNodePtr &node, std::vector<std::string> &bvarNames)
{
    XmlNodePtr childNode = node->firstChild();
    if (node->isMathmlElement("bvar")) {
        while (childNode != nullptr) {
            if (childNode->isMathmlElement("ci")) {
                XmlNodePtr grandchildNode = childNode->firstChild();
                bool hasBvarName = false;
                while (grandchildNode != nullptr) {
                    if (grandchildNode->isText()) {
                        std::string textNode = grandchildNode->convertToStrippedString();
                        if (!textNode.empty()) {
                            bvarNames.push_back(textNode);
                            hasBvarName = true;
                            break;
                        }
                    }
                    grandchildNode = grandchildNode->next();
                }
                if (hasBvarName) {
                    break;
                }
            }
            childNode = childNode->next();
        }
    } else {
        // Check children for bvars.
        if (childNode != nullptr) {
            gatherMathBvarVariableNames(childNode, bvarNames);
        }
    }
    // Check siblings for bvars.
    node = node->next();
    if (node != nullptr) {
        gatherMathBvarVariableNames(node, bvarNames);
    }
}

void Validator::ValidatorImpl::validateConnections(const ModelPtr &model)
{
    // Check the components in this model.
    if (model->componentCount() > 0) {
        for (size_t i = 0; i < model->componentCount(); ++i) {
            ComponentPtr component = model->component(i);
            // Check the variables in this component.
            for (size_t j = 0; j < component->variableCount(); ++j) {
                VariablePtr variable = component->variable(j);
                // Check the equivalent variables in this variable.
                if (variable->equivalentVariableCount() > 0) {
                    for (size_t k = 0; k < variable->equivalentVariableCount(); ++k) {
                        VariablePtr equivalentVariable = variable->getEquivalentVariable(k);
                        // TODO: validate variable interfaces according to 17.10.8
                        // TODO: add check for cyclical connections (17.10.5)
                        if (equivalentVariable->hasEquivalentVariable(variable)) {
                            // Check that the equivalent variable has a valid parent component.
                            auto component2 = static_cast<Component *>(equivalentVariable->parent());
                            if (!component2->hasVariable(equivalentVariable)) {
                                ErrorPtr err = std::make_shared<Error>();
                                err->setDescription("Variable '" + equivalentVariable->name() + "' is an equivalent variable to '" + variable->name() + "' but has no parent component.");
                                err->setModel(model);
                                err->setKind(Error::Kind::CONNECTION);
                                mValidator->addError(err);
                            }
                        } else {
                            ErrorPtr err = std::make_shared<Error>();
                            err->setDescription("Variable '" + variable->name() + "' has an equivalent variable '" + equivalentVariable->name() + "'  which does not reciprocally have '" + variable->name() + "' set as an equivalent variable.");
                            err->setModel(model);
                            err->setKind(Error::Kind::CONNECTION);
                            mValidator->addError(err);
                        }
                    }
                }
            }
        }
    }
}

// TODO: validateEncapsulations

void Validator::ValidatorImpl::removeSubstring(std::string &input, const std::string &pattern)
{
    std::string::size_type n = pattern.length();
    for (std::string::size_type i = input.find(pattern);
         i != std::string::npos;
         i = input.find(pattern)) {
        input.erase(i, n);
    }
}

bool Validator::ValidatorImpl::isSupportedMathMLElement(const XmlNodePtr &node)
{
    const std::vector<std::string> supportedMathMLElements = {
        "ci", "cn", "sep", "apply", "piecewise", "piece", "otherwise", "eq", "neq", "gt", "lt", "geq", "leq", "and", "or",
        "xor", "not", "plus", "minus", "times", "divide", "power", "root", "abs", "exp", "ln", "log", "floor",
        "ceiling", "min", "max", "rem", "diff", "bvar", "logbase", "degree", "sin", "cos", "tan", "sec", "csc",
        "cot", "sinh", "cosh", "tanh", "sech", "csch", "coth", "arcsin", "arccos", "arctan", "arcsec", "arccsc",
        "arccot", "arcsinh", "arccosh", "arctanh", "arcsech", "arccsch", "arccoth", "pi", "exponentiale",
        "notanumber", "infinity", "true", "false"};
    return (node->namespaceUri() == MATHML_NS)
           && std::find(supportedMathMLElements.begin(), supportedMathMLElements.end(), node->name()) != supportedMathMLElements.end();
}

bool Validator::ValidatorImpl::isStandardUnitName(const std::string &name)
{
    bool result = false;
    std::vector<std::string> standardUnitNames = {
        "ampere", "becquerel", "candela", "celsius", "coulomb", "dimensionless", "farad", "gram", "gray",
        "henry", "hertz", "joule", "katal", "kelvin", "kilogram", "liter", "litre", "lumen", "lux",
        "meter", "metre", "mole", "newton", "ohm", "pascal", "radian", "second", "siemens", "sievert",
        "steradian", "tesla", "volt", "watt", "weber"};
    if (std::find(standardUnitNames.begin(), standardUnitNames.end(), name) != standardUnitNames.end()) {
        result = true;
    }
    return result;
}

bool Validator::ValidatorImpl::isStandardPrefixName(const std::string &name)
{
    bool result = false;
    std::vector<std::string> prefixNames = {
        "atto", "centi", "deca", "deci", "exa", "femto", "giga", "hecto", "kilo", "mega", "micro", "milli",
        "nano", "peta", "pico", "tera", "yocto", "yotta", "zepto", "zetta"};
    if (std::find(prefixNames.begin(), prefixNames.end(), name) != prefixNames.end()) {
        result = true;
    }
    return result;
}

bool Validator::ValidatorImpl::isCellmlIdentifier(const std::string &name)
{
    bool result = true;
    // One or more alphabetic characters.
    if (!name.empty()) {
        // Does not start with numeric character.
        if (isdigit(name[0]) != 0) {
            result = false;
            ErrorPtr err = std::make_shared<Error>();
            err->setDescription("CellML identifiers must not begin with a European numeric character [0-9].");
            err->setRule(SpecificationRule::DATA_REPR_IDENTIFIER_BEGIN_EURO_NUM);
            mValidator->addError(err);
        } else {
            // Basic Latin alphanumeric characters and underscores.
            if (name.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_") != std::string::npos) {
                result = false;
                ErrorPtr err = std::make_shared<Error>();
                err->setDescription("CellML identifiers must not contain any characters other than [a-zA-Z0-9_].");
                err->setRule(SpecificationRule::DATA_REPR_IDENTIFIER_LATIN_ALPHANUM);
                mValidator->addError(err);
            }
        }
    } else {
        result = false;
        ErrorPtr err = std::make_shared<Error>();
        err->setDescription("CellML identifiers must contain one or more basic Latin alphabetic characters.");
        err->setRule(SpecificationRule::DATA_REPR_IDENTIFIER_AT_LEAST_ONE_ALPHANUM);
        mValidator->addError(err);
    }
    return result;
}

} // namespace libcellml

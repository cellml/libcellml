/*
Copyright 2015 University of Auckland

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
#include <string>
#include <vector>

#include "libcellml/component.h"
#include "libcellml/import.h"
#include "libcellml/error.h"
#include "libcellml/model.h"
#include "libcellml/variable.h"
#include "xmldoc.h"

namespace libcellml {

/**
 * @brief The Validator::ValidatorImpl struct.
 *
 * The private implementation for the Validator class.
 */
struct Validator::ValidatorImpl
{
public:
    Validator *mValidator;
    void validateMath(const std::string &input, const ComponentPtr &component, std::vector<std::string> &variableNames);
private:
    void gatherMathBvarVariableNames(XmlNodePtr &node, std::vector<std::string> &bvarNames);
    void validateMathCiNodes(XmlNodePtr &node, const ComponentPtr &component, const std::vector<std::string> &variableNames, const std::vector<std::string> &bvarNames);
    bool isNotWhitespace(std::string &input);
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

Validator::Validator(const Validator& rhs)
    : Logger(rhs)
    , mPimpl(new ValidatorImpl())
{
    mPimpl->mValidator = rhs.mPimpl->mValidator;
}

Validator::Validator(Validator &&rhs)
    : Logger(std::move(rhs))
    , mPimpl(rhs.mPimpl)
{
    rhs.mPimpl = nullptr;
}

Validator& Validator::operator=(Validator v)
{
    Logger::operator =(v);
    v.swap(*this);
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
    if (!model->getName().length()) {
        ErrorPtr err = std::make_shared<Error>();
        err->setDescription("Model does not have a valid name attribute.");
        err->setModel(model);
        err->setKind(Error::Kind::MODEL);
        addError(err);
    }
    // Check for components in this model.
    if (model->componentCount() > 0) {
        std::vector<std::string> componentNames;
        std::vector<std::string> componentRefs;
        std::vector<std::string> componentImportSources;
        for (size_t i = 0; i < model->componentCount(); ++i) {
            ComponentPtr component = model->getComponent(i);
            // Check for duplicate component names in this model.
            std::string componentName = component->getName();
            if (componentName.length()) {
                if (component->isImport()) {
                    // Check for a component_ref.
                    std::string componentRef = component->getImportReference();
                    std::string importSource = component->getImport()->getSource();
                    bool foundImportError = false;
                    if (!componentRef.length()) {
                        ErrorPtr err = std::make_shared<Error>();
                        err->setDescription("Imported component '" + componentName +
                                            "' does not have a valid component_ref attribute.");
                        err->setComponent(component);
                        err->setKind(Error::Kind::COMPONENT);
                        addError(err);
                        foundImportError = true;
                    }
                    // Check for a xlink:href.
                    if (!importSource.length()) {
                        ErrorPtr err = std::make_shared<Error>();
                        err->setDescription("Import of component '" + componentName +
                                            "' does not have a valid locator xlink:href attribute.");
                        err->setImport(component->getImport());
                        err->setKind(Error::Kind::IMPORT);
                        addError(err);
                        foundImportError = true;
                    }
                    // Check if we already have another import from the same source with the same component_ref.
                    // (This looks for matching enties at the same position in the source and ref vectors).
                    if ((componentImportSources.size() > 0) && (!foundImportError)) {
                        if ((std::find(componentImportSources.begin(), componentImportSources.end(), importSource) - componentImportSources.begin())
                         == (std::find(componentRefs.begin(), componentRefs.end(), componentRef) - componentRefs.begin())){
                            ErrorPtr err = std::make_shared<Error>();
                            err->setDescription("Model '" + model->getName() +
                                                "' contains multiple imported components from '" + importSource +
                                                "' with the same component_ref attribute '" + componentRef + "'.");
                            err->setModel(model);
                            err->setKind(Error::Kind::MODEL);
                            addError(err);
                        }
                    }
                    // Push back the unique sources and refs.
                    componentImportSources.push_back(importSource);
                    componentRefs.push_back(componentRef);
                }
                if(std::find(componentNames.begin(), componentNames.end(), componentName) != componentNames.end()) {
                    ErrorPtr err = std::make_shared<Error>();
                    err->setDescription("Model '" + model->getName() +
                                        "' contains multiple components with the name '" + componentName +
                                        "'. Valid component names should be unique to their model.");
                    err->setModel(model);
                    err->setKind(Error::Kind::MODEL);
                    addError(err);
                }
                componentNames.push_back(componentName);
            }
            // Validate component.
            validateComponent(component);
        }
    }
    // Check for units in this model.
    if (model->unitsCount() > 0) {
        std::vector<std::string> unitsNames;
        std::vector<std::string> unitsRefs;
        std::vector<std::string> unitsImportSources;
        for (size_t i = 0; i < model->unitsCount(); ++i) {
            UnitsPtr units = model->getUnits(i);
            std::string unitsName = units->getName();
            if (unitsName.length()) {
                if (units->isImport()) {
                    // Check for a units_ref.
                    std::string unitsRef = units->getImportReference();
                    std::string importSource = units->getImport()->getSource();
                    bool foundImportError = false;
                    if (!unitsRef.length()) {
                        ErrorPtr err = std::make_shared<Error>();
                        err->setDescription("Imported units '" + unitsName +
                                            "' does not have a valid units_ref attribute.");
                        err->setUnits(units);
                        err->setKind(Error::Kind::UNITS);
                        addError(err);
                        foundImportError = true;
                    }
                    // Check for a xlink:href.
                    if (!importSource.length()) {
                        ErrorPtr err = std::make_shared<Error>();
                        err->setDescription("Import of units '" + unitsName +
                                            "' does not have a valid locator xlink:href attribute.");
                        err->setImport(units->getImport());
                        err->setKind(Error::Kind::IMPORT);
                        addError(err);
                        foundImportError = true;
                    }
                    // Check if we already have another import from the same source with the same units_ref.
                    // (This looks for matching enties at the same position in the source and ref vectors).
                    if ((unitsImportSources.size() > 0) && (!foundImportError)) {
                        if ((std::find(unitsImportSources.begin(), unitsImportSources.end(), importSource) - unitsImportSources.begin())
                         == (std::find(unitsRefs.begin(), unitsRefs.end(), unitsRef) - unitsRefs.begin())){
                            ErrorPtr err = std::make_shared<Error>();
                            err->setDescription("Model '" + model->getName() +
                                                "' contains multiple imported units from '" + importSource +
                                                "' with the same units_ref attribute '" + unitsRef + "'.");
                            err->setModel(model);
                            err->setKind(Error::Kind::MODEL);
                            addError(err);
                        }
                    }
                    // Push back the unique sources and refs.
                    unitsImportSources.push_back(importSource);
                    unitsRefs.push_back(unitsRef);
                }
                // Check for duplicate units names in this model.
                if(std::find(unitsNames.begin(), unitsNames.end(), unitsName) != unitsNames.end()) {
                    ErrorPtr err = std::make_shared<Error>();
                    err->setDescription("Model '" + model->getName() +
                                        "' contains multiple units with the name '" + unitsName +
                                        "'. Valid units names should be unique to their model.");
                    err->setModel(model);
                    err->setKind(Error::Kind::MODEL);
                    addError(err);
                }
                unitsNames.push_back(unitsName);
            }
        }
        for (size_t i = 0; i < model->unitsCount(); ++i) {
            // Validate units.
            UnitsPtr units = model->getUnits(i);
            validateUnits(units, unitsNames);
        }
    }
}

void Validator::validateComponent(const ComponentPtr &component)
{
    // Check for a valid name attribute.
    if (!component->getName().length()) {
        ErrorPtr err = std::make_shared<Error>();
        err->setDescription("Component does not have a valid name attribute.");
        err->setComponent(component);
        err->setKind(Error::Kind::COMPONENT);
        addError(err);
    }
    // Check for units in this component.
    if (component->unitsCount() > 0) {
        std::vector<std::string> unitsNames;
        for (size_t i = 0; i < component->unitsCount(); ++i) {
            UnitsPtr units = component->getUnits(i);
            // Check for duplicate units names in this component.
            std::string unitsName = units->getName();
            if (unitsName.length()) {
                if(std::find(unitsNames.begin(), unitsNames.end(), unitsName) != unitsNames.end()) {
                    ErrorPtr err = std::make_shared<Error>();
                    err->setDescription("Component '" + component->getName() +
                                        "' contains multiple units with the name '" + unitsName +
                                        "'. Valid units names should be unique to their component.");
                    err->setComponent(component);
                    err->setKind(Error::Kind::COMPONENT);
                    addError(err);
                }
                unitsNames.push_back(unitsName);
            }
        }
        for (size_t i = 0; i < component->unitsCount(); ++i) {
            // Validate units.
            UnitsPtr units = component->getUnits(i);
            validateUnits(units, unitsNames);
        }
    }
    // Check for variables in this component.
    std::vector<std::string> variableNames;
    if (component->variableCount() > 0) {
        // Check for duplicate variable names and construct vector of valid names in case
        // we have a variable initial_value set by reference.
        for (size_t i = 0; i < component->variableCount(); ++i) {
            std::string variableName = component->getVariable(i)->getName();
            if (variableName.length()) {
                if(std::find(variableNames.begin(), variableNames.end(), variableName) != variableNames.end()) {
                    ErrorPtr err = std::make_shared<Error>();
                    err->setDescription("Component '" + component->getName() +
                                        "' contains multiple variables with the name '" + variableName +
                                        "'. Valid variable names should be unique to their component.");
                    err->setComponent(component);
                    err->setKind(Error::Kind::COMPONENT);
                    addError(err);
                }
                variableNames.push_back(variableName);
            }
        }
        // Validate variable(s).
        for (size_t i = 0; i < component->variableCount(); ++i) {
            VariablePtr variable = component->getVariable(i);
            validateVariable(variable, variableNames);
        }
    }
    // Validate math through the private implementation (for XML handling).
    if (component->getMath().length()) {
        mPimpl->validateMath(component->getMath(), component, variableNames);
    }
}

void Validator::validateUnits(const UnitsPtr &units, const std::vector<std::string> unitsNames)
{
    // Check for a valid name attribute.
    if (!units->getName().length()) {
        ErrorPtr err = std::make_shared<Error>();
        err->setDescription("Units does not have a valid name attribute.");
        err->setUnits(units);
        err->setKind(Error::Kind::UNITS);
        addError(err);
    } else {
        // TODO: Check that the units is not a Standard Unit. Probably want to convert the
        // STANDARD_UNIT_X types in units.h to a class enum, with a map to strings we can check against.
    }
    // Validate each unit in units.
    std::vector<std::string> unitErrors = units->getUnitValidationErrors(unitsNames);
    for (size_t i = 0; i < unitErrors.size(); ++i) {
        ErrorPtr err = std::make_shared<Error>();
        err->setDescription(unitErrors[i]);
        err->setUnits(units);
        err->setKind(Error::Kind::UNITS);
        addError(err);
    }

}

void Validator::validateVariable(const VariablePtr &variable, std::vector<std::string> &variableNames)
{
    // Check for a valid name attribute.
    if (!variable->getName().length()) {
        ErrorPtr err = std::make_shared<Error>();
        err->setDescription("Variable does not have a valid name attribute.");
        err->setVariable(variable);
        err->setKind(Error::Kind::VARIABLE);
        addError(err);
    }
    // Check for a valid units attribute.
    if (!variable->getUnits().length()) {
        ErrorPtr err = std::make_shared<Error>();
        err->setDescription("Variable '" + variable->getName() +
                            "' does not have a valid units attribute.");
        err->setVariable(variable);
        err->setKind(Error::Kind::VARIABLE);
        addError(err);
    }
    // Check for a valid interface attribute.
    if (variable->getInterfaceType().length()) {
        std::string interfaceType = variable->getInterfaceType();
        if ((interfaceType != "public") && (interfaceType != "private") &&
            (interfaceType != "none") && (interfaceType != "public_and_private")) {
            ErrorPtr err = std::make_shared<Error>();
            err->setDescription("Variable '" + variable->getName() +
                                "' has an invalid interface attribute value '" + interfaceType + "'.");
            err->setVariable(variable);
            err->setKind(Error::Kind::VARIABLE);
            addError(err);
        }
    }
    // Check for a valid initial value attribute.
    if (variable->getInitialValue().length()) {
        std::string initialValue = variable->getInitialValue();
        // Check if initial value is a variable reference
        if(!(std::find(variableNames.begin(), variableNames.end(), initialValue) != variableNames.end())) {
            // Otherwise, check that the initial value can be converted to a double
            if (catchDoubleConversionError(initialValue)) {
                ErrorPtr err = std::make_shared<Error>();
                err->setDescription("Variable '" + variable->getName() +
                                    "' has an invalid initial value '" + initialValue +
                                    "'. Initial values must be a real number string or a variable reference.");
                err->setVariable(variable);
                err->setKind(Error::Kind::VARIABLE);
                addError(err);
            }
        }
    }
}

void Validator::ValidatorImpl::validateMath(const std::string &input, const ComponentPtr &component, std::vector<std::string> &variableNames)
{
    std::string math = input;
    XmlDocPtr doc = std::make_shared<XmlDoc>();
    // Parse/validate this with the W3C MathML DTD.
    doc->parseMathML(math);
    // Copy any XML parsing or MathML validation errors into the common validator error handler.
    if (doc->xmlErrorCount() > 0) {
        for (size_t i = 0; i < doc->xmlErrorCount(); ++i) {
            ErrorPtr err = std::make_shared<Error>();
            err->setDescription(doc->getXmlError(i));
            err->setComponent(component);
            err->setKind(Error::Kind::MATHML);
            mValidator->addError(err);
        }
    }
    XmlNodePtr node = doc->getRootNode();
    XmlNodePtr nodeCopy(node);
    std::vector<std::string> bvarNames;
    // Get the bvar names in this math element.
    // TODO: may want to do this with XPath instead...
    gatherMathBvarVariableNames(nodeCopy, bvarNames);
    // Check that no variable names match new bvar names.
    for (std::string &variableName : variableNames) {
        if (std::find(bvarNames.begin(), bvarNames.end(), variableName) != bvarNames.end())
        {
            ErrorPtr err = std::make_shared<Error>();
            err->setDescription("MathML in component '" + component->getName() +
                                "' contains '" + variableName + "' as a bvar ci element but it is already a variable name.");
            err->setComponent(component);
            err->setKind(Error::Kind::MATHML);
            mValidator->addError(err);
        }
    }
    // Iterate through ci elements and units attributes.
    validateMathCiNodes(node, component, variableNames, bvarNames);
    // TODO: also need to validate <cn> elements as real numbers with cellml:units
}

void Validator::ValidatorImpl::validateMathCiNodes(XmlNodePtr &node, const ComponentPtr &component,
                                                   const std::vector<std::string> &variableNames,  const std::vector<std::string> &bvarNames)
{
    // TODO: also need to check for cellml:units (need to add to DTD)
    XmlNodePtr childNode = node->getFirstChild();
    if (node->isType("ci")) {
        if (childNode) {
            if (childNode->isType("text")) {
                std::string textNode = childNode->convertToString();
                if (isNotWhitespace(textNode)) {
                    // Check whether we can find this text as a variable name in this component.
                    if ((std::find(variableNames.begin(), variableNames.end(), textNode) == variableNames.end()) &&
                        (std::find(bvarNames.begin(), bvarNames.end(), textNode) == bvarNames.end())) {
                        ErrorPtr err = std::make_shared<Error>();
                        err->setDescription("MathML ci element has the child text '" + textNode +
                                            "', which does not correspond with any variable names present in component '" + component->getName() +
                                            "' and is not a variable defined within a bvar element.");
                        err->setComponent(component);
                        err->setKind(Error::Kind::MATHML);
                        mValidator->addError(err);
                    }
                } else {
                    ErrorPtr err = std::make_shared<Error>();
                    err->setDescription("MathML ci element has a whitespace-only child element.");
                    err->setComponent(component);
                    err->setKind(Error::Kind::MATHML);
                    mValidator->addError(err);
                }
            }
        } else {
            ErrorPtr err = std::make_shared<Error>();
            err->setDescription("MathML ci element has no valid variable.");
            err->setComponent(component);
            err->setKind(Error::Kind::MATHML);
            mValidator->addError(err);
        }
    } else {
        // Check children for ci.
        if (childNode) {
            validateMathCiNodes(childNode, component, variableNames, bvarNames);
        }
    }
    // Check siblings for ci.
    node = node->getNext();
    if (node) {
        validateMathCiNodes(node, component, variableNames, bvarNames);
    }
}

bool Validator::catchDoubleConversionError(const std::string &input)
{
    bool response = false;
    double value;
    // Try to convert the input string to double.
    try
    {
        value = std::stod(input);
    } catch (std::exception) {
        response = true;
        (void)value;
    }
    return response;
}

bool Validator::ValidatorImpl::isNotWhitespace (std::string &input)
{
    return input.find_first_not_of(" \t\n\v\f\r") != input.npos;
}

void Validator::ValidatorImpl::gatherMathBvarVariableNames(XmlNodePtr &node, std::vector<std::string> &bvarNames)
{
    XmlNodePtr childNode = node->getFirstChild();
    if (node->isType("bvar")) {
        if ((childNode) && (childNode->isType("ci"))) {
            XmlNodePtr grandchildNode = childNode->getFirstChild();
            if (grandchildNode) {
                std::string type = grandchildNode->getType();
                if (grandchildNode->isType("text")) {
                    std::string textNode = grandchildNode->convertToString();
                    if (isNotWhitespace(textNode)) {
                        bvarNames.push_back(textNode);
                    }
                }
            }
        }
    } else {
        // Check children for bvars.
        if (childNode) {
            gatherMathBvarVariableNames(childNode, bvarNames);
        }
    }
    // Check siblings for bvars.
    node = node->getNext();
    if (node) {
        gatherMathBvarVariableNames(node, bvarNames);
    }
}

}

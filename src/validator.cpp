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

struct Validator::ValidatorImpl
{
};

Validator::Validator()
    : mPimpl(new ValidatorImpl())
{
}

Validator::~Validator()
{
    delete mPimpl;
}

Validator::Validator(const Validator& rhs)
    : Logger(rhs)
    , mPimpl(new ValidatorImpl())
{
}

Validator::Validator(Validator &&rhs)
    : Logger(std::move(rhs))
    , mPimpl(rhs.mPimpl)
{
    rhs.mPimpl = nullptr;
}

Validator& Validator::operator=(Validator p)
{
    Logger::operator =(p);
    p.swap(*this);
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
        for (size_t i = 0; i < model->componentCount(); ++i) {
            ComponentPtr component = model->getComponent(i);
            // Check for duplicate component names in this model.
            std::string componentName = component->getName();
            if (componentName.length()) {
                //TODO: Check for import components
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
        std::vector<std::string> importSources;
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
                    if ((importSources.size() > 0) && (!foundImportError)) {
                        if ((std::find(importSources.begin(), importSources.end(), importSource) - importSources.begin())
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
                    importSources.push_back(importSource);
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
            // Validate units.
            validateUnits(units);
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
            // Validate units.
            validateUnits(units);
        }
    }
    // Check for variables in this component.
    if (component->variableCount() > 0) {
        std::vector<std::string> variableNames;
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
    // TODO: Maths validation here
}

void Validator::validateUnits(const UnitsPtr &units)
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
    // TODO: validateUnit
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

}

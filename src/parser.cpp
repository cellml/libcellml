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

#include "libcellml/parser.h"

#include <libcellml/model.h>
#include <libcellml/import.h>
#include <libcellml/variable.h>
#include <libcellml/component.h>
#include <libcellml/loggererrors.h>

#include "xmldoc.h"

namespace libcellml {

/**
 * @brief The Parser::ParserImpl struct.
 *
 * The private implementation for the Parser class.
 */
struct Parser::ParserImpl
{
    Format mFormat;
};

Parser::Parser(Format format)
    : mPimpl(new ParserImpl())
{
    mPimpl->mFormat = format;
}

Parser::~Parser()
{
    delete mPimpl;
}

Parser::Parser(const Parser& rhs)
    : Logger(rhs)
    , mPimpl(new ParserImpl())
{
    mPimpl->mFormat = rhs.mPimpl->mFormat;
}

Parser::Parser(Parser &&rhs)
    : Logger(std::move(rhs))
    , mPimpl(rhs.mPimpl)
{
    rhs.mPimpl = nullptr;
}

Parser& Parser::operator=(Parser p)
{
    Logger::operator =(p);
    p.swap(*this);
    return *this;
}

void Parser::swap(Parser &rhs)
{
    std::swap(this->mPimpl, rhs.mPimpl);
}

ModelPtr Parser::parseModel(const std::string &input)
{
    ModelPtr model = std::make_shared<Model>();
    updateModel(model, input);
    return model;
}

void Parser::updateModel(const ModelPtr &model, const std::string &input)
{
    if (mPimpl->mFormat == Format::XML) {
        XmlDocPtr doc = std::make_shared<XmlDoc>();
        doc->parse(input);
        const XmlNodePtr node = doc->getRootNode();
        if (node->isType("model")) {
            loadModel(model, node);
        } else {
            ModelErrorPtr err = std::make_shared<ModelError>();
            err->setDescription("Unexpected XML element type (not a model).");
            addError(err);
        }
    }
}

void Parser::loadModel(const ModelPtr &model, const XmlNodePtr &node)
{
    XmlAttributePtr attribute = node->getRootAttribute();
    while (attribute) {
        if (attribute->isType("name")) {
            model->setName(attribute->getValue());
        } else {
            ModelErrorPtr err = std::make_shared<ModelError>();
            err->setDescription("Invalid model attribute: '" + attribute->getType() + "' with value: '" + attribute->getValue() + "'.");
            addError(err);
        }
        attribute = attribute->getNext();
    }
    XmlNodePtr childNode = node->getChild();
    while (childNode) {
        if (childNode->isType("component")) {
            ComponentPtr component = std::make_shared<Component>();
            loadComponent(component, childNode);
            model->addComponent(component);
        } else if (childNode->isType("units")) {
            UnitsPtr units = std::make_shared<Units>();
            loadUnits(units, childNode);
            model->addUnits(units);
        } else if (childNode->isType("import")) {
            ImportPtr import = std::make_shared<Import>();
            loadImport(import, model, childNode);
        } else if (childNode->isType("encapsulation")) {
            XmlNodePtr componentRefNode = childNode->getChild();
            if (componentRefNode) {
                loadEncapsulation(model, componentRefNode);
            } else {
                ModelErrorPtr err = std::make_shared<ModelError>();
                err->setDescription("Encapsulation does not contain any component_ref");
                addError(err);
            }
        } else if (childNode->isType("connection")) {
            loadConnection(model, childNode);
        } else {
            ModelErrorPtr err = std::make_shared<ModelError>();
            if (model->getName() != "") {
                err->setDescription("Invalid XML element type '" + childNode->getType() + "' in model '" + model->getName() + "'.");
            } else {
                err->setDescription("Invalid XML element type '" + childNode->getType() + "' in unnamed model.");
            }
            addError(err);
        }
        childNode = childNode->getNext();
    }
}

void Parser::loadComponent(const ComponentPtr &component, const XmlNodePtr &node)
{
    XmlAttributePtr attribute = node->getRootAttribute();
    while (attribute) {
        if (attribute->isType("name")) {
            component->setName(attribute->getValue());
        } else {
            ComponentAttributeErrorPtr err = std::make_shared<ComponentAttributeError>();
            err->setType(attribute->getType());
            err->setComponent(component);
            addError(err);
        }
        attribute = attribute->getNext();
    }
    XmlNodePtr childNode = node->getChild();
    while (childNode) {
        if (childNode->isType("variable")) {
            VariablePtr variable = std::make_shared<Variable>();
            loadVariable(variable, childNode);
            component->addVariable(variable);
        } else if (childNode->isType("units")) {
            UnitsPtr units = std::make_shared<Units>();
            loadUnits(units, childNode);
            component->addUnits(units);
        } else if (childNode->isType("math")) {
            std::string math = childNode->convertToString();
            component->setMath(math);
        } else {
            ComponentElementErrorPtr err = std::make_shared<ComponentElementError>();
            err->setType(childNode->getType());
            err->setComponent(component);
            addError(err);
        }
        childNode = childNode->getNext();
    }
}

void Parser::loadUnits(const UnitsPtr &units, const XmlNodePtr &node)
{
    XmlAttributePtr attribute = node->getRootAttribute();
    while (attribute) {
        if (attribute->isType("name")) {
            units->setName(attribute->getValue());
        } else if (attribute->isType("base_unit")) {
            if (attribute->getValue() == "yes") {
                units->setBaseUnit(true);
            } else if (attribute->getValue() == "no") {
                units->setBaseUnit(false);
            } else {
                UnitsBaseUnitAttributeErrorPtr err = std::make_shared<UnitsBaseUnitAttributeError>();
                err->setUnits(units);
                err->setValue(node->getAttribute("base_unit"));
                addError(err);
            }
        } else {
            UnitsAttributeErrorPtr err = std::make_shared<UnitsAttributeError>();
            err->setType(attribute->getType());
            err->setUnits(units);
            addError(err);
        }
        attribute = attribute->getNext();
    }
    XmlNodePtr childNode = node->getChild();
    while (childNode) {
        if (childNode->isType("unit")) {
            std::string name = "";
            std::string prefix = "";
            double exponent = 1.0;
            double multiplier = 1.0;
            double offset = 0.0;
            attribute = childNode->getRootAttribute();
            while (attribute) {
                if (attribute->isType("units")) {
                    name = attribute->getValue();
                } else if (attribute->isType("prefix")) {
                    prefix = attribute->getValue();
                } else if (attribute->isType("exponent")) {
                    try
                    {
                        exponent = std::stod(attribute->getValue());
                    } catch (std::exception) {
                        UnitsExponentAttributeErrorPtr err = std::make_shared<UnitsExponentAttributeError>();
                        err->setUnits(units);
                        err->setValue(attribute->getValue());
                        addError(err);
                    }
                } else if (attribute->isType("multiplier")) {
                    try
                    {
                        multiplier = std::stod(attribute->getValue());
                    } catch (std::exception) {
                        UnitsMultiplierAttributeErrorPtr err = std::make_shared<UnitsMultiplierAttributeError>();
                        err->setUnits(units);
                        err->setValue(attribute->getValue());
                        addError(err);
                    }
                } else if (attribute->isType("offset")) {
                    try
                    {
                        offset = std::stod(attribute->getValue());
                    } catch (std::exception) {
                        UnitsOffsetAttributeErrorPtr err = std::make_shared<UnitsOffsetAttributeError>();
                        err->setUnits(units);
                        err->setValue(attribute->getValue());
                        addError(err);
                    }
                } else {
                    UnitAttributeErrorPtr err = std::make_shared<UnitAttributeError>();
                    err->setType(childNode->getType());
                    err->setUnits(units);
                    if (childNode->hasAttribute("units")) {
                        err->setUnitName(childNode->getAttribute("units"));
                    }
                    addError(err);
                }
                attribute = attribute->getNext();
            }
            units->addUnit(name, prefix, exponent, multiplier, offset);
        } else {
            UnitsElementErrorPtr err = std::make_shared<UnitsElementError>();
            err->setType(childNode->getType());
            err->setUnits(units);
            err->setParentLabel("element '" + node->getType() + "' with name '" + units->getName() + "'");
            addError(err);
        }
        childNode = childNode->getNext();
    }
}

void Parser::loadVariable(const VariablePtr &variable, const XmlNodePtr &node)
{
    XmlAttributePtr attribute = node->getRootAttribute();
    while (attribute) {
        if (attribute->isType("name")) {
            variable->setName(attribute->getValue());
        } else if (attribute->isType("units")) {
            variable->setUnits(attribute->getValue());
        } else if (attribute->isType("interface")) {
            variable->setInterfaceType(attribute->getValue());
        } else if (attribute->isType("initial_value")) {
            variable->setInitialValue(attribute->getValue());
        } else {
            VariableAttributeErrorPtr err = std::make_shared<VariableAttributeError>();
            err->setType(attribute->getType());
            err->setVariable(variable);
            addError(err);
        }
        attribute = attribute->getNext();
    }
}

void Parser::loadConnection(const ModelPtr &model, const XmlNodePtr &node)
{
    // Initialise connection components and variables.
    ComponentPtr component1 = nullptr;
    ComponentPtr component2 = nullptr;
    VariablePtr variable1 = nullptr;
    VariablePtr variable2 = nullptr;
    // Load the connection map_components.
    XmlNodePtr mapComponentsNode = node->getChild();
    if (!mapComponentsNode) {
        ModelErrorPtr err = std::make_shared<ModelError>();
        err->setDescription("Connection does not contain any child elements.");
        addError(err);
        return;
    }
    if (mapComponentsNode->isType("map_components")) {
        if (mapComponentsNode->hasAttribute("component_1")) {
            std::string componentName = mapComponentsNode->getAttribute("component_1");
            if (model->containsComponent(componentName)) {
                component1 = model->getComponent(componentName);
            } else {
                ModelErrorPtr err = std::make_shared<ModelError>();
                err->setDescription("Model does not contain the following component specified in a connection: " + componentName + ".");
                addError(err);
                return;
            }
            if (mapComponentsNode->hasAttribute("component_2")) {
                std::string componentName = mapComponentsNode->getAttribute("component_2");
                if (model->containsComponent(componentName)) {
                    component2 = model->getComponent(componentName);
                } else {
                    ModelErrorPtr err = std::make_shared<ModelError>();
                    err->setDescription("Model does not contain the following component specified in a connection: " + componentName + ".");
                    addError(err);
                    return;
                }
            }
        } else {
            ModelErrorPtr err = std::make_shared<ModelError>();
            err->setDescription("Connection map_components does not contain a component_1.");
            addError(err);
            return;
        }
    } else {
        ModelErrorPtr err = std::make_shared<ModelError>();
        err->setDescription("Connection does not contain a map_components.");
        addError(err);
        return;
    }

    // Load all connection map_variables.
    XmlNodePtr mapVariablesNode = mapComponentsNode->getNext();
    if (!mapVariablesNode) {
        ModelErrorPtr err = std::make_shared<ModelError>();
        err->setDescription("Connection only contains a map_components (no map_variables).");
        addError(err);
    }
    while (mapVariablesNode) {
        bool errorOccurred = false;
        variable1 = nullptr;
        if (mapVariablesNode->isType("map_variables")) {
            if (mapVariablesNode->hasAttribute("variable_1")) {
                std::string variableName = mapVariablesNode->getAttribute("variable_1");
                if (component1->hasVariable(variableName)) {
                    variable1 = component1->getVariable(variableName);
                } else if (component1->isImport()) {
                    /*
                     * With an imported component we are saying that you have entered a contract
                     * stating this variable exists in the imported component
                     */
                    variable1 = std::make_shared<Variable>();
                    variable1->setName(variableName);
                    component1->addVariable(variable1);
                } else {
                    VariableErrorPtr ve = std::make_shared<VariableError>();
                    ve->setComponent(component1);
                    ve->setValue(variableName);
                    addError(ve);
                    errorOccurred = true;
                }
                if (mapVariablesNode->hasAttribute("variable_2")) {
                    variable2 = nullptr;
                    std::string variableName = mapVariablesNode->getAttribute("variable_2");
                    if (component2) {
                        if (component2->hasVariable(variableName)) {
                            variable2 = component2->getVariable(variableName);
                        } else if (component2->isImport()) {
                            /*
                             * As above for component1, variable1.
                             */
                            variable2 = std::make_shared<Variable>();
                            variable2->setName(variableName);
                            component2->addVariable(variable2);
                        } else {
                            VariableErrorPtr ve = std::make_shared<VariableError>();
                            ve->setComponent(component2);
                            ve->setValue(variableName);
                            addError(ve);
                            errorOccurred = true;
                        }
                    } else {
                        ModelErrorPtr err = std::make_shared<ModelError>();
                        err->setDescription("Connection does not name a valid component_2 for connection "
                                            "between variables variable_1='" + variable1->getName() + "' "
                                            "and variable_2='" + variableName + "'.");
                        addError(err);
                        errorOccurred = true;
                    }
                } else {
                    ModelErrorPtr err = std::make_shared<ModelError>();
                    err->setDescription("Connection map_variables does not contain a variable_2.");
                    addError(err);
                    errorOccurred = true;
                }
            } else {
                ModelErrorPtr err = std::make_shared<ModelError>();
                err->setDescription("Connection map_variables does not contain a variable_1.");
                addError(err);
                errorOccurred = true;
            }
        } else {
            EntityElementErrorPtr err = std::make_shared<EntityElementError>();
            err->setType(mapVariablesNode->getType());
            err->setParentLabel("element '" + mapComponentsNode->getType() + "'");
            addError(err);
            errorOccurred = true;
        }

        // Set variable equivalence relationship.
        if (!errorOccurred) {
            Variable::addEquivalence(variable1, variable2);
        }
        // Continue on to next map_variables if one exists
        mapVariablesNode = mapVariablesNode->getNext();
    }
}

void Parser::loadEncapsulation(const ModelPtr &model, XmlNodePtr &parentComponentNode)
{
    while (parentComponentNode) {
        bool errorOccurred = false;
        ComponentPtr parentComponent = nullptr;
        if (parentComponentNode->isType("component_ref")) {
            if (parentComponentNode->hasAttribute("component")) {
                std::string parentComponentName = parentComponentNode->getAttribute("component");
                if (model->containsComponent(parentComponentName)) {
                    parentComponent = model->takeComponent(parentComponentName);
                } else {
                    ModelErrorPtr err = std::make_shared<ModelError>();
                    err->setDescription("Model does not contain the following component specified in an encapsulation: " + parentComponentName + ".");
                    addError(err);
                    errorOccurred = true;
                }
                // Get child components
                XmlNodePtr childComponentNode = parentComponentNode->getChild();
                if (!childComponentNode) {
                    ModelErrorPtr err = std::make_shared<ModelError>();
                    err->setDescription("Encapsulation contains no child components.");
                    addError(err);
                    errorOccurred = true;
                }
                while (childComponentNode) {
                    ComponentPtr childComponent = nullptr;
                    if (childComponentNode->isType("component_ref")) {
                        if (childComponentNode->hasAttribute("component")) {
                            std::string childComponentName = childComponentNode->getAttribute("component");
                            if (model->containsComponent(childComponentName)) {
                                childComponent = model->getComponent(childComponentName);
                            } else {
                                ModelErrorPtr err = std::make_shared<ModelError>();
                                err->setDescription("Model does not contain the following component specified in an encapsulation: " + childComponentName + ".");
                                addError(err);
                                errorOccurred = true;
                            }
                        } else {
                            ModelErrorPtr err = std::make_shared<ModelError>();
                            err->setDescription("Encapsulation component_ref does not contain a component.");
                            addError(err);
                            errorOccurred = true;
                        }
                    } else {
                        ModelErrorPtr err = std::make_shared<ModelError>();
                        err->setDescription("Encapsulation does not contain a component_ref.");
                        addError(err);
                        errorOccurred = true;
                    }
                    if (!errorOccurred) {
                        // Set parent/child relationship.
                        parentComponent->addComponent(childComponent);
                        // Load any further encapsulated children.
                        if (childComponentNode->getChild()) {
                            loadEncapsulation(model, childComponentNode);
                        }
                        // Load an encapsulated component only once through its parent.
                        model->removeComponent(childComponent);
                    }
                    if (childComponentNode) {
                        childComponentNode = childComponentNode->getNext();
                    }
                }
                model->addComponent(parentComponent);
            } else {
                ModelErrorPtr err = std::make_shared<ModelError>();
                err->setDescription("Encapsulation component_ref does not contain a component.");
                addError(err);
            }
        } else {
            ModelErrorPtr err = std::make_shared<ModelError>();
            err->setDescription("Encapsulation does not contain a component_ref.");
            addError(err);
        }
        // Get the next parent component at this level
        parentComponentNode = parentComponentNode->getNext();
    }
}

void Parser::loadImport(const ImportPtr &import, const ModelPtr &model, const XmlNodePtr &node)
{
    if (node->hasAttribute("href")) {
        import->setSource(node->getAttribute("href"));
    }
    XmlNodePtr childNode = node->getChild();
    while (childNode) {
        if (childNode->isType("component")) {
            ComponentPtr importedComponent = std::make_shared<Component>();
            if (childNode->hasAttribute("name")) {
                importedComponent->setName(childNode->getAttribute("name"));
            }
            if (childNode->hasAttribute("component_ref")) {
                importedComponent->setSourceComponent(import, childNode->getAttribute("component_ref"));
            }
            model->addComponent(importedComponent);
        }
        if (childNode->isType("units")) {
            UnitsPtr importedUnits = std::make_shared<Units>();
            if (childNode->hasAttribute("name")) {
                importedUnits->setName(childNode->getAttribute("name"));
            }
            if (childNode->hasAttribute("units_ref")) {
                importedUnits->setSourceUnits(import, childNode->getAttribute("units_ref"));
            }
            model->addUnits(importedUnits);
        }
        childNode = childNode->getNext();
    }
}

}

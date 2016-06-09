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
        if (node->isElementType("model")) {
            loadModel(model, node);
        } else {
            throw std::invalid_argument("Unexpected XML element type (not a model).");
        }
    } else {
        throw std::out_of_range("Unrecognised format specified.");
    }
}

void Parser::loadModel(const ModelPtr &model, const XmlNodePtr &node)
{
    if (node->hasAttribute("name")) {
        model->setName(node->getAttribute("name"));
    }
    XmlNodePtr childNode = node->getChild();
    while (childNode) {
        if (childNode->isElementType("component")) {
            ComponentPtr component = std::make_shared<Component>();
            loadComponent(component, childNode);
            model->addComponent(component);
        }
        if (childNode->isElementType("units")) {
            UnitsPtr units = std::make_shared<Units>();
            loadUnits(units, childNode);
            model->addUnits(units);
        }
        if (childNode->isElementType("import")) {
            ImportPtr import = std::make_shared<Import>();
            loadImport(import, model, childNode);
        }
        if (childNode->isElementType("encapsulation")) {
            XmlNodePtr componentRefNode = childNode->getChild();
            if (!componentRefNode) throw std::invalid_argument("Encapsulation does not contain any component_ref");
            loadEncapsulation(model, componentRefNode);
        }
        if (childNode->isElementType("connection")) {
            loadConnection(model, childNode);
        }
        childNode = childNode->getNext();
    }
}

void Parser::loadComponent(const ComponentPtr &component, const XmlNodePtr &node)
{
    if (node->hasAttribute("name")) {
        component->setName(node->getAttribute("name"));
    }
    XmlNodePtr childNode = node->getChild();
    while (childNode) {
        if (childNode->isElementType("variable")) {
            VariablePtr variable = std::make_shared<Variable>();
            loadVariable(variable, childNode);
            component->addVariable(variable);
        }
        if (childNode->isElementType("units")) {
            UnitsPtr units = std::make_shared<Units>();
            loadUnits(units, childNode);
            component->addUnits(units);
        }
        if (childNode->isElementType("math")) {
            std::string math = childNode->convertToString();
            component->setMath(math);
        }
        childNode = childNode->getNext();
    }
}

void Parser::loadUnits(const UnitsPtr &units, const XmlNodePtr &node)
{
    if (node->hasAttribute("name")) {
        units->setName(node->getAttribute("name"));
    }
    if (node->hasAttribute("base_unit")) {
        if (node->getAttribute("base_unit") == "yes") {
            units->setBaseUnit(true);
        } else if (node->getAttribute("base_unit") == "no") {
            units->setBaseUnit(false);
        } else {
            UnitsBaseUnitAttributeErrorPtr err = std::make_shared<UnitsBaseUnitAttributeError>();
            err->setUnits(units);
            addError(err);
        }
    }
    XmlNodePtr childNode = node->getChild();
    while (childNode) {
        if (childNode->isElementType("unit")) {
            std::string name = "";
            std::string prefix = "";
            double exponent = 1.0;
            double multiplier = 1.0;
            double offset = 0.0;
            if (childNode->hasAttribute("units")) {
                name = childNode->getAttribute("units");
            }
            if (childNode->hasAttribute("prefix")) {
                prefix = childNode->getAttribute("prefix");
            }
            if (childNode->hasAttribute("exponent")) {
                try
                {
                    exponent = std::stod(childNode->getAttribute("exponent"));
                } catch (std::invalid_argument) {
                    UnitsExponentAttributeErrorPtr err = std::make_shared<UnitsExponentAttributeError>();
                    err->setUnits(units);
                    addError(err);
                }
            }
            if (childNode->hasAttribute("multiplier")) {
                try
                {
                    multiplier = std::stod(childNode->getAttribute("multiplier"));
                } catch (std::invalid_argument) {
                    throw std::invalid_argument("Multiplier cannot be converted to a real number in unit: " + name);
                }
            }
            if (childNode->hasAttribute("offset")) {
                try
                {
                    offset = std::stod(childNode->getAttribute("offset"));
                } catch (std::invalid_argument) {
                    throw std::invalid_argument("Offset cannot be converted to a real number in unit: " + name);
                }
            }
            units->addUnit(name, prefix, exponent, multiplier, offset);
        } else {
            throw std::invalid_argument("Unrecognised child element in units: " + node->getAttribute("name"));
        }
        childNode = childNode->getNext();
    }
}

void Parser::loadVariable(const VariablePtr &variable, const XmlNodePtr &node)
{
    if (node->hasAttribute("name")) {
        variable->setName(node->getAttribute("name"));
    }
    if (node->hasAttribute("units")) {
        variable->setUnits(node->getAttribute("units"));
    }
    if (node->hasAttribute("interface")) {
        variable->setInterfaceType(node->getAttribute("interface"));
    }
    if (node->hasAttribute("initial_value")) {
        variable->setInitialValue(node->getAttribute("initial_value"));
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
    if (!mapComponentsNode) throw std::invalid_argument("Connection does not contain any child elements.");
    if (mapComponentsNode->isElementType("map_components")) {
        if (mapComponentsNode->hasAttribute("component_1")) {
            std::string componentName = mapComponentsNode->getAttribute("component_1");
            if (model->containsComponent(componentName)) {
                component1 = model->getComponent(componentName);
            } else {
                throw std::invalid_argument("Model does not contain the following component specified in a connection: " + componentName + ".");
            }
            if (mapComponentsNode->hasAttribute("component_2")) {
                std::string componentName = mapComponentsNode->getAttribute("component_2");
                if (model->containsComponent(componentName)) {
                    component2 = model->getComponent(componentName);
                } else {
                    throw std::invalid_argument("Model does not contain a the following component specified in a connection: " + componentName + ".");
                }
            }
        } else {
            throw std::invalid_argument("Connection map_components does not contain a component_1.");
        }
    } else {
        throw std::invalid_argument("Connection does not contain a map_components.");
    }

    // Load all connection map_variables.
    XmlNodePtr mapVariablesNode = mapComponentsNode->getNext();
    if (!mapVariablesNode) throw std::invalid_argument("Connection only contains a map_components (no map_variables).");
    while (mapVariablesNode) {
        variable1 = nullptr;
        if (mapVariablesNode->isElementType("map_variables")) {
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
                    ve->setName(variableName);
                    addError(ve);
                    break;
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
                            ve->setName(variableName);
                            addError(ve);
                        }
                    } else {
                        // Create a new variable if a parent component_2 does not exist
                        variable2 = std::make_shared<Variable>();
                        variable2->setName(variableName);
                    }
                } else {
                    throw std::invalid_argument("Connection map_variables does not contain a variable_2.");
                }
            } else {
                throw std::invalid_argument("Connection map_variables does not contain a variable_1.");
            }
        } else {
            throw std::invalid_argument("Unrecognised connection child- expected a map_variables.");
        }

        // Set variable equivalence relationship.
        Variable::addEquivalence(variable1, variable2);
        // Continue on to next map_variables if one exists
        mapVariablesNode = mapVariablesNode->getNext();
    }
}

void Parser::loadEncapsulation(const ModelPtr &model, XmlNodePtr &parentComponentNode)
{
    if (!parentComponentNode) throw std::invalid_argument("Encapsulation does not contain any elements.");
    while (parentComponentNode) {
        ComponentPtr parentComponent = nullptr;
        if (parentComponentNode->isElementType("component_ref")) {
            if (parentComponentNode->hasAttribute("component")) {
                std::string parentComponentName = parentComponentNode->getAttribute("component");
                if (model->containsComponent(parentComponentName)) {
                    parentComponent = model->takeComponent(parentComponentName);
                } else {
                    throw std::invalid_argument("Model does not contain the following component specified in an encapsulation: " + parentComponentName + ".");
                }
                // Get child components
                XmlNodePtr childComponentNode = parentComponentNode->getChild();
                if (!childComponentNode) throw std::invalid_argument("Encapsulation contains no child components.");
                while (childComponentNode) {
                    ComponentPtr childComponent = nullptr;
                    if (childComponentNode->isElementType("component_ref")) {
                        if (childComponentNode->hasAttribute("component")) {
                            std::string childComponentName = childComponentNode->getAttribute("component");
                            if (model->containsComponent(childComponentName)) {
                                childComponent = model->getComponent(childComponentName);
                            } else {
                                throw std::invalid_argument("Model does not contain the following component specified in an encapsulation: " + childComponentName + ".");
                            }
                        } else {
                            throw std::invalid_argument("Encapsulation component_ref does not contain a component.");
                        }
                    } else {
                        throw std::invalid_argument("Encapsulation does not contain a component_ref.");
                    }
                    // Set parent/child relationship.
                    parentComponent->addComponent(childComponent);
                    // Load any further encapsulated children.
                    if (childComponentNode->getChild()) loadEncapsulation(model, childComponentNode);
                    // Load an encapsulated component only once through its parent.
                    model->removeComponent(childComponent);
                    if (childComponentNode) childComponentNode = childComponentNode->getNext();
                }
                model->addComponent(parentComponent);
            } else {
                throw std::invalid_argument("Encapsulation component_ref does not contain a component.");
            }
        } else {
            throw std::invalid_argument("Encapsulation does not contain a component_ref.");
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
        if (childNode->isElementType("component")) {
            ComponentPtr importedComponent = std::make_shared<Component>();
            if (childNode->hasAttribute("name")) {
                importedComponent->setName(childNode->getAttribute("name"));
            }
            if (childNode->hasAttribute("component_ref")) {
                importedComponent->setSourceComponent(import, childNode->getAttribute("component_ref"));
            }
            model->addComponent(importedComponent);
        }
        if (childNode->isElementType("units")) {
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

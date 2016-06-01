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

#include "libcellml/model.h"

#include <map>
#include <vector>
#include <utility>
#include <stack>

#include <libcellml/import.h>
#include <libcellml/variable.h>
#include <libcellml/component.h>
#include <libcellml/units.h>

#include "xmlnode.h"

namespace libcellml {

Model::Model()
{
}

Model::~Model()
{
}

Model::Model(const Model& rhs)
    : ComponentEntity(rhs)
{
}

Model::Model(Model &&rhs)
    : ComponentEntity(std::move(rhs))
{
}

Model& Model::operator=(Model m)
{
    ComponentEntity::operator= (m);
    return *this;
}

std::string Model::doSerialisation(Format format) const
{
    // ImportMap
    typedef std::pair <std::string, std::string> ImportNamePair;
    typedef std::vector<ImportNamePair>::const_iterator VectorPairIterator;
    typedef std::map <ImportPtr, std::vector<ImportNamePair> > ImportMap;
    typedef ImportMap::const_iterator ImportMapIterator;
    ImportMap importMap;
    // VariableMap
    typedef std::pair <VariablePtr, VariablePtr> VariablePair;
    typedef std::vector<VariablePair> VariableMap;
    typedef VariableMap::const_iterator VariableMapIterator;
    VariableMap variableMap;
    // ComponentMap
    typedef std::pair <Component*, Component*> ComponentPair;
    typedef std::vector<ComponentPair> ComponentMap;
    typedef ComponentMap::const_iterator ComponentMapIterator;
    ComponentMap componentMap;
    ComponentMap serialisedComponentMap;

    // Gather all imports.
    std::stack<size_t> indeciesStack;
    std::stack<ComponentPtr> componentStack;
    bool incrementComponent = false;
    for (size_t i = 0; i < componentCount(); ++i) {
        ComponentPtr comp = getComponent(i);
        ComponentPtr modelComponent = comp;
        size_t index = 0;
        while (comp) {
            incrementComponent = false;
            if (comp->isImport()) {
                ImportNamePair pair = std::make_pair(comp->getImportReference(), comp->getName());
                ImportPtr imp = comp->getImport();
                if (!importMap.count(imp)) {
                    importMap[imp] = std::vector<ImportNamePair>();
                }
                importMap[imp].push_back(pair);
                incrementComponent = true;
            } else if (comp->componentCount()) {
                // If the current component is a model component
                // let the 'for' loop take care of the stack.
                if (modelComponent != comp) {
                    componentStack.push(comp);
                    indeciesStack.push(index);
                }
                index = 0;
                comp = comp->getComponent(index);
            } else {
                incrementComponent = true;
            }

            if (incrementComponent) {
                if (!componentStack.empty()) {
                    index = indeciesStack.top();
                    comp = componentStack.top();
                    indeciesStack.pop();
                    componentStack.pop();
                    index += 1;
                    if (index < comp->componentCount()) {
                        comp = comp->getComponent(index);
                    } else {
                        comp = nullptr;
                    }
                } else {
                    index = 0;
                    comp = nullptr;
                }
            }
        }
    }

    std::string repr = "";
    if (format == Format::XML) {
        repr += "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n<model xmlns=\"http://www.cellml.org/cellml/1.2#\"";
        if (getName().length()) {
            repr += " name=\"" + getName() + "\"";
        }
        bool endTag = false;
        if ((importMap.size() > 0) || (componentCount() > 0) || (unitsCount() > 0)){
            endTag = true;
            repr += ">";
        }

        for (ImportMapIterator iter = importMap.begin(); iter != importMap.end(); ++iter)
        {
            repr += "<import xlink:href=\"" + iter->first->getSource() + "\" xmlns:xlink=\"http://www.w3.org/1999/xlink\">";
            for (VectorPairIterator vectorIter = iter->second.begin(); vectorIter != iter->second.end(); ++vectorIter) {
                repr += "<component component_ref=\"" + std::get<0>(*vectorIter) + "\" name=\"" + std::get<1>(*vectorIter) + "\"/>";
            }
            repr += "</import>";
        }

        repr += serialiseUnits(format);

        // Serialise components of the model, imported components have already been dealt with at this point.
        for (size_t i = 0; i < componentCount(); ++i) {
            repr += getComponent(i)->serialise(format);
            // Build unique variable equivalence pairs (VariableMap) for connections.
            ComponentPtr component = getComponent(i);
            for (size_t j = 0; j < component->variableCount(); ++j) {
                VariablePtr variable = component->getVariable(j);
                if (variable->equivalentVariableCount() > 0) {
                    for (size_t k = 0; k < variable->equivalentVariableCount(); ++k) {
                        VariablePtr equivalentVariable = variable->getEquivalentVariable(k);
                        if (equivalentVariable->hasEquivalentVariable(variable)) {
                            VariablePair variablePair = std::make_pair(variable, equivalentVariable);
                            VariablePair reciprocalVariablePair = std::make_pair(equivalentVariable, variable);
                            bool pairFound = false;
                            for (VariableMapIterator iter = variableMap.begin(); iter < variableMap.end(); ++iter) {
                                if ((*iter == variablePair) || (*iter == reciprocalVariablePair)) {
                                    pairFound = true;
                                    break;
                                }
                            }
                            if (!pairFound) {
                                // Get parent components.
                                Component* component1 = static_cast<Component*>(variable->getParent());
                                Component* component2 = static_cast<Component*>(equivalentVariable->getParent());
                                // Do not serialise a variable's parent component in a connection if that variable no
                                // longer exists in that component. Allow serialisation of one componentless variable.
                                if (component1) {
                                    if (!component1->hasVariable(variable)) component1 = nullptr;
                                }
                                if (component2) {
                                    if (!component2->hasVariable(equivalentVariable)) component2 = nullptr;
                                }
                                // Add new unique variable equivalence pair to the VariableMap.
                                variableMap.push_back(variablePair);
                                // Also create a component map pair corresponding with the variable map pair.
                                ComponentPair componentPair = std::make_pair(component1, component2);
                                componentMap.push_back(componentPair);
                            }
                        }
                    }
                }
            }
        }
        // Serialise connections of the model.
        int componentMapIndex1 = 0;
        for (ComponentMapIterator iterPair = componentMap.begin(); iterPair < componentMap.end(); ++iterPair) {
            Component* currentComponent1 = iterPair->first;
            Component* currentComponent2 = iterPair->second;
            ComponentPair currentComponentPair = std::make_pair(currentComponent1, currentComponent2);
            ComponentPair reciprocalCurrentComponentPair = std::make_pair(currentComponent2, currentComponent1);
            // Check whether this set of map_components has already been serialised.
            bool pairFound = false;
            for (ComponentMapIterator serialisedIterPair = serialisedComponentMap.begin(); serialisedIterPair < serialisedComponentMap.end(); ++serialisedIterPair) {
                if ((*serialisedIterPair == currentComponentPair) || (*serialisedIterPair == reciprocalCurrentComponentPair)) {
                    pairFound = true;
                    break;
                }
            }
            // Continue to the next component pair if the current pair has already been serialised.
            if (pairFound) {
                ++componentMapIndex1;
                continue;
            }
            // Serialise out the new connection.
            std::string connection = "<connection><map_components";
            if (currentComponent1) {
                connection += " component_1=\"" + currentComponent1->getName() + "\"";
            }
            if (currentComponent2) {
                connection += " component_2=\"" + currentComponent2->getName() + "\"";
            }
            VariablePair variablePair = variableMap.at(componentMapIndex1);
            connection += "/><map_variables variable_1=\"" + variablePair.first->getName() + "\""
                                        + " variable_2=\"" + variablePair.second->getName() + "\"/>";
            // Check for subsequent variable equivalence pairs with the same parent components.
            int componentMapIndex2 = componentMapIndex1 + 1;
            for (ComponentMapIterator iterPair2 = iterPair + 1; iterPair2 < componentMap.end(); ++iterPair2) {
                Component* nextComponent1 = iterPair2->first;
                Component* nextComponent2 = iterPair2->second;
                VariablePair variablePair2 = variableMap.at(componentMapIndex2);
                if ((currentComponent1 == nextComponent1) && (currentComponent2 == nextComponent2)) {
                    connection += "<map_variables variable_1=\"" + variablePair2.first->getName() + "\""
                                                " variable_2=\"" + variablePair2.second->getName() + "\"/>";
                }
                ++componentMapIndex2;
            }
            connection += "</connection>";
            repr += connection;
            serialisedComponentMap.push_back(currentComponentPair);
            ++componentMapIndex1;
        }
        if (endTag) {
            repr += "</model>";
        } else {
            repr += "/>";
        }
    }

    return repr;
}

void Model::doDeserialisation(const XmlNodePtr &node)
{
    if (node->isElementType("model")) {
        if (node->hasAttribute("name")) {
            this->setName(node->getAttribute("name"));
        }
        XmlNodePtr childNode = node->getChild();
        while (childNode) {
            if (childNode->isElementType("component")) {
                ComponentPtr component = std::make_shared<Component>();
                component->deserialiseXmlNode(childNode);
                this->addComponent(component);
            }
            if (childNode->isElementType("units")) {
                UnitsPtr units = std::make_shared<Units>();
                units->deserialiseXmlNode(childNode);
                this->addUnits(units);
            }
            if (childNode->isElementType("import")) {
                ImportPtr import = std::make_shared<Import>();
                import->deserialiseXmlNode(childNode);
                this->addImport(import);
            }
            if (childNode->isElementType("encapsulation")) {
                XmlNodePtr componentRefNode = childNode->getChild();
                if (!componentRefNode) throw std::invalid_argument("Encapsulation does not contain any component_ref");
                deserialiseEncapsulation(componentRefNode);
            }
            if (childNode->isElementType("connection")) {
                deserialiseConnection(childNode);
            }
            childNode = childNode->getNext();
        }
    } else {
        throw std::invalid_argument("Unexpected XML element type.");
    }
}

void Model::doAddComponent(const ComponentPtr &c)
{
    // Check for cycles.
    if (!hasParent(c.get())) {
        c->setParent(this);
        ComponentEntity::doAddComponent(c);
    }
}

void Model::deserialiseConnection(const XmlNodePtr &node)
{
    // Deserialise connection map_components
    ComponentPtr component1 = nullptr;
    ComponentPtr component2 = nullptr;
    VariablePtr variable1 = nullptr;
    VariablePtr variable2 = nullptr;
    XmlNodePtr mapComponentsNode = node->getChild();
    if (!mapComponentsNode) throw std::invalid_argument("Connection does not contain any child elements");
    if (mapComponentsNode->isElementType("map_components")) {
        if (mapComponentsNode->hasAttribute("component_1")) {
            std::string componentName = mapComponentsNode->getAttribute("component_1");
            if (this->containsComponent(componentName)) {
                component1 = getComponent(componentName);
            } else {
                throw std::invalid_argument("Model does not contain the following component specified in a connection: " + componentName);
            }
            if (mapComponentsNode->hasAttribute("component_2")) {
                std::string componentName = mapComponentsNode->getAttribute("component_2");
                if (this->containsComponent(componentName)) {
                    component2 = getComponent(componentName);
                } else {
                    throw std::invalid_argument("Model does not contain a the following component specified in a connection: " + componentName);
                }
            }
        } else {
            throw std::invalid_argument("Connection map_components does not contain a component_1");
        }
    } else {
        throw std::invalid_argument("Connection does not contain a map_components");
    }

    // Deserialise connection map_variables
    XmlNodePtr mapVariablesNode = mapComponentsNode->getNext();
    if (!mapVariablesNode) throw std::invalid_argument("Connection only contains a map_components (no map_variables)");
    while (mapVariablesNode) {
        variable1 = nullptr;
        if (mapVariablesNode->isElementType("map_variables")) {
            if (mapVariablesNode->hasAttribute("variable_1")) {
                std::string variableName = mapVariablesNode->getAttribute("variable_1");
                if (component1->hasVariable(variableName)) {
                    variable1 = component1->getVariable(variableName);
                } else {
                    throw std::invalid_argument("Component '" + component1->getName() + "' does not contain the variable '" + variableName + "'.");
                }
                if (mapVariablesNode->hasAttribute("variable_2")) {
                    variable2 = nullptr;
                    std::string variableName = mapVariablesNode->getAttribute("variable_2");
                    if (component2) {
                        if (component2->hasVariable(variableName)) {
                            variable2 = component2->getVariable(variableName);
                        } else {
                            throw std::invalid_argument("Component '" + component2->getName() + "' does not contain the variable '" + variableName + "'.");
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
                throw std::invalid_argument("Connection map_variables does not contain a variable_1");
            }
        } else {
            throw std::invalid_argument("Connection does not contain a map_variables");
        }

        // Set variable equivalences
        Variable::addEquivalence(variable1, variable2);
        // Continue on to next map_variables if one exists
        mapVariablesNode = mapVariablesNode->getNext();
    }
}

void Model::deserialiseEncapsulation(XmlNodePtr &parentComponentNode)
{
    if (!parentComponentNode) throw std::invalid_argument("Encapsulation does not contain any elements");
    while (parentComponentNode) {
        ComponentPtr parentComponent = nullptr;
        if (parentComponentNode->isElementType("component_ref")) {
            if (parentComponentNode->hasAttribute("component")) {
                std::string componentName = parentComponentNode->getAttribute("component");
                if (this->containsComponent(componentName)) {
                    parentComponent = getComponent(componentName);
                } else {
                    throw std::invalid_argument("Model does not contain the following component specified in an encapsulation: " + componentName);
                }
                // Get child components
                XmlNodePtr childComponentNode = parentComponentNode->getChild();
                if (!childComponentNode) throw std::invalid_argument("Encapsulation contains no child components");
                while (childComponentNode) {
                    ComponentPtr childComponent = nullptr;
                    if (childComponentNode->isElementType("component_ref")) {
                        if (childComponentNode->hasAttribute("component")) {
                            std::string componentName = childComponentNode->getAttribute("component");
                            if (this->containsComponent(componentName)) {
                                childComponent = getComponent(componentName);
                            } else {
                                throw std::invalid_argument("Model does not contain the following component specified in an encapsulation: " + componentName);
                            }
                        } else {
                            throw std::invalid_argument("Encapsulation component_ref does not contain a component");
                        }
                    } else {
                        throw std::invalid_argument("Encapsulation does not contain a component_ref");
                    }
                    // Set parent/child relationship
                    parentComponent->addComponent(childComponent);
                    // Deserialise any further children
                    if (childComponentNode->getChild()) deserialiseEncapsulation(childComponentNode);
                    childComponentNode = childComponentNode->getNext();
                }
            } else {
                throw std::invalid_argument("Encapsulation component_ref does not contain a component");
            }
        } else {
            throw std::invalid_argument("Encapsulation does not contain a component_ref");
        }
        // Get the next parent component at this level
        parentComponentNode = parentComponentNode->getNext();
    }
}

}

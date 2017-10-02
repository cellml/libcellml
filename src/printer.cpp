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

#include "libcellml/printer.h"

#include <map>
#include <stack>
#include <utility>
#include <vector>

#include "libcellml/enumerations.h"
#include "libcellml/component.h"
#include "libcellml/importsource.h"
#include "libcellml/model.h"
#include "libcellml/units.h"
#include "libcellml/variable.h"

#include "utilities.h"

namespace libcellml {

/**
 * @brief The Printer::PrinterImpl struct.
 *
 * The private implementation for the Printer class.
 */
struct Printer::PrinterImpl
{
};

Printer::Printer()
    : mPimpl(new PrinterImpl())
{
}

Printer::~Printer()
{
    delete mPimpl;
}

Printer::Printer(const Printer& rhs)
    : Logger(rhs)
    , mPimpl(new PrinterImpl())
{
}

Printer::Printer(Printer &&rhs)
    : Logger(std::move(rhs))
    , mPimpl(rhs.mPimpl)
{
    rhs.mPimpl = nullptr;
}

Printer& Printer::operator=(Printer p)
{
    Logger::operator =(p);
    p.swap(*this);
    return *this;
}

void Printer::swap(Printer &rhs)
{
    std::swap(this->mPimpl, rhs.mPimpl);
}

std::string Printer::printUnits(UnitsPtr units) const
{
    std::string repr = "";
    if (units->getName().length()) {
        if (units->isImport()) {
            repr += "<import xlink:href=\"" + units->getImportSource()->getSource() + "\" xmlns:xlink=\"http://www.w3.org/1999/xlink\"";
            if (units->getImportSource()->getId().length()) {
                repr += " id=\"" + units->getImportSource()->getId() + "\"";
            }
            repr += "><units units_ref=\"" + units->getImportReference() + "\" name=\"" + units->getName() + "\"";
            if (units->getId().length()) {
                repr += " id=\"" + units->getId() + "\"";
            }
            repr += "/></import>";
        } else {
            bool endTag = false;
            repr += "<units name=\"" + units->getName() + "\"";
            if (units->getId().length()) {
                repr += " id=\"" + units->getId() + "\"";
            }
            if (units->unitCount() > 0) {
                endTag = true;
                repr += ">";
                for (size_t i = 0; i < units->unitCount(); ++i) {
                    std::string reference, prefix;
                    double exponent, multiplier;
                    units->getUnitAttributes(i, reference, prefix, exponent, multiplier);
                    repr += "<unit";
                    if (exponent != 1.0) {
                        repr += " exponent=\"" + convertDoubleToString(exponent) + "\"";
                    }
                    if (multiplier != 1.0) {
                        repr += " multiplier=\"" + convertDoubleToString(multiplier) + "\"";
                    }
                    if (prefix != "") {
                        repr += " prefix=\"" + prefix + "\"";
                    }
                    repr += " units=\"" + reference + "\"";
                    repr += "/>";
                }
            }
            if (endTag) {
                repr += "</units>";
            } else {
                repr += "/>";
            }
        }
    }

    return repr;
}

std::string Printer::printUnits(Units units) const
{
    return printUnits(std::shared_ptr<Units>(std::shared_ptr<Units>{}, &units));
}

std::string Printer::printComponent(ComponentPtr component) const
{
    std::string repr = "";
    if (component->isImport()) {
        return repr;
    }
    repr += "<component";
    std::string componentName = component->getName();
    if (componentName.length()) {
        repr += " name=\"" + componentName + "\"";
    }
    if (component->getId().length()) {
        repr += " id=\"" + component->getId() + "\"";
    }
    size_t variable_count = component->variableCount();
    if ((variable_count > 0) || (component->getMath().length())) {
        repr += ">";
        for (size_t i = 0; i < variable_count; ++i) {
            repr += printVariable(component->getVariable(i));
        }
        repr += component->getMath();
        repr += "</component>";
    } else {
        repr += "/>";
    }
    repr += printEncapsulation(component);
    return repr;
}

std::string Printer::printComponent(Component component) const
{
    return printComponent(std::shared_ptr<Component>(std::shared_ptr<Component>{}, &component));
}

std::string Printer::printVariable(VariablePtr variable) const
{
    std::string repr = "";
    repr += "<variable";
    std::string name = variable->getName();
    std::string id = variable->getId();
    std::string units = variable->getUnits();
    std::string intial_value = variable->getInitialValue();
    std::string interface_type = variable->getInterfaceType();
    if (name.length()) {
        repr += " name=\"" + name + "\"";
    }
    if (id.length()) {
        repr += " id=\"" + id + "\"";
    }
    if (units.length()) {
        repr += " units=\"" + units + "\"";
    }
    if (intial_value.length()) {
        repr += " initial_value=\"" + intial_value + "\"";
    }
    if (interface_type.length()) {
        repr += " interface=\"" + interface_type + "\"";
    }
    repr += "/>";
    return repr;
}

std::string Printer::printVariable(Variable variable) const
{
    return printVariable(std::shared_ptr<Variable>(std::shared_ptr<Variable>{}, &variable));
}

std::string Printer::printModel(ModelPtr model) const
{
    // ImportMap
    typedef std::pair <std::string, ComponentPtr> ImportPair;
    typedef std::vector<ImportPair>::const_iterator VectorPairIterator;
    typedef std::map <ImportSourcePtr, std::vector<ImportPair> > ImportMap;
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
    for (size_t i = 0; i < model->componentCount(); ++i) {
        ComponentPtr comp = model->getComponent(i);
        ComponentPtr modelComponent = comp;
        size_t index = 0;
        while (comp) {
            incrementComponent = false;
            if (comp->isImport()) {
                ImportPair pair = std::make_pair(comp->getImportReference(), comp);
                ImportSourcePtr importSource = comp->getImportSource();
                if (!importMap.count(importSource)) {
                    importMap[importSource] = std::vector<ImportPair>();
                }
                importMap[importSource].push_back(pair);
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
    repr += "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n<model xmlns=\"http://www.cellml.org/cellml/2.0#\"";
    if (model->getName().length()) {
        repr += " name=\"" + model->getName() + "\"";
    }
    if (model->getId().length()) {
        repr += " id=\"" + model->getId() + "\"";
    }
    bool endTag = false;
    if ((importMap.size() > 0) || (model->componentCount() > 0) || (model->unitsCount() > 0)){
        endTag = true;
        repr += ">";
    }

    for (ImportMapIterator iter = importMap.begin(); iter != importMap.end(); ++iter)
    {
        repr += "<import xlink:href=\"" + iter->first->getSource() + "\" xmlns:xlink=\"http://www.w3.org/1999/xlink\"";
        if (iter->first->getId().length() > 0) {
            repr += " id=\"" + iter->first->getId() + "\"";
        }
        repr += ">";
        for (VectorPairIterator vectorIter = iter->second.begin(); vectorIter != iter->second.end(); ++vectorIter) {
            ComponentPtr localComponent = std::get<1>(*vectorIter);
            repr += "<component component_ref=\"" + std::get<0>(*vectorIter) + "\" name=\"" + localComponent->getName() + "\"";
            if (localComponent->getId().length() > 0) {
                repr += " id=\"" + localComponent->getId() + "\"";
            }
            repr += "/>";
        }
        repr += "</import>";
    }

    for (size_t i = 0; i < model->unitsCount(); ++i) {
        repr += printUnits(model->getUnits(i));
    }

    // Serialise components of the model, imported components have already been dealt with at this point.
    for (size_t i = 0; i < model->componentCount(); ++i) {
        repr += printComponent(model->getComponent(i));
        // Build unique variable equivalence pairs (VariableMap) for connections.
        ComponentPtr component = model->getComponent(i);
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
                            // Do not serialise a variable's parent component in a connection if that variable no longer
                            // exists in that component. Allow serialisation of one componentless variable as an empty component_2.
                            if (component2) {
                                if (!component2->hasVariable(equivalentVariable)) {
                                    component2 = nullptr;
                                }
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
        // Check whether this set of connections has already been serialised.
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
        std::string connection = "<connection";
        if (currentComponent1) {
            connection += " component_1=\"" + currentComponent1->getName() + "\"";
        }
        if (currentComponent2) {
            connection += " component_2=\"" + currentComponent2->getName() + "\"";
        }
        VariablePair variablePair = variableMap.at(componentMapIndex1);
        connection += "><map_variables variable_1=\"" + variablePair.first->getName() + "\""
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

    return repr;
}

std::string Printer::printModel(Model model) const
{
    return printModel(std::shared_ptr<Model>(std::shared_ptr<Model>{}, &model));
}

std::string Printer::printModel(Model *model) const
{
    return printModel(std::shared_ptr<Model>(std::shared_ptr<Model>{}, model));
}

std::string Printer::printEncapsulation(ComponentPtr component) const
{
    const std::string encaps_tag = "<encapsulation>";
    const std::string encaps_end_tag = "</encapsulation>";
    std::string repr = "";
    std::string componentName = component->getName();
    std::string encaps = "";
    size_t component_count = component->componentCount();
    if (component_count) {
        encaps += encaps_tag;
        encaps += "<component_ref";
        if (componentName.length()) {
            encaps += " component=\"" + componentName + "\"";
        }
        encaps += ">";
    }
    for (size_t i = 0; i != component_count; ++i) {
        ComponentPtr encapsulated_component = component->getComponent(i);
        std::string comp = printComponent(encapsulated_component);
        std::size_t found = comp.find(encaps_tag);
        if (found == std::string::npos) {
            encaps += "<component_ref";
            if (encapsulated_component->getName().length()) {
                encaps += " component=\"" + encapsulated_component->getName() + "\"";
            }
            encaps += "/>";
        } else {
            std::string encaps_part = comp.substr(found);
            comp = comp.substr(0, found);
            found = encaps_part.find(encaps_tag);
            encaps_part.replace(found, encaps_tag.length(), "");
            found = encaps_part.find(encaps_end_tag);
            encaps_part.replace(found, encaps_end_tag.length(), "");
            encaps += encaps_part;
        }
        repr += comp;
    }

    if (component_count) {
        encaps += "</component_ref>" + encaps_end_tag;
    }
    repr += encaps;
    return repr;
}

}

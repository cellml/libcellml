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

#include "utilities.h"

#include "libcellml/component.h"
#include "libcellml/enumerations.h"
#include "libcellml/importsource.h"
#include "libcellml/model.h"
#include "libcellml/printer.h"
#include "libcellml/reset.h"
#include "libcellml/units.h"
#include "libcellml/variable.h"
#include "libcellml/when.h"

#include <iostream>
#include <map>
#include <stack>
#include <utility>
#include <vector>

namespace libcellml {

// VariableMap
using VariablePair = std::pair<VariablePtr, VariablePtr>; /**< Type definition for VariablePtr pair.*/
using VariableMap = std::vector<VariablePair>; /**< Type definition for vector of VariablePair.*/
using VariableMapIterator = VariableMap::const_iterator; /**< Type definition of const iterator for vector of VariablePair.*/
// ComponentMap
using ComponentPair = std::pair<Component*, Component*>; /**< Type definition for Component pointer pair.*/
using ComponentMap = std::vector<ComponentPair>; /**< Type definition for vector of ComponentPair.*/
using ComponentMapIterator = ComponentMap::const_iterator; /**< Type definition of const iterator for vector of ComponentPair.*/

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

Printer::Printer(const Printer &rhs)
    : Logger(rhs)
    , mPimpl(new PrinterImpl())
{
}

Printer::Printer(Printer &&rhs) noexcept
    : Logger(std::move(rhs))
    , mPimpl(rhs.mPimpl)
{
    rhs.mPimpl = nullptr;
}

Printer& Printer::operator=(Printer rhs)
{
    Logger::operator =(rhs);
    rhs.swap(*this);
    return *this;
}

void Printer::swap(Printer &rhs)
{
    std::swap(this->mPimpl, rhs.mPimpl);
}

std::string Printer::printUnits(const UnitsPtr &units) const
{
    std::string repr;
    if (!units->getName().empty()) {
        if (units->isImport()) {
            repr += R"(<import xlink:href=")" + units->getImportSource()->getUrl() + R"(" xmlns:xlink="http://www.w3.org/1999/xlink")";
            if (!units->getImportSource()->getId().empty()) {
                repr += R"( id=")" + units->getImportSource()->getId() + R"(")";
            }
            repr += R"(><units units_ref=")" + units->getImportReference() + R"(" name=")" + units->getName() + R"(")";
            if (!units->getId().empty()) {
                repr += R"( id=")" + units->getId() + R"(")";
            }
            repr += "/></import>";
        } else {
            bool endTag = false;
            repr += R"(<units name=")" + units->getName() + R"(")";
            if (!units->getId().empty()) {
                repr += R"( id=")" + units->getId() + R"(")";
            }
            if (units->unitCount() > 0) {
                endTag = true;
                repr += ">";
                for (size_t i = 0; i < units->unitCount(); ++i) {
                    std::string reference, prefix, id;
                    double exponent, multiplier;
                    units->getUnitAttributes(i, reference, prefix, exponent, multiplier, id);
                    repr += "<unit";
                    if (exponent != 1.0) {
                        repr += R"( exponent=")" + convertDoubleToString(exponent) + R"(")";
                    }
                    if (multiplier != 1.0) {
                        repr += R"( multiplier=")" + convertDoubleToString(multiplier) + R"(")";
                    }
                    if (!prefix.empty()) {
                        repr += R"( prefix=")" + prefix + R"(")";
                    }
                    repr += R"( units=")" + reference + R"(")";
                    if (!id.empty()) {
                        repr += R"( id=")" + id + R"(")";
                    }
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

std::string Printer::printComponent(const ComponentPtr &component) const
{
    std::string repr;
    if (component->isImport()) {
        return repr;
    }
    repr += "<component";
    std::string componentName = component->getName();
    if (!componentName.empty()) {
        repr += R"( name=")" + componentName + R"(")";
    }
    if (!component->getId().empty()) {
        repr += R"( id=")" + component->getId() + R"(")";
    }
    size_t variableCount = component->variableCount();
    size_t resetCount = component->resetCount();
    bool hasChildren = false;
    if (variableCount > 0 || resetCount > 0 || !component->getMath().empty()) {
        hasChildren = true;
    }
    if (hasChildren) {
        repr += ">";
        for (size_t i = 0; i < variableCount; ++i) {
            repr += printVariable(component->getVariable(i));
        }
        for (size_t i =0; i < resetCount; ++i) {
            repr += printReset(component->getReset(i));
        }
        repr += component->getMath();
        repr += "</component>";
    } else {
        repr += "/>";
    }
    // Traverse through children of this component and add them to the representation.
    for (size_t i = 0; i < component->componentCount(); ++i) {
        repr += printComponent(component->getComponent(i));
    }

    return repr;
}

std::string Printer::printComponent(Component component) const
{
    return printComponent(std::shared_ptr<Component>(std::shared_ptr<Component>{}, &component));
}

std::string printWhen(const WhenPtr &when)
{
    std::string repr = "<when";
    std::string id = when->getId();
    if (when->isOrderSet()) {
        repr += R"( order=")" + convertIntToString(when->getOrder()) + R"(")";
    }
    if (!id.empty()) {
        repr += R"( id=")" + id + R"(")";
    }
    std::string condition = when->getCondition();
    if (!condition.empty()) {
        repr += ">";
        repr += condition;
    }
    std::string value = when->getValue();
    if (!value.empty()) {
        if (condition.empty()) {
            repr += ">";
        }
        repr += value;
    }
    if (!condition.empty() || !value.empty()) {
        repr += "</when>";
    } else {
        repr += "/>";
    }
    return repr;
}

std::string Printer::printReset(const ResetPtr &reset) const
{
    std::string repr = "<reset";
    std::string id = reset->getId();
    VariablePtr variable = reset->getVariable();
    if (variable) {
        repr += R"( variable=")" + variable->getName() + R"(")";
    }
    if (reset->isOrderSet()) {
        repr += R"( order=")" + convertIntToString(reset->getOrder()) + R"(")";
    }
    if (!id.empty()) {
        repr += R"( id=")" + id + R"(")";
    }
    size_t when_count = reset->whenCount();
    if (when_count > 0) {
        repr += ">";
        for (size_t i = 0; i < when_count; ++i) {
            repr += printWhen(reset->getWhen(i));
        }
        repr += "</reset>";
    } else {
        repr += "/>";
    }
    return repr;
}

std::string Printer::printReset(Reset reset) const
{
    return printReset(std::shared_ptr<Reset>(std::shared_ptr<Reset>{}, &reset));
}

std::string Printer::printVariable(const VariablePtr &variable) const
{
    std::string repr;
    repr += "<variable";
    std::string name = variable->getName();
    std::string id = variable->getId();
    std::string units = variable->getUnits();
    std::string intialValue = variable->getInitialValue();
    std::string interfaceType = variable->getInterfaceType();
    if (!name.empty()) {
        repr += R"( name=")" + name + R"(")";
    }
    if (!units.empty()) {
        repr += R"( units=")" + units + R"(")";
    }
    if (!intialValue.empty()) {
        repr += R"( initial_value=")" + intialValue + R"(")";
    }
    if (!interfaceType.empty()) {
        repr += R"( interface=")" + interfaceType + R"(")";
    }
    if (!id.empty()) {
        repr += R"( id=")" + id + R"(")";
    }

    repr += "/>";
    return repr;
}

std::string Printer::printVariable(Variable variable) const
{
    return printVariable(std::shared_ptr<Variable>(std::shared_ptr<Variable>{}, &variable));
}

std::string printMapVariables(VariablePair variablePair)
{
    std::string mapVariables = R"(<map_variables variable_1=")" + variablePair.first->getName() + R"(")"
                                + R"( variable_2=")" + variablePair.second->getName() + R"(")";
    std::string mappingId = Variable::getEquivalenceMappingId(variablePair.first, variablePair.second);
    if (mappingId.length() > 0) {
        mapVariables += R"( id=")" + mappingId + R"(")";
    }
    mapVariables += "/>";
    return mapVariables;
}

std::string printConnections(ComponentMap componentMap, VariableMap variableMap)
{
    std::string connections;
    ComponentMap serialisedComponentMap;
    size_t componentMapIndex1 = 0;
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
        std::string mappingVariables;
        VariablePair variablePair = variableMap.at(componentMapIndex1);
        std::string connectionId = Variable::getEquivalenceConnectionId(variablePair.first, variablePair.second);
        mappingVariables += printMapVariables(variablePair);
        // Check for subsequent variable equivalence pairs with the same parent components.
        size_t componentMapIndex2 = componentMapIndex1 + 1;
        for (auto iterPair2 = iterPair + 1; iterPair2 < componentMap.end(); ++iterPair2) {
            Component* nextComponent1 = iterPair2->first;
            Component* nextComponent2 = iterPair2->second;
            VariablePair variablePair2 = variableMap.at(componentMapIndex2);
            if ((currentComponent1 == nextComponent1) && (currentComponent2 == nextComponent2)) {
                mappingVariables += printMapVariables(variablePair2);
                connectionId = Variable::getEquivalenceConnectionId(variablePair2.first, variablePair2.second);
            }
            ++componentMapIndex2;
        }
        // Serialise out the new connection.
        std::string connection = "<connection";
        if (currentComponent1 != nullptr) {
            connection += R"( component_1=")" + currentComponent1->getName() + R"(")";
        }
        if (currentComponent2 != nullptr) {
            connection += R"( component_2=")" + currentComponent2->getName() + R"(")";
        }
        if (connectionId.length() > 0) {
            connection += R"( id=")" + connectionId + R"(")";
        }
        connection += ">";
        connection += mappingVariables;
        connection += "</connection>";
        connections += connection;
        serialisedComponentMap.push_back(currentComponentPair);
        ++componentMapIndex1;
    }

    return connections;
}

void buildMaps(const ModelPtr &model, ComponentMap &componentMap, VariableMap &variableMap)
{
    for (size_t i = 0; i < model->componentCount(); ++i) {
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
                            auto component1 = static_cast<Component*>(variable->getParent());
                            auto component2 = static_cast<Component*>(equivalentVariable->getParent());
                            // Do not serialise a variable's parent component in a connection if that variable no longer
                            // exists in that component. Allow serialisation of one componentless variable as an empty component_2.
                            if (component2 != nullptr) {
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
}

std::string printEncapsulation(const ComponentPtr &component)
{
    std::string componentName = component->getName();
    std::string repr = "<component_ref";
    if (componentName.length() > 0) {
        repr += R"( component=")" + componentName + R"(")";
    }
    if (component->getEncapsulationId().length() > 0) {
        repr += R"( id=")" + component->getEncapsulationId() + R"(")";
    }
    size_t componentCount = component->componentCount();
    if (componentCount > 0) {
        repr += ">";
    } else {
        repr += "/>";
    }
    for (size_t i = 0; i < componentCount; ++i) {
        repr += printEncapsulation(component->getComponent(i));
    }
    if (componentCount > 0) {
        repr += "</component_ref>";
    }
    return repr;
}

std::string Printer::printModel(const ModelPtr &model) const
{
    // ImportMap
    using ImportPair = std::pair<std::string, ComponentPtr>;
    using ImportMap = std::map<ImportSourcePtr, std::vector<ImportPair>>;
    using ImportMapIterator = ImportMap::const_iterator;
    ImportMap importMap;
    VariableMap variableMap;
    ComponentMap componentMap;

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
                if (importMap.count(importSource) == 0u) {
                    importMap[importSource] = std::vector<ImportPair>();
                }
                importMap[importSource].push_back(pair);
                incrementComponent = true;
            } else if (comp->componentCount() != 0u) {
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

    std::string repr;
    repr += R"(<?xml version="1.0" encoding="UTF-8"?>
<model xmlns="http://www.cellml.org/cellml/2.0#")";
    if (!model->getName().empty()) {
        repr += R"( name=")" + model->getName() + R"(")";
    }
    if (!model->getId().empty()) {
        repr += R"( id=")" + model->getId() + R"(")";
    }
    bool endTag = false;
    if (!importMap.empty() || (model->componentCount() > 0) || (model->unitsCount() > 0)){
        endTag = true;
        repr += ">";
    }

    for (ImportMapIterator iter = importMap.begin(); iter != importMap.end(); ++iter)
    {
        repr += R"(<import xlink:href=")" + iter->first->getUrl() + R"(" xmlns:xlink="http://www.w3.org/1999/xlink")";
        if (iter->first->getId().length() > 0) {
            repr += R"( id=")" + iter->first->getId() + R"(")";
        }
        repr += ">";
        for (const auto &vectorIter : iter->second) {
            const ComponentPtr &localComponent = std::get<1>(vectorIter);
            repr += R"(<component component_ref=")" + std::get<0>(vectorIter) + R"(" name=")" + localComponent->getName() + R"(")";
            if (localComponent->getId().length() > 0) {
                repr += R"( id=")" + localComponent->getId() + R"(")";
            }
            repr += "/>";
        }
        repr += "</import>";
    }

    for (size_t i = 0; i < model->unitsCount(); ++i) {
        repr += printUnits(model->getUnits(i));
    }

    std::string componentEncapsulation;
    // Serialise components of the model, imported components have already been dealt with at this point.
    for (size_t i = 0; i < model->componentCount(); ++i) {
        ComponentPtr component = model->getComponent(i);
        repr += printComponent(component);
        if (component->componentCount() > 0) {
            componentEncapsulation += printEncapsulation(component);
        }
    }

    // Build unique variable equivalence pairs (ComponentMap, VariableMap) for connections.
    buildMaps(model, componentMap, variableMap);
    // Serialise connections of the model.
    repr += printConnections(componentMap, variableMap);

    if (componentEncapsulation.length() > 0) {
        repr += "<encapsulation";
        if (model->getEncapsulationId().length() > 0) {
            repr += R"( id=")" + model->getEncapsulationId() + R"(">)";
        } else {
            repr += ">";
        }
        repr += componentEncapsulation;
        repr += "</encapsulation>";
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

} // namespace libcellml

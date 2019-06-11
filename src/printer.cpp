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
#include <sstream>
#include <stack>
#include <utility>
#include <vector>

namespace libcellml {

// VariableMap
using VariablePair = std::pair<VariablePtr, VariablePtr>; /**< Type definition for VariablePtr pair.*/
using VariableMap = std::vector<VariablePair>; /**< Type definition for vector of VariablePair.*/
using VariableMapIterator = VariableMap::const_iterator; /**< Type definition of const iterator for vector of VariablePair.*/
// ComponentMap
using ComponentPair = std::pair<Component *, Component *>; /**< Type definition for Component pointer pair.*/
using ComponentMap = std::vector<ComponentPair>; /**< Type definition for vector of ComponentPair.*/
using ComponentMapIterator = ComponentMap::const_iterator; /**< Type definition of const iterator for vector of ComponentPair.*/

/**
 * @brief The Printer::PrinterImpl struct.
 *
 * The private implementation for the Printer class.
 */
struct Printer::PrinterImpl
{
    std::string printUnits(const UnitsPtr &units, const std::string &indent = "") const;
    std::string printComponent(const ComponentPtr &component, const std::string &indent = "") const;
    std::string printEncapsulation(const ComponentPtr &component, const std::string &indent = "") const;
    std::string printVariable(const VariablePtr &variable, const std::string &indent = "") const;
    std::string printReset(const ResetPtr &reset, const std::string &indent = "") const;
    std::string printWhen(const WhenPtr &when, const std::string &indent) const;
};

static const std::string tabIndent = "  ";
// Note: use the same number of spaces as libxml2 since we use it to format math
//       elements and this is done using a two-space indentation...

std::string printMapVariables(const VariablePair &variablePair, const std::string &indent)
{
    std::string mapVariables = indent + "<map_variables variable_1=\"" + variablePair.first->getName() + "\""
                               + " variable_2=\"" + variablePair.second->getName() + "\"";
    std::string mappingId = Variable::getEquivalenceMappingId(variablePair.first, variablePair.second);
    if (!mappingId.empty()) {
        mapVariables += " id=\"" + mappingId + "\"";
    }
    mapVariables += "/>\n";
    return mapVariables;
}

std::string printConnections(const ComponentMap &componentMap, const VariableMap &variableMap,
                             const std::string &indent)
{
    std::string connections;
    ComponentMap serialisedComponentMap;
    size_t componentMapIndex1 = 0;
    for (auto iterPair = componentMap.begin(); iterPair < componentMap.end(); ++iterPair) {
        Component *currentComponent1 = iterPair->first;
        Component *currentComponent2 = iterPair->second;
        ComponentPair currentComponentPair = std::make_pair(currentComponent1, currentComponent2);
        ComponentPair reciprocalCurrentComponentPair = std::make_pair(currentComponent2, currentComponent1);
        // Check whether this set of connections has already been serialised.
        bool pairFound = false;
        for (const auto &serialisedIterPair : serialisedComponentMap) {
            if ((serialisedIterPair == currentComponentPair) || (serialisedIterPair == reciprocalCurrentComponentPair)) {
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
        mappingVariables += printMapVariables(variablePair, indent + tabIndent);
        // Check for subsequent variable equivalence pairs with the same parent components.
        size_t componentMapIndex2 = componentMapIndex1 + 1;
        for (auto iterPair2 = iterPair + 1; iterPair2 < componentMap.end(); ++iterPair2) {
            Component *nextComponent1 = iterPair2->first;
            Component *nextComponent2 = iterPair2->second;
            VariablePair variablePair2 = variableMap.at(componentMapIndex2);
            if ((currentComponent1 == nextComponent1) && (currentComponent2 == nextComponent2)) {
                mappingVariables += printMapVariables(variablePair2, indent + tabIndent);
                connectionId = Variable::getEquivalenceConnectionId(variablePair2.first, variablePair2.second);
            }
            ++componentMapIndex2;
        }
        // Serialise out the new connection.
        std::string connection = indent + "<connection";
        if (currentComponent1 != nullptr) {
            connection += " component_1=\"" + currentComponent1->getName() + "\"";
        }
        if (currentComponent2 != nullptr) {
            connection += " component_2=\"" + currentComponent2->getName() + "\"";
        }
        if (!connectionId.empty()) {
            connection += " id=\"" + connectionId + "\"";
        }
        connection += ">\n";
        connection += mappingVariables;
        connection += indent + "</connection>\n";
        connections += connection;
        serialisedComponentMap.push_back(currentComponentPair);
        ++componentMapIndex1;
    }

    return connections;
}

std::string printMath(const std::string &math, const std::string &indent)
{
    std::string repr;
    std::istringstream lines(math);
    std::string line;
    while (std::getline(lines, line, '\n')) {
        repr += indent + line + "\n";
    }
    return repr;
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
                        for (const auto &iter : variableMap) {
                            if ((iter == variablePair) || (iter == reciprocalVariablePair)) {
                                pairFound = true;
                                break;
                            }
                        }
                        if (!pairFound) {
                            // Get parent components.
                            auto component1 = static_cast<Component *>(variable->getParent());
                            auto component2 = static_cast<Component *>(equivalentVariable->getParent());
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
                            ComponentPair iterPair = std::make_pair(component1, component2);
                            componentMap.push_back(iterPair);
                        }
                    }
                }
            }
        }
    }
}

std::string Printer::PrinterImpl::printUnits(const UnitsPtr &units, const std::string &indent) const
{
    std::string repr;
    if (!units->getName().empty()) {
        if (units->isImport()) {
            repr += indent + "<import xlink:href=\"" + units->getImportSource()->getUrl() + "\" xmlns:xlink=\"http://www.w3.org/1999/xlink\"";
            if (!units->getImportSource()->getId().empty()) {
                repr += " id=\"" + units->getImportSource()->getId() + "\"";
            }
            repr += ">\n" + indent + tabIndent + "<units units_ref=\"" + units->getImportReference() + "\" name=\"" + units->getName() + "\"";
            if (!units->getId().empty()) {
                repr += " id=\"" + units->getId() + "\"";
            }
            repr += "/>\n" + indent + "</import>\n";
        } else {
            bool endTag = false;
            repr += indent + "<units name=\"" + units->getName() + "\"";
            if (!units->getId().empty()) {
                repr += " id=\"" + units->getId() + "\"";
            }
            if (units->unitCount() > 0) {
                endTag = true;
                repr += ">\n";
                for (size_t i = 0; i < units->unitCount(); ++i) {
                    std::string reference;
                    std::string prefix;
                    std::string id;
                    double exponent;
                    double multiplier;
                    units->getUnitAttributes(i, reference, prefix, exponent, multiplier, id);
                    repr += indent + tabIndent + "<unit";
                    if (exponent != 1.0) {
                        repr += " exponent=\"" + convertDoubleToString(exponent) + "\"";
                    }
                    if (multiplier != 1.0) {
                        repr += " multiplier=\"" + convertDoubleToString(multiplier) + "\"";
                    }
                    if (!prefix.empty()) {
                        repr += " prefix=\"" + prefix + "\"";
                    }
                    repr += " units=\"" + reference + "\"";
                    if (!id.empty()) {
                        repr += " id=\"" + id + "\"";
                    }
                    repr += "/>\n";
                }
            }
            if (endTag) {
                repr += indent + "</units>\n";
            } else {
                repr += "/>\n";
            }
        }
    }

    return repr;
}

std::string Printer::PrinterImpl::printComponent(const ComponentPtr &component, const std::string &indent) const
{
    std::string repr;
    if (component->isImport()) {
        return repr;
    }
    repr += indent + "<component";
    std::string componentName = component->getName();
    if (!componentName.empty()) {
        repr += " name=\"" + componentName + "\"";
    }
    if (!component->getId().empty()) {
        repr += " id=\"" + component->getId() + "\"";
    }
    size_t variableCount = component->variableCount();
    size_t resetCount = component->resetCount();
    bool hasChildren = false;
    if (variableCount > 0 || resetCount > 0 || !component->getMath().empty()) {
        hasChildren = true;
    }
    if (hasChildren) {
        repr += ">\n";
        for (size_t i = 0; i < variableCount; ++i) {
            repr += printVariable(component->getVariable(i), indent + tabIndent);
        }
        for (size_t i = 0; i < resetCount; ++i) {
            repr += printReset(component->getReset(i), indent + tabIndent);
        }
        if (!component->getMath().empty()) {
            repr += printMath(component->getMath(), indent + tabIndent);
        }
        repr += indent + "</component>\n";
    } else {
        repr += "/>\n";
    }
    // Traverse through children of this component and add them to the representation.
    for (size_t i = 0; i < component->componentCount(); ++i) {
        repr += printComponent(component->getComponent(i), indent);
    }

    return repr;
}

std::string Printer::PrinterImpl::printEncapsulation(const ComponentPtr &component, const std::string &indent) const
{
    std::string componentName = component->getName();
    std::string repr = indent + "<component_ref";
    if (!componentName.empty()) {
        repr += " component=\"" + componentName + "\"";
    }
    if (!component->getEncapsulationId().empty()) {
        repr += " id=\"" + component->getEncapsulationId() + "\"";
    }
    size_t componentCount = component->componentCount();
    if (componentCount > 0) {
        repr += ">\n";
    } else {
        repr += "/>\n";
    }
    for (size_t i = 0; i < componentCount; ++i) {
        repr += printEncapsulation(component->getComponent(i), indent + tabIndent);
    }
    if (componentCount > 0) {
        repr += indent + "</component_ref>\n";
    }
    return repr;
}

std::string Printer::PrinterImpl::printVariable(const VariablePtr &variable, const std::string &indent) const
{
    std::string repr;
    repr += indent + "<variable";
    std::string name = variable->getName();
    std::string id = variable->getId();
    std::string units = variable->getUnits();
    std::string intial_value = variable->getInitialValue();
    std::string interface_type = variable->getInterfaceType();
    if (!name.empty()) {
        repr += " name=\"" + name + "\"";
    }
    if (!units.empty()) {
        repr += " units=\"" + units + "\"";
    }
    if (!intial_value.empty()) {
        repr += " initial_value=\"" + intial_value + "\"";
    }
    if (!interface_type.empty()) {
        repr += " interface=\"" + interface_type + "\"";
    }
    if (!id.empty()) {
        repr += " id=\"" + id + "\"";
    }

    repr += "/>\n";
    return repr;
}

std::string Printer::PrinterImpl::printReset(const ResetPtr &reset, const std::string &indent) const
{
    std::string repr = indent + "<reset";
    std::string id = reset->getId();
    VariablePtr variable = reset->getVariable();
    if (variable) {
        repr += " variable=\"" + variable->getName() + "\"";
    }
    if (reset->isOrderSet()) {
        repr += " order=\"" + convertIntToString(reset->getOrder()) + "\"";
    }
    if (!id.empty()) {
        repr += " id=\"" + id + "\"";
    }
    size_t when_count = reset->whenCount();
    if (when_count > 0) {
        repr += ">\n";
        for (size_t i = 0; i < when_count; ++i) {
            repr += printWhen(reset->getWhen(i), indent + tabIndent);
        }
        repr += indent + "</reset>\n";
    } else {
        repr += "/>\n";
    }
    return repr;
}

std::string Printer::PrinterImpl::printWhen(const WhenPtr &when, const std::string &indent) const
{
    std::string repr = indent + "<when";
    std::string id = when->getId();
    if (when->isOrderSet()) {
        repr += " order=\"" + convertIntToString(when->getOrder()) + "\"";
    }
    if (!id.empty()) {
        repr += " id=\"" + id + "\"";
    }
    std::string condition = when->getCondition();
    bool hasCondition = !condition.empty();
    if (hasCondition) {
        repr += ">\n";
        repr += printMath(condition, indent + tabIndent);
    }
    std::string value = when->getValue();
    bool hasValue = !value.empty();
    if (hasValue) {
        if (!hasCondition) {
            repr += ">\n";
        }
        repr += printMath(value, indent + tabIndent);
    }
    if (hasCondition || hasValue) {
        repr += indent + "</when>\n";
    } else {
        repr += "/>\n";
    }
    return repr;
}

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

Printer &Printer::operator=(Printer rhs)
{
    Logger::operator=(rhs);
    rhs.swap(*this);
    return *this;
}

void Printer::swap(Printer &rhs)
{
    std::swap(this->mPimpl, rhs.mPimpl);
}

std::string Printer::printUnits(const UnitsPtr &units) const
{
    return mPimpl->printUnits(units);
}

std::string Printer::printUnits(Units units) const
{
    return mPimpl->printUnits(std::shared_ptr<Units>(std::shared_ptr<Units> {}, &units));
}

std::string Printer::printComponent(const ComponentPtr &component) const
{
    return mPimpl->printComponent(component);
}

std::string Printer::printComponent(Component component) const
{
    return mPimpl->printComponent(std::shared_ptr<Component>(std::shared_ptr<Component> {}, &component));
}

std::string Printer::printReset(const ResetPtr &reset) const
{
    return mPimpl->printReset(reset);
}

std::string Printer::printReset(Reset reset) const
{
    return mPimpl->printReset(std::shared_ptr<Reset>(std::shared_ptr<Reset> {}, &reset));
}

std::string Printer::printVariable(const VariablePtr &variable) const
{
    return mPimpl->printVariable(variable);
}

std::string Printer::printVariable(Variable variable) const
{
    return mPimpl->printVariable(std::shared_ptr<Variable>(std::shared_ptr<Variable> {}, &variable));
}

std::string Printer::printModel(const ModelPtr &model) const
{
    // ImportMap
    using ImportPair = std::pair<std::string, ComponentPtr>;
    using ImportMap = std::map<ImportSourcePtr, std::vector<ImportPair>>;
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
                if (importMap.count(importSource) == 0) {
                    importMap[importSource] = std::vector<ImportPair>();
                }
                importMap[importSource].push_back(pair);
                incrementComponent = true;
            } else if (comp->componentCount() != 0) {
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
    repr += "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n<model xmlns=\"http://www.cellml.org/cellml/2.0#\"";
    if (!model->getName().empty()) {
        repr += " name=\"" + model->getName() + "\"";
    }
    if (!model->getId().empty()) {
        repr += " id=\"" + model->getId() + "\"";
    }
    bool endTag = false;
    if (!importMap.empty() || (model->componentCount() > 0) || (model->unitsCount() > 0)) {
        endTag = true;
        repr += ">\n";
    }

    for (const auto &iter : importMap) {
        repr += tabIndent + "<import xlink:href=\"" + iter.first->getUrl() + "\" xmlns:xlink=\"http://www.w3.org/1999/xlink\"";
        if (!iter.first->getId().empty()) {
            repr += " id=\"" + iter.first->getId() + "\"";
        }
        repr += ">\n";
        for (const auto &vectorIter : iter.second) {
            const ComponentPtr &localComponent = std::get<1>(vectorIter);
            repr += tabIndent + tabIndent + "<component component_ref=\"" + std::get<0>(vectorIter) + "\" name=\"" + localComponent->getName() + "\"";
            if (!localComponent->getId().empty()) {
                repr += " id=\"" + localComponent->getId() + "\"";
            }
            repr += "/>\n";
        }
        repr += tabIndent + "</import>\n";
    }

    for (size_t i = 0; i < model->unitsCount(); ++i) {
        repr += mPimpl->printUnits(model->getUnits(i), tabIndent);
    }

    std::string componentEncapsulation;
    // Serialise components of the model, imported components have already been dealt with at this point.
    for (size_t i = 0; i < model->componentCount(); ++i) {
        ComponentPtr component = model->getComponent(i);
        repr += mPimpl->printComponent(component, tabIndent);
        if (component->componentCount() > 0) {
            componentEncapsulation += mPimpl->printEncapsulation(component, tabIndent + tabIndent);
        }
    }

    // Build unique variable equivalence pairs (ComponentMap, VariableMap) for connections.
    buildMaps(model, componentMap, variableMap);
    // Serialise connections of the model.
    repr += printConnections(componentMap, variableMap, tabIndent);

    if (!componentEncapsulation.empty()) {
        repr += tabIndent + "<encapsulation";
        if (!model->getEncapsulationId().empty()) {
            repr += " id=\"" + model->getEncapsulationId() + "\">\n";
        } else {
            repr += ">\n";
        }
        repr += componentEncapsulation;
        repr += tabIndent + "</encapsulation>\n";
    }
    if (endTag) {
        repr += "</model>\n";
    } else {
        repr += "/>\n";
    }

    return repr;
}

std::string Printer::printModel(Model model) const
{
    return printModel(std::shared_ptr<Model>(std::shared_ptr<Model> {}, &model));
}

std::string Printer::printModel(Model *model) const
{
    return printModel(std::shared_ptr<Model>(std::shared_ptr<Model> {}, model));
}

} // namespace libcellml

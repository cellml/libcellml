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

#include <list>
#include <map>
#include <sstream>
#include <stack>
#include <utility>
#include <vector>

#include "libcellml/component.h"
#include "libcellml/enumerations.h"
#include "libcellml/importsource.h"
#include "libcellml/model.h"
#include "libcellml/reset.h"
#include "libcellml/units.h"
#include "libcellml/variable.h"

#include "utilities.h"
#include "xmldoc.h"

namespace libcellml {

// VariableMap
using VariablePair = std::pair<VariablePtr, VariablePtr>; /**< Type definition for VariablePtr pair.*/
using VariableMap = std::vector<VariablePair>; /**< Type definition for vector of VariablePair.*/
using VariableMapIterator = VariableMap::const_iterator; /**< Type definition of const iterator for vector of VariablePair.*/
// ComponentMap
using ComponentPair = std::pair<ComponentPtr, ComponentPtr>; /**< Type definition for Component pointer pair.*/
using ComponentMap = std::vector<ComponentPair>; /**< Type definition for vector of ComponentPair.*/
using ComponentMapIterator = ComponentMap::const_iterator; /**< Type definition of const iterator for vector of ComponentPair.*/

/**
 * @brief The Printer::PrinterImpl struct.
 *
 * The private implementation for the Printer class.
 */
struct Printer::PrinterImpl
{
    std::string printUnits(const UnitsPtr &units) const;
    std::string printComponent(const ComponentPtr &component) const;
    std::string printEncapsulation(const ComponentPtr &component) const;
    std::string printVariable(const VariablePtr &variable) const;
    std::string printReset(const ResetPtr &reset) const;
    std::string printResetChild(const std::string &childLabel, const std::string &childId, const std::string &math) const;
};

std::string printMapVariables(const VariablePair &variablePair)
{
    std::string mapVariables = "<map_variables variable_1=\"" + variablePair.first->name() + "\""
                               + " variable_2=\"" + variablePair.second->name() + "\"";
    std::string mappingId = Variable::equivalenceMappingId(variablePair.first, variablePair.second);
    if (!mappingId.empty()) {
        mapVariables += " id=\"" + mappingId + "\"";
    }
    mapVariables += "/>";
    return mapVariables;
}

std::string printConnections(const ComponentMap &componentMap, const VariableMap &variableMap)
{
    std::string connections;
    ComponentMap serialisedComponentMap;
    size_t componentMapIndex1 = 0;
    for (auto iterPair = componentMap.begin(); iterPair < componentMap.end(); ++iterPair) {
        ComponentPtr currentComponent1 = iterPair->first;
        ComponentPtr currentComponent2 = iterPair->second;
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
        std::string connectionId = Variable::equivalenceConnectionId(variablePair.first, variablePair.second);
        mappingVariables += printMapVariables(variablePair);
        // Check for subsequent variable equivalence pairs with the same parent components.
        size_t componentMapIndex2 = componentMapIndex1 + 1;
        for (auto iterPair2 = iterPair + 1; iterPair2 < componentMap.end(); ++iterPair2) {
            ComponentPtr nextComponent1 = iterPair2->first;
            ComponentPtr nextComponent2 = iterPair2->second;
            VariablePair variablePair2 = variableMap.at(componentMapIndex2);
            if ((currentComponent1 == nextComponent1) && (currentComponent2 == nextComponent2)) {
                mappingVariables += printMapVariables(variablePair2);
                connectionId = Variable::equivalenceConnectionId(variablePair2.first, variablePair2.second);
            }
            ++componentMapIndex2;
        }
        // Serialise out the new connection.
        connections += "<connection";
        if (currentComponent1 != nullptr) {
            connections += " component_1=\"" + currentComponent1->name() + "\"";
        }
        if (currentComponent2 != nullptr) {
            connections += " component_2=\"" + currentComponent2->name() + "\"";
        }
        if (!connectionId.empty()) {
            connections += " id=\"" + connectionId + "\"";
        }
        connections += ">" + mappingVariables + "</connection>";
        serialisedComponentMap.push_back(currentComponentPair);
        ++componentMapIndex1;
    }

    return connections;
}

std::string printMath(const std::string &math)
{
    std::string repr;
    std::istringstream lines(math);
    std::string line;
    while (std::getline(lines, line)) {
        repr += line;
    }
    return repr;
}

void buildMapsForComponentsVariables(const ComponentPtr &component, ComponentMap &componentMap, VariableMap &variableMap)
{
    for (size_t i = 0; i < component->variableCount(); ++i) {
        VariablePtr variable = component->variable(i);
        for (size_t j = 0; j < variable->equivalentVariableCount(); ++j) {
            VariablePtr equivalentVariable = variable->equivalentVariable(j);
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
                    ComponentPtr component1 = std::dynamic_pointer_cast<Component>(variable->parent());
                    ComponentPtr component2 = std::dynamic_pointer_cast<Component>(equivalentVariable->parent());
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

void buildMaps(const ComponentEntityPtr &componentEntity, ComponentMap &componentMap, VariableMap &variableMap)
{
    for (size_t i = 0; i < componentEntity->componentCount(); ++i) {
        ComponentPtr component = componentEntity->component(i);
        buildMapsForComponentsVariables(component, componentMap, variableMap);
        buildMaps(component, componentMap, variableMap);
    }
}

std::string Printer::PrinterImpl::printUnits(const UnitsPtr &units) const
{
    std::string repr;
    if (units->isImport()) {
        repr += "<import xmlns:xlink=\"http://www.w3.org/1999/xlink\" xlink:href=\"" + units->importSource()->url() + "\"";
        if (!units->importSource()->id().empty()) {
            repr += " id=\"" + units->importSource()->id() + "\"";
        }
        repr += "><units units_ref=\"" + units->importReference() + "\" name=\"" + units->name() + "\"";
        if (!units->id().empty()) {
            repr += " id=\"" + units->id() + "\"";
        }
        repr += "/></import>";
    } else {
        bool endTag = false;
        repr += "<units";
        std::string unitsName = units->name();
        if (!unitsName.empty()) {
            repr += " name=\"" + unitsName + "\"";
        }
        if (!units->id().empty()) {
            repr += " id=\"" + units->id() + "\"";
        }
        if (units->unitCount() > 0) {
            endTag = true;
            repr += ">";
            for (size_t i = 0; i < units->unitCount(); ++i) {
                std::string reference;
                std::string prefix;
                std::string id;
                double exponent;
                double multiplier;
                units->unitAttributes(i, reference, prefix, exponent, multiplier, id);
                repr += "<unit";
                if (exponent != 1.0) {
                    repr += " exponent=\"" + convertToString(exponent) + "\"";
                }
                if (multiplier != 1.0) {
                    repr += " multiplier=\"" + convertToString(multiplier) + "\"";
                }
                if (!prefix.empty()) {
                    repr += " prefix=\"" + prefix + "\"";
                }
                repr += " units=\"" + reference + "\"";
                if (!id.empty()) {
                    repr += " id=\"" + id + "\"";
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

    return repr;
}

std::string Printer::PrinterImpl::printComponent(const ComponentPtr &component) const
{
    std::string repr;
    if (component->isImport()) {
        return repr;
    }
    repr += "<component";
    std::string componentName = component->name();
    if (!componentName.empty()) {
        repr += " name=\"" + componentName + "\"";
    }
    if (!component->id().empty()) {
        repr += " id=\"" + component->id() + "\"";
    }
    size_t variableCount = component->variableCount();
    size_t resetCount = component->resetCount();
    bool hasChildren = false;
    if (variableCount > 0 || resetCount > 0 || !component->math().empty()) {
        hasChildren = true;
    }
    if (hasChildren) {
        repr += ">";
        for (size_t i = 0; i < variableCount; ++i) {
            repr += printVariable(component->variable(i));
        }
        for (size_t i = 0; i < resetCount; ++i) {
            repr += printReset(component->reset(i));
        }
        if (!component->math().empty()) {
            repr += printMath(component->math());
        }
        repr += "</component>";
    } else {
        repr += "/>";
    }
    // Traverse through children of this component and add them to the representation.
    for (size_t i = 0; i < component->componentCount(); ++i) {
        repr += printComponent(component->component(i));
    }

    return repr;
}

std::string Printer::PrinterImpl::printEncapsulation(const ComponentPtr &component) const
{
    std::string componentName = component->name();
    std::string repr = "<component_ref";
    if (!componentName.empty()) {
        repr += " component=\"" + componentName + "\"";
    }
    if (!component->encapsulationId().empty()) {
        repr += " id=\"" + component->encapsulationId() + "\"";
    }
    size_t componentCount = component->componentCount();
    if (componentCount > 0) {
        repr += ">";
    } else {
        repr += "/>";
    }
    for (size_t i = 0; i < componentCount; ++i) {
        repr += printEncapsulation(component->component(i));
    }
    if (componentCount > 0) {
        repr += "</component_ref>";
    }
    return repr;
}

std::string Printer::PrinterImpl::printVariable(const VariablePtr &variable) const
{
    std::string repr;
    repr += "<variable";
    std::string name = variable->name();
    std::string id = variable->id();
    std::string units = variable->units() != nullptr ? variable->units()->name() : "";
    std::string intial_value = variable->initialValue();
    std::string interface_type = variable->interfaceType();
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

    repr += "/>";
    return repr;
}

std::string Printer::PrinterImpl::printResetChild(const std::string &childLabel, const std::string &childId, const std::string &math) const
{
    std::string repr;

    if (!childId.empty() || !math.empty()) {
        repr += "<" + childLabel;
        if (!childId.empty()) {
            repr += " id=\"" + childId + "\"";
        }
        if (math.empty()) {
            repr += "/>";
        } else {
            repr += ">" + printMath(math) + "</" + childLabel + ">";
        }
    }

    return repr;
}

std::string Printer::PrinterImpl::printReset(const ResetPtr &reset) const
{
    std::string repr = "<reset";
    std::string rid = reset->id();
    std::string rvid = reset->resetValueId();
    VariablePtr variable = reset->variable();
    VariablePtr testVariable = reset->testVariable();
    bool hasChild = false;

    if (variable) {
        repr += " variable=\"" + variable->name() + "\"";
    }
    if (testVariable) {
        repr += " test_variable=\"" + testVariable->name() + "\"";
    }
    if (reset->isOrderSet()) {
        repr += " order=\"" + convertToString(reset->order()) + "\"";
    }
    if (!rid.empty()) {
        repr += " id=\"" + rid + "\"";
    }

    std::string testValue = printResetChild("test_value", reset->testValueId(), reset->testValue());
    if (!testValue.empty()) {
        repr += ">" + testValue;
        hasChild = true;
    }
    std::string resetValue = printResetChild("reset_value", reset->resetValueId(), reset->resetValue());
    if (!resetValue.empty()) {
        if (!hasChild) {
            repr += ">";
        }
        repr += resetValue;
        hasChild = true;
    }
    if (hasChild) {
        repr += "</reset>";
    } else {
        repr += "/>";
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

PrinterPtr Printer::create() noexcept
{
    return std::shared_ptr<Printer> {new Printer {}};
}

std::string Printer::printModel(const ModelPtr &model) const
{
    if (model == nullptr) {
        return "";
    }

    // ImportMap
    using ImportPair = std::pair<std::string, ComponentPtr>;
    using ImportMap = std::map<ImportSourcePtr, std::vector<ImportPair>>;
    using ImportOrder = std::vector<ImportSourcePtr>;
    ImportMap importMap;
    ImportOrder importOrder;
    VariableMap variableMap;
    ComponentMap componentMap;

    // Gather all imports.
    std::list<ComponentPtr> componentStack;
    for (size_t i = 0; i < model->componentCount(); ++i) {
        ComponentPtr comp = model->component(i);
        while (comp) {
            if (comp->isImport()) {
                ImportPair pair = std::make_pair(comp->importReference(), comp);
                ImportSourcePtr importSource = comp->importSource();
                if (importMap.count(importSource) == 0) {
                    importMap[importSource] = std::vector<ImportPair>();
                    // We track the order to make the testing easier. The alternative
                    // is to implement a weak ordering method on the ImportSource class.
                    importOrder.push_back(importSource);
                }
                importMap[importSource].push_back(pair);
            } else {
                for (size_t j = 0; j < comp->componentCount(); ++j) {
                    auto childComponent = comp->component(j);
                    componentStack.push_back(childComponent);
                }
            }

            if (componentStack.empty()) {
                comp = nullptr;
            } else {
                comp = componentStack.front();
                componentStack.pop_front();
            }
        }
    }

    std::string repr;
    repr += "<?xml version=\"1.0\" encoding=\"UTF-8\"?><model xmlns=\"http://www.cellml.org/cellml/2.0#\"";
    if (!model->name().empty()) {
        repr += " name=\"" + model->name() + "\"";
    }
    if (!model->id().empty()) {
        repr += " id=\"" + model->id() + "\"";
    }
    bool endTag = false;
    if (!importMap.empty() || (model->componentCount() > 0) || (model->unitsCount() > 0)) {
        endTag = true;
        repr += ">";
    }

    for (const auto &importSource : importOrder) {
        repr += "<import xmlns:xlink=\"http://www.w3.org/1999/xlink\" xlink:href=\"" + importSource->url() + "\"";
        if (!importSource->id().empty()) {
            repr += " id=\"" + importSource->id() + "\"";
        }
        repr += ">";
        const auto &importVector = importMap[importSource];
        for (const auto &entry : importVector) {
            const auto &reference = entry.first;
            const auto &localComponent = entry.second;
            repr += "<component component_ref=\"" + reference + "\" name=\"" + localComponent->name() + "\"";
            if (!localComponent->id().empty()) {
                repr += " id=\"" + localComponent->id() + "\"";
            }
            repr += "/>";
        }
        repr += "</import>";
    }

    for (size_t i = 0; i < model->unitsCount(); ++i) {
        repr += mPimpl->printUnits(model->units(i));
    }

    std::string componentEncapsulation;
    // Serialise components of the model, imported components have already been dealt with at this point.
    for (size_t i = 0; i < model->componentCount(); ++i) {
        ComponentPtr component = model->component(i);
        repr += mPimpl->printComponent(component);
        if (component->componentCount() > 0) {
            componentEncapsulation += mPimpl->printEncapsulation(component);
        }
    }

    // Build unique variable equivalence pairs (ComponentMap, VariableMap) for connections.
    buildMaps(model, componentMap, variableMap);
    // Serialise connections of the model.
    repr += printConnections(componentMap, variableMap);

    if (!componentEncapsulation.empty()) {
        repr += "<encapsulation";
        if (!model->encapsulationId().empty()) {
            repr += " id=\"" + model->encapsulationId() + "\">";
        } else {
            repr += ">";
        }
        repr += componentEncapsulation + "</encapsulation>";
    }
    if (endTag) {
        repr += "</model>";
    } else {
        repr += "/>";
    }

    // Generate a pretty-print version of the model using libxml2.

    XmlDocPtr xmlDoc = std::make_shared<XmlDoc>();

    xmlDoc->parse(repr);

    return xmlDoc->prettyPrint();
}

} // namespace libcellml

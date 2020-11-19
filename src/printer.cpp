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
#include <regex>
#include <sstream>
#include <stack>
#include <utility>
#include <vector>

#include "libcellml/component.h"
#include "libcellml/importsource.h"
#include "libcellml/model.h"
#include "libcellml/reset.h"
#include "libcellml/units.h"
#include "libcellml/variable.h"

#include "internaltypes.h"
#include "utilities.h"
#include "xmldoc.h"

namespace libcellml {

/**
 * @brief The Printer::PrinterImpl struct.
 *
 * The private implementation for the Printer class.
 */
struct Printer::PrinterImpl
{
    std::string printImports(const ModelPtr &model, IdList &idList, bool autoIds);
    std::string printUnits(const UnitsPtr &units, IdList &idList, bool autoIds);
    std::string printComponent(const ComponentPtr &component, IdList &idList, bool autoIds);
    std::string printEncapsulation(const ComponentPtr &component, IdList &idList, bool autoIds);
    std::string printVariable(const VariablePtr &variable, IdList &idList, bool autoIds);
    std::string printReset(const ResetPtr &reset, IdList &idList, bool autoIds);
    std::string printResetChild(const std::string &childLabel, const std::string &childId, const std::string &math, IdList &idList, bool autoIds);
};

std::string printMapVariables(const VariablePairPtr &variablePair, IdList &idList, bool autoIds)
{
    std::string mapVariables = "<map_variables variable_1=\"" + variablePair->variable1()->name() + "\""
                               + " variable_2=\"" + variablePair->variable2()->name() + "\"";
    std::string mappingId = Variable::equivalenceMappingId(variablePair->variable1(), variablePair->variable2());
    if (!mappingId.empty()) {
        mapVariables += " id=\"" + mappingId + "\"";
    } else if (autoIds) {
        mapVariables += " id=\"" + makeUniqueId(idList) + "\"";
    }
    mapVariables += "/>";
    return mapVariables;
}

std::string printConnections(const ComponentMap &componentMap, const VariableMap &variableMap, IdList &idList, bool autoIds)
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
        VariablePairPtr variablePair = variableMap.at(componentMapIndex1);
        std::string connectionId = Variable::equivalenceConnectionId(variablePair->variable1(), variablePair->variable2());
        mappingVariables += printMapVariables(variablePair, idList, autoIds);
        // Check for subsequent variable equivalence pairs with the same parent components.
        size_t componentMapIndex2 = componentMapIndex1 + 1;
        for (auto iterPair2 = iterPair + 1; iterPair2 < componentMap.end(); ++iterPair2) {
            ComponentPtr nextComponent1 = iterPair2->first;
            ComponentPtr nextComponent2 = iterPair2->second;
            VariablePairPtr variablePair2 = variableMap.at(componentMapIndex2);
            if ((currentComponent1 == nextComponent1) && (currentComponent2 == nextComponent2)) {
                mappingVariables += printMapVariables(variablePair2, idList, autoIds);
                connectionId = Variable::equivalenceConnectionId(variablePair2->variable1(), variablePair2->variable2());
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
        } else if (autoIds) {
            connections += " id=\"" + makeUniqueId(idList) + "\"";
        }
        connections += ">" + mappingVariables + "</connection>";
        serialisedComponentMap.push_back(currentComponentPair);
        ++componentMapIndex1;
    }

    return connections;
}

std::string printMath(const std::string &math)
{
    static const std::regex before(">[\\s\n\t]*");
    static const std::regex after("[\\s\n\t]*<");
    auto temp = std::regex_replace(math, before, ">");
    return std::regex_replace(temp, after, "<");
}

void buildMapsForComponentsVariables(const ComponentPtr &component, ComponentMap &componentMap, VariableMap &variableMap)
{
    for (size_t i = 0; i < component->variableCount(); ++i) {
        VariablePtr variable = component->variable(i);
        for (size_t j = 0; j < variable->equivalentVariableCount(); ++j) {
            VariablePtr equivalentVariable = variable->equivalentVariable(j);
            if (equivalentVariable->hasEquivalentVariable(variable)) {
                VariablePairPtr variablePair = VariablePair::create(variable, equivalentVariable);
                auto pairFound = std::find_if(variableMap.begin(), variableMap.end(),
                                              [variable, equivalentVariable](const VariablePairPtr &in) {
                                                  return ((in->variable1() == equivalentVariable) && (in->variable2() == variable))
                                                         || ((in->variable1() == variable) && (in->variable2() == equivalentVariable));
                                              });
                if (pairFound == variableMap.end()) {
                    // Get parent components.
                    ComponentPtr component1 = owningComponent(variable);
                    ComponentPtr component2 = owningComponent(equivalentVariable);
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

std::string Printer::PrinterImpl::printUnits(const UnitsPtr &units, IdList &idList, bool autoIds)
{
    std::string repr;
    if (!units->isImport() && !isStandardUnit(units)) {
        bool endTag = false;
        repr += "<units";
        std::string unitsName = units->name();
        if (!unitsName.empty()) {
            repr += " name=\"" + unitsName + "\"";
        }
        if (!units->id().empty()) {
            repr += " id=\"" + units->id() + "\"";
        } else if (autoIds) {
            repr += " id=\"" + makeUniqueId(idList) + "\"";
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
                } else if (autoIds) {
                    repr += " id=\"" + makeUniqueId(idList) + "\"";
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

std::string Printer::PrinterImpl::printComponent(const ComponentPtr &component, IdList &idList, bool autoIds)
{
    std::string repr;
    if (!component->isImport()) {
        repr += "<component";
        std::string componentName = component->name();
        if (!componentName.empty()) {
            repr += " name=\"" + componentName + "\"";
        }
        if (!component->id().empty()) {
            repr += " id=\"" + component->id() + "\"";
        } else if (autoIds) {
            repr += " id=\"" + makeUniqueId(idList) + "\"";
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
                repr += printVariable(component->variable(i), idList, autoIds);
            }
            for (size_t i = 0; i < resetCount; ++i) {
                repr += printReset(component->reset(i), idList, autoIds);
            }
            if (!component->math().empty()) {
                repr += printMath(component->math());
            }

            repr += "</component>";
        } else {
            repr += "/>";
        }
    }

    // Traverse through children of this component and add them to the representation.
    for (size_t i = 0; i < component->componentCount(); ++i) {
        repr += printComponent(component->component(i), idList, autoIds);
    }

    return repr;
}

std::string Printer::PrinterImpl::printEncapsulation(const ComponentPtr &component, IdList &idList, bool autoIds)
{
    std::string componentName = component->name();
    std::string repr = "<component_ref";
    if (!componentName.empty()) {
        repr += " component=\"" + componentName + "\"";
    }
    if (!component->encapsulationId().empty()) {
        repr += " id=\"" + component->encapsulationId() + "\"";
    } else if (autoIds) {
        repr += " id=\"" + makeUniqueId(idList) + "\"";
    }
    size_t componentCount = component->componentCount();
    if (componentCount > 0) {
        repr += ">";
    } else {
        repr += "/>";
    }
    for (size_t i = 0; i < componentCount; ++i) {
        repr += printEncapsulation(component->component(i), idList, autoIds);
    }
    if (componentCount > 0) {
        repr += "</component_ref>";
    }
    return repr;
}

std::string Printer::PrinterImpl::printVariable(const VariablePtr &variable, IdList &idList, bool autoIds)
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
    } else if (autoIds) {
        repr += " id=\"" + makeUniqueId(idList) + "\"";
    }

    repr += "/>";
    return repr;
}

std::string Printer::PrinterImpl::printResetChild(const std::string &childLabel, const std::string &childId,
                                                  const std::string &math, IdList &idList, bool autoIds)
{
    std::string repr;

    if (!childId.empty() || !math.empty()) {
        repr += "<" + childLabel;
        if (!childId.empty()) {
            repr += " id=\"" + childId + "\"";
        } else if (autoIds) {
            repr += " id=\"" + makeUniqueId(idList) + "\"";
        }
        if (math.empty()) {
            repr += "/>";
        } else {
            repr += ">" + printMath(math) + "</" + childLabel + ">";
        }
    }

    return repr;
}

std::string Printer::PrinterImpl::printReset(const ResetPtr &reset, IdList &idList, bool autoIds)
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
    } else if (autoIds) {
        repr += " id=\"" + makeUniqueId(idList) + "\"";
    }

    std::string testValue = printResetChild("test_value", reset->testValueId(), reset->testValue(), idList, autoIds);
    if (!testValue.empty()) {
        repr += ">" + testValue;
        hasChild = true;
    }
    std::string resetValue = printResetChild("reset_value", reset->resetValueId(), reset->resetValue(), idList, autoIds);
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

std::string Printer::PrinterImpl::printImports(const ModelPtr &model, IdList &idList, bool autoIds)
{
    std::string repr;

    for (size_t i = 0; i < model->importSourceCount(); ++i) {
        auto importSource = model->importSource(i);

        repr += "<import xmlns:xlink=\"http://www.w3.org/1999/xlink\" xlink:href=\"" + importSource->url() + "\"";
        if (!importSource->id().empty()) {
            repr += " id=\"" + importSource->id() + "\"";
        } else if (autoIds) {
            repr += " id=\"" + makeUniqueId(idList) + "\"";
        }
        repr += ">";

        for (size_t c = 0; c < importSource->componentCount(); ++c) {
            auto component = importSource->component(c);
            repr += "<component component_ref=\"" + component->importReference() + "\" name=\"" + component->name() + "\"";
            if (!component->id().empty()) {
                repr += " id=\"" + component->id() + "\"";
            } else if (autoIds) {
                repr += " id=\"" + makeUniqueId(idList) + "\"";
            }
            repr += "/>";
        }

        for (size_t u = 0; u < importSource->unitsCount(); ++u) {
            auto units = importSource->units(u);
            repr += "<units units_ref=\"" + units->importReference() + "\" name=\"" + units->name() + "\"";
            if (!units->id().empty()) {
                repr += " id=\"" + units->id() + "\"";
            } else if (autoIds) {
                repr += " id=\"" + makeUniqueId(idList) + "\"";
            }
            repr += "/>";
        }
        repr += "</import>";
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

std::string Printer::printModel(const ModelPtr &model, bool autoIds) const
{
    if (model == nullptr) {
        return "";
    }
    // Automatic ids.
    IdList idList;
    if (autoIds) {
        idList = listIds(model);
    }

    std::string repr;
    repr += "<?xml version=\"1.0\" encoding=\"UTF-8\"?><model xmlns=\"http://www.cellml.org/cellml/2.0#\"";
    if (!model->name().empty()) {
        repr += " name=\"" + model->name() + "\"";
    }
    if (!model->id().empty()) {
        repr += " id=\"" + model->id() + "\"";
    } else if (autoIds) {
        repr += " id=\"" + makeUniqueId(idList) + "\"";
    }

    bool endTag = false;
    if ((model->componentCount() > 0) || (model->unitsCount() > 0)) {
        endTag = true;
        repr += ">";
    }

    if (model->hasImports()) {
        repr += mPimpl->printImports(model, idList, autoIds);
    }

    for (size_t i = 0; i < model->unitsCount(); ++i) {
        repr += mPimpl->printUnits(model->units(i), idList, autoIds);
    }

    std::string componentEncapsulation;
    // Serialise components of the model, imported components have already been dealt with at this point,
    //  ... but their locally-defined children have not.
    for (size_t i = 0; i < model->componentCount(); ++i) {
        ComponentPtr component = model->component(i);
        repr += mPimpl->printComponent(component, idList, autoIds);
        if (component->componentCount() > 0) {
            componentEncapsulation += mPimpl->printEncapsulation(component, idList, autoIds);
        }
    }

    VariableMap variableMap;
    ComponentMap componentMap;
    // Build unique variable equivalence pairs (ComponentMap, VariableMap) for connections.
    buildMaps(model, componentMap, variableMap);
    // Serialise connections of the model.
    repr += printConnections(componentMap, variableMap, idList, autoIds);

    if (!componentEncapsulation.empty()) {
        repr += "<encapsulation";
        if (!model->encapsulationId().empty()) {
            repr += " id=\"" + model->encapsulationId() + "\">";
        } else if (autoIds) {
            repr += " id=\"" + makeUniqueId(idList) + "\">";
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
    // The xmlKeepBlanksDefault is turned off so that the pretty print can adjust
    // the spacing in the user-supplied MathML.
    // See http://www.xmlsoft.org/html/libxml-tree.html#xmlDocDumpFormatMemoryEnc
    // for details.
    XmlDocPtr xmlDoc = std::make_shared<XmlDoc>();
    xmlKeepBlanksDefault(0);
    xmlDoc->parse(repr);
    return xmlDoc->prettyPrint();
}

} // namespace libcellml

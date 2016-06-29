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

#include <string>
#include <vector>

#include "libcellml/component.h"
#include "libcellml/import.h"
#include "libcellml/loggererrors.h"
#include "libcellml/model.h"
#include "libcellml/variable.h"
#include "xmldoc.h"

namespace libcellml {

/**
 * @brief The Parser::ParserImpl struct.
 *
 * The private implementation for the Parser class.
 */
struct Parser::ParserImpl
{
public:
    Format mFormat;
    Parser *mParser;

    /**
     * @brief Update the @p model with attributes parsed from a @c std::string.
     *
     * Update the @p model with attributes and entities parsed from
     * the @c std::string @p input. Any entities or attributes in @p model with names
     * matching those in @p input will be overwritten.
     *
     * @param model The @c ModelPtr to update.
     * @param input The string to parse and update the @p model with.
     */
    void loadModel(const ModelPtr &model, const std::string &input);

private:
    /**
     * @brief Update the @p component with attributes parsed from @p node.
     *
     * Update the @p component with attributes and entities parsed from
     * the XML @p node. Any entities or attributes in @p component with names
     * matching those in @p node will be overwritten.
     *
     * @param component The @c ComponentPtr to update.
     * @param node The @c XmlNodePtr to parse and update the @p component with.
     */
    void loadComponent(const ComponentPtr &component, const XmlNodePtr &node);

    /**
     * @brief Update the @p model with a connection parsed from @p node.
     *
     * Update the @p model with connection information parsed from
     * the XML @p node. Connection information from @p node will be added
     * to any variable equivalence relationships already existing in @p model.
     *
     * @param model The @c ModelPtr to update.
     * @param node The @c XmlNodePtr to parse and update the model with.
     */
    void loadConnection(const ModelPtr &model, const XmlNodePtr &node);

    /**
     * @brief Update the @p model with an encapsulation parsed from @p node.
     *
     * Update the @p model with encapsulation information parsed from
     * the XML @p node. Encapsulation relationships from @p node will be added
     * to any encapsulations relationships already in @p model.
     *
     * @param model The @c ModelPtr to update.
     * @param node The @c XmlNodePtr to parse and update the model with.
     */
    void loadEncapsulation(const ModelPtr &model, const XmlNodePtr &node);

    /**
     * @brief Update the @p import with attributes parsed from @p node and add any imported
     * components or units it to the @p model.
     *
     * Update the @p import with attributes parsed from @p node and add any imported
     * components or units to the @p model. If any attributes exist in @p import
     * with names matching those in @p node, they will be overwritten. Likewise,
     * any imported components or units of the same name already in @p model will
     * be overwritten by those parsed from @p node.
     *
     * @param import The @c ImportPtr to update.
     * @param model The @c ModelPtr to add imported components/units to.
     * @param node The @c XmlNodePtr to parse and update the @p import with.
     */
    void loadImport(const ImportPtr &import, const ModelPtr &model, const XmlNodePtr &node);

    /**
     * @brief Update the @p units with attributes parsed from @p node.
     *
     * Update the @p units by parsing the XML @p node.
     * Existing attributes in @p units with names
     * matching those in @p node will be overwritten.
     *
     * @param units The @c UnitsPtr to update.
     * @param node The @c XmlNodePtr to parse and update the @p units with.
     */
    void loadUnits(const UnitsPtr &units, const XmlNodePtr &node);

    /**
     * @brief Update the @p units with a unit parsed from @p node.
     *
     * Update the @p units with a unit parsed from the XML @p node.
     * If a unit with the same name exists in @p units, it will be
     * overwritten by the unit from @p node.
     *
     * @param units The @c UnitsPtr to update.
     * @param node The unit @c XmlNodePtr to parse and update the @p units with.
     */
    void loadUnit(const UnitsPtr &units, const XmlNodePtr &node);

    /**
     * @brief Update the @p variable with attributes parsed from @p node.
     *
     * Update the @p variable with attributes parsed from
     * the XML @p node. Existing attributes in @p variable with names
     * matching those in @p node will be overwritten.
     *
     * @param variable The @c VariablePtr to update.
     * @param node The @c XmlNodePtr to parse and update the @p variable with.
     */
    void loadVariable(const VariablePtr &variable, const XmlNodePtr &node);

    /**
     * @brief Try to convert and return the unit @p attribute value to a @c double.
     *
     * Try to convert the unit @p attribute value to a @c double. Return the new
     * @c double value if possible. Otherwise, flag an error and return the @p defaultValue.
     *
     * @param defaultValue The default value for the unit attribute.
     * @param attribute The @c XmlAttributePtr with the value to convert.
     * @param node The @c XmlNodePtr the @p attribute is within.
     * @param units The units the unit @p attribute is relevant to.
     *
     * @return The unit @p attribute value if it can be converted to a @c double;
     * the @p defaultValue otherwise.
     *
     */
    double convertUnitAttributeValueToDouble(double &defaultValue, const XmlAttributePtr &attribute,
                                             const XmlNodePtr &node, const UnitsPtr &units);
};

Parser::Parser(Format format)
    : mPimpl(new ParserImpl())
{
    mPimpl->mFormat = format;
    mPimpl->mParser = this;
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
    mPimpl->mParser = rhs.mPimpl->mParser;
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
        mPimpl->loadModel(model, input);
    } else {
        EntityErrorPtr err = std::make_shared<EntityError>();
        err->setDescription("Invalid model format type (should be XML).");
        addError(err);
    }
}

void Parser::ParserImpl::loadModel(const ModelPtr &model, const std::string &input)
{
    XmlDocPtr doc = std::make_shared<XmlDoc>();
    doc->parse(input);
    // Copy any XML parsing errors into the common error handler.
    if (doc->xmlErrorCount() > 0) {
        for (size_t i = 0; i < doc->xmlErrorCount(); ++i) {
            EntityErrorPtr err = std::make_shared<EntityError>();
            err->setDescription(doc->getXmlError(i));
            mParser->addError(err);
        }
    }
    const XmlNodePtr node = doc->getRootNode();
    if (!node->isType("model")) {
        ModelErrorPtr err = std::make_shared<ModelError>();
        err->setDescription("Invalid XML element type (not a model).");
        err->setModel(model);
        mParser->addError(err);
    }
    // Get model attributes.
    XmlAttributePtr attribute = node->getFirstAttribute();
    while (attribute) {
        if (attribute->isType("name")) {
            model->setName(attribute->getValue());
        } else {
            ModelErrorPtr err = std::make_shared<ModelError>();
            err->setDescription("Invalid model attribute: '" + attribute->getType() +
                                "' with value: '" + attribute->getValue() + "'.");
            err->setModel(model);
            mParser->addError(err);
        }
        attribute = attribute->getNext();
    }
    // Get model children (CellML entities).
    XmlNodePtr childNode = node->getFirstChild();
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
            // An encapsulation should not have attributes.
            if (childNode->getFirstAttribute()) {
                XmlAttributePtr attribute = childNode->getFirstAttribute();
                while (attribute) {
                    ModelErrorPtr err = std::make_shared<ModelError>();
                    err->setDescription("Invalid attribute '" + attribute->getType() +
                                        "' found in encapsulation.");
                    err->setModel(model);
                    mParser->addError(err);
                    attribute = attribute->getNext();
                }
            }
            // Load encapsulated component_refs.
            XmlNodePtr componentRefNode = childNode->getFirstChild();
            if (componentRefNode) {
                while (componentRefNode) {
                    loadEncapsulation(model, componentRefNode);
                    componentRefNode = componentRefNode->getNext();
                }
            } else {
                ModelErrorPtr err = std::make_shared<ModelError>();
                err->setDescription("Encapsulation does not contain a component_ref.");
                err->setModel(model);
                mParser->addError(err);
            }
        } else if (childNode->isType("connection")) {
            loadConnection(model, childNode);
        } else {
            ModelErrorPtr err = std::make_shared<ModelError>();
            err->setDescription("Invalid XML element type '" + childNode->getType() +
                                "' in model '" + model->getName() + "'.");
            err->setModel(model);
            mParser->addError(err);
        }
        childNode = childNode->getNext();
    }
}

void Parser::ParserImpl::loadComponent(const ComponentPtr &component, const XmlNodePtr &node)
{
    XmlAttributePtr attribute = node->getFirstAttribute();
    while (attribute) {
        if (attribute->isType("name")) {
            component->setName(attribute->getValue());
        } else {
            ComponentErrorPtr err = std::make_shared<ComponentError>();
            err->setDescription("Invalid attribute '" + attribute->getType() +
                                "' found in component '" + node->getAttribute("name") + "'.");
            err->setComponent(component);
            mParser->addError(err);
        }
        attribute = attribute->getNext();
    }
    XmlNodePtr childNode = node->getFirstChild();
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
            ComponentErrorPtr err = std::make_shared<ComponentError>();
            err->setDescription("Invalid child element '" + childNode->getType() +
                                "' found in component '" + component->getName() + "'.");
            err->setComponent(component);
            mParser->addError(err);
        }
        childNode = childNode->getNext();
    }
}

void Parser::ParserImpl::loadUnits(const UnitsPtr &units, const XmlNodePtr &node)
{
    XmlAttributePtr attribute = node->getFirstAttribute();
    while (attribute) {
        if (attribute->isType("name")) {
            units->setName(attribute->getValue());
        } else if (attribute->isType("base_unit")) {
            if (attribute->getValue() == "yes") {
                units->setBaseUnit(true);
            } else if (attribute->getValue() == "no") {
                units->setBaseUnit(false);
            } else {
                UnitsErrorPtr err = std::make_shared<UnitsError>();
                err->setDescription("Invalid base_unit attribute in units '" + units->getName() +
                                    "'. Should be either 'yes' or 'no', and not '" + attribute->getValue() + "'.");
                err->setUnits(units);
                mParser->addError(err);
            }
        } else {
            UnitsErrorPtr err = std::make_shared<UnitsError>();
            err->setDescription("Invalid attribute '" + attribute->getType() +
                                "' found in units '"+ units->getName() + "'.");
            err->setUnits(units);
            mParser->addError(err);
        }
        attribute = attribute->getNext();
    }
    XmlNodePtr childNode = node->getFirstChild();
    while (childNode) {
        if (childNode->isType("unit")) {
            loadUnit(units, childNode);
        } else {
            UnitsErrorPtr err = std::make_shared<UnitsError>();
            err->setDescription("Invalid child element '" + childNode->getType() +
                                "' found in units '" + units->getName() + "'.");
            err->setUnits(units);
            mParser->addError(err);
        }
        childNode = childNode->getNext();
    }
}

void Parser::ParserImpl::loadUnit(const UnitsPtr &units, const XmlNodePtr &node)
{
    std::string name = "";
    std::string prefix = "";
    double exponent = 1.0;
    double multiplier = 1.0;
    double offset = 0.0;
    // A unit should not have any children.
    if (node->getFirstChild()) {
        XmlNodePtr childNode = node->getFirstChild();
        while (childNode) {
            UnitsErrorPtr err = std::make_shared<UnitsError>();
            err->setDescription("Invalid child element '" + childNode->getType() +
                                "' in unit '" + node->getAttribute("units") +
                                "' from units '" + units->getName() + "'.");
            err->setUnits(units);
            mParser->addError(err);
            childNode = childNode->getNext();
        }
    }
    // Parse the unit attributes.
    XmlAttributePtr attribute = node->getFirstAttribute();
    while (attribute) {
        if (attribute->isType("units")) {
            name = attribute->getValue();
        } else if (attribute->isType("prefix")) {
            prefix = attribute->getValue();
        } else if (attribute->isType("exponent")) {
            exponent = convertUnitAttributeValueToDouble(exponent, attribute, node, units);
        } else if (attribute->isType("multiplier")) {
            multiplier = convertUnitAttributeValueToDouble(multiplier, attribute, node, units);
        } else if (attribute->isType("offset")) {
            offset = convertUnitAttributeValueToDouble(offset, attribute, node, units);
        } else {
            UnitsErrorPtr err = std::make_shared<UnitsError>();
            err->setDescription("Invalid attribute '" + attribute->getType() +
                                "' found in unit '" + node->getAttribute("units") +
                                "' from units '" + units->getName() + "'.");
            err->setUnits(units);
            mParser->addError(err);
        }
        attribute = attribute->getNext();
    }
    // Add this unit to the parent units.
    units->addUnit(name, prefix, exponent, multiplier, offset);
}

double Parser::ParserImpl::convertUnitAttributeValueToDouble(double &defaultValue, const XmlAttributePtr &attribute,
                                                             const XmlNodePtr &node, const UnitsPtr &units)
{
    double value = defaultValue;
    // Try to convert the unit attribute value to double.
    try
    {
        value = std::stod(attribute->getValue());
    // On failure, flag error and use the default value.
    } catch (std::exception) {
        UnitsErrorPtr err = std::make_shared<UnitsError>();
        err->setDescription("Value '" + attribute->getValue() +
                            "' of attribute '" + attribute->getType() +
                            "' in unit '" + node->getAttribute("units") +
                            "' from units '" + units->getName() +
                            "' is not convertible to decimal number.");
        err->setUnits(units);
        mParser->addError(err);
    }
    return value;
}

void Parser::ParserImpl::loadVariable(const VariablePtr &variable, const XmlNodePtr &node)
{
    XmlAttributePtr attribute = node->getFirstAttribute();
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
            VariableErrorPtr err = std::make_shared<VariableError>();
            err->setDescription("Invalid attribute '" + attribute->getType() +
                                "' found in variable '" + node->getAttribute("name") + "'.");
            err->setVariable(variable);
            mParser->addError(err);
        }
        attribute = attribute->getNext();
    }
}

void Parser::ParserImpl::loadConnection(const ModelPtr &model, const XmlNodePtr &node)
{
    // Define types for variable and component pairs.
    typedef std::pair <std::string, std::string> NamePair;
    typedef std::vector<NamePair> NamePairMap;
    typedef NamePairMap::const_iterator NameMapIterator;

    // Check that the connection node has children.
    XmlNodePtr childNode = node->getFirstChild();
    if (!childNode) {
        ModelErrorPtr err = std::make_shared<ModelError>();
        err->setDescription("Connection in model '" + model->getName() +
                            "' does not contain any child elements.");
        err->setModel(model);
        mParser->addError(err);
        return;
    }

    // Initialise name pairs and flags.
    NamePair componentNamePair, variableNamePair;
    NamePairMap variableNameMap;
    bool mapComponentsFound = false;
    bool mapVariablesFound = false;
    bool component1Missing = false;
    bool component2Missing = false;
    bool variable1Missing = false;
    bool variable2Missing = false;
    // Iterate over connection child XML nodes.
    while (childNode) {
        // Connection map XML nodes should not have further children.
        if (childNode->getFirstChild()) {
            XmlNodePtr grandchildNode = childNode->getFirstChild();
            ModelErrorPtr err = std::make_shared<ModelError>();
            err->setDescription("Connection in model '" + model->getName() +
                                "' has an invalid child element '" + grandchildNode->getType() +
                                "' of element '" + childNode->getType() + "'.");
            err->setModel(model);
            mParser->addError(err);
        }

        // Check for a valid map_components and get the name pair.
        if (childNode->isType("map_components")) {
            std::string component1Name = "";
            std::string component2Name = "";
            XmlAttributePtr attribute = childNode->getFirstAttribute();
            while (attribute) {
                if (attribute->isType("component_1")) {
                    component1Name = attribute->getValue();
                } else if (attribute->isType("component_2")) {
                    component2Name = attribute->getValue();
                } else {
                    ModelErrorPtr err = std::make_shared<ModelError>();
                    err->setDescription("Connection in model '" + model->getName() +
                                        "' has an invalid map_components attribute '" + attribute->getType() + "'.");
                    err->setModel(model);
                    mParser->addError(err);
                }
                attribute = attribute->getNext();
            }
            // Check that we found both components.
            if (!component1Name.length()) {
                ModelErrorPtr err = std::make_shared<ModelError>();
                err->setDescription("Connection in model '" + model->getName() +
                                    "' does not have a valid component_1 in a map_components element.");
                err->setModel(model);
                mParser->addError(err);
                component1Missing = true;
            }
            if (!component2Name.length()) {
                ModelErrorPtr err = std::make_shared<ModelError>();
                err->setDescription("Connection in model '" + model->getName() +
                                    "' does not have a valid component_2 in a map_components element.");
                err->setModel(model);
                mParser->addError(err);
                component2Missing = true;
            }
            // We should only have one map_components per connection.
            if (mapComponentsFound) {
                ModelErrorPtr err = std::make_shared<ModelError>();
                err->setDescription("Connection in model '" + model->getName() +
                                    "' has more than one map_components element.");
                err->setModel(model);
                mParser->addError(err);
            }
            componentNamePair = std::make_pair(component1Name, component2Name);
            mapComponentsFound = true;

        // Check for a valid map_variables and add the name pair to the variableNameMap.
        } else if (childNode->isType("map_variables")) {
            std::string variable1Name = "";
            std::string variable2Name = "";
            XmlAttributePtr attribute = childNode->getFirstAttribute();
            while (attribute) {
                if (attribute->isType("variable_1")) {
                    variable1Name = attribute->getValue();
                } else if (attribute->isType("variable_2")) {
                    variable2Name = attribute->getValue();
                } else {
                    ModelErrorPtr err = std::make_shared<ModelError>();
                    err->setDescription("Connection in model '" + model->getName() +
                                        "' has an invalid map_variables attribute '" + attribute->getType() + "'.");
                    err->setModel(model);
                    mParser->addError(err);
                }
                attribute = attribute->getNext();
            }
            // Check that we found both variables.
            if (!variable1Name.length()) {
                ModelErrorPtr err = std::make_shared<ModelError>();
                err->setDescription("Connection in model '" + model->getName() +
                                    "' does not have a valid variable_1 in a map_variables element.");
                err->setModel(model);
                mParser->addError(err);
                variable1Missing = true;
            }
            if (!variable2Name.length()) {
                ModelErrorPtr err = std::make_shared<ModelError>();
                err->setDescription("Connection in model '" + model->getName() +
                                    "' does not have a valid variable_2 in a map_variables element.");
                err->setModel(model);
                mParser->addError(err);
                variable2Missing = true;
            }
            // We can have multiple map_variables per connection.
            variableNamePair = std::make_pair(variable1Name, variable2Name);
            variableNameMap.push_back(variableNamePair);
            mapVariablesFound = true;

        } else {
            ModelErrorPtr err = std::make_shared<ModelError>();
            err->setDescription("Connection in model '" + model->getName() +
                                "' has an invalid child element '" + childNode->getType() + "'.");
            err->setModel(model);
            mParser->addError(err);
        }
        childNode = childNode->getNext();
    }

    // If we have a map_components, check that the components exist in the model.
    ComponentPtr component1 = nullptr;
    ComponentPtr component2 = nullptr;
    if (mapComponentsFound) {
        // Now check the objects exist in the model.
        if (model->containsComponent(componentNamePair.first)) {
            component1 = model->getComponent(componentNamePair.first);
        } else {
            if (!component1Missing) {
                ModelErrorPtr err = std::make_shared<ModelError>();
                err->setDescription("Connection in model '" + model->getName() +
                                    "' specifies '" + componentNamePair.first +
                                    "' as component_1 but it does not exist in the model.");
                err->setModel(model);
                mParser->addError(err);
            }
        }
        if (model->containsComponent(componentNamePair.second)) {
            component2 = model->getComponent(componentNamePair.second);
        } else {
            if (!component2Missing) {
                ModelErrorPtr err = std::make_shared<ModelError>();
                err->setDescription("Connection in model '" + model->getName() +
                                    "' specifies '" + componentNamePair.second +
                                    "' as component_2 but it does not exist in the model.");
                err->setModel(model);
                mParser->addError(err);
            }
        }
    } else {
        ModelErrorPtr err = std::make_shared<ModelError>();
        err->setDescription("Connection in model '" + model->getName() +
                            "' does not have a map_components element.");
        err->setModel(model);
        mParser->addError(err);
    }

    // If we have a map_variables, check that the variables exist in the map_components.
    if (mapVariablesFound) {
        for (NameMapIterator iterPair = variableNameMap.begin(); iterPair < variableNameMap.end(); ++iterPair) {
            VariablePtr variable1 = nullptr;
            VariablePtr variable2 = nullptr;
            if (component1) {
                if (component1->hasVariable(iterPair->first)) {
                    variable1 = component1->getVariable(iterPair->first);
                } else if (component1->isImport()) {
                    // With an imported component we assume this variable exists in the imported component.
                    variable1 = std::make_shared<Variable>();
                    variable1->setName(iterPair->first);
                    component1->addVariable(variable1);
                } else {
                    if (!variable1Missing) {
                        VariableErrorPtr err = std::make_shared<VariableError>();
                        err->setDescription("Variable '" + iterPair->first +
                                            "' is specified as variable_1 in a connection but it does not exist in component_1 component '"
                                            + component1->getName() + "' of model '" + model->getName() + "'.");
                        err->setComponent(component1);
                        mParser->addError(err);
                    }
                }
            } else {
                ModelErrorPtr err = std::make_shared<ModelError>();
                err->setDescription("Connection in model '" + model->getName() +
                                    "' specifies '" + iterPair->first +
                                    "' as variable_1 but the corresponding component_1 is invalid.");
                err->setModel(model);
                mParser->addError(err);
            }
            if (component2) {
                if (component2->hasVariable(iterPair->second)) {
                    variable2 = component2->getVariable(iterPair->second);
                } else if (component2->isImport()) {
                    // With an imported component we assume this variable exists in the imported component.
                    variable2 = std::make_shared<Variable>();
                    variable2->setName(iterPair->second);
                    component2->addVariable(variable2);
                } else {
                    if (!variable2Missing) {
                        VariableErrorPtr err = std::make_shared<VariableError>();
                        err->setDescription("Variable '" + iterPair->second +
                                            "' is specified as variable_2 in a connection but it does not exist in component_2 component '"
                                            + component2->getName() + "' of model '" + model->getName() + "'.");
                        err->setComponent(component1);
                        mParser->addError(err);
                    }
                }
            } else {
                ModelErrorPtr err = std::make_shared<ModelError>();
                err->setDescription("Connection in model '" + model->getName() +
                                    "' specifies '" + iterPair->second +
                                    "' as variable_2 but the corresponding component_2 is invalid.");
                err->setModel(model);
                mParser->addError(err);
            }
            // Set the variable equivalence relationship for this variable pair.
            if ((variable1) && (variable2)) {
                Variable::addEquivalence(variable1, variable2);
            }
        }
    } else {
        ModelErrorPtr err = std::make_shared<ModelError>();
        err->setDescription("Connection in model '" + model->getName() +
                            "' does not have a map_variables element.");
        err->setModel(model);
        mParser->addError(err);
    }
}

void Parser::ParserImpl::loadEncapsulation(const ModelPtr &model, const XmlNodePtr &node)
{
    XmlNodePtr parentComponentNode = node;
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
                    err->setDescription("Model does not contain component '" + parentComponentName +
                                        "' but it has been specified in an encapsulation.");
                    err->setModel(model);
                    mParser->addError(err);
                    errorOccurred = true;
                }
                // Get child components
                XmlNodePtr childComponentNode = parentComponentNode->getFirstChild();
                if (!childComponentNode) {
                    ModelErrorPtr err = std::make_shared<ModelError>();
                    err->setDescription("Encapsulation contains no child components.");
                    err->setModel(model);
                    mParser->addError(err);
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
                                err->setDescription("Model does not contain component '" + childComponentName +
                                                    "' but it has been specified in an encapsulation.");
                                err->setModel(model);
                                mParser->addError(err);
                                errorOccurred = true;
                            }
                        } else {
                            ModelErrorPtr err = std::make_shared<ModelError>();
                            err->setDescription("Encapsulation component_ref does not contain a component.");
                            err->setModel(model);
                            mParser->addError(err);
                            errorOccurred = true;
                        }
                    } else {
                        ModelErrorPtr err = std::make_shared<ModelError>();
                        err->setDescription("Encapsulation does not contain a component_ref.");
                        err->setModel(model);
                        mParser->addError(err);
                        errorOccurred = true;
                    }
                    if (!errorOccurred) {
                        // Set parent/child relationship.
                        parentComponent->addComponent(childComponent);
                        // Load any further encapsulated children.
                        if (childComponentNode->getFirstChild()) {
                            loadEncapsulation(model, childComponentNode);
                        }
                        // A child component is added through its parent component rather than the model,
                        // so remove it if it exists.
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
                err->setModel(model);
                mParser->addError(err);
            }
        } else {
            ModelErrorPtr err = std::make_shared<ModelError>();
            err->setDescription("Encapsulation does not contain a component_ref.");
            err->setModel(model);
            mParser->addError(err);
        }
        // Get the next parent component at this level
        parentComponentNode = parentComponentNode->getNext();
    }
}

void Parser::ParserImpl::loadImport(const ImportPtr &import, const ModelPtr &model, const XmlNodePtr &node)
{
    XmlAttributePtr attribute = node->getFirstAttribute();
    while (attribute) {
        if (attribute->isType("href")) {
            import->setSource(attribute->getValue());
        } else if (attribute->isType("xlink")) {
            // Allow xlink attributes but do nothing for them.
        } else {
            ImportErrorPtr err = std::make_shared<ImportError>();
            err->setDescription("Invalid attribute '" + attribute->getType() +
                                "' found in import from '" + node->getAttribute("href") + "'.");
            err->setImport(import);
            mParser->addError(err);
        }
        attribute = attribute->getNext();
    }
    XmlNodePtr childNode = node->getFirstChild();
    while (childNode) {
        if (childNode->isType("component")) {
            ComponentPtr importedComponent = std::make_shared<Component>();
            bool errorOccurred = false;
            XmlAttributePtr attribute = childNode->getFirstAttribute();
            while (attribute) {
                if (attribute->isType("name")) {
                    importedComponent->setName(attribute->getValue());
                } else if (attribute->isType("component_ref")) {
                    importedComponent->setSourceComponent(import, attribute->getValue());
                } else {
                    ImportErrorPtr err = std::make_shared<ImportError>();
                    err->setDescription("Invalid attribute '" + attribute->getType() +
                                        "' found in import of component '" + childNode->getAttribute("name") +
                                        "' from '" + node->getAttribute("href") + "'.");
                    err->setImport(import);
                    mParser->addError(err);
                    errorOccurred = true;
                }
                attribute = attribute->getNext();
            }
            if (!errorOccurred) {
                model->addComponent(importedComponent);
            }
        } else if (childNode->isType("units")) {
            UnitsPtr importedUnits = std::make_shared<Units>();
            bool errorOccurred = false;
            XmlAttributePtr attribute = childNode->getFirstAttribute();
            while (attribute) {
                if (attribute->isType("name")) {
                    importedUnits->setName(attribute->getValue());
                } else if (attribute->isType("units_ref")) {
                    importedUnits->setSourceUnits(import, attribute->getValue());
                } else {
                    ImportErrorPtr err = std::make_shared<ImportError>();
                    err->setDescription("Invalid attribute '" + attribute->getType() +
                                        "' found in import of units '" + childNode->getAttribute("name") +
                                        "' from '" + node->getAttribute("href") + "'.");
                    err->setImport(import);
                    mParser->addError(err);
                    errorOccurred = true;
                }
                attribute = attribute->getNext();
            }
            if (!errorOccurred) {
                model->addUnits(importedUnits);
            }
        } else {
            ImportErrorPtr err = std::make_shared<ImportError>();
            err->setDescription("Invalid child element '" + childNode->getType() +
                                "' found in import from '" + node->getAttribute("href") + "'.");
            err->setImport(import);
            mParser->addError(err);
        }
        childNode = childNode->getNext();
    }
}

}

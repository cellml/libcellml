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

#include "libcellml/parser.h"

#include <string>
#include <vector>

#include "libcellml/component.h"
#include "libcellml/error.h"
#include "libcellml/importsource.h"
#include "libcellml/model.h"
#include "libcellml/variable.h"
#include "utilities.h"
#include "xmldoc.h"

namespace libcellml {

/**
 * @brief The Parser::ParserImpl struct.
 *
 * The private implementation for the Parser class.
 */
struct Parser::ParserImpl
{
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

    /**
     * @brief Update a @p model with the attributes from a @c std::string.
     *
     * Update the @p model with entities and attributes
     * from the @c std::string @p input. Any entities or attributes
     * in the @p model with names matching those in @p input
     * will be overwritten.
     *
     * @param model The @c ModelPtr to update.
     * @param input The string to parse and update the @p model with.
     */
    void updateModel(const ModelPtr &model, const std::string &input);

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
     * @brief Update the @p import source with attributes parsed from @p node and add any imported
     * components or units it to the @p model.
     *
     * Update the @p import source with attributes parsed from @p node and add any imported
     * components or units to the @p model. If any attributes exist in @p import source
     * with names matching those in @p node, they will be overwritten. Likewise,
     * any imported components or units of the same name already in @p model will
     * be overwritten by those parsed from @p node.
     *
     * @param importSource The @c ImportSourcePtr to update.
     * @param model The @c ModelPtr to add imported components/units to.
     * @param node The @c XmlNodePtr to parse and update the @p import source with.
     */
    void loadImport(const ImportSourcePtr &importSource, const ModelPtr &model, const XmlNodePtr &node);

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
};

Parser::Parser()
    : mPimpl(new ParserImpl())
{
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
    mPimpl->updateModel(model, input);
    return model;
}

void Parser::ParserImpl::updateModel(const ModelPtr &model, const std::string &input)
{
    loadModel(model, input);
}

void Parser::ParserImpl::loadModel(const ModelPtr &model, const std::string &input)
{
    XmlDocPtr doc = std::make_shared<XmlDoc>();
    doc->parse(input);
    // Copy any XML parsing errors into the common parser error handler.
    if (doc->xmlErrorCount() > 0) {
        for (size_t i = 0; i < doc->xmlErrorCount(); ++i) {
            ErrorPtr err = std::make_shared<Error>();
            err->setDescription(doc->getXmlError(i));
            err->setKind(Error::Kind::XML);
            mParser->addError(err);
        }
    }
    const XmlNodePtr node = doc->getRootNode();
    if (!node) {
        ErrorPtr err = std::make_shared<Error>();
        err->setDescription("Could not get a valid XML root node from the provided input.");
        err->setKind(Error::Kind::XML);
        mParser->addError(err);
        return;
    } else if (!node->isType("model")) {
        ErrorPtr err = std::make_shared<Error>();
        err->setDescription("Model root node is of invalid type '" + node->getType() +
                            "'. A valid CellML root node should be of type 'model'.");
        err->setModel(model);
        err->setKind(Error::Kind::MODEL);
        err->setRule(SpecificationRule::MODEL_ELEMENT);
        mParser->addError(err);
        return;
    }
    // Get model attributes.
    XmlAttributePtr attribute = node->getFirstAttribute();
    while (attribute) {
        if (attribute->isType("name")) {
            model->setName(attribute->getValue());
        } else if (attribute->isType("id")) {
            model->setId(attribute->getValue());
        } else {
            ErrorPtr err = std::make_shared<Error>();
            err->setDescription("Model '" + node->getAttribute("name") +
                                "' has an invalid attribute '" + attribute->getType() + "'.");
            err->setModel(model);
            err->setKind(Error::Kind::MODEL);
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
            ImportSourcePtr importSource = std::make_shared<ImportSource>();
            loadImport(importSource, model, childNode);
        } else if (childNode->isType("encapsulation")) {
            // An encapsulation should not have attributes.
            if (childNode->getFirstAttribute()) {
                XmlAttributePtr attribute = childNode->getFirstAttribute();
                while (attribute) {
                    ErrorPtr err = std::make_shared<Error>();
                    err->setDescription("Encapsulation in model '" + model->getName() +
                                        "' has an invalid attribute '" + attribute->getType() + "'.");
                    err->setModel(model);
                    err->setKind(Error::Kind::ENCAPSULATION);
                    mParser->addError(err);
                    attribute = attribute->getNext();
                }
            }
            // Load encapsulated component_refs.
            XmlNodePtr componentRefNode = childNode->getFirstChild();
            if (componentRefNode) {
                // This component_ref and its child and sibling elements will be loaded
                // and error-checked in loadEncapsulation().
                loadEncapsulation(model, componentRefNode);
            } else {
                ErrorPtr err = std::make_shared<Error>();
                err->setDescription("Encapsulation in model '" + model->getName() +
                                    "' does not contain any child elements.");
                err->setModel(model);
                err->setKind(Error::Kind::ENCAPSULATION);
                err->setRule(SpecificationRule::ENCAPSULATION_COMPONENT_REF);
                mParser->addError(err);
            }
        } else if (childNode->isType("connection")) {
            loadConnection(model, childNode);
        } else if (childNode->isType("text")) {
            std::string textNode = childNode->convertToString();
            // Ignore whitespace when parsing.
            if (hasNonWhitespaceCharacters(textNode)) {
                ErrorPtr err = std::make_shared<Error>();
                err->setDescription("Model '" + model->getName() +
                                    "' has an invalid non-whitespace child text element '" + textNode + "'.");
                err->setModel(model);
                err->setKind(Error::Kind::MODEL);
                err->setRule(SpecificationRule::MODEL_CHILD);
                mParser->addError(err);
            }
        } else {
            ErrorPtr err = std::make_shared<Error>();
            err->setDescription("Model '" + model->getName() +
                                "' has an invalid child element '" + childNode->getType() + "'.");
            err->setModel(model);
            err->setKind(Error::Kind::MODEL);
            err->setRule(SpecificationRule::MODEL_CHILD);
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
        } else if (attribute->isType("id")) {
            component->setId(attribute->getValue());
        } else {
            ErrorPtr err = std::make_shared<Error>();
            err->setDescription("Component '" + node->getAttribute("name") +
                                "' has an invalid attribute '" + attribute->getType() + "'.");
            err->setComponent(component);
            err->setKind(Error::Kind::COMPONENT);
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
        } else if (childNode->isType("math")) {
            // TODO: copy any namespaces declared in parents into the math element
            //       so math is a valid subdocument.
            std::string math = childNode->convertToString();
            component->appendMath(math);
        } else if (childNode->isType("text")) {
            std::string textNode = childNode->convertToString();
            // Ignore whitespace when parsing.
            if (hasNonWhitespaceCharacters(textNode)) {
                ErrorPtr err = std::make_shared<Error>();
                err->setDescription("Component '" + component->getName() +
                                    "' has an invalid non-whitespace child text element '" + textNode + "'.");
                err->setComponent(component);
                err->setKind(Error::Kind::COMPONENT);
                err->setRule(SpecificationRule::COMPONENT_CHILD);
                mParser->addError(err);
            }
        } else {
            ErrorPtr err = std::make_shared<Error>();
            err->setDescription("Component '" + component->getName() +
                                "' has an invalid child element '" + childNode->getType() + "'.");
            err->setComponent(component);
            err->setKind(Error::Kind::COMPONENT);
            err->setRule(SpecificationRule::COMPONENT_CHILD);
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
        } else if (attribute->isType("id")) {
            units->setId(attribute->getValue());
        } else {
            ErrorPtr err = std::make_shared<Error>();
            err->setDescription("Units '" + units->getName() +
                                "' has an invalid attribute '" + attribute->getType() + "'.");
            err->setUnits(units);
            err->setKind(Error::Kind::UNITS);
            mParser->addError(err);
        }
        attribute = attribute->getNext();
    }
    XmlNodePtr childNode = node->getFirstChild();
    while (childNode) {
        if (childNode->isType("unit")) {
            loadUnit(units, childNode);
        } else if (childNode->isType("text")) {
            std::string textNode = childNode->convertToString();
            // Ignore whitespace when parsing.
            if (hasNonWhitespaceCharacters(textNode)) {
                ErrorPtr err = std::make_shared<Error>();
                err->setDescription("Units '" + units->getName() +
                                    "' has an invalid non-whitespace child text element '" + textNode + "'.");
                err->setUnits(units);
                err->setKind(Error::Kind::UNITS);
                err->setRule(SpecificationRule::UNITS_CHILD);
                mParser->addError(err);
            }
        } else {
            ErrorPtr err = std::make_shared<Error>();
            err->setDescription("Units '" + units->getName() +
                                "' has an invalid child element '" + childNode->getType() + "'.");
            err->setUnits(units);
            err->setKind(Error::Kind::UNITS);
            err->setRule(SpecificationRule::UNITS_CHILD);
            mParser->addError(err);
        }
        childNode = childNode->getNext();
    }
}

void Parser::ParserImpl::loadUnit(const UnitsPtr &units, const XmlNodePtr &node)
{
    std::string reference = "";
    std::string prefix = "";
    double exponent = 1.0;
    double multiplier = 1.0;
    // A unit should not have any children.
    if (node->getFirstChild()) {
        XmlNodePtr childNode = node->getFirstChild();
        while (childNode) {
            if (childNode->isType("text")) {
                std::string textNode = childNode->convertToString();
                // Ignore whitespace when parsing.
                if (hasNonWhitespaceCharacters(textNode)) {
                    ErrorPtr err = std::make_shared<Error>();
                    err->setDescription("Unit referencing '" + node->getAttribute("units") +
                                        "' in units '" + units->getName() +
                                        "' has an invalid non-whitespace child text element '" + textNode + "'.");
                    err->setUnits(units);
                    err->setKind(Error::Kind::UNITS);
                    mParser->addError(err);
                }
            } else {
                ErrorPtr err = std::make_shared<Error>();
                err->setDescription("Unit referencing '" + node->getAttribute("units") +
                                    "' in units '" + units->getName() +
                                    "' has an invalid child element '" + childNode->getType() + "'.");
                err->setUnits(units);
                mParser->addError(err);
                err->setKind(Error::Kind::UNITS);
            }
            childNode = childNode->getNext();
        }
    }
    // Parse the unit attributes.
    XmlAttributePtr attribute = node->getFirstAttribute();
    while (attribute) {
        if (attribute->isType("units")) {
            reference = attribute->getValue();
        } else if (attribute->isType("prefix")) {
            prefix = attribute->getValue();
        } else if (attribute->isType("exponent")) {
            if (!convertToDouble(attribute->getValue(), &exponent)) {
                ErrorPtr err = std::make_shared<Error>();
                err->setDescription("Unit referencing '" + node->getAttribute("units") +
                                    "' in units '" + units->getName() +
                                    "' has an exponent with the value '" + attribute->getValue() +
                                    "' that cannot be converted to a decimal number.");
                err->setUnits(units);
                err->setKind(Error::Kind::UNITS);
                err->setRule(SpecificationRule::UNIT_EXPONENT);
                mParser->addError(err);
            }
        } else if (attribute->isType("multiplier")) {
            if (!convertToDouble(attribute->getValue(), &multiplier)) {
                ErrorPtr err = std::make_shared<Error>();
                err->setDescription("Unit referencing '" + node->getAttribute("units") +
                                    "' in units '" + units->getName() +
                                    "' has a multiplier with the value '" + attribute->getValue() +
                                    "' that cannot be converted to a decimal number.");
                err->setUnits(units);
                err->setKind(Error::Kind::UNITS);
                err->setRule(SpecificationRule::UNIT_MULTIPLIER);
                mParser->addError(err);
            }
        } else {
            ErrorPtr err = std::make_shared<Error>();
            err->setDescription("Unit referencing '" + node->getAttribute("units") +
                                "' in units '" + units->getName() +
                                "' has an invalid attribute '" + attribute->getType() + "'.");
            err->setUnits(units);
            err->setKind(Error::Kind::UNITS);
            err->setRule(SpecificationRule::UNIT_ATTRIBUTE);
            mParser->addError(err);
        }
        attribute = attribute->getNext();
    }
    // Add this unit to the parent units.
    units->addUnit(reference, prefix, exponent, multiplier);
}

void Parser::ParserImpl::loadVariable(const VariablePtr &variable, const XmlNodePtr &node)
{
    // A variable should not have any children.
    if (node->getFirstChild()) {
        XmlNodePtr childNode = node->getFirstChild();
        while (childNode) {
            if (childNode->isType("text")) {
                std::string textNode = childNode->convertToString();
                // Ignore whitespace when parsing.
                if (hasNonWhitespaceCharacters(textNode)) {
                    ErrorPtr err = std::make_shared<Error>();
                    err->setDescription("Variable '" + node->getAttribute("name") +
                                        "' has an invalid non-whitespace child text element '" + textNode + "'.");
                    err->setVariable(variable);
                    err->setKind(Error::Kind::VARIABLE);
                    mParser->addError(err);
                }
            } else {
                ErrorPtr err = std::make_shared<Error>();
                err->setDescription("Variable '" + node->getAttribute("name") +
                                    "' has an invalid child element '" + childNode->getType() + "'.");
                err->setVariable(variable);
                err->setKind(Error::Kind::VARIABLE);
                mParser->addError(err);
            }
            childNode = childNode->getNext();
        }
    }
    XmlAttributePtr attribute = node->getFirstAttribute();
    while (attribute) {
        if (attribute->isType("name")) {
            variable->setName(attribute->getValue());
        } else if (attribute->isType("id")) {
            variable->setId(attribute->getValue());
        } else if (attribute->isType("units")) {
            variable->setUnits(attribute->getValue());
        } else if (attribute->isType("interface")) {
            variable->setInterfaceType(attribute->getValue());
        } else if (attribute->isType("initial_value")) {
            variable->setInitialValue(attribute->getValue());
        } else {
            ErrorPtr err = std::make_shared<Error>();
            err->setDescription("Variable '" + node->getAttribute("name") +
                                "' has an invalid attribute '" + attribute->getType() + "'.");
            err->setVariable(variable);
            err->setKind(Error::Kind::VARIABLE);
            err->setRule(SpecificationRule::VARIABLE_ATTRIBUTE);
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

    // Initialise name pairs and flags.
    NamePair componentNamePair, variableNamePair;
    NamePairMap variableNameMap;
    bool mapVariablesFound = false;
    bool component1Missing = false;
    bool component2Missing = false;
    bool variable1Missing = false;
    bool variable2Missing = false;

    // Check connection for component_{1, 2} attributes and get the name pair.
    std::string component1Name = "";
    std::string component2Name = "";
    XmlAttributePtr attribute = node->getFirstAttribute();
    while (attribute) {
        if (attribute->isType("component_1")) {
            component1Name = attribute->getValue();
        } else if (attribute->isType("component_2")) {
            component2Name = attribute->getValue();
        } else {
            ErrorPtr err = std::make_shared<Error>();
            err->setDescription("Connection in model '" + model->getName() +
                                "' has an invalid connection attribute '" + attribute->getType() + "'.");
            err->setModel(model);
            err->setKind(Error::Kind::CONNECTION);
            mParser->addError(err);
        }
        attribute = attribute->getNext();
    }
    // Check that we found both components.
    if (!component1Name.length()) {
        ErrorPtr err = std::make_shared<Error>();
        err->setDescription("Connection in model '" + model->getName() +
                            "' does not have a valid component_1 in a connection element.");
        err->setModel(model);
        err->setKind(Error::Kind::CONNECTION);
        err->setRule(SpecificationRule::MAP_COMPONENTS_COMPONENT1);
        mParser->addError(err);
        component1Missing = true;
    }
    if (!component2Name.length()) {
        ErrorPtr err = std::make_shared<Error>();
        err->setDescription("Connection in model '" + model->getName() +
                            "' does not have a valid component_2 in a connection element.");
        err->setModel(model);
        err->setKind(Error::Kind::CONNECTION);
        err->setRule(SpecificationRule::MAP_COMPONENTS_COMPONENT2);
        mParser->addError(err);
        component2Missing = true;
    }
    componentNamePair = std::make_pair(component1Name, component2Name);

    XmlNodePtr childNode = node->getFirstChild();
    if (!childNode) {
        ErrorPtr err = std::make_shared<Error>();
        err->setDescription("Connection in model '" + model->getName() +
                            "' must contain one or more 'map_variables' elements.");
        err->setModel(model);
        err->setKind(Error::Kind::CONNECTION);
        err->setRule(SpecificationRule::CONNECTION_CHILD);
        mParser->addError(err);
        return;
    }

    // Iterate over connection child XML nodes.
    while (childNode) {
        // Connection map XML nodes should not have further children.
        if (childNode->getFirstChild()) {
            XmlNodePtr grandchildNode = childNode->getFirstChild();
            if (grandchildNode->isType("text")) {
                std::string textNode = grandchildNode->convertToString();
                // Ignore whitespace when parsing.
                if (hasNonWhitespaceCharacters(textNode)) {
                    ErrorPtr err = std::make_shared<Error>();
                    err->setDescription("Connection in model '" + model->getName() +
                                        "' has an invalid non-whitespace child text element '" + textNode + "'.");
                    err->setModel(model);
                    err->setKind(Error::Kind::CONNECTION);
                    err->setRule(SpecificationRule::CONNECTION_CHILD);
                    mParser->addError(err);
                }
            } else {
                ErrorPtr err = std::make_shared<Error>();
                err->setDescription("Connection in model '" + model->getName() +
                                    "' has an invalid child element '" + grandchildNode->getType() +
                                    "' of element '" + childNode->getType() + "'.");
                err->setModel(model);
                err->setKind(Error::Kind::CONNECTION);
                mParser->addError(err);
            }
        }

        if (childNode->isType("map_variables")) {
            std::string variable1Name = "";
            std::string variable2Name = "";
            XmlAttributePtr attribute = childNode->getFirstAttribute();
            while (attribute) {
                if (attribute->isType("variable_1")) {
                    variable1Name = attribute->getValue();
                } else if (attribute->isType("variable_2")) {
                    variable2Name = attribute->getValue();
                } else {
                    ErrorPtr err = std::make_shared<Error>();
                    err->setDescription("Connection in model '" + model->getName() +
                                        "' has an invalid map_variables attribute '" + attribute->getType() + "'.");
                    err->setModel(model);
                    err->setKind(Error::Kind::CONNECTION);
                    mParser->addError(err);
                }
                attribute = attribute->getNext();
            }
            // Check that we found both variables.
            if (!variable1Name.length()) {
                ErrorPtr err = std::make_shared<Error>();
                err->setDescription("Connection in model '" + model->getName() +
                                    "' does not have a valid variable_1 in a map_variables element.");
                err->setModel(model);
                err->setKind(Error::Kind::CONNECTION);
                err->setRule(SpecificationRule::MAP_VARIABLES_VARIABLE1);
                mParser->addError(err);
                variable1Missing = true;
            }
            if (!variable2Name.length()) {
                ErrorPtr err = std::make_shared<Error>();
                err->setDescription("Connection in model '" + model->getName() +
                                    "' does not have a valid variable_2 in a map_variables element.");
                err->setModel(model);
                err->setKind(Error::Kind::CONNECTION);
                err->setRule(SpecificationRule::MAP_VARIABLES_VARIABLE2);
                mParser->addError(err);
                variable2Missing = true;
            }
            // We can have multiple map_variables per connection.
            variableNamePair = std::make_pair(variable1Name, variable2Name);
            variableNameMap.push_back(variableNamePair);
            mapVariablesFound = true;

        } else if (childNode->isType("text")) {
            const std::string textNode = childNode->convertToString();
            // Ignore whitespace when parsing.
            if (hasNonWhitespaceCharacters(textNode)) {
                ErrorPtr err = std::make_shared<Error>();
                err->setDescription("Connection in model '" + model->getName() +
                                    "' has an invalid non-whitespace child text element '" + textNode + "'.");
                err->setModel(model);
                err->setKind(Error::Kind::CONNECTION);
                err->setRule(SpecificationRule::CONNECTION_CHILD);
                mParser->addError(err);
            }
        } else {
            ErrorPtr err = std::make_shared<Error>();
            err->setDescription("Connection in model '" + model->getName() +
                                "' has an invalid child element '" + childNode->getType() + "'.");
            err->setModel(model);
            err->setKind(Error::Kind::CONNECTION);
            err->setRule(SpecificationRule::CONNECTION_CHILD);
            mParser->addError(err);
        }
        childNode = childNode->getNext();
    }

    // If we have a component name pair, check that the components exist in the model.
    ComponentPtr component1 = nullptr;
    ComponentPtr component2 = nullptr;
    // Now check the objects exist in the model.
    if (model->containsComponent(componentNamePair.first)) {
        component1 = model->getComponent(componentNamePair.first);
    } else {
        if (!component1Missing) {
            ErrorPtr err = std::make_shared<Error>();
            err->setDescription("Connection in model '" + model->getName() +
                                "' specifies '" + componentNamePair.first +
                                "' as component_1 but it does not exist in the model.");
            err->setModel(model);
            err->setKind(Error::Kind::CONNECTION);
            err->setRule(SpecificationRule::MAP_COMPONENTS_COMPONENT1);
            mParser->addError(err);
        }
    }
    if (model->containsComponent(componentNamePair.second)) {
        component2 = model->getComponent(componentNamePair.second);
    } else {
        if (!component2Missing) {
            ErrorPtr err = std::make_shared<Error>();
            err->setDescription("Connection in model '" + model->getName() +
                                "' specifies '" + componentNamePair.second +
                                "' as component_2 but it does not exist in the model.");
            err->setModel(model);
            err->setKind(Error::Kind::CONNECTION);
            err->setRule(SpecificationRule::MAP_COMPONENTS_COMPONENT2);
            mParser->addError(err);
        }
    }

    // If we have a map_variables, check that the variables exist in the named components.
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
                        ErrorPtr err = std::make_shared<Error>();
                        err->setDescription("Variable '" + iterPair->first +
                                            "' is specified as variable_1 in a connection but it does not exist in component_1 component '"
                                            + component1->getName() + "' of model '" + model->getName() + "'.");
                        err->setComponent(component1);
                        err->setKind(Error::Kind::CONNECTION);
                        err->setRule(SpecificationRule::MAP_VARIABLES_VARIABLE1);
                        mParser->addError(err);
                    }
                }
            } else {
                ErrorPtr err = std::make_shared<Error>();
                err->setDescription("Connection in model '" + model->getName() +
                                    "' specifies '" + iterPair->first +
                                    "' as variable_1 but the corresponding component_1 is invalid.");
                err->setModel(model);
                err->setKind(Error::Kind::CONNECTION);
                err->setRule(SpecificationRule::MAP_VARIABLES_VARIABLE1);
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
                        ErrorPtr err = std::make_shared<Error>();
                        err->setDescription("Variable '" + iterPair->second +
                                            "' is specified as variable_2 in a connection but it does not exist in component_2 component '"
                                            + component2->getName() + "' of model '" + model->getName() + "'.");
                        err->setComponent(component1);
                        err->setKind(Error::Kind::CONNECTION);
                        err->setRule(SpecificationRule::MAP_VARIABLES_VARIABLE2);
                        mParser->addError(err);
                    }
                }
            } else {
                ErrorPtr err = std::make_shared<Error>();
                err->setDescription("Connection in model '" + model->getName() +
                                    "' specifies '" + iterPair->second +
                                    "' as variable_2 but the corresponding component_2 is invalid.");
                err->setModel(model);
                err->setKind(Error::Kind::CONNECTION);
                err->setRule(SpecificationRule::MAP_VARIABLES_VARIABLE2);
                mParser->addError(err);
            }
            // Set the variable equivalence relationship for this variable pair.
            if ((variable1) && (variable2)) {
                Variable::addEquivalence(variable1, variable2);
            }
        }
    } else {
        ErrorPtr err = std::make_shared<Error>();
        err->setDescription("Connection in model '" + model->getName() +
                            "' does not have a map_variables element.");
        err->setModel(model);
        err->setKind(Error::Kind::CONNECTION);
        err->setRule(SpecificationRule::CONNECTION_MAP_VARIABLES);
        mParser->addError(err);
    }
}

void Parser::ParserImpl::loadEncapsulation(const ModelPtr &model, const XmlNodePtr &node)
{
    XmlNodePtr parentComponentNode = node;
    while (parentComponentNode) {
        ComponentPtr parentComponent = nullptr;
        std::string parentComponentName;
        if (parentComponentNode->isType("component_ref")) {
            // Check for a component in the parent component_ref.
            XmlAttributePtr attribute = parentComponentNode->getFirstAttribute();
            while (attribute) {
                if (attribute->isType("component")) {
                    parentComponentName = attribute->getValue();
                    if (model->containsComponent(parentComponentName)) {
                        // Will re-add this to the model once we encapsulate the child(ren).
                        parentComponent = model->takeComponent(parentComponentName);
                    } else {
                        ErrorPtr err = std::make_shared<Error>();
                        err->setDescription("Encapsulation in model '" + model->getName() +
                                            "' specifies '" + parentComponentName +
                                            "' as a component in a component_ref but it does not exist in the model.");
                        err->setModel(model);
                        err->setKind(Error::Kind::ENCAPSULATION);
                        err->setRule(SpecificationRule::COMPONENT_REF_COMPONENT);
                        mParser->addError(err);
                    }
                } else {
                    ErrorPtr err = std::make_shared<Error>();
                    err->setDescription("Encapsulation in model '" + model->getName() +
                                        "' has an invalid component_ref attribute '" + attribute->getType() + "'.");
                    err->setModel(model);
                    err->setKind(Error::Kind::ENCAPSULATION);
                    err->setRule(SpecificationRule::COMPONENT_REF_COMPONENT);
                    mParser->addError(err);
                }
                attribute = attribute->getNext();
            }
            if ((!parentComponent) && (!parentComponentName.length())) {
                ErrorPtr err = std::make_shared<Error>();
                err->setDescription("Encapsulation in model '" + model->getName() +
                                    "' does not have a valid component attribute in a component_ref element.");
                err->setModel(model);
                err->setKind(Error::Kind::ENCAPSULATION);
                err->setRule(SpecificationRule::COMPONENT_REF_COMPONENT);
                mParser->addError(err);
            }
        } else if (parentComponentNode->isType("text")) {
            const std::string textNode = parentComponentNode->convertToString();
            // Ignore whitespace when parsing.
            if (hasNonWhitespaceCharacters(textNode)) {
                ErrorPtr err = std::make_shared<Error>();
                err->setDescription("Encapsulation in model '" + model->getName() +
                                    "' has an invalid non-whitespace child text element '" + textNode + "'.");
                err->setModel(model);
                err->setKind(Error::Kind::ENCAPSULATION);
                err->setRule(SpecificationRule::COMPONENT_REF_CHILD);
                mParser->addError(err);
            } else {
                // Continue to next node if this is whitespace (don't try to parse children of whitespace).
                parentComponentNode = parentComponentNode->getNext();
                continue;
            }
        } else {
            ErrorPtr err = std::make_shared<Error>();
            err->setDescription("Encapsulation in model '" + model->getName() +
                                "' has an invalid child element '" + parentComponentNode->getType() + "'.");
            err->setModel(model);
            err->setKind(Error::Kind::ENCAPSULATION);
            err->setRule(SpecificationRule::ENCAPSULATION_COMPONENT_REF);
            mParser->addError(err);
        }

        // Get first child of this parent component_ref.
        XmlNodePtr childComponentNode = parentComponentNode->getFirstChild();
        if (!childComponentNode) {
            XmlNodePtr grandParentComponentNode = parentComponentNode->getParent();
            if (grandParentComponentNode->getType() == "encapsulation") {
                ErrorPtr err = std::make_shared<Error>();
                if (parentComponent) {
                    err->setDescription("Encapsulation in model '" + model->getName() +
                                        "' specifies '" + parentComponent->getName() +
                                        "' as a parent component_ref but it does not have any children.");
                } else {
                    err->setDescription("Encapsulation in model '" + model->getName() +
                                        "' specifies an invalid parent component_ref that also does not have any children.");
                }
                err->setModel(model);
                err->setKind(Error::Kind::ENCAPSULATION);
                mParser->addError(err);
            }
        }

        // Loop over encapsulated children.
        while (childComponentNode) {
            ComponentPtr childComponent = nullptr;
            if (childComponentNode->isType("component_ref")) {
                bool childComponentMissing = false;
                bool foundChildComponent = false;
                XmlAttributePtr attribute = childComponentNode->getFirstAttribute();
                while (attribute) {
                    if (attribute->isType("component")) {
                        const std::string childComponentName = attribute->getValue();
                        if (model->containsComponent(childComponentName)) {
                            childComponent = model->getComponent(childComponentName);
                            foundChildComponent = true;
                        } else {
                            ErrorPtr err = std::make_shared<Error>();
                            err->setDescription("Encapsulation in model '" + model->getName() +
                                                "' specifies '" + childComponentName +
                                                "' as a component in a component_ref but it does not exist in the model.");
                            err->setModel(model);
                            err->setKind(Error::Kind::ENCAPSULATION);
                            err->setRule(SpecificationRule::COMPONENT_REF_COMPONENT);
                            mParser->addError(err);
                            childComponentMissing = true;
                        }
                    } else {
                        ErrorPtr err = std::make_shared<Error>();
                        err->setDescription("Encapsulation in model '" + model->getName() +
                                            "' has an invalid component_ref attribute '" + attribute->getType() + "'.");
                        err->setModel(model);
                        err->setKind(Error::Kind::ENCAPSULATION);
                        mParser->addError(err);
                    }
                    attribute = attribute->getNext();
                }
                if ((!foundChildComponent) && (!childComponentMissing)) {
                    ErrorPtr err = std::make_shared<Error>();
                    if (parentComponent) {
                        err->setDescription("Encapsulation in model '" + model->getName() +
                                            "' does not have a valid component attribute in a component_ref that is a child of '"
                                            + parentComponent->getName() + "'.");
                    } else if (parentComponentName.length()) {
                        err->setDescription("Encapsulation in model '" + model->getName() +
                                            "' does not have a valid component attribute in a component_ref that is a child of invalid parent component '"
                                            + parentComponentName + "'.");
                    } else {
                        err->setDescription("Encapsulation in model '" + model->getName() +
                                            "' does not have a valid component attribute in a component_ref that is a child of an invalid parent component.");
                    }
                    err->setModel(model);
                    err->setKind(Error::Kind::ENCAPSULATION);
                    err->setRule(SpecificationRule::COMPONENT_REF_COMPONENT);
                    mParser->addError(err);
                }

            } else if (childComponentNode->isType("text")) {
                const std::string textNode = childComponentNode->convertToString();
                // Ignore whitespace when parsing.
                if (hasNonWhitespaceCharacters(textNode)) {
                    ErrorPtr err = std::make_shared<Error>();
                    err->setDescription("Encapsulation in model '" + model->getName() +
                                        "' has an invalid non-whitespace child text element '" + textNode + "'.");
                    err->setModel(model);
                    err->setKind(Error::Kind::ENCAPSULATION);
                    err->setRule(SpecificationRule::COMPONENT_REF_CHILD);
                    mParser->addError(err);
                }
            } else {
                ErrorPtr err = std::make_shared<Error>();
                err->setDescription("Encapsulation in model '" + model->getName() +
                                    "' has an invalid child element '" + childComponentNode->getType() + "'.");
                err->setModel(model);
                err->setKind(Error::Kind::ENCAPSULATION);
                err->setRule(SpecificationRule::COMPONENT_REF_CHILD);
                mParser->addError(err);
            }

            if ((parentComponent) && (childComponent)) {
                // Set parent/child encapsulation relationship.
                parentComponent->addComponent(childComponent);
            }
            // Load any further encapsulated children.
            if (childComponentNode->getFirstChild()) {
                loadEncapsulation(model, childComponentNode);
            }
            if ((parentComponent) && (childComponent)) {
                // A child component is added through its parent component rather than the model,
                // so remove it if it exists.
                model->removeComponent(childComponent);
            }
            childComponentNode = childComponentNode->getNext();
        }

        // Re-add the parentComponent to the model with its child(ren) encapsulated.
        if (parentComponent) {
            model->addComponent(parentComponent);
        }
        // Get the next parent component at this level
        parentComponentNode = parentComponentNode->getNext();
    }
}

void Parser::ParserImpl::loadImport(const ImportSourcePtr &importSource, const ModelPtr &model, const XmlNodePtr &node)
{
    XmlAttributePtr attribute = node->getFirstAttribute();
    while (attribute) {
        if (attribute->isType("href")) {
            importSource->setSource(attribute->getValue());
        } else if (attribute->isType("id")) {
            importSource->setId(attribute->getValue());
        } else if (attribute->isType("xlink")) {
            // Allow xlink attributes but do nothing for them.
        } else {
            ErrorPtr err = std::make_shared<Error>();
            err->setDescription("Import from '" + node->getAttribute("href") +
                                "' has an invalid attribute '" + attribute->getType() + "'.");
            err->setImportSource(importSource);
            err->setKind(Error::Kind::IMPORT);
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
                } else if (attribute->isType("id")) {
                    importedComponent->setId(attribute->getValue());
                } else if (attribute->isType("component_ref")) {
                    importedComponent->setSourceComponent(importSource, attribute->getValue());
                } else {
                    ErrorPtr err = std::make_shared<Error>();
                    err->setDescription("Import of component '" + childNode->getAttribute("name") +
                                        "' from '" + node->getAttribute("href") +
                                        "' has an invalid attribute '" + attribute->getType() + "'.");
                    err->setImportSource(importSource);
                    err->setKind(Error::Kind::IMPORT);
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
                } else if (attribute->isType("id")) {
                    importedUnits->setId(attribute->getValue());
                } else if (attribute->isType("units_ref")) {
                    importedUnits->setSourceUnits(importSource, attribute->getValue());
                } else {
                    ErrorPtr err = std::make_shared<Error>();
                    err->setDescription("Import of units '" + childNode->getAttribute("name") +
                                        "' from '" + node->getAttribute("href") +
                                        "' has an invalid attribute '" + attribute->getType() + "'.");
                    err->setImportSource(importSource);
                    err->setKind(Error::Kind::IMPORT);
                    mParser->addError(err);
                    errorOccurred = true;
                }
                attribute = attribute->getNext();
            }
            if (!errorOccurred) {
                model->addUnits(importedUnits);
            }
        } else if (childNode->isType("text")) {
            const std::string textNode = childNode->convertToString();
            // Ignore whitespace when parsing.
            if (hasNonWhitespaceCharacters(textNode)) {
                ErrorPtr err = std::make_shared<Error>();
                err->setDescription("Import from '" + node->getAttribute("href") +
                                    "' has an invalid non-whitespace child text element '" + textNode + "'.");
                err->setImportSource(importSource);
                err->setKind(Error::Kind::IMPORT);
                err->setRule(SpecificationRule::IMPORT_CHILD);
                mParser->addError(err);
            }
        } else {
            ErrorPtr err = std::make_shared<Error>();
            err->setDescription("Import from '" + node->getAttribute("href") +
                                "' has an invalid child element '" + childNode->getType() + "'.");
            err->setImportSource(importSource);
            err->setKind(Error::Kind::IMPORT);
            err->setRule(SpecificationRule::IMPORT_CHILD);
            mParser->addError(err);
        }
        childNode = childNode->getNext();
    }
}

}

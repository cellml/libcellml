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

#include "namespaces.h"
#include "utilities.h"
#include "xmldoc.h"

#include "libcellml/component.h"
#include "libcellml/error.h"
#include "libcellml/importsource.h"
#include "libcellml/model.h"
#include "libcellml/parser.h"
#include "libcellml/reset.h"
#include "libcellml/variable.h"

#include <iostream>
#include <string>
#include <vector>

namespace libcellml {

/**
 * @brief The Parser::ParserImpl struct.
 *
 * The private implementation for the Parser class.
 */
struct Parser::ParserImpl
{
    Parser *mParser = nullptr;

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

    /**
     * @brief Update the @p reset with attributes parsed from the @p node.
     *
     * Update the @p reset with attributes parsed from
     * the XML @p node. Existing attributes in @p reset with names
     * matching those in @p node will be overwritten.
     *
     * @param reset The @c ResetPtr to update.
     * @param component The @c ComponentPtr the reset belongs to.
     * @param node The @c XmlNodePtr to parse and update the @p variable with.
     */
    void loadReset(const ResetPtr &reset, const ComponentPtr &component, const XmlNodePtr &node);
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

Parser::Parser(const Parser &rhs)
    : Logger(rhs)
    , mPimpl(new ParserImpl())
{
    mPimpl->mParser = rhs.mPimpl->mParser;
}

Parser::Parser(Parser &&rhs) noexcept
    : Logger(std::move(rhs))
    , mPimpl(rhs.mPimpl)
{
    rhs.mPimpl = nullptr;
}

Parser &Parser::operator=(Parser rhs)
{
    Logger::operator=(rhs);
    rhs.swap(*this);
    return *this;
}

void Parser::swap(Parser &rhs)
{
    std::swap(mPimpl, rhs.mPimpl);
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
            err->setDescription(doc->xmlError(i));
            err->setKind(Error::Kind::XML);
            mParser->addError(err);
        }
    }
    const XmlNodePtr node = doc->rootNode();
    if (!node) {
        ErrorPtr err = std::make_shared<Error>();
        err->setDescription("Could not get a valid XML root node from the provided input.");
        err->setKind(Error::Kind::XML);
        mParser->addError(err);
        return;
    }
    if (!node->isCellmlElement("model")) {
        ErrorPtr err = std::make_shared<Error>();
        if (node->name() == "model") {
            std::string nodeNamespace = node->namespaceUri();
            if (nodeNamespace.empty()) {
                nodeNamespace = "null";
            }
            err->setDescription("Model element is in invalid namespace '" + nodeNamespace + "'. A valid CellML root node should be in namespace '" + CELLML_2_0_NS + "'.");
        } else {
            err->setDescription("Model element is of invalid type '" + node->name() + "'. A valid CellML root node should be of type 'model'.");
        }
        err->setModel(model);
        err->setRule(SpecificationRule::MODEL_ELEMENT);
        mParser->addError(err);
        return;
    }
    // Get model attributes.
    XmlAttributePtr attribute = node->firstAttribute();
    while (attribute) {
        if (attribute->isType("name")) {
            model->setName(attribute->value());
        } else if (attribute->isType("id")) {
            model->setId(attribute->value());
        } else {
            ErrorPtr err = std::make_shared<Error>();
            err->setDescription("Model '" + node->attribute("name") + "' has an invalid attribute '" + attribute->name() + "'.");
            err->setModel(model);
            mParser->addError(err);
        }
        attribute = attribute->next();
    }
    // Get model children (CellML entities).
    XmlNodePtr childNode = node->firstChild();
    std::vector<XmlNodePtr> connectionNodes;
    std::vector<XmlNodePtr> encapsulationNodes;
    while (childNode) {
        if (childNode->isCellmlElement("component")) {
            ComponentPtr component = std::make_shared<Component>();
            loadComponent(component, childNode);
            model->addComponent(component);
        } else if (childNode->isCellmlElement("units")) {
            UnitsPtr units = std::make_shared<Units>();
            loadUnits(units, childNode);
            model->addUnits(units);
        } else if (childNode->isCellmlElement("import")) {
            ImportSourcePtr importSource = std::make_shared<ImportSource>();
            loadImport(importSource, model, childNode);
        } else if (childNode->isCellmlElement("encapsulation")) {
            // An encapsulation should not have attributes other than an 'id' attribute.
            if (childNode->firstAttribute()) {
                XmlAttributePtr childAttribute = childNode->firstAttribute();
                while (childAttribute) {
                    if (childAttribute->isType("id")) {
                        model->setEncapsulationId(childAttribute->value());
                    } else {
                        ErrorPtr err = std::make_shared<Error>();
                        err->setDescription("Encapsulation in model '" + model->name() + "' has an invalid attribute '" + childAttribute->name() + "'.");
                        err->setModel(model);
                        err->setKind(Error::Kind::ENCAPSULATION);
                        mParser->addError(err);
                    }
                    childAttribute = childAttribute->next();
                }
            }
            // Load encapsulated component_refs.
            XmlNodePtr componentRefNode = childNode->firstChild();
            if (componentRefNode) {
                // This component_ref and its child and sibling elements will be loaded
                // and error-checked in loadEncapsulation().
                encapsulationNodes.push_back(componentRefNode);
            } else {
                // TODO Should this be removed?
                ErrorPtr err = std::make_shared<Error>();
                err->setDescription("Encapsulation in model '" + model->name() + "' does not contain any child elements.");
                err->setModel(model);
                err->setKind(Error::Kind::ENCAPSULATION);
                err->setRule(SpecificationRule::ENCAPSULATION_COMPONENT_REF);
                mParser->addError(err);
            }
        } else if (childNode->isCellmlElement("connection")) {
            connectionNodes.push_back(childNode);
        } else if (childNode->isText()) {
            std::string textNode = childNode->convertToString();
            // Ignore whitespace when parsing.
            if (hasNonWhitespaceCharacters(textNode)) {
                ErrorPtr err = std::make_shared<Error>();
                err->setDescription("Model '" + model->name() + "' has an invalid non-whitespace child text element '" + textNode + "'.");
                err->setModel(model);
                err->setRule(SpecificationRule::MODEL_CHILD);
                mParser->addError(err);
            }
        } else if (childNode->isComment()) {
            // Do nothing.
        } else {
            ErrorPtr err = std::make_shared<Error>();
            err->setDescription("Model '" + model->name() + "' has an invalid child element '" + childNode->name() + "'.");
            err->setModel(model);
            err->setRule(SpecificationRule::MODEL_CHILD);
            mParser->addError(err);
        }
        childNode = childNode->next();
    }

    if (!encapsulationNodes.empty()) {
        loadEncapsulation(model, encapsulationNodes.at(0));
        if (encapsulationNodes.size() > 1) {
            ErrorPtr err = std::make_shared<Error>();
            err->setDescription("Model '" + model->name() + "' has more than one encapsulation element.");
            err->setModel(model);
            err->setKind(Error::Kind::ENCAPSULATION);
            err->setRule(SpecificationRule::MODEL_MORE_THAN_ONE_ENCAPSULATION);
            mParser->addError(err);
        }
    }
    for (const auto &connectionNode : connectionNodes) {
        loadConnection(model, connectionNode);
    }
}

void Parser::ParserImpl::loadComponent(const ComponentPtr &component, const XmlNodePtr &node)
{
    XmlAttributePtr attribute = node->firstAttribute();
    while (attribute) {
        if (attribute->isType("name")) {
            component->setName(attribute->value());
        } else if (attribute->isType("id")) {
            component->setId(attribute->value());
        } else {
            ErrorPtr err = std::make_shared<Error>();
            err->setDescription("Component '" + node->attribute("name") + "' has an invalid attribute '" + attribute->name() + "'.");
            err->setComponent(component);
            mParser->addError(err);
        }
        attribute = attribute->next();
    }
    XmlNodePtr childNode = node->firstChild();
    while (childNode) {
        if (childNode->isCellmlElement("variable")) {
            VariablePtr variable = std::make_shared<Variable>();
            loadVariable(variable, childNode);
            component->addVariable(variable);
        } else if (childNode->isCellmlElement("reset")) {
            ResetPtr reset = std::make_shared<Reset>();
            loadReset(reset, component, childNode);
            component->addReset(reset);
        } else if (childNode->isMathmlElement("math")) {
            // TODO: copy any namespaces declared in parents into the math element
            //       so math is a valid subdocument.
            std::string math = childNode->convertToString(true) + "\n";
            component->appendMath(math);
        } else if (childNode->isText()) {
            std::string textNode = childNode->convertToString();
            // Ignore whitespace when parsing.
            if (hasNonWhitespaceCharacters(textNode)) {
                ErrorPtr err = std::make_shared<Error>();
                err->setDescription("Component '" + component->name() + "' has an invalid non-whitespace child text element '" + textNode + "'.");
                err->setComponent(component);
                err->setRule(SpecificationRule::COMPONENT_CHILD);
                mParser->addError(err);
            }
        } else if (childNode->isComment()) {
            // Do nothing.
        } else {
            ErrorPtr err = std::make_shared<Error>();
            err->setDescription("Component '" + component->name() + "' has an invalid child element '" + childNode->name() + "'.");
            err->setComponent(component);
            err->setRule(SpecificationRule::COMPONENT_CHILD);
            mParser->addError(err);
        }
        childNode = childNode->next();
    }
}

void Parser::ParserImpl::loadUnits(const UnitsPtr &units, const XmlNodePtr &node)
{
    XmlAttributePtr attribute = node->firstAttribute();
    while (attribute) {
        if (attribute->isType("name")) {
            units->setName(attribute->value());
        } else if (attribute->isType("id")) {
            units->setId(attribute->value());
        } else {
            ErrorPtr err = std::make_shared<Error>();
            err->setDescription("Units '" + units->name() + "' has an invalid attribute '" + attribute->name() + "'.");
            err->setUnits(units);
            mParser->addError(err);
        }
        attribute = attribute->next();
    }
    XmlNodePtr childNode = node->firstChild();
    while (childNode) {
        if (childNode->isCellmlElement("unit")) {
            loadUnit(units, childNode);
        } else if (childNode->isText()) {
            std::string textNode = childNode->convertToString();
            // Ignore whitespace when parsing.
            if (hasNonWhitespaceCharacters(textNode)) {
                ErrorPtr err = std::make_shared<Error>();
                err->setDescription("Units '" + units->name() + "' has an invalid non-whitespace child text element '" + textNode + "'.");
                err->setUnits(units);
                err->setRule(SpecificationRule::UNITS_CHILD);
                mParser->addError(err);
            }
        } else if (childNode->isComment()) {
            // Do nothing.
        } else {
            ErrorPtr err = std::make_shared<Error>();
            err->setDescription("Units '" + units->name() + "' has an invalid child element '" + childNode->name() + "'.");
            err->setUnits(units);
            err->setRule(SpecificationRule::UNITS_CHILD);
            mParser->addError(err);
        }
        childNode = childNode->next();
    }
}

void Parser::ParserImpl::loadUnit(const UnitsPtr &units, const XmlNodePtr &node)
{
    std::string reference;
    std::string prefix;
    double exponent = 1.0;
    double multiplier = 1.0;
    std::string id;
    // A unit should not have any children.
    XmlNodePtr childNode = node->firstChild();
    while (childNode) {
        if (childNode->isText()) {
            std::string textNode = childNode->convertToString();
            // Ignore whitespace when parsing.
            if (hasNonWhitespaceCharacters(textNode)) {
                ErrorPtr err = std::make_shared<Error>();
                err->setDescription("Unit referencing '" + node->attribute("units") + "' in units '" + units->name() + "' has an invalid non-whitespace child text element '" + textNode + "'.");
                err->setUnits(units);
                mParser->addError(err);
            }
        } else if (childNode->isComment()) {
            // Do nothing.
        } else {
            ErrorPtr err = std::make_shared<Error>();
            err->setDescription("Unit referencing '" + node->attribute("units") + "' in units '" + units->name() + "' has an invalid child element '" + childNode->name() + "'.");
            err->setUnits(units);
            mParser->addError(err);
        }
        childNode = childNode->next();
    }
    // Parse the unit attributes.
    XmlAttributePtr attribute = node->firstAttribute();
    while (attribute) {
        if (attribute->isType("units")) {
            reference = attribute->value();
        } else if (attribute->isType("prefix")) {
            prefix = attribute->value();
        } else if (attribute->isType("exponent")) {
            if (isCellMLReal(attribute->value())) {
                exponent = convertToDouble(attribute->value());
            } else {
                // TODO This value won't be saved for validation later, so it does need to be reported now
                ErrorPtr err = std::make_shared<Error>();
                err->setDescription("Unit referencing '" + node->attribute("units") + "' in units '" + units->name() + "' has an exponent with the value '" + attribute->value() + "' that is not a representation of a CellML real valued number.");
                err->setUnits(units);
                err->setRule(SpecificationRule::UNIT_EXPONENT);
                mParser->addError(err);
            }
        } else if (attribute->isType("multiplier")) {
            if (isCellMLReal(attribute->value())) {
                multiplier = convertToDouble(attribute->value());
            } else {
                // TODO his value won't be saved for validation later, so it does need to be reported now
                ErrorPtr err = std::make_shared<Error>();
                err->setDescription("Unit referencing '" + node->attribute("units") + "' in units '" + units->name() + "' has a multiplier with the value '" + attribute->value() + "' that is not a representation of a CellML real valued number.");
                err->setUnits(units);
                err->setRule(SpecificationRule::UNIT_MULTIPLIER);
                mParser->addError(err);
            }
        } else if (attribute->isType("id")) {
            id = attribute->value();
        } else {
            ErrorPtr err = std::make_shared<Error>();
            err->setDescription("Unit referencing '" + node->attribute("units") + "' in units '" + units->name() + "' has an invalid attribute '" + attribute->name() + "'.");
            err->setUnits(units);
            err->setRule(SpecificationRule::UNIT_OPTIONAL_ATTRIBUTE);
            mParser->addError(err);
        }
        attribute = attribute->next();
    }
    // Add this unit to the parent units.
    units->addUnit(reference, prefix, exponent, multiplier, id);
}

void Parser::ParserImpl::loadVariable(const VariablePtr &variable, const XmlNodePtr &node)
{
    // A variable should not have any children.
    XmlNodePtr childNode = node->firstChild();
    while (childNode) {
        if (childNode->isText()) {
            std::string textNode = childNode->convertToString();
            // Ignore whitespace when parsing.
            if (hasNonWhitespaceCharacters(textNode)) {
                ErrorPtr err = std::make_shared<Error>();
                err->setDescription("Variable '" + node->attribute("name") + "' has an invalid non-whitespace child text element '" + textNode + "'.");
                err->setVariable(variable);
                mParser->addError(err);
            }
        } else if (childNode->isComment()) {
            // Do nothing.
        } else {
            ErrorPtr err = std::make_shared<Error>();
            err->setDescription("Variable '" + node->attribute("name") + "' has an invalid child element '" + childNode->name() + "'.");
            err->setVariable(variable);
            mParser->addError(err);
        }
        childNode = childNode->next();
    }
    XmlAttributePtr attribute = node->firstAttribute();
    while (attribute) {
        if (attribute->isType("name")) {
            variable->setName(attribute->value());
        } else if (attribute->isType("id")) {
            variable->setId(attribute->value());
        } else if (attribute->isType("units")) {
            variable->setUnits(attribute->value());
        } else if (attribute->isType("interface")) {
            variable->setInterfaceType(attribute->value());
        } else if (attribute->isType("initial_value")) {
            variable->setInitialValue(attribute->value());
        } else {
            ErrorPtr err = std::make_shared<Error>();
            err->setDescription("Variable '" + node->attribute("name") + "' has an invalid attribute '" + attribute->name() + "'.");
            err->setVariable(variable);
            mParser->addError(err);
        }
        attribute = attribute->next();
    }
}

void Parser::ParserImpl::loadConnection(const ModelPtr &model, const XmlNodePtr &node)
{
    // Define types for variable and component pairs.
    using NamePair = std::pair<std::string, std::string>;
    using NamePairMap = std::vector<NamePair>;

    // Initialise name pairs and flags.
    NamePair componentNamePair;
    NamePair variableNamePair;
    NamePairMap variableNameMap;
    bool mapVariablesFound = false;
    bool component1Missing = false;
    bool component2Missing = false;
    bool variable1Missing = false;
    bool variable2Missing = false;

    // Check connection for component_{1, 2} attributes and get the name pair.
    std::string component1Name;
    std::string component2Name;
    std::string mappingId;
    std::string connectionId;
    XmlAttributePtr attribute = node->firstAttribute();
    while (attribute) {
        if (attribute->isType("component_1")) {
            component1Name = attribute->value();
        } else if (attribute->isType("component_2")) {
            component2Name = attribute->value();
        } else if (attribute->isType("id")) {
            connectionId = attribute->value();
        } else {
            ErrorPtr err = std::make_shared<Error>();
            err->setDescription("Connection in model '" + model->name() + "' has an invalid connection attribute '" + attribute->name() + "'.");
            err->setModel(model);
            err->setKind(Error::Kind::CONNECTION);
            mParser->addError(err);
        }
        attribute = attribute->next();
    }
    // Check that we found both components.
    if (component1Name.empty()) {
        ErrorPtr err = std::make_shared<Error>();
        err->setDescription("Connection in model '" + model->name() + "' does not have a valid component_1 in a connection element.");
        err->setModel(model);
        err->setKind(Error::Kind::CONNECTION);
        err->setRule(SpecificationRule::CONNECTION_COMPONENT1);
        mParser->addError(err);
        component1Missing = true;
    }
    if (component2Name.empty()) {
        ErrorPtr err = std::make_shared<Error>();
        err->setDescription("Connection in model '" + model->name() + "' does not have a valid component_2 in a connection element.");
        err->setModel(model);
        err->setKind(Error::Kind::CONNECTION);
        err->setRule(SpecificationRule::CONNECTION_COMPONENT2);
        mParser->addError(err);
        component2Missing = true;
    }
    componentNamePair = std::make_pair(component1Name, component2Name);

    XmlNodePtr childNode = node->firstChild();

    if (!childNode) {
        // TODO Should this be removed too?
        ErrorPtr err = std::make_shared<Error>();
        err->setDescription("Connection in model '" + model->name() + "' must contain one or more 'map_variables' elements.");
        err->setModel(model);
        err->setKind(Error::Kind::CONNECTION);
        err->setRule(SpecificationRule::CONNECTION_MAP_VARIABLES);
        mParser->addError(err);
        return;
    }

    // Iterate over connection child XML nodes.
    while (childNode) {
        // Connection map XML nodes should not have further children.
        XmlNodePtr grandchildNode = childNode->firstChild();
        while (grandchildNode) {
            if (grandchildNode->isText()) {
                std::string textNode = grandchildNode->convertToString();
                // Ignore whitespace when parsing.
                if (hasNonWhitespaceCharacters(textNode)) {
                    ErrorPtr err = std::make_shared<Error>();
                    err->setDescription("Connection in model '" + model->name() + "' has an invalid non-whitespace child text element '" + textNode + "'.");
                    err->setModel(model);
                    err->setKind(Error::Kind::CONNECTION);
                    mParser->addError(err);
                }
            } else if (grandchildNode->isComment()) {
                // Do nothing.
            } else {
                ErrorPtr err = std::make_shared<Error>();
                err->setDescription("Connection in model '" + model->name() + "' has an invalid child element '" + grandchildNode->name() + "' of element '" + childNode->name() + "'.");
                err->setModel(model);
                err->setKind(Error::Kind::CONNECTION);
                mParser->addError(err);
            }
            grandchildNode = grandchildNode->next();
        }

        if (childNode->isCellmlElement("map_variables")) {
            std::string variable1Name;
            std::string variable2Name;
            XmlAttributePtr childAttribute = childNode->firstAttribute();
            while (childAttribute) {
                if (childAttribute->isType("variable_1")) {
                    variable1Name = childAttribute->value();
                } else if (childAttribute->isType("variable_2")) {
                    variable2Name = childAttribute->value();
                } else if (childAttribute->isType("id")) {
                    mappingId = childAttribute->value();
                } else {
                    ErrorPtr err = std::make_shared<Error>();
                    err->setDescription("Connection in model '" + model->name() + "' has an invalid map_variables attribute '" + childAttribute->name() + "'.");
                    err->setModel(model);
                    err->setKind(Error::Kind::CONNECTION);
                    mParser->addError(err);
                }
                childAttribute = childAttribute->next();
            }
            // Check that we found both variables.
            if (variable1Name.empty()) {
                ErrorPtr err = std::make_shared<Error>();
                err->setDescription("Connection in model '" + model->name() + "' does not have a valid variable_1 in a map_variables element.");
                err->setModel(model);
                err->setKind(Error::Kind::CONNECTION);
                err->setRule(SpecificationRule::MAP_VARIABLES_VARIABLE1);
                mParser->addError(err);
                variable1Missing = true;
            }
            if (variable2Name.empty()) {
                ErrorPtr err = std::make_shared<Error>();
                err->setDescription("Connection in model '" + model->name() + "' does not have a valid variable_2 in a map_variables element.");
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

        } else if (childNode->isText()) {
            const std::string textNode = childNode->convertToString();
            // Ignore whitespace when parsing.
            if (hasNonWhitespaceCharacters(textNode)) {
                ErrorPtr err = std::make_shared<Error>();
                err->setDescription("Connection in model '" + model->name() + "' has an invalid non-whitespace child text element '" + textNode + "'.");
                err->setModel(model);
                err->setKind(Error::Kind::CONNECTION);
                mParser->addError(err);
            }
        } else if (childNode->isComment()) {
            // Do nothing.
        } else {
            ErrorPtr err = std::make_shared<Error>();
            err->setDescription("Connection in model '" + model->name() + "' has an invalid child element '" + childNode->name() + "'.");
            err->setModel(model);
            err->setKind(Error::Kind::CONNECTION);
            mParser->addError(err);
        }

        childNode = childNode->next();
    }

    // If we have a component name pair, check that the components exist in the model.
    ComponentPtr component1 = nullptr;
    ComponentPtr component2 = nullptr;
    // Now check the objects exist in the model. TODO Remove as is validation?
    if (model->containsComponent(componentNamePair.first)) {
        component1 = model->component(componentNamePair.first);
    } else {
        if (!component1Missing) {
            ErrorPtr err = std::make_shared<Error>();
            err->setDescription("Connection in model '" + model->name() + "' specifies '" + componentNamePair.first + "' as component_1 but it does not exist in the model.");
            err->setModel(model);
            err->setKind(Error::Kind::CONNECTION);
            err->setRule(SpecificationRule::CONNECTION_COMPONENT1);
            mParser->addError(err);
        }
    }
    if (model->containsComponent(componentNamePair.second)) {
        component2 = model->component(componentNamePair.second);
    } else {
        if (!component2Missing) {
            ErrorPtr err = std::make_shared<Error>();
            err->setDescription("Connection in model '" + model->name() + "' specifies '" + componentNamePair.second + "' as component_2 but it does not exist in the model.");
            err->setModel(model);
            err->setKind(Error::Kind::CONNECTION);
            err->setRule(SpecificationRule::CONNECTION_COMPONENT2);
            mParser->addError(err);
        }
    }

    // If we have a map_variables, check that the variables exist in the named components. TODO Remove as is validation?
    if (mapVariablesFound) {
        for (const auto &iterPair : variableNameMap) {
            VariablePtr variable1 = nullptr;
            VariablePtr variable2 = nullptr;
            if (component1) {
                if (component1->hasVariable(iterPair.first)) {
                    variable1 = component1->variable(iterPair.first);
                } else if (component1->isImport()) {
                    // With an imported component we assume this variable exists in the imported component.
                    variable1 = std::make_shared<Variable>();
                    variable1->setName(iterPair.first);
                    component1->addVariable(variable1);
                } else {
                    if (!variable1Missing) {
                        ErrorPtr err = std::make_shared<Error>();
                        err->setDescription("Variable '" + iterPair.first + "' is specified as variable_1 in a connection but it does not exist in component_1 component '" + component1->name() + "' of model '" + model->name() + "'.");
                        err->setComponent(component1);
                        err->setKind(Error::Kind::CONNECTION);
                        err->setRule(SpecificationRule::MAP_VARIABLES_VARIABLE1);
                        mParser->addError(err);
                    }
                }
            } else {
                ErrorPtr err = std::make_shared<Error>();
                err->setDescription("Connection in model '" + model->name() + "' specifies '" + iterPair.first + "' as variable_1 but the corresponding component_1 is invalid.");
                err->setModel(model);
                err->setKind(Error::Kind::CONNECTION);
                err->setRule(SpecificationRule::MAP_VARIABLES_VARIABLE1);
                mParser->addError(err);
            }
            if (component2) {
                if (component2->hasVariable(iterPair.second)) {
                    variable2 = component2->variable(iterPair.second);
                } else if (component2->isImport()) {
                    // With an imported component we assume this variable exists in the imported component.
                    variable2 = std::make_shared<Variable>();
                    variable2->setName(iterPair.second);
                    component2->addVariable(variable2);
                } else {
                    if (!variable2Missing) {
                        ErrorPtr err = std::make_shared<Error>();
                        err->setDescription("Variable '" + iterPair.second + "' is specified as variable_2 in a connection but it does not exist in component_2 component '" + component2->name() + "' of model '" + model->name() + "'.");
                        err->setComponent(component1);
                        err->setKind(Error::Kind::CONNECTION);
                        err->setRule(SpecificationRule::MAP_VARIABLES_VARIABLE2);
                        mParser->addError(err);
                    }
                }
            } else {
                ErrorPtr err = std::make_shared<Error>();
                err->setDescription("Connection in model '" + model->name() + "' specifies '" + iterPair.second + "' as variable_2 but the corresponding component_2 is invalid.");
                err->setModel(model);
                err->setKind(Error::Kind::CONNECTION);
                err->setRule(SpecificationRule::MAP_VARIABLES_VARIABLE2);
                mParser->addError(err);
            }
            // Set the variable equivalence relationship for this variable pair.
            if ((variable1) && (variable2)) {
                Variable::addEquivalence(variable1, variable2, mappingId, connectionId);
            }
        }
    } else {
        ErrorPtr err = std::make_shared<Error>();
        err->setDescription("Connection in model '" + model->name() + "' does not have a map_variables element.");
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
        std::string encapsulationId;
        if (parentComponentNode->isCellmlElement("component_ref")) {
            // Check for a component in the parent component_ref.
            XmlAttributePtr attribute = parentComponentNode->firstAttribute();
            while (attribute) {
                if (attribute->isType("component")) {
                    parentComponentName = attribute->value();
                    if (model->containsComponent(parentComponentName)) {
                        // Will re-add this to the model once we encapsulate the child(ren).
                        parentComponent = model->takeComponent(parentComponentName);
                    } else {
                        // TODO Should this be removed?
                        ErrorPtr err = std::make_shared<Error>();
                        err->setDescription("Encapsulation in model '" + model->name() + "' specifies '" + parentComponentName + "' as a component in a component_ref but it does not exist in the model.");
                        err->setModel(model);
                        err->setKind(Error::Kind::ENCAPSULATION);
                        err->setRule(SpecificationRule::COMPONENT_REF_COMPONENT_ATTRIBUTE);
                        mParser->addError(err);
                    }
                } else if (attribute->isType("id")) {
                    encapsulationId = attribute->value();
                } else {
                    ErrorPtr err = std::make_shared<Error>();
                    err->setDescription("Encapsulation in model '" + model->name() + "' has an invalid component_ref attribute '" + attribute->name() + "'.");
                    err->setModel(model);
                    err->setKind(Error::Kind::ENCAPSULATION);
                    err->setRule(SpecificationRule::COMPONENT_REF_COMPONENT_ATTRIBUTE);
                    mParser->addError(err);
                }
                attribute = attribute->next();
            }
            // TODO Should this be removed too?
            if ((!parentComponent) && (parentComponentName.empty())) {
                ErrorPtr err = std::make_shared<Error>();
                err->setDescription("Encapsulation in model '" + model->name() + "' does not have a valid component attribute in a component_ref element.");
                err->setModel(model);
                err->setKind(Error::Kind::ENCAPSULATION);
                err->setRule(SpecificationRule::COMPONENT_REF_COMPONENT_ATTRIBUTE);
                mParser->addError(err);
            } else if (parentComponent) {
                parentComponent->setEncapsulationId(encapsulationId);
            }
        } else if (parentComponentNode->isText()) {
            const std::string textNode = parentComponentNode->convertToString();
            // Ignore whitespace when parsing.
            if (hasNonWhitespaceCharacters(textNode)) {
                ErrorPtr err = std::make_shared<Error>();
                err->setDescription("Encapsulation in model '" + model->name() + "' has an invalid non-whitespace child text element '" + textNode + "'.");
                err->setModel(model);
                err->setKind(Error::Kind::ENCAPSULATION);
                err->setRule(SpecificationRule::COMPONENT_REF_CHILD);
                mParser->addError(err);
            } else {
                // Continue to next node if this is whitespace (don't try to parse children of whitespace).
                parentComponentNode = parentComponentNode->next();
                continue;
            }
        } else {
            ErrorPtr err = std::make_shared<Error>();
            err->setDescription("Encapsulation in model '" + model->name() + "' has an invalid child element '" + parentComponentNode->name() + "'.");
            err->setModel(model);
            err->setKind(Error::Kind::ENCAPSULATION);
            err->setRule(SpecificationRule::ENCAPSULATION_COMPONENT_REF);
            mParser->addError(err);
        }

        // Get first child of this parent component_ref.
        XmlNodePtr childComponentNode = parentComponentNode->firstChild();
        if (!childComponentNode) {
            XmlNodePtr grandParentComponentNode = parentComponentNode->parent();
            if (grandParentComponentNode->isCellmlElement("encapsulation")) {
                ErrorPtr err = std::make_shared<Error>();
                if (parentComponent) {
                    err->setDescription("Encapsulation in model '" + model->name() + "' specifies '" + parentComponent->name() + "' as a parent component_ref but it does not have any children.");
                } else {
                    err->setDescription("Encapsulation in model '" + model->name() + "' specifies an invalid parent component_ref that also does not have any children.");
                }
                err->setModel(model);
                err->setKind(Error::Kind::ENCAPSULATION);
                mParser->addError(err);
            }
        }

        // Loop over encapsulated children.
        std::string childEncapsulationId;
        while (childComponentNode) {
            ComponentPtr childComponent = nullptr;
            if (childComponentNode->isCellmlElement("component_ref")) {
                bool childComponentMissing = false;
                bool foundChildComponent = false;
                XmlAttributePtr attribute = childComponentNode->firstAttribute();
                while (attribute) {
                    if (attribute->isType("component")) {
                        const std::string childComponentName = attribute->value();
                        if (model->containsComponent(childComponentName)) {
                            childComponent = model->component(childComponentName);
                            foundChildComponent = true;
                        } else {
                            ErrorPtr err = std::make_shared<Error>();
                            err->setDescription("Encapsulation in model '" + model->name() + "' specifies '" + childComponentName + "' as a component in a component_ref but it does not exist in the model.");
                            err->setModel(model);
                            err->setKind(Error::Kind::ENCAPSULATION);
                            err->setRule(SpecificationRule::COMPONENT_REF_COMPONENT_ATTRIBUTE);
                            mParser->addError(err);
                            childComponentMissing = true;
                        }
                    } else if (attribute->isType("id")) {
                        childEncapsulationId = attribute->value();
                    } else {
                        ErrorPtr err = std::make_shared<Error>();
                        err->setDescription("Encapsulation in model '" + model->name() + "' has an invalid component_ref attribute '" + attribute->name() + "'.");
                        err->setModel(model);
                        err->setKind(Error::Kind::ENCAPSULATION);
                        mParser->addError(err);
                    }
                    attribute = attribute->next();
                }
                if ((!foundChildComponent) && (!childComponentMissing)) {
                    ErrorPtr err = std::make_shared<Error>();
                    if (parentComponent) {
                        err->setDescription("Encapsulation in model '" + model->name() + "' does not have a valid component attribute in a component_ref that is a child of '" + parentComponent->name() + "'.");
                    } else if (!parentComponentName.empty()) {
                        err->setDescription("Encapsulation in model '" + model->name() + "' does not have a valid component attribute in a component_ref that is a child of invalid parent component '" + parentComponentName + "'.");
                    } else {
                        err->setDescription("Encapsulation in model '" + model->name() + "' does not have a valid component attribute in a component_ref that is a child of an invalid parent component.");
                    }
                    err->setModel(model);
                    err->setKind(Error::Kind::ENCAPSULATION);
                    err->setRule(SpecificationRule::COMPONENT_REF_COMPONENT_ATTRIBUTE);
                    mParser->addError(err);
                }
                if (childComponent) {
                    childComponent->setEncapsulationId(childEncapsulationId);
                }
            } else if (childComponentNode->isText()) {
                const std::string textNode = childComponentNode->convertToString();
                // Ignore whitespace when parsing.
                if (hasNonWhitespaceCharacters(textNode)) {
                    ErrorPtr err = std::make_shared<Error>();
                    err->setDescription("Encapsulation in model '" + model->name() + "' has an invalid non-whitespace child text element '" + textNode + "'.");
                    err->setModel(model);
                    err->setKind(Error::Kind::ENCAPSULATION);
                    err->setRule(SpecificationRule::COMPONENT_REF_CHILD);
                    mParser->addError(err);
                }
            } else {
                ErrorPtr err = std::make_shared<Error>();
                err->setDescription("Encapsulation in model '" + model->name() + "' has an invalid child element '" + childComponentNode->name() + "'.");
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
            if (childComponentNode->firstChild()) {
                loadEncapsulation(model, childComponentNode);
            }
            if ((parentComponent) && (childComponent)) {
                // A child component is added through its parent component rather than the model,
                // so remove it if it exists.
                model->removeComponent(childComponent);
            }
            childComponentNode = childComponentNode->next();
        }

        // Re-add the parentComponent to the model with its child(ren) encapsulated.
        if (parentComponent) {
            model->addComponent(parentComponent);
        }
        // Get the next parent component at this level
        parentComponentNode = parentComponentNode->next();
    }
}

void Parser::ParserImpl::loadImport(const ImportSourcePtr &importSource, const ModelPtr &model, const XmlNodePtr &node)
{
    XmlAttributePtr attribute = node->firstAttribute();
    while (attribute) {
        if (attribute->isType("href", XLINK_NS)) {
            importSource->setUrl(attribute->value());
        } else if (attribute->isType("id")) {
            importSource->setId(attribute->value());
        } else if (attribute->inNamespaceUri(XLINK_NS)) {
            // Allow xlink attributes but do nothing for them.
        } else {
            ErrorPtr err = std::make_shared<Error>();
            err->setDescription("Import from '" + node->attribute("href") + "' has an invalid attribute '" + attribute->name() + "'.");
            err->setImportSource(importSource);
            mParser->addError(err);
        }
        attribute = attribute->next();
    }
    XmlNodePtr childNode = node->firstChild();
    while (childNode) {
        if (childNode->isCellmlElement("component")) {
            ComponentPtr importedComponent = std::make_shared<Component>();
            bool errorOccurred = false;
            XmlAttributePtr childAttribute = childNode->firstAttribute();
            while (childAttribute) {
                if (childAttribute->isType("name")) {
                    importedComponent->setName(childAttribute->value());
                } else if (childAttribute->isType("id")) {
                    importedComponent->setId(childAttribute->value());
                } else if (childAttribute->isType("component_ref")) {
                    importedComponent->setSourceComponent(importSource, childAttribute->value());
                } else {
                    ErrorPtr err = std::make_shared<Error>();
                    err->setDescription("Import of component '" + childNode->attribute("name") + "' from '" + node->attribute("href") + "' has an invalid attribute '" + childAttribute->name() + "'.");
                    err->setImportSource(importSource);
                    mParser->addError(err);
                    errorOccurred = true;
                }
                childAttribute = childAttribute->next();
            }
            if (!errorOccurred) {
                model->addComponent(importedComponent);
            }
        } else if (childNode->isCellmlElement("units")) {
            UnitsPtr importedUnits = std::make_shared<Units>();
            bool errorOccurred = false;
            XmlAttributePtr childAttribute = childNode->firstAttribute();
            while (childAttribute) {
                if (childAttribute->isType("name")) {
                    importedUnits->setName(childAttribute->value());
                } else if (childAttribute->isType("id")) {
                    importedUnits->setId(childAttribute->value());
                } else if (childAttribute->isType("units_ref")) {
                    importedUnits->setSourceUnits(importSource, childAttribute->value());
                } else {
                    ErrorPtr err = std::make_shared<Error>();
                    err->setDescription("Import of units '" + childNode->attribute("name") + "' from '" + node->attribute("href") + "' has an invalid attribute '" + childAttribute->name() + "'.");
                    err->setImportSource(importSource);
                    mParser->addError(err);
                    errorOccurred = true;
                }
                childAttribute = childAttribute->next();
            }
            if (!errorOccurred) {
                model->addUnits(importedUnits);
            }
        } else if (childNode->isText()) {
            const std::string textNode = childNode->convertToString();
            // Ignore whitespace when parsing.
            if (hasNonWhitespaceCharacters(textNode)) {
                ErrorPtr err = std::make_shared<Error>();
                err->setDescription("Import from '" + node->attribute("href") + "' has an invalid non-whitespace child text element '" + textNode + "'.");
                err->setImportSource(importSource);
                err->setRule(SpecificationRule::IMPORT_CHILD);
                mParser->addError(err);
            }
        } else if (childNode->isComment()) {
            // Do nothing.
        } else {
            ErrorPtr err = std::make_shared<Error>();
            err->setDescription("Import from '" + node->attribute("href") + "' has an invalid child element '" + childNode->name() + "'.");
            err->setImportSource(importSource);
            err->setRule(SpecificationRule::IMPORT_CHILD);
            mParser->addError(err);
        }
        childNode = childNode->next();
    }
}

void Parser::ParserImpl::loadReset(const ResetPtr &reset, const ComponentPtr &component, const XmlNodePtr &node)
{
    int order = 0;
    bool orderValid = false;
    VariablePtr referencedVariable = nullptr;
    VariablePtr testVariable = nullptr;
    std::string variableName;
    std::string testVariableName;

    XmlAttributePtr attribute = node->firstAttribute();
    while (attribute) {
        if (attribute->isType("variable")) {
            const std::string variableReference = attribute->value();
            referencedVariable = component->variable(variableReference);

            // TODO This follows the same pattern as the errors returned from parsing the encapsulations
            if (referencedVariable == nullptr) {
                ErrorPtr err = std::make_shared<Error>();
                err->setDescription("Reset referencing variable '" + variableReference + "' is not a valid reference for a variable in component '" + component->name() + "'.");
                err->setReset(reset);
                err->setRule(SpecificationRule::RESET_VARIABLE_REFERENCE);
                mParser->addError(err);
            } else {
                reset->setVariable(referencedVariable);
            }
        } else if (attribute->isType("test_variable")) {
            const std::string testVariableReference = attribute->value();
            testVariable = component->variable(testVariableReference);
            if (testVariable == nullptr) {
                // TODO This follows the same pattern as the errors returned from parsing the encapsulations
                ErrorPtr err = std::make_shared<Error>();
                err->setDescription("Reset referencing test_variable '" + testVariableReference + "' is not a valid reference for a variable in component '" + component->name() + "'.");
                err->setReset(reset);
                err->setRule(SpecificationRule::RESET_TEST_VARIABLE_REFERENCE);
                mParser->addError(err);
            } else {
                reset->setTestVariable(testVariable);
            }
        } else if (attribute->isType("order")) {
            orderValid = isCellMLInteger(attribute->value());
            if (orderValid) {
                order = convertToInt(attribute->value());
            } else { // TODO This value won't be saved for validation later, so it does need to be reported now
                if (reset->variable() != nullptr) {
                    variableName = reset->variable()->name();
                }
                ErrorPtr err = std::make_shared<Error>();
                err->setDescription("Reset in component '" + component->name() + "' referencing variable '" + variableName + "' has a non-integer order value '" + attribute->value() + "'.");
                err->setReset(reset);
                err->setRule(SpecificationRule::RESET_ORDER);
                mParser->addError(err);
            }
        } else if (attribute->isType("id")) {
            reset->setId(attribute->value());
        } else {
            ErrorPtr err = std::make_shared<Error>();
            err->setDescription("Reset in component '" + component->name() + "' has an invalid attribute '" + attribute->name() + "'.");
            err->setReset(reset);
            mParser->addError(err);
        }
        attribute = attribute->next();
    }

    if (reset->variable() != nullptr) {
        variableName = reset->variable()->name();
    }

    if (reset->testVariable() != nullptr) {
        testVariableName = reset->testVariable()->name();
    }

    if (orderValid) {
        reset->setOrder(order);
    }

    XmlNodePtr childNode = node->firstChild();
    int testValueCount = 0;
    int resetValueCount = 0;

    while (childNode) {
        if (childNode->isCellmlElement("test_value")) {
            XmlAttributePtr childAttribute = childNode->firstAttribute();
            while (childAttribute) {
                if (childAttribute->isType("id")) {
                    reset->setTestValueId(childAttribute->value());
                } else {
                    ErrorPtr err = std::make_shared<Error>();
                    err->setDescription("Reset in component '" + component->name() + "' referencing variable '" + variableName + "' and test_variable '" + testVariableName + "' has an unexpected attribute in the test_value block of '" + childAttribute->name() + "'.");
                    err->setReset(reset);
                    err->setRule(SpecificationRule::RESET_TEST_VALUE);
                    mParser->addError(err);
                }
                childAttribute = childAttribute->next();
            }

            if (testValueCount == 0) {
                XmlNodePtr mathNode = childNode->firstChild();
                while (mathNode) {
                    if (mathNode->isMathmlElement("math")) {
                        std::string math = mathNode->convertToString(true) + "\n";
                        reset->appendTestValue(math);
                        testValueCount++;
                    } else if (mathNode->isComment()) {
                        // Do nothing
                    } else {
                        std::string textNode = mathNode->convertToString();
                        // Ignore whitespace when parsing.
                        if (hasNonWhitespaceCharacters(textNode)) {
                            ErrorPtr err = std::make_shared<Error>();
                            err->setDescription("Reset in component '" + component->name() + "' referencing variable '" + variableName + "' and test_variable '" + testVariableName + "' has a non-whitespace test_value child. MathML block expected.");
                            err->setReset(reset);
                            err->setRule(SpecificationRule::RESET_TEST_VALUE);
                            mParser->addError(err);
                        }
                    }
                    mathNode = mathNode->next();
                }
            } else {
                testValueCount++;
            }

        } else if (childNode->isCellmlElement("reset_value")) {
            XmlAttributePtr childAttribute = childNode->firstAttribute();
            while (childAttribute) {
                if (childAttribute->isType("id")) {
                    reset->setResetValueId(childAttribute->value());
                } else {
                    ErrorPtr err = std::make_shared<Error>();
                    err->setDescription("Reset in component '" + component->name() + "' referencing variable '" + variableName + "' and test_variable '" + testVariableName + "' has an unexpected attribute in the reset_value block of '" + childAttribute->name() + "'.");
                    err->setReset(reset);
                    err->setRule(SpecificationRule::RESET_RESET_VALUE);
                    mParser->addError(err);
                }
                childAttribute = childAttribute->next();
            }

            if (resetValueCount == 0) {
                XmlNodePtr mathNode = childNode->firstChild();
                while (mathNode) {
                    if (mathNode->isMathmlElement("math")) {
                        std::string math = mathNode->convertToString(true) + "\n";
                        reset->appendResetValue(math);
                        resetValueCount++;
                    } else if (mathNode->isComment()) {
                        // Do nothing
                    } else {
                        std::string textNode = mathNode->convertToString();
                        // Ignore whitespace when parsing.
                        if (hasNonWhitespaceCharacters(textNode)) {
                            ErrorPtr err = std::make_shared<Error>();
                            err->setDescription("Reset in component '" + component->name() + "' referencing variable '" + variableName + "' and test_variable '" + testVariableName + "' has a non-whitespace reset_value child. MathML block expected.");
                            err->setReset(reset);
                            err->setRule(SpecificationRule::RESET_RESET_VALUE);
                            mParser->addError(err);
                        }
                    }
                    mathNode = mathNode->next();
                }
            } else {
                resetValueCount++;
            }
        } else if (childNode->isText()) {
            std::string textNode = childNode->convertToString();
            // Ignore whitespace when parsing.
            if (hasNonWhitespaceCharacters(textNode)) {
                ErrorPtr err = std::make_shared<Error>();
                err->setDescription("Reset has an invalid non-whitespace child text element '" + textNode + "'.  Expected either 'test_value' or 'reset_value' block.");
                err->setReset(reset);
                err->setRule(SpecificationRule::RESET_CHILD);
                mParser->addError(err);
            }
        } else if (childNode->isComment()) {
            // Do nothing.
        }
        childNode = childNode->next();
    }

    // TODO Not sure if these should be removed or not?
    if (testValueCount > 1) {
        ErrorPtr err = std::make_shared<Error>();
        err->setDescription("Reset in component '" + component->name() + "' referencing variable '"
                            + variableName + "' and test_variable '" + testVariableName + "' has multiple test_value blocks.");
        err->setReset(reset);
        err->setRule(SpecificationRule::RESET_TEST_VALUE);
        mParser->addError(err);
    } else if (testValueCount == 0) {
        ErrorPtr err = std::make_shared<Error>();
        err->setDescription("Reset in component '" + component->name() + "' referencing variable '"
                            + variableName + "' and test_variable '" + testVariableName + "' does not have a test_value block defined.");
        err->setReset(reset);
        err->setRule(SpecificationRule::RESET_TEST_VALUE);
        mParser->addError(err);
    }
    if (resetValueCount > 1) {
        ErrorPtr err = std::make_shared<Error>();
        err->setDescription("Reset in component '" + component->name() + "' referencing variable '"
                            + variableName + "' and test_variable '" + testVariableName + "' has multiple reset_value blocks.");
        err->setReset(reset);
        err->setRule(SpecificationRule::RESET_RESET_VALUE);
        mParser->addError(err);
    } else if (resetValueCount == 0) {
        ErrorPtr err = std::make_shared<Error>();
        err->setDescription("Reset in component '" + component->name() + "' referencing variable '"
                            + variableName + "' and test_variable '" + testVariableName + "' does not have a reset_value block defined.");
        err->setReset(reset);
        err->setRule(SpecificationRule::RESET_RESET_VALUE);
        mParser->addError(err);
    }
}

} // namespace libcellml

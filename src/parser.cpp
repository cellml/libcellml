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
#include "libcellml/when.h"

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

    /**
     * @brief Update the @p when with attributes parsed from the @p node.
     *
     * Update the @p when with attributes parsed from
     * the XML @p node. Existing attributes in @p when with names
     * matching those in @p node will be overwritten.
     *
     * @param when The @c WhenPtr to update.
     * @param reset The @c ResetPtr the when belongs to.
     * @param node The @c XmlNodePtr to parse and update the @p variable with.
     */
    void loadWhen(const WhenPtr &when, const ResetPtr &reset, const XmlNodePtr &node);
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
    }
    if (!node->isCellmlElement("model")) {
        ErrorPtr err = std::make_shared<Error>();
        if (node->getName() == "model") {
            std::string nodeNamespace = node->getNamespace();
            if (nodeNamespace.empty()) {
                nodeNamespace = "null";
            }
            err->setDescription("Model element is in invalid namespace '" + nodeNamespace + "'. A valid CellML root node should be in namespace '" + CELLML_2_0_NS + "'.");
        } else {
            err->setDescription("Model element is of invalid type '" + node->getName() + "'. A valid CellML root node should be of type 'model'.");
        }
        err->setModel(model);
        err->setRule(SpecificationRule::MODEL_ELEMENT);
        mParser->addError(err);
        return;
    }
    // Get model attributes.
    XmlAttributePtr attribute = node->getFirstAttribute();
    while (attribute) {
        /// @cellml2_4 4.2.1 Checks for presence of name attribute of model at load time
        if (attribute->isType("name")) {
            model->setName(attribute->getValue());		
        } else if (attribute->isType("id")) {
            model->setId(attribute->getValue());
        } else {
            ErrorPtr err = std::make_shared<Error>();
            err->setDescription("Model '" + node->getAttribute("name") + "' has an invalid attribute '" + attribute->getName() + "'.");
            err->setModel(model);
            mParser->addError(err);
        }
        attribute = attribute->getNext();
    }
    // Get model children (CellML entities).
    XmlNodePtr childNode = node->getFirstChild();
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
            if (childNode->getFirstAttribute()) {
                XmlAttributePtr childAttribute = childNode->getFirstAttribute();
                while (childAttribute) {
                    if (childAttribute->isType("id")) {
                        model->setEncapsulationId(childAttribute->getValue());
                    } else {
                        ErrorPtr err = std::make_shared<Error>();
                        err->setDescription("Encapsulation in model '" + model->getName() + "' has an invalid attribute '" + childAttribute->getName() + "'.");
                        err->setModel(model);
                        err->setKind(Error::Kind::ENCAPSULATION);
                        mParser->addError(err);
                    }
                    childAttribute = childAttribute->getNext();
                }
            }
            // Load encapsulated component_refs.
            XmlNodePtr componentRefNode = childNode->getFirstChild();
            if (componentRefNode) {
                // This component_ref and its child and sibling elements will be loaded
                // and error-checked in loadEncapsulation().
                encapsulationNodes.push_back(componentRefNode);
            } else {
                ErrorPtr err = std::make_shared<Error>();
                err->setDescription("Encapsulation in model '" + model->getName() + "' does not contain any child elements.");
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
                err->setDescription("Model '" + model->getName() + "' has an invalid non-whitespace child text element '" + textNode + "'.");
                err->setModel(model);
                err->setRule(SpecificationRule::MODEL_CHILD);
                mParser->addError(err);
            }
        } else if (childNode->isComment()) {
            // Do nothing.
        } else {
            ErrorPtr err = std::make_shared<Error>();
            err->setDescription("Model '" + model->getName() + "' has an invalid child element '" + childNode->getName() + "'.");
            err->setModel(model);
            err->setRule(SpecificationRule::MODEL_CHILD);
            mParser->addError(err);
        }
        childNode = childNode->getNext();
    }

    if (!encapsulationNodes.empty()) {
        loadEncapsulation(model, encapsulationNodes.at(0));
        if (encapsulationNodes.size() > 1) {
            /// @cellml2_4 4.2.3 Check for maximum of one encapsulation item per model at load time
            ErrorPtr err = std::make_shared<Error>();
            err->setDescription("Model '" + model->getName() + "' has more than one encapsulation element.");
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
    XmlAttributePtr attribute = node->getFirstAttribute();
    while (attribute) {
        /// @cellml2_10 10.1.1 Loads a component name
        if (attribute->isType("name")) {
            component->setName(attribute->getValue());
        } else if (attribute->isType("id")) {
        /// @cellml2_10 Loads a component id
            component->setId(attribute->getValue());
        } else {
            ErrorPtr err = std::make_shared<Error>();
            err->setDescription("Component '" + node->getAttribute("name") + "' has an invalid attribute '" + attribute->getName() + "'.");
            err->setComponent(component);
            mParser->addError(err);
        }
        attribute = attribute->getNext();
    }
    XmlNodePtr childNode = node->getFirstChild();
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
                err->setDescription("Component '" + component->getName() + "' has an invalid non-whitespace child text element '" + textNode + "'.");
                err->setComponent(component);
                err->setRule(SpecificationRule::COMPONENT_CHILD);
                mParser->addError(err);
            }
        } else if (childNode->isComment()) {
            // Do nothing.
        } else {
            ErrorPtr err = std::make_shared<Error>();
            err->setDescription("Component '" + component->getName() + "' has an invalid child element '" + childNode->getName() + "'.");
            err->setComponent(component);
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
            err->setDescription("Units '" + units->getName() + "' has an invalid attribute '" + attribute->getName() + "'.");
            err->setUnits(units);
            mParser->addError(err);
        }
        attribute = attribute->getNext();
    }
    XmlNodePtr childNode = node->getFirstChild();
    while (childNode) {
        if (childNode->isCellmlElement("unit")) {
            loadUnit(units, childNode);
        } else if (childNode->isText()) {
            std::string textNode = childNode->convertToString();
            // Ignore whitespace when parsing.
            if (hasNonWhitespaceCharacters(textNode)) {
                ErrorPtr err = std::make_shared<Error>();
                err->setDescription("Units '" + units->getName() + "' has an invalid non-whitespace child text element '" + textNode + "'.");
                err->setUnits(units);
                err->setRule(SpecificationRule::UNITS_CHILD);
                mParser->addError(err);
            }
        } else if (childNode->isComment()) {
            // Do nothing.
        } else {
            ErrorPtr err = std::make_shared<Error>();
            err->setDescription("Units '" + units->getName() + "' has an invalid child element '" + childNode->getName() + "'.");
            err->setUnits(units);
            err->setRule(SpecificationRule::UNITS_CHILD);
            mParser->addError(err);
        }
        childNode = childNode->getNext();
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
    XmlNodePtr childNode = node->getFirstChild();
    while (childNode) {
        if (childNode->isText()) {
            std::string textNode = childNode->convertToString();
            // Ignore whitespace when parsing.
            if (hasNonWhitespaceCharacters(textNode)) {
                ErrorPtr err = std::make_shared<Error>();
                err->setDescription("Unit referencing '" + node->getAttribute("units") + "' in units '" + units->getName() + "' has an invalid non-whitespace child text element '" + textNode + "'.");
                err->setUnits(units);
                mParser->addError(err);
            }
        } else if (childNode->isComment()) {
            // Do nothing.
        } else {
            ErrorPtr err = std::make_shared<Error>();
            err->setDescription("Unit referencing '" + node->getAttribute("units") + "' in units '" + units->getName() + "' has an invalid child element '" + childNode->getName() + "'.");
            err->setUnits(units);
            mParser->addError(err);
        }
        childNode = childNode->getNext();
    }
    // Parse the unit attributes.
    XmlAttributePtr attribute = node->getFirstAttribute();
    while (attribute) {
        if (attribute->isType("units")) {
            reference = attribute->getValue();
        } else if (attribute->isType("prefix")) {
            prefix = attribute->getValue();
        } else if (attribute->isType("exponent")) {
            /// @cellml2_9 9.1.2.3 Check the exponent is a real number string on load
            if (isCellMLReal(attribute->getValue())) {
                exponent = convertToDouble(attribute->getValue());
            } else {
                ErrorPtr err = std::make_shared<Error>();
                err->setDescription("Unit referencing '" + node->getAttribute("units") + "' in units '" + units->getName() + "' has an exponent with the value '" + attribute->getValue() + "' that is not a representation of a CellML real valued number.");
                err->setUnits(units);
                err->setRule(SpecificationRule::UNIT_EXPONENT);
                mParser->addError(err);
            }
        } else if (attribute->isType("multiplier")) {
            /// @cellml2_9 9.1.2.2 Check the multiplier is a real number string on load
            if (isCellMLReal(attribute->getValue())) {
                multiplier = convertToDouble(attribute->getValue());
            } else {
                ErrorPtr err = std::make_shared<Error>();
                err->setDescription("Unit referencing '" + node->getAttribute("units") + "' in units '" + units->getName() + "' has a multiplier with the value '" + attribute->getValue() + "' that is not a representation of a CellML real valued number.");
                err->setUnits(units);
                err->setRule(SpecificationRule::UNIT_MULTIPLIER);
                mParser->addError(err);
            }
        } else if (attribute->isType("id")) {
            id = attribute->getValue();
        } else {
            ErrorPtr err = std::make_shared<Error>();
            err->setDescription("Unit referencing '" + node->getAttribute("units") + "' in units '" + units->getName() + "' has an invalid attribute '" + attribute->getName() + "'.");
            err->setUnits(units);
            err->setRule(SpecificationRule::UNIT_OPTIONAL_ATTRIBUTE);
            mParser->addError(err);
        }
        attribute = attribute->getNext();
    }
    // Add this unit to the parent units.
    units->addUnit(reference, prefix, exponent, multiplier, id);
}

void Parser::ParserImpl::loadVariable(const VariablePtr &variable, const XmlNodePtr &node)
{
    // A variable should not have any children.
    XmlNodePtr childNode = node->getFirstChild();
    while (childNode) {
        if (childNode->isText()) {
            std::string textNode = childNode->convertToString();
            // Ignore whitespace when parsing.
            if (hasNonWhitespaceCharacters(textNode)) {
                ErrorPtr err = std::make_shared<Error>();
                err->setDescription("Variable '" + node->getAttribute("name") + "' has an invalid non-whitespace child text element '" + textNode + "'.");
                err->setVariable(variable);
                mParser->addError(err);
            }
        } else if (childNode->isComment()) {
            // Do nothing.
        } else {
            ErrorPtr err = std::make_shared<Error>();
            err->setDescription("Variable '" + node->getAttribute("name") + "' has an invalid child element '" + childNode->getName() + "'.");
            err->setVariable(variable);
            mParser->addError(err);
        }
        childNode = childNode->getNext();
    }
    XmlAttributePtr attribute = node->getFirstAttribute();
    bool unitsAttributePresent = false;
    bool nameAttributePresent = false;
    while (attribute) {
        if (attribute->isType("name")) {
            nameAttributePresent = true;
            variable->setName(attribute->getValue());
        } else if (attribute->isType("id")) {
            variable->setId(attribute->getValue());
        } else if (attribute->isType("units")) {
            unitsAttributePresent = true;
            variable->setUnits(attribute->getValue());
        } else if (attribute->isType("interface")) {
            variable->setInterfaceType(attribute->getValue());
        } else if (attribute->isType("initial_value")) {
            variable->setInitialValue(attribute->getValue());
        } else {
            ErrorPtr err = std::make_shared<Error>();
            err->setDescription("Variable '" + node->getAttribute("name") + "' has an invalid attribute '" + attribute->getName() + "'.");
            err->setVariable(variable);
            mParser->addError(err);
        }
        attribute = attribute->getNext();
    }
    if (!nameAttributePresent) {
        /// @cellml2_11 11.1.1.1 Checks for presence of variable name attribute at load time
        ErrorPtr err = std::make_shared<Error>(variable);
        err->setDescription("Variable '" + node->getAttribute("name") + "' is missing a required 'name' attribute.");
        err->setRule(SpecificationRule::VARIABLE_NAME);
        mParser->addError(err);
    }
    if (!unitsAttributePresent) {
        /// @cellml2_11 11.1.1.1 Checks for presence of variable units attribute at load time
        ErrorPtr err = std::make_shared<Error>(variable);
        err->setDescription("Variable '" + node->getAttribute("name") + "' is missing a required 'units' attribute.");
        err->setRule(SpecificationRule::VARIABLE_UNITS);
        mParser->addError(err);
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
    XmlAttributePtr attribute = node->getFirstAttribute();
    while (attribute) {
        if (attribute->isType("component_1")) {
            component1Name = attribute->getValue();
        } else if (attribute->isType("component_2")) {
            component2Name = attribute->getValue();
        } else if (attribute->isType("id")) {
            connectionId = attribute->getValue();
        } else {
            ErrorPtr err = std::make_shared<Error>();
            err->setDescription("Connection in model '" + model->getName() + "' has an invalid connection attribute '" + attribute->getName() + "'.");
            err->setModel(model);
            err->setKind(Error::Kind::CONNECTION);
            mParser->addError(err);
        }
        attribute = attribute->getNext();
    }
    // Check that we found both components.
    if (component1Name.empty()) {
        /// @cellml2_17 17.1.2 Checks that component_1 attribute is found at load time
        ErrorPtr err = std::make_shared<Error>();
        err->setDescription("Connection in model '" + model->getName() + "' does not have a valid component_1 in a connection element.");
        err->setModel(model);
        err->setKind(Error::Kind::CONNECTION);
        err->setRule(SpecificationRule::CONNECTION_COMPONENT1);
        mParser->addError(err);
        component1Missing = true;
    }
    if (component2Name.empty()) {
        /// @cellml2_17 17.1.2 Checks that component_2 attribute is found at load time
        ErrorPtr err = std::make_shared<Error>();
        err->setDescription("Connection in model '" + model->getName() + "' does not have a valid component_2 in a connection element.");
        err->setModel(model);
        err->setKind(Error::Kind::CONNECTION);
        err->setRule(SpecificationRule::CONNECTION_COMPONENT2);
        mParser->addError(err);
        component2Missing = true;
    }
    componentNamePair = std::make_pair(component1Name, component2Name);

    /// @cellml2_17 17.1.2 Check that component1 != component2 (removed, should be allowed in parser)
    //if ((!component1Missing)&&(!component2Missing)&&(component1Name == component2Name)) {
    //    ErrorPtr err = std::make_shared<Error>();
    //    err->setDescription("Connection in model '" + model->getName() +
    //                        "' specifies component_1 attribute '" + component1Name +
    //                        "' the same as component_2 attribute '" + component2Name + "'. "); 
    //    err->setModel(model);
    //    err->setKind(Error::Kind::CONNECTION);
    //    mParser->addError(err);
    //}

    XmlNodePtr childNode = node->getFirstChild();
    if (!childNode) {
        ErrorPtr err = std::make_shared<Error>();
        err->setDescription("Connection in model '" + model->getName() + "' must contain one or more 'map_variables' elements.");
        err->setModel(model);
        err->setKind(Error::Kind::CONNECTION);
        err->setRule(SpecificationRule::CONNECTION_MAP_VARIABLES);
        mParser->addError(err);
        return;
    }

    // Iterate over connection child XML nodes.
    while (childNode) {
        // Connection map XML nodes should not have further children.
        if (childNode->getFirstChild()) {
            XmlNodePtr grandchildNode = childNode->getFirstChild();
            if (grandchildNode->isText()) {
                std::string textNode = grandchildNode->convertToString();
                // Ignore whitespace when parsing.
                if (hasNonWhitespaceCharacters(textNode)) {
                    ErrorPtr err = std::make_shared<Error>();
                    err->setDescription("Connection in model '" + model->getName() + "' has an invalid non-whitespace child text element '" + textNode + "'.");
                    err->setModel(model);
                    err->setKind(Error::Kind::CONNECTION);
                    mParser->addError(err);
                }
            } else if (childNode->isComment()) {
                // Do nothing.
            } else {
                ErrorPtr err = std::make_shared<Error>();
                err->setDescription("Connection in model '" + model->getName() + "' has an invalid child element '" + grandchildNode->getName() + "' of element '" + childNode->getName() + "'.");
                err->setModel(model);
                err->setKind(Error::Kind::CONNECTION);
                mParser->addError(err);
            }
        }

        if (childNode->isCellmlElement("map_variables")) {
            /// @cellml2_17 17.1.4 map_variables type checked here before use
            std::string variable1Name = "";
            std::string variable2Name = "";
            XmlAttributePtr childAttribute = childNode->getFirstAttribute();
            while (childAttribute) {
                if (childAttribute->isType("variable_1")) {
                    variable1Name = childAttribute->getValue();
                } else if (childAttribute->isType("variable_2")) {
                    variable2Name = childAttribute->getValue();
                } else if (childAttribute->isType("id")) {
                    mappingId = childAttribute->getValue();
                } else {
                    ErrorPtr err = std::make_shared<Error>();
                    err->setDescription("Connection in model '" + model->getName() + "' has an invalid map_variables attribute '" + childAttribute->getName() + "'.");
                    err->setModel(model);
                    err->setKind(Error::Kind::CONNECTION);
                    mParser->addError(err);
                }
                childAttribute = childAttribute->getNext();
            }
            // Check that we found both variables.
            if (variable1Name.empty()) {
                /// @cellml2_18 18.1.1 Presence of variable_1 attribute checked, but value not validated here
                ErrorPtr err = std::make_shared<Error>();
                err->setDescription("Connection in model '" + model->getName() + "' does not have a valid variable_1 in a map_variables element.");
                err->setModel(model);
                err->setKind(Error::Kind::CONNECTION);
                err->setRule(SpecificationRule::MAP_VARIABLES_VARIABLE1);
                mParser->addError(err);
                variable1Missing = true;
            }
            if (variable2Name.empty()) {
                /// @cellml2_18 18.1.2 Presence of variable_2 attribute checked, but value not validated here
                ErrorPtr err = std::make_shared<Error>();
                err->setDescription("Connection in model '" + model->getName() + "' does not have a valid variable_2 in a map_variables element.");
                err->setModel(model);
                err->setKind(Error::Kind::CONNECTION);
                err->setRule(SpecificationRule::MAP_VARIABLES_VARIABLE2);
                mParser->addError(err);
                variable2Missing = true;
            }
            // We can have multiple map_variables per connection.
            /// @cellml2_18 18.1.3 Pair of variable1 and variable2 added to connection but not checked for duplicates
            variableNamePair = std::make_pair(variable1Name, variable2Name);
            variableNameMap.push_back(variableNamePair);
            mapVariablesFound = true;

        } else if (childNode->isText()) {
            const std::string textNode = childNode->convertToString();
            // Ignore whitespace when parsing.
            if (hasNonWhitespaceCharacters(textNode)) {
                ErrorPtr err = std::make_shared<Error>();
                err->setDescription("Connection in model '" + model->getName() + "' has an invalid non-whitespace child text element '" + textNode + "'.");
                err->setModel(model);
                err->setKind(Error::Kind::CONNECTION);
                mParser->addError(err);
            }
        } else if (childNode->isComment()) {
            // Do nothing.
        } else {
            ErrorPtr err = std::make_shared<Error>();
            err->setDescription("Connection in model '" + model->getName() + "' has an invalid child element '" + childNode->getName() + "'.");
            err->setModel(model);
            err->setKind(Error::Kind::CONNECTION);
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
            /// @cellml2_17 17.1.1 Checks that component_1 specification points to a valid component
            ErrorPtr err = std::make_shared<Error>();
            err->setDescription("Connection in model '" + model->getName() + "' specifies '" + componentNamePair.first + "' as component_1 but it does not exist in the model.");
            err->setModel(model);
            err->setKind(Error::Kind::CONNECTION);
            err->setRule(SpecificationRule::CONNECTION_COMPONENT1);
            mParser->addError(err);
        }
    }
    if (model->containsComponent(componentNamePair.second)) {
        component2 = model->getComponent(componentNamePair.second);
    } else {
        if (!component2Missing) {
            /// @cellml2_17 17.1.2 Checks that component_2 specification points to a valid component
            ErrorPtr err = std::make_shared<Error>();
            err->setDescription("Connection in model '" + model->getName() + "' specifies '" + componentNamePair.second + "' as component_2 but it does not exist in the model.");
            err->setModel(model);
            err->setKind(Error::Kind::CONNECTION);
            err->setRule(SpecificationRule::CONNECTION_COMPONENT2);
            mParser->addError(err);
        }
    }

    // If we have a map_variables, check that the variables exist in the named components.
    if (mapVariablesFound) {
        for (const auto &iterPair : variableNameMap) {
            VariablePtr variable1 = nullptr;
            VariablePtr variable2 = nullptr;
            if (component1) {
                if (component1->hasVariable(iterPair.first)) {
                    variable1 = component1->getVariable(iterPair.first);
                } else if (component1->isImport()) {
                    // With an imported component we assume this variable exists in the imported component.
                    variable1 = std::make_shared<Variable>();
                    variable1->setName(iterPair.first);
                    component1->addVariable(variable1);
                } else {
                    if (!variable1Missing) {
                        /// @cellml2_18 18.1.1 Checks that the variable_1 attribute points to a valid variable within component_1
                        ErrorPtr err = std::make_shared<Error>();
                        err->setDescription("Variable '" + iterPair.first + "' is specified as variable_1 in a connection but it does not exist in component_1 component '" + component1->getName() + "' of model '" + model->getName() + "'.");
                        err->setComponent(component1);
                        err->setKind(Error::Kind::CONNECTION);
                        err->setRule(SpecificationRule::MAP_VARIABLES_VARIABLE1);
                        mParser->addError(err);
                    }
                }
            } else {
                ErrorPtr err = std::make_shared<Error>();
                err->setDescription("Connection in model '" + model->getName() + "' specifies '" + iterPair.first + "' as variable_1 but the corresponding component_1 is invalid.");
                err->setModel(model);
                err->setKind(Error::Kind::CONNECTION);
                err->setRule(SpecificationRule::MAP_VARIABLES_VARIABLE1);
                mParser->addError(err);
            }
            if (component2) {
                if (component2->hasVariable(iterPair.second)) {
                    variable2 = component2->getVariable(iterPair.second);
                } else if (component2->isImport()) {
                    // With an imported component we assume this variable exists in the imported component.
                    variable2 = std::make_shared<Variable>();
                    variable2->setName(iterPair.second);
                    component2->addVariable(variable2);
                } else {
                    if (!variable2Missing) {
                        /// @cellml2_18 18.1.2 Checks that the variable_2 attribute points to a valid variable within component_2
                        ErrorPtr err = std::make_shared<Error>();
                        err->setDescription("Variable '" + iterPair.second + "' is specified as variable_2 in a connection but it does not exist in component_2 component '" + component2->getName() + "' of model '" + model->getName() + "'.");
                        err->setComponent(component1);
                        err->setKind(Error::Kind::CONNECTION);
                        err->setRule(SpecificationRule::MAP_VARIABLES_VARIABLE2);
                        mParser->addError(err);
                    }
                }
            } else {
                ErrorPtr err = std::make_shared<Error>();
                err->setDescription("Connection in model '" + model->getName() + "' specifies '" + iterPair.second + "' as variable_2 but the corresponding component_2 is invalid.");
                err->setModel(model);
                err->setKind(Error::Kind::CONNECTION);
                err->setRule(SpecificationRule::MAP_VARIABLES_VARIABLE2);
                mParser->addError(err);
            }
            // Set the variable equivalence relationship for this variable pair.
            /// @cellml2_18 18.1.3 Other than overwriting in the map (see void Variable::VariableImpl::setEquivalentMappingId(const VariablePtr &equivalentVariable, const std::string &id) 
            /// the condition for no duplicated mappings is not tested anywhere
            if ((variable1) && (variable2)) {
                Variable::addEquivalence(variable1, variable2, mappingId, connectionId);
            }
        }
    } else {
        /// @celllml2_17 17.1.4 Presence of at least one map_variables element within connection checked
        ErrorPtr err = std::make_shared<Error>();
        err->setDescription("Connection in model '" + model->getName() + "' does not have a map_variables element.");
        err->setModel(model);
        err->setKind(Error::Kind::CONNECTION);
        err->setRule(SpecificationRule::CONNECTION_MAP_VARIABLES);
        mParser->addError(err);
    }
    /// @cellml2_17 17.1.3 Need to check that this infoset does not contain this connection element (component_1 --- component_2) already
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
            XmlAttributePtr attribute = parentComponentNode->getFirstAttribute();
            while (attribute) {
                if (attribute->isType("component")) {
                    parentComponentName = attribute->getValue();
                    if (model->containsComponent(parentComponentName)) {
                        // Will re-add this to the model once we encapsulate the child(ren).
                        parentComponent = model->takeComponent(parentComponentName);
                    } else {
                        ///@cellml2_16 16.1.1 Checks that the component attribute of a component_ref matches a name in the model at load time
                        ErrorPtr err = std::make_shared<Error>();
                        err->setDescription("Encapsulation in model '" + model->getName() + "' specifies '" + parentComponentName + "' as a component in a component_ref but it does not exist in the model.");
                        err->setModel(model);
                        err->setKind(Error::Kind::ENCAPSULATION);
                        err->setRule(SpecificationRule::COMPONENT_REF_COMPONENT_ATTRIBUTE);
                        mParser->addError(err);
                    }
                } else if (attribute->isType("id")) {
                    encapsulationId = attribute->getValue();
                } else {
                    ErrorPtr err = std::make_shared<Error>();
                    err->setDescription("Encapsulation in model '" + model->getName() + "' has an invalid component_ref attribute '" + attribute->getName() + "'.");
                    err->setModel(model);
                    err->setKind(Error::Kind::ENCAPSULATION);
                    err->setRule(SpecificationRule::COMPONENT_REF_COMPONENT_ATTRIBUTE);
                    mParser->addError(err);
                }
                attribute = attribute->getNext();
            }
            if ((!parentComponent) && (parentComponentName.empty())) {
                /// @cellml2_15 15.1.1 Checks for non-empty encapsulation at load time
                ErrorPtr err = std::make_shared<Error>();
                err->setDescription("Encapsulation in model '" + model->getName() + "' does not have a valid component attribute in a component_ref element.");
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
                err->setDescription("Encapsulation in model '" + model->getName() + "' has an invalid non-whitespace child text element '" + textNode + "'.");
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
            err->setDescription("Encapsulation in model '" + model->getName() + "' has an invalid child element '" + parentComponentNode->getName() + "'.");
            err->setModel(model);
            err->setKind(Error::Kind::ENCAPSULATION);
            err->setRule(SpecificationRule::ENCAPSULATION_COMPONENT_REF);
            mParser->addError(err);
        }

        // Get first child of this parent component_ref.
        XmlNodePtr childComponentNode = parentComponentNode->getFirstChild();
        if (!childComponentNode) {
            XmlNodePtr grandParentComponentNode = parentComponentNode->getParent();
            if (grandParentComponentNode->isCellmlElement("encapsulation")) {
                ErrorPtr err = std::make_shared<Error>();
                if (parentComponent) {
                    err->setDescription("Encapsulation in model '" + model->getName() + "' specifies '" + parentComponent->getName() + "' as a parent component_ref but it does not have any children.");
                } else {
                    err->setDescription("Encapsulation in model '" + model->getName() + "' specifies an invalid parent component_ref that also does not have any children.");
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
                XmlAttributePtr attribute = childComponentNode->getFirstAttribute();
                while (attribute) {
                    if (attribute->isType("component")) {
                        const std::string childComponentName = attribute->getValue();
                        if (model->containsComponent(childComponentName)) {
                            childComponent = model->getComponent(childComponentName);
                            foundChildComponent = true;
                        } else {
                            ErrorPtr err = std::make_shared<Error>();
                            err->setDescription("Encapsulation in model '" + model->getName() + "' specifies '" + childComponentName + "' as a component in a component_ref but it does not exist in the model.");
                            err->setModel(model);
                            err->setKind(Error::Kind::ENCAPSULATION);
                            err->setRule(SpecificationRule::COMPONENT_REF_COMPONENT_ATTRIBUTE);
                            mParser->addError(err);
                            childComponentMissing = true;
                        }
                    } else if (attribute->isType("id")) {
                        childEncapsulationId = attribute->getValue();
                    } else {
                        ErrorPtr err = std::make_shared<Error>();
                        err->setDescription("Encapsulation in model '" + model->getName() + "' has an invalid component_ref attribute '" + attribute->getName() + "'.");
                        err->setModel(model);
                        err->setKind(Error::Kind::ENCAPSULATION);
                        mParser->addError(err);
                    }
                    attribute = attribute->getNext();
                }
                if ((!foundChildComponent) && (!childComponentMissing)) {
                    ErrorPtr err = std::make_shared<Error>();
                    if (parentComponent) {
                        err->setDescription("Encapsulation in model '" + model->getName() + "' does not have a valid component attribute in a component_ref that is a child of '" + parentComponent->getName() + "'.");
                    } else if (!parentComponentName.empty()) {
                        err->setDescription("Encapsulation in model '" + model->getName() + "' does not have a valid component attribute in a component_ref that is a child of invalid parent component '" + parentComponentName + "'.");
                    } else {
                        err->setDescription("Encapsulation in model '" + model->getName() + "' does not have a valid component attribute in a component_ref that is a child of an invalid parent component.");
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
                    err->setDescription("Encapsulation in model '" + model->getName() + "' has an invalid non-whitespace child text element '" + textNode + "'.");
                    err->setModel(model);
                    err->setKind(Error::Kind::ENCAPSULATION);
                    err->setRule(SpecificationRule::COMPONENT_REF_CHILD);
                    mParser->addError(err);
                }
            } else {
                ErrorPtr err = std::make_shared<Error>();
                err->setDescription("Encapsulation in model '" + model->getName() + "' has an invalid child element '" + childComponentNode->getName() + "'.");
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
        if (attribute->isType("href", XLINK_NS)) {
            importSource->setUrl(attribute->getValue());
        } else if (attribute->isType("id")) {
            importSource->setId(attribute->getValue());
        } else if (attribute->isType("xlink")) {
            /// @cellml2_5 NB Skips loading 'xlink' attributes, no warning raised
            // Allow xlink attributes but do nothing for them.
        } else {
            ErrorPtr err = std::make_shared<Error>();
            err->setDescription("Import from '" + node->getAttribute("href") + "' has an invalid attribute '" + attribute->getName() + "'.");
            err->setImportSource(importSource);
            mParser->addError(err);
        }
        attribute = attribute->getNext();
    }

    XmlNodePtr childNode = node->getFirstChild();
    /// @cellml2_5 5.2.1-2 PARSER Checks importchildren are "component" or "units" only
    while (childNode) {
        if (childNode->isCellmlElement("component")) {
            ComponentPtr importedComponent = std::make_shared<Component>();
            bool errorOccurred = false;
            XmlAttributePtr childAttribute = childNode->getFirstAttribute();
            while (childAttribute) {
                if (childAttribute->isType("name")) {
                    importedComponent->setName(childAttribute->getValue());
                } else if (childAttribute->isType("id")) {
                    importedComponent->setId(childAttribute->getValue());
                } else if (childAttribute->isType("component_ref")) {
                    importedComponent->setSourceComponent(importSource, childAttribute->getValue());
                } else {
                    ErrorPtr err = std::make_shared<Error>();
                    err->setDescription("Import of component '" + childNode->getAttribute("name") + "' from '" + node->getAttribute("href") + "' has an invalid attribute '" + childAttribute->getName() + "'.");
                    err->setImportSource(importSource);
                    mParser->addError(err);
                    errorOccurred = true;
                }
                childAttribute = childAttribute->getNext();
            }
            if (!errorOccurred) {
                model->addComponent(importedComponent);
            }
        } else if (childNode->isCellmlElement("units")) {
            UnitsPtr importedUnits = std::make_shared<Units>();
            bool errorOccurred = false;
            XmlAttributePtr childAttribute = childNode->getFirstAttribute();
            while (childAttribute) {
                if (childAttribute->isType("name")) {
                    importedUnits->setName(childAttribute->getValue());
                } else if (childAttribute->isType("id")) {
                    importedUnits->setId(childAttribute->getValue());
                } else if (childAttribute->isType("units_ref")) {
                    importedUnits->setSourceUnits(importSource, childAttribute->getValue());
                } else {
                    ErrorPtr err = std::make_shared<Error>();
                    err->setDescription("Import of units '" + childNode->getAttribute("name") + "' from '" + node->getAttribute("href") + "' has an invalid attribute '" + childAttribute->getName() + "'.");
                    err->setImportSource(importSource);
                    mParser->addError(err);
                    errorOccurred = true;
                }
                childAttribute = childAttribute->getNext();
            }
            if (!errorOccurred) {
                model->addUnits(importedUnits);
            }
        } else if (childNode->isText()) {
            const std::string textNode = childNode->convertToString();
            // Ignore whitespace when parsing.
            if (hasNonWhitespaceCharacters(textNode)) {
                ErrorPtr err = std::make_shared<Error>();
                err->setDescription("Import from '" + node->getAttribute("href") + "' has an invalid non-whitespace child text element '" + textNode + "'.");
                err->setImportSource(importSource);
                err->setRule(SpecificationRule::IMPORT_CHILD);
                mParser->addError(err);
            }
        } else if (childNode->isComment()) {
            // Do nothing.
        } else {
            ErrorPtr err = std::make_shared<Error>();
            err->setDescription("Import from '" + node->getAttribute("href") + "' has an invalid child element '" + childNode->getName() + "'.");
            err->setImportSource(importSource);
            err->setRule(SpecificationRule::IMPORT_CHILD);
            mParser->addError(err);
        }
        childNode = childNode->getNext();
    }
}

void Parser::ParserImpl::loadReset(const ResetPtr &reset, const ComponentPtr &component, const XmlNodePtr &node)
{
    int order = 0;
    bool orderDefined = false;
    bool orderValid = false;
    VariablePtr referencedVariable = nullptr;
    std::string variableName;

    XmlAttributePtr attribute = node->getFirstAttribute();
    while (attribute) {
        if (attribute->isType("variable")) {
            const std::string variableReference = attribute->getValue();
            referencedVariable = component->getVariable(variableReference);
            /// @cellml2_12 12.1.1.1 Checks that reset has a valid varaible attribute at load time
            if (referencedVariable == nullptr) {
                ErrorPtr err = std::make_shared<Error>();
                err->setDescription("Reset referencing variable '" + variableReference + "' is not a valid reference for a variable in component '" + component->getName() + "'.");
                err->setReset(reset);
                err->setRule(SpecificationRule::RESET_VARIABLE_REFERENCE);
                mParser->addError(err);
            } else {
                reset->setVariable(referencedVariable);
            }
        } else if (attribute->isType("order")) {
            orderDefined = true;
            /// @cellml2_12 12.1.1.2 Checks that the order value is an integer at load time.
            /// __NB__ Does *not* check for duplicate order values here, and allows negative numbers??
            orderValid = isCellMLInteger(attribute->getValue());
            if (orderValid) {
                order = convertToInt(attribute->getValue());
            } else {
                if (reset->getVariable() != nullptr) {
                    variableName = reset->getVariable()->getName();
                }
                ErrorPtr err = std::make_shared<Error>();
                err->setDescription("Reset in component '" + component->getName() + "' referencing variable '" + variableName + "' has a non-integer order value '" + attribute->getValue() + "'.");
                err->setReset(reset);
                err->setRule(SpecificationRule::RESET_ORDER);
                mParser->addError(err);
            }
        } else if (attribute->isType("id")) {
            reset->setId(attribute->getValue());
        } else {
            ErrorPtr err = std::make_shared<Error>();
            err->setDescription("Reset in component '" + component->getName() + "' has an invalid attribute '" + attribute->getName() + "'.");
            err->setReset(reset);
            mParser->addError(err);
        }
        attribute = attribute->getNext();
    }

    if (referencedVariable == nullptr) {
        ErrorPtr err = std::make_shared<Error>();
        err->setDescription("Reset in component '" + component->getName() + "' does not reference a variable in the component.");
        err->setReset(reset);
        err->setRule(SpecificationRule::RESET_VARIABLE_REFERENCE);
        mParser->addError(err);
    }

    if (reset->getVariable() != nullptr) {
        variableName = reset->getVariable()->getName();
    }
    /// @cellml2_12 12.1.1.2 Checks that an order value is present at load time (but does not check it's 
    /// valid as an order, only as an int)
    if (orderValid) {
        reset->setOrder(order);
    } else if (!orderDefined) {
        ErrorPtr err = std::make_shared<Error>();
        err->setDescription("Reset in component '" + component->getName() + "' referencing variable '" + variableName + "' does not have an order defined.");
        err->setReset(reset);
        err->setRule(SpecificationRule::RESET_ORDER);
        mParser->addError(err);
    }

    XmlNodePtr childNode = node->getFirstChild();
    while (childNode) {
        if (childNode->isCellmlElement("when")) {
            WhenPtr when = std::make_shared<When>();
            loadWhen(when, reset, childNode);
            reset->addWhen(when);
        } else if (childNode->isText()) {
            const std::string textNode = childNode->convertToString();
            // Ignore whitespace when parsing.
            if (hasNonWhitespaceCharacters(textNode)) {
                ErrorPtr err = std::make_shared<Error>();
                err->setDescription("Reset in component '" + component->getName() + "' referencing variable '" + variableName + "' has an invalid non-whitespace child text element '" + textNode + "'.");
                err->setReset(reset);
                err->setRule(SpecificationRule::RESET_CHILD);
                mParser->addError(err);
            }
        } else if (childNode->isComment()) {
            // Do nothing.
        } else {
            ErrorPtr err = std::make_shared<Error>();
            err->setDescription("Reset in component '" + component->getName() + "' referencing variable '" + variableName + "' has an invalid child element '" + childNode->getName() + "'.");
            err->setReset(reset);
            err->setRule(SpecificationRule::RESET_CHILD);
            mParser->addError(err);
        }
        childNode = childNode->getNext();
    }
}

void Parser::ParserImpl::loadWhen(const WhenPtr &when, const ResetPtr &reset, const XmlNodePtr &node)
{
    std::string referencedVariableName;
    VariablePtr referencedVariable = reset->getVariable();
    if (referencedVariable != nullptr) {
        referencedVariableName = referencedVariable->getName();
    }
    std::string resetOrder;
    if (reset->isOrderSet()) {
        resetOrder = convertIntToString(reset->getOrder());
    }
    int order = 0;
    bool orderDefined = false;
    bool orderValid = false;
    XmlAttributePtr attribute = node->getFirstAttribute();
    while (attribute) {
        if (attribute->isType("order")) {
            orderValid = isCellMLInteger(attribute->getValue());
            /// @cellml2_13 13.1.1 Checks that this when has an order attribute which is an integer at 
            /// load time.
            if (orderValid) {
                order = convertToInt(attribute->getValue());
            }
        } else if (attribute->isType("id")) {
            when->setId(attribute->getValue());
        } else {
            ErrorPtr err = std::make_shared<Error>();
            err->setDescription("When in reset referencing variable '" + referencedVariableName + "' with order '" + resetOrder + "' has an invalid attribute '" + attribute->getName() + "'.");
            err->setWhen(when);
            mParser->addError(err);
        }
        attribute = attribute->getNext();
    }

    if (orderValid) {
        when->setOrder(order);
    } else if (!orderDefined) {
        ErrorPtr err = std::make_shared<Error>();
        err->setDescription("When in reset referencing variable '" + referencedVariableName + "' with order '" + resetOrder + "' does not have an order defined.");
        err->setWhen(when);
        err->setRule(SpecificationRule::WHEN_ORDER);
        mParser->addError(err);
    }

    size_t mathNodeCount = 0;
    XmlNodePtr childNode = node->getFirstChild();
    while (childNode) {
        if (childNode->isMathmlElement("math")) {
            // TODO: copy any namespaces declared in parents into the math element
            //       so math is a valid subdocument.
            std::string math = childNode->convertToString(true) + "\n";
            ++mathNodeCount;
            if (mathNodeCount == 1) {
                when->setCondition(math);	// first one read defines the MathML condition
            } else if (mathNodeCount == 2) {
                when->setValue(math);		// second one read defines the MathML expression to be evaluated
            } else {
                ErrorPtr err = std::make_shared<Error>();
                err->setDescription("When in reset referencing variable '" + referencedVariableName + "' with order '" + resetOrder + "' contains more than two MathML child elements.");
                err->setWhen(when);
                err->setRule(SpecificationRule::WHEN_CHILD);
                mParser->addError(err);
            }
        } else if (childNode->isText()) {
            const std::string textNode = childNode->convertToString();
            // Ignore whitespace when parsing.
            if (hasNonWhitespaceCharacters(textNode)) {
                ErrorPtr err = std::make_shared<Error>();
                err->setDescription("When in reset referencing variable '" + referencedVariableName + "' with order '" + resetOrder + "' has an invalid non-whitespace child text element '" + textNode + "'.");
                err->setWhen(when);
                err->setRule(SpecificationRule::WHEN_CHILD);
                mParser->addError(err);
            }
        } else if (childNode->isComment()) {
            // Do nothing.
        } else {
            ErrorPtr err = std::make_shared<Error>();
            err->setDescription("When in reset referencing variable '" + referencedVariableName + "' with order '" + resetOrder + "' has an invalid child element '" + childNode->getName() + "'.");
            err->setWhen(when);
            err->setRule(SpecificationRule::WHEN_CHILD);
            mParser->addError(err);
        }
        childNode = childNode->getNext();
    }

    if (mathNodeCount == 0 || mathNodeCount == 1) {
        std::string mathNodeCountString = "zero";
        std::string plural = "s";
        if (mathNodeCount == 1) {
            mathNodeCountString = "only one";
            plural = "";
        }
        ErrorPtr err = std::make_shared<Error>();
        err->setDescription("When in reset referencing variable '" + referencedVariableName + "' with order '" + resetOrder + "' contains " + mathNodeCountString + " MathML child element" + plural + ".");
        err->setWhen(when);
        mParser->addError(err);
    }
}

} // namespace libcellml

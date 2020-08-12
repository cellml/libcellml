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

#include <algorithm>
#include <limits>
#include <sstream>
#include <string>
#include <vector>

#include "libcellml/component.h"
#include "libcellml/importsource.h"
#include "libcellml/issue.h"
#include "libcellml/model.h"
#include "libcellml/reset.h"
#include "libcellml/variable.h"

#include "namespaces.h"
#include "utilities.h"
#include "xmldoc.h"
#include "xmlutils.h"

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
    void loadComponent(const ComponentPtr &component, const XmlNodePtr &node) const;

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
    void loadConnection(const ModelPtr &model, const XmlNodePtr &node) const;

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
     * @brief Recursively update the @p model with the encapsulation parsed from the @p node.
     *
     * Recusively parse through the @p node to create the component hierarchy.  Returns the
     * root component of the hierarchy to the calling method.
     *
     * @param model The @c ModelPtr to update.
     * @param nodee The @c XmlNodePtr to parse and update the model with.
     * @return A @c ComponentPtr which is the root of the component hierarchy.
     */
    ComponentPtr loadComponentRef(const ModelPtr &model, const XmlNodePtr &node);

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
    void loadImport(ImportSourcePtr &importSource, const ModelPtr &model, const XmlNodePtr &node) const;

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
    void loadUnits(const UnitsPtr &units, const XmlNodePtr &node) const;

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
    void loadUnit(const UnitsPtr &units, const XmlNodePtr &node) const;

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
    void loadVariable(const VariablePtr &variable, const XmlNodePtr &node) const;

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
    void loadReset(const ResetPtr &reset, const ComponentPtr &component, const XmlNodePtr &node) const;

    /**
     * @brief Update the @p reset with the child parsed from the @p node.
     *
     * Takes either a 'test_value' node or a 'reset_value' node that is
     * a child of a @c Reset.  Updates the @p reset with the information in the
     * @p node.
     *
     * @param childType The @c std::string type of child which is either 'test_value' or 'reset_value'.
     * @param reset The @c ResetPtr to update.
     * @param component The @c ComponentPtr the reset belongs to.
     * @param node The @c XmlNodePtr to parse and update the @p variable with.
     */
    void loadResetChild(const std::string &childType, const ResetPtr &reset, const ComponentPtr &component, const XmlNodePtr &node) const;

    /**
     * @brief Checks the multiplicity of the @p childType.
     *
     * Checks to determine if the @p childType has the correct number of entries
     * for a @c Reset.  Adds an issue to the @c Parser if the @p count is not correct
     * for the @p childType.
     *
     * @param count The number of children of the type defined by @p childType.
     * @param childType The @c std::string type of child which is either 'test_value' or 'reset_value'.
     * @param reset The @c ResetPtr to update.
     * @param component The @c ComponentPtr the reset belongs to.
     */
    void checkResetChildMultiplicity(size_t count, const std::string &childType, const ResetPtr &reset, const ComponentPtr &component) const;
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

ParserPtr Parser::create() noexcept
{
    return std::shared_ptr<Parser> {new Parser {}};
}

ModelPtr Parser::parseModel(const std::string &input)
{
    removeAllIssues();
    ModelPtr model = Model::create();
    if (input.empty()) {
        IssuePtr issue = Issue::create();
        issue->setDescription("Model string is empty.");
        issue->setCause(Issue::Cause::XML);
        issue->setModel(model);
        addIssue(issue);
    } else {
        mPimpl->updateModel(model, input);
    }
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
    // Copy any XML parsing issues into the common parser issue handler.
    if (doc->xmlErrorCount() > 0) {
        for (size_t i = 0; i < doc->xmlErrorCount(); ++i) {
            IssuePtr issue = Issue::create();
            issue->setDescription("LibXml2 error: " + doc->xmlError(i));
            issue->setCause(Issue::Cause::XML);
            mParser->addIssue(issue);
        }
    }
    const XmlNodePtr node = doc->rootNode();
    if (!node) {
        IssuePtr issue = Issue::create();
        issue->setDescription("Could not get a valid XML root node from the provided input.");
        issue->setCause(Issue::Cause::XML);
        mParser->addIssue(issue);
        return;
    }
    if (!node->isCellmlElement("model")) {
        IssuePtr issue = Issue::create();
        if (node->name() == "model") {
            std::string nodeNamespace = node->namespaceUri();
            if (nodeNamespace.empty()) {
                nodeNamespace = "null";
            }
            issue->setDescription("Model element is in invalid namespace '" + nodeNamespace + "'. A valid CellML root node should be in namespace '" + CELLML_2_0_NS + "'.");
        } else {
            issue->setDescription("Model element is of invalid type '" + node->name() + "'. A valid CellML root node should be of type 'model'.");
        }
        issue->setModel(model);
        issue->setReferenceRule(Issue::ReferenceRule::MODEL_ELEMENT);
        mParser->addIssue(issue);
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
            IssuePtr issue = Issue::create();
            issue->setDescription("Model '" + node->attribute("name") + "' has an invalid attribute '" + attribute->name() + "'.");
            issue->setModel(model);
            mParser->addIssue(issue);
        }
        attribute = attribute->next();
    }
    // Get model children (CellML entities).
    XmlNodePtr childNode = node->firstChild();
    std::vector<XmlNodePtr> connectionNodes;
    std::vector<XmlNodePtr> encapsulationNodes;
    while (childNode) {
        if (childNode->isCellmlElement("component")) {
            const std::string name;
            ComponentPtr component = Component::create(name);
            loadComponent(component, childNode);
            model->addComponent(component);
        } else if (childNode->isCellmlElement("units")) {
            UnitsPtr units = Units::create();
            loadUnits(units, childNode);
            model->addUnits(units);
        } else if (childNode->isCellmlElement("import")) {
            ImportSourcePtr importSource = ImportSource::create();
            loadImport(importSource, model, childNode);
            model->addImportSource(importSource);
        } else if (childNode->isCellmlElement("encapsulation")) {
            // An encapsulation should not have attributes other than an 'id' attribute.
            if (childNode->firstAttribute()) {
                XmlAttributePtr childAttribute = childNode->firstAttribute();
                while (childAttribute) {
                    if (childAttribute->isType("id")) {
                        model->setEncapsulationId(childAttribute->value());
                    } else {
                        IssuePtr issue = Issue::create();
                        issue->setDescription("Encapsulation in model '" + model->name() + "' has an invalid attribute '" + childAttribute->name() + "'.");
                        issue->setModel(model);
                        issue->setCause(Issue::Cause::ENCAPSULATION);
                        mParser->addIssue(issue);
                    }
                    childAttribute = childAttribute->next();
                }
            }
            // Load encapsulated component_refs.
            XmlNodePtr componentRefNode = childNode->firstChild();
            if (componentRefNode) {
                // This component_ref and its child and sibling elements will be loaded
                // and issue-checked in loadEncapsulation().
                encapsulationNodes.push_back(componentRefNode);
            } else {
                // Empty encapsulations are valid, but may not be intended.
                IssuePtr issue = Issue::create();
                issue->setDescription("Encapsulation in model '" + model->name() + "' does not contain any child elements.");
                issue->setModel(model);
                issue->setCause(Issue::Cause::ENCAPSULATION);
                issue->setReferenceRule(Issue::ReferenceRule::ENCAPSULATION_CHILD);
                issue->setLevel(libcellml::Issue::Level::WARNING);
                mParser->addIssue(issue);
            }
        } else if (childNode->isCellmlElement("connection")) {
            connectionNodes.push_back(childNode);
        } else if (childNode->isText()) {
            std::string textNode = childNode->convertToString();
            // Ignore whitespace when parsing.
            if (hasNonWhitespaceCharacters(textNode)) {
                IssuePtr issue = Issue::create();
                issue->setDescription("Model '" + model->name() + "' has an invalid non-whitespace child text element '" + textNode + "'.");
                issue->setModel(model);
                issue->setReferenceRule(Issue::ReferenceRule::MODEL_CHILD);
                mParser->addIssue(issue);
            }
        } else if (childNode->isComment()) {
            // Do nothing.
        } else {
            IssuePtr issue = Issue::create();
            issue->setDescription("Model '" + model->name() + "' has an invalid child element '" + childNode->name() + "'.");
            issue->setModel(model);
            issue->setReferenceRule(Issue::ReferenceRule::MODEL_CHILD);
            mParser->addIssue(issue);
        }
        childNode = childNode->next();
    }

    if (!encapsulationNodes.empty()) {
        loadEncapsulation(model, encapsulationNodes.at(0));
        if (encapsulationNodes.size() > 1) {
            IssuePtr issue = Issue::create();
            issue->setDescription("Model '" + model->name() + "' has more than one encapsulation element.");
            issue->setModel(model);
            issue->setCause(Issue::Cause::ENCAPSULATION);
            issue->setReferenceRule(Issue::ReferenceRule::MODEL_MORE_THAN_ONE_ENCAPSULATION);
            mParser->addIssue(issue);
        }
    }
    for (const auto &connectionNode : connectionNodes) {
        loadConnection(model, connectionNode);
    }

    // Link units to their names.
    for (size_t index = 0; index < model->componentCount(); ++index) {
        auto c = model->component(index);
        traverseComponentTreeLinkingUnits(c, mParser->shared_from_this());
    }
}

std::string cleanMath(const std::string &math)
{
    // Clean up the given math string so that all its lines have the same
    // indentation reference. Indeed, say that we parse the following code:
    //
    // <model xmlns="http://www.cellml.org/cellml/2.0#"
    //        xmlns:cellml="http://www.cellml.org/cellml/2.0#"
    //        xmlns:xlink="http://www.w3.org/1999/xlink" name="sin" id="sin">
    //   <component name="sin" id="sin">
    //     <variable name="x" units="dimensionless"
    //               interface="public_and_private"/>
    //     <variable id="sin" units="dimensionless" name="sin"
    //               interface="public_and_private"/>
    //     <math xmlns="http://www.w3.org/1998/Math/MathML">
    //       <apply id="actual_sin">
    //         <eq/>
    //         <ci>sin</ci>
    //         <apply>
    //           <sin/>
    //           <ci>x</ci>
    //         </apply>
    //       </apply>
    //     </math>
    //   </component>
    // </model>
    //
    // Then, Parser::ParserImpl::loadComponent() will eventually call
    // Component::appendMath() with a math string value of:
    //
    // <math xmlns="http://www.w3.org/1998/Math/MathML">
    //       <apply id="actual_sin">
    //         <eq/>
    //         <ci>sin</ci>
    //         <apply>
    //           <sin/>
    //           <ci>x</ci>
    //         </apply>
    //       </apply>
    //     </math>
    //
    // So, we need to clean it to get:
    //
    // <math xmlns="http://www.w3.org/1998/Math/MathML">
    //   <apply id="actual_sin">
    //     <eq/>
    //     <ci>sin</ci>
    //     <apply>
    //       <sin/>
    //       <ci>x</ci>
    //     </apply>
    //   </apply>
    // </math>

    std::istringstream lines(math);
    std::string line;
    bool skipLine = true;
    size_t indentSize = std::numeric_limits<size_t>::max();

    while (std::getline(lines, line)) {
        if (skipLine) {
            skipLine = false;
        } else {
            size_t crtIndentSize = 0;
            for (const char &c : line) {
                if (c == ' ') {
                    ++crtIndentSize;
                }
            }
            indentSize = std::min(crtIndentSize, indentSize);
        }
    }

    std::string cleanMath;

    lines = std::istringstream(math);
    skipLine = true;

    while (std::getline(lines, line)) {
        if (skipLine) {
            cleanMath += line + '\n';
            skipLine = false;
        } else {
            cleanMath += line.substr(indentSize) + '\n';
        }
    }

    return cleanMath;
}

void Parser::ParserImpl::loadComponent(const ComponentPtr &component, const XmlNodePtr &node) const
{
    XmlAttributePtr attribute = node->firstAttribute();
    while (attribute) {
        if (attribute->isType("name")) {
            component->setName(attribute->value());
        } else if (attribute->isType("id")) {
            component->setId(attribute->value());
        } else {
            IssuePtr issue = Issue::create();
            issue->setDescription("Component '" + node->attribute("name") + "' has an invalid attribute '" + attribute->name() + "'.");
            issue->setComponent(component);
            mParser->addIssue(issue);
        }
        attribute = attribute->next();
    }
    XmlNodePtr childNode = node->firstChild();
    while (childNode) {
        if (childNode->isCellmlElement("variable")) {
            VariablePtr variable = Variable::create();
            loadVariable(variable, childNode);
            component->addVariable(variable);
        } else if (childNode->isCellmlElement("reset")) {
            ResetPtr reset = Reset::create();
            loadReset(reset, component, childNode);
            component->addReset(reset);
        } else if (childNode->isMathmlElement("math")) {
            // Copy any namespaces that do not feature as a namespace definition
            // of the math node into the math node.
            auto mathElementDefinedNamespaces = childNode->definedNamespaces();
            auto possiblyUndefinedNamespaces = traverseTreeForUndefinedNamespaces(childNode);
            auto undefinedNamespaces = determineMissingNamespaces(possiblyUndefinedNamespaces, mathElementDefinedNamespaces);
            XmlNamespaceMap::const_iterator it;
            for (it = undefinedNamespaces.begin(); it != undefinedNamespaces.end(); ++it) {
                childNode->addNamespaceDefinition(it->second, it->first);
            }

            // Append a self contained math XML document to the component.
            std::string math = cleanMath(childNode->convertToString(true) + "\n");
            component->appendMath(math);
        } else if (childNode->isText()) {
            std::string textNode = childNode->convertToString();
            // Ignore whitespace when parsing.
            if (hasNonWhitespaceCharacters(textNode)) {
                IssuePtr issue = Issue::create();
                issue->setDescription("Component '" + component->name() + "' has an invalid non-whitespace child text element '" + textNode + "'.");
                issue->setComponent(component);
                issue->setReferenceRule(Issue::ReferenceRule::COMPONENT_CHILD);
                mParser->addIssue(issue);
            }
        } else if (childNode->isComment()) {
            // Do nothing.
        } else {
            IssuePtr issue = Issue::create();
            issue->setDescription("Component '" + component->name() + "' has an invalid child element '" + childNode->name() + "'.");
            issue->setComponent(component);
            issue->setReferenceRule(Issue::ReferenceRule::COMPONENT_CHILD);
            mParser->addIssue(issue);
        }
        childNode = childNode->next();
    }
}

void Parser::ParserImpl::loadUnits(const UnitsPtr &units, const XmlNodePtr &node) const
{
    XmlAttributePtr attribute = node->firstAttribute();
    while (attribute) {
        if (attribute->isType("name")) {
            units->setName(attribute->value());
        } else if (attribute->isType("id")) {
            units->setId(attribute->value());
        } else {
            IssuePtr issue = Issue::create();
            issue->setDescription("Units '" + units->name() + "' has an invalid attribute '" + attribute->name() + "'.");
            issue->setUnits(units);
            mParser->addIssue(issue);
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
                IssuePtr issue = Issue::create();
                issue->setDescription("Units '" + units->name() + "' has an invalid non-whitespace child text element '" + textNode + "'.");
                issue->setUnits(units);
                issue->setReferenceRule(Issue::ReferenceRule::UNITS_CHILD);
                mParser->addIssue(issue);
            }
        } else if (childNode->isComment()) {
            // Do nothing.
        } else {
            IssuePtr issue = Issue::create();
            issue->setDescription("Units '" + units->name() + "' has an invalid child element '" + childNode->name() + "'.");
            issue->setUnits(units);
            issue->setReferenceRule(Issue::ReferenceRule::UNITS_CHILD);
            mParser->addIssue(issue);
        }
        childNode = childNode->next();
    }
}

void Parser::ParserImpl::loadUnit(const UnitsPtr &units, const XmlNodePtr &node) const
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
                IssuePtr issue = Issue::create();
                issue->setDescription("Unit referencing '" + node->attribute("units") + "' in units '" + units->name() + "' has an invalid non-whitespace child text element '" + textNode + "'.");
                issue->setUnits(units);
                mParser->addIssue(issue);
            }
        } else if (childNode->isComment()) {
            // Do nothing.
        } else {
            IssuePtr issue = Issue::create();
            issue->setDescription("Unit referencing '" + node->attribute("units") + "' in units '" + units->name() + "' has an invalid child element '" + childNode->name() + "'.");
            issue->setUnits(units);
            mParser->addIssue(issue);
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
                if (!convertToDouble(attribute->value(), exponent)) {
                    // TODO This value won't be saved for validation later, so it does need to be reported now.
                    IssuePtr issue = Issue::create();
                    issue->setDescription("Unit referencing '" + node->attribute("units") + "' in units '" + units->name() + "' has an exponent with the value '" + attribute->value() + "' that is a representation of a CellML real valued number, but out of range of the 'double' type.");
                    issue->setUnits(units);
                    issue->setReferenceRule(Issue::ReferenceRule::UNIT_EXPONENT);
                    mParser->addIssue(issue);
                }
            } else {
                // TODO This value won't be saved for validation later, so it does need to be reported now.
                IssuePtr issue = Issue::create();
                issue->setDescription("Unit referencing '" + node->attribute("units") + "' in units '" + units->name() + "' has an exponent with the value '" + attribute->value() + "' that is not a representation of a CellML real valued number.");
                issue->setUnits(units);
                issue->setReferenceRule(Issue::ReferenceRule::UNIT_EXPONENT);
                mParser->addIssue(issue);
            }
        } else if (attribute->isType("multiplier")) {
            if (isCellMLReal(attribute->value())) {
                if (!convertToDouble(attribute->value(), multiplier)) {
                    // TODO This value won't be saved for validation later, so it does need to be reported now.
                    IssuePtr issue = Issue::create();
                    issue->setDescription("Unit referencing '" + node->attribute("units") + "' in units '" + units->name() + "' has a multiplier with the value '" + attribute->value() + "' that is a representation of a CellML real valued number, but out of range of the 'double' type.");
                    issue->setUnits(units);
                    issue->setReferenceRule(Issue::ReferenceRule::UNIT_MULTIPLIER);
                    mParser->addIssue(issue);
                }
            } else {
                // TODO This value won't be saved for validation later, so it does need to be reported now.
                IssuePtr issue = Issue::create();
                issue->setDescription("Unit referencing '" + node->attribute("units") + "' in units '" + units->name() + "' has a multiplier with the value '" + attribute->value() + "' that is not a representation of a CellML real valued number.");
                issue->setUnits(units);
                issue->setReferenceRule(Issue::ReferenceRule::UNIT_MULTIPLIER);
                mParser->addIssue(issue);
            }
        } else if (attribute->isType("id")) {
            id = attribute->value();
        } else {
            IssuePtr issue = Issue::create();
            issue->setDescription("Unit referencing '" + node->attribute("units") + "' in units '" + units->name() + "' has an invalid attribute '" + attribute->name() + "'.");
            issue->setUnits(units);
            issue->setReferenceRule(Issue::ReferenceRule::UNIT_OPTIONAL_ATTRIBUTE);
            mParser->addIssue(issue);
        }
        attribute = attribute->next();
    }
    // Add this unit to the parent units.
    units->addUnit(reference, prefix, exponent, multiplier, id);
}

void Parser::ParserImpl::loadVariable(const VariablePtr &variable, const XmlNodePtr &node) const
{
    // A variable should not have any children.
    XmlNodePtr childNode = node->firstChild();
    while (childNode) {
        if (childNode->isText()) {
            std::string textNode = childNode->convertToString();
            // Ignore whitespace when parsing.
            if (hasNonWhitespaceCharacters(textNode)) {
                IssuePtr issue = Issue::create();
                issue->setDescription("Variable '" + node->attribute("name") + "' has an invalid non-whitespace child text element '" + textNode + "'.");
                issue->setVariable(variable);
                mParser->addIssue(issue);
            }
        } else if (childNode->isComment()) {
            // Do nothing.
        } else {
            IssuePtr issue = Issue::create();
            issue->setDescription("Variable '" + node->attribute("name") + "' has an invalid child element '" + childNode->name() + "'.");
            issue->setVariable(variable);
            mParser->addIssue(issue);
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
            IssuePtr issue = Issue::create();
            issue->setDescription("Variable '" + node->attribute("name") + "' has an invalid attribute '" + attribute->name() + "'.");
            issue->setVariable(variable);
            mParser->addIssue(issue);
        }
        attribute = attribute->next();
    }
}

void Parser::ParserImpl::loadConnection(const ModelPtr &model, const XmlNodePtr &node) const
{
    // Define types for variable and component pairs, and their ids.
    using NameInfo = std::vector<std::string>;
    using NameInfoMap = std::vector<NameInfo>;
    using NamePair = std::pair<std::string, std::string>;

    // Initialise name pairs and flags.
    NamePair componentNamePair;
    NameInfo variableNameInfo;
    NameInfoMap variableNameMap;
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
            IssuePtr issue = Issue::create();
            issue->setDescription("Connection in model '" + model->name() + "' has an invalid connection attribute '" + attribute->name() + "'.");
            issue->setModel(model);
            issue->setCause(Issue::Cause::CONNECTION);
            mParser->addIssue(issue);
        }
        attribute = attribute->next();
    }
    // Check that we found both components.
    if (component1Name.empty()) {
        IssuePtr issue = Issue::create();
        issue->setDescription("Connection in model '" + model->name() + "' does not have a valid component_1 in a connection element.");
        issue->setModel(model);
        issue->setCause(Issue::Cause::CONNECTION);
        issue->setReferenceRule(Issue::ReferenceRule::CONNECTION_COMPONENT1);
        mParser->addIssue(issue);
        component1Missing = true;
    }
    if (component2Name.empty()) {
        IssuePtr issue = Issue::create();
        issue->setDescription("Connection in model '" + model->name() + "' does not have a valid component_2 in a connection element.");
        issue->setModel(model);
        issue->setCause(Issue::Cause::CONNECTION);
        issue->setReferenceRule(Issue::ReferenceRule::CONNECTION_COMPONENT2);
        mParser->addIssue(issue);
        component2Missing = true;
    }
    componentNamePair = std::make_pair(component1Name, component2Name);

    XmlNodePtr childNode = node->firstChild();

    if (childNode == nullptr) {
        IssuePtr issue = Issue::create();
        std::string des = "Connection in model '" + model->name() + "'";
        if (connectionId.empty()) {
            des += " does not contain any 'map_variables' elements and will be disregarded.";
        } else {
            des += " has an id of '" + connectionId + "' but does not contain any 'map_variables' elements.";
            des += " The connection will be disregarded and the associated id will be lost.";
        }
        issue->setDescription(des);
        issue->setModel(model);
        issue->setCause(Issue::Cause::CONNECTION);
        issue->setReferenceRule(Issue::ReferenceRule::CONNECTION_CHILD);
        issue->setLevel(libcellml::Issue::Level::WARNING);
        mParser->addIssue(issue);
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
                    IssuePtr issue = Issue::create();
                    issue->setDescription("Connection in model '" + model->name() + "' has an invalid non-whitespace child text element '" + textNode + "'.");
                    issue->setModel(model);
                    issue->setCause(Issue::Cause::CONNECTION);
                    mParser->addIssue(issue);
                }
            } else if (grandchildNode->isComment()) {
                // Do nothing.
            } else {
                IssuePtr issue = Issue::create();
                issue->setDescription("Connection in model '" + model->name() + "' has an invalid child element '" + grandchildNode->name() + "' of element '" + childNode->name() + "'.");
                issue->setModel(model);
                issue->setCause(Issue::Cause::CONNECTION);
                mParser->addIssue(issue);
            }
            grandchildNode = grandchildNode->next();
        }

        if (childNode->isCellmlElement("map_variables")) {
            std::string variable1Name;
            std::string variable2Name;
            XmlAttributePtr childAttribute = childNode->firstAttribute();
            mappingId.clear();
            while (childAttribute) {
                if (childAttribute->isType("variable_1")) {
                    variable1Name = childAttribute->value();
                } else if (childAttribute->isType("variable_2")) {
                    variable2Name = childAttribute->value();
                } else if (childAttribute->isType("id")) {
                    mappingId = childAttribute->value();
                } else {
                    IssuePtr issue = Issue::create();
                    issue->setDescription("Connection in model '" + model->name() + "' has an invalid map_variables attribute '" + childAttribute->name() + "'.");
                    issue->setModel(model);
                    issue->setCause(Issue::Cause::CONNECTION);
                    mParser->addIssue(issue);
                }
                childAttribute = childAttribute->next();
            }
            // Check that we found both variables.
            if (variable1Name.empty()) {
                IssuePtr issue = Issue::create();
                issue->setDescription("Connection in model '" + model->name() + "' does not have a valid variable_1 in a map_variables element.");
                issue->setModel(model);
                issue->setCause(Issue::Cause::CONNECTION);
                issue->setReferenceRule(Issue::ReferenceRule::MAP_VARIABLES_VARIABLE1);
                mParser->addIssue(issue);
                variable1Missing = true;
            }
            if (variable2Name.empty()) {
                IssuePtr issue = Issue::create();
                issue->setDescription("Connection in model '" + model->name() + "' does not have a valid variable_2 in a map_variables element.");
                issue->setModel(model);
                issue->setCause(Issue::Cause::CONNECTION);
                issue->setReferenceRule(Issue::ReferenceRule::MAP_VARIABLES_VARIABLE2);
                mParser->addIssue(issue);
                variable2Missing = true;
            }
            // We can have multiple map_variables per connection.
            variableNameInfo = {variable1Name, variable2Name, mappingId};
            variableNameMap.push_back(variableNameInfo);
            mapVariablesFound = true;

        } else if (childNode->isText()) {
            const std::string textNode = childNode->convertToString();
            // Ignore whitespace when parsing.
            if (hasNonWhitespaceCharacters(textNode)) {
                IssuePtr issue = Issue::create();
                issue->setDescription("Connection in model '" + model->name() + "' has an invalid non-whitespace child text element '" + textNode + "'.");
                issue->setModel(model);
                issue->setCause(Issue::Cause::CONNECTION);
                mParser->addIssue(issue);
            }
        } else if (childNode->isComment()) {
            // Do nothing.
        } else {
            IssuePtr issue = Issue::create();
            issue->setDescription("Connection in model '" + model->name() + "' has an invalid child element '" + childNode->name() + "'.");
            issue->setModel(model);
            issue->setCause(Issue::Cause::CONNECTION);
            mParser->addIssue(issue);
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
            IssuePtr issue = Issue::create();
            issue->setDescription("Connection in model '" + model->name() + "' specifies '" + componentNamePair.first + "' as component_1 but it does not exist in the model.");
            issue->setModel(model);
            issue->setCause(Issue::Cause::CONNECTION);
            issue->setReferenceRule(Issue::ReferenceRule::CONNECTION_COMPONENT1);
            mParser->addIssue(issue);
        }
    }
    if (model->containsComponent(componentNamePair.second)) {
        component2 = model->component(componentNamePair.second);
    } else {
        if (!component2Missing) {
            IssuePtr issue = Issue::create();
            issue->setDescription("Connection in model '" + model->name() + "' specifies '" + componentNamePair.second + "' as component_2 but it does not exist in the model.");
            issue->setModel(model);
            issue->setCause(Issue::Cause::CONNECTION);
            issue->setReferenceRule(Issue::ReferenceRule::CONNECTION_COMPONENT2);
            mParser->addIssue(issue);
        }
    }

    // If we have a map_variables, check that the variables exist in the named components. TODO Remove as is validation?
    if (mapVariablesFound) {
        for (const auto &iterInfo : variableNameMap) {
            VariablePtr variable1 = nullptr;
            VariablePtr variable2 = nullptr;
            if (component1) {
                if (component1->hasVariable(iterInfo[0])) {
                    variable1 = component1->variable(iterInfo[0]);
                } else if (component1->isImport()) {
                    // With an imported component we assume this variable exists in the imported component.
                    variable1 = Variable::create();
                    variable1->setName(iterInfo[0]);
                    component1->addVariable(variable1);
                } else {
                    if (!variable1Missing) {
                        IssuePtr issue = Issue::create();
                        issue->setDescription("Variable '" + iterInfo[0] + "' is specified as variable_1 in a connection but it does not exist in component_1 component '" + component1->name() + "' of model '" + model->name() + "'.");
                        issue->setComponent(component1);
                        issue->setCause(Issue::Cause::CONNECTION);
                        issue->setReferenceRule(Issue::ReferenceRule::MAP_VARIABLES_VARIABLE1);
                        mParser->addIssue(issue);
                    }
                }
            } else {
                IssuePtr issue = Issue::create();
                issue->setDescription("Connection in model '" + model->name() + "' specifies '" + iterInfo[0] + "' as variable_1 but the corresponding component_1 is invalid.");
                issue->setModel(model);
                issue->setCause(Issue::Cause::CONNECTION);
                issue->setReferenceRule(Issue::ReferenceRule::MAP_VARIABLES_VARIABLE1);
                mParser->addIssue(issue);
            }
            if (component2) {
                if (component2->hasVariable(iterInfo[1])) {
                    variable2 = component2->variable(iterInfo[1]);
                } else if (component2->isImport()) {
                    // With an imported component we assume this variable exists in the imported component.
                    variable2 = Variable::create();
                    variable2->setName(iterInfo[1]);
                    component2->addVariable(variable2);
                } else {
                    if (!variable2Missing) {
                        IssuePtr issue = Issue::create();
                        issue->setDescription("Variable '" + iterInfo[1] + "' is specified as variable_2 in a connection but it does not exist in component_2 component '" + component2->name() + "' of model '" + model->name() + "'.");
                        issue->setComponent(component1);
                        issue->setCause(Issue::Cause::CONNECTION);
                        issue->setReferenceRule(Issue::ReferenceRule::MAP_VARIABLES_VARIABLE2);
                        mParser->addIssue(issue);
                    }
                }
            } else {
                IssuePtr issue = Issue::create();
                issue->setDescription("Connection in model '" + model->name() + "' specifies '" + iterInfo[1] + "' as variable_2 but the corresponding component_2 is invalid.");
                issue->setModel(model);
                issue->setCause(Issue::Cause::CONNECTION);
                issue->setReferenceRule(Issue::ReferenceRule::MAP_VARIABLES_VARIABLE2);
                mParser->addIssue(issue);
            }
            // Set the variable equivalence relationship for this variable pair.
            if ((variable1) && (variable2)) {
                Variable::addEquivalence(variable1, variable2, iterInfo[2], connectionId);
            }
        }
    } else {
        IssuePtr issue = Issue::create();
        issue->setDescription("Connection in model '" + model->name() + "' does not have a map_variables element.");
        issue->setModel(model);
        issue->setCause(Issue::Cause::CONNECTION);
        issue->setReferenceRule(Issue::ReferenceRule::CONNECTION_CHILD);
        mParser->addIssue(issue);
    }
}

ComponentPtr Parser::ParserImpl::loadComponentRef(const ModelPtr &model, const XmlNodePtr &node)
{
    ComponentPtr parentComponent = nullptr;
    std::string parentComponentName;
    std::string encapsulationId;
    // Check for a component in the parent component_ref.
    XmlAttributePtr attribute = node->firstAttribute();
    while (attribute) {
        if (attribute->isType("component")) {
            parentComponentName = attribute->value();
            if (model->containsComponent(parentComponentName)) {
                // Will re-add this to the model once we encapsulate the child(ren).
                parentComponent = model->takeComponent(parentComponentName);
            } else {
                IssuePtr issue = Issue::create();
                issue->setDescription("Encapsulation in model '" + model->name() + "' specifies '" + parentComponentName + "' as a component in a component_ref but it does not exist in the model.");
                issue->setModel(model);
                issue->setCause(Issue::Cause::ENCAPSULATION);
                issue->setReferenceRule(Issue::ReferenceRule::COMPONENT_REF_COMPONENT);
                mParser->addIssue(issue);
            }
        } else if (attribute->isType("id")) {
            encapsulationId = attribute->value();
        } else {
            IssuePtr issue = Issue::create();
            issue->setDescription("Encapsulation in model '" + model->name() + "' has an invalid component_ref attribute '" + attribute->name() + "'.");
            issue->setModel(model);
            issue->setCause(Issue::Cause::ENCAPSULATION);
            issue->setReferenceRule(Issue::ReferenceRule::COMPONENT_REF_COMPONENT);
            mParser->addIssue(issue);
        }
        attribute = attribute->next();
    }
    if ((!parentComponent) && (parentComponentName.empty())) {
        IssuePtr issue = Issue::create();
        issue->setDescription("Encapsulation in model '" + model->name() + "' does not have a valid component attribute in a component_ref element.");
        issue->setModel(model);
        issue->setCause(Issue::Cause::ENCAPSULATION);
        issue->setReferenceRule(Issue::ReferenceRule::COMPONENT_REF_COMPONENT);
        mParser->addIssue(issue);
    } else if (parentComponent) {
        parentComponent->setEncapsulationId(encapsulationId);
    }

    // Get first child of this parent component_ref.
    XmlNodePtr childComponentNode = node->firstChild();

    // Loop over encapsulated children.
    std::string childEncapsulationId;
    while (childComponentNode) {
        ComponentPtr childComponent = nullptr;
        if (childComponentNode->isCellmlElement("component_ref")) {
            childComponent = loadComponentRef(model, childComponentNode);
        } else if (childComponentNode->isText()) {
            const std::string textNode = childComponentNode->convertToString();
            // Ignore whitespace when parsing.
            if (hasNonWhitespaceCharacters(textNode)) {
                IssuePtr issue = Issue::create();
                issue->setDescription("Encapsulation in model '" + model->name() + "' has an invalid non-whitespace child text element '" + textNode + "'.");
                issue->setModel(model);
                issue->setCause(Issue::Cause::ENCAPSULATION);
                mParser->addIssue(issue);
            }
        } else if (childComponentNode->isComment()) {
            // Do nothing.
        } else {
            IssuePtr issue = Issue::create();
            issue->setDescription("Encapsulation in model '" + model->name() + "' has an invalid child element '" + childComponentNode->name() + "'.");
            issue->setModel(model);
            issue->setCause(Issue::Cause::ENCAPSULATION);
            mParser->addIssue(issue);
        }

        if ((parentComponent) && (childComponent)) {
            // Set parent/child encapsulation relationship.
            parentComponent->addComponent(childComponent);
        }
        childComponentNode = childComponentNode->next();
    }

    return parentComponent;
}

void Parser::ParserImpl::loadEncapsulation(const ModelPtr &model, const XmlNodePtr &node)
{
    XmlNodePtr componentRefNode = node;
    while (componentRefNode) {
        ComponentPtr parentComponent = nullptr;
        std::string encapsulationId;
        bool haveComponentRef = false;
        if (componentRefNode->isCellmlElement("component_ref")) {
            haveComponentRef = true;
            parentComponent = loadComponentRef(model, componentRefNode);
        } else if (componentRefNode->isText()) {
            const std::string textNode = componentRefNode->convertToString();
            // Ignore whitespace when parsing.
            if (hasNonWhitespaceCharacters(textNode)) {
                IssuePtr issue = Issue::create();
                issue->setDescription("Encapsulation in model '" + model->name() + "' has an invalid non-whitespace child text element '" + textNode + "'.");
                issue->setModel(model);
                issue->setCause(Issue::Cause::ENCAPSULATION);
                issue->setReferenceRule(Issue::ReferenceRule::COMPONENT_REF_CHILD);
                mParser->addIssue(issue);
            } else {
                // Continue to next node if this is whitespace (don't try to parse children of whitespace).
                componentRefNode = componentRefNode->next();
                continue;
            }
        } else if (componentRefNode->isComment()) {
            // Do nothing.
        } else {
            IssuePtr issue = Issue::create();
            issue->setDescription("Encapsulation in model '" + model->name() + "' has an invalid child element '" + componentRefNode->name() + "'.");
            issue->setModel(model);
            issue->setCause(Issue::Cause::ENCAPSULATION);
            issue->setReferenceRule(Issue::ReferenceRule::ENCAPSULATION_CHILD);
            mParser->addIssue(issue);
        }

        // Add the parentComponent to the model with its child(ren) encapsulated.
        if (parentComponent) {
            model->addComponent(parentComponent);
            if (parentComponent->componentCount() == 0) {
                IssuePtr issue = Issue::create();
                issue->setDescription("Encapsulation in model '" + model->name() + "' specifies '" + parentComponent->name() + "' as a parent component_ref but it does not have any children.");
                issue->setModel(model);
                issue->setCause(Issue::Cause::ENCAPSULATION);
                mParser->addIssue(issue);
            }
        } else if (!parentComponent && haveComponentRef) {
            IssuePtr issue = Issue::create();
            issue->setDescription("Encapsulation in model '" + model->name() + "' specifies an invalid parent component_ref that also does not have any children.");
            issue->setModel(model);
            issue->setCause(Issue::Cause::ENCAPSULATION);
            mParser->addIssue(issue);
        }

        componentRefNode = componentRefNode->next();
    }
}

void Parser::ParserImpl::loadImport(ImportSourcePtr &importSource, const ModelPtr &model, const XmlNodePtr &node) const
{
    XmlAttributePtr attribute = node->firstAttribute();
    std::string id;
    while (attribute) {
        if (attribute->isType("href", XLINK_NS)) {
            importSource->setUrl(attribute->value());
        } else if (attribute->isType("id")) {
            id = attribute->value();
            importSource->setId(id);
        } else if (attribute->inNamespaceUri(XLINK_NS)) {
            // Allow xlink attributes but do nothing for them.
        } else {
            IssuePtr issue = Issue::create();
            issue->setDescription("Import from '" + node->attribute("href") + "' has an invalid attribute '" + attribute->name() + "'.");
            issue->setImportSource(importSource);
            mParser->addIssue(issue);
        }
        attribute = attribute->next();
    }
    XmlNodePtr childNode = node->firstChild();

    if (childNode == nullptr) {
        auto issue = Issue::create();
        if (id.empty()) {
            issue->setDescription("Import from '" + node->attribute("href") + "' is empty and will be disregarded.");
        } else {
            issue->setDescription("Import from '" + node->attribute("href") + "' has an id of '" + id + "' but is empty. The import will be disregarded and the associated id will be lost.");
        }
        issue->setImportSource(importSource);
        issue->setCause(libcellml::Issue::Cause::IMPORT);
        issue->setLevel(libcellml::Issue::Level::WARNING);
        mParser->addIssue(issue);
    }
    while (childNode) {
        if (childNode->isCellmlElement("component")) {
            ComponentPtr importedComponent = Component::create();
            XmlAttributePtr childAttribute = childNode->firstAttribute();
            importedComponent->setImportSource(importSource);
            while (childAttribute) {
                if (childAttribute->isType("name")) {
                    importedComponent->setName(childAttribute->value());
                } else if (childAttribute->isType("id")) {
                    importedComponent->setId(childAttribute->value());
                } else if (childAttribute->isType("component_ref")) {
                    importedComponent->setImportReference(childAttribute->value());
                } else {
                    IssuePtr issue = Issue::create();
                    issue->setDescription("Import of component '" + childNode->attribute("name") + "' from '" + node->attribute("href") + "' has an invalid attribute '" + childAttribute->name() + "'.");
                    issue->setImportSource(importSource);
                    mParser->addIssue(issue);
                }
                childAttribute = childAttribute->next();
            }
            model->addComponent(importedComponent);
        } else if (childNode->isCellmlElement("units")) {
            UnitsPtr importedUnits = Units::create();
            XmlAttributePtr childAttribute = childNode->firstAttribute();
            importedUnits->setImportSource(importSource);
            while (childAttribute) {
                if (childAttribute->isType("name")) {
                    importedUnits->setName(childAttribute->value());
                } else if (childAttribute->isType("id")) {
                    importedUnits->setId(childAttribute->value());
                } else if (childAttribute->isType("units_ref")) {
                    importedUnits->setImportReference(childAttribute->value());
                } else {
                    IssuePtr issue = Issue::create();
                    issue->setDescription("Import of units '" + childNode->attribute("name") + "' from '" + node->attribute("href") + "' has an invalid attribute '" + childAttribute->name() + "'.");
                    issue->setImportSource(importSource);
                    mParser->addIssue(issue);
                }
                childAttribute = childAttribute->next();
            }
            model->addUnits(importedUnits);
        } else if (childNode->isText()) {
            const std::string textNode = childNode->convertToString();
            // Ignore whitespace when parsing.
            if (hasNonWhitespaceCharacters(textNode)) {
                IssuePtr issue = Issue::create();
                issue->setDescription("Import from '" + node->attribute("href") + "' has an invalid non-whitespace child text element '" + textNode + "'.");
                issue->setImportSource(importSource);
                issue->setReferenceRule(Issue::ReferenceRule::IMPORT_CHILD);
                mParser->addIssue(issue);
            }
        } else if (childNode->isComment()) {
            // Do nothing.
        } else {
            IssuePtr issue = Issue::create();
            issue->setDescription("Import from '" + node->attribute("href") + "' has an invalid child element '" + childNode->name() + "'.");
            issue->setImportSource(importSource);
            issue->setReferenceRule(Issue::ReferenceRule::IMPORT_CHILD);
            mParser->addIssue(issue);
        }
        childNode = childNode->next();
    }
}

void Parser::ParserImpl::loadResetChild(const std::string &childType, const ResetPtr &reset, const ComponentPtr &component, const XmlNodePtr &node) const
{
    // TODO The spec. has not yet defined the test_value and reset_value specification elements.
    std::string variableName;
    std::string testVariableName;

    if (reset->variable() != nullptr) {
        variableName = reset->variable()->name();
    }

    if (reset->testVariable() != nullptr) {
        testVariableName = reset->testVariable()->name();
    }

    XmlAttributePtr childAttribute = node->firstAttribute();
    while (childAttribute) {
        if (childAttribute->isType("id")) {
            if (childType == "test_value") {
                reset->setTestValueId(childAttribute->value());
            } else {
                reset->setResetValueId(childAttribute->value());
            }
        } else {
            IssuePtr issue = Issue::create();
            issue->setDescription("Reset in component '" + component->name() + "' referencing variable '" + variableName + "' and test_variable '" + testVariableName + "' has an unexpected attribute in the " + childType + " block of '" + childAttribute->name() + "'.");
            issue->setReset(reset);
            issue->setReferenceRule(Issue::ReferenceRule::RESET_TEST_VALUE);
            mParser->addIssue(issue);
        }
        childAttribute = childAttribute->next();
    }

    XmlNodePtr mathNode = node->firstChild();
    while (mathNode) {
        if (mathNode->isMathmlElement("math")) {
            std::string math = mathNode->convertToString(true) + "\n";
            if (childType == "test_value") {
                reset->appendTestValue(math);
            } else {
                reset->appendResetValue(math);
            }
        } else if (mathNode->isComment()) {
            // Do nothing
        } else {
            std::string textNode = mathNode->convertToString();
            // Ignore whitespace when parsing.
            if (hasNonWhitespaceCharacters(textNode)) {
                IssuePtr issue = Issue::create();
                issue->setDescription("The " + childType + " in the reset in component '" + component->name() + "' referencing variable '" + variableName + "' and test_variable '" + testVariableName + "' should have a MathML block as a child.");
                issue->setReset(reset);
                issue->setReferenceRule(Issue::ReferenceRule::RESET_TEST_VALUE);
                mParser->addIssue(issue);
            }
        }
        mathNode = mathNode->next();
    }
}

void Parser::ParserImpl::checkResetChildMultiplicity(size_t count, const std::string &childType, const ResetPtr &reset, const ComponentPtr &component) const
{
    std::string variableName;
    std::string testVariableName;

    if (reset->variable() != nullptr) {
        variableName = reset->variable()->name();
    }

    if (reset->testVariable() != nullptr) {
        testVariableName = reset->testVariable()->name();
    }

    if (count > 1) {
        IssuePtr issue = Issue::create();
        issue->setDescription("Reset in component '" + component->name() + "' referencing variable '"
                              + variableName + "' and test_variable '" + testVariableName + "' has " + convertToString(count) + " " + childType + " blocks.");
        issue->setReset(reset);
        issue->setReferenceRule(Issue::ReferenceRule::RESET_TEST_VALUE);
        mParser->addIssue(issue);
    }
    if (count == 0) {
        IssuePtr issue = Issue::create();
        issue->setDescription("Reset in component '" + component->name() + "' referencing variable '"
                              + variableName + "' and test_variable '" + testVariableName + "' does not have a " + childType + " block defined.");
        issue->setReset(reset);
        issue->setReferenceRule(Issue::ReferenceRule::RESET_TEST_VALUE);
        mParser->addIssue(issue);
    }
}

void Parser::ParserImpl::loadReset(const ResetPtr &reset, const ComponentPtr &component, const XmlNodePtr &node) const
{
    int order = 0;
    bool orderValid = false;
    bool orderDefined = false;

    XmlAttributePtr attribute = node->firstAttribute();
    while (attribute) {
        if (attribute->isType("variable")) {
            const std::string variableReference = attribute->value();
            VariablePtr referencedVariable = component->variable(variableReference);

            if (referencedVariable == nullptr) {
                IssuePtr issue = Issue::create();
                issue->setDescription("Reset referencing variable '" + variableReference + "' is not a valid reference for a variable in component '" + component->name() + "'.");
                issue->setReset(reset);
                issue->setReferenceRule(Issue::ReferenceRule::RESET_VARIABLE_REF);
                mParser->addIssue(issue);
            } else {
                reset->setVariable(referencedVariable);
            }
        } else if (attribute->isType("test_variable")) {
            const std::string testVariableReference = attribute->value();
            VariablePtr testVariable = component->variable(testVariableReference);
            if (testVariable == nullptr) {
                IssuePtr issue = Issue::create();
                issue->setDescription("Reset referencing test_variable '" + testVariableReference + "' is not a valid reference for a variable in component '" + component->name() + "'.");
                issue->setReset(reset);
                issue->setReferenceRule(Issue::ReferenceRule::RESET_TEST_VARIABLE_REF);
                mParser->addIssue(issue);
            } else {
                reset->setTestVariable(testVariable);
            }
        } else if (attribute->isType("order")) {
            orderDefined = true;
            orderValid = isCellMLInteger(attribute->value());
            if (orderValid) {
                orderValid = convertToInt(attribute->value(), order);
                if (!orderValid) {
                    std::string variableName;
                    if (reset->variable() != nullptr) {
                        variableName = reset->variable()->name();
                    }
                    IssuePtr issue = Issue::create();
                    issue->setDescription("Reset in component '" + component->name() + "' referencing variable '" + variableName + "' has an out of range integer order value '" + attribute->value() + "'.");
                    issue->setReset(reset);
                    issue->setReferenceRule(Issue::ReferenceRule::RESET_ORDER);
                    mParser->addIssue(issue);
                }
            } else { // This value won't be saved for validation later, so it does need to be reported now.
                std::string variableName;
                if (reset->variable() != nullptr) {
                    variableName = reset->variable()->name();
                }
                IssuePtr issue = Issue::create();
                issue->setDescription("Reset in component '" + component->name() + "' referencing variable '" + variableName + "' has a non-integer order value '" + attribute->value() + "'.");
                issue->setReset(reset);
                issue->setReferenceRule(Issue::ReferenceRule::RESET_ORDER);
                mParser->addIssue(issue);
            }
        } else if (attribute->isType("id")) {
            reset->setId(attribute->value());
        } else {
            IssuePtr issue = Issue::create();
            issue->setDescription("Reset in component '" + component->name() + "' has an invalid attribute '" + attribute->name() + "'.");
            issue->setReset(reset);
            mParser->addIssue(issue);
        }
        attribute = attribute->next();
    }

    if (orderValid) {
        reset->setOrder(order);
    } else if (!orderDefined) {
        IssuePtr issue = Issue::create();
        issue->setDescription("Reset in component '" + component->name() + "' does not have its order set.");
        issue->setReset(reset);
        issue->setReferenceRule(Issue::ReferenceRule::RESET_ORDER);
        mParser->addIssue(issue);
    }

    XmlNodePtr childNode = node->firstChild();

    size_t testValueCount = 0;
    size_t resetValueCount = 0;
    while (childNode) {
        if (childNode->isCellmlElement("test_value")) {
            loadResetChild("test_value", reset, component, childNode);
            testValueCount++;
        } else if (childNode->isCellmlElement("reset_value")) {
            loadResetChild("reset_value", reset, component, childNode);
            resetValueCount++;
        } else if (childNode->isText()) {
            std::string textNode = childNode->convertToString();
            // Ignore whitespace when parsing.
            if (hasNonWhitespaceCharacters(textNode)) {
                IssuePtr issue = Issue::create();
                issue->setDescription("Reset has an invalid non-whitespace child text element '" + textNode + "'. Either a test_value block or a reset_value block is expected.");
                issue->setReset(reset);
                issue->setReferenceRule(Issue::ReferenceRule::RESET_CHILD);
                mParser->addIssue(issue);
            }
        } else if (childNode->isComment()) {
            // Do nothing.
        }
        childNode = childNode->next();
    }

    checkResetChildMultiplicity(testValueCount, "test_value", reset, component);
    checkResetChildMultiplicity(resetValueCount, "reset_value", reset, component);
}

} // namespace libcellml

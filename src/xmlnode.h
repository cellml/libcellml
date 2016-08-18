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

#pragma once

#include <libxml/parser.h>
#include <memory>
#include <string>

#include "xmlattribute.h"

namespace libcellml {

class XmlNode; /**< Forward declaration of the internal XmlNode class. */
typedef std::shared_ptr<XmlNode> XmlNodePtr; /**< Type definition for shared XML node pointer. */

/**
 * @brief The XmlNode class.
 *
 * The XmlNode class is a wrapper class for operations on
 * xmlNode objects from libxml2.
 */
class XmlNode
{
public:
    XmlNode(); /**< Constructor */
    ~XmlNode(); /**< Destructor */

    /**
     * @brief Set the internal @c xmlNode for this @c XmlNode wrapper.
     *
     * Sets the @c pImpl of the libxml2 xmlNode attribute
     * for this @c XmlNode.
     *
     * @param node The libxml2 @c xmlNodePtr to set.
     */
    void setXmlNode (const xmlNodePtr &node);

    /**
     * @brief Check if this @c XmlNode is of the named element type.
     *
     * Checks whether this @c XmlNode has the argument element type name.
     * Returns @ true if so, and @c false otherwise.
     *
     * @param elementName The @c char element type name to check for.
     *
     * @return @c true if this @c XmlNode is of the element type
     * specified by the @p elementName and @c false otherwise.
     */
    bool isType(const char *elementName);

    /**
     * @brief Get the type name of the XML element.
     *
     * Get the type name of the XML element.
     *
     * @return A @c std::string representation of the XML type name.
     */
    std::string getType() const;

    /**
     * @brief Check if this @c XmlNode has the specified attribute.
     *
     * Checks whether this @c XmlNode has an attribute of the type
     * specified by the argument @p attributeName. Returns @ true
     * if so, and @c false otherwise.
     *
     * @param attributeName The @c char attribute type to check for.
     *
     * @return @c true if this @c XmlNode has an attribute of the type
     * specified by the @p attributeName and @c false otherwise.
     */
    bool hasAttribute(const char *attributeName);

    /**
     * @brief Get the attribute of the specified type for this @c XmlNode
     *
     * Get the @c std::string corresponding with the attribute value
     * of the type @p attributeName for this @c  XmlNode.
     *
     * @param attributeName The @c char attribute type.
     *
     * @return The @c std::string form of the attribute value of the
     * specified type.
     */
    std::string getAttribute(const char *attributeName);

    /**
     * @brief Get the first attribute for this @c XmlNode
     *
     * Get the @c XmlAttributePtr corresponding with the first attribute
     * for this @c  XmlNode.
     *
     * @return The @c XmlAttributePtr form of the first attribute
     * for this @c XmlNode.
     */
    XmlAttributePtr getFirstAttribute();

    /**
     * @brief Get the first child for this @c XmlNode.
     *
     * Gets the first child @c XmlNode for this @c XmlNode based on the
     * ordering from the deserialised @c XmlDoc. If no child
     * node exists, returns @c nullptr.
     *
     * @return The @c XmlNodePtr to the first child node for this @c XmlNode.
     */
    XmlNodePtr getFirstChild();

    /**
     * @brief Get the @c XmlNode immediately following this @c XmlNode.
     *
     * Gets the next @c XmlNode immediately following this @c XmlNode based
     * on the ordering from the deserialised @c  XmlDoc. If no
     * next node exists, returns @c nullptr.
     *
     * @return The @c XmlNodePtr to the next node following this @c XmlNode.
     */
    XmlNodePtr getNext();

    /**
     * @brief Get the @c XmlNode parent of this @c XmlNode.
     *
     * Gets the parent @c XmlNode of this @c XmlNode based
     * on the ordering from the deserialised @c XmlDoc. If no
     * parent node exists, returns @c nullptr.
     *
     * @return The @c XmlNodePtr to the parent of this @c XmlNode.
     */
    XmlNodePtr getParent();

    /**
     * @brief Convert this @c XmlNode content into a @c std::string.
     *
     * Converts the content in this @c XmlNode (including all children and
     * attributes) into a @c std::string.
     *
     * @return The @c std::string representation of the content for this @c XmlNode.
     */
    std::string convertToString();

private:
    struct XmlNodeImpl; /**< Forward declaration for pImpl idiom. */
    XmlNodeImpl *mPimpl; /**< Private member to implementation pointer */
};

}

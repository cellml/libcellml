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

#ifndef XMLNODE_H
#define XMLNODE_H

#include <string>
#include <libxml/parser.h>
#include "libcellml/types.h"

namespace libcellml {

/**
 * @brief The XmlNode class.
 *
 * The XmlNode class is a wrapper class for operations on
 * xmlNode objects from libXML2.
 */
class XmlNode
{
public:
    XmlNode(); /**< Constructor */
    ~XmlNode(); /**< Destructor */

    /**
     * @brief Set the internal xmlNode for this XmlNode wrapper.
     *
     * Sets the @c pImpl of the libXML2 xmlNode attribute
     * for this XmlNode.
     *
     * @param node The libXML2 @c xmlNodePtr to set.
     */
    void setXmlNode (const xmlNodePtr &node);

    /**
     * @brief Check if this XmlNode is of the named element type.
     *
     * Checks whether this XmlNode has the argument element type name.
     * Returns @ true if so, and @c false otherwise.
     *
     * @param elementName The @c char element type name to check for.
     *
     * @return @c true if this XmlNode is of the element type
     * specified by the @p elementName and @c false otherwise.
     */
    bool isElementType(const char *elementName);

    /**
     * @brief Check if this XmlNode has the specified attribute.
     *
     * Checks whether this XmlNode has an attribute of the type
     * specified by the argument @p attributeName. Returns @ true
     * if so, and @c false otherwise.
     *
     * @param attributeName The @c char attribute type to check for.
     *
     * @return @c true if this XmlNode has an attribute of the type
     * specified by the @p attributeName and @c false otherwise.
     */
    bool hasAttribute(const char *attributeName);

    /**
     * @brief Get the attribute of the specified type for this XmlNode
     *
     * Get the @c std::string corresponding with the attribute
     * of the type @p attributeName for this XmlNode.
     *
     * @param attributeName The @c char attribute type.
     *
     * @return The @c std::string form of the attribute of the
     * specified type.
     */
    std::string getAttribute(const char *attributeName);

    /**
     * @brief Get the root attribute for this XmlNode
     *
     * Get the XmlAttributePtr corresponding with the first attribute
     * for this XmlNode.
     *
     * @return The @c XmlAttributePtr form of the first attribute
     * for this xml node
     */
    XmlAttributePtr getRootAttribute();

    /**
     * @brief Get the first child for this XmlNode.
     *
     * Gets the first child XmlNode for this XmlNode based on the
     * ordering from the deserialised XmlDoc. If no child
     * node exists, returns @c nullptr.
     *
     * @return The XmlNodePtr to the first child node for this XmlNode.
     */
    XmlNodePtr getChild();

    /**
     * @brief Get the XmlNode immediately following this XmlNode.
     *
     * Gets the next XmlNode immediately following this XmlNode based
     * on the ordering from the deserialised XmlDoc. If no
     * next node exists, returns @c nullptr.
     *
     * @return The XmlNodePtr to the next node following this XmlNode.
     */
    XmlNodePtr getNext();

    /**
     * @brief Convert this XmlNode content into a @c std::string.
     *
     * Converts the content in this XmlNode into a @c std::string.
     *
     * @return The @c std::string representation of the content for this XmlNode.
     */
    std::string convertToString();

private:
    struct XmlNodeImpl; /**< Forward declaration for pImpl idiom. */
    XmlNodeImpl* mPimpl; /**< Private member to implementation pointer */
};

}

#endif // XMLNODE_H

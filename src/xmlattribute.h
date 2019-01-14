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

#include <memory>
#include <string>

#include <libxml/parser.h>

namespace libcellml {

class XmlAttribute; /**< Forward declaration of the internal XmlAttribute class. */
typedef std::shared_ptr<XmlAttribute> XmlAttributePtr; /**< Type definition for shared XML attribute pointer. */

/**
 * @brief The XmlAttribute class.
 *
 * The XmlAttribute class is a wrapper class for operations on
 * xmlAttribute objects from libxml2.
 */
class XmlAttribute
{
public:
    XmlAttribute(); /**< Constructor */
    ~XmlAttribute(); /**< Destructor */

    /**
     * @brief Set the internal xmlAttribute for this XmlAttribute wrapper.
     *
     * Sets the @c pImpl of the libxml2 xmlAttribute attribute
     * for this XmlAttribute.
     *
     * @param attribute The libxml2 @c xmlAttributePtr to set.
     */
    void setXmlAttribute (const xmlAttrPtr &attribute);

    /**
     * @brief Check if this XmlAttribute is of the named attribute type.
     *
     * Checks whether this XmlAttribute has the argument attribute type name.
     * Returns @ true if so, and @c false otherwise.
     *
     * @param attributeName The @c char attribute type name to check for.
     *
     * @return @c true if this XmlAttribute is of the attribute type
     * specified by the @p attributeName and @c false otherwise.
     */
    bool isType(const char *attributeName);

    /**
     * @brief Get the type of this XmlAttribute.
     *
     * Gets the type of this XmlAttribute and returns it as a @c std::string.
     *
     * @return The @c std::string corresponding with the name of this XmlAttribute.
     */
    std::string getType() const;

    /**
     * @brief Get the value of this XmlAttribute.
     *
     * Gets the value of this XmlAttribute and returns it as a @c std::string.
     *
     * @return The @c std::string corresponding with the value of this XmlAttribute.
     */
    std::string getValue() const;

    /**
     * @brief Get the XmlAttribute immediately following this XmlAttribute.
     *
     * Gets the next XmlAttribute immediately following this XmlAttribute based
     * on the ordering from the parent XmlNode. If no
     * next attribute exists, returns @c nullptr.
     *
     * @return The XmlAttributePtr to the next attribute following this XmlAttribute.
     */
    XmlAttributePtr getNext();

    /**
     * @brief Remove this XmlAttribute from its parent XmlNode.
     *
     * Remove this XmlAttribute from its parent XmlNode.
     */
    void removeAttribute();

private:
    struct XmlAttributeImpl; /**< Forward declaration for pImpl idiom. */
    XmlAttributeImpl *mPimpl; /**< Private member to implementation pointer */
};

}

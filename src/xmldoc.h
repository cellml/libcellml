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

#include "xmlnode.h"

namespace libcellml {

class XmlDoc; /**< Forward declaration of the internal XmlDoc class. */
typedef std::shared_ptr<XmlDoc> XmlDocPtr; /**< Type definition for shared XML doc pointer. */

/**
 * @brief The XmlDoc class.
 *
 * The XmlDoc class is a wrapper class for operations on
 * xmlDoc objects from libxml2.
 */
class XmlDoc
{
public:
    XmlDoc(); /**< Constructor */
    ~XmlDoc(); /**< Destructor */

    /**
     * @brief Parse an XML document from a string.
     *
     * Parses the @p input @c std::string as an XML document.
     *
     * @param input The @c std::string to parse.
     */
    void parse(const std::string &input);

    /**
     * @brief Parse an XML string as MathML.
     *
     * Parses the @p input @c std::string as a MathML string.
     *
     * @param input The @c std::string to parse.
     */
    void parseMathML(const std::string &input);

    /**
     * @brief Get the root XML element of the document.
     *
     * Get the root XML element for this XML document as a
     * returned @c XMLNodePtr.
     *
     * @return The root XML element for this document.
     */
    XmlNodePtr getRootNode() const;

    /**
     * @brief Add an @p error raised while parsing this XML document.
     *
     * Adds the @p error raise while parsing this XML document to the
     * list of @c mXmlErrors. These errors will pertain to the ability
     * of libxml to parse a given document.
     *
     * @param error The XML error string to add.
     */
    void addXmlError(const std::string &error);

    /**
     * @brief Count the number of XML errors in this document.
     *
     * Returns the number of XML errors raised while parsing
     * this document.
     *
     * @return The number of XML errors.
     */
    size_t xmlErrorCount() const;

    /**
     * @brief Get a XML error at index.
     *
     * Returns the @c std::string message pertaining to the error
     * at the @p index raised by libxml during parsing.
     *
     * @param index The index of the error to get.
     * @return The @c std::string form of the XML error.
     */
    std::string getXmlError(size_t index) const;

private:
    struct XmlDocImpl; /**< Forward declaration for pImpl idiom. */
    XmlDocImpl *mPimpl; /**< Private member to implementation pointer */
};

}

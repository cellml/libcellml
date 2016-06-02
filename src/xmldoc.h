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

#ifndef XMLDOC_H
#define XMLDOC_H

#include <string>
#include "libcellml/types.h"
//#include "xmlnode.h"

namespace libcellml {

//class XmlDoc; /**< Forward declaration of XmlDoc class. */
//typedef std::shared_ptr<XmlDoc> XmlDocPtr; /**< Type definition for shared XML doc pointer. */

/**
 * @brief The XmlDoc class.
 *
 * The XmlDoc class is a wrapper class for operations on
 * xmlDoc objects from libXML2.
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
    void parse(const std::string& input);

    /**
     * @brief Get the root XML element of the document.
     *
     * Get the root XML element for this XML document as a
     * returned @c XMLNodePtr.
     *
     * @return The root XML element for this document.
     */
    XmlNodePtr getRootNode() const;

private:
    struct XmlDocImpl; /**< Forward declaration for pImpl idiom. */
    XmlDocImpl* mPimpl; /**< Private member to implementation pointer */
};

}

#endif // XMLDOC_H

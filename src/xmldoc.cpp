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

#include <string>
#include <cstring>
#include <libxml/parser.h>
#include <libxml/tree.h>

#include "xmldoc.h"
#include "xmlnode.h"

namespace libcellml {

/**
 * @brief The XmlDoc::XmlDocImpl struct.
 *
 * This struct is the private implementation struct for the XmlDoc class.  Separating
 * the implementation from the definition allows for greater flexibility when
 * distributing the code.
 */
struct XmlDoc::XmlDocImpl
{
    xmlDocPtr mXmlDocPtr;
};

XmlDoc::XmlDoc()
    : mPimpl(new XmlDocImpl())
{
}

XmlDoc::~XmlDoc()
{
    if (mPimpl->mXmlDocPtr) {
        xmlFreeDoc(mPimpl->mXmlDocPtr);
    }
    delete mPimpl;
}

void XmlDoc::parse(const std::string& input)
{
    if (input.length() > 0) {
        mPimpl->mXmlDocPtr = xmlParseDoc(BAD_CAST input.c_str());
        if (mPimpl->mXmlDocPtr == NULL) {
            throw std::invalid_argument("Error parsing XML string: " + input);
        }
    } else {
        throw std::invalid_argument("XML string empty.");
    }
}

XmlNodePtr XmlDoc::getRootNode() const
{
    xmlNodePtr root = xmlDocGetRootElement(mPimpl->mXmlDocPtr);
//    ASSERT(root != NULL);
//    if (root == NULL) {
//        Cannot get here when parsing a string.
//        throw std::invalid_argument("XML document empty.");
//    }
    XmlNodePtr rootHandle = std::make_shared<XmlNode>();
    rootHandle->setXmlNode(root);
    return rootHandle;
}

}

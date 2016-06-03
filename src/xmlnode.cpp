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
#include <libxml/parser.h>
#include <libxml/tree.h>

#include "xmlnode.h"

namespace libcellml {

/**
 * @brief The XmlNode::XmlNodeImpl struct.
 *
 * This struct is the private implementation struct for the XmlNode class.  Separating
 * the implementation from the definition allows for greater flexibility when
 * distributing the code.
 */
struct XmlNode::XmlNodeImpl
{
    xmlNodePtr mXmlNodePtr;
};

XmlNode::XmlNode()
    : mPimpl(new XmlNodeImpl())
{
}

XmlNode::~XmlNode()
{
    delete mPimpl;
}

void XmlNode::setXmlNode(const xmlNodePtr &node)
{
    mPimpl->mXmlNodePtr = node;
}

bool XmlNode::isElementType(const char *elementName)
{
    bool found = false;
    if (!xmlStrcmp(mPimpl->mXmlNodePtr->name, BAD_CAST elementName)) found = true;
    return found;
}

bool XmlNode::hasAttribute(const char *attributeName)
{
    bool found = false;
    xmlAttrPtr attribute = xmlHasProp(mPimpl->mXmlNodePtr, BAD_CAST attributeName);
    if (attribute) found = true;
    return found;
}

std::string XmlNode::getAttribute(const char *attributeName)
{
    char* attributeValue = (char*)xmlGetProp(mPimpl->mXmlNodePtr, BAD_CAST attributeName);
    std::string attributeValueString = std::string(attributeValue);
    xmlFree(attributeValue);
    return attributeValueString;
}

XmlNodePtr XmlNode::getChild()
{
    xmlNodePtr child = mPimpl->mXmlNodePtr->xmlChildrenNode;
    XmlNodePtr childHandle = std::make_shared<XmlNode>();
    childHandle->setXmlNode(child);
    if (child == NULL) childHandle = nullptr;
    return childHandle;
}

XmlNodePtr XmlNode::getNext()
{
    xmlNodePtr next = mPimpl->mXmlNodePtr->next;
    XmlNodePtr nextHandle = std::make_shared<XmlNode>();
    nextHandle->setXmlNode(next);
    if (next == NULL) nextHandle = nullptr;
    return nextHandle;
}

std::string XmlNode::convertToString() {
    char* content = (char*)xmlNodeGetContent(mPimpl->mXmlNodePtr);
    std::string contentString = std::string(content);
    xmlFree(content);
    return contentString;
}

}

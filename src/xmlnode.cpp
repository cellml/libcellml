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

#include "xmlattribute.h"
#include "xmlnode.h"

#include "libcellml/namespaces.h"

#include <string>

#include <libxml/parser.h>
#include <libxml/tree.h>

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

std::string XmlNode::getNamespace() const
{
    if (!mPimpl->mXmlNodePtr->ns) {
        return std::string();
    }
    return std::string(reinterpret_cast<const char *>(mPimpl->mXmlNodePtr->ns->href));
}

bool XmlNode::isElement(const char *name, const char *ns)
{
    bool found = false;
    if (    (mPimpl->mXmlNodePtr->type == XML_ELEMENT_NODE)
        && !xmlStrcmp(BAD_CAST getNamespace().c_str(), BAD_CAST ns)
        && !xmlStrcmp(mPimpl->mXmlNodePtr->name, BAD_CAST name)) {
        found = true;
    }
    return found;
}

bool XmlNode::isCellmlElement(const char *name)
{
    return isElement(name, CELLML_2_0_NS);
}

bool XmlNode::isMathmlElement(const char *name)
{
    return isElement(name, MATHML_NS);
}

bool XmlNode::isText()
{
    return mPimpl->mXmlNodePtr->type == XML_TEXT_NODE;
}

bool XmlNode::isComment()
{
    return mPimpl->mXmlNodePtr->type == XML_COMMENT_NODE;
}

std::string XmlNode::getName() const
{
    return std::string(reinterpret_cast<const char *>(mPimpl->mXmlNodePtr->name));
}

bool XmlNode::hasAttribute(const char *attributeName)
{
    bool found = false;
    xmlAttrPtr attribute = xmlHasProp(mPimpl->mXmlNodePtr, BAD_CAST attributeName);
    if (attribute) {
        found = true;
    }
    return found;
}

std::string XmlNode::getAttribute(const char *attributeName)
{
    std::string attributeValueString;
    if (hasAttribute(attributeName)) {
        xmlChar *attributeValue = xmlGetProp(mPimpl->mXmlNodePtr, BAD_CAST attributeName);
        attributeValueString = std::string(reinterpret_cast<const char *>(attributeValue));
        xmlFree(attributeValue);
    }
    return attributeValueString;
}

XmlAttributePtr XmlNode::getFirstAttribute()
{
    xmlAttrPtr attribute = mPimpl->mXmlNodePtr->properties;
    XmlAttributePtr attributeHandle = nullptr;
    if (attribute) {
        attributeHandle = std::make_shared<XmlAttribute>();
        attributeHandle->setXmlAttribute(attribute);
    }
    return attributeHandle;
}

XmlNodePtr XmlNode::getFirstChild()
{
    xmlNodePtr child = mPimpl->mXmlNodePtr->children;
    XmlNodePtr childHandle = nullptr;
    if (child) {
        childHandle = std::make_shared<XmlNode>();
        childHandle->setXmlNode(child);
    }
    return childHandle;
}

XmlNodePtr XmlNode::getNext()
{
    xmlNodePtr next = mPimpl->mXmlNodePtr->next;
    XmlNodePtr nextHandle = nullptr;
    if (next) {
        nextHandle = std::make_shared<XmlNode>();
        nextHandle->setXmlNode(next);
    }
    return nextHandle;
}

XmlNodePtr XmlNode::getParent()
{
    xmlNodePtr parent = mPimpl->mXmlNodePtr->parent;
    XmlNodePtr parentHandle = nullptr;
    if (parent) {
        parentHandle = std::make_shared<XmlNode>();
        parentHandle->setXmlNode(parent);
    }
    return parentHandle;
}

std::string XmlNode::convertToString() {
    std::string contentString;
    xmlBufferPtr buffer = xmlBufferCreate();
    int len = xmlNodeDump(buffer, mPimpl->mXmlNodePtr->doc, mPimpl->mXmlNodePtr, 0, 0);
    if (len > 0) {
        contentString = std::string(reinterpret_cast<const char *>(buffer->content));
    }
    xmlBufferFree(buffer);
    return contentString;
}

}

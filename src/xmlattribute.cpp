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

#include "xmlattribute.h"

namespace libcellml {

/**
 * @brief The XmlAttribute::XmlAttributeImpl struct.
 *
 * This struct is the private implementation struct for the XmlAttribute class.  Separating
 * the implementation from the definition allows for greater flexibility when
 * distributing the code.
 */
struct XmlAttribute::XmlAttributeImpl
{
    xmlAttrPtr mXmlAttributePtr;
};

XmlAttribute::XmlAttribute()
    : mPimpl(new XmlAttributeImpl())
{
}

XmlAttribute::~XmlAttribute()
{
    delete mPimpl;
}

void XmlAttribute::setXmlAttribute(const xmlAttrPtr &attribute)
{
    mPimpl->mXmlAttributePtr = attribute;
}

bool XmlAttribute::isAttributeType(const char *attributeName)
{
    bool found = false;
    if (!xmlStrcmp(mPimpl->mXmlAttributePtr->name, BAD_CAST attributeName)) found = true;
    return found;
}

std::string XmlAttribute::getAttributeType() const
{
    const char* type = reinterpret_cast<const char*>(mPimpl->mXmlAttributePtr->name);
    return std::string(type);
}

XmlAttributePtr XmlAttribute::getNext()
{
    xmlAttrPtr next = mPimpl->mXmlAttributePtr->next;
    XmlAttributePtr nextHandle = std::make_shared<XmlAttribute>();
    nextHandle->setXmlAttribute(next);
    if (next == NULL) nextHandle = nullptr;
    return nextHandle;
}

}

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

#include "namespaces.h"
#include "xmlattribute.h"

#include <string>

#include <libxml/parser.h>
#include <libxml/tree.h>

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

std::string XmlAttribute::getNamespace() const
{
    if (mPimpl->mXmlAttributePtr->ns == nullptr) {
        return std::string();
    }
    return std::string(reinterpret_cast<const char *>(mPimpl->mXmlAttributePtr->ns->href));
}

bool XmlAttribute::isType(const char *name, const char *ns)
{
    bool found = false;
    if ((xmlStrcmp(reinterpret_cast<const xmlChar *>(getNamespace().c_str()), reinterpret_cast<const xmlChar *>(ns)) == 0)
        && (xmlStrcmp(mPimpl->mXmlAttributePtr->name, reinterpret_cast<const xmlChar *>(name)) == 0)) {
        found = true;
    }
    return found;
}

bool XmlAttribute::isCellmlType(const char *name)
{
    return isType(name, CELLML_2_0_NS);
}

std::string XmlAttribute::getName() const
{
    std::string type;
    if (mPimpl->mXmlAttributePtr->name != nullptr) {
        type = std::string(reinterpret_cast<const char *>(mPimpl->mXmlAttributePtr->name));
    }
    return type;
}

std::string XmlAttribute::getValue() const
{
    std::string valueString;
    if ((mPimpl->mXmlAttributePtr->name != nullptr) && (mPimpl->mXmlAttributePtr->parent != nullptr)) {
        xmlChar *value = xmlGetProp(mPimpl->mXmlAttributePtr->parent, mPimpl->mXmlAttributePtr->name);
        valueString = std::string(reinterpret_cast<const char *>(value));
        xmlFree(value);
    }
    return valueString;
}

XmlAttributePtr XmlAttribute::getNext()
{
    xmlAttrPtr next = mPimpl->mXmlAttributePtr->next;
    XmlAttributePtr nextHandle = nullptr;
    if (next != nullptr) {
        nextHandle = std::make_shared<XmlAttribute>();
        nextHandle->setXmlAttribute(next);
    }
    return nextHandle;
}

void XmlAttribute::removeAttribute()
{
    xmlRemoveProp(mPimpl->mXmlAttributePtr);
}

} // namespace libcellml

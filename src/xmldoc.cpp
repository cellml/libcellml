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

#include "xmldoc.h"

#include <cstring>
#include <libxml/tree.h>
#include <libxml/xmlerror.h>
#include <string>
#include <vector>

#include "mathmlconfig.h"
#include "xmlnode.h"

namespace libcellml {

/**
 * @brief Callback for errors from the libxml2 context parser.
 *
 * Structured callback @c xmlStructuredErrorFunc for errors
 * from the libxml2 context parser used to parse this document.
 *
 * @param userData Private data type used to store the libxml context.
 *
 * @param error The @c xmlErrorPtr to the error raised by libxml.
 */
void structuredErrorCallback(void *userData, xmlErrorPtr error)
{
    std::string errorString = std::string(error->message);
    // Swap libxml2 carriage return for a period.
    if (errorString.substr(errorString.length() - 1) == "\n") {
        errorString.replace(errorString.end() - 1, errorString.end(), ".");
    }
    auto context = reinterpret_cast<xmlParserCtxtPtr>(userData);
    auto doc = reinterpret_cast<XmlDoc *>(context->_private);
    doc->addXmlError(errorString);
}

/**
 * @brief The XmlDoc::XmlDocImpl struct.
 *
 * This struct is the private implementation struct for the XmlDoc class.  Separating
 * the implementation from the definition allows for greater flexibility when
 * distributing the code.
 */
struct XmlDoc::XmlDocImpl
{
    xmlDocPtr mXmlDocPtr = nullptr;
    std::vector<std::string> mXmlErrors;
};

XmlDoc::XmlDoc()
    : mPimpl(new XmlDocImpl())
{
}

XmlDoc::~XmlDoc()
{
    if (mPimpl->mXmlDocPtr != nullptr) {
        xmlFreeDoc(mPimpl->mXmlDocPtr);
    }
    delete mPimpl;
}

void XmlDoc::parse(const std::string &input)
{
    xmlInitParser();
    xmlParserCtxtPtr context = xmlNewParserCtxt();
    context->_private = reinterpret_cast<void *>(this);
    xmlSetStructuredErrorFunc(context, structuredErrorCallback);
    mPimpl->mXmlDocPtr = xmlCtxtReadDoc(context, reinterpret_cast<const xmlChar *>(input.c_str()), "/", nullptr, 0);
    xmlFreeParserCtxt(context);
    xmlSetStructuredErrorFunc(nullptr, nullptr);
    xmlCleanupParser();
    xmlCleanupGlobals();
}

void XmlDoc::parseMathML(const std::string &input)
{
    xmlInitParser();
    std::string mathmlDtd = "<!DOCTYPE math SYSTEM \"" + LIBCELLML_MATHML_DTD_LOCATION + "\">";
    std::string mathmlString = mathmlDtd + input;
    xmlParserCtxtPtr context = xmlNewParserCtxt();
    context->_private = reinterpret_cast<void *>(this);
    xmlSetStructuredErrorFunc(context, structuredErrorCallback);
    mPimpl->mXmlDocPtr = xmlCtxtReadDoc(context, reinterpret_cast<const xmlChar *>(mathmlString.c_str()), "/", nullptr, XML_PARSE_DTDVALID);
    xmlFreeParserCtxt(context);
    xmlSetStructuredErrorFunc(nullptr, nullptr);
    xmlCleanupParser();
    xmlCleanupGlobals();
}

XmlNodePtr XmlDoc::rootNode() const
{
    xmlNodePtr root = xmlDocGetRootElement(mPimpl->mXmlDocPtr);
    XmlNodePtr rootHandle = nullptr;
    if (root != nullptr) {
        rootHandle = std::make_shared<XmlNode>();
        rootHandle->setXmlNode(root);
    }
    return rootHandle;
}

void XmlDoc::addXmlError(const std::string &error)
{
    mPimpl->mXmlErrors.push_back(error);
}

size_t XmlDoc::xmlErrorCount() const
{
    return mPimpl->mXmlErrors.size();
}

std::string XmlDoc::xmlError(size_t index) const
{
    return mPimpl->mXmlErrors.at(index);
}

} // namespace libcellml

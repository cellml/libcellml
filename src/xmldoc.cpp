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
#include <regex>
#include <sstream>
#include <string>
#include <vector>

#include <zlib.h>

#include "internaltypes.h"
#include "mathmldtd.h"
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
void structuredErrorCallback(void *userData, XML_ERROR_CALLBACK_ARGUMENT_TYPE error)
{
    static const std::regex newLineRegex("\\n");
    // Swap libxml2 carriage return for a period.
    std::string errorString = std::regex_replace(error->message, newLineRegex, ".");
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
    Strings mXmlErrors;
    size_t bufferPointer = 0;
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
}

std::string decompressMathMLDTD()
{
    std::vector<unsigned char> mathmlDTD;
    uLong sizeMathmlDTDUncompressedResize = MATHML_DTD_LEN;
    mathmlDTD.resize(sizeMathmlDTDUncompressedResize);

    const unsigned char *a = compressedMathMLDTD();

    uncompress(&mathmlDTD[0], &sizeMathmlDTDUncompressedResize, a, COMPRESSED_MATHML_DTD_LEN);

    return std::string(mathmlDTD.begin(), mathmlDTD.end());
}

/**
 * @brief The parsed MathML DTD.
 *
 * Parsing the MathML DTD is expensive (it is about 390 KB long), so we parse it only once rather than every time that
 * we validate some MathML. However, libxml2 builds (and caches) the content model of an element declaration the first
 * time that it validates an element against it, i.e. validating against a DTD modifies it, so we have one parsed MathML
 * DTD per thread.
 *
 * Note: this is why we never call xmlCleanupParser(). It is a process-wide operation that must only be called once
 *       libxml2 is no longer used (typically when an application exits) while a cached DTD may outlive any given call.
 */
class MathmlDtd
{
public:
    MathmlDtd()
    {
        auto mathmlDTD = decompressMathMLDTD();
        xmlParserInputBufferPtr buf = xmlParserInputBufferCreateMem(mathmlDTD.c_str(), static_cast<int>(mathmlDTD.size()), XML_CHAR_ENCODING_ASCII);

        mDtd = xmlIOParseDTD(nullptr, buf, XML_CHAR_ENCODING_ASCII);
    }

    ~MathmlDtd()
    {
        xmlFreeDtd(mDtd);
    }

    MathmlDtd(const MathmlDtd &) = delete;
    MathmlDtd &operator=(const MathmlDtd &) = delete;

    xmlDtdPtr dtd() const
    {
        return mDtd;
    }

private:
    xmlDtdPtr mDtd = nullptr;
};

void XmlDoc::parseMathML(const std::string &input)
{
    xmlInitParser();

    thread_local MathmlDtd mathmlDtd;

    xmlParserCtxtPtr context = xmlNewParserCtxt();
    context->_private = reinterpret_cast<void *>(this);
    xmlSetStructuredErrorFunc(context, structuredErrorCallback);
    mPimpl->mXmlDocPtr = xmlCtxtReadDoc(context, reinterpret_cast<const xmlChar *>(input.c_str()), "/", nullptr, 0);
    xmlValidateDtd(&(context->vctxt), mPimpl->mXmlDocPtr, mathmlDtd.dtd());

    xmlFreeParserCtxt(context);
    xmlSetStructuredErrorFunc(nullptr, nullptr);
}

std::string XmlDoc::prettyPrint() const
{
    xmlChar *buffer;
    int size = 0;
    xmlDocDumpFormatMemoryEnc(mPimpl->mXmlDocPtr, &buffer, &size, "UTF-8", 1);
    std::stringstream res;
    res << buffer;
    xmlFree(buffer);
    return res.str();
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


#include <iostream>
#include <libxml/parser.h>
#include <libxml/xmlerror.h>

void structuredErrorCallback(void *userData, xmlErrorPtr error)
{
    std::string errorString = std::string(error->message);
    // Swap libxml2 carriage return for a period.
    if (errorString.substr(errorString.length() - 1) == "\n") {
        errorString.replace(errorString.end() - 1, errorString.end(), ".");
    }
    std::cout << errorString << std::endl;
}

int main(int argc, char *argv[])
{
  const char *input = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n<ci cellml:units=\"dimensionless\">B</ci>";
  xmlParserCtxtPtr context = xmlNewParserCtxt();
  xmlSetStructuredErrorFunc(context, structuredErrorCallback);
  xmlDocPtr xmlDoc = xmlCtxtReadDoc(context, reinterpret_cast<const xmlChar *>(input), "/", nullptr, 0);
  xmlFreeParserCtxt(context);
  xmlSetStructuredErrorFunc(nullptr, nullptr);
  xmlFreeDoc(xmlDoc);
}

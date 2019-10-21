
#include <iostream>	
#include <libxml/parser.h>	
#include <libxml/xmlerror.h>	
#include <mathmlconfig.h>	

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
  const std::string input = "<math><ci cellml:units=\"dimensionless\">B</ci></math>";
  const std::string mathmlDtd = "<!DOCTYPE math SYSTEM \"" + libcellml::LIBCELLML_MATHML_DTD_LOCATION + "\">";	
  std::string mathmlString = mathmlDtd + input;	
  xmlInitParser();
  xmlParserCtxtPtr context = xmlNewParserCtxt();	
  xmlSetStructuredErrorFunc(context, structuredErrorCallback);	
  xmlDocPtr xmlDoc = xmlCtxtReadDoc(context, reinterpret_cast<const xmlChar *>(mathmlString.c_str()), "/", nullptr, XML_PARSE_DTDVALID);	
  xmlFreeParserCtxt(context);	
  xmlSetStructuredErrorFunc(nullptr, nullptr);	
  xmlFreeDoc(xmlDoc);
  xmlCleanupParser();
  xmlCleanupGlobals();	
}


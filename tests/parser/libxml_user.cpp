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

#include "gtest/gtest.h"

#include <algorithm>
#include <iostream>
#include <libcellml>
#include <string>
#include <vector>
#include <libxml/parser.h>

TEST(Parser, parseValidXmlDirectlyUsingLibxml) {
    const std::string e =
            "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
            "<model xmlns=\"http://www.cellml.org/cellml/2.0#\"/>";

    // parse the string using libcellml
    libcellml::Parser parser;
    libcellml::ModelPtr model = parser.parseModel(e);
    libcellml::Printer printer;
    const std::string a = printer.printModel(model);
    EXPECT_EQ(e, a);

    // and now parse directly using libxml2
    xmlParserCtxtPtr context = xmlNewParserCtxt();
    xmlDocPtr doc = xmlCtxtReadDoc(context, BAD_CAST e.c_str(), "/", nullptr, 0);
    xmlFreeParserCtxt(context);
    EXPECT_NE(nullptr, doc);
    xmlFreeDoc(doc);
}

TEST(Parser, parseInvalidXmlDirectlyUsingLibxml) {
    const std::string e =
            "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
            "<model xmlns=\"http://www.cellml.org/cellml/2.0#\"><component></model>";

    // parse the string using libcellml
    libcellml::Parser parser;
    libcellml::ModelPtr model = parser.parseModel(e);
    EXPECT_NE(0, parser.errorCount());

    // and now parse directly using libxml2
    xmlParserCtxtPtr context = xmlNewParserCtxt();
    xmlDocPtr doc = xmlCtxtReadDoc(context, BAD_CAST e.c_str(), "/", nullptr, 0);
    xmlFreeParserCtxt(context);
    EXPECT_EQ(nullptr, doc);
}



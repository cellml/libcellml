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

#include "test_utils.h"

#include "gtest/gtest.h"

#include <libcellml>

TEST(ParserTransform, emptyCellml_1_1)
{
    const std::string e =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/1.1#\"/>\n";

    libcellml::ParserPtr parser = libcellml::Parser::create();
    libcellml::ModelPtr model = parser->parseModel(e);
    EXPECT_EQ(size_t(1), parser->issueCount());
    EXPECT_EQ(libcellml::Issue::Level::MESSAGE, parser->issue(0)->level());
    EXPECT_EQ("Given model is a CellML 1.1 model, the parser will try to represent this model in CellML 2.0.", parser->issue(0)->description());
}

TEST(ParserTransform, parseNamedModelCellml_1_1)
{
    const std::string n = "name";
    const std::string e =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/1.1#\" name=\"name\"/>\n";

    libcellml::ParserPtr parser = libcellml::Parser::create();
    libcellml::ModelPtr model = parser->parseModel(e);
    EXPECT_EQ(n, model->name());
}

TEST(ParserTransform, sineCellml_1_1)
{
    const std::string e =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/2.0#\" name=\"sin\" id=\"sin\">\n"
        "  <component name=\"sin\" id=\"sin\">\n"
        "    <variable name=\"x\" units=\"dimensionless\" interface=\"public_and_private\"/>\n"
        "    <variable name=\"sin\" units=\"dimensionless\" interface=\"public_and_private\" id=\"sin\"/>\n"
        "    <math xmlns=\"http://www.w3.org/1998/Math/MathML\">\n"
        "      <apply id=\"actual_sin\">\n"
        "        <eq/>\n"
        "        <ci>sin</ci>\n"
        "        <apply>\n"
        "          <sin/>\n"
        "          <ci>x</ci>\n"
        "        </apply>\n"
        "      </apply>\n"
        "    </math>\n"
        "  </component>\n"
        "</model>\n";

    libcellml::ParserPtr parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("cellml11/sin.xml"));

    EXPECT_EQ(size_t(2), parser->issueCount());

    auto printer = libcellml::Printer::create();
    auto a = printer->printModel(model);
    EXPECT_EQ(e, a);
}

TEST(ParserTransform, derivedApproxSineCellml_1_1)
{
    const std::string e =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/2.0#\" name=\"deriv_approx_sin\" id=\"deriv_approx_sin\">\n"
        "  <component name=\"sin\" id=\"sin\">\n"
        "    <variable name=\"x\" units=\"dimensionless\" interface=\"public_and_private\" id=\"x\"/>\n"
        "    <variable name=\"sin\" units=\"dimensionless\" initial_value=\"sin_initial_value\" interface=\"public_and_private\" id=\"sin\"/>\n"
        "    <variable name=\"sin_initial_value\" units=\"dimensionless\" interface=\"public_and_private\"/>\n"
        "    <math xmlns=\"http://www.w3.org/1998/Math/MathML\">\n"
        "      <apply>\n"
        "        <eq/>\n"
        "        <apply>\n"
        "          <diff/>\n"
        "          <bvar>\n"
        "            <ci>x</ci>\n"
        "          </bvar>\n"
        "          <ci>sin</ci>\n"
        "        </apply>\n"
        "        <apply>\n"
        "          <cos/>\n"
        "          <ci>x</ci>\n"
        "        </apply>\n"
        "      </apply>\n"
        "    </math>\n"
        "  </component>\n"
        "</model>\n";

    libcellml::ParserPtr parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("cellml11/deriv_approx_sin.xml"));

    EXPECT_EQ(size_t(2), parser->issueCount());

    auto printer = libcellml::Printer::create();
    auto a = printer->printModel(model);
    EXPECT_EQ(e, a);
}

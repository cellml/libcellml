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

#include <algorithm>
#include <fstream>
#include <iostream>
#include <libcellml>
#include <sstream>
#include <vector>

TEST(Parser, parseSineModelFromFile)
{
    libcellml::Parser p;
    p.parseModel(fileContents("sine_approximations.xml"));

    EXPECT_EQ(size_t(0), p.errorCount());
}

TEST(Parser, parseSineImportsModelFromFile)
{
    libcellml::Parser p;
    p.parseModel(fileContents("sine_approximations_import.xml"));

    EXPECT_EQ(size_t(0), p.errorCount());
}

TEST(Parser, parseInvalidModelFromFile)
{
    const std::vector<std::string> expectedErrors = {
        "Start tag expected, '<' not found.",
        "Could not get a valid XML root node from the provided input.",
    };

    libcellml::Parser p;
    p.parseModel(fileContents("invalid_cellml_2.0.xml"));

    EXPECT_EQ_ERRORS(expectedErrors, p);
}

TEST(Parser, parseOrdModelFromFile)
{
    libcellml::Parser p;
    libcellml::ModelPtr model = p.parseModel(fileContents("Ohara_Rudy_2011.cellml"));

    EXPECT_EQ(size_t(0), p.errorCount());

    // Test some random values.
    std::string a = model->component("intracellular_ions")->variable("BSLmax")->initialValue();
    EXPECT_EQ("1.124", a);

    a = model->component("INa")->variable("mtD2")->initialValue();
    EXPECT_EQ("8.552", a);

    a = model->component("IK1")->variable("GK1_b")->initialValue();
    EXPECT_EQ("0.1908", a);

    a = model->component("SERCA")->variable("Jup")->interfaceType();
    EXPECT_EQ("public", a);
}

TEST(Parser, parseComplexEncapsulationModelFromFile)
{
    // This test resulted from https://github.com/cellml/libcellml/issues/170
    libcellml::Parser p;
    p.parseModel(fileContents("complex_encapsulation.xml"));

    EXPECT_EQ(size_t(0), p.errorCount());
}

TEST(Parser, parseModelWithComponentsWithMultipleMathElements)
{
    // This test resulted from https://github.com/cellml/libcellml/issues/183
    const std::string e1 =
        "<math xmlns=\"http://www.w3.org/1998/Math/MathML\">\n"
        "  <apply>\n"
        "    <eq/>\n"
        "    <ci>a1</ci>\n"
        "    <apply>\n"
        "      <plus/>\n"
        "      <ci>b1</ci>\n"
        "      <ci>c1</ci>\n"
        "    </apply>\n"
        "  </apply>\n"
        "</math>\n";
    const std::string e2 =
        "<math xmlns=\"http://www.w3.org/1998/Math/MathML\">\n"
        "  <apply>\n"
        "    <eq/>\n"
        "    <ci>b2</ci>\n"
        "    <apply>\n"
        "      <times/>\n"
        "      <cn xmlns:cellml=\"http://www.cellml.org/cellml/2.0#\" cellml:units=\"dimensionless\">2.0</cn>\n"
        "      <ci>d</ci>\n"
        "    </apply>\n"
        "  </apply>\n"
        "</math>\n"
        "<math xmlns=\"http://www.w3.org/1998/Math/MathML\">\n"
        "  <apply>\n"
        "    <eq/>\n"
        "    <ci>d</ci>\n"
        "    <cn xmlns:cellml=\"http://www.cellml.org/cellml/2.0#\" cellml:units=\"dimensionless\" type=\"e-notation\">0.5<sep/>1</cn>\n"
        "  </apply>\n"
        "</math>\n";

    libcellml::Parser p;
    libcellml::ModelPtr model = p.parseModel(fileContents("a_plus_b.cellml"));
    EXPECT_EQ(size_t(0), p.errorCount());

    std::string a = model->component("c1")->math();
    EXPECT_EQ(e1, a);

    a = model->component("c2")->math();
    EXPECT_EQ(e2, a);
}

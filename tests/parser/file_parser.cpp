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
#include <fstream>
#include <iostream>
#include <libcellml>
#include <sstream>
#include <vector>

// generated with test resource locations
#include "test_resources.h"

TEST(Parser, parseSineModelFromFile) {
    std::ifstream t(TestResources::getLocation(
                    TestResources::CELLML_SINE_MODEL_RESOURCE));
    std::stringstream buffer;
    buffer << t.rdbuf();

    libcellml::Parser p;
    p.parseModel(buffer.str());

    EXPECT_EQ(0, p.errorCount());
}

TEST(Parser, parseSineImportsModelFromFile) {
    std::ifstream t(TestResources::getLocation(
                    TestResources::CELLML_SINE_IMPORTS_MODEL_RESOURCE));
    std::stringstream buffer;
    buffer << t.rdbuf();

    libcellml::Parser p;
    p.parseModel(buffer.str());

    EXPECT_EQ(0, p.errorCount());
}

TEST(Parser, parseInvalidModelFromFile) {
    std::ifstream t(TestResources::getLocation(
                    TestResources::CELLML_INVALID_MODEL_RESOURCE));
    std::stringstream buffer;
    buffer << t.rdbuf();

    std::vector<std::string> expectedErrors = {
        "Start tag expected, '<' not found.",
        "Could not get a valid XML root node from the provided input."
    };

    libcellml::Parser p;
    p.parseModel(buffer.str());

    EXPECT_EQ(expectedErrors.size(), p.errorCount());
    for (size_t i = 0; i < p.errorCount(); ++i) {
        EXPECT_EQ(expectedErrors.at(i), p.getError(i)->getDescription());
    }
}

TEST(Parser, parseOrdModelFromFile) {
    std::ifstream t(TestResources::getLocation(
                    TestResources::CELLML_ORD_MODEL_RESOURCE));
    std::stringstream buffer;
    buffer << t.rdbuf();

    libcellml::Parser p;
    libcellml::ModelPtr model = p.parseModel(buffer.str());

    EXPECT_EQ(0, p.errorCount());

    // Test some random values.
    std::string a = model->getComponent("intracellular_ions")->getVariable("BSLmax")->getInitialValue();
    EXPECT_EQ("1.124", a);

    a = model->getComponent("INa")->getVariable("mtD2")->getInitialValue();
    EXPECT_EQ("8.552", a);

    a = model->getComponent("IK1")->getVariable("GK1_b")->getInitialValue();
    EXPECT_EQ("0.1908", a);

    a = model->getComponent("SERCA")->getVariable("Jup")->getInterfaceType();
    EXPECT_EQ("public", a);
}

TEST(Parser, parseComplexEncapsulationModelFromFile) {
    // This test resulted from https://github.com/cellml/libcellml/issues/170
    std::ifstream t(TestResources::getLocation(
                    TestResources::CELLML_COMPLEX_ENCAPSULATION_MODEL_RESOURCE));
    std::stringstream buffer;
    buffer << t.rdbuf();

    libcellml::Parser p;
    p.parseModel(buffer.str());

    EXPECT_EQ(0, p.errorCount());
}

TEST(Parser, parseModelWithComponentsWithMultipleMathElements) {
    // This test resulted from https://github.com/cellml/libcellml/issues/183

    std::string e1 = "<math xmlns=\"http://www.w3.org/1998/Math/MathML\">\n\t\t\t<apply><eq/>\n\t\t\t\t<ci>a1</ci>\n\t\t\t\t<apply><plus/>\n\t\t\t\t\t<ci>b1</ci>\n\t\t\t\t\t<ci>c1</ci>\n\t\t\t\t</apply>\n\t\t\t</apply>\n\t\t</math>";
    std::string e2 = "<math xmlns=\"http://www.w3.org/1998/Math/MathML\">\n\t\t\t<apply><eq/>\n\t\t\t\t<ci>b2</ci>\n\t\t\t\t<apply><times/>\n\t\t\t\t\t<cn xmlns:cellml=\"http://www.cellml.org/cellml/2.0#\" cellml:units=\"dimensionless\">2.0</cn>\n\t\t\t\t\t<ci>d</ci>\n\t\t\t\t</apply>\n\t\t\t</apply>\n\t\t</math><math xmlns=\"http://www.w3.org/1998/Math/MathML\">\n\t\t\t<apply><eq/>\n\t\t\t\t<ci>d</ci>\n\t\t\t\t<cn xmlns:cellml=\"http://www.cellml.org/cellml/2.0#\" cellml:units=\"dimensionless\" type=\"e-notation\">0.5<sep/>1</cn>\n\t\t\t</apply>\n\t\t</math>";

    std::ifstream t(TestResources::getLocation(
                    TestResources::CELLML_A_PLUS_B_MODEL_RESOURCE));
    std::stringstream buffer;
    buffer << t.rdbuf();

    libcellml::Parser p;
    libcellml::ModelPtr model = p.parseModel(buffer.str());
    EXPECT_EQ(0, p.errorCount());

    std::string a = model->getComponent("c1")->getMath();
    EXPECT_EQ(e1, a);

    a = model->getComponent("c2")->getMath();
    EXPECT_EQ(e2, a);
}


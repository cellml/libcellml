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

#include <libcellml>

TEST(Maths, setAndGetMath) {
    std::string math = "<math xmlns=\"http://www.w3.org/1998/Math/MathML\"/>";
    libcellml::Component c;
    c.setMath(math);
    EXPECT_EQ(math, c.getMath());
}

TEST(Maths, appendAndSerialiseMathComponent) {
    const std::string e =
            "<component>"
                "<math xmlns=\"http://www.w3.org/1998/Math/MathML\"/>"
            "</component>";

    std::string math = "<math xmlns=\"http://www.w3.org/1998/Math/MathML\"/>";

    libcellml::Component c;
    c.appendMath(math);

    libcellml::Printer printer;
    const std::string a = printer.printComponent(c);
    EXPECT_EQ(e, a);
}

TEST(Maths, appendAndResetMathComponent) {
    const std::string e = "<component/>";

    std::string math = "<math xmlns=\"http://www.w3.org/1998/Math/MathML\"/>";

    libcellml::Component c;
    c.appendMath(math);
    c.setMath("");

    libcellml::Printer printer;
    const std::string a = printer.printComponent(c);
    EXPECT_EQ(e, a);
}

TEST(Maths, appendSerialiseAndParseMathModel) {
    const std::string e =
            "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
            "<model xmlns=\"http://www.cellml.org/cellml/2.0#\">"
                "<component>"
                    "<math xmlns=\"http://www.w3.org/1998/Math/MathML\"/>"
                "</component>"
            "</model>";

    std::string math = "<math xmlns=\"http://www.w3.org/1998/Math/MathML\"/>";

    libcellml::Model m;
    libcellml::ComponentPtr c = std::make_shared<libcellml::Component>();
    m.addComponent(c);
    c->appendMath(math);

    libcellml::Printer printer;
    std::string a = printer.printModel(m);
    EXPECT_EQ(e, a);

    // Parse
    libcellml::Parser parser;
    libcellml::ModelPtr model = parser.parseModel(e);
    a = printer.printModel(model);
    EXPECT_EQ(e, a);
}

TEST(Maths, modelWithTwoVariablesAndTwoInvalidMaths) {
    const std::string e =
            "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
            "<model xmlns=\"http://www.cellml.org/cellml/2.0#\">"
                "<component name=\"component\">"
                    "<variable name=\"variable1\"/>"
                    "<variable name=\"variable2\"/>"
                    "<math xmlns=\"http://www.w3.org/1998/Math/MathML\"/>"
                    "<math xmlns=\"http://www.w3.org/1998/Math/MathML\"/>"
                "</component>"
            "</model>";

    std::string math = "<math xmlns=\"http://www.w3.org/1998/Math/MathML\"/>";

    libcellml::Model m;
    libcellml::ComponentPtr c = std::make_shared<libcellml::Component>();
    libcellml::VariablePtr v1 = std::make_shared<libcellml::Variable>();
    libcellml::VariablePtr v2 = std::make_shared<libcellml::Variable>();
    c->setName("component");
    v1->setName("variable1");
    v2->setName("variable2");
    c->addVariable(v1);
    c->addVariable(v2);
    c->appendMath(math);
    c->appendMath(math);
    m.addComponent(c);

    libcellml::Printer printer;
    const std::string a = printer.printModel(m);
    EXPECT_EQ(e, a);
}

TEST(Maths, modelWithTwoVariablesWithInitialValuesAndInvalidMath) {
    const std::string e =
            "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
            "<model xmlns=\"http://www.cellml.org/cellml/2.0#\">"
                "<component name=\"component\">"
                    "<variable name=\"variable1\" initial_value=\"1.0\"/>"
                    "<variable name=\"variable2\" initial_value=\"-1.0\"/>"
                    "<math xmlns=\"http://www.w3.org/1998/Math/MathML\"/>"
                "</component>"
            "</model>";

    std::string math = "<math xmlns=\"http://www.w3.org/1998/Math/MathML\"/>";

    libcellml::Model m;
    libcellml::ComponentPtr c = std::make_shared<libcellml::Component>();
    libcellml::VariablePtr v1 = std::make_shared<libcellml::Variable>();
    libcellml::VariablePtr v2 = std::make_shared<libcellml::Variable>();
    c->setName("component");
    v1->setName("variable1");
    v2->setName("variable2");
    v1->setInitialValue("1.0");
    v2->setInitialValue("-1.0");
    c->addVariable(v1);
    c->addVariable(v2);
    c->appendMath(math);
    m.addComponent(c);

    libcellml::Printer printer;
    const std::string a = printer.printModel(m);
    EXPECT_EQ(e, a);
}

// 1.xiii.a
TEST(Maths, modelWithTwoVariablesWithInitialValuesAndValidMath) {
    const std::string e =
            "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
            "<model xmlns=\"http://www.cellml.org/cellml/2.0#\">"
                "<component name=\"component\">"
                    "<variable name=\"A\" initial_value=\"1.0\"/>"
                    "<variable name=\"B\" initial_value=\"-1.0\"/>"
                    "<math xmlns=\"http://www.w3.org/1998/Math/MathML\">"
                        "<apply>"
                            "<eq/>"
                            "<ci>C</ci>"
                            "<apply>"
                                "<plus/>"
                                "<ci>A</ci>"
                                "<ci>B</ci>"
                            "</apply>"
                        "</apply>"
                    "</math>"
                "</component>"
            "</model>";

    std::string math =
            "<math xmlns=\"http://www.w3.org/1998/Math/MathML\">"
                "<apply>"
                    "<eq/>"
                    "<ci>C</ci>"
                    "<apply>"
                        "<plus/>"
                        "<ci>A</ci>"
                        "<ci>B</ci>"
                    "</apply>"
                "</apply>"
            "</math>";

    libcellml::Model m;
    libcellml::ComponentPtr c = std::make_shared<libcellml::Component>();
    libcellml::VariablePtr v1 = std::make_shared<libcellml::Variable>();
    libcellml::VariablePtr v2 = std::make_shared<libcellml::Variable>();
    c->setName("component");
    v1->setName("A");
    v2->setName("B");
    v1->setInitialValue("1.0");
    v2->setInitialValue("-1.0");
    c->addVariable(v1);
    c->addVariable(v2);
    c->appendMath(math);
    m.addComponent(c);

    libcellml::Printer printer;
    const std::string a = printer.printModel(m);
    EXPECT_EQ(e, a);
}

// 1.xiv.a
TEST(Maths, twoComponentsWithMathAndConnectionAndParse) {
    const std::string e =
            "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
            "<model xmlns=\"http://www.cellml.org/cellml/2.0#\">"
                "<component name=\"component1\">"
                    "<variable name=\"A1\"/>"
                    "<variable name=\"B1\"/>"
                    "<math xmlns=\"http://www.w3.org/1998/Math/MathML\">"
                        "<apply>"
                            "<eq/>"
                            "<ci>C1</ci>"
                            "<apply>"
                                "<plus/>"
                                "<ci>A1</ci>"
                                "<ci>B1</ci>"
                            "</apply>"
                        "</apply>"
                    "</math>"
                "</component>"
                "<component name=\"component2\">"
                    "<variable name=\"A2\"/>"
                    "<variable name=\"B2\"/>"
                    "<math xmlns=\"http://www.w3.org/1998/Math/MathML\">"
                        "<apply>"
                            "<eq/>"
                            "<ci>C2</ci>"
                            "<apply>"
                                "<plus/>"
                                "<ci>A2</ci>"
                                "<ci>B2</ci>"
                            "</apply>"
                        "</apply>"
                    "</math>"
                "</component>"
                "<connection component_1=\"component1\" component_2=\"component2\">"
                    "<map_variables variable_1=\"A1\" variable_2=\"A2\"/>"
                "</connection>"
            "</model>";

    std::string math1 =
            "<math xmlns=\"http://www.w3.org/1998/Math/MathML\">"
                "<apply>"
                    "<eq/>"
                    "<ci>C1</ci>"
                    "<apply>"
                        "<plus/>"
                        "<ci>A1</ci>"
                        "<ci>B1</ci>"
                    "</apply>"
                "</apply>"
            "</math>";

    std::string math2 =
            "<math xmlns=\"http://www.w3.org/1998/Math/MathML\">"
                "<apply>"
                    "<eq/>"
                    "<ci>C2</ci>"
                    "<apply>"
                        "<plus/>"
                        "<ci>A2</ci>"
                        "<ci>B2</ci>"
                    "</apply>"
                "</apply>"
            "</math>";

    libcellml::Model m;
    libcellml::ComponentPtr comp1 = std::make_shared<libcellml::Component>();
    libcellml::ComponentPtr comp2 = std::make_shared<libcellml::Component>();
    libcellml::VariablePtr v11 = std::make_shared<libcellml::Variable>();
    libcellml::VariablePtr v12 = std::make_shared<libcellml::Variable>();
    libcellml::VariablePtr v21 = std::make_shared<libcellml::Variable>();
    libcellml::VariablePtr v22 = std::make_shared<libcellml::Variable>();

    comp1->setName("component1");
    comp2->setName("component2");
    v11->setName("A1");
    v12->setName("B1");
    v21->setName("A2");
    v22->setName("B2");

    comp1->addVariable(v11);
    comp1->addVariable(v12);
    comp2->addVariable(v21);
    comp2->addVariable(v22);
    comp1->appendMath(math1);
    comp2->appendMath(math2);
    m.addComponent(comp1);
    m.addComponent(comp2);
    libcellml::Variable::addEquivalence(v11, v21);

    libcellml::Printer printer;
    std::string a = printer.printModel(m);
    EXPECT_EQ(e, a);

    // Parse
    libcellml::Parser parser;
    libcellml::ModelPtr model = parser.parseModel(e);
    a = printer.printModel(model);
    EXPECT_EQ(e, a);
}

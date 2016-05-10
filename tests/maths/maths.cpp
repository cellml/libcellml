/*
Copyright 2015 University of Auckland

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.Some license of other
*/

#include "gtest/gtest.h"

#include <libcellml>

TEST(Maths, appendAndGetMaths) {
    std::string mathString =
    "<math xmlns=\"http://www.w3.org/1998/Math/MathML\"/>";
    libcellml::Component c;
    c.appendMaths(mathString);
    EXPECT_EQ(mathString, c.getMaths());
}

TEST(Maths, appendAndSerialiseMathsComponent) {
    const std::string e =
    "<component>"
      "<math xmlns=\"http://www.w3.org/1998/Math/MathML\"/>"
    "</component>";
    std::string mathString =
    "<math xmlns=\"http://www.w3.org/1998/Math/MathML\"/>";
    libcellml::Component c;
    c.appendMaths(mathString);
    std::string a = c.serialise(libcellml::FORMAT_XML);
    EXPECT_EQ(e, a);
}

TEST(Maths, appendAndRemoveMathsComponent) {
    const std::string e =
    "<component/>";
    std::string mathString =
    "<math xmlns=\"http://www.w3.org/1998/Math/MathML\"/>";
    libcellml::Component c;
    c.appendMaths(mathString);
    c.removeMaths();
    std::string a = c.serialise(libcellml::FORMAT_XML);
    EXPECT_EQ(e, a);
}

TEST(Maths, appendAndSerialiseMathsModel) {
    const std::string e =
    "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
    "<model xmlns=\"http://www.cellml.org/cellml/1.2#\">"
      "<component>"
        "<math xmlns=\"http://www.w3.org/1998/Math/MathML\"/>"
      "</component>"
    "</model>";
    std::string mathString =
    "<math xmlns=\"http://www.w3.org/1998/Math/MathML\"/>";
    libcellml::Component m;
    libcellml::ComponentPtr c = std::make_shared<libcellml::Component>();
    m.addComponent(c);
    c->appendMaths(mathString);
    std::string a = m.serialise(libcellml::FORMAT_XML);
    EXPECT_EQ(e, a);
}

TEST(Maths, modelWithTwoVariablesAndTwoInvalidMaths) {
    const std::string e =
    "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
    "<model xmlns=\"http://www.cellml.org/cellml/1.2#\">"
      "<component name=\"component\">"
        "<variable name=\"variable1\"/>"
        "<variable name=\"variable2\"/>"
        "<math xmlns=\"http://www.w3.org/1998/Math/MathML\"/>"
        "<math xmlns=\"http://www.w3.org/1998/Math/MathML\"/>"
      "</component>"
    "</model>";
    std::string mathString =
    "<math xmlns=\"http://www.w3.org/1998/Math/MathML\">";
    libcellml::Model m;
    libcellml::ComponentPtr c = std::make_shared<libcellml::Component>();
    libcellml::VariablePtr v1 = std::make_shared<libcellml::Variable>();
    libcellml::VariablePtr v2 = std::make_shared<libcellml::Variable>();
    c->setName("component");
    v1->setName("variable1");
    v2->setName("variable2");
    c->addVariable(v1);
    c->addVariable(v2);
    c->appendMaths(mathString);
    c->appendMaths(mathString);
    m.addComponent(c);
    std::string a = m.serialise(libcellml::FORMAT_XML);
    EXPECT_EQ(e, a);
}

// 1.xiii.a
TEST(Maths, modelWithTwoVariablesWithInitialValuesAndInvalidMaths) {
    const std::string e =
    "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
    "<model xmlns=\"http://www.cellml.org/cellml/1.2#\">"
      "<component name=\"component\">"
        "<variable name=\"variable1\" initial_value=\"1.0\"/>"
        "<variable name=\"variable2\" initial_value=\"-1.0\"/>"
        "<math xmlns=\"http://www.w3.org/1998/Math/MathML\"/>";
      "</component>"
    "</model>";
    std::string mathString =
    "<math xmlns=\"http://www.w3.org/1998/Math/MathML\">";
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
    c->appendMaths(mathString);
    m.addComponent(c);
    std::string a = m.serialise(libcellml::FORMAT_XML);
    EXPECT_EQ(e, a);
}

TEST(Maths, modelWithTwoVariablesWithInitialValuesAndValidMaths) {
    const std::string e =
    "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
    "<model xmlns=\"http://www.cellml.org/cellml/1.2#\">"
      "<component name=\"component\">"
        "<variable name=\"A\" initial_value=\"1.0\"/>"
        "<variable name=\"B\" initial_value=\"-1.0\"/>"
        "<math xmlns=\"http://www.w3.org/1998/Math/MathML\">"
          "<apply>"
             "<plus/>"
             "<ci>A</ci>"
             "<ci>B</ci>"
          "</apply>"
        "</math>"
      "</component>"
    "</model>";
    std::string mathString =
    "<math xmlns=\"http://www.w3.org/1998/Math/MathML\">"
      "<apply>"
         "<plus/>"
         "<ci>A</ci>"
         "<ci>B</ci>"
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
    c->appendMaths(mathString);
    m.addComponent(c);
    std::string a = m.serialise(libcellml::FORMAT_XML);
    EXPECT_EQ(e, a);
}

// 1.xiv.a
TEST(Maths, twoComponentsWithMathsAndConnection) {
    const std::string e =
    "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
    "<model xmlns=\"http://www.cellml.org/cellml/1.2#\">"
      "<component name=\"component1\">"
        "<variable name=\"A1\"/>"
        "<variable name=\"B1\"/>"
        "<math xmlns=\"http://www.w3.org/1998/Math/MathML\">"
          "<apply>"
             "<plus/>"
             "<ci>A1</ci>"
             "<ci>B1</ci>"
          "</apply>"
        "</math>"
      "</component>"
      "<component name=\"component2\">"
        "<variable name=\"A2\"/>"
        "<variable name=\"B2\"/>"
        "<math xmlns=\"http://www.w3.org/1998/Math/MathML\">"
          "<apply>"
             "<plus/>"
             "<ci>A2</ci>"
             "<ci>B2</ci>"
          "</apply>"
        "</math>"
      "</component>"
      "<connection>"
        "<map_components component_1=\"component1\" component_2=\"component2\"/>"
        "<map_variables variable_1=\"A1\" variable_2=\"A2\"/>"
      "</connection>"
    "</model>";

    std::string mathString1 =
    "<math xmlns=\"http://www.w3.org/1998/Math/MathML\">"
      "<apply>"
         "<plus/>"
         "<ci>A1</ci>"
         "<ci>B1</ci>"
      "</apply>"
    "</math>";
    std::string mathString2 =
    "<math xmlns=\"http://www.w3.org/1998/Math/MathML\">"
      "<apply>"
         "<plus/>"
         "<ci>A2</ci>"
         "<ci>B2</ci>"
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
    comp1->appendMaths(mathString1);
    comp2->appendMaths(mathString2);
    m.addComponent(comp1);
    m.addComponent(comp2);
    libcellml::Variable::addEquivalence(v11,v21);

    std::string a = m.serialise(libcellml::FORMAT_XML);
    EXPECT_EQ(e, a);
}

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

static const std::string emptyMath = "<math xmlns=\"http://www.w3.org/1998/Math/MathML\"/>\n";

TEST(Maths, setAndGetMath) {
    libcellml::Component c;
    c.setMath(emptyMath);
    EXPECT_EQ(emptyMath, c.getMath());
}

TEST(Maths, appendAndSerialiseMathComponent) {
    const std::string e =
            "<component>\n"
            "  <math xmlns=\"http://www.w3.org/1998/Math/MathML\"/>\n"
            "</component>\n";

    libcellml::Component c;
    c.appendMath(emptyMath);

    libcellml::Printer printer;
    const std::string a = printer.printComponent(c);
    EXPECT_EQ(e, a);
}

TEST(Maths, appendAndResetMathComponent) {
    const std::string e = "<component/>\n";

    libcellml::Component c;
    c.appendMath(emptyMath);
    c.setMath("");

    libcellml::Printer printer;
    const std::string a = printer.printComponent(c);
    EXPECT_EQ(e, a);
}

TEST(Maths, appendSerialiseAndParseMathModel) {
    const std::string e =
            "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
            "<model xmlns=\"http://www.cellml.org/cellml/2.0#\">\n"
            "  <component>\n"
            "    <math xmlns=\"http://www.w3.org/1998/Math/MathML\"/>\n"
            "  </component>\n"
            "</model>\n";

    libcellml::Model m;
    libcellml::ComponentPtr c = std::make_shared<libcellml::Component>();
    m.addComponent(c);
    c->appendMath(emptyMath);

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
            "<model xmlns=\"http://www.cellml.org/cellml/2.0#\">\n"
            "  <component name=\"component\">\n"
            "    <variable name=\"variable1\"/>\n"
            "    <variable name=\"variable2\"/>\n"
            "    <math xmlns=\"http://www.w3.org/1998/Math/MathML\"/>\n"
            "    <math xmlns=\"http://www.w3.org/1998/Math/MathML\"/>\n"
            "  </component>\n"
            "</model>\n";

    libcellml::Model m;
    libcellml::ComponentPtr c = std::make_shared<libcellml::Component>();
    libcellml::VariablePtr v1 = std::make_shared<libcellml::Variable>();
    libcellml::VariablePtr v2 = std::make_shared<libcellml::Variable>();
    c->setName("component");
    v1->setName("variable1");
    v2->setName("variable2");
    c->addVariable(v1);
    c->addVariable(v2);
    c->appendMath(emptyMath);
    c->appendMath(emptyMath);
    m.addComponent(c);

    libcellml::Printer printer;
    const std::string a = printer.printModel(m);
    EXPECT_EQ(e, a);
}

TEST(Maths, modelWithTwoVariablesWithInitialValuesAndInvalidMath) {
    const std::string e =
            "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
            "<model xmlns=\"http://www.cellml.org/cellml/2.0#\">\n"
            "  <component name=\"component\">\n"
            "    <variable name=\"variable1\" initial_value=\"1.0\"/>\n"
            "    <variable name=\"variable2\" initial_value=\"-1.0\"/>\n"
            "    <math xmlns=\"http://www.w3.org/1998/Math/MathML\"/>\n"
            "  </component>\n"
            "</model>\n";

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
    c->appendMath(emptyMath);
    m.addComponent(c);

    libcellml::Printer printer;
    const std::string a = printer.printModel(m);
    EXPECT_EQ(e, a);
}

// 1.xiii.a
TEST(Maths, modelWithTwoVariablesWithInitialValuesAndValidMath) {
    const std::string e =
            "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
            "<model xmlns=\"http://www.cellml.org/cellml/2.0#\">\n"
            "  <component name=\"component\">\n"
            "    <variable name=\"A\" initial_value=\"1.0\"/>\n"
            "    <variable name=\"B\" initial_value=\"-1.0\"/>\n"
            "    <math xmlns=\"http://www.w3.org/1998/Math/MathML\">\n"
            "      <apply>\n"
            "        <eq/>\n"
            "        <ci>C</ci>\n"
            "        <apply>\n"
            "          <plus/>\n"
            "          <ci>A</ci>\n"
            "          <ci>B</ci>\n"
            "        </apply>\n"
            "      </apply>\n"
            "    </math>\n"
            "  </component>\n"
            "</model>\n";
    const std::string math =
            "<math xmlns=\"http://www.w3.org/1998/Math/MathML\">\n"
            "  <apply>\n"
            "    <eq/>\n"
            "    <ci>C</ci>\n"
            "    <apply>\n"
            "      <plus/>\n"
            "      <ci>A</ci>\n"
            "      <ci>B</ci>\n"
            "    </apply>\n"
            "  </apply>\n"
            "</math>\n";

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
            "<model xmlns=\"http://www.cellml.org/cellml/2.0#\">\n"
            "  <component name=\"component1\">\n"
            "    <variable name=\"A1\"/>\n"
            "    <variable name=\"B1\"/>\n"
            "    <math xmlns=\"http://www.w3.org/1998/Math/MathML\">\n"
            "      <apply>\n"
            "        <eq/>\n"
            "        <ci>C1</ci>\n"
            "        <apply>\n"
            "          <plus/>\n"
            "          <ci>A1</ci>\n"
            "          <ci>B1</ci>\n"
            "        </apply>\n"
            "      </apply>\n"
            "    </math>\n"
            "  </component>\n"
            "  <component name=\"component2\">\n"
            "    <variable name=\"A2\"/>\n"
            "    <variable name=\"B2\"/>\n"
            "    <math xmlns=\"http://www.w3.org/1998/Math/MathML\">\n"
            "      <apply>\n"
            "        <eq/>\n"
            "        <ci>C2</ci>\n"
            "        <apply>\n"
            "          <plus/>\n"
            "          <ci>A2</ci>\n"
            "          <ci>B2</ci>\n"
            "        </apply>\n"
            "      </apply>\n"
            "    </math>\n"
            "  </component>\n"
            "  <connection component_1=\"component1\" component_2=\"component2\">\n"
            "    <map_variables variable_1=\"A1\" variable_2=\"A2\"/>\n"
            "  </connection>\n"
            "</model>\n";
    const std::string math1 =
            "<math xmlns=\"http://www.w3.org/1998/Math/MathML\">\n"
            "  <apply>\n"
            "    <eq/>\n"
            "    <ci>C1</ci>\n"
            "    <apply>\n"
            "      <plus/>\n"
            "      <ci>A1</ci>\n"
            "      <ci>B1</ci>\n"
            "    </apply>\n"
            "  </apply>\n"
            "</math>\n";
    const std::string math2 =
            "<math xmlns=\"http://www.w3.org/1998/Math/MathML\">\n"
            "  <apply>\n"
            "    <eq/>\n"
            "    <ci>C2</ci>\n"
            "    <apply>\n"
            "      <plus/>\n"
            "      <ci>A2</ci>\n"
            "      <ci>B2</ci>\n"
            "    </apply>\n"
            "  </apply>\n"
            "</math>\n";

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

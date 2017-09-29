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

TEST(Variable, addAndGetEquivalentVariable) {
    libcellml::VariablePtr v1 = std::make_shared<libcellml::Variable>();
    libcellml::VariablePtr v2 = std::make_shared<libcellml::Variable>();
    libcellml::Variable::addEquivalence(v1, v2);
    EXPECT_EQ(v2, v1->getEquivalentVariable(0));
}

TEST(Variable, addAndGetEquivalentVariableReciprocal) {
    libcellml::VariablePtr v1 = std::make_shared<libcellml::Variable>();
    libcellml::VariablePtr v2 = std::make_shared<libcellml::Variable>();
    libcellml::Variable::addEquivalence(v1, v2);
    EXPECT_EQ(v1, v2->getEquivalentVariable(0));
}

TEST(Variable, addTwoEquivalentVariablesAndCount) {
    libcellml::VariablePtr v1 = std::make_shared<libcellml::Variable>();
    libcellml::VariablePtr v2 = std::make_shared<libcellml::Variable>();
    libcellml::VariablePtr v3 = std::make_shared<libcellml::Variable>();
    libcellml::Variable::addEquivalence(v1, v2);
    libcellml::Variable::addEquivalence(v1, v3);
    const size_t e = 2;
    size_t a = v1->equivalentVariableCount();
    EXPECT_EQ(e, a);
}

TEST(Variable, addDuplicateEquivalentVariablesAndCount) {
    libcellml::VariablePtr v1 = std::make_shared<libcellml::Variable>();
    libcellml::VariablePtr v2 = std::make_shared<libcellml::Variable>();
    libcellml::Variable::addEquivalence(v1, v2);
    libcellml::Variable::addEquivalence(v1, v2);
    libcellml::Variable::addEquivalence(v2, v1);
    libcellml::Variable::addEquivalence(v2, v1);
    const size_t e = 1;
    size_t a = v1->equivalentVariableCount();
    EXPECT_EQ(e, a);
}

TEST(Variable, hasNoEquivalentVariable) {
    libcellml::VariablePtr v1 = std::make_shared<libcellml::Variable>();
    libcellml::VariablePtr v2 = std::make_shared<libcellml::Variable>();
    bool a = v1->hasEquivalentVariable(v2);
    const bool e = false;
    EXPECT_EQ(e, a);
}

TEST(Variable, hasEquivalentVariable) {
    libcellml::VariablePtr v1 = std::make_shared<libcellml::Variable>();
    libcellml::VariablePtr v2 = std::make_shared<libcellml::Variable>();
    libcellml::Variable::addEquivalence(v1, v2);
    bool a = v1->hasEquivalentVariable(v2);
    const bool e = true;
    EXPECT_EQ(e, a);
}

TEST(Connection, componentlessVariableInvalidConnection) {
    const std::string e =
            "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
            "<model xmlns=\"http://www.cellml.org/cellml/2.0#\">"
                "<component name=\"component1\">"
                    "<variable name=\"variable1\"/>"
                "</component>"
                "<connection component_1=\"component1\">"
                    "<map_variables variable_1=\"variable1\" variable_2=\"variable2\"/>"
                "</connection>"
            "</model>";
    libcellml::Model m;
    libcellml::ComponentPtr comp1 = std::make_shared<libcellml::Component>();
    libcellml::VariablePtr v1 = std::make_shared<libcellml::Variable>();
    libcellml::VariablePtr v2 = std::make_shared<libcellml::Variable>();
    comp1->setName("component1");
    v1->setName("variable1");
    v2->setName("variable2");
    comp1->addVariable(v1);
    m.addComponent(comp1);
    libcellml::Variable::addEquivalence(v1, v2);

    libcellml::Printer printer;
    const std::string a = printer.printModel(m);
    EXPECT_EQ(e, a);
}

TEST(Connection, componentlessVariableInvalidConnectionClearParentCheck) {
    const std::string e =
            "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
            "<model xmlns=\"http://www.cellml.org/cellml/2.0#\">"
                "<component name=\"component2\">"
                    "<variable name=\"variable2\"/>"
                "</component>"
                "<connection component_1=\"component2\">"
                    "<map_variables variable_1=\"variable2\" variable_2=\"variable1\"/>"
                "</connection>"
            "</model>";
    libcellml::Model m;
    libcellml::ComponentPtr comp2 = std::make_shared<libcellml::Component>();
    libcellml::VariablePtr v1 = std::make_shared<libcellml::Variable>();
    libcellml::VariablePtr v2 = std::make_shared<libcellml::Variable>();
    comp2->setName("component2");
    v1->setName("variable1");
    v2->setName("variable2");
    comp2->addVariable(v2);
    {
        // Place comp1 in a different scope.
        libcellml::ComponentPtr comp1 = std::make_shared<libcellml::Component>();
        comp1->setName("component1");
        comp1->addVariable(v1);
        m.addComponent(comp1);
    }
    m.addComponent(comp2);
    libcellml::Variable::addEquivalence(v1, v2);
    m.removeComponent("component1");
    libcellml::Printer printer;
    const std::string a = printer.printModel(m);
    EXPECT_EQ(e, a);
}

TEST(Connection, validConnectionAndParse) {
    const std::string e =
            "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
            "<model xmlns=\"http://www.cellml.org/cellml/2.0#\">"
                "<component name=\"component1\">"
                    "<variable name=\"variable1\"/>"
                "</component>"
                "<component name=\"component2\">"
                    "<variable name=\"variable2\"/>"
                "</component>"
                "<connection component_1=\"component1\" component_2=\"component2\">"
                    "<map_variables variable_1=\"variable1\" variable_2=\"variable2\"/>"
                "</connection>"
            "</model>";
    libcellml::Model m;
    libcellml::ComponentPtr comp1 = std::make_shared<libcellml::Component>();
    libcellml::ComponentPtr comp2 = std::make_shared<libcellml::Component>();
    libcellml::VariablePtr v1 = std::make_shared<libcellml::Variable>();
    libcellml::VariablePtr v2 = std::make_shared<libcellml::Variable>();
    comp1->setName("component1");
    comp2->setName("component2");
    v1->setName("variable1");
    v2->setName("variable2");
    comp1->addVariable(v1);
    comp2->addVariable(v2);
    m.addComponent(comp1);
    m.addComponent(comp2);
    libcellml::Variable::addEquivalence(v1, v2);
    libcellml::Printer printer;
    std::string a = printer.printModel(m);
    EXPECT_EQ(e, a);

    // Parse
    libcellml::Parser parser;
    libcellml::ModelPtr model = parser.parseModel(e);
    a = printer.printModel(model);
    EXPECT_EQ(e, a);
}

TEST(Connection, twoMapVariablesConnection) {
    const std::string e =
            "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
            "<model xmlns=\"http://www.cellml.org/cellml/2.0#\">"
                "<component name=\"component1\">"
                    "<variable name=\"variable11\"/>"
                    "<variable name=\"variable12\"/>"
                "</component>"
                "<component name=\"component2\">"
                    "<variable name=\"variable21\"/>"
                    "<variable name=\"variable22\"/>"
                "</component>"
                "<connection component_1=\"component1\" component_2=\"component2\">"
                    "<map_variables variable_1=\"variable11\" variable_2=\"variable21\"/>"
                    "<map_variables variable_1=\"variable12\" variable_2=\"variable22\"/>"
                "</connection>"
            "</model>";

    libcellml::Model m;
    libcellml::ComponentPtr comp1 = std::make_shared<libcellml::Component>();
    libcellml::ComponentPtr comp2 = std::make_shared<libcellml::Component>();
    libcellml::VariablePtr v11 = std::make_shared<libcellml::Variable>();
    libcellml::VariablePtr v12 = std::make_shared<libcellml::Variable>();
    libcellml::VariablePtr v21 = std::make_shared<libcellml::Variable>();
    libcellml::VariablePtr v22 = std::make_shared<libcellml::Variable>();

    comp1->setName("component1");
    comp2->setName("component2");
    v11->setName("variable11");
    v12->setName("variable12");
    v21->setName("variable21");
    v22->setName("variable22");

    comp1->addVariable(v11);
    comp1->addVariable(v12);
    comp2->addVariable(v21);
    comp2->addVariable(v22);
    m.addComponent(comp1);
    m.addComponent(comp2);
    libcellml::Variable::addEquivalence(v11, v21);
    libcellml::Variable::addEquivalence(v12, v22);

    libcellml::Printer printer;
    const std::string a = printer.printModel(m);
    EXPECT_EQ(e, a);
}

TEST(Connection, threeMapVariablesConnectionOneDuplicate) {
    const std::string e =
            "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
            "<model xmlns=\"http://www.cellml.org/cellml/2.0#\">"
                "<component name=\"component1\">"
                    "<variable name=\"variable11\"/>"
                    "<variable name=\"variable12\"/>"
                    "<variable name=\"variable13\"/>"
                "</component>"
                "<component name=\"component2\">"
                    "<variable name=\"variable21\"/>"
                    "<variable name=\"variable22\"/>"
                    "<variable name=\"variable23\"/>"
                "</component>"
                "<connection component_1=\"component1\" component_2=\"component2\">"
                    "<map_variables variable_1=\"variable11\" variable_2=\"variable21\"/>"
                    "<map_variables variable_1=\"variable12\" variable_2=\"variable22\"/>"
                    "<map_variables variable_1=\"variable13\" variable_2=\"variable23\"/>"
                "</connection>"
            "</model>";

    libcellml::Model m;
    libcellml::ComponentPtr comp1 = std::make_shared<libcellml::Component>();
    libcellml::ComponentPtr comp2 = std::make_shared<libcellml::Component>();
    libcellml::VariablePtr v11 = std::make_shared<libcellml::Variable>();
    libcellml::VariablePtr v12 = std::make_shared<libcellml::Variable>();
    libcellml::VariablePtr v13 = std::make_shared<libcellml::Variable>();
    libcellml::VariablePtr v21 = std::make_shared<libcellml::Variable>();
    libcellml::VariablePtr v22 = std::make_shared<libcellml::Variable>();
    libcellml::VariablePtr v23 = std::make_shared<libcellml::Variable>();

    comp1->setName("component1");
    comp2->setName("component2");
    v11->setName("variable11");
    v12->setName("variable12");
    v13->setName("variable13");
    v21->setName("variable21");
    v22->setName("variable22");
    v23->setName("variable23");

    comp1->addVariable(v11);
    comp1->addVariable(v12);
    comp1->addVariable(v13);
    comp2->addVariable(v21);
    comp2->addVariable(v22);
    comp2->addVariable(v23);
    m.addComponent(comp1);
    m.addComponent(comp2);

    libcellml::Variable::addEquivalence(v23, v13);
    libcellml::Variable::addEquivalence(v21, v11);
    libcellml::Variable::addEquivalence(v12, v22);
    libcellml::Variable::addEquivalence(v13, v23);

    libcellml::Printer printer;
    const std::string a = printer.printModel(m);
    EXPECT_EQ(e, a);
}

TEST(Connection, nineVariablesTenConnectionsAndParse) {
    const std::string e =
            "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
            "<model xmlns=\"http://www.cellml.org/cellml/2.0#\">"
                "<component name=\"component1\">"
                    "<variable name=\"variable11\"/>"
                    "<variable name=\"variable12\"/>"
                    "<variable name=\"variable13\"/>"
                "</component>"
                "<component name=\"component2\">"
                    "<variable name=\"variable21\"/>"
                    "<variable name=\"variable22\"/>"
                    "<variable name=\"variable23\"/>"
                "</component>"
                "<component name=\"component3\">"
                    "<variable name=\"variable31\"/>"
                    "<variable name=\"variable32\"/>"
                    "<variable name=\"variable33\"/>"
                "</component>"
                "<connection component_1=\"component1\" component_2=\"component2\">"
                    "<map_variables variable_1=\"variable11\" variable_2=\"variable21\"/>"
                    "<map_variables variable_1=\"variable12\" variable_2=\"variable22\"/>"
                    "<map_variables variable_1=\"variable13\" variable_2=\"variable23\"/>"
                "</connection>"
                "<connection component_1=\"component1\" component_2=\"component3\">"
                    "<map_variables variable_1=\"variable11\" variable_2=\"variable31\"/>"
                    "<map_variables variable_1=\"variable11\" variable_2=\"variable33\"/>"
                    "<map_variables variable_1=\"variable12\" variable_2=\"variable32\"/>"
                    "<map_variables variable_1=\"variable13\" variable_2=\"variable33\"/>"
                "</connection>"
                "<connection component_1=\"component2\" component_2=\"component3\">"
                    "<map_variables variable_1=\"variable21\" variable_2=\"variable33\"/>"
                    "<map_variables variable_1=\"variable23\" variable_2=\"variable31\"/>"
                    "<map_variables variable_1=\"variable23\" variable_2=\"variable33\"/>"
                "</connection>"
            "</model>";

    libcellml::Model m;
    libcellml::ComponentPtr comp1 = std::make_shared<libcellml::Component>();
    libcellml::ComponentPtr comp2 = std::make_shared<libcellml::Component>();
    libcellml::ComponentPtr comp3 = std::make_shared<libcellml::Component>();
    libcellml::VariablePtr v11 = std::make_shared<libcellml::Variable>();
    libcellml::VariablePtr v12 = std::make_shared<libcellml::Variable>();
    libcellml::VariablePtr v13 = std::make_shared<libcellml::Variable>();
    libcellml::VariablePtr v21 = std::make_shared<libcellml::Variable>();
    libcellml::VariablePtr v22 = std::make_shared<libcellml::Variable>();
    libcellml::VariablePtr v23 = std::make_shared<libcellml::Variable>();
    libcellml::VariablePtr v31 = std::make_shared<libcellml::Variable>();
    libcellml::VariablePtr v32 = std::make_shared<libcellml::Variable>();
    libcellml::VariablePtr v33 = std::make_shared<libcellml::Variable>();

    comp1->setName("component1");
    comp2->setName("component2");
    comp3->setName("component3");
    v11->setName("variable11");
    v12->setName("variable12");
    v13->setName("variable13");
    v21->setName("variable21");
    v22->setName("variable22");
    v23->setName("variable23");
    v31->setName("variable31");
    v32->setName("variable32");
    v33->setName("variable33");

    comp1->addVariable(v11);
    comp1->addVariable(v12);
    comp1->addVariable(v13);
    comp2->addVariable(v21);
    comp2->addVariable(v22);
    comp2->addVariable(v23);
    comp3->addVariable(v31);
    comp3->addVariable(v32);
    comp3->addVariable(v33);
    m.addComponent(comp1);
    m.addComponent(comp2);
    m.addComponent(comp3);

    libcellml::Variable::addEquivalence(v11, v21);
    libcellml::Variable::addEquivalence(v31, v11);
    libcellml::Variable::addEquivalence(v12, v22);
    libcellml::Variable::addEquivalence(v32, v12);
    libcellml::Variable::addEquivalence(v13, v23);
    libcellml::Variable::addEquivalence(v33, v13);
    libcellml::Variable::addEquivalence(v31, v23);
    libcellml::Variable::addEquivalence(v21, v33);
    libcellml::Variable::addEquivalence(v11, v33);
    libcellml::Variable::addEquivalence(v33, v23);

    libcellml::Printer printer;
    std::string a = printer.printModel(m);
    EXPECT_EQ(e, a);

    // Parse
    libcellml::Parser parser;
    libcellml::ModelPtr model = parser.parseModel(e);
    a = printer.printModel(model);
    EXPECT_EQ(e, a);
}

TEST(Connection, twoValidConnections) {
    const std::string e =
            "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
            "<model xmlns=\"http://www.cellml.org/cellml/2.0#\">"
                "<component name=\"component1\">"
                    "<variable name=\"variable1\"/>"
                "</component>"
                "<component name=\"component2\">"
                    "<variable name=\"variable2\"/>"
                "</component>"
                "<component name=\"component3\">"
                    "<variable name=\"variable3\"/>"
                "</component>"
                "<connection component_1=\"component1\" component_2=\"component2\">"
                    "<map_variables variable_1=\"variable1\" variable_2=\"variable2\"/>"
                "</connection>"
                "<connection component_1=\"component1\" component_2=\"component3\">"
                    "<map_variables variable_1=\"variable1\" variable_2=\"variable3\"/>"
                "</connection>"
            "</model>";

    libcellml::Model m;
    libcellml::ComponentPtr comp1 = std::make_shared<libcellml::Component>();
    libcellml::ComponentPtr comp2 = std::make_shared<libcellml::Component>();
    libcellml::ComponentPtr comp3 = std::make_shared<libcellml::Component>();
    libcellml::VariablePtr v1 = std::make_shared<libcellml::Variable>();
    libcellml::VariablePtr v2 = std::make_shared<libcellml::Variable>();
    libcellml::VariablePtr v3 = std::make_shared<libcellml::Variable>();
    comp1->setName("component1");
    comp2->setName("component2");
    comp3->setName("component3");
    v1->setName("variable1");
    v2->setName("variable2");
    v3->setName("variable3");
    comp1->addVariable(v1);
    comp2->addVariable(v2);
    comp3->addVariable(v3);
    m.addComponent(comp1);
    m.addComponent(comp2);
    m.addComponent(comp3);
    libcellml::Variable::addEquivalence(v1, v2);
    libcellml::Variable::addEquivalence(v1, v3);
    libcellml::Printer printer;
    const std::string a = printer.printModel(m);
    EXPECT_EQ(e, a);
}

TEST(Connection, removeEquivalentVariableMethods) {
    const std::string e1 =
            "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
            "<model xmlns=\"http://www.cellml.org/cellml/2.0#\">"
                "<component name=\"component1\">"
                    "<variable name=\"variable1\"/>"
                "</component>"
                "<component name=\"component2\">"
                    "<variable name=\"variable2\"/>"
                "</component>"
                "<component name=\"component3\">"
                    "<variable name=\"variable3\"/>"
                "</component>"
                "<connection component_1=\"component1\" component_2=\"component2\">"
                    "<map_variables variable_1=\"variable1\" variable_2=\"variable2\"/>"
                "</connection>"
                "<connection component_1=\"component1\" component_2=\"component3\">"
                    "<map_variables variable_1=\"variable1\" variable_2=\"variable3\"/>"
                "</connection>"
                "<connection component_1=\"component2\" component_2=\"component3\">"
                    "<map_variables variable_1=\"variable2\" variable_2=\"variable3\"/>"
                "</connection>"
            "</model>";

    const std::string e2 =
            "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
            "<model xmlns=\"http://www.cellml.org/cellml/2.0#\">"
                "<component name=\"component1\">"
                    "<variable name=\"variable1\"/>"
                "</component>"
                "<component name=\"component2\">"
                    "<variable name=\"variable2\"/>"
                "</component>"
                "<component name=\"component3\">"
                    "<variable name=\"variable3\"/>"
                "</component>"
                "<connection component_1=\"component1\" component_2=\"component2\">"
                    "<map_variables variable_1=\"variable1\" variable_2=\"variable2\"/>"
                "</connection>"
                "<connection component_1=\"component1\" component_2=\"component3\">"
                    "<map_variables variable_1=\"variable1\" variable_2=\"variable3\"/>"
                "</connection>"
            "</model>";

    const std::string e3 =
            "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
            "<model xmlns=\"http://www.cellml.org/cellml/2.0#\">"
                "<component name=\"component1\">"
                    "<variable name=\"variable1\"/>"
                "</component>"
                "<component name=\"component2\">"
                    "<variable name=\"variable2\"/>"
                "</component>"
                "<component name=\"component3\">"
                    "<variable name=\"variable3\"/>"
                "</component>"
            "</model>";

    libcellml::Model m;
    libcellml::ComponentPtr comp1 = std::make_shared<libcellml::Component>();
    libcellml::ComponentPtr comp2 = std::make_shared<libcellml::Component>();
    libcellml::ComponentPtr comp3 = std::make_shared<libcellml::Component>();
    libcellml::VariablePtr v1 = std::make_shared<libcellml::Variable>();
    libcellml::VariablePtr v2 = std::make_shared<libcellml::Variable>();
    libcellml::VariablePtr v3 = std::make_shared<libcellml::Variable>();
    libcellml::VariablePtr v4 = std::make_shared<libcellml::Variable>();
    comp1->setName("component1");
    comp2->setName("component2");
    comp3->setName("component3");
    v1->setName("variable1");
    v2->setName("variable2");
    v3->setName("variable3");

    comp1->addVariable(v1);
    comp2->addVariable(v2);
    comp3->addVariable(v3);
    m.addComponent(comp1);
    m.addComponent(comp2);
    m.addComponent(comp3);
    libcellml::Variable::addEquivalence(v1, v2);
    libcellml::Variable::addEquivalence(v1, v3);
    libcellml::Variable::addEquivalence(v2, v3);
    libcellml::Printer printer;
    std::string a = printer.printModel(m);
    EXPECT_EQ(e1, a);

    EXPECT_TRUE(libcellml::Variable::removeEquivalence(v2, v3));
    a = printer.printModel(m);
    EXPECT_EQ(e2, a);
    EXPECT_FALSE(libcellml::Variable::removeEquivalence(v3, v4));

    v1->removeAllEquivalences();
    a = printer.printModel(m);
    EXPECT_EQ(e3, a);
}

TEST(Connection, removeVariablesFromConnections) {
    // Initial model
    const std::string e1 =
            "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
            "<model xmlns=\"http://www.cellml.org/cellml/2.0#\">"
                "<component name=\"component1\">"
                    "<variable name=\"variable1_1\"/>"
                    "<variable name=\"variable1_2\"/>"
                "</component>"
                "<component name=\"component2\">"
                    "<variable name=\"variable2\"/>"
                "</component>"
                "<component name=\"component3\">"
                    "<variable name=\"variable3\"/>"
                "</component>"
                "<component name=\"component4\">"
                    "<variable name=\"variable4\"/>"
                "</component>"
                "<connection component_1=\"component1\" component_2=\"component2\">"
                    "<map_variables variable_1=\"variable1_1\" variable_2=\"variable2\"/>"
                    "<map_variables variable_1=\"variable1_2\" variable_2=\"variable2\"/>"
                "</connection>"
                "<connection component_1=\"component1\" component_2=\"component3\">"
                    "<map_variables variable_1=\"variable1_1\" variable_2=\"variable3\"/>"
                "</connection>"
                "<connection component_1=\"component1\" component_2=\"component4\">"
                    "<map_variables variable_1=\"variable1_1\" variable_2=\"variable4\"/>"
                "</connection>"
                "<connection component_1=\"component2\" component_2=\"component3\">"
                    "<map_variables variable_1=\"variable2\" variable_2=\"variable3\"/>"
                "</connection>"
            "</model>";

    // Remove variable4
    const std::string e2 =
            "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
            "<model xmlns=\"http://www.cellml.org/cellml/2.0#\">"
                "<component name=\"component1\">"
                    "<variable name=\"variable1_1\"/>"
                    "<variable name=\"variable1_2\"/>"
                "</component>"
                "<component name=\"component2\">"
                    "<variable name=\"variable2\"/>"
                "</component>"
                "<component name=\"component3\">"
                    "<variable name=\"variable3\"/>"
                "</component>"
                "<component name=\"component4\"/>"
                "<connection component_1=\"component1\" component_2=\"component2\">"
                    "<map_variables variable_1=\"variable1_1\" variable_2=\"variable2\"/>"
                    "<map_variables variable_1=\"variable1_2\" variable_2=\"variable2\"/>"
                "</connection>"
                "<connection component_1=\"component1\" component_2=\"component3\">"
                    "<map_variables variable_1=\"variable1_1\" variable_2=\"variable3\"/>"
                "</connection>"
                "<connection component_1=\"component1\">"
                    "<map_variables variable_1=\"variable1_1\" variable_2=\"variable4\"/>"
                "</connection>"
                "<connection component_1=\"component2\" component_2=\"component3\">"
                    "<map_variables variable_1=\"variable2\" variable_2=\"variable3\"/>"
                "</connection>"
            "</model>";

    // Remove variable3
    const std::string e3 =
            "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
            "<model xmlns=\"http://www.cellml.org/cellml/2.0#\">"
                "<component name=\"component1\">"
                    "<variable name=\"variable1_1\"/>"
                    "<variable name=\"variable1_2\"/>"
                "</component>"
                "<component name=\"component2\">"
                    "<variable name=\"variable2\"/>"
                "</component>"
                "<component name=\"component3\"/>"
                "<component name=\"component4\"/>"
                "<connection component_1=\"component1\" component_2=\"component2\">"
                    "<map_variables variable_1=\"variable1_1\" variable_2=\"variable2\"/>"
                    "<map_variables variable_1=\"variable1_2\" variable_2=\"variable2\"/>"
                "</connection>"
                "<connection component_1=\"component1\">"
                    "<map_variables variable_1=\"variable1_1\" variable_2=\"variable3\"/>"
                    "<map_variables variable_1=\"variable1_1\" variable_2=\"variable4\"/>"
                "</connection>"
                "<connection component_1=\"component2\">"
                    "<map_variables variable_1=\"variable2\" variable_2=\"variable3\"/>"
                "</connection>"
            "</model>";

    // Remove variable2
    const std::string e4 =
            "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
            "<model xmlns=\"http://www.cellml.org/cellml/2.0#\">"
                "<component name=\"component1\">"
                    "<variable name=\"variable1_1\"/>"
                    "<variable name=\"variable1_2\"/>"
                "</component>"
                "<component name=\"component2\"/>"
                "<component name=\"component3\"/>"
                "<component name=\"component4\"/>"
                "<connection component_1=\"component1\">"
                    "<map_variables variable_1=\"variable1_1\" variable_2=\"variable2\"/>"
                    "<map_variables variable_1=\"variable1_1\" variable_2=\"variable3\"/>"
                    "<map_variables variable_1=\"variable1_1\" variable_2=\"variable4\"/>"
                    "<map_variables variable_1=\"variable1_2\" variable_2=\"variable2\"/>"
                "</connection>"
            "</model>";

    // Remove all variables from component1 (variable1_1 and variable1_2)
    const std::string e5 =
            "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
            "<model xmlns=\"http://www.cellml.org/cellml/2.0#\">"
                "<component name=\"component1\"/>"
                "<component name=\"component2\"/>"
                "<component name=\"component3\"/>"
                "<component name=\"component4\"/>"
            "</model>";

    libcellml::Model m;
    libcellml::ComponentPtr comp1 = std::make_shared<libcellml::Component>();
    libcellml::ComponentPtr comp2 = std::make_shared<libcellml::Component>();
    libcellml::ComponentPtr comp3 = std::make_shared<libcellml::Component>();
    libcellml::ComponentPtr comp4 = std::make_shared<libcellml::Component>();
    libcellml::VariablePtr v1_1 = std::make_shared<libcellml::Variable>();
    libcellml::VariablePtr v1_2 = std::make_shared<libcellml::Variable>();
    libcellml::VariablePtr v2 = std::make_shared<libcellml::Variable>();
    libcellml::VariablePtr v3 = std::make_shared<libcellml::Variable>();
    libcellml::VariablePtr v4 = std::make_shared<libcellml::Variable>();
    comp1->setName("component1");
    comp2->setName("component2");
    comp3->setName("component3");
    comp4->setName("component4");
    v1_1->setName("variable1_1");
    v1_2->setName("variable1_2");
    v2->setName("variable2");
    v3->setName("variable3");
    v4->setName("variable4");

    comp1->addVariable(v1_1);
    comp1->addVariable(v1_2);
    comp2->addVariable(v2);
    comp3->addVariable(v3);
    comp4->addVariable(v4);
    m.addComponent(comp1);
    m.addComponent(comp2);
    m.addComponent(comp3);
    m.addComponent(comp4);
    libcellml::Variable::addEquivalence(v1_1, v2);
    libcellml::Variable::addEquivalence(v1_2, v2);
    libcellml::Variable::addEquivalence(v1_1, v3);
    libcellml::Variable::addEquivalence(v1_1, v4);
    libcellml::Variable::addEquivalence(v2, v3);
    libcellml::Printer printer;
    std::string a = printer.printModel(m);
    EXPECT_EQ(e1, a);

    comp4->removeVariable(v4);
    a = printer.printModel(m);
    EXPECT_EQ(e2, a);

    comp3->removeVariable("variable3");
    a = printer.printModel(m);
    EXPECT_EQ(e3, a);

    comp2->removeVariable(v2);
    a = printer.printModel(m);
    EXPECT_EQ(e4, a);

    comp1->removeAllVariables();
    a = printer.printModel(m);
    EXPECT_EQ(e5, a);
}

TEST(Connection, twoEncapsulatedChildComponentsWithConnectionsAndMixedInterfaces) {
    const std::string e =
            "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
            "<model xmlns=\"http://www.cellml.org/cellml/2.0#\">"
                "<component name=\"parent\">"
                    "<variable name=\"variable1\" interface=\"private\"/>"
                "</component>"
                "<component name=\"child1\">"
                    "<variable name=\"variable2\" interface=\"public\"/>"
                "</component>"
                "<component name=\"child2\">"
                    "<variable name=\"variable3\" interface=\"public\"/>"
                "</component>"
                "<encapsulation>"
                    "<component_ref component=\"parent\">"
                        "<component_ref component=\"child1\"/>"
                        "<component_ref component=\"child2\"/>"
                    "</component_ref>"
                "</encapsulation>"
                "<connection component_1=\"parent\" component_2=\"child1\">"
                    "<map_variables variable_1=\"variable1\" variable_2=\"variable2\"/>"
                "</connection>"
                "<connection component_1=\"parent\" component_2=\"child2\">"
                    "<map_variables variable_1=\"variable1\" variable_2=\"variable3\"/>"
                "</connection>"
            "</model>";

    libcellml::Model m;
    libcellml::ComponentPtr parent = std::make_shared<libcellml::Component>();
    libcellml::ComponentPtr child1 = std::make_shared<libcellml::Component>();
    libcellml::ComponentPtr child2 = std::make_shared<libcellml::Component>();
    libcellml::VariablePtr v1 = std::make_shared<libcellml::Variable>();
    libcellml::VariablePtr v2 = std::make_shared<libcellml::Variable>();
    libcellml::VariablePtr v3 = std::make_shared<libcellml::Variable>();

    parent->setName("parent");
    child1->setName("child1");
    child2->setName("child2");
    v1->setName("variable1");
    v2->setName("variable2");
    v3->setName("variable3");

    m.addComponent(parent);
    parent->addComponent(child1);
    parent->addComponent(child2);
    parent->addVariable(v1);
    child1->addVariable(v2);
    child2->addVariable(v3);
    libcellml::Variable::addEquivalence(v1, v2);
    libcellml::Variable::addEquivalence(v1, v3);
    v1->setInterfaceType(libcellml::Variable::InterfaceType::PRIVATE);
    v2->setInterfaceType(libcellml::Variable::InterfaceType::PUBLIC);
    v3->setInterfaceType(libcellml::Variable::InterfaceType::PUBLIC);

    libcellml::Printer printer;
    const std::string a = printer.printModel(m);
    EXPECT_EQ(e, a);
}

TEST(Connection, twoEncapsulatedChildComponentsWithConnectionsAndPublicInterfaces) {
    const std::string e =
            "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
            "<model xmlns=\"http://www.cellml.org/cellml/2.0#\">"
                "<component name=\"parent\">"
                    "<variable name=\"variable1\" interface=\"public\"/>"
                "</component>"
                "<component name=\"child1\">"
                    "<variable name=\"variable2\" interface=\"public\"/>"
                "</component>"
                "<component name=\"child2\">"
                    "<variable name=\"variable3\" interface=\"public\"/>"
                "</component>"
                "<encapsulation>"
                    "<component_ref component=\"parent\">"
                        "<component_ref component=\"child1\"/>"
                        "<component_ref component=\"child2\"/>"
                    "</component_ref>"
                "</encapsulation>"
                "<connection component_1=\"parent\" component_2=\"child1\">"
                    "<map_variables variable_1=\"variable1\" variable_2=\"variable2\"/>"
                "</connection>"
                "<connection component_1=\"parent\" component_2=\"child2\">"
                    "<map_variables variable_1=\"variable1\" variable_2=\"variable3\"/>"
                "</connection>"
            "</model>";

    libcellml::Model m;
    libcellml::ComponentPtr parent = std::make_shared<libcellml::Component>();
    libcellml::ComponentPtr child1 = std::make_shared<libcellml::Component>();
    libcellml::ComponentPtr child2 = std::make_shared<libcellml::Component>();
    libcellml::VariablePtr v1 = std::make_shared<libcellml::Variable>();
    libcellml::VariablePtr v2 = std::make_shared<libcellml::Variable>();
    libcellml::VariablePtr v3 = std::make_shared<libcellml::Variable>();

    parent->setName("parent");
    child1->setName("child1");
    child2->setName("child2");
    v1->setName("variable1");
    v2->setName("variable2");
    v3->setName("variable3");

    m.addComponent(parent);
    parent->addComponent(child1);
    parent->addComponent(child2);
    parent->addVariable(v1);
    child1->addVariable(v2);
    child2->addVariable(v3);
    libcellml::Variable::addEquivalence(v1, v2);
    libcellml::Variable::addEquivalence(v1, v3);
    v1->setInterfaceType(libcellml::Variable::InterfaceType::PUBLIC);
    v2->setInterfaceType(libcellml::Variable::InterfaceType::PUBLIC);
    v3->setInterfaceType(libcellml::Variable::InterfaceType::PUBLIC);

    libcellml::Printer printer;
    const std::string a = printer.printModel(m);
    EXPECT_EQ(e, a);
}

TEST(Connection, importedComponentConnectionAndParse) {
    const std::string e =
            "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
            "<model xmlns=\"http://www.cellml.org/cellml/2.0#\">"
                "<import xlink:href=\"some-other-model.xml\" xmlns:xlink=\"http://www.w3.org/1999/xlink\">"
                    "<component component_ref=\"component_in_that_model\" name=\"component_in_this_model\"/>"
                "</import>"
                "<component name=\"component_bob\">"
                    "<variable name=\"variable_bob\"/>"
                "</component>"
                "<connection component_1=\"component_in_this_model\" component_2=\"component_bob\">"
                    "<map_variables variable_1=\"variable_import\" variable_2=\"variable_bob\"/>"
                "</connection>"
            "</model>";

    libcellml::Model m;
    libcellml::ImportSourcePtr imp = std::make_shared<libcellml::ImportSource>();
    libcellml::ComponentPtr componentImported = std::make_shared<libcellml::Component>();
    libcellml::ComponentPtr componentBob = std::make_shared<libcellml::Component>();
    libcellml::VariablePtr variableImported = std::make_shared<libcellml::Variable>();
    libcellml::VariablePtr variableBob = std::make_shared<libcellml::Variable>();

    imp->setSource("some-other-model.xml");
    componentImported->setName("component_in_this_model");
    componentImported->setSourceComponent(imp, "component_in_that_model");
    componentBob->setName("component_bob");
    variableImported->setName("variable_import");
    variableBob->setName("variable_bob");

    m.addComponent(componentImported);
    m.addComponent(componentBob);
    componentImported->addVariable(variableImported);
    componentBob->addVariable(variableBob);
    EXPECT_EQ(componentImported->getVariable(0), variableImported);
    libcellml::Variable::addEquivalence(variableImported, variableBob);
    libcellml::Printer printer;
    std::string a = printer.printModel(m);
    EXPECT_EQ(e, a);

    // Parse
    libcellml::Parser parser;
    libcellml::ModelPtr model = parser.parseModel(e);
    EXPECT_EQ(0, parser.errorCount());

    a = printer.printModel(model);
    EXPECT_EQ(e, a);
}

TEST(Connection, componentConnectionAndParseMissingVariable) {
    const std::string s =
            "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
            "<model xmlns=\"http://www.cellml.org/cellml/2.0#\">"
                "<component name=\"component_dave\">"
                    "<variable name=\"variable_dave\"/>"
                "</component>"
                "<component name=\"component_bob\">"
                    "<variable name=\"variable_bob\"/>"
                "</component>"
                "<connection component_1=\"component_dave\" component_2=\"component_bob\">"
                    "<map_variables variable_1=\"variable_angus\" variable_2=\"variable_bob\"/>"
                "</connection>"
            "</model>";

    const std::string e =
            "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
            "<model xmlns=\"http://www.cellml.org/cellml/2.0#\">"
                "<component name=\"component_dave\">"
                    "<variable name=\"variable_dave\"/>"
                "</component>"
                "<component name=\"component_bob\">"
                    "<variable name=\"variable_bob\"/>"
                "</component>"
            "</model>";

    std::string expectError = "Variable 'variable_angus' is specified as variable_1 in a connection but it does not exist in component_1 component 'component_dave' of model ''.";

    // Parse
    libcellml::Parser parser;
    libcellml::ModelPtr model = parser.parseModel(s);
    EXPECT_EQ(1, parser.errorCount());

    EXPECT_EQ(expectError, parser.getError(0)->getDescription());
    parser.clearErrors();
    EXPECT_EQ(0, parser.errorCount());

    libcellml::Printer printer;
    const std::string a = printer.printModel(model);
    EXPECT_EQ(e, a);
}

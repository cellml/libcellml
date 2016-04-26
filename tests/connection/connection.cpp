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

TEST(Variable, addAndGetEquivalentVariable) {
    libcellml::Variable v1;
    libcellml::VariablePtr v2 = std::make_shared<libcellml::Variable>();
    v1.addEquivalence(v2);
    EXPECT_EQ(v2,v1.getEquivalentVariable(0));
}

TEST(Variable, addAndGetEquivalentVariableReciprocal) {
    libcellml::Variable v1;
    libcellml::VariablePtr v2 = std::make_shared<libcellml::Variable>();
    v1.addEquivalence(v2);
    EXPECT_EQ(v1,v2->getEquivalentVariable(0));
}

TEST(Variable, addTwoEquivalentVariablesAndCount) {
    libcellml::Variable v1;
    libcellml::VariablePtr v2 = std::make_shared<libcellml::Variable>();
    libcellml::VariablePtr v3 = std::make_shared<libcellml::Variable>();
    v1.addEquivalence(v2);
    v1.addEquivalence(v3);
    size_t e = 2;
    size_t a = v1.countEquivalentVariables;
    EXPECT_EQ(e, a);
}

TEST(Variable, hasEquivalentVariable) {
    libcellml::Variable v1;
    libcellml::VariablePtr v2 = std::make_shared<libcellml::Variable>();
    v1.addEquivalence(v2);
    EXPECT_EQ(true,v1.hasEquivalentVariable(v2));
}

TEST(Connection, componentlessVariableInvalidConnection) {
    const std::string e =
    "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
    "<model xmlns=\"http://www.cellml.org/cellml/1.2#\">"
      "<component name=\"component1\">"
        "<variable name=\"variable1\"/>"
      "</component>"
      "<variable name=\"variable2\"/>"
      "<connection>"
        "<map_components component1_1=\"component1\"/>"
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
    v1->addEquivalence(v2);
    std::string a = m.serialise(libcellml::FORMAT_XML);
    EXPECT_EQ(e, a);
}

TEST(Connection, validConnection) {
    const std::string e =
    "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
    "<model xmlns=\"http://www.cellml.org/cellml/1.2#\">"
      "<component name=\"component1\">"
        "<variable name=\"variable1\"/>"
      "</component>"
      "<component name=\"component2\">"
        "<variable name=\"variable2\"/>"
      "</component>"
      "<connection>"
        "<map_components component_1=\"component1\" component_2=\"component2\"/>"
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
    v1->addEquivalence(v2);
    std::string a = m.serialise(libcellml::FORMAT_XML);
    EXPECT_EQ(e, a);
}

TEST(Connection, twoMapVariablesConnection) {
    const std::string e =
    "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
    "<model xmlns=\"http://www.cellml.org/cellml/1.2#\">"
      "<component name=\"component1\">"
        "<variable name=\"variable11\"/>"
        "<variable name=\"variable12\"/>"
      "</component>"
      "<component name=\"component2\">"
        "<variable name=\"variable21\"/>"
        "<variable name=\"variable22\"/>"
      "</component>"
      "<connection>"
        "<map_components component_1=\"component1\" component_2=\"component2\"/>"
        "<map_variables variable_1=\"variable11\" variable_2=\"variable21\"/>"
        "<map_variables variable_1=\"variable12\" variable_2=\"variable22\"/>"
      "</connection>"
    "</model>";

    libcellml::Model m;
    libcellml::ComponentPtr comp1 = std::make_shared<libcellml::Component>();
    comp1->setName("component1");
    libcellml::ComponentPtr comp2 = std::make_shared<libcellml::Component>();
    comp2->setName("component2");
    libcellml::VariablePtr v11 = std::make_shared<libcellml::Variable>();
    v11->setName("variable11");
    libcellml::VariablePtr v12 = std::make_shared<libcellml::Variable>();
    v12->setName("variable12");
    libcellml::VariablePtr v21 = std::make_shared<libcellml::Variable>();
    v21->setName("variable21");
    libcellml::VariablePtr v22 = std::make_shared<libcellml::Variable>();
    v22->setName("variable22");

    comp1->addVariable(v11);
    comp1->addVariable(v12);
    comp2->addVariable(v21);
    comp2->addVariable(v22);
    m.addComponent(comp1);
    m.addComponent(comp2);
    v11->addEquivalence(v21);
    v12->addEquivalence(v22);

    std::string a = m.serialise(libcellml::FORMAT_XML);
    EXPECT_EQ(e, a);
}

TEST(Connection, twoEncapsulatedChildrenInterfaces) {
    const std::string e =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/1.2#\">"

          "<component name=\"parent_component\">"
            "<variable name=\"variable1\" interface=\"private\"/>"
          "</component>"
          "<component name=\"child1\">"
            "<variable name=\"variable2\" interface=\"public\"/>"
          "</component>"
          "<component name=\"child2\">"
            "<variable name=\"variable3\" interface=\"public\"/>"
          "</component>"

          "<encapsulation>"
              "<component_ref component=\"parent_component\">"
                  "<component_ref component=\"child1\"/>"
                  "<component_ref component=\"child2\"/>"
              "</component_ref>"
          "</encapsulation>"

          "<connection>"
            "<map_components component_2=\"parent_component\" component_1=\"child1\"/>"
            "<map_variables variable_2=\"variable1\" variable_1=\"variable2\"/>"
          "</connection>"

          "<connection>"
            "<map_components component_2=\"parent_component\" component_1=\"child2\"/>"
            "<map_variables variable_2=\"variable1\" variable_1=\"variable3\"/>"
          "</connection>"
        "</model>";

    libcellml::Model m;
    libcellml::ComponentPtr parent = std::make_shared<libcellml::Component>();
    libcellml::ComponentPtr child1 = std::make_shared<libcellml::Component>();
    libcellml::ComponentPtr child2 = std::make_shared<libcellml::Component>();
    libcellml::VariablePtr v1 = std::make_shared<libcellml::Variable>();

    parent->setName("parent_component");
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
    v1->addEquivalence(v2);
    v1->addEquivalence(v3);
    v1.setInterfaceType(libcellml::Variable::INTERFACE_TYPE_PRIVATE);
    v2.setInterfaceType(libcellml::Variable::INTERFACE_TYPE_PUBLIC);
    v3.setInterfaceType(libcellml::Variable::INTERFACE_TYPE_PUBLIC);

    std::string a = parent.serialise(libcellml::FORMAT_XML);
    EXPECT_EQ(e, a);
}





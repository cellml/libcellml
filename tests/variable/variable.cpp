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
limitations under the License.
*/

#include "gtest/gtest.h"

#include <libcellml>


TEST(Variable, serialise) {
    const std::string e = "<variable/>";
    libcellml::Variable v;
    std::string a = v.serialise(libcellml::Format::XML);
    EXPECT_EQ(e, a);
}

TEST(Variable, setValidVariableName) {
    const std::string in = "valid_name";
    const std::string e = "<variable name=\"" + in + "\"/>";
    libcellml::Variable v;
    v.setName(in);
    std::string a = v.serialise(libcellml::Format::XML);
    EXPECT_EQ(e, a);
}

TEST(Variable, setInvalidVariableName) {
    const std::string in = "invalid name";
    const std::string e = "<variable name=\"" + in + "\"/>";
    libcellml::Variable v;
    v.setName(in);
    std::string a = v.serialise(libcellml::Format::XML);
    EXPECT_EQ(e, a);
}

TEST(Variable, getValidVariableName) {
    const std::string in = "valid_name";
    const std::string e = in;
    libcellml::Variable v;
    v.setName(in);
    std::string a = v.getName();
    EXPECT_EQ(e, a);
}

TEST(Variable, getInvalidVariableName) {
    const std::string in = "invalid name";
    const std::string e = in;
    libcellml::Variable v;
    v.setName(in);
    std::string a = v.getName();
    EXPECT_EQ(e, a);
}

TEST(Variable, setUnits) {
    const std::string in = "dimensionless";
    const std::string e = "<variable units=\"" + in + "\"/>";
    libcellml::Variable v;

    libcellml::UnitsPtr u = std::make_shared<libcellml::Units>();
    u->setName(in);
    v.setUnits(u);

    std::string a = v.serialise(libcellml::Format::XML);
    EXPECT_EQ(e, a);
}

TEST(Variable, setUnitsAndName) {
    const std::string in = "valid_name";
    const std::string e = "<variable name=\"" + in + "\" units=\"dimensionless\"/>";
    libcellml::Variable v;
    v.setName(in);

    libcellml::UnitsPtr u = std::make_shared<libcellml::Units>();
    u->setName("dimensionless");
    v.setUnits(u);

    std::string a = v.serialise(libcellml::Format::XML);
    EXPECT_EQ(e, a);
}

TEST(Variable, setInitialValueByString) {
    const std::string e = "<variable initial_value=\"0.0\"/>";
    libcellml::Variable v;
    v.setInitialValue("0.0");
    std::string a = v.serialise(libcellml::Format::XML);
    EXPECT_EQ(e, a);
}

TEST(Variable, setInitialValueByDouble) {
    const std::string e = "<variable initial_value=\"0\"/>";
    libcellml::Variable v;
    double value = 0.0;
    v.setInitialValue(value);
    std::string a = v.serialise(libcellml::Format::XML);
    EXPECT_EQ(e, a);
}

TEST(Variable, setInitialValueByReference) {
    const std::string e = "<variable initial_value=\"referencedVariable\"/>";
    libcellml::VariablePtr v1 = std::make_shared<libcellml::Variable>();
    v1->setName("referencedVariable");
    libcellml::Variable v2;
    v2.setInitialValue(v1);
    std::string a = v2.serialise(libcellml::Format::XML);
    EXPECT_EQ(e, a);
}

TEST(Variable, getUnsetInitialValue) {
    libcellml::Variable v;
    EXPECT_EQ(v.getInitialValue(), "");
}

TEST(Variable, getSetInitialValue) {
    libcellml::Variable v;
    std::string e = "0.0";
    v.setInitialValue(e);
    std::string a = v.getInitialValue();
    EXPECT_EQ(e, a);
}

TEST(Variable, setInterfaceTypeByInvalidString) {
    const std::string e = "<variable interface=\"invalid\"/>";
    libcellml::Variable v;
    v.setInterfaceType("invalid");
    std::string a = v.serialise(libcellml::Format::XML);
    EXPECT_EQ(e, a);
}

TEST(Variable, setInterfaceTypeNoneByValidString) {
    const std::string e = "<variable interface=\"none\"/>";
    libcellml::Variable v;
    v.setInterfaceType("none");
    std::string a = v.serialise(libcellml::Format::XML);
    EXPECT_EQ(e, a);
}

TEST(Variable, setInterfaceTypeNoneByEnum) {
    const std::string e = "<variable interface=\"none\"/>";
    libcellml::Variable v;
    v.setInterfaceType(libcellml::Variable::InterfaceType::NONE);
    std::string a = v.serialise(libcellml::Format::XML);
    EXPECT_EQ(e, a);
}

TEST(Variable, setInterfaceTypePrivate) {
    const std::string e = "<variable interface=\"private\"/>";
    libcellml::Variable v;
    v.setInterfaceType(libcellml::Variable::InterfaceType::PRIVATE);
    std::string a = v.serialise(libcellml::Format::XML);
    EXPECT_EQ(e, a);
}

TEST(Variable, setInterfaceTypePublic) {
    const std::string e = "<variable interface=\"public\"/>";
    libcellml::Variable v;
    v.setInterfaceType(libcellml::Variable::InterfaceType::PUBLIC);
    std::string a = v.serialise(libcellml::Format::XML);
    EXPECT_EQ(e, a);
}

TEST(Variable, setInterfaceTypePublicAndPrivate) {
    const std::string e = "<variable interface=\"public_and_private\"/>";
    libcellml::Variable v;
    v.setInterfaceType(libcellml::Variable::InterfaceType::PUBLIC_AND_PRIVATE);
    std::string a = v.serialise(libcellml::Format::XML);
    EXPECT_EQ(e, a);
}

TEST(Variable, setGetInterfaceType) {
    libcellml::Variable v1;
    libcellml::Variable v2;
    libcellml::Variable v3;
    libcellml::Variable v4;
    libcellml::Variable::InterfaceType interfaceType1 = libcellml::Variable::InterfaceType::NONE;
    libcellml::Variable::InterfaceType interfaceType2 = libcellml::Variable::InterfaceType::PRIVATE;
    libcellml::Variable::InterfaceType interfaceType3 = libcellml::Variable::InterfaceType::PUBLIC;
    libcellml::Variable::InterfaceType interfaceType4 = libcellml::Variable::InterfaceType::PUBLIC_AND_PRIVATE;
    v1.setInterfaceType(interfaceType1);
    v2.setInterfaceType(interfaceType2);
    v3.setInterfaceType(interfaceType3);
    v4.setInterfaceType(interfaceType4);

    const std::string interfaceTypeString1 = "none";
    const std::string interfaceTypeString2 = "private";
    const std::string interfaceTypeString3 = "public";
    const std::string interfaceTypeString4 = "public_and_private";

    EXPECT_EQ(interfaceTypeString1, v1.getInterfaceType());
    EXPECT_EQ(interfaceTypeString2, v2.getInterfaceType());
    EXPECT_EQ(interfaceTypeString3, v3.getInterfaceType());
    EXPECT_EQ(interfaceTypeString4, v4.getInterfaceType());
}

TEST(Variable, addVariable) {
    const std::string in = "valid_name";
    const std::string e =
            "<component name=\"" + in + "\">"
                "<variable name=\"" + in + "\" units=\"dimensionless\"/>"
              "</component>";

    libcellml::Component c;
    c.setName(in);

    libcellml::VariablePtr v = std::make_shared<libcellml::Variable>();
    v->setName(in);
    c.addVariable(v);

    libcellml::UnitsPtr u = std::make_shared<libcellml::Units>();
    u->setName("dimensionless");
    v->setUnits(u);

    std::string a = c.serialise(libcellml::Format::XML);
    EXPECT_EQ(e, a);
}

TEST(Variable, getParentComponent) {
    libcellml::Component c;
    libcellml::VariablePtr v = std::make_shared<libcellml::Variable>();
    c.addVariable(v);
    EXPECT_EQ(&c, v->getParent());
}

TEST(Variable, getNullParentComponent) {
    libcellml::VariablePtr v = std::make_shared<libcellml::Variable>();
    EXPECT_EQ(nullptr, v->getParent());
}

TEST(Variable, addVariableToUnnamedComponent) {
    const std::string in = "valid_name";
    const std::string e =
            "<component>"
                "<variable name=\"" + in + "\"/>"
             "</component>";

    libcellml::Component c;

    libcellml::VariablePtr v = std::make_shared<libcellml::Variable>();
    v->setName(in);
    c.addVariable(v);

    std::string a = c.serialise(libcellml::Format::XML);
    EXPECT_EQ(e, a);
}

TEST(Variable, addTwoVariables) {
    const std::string in = "valid_name";
    const std::string e =
            "<component name=\"" + in + "\">"
                "<variable name=\"variable1\"/>"
                "<variable name=\"variable2\"/>"
            "</component>";

    libcellml::Component c;
    c.setName(in);

    libcellml::VariablePtr v1 = std::make_shared<libcellml::Variable>();
    v1->setName("variable1");
    c.addVariable(v1);

    libcellml::VariablePtr v2 = std::make_shared<libcellml::Variable>();
    v2->setName("variable2");
    c.addVariable(v2);

    std::string a = c.serialise(libcellml::Format::XML);
    EXPECT_EQ(e, a);
}

TEST(Variable, addVariablesWithAndWithoutNameAndUnits) {
    const std::string e =
        "<component>"
            "<variable name=\"var1\" units=\"dimensionless\"/>"
            "<variable name=\"var2\"/>"
            "<variable units=\"dimensionless\"/>"
            "<variable/>"
        "</component>";

    libcellml::Component c;

    libcellml::VariablePtr v1 = std::make_shared<libcellml::Variable>();
    v1->setName("var1");
    libcellml::VariablePtr v2 = std::make_shared<libcellml::Variable>();
    v2->setName("var2");
    libcellml::VariablePtr v3 = std::make_shared<libcellml::Variable>();
    libcellml::VariablePtr v4 = std::make_shared<libcellml::Variable>();

    c.addVariable(v1);
    c.addVariable(v2);
    c.addVariable(v3);
    c.addVariable(v4);

    libcellml::UnitsPtr u = std::make_shared<libcellml::Units>();
    u->setName("dimensionless");
    v1->setUnits(u);
    v3->setUnits(u);

    std::string a = c.serialise(libcellml::Format::XML);
    EXPECT_EQ(e, a);
}

TEST(Variable, componentWithTwoVariablesWithInitialValues) {
    const std::string in = "valid_name";
    const std::string e =
            "<component name=\"" + in + "\">"
                "<variable initial_value=\"1\"/>"
                "<variable initial_value=\"-1\"/>"
            "</component>";

    libcellml::Component c;
    c.setName(in);

    libcellml::VariablePtr v1 = std::make_shared<libcellml::Variable>();
    v1->setInitialValue(1.0);
    c.addVariable(v1);

    libcellml::VariablePtr v2 = std::make_shared<libcellml::Variable>();
    v2->setInitialValue(-1.0);
    c.addVariable(v2);

    std::string a = c.serialise(libcellml::Format::XML);
    EXPECT_EQ(e, a);
}

TEST(Variable, removeVariableMethods) {
    const std::string in = "valid_name";
    const std::string e1 =
            "<component name=\"" + in + "\">"
                "<variable name=\"variable2\"/>"
            "</component>";
    const std::string e2 =
            "<component name=\"" + in + "\"/>";

    libcellml::Component c;
    libcellml::VariablePtr v1 = std::make_shared<libcellml::Variable>();
    libcellml::VariablePtr v2 = std::make_shared<libcellml::Variable>();
    libcellml::VariablePtr v3 = std::make_shared<libcellml::Variable>();
    libcellml::VariablePtr v4 = std::make_shared<libcellml::Variable>();
    libcellml::VariablePtr v5 = std::make_shared<libcellml::Variable>();

    c.setName(in);
    v1->setName("variable1");
    v2->setName("variable2");
    v3->setName("variable3");
    v4->setName("variable4");

    c.addVariable(v1);
    c.addVariable(v2);
    c.addVariable(v3);

    c.removeVariable("variable1");
    c.removeVariable(v3);
    std::string a = c.serialise(libcellml::Format::XML);
    EXPECT_EQ(e1, a);
    EXPECT_THROW(c.removeVariable("BAD_NAME"), std::out_of_range);

    c.addVariable(v4);
    c.removeAllVariables();
    a = c.serialise(libcellml::Format::XML);
    EXPECT_EQ(e2, a);
    EXPECT_THROW(c.removeVariable(v5), std::out_of_range);
}

TEST(Variable, getVariableMethods) {
    const std::string in = "valid_name";
    libcellml::Component c;
    c.setName(in);

    libcellml::VariablePtr v1 = std::make_shared<libcellml::Variable>();
    v1->setName("variable1");
    c.addVariable(v1);
    libcellml::VariablePtr v2 = std::make_shared<libcellml::Variable>();
    v2->setName("variable2");
    c.addVariable(v2);
    libcellml::VariablePtr v3 = std::make_shared<libcellml::Variable>();
    v3->setName("variable3");
    c.addVariable(v3);
    libcellml::VariablePtr v4 = std::make_shared<libcellml::Variable>();
    v4->setName("variable4");
    c.addVariable(v4);

    // Get by string
    libcellml::VariablePtr vMethod1 = c.getVariable("variable1");
    std::string a1 = vMethod1->getName();
    EXPECT_EQ("variable1", a1);

    // Get by index
    libcellml::VariablePtr vMethod2 = c.getVariable(1);
    std::string a2 = vMethod2->getName();
    EXPECT_EQ("variable2", a2);

    // Get const by string
    const libcellml::VariablePtr vMethod3 = static_cast<const libcellml::Component>(c).getVariable("variable3");
    std::string a3 = vMethod3->getName();
    EXPECT_EQ("variable3", a3);

    // Get const by index
    const libcellml::VariablePtr vMethod4 = static_cast<const libcellml::Component>(c).getVariable(3);
    std::string a4 = vMethod4->getName();
    EXPECT_EQ("variable4", a4);
}

TEST(Variable, modelWithComponentWithVariableWithValidName) {
    const std::string in = "valid_name";
    const std::string e =
            "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
            "<model xmlns=\"http://www.cellml.org/cellml/1.2#\">"
              "<component name=\"" + in + "\">"
                "<variable name=\"" + in + "\" units=\"dimensionless\"/>"
              "</component>"
            "</model>";

    libcellml::Model m;

    libcellml::ComponentPtr c = std::make_shared<libcellml::Component>();
    c->setName(in);
    m.addComponent(c);

    libcellml::VariablePtr v = std::make_shared<libcellml::Variable>();
    v->setName(in);
    c->addVariable(v);

    libcellml::UnitsPtr u = std::make_shared<libcellml::Units>();
    u->setName("dimensionless");
    v->setUnits(u);

    std::string a = m.serialise(libcellml::Format::XML);
    EXPECT_EQ(e, a);
    EXPECT_EQ("valid_name", v->getName());
}

TEST(Variable, modelWithComponentWithVariableWithInvalidName) {
    const std::string in = "invalid name";
    const std::string e =
            "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
            "<model xmlns=\"http://www.cellml.org/cellml/1.2#\">"
              "<component name=\"" + in + "\">"
                "<variable name=\"" + in + "\" units=\"dimensionless\"/>"
              "</component>"
            "</model>";

    libcellml::Model m;

    libcellml::ComponentPtr c = std::make_shared<libcellml::Component>();
    c->setName(in);
    m.addComponent(c);

    libcellml::VariablePtr v = std::make_shared<libcellml::Variable>();
    v->setName(in);
    c->addVariable(v);

    libcellml::UnitsPtr u = std::make_shared<libcellml::Units>();
    u->setName("dimensionless");
    v->setUnits(u);

    std::string a = m.serialise(libcellml::Format::XML);
    EXPECT_EQ(e, a);
    EXPECT_EQ("invalid name", v->getName());
}

TEST(Variable, modelWithComponentWithVariableWithInvalidUnitsName) {
    const std::string in = "valid_name";
    const std::string e =
            "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
            "<model xmlns=\"http://www.cellml.org/cellml/1.2#\">"
              "<component name=\"" + in + "\">"
                "<variable name=\"" + in + "\" units=\"invalid name\"/>"
              "</component>"
            "</model>";

    libcellml::Model m;

    libcellml::ComponentPtr c = std::make_shared<libcellml::Component>();
    c->setName(in);
    m.addComponent(c);

    libcellml::VariablePtr v = std::make_shared<libcellml::Variable>();
    v->setName(in);
    c->addVariable(v);

    libcellml::UnitsPtr u = std::make_shared<libcellml::Units>();
    u->setName("invalid name");
    v->setUnits(u);

    std::string a = m.serialise(libcellml::Format::XML);
    EXPECT_EQ(e, a);
    EXPECT_EQ("invalid name", u->getName());
}

TEST(Variable, modelWithComponentWithTwoNamedVariablesWithInitialValues) {
    const std::string in = "valid_name";
    const std::string e =
            "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
            "<model xmlns=\"http://www.cellml.org/cellml/1.2#\">"
                "<component name=\"" + in + "\">"
                    "<variable name=\"variable1\" initial_value=\"1.0\"/>"
                    "<variable name=\"variable2\" initial_value=\"-1.0\"/>"
                "</component>"
            "</model>";

    libcellml::Model m;

    libcellml::ComponentPtr c = std::make_shared<libcellml::Component>();
    c->setName(in);
    m.addComponent(c);

    libcellml::VariablePtr v1 = std::make_shared<libcellml::Variable>();
    v1->setName("variable1");
    v1->setInitialValue("1.0");
    c->addVariable(v1);

    libcellml::VariablePtr v2 = std::make_shared<libcellml::Variable>();
    v2->setName("variable2");
    v2->setInitialValue("-1.0");
    c->addVariable(v2);

    std::string a = m.serialise(libcellml::Format::XML);
    EXPECT_EQ(e, a);
}

TEST(Variable, modelWithComponentWithTwoNamedVariablesWithInitialValuesOneReferenced) {
    const std::string in = "valid_name";
    const std::string e =
            "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
            "<model xmlns=\"http://www.cellml.org/cellml/1.2#\">"
                "<component name=\"" + in + "\">"
                    "<variable name=\"variable1\" initial_value=\"1\"/>"
                    "<variable name=\"variable2\" initial_value=\"variable1\"/>"
                "</component>"
            "</model>";

    libcellml::Model m;

    libcellml::ComponentPtr c = std::make_shared<libcellml::Component>();
    c->setName(in);
    m.addComponent(c);

    libcellml::VariablePtr v1 = std::make_shared<libcellml::Variable>();
    v1->setName("variable1");
    v1->setInitialValue(1.0);
    c->addVariable(v1);

    libcellml::VariablePtr v2 = std::make_shared<libcellml::Variable>();
    v2->setName("variable2");
    v2->setInitialValue(v1);
    c->addVariable(v2);

    std::string a = m.serialise(libcellml::Format::XML);
    EXPECT_EQ(e, a);
}




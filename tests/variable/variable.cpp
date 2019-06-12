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

TEST(Variable, setValidVariableName)
{
    const std::string in = "valid_name";
    const std::string e = "<variable name=\"valid_name\"/>\n";
    libcellml::Variable v;
    v.setName(in);
    libcellml::Printer printer;
    const std::string a = printer.printVariable(v);
    EXPECT_EQ(e, a);
}

TEST(Variable, setInvalidVariableName)
{
    const std::string in = "invalid name";
    const std::string e = "<variable name=\"invalid name\"/>\n";
    libcellml::Variable v;
    v.setName(in);
    libcellml::Printer printer;
    const std::string a = printer.printVariable(v);
    EXPECT_EQ(e, a);
}

TEST(Variable, getValidVariableName)
{
    const std::string in = "valid_name";
    const std::string e = in;
    libcellml::Variable v;
    v.setName(in);
    const std::string a = v.getName();
    EXPECT_EQ(e, a);
}

TEST(Variable, getInvalidVariableName)
{
    const std::string in = "invalid name";
    const std::string e = in;
    libcellml::Variable v;
    v.setName(in);
    const std::string a = v.getName();
    EXPECT_EQ(e, a);
}

TEST(Variable, setUnits)
{
    const std::string in = "dimensionless";
    const std::string e = "<variable units=\"dimensionless\"/>\n";
    libcellml::Variable v;

    libcellml::UnitsPtr u = std::make_shared<libcellml::Units>();
    u->setName(in);
    v.setUnits(u);

    libcellml::Printer printer;
    const std::string a = printer.printVariable(v);
    EXPECT_EQ(e, a);
}

TEST(Variable, setUnitsAndName)
{
    const std::string in = "valid_name";
    const std::string e = "<variable name=\"valid_name\" units=\"dimensionless\"/>\n";
    libcellml::Variable v;
    v.setName(in);

    libcellml::UnitsPtr u = std::make_shared<libcellml::Units>();
    u->setName("dimensionless");
    v.setUnits(u);

    libcellml::Printer printer;
    const std::string a = printer.printVariable(v);
    EXPECT_EQ(e, a);
}

TEST(Variable, setInitialValueByString)
{
    const std::string e = "<variable initial_value=\"0.0\"/>\n";
    libcellml::Variable v;
    v.setInitialValue("0.0");
    libcellml::Printer printer;
    const std::string a = printer.printVariable(v);
    EXPECT_EQ(e, a);
}

TEST(Variable, setInitialValueByDouble)
{
    const std::string e = "<variable initial_value=\"0\"/>\n";
    libcellml::Variable v;
    double value = 0.0;
    v.setInitialValue(value);
    libcellml::Printer printer;
    const std::string a = printer.printVariable(v);
    EXPECT_EQ(e, a);
}

TEST(Variable, setInitialValueByReference)
{
    const std::string e = "<variable initial_value=\"referencedVariable\"/>\n";
    libcellml::VariablePtr v1 = std::make_shared<libcellml::Variable>();
    v1->setName("referencedVariable");
    libcellml::Variable v2;
    v2.setInitialValue(v1);
    libcellml::Printer printer;
    const std::string a = printer.printVariable(v2);
    EXPECT_EQ(e, a);
}

TEST(Variable, getUnsetInitialValue)
{
    libcellml::Variable v;
    EXPECT_EQ(v.getInitialValue(), "");
}

TEST(Variable, getSetInitialValue)
{
    libcellml::Variable v;
    const std::string e = "0.0";
    v.setInitialValue(e);
    const std::string a = v.getInitialValue();
    EXPECT_EQ(e, a);
}

TEST(Variable, setInterfaceTypeByInvalidString)
{
    const std::string e = "<variable interface=\"invalid\"/>\n";
    libcellml::Variable v;
    v.setInterfaceType("invalid");
    libcellml::Printer printer;
    const std::string a = printer.printVariable(v);
    EXPECT_EQ(e, a);
}

TEST(Variable, setInterfaceTypeNoneByValidString)
{
    const std::string e = "<variable interface=\"none\"/>\n";
    libcellml::Variable v;
    v.setInterfaceType("none");
    libcellml::Printer printer;
    const std::string a = printer.printVariable(v);
    EXPECT_EQ(e, a);
}

TEST(Variable, setInterfaceTypeNoneByEnum)
{
    const std::string e = "<variable interface=\"none\"/>\n";
    libcellml::Variable v;
    v.setInterfaceType(libcellml::Variable::InterfaceType::NONE);
    libcellml::Printer printer;
    const std::string a = printer.printVariable(v);
    EXPECT_EQ(e, a);
}

TEST(Variable, setInterfaceTypePrivate)
{
    const std::string e = "<variable interface=\"private\"/>\n";
    libcellml::Variable v;
    v.setInterfaceType(libcellml::Variable::InterfaceType::PRIVATE);
    libcellml::Printer printer;
    const std::string a = printer.printVariable(v);
    EXPECT_EQ(e, a);
}

TEST(Variable, setInterfaceTypePublic)
{
    const std::string e = "<variable interface=\"public\"/>\n";
    libcellml::Variable v;
    v.setInterfaceType(libcellml::Variable::InterfaceType::PUBLIC);
    libcellml::Printer printer;
    const std::string a = printer.printVariable(v);
    EXPECT_EQ(e, a);
}

TEST(Variable, setInterfaceTypePublicAndPrivate)
{
    const std::string e = "<variable interface=\"public_and_private\"/>\n";
    libcellml::Variable v;
    v.setInterfaceType(libcellml::Variable::InterfaceType::PUBLIC_AND_PRIVATE);
    libcellml::Printer printer;
    const std::string a = printer.printVariable(v);
    EXPECT_EQ(e, a);
}

TEST(Variable, setGetInterfaceType)
{
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

TEST(Variable, addVariable)
{
    const std::string in = "valid_name";
    const std::string e =
        "<component name=\"valid_name\">\n"
        "  <variable name=\"valid_name\" units=\"dimensionless\"/>\n"
        "</component>\n";

    libcellml::Component c;
    c.setName(in);

    libcellml::VariablePtr v = std::make_shared<libcellml::Variable>();
    v->setName(in);
    c.addVariable(v);

    libcellml::UnitsPtr u = std::make_shared<libcellml::Units>();
    u->setName("dimensionless");
    v->setUnits(u);

    libcellml::Printer printer;
    const std::string a = printer.printComponent(c);
    EXPECT_EQ(e, a);
}

TEST(Variable, getParentComponent)
{
    libcellml::Component c;
    libcellml::VariablePtr v = std::make_shared<libcellml::Variable>();
    c.addVariable(v);
    EXPECT_EQ(&c, v->getParent());
}

TEST(Variable, getNullParentComponent)
{
    libcellml::VariablePtr v = std::make_shared<libcellml::Variable>();
    EXPECT_EQ(nullptr, v->getParent());
}

TEST(Variable, hasDirectEquivalentVariable)
{
    libcellml::VariablePtr v1 = std::make_shared<libcellml::Variable>();
    libcellml::VariablePtr v2 = std::make_shared<libcellml::Variable>();
    libcellml::VariablePtr v3 = std::make_shared<libcellml::Variable>();
    libcellml::VariablePtr v4 = std::make_shared<libcellml::Variable>();
    libcellml::VariablePtr v5 = std::make_shared<libcellml::Variable>();

    EXPECT_FALSE(v1->hasDirectEquivalentVariable(v1));
    EXPECT_FALSE(v1->hasDirectEquivalentVariable(v2));
    EXPECT_FALSE(v1->hasDirectEquivalentVariable(v3));
    EXPECT_FALSE(v1->hasDirectEquivalentVariable(v4));
    EXPECT_FALSE(v1->hasDirectEquivalentVariable(v5));

    EXPECT_FALSE(v2->hasDirectEquivalentVariable(v1));
    EXPECT_FALSE(v2->hasDirectEquivalentVariable(v2));
    EXPECT_FALSE(v2->hasDirectEquivalentVariable(v3));
    EXPECT_FALSE(v2->hasDirectEquivalentVariable(v4));
    EXPECT_FALSE(v2->hasDirectEquivalentVariable(v5));

    EXPECT_FALSE(v3->hasDirectEquivalentVariable(v1));
    EXPECT_FALSE(v3->hasDirectEquivalentVariable(v2));
    EXPECT_FALSE(v3->hasDirectEquivalentVariable(v3));
    EXPECT_FALSE(v3->hasDirectEquivalentVariable(v4));
    EXPECT_FALSE(v3->hasDirectEquivalentVariable(v5));

    EXPECT_FALSE(v4->hasDirectEquivalentVariable(v1));
    EXPECT_FALSE(v4->hasDirectEquivalentVariable(v2));
    EXPECT_FALSE(v4->hasDirectEquivalentVariable(v3));
    EXPECT_FALSE(v4->hasDirectEquivalentVariable(v4));
    EXPECT_FALSE(v4->hasDirectEquivalentVariable(v5));

    EXPECT_FALSE(v5->hasDirectEquivalentVariable(v1));
    EXPECT_FALSE(v5->hasDirectEquivalentVariable(v2));
    EXPECT_FALSE(v5->hasDirectEquivalentVariable(v3));
    EXPECT_FALSE(v5->hasDirectEquivalentVariable(v4));
    EXPECT_FALSE(v5->hasDirectEquivalentVariable(v5));

    libcellml::Variable::addEquivalence(v1, v2);
    libcellml::Variable::addEquivalence(v2, v3);
    libcellml::Variable::addEquivalence(v3, v4);
    libcellml::Variable::addEquivalence(v4, v5);

    EXPECT_FALSE(v1->hasDirectEquivalentVariable(v1));
    EXPECT_TRUE(v1->hasDirectEquivalentVariable(v2));
    EXPECT_FALSE(v1->hasDirectEquivalentVariable(v3));
    EXPECT_FALSE(v1->hasDirectEquivalentVariable(v4));
    EXPECT_FALSE(v1->hasDirectEquivalentVariable(v5));

    EXPECT_TRUE(v2->hasDirectEquivalentVariable(v1));
    EXPECT_FALSE(v2->hasDirectEquivalentVariable(v2));
    EXPECT_TRUE(v2->hasDirectEquivalentVariable(v3));
    EXPECT_FALSE(v2->hasDirectEquivalentVariable(v4));
    EXPECT_FALSE(v2->hasDirectEquivalentVariable(v5));

    EXPECT_FALSE(v3->hasDirectEquivalentVariable(v1));
    EXPECT_TRUE(v3->hasDirectEquivalentVariable(v2));
    EXPECT_FALSE(v3->hasDirectEquivalentVariable(v3));
    EXPECT_TRUE(v3->hasDirectEquivalentVariable(v4));
    EXPECT_FALSE(v3->hasDirectEquivalentVariable(v5));

    EXPECT_FALSE(v4->hasDirectEquivalentVariable(v1));
    EXPECT_FALSE(v4->hasDirectEquivalentVariable(v2));
    EXPECT_TRUE(v4->hasDirectEquivalentVariable(v3));
    EXPECT_FALSE(v4->hasDirectEquivalentVariable(v4));
    EXPECT_TRUE(v4->hasDirectEquivalentVariable(v5));

    EXPECT_FALSE(v5->hasDirectEquivalentVariable(v1));
    EXPECT_FALSE(v5->hasDirectEquivalentVariable(v2));
    EXPECT_FALSE(v5->hasDirectEquivalentVariable(v3));
    EXPECT_TRUE(v5->hasDirectEquivalentVariable(v4));
    EXPECT_FALSE(v5->hasDirectEquivalentVariable(v5));
}

TEST(Variable, hasEquivalentVariable)
{
    libcellml::VariablePtr v1 = std::make_shared<libcellml::Variable>();
    libcellml::VariablePtr v2 = std::make_shared<libcellml::Variable>();
    libcellml::VariablePtr v3 = std::make_shared<libcellml::Variable>();
    libcellml::VariablePtr v4 = std::make_shared<libcellml::Variable>();
    libcellml::VariablePtr v5 = std::make_shared<libcellml::Variable>();

    EXPECT_FALSE(v1->hasEquivalentVariable(v1));
    EXPECT_FALSE(v1->hasEquivalentVariable(v2));
    EXPECT_FALSE(v1->hasEquivalentVariable(v3));
    EXPECT_FALSE(v1->hasEquivalentVariable(v4));
    EXPECT_FALSE(v1->hasEquivalentVariable(v5));

    EXPECT_FALSE(v2->hasEquivalentVariable(v1));
    EXPECT_FALSE(v2->hasEquivalentVariable(v2));
    EXPECT_FALSE(v2->hasEquivalentVariable(v3));
    EXPECT_FALSE(v2->hasEquivalentVariable(v4));
    EXPECT_FALSE(v2->hasEquivalentVariable(v5));

    EXPECT_FALSE(v3->hasEquivalentVariable(v1));
    EXPECT_FALSE(v3->hasEquivalentVariable(v2));
    EXPECT_FALSE(v3->hasEquivalentVariable(v3));
    EXPECT_FALSE(v3->hasEquivalentVariable(v4));
    EXPECT_FALSE(v3->hasEquivalentVariable(v5));

    EXPECT_FALSE(v4->hasEquivalentVariable(v1));
    EXPECT_FALSE(v4->hasEquivalentVariable(v2));
    EXPECT_FALSE(v4->hasEquivalentVariable(v3));
    EXPECT_FALSE(v4->hasEquivalentVariable(v4));
    EXPECT_FALSE(v4->hasEquivalentVariable(v5));

    EXPECT_FALSE(v5->hasEquivalentVariable(v1));
    EXPECT_FALSE(v5->hasEquivalentVariable(v2));
    EXPECT_FALSE(v5->hasEquivalentVariable(v3));
    EXPECT_FALSE(v5->hasEquivalentVariable(v4));
    EXPECT_FALSE(v5->hasEquivalentVariable(v5));

    libcellml::Variable::addEquivalence(v1, v2);
    libcellml::Variable::addEquivalence(v2, v3);
    libcellml::Variable::addEquivalence(v3, v4);
    libcellml::Variable::addEquivalence(v4, v5);

    EXPECT_FALSE(v1->hasEquivalentVariable(v1));
    EXPECT_TRUE(v1->hasEquivalentVariable(v2));
    EXPECT_TRUE(v1->hasEquivalentVariable(v3));
    EXPECT_TRUE(v1->hasEquivalentVariable(v4));
    EXPECT_TRUE(v1->hasEquivalentVariable(v5));

    EXPECT_TRUE(v2->hasEquivalentVariable(v1));
    EXPECT_FALSE(v2->hasEquivalentVariable(v2));
    EXPECT_TRUE(v2->hasEquivalentVariable(v3));
    EXPECT_TRUE(v2->hasEquivalentVariable(v4));
    EXPECT_TRUE(v2->hasEquivalentVariable(v5));

    EXPECT_TRUE(v3->hasEquivalentVariable(v1));
    EXPECT_TRUE(v3->hasEquivalentVariable(v2));
    EXPECT_FALSE(v3->hasEquivalentVariable(v3));
    EXPECT_TRUE(v3->hasEquivalentVariable(v4));
    EXPECT_TRUE(v3->hasEquivalentVariable(v5));

    EXPECT_TRUE(v4->hasEquivalentVariable(v1));
    EXPECT_TRUE(v4->hasEquivalentVariable(v2));
    EXPECT_TRUE(v4->hasEquivalentVariable(v3));
    EXPECT_FALSE(v4->hasEquivalentVariable(v4));
    EXPECT_TRUE(v4->hasEquivalentVariable(v5));

    EXPECT_TRUE(v5->hasEquivalentVariable(v1));
    EXPECT_TRUE(v5->hasEquivalentVariable(v2));
    EXPECT_TRUE(v5->hasEquivalentVariable(v3));
    EXPECT_TRUE(v5->hasEquivalentVariable(v4));
    EXPECT_FALSE(v5->hasEquivalentVariable(v5));
}

TEST(Variable, addVariableToUnnamedComponent)
{
    const std::string in = "valid_name";
    const std::string e =
        "<component>\n"
        "  <variable name=\"valid_name\"/>\n"
        "</component>\n";

    libcellml::Component c;

    libcellml::VariablePtr v = std::make_shared<libcellml::Variable>();
    v->setName(in);
    c.addVariable(v);

    libcellml::Printer printer;
    const std::string a = printer.printComponent(c);
    EXPECT_EQ(e, a);
}

TEST(Variable, addTwoVariables)
{
    const std::string in = "valid_name";
    const std::string e =
        "<component name=\"valid_name\">\n"
        "  <variable name=\"variable1\"/>\n"
        "  <variable name=\"variable2\"/>\n"
        "</component>\n";

    libcellml::Component c;
    c.setName(in);

    libcellml::VariablePtr v1 = std::make_shared<libcellml::Variable>();
    v1->setName("variable1");
    c.addVariable(v1);

    libcellml::VariablePtr v2 = std::make_shared<libcellml::Variable>();
    v2->setName("variable2");
    c.addVariable(v2);

    libcellml::Printer printer;
    const std::string a = printer.printComponent(c);
    EXPECT_EQ(e, a);
}

TEST(Variable, addVariablesWithAndWithoutNameAndUnits)
{
    const std::string e =
        "<component>\n"
        "  <variable name=\"var1\" units=\"dimensionless\"/>\n"
        "  <variable name=\"var2\"/>\n"
        "  <variable units=\"dimensionless\"/>\n"
        "  <variable/>\n"
        "</component>\n";

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

    libcellml::Printer printer;
    const std::string a = printer.printComponent(c);
    EXPECT_EQ(e, a);
}

TEST(Variable, componentWithTwoVariablesWithInitialValues)
{
    const std::string in = "valid_name";
    const std::string e =
        "<component name=\"valid_name\">\n"
        "  <variable initial_value=\"1\"/>\n"
        "  <variable initial_value=\"-1\"/>\n"
        "</component>\n";

    libcellml::Component c;
    c.setName(in);

    libcellml::VariablePtr v1 = std::make_shared<libcellml::Variable>();
    v1->setInitialValue(1.0);
    c.addVariable(v1);

    libcellml::VariablePtr v2 = std::make_shared<libcellml::Variable>();
    v2->setInitialValue(-1.0);
    c.addVariable(v2);

    libcellml::Printer printer;
    const std::string a = printer.printComponent(c);
    EXPECT_EQ(e, a);
}

TEST(Variable, removeVariableMethods)
{
    const std::string in = "valid_name";
    const std::string e1 =
        "<component name=\"valid_name\">\n"
        "  <variable name=\"variable2\"/>\n"
        "</component>\n";
    const std::string e2 = "<component name=\"valid_name\"/>\n";

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

    EXPECT_TRUE(c.removeVariable("variable1"));
    EXPECT_TRUE(c.removeVariable(v3));
    libcellml::Printer printer;
    std::string a = printer.printComponent(c);
    EXPECT_EQ(e1, a);
    EXPECT_FALSE(c.removeVariable("BAD_NAME"));

    c.addVariable(v4);
    c.removeAllVariables();
    a = printer.printComponent(c);
    EXPECT_EQ(e2, a);
    EXPECT_FALSE(c.removeVariable(v5));

    c.addVariable(v1);
    c.addVariable(v2);
    c.addVariable(v3);

    EXPECT_TRUE(c.removeVariable(0)); // v1
    EXPECT_TRUE(c.removeVariable(1)); // new index of v3
    a = printer.printComponent(c);
    EXPECT_EQ(e1, a);
    EXPECT_FALSE(c.removeVariable(1));
}

TEST(Variable, getVariableMethods)
{
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
    const std::string a1 = vMethod1->getName();
    EXPECT_EQ("variable1", a1);

    // Get by index
    libcellml::VariablePtr vMethod2 = c.getVariable(1);
    const std::string a2 = vMethod2->getName();
    EXPECT_EQ("variable2", a2);

    // Get const by string
    const libcellml::VariablePtr vMethod3 = static_cast<const libcellml::Component>(c).getVariable("variable3");
    const std::string a3 = vMethod3->getName();
    EXPECT_EQ("variable3", a3);

    // Get const by index
    const libcellml::VariablePtr vMethod4 = static_cast<const libcellml::Component>(c).getVariable(3);
    const std::string a4 = vMethod4->getName();
    EXPECT_EQ("variable4", a4);

    // Get invalid index
    EXPECT_EQ(nullptr, static_cast<const libcellml::Component>(c).getVariable(42));
    EXPECT_EQ(nullptr, c.getVariable(7));

    // Get non-existent variable by string
    EXPECT_EQ(nullptr, c.getVariable("notreal"));
    EXPECT_EQ(nullptr, static_cast<const libcellml::Component>(c).getVariable("doesntexist"));
}

TEST(Variable, takeVariableMethods)
{
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

    // Take by index
    libcellml::VariablePtr tv = c.takeVariable(0);
    std::string tvn = tv->getName();
    EXPECT_EQ("variable1", tvn);
    libcellml::VariablePtr gv = c.getVariable(0);
    std::string gvn = gv->getName();
    EXPECT_EQ("variable2", gvn);
    tv = c.takeVariable(0);
    tvn = tv->getName();
    EXPECT_EQ("variable2", tvn);
    gv = c.getVariable(0);
    gvn = gv->getName();
    EXPECT_EQ("variable3", gvn);

    // Take by string
    libcellml::VariablePtr tv3 = c.takeVariable("variable3");
    const std::string tvn3 = tv3->getName();
    EXPECT_EQ("variable3", tvn3);

    // Get invalid index
    EXPECT_EQ(nullptr, c.takeVariable(737));

    // Get non-existent variable by string
    EXPECT_EQ(nullptr, c.takeVariable("notreal"));
    EXPECT_EQ(nullptr, c.takeVariable("doesntexist"));
}

TEST(Variable, modelWithComponentWithVariableWithValidName)
{
    const std::string in = "valid_name";
    const std::string e =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/2.0#\">\n"
        "  <component name=\"valid_name\">\n"
        "    <variable name=\"valid_name\" units=\"dimensionless\"/>\n"
        "  </component>\n"
        "</model>\n";

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

    libcellml::Printer printer;
    const std::string a = printer.printModel(m);
    EXPECT_EQ(e, a);
    EXPECT_EQ("valid_name", v->getName());
}

TEST(Variable, modelWithComponentWithVariableWithInvalidName)
{
    const std::string in = "invalid name";
    const std::string e =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/2.0#\">\n"
        "  <component name=\"invalid name\">\n"
        "    <variable name=\"invalid name\" units=\"dimensionless\"/>\n"
        "  </component>\n"
        "</model>\n";

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

    libcellml::Printer printer;
    const std::string a = printer.printModel(m);
    EXPECT_EQ(e, a);
    EXPECT_EQ("invalid name", v->getName());
}

TEST(Variable, modelWithComponentWithVariableWithInvalidUnitsNameAndParse)
{
    const std::string in = "valid_name";
    const std::string e =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/2.0#\">\n"
        "  <component name=\"valid_name\">\n"
        "    <variable name=\"valid_name\" units=\"invalid name\"/>\n"
        "  </component>\n"
        "</model>\n";

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

    libcellml::Printer printer;
    std::string a = printer.printModel(m);
    EXPECT_EQ(e, a);
    EXPECT_EQ("invalid name", u->getName());

    // Parse
    libcellml::Parser parser;
    libcellml::ModelPtr model = parser.parseModel(e);
    a = printer.printModel(model);
    EXPECT_EQ(e, a);
}

TEST(Variable, modelWithComponentWithTwoNamedVariablesWithInitialValues)
{
    const std::string in = "valid_name";
    const std::string e =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/2.0#\">\n"
        "  <component name=\"valid_name\">\n"
        "    <variable name=\"variable1\" initial_value=\"1.0\"/>\n"
        "    <variable name=\"variable2\" initial_value=\"-1.0\"/>\n"
        "  </component>\n"
        "</model>\n";

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

    libcellml::Printer printer;
    const std::string a = printer.printModel(m);
    EXPECT_EQ(e, a);
}

TEST(Variable, modelWithComponentWithTwoNamedVariablesWithInitialValuesOneReferenced)
{
    const std::string in = "valid_name";
    const std::string e =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/2.0#\">\n"
        "  <component name=\"valid_name\">\n"
        "    <variable name=\"variable1\" initial_value=\"1\"/>\n"
        "    <variable name=\"variable2\" initial_value=\"variable1\"/>\n"
        "  </component>\n"
        "</model>\n";

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

    libcellml::Printer printer;
    const std::string a = printer.printModel(m);
    EXPECT_EQ(e, a);
}

TEST(Variable, modelWithComponentWithTwoNamedVariablesWithInitialValuesAndParse)
{
    const std::string in = "valid_name";
    const std::string e =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/2.0#\">\n"
        "  <component name=\"valid_name\">\n"
        "    <variable name=\"variable1\" initial_value=\"1.0\"/>\n"
        "    <variable name=\"variable2\" initial_value=\"-1.0\"/>\n"
        "  </component>\n"
        "</model>\n";

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

    libcellml::Parser parser;
    libcellml::ModelPtr model = parser.parseModel(e);
    libcellml::Printer printer;
    const std::string a = printer.printModel(model);
    EXPECT_EQ(e, a);
}

TEST(Variable, modelWithComponentWithFourNamedVariablesWithInterfaces)
{
    const std::string e =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/2.0#\">\n"
        "  <component name=\"valid_name\">\n"
        "    <variable name=\"variable1\" interface=\"none\"/>\n"
        "    <variable name=\"variable2\" interface=\"public\"/>\n"
        "    <variable name=\"variable3\" interface=\"private\"/>\n"
        "    <variable name=\"variable4\" interface=\"public_and_private\"/>\n"
        "  </component>\n"
        "</model>\n";

    libcellml::Model m;

    libcellml::ComponentPtr c = std::make_shared<libcellml::Component>();
    c->setName("valid_name");
    m.addComponent(c);

    libcellml::VariablePtr v1 = std::make_shared<libcellml::Variable>();
    v1->setName("variable1");
    v1->setInterfaceType(libcellml::Variable::InterfaceType::NONE);
    c->addVariable(v1);

    libcellml::VariablePtr v2 = std::make_shared<libcellml::Variable>();
    v2->setName("variable2");
    v2->setInterfaceType(libcellml::Variable::InterfaceType::PUBLIC);
    c->addVariable(v2);

    libcellml::VariablePtr v3 = std::make_shared<libcellml::Variable>();
    v3->setName("variable3");
    v3->setInterfaceType(libcellml::Variable::InterfaceType::PRIVATE);
    c->addVariable(v3);

    libcellml::VariablePtr v4 = std::make_shared<libcellml::Variable>();
    v4->setName("variable4");
    v4->setInterfaceType(libcellml::Variable::InterfaceType::PUBLIC_AND_PRIVATE);
    c->addVariable(v4);

    libcellml::Printer printer;
    const std::string a = printer.printModel(m);
    EXPECT_EQ(e, a);
}

TEST(Variable, modelWithComponentWithFourNamedVariablesWithInterfacesAndParse)
{
    const std::string e =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/2.0#\">\n"
        "  <component name=\"valid_name\">\n"
        "    <variable name=\"variable1\" interface=\"none\"/>\n"
        "    <variable name=\"variable2\" interface=\"public\"/>\n"
        "    <variable name=\"variable3\" interface=\"private\"/>\n"
        "    <variable name=\"variable4\" interface=\"public_and_private\"/>\n"
        "  </component>\n"
        "</model>\n";

    libcellml::Model m;

    libcellml::ComponentPtr c = std::make_shared<libcellml::Component>();
    c->setName("valid_name");
    m.addComponent(c);

    libcellml::VariablePtr v1 = std::make_shared<libcellml::Variable>();
    v1->setName("variable1");
    v1->setInterfaceType(libcellml::Variable::InterfaceType::NONE);
    c->addVariable(v1);

    libcellml::VariablePtr v2 = std::make_shared<libcellml::Variable>();
    v2->setName("variable2");
    v2->setInterfaceType("public");
    c->addVariable(v2);

    libcellml::VariablePtr v3 = std::make_shared<libcellml::Variable>();
    v3->setName("variable3");
    v3->setInterfaceType(libcellml::Variable::InterfaceType::PRIVATE);
    c->addVariable(v3);

    libcellml::VariablePtr v4 = std::make_shared<libcellml::Variable>();
    v4->setName("variable4");
    v4->setInterfaceType(libcellml::Variable::InterfaceType::PUBLIC_AND_PRIVATE);
    c->addVariable(v4);

    libcellml::Parser parser;
    libcellml::ModelPtr model = parser.parseModel(e);
    libcellml::Printer printer;
    const std::string a = printer.printModel(model);
    EXPECT_EQ(e, a);
}

TEST(Variable, modelWithComponentWithFiveNamedVariablesWithInterfacesAndParse)
{
    const std::string e =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/2.0#\">\n"
        "  <component name=\"valid_name\">\n"
        "    <variable name=\"variable1\" interface=\"none\"/>\n"
        "    <variable name=\"variable2\" interface=\"public\"/>\n"
        "    <variable name=\"variable3\" interface=\"private\"/>\n"
        "    <variable name=\"variable4\" interface=\"public_and_private\"/>\n"
        "    <variable name=\"variable5\"/>\n"
        "  </component>\n"
        "</model>\n";

    libcellml::Model m;

    libcellml::ComponentPtr c = std::make_shared<libcellml::Component>();
    c->setName("valid_name");
    m.addComponent(c);

    libcellml::VariablePtr v1 = std::make_shared<libcellml::Variable>();
    v1->setName("variable1");
    v1->setInterfaceType(libcellml::Variable::InterfaceType::NONE);
    c->addVariable(v1);

    libcellml::VariablePtr v2 = std::make_shared<libcellml::Variable>();
    v2->setName("variable2");
    v2->setInterfaceType("public");
    c->addVariable(v2);

    libcellml::VariablePtr v3 = std::make_shared<libcellml::Variable>();
    v3->setName("variable3");
    v3->setInterfaceType(libcellml::Variable::InterfaceType::PRIVATE);
    c->addVariable(v3);

    libcellml::VariablePtr v4 = std::make_shared<libcellml::Variable>();
    v4->setName("variable4");
    v4->setInterfaceType(libcellml::Variable::InterfaceType::PUBLIC_AND_PRIVATE);
    c->addVariable(v4);

    libcellml::VariablePtr v5 = std::make_shared<libcellml::Variable>();
    v5->setName("variable4");
    v5->setInterfaceType("other");
    c->addVariable(v5);

    libcellml::Parser parser;
    libcellml::ModelPtr model = parser.parseModel(e);
    libcellml::Printer printer;
    const std::string a = printer.printModel(model);
    EXPECT_EQ(e, a);
}

TEST(Variable, modelUnitsAttributeBeforeNameAttribute)
{
    const std::string e =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/2.0#\">\n"
        "  <component name=\"valid_name\">\n"
        "    <variable units=\"dimensionless\" name=\"variable1\" interface=\"none\"/>\n"
        "    <variable id=\"sin\" units=\"dimensionless\" name=\"sin1\" interface=\"public_and_private\"/>\n"
        "    <variable id=\"deriv_approx_initial_value\" units=\"dimensionless\" initial_value=\"0\" name=\"deriv_approx_initial_value\" interface=\"public_and_private\"/>\n"
        "  </component>\n"
        "</model>\n";

    libcellml::Model m;

    libcellml::Parser parser;
    parser.parseModel(e);
    EXPECT_EQ(size_t(0), parser.errorCount());
}

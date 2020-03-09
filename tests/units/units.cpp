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

TEST(Units, construct)
{
    libcellml::UnitsPtr u = libcellml::Units::create();
    u->setName("valid_name");
    EXPECT_EQ("valid_name", u->name());

    const std::string validName = "another_valid_name";
    auto u2 = libcellml::Units::create(validName);
    EXPECT_EQ("another_valid_name", u2->name());
}

TEST(Units, validName)
{
    const std::string e =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/2.0#\">\n"
        "  <units name=\"valid_name\"/>\n"
        "</model>\n";

    libcellml::ModelPtr m = libcellml::Model::create();

    libcellml::UnitsPtr u = libcellml::Units::create();
    u->setName("valid_name");

    m->addUnits(u);

    libcellml::PrinterPtr printer = libcellml::Printer::create();
    const std::string a = printer->printModel(m);
    EXPECT_EQ(e, a);
    EXPECT_EQ("valid_name", u->name());
}

TEST(Units, invalidName)
{
    const std::string e =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/2.0#\">\n"
        "  <units name=\"invalid name\"/>\n"
        "</model>\n";

    libcellml::ModelPtr m = libcellml::Model::create();

    libcellml::UnitsPtr u = libcellml::Units::create();
    u->setName("invalid name");

    m->addUnits(u);

    libcellml::PrinterPtr printer = libcellml::Printer::create();
    const std::string a = printer->printModel(m);
    EXPECT_EQ(e, a);
    EXPECT_EQ("invalid name", u->name());
}

TEST(Units, compoundUnitsRaw)
{
    const std::string e =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/2.0#\">\n"
        "  <units name=\"compound_unit\">\n"
        "    <unit prefix=\"-6\" units=\"ampere\"/>\n"
        "    <unit units=\"kelvin\"/>\n"
        "    <unit exponent=\"-1\" prefix=\"-3\" units=\"siemens\"/>\n"
        "  </units>\n"
        "</model>\n";

    libcellml::ModelPtr m = libcellml::Model::create();

    libcellml::UnitsPtr u = libcellml::Units::create();
    u->setName("compound_unit");

    u->addUnit("ampere", -6, 1.0);
    u->addUnit("kelvin");
    u->addUnit("siemens", -3, -1.0);

    m->addUnits(u);

    libcellml::PrinterPtr printer = libcellml::Printer::create();
    const std::string a = printer->printModel(m);
    EXPECT_EQ(e, a);
}

TEST(Units, addUnitsVariations)
{
    libcellml::UnitsPtr u = libcellml::Units::create();
    u->setName("compound_unit");

    u->addUnit(libcellml::Units::StandardUnit::AMPERE, libcellml::Units::Prefix::MICRO);
    u->addUnit(libcellml::Units::StandardUnit::KELVIN, -3, 2.0, 5.5);

    EXPECT_EQ(size_t(2), u->unitCount());
}

TEST(Units, compoundUnitsUsingDefines)
{
    const std::string e =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/2.0#\">\n"
        "  <units name=\"compound_unit\">\n"
        "    <unit prefix=\"micro\" units=\"ampere\"/>\n"
        "    <unit units=\"kelvin\"/>\n"
        "    <unit exponent=\"-1\" prefix=\"milli\" units=\"siemens\"/>\n"
        "  </units>\n"
        "</model>\n";

    libcellml::ModelPtr m = libcellml::Model::create();

    libcellml::UnitsPtr u = libcellml::Units::create();
    u->setName("compound_unit");

    u->addUnit(libcellml::Units::StandardUnit::AMPERE, libcellml::Units::Prefix::MICRO);
    u->addUnit(libcellml::Units::StandardUnit::KELVIN);
    u->addUnit(libcellml::Units::StandardUnit::SIEMENS, libcellml::Units::Prefix::MILLI, -1.0);

    m->addUnits(u);

    libcellml::PrinterPtr printer = libcellml::Printer::create();
    const std::string a = printer->printModel(m);
    EXPECT_EQ(e, a);
}

TEST(Units, compoundUnitsUsingDefinesAndStringUnitsAndPrefix)
{
    const std::string e =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/2.0#\">\n"
        "  <units name=\"compound_unit\">\n"
        "    <unit prefix=\"micro\" units=\"ampere\"/>\n"
        "    <unit units=\"kelvin\"/>\n"
        "    <unit exponent=\"-1\" prefix=\"milli\" units=\"siemens\"/>\n"
        "    <unit prefix=\"1.7e310\" units=\"metre\"/>\n"
        "  </units>\n"
        "</model>\n";

    libcellml::ModelPtr m = libcellml::Model::create();

    libcellml::UnitsPtr u = libcellml::Units::create();
    u->setName("compound_unit");

    u->addUnit(libcellml::Units::StandardUnit::AMPERE, "micro");
    u->addUnit("kelvin");
    u->addUnit("siemens", "milli", -1.0);
    u->addUnit("metre", "1.7e310");

    m->addUnits(u);

    libcellml::PrinterPtr printer = libcellml::Printer::create();
    const std::string a = printer->printModel(m);
    EXPECT_EQ(e, a);
}

TEST(Units, removeUnitsMethodsAndCount)
{
    const std::string e1 =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/2.0#\">\n"
        "  <units name=\"compound_unit\">\n"
        "    <unit prefix=\"micro\" units=\"ampere\"/>\n"
        "    <unit units=\"kelvin\"/>\n"
        "    <unit exponent=\"-1\" prefix=\"milli\" units=\"siemens\"/>\n"
        "    <unit prefix=\"1.7e10\" units=\"metre\"/>\n"
        "  </units>\n"
        "  <units name=\"simple_unit_2\"/>\n"
        "  <units name=\"simple_unit_3\"/>\n"
        "  <units name=\"simple_unit_4\"/>\n"
        "</model>\n";
    const std::string e2 =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/2.0#\">\n"
        "  <units name=\"compound_unit\"/>\n"
        "  <units name=\"simple_unit_2\"/>\n"
        "  <units name=\"simple_unit_3\"/>\n"
        "  <units name=\"simple_unit_4\"/>\n"
        "</model>\n";
    const std::string e3 =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/2.0#\">\n"
        "  <units name=\"compound_unit\"/>\n"
        "  <units name=\"simple_unit_4\"/>\n"
        "</model>\n";
    const std::string e4 =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/2.0#\"/>\n";

    libcellml::ModelPtr m = libcellml::Model::create();

    libcellml::UnitsPtr u1 = libcellml::Units::create();
    libcellml::UnitsPtr u2 = libcellml::Units::create();
    libcellml::UnitsPtr u3 = libcellml::Units::create();
    libcellml::UnitsPtr u4 = libcellml::Units::create();
    libcellml::UnitsPtr u5 = libcellml::Units::create();
    u1->setName("compound_unit");
    u2->setName("simple_unit_2");
    u3->setName("simple_unit_3");
    u4->setName("simple_unit_4");

    u1->addUnit(libcellml::Units::StandardUnit::AMPERE, "micro");
    u1->addUnit("kelvin");
    u1->addUnit("siemens", "milli", -1.0);
    u1->addUnit("metre", "1.7e10");
    m->addUnits(u1);
    m->addUnits(u2);
    m->addUnits(u3);
    m->addUnits(u4);

    libcellml::PrinterPtr printer = libcellml::Printer::create();
    std::string a = printer->printModel(m);
    EXPECT_EQ(e1, a);

    u1->removeAllUnits();
    a = printer->printModel(m);
    EXPECT_EQ(e2, a);

    EXPECT_TRUE(m->removeUnits("simple_unit_2"));
    EXPECT_TRUE(m->removeUnits(u3));
    a = printer->printModel(m);
    EXPECT_EQ(e3, a);
    EXPECT_EQ(size_t(2), m->unitsCount());

    EXPECT_FALSE(m->removeUnits("gram"));
    EXPECT_FALSE(m->removeUnits(u5));
    EXPECT_FALSE(m->removeUnits(3));
    EXPECT_EQ(size_t(2), m->unitsCount());

    EXPECT_TRUE(m->removeUnits(1));
    EXPECT_EQ(size_t(1), m->unitsCount());

    m->removeAllUnits();
    a = printer->printModel(m);
    EXPECT_EQ(e4, a);
}

TEST(Units, hasUnitsName)
{
    libcellml::ModelPtr m = libcellml::Model::create();

    libcellml::UnitsPtr u = libcellml::Units::create();
    u->setName("a_unit");

    u->addUnit(libcellml::Units::StandardUnit::AMPERE, "micro");
    m->addUnits(u);
    EXPECT_TRUE(m->hasUnits("a_unit"));
}

TEST(Units, hasUnitsPtr)
{
    libcellml::ModelPtr m = libcellml::Model::create();

    libcellml::UnitsPtr u = libcellml::Units::create();
    u->setName("a_unit");

    u->addUnit(libcellml::Units::StandardUnit::AMPERE, "micro");
    m->addUnits(u);
    EXPECT_TRUE(m->hasUnits(u));
}

TEST(Units, takeUnits)
{
    libcellml::ModelPtr m = libcellml::Model::create();

    libcellml::UnitsPtr u1 = libcellml::Units::create();
    libcellml::UnitsPtr u2 = libcellml::Units::create();
    libcellml::UnitsPtr u3 = libcellml::Units::create();

    u1->setName("a_unit");
    u2->setName("b_unit");
    u3->setName("c_unit");

    u1->addUnit(libcellml::Units::StandardUnit::AMPERE, "micro");
    m->addUnits(u1);
    m->addUnits(u2);
    m->addUnits(u3);

    libcellml::UnitsPtr u4 = m->takeUnits("b_unit");
    EXPECT_EQ("b_unit", u4->name());
    EXPECT_EQ(size_t(2), m->unitsCount());

    libcellml::UnitsPtr u5 = m->takeUnits(1);
    EXPECT_EQ("c_unit", u5->name());
    EXPECT_EQ(size_t(1), m->unitsCount());

    EXPECT_EQ(nullptr, m->takeUnits(7));

    EXPECT_EQ(nullptr, m->takeUnits("d_unit"));
}

TEST(Units, replaceUnits)
{
    libcellml::ModelPtr m = libcellml::Model::create();

    libcellml::UnitsPtr u1 = libcellml::Units::create();
    libcellml::UnitsPtr u2 = libcellml::Units::create();
    libcellml::UnitsPtr u3 = libcellml::Units::create();

    u1->setName("a_unit");
    u2->setName("b_unit");
    u3->setName("c_unit");

    u1->addUnit(libcellml::Units::StandardUnit::AMPERE, "micro");
    m->addUnits(u1);
    m->addUnits(u2);

    EXPECT_TRUE(m->replaceUnits("b_unit", u3));
    EXPECT_EQ(size_t(2), m->unitsCount());

    libcellml::UnitsPtr u4 = m->takeUnits(1);
    EXPECT_EQ("c_unit", u4->name());
    EXPECT_EQ(size_t(1), m->unitsCount());

    EXPECT_TRUE(m->replaceUnits(0, u4));

    u1 = m->units(0);
    EXPECT_EQ("c_unit", u1->name());
    EXPECT_EQ(size_t(1), m->unitsCount());

    // Replace non-existent units.
    EXPECT_FALSE(m->replaceUnits("d_unit", u2));
    EXPECT_FALSE(m->replaceUnits(5, u1));

    // Replace with pointers
    EXPECT_FALSE(m->replaceUnits(u2, u1));
    EXPECT_TRUE(m->replaceUnits(u1, u2));
    EXPECT_FALSE(m->replaceUnits(u1, u2));
    EXPECT_TRUE(m->replaceUnits(u2, u1));
}

TEST(Units, hasUnlinkedUnitsWhenBaseUnitsAddedToVariableButNotModel)
{
    libcellml::ModelPtr m = libcellml::Model::create();
    libcellml::ComponentPtr c1 = libcellml::Component::create();

    libcellml::UnitsPtr u1 = libcellml::Units::create();

    libcellml::VariablePtr v1 = libcellml::Variable::create();

    u1->setName("a_unit");

    v1->setUnits(u1);
    c1->addVariable(v1);
    m->addComponent(c1);

    EXPECT_TRUE(m->hasUnlinkedUnits());
}

TEST(Units, hasLinkedUnitsWhenUnitsObjectAddedToBothModelAndVariable)
{
    libcellml::ModelPtr m = libcellml::Model::create();
    libcellml::ComponentPtr c1 = libcellml::Component::create();
    libcellml::UnitsPtr u1 = libcellml::Units::create();
    libcellml::VariablePtr v1 = libcellml::Variable::create();

    u1->setName("a_unit");

    v1->setUnits(u1);

    c1->addVariable(v1);
    m->addComponent(c1);
    m->addUnits(u1);

    EXPECT_FALSE(m->hasUnlinkedUnits());
}

TEST(Units, hasUnlinkedUnitsWhenUnitsObjectsWithSameNameAddedToModelAndVariable)
{
    libcellml::ModelPtr m = libcellml::Model::create();
    libcellml::ComponentPtr c1 = libcellml::Component::create();
    libcellml::UnitsPtr u1 = libcellml::Units::create();
    libcellml::UnitsPtr u2 = libcellml::Units::create();
    libcellml::VariablePtr v1 = libcellml::Variable::create();

    u1->setName("a_unit");
    u2->setName("a_unit");

    v1->setUnits(u1);

    c1->addVariable(v1);
    m->addComponent(c1);
    m->addUnits(u2);

    EXPECT_TRUE(m->hasUnlinkedUnits());
}

TEST(Units, hasUnlinkedUnitsWhenBaseUnitsAddedToVariableByName)
{
    libcellml::ModelPtr m = libcellml::Model::create();
    libcellml::ComponentPtr c1 = libcellml::Component::create();

    libcellml::UnitsPtr u1 = libcellml::Units::create();

    libcellml::VariablePtr v1 = libcellml::Variable::create();

    u1->setName("a_unit");

    c1->addVariable(v1);
    m->addComponent(c1);

    m->addUnits(u1);
    v1->setUnits("a_unit");

    EXPECT_TRUE(m->hasUnlinkedUnits());
}

TEST(Units, hasUnlinkedUnitsWhenBaseUnitsAddedToModelAfterNameUsedForVariableUnits)
{
    libcellml::ModelPtr m = libcellml::Model::create();
    libcellml::ComponentPtr c1 = libcellml::Component::create();
    libcellml::UnitsPtr u1 = libcellml::Units::create();
    libcellml::VariablePtr v1 = libcellml::Variable::create();

    u1->setName("a_unit");

    c1->addVariable(v1);
    m->addComponent(c1);

    v1->setUnits("a_unit");
    m->addUnits(u1);

    EXPECT_TRUE(m->hasUnlinkedUnits());
}

TEST(Units, hasUnlinkedUnitsLayeredComponentsWithVariables)
{
    libcellml::ModelPtr m = libcellml::Model::create();
    libcellml::ComponentPtr c1 = libcellml::Component::create();
    libcellml::ComponentPtr c2 = libcellml::Component::create();
    libcellml::ComponentPtr c3 = libcellml::Component::create();
    libcellml::UnitsPtr u1 = libcellml::Units::create();
    libcellml::VariablePtr v1 = libcellml::Variable::create();
    libcellml::VariablePtr v2 = libcellml::Variable::create();
    libcellml::VariablePtr v3 = libcellml::Variable::create();
    libcellml::VariablePtr v4 = libcellml::Variable::create();

    u1->setName("a_unit");
    u1->addUnit("second");

    v2->setUnits(u1);
    v3->setUnits(u1);

    c1->addVariable(v1);
    c2->addVariable(v2);
    c3->addVariable(v3);
    c3->addVariable(v4);

    c2->addComponent(c3);
    c1->addComponent(c2);
    m->addComponent(c1);

    v1->setUnits("a_unit");
    m->addUnits(u1);
    v4->setUnits(u1);

    EXPECT_TRUE(m->hasUnlinkedUnits());
}

TEST(Units, hasUnlinkedUnitsSiblingComponentsWithVariables)
{
    libcellml::ModelPtr m = libcellml::Model::create();
    libcellml::ComponentPtr c1 = libcellml::Component::create();
    libcellml::ComponentPtr c2 = libcellml::Component::create();
    libcellml::ComponentPtr c3 = libcellml::Component::create();
    libcellml::UnitsPtr u1 = libcellml::Units::create();
    libcellml::VariablePtr v1 = libcellml::Variable::create();
    libcellml::VariablePtr v2 = libcellml::Variable::create();
    libcellml::VariablePtr v3 = libcellml::Variable::create();
    libcellml::VariablePtr v4 = libcellml::Variable::create();

    u1->setName("a_unit");
    u1->addUnit("second");

    c1->addVariable(v1);
    c2->addVariable(v2);
    c3->addVariable(v3);
    c3->addVariable(v4);

    c1->addComponent(c2);
    c1->addComponent(c3);
    m->addComponent(c1);

    v4->setUnits("a_unit");

    m->addUnits(u1);
    v1->setUnits("a_unit");
    v2->setUnits(u1);
    v3->setUnits(u1);

    EXPECT_TRUE(m->hasUnlinkedUnits());
}

TEST(Units, hasUnlinkedUnitsInDeepComponentHierarchy)
{
    libcellml::ModelPtr model = libcellml::Model::create();
    libcellml::ComponentPtr c1 = libcellml::Component::create();
    libcellml::ComponentPtr c2 = libcellml::Component::create();
    libcellml::ComponentPtr c3 = libcellml::Component::create();

    libcellml::UnitsPtr u = libcellml::Units::create();

    model->setName("model");
    u->setName("my_units");
    model->addUnits(u);

    c1->setName("c1");
    c2->setName("c2");
    c3->setName("c3");

    model->addComponent(c1);
    c1->addComponent(c2);
    c2->addComponent(c3);

    c3->addVariable(createVariableWithUnits("v", "my_units"));

    EXPECT_TRUE(model->hasUnlinkedUnits());

    model->linkUnits();
    EXPECT_FALSE(model->hasUnlinkedUnits());
}

TEST(Units, linkUnitsViaName)
{
    libcellml::ModelPtr m = libcellml::Model::create();
    libcellml::ComponentPtr c1 = libcellml::Component::create();
    libcellml::UnitsPtr u1 = libcellml::Units::create();
    libcellml::VariablePtr v1 = libcellml::Variable::create();

    u1->setName("a_unit");

    c1->addVariable(v1);
    m->addComponent(c1);

    v1->setUnits("a_unit");
    m->addUnits(u1);

    m->linkUnits();
    EXPECT_FALSE(m->hasUnlinkedUnits());
}

TEST(Units, linkUnitsViaUnitsObject)
{
    libcellml::ModelPtr m = libcellml::Model::create();
    libcellml::ComponentPtr c1 = libcellml::Component::create();
    libcellml::UnitsPtr u1 = libcellml::Units::create();
    libcellml::UnitsPtr u2 = libcellml::Units::create();
    libcellml::VariablePtr v1 = libcellml::Variable::create();

    u1->setName("a_unit");
    u2->setName("a_unit");

    v1->setUnits(u1);

    c1->addVariable(v1);
    m->addComponent(c1);
    m->addUnits(u2);

    m->linkUnits();
    EXPECT_FALSE(m->hasUnlinkedUnits());
}

TEST(Units, cannotLinkUnitsNotAddedToModel)
{
    libcellml::ModelPtr m = libcellml::Model::create();
    libcellml::ComponentPtr c1 = libcellml::Component::create();
    libcellml::UnitsPtr u1 = libcellml::Units::create();
    libcellml::VariablePtr v1 = libcellml::Variable::create();

    u1->setName("a_unit");

    c1->addVariable(v1);
    m->addComponent(c1);

    v1->setUnits(u1);

    m->linkUnits();
    EXPECT_TRUE(m->hasUnlinkedUnits());
}

TEST(Units, multiply)
{
    const std::string e =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/2.0#\">\n"
        "  <units name=\"compound_unit\">\n"
        "    <unit prefix=\"micro\" units=\"ampere\"/>\n"
        "    <unit units=\"kelvin\"/>\n"
        "    <unit exponent=\"-1\" prefix=\"milli\" units=\"siemens\"/>\n"
        "  </units>\n"
        "  <units name=\"valid_name\"/>\n"
        "  <units name=\"multiplied\">\n"
        "    <unit units=\"compound_unit\"/>\n"
        "    <unit units=\"valid_name\"/>\n"
        "  </units>\n"
        "</model>\n";

    libcellml::ModelPtr m = libcellml::Model::create();

    libcellml::UnitsPtr u1 = libcellml::Units::create();
    u1->setName("compound_unit");

    u1->addUnit(libcellml::Units::StandardUnit::AMPERE, libcellml::Units::Prefix::MICRO);
    u1->addUnit(libcellml::Units::StandardUnit::KELVIN);
    u1->addUnit(libcellml::Units::StandardUnit::SIEMENS, libcellml::Units::Prefix::MILLI, -1.0);

    m->addUnits(u1);

    libcellml::UnitsPtr u2 = libcellml::Units::create();
    u2->setName("valid_name");

    m->addUnits(u2);

    libcellml::UnitsPtr u3 = libcellml::Units::create();
    u3->setName("multiplied");
    u3->addUnit("compound_unit");
    u3->addUnit("valid_name");

    m->addUnits(u3);

    libcellml::PrinterPtr printer = libcellml::Printer::create();
    const std::string a = printer->printModel(m);
    EXPECT_EQ(e, a);
}

TEST(Units, newBaseUnit)
{
    const std::string e =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/2.0#\">\n"
        "  <units name=\"pH\"/>\n"
        "</model>\n";

    libcellml::ModelPtr m = libcellml::Model::create();

    libcellml::UnitsPtr u = libcellml::Units::create();
    u->setName("pH");

    m->addUnits(u);

    libcellml::PrinterPtr printer = libcellml::Printer::create();
    const std::string a = printer->printModel(m);
    EXPECT_EQ(e, a);
    EXPECT_EQ("pH", u->name());
}

TEST(Units, isBaseUnit)
{
    libcellml::UnitsPtr u = libcellml::Units::create();
    u->setName("pH");

    EXPECT_TRUE(u->isBaseUnit());

    u->addUnit("Candela");

    EXPECT_FALSE(u->isBaseUnit());
}

TEST(Units, farhenheit)
{
    const std::string e =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/2.0#\">\n"
        "  <units name=\"fahrenheitish\">\n"
        "    <unit multiplier=\"1.8\" units=\"kelvin\"/>\n"
        "  </units>\n"
        "</model>\n";

    libcellml::ModelPtr m = libcellml::Model::create();

    libcellml::UnitsPtr u = libcellml::Units::create();
    u->setName("fahrenheitish");

    /* Give prefix and exponent their default values. */
    u->addUnit("kelvin", 0, 1.0, 1.8);
    m->addUnits(u);

    libcellml::PrinterPtr printer = libcellml::Printer::create();
    const std::string a = printer->printModel(m);
    EXPECT_EQ(e, a);
    EXPECT_EQ("fahrenheitish", u->name());
}

TEST(Units, unitAttributes)
{
    libcellml::ModelPtr m = libcellml::Model::create();

    libcellml::UnitsPtr u = libcellml::Units::create();
    u->setName("fahrenheitish");

    /* Give prefix and exponent their default values. */
    u->addUnit("kelvin", 0, 1.0, 1.8);
    m->addUnits(u);

    std::string reference;
    std::string prefix;
    std::string id;
    double exponent;
    double multiplier;
    u->unitAttributes(0, reference, prefix, exponent, multiplier, id);
    EXPECT_EQ("kelvin", reference);
    EXPECT_EQ("", prefix);
    EXPECT_DOUBLE_EQ(1.0, exponent);
    EXPECT_DOUBLE_EQ(1.8, multiplier);

    u->addUnit("NewUnit", 4, 1.05, 17.0);
    u->unitAttributes(1, reference, prefix, exponent, multiplier, id);
    EXPECT_EQ("NewUnit", reference);
    EXPECT_EQ("4", prefix);
    EXPECT_DOUBLE_EQ(1.05, exponent);
    EXPECT_DOUBLE_EQ(17, multiplier);

    // Get non-existent unit.
    u->unitAttributes(2, reference, prefix, exponent, multiplier, id);
    EXPECT_EQ("", reference);
    EXPECT_EQ("", prefix);
    EXPECT_DOUBLE_EQ(1, exponent);
    EXPECT_DOUBLE_EQ(1, multiplier);

    u->addUnit("daves", "house");
    u->unitAttributes(2, reference, prefix, exponent, multiplier, id);
    EXPECT_EQ("daves", reference);
    EXPECT_EQ("house", prefix);

    u->unitAttributes("daves", prefix, exponent, multiplier, id);
    EXPECT_EQ("daves", reference);
    EXPECT_EQ("house", prefix);

    u->unitAttributes("kelvin", prefix, exponent, multiplier, id);
    EXPECT_EQ("", prefix);
    EXPECT_DOUBLE_EQ(1.0, exponent);
    EXPECT_DOUBLE_EQ(1.8, multiplier);
}

TEST(Units, multipleUnitUsingStandardRef)
{
    auto u = libcellml::Units::create();

    u->addUnit(libcellml::Units::StandardUnit::AMPERE, "micro");
    u->addUnit(libcellml::Units::StandardUnit::AMPERE, "milli");
    u->addUnit(libcellml::Units::StandardUnit::AMPERE, libcellml::Units::Prefix::CENTI);
    u->addUnit(libcellml::Units::StandardUnit::AMPERE, libcellml::Units::Prefix::MICRO);

    EXPECT_EQ(size_t(4), u->unitCount());

    u->removeUnit(libcellml::Units::StandardUnit::AMPERE);

    EXPECT_EQ(size_t(3), u->unitCount());

    std::string prefix;
    std::string reference;
    std::string id;
    double exponent;
    double multiplier;
    u->unitAttributes(libcellml::Units::StandardUnit::AMPERE, prefix, exponent, multiplier, id);
    EXPECT_EQ("milli", prefix);
    u->unitAttributes(0, reference, prefix, exponent, multiplier, id);
    EXPECT_EQ("milli", prefix);
    u->unitAttributes(1, reference, prefix, exponent, multiplier, id);
    EXPECT_EQ("centi", prefix);
    u->unitAttributes(2, reference, prefix, exponent, multiplier, id);
    EXPECT_EQ("micro", prefix);
}

TEST(Units, removeUnit)
{
    libcellml::UnitsPtr u = libcellml::Units::create();

    u->addUnit(libcellml::Units::StandardUnit::AMPERE, "micro");
    u->addUnit("kelvin");
    u->addUnit("siemens", "milli", -1.0);
    u->addUnit("metre", "1.7e10");

    EXPECT_EQ(size_t(4), u->unitCount());
    EXPECT_TRUE(u->removeUnit("siemens"));
    EXPECT_TRUE(u->removeUnit(libcellml::Units::StandardUnit::KELVIN));
    EXPECT_TRUE(u->removeUnit(1));
    EXPECT_EQ(size_t(1), u->unitCount());

    // Remove non-existent unit
    EXPECT_FALSE(u->removeUnit("gram"));
    EXPECT_FALSE(u->removeUnit(libcellml::Units::StandardUnit::BECQUEREL));
    EXPECT_FALSE(u->removeUnit(3));
    EXPECT_EQ(size_t(1), u->unitCount());

    u->removeAllUnits();
    EXPECT_EQ(size_t(0), u->unitCount());
}

TEST(Units, multipleAndParse)
{
    const std::string e =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/2.0#\">\n"
        "  <units name=\"fahrenheitish\">\n"
        "    <unit multiplier=\"1.8\" units=\"kelvin\"/>\n"
        "  </units>\n"
        "  <units name=\"metres_per_second\">\n"
        "    <unit units=\"metre\"/>\n"
        "    <unit exponent=\"-1\" units=\"second\"/>\n"
        "  </units>\n"
        "</model>\n";

    libcellml::ModelPtr m = libcellml::Model::create();

    libcellml::UnitsPtr u1 = libcellml::Units::create();
    u1->setName("fahrenheitish");

    /* Give prefix and exponent their default values. */
    u1->addUnit("kelvin", 0, 1.0, 1.8);

    libcellml::UnitsPtr u2 = libcellml::Units::create();
    u2->setName("metres_per_second");
    u2->addUnit(libcellml::Units::StandardUnit::METRE);
    u2->addUnit(libcellml::Units::StandardUnit::SECOND, -1.0);

    m->addUnits(u1);
    m->addUnits(u2);

    libcellml::PrinterPtr printer = libcellml::Printer::create();
    std::string a = printer->printModel(m);
    EXPECT_EQ(e, a);

    // Parse
    libcellml::ParserPtr parser = libcellml::Parser::create();
    libcellml::ModelPtr model = parser->parseModel(e);
    a = printer->printModel(model);
    EXPECT_EQ(e, a);
}

TEST(Units, unitsWithPrefixOutOfRange)
{
    // int limit is 18,446,744,073,709,551,615

    const std::string e = "Prefix '18446744073709551616' of a unit referencing 'second' in units 'myUnits' is out of the integer range.";

    libcellml::ValidatorPtr validator = libcellml::Validator::create();
    libcellml::ModelPtr m = libcellml::Model::create();
    m->setName("myModel");
    libcellml::ComponentPtr c = libcellml::Component::create();
    c->setName("myComponent");
    libcellml::VariablePtr v = libcellml::Variable::create();
    v->setName("myVariable");
    libcellml::UnitsPtr u = libcellml::Units::create();

    u->setName("myUnits");
    u->addUnit("second", "18446744073709551616");
    v->setUnits(u);
    c->addVariable(v);
    m->addComponent(c);
    m->addUnits(u);

    EXPECT_FALSE(m->hasUnlinkedUnits());

    validator->validateModel(m);

    EXPECT_EQ(size_t(1), validator->errorCount());
    EXPECT_EQ(e, validator->error(0)->description());
}

TEST(Units, parentOfUnits)
{
    libcellml::ModelPtr model = libcellml::Model::create();
    model->setName("I_am_a_model");

    libcellml::UnitsPtr u = libcellml::Units::create();
    u->setName("u");

    model->addUnits(u);

    libcellml::ModelPtr parent = std::dynamic_pointer_cast<libcellml::Model>(u->parent());
    EXPECT_FALSE(parent == nullptr);
    EXPECT_EQ(model, parent);
}

TEST(Units, parentlessUsingRemoveUnits)
{
    libcellml::ModelPtr model = libcellml::Model::create();
    model->setName("I_am_a_model");

    libcellml::UnitsPtr u = libcellml::Units::create();
    u->setName("u");

    model->addUnits(u);
    EXPECT_TRUE(u->hasParent());

    model->removeUnits(0);
    EXPECT_FALSE(u->hasParent());

    model->addUnits(u);
    EXPECT_TRUE(u->hasParent());

    model->removeUnits("u");
    EXPECT_FALSE(u->hasParent());

    model->addUnits(u);
    EXPECT_TRUE(u->hasParent());

    model->removeUnits(u);
    EXPECT_FALSE(u->hasParent());
}

TEST(Units, compareEqualMultiplierSimple)
{
    // u1 = 1000*u2
    libcellml::UnitsPtr u1 = libcellml::Units::create();
    u1->setName("u1");
    u1->addUnit("metre", 0, 1.0, 113.0);
    libcellml::UnitsPtr u2 = libcellml::Units::create();
    u2->setName("u2");
    u2->addUnit("metre", 0, 1.0, 113.0);

    EXPECT_EQ(1.0, libcellml::Units::scalingFactor(u1, u2));
}

TEST(Units, compareMultiplierSimple)
{
    // u1 = 1000*u2
    libcellml::UnitsPtr u1 = libcellml::Units::create();
    u1->setName("u1");
    u1->addUnit("metre", 0, 1.0, 1000.0);
    libcellml::UnitsPtr u2 = libcellml::Units::create();
    u2->setName("u2");
    u2->addUnit("metre", 0, 1.0, 1.0);

    EXPECT_EQ(0.001, libcellml::Units::scalingFactor(u1, u2)); // 10^-3.0 factor difference
    EXPECT_EQ(1000.0, libcellml::Units::scalingFactor(u2, u1)); // 10^3.0 factor difference
}

TEST(Units, compareMultiplierStandardUnit)
{
    // u1 = 1000*u2
    libcellml::UnitsPtr u1 = libcellml::Units::create();
    u1->setName("u1");
    u1->addUnit(libcellml::Units::StandardUnit::BECQUEREL, 0, 1.0, 500.0);
    libcellml::UnitsPtr u2 = libcellml::Units::create();
    u2->setName("u2");
    u2->addUnit(libcellml::Units::StandardUnit::BECQUEREL, 0, 1.0, 1.0);

    EXPECT_NEAR(0.002, libcellml::Units::scalingFactor(u1, u2), 1e-12);
    EXPECT_NEAR(500.0, libcellml::Units::scalingFactor(u2, u1), 1e-12);
}

TEST(Units, compareSameBaseUnits)
{
    libcellml::UnitsPtr u1 = libcellml::Units::create();
    u1->setName("frufru");
    libcellml::UnitsPtr u2 = libcellml::Units::create();
    u2->setName("frufru");

    EXPECT_EQ(1.0, libcellml::Units::scalingFactor(u1, u2));
}

TEST(Units, compareBaseUnitsAgainstItself)
{
    libcellml::UnitsPtr u1 = libcellml::Units::create();
    u1->setName("frufru");

    EXPECT_EQ(1.0, libcellml::Units::scalingFactor(u1, u1));
}

TEST(Units, compareBaseUnitsWithCapitalisation)
{
    libcellml::UnitsPtr u1 = libcellml::Units::create();
    u1->setName("frufru");
    libcellml::UnitsPtr u2 = libcellml::Units::create();
    u2->setName("Frufru");

    EXPECT_EQ(0.0, libcellml::Units::scalingFactor(u1, u2));
}

TEST(Units, compareScalingFactorWithNullptrAsFirstParameter)
{
    libcellml::UnitsPtr u = libcellml::Units::create();
    u->setName("u");
    u->addUnit(libcellml::Units::StandardUnit::LUX, 0, 1.0, 1.0);

    EXPECT_EQ(0.0, libcellml::Units::scalingFactor(nullptr, u));
}

TEST(Units, compareScalingFactorWithNullptrAsSecondParameter)
{
    libcellml::UnitsPtr u = libcellml::Units::create();
    u->setName("u");
    u->addUnit(libcellml::Units::StandardUnit::LUX, 0, 1.0, 1.0);

    EXPECT_EQ(0.0, libcellml::Units::scalingFactor(u, nullptr));
}

TEST(Units, compareScalingFactorWithNullptrAsBothParameters)
{
    EXPECT_EQ(0.0, libcellml::Units::scalingFactor(nullptr, nullptr));
}

TEST(Units, compareScalingFactorWithUnitBasedOnUnknownUnit)
{
    libcellml::UnitsPtr u1 = libcellml::Units::create();
    u1->setName("u1");
    u1->addUnit("apple", 0, 1.0, 1.0);

    libcellml::UnitsPtr u2 = libcellml::Units::create();
    u2->setName("u2");
    u2->addUnit(libcellml::Units::StandardUnit::LUX, 0, 1.0, 1.0);

    EXPECT_EQ(0.0, libcellml::Units::scalingFactor(u1, u2));
    EXPECT_EQ(0.0, libcellml::Units::scalingFactor(u2, u1));
}

TEST(Units, compareScalingFactorWithTwoUnitsBasedOnUnknownUnits)
{
    libcellml::UnitsPtr u1 = libcellml::Units::create();
    u1->setName("u1");
    u1->addUnit("apple", 0, 1.0, 1.0);

    libcellml::UnitsPtr u2 = libcellml::Units::create();
    u2->setName("u2");
    u2->addUnit("banana", 0, 1.0, 1.0);

    EXPECT_EQ(0.0, libcellml::Units::scalingFactor(u1, u2));
}

TEST(Units, scalingFactorWithOneEmptyUnit)
{
    // Add unit with no members
    libcellml::UnitsPtr u1 = libcellml::Units::create();
    u1->setName("u1");

    libcellml::UnitsPtr u2 = libcellml::Units::create();
    u2->setName("u2");
    u2->addUnit(libcellml::Units::StandardUnit::LITRE, 0, 1.0, 1.0);

    EXPECT_EQ(0.0, libcellml::Units::scalingFactor(u1, u2));
    EXPECT_EQ(0.0, libcellml::Units::scalingFactor(u2, u1));
}

TEST(Units, scalingFactorWithTwoEmptyUnits)
{
    libcellml::UnitsPtr u1 = libcellml::Units::create();
    u1->setName("u1");

    libcellml::UnitsPtr u2 = libcellml::Units::create();
    u2->setName("u2");

    EXPECT_EQ(0.0, libcellml::Units::scalingFactor(u2, u1));
}

TEST(Units, scalingFactorBetweenDissimilarUnits)
{
    libcellml::UnitsPtr u1 = libcellml::Units::create();
    u1->setName("u1");
    u1->addUnit("metre", 0, 1.0, 1000.0);
    libcellml::UnitsPtr u2 = libcellml::Units::create();
    u2->setName("u2");
    u2->addUnit("metre", 0, 1.0, 1.0);
    u2->addUnit("metre", 0, 1.0, 1.0);
    u2->addUnit("metre", 0, 1.0, 1.0);

    EXPECT_EQ(0.0, libcellml::Units::scalingFactor(u2, u1));
}

TEST(Units, compareIncompatibleMultiplierSimple)
{
    libcellml::UnitsPtr u1 = libcellml::Units::create();
    u1->setName("u1");
    u1->addUnit("metre", 0, 1.0, 1.0);
    libcellml::UnitsPtr u2 = libcellml::Units::create();
    u2->setName("u2");
    u2->addUnit("second", 0, 1.0, 1.0);

    // Incompatible units return a scaling factor of 0.0.
    EXPECT_EQ(0.0, libcellml::Units::scalingFactor(u1, u2));
    EXPECT_EQ(0.0, libcellml::Units::scalingFactor(u2, u1));
}

TEST(Units, dimensionlessScalingFactor)
{
    auto m = libcellml::Model::create("model");
    auto u = libcellml::Units::create("u");

    auto u1 = libcellml::Units::create("u1");
    u1->addUnit("u", "milli", 2.0, 1000.0);
    u1->addUnit("dimensionless");
    auto u2 = libcellml::Units::create("u2");
    u2->addUnit("u", "kilo", 2.0, 0.001);
    u2->addUnit("dimensionless");

    auto u3 = libcellml::Units::create("u3");
    u3->addUnit("u", "milli", 2.0, 1000.0);
    auto u4 = libcellml::Units::create("u4");
    u4->addUnit("u", "kilo", 2.0, 0.001);

    auto u5 = libcellml::Units::create("u5");
    u5->addUnit("u", "milli", 2.0, 1000.0);
    u5->addUnit("dimensionless", 2.0);
    auto u6 = libcellml::Units::create("u6");
    u6->addUnit("u", "kilo", 2.0, 0.001);
    u6->addUnit("dimensionless", 2.0);

    m->addUnits(u);
    m->addUnits(u1);
    m->addUnits(u2);
    m->addUnits(u3);
    m->addUnits(u4);
    m->addUnits(u5);
    m->addUnits(u6);

    EXPECT_EQ(1.0, libcellml::Units::scalingFactor(u1, u2));
    EXPECT_EQ(1.0, libcellml::Units::scalingFactor(u2, u1));
    EXPECT_EQ(1.0, libcellml::Units::scalingFactor(u3, u4));
    EXPECT_EQ(1.0, libcellml::Units::scalingFactor(u4, u3));
    EXPECT_EQ(1.0, libcellml::Units::scalingFactor(u1, u3));
    EXPECT_EQ(1.0, libcellml::Units::scalingFactor(u2, u4));
    EXPECT_EQ(1.0, libcellml::Units::scalingFactor(u1, u4));
    EXPECT_EQ(1.0, libcellml::Units::scalingFactor(u2, u3));
    EXPECT_EQ(1.0, libcellml::Units::scalingFactor(u5, u6));
    EXPECT_EQ(1.0, libcellml::Units::scalingFactor(u6, u5));
    EXPECT_EQ(1.0, libcellml::Units::scalingFactor(u1, u5));
}

TEST(Units, customUnitsScalingFactorSimple)
{
    auto m = libcellml::Model::create("model");
    auto u1 = libcellml::Units::create("u1");
    m->addUnits(u1);
    auto u2 = libcellml::Units::create("u2");
    u2->addUnit("u1");
    m->addUnits(u2);

    m->linkUnits();

    EXPECT_TRUE(libcellml::Units::compatible(u1, u2));
    EXPECT_EQ(1.0, libcellml::Units::scalingFactor(u1, u2));
    EXPECT_TRUE(libcellml::Units::equivalent(u1, u2));
}

TEST(Units, customUnitsScalingFactorIncludingDimensionless)
{
    auto m = libcellml::Model::create("model");
    auto u1 = libcellml::Units::create("u1");

    m->addUnits(u1);

    auto u2 = libcellml::Units::create("u2");
    u2->addUnit("u1");
    u2->addUnit("dimensionless");
    u2->addUnit("radian");
    u2->addUnit("steradian");
    u2->addUnit("metre", 1.0);
    u2->addUnit("metre", -1.0);

    m->addUnits(u2);

    m->linkUnits();

    EXPECT_TRUE(libcellml::Units::compatible(u1, u2));
    EXPECT_EQ(1.0, libcellml::Units::scalingFactor(u1, u2));
    EXPECT_TRUE(libcellml::Units::equivalent(u1, u2));
}

TEST(Units, complicatedMultiplicationFactorUnits)
{
    libcellml::ModelPtr model = libcellml::Model::create();

    libcellml::UnitsPtr u = libcellml::Units::create();
    u->setName("u");

    libcellml::UnitsPtr u1 = libcellml::Units::create("u1");
    u1->addUnit("u", "milli", 2.0, 1000.0); // u1 = u^2
    u1->addUnit("dimensionless");

    libcellml::UnitsPtr u2 = libcellml::Units::create("u2");
    u2->addUnit("u", "kilo", 2.0, 0.001); // u2 = u^2
    u2->addUnit("dimensionless");

    libcellml::UnitsPtr u3 = libcellml::Units::create("u3");
    u3->addUnit("u", "kilo", 4.0, 0.001); // u3 = u^4

    libcellml::UnitsPtr u4 = libcellml::Units::create("u4");
    u4->addUnit("u2", 2.0); // u4 = u^4

    libcellml::UnitsPtr apple = libcellml::Units::create("apple");
    libcellml::UnitsPtr banana = libcellml::Units::create("banana");

    libcellml::UnitsPtr bushell_of_apples = libcellml::Units::create("bushell_of_apples");
    bushell_of_apples->addUnit("apple", "mega", 1.0, 1000.0); // 1000*mega*apple^1

    libcellml::UnitsPtr square_apple = libcellml::Units::create("square_apple");
    square_apple->addUnit("apple", 2.0);

    libcellml::UnitsPtr incredible_pile_of_square_apples = libcellml::Units::create("incredible_pile_of_square_apples");
    incredible_pile_of_square_apples->addUnit("square_apple", "mega", 1.0, 100.0);

    libcellml::UnitsPtr bunch_of_bananas = libcellml::Units::create("bunch_of_bananas");
    bunch_of_bananas->addUnit("banana", 1, 1.0, 1.0); // 10 bananas

    model->setName("model");
    model->addUnits(u);
    model->addUnits(u1);
    model->addUnits(u2);
    model->addUnits(u3);
    model->addUnits(u4);
    model->addUnits(bushell_of_apples);
    model->addUnits(apple);
    model->addUnits(banana);
    model->addUnits(square_apple);
    model->addUnits(incredible_pile_of_square_apples);
    model->addUnits(bunch_of_bananas);

    EXPECT_EQ(1.0, libcellml::Units::scalingFactor(u1, u2));
    EXPECT_EQ(1.0, libcellml::Units::scalingFactor(u3, u4));
    EXPECT_EQ(1e-08, libcellml::Units::scalingFactor(incredible_pile_of_square_apples, square_apple));
    // Incompatible units so we return a scaling factor of 0.0.
    EXPECT_EQ(0.0, libcellml::Units::scalingFactor(incredible_pile_of_square_apples, bunch_of_bananas));
}

TEST(Units, checkingOwningModelBothUnits)
{
    libcellml::ModelPtr model = libcellml::Model::create();

    libcellml::UnitsPtr u1 = libcellml::Units::create();
    u1->setName("u1");
    u1->addUnit("u", "milli", 2.0, 1000.0); //m^2
    u1->addUnit("dimensionless");

    libcellml::UnitsPtr u2 = libcellml::Units::create();
    u2->setName("u2");
    u2->addUnit("u", "kilo", 2.0, 0.001); // standard, exponent.
    u2->addUnit("dimensionless");

    model->addUnits(u1);
    model->addUnits(u2);

    EXPECT_EQ(0.0, libcellml::Units::scalingFactor(u1, u2));
    EXPECT_EQ(0.0, libcellml::Units::scalingFactor(u2, u1));
}

TEST(Units, checkingOwningModelWithUnitBaseOnlyInModel)
{
    libcellml::ModelPtr model = libcellml::Model::create();

    libcellml::UnitsPtr u = libcellml::Units::create();
    u->setName("apple");

    libcellml::UnitsPtr u1 = libcellml::Units::create();
    u1->setName("u1");
    u1->addUnit("apple", "kilo", 2.0, 0.001); // standard, exponent.
    u1->addUnit("dimensionless");

    libcellml::UnitsPtr u2 = libcellml::Units::create();
    u2->setName("u2");
    u2->addUnit("apple", "kilo", 4.0, 0.001); // standard, exponent.

    model->addUnits(u);
    model->addUnits(u1);

    EXPECT_EQ(0.0, libcellml::Units::scalingFactor(u1, u2));
    EXPECT_EQ(0.0, libcellml::Units::scalingFactor(u2, u1));
}

TEST(Units, checkingOwningModelOneUnit)
{
    libcellml::ModelPtr model = libcellml::Model::create();

    libcellml::UnitsPtr u = libcellml::Units::create();
    u->setName("u");

    libcellml::UnitsPtr u1 = libcellml::Units::create();
    u1->setName("u1");
    u1->addUnit("u", "milli", 1.0, 1.0); // u1 is a parent of u

    libcellml::UnitsPtr u2 = libcellml::Units::create();
    u2->setName("u2");
    u2->addUnit("apples", "kilo", 2.0, 1000.0); // apples not in model

    model->addUnits(u);
    model->addUnits(u1);
    model->addUnits(u2);

    EXPECT_EQ(0.0, libcellml::Units::scalingFactor(u1, u2));
    EXPECT_EQ(0.0, libcellml::Units::scalingFactor(u2, u1));
}

TEST(Units, checkScalingFactorImportedModel)
{
    libcellml::UnitsPtr u1 = libcellml::Units::create();
    u1->setName("u1");
    u1->addUnit(libcellml::Units::StandardUnit::RADIAN, 0, 1.0, 1.0);

    libcellml::UnitsPtr u2 = libcellml::Units::create();
    u2->setName("u2");
    u2->addUnit(libcellml::Units::StandardUnit::RADIAN, 0, 1.0, 1.0);

    libcellml::ModelPtr model = libcellml::Model::create();
    model->setName("model");
    model->addUnits(u1);

    libcellml::ImportSourcePtr import = libcellml::ImportSource::create();
    import->setUrl("I_am_a_url");
    import->setModel(model);

    model->addUnits(u1);
    model->addUnits(u2);

    EXPECT_EQ(1.0, libcellml::Units::scalingFactor(u1, u2));
    EXPECT_EQ(1.0, libcellml::Units::scalingFactor(u2, u1));
}

TEST(Units, checkScalingFactorOneUnitImported)
{
    libcellml::UnitsPtr u1 = libcellml::Units::create();
    u1->setName("u1");
    u1->addUnit(libcellml::Units::StandardUnit::RADIAN, 0, 1.0, 1.0);

    libcellml::UnitsPtr u2 = libcellml::Units::create();
    u2->setName("u2");
    u2->addUnit(libcellml::Units::StandardUnit::RADIAN, 0, 1.0, 1.0);

    libcellml::ImportSourcePtr import = libcellml::ImportSource::create();
    import->setUrl("I_am_a_url");

    u1->setImportSource(import);

    // Scaling factor returns 0.0 because of imported units.
    EXPECT_EQ(0.0, libcellml::Units::scalingFactor(u1, u2));
    EXPECT_EQ(0.0, libcellml::Units::scalingFactor(u2, u1));
}

TEST(Units, checkScalingFactorOneNonBaseUnitImported)
{
    libcellml::ModelPtr model = libcellml::Model::create();
    model->setName("model");

    libcellml::UnitsPtr u = libcellml::Units::create();
    u->setName("u");
    u->addUnit("apples", 0, 1.0, 1.0);

    libcellml::UnitsPtr u1 = libcellml::Units::create();
    u1->setName("u1");
    u1->addUnit(libcellml::Units::StandardUnit::RADIAN, 0, 1.0, 1.0);

    libcellml::UnitsPtr u2 = libcellml::Units::create();
    u2->setName("u2");
    u2->addUnit(libcellml::Units::StandardUnit::RADIAN, 0, 1.0, 1.0);
    u2->addUnit("u", 0, 1.0, 1.0);

    model->addUnits(u);
    model->addUnits(u1);
    model->addUnits(u2);

    libcellml::ImportSourcePtr import = libcellml::ImportSource::create();
    import->setUrl("I_am_a_url");

    u->setImportSource(import);

    EXPECT_TRUE(u->isImport());
    EXPECT_EQ(0.0, libcellml::Units::scalingFactor(u1, u2));
    EXPECT_EQ(0.0, libcellml::Units::scalingFactor(u2, u1));
}

TEST(Units, checkScalingFactorBothNonBaseUnitsImported)
{
    libcellml::ModelPtr model = libcellml::Model::create();
    model->setName("model");

    libcellml::UnitsPtr u = libcellml::Units::create();
    u->setName("u");
    u->addUnit("apples", 0, 1.0, 1.0);

    libcellml::UnitsPtr u1 = libcellml::Units::create();
    u1->setName("u1");
    u1->addUnit(libcellml::Units::StandardUnit::AMPERE, 0, 1.0, 1.0);
    u1->addUnit("u", 0, 1.0, 1.0);

    libcellml::UnitsPtr u2 = libcellml::Units::create();
    u2->setName("u2");
    u2->addUnit(libcellml::Units::StandardUnit::RADIAN, 0, 1.0, 1.0);
    u2->addUnit("u", 0, 1.0, 1.0);

    model->addUnits(u);
    model->addUnits(u1);
    model->addUnits(u2);

    libcellml::ImportSourcePtr import = libcellml::ImportSource::create();
    import->setUrl("I_am_a_url");

    u->setImportSource(import);

    EXPECT_TRUE(u->isImport());
    EXPECT_EQ(0.0, libcellml::Units::scalingFactor(u1, u2));
    EXPECT_EQ(0.0, libcellml::Units::scalingFactor(u2, u1));
}

TEST(Units, compareEquivalentUnits)
{
    libcellml::UnitsPtr u1 = libcellml::Units::create();
    u1->setName("u1");
    u1->addUnit(libcellml::Units::StandardUnit::LUX, 0, 1.0, 1.0);

    libcellml::UnitsPtr u2 = libcellml::Units::create();
    u2->setName("u2");
    u2->addUnit(libcellml::Units::StandardUnit::LUX, 0, 1.0, 1.0);

    EXPECT_TRUE(libcellml::Units::equivalent(u1, u2));
}

TEST(Units, compareDimensionallyNonEquivalentUnitsWhichHaveSameBase)
{
    libcellml::UnitsPtr u1 = libcellml::Units::create();
    u1->setName("u1");
    u1->addUnit(libcellml::Units::StandardUnit::LUX, "milli");

    libcellml::UnitsPtr u2 = libcellml::Units::create();
    u2->setName("u2");
    u2->addUnit(libcellml::Units::StandardUnit::LUX, 0, 1.0, 1.0);

    EXPECT_FALSE(libcellml::Units::equivalent(u1, u2));
    EXPECT_FALSE(libcellml::Units::equivalent(u2, u1));
}

TEST(Units, compareEquivalentUnitsWhichHaveNonStandardBase)
{
    libcellml::ModelPtr model = libcellml::Model::create();
    model->setName("model");

    libcellml::UnitsPtr u = libcellml::Units::create();
    u->setName("u");

    libcellml::UnitsPtr u1 = libcellml::Units::create();
    u1->setName("u1");
    u1->addUnit("u");

    libcellml::UnitsPtr u2 = libcellml::Units::create();
    u2->setName("u2");
    u2->addUnit("u");

    model->addUnits(u);
    model->addUnits(u1);
    model->addUnits(u2);

    EXPECT_TRUE(libcellml::Units::equivalent(u1, u2));
    EXPECT_TRUE(libcellml::Units::equivalent(u2, u1));
}

TEST(Units, compareNonEquivalentUnitsWhichHaveDifferentBase)
{
    libcellml::UnitsPtr u1 = libcellml::Units::create();
    u1->setName("u1");
    u1->addUnit(libcellml::Units::StandardUnit::BECQUEREL, 0, 1.0, 1.0);

    libcellml::UnitsPtr u2 = libcellml::Units::create();
    u2->setName("u2");
    u2->addUnit(libcellml::Units::StandardUnit::LUX, 0, 1.0, 1.0);

    EXPECT_FALSE(libcellml::Units::equivalent(u1, u2));
}

TEST(Units, compareEquivalentUnitsComplex)
{
    libcellml::UnitsPtr u = libcellml::Units::create();
    u->setName("u");
    u->addUnit(libcellml::Units::StandardUnit::CANDELA, "micro", 2.0, 3.0);

    libcellml::UnitsPtr u1 = libcellml::Units::create();
    u1->setName("u1");
    u1->addUnit("metre", "milli", 2.0, 1.0);
    u1->addUnit(libcellml::Units::StandardUnit::AMPERE, 0, 1.0, 1.0);
    u1->addUnit("u");

    libcellml::UnitsPtr u2 = libcellml::Units::create();
    u2->setName("u2");
    u2->addUnit(libcellml::Units::StandardUnit::AMPERE, 0, 1.0, 1.0);
    u2->addUnit("u");
    u2->addUnit("metre", "milli", 2.0, 1.0); // Ordering shouldn't matter

    libcellml::ModelPtr model = libcellml::Model::create();
    model->setName("model");
    model->addUnits(u);
    model->addUnits(u1);
    model->addUnits(u2);

    EXPECT_TRUE(libcellml::Units::equivalent(u1, u2));
    EXPECT_TRUE(libcellml::Units::equivalent(u2, u1));
}

TEST(Units, compareIncomparableEquivalentUnitsComplex)
{
    libcellml::UnitsPtr u = libcellml::Units::create();
    u->setName("u");
    u->addUnit(libcellml::Units::StandardUnit::CANDELA, "micro", 2.0, 3.0);

    libcellml::UnitsPtr u1 = libcellml::Units::create();
    u1->setName("u1");
    u1->addUnit("metre", "milli", 2.0, 1.0);
    u1->addUnit(libcellml::Units::StandardUnit::AMPERE, 0, 1.0, 1.0);
    u1->addUnit("u");

    libcellml::UnitsPtr u2 = libcellml::Units::create();
    u2->setName("u2");
    u2->addUnit(libcellml::Units::StandardUnit::AMPERE, 0, 1.0, 1.0);
    u2->addUnit("metre", "milli", 2.0, 1.0);

    libcellml::ModelPtr model = libcellml::Model::create();
    model->setName("model");
    model->addUnits(u);
    model->addUnits(u1);
    model->addUnits(u2);

    EXPECT_FALSE(libcellml::Units::equivalent(u1, u2));
    EXPECT_FALSE(libcellml::Units::equivalent(u2, u1));
}

TEST(Units, compareBaseIncomparableUnitsWithInputAsNullptr)
{
    libcellml::UnitsPtr u = libcellml::Units::create();
    u->setName("u");
    u->addUnit(libcellml::Units::StandardUnit::LUX, "milli");

    EXPECT_FALSE(libcellml::Units::compatible(u, nullptr));
    EXPECT_FALSE(libcellml::Units::compatible(nullptr, u));
}

TEST(Units, compareBaseIncomparableUnitsWithBothInputsAsNullptr)
{
    EXPECT_FALSE(libcellml::Units::compatible(nullptr, nullptr));
}

TEST(Units, compareCompatibleUnits)
{
    libcellml::UnitsPtr u1 = libcellml::Units::create();
    u1->setName("u1");
    u1->addUnit(libcellml::Units::StandardUnit::LUX, "milli");

    libcellml::UnitsPtr u2 = libcellml::Units::create();
    u2->setName("u2");
    u2->addUnit(libcellml::Units::StandardUnit::LUX, 0, 1.0, 1.0);

    EXPECT_TRUE(libcellml::Units::compatible(u1, u2));
}

TEST(Units, compareEquivalentNonStandardWhichCannotBeResolvedUnits)
{
    libcellml::UnitsPtr u1 = libcellml::Units::create();
    u1->setName("a");
    u1->addUnit("millisecond", -1);

    libcellml::UnitsPtr u2 = libcellml::Units::create();
    u2->setName("b");
    u2->addUnit("millisecond", -1);

    EXPECT_FALSE(libcellml::Units::equivalent(u1, u2));
}

TEST(Units, compareEquivalentNonStandardUnitsOneUnitsWithParentModel)
{
    libcellml::ModelPtr m = libcellml::Model::create();

    libcellml::UnitsPtr u = libcellml::Units::create();
    u->setName("millisecond");
    u->addUnit("second", "milli");

    libcellml::UnitsPtr u1 = libcellml::Units::create();
    u1->setName("per_millisecond");
    u1->addUnit("millisecond", -1);

    m->addUnits(u);
    m->addUnits(u1);

    libcellml::UnitsPtr u2 = libcellml::Units::create();
    u2->setName("per_millisecond");
    u2->addUnit("millisecond", -1);

    // Cannot resolve reference to millisecond in u2 so
    // the two units are not considered equivalent.
    EXPECT_FALSE(libcellml::Units::equivalent(u1, u2));
}

TEST(Units, compareNonCompatibleUnits)
{
    libcellml::UnitsPtr u1 = libcellml::Units::create();
    u1->setName("u1");
    u1->addUnit(libcellml::Units::StandardUnit::WEBER, "milli");

    libcellml::UnitsPtr u2 = libcellml::Units::create();
    u2->setName("u2");
    u2->addUnit(libcellml::Units::StandardUnit::LUX, 0, 1.0, 1.0);

    EXPECT_FALSE(libcellml::Units::compatible(u1, u2));
}

TEST(Units, compareOneUnitWithNullptr)
{
    libcellml::UnitsPtr u = libcellml::Units::create();
    u->setName("u");
    u->addUnit(libcellml::Units::StandardUnit::LUX, "milli");

    EXPECT_FALSE(libcellml::Units::compatible(u, nullptr));
    EXPECT_FALSE(libcellml::Units::compatible(nullptr, u));
}

TEST(Units, compareBothInputsNullptr)
{
    EXPECT_FALSE(libcellml::Units::compatible(nullptr, nullptr));
}

TEST(Units, compareUnitsCompatibleComplex)
{
    libcellml::UnitsPtr u = libcellml::Units::create();
    u->setName("u");
    u->addUnit(libcellml::Units::StandardUnit::CANDELA, "micro", 2.0, 3.0);

    libcellml::UnitsPtr u1 = libcellml::Units::create();
    u1->setName("u1");
    u1->addUnit("metre", "milli", 2.0, 1.0);
    u1->addUnit(libcellml::Units::StandardUnit::AMPERE, "milli", 1.0, 1.0);
    u1->addUnit("u");

    libcellml::UnitsPtr u2 = libcellml::Units::create();
    u2->setName("u2");
    u2->addUnit(libcellml::Units::StandardUnit::AMPERE, 0, 1.0, 3.0);
    u2->addUnit("u");
    u2->addUnit("metre", "milli", 2.0, 1.0); // Only unit attirbutes which matter now are the exponent and the base unit. Not interested in multipliers.

    libcellml::ModelPtr model = libcellml::Model::create();
    model->setName("model");
    model->addUnits(u);
    model->addUnits(u1);
    model->addUnits(u2);

    EXPECT_TRUE(libcellml::Units::compatible(u1, u2));
    EXPECT_TRUE(libcellml::Units::compatible(u2, u1));
}

TEST(Units, compareUnitsNotCompatibleComplex)
{
    libcellml::UnitsPtr u = libcellml::Units::create();
    u->setName("u");
    u->addUnit(libcellml::Units::StandardUnit::CANDELA, "micro", 2.0, 3.0);

    libcellml::UnitsPtr u1 = libcellml::Units::create();
    u1->setName("u1");
    u1->addUnit("metre", "milli", 2.0, 1.0);
    u1->addUnit(libcellml::Units::StandardUnit::AMPERE, 0, 1.0, 1.0);
    u1->addUnit("u");

    libcellml::UnitsPtr u2 = libcellml::Units::create();
    u2->setName("u2");
    u2->addUnit(libcellml::Units::StandardUnit::WEBER, 0, 1.0, 1.0);
    u2->addUnit("metre", "milli", 2.0, 1.0);

    libcellml::ModelPtr model = libcellml::Model::create();
    model->setName("model");
    model->addUnits(u);
    model->addUnits(u1);
    model->addUnits(u2);

    EXPECT_FALSE(libcellml::Units::compatible(u1, u2));
    EXPECT_FALSE(libcellml::Units::compatible(u2, u1));
}

TEST(Units, compareUnitsEquivalentSameBaseTwice)
{
    libcellml::UnitsPtr u = libcellml::Units::create();
    u->setName("u");
    u->addUnit(libcellml::Units::StandardUnit::CANDELA, "micro", 2.0, 3.0);

    libcellml::UnitsPtr u1 = libcellml::Units::create();
    u1->setName("u1");
    u1->addUnit("u");
    u1->addUnit("u");

    libcellml::UnitsPtr u2 = libcellml::Units::create();
    u2->setName("u2");
    u2->addUnit("u");
    u2->addUnit("u");

    libcellml::ModelPtr model = libcellml::Model::create();
    model->setName("model");
    model->addUnits(u);
    model->addUnits(u1);
    model->addUnits(u2);

    EXPECT_TRUE(libcellml::Units::compatible(u1, u2));
    EXPECT_TRUE(libcellml::Units::compatible(u2, u1));
}

TEST(Units, compareStandardUnitsAsCompatible)
{
    libcellml::UnitsPtr u = libcellml::Units::create();
    u->setName("u");

    libcellml::UnitsPtr u1 = libcellml::Units::create();
    u1->setName("u1");
    u1->addUnit("u");
    u1->addUnit("u");

    libcellml::UnitsPtr u2 = libcellml::Units::create();
    u2->setName("u2");
    u2->addUnit("u");
    u2->addUnit("u");

    libcellml::ModelPtr model = libcellml::Model::create();
    model->addUnits(u);
    model->addUnits(u1);
    model->addUnits(u2);

    EXPECT_TRUE(libcellml::Units::compatible(u1, u2));
    EXPECT_TRUE(libcellml::Units::compatible(u2, u1));
}

TEST(Units, isCompatibleOneUnitImported)
{
    libcellml::UnitsPtr u1 = libcellml::Units::create();
    u1->setName("u1");
    u1->addUnit(libcellml::Units::StandardUnit::RADIAN, 0, 1.0, 1.0);

    libcellml::UnitsPtr u2 = libcellml::Units::create();
    u2->setName("u2");
    u2->addUnit(libcellml::Units::StandardUnit::RADIAN, 0, 1.0, 1.0);

    libcellml::ImportSourcePtr import = libcellml::ImportSource::create();
    import->setUrl("I_am_a_url");

    u1->setImportSource(import);

    EXPECT_TRUE(u1->isImport());
    EXPECT_FALSE(libcellml::Units::compatible(u1, u2));
    EXPECT_FALSE(libcellml::Units::compatible(u2, u1));
}

TEST(Units, isCompatibleBothUnitsImported)
{
    libcellml::UnitsPtr u1 = libcellml::Units::create();
    u1->setName("u1");
    u1->addUnit(libcellml::Units::StandardUnit::RADIAN, 0, 1.0, 1.0);

    libcellml::UnitsPtr u2 = libcellml::Units::create();
    u2->setName("u2");
    u2->addUnit(libcellml::Units::StandardUnit::RADIAN, 0, 1.0, 1.0);

    libcellml::ImportSourcePtr import = libcellml::ImportSource::create();
    import->setUrl("I_am_a_url");

    u1->setImportSource(import);
    u2->setImportSource(import);

    EXPECT_TRUE(u1->isImport());
    EXPECT_FALSE(libcellml::Units::compatible(u1, u2));
    EXPECT_FALSE(libcellml::Units::compatible(u2, u1));
}

TEST(Units, isCompatibleBaseUnitImported)
{
    libcellml::ModelPtr model = libcellml::Model::create();
    model->setName("model");

    libcellml::UnitsPtr u = libcellml::Units::create();
    u->setName("u");
    u->addUnit("apples", 0, 1.0, 1.0);

    libcellml::UnitsPtr u1 = libcellml::Units::create();
    u1->setName("u1");
    u1->addUnit(libcellml::Units::StandardUnit::RADIAN, 0, 1.0, 1.0);

    libcellml::UnitsPtr u2 = libcellml::Units::create();
    u2->setName("u2");
    u2->addUnit(libcellml::Units::StandardUnit::RADIAN, 0, 1.0, 1.0);
    u2->addUnit("u", 0, 1.0, 1.0);

    model->addUnits(u);
    model->addUnits(u1);
    model->addUnits(u2);

    libcellml::ImportSourcePtr import = libcellml::ImportSource::create();
    import->setUrl("I_am_a_url");

    u->setImportSource(import);

    EXPECT_TRUE(u->isImport());
    EXPECT_FALSE(libcellml::Units::compatible(u1, u2));
    EXPECT_FALSE(libcellml::Units::compatible(u2, u1));
}

TEST(Units, isCompatibleBaseGrandchildUnitImported)
{
    libcellml::ModelPtr model = libcellml::Model::create();
    model->setName("model");

    libcellml::UnitsPtr u = libcellml::Units::create("u");

    libcellml::UnitsPtr u3 = libcellml::Units::create();
    u3->setName("u3");
    u3->addUnit("u", 0, 1.0, 1.0);

    libcellml::UnitsPtr u1 = libcellml::Units::create();
    u1->setName("u1");
    u1->addUnit(libcellml::Units::StandardUnit::RADIAN, 0, 1.0, 1.0);

    libcellml::UnitsPtr u2 = libcellml::Units::create();
    u2->setName("u2");
    u2->addUnit(libcellml::Units::StandardUnit::RADIAN, 0, 1.0, 1.0);
    u2->addUnit("u3", 0, 1.0, 1.0);

    model->addUnits(u);
    model->addUnits(u1);
    model->addUnits(u2);
    model->addUnits(u3);

    libcellml::ImportSourcePtr import = libcellml::ImportSource::create();
    import->setUrl("I_am_a_url");

    u->setImportSource(import);

    EXPECT_TRUE(u->isImport());
    EXPECT_FALSE(libcellml::Units::compatible(u1, u2));
    EXPECT_FALSE(libcellml::Units::compatible(u2, u1));
}

TEST(Units, isEquivalentBaseUnitNotInModel)
{
    libcellml::ModelPtr model = libcellml::Model::create();
    model->setName("model");

    libcellml::UnitsPtr u = libcellml::Units::create();
    u->setName("u");
    u->addUnit("apples", 0, 1.0, 1.0);

    libcellml::UnitsPtr u1 = libcellml::Units::create();
    u1->setName("u1");
    u1->addUnit(libcellml::Units::StandardUnit::RADIAN, 0, 1.0, 1.0);

    libcellml::UnitsPtr u2 = libcellml::Units::create();
    u2->setName("u2");
    u2->addUnit(libcellml::Units::StandardUnit::RADIAN, 0, 1.0, 1.0);
    u2->addUnit("u", 0, 1.0, 1.0);
    // u1 compatible to u2 test should fail because base unit "u" is not present in u1, regardless of whether "apples" exists or not

    model->addUnits(u1);
    model->addUnits(u2);

    // Units "u" not in model.  Units "apples" doesn't exist.  Units are not linked.
    EXPECT_FALSE(libcellml::Units::compatible(u1, u2));
    EXPECT_FALSE(libcellml::Units::compatible(u2, u1));
}

TEST(Units, compareCompatibleSameSizeButDifferentUnits)
{
    libcellml::UnitsPtr u1 = libcellml::Units::create();
    u1->setName("u1");

    libcellml::UnitsPtr u2 = libcellml::Units::create();
    u2->setName("u2");

    EXPECT_FALSE(libcellml::Units::compatible(u1, u2));
    EXPECT_FALSE(libcellml::Units::compatible(u2, u1));
}

TEST(Units, compareCompatibleSameSizeButDifferentExponent)
{
    libcellml::UnitsPtr u1 = libcellml::Units::create();
    u1->setName("u1");
    u1->addUnit(libcellml::Units::StandardUnit::AMPERE, 0, 1.0, 1.0);

    libcellml::UnitsPtr u2 = libcellml::Units::create();
    u2->setName("u2");
    u2->addUnit(libcellml::Units::StandardUnit::AMPERE, 0, 2.0, 1.0);

    EXPECT_FALSE(libcellml::Units::compatible(u1, u2));
    EXPECT_FALSE(libcellml::Units::compatible(u2, u1));
}

TEST(Units, compareCompatibleUnitsWhichAreDimensionless)
{
    libcellml::ModelPtr model = libcellml::Model::create();

    // u1 = u2 = u3: testing that cancelled units become dimensionless and equivalent to radians, steradians, etc.
    libcellml::UnitsPtr u1 = libcellml::Units::create();
    u1->setName("dimensionless");
    libcellml::UnitsPtr u2 = libcellml::Units::create();
    u2->setName("testunit2");
    u2->addUnit("metre", -2.0);
    u2->addUnit("metre", 2.0);
    libcellml::UnitsPtr u3 = libcellml::Units::create();
    u3->setName("testunit3");
    u3->addUnit("steradian");
    libcellml::UnitsPtr u4 = libcellml::Units::create();
    u4->setName("testunit4");
    u4->addUnit("metre", 1.0);
    u4->addUnit("metre", -1.0);
    libcellml::UnitsPtr u5 = libcellml::Units::create();
    u5->setName("testunit5");
    u5->addUnit("radian");

    model->addUnits(u1);
    model->addUnits(u2);
    model->addUnits(u3);

    EXPECT_TRUE(libcellml::Units::compatible(u1, u2));
    EXPECT_TRUE(libcellml::Units::compatible(u1, u3));
    EXPECT_TRUE(libcellml::Units::compatible(u1, u4));
    EXPECT_TRUE(libcellml::Units::compatible(u1, u5));
}

TEST(Units, compareCompatibleUnitsWhichAreNested)
{
    libcellml::ModelPtr model = libcellml::Model::create();

    // millimetres
    libcellml::UnitsPtr u1 = libcellml::Units::create();
    u1->setName("u1");
    u1->addUnit("metre", "milli"); // standard, prefix.

    // mm^3
    libcellml::UnitsPtr u2 = libcellml::Units::create();
    u2->setName("u2");
    u2->addUnit("u1", 3.0); // standard, exponent.

    // mm^6
    libcellml::UnitsPtr u3 = libcellml::Units::create();
    u3->setName("u3");
    u3->addUnit("u2", 2.0); // standard, exponent.

    // m^6
    libcellml::UnitsPtr u4 = libcellml::Units::create();
    u4->setName("u4");
    u4->addUnit("u3", 15, 1.0); // standard, prefix, exponent.

    libcellml::UnitsPtr u5 = libcellml::Units::create();
    u5->setName("u5");
    u5->addUnit("metre", 6.0); // standard, exponent.

    model->setName("model");
    model->addUnits(u1);
    model->addUnits(u2);
    model->addUnits(u3);
    model->addUnits(u4);
    model->addUnits(u5);

    EXPECT_TRUE(libcellml::Units::compatible(u4, u5));
}

TEST(Units, isBaseUnitsImported)
{
    libcellml::ModelPtr model = libcellml::Model::create();

    libcellml::UnitsPtr u1 = libcellml::Units::create();
    u1->setName("u");

    model->addUnits(u1);

    libcellml::UnitsPtr u2 = libcellml::Units::create();
    u2->setName("some_u");

    libcellml::ImportSourcePtr importSource = libcellml::ImportSource::create();
    importSource->setUrl("I_am_a_url");
    importSource->setModel(model);

    u2->setImportSource(importSource);
    u2->setImportReference("u");

    EXPECT_TRUE(u2->isImport());
    EXPECT_TRUE(u2->isBaseUnit());
}

TEST(Units, isNotBaseUnitsImported)
{
    libcellml::ModelPtr model = libcellml::Model::create();
    model->setName("model");

    libcellml::UnitsPtr u1 = libcellml::Units::create();
    libcellml::UnitsPtr u2 = libcellml::Units::create();

    u1->setName("u1");
    u1->addUnit(libcellml::Units::StandardUnit::AMPERE, 0, 1.0, 1.0);
    u2->setName("some_u");

    model->addUnits(u1);

    libcellml::ImportSourcePtr import = libcellml::ImportSource::create();
    import->setUrl("I_am_a_url");
    import->setModel(model);

    u2->setImportSource(import);
    u2->setImportReference("u1");

    EXPECT_TRUE(u2->isImport());
    EXPECT_FALSE(u2->isBaseUnit());
}

TEST(Units, isBaseUnitsNoImport)
{
    libcellml::UnitsPtr u = libcellml::Units::create();

    u->setName("some_u"); // Base unit

    EXPECT_FALSE(u->isImport());
    EXPECT_TRUE(u->isBaseUnit());
}

TEST(Units, isBaseUnitSecond)
{
    libcellml::UnitsPtr u = libcellml::Units::create();

    u->setName("second");

    EXPECT_TRUE(u->isBaseUnit());
}

TEST(Units, isBaseUnitDimensionless)
{
    libcellml::UnitsPtr u = libcellml::Units::create();

    u->setName("dimensionless");

    EXPECT_TRUE(u->isBaseUnit());
}

TEST(Units, isBaseUnitSecondRedefined)
{
    libcellml::UnitsPtr u = libcellml::Units::create();

    u->setName("second");
    u->addUnit("volt");

    EXPECT_FALSE(u->isBaseUnit());
}

TEST(Units, isBaseUnitSecondRedefinedPrinted)
{
    const std::string e =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/2.0#\" name=\"model\">\n"
        "  <units name=\"second\">\n"
        "    <unit units=\"volt\"/>\n"
        "  </units>\n"
        "</model>\n";

    libcellml::PrinterPtr p = libcellml::Printer::create();
    libcellml::ModelPtr m = libcellml::Model::create("model");
    libcellml::UnitsPtr u = libcellml::Units::create();

    u->setName("second");
    u->addUnit("volt");

    m->addUnits(u);

    EXPECT_FALSE(u->isBaseUnit());

    EXPECT_EQ(e, p->printModel(m));
}

TEST(Units, isBaseUnitVolt)
{
    libcellml::UnitsPtr u = libcellml::Units::create();

    u->setName("volt");

    EXPECT_FALSE(u->isBaseUnit());
}

TEST(Units, isBaseUnitAllStandardUnits)
{
    const std::vector<libcellml::Units::StandardUnit> standardUnits = {
        libcellml::Units::StandardUnit::AMPERE,
        libcellml::Units::StandardUnit::BECQUEREL,
        libcellml::Units::StandardUnit::CANDELA,
        libcellml::Units::StandardUnit::COULOMB,
        libcellml::Units::StandardUnit::DIMENSIONLESS,
        libcellml::Units::StandardUnit::FARAD,
        libcellml::Units::StandardUnit::GRAM,
        libcellml::Units::StandardUnit::GRAY,
        libcellml::Units::StandardUnit::HENRY,
        libcellml::Units::StandardUnit::HERTZ,
        libcellml::Units::StandardUnit::JOULE,
        libcellml::Units::StandardUnit::KATAL,
        libcellml::Units::StandardUnit::KELVIN,
        libcellml::Units::StandardUnit::KILOGRAM,
        libcellml::Units::StandardUnit::LITRE,
        libcellml::Units::StandardUnit::LUMEN,
        libcellml::Units::StandardUnit::LUX,
        libcellml::Units::StandardUnit::METRE,
        libcellml::Units::StandardUnit::MOLE,
        libcellml::Units::StandardUnit::NEWTON,
        libcellml::Units::StandardUnit::OHM,
        libcellml::Units::StandardUnit::PASCAL,
        libcellml::Units::StandardUnit::RADIAN,
        libcellml::Units::StandardUnit::SECOND,
        libcellml::Units::StandardUnit::SIEMENS,
        libcellml::Units::StandardUnit::SIEVERT,
        libcellml::Units::StandardUnit::STERADIAN,
        libcellml::Units::StandardUnit::TESLA,
        libcellml::Units::StandardUnit::VOLT,
        libcellml::Units::StandardUnit::WATT,
        libcellml::Units::StandardUnit::WEBER,
    };

    const std::vector<size_t> baseUnitIndices = {0, 2, 4, 12, 13, 17, 18, 23};

    EXPECT_EQ(size_t(31), standardUnits.size());
    EXPECT_EQ(size_t(8), baseUnitIndices.size());

    libcellml::UnitsPtr u = libcellml::Units::create();
    std::string ref;
    std::string pre;
    std::string id;
    double expMult;
    double uExp;

    size_t index = 0;
    for (auto standardUnit : standardUnits) {
        u->addUnit(standardUnit);
        u->unitAttributes(0, ref, pre, uExp, expMult, id);

        libcellml::UnitsPtr testUnit = libcellml::Units::create(ref);
        auto found = std::find(baseUnitIndices.begin(), baseUnitIndices.end(), index);
        if (found != baseUnitIndices.end()) {
            EXPECT_TRUE(testUnit->isBaseUnit());
        } else {
            EXPECT_FALSE(testUnit->isBaseUnit());
        }

        u->removeUnit(standardUnit);
        index++;
    }
}

TEST(Units, isBaseUnitsImportModelUnresolved)
{
    libcellml::UnitsPtr u1 = libcellml::Units::create();
    libcellml::UnitsPtr u2 = libcellml::Units::create();

    u1->setName("u1");
    u2->setName("some_u");

    libcellml::ImportSourcePtr import = libcellml::ImportSource::create();
    import->setUrl("I_am_a_url");

    u2->setImportSource(import);
    u2->setImportReference("u1");

    EXPECT_TRUE(u2->isImport());
    EXPECT_EQ(u2->importSource()->model(), nullptr);
    EXPECT_FALSE(u2->isBaseUnit());
}

TEST(Units, isBaseUnitImportReferenceUnresolved)
{
    libcellml::ModelPtr model = libcellml::Model::create();
    model->setName("model");

    libcellml::UnitsPtr u1 = libcellml::Units::create();
    u1->setName("u");
    libcellml::UnitsPtr u2 = libcellml::Units::create();
    u2->setName("some_other_u");

    libcellml::ImportSourcePtr import = libcellml::ImportSource::create();
    import->setUrl("I_am_a_url");

    model->addUnits(u1);

    u2->setImportSource(import);
    import->setModel(model);

    EXPECT_TRUE(u2->isImport());
    EXPECT_TRUE(u2->importReference().empty());
    EXPECT_FALSE(u2->isBaseUnit());
}

TEST(Units, isBaseUnitImportedTwice)
{
    libcellml::ModelPtr m_i1 = libcellml::Model::create();
    m_i1->setName("m_i1");
    libcellml::ModelPtr m_i2 = libcellml::Model::create();
    m_i2->setName("m_i2");

    libcellml::UnitsPtr u_i1 = libcellml::Units::create();
    libcellml::UnitsPtr u_i2 = libcellml::Units::create();
    libcellml::UnitsPtr u_i0 = libcellml::Units::create();

    u_i0->setName("some_other_u");
    u_i1->setName("u_i1");
    u_i2->setName("u_i2");

    m_i1->addUnits(u_i1);
    m_i2->addUnits(u_i2);

    libcellml::ImportSourcePtr i2 = libcellml::ImportSource::create();
    i2->setUrl("I_am_a_url");
    i2->setModel(m_i2);
    u_i1->setImportSource(i2);
    u_i1->setImportReference("u_i2");

    libcellml::ImportSourcePtr i1 = libcellml::ImportSource::create();
    i1->setUrl("I_am_another_url");
    i1->setModel(m_i1);
    u_i0->setImportSource(i1);
    u_i0->setImportReference("u_i1");

    EXPECT_TRUE(u_i0->isImport());
    EXPECT_TRUE(u_i1->isImport());
    EXPECT_FALSE(u_i2->isImport());
    EXPECT_TRUE(u_i0->isBaseUnit());
}

TEST(Units, isNotBaseUnitImportedTwice)
{
    libcellml::ModelPtr m_i1 = libcellml::Model::create();
    m_i1->setName("m_i1");
    libcellml::ModelPtr m_i2 = libcellml::Model::create();
    m_i2->setName("m_i2");

    libcellml::UnitsPtr u_i1 = libcellml::Units::create();
    libcellml::UnitsPtr u_i2 = libcellml::Units::create();
    libcellml::UnitsPtr u_i0 = libcellml::Units::create();

    u_i2->setName("u_i2");
    u_i2->addUnit(libcellml::Units::StandardUnit::AMPERE, 0, 1.0, 1.0);
    u_i1->setName("u_i1");
    u_i0->setName("some_other_u");

    m_i1->addUnits(u_i1);
    m_i2->addUnits(u_i2);

    libcellml::ImportSourcePtr i2 = libcellml::ImportSource::create();
    i2->setUrl("I_am_a_url");
    i2->setModel(m_i2);
    u_i1->setImportSource(i2);
    u_i1->setImportReference("u_i2");

    libcellml::ImportSourcePtr i1 = libcellml::ImportSource::create();
    i1->setUrl("I_am_another_url");
    i1->setModel(m_i1);
    u_i0->setImportSource(i1);
    u_i0->setImportReference("u_i1");

    EXPECT_TRUE(u_i0->isImport());
    EXPECT_TRUE(u_i1->isImport());
    EXPECT_FALSE(u_i2->isImport());
    EXPECT_FALSE(u_i0->isBaseUnit());
}

TEST(Units, scalingFactorAcrossBaseUnits)
{
    libcellml::UnitsPtr u1 = libcellml::Units::create("second");
    libcellml::UnitsPtr u2 = libcellml::Units::create("millisecond");
    u2->addUnit(libcellml::Units::StandardUnit::SECOND, libcellml::Units::Prefix::MILLI);

    EXPECT_EQ(0.001, libcellml::Units::scalingFactor(u1, u2));
    EXPECT_EQ(1000.0, libcellml::Units::scalingFactor(u2, u1));
}

TEST(Units, scalingFactorAcrossStandardUnits)
{
    libcellml::UnitsPtr u1 = libcellml::Units::create("volt");
    libcellml::UnitsPtr u2 = libcellml::Units::create("millivolt");
    u2->addUnit(libcellml::Units::StandardUnit::VOLT, libcellml::Units::Prefix::MILLI);

    EXPECT_EQ(0.001, libcellml::Units::scalingFactor(u1, u2));
    EXPECT_EQ(1000.0, libcellml::Units::scalingFactor(u2, u1));
}

TEST(Units, scalingFactorChildUnitsNotFound)
{
    auto model = libcellml::Model::create("nurseryrhymes");
    auto u1 = libcellml::Units::create("bo_peep");
    u1->addUnit("sheep");

    auto u2 = libcellml::Units::create("flock");

    model->addUnits(u1);
    model->addUnits(u2);

    EXPECT_EQ(0.0, libcellml::Units::scalingFactor(u1, u2));
}

TEST(Units, scalingFactorGrandchildUnitsNotFound)
{
    auto model = libcellml::Model::create("nurseryrhymes");

    auto u0 = libcellml::Units::create("sheep");
    u0->addUnit("wool");

    auto u1 = libcellml::Units::create("bo_peep");
    u1->addUnit("sheep");

    auto u2 = libcellml::Units::create("flock");
    u2->addUnit("sheep");

    model->addUnits(u0);
    model->addUnits(u1);
    model->addUnits(u2);

    // Child units of "wool" are not found within "sheep" units.  Comparison should return 0.0.
    EXPECT_EQ(0.0, libcellml::Units::scalingFactor(u1, u2));
}

TEST(Units, compatibleUnitsInDifferentModelsChildNotFound)
{
    auto m1 = libcellml::Model::create("nurseryrhymes");
    auto m2 = libcellml::Model::create("farmwork");
    auto u1 = libcellml::Units::create("bo_peep");
    u1->addUnit("sheep");

    auto u2 = libcellml::Units::create("flock");
    auto u3 = libcellml::Units::create("sheep");
    u2->addUnit("sheep");

    m1->addUnits(u1);
    m2->addUnits(u2);
    m2->addUnits(u3);

    // Child unit of "sheep" exists only in m2, return 0.0.
    EXPECT_EQ(0.0, libcellml::Units::scalingFactor(u1, u2));
}

TEST(Units, importedGrandchildUnitsNotCompatible)
{
    auto model = libcellml::Model::create("nurseryrhymes");

    auto imported_units = libcellml::Units::create("imported_units");
    auto imp = libcellml::ImportSource::create();
    imp->setUrl("i_am_a_url");
    imported_units->setImportSource(imp);

    auto u0 = libcellml::Units::create("u0");
    u0->addUnit("imported_units");

    auto u1 = libcellml::Units::create("u1");
    u1->addUnit("u0");

    auto u2 = libcellml::Units::create("u2");
    u2->addUnit("u1");

    auto u3 = libcellml::Units::create("u3");
    u3->addUnit("imported_units");

    model->addUnits(u0);
    model->addUnits(u1);
    model->addUnits(u2);
    model->addUnits(u3);
    model->addUnits(imported_units);

    // Expect false only because the first units "imported_units" is imported... otherwise it would be true.
    // Imports are not resolved during the compatibility/equivalence checking, so any comparisons which
    // have unresolved imports must return `false` as there's not enough information to confirm that they're
    // the same.
    EXPECT_FALSE(libcellml::Units::compatible(u2, u3));
}

TEST(Units, scalingFactorBetweenExponentialUnits)
{
    libcellml::UnitsPtr u1 = libcellml::Units::create();
    u1->setName("u1");
    u1->addUnit("metre", 0, 3.0, 1000.0);
    libcellml::UnitsPtr u2 = libcellml::Units::create();
    u2->setName("u2");
    u2->addUnit("metre", 0, 1.0, 1.0);
    u2->addUnit("metre", 0, 1.0, 1.0);
    u2->addUnit("metre", 0, 1.0, 1.0);

    EXPECT_EQ(1000.0, libcellml::Units::scalingFactor(u2, u1));
    EXPECT_EQ(0.001, libcellml::Units::scalingFactor(u1, u2));
}

TEST(Units, scalingFactorBetweenMultipliedUnits)
{
    libcellml::UnitsPtr u1 = libcellml::Units::create();
    u1->setName("u1");
    u1->addUnit("metre", 0, 3.0, 1000.0);
    libcellml::UnitsPtr u2 = libcellml::Units::create();
    u2->setName("u2");
    u2->addUnit("metre", 0, 3.0, 1.0);

    EXPECT_EQ(1000.0, libcellml::Units::scalingFactor(u2, u1));
    EXPECT_EQ(0.001, libcellml::Units::scalingFactor(u1, u2));
}

TEST(Units, parsedUnitsRequiringImports)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("requires_imports.cellml"));

    // When parsing a model it's hard to know whether the units it uses are imported
    // or not if the import is in a child units item.  Using the Units::requiresImports()
    // function should tell us.

    EXPECT_EQ(size_t(3), model->unitsCount());
    EXPECT_FALSE(model->units("grandpa")->isImport());
    EXPECT_TRUE(model->units("grandpa")->requiresImports());
}

TEST(Units, scalingFactorIncompatibleUnitsNoChecking)
{
    // This test shows that a scaling factor can be returned for incompatible units
    // when compatibility checking is turned off.

    auto model = libcellml::Model::create("st_clements");
    auto lemons = libcellml::Units::create("lemons");
    lemons->addUnit("metre", "kilo");
    auto oranges = libcellml::Units::create("oranges");
    oranges->addUnit("second", "milli");
    model->addUnits(oranges);
    model->addUnits(lemons);

    EXPECT_EQ(1.0E+6, libcellml::Units::scalingFactor(oranges, lemons, false));
}

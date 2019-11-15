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

    libcellml::Printer printer;
    const std::string a = printer.printModel(m);
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

    libcellml::Printer printer;
    const std::string a = printer.printModel(m);
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

    libcellml::Printer printer;
    const std::string a = printer.printModel(m);
    EXPECT_EQ(e, a);
}

TEST(Units, addUnitsVariations)
{
    libcellml::UnitsPtr u = libcellml::Units::create();
    u->setName("compound_unit");

    u->addUnit(libcellml::Units::StandardUnit::AMPERE, libcellml::Prefix::MICRO);
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

    u->addUnit(libcellml::Units::StandardUnit::AMPERE, libcellml::Prefix::MICRO);
    u->addUnit(libcellml::Units::StandardUnit::KELVIN);
    u->addUnit(libcellml::Units::StandardUnit::SIEMENS, libcellml::Prefix::MILLI, -1.0);

    m->addUnits(u);

    libcellml::Printer printer;
    const std::string a = printer.printModel(m);
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

    libcellml::Printer printer;
    const std::string a = printer.printModel(m);
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

    libcellml::Printer printer;
    std::string a = printer.printModel(m);
    EXPECT_EQ(e1, a);

    u1->removeAllUnits();
    a = printer.printModel(m);
    EXPECT_EQ(e2, a);

    EXPECT_TRUE(m->removeUnits("simple_unit_2"));
    EXPECT_TRUE(m->removeUnits(u3));
    a = printer.printModel(m);
    EXPECT_EQ(e3, a);
    EXPECT_EQ(size_t(2), m->unitsCount());

    EXPECT_FALSE(m->removeUnits("gram"));
    EXPECT_FALSE(m->removeUnits(u5));
    EXPECT_FALSE(m->removeUnits(3));
    EXPECT_EQ(size_t(2), m->unitsCount());

    EXPECT_TRUE(m->removeUnits(1));
    EXPECT_EQ(size_t(1), m->unitsCount());

    m->removeAllUnits();
    a = printer.printModel(m);
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

    u1->addUnit(libcellml::Units::StandardUnit::AMPERE, libcellml::Prefix::MICRO);
    u1->addUnit(libcellml::Units::StandardUnit::KELVIN);
    u1->addUnit(libcellml::Units::StandardUnit::SIEMENS, libcellml::Prefix::MILLI, -1.0);

    m->addUnits(u1);

    libcellml::UnitsPtr u2 = libcellml::Units::create();
    u2->setName("valid_name");

    m->addUnits(u2);

    libcellml::UnitsPtr u3 = libcellml::Units::create();
    u3->setName("multiplied");
    u3->addUnit("compound_unit");
    u3->addUnit("valid_name");

    m->addUnits(u3);

    libcellml::Printer printer;
    const std::string a = printer.printModel(m);
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

    libcellml::Printer printer;
    const std::string a = printer.printModel(m);
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

    libcellml::Printer printer;
    const std::string a = printer.printModel(m);
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
    u->addUnit(libcellml::Units::StandardUnit::AMPERE, libcellml::Prefix::CENTI);
    u->addUnit(libcellml::Units::StandardUnit::AMPERE, libcellml::Prefix::MICRO);

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

    libcellml::Printer printer;
    std::string a = printer.printModel(m);
    EXPECT_EQ(e, a);

    // Parse
    libcellml::ParserPtr parser = libcellml::Parser::create();
    libcellml::ModelPtr model = parser->parseModel(e);
    a = printer.printModel(model);
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

    validator->validateModel(m);

    EXPECT_EQ(size_t(1), validator->errorCount());
    EXPECT_EQ(e, validator->error(0)->description());
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
    u2->addUnit(libcellml::Units::StandardUnit::LUX, 0, 1.0, 1.0);

    EXPECT_NEAR(0.002, libcellml::Units::scalingFactor(u1, u2), 1e-12);
    EXPECT_NEAR(500.0, libcellml::Units::scalingFactor(u2, u1), 1e-12);
}

TEST(Units, compareIncompatiableMultiplierSimple)
{
    // u1 = 1000*u2
    libcellml::UnitsPtr u1 = libcellml::Units::create();
    u1->setName("u1");
    u1->addUnit("metre", 0, 1.0, 1.0);
    libcellml::UnitsPtr u2 = libcellml::Units::create();
    u2->setName("u2");
    u2->addUnit("second", 0, 1.0, 1.0);

    // Incompatible units but return a scaling factor of 1.0.
    EXPECT_EQ(1.0, libcellml::Units::scalingFactor(u1, u2));
    EXPECT_EQ(1.0, libcellml::Units::scalingFactor(u2, u1));
}

TEST(Units, complicatedMultiplicationFactorUnits)
{
    libcellml::ModelPtr model = libcellml::Model::create();

    libcellml::UnitsPtr u = libcellml::Units::create();
    u->setName("u");

    libcellml::UnitsPtr u1 = libcellml::Units::create();
    u1->setName("u1");
    u1->addUnit("u", "milli", 2.0, 1000.0); //m^2
    u1->addUnit("dimensionless");

    libcellml::UnitsPtr u2 = libcellml::Units::create();
    u2->setName("u2");
    u2->addUnit("u", "kilo", 2.0, 0.001); // standard, exponent.
    u2->addUnit("dimensionless");

    libcellml::UnitsPtr u3 = libcellml::Units::create();
    u3->setName("u3");
    u3->addUnit("u", "kilo", 4.0, 0.001); // standard, exponent.

    libcellml::UnitsPtr u4 = libcellml::Units::create();
    u4->setName("u4");
    u4->addUnit("u2", "milli", 4.0, 1000.0);

    libcellml::UnitsPtr apple = libcellml::Units::create();
    apple->setName("apple");

    libcellml::UnitsPtr banana = libcellml::Units::create();
    banana->setName("banana");

    libcellml::UnitsPtr u5 = libcellml::Units::create();
    u5->setName("bushell_of_apples");
    u5->addUnit("apple", "mega", 1.0, 1000.0); // 1000*mega*apple^1

    libcellml::UnitsPtr square_apple = libcellml::Units::create();
    square_apple->setName("square_apple");
    square_apple->addUnit("apple", 2);

    libcellml::UnitsPtr incredible_pile_of_square_apples = libcellml::Units::create();
    incredible_pile_of_square_apples->setName("incredible_pile_of_square_apples");
    incredible_pile_of_square_apples->addUnit("square_apple", "mega", 1, 100.0);

    libcellml::UnitsPtr bunch_of_bananas = libcellml::Units::create();
    bunch_of_bananas->setName("bunch_of_bananas");
    bunch_of_bananas->addUnit("banana", 1, 1, 1.0); // 10 bananas

    model->setName("model");
    model->addUnits(u);
    model->addUnits(u1);
    model->addUnits(u2);
    model->addUnits(u3);
    model->addUnits(u4);
    model->addUnits(u5);
    model->addUnits(apple);
    model->addUnits(banana);
    model->addUnits(square_apple);
    model->addUnits(incredible_pile_of_square_apples);
    model->addUnits(bunch_of_bananas);

    EXPECT_EQ(1.0, libcellml::Units::scalingFactor(u1, u2));
    EXPECT_EQ(1.0, libcellml::Units::scalingFactor(u3, u4));
    EXPECT_EQ(1e-08, libcellml::Units::scalingFactor(incredible_pile_of_square_apples, square_apple));
    // Incompatible units but return a scaling factor.
    EXPECT_EQ(1e-07, libcellml::Units::scalingFactor(incredible_pile_of_square_apples, bunch_of_bananas));
}

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


TEST(Units, serialise) {
    const std::string e = "";
    libcellml::Units u;
    std::string a = u.serialise(libcellml::Format::XML);
    EXPECT_EQ(e, a);
}

TEST(Units, validName) {
    const std::string e =
            "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
            "<model xmlns=\"http://www.cellml.org/cellml/1.2#\">"
            "<units name=\"valid_name\" base_unit=\"yes\"/>"
            "</model>";

    libcellml::Model m;

    libcellml::UnitsPtr u = std::make_shared<libcellml::Units>();;
    u->setName("valid_name");

    /* Base unit is false by default */
    EXPECT_FALSE(u->isBaseUnit());
    u->setBaseUnit();
    EXPECT_TRUE(u->isBaseUnit());
    u->setBaseUnit(false);
    EXPECT_FALSE(u->isBaseUnit());
    u->setBaseUnit(true);
    EXPECT_TRUE(u->isBaseUnit());

    m.addUnits(u);

    std::string a = m.serialise(libcellml::Format::XML);
    EXPECT_EQ(e, a);
    EXPECT_EQ("valid_name", u->getName());
}

TEST(Units, invalidName) {
    const std::string e =
            "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
            "<model xmlns=\"http://www.cellml.org/cellml/1.2#\">"
            "<units name=\"invalid name\" base_unit=\"yes\"/>"
            "</model>";

    libcellml::Model m;

    libcellml::UnitsPtr u = std::make_shared<libcellml::Units>();
    u->setName("invalid name");
    u->setBaseUnit();

    m.addUnits(u);

    std::string a = m.serialise(libcellml::Format::XML);
    EXPECT_EQ(e, a);
    EXPECT_EQ("invalid name", u->getName());
}

TEST(Units, compoundUnitsRaw) {
    const std::string e =
            "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
            "<model xmlns=\"http://www.cellml.org/cellml/1.2#\">"
            "<units name=\"compound_unit\">"
            "<unit prefix=\"-6\" units=\"ampere\"/>"
            "<unit units=\"kelvin\"/>"
            "<unit exponent=\"-1\" prefix=\"-3\" units=\"siemens\"/>"
            "</units>"
            "</model>";

    libcellml::Model m;

    libcellml::UnitsPtr u = std::make_shared<libcellml::Units>();
    u->setName("compound_unit");

    u->addUnit("ampere", -6, 1.0);
    u->addUnit("kelvin");
    u->addUnit("siemens", -3, -1.0);

    m.addUnits(u);

    std::string a = m.serialise(libcellml::Format::XML);
    EXPECT_EQ(e, a);
}

TEST(Units, compoundUnitsUsingDefines) {
    const std::string e =
            "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
            "<model xmlns=\"http://www.cellml.org/cellml/1.2#\">"
            "<units name=\"compound_unit\">"
            "<unit prefix=\"micro\" units=\"ampere\"/>"
            "<unit units=\"kelvin\"/>"
            "<unit exponent=\"-1\" prefix=\"milli\" units=\"siemens\"/>"
            "</units>"
            "</model>";

    libcellml::Model m;

    libcellml::UnitsPtr u = std::make_shared<libcellml::Units>();
    u->setName("compound_unit");

    u->addUnit(libcellml::STANDARD_UNIT_AMPERE, libcellml::Prefix::MICRO);
    u->addUnit(libcellml::STANDARD_UNIT_KELVIN);
    u->addUnit(libcellml::STANDARD_UNIT_SIEMENS, libcellml::Prefix::MILLI, -1.0);

    m.addUnits(u);

    std::string a = m.serialise(libcellml::Format::XML);
    EXPECT_EQ(e, a);
}

TEST(Units, compoundUnitsUsingDefinesAndStringUnitsAndPrefix) {
    const std::string e =
            "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
            "<model xmlns=\"http://www.cellml.org/cellml/1.2#\">"
            "<units name=\"compound_unit\">"
            "<unit prefix=\"micro\" units=\"ampere\"/>"
            "<unit units=\"kelvin\"/>"
            "<unit exponent=\"-1\" prefix=\"milli\" units=\"siemens\"/>"
            "<unit prefix=\"1.7e310\" units=\"meter\"/>"
            "</units>"
            "</model>";

    libcellml::Model m;

    libcellml::UnitsPtr u = std::make_shared<libcellml::Units>();
    u->setName("compound_unit");

    u->addUnit(libcellml::STANDARD_UNIT_AMPERE, "micro");
    u->addUnit("kelvin");
    u->addUnit("siemens", "milli", -1.0);
    u->addUnit("meter", "1.7e310");

    m.addUnits(u);

    std::string a = m.serialise(libcellml::Format::XML);
    EXPECT_EQ(e, a);
}

TEST(Units, removeUnitsMethodsAndCount) {
    const std::string e1 =
            "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
            "<model xmlns=\"http://www.cellml.org/cellml/1.2#\">"
              "<units name=\"compound_unit\">"
                "<unit prefix=\"micro\" units=\"ampere\"/>"
                "<unit prefix=\"1.7e10\" units=\"meter\"/>"
              "</units>"
              "<units name=\"simple_unit_2\"/>"
              "<units name=\"simple_unit_3\"/>"
              "<units name=\"simple_unit_4\"/>"
            "</model>";
    const std::string e2 =
            "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
            "<model xmlns=\"http://www.cellml.org/cellml/1.2#\">"
              "<units name=\"compound_unit\"/>"
              "<units name=\"simple_unit_2\"/>"
              "<units name=\"simple_unit_3\"/>"
              "<units name=\"simple_unit_4\"/>"
            "</model>";
    const std::string e3 =
            "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
            "<model xmlns=\"http://www.cellml.org/cellml/1.2#\">"
              "<units name=\"compound_unit\"/>"
              "<units name=\"simple_unit_4\"/>"
            "</model>";
    const std::string e4 =
            "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
            "<model xmlns=\"http://www.cellml.org/cellml/1.2#\"/>";

    libcellml::Model m;

    libcellml::UnitsPtr u1 = std::make_shared<libcellml::Units>();
    libcellml::UnitsPtr u2 = std::make_shared<libcellml::Units>();
    libcellml::UnitsPtr u3 = std::make_shared<libcellml::Units>();
    libcellml::UnitsPtr u4 = std::make_shared<libcellml::Units>();
    libcellml::UnitsPtr u5 = std::make_shared<libcellml::Units>();
    u1->setName("compound_unit");
    u2->setName("simple_unit_2");
    u3->setName("simple_unit_3");
    u4->setName("simple_unit_4");

    u1->addUnit(libcellml::STANDARD_UNIT_AMPERE, "micro");
    u1->addUnit("kelvin");
    u1->addUnit("siemens", "milli", -1.0);
    u1->addUnit("meter", "1.7e10");
    m.addUnits(u1);
    m.addUnits(u2);
    m.addUnits(u3);
    m.addUnits(u4);

    EXPECT_EQ(u1->unitCount(), 4);
    u1->removeUnit("siemens");
    u1->removeUnit(libcellml::STANDARD_UNIT_KELVIN);
    std::string a = m.serialise(libcellml::Format::XML);
    EXPECT_EQ(e1, a);
    EXPECT_THROW(u1->removeUnit("gram"), std::out_of_range);

    u1->removeAllUnits();
    a = m.serialise(libcellml::Format::XML);
    EXPECT_EQ(e2, a);

    m.removeUnits("simple_unit_2");
    m.removeUnits(u3);
    a = m.serialise(libcellml::Format::XML);
    EXPECT_EQ(e3, a);
    EXPECT_EQ(m.unitsCount(), 2);
    EXPECT_THROW(m.removeUnits("gram"), std::out_of_range);
    EXPECT_THROW(m.removeUnits(u5), std::out_of_range);

    m.removeAllUnits();
    a = m.serialise(libcellml::Format::XML);
    EXPECT_EQ(e4, a);
}

TEST(Units, multiply) {
    const std::string e =
            "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
            "<model xmlns=\"http://www.cellml.org/cellml/1.2#\">"
            "<units name=\"compound_unit\">"
            "<unit prefix=\"micro\" units=\"ampere\"/>"
            "<unit units=\"kelvin\"/>"
            "<unit exponent=\"-1\" prefix=\"milli\" units=\"siemens\"/>"
            "</units>"
            "<units name=\"valid_name\" base_unit=\"yes\"/>"
            "<units name=\"multiplied\">"
            "<unit units=\"compound_unit\"/>"
            "<unit units=\"valid_name\"/>"
            "</units>"
            "</model>";

    libcellml::Model m;

    libcellml::UnitsPtr u1 = std::make_shared<libcellml::Units>();
    u1->setName("compound_unit");

    u1->addUnit(libcellml::STANDARD_UNIT_AMPERE, libcellml::Prefix::MICRO);
    u1->addUnit(libcellml::STANDARD_UNIT_KELVIN);
    u1->addUnit(libcellml::STANDARD_UNIT_SIEMENS, libcellml::Prefix::MILLI, -1.0);

    m.addUnits(u1);

    libcellml::UnitsPtr u2 = std::make_shared<libcellml::Units>();
    u2->setName("valid_name");
    u2->setBaseUnit();

    m.addUnits(u2);

    libcellml::UnitsPtr u3 = std::make_shared<libcellml::Units>();
    u3->setName("multiplied");
    u3->addUnit("compound_unit");
    u3->addUnit("valid_name");

    m.addUnits(u3);

    std::string a = m.serialise(libcellml::Format::XML);
    EXPECT_EQ(e, a);
}

TEST(Units, newBaseUnit) {
    const std::string e =
            "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
            "<model xmlns=\"http://www.cellml.org/cellml/1.2#\">"
            "<units name=\"pH\" base_unit=\"yes\"/>"
            "</model>";

    libcellml::Model m;

    libcellml::UnitsPtr u = std::make_shared<libcellml::Units>();
    u->setName("pH");
    u->setBaseUnit();

    m.addUnits(u);

    std::string a = m.serialise(libcellml::Format::XML);
    EXPECT_EQ(e, a);
    EXPECT_EQ("pH", u->getName());
}

TEST(Units, farhenheit) {
    const std::string e =
            "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
            "<model xmlns=\"http://www.cellml.org/cellml/1.2#\">"
            "<units name=\"fahrenheit\">"
            "<unit multiplier=\"1.8\" offset=\"32\" units=\"celsius\"/>"
            "</units>"
            "</model>";

    libcellml::Model m;

    libcellml::UnitsPtr u = std::make_shared<libcellml::Units>();
    u->setName("fahrenheit");

    /* Give prefix and exponent their default values. */
    u->addUnit(libcellml::STANDARD_UNIT_CELSIUS, 0.0, 1.0, 1.8, 32.0);
    m.addUnits(u);

    std::string a = m.serialise(libcellml::Format::XML);
    EXPECT_EQ(e, a);
    EXPECT_EQ("fahrenheit", u->getName());
}

TEST(Units, multiple) {
    const std::string e =
            "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
            "<model xmlns=\"http://www.cellml.org/cellml/1.2#\">"
            "<units name=\"fahrenheit\">"
            "<unit multiplier=\"1.8\" offset=\"32\" units=\"celsius\"/>"
            "</units>"
            "<units name=\"metres_per_second\">"
            "<unit units=\"metre\"/>"
            "<unit exponent=\"-1\" units=\"second\"/>"
            "</units>"
            "</model>";

    libcellml::Model m;

    libcellml::UnitsPtr u1 = std::make_shared<libcellml::Units>();
    u1->setName("fahrenheit");

    /* Give prefix and exponent their default values. */
    u1->addUnit(libcellml::STANDARD_UNIT_CELSIUS, 0, 1.0, 1.8, 32.0);

    libcellml::UnitsPtr u2 = std::make_shared<libcellml::Units>();
    u2->setName("metres_per_second");
    u2->addUnit(libcellml::STANDARD_UNIT_METRE);
    u2->addUnit(libcellml::STANDARD_UNIT_SECOND, -1.0);

    m.addUnits(u1);
    m.addUnits(u2);

    std::string a = m.serialise(libcellml::Format::XML);
    EXPECT_EQ(e, a);
}


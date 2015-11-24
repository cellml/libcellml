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


TEST(Units, serialise) {
    const std::string e = "";
    libcellml::Units u;
    std::string a = u.serialise(libcellml::FORMAT_XML);
    EXPECT_EQ(e, a);
}

TEST(Units, valid_name) {
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

    std::string a = m.serialise(libcellml::FORMAT_XML);
    EXPECT_EQ(e, a);
    EXPECT_EQ("valid_name", u->getName());
}

TEST(Units, invalid_name) {
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

    std::string a = m.serialise(libcellml::FORMAT_XML);
    EXPECT_EQ(e, a);
    EXPECT_EQ("invalid name", u->getName());
}

TEST(Units, compound_units_raw) {
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

    u->addUnit("ampere", -6);
    u->addUnit("kelvin");
    u->addUnit("siemens", -3, -1.0);

    m.addUnits(u);

    std::string a = m.serialise(libcellml::FORMAT_XML);
    EXPECT_EQ(e, a);
}

TEST(Units, compound_units_using_defines) {
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

    u->addUnit(libcellml::STANDARD_UNIT_AMPERE, libcellml::PREFIX_MICRO);
    u->addUnit(libcellml::STANDARD_UNIT_KELVIN);
    u->addUnit(libcellml::STANDARD_UNIT_SIEMENS, libcellml::PREFIX_MILLI, -1.0);

    m.addUnits(u);

    std::string a = m.serialise(libcellml::FORMAT_XML);
    EXPECT_EQ(e, a);
}

TEST(Units, new_base_unit) {
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

    std::string a = m.serialise(libcellml::FORMAT_XML);
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
    u->addUnit(libcellml::STANDARD_UNIT_CELSIUS, libcellml::PREFIX_UNIT, 1.0, 1.8, 32.0);
    m.addUnits(u);

    std::string a = m.serialise(libcellml::FORMAT_XML);
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
    u1->addUnit(libcellml::STANDARD_UNIT_CELSIUS, libcellml::PREFIX_UNIT, 1.0, 1.8, 32.0);

    libcellml::UnitsPtr u2 = std::make_shared<libcellml::Units>();
    u2->setName("metres_per_second");
    u2->addUnit(libcellml::STANDARD_UNIT_METRE);
    u2->addUnit(libcellml::STANDARD_UNIT_SECOND, -1.0);

    m.addUnits(u1);
    m.addUnits(u2);

    std::string a = m.serialise(libcellml::FORMAT_XML);
    EXPECT_EQ(e, a);
}


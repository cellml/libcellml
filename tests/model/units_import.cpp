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

TEST(UnitsImport, basics) {
    const std::string e = "";

    libcellml::ImportSourcePtr imp = std::make_shared<libcellml::ImportSource>();
    imp->setSource("a-model.xml");

    libcellml::UnitsPtr u = std::make_shared<libcellml::Units>();

    EXPECT_EQ(u->getImportSource(), nullptr);
    EXPECT_EQ(u->getImportReference(), "");

    u->setImportSource(imp);
    u->setImportReference("bob");

    EXPECT_EQ(u->getImportSource(), imp);
    EXPECT_EQ(u->getImportReference(), "bob");

    libcellml::Printer printer;
    const std::string a = printer.printUnits(u);
    EXPECT_EQ(e, a);
}

TEST(UnitsImport, importValidName) {
    const std::string e =
            "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
            "<model xmlns=\"http://www.cellml.org/cellml/2.0#\">"
                "<import xlink:href=\"some-other-model.xml\" xmlns:xlink=\"http://www.w3.org/1999/xlink\">"
                    "<units units_ref=\"a_units_in_that_model\" name=\"units_in_this_model\"/>"
                "</import>"
            "</model>";

    libcellml::Model m;
    libcellml::ImportSourcePtr imp = std::make_shared<libcellml::ImportSource>();
    imp->setSource("some-other-model.xml");

    libcellml::UnitsPtr importedUnits = std::make_shared<libcellml::Units>();

    EXPECT_EQ(importedUnits->getImportSource(), nullptr);

    EXPECT_FALSE(importedUnits->isImport());

    importedUnits->setName("units_in_this_model");
    importedUnits->setSourceUnits(imp, "a_units_in_that_model");

    EXPECT_EQ(importedUnits->getImportSource(), imp);

    EXPECT_TRUE(importedUnits->isImport());

    m.addUnits(importedUnits);

    libcellml::Printer printer;
    const std::string a = printer.printModel(m);
    EXPECT_EQ(e, a);
}

TEST(UnitsImport, importInvalidName) {
    const std::string e =
            "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
            "<model xmlns=\"http://www.cellml.org/cellml/2.0#\">"
                "<import xlink:href=\"some-other-model.xml\" xmlns:xlink=\"http://www.w3.org/1999/xlink\">"
                    "<units units_ref=\"a units in that model\" name=\"units_in_this_model\"/>"
                "</import>"
            "</model>";

    libcellml::Model m;
    libcellml::ImportSourcePtr imp = std::make_shared<libcellml::ImportSource>();
    imp->setSource("some-other-model.xml");

    libcellml::UnitsPtr importedUnits = std::make_shared<libcellml::Units>();

    EXPECT_EQ(importedUnits->getImportSource(), nullptr);

    importedUnits->setName("units_in_this_model");
    importedUnits->setSourceUnits(imp, "a units in that model");

    EXPECT_EQ(importedUnits->getImportSource(), imp);

    m.addUnits(importedUnits);

    libcellml::Printer printer;
    const std::string a = printer.printModel(m);
    EXPECT_EQ(e, a);
}

TEST(UnitsImport, nonExistentURL) {
    const std::string e =
            "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
            "<model xmlns=\"http://www.cellml.org/cellml/2.0#\">"
                "<import xlink:href=\"http://someplace.world/cellml/model.xml\" xmlns:xlink=\"http://www.w3.org/1999/xlink\">"
                    "<units units_ref=\"per_mole\" name=\"noble_per_mole\"/>"
                "</import>"
            "</model>";

    libcellml::Model m;
    libcellml::ImportSourcePtr imp = std::make_shared<libcellml::ImportSource>();
    imp->setSource("http://someplace.world/cellml/model.xml");

    libcellml::UnitsPtr importedUnits = std::make_shared<libcellml::Units>();

    EXPECT_EQ(importedUnits->getImportSource(), nullptr);

    importedUnits->setName("noble_per_mole");
    importedUnits->setSourceUnits(imp, "per_mole");

    EXPECT_EQ(importedUnits->getImportSource(), imp);

    EXPECT_EQ(0, m.unitsCount());
    m.addUnits(importedUnits);
    EXPECT_EQ(1, m.unitsCount());

    libcellml::Printer printer;
    const std::string a = printer.printModel(m);
    EXPECT_EQ(e, a);
}

TEST(UnitsImport, importModifyAndParse) {
    const std::string e =
            "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
            "<model xmlns=\"http://www.cellml.org/cellml/2.0#\">"
                "<import xlink:href=\"some-other-model.xml\" xmlns:xlink=\"http://www.w3.org/1999/xlink\">"
                    "<units units_ref=\"a_units_in_that_model\" name=\"units_in_this_model\"/>"
                "</import>"
                "<units name=\"multiplied_import\">"
                    "<unit multiplier=\"5.6\" units=\"units_in_this_model\"/>"
                "</units>"
                "<units name=\"prefixed_import\">"
                    "<unit prefix=\"yotta\" units=\"units_in_this_model\"/>"
                "</units>"
                "<units name=\"exponented_import\">"
                    "<unit exponent=\"3\" units=\"units_in_this_model\"/>"
                "</units>"
                "<units name=\"all_import\">"
                    "<unit exponent=\"-4\" multiplier=\"-1.3\" prefix=\"-17\" units=\"units_in_this_model\"/>"
                "</units>"
            "</model>";

    libcellml::Model m;
    libcellml::ImportSourcePtr imp = std::make_shared<libcellml::ImportSource>();
    imp->setSource("some-other-model.xml");

    libcellml::UnitsPtr importedUnits = std::make_shared<libcellml::Units>();
    importedUnits->setName("units_in_this_model");
    importedUnits->setSourceUnits(imp, "a_units_in_that_model");

    m.addUnits(importedUnits);

    libcellml::UnitsPtr importedUnitsMultiplied = std::make_shared<libcellml::Units>();
    importedUnitsMultiplied->setName("multiplied_import");
    importedUnitsMultiplied->addUnit("units_in_this_model", 0.0, 1.0, 5.6);

    m.addUnits(importedUnitsMultiplied);

    libcellml::UnitsPtr importedUnitsPrefixed = std::make_shared<libcellml::Units>();
    importedUnitsPrefixed->setName("prefixed_import");
    importedUnitsPrefixed->addUnit("units_in_this_model", libcellml::Prefix::YOTTA);

    m.addUnits(importedUnitsPrefixed);

    libcellml::UnitsPtr importedUnitsExponented = std::make_shared<libcellml::Units>();
    importedUnitsExponented->setName("exponented_import");
    importedUnitsExponented->addUnit("units_in_this_model", 3.0);

    m.addUnits(importedUnitsExponented);

    libcellml::UnitsPtr importedUnitsAll = std::make_shared<libcellml::Units>();
    importedUnitsAll->setName("all_import");
    importedUnitsAll->addUnit("units_in_this_model", -17, -4.0, -1.3);

    m.addUnits(importedUnitsAll);

    libcellml::Printer printer;
    std::string a = printer.printModel(m);
    EXPECT_EQ(e, a);

    // Parse
    libcellml::Parser parser;
    libcellml::ModelPtr model = parser.parseModel(e);
    a = printer.printModel(model);
    EXPECT_EQ(e, a);

    // check units count
    EXPECT_EQ(5, model->unitsCount());
}


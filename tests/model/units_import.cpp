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

TEST(UnitsImport, basics) {
    const std::string e = "";

    libcellml::ImportPtr imp = std::make_shared<libcellml::Import>();
    imp->setSource("a-model.xml");

    libcellml::UnitsPtr u = std::make_shared<libcellml::Units>();

    EXPECT_EQ(u->getImport(), nullptr);
    EXPECT_EQ(u->getImportReference(), "");

    u->setImport(imp);
    u->setImportReference("bob");

    EXPECT_EQ(u->getImport(), imp);
    EXPECT_EQ(u->getImportReference(), "bob");

    EXPECT_EQ(e, u->serialise(libcellml::FORMAT_XML));
}

TEST(UnitsImport, importValidName) {
    const std::string e =
            "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
            "<model xmlns=\"http://www.cellml.org/cellml/1.2#\">"
               "<import xlink:href=\"some-other-model.xml\" "
                       "xmlns:xlink=\"http://www.w3.org/1999/xlink\">"
                   "<units units_ref=\"a_units_in_that_model\" "
                              "name=\"units_in_this_model\"/>"
               "</import>"
            "</model>";
    libcellml::Model m;
    libcellml::ImportPtr imp = std::make_shared<libcellml::Import>();
    imp->setSource("some-other-model.xml");

    libcellml::UnitsPtr importedUnits = std::make_shared<libcellml::Units>();

    EXPECT_EQ(importedUnits->getImport(), nullptr);

    importedUnits->setName("units_in_this_model");
    importedUnits->setSourceUnits(imp, "a_units_in_that_model");

    EXPECT_EQ(importedUnits->getImport(), imp);

    m.addUnits(importedUnits);

    std::string a = m.serialise(libcellml::FORMAT_XML);

   EXPECT_EQ(e, a);
}

TEST(UnitsImport, importInvalidName) {
    const std::string e =
            "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
            "<model xmlns=\"http://www.cellml.org/cellml/1.2#\">"
               "<import xlink:href=\"some-other-model.xml\" "
                       "xmlns:xlink=\"http://www.w3.org/1999/xlink\">"
                   "<units units_ref=\"a units in that model\" "
                              "name=\"units_in_this_model\"/>"
               "</import>"
            "</model>";
    libcellml::Model m;
    libcellml::ImportPtr imp = std::make_shared<libcellml::Import>();
    imp->setSource("some-other-model.xml");

    libcellml::UnitsPtr importedUnits = std::make_shared<libcellml::Units>();

    EXPECT_EQ(importedUnits->getImport(), nullptr);

    importedUnits->setName("units_in_this_model");
    importedUnits->setSourceUnits(imp, "a units in that model");

    EXPECT_EQ(importedUnits->getImport(), imp);

    m.addUnits(importedUnits);

    std::string a = m.serialise(libcellml::FORMAT_XML);

   EXPECT_EQ(e, a);
}

TEST(UnitsImport, nonExistentURL) {
    const std::string e =
            "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
            "<model xmlns=\"http://www.cellml.org/cellml/1.2#\">"
               "<import xlink:href=\"http://someplace.world/cellml/model.xml\" "
                       "xmlns:xlink=\"http://www.w3.org/1999/xlink\">"
                   "<units units_ref=\"per_mole\" "
                              "name=\"noble_per_mole\"/>"
               "</import>"
            "</model>";
    libcellml::Model m;
    libcellml::ImportPtr imp = std::make_shared<libcellml::Import>();
    imp->setSource("http://someplace.world/cellml/model.xml");

    libcellml::UnitsPtr importedUnits = std::make_shared<libcellml::Units>();

    EXPECT_EQ(importedUnits->getImport(), nullptr);

    importedUnits->setName("noble_per_mole");
    importedUnits->setSourceUnits(imp, "per_mole");

    EXPECT_EQ(importedUnits->getImport(), imp);

    m.addUnits(importedUnits);

    std::string a = m.serialise(libcellml::FORMAT_XML);

   EXPECT_EQ(e, a);
}


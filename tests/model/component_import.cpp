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

/**
 * @todo Need a way to have resources which can be used in tests, such as the
 * source models used in these tests. But I guess not until we start validating
 * models...
 *
 * While this is needed eventually, for now we are not instantiating the imports
 * so don't need it just yet.
 */

TEST(ComponentImport, basics) {
    const std::string e = "";

    libcellml::ImportPtr imp = std::make_shared<libcellml::Import>();
    imp->setSource("a-model.xml");

    libcellml::ComponentPtr c = std::make_shared<libcellml::Component>();

    EXPECT_EQ(c->getImport(), nullptr);
    EXPECT_EQ(c->getImportReference(), "");

    c->setImport(imp);
    c->setImportReference("bob");

    EXPECT_EQ(c->getImport(), imp);
    EXPECT_EQ(c->getImportReference(), "bob");

    EXPECT_EQ(e, c->serialise(libcellml::Format::XML));
}

TEST(ComponentImport, singleImportA) {
    const std::string e =
            "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
            "<model xmlns=\"http://www.cellml.org/cellml/1.2#\">"
               "<import xlink:href=\"some-other-model.xml\" "
                       "xmlns:xlink=\"http://www.w3.org/1999/xlink\">"
                   "<component component_ref=\"a_component_in_that_model\" "
                              "name=\"component_in_this_model\"/>"
               "</import>"
            "</model>";
    libcellml::Model m;
    libcellml::ImportPtr imp = std::make_shared<libcellml::Import>();
    imp->setSource("some-other-model.xml");

    libcellml::ComponentPtr importedComponent = std::make_shared<libcellml::Component>();

    EXPECT_EQ(importedComponent->getImport(), nullptr);

    importedComponent->setName("component_in_this_model");
    importedComponent->setSourceComponent(imp, "a_component_in_that_model");

    EXPECT_EQ(importedComponent->getImport(), imp);

    m.addComponent(importedComponent);

    std::string a = m.serialise(libcellml::Format::XML);

   EXPECT_EQ(e, a);
}

TEST(ComponentImport, singleImportB) {
    const std::string e =
            "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
            "<model xmlns=\"http://www.cellml.org/cellml/1.2#\">"
               "<import xlink:href=\"some-other-model.xml\" "
                       "xmlns:xlink=\"http://www.w3.org/1999/xlink\">"
                   "<component component_ref=\"a_component_in_that_model\" "
                              "name=\"component_in_this_model\"/>"
               "</import>"
            "</model>";
    libcellml::Model m;
    libcellml::ImportPtr imp = std::make_shared<libcellml::Import>();
    imp->setSource("some-other-model.xml");

    libcellml::ComponentPtr importedComponent = std::make_shared<libcellml::Component>();
    importedComponent->setName("component_in_this_model");
    importedComponent->setImport(imp);
    importedComponent->setImportReference("a_component_in_that_model");
    m.addComponent(importedComponent);

    std::string a = m.serialise(libcellml::Format::XML);

    EXPECT_EQ(e, a);
}

TEST(ComponentImport, nonExistentURL) {
    const std::string e =
            "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
            "<model xmlns=\"http://www.cellml.org/cellml/1.2#\">"
               "<import xlink:href=\"http://someplace.world/cellml/model.xml\" "
                       "xmlns:xlink=\"http://www.w3.org/1999/xlink\">"
                   "<component component_ref=\"na_channel\" "
                              "name=\"noble_na_channel\"/>"
               "</import>"
            "</model>";
    libcellml::Model m;
    libcellml::ImportPtr imp = std::make_shared<libcellml::Import>();
    imp->setSource("http://someplace.world/cellml/model.xml");

    libcellml::ComponentPtr importedComponent = std::make_shared<libcellml::Component>();

    EXPECT_EQ(importedComponent->getImport(), nullptr);

    importedComponent->setName("noble_na_channel");
    importedComponent->setSourceComponent(imp, "na_channel");

    EXPECT_EQ(importedComponent->getImport(), imp);

    m.addComponent(importedComponent);

    std::string a = m.serialise(libcellml::Format::XML);

   EXPECT_EQ(e, a);
}

TEST(ComponentImport, multipleImport) {

    const std::string e1 =
            "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
            "<model xmlns=\"http://www.cellml.org/cellml/1.2#\">"
            "<import xlink:href=\"some-other-model.xml\" "
                    "xmlns:xlink=\"http://www.w3.org/1999/xlink\">"
                 "<component component_ref=\"cc1\" "
                            "name=\"c1\"/>"
                 "<component component_ref=\"cc2\" "
                            "name=\"c2\"/>"
            "</import>"
            "<import xlink:href=\"some-other-model.xml\" "
                    "xmlns:xlink=\"http://www.w3.org/1999/xlink\">"
                 "<component component_ref=\"cc1\" "
                            "name=\"c3\"/>"
            "</import>"
            "</model>";
    const std::string e2 =
            "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
            "<model xmlns=\"http://www.cellml.org/cellml/1.2#\">"
            "<import xlink:href=\"some-other-model.xml\" "
                    "xmlns:xlink=\"http://www.w3.org/1999/xlink\">"
                 "<component component_ref=\"cc1\" "
                            "name=\"c3\"/>"
            "</import>"
            "<import xlink:href=\"some-other-model.xml\" "
                    "xmlns:xlink=\"http://www.w3.org/1999/xlink\">"
                 "<component component_ref=\"cc1\" "
                            "name=\"c1\"/>"
                 "<component component_ref=\"cc2\" "
                            "name=\"c2\"/>"
            "</import>"
            "</model>";

    libcellml::Model m;
    libcellml::ImportPtr imp = std::make_shared<libcellml::Import>();
    imp->setSource("some-other-model.xml");
    libcellml::ComponentPtr c1 = std::make_shared<libcellml::Component>();
    c1->setName("c1");
    c1->setSourceComponent(imp, "cc1");
    m.addComponent(c1);
    libcellml::ComponentPtr c2 = std::make_shared<libcellml::Component>();
    c2->setName("c2");
    c2->setSourceComponent(imp, "cc2");
    m.addComponent(c2);

    libcellml::ImportPtr imp2 = std::make_shared<libcellml::Import>();
    imp2->setSource("some-other-model.xml");
    libcellml::ComponentPtr c3 = std::make_shared<libcellml::Component>();
    c3->setName("c3");
    c3->setSourceComponent(imp2, "cc1");
    m.addComponent(c3);

    std::string a = m.serialise(libcellml::Format::XML);

    EXPECT_TRUE((e1 == a) || (e2 == a));
}

TEST(ComponentImport, hierarchicalImport) {

    const std::string e =
            "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
            "<model xmlns=\"http://www.cellml.org/cellml/1.2#\">"
               "<import xlink:href=\"some-other-model.xml\" "
                       "xmlns:xlink=\"http://www.w3.org/1999/xlink\">"
                    "<component component_ref=\"cc1\" "
                               "name=\"c1\"/>"
               "</import>"
               "<component name=\"dave\"/>"
               "<component name=\"bob\"/>"
               "<encapsulation>"
                  "<component_ref component=\"dave\">"
                     "<component_ref component=\"bob\">"
                        "<component_ref component=\"c1\"/>"
                     "</component_ref>"
                  "</component_ref>"
               "</encapsulation>"
            "</model>";
    libcellml::Model m;
    libcellml::ImportPtr imp = std::make_shared<libcellml::Import>();
    imp->setSource("some-other-model.xml");

    libcellml::ComponentPtr dave = std::make_shared<libcellml::Component>();
    dave->setName("dave");
    m.addComponent(dave);

    libcellml::ComponentPtr bob = std::make_shared<libcellml::Component>();
    bob->setName("bob");
    dave->addComponent(bob);

    EXPECT_FALSE(dave->isImport());

    libcellml::ComponentPtr i1 = std::make_shared<libcellml::Component>();
    i1->setName("c1");
    i1->setSourceComponent(imp, "cc1");

    EXPECT_TRUE(i1->isImport());

    bob->addComponent(i1);

    std::string a = m.serialise(libcellml::Format::XML);

    EXPECT_EQ(e, a);
}

TEST(ComponentImport, complexImport) {

    const std::string e =
            "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
            "<model xmlns=\"http://www.cellml.org/cellml/1.2#\">"
               "<import xlink:href=\"some-other-model.xml\" "
                       "xmlns:xlink=\"http://www.w3.org/1999/xlink\">"
                    "<component component_ref=\"cc1\" "
                               "name=\"c1\"/>"
               "</import>"
               "<component name=\"dave\"/>"
               "<component name=\"bob\"/>"
               "<component name=\"angus\"/>"
               "<encapsulation>"
                  "<component_ref component=\"dave\">"
                     "<component_ref component=\"bob\">"
                        "<component_ref component=\"c1\"/>"
                        "<component_ref component=\"angus\"/>"
                     "</component_ref>"
                  "</component_ref>"
               "</encapsulation>"
            "</model>";
    libcellml::Model m;
    libcellml::ImportPtr imp = std::make_shared<libcellml::Import>();
    imp->setSource("some-other-model.xml");

    libcellml::ComponentPtr dave = std::make_shared<libcellml::Component>();
    dave->setName("dave");
    m.addComponent(dave);

    libcellml::ComponentPtr bob = std::make_shared<libcellml::Component>();
    bob->setName("bob");
    dave->addComponent(bob);

    EXPECT_FALSE(dave->isImport());

    libcellml::ComponentPtr i1 = std::make_shared<libcellml::Component>();
    i1->setName("c1");
    i1->setSourceComponent(imp, "cc1");

    EXPECT_TRUE(i1->isImport());

    bob->addComponent(i1);

    libcellml::ComponentPtr angus = std::make_shared<libcellml::Component>();
    angus->setName("angus");
    bob->addComponent(angus);

    std::string a = m.serialise(libcellml::Format::XML);

    EXPECT_EQ(e, a);
}


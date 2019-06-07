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

/**
 * @todo Need a way to have resources which can be used in tests, such as the
 * source models used in these tests. But I guess not until we start validating
 * models...
 *
 * While this is needed eventually, for now we are not instantiating the imports
 * so don't need it just yet.
 */

TEST(ComponentImport, basics)
{
    const std::string e =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/2.0#\">\n"
        "  <import xlink:href=\"a-model.xml\" xmlns:xlink=\"http://www.w3.org/1999/xlink\">\n"
        "    <component component_ref=\"bob\" name=\"\"/>\n"
        "  </import>\n"
        "</model>\n";

    libcellml::Model m;
    libcellml::ImportSourcePtr imp = std::make_shared<libcellml::ImportSource>();
    imp->setUrl("a-model.xml");

    libcellml::ComponentPtr c = std::make_shared<libcellml::Component>();

    EXPECT_EQ(c->getImportSource(), nullptr);
    EXPECT_EQ(c->getImportReference(), "");

    c->setImportSource(imp);
    c->setImportReference("bob");

    EXPECT_EQ(c->getImportSource(), imp);
    EXPECT_EQ(c->getImportReference(), "bob");

    m.addComponent(c);

    libcellml::Printer printer;
    const std::string a = printer.printModel(m);
    EXPECT_EQ(e, a);
}

TEST(ComponentImport, singleImportA)
{
    const std::string e =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/2.0#\">\n"
        "  <import xlink:href=\"some-other-model.xml\" xmlns:xlink=\"http://www.w3.org/1999/xlink\">\n"
        "    <component component_ref=\"a_component_in_that_model\" name=\"component_in_this_model\"/>\n"
        "  </import>\n"
        "</model>\n";

    libcellml::Model m;
    libcellml::ImportSourcePtr imp = std::make_shared<libcellml::ImportSource>();
    imp->setUrl("some-other-model.xml");

    libcellml::ComponentPtr importedComponent = std::make_shared<libcellml::Component>();

    EXPECT_EQ(importedComponent->getImportSource(), nullptr);

    importedComponent->setName("component_in_this_model");
    importedComponent->setSourceComponent(imp, "a_component_in_that_model");

    EXPECT_EQ(importedComponent->getImportSource(), imp);

    EXPECT_EQ(0u, m.componentCount());
    m.addComponent(importedComponent);
    EXPECT_EQ(1u, m.componentCount());

    libcellml::Printer printer;
    const std::string a = printer.printModel(m);
    EXPECT_EQ(e, a);
}

TEST(ComponentImport, singleImportB)
{
    const std::string e =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/2.0#\">\n"
        "  <import xlink:href=\"some-other-model.xml\" xmlns:xlink=\"http://www.w3.org/1999/xlink\">\n"
        "    <component component_ref=\"a_component_in_that_model\" name=\"component_in_this_model\"/>\n"
        "  </import>\n"
        "</model>\n";

    libcellml::Model m;
    libcellml::ImportSourcePtr imp = std::make_shared<libcellml::ImportSource>();
    imp->setUrl("some-other-model.xml");

    libcellml::ComponentPtr importedComponent = std::make_shared<libcellml::Component>();
    importedComponent->setName("component_in_this_model");
    importedComponent->setImportSource(imp);
    importedComponent->setImportReference("a_component_in_that_model");
    m.addComponent(importedComponent);

    libcellml::Printer printer;
    const std::string a = printer.printModel(m);
    EXPECT_EQ(e, a);
}

TEST(ComponentImport, nonExistentURLAndParse)
{
    const std::string e =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/2.0#\">\n"
        "  <import xlink:href=\"http://someplace.world/cellml/model.xml\" xmlns:xlink=\"http://www.w3.org/1999/xlink\">\n"
        "    <component component_ref=\"na_channel\" name=\"noble_na_channel\"/>\n"
        "  </import>\n"
        "</model>\n";

    libcellml::Model m;
    libcellml::ImportSourcePtr imp = std::make_shared<libcellml::ImportSource>();
    imp->setUrl("http://someplace.world/cellml/model.xml");

    libcellml::ComponentPtr importedComponent = std::make_shared<libcellml::Component>();

    EXPECT_EQ(importedComponent->getImportSource(), nullptr);

    importedComponent->setName("noble_na_channel");
    importedComponent->setSourceComponent(imp, "na_channel");

    EXPECT_EQ(importedComponent->getImportSource(), imp);

    EXPECT_EQ(0u, m.componentCount());
    m.addComponent(importedComponent);
    EXPECT_EQ(1u, m.componentCount());

    libcellml::Printer printer;
    std::string a = printer.printModel(m);
    EXPECT_EQ(e, a);

    // Parse
    libcellml::Parser parser;
    libcellml::ModelPtr model = parser.parseModel(e);
    EXPECT_EQ(1u, model->componentCount());
    a = printer.printModel(model);
    EXPECT_EQ(e, a);
}

TEST(ComponentImport, multipleImportAndParse)
{
    const std::string e1 =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/2.0#\">\n"
        "  <import xlink:href=\"some-other-model.xml\" xmlns:xlink=\"http://www.w3.org/1999/xlink\">\n"
        "    <component component_ref=\"cc1\" name=\"c1\"/>\n"
        "    <component component_ref=\"cc2\" name=\"c2\"/>\n"
        "  </import>\n"
        "  <import xlink:href=\"some-other-model.xml\" xmlns:xlink=\"http://www.w3.org/1999/xlink\">\n"
        "    <component component_ref=\"cc1\" name=\"c3\"/>\n"
        "  </import>\n"
        "</model>\n";
    const std::string e2 =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/2.0#\">\n"
        "  <import xlink:href=\"some-other-model.xml\" xmlns:xlink=\"http://www.w3.org/1999/xlink\">\n"
        "    <component component_ref=\"cc1\" name=\"c3\"/>\n"
        "  </import>\n"
        "  <import xlink:href=\"some-other-model.xml\" xmlns:xlink=\"http://www.w3.org/1999/xlink\">\n"
        "    <component component_ref=\"cc1\" name=\"c1\"/>\n"
        "    <component component_ref=\"cc2\" name=\"c2\"/>\n"
        "  </import>\n"
        "</model>\n";

    libcellml::Model m;
    libcellml::ImportSourcePtr imp = std::make_shared<libcellml::ImportSource>();
    imp->setUrl("some-other-model.xml");
    libcellml::ComponentPtr c1 = std::make_shared<libcellml::Component>();
    c1->setName("c1");
    c1->setSourceComponent(imp, "cc1");
    m.addComponent(c1);
    libcellml::ComponentPtr c2 = std::make_shared<libcellml::Component>();
    c2->setName("c2");
    c2->setSourceComponent(imp, "cc2");
    m.addComponent(c2);

    libcellml::ImportSourcePtr imp2 = std::make_shared<libcellml::ImportSource>();
    imp2->setUrl("some-other-model.xml");
    libcellml::ComponentPtr c3 = std::make_shared<libcellml::Component>();
    c3->setName("c3");
    c3->setSourceComponent(imp2, "cc1");
    m.addComponent(c3);

    libcellml::Printer printer;
    std::string a = printer.printModel(m);
    EXPECT_TRUE((e1 == a) || (e2 == a));

    // Parse
    libcellml::Parser parser;
    libcellml::ModelPtr model = parser.parseModel(e2);
    EXPECT_EQ(3u, model->componentCount());
    a = printer.printModel(model);
    EXPECT_TRUE((e1 == a) || (e2 == a));
}

TEST(ComponentImport, hierarchicalImportAndParse)
{
    const std::string e =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/2.0#\">\n"
        "  <import xlink:href=\"some-other-model.xml\" xmlns:xlink=\"http://www.w3.org/1999/xlink\">\n"
        "    <component component_ref=\"cc1\" name=\"c1\"/>\n"
        "  </import>\n"
        "  <component name=\"dave\"/>\n"
        "  <component name=\"bob\"/>\n"
        "  <encapsulation>\n"
        "    <component_ref component=\"dave\">\n"
        "      <component_ref component=\"bob\">\n"
        "        <component_ref component=\"c1\"/>\n"
        "      </component_ref>\n"
        "    </component_ref>\n"
        "  </encapsulation>\n"
        "</model>\n";

    libcellml::Model m;
    libcellml::ImportSourcePtr imp = std::make_shared<libcellml::ImportSource>();
    imp->setUrl("some-other-model.xml");

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

    EXPECT_EQ(0u, bob->componentCount());
    bob->addComponent(i1);
    EXPECT_EQ(1u, bob->componentCount());

    libcellml::Printer printer;
    std::string a = printer.printModel(m);
    EXPECT_EQ(e, a);

    // Parse
    libcellml::Parser parser;
    libcellml::ModelPtr model = parser.parseModel(e);
    EXPECT_EQ(1u, model->componentCount());
    a = printer.printModel(model);
    EXPECT_EQ(e, a);
}

TEST(ComponentImport, complexImportAndParse)
{
    const std::string e =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/2.0#\">\n"
        "  <import xlink:href=\"some-other-model.xml\" xmlns:xlink=\"http://www.w3.org/1999/xlink\">\n"
        "    <component component_ref=\"cc1\" name=\"c1\"/>\n"
        "  </import>\n"
        "  <component name=\"dave\"/>\n"
        "  <component name=\"bob\"/>\n"
        "  <component name=\"angus\"/>\n"
        "  <encapsulation>\n"
        "    <component_ref component=\"dave\">\n"
        "      <component_ref component=\"bob\">\n"
        "        <component_ref component=\"c1\"/>\n"
        "        <component_ref component=\"angus\"/>\n"
        "      </component_ref>\n"
        "    </component_ref>\n"
        "  </encapsulation>\n"
        "</model>\n";

    libcellml::Model m;
    libcellml::ImportSourcePtr imp = std::make_shared<libcellml::ImportSource>();
    imp->setUrl("some-other-model.xml");

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

    libcellml::Printer printer;
    std::string a = printer.printModel(m);
    EXPECT_EQ(e, a);

    // Parse
    libcellml::Parser parser;
    libcellml::ModelPtr model = parser.parseModel(e);
    a = printer.printModel(model);
    EXPECT_EQ(e, a);

    // check component counts
    const libcellml::ComponentPtr constDave = model->getComponent("dave");
    EXPECT_EQ(1u, constDave->componentCount());
    const libcellml::ComponentPtr constBob = constDave->getComponent("bob");
    EXPECT_EQ(2u, constBob->componentCount());
}

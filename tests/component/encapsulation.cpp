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

#include <iostream>

TEST(Encapsulation, reparentComponent)
{
    const std::string e_parent_1 =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/2.0#\">\n"
        "  <component name=\"parent_component\"/>\n"
        "  <component name=\"child1\"/>\n"
        "  <component name=\"child2\"/>\n"
        "  <component name=\"child3\"/>\n"
        "  <encapsulation>\n"
        "    <component_ref component=\"parent_component\">\n"
        "      <component_ref component=\"child1\"/>\n"
        "      <component_ref component=\"child2\"/>\n"
        "      <component_ref component=\"child3\"/>\n"
        "    </component_ref>\n"
        "  </encapsulation>\n"
        "</model>\n";
    const std::string e_parent_2 =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/2.0#\">\n"
        "  <component name=\"parent_component\"/>\n"
        "  <component name=\"child1\"/>\n"
        "  <component name=\"child2\"/>\n"
        "  <component name=\"child3\"/>\n"
        "  <encapsulation>\n"
        "    <component_ref component=\"parent_component\">\n"
        "      <component_ref component=\"child1\"/>\n"
        "      <component_ref component=\"child2\">\n"
        "        <component_ref component=\"child3\"/>\n"
        "      </component_ref>\n"
        "    </component_ref>\n"
        "  </encapsulation>\n"
        "</model>\n";
    const std::string e_re_add =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/2.0#\">\n"
        "  <component name=\"parent_component\"/>\n"
        "  <component name=\"child1\"/>\n"
        "  <component name=\"child2\"/>\n"
        "  <component name=\"child3\"/>\n"
        "  <encapsulation>\n"
        "    <component_ref component=\"parent_component\">\n"
        "      <component_ref component=\"child1\"/>\n"
        "    </component_ref>\n"
        "    <component_ref component=\"child2\">\n"
        "      <component_ref component=\"child3\"/>\n"
        "    </component_ref>\n"
        "  </encapsulation>\n"
        "</model>\n";

    libcellml::ModelPtr model = std::make_shared<libcellml::Model>();
    libcellml::ComponentPtr parent = std::make_shared<libcellml::Component>();
    parent->setName("parent_component");
    libcellml::ComponentPtr child1 = std::make_shared<libcellml::Component>();
    child1->setName("child1");
    libcellml::ComponentPtr child2 = std::make_shared<libcellml::Component>();
    child2->setName("child2");
    libcellml::ComponentPtr child3 = std::make_shared<libcellml::Component>();
    child3->setName("child3");
    parent->addComponent(child1);
    parent->addComponent(child2);
    parent->addComponent(child3);

    model->addComponent(parent);

    libcellml::Printer printer;
    std::string a_parent = printer.printModel(model);
    EXPECT_EQ(e_parent_1, a_parent);

    // 'child3's parent is changed to 'child2'.
    child2->addComponent(child3);

    a_parent = printer.printModel(model);
    EXPECT_EQ(e_parent_2, a_parent);

    // Now we have two components at the bottom of the hierarchy.
    model->addComponent(child2);
    a_parent = printer.printModel(model);
    EXPECT_EQ(e_re_add, a_parent);
}

TEST(Encapsulation, hierarchyWaterfall)
{
    const std::string e_parent =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/2.0#\">\n"
        "  <component name=\"parent_component\"/>\n"
        "  <component name=\"child1\"/>\n"
        "  <component name=\"child2\"/>\n"
        "  <component name=\"child3\"/>\n"
        "  <encapsulation>\n"
        "    <component_ref component=\"parent_component\">\n"
        "      <component_ref component=\"child1\">\n"
        "        <component_ref component=\"child2\">\n"
        "          <component_ref component=\"child3\"/>\n"
        "        </component_ref>\n"
        "      </component_ref>\n"
        "    </component_ref>\n"
        "  </encapsulation>\n"
        "</model>\n";

    libcellml::ModelPtr model = std::make_shared<libcellml::Model>();
    libcellml::ComponentPtr parent = std::make_shared<libcellml::Component>();
    parent->setName("parent_component");
    libcellml::ComponentPtr child1 = std::make_shared<libcellml::Component>();
    child1->setName("child1");
    libcellml::ComponentPtr child2 = std::make_shared<libcellml::Component>();
    child2->setName("child2");
    libcellml::ComponentPtr child3 = std::make_shared<libcellml::Component>();
    child3->setName("child3");

    child2->addComponent(child3);
    child1->addComponent(child2);
    parent->addComponent(child1);

    model->addComponent(parent);

    libcellml::Printer printer;
    const std::string a_parent = printer.printModel(model);
    EXPECT_EQ(e_parent, a_parent);
}

TEST(Encapsulation, hierarchyCircular)
{
    const std::string e_parent_1 =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/2.0#\">\n"
        "  <component name=\"parent_component\"/>\n"
        "  <component name=\"child1\"/>\n"
        "  <encapsulation>\n"
        "    <component_ref component=\"parent_component\">\n"
        "      <component_ref component=\"child1\"/>\n"
        "    </component_ref>\n"
        "  </encapsulation>\n"
        "</model>\n";
    const std::string e_parent_2 =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/2.0#\">\n"
        "  <component name=\"parent_component\"/>\n"
        "  <component name=\"child1\"/>\n"
        "  <component name=\"child2\"/>\n"
        "  <encapsulation>\n"
        "    <component_ref component=\"parent_component\">\n"
        "      <component_ref component=\"child1\">\n"
        "        <component_ref component=\"child2\"/>\n"
        "      </component_ref>\n"
        "    </component_ref>\n"
        "  </encapsulation>\n"
        "</model>\n";

    libcellml::ModelPtr model = std::make_shared<libcellml::Model>();
    libcellml::ComponentPtr parent = std::make_shared<libcellml::Component>();
    parent->setName("parent_component");
    libcellml::ComponentPtr child1 = std::make_shared<libcellml::Component>();
    child1->setName("child1");
    libcellml::ComponentPtr child2 = std::make_shared<libcellml::Component>();
    child2->setName("child2");

    // Standard addition of one component onto another.
    parent->addComponent(child1);
    EXPECT_EQ(size_t(0), child1->componentCount());
    EXPECT_EQ(size_t(1), parent->componentCount());

    // Can't make this circular hierarchy 'parent' will not be added as a child
    // of 'child1'. Everything will remain as it is.
    child1->addComponent(parent);
    EXPECT_EQ(size_t(0), child1->componentCount());
    EXPECT_EQ(size_t(1), parent->componentCount());

    // Add the 'parent' component onto the model to make a
    // waterfall hierarchy of two steps.
    model->addComponent(parent);

    libcellml::Printer printer;
    std::string a_parent = printer.printModel(model);
    EXPECT_EQ(e_parent_1, a_parent);

    // Add 'child2' to 'child1' to make a waterfall hierarchy of
    // three steps.
    child1->addComponent(child2);
    a_parent = printer.printModel(model);
    EXPECT_EQ(e_parent_2, a_parent);

    // Try to make a circular hierarchy but we will not succeed as this is not
    // allowed.  The model will stay as it is.
    child2->addComponent(parent);
    EXPECT_FALSE(parent->hasAncestor(child2));
    a_parent = printer.printModel(model);
    EXPECT_EQ(e_parent_2, a_parent);
}

TEST(Encapsulation, hierarchyWaterfallAndParse)
{
    const std::string e =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/2.0#\">\n"
        "  <component name=\"parent_component\"/>\n"
        "  <component name=\"child1\"/>\n"
        "  <component name=\"child2\"/>\n"
        "  <component name=\"child3\"/>\n"
        "  <encapsulation>\n"
        "    <component_ref component=\"parent_component\">\n"
        "      <component_ref component=\"child1\">\n"
        "        <component_ref component=\"child2\">\n"
        "          <component_ref component=\"child3\"/>\n"
        "        </component_ref>\n"
        "      </component_ref>\n"
        "    </component_ref>\n"
        "  </encapsulation>\n"
        "</model>\n";

    libcellml::ModelPtr model = std::make_shared<libcellml::Model>();
    libcellml::ComponentPtr parent = std::make_shared<libcellml::Component>();
    parent->setName("parent_component");
    libcellml::ComponentPtr child1 = std::make_shared<libcellml::Component>();
    child1->setName("child1");
    libcellml::ComponentPtr child2 = std::make_shared<libcellml::Component>();
    child2->setName("child2");
    libcellml::ComponentPtr child3 = std::make_shared<libcellml::Component>();
    child3->setName("child3");

    child2->addComponent(child3);
    child1->addComponent(child2);
    parent->addComponent(child1);
    model->addComponent(parent);

    libcellml::Printer printer;
    std::string a = printer.printModel(model);
    EXPECT_EQ(e, a);

    libcellml::Parser parser = libcellml::Parser();
    libcellml::ModelPtr parsedModel = parser.parseModel(e);

    a = printer.printModel(parsedModel);
    EXPECT_EQ(e, a);
}

TEST(Encapsulation, parseAlternateFormHierarchy)
{
    const std::string input =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/2.0#\">\n"
        "  <component name=\"parent_component\"/>\n"
        "  <encapsulation>\n"
        "    <component_ref component=\"parent_component\">\n"
        "      <component_ref component=\"child1\">\n"
        "        <component_ref component=\"child2\">\n"
        "          <component_ref component=\"child3\"/>\n"
        "        </component_ref>\n"
        "      </component_ref>\n"
        "    </component_ref>\n"
        "  </encapsulation>\n"
        "  <component name=\"child1\"/>\n"
        "  <component name=\"child2\"/>\n"
        "  <component name=\"child3\"/>\n"
        "</model>\n";

    libcellml::Parser parser = libcellml::Parser();
    libcellml::ModelPtr model = parser.parseModel(input);

    EXPECT_EQ(size_t(0), parser.errorCount());
    printErrors(parser);
    EXPECT_EQ(size_t(1), model->componentCount());
    auto component = model->component(0);
    for (size_t i = 0; i < 3; ++i) {
        EXPECT_EQ(size_t(1), component->componentCount());
        component = component->component(0);
    }
    EXPECT_EQ(size_t(0), component->componentCount());
}

TEST(Encapsulation, encapsulatedComponentMethods)
{
    const std::string e = "<component/>\n";
    libcellml::ComponentPtr c = std::make_shared<libcellml::Component>();
    libcellml::ComponentPtr c1 = std::make_shared<libcellml::Component>();
    libcellml::ComponentPtr c2 = std::make_shared<libcellml::Component>();
    libcellml::ComponentPtr c3 = std::make_shared<libcellml::Component>();
    libcellml::ComponentPtr c4 = std::make_shared<libcellml::Component>();
    libcellml::ComponentPtr c5 = std::make_shared<libcellml::Component>();
    libcellml::ComponentPtr c6 = std::make_shared<libcellml::Component>();
    libcellml::ComponentPtr c4n = std::make_shared<libcellml::Component>();

    c1->setName("comp1");
    c2->setName("comp2");
    c3->setName("comp3");
    c4->setName("comp4");
    c5->setName("comp5");
    c6->setName("comp6");
    c4n->setName("comp4new");

    c->addComponent(c1);
    c1->addComponent(c2);
    c2->addComponent(c3);
    c3->addComponent(c4);
    c4->addComponent(c5);
    c5->addComponent(c6);

    // Contains component
    EXPECT_TRUE(c->containsComponent("comp5"));
    // Get component
    EXPECT_EQ(c4, c->component("comp4"));
    const libcellml::ComponentPtr constC4 = c->component("comp4");
    EXPECT_EQ("comp4", constC4->name());
    EXPECT_FALSE(c->containsComponent("invalid"));
    const libcellml::ComponentPtr &const_c = c;
    EXPECT_EQ(const_c->component("invalid"), nullptr);
    EXPECT_FALSE(c->containsComponent("comp4new"));
    EXPECT_EQ(const_c->component("comp4new"), nullptr);
    // Replace component
    c->replaceComponent("comp4", c4n);
    c4n->addComponent(c5);
    EXPECT_EQ(c4n, c->component("comp4new"));
    // Take component
    libcellml::ComponentPtr c6take = c->takeComponent("comp6");
    EXPECT_EQ(c6, c6take);
    // Remove component
    c->removeComponent("comp5");
    c->removeComponent(c4n);
    EXPECT_FALSE(c->containsComponent("comp5"));
    EXPECT_FALSE(c->containsComponent("comp4new"));
}

TEST(Encapsulation, encapsulationWithMultipleRootHierarchy)
{
    const std::string e =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/2.0#\">\n"
        "  <component name=\"parent1_component\"/>\n"
        "  <component name=\"child11_component\"/>\n"
        "  <component name=\"child12_component\"/>\n"
        "  <component name=\"parent2_component\"/>\n"
        "  <component name=\"child21_component\"/>\n"
        "  <encapsulation>\n"
        "    <component_ref component=\"parent1_component\">\n"
        "      <component_ref component=\"child11_component\"/>\n"
        "      <component_ref component=\"child12_component\"/>\n"
        "    </component_ref>\n"
        "    <component_ref component=\"parent2_component\">\n"
        "      <component_ref component=\"child21_component\"/>\n"
        "    </component_ref>\n"
        "  </encapsulation>\n"
        "</model>\n";
    libcellml::ModelPtr model = std::make_shared<libcellml::Model>();
    libcellml::ComponentPtr parent1 = std::make_shared<libcellml::Component>();
    parent1->setName("parent1_component");
    libcellml::ComponentPtr parent2 = std::make_shared<libcellml::Component>();
    parent2->setName("parent2_component");
    libcellml::ComponentPtr child11 = std::make_shared<libcellml::Component>();
    child11->setName("child11_component");
    libcellml::ComponentPtr child12 = std::make_shared<libcellml::Component>();
    child12->setName("child12_component");
    libcellml::ComponentPtr child21 = std::make_shared<libcellml::Component>();
    child21->setName("child21_component");

    parent1->addComponent(child11);
    parent1->addComponent(child12);
    parent2->addComponent(child21);

    model->addComponent(parent1);
    model->addComponent(parent2);

    libcellml::Printer printer;
    const std::string a = printer.printModel(model);
    EXPECT_EQ(e, a);
}

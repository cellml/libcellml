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

#include "test_utils.h"

TEST(Component, validName)
{
    const std::string in = "valid_name";
    const std::string e = "<component name=\"" + in + "\"/>\n";
    libcellml::ModelPtr m = createModelWithComponent();
    libcellml::ComponentPtr c = m->getComponent(0);
    c->setName(in);

    libcellml::Printer printer;
    const std::string a = printer.printModel(m);
    EXPECT_EQ(e, a);
    EXPECT_EQ("valid_name", c->getName());
}

TEST(Component, invalidName)
{
    const std::string in = "invalid name -";
    const std::string e = "<component name=\"" + in + "\"/>\n";
    libcellml::ModelPtr m = createModelWithComponent();
    libcellml::ComponentPtr c = m->getComponent(0);
    c->setName(in);

    libcellml::Printer printer;
    const std::string a = printer.printModel(m);
    EXPECT_EQ(e, a);
    EXPECT_EQ("invalid name -", c->getName());
}

TEST(Component, setAndUnsetName)
{
    const std::string in = "name";
    const std::string eName = "<component name=\"" + in + "\"/>\n";
    const std::string e = "<component/>\n";
    libcellml::ModelPtr m = createModelWithComponent();
    libcellml::ComponentPtr c = m->getComponent(0);
    c->setName(in);

    libcellml::Printer printer;
    std::string a = printer.printModel(m);
    EXPECT_EQ("name", c->getName());
    EXPECT_EQ(eName, a);
    c->setName("");
    EXPECT_EQ("", c->getName());
    a = printer.printModel(m);
    EXPECT_EQ(e, a);
}

TEST(Component, addAndCountChildren)
{
    libcellml::Component parent;
    parent.setName("parent");
    libcellml::ComponentPtr child1 = std::make_shared<libcellml::Component>();
    child1->setName("child1");
    libcellml::ComponentPtr child2 = std::make_shared<libcellml::Component>();
    child2->setName("child2");
    libcellml::ComponentPtr child3 = std::make_shared<libcellml::Component>();
    child3->setName("child3");
    libcellml::ComponentPtr child4 = std::make_shared<libcellml::Component>();
    child4->setName("child4");

    EXPECT_EQ(0u, parent.componentCount());

    parent.addComponent(child1);
    parent.addComponent(child2);
    parent.addComponent(child3);
    parent.addComponent(child4);
    EXPECT_EQ(4u, parent.componentCount());

    child3->addComponent(child4);
    parent.addComponent(child3);
    EXPECT_EQ(5u, parent.componentCount());

    EXPECT_EQ(1u, child3->componentCount());
}

TEST(Component, contains)
{
    libcellml::Component c;
    libcellml::ComponentPtr c1 = std::make_shared<libcellml::Component>();
    libcellml::ComponentPtr c2 = std::make_shared<libcellml::Component>();
    libcellml::ComponentPtr c21 = std::make_shared<libcellml::Component>();
    c1->setName("child1");
    c2->setName("child2");
    c2->addComponent(c21);

    EXPECT_FALSE(c.containsComponent("child1"));

    c.addComponent(c1);
    c.addComponent(c2);
    EXPECT_TRUE(c.containsComponent(c2));
    EXPECT_TRUE(c.containsComponent(c21));
}

TEST(Component, addChildrenAndSerialise)
{
    const std::string e1 =
        "<component name=\"child0\"/>\n"
        "<component name=\"child1\"/>\n"
        "<component name=\"child2\"/>\n";
    const std::string e2 =
        "<component name=\"child0\"/>\n"
        "<component name=\"child1\"/>\n"
        "<component name=\"child2\"/>\n"
        "<component name=\"child3\"/>\n";
    libcellml::ModelPtr m = createModel();
    libcellml::ComponentPtr c0 = std::make_shared<libcellml::Component>();
    libcellml::ComponentPtr c1 = std::make_shared<libcellml::Component>();
    libcellml::ComponentPtr c2 = std::make_shared<libcellml::Component>();
    libcellml::ComponentPtr c3 = std::make_shared<libcellml::Component>();

    c0->setName("child0");
    c3->setName("child3");

    c1->addComponent(c2);
    c0->addComponent(c1);

    c1->setName("child1");
    c2->setName("child2");

    m->addComponent(c0);

    libcellml::Printer printer;
    std::string a = printer.printModel(m);
    EXPECT_EQ(e1, a);

    c2->addComponent(c3);
    a = printer.printModel(m);
    EXPECT_EQ(e2, a);
}

TEST(Component, removeComponentMethods)
{
    const std::string e1 =
        "<component/>\n"
        "<component name=\"child2\"/>\n";
    const std::string e2 =
        "<component/>\n"
        "<component name=\"child2\"/>\n"
        "<component name=\"child1\"/>\n";
    const std::string e3 = "<component/>\n";
    libcellml::ModelPtr m = createModelWithComponent();
    libcellml::ComponentPtr c = m->getComponent(0);
    libcellml::ComponentPtr c1 = std::make_shared<libcellml::Component>();
    libcellml::ComponentPtr c2 = std::make_shared<libcellml::Component>();
    libcellml::ComponentPtr c3 = std::make_shared<libcellml::Component>();
    c1->setName("child1");
    c2->setName("child2");
    c->addComponent(c1);
    c->addComponent(c2);

    EXPECT_TRUE(c->removeComponent(0));
    EXPECT_EQ(1u, c->componentCount());

    libcellml::Printer printer;
    std::string a = printer.printModel(m);
    EXPECT_EQ(e1, a);
    EXPECT_FALSE(c->removeComponent(1));

    c->addComponent(c1);
    c->addComponent(c1);
    c->addComponent(c1);
    // Remove the first occurence of "child1".
    EXPECT_TRUE(c->removeComponent("child1"));
    // Remove the second occurence of "child1".
    EXPECT_TRUE(c->removeComponent(c1));
    EXPECT_EQ(2u, c->componentCount());
    a = printer.printModel(m);
    EXPECT_EQ(e2, a);

    // Expect no change
    EXPECT_FALSE(c->removeComponent("child3"));
    EXPECT_FALSE(c->removeComponent(c3));
    EXPECT_EQ(2u, c->componentCount());

    c->removeAllComponents();
    a = printer.printModel(m);
    EXPECT_EQ(e3, a);
    EXPECT_EQ(0u, c->componentCount());
}

TEST(Component, getComponentMethods)
{
    const std::string e1 =
        "<component/>\n"
        "<component name=\"childA\"/>\n";
    const std::string e2 =
        "<component name=\"parent\"/>\n"
        "<component name=\"gus\"/>\n"
        "<component name=\"childB\"/>\n"
        "<component name=\"child3\"/>\n"
        "<component name=\"gus\"/>\n"
        "<component name=\"childB\"/>\n"
        "<component name=\"child3\"/>\n";
    ;
    libcellml::ModelPtr m = createModelWithComponent();
    libcellml::ComponentPtr c = m->getComponent(0);
    libcellml::ComponentPtr c1 = std::make_shared<libcellml::Component>();
    libcellml::ComponentPtr c2 = std::make_shared<libcellml::Component>();
    libcellml::ComponentPtr c3 = std::make_shared<libcellml::Component>();
    c1->setName("child1");
    c2->setName("child2");
    c3->setName("child3");
    c->addComponent(c1);

    libcellml::ComponentPtr cA = c->getComponent(0);
    cA->setName("childA");

    libcellml::Printer printer;
    std::string a = printer.printModel(m);
    EXPECT_EQ(e1, a);

    // Using const version of overloaded method
    const libcellml::ComponentPtr cS = static_cast<const libcellml::ComponentPtr>(c)->getComponent(0);
    // Can do this as we just have a const pointer
    cS->setName("gus");
    EXPECT_EQ("gus", cS->getName());
    EXPECT_EQ(nullptr, c->getComponent(4));

    libcellml::ComponentPtr cAr = c->getComponent("gus");
    EXPECT_EQ("gus", cAr->getName());

    // Modify a deeper Component
    c->setName("parent");
    c->addComponent(c1);
    c1->addComponent(c2);
    c1->addComponent(c3);

    libcellml::ComponentPtr cB = c->getComponent(1);
    libcellml::ComponentPtr cBB = cB->getComponent(0);
    cBB->setName("childB");

    EXPECT_EQ(nullptr, c->getComponent(3));

    libcellml::ComponentPtr cSn = static_cast<const libcellml::ComponentPtr>(c)->getComponent("gus");
    EXPECT_EQ("gus", cSn->getName());

    a = printer.printModel(m);
    EXPECT_EQ(e2, a);
}

TEST(Component, takeComponentMethods)
{
    const std::string e = "<component/>\n";
    libcellml::ModelPtr m = createModelWithComponent();
    libcellml::ComponentPtr c = m->getComponent(0);
    libcellml::ComponentPtr c1 = std::make_shared<libcellml::Component>();
    libcellml::ComponentPtr c2 = std::make_shared<libcellml::Component>();
    c1->setName("child1");
    c2->setName("child2");
    c->addComponent(c1);
    c->addComponent(c2);

    libcellml::ComponentPtr c02 = c->takeComponent(1);
    EXPECT_EQ(1u, c->componentCount());

    EXPECT_EQ(c->takeComponent(4), nullptr);

    EXPECT_EQ("child2", c02->getName());

    libcellml::ComponentPtr c01 = c->takeComponent("child1");
    EXPECT_EQ(0u, c->componentCount());

    EXPECT_EQ("child1", c01->getName());

    libcellml::Printer printer;
    const std::string a = printer.printModel(m);
    EXPECT_EQ(e, a);
}

TEST(Component, replaceComponentMethods)
{
    const std::string e_orig =
        "<component name=\"parent\"/>\n"
        "<component/>\n"
        "<component name=\"child2\"/>\n";
    const std::string e_after =
        "<component name=\"parent\"/>\n"
        "<component/>\n"
        "<component name=\"child3\"/>\n";
    const std::string e_post =
        "<component name=\"parent\"/>\n"
        "<component name=\"child4\"/>\n"
        "<component name=\"child3\"/>\n";

    libcellml::ModelPtr m = createModelWithComponent();
    libcellml::ComponentPtr c = m->getComponent(0);
    libcellml::ComponentPtr c1 = std::make_shared<libcellml::Component>();
    libcellml::ComponentPtr c2 = std::make_shared<libcellml::Component>();
    libcellml::ComponentPtr c3 = std::make_shared<libcellml::Component>();
    libcellml::ComponentPtr c4 = std::make_shared<libcellml::Component>();
    c->setName("parent");
    // c1.setName();
    c2->setName("child2");
    c3->setName("child3");
    c4->setName("child4");
    c->addComponent(c1);
    c->addComponent(c2);

    // Test replace by index
    libcellml::Printer printer;
    std::string a = printer.printModel(m);
    EXPECT_EQ(e_orig, a);
    EXPECT_FALSE(c->replaceComponent(5, c3));

    EXPECT_TRUE(c->replaceComponent(1, c3));

    a = printer.printModel(m);
    EXPECT_EQ(e_after, a);

    // Test replace by name
    // Try to replace non-existent child.
    EXPECT_FALSE(c->replaceComponent("child5", c4));

    EXPECT_TRUE(c->replaceComponent("", c4));

    a = printer.printModel(m);
    EXPECT_EQ(e_post, a);

    // Test replace by ptr
    EXPECT_FALSE(c->replaceComponent(c1, c2));
    EXPECT_TRUE(c->replaceComponent(c4, c1));
    a = printer.printModel(m);
    EXPECT_EQ(e_after, a);
}

TEST(Component, constructors)
{
    const std::string e =
        "<component name=\"my_name\"/>\n"
        "<component/>\n";
    const std::string n = "my_name";
    libcellml::ModelPtr m = createModelWithComponent();
    libcellml::ComponentPtr c = m->getComponent(0);
    libcellml::ComponentPtr c1, c2;

    c->setName(n);
    c->addComponent(std::make_shared<libcellml::Component>());

    libcellml::Printer printer;
    const std::string a = printer.printModel(m);
    EXPECT_EQ(e, a);

    // Testing assignment for component
    c1 = c;
    EXPECT_EQ("my_name", c1->getName());

    // Testing move assignment for component
    c2 = std::move(c1);
    EXPECT_EQ("my_name", c2->getName());
    // c1 is now in a valid but undefined state. For us this means we cannot use it, the pointer to implementation
    // is now a nullptr and anything that tries to dereference it will segfault, like getName().
    // EXPECT_EQ("", c1.getName());

    // Testing move constructor for component
    libcellml::ComponentPtr c3 = std::move(c2);
    EXPECT_EQ("my_name", c3->getName());
}

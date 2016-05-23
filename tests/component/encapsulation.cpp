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

#include <iostream>
TEST(Encapsulation, serialise) {
    libcellml::Component parent;
    libcellml::ComponentPtr child = std::make_shared<libcellml::Component>();
    parent.addComponent(child);
    const std::string e_parent = "<component/><component/><encapsulation><component_ref><component_ref/></component_ref></encapsulation>";
    std::string a_parent = parent.serialise(libcellml::Format::XML);
    EXPECT_EQ(e_parent, a_parent);
    const std::string e_child = "<component/>";
    std::string a_child = child->serialise(libcellml::Format::XML);
    EXPECT_EQ(e_child, a_child);
}

TEST(Encapsulation, serialiseWithNames) {
    libcellml::Component parent;
    parent.setName("parent_component");
    libcellml::ComponentPtr child = std::make_shared<libcellml::Component>();
    child->setName("child_component");
    parent.addComponent(child);
    const std::string e_parent = "<component name=\"parent_component\"/><component name=\"child_component\"/><encapsulation><component_ref component=\"parent_component\"><component_ref component=\"child_component\"/></component_ref></encapsulation>";
    std::string a_parent = parent.serialise(libcellml::Format::XML);
    EXPECT_EQ(e_parent, a_parent);
    const std::string e_child= "<component name=\"child_component\"/>";
    std::string a_child = child->serialise(libcellml::Format::XML);
    EXPECT_EQ(e_child, a_child);
}

TEST(Encapsulation, reparentComponent) {
    const std::string e_parent_1 = "<component name=\"parent_component\"/><component name=\"child1\"/><component name=\"child2\"/><component name=\"child3\"/><encapsulation><component_ref component=\"parent_component\"><component_ref component=\"child1\"/><component_ref component=\"child2\"/><component_ref component=\"child3\"/></component_ref></encapsulation>";
    const std::string e_parent_2 = "<component name=\"parent_component\"/><component name=\"child1\"/><component name=\"child2\"/><component name=\"child3\"/><component name=\"child3\"/><encapsulation><component_ref component=\"parent_component\"><component_ref component=\"child1\"/><component_ref component=\"child2\"><component_ref component=\"child3\"/></component_ref><component_ref component=\"child3\"/></component_ref></encapsulation>";

    libcellml::Component parent;
    parent.setName("parent_component");
    libcellml::ComponentPtr child1 = std::make_shared<libcellml::Component>();
    child1->setName("child1");
    libcellml::ComponentPtr child2 = std::make_shared<libcellml::Component>();
    child2->setName("child2");
    libcellml::ComponentPtr child3 = std::make_shared<libcellml::Component>();
    child3->setName("child3");
    parent.addComponent(child1);
    parent.addComponent(child2);
    parent.addComponent(child3);
    std::string a_parent = parent.serialise(libcellml::Format::XML);
    EXPECT_EQ(e_parent_1, a_parent);

    // what do we expect this to achieve? The addition of child3 to child2
    child2->addComponent(child3);

    a_parent = parent.serialise(libcellml::Format::XML);
    EXPECT_EQ(e_parent_2, a_parent);

    // Now we have two 'child2's and three 'child3's with a hierarchical encapsulation
    parent.addComponent(child2);
    a_parent = parent.serialise(libcellml::Format::XML);
    const std::string e_re_add = "<component name=\"parent_component\"/><component name=\"child1\"/><component name=\"child2\"/><component name=\"child3\"/><component name=\"child3\"/><component name=\"child2\"/><component name=\"child3\"/><encapsulation><component_ref component=\"parent_component\"><component_ref component=\"child1\"/><component_ref component=\"child2\"><component_ref component=\"child3\"/></component_ref><component_ref component=\"child3\"/><component_ref component=\"child2\"><component_ref component=\"child3\"/></component_ref></component_ref></encapsulation>";
    EXPECT_EQ(e_re_add, a_parent);

    // option 2: add child3 as a child of child2 and remove it as a child of parent_component
    // Not really an option is it a bit side-effecty

    // other options?
}

TEST(Encapsulation, hierarchyWaterfall) {

    libcellml::Component parent;
    parent.setName("parent_component");
    libcellml::ComponentPtr child1 = std::make_shared<libcellml::Component>();
    child1->setName("child1");
    libcellml::ComponentPtr child2 = std::make_shared<libcellml::Component>();
    child2->setName("child2");
    libcellml::ComponentPtr child3 = std::make_shared<libcellml::Component>();
    child3->setName("child3");

    child2->addComponent(child3);
    child1->addComponent(child2);
    parent.addComponent(child1);
    const std::string e_parent = "<component name=\"parent_component\"/><component name=\"child1\"/><component name=\"child2\"/><component name=\"child3\"/><encapsulation><component_ref component=\"parent_component\"><component_ref component=\"child1\"><component_ref component=\"child2\"><component_ref component=\"child3\"/></component_ref></component_ref></component_ref></encapsulation>";
    std::string a_parent = parent.serialise(libcellml::Format::XML);
    EXPECT_EQ(e_parent, a_parent);
}

TEST(Encapsulation, hierarchyCircular) {
    const std::string e_parent_1 = "<component name=\"parent_component\"/><component name=\"child1\"/><encapsulation><component_ref component=\"parent_component\"><component_ref component=\"child1\"/></component_ref></encapsulation>";
    const std::string e_parent_2 = "<component name=\"parent_component\"/><component name=\"child1\"/><component name=\"child2\"/><encapsulation><component_ref component=\"parent_component\"><component_ref component=\"child1\"><component_ref component=\"child2\"/></component_ref></component_ref></encapsulation>";

    libcellml::ComponentPtr parent = std::make_shared<libcellml::Component>();
    parent->setName("parent_component");
    libcellml::ComponentPtr child1 = std::make_shared<libcellml::Component>();
    child1->setName("child1");
    libcellml::ComponentPtr child2 = std::make_shared<libcellml::Component>();
    child2->setName("child2");

    parent->addComponent(child1);
    child1->addComponent(parent);
    std::string a_parent = parent->serialise(libcellml::Format::XML);
    EXPECT_EQ(e_parent_1, a_parent);

    child1->addComponent(child2);
    a_parent = parent->serialise(libcellml::Format::XML);
    EXPECT_EQ(e_parent_2, a_parent);

    child2->addComponent(parent);
    a_parent = parent->serialise(libcellml::Format::XML);
    EXPECT_EQ(e_parent_2, a_parent);
}

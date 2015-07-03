#include "gtest/gtest.h"

#include <libcellml>

#include <iostream>
TEST(Encapsulation, serialise) {
    libcellml::Component parent;
    libcellml::Component child;
    parent.addComponent(child);
    const std::string e_parent = "<component/><component/><encapsulation><component_ref><component_ref/></component_ref></encapsulation>";
    std::string a_parent = parent.serialise(libcellml::CELLML_FORMAT_XML);
    EXPECT_EQ(e_parent, a_parent);
    const std::string e_child = "<component/>";
    std::string a_child = child.serialise(libcellml::CELLML_FORMAT_XML);
    EXPECT_EQ(e_child, a_child);
}

TEST(Encapsulation, serialise_with_names) {
    libcellml::Component parent;
    parent.setName("parent_component");
    libcellml::Component child;
    child.setName("child_component");
    parent.addComponent(child);
    const std::string e_parent = "<component name=\"parent_component\"/><component name=\"child_component\"/><encapsulation><component_ref component=\"parent_component\"><component_ref component=\"child_component\"/></component_ref></encapsulation>";
    std::string a_parent = parent.serialise(libcellml::CELLML_FORMAT_XML);
    EXPECT_EQ(e_parent, a_parent);
    const std::string e_child= "<component name=\"child_component\"/>";
    std::string a_child = child.serialise(libcellml::CELLML_FORMAT_XML);
    EXPECT_EQ(e_child, a_child);
}

TEST(Encapsulation, reparent_component) {
    libcellml::Component parent;
    parent.setName("parent_component");
    libcellml::Component child1;
    child1.setName("child1");
    libcellml::Component child2;
    child2.setName("child2");
    libcellml::Component child3;
    child3.setName("child3");
    parent.addComponent(child1);
    parent.addComponent(child2);
    parent.addComponent(child3);
    const std::string e_parent = "<component name=\"parent_component\"/><component name=\"child1\"/><component name=\"child2\"/><component name=\"child3\"/><encapsulation><component_ref component=\"parent_component\"><component_ref component=\"child1\"/><component_ref component=\"child2\"/><component_ref component=\"child3\"/></component_ref></encapsulation>";
    std::string a_parent = parent.serialise(libcellml::CELLML_FORMAT_XML);
    EXPECT_EQ(e_parent, a_parent);

    // what do we expect this to achieve? Nothing, since we don't add this state of 'child2' to anything?
    child2.addComponent(child3);

    a_parent = parent.serialise(libcellml::CELLML_FORMAT_XML);
    EXPECT_EQ(e_parent, a_parent);

    // Now we have two 'child2's and two 'child3's with a hierarchical encapsulation
    parent.addComponent(child2);
    a_parent = parent.serialise(libcellml::CELLML_FORMAT_XML);
    const std::string e_re_add = "<component name=\"parent_component\"/><component name=\"child1\"/><component name=\"child2\"/><component name=\"child3\"/><component name=\"child2\"/><component name=\"child3\"/><encapsulation><component_ref component=\"parent_component\"><component_ref component=\"child1\"/><component_ref component=\"child2\"/><component_ref component=\"child3\"/><component_ref component=\"child2\"><component_ref component=\"child3\"/></component_ref></component_ref></encapsulation>";
    EXPECT_EQ(e_re_add, a_parent);

    // option 2: add child3 as a child of child2 and remove it as a child of parent_component
    // Not really an option is it a bit side-effecty

    // other options?
}

TEST(Encapsulation, hierarchy_waterfall) {

    libcellml::Component parent;
    parent.setName("parent_component");
    libcellml::Component child1;
    child1.setName("child1");
    libcellml::Component child2;
    child2.setName("child2");
    libcellml::Component child3;
    child3.setName("child3");

    child2.addComponent(child3);
    child1.addComponent(child2);
    parent.addComponent(child1);
    const std::string e_parent = "<component name=\"parent_component\"/><component name=\"child1\"/><component name=\"child2\"/><component name=\"child3\"/><encapsulation><component_ref component=\"parent_component\"><component_ref component=\"child1\"><component_ref component=\"child2\"><component_ref component=\"child3\"/></component_ref></component_ref></component_ref></encapsulation>";
    std::string a_parent = parent.serialise(libcellml::CELLML_FORMAT_XML);
    EXPECT_EQ(e_parent, a_parent);
}

TEST(Encapsulation, hierarchy_circular) {

    libcellml::Component parent;
    parent.setName("parent_component");
    libcellml::Component child1;
    child1.setName("child1");

    child1.addComponent(parent);
    parent.addComponent(child1);
    const std::string e_parent = "<component name=\"parent_component\"/><component name=\"child1\"/><component name=\"parent_component\"/><encapsulation><component_ref component=\"parent_component\"><component_ref component=\"child1\"><component_ref component=\"parent_component\"/></component_ref></component_ref></encapsulation>";
    std::string a_parent = parent.serialise(libcellml::CELLML_FORMAT_XML);
    EXPECT_EQ(e_parent, a_parent);
}

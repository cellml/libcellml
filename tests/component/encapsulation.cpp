#include "gtest/gtest.h"

#include <libcellml>


TEST(Encapsulation, serialise) {
    libcellml::Component parent = libcellml::Component();
    libcellml::Component child = libcellml::Component();
    parent.addComponent(child);
    const std::string e_parent = "<component/><component/><encapsulation><component_ref><component_ref/></component_ref></encapsulation>";
    std::string a_parent = parent.serialise(libcellml::CELLML_FORMAT_XML);
    EXPECT_EQ(e_parent, a_parent);
    const std::string e_child= "<component/>";
    std::string a_child = child.serialise(libcellml::CELLML_FORMAT_XML);
    EXPECT_EQ(e_child, a_child);
}

TEST(Encapsulation, serialise_with_names) {
    libcellml::Component parent = libcellml::Component();
    parent.setName("parent_component");
    libcellml::Component child = libcellml::Component();
    parent.addComponent(child);
    child.setName("child_component");
    const std::string e_parent = "<component name=\"parent_component\"/><component name=\"child_component\"/><encapsulation><component_ref component=\"parent_component\"><component_ref component=\"child_component\"/></component_ref></encapsulation>";
    std::string a_parent = parent.serialise(libcellml::CELLML_FORMAT_XML);
    EXPECT_EQ(e_parent, a_parent);
    const std::string e_child= "<component name=\"child_component\"/>";
    std::string a_child = child.serialise(libcellml::CELLML_FORMAT_XML);
    EXPECT_EQ(e_child, a_child);
}

TEST(Encapsulation, reparent_component) {
    auto parent = libcellml::Component();
    parent.setName("parent_component");
    auto child1 = libcellml::Component();
    child1.setName("child2");
    auto child2 = libcellml::Component();
    child2.setName("child2");
    auto child3 = libcellml::Component();
    child3.setName("child3");
    parent.addComponent(child1);
    parent.addComponent(child2);
    parent.addComponent(child3);
    const std::string e_parent = "<component name=\"parent_component\"/><component name=\"child1\"/><component name=\"child2\"/><component name=\"child3\"/><encapsulation><component_ref component=\"parent_component\"><component_ref component=\"child1\"/><component_ref component=\"child2\"/><component_ref component=\"child3\"/></component_ref></encapsulation>";
    std::string a_parent = parent.serialise(libcellml::CELLML_FORMAT_XML);
    EXPECT_EQ(e_parent, a_parent);

    // what do we expect this to achieve?
    child2.addComponent(child3);

    // option 1: add child3 as a child of child2 and leave child3 as also a child of parent_component
    const std::string e_reparent_option1 = "<component name=\"parent_component\"/><component name=\"child1\"/><component name=\"child2\"/><component name=\"child3\"/><encapsulation><component_ref component=\"parent_component\"><component_ref component=\"child1\"/><component_ref component=\"child2\"><component_ref component=\"child3\"/></component_ref><component_ref component=\"child3\"/></component_ref></encapsulation>";
    a_parent = parent.serialise(libcellml::CELLML_FORMAT_XML);
    EXPECT_EQ(e_reparent_option1, a_parent);

    // option 2: add child3 as a child of child2 and remove it as a child of parent_component
    const std::string e_reparent_option2 = "<component name=\"parent_component\"/><component name=\"child1\"/><component name=\"child2\"/><component name=\"child3\"/><encapsulation><component_ref component=\"parent_component\"><component_ref component=\"child1\"/><component_ref component=\"child2\"><component_ref component=\"child3\"/></component_ref></component_ref></encapsulation>";
    a_parent = parent.serialise(libcellml::CELLML_FORMAT_XML);
    EXPECT_EQ(e_reparent_option2, a_parent);

    // other options?
}


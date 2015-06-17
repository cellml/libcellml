#include "gtest/gtest.h"

#include <libcellml>


TEST(Encapsulation, serialise) {
    libcellml::Component parent = libcellml::Component();
    libcellml::Component child = libcellml::Component();
    parent.addComponent(child);
    const std::string e_parent = "<component/><component/><encapsulation><component_ref><component_ref/></component_ref>";
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
    const std::string e_parent = "<component name=\"parent_component\"/><component name=\"child_component\"/><encapsulation><component_ref component=\"parent_component\"><component_ref component=\"child_component\"/></component_ref>";
    std::string a_parent = parent.serialise(libcellml::CELLML_FORMAT_XML);
    EXPECT_EQ(e_parent, a_parent);
    const std::string e_child= "<component name=\"child_component\"/>";
    std::string a_child = child.serialise(libcellml::CELLML_FORMAT_XML);
    EXPECT_EQ(e_child, a_child);
}


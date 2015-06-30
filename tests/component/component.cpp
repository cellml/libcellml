#include "gtest/gtest.h"

#include <libcellml>


TEST(Component, serialise) {
    const std::string e = "<component/>";
    libcellml::Component c;
    std::string a = c.serialise(libcellml::CELLML_FORMAT_XML);
    EXPECT_EQ(e, a);
}

TEST(Component, valid_name) {
    const std::string in = "valid_name";
    const std::string e = "<component name=\"" + in + "\"/>";
    libcellml::Component c;
    c.setName(in);
    std::string a = c.serialise(libcellml::CELLML_FORMAT_XML);
    EXPECT_EQ(e, a);
    EXPECT_EQ("valid_name", c.getName());
}

TEST(Component, invalid_name) {
    const std::string in = "invalid name -";
    const std::string e = "<component name=\"" + in + "\"/>";
    libcellml::Component c;
    c.setName(in);
    std::string a = c.serialise(libcellml::CELLML_FORMAT_XML);
    EXPECT_EQ(e, a);
    EXPECT_EQ("invalid name -", c.getName());
}

TEST(Component, unset_name) {
    const std::string in = "name";
    const std::string eName = "<component name=\"" + in + "\"/>";
    const std::string e = "<component/>";
    libcellml::Component c;
    c.setName(in);
    std::string a = c.serialise(libcellml::CELLML_FORMAT_XML);
    EXPECT_EQ("name", c.getName());
    EXPECT_EQ(eName, a);
    c.setName("");
    EXPECT_EQ("", c.getName());
    a = c.serialise(libcellml::CELLML_FORMAT_XML);
    EXPECT_EQ(e, a);
}

libcellml::Component RetByValue()
{
    libcellml::Component c;
    c.setName("returned_by_value");
    return c;
}

TEST(Component, constructors) {
    const std::string n = "my_name";
    libcellml::Component c, c1, c2;
    c.setName(n);
    c.addComponent(libcellml::Component());
    std::string a = c.serialise(libcellml::CELLML_FORMAT_XML);

    const std::string e = "<component name=\"my_name\"/><component/><encapsulation><component_ref component=\"my_name\"><component_ref/></component_ref></encapsulation>";
    EXPECT_EQ(e, a);

    c1 = c;
    EXPECT_EQ("my_name", c1.getName());

    // Testing move assignment for component
    c2 = std::move(c1);
    EXPECT_EQ("my_name", c2.getName());
    EXPECT_EQ("", c1.getName());

    // Testing move constructor for component
    libcellml::Component c3 = std::move(c2);
    EXPECT_EQ("my_name", c3.getName());
    EXPECT_EQ("", c2.getName());

}


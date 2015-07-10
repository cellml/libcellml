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

TEST(Component, count) {
    libcellml::Component parent;
    parent.setName("parent");
    libcellml::Component child1;
    child1.setName("child1");
    libcellml::Component child2;
    child2.setName("child2");
    libcellml::Component child3;
    child3.setName("child3");
    libcellml::Component child4;
    child4.setName("child4");

    EXPECT_EQ(0, parent.componentCount());

    parent.addComponent(child1);
    parent.addComponent(child2);
    parent.addComponent(child3);
    parent.addComponent(child4);
    EXPECT_EQ(4, parent.componentCount());

    child3.addComponent(child4);
    parent.addComponent(child3);
    EXPECT_EQ(5, parent.componentCount());

    EXPECT_EQ(1, child3.componentCount());
}

TEST(Component, contains) {
    libcellml::Component c;
    libcellml::Component c1, c2;
    c1.setName("child1");
    c2.setName("child2");

    EXPECT_FALSE(c.containsComponent("child1"));

    c.addComponent(c1);
    c.addComponent(c2);
    EXPECT_TRUE(c.containsComponent("child2"));
}

TEST(Component, remove) {
    const std::string e1 = "<component/><component name=\"child2\"/><encapsulation><component_ref><component_ref component=\"child2\"/></component_ref></encapsulation>";
    const std::string e2 = "<component/><component name=\"child2\"/><component name=\"child1\"/><encapsulation><component_ref><component_ref component=\"child2\"/><component_ref component=\"child1\"/></component_ref></encapsulation>";
    libcellml::Component c;
    libcellml::Component c1, c2;
    c1.setName("child1");
    c2.setName("child2");
    c.addComponent(c1);
    c.addComponent(c2);

    c.removeComponent(0);
    EXPECT_EQ(1, c.componentCount());
    std::string a = c.serialise(libcellml::CELLML_FORMAT_XML);
    EXPECT_EQ(e1, a);
    EXPECT_THROW(c.removeComponent(1), std::out_of_range);

    c.addComponent(c1);
    c.addComponent(c1);
    // Remove the first occurence of "child1".
    c.removeComponent("child1");
    EXPECT_EQ(2, c.componentCount());
    a = c.serialise(libcellml::CELLML_FORMAT_XML);
    EXPECT_EQ(e2, a);
    EXPECT_THROW(c.removeComponent("child3"), std::out_of_range);
}

TEST(Component, getcomponent) {
    const std::string e1 = "<component/><component name=\"childA\"/><encapsulation><component_ref><component_ref component=\"childA\"/></component_ref></encapsulation>";
    const std::string e2 = "<component name=\"parent\"/><component name=\"childA\"/><component name=\"child1\"/><component name=\"childB\"/><component name=\"child3\"/><encapsulation><component_ref component=\"parent\"><component_ref component=\"childA\"/><component_ref component=\"child1\"><component_ref component=\"childB\"/><component_ref component=\"child3\"/></component_ref></component_ref></encapsulation>";
    libcellml::Component c;
    libcellml::Component c1, c2, c3;
    c1.setName("child1");
    c2.setName("child2");
    c3.setName("child3");
    c.addComponent(c1);

    libcellml::Component& cA = c.getComponent(0);
    cA.setName("childA");

    std::string a = c.serialise(libcellml::CELLML_FORMAT_XML);
    EXPECT_EQ(e1, a);

    // Using const version of overloaded method
    libcellml::Component cS = static_cast<const libcellml::Component>(c).getComponent(0);
    // Can't do this as I have said it is a const reference
    // cB.setName("gus");
    EXPECT_EQ("childA", cS.getName());

    EXPECT_THROW(c.getComponent(4), std::out_of_range);

    // Modify a deeper Component
    c.setName("parent");
    c1.addComponent(c2);
    c1.addComponent(c3);
    c.addComponent(c1);

    libcellml::Component& cB = c.getComponent(1);
    libcellml::Component& cBB = cB.getComponent(0);
    cBB.setName("childB");

    a = c.serialise(libcellml::CELLML_FORMAT_XML);
    EXPECT_EQ(e2, a);
}

TEST(Component, take) {
    const std::string e = "<component/>";
    libcellml::Component c;
    libcellml::Component c1, c2;
    c1.setName("child1");
    c2.setName("child2");
    c.addComponent(c1);
    c.addComponent(c2);

    libcellml::Component c02 = c.takeComponent(1);
    EXPECT_EQ(1, c.componentCount());

    EXPECT_THROW(c.takeComponent(4), std::out_of_range);

    EXPECT_EQ("child2", c02.getName());

    libcellml::Component c01 = c.takeComponent("child1");
    EXPECT_EQ(0, c.componentCount());

    EXPECT_EQ("child1", c01.getName());
    std::string a = c.serialise(libcellml::CELLML_FORMAT_XML);
    EXPECT_EQ(e, a);

    EXPECT_THROW(c.takeComponent("child4"), std::out_of_range);
}

TEST(Component, replace) {
    const std::string e_orig = "<component name=\"parent\"/><component/><component name=\"child2\"/><encapsulation><component_ref component=\"parent\"><component_ref/><component_ref component=\"child2\"/></component_ref></encapsulation>";
    const std::string e_after = "<component name=\"parent\"/><component/><component name=\"child3\"/><encapsulation><component_ref component=\"parent\"><component_ref/><component_ref component=\"child3\"/></component_ref></encapsulation>";
    const std::string e_post = "<component name=\"parent\"/><component name=\"child4\"/><component name=\"child3\"/><encapsulation><component_ref component=\"parent\"><component_ref component=\"child4\"/><component_ref component=\"child3\"/></component_ref></encapsulation>";

    libcellml::Component c;
    libcellml::Component c1, c2, c3, c4;
    c.setName("parent");
//    c1.setName();
    c2.setName("child2");
    c3.setName("child3");
    c4.setName("child4");
    c.addComponent(c1);
    c.addComponent(c2);

    std::string a = c.serialise(libcellml::CELLML_FORMAT_XML);
    EXPECT_EQ(e_orig, a);
    EXPECT_THROW(c.replaceComponent(5, c3), std::out_of_range);

    c.replaceComponent(1, c3);

    a = c.serialise(libcellml::CELLML_FORMAT_XML);
    EXPECT_EQ(e_after, a);

    EXPECT_THROW(c.replaceComponent("child5", c4), std::out_of_range);

    c.replaceComponent("", c4);

    a = c.serialise(libcellml::CELLML_FORMAT_XML);
    EXPECT_EQ(e_post, a);
}

TEST(Component, constructors) {
    const std::string n = "my_name";
    libcellml::Component c, c1, c2;
    c.setName(n);
    c.addComponent(libcellml::Component());
    std::string a = c.serialise(libcellml::CELLML_FORMAT_XML);

    const std::string e = "<component name=\"my_name\"/><component/><encapsulation><component_ref component=\"my_name\"><component_ref/></component_ref></encapsulation>";
    EXPECT_EQ(e, a);

    // Testing assignment for component
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


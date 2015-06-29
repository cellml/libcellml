#include "gtest/gtest.h"

#include <libcellml>


TEST(Model, serialise) {
    const std::string e = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n<model xmlns=\"http://www.cellml.org/cellml/1.2#\"></model>";
    libcellml::Model m;
    std::string a = m.serialise(libcellml::CELLML_FORMAT_XML);

   EXPECT_EQ(e, a);
}

TEST(Model, serialise_p) {
    const std::string e = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n<model xmlns=\"http://www.cellml.org/cellml/1.2#\"></model>";
    libcellml::Model* m = new libcellml::Model();
    std::string a = m->serialise(libcellml::CELLML_FORMAT_XML);

   EXPECT_EQ(e, a);
   delete m;
}

TEST(Model, name) {
    std::string n = "name";
    const std::string e = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n<model xmlns=\"http://www.cellml.org/cellml/1.2#\" name=\"" + n + "\"></model>";

    libcellml::Model m;
    m.setName(n);

    EXPECT_EQ("name", m.getName());

    EXPECT_EQ(e, m.serialise(libcellml::CELLML_FORMAT_XML));
}

TEST(Model, unset_name) {
    std::string n = "name";
    const std::string eName = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n<model xmlns=\"http://www.cellml.org/cellml/1.2#\" name=\"" + n + "\"></model>";
    const std::string e = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n<model xmlns=\"http://www.cellml.org/cellml/1.2#\"></model>";

    libcellml::Model m;
    m.setName(n);
    EXPECT_EQ("name", m.getName());
    EXPECT_EQ(eName, m.serialise(libcellml::CELLML_FORMAT_XML));

    m.setName("");
    EXPECT_EQ("", m.getName());
    EXPECT_EQ(e, m.serialise(libcellml::CELLML_FORMAT_XML));
}

TEST(Model, invalid_name) {
    std::string in = "invalid name";
    const std::string e = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n<model xmlns=\"http://www.cellml.org/cellml/1.2#\" name=\"" + in + "\"></model>";

    libcellml::Model m;
    m.setName(in);

    EXPECT_EQ("invalid name", m.getName());

    EXPECT_EQ(e, m.serialise(libcellml::CELLML_FORMAT_XML));
}

TEST(Model, add_component) {
    const std::string e = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n<model xmlns=\"http://www.cellml.org/cellml/1.2#\"><component/></model>";
    libcellml::Model m;
    libcellml::Component c;
    m.addComponent(c);
    std::string a = m.serialise(libcellml::CELLML_FORMAT_XML);

    EXPECT_EQ(e, a);
}

TEST(Model, add_valid_component) {
    const std::string in = "valid_name";
    const std::string e = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n<model xmlns=\"http://www.cellml.org/cellml/1.2#\"><component name=\"" + in + "\"/></model>";
    libcellml::Model m;
    libcellml::Component c;
    c.setName(in);
    m.addComponent(c);
    std::string a = m.serialise(libcellml::CELLML_FORMAT_XML);

    EXPECT_EQ(e, a);
}

TEST(Model, add_invalid_component) {
    const std::string in = "invalid name";
    const std::string e = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n<model xmlns=\"http://www.cellml.org/cellml/1.2#\"><component name=\"" + in + "\"/></model>";
    libcellml::Model m;
    libcellml::Component c;
    c.setName(in);
    m.addComponent(c);
    std::string a = m.serialise(libcellml::CELLML_FORMAT_XML);

    EXPECT_EQ(e, a);
}

TEST(Model, add_components) {
    const std::string name1 = "component_1";
    const std::string name2 = "component_2";
    const std::string e = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n<model xmlns=\"http://www.cellml.org/cellml/1.2#\"><component name=\"" + name1 + "\"/><component/></model>";
    libcellml::Model m;
    libcellml::Component c1;
    c1.setName(name1);
    m.addComponent(c1);
    libcellml::Component c2;
    m.addComponent(c2);
    // once the component is added, we should be able to change the handle to the component and have those changes
    // reflected in the model? No, adding component to model moves that component to the model and we no longer have access
    // to it here.
    c2.setName(name2); // so should this give an error?
    std::string a = m.serialise(libcellml::CELLML_FORMAT_XML);

    EXPECT_EQ(e, a);
}

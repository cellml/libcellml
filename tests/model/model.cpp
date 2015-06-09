#include "gtest/gtest.h"

#include <libcellml>

const std::string e = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n<model xmlns=\"http://www.cellml.org/cellml/1.2#\"></model>";

TEST(Model, serialise) {
    libcellml::Model m = libcellml::Model();
    std::string a = m.serialise(libcellml::CELLML_FORMAT_XML);

   EXPECT_EQ(e, a);
}

TEST(Model, name) {
    const std::string e = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n<model xmlns=\"http://www.cellml.org/cellml/1.2#\"></model>";

    libcellml::Model m = libcellml::Model();
    std::string n = "name";
    m.setName(n);

    EXPECT_EQ("name", m.getName());

    EXPECT_EQ(e, m.serialise(libcellml::CELLML_FORMAT_XML));
}

TEST(Model, invalid_name) {
    libcellml::Model m = libcellml::Model();
    std::string in = "invalid name";
    m.setName(in);

    EXPECT_EQ("invalid name", m.getName());

    EXPECT_EQ(e, m.serialise(libcellml::CELLML_FORMAT_XML));
}

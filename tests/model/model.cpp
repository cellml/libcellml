#include "gtest/gtest.h"

#include <libcellml>

const std::string e = "<?xml version=\"1.0\" encoding=\"UTF-8\"?> \
<model \
    xmlns=\"http://www.cellml.org/cellml/1.2#\" \
</model>";

TEST(Model, serialise) {
    libcellml::Model m = libcellml::Model();
    std::string a = m.serialise(libcellml::CELLML_FORMAT_XML);

   EXPECT_EQ(e, a);
}


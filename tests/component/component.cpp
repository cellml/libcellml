#include "gtest/gtest.h"

#include <libcellml>


TEST(Component, serialise) {
    const std::string e = "<component></component>";
    libcellml::Component m = libcellml::Component();
    std::string a = m.serialise(libcellml::CELLML_FORMAT_XML);

   EXPECT_EQ(e, a);
}


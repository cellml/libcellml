#include "gtest/gtest.h"

#include <libcellml>

TEST(Version, versionMatch)
{
    unsigned int version = libcellml::version();
    EXPECT_EQ(0x000700U, version);

    std::string versionString = libcellml::versionString();
    EXPECT_EQ("0.7.0", versionString);
}

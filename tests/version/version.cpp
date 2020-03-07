#include "gtest/gtest.h"

#include <libcellml>

TEST(Version, versionMatch)
{
    unsigned int version = libcellml::version();
    EXPECT_EQ(0x000200U, version);

    std::string versionString = libcellml::versionString();
    EXPECT_EQ("0.2.0", versionString);
}

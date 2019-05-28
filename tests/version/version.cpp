#include "gtest/gtest.h"

#include <libcellml>

TEST(Version, versionMatch)
{
    unsigned int version = libcellml::version();
    EXPECT_EQ(0x000200u, version);

    std::string version_string = libcellml::versionString();
    EXPECT_EQ("0.2.0", version_string);
}

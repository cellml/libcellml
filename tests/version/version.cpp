#include "gtest/gtest.h"

#include <libcellml>

TEST(Version, versionMatch)
{
    unsigned int version = libcellml::version();
    EXPECT_EQ(0x000100U, version);

    std::string version_string = libcellml::versionString();
    EXPECT_EQ("0.1.0", version_string);
}

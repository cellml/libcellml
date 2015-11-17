/*
Copyright 2015 University of Auckland

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.Some license of other
*/

#include "gtest/gtest.h"

#include <libcellml>


TEST(Units, serialise) {
    const std::string e = "<units/>";
    libcellml::Units u;
    std::string a = u.serialise(libcellml::CELLML_FORMAT_XML);
    EXPECT_EQ(e, a);
}

TEST(Units, valid_name) {
    const std::string e = "<units name=\"valid_name\"/>";
    libcellml::Units u;
    u.setName("valid_name");
    std::string a = u.serialise(libcellml::CELLML_FORMAT_XML);
    EXPECT_EQ(e, a);
    EXPECT_EQ("valid_name", u.getName());
}

TEST(Units, invalid_name) {
    const std::string e = "<units name=\"invalid name\"/>";
    libcellml::Units u;
    u.setName("invalid name");
    std::string a = u.serialise(libcellml::CELLML_FORMAT_XML);
    EXPECT_EQ(e, a);
    EXPECT_EQ("invalid name", u.getName());
}


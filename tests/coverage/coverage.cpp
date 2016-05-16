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
limitations under the License.
*/

#include "gtest/gtest.h"

#include <libcellml>

/*
 * The tests in this file are here to catch any branches of code that
 * are not picked up by the main tests testing the API of the library
 */

TEST(Coverage, import) {
    std::string e = "";
    libcellml::Import i, im;

    im = std::move(i);

    // Copy constructor
    libcellml::Import ic(im);

    EXPECT_EQ(e, ic.serialise(libcellml::Formats::XML));
}

TEST(Coverage, entity) {
    std::string ex = "";

    libcellml::Entity e, em;

    EXPECT_EQ(ex, e.serialise(libcellml::Formats::XML));
    em = std::move(e);

    libcellml::Model m;
    e.setParent(&m);

    EXPECT_EQ(&m, e.getParent());

    libcellml::Component c;
    e.setParent(&c);

    EXPECT_EQ(&c, e.getParent());
}

TEST(Coverage, units) {
    std::string e = "";
    libcellml::Units u, um;

    um = std::move(u);

    // Copy constructor
    libcellml::Units uc(um);

    EXPECT_EQ(e, uc.serialise(libcellml::Formats::XML));
}


TEST(Coverage, prefixToString) {
    libcellml::Model m;

    std::vector<std::string> prefix_str =
        {"atto",
         "centi",
         "deca",
         "deci",
         "exa",
         "femto",
         "giga",
         "hecto",
         "kilo",
         "mega",
         "micro",
         "milli",
         "nano",
         "peta",
         "pico",
         "tera",
         "yocto",
         "yotta",
         "zepto",
         "zetta"
        };
    std::vector<libcellml::Prefixes> prefix_enum =
        {libcellml::Prefixes::ATTO,
         libcellml::Prefixes::CENTI,
         libcellml::Prefixes::DECA,
         libcellml::Prefixes::DECI,
         libcellml::Prefixes::EXA,
         libcellml::Prefixes::FEMTO,
         libcellml::Prefixes::GIGA,
         libcellml::Prefixes::HECTO,
         libcellml::Prefixes::KILO,
         libcellml::Prefixes::MEGA,
         libcellml::Prefixes::MICRO,
         libcellml::Prefixes::MILLI,
         libcellml::Prefixes::NANO,
         libcellml::Prefixes::PETA,
         libcellml::Prefixes::PICO,
         libcellml::Prefixes::TERA,
         libcellml::Prefixes::YOCTO,
         libcellml::Prefixes::YOTTA,
         libcellml::Prefixes::ZEPTO,
         libcellml::Prefixes::ZETTA
        };
    for (std::vector<std::string>::size_type i = 0; i != prefix_str.size(); ++i) {
        std::string prefix = prefix_str[i];
        libcellml::UnitsPtr u = std::make_shared<libcellml::Units>();
        u->setName("abcdefg");
        u->addUnit("empty", prefix_enum[i]);

        m.addUnits(u);

        std::string a = m.serialise(libcellml::Formats::XML);
        std::size_t found = a.find(prefix);
        EXPECT_NE(std::string::npos, found);
    }
}

TEST(Coverage, variable) {
    std::string e = "<variable/>";
    libcellml::Variable v, vm;

    vm = std::move(v);

    // Copy constructor
    libcellml::Variable vc(vm);

    EXPECT_EQ(e, vc.serialise(libcellml::Formats::XML));
}

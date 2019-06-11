/*
Copyright libCellML Contributors

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

#include <iostream>
#include <libcellml>

/*
 * The tests in this file are here to catch any branches of code that
 * are not picked up by the main tests testing the API of the library
 */
TEST(Coverage, import)
{
    const std::string e;
    libcellml::ImportSource i;
    libcellml::ImportSource im;

    im = std::move(i);

    // Copy constructor
    libcellml::ImportSource ic(im);

    const std::string a = ic.id();
    EXPECT_EQ(e, a);
}

TEST(Coverage, printer)
{
    libcellml::Printer p;
    libcellml::Printer pm;

    pm = std::move(p);

    // Copy constructor
    libcellml::Printer pc(pm);

    size_t error_count = pc.errorCount();
    EXPECT_EQ(size_t(0), error_count);
}

TEST(Coverage, units)
{
    const std::string e = "<units name=\"dimensionless\"/>\n";
    libcellml::Units u;
    libcellml::Units um;

    u.setName("dimensionless");

    um = std::move(u);

    // Copy constructor
    libcellml::Units uc(um);

    libcellml::Printer printer;
    const std::string a = printer.printUnits(uc);
    EXPECT_EQ(e, a);
}

TEST(Coverage, when)
{
    const std::string e =
        "<reset>\n"
        "  <when/>\n"
        "</reset>\n";
    libcellml::When w;
    libcellml::When wm;
    libcellml::Reset r;

    wm = std::move(w);

    libcellml::When wc(wm);

    libcellml::WhenPtr wp = std::make_shared<libcellml::When>(wc);
    r.addWhen(wp);

    libcellml::Printer printer;
    const std::string a = printer.printReset(r);
    EXPECT_EQ(e, a);
}

TEST(Coverage, unitsGetVariations)
{
    libcellml::Model m;

    libcellml::UnitsPtr u = std::make_shared<libcellml::Units>();
    u->setName("a_unit");

    u->addUnit(libcellml::Units::StandardUnit::AMPERE, "micro");
    m.addUnits(u);

    libcellml::UnitsPtr un = m.getUnits(0);
    EXPECT_EQ("a_unit", un->getName());
    libcellml::UnitsPtr uSn = static_cast<const libcellml::Model>(m).getUnits(0);
    EXPECT_EQ("a_unit", uSn->getName());

    libcellml::UnitsPtr uns = m.getUnits("a_unit");
    EXPECT_EQ("a_unit", uns->getName());
    libcellml::UnitsPtr uSns = static_cast<const libcellml::Model>(m).getUnits("a_unit");
    EXPECT_EQ("a_unit", uSns->getName());

    EXPECT_EQ(nullptr, m.getUnits("b_unit"));
    EXPECT_EQ(nullptr, m.getUnits(4));
}

TEST(Coverage, prefixToString)
{
    libcellml::Model m;
    libcellml::Printer printer;

    std::vector<std::string> prefixString =
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
         "zetta"};
    std::vector<libcellml::Prefix> prefixEnum =
        {libcellml::Prefix::ATTO,
         libcellml::Prefix::CENTI,
         libcellml::Prefix::DECA,
         libcellml::Prefix::DECI,
         libcellml::Prefix::EXA,
         libcellml::Prefix::FEMTO,
         libcellml::Prefix::GIGA,
         libcellml::Prefix::HECTO,
         libcellml::Prefix::KILO,
         libcellml::Prefix::MEGA,
         libcellml::Prefix::MICRO,
         libcellml::Prefix::MILLI,
         libcellml::Prefix::NANO,
         libcellml::Prefix::PETA,
         libcellml::Prefix::PICO,
         libcellml::Prefix::TERA,
         libcellml::Prefix::YOCTO,
         libcellml::Prefix::YOTTA,
         libcellml::Prefix::ZEPTO,
         libcellml::Prefix::ZETTA};
    for (std::vector<std::string>::size_type i = 0; i != prefixString.size(); ++i) {
        libcellml::UnitsPtr u = std::make_shared<libcellml::Units>();
        u->setName("abcdefg");
        u->addUnit("empty", prefixEnum[i]);

        m.addUnits(u);

        const std::string a = printer.printModel(m);
        std::size_t found = a.find(prefixString[i]);
        EXPECT_NE(std::string::npos, found);
        m.removeAllUnits();
    }
}

TEST(Coverage, variable)
{
    const std::string e = "<variable units=\"dimensionless\" initial_value=\"1\" interface=\"public\"/>\n";
    libcellml::Variable v;
    libcellml::Variable vm;
    libcellml::UnitsPtr u = std::make_shared<libcellml::Units>();

    v.setInitialValue(1.0);
    v.setInterfaceType("public");
    u->setName("dimensionless");
    v.setUnits(u);

    vm = std::move(v);

    // Copy constructor
    libcellml::Variable vc(vm);

    libcellml::Printer printer;
    const std::string a = printer.printVariable(vc);
    EXPECT_EQ(e, a);
}

TEST(Coverage, component)
{
    const std::string e =
        "<component name=\"name\">\n"
        "  <variable/>\n"
        "  <1+1=2>\n"
        "</component>\n";
    const std::string math = "<1+1=2>\n";
    libcellml::Component c;
    libcellml::Component cm;
    libcellml::VariablePtr v = std::make_shared<libcellml::Variable>();

    c.setName("name");
    c.addVariable(v);
    c.setMath(math);

    libcellml::Printer printer;
    std::string a = printer.printComponent(c);
    EXPECT_EQ(e, a);

    cm = std::move(c);
    a = printer.printComponent(cm);
    EXPECT_EQ(e, a);

    // Copy constructor
    libcellml::Component cc(cm);
    a = printer.printComponent(cc);
    EXPECT_EQ(e, a);
}

TEST(Coverage, error)
{
    libcellml::ErrorPtr err = std::make_shared<libcellml::Error>();
    libcellml::Error e;
    libcellml::Error em;
    const std::string description = "test";

    e.setDescription(description);
    e.setKind(libcellml::Error::Kind::XML);

    em = std::move(e);
    // Copy constructor
    libcellml::Error ec(em);

    EXPECT_EQ(description, ec.description());
    EXPECT_EQ(libcellml::Error::Kind::XML, ec.kind());
}

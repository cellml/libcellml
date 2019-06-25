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
TEST(Coverage, connectionComment)
{
    const std::string in =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/2.0#\" name=\"modelA\">\n"
        "  <component name=\"componentA\">\n"
        "    <variable name=\"variable1\" units=\"dimensionless\"/>\n"
        "  </component>\n"
        "  <connection component_1=\"component1\">\n"
        "    <!-- Comment on connection. -->\n"
        "    <map_variables variable_1=\"variable1\" variable_2=\"variable2\">\n"
        "      <!-- Comment in a map variables. -->\n"
        "    </map_variables>\n"
        "  </connection>\n"
        "</model>\n";

    libcellml::Parser p;
    p.parseModel(in);
    EXPECT_EQ(size_t(4), p.errorCount());
}

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

TEST(Coverage, importWithNonHrefXlink)
{
    const std::string e =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/2.0#\">\n"
        "  <import xlink:href=\"some-other-model.xml\" xlink:type=\"simple\" xmlns:xlink=\"http://www.w3.org/1999/xlink\">\n"
        "    <component component_ref=\"component_in_that_model\" name=\"component_in_this_model\"/>\n"
        "    <!-- Comment in an import block -->\n"
        "  </import>\n"
        "  <component name=\"component_bob\">\n"
        "    <variable name=\"variable_bob\" units=\"dimensionless\"/>\n"
        "  </component>\n"
        "  <connection component_2=\"component_in_this_model\" component_1=\"component_bob\">\n"
        "    <map_variables variable_2=\"variable_import\" variable_1=\"variable_bob\"/>\n"
        "  </connection>\n"
        "</model>\n";

    // Parse
    libcellml::Parser parser;
    parser.parseModel(e);
    EXPECT_EQ(size_t(0), parser.errorCount());
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

    EXPECT_EQ("dimensionless", uc.name());
}

TEST(Coverage, when)
{
    const std::string randomValue = "4738";

    libcellml::When w;
    libcellml::When wm;
    libcellml::Reset r;

    w.setValue(randomValue);
    wm = std::move(w);

    libcellml::When wc(wm);

    libcellml::WhenPtr wp = std::make_shared<libcellml::When>(wc);
    r.addWhen(wp);

    EXPECT_EQ(randomValue, wc.value());
}

TEST(Coverage, unitsGetVariations)
{
    libcellml::Model m;

    libcellml::UnitsPtr u = std::make_shared<libcellml::Units>();
    u->setName("a_unit");

    u->addUnit(libcellml::Units::StandardUnit::AMPERE, "micro");
    m.addUnits(u);

    libcellml::UnitsPtr un = m.units(0);
    EXPECT_EQ("a_unit", un->name());
    libcellml::UnitsPtr uSn = static_cast<const libcellml::Model>(m).units(0);
    EXPECT_EQ("a_unit", uSn->name());

    libcellml::UnitsPtr uns = m.units("a_unit");
    EXPECT_EQ("a_unit", uns->name());
    libcellml::UnitsPtr uSns = static_cast<const libcellml::Model>(m).units("a_unit");
    EXPECT_EQ("a_unit", uSns->name());

    EXPECT_EQ(nullptr, m.units("b_unit"));
    EXPECT_EQ(nullptr, m.units(4));
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
    const std::string dimensionless = "dimensionless";
    libcellml::Variable v;
    libcellml::Variable vm;
    libcellml::UnitsPtr u = std::make_shared<libcellml::Units>();

    v.setInitialValue(1.0);
    v.setInterfaceType("public");
    u->setName(dimensionless);
    v.setUnits(u);

    vm = std::move(v);

    // Copy constructor
    libcellml::Variable vc(vm);

    EXPECT_EQ(dimensionless, vc.units());
}

TEST(Coverage, component)
{
    const std::string math = "<1+1=2>\n";
    libcellml::Component c;
    libcellml::Component cm;
    libcellml::VariablePtr v = std::make_shared<libcellml::Variable>();

    c.setName("name");
    c.addVariable(v);
    c.setMath(math);

    EXPECT_EQ(size_t(1), c.variableCount());

    cm = std::move(c);
    EXPECT_EQ(size_t(1), cm.variableCount());

    // Copy constructor
    libcellml::Component cc(cm);
    EXPECT_EQ(size_t(1), cc.variableCount());
}

TEST(Coverage, error)
{
    libcellml::IssuePtr err = std::make_shared<libcellml::Issue>();
    libcellml::Issue e;
    libcellml::Issue em;
    const std::string description = "test";

    e.setDescription(description);
    e.setKind(libcellml::Issue::Kind::XML);

    em = std::move(e);
    // Copy constructor
    libcellml::Issue ec(em);

    EXPECT_EQ(description, ec.description());
    EXPECT_EQ(libcellml::Issue::Kind::XML, ec.kind());
}

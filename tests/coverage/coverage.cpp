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
    const std::string id = "id";

    libcellml::ImportSource i;
    libcellml::ImportSource im;

    i.setId(id);

    im = std::move(i);

    libcellml::ImportSource ic(im);

    EXPECT_EQ(id, ic.id());
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

    libcellml::ErrorPtr error = std::make_shared<libcellml::Error>();

    p.addError(error);

    pm = std::move(p);

    libcellml::Printer pc(pm);

    EXPECT_EQ(size_t(1), pc.errorCount());
}

TEST(Coverage, units)
{
    const std::string n = "dimensionless";

    libcellml::Units u;
    libcellml::Units um;

    u.setName("dimensionless");

    um = std::move(u);

    libcellml::Units uc(um);

    EXPECT_EQ(n, uc.name());
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
    const std::string n = "dimensionless";

    libcellml::Variable v;
    libcellml::Variable vm;
    libcellml::UnitsPtr u = std::make_shared<libcellml::Units>();

    u->setName(n);
    v.setUnits(u);

    vm = std::move(v);

    libcellml::Variable vc(vm);

    EXPECT_EQ(n, vc.units());
}

TEST(Coverage, component)
{
    const std::string n = "name";

    libcellml::Component rc;
    libcellml::Component ao;

    rc.setName(n);

    ao = rc;

    EXPECT_EQ(n, ao.name());

    std::vector<libcellml::Component> vec;

    vec.push_back(rc);
    vec.insert(vec.begin(), ao);
}

TEST(Coverage, error)
{
    const std::string description = "test";

    libcellml::Error e;
    libcellml::Error em;

    e.setDescription(description);

    em = std::move(e);

    libcellml::Error ec(em);

    EXPECT_EQ(description, ec.description());
}

TEST(Coverage, model)
{
    const std::string n = "model";

    libcellml::Model rm;
    libcellml::Model ao;

    rm.setName(n);

    ao = rm;

    EXPECT_EQ(n, ao.name());

    std::vector<libcellml::Model> vec;

    vec.push_back(rm);
    vec.insert(vec.begin(), ao);
}

TEST(Coverage, generator)
{
    libcellml::Generator rg;
    libcellml::Generator ao;

    ao = rg;

    std::vector<libcellml::Generator> vec;

    vec.push_back(rg);
    vec.insert(vec.begin(), ao);

    rg.setProfile(std::make_shared<libcellml::GeneratorProfile>());
}

TEST(Coverage, generatorProfile)
{
    libcellml::GeneratorProfile rgp;
    libcellml::GeneratorProfile ao;

    ao = rgp;

    std::vector<libcellml::GeneratorProfile> vec;

    vec.push_back(rgp);
    vec.insert(vec.begin(), ao);
}

TEST(Coverage, generatorVariable)
{
    libcellml::GeneratorVariable rgp;
    libcellml::GeneratorVariable ao;

    ao = rgp;

    std::vector<libcellml::GeneratorVariable> vec;

    vec.push_back(rgp);
    vec.insert(vec.begin(), ao);
}

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
    const std::string id = "id";
    libcellml::ImportSource i;
    libcellml::ImportSource im;

    i.setId(id);

    im = std::move(i);

    EXPECT_EQ(id, im.getId());
}

TEST(Coverage, printer)
{
    libcellml::Printer p;
    libcellml::Printer pm;

    libcellml::ErrorPtr error = std::make_shared<libcellml::Error>();

    p.addError(error);

    pm = std::move(p);

    EXPECT_EQ(size_t(1), pm.errorCount());
}

TEST(Coverage, units)
{
    const std::string n = "dimensionless";
    libcellml::Units u;
    libcellml::Units um;

    u.setName("dimensionless");

    um = std::move(u);

    EXPECT_EQ(n, um.getName());
}

TEST(Coverage, when)
{
    const std::string id = "id";
    libcellml::When w;
    libcellml::When wm;

    w.setId(id);

    wm = std::move(w);

    EXPECT_EQ(id, wm.getId());
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
    const std::string n = "name";
    const std::string e =
        "<component name=\"name\">\n"
        "  <variable/>\n"
        "  <1+1=2>\n"
        "</component>\n";
    const std::string math = "<1+1=2>\n";

    libcellml::ComponentPtr c = std::make_shared<libcellml::Component>();
    libcellml::ComponentPtr cm;
    libcellml::VariablePtr v = std::make_shared<libcellml::Variable>();

    c->setName(n);
    c->addVariable(v);
    c->setMath(math);

    libcellml::Printer printer;
    std::string a = printer.printComponent(c);
    EXPECT_EQ(e, a);

    cm = std::move(c);
    a = printer.printComponent(cm);
    EXPECT_EQ(e, a);

    // Move constructor, assignment operator and swap method
    std::vector<libcellml::Component> vec;
    vec.emplace_back();

    libcellml::Component rc;
    libcellml::Component ao;

    rc.setName(n);

    ao = rc;

    EXPECT_EQ(n, ao.getName());
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

    EXPECT_EQ(description, ec.getDescription());
    EXPECT_EQ(libcellml::Error::Kind::XML, ec.getKind());
}

TEST(Coverage, model)
{
    // Move constructor, assignment operator and swap method
    std::vector<libcellml::Model> vec;
    vec.emplace_back();

    libcellml::Model rm;
    libcellml::Model ao;

    ao = rm;
}

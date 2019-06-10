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

TEST(Coverage, variable)
{
    const std::string n = "dimensionless";
    libcellml::Variable v;
    libcellml::Variable vm;
    libcellml::UnitsPtr u = std::make_shared<libcellml::Units>();

    u->setName(n);
    v.setUnits(u);

    vm = std::move(v);

    EXPECT_EQ(n, vm.getUnits());
}

TEST(Coverage, component)
{
    const std::string n = "name";

    libcellml::Component rc;
    libcellml::Component ao;

    rc.setName(n);

    ao = rc;

    EXPECT_EQ(n, ao.getName());
}

TEST(Coverage, error)
{
    libcellml::Error e;
    libcellml::Error em;
    const std::string description = "test";

    e.setDescription(description);

    em = std::move(e);

    EXPECT_EQ(description, em.getDescription());
}

TEST(Coverage, model)
{
    const std::string n = "model";

    libcellml::Model rm;
    libcellml::Model ao;

    rm.setName(n);

    ao = rm;

    EXPECT_EQ(n, ao.getName());
}

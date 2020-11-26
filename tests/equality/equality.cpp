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

#include <libcellml>

TEST(Equality, invalidInput)
{
    libcellml::VariablePtr v1 = libcellml::Variable::create("variable");

    EXPECT_FALSE(v1->equal(nullptr));
}

TEST(Equality, variableEqualByNameOnly)
{
    libcellml::VariablePtr v1 = libcellml::Variable::create("variable");
    libcellml::VariablePtr v2 = libcellml::Variable::create("variable");

    EXPECT_NE(v1, v2);
    EXPECT_TRUE(v1->equal(v2));
}

TEST(Equality, variableNotEqualByNameOnly)
{
    libcellml::VariablePtr v1 = libcellml::Variable::create("variableA");
    libcellml::VariablePtr v2 = libcellml::Variable::create("variableB");

    EXPECT_NE(v1, v2);
    EXPECT_FALSE(v1->equal(v2));
}

TEST(Equality, variableNotEqualToUnits)
{
    libcellml::VariablePtr v1 = libcellml::Variable::create("variable");
    libcellml::UnitsPtr u1 = libcellml::Units::create("variable");

    EXPECT_FALSE(v1->equal(u1));
}

TEST(Equality, variableEqualDifferentId)
{
    libcellml::VariablePtr v1 = libcellml::Variable::create("variable");
    libcellml::VariablePtr v2 = libcellml::Variable::create("variable");

    v1->setId("eijei3009");
    v2->setId("lefisjeij");

    EXPECT_TRUE(v1->equal(v2));
}

TEST(Equality, variableEqualAllTestedConditionsVariant1)
{
    libcellml::VariablePtr v1 = libcellml::Variable::create();
    libcellml::VariablePtr v2 = libcellml::Variable::create();

    v1->setName("variable");
    v2->setName("variable");

    v1->setInitialValue(3.0);
    v2->setInitialValue("3");

    v1->setInterfaceType(libcellml::Variable::InterfaceType::PUBLIC);
    v2->setInterfaceType(libcellml::Variable::InterfaceType::PUBLIC);

    v1->setUnits("ampere");
    v2->setUnits("ampere");

    EXPECT_TRUE(v1->equal(v2));
}

TEST(Equality, variableEqualAllTestedConditionsVariant2)
{
    libcellml::VariablePtr v1 = libcellml::Variable::create("variable");
    libcellml::VariablePtr v2 = libcellml::Variable::create("variable");

    libcellml::VariablePtr v3 = libcellml::Variable::create("initialValue");
    libcellml::VariablePtr v4 = libcellml::Variable::create("initialValue");

    libcellml::UnitsPtr u1 = libcellml::Units::create("m_per_s");
    libcellml::UnitsPtr u2 = libcellml::Units::create("m_per_s");

    v1->setInitialValue(v3);
    v2->setInitialValue(v4);

    v1->setInterfaceType(libcellml::Variable::InterfaceType::PUBLIC);
    v2->setInterfaceType(libcellml::Variable::InterfaceType::PUBLIC);

    v1->setUnits(u1);
    v2->setUnits(u2);

    EXPECT_TRUE(v1->equal(v2));
}

TEST(Equality, unitsEqualByNameOnly)
{
    libcellml::UnitsPtr u1 = libcellml::Units::create("units");
    libcellml::UnitsPtr u2 = libcellml::Units::create("units");

    EXPECT_NE(u1, u2);
    EXPECT_TRUE(u1->equal(u2));
    EXPECT_TRUE(libcellml::Units::equivalent(u1, u2));
}

TEST(Equality, unitsNotEqualByNameOnly)
{
    libcellml::UnitsPtr u1 = libcellml::Units::create("unitsA");
    libcellml::UnitsPtr u2 = libcellml::Units::create("unitsB");

    EXPECT_NE(u1, u2);
    EXPECT_FALSE(u1->equal(u2));
    EXPECT_FALSE(libcellml::Units::equivalent(u1, u2));
}

TEST(Equality, unitsEqualAllTestedConditionsVariant1)
{
    libcellml::UnitsPtr u1 = libcellml::Units::create("unitsA");
    libcellml::UnitsPtr u2 = libcellml::Units::create("unitsA");

    libcellml::ImportSourcePtr is = libcellml::ImportSource::create();

    u1->setImportReference("some_location");
    u2->setImportReference("some_location");

    u1->setSourceUnits(is, "ampere");
    u2->setSourceUnits(is, "ampere");

    u1->addUnit("meter");
    u2->addUnit("meter");

    EXPECT_TRUE(u1->equal(u2));
}


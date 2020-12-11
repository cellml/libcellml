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

TEST(Equality, variableEqualById)
{
    libcellml::VariablePtr v1 = libcellml::Variable::create("variable");
    libcellml::VariablePtr v2 = libcellml::Variable::create("variable");

    v1->setId("lefisjeij");
    v2->setId("lefisjeij");

    EXPECT_TRUE(v1->equal(v2));
}

TEST(Equality, variableNotEqualById)
{
    libcellml::VariablePtr v1 = libcellml::Variable::create("variable");
    libcellml::VariablePtr v2 = libcellml::Variable::create("variable");

    v1->setId("eijei3009");
    v2->setId("lefisjeij");

    EXPECT_FALSE(v1->equal(v2));
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

TEST(Equality, unitsEqualAllTestedConditionsVariant2)
{
    libcellml::UnitsPtr u1 = libcellml::Units::create("unitsA");
    libcellml::UnitsPtr u2 = libcellml::Units::create("unitsA");

    libcellml::ImportSourcePtr is = libcellml::ImportSource::create();

    u1->setImportReference("some_location");
    u2->setImportReference("some_location");

    u1->setSourceUnits(is, "ampere");
    u2->setSourceUnits(is, "ampere");

    u1->addUnit("second", 1.0, "unit_id");
    u2->addUnit("second", 1.0, "unit_id");

    EXPECT_TRUE(u1->equal(u2));
}

TEST(Equality, unitsNotEqualDifferingNumberOfUnits)
{
    libcellml::UnitsPtr u1 = libcellml::Units::create("unitsA");
    libcellml::UnitsPtr u2 = libcellml::Units::create("unitsA");

    libcellml::ImportSourcePtr is = libcellml::ImportSource::create();

    u1->addUnit("second", 1.0, "second_id");
    u1->addUnit("meter", -1.0, "meter_id");
    u2->addUnit("second", 1.0, "second_id");

    EXPECT_FALSE(u1->equal(u2));
}

TEST(Equality, unitsNotEqualDifferingUnitsBasic)
{
    libcellml::UnitsPtr u1 = libcellml::Units::create("unitsA");
    libcellml::UnitsPtr u2 = libcellml::Units::create("unitsA");

    libcellml::ImportSourcePtr is = libcellml::ImportSource::create();

    u1->addUnit("second", 1.0, "unit_id");
    u2->addUnit("second", 2.0, "unit_id");

    EXPECT_FALSE(u1->equal(u2));
}

TEST(Equality, unitsEqualDifferingOrderOfUnits)
{
    libcellml::UnitsPtr u1 = libcellml::Units::create("unitsA");
    libcellml::UnitsPtr u2 = libcellml::Units::create("unitsA");

    u1->addUnit("second", 1.0, "unit_id");
    u1->addUnit("meter", 3.0);
    u2->addUnit("meter", 3.0);
    u2->addUnit("second", 1.0, "unit_id");

    EXPECT_TRUE(u1->equal(u2));
}

TEST(Equality, unitsEqualDifferingOrderOfUnitsManyUnit)
{
    libcellml::UnitsPtr u1 = libcellml::Units::create("unitsA");
    libcellml::UnitsPtr u2 = libcellml::Units::create("unitsA");

    u1->addUnit("second", 1.0, "unit_id");
    u1->addUnit("meter", 3.0);
    u1->addUnit("apple", 1.0);
    u1->addUnit("jedi", "yota", -2.0);
    u1->addUnit("flip");
    u1->addUnit("lumen");

    u2->addUnit("jedi", "yota", -2.0);
    u2->addUnit("second", 1.0, "unit_id");
    u2->addUnit("lumen");
    u2->addUnit("meter", 3.0);
    u2->addUnit("apple", 1.0);
    u2->addUnit("flip");

    EXPECT_TRUE(u1->equal(u2));
}

TEST(Equality, unitsNotEqualDifferingOrderOfUnits)
{
    libcellml::UnitsPtr u1 = libcellml::Units::create("unitsA");
    libcellml::UnitsPtr u2 = libcellml::Units::create("unitsA");

    u1->addUnit("meter", 3.0);
    u1->addUnit("second", 1.0, "unit_id");
    u2->addUnit("second", 2.0, "unit_id");
    u2->addUnit("meter", 3.0);

    EXPECT_FALSE(u1->equal(u2));
}

TEST(Equality, resetEqual)
{
    libcellml::ResetPtr r1 = libcellml::Reset::create();
    libcellml::ResetPtr r2 = libcellml::Reset::create();

    libcellml::VariablePtr v1 = libcellml::Variable::create("vA");
    libcellml::VariablePtr v2 = libcellml::Variable::create("vA");

    libcellml::VariablePtr tv1 = libcellml::Variable::create("vTest");
    libcellml::VariablePtr tv2 = libcellml::Variable::create("vTest");

    r1->setOrder(3);
    r2->setOrder(3);

    r1->setResetValue("reset value math");
    r2->setResetValue("reset value math");

    r1->setResetValueId("rv_id");
    r2->setResetValueId("rv_id");

    r1->setTestValue("test value math");
    r2->setTestValue("test value math");

    r1->setTestValueId("tv_id");
    r2->setTestValueId("tv_id");

    r1->setTestVariable(tv1);
    r2->setTestVariable(tv2);

    r1->setVariable(v1);
    r2->setVariable(v2);


    EXPECT_TRUE(r1->equal(r2));
}

TEST(Equality, resetNotEqualByOrder)
{
    libcellml::ResetPtr r1 = libcellml::Reset::create();
    libcellml::ResetPtr r2 = libcellml::Reset::create();

    libcellml::VariablePtr v1 = libcellml::Variable::create("vA");
    libcellml::VariablePtr v2 = libcellml::Variable::create("vA");

    libcellml::VariablePtr tv1 = libcellml::Variable::create("vTest");
    libcellml::VariablePtr tv2 = libcellml::Variable::create("vTest");

    r1->setOrder(3);
    r2->setOrder(2);

    r1->setResetValue("reset value math");
    r2->setResetValue("reset value math");

    r1->setResetValueId("rv_id");
    r2->setResetValueId("rv_id");

    r1->setTestValue("test value math");
    r2->setTestValue("test value math");

    r1->setTestValueId("tv_id");
    r2->setTestValueId("tv_id");

    r1->setTestVariable(tv1);
    r2->setTestVariable(tv2);

    r1->setVariable(v1);
    r2->setVariable(v2);


    EXPECT_FALSE(r1->equal(r2));
}

TEST(Equality, resetNotEqualByResetValue)
{
    libcellml::ResetPtr r1 = libcellml::Reset::create();
    libcellml::ResetPtr r2 = libcellml::Reset::create();

    libcellml::VariablePtr v1 = libcellml::Variable::create("vA");
    libcellml::VariablePtr v2 = libcellml::Variable::create("vA");

    libcellml::VariablePtr tv1 = libcellml::Variable::create("vTest");
    libcellml::VariablePtr tv2 = libcellml::Variable::create("vTest");

    r1->setOrder(3);
    r2->setOrder(3);

    r1->setResetValue("reset value math");
    r2->setResetValue("reset value different math");

    r1->setResetValueId("rv_id");
    r2->setResetValueId("rv_id");

    r1->setTestValue("test value math");
    r2->setTestValue("test value math");

    r1->setTestValueId("tv_id");
    r2->setTestValueId("tv_id");

    r1->setTestVariable(tv1);
    r2->setTestVariable(tv2);

    r1->setVariable(v1);
    r2->setVariable(v2);


    EXPECT_FALSE(r1->equal(r2));
}

TEST(Equality, resetNotEqualByResetValueId)
{
    libcellml::ResetPtr r1 = libcellml::Reset::create();
    libcellml::ResetPtr r2 = libcellml::Reset::create();

    libcellml::VariablePtr v1 = libcellml::Variable::create("vA");
    libcellml::VariablePtr v2 = libcellml::Variable::create("vA");

    libcellml::VariablePtr tv1 = libcellml::Variable::create("vTest");
    libcellml::VariablePtr tv2 = libcellml::Variable::create("vTest");

    r1->setOrder(3);
    r2->setOrder(3);

    r1->setResetValue("reset value math");
    r2->setResetValue("reset value math");

    r1->setResetValueId("rv_id");
    r2->setResetValueId("rv_alt_id");

    r1->setTestValue("test value math");
    r2->setTestValue("test value math");

    r1->setTestValueId("tv_id");
    r2->setTestValueId("tv_id");

    r1->setTestVariable(tv1);
    r2->setTestVariable(tv2);

    r1->setVariable(v1);
    r2->setVariable(v2);


    EXPECT_FALSE(r1->equal(r2));
}

TEST(Equality, resetNotEqualByTestValue)
{
    libcellml::ResetPtr r1 = libcellml::Reset::create();
    libcellml::ResetPtr r2 = libcellml::Reset::create();

    libcellml::VariablePtr v1 = libcellml::Variable::create("vA");
    libcellml::VariablePtr v2 = libcellml::Variable::create("vA");

    libcellml::VariablePtr tv1 = libcellml::Variable::create("vTest");
    libcellml::VariablePtr tv2 = libcellml::Variable::create("vTest");

    r1->setOrder(3);
    r2->setOrder(3);

    r1->setResetValue("reset value math");
    r2->setResetValue("reset value math");

    r1->setResetValueId("rv_id");
    r2->setResetValueId("rv_id");

    r1->setTestValue("test value different math");
    r2->setTestValue("test value math");

    r1->setTestValueId("tv_id");
    r2->setTestValueId("tv_id");

    r1->setTestVariable(tv1);
    r2->setTestVariable(tv2);

    r1->setVariable(v1);
    r2->setVariable(v2);


    EXPECT_FALSE(r1->equal(r2));
}

TEST(Equality, resetNotEqualByTestValueId)
{
    libcellml::ResetPtr r1 = libcellml::Reset::create();
    libcellml::ResetPtr r2 = libcellml::Reset::create();

    libcellml::VariablePtr v1 = libcellml::Variable::create("vA");
    libcellml::VariablePtr v2 = libcellml::Variable::create("vA");

    libcellml::VariablePtr tv1 = libcellml::Variable::create("vTest");
    libcellml::VariablePtr tv2 = libcellml::Variable::create("vTest");

    r1->setOrder(3);
    r2->setOrder(3);

    r1->setResetValue("reset value math");
    r2->setResetValue("reset value math");

    r1->setResetValueId("rv_id");
    r2->setResetValueId("rv_id");

    r1->setTestValue("test value math");
    r2->setTestValue("test value math");

    r1->setTestValueId("tv_alt_id");
    r2->setTestValueId("tv_id");

    r1->setTestVariable(tv1);
    r2->setTestVariable(tv2);

    r1->setVariable(v1);
    r2->setVariable(v2);


    EXPECT_FALSE(r1->equal(r2));
}

TEST(Equality, resetNotEqualByTestVariable)
{
    libcellml::ResetPtr r1 = libcellml::Reset::create();
    libcellml::ResetPtr r2 = libcellml::Reset::create();

    libcellml::VariablePtr v1 = libcellml::Variable::create("vA");
    libcellml::VariablePtr v2 = libcellml::Variable::create("vA");

    libcellml::VariablePtr tv1 = libcellml::Variable::create("vTestA");
    libcellml::VariablePtr tv2 = libcellml::Variable::create("vTest");

    r1->setOrder(3);
    r2->setOrder(3);

    r1->setResetValue("reset value math");
    r2->setResetValue("reset value math");

    r1->setResetValueId("rv_id");
    r2->setResetValueId("rv_id");

    r1->setTestValue("test value math");
    r2->setTestValue("test value math");

    r1->setTestValueId("tv_id");
    r2->setTestValueId("tv_id");

    r1->setTestVariable(tv1);
    r2->setTestVariable(tv2);

    r1->setVariable(v1);
    r2->setVariable(v2);


    EXPECT_FALSE(r1->equal(r2));
}

TEST(Equality, resetNotEqualByVariable)
{
    libcellml::ResetPtr r1 = libcellml::Reset::create();
    libcellml::ResetPtr r2 = libcellml::Reset::create();

    libcellml::VariablePtr v1 = libcellml::Variable::create("vA");
    libcellml::VariablePtr v2 = libcellml::Variable::create("vB");

    libcellml::VariablePtr tv1 = libcellml::Variable::create("vTest");
    libcellml::VariablePtr tv2 = libcellml::Variable::create("vTest");

    r1->setOrder(3);
    r2->setOrder(3);

    r1->setResetValue("reset value math");
    r2->setResetValue("reset value math");

    r1->setResetValueId("rv_id");
    r2->setResetValueId("rv_id");

    r1->setTestValue("test value math");
    r2->setTestValue("test value math");

    r1->setTestValueId("tv_id");
    r2->setTestValueId("tv_id");

    r1->setTestVariable(tv1);
    r2->setTestVariable(tv2);

    r1->setVariable(v1);
    r2->setVariable(v2);


    EXPECT_FALSE(r1->equal(r2));
}

/*
Copyright libCellML Contributors

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License->
You may obtain a copy of the License at

    http://www.apache->org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License->
*/

#include "gtest/gtest.h"

#include <libcellml>

TEST(Issue, createModelError)
{
    libcellml::ModelPtr m = libcellml::Model::create();
    libcellml::IssuePtr e = libcellml::Issue::create(m);

    EXPECT_EQ(libcellml::Issue::Cause::MODEL, e->cause());
}

TEST(Issue, createComponemntError)
{
    libcellml::ComponentPtr c = libcellml::Component::create();
    libcellml::IssuePtr e = libcellml::Issue::create(c);

    EXPECT_EQ(libcellml::Issue::Cause::COMPONENT, e->cause());
}

TEST(Issue, createVariableError)
{
    libcellml::VariablePtr v = libcellml::Variable::create();
    libcellml::IssuePtr e = libcellml::Issue::create(v);

    EXPECT_EQ(libcellml::Issue::Cause::VARIABLE, e->cause());
}

TEST(Issue, createUnitsError)
{
    libcellml::UnitsPtr u = libcellml::Units::create();
    libcellml::IssuePtr e = libcellml::Issue::create(u);

    EXPECT_EQ(libcellml::Issue::Cause::UNITS, e->cause());
}

TEST(Issue, createImportSourceError)
{
    libcellml::ImportSourcePtr i = libcellml::ImportSource::create();
    libcellml::IssuePtr e = libcellml::Issue::create(i);

    EXPECT_EQ(libcellml::Issue::Cause::IMPORT, e->cause());
}

TEST(Issue, createResetError)
{
    libcellml::ResetPtr r = libcellml::Reset::create();
    libcellml::IssuePtr e = libcellml::Issue::create(r);

    EXPECT_EQ(libcellml::Issue::Cause::RESET, e->cause());
}

void testSpecificationRule(const libcellml::IssuePtr &e)
{
    switch (e->rule()) {
    case libcellml::SpecificationRule::COMPONENT_CHILD:
        EXPECT_EQ("10.1.2", e->specificationHeading());
        break;
    case libcellml::SpecificationRule::COMPONENT_NAME:
        EXPECT_EQ("10.1.1", e->specificationHeading());
        break;
    case libcellml::SpecificationRule::COMPONENT_REF_CHILD:
        EXPECT_EQ("16.1.2", e->specificationHeading());
        break;
    case libcellml::SpecificationRule::COMPONENT_REF_COMPONENT_ATTRIBUTE:
        EXPECT_EQ("16.1.1", e->specificationHeading());
        break;
    case libcellml::SpecificationRule::COMPONENT_REF_ENCAPSULATION:
        EXPECT_EQ("16.1.3", e->specificationHeading());
        break;
    case libcellml::SpecificationRule::CONNECTION_COMPONENT1:
        EXPECT_EQ("17.1.1", e->specificationHeading());
        break;
    case libcellml::SpecificationRule::CONNECTION_COMPONENT2:
        EXPECT_EQ("17.1.2", e->specificationHeading());
        break;
    case libcellml::SpecificationRule::CONNECTION_UNIQUE_TRANSITIVE:
        EXPECT_EQ("17.1.3", e->specificationHeading());
        break;
    case libcellml::SpecificationRule::CONNECTION_MAP_VARIABLES:
        EXPECT_EQ("17.1.4", e->specificationHeading());
        break;
    case libcellml::SpecificationRule::DATA_REPR_IDENTIFIER_AT_LEAST_ONE_ALPHANUM:
        EXPECT_EQ("3.1.3", e->specificationHeading());
        break;
    case libcellml::SpecificationRule::DATA_REPR_IDENTIFIER_BEGIN_EURO_NUM:
        EXPECT_EQ("3.1.4", e->specificationHeading());
        break;
    case libcellml::SpecificationRule::DATA_REPR_IDENTIFIER_IDENTICAL:
        EXPECT_EQ("3.1.5", e->specificationHeading());
        break;
    case libcellml::SpecificationRule::DATA_REPR_IDENTIFIER_LATIN_ALPHANUM:
        EXPECT_EQ("3.1.2", e->specificationHeading());
        break;
    case libcellml::SpecificationRule::DATA_REPR_IDENTIFIER_UNICODE:
        EXPECT_EQ("3.1.1", e->specificationHeading());
        break;
    case libcellml::SpecificationRule::DATA_REPR_NNEG_INT_BASE10:
        EXPECT_EQ("3.2.1", e->specificationHeading());
        break;
    case libcellml::SpecificationRule::DATA_REPR_NNEG_INT_EURO_NUM:
        EXPECT_EQ("3.2.2", e->specificationHeading());
        break;
    case libcellml::SpecificationRule::ENCAPSULATION_COMPONENT_REF:
        EXPECT_EQ("15.1.1", e->specificationHeading());
        break;
    case libcellml::SpecificationRule::IMPORT_CHILD:
        EXPECT_EQ("5.1.2", e->specificationHeading());
        break;
    case libcellml::SpecificationRule::IMPORT_CIRCULAR:
        EXPECT_EQ("5.1.3", e->specificationHeading());
        break;
    case libcellml::SpecificationRule::IMPORT_COMPONENT_NAME:
        EXPECT_EQ("7.1.1", e->specificationHeading());
        break;
    case libcellml::SpecificationRule::IMPORT_COMPONENT_REF:
        EXPECT_EQ("7.1.2", e->specificationHeading());
        break;
    case libcellml::SpecificationRule::IMPORT_HREF:
        EXPECT_EQ("5.1.1", e->specificationHeading());
        break;
    case libcellml::SpecificationRule::IMPORT_UNITS_NAME:
        EXPECT_EQ("6.1.1", e->specificationHeading());
        break;
    case libcellml::SpecificationRule::IMPORT_UNITS_REF:
        EXPECT_EQ("6.1.2", e->specificationHeading());
        break;
    case libcellml::SpecificationRule::MAP_VARIABLES_UNIQUE:
        EXPECT_EQ("18.1.3", e->specificationHeading());
        break;
    case libcellml::SpecificationRule::MAP_VARIABLES_VARIABLE1:
        EXPECT_EQ("18.1.1", e->specificationHeading());
        break;
    case libcellml::SpecificationRule::MAP_VARIABLES_VARIABLE2:
        EXPECT_EQ("18.1.2", e->specificationHeading());
        break;
    case libcellml::SpecificationRule::MATH_CHILD:
        EXPECT_EQ("14.1.2", e->specificationHeading());
        break;
    case libcellml::SpecificationRule::MATH_CI_VARIABLE_REFERENCE:
        EXPECT_EQ("14.1.3", e->specificationHeading());
        break;
    case libcellml::SpecificationRule::MATH_CN_UNITS_ATTRIBUTE:
        EXPECT_EQ("14.1.4", e->specificationHeading());
        break;
    case libcellml::SpecificationRule::MATH_MATHML:
        EXPECT_EQ("14.1.1", e->specificationHeading());
        break;
    case libcellml::SpecificationRule::MODEL_CHILD:
        EXPECT_EQ("4.2.2", e->specificationHeading());
        break;
    case libcellml::SpecificationRule::MODEL_ELEMENT:
        EXPECT_EQ("4.1", e->specificationHeading());
        break;
    case libcellml::SpecificationRule::MODEL_MORE_THAN_ONE_ENCAPSULATION:
        EXPECT_EQ("4.2.3", e->specificationHeading());
        break;
    case libcellml::SpecificationRule::MODEL_NAME:
        EXPECT_EQ("4.2.1", e->specificationHeading());
        break;
    case libcellml::SpecificationRule::RESET_CHILD:
        EXPECT_EQ("12.1.2", e->specificationHeading());
        break;
    case libcellml::SpecificationRule::RESET_VARIABLE_REFERENCE:
        EXPECT_EQ("12.1.1.1", e->specificationHeading());
        break;
    case libcellml::SpecificationRule::RESET_TEST_VARIABLE_REFERENCE:
        EXPECT_EQ("12.1.1.1", e->specificationHeading());
        break;
    case libcellml::SpecificationRule::RESET_ORDER:
        EXPECT_EQ("12.1.1.2", e->specificationHeading());
        break;
    case libcellml::SpecificationRule::RESET_TEST_VALUE:
        EXPECT_EQ("12.1.2", e->specificationHeading());
        break;
    case libcellml::SpecificationRule::RESET_RESET_VALUE:
        EXPECT_EQ("12.1.2", e->specificationHeading());
        break;
    case libcellml::SpecificationRule::UNITS_CHILD:
        EXPECT_EQ("8.1.4", e->specificationHeading());
        break;
    case libcellml::SpecificationRule::UNITS_NAME:
        EXPECT_EQ("8.1.1", e->specificationHeading());
        break;
    case libcellml::SpecificationRule::UNITS_NAME_UNIQUE:
        EXPECT_EQ("8.1.2", e->specificationHeading());
        break;
    case libcellml::SpecificationRule::UNITS_STANDARD:
        EXPECT_EQ("8.1.3", e->specificationHeading());
        break;
    case libcellml::SpecificationRule::UNIT_OPTIONAL_ATTRIBUTE:
        EXPECT_EQ("9.1.2", e->specificationHeading());
        break;
    case libcellml::SpecificationRule::UNIT_CIRCULAR_REF:
        EXPECT_EQ("9.1.1.2", e->specificationHeading());
        break;
    case libcellml::SpecificationRule::UNIT_DIGRAPH:
        EXPECT_EQ("9.1.1.1", e->specificationHeading());
        break;
    case libcellml::SpecificationRule::UNIT_EXPONENT:
        EXPECT_EQ("9.1.2.3", e->specificationHeading());
        break;
    case libcellml::SpecificationRule::UNIT_MULTIPLIER:
        EXPECT_EQ("9.1.2.2", e->specificationHeading());
        break;
    case libcellml::SpecificationRule::UNIT_PREFIX:
        EXPECT_EQ("9.1.2.1", e->specificationHeading());
        break;
    case libcellml::SpecificationRule::UNIT_UNITS_REF:
        EXPECT_EQ("9.1.1", e->specificationHeading());
        break;
    case libcellml::SpecificationRule::VARIABLE_INITIAL_VALUE:
        EXPECT_EQ("11.1.2.2", e->specificationHeading());
        break;
    case libcellml::SpecificationRule::VARIABLE_INTERFACE:
        EXPECT_EQ("11.1.2.1", e->specificationHeading());
        break;
    case libcellml::SpecificationRule::VARIABLE_NAME:
        EXPECT_EQ("11.1.1.1", e->specificationHeading());
        break;
    case libcellml::SpecificationRule::VARIABLE_UNITS:
        EXPECT_EQ("11.1.1.2", e->specificationHeading());
        break;
    case libcellml::SpecificationRule::UNDEFINED:
        EXPECT_EQ("", e->specificationHeading());
        break;
    }
}

TEST(Issue, specificationRule)
{
    size_t count = 0;
    libcellml::IssuePtr e = libcellml::Issue::create();
    e->setRule(libcellml::SpecificationRule::UNDEFINED);
    ++count;
    testSpecificationRule(e);
    e->setRule(libcellml::SpecificationRule::COMPONENT_CHILD);
    ++count;
    testSpecificationRule(e);
    e->setRule(libcellml::SpecificationRule::COMPONENT_NAME);
    ++count;
    testSpecificationRule(e);
    e->setRule(libcellml::SpecificationRule::COMPONENT_REF_CHILD);
    ++count;
    testSpecificationRule(e);
    e->setRule(libcellml::SpecificationRule::COMPONENT_REF_COMPONENT_ATTRIBUTE);
    ++count;
    testSpecificationRule(e);
    e->setRule(libcellml::SpecificationRule::COMPONENT_REF_ENCAPSULATION);
    ++count;
    testSpecificationRule(e);
    e->setRule(libcellml::SpecificationRule::CONNECTION_COMPONENT1);
    ++count;
    testSpecificationRule(e);
    e->setRule(libcellml::SpecificationRule::CONNECTION_COMPONENT2);
    ++count;
    testSpecificationRule(e);
    e->setRule(libcellml::SpecificationRule::CONNECTION_UNIQUE_TRANSITIVE);
    ++count;
    testSpecificationRule(e);
    e->setRule(libcellml::SpecificationRule::CONNECTION_MAP_VARIABLES);
    ++count;
    testSpecificationRule(e);
    e->setRule(libcellml::SpecificationRule::DATA_REPR_IDENTIFIER_AT_LEAST_ONE_ALPHANUM);
    ++count;
    testSpecificationRule(e);
    e->setRule(libcellml::SpecificationRule::DATA_REPR_IDENTIFIER_BEGIN_EURO_NUM);
    ++count;
    testSpecificationRule(e);
    e->setRule(libcellml::SpecificationRule::DATA_REPR_IDENTIFIER_IDENTICAL);
    ++count;
    testSpecificationRule(e);
    e->setRule(libcellml::SpecificationRule::DATA_REPR_IDENTIFIER_LATIN_ALPHANUM);
    ++count;
    testSpecificationRule(e);
    e->setRule(libcellml::SpecificationRule::DATA_REPR_IDENTIFIER_UNICODE);
    ++count;
    testSpecificationRule(e);
    e->setRule(libcellml::SpecificationRule::DATA_REPR_NNEG_INT_BASE10);
    ++count;
    testSpecificationRule(e);
    e->setRule(libcellml::SpecificationRule::DATA_REPR_NNEG_INT_EURO_NUM);
    ++count;
    testSpecificationRule(e);
    e->setRule(libcellml::SpecificationRule::ENCAPSULATION_COMPONENT_REF);
    ++count;
    testSpecificationRule(e);
    e->setRule(libcellml::SpecificationRule::IMPORT_CHILD);
    ++count;
    testSpecificationRule(e);
    e->setRule(libcellml::SpecificationRule::IMPORT_CIRCULAR);
    ++count;
    testSpecificationRule(e);
    e->setRule(libcellml::SpecificationRule::IMPORT_COMPONENT_NAME);
    ++count;
    testSpecificationRule(e);
    e->setRule(libcellml::SpecificationRule::IMPORT_COMPONENT_REF);
    ++count;
    testSpecificationRule(e);
    e->setRule(libcellml::SpecificationRule::IMPORT_HREF);
    ++count;
    testSpecificationRule(e);
    e->setRule(libcellml::SpecificationRule::IMPORT_UNITS_NAME);
    ++count;
    testSpecificationRule(e);
    e->setRule(libcellml::SpecificationRule::IMPORT_UNITS_REF);
    ++count;
    testSpecificationRule(e);
    e->setRule(libcellml::SpecificationRule::MAP_VARIABLES_UNIQUE);
    ++count;
    testSpecificationRule(e);
    e->setRule(libcellml::SpecificationRule::MAP_VARIABLES_VARIABLE1);
    ++count;
    testSpecificationRule(e);
    e->setRule(libcellml::SpecificationRule::MAP_VARIABLES_VARIABLE2);
    ++count;
    testSpecificationRule(e);
    e->setRule(libcellml::SpecificationRule::MODEL_CHILD);
    ++count;
    testSpecificationRule(e);
    e->setRule(libcellml::SpecificationRule::MODEL_ELEMENT);
    ++count;
    testSpecificationRule(e);
    e->setRule(libcellml::SpecificationRule::MODEL_MORE_THAN_ONE_ENCAPSULATION);
    ++count;
    testSpecificationRule(e);
    e->setRule(libcellml::SpecificationRule::MODEL_NAME);
    ++count;
    testSpecificationRule(e);
    e->setRule(libcellml::SpecificationRule::RESET_CHILD);
    ++count;
    testSpecificationRule(e);
    e->setRule(libcellml::SpecificationRule::RESET_VARIABLE_REFERENCE);
    ++count;
    testSpecificationRule(e);
    e->setRule(libcellml::SpecificationRule::RESET_TEST_VARIABLE_REFERENCE);
    ++count;
    testSpecificationRule(e);
    e->setRule(libcellml::SpecificationRule::RESET_ORDER);
    ++count;
    testSpecificationRule(e);
    e->setRule(libcellml::SpecificationRule::UNITS_CHILD);
    ++count;
    testSpecificationRule(e);
    e->setRule(libcellml::SpecificationRule::UNITS_NAME);
    ++count;
    testSpecificationRule(e);
    e->setRule(libcellml::SpecificationRule::UNITS_NAME_UNIQUE);
    ++count;
    testSpecificationRule(e);
    e->setRule(libcellml::SpecificationRule::UNITS_STANDARD);
    ++count;
    testSpecificationRule(e);
    e->setRule(libcellml::SpecificationRule::UNIT_OPTIONAL_ATTRIBUTE);
    ++count;
    testSpecificationRule(e);
    e->setRule(libcellml::SpecificationRule::UNIT_CIRCULAR_REF);
    ++count;
    testSpecificationRule(e);
    e->setRule(libcellml::SpecificationRule::UNIT_DIGRAPH);
    ++count;
    testSpecificationRule(e);
    e->setRule(libcellml::SpecificationRule::UNIT_EXPONENT);
    ++count;
    testSpecificationRule(e);
    e->setRule(libcellml::SpecificationRule::UNIT_MULTIPLIER);
    ++count;
    testSpecificationRule(e);
    e->setRule(libcellml::SpecificationRule::UNIT_PREFIX);
    ++count;
    testSpecificationRule(e);
    e->setRule(libcellml::SpecificationRule::UNIT_UNITS_REF);
    ++count;
    testSpecificationRule(e);
    e->setRule(libcellml::SpecificationRule::VARIABLE_INITIAL_VALUE);
    ++count;
    testSpecificationRule(e);
    e->setRule(libcellml::SpecificationRule::VARIABLE_INTERFACE);
    ++count;
    testSpecificationRule(e);
    e->setRule(libcellml::SpecificationRule::VARIABLE_NAME);
    ++count;
    testSpecificationRule(e);
    e->setRule(libcellml::SpecificationRule::VARIABLE_UNITS);
    ++count;
    testSpecificationRule(e);
    EXPECT_EQ(size_t(51), count);
}

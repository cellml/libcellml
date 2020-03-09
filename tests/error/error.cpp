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

TEST(Error, createModelError)
{
    libcellml::ModelPtr m = libcellml::Model::create();
    libcellml::ErrorPtr e = libcellml::Error::create(m);

    EXPECT_EQ(libcellml::Error::Kind::MODEL, e->kind());
}

TEST(Error, createComponemntError)
{
    libcellml::ComponentPtr c = libcellml::Component::create();
    libcellml::ErrorPtr e = libcellml::Error::create(c);

    EXPECT_EQ(libcellml::Error::Kind::COMPONENT, e->kind());
}

TEST(Error, createVariableError)
{
    libcellml::VariablePtr v = libcellml::Variable::create();
    libcellml::ErrorPtr e = libcellml::Error::create(v);

    EXPECT_EQ(libcellml::Error::Kind::VARIABLE, e->kind());
}

TEST(Error, createUnitsError)
{
    libcellml::UnitsPtr u = libcellml::Units::create();
    libcellml::ErrorPtr e = libcellml::Error::create(u);

    EXPECT_EQ(libcellml::Error::Kind::UNITS, e->kind());
}

TEST(Error, createImportSourceError)
{
    libcellml::ImportSourcePtr i = libcellml::ImportSource::create();
    libcellml::ErrorPtr e = libcellml::Error::create(i);

    EXPECT_EQ(libcellml::Error::Kind::IMPORT, e->kind());
}

TEST(Error, createResetError)
{
    libcellml::ResetPtr r = libcellml::Reset::create();
    libcellml::ErrorPtr e = libcellml::Error::create(r);

    EXPECT_EQ(libcellml::Error::Kind::RESET, e->kind());
}

void testSpecificationRule(const libcellml::ErrorPtr &e)
{
    switch (e->rule()) {
    case libcellml::SpecificationRule::COMPONENT_CHILD:
        EXPECT_EQ("B7.1.2", e->specificationHeading());
        break;
    case libcellml::SpecificationRule::COMPONENT_NAME:
        EXPECT_EQ("B7.1.1", e->specificationHeading());
        break;
    case libcellml::SpecificationRule::COMPONENT_REF_CHILD:
        EXPECT_EQ("B14.1.2", e->specificationHeading());
        break;
    case libcellml::SpecificationRule::COMPONENT_REF_COMPONENT_ATTRIBUTE:
        EXPECT_EQ("B14.1.1", e->specificationHeading());
        break;
    case libcellml::SpecificationRule::COMPONENT_REF_ENCAPSULATION:
        EXPECT_EQ("B14.1.3", e->specificationHeading());
        break;
    case libcellml::SpecificationRule::CONNECTION_COMPONENT1:
        EXPECT_EQ("B15.1.1", e->specificationHeading());
        break;
    case libcellml::SpecificationRule::CONNECTION_COMPONENT2:
        EXPECT_EQ("B15.1.2", e->specificationHeading());
        break;
    case libcellml::SpecificationRule::CONNECTION_UNIQUE_TRANSITIVE:
        EXPECT_EQ("B15.1.3", e->specificationHeading());
        break;
    case libcellml::SpecificationRule::CONNECTION_MAP_VARIABLES:
        EXPECT_EQ("B15.1.4", e->specificationHeading());
        break;
    case libcellml::SpecificationRule::DATA_REPR_BASIC_REAL_BASE10:
        EXPECT_EQ("A3.4.1", e->specificationHeading());
        break;
    case libcellml::SpecificationRule::DATA_REPR_BASIC_REAL_DECIMAL:
        EXPECT_EQ("A3.4.3", e->specificationHeading());
        break;
    case libcellml::SpecificationRule::DATA_REPR_BASIC_REAL_EURO_NUM:
        EXPECT_EQ("A3.4.4", e->specificationHeading());
        break;
    case libcellml::SpecificationRule::DATA_REPR_BASIC_REAL_SIGN:
        EXPECT_EQ("A3.4.2", e->specificationHeading());
        break;

    case libcellml::SpecificationRule::DATA_REPR_IDENTIFIER_AT_LEAST_ONE_ALPHANUM:
        EXPECT_EQ("A3.1.3", e->specificationHeading());
        break;
    case libcellml::SpecificationRule::DATA_REPR_IDENTIFIER_BEGIN_EURO_NUM:
        EXPECT_EQ("A3.1.4", e->specificationHeading());
        break;
    case libcellml::SpecificationRule::DATA_REPR_IDENTIFIER_IDENTICAL:
        EXPECT_EQ("A3.1.5", e->specificationHeading());
        break;
    case libcellml::SpecificationRule::DATA_REPR_IDENTIFIER_LATIN_ALPHANUM:
        EXPECT_EQ("A3.1.2", e->specificationHeading());
        break;
    case libcellml::SpecificationRule::DATA_REPR_IDENTIFIER_UNICODE:
        EXPECT_EQ("A3.1.1", e->specificationHeading());
        break;
    case libcellml::SpecificationRule::DATA_REPR_INT_BASE10:
        EXPECT_EQ("A3.3.1", e->specificationHeading());
        break;
    case libcellml::SpecificationRule::DATA_REPR_INT_EURO_NUM:
        EXPECT_EQ("A3.3.3", e->specificationHeading());
        break;
    case libcellml::SpecificationRule::DATA_REPR_INT_SIGN:
        EXPECT_EQ("A3.3.2", e->specificationHeading());
        break;
    case libcellml::SpecificationRule::DATA_REPR_NNEG_INT_BASE10:
        EXPECT_EQ("A3.2.1", e->specificationHeading());
        break;
    case libcellml::SpecificationRule::DATA_REPR_NNEG_INT_EURO_NUM:
        EXPECT_EQ("A3.2.2", e->specificationHeading());
        break;
    case libcellml::SpecificationRule::DATA_REPR_REAL_BASE10:
        EXPECT_EQ("A3.5.1", e->specificationHeading());
        break;
    case libcellml::SpecificationRule::DATA_REPR_REAL_EXPONENT:
        EXPECT_EQ("A3.5.4", e->specificationHeading());
        break;
    case libcellml::SpecificationRule::DATA_REPR_REAL_NO_EXPONENT:
        EXPECT_EQ("A3.5.5", e->specificationHeading());
        break;
    case libcellml::SpecificationRule::DATA_REPR_REAL_REPR:
        EXPECT_EQ("A3.5.2", e->specificationHeading());
        break;
    case libcellml::SpecificationRule::DATA_REPR_REAL_SIGNIFICAND:
        EXPECT_EQ("A3.5.3", e->specificationHeading());
        break;
    case libcellml::SpecificationRule::ENCAPSULATION_COMPONENT_REF:
        EXPECT_EQ("B13.1.1", e->specificationHeading());
        break;
    case libcellml::SpecificationRule::IMPORT_CHILD:
        EXPECT_EQ("B2.1.2", e->specificationHeading());
        break;
    case libcellml::SpecificationRule::IMPORT_CIRCULAR:
        EXPECT_EQ("B2.1.3", e->specificationHeading());
        break;
    case libcellml::SpecificationRule::IMPORT_COMPONENT_NAME:
        EXPECT_EQ("B4.1.1", e->specificationHeading());
        break;
    case libcellml::SpecificationRule::IMPORT_COMPONENT_REF:
        EXPECT_EQ("B4.1.2", e->specificationHeading());
        break;
    case libcellml::SpecificationRule::IMPORT_HREF:
        EXPECT_EQ("B2.1.1", e->specificationHeading());
        break;
    case libcellml::SpecificationRule::IMPORT_UNITS_NAME:
        EXPECT_EQ("B3.1.1", e->specificationHeading());
        break;
    case libcellml::SpecificationRule::IMPORT_UNITS_REF:
        EXPECT_EQ("B3.1.2", e->specificationHeading());
        break;
    case libcellml::SpecificationRule::MAP_VARIABLES_IDENTICAL_UNIT_REDUCTION:
        EXPECT_EQ("C10.6", e->specificationHeading());
        break;
    case libcellml::SpecificationRule::MAP_VARIABLES_UNIQUE:
        EXPECT_EQ("B16.1.3", e->specificationHeading());
        break;
    case libcellml::SpecificationRule::MAP_VARIABLES_VARIABLE1:
        EXPECT_EQ("B16.1.1", e->specificationHeading());
        break;
    case libcellml::SpecificationRule::MAP_VARIABLES_VARIABLE2:
        EXPECT_EQ("B16.1.2", e->specificationHeading());
        break;
    case libcellml::SpecificationRule::MATH_CHILD:
        EXPECT_EQ("B12.1.2", e->specificationHeading());
        break;
    case libcellml::SpecificationRule::MATH_CI_VARIABLE_REFERENCE:
        EXPECT_EQ("B12.1.3", e->specificationHeading());
        break;
    case libcellml::SpecificationRule::MATH_CN_TYPE:
        EXPECT_EQ("B12.1.5", e->specificationHeading());
        break;
    case libcellml::SpecificationRule::MATH_CN_BASE10:
        EXPECT_EQ("B12.1.6", e->specificationHeading());
        break;
    case libcellml::SpecificationRule::MATH_CN_UNITS_ATTRIBUTE:
        EXPECT_EQ("B12.1.4", e->specificationHeading());
        break;
    case libcellml::SpecificationRule::MATH_MATHML:
        EXPECT_EQ("B12.1.1", e->specificationHeading());
        break;
    case libcellml::SpecificationRule::MODEL_CHILD:
        EXPECT_EQ("B1.2.2", e->specificationHeading());
        break;
    case libcellml::SpecificationRule::MODEL_ELEMENT:
        EXPECT_EQ("B1.1", e->specificationHeading());
        break;
    case libcellml::SpecificationRule::MODEL_MORE_THAN_ONE_ENCAPSULATION:
        EXPECT_EQ("B1.2.3", e->specificationHeading());
        break;
    case libcellml::SpecificationRule::MODEL_NAME:
        EXPECT_EQ("B1.2.1", e->specificationHeading());
        break;
    case libcellml::SpecificationRule::RESET_CHILD:
        EXPECT_EQ("B9.1.2", e->specificationHeading());
        break;
    case libcellml::SpecificationRule::RESET_VARIABLE_REFERENCE:
        EXPECT_EQ("B9.1.1.1", e->specificationHeading());
        break;
    case libcellml::SpecificationRule::RESET_TEST_VARIABLE_REFERENCE:
        EXPECT_EQ("B9.1.1.1", e->specificationHeading());
        break;
    case libcellml::SpecificationRule::RESET_ORDER:
        EXPECT_EQ("B9.1.1.2", e->specificationHeading());
        break;
    case libcellml::SpecificationRule::RESET_RESET_VALUE:
        EXPECT_EQ("B9.1.2", e->specificationHeading());
        break;
    case libcellml::SpecificationRule::RESET_TEST_VALUE:
        EXPECT_EQ("B9.1.2", e->specificationHeading());
        break;
    case libcellml::SpecificationRule::RESET_RESET_VALUE_CHILD:
        EXPECT_EQ("B11.1.1", e->specificationHeading());
        break;
    case libcellml::SpecificationRule::RESET_TEST_VALUE_CHILD:
        EXPECT_EQ("B10.1.1", e->specificationHeading());
        break;
    case libcellml::SpecificationRule::UNITS_CHILD:
        EXPECT_EQ("B5.1.4", e->specificationHeading());
        break;
    case libcellml::SpecificationRule::UNITS_NAME:
        EXPECT_EQ("B5.1.1", e->specificationHeading());
        break;
    case libcellml::SpecificationRule::UNITS_NAME_UNIQUE:
        EXPECT_EQ("B5.1.2", e->specificationHeading());
        break;
    case libcellml::SpecificationRule::UNITS_STANDARD:
        EXPECT_EQ("B5.1.3", e->specificationHeading());
        break;
    case libcellml::SpecificationRule::UNIT_OPTIONAL_ATTRIBUTE:
        EXPECT_EQ("B6.1.2", e->specificationHeading());
        break;
    case libcellml::SpecificationRule::UNIT_CIRCULAR_REF:
        EXPECT_EQ("B6.1.1.2", e->specificationHeading());
        break;
    case libcellml::SpecificationRule::UNIT_DIGRAPH:
        EXPECT_EQ("B6.1.1.1", e->specificationHeading());
        break;
    case libcellml::SpecificationRule::UNIT_EXPONENT:
        EXPECT_EQ("B6.1.2.3", e->specificationHeading());
        break;
    case libcellml::SpecificationRule::UNIT_MULTIPLIER:
        EXPECT_EQ("B6.1.2.2", e->specificationHeading());
        break;
    case libcellml::SpecificationRule::UNIT_PREFIX:
        EXPECT_EQ("B6.1.2.1", e->specificationHeading());
        break;
    case libcellml::SpecificationRule::UNIT_UNITS_REF:
        EXPECT_EQ("B6.1.1", e->specificationHeading());
        break;
    case libcellml::SpecificationRule::VARIABLE_INITIAL_VALUE:
        EXPECT_EQ("B8.1.2.2", e->specificationHeading());
        break;
    case libcellml::SpecificationRule::VARIABLE_INTERFACE:
        EXPECT_EQ("B8.1.2.1", e->specificationHeading());
        break;
    case libcellml::SpecificationRule::VARIABLE_NAME:
        EXPECT_EQ("B8.1.1.1", e->specificationHeading());
        break;
    case libcellml::SpecificationRule::VARIABLE_UNITS:
        EXPECT_EQ("B8.1.1.2", e->specificationHeading());
        break;
    case libcellml::SpecificationRule::UNDEFINED:
        EXPECT_EQ("", e->specificationHeading());
        break;
    }
}

TEST(Error, specificationRule)
{
    size_t count = 0;
    libcellml::ErrorPtr e = libcellml::Error::create();
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
    e->setRule(libcellml::SpecificationRule::DATA_REPR_BASIC_REAL_BASE10);
    ++count;
    testSpecificationRule(e);
    e->setRule(libcellml::SpecificationRule::DATA_REPR_BASIC_REAL_DECIMAL);
    ++count;
    testSpecificationRule(e);
    e->setRule(libcellml::SpecificationRule::DATA_REPR_BASIC_REAL_EURO_NUM);
    ++count;
    testSpecificationRule(e);
    e->setRule(libcellml::SpecificationRule::DATA_REPR_BASIC_REAL_SIGN);
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
    e->setRule(libcellml::SpecificationRule::DATA_REPR_INT_BASE10);
    ++count;
    testSpecificationRule(e);
    e->setRule(libcellml::SpecificationRule::DATA_REPR_INT_EURO_NUM);
    ++count;
    testSpecificationRule(e);
    e->setRule(libcellml::SpecificationRule::DATA_REPR_INT_SIGN);
    ++count;
    testSpecificationRule(e);
    e->setRule(libcellml::SpecificationRule::DATA_REPR_NNEG_INT_BASE10);
    ++count;
    testSpecificationRule(e);
    e->setRule(libcellml::SpecificationRule::DATA_REPR_NNEG_INT_EURO_NUM);
    ++count;
    testSpecificationRule(e);
    e->setRule(libcellml::SpecificationRule::DATA_REPR_REAL_BASE10);
    ++count;
    testSpecificationRule(e);
    e->setRule(libcellml::SpecificationRule::DATA_REPR_REAL_EXPONENT);
    ++count;
    testSpecificationRule(e);
    e->setRule(libcellml::SpecificationRule::DATA_REPR_REAL_NO_EXPONENT);
    ++count;
    testSpecificationRule(e);
    e->setRule(libcellml::SpecificationRule::DATA_REPR_REAL_REPR);
    ++count;
    testSpecificationRule(e);
    e->setRule(libcellml::SpecificationRule::DATA_REPR_REAL_SIGNIFICAND);
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
    e->setRule(libcellml::SpecificationRule::MATH_CHILD);
    ++count;
    testSpecificationRule(e);
    e->setRule(libcellml::SpecificationRule::MATH_CI_VARIABLE_REFERENCE);
    ++count;
    testSpecificationRule(e);
    e->setRule(libcellml::SpecificationRule::MATH_CN_TYPE);
    ++count;
    testSpecificationRule(e);
    e->setRule(libcellml::SpecificationRule::MATH_CN_BASE10);
    ++count;
    testSpecificationRule(e);
    e->setRule(libcellml::SpecificationRule::MATH_CN_UNITS_ATTRIBUTE);
    ++count;
    testSpecificationRule(e);
    e->setRule(libcellml::SpecificationRule::MATH_MATHML);
    ++count;
    testSpecificationRule(e);
    e->setRule(libcellml::SpecificationRule::MAP_VARIABLES_IDENTICAL_UNIT_REDUCTION);
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
    e->setRule(libcellml::SpecificationRule::RESET_RESET_VALUE);
    ++count;
    testSpecificationRule(e);
    e->setRule(libcellml::SpecificationRule::RESET_RESET_VALUE_CHILD);
    ++count;
    testSpecificationRule(e);
    e->setRule(libcellml::SpecificationRule::RESET_TEST_VALUE);
    ++count;
    testSpecificationRule(e);
    e->setRule(libcellml::SpecificationRule::RESET_TEST_VALUE_CHILD);
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
    EXPECT_EQ(size_t(74), count);
}

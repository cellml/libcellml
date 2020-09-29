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

TEST(Issue, createModelIssue)
{
    libcellml::ModelPtr m = libcellml::Model::create();
    libcellml::IssuePtr e = libcellml::Issue::create(m);

    EXPECT_EQ(libcellml::Issue::Cause::MODEL, e->cause());
}

TEST(Issue, createComponentIssue)
{
    libcellml::ComponentPtr c = libcellml::Component::create();
    libcellml::IssuePtr e = libcellml::Issue::create(c);

    EXPECT_EQ(libcellml::Issue::Cause::COMPONENT, e->cause());
}

TEST(Issue, createVariableIssue)
{
    libcellml::VariablePtr v = libcellml::Variable::create();
    libcellml::IssuePtr e = libcellml::Issue::create(v);

    EXPECT_EQ(libcellml::Issue::Cause::VARIABLE, e->cause());
}

TEST(Issue, createUnitsIssue)
{
    libcellml::UnitsPtr u = libcellml::Units::create();
    libcellml::IssuePtr e = libcellml::Issue::create(u);

    EXPECT_EQ(libcellml::Issue::Cause::UNITS, e->cause());
}

TEST(Issue, createImportSourceIssue)
{
    libcellml::ImportSourcePtr i = libcellml::ImportSource::create();
    libcellml::IssuePtr e = libcellml::Issue::create(i);

    EXPECT_EQ(libcellml::Issue::Cause::IMPORT, e->cause());
}

TEST(Issue, createResetIssue)
{
    libcellml::ResetPtr r = libcellml::Reset::create();
    libcellml::IssuePtr e = libcellml::Issue::create(r);

    EXPECT_EQ(libcellml::Issue::Cause::RESET, e->cause());
}

void testReferenceRule(const libcellml::IssuePtr &e)
{
    switch (e->referenceRule()) {
    case libcellml::Issue::ReferenceRule::UNDEFINED:
        EXPECT_EQ("", e->referenceHeading());
        break;
    case libcellml::Issue::ReferenceRule::DATA_REPR_IDENTIFIER_UNICODE:
        EXPECT_EQ("1.3.1.1", e->referenceHeading());
        break;
    case libcellml::Issue::ReferenceRule::DATA_REPR_IDENTIFIER_LATIN_ALPHANUM:
        EXPECT_EQ("1.3.1.1", e->referenceHeading());
        break;
    case libcellml::Issue::ReferenceRule::DATA_REPR_IDENTIFIER_AT_LEAST_ONE_ALPHANUM:
        EXPECT_EQ("1.3.1.1", e->referenceHeading());
        break;
    case libcellml::Issue::ReferenceRule::DATA_REPR_IDENTIFIER_BEGIN_EURO_NUM:
        EXPECT_EQ("1.3.1.1", e->referenceHeading());
        break;
    case libcellml::Issue::ReferenceRule::DATA_REPR_IDENTIFIER_IDENTICAL:
        EXPECT_EQ("1.3.1.2", e->referenceHeading());
        break;
    case libcellml::Issue::ReferenceRule::DATA_REPR_INT_BASE10:
        EXPECT_EQ("1.3.2.1", e->referenceHeading());
        break;
    case libcellml::Issue::ReferenceRule::DATA_REPR_INT_SIGN:
        EXPECT_EQ("1.3.2.2", e->referenceHeading());
        break;
    case libcellml::Issue::ReferenceRule::DATA_REPR_INT_DIGIT:
        EXPECT_EQ("1.3.2.3", e->referenceHeading());
        break;
    case libcellml::Issue::ReferenceRule::DATA_REPR_BASIC_REAL_BASE10:
        EXPECT_EQ("1.3.3.1", e->referenceHeading());
        break;
    case libcellml::Issue::ReferenceRule::DATA_REPR_BASIC_REAL_SIGN:
        EXPECT_EQ("1.3.3.2", e->referenceHeading());
        break;
    case libcellml::Issue::ReferenceRule::DATA_REPR_BASIC_REAL_DECIMAL:
        EXPECT_EQ("1.3.3.3", e->referenceHeading());
        break;
    case libcellml::Issue::ReferenceRule::DATA_REPR_BASIC_REAL_DIGIT:
        EXPECT_EQ("1.3.3.4", e->referenceHeading());
        break;
    case libcellml::Issue::ReferenceRule::DATA_REPR_REAL_BASE10:
        EXPECT_EQ("1.3.4.1", e->referenceHeading());
        break;
    case libcellml::Issue::ReferenceRule::DATA_REPR_REAL_SIGNIFICAND:
        EXPECT_EQ("1.3.4.3", e->referenceHeading());
        break;
    case libcellml::Issue::ReferenceRule::DATA_REPR_REAL_EXPONENT:
        EXPECT_EQ("1.3.4.4", e->referenceHeading());
        break;
    case libcellml::Issue::ReferenceRule::MODEL_ELEMENT:
        EXPECT_EQ("2.1", e->referenceHeading());
        break;
    case libcellml::Issue::ReferenceRule::MODEL_NAME:
        EXPECT_EQ("2.1.1", e->referenceHeading());
        break;
    case libcellml::Issue::ReferenceRule::MODEL_CHILD:
        EXPECT_EQ("2.1.2", e->referenceHeading());
        break;
    case libcellml::Issue::ReferenceRule::MODEL_MORE_THAN_ONE_ENCAPSULATION:
        EXPECT_EQ("2.1.3", e->referenceHeading());
        break;
    case libcellml::Issue::ReferenceRule::IMPORT_HREF:
        EXPECT_EQ("2.2.1", e->referenceHeading());
        break;
    case libcellml::Issue::ReferenceRule::IMPORT_CHILD:
        EXPECT_EQ("2.2.2", e->referenceHeading());
        break;
    case libcellml::Issue::ReferenceRule::IMPORT_EQUIVALENT:
        EXPECT_EQ("2.2.3", e->referenceHeading());
        break;
    case libcellml::Issue::ReferenceRule::IMPORT_UNITS_NAME:
        EXPECT_EQ("2.3.1", e->referenceHeading());
        break;
    case libcellml::Issue::ReferenceRule::IMPORT_UNITS_NAME_UNIQUE:
        EXPECT_EQ("2.3.1", e->referenceHeading());
        break;
    case libcellml::Issue::ReferenceRule::IMPORT_UNITS_REF:
        EXPECT_EQ("2.3.2", e->referenceHeading());
        break;
    case libcellml::Issue::ReferenceRule::IMPORT_COMPONENT_NAME:
        EXPECT_EQ("2.4.1", e->referenceHeading());
        break;
    case libcellml::Issue::ReferenceRule::IMPORT_COMPONENT_NAME_UNIQUE:
        EXPECT_EQ("2.4.1", e->referenceHeading());
        break;
    case libcellml::Issue::ReferenceRule::IMPORT_COMPONENT_COMPONENT_REF:
        EXPECT_EQ("2.4.2", e->referenceHeading());
        break;
    case libcellml::Issue::ReferenceRule::UNITS_NAME:
        EXPECT_EQ("2.5.1", e->referenceHeading());
        break;
    case libcellml::Issue::ReferenceRule::UNITS_NAME_UNIQUE:
        EXPECT_EQ("2.5.1", e->referenceHeading());
        break;
    case libcellml::Issue::ReferenceRule::UNITS_STANDARD:
        EXPECT_EQ("2.5.2", e->referenceHeading());
        break;
    case libcellml::Issue::ReferenceRule::UNITS_CHILD:
        EXPECT_EQ("2.5.3", e->referenceHeading());
        break;
    case libcellml::Issue::ReferenceRule::UNIT_UNITS_REF:
        EXPECT_EQ("2.6.1", e->referenceHeading());
        break;
    case libcellml::Issue::ReferenceRule::UNIT_CIRCULAR_REF:
        EXPECT_EQ("2.6.1.2", e->referenceHeading());
        break;
    case libcellml::Issue::ReferenceRule::UNIT_OPTIONAL_ATTRIBUTE:
        EXPECT_EQ("2.6.2", e->referenceHeading());
        break;
    case libcellml::Issue::ReferenceRule::UNIT_PREFIX:
        EXPECT_EQ("2.6.2.1", e->referenceHeading());
        break;
    case libcellml::Issue::ReferenceRule::UNIT_MULTIPLIER:
        EXPECT_EQ("2.6.2.2", e->referenceHeading());
        break;
    case libcellml::Issue::ReferenceRule::UNIT_EXPONENT:
        EXPECT_EQ("2.6.2.3", e->referenceHeading());
        break;
    case libcellml::Issue::ReferenceRule::COMPONENT_NAME:
        EXPECT_EQ("2.7.1", e->referenceHeading());
        break;
    case libcellml::Issue::ReferenceRule::COMPONENT_NAME_UNIQUE:
        EXPECT_EQ("2.7.1", e->referenceHeading());
        break;
    case libcellml::Issue::ReferenceRule::COMPONENT_CHILD:
        EXPECT_EQ("2.7.2", e->referenceHeading());
        break;
    case libcellml::Issue::ReferenceRule::VARIABLE_NAME:
        EXPECT_EQ("2.8.1.1", e->referenceHeading());
        break;
    case libcellml::Issue::ReferenceRule::VARIABLE_NAME_UNIQUE:
        EXPECT_EQ("2.8.1.1", e->referenceHeading());
        break;
    case libcellml::Issue::ReferenceRule::VARIABLE_UNITS:
        EXPECT_EQ("2.8.1.2", e->referenceHeading());
        break;
    case libcellml::Issue::ReferenceRule::VARIABLE_INTERFACE:
        EXPECT_EQ("2.8.2.1", e->referenceHeading());
        break;
    case libcellml::Issue::ReferenceRule::VARIABLE_INITIAL_VALUE:
        EXPECT_EQ("2.8.2.2", e->referenceHeading());
        break;
    case libcellml::Issue::ReferenceRule::RESET_VARIABLE_REF:
        EXPECT_EQ("2.9.1.1", e->referenceHeading());
        break;
    case libcellml::Issue::ReferenceRule::RESET_TEST_VARIABLE_REF:
        EXPECT_EQ("2.9.1.2", e->referenceHeading());
        break;
    case libcellml::Issue::ReferenceRule::RESET_ORDER:
        EXPECT_EQ("2.9.1.3", e->referenceHeading());
        break;
    case libcellml::Issue::ReferenceRule::RESET_CHILD:
        EXPECT_EQ("2.9.2", e->referenceHeading());
        break;
    case libcellml::Issue::ReferenceRule::RESET_TEST_VALUE:
        EXPECT_EQ("2.10", e->referenceHeading());
        break;
    case libcellml::Issue::ReferenceRule::RESET_RESET_VALUE:
        EXPECT_EQ("2.11", e->referenceHeading());
        break;
    case libcellml::Issue::ReferenceRule::MATH_MATHML:
        EXPECT_EQ("2.12.1", e->referenceHeading());
        break;
    case libcellml::Issue::ReferenceRule::MATH_CHILD:
        EXPECT_EQ("2.12.2", e->referenceHeading());
        break;
    case libcellml::Issue::ReferenceRule::MATH_CI_VARIABLE_REF:
        EXPECT_EQ("2.12.3", e->referenceHeading());
        break;
    case libcellml::Issue::ReferenceRule::MATH_CN_UNITS:
        EXPECT_EQ("2.13.4", e->referenceHeading());
        break;
    case libcellml::Issue::ReferenceRule::MATH_CN_BASE10:
        EXPECT_EQ("2.13.5", e->referenceHeading());
        break;
    case libcellml::Issue::ReferenceRule::MATH_CN_FORMAT:
        EXPECT_EQ("2.13.5", e->referenceHeading());
        break;
    case libcellml::Issue::ReferenceRule::ENCAPSULATION_CHILD:
        EXPECT_EQ("2.13.1", e->referenceHeading());
        break;
    case libcellml::Issue::ReferenceRule::COMPONENT_REF_COMPONENT:
        EXPECT_EQ("2.14.1", e->referenceHeading());
        break;
    case libcellml::Issue::ReferenceRule::COMPONENT_REF_CHILD:
        EXPECT_EQ("2.14.2", e->referenceHeading());
        break;
    case libcellml::Issue::ReferenceRule::CONNECTION_COMPONENT1:
        EXPECT_EQ("2.15.1", e->referenceHeading());
        break;
    case libcellml::Issue::ReferenceRule::CONNECTION_COMPONENT2:
        EXPECT_EQ("2.15.2", e->referenceHeading());
        break;
    case libcellml::Issue::ReferenceRule::CONNECTION_EXCLUDE_SELF:
        EXPECT_EQ("2.15.3", e->referenceHeading());
        break;
    case libcellml::Issue::ReferenceRule::CONNECTION_UNIQUE:
        EXPECT_EQ("2.15.4", e->referenceHeading());
        break;
    case libcellml::Issue::ReferenceRule::CONNECTION_CHILD:
        EXPECT_EQ("2.15.5", e->referenceHeading());
        break;
    case libcellml::Issue::ReferenceRule::MAP_VARIABLES_VARIABLE1:
        EXPECT_EQ("2.16.1", e->referenceHeading());
        break;
    case libcellml::Issue::ReferenceRule::MAP_VARIABLES_VARIABLE2:
        EXPECT_EQ("2.16.2", e->referenceHeading());
        break;
    case libcellml::Issue::ReferenceRule::MAP_VARIABLES_UNIQUE:
        EXPECT_EQ("2.16.3", e->referenceHeading());
        break;
    case libcellml::Issue::ReferenceRule::MAP_VARIABLES_IDENTICAL_UNIT_REDUCTION:
        EXPECT_EQ("", e->referenceHeading());
        break;
    case libcellml::Issue::ReferenceRule::LIBXML2_ISSUE:
        EXPECT_EQ("", e->referenceHeading());
        break;
    case libcellml::Issue::ReferenceRule::MAP_VARIABLES_AVAILABLE_INTERFACE:
        EXPECT_EQ("3.10.8", e->referenceHeading());
        break;
    }
}

TEST(Issue, referenceRule)
{
    size_t count = 0;
    libcellml::IssuePtr e = libcellml::Issue::create();
    e->setReferenceRule(libcellml::Issue::ReferenceRule::UNDEFINED);
    ++count;
    testReferenceRule(e);
    e->setReferenceRule(libcellml::Issue::ReferenceRule::DATA_REPR_IDENTIFIER_UNICODE);
    ++count;
    testReferenceRule(e);
    e->setReferenceRule(libcellml::Issue::ReferenceRule::DATA_REPR_IDENTIFIER_LATIN_ALPHANUM);
    ++count;
    testReferenceRule(e);
    e->setReferenceRule(libcellml::Issue::ReferenceRule::DATA_REPR_IDENTIFIER_AT_LEAST_ONE_ALPHANUM);
    ++count;
    testReferenceRule(e);
    e->setReferenceRule(libcellml::Issue::ReferenceRule::DATA_REPR_IDENTIFIER_BEGIN_EURO_NUM);
    ++count;
    testReferenceRule(e);
    e->setReferenceRule(libcellml::Issue::ReferenceRule::DATA_REPR_IDENTIFIER_IDENTICAL);
    ++count;
    testReferenceRule(e);
    e->setReferenceRule(libcellml::Issue::ReferenceRule::DATA_REPR_INT_BASE10);
    ++count;
    testReferenceRule(e);
    e->setReferenceRule(libcellml::Issue::ReferenceRule::DATA_REPR_INT_SIGN);
    ++count;
    testReferenceRule(e);
    e->setReferenceRule(libcellml::Issue::ReferenceRule::DATA_REPR_INT_DIGIT);
    ++count;
    testReferenceRule(e);
    e->setReferenceRule(libcellml::Issue::ReferenceRule::DATA_REPR_BASIC_REAL_BASE10);
    ++count;
    testReferenceRule(e);
    e->setReferenceRule(libcellml::Issue::ReferenceRule::DATA_REPR_BASIC_REAL_SIGN);
    ++count;
    testReferenceRule(e);
    e->setReferenceRule(libcellml::Issue::ReferenceRule::DATA_REPR_BASIC_REAL_DECIMAL);
    ++count;
    testReferenceRule(e);
    e->setReferenceRule(libcellml::Issue::ReferenceRule::DATA_REPR_BASIC_REAL_DIGIT);
    ++count;
    testReferenceRule(e);
    e->setReferenceRule(libcellml::Issue::ReferenceRule::DATA_REPR_REAL_BASE10);
    ++count;
    testReferenceRule(e);
    e->setReferenceRule(libcellml::Issue::ReferenceRule::DATA_REPR_REAL_SIGNIFICAND);
    ++count;
    testReferenceRule(e);
    e->setReferenceRule(libcellml::Issue::ReferenceRule::DATA_REPR_REAL_EXPONENT);
    ++count;
    testReferenceRule(e);
    e->setReferenceRule(libcellml::Issue::ReferenceRule::MODEL_ELEMENT);
    ++count;
    testReferenceRule(e);
    e->setReferenceRule(libcellml::Issue::ReferenceRule::MODEL_NAME);
    ++count;
    testReferenceRule(e);
    e->setReferenceRule(libcellml::Issue::ReferenceRule::MODEL_CHILD);
    ++count;
    testReferenceRule(e);
    e->setReferenceRule(libcellml::Issue::ReferenceRule::MODEL_MORE_THAN_ONE_ENCAPSULATION);
    ++count;
    testReferenceRule(e);
    e->setReferenceRule(libcellml::Issue::ReferenceRule::IMPORT_HREF);
    ++count;
    testReferenceRule(e);
    e->setReferenceRule(libcellml::Issue::ReferenceRule::IMPORT_CHILD);
    ++count;
    testReferenceRule(e);
    e->setReferenceRule(libcellml::Issue::ReferenceRule::IMPORT_EQUIVALENT);
    ++count;
    testReferenceRule(e);
    e->setReferenceRule(libcellml::Issue::ReferenceRule::IMPORT_UNITS_NAME);
    ++count;
    testReferenceRule(e);
    e->setReferenceRule(libcellml::Issue::ReferenceRule::IMPORT_UNITS_NAME_UNIQUE);
    ++count;
    testReferenceRule(e);
    e->setReferenceRule(libcellml::Issue::ReferenceRule::IMPORT_UNITS_REF);
    ++count;
    testReferenceRule(e);
    e->setReferenceRule(libcellml::Issue::ReferenceRule::IMPORT_COMPONENT_NAME);
    ++count;
    testReferenceRule(e);
    e->setReferenceRule(libcellml::Issue::ReferenceRule::IMPORT_COMPONENT_NAME_UNIQUE);
    ++count;
    testReferenceRule(e);
    e->setReferenceRule(libcellml::Issue::ReferenceRule::IMPORT_COMPONENT_COMPONENT_REF);
    ++count;
    testReferenceRule(e);
    e->setReferenceRule(libcellml::Issue::ReferenceRule::UNITS_NAME);
    ++count;
    testReferenceRule(e);
    e->setReferenceRule(libcellml::Issue::ReferenceRule::UNITS_NAME_UNIQUE);
    ++count;
    testReferenceRule(e);
    e->setReferenceRule(libcellml::Issue::ReferenceRule::UNITS_STANDARD);
    ++count;
    testReferenceRule(e);
    e->setReferenceRule(libcellml::Issue::ReferenceRule::UNITS_CHILD);
    ++count;
    testReferenceRule(e);
    e->setReferenceRule(libcellml::Issue::ReferenceRule::UNIT_UNITS_REF);
    ++count;
    testReferenceRule(e);
    e->setReferenceRule(libcellml::Issue::ReferenceRule::UNIT_CIRCULAR_REF);
    ++count;
    testReferenceRule(e);
    e->setReferenceRule(libcellml::Issue::ReferenceRule::UNIT_OPTIONAL_ATTRIBUTE);
    ++count;
    testReferenceRule(e);
    e->setReferenceRule(libcellml::Issue::ReferenceRule::UNIT_PREFIX);
    ++count;
    testReferenceRule(e);
    e->setReferenceRule(libcellml::Issue::ReferenceRule::UNIT_MULTIPLIER);
    ++count;
    testReferenceRule(e);
    e->setReferenceRule(libcellml::Issue::ReferenceRule::UNIT_EXPONENT);
    ++count;
    testReferenceRule(e);
    e->setReferenceRule(libcellml::Issue::ReferenceRule::COMPONENT_NAME);
    ++count;
    testReferenceRule(e);
    e->setReferenceRule(libcellml::Issue::ReferenceRule::COMPONENT_NAME_UNIQUE);
    ++count;
    testReferenceRule(e);
    e->setReferenceRule(libcellml::Issue::ReferenceRule::COMPONENT_CHILD);
    ++count;
    testReferenceRule(e);
    e->setReferenceRule(libcellml::Issue::ReferenceRule::VARIABLE_NAME);
    ++count;
    testReferenceRule(e);
    e->setReferenceRule(libcellml::Issue::ReferenceRule::VARIABLE_NAME_UNIQUE);
    ++count;
    testReferenceRule(e);
    e->setReferenceRule(libcellml::Issue::ReferenceRule::VARIABLE_UNITS);
    ++count;
    testReferenceRule(e);
    e->setReferenceRule(libcellml::Issue::ReferenceRule::VARIABLE_INTERFACE);
    ++count;
    testReferenceRule(e);
    e->setReferenceRule(libcellml::Issue::ReferenceRule::VARIABLE_INITIAL_VALUE);
    ++count;
    testReferenceRule(e);
    e->setReferenceRule(libcellml::Issue::ReferenceRule::RESET_VARIABLE_REF);
    ++count;
    testReferenceRule(e);
    e->setReferenceRule(libcellml::Issue::ReferenceRule::RESET_TEST_VARIABLE_REF);
    ++count;
    testReferenceRule(e);
    e->setReferenceRule(libcellml::Issue::ReferenceRule::RESET_ORDER);
    ++count;
    testReferenceRule(e);
    e->setReferenceRule(libcellml::Issue::ReferenceRule::RESET_CHILD);
    ++count;
    testReferenceRule(e);
    e->setReferenceRule(libcellml::Issue::ReferenceRule::RESET_TEST_VALUE);
    ++count;
    testReferenceRule(e);
    e->setReferenceRule(libcellml::Issue::ReferenceRule::RESET_RESET_VALUE);
    ++count;
    testReferenceRule(e);
    e->setReferenceRule(libcellml::Issue::ReferenceRule::MATH_MATHML);
    ++count;
    testReferenceRule(e);
    e->setReferenceRule(libcellml::Issue::ReferenceRule::MATH_CHILD);
    ++count;
    testReferenceRule(e);
    e->setReferenceRule(libcellml::Issue::ReferenceRule::MATH_CI_VARIABLE_REF);
    ++count;
    testReferenceRule(e);
    e->setReferenceRule(libcellml::Issue::ReferenceRule::MATH_CN_UNITS);
    ++count;
    testReferenceRule(e);
    e->setReferenceRule(libcellml::Issue::ReferenceRule::MATH_CN_BASE10);
    ++count;
    testReferenceRule(e);
    e->setReferenceRule(libcellml::Issue::ReferenceRule::MATH_CN_FORMAT);
    ++count;
    testReferenceRule(e);
    e->setReferenceRule(libcellml::Issue::ReferenceRule::ENCAPSULATION_CHILD);
    ++count;
    testReferenceRule(e);
    e->setReferenceRule(libcellml::Issue::ReferenceRule::COMPONENT_REF_COMPONENT);
    ++count;
    testReferenceRule(e);
    e->setReferenceRule(libcellml::Issue::ReferenceRule::COMPONENT_REF_CHILD);
    ++count;
    testReferenceRule(e);
    e->setReferenceRule(libcellml::Issue::ReferenceRule::CONNECTION_COMPONENT1);
    ++count;
    testReferenceRule(e);
    e->setReferenceRule(libcellml::Issue::ReferenceRule::CONNECTION_COMPONENT2);
    ++count;
    testReferenceRule(e);
    e->setReferenceRule(libcellml::Issue::ReferenceRule::CONNECTION_EXCLUDE_SELF);
    ++count;
    testReferenceRule(e);
    e->setReferenceRule(libcellml::Issue::ReferenceRule::CONNECTION_UNIQUE);
    ++count;
    testReferenceRule(e);
    e->setReferenceRule(libcellml::Issue::ReferenceRule::CONNECTION_CHILD);
    ++count;
    testReferenceRule(e);
    e->setReferenceRule(libcellml::Issue::ReferenceRule::MAP_VARIABLES_VARIABLE1);
    ++count;
    testReferenceRule(e);
    e->setReferenceRule(libcellml::Issue::ReferenceRule::MAP_VARIABLES_VARIABLE2);
    ++count;
    testReferenceRule(e);
    e->setReferenceRule(libcellml::Issue::ReferenceRule::MAP_VARIABLES_UNIQUE);
    ++count;
    testReferenceRule(e);
    e->setReferenceRule(libcellml::Issue::ReferenceRule::MAP_VARIABLES_IDENTICAL_UNIT_REDUCTION);
    ++count;
    testReferenceRule(e);
    e->setReferenceRule(libcellml::Issue::ReferenceRule::MAP_VARIABLES_AVAILABLE_INTERFACE);
    ++count;
    testReferenceRule(e);
    e->setReferenceRule(libcellml::Issue::ReferenceRule::LIBXML2_ISSUE);
    ++count;
    testReferenceRule(e);
    EXPECT_EQ(size_t(73), count);
}

TEST(Issue, createModelWarning)
{
    libcellml::ModelPtr m = libcellml::Model::create();
    libcellml::IssuePtr e = libcellml::Issue::create(m);
    e->setLevel(libcellml::Issue::Level::WARNING);
    EXPECT_EQ(libcellml::Issue::Cause::MODEL, e->cause());
    EXPECT_EQ(libcellml::Issue::Level::WARNING, e->level());
}

TEST(Issue, createComponemntWarning)
{
    libcellml::ComponentPtr c = libcellml::Component::create();
    libcellml::IssuePtr e = libcellml::Issue::create(c);
    e->setLevel(libcellml::Issue::Level::WARNING);
    EXPECT_EQ(libcellml::Issue::Cause::COMPONENT, e->cause());
    EXPECT_EQ(libcellml::Issue::Level::WARNING, e->level());
}

TEST(Issue, createVariableWarning)
{
    libcellml::VariablePtr v = libcellml::Variable::create();
    libcellml::IssuePtr e = libcellml::Issue::create(v);
    e->setLevel(libcellml::Issue::Level::WARNING);
    EXPECT_EQ(libcellml::Issue::Cause::VARIABLE, e->cause());
    EXPECT_EQ(libcellml::Issue::Level::WARNING, e->level());
}

TEST(Issue, createUnitsWarning)
{
    libcellml::UnitsPtr u = libcellml::Units::create();
    libcellml::IssuePtr e = libcellml::Issue::create(u);
    e->setLevel(libcellml::Issue::Level::WARNING);
    EXPECT_EQ(libcellml::Issue::Cause::UNITS, e->cause());
    EXPECT_EQ(libcellml::Issue::Level::WARNING, e->level());
}

TEST(Issue, createImportSourceWarning)
{
    libcellml::ImportSourcePtr i = libcellml::ImportSource::create();
    libcellml::IssuePtr e = libcellml::Issue::create(i);
    e->setLevel(libcellml::Issue::Level::WARNING);
    EXPECT_EQ(libcellml::Issue::Cause::IMPORT, e->cause());
    EXPECT_EQ(libcellml::Issue::Level::WARNING, e->level());
}

TEST(Issue, createResetWarning)
{
    libcellml::ResetPtr r = libcellml::Reset::create();
    libcellml::IssuePtr e = libcellml::Issue::create(r);
    e->setLevel(libcellml::Issue::Level::WARNING);
    EXPECT_EQ(libcellml::Issue::Cause::RESET, e->cause());
    EXPECT_EQ(libcellml::Issue::Level::WARNING, e->level());
}

TEST(Issue, isError)
{
    auto e = libcellml::Issue::create();
    e->setLevel(libcellml::Issue::Level::ERROR);
    EXPECT_EQ(e->level(), libcellml::Issue::Level::ERROR);
}

TEST(Issue, isWarning)
{
    auto e = libcellml::Issue::create();
    e->setLevel(libcellml::Issue::Level::WARNING);
    EXPECT_EQ(e->level(), libcellml::Issue::Level::WARNING);
}

TEST(Issue, isHint)
{
    auto e = libcellml::Issue::create();
    e->setLevel(libcellml::Issue::Level::HINT);
    EXPECT_EQ(e->level(), libcellml::Issue::Level::HINT);
}

TEST(Issue, isMessage)
{
    auto e = libcellml::Issue::create();
    e->setLevel(libcellml::Issue::Level::MESSAGE);
    EXPECT_EQ(e->level(), libcellml::Issue::Level::MESSAGE);
}

TEST(Issue, url)
{
    auto expectedUrl = "https://cellml-specification.readthedocs.io/en/latest/reference/formal_and_informative/specB01.html?issue=2.1.1";

    auto issue = libcellml::Issue::create();
    issue->setReferenceRule(libcellml::Issue::ReferenceRule::MODEL_NAME);
    EXPECT_EQ(expectedUrl, issue->url());
}

TEST(Issue, undefinedIssueUrl)
{
    std::string e;
    e = "";
    auto issue = libcellml::Issue::create();
    EXPECT_EQ(e, issue->url());
    EXPECT_EQ(e, issue->referenceHeading());
}

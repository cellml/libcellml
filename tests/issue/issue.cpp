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
    case libcellml::Issue::ReferenceRule::COMPONENT_CHILD:
        EXPECT_EQ("10.1.2", e->referenceHeading());
        break;
    case libcellml::Issue::ReferenceRule::COMPONENT_NAME:
        EXPECT_EQ("10.1.1", e->referenceHeading());
        break;
    case libcellml::Issue::ReferenceRule::COMPONENT_REF_CHILD:
        EXPECT_EQ("16.1.2", e->referenceHeading());
        break;
    case libcellml::Issue::ReferenceRule::COMPONENT_REF_COMPONENT_ATTRIBUTE:
        EXPECT_EQ("16.1.1", e->referenceHeading());
        break;
    case libcellml::Issue::ReferenceRule::COMPONENT_REF_ENCAPSULATION:
        EXPECT_EQ("16.1.3", e->referenceHeading());
        break;
    case libcellml::Issue::ReferenceRule::CONNECTION_COMPONENT1:
        EXPECT_EQ("17.1.1", e->referenceHeading());
        break;
    case libcellml::Issue::ReferenceRule::CONNECTION_COMPONENT2:
        EXPECT_EQ("17.1.2", e->referenceHeading());
        break;
    case libcellml::Issue::ReferenceRule::CONNECTION_UNIQUE_TRANSITIVE:
        EXPECT_EQ("17.1.3", e->referenceHeading());
        break;
    case libcellml::Issue::ReferenceRule::CONNECTION_MAP_VARIABLES:
        EXPECT_EQ("17.1.4", e->referenceHeading());
        break;
    case libcellml::Issue::ReferenceRule::DATA_REPR_IDENTIFIER_AT_LEAST_ONE_ALPHANUM:
        EXPECT_EQ("3.1.3", e->referenceHeading());
        break;
    case libcellml::Issue::ReferenceRule::DATA_REPR_IDENTIFIER_BEGIN_EURO_NUM:
        EXPECT_EQ("3.1.4", e->referenceHeading());
        break;
    case libcellml::Issue::ReferenceRule::DATA_REPR_IDENTIFIER_IDENTICAL:
        EXPECT_EQ("3.1.5", e->referenceHeading());
        break;
    case libcellml::Issue::ReferenceRule::DATA_REPR_IDENTIFIER_LATIN_ALPHANUM:
        EXPECT_EQ("3.1.2", e->referenceHeading());
        break;
    case libcellml::Issue::ReferenceRule::DATA_REPR_IDENTIFIER_UNICODE:
        EXPECT_EQ("3.1.1", e->referenceHeading());
        break;
    case libcellml::Issue::ReferenceRule::DATA_REPR_NNEG_INT_BASE10:
        EXPECT_EQ("3.2.1", e->referenceHeading());
        break;
    case libcellml::Issue::ReferenceRule::DATA_REPR_NNEG_INT_EURO_NUM:
        EXPECT_EQ("3.2.2", e->referenceHeading());
        break;
    case libcellml::Issue::ReferenceRule::ENCAPSULATION_COMPONENT_REF:
        EXPECT_EQ("15.1.1", e->referenceHeading());
        break;
    case libcellml::Issue::ReferenceRule::IMPORT_CHILD:
        EXPECT_EQ("5.1.2", e->referenceHeading());
        break;
    case libcellml::Issue::ReferenceRule::IMPORT_CIRCULAR:
        EXPECT_EQ("5.1.3", e->referenceHeading());
        break;
    case libcellml::Issue::ReferenceRule::IMPORT_COMPONENT_NAME:
        EXPECT_EQ("7.1.1", e->referenceHeading());
        break;
    case libcellml::Issue::ReferenceRule::IMPORT_COMPONENT_REF:
        EXPECT_EQ("7.1.2", e->referenceHeading());
        break;
    case libcellml::Issue::ReferenceRule::IMPORT_HREF:
        EXPECT_EQ("5.1.1", e->referenceHeading());
        break;
    case libcellml::Issue::ReferenceRule::IMPORT_UNITS_NAME:
        EXPECT_EQ("6.1.1", e->referenceHeading());
        break;
    case libcellml::Issue::ReferenceRule::IMPORT_UNITS_REF:
        EXPECT_EQ("6.1.2", e->referenceHeading());
        break;
    case libcellml::Issue::ReferenceRule::MAP_VARIABLES_IDENTICAL_UNIT_REDUCTION:
        EXPECT_EQ("16.1.3", e->referenceHeading());
        break;
    case libcellml::Issue::ReferenceRule::MAP_VARIABLES_UNIQUE:
        EXPECT_EQ("18.1.3", e->referenceHeading());
        break;
    case libcellml::Issue::ReferenceRule::MAP_VARIABLES_VARIABLE1:
        EXPECT_EQ("18.1.1", e->referenceHeading());
        break;
    case libcellml::Issue::ReferenceRule::MAP_VARIABLES_VARIABLE2:
        EXPECT_EQ("18.1.2", e->referenceHeading());
        break;
    case libcellml::Issue::ReferenceRule::MATH_CHILD:
        EXPECT_EQ("14.1.2", e->referenceHeading());
        break;
    case libcellml::Issue::ReferenceRule::MATH_CI_VARIABLE_REFERENCE:
        EXPECT_EQ("14.1.3", e->referenceHeading());
        break;
    case libcellml::Issue::ReferenceRule::MATH_CN_UNITS_ATTRIBUTE:
        EXPECT_EQ("14.1.4", e->referenceHeading());
        break;
    case libcellml::Issue::ReferenceRule::MATH_MATHML:
        EXPECT_EQ("14.1.1", e->referenceHeading());
        break;
    case libcellml::Issue::ReferenceRule::MODEL_CHILD:
        EXPECT_EQ("4.2.2", e->referenceHeading());
        break;
    case libcellml::Issue::ReferenceRule::MODEL_ELEMENT:
        EXPECT_EQ("4.1", e->referenceHeading());
        break;
    case libcellml::Issue::ReferenceRule::MODEL_MORE_THAN_ONE_ENCAPSULATION:
        EXPECT_EQ("4.2.3", e->referenceHeading());
        break;
    case libcellml::Issue::ReferenceRule::MODEL_NAME:
        EXPECT_EQ("4.2.1", e->referenceHeading());
        break;
    case libcellml::Issue::ReferenceRule::RESET_CHILD:
        EXPECT_EQ("12.1.2", e->referenceHeading());
        break;
    case libcellml::Issue::ReferenceRule::RESET_VARIABLE_REFERENCE:
        EXPECT_EQ("12.1.1.1", e->referenceHeading());
        break;
    case libcellml::Issue::ReferenceRule::RESET_TEST_VARIABLE_REFERENCE:
        EXPECT_EQ("12.1.1.1", e->referenceHeading());
        break;
    case libcellml::Issue::ReferenceRule::RESET_ORDER:
        EXPECT_EQ("12.1.1.2", e->referenceHeading());
        break;
    case libcellml::Issue::ReferenceRule::RESET_TEST_VALUE:
        EXPECT_EQ("12.1.2", e->referenceHeading());
        break;
    case libcellml::Issue::ReferenceRule::RESET_RESET_VALUE:
        EXPECT_EQ("12.1.2", e->referenceHeading());
        break;
    case libcellml::Issue::ReferenceRule::UNITS_CHILD:
        EXPECT_EQ("8.1.4", e->referenceHeading());
        break;
    case libcellml::Issue::ReferenceRule::UNITS_NAME:
        EXPECT_EQ("8.1.1", e->referenceHeading());
        break;
    case libcellml::Issue::ReferenceRule::UNITS_NAME_UNIQUE:
        EXPECT_EQ("8.1.2", e->referenceHeading());
        break;
    case libcellml::Issue::ReferenceRule::UNITS_STANDARD:
        EXPECT_EQ("8.1.3", e->referenceHeading());
        break;
    case libcellml::Issue::ReferenceRule::UNIT_OPTIONAL_ATTRIBUTE:
        EXPECT_EQ("9.1.2", e->referenceHeading());
        break;
    case libcellml::Issue::ReferenceRule::UNIT_CIRCULAR_REF:
        EXPECT_EQ("9.1.1.2", e->referenceHeading());
        break;
    case libcellml::Issue::ReferenceRule::UNIT_DIGRAPH:
        EXPECT_EQ("9.1.1.1", e->referenceHeading());
        break;
    case libcellml::Issue::ReferenceRule::UNIT_EXPONENT:
        EXPECT_EQ("9.1.2.3", e->referenceHeading());
        break;
    case libcellml::Issue::ReferenceRule::UNIT_MULTIPLIER:
        EXPECT_EQ("9.1.2.2", e->referenceHeading());
        break;
    case libcellml::Issue::ReferenceRule::UNIT_PREFIX:
        EXPECT_EQ("9.1.2.1", e->referenceHeading());
        break;
    case libcellml::Issue::ReferenceRule::UNIT_UNITS_REF:
        EXPECT_EQ("9.1.1", e->referenceHeading());
        break;
    case libcellml::Issue::ReferenceRule::VARIABLE_INITIAL_VALUE:
        EXPECT_EQ("11.1.2.2", e->referenceHeading());
        break;
    case libcellml::Issue::ReferenceRule::VARIABLE_INTERFACE:
        EXPECT_EQ("11.1.2.1", e->referenceHeading());
        break;
    case libcellml::Issue::ReferenceRule::VARIABLE_NAME:
        EXPECT_EQ("11.1.1.1", e->referenceHeading());
        break;
    case libcellml::Issue::ReferenceRule::VARIABLE_UNITS:
        EXPECT_EQ("11.1.1.2", e->referenceHeading());
        break;
    case libcellml::Issue::ReferenceRule::UNDEFINED:
        EXPECT_EQ("", e->referenceHeading());
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
    e->setReferenceRule(libcellml::Issue::ReferenceRule::COMPONENT_CHILD);
    ++count;
    testReferenceRule(e);
    e->setReferenceRule(libcellml::Issue::ReferenceRule::COMPONENT_NAME);
    ++count;
    testReferenceRule(e);
    e->setReferenceRule(libcellml::Issue::ReferenceRule::COMPONENT_REF_CHILD);
    ++count;
    testReferenceRule(e);
    e->setReferenceRule(libcellml::Issue::ReferenceRule::COMPONENT_REF_COMPONENT_ATTRIBUTE);
    ++count;
    testReferenceRule(e);
    e->setReferenceRule(libcellml::Issue::ReferenceRule::COMPONENT_REF_ENCAPSULATION);
    ++count;
    testReferenceRule(e);
    e->setReferenceRule(libcellml::Issue::ReferenceRule::CONNECTION_COMPONENT1);
    ++count;
    testReferenceRule(e);
    e->setReferenceRule(libcellml::Issue::ReferenceRule::CONNECTION_COMPONENT2);
    ++count;
    testReferenceRule(e);
    e->setReferenceRule(libcellml::Issue::ReferenceRule::CONNECTION_UNIQUE_TRANSITIVE);
    ++count;
    testReferenceRule(e);
    e->setReferenceRule(libcellml::Issue::ReferenceRule::CONNECTION_MAP_VARIABLES);
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
    e->setReferenceRule(libcellml::Issue::ReferenceRule::DATA_REPR_IDENTIFIER_LATIN_ALPHANUM);
    ++count;
    testReferenceRule(e);
    e->setReferenceRule(libcellml::Issue::ReferenceRule::DATA_REPR_IDENTIFIER_UNICODE);
    ++count;
    testReferenceRule(e);
    e->setReferenceRule(libcellml::Issue::ReferenceRule::DATA_REPR_NNEG_INT_BASE10);
    ++count;
    testReferenceRule(e);
    e->setReferenceRule(libcellml::Issue::ReferenceRule::DATA_REPR_NNEG_INT_EURO_NUM);
    ++count;
    testReferenceRule(e);
    e->setReferenceRule(libcellml::Issue::ReferenceRule::ENCAPSULATION_COMPONENT_REF);
    ++count;
    testReferenceRule(e);
    e->setReferenceRule(libcellml::Issue::ReferenceRule::IMPORT_CHILD);
    ++count;
    testReferenceRule(e);
    e->setReferenceRule(libcellml::Issue::ReferenceRule::IMPORT_CIRCULAR);
    ++count;
    testReferenceRule(e);
    e->setReferenceRule(libcellml::Issue::ReferenceRule::IMPORT_COMPONENT_NAME);
    ++count;
    testReferenceRule(e);
    e->setReferenceRule(libcellml::Issue::ReferenceRule::IMPORT_COMPONENT_REF);
    ++count;
    testReferenceRule(e);
    e->setReferenceRule(libcellml::Issue::ReferenceRule::IMPORT_HREF);
    ++count;
    testReferenceRule(e);
    e->setReferenceRule(libcellml::Issue::ReferenceRule::IMPORT_UNITS_NAME);
    ++count;
    testReferenceRule(e);
    e->setReferenceRule(libcellml::Issue::ReferenceRule::IMPORT_UNITS_REF);
    ++count;
    testReferenceRule(e);
    e->setReferenceRule(libcellml::Issue::ReferenceRule::MAP_VARIABLES_UNIQUE);
    ++count;
    testReferenceRule(e);
    e->setReferenceRule(libcellml::Issue::ReferenceRule::MAP_VARIABLES_VARIABLE1);
    ++count;
    testReferenceRule(e);
    e->setReferenceRule(libcellml::Issue::ReferenceRule::MAP_VARIABLES_VARIABLE2);
    ++count;
    testReferenceRule(e);
    e->setReferenceRule(libcellml::Issue::ReferenceRule::MODEL_CHILD);
    ++count;
    testReferenceRule(e);
    e->setReferenceRule(libcellml::Issue::ReferenceRule::MODEL_ELEMENT);
    ++count;
    testReferenceRule(e);
    e->setReferenceRule(libcellml::Issue::ReferenceRule::MODEL_MORE_THAN_ONE_ENCAPSULATION);
    ++count;
    testReferenceRule(e);
    e->setReferenceRule(libcellml::Issue::ReferenceRule::MODEL_NAME);
    ++count;
    testReferenceRule(e);
    e->setReferenceRule(libcellml::Issue::ReferenceRule::RESET_CHILD);
    ++count;
    testReferenceRule(e);
    e->setReferenceRule(libcellml::Issue::ReferenceRule::RESET_VARIABLE_REFERENCE);
    ++count;
    testReferenceRule(e);
    e->setReferenceRule(libcellml::Issue::ReferenceRule::RESET_TEST_VARIABLE_REFERENCE);
    ++count;
    testReferenceRule(e);
    e->setReferenceRule(libcellml::Issue::ReferenceRule::RESET_ORDER);
    ++count;
    testReferenceRule(e);
    e->setReferenceRule(libcellml::Issue::ReferenceRule::UNITS_CHILD);
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
    e->setReferenceRule(libcellml::Issue::ReferenceRule::UNIT_OPTIONAL_ATTRIBUTE);
    ++count;
    testReferenceRule(e);
    e->setReferenceRule(libcellml::Issue::ReferenceRule::UNIT_CIRCULAR_REF);
    ++count;
    testReferenceRule(e);
    e->setReferenceRule(libcellml::Issue::ReferenceRule::UNIT_DIGRAPH);
    ++count;
    testReferenceRule(e);
    e->setReferenceRule(libcellml::Issue::ReferenceRule::UNIT_EXPONENT);
    ++count;
    testReferenceRule(e);
    e->setReferenceRule(libcellml::Issue::ReferenceRule::UNIT_MULTIPLIER);
    ++count;
    testReferenceRule(e);
    e->setReferenceRule(libcellml::Issue::ReferenceRule::UNIT_PREFIX);
    ++count;
    testReferenceRule(e);
    e->setReferenceRule(libcellml::Issue::ReferenceRule::UNIT_UNITS_REF);
    ++count;
    testReferenceRule(e);
    e->setReferenceRule(libcellml::Issue::ReferenceRule::VARIABLE_INITIAL_VALUE);
    ++count;
    testReferenceRule(e);
    e->setReferenceRule(libcellml::Issue::ReferenceRule::VARIABLE_INTERFACE);
    ++count;
    testReferenceRule(e);
    e->setReferenceRule(libcellml::Issue::ReferenceRule::VARIABLE_NAME);
    ++count;
    testReferenceRule(e);
    e->setReferenceRule(libcellml::Issue::ReferenceRule::VARIABLE_UNITS);
    ++count;
    testReferenceRule(e);
    EXPECT_EQ(size_t(51), count);
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

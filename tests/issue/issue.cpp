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

    EXPECT_EQ(libcellml::CellmlElementType::MODEL, e->cellmlElementType());
}

TEST(Issue, createComponentIssue)
{
    libcellml::ComponentPtr c = libcellml::Component::create();
    libcellml::IssuePtr e = libcellml::Issue::create(c);

    EXPECT_EQ(libcellml::CellmlElementType::COMPONENT, e->cellmlElementType());
}

TEST(Issue, createVariableIssue)
{
    libcellml::VariablePtr v = libcellml::Variable::create();
    libcellml::IssuePtr e = libcellml::Issue::create(v);

    EXPECT_EQ(libcellml::CellmlElementType::VARIABLE, e->cellmlElementType());
}

TEST(Issue, createUnitsIssue)
{
    libcellml::UnitsPtr u = libcellml::Units::create();
    libcellml::IssuePtr e = libcellml::Issue::create(u);

    EXPECT_EQ(libcellml::CellmlElementType::UNITS, e->cellmlElementType());
}

TEST(Issue, createImportSourceIssue)
{
    libcellml::ImportSourcePtr i = libcellml::ImportSource::create();
    libcellml::IssuePtr e = libcellml::Issue::create(i);

    EXPECT_EQ(libcellml::CellmlElementType::IMPORT, e->cellmlElementType());
}

TEST(Issue, createResetIssue)
{
    libcellml::ResetPtr r = libcellml::Reset::create();
    libcellml::IssuePtr e = libcellml::Issue::create(r);

    EXPECT_EQ(libcellml::CellmlElementType::RESET, e->cellmlElementType());
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
    case libcellml::Issue::ReferenceRule::IMPORT_ATTRIBUTE:
        EXPECT_EQ("2.2", e->referenceHeading());
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
    case libcellml::Issue::ReferenceRule::UNITS_ATTRIBUTE:
        EXPECT_EQ("2.5", e->referenceHeading());
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
    case libcellml::Issue::ReferenceRule::UNIT_ATTRIBUTE:
        EXPECT_EQ("2.6", e->referenceHeading());
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
    case libcellml::Issue::ReferenceRule::COMPONENT_ATTRIBUTE:
        EXPECT_EQ("2.7", e->referenceHeading());
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
    case libcellml::Issue::ReferenceRule::VARIABLE_ATTRIBUTE:
        EXPECT_EQ("2.8", e->referenceHeading());
        break;
    case libcellml::Issue::ReferenceRule::VARIABLE_CHILD:
        EXPECT_EQ("2.8", e->referenceHeading());
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
    case libcellml::Issue::ReferenceRule::RESET_ATTRIBUTE:
        EXPECT_EQ("2.9", e->referenceHeading());
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
    case libcellml::Issue::ReferenceRule::ENCAPSULATION_ATTRIBUTE:
        EXPECT_EQ("2.13", e->referenceHeading());
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
    case libcellml::Issue::ReferenceRule::CONNECTION_ATTRIBUTE:
        EXPECT_EQ("2.15", e->referenceHeading());
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
    case libcellml::Issue::ReferenceRule::MAP_VARIABLES_ATTRIBUTE:
        EXPECT_EQ("2.16", e->referenceHeading());
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
    case libcellml::Issue::ReferenceRule::XML:
        EXPECT_EQ("1.2.1", e->referenceHeading());
        break;
    case libcellml::Issue::ReferenceRule::MAP_VARIABLES_AVAILABLE_INTERFACE:
        EXPECT_EQ("3.10.8", e->referenceHeading());
        break;
    case libcellml::Issue::ReferenceRule::ANALYSER_VARIABLE_INITIALISED_MORE_THAN_ONCE:
    case libcellml::Issue::ReferenceRule::ANALYSER_VARIABLE_NON_CONSTANT_INITIALISATION:
    case libcellml::Issue::ReferenceRule::ANALYSER_VOI_INITIALISED:
    case libcellml::Issue::ReferenceRule::ANALYSER_VOI_SEVERAL:
    case libcellml::Issue::ReferenceRule::ANALYSER_ODE_NOT_FIRST_ORDER:
    case libcellml::Issue::ReferenceRule::ANALYSER_VARIABLE_UNUSED:
    case libcellml::Issue::ReferenceRule::ANALYSER_STATE_NOT_INITIALISED:
    case libcellml::Issue::ReferenceRule::ANALYSER_VARIABLE_COMPUTED_MORE_THAN_ONCE:
    case libcellml::Issue::ReferenceRule::ANALYSER_EXTERNAL_VARIABLE_DIFFERENT_MODEL:
    case libcellml::Issue::ReferenceRule::ANALYSER_EXTERNAL_VARIABLE_VOI:
    case libcellml::Issue::ReferenceRule::ANALYSER_EXTERNAL_VARIABLE_USE_PRIMARY_VARIABLE:
    case libcellml::Issue::ReferenceRule::UNSPECIFIED:
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
    e->setReferenceRule(libcellml::Issue::ReferenceRule::IMPORT_ATTRIBUTE);
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
    e->setReferenceRule(libcellml::Issue::ReferenceRule::UNITS_ATTRIBUTE);
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
    e->setReferenceRule(libcellml::Issue::ReferenceRule::UNIT_ATTRIBUTE);
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
    e->setReferenceRule(libcellml::Issue::ReferenceRule::COMPONENT_ATTRIBUTE);
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
    e->setReferenceRule(libcellml::Issue::ReferenceRule::VARIABLE_ATTRIBUTE);
    ++count;
    testReferenceRule(e);
    e->setReferenceRule(libcellml::Issue::ReferenceRule::VARIABLE_CHILD);
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
    e->setReferenceRule(libcellml::Issue::ReferenceRule::RESET_ATTRIBUTE);
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
    e->setReferenceRule(libcellml::Issue::ReferenceRule::ENCAPSULATION_ATTRIBUTE);
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
    e->setReferenceRule(libcellml::Issue::ReferenceRule::CONNECTION_ATTRIBUTE);
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
    e->setReferenceRule(libcellml::Issue::ReferenceRule::MAP_VARIABLES_ATTRIBUTE);
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
    e->setReferenceRule(libcellml::Issue::ReferenceRule::XML);
    ++count;
    testReferenceRule(e);
    e->setReferenceRule(libcellml::Issue::ReferenceRule::UNSPECIFIED);
    ++count;
    testReferenceRule(e);
    EXPECT_EQ(size_t(84), count);
}

TEST(Issue, createModelWarning)
{
    libcellml::ModelPtr m = libcellml::Model::create();
    libcellml::IssuePtr e = libcellml::Issue::create(m);
    e->setLevel(libcellml::Issue::Level::WARNING);
    EXPECT_EQ(libcellml::CellmlElementType::MODEL, e->cellmlElementType());
    EXPECT_EQ(libcellml::Issue::Level::WARNING, e->level());
}

TEST(Issue, createComponentWarning)
{
    libcellml::ComponentPtr c = libcellml::Component::create();
    libcellml::IssuePtr e = libcellml::Issue::create(c);
    e->setLevel(libcellml::Issue::Level::WARNING);
    EXPECT_EQ(libcellml::CellmlElementType::COMPONENT, e->cellmlElementType());
    EXPECT_EQ(libcellml::Issue::Level::WARNING, e->level());
}

TEST(Issue, createVariableWarning)
{
    libcellml::VariablePtr v = libcellml::Variable::create();
    libcellml::IssuePtr e = libcellml::Issue::create(v);
    e->setLevel(libcellml::Issue::Level::WARNING);
    EXPECT_EQ(libcellml::CellmlElementType::VARIABLE, e->cellmlElementType());
    EXPECT_EQ(libcellml::Issue::Level::WARNING, e->level());
}

TEST(Issue, createUnitsWarning)
{
    libcellml::UnitsPtr u = libcellml::Units::create();
    libcellml::IssuePtr e = libcellml::Issue::create(u);
    e->setLevel(libcellml::Issue::Level::WARNING);
    EXPECT_EQ(libcellml::CellmlElementType::UNITS, e->cellmlElementType());
    EXPECT_EQ(libcellml::Issue::Level::WARNING, e->level());
}

TEST(Issue, createUnitWarning)
{
    libcellml::UnitsPtr u = libcellml::Units::create();
    u->addUnit("second");
    libcellml::IssuePtr e = libcellml::Issue::create(libcellml::Unit::create(u, 0));
    e->setLevel(libcellml::Issue::Level::WARNING);
    EXPECT_EQ(libcellml::CellmlElementType::UNIT, e->cellmlElementType());
    EXPECT_EQ(libcellml::Issue::Level::WARNING, e->level());
}

TEST(Issue, createImportSourceWarning)
{
    libcellml::ImportSourcePtr i = libcellml::ImportSource::create();
    libcellml::IssuePtr e = libcellml::Issue::create(i);
    e->setLevel(libcellml::Issue::Level::WARNING);
    EXPECT_EQ(libcellml::CellmlElementType::IMPORT, e->cellmlElementType());
    EXPECT_EQ(libcellml::Issue::Level::WARNING, e->level());
}

TEST(Issue, createResetWarning)
{
    libcellml::ResetPtr r = libcellml::Reset::create();
    libcellml::IssuePtr e = libcellml::Issue::create(r);
    e->setLevel(libcellml::Issue::Level::WARNING);
    EXPECT_EQ(libcellml::CellmlElementType::RESET, e->cellmlElementType());
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

TEST(Issue, componentValid)
{
    auto issue = libcellml::Issue::create();
    auto component = libcellml::Component::create("component");

    issue->setLevel(libcellml::Issue::Level::MESSAGE);
    issue->setDescription("Not a real component");
    issue->setComponent(component);

    EXPECT_EQ(libcellml::Issue::Level::MESSAGE, issue->level());
    EXPECT_EQ("Not a real component", issue->description());
    EXPECT_EQ(component, issue->component());
}

TEST(Issue, componentInvalid)
{
    auto issue = libcellml::Issue::create();
    libcellml::ComponentPtr component;

    issue->setLevel(libcellml::Issue::Level::MESSAGE);
    issue->setDescription("Not a real component");
    issue->setComponent(component);

    EXPECT_EQ(libcellml::Issue::Level::MESSAGE, issue->level());
    EXPECT_EQ("Not a real component", issue->description());
    EXPECT_EQ(nullptr, issue->component());
}

TEST(Issue, setGetItems)
{
    auto model = libcellml::Model::create("model");
    auto component = libcellml::Component::create("component");
    auto variable1 = libcellml::Variable::create("variable1");
    auto variable2 = libcellml::Variable::create("variable2");
    auto pair = std::make_pair(variable1, variable2);
    auto import = libcellml::ImportSource::create();
    auto reset = libcellml::Reset::create();
    auto units = libcellml::Units::create();
    units->addUnit("second");
    auto issue = libcellml::Issue::create();

    std::any item = component;

    issue->setComponent(component);
    EXPECT_EQ(component, issue->component());
    EXPECT_EQ(libcellml::CellmlElementType::COMPONENT, issue->cellmlElementType());
    EXPECT_EQ(component, std::any_cast<libcellml::ComponentPtr>(issue->item()));

    issue->setComponentRef(component);
    EXPECT_EQ(component, issue->componentRef());
    EXPECT_EQ(libcellml::CellmlElementType::COMPONENT_REF, issue->cellmlElementType());
    EXPECT_EQ(component, std::any_cast<libcellml::ComponentPtr>(issue->item()));

    issue->setConnection(variable1, variable2);
    EXPECT_EQ(variable1, issue->connection()->variable1());
    EXPECT_EQ(variable2, issue->connection()->variable2());
    EXPECT_EQ(libcellml::CellmlElementType::CONNECTION, issue->cellmlElementType());
    EXPECT_EQ(variable1, std::any_cast<libcellml::VariablePairPtr>(issue->item())->variable1());
    EXPECT_EQ(variable2, std::any_cast<libcellml::VariablePairPtr>(issue->item())->variable2());

    issue->setEncapsulation(model);
    EXPECT_EQ(model, issue->encapsulation());
    EXPECT_EQ(libcellml::CellmlElementType::ENCAPSULATION, issue->cellmlElementType());
    EXPECT_EQ(model, std::any_cast<libcellml::ModelPtr>(issue->item()));

    issue->setImportSource(import);
    EXPECT_EQ(import, issue->importSource());
    EXPECT_EQ(libcellml::CellmlElementType::IMPORT, issue->cellmlElementType());
    EXPECT_EQ(import, std::any_cast<libcellml::ImportSourcePtr>(issue->item()));

    issue->setMapVariables(variable1, variable2);
    EXPECT_EQ(variable1, issue->mapVariables()->variable1());
    EXPECT_EQ(variable2, issue->mapVariables()->variable2());
    EXPECT_EQ(libcellml::CellmlElementType::MAP_VARIABLES, issue->cellmlElementType());
    EXPECT_EQ(variable1, std::any_cast<libcellml::VariablePairPtr>(issue->item())->variable1());
    EXPECT_EQ(variable2, std::any_cast<libcellml::VariablePairPtr>(issue->item())->variable2());

    issue->setMath(component);
    EXPECT_EQ(component, issue->math());
    EXPECT_EQ(libcellml::CellmlElementType::MATH, issue->cellmlElementType());
    EXPECT_EQ(component, std::any_cast<libcellml::ComponentPtr>(issue->item()));

    issue->setModel(model);
    EXPECT_EQ(model, issue->model());
    EXPECT_EQ(libcellml::CellmlElementType::MODEL, issue->cellmlElementType());
    EXPECT_EQ(model, std::any_cast<libcellml::ModelPtr>(issue->item()));

    issue->setReset(reset);
    EXPECT_EQ(reset, issue->reset());
    EXPECT_EQ(libcellml::CellmlElementType::RESET, issue->cellmlElementType());
    EXPECT_EQ(reset, std::any_cast<libcellml::ResetPtr>(issue->item()));

    issue->setResetValue(reset);
    EXPECT_EQ(reset, issue->resetValue());
    EXPECT_EQ(libcellml::CellmlElementType::RESET_VALUE, issue->cellmlElementType());
    EXPECT_EQ(reset, std::any_cast<libcellml::ResetPtr>(issue->item()));

    issue->setTestValue(reset);
    EXPECT_EQ(reset, issue->testValue());
    EXPECT_EQ(libcellml::CellmlElementType::TEST_VALUE, issue->cellmlElementType());
    EXPECT_EQ(reset, std::any_cast<libcellml::ResetPtr>(issue->item()));

    issue->setUnit(libcellml::Unit::create(units, 0));
    EXPECT_EQ(units, issue->unit()->units());
    EXPECT_EQ(size_t(0), issue->unit()->index());
    EXPECT_EQ(libcellml::CellmlElementType::UNIT, issue->cellmlElementType());
    EXPECT_EQ(units, std::any_cast<libcellml::UnitPtr>(issue->item())->units());
    EXPECT_EQ(size_t(0), std::any_cast<libcellml::UnitPtr>(issue->item())->index());

    issue->setUnits(units);
    EXPECT_EQ(units, issue->units());
    EXPECT_EQ(libcellml::CellmlElementType::UNITS, issue->cellmlElementType());
    EXPECT_EQ(units, std::any_cast<libcellml::UnitsPtr>(issue->item()));

    issue->setVariable(variable1);
    EXPECT_EQ(variable1, issue->variable());
    EXPECT_EQ(libcellml::CellmlElementType::VARIABLE, issue->cellmlElementType());
    EXPECT_EQ(variable1, std::any_cast<libcellml::VariablePtr>(issue->item()));

    issue->setItem(libcellml::CellmlElementType::COMPONENT, item);
    EXPECT_EQ(libcellml::CellmlElementType::COMPONENT, issue->cellmlElementType());
    EXPECT_EQ(component, std::any_cast<libcellml::ComponentPtr>(issue->item()));
    EXPECT_EQ(component, issue->component());
}

TEST(Issue, createCorrectType)
{
    auto model = libcellml::Model::create("model");
    auto component = libcellml::Component::create("component");
    auto variable1 = libcellml::Variable::create("variable1");
    auto variable2 = libcellml::Variable::create("variable2");
    auto import = libcellml::ImportSource::create();
    auto reset = libcellml::Reset::create();
    auto units = libcellml::Units::create();
    units->addUnit("second");
    auto unit = libcellml::Unit::create(units, 0);
    auto pair = libcellml::VariablePair::create(variable1, variable2);

    EXPECT_NE(nullptr, libcellml::Issue::create(component));
    EXPECT_NE(nullptr, libcellml::Issue::create(component, libcellml::CellmlElementType::COMPONENT_REF));
    EXPECT_NE(nullptr, libcellml::Issue::create(component, libcellml::CellmlElementType::MATH));
    EXPECT_NE(nullptr, libcellml::Issue::create(variable1));
    EXPECT_NE(nullptr, libcellml::Issue::create(model));
    EXPECT_NE(nullptr, libcellml::Issue::create(model, libcellml::CellmlElementType::ENCAPSULATION));
    EXPECT_NE(nullptr, libcellml::Issue::create(import));
    EXPECT_NE(nullptr, libcellml::Issue::create(reset));
    EXPECT_NE(nullptr, libcellml::Issue::create(reset, libcellml::CellmlElementType::RESET_VALUE));
    EXPECT_NE(nullptr, libcellml::Issue::create(reset, libcellml::CellmlElementType::TEST_VALUE));
    EXPECT_NE(nullptr, libcellml::Issue::create(units));
    EXPECT_NE(nullptr, libcellml::Issue::create(unit));
    EXPECT_NE(nullptr, libcellml::Issue::create(pair, libcellml::CellmlElementType::CONNECTION));
    EXPECT_NE(nullptr, libcellml::Issue::create(pair));
}

TEST(Issue, createMismatchedTypeReturnsNull)
{
    auto model = libcellml::Model::create("model");
    auto component = libcellml::Component::create("component");
    auto variable1 = libcellml::Variable::create("variable1");
    auto variable2 = libcellml::Variable::create("variable2");
    auto import = libcellml::ImportSource::create();
    auto reset = libcellml::Reset::create();
    auto units = libcellml::Units::create();
    units->addUnit("second");
    auto unit = libcellml::Unit::create(units, 0);

    EXPECT_EQ(nullptr, libcellml::Issue::create(component, libcellml::CellmlElementType::MODEL));
    EXPECT_EQ(nullptr, libcellml::Issue::create(model, libcellml::CellmlElementType::MATH));
    EXPECT_EQ(nullptr, libcellml::Issue::create(reset, libcellml::CellmlElementType::IMPORT));
    EXPECT_EQ(nullptr, libcellml::Issue::create(libcellml::VariablePair::create(variable1, variable2), libcellml::CellmlElementType::VARIABLE));
}

TEST(Issue, createIssueWithNullptr)
{
    libcellml::ModelPtr model;
    libcellml::ComponentPtr component;
    libcellml::ResetPtr reset;
    libcellml::VariablePairPtr pair1 = libcellml::VariablePair::create(nullptr, nullptr);
    libcellml::VariablePairPtr pair2 = libcellml::VariablePair::create(nullptr, libcellml::Variable::create("v1"));
    libcellml::VariablePairPtr pair3 = libcellml::VariablePair::create(libcellml::Variable::create("v2"), nullptr);
    libcellml::VariablePtr variable;
    libcellml::UnitsPtr units;
    libcellml::UnitPtr unit = libcellml::Unit::create(nullptr, 0);
    libcellml::ImportSourcePtr import;

    EXPECT_EQ(nullptr, libcellml::Issue::create(component));
    EXPECT_EQ(nullptr, libcellml::Issue::create(model));
    EXPECT_EQ(nullptr, libcellml::Issue::create(reset));
    EXPECT_EQ(nullptr, libcellml::Issue::create(pair1));
    EXPECT_EQ(nullptr, libcellml::Issue::create(pair2));
    EXPECT_EQ(nullptr, libcellml::Issue::create(pair3));
    EXPECT_EQ(nullptr, libcellml::Issue::create(units));
    EXPECT_EQ(nullptr, libcellml::Issue::create(unit));
    EXPECT_EQ(nullptr, libcellml::Issue::create(variable));
    EXPECT_EQ(nullptr, libcellml::Issue::create(import));
}

TEST(Issue, setItemWithNullptr)
{
    libcellml::ModelPtr model;
    libcellml::ComponentPtr component;
    libcellml::ResetPtr reset;
    libcellml::VariablePairPtr pair1 = libcellml::VariablePair::create(nullptr, nullptr);
    libcellml::VariablePairPtr pair2 = libcellml::VariablePair::create(nullptr, libcellml::Variable::create("v1"));
    libcellml::VariablePairPtr pair3 = libcellml::VariablePair::create(libcellml::Variable::create("v2"), nullptr);
    libcellml::VariablePtr variable;
    libcellml::UnitsPtr units;
    libcellml::UnitPtr unit = libcellml::Unit::create(nullptr, 0);
    libcellml::ImportSourcePtr import;

    auto issue = libcellml::Issue::create();

    issue->setItem(libcellml::CellmlElementType::COMPONENT, component);
    EXPECT_EQ(libcellml::CellmlElementType::COMPONENT, issue->cellmlElementType());

    issue->setItem(libcellml::CellmlElementType::CONNECTION, pair1);
    EXPECT_EQ(libcellml::CellmlElementType::CONNECTION, issue->cellmlElementType());

    issue->setItem(libcellml::CellmlElementType::CONNECTION, pair2);
    EXPECT_EQ(libcellml::CellmlElementType::CONNECTION, issue->cellmlElementType());

    issue->setItem(libcellml::CellmlElementType::CONNECTION, pair3);
    EXPECT_EQ(libcellml::CellmlElementType::CONNECTION, issue->cellmlElementType());

    issue->setItem(libcellml::CellmlElementType::ENCAPSULATION, model);
    EXPECT_EQ(libcellml::CellmlElementType::ENCAPSULATION, issue->cellmlElementType());

    issue->setItem(libcellml::CellmlElementType::IMPORT, import);
    EXPECT_EQ(libcellml::CellmlElementType::IMPORT, issue->cellmlElementType());

    issue->setItem(libcellml::CellmlElementType::RESET, reset);
    EXPECT_EQ(libcellml::CellmlElementType::RESET, issue->cellmlElementType());

    issue->setItem(libcellml::CellmlElementType::UNIT, unit);
    EXPECT_EQ(libcellml::CellmlElementType::UNIT, issue->cellmlElementType());

    issue->setItem(libcellml::CellmlElementType::UNITS, units);
    EXPECT_EQ(libcellml::CellmlElementType::UNITS, issue->cellmlElementType());

    issue->setItem(libcellml::CellmlElementType::VARIABLE, variable);
    EXPECT_EQ(libcellml::CellmlElementType::VARIABLE, issue->cellmlElementType());
}

TEST(Issue, getMismatchedTypeReturnsNullComponent)
{
    auto component = libcellml::Component::create("component");
    auto issue = libcellml::Issue::create();

    issue->setComponent(component);
    EXPECT_NE(nullptr, issue->component());
    EXPECT_EQ(nullptr, issue->componentRef());
    EXPECT_EQ(nullptr, issue->connection());
    EXPECT_EQ(nullptr, issue->encapsulation());
    EXPECT_EQ(nullptr, issue->importSource());
    EXPECT_EQ(nullptr, issue->mapVariables());
    EXPECT_EQ(nullptr, issue->math());
    EXPECT_EQ(nullptr, issue->model());
    EXPECT_EQ(nullptr, issue->reset());
    EXPECT_EQ(nullptr, issue->resetValue());
    EXPECT_EQ(nullptr, issue->testValue());
    EXPECT_EQ(nullptr, issue->unit());
    EXPECT_EQ(nullptr, issue->units());
    EXPECT_EQ(nullptr, issue->variable());

    issue->setComponent(nullptr);
    EXPECT_EQ(nullptr, issue->component());
}

TEST(Issue, getMismatchedTypeReturnsNullComponentRef)
{
    auto component = libcellml::Component::create("component");
    auto issue = libcellml::Issue::create();

    issue->setComponentRef(component);
    EXPECT_EQ(nullptr, issue->component());
    EXPECT_NE(nullptr, issue->componentRef());
    EXPECT_EQ(nullptr, issue->connection());
    EXPECT_EQ(nullptr, issue->encapsulation());
    EXPECT_EQ(nullptr, issue->importSource());
    EXPECT_EQ(nullptr, issue->mapVariables());
    EXPECT_EQ(nullptr, issue->math());
    EXPECT_EQ(nullptr, issue->model());
    EXPECT_EQ(nullptr, issue->reset());
    EXPECT_EQ(nullptr, issue->resetValue());
    EXPECT_EQ(nullptr, issue->testValue());
    EXPECT_EQ(nullptr, issue->unit());
    EXPECT_EQ(nullptr, issue->units());
    EXPECT_EQ(nullptr, issue->variable());

    issue->setComponentRef(nullptr);
    EXPECT_EQ(nullptr, issue->componentRef());
}

TEST(Issue, getMismatchedTypeReturnsNullConnection)
{
    auto variable1 = libcellml::Variable::create("variable1");
    auto variable2 = libcellml::Variable::create("variable2");
    auto pair = libcellml::VariablePair::create(variable1, variable2);
    auto issue = libcellml::Issue::create();
    issue->setConnection(pair);
    EXPECT_EQ(nullptr, issue->component());
    EXPECT_EQ(nullptr, issue->componentRef());
    EXPECT_NE(nullptr, issue->connection()->variable1());
    EXPECT_EQ(nullptr, issue->encapsulation());
    EXPECT_EQ(nullptr, issue->importSource());
    EXPECT_EQ(nullptr, issue->mapVariables());
    EXPECT_EQ(nullptr, issue->math());
    EXPECT_EQ(nullptr, issue->model());
    EXPECT_EQ(nullptr, issue->reset());
    EXPECT_EQ(nullptr, issue->resetValue());
    EXPECT_EQ(nullptr, issue->testValue());
    EXPECT_EQ(nullptr, issue->unit());
    EXPECT_EQ(nullptr, issue->units());
    EXPECT_EQ(nullptr, issue->variable());

    issue->setConnection(nullptr, nullptr);
    EXPECT_EQ(nullptr, issue->connection());
    EXPECT_EQ(nullptr, issue->connection());
}

TEST(Issue, getMismatchedTypeReturnsNullEncapsulation)
{
    auto model = libcellml::Model::create("model");
    auto issue = libcellml::Issue::create();
    issue->setEncapsulation(model);

    EXPECT_EQ(nullptr, issue->component());
    EXPECT_EQ(nullptr, issue->componentRef());
    EXPECT_EQ(nullptr, issue->connection());
    EXPECT_NE(nullptr, issue->encapsulation());
    EXPECT_EQ(nullptr, issue->importSource());
    EXPECT_EQ(nullptr, issue->mapVariables());
    EXPECT_EQ(nullptr, issue->math());
    EXPECT_EQ(nullptr, issue->model());
    EXPECT_EQ(nullptr, issue->reset());
    EXPECT_EQ(nullptr, issue->resetValue());
    EXPECT_EQ(nullptr, issue->testValue());
    EXPECT_EQ(nullptr, issue->unit());
    EXPECT_EQ(nullptr, issue->units());
    EXPECT_EQ(nullptr, issue->variable());

    issue->setEncapsulation(nullptr);
    EXPECT_EQ(nullptr, issue->encapsulation());
}

TEST(Issue, getMismatchedTypeReturnsNullImportSource)
{
    auto import = libcellml::ImportSource::create();
    auto issue = libcellml::Issue::create();
    issue->setImportSource(import);

    EXPECT_EQ(nullptr, issue->component());
    EXPECT_EQ(nullptr, issue->componentRef());
    EXPECT_EQ(nullptr, issue->connection());
    EXPECT_EQ(nullptr, issue->encapsulation());
    EXPECT_NE(nullptr, issue->importSource());
    EXPECT_EQ(nullptr, issue->mapVariables());
    EXPECT_EQ(nullptr, issue->math());
    EXPECT_EQ(nullptr, issue->model());
    EXPECT_EQ(nullptr, issue->reset());
    EXPECT_EQ(nullptr, issue->resetValue());
    EXPECT_EQ(nullptr, issue->testValue());
    EXPECT_EQ(nullptr, issue->unit());
    EXPECT_EQ(nullptr, issue->units());
    EXPECT_EQ(nullptr, issue->variable());

    issue->setImportSource(nullptr);
    EXPECT_EQ(nullptr, issue->importSource());
}

TEST(Issue, getMismatchedTypeReturnsNullMapVariables)
{
    auto variable1 = libcellml::Variable::create("variable1");
    auto variable2 = libcellml::Variable::create("variable2");
    auto pair = libcellml::VariablePair::create(variable1, variable2);
    auto issue = libcellml::Issue::create();
    issue->setMapVariables(pair);

    EXPECT_EQ(nullptr, issue->component());
    EXPECT_EQ(nullptr, issue->componentRef());
    EXPECT_EQ(nullptr, issue->connection());
    EXPECT_EQ(nullptr, issue->encapsulation());
    EXPECT_EQ(nullptr, issue->importSource());
    EXPECT_NE(nullptr, issue->mapVariables());
    EXPECT_EQ(nullptr, issue->math());
    EXPECT_EQ(nullptr, issue->model());
    EXPECT_EQ(nullptr, issue->reset());
    EXPECT_EQ(nullptr, issue->resetValue());
    EXPECT_EQ(nullptr, issue->testValue());
    EXPECT_EQ(nullptr, issue->unit());
    EXPECT_EQ(nullptr, issue->units());
    EXPECT_EQ(nullptr, issue->variable());

    issue->setMapVariables(nullptr, nullptr);
    EXPECT_EQ(nullptr, issue->mapVariables());
    EXPECT_EQ(nullptr, issue->mapVariables());
}

TEST(Issue, getMismatchedTypeReturnsNullMath)
{
    auto component = libcellml::Component::create("component");
    auto issue = libcellml::Issue::create();
    issue->setMath(component);
    EXPECT_EQ(nullptr, issue->component());
    EXPECT_EQ(nullptr, issue->componentRef());
    EXPECT_EQ(nullptr, issue->connection());
    EXPECT_EQ(nullptr, issue->encapsulation());
    EXPECT_EQ(nullptr, issue->importSource());
    EXPECT_EQ(nullptr, issue->mapVariables());
    EXPECT_NE(nullptr, issue->math());
    EXPECT_EQ(nullptr, issue->model());
    EXPECT_EQ(nullptr, issue->reset());
    EXPECT_EQ(nullptr, issue->resetValue());
    EXPECT_EQ(nullptr, issue->testValue());
    EXPECT_EQ(nullptr, issue->unit());
    EXPECT_EQ(nullptr, issue->units());
    EXPECT_EQ(nullptr, issue->variable());

    issue->setMath(nullptr);
    EXPECT_EQ(nullptr, issue->math());
}

TEST(Issue, getMismatchedTypeReturnsNullModel)
{
    auto model = libcellml::Model::create("model");
    auto issue = libcellml::Issue::create();
    issue->setModel(model);

    EXPECT_EQ(nullptr, issue->component());
    EXPECT_EQ(nullptr, issue->componentRef());
    EXPECT_EQ(nullptr, issue->connection());
    EXPECT_EQ(nullptr, issue->encapsulation());
    EXPECT_EQ(nullptr, issue->importSource());
    EXPECT_EQ(nullptr, issue->mapVariables());
    EXPECT_EQ(nullptr, issue->math());
    EXPECT_NE(nullptr, issue->model());
    EXPECT_EQ(nullptr, issue->reset());
    EXPECT_EQ(nullptr, issue->resetValue());
    EXPECT_EQ(nullptr, issue->testValue());
    EXPECT_EQ(nullptr, issue->unit());
    EXPECT_EQ(nullptr, issue->units());
    EXPECT_EQ(nullptr, issue->variable());

    issue->setModel(nullptr);
    EXPECT_EQ(nullptr, issue->model());
}

TEST(Issue, getMismatchedTypeReturnsNullReset)
{
    auto reset = libcellml::Reset::create();
    auto issue = libcellml::Issue::create();
    issue->setReset(reset);

    EXPECT_EQ(nullptr, issue->component());
    EXPECT_EQ(nullptr, issue->componentRef());
    EXPECT_EQ(nullptr, issue->connection());
    EXPECT_EQ(nullptr, issue->encapsulation());
    EXPECT_EQ(nullptr, issue->importSource());
    EXPECT_EQ(nullptr, issue->mapVariables());
    EXPECT_EQ(nullptr, issue->math());
    EXPECT_EQ(nullptr, issue->model());
    EXPECT_NE(nullptr, issue->reset());
    EXPECT_EQ(nullptr, issue->resetValue());
    EXPECT_EQ(nullptr, issue->testValue());
    EXPECT_EQ(nullptr, issue->unit());
    EXPECT_EQ(nullptr, issue->units());
    EXPECT_EQ(nullptr, issue->variable());

    issue->setReset(nullptr);
    EXPECT_EQ(nullptr, issue->reset());
}

TEST(Issue, getMismatchedTypeReturnsNullResetValue)
{
    auto reset = libcellml::Reset::create();
    auto issue = libcellml::Issue::create();
    issue->setResetValue(reset);

    EXPECT_EQ(nullptr, issue->component());
    EXPECT_EQ(nullptr, issue->componentRef());
    EXPECT_EQ(nullptr, issue->connection());
    EXPECT_EQ(nullptr, issue->encapsulation());
    EXPECT_EQ(nullptr, issue->importSource());
    EXPECT_EQ(nullptr, issue->mapVariables());
    EXPECT_EQ(nullptr, issue->math());
    EXPECT_EQ(nullptr, issue->model());
    EXPECT_EQ(nullptr, issue->reset());
    EXPECT_NE(nullptr, issue->resetValue());
    EXPECT_EQ(nullptr, issue->testValue());
    EXPECT_EQ(nullptr, issue->unit());
    EXPECT_EQ(nullptr, issue->units());
    EXPECT_EQ(nullptr, issue->variable());

    issue->setResetValue(nullptr);
    EXPECT_EQ(nullptr, issue->resetValue());
}

TEST(Issue, getMismatchedTypeReturnsNullTestValue)
{
    auto reset = libcellml::Reset::create();
    auto issue = libcellml::Issue::create();
    issue->setTestValue(reset);

    EXPECT_EQ(nullptr, issue->component());
    EXPECT_EQ(nullptr, issue->componentRef());
    EXPECT_EQ(nullptr, issue->connection());
    EXPECT_EQ(nullptr, issue->encapsulation());
    EXPECT_EQ(nullptr, issue->importSource());
    EXPECT_EQ(nullptr, issue->mapVariables());
    EXPECT_EQ(nullptr, issue->math());
    EXPECT_EQ(nullptr, issue->model());
    EXPECT_EQ(nullptr, issue->reset());
    EXPECT_EQ(nullptr, issue->resetValue());
    EXPECT_NE(nullptr, issue->testValue());
    EXPECT_EQ(nullptr, issue->unit());
    EXPECT_EQ(nullptr, issue->units());
    EXPECT_EQ(nullptr, issue->variable());

    issue->setTestValue(nullptr);
    EXPECT_EQ(nullptr, issue->testValue());
}

TEST(Issue, getMismatchedTypeReturnsUnit)
{
    auto units = libcellml::Units::create();
    units->addUnit("second");
    auto unit = libcellml::Unit::create(units, 0);
    auto issue = libcellml::Issue::create();
    issue->setUnit(unit);

    EXPECT_EQ(nullptr, issue->component());
    EXPECT_EQ(nullptr, issue->componentRef());
    EXPECT_EQ(nullptr, issue->connection());
    EXPECT_EQ(nullptr, issue->encapsulation());
    EXPECT_EQ(nullptr, issue->importSource());
    EXPECT_EQ(nullptr, issue->mapVariables());
    EXPECT_EQ(nullptr, issue->math());
    EXPECT_EQ(nullptr, issue->model());
    EXPECT_EQ(nullptr, issue->reset());
    EXPECT_EQ(nullptr, issue->resetValue());
    EXPECT_EQ(nullptr, issue->testValue());
    EXPECT_NE(nullptr, issue->unit()->units());
    EXPECT_EQ(nullptr, issue->units());
    EXPECT_EQ(nullptr, issue->variable());

    issue->setUnit(libcellml::Unit::create(nullptr, size_t(0)));
    EXPECT_EQ(nullptr, issue->unit());
}

TEST(Issue, getMismatchedTypeReturnsNullUnits)
{
    auto units = libcellml::Units::create();
    auto issue = libcellml::Issue::create();
    issue->setUnits(units);

    EXPECT_EQ(nullptr, issue->component());
    EXPECT_EQ(nullptr, issue->componentRef());
    EXPECT_EQ(nullptr, issue->connection());
    EXPECT_EQ(nullptr, issue->encapsulation());
    EXPECT_EQ(nullptr, issue->importSource());
    EXPECT_EQ(nullptr, issue->mapVariables());
    EXPECT_EQ(nullptr, issue->math());
    EXPECT_EQ(nullptr, issue->model());
    EXPECT_EQ(nullptr, issue->reset());
    EXPECT_EQ(nullptr, issue->resetValue());
    EXPECT_EQ(nullptr, issue->testValue());
    EXPECT_EQ(nullptr, issue->unit());
    EXPECT_NE(nullptr, issue->units());
    EXPECT_EQ(nullptr, issue->variable());

    issue->setUnits(nullptr);
    EXPECT_EQ(nullptr, issue->units());
}

TEST(Issue, getMismatchedTypeReturnsNullVariable)
{
    auto variable = libcellml::Variable::create("variable");
    auto issue = libcellml::Issue::create();
    issue->setVariable(variable);
    EXPECT_EQ(nullptr, issue->component());
    EXPECT_EQ(nullptr, issue->componentRef());
    EXPECT_EQ(nullptr, issue->connection());
    EXPECT_EQ(nullptr, issue->encapsulation());
    EXPECT_EQ(nullptr, issue->importSource());
    EXPECT_EQ(nullptr, issue->mapVariables());
    EXPECT_EQ(nullptr, issue->math());
    EXPECT_EQ(nullptr, issue->model());
    EXPECT_EQ(nullptr, issue->reset());
    EXPECT_EQ(nullptr, issue->resetValue());
    EXPECT_EQ(nullptr, issue->testValue());
    EXPECT_EQ(nullptr, issue->unit());
    EXPECT_EQ(nullptr, issue->units());
    EXPECT_NE(nullptr, issue->variable());

    issue->setVariable(nullptr);
    EXPECT_EQ(nullptr, issue->variable());
}

TEST(Issue, clearStoredItem)
{
    auto model = libcellml::Model::create();
    auto issue = libcellml::Issue::create(model);
    EXPECT_EQ(model, issue->model());
    EXPECT_EQ(libcellml::CellmlElementType::MODEL, issue->cellmlElementType());

    // Clear by setting to nullptr.
    issue->setModel(nullptr);
    EXPECT_EQ(nullptr, issue->model());
    EXPECT_EQ(libcellml::CellmlElementType::UNDEFINED, issue->cellmlElementType());

    issue->setModel(model);
    EXPECT_EQ(model, issue->model());
    EXPECT_EQ(libcellml::CellmlElementType::MODEL, issue->cellmlElementType());

    // Clear by calling the clear function.
    issue->clear();
    EXPECT_EQ(nullptr, issue->model());
    EXPECT_EQ(libcellml::CellmlElementType::UNDEFINED, issue->cellmlElementType());
}

TEST(Issue, crossClearStoredItem)
{
    auto model = libcellml::Model::create();
    auto issue = libcellml::Issue::create(model);
    EXPECT_EQ(model, issue->model());
    EXPECT_EQ(libcellml::CellmlElementType::MODEL, issue->cellmlElementType());

    // Cannot clear by setting to nullptr through another type.
    issue->setEncapsulation(nullptr);
    EXPECT_EQ(nullptr, issue->model());
    EXPECT_EQ(libcellml::CellmlElementType::UNDEFINED, issue->cellmlElementType());
}

TEST(Issue, clear)
{
    auto issue = libcellml::Issue::create();
    auto model = libcellml::Model::create();

    EXPECT_EQ(nullptr, issue->model());
    EXPECT_EQ(libcellml::CellmlElementType::UNDEFINED, issue->cellmlElementType());
    EXPECT_EQ("", issue->description());
    EXPECT_EQ(libcellml::Issue::Level::ERROR, issue->level());
    EXPECT_EQ(libcellml::Issue::ReferenceRule::UNDEFINED, issue->referenceRule());

    issue->setModel(model);
    issue->setDescription("description");
    issue->setLevel(libcellml::Issue::Level::MESSAGE);
    issue->setReferenceRule(libcellml::Issue::ReferenceRule::CONNECTION_CHILD);

    EXPECT_EQ(model, issue->model());
    EXPECT_EQ(libcellml::CellmlElementType::MODEL, issue->cellmlElementType());
    EXPECT_EQ("description", issue->description());
    EXPECT_EQ(libcellml::Issue::Level::MESSAGE, issue->level());
    EXPECT_EQ(libcellml::Issue::ReferenceRule::CONNECTION_CHILD, issue->referenceRule());

    issue->clear();

    EXPECT_EQ(nullptr, issue->model());
    EXPECT_EQ(libcellml::CellmlElementType::UNDEFINED, issue->cellmlElementType());
    EXPECT_EQ("", issue->description());
    EXPECT_EQ(libcellml::Issue::Level::ERROR, issue->level());
    EXPECT_EQ(libcellml::Issue::ReferenceRule::UNDEFINED, issue->referenceRule());
}

TEST(Issue, setItemMisMatchingType)
{
    auto issue = libcellml::Issue::create();
    auto model = libcellml::Model::create();

    issue->setItem(libcellml::CellmlElementType::MATH, model);

    EXPECT_EQ(nullptr, issue->math());
}

TEST(Issue, setItemUndefined)
{
    auto issue = libcellml::Issue::create();
    auto model = libcellml::Model::create();

    issue->setItem(libcellml::CellmlElementType::MODEL, model);

    EXPECT_EQ(model, issue->model());
    EXPECT_EQ(libcellml::CellmlElementType::MODEL, issue->cellmlElementType());

    issue->setItem(libcellml::CellmlElementType::UNDEFINED, model);

    EXPECT_EQ(nullptr, issue->model());
    EXPECT_EQ(libcellml::CellmlElementType::UNDEFINED, issue->cellmlElementType());
}

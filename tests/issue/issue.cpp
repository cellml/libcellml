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
#include "test_utils.h"

#include "gtest/gtest.h"

#include <libcellml>

TEST(Issue, createIssue)
{
    libcellml::IssuePtr e = std::make_shared<libcellml::Issue>();
    libcellml::Parser parser;

    parser.addIssue(e);

    EXPECT_EQ(size_t(1), parser.issueCount());
}

TEST(Issue, createModelIssue)
{
    libcellml::ModelPtr m = std::make_shared<libcellml::Model>();
    libcellml::IssuePtr e = std::make_shared<libcellml::Issue>(m);

    EXPECT_EQ(libcellml::Issue::Cause::MODEL, e->cause());
}

TEST(Issue, createComponentIssue)
{
    libcellml::ComponentPtr c = std::make_shared<libcellml::Component>();
    libcellml::IssuePtr e = std::make_shared<libcellml::Issue>(c);

    EXPECT_EQ(libcellml::Issue::Cause::COMPONENT, e->cause());
}

TEST(Issue, createVariableIssue)
{
    libcellml::VariablePtr v = std::make_shared<libcellml::Variable>();
    libcellml::IssuePtr e = std::make_shared<libcellml::Issue>(v);

    EXPECT_EQ(libcellml::Issue::Cause::VARIABLE, e->cause());
}

TEST(Issue, createUnitsIssue)
{
    libcellml::UnitsPtr u = std::make_shared<libcellml::Units>();
    libcellml::IssuePtr e = std::make_shared<libcellml::Issue>(u);

    EXPECT_EQ(libcellml::Issue::Cause::UNITS, e->cause());
}

TEST(Issue, createImportSourceIssue)
{
    libcellml::ImportSourcePtr i = std::make_shared<libcellml::ImportSource>();
    libcellml::IssuePtr e = std::make_shared<libcellml::Issue>(i);

    EXPECT_EQ(libcellml::Issue::Cause::IMPORT, e->cause());
}

TEST(Issue, createResetIssue)
{
    libcellml::ResetPtr r = std::make_shared<libcellml::Reset>();
    libcellml::IssuePtr e = std::make_shared<libcellml::Issue>(r);

    EXPECT_EQ(libcellml::Issue::Cause::RESET, e->cause());
}

TEST(Issue, createWhenIssue)
{
    libcellml::WhenPtr w = std::make_shared<libcellml::When>();
    libcellml::IssuePtr e = std::make_shared<libcellml::Issue>(w);

    EXPECT_EQ(libcellml::Issue::Cause::WHEN, e->cause());
}

void testSpecificationRule(const libcellml::Issue &e)
{
    switch (e.rule()) {
    case libcellml::SpecificationRule::COMPONENT_CHILD:
        EXPECT_EQ("10.1.2", e.specificationHeading());
        break;
    case libcellml::SpecificationRule::COMPONENT_NAME:
        EXPECT_EQ("10.1.1", e.specificationHeading());
        break;
    case libcellml::SpecificationRule::COMPONENT_REF_CHILD:
        EXPECT_EQ("16.1.2", e.specificationHeading());
        break;
    case libcellml::SpecificationRule::COMPONENT_REF_COMPONENT_ATTRIBUTE:
        EXPECT_EQ("16.1.1", e.specificationHeading());
        break;
    case libcellml::SpecificationRule::COMPONENT_REF_ENCAPSULATION:
        EXPECT_EQ("16.1.3", e.specificationHeading());
        break;
    case libcellml::SpecificationRule::CONNECTION_COMPONENT1:
        EXPECT_EQ("17.1.1", e.specificationHeading());
        break;
    case libcellml::SpecificationRule::CONNECTION_COMPONENT2:
        EXPECT_EQ("17.1.2", e.specificationHeading());
        break;
    case libcellml::SpecificationRule::CONNECTION_UNIQUE_TRANSITIVE:
        EXPECT_EQ("17.1.3", e.specificationHeading());
        break;
    case libcellml::SpecificationRule::CONNECTION_MAP_VARIABLES:
        EXPECT_EQ("17.1.4", e.specificationHeading());
        break;
    case libcellml::SpecificationRule::DATA_REPR_IDENTIFIER_AT_LEAST_ONE_ALPHANUM:
        EXPECT_EQ("3.1.3", e.specificationHeading());
        break;
    case libcellml::SpecificationRule::DATA_REPR_IDENTIFIER_BEGIN_EURO_NUM:
        EXPECT_EQ("3.1.4", e.specificationHeading());
        break;
    case libcellml::SpecificationRule::DATA_REPR_IDENTIFIER_IDENTICAL:
        EXPECT_EQ("3.1.5", e.specificationHeading());
        break;
    case libcellml::SpecificationRule::DATA_REPR_IDENTIFIER_LATIN_ALPHANUM:
        EXPECT_EQ("3.1.2", e.specificationHeading());
        break;
    case libcellml::SpecificationRule::DATA_REPR_IDENTIFIER_UNICODE:
        EXPECT_EQ("3.1.1", e.specificationHeading());
        break;
    case libcellml::SpecificationRule::DATA_REPR_NNEG_INT_BASE10:
        EXPECT_EQ("3.2.1", e.specificationHeading());
        break;
    case libcellml::SpecificationRule::DATA_REPR_NNEG_INT_EURO_NUM:
        EXPECT_EQ("3.2.2", e.specificationHeading());
        break;
    case libcellml::SpecificationRule::ENCAPSULATION_COMPONENT_REF:
        EXPECT_EQ("15.1.1", e.specificationHeading());
        break;
    case libcellml::SpecificationRule::IMPORT_CHILD:
        EXPECT_EQ("5.1.2", e.specificationHeading());
        break;
    case libcellml::SpecificationRule::IMPORT_CIRCULAR:
        EXPECT_EQ("5.1.3", e.specificationHeading());
        break;
    case libcellml::SpecificationRule::IMPORT_COMPONENT_NAME:
        EXPECT_EQ("7.1.1", e.specificationHeading());
        break;
    case libcellml::SpecificationRule::IMPORT_COMPONENT_REF:
        EXPECT_EQ("7.1.2", e.specificationHeading());
        break;
    case libcellml::SpecificationRule::IMPORT_HREF:
        EXPECT_EQ("5.1.1", e.specificationHeading());
        break;
    case libcellml::SpecificationRule::IMPORT_UNITS_NAME:
        EXPECT_EQ("6.1.1", e.specificationHeading());
        break;
    case libcellml::SpecificationRule::IMPORT_UNITS_REF:
        EXPECT_EQ("6.1.2", e.specificationHeading());
        break;
    case libcellml::SpecificationRule::MAP_VARIABLES_UNIQUE:
        EXPECT_EQ("18.1.3", e.specificationHeading());
        break;
    case libcellml::SpecificationRule::MAP_VARIABLES_VARIABLE1:
        EXPECT_EQ("18.1.1", e.specificationHeading());
        break;
    case libcellml::SpecificationRule::MAP_VARIABLES_VARIABLE2:
        EXPECT_EQ("18.1.2", e.specificationHeading());
        break;
    case libcellml::SpecificationRule::MATH_CHILD:
        EXPECT_EQ("14.1.2", e.specificationHeading());
        break;
    case libcellml::SpecificationRule::MATH_CI_VARIABLE_REFERENCE:
        EXPECT_EQ("14.1.3", e.specificationHeading());
        break;
    case libcellml::SpecificationRule::MATH_CN_UNITS_ATTRIBUTE:
        EXPECT_EQ("14.1.4", e.specificationHeading());
        break;
    case libcellml::SpecificationRule::MATH_MATHML:
        EXPECT_EQ("14.1.1", e.specificationHeading());
        break;
    case libcellml::SpecificationRule::MODEL_CHILD:
        EXPECT_EQ("4.2.2", e.specificationHeading());
        break;
    case libcellml::SpecificationRule::MODEL_ELEMENT:
        EXPECT_EQ("4.1", e.specificationHeading());
        break;
    case libcellml::SpecificationRule::MODEL_MORE_THAN_ONE_ENCAPSULATION:
        EXPECT_EQ("4.2.3", e.specificationHeading());
        break;
    case libcellml::SpecificationRule::MODEL_NAME:
        EXPECT_EQ("4.2.1", e.specificationHeading());
        break;
    case libcellml::SpecificationRule::RESET_CHILD:
        EXPECT_EQ("12.1.2", e.specificationHeading());
        break;
    case libcellml::SpecificationRule::RESET_VARIABLE_REFERENCE:
        EXPECT_EQ("12.1.1.1", e.specificationHeading());
        break;
    case libcellml::SpecificationRule::RESET_ORDER:
        EXPECT_EQ("12.1.1.2", e.specificationHeading());
        break;
    case libcellml::SpecificationRule::UNITS_CHILD:
        EXPECT_EQ("8.1.4", e.specificationHeading());
        break;
    case libcellml::SpecificationRule::UNITS_NAME:
        EXPECT_EQ("8.1.1", e.specificationHeading());
        break;
    case libcellml::SpecificationRule::UNITS_NAME_UNIQUE:
        EXPECT_EQ("8.1.2", e.specificationHeading());
        break;
    case libcellml::SpecificationRule::UNITS_STANDARD:
        EXPECT_EQ("8.1.3", e.specificationHeading());
        break;
    case libcellml::SpecificationRule::UNIT_OPTIONAL_ATTRIBUTE:
        EXPECT_EQ("9.1.2", e.specificationHeading());
        break;
    case libcellml::SpecificationRule::UNIT_CIRCULAR_REF:
        EXPECT_EQ("9.1.1.2", e.specificationHeading());
        break;
    case libcellml::SpecificationRule::UNIT_DIGRAPH:
        EXPECT_EQ("9.1.1.1", e.specificationHeading());
        break;
    case libcellml::SpecificationRule::UNIT_EXPONENT:
        EXPECT_EQ("9.1.2.3", e.specificationHeading());
        break;
    case libcellml::SpecificationRule::UNIT_MULTIPLIER:
        EXPECT_EQ("9.1.2.2", e.specificationHeading());
        break;
    case libcellml::SpecificationRule::UNIT_PREFIX:
        EXPECT_EQ("9.1.2.1", e.specificationHeading());
        break;
    case libcellml::SpecificationRule::UNIT_UNITS_REF:
        EXPECT_EQ("9.1.1", e.specificationHeading());
        break;
    case libcellml::SpecificationRule::VARIABLE_INITIAL_VALUE:
        EXPECT_EQ("11.1.2.2", e.specificationHeading());
        break;
    case libcellml::SpecificationRule::VARIABLE_INTERFACE:
        EXPECT_EQ("11.1.2.1", e.specificationHeading());
        break;
    case libcellml::SpecificationRule::VARIABLE_NAME:
        EXPECT_EQ("11.1.1.1", e.specificationHeading());
        break;
    case libcellml::SpecificationRule::VARIABLE_UNITS:
        EXPECT_EQ("11.1.1.2", e.specificationHeading());
        break;
    case libcellml::SpecificationRule::WHEN_ORDER:
        EXPECT_EQ("13.1.1", e.specificationHeading());
        break;
    case libcellml::SpecificationRule::WHEN_CHILD:
        EXPECT_EQ("13.1.2", e.specificationHeading());
        break;
    case libcellml::SpecificationRule::UNDEFINED:
        EXPECT_EQ("", e.specificationHeading());
        break;
    }
}

TEST(Issue, specificationRule)
{
    size_t count = 0;
    libcellml::Issue e;
    e.setRule(libcellml::SpecificationRule::UNDEFINED);
    ++count;
    testSpecificationRule(e);
    e.setRule(libcellml::SpecificationRule::COMPONENT_CHILD);
    ++count;
    testSpecificationRule(e);
    e.setRule(libcellml::SpecificationRule::COMPONENT_NAME);
    ++count;
    testSpecificationRule(e);
    e.setRule(libcellml::SpecificationRule::COMPONENT_REF_CHILD);
    ++count;
    testSpecificationRule(e);
    e.setRule(libcellml::SpecificationRule::COMPONENT_REF_COMPONENT_ATTRIBUTE);
    ++count;
    testSpecificationRule(e);
    e.setRule(libcellml::SpecificationRule::COMPONENT_REF_ENCAPSULATION);
    ++count;
    testSpecificationRule(e);
    e.setRule(libcellml::SpecificationRule::CONNECTION_COMPONENT1);
    ++count;
    testSpecificationRule(e);
    e.setRule(libcellml::SpecificationRule::CONNECTION_COMPONENT2);
    ++count;
    testSpecificationRule(e);
    e.setRule(libcellml::SpecificationRule::CONNECTION_UNIQUE_TRANSITIVE);
    ++count;
    testSpecificationRule(e);
    e.setRule(libcellml::SpecificationRule::CONNECTION_MAP_VARIABLES);
    ++count;
    testSpecificationRule(e);
    e.setRule(libcellml::SpecificationRule::DATA_REPR_IDENTIFIER_AT_LEAST_ONE_ALPHANUM);
    ++count;
    testSpecificationRule(e);
    e.setRule(libcellml::SpecificationRule::DATA_REPR_IDENTIFIER_BEGIN_EURO_NUM);
    ++count;
    testSpecificationRule(e);
    e.setRule(libcellml::SpecificationRule::DATA_REPR_IDENTIFIER_IDENTICAL);
    ++count;
    testSpecificationRule(e);
    e.setRule(libcellml::SpecificationRule::DATA_REPR_IDENTIFIER_LATIN_ALPHANUM);
    ++count;
    testSpecificationRule(e);
    e.setRule(libcellml::SpecificationRule::DATA_REPR_IDENTIFIER_UNICODE);
    ++count;
    testSpecificationRule(e);
    e.setRule(libcellml::SpecificationRule::DATA_REPR_NNEG_INT_BASE10);
    ++count;
    testSpecificationRule(e);
    e.setRule(libcellml::SpecificationRule::DATA_REPR_NNEG_INT_EURO_NUM);
    ++count;
    testSpecificationRule(e);
    e.setRule(libcellml::SpecificationRule::ENCAPSULATION_COMPONENT_REF);
    ++count;
    testSpecificationRule(e);
    e.setRule(libcellml::SpecificationRule::IMPORT_CHILD);
    ++count;
    testSpecificationRule(e);
    e.setRule(libcellml::SpecificationRule::IMPORT_CIRCULAR);
    ++count;
    testSpecificationRule(e);
    e.setRule(libcellml::SpecificationRule::IMPORT_COMPONENT_NAME);
    ++count;
    testSpecificationRule(e);
    e.setRule(libcellml::SpecificationRule::IMPORT_COMPONENT_REF);
    ++count;
    testSpecificationRule(e);
    e.setRule(libcellml::SpecificationRule::IMPORT_HREF);
    ++count;
    testSpecificationRule(e);
    e.setRule(libcellml::SpecificationRule::IMPORT_UNITS_NAME);
    ++count;
    testSpecificationRule(e);
    e.setRule(libcellml::SpecificationRule::IMPORT_UNITS_REF);
    ++count;
    testSpecificationRule(e);
    e.setRule(libcellml::SpecificationRule::MAP_VARIABLES_UNIQUE);
    ++count;
    testSpecificationRule(e);
    e.setRule(libcellml::SpecificationRule::MAP_VARIABLES_VARIABLE1);
    ++count;
    testSpecificationRule(e);
    e.setRule(libcellml::SpecificationRule::MAP_VARIABLES_VARIABLE2);
    ++count;
    testSpecificationRule(e);
    e.setRule(libcellml::SpecificationRule::MODEL_CHILD);
    ++count;
    testSpecificationRule(e);
    e.setRule(libcellml::SpecificationRule::MODEL_ELEMENT);
    ++count;
    testSpecificationRule(e);
    e.setRule(libcellml::SpecificationRule::MODEL_MORE_THAN_ONE_ENCAPSULATION);
    ++count;
    testSpecificationRule(e);
    e.setRule(libcellml::SpecificationRule::MODEL_NAME);
    ++count;
    testSpecificationRule(e);
    e.setRule(libcellml::SpecificationRule::RESET_CHILD);
    ++count;
    testSpecificationRule(e);
    e.setRule(libcellml::SpecificationRule::RESET_VARIABLE_REFERENCE);
    ++count;
    testSpecificationRule(e);
    e.setRule(libcellml::SpecificationRule::RESET_ORDER);
    ++count;
    testSpecificationRule(e);
    e.setRule(libcellml::SpecificationRule::UNITS_CHILD);
    ++count;
    testSpecificationRule(e);
    e.setRule(libcellml::SpecificationRule::UNITS_NAME);
    ++count;
    testSpecificationRule(e);
    e.setRule(libcellml::SpecificationRule::UNITS_NAME_UNIQUE);
    ++count;
    testSpecificationRule(e);
    e.setRule(libcellml::SpecificationRule::UNITS_STANDARD);
    ++count;
    testSpecificationRule(e);
    e.setRule(libcellml::SpecificationRule::UNIT_OPTIONAL_ATTRIBUTE);
    ++count;
    testSpecificationRule(e);
    e.setRule(libcellml::SpecificationRule::UNIT_CIRCULAR_REF);
    ++count;
    testSpecificationRule(e);
    e.setRule(libcellml::SpecificationRule::UNIT_DIGRAPH);
    ++count;
    testSpecificationRule(e);
    e.setRule(libcellml::SpecificationRule::UNIT_EXPONENT);
    ++count;
    testSpecificationRule(e);
    e.setRule(libcellml::SpecificationRule::UNIT_MULTIPLIER);
    ++count;
    testSpecificationRule(e);
    e.setRule(libcellml::SpecificationRule::UNIT_PREFIX);
    ++count;
    testSpecificationRule(e);
    e.setRule(libcellml::SpecificationRule::UNIT_UNITS_REF);
    ++count;
    testSpecificationRule(e);
    e.setRule(libcellml::SpecificationRule::VARIABLE_INITIAL_VALUE);
    ++count;
    testSpecificationRule(e);
    e.setRule(libcellml::SpecificationRule::VARIABLE_INTERFACE);
    ++count;
    testSpecificationRule(e);
    e.setRule(libcellml::SpecificationRule::VARIABLE_NAME);
    ++count;
    testSpecificationRule(e);
    e.setRule(libcellml::SpecificationRule::VARIABLE_UNITS);
    ++count;
    testSpecificationRule(e);
    e.setRule(libcellml::SpecificationRule::WHEN_CHILD);
    ++count;
    testSpecificationRule(e);
    e.setRule(libcellml::SpecificationRule::WHEN_ORDER);
    ++count;
    testSpecificationRule(e);
    EXPECT_EQ(size_t(52), count);
}

TEST(Issue, collectHints)
{
    std::string expectedHint = "Multiplier mismatch in units of equivalent variables 'variable1' with units of 'metre', and 'variable2' with units of 'kilometre', by a factor of 10^3.";

    libcellml::Validator validator;
    libcellml::ModelPtr m = std::make_shared<libcellml::Model>();
    libcellml::ComponentPtr c1 = std::make_shared<libcellml::Component>();
    libcellml::ComponentPtr c2 = std::make_shared<libcellml::Component>();
    libcellml::VariablePtr v1 = std::make_shared<libcellml::Variable>();
    libcellml::VariablePtr v2 = std::make_shared<libcellml::Variable>();
    libcellml::UnitsPtr u2 = std::make_shared<libcellml::Units>();

    m->setName("model");
    c1->setName("component1");
    c2->setName("component2");

    v1->setName("variable1");
    v1->setUnits("metre");

    v2->setName("variable2");
    u2->setName("kilometre");
    u2->addUnit("metre", "kilo");
    v2->setUnits(u2);

    c1->addVariable(v1);
    c2->addVariable(v2);

    m->addComponent(c1);
    m->addComponent(c2);
    m->addUnits(u2);

    // Variables are equivalent but with different order of magnitude
    libcellml::Variable::addEquivalence(v1, v2);

    validator.validateModel(m);
    printIssues(validator);
    EXPECT_EQ(size_t(0), validator.issueCount()); // This way is what we currently have ...
    EXPECT_EQ(size_t(0), validator.issueCount(libcellml::Issue::Type::ERROR)); // Would rather do it this way: generic issue retrival based on level argument TODO Will fail because this function doesn't exist ...

    // Want to generate a hint for the mismatch in unit multiplier/prefix
    // TODO: Need to turn on the hint generation before this will work ...
    // EXPECT_EQ(size_t(1), validator.issueCount(libcellml::Issue::Type::HINT)); // As above: generic issue retrival based on level argument
    // EXPECT_EQ(expectedHint, validator.issue(libcellml::Issue::Type::HINT, 0)->description());
}

TEST(Issue, collectWarnings)
{
    std::vector<std::string> expectedWarnings = {
        "Reset in component 'component' with variable 'v1', and test_variable 'v1', and order '1' has an empty MathML block for its test_value. ",
        "Reset in component 'component' with variable 'v1', and test_variable 'v1', and order '1' has an empty MathML block for its reset_value. ",
    };

    libcellml::Validator validator;
    libcellml::ModelPtr m = std::make_shared<libcellml::Model>();
    libcellml::ComponentPtr c = std::make_shared<libcellml::Component>();
    libcellml::VariablePtr v1 = std::make_shared<libcellml::Variable>();
    libcellml::VariablePtr v2 = std::make_shared<libcellml::Variable>();
    libcellml::ResetPtr r = std::make_shared<libcellml::Reset>();

    m->setName("model");
    c->setName("component");

    v1->setName("variable1");
    v1->setUnits("dimensionless");
    v2->setName("variable2");
    v2->setUnits("dimensionless");

    // TODO these will all fail to compile because they use the new format for resets
    // r->setVariable(v1);
    // r->setTestVariable(v2);
    // r->setOrder(1);
    // r->setTestValue(emptyMath); // Resets contain a mathml field, but that math field is empty. Valid, but not meaningful ...
    // r->setResetValue(emptyMath); // Resets contain a mathml field, but that math field is empty. Valid, but not meaningful ...
    // c->addReset(r);

    c->addVariable(v1);
    c->addVariable(v2);
    m->addComponent(c);

    validator.validateModel(m);
    printIssues(validator);
    EXPECT_EQ(size_t(0), validator.issueCount(libcellml::Issue::Type::ERROR)); // No ERROR-type issues generated

    // Want to generate a warning for the empty MathML block
    // TODO: Need to turn on the warning generation in the validator for this to work
    // EXPECT_EQ(size_t(2), validator.issueCount(libcellml::Issue::Type::WARNING)); // As above: generic issue retrival based on level argument
    // EXPECT_EQ(expectedWarnings.at(0), validator.issue(libcellml::Issue::Type::WARNING, 0)->description());
    // EXPECT_EQ(expectedWarnings.at(1), validator.issue(libcellml::Issue::Type::WARNING, 1)->description());
    EXPECT_EQ(size_t(0), validator.issueCount()); // Defaults to all types of error
}

TEST(Issue, orderOfIssuesValidator)
{
    // Test that issues are reported in the order encountered, regardless of the level at which they're requested
    std::vector<std::string> expectedIssues;
    std::vector<std::string> expectedErrors;
    std::vector<std::string> expectedWarnings;
    std::vector<std::string> expectedHints;

    // Model  will generate a combination of errors, warnings, and hints
    libcellml::Validator validator;
    libcellml::ModelPtr m = std::make_shared<libcellml::Model>();
    libcellml::ComponentPtr c1 = std::make_shared<libcellml::Component>();
    libcellml::ComponentPtr c2 = std::make_shared<libcellml::Component>();
    libcellml::ComponentPtr c3 = std::make_shared<libcellml::Component>();
    libcellml::VariablePtr v1 = std::make_shared<libcellml::Variable>();
    libcellml::VariablePtr v2 = std::make_shared<libcellml::Variable>();
    libcellml::VariablePtr v3 = std::make_shared<libcellml::Variable>();
    libcellml::UnitsPtr u3 = std::make_shared<libcellml::Units>();
    libcellml::ResetPtr r = std::make_shared<libcellml::Reset>();

    m->setName("model");
    m->addComponent(c1);
    m->addComponent(c2);
    m->addComponent(c3);
    m->addUnits(u3);
    c1->setName("component1");
    c2->setName("component2");
    v1->setName("variable1");
    v2->setName("variable2");
    v3->setName("variable3");
    c1->addVariable(v1);
    c1->addVariable(v2);
    c2->addVariable(v3);

    // Making an error: Component has no name
    c3->setName("");
    expectedErrors = {
        "CellML identifiers must contain one or more basic Latin alphabetic characters.",
        "Component does not have a valid name attribute."};

    // Making a hint: Equivalent variables with mis-matched multipliers in the units
    // TODO this will not generate a hint as multiplier checking is not active yet.
    v1->setUnits("metre");
    v2->setUnits("dimensionless");
    u3->setName("kilometre");
    u3->addUnit("metre", "kilo");
    v3->setUnits(u3);
    libcellml::Variable::addEquivalence(v1, v3);
    expectedHints = {
        "Multiplier mismatch in units of equivalent variables 'variable1' with units of 'metre', and 'variable3' with units of 'kilometre', by a factor of 10^3."};

    // Making a warning: empty mathml field in resets
    // TODO these will all fail to compile because they use the new format for resets
    // r->setVariable(v1);
    // r->setTestVariable(v2);
    // r->setOrder(1);
    // r->setTestValue(emptyMath);
    // r->setResetValue(emptyMath);
    // c1->addReset(r);
    
    expectedWarnings = {
        "Reset in component 'component' with variable 'v1', and test_variable 'v1', and order '1' has an empty MathML block for its test_value. ",
        "Reset in component 'component' with variable 'v1', and test_variable 'v1', and order '1' has an empty MathML block for its reset_value. ",
    };
    // Creating the issues in order that they will be returned
    expectedIssues.push_back(expectedErrors.at(0)); // parser error first
    expectedIssues.push_back(expectedHints.at(0)); // unit validation next
    expectedIssues.push_back(expectedWarnings.at(0));
    expectedIssues.push_back(expectedWarnings.at(1)); // resets tested last

    validator.validateModel(m);

    // EXPECT_EQ(size_t(5), validator.issueCount()); // Default returns all issue types
    EXPECT_EQ(size_t(2), validator.issueCount(libcellml::Issue::Type::ERROR));

    printIssues(validator);
    // EXPECT_EQ(size_t(2), validator.issueCount(libcellml::Issue::Type::WARNING));
    // EXPECT_EQ(size_t(1), validator.issueCount(libcellml::Issue::Type::HINT));

    // std::vector<libcellml::Issue::Type> findType {libcellml::Issue::Type::ERROR, libcellml::Issue::Type::HINT};

    // EXPECT_EQ(size_t(3), validator.issueCount(findType)); // Test combination of types
}

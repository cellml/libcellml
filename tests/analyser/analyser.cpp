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

TEST(Analyser, unlinkedUnitsInModel)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("generator/hodgkin_huxley_squid_axon_model_1952/model.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    // When parsing a model all Units are automatically linked.

    EXPECT_FALSE(model->hasUnlinkedUnits());

    // When we set a Units units by name we create an unlinked Units. That is,
    // a Units that has a reference to a Units defined in the model but it is
    // not using the object Units defined in the model.

    model->component("membrane")->variable("V")->setUnits("millivolt");

    EXPECT_TRUE(model->hasUnlinkedUnits());

    // As a result of the aforementioned unlinked Units, the analyser should log
    // an error for it.

    const std::vector<std::string> expectedIssues = {
        "The model has units which are not linked together.",
    };

    auto analyser = libcellml::Analyser::create();

    analyser->analyseModel(model);

    EXPECT_EQ_ISSUES_CELLMLELEMENTTYPES_LEVELS_REFERENCERULES_URLS(expectedIssues,
                                                                   expectedCellmlElementTypes(expectedIssues.size(), libcellml::CellmlElementType::UNDEFINED),
                                                                   expectedLevels(expectedIssues.size(), libcellml::Issue::Level::ERROR),
                                                                   expectedReferenceRules(expectedIssues.size(), libcellml::Issue::ReferenceRule::ANALYSER_UNLINKED_UNITS),
                                                                   expectedUrls(expectedIssues.size(), "https://libcellml.org/documentation/guides/latest/runtime_codes/index?issue=ANALYSER_UNLINKED_UNITS"),
                                                                   analyser);
}

TEST(Analyser, notEqualityStatement)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("analyser/not_equality_statement.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    const std::vector<std::string> expectedIssues = {
        "Equation 'x+y+z' in component 'my_component' is not an equality statement (i.e. LHS = RHS).",
    };

    auto analyser = libcellml::Analyser::create();

    analyser->analyseModel(model);

    EXPECT_EQ_ISSUES_CELLMLELEMENTTYPES_LEVELS_REFERENCERULES_URLS(expectedIssues,
                                                                   expectedCellmlElementTypes(expectedIssues.size(), libcellml::CellmlElementType::COMPONENT),
                                                                   expectedLevels(expectedIssues.size(), libcellml::Issue::Level::ERROR),
                                                                   expectedReferenceRules(expectedIssues.size(), libcellml::Issue::ReferenceRule::ANALYSER_EQUATION_NOT_EQUALITY_STATEMENT),
                                                                   expectedUrls(expectedIssues.size(), "https://libcellml.org/documentation/guides/latest/runtime_codes/index?issue=ANALYSER_EQUATION_NOT_EQUALITY_STATEMENT"),
                                                                   analyser);

    EXPECT_EQ(libcellml::AnalyserModel::Type::INVALID, analyser->model()->type());
}

TEST(Analyser, initialisedVariableOfIntegration)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("analyser/initialised_variable_of_integration.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    const std::vector<std::string> expectedIssues = {
        "Variable 'time' in component 'my_component' cannot be both a variable of integration and initialised.",
    };

    auto analyser = libcellml::Analyser::create();

    analyser->analyseModel(model);

    EXPECT_EQ_ISSUES_CELLMLELEMENTTYPES_LEVELS_REFERENCERULES_URLS(expectedIssues,
                                                                   expectedCellmlElementTypes(expectedIssues.size(), libcellml::CellmlElementType::VARIABLE),
                                                                   expectedLevels(expectedIssues.size(), libcellml::Issue::Level::ERROR),
                                                                   expectedReferenceRules(expectedIssues.size(), libcellml::Issue::ReferenceRule::ANALYSER_VOI_INITIALISED),
                                                                   expectedUrls(expectedIssues.size(), "https://libcellml.org/documentation/guides/latest/runtime_codes/index?issue=ANALYSER_VOI_INITIALISED"),
                                                                   analyser);

    EXPECT_EQ(libcellml::AnalyserModel::Type::INVALID, analyser->model()->type());
    EXPECT_EQ("invalid", libcellml::AnalyserModel::typeAsString(analyser->model()->type()));
}

TEST(Analyser, initialisedVariableOfIntegrationInNonFirstComponent)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("analyser/initialised_variable_of_integration_in_non_first_component.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    const std::vector<std::string> expectedIssues = {
        "Variable 'time' in component 'environment' cannot be both a variable of integration and initialised.",
    };

    auto analyser = libcellml::Analyser::create();

    analyser->analyseModel(model);

    EXPECT_EQ_ISSUES_CELLMLELEMENTTYPES_LEVELS_REFERENCERULES_URLS(expectedIssues,
                                                                   expectedCellmlElementTypes(expectedIssues.size(), libcellml::CellmlElementType::VARIABLE),
                                                                   expectedLevels(expectedIssues.size(), libcellml::Issue::Level::ERROR),
                                                                   expectedReferenceRules(expectedIssues.size(), libcellml::Issue::ReferenceRule::ANALYSER_VOI_INITIALISED),
                                                                   expectedUrls(expectedIssues.size(), "https://libcellml.org/documentation/guides/latest/runtime_codes/index?issue=ANALYSER_VOI_INITIALISED"),
                                                                   analyser);

    EXPECT_EQ(libcellml::AnalyserModel::Type::INVALID, analyser->model()->type());
}

TEST(Analyser, twoVariablesOfIntegration)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("analyser/two_variables_of_integration.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    const std::vector<std::string> expectedIssues = {
        "Variable 'time' in component 'main' and variable 'other_time' in component 'sub_sub_sub' cannot both be the variable of integration.",
    };

    auto analyser = libcellml::Analyser::create();

    analyser->analyseModel(model);

    EXPECT_EQ_ISSUES_CELLMLELEMENTTYPES_LEVELS_REFERENCERULES_URLS(expectedIssues,
                                                                   expectedCellmlElementTypes(expectedIssues.size(), libcellml::CellmlElementType::VARIABLE),
                                                                   expectedLevels(expectedIssues.size(), libcellml::Issue::Level::ERROR),
                                                                   expectedReferenceRules(expectedIssues.size(), libcellml::Issue::ReferenceRule::ANALYSER_VOI_SEVERAL),
                                                                   expectedUrls(expectedIssues.size(), "https://libcellml.org/documentation/guides/latest/runtime_codes/index?issue=ANALYSER_VOI_SEVERAL"),
                                                                   analyser);

    EXPECT_EQ(libcellml::AnalyserModel::Type::INVALID, analyser->model()->type());
}

TEST(Analyser, nonFirstOrderOdes)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("analyser/non_first_order_odes.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    const std::vector<std::string> expectedIssues = {
        "The differential equation for variable 'x' in component 'main' must be of the first order.",
        "The differential equation for variable 'y' in component 'sub' must be of the first order.",
        "The differential equation for variable 'z' in component 'sub_sub' must be of the first order.",
    };

    auto analyser = libcellml::Analyser::create();

    analyser->analyseModel(model);

    EXPECT_EQ_ISSUES_CELLMLELEMENTTYPES_LEVELS_REFERENCERULES_URLS(expectedIssues,
                                                                   expectedCellmlElementTypes(expectedIssues.size(), libcellml::CellmlElementType::MATH),
                                                                   expectedLevels(expectedIssues.size(), libcellml::Issue::Level::ERROR),
                                                                   expectedReferenceRules(expectedIssues.size(), libcellml::Issue::ReferenceRule::ANALYSER_ODE_NOT_FIRST_ORDER),
                                                                   expectedUrls(expectedIssues.size(), "https://libcellml.org/documentation/guides/latest/runtime_codes/index?issue=ANALYSER_ODE_NOT_FIRST_ORDER"),
                                                                   analyser);

    EXPECT_EQ(libcellml::AnalyserModel::Type::INVALID, analyser->model()->type());
}

TEST(Analyser, undefinedVariables)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("analyser/undefined_variables.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    const std::vector<std::string> expectedIssues = {
        "MathML ci element has the child text 'a' which does not correspond with any variable names present in component 'my_component'.",
        "MathML ci element has the child text 'b' which does not correspond with any variable names present in component 'my_component'.",
    };

    auto analyser = libcellml::Analyser::create();

    analyser->analyseModel(model);

    EXPECT_EQ_ISSUES_CELLMLELEMENTTYPES_LEVELS_REFERENCERULES_URLS(expectedIssues,
                                                                   expectedCellmlElementTypes(expectedIssues.size(), libcellml::CellmlElementType::MATH),
                                                                   expectedLevels(expectedIssues.size(), libcellml::Issue::Level::ERROR),
                                                                   expectedReferenceRules(expectedIssues.size(), libcellml::Issue::ReferenceRule::MATH_CI_VARIABLE_REF),
                                                                   expectedUrls(expectedIssues.size(), "https://cellml-specification.readthedocs.io/en/latest/reference/formal_and_informative/specB12.html?issue=MATH_CI_VARIABLE_REF"),
                                                                   analyser);

    EXPECT_EQ(libcellml::AnalyserModel::Type::INVALID, analyser->model()->type());
}

TEST(Analyser, variableInitialisedTwice)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("analyser/variable_initialised_twice.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    const std::vector<std::string> expectedIssues = {
        "Variable 'x' in component 'sub' and variable 'x' in component 'main' are equivalent and cannot therefore both be initialised.",
    };

    auto analyser = libcellml::Analyser::create();

    analyser->analyseModel(model);

    EXPECT_EQ_ISSUES_CELLMLELEMENTTYPES_LEVELS_REFERENCERULES_URLS(expectedIssues,
                                                                   expectedCellmlElementTypes(expectedIssues.size(), libcellml::CellmlElementType::VARIABLE),
                                                                   expectedLevels(expectedIssues.size(), libcellml::Issue::Level::ERROR),
                                                                   expectedReferenceRules(expectedIssues.size(), libcellml::Issue::ReferenceRule::ANALYSER_VARIABLE_INITIALISED_MORE_THAN_ONCE),
                                                                   expectedUrls(expectedIssues.size(), "https://libcellml.org/documentation/guides/latest/runtime_codes/index?issue=ANALYSER_VARIABLE_INITIALISED_MORE_THAN_ONCE"),
                                                                   analyser);

    EXPECT_EQ(libcellml::AnalyserModel::Type::INVALID, analyser->model()->type());
}

TEST(Analyser, nonConstantInitialisingVariable)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("analyser/non_constant_initialising_variable.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    const std::vector<std::string> expectedIssues = {
        "Variable 'x' in component 'main' is initialised using variable 'k2', which is not a constant.",
    };

    auto analyser = libcellml::Analyser::create();

    analyser->analyseModel(model);

    EXPECT_EQ_ISSUES_CELLMLELEMENTTYPES_LEVELS_REFERENCERULES_URLS(expectedIssues,
                                                                   expectedCellmlElementTypes(expectedIssues.size(), libcellml::CellmlElementType::VARIABLE),
                                                                   expectedLevels(expectedIssues.size(), libcellml::Issue::Level::ERROR),
                                                                   expectedReferenceRules(expectedIssues.size(), libcellml::Issue::ReferenceRule::ANALYSER_VARIABLE_NON_CONSTANT_INITIALISATION),
                                                                   expectedUrls(expectedIssues.size(), "https://libcellml.org/documentation/guides/latest/runtime_codes/index?issue=ANALYSER_VARIABLE_NON_CONSTANT_INITIALISATION"),
                                                                   analyser);

    EXPECT_EQ(libcellml::AnalyserModel::Type::INVALID, analyser->model()->type());
}

TEST(Analyser, nonExistingInitialisingVariable)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("analyser/non_existing_initialising_variable.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    const std::vector<std::string> expectedIssues = {
        "Variable 'x' in component 'main' has an invalid initial value 'k'. Initial values must be a real number string or a variable reference.",
    };

    auto analyser = libcellml::Analyser::create();

    analyser->analyseModel(model);

    EXPECT_EQ_ISSUES_CELLMLELEMENTTYPES_LEVELS_REFERENCERULES_URLS(expectedIssues,
                                                                   expectedCellmlElementTypes(expectedIssues.size(), libcellml::CellmlElementType::VARIABLE),
                                                                   expectedLevels(expectedIssues.size(), libcellml::Issue::Level::ERROR),
                                                                   expectedReferenceRules(expectedIssues.size(), libcellml::Issue::ReferenceRule::VARIABLE_INITIAL_VALUE),
                                                                   expectedUrls(expectedIssues.size(), "https://cellml-specification.readthedocs.io/en/latest/reference/formal_and_informative/specB08.html?issue=VARIABLE_INITIAL_VALUE"),
                                                                   analyser);

    EXPECT_EQ(libcellml::AnalyserModel::Type::INVALID, analyser->model()->type());
}

TEST(Analyser, nonInitialisedState)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("analyser/non_initialised_state.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    const std::vector<std::string> expectedIssues = {
        "Variable 'x' in component 'my_component' is used in an ODE, but it is not initialised.",
    };
    const std::string expectedVariableName = "x";

    auto analyser = libcellml::Analyser::create();

    analyser->analyseModel(model);

    EXPECT_EQ_ISSUES_CELLMLELEMENTTYPES_LEVELS_REFERENCERULES_URLS(expectedIssues,
                                                                   expectedCellmlElementTypes(expectedIssues.size(), libcellml::CellmlElementType::VARIABLE),
                                                                   expectedLevels(expectedIssues.size(), libcellml::Issue::Level::ERROR),
                                                                   expectedReferenceRules(expectedIssues.size(), libcellml::Issue::ReferenceRule::ANALYSER_STATE_NOT_INITIALISED),
                                                                   expectedUrls(expectedIssues.size(), "https://libcellml.org/documentation/guides/latest/runtime_codes/index?issue=ANALYSER_STATE_NOT_INITIALISED"),
                                                                   analyser);
    EXPECT_EQ(expectedVariableName, analyser->issue(0)->item()->variable()->name());

    EXPECT_EQ(libcellml::AnalyserModel::Type::UNDERCONSTRAINED, analyser->model()->type());
    EXPECT_EQ("underconstrained", libcellml::AnalyserModel::typeAsString(analyser->model()->type()));
}

TEST(Analyser, underconstrained)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("analyser/underconstrained.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    const std::vector<std::string> expectedIssues = {
        "Variable 'x' in component 'my_component' is unused.",
    };

    auto analyser = libcellml::Analyser::create();

    analyser->analyseModel(model);

    EXPECT_EQ_ISSUES_CELLMLELEMENTTYPES_LEVELS_REFERENCERULES_URLS(expectedIssues,
                                                                   expectedCellmlElementTypes(expectedIssues.size(), libcellml::CellmlElementType::VARIABLE),
                                                                   expectedLevels(expectedIssues.size(), libcellml::Issue::Level::ERROR),
                                                                   expectedReferenceRules(expectedIssues.size(), libcellml::Issue::ReferenceRule::ANALYSER_VARIABLE_UNUSED),
                                                                   expectedUrls(expectedIssues.size(), "https://libcellml.org/documentation/guides/latest/runtime_codes/index?issue=ANALYSER_VARIABLE_UNUSED"),
                                                                   analyser);

    EXPECT_EQ(libcellml::AnalyserModel::Type::UNDERCONSTRAINED, analyser->model()->type());
}

TEST(Analyser, overconstrainedOneVariable)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("analyser/overconstrained_one_variable.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    const std::vector<std::string> expectedIssues = {
        "Variable 'x' in component 'my_component' is computed more than once.",
    };

    auto analyser = libcellml::Analyser::create();

    analyser->analyseModel(model);

    EXPECT_EQ_ISSUES_CELLMLELEMENTTYPES_LEVELS_REFERENCERULES_URLS(expectedIssues,
                                                                   expectedCellmlElementTypes(expectedIssues.size(), libcellml::CellmlElementType::VARIABLE),
                                                                   expectedLevels(expectedIssues.size(), libcellml::Issue::Level::ERROR),
                                                                   expectedReferenceRules(expectedIssues.size(), libcellml::Issue::ReferenceRule::ANALYSER_VARIABLE_COMPUTED_MORE_THAN_ONCE),
                                                                   expectedUrls(expectedIssues.size(), "https://libcellml.org/documentation/guides/latest/runtime_codes/index?issue=ANALYSER_VARIABLE_COMPUTED_MORE_THAN_ONCE"),
                                                                   analyser);

    EXPECT_EQ(libcellml::AnalyserModel::Type::OVERCONSTRAINED, analyser->model()->type());
    EXPECT_EQ("overconstrained", libcellml::AnalyserModel::typeAsString(analyser->model()->type()));
}

TEST(Analyser, overconstrainedTwoVariables)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("analyser/overconstrained_two_variables.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    const std::vector<std::string> expectedIssues = {
        "Variable 'y' in component 'my_component' is computed more than once.",
        "Variable 'x' in component 'my_component' is computed more than once.",
    };

    auto analyser = libcellml::Analyser::create();

    analyser->analyseModel(model);

    EXPECT_EQ_ISSUES_CELLMLELEMENTTYPES_LEVELS_REFERENCERULES_URLS(expectedIssues,
                                                                   expectedCellmlElementTypes(expectedIssues.size(), libcellml::CellmlElementType::VARIABLE),
                                                                   expectedLevels(expectedIssues.size(), libcellml::Issue::Level::ERROR),
                                                                   expectedReferenceRules(expectedIssues.size(), libcellml::Issue::ReferenceRule::ANALYSER_VARIABLE_COMPUTED_MORE_THAN_ONCE),
                                                                   expectedUrls(expectedIssues.size(), "https://libcellml.org/documentation/guides/latest/runtime_codes/index?issue=ANALYSER_VARIABLE_COMPUTED_MORE_THAN_ONCE"),
                                                                   analyser);

    EXPECT_EQ(libcellml::AnalyserModel::Type::OVERCONSTRAINED, analyser->model()->type());
}

TEST(Analyser, overconstrainedThreeVariables)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("analyser/overconstrained_three_variables.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    const std::vector<std::string> expectedIssues = {
        "Variable 'z' in component 'my_component' is computed more than once.",
        "Variable 'x' in component 'my_component' is computed more than once.",
        "Variable 'y' in component 'my_component' is computed more than once.",
    };

    auto analyser = libcellml::Analyser::create();

    analyser->analyseModel(model);

    EXPECT_EQ_ISSUES_CELLMLELEMENTTYPES_LEVELS_REFERENCERULES_URLS(expectedIssues,
                                                                   expectedCellmlElementTypes(expectedIssues.size(), libcellml::CellmlElementType::VARIABLE),
                                                                   expectedLevels(expectedIssues.size(), libcellml::Issue::Level::ERROR),
                                                                   expectedReferenceRules(expectedIssues.size(), libcellml::Issue::ReferenceRule::ANALYSER_VARIABLE_COMPUTED_MORE_THAN_ONCE),
                                                                   expectedUrls(expectedIssues.size(), "https://libcellml.org/documentation/guides/latest/runtime_codes/index?issue=ANALYSER_VARIABLE_COMPUTED_MORE_THAN_ONCE"),
                                                                   analyser);

    EXPECT_EQ(libcellml::AnalyserModel::Type::OVERCONSTRAINED, analyser->model()->type());
}

TEST(Analyser, unsuitablyConstrained)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("analyser/unsuitably_constrained.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    const std::vector<std::string> expectedIssues = {
        "Variable 'y' in component 'my_component' is computed more than once.",
        "Variable 'x' in component 'my_component' is unused.",
    };
    const std::vector<libcellml::Issue::ReferenceRule> expectedReferenceRules = {
        libcellml::Issue::ReferenceRule::ANALYSER_VARIABLE_COMPUTED_MORE_THAN_ONCE,
        libcellml::Issue::ReferenceRule::ANALYSER_VARIABLE_UNUSED,
    };
    const std::vector<std::string> expectedUrls = {
        "https://libcellml.org/documentation/guides/latest/runtime_codes/index?issue=ANALYSER_VARIABLE_COMPUTED_MORE_THAN_ONCE",
        "https://libcellml.org/documentation/guides/latest/runtime_codes/index?issue=ANALYSER_VARIABLE_UNUSED",
    };

    auto analyser = libcellml::Analyser::create();

    analyser->analyseModel(model);

    EXPECT_EQ_ISSUES_CELLMLELEMENTTYPES_LEVELS_REFERENCERULES_URLS(expectedIssues,
                                                                   expectedCellmlElementTypes(expectedIssues.size(), libcellml::CellmlElementType::VARIABLE),
                                                                   expectedLevels(expectedIssues.size(), libcellml::Issue::Level::ERROR),
                                                                   expectedReferenceRules,
                                                                   expectedUrls,
                                                                   analyser);

    EXPECT_EQ(libcellml::AnalyserModel::Type::UNSUITABLY_CONSTRAINED, analyser->model()->type());
    EXPECT_EQ("unsuitably_constrained", libcellml::AnalyserModel::typeAsString(analyser->model()->type()));
}

TEST(Analyser, addSameExternalVariable)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("generator/hodgkin_huxley_squid_axon_model_1952/model.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    auto analyser = libcellml::Analyser::create();
    auto externalVariable = libcellml::AnalyserExternalVariable::create(model->component("membrane")->variable("V"));

    analyser->addExternalVariable(externalVariable);

    EXPECT_EQ(size_t(1), analyser->externalVariableCount());

    analyser->addExternalVariable(externalVariable);

    EXPECT_EQ(size_t(1), analyser->externalVariableCount());
}

TEST(Analyser, addExternalVariableFromDifferentModels)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("generator/hodgkin_huxley_squid_axon_model_1952/model.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    auto other_model = parser->parseModel(fileContents("generator/hodgkin_huxley_squid_axon_model_1952/model.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    const std::vector<std::string> expectedIssues = {
        "Variable 'V' in component 'membrane' is marked as an external variable, but it belongs to a different model and will therefore be ignored.",
    };

    auto analyser = libcellml::Analyser::create();

    analyser->addExternalVariable(libcellml::AnalyserExternalVariable::create(model->component("membrane")->variable("V")));
    analyser->addExternalVariable(libcellml::AnalyserExternalVariable::create(other_model->component("membrane")->variable("V")));

    EXPECT_EQ(size_t(2), analyser->externalVariableCount());

    analyser->analyseModel(model);

    EXPECT_EQ(size_t(1), analyser->messageCount());
    EXPECT_EQ(expectedIssues[0], analyser->message(0)->description());

    EXPECT_EQ_ISSUES_CELLMLELEMENTTYPES_LEVELS_REFERENCERULES_URLS(expectedIssues,
                                                                   expectedCellmlElementTypes(expectedIssues.size(), libcellml::CellmlElementType::VARIABLE),
                                                                   expectedLevels(expectedIssues.size(), libcellml::Issue::Level::MESSAGE),
                                                                   expectedReferenceRules(expectedIssues.size(), libcellml::Issue::ReferenceRule::ANALYSER_EXTERNAL_VARIABLE_DIFFERENT_MODEL),
                                                                   expectedUrls(expectedIssues.size(), "https://libcellml.org/documentation/guides/latest/runtime_codes/index?issue=ANALYSER_EXTERNAL_VARIABLE_DIFFERENT_MODEL"),
                                                                   analyser);
}

TEST(Analyser, removeExternalVariableByIndex)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("generator/hodgkin_huxley_squid_axon_model_1952/model.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    auto analyser = libcellml::Analyser::create();

    EXPECT_FALSE(analyser->removeExternalVariable(0));

    analyser->addExternalVariable(libcellml::AnalyserExternalVariable::create(model->component("membrane")->variable("V")));

    EXPECT_TRUE(analyser->removeExternalVariable(0));
    EXPECT_FALSE(analyser->removeExternalVariable(1));
}

TEST(Analyser, removeExternalVariableByName)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("generator/hodgkin_huxley_squid_axon_model_1952/model.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    auto analyser = libcellml::Analyser::create();

    EXPECT_FALSE(analyser->removeExternalVariable(model, "membrane", "V"));

    analyser->addExternalVariable(libcellml::AnalyserExternalVariable::create(model->component("membrane")->variable("V")));

    EXPECT_FALSE(analyser->removeExternalVariable(nullptr, "membrane", "V"));
    EXPECT_FALSE(analyser->removeExternalVariable(model, "X", "V"));
    EXPECT_FALSE(analyser->removeExternalVariable(model, "membrane", "X"));
    EXPECT_TRUE(analyser->removeExternalVariable(model, "membrane", "V"));
    EXPECT_FALSE(analyser->removeExternalVariable(model, "membrane", "V"));
}

TEST(Analyser, removeExternalVariableByPointer)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("generator/hodgkin_huxley_squid_axon_model_1952/model.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    auto analyser = libcellml::Analyser::create();
    auto externalVariable = libcellml::AnalyserExternalVariable::create(model->component("membrane")->variable("V"));

    EXPECT_FALSE(analyser->removeExternalVariable(externalVariable));

    analyser->addExternalVariable(externalVariable);

    EXPECT_FALSE(analyser->removeExternalVariable(nullptr));
    EXPECT_TRUE(analyser->removeExternalVariable(externalVariable));
    EXPECT_FALSE(analyser->removeExternalVariable(externalVariable));
}

TEST(Analyser, removeAllExternalVariables)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("generator/hodgkin_huxley_squid_axon_model_1952/model.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    auto analyser = libcellml::Analyser::create();

    analyser->addExternalVariable(libcellml::AnalyserExternalVariable::create(model->component("membrane")->variable("V")));
    analyser->addExternalVariable(libcellml::AnalyserExternalVariable::create(model->component("sodium_channel")->variable("V")));
    analyser->addExternalVariable(libcellml::AnalyserExternalVariable::create(model->component("potassium_channel")->variable("V")));

    EXPECT_EQ(size_t(3), analyser->externalVariableCount());

    analyser->removeAllExternalVariables();

    EXPECT_EQ(size_t(0), analyser->externalVariableCount());
}

TEST(Analyser, containsExternalVariableByName)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("generator/hodgkin_huxley_squid_axon_model_1952/model.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    auto analyser = libcellml::Analyser::create();

    analyser->addExternalVariable(libcellml::AnalyserExternalVariable::create(model->component("membrane")->variable("V")));

    EXPECT_TRUE(analyser->containsExternalVariable(model, "membrane", "V"));
    EXPECT_FALSE(analyser->containsExternalVariable(model, "membrane", "X"));
}

TEST(Analyser, containsExternalVariableByPointer)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("generator/hodgkin_huxley_squid_axon_model_1952/model.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    auto analyser = libcellml::Analyser::create();
    auto externalVariable = libcellml::AnalyserExternalVariable::create(model->component("membrane")->variable("V"));

    analyser->addExternalVariable(externalVariable);

    EXPECT_TRUE(analyser->containsExternalVariable(externalVariable));
    EXPECT_FALSE(analyser->containsExternalVariable(nullptr));
}

TEST(Analyser, externalVariableByIndex)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("generator/hodgkin_huxley_squid_axon_model_1952/model.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    auto analyser = libcellml::Analyser::create();

    EXPECT_EQ(nullptr, analyser->externalVariable(0));

    auto externalVariable = libcellml::AnalyserExternalVariable::create(model->component("membrane")->variable("V"));

    analyser->addExternalVariable(externalVariable);

    EXPECT_EQ(externalVariable, analyser->externalVariable(0));
    EXPECT_EQ(nullptr, analyser->externalVariable(1));
}

TEST(Analyser, externalVariableByName)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("generator/hodgkin_huxley_squid_axon_model_1952/model.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    auto analyser = libcellml::Analyser::create();

    EXPECT_EQ(nullptr, analyser->externalVariable(model, "membrane", "V"));

    auto externalVariable = libcellml::AnalyserExternalVariable::create(model->component("membrane")->variable("V"));

    analyser->addExternalVariable(externalVariable);

    EXPECT_EQ(externalVariable, analyser->externalVariable(model, "membrane", "V"));
    EXPECT_EQ(nullptr, analyser->externalVariable(model, "membrane", "X"));
}

TEST(Analyser, onePrimaryVoiExternalVariable)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("generator/hodgkin_huxley_squid_axon_model_1952/model.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    const std::vector<std::string> expectedIssues = {
        "Variable 'time' in component 'environment' is marked as an external variable, but it is the variable of integration which cannot be used as an external variable.",
    };

    auto analyser = libcellml::Analyser::create();

    analyser->addExternalVariable(libcellml::AnalyserExternalVariable::create(model->component("environment")->variable("time")));

    analyser->analyseModel(model);

    EXPECT_EQ_ISSUES(expectedIssues, analyser);
}

TEST(Analyser, oneNonPrimaryVoiExternalVariable)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("generator/hodgkin_huxley_squid_axon_model_1952/model.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    const std::vector<std::string> expectedIssues = {
        "Variable 'time' in component 'membrane' is marked as an external variable, but it is equivalent to variable 'time' in component 'environment', the primary variable of integration which cannot be used as an external variable.",
    };

    auto analyser = libcellml::Analyser::create();

    analyser->addExternalVariable(libcellml::AnalyserExternalVariable::create(model->component("membrane")->variable("time")));

    analyser->analyseModel(model);

    EXPECT_EQ_ISSUES(expectedIssues, analyser);
}

TEST(Analyser, twoEquivalentVoiExternalVariablesIncludingPrimaryVariable)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("generator/hodgkin_huxley_squid_axon_model_1952/model.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    const std::vector<std::string> expectedIssues = {
        "Both variable 'time' in component 'environment' and variable 'time' in component 'membrane' are marked as external variables, but they are equivalent to variable 'time' in component 'environment', the primary variable of integration which cannot be used as an external variable.",
    };

    auto analyser = libcellml::Analyser::create();

    analyser->addExternalVariable(libcellml::AnalyserExternalVariable::create(model->component("environment")->variable("time")));
    analyser->addExternalVariable(libcellml::AnalyserExternalVariable::create(model->component("membrane")->variable("time")));

    analyser->analyseModel(model);

    EXPECT_EQ_ISSUES_CELLMLELEMENTTYPES_LEVELS_REFERENCERULES_URLS(expectedIssues,
                                                                   expectedCellmlElementTypes(expectedIssues.size(), libcellml::CellmlElementType::VARIABLE),
                                                                   expectedLevels(expectedIssues.size(), libcellml::Issue::Level::MESSAGE),
                                                                   expectedReferenceRules(expectedIssues.size(), libcellml::Issue::ReferenceRule::ANALYSER_EXTERNAL_VARIABLE_VOI),
                                                                   expectedUrls(expectedIssues.size(), "https://libcellml.org/documentation/guides/latest/runtime_codes/index?issue=ANALYSER_EXTERNAL_VARIABLE_VOI"),
                                                                   analyser);
}

TEST(Analyser, twoEquivalentVoiExternalVariablesNotIncludingPrimaryVariable)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("generator/hodgkin_huxley_squid_axon_model_1952/model.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    const std::vector<std::string> expectedIssues = {
        "Both variable 'time' in component 'membrane' and variable 'time' in component 'sodium_channel' are marked as external variables, but they are equivalent to variable 'time' in component 'environment', the primary variable of integration which cannot be used as an external variable.",
    };

    auto analyser = libcellml::Analyser::create();

    analyser->addExternalVariable(libcellml::AnalyserExternalVariable::create(model->component("membrane")->variable("time")));
    analyser->addExternalVariable(libcellml::AnalyserExternalVariable::create(model->component("sodium_channel")->variable("time")));

    analyser->analyseModel(model);

    EXPECT_EQ_ISSUES_CELLMLELEMENTTYPES_LEVELS_REFERENCERULES_URLS(expectedIssues,
                                                                   expectedCellmlElementTypes(expectedIssues.size(), libcellml::CellmlElementType::VARIABLE),
                                                                   expectedLevels(expectedIssues.size(), libcellml::Issue::Level::MESSAGE),
                                                                   expectedReferenceRules(expectedIssues.size(), libcellml::Issue::ReferenceRule::ANALYSER_EXTERNAL_VARIABLE_VOI),
                                                                   expectedUrls(expectedIssues.size(), "https://libcellml.org/documentation/guides/latest/runtime_codes/index?issue=ANALYSER_EXTERNAL_VARIABLE_VOI"),
                                                                   analyser);
}

TEST(Analyser, threeEquivalentVoiExternalVariablesIncludingPrimaryVariable)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("generator/hodgkin_huxley_squid_axon_model_1952/model.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    const std::vector<std::string> expectedIssues = {
        "Variable 'time' in component 'environment', variable 'time' in component 'membrane' and variable 'time' in component 'sodium_channel' are marked as external variables, but they are equivalent to variable 'time' in component 'environment', the primary variable of integration which cannot be used as an external variable.",
    };

    auto analyser = libcellml::Analyser::create();

    analyser->addExternalVariable(libcellml::AnalyserExternalVariable::create(model->component("environment")->variable("time")));
    analyser->addExternalVariable(libcellml::AnalyserExternalVariable::create(model->component("membrane")->variable("time")));
    analyser->addExternalVariable(libcellml::AnalyserExternalVariable::create(model->component("sodium_channel")->variable("time")));

    analyser->analyseModel(model);

    EXPECT_EQ_ISSUES_CELLMLELEMENTTYPES_LEVELS_REFERENCERULES_URLS(expectedIssues,
                                                                   expectedCellmlElementTypes(expectedIssues.size(), libcellml::CellmlElementType::VARIABLE),
                                                                   expectedLevels(expectedIssues.size(), libcellml::Issue::Level::MESSAGE),
                                                                   expectedReferenceRules(expectedIssues.size(), libcellml::Issue::ReferenceRule::ANALYSER_EXTERNAL_VARIABLE_VOI),
                                                                   expectedUrls(expectedIssues.size(), "https://libcellml.org/documentation/guides/latest/runtime_codes/index?issue=ANALYSER_EXTERNAL_VARIABLE_VOI"),
                                                                   analyser);
}

TEST(Analyser, threeEquivalentVoiExternalVariablesNotIncludingPrimaryVariable)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("generator/hodgkin_huxley_squid_axon_model_1952/model.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    const std::vector<std::string> expectedIssues = {
        "Variable 'time' in component 'membrane', variable 'time' in component 'sodium_channel' and variable 'time' in component 'potassium_channel' are marked as external variables, but they are equivalent to variable 'time' in component 'environment', the primary variable of integration which cannot be used as an external variable.",
    };

    auto analyser = libcellml::Analyser::create();

    analyser->addExternalVariable(libcellml::AnalyserExternalVariable::create(model->component("membrane")->variable("time")));
    analyser->addExternalVariable(libcellml::AnalyserExternalVariable::create(model->component("sodium_channel")->variable("time")));
    analyser->addExternalVariable(libcellml::AnalyserExternalVariable::create(model->component("potassium_channel")->variable("time")));

    analyser->analyseModel(model);

    EXPECT_EQ_ISSUES_CELLMLELEMENTTYPES_LEVELS_REFERENCERULES_URLS(expectedIssues,
                                                                   expectedCellmlElementTypes(expectedIssues.size(), libcellml::CellmlElementType::VARIABLE),
                                                                   expectedLevels(expectedIssues.size(), libcellml::Issue::Level::MESSAGE),
                                                                   expectedReferenceRules(expectedIssues.size(), libcellml::Issue::ReferenceRule::ANALYSER_EXTERNAL_VARIABLE_VOI),
                                                                   expectedUrls(expectedIssues.size(), "https://libcellml.org/documentation/guides/latest/runtime_codes/index?issue=ANALYSER_EXTERNAL_VARIABLE_VOI"),
                                                                   analyser);
}

TEST(Analyser, onePrimaryExternalVariable)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("generator/hodgkin_huxley_squid_axon_model_1952/model.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    auto analyser = libcellml::Analyser::create();

    analyser->addExternalVariable(libcellml::AnalyserExternalVariable::create(model->component("membrane")->variable("V")));

    analyser->analyseModel(model);

    EXPECT_EQ(size_t(0), analyser->issueCount());
}

TEST(Analyser, oneNonPrimaryExternalVariable)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("generator/hodgkin_huxley_squid_axon_model_1952/model.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    const std::vector<std::string> expectedIssues = {
        "Variable 'V' in component 'sodium_channel' is marked as an external variable, but it is not a primary variable. Variable 'V' in component 'membrane' is its corresponding primary variable and will therefore be the one used as an external variable.",
    };

    auto analyser = libcellml::Analyser::create();

    analyser->addExternalVariable(libcellml::AnalyserExternalVariable::create(model->component("sodium_channel")->variable("V")));

    analyser->analyseModel(model);

    EXPECT_EQ_ISSUES_CELLMLELEMENTTYPES_LEVELS_REFERENCERULES_URLS(expectedIssues,
                                                                   expectedCellmlElementTypes(expectedIssues.size(), libcellml::CellmlElementType::VARIABLE),
                                                                   expectedLevels(expectedIssues.size(), libcellml::Issue::Level::MESSAGE),
                                                                   expectedReferenceRules(expectedIssues.size(), libcellml::Issue::ReferenceRule::ANALYSER_EXTERNAL_VARIABLE_USE_PRIMARY_VARIABLE),
                                                                   expectedUrls(expectedIssues.size(), "https://libcellml.org/documentation/guides/latest/runtime_codes/index?issue=ANALYSER_EXTERNAL_VARIABLE_USE_PRIMARY_VARIABLE"),
                                                                   analyser);
}

TEST(Analyser, twoEquivalentExternalVariablesIncludingPrimaryVariable)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("generator/hodgkin_huxley_squid_axon_model_1952/model.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    const std::vector<std::string> expectedIssues = {
        "Both variable 'V' in component 'membrane' and variable 'V' in component 'sodium_channel' are marked as external variables, but they are equivalent. Variable 'V' in component 'membrane' is the primary variable and will therefore be the one used as an external variable.",
    };

    auto analyser = libcellml::Analyser::create();

    analyser->addExternalVariable(libcellml::AnalyserExternalVariable::create(model->component("membrane")->variable("V")));
    analyser->addExternalVariable(libcellml::AnalyserExternalVariable::create(model->component("sodium_channel")->variable("V")));

    analyser->analyseModel(model);

    EXPECT_EQ_ISSUES_CELLMLELEMENTTYPES_LEVELS_REFERENCERULES_URLS(expectedIssues,
                                                                   expectedCellmlElementTypes(expectedIssues.size(), libcellml::CellmlElementType::VARIABLE),
                                                                   expectedLevels(expectedIssues.size(), libcellml::Issue::Level::MESSAGE),
                                                                   expectedReferenceRules(expectedIssues.size(), libcellml::Issue::ReferenceRule::ANALYSER_EXTERNAL_VARIABLE_USE_PRIMARY_VARIABLE),
                                                                   expectedUrls(expectedIssues.size(), "https://libcellml.org/documentation/guides/latest/runtime_codes/index?issue=ANALYSER_EXTERNAL_VARIABLE_USE_PRIMARY_VARIABLE"),
                                                                   analyser);
}

TEST(Analyser, twoEquivalentExternalVariablesNotIncludingPrimaryVariable)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("generator/hodgkin_huxley_squid_axon_model_1952/model.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    const std::vector<std::string> expectedIssues = {
        "Both variable 'V' in component 'sodium_channel' and variable 'V' in component 'potassium_channel' are marked as external variables, but they are equivalent. Variable 'V' in component 'membrane' is their corresponding primary variable and will therefore be the one used as an external variable.",
    };

    auto analyser = libcellml::Analyser::create();

    analyser->addExternalVariable(libcellml::AnalyserExternalVariable::create(model->component("sodium_channel")->variable("V")));
    analyser->addExternalVariable(libcellml::AnalyserExternalVariable::create(model->component("potassium_channel")->variable("V")));

    analyser->analyseModel(model);

    EXPECT_EQ_ISSUES_CELLMLELEMENTTYPES_LEVELS_REFERENCERULES_URLS(expectedIssues,
                                                                   expectedCellmlElementTypes(expectedIssues.size(), libcellml::CellmlElementType::VARIABLE),
                                                                   expectedLevels(expectedIssues.size(), libcellml::Issue::Level::MESSAGE),
                                                                   expectedReferenceRules(expectedIssues.size(), libcellml::Issue::ReferenceRule::ANALYSER_EXTERNAL_VARIABLE_USE_PRIMARY_VARIABLE),
                                                                   expectedUrls(expectedIssues.size(), "https://libcellml.org/documentation/guides/latest/runtime_codes/index?issue=ANALYSER_EXTERNAL_VARIABLE_USE_PRIMARY_VARIABLE"),
                                                                   analyser);
}

TEST(Analyser, threeEquivalentExternalVariablesIncludingPrimaryVariable)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("generator/hodgkin_huxley_squid_axon_model_1952/model.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    const std::vector<std::string> expectedIssues = {
        "Variable 'V' in component 'membrane', variable 'V' in component 'sodium_channel' and variable 'V' in component 'potassium_channel' are marked as external variables, but they are all equivalent. Variable 'V' in component 'membrane' is the primary variable and will therefore be the one used as an external variable.",
    };

    auto analyser = libcellml::Analyser::create();

    analyser->addExternalVariable(libcellml::AnalyserExternalVariable::create(model->component("membrane")->variable("V")));
    analyser->addExternalVariable(libcellml::AnalyserExternalVariable::create(model->component("sodium_channel")->variable("V")));
    analyser->addExternalVariable(libcellml::AnalyserExternalVariable::create(model->component("potassium_channel")->variable("V")));

    analyser->analyseModel(model);

    EXPECT_EQ_ISSUES_CELLMLELEMENTTYPES_LEVELS_REFERENCERULES_URLS(expectedIssues,
                                                                   expectedCellmlElementTypes(expectedIssues.size(), libcellml::CellmlElementType::VARIABLE),
                                                                   expectedLevels(expectedIssues.size(), libcellml::Issue::Level::MESSAGE),
                                                                   expectedReferenceRules(expectedIssues.size(), libcellml::Issue::ReferenceRule::ANALYSER_EXTERNAL_VARIABLE_USE_PRIMARY_VARIABLE),
                                                                   expectedUrls(expectedIssues.size(), "https://libcellml.org/documentation/guides/latest/runtime_codes/index?issue=ANALYSER_EXTERNAL_VARIABLE_USE_PRIMARY_VARIABLE"),
                                                                   analyser);
}

TEST(Analyser, threeEquivalentExternalVariablesNotIncludingPrimaryVariable)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("generator/hodgkin_huxley_squid_axon_model_1952/model.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    const std::vector<std::string> expectedIssues = {
        "Variable 'V' in component 'sodium_channel', variable 'V' in component 'potassium_channel' and variable 'V' in component 'leakage_current' are marked as external variables, but they are all equivalent. Variable 'V' in component 'membrane' is their corresponding primary variable and will therefore be the one used as an external variable.",
    };

    auto analyser = libcellml::Analyser::create();

    analyser->addExternalVariable(libcellml::AnalyserExternalVariable::create(model->component("sodium_channel")->variable("V")));
    analyser->addExternalVariable(libcellml::AnalyserExternalVariable::create(model->component("potassium_channel")->variable("V")));
    analyser->addExternalVariable(libcellml::AnalyserExternalVariable::create(model->component("leakage_current")->variable("V")));

    analyser->analyseModel(model);

    EXPECT_EQ_ISSUES_CELLMLELEMENTTYPES_LEVELS_REFERENCERULES_URLS(expectedIssues,
                                                                   expectedCellmlElementTypes(expectedIssues.size(), libcellml::CellmlElementType::VARIABLE),
                                                                   expectedLevels(expectedIssues.size(), libcellml::Issue::Level::MESSAGE),
                                                                   expectedReferenceRules(expectedIssues.size(), libcellml::Issue::ReferenceRule::ANALYSER_EXTERNAL_VARIABLE_USE_PRIMARY_VARIABLE),
                                                                   expectedUrls(expectedIssues.size(), "https://libcellml.org/documentation/guides/latest/runtime_codes/index?issue=ANALYSER_EXTERNAL_VARIABLE_USE_PRIMARY_VARIABLE"),
                                                                   analyser);
}

TEST(Analyser, algebraicSystemWithThreeLinkedUnknownsWithOneExternalVariable)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("generator/algebraic_system_with_three_linked_unknowns/model.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    const std::vector<std::string> expectedIssues = {
        "Variable 'y' in component 'my_algebraic_system' is computed more than once.",
        "Variable 'z' in component 'my_algebraic_system' is computed more than once.",
    };

    auto analyser = libcellml::Analyser::create();

    analyser->addExternalVariable(libcellml::AnalyserExternalVariable::create(model->component("my_algebraic_system")->variable("x")));

    analyser->analyseModel(model);

    EXPECT_EQ_ISSUES_CELLMLELEMENTTYPES_LEVELS_REFERENCERULES_URLS(expectedIssues,
                                                                   expectedCellmlElementTypes(expectedIssues.size(), libcellml::CellmlElementType::VARIABLE),
                                                                   expectedLevels(expectedIssues.size(), libcellml::Issue::Level::ERROR),
                                                                   expectedReferenceRules(expectedIssues.size(), libcellml::Issue::ReferenceRule::ANALYSER_VARIABLE_COMPUTED_MORE_THAN_ONCE),
                                                                   expectedUrls(expectedIssues.size(), "https://libcellml.org/documentation/guides/latest/runtime_codes/index?issue=ANALYSER_VARIABLE_COMPUTED_MORE_THAN_ONCE"),
                                                                   analyser);

    EXPECT_EQ(libcellml::AnalyserModel::Type::OVERCONSTRAINED, analyser->model()->type());
}

TEST(Analyser, algebraicSystemWithThreeLinkedUnknownsWithTwoExternalVariables)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("generator/algebraic_system_with_three_linked_unknowns/model.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    const std::vector<std::string> expectedIssues = {
        "Variable 'y' in component 'my_algebraic_system' is computed more than once.",
    };

    auto analyser = libcellml::Analyser::create();

    analyser->addExternalVariable(libcellml::AnalyserExternalVariable::create(model->component("my_algebraic_system")->variable("x")));
    analyser->addExternalVariable(libcellml::AnalyserExternalVariable::create(model->component("my_algebraic_system")->variable("z")));

    analyser->analyseModel(model);

    EXPECT_EQ_ISSUES_CELLMLELEMENTTYPES_LEVELS_REFERENCERULES_URLS(expectedIssues,
                                                                   expectedCellmlElementTypes(expectedIssues.size(), libcellml::CellmlElementType::VARIABLE),
                                                                   expectedLevels(expectedIssues.size(), libcellml::Issue::Level::ERROR),
                                                                   expectedReferenceRules(expectedIssues.size(), libcellml::Issue::ReferenceRule::ANALYSER_VARIABLE_COMPUTED_MORE_THAN_ONCE),
                                                                   expectedUrls(expectedIssues.size(), "https://libcellml.org/documentation/guides/latest/runtime_codes/index?issue=ANALYSER_VARIABLE_COMPUTED_MORE_THAN_ONCE"),
                                                                   analyser);

    EXPECT_EQ(libcellml::AnalyserModel::Type::OVERCONSTRAINED, analyser->model()->type());
}

TEST(Analyser, overconstrainedNlaSystem)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("analyser/overconstrained_nla_system.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    const std::vector<std::string> expectedIssues = {
        "Variable 'x' in component 'my_algebraic_system' is computed more than once.",
        "Variable 'y' in component 'my_algebraic_system' is computed more than once.",
    };

    auto analyser = libcellml::Analyser::create();

    analyser->analyseModel(model);

    EXPECT_EQ_ISSUES_CELLMLELEMENTTYPES_LEVELS_REFERENCERULES_URLS(expectedIssues,
                                                                   expectedCellmlElementTypes(expectedIssues.size(), libcellml::CellmlElementType::VARIABLE),
                                                                   expectedLevels(expectedIssues.size(), libcellml::Issue::Level::ERROR),
                                                                   expectedReferenceRules(expectedIssues.size(), libcellml::Issue::ReferenceRule::ANALYSER_VARIABLE_COMPUTED_MORE_THAN_ONCE),
                                                                   expectedUrls(expectedIssues.size(), "https://libcellml.org/documentation/guides/latest/runtime_codes/index?issue=ANALYSER_VARIABLE_COMPUTED_MORE_THAN_ONCE"),
                                                                   analyser);

    EXPECT_EQ(libcellml::AnalyserModel::Type::OVERCONSTRAINED, analyser->model()->type());
}

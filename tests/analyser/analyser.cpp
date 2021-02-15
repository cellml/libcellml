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

TEST(Analyser, initialisedVariableOfIntegration)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("analyser/initialised_variable_of_integration.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    const std::vector<std::string> expectedIssues = {
        "Variable 'time' in component 'my_component' cannot be both a variable of integration and initialised.",
    };
    const std::vector<libcellml::CellmlElementType> expectedCellmlElementTypes = {
        libcellml::CellmlElementType::VARIABLE,
    };
    const std::vector<libcellml::Issue::Level> expectedLevels = {
        libcellml::Issue::Level::ERROR,
    };
    const std::vector<libcellml::Issue::ReferenceRule> expectedReferenceRules = {
        libcellml::Issue::ReferenceRule::ANALYSER_VOI_INITIALISED,
    };

    auto analyser = libcellml::Analyser::create();

    analyser->analyseModel(model);

    EXPECT_EQ_ISSUES_CELLMLELEMENTTYPES_LEVELS_REFERENCERULES(expectedIssues, expectedCellmlElementTypes, expectedLevels, expectedReferenceRules, analyser);

    EXPECT_EQ(libcellml::AnalyserModel::Type::INVALID, analyser->model()->type());
}

TEST(Analyser, initialisedVariableOfIntegrationInNonFirstComponent)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("analyser/initialised_variable_of_integration_in_non_first_component.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    const std::vector<std::string> expectedIssues = {
        "Variable 'time' in component 'environment' cannot be both a variable of integration and initialised.",
    };
    const std::vector<libcellml::CellmlElementType> expectedCellmlElementTypes = {
        libcellml::CellmlElementType::VARIABLE,
    };
    const std::vector<libcellml::Issue::Level> expectedLevels = {
        libcellml::Issue::Level::ERROR,
    };
    const std::vector<libcellml::Issue::ReferenceRule> expectedReferenceRules = {
        libcellml::Issue::ReferenceRule::ANALYSER_VOI_INITIALISED,
    };

    auto analyser = libcellml::Analyser::create();

    analyser->analyseModel(model);

    EXPECT_EQ_ISSUES_CELLMLELEMENTTYPES_LEVELS_REFERENCERULES(expectedIssues, expectedCellmlElementTypes, expectedLevels, expectedReferenceRules, analyser);

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
    const std::vector<libcellml::CellmlElementType> expectedCellmlElementTypes = {
        libcellml::CellmlElementType::VARIABLE,
    };
    const std::vector<libcellml::Issue::Level> expectedLevels = {
        libcellml::Issue::Level::ERROR,
    };
    const std::vector<libcellml::Issue::ReferenceRule> expectedReferenceRules = {
        libcellml::Issue::ReferenceRule::ANALYSER_VOI_SEVERAL,
    };

    auto analyser = libcellml::Analyser::create();

    analyser->analyseModel(model);

    EXPECT_EQ_ISSUES_CELLMLELEMENTTYPES_LEVELS_REFERENCERULES(expectedIssues, expectedCellmlElementTypes, expectedLevels, expectedReferenceRules, analyser);

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
    const std::vector<libcellml::CellmlElementType> expectedCellmlElementTypes = {
        libcellml::CellmlElementType::MATH,
        libcellml::CellmlElementType::MATH,
        libcellml::CellmlElementType::MATH,
    };
    const std::vector<libcellml::Issue::Level> expectedLevels = {
        libcellml::Issue::Level::ERROR,
        libcellml::Issue::Level::ERROR,
        libcellml::Issue::Level::ERROR,
    };
    const std::vector<libcellml::Issue::ReferenceRule> expectedReferenceRules = {
        libcellml::Issue::ReferenceRule::ANALYSER_ODE_NOT_FIRST_ORDER,
        libcellml::Issue::ReferenceRule::ANALYSER_ODE_NOT_FIRST_ORDER,
        libcellml::Issue::ReferenceRule::ANALYSER_ODE_NOT_FIRST_ORDER,
    };

    auto analyser = libcellml::Analyser::create();

    analyser->analyseModel(model);

    EXPECT_EQ_ISSUES_CELLMLELEMENTTYPES_LEVELS_REFERENCERULES(expectedIssues, expectedCellmlElementTypes, expectedLevels, expectedReferenceRules, analyser);

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
    const std::vector<libcellml::CellmlElementType> expectedCellmlElementTypes = {
        libcellml::CellmlElementType::MATH,
        libcellml::CellmlElementType::MATH,
    };
    const std::vector<libcellml::Issue::Level> expectedLevels = {
        libcellml::Issue::Level::ERROR,
        libcellml::Issue::Level::ERROR,
    };
    const std::vector<libcellml::Issue::ReferenceRule> expectedReferenceRules = {
        libcellml::Issue::ReferenceRule::MATH_CI_VARIABLE_REF,
        libcellml::Issue::ReferenceRule::MATH_CI_VARIABLE_REF,
    };

    auto analyser = libcellml::Analyser::create();

    analyser->analyseModel(model);

    EXPECT_EQ_ISSUES_CELLMLELEMENTTYPES_LEVELS_REFERENCERULES(expectedIssues, expectedCellmlElementTypes, expectedLevels, expectedReferenceRules, analyser);

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
    const std::vector<libcellml::CellmlElementType> expectedCellmlElementTypes = {
        libcellml::CellmlElementType::VARIABLE,
    };
    const std::vector<libcellml::Issue::Level> expectedLevels = {
        libcellml::Issue::Level::ERROR,
    };
    const std::vector<libcellml::Issue::ReferenceRule> expectedReferenceRules = {
        libcellml::Issue::ReferenceRule::ANALYSER_VARIABLE_INITIALISED_MORE_THAN_ONCE,
    };

    auto analyser = libcellml::Analyser::create();

    analyser->analyseModel(model);

    EXPECT_EQ_ISSUES_CELLMLELEMENTTYPES_LEVELS_REFERENCERULES(expectedIssues, expectedCellmlElementTypes, expectedLevels, expectedReferenceRules, analyser);

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
    const std::vector<libcellml::CellmlElementType> expectedCellmlElementTypes = {
        libcellml::CellmlElementType::VARIABLE,
    };
    const std::vector<libcellml::Issue::Level> expectedLevels = {
        libcellml::Issue::Level::ERROR,
    };
    const std::vector<libcellml::Issue::ReferenceRule> expectedReferenceRules = {
        libcellml::Issue::ReferenceRule::ANALYSER_VARIABLE_NON_CONSTANT_INITIALISATION,
    };

    auto analyser = libcellml::Analyser::create();

    analyser->analyseModel(model);

    EXPECT_EQ_ISSUES_CELLMLELEMENTTYPES_LEVELS_REFERENCERULES(expectedIssues, expectedCellmlElementTypes, expectedLevels, expectedReferenceRules, analyser);

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
    const std::vector<libcellml::CellmlElementType> expectedCellmlElementTypes = {
        libcellml::CellmlElementType::VARIABLE,
    };
    const std::vector<libcellml::Issue::Level> expectedLevels = {
        libcellml::Issue::Level::ERROR,
    };
    const std::vector<libcellml::Issue::ReferenceRule> expectedReferenceRules = {
        libcellml::Issue::ReferenceRule::VARIABLE_INITIAL_VALUE,
    };

    auto analyser = libcellml::Analyser::create();

    analyser->analyseModel(model);

    EXPECT_EQ_ISSUES_CELLMLELEMENTTYPES_LEVELS_REFERENCERULES(expectedIssues, expectedCellmlElementTypes, expectedLevels, expectedReferenceRules, analyser);

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
    const std::vector<libcellml::CellmlElementType> expectedCellmlElementTypes = {
        libcellml::CellmlElementType::VARIABLE,
    };
    const std::vector<libcellml::Issue::Level> expectedLevels = {
        libcellml::Issue::Level::ERROR,
    };
    const std::vector<libcellml::Issue::ReferenceRule> expectedReferenceRules = {
        libcellml::Issue::ReferenceRule::ANALYSER_STATE_NOT_INITIALISED,
    };
    const std::string expectedVariableName = "x";

    auto analyser = libcellml::Analyser::create();

    analyser->analyseModel(model);

    EXPECT_EQ_ISSUES_CELLMLELEMENTTYPES_LEVELS_REFERENCERULES(expectedIssues, expectedCellmlElementTypes, expectedLevels, expectedReferenceRules, analyser);
    EXPECT_EQ(expectedVariableName, analyser->issue(0)->variable()->name());

    EXPECT_EQ(libcellml::AnalyserModel::Type::UNDERCONSTRAINED, analyser->model()->type());
}

TEST(Analyser, underconstrained)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("analyser/underconstrained.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    const std::vector<std::string> expectedIssues = {
        "Variable 'x' in component 'my_component' is unused.",
    };
    const std::vector<libcellml::CellmlElementType> expectedCellmlElementTypes = {
        libcellml::CellmlElementType::VARIABLE,
    };
    const std::vector<libcellml::Issue::Level> expectedLevels = {
        libcellml::Issue::Level::ERROR,
    };
    const std::vector<libcellml::Issue::ReferenceRule> expectedReferenceRules = {
        libcellml::Issue::ReferenceRule::ANALYSER_VARIABLE_UNUSED,
    };

    auto analyser = libcellml::Analyser::create();

    analyser->analyseModel(model);

    EXPECT_EQ_ISSUES_CELLMLELEMENTTYPES_LEVELS_REFERENCERULES(expectedIssues, expectedCellmlElementTypes, expectedLevels, expectedReferenceRules, analyser);

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
    const std::vector<libcellml::CellmlElementType> expectedCellmlElementTypes = {
        libcellml::CellmlElementType::VARIABLE,
    };
    const std::vector<libcellml::Issue::Level> expectedLevels = {
        libcellml::Issue::Level::ERROR,
    };
    const std::vector<libcellml::Issue::ReferenceRule> expectedReferenceRules = {
        libcellml::Issue::ReferenceRule::ANALYSER_VARIABLE_COMPUTED_MORE_THAN_ONCE,
    };

    auto analyser = libcellml::Analyser::create();

    analyser->analyseModel(model);

    EXPECT_EQ_ISSUES_CELLMLELEMENTTYPES_LEVELS_REFERENCERULES(expectedIssues, expectedCellmlElementTypes, expectedLevels, expectedReferenceRules, analyser);

    EXPECT_EQ(libcellml::AnalyserModel::Type::OVERCONSTRAINED, analyser->model()->type());
}

TEST(Analyser, overconstrainedTwoVariables)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("analyser/overconstrained_two_variables.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    const std::vector<std::string> expectedIssues = {
        "Variable 'x' in component 'my_component' is computed more than once.",
        "Variable 'y' in component 'my_component' is computed more than once.",
    };
    const std::vector<libcellml::CellmlElementType> expectedCellmlElementTypes = {
        libcellml::CellmlElementType::VARIABLE,
        libcellml::CellmlElementType::VARIABLE,
    };
    const std::vector<libcellml::Issue::Level> expectedLevels = {
        libcellml::Issue::Level::ERROR,
        libcellml::Issue::Level::ERROR,
    };
    const std::vector<libcellml::Issue::ReferenceRule> expectedReferenceRules = {
        libcellml::Issue::ReferenceRule::ANALYSER_VARIABLE_COMPUTED_MORE_THAN_ONCE,
        libcellml::Issue::ReferenceRule::ANALYSER_VARIABLE_COMPUTED_MORE_THAN_ONCE,
    };

    auto analyser = libcellml::Analyser::create();

    analyser->analyseModel(model);

    EXPECT_EQ_ISSUES_CELLMLELEMENTTYPES_LEVELS_REFERENCERULES(expectedIssues, expectedCellmlElementTypes, expectedLevels, expectedReferenceRules, analyser);

    EXPECT_EQ(libcellml::AnalyserModel::Type::OVERCONSTRAINED, analyser->model()->type());
}

TEST(Analyser, overconstrainedThreeVariables)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("analyser/overconstrained_three_variables.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    const std::vector<std::string> expectedIssues = {
        "Variable 'x' in component 'my_component' is computed more than once.",
        "Variable 'y' in component 'my_component' is computed more than once.",
        "Variable 'z' in component 'my_component' is computed more than once.",
    };
    const std::vector<libcellml::CellmlElementType> expectedCellmlElementTypes = {
        libcellml::CellmlElementType::VARIABLE,
        libcellml::CellmlElementType::VARIABLE,
        libcellml::CellmlElementType::VARIABLE,
    };
    const std::vector<libcellml::Issue::Level> expectedLevels = {
        libcellml::Issue::Level::ERROR,
        libcellml::Issue::Level::ERROR,
        libcellml::Issue::Level::ERROR,
    };
    const std::vector<libcellml::Issue::ReferenceRule> expectedReferenceRules = {
        libcellml::Issue::ReferenceRule::ANALYSER_VARIABLE_COMPUTED_MORE_THAN_ONCE,
        libcellml::Issue::ReferenceRule::ANALYSER_VARIABLE_COMPUTED_MORE_THAN_ONCE,
        libcellml::Issue::ReferenceRule::ANALYSER_VARIABLE_COMPUTED_MORE_THAN_ONCE,
    };

    auto analyser = libcellml::Analyser::create();

    analyser->analyseModel(model);

    EXPECT_EQ_ISSUES_CELLMLELEMENTTYPES_LEVELS_REFERENCERULES(expectedIssues, expectedCellmlElementTypes, expectedLevels, expectedReferenceRules, analyser);

    EXPECT_EQ(libcellml::AnalyserModel::Type::OVERCONSTRAINED, analyser->model()->type());
}

TEST(Analyser, unsuitablyConstrained)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("analyser/unsuitably_constrained.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    const std::vector<std::string> expectedIssues = {
        "Variable 'x' in component 'my_component' is unused.",
        "Variable 'y' in component 'my_component' is computed more than once.",
    };
    const std::vector<libcellml::CellmlElementType> expectedCellmlElementTypes = {
        libcellml::CellmlElementType::VARIABLE,
        libcellml::CellmlElementType::VARIABLE,
    };
    const std::vector<libcellml::Issue::Level> expectedLevels = {
        libcellml::Issue::Level::ERROR,
        libcellml::Issue::Level::ERROR,
    };
    const std::vector<libcellml::Issue::ReferenceRule> expectedReferenceRules = {
        libcellml::Issue::ReferenceRule::ANALYSER_VARIABLE_UNUSED,
        libcellml::Issue::ReferenceRule::ANALYSER_VARIABLE_COMPUTED_MORE_THAN_ONCE,
    };

    auto analyser = libcellml::Analyser::create();

    analyser->analyseModel(model);

    EXPECT_EQ_ISSUES_CELLMLELEMENTTYPES_LEVELS_REFERENCERULES(expectedIssues, expectedCellmlElementTypes, expectedLevels, expectedReferenceRules, analyser);

    EXPECT_EQ(libcellml::AnalyserModel::Type::UNSUITABLY_CONSTRAINED, analyser->model()->type());
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
    const std::vector<libcellml::CellmlElementType> expectedCellmlElementTypes = {
        libcellml::CellmlElementType::VARIABLE,
    };
    const std::vector<libcellml::Issue::Level> expectedLevels = {
        libcellml::Issue::Level::MESSAGE,
    };
    const std::vector<libcellml::Issue::ReferenceRule> expectedReferenceRules = {
        libcellml::Issue::ReferenceRule::ANALYSER_EXTERNAL_VARIABLE_DIFFERENT_MODEL,
    };

    auto analyser = libcellml::Analyser::create();

    analyser->addExternalVariable(libcellml::AnalyserExternalVariable::create(model->component("membrane")->variable("V")));
    analyser->addExternalVariable(libcellml::AnalyserExternalVariable::create(other_model->component("membrane")->variable("V")));

    EXPECT_EQ(size_t(2), analyser->externalVariableCount());

    analyser->analyseModel(model);

    EXPECT_EQ_ISSUES_CELLMLELEMENTTYPES_LEVELS_REFERENCERULES(expectedIssues, expectedCellmlElementTypes, expectedLevels, expectedReferenceRules, analyser);
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

    EXPECT_TRUE(analyser->removeExternalVariable(model, "membrane", "V"));
    EXPECT_FALSE(analyser->removeExternalVariable(model, "membrane", "X"));
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

    EXPECT_TRUE(analyser->removeExternalVariable(externalVariable));
    EXPECT_FALSE(analyser->removeExternalVariable(externalVariable));
    EXPECT_FALSE(analyser->removeExternalVariable(nullptr));
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
    const std::vector<libcellml::CellmlElementType> expectedCellmlElementTypes = {
        libcellml::CellmlElementType::VARIABLE,
    };
    const std::vector<libcellml::Issue::Level> expectedLevels = {
        libcellml::Issue::Level::MESSAGE,
    };
    const std::vector<libcellml::Issue::ReferenceRule> expectedReferenceRules = {
        libcellml::Issue::ReferenceRule::ANALYSER_EXTERNAL_VARIABLE_VOI,
    };

    auto analyser = libcellml::Analyser::create();

    analyser->addExternalVariable(libcellml::AnalyserExternalVariable::create(model->component("environment")->variable("time")));
    analyser->addExternalVariable(libcellml::AnalyserExternalVariable::create(model->component("membrane")->variable("time")));

    analyser->analyseModel(model);

    EXPECT_EQ_ISSUES_CELLMLELEMENTTYPES_LEVELS_REFERENCERULES(expectedIssues, expectedCellmlElementTypes, expectedLevels, expectedReferenceRules, analyser);
}

TEST(Analyser, twoEquivalentVoiExternalVariablesNotIncludingPrimaryVariable)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("generator/hodgkin_huxley_squid_axon_model_1952/model.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    const std::vector<std::string> expectedIssues = {
        "Both variable 'time' in component 'membrane' and variable 'time' in component 'sodium_channel' are marked as external variables, but they are equivalent to variable 'time' in component 'environment', the primary variable of integration which cannot be used as an external variable.",
    };
    const std::vector<libcellml::CellmlElementType> expectedCellmlElementTypes = {
        libcellml::CellmlElementType::VARIABLE,
    };
    const std::vector<libcellml::Issue::Level> expectedLevels = {
        libcellml::Issue::Level::MESSAGE,
    };
    const std::vector<libcellml::Issue::ReferenceRule> expectedReferenceRules = {
        libcellml::Issue::ReferenceRule::ANALYSER_EXTERNAL_VARIABLE_VOI,
    };

    auto analyser = libcellml::Analyser::create();

    analyser->addExternalVariable(libcellml::AnalyserExternalVariable::create(model->component("membrane")->variable("time")));
    analyser->addExternalVariable(libcellml::AnalyserExternalVariable::create(model->component("sodium_channel")->variable("time")));

    analyser->analyseModel(model);

    EXPECT_EQ_ISSUES_CELLMLELEMENTTYPES_LEVELS_REFERENCERULES(expectedIssues, expectedCellmlElementTypes, expectedLevels, expectedReferenceRules, analyser);
}

TEST(Analyser, threeEquivalentVoiExternalVariablesIncludingPrimaryVariable)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("generator/hodgkin_huxley_squid_axon_model_1952/model.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    const std::vector<std::string> expectedIssues = {
        "Variable 'time' in component 'environment', variable 'time' in component 'membrane' and variable 'time' in component 'sodium_channel' are marked as external variables, but they are equivalent to variable 'time' in component 'environment', the primary variable of integration which cannot be used as an external variable.",
    };
    const std::vector<libcellml::CellmlElementType> expectedCellmlElementTypes = {
        libcellml::CellmlElementType::VARIABLE,
    };
    const std::vector<libcellml::Issue::Level> expectedLevels = {
        libcellml::Issue::Level::MESSAGE,
    };
    const std::vector<libcellml::Issue::ReferenceRule> expectedReferenceRules = {
        libcellml::Issue::ReferenceRule::ANALYSER_EXTERNAL_VARIABLE_VOI,
    };

    auto analyser = libcellml::Analyser::create();

    analyser->addExternalVariable(libcellml::AnalyserExternalVariable::create(model->component("environment")->variable("time")));
    analyser->addExternalVariable(libcellml::AnalyserExternalVariable::create(model->component("membrane")->variable("time")));
    analyser->addExternalVariable(libcellml::AnalyserExternalVariable::create(model->component("sodium_channel")->variable("time")));

    analyser->analyseModel(model);

    EXPECT_EQ_ISSUES_CELLMLELEMENTTYPES_LEVELS_REFERENCERULES(expectedIssues, expectedCellmlElementTypes, expectedLevels, expectedReferenceRules, analyser);
}

TEST(Analyser, threeEquivalentVoiExternalVariablesNotIncludingPrimaryVariable)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("generator/hodgkin_huxley_squid_axon_model_1952/model.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    const std::vector<std::string> expectedIssues = {
        "Variable 'time' in component 'membrane', variable 'time' in component 'sodium_channel' and variable 'time' in component 'potassium_channel' are marked as external variables, but they are equivalent to variable 'time' in component 'environment', the primary variable of integration which cannot be used as an external variable.",
    };
    const std::vector<libcellml::CellmlElementType> expectedCellmlElementTypes = {
        libcellml::CellmlElementType::VARIABLE,
    };
    const std::vector<libcellml::Issue::Level> expectedLevels = {
        libcellml::Issue::Level::MESSAGE,
    };
    const std::vector<libcellml::Issue::ReferenceRule> expectedReferenceRules = {
        libcellml::Issue::ReferenceRule::ANALYSER_EXTERNAL_VARIABLE_VOI,
    };

    auto analyser = libcellml::Analyser::create();

    analyser->addExternalVariable(libcellml::AnalyserExternalVariable::create(model->component("membrane")->variable("time")));
    analyser->addExternalVariable(libcellml::AnalyserExternalVariable::create(model->component("sodium_channel")->variable("time")));
    analyser->addExternalVariable(libcellml::AnalyserExternalVariable::create(model->component("potassium_channel")->variable("time")));

    analyser->analyseModel(model);

    EXPECT_EQ_ISSUES_CELLMLELEMENTTYPES_LEVELS_REFERENCERULES(expectedIssues, expectedCellmlElementTypes, expectedLevels, expectedReferenceRules, analyser);
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
    const std::vector<libcellml::CellmlElementType> expectedCellmlElementTypes = {
        libcellml::CellmlElementType::VARIABLE,
    };
    const std::vector<libcellml::Issue::Level> expectedLevels = {
        libcellml::Issue::Level::MESSAGE,
    };
    const std::vector<libcellml::Issue::ReferenceRule> expectedReferenceRules = {
        libcellml::Issue::ReferenceRule::ANALYSER_EXTERNAL_VARIABLE_USE_PRIMARY_VARIABLE,
    };

    auto analyser = libcellml::Analyser::create();

    analyser->addExternalVariable(libcellml::AnalyserExternalVariable::create(model->component("sodium_channel")->variable("V")));

    analyser->analyseModel(model);

    EXPECT_EQ_ISSUES_CELLMLELEMENTTYPES_LEVELS_REFERENCERULES(expectedIssues, expectedCellmlElementTypes, expectedLevels, expectedReferenceRules, analyser);
}

TEST(Analyser, twoEquivalentExternalVariablesIncludingPrimaryVariable)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("generator/hodgkin_huxley_squid_axon_model_1952/model.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    const std::vector<std::string> expectedIssues = {
        "Both variable 'V' in component 'membrane' and variable 'V' in component 'sodium_channel' are marked as external variables, but they are equivalent. Variable 'V' in component 'membrane' is the primary variable and will therefore be the one used as an external variable.",
    };
    const std::vector<libcellml::CellmlElementType> expectedCellmlElementTypes = {
        libcellml::CellmlElementType::VARIABLE,
    };
    const std::vector<libcellml::Issue::Level> expectedLevels = {
        libcellml::Issue::Level::MESSAGE,
    };
    const std::vector<libcellml::Issue::ReferenceRule> expectedReferenceRules = {
        libcellml::Issue::ReferenceRule::ANALYSER_EXTERNAL_VARIABLE_USE_PRIMARY_VARIABLE,
    };

    auto analyser = libcellml::Analyser::create();

    analyser->addExternalVariable(libcellml::AnalyserExternalVariable::create(model->component("membrane")->variable("V")));
    analyser->addExternalVariable(libcellml::AnalyserExternalVariable::create(model->component("sodium_channel")->variable("V")));

    analyser->analyseModel(model);

    EXPECT_EQ_ISSUES_CELLMLELEMENTTYPES_LEVELS_REFERENCERULES(expectedIssues, expectedCellmlElementTypes, expectedLevels, expectedReferenceRules, analyser);
}

TEST(Analyser, twoEquivalentExternalVariablesNotIncludingPrimaryVariable)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("generator/hodgkin_huxley_squid_axon_model_1952/model.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    const std::vector<std::string> expectedIssues = {
        "Both variable 'V' in component 'sodium_channel' and variable 'V' in component 'potassium_channel' are marked as external variables, but they are equivalent. Variable 'V' in component 'membrane' is their corresponding primary variable and will therefore be the one used as an external variable.",
    };
    const std::vector<libcellml::CellmlElementType> expectedCellmlElementTypes = {
        libcellml::CellmlElementType::VARIABLE,
    };
    const std::vector<libcellml::Issue::Level> expectedLevels = {
        libcellml::Issue::Level::MESSAGE,
    };
    const std::vector<libcellml::Issue::ReferenceRule> expectedReferenceRules = {
        libcellml::Issue::ReferenceRule::ANALYSER_EXTERNAL_VARIABLE_USE_PRIMARY_VARIABLE,
    };

    auto analyser = libcellml::Analyser::create();

    analyser->addExternalVariable(libcellml::AnalyserExternalVariable::create(model->component("sodium_channel")->variable("V")));
    analyser->addExternalVariable(libcellml::AnalyserExternalVariable::create(model->component("potassium_channel")->variable("V")));

    analyser->analyseModel(model);

    EXPECT_EQ_ISSUES_CELLMLELEMENTTYPES_LEVELS_REFERENCERULES(expectedIssues, expectedCellmlElementTypes, expectedLevels, expectedReferenceRules, analyser);
}

TEST(Analyser, threeEquivalentExternalVariablesIncludingPrimaryVariable)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("generator/hodgkin_huxley_squid_axon_model_1952/model.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    const std::vector<std::string> expectedIssues = {
        "Variable 'V' in component 'membrane', variable 'V' in component 'sodium_channel' and variable 'V' in component 'potassium_channel' are marked as external variables, but they are all equivalent. Variable 'V' in component 'membrane' is the primary variable and will therefore be the one used as an external variable.",
    };
    const std::vector<libcellml::CellmlElementType> expectedCellmlElementTypes = {
        libcellml::CellmlElementType::VARIABLE,
    };
    const std::vector<libcellml::Issue::Level> expectedLevels = {
        libcellml::Issue::Level::MESSAGE,
    };
    const std::vector<libcellml::Issue::ReferenceRule> expectedReferenceRules = {
        libcellml::Issue::ReferenceRule::ANALYSER_EXTERNAL_VARIABLE_USE_PRIMARY_VARIABLE,
    };

    auto analyser = libcellml::Analyser::create();

    analyser->addExternalVariable(libcellml::AnalyserExternalVariable::create(model->component("membrane")->variable("V")));
    analyser->addExternalVariable(libcellml::AnalyserExternalVariable::create(model->component("sodium_channel")->variable("V")));
    analyser->addExternalVariable(libcellml::AnalyserExternalVariable::create(model->component("potassium_channel")->variable("V")));

    analyser->analyseModel(model);

    EXPECT_EQ_ISSUES_CELLMLELEMENTTYPES_LEVELS_REFERENCERULES(expectedIssues, expectedCellmlElementTypes, expectedLevels, expectedReferenceRules, analyser);
}

TEST(Analyser, threeEquivalentExternalVariablesNotIncludingPrimaryVariable)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("generator/hodgkin_huxley_squid_axon_model_1952/model.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    const std::vector<std::string> expectedIssues = {
        "Variable 'V' in component 'sodium_channel', variable 'V' in component 'potassium_channel' and variable 'V' in component 'leakage_current' are marked as external variables, but they are all equivalent. Variable 'V' in component 'membrane' is their corresponding primary variable and will therefore be the one used as an external variable.",
    };
    const std::vector<libcellml::CellmlElementType> expectedCellmlElementTypes = {
        libcellml::CellmlElementType::VARIABLE,
    };
    const std::vector<libcellml::Issue::Level> expectedLevels = {
        libcellml::Issue::Level::MESSAGE,
    };
    const std::vector<libcellml::Issue::ReferenceRule> expectedReferenceRules = {
        libcellml::Issue::ReferenceRule::ANALYSER_EXTERNAL_VARIABLE_USE_PRIMARY_VARIABLE,
    };

    auto analyser = libcellml::Analyser::create();

    analyser->addExternalVariable(libcellml::AnalyserExternalVariable::create(model->component("sodium_channel")->variable("V")));
    analyser->addExternalVariable(libcellml::AnalyserExternalVariable::create(model->component("potassium_channel")->variable("V")));
    analyser->addExternalVariable(libcellml::AnalyserExternalVariable::create(model->component("leakage_current")->variable("V")));

    analyser->analyseModel(model);

    EXPECT_EQ_ISSUES_CELLMLELEMENTTYPES_LEVELS_REFERENCERULES(expectedIssues, expectedCellmlElementTypes, expectedLevels, expectedReferenceRules, analyser);
}

TEST(Analyser, unitsInMathmlStrings)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("analyser/units_in_mathml_strings.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    const std::vector<std::string> expectedIssues = {
        "The units in the expression 'i = a+b' in component 'direct_comparison_operators' are not equivalent. The unit mismatch is ampere^-3, kilogram^2, metre^3, second^-6.",
        "The units in the expression 'a+pow(b, 2.0)' in component 'direct_comparison_operators' are not equivalent. The unit mismatch is metre^-1, second^1.",
        "The argument in the expression 'tan(a)' in component 'trigonometric_operators' is not dimensionless. The units in the argument are: second^1.",
        "The units in the expression 'log(a)/log(2.0)' in component '' are not consistent with the base. The mismatch is: second^1.",
        "The units in the expression 'log(a)/log(3.0)' in component '' are not consistent with the base. The mismatch is: second^1.",
        "The units in the expression 'l = pow(a, 2.0)' in component 'power_root_operators' are not equivalent. The unit mismatch is ampere^6, kilogram^-4, metre^-8, second^14.",
    };
    const std::vector<libcellml::CellmlElementType> expectedCellmlElementTypes = {
        libcellml::CellmlElementType::UNDEFINED,
        libcellml::CellmlElementType::UNDEFINED,
        libcellml::CellmlElementType::UNDEFINED,
        libcellml::CellmlElementType::UNDEFINED,
        libcellml::CellmlElementType::UNDEFINED,
        libcellml::CellmlElementType::UNDEFINED,
    };
    const std::vector<libcellml::Issue::Level> expectedLevels = {
        libcellml::Issue::Level::MESSAGE,
        libcellml::Issue::Level::MESSAGE,
        libcellml::Issue::Level::MESSAGE,
        libcellml::Issue::Level::MESSAGE,
        libcellml::Issue::Level::MESSAGE,
        libcellml::Issue::Level::MESSAGE,
    };
    const std::vector<libcellml::Issue::ReferenceRule> expectedReferenceRules = {
        libcellml::Issue::ReferenceRule::ANALYSER_UNITS,
        libcellml::Issue::ReferenceRule::ANALYSER_UNITS,
        libcellml::Issue::ReferenceRule::ANALYSER_UNITS,
        libcellml::Issue::ReferenceRule::ANALYSER_UNITS,
        libcellml::Issue::ReferenceRule::ANALYSER_UNITS,
        libcellml::Issue::ReferenceRule::ANALYSER_UNITS,
    };

    auto analyser = libcellml::Analyser::create();

    analyser->analyseModel(model);

    EXPECT_EQ_ISSUES_CELLMLELEMENTTYPES_LEVELS_REFERENCERULES(expectedIssues, expectedCellmlElementTypes, expectedLevels, expectedReferenceRules, analyser);
}

TEST(Analyser, unitsMultiplierInMathmlStrings)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("analyser/units_multiplier_in_mathml_strings.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    const std::vector<std::string> expectedIssues = {
        "The expression 'k = pow(sqrt(c), 4.0)/100.0' in component 'simple_checks' has a multiplier mismatch. The mismatch is: -3.000000. A variable in the expression is k.",
        "The expression 'k = log10(1000.0)*pow(b, 2.0)/(b*3.0)*1000.0' in component 'complex_checks' has a multiplier mismatch. The mismatch is: 3.000000. A variable in the expression is k.",
        "The expression 'n = pow(10000.0*a, 2.0)/a' in component 'complex_checks' has a multiplier mismatch. The mismatch is: 3.000000. A variable in the expression is n.",
        "The units in the expression 'o = pow(a, 1.0/3.0)' in component 'complex_checks' are not equivalent. The unit mismatch is ampere^-0.666667, kilogram^0.666667, metre^1.333333, second^-2.",
        "The expression 'o = pow(a, 1.0/3.0)' in component 'complex_checks' has a multiplier mismatch. The mismatch is: -3.000000. A variable in the expression is o.",
    };
    const std::vector<libcellml::CellmlElementType> expectedCellmlElementTypes = {
        libcellml::CellmlElementType::UNDEFINED,
        libcellml::CellmlElementType::UNDEFINED,
        libcellml::CellmlElementType::UNDEFINED,
        libcellml::CellmlElementType::UNDEFINED,
        libcellml::CellmlElementType::UNDEFINED,
    };
    const std::vector<libcellml::Issue::Level> expectedLevels = {
        libcellml::Issue::Level::MESSAGE,
        libcellml::Issue::Level::MESSAGE,
        libcellml::Issue::Level::MESSAGE,
        libcellml::Issue::Level::MESSAGE,
        libcellml::Issue::Level::MESSAGE,
    };
    const std::vector<libcellml::Issue::ReferenceRule> expectedReferenceRules = {
        libcellml::Issue::ReferenceRule::ANALYSER_UNITS,
        libcellml::Issue::ReferenceRule::ANALYSER_UNITS,
        libcellml::Issue::ReferenceRule::ANALYSER_UNITS,
        libcellml::Issue::ReferenceRule::ANALYSER_UNITS,
        libcellml::Issue::ReferenceRule::ANALYSER_UNITS,
    };

    auto analyser = libcellml::Analyser::create();

    analyser->analyseModel(model);

    EXPECT_EQ_ISSUES_CELLMLELEMENTTYPES_LEVELS_REFERENCERULES(expectedIssues, expectedCellmlElementTypes, expectedLevels, expectedReferenceRules, analyser);
}

TEST(Analyser, coverage)
{
    auto analyser = libcellml::Analyser::create();

    analyser->analyseModel(nullptr);

    EXPECT_EQ(size_t(0), analyser->issueCount());

    auto analyserModel = analyser->model();

    EXPECT_FALSE(analyserModel->isValid());

    EXPECT_EQ(libcellml::AnalyserModel::Type::UNKNOWN, analyserModel->type());

    EXPECT_EQ(nullptr, analyserModel->voi());

    EXPECT_FALSE(analyserModel->hasExternalVariables());

    EXPECT_EQ(size_t(0), analyserModel->stateCount());
    EXPECT_EQ(size_t(0), analyserModel->states().size());

    EXPECT_EQ(size_t(0), analyserModel->variableCount());
    EXPECT_EQ(size_t(0), analyserModel->variables().size());

    EXPECT_EQ(size_t(0), analyserModel->equationCount());
    EXPECT_EQ(size_t(0), analyserModel->equations().size());

    EXPECT_FALSE(analyserModel->needEqFunction());
    EXPECT_FALSE(analyserModel->needNeqFunction());
    EXPECT_FALSE(analyserModel->needLtFunction());
    EXPECT_FALSE(analyserModel->needLeqFunction());
    EXPECT_FALSE(analyserModel->needGtFunction());
    EXPECT_FALSE(analyserModel->needGeqFunction());
    EXPECT_FALSE(analyserModel->needAndFunction());
    EXPECT_FALSE(analyserModel->needOrFunction());
    EXPECT_FALSE(analyserModel->needXorFunction());
    EXPECT_FALSE(analyserModel->needNotFunction());
    EXPECT_FALSE(analyserModel->needMinFunction());
    EXPECT_FALSE(analyserModel->needMaxFunction());
    EXPECT_FALSE(analyserModel->needSecFunction());
    EXPECT_FALSE(analyserModel->needCscFunction());
    EXPECT_FALSE(analyserModel->needCotFunction());
    EXPECT_FALSE(analyserModel->needSechFunction());
    EXPECT_FALSE(analyserModel->needCschFunction());
    EXPECT_FALSE(analyserModel->needCothFunction());
    EXPECT_FALSE(analyserModel->needAsecFunction());
    EXPECT_FALSE(analyserModel->needAcscFunction());
    EXPECT_FALSE(analyserModel->needAcotFunction());
    EXPECT_FALSE(analyserModel->needAsechFunction());
    EXPECT_FALSE(analyserModel->needAcschFunction());
    EXPECT_FALSE(analyserModel->needAcothFunction());

    auto ast = libcellml::AnalyserEquationAst::create();

    EXPECT_NE(nullptr, ast);

    ast->setType(libcellml::AnalyserEquationAst::Type::ASSIGNMENT);
    ast->setValue({});
    ast->setVariable(libcellml::Variable::create());
    ast->setParent(libcellml::AnalyserEquationAst::create());
}

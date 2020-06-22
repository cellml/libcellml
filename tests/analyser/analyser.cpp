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

TEST(Analyser, emptyModel)
{
    libcellml::ModelPtr model = libcellml::Model::create("empty_model");
    libcellml::AnalyserPtr analyser = libcellml::Analyser::create();

    analyser->processModel(model);

    EXPECT_EQ(size_t(0), analyser->issueCount());
}

TEST(Analyser, initialisedVariableOfIntegration)
{
    libcellml::ParserPtr parser = libcellml::Parser::create();
    libcellml::ModelPtr model = parser->parseModel(fileContents("analyser/initialised_variable_of_integration.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    const std::vector<std::string> expectedIssues = {
        "Variable 'time' in component 'my_component' of model 'initialised_variable_of_integration' cannot be both a variable of integration and initialised.",
    };
    const std::vector<libcellml::Issue::Cause> expectedCauses = {
        libcellml::Issue::Cause::ANALYSER,
    };

    libcellml::AnalyserPtr analyser = libcellml::Analyser::create();

    analyser->processModel(model);

    EXPECT_EQ_ISSUES_CAUSES(expectedIssues, expectedCauses, analyser);

    EXPECT_EQ(libcellml::Analyser::ModelType::INVALID, analyser->modelType());

    EXPECT_EQ(size_t(0), analyser->stateCount());
    EXPECT_EQ(size_t(0), analyser->variableCount());

    EXPECT_EQ(nullptr, analyser->voi());
    EXPECT_EQ(nullptr, analyser->state(0));
    EXPECT_EQ(nullptr, analyser->variable(0));
}

TEST(Analyser, initialisedVariableOfIntegrationInNonFirstComponent)
{
    libcellml::ParserPtr parser = libcellml::Parser::create();
    libcellml::ModelPtr model = parser->parseModel(fileContents("analyser/initialised_variable_of_integration_in_non_first_component.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    const std::vector<std::string> expectedIssues = {
        "Variable 'time' in component 'environment' of model 'initialised_variable_of_integration_in_non_first_component' cannot be both a variable of integration and initialised.",
    };
    const std::vector<libcellml::Issue::Cause> expectedCauses = {
        libcellml::Issue::Cause::ANALYSER,
    };

    libcellml::AnalyserPtr analyser = libcellml::Analyser::create();

    analyser->processModel(model);

    EXPECT_EQ_ISSUES_CAUSES(expectedIssues, expectedCauses, analyser);

    EXPECT_EQ(libcellml::Analyser::ModelType::INVALID, analyser->modelType());

    EXPECT_EQ(size_t(0), analyser->stateCount());
    EXPECT_EQ(size_t(0), analyser->variableCount());

    EXPECT_EQ(nullptr, analyser->voi());
    EXPECT_EQ(nullptr, analyser->state(0));
    EXPECT_EQ(nullptr, analyser->variable(0));
}

TEST(Analyser, twoVariablesOfIntegration)
{
    libcellml::ParserPtr parser = libcellml::Parser::create();
    libcellml::ModelPtr model = parser->parseModel(fileContents("analyser/two_variables_of_integration.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    const std::vector<std::string> expectedIssues = {
        "Variable 'time' in component 'main' of model 'two_variables_of_integration' and variable 'other_time' in component 'sub_sub_sub' of model 'two_variables_of_integration' cannot both be the variable of integration.",
    };
    const std::vector<libcellml::Issue::Cause> expectedCauses = {
        libcellml::Issue::Cause::ANALYSER,
    };

    libcellml::AnalyserPtr analyser = libcellml::Analyser::create();

    analyser->processModel(model);

    EXPECT_EQ_ISSUES_CAUSES(expectedIssues, expectedCauses, analyser);

    EXPECT_EQ(libcellml::Analyser::ModelType::INVALID, analyser->modelType());

    EXPECT_EQ(size_t(0), analyser->stateCount());
    EXPECT_EQ(size_t(0), analyser->variableCount());

    EXPECT_EQ(nullptr, analyser->voi());
    EXPECT_EQ(nullptr, analyser->state(0));
    EXPECT_EQ(nullptr, analyser->variable(0));
}

TEST(Analyser, nonFirstOrderOdes)
{
    libcellml::ParserPtr parser = libcellml::Parser::create();
    libcellml::ModelPtr model = parser->parseModel(fileContents("analyser/non_first_order_odes.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    const std::vector<std::string> expectedIssues = {
        "The differential equation for variable 'x' in component 'main' of model 'non_first_order_odes' must be of the first order.",
        "The differential equation for variable 'y' in component 'sub' of model 'non_first_order_odes' must be of the first order.",
        "The differential equation for variable 'z' in component 'sub_sub' of model 'non_first_order_odes' must be of the first order.",
    };
    const std::vector<libcellml::Issue::Cause> expectedCauses = {
        libcellml::Issue::Cause::ANALYSER,
        libcellml::Issue::Cause::ANALYSER,
        libcellml::Issue::Cause::ANALYSER,
    };

    libcellml::AnalyserPtr analyser = libcellml::Analyser::create();

    analyser->processModel(model);

    EXPECT_EQ_ISSUES_CAUSES(expectedIssues, expectedCauses, analyser);

    EXPECT_EQ(libcellml::Analyser::ModelType::INVALID, analyser->modelType());

    EXPECT_EQ(size_t(0), analyser->stateCount());
    EXPECT_EQ(size_t(0), analyser->variableCount());

    EXPECT_EQ(nullptr, analyser->voi());
    EXPECT_EQ(nullptr, analyser->state(0));
    EXPECT_EQ(nullptr, analyser->variable(0));
}

TEST(Analyser, undefinedVariables)
{
    libcellml::ParserPtr parser = libcellml::Parser::create();
    libcellml::ModelPtr model = parser->parseModel(fileContents("analyser/undefined_variables.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    const std::vector<std::string> expectedIssues = {
        "MathML ci element has the child text 'a' which does not correspond with any variable names present in component 'my_component'.",
        "MathML ci element has the child text 'b' which does not correspond with any variable names present in component 'my_component'.",
    };
    const std::vector<libcellml::Issue::Cause> expectedCauses = {
        libcellml::Issue::Cause::MATHML,
        libcellml::Issue::Cause::MATHML,
    };

    libcellml::AnalyserPtr analyser = libcellml::Analyser::create();

    analyser->processModel(model);

    EXPECT_EQ_ISSUES_CAUSES(expectedIssues, expectedCauses, analyser);

    EXPECT_EQ(libcellml::Analyser::ModelType::INVALID, analyser->modelType());

    EXPECT_EQ(size_t(0), analyser->stateCount());
    EXPECT_EQ(size_t(0), analyser->variableCount());

    EXPECT_EQ(nullptr, analyser->voi());
    EXPECT_EQ(nullptr, analyser->state(0));
    EXPECT_EQ(nullptr, analyser->variable(0));
}

TEST(Analyser, variableInitialisedTwice)
{
    libcellml::ParserPtr parser = libcellml::Parser::create();
    libcellml::ModelPtr model = parser->parseModel(fileContents("analyser/variable_initialised_twice.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    const std::vector<std::string> expectedIssues = {
        "Variable 'x' in component 'sub' of model 'variable_initialised_twice' and variable 'x' in component 'main' of model 'variable_initialised_twice' are equivalent and cannot therefore both be initialised.",
    };
    const std::vector<libcellml::Issue::Cause> expectedCauses = {
        libcellml::Issue::Cause::ANALYSER,
    };

    libcellml::AnalyserPtr analyser = libcellml::Analyser::create();

    analyser->processModel(model);

    EXPECT_EQ_ISSUES_CAUSES(expectedIssues, expectedCauses, analyser);

    EXPECT_EQ(libcellml::Analyser::ModelType::INVALID, analyser->modelType());

    EXPECT_EQ(size_t(0), analyser->stateCount());
    EXPECT_EQ(size_t(0), analyser->variableCount());

    EXPECT_EQ(nullptr, analyser->voi());
    EXPECT_EQ(nullptr, analyser->state(0));
    EXPECT_EQ(nullptr, analyser->variable(0));
}

TEST(Analyser, nonConstantInitialisingVariable)
{
    libcellml::ParserPtr parser = libcellml::Parser::create();
    libcellml::ModelPtr model = parser->parseModel(fileContents("analyser/non_constant_initialising_variable.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    const std::vector<std::string> expectedIssues = {
        "Variable 'x' in component 'main' of model 'my_model' is initialised using variable 'k2', but it is not a constant.",
    };
    const std::vector<libcellml::Issue::Cause> expectedCauses = {
        libcellml::Issue::Cause::ANALYSER,
    };

    libcellml::AnalyserPtr analyser = libcellml::Analyser::create();

    analyser->processModel(model);

    EXPECT_EQ_ISSUES_CAUSES(expectedIssues, expectedCauses, analyser);

    EXPECT_EQ(libcellml::Analyser::ModelType::INVALID, analyser->modelType());

    EXPECT_EQ(size_t(0), analyser->stateCount());
    EXPECT_EQ(size_t(0), analyser->variableCount());

    EXPECT_EQ(nullptr, analyser->voi());
    EXPECT_EQ(nullptr, analyser->state(0));
    EXPECT_EQ(nullptr, analyser->variable(0));
}

TEST(Analyser, nonExistingInitialisingVariable)
{
    libcellml::ParserPtr parser = libcellml::Parser::create();
    libcellml::ModelPtr model = parser->parseModel(fileContents("analyser/non_existing_initialising_variable.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    const std::vector<std::string> expectedIssues = {
        "Variable 'x' has an invalid initial value 'k'. Initial values must be a real number string or a variable reference.",
    };
    const std::vector<libcellml::Issue::Cause> expectedCauses = {
        libcellml::Issue::Cause::VARIABLE,
    };

    libcellml::AnalyserPtr analyser = libcellml::Analyser::create();

    analyser->processModel(model);

    EXPECT_EQ_ISSUES_CAUSES(expectedIssues, expectedCauses, analyser);

    EXPECT_EQ(libcellml::Analyser::ModelType::INVALID, analyser->modelType());

    EXPECT_EQ(size_t(0), analyser->stateCount());
    EXPECT_EQ(size_t(0), analyser->variableCount());

    EXPECT_EQ(nullptr, analyser->voi());
    EXPECT_EQ(nullptr, analyser->state(0));
    EXPECT_EQ(nullptr, analyser->variable(0));
}

TEST(Analyser, nonInitialisedState)
{
    libcellml::ParserPtr parser = libcellml::Parser::create();
    libcellml::ModelPtr model = parser->parseModel(fileContents("analyser/non_initialised_state.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    const std::vector<std::string> expectedIssues = {
        "Variable 'x' in component 'my_component' of model 'non_initialised_state' is used in an ODE, but it is not initialised.",
    };
    const std::vector<libcellml::Issue::Cause> expectedCauses = {
        libcellml::Issue::Cause::ANALYSER,
    };

    libcellml::AnalyserPtr analyser = libcellml::Analyser::create();

    analyser->processModel(model);

    EXPECT_EQ_ISSUES_CAUSES(expectedIssues, expectedCauses, analyser);

    EXPECT_EQ(libcellml::Analyser::ModelType::UNDERCONSTRAINED, analyser->modelType());

    EXPECT_EQ(size_t(0), analyser->stateCount());
    EXPECT_EQ(size_t(0), analyser->variableCount());

    EXPECT_EQ(nullptr, analyser->voi());
    EXPECT_EQ(nullptr, analyser->state(0));
    EXPECT_EQ(nullptr, analyser->variable(0));
}

TEST(Analyser, underconstrained)
{
    libcellml::ParserPtr parser = libcellml::Parser::create();
    libcellml::ModelPtr model = parser->parseModel(fileContents("analyser/underconstrained.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    const std::vector<std::string> expectedIssues = {
        "Variable 'x' in component 'my_component' of model 'my_model' is not computed.",
    };
    const std::vector<libcellml::Issue::Cause> expectedCauses = {
        libcellml::Issue::Cause::ANALYSER,
    };

    libcellml::AnalyserPtr analyser = libcellml::Analyser::create();

    analyser->processModel(model);

    EXPECT_EQ_ISSUES_CAUSES(expectedIssues, expectedCauses, analyser);

    EXPECT_EQ(libcellml::Analyser::ModelType::UNDERCONSTRAINED, analyser->modelType());

    EXPECT_EQ(size_t(0), analyser->stateCount());
    EXPECT_EQ(size_t(0), analyser->variableCount());

    EXPECT_EQ(nullptr, analyser->voi());
    EXPECT_EQ(nullptr, analyser->state(0));
    EXPECT_EQ(nullptr, analyser->variable(0));
}

TEST(Analyser, overconstrained)
{
    libcellml::ParserPtr parser = libcellml::Parser::create();
    libcellml::ModelPtr model = parser->parseModel(fileContents("analyser/overconstrained.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    const std::vector<std::string> expectedIssues = {
        "Variable 'x' in component 'my_component' of model 'my_model' is computed more than once.",
    };
    const std::vector<libcellml::Issue::Cause> expectedCauses = {
        libcellml::Issue::Cause::ANALYSER,
    };

    libcellml::AnalyserPtr analyser = libcellml::Analyser::create();

    analyser->processModel(model);

    EXPECT_EQ_ISSUES_CAUSES(expectedIssues, expectedCauses, analyser);

    EXPECT_EQ(libcellml::Analyser::ModelType::OVERCONSTRAINED, analyser->modelType());

    EXPECT_EQ(size_t(0), analyser->stateCount());
    EXPECT_EQ(size_t(0), analyser->variableCount());

    EXPECT_EQ(nullptr, analyser->voi());
    EXPECT_EQ(nullptr, analyser->state(0));
    EXPECT_EQ(nullptr, analyser->variable(0));
}

TEST(Analyser, unsuitablyConstrained)
{
    libcellml::ParserPtr parser = libcellml::Parser::create();
    libcellml::ModelPtr model = parser->parseModel(fileContents("analyser/unsuitably_constrained.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    const std::vector<std::string> expectedIssues = {
        "Variable 'x' in component 'my_component' of model 'my_model' is not computed.",
        "Variable 'y' in component 'my_component' of model 'my_model' is computed more than once.",
    };
    const std::vector<libcellml::Issue::Cause> expectedCauses = {
        libcellml::Issue::Cause::ANALYSER,
        libcellml::Issue::Cause::ANALYSER,
    };

    libcellml::AnalyserPtr analyser = libcellml::Analyser::create();

    analyser->processModel(model);

    EXPECT_EQ_ISSUES_CAUSES(expectedIssues, expectedCauses, analyser);

    EXPECT_EQ(libcellml::Analyser::ModelType::UNSUITABLY_CONSTRAINED, analyser->modelType());

    EXPECT_EQ(size_t(0), analyser->stateCount());
    EXPECT_EQ(size_t(0), analyser->variableCount());

    EXPECT_EQ(nullptr, analyser->voi());
    EXPECT_EQ(nullptr, analyser->state(0));
    EXPECT_EQ(nullptr, analyser->variable(0));
}

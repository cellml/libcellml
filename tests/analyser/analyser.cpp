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

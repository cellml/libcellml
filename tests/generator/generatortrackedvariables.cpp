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

TEST(GeneratorTrackedVariables, noModelAndOrVariable)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("generator/hodgkin_huxley_squid_axon_model_1952/model.cellml"));
    auto analyser = libcellml::Analyser::create();

    analyser->analyseModel(model);

    auto analyserModel = analyser->model();
    auto generator = libcellml::Generator::create();

    EXPECT_EQ(size_t(0), generator->trackedVariableCount(nullptr));
    EXPECT_EQ(size_t(0), generator->untrackedVariableCount(nullptr));

    EXPECT_FALSE(generator->trackVariable(nullptr, nullptr));
    EXPECT_FALSE(generator->untrackVariable(nullptr, nullptr));

    EXPECT_FALSE(generator->trackVariable(analyserModel, nullptr));
    EXPECT_FALSE(generator->untrackVariable(analyserModel, nullptr));

    EXPECT_FALSE(generator->trackAllVariables(nullptr));
    EXPECT_FALSE(generator->untrackAllVariables(nullptr));
}

TEST(GeneratorTrackedVariables, trackUntrackAllVariables)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("generator/hodgkin_huxley_squid_axon_model_1952/model.cellml"));
    auto analyser = libcellml::Analyser::create();

    analyser->analyseModel(model);

    auto analyserModel = analyser->model();
    auto generator = libcellml::Generator::create();

    EXPECT_EQ(size_t(18), generator->trackedVariableCount(analyserModel));
    EXPECT_EQ(size_t(0), generator->untrackedVariableCount(analyserModel));

    generator->untrackAllVariables(analyserModel);

    EXPECT_EQ(size_t(0), generator->trackedVariableCount(analyserModel));
    EXPECT_EQ(size_t(18), generator->untrackedVariableCount(analyserModel));

    generator->trackAllVariables(analyserModel);

    EXPECT_EQ(size_t(18), generator->trackedVariableCount(analyserModel));
    EXPECT_EQ(size_t(0), generator->untrackedVariableCount(analyserModel));
}

TEST(GeneratorTrackedVariables, trackUntrackVariableOfIntegration)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("generator/hodgkin_huxley_squid_axon_model_1952/model.cellml"));
    auto analyser = libcellml::Analyser::create();

    analyser->analyseModel(model);

    auto analyserModel = analyser->model();
    auto generator = libcellml::Generator::create();

    auto variable = model->component("environment")->variable("time");

    EXPECT_EQ(size_t(18), generator->trackedVariableCount(analyserModel));
    EXPECT_EQ(size_t(0), generator->untrackedVariableCount(analyserModel));

    EXPECT_FALSE(generator->untrackVariable(analyserModel, variable));

    EXPECT_EQ(size_t(18), generator->trackedVariableCount(analyserModel));
    EXPECT_EQ(size_t(0), generator->untrackedVariableCount(analyserModel));

    EXPECT_FALSE(generator->trackVariable(analyserModel, variable));

    EXPECT_EQ(size_t(18), generator->trackedVariableCount(analyserModel));
    EXPECT_EQ(size_t(0), generator->untrackedVariableCount(analyserModel));
}

TEST(GeneratorTrackedVariables, trackUntrackStateVariable)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("generator/hodgkin_huxley_squid_axon_model_1952/model.cellml"));
    auto analyser = libcellml::Analyser::create();

    analyser->analyseModel(model);

    auto analyserModel = analyser->model();
    auto generator = libcellml::Generator::create();

    auto variable = model->component("membrane")->variable("V");

    EXPECT_EQ(size_t(18), generator->trackedVariableCount(analyserModel));
    EXPECT_EQ(size_t(0), generator->untrackedVariableCount(analyserModel));

    EXPECT_FALSE(generator->untrackVariable(analyserModel, variable));

    EXPECT_EQ(size_t(18), generator->trackedVariableCount(analyserModel));
    EXPECT_EQ(size_t(0), generator->untrackedVariableCount(analyserModel));

    EXPECT_FALSE(generator->trackVariable(analyserModel, variable));

    EXPECT_EQ(size_t(18), generator->trackedVariableCount(analyserModel));
    EXPECT_EQ(size_t(0), generator->untrackedVariableCount(analyserModel));
}

TEST(GeneratorTrackedVariables, trackUntrackConstant)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("generator/hodgkin_huxley_squid_axon_model_1952/model.cellml"));
    auto analyser = libcellml::Analyser::create();

    analyser->analyseModel(model);

    auto analyserModel = analyser->model();
    auto generator = libcellml::Generator::create();

    auto variable = model->component("membrane")->variable("Cm");

    EXPECT_EQ(size_t(18), generator->trackedVariableCount(analyserModel));
    EXPECT_EQ(size_t(0), generator->untrackedVariableCount(analyserModel));

    EXPECT_TRUE(generator->untrackVariable(analyserModel, variable));

    EXPECT_EQ(size_t(17), generator->trackedVariableCount(analyserModel));
    EXPECT_EQ(size_t(1), generator->untrackedVariableCount(analyserModel));

    EXPECT_TRUE(generator->trackVariable(analyserModel, variable));

    EXPECT_EQ(size_t(18), generator->trackedVariableCount(analyserModel));
    EXPECT_EQ(size_t(0), generator->untrackedVariableCount(analyserModel));
}

TEST(GeneratorTrackedVariables, trackUntrackComputedConstant)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("generator/hodgkin_huxley_squid_axon_model_1952/model.cellml"));
    auto analyser = libcellml::Analyser::create();

    analyser->analyseModel(model);

    auto analyserModel = analyser->model();
    auto generator = libcellml::Generator::create();

    auto variable = model->component("leakage_current")->variable("E_L");

    EXPECT_EQ(size_t(18), generator->trackedVariableCount(analyserModel));
    EXPECT_EQ(size_t(0), generator->untrackedVariableCount(analyserModel));

    EXPECT_TRUE(generator->untrackVariable(analyserModel, variable));

    EXPECT_EQ(size_t(17), generator->trackedVariableCount(analyserModel));
    EXPECT_EQ(size_t(1), generator->untrackedVariableCount(analyserModel));

    EXPECT_TRUE(generator->trackVariable(analyserModel, variable));

    EXPECT_EQ(size_t(18), generator->trackedVariableCount(analyserModel));
    EXPECT_EQ(size_t(0), generator->untrackedVariableCount(analyserModel));
}

TEST(GeneratorTrackedVariables, trackUntrackAlgebraicVariable)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("generator/hodgkin_huxley_squid_axon_model_1952/model.cellml"));
    auto analyser = libcellml::Analyser::create();

    analyser->analyseModel(model);

    auto analyserModel = analyser->model();
    auto generator = libcellml::Generator::create();

    auto variable = model->component("membrane")->variable("i_Stim");

    EXPECT_EQ(size_t(18), generator->trackedVariableCount(analyserModel));
    EXPECT_EQ(size_t(0), generator->untrackedVariableCount(analyserModel));

    EXPECT_TRUE(generator->untrackVariable(analyserModel, variable));

    EXPECT_EQ(size_t(17), generator->trackedVariableCount(analyserModel));
    EXPECT_EQ(size_t(1), generator->untrackedVariableCount(analyserModel));

    EXPECT_TRUE(generator->trackVariable(analyserModel, variable));

    EXPECT_EQ(size_t(18), generator->trackedVariableCount(analyserModel));
    EXPECT_EQ(size_t(0), generator->untrackedVariableCount(analyserModel));
}

TEST(GeneratorTrackedVariables, trackUntrackNonMatchingModelAndVariable)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("generator/hodgkin_huxley_squid_axon_model_1952/model.cellml"));
    auto otherModel = parser->parseModel(fileContents("generator/noble_model_1962/model.cellml"));
    auto analyser = libcellml::Analyser::create();

    analyser->analyseModel(model);

    auto analyserModel = analyser->model();
    auto generator = libcellml::Generator::create();

    auto otherVariable = otherModel->component("membrane")->variable("Cm");

    EXPECT_FALSE(generator->untrackVariable(analyserModel, otherVariable));
    EXPECT_FALSE(generator->trackVariable(analyserModel, otherVariable));
}

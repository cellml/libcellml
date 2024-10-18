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

TEST(GeneratorTrackedVariables, noModelOrVariable)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("generator/hodgkin_huxley_squid_axon_model_1952/model.cellml"));
    auto analyser = libcellml::Analyser::create();

    analyser->analyseModel(model);

    auto analyserModel = analyser->model();
    auto generator = libcellml::Generator::create();

    EXPECT_EQ(size_t(0), generator->trackedVariableCount(nullptr));
    EXPECT_EQ(size_t(0), generator->untrackedVariableCount(nullptr));

    EXPECT_FALSE(generator->trackVariable(nullptr));
    EXPECT_FALSE(generator->untrackVariable(nullptr));

    EXPECT_FALSE(generator->trackAllVariables(nullptr));
    EXPECT_FALSE(generator->untrackAllVariables(nullptr));
}

TEST(GeneratorTrackedVariables, tracAndkUntrackVariableOfIntegration)
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

    EXPECT_FALSE(generator->untrackVariable(analyserModel->variable(variable)));

    EXPECT_EQ(size_t(18), generator->trackedVariableCount(analyserModel));
    EXPECT_EQ(size_t(0), generator->untrackedVariableCount(analyserModel));

    EXPECT_FALSE(generator->trackVariable(analyserModel->variable(variable)));

    EXPECT_EQ(size_t(18), generator->trackedVariableCount(analyserModel));
    EXPECT_EQ(size_t(0), generator->untrackedVariableCount(analyserModel));
}

TEST(GeneratorTrackedVariables, trackAndUntrackStateVariable)
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

    EXPECT_FALSE(generator->untrackVariable(analyserModel->variable(variable)));

    EXPECT_EQ(size_t(18), generator->trackedVariableCount(analyserModel));
    EXPECT_EQ(size_t(0), generator->untrackedVariableCount(analyserModel));

    EXPECT_FALSE(generator->trackVariable(analyserModel->variable(variable)));

    EXPECT_EQ(size_t(18), generator->trackedVariableCount(analyserModel));
    EXPECT_EQ(size_t(0), generator->untrackedVariableCount(analyserModel));
}

TEST(GeneratorTrackedVariables, trackAndUntrackConstant)
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

    EXPECT_TRUE(generator->untrackVariable(analyserModel->variable(variable)));

    EXPECT_EQ(size_t(17), generator->trackedVariableCount(analyserModel));
    EXPECT_EQ(size_t(1), generator->untrackedVariableCount(analyserModel));

    EXPECT_TRUE(generator->trackVariable(analyserModel->variable(variable)));

    EXPECT_EQ(size_t(18), generator->trackedVariableCount(analyserModel));
    EXPECT_EQ(size_t(0), generator->untrackedVariableCount(analyserModel));
}

TEST(GeneratorTrackedVariables, trackAndUntrackComputedConstant)
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

    EXPECT_TRUE(generator->untrackVariable(analyserModel->variable(variable)));

    EXPECT_EQ(size_t(17), generator->trackedVariableCount(analyserModel));
    EXPECT_EQ(size_t(1), generator->untrackedVariableCount(analyserModel));

    EXPECT_TRUE(generator->trackVariable(analyserModel->variable(variable)));

    EXPECT_EQ(size_t(18), generator->trackedVariableCount(analyserModel));
    EXPECT_EQ(size_t(0), generator->untrackedVariableCount(analyserModel));
}

TEST(GeneratorTrackedVariables, trackAndUntrackAlgebraicVariable)
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

    EXPECT_TRUE(generator->untrackVariable(analyserModel->variable(variable)));

    EXPECT_EQ(size_t(17), generator->trackedVariableCount(analyserModel));
    EXPECT_EQ(size_t(1), generator->untrackedVariableCount(analyserModel));

    EXPECT_TRUE(generator->trackVariable(analyserModel->variable(variable)));

    EXPECT_EQ(size_t(18), generator->trackedVariableCount(analyserModel));
    EXPECT_EQ(size_t(0), generator->untrackedVariableCount(analyserModel));
}

TEST(GeneratorTrackedVariables, trackAndUntrackExternalVariable)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("generator/hodgkin_huxley_squid_axon_model_1952/model.cellml"));
    auto analyser = libcellml::Analyser::create();

    analyser->addExternalVariable(libcellml::AnalyserExternalVariable::create(model->component("membrane")->variable("V")));

    analyser->analyseModel(model);

    auto analyserModel = analyser->model();
    auto generator = libcellml::Generator::create();

    auto variable = model->component("membrane")->variable("V");

    EXPECT_EQ(size_t(19), generator->trackedVariableCount(analyserModel));
    EXPECT_EQ(size_t(0), generator->untrackedVariableCount(analyserModel));

    EXPECT_TRUE(generator->untrackVariable(analyserModel->variable(variable)));

    EXPECT_EQ(size_t(18), generator->trackedVariableCount(analyserModel));
    EXPECT_EQ(size_t(1), generator->untrackedVariableCount(analyserModel));

    EXPECT_TRUE(generator->trackVariable(analyserModel->variable(variable)));

    EXPECT_EQ(size_t(19), generator->trackedVariableCount(analyserModel));
    EXPECT_EQ(size_t(0), generator->untrackedVariableCount(analyserModel));
}

TEST(GeneratorTrackedVariables, trackAndUntrackVariableFromOtherModel)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("generator/hodgkin_huxley_squid_axon_model_1952/model.cellml"));
    auto otherModel = parser->parseModel(fileContents("generator/noble_model_1962/model.cellml"));
    auto analyser = libcellml::Analyser::create();

    analyser->analyseModel(model);

    auto analyserModel = analyser->model();
    auto generator = libcellml::Generator::create();

    auto otherVariable = otherModel->component("membrane")->variable("Cm");

    EXPECT_FALSE(generator->untrackVariable(analyserModel->variable(otherVariable)));
    EXPECT_FALSE(generator->trackVariable(analyserModel->variable(otherVariable)));
}

TEST(GeneratorTrackedVariables, trackAndUntrackAllConstants)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("generator/hodgkin_huxley_squid_axon_model_1952/model.cellml"));
    auto analyser = libcellml::Analyser::create();

    analyser->analyseModel(model);

    auto analyserModel = analyser->model();
    auto generator = libcellml::Generator::create();

    EXPECT_EQ(size_t(5), generator->trackedConstantCount(analyserModel));
    EXPECT_EQ(size_t(0), generator->untrackedConstantCount(analyserModel));
    EXPECT_EQ(size_t(18), generator->trackedVariableCount(analyserModel));
    EXPECT_EQ(size_t(0), generator->untrackedVariableCount(analyserModel));

    generator->untrackAllConstants(analyserModel);

    EXPECT_EQ(size_t(0), generator->trackedConstantCount(analyserModel));
    EXPECT_EQ(size_t(5), generator->untrackedConstantCount(analyserModel));
    EXPECT_EQ(size_t(13), generator->trackedVariableCount(analyserModel));
    EXPECT_EQ(size_t(5), generator->untrackedVariableCount(analyserModel));

    generator->trackAllConstants(analyserModel);

    EXPECT_EQ(size_t(5), generator->trackedConstantCount(analyserModel));
    EXPECT_EQ(size_t(0), generator->untrackedConstantCount(analyserModel));
    EXPECT_EQ(size_t(18), generator->trackedVariableCount(analyserModel));
    EXPECT_EQ(size_t(0), generator->untrackedVariableCount(analyserModel));
}

TEST(GeneratorTrackedVariables, trackAndUntrackAllComputedConstants)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("generator/hodgkin_huxley_squid_axon_model_1952/model.cellml"));
    auto analyser = libcellml::Analyser::create();

    analyser->analyseModel(model);

    auto analyserModel = analyser->model();
    auto generator = libcellml::Generator::create();

    EXPECT_EQ(size_t(3), generator->trackedComputedConstantCount(analyserModel));
    EXPECT_EQ(size_t(0), generator->untrackedComputedConstantCount(analyserModel));
    EXPECT_EQ(size_t(18), generator->trackedVariableCount(analyserModel));
    EXPECT_EQ(size_t(0), generator->untrackedVariableCount(analyserModel));

    generator->untrackAllComputedConstants(analyserModel);

    EXPECT_EQ(size_t(0), generator->trackedComputedConstantCount(analyserModel));
    EXPECT_EQ(size_t(3), generator->untrackedComputedConstantCount(analyserModel));
    EXPECT_EQ(size_t(15), generator->trackedVariableCount(analyserModel));
    EXPECT_EQ(size_t(3), generator->untrackedVariableCount(analyserModel));

    generator->trackAllComputedConstants(analyserModel);

    EXPECT_EQ(size_t(3), generator->trackedComputedConstantCount(analyserModel));
    EXPECT_EQ(size_t(0), generator->untrackedComputedConstantCount(analyserModel));
    EXPECT_EQ(size_t(18), generator->trackedVariableCount(analyserModel));
    EXPECT_EQ(size_t(0), generator->untrackedVariableCount(analyserModel));
}

TEST(GeneratorTrackedVariables, trackAndUntrackAllAlgebraicVariables)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("generator/hodgkin_huxley_squid_axon_model_1952/model.cellml"));
    auto analyser = libcellml::Analyser::create();

    analyser->analyseModel(model);

    auto analyserModel = analyser->model();
    auto generator = libcellml::Generator::create();

    EXPECT_EQ(size_t(10), generator->trackedAlgebraicCount(analyserModel));
    EXPECT_EQ(size_t(0), generator->untrackedAlgebraicCount(analyserModel));
    EXPECT_EQ(size_t(18), generator->trackedVariableCount(analyserModel));
    EXPECT_EQ(size_t(0), generator->untrackedVariableCount(analyserModel));

    generator->untrackAllAlgebraic(analyserModel);

    EXPECT_EQ(size_t(0), generator->trackedAlgebraicCount(analyserModel));
    EXPECT_EQ(size_t(10), generator->untrackedAlgebraicCount(analyserModel));
    EXPECT_EQ(size_t(8), generator->trackedVariableCount(analyserModel));
    EXPECT_EQ(size_t(10), generator->untrackedVariableCount(analyserModel));

    generator->trackAllAlgebraic(analyserModel);

    EXPECT_EQ(size_t(10), generator->trackedAlgebraicCount(analyserModel));
    EXPECT_EQ(size_t(0), generator->untrackedAlgebraicCount(analyserModel));
    EXPECT_EQ(size_t(18), generator->trackedVariableCount(analyserModel));
    EXPECT_EQ(size_t(0), generator->untrackedVariableCount(analyserModel));
}

TEST(GeneratorTrackedVariables, trackAndUntrackAllExternalVariables)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("generator/hodgkin_huxley_squid_axon_model_1952/model.cellml"));
    auto analyser = libcellml::Analyser::create();

    analyser->addExternalVariable(libcellml::AnalyserExternalVariable::create(model->component("sodium_channel_m_gate")->variable("m")));
    analyser->addExternalVariable(libcellml::AnalyserExternalVariable::create(model->component("sodium_channel_h_gate")->variable("h")));
    analyser->addExternalVariable(libcellml::AnalyserExternalVariable::create(model->component("potassium_channel_n_gate")->variable("n")));

    analyser->analyseModel(model);

    auto analyserModel = analyser->model();
    auto generator = libcellml::Generator::create();

    EXPECT_EQ(size_t(3), generator->trackedExternalCount(analyserModel));
    EXPECT_EQ(size_t(0), generator->untrackedExternalCount(analyserModel));
    EXPECT_EQ(size_t(21), generator->trackedVariableCount(analyserModel));
    EXPECT_EQ(size_t(0), generator->untrackedVariableCount(analyserModel));

    generator->untrackAllExternals(analyserModel);

    EXPECT_EQ(size_t(0), generator->trackedExternalCount(analyserModel));
    EXPECT_EQ(size_t(3), generator->untrackedExternalCount(analyserModel));
    EXPECT_EQ(size_t(18), generator->trackedVariableCount(analyserModel));
    EXPECT_EQ(size_t(3), generator->untrackedVariableCount(analyserModel));

    generator->trackAllExternals(analyserModel);

    EXPECT_EQ(size_t(3), generator->trackedExternalCount(analyserModel));
    EXPECT_EQ(size_t(0), generator->untrackedExternalCount(analyserModel));
    EXPECT_EQ(size_t(21), generator->trackedVariableCount(analyserModel));
    EXPECT_EQ(size_t(0), generator->untrackedVariableCount(analyserModel));
}

TEST(GeneratorTrackedVariables, trackAndUntrackAllVariables)
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

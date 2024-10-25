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

    EXPECT_FALSE(generator->isTrackedVariable(nullptr));
    EXPECT_FALSE(generator->isUntrackedVariable(nullptr));

    EXPECT_FALSE(generator->trackVariable(nullptr));
    EXPECT_FALSE(generator->untrackVariable(nullptr));

    EXPECT_FALSE(generator->trackAllConstants(nullptr));
    EXPECT_FALSE(generator->untrackAllConstants(nullptr));

    EXPECT_FALSE(generator->trackAllComputedConstants(nullptr));
    EXPECT_FALSE(generator->untrackAllComputedConstants(nullptr));

    EXPECT_FALSE(generator->trackAllAlgebraic(nullptr));
    EXPECT_FALSE(generator->untrackAllAlgebraic(nullptr));

    EXPECT_FALSE(generator->trackAllExternals(nullptr));
    EXPECT_FALSE(generator->untrackAllExternals(nullptr));

    EXPECT_FALSE(generator->trackAllVariables(nullptr));
    EXPECT_FALSE(generator->untrackAllVariables(nullptr));

    EXPECT_EQ(size_t(0), generator->trackedConstantCount(nullptr));
    EXPECT_EQ(size_t(0), generator->untrackedConstantCount(nullptr));

    EXPECT_EQ(size_t(0), generator->trackedComputedConstantCount(nullptr));
    EXPECT_EQ(size_t(0), generator->untrackedComputedConstantCount(nullptr));

    EXPECT_EQ(size_t(0), generator->trackedAlgebraicCount(nullptr));
    EXPECT_EQ(size_t(0), generator->untrackedAlgebraicCount(nullptr));

    EXPECT_EQ(size_t(0), generator->trackedExternalCount(nullptr));
    EXPECT_EQ(size_t(0), generator->untrackedExternalCount(nullptr));

    EXPECT_EQ(size_t(0), generator->trackedVariableCount(nullptr));
    EXPECT_EQ(size_t(0), generator->untrackedVariableCount(nullptr));
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

    EXPECT_TRUE(generator->isTrackedVariable(analyserModel->variable(variable)));
    EXPECT_FALSE(generator->isUntrackedVariable(analyserModel->variable(variable)));

    EXPECT_EQ(size_t(18), generator->trackedVariableCount(analyserModel));
    EXPECT_EQ(size_t(0), generator->untrackedVariableCount(analyserModel));

    EXPECT_FALSE(generator->untrackVariable(analyserModel->variable(variable)));

    EXPECT_TRUE(generator->isTrackedVariable(analyserModel->variable(variable)));
    EXPECT_FALSE(generator->isUntrackedVariable(analyserModel->variable(variable)));

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

    EXPECT_TRUE(generator->isTrackedVariable(analyserModel->variable(variable)));
    EXPECT_FALSE(generator->isUntrackedVariable(analyserModel->variable(variable)));

    EXPECT_EQ(size_t(18), generator->trackedVariableCount(analyserModel));
    EXPECT_EQ(size_t(0), generator->untrackedVariableCount(analyserModel));

    EXPECT_FALSE(generator->untrackVariable(analyserModel->variable(variable)));

    EXPECT_TRUE(generator->isTrackedVariable(analyserModel->variable(variable)));
    EXPECT_FALSE(generator->isUntrackedVariable(analyserModel->variable(variable)));

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

    EXPECT_TRUE(generator->isTrackedVariable(analyserModel->variable(variable)));
    EXPECT_FALSE(generator->isUntrackedVariable(analyserModel->variable(variable)));

    EXPECT_EQ(size_t(18), generator->trackedVariableCount(analyserModel));
    EXPECT_EQ(size_t(0), generator->untrackedVariableCount(analyserModel));

    EXPECT_TRUE(generator->untrackVariable(analyserModel->variable(variable)));

    EXPECT_FALSE(generator->isTrackedVariable(analyserModel->variable(variable)));
    EXPECT_TRUE(generator->isUntrackedVariable(analyserModel->variable(variable)));

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

    EXPECT_TRUE(generator->isTrackedVariable(analyserModel->variable(variable)));
    EXPECT_FALSE(generator->isUntrackedVariable(analyserModel->variable(variable)));

    EXPECT_EQ(size_t(18), generator->trackedVariableCount(analyserModel));
    EXPECT_EQ(size_t(0), generator->untrackedVariableCount(analyserModel));

    EXPECT_TRUE(generator->untrackVariable(analyserModel->variable(variable)));

    EXPECT_FALSE(generator->isTrackedVariable(analyserModel->variable(variable)));
    EXPECT_TRUE(generator->isUntrackedVariable(analyserModel->variable(variable)));

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

    EXPECT_TRUE(generator->isTrackedVariable(analyserModel->variable(variable)));
    EXPECT_FALSE(generator->isUntrackedVariable(analyserModel->variable(variable)));

    EXPECT_EQ(size_t(18), generator->trackedVariableCount(analyserModel));
    EXPECT_EQ(size_t(0), generator->untrackedVariableCount(analyserModel));

    EXPECT_TRUE(generator->untrackVariable(analyserModel->variable(variable)));

    EXPECT_FALSE(generator->isTrackedVariable(analyserModel->variable(variable)));
    EXPECT_TRUE(generator->isUntrackedVariable(analyserModel->variable(variable)));

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

    EXPECT_TRUE(generator->isTrackedVariable(analyserModel->variable(variable)));
    EXPECT_FALSE(generator->isUntrackedVariable(analyserModel->variable(variable)));

    EXPECT_EQ(size_t(19), generator->trackedVariableCount(analyserModel));
    EXPECT_EQ(size_t(0), generator->untrackedVariableCount(analyserModel));

    EXPECT_TRUE(generator->untrackVariable(analyserModel->variable(variable)));

    EXPECT_FALSE(generator->isTrackedVariable(analyserModel->variable(variable)));
    EXPECT_TRUE(generator->isUntrackedVariable(analyserModel->variable(variable)));

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

    EXPECT_FALSE(generator->trackVariable(analyserModel->variable(otherVariable)));
    EXPECT_FALSE(generator->untrackVariable(analyserModel->variable(otherVariable)));
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

TEST(GeneratorTrackedVariables, hodgkinHuxleySquidAxonModel1952NoTracking)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("generator/hodgkin_huxley_squid_axon_model_1952/model.cellml"));
    auto analyser = libcellml::Analyser::create();

    analyser->analyseModel(model);

    auto analyserModel = analyser->model();
    auto generator = libcellml::Generator::create();

    generator->untrackAllVariables(analyserModel);

    EXPECT_EQ_FILE_CONTENTS("generator/hodgkin_huxley_squid_axon_model_1952/model.no.tracking.h", generator->interfaceCode(analyserModel));
    EXPECT_EQ_FILE_CONTENTS("generator/hodgkin_huxley_squid_axon_model_1952/model.no.tracking.c", generator->implementationCode(analyserModel));

    auto profile = libcellml::GeneratorProfile::create(libcellml::GeneratorProfile::Profile::PYTHON);

    generator->setProfile(profile);

    EXPECT_EQ_FILE_CONTENTS("generator/hodgkin_huxley_squid_axon_model_1952/model.no.tracking.py", generator->implementationCode(analyserModel));
}

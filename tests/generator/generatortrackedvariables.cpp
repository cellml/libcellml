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

    generator->trackVariable(nullptr);
    EXPECT_EQ_ISSUES({"The variable is null."}, generator);

    generator->untrackVariable(nullptr);
    EXPECT_EQ_ISSUES({"The variable is null."}, generator);

    generator->trackAllConstants(nullptr);
    EXPECT_EQ_ISSUES({"The model is null."}, generator);

    generator->untrackAllConstants(nullptr);
    EXPECT_EQ_ISSUES({"The model is null."}, generator);

    generator->trackAllComputedConstants(nullptr);
    EXPECT_EQ_ISSUES({"The model is null."}, generator);

    generator->untrackAllComputedConstants(nullptr);
    EXPECT_EQ_ISSUES({"The model is null."}, generator);

    generator->trackAllAlgebraic(nullptr);
    EXPECT_EQ_ISSUES({"The model is null."}, generator);

    generator->untrackAllAlgebraic(nullptr);
    EXPECT_EQ_ISSUES({"The model is null."}, generator);

    generator->trackAllVariables(nullptr);
    EXPECT_EQ_ISSUES({"The model is null."}, generator);

    generator->untrackAllVariables(nullptr);
    EXPECT_EQ_ISSUES({"The model is null."}, generator);

    EXPECT_EQ(size_t(0), generator->trackedConstantCount(nullptr));
    EXPECT_EQ(size_t(0), generator->untrackedConstantCount(nullptr));

    EXPECT_EQ(size_t(0), generator->trackedComputedConstantCount(nullptr));
    EXPECT_EQ(size_t(0), generator->untrackedComputedConstantCount(nullptr));

    EXPECT_EQ(size_t(0), generator->trackedAlgebraicCount(nullptr));
    EXPECT_EQ(size_t(0), generator->untrackedAlgebraicCount(nullptr));

    EXPECT_EQ(size_t(0), generator->trackedVariableCount(nullptr));
    EXPECT_EQ(size_t(0), generator->untrackedVariableCount(nullptr));
}

TEST(GeneratorTrackedVariables, tracAndkUntrackVariableOfIntegration)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("generator/hodgkin_huxley_squid_axon_model_1952/model.cellml"));
    auto analyser = libcellml::Analyser::create();

    analyser->addExternalVariable(libcellml::AnalyserExternalVariable::create(model->component("membrane")->variable("V")));
    // Note: this external variable helps with our coverage since we check for the variable of integration last in
    //       Generator::GeneratorImpl::doTrackVariable().

    analyser->analyseModel(model);

    auto analyserModel = analyser->model();
    auto generator = libcellml::Generator::create();

    auto variable = model->component("environment")->variable("time");

    EXPECT_TRUE(generator->isTrackedVariable(analyserModel->variable(variable)));
    EXPECT_FALSE(generator->isUntrackedVariable(analyserModel->variable(variable)));

    EXPECT_EQ(size_t(18), generator->trackedVariableCount(analyserModel));
    EXPECT_EQ(size_t(0), generator->untrackedVariableCount(analyserModel));

    generator->untrackVariable(analyserModel->variable(variable));
    EXPECT_EQ_ISSUES({"Variable 'time' in component 'environment' is the variable of integration and cannot therefore be untracked."}, generator);

    EXPECT_TRUE(generator->isTrackedVariable(analyserModel->variable(variable)));
    EXPECT_FALSE(generator->isUntrackedVariable(analyserModel->variable(variable)));

    EXPECT_EQ(size_t(18), generator->trackedVariableCount(analyserModel));
    EXPECT_EQ(size_t(0), generator->untrackedVariableCount(analyserModel));

    generator->trackVariable(analyserModel->variable(variable));
    EXPECT_EQ_ISSUES({"Variable 'time' in component 'environment' is the variable of integration and is therefore always tracked."}, generator);

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

    generator->untrackVariable(analyserModel->variable(variable));
    EXPECT_EQ_ISSUES({"Variable 'V' in component 'membrane' is a state variable and cannot therefore be untracked."}, generator);

    EXPECT_TRUE(generator->isTrackedVariable(analyserModel->variable(variable)));
    EXPECT_FALSE(generator->isUntrackedVariable(analyserModel->variable(variable)));

    EXPECT_EQ(size_t(18), generator->trackedVariableCount(analyserModel));
    EXPECT_EQ(size_t(0), generator->untrackedVariableCount(analyserModel));

    generator->trackVariable(analyserModel->variable(variable));
    EXPECT_EQ_ISSUES({"Variable 'V' in component 'membrane' is a state variable and is therefore always tracked."}, generator);

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

    generator->untrackVariable(analyserModel->variable(variable));
    EXPECT_EQ_ISSUES({}, generator);

    EXPECT_FALSE(generator->isTrackedVariable(analyserModel->variable(variable)));
    EXPECT_TRUE(generator->isUntrackedVariable(analyserModel->variable(variable)));

    EXPECT_EQ(size_t(17), generator->trackedVariableCount(analyserModel));
    EXPECT_EQ(size_t(1), generator->untrackedVariableCount(analyserModel));

    generator->trackVariable(analyserModel->variable(variable));
    EXPECT_EQ_ISSUES({}, generator);

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

    generator->untrackVariable(analyserModel->variable(variable));
    EXPECT_EQ_ISSUES({}, generator);

    EXPECT_FALSE(generator->isTrackedVariable(analyserModel->variable(variable)));
    EXPECT_TRUE(generator->isUntrackedVariable(analyserModel->variable(variable)));

    EXPECT_EQ(size_t(17), generator->trackedVariableCount(analyserModel));
    EXPECT_EQ(size_t(1), generator->untrackedVariableCount(analyserModel));

    generator->trackVariable(analyserModel->variable(variable));
    EXPECT_EQ_ISSUES({}, generator);

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

    generator->untrackVariable(analyserModel->variable(variable));
    EXPECT_EQ_ISSUES({}, generator);

    EXPECT_FALSE(generator->isTrackedVariable(analyserModel->variable(variable)));
    EXPECT_TRUE(generator->isUntrackedVariable(analyserModel->variable(variable)));

    EXPECT_EQ(size_t(17), generator->trackedVariableCount(analyserModel));
    EXPECT_EQ(size_t(1), generator->untrackedVariableCount(analyserModel));

    generator->trackVariable(analyserModel->variable(variable));
    EXPECT_EQ_ISSUES({}, generator);

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

    EXPECT_EQ(size_t(18), generator->trackedVariableCount(analyserModel));
    EXPECT_EQ(size_t(0), generator->untrackedVariableCount(analyserModel));

    generator->untrackVariable(analyserModel->variable(variable));
    EXPECT_EQ_ISSUES({"Variable 'V' in component 'membrane' is an external variable and cannot therefore be untracked."}, generator);

    EXPECT_TRUE(generator->isTrackedVariable(analyserModel->variable(variable)));
    EXPECT_FALSE(generator->isUntrackedVariable(analyserModel->variable(variable)));

    EXPECT_EQ(size_t(18), generator->trackedVariableCount(analyserModel));
    EXPECT_EQ(size_t(0), generator->untrackedVariableCount(analyserModel));

    generator->trackVariable(analyserModel->variable(variable));
    EXPECT_EQ_ISSUES({"Variable 'V' in component 'membrane' is an external variable and is therefore always tracked."}, generator);

    EXPECT_EQ(size_t(18), generator->trackedVariableCount(analyserModel));
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

    generator->trackVariable(analyserModel->variable(otherVariable));
    EXPECT_EQ_ISSUES({"The variable is null."}, generator);

    generator->untrackVariable(analyserModel->variable(otherVariable));
    EXPECT_EQ_ISSUES({"The variable is null."}, generator);
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
    EXPECT_EQ_ISSUES({}, generator);

    EXPECT_EQ(size_t(0), generator->trackedConstantCount(analyserModel));
    EXPECT_EQ(size_t(5), generator->untrackedConstantCount(analyserModel));
    EXPECT_EQ(size_t(13), generator->trackedVariableCount(analyserModel));
    EXPECT_EQ(size_t(5), generator->untrackedVariableCount(analyserModel));

    generator->trackAllConstants(analyserModel);
    EXPECT_EQ_ISSUES({}, generator);

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
    EXPECT_EQ_ISSUES({}, generator);

    EXPECT_EQ(size_t(0), generator->trackedComputedConstantCount(analyserModel));
    EXPECT_EQ(size_t(3), generator->untrackedComputedConstantCount(analyserModel));
    EXPECT_EQ(size_t(15), generator->trackedVariableCount(analyserModel));
    EXPECT_EQ(size_t(3), generator->untrackedVariableCount(analyserModel));

    generator->trackAllComputedConstants(analyserModel);
    EXPECT_EQ_ISSUES({}, generator);

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
    EXPECT_EQ_ISSUES({}, generator);

    EXPECT_EQ(size_t(0), generator->trackedAlgebraicCount(analyserModel));
    EXPECT_EQ(size_t(10), generator->untrackedAlgebraicCount(analyserModel));
    EXPECT_EQ(size_t(8), generator->trackedVariableCount(analyserModel));
    EXPECT_EQ(size_t(10), generator->untrackedVariableCount(analyserModel));

    generator->trackAllAlgebraic(analyserModel);
    EXPECT_EQ_ISSUES({}, generator);

    EXPECT_EQ(size_t(10), generator->trackedAlgebraicCount(analyserModel));
    EXPECT_EQ(size_t(0), generator->untrackedAlgebraicCount(analyserModel));
    EXPECT_EQ(size_t(18), generator->trackedVariableCount(analyserModel));
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
    EXPECT_EQ_ISSUES({}, generator);

    EXPECT_EQ(size_t(0), generator->trackedVariableCount(analyserModel));
    EXPECT_EQ(size_t(18), generator->untrackedVariableCount(analyserModel));

    generator->trackAllVariables(analyserModel);
    EXPECT_EQ_ISSUES({}, generator);

    EXPECT_EQ(size_t(18), generator->trackedVariableCount(analyserModel));
    EXPECT_EQ(size_t(0), generator->untrackedVariableCount(analyserModel));
}

enum class TrackingType
{
    VARIABLES,
    CONSTANTS,
    COMPUTED_CONSTANTS,
    ALGEBRAIC
};

void untrack(const libcellml::AnalyserModelPtr &model, const libcellml::GeneratorPtr &generator, TrackingType trackingType)
{
    switch (trackingType) {
    case TrackingType::VARIABLES:
        generator->trackAllVariables(model); // For coverage.
        generator->untrackAllVariables(model);

        break;
    case TrackingType::CONSTANTS:
        generator->untrackAllConstants(model);

        break;
    case TrackingType::COMPUTED_CONSTANTS:
        generator->untrackAllComputedConstants(model);

        break;
    case TrackingType::ALGEBRAIC:
        generator->untrackAllAlgebraic(model);

        break;
    }
}

void hodgkinHuxleySquidAxonModel1952CodeGeneration(bool ode, TrackingType trackingType,
                                                   const std::vector<std::string> &issues = {},
                                                   const std::vector<std::string> &externalIssues = {})
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents(std::string("generator/hodgkin_huxley_squid_axon_model_1952/model") + (ode ? "" : ".dae.wo.cc") + ".cellml"));
    auto analyser = libcellml::Analyser::create();
    auto generator = libcellml::Generator::create();
    std::string modelType = ode ? "model" : "model.dae.wo.cc";
    std::string variableType = (trackingType == TrackingType::VARIABLES) ?
                                   "variables" :
                                   ((trackingType == TrackingType::CONSTANTS) ?
                                        "constants" :
                                        ((trackingType == TrackingType::COMPUTED_CONSTANTS) ?
                                             "computed.constants" :
                                             "algebraic.variables"));

    analyser->analyseModel(model);

    auto analyserModel = analyser->model();

    untrack(analyserModel, generator, trackingType);

    EXPECT_EQ_ISSUES(issues, generator);

    auto profile = generator->profile();

    profile->setInterfaceFileNameString(modelType + ".untracked." + variableType + ".h");

    EXPECT_EQ_FILE_CONTENTS("generator/hodgkin_huxley_squid_axon_model_1952/" + modelType + ".untracked." + variableType + ".h", generator->interfaceCode(analyserModel));
    EXPECT_EQ_FILE_CONTENTS("generator/hodgkin_huxley_squid_axon_model_1952/" + modelType + ".untracked." + variableType + ".c", generator->implementationCode(analyserModel));

    profile = libcellml::GeneratorProfile::create(libcellml::GeneratorProfile::Profile::PYTHON);

    generator->setProfile(profile);

    EXPECT_EQ_FILE_CONTENTS("generator/hodgkin_huxley_squid_axon_model_1952/" + modelType + ".untracked." + variableType + ".py", generator->implementationCode(analyserModel));

    // With an external variable with a dependency on a constant, computed constant, and algebraic variable.

    auto membrane_Cm = model->component("membrane")->variable("Cm");
    auto potassium_channel_EK = model->component("potassium_channel")->variable("E_K");
    auto sodium_channel_m_gate_alapha_m = model->component("sodium_channel_m_gate")->variable("alpha_m");
    auto external_sodium_channel_i_Na = libcellml::AnalyserExternalVariable::create(model->component("sodium_channel")->variable("i_Na"));

    external_sodium_channel_i_Na->addDependency(membrane_Cm);
    external_sodium_channel_i_Na->addDependency(potassium_channel_EK);
    external_sodium_channel_i_Na->addDependency(sodium_channel_m_gate_alapha_m);

    analyser->addExternalVariable(external_sodium_channel_i_Na);

    analyser->analyseModel(model);

    analyserModel = analyser->model();

    untrack(analyserModel, generator, trackingType);

    EXPECT_EQ_ISSUES(externalIssues, generator);

    profile = libcellml::GeneratorProfile::create(libcellml::GeneratorProfile::Profile::C);

    generator->setProfile(profile);

    profile->setInterfaceFileNameString(modelType + ".untracked." + variableType + ".with.externals.h");

    EXPECT_EQ_FILE_CONTENTS("generator/hodgkin_huxley_squid_axon_model_1952/" + modelType + ".untracked." + variableType + ".with.externals.h", generator->interfaceCode(analyserModel));
    EXPECT_EQ_FILE_CONTENTS("generator/hodgkin_huxley_squid_axon_model_1952/" + modelType + ".untracked." + variableType + ".with.externals.c", generator->implementationCode(analyserModel));

    profile = libcellml::GeneratorProfile::create(libcellml::GeneratorProfile::Profile::PYTHON);

    generator->setProfile(profile);

    EXPECT_EQ_FILE_CONTENTS("generator/hodgkin_huxley_squid_axon_model_1952/" + modelType + ".untracked." + variableType + ".with.externals.py", generator->implementationCode(analyserModel));
}

const std::vector<std::string> noIssues;
const std::vector<std::string> constantRelatedExternalIssues = {
    "Variable 'Cm' in component 'membrane' is needed to compute an external variable and cannot therefore be untracked.",
};

TEST(GeneratorTrackedVariables, hodgkinHuxleySquidAxonModel1952UntrackedConstants)
{
    hodgkinHuxleySquidAxonModel1952CodeGeneration(true, TrackingType::CONSTANTS, noIssues, constantRelatedExternalIssues);
}

const std::vector<std::string> computedConstantRelatedExternalIssues = {
    "Variable 'E_K' in component 'potassium_channel' is needed to compute an external variable and cannot therefore be untracked.",
};

TEST(GeneratorTrackedVariables, hodgkinHuxleySquidAxonModel1952UntrackedComputedConstants)
{
    hodgkinHuxleySquidAxonModel1952CodeGeneration(true, TrackingType::COMPUTED_CONSTANTS, noIssues, computedConstantRelatedExternalIssues);
}

const std::vector<std::string> algebraicRelatedExternalIssues = {
    "Variable 'alpha_m' in component 'sodium_channel_m_gate' is needed to compute an external variable and cannot therefore be untracked.",
};

TEST(GeneratorTrackedVariables, hodgkinHuxleySquidAxonModel1952UntrackedAlgebraicVariables)
{
    hodgkinHuxleySquidAxonModel1952CodeGeneration(true, TrackingType::ALGEBRAIC, noIssues, algebraicRelatedExternalIssues);
}

TEST(GeneratorTrackedVariables, hodgkinHuxleySquidAxonModel1952UntrackedVariables)
{
    const std::vector<std::string> variableRelatedExternalIssues = {
        "Variable 'Cm' in component 'membrane' is needed to compute an external variable and cannot therefore be untracked.",
        "Variable 'E_K' in component 'potassium_channel' is needed to compute an external variable and cannot therefore be untracked.",
        "Variable 'alpha_m' in component 'sodium_channel_m_gate' is needed to compute an external variable and cannot therefore be untracked.",
    };

    hodgkinHuxleySquidAxonModel1952CodeGeneration(true, TrackingType::VARIABLES, noIssues, variableRelatedExternalIssues);
}

TEST(GeneratorTrackedVariables, hodgkinHuxleySquidAxonModel1952DaeUntrackedConstants)
{
    hodgkinHuxleySquidAxonModel1952CodeGeneration(false, TrackingType::CONSTANTS, noIssues, constantRelatedExternalIssues);
}

TEST(GeneratorTrackedVariables, hodgkinHuxleySquidAxonModel1952DaeUntrackedComputedConstants)
{
    hodgkinHuxleySquidAxonModel1952CodeGeneration(false, TrackingType::COMPUTED_CONSTANTS, noIssues, computedConstantRelatedExternalIssues);
}

const std::vector<std::string> daeIssues = {
    "Variable 'i_Stim' in component 'membrane' is computed using an NLA system and cannot therefore be untracked.",
    "Variable 'i_L' in component 'leakage_current' is computed using an NLA system and cannot therefore be untracked.",
    "Variable 'i_K' in component 'potassium_channel' is computed using an NLA system and cannot therefore be untracked.",
    "Variable 'i_Na' in component 'sodium_channel' is computed using an NLA system and cannot therefore be untracked.",
    "Variable 'E_L' in component 'leakage_current' is computed using an NLA system and cannot therefore be untracked.",
    "Variable 'E_Na' in component 'sodium_channel' is computed using an NLA system and cannot therefore be untracked.",
    "Variable 'beta_m' in component 'sodium_channel_m_gate' is computed using an NLA system and cannot therefore be untracked.",
    "Variable 'alpha_h' in component 'sodium_channel_h_gate' is computed using an NLA system and cannot therefore be untracked.",
    "Variable 'beta_h' in component 'sodium_channel_h_gate' is computed using an NLA system and cannot therefore be untracked.",
    "Variable 'alpha_n' in component 'potassium_channel_n_gate' is computed using an NLA system and cannot therefore be untracked.",
    "Variable 'beta_n' in component 'potassium_channel_n_gate' is computed using an NLA system and cannot therefore be untracked.",
};

TEST(GeneratorTrackedVariables, hodgkinHuxleySquidAxonModel1952DaeUntrackedAlgebraicVariables)
{
    const std::vector<std::string> daeExternalIssues = {
        "Variable 'i_Stim' in component 'membrane' is computed using an NLA system and cannot therefore be untracked.",
        "Variable 'i_L' in component 'leakage_current' is computed using an NLA system and cannot therefore be untracked.",
        "Variable 'i_K' in component 'potassium_channel' is computed using an NLA system and cannot therefore be untracked.",
        "Variable 'E_L' in component 'leakage_current' is computed using an NLA system and cannot therefore be untracked.",
        "Variable 'E_Na' in component 'sodium_channel' is computed using an NLA system and cannot therefore be untracked.",
        "Variable 'alpha_m' in component 'sodium_channel_m_gate' is needed to compute an external variable and cannot therefore be untracked.",
        "Variable 'beta_m' in component 'sodium_channel_m_gate' is computed using an NLA system and cannot therefore be untracked.",
        "Variable 'alpha_h' in component 'sodium_channel_h_gate' is computed using an NLA system and cannot therefore be untracked.",
        "Variable 'beta_h' in component 'sodium_channel_h_gate' is computed using an NLA system and cannot therefore be untracked.",
        "Variable 'alpha_n' in component 'potassium_channel_n_gate' is computed using an NLA system and cannot therefore be untracked.",
        "Variable 'beta_n' in component 'potassium_channel_n_gate' is computed using an NLA system and cannot therefore be untracked.",
    };

    hodgkinHuxleySquidAxonModel1952CodeGeneration(false, TrackingType::ALGEBRAIC, daeIssues, daeExternalIssues);
}

TEST(GeneratorTrackedVariables, hodgkinHuxleySquidAxonModel1952DaeUntrackedVariables)
{
    const std::vector<std::string> daeExternalIssues = {
        "Variable 'Cm' in component 'membrane' is needed to compute an external variable and cannot therefore be untracked.",
        "Variable 'E_K' in component 'potassium_channel' is needed to compute an external variable and cannot therefore be untracked.",
        "Variable 'i_Stim' in component 'membrane' is computed using an NLA system and cannot therefore be untracked.",
        "Variable 'i_L' in component 'leakage_current' is computed using an NLA system and cannot therefore be untracked.",
        "Variable 'i_K' in component 'potassium_channel' is computed using an NLA system and cannot therefore be untracked.",
        "Variable 'E_L' in component 'leakage_current' is computed using an NLA system and cannot therefore be untracked.",
        "Variable 'E_Na' in component 'sodium_channel' is computed using an NLA system and cannot therefore be untracked.",
        "Variable 'alpha_m' in component 'sodium_channel_m_gate' is needed to compute an external variable and cannot therefore be untracked.",
        "Variable 'beta_m' in component 'sodium_channel_m_gate' is computed using an NLA system and cannot therefore be untracked.",
        "Variable 'alpha_h' in component 'sodium_channel_h_gate' is computed using an NLA system and cannot therefore be untracked.",
        "Variable 'beta_h' in component 'sodium_channel_h_gate' is computed using an NLA system and cannot therefore be untracked.",
        "Variable 'alpha_n' in component 'potassium_channel_n_gate' is computed using an NLA system and cannot therefore be untracked.",
        "Variable 'beta_n' in component 'potassium_channel_n_gate' is computed using an NLA system and cannot therefore be untracked.",
    };

    hodgkinHuxleySquidAxonModel1952CodeGeneration(false, TrackingType::VARIABLES, daeIssues, daeExternalIssues);
}

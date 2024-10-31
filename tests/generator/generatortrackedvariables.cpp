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

    const std::vector<std::string> nullVariableIssue = {"The variable is null."};
    const std::vector<libcellml::Issue::Level> errorLevel = {libcellml::Issue::Level::ERROR};
    const std::vector<libcellml::Issue::ReferenceRule> nullVariableReferenceRule = {libcellml::Issue::ReferenceRule::GENERATOR_NULL_VARIABLE};

    generator->trackVariable(nullptr);
    EXPECT_EQ_ISSUES_LEVELS_REFERENCERULES(nullVariableIssue, errorLevel, nullVariableReferenceRule, generator);

    generator->untrackVariable(nullptr);
    EXPECT_EQ_ISSUES_LEVELS_REFERENCERULES(nullVariableIssue, errorLevel, nullVariableReferenceRule, generator);

    const std::vector<std::string> nullModelIssue = {"The model is null."};
    const std::vector<libcellml::Issue::ReferenceRule> nullModelReferenceRule = {libcellml::Issue::ReferenceRule::GENERATOR_NULL_MODEL};

    generator->trackAllConstants(nullptr);
    EXPECT_EQ_ISSUES_LEVELS_REFERENCERULES(nullModelIssue, errorLevel, nullModelReferenceRule, generator);

    generator->untrackAllConstants(nullptr);
    EXPECT_EQ_ISSUES_LEVELS_REFERENCERULES(nullModelIssue, errorLevel, nullModelReferenceRule, generator);

    generator->trackAllComputedConstants(nullptr);
    EXPECT_EQ_ISSUES_LEVELS_REFERENCERULES(nullModelIssue, errorLevel, nullModelReferenceRule, generator);

    generator->untrackAllComputedConstants(nullptr);
    EXPECT_EQ_ISSUES_LEVELS_REFERENCERULES(nullModelIssue, errorLevel, nullModelReferenceRule, generator);

    generator->trackAllAlgebraic(nullptr);
    EXPECT_EQ_ISSUES_LEVELS_REFERENCERULES(nullModelIssue, errorLevel, nullModelReferenceRule, generator);

    generator->untrackAllAlgebraic(nullptr);
    EXPECT_EQ_ISSUES_LEVELS_REFERENCERULES(nullModelIssue, errorLevel, nullModelReferenceRule, generator);

    generator->trackAllVariables(nullptr);
    EXPECT_EQ_ISSUES_LEVELS_REFERENCERULES(nullModelIssue, errorLevel, nullModelReferenceRule, generator);

    generator->untrackAllVariables(nullptr);
    EXPECT_EQ_ISSUES_LEVELS_REFERENCERULES(nullModelIssue, errorLevel, nullModelReferenceRule, generator);

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
    EXPECT_EQ_ISSUES_LEVELS_REFERENCERULES({}, {}, {}, generator);

    EXPECT_FALSE(generator->isTrackedVariable(analyserModel->variable(variable)));
    EXPECT_TRUE(generator->isUntrackedVariable(analyserModel->variable(variable)));

    EXPECT_EQ(size_t(17), generator->trackedVariableCount(analyserModel));
    EXPECT_EQ(size_t(1), generator->untrackedVariableCount(analyserModel));

    generator->trackVariable(analyserModel->variable(variable));
    EXPECT_EQ_ISSUES_LEVELS_REFERENCERULES({}, {}, {}, generator);

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
    EXPECT_EQ_ISSUES_LEVELS_REFERENCERULES({}, {}, {}, generator);

    EXPECT_FALSE(generator->isTrackedVariable(analyserModel->variable(variable)));
    EXPECT_TRUE(generator->isUntrackedVariable(analyserModel->variable(variable)));

    EXPECT_EQ(size_t(17), generator->trackedVariableCount(analyserModel));
    EXPECT_EQ(size_t(1), generator->untrackedVariableCount(analyserModel));

    generator->trackVariable(analyserModel->variable(variable));
    EXPECT_EQ_ISSUES_LEVELS_REFERENCERULES({}, {}, {}, generator);

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
    EXPECT_EQ_ISSUES_LEVELS_REFERENCERULES({}, {}, {}, generator);

    EXPECT_FALSE(generator->isTrackedVariable(analyserModel->variable(variable)));
    EXPECT_TRUE(generator->isUntrackedVariable(analyserModel->variable(variable)));

    EXPECT_EQ(size_t(17), generator->trackedVariableCount(analyserModel));
    EXPECT_EQ(size_t(1), generator->untrackedVariableCount(analyserModel));

    generator->trackVariable(analyserModel->variable(variable));
    EXPECT_EQ_ISSUES_LEVELS_REFERENCERULES({}, {}, {}, generator);

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
    EXPECT_EQ_ISSUES_LEVELS_REFERENCERULES({}, {}, {}, generator);

    EXPECT_EQ(size_t(0), generator->trackedConstantCount(analyserModel));
    EXPECT_EQ(size_t(5), generator->untrackedConstantCount(analyserModel));
    EXPECT_EQ(size_t(13), generator->trackedVariableCount(analyserModel));
    EXPECT_EQ(size_t(5), generator->untrackedVariableCount(analyserModel));

    generator->trackAllConstants(analyserModel);
    EXPECT_EQ_ISSUES_LEVELS_REFERENCERULES({}, {}, {}, generator);

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
    EXPECT_EQ_ISSUES_LEVELS_REFERENCERULES({}, {}, {}, generator);

    EXPECT_EQ(size_t(0), generator->trackedComputedConstantCount(analyserModel));
    EXPECT_EQ(size_t(3), generator->untrackedComputedConstantCount(analyserModel));
    EXPECT_EQ(size_t(15), generator->trackedVariableCount(analyserModel));
    EXPECT_EQ(size_t(3), generator->untrackedVariableCount(analyserModel));

    generator->trackAllComputedConstants(analyserModel);
    EXPECT_EQ_ISSUES_LEVELS_REFERENCERULES({}, {}, {}, generator);

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
    EXPECT_EQ_ISSUES_LEVELS_REFERENCERULES({}, {}, {}, generator);

    EXPECT_EQ(size_t(0), generator->trackedAlgebraicCount(analyserModel));
    EXPECT_EQ(size_t(10), generator->untrackedAlgebraicCount(analyserModel));
    EXPECT_EQ(size_t(8), generator->trackedVariableCount(analyserModel));
    EXPECT_EQ(size_t(10), generator->untrackedVariableCount(analyserModel));

    generator->trackAllAlgebraic(analyserModel);
    EXPECT_EQ_ISSUES_LEVELS_REFERENCERULES({}, {}, {}, generator);

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
    EXPECT_EQ_ISSUES_LEVELS_REFERENCERULES({}, {}, {}, generator);

    EXPECT_EQ(size_t(0), generator->trackedVariableCount(analyserModel));
    EXPECT_EQ(size_t(18), generator->untrackedVariableCount(analyserModel));

    generator->trackAllVariables(analyserModel);
    EXPECT_EQ_ISSUES_LEVELS_REFERENCERULES({}, {}, {}, generator);

    EXPECT_EQ(size_t(18), generator->trackedVariableCount(analyserModel));
    EXPECT_EQ(size_t(0), generator->untrackedVariableCount(analyserModel));
}

enum class TrackingType
{
    CONTROL,
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
    default: // CONTROL.
        break;
    }
}

void hodgkinHuxleySquidAxonModel1952CodeGeneration(bool ode, TrackingType trackingType,
                                                   const std::vector<std::string> &issues,
                                                   const std::vector<libcellml::Issue::Level> &levels,
                                                   const std::vector<libcellml::Issue::ReferenceRule> &referenceRules,
                                                   const std::vector<std::string> &externalIssues,
                                                   const std::vector<libcellml::Issue::Level> &externalLevels,
                                                   const std::vector<libcellml::Issue::ReferenceRule> &externalReferenceRules)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents(std::string("generator/hodgkin_huxley_squid_axon_model_1952/model") + (ode ? "" : ".dae.for.tracking") + ".cellml"));
    auto analyser = libcellml::Analyser::create();
    auto generator = libcellml::Generator::create();
    std::string modelType = ode ? "model" : "model.dae.for.tracking";
    std::string variableType = (trackingType == TrackingType::VARIABLES) ?
                                   "untracked.variables" :
                                   ((trackingType == TrackingType::CONSTANTS) ?
                                        "untracked.constants" :
                                        ((trackingType == TrackingType::COMPUTED_CONSTANTS) ?
                                             "untracked.computed.constants" :
                                             ((trackingType == TrackingType::ALGEBRAIC) ?
                                                  "untracked.algebraic.variables" :
                                                  "control")));

    analyser->analyseModel(model);

    auto analyserModel = analyser->model();

    untrack(analyserModel, generator, trackingType);

    EXPECT_EQ_ISSUES_LEVELS_REFERENCERULES(issues, levels, referenceRules, generator);

    auto profile = generator->profile();

    profile->setInterfaceFileNameString(modelType + "." + variableType + ".h");

    EXPECT_EQ_FILE_CONTENTS("generator/hodgkin_huxley_squid_axon_model_1952/" + modelType + "." + variableType + ".h", generator->interfaceCode(analyserModel));
    EXPECT_EQ_FILE_CONTENTS("generator/hodgkin_huxley_squid_axon_model_1952/" + modelType + "." + variableType + ".c", generator->implementationCode(analyserModel));

    profile = libcellml::GeneratorProfile::create(libcellml::GeneratorProfile::Profile::PYTHON);

    generator->setProfile(profile);

    EXPECT_EQ_FILE_CONTENTS("generator/hodgkin_huxley_squid_axon_model_1952/" + modelType + "." + variableType + ".py", generator->implementationCode(analyserModel));

    // With an external variable with a dependency on a constant, computed constant, and algebraic variable.

    auto membrane_Cm = model->component("membrane")->variable("Cm"); // Constant.
    auto potassium_channel_EK = model->component("potassium_channel")->variable("E_K"); // Computed constant.
    auto sodium_channel_m_gate_alapha_m = model->component("sodium_channel_m_gate")->variable("alpha_m"); // Algebraic variable.
    auto external_sodium_channel_i_Na = libcellml::AnalyserExternalVariable::create(model->component("sodium_channel")->variable("i_Na"));

    external_sodium_channel_i_Na->addDependency(membrane_Cm);
    external_sodium_channel_i_Na->addDependency(potassium_channel_EK);
    external_sodium_channel_i_Na->addDependency(sodium_channel_m_gate_alapha_m);

    analyser->addExternalVariable(external_sodium_channel_i_Na);

    analyser->analyseModel(model);

    analyserModel = analyser->model();

    untrack(analyserModel, generator, trackingType);

    EXPECT_EQ_ISSUES_LEVELS_REFERENCERULES(externalIssues, externalLevels, externalReferenceRules, generator);

    profile = libcellml::GeneratorProfile::create(libcellml::GeneratorProfile::Profile::C);

    generator->setProfile(profile);

    profile->setInterfaceFileNameString(modelType + "." + variableType + ".with.externals.h");

    EXPECT_EQ_FILE_CONTENTS("generator/hodgkin_huxley_squid_axon_model_1952/" + modelType + "." + variableType + ".with.externals.h", generator->interfaceCode(analyserModel));
    EXPECT_EQ_FILE_CONTENTS("generator/hodgkin_huxley_squid_axon_model_1952/" + modelType + "." + variableType + ".with.externals.c", generator->implementationCode(analyserModel));

    profile = libcellml::GeneratorProfile::create(libcellml::GeneratorProfile::Profile::PYTHON);

    generator->setProfile(profile);

    EXPECT_EQ_FILE_CONTENTS("generator/hodgkin_huxley_squid_axon_model_1952/" + modelType + "." + variableType + ".with.externals.py", generator->implementationCode(analyserModel));
}

TEST(GeneratorTrackedVariables, hodgkinHuxleySquidAxonModel1952Control)
{
    hodgkinHuxleySquidAxonModel1952CodeGeneration(true, TrackingType::CONSTANTS,
                                                  {}, {}, {},
                                                  {"Variable 'Cm' in component 'membrane' is needed to compute an external variable and cannot therefore be untracked."},
                                                  {libcellml::Issue::Level::ERROR},
                                                  {libcellml::Issue::ReferenceRule::GENERATOR_EXTERNALLY_NEEDED_VARIABLE_NOT_UNTRACKABLE});
}

TEST(GeneratorTrackedVariables, hodgkinHuxleySquidAxonModel1952UntrackedConstants)
{
    hodgkinHuxleySquidAxonModel1952CodeGeneration(true, TrackingType::CONSTANTS,
                                                  {}, {}, {},
                                                  {"Variable 'Cm' in component 'membrane' is needed to compute an external variable and cannot therefore be untracked."},
                                                  {libcellml::Issue::Level::ERROR},
                                                  {libcellml::Issue::ReferenceRule::GENERATOR_EXTERNALLY_NEEDED_VARIABLE_NOT_UNTRACKABLE});
}

TEST(GeneratorTrackedVariables, hodgkinHuxleySquidAxonModel1952UntrackedComputedConstants)
{
    hodgkinHuxleySquidAxonModel1952CodeGeneration(true, TrackingType::COMPUTED_CONSTANTS,
                                                  {}, {}, {},
                                                  {"Variable 'E_K' in component 'potassium_channel' is needed to compute an external variable and cannot therefore be untracked."},
                                                  {libcellml::Issue::Level::ERROR},
                                                  {libcellml::Issue::ReferenceRule::GENERATOR_EXTERNALLY_NEEDED_VARIABLE_NOT_UNTRACKABLE});
}

const std::vector<std::string> algebraicRelatedExternalIssues = {
    "Variable 'alpha_m' in component 'sodium_channel_m_gate' is needed to compute an external variable and cannot therefore be untracked.",
};

TEST(GeneratorTrackedVariables, hodgkinHuxleySquidAxonModel1952UntrackedAlgebraicVariables)
{
    hodgkinHuxleySquidAxonModel1952CodeGeneration(true, TrackingType::ALGEBRAIC,
                                                  {}, {}, {},
                                                  {"Variable 'alpha_m' in component 'sodium_channel_m_gate' is needed to compute an external variable and cannot therefore be untracked."},
                                                  {libcellml::Issue::Level::ERROR},
                                                  {libcellml::Issue::ReferenceRule::GENERATOR_EXTERNALLY_NEEDED_VARIABLE_NOT_UNTRACKABLE});
}

TEST(GeneratorTrackedVariables, hodgkinHuxleySquidAxonModel1952UntrackedVariables)
{
    hodgkinHuxleySquidAxonModel1952CodeGeneration(true, TrackingType::VARIABLES,
                                                  {}, {}, {},
                                                  {
                                                      "Variable 'Cm' in component 'membrane' is needed to compute an external variable and cannot therefore be untracked.",
                                                      "Variable 'E_K' in component 'potassium_channel' is needed to compute an external variable and cannot therefore be untracked.",
                                                      "Variable 'alpha_m' in component 'sodium_channel_m_gate' is needed to compute an external variable and cannot therefore be untracked.",
                                                  },
                                                  expectedLevels(3, libcellml::Issue::Level::ERROR),
                                                  expectedReferenceRules(3, libcellml::Issue::ReferenceRule::GENERATOR_EXTERNALLY_NEEDED_VARIABLE_NOT_UNTRACKABLE));
}

TEST(GeneratorTrackedVariables, hodgkinHuxleySquidAxonModel1952DaeControl)
{
    hodgkinHuxleySquidAxonModel1952CodeGeneration(false, TrackingType::CONTROL,
                                                  {}, {}, {},
                                                  {}, {}, {});
}

TEST(GeneratorTrackedVariables, hodgkinHuxleySquidAxonModel1952DaeUntrackedConstants)
{
    hodgkinHuxleySquidAxonModel1952CodeGeneration(false, TrackingType::CONSTANTS,
                                                  {}, {}, {},
                                                  {"Variable 'Cm' in component 'membrane' is needed to compute an external variable and cannot therefore be untracked."},
                                                  {libcellml::Issue::Level::ERROR},
                                                  {libcellml::Issue::ReferenceRule::GENERATOR_EXTERNALLY_NEEDED_VARIABLE_NOT_UNTRACKABLE});
}

TEST(GeneratorTrackedVariables, hodgkinHuxleySquidAxonModel1952DaeUntrackedComputedConstants)
{
    hodgkinHuxleySquidAxonModel1952CodeGeneration(false, TrackingType::COMPUTED_CONSTANTS,
                                                  {}, {}, {},
                                                  {"Variable 'E_K' in component 'potassium_channel' is needed to compute an external variable and cannot therefore be untracked."},
                                                  {libcellml::Issue::Level::ERROR},
                                                  {libcellml::Issue::ReferenceRule::GENERATOR_EXTERNALLY_NEEDED_VARIABLE_NOT_UNTRACKABLE});
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
const std::vector<libcellml::Issue::Level> daeLevels = expectedLevels(daeIssues.size(), libcellml::Issue::Level::ERROR);
const std::vector<libcellml::Issue::ReferenceRule> daeReferenceRules = expectedReferenceRules(daeIssues.size(), libcellml::Issue::ReferenceRule::GENERATOR_NLA_BASED_VARIABLE_NOT_UNTRACKABLE);

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
    const std::vector<libcellml::Issue::ReferenceRule> daeExternalReferenceRules = {
        libcellml::Issue::ReferenceRule::GENERATOR_NLA_BASED_VARIABLE_NOT_UNTRACKABLE,
        libcellml::Issue::ReferenceRule::GENERATOR_NLA_BASED_VARIABLE_NOT_UNTRACKABLE,
        libcellml::Issue::ReferenceRule::GENERATOR_NLA_BASED_VARIABLE_NOT_UNTRACKABLE,
        libcellml::Issue::ReferenceRule::GENERATOR_NLA_BASED_VARIABLE_NOT_UNTRACKABLE,
        libcellml::Issue::ReferenceRule::GENERATOR_NLA_BASED_VARIABLE_NOT_UNTRACKABLE,
        libcellml::Issue::ReferenceRule::GENERATOR_EXTERNALLY_NEEDED_VARIABLE_NOT_UNTRACKABLE,
        libcellml::Issue::ReferenceRule::GENERATOR_NLA_BASED_VARIABLE_NOT_UNTRACKABLE,
        libcellml::Issue::ReferenceRule::GENERATOR_NLA_BASED_VARIABLE_NOT_UNTRACKABLE,
        libcellml::Issue::ReferenceRule::GENERATOR_NLA_BASED_VARIABLE_NOT_UNTRACKABLE,
        libcellml::Issue::ReferenceRule::GENERATOR_NLA_BASED_VARIABLE_NOT_UNTRACKABLE,
        libcellml::Issue::ReferenceRule::GENERATOR_NLA_BASED_VARIABLE_NOT_UNTRACKABLE,
    };

    hodgkinHuxleySquidAxonModel1952CodeGeneration(false, TrackingType::ALGEBRAIC,
                                                  daeIssues, daeLevels, daeReferenceRules,
                                                  daeExternalIssues, expectedLevels(daeExternalIssues.size(), libcellml::Issue::Level::ERROR), daeExternalReferenceRules);
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
    const std::vector<libcellml::Issue::ReferenceRule> daeExternalReferenceRules = {
        libcellml::Issue::ReferenceRule::GENERATOR_EXTERNALLY_NEEDED_VARIABLE_NOT_UNTRACKABLE,
        libcellml::Issue::ReferenceRule::GENERATOR_EXTERNALLY_NEEDED_VARIABLE_NOT_UNTRACKABLE,
        libcellml::Issue::ReferenceRule::GENERATOR_NLA_BASED_VARIABLE_NOT_UNTRACKABLE,
        libcellml::Issue::ReferenceRule::GENERATOR_NLA_BASED_VARIABLE_NOT_UNTRACKABLE,
        libcellml::Issue::ReferenceRule::GENERATOR_NLA_BASED_VARIABLE_NOT_UNTRACKABLE,
        libcellml::Issue::ReferenceRule::GENERATOR_NLA_BASED_VARIABLE_NOT_UNTRACKABLE,
        libcellml::Issue::ReferenceRule::GENERATOR_NLA_BASED_VARIABLE_NOT_UNTRACKABLE,
        libcellml::Issue::ReferenceRule::GENERATOR_EXTERNALLY_NEEDED_VARIABLE_NOT_UNTRACKABLE,
        libcellml::Issue::ReferenceRule::GENERATOR_NLA_BASED_VARIABLE_NOT_UNTRACKABLE,
        libcellml::Issue::ReferenceRule::GENERATOR_NLA_BASED_VARIABLE_NOT_UNTRACKABLE,
        libcellml::Issue::ReferenceRule::GENERATOR_NLA_BASED_VARIABLE_NOT_UNTRACKABLE,
        libcellml::Issue::ReferenceRule::GENERATOR_NLA_BASED_VARIABLE_NOT_UNTRACKABLE,
        libcellml::Issue::ReferenceRule::GENERATOR_NLA_BASED_VARIABLE_NOT_UNTRACKABLE,
    };

    hodgkinHuxleySquidAxonModel1952CodeGeneration(false, TrackingType::VARIABLES,
                                                  daeIssues, daeLevels, daeReferenceRules,
                                                  daeExternalIssues, expectedLevels(daeExternalIssues.size(), libcellml::Issue::Level::ERROR), daeExternalReferenceRules);
}

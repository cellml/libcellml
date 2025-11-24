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

TEST(GeneratorContext, noModelOrVariable)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("generator/hodgkin_huxley_squid_axon_model_1952/model.cellml"));
    auto analyser = libcellml::Analyser::create();

    analyser->analyseModel(model);

    auto analyserModel = analyser->analyserModel();
    auto generatorContext = libcellml::GeneratorContext::create();

    EXPECT_FALSE(generatorContext->isTrackedVariable(nullptr));
    EXPECT_FALSE(generatorContext->isUntrackedVariable(nullptr));

    const std::vector<std::string> nullVariableIssue = {"The variable is null."};
    const std::vector<libcellml::Issue::Level> errorLevel = {libcellml::Issue::Level::ERROR};
    const std::vector<libcellml::Issue::ReferenceRule> nullVariableReferenceRule = {libcellml::Issue::ReferenceRule::GENERATOR_NULL_VARIABLE};

    generatorContext->trackVariable(nullptr);
    EXPECT_EQ_ISSUES_LEVELS_REFERENCERULES(nullVariableIssue, errorLevel, nullVariableReferenceRule, generatorContext);

    generatorContext->untrackVariable(nullptr);
    EXPECT_EQ_ISSUES_LEVELS_REFERENCERULES(nullVariableIssue, errorLevel, nullVariableReferenceRule, generatorContext);

    const std::vector<std::string> nullModelIssue = {"The model is null."};
    const std::vector<libcellml::Issue::ReferenceRule> nullModelReferenceRule = {libcellml::Issue::ReferenceRule::GENERATOR_NULL_MODEL};

    generatorContext->trackAllConstants(nullptr);
    EXPECT_EQ_ISSUES_LEVELS_REFERENCERULES(nullModelIssue, errorLevel, nullModelReferenceRule, generatorContext);

    generatorContext->untrackAllConstants(nullptr);
    EXPECT_EQ_ISSUES_LEVELS_REFERENCERULES(nullModelIssue, errorLevel, nullModelReferenceRule, generatorContext);

    generatorContext->trackAllComputedConstants(nullptr);
    EXPECT_EQ_ISSUES_LEVELS_REFERENCERULES(nullModelIssue, errorLevel, nullModelReferenceRule, generatorContext);

    generatorContext->untrackAllComputedConstants(nullptr);
    EXPECT_EQ_ISSUES_LEVELS_REFERENCERULES(nullModelIssue, errorLevel, nullModelReferenceRule, generatorContext);

    generatorContext->trackAllAlgebraicVariables(nullptr);
    EXPECT_EQ_ISSUES_LEVELS_REFERENCERULES(nullModelIssue, errorLevel, nullModelReferenceRule, generatorContext);

    generatorContext->untrackAllAlgebraicVariables(nullptr);
    EXPECT_EQ_ISSUES_LEVELS_REFERENCERULES(nullModelIssue, errorLevel, nullModelReferenceRule, generatorContext);

    generatorContext->trackAllVariables(nullptr);
    EXPECT_EQ_ISSUES_LEVELS_REFERENCERULES(nullModelIssue, errorLevel, nullModelReferenceRule, generatorContext);

    generatorContext->untrackAllVariables(nullptr);
    EXPECT_EQ_ISSUES_LEVELS_REFERENCERULES(nullModelIssue, errorLevel, nullModelReferenceRule, generatorContext);

    EXPECT_EQ(size_t(0), generatorContext->trackedConstantCount(nullptr));
    EXPECT_EQ(size_t(0), generatorContext->untrackedConstantCount(nullptr));

    EXPECT_EQ(size_t(0), generatorContext->trackedComputedConstantCount(nullptr));
    EXPECT_EQ(size_t(0), generatorContext->untrackedComputedConstantCount(nullptr));

    EXPECT_EQ(size_t(0), generatorContext->trackedAlgebraicVariableCount(nullptr));
    EXPECT_EQ(size_t(0), generatorContext->untrackedAlgebraicVariableCount(nullptr));

    EXPECT_EQ(size_t(0), generatorContext->trackedVariableCount(nullptr));
    EXPECT_EQ(size_t(0), generatorContext->untrackedVariableCount(nullptr));
}

TEST(GeneratorContext, tracAndkUntrackVariableOfIntegration)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("generator/hodgkin_huxley_squid_axon_model_1952/model.cellml"));
    auto analyser = libcellml::Analyser::create();

    analyser->addExternalVariable(libcellml::AnalyserExternalVariable::create(model->component("membrane")->variable("V")));
    // Note: this external variable helps with our coverage since we check for the variable of integration last in
    //       Generator::GeneratorImpl::trackVariable().

    analyser->analyseModel(model);

    auto analyserModel = analyser->analyserModel();
    auto generatorContext = libcellml::GeneratorContext::create();

    auto variable = model->component("environment")->variable("time");

    EXPECT_TRUE(generatorContext->isTrackedVariable(analyserModel->analyserVariable(variable)));
    EXPECT_FALSE(generatorContext->isUntrackedVariable(analyserModel->analyserVariable(variable)));

    EXPECT_EQ(size_t(18), generatorContext->trackedVariableCount(analyserModel));
    EXPECT_EQ(size_t(0), generatorContext->untrackedVariableCount(analyserModel));

    generatorContext->untrackVariable(analyserModel->analyserVariable(variable));
    EXPECT_EQ_ISSUES({"Variable 'time' in component 'environment' is the variable of integration and cannot therefore be untracked."}, generatorContext);

    EXPECT_TRUE(generatorContext->isTrackedVariable(analyserModel->analyserVariable(variable)));
    EXPECT_FALSE(generatorContext->isUntrackedVariable(analyserModel->analyserVariable(variable)));

    EXPECT_EQ(size_t(18), generatorContext->trackedVariableCount(analyserModel));
    EXPECT_EQ(size_t(0), generatorContext->untrackedVariableCount(analyserModel));

    generatorContext->trackVariable(analyserModel->analyserVariable(variable));
    EXPECT_EQ_ISSUES({"Variable 'time' in component 'environment' is the variable of integration and is therefore always tracked."}, generatorContext);

    EXPECT_EQ(size_t(18), generatorContext->trackedVariableCount(analyserModel));
    EXPECT_EQ(size_t(0), generatorContext->untrackedVariableCount(analyserModel));
}

TEST(GeneratorContext, trackAndUntrackStateVariable)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("generator/hodgkin_huxley_squid_axon_model_1952/model.cellml"));
    auto analyser = libcellml::Analyser::create();

    analyser->analyseModel(model);

    auto analyserModel = analyser->analyserModel();
    auto generatorContext = libcellml::GeneratorContext::create();

    auto variable = model->component("membrane")->variable("V");

    EXPECT_TRUE(generatorContext->isTrackedVariable(analyserModel->analyserVariable(variable)));
    EXPECT_FALSE(generatorContext->isUntrackedVariable(analyserModel->analyserVariable(variable)));

    EXPECT_EQ(size_t(18), generatorContext->trackedVariableCount(analyserModel));
    EXPECT_EQ(size_t(0), generatorContext->untrackedVariableCount(analyserModel));

    generatorContext->untrackVariable(analyserModel->analyserVariable(variable));
    EXPECT_EQ_ISSUES({"Variable 'V' in component 'membrane' is a state variable and cannot therefore be untracked."}, generatorContext);

    EXPECT_TRUE(generatorContext->isTrackedVariable(analyserModel->analyserVariable(variable)));
    EXPECT_FALSE(generatorContext->isUntrackedVariable(analyserModel->analyserVariable(variable)));

    EXPECT_EQ(size_t(18), generatorContext->trackedVariableCount(analyserModel));
    EXPECT_EQ(size_t(0), generatorContext->untrackedVariableCount(analyserModel));

    generatorContext->trackVariable(analyserModel->analyserVariable(variable));
    EXPECT_EQ_ISSUES({"Variable 'V' in component 'membrane' is a state variable and is therefore always tracked."}, generatorContext);

    EXPECT_EQ(size_t(18), generatorContext->trackedVariableCount(analyserModel));
    EXPECT_EQ(size_t(0), generatorContext->untrackedVariableCount(analyserModel));
}

TEST(GeneratorContext, trackAndUntrackConstant)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("generator/hodgkin_huxley_squid_axon_model_1952/model.cellml"));
    auto analyser = libcellml::Analyser::create();

    analyser->analyseModel(model);

    auto analyserModel = analyser->analyserModel();
    auto generatorContext = libcellml::GeneratorContext::create();

    auto variable = model->component("membrane")->variable("Cm");

    EXPECT_TRUE(generatorContext->isTrackedVariable(analyserModel->analyserVariable(variable)));
    EXPECT_FALSE(generatorContext->isUntrackedVariable(analyserModel->analyserVariable(variable)));

    EXPECT_EQ(size_t(18), generatorContext->trackedVariableCount(analyserModel));
    EXPECT_EQ(size_t(0), generatorContext->untrackedVariableCount(analyserModel));

    generatorContext->untrackVariable(analyserModel->analyserVariable(variable));
    EXPECT_EQ_ISSUES_LEVELS_REFERENCERULES({}, {}, {}, generatorContext);

    EXPECT_FALSE(generatorContext->isTrackedVariable(analyserModel->analyserVariable(variable)));
    EXPECT_TRUE(generatorContext->isUntrackedVariable(analyserModel->analyserVariable(variable)));

    EXPECT_EQ(size_t(17), generatorContext->trackedVariableCount(analyserModel));
    EXPECT_EQ(size_t(1), generatorContext->untrackedVariableCount(analyserModel));

    generatorContext->trackVariable(analyserModel->analyserVariable(variable));
    EXPECT_EQ_ISSUES_LEVELS_REFERENCERULES({}, {}, {}, generatorContext);

    EXPECT_EQ(size_t(18), generatorContext->trackedVariableCount(analyserModel));
    EXPECT_EQ(size_t(0), generatorContext->untrackedVariableCount(analyserModel));
}

TEST(GeneratorContext, trackAndUntrackComputedConstant)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("generator/hodgkin_huxley_squid_axon_model_1952/model.cellml"));
    auto analyser = libcellml::Analyser::create();

    analyser->analyseModel(model);

    auto analyserModel = analyser->analyserModel();
    auto generatorContext = libcellml::GeneratorContext::create();

    auto variable = model->component("leakage_current")->variable("E_L");

    EXPECT_TRUE(generatorContext->isTrackedVariable(analyserModel->analyserVariable(variable)));
    EXPECT_FALSE(generatorContext->isUntrackedVariable(analyserModel->analyserVariable(variable)));

    EXPECT_EQ(size_t(18), generatorContext->trackedVariableCount(analyserModel));
    EXPECT_EQ(size_t(0), generatorContext->untrackedVariableCount(analyserModel));

    generatorContext->untrackVariable(analyserModel->analyserVariable(variable));
    EXPECT_EQ_ISSUES_LEVELS_REFERENCERULES({}, {}, {}, generatorContext);

    EXPECT_FALSE(generatorContext->isTrackedVariable(analyserModel->analyserVariable(variable)));
    EXPECT_TRUE(generatorContext->isUntrackedVariable(analyserModel->analyserVariable(variable)));

    EXPECT_EQ(size_t(17), generatorContext->trackedVariableCount(analyserModel));
    EXPECT_EQ(size_t(1), generatorContext->untrackedVariableCount(analyserModel));

    generatorContext->trackVariable(analyserModel->analyserVariable(variable));
    EXPECT_EQ_ISSUES_LEVELS_REFERENCERULES({}, {}, {}, generatorContext);

    EXPECT_EQ(size_t(18), generatorContext->trackedVariableCount(analyserModel));
    EXPECT_EQ(size_t(0), generatorContext->untrackedVariableCount(analyserModel));
}

TEST(GeneratorContext, trackAndUntrackAlgebraicVariable)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("generator/hodgkin_huxley_squid_axon_model_1952/model.cellml"));
    auto analyser = libcellml::Analyser::create();

    analyser->analyseModel(model);

    auto analyserModel = analyser->analyserModel();
    auto generatorContext = libcellml::GeneratorContext::create();

    auto variable = model->component("membrane")->variable("i_Stim");

    EXPECT_TRUE(generatorContext->isTrackedVariable(analyserModel->analyserVariable(variable)));
    EXPECT_FALSE(generatorContext->isUntrackedVariable(analyserModel->analyserVariable(variable)));

    EXPECT_EQ(size_t(18), generatorContext->trackedVariableCount(analyserModel));
    EXPECT_EQ(size_t(0), generatorContext->untrackedVariableCount(analyserModel));

    generatorContext->untrackVariable(analyserModel->analyserVariable(variable));
    EXPECT_EQ_ISSUES_LEVELS_REFERENCERULES({}, {}, {}, generatorContext);

    EXPECT_FALSE(generatorContext->isTrackedVariable(analyserModel->analyserVariable(variable)));
    EXPECT_TRUE(generatorContext->isUntrackedVariable(analyserModel->analyserVariable(variable)));

    EXPECT_EQ(size_t(17), generatorContext->trackedVariableCount(analyserModel));
    EXPECT_EQ(size_t(1), generatorContext->untrackedVariableCount(analyserModel));

    generatorContext->trackVariable(analyserModel->analyserVariable(variable));
    EXPECT_EQ_ISSUES_LEVELS_REFERENCERULES({}, {}, {}, generatorContext);

    EXPECT_EQ(size_t(18), generatorContext->trackedVariableCount(analyserModel));
    EXPECT_EQ(size_t(0), generatorContext->untrackedVariableCount(analyserModel));
}

TEST(GeneratorContext, trackAndUntrackExternalVariable)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("generator/hodgkin_huxley_squid_axon_model_1952/model.cellml"));
    auto analyser = libcellml::Analyser::create();

    analyser->addExternalVariable(libcellml::AnalyserExternalVariable::create(model->component("membrane")->variable("V")));

    analyser->analyseModel(model);

    auto analyserModel = analyser->analyserModel();
    auto generatorContext = libcellml::GeneratorContext::create();

    auto variable = model->component("membrane")->variable("V");

    EXPECT_TRUE(generatorContext->isTrackedVariable(analyserModel->analyserVariable(variable)));
    EXPECT_FALSE(generatorContext->isUntrackedVariable(analyserModel->analyserVariable(variable)));

    EXPECT_EQ(size_t(18), generatorContext->trackedVariableCount(analyserModel));
    EXPECT_EQ(size_t(0), generatorContext->untrackedVariableCount(analyserModel));

    generatorContext->untrackVariable(analyserModel->analyserVariable(variable));
    EXPECT_EQ_ISSUES({"Variable 'V' in component 'membrane' is an external variable and cannot therefore be untracked."}, generatorContext);

    EXPECT_TRUE(generatorContext->isTrackedVariable(analyserModel->analyserVariable(variable)));
    EXPECT_FALSE(generatorContext->isUntrackedVariable(analyserModel->analyserVariable(variable)));

    EXPECT_EQ(size_t(18), generatorContext->trackedVariableCount(analyserModel));
    EXPECT_EQ(size_t(0), generatorContext->untrackedVariableCount(analyserModel));

    generatorContext->trackVariable(analyserModel->analyserVariable(variable));
    EXPECT_EQ_ISSUES({"Variable 'V' in component 'membrane' is an external variable and is therefore always tracked."}, generatorContext);

    EXPECT_EQ(size_t(18), generatorContext->trackedVariableCount(analyserModel));
    EXPECT_EQ(size_t(0), generatorContext->untrackedVariableCount(analyserModel));
}

TEST(GeneratorContext, trackAndUntrackVariableFromOtherModel)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("generator/hodgkin_huxley_squid_axon_model_1952/model.cellml"));
    auto otherModel = parser->parseModel(fileContents("generator/noble_model_1962/model.cellml"));
    auto analyser = libcellml::Analyser::create();

    analyser->analyseModel(model);

    auto analyserModel = analyser->analyserModel();
    auto generatorContext = libcellml::GeneratorContext::create();

    auto otherVariable = otherModel->component("membrane")->variable("Cm");

    generatorContext->trackVariable(analyserModel->analyserVariable(otherVariable));
    EXPECT_EQ_ISSUES({"The variable is null."}, generatorContext);

    generatorContext->untrackVariable(analyserModel->analyserVariable(otherVariable));
    EXPECT_EQ_ISSUES({"The variable is null."}, generatorContext);
}

TEST(GeneratorContext, trackAndUntrackAllConstants)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("generator/hodgkin_huxley_squid_axon_model_1952/model.cellml"));
    auto analyser = libcellml::Analyser::create();

    analyser->analyseModel(model);

    auto analyserModel = analyser->analyserModel();
    auto generatorContext = libcellml::GeneratorContext::create();

    EXPECT_EQ(size_t(5), generatorContext->trackedConstantCount(analyserModel));
    EXPECT_EQ(size_t(0), generatorContext->untrackedConstantCount(analyserModel));
    EXPECT_EQ(size_t(18), generatorContext->trackedVariableCount(analyserModel));
    EXPECT_EQ(size_t(0), generatorContext->untrackedVariableCount(analyserModel));

    generatorContext->untrackAllConstants(analyserModel);
    EXPECT_EQ_ISSUES_LEVELS_REFERENCERULES({}, {}, {}, generatorContext);

    EXPECT_EQ(size_t(0), generatorContext->trackedConstantCount(analyserModel));
    EXPECT_EQ(size_t(5), generatorContext->untrackedConstantCount(analyserModel));
    EXPECT_EQ(size_t(13), generatorContext->trackedVariableCount(analyserModel));
    EXPECT_EQ(size_t(5), generatorContext->untrackedVariableCount(analyserModel));

    generatorContext->trackAllConstants(analyserModel);
    EXPECT_EQ_ISSUES_LEVELS_REFERENCERULES({}, {}, {}, generatorContext);

    EXPECT_EQ(size_t(5), generatorContext->trackedConstantCount(analyserModel));
    EXPECT_EQ(size_t(0), generatorContext->untrackedConstantCount(analyserModel));
    EXPECT_EQ(size_t(18), generatorContext->trackedVariableCount(analyserModel));
    EXPECT_EQ(size_t(0), generatorContext->untrackedVariableCount(analyserModel));
}

TEST(GeneratorContext, trackAndUntrackAllComputedConstants)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("generator/hodgkin_huxley_squid_axon_model_1952/model.cellml"));
    auto analyser = libcellml::Analyser::create();

    analyser->analyseModel(model);

    auto analyserModel = analyser->analyserModel();
    auto generatorContext = libcellml::GeneratorContext::create();

    EXPECT_EQ(size_t(3), generatorContext->trackedComputedConstantCount(analyserModel));
    EXPECT_EQ(size_t(0), generatorContext->untrackedComputedConstantCount(analyserModel));
    EXPECT_EQ(size_t(18), generatorContext->trackedVariableCount(analyserModel));
    EXPECT_EQ(size_t(0), generatorContext->untrackedVariableCount(analyserModel));

    generatorContext->untrackAllComputedConstants(analyserModel);
    EXPECT_EQ_ISSUES_LEVELS_REFERENCERULES({}, {}, {}, generatorContext);

    EXPECT_EQ(size_t(0), generatorContext->trackedComputedConstantCount(analyserModel));
    EXPECT_EQ(size_t(3), generatorContext->untrackedComputedConstantCount(analyserModel));
    EXPECT_EQ(size_t(15), generatorContext->trackedVariableCount(analyserModel));
    EXPECT_EQ(size_t(3), generatorContext->untrackedVariableCount(analyserModel));

    generatorContext->trackAllComputedConstants(analyserModel);
    EXPECT_EQ_ISSUES_LEVELS_REFERENCERULES({}, {}, {}, generatorContext);

    EXPECT_EQ(size_t(3), generatorContext->trackedComputedConstantCount(analyserModel));
    EXPECT_EQ(size_t(0), generatorContext->untrackedComputedConstantCount(analyserModel));
    EXPECT_EQ(size_t(18), generatorContext->trackedVariableCount(analyserModel));
    EXPECT_EQ(size_t(0), generatorContext->untrackedVariableCount(analyserModel));
}

TEST(GeneratorContext, trackAndUntrackAllAlgebraicVariables)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("generator/hodgkin_huxley_squid_axon_model_1952/model.cellml"));
    auto analyser = libcellml::Analyser::create();

    analyser->analyseModel(model);

    auto analyserModel = analyser->analyserModel();
    auto generatorContext = libcellml::GeneratorContext::create();

    EXPECT_EQ(size_t(10), generatorContext->trackedAlgebraicVariableCount(analyserModel));
    EXPECT_EQ(size_t(0), generatorContext->untrackedAlgebraicVariableCount(analyserModel));
    EXPECT_EQ(size_t(18), generatorContext->trackedVariableCount(analyserModel));
    EXPECT_EQ(size_t(0), generatorContext->untrackedVariableCount(analyserModel));

    generatorContext->untrackAllAlgebraicVariables(analyserModel);
    EXPECT_EQ_ISSUES_LEVELS_REFERENCERULES({}, {}, {}, generatorContext);

    EXPECT_EQ(size_t(0), generatorContext->trackedAlgebraicVariableCount(analyserModel));
    EXPECT_EQ(size_t(10), generatorContext->untrackedAlgebraicVariableCount(analyserModel));
    EXPECT_EQ(size_t(8), generatorContext->trackedVariableCount(analyserModel));
    EXPECT_EQ(size_t(10), generatorContext->untrackedVariableCount(analyserModel));

    generatorContext->trackAllAlgebraicVariables(analyserModel);
    EXPECT_EQ_ISSUES_LEVELS_REFERENCERULES({}, {}, {}, generatorContext);

    EXPECT_EQ(size_t(10), generatorContext->trackedAlgebraicVariableCount(analyserModel));
    EXPECT_EQ(size_t(0), generatorContext->untrackedAlgebraicVariableCount(analyserModel));
    EXPECT_EQ(size_t(18), generatorContext->trackedVariableCount(analyserModel));
    EXPECT_EQ(size_t(0), generatorContext->untrackedVariableCount(analyserModel));
}

TEST(GeneratorContext, trackAndUntrackAllVariables)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("generator/hodgkin_huxley_squid_axon_model_1952/model.cellml"));
    auto analyser = libcellml::Analyser::create();

    analyser->analyseModel(model);

    auto analyserModel = analyser->analyserModel();
    auto generatorContext = libcellml::GeneratorContext::create();

    EXPECT_EQ(size_t(18), generatorContext->trackedVariableCount(analyserModel));
    EXPECT_EQ(size_t(0), generatorContext->untrackedVariableCount(analyserModel));

    generatorContext->untrackAllVariables(analyserModel);
    EXPECT_EQ_ISSUES_LEVELS_REFERENCERULES({}, {}, {}, generatorContext);

    EXPECT_EQ(size_t(0), generatorContext->trackedVariableCount(analyserModel));
    EXPECT_EQ(size_t(18), generatorContext->untrackedVariableCount(analyserModel));

    generatorContext->trackAllVariables(analyserModel);
    EXPECT_EQ_ISSUES_LEVELS_REFERENCERULES({}, {}, {}, generatorContext);

    EXPECT_EQ(size_t(18), generatorContext->trackedVariableCount(analyserModel));
    EXPECT_EQ(size_t(0), generatorContext->untrackedVariableCount(analyserModel));
}

enum class TrackingType
{
    CONTROL,
    VARIABLES,
    CONSTANTS,
    COMPUTED_CONSTANTS,
    ALGEBRAIC
};

void untrack(const libcellml::AnalyserModelPtr &analyserModel, const libcellml::GeneratorContextPtr &generatorContext, TrackingType trackingType)
{
    switch (trackingType) {
    case TrackingType::VARIABLES:
        generatorContext->trackAllVariables(analyserModel); // For coverage.
        generatorContext->untrackAllVariables(analyserModel);

        break;
    case TrackingType::CONSTANTS:
        generatorContext->untrackAllConstants(analyserModel);

        break;
    case TrackingType::COMPUTED_CONSTANTS:
        generatorContext->untrackAllComputedConstants(analyserModel);

        break;
    case TrackingType::ALGEBRAIC:
        generatorContext->untrackAllAlgebraicVariables(analyserModel);

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
    auto generatorContext = libcellml::GeneratorContext::create();
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

    generator->setContext(generatorContext);

    analyser->analyseModel(model);

    auto analyserModel = analyser->analyserModel();

    untrack(analyserModel, generatorContext, trackingType);

    EXPECT_EQ_ISSUES_LEVELS_REFERENCERULES(issues, levels, referenceRules, generatorContext);

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

    analyserModel = analyser->analyserModel();

    untrack(analyserModel, generatorContext, trackingType);

    EXPECT_EQ_ISSUES_LEVELS_REFERENCERULES(externalIssues, externalLevels, externalReferenceRules, generatorContext);

    profile = libcellml::GeneratorProfile::create(libcellml::GeneratorProfile::Profile::C);

    generator->setProfile(profile);

    profile->setInterfaceFileNameString(modelType + "." + variableType + ".with.externals.h");

    EXPECT_EQ_FILE_CONTENTS("generator/hodgkin_huxley_squid_axon_model_1952/" + modelType + "." + variableType + ".with.externals.h", generator->interfaceCode(analyserModel));
    EXPECT_EQ_FILE_CONTENTS("generator/hodgkin_huxley_squid_axon_model_1952/" + modelType + "." + variableType + ".with.externals.c", generator->implementationCode(analyserModel));

    profile = libcellml::GeneratorProfile::create(libcellml::GeneratorProfile::Profile::PYTHON);

    generator->setProfile(profile);

    EXPECT_EQ_FILE_CONTENTS("generator/hodgkin_huxley_squid_axon_model_1952/" + modelType + "." + variableType + ".with.externals.py", generator->implementationCode(analyserModel));
}

TEST(GeneratorContext, hodgkinHuxleySquidAxonModel1952Control)
{
    hodgkinHuxleySquidAxonModel1952CodeGeneration(true, TrackingType::CONSTANTS,
                                                  {}, {}, {},
                                                  {"Variable 'Cm' in component 'membrane' is needed to compute an external variable and cannot therefore be untracked."},
                                                  {libcellml::Issue::Level::ERROR},
                                                  {libcellml::Issue::ReferenceRule::GENERATOR_EXTERNALLY_NEEDED_VARIABLE_NOT_UNTRACKABLE});
}

TEST(GeneratorContext, hodgkinHuxleySquidAxonModel1952UntrackedConstants)
{
    hodgkinHuxleySquidAxonModel1952CodeGeneration(true, TrackingType::CONSTANTS,
                                                  {}, {}, {},
                                                  {"Variable 'Cm' in component 'membrane' is needed to compute an external variable and cannot therefore be untracked."},
                                                  {libcellml::Issue::Level::ERROR},
                                                  {libcellml::Issue::ReferenceRule::GENERATOR_EXTERNALLY_NEEDED_VARIABLE_NOT_UNTRACKABLE});
}

TEST(GeneratorContext, hodgkinHuxleySquidAxonModel1952UntrackedComputedConstants)
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

TEST(GeneratorContext, hodgkinHuxleySquidAxonModel1952UntrackedAlgebraicVariables)
{
    hodgkinHuxleySquidAxonModel1952CodeGeneration(true, TrackingType::ALGEBRAIC,
                                                  {}, {}, {},
                                                  {"Variable 'alpha_m' in component 'sodium_channel_m_gate' is needed to compute an external variable and cannot therefore be untracked."},
                                                  {libcellml::Issue::Level::ERROR},
                                                  {libcellml::Issue::ReferenceRule::GENERATOR_EXTERNALLY_NEEDED_VARIABLE_NOT_UNTRACKABLE});
}

TEST(GeneratorContext, hodgkinHuxleySquidAxonModel1952UntrackedVariables)
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

TEST(GeneratorContext, hodgkinHuxleySquidAxonModel1952DaeControl)
{
    hodgkinHuxleySquidAxonModel1952CodeGeneration(false, TrackingType::CONTROL,
                                                  {}, {}, {},
                                                  {}, {}, {});
}

TEST(GeneratorContext, hodgkinHuxleySquidAxonModel1952DaeUntrackedConstants)
{
    hodgkinHuxleySquidAxonModel1952CodeGeneration(false, TrackingType::CONSTANTS,
                                                  {}, {}, {},
                                                  {"Variable 'Cm' in component 'membrane' is needed to compute an external variable and cannot therefore be untracked."},
                                                  {libcellml::Issue::Level::ERROR},
                                                  {libcellml::Issue::ReferenceRule::GENERATOR_EXTERNALLY_NEEDED_VARIABLE_NOT_UNTRACKABLE});
}

TEST(GeneratorContext, hodgkinHuxleySquidAxonModel1952DaeUntrackedComputedConstants)
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

TEST(GeneratorContext, hodgkinHuxleySquidAxonModel1952DaeUntrackedAlgebraicVariables)
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

TEST(GeneratorContext, hodgkinHuxleySquidAxonModel1952DaeUntrackedVariables)
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

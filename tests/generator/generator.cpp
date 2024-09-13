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

#ifdef _WIN32
#    define _USE_MATH_DEFINES
#endif

#include "test_utils.h"

#include "gtest/gtest.h"

#include <chrono>
#include <cmath>
#include <fstream>
#include <iostream>
#include <libcellml>

#include "libcellml/undefines.h"

static const std::string EMPTY_STRING;
static const std::vector<double> NO_VALUES;
static const auto NAN = std::numeric_limits<double>::quiet_NaN();
static const auto NAN_x_2 = std::vector<double>(2, NAN);
static const auto NAN_x_3 = std::vector<double>(3, NAN);
static const auto NAN_x_4 = std::vector<double>(4, NAN);

#if defined(_MSC_VER) && !defined(__clang__)
#    pragma warning(push)
#    pragma warning(disable : 4100)
#elif defined(__GNUC__) && !defined(__clang__)
#    pragma GCC diagnostic push
#    pragma GCC diagnostic ignored "-Wunused-parameter"
#else
#    pragma clang diagnostic push
#    pragma clang diagnostic ignored "-Wunused-parameter"
#endif

namespace fabbri_fantini_wilders_severi_human_san_model_2017 {
#include "../resources/generator/fabbri_fantini_wilders_severi_human_san_model_2017/model.c"
} // namespace fabbri_fantini_wilders_severi_human_san_model_2017

namespace garny_kohl_hunter_boyett_noble_rabbit_san_model_2003 {
#include "../resources/generator/garny_kohl_hunter_boyett_noble_rabbit_san_model_2003/model.c"
} // namespace garny_kohl_hunter_boyett_noble_rabbit_san_model_2003

#if defined(_MSC_VER) && !defined(__clang__)
#    pragma warning(pop)
#elif defined(__GNUC__) && !defined(__clang__)
#    pragma GCC diagnostic pop
#else
#    pragma clang diagnostic pop
#endif

#define INITIALISE_INTERPRETED_ALGEBRAIC_MODEL(analyserModel) \
    double *expectedStatesData = nullptr; \
    double *expectedRatesData = nullptr; \
    double *expectedConstantsData = nullptr; \
    double *expectedComputedConstantsData = nullptr; \
    double *expectedAlgebraicData = nullptr; \
    double *states = nullptr; \
    double *rates = nullptr; \
    auto *constants = new double[analyserModel->constantCount()]; \
    auto *computedConstants = new double[analyserModel->computedConstantCount()]; \
    auto *algebraic = new double[analyserModel->algebraicCount()]; \
\
    (void)expectedStatesData; \
    (void)expectedRatesData; \
    (void)expectedConstantsData; \
    (void)expectedComputedConstantsData; \
    (void)expectedAlgebraicData; \
    interpreter->initialiseVariablesForAlgebraicModel(constants, computedConstants, algebraic); \
    interpreter->computeComputedConstants(constants, computedConstants); \
    interpreter->computeVariablesForAlgebraicModel(constants, computedConstants, algebraic);

#define INITIALISE_INTERPRETED_DIFFERENTIAL_MODEL(analyserModel) \
    double *expectedStatesData = nullptr; \
    double *expectedRatesData = nullptr; \
    double *expectedConstantsData = nullptr; \
    double *expectedComputedConstantsData = nullptr; \
    double *expectedAlgebraicData = nullptr; \
    auto *states = new double[analyserModel->stateCount()]; \
    auto *rates = new double[analyserModel->stateCount()]; \
    auto *constants = new double[analyserModel->constantCount()]; \
    auto *computedConstants = new double[analyserModel->computedConstantCount()]; \
    auto *algebraic = new double[analyserModel->algebraicCount()]; \
\
    (void)expectedStatesData; \
    (void)expectedRatesData; \
    (void)expectedConstantsData; \
    (void)expectedComputedConstantsData; \
    (void)expectedAlgebraicData; \
    interpreter->initialiseVariablesForDifferentialModel(states, rates, constants, computedConstants, algebraic); \
    interpreter->computeComputedConstants(constants, computedConstants); \
    interpreter->computeRates(0.0, states, rates, constants, computedConstants, algebraic); \
    interpreter->computeVariablesForDifferentialModel(0.0, states, rates, constants, computedConstants, algebraic);

#define INITIALISE_COMPILED_MODEL(model) \
    expectedStatesData = model::createStatesArray(); \
    expectedRatesData = model::createStatesArray(); \
    expectedConstantsData = model::createConstantsArray(); \
    expectedComputedConstantsData = model::createComputedConstantsArray(); \
    expectedAlgebraicData = model::createAlgebraicArray(); \
\
    model::initialiseVariables(expectedStatesData, expectedRatesData, expectedConstantsData, expectedComputedConstantsData, expectedAlgebraicData); \
    model::computeComputedConstants(expectedConstantsData, expectedComputedConstantsData); \
    model::computeRates(0.0, expectedStatesData, expectedRatesData, expectedConstantsData, expectedComputedConstantsData, expectedAlgebraicData); \
    model::computeVariables(0.0, expectedStatesData, expectedRatesData, expectedConstantsData, expectedComputedConstantsData, expectedAlgebraicData); \
\
    std::vector<double> expectedStates(expectedStatesData, expectedStatesData + model::STATE_COUNT); \
    std::vector<double> expectedRates(expectedRatesData, expectedRatesData + model::STATE_COUNT); \
    std::vector<double> expectedConstants(expectedConstantsData, expectedConstantsData + model::CONSTANT_COUNT); \
    std::vector<double> expectedComputedConstants(expectedComputedConstantsData, expectedComputedConstantsData + model::COMPUTED_CONSTANT_COUNT); \
    std::vector<double> expectedAlgebraic(expectedAlgebraicData, expectedAlgebraicData + model::ALGEBRAIC_COUNT);

#define FINALISE_MODEL() \
    delete[] expectedStatesData; \
    delete[] expectedRatesData; \
    delete[] expectedConstantsData; \
    delete[] expectedComputedConstantsData; \
    delete[] expectedAlgebraicData; \
    delete[] states; \
    delete[] rates; \
    delete[] constants; \
    delete[] computedConstants; \
    delete[] algebraic;

#define STRINGIFY(x) #x

TEST(Generator, emptyModel)
{
    libcellml::ModelPtr model = libcellml::Model::create("empty_model");
    libcellml::AnalyserPtr analyser = libcellml::Analyser::create();

    analyser->analyseModel(model);

    EXPECT_EQ(size_t(0), analyser->errorCount());

    auto analyserModel = analyser->model();
    auto generator = libcellml::Generator::create();

    generator->setModel(analyserModel);

    EXPECT_EQ(EMPTY_STRING, generator->interfaceCode());
    EXPECT_EQ(EMPTY_STRING, generator->implementationCode());
}

TEST(Generator, algebraicEqnComputedVarOnRhs)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("generator/algebraic_eqn_computed_var_on_rhs/model.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    auto analyser = libcellml::Analyser::create();

    analyser->analyseModel(model);

    EXPECT_EQ(size_t(0), analyser->errorCount());

    auto analyserModel = analyser->model();
    auto generator = libcellml::Generator::create();

    generator->setModel(analyserModel);

    EXPECT_EQ_FILE_CONTENTS("generator/algebraic_eqn_computed_var_on_rhs/model.h", generator->interfaceCode());
    EXPECT_EQ_FILE_CONTENTS("generator/algebraic_eqn_computed_var_on_rhs/model.c", generator->implementationCode());

    auto profile = libcellml::GeneratorProfile::create(libcellml::GeneratorProfile::Profile::PYTHON);

    generator->setProfile(profile);

    EXPECT_EQ_FILE_CONTENTS("generator/algebraic_eqn_computed_var_on_rhs/model.py", generator->implementationCode());

    auto interpreter = libcellml::Interpreter::create();

    interpreter->setModel(analyserModel);

    INITIALISE_INTERPRETED_ALGEBRAIC_MODEL(analyserModel);

    EXPECT_EQ_VALUES(std::vector<double>({1.0, 1.0}), constants, analyserModel->constantCount());
    EXPECT_EQ_VALUES(std::vector<double>({1.0, 1.0}), computedConstants, analyserModel->computedConstantCount());
    EXPECT_EQ_VALUES(std::vector<double>({1.0, 1.0}), algebraic, analyserModel->algebraicCount());

    FINALISE_MODEL();
}

TEST(Generator, algebraicEqnComputedVarOnRhsWithComputedConstantAsExternalVariable)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("generator/algebraic_eqn_computed_var_on_rhs/model.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    auto analyser = libcellml::Analyser::create();

    analyser->addExternalVariable(libcellml::AnalyserExternalVariable::create(model->component("my_algebraic_eqn")->variable("a")));

    analyser->analyseModel(model);

    EXPECT_EQ(size_t(0), analyser->errorCount());

    auto analyserModel = analyser->model();
    auto generator = libcellml::Generator::create();

    generator->setModel(analyserModel);

    auto profile = generator->profile();

    profile->setInterfaceFileNameString("model.external.h");

    EXPECT_EQ_FILE_CONTENTS("generator/algebraic_eqn_computed_var_on_rhs/model.external.h", generator->interfaceCode());
    EXPECT_EQ_FILE_CONTENTS("generator/algebraic_eqn_computed_var_on_rhs/model.external.c", generator->implementationCode());

    profile = libcellml::GeneratorProfile::create(libcellml::GeneratorProfile::Profile::PYTHON);

    generator->setProfile(profile);

    EXPECT_EQ_FILE_CONTENTS("generator/algebraic_eqn_computed_var_on_rhs/model.external.py", generator->implementationCode());

    auto interpreter = libcellml::Interpreter::create();

    interpreter->setModel(analyserModel);

    INITIALISE_INTERPRETED_ALGEBRAIC_MODEL(analyserModel);

    EXPECT_EQ_VALUES(NAN_x_2, constants, analyserModel->constantCount());
    EXPECT_EQ_VALUES(NAN_x_2, computedConstants, analyserModel->computedConstantCount());
    EXPECT_EQ_VALUES(NAN_x_2, algebraic, analyserModel->algebraicCount());

    FINALISE_MODEL();
}

TEST(Generator, algebraicEqnConstVarOnRhs)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("generator/algebraic_eqn_const_var_on_rhs/model.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    auto analyser = libcellml::Analyser::create();

    analyser->analyseModel(model);

    EXPECT_EQ(size_t(0), analyser->errorCount());

    auto analyserModel = analyser->model();
    auto generator = libcellml::Generator::create();

    generator->setModel(analyserModel);

    EXPECT_EQ_FILE_CONTENTS("generator/algebraic_eqn_const_var_on_rhs/model.h", generator->interfaceCode());
    EXPECT_EQ_FILE_CONTENTS("generator/algebraic_eqn_const_var_on_rhs/model.c", generator->implementationCode());

    auto profile = libcellml::GeneratorProfile::create(libcellml::GeneratorProfile::Profile::PYTHON);

    generator->setProfile(profile);

    EXPECT_EQ_FILE_CONTENTS("generator/algebraic_eqn_const_var_on_rhs/model.py", generator->implementationCode());

    auto interpreter = libcellml::Interpreter::create();

    interpreter->setModel(analyserModel);

    INITIALISE_INTERPRETED_ALGEBRAIC_MODEL(analyserModel);

    EXPECT_EQ_VALUES(std::vector<double>({1.0, 1.0}), constants, analyserModel->constantCount());
    EXPECT_EQ_VALUES(std::vector<double>({1.0, 1.0}), computedConstants, analyserModel->computedConstantCount());
    EXPECT_EQ_VALUES(std::vector<double>({1.0, 1.0}), algebraic, analyserModel->algebraicCount());

    FINALISE_MODEL();
}

TEST(Generator, algebraicEqnConstantOnRhs)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("generator/algebraic_eqn_constant_on_rhs/model.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    auto analyser = libcellml::Analyser::create();

    analyser->analyseModel(model);

    EXPECT_EQ(size_t(0), analyser->errorCount());

    auto analyserModel = analyser->model();
    auto generator = libcellml::Generator::create();

    generator->setModel(analyserModel);

    EXPECT_EQ_FILE_CONTENTS("generator/algebraic_eqn_constant_on_rhs/model.h", generator->interfaceCode());
    EXPECT_EQ_FILE_CONTENTS("generator/algebraic_eqn_constant_on_rhs/model.c", generator->implementationCode());

    auto profile = libcellml::GeneratorProfile::create(libcellml::GeneratorProfile::Profile::PYTHON);

    generator->setProfile(profile);

    EXPECT_EQ_FILE_CONTENTS("generator/algebraic_eqn_constant_on_rhs/model.py", generator->implementationCode());

    auto interpreter = libcellml::Interpreter::create();

    interpreter->setModel(analyserModel);

    INITIALISE_INTERPRETED_ALGEBRAIC_MODEL(analyserModel);

    EXPECT_EQ_VALUES(std::vector<double>({1.0}), constants, analyserModel->constantCount());
    EXPECT_EQ_VALUES(std::vector<double>({1.0}), computedConstants, analyserModel->computedConstantCount());
    EXPECT_EQ_VALUES(std::vector<double>({1.0}), algebraic, analyserModel->algebraicCount());

    FINALISE_MODEL();
}

TEST(Generator, algebraicEqnDerivativeOnRhs)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("generator/algebraic_eqn_derivative_on_rhs/model.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    auto analyser = libcellml::Analyser::create();

    analyser->analyseModel(model);

    EXPECT_EQ(size_t(0), analyser->errorCount());

    auto analyserModel = analyser->model();
    auto generator = libcellml::Generator::create();

    generator->setModel(analyserModel);

    EXPECT_EQ_FILE_CONTENTS("generator/algebraic_eqn_derivative_on_rhs/model.h", generator->interfaceCode());
    EXPECT_EQ_FILE_CONTENTS("generator/algebraic_eqn_derivative_on_rhs/model.c", generator->implementationCode());

    auto profile = libcellml::GeneratorProfile::create(libcellml::GeneratorProfile::Profile::PYTHON);

    generator->setProfile(profile);

    EXPECT_EQ_FILE_CONTENTS("generator/algebraic_eqn_derivative_on_rhs/model.py", generator->implementationCode());

    auto interpreter = libcellml::Interpreter::create();

    interpreter->setModel(analyserModel);

    INITIALISE_INTERPRETED_DIFFERENTIAL_MODEL(analyserModel);

    EXPECT_EQ_VALUES(std::vector<double>({1.0}), states, analyserModel->stateCount());
    EXPECT_EQ_VALUES(std::vector<double>({1.0}), rates, analyserModel->stateCount());
    EXPECT_EQ_VALUES(std::vector<double>({1.0, 1.0}), constants, analyserModel->constantCount());
    EXPECT_EQ_VALUES(std::vector<double>({1.0, 1.0}), computedConstants, analyserModel->computedConstantCount());
    EXPECT_EQ_VALUES(std::vector<double>({1.0, 1.0}), algebraic, analyserModel->algebraicCount());

    FINALISE_MODEL();
}

TEST(Generator, algebraicEqnDerivativeOnRhsOneComponent)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("generator/algebraic_eqn_derivative_on_rhs_one_component/model.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    auto analyser = libcellml::Analyser::create();

    analyser->analyseModel(model);

    EXPECT_EQ(size_t(0), analyser->errorCount());

    auto analyserModel = analyser->model();
    auto generator = libcellml::Generator::create();

    generator->setModel(analyserModel);

    EXPECT_EQ_FILE_CONTENTS("generator/algebraic_eqn_derivative_on_rhs_one_component/model.h", generator->interfaceCode());
    EXPECT_EQ_FILE_CONTENTS("generator/algebraic_eqn_derivative_on_rhs_one_component/model.c", generator->implementationCode());

    auto profile = libcellml::GeneratorProfile::create(libcellml::GeneratorProfile::Profile::PYTHON);

    generator->setProfile(profile);

    EXPECT_EQ_FILE_CONTENTS("generator/algebraic_eqn_derivative_on_rhs_one_component/model.py", generator->implementationCode());

    auto interpreter = libcellml::Interpreter::create();

    interpreter->setModel(analyserModel);

    INITIALISE_INTERPRETED_DIFFERENTIAL_MODEL(analyserModel);

    EXPECT_EQ_VALUES(std::vector<double>({1.0}), states, analyserModel->stateCount());
    EXPECT_EQ_VALUES(std::vector<double>({1.0}), rates, analyserModel->stateCount());
    EXPECT_EQ_VALUES(std::vector<double>({1.0, 1.0}), constants, analyserModel->constantCount());
    EXPECT_EQ_VALUES(std::vector<double>({1.0, 1.0}), computedConstants, analyserModel->computedConstantCount());
    EXPECT_EQ_VALUES(std::vector<double>({1.0, 1.0}), algebraic, analyserModel->algebraicCount());

    FINALISE_MODEL();
}

TEST(Generator, algebraicEqnStateVarOnRhs)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("generator/algebraic_eqn_state_var_on_rhs/model.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    auto analyser = libcellml::Analyser::create();

    analyser->analyseModel(model);

    EXPECT_EQ(size_t(0), analyser->errorCount());

    auto analyserModel = analyser->model();
    auto generator = libcellml::Generator::create();

    generator->setModel(analyserModel);

    EXPECT_EQ_FILE_CONTENTS("generator/algebraic_eqn_state_var_on_rhs/model.h", generator->interfaceCode());
    EXPECT_EQ_FILE_CONTENTS("generator/algebraic_eqn_state_var_on_rhs/model.c", generator->implementationCode());

    auto profile = libcellml::GeneratorProfile::create(libcellml::GeneratorProfile::Profile::PYTHON);

    generator->setProfile(profile);

    EXPECT_EQ_FILE_CONTENTS("generator/algebraic_eqn_state_var_on_rhs/model.py", generator->implementationCode());

    auto interpreter = libcellml::Interpreter::create();

    interpreter->setModel(analyserModel);

    INITIALISE_INTERPRETED_DIFFERENTIAL_MODEL(analyserModel);

    EXPECT_EQ_VALUES(std::vector<double>({1.0}), states, analyserModel->stateCount());
    EXPECT_EQ_VALUES(std::vector<double>({1.0}), rates, analyserModel->stateCount());
    EXPECT_EQ_VALUES(std::vector<double>({1.0, 2.0}), constants, analyserModel->constantCount());
    EXPECT_EQ_VALUES(std::vector<double>({1.0, 2.0}), computedConstants, analyserModel->computedConstantCount());
    EXPECT_EQ_VALUES(std::vector<double>({1.0, 2.0}), algebraic, analyserModel->algebraicCount());

    FINALISE_MODEL();
}

TEST(Generator, algebraicEqnStateVarOnRhsOneComponent)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("generator/algebraic_eqn_state_var_on_rhs_one_component/model.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    auto analyser = libcellml::Analyser::create();

    analyser->analyseModel(model);

    EXPECT_EQ(size_t(0), analyser->errorCount());

    auto analyserModel = analyser->model();
    auto generator = libcellml::Generator::create();

    generator->setModel(analyserModel);

    EXPECT_EQ_FILE_CONTENTS("generator/algebraic_eqn_state_var_on_rhs_one_component/model.h", generator->interfaceCode());
    EXPECT_EQ_FILE_CONTENTS("generator/algebraic_eqn_state_var_on_rhs_one_component/model.c", generator->implementationCode());

    auto profile = libcellml::GeneratorProfile::create(libcellml::GeneratorProfile::Profile::PYTHON);

    generator->setProfile(profile);

    EXPECT_EQ_FILE_CONTENTS("generator/algebraic_eqn_state_var_on_rhs_one_component/model.py", generator->implementationCode());

    auto interpreter = libcellml::Interpreter::create();

    interpreter->setModel(analyserModel);

    INITIALISE_INTERPRETED_DIFFERENTIAL_MODEL(analyserModel);

    EXPECT_EQ_VALUES(std::vector<double>({1.0}), states, analyserModel->stateCount());
    EXPECT_EQ_VALUES(std::vector<double>({1.0}), rates, analyserModel->stateCount());
    EXPECT_EQ_VALUES(std::vector<double>({1.0, 2.0}), constants, analyserModel->constantCount());
    EXPECT_EQ_VALUES(std::vector<double>({1.0, 2.0}), computedConstants, analyserModel->computedConstantCount());
    EXPECT_EQ_VALUES(std::vector<double>({1.0, 2.0}), algebraic, analyserModel->algebraicCount());

    FINALISE_MODEL();
}

TEST(Generator, algebraicUnknownVarOnRhs)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("generator/algebraic_unknown_var_on_rhs/model.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    auto analyser = libcellml::Analyser::create();

    analyser->analyseModel(model);

    EXPECT_EQ(size_t(0), analyser->errorCount());

    auto analyserModel = analyser->model();
    auto generator = libcellml::Generator::create();

    generator->setModel(analyserModel);

    EXPECT_EQ_FILE_CONTENTS("generator/algebraic_unknown_var_on_rhs/model.h", generator->interfaceCode());
    EXPECT_EQ_FILE_CONTENTS("generator/algebraic_unknown_var_on_rhs/model.c", generator->implementationCode());

    auto profile = libcellml::GeneratorProfile::create(libcellml::GeneratorProfile::Profile::PYTHON);

    generator->setProfile(profile);

    EXPECT_EQ_FILE_CONTENTS("generator/algebraic_unknown_var_on_rhs/model.py", generator->implementationCode());

    auto interpreter = libcellml::Interpreter::create();

    interpreter->setModel(analyserModel);

    INITIALISE_INTERPRETED_ALGEBRAIC_MODEL(analyserModel);

    EXPECT_EQ_VALUES(std::vector<double>({1.0, 1.0}), constants, analyserModel->constantCount());
    EXPECT_EQ_VALUES(std::vector<double>({1.0, 1.0}), computedConstants, analyserModel->computedConstantCount());
    EXPECT_EQ_VALUES(std::vector<double>({1.0, 1.0}), algebraic, analyserModel->algebraicCount());

    FINALISE_MODEL();
}

TEST(Generator, algebraicEqnWithOneNonIsolatedUnknown)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("generator/algebraic_eqn_with_one_non_isolated_unknown/model.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    auto analyser = libcellml::Analyser::create();

    analyser->analyseModel(model);

    EXPECT_EQ(size_t(0), analyser->errorCount());

    auto analyserModel = analyser->model();
    auto generator = libcellml::Generator::create();

    generator->setModel(analyserModel);

    EXPECT_EQ_FILE_CONTENTS("generator/algebraic_eqn_with_one_non_isolated_unknown/model.h", generator->interfaceCode());
    EXPECT_EQ_FILE_CONTENTS("generator/algebraic_eqn_with_one_non_isolated_unknown/model.c", generator->implementationCode());

    auto profile = libcellml::GeneratorProfile::create(libcellml::GeneratorProfile::Profile::PYTHON);

    generator->setProfile(profile);

    EXPECT_EQ_FILE_CONTENTS("generator/algebraic_eqn_with_one_non_isolated_unknown/model.py", generator->implementationCode());

    auto interpreter = libcellml::Interpreter::create();

    interpreter->setModel(analyserModel);

    INITIALISE_INTERPRETED_ALGEBRAIC_MODEL(analyserModel);

    EXPECT_EQ_VALUES(std::vector<double>({3.0, 5.0, 7.0, 1.0}), constants, analyserModel->constantCount());
    EXPECT_EQ_VALUES(std::vector<double>({3.0, 5.0, 7.0, 1.0}), computedConstants, analyserModel->computedConstantCount());
    EXPECT_EQ_VALUES(std::vector<double>({3.0, 5.0, 7.0, 1.0}), algebraic, analyserModel->algebraicCount());

    FINALISE_MODEL();
}

TEST(Generator, algebraicEqnWithOneNonIsolatedUnknownWithExternalVariable)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("generator/algebraic_eqn_with_one_non_isolated_unknown/model.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    auto analyser = libcellml::Analyser::create();

    analyser->addExternalVariable(libcellml::AnalyserExternalVariable::create(model->component("my_algebraic_eqn")->variable("c")));

    analyser->analyseModel(model);

    EXPECT_EQ(size_t(0), analyser->errorCount());

    auto analyserModel = analyser->model();
    auto generator = libcellml::Generator::create();

    generator->setModel(analyserModel);

    auto profile = generator->profile();

    profile->setInterfaceFileNameString("model.external.h");

    EXPECT_EQ_FILE_CONTENTS("generator/algebraic_eqn_with_one_non_isolated_unknown/model.external.h", generator->interfaceCode());
    EXPECT_EQ_FILE_CONTENTS("generator/algebraic_eqn_with_one_non_isolated_unknown/model.external.c", generator->implementationCode());

    profile = libcellml::GeneratorProfile::create(libcellml::GeneratorProfile::Profile::PYTHON);

    generator->setProfile(profile);

    EXPECT_EQ_FILE_CONTENTS("generator/algebraic_eqn_with_one_non_isolated_unknown/model.external.py", generator->implementationCode());

    auto interpreter = libcellml::Interpreter::create();

    interpreter->setModel(analyserModel);

    INITIALISE_INTERPRETED_ALGEBRAIC_MODEL(analyserModel);

    EXPECT_EQ_VALUES(std::vector<double>({3.0, 5.0, 7.0, NAN}), constants, analyserModel->constantCount());
    EXPECT_EQ_VALUES(std::vector<double>({3.0, 5.0, 7.0, NAN}), computedConstants, analyserModel->computedConstantCount());
    EXPECT_EQ_VALUES(std::vector<double>({3.0, 5.0, 7.0, NAN}), algebraic, analyserModel->algebraicCount());

    FINALISE_MODEL();
}

TEST(Generator, algebraicSystemWithThreeLinkedUnknowns)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("generator/algebraic_system_with_three_linked_unknowns/model.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    auto analyser = libcellml::Analyser::create();

    analyser->analyseModel(model);

    EXPECT_EQ(size_t(0), analyser->errorCount());

    auto analyserModel = analyser->model();
    auto generator = libcellml::Generator::create();

    generator->setModel(analyserModel);

    EXPECT_EQ_FILE_CONTENTS("generator/algebraic_system_with_three_linked_unknowns/model.h", generator->interfaceCode());
    EXPECT_EQ_FILE_CONTENTS("generator/algebraic_system_with_three_linked_unknowns/model.c", generator->implementationCode());

    auto profile = libcellml::GeneratorProfile::create(libcellml::GeneratorProfile::Profile::PYTHON);

    generator->setProfile(profile);

    EXPECT_EQ_FILE_CONTENTS("generator/algebraic_system_with_three_linked_unknowns/model.py", generator->implementationCode());

    auto interpreter = libcellml::Interpreter::create();

    interpreter->setModel(analyserModel);

    INITIALISE_INTERPRETED_ALGEBRAIC_MODEL(analyserModel);

    EXPECT_EQ_VALUES(std::vector<double>({1.0, 1.0, 1.0}), constants, analyserModel->constantCount());
    EXPECT_EQ_VALUES(std::vector<double>({1.0, 1.0, 1.0}), computedConstants, analyserModel->computedConstantCount());
    EXPECT_EQ_VALUES(std::vector<double>({1.0, 1.0, 1.0}), algebraic, analyserModel->algebraicCount());

    FINALISE_MODEL();
}

TEST(Generator, algebraicSystemWithThreeLinkedUnknownsWithThreeExternalVariables)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("generator/algebraic_system_with_three_linked_unknowns/model.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    auto analyser = libcellml::Analyser::create();

    analyser->addExternalVariable(libcellml::AnalyserExternalVariable::create(model->component("my_algebraic_system")->variable("x")));
    analyser->addExternalVariable(libcellml::AnalyserExternalVariable::create(model->component("my_algebraic_system")->variable("y")));
    analyser->addExternalVariable(libcellml::AnalyserExternalVariable::create(model->component("my_algebraic_system")->variable("z")));

    analyser->analyseModel(model);

    EXPECT_EQ(size_t(0), analyser->errorCount());

    auto analyserModel = analyser->model();
    auto generator = libcellml::Generator::create();

    generator->setModel(analyserModel);

    auto profile = generator->profile();

    profile->setInterfaceFileNameString("model.external.h");

    EXPECT_EQ_FILE_CONTENTS("generator/algebraic_system_with_three_linked_unknowns/model.external.h", generator->interfaceCode());
    EXPECT_EQ_FILE_CONTENTS("generator/algebraic_system_with_three_linked_unknowns/model.external.c", generator->implementationCode());

    profile = libcellml::GeneratorProfile::create(libcellml::GeneratorProfile::Profile::PYTHON);

    generator->setProfile(profile);

    EXPECT_EQ_FILE_CONTENTS("generator/algebraic_system_with_three_linked_unknowns/model.external.py", generator->implementationCode());

    auto interpreter = libcellml::Interpreter::create();

    interpreter->setModel(analyserModel);

    INITIALISE_INTERPRETED_ALGEBRAIC_MODEL(analyserModel);

    EXPECT_EQ_VALUES(NAN_x_3, constants, analyserModel->constantCount());
    EXPECT_EQ_VALUES(NAN_x_3, computedConstants, analyserModel->computedConstantCount());
    EXPECT_EQ_VALUES(NAN_x_3, algebraic, analyserModel->algebraicCount());

    FINALISE_MODEL();
}

TEST(Generator, algebraicSystemWithVariousDependenciesOrdered)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("generator/algebraic_system_with_various_dependencies/model.ordered.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    auto analyser = libcellml::Analyser::create();

    analyser->analyseModel(model);

    EXPECT_EQ(size_t(0), analyser->errorCount());

    auto analyserModel = analyser->model();
    auto generator = libcellml::Generator::create();

    generator->setModel(analyserModel);

    auto profile = generator->profile();

    profile->setInterfaceFileNameString("model.ordered.h");

    EXPECT_EQ_FILE_CONTENTS("generator/algebraic_system_with_various_dependencies/model.ordered.h", generator->interfaceCode());
    EXPECT_EQ_FILE_CONTENTS("generator/algebraic_system_with_various_dependencies/model.ordered.c", generator->implementationCode());

    profile = libcellml::GeneratorProfile::create(libcellml::GeneratorProfile::Profile::PYTHON);

    generator->setProfile(profile);

    EXPECT_EQ_FILE_CONTENTS("generator/algebraic_system_with_various_dependencies/model.ordered.py", generator->implementationCode());

    auto interpreter = libcellml::Interpreter::create();

    interpreter->setModel(analyserModel);

    INITIALISE_INTERPRETED_ALGEBRAIC_MODEL(analyserModel);

    EXPECT_EQ_VALUES(std::vector<double>({14.0, 3.0, 5.0, 1.0, 1.0, 2.0}), constants, analyserModel->constantCount());
    EXPECT_EQ_VALUES(std::vector<double>({14.0, 3.0, 5.0, 1.0, 1.0, 2.0}), computedConstants, analyserModel->computedConstantCount());
    EXPECT_EQ_VALUES(std::vector<double>({14.0, 3.0, 5.0, 1.0, 1.0, 2.0}), algebraic, analyserModel->algebraicCount());

    FINALISE_MODEL();
}

TEST(Generator, algebraicSystemWithVariousDependenciesNotOrdered)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("generator/algebraic_system_with_various_dependencies/model.not.ordered.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    auto analyser = libcellml::Analyser::create();

    analyser->analyseModel(model);

    EXPECT_EQ(size_t(0), analyser->errorCount());

    auto analyserModel = analyser->model();
    auto generator = libcellml::Generator::create();

    generator->setModel(analyserModel);

    auto profile = generator->profile();

    profile->setInterfaceFileNameString("model.not.ordered.h");

    EXPECT_EQ_FILE_CONTENTS("generator/algebraic_system_with_various_dependencies/model.not.ordered.h", generator->interfaceCode());
    EXPECT_EQ_FILE_CONTENTS("generator/algebraic_system_with_various_dependencies/model.not.ordered.c", generator->implementationCode());

    profile = libcellml::GeneratorProfile::create(libcellml::GeneratorProfile::Profile::PYTHON);

    generator->setProfile(profile);

    EXPECT_EQ_FILE_CONTENTS("generator/algebraic_system_with_various_dependencies/model.not.ordered.py", generator->implementationCode());

    auto interpreter = libcellml::Interpreter::create();

    interpreter->setModel(analyserModel);

    INITIALISE_INTERPRETED_ALGEBRAIC_MODEL(analyserModel);

    EXPECT_EQ_VALUES(std::vector<double>({2.0, 1.0, 1.0, 14.0, 3.0, 5.0}), constants, analyserModel->constantCount());
    EXPECT_EQ_VALUES(std::vector<double>({2.0, 1.0, 1.0, 14.0, 3.0, 5.0}), computedConstants, analyserModel->computedConstantCount());
    EXPECT_EQ_VALUES(std::vector<double>({2.0, 1.0, 1.0, 14.0, 3.0, 5.0}), algebraic, analyserModel->algebraicCount());

    FINALISE_MODEL();
}

TEST(Generator, odeComputedVarOnRhs)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("generator/ode_computed_var_on_rhs/model.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    auto analyser = libcellml::Analyser::create();

    analyser->analyseModel(model);

    EXPECT_EQ(size_t(0), analyser->errorCount());

    auto analyserModel = analyser->model();
    auto generator = libcellml::Generator::create();

    generator->setModel(analyserModel);

    EXPECT_EQ_FILE_CONTENTS("generator/ode_computed_var_on_rhs/model.h", generator->interfaceCode());
    EXPECT_EQ_FILE_CONTENTS("generator/ode_computed_var_on_rhs/model.c", generator->implementationCode());

    auto profile = libcellml::GeneratorProfile::create(libcellml::GeneratorProfile::Profile::PYTHON);

    generator->setProfile(profile);

    EXPECT_EQ_FILE_CONTENTS("generator/ode_computed_var_on_rhs/model.py", generator->implementationCode());

    auto interpreter = libcellml::Interpreter::create();

    interpreter->setModel(analyserModel);

    INITIALISE_INTERPRETED_DIFFERENTIAL_MODEL(analyserModel);

    EXPECT_EQ_VALUES(std::vector<double>({1.0}), states, analyserModel->stateCount());
    EXPECT_EQ_VALUES(std::vector<double>({1.0}), rates, analyserModel->stateCount());
    EXPECT_EQ_VALUES(std::vector<double>({1.0}), constants, analyserModel->constantCount());
    EXPECT_EQ_VALUES(std::vector<double>({1.0}), computedConstants, analyserModel->computedConstantCount());
    EXPECT_EQ_VALUES(std::vector<double>({1.0}), algebraic, analyserModel->algebraicCount());

    FINALISE_MODEL();
}

TEST(Generator, odeComputedVarOnRhsOneComponent)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("generator/ode_computed_var_on_rhs_one_component/model.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    auto analyser = libcellml::Analyser::create();

    analyser->analyseModel(model);

    EXPECT_EQ(size_t(0), analyser->errorCount());

    auto analyserModel = analyser->model();
    auto generator = libcellml::Generator::create();

    generator->setModel(analyserModel);

    EXPECT_EQ_FILE_CONTENTS("generator/ode_computed_var_on_rhs_one_component/model.h", generator->interfaceCode());
    EXPECT_EQ_FILE_CONTENTS("generator/ode_computed_var_on_rhs_one_component/model.c", generator->implementationCode());

    auto profile = libcellml::GeneratorProfile::create(libcellml::GeneratorProfile::Profile::PYTHON);

    generator->setProfile(profile);

    EXPECT_EQ_FILE_CONTENTS("generator/ode_computed_var_on_rhs_one_component/model.py", generator->implementationCode());

    auto interpreter = libcellml::Interpreter::create();

    interpreter->setModel(analyserModel);

    INITIALISE_INTERPRETED_DIFFERENTIAL_MODEL(analyserModel);

    EXPECT_EQ_VALUES(std::vector<double>({1.0}), states, analyserModel->stateCount());
    EXPECT_EQ_VALUES(std::vector<double>({1.0}), rates, analyserModel->stateCount());
    EXPECT_EQ_VALUES(std::vector<double>({1.0}), constants, analyserModel->constantCount());
    EXPECT_EQ_VALUES(std::vector<double>({1.0}), computedConstants, analyserModel->computedConstantCount());
    EXPECT_EQ_VALUES(std::vector<double>({1.0}), algebraic, analyserModel->algebraicCount());

    FINALISE_MODEL();
}

TEST(Generator, odeConstVarOnRhs)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("generator/ode_const_var_on_rhs/model.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    auto analyser = libcellml::Analyser::create();

    analyser->analyseModel(model);

    EXPECT_EQ(size_t(0), analyser->errorCount());

    auto analyserModel = analyser->model();
    auto generator = libcellml::Generator::create();

    generator->setModel(analyserModel);

    EXPECT_EQ_FILE_CONTENTS("generator/ode_const_var_on_rhs/model.h", generator->interfaceCode());
    EXPECT_EQ_FILE_CONTENTS("generator/ode_const_var_on_rhs/model.c", generator->implementationCode());

    auto profile = libcellml::GeneratorProfile::create(libcellml::GeneratorProfile::Profile::PYTHON);

    generator->setProfile(profile);

    EXPECT_EQ_FILE_CONTENTS("generator/ode_const_var_on_rhs/model.py", generator->implementationCode());

    auto interpreter = libcellml::Interpreter::create();

    interpreter->setModel(analyserModel);

    INITIALISE_INTERPRETED_DIFFERENTIAL_MODEL(analyserModel);

    EXPECT_EQ_VALUES(std::vector<double>({1.0}), states, analyserModel->stateCount());
    EXPECT_EQ_VALUES(std::vector<double>({1.0}), rates, analyserModel->stateCount());
    EXPECT_EQ_VALUES(std::vector<double>({1.0}), constants, analyserModel->constantCount());
    EXPECT_EQ_VALUES(std::vector<double>({1.0}), computedConstants, analyserModel->computedConstantCount());
    EXPECT_EQ_VALUES(std::vector<double>({1.0}), algebraic, analyserModel->algebraicCount());

    FINALISE_MODEL();
}

TEST(Generator, odeConstVarOnRhsOneComponent)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("generator/ode_const_var_on_rhs_one_component/model.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    auto analyser = libcellml::Analyser::create();

    analyser->analyseModel(model);

    EXPECT_EQ(size_t(0), analyser->errorCount());

    auto analyserModel = analyser->model();
    auto generator = libcellml::Generator::create();

    generator->setModel(analyserModel);

    EXPECT_EQ_FILE_CONTENTS("generator/ode_const_var_on_rhs_one_component/model.h", generator->interfaceCode());
    EXPECT_EQ_FILE_CONTENTS("generator/ode_const_var_on_rhs_one_component/model.c", generator->implementationCode());

    auto profile = libcellml::GeneratorProfile::create(libcellml::GeneratorProfile::Profile::PYTHON);

    generator->setProfile(profile);

    EXPECT_EQ_FILE_CONTENTS("generator/ode_const_var_on_rhs_one_component/model.py", generator->implementationCode());

    auto interpreter = libcellml::Interpreter::create();

    interpreter->setModel(analyserModel);

    INITIALISE_INTERPRETED_DIFFERENTIAL_MODEL(analyserModel);

    EXPECT_EQ_VALUES(std::vector<double>({1.0}), states, analyserModel->stateCount());
    EXPECT_EQ_VALUES(std::vector<double>({1.0}), rates, analyserModel->stateCount());
    EXPECT_EQ_VALUES(std::vector<double>({1.0}), constants, analyserModel->constantCount());
    EXPECT_EQ_VALUES(std::vector<double>({1.0}), computedConstants, analyserModel->computedConstantCount());
    EXPECT_EQ_VALUES(std::vector<double>({1.0}), algebraic, analyserModel->algebraicCount());

    FINALISE_MODEL();
}

TEST(Generator, odeConstantOnRhs)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("generator/ode_constant_on_rhs/model.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    auto analyser = libcellml::Analyser::create();

    analyser->analyseModel(model);

    EXPECT_EQ(size_t(0), analyser->errorCount());

    auto analyserModel = analyser->model();
    auto generator = libcellml::Generator::create();

    generator->setModel(analyserModel);

    EXPECT_EQ_FILE_CONTENTS("generator/ode_constant_on_rhs/model.h", generator->interfaceCode());
    EXPECT_EQ_FILE_CONTENTS("generator/ode_constant_on_rhs/model.c", generator->implementationCode());

    auto profile = libcellml::GeneratorProfile::create(libcellml::GeneratorProfile::Profile::PYTHON);

    generator->setProfile(profile);

    EXPECT_EQ_FILE_CONTENTS("generator/ode_constant_on_rhs/model.py", generator->implementationCode());

    auto interpreter = libcellml::Interpreter::create();

    interpreter->setModel(analyserModel);

    INITIALISE_INTERPRETED_DIFFERENTIAL_MODEL(analyserModel);

    EXPECT_EQ_VALUES(std::vector<double>({1.0}), states, analyserModel->stateCount());
    EXPECT_EQ_VALUES(std::vector<double>({1.0}), rates, analyserModel->stateCount());
    EXPECT_EQ_VALUES(NO_VALUES, constants, analyserModel->constantCount());
    EXPECT_EQ_VALUES(NO_VALUES, computedConstants, analyserModel->computedConstantCount());
    EXPECT_EQ_VALUES(NO_VALUES, algebraic, analyserModel->algebraicCount());

    FINALISE_MODEL();
}

TEST(Generator, odeConstantOnRhsOneComponent)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("generator/ode_constant_on_rhs_one_component/model.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    auto analyser = libcellml::Analyser::create();

    analyser->analyseModel(model);

    EXPECT_EQ(size_t(0), analyser->errorCount());

    auto analyserModel = analyser->model();
    auto generator = libcellml::Generator::create();

    generator->setModel(analyserModel);

    EXPECT_EQ_FILE_CONTENTS("generator/ode_constant_on_rhs_one_component/model.h", generator->interfaceCode());
    EXPECT_EQ_FILE_CONTENTS("generator/ode_constant_on_rhs_one_component/model.c", generator->implementationCode());

    auto profile = libcellml::GeneratorProfile::create(libcellml::GeneratorProfile::Profile::PYTHON);

    generator->setProfile(profile);

    EXPECT_EQ_FILE_CONTENTS("generator/ode_constant_on_rhs_one_component/model.py", generator->implementationCode());

    auto interpreter = libcellml::Interpreter::create();

    interpreter->setModel(analyserModel);

    INITIALISE_INTERPRETED_DIFFERENTIAL_MODEL(analyserModel);

    EXPECT_EQ_VALUES(std::vector<double>({1.0}), states, analyserModel->stateCount());
    EXPECT_EQ_VALUES(std::vector<double>({1.0}), rates, analyserModel->stateCount());
    EXPECT_EQ_VALUES(NO_VALUES, constants, analyserModel->constantCount());
    EXPECT_EQ_VALUES(NO_VALUES, computedConstants, analyserModel->computedConstantCount());
    EXPECT_EQ_VALUES(NO_VALUES, algebraic, analyserModel->algebraicCount());

    FINALISE_MODEL();
}

TEST(Generator, odeMultipleDependentOdes)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("generator/ode_multiple_dependent_odes/model.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    auto analyser = libcellml::Analyser::create();

    analyser->analyseModel(model);

    EXPECT_EQ(size_t(0), analyser->errorCount());

    auto analyserModel = analyser->model();
    auto generator = libcellml::Generator::create();

    generator->setModel(analyserModel);

    EXPECT_EQ_FILE_CONTENTS("generator/ode_multiple_dependent_odes/model.h", generator->interfaceCode());
    EXPECT_EQ_FILE_CONTENTS("generator/ode_multiple_dependent_odes/model.c", generator->implementationCode());

    auto profile = libcellml::GeneratorProfile::create(libcellml::GeneratorProfile::Profile::PYTHON);

    generator->setProfile(profile);

    EXPECT_EQ_FILE_CONTENTS("generator/ode_multiple_dependent_odes/model.py", generator->implementationCode());

    auto interpreter = libcellml::Interpreter::create();

    interpreter->setModel(analyserModel);

    INITIALISE_INTERPRETED_DIFFERENTIAL_MODEL(analyserModel);

    EXPECT_EQ_VALUES(std::vector<double>({-2.0, 0.0}), states, analyserModel->stateCount());
    EXPECT_EQ_VALUES(std::vector<double>({0.0, 2.0}), rates, analyserModel->stateCount());
    EXPECT_EQ_VALUES(std::vector<double>({1.0}), constants, analyserModel->constantCount());
    EXPECT_EQ_VALUES(std::vector<double>({1.0}), computedConstants, analyserModel->computedConstantCount());
    EXPECT_EQ_VALUES(std::vector<double>({1.0}), algebraic, analyserModel->algebraicCount());

    FINALISE_MODEL();
}

TEST(Generator, odeMultipleDependentOdesOneComponent)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("generator/ode_multiple_dependent_odes_one_component/model.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    auto analyser = libcellml::Analyser::create();

    analyser->analyseModel(model);

    EXPECT_EQ(size_t(0), analyser->errorCount());

    auto analyserModel = analyser->model();
    auto generator = libcellml::Generator::create();

    generator->setModel(analyserModel);

    EXPECT_EQ_FILE_CONTENTS("generator/ode_multiple_dependent_odes_one_component/model.h", generator->interfaceCode());
    EXPECT_EQ_FILE_CONTENTS("generator/ode_multiple_dependent_odes_one_component/model.c", generator->implementationCode());

    auto profile = libcellml::GeneratorProfile::create(libcellml::GeneratorProfile::Profile::PYTHON);

    generator->setProfile(profile);

    EXPECT_EQ_FILE_CONTENTS("generator/ode_multiple_dependent_odes_one_component/model.py", generator->implementationCode());

    auto interpreter = libcellml::Interpreter::create();

    interpreter->setModel(analyserModel);

    INITIALISE_INTERPRETED_DIFFERENTIAL_MODEL(analyserModel);

    EXPECT_EQ_VALUES(std::vector<double>({-2.0, 0.0}), states, analyserModel->stateCount());
    EXPECT_EQ_VALUES(std::vector<double>({0.0, 2.0}), rates, analyserModel->stateCount());
    EXPECT_EQ_VALUES(std::vector<double>({1.0}), constants, analyserModel->constantCount());
    EXPECT_EQ_VALUES(std::vector<double>({1.0}), computedConstants, analyserModel->computedConstantCount());
    EXPECT_EQ_VALUES(std::vector<double>({1.0}), algebraic, analyserModel->algebraicCount());

    FINALISE_MODEL();
}

TEST(Generator, odeMultipleOdesWithSameName)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("generator/ode_multiple_odes_with_same_name/model.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    auto analyser = libcellml::Analyser::create();

    analyser->analyseModel(model);

    EXPECT_EQ(size_t(0), analyser->errorCount());

    auto analyserModel = analyser->model();
    auto generator = libcellml::Generator::create();

    generator->setModel(analyserModel);

    EXPECT_EQ_FILE_CONTENTS("generator/ode_multiple_odes_with_same_name/model.h", generator->interfaceCode());
    EXPECT_EQ_FILE_CONTENTS("generator/ode_multiple_odes_with_same_name/model.c", generator->implementationCode());

    auto profile = libcellml::GeneratorProfile::create(libcellml::GeneratorProfile::Profile::PYTHON);

    generator->setProfile(profile);

    EXPECT_EQ_FILE_CONTENTS("generator/ode_multiple_odes_with_same_name/model.py", generator->implementationCode());

    auto interpreter = libcellml::Interpreter::create();

    interpreter->setModel(analyserModel);

    INITIALISE_INTERPRETED_DIFFERENTIAL_MODEL(analyserModel);

    EXPECT_EQ_VALUES(std::vector<double>({1.0, 1.0}), states, analyserModel->stateCount());
    EXPECT_EQ_VALUES(std::vector<double>({1.0, 1.0}), rates, analyserModel->stateCount());
    EXPECT_EQ_VALUES(std::vector<double>({1.0}), constants, analyserModel->constantCount());
    EXPECT_EQ_VALUES(std::vector<double>({1.0}), computedConstants, analyserModel->computedConstantCount());
    EXPECT_EQ_VALUES(std::vector<double>({1.0}), algebraic, analyserModel->algebraicCount());

    FINALISE_MODEL();
}

TEST(Generator, odeUnknownVarOnRhs)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("generator/ode_unknown_var_on_rhs/model.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    auto analyser = libcellml::Analyser::create();

    analyser->analyseModel(model);

    EXPECT_EQ(size_t(0), analyser->errorCount());

    auto analyserModel = analyser->model();
    auto generator = libcellml::Generator::create();

    generator->setModel(analyserModel);

    EXPECT_EQ_FILE_CONTENTS("generator/ode_unknown_var_on_rhs/model.h", generator->interfaceCode());
    EXPECT_EQ_FILE_CONTENTS("generator/ode_unknown_var_on_rhs/model.c", generator->implementationCode());

    auto profile = libcellml::GeneratorProfile::create(libcellml::GeneratorProfile::Profile::PYTHON);

    generator->setProfile(profile);

    EXPECT_EQ_FILE_CONTENTS("generator/ode_unknown_var_on_rhs/model.py", generator->implementationCode());

    auto interpreter = libcellml::Interpreter::create();

    interpreter->setModel(analyserModel);

    INITIALISE_INTERPRETED_DIFFERENTIAL_MODEL(analyserModel);

    EXPECT_EQ_VALUES(std::vector<double>({1.0, 1.0}), states, analyserModel->stateCount());
    EXPECT_EQ_VALUES(std::vector<double>({1.0, 1.0}), rates, analyserModel->stateCount());
    EXPECT_EQ_VALUES(NO_VALUES, constants, analyserModel->constantCount());
    EXPECT_EQ_VALUES(NO_VALUES, computedConstants, analyserModel->computedConstantCount());
    EXPECT_EQ_VALUES(NO_VALUES, algebraic, analyserModel->algebraicCount());

    FINALISE_MODEL();
}

TEST(Generator, cellmlMappingsAndEncapsulations)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("generator/cellml_mappings_and_encapsulations/model.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    auto analyser = libcellml::Analyser::create();

    analyser->analyseModel(model);

    EXPECT_EQ(size_t(0), analyser->errorCount());

    auto analyserModel = analyser->model();
    auto generator = libcellml::Generator::create();

    generator->setModel(analyserModel);

    EXPECT_EQ_FILE_CONTENTS("generator/cellml_mappings_and_encapsulations/model.h", generator->interfaceCode());
    EXPECT_EQ_FILE_CONTENTS("generator/cellml_mappings_and_encapsulations/model.c", generator->implementationCode());

    auto profile = libcellml::GeneratorProfile::create(libcellml::GeneratorProfile::Profile::PYTHON);

    generator->setProfile(profile);

    EXPECT_EQ_FILE_CONTENTS("generator/cellml_mappings_and_encapsulations/model.py", generator->implementationCode());

    auto interpreter = libcellml::Interpreter::create();

    interpreter->setModel(analyserModel);

    INITIALISE_INTERPRETED_DIFFERENTIAL_MODEL(analyserModel);

    EXPECT_EQ_VALUES(std::vector<double>({1.0, 0.0}), states, analyserModel->stateCount());
    EXPECT_EQ_VALUES(std::vector<double>({0.0, -1.0}), rates, analyserModel->stateCount());
    EXPECT_EQ_VALUES(std::vector<double>({4.3153879373667952, 0.0}), constants, analyserModel->constantCount());
    EXPECT_EQ_VALUES(std::vector<double>({4.3153879373667952, 0.0}), computedConstants, analyserModel->computedConstantCount());
    EXPECT_EQ_VALUES(std::vector<double>({4.3153879373667952, 0.0}), algebraic, analyserModel->algebraicCount());

    FINALISE_MODEL();
}

TEST(Generator, cellmlStateInitialisedUsingVariable)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("generator/cellml_state_initialised_using_variable/model.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    auto analyser = libcellml::Analyser::create();

    analyser->analyseModel(model);

    EXPECT_EQ(size_t(0), analyser->errorCount());

    auto analyserModel = analyser->model();
    auto generator = libcellml::Generator::create();

    generator->setModel(analyserModel);

    EXPECT_EQ_FILE_CONTENTS("generator/cellml_state_initialised_using_variable/model.h", generator->interfaceCode());
    EXPECT_EQ_FILE_CONTENTS("generator/cellml_state_initialised_using_variable/model.c", generator->implementationCode());

    auto profile = libcellml::GeneratorProfile::create(libcellml::GeneratorProfile::Profile::PYTHON);

    generator->setProfile(profile);

    EXPECT_EQ_FILE_CONTENTS("generator/cellml_state_initialised_using_variable/model.py", generator->implementationCode());

    auto interpreter = libcellml::Interpreter::create();

    interpreter->setModel(analyserModel);

    INITIALISE_INTERPRETED_DIFFERENTIAL_MODEL(analyserModel);

    EXPECT_EQ_VALUES(std::vector<double>({123.0}), states, analyserModel->stateCount());
    EXPECT_EQ_VALUES(std::vector<double>({1.23}), rates, analyserModel->stateCount());
    EXPECT_EQ_VALUES(std::vector<double>({123.0}), constants, analyserModel->constantCount());
    EXPECT_EQ_VALUES(std::vector<double>({123.0}), computedConstants, analyserModel->computedConstantCount());
    EXPECT_EQ_VALUES(std::vector<double>({123.0}), algebraic, analyserModel->algebraicCount());

    FINALISE_MODEL();
}

TEST(Generator, cellmlUnitScalingVoiIndirect)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("generator/cellml_unit_scaling_voi_indirect/model.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    auto analyser = libcellml::Analyser::create();

    analyser->analyseModel(model);

    EXPECT_EQ(size_t(0), analyser->errorCount());

    auto analyserModel = analyser->model();
    auto generator = libcellml::Generator::create();

    generator->setModel(analyserModel);

    EXPECT_EQ_FILE_CONTENTS("generator/cellml_unit_scaling_voi_indirect/model.h", generator->interfaceCode());
    EXPECT_EQ_FILE_CONTENTS("generator/cellml_unit_scaling_voi_indirect/model.c", generator->implementationCode());

    auto profile = libcellml::GeneratorProfile::create(libcellml::GeneratorProfile::Profile::PYTHON);

    generator->setProfile(profile);

    EXPECT_EQ_FILE_CONTENTS("generator/cellml_unit_scaling_voi_indirect/model.py", generator->implementationCode());

    auto interpreter = libcellml::Interpreter::create();

    interpreter->setModel(analyserModel);

    INITIALISE_INTERPRETED_DIFFERENTIAL_MODEL(analyserModel);

    EXPECT_EQ_VALUES(std::vector<double>({3.0, 7.0, 11.0}), states, analyserModel->stateCount());
    EXPECT_EQ_VALUES(std::vector<double>({5.0, 9000.0, 0.013}), rates, analyserModel->stateCount());
    EXPECT_EQ_VALUES(NO_VALUES, constants, analyserModel->constantCount());
    EXPECT_EQ_VALUES(NO_VALUES, computedConstants, analyserModel->computedConstantCount());
    EXPECT_EQ_VALUES(NO_VALUES, algebraic, analyserModel->algebraicCount());

    FINALISE_MODEL();
}

TEST(Generator, cellmlUnitScalingVoiDirect)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("generator/cellml_unit_scaling_voi_direct/model.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    auto analyser = libcellml::Analyser::create();

    analyser->analyseModel(model);

    EXPECT_EQ(size_t(0), analyser->errorCount());

    auto analyserModel = analyser->model();
    auto generator = libcellml::Generator::create();

    generator->setModel(analyserModel);

    EXPECT_EQ_FILE_CONTENTS("generator/cellml_unit_scaling_voi_direct/model.h", generator->interfaceCode());
    EXPECT_EQ_FILE_CONTENTS("generator/cellml_unit_scaling_voi_direct/model.c", generator->implementationCode());

    auto profile = libcellml::GeneratorProfile::create(libcellml::GeneratorProfile::Profile::PYTHON);

    generator->setProfile(profile);

    EXPECT_EQ_FILE_CONTENTS("generator/cellml_unit_scaling_voi_direct/model.py", generator->implementationCode());

    auto interpreter = libcellml::Interpreter::create();

    interpreter->setModel(analyserModel);

    INITIALISE_INTERPRETED_DIFFERENTIAL_MODEL(analyserModel);

    EXPECT_EQ_VALUES(std::vector<double>({3.0, 5.0}), states, analyserModel->stateCount());
    EXPECT_EQ_VALUES(std::vector<double>({0.0, 0.0}), rates, analyserModel->stateCount());
    EXPECT_EQ_VALUES(NO_VALUES, constants, analyserModel->constantCount());
    EXPECT_EQ_VALUES(NO_VALUES, computedConstants, analyserModel->computedConstantCount());
    EXPECT_EQ_VALUES(NO_VALUES, algebraic, analyserModel->algebraicCount());

    FINALISE_MODEL();
}

TEST(Generator, cellmlUnitScalingConstant)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("generator/cellml_unit_scaling_constant/model.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    auto analyser = libcellml::Analyser::create();

    const std::vector<std::string> expectedIssues = {
        "Variable 'c_M' in component 'constants' is initialised using variable 'c' which has different units.",
        "Variable 'oc_mM' in component 'other_constants' is initialised using variable 'c' which has different units.",
    };

    analyser->analyseModel(model);

    EXPECT_EQ_ISSUES(expectedIssues, analyser);

    auto analyserModel = analyser->model();
    auto generator = libcellml::Generator::create();

    generator->setModel(analyserModel);

    EXPECT_EQ_FILE_CONTENTS("generator/cellml_unit_scaling_constant/model.h", generator->interfaceCode());
    EXPECT_EQ_FILE_CONTENTS("generator/cellml_unit_scaling_constant/model.c", generator->implementationCode());

    auto profile = libcellml::GeneratorProfile::create(libcellml::GeneratorProfile::Profile::PYTHON);

    generator->setProfile(profile);

    EXPECT_EQ_FILE_CONTENTS("generator/cellml_unit_scaling_constant/model.py", generator->implementationCode());

    auto interpreter = libcellml::Interpreter::create();

    interpreter->setModel(analyserModel);

    INITIALISE_INTERPRETED_ALGEBRAIC_MODEL(analyserModel);

    EXPECT_EQ_VALUES(std::vector<double>({123.0, 246.0, 0.246}), constants, analyserModel->constantCount());
    EXPECT_EQ_VALUES(std::vector<double>({123.0, 246.0, 0.246}), computedConstants, analyserModel->computedConstantCount());
    EXPECT_EQ_VALUES(std::vector<double>({123.0, 246.0, 0.246}), algebraic, analyserModel->algebraicCount());

    FINALISE_MODEL();
}

TEST(Generator, cellmlUnitScalingState)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("generator/cellml_unit_scaling_state/model.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    auto analyser = libcellml::Analyser::create();

    analyser->analyseModel(model);

    EXPECT_EQ(size_t(0), analyser->errorCount());

    auto analyserModel = analyser->model();
    auto generator = libcellml::Generator::create();

    generator->setModel(analyserModel);

    EXPECT_EQ_FILE_CONTENTS("generator/cellml_unit_scaling_state/model.h", generator->interfaceCode());
    EXPECT_EQ_FILE_CONTENTS("generator/cellml_unit_scaling_state/model.c", generator->implementationCode());

    auto profile = libcellml::GeneratorProfile::create(libcellml::GeneratorProfile::Profile::PYTHON);

    generator->setProfile(profile);

    EXPECT_EQ_FILE_CONTENTS("generator/cellml_unit_scaling_state/model.py", generator->implementationCode());

    auto interpreter = libcellml::Interpreter::create();

    interpreter->setModel(analyserModel);

    INITIALISE_INTERPRETED_DIFFERENTIAL_MODEL(analyserModel);

    EXPECT_EQ_VALUES(std::vector<double>({123.0}), states, analyserModel->stateCount());
    EXPECT_EQ_VALUES(std::vector<double>({1.23}), rates, analyserModel->stateCount());
    EXPECT_EQ_VALUES(std::vector<double>({246.0, 0.246}), constants, analyserModel->constantCount());
    EXPECT_EQ_VALUES(std::vector<double>({246.0, 0.246}), computedConstants, analyserModel->computedConstantCount());
    EXPECT_EQ_VALUES(std::vector<double>({246.0, 0.246}), algebraic, analyserModel->algebraicCount());

    FINALISE_MODEL();
}

TEST(Generator, cellmlUnitScalingStateInitialisedUsingConstant)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("generator/cellml_unit_scaling_state_initialised_using_constant/model.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    auto analyser = libcellml::Analyser::create();

    analyser->analyseModel(model);

    EXPECT_EQ(size_t(0), analyser->errorCount());

    auto analyserModel = analyser->model();
    auto generator = libcellml::Generator::create();

    generator->setModel(analyserModel);

    EXPECT_EQ_FILE_CONTENTS("generator/cellml_unit_scaling_state_initialised_using_constant/model.h", generator->interfaceCode());
    EXPECT_EQ_FILE_CONTENTS("generator/cellml_unit_scaling_state_initialised_using_constant/model.c", generator->implementationCode());

    auto profile = libcellml::GeneratorProfile::create(libcellml::GeneratorProfile::Profile::PYTHON);

    generator->setProfile(profile);

    EXPECT_EQ_FILE_CONTENTS("generator/cellml_unit_scaling_state_initialised_using_constant/model.py", generator->implementationCode());

    auto interpreter = libcellml::Interpreter::create();

    interpreter->setModel(analyserModel);

    INITIALISE_INTERPRETED_DIFFERENTIAL_MODEL(analyserModel);

    EXPECT_EQ_VALUES(std::vector<double>({123.0, 0.789}), states, analyserModel->stateCount());
    EXPECT_EQ_VALUES(std::vector<double>({1.23, 7.89}), rates, analyserModel->stateCount());
    EXPECT_EQ_VALUES(NO_VALUES, constants, analyserModel->constantCount());
    EXPECT_EQ_VALUES(NO_VALUES, computedConstants, analyserModel->computedConstantCount());
    EXPECT_EQ_VALUES(NO_VALUES, algebraic, analyserModel->algebraicCount());

    FINALISE_MODEL();
}

TEST(Generator, cellmlUnitScalingStateInitialisedUsingVariable)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("generator/cellml_unit_scaling_state_initialised_using_variable/model.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    auto analyser = libcellml::Analyser::create();

    analyser->analyseModel(model);

    EXPECT_EQ(size_t(0), analyser->errorCount());

    auto analyserModel = analyser->model();
    auto generator = libcellml::Generator::create();

    generator->setModel(analyserModel);

    EXPECT_EQ_FILE_CONTENTS("generator/cellml_unit_scaling_state_initialised_using_variable/model.h", generator->interfaceCode());
    EXPECT_EQ_FILE_CONTENTS("generator/cellml_unit_scaling_state_initialised_using_variable/model.c", generator->implementationCode());

    auto profile = libcellml::GeneratorProfile::create(libcellml::GeneratorProfile::Profile::PYTHON);

    generator->setProfile(profile);

    EXPECT_EQ_FILE_CONTENTS("generator/cellml_unit_scaling_state_initialised_using_variable/model.py", generator->implementationCode());

    auto interpreter = libcellml::Interpreter::create();

    interpreter->setModel(analyserModel);

    INITIALISE_INTERPRETED_DIFFERENTIAL_MODEL(analyserModel);

    EXPECT_EQ_VALUES(std::vector<double>({123.0, 0.789}), states, analyserModel->stateCount());
    EXPECT_EQ_VALUES(std::vector<double>({1.23, 7.89}), rates, analyserModel->stateCount());
    EXPECT_EQ_VALUES(std::vector<double>({123.0, 789.0}), constants, analyserModel->constantCount());
    EXPECT_EQ_VALUES(std::vector<double>({123.0, 789.0}), computedConstants, analyserModel->computedConstantCount());
    EXPECT_EQ_VALUES(std::vector<double>({123.0, 789.0}), algebraic, analyserModel->algebraicCount());

    FINALISE_MODEL();
}

TEST(Generator, cellmlUnitScalingRate)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("generator/cellml_unit_scaling_rate/model.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    auto analyser = libcellml::Analyser::create();

    analyser->analyseModel(model);

    EXPECT_EQ(size_t(0), analyser->errorCount());

    auto analyserModel = analyser->model();
    auto generator = libcellml::Generator::create();

    generator->setModel(analyserModel);

    EXPECT_EQ_FILE_CONTENTS("generator/cellml_unit_scaling_rate/model.h", generator->interfaceCode());
    EXPECT_EQ_FILE_CONTENTS("generator/cellml_unit_scaling_rate/model.c", generator->implementationCode());

    auto profile = libcellml::GeneratorProfile::create(libcellml::GeneratorProfile::Profile::PYTHON);

    generator->setProfile(profile);

    EXPECT_EQ_FILE_CONTENTS("generator/cellml_unit_scaling_rate/model.py", generator->implementationCode());

    auto interpreter = libcellml::Interpreter::create();

    interpreter->setModel(analyserModel);

    INITIALISE_INTERPRETED_DIFFERENTIAL_MODEL(analyserModel);

    EXPECT_EQ_VALUES(std::vector<double>({123.0}), states, analyserModel->stateCount());
    EXPECT_EQ_VALUES(std::vector<double>({1.23}), rates, analyserModel->stateCount());
    EXPECT_EQ_VALUES(std::vector<double>({2460.0, 2.46}), constants, analyserModel->constantCount());
    EXPECT_EQ_VALUES(std::vector<double>({2460.0, 2.46}), computedConstants, analyserModel->computedConstantCount());
    EXPECT_EQ_VALUES(std::vector<double>({2460.0, 2.46}), algebraic, analyserModel->algebraicCount());

    FINALISE_MODEL();
}

TEST(Generator, dependentEqns)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("generator/dependent_eqns/model.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    auto analyser = libcellml::Analyser::create();

    analyser->analyseModel(model);

    EXPECT_EQ(size_t(0), analyser->errorCount());

    auto analyserModel = analyser->model();
    auto generator = libcellml::Generator::create();

    generator->setModel(analyserModel);

    EXPECT_EQ_FILE_CONTENTS("generator/dependent_eqns/model.h", generator->interfaceCode());
    EXPECT_EQ_FILE_CONTENTS("generator/dependent_eqns/model.c", generator->implementationCode());

    auto profile = libcellml::GeneratorProfile::create(libcellml::GeneratorProfile::Profile::PYTHON);

    generator->setProfile(profile);

    EXPECT_EQ_FILE_CONTENTS("generator/dependent_eqns/model.py", generator->implementationCode());

    auto interpreter = libcellml::Interpreter::create();

    interpreter->setModel(analyserModel);

    INITIALISE_INTERPRETED_DIFFERENTIAL_MODEL(analyserModel);

    EXPECT_EQ_VALUES(std::vector<double>({0.0}), states, analyserModel->stateCount());
    EXPECT_EQ_VALUES(std::vector<double>({1.0}), rates, analyserModel->stateCount());
    EXPECT_EQ_VALUES(std::vector<double>({0.0, 0.0}), constants, analyserModel->constantCount());
    EXPECT_EQ_VALUES(std::vector<double>({0.0, 0.0}), computedConstants, analyserModel->computedConstantCount());
    EXPECT_EQ_VALUES(std::vector<double>({0.0, 0.0}), algebraic, analyserModel->algebraicCount());

    FINALISE_MODEL();
}

TEST(Generator, cellGeometryModel)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("generator/cell_geometry_model/model.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    auto analyser = libcellml::Analyser::create();

    analyser->analyseModel(model);

    EXPECT_EQ(size_t(0), analyser->errorCount());

    auto analyserModel = analyser->model();
    auto generator = libcellml::Generator::create();

    generator->setModel(analyserModel);

    EXPECT_EQ_FILE_CONTENTS("generator/cell_geometry_model/model.h", generator->interfaceCode());
    EXPECT_EQ_FILE_CONTENTS("generator/cell_geometry_model/model.c", generator->implementationCode());

    auto profile = libcellml::GeneratorProfile::create(libcellml::GeneratorProfile::Profile::PYTHON);

    generator->setProfile(profile);

    EXPECT_EQ_FILE_CONTENTS("generator/cell_geometry_model/model.py", generator->implementationCode());

    auto interpreter = libcellml::Interpreter::create();

    interpreter->setModel(analyserModel);

    INITIALISE_INTERPRETED_ALGEBRAIC_MODEL(analyserModel);

    EXPECT_EQ_VALUES(std::vector<double>({0.000037994, 0.01, 0.0011, 0.00000075988}), constants, analyserModel->constantCount());
    EXPECT_EQ_VALUES(std::vector<double>({0.000037994, 0.01, 0.0011, 0.00000075988}), computedConstants, analyserModel->computedConstantCount());
    EXPECT_EQ_VALUES(std::vector<double>({0.000037994, 0.01, 0.0011, 0.00000075988}), algebraic, analyserModel->algebraicCount());

    FINALISE_MODEL();
}

TEST(Generator, cellGeometryModelWithSomeConstantsAsExternalVariables)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("generator/cell_geometry_model/model.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    auto analyser = libcellml::Analyser::create();

    analyser->addExternalVariable(libcellml::AnalyserExternalVariable::create(model->component("cell_geometry")->variable("L")));
    analyser->addExternalVariable(libcellml::AnalyserExternalVariable::create(model->component("cell_geometry")->variable("rad")));

    analyser->analyseModel(model);

    EXPECT_EQ(size_t(0), analyser->errorCount());

    auto analyserModel = analyser->model();
    auto generator = libcellml::Generator::create();

    generator->setModel(analyserModel);

    auto profile = generator->profile();

    profile->setInterfaceFileNameString("model.external.h");

    EXPECT_EQ_FILE_CONTENTS("generator/cell_geometry_model/model.external.h", generator->interfaceCode());
    EXPECT_EQ_FILE_CONTENTS("generator/cell_geometry_model/model.external.c", generator->implementationCode());

    profile = libcellml::GeneratorProfile::create(libcellml::GeneratorProfile::Profile::PYTHON);

    generator->setProfile(profile);

    EXPECT_EQ_FILE_CONTENTS("generator/cell_geometry_model/model.external.py", generator->implementationCode());

    auto interpreter = libcellml::Interpreter::create();

    interpreter->setModel(analyserModel);

    INITIALISE_INTERPRETED_ALGEBRAIC_MODEL(analyserModel);

    EXPECT_EQ_VALUES(NAN_x_4, constants, analyserModel->constantCount());
    EXPECT_EQ_VALUES(NAN_x_4, computedConstants, analyserModel->computedConstantCount());
    EXPECT_EQ_VALUES(NAN_x_4, algebraic, analyserModel->algebraicCount());

    FINALISE_MODEL();
}

TEST(Generator, fabbriFantiniWildersSeveriHumanSanModel2017)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("generator/fabbri_fantini_wilders_severi_human_san_model_2017/model.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    auto analyser = libcellml::Analyser::create();

    analyser->analyseModel(model);

    EXPECT_EQ(size_t(0), analyser->errorCount());

    auto analyserModel = analyser->model();
    auto generator = libcellml::Generator::create();

    generator->setModel(analyserModel);

    EXPECT_EQ_FILE_CONTENTS("generator/fabbri_fantini_wilders_severi_human_san_model_2017/model.h", generator->interfaceCode());
    EXPECT_EQ_FILE_CONTENTS("generator/fabbri_fantini_wilders_severi_human_san_model_2017/model.c", generator->implementationCode());

    auto profile = libcellml::GeneratorProfile::create(libcellml::GeneratorProfile::Profile::PYTHON);

    generator->setProfile(profile);

    EXPECT_EQ_FILE_CONTENTS("generator/fabbri_fantini_wilders_severi_human_san_model_2017/model.py", generator->implementationCode());

    auto interpreter = libcellml::Interpreter::create();

    interpreter->setModel(analyserModel);

    INITIALISE_INTERPRETED_DIFFERENTIAL_MODEL(analyserModel);
    INITIALISE_COMPILED_MODEL(fabbri_fantini_wilders_severi_human_san_model_2017);

    EXPECT_EQ_VALUES(expectedStates, states, analyserModel->stateCount());
    EXPECT_EQ_VALUES(expectedRates, rates, analyserModel->stateCount());
    EXPECT_EQ_VALUES(expectedConstants, constants, analyserModel->constantCount());
    EXPECT_EQ_VALUES(expectedComputedConstants, computedConstants, analyserModel->computedConstantCount());
    EXPECT_EQ_VALUES(expectedAlgebraic, algebraic, analyserModel->algebraicCount());

    FINALISE_MODEL();
}

TEST(Generator, garnyKohlHunterBoyettNobleRabbitSanModel2003)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("generator/garny_kohl_hunter_boyett_noble_rabbit_san_model_2003/model.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    auto analyser = libcellml::Analyser::create();

    analyser->analyseModel(model);

    EXPECT_EQ(size_t(0), analyser->errorCount());

    auto analyserModel = analyser->model();
    auto generator = libcellml::Generator::create();

    generator->setModel(analyserModel);

    EXPECT_EQ_FILE_CONTENTS("generator/garny_kohl_hunter_boyett_noble_rabbit_san_model_2003/model.h", generator->interfaceCode());
    EXPECT_EQ_FILE_CONTENTS("generator/garny_kohl_hunter_boyett_noble_rabbit_san_model_2003/model.c", generator->implementationCode());

    auto profile = libcellml::GeneratorProfile::create(libcellml::GeneratorProfile::Profile::PYTHON);

    generator->setProfile(profile);

    EXPECT_EQ_FILE_CONTENTS("generator/garny_kohl_hunter_boyett_noble_rabbit_san_model_2003/model.py", generator->implementationCode());

    auto interpreter = libcellml::Interpreter::create();

    interpreter->setModel(analyserModel);

    INITIALISE_INTERPRETED_DIFFERENTIAL_MODEL(analyserModel);
    INITIALISE_COMPILED_MODEL(garny_kohl_hunter_boyett_noble_rabbit_san_model_2003);

    EXPECT_EQ_VALUES(expectedStates, states, analyserModel->stateCount());
    EXPECT_EQ_VALUES(expectedRates, rates, analyserModel->stateCount());
    EXPECT_EQ_VALUES(expectedConstants, constants, analyserModel->constantCount());
    EXPECT_EQ_VALUES(expectedComputedConstants, computedConstants, analyserModel->computedConstantCount());
    EXPECT_EQ_VALUES(expectedAlgebraic, algebraic, analyserModel->algebraicCount());

    FINALISE_MODEL();
}

TEST(Generator, hodgkinHuxleySquidAxonModel1952)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("generator/hodgkin_huxley_squid_axon_model_1952/model.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    auto analyser = libcellml::Analyser::create();

    analyser->analyseModel(model);

    EXPECT_EQ(size_t(0), analyser->errorCount());

    auto analyserModel = analyser->model();
    auto generator = libcellml::Generator::create();

    generator->setModel(analyserModel);

    EXPECT_EQ_FILE_CONTENTS("generator/hodgkin_huxley_squid_axon_model_1952/model.h", generator->interfaceCode());
    EXPECT_EQ_FILE_CONTENTS("generator/hodgkin_huxley_squid_axon_model_1952/model.c", generator->implementationCode());

    auto profile = libcellml::GeneratorProfile::create(libcellml::GeneratorProfile::Profile::PYTHON);

    generator->setProfile(profile);

    EXPECT_EQ_FILE_CONTENTS("generator/hodgkin_huxley_squid_axon_model_1952/model.py", generator->implementationCode());

    auto interpreter = libcellml::Interpreter::create();

    interpreter->setModel(analyserModel);

    INITIALISE_INTERPRETED_DIFFERENTIAL_MODEL(analyserModel);

    EXPECT_EQ_VALUES(std::vector<double>({0.0, 0.6, 0.05, 0.325}), states, analyserModel->stateCount());
    EXPECT_EQ_VALUES(std::vector<double>({0.60076874999999963, -0.00045552390654006458, 0.012385538355398518, -0.0013415722863204596}), rates, analyserModel->stateCount());
    EXPECT_EQ_VALUES(std::vector<double>({0.0, 3.1839, -4.81966875, 1.035, 1.0, 0.0, -10.613, 0.3, -115.0, 120.0, 0.22356372458463003, 4.0, 0.07, 0.047425873177566781, 12.0, 36.0, 0.05819767068693265, 0.125}), constants, analyserModel->constantCount());
    EXPECT_EQ_VALUES(std::vector<double>({0.0, 3.1839, -4.81966875, 1.035, 1.0, 0.0, -10.613, 0.3, -115.0, 120.0, 0.22356372458463003, 4.0, 0.07, 0.047425873177566781, 12.0, 36.0, 0.05819767068693265, 0.125}), computedConstants, analyserModel->computedConstantCount());
    EXPECT_EQ_VALUES(std::vector<double>({0.0, 3.1839, -4.81966875, 1.035, 1.0, 0.0, -10.613, 0.3, -115.0, 120.0, 0.22356372458463003, 4.0, 0.07, 0.047425873177566781, 12.0, 36.0, 0.05819767068693265, 0.125}), algebraic, analyserModel->algebraicCount());

    FINALISE_MODEL();
}

TEST(Generator, hodgkinHuxleySquidAxonModel1952UnknownVarsOnRhs)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("generator/hodgkin_huxley_squid_axon_model_1952/model_unknown_vars_on_rhs.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    auto analyser = libcellml::Analyser::create();

    analyser->analyseModel(model);

    EXPECT_EQ(size_t(0), analyser->errorCount());

    auto analyserModel = analyser->model();
    auto generator = libcellml::Generator::create();

    generator->setModel(analyserModel);

    EXPECT_EQ_FILE_CONTENTS("generator/hodgkin_huxley_squid_axon_model_1952/model.h", generator->interfaceCode());
    EXPECT_EQ_FILE_CONTENTS("generator/hodgkin_huxley_squid_axon_model_1952/model.c", generator->implementationCode());

    auto profile = libcellml::GeneratorProfile::create(libcellml::GeneratorProfile::Profile::PYTHON);

    generator->setProfile(profile);

    EXPECT_EQ_FILE_CONTENTS("generator/hodgkin_huxley_squid_axon_model_1952/model.py", generator->implementationCode());

    auto interpreter = libcellml::Interpreter::create();

    interpreter->setModel(analyserModel);

    INITIALISE_INTERPRETED_DIFFERENTIAL_MODEL(analyserModel);

    EXPECT_EQ_VALUES(std::vector<double>({0.0, 0.6, 0.05, 0.325}), states, analyserModel->stateCount());
    EXPECT_EQ_VALUES(std::vector<double>({0.60076874999999963, -0.00045552390654006458, 0.012385538355398518, -0.0013415722863204596}), rates, analyserModel->stateCount());
    EXPECT_EQ_VALUES(std::vector<double>({0.0, 3.1839, -4.8196687499999999, 1.035, 1.0, 0.0, -10.613, 0.3, -115.0, 120.0, 0.22356372458463003, 4.0, 0.07, 0.047425873177566781, 12.0, 36.0, 0.05819767068693265, 0.125}), constants, analyserModel->constantCount());
    EXPECT_EQ_VALUES(std::vector<double>({0.0, 3.1839, -4.8196687499999999, 1.035, 1.0, 0.0, -10.613, 0.3, -115.0, 120.0, 0.22356372458463003, 4.0, 0.07, 0.047425873177566781, 12.0, 36.0, 0.05819767068693265, 0.125}), computedConstants, analyserModel->computedConstantCount());
    EXPECT_EQ_VALUES(std::vector<double>({0.0, 3.1839, -4.8196687499999999, 1.035, 1.0, 0.0, -10.613, 0.3, -115.0, 120.0, 0.22356372458463003, 4.0, 0.07, 0.047425873177566781, 12.0, 36.0, 0.05819767068693265, 0.125}), algebraic, analyserModel->algebraicCount());

    FINALISE_MODEL();
}

TEST(Generator, hodgkinHuxleySquidAxonModel1952WithStateVariableAsExternalVariable)
{
    // Generate some code for the HH52 model with sodium_channel.m (i.e. not a
    // primary variable) as an external variable.

    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("generator/hodgkin_huxley_squid_axon_model_1952/model.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    auto analyser = libcellml::Analyser::create();

    analyser->addExternalVariable(libcellml::AnalyserExternalVariable::create(model->component("sodium_channel")->variable("m")));

    analyser->analyseModel(model);

    EXPECT_EQ(size_t(0), analyser->errorCount());

    auto analyserModel = analyser->model();
    auto generator = libcellml::Generator::create();

    generator->setModel(analyserModel);

    auto profile = generator->profile();

    profile->setInterfaceFileNameString("model.state.h");

    EXPECT_EQ_FILE_CONTENTS("generator/hodgkin_huxley_squid_axon_model_1952/model.state.h", generator->interfaceCode());
    EXPECT_EQ_FILE_CONTENTS("generator/hodgkin_huxley_squid_axon_model_1952/model.state.c", generator->implementationCode());

    profile = libcellml::GeneratorProfile::create(libcellml::GeneratorProfile::Profile::PYTHON);

    generator->setProfile(profile);

    EXPECT_EQ_FILE_CONTENTS("generator/hodgkin_huxley_squid_axon_model_1952/model.state.py", generator->implementationCode());

    auto interpreter = libcellml::Interpreter::create();

    interpreter->setModel(analyserModel);

    INITIALISE_INTERPRETED_DIFFERENTIAL_MODEL(analyserModel);

    EXPECT_EQ_VALUES(std::vector<double>({0.0, 0.6, 0.325}), states, analyserModel->stateCount());
    EXPECT_EQ_VALUES(std::vector<double>({NAN, -0.00045552390654006458, -0.0013415722863204596}), rates, analyserModel->stateCount());
    EXPECT_EQ_VALUES(std::vector<double>({0.0, 3.1839, -4.8196687499999999, NAN, 1.0, 0.0, -10.613, 0.3, -115.0, 120.0, NAN, 0.22356372458463003, 4.0, 0.07, 0.047425873177566781, 12.0, 36.0, 0.05819767068693265, 0.125}), constants, analyserModel->constantCount());
    EXPECT_EQ_VALUES(std::vector<double>({0.0, 3.1839, -4.8196687499999999, NAN, 1.0, 0.0, -10.613, 0.3, -115.0, 120.0, NAN, 0.22356372458463003, 4.0, 0.07, 0.047425873177566781, 12.0, 36.0, 0.05819767068693265, 0.125}), computedConstants, analyserModel->computedConstantCount());
    EXPECT_EQ_VALUES(std::vector<double>({0.0, 3.1839, -4.8196687499999999, NAN, 1.0, 0.0, -10.613, 0.3, -115.0, 120.0, NAN, 0.22356372458463003, 4.0, 0.07, 0.047425873177566781, 12.0, 36.0, 0.05819767068693265, 0.125}), algebraic, analyserModel->algebraicCount());

    FINALISE_MODEL();
}

TEST(Generator, hodgkinHuxleySquidAxonModel1952WithStateVariablesAsExternalVariablesIncludingOneDependingOnTheOther)
{
    // Generate some code for the HH52 model with sodium_channel.m (i.e. not a
    // primary variable) as an external variable which has a dependency on
    // sodium_channel.V (i.e. not a primary variable), another state marked as
    // an external variable.

    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("generator/hodgkin_huxley_squid_axon_model_1952/model.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    auto analyser = libcellml::Analyser::create();
    auto sodium_channel_V = model->component("sodium_channel")->variable("V");
    auto external_sodium_channel_m = libcellml::AnalyserExternalVariable::create(model->component("sodium_channel")->variable("m"));

    external_sodium_channel_m->addDependency(sodium_channel_V);

    analyser->addExternalVariable(libcellml::AnalyserExternalVariable::create(sodium_channel_V));
    analyser->addExternalVariable(external_sodium_channel_m);

    analyser->analyseModel(model);

    EXPECT_EQ(size_t(0), analyser->errorCount());

    auto analyserModel = analyser->model();
    auto generator = libcellml::Generator::create();

    generator->setModel(analyserModel);

    auto profile = generator->profile();

    profile->setInterfaceFileNameString("model.dependent.state.h");

    EXPECT_EQ_FILE_CONTENTS("generator/hodgkin_huxley_squid_axon_model_1952/model.dependent.state.h", generator->interfaceCode());
    EXPECT_EQ_FILE_CONTENTS("generator/hodgkin_huxley_squid_axon_model_1952/model.dependent.state.c", generator->implementationCode());

    profile = libcellml::GeneratorProfile::create(libcellml::GeneratorProfile::Profile::PYTHON);

    generator->setProfile(profile);

    EXPECT_EQ_FILE_CONTENTS("generator/hodgkin_huxley_squid_axon_model_1952/model.dependent.state.py", generator->implementationCode());

    auto interpreter = libcellml::Interpreter::create();

    interpreter->setModel(analyserModel);

    INITIALISE_INTERPRETED_DIFFERENTIAL_MODEL(analyserModel);

    EXPECT_EQ_VALUES(std::vector<double>({0.6, 0.325}), states, analyserModel->stateCount());
    EXPECT_EQ_VALUES(NAN_x_2, rates, analyserModel->stateCount());
    EXPECT_EQ_VALUES(std::vector<double>({0.0, NAN, NAN, NAN, NAN, 1.0, 0.0, -10.613, 0.3, -115.0, 120.0, NAN, NAN, NAN, NAN, NAN, 12.0, 36.0, NAN, NAN}), constants, analyserModel->constantCount());
    EXPECT_EQ_VALUES(std::vector<double>({0.0, NAN, NAN, NAN, NAN, 1.0, 0.0, -10.613, 0.3, -115.0, 120.0, NAN, NAN, NAN, NAN, NAN, 12.0, 36.0, NAN, NAN}), computedConstants, analyserModel->computedConstantCount());
    EXPECT_EQ_VALUES(std::vector<double>({0.0, NAN, NAN, NAN, NAN, 1.0, 0.0, -10.613, 0.3, -115.0, 120.0, NAN, NAN, NAN, NAN, NAN, 12.0, 36.0, NAN, NAN}), algebraic, analyserModel->algebraicCount());

    FINALISE_MODEL();
}

TEST(Generator, hodgkinHuxleySquidAxonModel1952WithConstantAsExternalVariable)
{
    // Generate some code for the HH52 model with membrane.Cm as an external
    // variable.

    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("generator/hodgkin_huxley_squid_axon_model_1952/model.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    auto analyser = libcellml::Analyser::create();

    analyser->addExternalVariable(libcellml::AnalyserExternalVariable::create(model->component("membrane")->variable("Cm")));

    analyser->analyseModel(model);

    EXPECT_EQ(size_t(0), analyser->errorCount());

    auto analyserModel = analyser->model();
    auto generator = libcellml::Generator::create();

    generator->setModel(analyserModel);

    auto profile = generator->profile();

    profile->setInterfaceFileNameString("model.constant.h");

    EXPECT_EQ_FILE_CONTENTS("generator/hodgkin_huxley_squid_axon_model_1952/model.constant.h", generator->interfaceCode());
    EXPECT_EQ_FILE_CONTENTS("generator/hodgkin_huxley_squid_axon_model_1952/model.constant.c", generator->implementationCode());

    profile = libcellml::GeneratorProfile::create(libcellml::GeneratorProfile::Profile::PYTHON);

    generator->setProfile(profile);

    EXPECT_EQ_FILE_CONTENTS("generator/hodgkin_huxley_squid_axon_model_1952/model.constant.py", generator->implementationCode());

    auto interpreter = libcellml::Interpreter::create();

    interpreter->setModel(analyserModel);

    INITIALISE_INTERPRETED_DIFFERENTIAL_MODEL(analyserModel);

    EXPECT_EQ_VALUES(std::vector<double>({0.0, 0.6, 0.05, 0.325}), states, analyserModel->stateCount());
    EXPECT_EQ_VALUES(std::vector<double>({NAN, -0.00045552390654006458, 0.012385538355398518, -0.0013415722863204596}), rates, analyserModel->stateCount());
    EXPECT_EQ_VALUES(std::vector<double>({0.0, 3.1839, -4.8196687499999999, 1.035, NAN, 0.0, -10.613, 0.3, -115.0, 120.0, 0.22356372458463003, 4.0, 0.07, 0.047425873177566781, 12.0, 36.0, 0.05819767068693265, 0.125}), constants, analyserModel->constantCount());
    EXPECT_EQ_VALUES(std::vector<double>({0.0, 3.1839, -4.8196687499999999, 1.035, NAN, 0.0, -10.613, 0.3, -115.0, 120.0, 0.22356372458463003, 4.0, 0.07, 0.047425873177566781, 12.0, 36.0, 0.05819767068693265, 0.125}), computedConstants, analyserModel->computedConstantCount());
    EXPECT_EQ_VALUES(std::vector<double>({0.0, 3.1839, -4.8196687499999999, 1.035, NAN, 0.0, -10.613, 0.3, -115.0, 120.0, 0.22356372458463003, 4.0, 0.07, 0.047425873177566781, 12.0, 36.0, 0.05819767068693265, 0.125}), algebraic, analyserModel->algebraicCount());

    FINALISE_MODEL();
}

TEST(Generator, hodgkinHuxleySquidAxonModel1952WithConstantsAsExternalVariablesIncludingOneDependingOnTheOther)
{
    // Generate some code for the HH52 model with membrane.Cm as an external
    // variable which has a dependency on sodium_channel.g_Na, another constant
    // marked as an external variable.

    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("generator/hodgkin_huxley_squid_axon_model_1952/model.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    auto analyser = libcellml::Analyser::create();
    auto sodium_channel_g_Na = model->component("sodium_channel")->variable("g_Na");
    auto external_sodium_channel_Cm = libcellml::AnalyserExternalVariable::create(model->component("membrane")->variable("Cm"));

    external_sodium_channel_Cm->addDependency(sodium_channel_g_Na);

    analyser->addExternalVariable(libcellml::AnalyserExternalVariable::create(sodium_channel_g_Na));
    analyser->addExternalVariable(external_sodium_channel_Cm);

    analyser->analyseModel(model);

    EXPECT_EQ(size_t(0), analyser->errorCount());

    auto analyserModel = analyser->model();
    auto generator = libcellml::Generator::create();

    generator->setModel(analyserModel);

    auto profile = generator->profile();

    profile->setInterfaceFileNameString("model.dependent.constant.h");

    EXPECT_EQ_FILE_CONTENTS("generator/hodgkin_huxley_squid_axon_model_1952/model.dependent.constant.h", generator->interfaceCode());
    EXPECT_EQ_FILE_CONTENTS("generator/hodgkin_huxley_squid_axon_model_1952/model.dependent.constant.c", generator->implementationCode());

    profile = libcellml::GeneratorProfile::create(libcellml::GeneratorProfile::Profile::PYTHON);

    generator->setProfile(profile);

    EXPECT_EQ_FILE_CONTENTS("generator/hodgkin_huxley_squid_axon_model_1952/model.dependent.constant.py", generator->implementationCode());

    auto interpreter = libcellml::Interpreter::create();

    interpreter->setModel(analyserModel);

    INITIALISE_INTERPRETED_DIFFERENTIAL_MODEL(analyserModel);

    EXPECT_EQ_VALUES(std::vector<double>({0.0, 0.6, 0.05, 0.325}), states, analyserModel->stateCount());
    EXPECT_EQ_VALUES(std::vector<double>({NAN, -0.00045552390654006458, 0.012385538355398518, -0.0013415722863204596}), rates, analyserModel->stateCount());
    EXPECT_EQ_VALUES(std::vector<double>({0.0, 3.1839, -4.8196687499999999, NAN, NAN, 0.0, -10.613, 0.3, -115.0, NAN, 0.22356372458463003, 4.0, 0.07, 0.047425873177566781, 12.0, 36.0, 0.05819767068693265, 0.125}), constants, analyserModel->constantCount());
    EXPECT_EQ_VALUES(std::vector<double>({0.0, 3.1839, -4.8196687499999999, NAN, NAN, 0.0, -10.613, 0.3, -115.0, NAN, 0.22356372458463003, 4.0, 0.07, 0.047425873177566781, 12.0, 36.0, 0.05819767068693265, 0.125}), computedConstants, analyserModel->computedConstantCount());
    EXPECT_EQ_VALUES(std::vector<double>({0.0, 3.1839, -4.8196687499999999, NAN, NAN, 0.0, -10.613, 0.3, -115.0, NAN, 0.22356372458463003, 4.0, 0.07, 0.047425873177566781, 12.0, 36.0, 0.05819767068693265, 0.125}), algebraic, analyserModel->algebraicCount());

    FINALISE_MODEL();
}

TEST(Generator, hodgkinHuxleySquidAxonModel1952WithComputedConstantAsExternalVariable)
{
    // Generate some code for the HH52 model with leakage_current.E_L as an
    // external variable.

    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("generator/hodgkin_huxley_squid_axon_model_1952/model.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    auto analyser = libcellml::Analyser::create();

    analyser->addExternalVariable(libcellml::AnalyserExternalVariable::create(model->component("leakage_current")->variable("E_L")));

    analyser->analyseModel(model);

    EXPECT_EQ(size_t(0), analyser->errorCount());

    auto analyserModel = analyser->model();
    auto generator = libcellml::Generator::create();

    generator->setModel(analyserModel);

    auto profile = generator->profile();

    profile->setInterfaceFileNameString("model.computed.constant.h");

    EXPECT_EQ_FILE_CONTENTS("generator/hodgkin_huxley_squid_axon_model_1952/model.computed.constant.h", generator->interfaceCode());
    EXPECT_EQ_FILE_CONTENTS("generator/hodgkin_huxley_squid_axon_model_1952/model.computed.constant.c", generator->implementationCode());

    profile = libcellml::GeneratorProfile::create(libcellml::GeneratorProfile::Profile::PYTHON);

    generator->setProfile(profile);

    EXPECT_EQ_FILE_CONTENTS("generator/hodgkin_huxley_squid_axon_model_1952/model.computed.constant.py", generator->implementationCode());

    auto interpreter = libcellml::Interpreter::create();

    interpreter->setModel(analyserModel);

    INITIALISE_INTERPRETED_DIFFERENTIAL_MODEL(analyserModel);

    EXPECT_EQ_VALUES(std::vector<double>({0.0, 0.6, 0.05, 0.325}), states, analyserModel->stateCount());
    EXPECT_EQ_VALUES(std::vector<double>({NAN, -0.00045552390654006458, 0.012385538355398518, -0.0013415722863204596}), rates, analyserModel->stateCount());
    EXPECT_EQ_VALUES(std::vector<double>({0.0, NAN, -4.8196687499999999, 1.035, 1.0, 0.0, NAN, 0.3, -115.0, 120.0, 0.22356372458463003, 4.0, 0.07, 0.047425873177566781, 12.0, 36.0, 0.05819767068693265, 0.125}), constants, analyserModel->constantCount());
    EXPECT_EQ_VALUES(std::vector<double>({0.0, NAN, -4.8196687499999999, 1.035, 1.0, 0.0, NAN, 0.3, -115.0, 120.0, 0.22356372458463003, 4.0, 0.07, 0.047425873177566781, 12.0, 36.0, 0.05819767068693265, 0.125}), computedConstants, analyserModel->computedConstantCount());
    EXPECT_EQ_VALUES(std::vector<double>({0.0, NAN, -4.8196687499999999, 1.035, 1.0, 0.0, NAN, 0.3, -115.0, 120.0, 0.22356372458463003, 4.0, 0.07, 0.047425873177566781, 12.0, 36.0, 0.05819767068693265, 0.125}), algebraic, analyserModel->algebraicCount());

    FINALISE_MODEL();
}

TEST(Generator, hodgkinHuxleySquidAxonModel1952WithComputedConstantsAsExternalVariablesIncludingOneDependingOnTheOther)
{
    // Generate some code for the HH52 model with leakage_current.E_R as an
    // external variable which has a dependency on potassium_channel.E_K,
    // another computed constant marked as an external variable.

    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("generator/hodgkin_huxley_squid_axon_model_1952/model.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    auto analyser = libcellml::Analyser::create();
    auto potassium_channel_E_K = model->component("potassium_channel")->variable("E_K");
    auto external_leakage_current_E_R = libcellml::AnalyserExternalVariable::create(model->component("membrane")->variable("E_R"));

    external_leakage_current_E_R->addDependency(potassium_channel_E_K);

    analyser->addExternalVariable(libcellml::AnalyserExternalVariable::create(potassium_channel_E_K));
    analyser->addExternalVariable(external_leakage_current_E_R);

    analyser->analyseModel(model);

    EXPECT_EQ(size_t(0), analyser->errorCount());

    auto analyserModel = analyser->model();
    auto generator = libcellml::Generator::create();

    generator->setModel(analyserModel);

    auto profile = generator->profile();

    profile->setInterfaceFileNameString("model.dependent.computed.constant.h");

    EXPECT_EQ_FILE_CONTENTS("generator/hodgkin_huxley_squid_axon_model_1952/model.dependent.computed.constant.h", generator->interfaceCode());
    EXPECT_EQ_FILE_CONTENTS("generator/hodgkin_huxley_squid_axon_model_1952/model.dependent.computed.constant.c", generator->implementationCode());

    profile = libcellml::GeneratorProfile::create(libcellml::GeneratorProfile::Profile::PYTHON);

    generator->setProfile(profile);

    EXPECT_EQ_FILE_CONTENTS("generator/hodgkin_huxley_squid_axon_model_1952/model.dependent.computed.constant.py", generator->implementationCode());

    auto interpreter = libcellml::Interpreter::create();

    interpreter->setModel(analyserModel);

    INITIALISE_INTERPRETED_DIFFERENTIAL_MODEL(analyserModel);

    EXPECT_EQ_VALUES(std::vector<double>({0.0, 0.6, 0.05, 0.325}), states, analyserModel->stateCount());
    EXPECT_EQ_VALUES(std::vector<double>({NAN, -0.00045552390654006458, 0.012385538355398518, -0.0013415722863204596}), rates, analyserModel->stateCount());
    EXPECT_EQ_VALUES(std::vector<double>({0.0, NAN, NAN, NAN, 1.0, NAN, NAN, 0.3, NAN, 120.0, 0.22356372458463003, 4.0, 0.07, 0.047425873177566781, NAN, 36.0, 0.05819767068693265, 0.125}), constants, analyserModel->constantCount());
    EXPECT_EQ_VALUES(std::vector<double>({0.0, NAN, NAN, NAN, 1.0, NAN, NAN, 0.3, NAN, 120.0, 0.22356372458463003, 4.0, 0.07, 0.047425873177566781, NAN, 36.0, 0.05819767068693265, 0.125}), computedConstants, analyserModel->computedConstantCount());
    EXPECT_EQ_VALUES(std::vector<double>({0.0, NAN, NAN, NAN, 1.0, NAN, NAN, 0.3, NAN, 120.0, 0.22356372458463003, 4.0, 0.07, 0.047425873177566781, NAN, 36.0, 0.05819767068693265, 0.125}), algebraic, analyserModel->algebraicCount());

    FINALISE_MODEL();
}

TEST(Generator, hodgkinHuxleySquidAxonModel1952WithAlgebraicVariableAsExternalVariable)
{
    // Generate some code for the HH52 model with membrane.i_Stim as an external
    // variable.

    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("generator/hodgkin_huxley_squid_axon_model_1952/model.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    auto analyser = libcellml::Analyser::create();

    analyser->addExternalVariable(libcellml::AnalyserExternalVariable::create(model->component("membrane")->variable("i_Stim")));

    analyser->analyseModel(model);

    EXPECT_EQ(size_t(0), analyser->errorCount());

    auto analyserModel = analyser->model();
    auto generator = libcellml::Generator::create();

    generator->setModel(analyserModel);

    auto profile = generator->profile();

    profile->setInterfaceFileNameString("model.algebraic.h");

    EXPECT_EQ_FILE_CONTENTS("generator/hodgkin_huxley_squid_axon_model_1952/model.algebraic.h", generator->interfaceCode());
    EXPECT_EQ_FILE_CONTENTS("generator/hodgkin_huxley_squid_axon_model_1952/model.algebraic.c", generator->implementationCode());

    profile = libcellml::GeneratorProfile::create(libcellml::GeneratorProfile::Profile::PYTHON);

    generator->setProfile(profile);

    EXPECT_EQ_FILE_CONTENTS("generator/hodgkin_huxley_squid_axon_model_1952/model.algebraic.py", generator->implementationCode());

    auto interpreter = libcellml::Interpreter::create();

    interpreter->setModel(analyserModel);

    INITIALISE_INTERPRETED_DIFFERENTIAL_MODEL(analyserModel);

    EXPECT_EQ_VALUES(std::vector<double>({0.0, 0.6, 0.05, 0.325}), states, analyserModel->stateCount());
    EXPECT_EQ_VALUES(std::vector<double>({NAN, -0.00045552390654006458, 0.012385538355398518, -0.0013415722863204596}), rates, analyserModel->stateCount());
    EXPECT_EQ_VALUES(std::vector<double>({NAN, 3.1839, -4.81966875, 1.035, 1.0, 0.0, -10.613, 0.3, -115.0, 120.0, 0.22356372458463003, 4.0, 0.07, 0.047425873177566781, 12.0, 36.0, 0.05819767068693265, 0.125}), constants, analyserModel->constantCount());
    EXPECT_EQ_VALUES(std::vector<double>({NAN, 3.1839, -4.81966875, 1.035, 1.0, 0.0, -10.613, 0.3, -115.0, 120.0, 0.22356372458463003, 4.0, 0.07, 0.047425873177566781, 12.0, 36.0, 0.05819767068693265, 0.125}), computedConstants, analyserModel->computedConstantCount());
    EXPECT_EQ_VALUES(std::vector<double>({NAN, 3.1839, -4.81966875, 1.035, 1.0, 0.0, -10.613, 0.3, -115.0, 120.0, 0.22356372458463003, 4.0, 0.07, 0.047425873177566781, 12.0, 36.0, 0.05819767068693265, 0.125}), algebraic, analyserModel->algebraicCount());

    FINALISE_MODEL();
}

TEST(Generator, hodgkinHuxleySquidAxonModel1952WithAlgebraicVariablesAsExternalVariablesIncludingOneDependingOnTheOther)
{
    // Generate some code for the HH52 model with membrane.i_Stim as an external
    // variable which has a dependency on potassium_channel_n_gate.beta_n,
    // another algebraic variable marked as an external variable.

    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("generator/hodgkin_huxley_squid_axon_model_1952/model.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    auto analyser = libcellml::Analyser::create();
    auto potassium_channel_n_gate_beta_n = model->component("potassium_channel_n_gate")->variable("beta_n");
    auto membrane_i_Stim = libcellml::AnalyserExternalVariable::create(model->component("membrane")->variable("i_Stim"));

    membrane_i_Stim->addDependency(potassium_channel_n_gate_beta_n);

    analyser->addExternalVariable(libcellml::AnalyserExternalVariable::create(potassium_channel_n_gate_beta_n));
    analyser->addExternalVariable(membrane_i_Stim);

    analyser->analyseModel(model);

    EXPECT_EQ(size_t(0), analyser->errorCount());

    auto analyserModel = analyser->model();
    auto generator = libcellml::Generator::create();

    generator->setModel(analyserModel);

    auto profile = generator->profile();

    profile->setInterfaceFileNameString("model.dependent.algebraic.h");

    EXPECT_EQ_FILE_CONTENTS("generator/hodgkin_huxley_squid_axon_model_1952/model.dependent.algebraic.h", generator->interfaceCode());
    EXPECT_EQ_FILE_CONTENTS("generator/hodgkin_huxley_squid_axon_model_1952/model.dependent.algebraic.c", generator->implementationCode());

    profile = libcellml::GeneratorProfile::create(libcellml::GeneratorProfile::Profile::PYTHON);

    generator->setProfile(profile);

    EXPECT_EQ_FILE_CONTENTS("generator/hodgkin_huxley_squid_axon_model_1952/model.dependent.algebraic.py", generator->implementationCode());

    auto interpreter = libcellml::Interpreter::create();

    interpreter->setModel(analyserModel);

    INITIALISE_INTERPRETED_DIFFERENTIAL_MODEL(analyserModel);

    EXPECT_EQ_VALUES(std::vector<double>({0.0, 0.6, 0.05, 0.325}), states, analyserModel->stateCount());
    EXPECT_EQ_VALUES(std::vector<double>({NAN, -0.00045552390654006458, 0.012385538355398518, NAN}), rates, analyserModel->stateCount());
    EXPECT_EQ_VALUES(std::vector<double>({NAN, 3.1839, -4.81966875, 1.035, 1.0, 0.0, -10.613, 0.3, -115.0, 120.0, 0.22356372458463003, 4.0, 0.07, 0.047425873177566781, 12.0, 36.0, 0.05819767068693265, NAN}), constants, analyserModel->constantCount());
    EXPECT_EQ_VALUES(std::vector<double>({NAN, 3.1839, -4.81966875, 1.035, 1.0, 0.0, -10.613, 0.3, -115.0, 120.0, 0.22356372458463003, 4.0, 0.07, 0.047425873177566781, 12.0, 36.0, 0.05819767068693265, NAN}), computedConstants, analyserModel->computedConstantCount());
    EXPECT_EQ_VALUES(std::vector<double>({NAN, 3.1839, -4.81966875, 1.035, 1.0, 0.0, -10.613, 0.3, -115.0, 120.0, 0.22356372458463003, 4.0, 0.07, 0.047425873177566781, 12.0, 36.0, 0.05819767068693265, NAN}), algebraic, analyserModel->algebraicCount());

    FINALISE_MODEL();
}

TEST(Generator, hodgkinHuxleySquidAxonModel1952WithVariousExternalVariables)
{
    // Generate some code for the HH52 model with sodium_channel.i_Na as an
    // external variable which has a dependency on
    // potassium_channel_n_gate.alpha_n, another external variable (which is
    // going to be declared after i_Na, so that it ends up with a higher index,
    // meaning that it would normally be computed after i_Na if there was no
    // such a dependency), and on sodium_channel_h_gate.h, a state variable, so
    // that i_Na ends up being computed both in the computeRates() and
    // computeVariables() methods.

    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("generator/hodgkin_huxley_squid_axon_model_1952/model.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    auto analyser = libcellml::Analyser::create();
    auto potassium_channel_n_gate_alpha_n = model->component("potassium_channel_n_gate")->variable("alpha_n");
    auto external_sodium_channel_i_Na = libcellml::AnalyserExternalVariable::create(model->component("sodium_channel")->variable("i_Na"));

    external_sodium_channel_i_Na->addDependency(potassium_channel_n_gate_alpha_n);
    external_sodium_channel_i_Na->addDependency(model->component("sodium_channel_h_gate")->variable("h"));

    analyser->addExternalVariable(libcellml::AnalyserExternalVariable::create(model->component("membrane")->variable("V")));
    analyser->addExternalVariable(external_sodium_channel_i_Na);
    analyser->addExternalVariable(libcellml::AnalyserExternalVariable::create(potassium_channel_n_gate_alpha_n));

    analyser->analyseModel(model);

    EXPECT_EQ(size_t(0), analyser->errorCount());

    auto analyserModel = analyser->model();
    auto generator = libcellml::Generator::create();

    generator->setModel(analyserModel);

    auto profile = generator->profile();

    profile->setInterfaceFileNameString("model.external.h");

    EXPECT_EQ_FILE_CONTENTS("generator/hodgkin_huxley_squid_axon_model_1952/model.external.h", generator->interfaceCode());
    EXPECT_EQ_FILE_CONTENTS("generator/hodgkin_huxley_squid_axon_model_1952/model.external.c", generator->implementationCode());

    profile = libcellml::GeneratorProfile::create(libcellml::GeneratorProfile::Profile::PYTHON);

    generator->setProfile(profile);

    EXPECT_EQ_FILE_CONTENTS("generator/hodgkin_huxley_squid_axon_model_1952/model.external.py", generator->implementationCode());

    auto interpreter = libcellml::Interpreter::create();

    interpreter->setModel(analyserModel);

    INITIALISE_INTERPRETED_DIFFERENTIAL_MODEL(analyserModel);

    EXPECT_EQ_VALUES(std::vector<double>({0.6, 0.05, 0.325}), states, analyserModel->stateCount());
    EXPECT_EQ_VALUES(NAN_x_3, rates, analyserModel->stateCount());
    EXPECT_EQ_VALUES(std::vector<double>({0.0, NAN, NAN, NAN, NAN, 1.0, 0.0, -10.613, 0.3, -115.0, 120.0, NAN, NAN, NAN, NAN, 12.0, 36.0, NAN, NAN}), constants, analyserModel->constantCount());
    EXPECT_EQ_VALUES(std::vector<double>({0.0, NAN, NAN, NAN, NAN, 1.0, 0.0, -10.613, 0.3, -115.0, 120.0, NAN, NAN, NAN, NAN, 12.0, 36.0, NAN, NAN}), computedConstants, analyserModel->computedConstantCount());
    EXPECT_EQ_VALUES(std::vector<double>({0.0, NAN, NAN, NAN, NAN, 1.0, 0.0, -10.613, 0.3, -115.0, 120.0, NAN, NAN, NAN, NAN, 12.0, 36.0, NAN, NAN}), algebraic, analyserModel->algebraicCount());

    FINALISE_MODEL();
}

TEST(Generator, hodgkinHuxleySquidAxonModel195Dae)
{
    // Same as the hodgkinHuxleySquidAxonModel1952 test, except that all the
    // algebraic equations are to be computed using NLA systems of one equation.

    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("generator/hodgkin_huxley_squid_axon_model_1952/model.dae.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    auto analyser = libcellml::Analyser::create();

    analyser->analyseModel(model);

    EXPECT_EQ(size_t(0), analyser->errorCount());

    auto analyserModel = analyser->model();
    auto generator = libcellml::Generator::create();

    generator->setModel(analyserModel);

    auto profile = generator->profile();

    profile->setInterfaceFileNameString("model.dae.h");

    EXPECT_EQ_FILE_CONTENTS("generator/hodgkin_huxley_squid_axon_model_1952/model.dae.h", generator->interfaceCode());
    EXPECT_EQ_FILE_CONTENTS("generator/hodgkin_huxley_squid_axon_model_1952/model.dae.c", generator->implementationCode());

    profile = libcellml::GeneratorProfile::create(libcellml::GeneratorProfile::Profile::PYTHON);

    generator->setProfile(profile);

    EXPECT_EQ_FILE_CONTENTS("generator/hodgkin_huxley_squid_axon_model_1952/model.dae.py", generator->implementationCode());

    auto interpreter = libcellml::Interpreter::create();

    interpreter->setModel(analyserModel);

    INITIALISE_INTERPRETED_DIFFERENTIAL_MODEL(analyserModel);

    EXPECT_EQ_VALUES(std::vector<double>({0.0, 0.6, 0.05, 0.325}), states, analyserModel->stateCount());
    EXPECT_EQ_VALUES(std::vector<double>({0.0, 0.0, 0.0, 0.0}), rates, analyserModel->stateCount());
    EXPECT_EQ_VALUES(std::vector<double>({0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.3, 0.0, 120.0, 0.0, 0.0, 0.0, 0.0, 0.0, 36.0, 0.0, 0.0}), constants, analyserModel->constantCount());
    EXPECT_EQ_VALUES(std::vector<double>({0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.3, 0.0, 120.0, 0.0, 0.0, 0.0, 0.0, 0.0, 36.0, 0.0, 0.0}), computedConstants, analyserModel->computedConstantCount());
    EXPECT_EQ_VALUES(std::vector<double>({0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.3, 0.0, 120.0, 0.0, 0.0, 0.0, 0.0, 0.0, 36.0, 0.0, 0.0}), algebraic, analyserModel->algebraicCount());

    FINALISE_MODEL();
}

TEST(Generator, hodgkinHuxleySquidAxonModel1952DaeWithVariousExternalVariables)
{
    // Same as hodgkinHuxleySquidAxonModel1952WithVariousExternalVariables but with the DAE version of the HH52 model.

    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("generator/hodgkin_huxley_squid_axon_model_1952/model.dae.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    auto analyser = libcellml::Analyser::create();
    auto potassium_channel_n_gate_alpha_n = model->component("potassium_channel_n_gate")->variable("alpha_n");
    auto external_sodium_channel_i_Na = libcellml::AnalyserExternalVariable::create(model->component("sodium_channel")->variable("i_Na"));

    external_sodium_channel_i_Na->addDependency(potassium_channel_n_gate_alpha_n);
    external_sodium_channel_i_Na->addDependency(model->component("sodium_channel_h_gate")->variable("h"));

    analyser->addExternalVariable(libcellml::AnalyserExternalVariable::create(model->component("membrane")->variable("V")));
    analyser->addExternalVariable(external_sodium_channel_i_Na);
    analyser->addExternalVariable(libcellml::AnalyserExternalVariable::create(potassium_channel_n_gate_alpha_n));

    analyser->analyseModel(model);

    EXPECT_EQ(size_t(0), analyser->errorCount());

    auto analyserModel = analyser->model();
    auto generator = libcellml::Generator::create();

    generator->setModel(analyserModel);

    auto profile = generator->profile();

    profile->setInterfaceFileNameString("model.dae.external.h");

    EXPECT_EQ_FILE_CONTENTS("generator/hodgkin_huxley_squid_axon_model_1952/model.dae.external.h", generator->interfaceCode());
    EXPECT_EQ_FILE_CONTENTS("generator/hodgkin_huxley_squid_axon_model_1952/model.dae.external.c", generator->implementationCode());

    profile = libcellml::GeneratorProfile::create(libcellml::GeneratorProfile::Profile::PYTHON);

    generator->setProfile(profile);

    EXPECT_EQ_FILE_CONTENTS("generator/hodgkin_huxley_squid_axon_model_1952/model.dae.external.py", generator->implementationCode());

    auto interpreter = libcellml::Interpreter::create();

    interpreter->setModel(analyserModel);

    INITIALISE_INTERPRETED_DIFFERENTIAL_MODEL(analyserModel);

    EXPECT_EQ_VALUES(std::vector<double>({0.0, 0.6, 0.05, 0.325}), states, analyserModel->stateCount());
    EXPECT_EQ_VALUES(std::vector<double>({0.0, 0.0, 0.0, 0.0}), rates, analyserModel->stateCount());
    EXPECT_EQ_VALUES(std::vector<double>({0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.3, 0.0, 120.0, 0.0, 0.0, 0.0, 0.0, 0.0, 36.0, 0.0, 0.0}), constants, analyserModel->constantCount());
    EXPECT_EQ_VALUES(std::vector<double>({0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.3, 0.0, 120.0, 0.0, 0.0, 0.0, 0.0, 0.0, 36.0, 0.0, 0.0}), computedConstants, analyserModel->computedConstantCount());
    EXPECT_EQ_VALUES(std::vector<double>({0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.3, 0.0, 120.0, 0.0, 0.0, 0.0, 0.0, 0.0, 36.0, 0.0, 0.0}), algebraic, analyserModel->algebraicCount());

    FINALISE_MODEL();
}

TEST(Generator, nobleModel1962)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("generator/noble_model_1962/model.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    auto analyser = libcellml::Analyser::create();

    analyser->analyseModel(model);

    EXPECT_EQ(size_t(0), analyser->errorCount());

    auto analyserModel = analyser->model();
    auto generator = libcellml::Generator::create();

    generator->setModel(analyserModel);

    EXPECT_EQ_FILE_CONTENTS("generator/noble_model_1962/model.h", generator->interfaceCode());
    EXPECT_EQ_FILE_CONTENTS("generator/noble_model_1962/model.c", generator->implementationCode());

    auto profile = libcellml::GeneratorProfile::create(libcellml::GeneratorProfile::Profile::PYTHON);

    generator->setProfile(profile);

    EXPECT_EQ_FILE_CONTENTS("generator/noble_model_1962/model.py", generator->implementationCode());

    auto interpreter = libcellml::Interpreter::create();

    interpreter->setModel(analyserModel);

    INITIALISE_INTERPRETED_DIFFERENTIAL_MODEL(analyserModel);

    EXPECT_EQ_VALUES(std::vector<double>({-87.0, 0.01, 0.8, 0.01}), states, analyserModel->stateCount());
    EXPECT_EQ_VALUES(std::vector<double>({0.41242627135769938, 0.21497864158814481, 0.020474517093977421, 7.3594167713619075e-05}), rates, analyserModel->stateCount());
    EXPECT_EQ_VALUES(std::vector<double>({-17.82064, -2.025, 14.896524743707609, 12.0, 0.075, -60.0, 0.00032, 400.0, 40.0, 0.31290773193785848, 9.4800013030335055, 0.14632035599225984, 0.01098694263059318, 1.145886506746739, 1.2e-08, 9.3796016230338899e-05, 0.0019263888354416436}), constants, analyserModel->constantCount());
    EXPECT_EQ_VALUES(std::vector<double>({-17.82064, -2.025, 14.896524743707609, 12.0, 0.075, -60.0, 0.00032, 400.0, 40.0, 0.31290773193785848, 9.4800013030335055, 0.14632035599225984, 0.01098694263059318, 1.145886506746739, 1.2e-08, 9.3796016230338899e-05, 0.0019263888354416436}), computedConstants, analyserModel->computedConstantCount());
    EXPECT_EQ_VALUES(std::vector<double>({-17.82064, -2.025, 14.896524743707609, 12.0, 0.075, -60.0, 0.00032, 400.0, 40.0, 0.31290773193785848, 9.4800013030335055, 0.14632035599225984, 0.01098694263059318, 1.145886506746739, 1.2e-08, 9.3796016230338899e-05, 0.0019263888354416436}), algebraic, analyserModel->algebraicCount());

    FINALISE_MODEL();
}

TEST(Generator, robertsonOdeModel1966)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("generator/robertson_model_1966/model.ode.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    auto analyser = libcellml::Analyser::create();

    analyser->analyseModel(model);

    EXPECT_EQ(size_t(0), analyser->errorCount());

    auto analyserModel = analyser->model();
    auto generator = libcellml::Generator::create();

    generator->setModel(analyserModel);

    auto profile = generator->profile();

    profile->setInterfaceFileNameString("model.ode.h");

    EXPECT_EQ_FILE_CONTENTS("generator/robertson_model_1966/model.ode.h", generator->interfaceCode());
    EXPECT_EQ_FILE_CONTENTS("generator/robertson_model_1966/model.ode.c", generator->implementationCode());

    profile = libcellml::GeneratorProfile::create(libcellml::GeneratorProfile::Profile::PYTHON);

    generator->setProfile(profile);

    EXPECT_EQ_FILE_CONTENTS("generator/robertson_model_1966/model.ode.py", generator->implementationCode());

    auto interpreter = libcellml::Interpreter::create();

    interpreter->setModel(analyserModel);

    INITIALISE_INTERPRETED_DIFFERENTIAL_MODEL(analyserModel);

    EXPECT_EQ_VALUES(std::vector<double>({1.0, 0.0, 0.0}), states, analyserModel->stateCount());
    EXPECT_EQ_VALUES(std::vector<double>({-0.04, 0.0, 0.04}), rates, analyserModel->stateCount());
    EXPECT_EQ_VALUES(std::vector<double>({0.04, 10000.0, 30000000.0, 0.0}), constants, analyserModel->constantCount());
    EXPECT_EQ_VALUES(std::vector<double>({0.04, 10000.0, 30000000.0, 0.0}), computedConstants, analyserModel->computedConstantCount());
    EXPECT_EQ_VALUES(std::vector<double>({0.04, 10000.0, 30000000.0, 0.0}), algebraic, analyserModel->algebraicCount());

    FINALISE_MODEL();
}

TEST(Generator, robertsonDaeModel1966)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("generator/robertson_model_1966/model.dae.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    auto analyser = libcellml::Analyser::create();

    analyser->analyseModel(model);

    EXPECT_EQ(size_t(0), analyser->errorCount());

    auto analyserModel = analyser->model();
    auto generator = libcellml::Generator::create();

    generator->setModel(analyserModel);

    auto profile = generator->profile();

    profile->setInterfaceFileNameString("model.dae.h");

    EXPECT_EQ_FILE_CONTENTS("generator/robertson_model_1966/model.dae.h", generator->interfaceCode());
    EXPECT_EQ_FILE_CONTENTS("generator/robertson_model_1966/model.dae.c", generator->implementationCode());

    profile = libcellml::GeneratorProfile::create(libcellml::GeneratorProfile::Profile::PYTHON);

    generator->setProfile(profile);

    EXPECT_EQ_FILE_CONTENTS("generator/robertson_model_1966/model.dae.py", generator->implementationCode());

    auto interpreter = libcellml::Interpreter::create();

    interpreter->setModel(analyserModel);

    INITIALISE_INTERPRETED_DIFFERENTIAL_MODEL(analyserModel);

    EXPECT_EQ_VALUES(std::vector<double>({1.0, 0.0}), states, analyserModel->stateCount());
    EXPECT_EQ_VALUES(std::vector<double>({-0.04, 0.04}), rates, analyserModel->stateCount());
    EXPECT_EQ_VALUES(std::vector<double>({0.04, 10000.0, 0.0, 30000000.0, 0.0}), constants, analyserModel->constantCount());
    EXPECT_EQ_VALUES(std::vector<double>({0.04, 10000.0, 0.0, 30000000.0, 0.0}), computedConstants, analyserModel->computedConstantCount());
    EXPECT_EQ_VALUES(std::vector<double>({0.04, 10000.0, 0.0, 30000000.0, 0.0}), algebraic, analyserModel->algebraicCount());

    FINALISE_MODEL();
}

TEST(Generator, sineImports)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("sine_approximations_import.xml"));
    auto importer = libcellml::Importer::create();

    EXPECT_EQ(size_t(0), parser->issueCount());
    EXPECT_TRUE(model->hasUnresolvedImports());

    importer->resolveImports(model, resourcePath());

    EXPECT_FALSE(model->hasUnresolvedImports());

    model = importer->flattenModel(model);

    auto analyser = libcellml::Analyser::create();

    analyser->analyseModel(model);

    EXPECT_EQ(size_t(0), analyser->errorCount());

    auto analyserModel = analyser->model();
    auto generator = libcellml::Generator::create();

    generator->setModel(analyserModel);

    EXPECT_EQ_FILE_CONTENTS("generator/sine_model_imports/model.h", generator->interfaceCode());
    EXPECT_EQ_FILE_CONTENTS("generator/sine_model_imports/model.c", generator->implementationCode());

    auto profile = libcellml::GeneratorProfile::create(libcellml::GeneratorProfile::Profile::PYTHON);

    generator->setProfile(profile);

    EXPECT_EQ_FILE_CONTENTS("generator/sine_model_imports/model.py", generator->implementationCode());

    auto interpreter = libcellml::Interpreter::create();

    interpreter->setModel(analyserModel);

    INITIALISE_INTERPRETED_DIFFERENTIAL_MODEL(analyserModel);

    EXPECT_EQ_VALUES(std::vector<double>({0.0}), states, analyserModel->stateCount());
    EXPECT_EQ_VALUES(std::vector<double>({1.0}), rates, analyserModel->stateCount());
    EXPECT_EQ_VALUES(std::vector<double>({0.0, 0.0, 0.0, 0.75, 0.63661977236758138, 6.2831853071795862, 1.5707963267948966, 3.1415926535897931, 4.7123889803846897, -0.5}), constants, analyserModel->constantCount());
    EXPECT_EQ_VALUES(std::vector<double>({0.0, 0.0, 0.0, 0.75, 0.63661977236758138, 6.2831853071795862, 1.5707963267948966, 3.1415926535897931, 4.7123889803846897, -0.5}), computedConstants, analyserModel->computedConstantCount());
    EXPECT_EQ_VALUES(std::vector<double>({0.0, 0.0, 0.0, 0.75, 0.63661977236758138, 6.2831853071795862, 1.5707963267948966, 3.1415926535897931, 4.7123889803846897, -0.5}), algebraic, analyserModel->algebraicCount());

    FINALISE_MODEL();
}

TEST(Generator, analyserModelScopeTest)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("generator/hodgkin_huxley_squid_axon_model_1952/model.cellml"));

    libcellml::AnalyserModelPtr analyserModel = nullptr;

    {
        auto analyser = libcellml::Analyser::create();

        analyser->analyseModel(model);

        EXPECT_EQ(size_t(0), analyser->errorCount());

        analyserModel = analyser->model();
    }

    auto generator = libcellml::Generator::create();

    generator->setModel(analyserModel);

    EXPECT_EQ_FILE_CONTENTS("generator/hodgkin_huxley_squid_axon_model_1952/model.h", generator->interfaceCode());
    EXPECT_EQ_FILE_CONTENTS("generator/hodgkin_huxley_squid_axon_model_1952/model.c", generator->implementationCode());

    auto interpreter = libcellml::Interpreter::create();

    interpreter->setModel(analyserModel);

    INITIALISE_INTERPRETED_DIFFERENTIAL_MODEL(analyserModel);

    EXPECT_EQ_VALUES(std::vector<double>({0.0, 0.6, 0.05, 0.325}), states, analyserModel->stateCount());
    EXPECT_EQ_VALUES(std::vector<double>({0.60076874999999963, -0.00045552390654006458, 0.012385538355398518, -0.0013415722863204596}), rates, analyserModel->stateCount());
    EXPECT_EQ_VALUES(std::vector<double>({0.0, 3.1839, -4.81966875, 1.035, 1.0, 0.0, -10.613, 0.3, -115.0, 120.0, 0.22356372458463003, 4.0, 0.07, 0.047425873177566781, 12.0, 36.0, 0.05819767068693265, 0.125}), constants, analyserModel->constantCount());
    EXPECT_EQ_VALUES(std::vector<double>({0.0, 3.1839, -4.81966875, 1.035, 1.0, 0.0, -10.613, 0.3, -115.0, 120.0, 0.22356372458463003, 4.0, 0.07, 0.047425873177566781, 12.0, 36.0, 0.05819767068693265, 0.125}), computedConstants, analyserModel->computedConstantCount());
    EXPECT_EQ_VALUES(std::vector<double>({0.0, 3.1839, -4.81966875, 1.035, 1.0, 0.0, -10.613, 0.3, -115.0, 120.0, 0.22356372458463003, 4.0, 0.07, 0.047425873177566781, 12.0, 36.0, 0.05819767068693265, 0.125}), algebraic, analyserModel->algebraicCount());

    FINALISE_MODEL();
}

TEST(Generator, daeModel)
{
    auto parser = libcellml::Parser::create(false);
    auto model = parser->parseModel(fileContents("generator/dae_cellml_1_1_model/model.cellml"));

    EXPECT_EQ(size_t(0), parser->errorCount());

    auto analyser = libcellml::Analyser::create();

    analyser->analyseModel(model);

    EXPECT_EQ(size_t(0), analyser->errorCount());

    auto analyserModel = analyser->model();
    auto generator = libcellml::Generator::create();

    generator->setModel(analyserModel);

    EXPECT_EQ_FILE_CONTENTS("generator/dae_cellml_1_1_model/model.h", generator->interfaceCode());
    EXPECT_EQ_FILE_CONTENTS("generator/dae_cellml_1_1_model/model.c", generator->implementationCode());

    auto profile = libcellml::GeneratorProfile::create(libcellml::GeneratorProfile::Profile::PYTHON);

    generator->setProfile(profile);

    EXPECT_EQ_FILE_CONTENTS("generator/dae_cellml_1_1_model/model.py", generator->implementationCode());

    auto interpreter = libcellml::Interpreter::create();

    interpreter->setModel(analyserModel);

    INITIALISE_INTERPRETED_DIFFERENTIAL_MODEL(analyserModel);

    EXPECT_EQ_VALUES(std::vector<double>({1.0, 0.0}), states, analyserModel->stateCount());
    EXPECT_EQ_VALUES(std::vector<double>({0.0, 0.0}), rates, analyserModel->stateCount());
    EXPECT_EQ_VALUES(std::vector<double>({0.0, 1.0, 1.0, 1.0, 0.05, 2.0, 0.0, 20.0, 2.0, 10.0}), constants, analyserModel->constantCount());
    EXPECT_EQ_VALUES(std::vector<double>({0.0, 1.0, 1.0, 1.0, 0.05, 2.0, 0.0, 20.0, 2.0, 10.0}), computedConstants, analyserModel->computedConstantCount());
    EXPECT_EQ_VALUES(std::vector<double>({0.0, 1.0, 1.0, 1.0, 0.05, 2.0, 0.0, 20.0, 2.0, 10.0}), algebraic, analyserModel->algebraicCount());

    FINALISE_MODEL();
}

TEST(Generator, variableInitialisedUsingAConstant)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("generator/variable_initialised_using_a_constant/model.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    auto analyser = libcellml::Analyser::create();

    analyser->analyseModel(model);

    EXPECT_EQ(size_t(0), analyser->errorCount());

    auto analyserModel = analyser->model();
    auto generator = libcellml::Generator::create();

    generator->setModel(analyserModel);

    EXPECT_EQ_FILE_CONTENTS("generator/variable_initialised_using_a_constant/model.h", generator->interfaceCode());
    EXPECT_EQ_FILE_CONTENTS("generator/variable_initialised_using_a_constant/model.c", generator->implementationCode());

    auto profile = libcellml::GeneratorProfile::create(libcellml::GeneratorProfile::Profile::PYTHON);

    generator->setProfile(profile);

    EXPECT_EQ_FILE_CONTENTS("generator/variable_initialised_using_a_constant/model.py", generator->implementationCode());

    auto interpreter = libcellml::Interpreter::create();

    interpreter->setModel(analyserModel);

    INITIALISE_INTERPRETED_DIFFERENTIAL_MODEL(analyserModel);

    EXPECT_EQ_VALUES(std::vector<double>({7.0}), states, analyserModel->stateCount());
    EXPECT_EQ_VALUES(std::vector<double>({3.0}), rates, analyserModel->stateCount());
    EXPECT_EQ_VALUES(std::vector<double>({7.0}), constants, analyserModel->constantCount());
    EXPECT_EQ_VALUES(std::vector<double>({7.0}), computedConstants, analyserModel->computedConstantCount());
    EXPECT_EQ_VALUES(std::vector<double>({7.0}), algebraic, analyserModel->algebraicCount());

    FINALISE_MODEL();
}

TEST(Generator, modelOutOfScope)
{
    libcellml::AnalyserModelPtr analyserModel;

    {
        auto analyser = libcellml::Analyser::create();
        auto parser = libcellml::Parser::create();
        auto model = parser->parseModel(fileContents("generator/ode_multiple_dependent_odes/model.cellml"));

        EXPECT_EQ(size_t(0), parser->issueCount());

        analyser->analyseModel(model);

        EXPECT_EQ(size_t(0), analyser->errorCount());

        analyserModel = analyser->model();
    }

    auto generator = libcellml::Generator::create();

    generator->setModel(analyserModel);

    auto profile = libcellml::GeneratorProfile::create(libcellml::GeneratorProfile::Profile::PYTHON);

    generator->setProfile(profile);

    EXPECT_EQ_FILE_CONTENTS("generator/ode_multiple_dependent_odes/model.py", generator->implementationCode());

    auto interpreter = libcellml::Interpreter::create();

    interpreter->setModel(analyserModel);

    INITIALISE_INTERPRETED_DIFFERENTIAL_MODEL(analyserModel);

    EXPECT_EQ_VALUES(std::vector<double>({-2.0, 0.0}), states, analyserModel->stateCount());
    EXPECT_EQ_VALUES(std::vector<double>({0.0, 2.0}), rates, analyserModel->stateCount());
    EXPECT_EQ_VALUES(std::vector<double>({1.0}), constants, analyserModel->constantCount());
    EXPECT_EQ_VALUES(std::vector<double>({1.0}), computedConstants, analyserModel->computedConstantCount());
    EXPECT_EQ_VALUES(std::vector<double>({1.0}), algebraic, analyserModel->algebraicCount());

    FINALISE_MODEL();
}

TEST(Generator, unknownVariableMarkedAsExternalVariable)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("generator/unknown_variable_as_external_variable/model.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    auto analyser = libcellml::Analyser::create();

    analyser->addExternalVariable(libcellml::AnalyserExternalVariable::create(model->component("SLC_template3_ss")->variable("P_3")));

    analyser->analyseModel(model);

    EXPECT_EQ(size_t(0), analyser->errorCount());

    auto analyserModel = analyser->model();
    auto generator = libcellml::Generator::create();

    generator->setModel(analyserModel);

    EXPECT_EQ_FILE_CONTENTS("generator/unknown_variable_as_external_variable/model.h", generator->interfaceCode());
    EXPECT_EQ_FILE_CONTENTS("generator/unknown_variable_as_external_variable/model.c", generator->implementationCode());

    auto profile = libcellml::GeneratorProfile::create(libcellml::GeneratorProfile::Profile::PYTHON);

    generator->setProfile(profile);

    EXPECT_EQ_FILE_CONTENTS("generator/unknown_variable_as_external_variable/model.py", generator->implementationCode());

    auto interpreter = libcellml::Interpreter::create();

    interpreter->setModel(analyserModel);

    INITIALISE_INTERPRETED_ALGEBRAIC_MODEL(analyserModel);

    EXPECT_EQ_VALUES(std::vector<double>({NAN, 1.1, 21262500.0, 150.0, 3402000.0, 2.0, 2902500.0, 810000.0, 247140.0, NAN}), constants, analyserModel->constantCount());
    EXPECT_EQ_VALUES(std::vector<double>({NAN, 1.1, 21262500.0, 150.0, 3402000.0, 2.0, 2902500.0, 810000.0, 247140.0, NAN}), computedConstants, analyserModel->computedConstantCount());
    EXPECT_EQ_VALUES(std::vector<double>({NAN, 1.1, 21262500.0, 150.0, 3402000.0, 2.0, 2902500.0, 810000.0, 247140.0, NAN}), algebraic, analyserModel->algebraicCount());

    FINALISE_MODEL();
}

TEST(Generator, modelWithComplexUnitsOutOfScope)
{
    libcellml::AnalyserModelPtr analyserModel;

    {
        auto analyser = libcellml::Analyser::create();
        auto parser = libcellml::Parser::create();
        auto importer = libcellml::Importer::create();
        auto model = parser->parseModel(fileContents("generator/cellml_slc_example/slc_model.cellml"));

        EXPECT_EQ(size_t(0), parser->issueCount());

        importer->resolveImports(model, resourcePath("generator/cellml_slc_example"));
        EXPECT_FALSE(model->hasUnresolvedImports());

        model = importer->flattenModel(model);

        analyser->analyseModel(model);
        EXPECT_EQ(size_t(0), analyser->errorCount());

        analyserModel = analyser->model();
    }

    auto generator = libcellml::Generator::create();

    generator->setModel(analyserModel);

    auto profile = libcellml::GeneratorProfile::create(libcellml::GeneratorProfile::Profile::PYTHON);

    generator->setProfile(profile);

    EXPECT_EQ_FILE_CONTENTS("generator/cellml_slc_example/model.py", generator->implementationCode());

    auto interpreter = libcellml::Interpreter::create();

    interpreter->setModel(analyserModel);

    INITIALISE_INTERPRETED_ALGEBRAIC_MODEL(analyserModel);

    EXPECT_EQ_VALUES(std::vector<double>({6.7828154425612066, 1.1, 21262500.0, 150.0, 3402000.0, 2.0, 2902500.0, 810000.0, 247140.0, 2902500.0}), constants, analyserModel->constantCount());
    EXPECT_EQ_VALUES(std::vector<double>({6.7828154425612066, 1.1, 21262500.0, 150.0, 3402000.0, 2.0, 2902500.0, 810000.0, 247140.0, 2902500.0}), computedConstants, analyserModel->computedConstantCount());
    EXPECT_EQ_VALUES(std::vector<double>({6.7828154425612066, 1.1, 21262500.0, 150.0, 3402000.0, 2.0, 2902500.0, 810000.0, 247140.0, 2902500.0}), algebraic, analyserModel->algebraicCount());

    FINALISE_MODEL();
}

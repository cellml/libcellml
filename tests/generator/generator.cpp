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

#include "libcellml/undefines.h"

static const std::string EMPTY_STRING;
static const std::vector<double> NO_VALUES;
static const auto NAN = std::numeric_limits<double>::quiet_NaN();
static const auto NAN_x_1 = std::vector<double>(1, NAN);
static const auto NAN_x_2 = std::vector<double>(2, NAN);
static const auto NAN_x_3 = std::vector<double>(3, NAN);
static const auto NAN_x_4 = std::vector<double>(4, NAN);
static const auto NAN_x_5 = std::vector<double>(5, NAN);
static const auto NAN_x_6 = std::vector<double>(6, NAN);
static const auto NAN_x_10 = std::vector<double>(10, NAN);
static const auto NAN_x_15 = std::vector<double>(15, NAN);
static const auto NAN_x_17 = std::vector<double>(17, NAN);
static const auto NAN_x_18 = std::vector<double>(18, NAN);
static const auto NAN_x_19 = std::vector<double>(19, NAN);
static const auto NAN_x_20 = std::vector<double>(20, NAN);
static const auto NAN_x_33 = std::vector<double>(33, NAN);
static const auto NAN_x_185 = std::vector<double>(185, NAN);
static const auto NAN_x_217 = std::vector<double>(217, NAN);

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

    auto interpreter = libcellml::Interpreter::create();

    interpreter->setModel(analyserModel);

    EXPECT_EQ(0.0, interpreter->voi());

    EXPECT_EQ(size_t(0), interpreter->states().size());
    EXPECT_EQ(size_t(0), interpreter->rates().size());
    EXPECT_EQ(size_t(0), interpreter->variables().size());
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

    EXPECT_EQ(fileContents("generator/algebraic_eqn_computed_var_on_rhs/model.h"), generator->interfaceCode());
    EXPECT_EQ(fileContents("generator/algebraic_eqn_computed_var_on_rhs/model.c"), generator->implementationCode());

    auto profile = libcellml::GeneratorProfile::create(libcellml::GeneratorProfile::Profile::PYTHON);

    generator->setProfile(profile);

    EXPECT_EQ(fileContents("generator/algebraic_eqn_computed_var_on_rhs/model.py"), generator->implementationCode());

    auto interpreter = libcellml::Interpreter::create();

    interpreter->setModel(analyserModel);

    EXPECT_EQ(0.0, interpreter->voi());
    EXPECT_EQ_VALUES(NO_VALUES, interpreter->states());
    EXPECT_EQ_VALUES(NO_VALUES, interpreter->rates());
    EXPECT_EQ_VALUES(NAN_x_2, interpreter->variables());

    interpreter->initialiseVariables();
    interpreter->computeComputedConstants();
    interpreter->computeRates();
    interpreter->computeVariables();

    EXPECT_EQ_VALUES(NO_VALUES, interpreter->states());
    EXPECT_EQ_VALUES(NO_VALUES, interpreter->rates());
    EXPECT_EQ_VALUES(std::vector<double>({NAN, 1.0}), interpreter->variables());
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

    EXPECT_EQ(fileContents("generator/algebraic_eqn_computed_var_on_rhs/model.external.h"), generator->interfaceCode());
    EXPECT_EQ(fileContents("generator/algebraic_eqn_computed_var_on_rhs/model.external.c"), generator->implementationCode());

    profile = libcellml::GeneratorProfile::create(libcellml::GeneratorProfile::Profile::PYTHON);

    generator->setProfile(profile);

    EXPECT_EQ(fileContents("generator/algebraic_eqn_computed_var_on_rhs/model.external.py"), generator->implementationCode());

    auto interpreter = libcellml::Interpreter::create();

    interpreter->setModel(analyserModel);

    EXPECT_EQ(0.0, interpreter->voi());
    EXPECT_EQ_VALUES(NO_VALUES, interpreter->states());
    EXPECT_EQ_VALUES(NO_VALUES, interpreter->rates());
    EXPECT_EQ_VALUES(NAN_x_2, interpreter->variables());

    interpreter->initialiseVariables();
    interpreter->computeComputedConstants();
    interpreter->computeRates();
    interpreter->computeVariables();

    EXPECT_EQ_VALUES(NO_VALUES, interpreter->states());
    EXPECT_EQ_VALUES(NO_VALUES, interpreter->rates());
    EXPECT_EQ_VALUES(NAN_x_2, interpreter->variables());
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

    EXPECT_EQ(fileContents("generator/algebraic_eqn_const_var_on_rhs/model.h"), generator->interfaceCode());
    EXPECT_EQ(fileContents("generator/algebraic_eqn_const_var_on_rhs/model.c"), generator->implementationCode());

    auto profile = libcellml::GeneratorProfile::create(libcellml::GeneratorProfile::Profile::PYTHON);

    generator->setProfile(profile);

    EXPECT_EQ(fileContents("generator/algebraic_eqn_const_var_on_rhs/model.py"), generator->implementationCode());

    auto interpreter = libcellml::Interpreter::create();

    interpreter->setModel(analyserModel);

    EXPECT_EQ(0.0, interpreter->voi());
    EXPECT_EQ_VALUES(NO_VALUES, interpreter->states());
    EXPECT_EQ_VALUES(NO_VALUES, interpreter->rates());
    EXPECT_EQ_VALUES(NAN_x_2, interpreter->variables());

    interpreter->initialiseVariables();
    interpreter->computeComputedConstants();
    interpreter->computeRates();
    interpreter->computeVariables();

    EXPECT_EQ_VALUES(NO_VALUES, interpreter->states());
    EXPECT_EQ_VALUES(NO_VALUES, interpreter->rates());
    EXPECT_EQ_VALUES(std::vector<double>({NAN, 1.0}), interpreter->variables());
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

    EXPECT_EQ(fileContents("generator/algebraic_eqn_constant_on_rhs/model.h"), generator->interfaceCode());
    EXPECT_EQ(fileContents("generator/algebraic_eqn_constant_on_rhs/model.c"), generator->implementationCode());

    auto profile = libcellml::GeneratorProfile::create(libcellml::GeneratorProfile::Profile::PYTHON);

    generator->setProfile(profile);

    EXPECT_EQ(fileContents("generator/algebraic_eqn_constant_on_rhs/model.py"), generator->implementationCode());

    auto interpreter = libcellml::Interpreter::create();

    interpreter->setModel(analyserModel);

    EXPECT_EQ(0.0, interpreter->voi());
    EXPECT_EQ_VALUES(NO_VALUES, interpreter->states());
    EXPECT_EQ_VALUES(NO_VALUES, interpreter->rates());
    EXPECT_EQ_VALUES(NAN_x_1, interpreter->variables());

    interpreter->initialiseVariables();
    interpreter->computeComputedConstants();
    interpreter->computeRates();
    interpreter->computeVariables();

    EXPECT_EQ_VALUES(NO_VALUES, interpreter->states());
    EXPECT_EQ_VALUES(NO_VALUES, interpreter->rates());
    EXPECT_EQ_VALUES(std::vector<double>({1.0}), interpreter->variables());
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

    EXPECT_EQ(fileContents("generator/algebraic_eqn_derivative_on_rhs/model.h"), generator->interfaceCode());
    EXPECT_EQ(fileContents("generator/algebraic_eqn_derivative_on_rhs/model.c"), generator->implementationCode());

    auto profile = libcellml::GeneratorProfile::create(libcellml::GeneratorProfile::Profile::PYTHON);

    generator->setProfile(profile);

    EXPECT_EQ(fileContents("generator/algebraic_eqn_derivative_on_rhs/model.py"), generator->implementationCode());

    auto interpreter = libcellml::Interpreter::create();

    interpreter->setModel(analyserModel);

    EXPECT_EQ(0.0, interpreter->voi());
    EXPECT_EQ_VALUES(NAN_x_1, interpreter->states());
    EXPECT_EQ_VALUES(NAN_x_1, interpreter->rates());
    EXPECT_EQ_VALUES(NAN_x_2, interpreter->variables());

    interpreter->initialiseVariables();
    interpreter->computeComputedConstants();
    interpreter->computeRates();
    interpreter->computeVariables();

    EXPECT_EQ_VALUES(std::vector<double>({1.0}), interpreter->states());
    EXPECT_EQ_VALUES(NAN_x_1, interpreter->rates());
    EXPECT_EQ_VALUES(std::vector<double>({1.0, NAN}), interpreter->variables());
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

    EXPECT_EQ(fileContents("generator/algebraic_eqn_derivative_on_rhs_one_component/model.h"), generator->interfaceCode());
    EXPECT_EQ(fileContents("generator/algebraic_eqn_derivative_on_rhs_one_component/model.c"), generator->implementationCode());

    auto profile = libcellml::GeneratorProfile::create(libcellml::GeneratorProfile::Profile::PYTHON);

    generator->setProfile(profile);

    EXPECT_EQ(fileContents("generator/algebraic_eqn_derivative_on_rhs_one_component/model.py"), generator->implementationCode());

    auto interpreter = libcellml::Interpreter::create();

    interpreter->setModel(analyserModel);

    EXPECT_EQ(0.0, interpreter->voi());
    EXPECT_EQ_VALUES(NAN_x_1, interpreter->states());
    EXPECT_EQ_VALUES(NAN_x_1, interpreter->rates());
    EXPECT_EQ_VALUES(NAN_x_2, interpreter->variables());

    interpreter->initialiseVariables();
    interpreter->computeComputedConstants();
    interpreter->computeRates();
    interpreter->computeVariables();

    EXPECT_EQ_VALUES(std::vector<double>({1.0}), interpreter->states());
    EXPECT_EQ_VALUES(NAN_x_1, interpreter->rates());
    EXPECT_EQ_VALUES(std::vector<double>({1.0, NAN}), interpreter->variables());
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

    EXPECT_EQ(fileContents("generator/algebraic_eqn_state_var_on_rhs/model.h"), generator->interfaceCode());
    EXPECT_EQ(fileContents("generator/algebraic_eqn_state_var_on_rhs/model.c"), generator->implementationCode());

    auto profile = libcellml::GeneratorProfile::create(libcellml::GeneratorProfile::Profile::PYTHON);

    generator->setProfile(profile);

    EXPECT_EQ(fileContents("generator/algebraic_eqn_state_var_on_rhs/model.py"), generator->implementationCode());

    auto interpreter = libcellml::Interpreter::create();

    interpreter->setModel(analyserModel);

    EXPECT_EQ(0.0, interpreter->voi());
    EXPECT_EQ_VALUES(NAN_x_1, interpreter->states());
    EXPECT_EQ_VALUES(NAN_x_1, interpreter->rates());
    EXPECT_EQ_VALUES(NAN_x_2, interpreter->variables());

    interpreter->initialiseVariables();
    interpreter->computeComputedConstants();
    interpreter->computeRates();
    interpreter->computeVariables();

    EXPECT_EQ_VALUES(std::vector<double>({1.0}), interpreter->states());
    EXPECT_EQ_VALUES(NAN_x_1, interpreter->rates());
    EXPECT_EQ_VALUES(std::vector<double>({1.0, NAN}), interpreter->variables());
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

    EXPECT_EQ(fileContents("generator/algebraic_eqn_state_var_on_rhs_one_component/model.h"), generator->interfaceCode());
    EXPECT_EQ(fileContents("generator/algebraic_eqn_state_var_on_rhs_one_component/model.c"), generator->implementationCode());

    auto profile = libcellml::GeneratorProfile::create(libcellml::GeneratorProfile::Profile::PYTHON);

    generator->setProfile(profile);

    EXPECT_EQ(fileContents("generator/algebraic_eqn_state_var_on_rhs_one_component/model.py"), generator->implementationCode());

    auto interpreter = libcellml::Interpreter::create();

    interpreter->setModel(analyserModel);

    EXPECT_EQ(0.0, interpreter->voi());
    EXPECT_EQ_VALUES(NAN_x_1, interpreter->states());
    EXPECT_EQ_VALUES(NAN_x_1, interpreter->rates());
    EXPECT_EQ_VALUES(NAN_x_2, interpreter->variables());

    interpreter->initialiseVariables();
    interpreter->computeComputedConstants();
    interpreter->computeRates();
    interpreter->computeVariables();

    EXPECT_EQ_VALUES(std::vector<double>({1.0}), interpreter->states());
    EXPECT_EQ_VALUES(NAN_x_1, interpreter->rates());
    EXPECT_EQ_VALUES(std::vector<double>({1.0, NAN}), interpreter->variables());
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

    EXPECT_EQ(fileContents("generator/algebraic_unknown_var_on_rhs/model.h"), generator->interfaceCode());
    EXPECT_EQ(fileContents("generator/algebraic_unknown_var_on_rhs/model.c"), generator->implementationCode());

    auto profile = libcellml::GeneratorProfile::create(libcellml::GeneratorProfile::Profile::PYTHON);

    generator->setProfile(profile);

    EXPECT_EQ(fileContents("generator/algebraic_unknown_var_on_rhs/model.py"), generator->implementationCode());

    auto interpreter = libcellml::Interpreter::create();

    interpreter->setModel(analyserModel);

    EXPECT_EQ(0.0, interpreter->voi());
    EXPECT_EQ_VALUES(NO_VALUES, interpreter->states());
    EXPECT_EQ_VALUES(NO_VALUES, interpreter->rates());
    EXPECT_EQ_VALUES(NAN_x_2, interpreter->variables());

    interpreter->initialiseVariables();
    interpreter->computeComputedConstants();
    interpreter->computeRates();
    interpreter->computeVariables();

    EXPECT_EQ_VALUES(NO_VALUES, interpreter->states());
    EXPECT_EQ_VALUES(NO_VALUES, interpreter->rates());
    EXPECT_EQ_VALUES(std::vector<double>({1.0, NAN}), interpreter->variables());
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

    EXPECT_EQ(fileContents("generator/algebraic_eqn_with_one_non_isolated_unknown/model.h"), generator->interfaceCode());
    EXPECT_EQ(fileContents("generator/algebraic_eqn_with_one_non_isolated_unknown/model.c"), generator->implementationCode());

    auto profile = libcellml::GeneratorProfile::create(libcellml::GeneratorProfile::Profile::PYTHON);

    generator->setProfile(profile);

    EXPECT_EQ(fileContents("generator/algebraic_eqn_with_one_non_isolated_unknown/model.py"), generator->implementationCode());

    auto interpreter = libcellml::Interpreter::create();

    interpreter->setModel(analyserModel);

    EXPECT_EQ(0.0, interpreter->voi());
    EXPECT_EQ_VALUES(NO_VALUES, interpreter->states());
    EXPECT_EQ_VALUES(NO_VALUES, interpreter->rates());
    EXPECT_EQ_VALUES(NAN_x_4, interpreter->variables());

    interpreter->initialiseVariables();
    interpreter->computeComputedConstants();
    interpreter->computeRates();
    interpreter->computeVariables();

    EXPECT_EQ_VALUES(NO_VALUES, interpreter->states());
    EXPECT_EQ_VALUES(NO_VALUES, interpreter->rates());
    EXPECT_EQ_VALUES(std::vector<double>({3.0, 5.0, 7.0, 1.0}), interpreter->variables());
}

TEST(Generator, algebraicEqnWithOneNonIsolatedUnknownWithExternalVariable)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("generator/algebraic_eqn_with_one_non_isolated_unknown/model.cellml"));

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

    EXPECT_EQ(fileContents("generator/algebraic_eqn_with_one_non_isolated_unknown/model.external.h"), generator->interfaceCode());
    EXPECT_EQ(fileContents("generator/algebraic_eqn_with_one_non_isolated_unknown/model.external.c"), generator->implementationCode());

    profile = libcellml::GeneratorProfile::create(libcellml::GeneratorProfile::Profile::PYTHON);

    generator->setProfile(profile);

    EXPECT_EQ(fileContents("generator/algebraic_eqn_with_one_non_isolated_unknown/model.external.py"), generator->implementationCode());

    auto interpreter = libcellml::Interpreter::create();

    interpreter->setModel(analyserModel);

    EXPECT_EQ(0.0, interpreter->voi());
    EXPECT_EQ_VALUES(NO_VALUES, interpreter->states());
    EXPECT_EQ_VALUES(NO_VALUES, interpreter->rates());
    EXPECT_EQ_VALUES(NAN_x_4, interpreter->variables());

    interpreter->initialiseVariables();
    interpreter->computeComputedConstants();
    interpreter->computeRates();
    interpreter->computeVariables();

    EXPECT_EQ_VALUES(NO_VALUES, interpreter->states());
    EXPECT_EQ_VALUES(NO_VALUES, interpreter->rates());
    EXPECT_EQ_VALUES(std::vector<double>({3.0, 5.0, 7.0, NAN}), interpreter->variables());
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

    EXPECT_EQ(fileContents("generator/algebraic_system_with_three_linked_unknowns/model.h"), generator->interfaceCode());
    EXPECT_EQ(fileContents("generator/algebraic_system_with_three_linked_unknowns/model.c"), generator->implementationCode());

    auto profile = libcellml::GeneratorProfile::create(libcellml::GeneratorProfile::Profile::PYTHON);

    generator->setProfile(profile);

    EXPECT_EQ(fileContents("generator/algebraic_system_with_three_linked_unknowns/model.py"), generator->implementationCode());

    auto interpreter = libcellml::Interpreter::create();

    interpreter->setModel(analyserModel);

    EXPECT_EQ(0.0, interpreter->voi());
    EXPECT_EQ_VALUES(NO_VALUES, interpreter->states());
    EXPECT_EQ_VALUES(NO_VALUES, interpreter->rates());
    EXPECT_EQ_VALUES(NAN_x_3, interpreter->variables());

    interpreter->initialiseVariables();
    interpreter->computeComputedConstants();
    interpreter->computeRates();
    interpreter->computeVariables();

    EXPECT_EQ_VALUES(NO_VALUES, interpreter->states());
    EXPECT_EQ_VALUES(NO_VALUES, interpreter->rates());
    EXPECT_EQ_VALUES(std::vector<double>({1.0, 1.0, 1.0}), interpreter->variables());
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

    profile->setInterfaceFileNameString("model.three.externals.h");

    EXPECT_EQ(fileContents("generator/algebraic_system_with_three_linked_unknowns/model.three.externals.h"), generator->interfaceCode());
    EXPECT_EQ(fileContents("generator/algebraic_system_with_three_linked_unknowns/model.three.externals.c"), generator->implementationCode());

    profile = libcellml::GeneratorProfile::create(libcellml::GeneratorProfile::Profile::PYTHON);

    generator->setProfile(profile);

    EXPECT_EQ(fileContents("generator/algebraic_system_with_three_linked_unknowns/model.three.externals.py"), generator->implementationCode());

    auto interpreter = libcellml::Interpreter::create();

    interpreter->setModel(analyserModel);

    EXPECT_EQ(0.0, interpreter->voi());
    EXPECT_EQ_VALUES(NO_VALUES, interpreter->states());
    EXPECT_EQ_VALUES(NO_VALUES, interpreter->rates());
    EXPECT_EQ_VALUES(NAN_x_3, interpreter->variables());

    interpreter->initialiseVariables();
    interpreter->computeComputedConstants();
    interpreter->computeRates();
    interpreter->computeVariables();

    EXPECT_EQ_VALUES(NO_VALUES, interpreter->states());
    EXPECT_EQ_VALUES(NO_VALUES, interpreter->rates());
    EXPECT_EQ_VALUES(NAN_x_3, interpreter->variables());
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

    EXPECT_EQ(fileContents("generator/algebraic_system_with_various_dependencies/model.ordered.h"), generator->interfaceCode());
    EXPECT_EQ(fileContents("generator/algebraic_system_with_various_dependencies/model.ordered.c"), generator->implementationCode());

    profile = libcellml::GeneratorProfile::create(libcellml::GeneratorProfile::Profile::PYTHON);

    generator->setProfile(profile);

    EXPECT_EQ(fileContents("generator/algebraic_system_with_various_dependencies/model.ordered.py"), generator->implementationCode());

    auto interpreter = libcellml::Interpreter::create();

    interpreter->setModel(analyserModel);

    EXPECT_EQ(0.0, interpreter->voi());
    EXPECT_EQ_VALUES(NO_VALUES, interpreter->states());
    EXPECT_EQ_VALUES(NO_VALUES, interpreter->rates());
    EXPECT_EQ_VALUES(NAN_x_6, interpreter->variables());

    interpreter->initialiseVariables();
    interpreter->computeComputedConstants();
    interpreter->computeRates();
    interpreter->computeVariables();

    EXPECT_EQ_VALUES(NO_VALUES, interpreter->states());
    EXPECT_EQ_VALUES(NO_VALUES, interpreter->rates());
    EXPECT_EQ_VALUES(std::vector<double>({NAN, 3.0, 5.0, 1.0, 1.0, NAN}), interpreter->variables());
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

    EXPECT_EQ(fileContents("generator/algebraic_system_with_various_dependencies/model.not.ordered.h"), generator->interfaceCode());
    EXPECT_EQ(fileContents("generator/algebraic_system_with_various_dependencies/model.not.ordered.c"), generator->implementationCode());

    profile = libcellml::GeneratorProfile::create(libcellml::GeneratorProfile::Profile::PYTHON);

    generator->setProfile(profile);

    EXPECT_EQ(fileContents("generator/algebraic_system_with_various_dependencies/model.not.ordered.py"), generator->implementationCode());

    auto interpreter = libcellml::Interpreter::create();

    interpreter->setModel(analyserModel);

    EXPECT_EQ(0.0, interpreter->voi());
    EXPECT_EQ_VALUES(NO_VALUES, interpreter->states());
    EXPECT_EQ_VALUES(NO_VALUES, interpreter->rates());
    EXPECT_EQ_VALUES(NAN_x_6, interpreter->variables());

    interpreter->initialiseVariables();
    interpreter->computeComputedConstants();
    interpreter->computeRates();
    interpreter->computeVariables();

    EXPECT_EQ_VALUES(NO_VALUES, interpreter->states());
    EXPECT_EQ_VALUES(NO_VALUES, interpreter->rates());
    EXPECT_EQ_VALUES(std::vector<double>({NAN, 1.0, 1.0, NAN, 3.0, 5.0}), interpreter->variables());
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

    EXPECT_EQ(fileContents("generator/ode_computed_var_on_rhs/model.h"), generator->interfaceCode());
    EXPECT_EQ(fileContents("generator/ode_computed_var_on_rhs/model.c"), generator->implementationCode());

    auto profile = libcellml::GeneratorProfile::create(libcellml::GeneratorProfile::Profile::PYTHON);

    generator->setProfile(profile);

    EXPECT_EQ(fileContents("generator/ode_computed_var_on_rhs/model.py"), generator->implementationCode());

    auto interpreter = libcellml::Interpreter::create();

    interpreter->setModel(analyserModel);

    EXPECT_EQ(0.0, interpreter->voi());
    EXPECT_EQ_VALUES(NAN_x_1, interpreter->states());
    EXPECT_EQ_VALUES(NAN_x_1, interpreter->rates());
    EXPECT_EQ_VALUES(NAN_x_1, interpreter->variables());

    interpreter->initialiseVariables();
    interpreter->computeComputedConstants();
    interpreter->computeRates();
    interpreter->computeVariables();

    EXPECT_EQ_VALUES(std::vector<double>({1.0}), interpreter->states());
    EXPECT_EQ_VALUES(NAN_x_1, interpreter->rates());
    EXPECT_EQ_VALUES(std::vector<double>({1.0}), interpreter->variables());
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

    EXPECT_EQ(fileContents("generator/ode_computed_var_on_rhs_one_component/model.h"), generator->interfaceCode());
    EXPECT_EQ(fileContents("generator/ode_computed_var_on_rhs_one_component/model.c"), generator->implementationCode());

    auto profile = libcellml::GeneratorProfile::create(libcellml::GeneratorProfile::Profile::PYTHON);

    generator->setProfile(profile);

    EXPECT_EQ(fileContents("generator/ode_computed_var_on_rhs_one_component/model.py"), generator->implementationCode());

    auto interpreter = libcellml::Interpreter::create();

    interpreter->setModel(analyserModel);

    EXPECT_EQ(0.0, interpreter->voi());
    EXPECT_EQ_VALUES(NAN_x_1, interpreter->states());
    EXPECT_EQ_VALUES(NAN_x_1, interpreter->rates());
    EXPECT_EQ_VALUES(NAN_x_1, interpreter->variables());

    interpreter->initialiseVariables();
    interpreter->computeComputedConstants();
    interpreter->computeRates();
    interpreter->computeVariables();

    EXPECT_EQ_VALUES(std::vector<double>({1.0}), interpreter->states());
    EXPECT_EQ_VALUES(NAN_x_1, interpreter->rates());
    EXPECT_EQ_VALUES(std::vector<double>({1.0}), interpreter->variables());
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

    EXPECT_EQ(fileContents("generator/ode_const_var_on_rhs/model.h"), generator->interfaceCode());
    EXPECT_EQ(fileContents("generator/ode_const_var_on_rhs/model.c"), generator->implementationCode());

    auto profile = libcellml::GeneratorProfile::create(libcellml::GeneratorProfile::Profile::PYTHON);

    generator->setProfile(profile);

    EXPECT_EQ(fileContents("generator/ode_const_var_on_rhs/model.py"), generator->implementationCode());

    auto interpreter = libcellml::Interpreter::create();

    interpreter->setModel(analyserModel);

    EXPECT_EQ(0.0, interpreter->voi());
    EXPECT_EQ_VALUES(NAN_x_1, interpreter->states());
    EXPECT_EQ_VALUES(NAN_x_1, interpreter->rates());
    EXPECT_EQ_VALUES(NAN_x_1, interpreter->variables());

    interpreter->initialiseVariables();
    interpreter->computeComputedConstants();
    interpreter->computeRates();
    interpreter->computeVariables();

    EXPECT_EQ_VALUES(std::vector<double>({1.0}), interpreter->states());
    EXPECT_EQ_VALUES(NAN_x_1, interpreter->rates());
    EXPECT_EQ_VALUES(std::vector<double>({1.0}), interpreter->variables());
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

    EXPECT_EQ(fileContents("generator/ode_const_var_on_rhs_one_component/model.h"), generator->interfaceCode());
    EXPECT_EQ(fileContents("generator/ode_const_var_on_rhs_one_component/model.c"), generator->implementationCode());

    auto profile = libcellml::GeneratorProfile::create(libcellml::GeneratorProfile::Profile::PYTHON);

    generator->setProfile(profile);

    EXPECT_EQ(fileContents("generator/ode_const_var_on_rhs_one_component/model.py"), generator->implementationCode());

    auto interpreter = libcellml::Interpreter::create();

    interpreter->setModel(analyserModel);

    EXPECT_EQ(0.0, interpreter->voi());
    EXPECT_EQ_VALUES(NAN_x_1, interpreter->states());
    EXPECT_EQ_VALUES(NAN_x_1, interpreter->rates());
    EXPECT_EQ_VALUES(NAN_x_1, interpreter->variables());

    interpreter->initialiseVariables();
    interpreter->computeComputedConstants();
    interpreter->computeRates();
    interpreter->computeVariables();

    EXPECT_EQ_VALUES(std::vector<double>({1.0}), interpreter->states());
    EXPECT_EQ_VALUES(NAN_x_1, interpreter->rates());
    EXPECT_EQ_VALUES(std::vector<double>({1.0}), interpreter->variables());
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

    EXPECT_EQ(fileContents("generator/ode_constant_on_rhs/model.h"), generator->interfaceCode());
    EXPECT_EQ(fileContents("generator/ode_constant_on_rhs/model.c"), generator->implementationCode());

    auto profile = libcellml::GeneratorProfile::create(libcellml::GeneratorProfile::Profile::PYTHON);

    generator->setProfile(profile);

    EXPECT_EQ(fileContents("generator/ode_constant_on_rhs/model.py"), generator->implementationCode());

    auto interpreter = libcellml::Interpreter::create();

    interpreter->setModel(analyserModel);

    EXPECT_EQ(0.0, interpreter->voi());
    EXPECT_EQ_VALUES(NAN_x_1, interpreter->states());
    EXPECT_EQ_VALUES(NAN_x_1, interpreter->rates());
    EXPECT_EQ_VALUES(NO_VALUES, interpreter->variables());

    interpreter->initialiseVariables();
    interpreter->computeComputedConstants();
    interpreter->computeRates();
    interpreter->computeVariables();

    EXPECT_EQ_VALUES(std::vector<double>({1.0}), interpreter->states());
    EXPECT_EQ_VALUES(NAN_x_1, interpreter->rates());
    EXPECT_EQ_VALUES(NO_VALUES, interpreter->variables());
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

    EXPECT_EQ(fileContents("generator/ode_constant_on_rhs_one_component/model.h"), generator->interfaceCode());
    EXPECT_EQ(fileContents("generator/ode_constant_on_rhs_one_component/model.c"), generator->implementationCode());

    auto profile = libcellml::GeneratorProfile::create(libcellml::GeneratorProfile::Profile::PYTHON);

    generator->setProfile(profile);

    EXPECT_EQ(fileContents("generator/ode_constant_on_rhs_one_component/model.py"), generator->implementationCode());

    auto interpreter = libcellml::Interpreter::create();

    interpreter->setModel(analyserModel);

    EXPECT_EQ(0.0, interpreter->voi());
    EXPECT_EQ_VALUES(NAN_x_1, interpreter->states());
    EXPECT_EQ_VALUES(NAN_x_1, interpreter->rates());
    EXPECT_EQ_VALUES(NO_VALUES, interpreter->variables());

    interpreter->initialiseVariables();
    interpreter->computeComputedConstants();
    interpreter->computeRates();
    interpreter->computeVariables();

    EXPECT_EQ_VALUES(std::vector<double>({1.0}), interpreter->states());
    EXPECT_EQ_VALUES(NAN_x_1, interpreter->rates());
    EXPECT_EQ_VALUES(NO_VALUES, interpreter->variables());
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

    EXPECT_EQ(fileContents("generator/ode_multiple_dependent_odes/model.h"), generator->interfaceCode());
    EXPECT_EQ(fileContents("generator/ode_multiple_dependent_odes/model.c"), generator->implementationCode());

    auto profile = libcellml::GeneratorProfile::create(libcellml::GeneratorProfile::Profile::PYTHON);

    generator->setProfile(profile);

    EXPECT_EQ(fileContents("generator/ode_multiple_dependent_odes/model.py"), generator->implementationCode());

    auto interpreter = libcellml::Interpreter::create();

    interpreter->setModel(analyserModel);

    EXPECT_EQ(0.0, interpreter->voi());
    EXPECT_EQ_VALUES(NAN_x_2, interpreter->states());
    EXPECT_EQ_VALUES(NAN_x_2, interpreter->rates());
    EXPECT_EQ_VALUES(NAN_x_1, interpreter->variables());

    interpreter->initialiseVariables();
    interpreter->computeComputedConstants();
    interpreter->computeRates();
    interpreter->computeVariables();

    EXPECT_EQ_VALUES(std::vector<double>({-2.0, 0.0}), interpreter->states());
    EXPECT_EQ_VALUES(NAN_x_2, interpreter->rates());
    EXPECT_EQ_VALUES(std::vector<double>({1.0}), interpreter->variables());
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

    EXPECT_EQ(fileContents("generator/ode_multiple_dependent_odes_one_component/model.h"), generator->interfaceCode());
    EXPECT_EQ(fileContents("generator/ode_multiple_dependent_odes_one_component/model.c"), generator->implementationCode());

    auto profile = libcellml::GeneratorProfile::create(libcellml::GeneratorProfile::Profile::PYTHON);

    generator->setProfile(profile);

    EXPECT_EQ(fileContents("generator/ode_multiple_dependent_odes_one_component/model.py"), generator->implementationCode());

    auto interpreter = libcellml::Interpreter::create();

    interpreter->setModel(analyserModel);

    EXPECT_EQ(0.0, interpreter->voi());
    EXPECT_EQ_VALUES(NAN_x_2, interpreter->states());
    EXPECT_EQ_VALUES(NAN_x_2, interpreter->rates());
    EXPECT_EQ_VALUES(NAN_x_1, interpreter->variables());

    interpreter->initialiseVariables();
    interpreter->computeComputedConstants();
    interpreter->computeRates();
    interpreter->computeVariables();

    EXPECT_EQ_VALUES(std::vector<double>({-2.0, 0.0}), interpreter->states());
    EXPECT_EQ_VALUES(NAN_x_2, interpreter->rates());
    EXPECT_EQ_VALUES(std::vector<double>({1.0}), interpreter->variables());
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

    EXPECT_EQ(fileContents("generator/ode_multiple_odes_with_same_name/model.h"), generator->interfaceCode());
    EXPECT_EQ(fileContents("generator/ode_multiple_odes_with_same_name/model.c"), generator->implementationCode());

    auto profile = libcellml::GeneratorProfile::create(libcellml::GeneratorProfile::Profile::PYTHON);

    generator->setProfile(profile);

    EXPECT_EQ(fileContents("generator/ode_multiple_odes_with_same_name/model.py"), generator->implementationCode());

    auto interpreter = libcellml::Interpreter::create();

    interpreter->setModel(analyserModel);

    EXPECT_EQ(0.0, interpreter->voi());
    EXPECT_EQ_VALUES(NAN_x_2, interpreter->states());
    EXPECT_EQ_VALUES(NAN_x_2, interpreter->rates());
    EXPECT_EQ_VALUES(NAN_x_1, interpreter->variables());

    interpreter->initialiseVariables();
    interpreter->computeComputedConstants();
    interpreter->computeRates();
    interpreter->computeVariables();

    EXPECT_EQ_VALUES(std::vector<double>({1.0, 1.0}), interpreter->states());
    EXPECT_EQ_VALUES(NAN_x_2, interpreter->rates());
    EXPECT_EQ_VALUES(std::vector<double>({1.0}), interpreter->variables());
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

    EXPECT_EQ(fileContents("generator/ode_unknown_var_on_rhs/model.h"), generator->interfaceCode());
    EXPECT_EQ(fileContents("generator/ode_unknown_var_on_rhs/model.c"), generator->implementationCode());

    auto profile = libcellml::GeneratorProfile::create(libcellml::GeneratorProfile::Profile::PYTHON);

    generator->setProfile(profile);

    EXPECT_EQ(fileContents("generator/ode_unknown_var_on_rhs/model.py"), generator->implementationCode());

    auto interpreter = libcellml::Interpreter::create();

    interpreter->setModel(analyserModel);

    EXPECT_EQ(0.0, interpreter->voi());
    EXPECT_EQ_VALUES(NAN_x_2, interpreter->states());
    EXPECT_EQ_VALUES(NAN_x_2, interpreter->rates());
    EXPECT_EQ_VALUES(NO_VALUES, interpreter->variables());

    interpreter->initialiseVariables();
    interpreter->computeComputedConstants();
    interpreter->computeRates();
    interpreter->computeVariables();

    EXPECT_EQ_VALUES(std::vector<double>({1.0, 1.0}), interpreter->states());
    EXPECT_EQ_VALUES(NAN_x_2, interpreter->rates());
    EXPECT_EQ_VALUES(NO_VALUES, interpreter->variables());
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

    EXPECT_EQ(fileContents("generator/cellml_mappings_and_encapsulations/model.h"), generator->interfaceCode());
    EXPECT_EQ(fileContents("generator/cellml_mappings_and_encapsulations/model.c"), generator->implementationCode());

    auto profile = libcellml::GeneratorProfile::create(libcellml::GeneratorProfile::Profile::PYTHON);

    generator->setProfile(profile);

    EXPECT_EQ(fileContents("generator/cellml_mappings_and_encapsulations/model.py"), generator->implementationCode());

    auto interpreter = libcellml::Interpreter::create();

    interpreter->setModel(analyserModel);

    EXPECT_EQ(0.0, interpreter->voi());
    EXPECT_EQ_VALUES(NAN_x_2, interpreter->states());
    EXPECT_EQ_VALUES(NAN_x_2, interpreter->rates());
    EXPECT_EQ_VALUES(NAN_x_2, interpreter->variables());

    interpreter->initialiseVariables();
    interpreter->computeComputedConstants();
    interpreter->computeRates();
    interpreter->computeVariables();

    EXPECT_EQ_VALUES(std::vector<double>({1.0, 0.0}), interpreter->states());
    EXPECT_EQ_VALUES(NAN_x_2, interpreter->rates());
    EXPECT_EQ_VALUES(NAN_x_2, interpreter->variables());
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

    EXPECT_EQ(fileContents("generator/cellml_state_initialised_using_variable/model.h"), generator->interfaceCode());
    EXPECT_EQ(fileContents("generator/cellml_state_initialised_using_variable/model.c"), generator->implementationCode());

    auto profile = libcellml::GeneratorProfile::create(libcellml::GeneratorProfile::Profile::PYTHON);

    generator->setProfile(profile);

    EXPECT_EQ(fileContents("generator/cellml_state_initialised_using_variable/model.py"), generator->implementationCode());

    auto interpreter = libcellml::Interpreter::create();

    interpreter->setModel(analyserModel);

    EXPECT_EQ(0.0, interpreter->voi());
    EXPECT_EQ_VALUES(NAN_x_1, interpreter->states());
    EXPECT_EQ_VALUES(NAN_x_1, interpreter->rates());
    EXPECT_EQ_VALUES(NAN_x_1, interpreter->variables());

    interpreter->initialiseVariables();
    interpreter->computeComputedConstants();
    interpreter->computeRates();
    interpreter->computeVariables();

    EXPECT_EQ_VALUES(std::vector<double>({123.0}), interpreter->states());
    EXPECT_EQ_VALUES(NAN_x_1, interpreter->rates());
    EXPECT_EQ_VALUES(std::vector<double>({123.0}), interpreter->variables());
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

    EXPECT_EQ(fileContents("generator/cellml_unit_scaling_voi_indirect/model.h"), generator->interfaceCode());
    EXPECT_EQ(fileContents("generator/cellml_unit_scaling_voi_indirect/model.c"), generator->implementationCode());

    auto profile = libcellml::GeneratorProfile::create(libcellml::GeneratorProfile::Profile::PYTHON);

    generator->setProfile(profile);

    EXPECT_EQ(fileContents("generator/cellml_unit_scaling_voi_indirect/model.py"), generator->implementationCode());

    auto interpreter = libcellml::Interpreter::create();

    interpreter->setModel(analyserModel);

    EXPECT_EQ(0.0, interpreter->voi());
    EXPECT_EQ_VALUES(NAN_x_2, interpreter->states());
    EXPECT_EQ_VALUES(NAN_x_2, interpreter->rates());
    EXPECT_EQ_VALUES(NO_VALUES, interpreter->variables());

    interpreter->initialiseVariables();
    interpreter->computeComputedConstants();
    interpreter->computeRates();
    interpreter->computeVariables();

    EXPECT_EQ_VALUES(std::vector<double>({3.0, 7.0}), interpreter->states());
    EXPECT_EQ_VALUES(NAN_x_2, interpreter->rates());
    EXPECT_EQ_VALUES(NO_VALUES, interpreter->variables());
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

    EXPECT_EQ(fileContents("generator/cellml_unit_scaling_voi_direct/model.h"), generator->interfaceCode());
    EXPECT_EQ(fileContents("generator/cellml_unit_scaling_voi_direct/model.c"), generator->implementationCode());

    auto profile = libcellml::GeneratorProfile::create(libcellml::GeneratorProfile::Profile::PYTHON);

    generator->setProfile(profile);

    EXPECT_EQ(fileContents("generator/cellml_unit_scaling_voi_direct/model.py"), generator->implementationCode());

    auto interpreter = libcellml::Interpreter::create();

    interpreter->setModel(analyserModel);

    EXPECT_EQ(0.0, interpreter->voi());
    EXPECT_EQ_VALUES(NAN_x_2, interpreter->states());
    EXPECT_EQ_VALUES(NAN_x_2, interpreter->rates());
    EXPECT_EQ_VALUES(NO_VALUES, interpreter->variables());

    interpreter->initialiseVariables();
    interpreter->computeComputedConstants();
    interpreter->computeRates();
    interpreter->computeVariables();

    EXPECT_EQ_VALUES(std::vector<double>({3.0, 5.0}), interpreter->states());
    EXPECT_EQ_VALUES(NAN_x_2, interpreter->rates());
    EXPECT_EQ_VALUES(NO_VALUES, interpreter->variables());
}

TEST(Generator, cellmlUnitScalingConstant)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("generator/cellml_unit_scaling_constant/model.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    auto analyser = libcellml::Analyser::create();

    analyser->analyseModel(model);

    EXPECT_EQ(size_t(0), analyser->errorCount());

    auto analyserModel = analyser->model();
    auto generator = libcellml::Generator::create();

    generator->setModel(analyserModel);

    EXPECT_EQ(fileContents("generator/cellml_unit_scaling_constant/model.h"), generator->interfaceCode());
    EXPECT_EQ(fileContents("generator/cellml_unit_scaling_constant/model.c"), generator->implementationCode());

    auto profile = libcellml::GeneratorProfile::create(libcellml::GeneratorProfile::Profile::PYTHON);

    generator->setProfile(profile);

    EXPECT_EQ(fileContents("generator/cellml_unit_scaling_constant/model.py"), generator->implementationCode());

    auto interpreter = libcellml::Interpreter::create();

    interpreter->setModel(analyserModel);

    EXPECT_EQ(0.0, interpreter->voi());
    EXPECT_EQ_VALUES(NO_VALUES, interpreter->states());
    EXPECT_EQ_VALUES(NO_VALUES, interpreter->rates());
    EXPECT_EQ_VALUES(NAN_x_3, interpreter->variables());

    interpreter->initialiseVariables();
    interpreter->computeComputedConstants();
    interpreter->computeRates();
    interpreter->computeVariables();

    EXPECT_EQ_VALUES(NO_VALUES, interpreter->states());
    EXPECT_EQ_VALUES(NO_VALUES, interpreter->rates());
    EXPECT_EQ_VALUES(std::vector<double>({123.0, NAN, NAN}), interpreter->variables());
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

    EXPECT_EQ(fileContents("generator/cellml_unit_scaling_state/model.h"), generator->interfaceCode());
    EXPECT_EQ(fileContents("generator/cellml_unit_scaling_state/model.c"), generator->implementationCode());

    auto profile = libcellml::GeneratorProfile::create(libcellml::GeneratorProfile::Profile::PYTHON);

    generator->setProfile(profile);

    EXPECT_EQ(fileContents("generator/cellml_unit_scaling_state/model.py"), generator->implementationCode());

    auto interpreter = libcellml::Interpreter::create();

    interpreter->setModel(analyserModel);

    EXPECT_EQ(0.0, interpreter->voi());
    EXPECT_EQ_VALUES(NAN_x_1, interpreter->states());
    EXPECT_EQ_VALUES(NAN_x_1, interpreter->rates());
    EXPECT_EQ_VALUES(NAN_x_2, interpreter->variables());

    interpreter->initialiseVariables();
    interpreter->computeComputedConstants();
    interpreter->computeRates();
    interpreter->computeVariables();

    EXPECT_EQ_VALUES(std::vector<double>({123.0}), interpreter->states());
    EXPECT_EQ_VALUES(NAN_x_1, interpreter->rates());
    EXPECT_EQ_VALUES(NAN_x_2, interpreter->variables());
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

    EXPECT_EQ(fileContents("generator/cellml_unit_scaling_state_initialised_using_constant/model.h"), generator->interfaceCode());
    EXPECT_EQ(fileContents("generator/cellml_unit_scaling_state_initialised_using_constant/model.c"), generator->implementationCode());

    auto profile = libcellml::GeneratorProfile::create(libcellml::GeneratorProfile::Profile::PYTHON);

    generator->setProfile(profile);

    EXPECT_EQ(fileContents("generator/cellml_unit_scaling_state_initialised_using_constant/model.py"), generator->implementationCode());

    auto interpreter = libcellml::Interpreter::create();

    interpreter->setModel(analyserModel);

    EXPECT_EQ(0.0, interpreter->voi());
    EXPECT_EQ_VALUES(NAN_x_2, interpreter->states());
    EXPECT_EQ_VALUES(NAN_x_2, interpreter->rates());
    EXPECT_EQ_VALUES(NO_VALUES, interpreter->variables());

    interpreter->initialiseVariables();
    interpreter->computeComputedConstants();
    interpreter->computeRates();
    interpreter->computeVariables();

    EXPECT_EQ_VALUES(std::vector<double>({123.0, 0.789}), interpreter->states());
    EXPECT_EQ_VALUES(NAN_x_2, interpreter->rates());
    EXPECT_EQ_VALUES(NO_VALUES, interpreter->variables());
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

    EXPECT_EQ(fileContents("generator/cellml_unit_scaling_state_initialised_using_variable/model.h"), generator->interfaceCode());
    EXPECT_EQ(fileContents("generator/cellml_unit_scaling_state_initialised_using_variable/model.c"), generator->implementationCode());

    auto profile = libcellml::GeneratorProfile::create(libcellml::GeneratorProfile::Profile::PYTHON);

    generator->setProfile(profile);

    EXPECT_EQ(fileContents("generator/cellml_unit_scaling_state_initialised_using_variable/model.py"), generator->implementationCode());

    auto interpreter = libcellml::Interpreter::create();

    interpreter->setModel(analyserModel);

    EXPECT_EQ(0.0, interpreter->voi());
    EXPECT_EQ_VALUES(NAN_x_2, interpreter->states());
    EXPECT_EQ_VALUES(NAN_x_2, interpreter->rates());
    EXPECT_EQ_VALUES(NAN_x_2, interpreter->variables());

    interpreter->initialiseVariables();
    interpreter->computeComputedConstants();
    interpreter->computeRates();
    interpreter->computeVariables();

    EXPECT_EQ_VALUES(std::vector<double>({123.0, 0.789}), interpreter->states());
    EXPECT_EQ_VALUES(NAN_x_2, interpreter->rates());
    EXPECT_EQ_VALUES(std::vector<double>({123.0, 789.0}), interpreter->variables());
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

    EXPECT_EQ(fileContents("generator/cellml_unit_scaling_rate/model.h"), generator->interfaceCode());
    EXPECT_EQ(fileContents("generator/cellml_unit_scaling_rate/model.c"), generator->implementationCode());

    auto profile = libcellml::GeneratorProfile::create(libcellml::GeneratorProfile::Profile::PYTHON);

    generator->setProfile(profile);

    EXPECT_EQ(fileContents("generator/cellml_unit_scaling_rate/model.py"), generator->implementationCode());

    auto interpreter = libcellml::Interpreter::create();

    interpreter->setModel(analyserModel);

    EXPECT_EQ(0.0, interpreter->voi());
    EXPECT_EQ_VALUES(NAN_x_1, interpreter->states());
    EXPECT_EQ_VALUES(NAN_x_1, interpreter->rates());
    EXPECT_EQ_VALUES(NAN_x_2, interpreter->variables());

    interpreter->initialiseVariables();
    interpreter->computeComputedConstants();
    interpreter->computeRates();
    interpreter->computeVariables();

    EXPECT_EQ_VALUES(std::vector<double>({123.0}), interpreter->states());
    EXPECT_EQ_VALUES(NAN_x_1, interpreter->rates());
    EXPECT_EQ_VALUES(NAN_x_2, interpreter->variables());
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

    EXPECT_EQ(fileContents("generator/dependent_eqns/model.h"), generator->interfaceCode());
    EXPECT_EQ(fileContents("generator/dependent_eqns/model.c"), generator->implementationCode());

    auto profile = libcellml::GeneratorProfile::create(libcellml::GeneratorProfile::Profile::PYTHON);

    generator->setProfile(profile);

    EXPECT_EQ(fileContents("generator/dependent_eqns/model.py"), generator->implementationCode());

    auto interpreter = libcellml::Interpreter::create();

    interpreter->setModel(analyserModel);

    EXPECT_EQ(0.0, interpreter->voi());
    EXPECT_EQ_VALUES(NAN_x_1, interpreter->states());
    EXPECT_EQ_VALUES(NAN_x_1, interpreter->rates());
    EXPECT_EQ_VALUES(NAN_x_2, interpreter->variables());

    interpreter->initialiseVariables();
    interpreter->computeComputedConstants();
    interpreter->computeRates();
    interpreter->computeVariables();

    EXPECT_EQ_VALUES(std::vector<double>({0.0}), interpreter->states());
    EXPECT_EQ_VALUES(NAN_x_1, interpreter->rates());
    EXPECT_EQ_VALUES(NAN_x_2, interpreter->variables());
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

    EXPECT_EQ(fileContents("generator/cell_geometry_model/model.h"), generator->interfaceCode());
    EXPECT_EQ(fileContents("generator/cell_geometry_model/model.c"), generator->implementationCode());

    auto profile = libcellml::GeneratorProfile::create(libcellml::GeneratorProfile::Profile::PYTHON);

    generator->setProfile(profile);

    EXPECT_EQ(fileContents("generator/cell_geometry_model/model.py"), generator->implementationCode());

    auto interpreter = libcellml::Interpreter::create();

    interpreter->setModel(analyserModel);

    EXPECT_EQ(0.0, interpreter->voi());
    EXPECT_EQ_VALUES(NO_VALUES, interpreter->states());
    EXPECT_EQ_VALUES(NO_VALUES, interpreter->rates());
    EXPECT_EQ_VALUES(NAN_x_4, interpreter->variables());

    interpreter->initialiseVariables();
    interpreter->computeComputedConstants();
    interpreter->computeRates();
    interpreter->computeVariables();

    EXPECT_EQ_VALUES(NO_VALUES, interpreter->states());
    EXPECT_EQ_VALUES(NO_VALUES, interpreter->rates());
    EXPECT_EQ_VALUES(std::vector<double>({NAN, 0.01, 0.0011, NAN}), interpreter->variables());
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

    EXPECT_EQ(fileContents("generator/cell_geometry_model/model.external.h"), generator->interfaceCode());
    EXPECT_EQ(fileContents("generator/cell_geometry_model/model.external.c"), generator->implementationCode());

    profile = libcellml::GeneratorProfile::create(libcellml::GeneratorProfile::Profile::PYTHON);

    generator->setProfile(profile);

    EXPECT_EQ(fileContents("generator/cell_geometry_model/model.external.py"), generator->implementationCode());

    auto interpreter = libcellml::Interpreter::create();

    interpreter->setModel(analyserModel);

    EXPECT_EQ(0.0, interpreter->voi());
    EXPECT_EQ_VALUES(NO_VALUES, interpreter->states());
    EXPECT_EQ_VALUES(NO_VALUES, interpreter->rates());
    EXPECT_EQ_VALUES(NAN_x_4, interpreter->variables());

    interpreter->initialiseVariables();
    interpreter->computeComputedConstants();
    interpreter->computeRates();
    interpreter->computeVariables();

    EXPECT_EQ_VALUES(NO_VALUES, interpreter->states());
    EXPECT_EQ_VALUES(NO_VALUES, interpreter->rates());
    EXPECT_EQ_VALUES(NAN_x_4, interpreter->variables());
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

    EXPECT_EQ(fileContents("generator/fabbri_fantini_wilders_severi_human_san_model_2017/model.h"), generator->interfaceCode());
    EXPECT_EQ(fileContents("generator/fabbri_fantini_wilders_severi_human_san_model_2017/model.c"), generator->implementationCode());

    auto profile = libcellml::GeneratorProfile::create(libcellml::GeneratorProfile::Profile::PYTHON);

    generator->setProfile(profile);

    EXPECT_EQ(fileContents("generator/fabbri_fantini_wilders_severi_human_san_model_2017/model.py"), generator->implementationCode());

    auto interpreter = libcellml::Interpreter::create();

    interpreter->setModel(analyserModel);

    EXPECT_EQ(0.0, interpreter->voi());
    EXPECT_EQ_VALUES(NAN_x_33, interpreter->states());
    EXPECT_EQ_VALUES(NAN_x_33, interpreter->rates());
    EXPECT_EQ_VALUES(NAN_x_217, interpreter->variables());

    interpreter->initialiseVariables();
    interpreter->computeComputedConstants();
    interpreter->computeRates();
    interpreter->computeVariables();

    EXPECT_EQ_VALUES(std::vector<double>({6.226104e-5, 5.0, 0.409551, 6.181512e-9, 0.9308, 0.069199, 4.595622e-10, 9.15641e-6, 0.435148, 0.017929, 0.259947, 0.653777, 0.217311, 0.158521, 0.138975, -47.787168, 0.009508, 0.003058, 0.447724, 0.845304, 0.011845, 0.844449, 0.846702, 0.001921, 0.020484, 0.268909, 0.014523, 0.430836, 0.709051, 0.011068, 0.283185, 0.1162, 0.00277}), interpreter->states());
    EXPECT_EQ_VALUES(NAN_x_33, interpreter->rates());
    EXPECT_EQ_VALUES(std::vector<double>({0.0, 0.0, NAN, NAN, 140.0, NAN, NAN, 5.4, 140.0, NAN, 1.8, 1.0, NAN, NAN, NAN, NAN, NAN, 96485.3415, NAN, NAN, NAN, NAN, 14.0, 1.4, 0.08105, 0.0, NAN, NAN, NAN, NAN, 3.343, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, 26.44, 0.0207, 0.1369, NAN, 395.3, 2.289, 0.4315, 26.44, 4.663, 3.663, 0.0, NAN, 1628.0, 561.4, NAN, 148041085.1, NAN, NAN, 15.0, 1.0, 0.45, 2.5, NAN, 10000.0, NAN, 500.0, 5.0, 660.0, NAN, NAN, NAN, 5.0, NAN, 5.469e-5, NAN, 0.000286113, 5.0e-5, NAN, 0.04, NAN, 88800.0, 446.0, NAN, 227700.0, 7.51, NAN, 2277.0, 2.5, 751.0, NAN, 1.642e6, 542.0, NAN, NAN, 175.4, 445.0, 0.031, 0.062, 0.045, 10.0, NAN, NAN, NAN, NAN, NAN, 67.0, 3.9, 0.02, 0.0012, 0.46, 0.0116, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, 5.7e-5, 8314.472, 310.0, NAN, 0.0, -35.0, 0.5, 0.5, -45.0, NAN, 0.00427, 45.0, NAN, 0.5927, NAN, NAN, NAN, 0.0, NAN, NAN, NAN, NAN, NAN, 0.0, NAN, NAN, 0.0223, NAN, 0.0, NAN, NAN, NAN, 1.0e-5, NAN, NAN, NAN, NAN, NAN, NAN, 0.1539e-3, NAN, NAN, NAN, NAN, NAN, 0.4578, NAN, NAN, NAN, NAN, NAN, -16.4508, 4.3371, NAN, NAN, NAN, NAN, NAN, NAN, 0.0, 0.0, NAN, NAN, 0.000338, NAN, 0.0075, 0.04132, NAN, NAN, NAN, NAN, 0.0, 3.5e-3, NAN, NAN, NAN, NAN, 0.00424, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, 0.00065, NAN, NAN, NAN, NAN, NAN, NAN, 1.0, 0.00345, NAN, NAN, NAN, NAN}), interpreter->variables());
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

    EXPECT_EQ(fileContents("generator/garny_kohl_hunter_boyett_noble_rabbit_san_model_2003/model.h"), generator->interfaceCode());
    EXPECT_EQ(fileContents("generator/garny_kohl_hunter_boyett_noble_rabbit_san_model_2003/model.c"), generator->implementationCode());

    auto profile = libcellml::GeneratorProfile::create(libcellml::GeneratorProfile::Profile::PYTHON);

    generator->setProfile(profile);

    EXPECT_EQ(fileContents("generator/garny_kohl_hunter_boyett_noble_rabbit_san_model_2003/model.py"), generator->implementationCode());

    auto interpreter = libcellml::Interpreter::create();

    interpreter->setModel(analyserModel);

    EXPECT_EQ(0.0, interpreter->voi());
    EXPECT_EQ_VALUES(NAN_x_15, interpreter->states());
    EXPECT_EQ_VALUES(NAN_x_15, interpreter->rates());
    EXPECT_EQ_VALUES(NAN_x_185, interpreter->variables());

    interpreter->initialiseVariables();
    interpreter->computeComputedConstants();
    interpreter->computeRates();
    interpreter->computeVariables();
    EXPECT_EQ_VALUES(std::vector<double>({-39.013558536, 0.092361701692, 0.015905380261, 0.01445216109, 0.48779845203, 0.04804900895, 0.038968420558, 0.42074047435, 0.064402950262, 0.29760539675, 0.87993375273, 0.13034201158, 0.46960956028, 0.082293827208, 0.03889291759}), interpreter->states());
    EXPECT_EQ_VALUES(NAN_x_15, interpreter->rates());
    EXPECT_EQ_VALUES(std::vector<double>({NAN, 0.0, 1.0, 1.0309347, NAN, 2.0e-5, 6.5e-5, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, 8314.0, 310.0, 96845.0, NAN, 5.8e-5, 0.000189, 5.8e-5, 0.000189, 5.81818e-5, 0.0001888, NAN, NAN, 2.52e-5, 8.19e-5, 2.52e-5, 8.19e-5, 2.523636e-5, 8.1892e-5, NAN, NAN, 1.32e-5, 4.3e-5, 1.323e-5, 4.29e-5, 1.3236e-5, 4.2952e-5, NAN, NAN, 2.7e-6, 8.8e-6, 2.8e-6, 8.8e-6, 2.7229e-6, 8.83584e-6, 8.0, 0.5, 2.0, 140.0, 0.0001, 0.0001, NAN, 0.0478, 0.16, 0.0478, 0.16, 0.04782545, 0.1551936, 5.4, 0.621, 5.64, NAN, 0.0, 0.0, 0.0042, 0.03339, 0.0, 0.0, 140.0, NAN, NAN, 0.0, 1.2e-6, 0.0, 3.7e-7, 0.0, 1.204e-6, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, 0.0058, 0.0659, 0.0082, 0.0659, 0.0057938, 0.06588648, 46.4, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, 0.0043, 0.0139, 0.0021, 0.00694, 0.00427806, 0.0138823, 45.0, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, 0.00491, 0.03649, 0.004905, 0.0365, 0.004905, 0.036495, NAN, 6.65e-5, 0.0114, 0.000266, 0.0114, 6.645504e-5, 0.01138376, NAN, NAN, NAN, NAN, NAN, 0.000797, 0.016, 0.000738, 0.0208, 0.00079704, 0.016, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, 0.000518, 0.0104, 0.000345, 0.0104, 0.0003445, 0.0104, NAN, NAN, NAN, 0.000548, 0.0069, 0.000437, 0.0055, 0.0005465, 0.006875, NAN, 0.000548, 0.0069, 0.000437, 0.0055, 0.0005465, 0.006875, NAN, NAN}), interpreter->variables());
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

    EXPECT_EQ(fileContents("generator/hodgkin_huxley_squid_axon_model_1952/model.h"), generator->interfaceCode());
    EXPECT_EQ(fileContents("generator/hodgkin_huxley_squid_axon_model_1952/model.c"), generator->implementationCode());

    auto profile = libcellml::GeneratorProfile::create(libcellml::GeneratorProfile::Profile::PYTHON);

    generator->setProfile(profile);

    EXPECT_EQ(fileContents("generator/hodgkin_huxley_squid_axon_model_1952/model.py"), generator->implementationCode());

    auto interpreter = libcellml::Interpreter::create();

    interpreter->setModel(analyserModel);

    EXPECT_EQ(0.0, interpreter->voi());
    EXPECT_EQ_VALUES(NAN_x_4, interpreter->states());
    EXPECT_EQ_VALUES(NAN_x_4, interpreter->rates());
    EXPECT_EQ_VALUES(NAN_x_18, interpreter->variables());

    interpreter->initialiseVariables();
    interpreter->computeComputedConstants();
    interpreter->computeRates();
    interpreter->computeVariables();

    EXPECT_EQ_VALUES(std::vector<double>({0.0, 0.6, 0.05, 0.325}), interpreter->states());
    EXPECT_EQ_VALUES(NAN_x_4, interpreter->rates());
    EXPECT_EQ_VALUES(std::vector<double>({NAN, NAN, NAN, NAN, 1.0, 0.0, NAN, 0.3, NAN, 120.0, NAN, NAN, NAN, NAN, NAN, 36.0, NAN, NAN}), interpreter->variables());
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

    EXPECT_EQ(fileContents("generator/hodgkin_huxley_squid_axon_model_1952/model.h"), generator->interfaceCode());
    EXPECT_EQ(fileContents("generator/hodgkin_huxley_squid_axon_model_1952/model.c"), generator->implementationCode());

    auto profile = libcellml::GeneratorProfile::create(libcellml::GeneratorProfile::Profile::PYTHON);

    generator->setProfile(profile);

    EXPECT_EQ(fileContents("generator/hodgkin_huxley_squid_axon_model_1952/model.py"), generator->implementationCode());

    auto interpreter = libcellml::Interpreter::create();

    interpreter->setModel(analyserModel);

    EXPECT_EQ(0.0, interpreter->voi());
    EXPECT_EQ_VALUES(NAN_x_4, interpreter->states());
    EXPECT_EQ_VALUES(NAN_x_4, interpreter->rates());
    EXPECT_EQ_VALUES(NAN_x_18, interpreter->variables());

    interpreter->initialiseVariables();
    interpreter->computeComputedConstants();
    interpreter->computeRates();
    interpreter->computeVariables();

    EXPECT_EQ_VALUES(std::vector<double>({0.0, 0.6, 0.05, 0.325}), interpreter->states());
    EXPECT_EQ_VALUES(NAN_x_4, interpreter->rates());
    EXPECT_EQ_VALUES(std::vector<double>({NAN, NAN, NAN, NAN, 1.0, 0.0, NAN, 0.3, NAN, 120.0, NAN, NAN, NAN, NAN, NAN, 36.0, NAN, NAN}), interpreter->variables());
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

    EXPECT_EQ(fileContents("generator/hodgkin_huxley_squid_axon_model_1952/model.state.h"), generator->interfaceCode());
    EXPECT_EQ(fileContents("generator/hodgkin_huxley_squid_axon_model_1952/model.state.c"), generator->implementationCode());

    profile = libcellml::GeneratorProfile::create(libcellml::GeneratorProfile::Profile::PYTHON);

    generator->setProfile(profile);

    EXPECT_EQ(fileContents("generator/hodgkin_huxley_squid_axon_model_1952/model.state.py"), generator->implementationCode());

    auto interpreter = libcellml::Interpreter::create();

    interpreter->setModel(analyserModel);

    EXPECT_EQ(0.0, interpreter->voi());
    EXPECT_EQ_VALUES(NAN_x_3, interpreter->states());
    EXPECT_EQ_VALUES(NAN_x_3, interpreter->rates());
    EXPECT_EQ_VALUES(NAN_x_19, interpreter->variables());

    interpreter->initialiseVariables();
    interpreter->computeComputedConstants();
    interpreter->computeRates();
    interpreter->computeVariables();

    EXPECT_EQ_VALUES(std::vector<double>({0.0, 0.6, 0.325}), interpreter->states());
    EXPECT_EQ_VALUES(NAN_x_3, interpreter->rates());
    EXPECT_EQ_VALUES(std::vector<double>({NAN, NAN, NAN, NAN, 1.0, 0.0, NAN, 0.3, NAN, 120.0, NAN, NAN, NAN, NAN, NAN, NAN, 36.0, NAN, NAN}), interpreter->variables());
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

    EXPECT_EQ(fileContents("generator/hodgkin_huxley_squid_axon_model_1952/model.dependent.state.h"), generator->interfaceCode());
    EXPECT_EQ(fileContents("generator/hodgkin_huxley_squid_axon_model_1952/model.dependent.state.c"), generator->implementationCode());

    profile = libcellml::GeneratorProfile::create(libcellml::GeneratorProfile::Profile::PYTHON);

    generator->setProfile(profile);

    EXPECT_EQ(fileContents("generator/hodgkin_huxley_squid_axon_model_1952/model.dependent.state.py"), generator->implementationCode());

    auto interpreter = libcellml::Interpreter::create();

    interpreter->setModel(analyserModel);

    EXPECT_EQ(0.0, interpreter->voi());
    EXPECT_EQ_VALUES(NAN_x_2, interpreter->states());
    EXPECT_EQ_VALUES(NAN_x_2, interpreter->rates());
    EXPECT_EQ_VALUES(NAN_x_20, interpreter->variables());

    interpreter->initialiseVariables();
    interpreter->computeComputedConstants();
    interpreter->computeRates();
    interpreter->computeVariables();

    EXPECT_EQ_VALUES(std::vector<double>({0.6, 0.325}), interpreter->states());
    EXPECT_EQ_VALUES(NAN_x_2, interpreter->rates());
    EXPECT_EQ_VALUES(std::vector<double>({NAN, NAN, NAN, NAN, NAN, 1.0, 0.0, NAN, 0.3, NAN, 120.0, NAN, NAN, NAN, NAN, NAN, NAN, 36.0, NAN, NAN}), interpreter->variables());
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

    EXPECT_EQ(fileContents("generator/hodgkin_huxley_squid_axon_model_1952/model.constant.h"), generator->interfaceCode());
    EXPECT_EQ(fileContents("generator/hodgkin_huxley_squid_axon_model_1952/model.constant.c"), generator->implementationCode());

    profile = libcellml::GeneratorProfile::create(libcellml::GeneratorProfile::Profile::PYTHON);

    generator->setProfile(profile);

    EXPECT_EQ(fileContents("generator/hodgkin_huxley_squid_axon_model_1952/model.constant.py"), generator->implementationCode());

    auto interpreter = libcellml::Interpreter::create();

    interpreter->setModel(analyserModel);

    EXPECT_EQ(0.0, interpreter->voi());
    EXPECT_EQ_VALUES(NAN_x_4, interpreter->states());
    EXPECT_EQ_VALUES(NAN_x_4, interpreter->rates());
    EXPECT_EQ_VALUES(NAN_x_18, interpreter->variables());

    interpreter->initialiseVariables();
    interpreter->computeComputedConstants();
    interpreter->computeRates();
    interpreter->computeVariables();

    EXPECT_EQ_VALUES(std::vector<double>({0.0, 0.6, 0.05, 0.325}), interpreter->states());
    EXPECT_EQ_VALUES(NAN_x_4, interpreter->rates());
    EXPECT_EQ_VALUES(std::vector<double>({NAN, NAN, NAN, NAN, NAN, 0.0, NAN, 0.3, NAN, 120.0, NAN, NAN, NAN, NAN, NAN, 36.0, NAN, NAN}), interpreter->variables());
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

    EXPECT_EQ(fileContents("generator/hodgkin_huxley_squid_axon_model_1952/model.dependent.constant.h"), generator->interfaceCode());
    EXPECT_EQ(fileContents("generator/hodgkin_huxley_squid_axon_model_1952/model.dependent.constant.c"), generator->implementationCode());

    profile = libcellml::GeneratorProfile::create(libcellml::GeneratorProfile::Profile::PYTHON);

    generator->setProfile(profile);

    EXPECT_EQ(fileContents("generator/hodgkin_huxley_squid_axon_model_1952/model.dependent.constant.py"), generator->implementationCode());

    auto interpreter = libcellml::Interpreter::create();

    interpreter->setModel(analyserModel);

    EXPECT_EQ(0.0, interpreter->voi());
    EXPECT_EQ_VALUES(NAN_x_4, interpreter->states());
    EXPECT_EQ_VALUES(NAN_x_4, interpreter->rates());
    EXPECT_EQ_VALUES(NAN_x_18, interpreter->variables());

    interpreter->initialiseVariables();
    interpreter->computeComputedConstants();
    interpreter->computeRates();
    interpreter->computeVariables();

    EXPECT_EQ_VALUES(std::vector<double>({0.0, 0.6, 0.05, 0.325}), interpreter->states());
    EXPECT_EQ_VALUES(NAN_x_4, interpreter->rates());
    EXPECT_EQ_VALUES(std::vector<double>({NAN, NAN, NAN, NAN, NAN, 0.0, NAN, 0.3, NAN, NAN, NAN, NAN, NAN, NAN, NAN, 36.0, NAN, NAN}), interpreter->variables());
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

    EXPECT_EQ(fileContents("generator/hodgkin_huxley_squid_axon_model_1952/model.computed.constant.h"), generator->interfaceCode());
    EXPECT_EQ(fileContents("generator/hodgkin_huxley_squid_axon_model_1952/model.computed.constant.c"), generator->implementationCode());

    profile = libcellml::GeneratorProfile::create(libcellml::GeneratorProfile::Profile::PYTHON);

    generator->setProfile(profile);

    EXPECT_EQ(fileContents("generator/hodgkin_huxley_squid_axon_model_1952/model.computed.constant.py"), generator->implementationCode());

    auto interpreter = libcellml::Interpreter::create();

    interpreter->setModel(analyserModel);

    EXPECT_EQ(0.0, interpreter->voi());
    EXPECT_EQ_VALUES(NAN_x_4, interpreter->states());
    EXPECT_EQ_VALUES(NAN_x_4, interpreter->rates());
    EXPECT_EQ_VALUES(NAN_x_18, interpreter->variables());

    interpreter->initialiseVariables();
    interpreter->computeComputedConstants();
    interpreter->computeRates();
    interpreter->computeVariables();

    EXPECT_EQ_VALUES(std::vector<double>({0.0, 0.6, 0.05, 0.325}), interpreter->states());
    EXPECT_EQ_VALUES(NAN_x_4, interpreter->rates());
    EXPECT_EQ_VALUES(std::vector<double>({NAN, NAN, NAN, NAN, 1.0, 0.0, NAN, 0.3, NAN, 120.0, NAN, NAN, NAN, NAN, NAN, 36.0, NAN, NAN}), interpreter->variables());
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

    EXPECT_EQ(fileContents("generator/hodgkin_huxley_squid_axon_model_1952/model.dependent.computed.constant.h"), generator->interfaceCode());
    EXPECT_EQ(fileContents("generator/hodgkin_huxley_squid_axon_model_1952/model.dependent.computed.constant.c"), generator->implementationCode());

    profile = libcellml::GeneratorProfile::create(libcellml::GeneratorProfile::Profile::PYTHON);

    generator->setProfile(profile);

    EXPECT_EQ(fileContents("generator/hodgkin_huxley_squid_axon_model_1952/model.dependent.computed.constant.py"), generator->implementationCode());

    auto interpreter = libcellml::Interpreter::create();

    interpreter->setModel(analyserModel);

    EXPECT_EQ(0.0, interpreter->voi());
    EXPECT_EQ_VALUES(NAN_x_4, interpreter->states());
    EXPECT_EQ_VALUES(NAN_x_4, interpreter->rates());
    EXPECT_EQ_VALUES(NAN_x_18, interpreter->variables());

    interpreter->initialiseVariables();
    interpreter->computeComputedConstants();
    interpreter->computeRates();
    interpreter->computeVariables();

    EXPECT_EQ_VALUES(std::vector<double>({0.0, 0.6, 0.05, 0.325}), interpreter->states());
    EXPECT_EQ_VALUES(NAN_x_4, interpreter->rates());
    EXPECT_EQ_VALUES(std::vector<double>({NAN, NAN, NAN, NAN, 1.0, NAN, NAN, 0.3, NAN, 120.0, NAN, NAN, NAN, NAN, NAN, 36.0, NAN, NAN}), interpreter->variables());
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

    EXPECT_EQ(fileContents("generator/hodgkin_huxley_squid_axon_model_1952/model.algebraic.h"), generator->interfaceCode());
    EXPECT_EQ(fileContents("generator/hodgkin_huxley_squid_axon_model_1952/model.algebraic.c"), generator->implementationCode());

    profile = libcellml::GeneratorProfile::create(libcellml::GeneratorProfile::Profile::PYTHON);

    generator->setProfile(profile);

    EXPECT_EQ(fileContents("generator/hodgkin_huxley_squid_axon_model_1952/model.algebraic.py"), generator->implementationCode());

    auto interpreter = libcellml::Interpreter::create();

    interpreter->setModel(analyserModel);

    EXPECT_EQ(0.0, interpreter->voi());
    EXPECT_EQ_VALUES(NAN_x_4, interpreter->states());
    EXPECT_EQ_VALUES(NAN_x_4, interpreter->rates());
    EXPECT_EQ_VALUES(NAN_x_18, interpreter->variables());

    interpreter->initialiseVariables();
    interpreter->computeComputedConstants();
    interpreter->computeRates();
    interpreter->computeVariables();

    EXPECT_EQ_VALUES(std::vector<double>({0.0, 0.6, 0.05, 0.325}), interpreter->states());
    EXPECT_EQ_VALUES(NAN_x_4, interpreter->rates());
    EXPECT_EQ_VALUES(std::vector<double>({NAN, NAN, NAN, NAN, 1.0, 0.0, NAN, 0.3, NAN, 120.0, NAN, NAN, NAN, NAN, NAN, 36.0, NAN, NAN}), interpreter->variables());
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
    auto membrane_i_Stime = libcellml::AnalyserExternalVariable::create(model->component("membrane")->variable("i_Stim"));

    membrane_i_Stime->addDependency(potassium_channel_n_gate_beta_n);

    analyser->addExternalVariable(libcellml::AnalyserExternalVariable::create(potassium_channel_n_gate_beta_n));
    analyser->addExternalVariable(membrane_i_Stime);

    analyser->analyseModel(model);

    EXPECT_EQ(size_t(0), analyser->errorCount());

    auto analyserModel = analyser->model();
    auto generator = libcellml::Generator::create();

    generator->setModel(analyserModel);

    auto profile = generator->profile();

    profile->setInterfaceFileNameString("model.dependent.algebraic.h");

    EXPECT_EQ(fileContents("generator/hodgkin_huxley_squid_axon_model_1952/model.dependent.algebraic.h"), generator->interfaceCode());
    EXPECT_EQ(fileContents("generator/hodgkin_huxley_squid_axon_model_1952/model.dependent.algebraic.c"), generator->implementationCode());

    profile = libcellml::GeneratorProfile::create(libcellml::GeneratorProfile::Profile::PYTHON);

    generator->setProfile(profile);

    EXPECT_EQ(fileContents("generator/hodgkin_huxley_squid_axon_model_1952/model.dependent.algebraic.py"), generator->implementationCode());

    auto interpreter = libcellml::Interpreter::create();

    interpreter->setModel(analyserModel);

    EXPECT_EQ(0.0, interpreter->voi());
    EXPECT_EQ_VALUES(NAN_x_4, interpreter->states());
    EXPECT_EQ_VALUES(NAN_x_4, interpreter->rates());
    EXPECT_EQ_VALUES(NAN_x_18, interpreter->variables());

    interpreter->initialiseVariables();
    interpreter->computeComputedConstants();
    interpreter->computeRates();
    interpreter->computeVariables();

    EXPECT_EQ_VALUES(std::vector<double>({0.0, 0.6, 0.05, 0.325}), interpreter->states());
    EXPECT_EQ_VALUES(NAN_x_4, interpreter->rates());
    EXPECT_EQ_VALUES(std::vector<double>({NAN, NAN, NAN, NAN, 1.0, 0.0, NAN, 0.3, NAN, 120.0, NAN, NAN, NAN, NAN, NAN, 36.0, NAN, NAN}), interpreter->variables());
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

    EXPECT_EQ(fileContents("generator/hodgkin_huxley_squid_axon_model_1952/model.external.h"), generator->interfaceCode());
    EXPECT_EQ(fileContents("generator/hodgkin_huxley_squid_axon_model_1952/model.external.c"), generator->implementationCode());

    profile = libcellml::GeneratorProfile::create(libcellml::GeneratorProfile::Profile::PYTHON);

    generator->setProfile(profile);

    EXPECT_EQ(fileContents("generator/hodgkin_huxley_squid_axon_model_1952/model.external.py"), generator->implementationCode());

    auto interpreter = libcellml::Interpreter::create();

    interpreter->setModel(analyserModel);

    EXPECT_EQ(0.0, interpreter->voi());
    EXPECT_EQ_VALUES(NAN_x_3, interpreter->states());
    EXPECT_EQ_VALUES(NAN_x_3, interpreter->rates());
    EXPECT_EQ_VALUES(NAN_x_19, interpreter->variables());

    interpreter->initialiseVariables();
    interpreter->computeComputedConstants();
    interpreter->computeRates();
    interpreter->computeVariables();

    EXPECT_EQ_VALUES(std::vector<double>({0.6, 0.05, 0.325}), interpreter->states());
    EXPECT_EQ_VALUES(NAN_x_3, interpreter->rates());
    EXPECT_EQ_VALUES(std::vector<double>({NAN, NAN, NAN, NAN, NAN, 1.0, 0.0, NAN, 0.3, NAN, 120.0, NAN, NAN, NAN, NAN, NAN, 36.0, NAN, NAN}), interpreter->variables());
}

TEST(Generator, hodgkinHuxleySquidAxonModel1952Nla)
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

    EXPECT_EQ(fileContents("generator/hodgkin_huxley_squid_axon_model_1952/model.dae.h"), generator->interfaceCode());
    EXPECT_EQ(fileContents("generator/hodgkin_huxley_squid_axon_model_1952/model.dae.c"), generator->implementationCode());

    profile = libcellml::GeneratorProfile::create(libcellml::GeneratorProfile::Profile::PYTHON);

    generator->setProfile(profile);

    EXPECT_EQ(fileContents("generator/hodgkin_huxley_squid_axon_model_1952/model.dae.py"), generator->implementationCode());

    auto interpreter = libcellml::Interpreter::create();

    interpreter->setModel(analyserModel);

    EXPECT_EQ(0.0, interpreter->voi());
    EXPECT_EQ_VALUES(NAN_x_4, interpreter->states());
    EXPECT_EQ_VALUES(NAN_x_4, interpreter->rates());
    EXPECT_EQ_VALUES(NAN_x_18, interpreter->variables());

    interpreter->initialiseVariables();
    interpreter->computeComputedConstants();
    interpreter->computeRates();
    interpreter->computeVariables();

    EXPECT_EQ_VALUES(std::vector<double>({0.0, 0.6, 0.05, 0.325}), interpreter->states());
    EXPECT_EQ_VALUES(std::vector<double>({0.0, 0.0, 0.0, 0.0}), interpreter->rates());
    EXPECT_EQ_VALUES(std::vector<double>({0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.3, 0.0, 120.0, 0.0, 0.0, 0.0, 0.0, 0.0, 36.0, 0.0, 0.0}), interpreter->variables());
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

    EXPECT_EQ(fileContents("generator/noble_model_1962/model.h"), generator->interfaceCode());
    EXPECT_EQ(fileContents("generator/noble_model_1962/model.c"), generator->implementationCode());

    auto profile = libcellml::GeneratorProfile::create(libcellml::GeneratorProfile::Profile::PYTHON);

    generator->setProfile(profile);

    EXPECT_EQ(fileContents("generator/noble_model_1962/model.py"), generator->implementationCode());

    auto interpreter = libcellml::Interpreter::create();

    interpreter->setModel(analyserModel);

    EXPECT_EQ(0.0, interpreter->voi());
    EXPECT_EQ_VALUES(NAN_x_4, interpreter->states());
    EXPECT_EQ_VALUES(NAN_x_4, interpreter->rates());
    EXPECT_EQ_VALUES(NAN_x_17, interpreter->variables());

    interpreter->initialiseVariables();
    interpreter->computeComputedConstants();
    interpreter->computeRates();
    interpreter->computeVariables();

    EXPECT_EQ_VALUES(std::vector<double>({-87.0, 0.01, 0.8, 0.01}), interpreter->states());
    EXPECT_EQ_VALUES(NAN_x_4, interpreter->rates());
    EXPECT_EQ_VALUES(std::vector<double>({NAN, NAN, NAN, 12.0, 0.075, -60.0, NAN, 400.0, 40.0, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN}), interpreter->variables());
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

    EXPECT_EQ(fileContents("generator/robertson_model_1966/model.ode.h"), generator->interfaceCode());
    EXPECT_EQ(fileContents("generator/robertson_model_1966/model.ode.c"), generator->implementationCode());

    profile = libcellml::GeneratorProfile::create(libcellml::GeneratorProfile::Profile::PYTHON);

    generator->setProfile(profile);

    EXPECT_EQ(fileContents("generator/robertson_model_1966/model.ode.py"), generator->implementationCode());

    auto interpreter = libcellml::Interpreter::create();

    interpreter->setModel(analyserModel);

    EXPECT_EQ(0.0, interpreter->voi());
    EXPECT_EQ_VALUES(NAN_x_3, interpreter->states());
    EXPECT_EQ_VALUES(NAN_x_3, interpreter->rates());
    EXPECT_EQ_VALUES(NAN_x_4, interpreter->variables());

    interpreter->initialiseVariables();
    interpreter->computeComputedConstants();
    interpreter->computeRates();
    interpreter->computeVariables();

    EXPECT_EQ_VALUES(std::vector<double>({1.0, 0.0, 0.0}), interpreter->states());
    EXPECT_EQ_VALUES(NAN_x_3, interpreter->rates());
    EXPECT_EQ_VALUES(std::vector<double>({0.04, 10000.0, 30000000.0, NAN}), interpreter->variables());
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

    EXPECT_EQ(fileContents("generator/robertson_model_1966/model.dae.h"), generator->interfaceCode());
    EXPECT_EQ(fileContents("generator/robertson_model_1966/model.dae.c"), generator->implementationCode());

    profile = libcellml::GeneratorProfile::create(libcellml::GeneratorProfile::Profile::PYTHON);

    generator->setProfile(profile);

    EXPECT_EQ(fileContents("generator/robertson_model_1966/model.dae.py"), generator->implementationCode());

    auto interpreter = libcellml::Interpreter::create();

    interpreter->setModel(analyserModel);

    EXPECT_EQ(0.0, interpreter->voi());
    EXPECT_EQ_VALUES(NAN_x_2, interpreter->states());
    EXPECT_EQ_VALUES(NAN_x_2, interpreter->rates());
    EXPECT_EQ_VALUES(NAN_x_5, interpreter->variables());

    interpreter->initialiseVariables();
    interpreter->computeComputedConstants();
    interpreter->computeRates();
    interpreter->computeVariables();

    EXPECT_EQ_VALUES(std::vector<double>({1.0, 0.0}), interpreter->states());
    EXPECT_EQ_VALUES(NAN_x_2, interpreter->rates());
    EXPECT_EQ_VALUES(std::vector<double>({0.04, 10000.0, 0.0, 30000000.0, NAN}), interpreter->variables());
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

    EXPECT_EQ(fileContents("generator/sine_model_imports/model.h"), generator->interfaceCode());
    EXPECT_EQ(fileContents("generator/sine_model_imports/model.c"), generator->implementationCode());

    auto profile = libcellml::GeneratorProfile::create(libcellml::GeneratorProfile::Profile::PYTHON);

    generator->setProfile(profile);

    EXPECT_EQ(fileContents("generator/sine_model_imports/model.py"), generator->implementationCode());

    auto interpreter = libcellml::Interpreter::create();

    interpreter->setModel(analyserModel);

    EXPECT_EQ(0.0, interpreter->voi());
    EXPECT_EQ_VALUES(NAN_x_1, interpreter->states());
    EXPECT_EQ_VALUES(NAN_x_1, interpreter->rates());
    EXPECT_EQ_VALUES(NAN_x_10, interpreter->variables());

    interpreter->initialiseVariables();
    interpreter->computeComputedConstants();
    interpreter->computeRates();
    interpreter->computeVariables();

    EXPECT_EQ_VALUES(std::vector<double>({0.0}), interpreter->states());
    EXPECT_EQ_VALUES(NAN_x_1, interpreter->rates());
    EXPECT_EQ_VALUES(std::vector<double>({NAN, 0.0, NAN, 0.75, 0.63661977236758138, 6.2831853071795862, 1.5707963267948966, 3.1415926535897931, 4.7123889803846897, NAN}), interpreter->variables());
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

    EXPECT_EQ(fileContents("generator/hodgkin_huxley_squid_axon_model_1952/model.h"), generator->interfaceCode());
    EXPECT_EQ(fileContents("generator/hodgkin_huxley_squid_axon_model_1952/model.c"), generator->implementationCode());

    auto interpreter = libcellml::Interpreter::create();

    interpreter->setModel(analyserModel);

    EXPECT_EQ(0.0, interpreter->voi());
    EXPECT_EQ_VALUES(NAN_x_4, interpreter->states());
    EXPECT_EQ_VALUES(NAN_x_4, interpreter->rates());
    EXPECT_EQ_VALUES(NAN_x_18, interpreter->variables());

    interpreter->initialiseVariables();
    interpreter->computeComputedConstants();
    interpreter->computeRates();
    interpreter->computeVariables();

    EXPECT_EQ_VALUES(std::vector<double>({0.0, 0.6, 0.05, 0.325}), interpreter->states());
    EXPECT_EQ_VALUES(NAN_x_4, interpreter->rates());
    EXPECT_EQ_VALUES(std::vector<double>({NAN, NAN, NAN, NAN, 1.0, 0.0, NAN, 0.3, NAN, 120.0, NAN, NAN, NAN, NAN, NAN, 36.0, NAN, NAN}), interpreter->variables());
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

    EXPECT_EQ(fileContents("generator/dae_cellml_1_1_model/model.h"), generator->interfaceCode());
    EXPECT_EQ(fileContents("generator/dae_cellml_1_1_model/model.c"), generator->implementationCode());

    auto profile = libcellml::GeneratorProfile::create(libcellml::GeneratorProfile::Profile::PYTHON);

    generator->setProfile(profile);

    EXPECT_EQ(fileContents("generator/dae_cellml_1_1_model/model.py"), generator->implementationCode());

    auto interpreter = libcellml::Interpreter::create();

    interpreter->setModel(analyserModel);

    EXPECT_EQ(0.0, interpreter->voi());
    EXPECT_EQ_VALUES(NAN_x_2, interpreter->states());
    EXPECT_EQ_VALUES(NAN_x_2, interpreter->rates());
    EXPECT_EQ_VALUES(NAN_x_10, interpreter->variables());

    interpreter->initialiseVariables();
    interpreter->computeComputedConstants();
    interpreter->computeRates();
    interpreter->computeVariables();

    EXPECT_EQ_VALUES(std::vector<double>({1.0, 0.0}), interpreter->states());
    EXPECT_EQ_VALUES(NAN_x_2, interpreter->rates());
    EXPECT_EQ_VALUES(std::vector<double>({0.0, 1.0, NAN, 1.0, NAN, NAN, 0.0, 20.0, 2.0, 10.0}), interpreter->variables());
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

    EXPECT_EQ(fileContents("generator/variable_initialised_using_a_constant/model.h"), generator->interfaceCode());
    EXPECT_EQ(fileContents("generator/variable_initialised_using_a_constant/model.c"), generator->implementationCode());

    auto profile = libcellml::GeneratorProfile::create(libcellml::GeneratorProfile::Profile::PYTHON);

    generator->setProfile(profile);

    EXPECT_EQ(fileContents("generator/variable_initialised_using_a_constant/model.py"), generator->implementationCode());

    auto interpreter = libcellml::Interpreter::create();

    interpreter->setModel(analyserModel);

    EXPECT_EQ(0.0, interpreter->voi());
    EXPECT_EQ_VALUES(NAN_x_1, interpreter->states());
    EXPECT_EQ_VALUES(NAN_x_1, interpreter->rates());
    EXPECT_EQ_VALUES(NAN_x_1, interpreter->variables());

    interpreter->initialiseVariables();
    interpreter->computeComputedConstants();
    interpreter->computeRates();
    interpreter->computeVariables();

    EXPECT_EQ_VALUES(std::vector<double>({7.0}), interpreter->states());
    EXPECT_EQ_VALUES(NAN_x_1, interpreter->rates());
    EXPECT_EQ_VALUES(std::vector<double>({7.0}), interpreter->variables());
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

    EXPECT_EQ(fileContents("generator/ode_multiple_dependent_odes/model.py"), generator->implementationCode());

    auto interpreter = libcellml::Interpreter::create();

    interpreter->setModel(analyserModel);

    EXPECT_EQ(0.0, interpreter->voi());
    EXPECT_EQ_VALUES(NAN_x_2, interpreter->states());
    EXPECT_EQ_VALUES(NAN_x_2, interpreter->rates());
    EXPECT_EQ_VALUES(NAN_x_1, interpreter->variables());

    interpreter->initialiseVariables();
    interpreter->computeComputedConstants();
    interpreter->computeRates();
    interpreter->computeVariables();

    EXPECT_EQ_VALUES(std::vector<double>({-2.0, 0.0}), interpreter->states());
    EXPECT_EQ_VALUES(NAN_x_2, interpreter->rates());
    EXPECT_EQ_VALUES(std::vector<double>({1.0}), interpreter->variables());
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

    EXPECT_EQ(fileContents("generator/unknown_variable_as_external_variable/model.h"), generator->interfaceCode());
    EXPECT_EQ(fileContents("generator/unknown_variable_as_external_variable/model.c"), generator->implementationCode());

    auto profile = libcellml::GeneratorProfile::create(libcellml::GeneratorProfile::Profile::PYTHON);

    generator->setProfile(profile);

    EXPECT_EQ(fileContents("generator/unknown_variable_as_external_variable/model.py"), generator->implementationCode());

    auto interpreter = libcellml::Interpreter::create();

    interpreter->setModel(analyserModel);

    EXPECT_EQ(0.0, interpreter->voi());
    EXPECT_EQ_VALUES(NO_VALUES, interpreter->states());
    EXPECT_EQ_VALUES(NO_VALUES, interpreter->rates());
    EXPECT_EQ_VALUES(NAN_x_10, interpreter->variables());

    interpreter->initialiseVariables();
    interpreter->computeComputedConstants();
    interpreter->computeRates();
    interpreter->computeVariables();

    EXPECT_EQ_VALUES(NO_VALUES, interpreter->states());
    EXPECT_EQ_VALUES(NO_VALUES, interpreter->rates());
    EXPECT_EQ_VALUES(std::vector<double>({NAN, 1.1, 21262500.0, 150.0, 3402000.0, 2.0, 2902500.0, 810000.0, 247140.0, NAN}), interpreter->variables());
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

    EXPECT_EQ(fileContents("generator/cellml_slc_example/model.py"), generator->implementationCode());

    auto interpreter = libcellml::Interpreter::create();

    interpreter->setModel(analyserModel);

    EXPECT_EQ(0.0, interpreter->voi());
    EXPECT_EQ_VALUES(NO_VALUES, interpreter->states());
    EXPECT_EQ_VALUES(NO_VALUES, interpreter->rates());
    EXPECT_EQ_VALUES(NAN_x_10, interpreter->variables());

    interpreter->initialiseVariables();
    interpreter->computeComputedConstants();
    interpreter->computeRates();
    interpreter->computeVariables();

    EXPECT_EQ_VALUES(NO_VALUES, interpreter->states());
    EXPECT_EQ_VALUES(NO_VALUES, interpreter->rates());
    EXPECT_EQ_VALUES(std::vector<double>({NAN, 1.1, 21262500.0, 150.0, 3402000.0, 2.0, 2902500.0, 810000.0, 247140.0, 2902500.0}), interpreter->variables());
}

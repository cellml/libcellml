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

static const std::string EMPTY_STRING;

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

    EXPECT_EQ(libcellml::AnalyserModel::Type::ALGEBRAIC, analyserModel->type());

    EXPECT_EQ(size_t(0), analyserModel->stateCount());
    EXPECT_EQ(size_t(2), analyserModel->variableCount());
    EXPECT_EQ(size_t(2), analyserModel->equationCount());

    EXPECT_EQ(nullptr, analyserModel->voi());
    EXPECT_EQ(nullptr, analyserModel->state(0));
    EXPECT_NE(nullptr, analyserModel->variable(0));
    EXPECT_EQ(nullptr, analyserModel->variable(analyserModel->variableCount()));
    EXPECT_NE(nullptr, analyserModel->equation(0));
    EXPECT_EQ(nullptr, analyserModel->equation(analyserModel->equationCount()));

    auto generator = libcellml::Generator::create();

    generator->setModel(analyserModel);

    EXPECT_EQ(fileContents("generator/algebraic_eqn_computed_var_on_rhs/model.h"), generator->interfaceCode());
    EXPECT_EQ(fileContents("generator/algebraic_eqn_computed_var_on_rhs/model.c"), generator->implementationCode());

    auto profile = libcellml::GeneratorProfile::create(libcellml::GeneratorProfile::Profile::PYTHON);

    generator->setProfile(profile);

    EXPECT_EQ(EMPTY_STRING, generator->interfaceCode());
    EXPECT_EQ(fileContents("generator/algebraic_eqn_computed_var_on_rhs/model.py"), generator->implementationCode());
}

TEST(Generator, algebraicEqnComputedVarOnRhsWithExternalVariables)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("generator/algebraic_eqn_computed_var_on_rhs/model.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    auto analyser = libcellml::Analyser::create();

    analyser->addExternalVariable(libcellml::AnalyserExternalVariable::create(model->component("my_algebraic_eqn")->variable("a")));

    analyser->analyseModel(model);

    EXPECT_EQ(size_t(0), analyser->errorCount());

    auto analyserModel = analyser->model();

    EXPECT_EQ(libcellml::AnalyserModel::Type::ALGEBRAIC, analyserModel->type());

    EXPECT_EQ(size_t(0), analyserModel->stateCount());
    EXPECT_EQ(size_t(2), analyserModel->variableCount());
    EXPECT_EQ(size_t(2), analyserModel->equationCount());

    EXPECT_EQ(nullptr, analyserModel->voi());
    EXPECT_EQ(nullptr, analyserModel->state(0));
    EXPECT_NE(nullptr, analyserModel->variable(0));
    EXPECT_EQ(nullptr, analyserModel->variable(analyserModel->variableCount()));
    EXPECT_NE(nullptr, analyserModel->equation(0));
    EXPECT_EQ(nullptr, analyserModel->equation(analyserModel->equationCount()));

    auto generator = libcellml::Generator::create();

    generator->setModel(analyserModel);

    auto profile = generator->profile();

    profile->setInterfaceFileNameString("model.external.h");

    EXPECT_EQ(fileContents("generator/algebraic_eqn_computed_var_on_rhs/model.external.h"), generator->interfaceCode());
    EXPECT_EQ(fileContents("generator/algebraic_eqn_computed_var_on_rhs/model.external.c"), generator->implementationCode());

    profile = libcellml::GeneratorProfile::create(libcellml::GeneratorProfile::Profile::PYTHON);

    generator->setProfile(profile);

    EXPECT_EQ(EMPTY_STRING, generator->interfaceCode());
    EXPECT_EQ(fileContents("generator/algebraic_eqn_computed_var_on_rhs/model.external.py"), generator->implementationCode());
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

    EXPECT_EQ(libcellml::AnalyserModel::Type::ALGEBRAIC, analyserModel->type());

    EXPECT_EQ(size_t(0), analyserModel->stateCount());
    EXPECT_EQ(size_t(2), analyserModel->variableCount());
    EXPECT_EQ(size_t(1), analyserModel->equationCount());

    EXPECT_EQ(nullptr, analyserModel->voi());
    EXPECT_EQ(nullptr, analyserModel->state(0));
    EXPECT_NE(nullptr, analyserModel->variable(0));
    EXPECT_EQ(nullptr, analyserModel->variable(analyserModel->variableCount()));
    EXPECT_NE(nullptr, analyserModel->equation(0));
    EXPECT_EQ(nullptr, analyserModel->equation(analyserModel->equationCount()));

    auto generator = libcellml::Generator::create();

    generator->setModel(analyserModel);

    EXPECT_EQ(fileContents("generator/algebraic_eqn_const_var_on_rhs/model.h"), generator->interfaceCode());
    EXPECT_EQ(fileContents("generator/algebraic_eqn_const_var_on_rhs/model.c"), generator->implementationCode());

    auto profile = libcellml::GeneratorProfile::create(libcellml::GeneratorProfile::Profile::PYTHON);

    generator->setProfile(profile);

    EXPECT_EQ(EMPTY_STRING, generator->interfaceCode());
    EXPECT_EQ(fileContents("generator/algebraic_eqn_const_var_on_rhs/model.py"), generator->implementationCode());
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

    EXPECT_EQ(libcellml::AnalyserModel::Type::ALGEBRAIC, analyserModel->type());

    EXPECT_EQ(size_t(0), analyserModel->stateCount());
    EXPECT_EQ(size_t(1), analyserModel->variableCount());
    EXPECT_EQ(size_t(1), analyserModel->equationCount());

    EXPECT_EQ(nullptr, analyserModel->voi());
    EXPECT_EQ(nullptr, analyserModel->state(0));
    EXPECT_NE(nullptr, analyserModel->variable(0));
    EXPECT_EQ(nullptr, analyserModel->variable(analyserModel->variableCount()));
    EXPECT_NE(nullptr, analyserModel->equation(0));
    EXPECT_EQ(nullptr, analyserModel->equation(analyserModel->equationCount()));

    auto generator = libcellml::Generator::create();

    generator->setModel(analyserModel);

    EXPECT_EQ(fileContents("generator/algebraic_eqn_constant_on_rhs/model.h"), generator->interfaceCode());
    EXPECT_EQ(fileContents("generator/algebraic_eqn_constant_on_rhs/model.c"), generator->implementationCode());

    auto profile = libcellml::GeneratorProfile::create(libcellml::GeneratorProfile::Profile::PYTHON);

    generator->setProfile(profile);

    EXPECT_EQ(EMPTY_STRING, generator->interfaceCode());
    EXPECT_EQ(fileContents("generator/algebraic_eqn_constant_on_rhs/model.py"), generator->implementationCode());
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

    EXPECT_EQ(libcellml::AnalyserModel::Type::ODE, analyserModel->type());

    EXPECT_EQ(size_t(1), analyserModel->stateCount());
    EXPECT_EQ(size_t(2), analyserModel->variableCount());
    EXPECT_EQ(size_t(3), analyserModel->equationCount());

    EXPECT_NE(nullptr, analyserModel->voi());
    EXPECT_NE(nullptr, analyserModel->state(0));
    EXPECT_EQ(nullptr, analyserModel->state(analyserModel->stateCount()));
    EXPECT_NE(nullptr, analyserModel->variable(0));
    EXPECT_EQ(nullptr, analyserModel->variable(analyserModel->variableCount()));
    EXPECT_NE(nullptr, analyserModel->equation(0));
    EXPECT_EQ(nullptr, analyserModel->equation(analyserModel->equationCount()));

    auto generator = libcellml::Generator::create();

    generator->setModel(analyserModel);

    EXPECT_EQ(fileContents("generator/algebraic_eqn_derivative_on_rhs/model.h"), generator->interfaceCode());
    EXPECT_EQ(fileContents("generator/algebraic_eqn_derivative_on_rhs/model.c"), generator->implementationCode());

    auto profile = libcellml::GeneratorProfile::create(libcellml::GeneratorProfile::Profile::PYTHON);

    generator->setProfile(profile);

    EXPECT_EQ(EMPTY_STRING, generator->interfaceCode());
    EXPECT_EQ(fileContents("generator/algebraic_eqn_derivative_on_rhs/model.py"), generator->implementationCode());
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

    EXPECT_EQ(libcellml::AnalyserModel::Type::ODE, analyserModel->type());

    EXPECT_EQ(size_t(1), analyserModel->stateCount());
    EXPECT_EQ(size_t(2), analyserModel->variableCount());
    EXPECT_EQ(size_t(3), analyserModel->equationCount());

    EXPECT_NE(nullptr, analyserModel->voi());
    EXPECT_NE(nullptr, analyserModel->state(0));
    EXPECT_EQ(nullptr, analyserModel->state(analyserModel->stateCount()));
    EXPECT_NE(nullptr, analyserModel->variable(0));
    EXPECT_EQ(nullptr, analyserModel->variable(analyserModel->variableCount()));
    EXPECT_NE(nullptr, analyserModel->equation(0));
    EXPECT_EQ(nullptr, analyserModel->equation(analyserModel->equationCount()));

    auto generator = libcellml::Generator::create();

    generator->setModel(analyserModel);

    EXPECT_EQ(fileContents("generator/algebraic_eqn_derivative_on_rhs_one_component/model.h"), generator->interfaceCode());
    EXPECT_EQ(fileContents("generator/algebraic_eqn_derivative_on_rhs_one_component/model.c"), generator->implementationCode());

    auto profile = libcellml::GeneratorProfile::create(libcellml::GeneratorProfile::Profile::PYTHON);

    generator->setProfile(profile);

    EXPECT_EQ(EMPTY_STRING, generator->interfaceCode());
    EXPECT_EQ(fileContents("generator/algebraic_eqn_derivative_on_rhs_one_component/model.py"), generator->implementationCode());
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

    EXPECT_EQ(libcellml::AnalyserModel::Type::ODE, analyserModel->type());

    EXPECT_EQ(size_t(1), analyserModel->stateCount());
    EXPECT_EQ(size_t(2), analyserModel->variableCount());
    EXPECT_EQ(size_t(3), analyserModel->equationCount());

    EXPECT_NE(nullptr, analyserModel->voi());
    EXPECT_NE(nullptr, analyserModel->state(0));
    EXPECT_EQ(nullptr, analyserModel->state(analyserModel->stateCount()));
    EXPECT_NE(nullptr, analyserModel->variable(0));
    EXPECT_EQ(nullptr, analyserModel->variable(analyserModel->variableCount()));
    EXPECT_NE(nullptr, analyserModel->equation(0));
    EXPECT_EQ(nullptr, analyserModel->equation(analyserModel->equationCount()));

    auto generator = libcellml::Generator::create();

    generator->setModel(analyserModel);

    EXPECT_EQ(fileContents("generator/algebraic_eqn_state_var_on_rhs/model.h"), generator->interfaceCode());
    EXPECT_EQ(fileContents("generator/algebraic_eqn_state_var_on_rhs/model.c"), generator->implementationCode());

    auto profile = libcellml::GeneratorProfile::create(libcellml::GeneratorProfile::Profile::PYTHON);

    generator->setProfile(profile);

    EXPECT_EQ(EMPTY_STRING, generator->interfaceCode());
    EXPECT_EQ(fileContents("generator/algebraic_eqn_state_var_on_rhs/model.py"), generator->implementationCode());
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

    EXPECT_EQ(libcellml::AnalyserModel::Type::ODE, analyserModel->type());

    EXPECT_EQ(size_t(1), analyserModel->stateCount());
    EXPECT_EQ(size_t(2), analyserModel->variableCount());
    EXPECT_EQ(size_t(3), analyserModel->equationCount());

    EXPECT_NE(nullptr, analyserModel->voi());
    EXPECT_NE(nullptr, analyserModel->state(0));
    EXPECT_EQ(nullptr, analyserModel->state(analyserModel->stateCount()));
    EXPECT_NE(nullptr, analyserModel->variable(0));
    EXPECT_EQ(nullptr, analyserModel->variable(analyserModel->variableCount()));
    EXPECT_NE(nullptr, analyserModel->equation(0));
    EXPECT_EQ(nullptr, analyserModel->equation(analyserModel->equationCount()));

    auto generator = libcellml::Generator::create();

    generator->setModel(analyserModel);

    EXPECT_EQ(fileContents("generator/algebraic_eqn_state_var_on_rhs_one_component/model.h"), generator->interfaceCode());
    EXPECT_EQ(fileContents("generator/algebraic_eqn_state_var_on_rhs_one_component/model.c"), generator->implementationCode());

    auto profile = libcellml::GeneratorProfile::create(libcellml::GeneratorProfile::Profile::PYTHON);

    generator->setProfile(profile);

    EXPECT_EQ(EMPTY_STRING, generator->interfaceCode());
    EXPECT_EQ(fileContents("generator/algebraic_eqn_state_var_on_rhs_one_component/model.py"), generator->implementationCode());
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

    EXPECT_EQ(libcellml::AnalyserModel::Type::ALGEBRAIC, analyserModel->type());

    EXPECT_EQ(size_t(0), analyserModel->stateCount());
    EXPECT_EQ(size_t(2), analyserModel->variableCount());
    EXPECT_EQ(size_t(2), analyserModel->equationCount());

    EXPECT_EQ(nullptr, analyserModel->voi());
    EXPECT_EQ(nullptr, analyserModel->state(0));
    EXPECT_NE(nullptr, analyserModel->variable(0));
    EXPECT_EQ(nullptr, analyserModel->variable(analyserModel->variableCount()));
    EXPECT_NE(nullptr, analyserModel->equation(0));
    EXPECT_EQ(nullptr, analyserModel->equation(analyserModel->equationCount()));

    auto generator = libcellml::Generator::create();

    generator->setModel(analyserModel);

    EXPECT_EQ(fileContents("generator/algebraic_unknown_var_on_rhs/model.h"), generator->interfaceCode());
    EXPECT_EQ(fileContents("generator/algebraic_unknown_var_on_rhs/model.c"), generator->implementationCode());

    auto profile = libcellml::GeneratorProfile::create(libcellml::GeneratorProfile::Profile::PYTHON);

    generator->setProfile(profile);

    EXPECT_EQ(EMPTY_STRING, generator->interfaceCode());
    EXPECT_EQ(fileContents("generator/algebraic_unknown_var_on_rhs/model.py"), generator->implementationCode());
}

TEST(Generator, algebraicEqnWithOneUnknownOnRhs)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("generator/algebraic_eqn_with_one_unknown_on_rhs/model.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    auto analyser = libcellml::Analyser::create();

    analyser->analyseModel(model);

    EXPECT_EQ(size_t(0), analyser->errorCount());

    auto analyserModel = analyser->model();

    EXPECT_EQ(libcellml::AnalyserModel::Type::ALGEBRAIC, analyserModel->type());

    EXPECT_EQ(size_t(0), analyserModel->stateCount());
    EXPECT_EQ(size_t(4), analyserModel->variableCount());
    EXPECT_EQ(size_t(1), analyserModel->equationCount());

    EXPECT_EQ(nullptr, analyserModel->voi());
    EXPECT_EQ(nullptr, analyserModel->state(0));
    EXPECT_EQ(nullptr, analyserModel->state(analyserModel->stateCount()));
    EXPECT_NE(nullptr, analyserModel->variable(0));
    EXPECT_EQ(nullptr, analyserModel->variable(analyserModel->variableCount()));
    EXPECT_NE(nullptr, analyserModel->equation(0));
    EXPECT_EQ(nullptr, analyserModel->equation(analyserModel->equationCount()));

    auto generator = libcellml::Generator::create();

    generator->setModel(analyserModel);

    EXPECT_EQ(fileContents("generator/algebraic_eqn_with_one_unknown_on_rhs/model.h"), generator->interfaceCode());
    EXPECT_EQ(fileContents("generator/algebraic_eqn_with_one_unknown_on_rhs/model.c"), generator->implementationCode());

    auto profile = libcellml::GeneratorProfile::create(libcellml::GeneratorProfile::Profile::PYTHON);

    generator->setProfile(profile);

    EXPECT_EQ(EMPTY_STRING, generator->interfaceCode());
    EXPECT_EQ(fileContents("generator/algebraic_eqn_with_one_unknown_on_rhs/model.py"), generator->implementationCode());
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

    EXPECT_EQ(libcellml::AnalyserModel::Type::ODE, analyserModel->type());

    EXPECT_EQ(size_t(1), analyserModel->stateCount());
    EXPECT_EQ(size_t(1), analyserModel->variableCount());
    EXPECT_EQ(size_t(2), analyserModel->equationCount());

    EXPECT_NE(nullptr, analyserModel->voi());
    EXPECT_NE(nullptr, analyserModel->state(0));
    EXPECT_EQ(nullptr, analyserModel->state(analyserModel->stateCount()));
    EXPECT_NE(nullptr, analyserModel->variable(0));
    EXPECT_EQ(nullptr, analyserModel->variable(analyserModel->variableCount()));
    EXPECT_NE(nullptr, analyserModel->equation(0));
    EXPECT_EQ(nullptr, analyserModel->equation(analyserModel->equationCount()));

    auto generator = libcellml::Generator::create();

    generator->setModel(analyserModel);

    EXPECT_EQ(fileContents("generator/ode_computed_var_on_rhs/model.h"), generator->interfaceCode());
    EXPECT_EQ(fileContents("generator/ode_computed_var_on_rhs/model.c"), generator->implementationCode());

    auto profile = libcellml::GeneratorProfile::create(libcellml::GeneratorProfile::Profile::PYTHON);

    generator->setProfile(profile);

    EXPECT_EQ(EMPTY_STRING, generator->interfaceCode());
    EXPECT_EQ(fileContents("generator/ode_computed_var_on_rhs/model.py"), generator->implementationCode());
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

    EXPECT_EQ(libcellml::AnalyserModel::Type::ODE, analyserModel->type());

    EXPECT_EQ(size_t(1), analyserModel->stateCount());
    EXPECT_EQ(size_t(1), analyserModel->variableCount());
    EXPECT_EQ(size_t(2), analyserModel->equationCount());

    EXPECT_NE(nullptr, analyserModel->voi());
    EXPECT_NE(nullptr, analyserModel->state(0));
    EXPECT_EQ(nullptr, analyserModel->state(analyserModel->stateCount()));
    EXPECT_NE(nullptr, analyserModel->variable(0));
    EXPECT_EQ(nullptr, analyserModel->variable(analyserModel->variableCount()));
    EXPECT_NE(nullptr, analyserModel->equation(0));
    EXPECT_EQ(nullptr, analyserModel->equation(analyserModel->equationCount()));

    auto generator = libcellml::Generator::create();

    generator->setModel(analyserModel);

    EXPECT_EQ(fileContents("generator/ode_computed_var_on_rhs_one_component/model.h"), generator->interfaceCode());
    EXPECT_EQ(fileContents("generator/ode_computed_var_on_rhs_one_component/model.c"), generator->implementationCode());

    auto profile = libcellml::GeneratorProfile::create(libcellml::GeneratorProfile::Profile::PYTHON);

    generator->setProfile(profile);

    EXPECT_EQ(EMPTY_STRING, generator->interfaceCode());
    EXPECT_EQ(fileContents("generator/ode_computed_var_on_rhs_one_component/model.py"), generator->implementationCode());
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

    EXPECT_EQ(libcellml::AnalyserModel::Type::ODE, analyserModel->type());

    EXPECT_EQ(size_t(1), analyserModel->stateCount());
    EXPECT_EQ(size_t(1), analyserModel->variableCount());
    EXPECT_EQ(size_t(1), analyserModel->equationCount());

    EXPECT_NE(nullptr, analyserModel->voi());
    EXPECT_NE(nullptr, analyserModel->state(0));
    EXPECT_EQ(nullptr, analyserModel->state(analyserModel->stateCount()));
    EXPECT_NE(nullptr, analyserModel->variable(0));
    EXPECT_EQ(nullptr, analyserModel->variable(analyserModel->variableCount()));
    EXPECT_NE(nullptr, analyserModel->equation(0));
    EXPECT_EQ(nullptr, analyserModel->equation(analyserModel->equationCount()));

    auto generator = libcellml::Generator::create();

    generator->setModel(analyserModel);

    EXPECT_EQ(fileContents("generator/ode_const_var_on_rhs/model.h"), generator->interfaceCode());
    EXPECT_EQ(fileContents("generator/ode_const_var_on_rhs/model.c"), generator->implementationCode());

    auto profile = libcellml::GeneratorProfile::create(libcellml::GeneratorProfile::Profile::PYTHON);

    generator->setProfile(profile);

    EXPECT_EQ(EMPTY_STRING, generator->interfaceCode());
    EXPECT_EQ(fileContents("generator/ode_const_var_on_rhs/model.py"), generator->implementationCode());
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

    EXPECT_EQ(libcellml::AnalyserModel::Type::ODE, analyserModel->type());

    EXPECT_EQ(size_t(1), analyserModel->stateCount());
    EXPECT_EQ(size_t(1), analyserModel->variableCount());
    EXPECT_EQ(size_t(1), analyserModel->equationCount());

    EXPECT_NE(nullptr, analyserModel->voi());
    EXPECT_NE(nullptr, analyserModel->state(0));
    EXPECT_EQ(nullptr, analyserModel->state(analyserModel->stateCount()));
    EXPECT_NE(nullptr, analyserModel->variable(0));
    EXPECT_EQ(nullptr, analyserModel->variable(analyserModel->variableCount()));
    EXPECT_NE(nullptr, analyserModel->equation(0));
    EXPECT_EQ(nullptr, analyserModel->equation(analyserModel->equationCount()));

    auto generator = libcellml::Generator::create();

    generator->setModel(analyserModel);

    EXPECT_EQ(fileContents("generator/ode_const_var_on_rhs_one_component/model.h"), generator->interfaceCode());
    EXPECT_EQ(fileContents("generator/ode_const_var_on_rhs_one_component/model.c"), generator->implementationCode());

    auto profile = libcellml::GeneratorProfile::create(libcellml::GeneratorProfile::Profile::PYTHON);

    generator->setProfile(profile);

    EXPECT_EQ(EMPTY_STRING, generator->interfaceCode());
    EXPECT_EQ(fileContents("generator/ode_const_var_on_rhs_one_component/model.py"), generator->implementationCode());
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

    EXPECT_EQ(libcellml::AnalyserModel::Type::ODE, analyserModel->type());

    EXPECT_EQ(size_t(1), analyserModel->stateCount());
    EXPECT_EQ(size_t(0), analyserModel->variableCount());
    EXPECT_EQ(size_t(1), analyserModel->equationCount());

    EXPECT_NE(nullptr, analyserModel->voi());
    EXPECT_NE(nullptr, analyserModel->state(0));
    EXPECT_EQ(nullptr, analyserModel->state(analyserModel->stateCount()));
    EXPECT_EQ(nullptr, analyserModel->variable(0));
    EXPECT_NE(nullptr, analyserModel->equation(0));
    EXPECT_EQ(nullptr, analyserModel->equation(analyserModel->equationCount()));

    auto generator = libcellml::Generator::create();

    generator->setModel(analyserModel);

    EXPECT_EQ(fileContents("generator/ode_constant_on_rhs/model.h"), generator->interfaceCode());
    EXPECT_EQ(fileContents("generator/ode_constant_on_rhs/model.c"), generator->implementationCode());

    auto profile = libcellml::GeneratorProfile::create(libcellml::GeneratorProfile::Profile::PYTHON);

    generator->setProfile(profile);

    EXPECT_EQ(EMPTY_STRING, generator->interfaceCode());
    EXPECT_EQ(fileContents("generator/ode_constant_on_rhs/model.py"), generator->implementationCode());
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

    EXPECT_EQ(libcellml::AnalyserModel::Type::ODE, analyserModel->type());

    EXPECT_EQ(size_t(1), analyserModel->stateCount());
    EXPECT_EQ(size_t(0), analyserModel->variableCount());
    EXPECT_EQ(size_t(1), analyserModel->equationCount());

    EXPECT_NE(nullptr, analyserModel->voi());
    EXPECT_NE(nullptr, analyserModel->state(0));
    EXPECT_EQ(nullptr, analyserModel->state(analyserModel->stateCount()));
    EXPECT_EQ(nullptr, analyserModel->variable(0));
    EXPECT_NE(nullptr, analyserModel->equation(0));
    EXPECT_EQ(nullptr, analyserModel->equation(analyserModel->equationCount()));

    auto generator = libcellml::Generator::create();

    generator->setModel(analyserModel);

    EXPECT_EQ(fileContents("generator/ode_constant_on_rhs_one_component/model.h"), generator->interfaceCode());
    EXPECT_EQ(fileContents("generator/ode_constant_on_rhs_one_component/model.c"), generator->implementationCode());

    auto profile = libcellml::GeneratorProfile::create(libcellml::GeneratorProfile::Profile::PYTHON);

    generator->setProfile(profile);

    EXPECT_EQ(EMPTY_STRING, generator->interfaceCode());
    EXPECT_EQ(fileContents("generator/ode_constant_on_rhs_one_component/model.py"), generator->implementationCode());
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

    EXPECT_EQ(libcellml::AnalyserModel::Type::ODE, analyserModel->type());

    EXPECT_EQ(size_t(2), analyserModel->stateCount());
    EXPECT_EQ(size_t(1), analyserModel->variableCount());
    EXPECT_EQ(size_t(2), analyserModel->equationCount());

    EXPECT_NE(nullptr, analyserModel->voi());
    EXPECT_NE(nullptr, analyserModel->state(0));
    EXPECT_EQ(nullptr, analyserModel->state(analyserModel->stateCount()));
    EXPECT_NE(nullptr, analyserModel->variable(0));
    EXPECT_EQ(nullptr, analyserModel->variable(analyserModel->variableCount()));
    EXPECT_NE(nullptr, analyserModel->equation(0));
    EXPECT_EQ(nullptr, analyserModel->equation(analyserModel->equationCount()));

    auto generator = libcellml::Generator::create();

    generator->setModel(analyserModel);

    EXPECT_EQ(fileContents("generator/ode_multiple_dependent_odes/model.h"), generator->interfaceCode());
    EXPECT_EQ(fileContents("generator/ode_multiple_dependent_odes/model.c"), generator->implementationCode());

    auto profile = libcellml::GeneratorProfile::create(libcellml::GeneratorProfile::Profile::PYTHON);

    generator->setProfile(profile);

    EXPECT_EQ(EMPTY_STRING, generator->interfaceCode());
    EXPECT_EQ(fileContents("generator/ode_multiple_dependent_odes/model.py"), generator->implementationCode());
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

    EXPECT_EQ(libcellml::AnalyserModel::Type::ODE, analyserModel->type());

    EXPECT_EQ(size_t(2), analyserModel->stateCount());
    EXPECT_EQ(size_t(1), analyserModel->variableCount());
    EXPECT_EQ(size_t(2), analyserModel->equationCount());

    EXPECT_NE(nullptr, analyserModel->voi());
    EXPECT_NE(nullptr, analyserModel->state(0));
    EXPECT_EQ(nullptr, analyserModel->state(analyserModel->stateCount()));
    EXPECT_NE(nullptr, analyserModel->variable(0));
    EXPECT_EQ(nullptr, analyserModel->variable(analyserModel->variableCount()));
    EXPECT_NE(nullptr, analyserModel->equation(0));
    EXPECT_EQ(nullptr, analyserModel->equation(analyserModel->equationCount()));

    auto generator = libcellml::Generator::create();

    generator->setModel(analyserModel);

    EXPECT_EQ(fileContents("generator/ode_multiple_dependent_odes_one_component/model.h"), generator->interfaceCode());
    EXPECT_EQ(fileContents("generator/ode_multiple_dependent_odes_one_component/model.c"), generator->implementationCode());

    auto profile = libcellml::GeneratorProfile::create(libcellml::GeneratorProfile::Profile::PYTHON);

    generator->setProfile(profile);

    EXPECT_EQ(EMPTY_STRING, generator->interfaceCode());
    EXPECT_EQ(fileContents("generator/ode_multiple_dependent_odes_one_component/model.py"), generator->implementationCode());
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

    EXPECT_EQ(libcellml::AnalyserModel::Type::ODE, analyserModel->type());

    EXPECT_EQ(size_t(2), analyserModel->stateCount());
    EXPECT_EQ(size_t(1), analyserModel->variableCount());
    EXPECT_EQ(size_t(2), analyserModel->equationCount());

    EXPECT_NE(nullptr, analyserModel->voi());
    EXPECT_NE(nullptr, analyserModel->state(0));
    EXPECT_EQ(nullptr, analyserModel->state(analyserModel->stateCount()));
    EXPECT_NE(nullptr, analyserModel->variable(0));
    EXPECT_EQ(nullptr, analyserModel->variable(analyserModel->variableCount()));
    EXPECT_NE(nullptr, analyserModel->equation(0));
    EXPECT_EQ(nullptr, analyserModel->equation(analyserModel->equationCount()));

    auto generator = libcellml::Generator::create();

    generator->setModel(analyserModel);

    EXPECT_EQ(fileContents("generator/ode_multiple_odes_with_same_name/model.h"), generator->interfaceCode());
    EXPECT_EQ(fileContents("generator/ode_multiple_odes_with_same_name/model.c"), generator->implementationCode());

    auto profile = libcellml::GeneratorProfile::create(libcellml::GeneratorProfile::Profile::PYTHON);

    generator->setProfile(profile);

    EXPECT_EQ(EMPTY_STRING, generator->interfaceCode());
    EXPECT_EQ(fileContents("generator/ode_multiple_odes_with_same_name/model.py"), generator->implementationCode());
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

    EXPECT_EQ(libcellml::AnalyserModel::Type::ODE, analyserModel->type());

    EXPECT_EQ(size_t(2), analyserModel->stateCount());
    EXPECT_EQ(size_t(0), analyserModel->variableCount());
    EXPECT_EQ(size_t(2), analyserModel->equationCount());

    EXPECT_NE(nullptr, analyserModel->voi());
    EXPECT_NE(nullptr, analyserModel->state(0));
    EXPECT_EQ(nullptr, analyserModel->state(analyserModel->stateCount()));
    EXPECT_EQ(nullptr, analyserModel->variable(0));
    EXPECT_NE(nullptr, analyserModel->equation(0));
    EXPECT_EQ(nullptr, analyserModel->equation(analyserModel->equationCount()));

    auto generator = libcellml::Generator::create();

    generator->setModel(analyserModel);

    EXPECT_EQ(fileContents("generator/ode_unknown_var_on_rhs/model.h"), generator->interfaceCode());
    EXPECT_EQ(fileContents("generator/ode_unknown_var_on_rhs/model.c"), generator->implementationCode());

    auto profile = libcellml::GeneratorProfile::create(libcellml::GeneratorProfile::Profile::PYTHON);

    generator->setProfile(profile);

    EXPECT_EQ(EMPTY_STRING, generator->interfaceCode());
    EXPECT_EQ(fileContents("generator/ode_unknown_var_on_rhs/model.py"), generator->implementationCode());
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

    EXPECT_EQ(libcellml::AnalyserModel::Type::ODE, analyserModel->type());

    EXPECT_EQ(size_t(2), analyserModel->stateCount());
    EXPECT_EQ(size_t(2), analyserModel->variableCount());
    EXPECT_EQ(size_t(4), analyserModel->equationCount());

    EXPECT_NE(nullptr, analyserModel->voi());
    EXPECT_NE(nullptr, analyserModel->state(0));
    EXPECT_EQ(nullptr, analyserModel->state(analyserModel->stateCount()));
    EXPECT_NE(nullptr, analyserModel->variable(0));
    EXPECT_EQ(nullptr, analyserModel->variable(analyserModel->variableCount()));
    EXPECT_NE(nullptr, analyserModel->equation(0));
    EXPECT_EQ(nullptr, analyserModel->equation(analyserModel->equationCount()));

    auto generator = libcellml::Generator::create();

    generator->setModel(analyserModel);

    EXPECT_EQ(fileContents("generator/cellml_mappings_and_encapsulations/model.h"), generator->interfaceCode());
    EXPECT_EQ(fileContents("generator/cellml_mappings_and_encapsulations/model.c"), generator->implementationCode());

    auto profile = libcellml::GeneratorProfile::create(libcellml::GeneratorProfile::Profile::PYTHON);

    generator->setProfile(profile);

    EXPECT_EQ(EMPTY_STRING, generator->interfaceCode());
    EXPECT_EQ(fileContents("generator/cellml_mappings_and_encapsulations/model.py"), generator->implementationCode());
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

    EXPECT_EQ(libcellml::AnalyserModel::Type::ODE, analyserModel->type());

    EXPECT_EQ(size_t(1), analyserModel->stateCount());
    EXPECT_EQ(size_t(1), analyserModel->variableCount());
    EXPECT_EQ(size_t(1), analyserModel->equationCount());

    EXPECT_NE(nullptr, analyserModel->voi());
    EXPECT_NE(nullptr, analyserModel->state(0));
    EXPECT_EQ(nullptr, analyserModel->state(analyserModel->stateCount()));
    EXPECT_NE(nullptr, analyserModel->variable(0));
    EXPECT_EQ(nullptr, analyserModel->variable(analyserModel->variableCount()));
    EXPECT_NE(nullptr, analyserModel->equation(0));
    EXPECT_EQ(nullptr, analyserModel->equation(analyserModel->equationCount()));

    auto generator = libcellml::Generator::create();

    generator->setModel(analyserModel);

    EXPECT_EQ(fileContents("generator/cellml_state_initialised_using_variable/model.h"), generator->interfaceCode());
    EXPECT_EQ(fileContents("generator/cellml_state_initialised_using_variable/model.c"), generator->implementationCode());

    auto profile = libcellml::GeneratorProfile::create(libcellml::GeneratorProfile::Profile::PYTHON);

    generator->setProfile(profile);

    EXPECT_EQ(EMPTY_STRING, generator->interfaceCode());
    EXPECT_EQ(fileContents("generator/cellml_state_initialised_using_variable/model.py"), generator->implementationCode());
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

    EXPECT_EQ(libcellml::AnalyserModel::Type::ODE, analyserModel->type());

    EXPECT_EQ(size_t(2), analyserModel->stateCount());
    EXPECT_EQ(size_t(0), analyserModel->variableCount());
    EXPECT_EQ(size_t(2), analyserModel->equationCount());

    EXPECT_NE(nullptr, analyserModel->voi());
    EXPECT_NE(nullptr, analyserModel->state(0));
    EXPECT_EQ(nullptr, analyserModel->state(analyserModel->stateCount()));
    EXPECT_EQ(nullptr, analyserModel->variable(0));
    EXPECT_EQ(nullptr, analyserModel->variable(analyserModel->variableCount()));
    EXPECT_NE(nullptr, analyserModel->equation(0));
    EXPECT_EQ(nullptr, analyserModel->equation(analyserModel->equationCount()));

    auto generator = libcellml::Generator::create();

    generator->setModel(analyserModel);

    EXPECT_EQ(fileContents("generator/cellml_unit_scaling_voi_indirect/model.h"), generator->interfaceCode());
    EXPECT_EQ(fileContents("generator/cellml_unit_scaling_voi_indirect/model.c"), generator->implementationCode());

    auto profile = libcellml::GeneratorProfile::create(libcellml::GeneratorProfile::Profile::PYTHON);

    generator->setProfile(profile);

    EXPECT_EQ(EMPTY_STRING, generator->interfaceCode());
    EXPECT_EQ(fileContents("generator/cellml_unit_scaling_voi_indirect/model.py"), generator->implementationCode());
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

    EXPECT_EQ(libcellml::AnalyserModel::Type::ODE, analyserModel->type());

    EXPECT_EQ(size_t(2), analyserModel->stateCount());
    EXPECT_EQ(size_t(0), analyserModel->variableCount());
    EXPECT_EQ(size_t(2), analyserModel->equationCount());

    EXPECT_NE(nullptr, analyserModel->voi());
    EXPECT_NE(nullptr, analyserModel->state(0));
    EXPECT_EQ(nullptr, analyserModel->state(analyserModel->stateCount()));
    EXPECT_EQ(nullptr, analyserModel->variable(0));
    EXPECT_EQ(nullptr, analyserModel->variable(analyserModel->variableCount()));
    EXPECT_NE(nullptr, analyserModel->equation(0));
    EXPECT_EQ(nullptr, analyserModel->equation(analyserModel->equationCount()));

    auto generator = libcellml::Generator::create();

    generator->setModel(analyserModel);

    EXPECT_EQ(fileContents("generator/cellml_unit_scaling_voi_direct/model.h"), generator->interfaceCode());
    EXPECT_EQ(fileContents("generator/cellml_unit_scaling_voi_direct/model.c"), generator->implementationCode());

    auto profile = libcellml::GeneratorProfile::create(libcellml::GeneratorProfile::Profile::PYTHON);

    generator->setProfile(profile);

    EXPECT_EQ(EMPTY_STRING, generator->interfaceCode());
    EXPECT_EQ(fileContents("generator/cellml_unit_scaling_voi_direct/model.py"), generator->implementationCode());
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

    EXPECT_EQ(libcellml::AnalyserModel::Type::ALGEBRAIC, analyserModel->type());

    EXPECT_EQ(size_t(0), analyserModel->stateCount());
    EXPECT_EQ(size_t(3), analyserModel->variableCount());
    EXPECT_EQ(size_t(2), analyserModel->equationCount());

    EXPECT_EQ(nullptr, analyserModel->voi());
    EXPECT_EQ(nullptr, analyserModel->state(0));
    EXPECT_NE(nullptr, analyserModel->variable(0));
    EXPECT_EQ(nullptr, analyserModel->variable(analyserModel->variableCount()));
    EXPECT_NE(nullptr, analyserModel->equation(0));
    EXPECT_EQ(nullptr, analyserModel->equation(analyserModel->equationCount()));

    auto generator = libcellml::Generator::create();

    generator->setModel(analyserModel);

    EXPECT_EQ(fileContents("generator/cellml_unit_scaling_constant/model.h"), generator->interfaceCode());
    EXPECT_EQ(fileContents("generator/cellml_unit_scaling_constant/model.c"), generator->implementationCode());

    auto profile = libcellml::GeneratorProfile::create(libcellml::GeneratorProfile::Profile::PYTHON);

    generator->setProfile(profile);

    EXPECT_EQ(EMPTY_STRING, generator->interfaceCode());
    EXPECT_EQ(fileContents("generator/cellml_unit_scaling_constant/model.py"), generator->implementationCode());
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

    EXPECT_EQ(libcellml::AnalyserModel::Type::ODE, analyserModel->type());

    EXPECT_EQ(size_t(1), analyserModel->stateCount());
    EXPECT_EQ(size_t(2), analyserModel->variableCount());
    EXPECT_EQ(size_t(3), analyserModel->equationCount());

    EXPECT_NE(nullptr, analyserModel->voi());
    EXPECT_NE(nullptr, analyserModel->state(0));
    EXPECT_EQ(nullptr, analyserModel->state(analyserModel->stateCount()));
    EXPECT_NE(nullptr, analyserModel->variable(0));
    EXPECT_EQ(nullptr, analyserModel->variable(analyserModel->variableCount()));
    EXPECT_NE(nullptr, analyserModel->equation(0));
    EXPECT_EQ(nullptr, analyserModel->equation(analyserModel->equationCount()));

    auto generator = libcellml::Generator::create();

    generator->setModel(analyserModel);

    EXPECT_EQ(fileContents("generator/cellml_unit_scaling_state/model.h"), generator->interfaceCode());
    EXPECT_EQ(fileContents("generator/cellml_unit_scaling_state/model.c"), generator->implementationCode());

    auto profile = libcellml::GeneratorProfile::create(libcellml::GeneratorProfile::Profile::PYTHON);

    generator->setProfile(profile);

    EXPECT_EQ(EMPTY_STRING, generator->interfaceCode());
    EXPECT_EQ(fileContents("generator/cellml_unit_scaling_state/model.py"), generator->implementationCode());
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

    EXPECT_EQ(libcellml::AnalyserModel::Type::ODE, analyserModel->type());

    EXPECT_EQ(size_t(2), analyserModel->stateCount());
    EXPECT_EQ(size_t(0), analyserModel->variableCount());
    EXPECT_EQ(size_t(2), analyserModel->equationCount());

    EXPECT_NE(nullptr, analyserModel->voi());
    EXPECT_NE(nullptr, analyserModel->state(0));
    EXPECT_EQ(nullptr, analyserModel->state(analyserModel->stateCount()));
    EXPECT_EQ(nullptr, analyserModel->variable(0));
    EXPECT_EQ(nullptr, analyserModel->variable(analyserModel->variableCount()));
    EXPECT_NE(nullptr, analyserModel->equation(0));
    EXPECT_EQ(nullptr, analyserModel->equation(analyserModel->equationCount()));

    auto generator = libcellml::Generator::create();

    generator->setModel(analyserModel);

    EXPECT_EQ(fileContents("generator/cellml_unit_scaling_state_initialised_using_constant/model.h"), generator->interfaceCode());
    EXPECT_EQ(fileContents("generator/cellml_unit_scaling_state_initialised_using_constant/model.c"), generator->implementationCode());

    auto profile = libcellml::GeneratorProfile::create(libcellml::GeneratorProfile::Profile::PYTHON);

    generator->setProfile(profile);

    EXPECT_EQ(EMPTY_STRING, generator->interfaceCode());
    EXPECT_EQ(fileContents("generator/cellml_unit_scaling_state_initialised_using_constant/model.py"), generator->implementationCode());
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

    EXPECT_EQ(libcellml::AnalyserModel::Type::ODE, analyserModel->type());

    EXPECT_EQ(size_t(2), analyserModel->stateCount());
    EXPECT_EQ(size_t(2), analyserModel->variableCount());
    EXPECT_EQ(size_t(2), analyserModel->equationCount());

    EXPECT_NE(nullptr, analyserModel->voi());
    EXPECT_NE(nullptr, analyserModel->state(0));
    EXPECT_EQ(nullptr, analyserModel->state(analyserModel->stateCount()));
    EXPECT_NE(nullptr, analyserModel->variable(0));
    EXPECT_EQ(nullptr, analyserModel->variable(analyserModel->variableCount()));
    EXPECT_NE(nullptr, analyserModel->equation(0));
    EXPECT_EQ(nullptr, analyserModel->equation(analyserModel->equationCount()));

    auto generator = libcellml::Generator::create();

    generator->setModel(analyserModel);

    EXPECT_EQ(fileContents("generator/cellml_unit_scaling_state_initialised_using_variable/model.h"), generator->interfaceCode());
    EXPECT_EQ(fileContents("generator/cellml_unit_scaling_state_initialised_using_variable/model.c"), generator->implementationCode());

    auto profile = libcellml::GeneratorProfile::create(libcellml::GeneratorProfile::Profile::PYTHON);

    generator->setProfile(profile);

    EXPECT_EQ(EMPTY_STRING, generator->interfaceCode());
    EXPECT_EQ(fileContents("generator/cellml_unit_scaling_state_initialised_using_variable/model.py"), generator->implementationCode());
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

    EXPECT_EQ(libcellml::AnalyserModel::Type::ODE, analyserModel->type());

    EXPECT_EQ(size_t(1), analyserModel->stateCount());
    EXPECT_EQ(size_t(2), analyserModel->variableCount());
    EXPECT_EQ(size_t(3), analyserModel->equationCount());

    EXPECT_NE(nullptr, analyserModel->voi());
    EXPECT_NE(nullptr, analyserModel->state(0));
    EXPECT_EQ(nullptr, analyserModel->state(analyserModel->stateCount()));
    EXPECT_NE(nullptr, analyserModel->variable(0));
    EXPECT_EQ(nullptr, analyserModel->variable(analyserModel->variableCount()));
    EXPECT_NE(nullptr, analyserModel->equation(0));
    EXPECT_EQ(nullptr, analyserModel->equation(analyserModel->equationCount()));

    auto generator = libcellml::Generator::create();

    generator->setModel(analyserModel);

    EXPECT_EQ(fileContents("generator/cellml_unit_scaling_rate/model.h"), generator->interfaceCode());
    EXPECT_EQ(fileContents("generator/cellml_unit_scaling_rate/model.c"), generator->implementationCode());

    auto profile = libcellml::GeneratorProfile::create(libcellml::GeneratorProfile::Profile::PYTHON);

    generator->setProfile(profile);

    EXPECT_EQ(EMPTY_STRING, generator->interfaceCode());
    EXPECT_EQ(fileContents("generator/cellml_unit_scaling_rate/model.py"), generator->implementationCode());
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

    EXPECT_EQ(libcellml::AnalyserModel::Type::ODE, analyserModel->type());

    EXPECT_EQ(size_t(1), analyserModel->stateCount());
    EXPECT_EQ(size_t(2), analyserModel->variableCount());
    EXPECT_EQ(size_t(3), analyserModel->equationCount());

    EXPECT_NE(nullptr, analyserModel->voi());
    EXPECT_NE(nullptr, analyserModel->state(0));
    EXPECT_EQ(nullptr, analyserModel->state(analyserModel->stateCount()));
    EXPECT_NE(nullptr, analyserModel->variable(0));
    EXPECT_EQ(nullptr, analyserModel->variable(analyserModel->variableCount()));
    EXPECT_NE(nullptr, analyserModel->equation(0));
    EXPECT_EQ(nullptr, analyserModel->equation(analyserModel->equationCount()));

    auto generator = libcellml::Generator::create();

    generator->setModel(analyserModel);

    EXPECT_EQ(fileContents("generator/dependent_eqns/model.h"), generator->interfaceCode());
    EXPECT_EQ(fileContents("generator/dependent_eqns/model.c"), generator->implementationCode());

    auto profile = libcellml::GeneratorProfile::create(libcellml::GeneratorProfile::Profile::PYTHON);

    generator->setProfile(profile);

    EXPECT_EQ(EMPTY_STRING, generator->interfaceCode());
    EXPECT_EQ(fileContents("generator/dependent_eqns/model.py"), generator->implementationCode());
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

    EXPECT_EQ(libcellml::AnalyserModel::Type::ALGEBRAIC, analyserModel->type());

    EXPECT_EQ(size_t(0), analyserModel->stateCount());
    EXPECT_EQ(size_t(4), analyserModel->variableCount());
    EXPECT_EQ(size_t(2), analyserModel->equationCount());

    EXPECT_EQ(nullptr, analyserModel->voi());
    EXPECT_EQ(nullptr, analyserModel->state(0));
    EXPECT_NE(nullptr, analyserModel->variable(0));
    EXPECT_EQ(nullptr, analyserModel->variable(analyserModel->variableCount()));
    EXPECT_NE(nullptr, analyserModel->equation(0));
    EXPECT_EQ(nullptr, analyserModel->equation(analyserModel->equationCount()));

    auto generator = libcellml::Generator::create();

    generator->setModel(analyserModel);

    EXPECT_EQ(fileContents("generator/cell_geometry_model/model.h"), generator->interfaceCode());
    EXPECT_EQ(fileContents("generator/cell_geometry_model/model.c"), generator->implementationCode());

    auto profile = libcellml::GeneratorProfile::create(libcellml::GeneratorProfile::Profile::PYTHON);

    generator->setProfile(profile);

    EXPECT_EQ(EMPTY_STRING, generator->interfaceCode());
    EXPECT_EQ(fileContents("generator/cell_geometry_model/model.py"), generator->implementationCode());
}

TEST(Generator, cellGeometryModelWithExternalVariables)
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

    EXPECT_EQ(libcellml::AnalyserModel::Type::ALGEBRAIC, analyserModel->type());

    EXPECT_EQ(size_t(0), analyserModel->stateCount());
    EXPECT_EQ(size_t(4), analyserModel->variableCount());
    EXPECT_EQ(size_t(4), analyserModel->equationCount());

    EXPECT_EQ(nullptr, analyserModel->voi());
    EXPECT_EQ(nullptr, analyserModel->state(0));
    EXPECT_NE(nullptr, analyserModel->variable(0));
    EXPECT_EQ(nullptr, analyserModel->variable(analyserModel->variableCount()));
    EXPECT_NE(nullptr, analyserModel->equation(0));
    EXPECT_EQ(nullptr, analyserModel->equation(analyserModel->equationCount()));

    auto generator = libcellml::Generator::create();

    generator->setModel(analyserModel);

    auto profile = generator->profile();

    profile->setInterfaceFileNameString("model.external.h");

    EXPECT_EQ(fileContents("generator/cell_geometry_model/model.external.h"), generator->interfaceCode());
    EXPECT_EQ(fileContents("generator/cell_geometry_model/model.external.c"), generator->implementationCode());

    profile = libcellml::GeneratorProfile::create(libcellml::GeneratorProfile::Profile::PYTHON);

    generator->setProfile(profile);

    EXPECT_EQ(EMPTY_STRING, generator->interfaceCode());
    EXPECT_EQ(fileContents("generator/cell_geometry_model/model.external.py"), generator->implementationCode());
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

    EXPECT_EQ(libcellml::AnalyserModel::Type::ODE, analyserModel->type());

    EXPECT_EQ(size_t(33), analyserModel->stateCount());
    EXPECT_EQ(size_t(217), analyserModel->variableCount());
    EXPECT_EQ(size_t(159), analyserModel->equationCount());

    EXPECT_NE(nullptr, analyserModel->voi());
    EXPECT_NE(nullptr, analyserModel->state(0));
    EXPECT_EQ(nullptr, analyserModel->state(analyserModel->stateCount()));
    EXPECT_NE(nullptr, analyserModel->variable(0));
    EXPECT_EQ(nullptr, analyserModel->variable(analyserModel->variableCount()));
    EXPECT_NE(nullptr, analyserModel->equation(0));
    EXPECT_EQ(nullptr, analyserModel->equation(analyserModel->equationCount()));

    auto generator = libcellml::Generator::create();

    generator->setModel(analyserModel);

    EXPECT_EQ(fileContents("generator/fabbri_fantini_wilders_severi_human_san_model_2017/model.h"), generator->interfaceCode());
    EXPECT_EQ(fileContents("generator/fabbri_fantini_wilders_severi_human_san_model_2017/model.c"), generator->implementationCode());

    auto profile = libcellml::GeneratorProfile::create(libcellml::GeneratorProfile::Profile::PYTHON);

    generator->setProfile(profile);

    EXPECT_EQ(EMPTY_STRING, generator->interfaceCode());
    EXPECT_EQ(fileContents("generator/fabbri_fantini_wilders_severi_human_san_model_2017/model.py"), generator->implementationCode());
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

    EXPECT_EQ(libcellml::AnalyserModel::Type::ODE, analyserModel->type());

    EXPECT_EQ(size_t(15), analyserModel->stateCount());
    EXPECT_EQ(size_t(185), analyserModel->variableCount());
    EXPECT_EQ(size_t(90), analyserModel->equationCount());

    EXPECT_NE(nullptr, analyserModel->voi());
    EXPECT_NE(nullptr, analyserModel->state(0));
    EXPECT_EQ(nullptr, analyserModel->state(analyserModel->stateCount()));
    EXPECT_NE(nullptr, analyserModel->variable(0));
    EXPECT_EQ(nullptr, analyserModel->variable(analyserModel->variableCount()));
    EXPECT_NE(nullptr, analyserModel->equation(0));
    EXPECT_EQ(nullptr, analyserModel->equation(analyserModel->equationCount()));

    auto generator = libcellml::Generator::create();

    generator->setModel(analyserModel);

    EXPECT_EQ(fileContents("generator/garny_kohl_hunter_boyett_noble_rabbit_san_model_2003/model.h"), generator->interfaceCode());
    EXPECT_EQ(fileContents("generator/garny_kohl_hunter_boyett_noble_rabbit_san_model_2003/model.c"), generator->implementationCode());

    auto profile = libcellml::GeneratorProfile::create(libcellml::GeneratorProfile::Profile::PYTHON);

    generator->setProfile(profile);

    EXPECT_EQ(EMPTY_STRING, generator->interfaceCode());
    EXPECT_EQ(fileContents("generator/garny_kohl_hunter_boyett_noble_rabbit_san_model_2003/model.py"), generator->implementationCode());
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

    EXPECT_EQ(libcellml::AnalyserModel::Type::ODE, analyserModel->type());

    EXPECT_EQ(size_t(4), analyserModel->stateCount());
    EXPECT_EQ(size_t(18), analyserModel->variableCount());
    EXPECT_EQ(size_t(17), analyserModel->equationCount());

    EXPECT_NE(nullptr, analyserModel->voi());
    EXPECT_NE(nullptr, analyserModel->state(0));
    EXPECT_EQ(nullptr, analyserModel->state(analyserModel->stateCount()));
    EXPECT_NE(nullptr, analyserModel->variable(0));
    EXPECT_EQ(nullptr, analyserModel->variable(analyserModel->variableCount()));
    EXPECT_NE(nullptr, analyserModel->equation(0));
    EXPECT_EQ(nullptr, analyserModel->equation(analyserModel->equationCount()));

    auto generator = libcellml::Generator::create();

    generator->setModel(analyserModel);

    EXPECT_EQ(fileContents("generator/hodgkin_huxley_squid_axon_model_1952/model.h"), generator->interfaceCode());
    EXPECT_EQ(fileContents("generator/hodgkin_huxley_squid_axon_model_1952/model.c"), generator->implementationCode());

    auto profile = libcellml::GeneratorProfile::create(libcellml::GeneratorProfile::Profile::PYTHON);

    generator->setProfile(profile);

    EXPECT_EQ(EMPTY_STRING, generator->interfaceCode());
    EXPECT_EQ(fileContents("generator/hodgkin_huxley_squid_axon_model_1952/model.py"), generator->implementationCode());
}

TEST(Generator, hodgkinHuxleySquidAxonModel1952WithStateAsExternalVariable)
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

    EXPECT_EQ(libcellml::AnalyserModel::Type::ODE, analyserModel->type());

    EXPECT_EQ(size_t(3), analyserModel->stateCount());
    EXPECT_EQ(size_t(19), analyserModel->variableCount());
    EXPECT_EQ(size_t(17), analyserModel->equationCount());

    EXPECT_NE(nullptr, analyserModel->voi());
    EXPECT_NE(nullptr, analyserModel->state(0));
    EXPECT_EQ(nullptr, analyserModel->state(analyserModel->stateCount()));
    EXPECT_NE(nullptr, analyserModel->variable(0));
    EXPECT_EQ(nullptr, analyserModel->variable(analyserModel->variableCount()));
    EXPECT_NE(nullptr, analyserModel->equation(0));
    EXPECT_EQ(nullptr, analyserModel->equation(analyserModel->equationCount()));

    auto generator = libcellml::Generator::create();

    generator->setModel(analyserModel);

    auto profile = generator->profile();

    profile->setInterfaceFileNameString("model.state.h");

    EXPECT_EQ(fileContents("generator/hodgkin_huxley_squid_axon_model_1952/model.state.h"), generator->interfaceCode());
    EXPECT_EQ(fileContents("generator/hodgkin_huxley_squid_axon_model_1952/model.state.c"), generator->implementationCode());

    profile = libcellml::GeneratorProfile::create(libcellml::GeneratorProfile::Profile::PYTHON);

    generator->setProfile(profile);

    EXPECT_EQ(EMPTY_STRING, generator->interfaceCode());
    EXPECT_EQ(fileContents("generator/hodgkin_huxley_squid_axon_model_1952/model.state.py"), generator->implementationCode());
}

TEST(Generator, hodgkinHuxleySquidAxonModel1952WithDependentStateExternalVariable)
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

    EXPECT_EQ(libcellml::AnalyserModel::Type::ODE, analyserModel->type());

    EXPECT_EQ(size_t(2), analyserModel->stateCount());
    EXPECT_EQ(size_t(20), analyserModel->variableCount());
    EXPECT_EQ(size_t(17), analyserModel->equationCount());

    EXPECT_NE(nullptr, analyserModel->voi());
    EXPECT_NE(nullptr, analyserModel->state(0));
    EXPECT_EQ(nullptr, analyserModel->state(analyserModel->stateCount()));
    EXPECT_NE(nullptr, analyserModel->variable(0));
    EXPECT_EQ(nullptr, analyserModel->variable(analyserModel->variableCount()));
    EXPECT_NE(nullptr, analyserModel->equation(0));
    EXPECT_EQ(nullptr, analyserModel->equation(analyserModel->equationCount()));

    auto generator = libcellml::Generator::create();

    generator->setModel(analyserModel);

    auto profile = generator->profile();

    profile->setInterfaceFileNameString("model.dependent.state.h");

    EXPECT_EQ(fileContents("generator/hodgkin_huxley_squid_axon_model_1952/model.dependent.state.h"), generator->interfaceCode());
    EXPECT_EQ(fileContents("generator/hodgkin_huxley_squid_axon_model_1952/model.dependent.state.c"), generator->implementationCode());

    profile = libcellml::GeneratorProfile::create(libcellml::GeneratorProfile::Profile::PYTHON);

    generator->setProfile(profile);

    EXPECT_EQ(EMPTY_STRING, generator->interfaceCode());
    EXPECT_EQ(fileContents("generator/hodgkin_huxley_squid_axon_model_1952/model.dependent.state.py"), generator->implementationCode());
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

    EXPECT_EQ(libcellml::AnalyserModel::Type::ODE, analyserModel->type());

    EXPECT_EQ(size_t(4), analyserModel->stateCount());
    EXPECT_EQ(size_t(18), analyserModel->variableCount());
    EXPECT_EQ(size_t(18), analyserModel->equationCount());

    EXPECT_NE(nullptr, analyserModel->voi());
    EXPECT_NE(nullptr, analyserModel->state(0));
    EXPECT_EQ(nullptr, analyserModel->state(analyserModel->stateCount()));
    EXPECT_NE(nullptr, analyserModel->variable(0));
    EXPECT_EQ(nullptr, analyserModel->variable(analyserModel->variableCount()));
    EXPECT_NE(nullptr, analyserModel->equation(0));
    EXPECT_EQ(nullptr, analyserModel->equation(analyserModel->equationCount()));

    auto generator = libcellml::Generator::create();

    generator->setModel(analyserModel);

    auto profile = generator->profile();

    profile->setInterfaceFileNameString("model.constant.h");

    EXPECT_EQ(fileContents("generator/hodgkin_huxley_squid_axon_model_1952/model.constant.h"), generator->interfaceCode());
    EXPECT_EQ(fileContents("generator/hodgkin_huxley_squid_axon_model_1952/model.constant.c"), generator->implementationCode());

    profile = libcellml::GeneratorProfile::create(libcellml::GeneratorProfile::Profile::PYTHON);

    generator->setProfile(profile);

    EXPECT_EQ(EMPTY_STRING, generator->interfaceCode());
    EXPECT_EQ(fileContents("generator/hodgkin_huxley_squid_axon_model_1952/model.constant.py"), generator->implementationCode());
}

TEST(Generator, hodgkinHuxleySquidAxonModel1952WithDependentConstantAsExternalVariable)
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

    EXPECT_EQ(libcellml::AnalyserModel::Type::ODE, analyserModel->type());

    EXPECT_EQ(size_t(4), analyserModel->stateCount());
    EXPECT_EQ(size_t(18), analyserModel->variableCount());
    EXPECT_EQ(size_t(19), analyserModel->equationCount());

    EXPECT_NE(nullptr, analyserModel->voi());
    EXPECT_NE(nullptr, analyserModel->state(0));
    EXPECT_EQ(nullptr, analyserModel->state(analyserModel->stateCount()));
    EXPECT_NE(nullptr, analyserModel->variable(0));
    EXPECT_EQ(nullptr, analyserModel->variable(analyserModel->variableCount()));
    EXPECT_NE(nullptr, analyserModel->equation(0));
    EXPECT_EQ(nullptr, analyserModel->equation(analyserModel->equationCount()));

    auto generator = libcellml::Generator::create();

    generator->setModel(analyserModel);

    auto profile = generator->profile();

    profile->setInterfaceFileNameString("model.dependent.constant.h");

    EXPECT_EQ(fileContents("generator/hodgkin_huxley_squid_axon_model_1952/model.dependent.constant.h"), generator->interfaceCode());
    EXPECT_EQ(fileContents("generator/hodgkin_huxley_squid_axon_model_1952/model.dependent.constant.c"), generator->implementationCode());

    profile = libcellml::GeneratorProfile::create(libcellml::GeneratorProfile::Profile::PYTHON);

    generator->setProfile(profile);

    EXPECT_EQ(EMPTY_STRING, generator->interfaceCode());
    EXPECT_EQ(fileContents("generator/hodgkin_huxley_squid_axon_model_1952/model.dependent.constant.py"), generator->implementationCode());
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

    EXPECT_EQ(libcellml::AnalyserModel::Type::ODE, analyserModel->type());

    EXPECT_EQ(size_t(4), analyserModel->stateCount());
    EXPECT_EQ(size_t(18), analyserModel->variableCount());
    EXPECT_EQ(size_t(17), analyserModel->equationCount());

    EXPECT_NE(nullptr, analyserModel->voi());
    EXPECT_NE(nullptr, analyserModel->state(0));
    EXPECT_EQ(nullptr, analyserModel->state(analyserModel->stateCount()));
    EXPECT_NE(nullptr, analyserModel->variable(0));
    EXPECT_EQ(nullptr, analyserModel->variable(analyserModel->variableCount()));
    EXPECT_NE(nullptr, analyserModel->equation(0));
    EXPECT_EQ(nullptr, analyserModel->equation(analyserModel->equationCount()));

    auto generator = libcellml::Generator::create();

    generator->setModel(analyserModel);

    auto profile = generator->profile();

    profile->setInterfaceFileNameString("model.computed.constant.h");

    EXPECT_EQ(fileContents("generator/hodgkin_huxley_squid_axon_model_1952/model.computed.constant.h"), generator->interfaceCode());
    EXPECT_EQ(fileContents("generator/hodgkin_huxley_squid_axon_model_1952/model.computed.constant.c"), generator->implementationCode());

    profile = libcellml::GeneratorProfile::create(libcellml::GeneratorProfile::Profile::PYTHON);

    generator->setProfile(profile);

    EXPECT_EQ(EMPTY_STRING, generator->interfaceCode());
    EXPECT_EQ(fileContents("generator/hodgkin_huxley_squid_axon_model_1952/model.computed.constant.py"), generator->implementationCode());
}

TEST(Generator, hodgkinHuxleySquidAxonModel1952WithDependentComputedConstantAsExternalVariable)
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

    EXPECT_EQ(libcellml::AnalyserModel::Type::ODE, analyserModel->type());

    EXPECT_EQ(size_t(4), analyserModel->stateCount());
    EXPECT_EQ(size_t(18), analyserModel->variableCount());
    EXPECT_EQ(size_t(18), analyserModel->equationCount());

    EXPECT_NE(nullptr, analyserModel->voi());
    EXPECT_NE(nullptr, analyserModel->state(0));
    EXPECT_EQ(nullptr, analyserModel->state(analyserModel->stateCount()));
    EXPECT_NE(nullptr, analyserModel->variable(0));
    EXPECT_EQ(nullptr, analyserModel->variable(analyserModel->variableCount()));
    EXPECT_NE(nullptr, analyserModel->equation(0));
    EXPECT_EQ(nullptr, analyserModel->equation(analyserModel->equationCount()));

    auto generator = libcellml::Generator::create();

    generator->setModel(analyserModel);

    auto profile = generator->profile();

    profile->setInterfaceFileNameString("model.dependent.computed.constant.h");

    EXPECT_EQ(fileContents("generator/hodgkin_huxley_squid_axon_model_1952/model.dependent.computed.constant.h"), generator->interfaceCode());
    EXPECT_EQ(fileContents("generator/hodgkin_huxley_squid_axon_model_1952/model.dependent.computed.constant.c"), generator->implementationCode());

    profile = libcellml::GeneratorProfile::create(libcellml::GeneratorProfile::Profile::PYTHON);

    generator->setProfile(profile);

    EXPECT_EQ(EMPTY_STRING, generator->interfaceCode());
    EXPECT_EQ(fileContents("generator/hodgkin_huxley_squid_axon_model_1952/model.dependent.computed.constant.py"), generator->implementationCode());
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

    EXPECT_EQ(libcellml::AnalyserModel::Type::ODE, analyserModel->type());

    EXPECT_EQ(size_t(4), analyserModel->stateCount());
    EXPECT_EQ(size_t(18), analyserModel->variableCount());
    EXPECT_EQ(size_t(17), analyserModel->equationCount());

    EXPECT_NE(nullptr, analyserModel->voi());
    EXPECT_NE(nullptr, analyserModel->state(0));
    EXPECT_EQ(nullptr, analyserModel->state(analyserModel->stateCount()));
    EXPECT_NE(nullptr, analyserModel->variable(0));
    EXPECT_EQ(nullptr, analyserModel->variable(analyserModel->variableCount()));
    EXPECT_NE(nullptr, analyserModel->equation(0));
    EXPECT_EQ(nullptr, analyserModel->equation(analyserModel->equationCount()));

    auto generator = libcellml::Generator::create();

    generator->setModel(analyserModel);

    auto profile = generator->profile();

    profile->setInterfaceFileNameString("model.algebraic.h");

    EXPECT_EQ(fileContents("generator/hodgkin_huxley_squid_axon_model_1952/model.algebraic.h"), generator->interfaceCode());
    EXPECT_EQ(fileContents("generator/hodgkin_huxley_squid_axon_model_1952/model.algebraic.c"), generator->implementationCode());

    profile = libcellml::GeneratorProfile::create(libcellml::GeneratorProfile::Profile::PYTHON);

    generator->setProfile(profile);

    EXPECT_EQ(EMPTY_STRING, generator->interfaceCode());
    EXPECT_EQ(fileContents("generator/hodgkin_huxley_squid_axon_model_1952/model.algebraic.py"), generator->implementationCode());
}

TEST(Generator, hodgkinHuxleySquidAxonModel1952WithDependentAlgebraicVariableAsExternalVariable)
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

    EXPECT_EQ(libcellml::AnalyserModel::Type::ODE, analyserModel->type());

    EXPECT_EQ(size_t(4), analyserModel->stateCount());
    EXPECT_EQ(size_t(18), analyserModel->variableCount());
    EXPECT_EQ(size_t(17), analyserModel->equationCount());

    EXPECT_NE(nullptr, analyserModel->voi());
    EXPECT_NE(nullptr, analyserModel->state(0));
    EXPECT_EQ(nullptr, analyserModel->state(analyserModel->stateCount()));
    EXPECT_NE(nullptr, analyserModel->variable(0));
    EXPECT_EQ(nullptr, analyserModel->variable(analyserModel->variableCount()));
    EXPECT_NE(nullptr, analyserModel->equation(0));
    EXPECT_EQ(nullptr, analyserModel->equation(analyserModel->equationCount()));

    auto generator = libcellml::Generator::create();

    generator->setModel(analyserModel);

    auto profile = generator->profile();

    profile->setInterfaceFileNameString("model.dependent.algebraic.h");

    EXPECT_EQ(fileContents("generator/hodgkin_huxley_squid_axon_model_1952/model.dependent.algebraic.h"), generator->interfaceCode());
    EXPECT_EQ(fileContents("generator/hodgkin_huxley_squid_axon_model_1952/model.dependent.algebraic.c"), generator->implementationCode());

    profile = libcellml::GeneratorProfile::create(libcellml::GeneratorProfile::Profile::PYTHON);

    generator->setProfile(profile);

    EXPECT_EQ(EMPTY_STRING, generator->interfaceCode());
    EXPECT_EQ(fileContents("generator/hodgkin_huxley_squid_axon_model_1952/model.dependent.algebraic.py"), generator->implementationCode());
}

TEST(Generator, hodgkinHuxleySquidAxonModel1952WithExternalVariables)
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

    EXPECT_EQ(libcellml::AnalyserModel::Type::ODE, analyserModel->type());

    EXPECT_EQ(size_t(3), analyserModel->stateCount());
    EXPECT_EQ(size_t(19), analyserModel->variableCount());
    EXPECT_EQ(size_t(17), analyserModel->equationCount());

    EXPECT_NE(nullptr, analyserModel->voi());
    EXPECT_NE(nullptr, analyserModel->state(0));
    EXPECT_EQ(nullptr, analyserModel->state(analyserModel->stateCount()));
    EXPECT_NE(nullptr, analyserModel->variable(0));
    EXPECT_EQ(nullptr, analyserModel->variable(analyserModel->variableCount()));
    EXPECT_NE(nullptr, analyserModel->equation(0));
    EXPECT_EQ(nullptr, analyserModel->equation(analyserModel->equationCount()));

    auto generator = libcellml::Generator::create();

    generator->setModel(analyserModel);

    auto profile = generator->profile();

    profile->setInterfaceFileNameString("model.external.h");

    EXPECT_EQ(fileContents("generator/hodgkin_huxley_squid_axon_model_1952/model.external.h"), generator->interfaceCode());
    EXPECT_EQ(fileContents("generator/hodgkin_huxley_squid_axon_model_1952/model.external.c"), generator->implementationCode());

    profile = libcellml::GeneratorProfile::create(libcellml::GeneratorProfile::Profile::PYTHON);

    generator->setProfile(profile);

    EXPECT_EQ(EMPTY_STRING, generator->interfaceCode());
    EXPECT_EQ(fileContents("generator/hodgkin_huxley_squid_axon_model_1952/model.external.py"), generator->implementationCode());
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

    EXPECT_EQ(libcellml::AnalyserModel::Type::ODE, analyserModel->type());

    EXPECT_EQ(size_t(4), analyserModel->stateCount());
    EXPECT_EQ(size_t(17), analyserModel->variableCount());
    EXPECT_EQ(size_t(16), analyserModel->equationCount());

    EXPECT_NE(nullptr, analyserModel->voi());
    EXPECT_NE(nullptr, analyserModel->state(0));
    EXPECT_EQ(nullptr, analyserModel->state(analyserModel->stateCount()));
    EXPECT_NE(nullptr, analyserModel->variable(0));
    EXPECT_EQ(nullptr, analyserModel->variable(analyserModel->variableCount()));
    EXPECT_NE(nullptr, analyserModel->equation(0));
    EXPECT_EQ(nullptr, analyserModel->equation(analyserModel->equationCount()));

    auto generator = libcellml::Generator::create();

    generator->setModel(analyserModel);

    EXPECT_EQ(fileContents("generator/noble_model_1962/model.h"), generator->interfaceCode());
    EXPECT_EQ(fileContents("generator/noble_model_1962/model.c"), generator->implementationCode());

    auto profile = libcellml::GeneratorProfile::create(libcellml::GeneratorProfile::Profile::PYTHON);

    generator->setProfile(profile);

    EXPECT_EQ(EMPTY_STRING, generator->interfaceCode());
    EXPECT_EQ(fileContents("generator/noble_model_1962/model.py"), generator->implementationCode());
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

    EXPECT_EQ(libcellml::AnalyserModel::Type::ODE, analyserModel->type());

    EXPECT_EQ(size_t(1), analyserModel->stateCount());
    EXPECT_EQ(size_t(10), analyserModel->variableCount());
    EXPECT_EQ(size_t(9), analyserModel->equationCount());

    EXPECT_NE(nullptr, analyserModel->voi());
    EXPECT_NE(nullptr, analyserModel->state(0));
    EXPECT_EQ(nullptr, analyserModel->state(analyserModel->stateCount()));
    EXPECT_NE(nullptr, analyserModel->variable(0));
    EXPECT_EQ(nullptr, analyserModel->variable(analyserModel->variableCount()));
    EXPECT_NE(nullptr, analyserModel->equation(0));
    EXPECT_EQ(nullptr, analyserModel->equation(analyserModel->equationCount()));

    auto generator = libcellml::Generator::create();

    generator->setModel(analyserModel);

    EXPECT_EQ(fileContents("generator/sine_model_imports/model.h"), generator->interfaceCode());
    EXPECT_EQ(fileContents("generator/sine_model_imports/model.c"), generator->implementationCode());

    auto profile = libcellml::GeneratorProfile::create(libcellml::GeneratorProfile::Profile::PYTHON);

    generator->setProfile(profile);

    EXPECT_EQ(EMPTY_STRING, generator->interfaceCode());
    EXPECT_EQ(fileContents("generator/sine_model_imports/model.py"), generator->implementationCode());
}

TEST(Generator, coverage)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("generator/coverage/model.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    auto analyser = libcellml::Analyser::create();

    analyser->analyseModel(model);

    EXPECT_EQ(size_t(0), analyser->errorCount());

    auto analyserModel = analyser->model();

    EXPECT_EQ(libcellml::AnalyserModel::Type::ODE, analyserModel->type());

    EXPECT_EQ(size_t(1), analyserModel->stateCount());
    EXPECT_EQ(size_t(186), analyserModel->variableCount());
    EXPECT_EQ(size_t(180), analyserModel->equationCount());

    EXPECT_NE(nullptr, analyserModel->voi());
    EXPECT_EQ(nullptr, analyserModel->voi()->equation());
    EXPECT_NE(nullptr, analyserModel->state(0));
    EXPECT_NE(nullptr, analyserModel->state(0)->equation());
    EXPECT_EQ(nullptr, analyserModel->state(analyserModel->stateCount()));
    EXPECT_NE(nullptr, analyserModel->variable(0));
    EXPECT_EQ(nullptr, analyserModel->variable(analyserModel->variableCount()));
    EXPECT_NE(nullptr, analyserModel->equation(0));
    EXPECT_NE(nullptr, analyserModel->equation(0)->variable());
    EXPECT_EQ(nullptr, analyserModel->equation(analyserModel->equationCount()));

    auto generator = libcellml::Generator::create();

    EXPECT_EQ(nullptr, analyserModel->voi()->initialisingVariable());

    for (size_t i = 0; i < analyserModel->stateCount(); ++i) {
        EXPECT_NE(nullptr, analyserModel->state(i)->initialisingVariable());
    }

    for (size_t i = 0; i < analyserModel->variableCount(); ++i) {
        EXPECT_EQ(i < 7, analyserModel->variable(i)->initialisingVariable() != nullptr);
    }

    EXPECT_EQ(nullptr, generator->model());
    EXPECT_EQ(EMPTY_STRING, generator->interfaceCode());
    EXPECT_EQ(EMPTY_STRING, generator->implementationCode());

    generator->setModel(analyserModel);

    EXPECT_EQ(analyserModel, generator->model());
    EXPECT_EQ(fileContents("generator/coverage/model.h"), generator->interfaceCode());
    EXPECT_EQ(fileContents("generator/coverage/model.c"), generator->implementationCode());

    auto profile = generator->profile();

    profile->setInterfaceCreateStatesArrayMethodString("double * createStatesVector();\n");
    profile->setImplementationCreateStatesArrayMethodString("double * createStatesVector()\n"
                                                            "{\n"
                                                            "    return malloc(STATE_COUNT*sizeof(double));\n"
                                                            "}\n");

    EXPECT_EQ(fileContents("generator/coverage/model.modified.profile.h"), generator->interfaceCode());
    EXPECT_EQ(fileContents("generator/coverage/model.modified.profile.c"), generator->implementationCode());

    profile = libcellml::GeneratorProfile::create();

    generator->setProfile(profile);

    profile->setHasInterface(false);

    profile->setXorString("^");
    profile->setHasXorOperator(true);

    profile->setPowerString("^^");
    profile->setSquareString("sqr");
    profile->setHasPowerOperator(true);

    profile->setPiecewiseIfString("piecewise([CONDITION], [IF_STATEMENT]");
    profile->setPiecewiseElseString(", [ELSE_STATEMENT])");
    profile->setHasConditionalOperator(false);

    profile->setInterfaceFileNameString("customheaderfile.h");

    profile->setImplementationHeaderString("#include \"[INTERFACE_FILE_NAME]\"\n");

    profile->setImplementationVersionString("");

    profile->setImplementationLibcellmlVersionString("");

    profile->setImplementationStateCountString("");

    profile->setImplementationVariableCountString("");

    profile->setVariableTypeObjectString(false, false, "");
    profile->setVariableTypeObjectString(false, true, "");
    profile->setVariableTypeObjectString(true, false, "");
    profile->setVariableTypeObjectString(true, true, "");

    profile->setVariableOfIntegrationVariableTypeString("");
    profile->setStateVariableTypeString("");
    profile->setConstantVariableTypeString("");
    profile->setComputedConstantVariableTypeString("");
    profile->setAlgebraicVariableTypeString("");
    profile->setExternalVariableTypeString("");

    profile->setVariableInfoObjectString("");

    profile->setImplementationVoiInfoString("");

    profile->setImplementationStateInfoString("");

    profile->setImplementationVariableInfoString("");

    profile->setVariableInfoEntryString("");

    profile->setImplementationCreateStatesArrayMethodString("");

    profile->setImplementationCreateVariablesArrayMethodString("");

    profile->setImplementationDeleteArrayMethodString("");

    profile->setImplementationComputeVariablesMethodString(false, false, "");
    profile->setImplementationComputeVariablesMethodString(false, true, "");
    profile->setImplementationComputeVariablesMethodString(true, false, "");
    profile->setImplementationComputeVariablesMethodString(true, true, "");

    EXPECT_EQ(EMPTY_STRING, generator->interfaceCode());
    EXPECT_EQ(fileContents("generator/coverage/model.out"), generator->implementationCode());

    profile = libcellml::GeneratorProfile::create();

    generator->setProfile(profile);

    profile->setHasInterface(true);

    profile->setEqString("eq");
    profile->setNeqString("neq");
    profile->setLtString("lt");
    profile->setLeqString("leq");
    profile->setGtString("gt");
    profile->setGeqString("geq");
    profile->setAndString("and");
    profile->setOrString("or");
    profile->setNotString("not");

    profile->setHasEqOperator(false);
    profile->setHasNeqOperator(false);
    profile->setHasLtOperator(false);
    profile->setHasLeqOperator(false);
    profile->setHasGtOperator(false);
    profile->setHasGeqOperator(false);
    profile->setHasAndOperator(false);
    profile->setHasOrOperator(false);
    profile->setHasNotOperator(false);

    profile->setImplementationHeaderString("");

    profile->setInterfaceVersionString("");
    profile->setImplementationVersionString("");

    profile->setInterfaceLibcellmlVersionString("");
    profile->setImplementationLibcellmlVersionString("");

    profile->setInterfaceStateCountString("");
    profile->setImplementationStateCountString("");

    profile->setInterfaceVariableCountString("");
    profile->setImplementationVariableCountString("");

    profile->setVariableTypeObjectString(false, false, "");
    profile->setVariableTypeObjectString(false, true, "");
    profile->setVariableTypeObjectString(true, false, "");
    profile->setVariableTypeObjectString(true, true, "");

    profile->setVariableOfIntegrationVariableTypeString("");
    profile->setStateVariableTypeString("");
    profile->setConstantVariableTypeString("");
    profile->setComputedConstantVariableTypeString("");
    profile->setAlgebraicVariableTypeString("");
    profile->setExternalVariableTypeString("");

    profile->setVariableInfoObjectString("");

    profile->setInterfaceVoiInfoString("");
    profile->setImplementationVoiInfoString("");

    profile->setInterfaceStateInfoString("");
    profile->setImplementationStateInfoString("");

    profile->setInterfaceVariableInfoString("");
    profile->setImplementationVariableInfoString("");

    profile->setVariableInfoEntryString("");

    EXPECT_EQ(fileContents("generator/coverage/model.interface.out"), generator->interfaceCode());
    EXPECT_EQ(fileContents("generator/coverage/model.implementation.out"), generator->implementationCode());

    profile->setProfile(libcellml::GeneratorProfile::Profile::PYTHON);

    EXPECT_EQ(EMPTY_STRING, generator->interfaceCode());
    EXPECT_EQ(fileContents("generator/coverage/model.py"), generator->implementationCode());

    profile->setImplementationCreateStatesArrayMethodString("\n"
                                                            "def create_states_vector():\n"
                                                            "    return [nan]*STATE_COUNT\n");

    EXPECT_EQ(EMPTY_STRING, generator->interfaceCode());
    EXPECT_EQ(fileContents("generator/coverage/model.modified.profile.py"), generator->implementationCode());
}

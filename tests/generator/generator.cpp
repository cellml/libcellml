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

/*
TEST(Generator, emptyModel)
{
    libcellml::ModelPtr model = libcellml::Model::create("empty_model");
    libcellml::AnalyserPtr analyser = libcellml::Analyser::create();

    analyser->processModel(model);

    EXPECT_EQ(size_t(0), analyser->issueCount());

    auto analyserModel = analyser->model();
    auto generator = libcellml::Generator::create();

    EXPECT_EQ(EMPTY_STRING, generator->interfaceCode(analyserModel));
    EXPECT_EQ(EMPTY_STRING, generator->implementationCode(analyserModel));
}

TEST(Generator, algebraicEqnComputedVarOnRhs)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("generator/algebraic_eqn_computed_var_on_rhs/model.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    auto analyser = libcellml::Analyser::create();

    analyser->processModel(model);

    EXPECT_EQ(size_t(0), analyser->issueCount());

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

    EXPECT_EQ(fileContents("generator/algebraic_eqn_computed_var_on_rhs/model.h"), generator->interfaceCode(analyserModel));
    EXPECT_EQ(fileContents("generator/algebraic_eqn_computed_var_on_rhs/model.c"), generator->implementationCode(analyserModel));

    auto profile = libcellml::GeneratorProfile::create(libcellml::GeneratorProfile::Profile::PYTHON);

    generator->setProfile(profile);

    EXPECT_EQ(EMPTY_STRING, generator->interfaceCode(analyserModel));
    EXPECT_EQ(fileContents("generator/algebraic_eqn_computed_var_on_rhs/model.py"), generator->implementationCode(analyserModel));
}

TEST(Generator, algebraicEqnConstVarOnRhs)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("generator/algebraic_eqn_const_var_on_rhs/model.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    auto analyser = libcellml::Analyser::create();

    analyser->processModel(model);

    EXPECT_EQ(size_t(0), analyser->issueCount());

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

    EXPECT_EQ(fileContents("generator/algebraic_eqn_const_var_on_rhs/model.h"), generator->interfaceCode(analyserModel));
    EXPECT_EQ(fileContents("generator/algebraic_eqn_const_var_on_rhs/model.c"), generator->implementationCode(analyserModel));

    auto profile = libcellml::GeneratorProfile::create(libcellml::GeneratorProfile::Profile::PYTHON);

    generator->setProfile(profile);

    EXPECT_EQ(EMPTY_STRING, generator->interfaceCode(analyserModel));
    EXPECT_EQ(fileContents("generator/algebraic_eqn_const_var_on_rhs/model.py"), generator->implementationCode(analyserModel));
}

TEST(Generator, algebraicEqnConstantOnRhs)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("generator/algebraic_eqn_constant_on_rhs/model.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    auto analyser = libcellml::Analyser::create();

    analyser->processModel(model);

    EXPECT_EQ(size_t(0), analyser->issueCount());

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

    EXPECT_EQ(fileContents("generator/algebraic_eqn_constant_on_rhs/model.h"), generator->interfaceCode(analyserModel));
    EXPECT_EQ(fileContents("generator/algebraic_eqn_constant_on_rhs/model.c"), generator->implementationCode(analyserModel));

    auto profile = libcellml::GeneratorProfile::create(libcellml::GeneratorProfile::Profile::PYTHON);

    generator->setProfile(profile);

    EXPECT_EQ(EMPTY_STRING, generator->interfaceCode(analyserModel));
    EXPECT_EQ(fileContents("generator/algebraic_eqn_constant_on_rhs/model.py"), generator->implementationCode(analyserModel));
}

TEST(Generator, algebraicEqnDerivativeOnRhs)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("generator/algebraic_eqn_derivative_on_rhs/model.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    auto analyser = libcellml::Analyser::create();

    analyser->processModel(model);

    EXPECT_EQ(size_t(0), analyser->issueCount());

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

    EXPECT_EQ(fileContents("generator/algebraic_eqn_derivative_on_rhs/model.h"), generator->interfaceCode(analyserModel));
    EXPECT_EQ(fileContents("generator/algebraic_eqn_derivative_on_rhs/model.c"), generator->implementationCode(analyserModel));

    auto profile = libcellml::GeneratorProfile::create(libcellml::GeneratorProfile::Profile::PYTHON);

    generator->setProfile(profile);

    EXPECT_EQ(EMPTY_STRING, generator->interfaceCode(analyserModel));
    EXPECT_EQ(fileContents("generator/algebraic_eqn_derivative_on_rhs/model.py"), generator->implementationCode(analyserModel));
}

TEST(Generator, algebraicEqnDerivativeOnRhsOneComponent)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("generator/algebraic_eqn_derivative_on_rhs_one_component/model.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    auto analyser = libcellml::Analyser::create();

    analyser->processModel(model);

    EXPECT_EQ(size_t(0), analyser->issueCount());

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

    EXPECT_EQ(fileContents("generator/algebraic_eqn_derivative_on_rhs_one_component/model.h"), generator->interfaceCode(analyserModel));
    EXPECT_EQ(fileContents("generator/algebraic_eqn_derivative_on_rhs_one_component/model.c"), generator->implementationCode(analyserModel));

    auto profile = libcellml::GeneratorProfile::create(libcellml::GeneratorProfile::Profile::PYTHON);

    generator->setProfile(profile);

    EXPECT_EQ(EMPTY_STRING, generator->interfaceCode(analyserModel));
    EXPECT_EQ(fileContents("generator/algebraic_eqn_derivative_on_rhs_one_component/model.py"), generator->implementationCode(analyserModel));
}

TEST(Generator, algebraicEqnStateVarOnRhs)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("generator/algebraic_eqn_state_var_on_rhs/model.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    auto analyser = libcellml::Analyser::create();

    analyser->processModel(model);

    EXPECT_EQ(size_t(0), analyser->issueCount());

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

    EXPECT_EQ(fileContents("generator/algebraic_eqn_state_var_on_rhs/model.h"), generator->interfaceCode(analyserModel));
    EXPECT_EQ(fileContents("generator/algebraic_eqn_state_var_on_rhs/model.c"), generator->implementationCode(analyserModel));

    auto profile = libcellml::GeneratorProfile::create(libcellml::GeneratorProfile::Profile::PYTHON);

    generator->setProfile(profile);

    EXPECT_EQ(EMPTY_STRING, generator->interfaceCode(analyserModel));
    EXPECT_EQ(fileContents("generator/algebraic_eqn_state_var_on_rhs/model.py"), generator->implementationCode(analyserModel));
}

TEST(Generator, algebraicEqnStateVarOnRhsOneComponent)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("generator/algebraic_eqn_state_var_on_rhs_one_component/model.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    auto analyser = libcellml::Analyser::create();

    analyser->processModel(model);

    EXPECT_EQ(size_t(0), analyser->issueCount());

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

    EXPECT_EQ(fileContents("generator/algebraic_eqn_state_var_on_rhs_one_component/model.h"), generator->interfaceCode(analyserModel));
    EXPECT_EQ(fileContents("generator/algebraic_eqn_state_var_on_rhs_one_component/model.c"), generator->implementationCode(analyserModel));

    auto profile = libcellml::GeneratorProfile::create(libcellml::GeneratorProfile::Profile::PYTHON);

    generator->setProfile(profile);

    EXPECT_EQ(EMPTY_STRING, generator->interfaceCode(analyserModel));
    EXPECT_EQ(fileContents("generator/algebraic_eqn_state_var_on_rhs_one_component/model.py"), generator->implementationCode(analyserModel));
}

TEST(Generator, odeComputedVarOnRhs)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("generator/ode_computed_var_on_rhs/model.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    auto analyser = libcellml::Analyser::create();

    analyser->processModel(model);

    EXPECT_EQ(size_t(0), analyser->issueCount());

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

    EXPECT_EQ(fileContents("generator/ode_computed_var_on_rhs/model.h"), generator->interfaceCode(analyserModel));
    EXPECT_EQ(fileContents("generator/ode_computed_var_on_rhs/model.c"), generator->implementationCode(analyserModel));

    auto profile = libcellml::GeneratorProfile::create(libcellml::GeneratorProfile::Profile::PYTHON);

    generator->setProfile(profile);

    EXPECT_EQ(EMPTY_STRING, generator->interfaceCode(analyserModel));
    EXPECT_EQ(fileContents("generator/ode_computed_var_on_rhs/model.py"), generator->implementationCode(analyserModel));
}

TEST(Generator, odeComputedVarOnRhsOneComponent)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("generator/ode_computed_var_on_rhs_one_component/model.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    auto analyser = libcellml::Analyser::create();

    analyser->processModel(model);

    EXPECT_EQ(size_t(0), analyser->issueCount());

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

    EXPECT_EQ(fileContents("generator/ode_computed_var_on_rhs_one_component/model.h"), generator->interfaceCode(analyserModel));
    EXPECT_EQ(fileContents("generator/ode_computed_var_on_rhs_one_component/model.c"), generator->implementationCode(analyserModel));

    auto profile = libcellml::GeneratorProfile::create(libcellml::GeneratorProfile::Profile::PYTHON);

    generator->setProfile(profile);

    EXPECT_EQ(EMPTY_STRING, generator->interfaceCode(analyserModel));
    EXPECT_EQ(fileContents("generator/ode_computed_var_on_rhs_one_component/model.py"), generator->implementationCode(analyserModel));
}

TEST(Generator, odeConstVarOnRhs)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("generator/ode_const_var_on_rhs/model.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    auto analyser = libcellml::Analyser::create();

    analyser->processModel(model);

    EXPECT_EQ(size_t(0), analyser->issueCount());

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

    EXPECT_EQ(fileContents("generator/ode_const_var_on_rhs/model.h"), generator->interfaceCode(analyserModel));
    EXPECT_EQ(fileContents("generator/ode_const_var_on_rhs/model.c"), generator->implementationCode(analyserModel));

    auto profile = libcellml::GeneratorProfile::create(libcellml::GeneratorProfile::Profile::PYTHON);

    generator->setProfile(profile);

    EXPECT_EQ(EMPTY_STRING, generator->interfaceCode(analyserModel));
    EXPECT_EQ(fileContents("generator/ode_const_var_on_rhs/model.py"), generator->implementationCode(analyserModel));
}

TEST(Generator, odeConstVarOnRhsOneComponent)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("generator/ode_const_var_on_rhs_one_component/model.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    auto analyser = libcellml::Analyser::create();

    analyser->processModel(model);

    EXPECT_EQ(size_t(0), analyser->issueCount());

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

    EXPECT_EQ(fileContents("generator/ode_const_var_on_rhs_one_component/model.h"), generator->interfaceCode(analyserModel));
    EXPECT_EQ(fileContents("generator/ode_const_var_on_rhs_one_component/model.c"), generator->implementationCode(analyserModel));

    auto profile = libcellml::GeneratorProfile::create(libcellml::GeneratorProfile::Profile::PYTHON);

    generator->setProfile(profile);

    EXPECT_EQ(EMPTY_STRING, generator->interfaceCode(analyserModel));
    EXPECT_EQ(fileContents("generator/ode_const_var_on_rhs_one_component/model.py"), generator->implementationCode(analyserModel));
}

TEST(Generator, odeConstantOnRhs)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("generator/ode_constant_on_rhs/model.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    auto analyser = libcellml::Analyser::create();

    analyser->processModel(model);

    EXPECT_EQ(size_t(0), analyser->issueCount());

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

    EXPECT_EQ(fileContents("generator/ode_constant_on_rhs/model.h"), generator->interfaceCode(analyserModel));
    EXPECT_EQ(fileContents("generator/ode_constant_on_rhs/model.c"), generator->implementationCode(analyserModel));

    auto profile = libcellml::GeneratorProfile::create(libcellml::GeneratorProfile::Profile::PYTHON);

    generator->setProfile(profile);

    EXPECT_EQ(EMPTY_STRING, generator->interfaceCode(analyserModel));
    EXPECT_EQ(fileContents("generator/ode_constant_on_rhs/model.py"), generator->implementationCode(analyserModel));
}

TEST(Generator, odeConstantOnRhsOneComponent)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("generator/ode_constant_on_rhs_one_component/model.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    auto analyser = libcellml::Analyser::create();

    analyser->processModel(model);

    EXPECT_EQ(size_t(0), analyser->issueCount());

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

    EXPECT_EQ(fileContents("generator/ode_constant_on_rhs_one_component/model.h"), generator->interfaceCode(analyserModel));
    EXPECT_EQ(fileContents("generator/ode_constant_on_rhs_one_component/model.c"), generator->implementationCode(analyserModel));

    auto profile = libcellml::GeneratorProfile::create(libcellml::GeneratorProfile::Profile::PYTHON);

    generator->setProfile(profile);

    EXPECT_EQ(EMPTY_STRING, generator->interfaceCode(analyserModel));
    EXPECT_EQ(fileContents("generator/ode_constant_on_rhs_one_component/model.py"), generator->implementationCode(analyserModel));
}

TEST(Generator, odeMultipleDependentOdes)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("generator/ode_multiple_dependent_odes/model.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    auto analyser = libcellml::Analyser::create();

    analyser->processModel(model);

    EXPECT_EQ(size_t(0), analyser->issueCount());

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

    EXPECT_EQ(fileContents("generator/ode_multiple_dependent_odes/model.h"), generator->interfaceCode(analyserModel));
    EXPECT_EQ(fileContents("generator/ode_multiple_dependent_odes/model.c"), generator->implementationCode(analyserModel));

    auto profile = libcellml::GeneratorProfile::create(libcellml::GeneratorProfile::Profile::PYTHON);

    generator->setProfile(profile);

    EXPECT_EQ(EMPTY_STRING, generator->interfaceCode(analyserModel));
    EXPECT_EQ(fileContents("generator/ode_multiple_dependent_odes/model.py"), generator->implementationCode(analyserModel));
}

TEST(Generator, odeMultipleDependentOdesOneComponent)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("generator/ode_multiple_dependent_odes_one_component/model.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    auto analyser = libcellml::Analyser::create();

    analyser->processModel(model);

    EXPECT_EQ(size_t(0), analyser->issueCount());

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

    EXPECT_EQ(fileContents("generator/ode_multiple_dependent_odes_one_component/model.h"), generator->interfaceCode(analyserModel));
    EXPECT_EQ(fileContents("generator/ode_multiple_dependent_odes_one_component/model.c"), generator->implementationCode(analyserModel));

    auto profile = libcellml::GeneratorProfile::create(libcellml::GeneratorProfile::Profile::PYTHON);

    generator->setProfile(profile);

    EXPECT_EQ(EMPTY_STRING, generator->interfaceCode(analyserModel));
    EXPECT_EQ(fileContents("generator/ode_multiple_dependent_odes_one_component/model.py"), generator->implementationCode(analyserModel));
}

TEST(Generator, odeMultipleOdesWithSameName)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("generator/ode_multiple_odes_with_same_name/model.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    auto analyser = libcellml::Analyser::create();

    analyser->processModel(model);

    EXPECT_EQ(size_t(0), analyser->issueCount());

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

    EXPECT_EQ(fileContents("generator/ode_multiple_odes_with_same_name/model.h"), generator->interfaceCode(analyserModel));
    EXPECT_EQ(fileContents("generator/ode_multiple_odes_with_same_name/model.c"), generator->implementationCode(analyserModel));

    auto profile = libcellml::GeneratorProfile::create(libcellml::GeneratorProfile::Profile::PYTHON);

    generator->setProfile(profile);

    EXPECT_EQ(EMPTY_STRING, generator->interfaceCode(analyserModel));
    EXPECT_EQ(fileContents("generator/ode_multiple_odes_with_same_name/model.py"), generator->implementationCode(analyserModel));
}

TEST(Generator, cellmlMappingsAndEncapsulations)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("generator/cellml_mappings_and_encapsulations/model.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    auto analyser = libcellml::Analyser::create();

    analyser->processModel(model);

    EXPECT_EQ(size_t(0), analyser->issueCount());

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

    EXPECT_EQ(fileContents("generator/cellml_mappings_and_encapsulations/model.h"), generator->interfaceCode(analyserModel));
    EXPECT_EQ(fileContents("generator/cellml_mappings_and_encapsulations/model.c"), generator->implementationCode(analyserModel));

    auto profile = libcellml::GeneratorProfile::create(libcellml::GeneratorProfile::Profile::PYTHON);

    generator->setProfile(profile);

    EXPECT_EQ(EMPTY_STRING, generator->interfaceCode(analyserModel));
    EXPECT_EQ(fileContents("generator/cellml_mappings_and_encapsulations/model.py"), generator->implementationCode(analyserModel));
}

TEST(Generator, cellmlStateInitialisedUsingVariable)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("generator/cellml_state_initialised_using_variable/model.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    auto analyser = libcellml::Analyser::create();

    analyser->processModel(model);

    EXPECT_EQ(size_t(0), analyser->issueCount());

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

    EXPECT_EQ(fileContents("generator/cellml_state_initialised_using_variable/model.h"), generator->interfaceCode(analyserModel));
    EXPECT_EQ(fileContents("generator/cellml_state_initialised_using_variable/model.c"), generator->implementationCode(analyserModel));

    auto profile = libcellml::GeneratorProfile::create(libcellml::GeneratorProfile::Profile::PYTHON);

    generator->setProfile(profile);

    EXPECT_EQ(EMPTY_STRING, generator->interfaceCode(analyserModel));
    EXPECT_EQ(fileContents("generator/cellml_state_initialised_using_variable/model.py"), generator->implementationCode(analyserModel));
}

TEST(Generator, cellmlUnitScalingVoiIndirect)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("generator/cellml_unit_scaling_voi_indirect/model.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    auto analyser = libcellml::Analyser::create();

    analyser->processModel(model);

    EXPECT_EQ(size_t(0), analyser->issueCount());

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

    EXPECT_EQ(fileContents("generator/cellml_unit_scaling_voi_indirect/model.h"), generator->interfaceCode(analyserModel));
    EXPECT_EQ(fileContents("generator/cellml_unit_scaling_voi_indirect/model.c"), generator->implementationCode(analyserModel));

    auto profile = libcellml::GeneratorProfile::create(libcellml::GeneratorProfile::Profile::PYTHON);

    generator->setProfile(profile);

    EXPECT_EQ(EMPTY_STRING, generator->interfaceCode(analyserModel));
    EXPECT_EQ(fileContents("generator/cellml_unit_scaling_voi_indirect/model.py"), generator->implementationCode(analyserModel));
}

TEST(Generator, cellmlUnitScalingVoiDirect)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("generator/cellml_unit_scaling_voi_direct/model.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    auto analyser = libcellml::Analyser::create();

    analyser->processModel(model);

    EXPECT_EQ(size_t(0), analyser->issueCount());

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

    EXPECT_EQ(fileContents("generator/cellml_unit_scaling_voi_direct/model.h"), generator->interfaceCode(analyserModel));
    EXPECT_EQ(fileContents("generator/cellml_unit_scaling_voi_direct/model.c"), generator->implementationCode(analyserModel));

    auto profile = libcellml::GeneratorProfile::create(libcellml::GeneratorProfile::Profile::PYTHON);

    generator->setProfile(profile);

    EXPECT_EQ(EMPTY_STRING, generator->interfaceCode(analyserModel));
    EXPECT_EQ(fileContents("generator/cellml_unit_scaling_voi_direct/model.py"), generator->implementationCode(analyserModel));
}

TEST(Generator, cellmlUnitScalingConstant)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("generator/cellml_unit_scaling_constant/model.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    auto analyser = libcellml::Analyser::create();

    analyser->processModel(model);

    EXPECT_EQ(size_t(0), analyser->issueCount());

    auto analyserModel = analyser->model();

    EXPECT_EQ(libcellml::AnalyserModel::Type::ALGEBRAIC, analyserModel->type());

    EXPECT_EQ(size_t(0), analyserModel->stateCount());
    EXPECT_EQ(size_t(3), analyserModel->variableCount());
    EXPECT_EQ(size_t(2), analyserModel->equationCount());

    EXPECT_EQ(nullptr, analyserModel->voi());
    EXPECT_EQ(nullptr, analyserModel->state(0));
    EXPECT_EQ(nullptr, analyserModel->state(analyserModel->stateCount()));
    EXPECT_NE(nullptr, analyserModel->variable(0));
    EXPECT_EQ(nullptr, analyserModel->variable(analyserModel->variableCount()));
    EXPECT_NE(nullptr, analyserModel->equation(0));
    EXPECT_EQ(nullptr, analyserModel->equation(analyserModel->equationCount()));

    auto generator = libcellml::Generator::create();

    EXPECT_EQ(fileContents("generator/cellml_unit_scaling_constant/model.h"), generator->interfaceCode(analyserModel));
    EXPECT_EQ(fileContents("generator/cellml_unit_scaling_constant/model.c"), generator->implementationCode(analyserModel));

    auto profile = libcellml::GeneratorProfile::create(libcellml::GeneratorProfile::Profile::PYTHON);

    generator->setProfile(profile);

    EXPECT_EQ(EMPTY_STRING, generator->interfaceCode(analyserModel));
    EXPECT_EQ(fileContents("generator/cellml_unit_scaling_constant/model.py"), generator->implementationCode(analyserModel));
}

TEST(Generator, cellmlUnitScalingState)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("generator/cellml_unit_scaling_state/model.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    auto analyser = libcellml::Analyser::create();

    analyser->processModel(model);

    EXPECT_EQ(size_t(0), analyser->issueCount());

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

    EXPECT_EQ(fileContents("generator/cellml_unit_scaling_state/model.h"), generator->interfaceCode(analyserModel));
    EXPECT_EQ(fileContents("generator/cellml_unit_scaling_state/model.c"), generator->implementationCode(analyserModel));

    auto profile = libcellml::GeneratorProfile::create(libcellml::GeneratorProfile::Profile::PYTHON);

    generator->setProfile(profile);

    EXPECT_EQ(EMPTY_STRING, generator->interfaceCode(analyserModel));
    EXPECT_EQ(fileContents("generator/cellml_unit_scaling_state/model.py"), generator->implementationCode(analyserModel));
}

TEST(Generator, cellmlUnitScalingStateInitialisedUsingConstant)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("generator/cellml_unit_scaling_state_initialised_using_constant/model.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    auto analyser = libcellml::Analyser::create();

    analyser->processModel(model);

    EXPECT_EQ(size_t(0), analyser->issueCount());

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

    EXPECT_EQ(fileContents("generator/cellml_unit_scaling_state_initialised_using_constant/model.h"), generator->interfaceCode(analyserModel));
    EXPECT_EQ(fileContents("generator/cellml_unit_scaling_state_initialised_using_constant/model.c"), generator->implementationCode(analyserModel));

    auto profile = libcellml::GeneratorProfile::create(libcellml::GeneratorProfile::Profile::PYTHON);

    generator->setProfile(profile);

    EXPECT_EQ(EMPTY_STRING, generator->interfaceCode(analyserModel));
    EXPECT_EQ(fileContents("generator/cellml_unit_scaling_state_initialised_using_constant/model.py"), generator->implementationCode(analyserModel));
}

TEST(Generator, cellmlUnitScalingStateInitialisedUsingVariable)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("generator/cellml_unit_scaling_state_initialised_using_variable/model.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    auto analyser = libcellml::Analyser::create();

    analyser->processModel(model);

    EXPECT_EQ(size_t(0), analyser->issueCount());

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

    EXPECT_EQ(fileContents("generator/cellml_unit_scaling_state_initialised_using_variable/model.h"), generator->interfaceCode(analyserModel));
    EXPECT_EQ(fileContents("generator/cellml_unit_scaling_state_initialised_using_variable/model.c"), generator->implementationCode(analyserModel));

    auto profile = libcellml::GeneratorProfile::create(libcellml::GeneratorProfile::Profile::PYTHON);

    generator->setProfile(profile);

    EXPECT_EQ(EMPTY_STRING, generator->interfaceCode(analyserModel));
    EXPECT_EQ(fileContents("generator/cellml_unit_scaling_state_initialised_using_variable/model.py"), generator->implementationCode(analyserModel));
}

TEST(Generator, cellmlUnitScalingRate)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("generator/cellml_unit_scaling_rate/model.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    auto analyser = libcellml::Analyser::create();

    analyser->processModel(model);

    EXPECT_EQ(size_t(0), analyser->issueCount());

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

    EXPECT_EQ(fileContents("generator/cellml_unit_scaling_rate/model.h"), generator->interfaceCode(analyserModel));
    EXPECT_EQ(fileContents("generator/cellml_unit_scaling_rate/model.c"), generator->implementationCode(analyserModel));

    auto profile = libcellml::GeneratorProfile::create(libcellml::GeneratorProfile::Profile::PYTHON);

    generator->setProfile(profile);

    EXPECT_EQ(EMPTY_STRING, generator->interfaceCode(analyserModel));
    EXPECT_EQ(fileContents("generator/cellml_unit_scaling_rate/model.py"), generator->implementationCode(analyserModel));
}

TEST(Generator, dependentEqns)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("generator/dependent_eqns/model.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    auto analyser = libcellml::Analyser::create();

    analyser->processModel(model);

    EXPECT_EQ(size_t(0), analyser->issueCount());

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

    EXPECT_EQ(fileContents("generator/dependent_eqns/model.h"), generator->interfaceCode(analyserModel));
    EXPECT_EQ(fileContents("generator/dependent_eqns/model.c"), generator->implementationCode(analyserModel));

    auto profile = libcellml::GeneratorProfile::create(libcellml::GeneratorProfile::Profile::PYTHON);

    generator->setProfile(profile);

    EXPECT_EQ(EMPTY_STRING, generator->interfaceCode(analyserModel));
    EXPECT_EQ(fileContents("generator/dependent_eqns/model.py"), generator->implementationCode(analyserModel));
}

TEST(Generator, fabbriFantiniWildersSeveriHumanSanModel2017)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("generator/fabbri_fantini_wilders_severi_human_san_model_2017/model.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    auto analyser = libcellml::Analyser::create();

    analyser->processModel(model);

    EXPECT_EQ(size_t(0), analyser->issueCount());

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

    EXPECT_EQ(fileContents("generator/fabbri_fantini_wilders_severi_human_san_model_2017/model.h"), generator->interfaceCode(analyserModel));
    EXPECT_EQ(fileContents("generator/fabbri_fantini_wilders_severi_human_san_model_2017/model.c"), generator->implementationCode(analyserModel));

    auto profile = libcellml::GeneratorProfile::create(libcellml::GeneratorProfile::Profile::PYTHON);

    generator->setProfile(profile);

    EXPECT_EQ(EMPTY_STRING, generator->interfaceCode(analyserModel));
    EXPECT_EQ(fileContents("generator/fabbri_fantini_wilders_severi_human_san_model_2017/model.py"), generator->implementationCode(analyserModel));
}

TEST(Generator, garnyKohlHunterBoyettNobleRabbitSanModel2003)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("generator/garny_kohl_hunter_boyett_noble_rabbit_san_model_2003/model.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    auto analyser = libcellml::Analyser::create();

    analyser->processModel(model);

    EXPECT_EQ(size_t(0), analyser->issueCount());

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

    EXPECT_EQ(fileContents("generator/garny_kohl_hunter_boyett_noble_rabbit_san_model_2003/model.h"), generator->interfaceCode(analyserModel));
    EXPECT_EQ(fileContents("generator/garny_kohl_hunter_boyett_noble_rabbit_san_model_2003/model.c"), generator->implementationCode(analyserModel));

    auto profile = libcellml::GeneratorProfile::create(libcellml::GeneratorProfile::Profile::PYTHON);

    generator->setProfile(profile);

    EXPECT_EQ(EMPTY_STRING, generator->interfaceCode(analyserModel));
    EXPECT_EQ(fileContents("generator/garny_kohl_hunter_boyett_noble_rabbit_san_model_2003/model.py"), generator->implementationCode(analyserModel));
}

TEST(Generator, hodgkinHuxleySquidAxonModel1952)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("generator/hodgkin_huxley_squid_axon_model_1952/model.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    auto analyser = libcellml::Analyser::create();

    analyser->processModel(model);

    EXPECT_EQ(size_t(0), analyser->issueCount());

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

    EXPECT_EQ(fileContents("generator/hodgkin_huxley_squid_axon_model_1952/model.h"), generator->interfaceCode(analyserModel));
    EXPECT_EQ(fileContents("generator/hodgkin_huxley_squid_axon_model_1952/model.c"), generator->implementationCode(analyserModel));

    auto profile = libcellml::GeneratorProfile::create(libcellml::GeneratorProfile::Profile::PYTHON);

    generator->setProfile(profile);

    EXPECT_EQ(EMPTY_STRING, generator->interfaceCode(analyserModel));
    EXPECT_EQ(fileContents("generator/hodgkin_huxley_squid_axon_model_1952/model.py"), generator->implementationCode(analyserModel));
}
*/

TEST(Generator, hodgkinHuxleySquidAxonModel1952WithExternalVariables)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("generator/hodgkin_huxley_squid_axon_model_1952/model.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    auto analyser = libcellml::Analyser::create();
    std::vector<libcellml::VariablePtr> externalVariables;

    externalVariables.push_back(model->component("membrane")->variable("V"));
    externalVariables.push_back(model->component("sodium_channel")->variable("i_Na"));
    externalVariables.push_back(model->component("potassium_channel_n_gate")->variable("alpha_n"));

    analyser->processModel(model, externalVariables);

    EXPECT_EQ(size_t(0), analyser->issueCount());

    auto analyserModel = analyser->model();

    EXPECT_EQ(libcellml::AnalyserModel::Type::ODE, analyserModel->type());

    EXPECT_EQ(size_t(3), analyserModel->stateCount());
    EXPECT_EQ(size_t(19), analyserModel->variableCount());
    EXPECT_EQ(size_t(15), analyserModel->equationCount());

    EXPECT_NE(nullptr, analyserModel->voi());
    EXPECT_NE(nullptr, analyserModel->state(0));
    EXPECT_EQ(nullptr, analyserModel->state(analyserModel->stateCount()));
    EXPECT_NE(nullptr, analyserModel->variable(0));
    EXPECT_EQ(nullptr, analyserModel->variable(analyserModel->variableCount()));
    EXPECT_NE(nullptr, analyserModel->equation(0));
    EXPECT_EQ(nullptr, analyserModel->equation(analyserModel->equationCount()));

    auto generator = libcellml::Generator::create();

    EXPECT_EQ(fileContents("generator/hodgkin_huxley_squid_axon_model_1952/model.external.h"), generator->interfaceCode(analyserModel));
    EXPECT_EQ(fileContents("generator/hodgkin_huxley_squid_axon_model_1952/model.external.c"), generator->implementationCode(analyserModel));

    auto profile = libcellml::GeneratorProfile::create(libcellml::GeneratorProfile::Profile::PYTHON);

    generator->setProfile(profile);

    EXPECT_EQ(EMPTY_STRING, generator->interfaceCode(analyserModel));
    EXPECT_EQ(fileContents("generator/hodgkin_huxley_squid_axon_model_1952/model.external.py"), generator->implementationCode(analyserModel));
}

/*
TEST(Generator, nobleModel1962)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("generator/noble_model_1962/model.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    auto analyser = libcellml::Analyser::create();

    analyser->processModel(model);

    EXPECT_EQ(size_t(0), analyser->issueCount());

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

    EXPECT_EQ(fileContents("generator/noble_model_1962/model.h"), generator->interfaceCode(analyserModel));
    EXPECT_EQ(fileContents("generator/noble_model_1962/model.c"), generator->implementationCode(analyserModel));

    auto profile = libcellml::GeneratorProfile::create(libcellml::GeneratorProfile::Profile::PYTHON);

    generator->setProfile(profile);

    EXPECT_EQ(EMPTY_STRING, generator->interfaceCode(analyserModel));
    EXPECT_EQ(fileContents("generator/noble_model_1962/model.py"), generator->implementationCode(analyserModel));
}

TEST(Generator, sineImports)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("sine_approximations_import.xml"));

    EXPECT_EQ(size_t(0), parser->issueCount());
    EXPECT_TRUE(model->hasUnresolvedImports());

    model->resolveImports(resourcePath());

    EXPECT_FALSE(model->hasUnresolvedImports());

    model->flatten();

    auto analyser = libcellml::Analyser::create();

    analyser->processModel(model);

    EXPECT_EQ(size_t(0), analyser->issueCount());

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

    EXPECT_EQ(fileContents("generator/sine_model_imports/model.h"), generator->interfaceCode(analyserModel));
    EXPECT_EQ(fileContents("generator/sine_model_imports/model.c"), generator->implementationCode(analyserModel));

    auto profile = libcellml::GeneratorProfile::create(libcellml::GeneratorProfile::Profile::PYTHON);

    generator->setProfile(profile);

    EXPECT_EQ(EMPTY_STRING, generator->interfaceCode(analyserModel));
    EXPECT_EQ(fileContents("generator/sine_model_imports/model.py"), generator->implementationCode(analyserModel));
}

TEST(Generator, coverage)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("generator/coverage/model.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    auto analyser = libcellml::Analyser::create();

    analyser->processModel(model);

    EXPECT_EQ(size_t(0), analyser->issueCount());

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

    EXPECT_EQ(fileContents("generator/coverage/model.h"), generator->interfaceCode(analyserModel));
    EXPECT_EQ(fileContents("generator/coverage/model.c"), generator->implementationCode(analyserModel));

    auto profile = generator->profile();

    profile->setInterfaceCreateStatesArrayMethodString("double * createStatesVector();\n");
    profile->setImplementationCreateStatesArrayMethodString("double * createStatesVector()\n"
                                                            "{\n"
                                                            "    return (double *) malloc(STATE_COUNT*sizeof(double));\n"
                                                            "}\n");

    EXPECT_EQ(fileContents("generator/coverage/model.modified.profile.h"), generator->interfaceCode(analyserModel));
    EXPECT_EQ(fileContents("generator/coverage/model.modified.profile.c"), generator->implementationCode(analyserModel));

    profile = libcellml::GeneratorProfile::create();

    generator->setProfile(profile);

    profile->setHasInterface(false);

    profile->setXorString("^");
    profile->setHasXorOperator(true);

    profile->setPowerString("^^");
    profile->setSquareString("sqr");
    profile->setHasPowerOperator(true);

    profile->setPiecewiseIfString("piecewise(<CONDITION>, <IF_STATEMENT>");
    profile->setPiecewiseElseString(", <ELSE_STATEMENT>)");
    profile->setHasConditionalOperator(false);

    profile->setInterfaceFileNameString("customheaderfile.h");

    profile->setImplementationHeaderString("#include \"<INTERFACE_FILE_NAME>\"\n");

    profile->setImplementationVersionString("");

    profile->setImplementationLibcellmlVersionString("");

    profile->setImplementationStateCountString("");

    profile->setImplementationVariableCountString("");

    profile->setVariableTypeObjectString("");

    profile->setConstantVariableTypeString("");
    profile->setComputedConstantVariableTypeString("");
    profile->setAlgebraicVariableTypeString("");

    profile->setVariableInfoObjectString("");
    profile->setVariableInfoWithTypeObjectString("");

    profile->setImplementationVoiInfoString("");

    profile->setImplementationStateInfoString("");

    profile->setImplementationVariableInfoString("");

    profile->setVariableInfoEntryString("");
    profile->setVariableInfoWithTypeEntryString("");

    profile->setImplementationCreateStatesArrayMethodString("");

    profile->setImplementationCreateVariablesArrayMethodString("");

    profile->setImplementationDeleteArrayMethodString("");

    profile->setImplementationComputeVariablesMethodString("// We should have computeVariables() here, but we replaced it with this comment\n"
                                                           "// and no code template that can be replaced so that our replace() method can\n"
                                                           "// is forced to return an empty string, ensuring 100% coverage using llvm-cov...\n");

    EXPECT_EQ(EMPTY_STRING, generator->interfaceCode(analyserModel));
    EXPECT_EQ(fileContents("generator/coverage/model.out"), generator->implementationCode(analyserModel));

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

    profile->setVariableTypeObjectString("");

    profile->setConstantVariableTypeString("");
    profile->setComputedConstantVariableTypeString("");
    profile->setAlgebraicVariableTypeString("");

    profile->setVariableInfoObjectString("");
    profile->setVariableInfoWithTypeObjectString("");

    profile->setInterfaceVoiInfoString("");
    profile->setImplementationVoiInfoString("");

    profile->setInterfaceStateInfoString("");
    profile->setImplementationStateInfoString("");

    profile->setInterfaceVariableInfoString("");
    profile->setImplementationVariableInfoString("");

    profile->setVariableInfoEntryString("");
    profile->setVariableInfoWithTypeEntryString("");

    EXPECT_EQ(fileContents("generator/coverage/model.interface.out"), generator->interfaceCode(analyserModel));
    EXPECT_EQ(fileContents("generator/coverage/model.implementation.out"), generator->implementationCode(analyserModel));

    profile->setProfile(libcellml::GeneratorProfile::Profile::PYTHON);

    EXPECT_EQ(EMPTY_STRING, generator->interfaceCode(analyserModel));
    EXPECT_EQ(fileContents("generator/coverage/model.py"), generator->implementationCode(analyserModel));

    profile->setImplementationCreateStatesArrayMethodString("\n"
                                                            "def create_states_vector():\n"
                                                            "    return [nan]*STATE_COUNT\n");

    EXPECT_EQ(EMPTY_STRING, generator->interfaceCode(analyserModel));
    EXPECT_EQ(fileContents("generator/coverage/model.modified.profile.py"), generator->implementationCode(analyserModel));
}
*/

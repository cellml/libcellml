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

TEST(Generator, algebraicEqnComputedVarOnRhs)
{
    libcellml::ParserPtr parser = libcellml::Parser::create();
    libcellml::ModelPtr model = parser->parseModel(fileContents("generator/algebraic_eqn_computed_var_on_rhs/model.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    libcellml::GeneratorPtr generator = libcellml::Generator::create();

    generator->processModel(model);

    EXPECT_EQ(size_t(0), generator->issueCount());

    EXPECT_EQ(libcellml::Generator::ModelType::ALGEBRAIC, generator->modelType());

    EXPECT_EQ(size_t(0), generator->stateCount());
    EXPECT_EQ(size_t(2), generator->variableCount());

    EXPECT_EQ(nullptr, generator->voi());
    EXPECT_EQ(nullptr, generator->state(0));
    EXPECT_NE(nullptr, generator->variable(0));
    EXPECT_EQ(nullptr, generator->variable(generator->variableCount()));

    EXPECT_EQ(fileContents("generator/algebraic_eqn_computed_var_on_rhs/model.h"), generator->interfaceCode());
    EXPECT_EQ(fileContents("generator/algebraic_eqn_computed_var_on_rhs/model.c"), generator->implementationCode());

    libcellml::GeneratorProfilePtr profile = libcellml::GeneratorProfile::create(libcellml::GeneratorProfile::Profile::PYTHON);

    generator->setProfile(profile);

    EXPECT_EQ(EMPTY_STRING, generator->interfaceCode());
    EXPECT_EQ(fileContents("generator/algebraic_eqn_computed_var_on_rhs/model.py"), generator->implementationCode());
}

TEST(Generator, algebraicEqnConstVarOnRhs)
{
    libcellml::ParserPtr parser = libcellml::Parser::create();
    libcellml::ModelPtr model = parser->parseModel(fileContents("generator/algebraic_eqn_const_var_on_rhs/model.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    libcellml::GeneratorPtr generator = libcellml::Generator::create();

    generator->processModel(model);

    EXPECT_EQ(size_t(0), generator->issueCount());

    EXPECT_EQ(libcellml::Generator::ModelType::ALGEBRAIC, generator->modelType());

    EXPECT_EQ(size_t(0), generator->stateCount());
    EXPECT_EQ(size_t(2), generator->variableCount());

    EXPECT_EQ(nullptr, generator->voi());
    EXPECT_EQ(nullptr, generator->state(0));
    EXPECT_NE(nullptr, generator->variable(0));
    EXPECT_EQ(nullptr, generator->variable(generator->variableCount()));

    EXPECT_EQ(fileContents("generator/algebraic_eqn_const_var_on_rhs/model.h"), generator->interfaceCode());
    EXPECT_EQ(fileContents("generator/algebraic_eqn_const_var_on_rhs/model.c"), generator->implementationCode());

    libcellml::GeneratorProfilePtr profile = libcellml::GeneratorProfile::create(libcellml::GeneratorProfile::Profile::PYTHON);

    generator->setProfile(profile);

    EXPECT_EQ(EMPTY_STRING, generator->interfaceCode());
    EXPECT_EQ(fileContents("generator/algebraic_eqn_const_var_on_rhs/model.py"), generator->implementationCode());
}

TEST(Generator, algebraicEqnConstantOnRhs)
{
    libcellml::ParserPtr parser = libcellml::Parser::create();
    libcellml::ModelPtr model = parser->parseModel(fileContents("generator/algebraic_eqn_constant_on_rhs/model.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    libcellml::GeneratorPtr generator = libcellml::Generator::create();

    generator->processModel(model);

    EXPECT_EQ(size_t(0), generator->issueCount());

    EXPECT_EQ(libcellml::Generator::ModelType::ALGEBRAIC, generator->modelType());

    EXPECT_EQ(size_t(0), generator->stateCount());
    EXPECT_EQ(size_t(1), generator->variableCount());

    EXPECT_EQ(nullptr, generator->voi());
    EXPECT_EQ(nullptr, generator->state(0));
    EXPECT_NE(nullptr, generator->variable(0));
    EXPECT_EQ(nullptr, generator->variable(generator->variableCount()));

    EXPECT_EQ(fileContents("generator/algebraic_eqn_constant_on_rhs/model.h"), generator->interfaceCode());
    EXPECT_EQ(fileContents("generator/algebraic_eqn_constant_on_rhs/model.c"), generator->implementationCode());

    libcellml::GeneratorProfilePtr profile = libcellml::GeneratorProfile::create(libcellml::GeneratorProfile::Profile::PYTHON);

    generator->setProfile(profile);

    EXPECT_EQ(EMPTY_STRING, generator->interfaceCode());
    EXPECT_EQ(fileContents("generator/algebraic_eqn_constant_on_rhs/model.py"), generator->implementationCode());
}

TEST(Generator, algebraicEqnDerivativeOnRhs)
{
    libcellml::ParserPtr parser = libcellml::Parser::create();
    libcellml::ModelPtr model = parser->parseModel(fileContents("generator/algebraic_eqn_derivative_on_rhs/model.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    libcellml::GeneratorPtr generator = libcellml::Generator::create();

    generator->processModel(model);

    EXPECT_EQ(size_t(0), generator->issueCount());

    EXPECT_EQ(libcellml::Generator::ModelType::ODE, generator->modelType());

    EXPECT_EQ(size_t(1), generator->stateCount());
    EXPECT_EQ(size_t(2), generator->variableCount());

    EXPECT_NE(nullptr, generator->voi());
    EXPECT_NE(nullptr, generator->state(0));
    EXPECT_EQ(nullptr, generator->state(generator->stateCount()));
    EXPECT_NE(nullptr, generator->variable(0));
    EXPECT_EQ(nullptr, generator->variable(generator->variableCount()));

    EXPECT_EQ(fileContents("generator/algebraic_eqn_derivative_on_rhs/model.h"), generator->interfaceCode());
    EXPECT_EQ(fileContents("generator/algebraic_eqn_derivative_on_rhs/model.c"), generator->implementationCode());

    libcellml::GeneratorProfilePtr profile = libcellml::GeneratorProfile::create(libcellml::GeneratorProfile::Profile::PYTHON);

    generator->setProfile(profile);

    EXPECT_EQ(EMPTY_STRING, generator->interfaceCode());
    EXPECT_EQ(fileContents("generator/algebraic_eqn_derivative_on_rhs/model.py"), generator->implementationCode());
}

TEST(Generator, algebraicEqnDerivativeOnRhsOneComponent)
{
    libcellml::ParserPtr parser = libcellml::Parser::create();
    libcellml::ModelPtr model = parser->parseModel(fileContents("generator/algebraic_eqn_derivative_on_rhs_one_component/model.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    libcellml::GeneratorPtr generator = libcellml::Generator::create();

    generator->processModel(model);

    EXPECT_EQ(size_t(0), generator->issueCount());

    EXPECT_EQ(libcellml::Generator::ModelType::ODE, generator->modelType());

    EXPECT_EQ(size_t(1), generator->stateCount());
    EXPECT_EQ(size_t(2), generator->variableCount());

    EXPECT_NE(nullptr, generator->voi());
    EXPECT_NE(nullptr, generator->state(0));
    EXPECT_EQ(nullptr, generator->state(generator->stateCount()));
    EXPECT_NE(nullptr, generator->variable(0));
    EXPECT_EQ(nullptr, generator->variable(generator->variableCount()));

    EXPECT_EQ(fileContents("generator/algebraic_eqn_derivative_on_rhs_one_component/model.h"), generator->interfaceCode());
    EXPECT_EQ(fileContents("generator/algebraic_eqn_derivative_on_rhs_one_component/model.c"), generator->implementationCode());

    libcellml::GeneratorProfilePtr profile = libcellml::GeneratorProfile::create(libcellml::GeneratorProfile::Profile::PYTHON);

    generator->setProfile(profile);

    EXPECT_EQ(EMPTY_STRING, generator->interfaceCode());
    EXPECT_EQ(fileContents("generator/algebraic_eqn_derivative_on_rhs_one_component/model.py"), generator->implementationCode());
}

TEST(Generator, algebraicEqnStateVarOnRhs)
{
    libcellml::ParserPtr parser = libcellml::Parser::create();
    libcellml::ModelPtr model = parser->parseModel(fileContents("generator/algebraic_eqn_state_var_on_rhs/model.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    libcellml::GeneratorPtr generator = libcellml::Generator::create();

    generator->processModel(model);

    EXPECT_EQ(size_t(0), generator->issueCount());

    EXPECT_EQ(libcellml::Generator::ModelType::ODE, generator->modelType());

    EXPECT_EQ(size_t(1), generator->stateCount());
    EXPECT_EQ(size_t(2), generator->variableCount());

    EXPECT_NE(nullptr, generator->voi());
    EXPECT_NE(nullptr, generator->state(0));
    EXPECT_EQ(nullptr, generator->state(generator->stateCount()));
    EXPECT_NE(nullptr, generator->variable(0));
    EXPECT_EQ(nullptr, generator->variable(generator->variableCount()));

    EXPECT_EQ(fileContents("generator/algebraic_eqn_state_var_on_rhs/model.h"), generator->interfaceCode());
    EXPECT_EQ(fileContents("generator/algebraic_eqn_state_var_on_rhs/model.c"), generator->implementationCode());

    libcellml::GeneratorProfilePtr profile = libcellml::GeneratorProfile::create(libcellml::GeneratorProfile::Profile::PYTHON);

    generator->setProfile(profile);

    EXPECT_EQ(EMPTY_STRING, generator->interfaceCode());
    EXPECT_EQ(fileContents("generator/algebraic_eqn_state_var_on_rhs/model.py"), generator->implementationCode());
}

TEST(Generator, algebraicEqnStateVarOnRhsOneComponent)
{
    libcellml::ParserPtr parser = libcellml::Parser::create();
    libcellml::ModelPtr model = parser->parseModel(fileContents("generator/algebraic_eqn_state_var_on_rhs_one_component/model.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    libcellml::GeneratorPtr generator = libcellml::Generator::create();

    generator->processModel(model);

    EXPECT_EQ(size_t(0), generator->issueCount());

    EXPECT_EQ(libcellml::Generator::ModelType::ODE, generator->modelType());

    EXPECT_EQ(size_t(1), generator->stateCount());
    EXPECT_EQ(size_t(2), generator->variableCount());

    EXPECT_NE(nullptr, generator->voi());
    EXPECT_NE(nullptr, generator->state(0));
    EXPECT_EQ(nullptr, generator->state(generator->stateCount()));
    EXPECT_NE(nullptr, generator->variable(0));
    EXPECT_EQ(nullptr, generator->variable(generator->variableCount()));

    EXPECT_EQ(fileContents("generator/algebraic_eqn_state_var_on_rhs_one_component/model.h"), generator->interfaceCode());
    EXPECT_EQ(fileContents("generator/algebraic_eqn_state_var_on_rhs_one_component/model.c"), generator->implementationCode());

    libcellml::GeneratorProfilePtr profile = libcellml::GeneratorProfile::create(libcellml::GeneratorProfile::Profile::PYTHON);

    generator->setProfile(profile);

    EXPECT_EQ(EMPTY_STRING, generator->interfaceCode());
    EXPECT_EQ(fileContents("generator/algebraic_eqn_state_var_on_rhs_one_component/model.py"), generator->implementationCode());
}

TEST(Generator, odeComputedVarOnRhs)
{
    libcellml::ParserPtr parser = libcellml::Parser::create();
    libcellml::ModelPtr model = parser->parseModel(fileContents("generator/ode_computed_var_on_rhs/model.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    libcellml::GeneratorPtr generator = libcellml::Generator::create();

    generator->processModel(model);

    EXPECT_EQ(size_t(0), generator->issueCount());

    EXPECT_EQ(libcellml::Generator::ModelType::ODE, generator->modelType());

    EXPECT_EQ(size_t(1), generator->stateCount());
    EXPECT_EQ(size_t(1), generator->variableCount());

    EXPECT_NE(nullptr, generator->voi());
    EXPECT_NE(nullptr, generator->state(0));
    EXPECT_EQ(nullptr, generator->state(generator->stateCount()));
    EXPECT_NE(nullptr, generator->variable(0));
    EXPECT_EQ(nullptr, generator->variable(generator->variableCount()));

    EXPECT_EQ(fileContents("generator/ode_computed_var_on_rhs/model.h"), generator->interfaceCode());
    EXPECT_EQ(fileContents("generator/ode_computed_var_on_rhs/model.c"), generator->implementationCode());

    libcellml::GeneratorProfilePtr profile = libcellml::GeneratorProfile::create(libcellml::GeneratorProfile::Profile::PYTHON);

    generator->setProfile(profile);

    EXPECT_EQ(EMPTY_STRING, generator->interfaceCode());
    EXPECT_EQ(fileContents("generator/ode_computed_var_on_rhs/model.py"), generator->implementationCode());
}

TEST(Generator, odeComputedVarOnRhsOneComponent)
{
    libcellml::ParserPtr parser = libcellml::Parser::create();
    libcellml::ModelPtr model = parser->parseModel(fileContents("generator/ode_computed_var_on_rhs_one_component/model.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    libcellml::GeneratorPtr generator = libcellml::Generator::create();

    generator->processModel(model);

    EXPECT_EQ(size_t(0), generator->issueCount());

    EXPECT_EQ(libcellml::Generator::ModelType::ODE, generator->modelType());

    EXPECT_EQ(size_t(1), generator->stateCount());
    EXPECT_EQ(size_t(1), generator->variableCount());

    EXPECT_NE(nullptr, generator->voi());
    EXPECT_NE(nullptr, generator->state(0));
    EXPECT_EQ(nullptr, generator->state(generator->stateCount()));
    EXPECT_NE(nullptr, generator->variable(0));
    EXPECT_EQ(nullptr, generator->variable(generator->variableCount()));

    EXPECT_EQ(fileContents("generator/ode_computed_var_on_rhs_one_component/model.h"), generator->interfaceCode());
    EXPECT_EQ(fileContents("generator/ode_computed_var_on_rhs_one_component/model.c"), generator->implementationCode());

    libcellml::GeneratorProfilePtr profile = libcellml::GeneratorProfile::create(libcellml::GeneratorProfile::Profile::PYTHON);

    generator->setProfile(profile);

    EXPECT_EQ(EMPTY_STRING, generator->interfaceCode());
    EXPECT_EQ(fileContents("generator/ode_computed_var_on_rhs_one_component/model.py"), generator->implementationCode());
}

TEST(Generator, odeConstVarOnRhs)
{
    libcellml::ParserPtr parser = libcellml::Parser::create();
    libcellml::ModelPtr model = parser->parseModel(fileContents("generator/ode_const_var_on_rhs/model.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    libcellml::GeneratorPtr generator = libcellml::Generator::create();

    generator->processModel(model);

    EXPECT_EQ(size_t(0), generator->issueCount());

    EXPECT_EQ(libcellml::Generator::ModelType::ODE, generator->modelType());

    EXPECT_EQ(size_t(1), generator->stateCount());
    EXPECT_EQ(size_t(1), generator->variableCount());

    EXPECT_NE(nullptr, generator->voi());
    EXPECT_NE(nullptr, generator->state(0));
    EXPECT_EQ(nullptr, generator->state(generator->stateCount()));
    EXPECT_NE(nullptr, generator->variable(0));
    EXPECT_EQ(nullptr, generator->variable(generator->variableCount()));

    EXPECT_EQ(fileContents("generator/ode_const_var_on_rhs/model.h"), generator->interfaceCode());
    EXPECT_EQ(fileContents("generator/ode_const_var_on_rhs/model.c"), generator->implementationCode());

    libcellml::GeneratorProfilePtr profile = libcellml::GeneratorProfile::create(libcellml::GeneratorProfile::Profile::PYTHON);

    generator->setProfile(profile);

    EXPECT_EQ(EMPTY_STRING, generator->interfaceCode());
    EXPECT_EQ(fileContents("generator/ode_const_var_on_rhs/model.py"), generator->implementationCode());
}

TEST(Generator, odeConstVarOnRhsOneComponent)
{
    libcellml::ParserPtr parser = libcellml::Parser::create();
    libcellml::ModelPtr model = parser->parseModel(fileContents("generator/ode_const_var_on_rhs_one_component/model.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    libcellml::GeneratorPtr generator = libcellml::Generator::create();

    generator->processModel(model);

    EXPECT_EQ(size_t(0), generator->issueCount());

    EXPECT_EQ(libcellml::Generator::ModelType::ODE, generator->modelType());

    EXPECT_EQ(size_t(1), generator->stateCount());
    EXPECT_EQ(size_t(1), generator->variableCount());

    EXPECT_NE(nullptr, generator->voi());
    EXPECT_NE(nullptr, generator->state(0));
    EXPECT_EQ(nullptr, generator->state(generator->stateCount()));
    EXPECT_NE(nullptr, generator->variable(0));
    EXPECT_EQ(nullptr, generator->variable(generator->variableCount()));

    EXPECT_EQ(fileContents("generator/ode_const_var_on_rhs_one_component/model.h"), generator->interfaceCode());
    EXPECT_EQ(fileContents("generator/ode_const_var_on_rhs_one_component/model.c"), generator->implementationCode());

    libcellml::GeneratorProfilePtr profile = libcellml::GeneratorProfile::create(libcellml::GeneratorProfile::Profile::PYTHON);

    generator->setProfile(profile);

    EXPECT_EQ(EMPTY_STRING, generator->interfaceCode());
    EXPECT_EQ(fileContents("generator/ode_const_var_on_rhs_one_component/model.py"), generator->implementationCode());
}

TEST(Generator, odeConstantOnRhs)
{
    libcellml::ParserPtr parser = libcellml::Parser::create();
    libcellml::ModelPtr model = parser->parseModel(fileContents("generator/ode_constant_on_rhs/model.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    libcellml::GeneratorPtr generator = libcellml::Generator::create();

    generator->processModel(model);

    EXPECT_EQ(size_t(0), generator->issueCount());

    EXPECT_EQ(libcellml::Generator::ModelType::ODE, generator->modelType());

    EXPECT_EQ(size_t(1), generator->stateCount());
    EXPECT_EQ(size_t(0), generator->variableCount());

    EXPECT_NE(nullptr, generator->voi());
    EXPECT_NE(nullptr, generator->state(0));
    EXPECT_EQ(nullptr, generator->state(generator->stateCount()));
    EXPECT_EQ(nullptr, generator->variable(0));

    EXPECT_EQ(fileContents("generator/ode_constant_on_rhs/model.h"), generator->interfaceCode());
    EXPECT_EQ(fileContents("generator/ode_constant_on_rhs/model.c"), generator->implementationCode());

    libcellml::GeneratorProfilePtr profile = libcellml::GeneratorProfile::create(libcellml::GeneratorProfile::Profile::PYTHON);

    generator->setProfile(profile);

    EXPECT_EQ(EMPTY_STRING, generator->interfaceCode());
    EXPECT_EQ(fileContents("generator/ode_constant_on_rhs/model.py"), generator->implementationCode());
}

TEST(Generator, odeConstantOnRhsOneComponent)
{
    libcellml::ParserPtr parser = libcellml::Parser::create();
    libcellml::ModelPtr model = parser->parseModel(fileContents("generator/ode_constant_on_rhs_one_component/model.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    libcellml::GeneratorPtr generator = libcellml::Generator::create();

    generator->processModel(model);

    EXPECT_EQ(size_t(0), generator->issueCount());

    EXPECT_EQ(libcellml::Generator::ModelType::ODE, generator->modelType());

    EXPECT_EQ(size_t(1), generator->stateCount());
    EXPECT_EQ(size_t(0), generator->variableCount());

    EXPECT_NE(nullptr, generator->voi());
    EXPECT_NE(nullptr, generator->state(0));
    EXPECT_EQ(nullptr, generator->state(generator->stateCount()));
    EXPECT_EQ(nullptr, generator->variable(0));

    EXPECT_EQ(fileContents("generator/ode_constant_on_rhs_one_component/model.h"), generator->interfaceCode());
    EXPECT_EQ(fileContents("generator/ode_constant_on_rhs_one_component/model.c"), generator->implementationCode());

    libcellml::GeneratorProfilePtr profile = libcellml::GeneratorProfile::create(libcellml::GeneratorProfile::Profile::PYTHON);

    generator->setProfile(profile);

    EXPECT_EQ(EMPTY_STRING, generator->interfaceCode());
    EXPECT_EQ(fileContents("generator/ode_constant_on_rhs_one_component/model.py"), generator->implementationCode());
}

TEST(Generator, odeMultipleDependentOdes)
{
    libcellml::ParserPtr parser = libcellml::Parser::create();
    libcellml::ModelPtr model = parser->parseModel(fileContents("generator/ode_multiple_dependent_odes/model.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    libcellml::GeneratorPtr generator = libcellml::Generator::create();

    generator->processModel(model);

    EXPECT_EQ(size_t(0), generator->issueCount());

    EXPECT_EQ(libcellml::Generator::ModelType::ODE, generator->modelType());

    EXPECT_EQ(size_t(2), generator->stateCount());
    EXPECT_EQ(size_t(1), generator->variableCount());

    EXPECT_NE(nullptr, generator->voi());
    EXPECT_NE(nullptr, generator->state(0));
    EXPECT_EQ(nullptr, generator->state(generator->stateCount()));
    EXPECT_NE(nullptr, generator->variable(0));
    EXPECT_EQ(nullptr, generator->variable(generator->variableCount()));

    EXPECT_EQ(fileContents("generator/ode_multiple_dependent_odes/model.h"), generator->interfaceCode());
    EXPECT_EQ(fileContents("generator/ode_multiple_dependent_odes/model.c"), generator->implementationCode());

    libcellml::GeneratorProfilePtr profile = libcellml::GeneratorProfile::create(libcellml::GeneratorProfile::Profile::PYTHON);

    generator->setProfile(profile);

    EXPECT_EQ(EMPTY_STRING, generator->interfaceCode());
    EXPECT_EQ(fileContents("generator/ode_multiple_dependent_odes/model.py"), generator->implementationCode());
}

TEST(Generator, odeMultipleDependentOdesOneComponent)
{
    libcellml::ParserPtr parser = libcellml::Parser::create();
    libcellml::ModelPtr model = parser->parseModel(fileContents("generator/ode_multiple_dependent_odes_one_component/model.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    libcellml::GeneratorPtr generator = libcellml::Generator::create();

    generator->processModel(model);

    EXPECT_EQ(size_t(0), generator->issueCount());

    EXPECT_EQ(libcellml::Generator::ModelType::ODE, generator->modelType());

    EXPECT_EQ(size_t(2), generator->stateCount());
    EXPECT_EQ(size_t(1), generator->variableCount());

    EXPECT_NE(nullptr, generator->voi());
    EXPECT_NE(nullptr, generator->state(0));
    EXPECT_EQ(nullptr, generator->state(generator->stateCount()));
    EXPECT_NE(nullptr, generator->variable(0));
    EXPECT_EQ(nullptr, generator->variable(generator->variableCount()));

    EXPECT_EQ(fileContents("generator/ode_multiple_dependent_odes_one_component/model.h"), generator->interfaceCode());
    EXPECT_EQ(fileContents("generator/ode_multiple_dependent_odes_one_component/model.c"), generator->implementationCode());

    libcellml::GeneratorProfilePtr profile = libcellml::GeneratorProfile::create(libcellml::GeneratorProfile::Profile::PYTHON);

    generator->setProfile(profile);

    EXPECT_EQ(EMPTY_STRING, generator->interfaceCode());
    EXPECT_EQ(fileContents("generator/ode_multiple_dependent_odes_one_component/model.py"), generator->implementationCode());
}

TEST(Generator, odeMultipleOdesWithSameName)
{
    libcellml::ParserPtr parser = libcellml::Parser::create();
    libcellml::ModelPtr model = parser->parseModel(fileContents("generator/ode_multiple_odes_with_same_name/model.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    libcellml::GeneratorPtr generator = libcellml::Generator::create();

    generator->processModel(model);

    EXPECT_EQ(size_t(0), generator->issueCount());

    EXPECT_EQ(libcellml::Generator::ModelType::ODE, generator->modelType());

    EXPECT_EQ(size_t(2), generator->stateCount());
    EXPECT_EQ(size_t(1), generator->variableCount());

    EXPECT_NE(nullptr, generator->voi());
    EXPECT_NE(nullptr, generator->state(0));
    EXPECT_EQ(nullptr, generator->state(generator->stateCount()));
    EXPECT_NE(nullptr, generator->variable(0));
    EXPECT_EQ(nullptr, generator->variable(generator->variableCount()));

    EXPECT_EQ(fileContents("generator/ode_multiple_odes_with_same_name/model.h"), generator->interfaceCode());
    EXPECT_EQ(fileContents("generator/ode_multiple_odes_with_same_name/model.c"), generator->implementationCode());

    libcellml::GeneratorProfilePtr profile = libcellml::GeneratorProfile::create(libcellml::GeneratorProfile::Profile::PYTHON);

    generator->setProfile(profile);

    EXPECT_EQ(EMPTY_STRING, generator->interfaceCode());
    EXPECT_EQ(fileContents("generator/ode_multiple_odes_with_same_name/model.py"), generator->implementationCode());
}

TEST(Generator, cellmlMappingsAndEncapsulations)
{
    libcellml::ParserPtr parser = libcellml::Parser::create();
    libcellml::ModelPtr model = parser->parseModel(fileContents("generator/cellml_mappings_and_encapsulations/model.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    libcellml::GeneratorPtr generator = libcellml::Generator::create();

    generator->processModel(model);

    EXPECT_EQ(size_t(0), generator->issueCount());

    EXPECT_EQ(libcellml::Generator::ModelType::ODE, generator->modelType());

    EXPECT_EQ(size_t(2), generator->stateCount());
    EXPECT_EQ(size_t(2), generator->variableCount());

    EXPECT_NE(nullptr, generator->voi());
    EXPECT_NE(nullptr, generator->state(0));
    EXPECT_EQ(nullptr, generator->state(generator->stateCount()));
    EXPECT_NE(nullptr, generator->variable(0));
    EXPECT_EQ(nullptr, generator->variable(generator->variableCount()));

    EXPECT_EQ(fileContents("generator/cellml_mappings_and_encapsulations/model.h"), generator->interfaceCode());
    EXPECT_EQ(fileContents("generator/cellml_mappings_and_encapsulations/model.c"), generator->implementationCode());

    libcellml::GeneratorProfilePtr profile = libcellml::GeneratorProfile::create(libcellml::GeneratorProfile::Profile::PYTHON);

    generator->setProfile(profile);

    EXPECT_EQ(EMPTY_STRING, generator->interfaceCode());
    EXPECT_EQ(fileContents("generator/cellml_mappings_and_encapsulations/model.py"), generator->implementationCode());
}

TEST(Generator, cellmlStateInitialisedUsingVariable)
{
    libcellml::ParserPtr parser = libcellml::Parser::create();
    libcellml::ModelPtr model = parser->parseModel(fileContents("generator/cellml_state_initialised_using_variable/model.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    libcellml::GeneratorPtr generator = libcellml::Generator::create();

    generator->processModel(model);

    EXPECT_EQ(size_t(0), generator->issueCount());

    EXPECT_EQ(libcellml::Generator::ModelType::ODE, generator->modelType());

    EXPECT_EQ(size_t(1), generator->stateCount());
    EXPECT_EQ(size_t(1), generator->variableCount());

    EXPECT_NE(nullptr, generator->voi());
    EXPECT_NE(nullptr, generator->state(0));
    EXPECT_EQ(nullptr, generator->state(generator->stateCount()));
    EXPECT_NE(nullptr, generator->variable(0));
    EXPECT_EQ(nullptr, generator->variable(generator->variableCount()));

    EXPECT_EQ(fileContents("generator/cellml_state_initialised_using_variable/model.h"), generator->interfaceCode());
    EXPECT_EQ(fileContents("generator/cellml_state_initialised_using_variable/model.c"), generator->implementationCode());

    libcellml::GeneratorProfilePtr profile = libcellml::GeneratorProfile::create(libcellml::GeneratorProfile::Profile::PYTHON);

    generator->setProfile(profile);

    EXPECT_EQ(EMPTY_STRING, generator->interfaceCode());
    EXPECT_EQ(fileContents("generator/cellml_state_initialised_using_variable/model.py"), generator->implementationCode());
}

TEST(Generator, cellmlUnitScalingVoiIndirect)
{
    libcellml::ParserPtr parser = libcellml::Parser::create();
    libcellml::ModelPtr model = parser->parseModel(fileContents("generator/cellml_unit_scaling_voi_indirect/model.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    libcellml::GeneratorPtr generator = libcellml::Generator::create();

    generator->processModel(model);

    EXPECT_EQ(size_t(0), generator->issueCount());

    EXPECT_EQ(libcellml::Generator::ModelType::ODE, generator->modelType());

    EXPECT_EQ(size_t(2), generator->stateCount());
    EXPECT_EQ(size_t(0), generator->variableCount());

    EXPECT_NE(nullptr, generator->voi());
    EXPECT_NE(nullptr, generator->state(0));
    EXPECT_EQ(nullptr, generator->state(generator->stateCount()));
    EXPECT_EQ(nullptr, generator->variable(0));
    EXPECT_EQ(nullptr, generator->variable(generator->variableCount()));

    EXPECT_EQ(fileContents("generator/cellml_unit_scaling_voi_indirect/model.h"), generator->interfaceCode());
    EXPECT_EQ(fileContents("generator/cellml_unit_scaling_voi_indirect/model.c"), generator->implementationCode());

    libcellml::GeneratorProfilePtr profile = libcellml::GeneratorProfile::create(libcellml::GeneratorProfile::Profile::PYTHON);

    generator->setProfile(profile);

    EXPECT_EQ(EMPTY_STRING, generator->interfaceCode());
    EXPECT_EQ(fileContents("generator/cellml_unit_scaling_voi_indirect/model.py"), generator->implementationCode());
}

TEST(Generator, cellmlUnitScalingVoiDirect)
{
    libcellml::ParserPtr parser = libcellml::Parser::create();
    libcellml::ModelPtr model = parser->parseModel(fileContents("generator/cellml_unit_scaling_voi_direct/model.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    libcellml::GeneratorPtr generator = libcellml::Generator::create();

    generator->processModel(model);

    EXPECT_EQ(size_t(0), generator->issueCount());

    EXPECT_EQ(libcellml::Generator::ModelType::ODE, generator->modelType());

    EXPECT_EQ(size_t(2), generator->stateCount());
    EXPECT_EQ(size_t(0), generator->variableCount());

    EXPECT_NE(nullptr, generator->voi());
    EXPECT_NE(nullptr, generator->state(0));
    EXPECT_EQ(nullptr, generator->state(generator->stateCount()));
    EXPECT_EQ(nullptr, generator->variable(0));
    EXPECT_EQ(nullptr, generator->variable(generator->variableCount()));

    EXPECT_EQ(fileContents("generator/cellml_unit_scaling_voi_direct/model.h"), generator->interfaceCode());
    EXPECT_EQ(fileContents("generator/cellml_unit_scaling_voi_direct/model.c"), generator->implementationCode());

    libcellml::GeneratorProfilePtr profile = libcellml::GeneratorProfile::create(libcellml::GeneratorProfile::Profile::PYTHON);

    generator->setProfile(profile);

    EXPECT_EQ(EMPTY_STRING, generator->interfaceCode());
    EXPECT_EQ(fileContents("generator/cellml_unit_scaling_voi_direct/model.py"), generator->implementationCode());
}

TEST(Generator, cellmlUnitScalingConstant)
{
    libcellml::ParserPtr parser = libcellml::Parser::create();
    libcellml::ModelPtr model = parser->parseModel(fileContents("generator/cellml_unit_scaling_constant/model.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    libcellml::GeneratorPtr generator = libcellml::Generator::create();

    generator->processModel(model);

    EXPECT_EQ(size_t(0), generator->issueCount());

    EXPECT_EQ(libcellml::Generator::ModelType::ALGEBRAIC, generator->modelType());

    EXPECT_EQ(size_t(0), generator->stateCount());
    EXPECT_EQ(size_t(3), generator->variableCount());

    EXPECT_EQ(nullptr, generator->voi());
    EXPECT_EQ(nullptr, generator->state(0));
    EXPECT_EQ(nullptr, generator->state(generator->stateCount()));
    EXPECT_NE(nullptr, generator->variable(0));
    EXPECT_EQ(nullptr, generator->variable(generator->variableCount()));

    EXPECT_EQ(fileContents("generator/cellml_unit_scaling_constant/model.h"), generator->interfaceCode());
    EXPECT_EQ(fileContents("generator/cellml_unit_scaling_constant/model.c"), generator->implementationCode());

    libcellml::GeneratorProfilePtr profile = libcellml::GeneratorProfile::create(libcellml::GeneratorProfile::Profile::PYTHON);

    generator->setProfile(profile);

    EXPECT_EQ(EMPTY_STRING, generator->interfaceCode());
    EXPECT_EQ(fileContents("generator/cellml_unit_scaling_constant/model.py"), generator->implementationCode());
}

TEST(Generator, cellmlUnitScalingState)
{
    libcellml::ParserPtr parser = libcellml::Parser::create();
    libcellml::ModelPtr model = parser->parseModel(fileContents("generator/cellml_unit_scaling_state/model.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    libcellml::GeneratorPtr generator = libcellml::Generator::create();

    generator->processModel(model);

    EXPECT_EQ(size_t(0), generator->issueCount());

    EXPECT_EQ(libcellml::Generator::ModelType::ODE, generator->modelType());

    EXPECT_EQ(size_t(1), generator->stateCount());
    EXPECT_EQ(size_t(2), generator->variableCount());

    EXPECT_NE(nullptr, generator->voi());
    EXPECT_NE(nullptr, generator->state(0));
    EXPECT_EQ(nullptr, generator->state(generator->stateCount()));
    EXPECT_NE(nullptr, generator->variable(0));
    EXPECT_EQ(nullptr, generator->variable(generator->variableCount()));

    EXPECT_EQ(fileContents("generator/cellml_unit_scaling_state/model.h"), generator->interfaceCode());
    EXPECT_EQ(fileContents("generator/cellml_unit_scaling_state/model.c"), generator->implementationCode());

    libcellml::GeneratorProfilePtr profile = libcellml::GeneratorProfile::create(libcellml::GeneratorProfile::Profile::PYTHON);

    generator->setProfile(profile);

    EXPECT_EQ(EMPTY_STRING, generator->interfaceCode());
    EXPECT_EQ(fileContents("generator/cellml_unit_scaling_state/model.py"), generator->implementationCode());
}

TEST(Generator, cellmlUnitScalingStateInitialisedUsingConstant)
{
    libcellml::ParserPtr parser = libcellml::Parser::create();
    libcellml::ModelPtr model = parser->parseModel(fileContents("generator/cellml_unit_scaling_state_initialised_using_constant/model.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    libcellml::GeneratorPtr generator = libcellml::Generator::create();

    generator->processModel(model);

    EXPECT_EQ(size_t(0), generator->issueCount());

    EXPECT_EQ(libcellml::Generator::ModelType::ODE, generator->modelType());

    EXPECT_EQ(size_t(2), generator->stateCount());
    EXPECT_EQ(size_t(0), generator->variableCount());

    EXPECT_NE(nullptr, generator->voi());
    EXPECT_NE(nullptr, generator->state(0));
    EXPECT_EQ(nullptr, generator->state(generator->stateCount()));
    EXPECT_EQ(nullptr, generator->variable(0));
    EXPECT_EQ(nullptr, generator->variable(generator->variableCount()));

    EXPECT_EQ(fileContents("generator/cellml_unit_scaling_state_initialised_using_constant/model.h"), generator->interfaceCode());
    EXPECT_EQ(fileContents("generator/cellml_unit_scaling_state_initialised_using_constant/model.c"), generator->implementationCode());

    libcellml::GeneratorProfilePtr profile = libcellml::GeneratorProfile::create(libcellml::GeneratorProfile::Profile::PYTHON);

    generator->setProfile(profile);

    EXPECT_EQ(EMPTY_STRING, generator->interfaceCode());
    EXPECT_EQ(fileContents("generator/cellml_unit_scaling_state_initialised_using_constant/model.py"), generator->implementationCode());
}

TEST(Generator, cellmlUnitScalingStateInitialisedUsingVariable)
{
    libcellml::ParserPtr parser = libcellml::Parser::create();
    libcellml::ModelPtr model = parser->parseModel(fileContents("generator/cellml_unit_scaling_state_initialised_using_variable/model.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    libcellml::GeneratorPtr generator = libcellml::Generator::create();

    generator->processModel(model);

    EXPECT_EQ(size_t(0), generator->issueCount());

    EXPECT_EQ(libcellml::Generator::ModelType::ODE, generator->modelType());

    EXPECT_EQ(size_t(2), generator->stateCount());
    EXPECT_EQ(size_t(2), generator->variableCount());

    EXPECT_NE(nullptr, generator->voi());
    EXPECT_NE(nullptr, generator->state(0));
    EXPECT_EQ(nullptr, generator->state(generator->stateCount()));
    EXPECT_NE(nullptr, generator->variable(0));
    EXPECT_EQ(nullptr, generator->variable(generator->variableCount()));

    EXPECT_EQ(fileContents("generator/cellml_unit_scaling_state_initialised_using_variable/model.h"), generator->interfaceCode());
    EXPECT_EQ(fileContents("generator/cellml_unit_scaling_state_initialised_using_variable/model.c"), generator->implementationCode());

    libcellml::GeneratorProfilePtr profile = libcellml::GeneratorProfile::create(libcellml::GeneratorProfile::Profile::PYTHON);

    generator->setProfile(profile);

    EXPECT_EQ(EMPTY_STRING, generator->interfaceCode());
    EXPECT_EQ(fileContents("generator/cellml_unit_scaling_state_initialised_using_variable/model.py"), generator->implementationCode());
}

TEST(Generator, cellmlUnitScalingRate)
{
    libcellml::ParserPtr parser = libcellml::Parser::create();
    libcellml::ModelPtr model = parser->parseModel(fileContents("generator/cellml_unit_scaling_rate/model.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    libcellml::GeneratorPtr generator = libcellml::Generator::create();

    generator->processModel(model);

    EXPECT_EQ(size_t(0), generator->issueCount());

    EXPECT_EQ(libcellml::Generator::ModelType::ODE, generator->modelType());

    EXPECT_EQ(size_t(1), generator->stateCount());
    EXPECT_EQ(size_t(2), generator->variableCount());

    EXPECT_NE(nullptr, generator->voi());
    EXPECT_NE(nullptr, generator->state(0));
    EXPECT_EQ(nullptr, generator->state(generator->stateCount()));
    EXPECT_NE(nullptr, generator->variable(0));
    EXPECT_EQ(nullptr, generator->variable(generator->variableCount()));

    EXPECT_EQ(fileContents("generator/cellml_unit_scaling_rate/model.h"), generator->interfaceCode());
    EXPECT_EQ(fileContents("generator/cellml_unit_scaling_rate/model.c"), generator->implementationCode());

    libcellml::GeneratorProfilePtr profile = libcellml::GeneratorProfile::create(libcellml::GeneratorProfile::Profile::PYTHON);

    generator->setProfile(profile);

    EXPECT_EQ(EMPTY_STRING, generator->interfaceCode());
    EXPECT_EQ(fileContents("generator/cellml_unit_scaling_rate/model.py"), generator->implementationCode());
}

TEST(Generator, dependentEqns)
{
    libcellml::ParserPtr parser = libcellml::Parser::create();
    libcellml::ModelPtr model = parser->parseModel(fileContents("generator/dependent_eqns/model.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    libcellml::GeneratorPtr generator = libcellml::Generator::create();

    generator->processModel(model);

    EXPECT_EQ(size_t(0), generator->issueCount());

    EXPECT_EQ(libcellml::Generator::ModelType::ODE, generator->modelType());

    EXPECT_EQ(size_t(1), generator->stateCount());
    EXPECT_EQ(size_t(2), generator->variableCount());

    EXPECT_NE(nullptr, generator->voi());
    EXPECT_NE(nullptr, generator->state(0));
    EXPECT_EQ(nullptr, generator->state(generator->stateCount()));
    EXPECT_NE(nullptr, generator->variable(0));
    EXPECT_EQ(nullptr, generator->variable(generator->variableCount()));

    EXPECT_EQ(fileContents("generator/dependent_eqns/model.h"), generator->interfaceCode());
    EXPECT_EQ(fileContents("generator/dependent_eqns/model.c"), generator->implementationCode());

    libcellml::GeneratorProfilePtr profile = libcellml::GeneratorProfile::create(libcellml::GeneratorProfile::Profile::PYTHON);

    generator->setProfile(profile);

    EXPECT_EQ(EMPTY_STRING, generator->interfaceCode());
    EXPECT_EQ(fileContents("generator/dependent_eqns/model.py"), generator->implementationCode());
}

TEST(Generator, fabbriFantiniWildersSeveriHumanSanModel2017)
{
    libcellml::ParserPtr parser = libcellml::Parser::create();
    libcellml::ModelPtr model = parser->parseModel(fileContents("generator/fabbri_fantini_wilders_severi_human_san_model_2017/model.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    libcellml::GeneratorPtr generator = libcellml::Generator::create();

    generator->processModel(model);

    EXPECT_EQ(size_t(0), generator->issueCount());

    EXPECT_EQ(libcellml::Generator::ModelType::ODE, generator->modelType());

    EXPECT_EQ(size_t(33), generator->stateCount());
    EXPECT_EQ(size_t(217), generator->variableCount());

    EXPECT_NE(nullptr, generator->voi());
    EXPECT_NE(nullptr, generator->state(0));
    EXPECT_EQ(nullptr, generator->state(generator->stateCount()));
    EXPECT_NE(nullptr, generator->variable(0));
    EXPECT_EQ(nullptr, generator->variable(generator->variableCount()));

    EXPECT_EQ(fileContents("generator/fabbri_fantini_wilders_severi_human_san_model_2017/model.h"), generator->interfaceCode());
    EXPECT_EQ(fileContents("generator/fabbri_fantini_wilders_severi_human_san_model_2017/model.c"), generator->implementationCode());

    libcellml::GeneratorProfilePtr profile = libcellml::GeneratorProfile::create(libcellml::GeneratorProfile::Profile::PYTHON);

    generator->setProfile(profile);

    EXPECT_EQ(EMPTY_STRING, generator->interfaceCode());
    EXPECT_EQ(fileContents("generator/fabbri_fantini_wilders_severi_human_san_model_2017/model.py"), generator->implementationCode());
}

TEST(Generator, garnyKohlHunterBoyettNobleRabbitSanModel2003)
{
    libcellml::ParserPtr parser = libcellml::Parser::create();
    libcellml::ModelPtr model = parser->parseModel(fileContents("generator/garny_kohl_hunter_boyett_noble_rabbit_san_model_2003/model.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    libcellml::GeneratorPtr generator = libcellml::Generator::create();

    generator->processModel(model);

    EXPECT_EQ(size_t(0), generator->issueCount());

    EXPECT_EQ(libcellml::Generator::ModelType::ODE, generator->modelType());

    EXPECT_EQ(size_t(15), generator->stateCount());
    EXPECT_EQ(size_t(185), generator->variableCount());

    EXPECT_NE(nullptr, generator->voi());
    EXPECT_NE(nullptr, generator->state(0));
    EXPECT_EQ(nullptr, generator->state(generator->stateCount()));
    EXPECT_NE(nullptr, generator->variable(0));
    EXPECT_EQ(nullptr, generator->variable(generator->variableCount()));

    EXPECT_EQ(fileContents("generator/garny_kohl_hunter_boyett_noble_rabbit_san_model_2003/model.h"), generator->interfaceCode());
    EXPECT_EQ(fileContents("generator/garny_kohl_hunter_boyett_noble_rabbit_san_model_2003/model.c"), generator->implementationCode());

    libcellml::GeneratorProfilePtr profile = libcellml::GeneratorProfile::create(libcellml::GeneratorProfile::Profile::PYTHON);

    generator->setProfile(profile);

    EXPECT_EQ(EMPTY_STRING, generator->interfaceCode());
    EXPECT_EQ(fileContents("generator/garny_kohl_hunter_boyett_noble_rabbit_san_model_2003/model.py"), generator->implementationCode());
}

TEST(Generator, hodgkinHuxleySquidAxonModel1952)
{
    libcellml::ParserPtr parser = libcellml::Parser::create();
    libcellml::ModelPtr model = parser->parseModel(fileContents("generator/hodgkin_huxley_squid_axon_model_1952/model.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    libcellml::GeneratorPtr generator = libcellml::Generator::create();

    generator->processModel(model);

    EXPECT_EQ(size_t(0), generator->issueCount());

    EXPECT_EQ(libcellml::Generator::ModelType::ODE, generator->modelType());

    EXPECT_EQ(size_t(4), generator->stateCount());
    EXPECT_EQ(size_t(18), generator->variableCount());

    EXPECT_NE(nullptr, generator->voi());
    EXPECT_NE(nullptr, generator->state(0));
    EXPECT_EQ(nullptr, generator->state(generator->stateCount()));
    EXPECT_NE(nullptr, generator->variable(0));
    EXPECT_EQ(nullptr, generator->variable(generator->variableCount()));

    EXPECT_EQ(fileContents("generator/hodgkin_huxley_squid_axon_model_1952/model.h"), generator->interfaceCode());
    EXPECT_EQ(fileContents("generator/hodgkin_huxley_squid_axon_model_1952/model.c"), generator->implementationCode());

    libcellml::GeneratorProfilePtr profile = libcellml::GeneratorProfile::create(libcellml::GeneratorProfile::Profile::PYTHON);

    generator->setProfile(profile);

    EXPECT_EQ(EMPTY_STRING, generator->interfaceCode());
    EXPECT_EQ(fileContents("generator/hodgkin_huxley_squid_axon_model_1952/model.py"), generator->implementationCode());
}

TEST(Generator, nobleModel1962)
{
    libcellml::ParserPtr parser = libcellml::Parser::create();
    libcellml::ModelPtr model = parser->parseModel(fileContents("generator/noble_model_1962/model.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    libcellml::GeneratorPtr generator = libcellml::Generator::create();

    generator->processModel(model);

    EXPECT_EQ(size_t(0), generator->issueCount());

    EXPECT_EQ(libcellml::Generator::ModelType::ODE, generator->modelType());

    EXPECT_EQ(size_t(4), generator->stateCount());
    EXPECT_EQ(size_t(17), generator->variableCount());

    EXPECT_NE(nullptr, generator->voi());
    EXPECT_NE(nullptr, generator->state(0));
    EXPECT_EQ(nullptr, generator->state(generator->stateCount()));
    EXPECT_NE(nullptr, generator->variable(0));
    EXPECT_EQ(nullptr, generator->variable(generator->variableCount()));

    EXPECT_EQ(fileContents("generator/noble_model_1962/model.h"), generator->interfaceCode());
    EXPECT_EQ(fileContents("generator/noble_model_1962/model.c"), generator->implementationCode());

    libcellml::GeneratorProfilePtr profile = libcellml::GeneratorProfile::create(libcellml::GeneratorProfile::Profile::PYTHON);

    generator->setProfile(profile);

    EXPECT_EQ(EMPTY_STRING, generator->interfaceCode());
    EXPECT_EQ(fileContents("generator/noble_model_1962/model.py"), generator->implementationCode());
}

TEST(Generator, sineImports)
{
    libcellml::ParserPtr parser = libcellml::Parser::create();
    libcellml::ModelPtr model = parser->parseModel(fileContents("sine_approximations_import.xml"));

    EXPECT_EQ(size_t(0), parser->issueCount());
    EXPECT_TRUE(model->hasUnresolvedImports());

    model->resolveImports(resourcePath());

    EXPECT_FALSE(model->hasUnresolvedImports());

    model->flatten();

    libcellml::GeneratorPtr generator = libcellml::Generator::create();

    generator->processModel(model);

    EXPECT_EQ(size_t(0), generator->issueCount());

    EXPECT_EQ(libcellml::Generator::ModelType::ODE, generator->modelType());

    EXPECT_EQ(size_t(1), generator->stateCount());
    EXPECT_EQ(size_t(10), generator->variableCount());

    EXPECT_NE(nullptr, generator->voi());
    EXPECT_NE(nullptr, generator->state(0));
    EXPECT_EQ(nullptr, generator->state(generator->stateCount()));
    EXPECT_NE(nullptr, generator->variable(0));
    EXPECT_EQ(nullptr, generator->variable(generator->variableCount()));

    EXPECT_EQ(fileContents("generator/sine_model_imports/model.h"), generator->interfaceCode());
    EXPECT_EQ(fileContents("generator/sine_model_imports/model.c"), generator->implementationCode());

    libcellml::GeneratorProfilePtr profile = libcellml::GeneratorProfile::create(libcellml::GeneratorProfile::Profile::PYTHON);

    generator->setProfile(profile);

    EXPECT_EQ(EMPTY_STRING, generator->interfaceCode());
    EXPECT_EQ(fileContents("generator/sine_model_imports/model.py"), generator->implementationCode());
}

TEST(Generator, coverage)
{
    libcellml::ParserPtr parser = libcellml::Parser::create();
    libcellml::ModelPtr model = parser->parseModel(fileContents("generator/coverage/model.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    libcellml::GeneratorPtr generator = libcellml::Generator::create();

    generator->processModel(model);

    EXPECT_EQ(size_t(0), generator->issueCount());

    EXPECT_EQ(libcellml::Generator::ModelType::ODE, generator->modelType());

    EXPECT_EQ(size_t(1), generator->stateCount());
    EXPECT_EQ(size_t(186), generator->variableCount());

    EXPECT_NE(nullptr, generator->voi());
    EXPECT_NE(nullptr, generator->state(0));
    EXPECT_EQ(nullptr, generator->state(generator->stateCount()));
    EXPECT_NE(nullptr, generator->variable(0));
    EXPECT_EQ(nullptr, generator->variable(generator->variableCount()));

    EXPECT_EQ(nullptr, generator->voi()->initialisingVariable());

    for (size_t i = 0; i < generator->stateCount(); ++i) {
        EXPECT_NE(nullptr, generator->state(i)->initialisingVariable());
    }

    for (size_t i = 0; i < generator->variableCount(); ++i) {
        EXPECT_EQ(i < 7, generator->variable(i)->initialisingVariable() != nullptr);
    }

    EXPECT_EQ(fileContents("generator/coverage/model.h"), generator->interfaceCode());
    EXPECT_EQ(fileContents("generator/coverage/model.c"), generator->implementationCode());

    libcellml::GeneratorProfilePtr profile = generator->profile();

    profile->setInterfaceCreateStatesArrayMethodString("double * createStatesVector();\n");
    profile->setImplementationCreateStatesArrayMethodString("double * createStatesVector()\n"
                                                            "{\n"
                                                            "    return (double *) malloc(STATE_COUNT*sizeof(double));\n"
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

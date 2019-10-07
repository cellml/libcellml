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
    libcellml::ModelPtr model = std::make_shared<libcellml::Model>();
    libcellml::Generator generator;

    generator.processModel(model);

    EXPECT_EQ(size_t(0), generator.errorCount());

    EXPECT_EQ(libcellml::Generator::ModelType::UNKNOWN, generator.modelType());

    EXPECT_EQ(size_t(0), generator.stateCount());
    EXPECT_EQ(size_t(0), generator.variableCount());

    EXPECT_EQ(nullptr, generator.voi());
    EXPECT_EQ(nullptr, generator.state(0));
    EXPECT_EQ(nullptr, generator.variable(0));

    EXPECT_EQ(EMPTY_STRING, generator.interfaceCode());
    EXPECT_EQ(EMPTY_STRING, generator.implementationCode());
}

TEST(Generator, initializedVariableOfIntegration)
{
    libcellml::Parser parser;
    libcellml::ModelPtr model = parser.parseModel(fileContents("generator/initialized_variable_of_integration.cellml"));

    EXPECT_EQ(size_t(0), parser.errorCount());

    const std::vector<std::string> expectedErrors = {
        "Variable 'time' in component 'my_component' of model 'initialized_variable_of_integration' cannot be both a variable of integration and initialised."};

    libcellml::Generator generator;

    generator.processModel(model);

    EXPECT_EQ(expectedErrors.size(), generator.errorCount());

    for (size_t i = 0; i < generator.errorCount(); ++i) {
        EXPECT_EQ(expectedErrors.at(i), generator.error(i)->description());
        EXPECT_EQ(libcellml::Error::Kind::GENERATOR, generator.error(i)->kind());
    }

    EXPECT_EQ(libcellml::Generator::ModelType::INVALID, generator.modelType());

    EXPECT_EQ(size_t(0), generator.stateCount());
    EXPECT_EQ(size_t(0), generator.variableCount());

    EXPECT_EQ(nullptr, generator.voi());
    EXPECT_EQ(nullptr, generator.state(0));
    EXPECT_EQ(nullptr, generator.variable(0));

    EXPECT_EQ(EMPTY_STRING, generator.interfaceCode());
    EXPECT_EQ(EMPTY_STRING, generator.implementationCode());
}

TEST(Generator, twoVariablesOfIntegration)
{
    libcellml::Parser parser;
    libcellml::ModelPtr model = parser.parseModel(fileContents("generator/two_variables_of_integration.cellml"));

    EXPECT_EQ(size_t(0), parser.errorCount());

    const std::vector<std::string> expectedErrors = {
        "Variable 'time' in component 'main' of model 'two_variables_of_integration' and variable 'other_time' in component 'sub_sub_sub' of model 'two_variables_of_integration' cannot both be a variable of integration."};

    libcellml::Generator generator;

    generator.processModel(model);

    EXPECT_EQ(expectedErrors.size(), generator.errorCount());

    for (size_t i = 0; i < generator.errorCount(); ++i) {
        EXPECT_EQ(expectedErrors.at(i), generator.error(i)->description());
        EXPECT_EQ(libcellml::Error::Kind::GENERATOR, generator.error(i)->kind());
    }

    EXPECT_EQ(libcellml::Generator::ModelType::INVALID, generator.modelType());

    EXPECT_EQ(size_t(0), generator.stateCount());
    EXPECT_EQ(size_t(0), generator.variableCount());

    EXPECT_EQ(nullptr, generator.voi());
    EXPECT_EQ(nullptr, generator.state(0));
    EXPECT_EQ(nullptr, generator.variable(0));

    EXPECT_EQ(EMPTY_STRING, generator.interfaceCode());
    EXPECT_EQ(EMPTY_STRING, generator.implementationCode());
}

TEST(Generator, nonFirstOrderOdes)
{
    libcellml::Parser parser;
    libcellml::ModelPtr model = parser.parseModel(fileContents("generator/non_first_order_odes.cellml"));

    EXPECT_EQ(size_t(0), parser.errorCount());

    const std::vector<std::string> expectedErrors = {
        "The differential equation for variable 'x' in component 'main' of model 'non_first_order_odes' must be of the first order.",
        "The differential equation for variable 'y' in component 'sub' of model 'non_first_order_odes' must be of the first order.",
        "The differential equation for variable 'z' in component 'sub_sub' of model 'non_first_order_odes' must be of the first order."};

    libcellml::Generator generator;

    generator.processModel(model);

    EXPECT_EQ(expectedErrors.size(), generator.errorCount());

    for (size_t i = 0; i < generator.errorCount(); ++i) {
        EXPECT_EQ(expectedErrors.at(i), generator.error(i)->description());
        EXPECT_EQ(libcellml::Error::Kind::GENERATOR, generator.error(i)->kind());
    }

    EXPECT_EQ(libcellml::Generator::ModelType::INVALID, generator.modelType());

    EXPECT_EQ(size_t(0), generator.stateCount());
    EXPECT_EQ(size_t(0), generator.variableCount());

    EXPECT_EQ(nullptr, generator.voi());
    EXPECT_EQ(nullptr, generator.state(0));
    EXPECT_EQ(nullptr, generator.variable(0));

    EXPECT_EQ(EMPTY_STRING, generator.interfaceCode());
    EXPECT_EQ(EMPTY_STRING, generator.implementationCode());
}

TEST(Generator, undefinedVariables)
{
    libcellml::Parser parser;
    libcellml::ModelPtr model = parser.parseModel(fileContents("generator/undefined_variables.cellml"));

    EXPECT_EQ(size_t(0), parser.errorCount());

    const std::vector<std::string> expectedErrors = {
        "Variable 'a' in component 'my_component' of model 'undefined_variables' is referenced in an equation, but it is not defined anywhere.",
        "Variable 'b' in component 'my_component' of model 'undefined_variables' is referenced in an equation, but it is not defined anywhere."};

    libcellml::Generator generator;

    generator.processModel(model);

    EXPECT_EQ(expectedErrors.size(), generator.errorCount());

    for (size_t i = 0; i < generator.errorCount(); ++i) {
        EXPECT_EQ(expectedErrors.at(i), generator.error(i)->description());
    }

    EXPECT_EQ(libcellml::Generator::ModelType::INVALID, generator.modelType());

    EXPECT_EQ(size_t(0), generator.stateCount());
    EXPECT_EQ(size_t(0), generator.variableCount());

    EXPECT_EQ(nullptr, generator.voi());
    EXPECT_EQ(nullptr, generator.state(0));
    EXPECT_EQ(nullptr, generator.variable(0));

    EXPECT_EQ(EMPTY_STRING, generator.interfaceCode());
    EXPECT_EQ(EMPTY_STRING, generator.implementationCode());
}

TEST(Generator, variableInitializedTwice)
{
    libcellml::Parser parser;
    libcellml::ModelPtr model = parser.parseModel(fileContents("generator/variable_initialized_twice.cellml"));

    EXPECT_EQ(size_t(0), parser.errorCount());

    const std::vector<std::string> expectedErrors = {
        "Variable 'x' in component 'sub' of model 'variable_initialized_twice' and variable 'x' in component 'main' of model 'variable_initialized_twice' are equivalent and cannot therefore both be initialised."};

    libcellml::Generator generator;

    generator.processModel(model);

    EXPECT_EQ(expectedErrors.size(), generator.errorCount());

    for (size_t i = 0; i < generator.errorCount(); ++i) {
        EXPECT_EQ(expectedErrors.at(i), generator.error(i)->description());
    }

    EXPECT_EQ(libcellml::Generator::ModelType::INVALID, generator.modelType());

    EXPECT_EQ(size_t(0), generator.stateCount());
    EXPECT_EQ(size_t(0), generator.variableCount());

    EXPECT_EQ(nullptr, generator.voi());
    EXPECT_EQ(nullptr, generator.state(0));
    EXPECT_EQ(nullptr, generator.variable(0));

    EXPECT_EQ(EMPTY_STRING, generator.interfaceCode());
    EXPECT_EQ(EMPTY_STRING, generator.implementationCode());
}

TEST(Generator, nonInitializedState)
{
    libcellml::Parser parser;
    libcellml::ModelPtr model = parser.parseModel(fileContents("generator/non_initialized_state.cellml"));

    EXPECT_EQ(size_t(0), parser.errorCount());

    const std::vector<std::string> expectedErrors = {
        "Variable 'x' in component 'my_component' of model 'non_initialized_state' is used in an ODE, but it is not initialised."};

    libcellml::Generator generator;

    generator.processModel(model);

    EXPECT_EQ(expectedErrors.size(), generator.errorCount());

    for (size_t i = 0; i < generator.errorCount(); ++i) {
        EXPECT_EQ(expectedErrors.at(i), generator.error(i)->description());
    }

    EXPECT_EQ(libcellml::Generator::ModelType::UNDERCONSTRAINED, generator.modelType());

    EXPECT_EQ(size_t(0), generator.stateCount());
    EXPECT_EQ(size_t(0), generator.variableCount());

    EXPECT_EQ(nullptr, generator.voi());
    EXPECT_EQ(nullptr, generator.state(0));
    EXPECT_EQ(nullptr, generator.variable(0));

    EXPECT_EQ(EMPTY_STRING, generator.interfaceCode());
    EXPECT_EQ(EMPTY_STRING, generator.implementationCode());
}

TEST(Generator, underconstrained)
{
    libcellml::Parser parser;
    libcellml::ModelPtr model = parser.parseModel(fileContents("generator/underconstrained.cellml"));

    EXPECT_EQ(size_t(0), parser.errorCount());

    const std::vector<std::string> expectedErrors = {
        "Variable 'x' in component 'my_component' of model 'my_model' is not computed."};

    libcellml::Generator generator;

    generator.processModel(model);

    EXPECT_EQ(expectedErrors.size(), generator.errorCount());

    for (size_t i = 0; i < generator.errorCount(); ++i) {
        EXPECT_EQ(expectedErrors.at(i), generator.error(i)->description());
    }

    EXPECT_EQ(libcellml::Generator::ModelType::UNDERCONSTRAINED, generator.modelType());

    EXPECT_EQ(size_t(0), generator.stateCount());
    EXPECT_EQ(size_t(0), generator.variableCount());

    EXPECT_EQ(nullptr, generator.voi());
    EXPECT_EQ(nullptr, generator.state(0));
    EXPECT_EQ(nullptr, generator.variable(0));

    EXPECT_EQ(EMPTY_STRING, generator.interfaceCode());
    EXPECT_EQ(EMPTY_STRING, generator.implementationCode());
}

TEST(Generator, overconstrained)
{
    libcellml::Parser parser;
    libcellml::ModelPtr model = parser.parseModel(fileContents("generator/overconstrained.cellml"));

    EXPECT_EQ(size_t(0), parser.errorCount());

    const std::vector<std::string> expectedErrors = {
        "Variable 'x' in component 'my_component' of model 'my_model' is computed more than once."};

    libcellml::Generator generator;

    generator.processModel(model);

    EXPECT_EQ(expectedErrors.size(), generator.errorCount());

    for (size_t i = 0; i < generator.errorCount(); ++i) {
        EXPECT_EQ(expectedErrors.at(i), generator.error(i)->description());
    }

    EXPECT_EQ(libcellml::Generator::ModelType::OVERCONSTRAINED, generator.modelType());

    EXPECT_EQ(size_t(0), generator.stateCount());
    EXPECT_EQ(size_t(0), generator.variableCount());

    EXPECT_EQ(nullptr, generator.voi());
    EXPECT_EQ(nullptr, generator.state(0));
    EXPECT_EQ(nullptr, generator.variable(0));

    EXPECT_EQ(EMPTY_STRING, generator.interfaceCode());
    EXPECT_EQ(EMPTY_STRING, generator.implementationCode());
}

TEST(Generator, unsuitablyConstrained)
{
    libcellml::Parser parser;
    libcellml::ModelPtr model = parser.parseModel(fileContents("generator/unsuitably_constrained.cellml"));

    EXPECT_EQ(size_t(0), parser.errorCount());

    const std::vector<std::string> expectedErrors = {
        "Variable 'x' in component 'my_component' of model 'my_model' is not computed.",
        "Variable 'y' in component 'my_component' of model 'my_model' is computed more than once."};

    libcellml::Generator generator;

    generator.processModel(model);

    EXPECT_EQ(expectedErrors.size(), generator.errorCount());

    for (size_t i = 0; i < generator.errorCount(); ++i) {
        EXPECT_EQ(expectedErrors.at(i), generator.error(i)->description());
    }

    EXPECT_EQ(libcellml::Generator::ModelType::UNSUITABLY_CONSTRAINED, generator.modelType());

    EXPECT_EQ(size_t(0), generator.stateCount());
    EXPECT_EQ(size_t(0), generator.variableCount());

    EXPECT_EQ(nullptr, generator.voi());
    EXPECT_EQ(nullptr, generator.state(0));
    EXPECT_EQ(nullptr, generator.variable(0));

    EXPECT_EQ(EMPTY_STRING, generator.interfaceCode());
    EXPECT_EQ(EMPTY_STRING, generator.implementationCode());
}

TEST(Generator, algebraicEqnComputedVarOnRhs)
{
    libcellml::Parser parser;
    libcellml::ModelPtr model = parser.parseModel(fileContents("generator/algebraic_eqn_computed_var_on_rhs/model.cellml"));

    EXPECT_EQ(size_t(0), parser.errorCount());

    libcellml::Generator generator;

    generator.processModel(model);

    EXPECT_EQ(size_t(0), generator.errorCount());

    EXPECT_EQ(libcellml::Generator::ModelType::ALGEBRAIC, generator.modelType());

    EXPECT_EQ(size_t(0), generator.stateCount());
    EXPECT_EQ(size_t(2), generator.variableCount());

    EXPECT_EQ(nullptr, generator.voi());
    EXPECT_EQ(nullptr, generator.state(0));
    EXPECT_NE(nullptr, generator.variable(0));
    EXPECT_EQ(nullptr, generator.variable(generator.variableCount()));

    EXPECT_EQ(fileContents("generator/algebraic_eqn_computed_var_on_rhs/model.h"), generator.interfaceCode());
    EXPECT_EQ(fileContents("generator/algebraic_eqn_computed_var_on_rhs/model.c"), generator.implementationCode());

    libcellml::GeneratorProfilePtr profile = std::make_shared<libcellml::GeneratorProfile>(libcellml::GeneratorProfile::Profile::PYTHON);

    generator.setProfile(profile);

    EXPECT_EQ(EMPTY_STRING, generator.interfaceCode());
    EXPECT_EQ(fileContents("generator/algebraic_eqn_computed_var_on_rhs/model.py"), generator.implementationCode());
}

TEST(Generator, algebraicEqnConstVarOnRhs)
{
    libcellml::Parser parser;
    libcellml::ModelPtr model = parser.parseModel(fileContents("generator/algebraic_eqn_const_var_on_rhs/model.cellml"));

    EXPECT_EQ(size_t(0), parser.errorCount());

    libcellml::Generator generator;

    generator.processModel(model);

    EXPECT_EQ(size_t(0), generator.errorCount());

    EXPECT_EQ(libcellml::Generator::ModelType::ALGEBRAIC, generator.modelType());

    EXPECT_EQ(size_t(0), generator.stateCount());
    EXPECT_EQ(size_t(2), generator.variableCount());

    EXPECT_EQ(nullptr, generator.voi());
    EXPECT_EQ(nullptr, generator.state(0));
    EXPECT_NE(nullptr, generator.variable(0));
    EXPECT_EQ(nullptr, generator.variable(generator.variableCount()));

    EXPECT_EQ(fileContents("generator/algebraic_eqn_const_var_on_rhs/model.h"), generator.interfaceCode());
    EXPECT_EQ(fileContents("generator/algebraic_eqn_const_var_on_rhs/model.c"), generator.implementationCode());

    libcellml::GeneratorProfilePtr profile = std::make_shared<libcellml::GeneratorProfile>(libcellml::GeneratorProfile::Profile::PYTHON);

    generator.setProfile(profile);

    EXPECT_EQ(EMPTY_STRING, generator.interfaceCode());
    EXPECT_EQ(fileContents("generator/algebraic_eqn_const_var_on_rhs/model.py"), generator.implementationCode());
}

TEST(Generator, algebraicEqnConstantOnRhs)
{
    libcellml::Parser parser;
    libcellml::ModelPtr model = parser.parseModel(fileContents("generator/algebraic_eqn_constant_on_rhs/model.cellml"));

    EXPECT_EQ(size_t(0), parser.errorCount());

    libcellml::Generator generator;

    generator.processModel(model);

    EXPECT_EQ(size_t(0), generator.errorCount());

    EXPECT_EQ(libcellml::Generator::ModelType::ALGEBRAIC, generator.modelType());

    EXPECT_EQ(size_t(0), generator.stateCount());
    EXPECT_EQ(size_t(1), generator.variableCount());

    EXPECT_EQ(nullptr, generator.voi());
    EXPECT_EQ(nullptr, generator.state(0));
    EXPECT_NE(nullptr, generator.variable(0));
    EXPECT_EQ(nullptr, generator.variable(generator.variableCount()));

    EXPECT_EQ(fileContents("generator/algebraic_eqn_constant_on_rhs/model.h"), generator.interfaceCode());
    EXPECT_EQ(fileContents("generator/algebraic_eqn_constant_on_rhs/model.c"), generator.implementationCode());

    libcellml::GeneratorProfilePtr profile = std::make_shared<libcellml::GeneratorProfile>(libcellml::GeneratorProfile::Profile::PYTHON);

    generator.setProfile(profile);

    EXPECT_EQ(EMPTY_STRING, generator.interfaceCode());
    EXPECT_EQ(fileContents("generator/algebraic_eqn_constant_on_rhs/model.py"), generator.implementationCode());
}

TEST(Generator, algebraicEqnDerivativeOnRhs)
{
    libcellml::Parser parser;
    libcellml::ModelPtr model = parser.parseModel(fileContents("generator/algebraic_eqn_derivative_on_rhs/model.cellml"));

    EXPECT_EQ(size_t(0), parser.errorCount());

    libcellml::Generator generator;

    generator.processModel(model);

    EXPECT_EQ(size_t(0), generator.errorCount());

    EXPECT_EQ(libcellml::Generator::ModelType::ODE, generator.modelType());

    EXPECT_EQ(size_t(1), generator.stateCount());
    EXPECT_EQ(size_t(2), generator.variableCount());

    EXPECT_NE(nullptr, generator.voi());
    EXPECT_NE(nullptr, generator.state(0));
    EXPECT_EQ(nullptr, generator.state(generator.stateCount()));
    EXPECT_NE(nullptr, generator.variable(0));
    EXPECT_EQ(nullptr, generator.variable(generator.variableCount()));

    EXPECT_EQ(fileContents("generator/algebraic_eqn_derivative_on_rhs/model.h"), generator.interfaceCode());
    EXPECT_EQ(fileContents("generator/algebraic_eqn_derivative_on_rhs/model.c"), generator.implementationCode());

    libcellml::GeneratorProfilePtr profile = std::make_shared<libcellml::GeneratorProfile>(libcellml::GeneratorProfile::Profile::PYTHON);

    generator.setProfile(profile);

    EXPECT_EQ(EMPTY_STRING, generator.interfaceCode());
    EXPECT_EQ(fileContents("generator/algebraic_eqn_derivative_on_rhs/model.py"), generator.implementationCode());
}

TEST(Generator, algebraicEqnDerivativeOnRhsOneComponent)
{
    libcellml::Parser parser;
    libcellml::ModelPtr model = parser.parseModel(fileContents("generator/algebraic_eqn_derivative_on_rhs_one_component/model.cellml"));

    EXPECT_EQ(size_t(0), parser.errorCount());

    libcellml::Generator generator;

    generator.processModel(model);

    EXPECT_EQ(size_t(0), generator.errorCount());

    EXPECT_EQ(libcellml::Generator::ModelType::ODE, generator.modelType());

    EXPECT_EQ(size_t(1), generator.stateCount());
    EXPECT_EQ(size_t(2), generator.variableCount());

    EXPECT_NE(nullptr, generator.voi());
    EXPECT_NE(nullptr, generator.state(0));
    EXPECT_EQ(nullptr, generator.state(generator.stateCount()));
    EXPECT_NE(nullptr, generator.variable(0));
    EXPECT_EQ(nullptr, generator.variable(generator.variableCount()));

    EXPECT_EQ(fileContents("generator/algebraic_eqn_derivative_on_rhs_one_component/model.h"), generator.interfaceCode());
    EXPECT_EQ(fileContents("generator/algebraic_eqn_derivative_on_rhs_one_component/model.c"), generator.implementationCode());

    libcellml::GeneratorProfilePtr profile = std::make_shared<libcellml::GeneratorProfile>(libcellml::GeneratorProfile::Profile::PYTHON);

    generator.setProfile(profile);

    EXPECT_EQ(EMPTY_STRING, generator.interfaceCode());
    EXPECT_EQ(fileContents("generator/algebraic_eqn_derivative_on_rhs_one_component/model.py"), generator.implementationCode());
}

TEST(Generator, algebraicEqnStateVarOnRhs)
{
    libcellml::Parser parser;
    libcellml::ModelPtr model = parser.parseModel(fileContents("generator/algebraic_eqn_state_var_on_rhs/model.cellml"));

    EXPECT_EQ(size_t(0), parser.errorCount());

    libcellml::Generator generator;

    generator.processModel(model);

    EXPECT_EQ(size_t(0), generator.errorCount());

    EXPECT_EQ(libcellml::Generator::ModelType::ODE, generator.modelType());

    EXPECT_EQ(size_t(1), generator.stateCount());
    EXPECT_EQ(size_t(2), generator.variableCount());

    EXPECT_NE(nullptr, generator.voi());
    EXPECT_NE(nullptr, generator.state(0));
    EXPECT_EQ(nullptr, generator.state(generator.stateCount()));
    EXPECT_NE(nullptr, generator.variable(0));
    EXPECT_EQ(nullptr, generator.variable(generator.variableCount()));

    EXPECT_EQ(fileContents("generator/algebraic_eqn_state_var_on_rhs/model.h"), generator.interfaceCode());
    EXPECT_EQ(fileContents("generator/algebraic_eqn_state_var_on_rhs/model.c"), generator.implementationCode());

    libcellml::GeneratorProfilePtr profile = std::make_shared<libcellml::GeneratorProfile>(libcellml::GeneratorProfile::Profile::PYTHON);

    generator.setProfile(profile);

    EXPECT_EQ(EMPTY_STRING, generator.interfaceCode());
    EXPECT_EQ(fileContents("generator/algebraic_eqn_state_var_on_rhs/model.py"), generator.implementationCode());
}

TEST(Generator, algebraicEqnStateVarOnRhsOneComponent)
{
    libcellml::Parser parser;
    libcellml::ModelPtr model = parser.parseModel(fileContents("generator/algebraic_eqn_state_var_on_rhs_one_component/model.cellml"));

    EXPECT_EQ(size_t(0), parser.errorCount());

    libcellml::Generator generator;

    generator.processModel(model);

    EXPECT_EQ(size_t(0), generator.errorCount());

    EXPECT_EQ(libcellml::Generator::ModelType::ODE, generator.modelType());

    EXPECT_EQ(size_t(1), generator.stateCount());
    EXPECT_EQ(size_t(2), generator.variableCount());

    EXPECT_NE(nullptr, generator.voi());
    EXPECT_NE(nullptr, generator.state(0));
    EXPECT_EQ(nullptr, generator.state(generator.stateCount()));
    EXPECT_NE(nullptr, generator.variable(0));
    EXPECT_EQ(nullptr, generator.variable(generator.variableCount()));

    EXPECT_EQ(fileContents("generator/algebraic_eqn_state_var_on_rhs_one_component/model.h"), generator.interfaceCode());
    EXPECT_EQ(fileContents("generator/algebraic_eqn_state_var_on_rhs_one_component/model.c"), generator.implementationCode());

    libcellml::GeneratorProfilePtr profile = std::make_shared<libcellml::GeneratorProfile>(libcellml::GeneratorProfile::Profile::PYTHON);

    generator.setProfile(profile);

    EXPECT_EQ(EMPTY_STRING, generator.interfaceCode());
    EXPECT_EQ(fileContents("generator/algebraic_eqn_state_var_on_rhs_one_component/model.py"), generator.implementationCode());
}

TEST(Generator, odeComputedVarOnRhs)
{
    libcellml::Parser parser;
    libcellml::ModelPtr model = parser.parseModel(fileContents("generator/ode_computed_var_on_rhs/model.cellml"));

    EXPECT_EQ(size_t(0), parser.errorCount());

    libcellml::Generator generator;

    generator.processModel(model);

    EXPECT_EQ(size_t(0), generator.errorCount());

    EXPECT_EQ(libcellml::Generator::ModelType::ODE, generator.modelType());

    EXPECT_EQ(size_t(1), generator.stateCount());
    EXPECT_EQ(size_t(1), generator.variableCount());

    EXPECT_NE(nullptr, generator.voi());
    EXPECT_NE(nullptr, generator.state(0));
    EXPECT_EQ(nullptr, generator.state(generator.stateCount()));
    EXPECT_NE(nullptr, generator.variable(0));
    EXPECT_EQ(nullptr, generator.variable(generator.variableCount()));

    EXPECT_EQ(fileContents("generator/ode_computed_var_on_rhs/model.h"), generator.interfaceCode());
    EXPECT_EQ(fileContents("generator/ode_computed_var_on_rhs/model.c"), generator.implementationCode());

    libcellml::GeneratorProfilePtr profile = std::make_shared<libcellml::GeneratorProfile>(libcellml::GeneratorProfile::Profile::PYTHON);

    generator.setProfile(profile);

    EXPECT_EQ(EMPTY_STRING, generator.interfaceCode());
    EXPECT_EQ(fileContents("generator/ode_computed_var_on_rhs/model.py"), generator.implementationCode());
}

TEST(Generator, odeComputedVarOnRhsOneComponent)
{
    libcellml::Parser parser;
    libcellml::ModelPtr model = parser.parseModel(fileContents("generator/ode_computed_var_on_rhs_one_component/model.cellml"));

    EXPECT_EQ(size_t(0), parser.errorCount());

    libcellml::Generator generator;

    generator.processModel(model);

    EXPECT_EQ(size_t(0), generator.errorCount());

    EXPECT_EQ(libcellml::Generator::ModelType::ODE, generator.modelType());

    EXPECT_EQ(size_t(1), generator.stateCount());
    EXPECT_EQ(size_t(1), generator.variableCount());

    EXPECT_NE(nullptr, generator.voi());
    EXPECT_NE(nullptr, generator.state(0));
    EXPECT_EQ(nullptr, generator.state(generator.stateCount()));
    EXPECT_NE(nullptr, generator.variable(0));
    EXPECT_EQ(nullptr, generator.variable(generator.variableCount()));

    EXPECT_EQ(fileContents("generator/ode_computed_var_on_rhs_one_component/model.h"), generator.interfaceCode());
    EXPECT_EQ(fileContents("generator/ode_computed_var_on_rhs_one_component/model.c"), generator.implementationCode());

    libcellml::GeneratorProfilePtr profile = std::make_shared<libcellml::GeneratorProfile>(libcellml::GeneratorProfile::Profile::PYTHON);

    generator.setProfile(profile);

    EXPECT_EQ(EMPTY_STRING, generator.interfaceCode());
    EXPECT_EQ(fileContents("generator/ode_computed_var_on_rhs_one_component/model.py"), generator.implementationCode());
}

TEST(Generator, odeConstVarOnRhs)
{
    libcellml::Parser parser;
    libcellml::ModelPtr model = parser.parseModel(fileContents("generator/ode_const_var_on_rhs/model.cellml"));

    EXPECT_EQ(size_t(0), parser.errorCount());

    libcellml::Generator generator;

    generator.processModel(model);

    EXPECT_EQ(size_t(0), generator.errorCount());

    EXPECT_EQ(libcellml::Generator::ModelType::ODE, generator.modelType());

    EXPECT_EQ(size_t(1), generator.stateCount());
    EXPECT_EQ(size_t(1), generator.variableCount());

    EXPECT_NE(nullptr, generator.voi());
    EXPECT_NE(nullptr, generator.state(0));
    EXPECT_EQ(nullptr, generator.state(generator.stateCount()));
    EXPECT_NE(nullptr, generator.variable(0));
    EXPECT_EQ(nullptr, generator.variable(generator.variableCount()));

    EXPECT_EQ(fileContents("generator/ode_const_var_on_rhs/model.h"), generator.interfaceCode());
    EXPECT_EQ(fileContents("generator/ode_const_var_on_rhs/model.c"), generator.implementationCode());

    libcellml::GeneratorProfilePtr profile = std::make_shared<libcellml::GeneratorProfile>(libcellml::GeneratorProfile::Profile::PYTHON);

    generator.setProfile(profile);

    EXPECT_EQ(EMPTY_STRING, generator.interfaceCode());
    EXPECT_EQ(fileContents("generator/ode_const_var_on_rhs/model.py"), generator.implementationCode());
}

TEST(Generator, odeConstVarOnRhsOneComponent)
{
    libcellml::Parser parser;
    libcellml::ModelPtr model = parser.parseModel(fileContents("generator/ode_const_var_on_rhs_one_component/model.cellml"));

    EXPECT_EQ(size_t(0), parser.errorCount());

    libcellml::Generator generator;

    generator.processModel(model);

    EXPECT_EQ(size_t(0), generator.errorCount());

    EXPECT_EQ(libcellml::Generator::ModelType::ODE, generator.modelType());

    EXPECT_EQ(size_t(1), generator.stateCount());
    EXPECT_EQ(size_t(1), generator.variableCount());

    EXPECT_NE(nullptr, generator.voi());
    EXPECT_NE(nullptr, generator.state(0));
    EXPECT_EQ(nullptr, generator.state(generator.stateCount()));
    EXPECT_NE(nullptr, generator.variable(0));
    EXPECT_EQ(nullptr, generator.variable(generator.variableCount()));

    EXPECT_EQ(fileContents("generator/ode_const_var_on_rhs_one_component/model.h"), generator.interfaceCode());
    EXPECT_EQ(fileContents("generator/ode_const_var_on_rhs_one_component/model.c"), generator.implementationCode());

    libcellml::GeneratorProfilePtr profile = std::make_shared<libcellml::GeneratorProfile>(libcellml::GeneratorProfile::Profile::PYTHON);

    generator.setProfile(profile);

    EXPECT_EQ(EMPTY_STRING, generator.interfaceCode());
    EXPECT_EQ(fileContents("generator/ode_const_var_on_rhs_one_component/model.py"), generator.implementationCode());
}

TEST(Generator, odeConstantOnRhs)
{
    libcellml::Parser parser;
    libcellml::ModelPtr model = parser.parseModel(fileContents("generator/ode_constant_on_rhs/model.cellml"));

    EXPECT_EQ(size_t(0), parser.errorCount());

    libcellml::Generator generator;

    generator.processModel(model);

    EXPECT_EQ(size_t(0), generator.errorCount());

    EXPECT_EQ(libcellml::Generator::ModelType::ODE, generator.modelType());

    EXPECT_EQ(size_t(1), generator.stateCount());
    EXPECT_EQ(size_t(0), generator.variableCount());

    EXPECT_NE(nullptr, generator.voi());
    EXPECT_NE(nullptr, generator.state(0));
    EXPECT_EQ(nullptr, generator.state(generator.stateCount()));
    EXPECT_EQ(nullptr, generator.variable(0));

    EXPECT_EQ(fileContents("generator/ode_constant_on_rhs/model.h"), generator.interfaceCode());
    EXPECT_EQ(fileContents("generator/ode_constant_on_rhs/model.c"), generator.implementationCode());

    libcellml::GeneratorProfilePtr profile = std::make_shared<libcellml::GeneratorProfile>(libcellml::GeneratorProfile::Profile::PYTHON);

    generator.setProfile(profile);

    EXPECT_EQ(EMPTY_STRING, generator.interfaceCode());
    EXPECT_EQ(fileContents("generator/ode_constant_on_rhs/model.py"), generator.implementationCode());
}

TEST(Generator, odeConstantOnRhsOneComponent)
{
    libcellml::Parser parser;
    libcellml::ModelPtr model = parser.parseModel(fileContents("generator/ode_constant_on_rhs_one_component/model.cellml"));

    EXPECT_EQ(size_t(0), parser.errorCount());

    libcellml::Generator generator;

    generator.processModel(model);

    EXPECT_EQ(size_t(0), generator.errorCount());

    EXPECT_EQ(libcellml::Generator::ModelType::ODE, generator.modelType());

    EXPECT_EQ(size_t(1), generator.stateCount());
    EXPECT_EQ(size_t(0), generator.variableCount());

    EXPECT_NE(nullptr, generator.voi());
    EXPECT_NE(nullptr, generator.state(0));
    EXPECT_EQ(nullptr, generator.state(generator.stateCount()));
    EXPECT_EQ(nullptr, generator.variable(0));

    EXPECT_EQ(fileContents("generator/ode_constant_on_rhs_one_component/model.h"), generator.interfaceCode());
    EXPECT_EQ(fileContents("generator/ode_constant_on_rhs_one_component/model.c"), generator.implementationCode());

    libcellml::GeneratorProfilePtr profile = std::make_shared<libcellml::GeneratorProfile>(libcellml::GeneratorProfile::Profile::PYTHON);

    generator.setProfile(profile);

    EXPECT_EQ(EMPTY_STRING, generator.interfaceCode());
    EXPECT_EQ(fileContents("generator/ode_constant_on_rhs_one_component/model.py"), generator.implementationCode());
}

TEST(Generator, odeMultipleDependentOdes)
{
    libcellml::Parser parser;
    libcellml::ModelPtr model = parser.parseModel(fileContents("generator/ode_multiple_dependent_odes/model.cellml"));

    EXPECT_EQ(size_t(0), parser.errorCount());

    libcellml::Generator generator;

    generator.processModel(model);

    EXPECT_EQ(size_t(0), generator.errorCount());

    EXPECT_EQ(libcellml::Generator::ModelType::ODE, generator.modelType());

    EXPECT_EQ(size_t(2), generator.stateCount());
    EXPECT_EQ(size_t(1), generator.variableCount());

    EXPECT_NE(nullptr, generator.voi());
    EXPECT_NE(nullptr, generator.state(0));
    EXPECT_EQ(nullptr, generator.state(generator.stateCount()));
    EXPECT_NE(nullptr, generator.variable(0));
    EXPECT_EQ(nullptr, generator.variable(generator.variableCount()));

    EXPECT_EQ(fileContents("generator/ode_multiple_dependent_odes/model.h"), generator.interfaceCode());
    EXPECT_EQ(fileContents("generator/ode_multiple_dependent_odes/model.c"), generator.implementationCode());

    libcellml::GeneratorProfilePtr profile = std::make_shared<libcellml::GeneratorProfile>(libcellml::GeneratorProfile::Profile::PYTHON);

    generator.setProfile(profile);

    EXPECT_EQ(EMPTY_STRING, generator.interfaceCode());
    EXPECT_EQ(fileContents("generator/ode_multiple_dependent_odes/model.py"), generator.implementationCode());
}

TEST(Generator, odeMultipleDependentOdesOneComponent)
{
    libcellml::Parser parser;
    libcellml::ModelPtr model = parser.parseModel(fileContents("generator/ode_multiple_dependent_odes_one_component/model.cellml"));

    EXPECT_EQ(size_t(0), parser.errorCount());

    libcellml::Generator generator;

    generator.processModel(model);

    EXPECT_EQ(size_t(0), generator.errorCount());

    EXPECT_EQ(libcellml::Generator::ModelType::ODE, generator.modelType());

    EXPECT_EQ(size_t(2), generator.stateCount());
    EXPECT_EQ(size_t(1), generator.variableCount());

    EXPECT_NE(nullptr, generator.voi());
    EXPECT_NE(nullptr, generator.state(0));
    EXPECT_EQ(nullptr, generator.state(generator.stateCount()));
    EXPECT_NE(nullptr, generator.variable(0));
    EXPECT_EQ(nullptr, generator.variable(generator.variableCount()));

    EXPECT_EQ(fileContents("generator/ode_multiple_dependent_odes_one_component/model.h"), generator.interfaceCode());
    EXPECT_EQ(fileContents("generator/ode_multiple_dependent_odes_one_component/model.c"), generator.implementationCode());

    libcellml::GeneratorProfilePtr profile = std::make_shared<libcellml::GeneratorProfile>(libcellml::GeneratorProfile::Profile::PYTHON);

    generator.setProfile(profile);

    EXPECT_EQ(EMPTY_STRING, generator.interfaceCode());
    EXPECT_EQ(fileContents("generator/ode_multiple_dependent_odes_one_component/model.py"), generator.implementationCode());
}

TEST(Generator, odeMultipleOdesWithSameName)
{
    libcellml::Parser parser;
    libcellml::ModelPtr model = parser.parseModel(fileContents("generator/ode_multiple_odes_with_same_name/model.cellml"));

    EXPECT_EQ(size_t(0), parser.errorCount());

    libcellml::Generator generator;

    generator.processModel(model);

    EXPECT_EQ(size_t(0), generator.errorCount());

    EXPECT_EQ(libcellml::Generator::ModelType::ODE, generator.modelType());

    EXPECT_EQ(size_t(2), generator.stateCount());
    EXPECT_EQ(size_t(1), generator.variableCount());

    EXPECT_NE(nullptr, generator.voi());
    EXPECT_NE(nullptr, generator.state(0));
    EXPECT_EQ(nullptr, generator.state(generator.stateCount()));
    EXPECT_NE(nullptr, generator.variable(0));
    EXPECT_EQ(nullptr, generator.variable(generator.variableCount()));

    EXPECT_EQ(fileContents("generator/ode_multiple_odes_with_same_name/model.h"), generator.interfaceCode());
    EXPECT_EQ(fileContents("generator/ode_multiple_odes_with_same_name/model.c"), generator.implementationCode());

    libcellml::GeneratorProfilePtr profile = std::make_shared<libcellml::GeneratorProfile>(libcellml::GeneratorProfile::Profile::PYTHON);

    generator.setProfile(profile);

    EXPECT_EQ(EMPTY_STRING, generator.interfaceCode());
    EXPECT_EQ(fileContents("generator/ode_multiple_odes_with_same_name/model.py"), generator.implementationCode());
}

TEST(Generator, cellmlMappingsAndEncapsulations)
{
    libcellml::Parser parser;
    libcellml::ModelPtr model = parser.parseModel(fileContents("generator/cellml_mappings_and_encapsulations/model.cellml"));

    //TODO: currently, the parser wrongly reports an error with our model, hence
    //      we "expect" one parsing error. Clearly, no parsing error should be
    //      reported once issue #377 has been addressed.
    EXPECT_EQ(size_t(1), parser.errorCount());

    libcellml::Generator generator;

    generator.processModel(model);

    EXPECT_EQ(size_t(0), generator.errorCount());

    EXPECT_EQ(libcellml::Generator::ModelType::ODE, generator.modelType());

    EXPECT_EQ(size_t(2), generator.stateCount());
    EXPECT_EQ(size_t(2), generator.variableCount());

    EXPECT_NE(nullptr, generator.voi());
    EXPECT_NE(nullptr, generator.state(0));
    EXPECT_EQ(nullptr, generator.state(generator.stateCount()));
    EXPECT_NE(nullptr, generator.variable(0));
    EXPECT_EQ(nullptr, generator.variable(generator.variableCount()));

    EXPECT_EQ(fileContents("generator/cellml_mappings_and_encapsulations/model.h"), generator.interfaceCode());
    EXPECT_EQ(fileContents("generator/cellml_mappings_and_encapsulations/model.c"), generator.implementationCode());

    libcellml::GeneratorProfilePtr profile = std::make_shared<libcellml::GeneratorProfile>(libcellml::GeneratorProfile::Profile::PYTHON);

    generator.setProfile(profile);

    EXPECT_EQ(EMPTY_STRING, generator.interfaceCode());
    EXPECT_EQ(fileContents("generator/cellml_mappings_and_encapsulations/model.py"), generator.implementationCode());
}

TEST(Generator, dependentEqns)
{
    libcellml::Parser parser;
    libcellml::ModelPtr model = parser.parseModel(fileContents("generator/dependent_eqns/model.cellml"));

    EXPECT_EQ(size_t(0), parser.errorCount());

    libcellml::Generator generator;

    generator.processModel(model);

    EXPECT_EQ(size_t(0), generator.errorCount());

    EXPECT_EQ(libcellml::Generator::ModelType::ODE, generator.modelType());

    EXPECT_EQ(size_t(1), generator.stateCount());
    EXPECT_EQ(size_t(2), generator.variableCount());

    EXPECT_NE(nullptr, generator.voi());
    EXPECT_NE(nullptr, generator.state(0));
    EXPECT_EQ(nullptr, generator.state(generator.stateCount()));
    EXPECT_NE(nullptr, generator.variable(0));
    EXPECT_EQ(nullptr, generator.variable(generator.variableCount()));

    EXPECT_EQ(fileContents("generator/dependent_eqns/model.h"), generator.interfaceCode());
    EXPECT_EQ(fileContents("generator/dependent_eqns/model.c"), generator.implementationCode());

    libcellml::GeneratorProfilePtr profile = std::make_shared<libcellml::GeneratorProfile>(libcellml::GeneratorProfile::Profile::PYTHON);

    generator.setProfile(profile);

    EXPECT_EQ(EMPTY_STRING, generator.interfaceCode());
    EXPECT_EQ(fileContents("generator/dependent_eqns/model.py"), generator.implementationCode());
}

TEST(Generator, fabbriFantiniWildersSeveriHumanSanModel2017)
{
    libcellml::Parser parser;
    libcellml::ModelPtr model = parser.parseModel(fileContents("generator/fabbri_fantini_wilders_severi_human_san_model_2017/model.cellml"));

    EXPECT_EQ(size_t(0), parser.errorCount());

    libcellml::Generator generator;

    generator.processModel(model);

    EXPECT_EQ(size_t(0), generator.errorCount());

    EXPECT_EQ(libcellml::Generator::ModelType::ODE, generator.modelType());

    EXPECT_EQ(size_t(33), generator.stateCount());
    EXPECT_EQ(size_t(217), generator.variableCount());

    EXPECT_NE(nullptr, generator.voi());
    EXPECT_NE(nullptr, generator.state(0));
    EXPECT_EQ(nullptr, generator.state(generator.stateCount()));
    EXPECT_NE(nullptr, generator.variable(0));
    EXPECT_EQ(nullptr, generator.variable(generator.variableCount()));

    EXPECT_EQ(fileContents("generator/fabbri_fantini_wilders_severi_human_san_model_2017/model.h"), generator.interfaceCode());
    EXPECT_EQ(fileContents("generator/fabbri_fantini_wilders_severi_human_san_model_2017/model.c"), generator.implementationCode());

    libcellml::GeneratorProfilePtr profile = std::make_shared<libcellml::GeneratorProfile>(libcellml::GeneratorProfile::Profile::PYTHON);

    generator.setProfile(profile);

    EXPECT_EQ(EMPTY_STRING, generator.interfaceCode());
    EXPECT_EQ(fileContents("generator/fabbri_fantini_wilders_severi_human_san_model_2017/model.py"), generator.implementationCode());
}

TEST(Generator, garnyKohlHunterBoyettNobleRabbitSanModel2003)
{
    libcellml::Parser parser;
    libcellml::ModelPtr model = parser.parseModel(fileContents("generator/garny_kohl_hunter_boyett_noble_rabbit_san_model_2003/model.cellml"));

    EXPECT_EQ(size_t(0), parser.errorCount());

    libcellml::Generator generator;

    generator.processModel(model);

    EXPECT_EQ(size_t(0), generator.errorCount());

    EXPECT_EQ(libcellml::Generator::ModelType::ODE, generator.modelType());

    EXPECT_EQ(size_t(15), generator.stateCount());
    EXPECT_EQ(size_t(185), generator.variableCount());

    EXPECT_NE(nullptr, generator.voi());
    EXPECT_NE(nullptr, generator.state(0));
    EXPECT_EQ(nullptr, generator.state(generator.stateCount()));
    EXPECT_NE(nullptr, generator.variable(0));
    EXPECT_EQ(nullptr, generator.variable(generator.variableCount()));

    EXPECT_EQ(fileContents("generator/garny_kohl_hunter_boyett_noble_rabbit_san_model_2003/model.h"), generator.interfaceCode());
    EXPECT_EQ(fileContents("generator/garny_kohl_hunter_boyett_noble_rabbit_san_model_2003/model.c"), generator.implementationCode());

    libcellml::GeneratorProfilePtr profile = std::make_shared<libcellml::GeneratorProfile>(libcellml::GeneratorProfile::Profile::PYTHON);

    generator.setProfile(profile);

    EXPECT_EQ(EMPTY_STRING, generator.interfaceCode());
    EXPECT_EQ(fileContents("generator/garny_kohl_hunter_boyett_noble_rabbit_san_model_2003/model.py"), generator.implementationCode());
}

TEST(Generator, hodgkinHuxleySquidAxonModel1952)
{
    libcellml::Parser parser;
    libcellml::ModelPtr model = parser.parseModel(fileContents("generator/hodgkin_huxley_squid_axon_model_1952/model.cellml"));

    EXPECT_EQ(size_t(0), parser.errorCount());

    libcellml::Generator generator;

    generator.processModel(model);

    EXPECT_EQ(size_t(0), generator.errorCount());

    EXPECT_EQ(libcellml::Generator::ModelType::ODE, generator.modelType());

    EXPECT_EQ(size_t(4), generator.stateCount());
    EXPECT_EQ(size_t(18), generator.variableCount());

    EXPECT_NE(nullptr, generator.voi());
    EXPECT_NE(nullptr, generator.state(0));
    EXPECT_EQ(nullptr, generator.state(generator.stateCount()));
    EXPECT_NE(nullptr, generator.variable(0));
    EXPECT_EQ(nullptr, generator.variable(generator.variableCount()));

    const std::vector<libcellml::GeneratorVariable::Type> expectedTypes = {
        libcellml::GeneratorVariable::Type::CONSTANT,
        libcellml::GeneratorVariable::Type::CONSTANT,
        libcellml::GeneratorVariable::Type::CONSTANT,
        libcellml::GeneratorVariable::Type::CONSTANT,
        libcellml::GeneratorVariable::Type::CONSTANT,
        libcellml::GeneratorVariable::Type::COMPUTED_CONSTANT,
        libcellml::GeneratorVariable::Type::COMPUTED_CONSTANT,
        libcellml::GeneratorVariable::Type::COMPUTED_CONSTANT,
        libcellml::GeneratorVariable::Type::ALGEBRAIC,
        libcellml::GeneratorVariable::Type::ALGEBRAIC,
        libcellml::GeneratorVariable::Type::ALGEBRAIC,
        libcellml::GeneratorVariable::Type::ALGEBRAIC,
        libcellml::GeneratorVariable::Type::ALGEBRAIC,
        libcellml::GeneratorVariable::Type::ALGEBRAIC,
        libcellml::GeneratorVariable::Type::ALGEBRAIC,
        libcellml::GeneratorVariable::Type::ALGEBRAIC,
        libcellml::GeneratorVariable::Type::ALGEBRAIC,
        libcellml::GeneratorVariable::Type::ALGEBRAIC};

    for (size_t i = 0; i < generator.variableCount(); ++i) {
        EXPECT_NE(nullptr, generator.variable(i)->variable());
        EXPECT_EQ(expectedTypes[i], generator.variable(i)->type());
    }

    EXPECT_EQ(fileContents("generator/hodgkin_huxley_squid_axon_model_1952/model.h"), generator.interfaceCode());
    EXPECT_EQ(fileContents("generator/hodgkin_huxley_squid_axon_model_1952/model.c"), generator.implementationCode());

    libcellml::GeneratorProfilePtr profile = std::make_shared<libcellml::GeneratorProfile>(libcellml::GeneratorProfile::Profile::PYTHON);

    generator.setProfile(profile);

    EXPECT_EQ(EMPTY_STRING, generator.interfaceCode());
    EXPECT_EQ(fileContents("generator/hodgkin_huxley_squid_axon_model_1952/model.py"), generator.implementationCode());
}

TEST(Generator, nobleModel1962)
{
    libcellml::Parser parser;
    libcellml::ModelPtr model = parser.parseModel(fileContents("generator/noble_model_1962/model.cellml"));

    EXPECT_EQ(size_t(0), parser.errorCount());

    libcellml::Generator generator;

    generator.processModel(model);

    EXPECT_EQ(size_t(0), generator.errorCount());

    EXPECT_EQ(libcellml::Generator::ModelType::ODE, generator.modelType());

    EXPECT_EQ(size_t(4), generator.stateCount());
    EXPECT_EQ(size_t(17), generator.variableCount());

    EXPECT_NE(nullptr, generator.voi());
    EXPECT_NE(nullptr, generator.state(0));
    EXPECT_EQ(nullptr, generator.state(generator.stateCount()));
    EXPECT_NE(nullptr, generator.variable(0));
    EXPECT_EQ(nullptr, generator.variable(generator.variableCount()));

    EXPECT_EQ(fileContents("generator/noble_model_1962/model.h"), generator.interfaceCode());
    EXPECT_EQ(fileContents("generator/noble_model_1962/model.c"), generator.implementationCode());

    libcellml::GeneratorProfilePtr profile = std::make_shared<libcellml::GeneratorProfile>(libcellml::GeneratorProfile::Profile::PYTHON);

    generator.setProfile(profile);

    EXPECT_EQ(EMPTY_STRING, generator.interfaceCode());
    EXPECT_EQ(fileContents("generator/noble_model_1962/model.py"), generator.implementationCode());
}

TEST(Generator, coverage)
{
    libcellml::Parser parser;
    libcellml::ModelPtr model = parser.parseModel(fileContents("generator/coverage/model.cellml"));

    EXPECT_EQ(size_t(0), parser.errorCount());

    libcellml::Generator generator;

    generator.processModel(model);

    EXPECT_EQ(size_t(0), generator.errorCount());

    EXPECT_EQ(libcellml::Generator::ModelType::ODE, generator.modelType());

    EXPECT_EQ(size_t(1), generator.stateCount());
    EXPECT_EQ(size_t(186), generator.variableCount());

    EXPECT_NE(nullptr, generator.voi());
    EXPECT_NE(nullptr, generator.state(0));
    EXPECT_EQ(nullptr, generator.state(generator.stateCount()));
    EXPECT_NE(nullptr, generator.variable(0));
    EXPECT_EQ(nullptr, generator.variable(generator.variableCount()));

    EXPECT_EQ(fileContents("generator/coverage/model.h"), generator.interfaceCode());
    EXPECT_EQ(fileContents("generator/coverage/model.c"), generator.implementationCode());

    libcellml::GeneratorProfilePtr profile = generator.profile();

    profile->setInterfaceCreateStatesArrayMethodString("double * createStatesVector();\n");
    profile->setImplementationCreateStatesArrayMethodString("double * createStatesVector()\n"
                                                            "{\n"
                                                            "<CODE>"
                                                            "}\n");

    EXPECT_EQ(fileContents("generator/coverage/model.modified.profile.h"), generator.interfaceCode());
    EXPECT_EQ(fileContents("generator/coverage/model.modified.profile.c"), generator.implementationCode());

    profile = std::make_shared<libcellml::GeneratorProfile>();

    generator.setProfile(profile);

    profile->setHasInterface(false);

    profile->setXorString("^");
    profile->setHasXorOperator(true);

    profile->setPowerString("^^");
    profile->setSquareString("sqr");
    profile->setHasPowerOperator(true);

    profile->setPiecewiseIfString("piecewise(<CONDITION>, <IF_STATEMENT>");
    profile->setPiecewiseElseString(", <ELSE_STATEMENT>)");
    profile->setHasConditionalOperator(false);

    profile->setImplementationHeaderString("");

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

    profile->setReturnCreatedArrayString("");

    profile->setImplementationCreateStatesArrayMethodString("");

    profile->setImplementationCreateVariablesArrayMethodString("");

    profile->setImplementationDeleteArrayMethodString("");

    profile->setImplementationComputeVariablesMethodString("// We should have computeVariables() here, but we replaced it with this comment\n"
                                                           "// and no code template that can be replaced so that our replace() method can\n"
                                                           "// is forced to return an empty string, ensuring 100% coverage using llvm-cov...\n");

    EXPECT_EQ(EMPTY_STRING, generator.interfaceCode());
    EXPECT_EQ(fileContents("generator/coverage/model.out"), generator.implementationCode());

    profile = std::make_shared<libcellml::GeneratorProfile>();

    generator.setProfile(profile);

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

    EXPECT_EQ(fileContents("generator/coverage/model.interface.out"), generator.interfaceCode());
    EXPECT_EQ(fileContents("generator/coverage/model.implementation.out"), generator.implementationCode());

    profile->setProfile(libcellml::GeneratorProfile::Profile::PYTHON);

    EXPECT_EQ(EMPTY_STRING, generator.interfaceCode());
    EXPECT_EQ(fileContents("generator/coverage/model.py"), generator.implementationCode());

    profile->setImplementationCreateStatesArrayMethodString("\n"
                                                            "def create_states_vector():\n"
                                                            "<CODE>");

    EXPECT_EQ(EMPTY_STRING, generator.interfaceCode());
    EXPECT_EQ(fileContents("generator/coverage/model.modified.profile.py"), generator.implementationCode());
}

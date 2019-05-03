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

static const std::string EMPTY_STRING = "";

TEST(Generator, emptyModel) {
    libcellml::ModelPtr model = std::make_shared<libcellml::Model>();

    model->setName("emptyModel");

    libcellml::Generator generator;

    generator.processModel(model);

    EXPECT_EQ(size_t(0), generator.errorCount());

    EXPECT_EQ(size_t(0), generator.stateCount());
    EXPECT_EQ(size_t(0), generator.rateCount());
    EXPECT_EQ(size_t(0), generator.variableCount());

    EXPECT_EQ(EMPTY_STRING, generator.initializeVariables());
    EXPECT_EQ(EMPTY_STRING, generator.computeConstantEquations());
    EXPECT_EQ(EMPTY_STRING, generator.computeRateEquations());
    EXPECT_EQ(EMPTY_STRING, generator.computeAlgebraicEquations());
}

TEST(Generator, coverage) {
//TODO: code should be generated for the coverage CellML file with and without
//      the Generator's private mHasXXX booleans set, so that we really cover
//      everything indeed...
    libcellml::Parser parser;
    libcellml::ModelPtr model = parser.parseModel(fileContents("generator/resources/coverage.cellml"));

    EXPECT_EQ(size_t(0), parser.errorCount());

    libcellml::Generator generator;

    generator.processModel(model);

    EXPECT_EQ(size_t(0), generator.errorCount());
}

/*TODO: reenable this test once we are done with the previous tests...
TEST(Generator, algebraic_eqn_derivative_on_rhs_one_component) {
    libcellml::Parser parser;
    libcellml::ModelPtr model = parser.parseModel(fileContents("generator/resources/algebraic_eqn_derivative_on_rhs_one_component.cellml"));

    EXPECT_EQ(size_t(0), parser.errorCount());

    libcellml::Generator generator;

    generator.processModel(model);

    EXPECT_EQ(size_t(0), generator.errorCount());

    EXPECT_EQ(size_t(1), generator.stateCount());
    EXPECT_EQ(size_t(1), generator.rateCount());
    EXPECT_EQ(size_t(2), generator.variableCount());

    EXPECT_EQ(fileContents("generator/resources/algebraic_eqn_derivative_on_rhs_one_component_initializeVariables.out"),
              generator.initializeVariables());
    EXPECT_EQ(fileContents("generator/resources/algebraic_eqn_derivative_on_rhs_one_component_computeConstantEquations.out"),
              generator.computeConstantEquations());
    EXPECT_EQ(fileContents("generator/resources/algebraic_eqn_derivative_on_rhs_one_component_computeRateEquations.out"),
              generator.computeRateEquations());
    EXPECT_EQ(EMPTY_STRING,
              generator.computeAlgebraicEquations());

    generator.setWithNames(true);

    EXPECT_EQ(fileContents("generator/resources/algebraic_eqn_derivative_on_rhs_one_component_initializeVariables_with_names.out"),
              generator.initializeVariables());
    EXPECT_EQ(fileContents("generator/resources/algebraic_eqn_derivative_on_rhs_one_component_computeConstantEquations_with_names.out"),
              generator.computeConstantEquations());
    EXPECT_EQ(fileContents("generator/resources/algebraic_eqn_derivative_on_rhs_one_component_computeRateEquations_with_names.out"),
              generator.computeRateEquations());
    EXPECT_EQ(EMPTY_STRING,
              generator.computeAlgebraicEquations());
}
*/

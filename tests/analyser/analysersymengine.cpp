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

TEST(Analyser, rearrangeAdditiveEquations)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("analyser/symengine/unarranged_addition.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    auto analyser = libcellml::Analyser::create();

    analyser->analyseModel(model);

    EXPECT_EQ(libcellml::AnalyserModel::Type::ALGEBRAIC, analyser->analyserModel()->type());
}

TEST(Analyser, rearrangeMultiplicativeEquations)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("analyser/symengine/unarranged_multiplication.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    auto analyser = libcellml::Analyser::create();

    analyser->analyseModel(model);

    EXPECT_EQ(libcellml::AnalyserModel::Type::ALGEBRAIC, analyser->analyserModel()->type());
}

TEST(Analyser, rearrangeTrigonometricEquations)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("analyser/symengine/unarranged_trig.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    auto analyser = libcellml::Analyser::create();

    analyser->analyseModel(model);

    EXPECT_EQ(libcellml::AnalyserModel::Type::ALGEBRAIC, analyser->analyserModel()->type());
}

TEST(Analyser, rearrangeInverseTrigonometricEquations)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("analyser/symengine/unarranged_inverse_trig.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    auto analyser = libcellml::Analyser::create();

    analyser->analyseModel(model);

    EXPECT_EQ(libcellml::AnalyserModel::Type::ALGEBRAIC, analyser->analyserModel()->type());
}

TEST(Analyser, rearrangeHyperbolicTrigonometricEquations)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("analyser/symengine/unarranged_hyperbolic_trig.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    auto analyser = libcellml::Analyser::create();

    analyser->analyseModel(model);

    EXPECT_EQ(libcellml::AnalyserModel::Type::ALGEBRAIC, analyser->analyserModel()->type());
}

TEST(Analyser, rearrangeExponentialEquations)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("analyser/symengine/unarranged_exponential.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    auto analyser = libcellml::Analyser::create();

    analyser->analyseModel(model);

    EXPECT_EQ(libcellml::AnalyserModel::Type::ALGEBRAIC, analyser->analyserModel()->type());
}

TEST(Analyser, rearrangeLogarithmicEquations)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("analyser/symengine/unarranged_logarithmic.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    auto analyser = libcellml::Analyser::create();

    analyser->analyseModel(model);

    EXPECT_EQ(libcellml::AnalyserModel::Type::ALGEBRAIC, analyser->analyserModel()->type());
}

TEST(Analyser, rearrangeEquationsWithConstants)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("analyser/symengine/unarranged_constants.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    auto analyser = libcellml::Analyser::create();

    analyser->analyseModel(model);

    EXPECT_EQ(libcellml::AnalyserModel::Type::ALGEBRAIC, analyser->analyserModel()->type());
}

TEST(Analyser, rearrangePolynomialEquations)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("analyser/symengine/unarranged_polynomials.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    auto analyser = libcellml::Analyser::create();

    analyser->analyseModel(model);

    EXPECT_EQ(libcellml::AnalyserModel::Type::ALGEBRAIC, analyser->analyserModel()->type());
}

TEST(Analyser, rearrangeCombinationEquations)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("analyser/symengine/unarranged_combination.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    auto analyser = libcellml::Analyser::create();

    analyser->analyseModel(model);

    EXPECT_EQ(libcellml::AnalyserModel::Type::ALGEBRAIC, analyser->analyserModel()->type());
}
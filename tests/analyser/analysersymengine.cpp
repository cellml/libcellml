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
    auto model = parser->parseModel(fileContents("analyser/symengine/addition.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    auto analyser = libcellml::Analyser::create();

    analyser->analyseModel(model);

    EXPECT_EQ(libcellml::AnalyserModel::Type::ALGEBRAIC, analyser->analyserModel()->type());

    EXPECT_EQ("a = 10.0+-1.0*(w+x)", libcellml::Generator::equationCode(analyser->analyserModel()->analyserEquation(0)->ast()));
    EXPECT_EQ("b = 1.0+-1.0*(2.0+-1.0*y)", libcellml::Generator::equationCode(analyser->analyserModel()->analyserEquation(1)->ast()));
    EXPECT_EQ("c = -1.0*z+-1.0*(1.0+x)", libcellml::Generator::equationCode(analyser->analyserModel()->analyserEquation(2)->ast()));
    EXPECT_EQ("d = y+-1.0*w", libcellml::Generator::equationCode(analyser->analyserModel()->analyserEquation(3)->ast()));
}

TEST(Analyser, rearrangeMultiplicativeEquations)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("analyser/symengine/multiplication.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    auto analyser = libcellml::Analyser::create();

    analyser->analyseModel(model);

    EXPECT_EQ(libcellml::AnalyserModel::Type::ALGEBRAIC, analyser->analyserModel()->type());

    EXPECT_EQ("a = 4.0*pow(w, -1.0)", libcellml::Generator::equationCode(analyser->analyserModel()->analyserEquation(0)->ast()));
    EXPECT_EQ("b = 18.0*y", libcellml::Generator::equationCode(analyser->analyserModel()->analyserEquation(1)->ast()));
    EXPECT_EQ("c = 30.0*x*pow(z, -1.0)", libcellml::Generator::equationCode(analyser->analyserModel()->analyserEquation(2)->ast()));
}

TEST(Analyser, rearrangeTrigonometricEquations)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("analyser/symengine/trigonometric.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    auto analyser = libcellml::Analyser::create();

    analyser->analyseModel(model);

    EXPECT_EQ(libcellml::AnalyserModel::Type::ALGEBRAIC, analyser->analyserModel()->type());

    EXPECT_EQ("a = 1/2.0*(1.0+-1.0*sin(w))", libcellml::Generator::equationCode(analyser->analyserModel()->analyserEquation(0)->ast()));
    EXPECT_EQ("b = cos(4.0+x)", libcellml::Generator::equationCode(analyser->analyserModel()->analyserEquation(1)->ast()));
    EXPECT_EQ("c = 2.0+tan(3.0+-1.0*y)", libcellml::Generator::equationCode(analyser->analyserModel()->analyserEquation(2)->ast()));
}

TEST(Analyser, rearrangeEquationsWithConstants)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("analyser/symengine/constants.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    auto analyser = libcellml::Analyser::create();

    analyser->analyseModel(model);

    EXPECT_EQ(libcellml::AnalyserModel::Type::ALGEBRAIC, analyser->analyserModel()->type());

    EXPECT_EQ("a = 8.65+-1.0*x", libcellml::Generator::equationCode(analyser->analyserModel()->analyserEquation(0)->ast()));
    EXPECT_EQ("b = 400000.0*pow(w, -1.0)", libcellml::Generator::equationCode(analyser->analyserModel()->analyserEquation(1)->ast()));
    EXPECT_EQ("c = y*2.71828182845905", libcellml::Generator::equationCode(analyser->analyserModel()->analyserEquation(2)->ast()));
    EXPECT_EQ("d = -1.0*(-1.0*z+-1.0*3.14159265358979)", libcellml::Generator::equationCode(analyser->analyserModel()->analyserEquation(3)->ast()));
    EXPECT_EQ("e = INFINITY+-1.0*w", libcellml::Generator::equationCode(analyser->analyserModel()->analyserEquation(4)->ast()));
}

TEST(Analyser, rearrangePolynomialEquations)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("analyser/symengine/polynomials.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    auto analyser = libcellml::Analyser::create();

    analyser->analyseModel(model);

    EXPECT_EQ(libcellml::AnalyserModel::Type::ALGEBRAIC, analyser->analyserModel()->type());

    EXPECT_EQ("a = -1/3.0*(6.0+15.0*pow(-1.0, 1/3.0))", libcellml::Generator::equationCode(analyser->analyserModel()->analyserEquation(0)->ast()));
    EXPECT_EQ("b = -2.0", libcellml::Generator::equationCode(analyser->analyserModel()->analyserEquation(1)->ast()));
    EXPECT_EQ("c = -1/3.0*(1/2.0*pow(2.0, 2/3.0)*pow(-972.0+pow(947700.0, 1/2.0), 1/3.0)+-9.0*pow(2.0, 1/3.0)*pow(-972.0+pow(947700.0, 1/2.0), -1/3.0))", libcellml::Generator::equationCode(analyser->analyserModel()->analyserEquation(2)->ast()));
    EXPECT_EQ("d = -1/6.0*pow(2.0, 2/3.0)*pow(-27.0*w+27.0*pow(pow(w, 2.0), 1/2.0), 1/3.0)", libcellml::Generator::equationCode(analyser->analyserModel()->analyserEquation(3)->ast()));
}

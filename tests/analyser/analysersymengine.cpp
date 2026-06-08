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

TEST(AnalyserSymEngine, rearrangeAdditiveEquations)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("analyser/symengine/addition.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    auto analyser = libcellml::Analyser::create();

    analyser->analyseModel(model);

    auto analyserModel = analyser->analyserModel();

    EXPECT_EQ(libcellml::AnalyserModel::Type::ALGEBRAIC, analyserModel->type());

#ifdef _WIN32
    EXPECT_EQ("a = 10.0-w-x", libcellml::Generator::equationCode(analyserModel->analyserEquation(0)->ast()));
#else
    EXPECT_EQ("a = 10.0-x-w", libcellml::Generator::equationCode(analyserModel->analyserEquation(0)->ast()));
#endif
    EXPECT_EQ("b = -1.0+y", libcellml::Generator::equationCode(analyserModel->analyserEquation(1)->ast()));
    EXPECT_EQ("c = -1.0-z-x", libcellml::Generator::equationCode(analyserModel->analyserEquation(2)->ast()));
    EXPECT_EQ("d = y-w", libcellml::Generator::equationCode(analyserModel->analyserEquation(3)->ast()));
}

TEST(AnalyserSymEngine, rearrangeMultiplicativeEquations)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("analyser/symengine/multiplication.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    auto analyser = libcellml::Analyser::create();

    analyser->analyseModel(model);

    auto analyserModel = analyser->analyserModel();

    EXPECT_EQ(libcellml::AnalyserModel::Type::ALGEBRAIC, analyserModel->type());

    EXPECT_EQ("a = 4.0/w", libcellml::Generator::equationCode(analyserModel->analyserEquation(0)->ast()));
    EXPECT_EQ("b = 18.0*y", libcellml::Generator::equationCode(analyserModel->analyserEquation(1)->ast()));
    EXPECT_EQ("c = 30.0*x/z", libcellml::Generator::equationCode(analyserModel->analyserEquation(2)->ast()));
}

TEST(AnalyserSymEngine, rearrangeTrigonometricEquations)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("analyser/symengine/trigonometric.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    auto analyser = libcellml::Analyser::create();

    analyser->analyseModel(model);

    auto analyserModel = analyser->analyserModel();

    EXPECT_EQ(libcellml::AnalyserModel::Type::ALGEBRAIC, analyserModel->type());

    EXPECT_EQ("a = 0.5-0.5*sin(z1)", libcellml::Generator::equationCode(analyserModel->analyserEquation(0)->ast()));
    EXPECT_EQ("b = cos(4.0+z2)", libcellml::Generator::equationCode(analyserModel->analyserEquation(1)->ast()));
    EXPECT_EQ("c = 2.0+tan(3.0-z3)", libcellml::Generator::equationCode(analyserModel->analyserEquation(2)->ast()));
    EXPECT_EQ("d = 0.5-0.5*sec(z1)", libcellml::Generator::equationCode(analyserModel->analyserEquation(3)->ast()));
    EXPECT_EQ("e = csc(4.0+z2)", libcellml::Generator::equationCode(analyserModel->analyserEquation(4)->ast()));
    EXPECT_EQ("f = 2.0+cot(3.0-z3)", libcellml::Generator::equationCode(analyserModel->analyserEquation(5)->ast()));
    EXPECT_EQ("g = 0.5-0.5*sinh(z1)", libcellml::Generator::equationCode(analyserModel->analyserEquation(6)->ast()));
    EXPECT_EQ("h = cosh(4.0+z2)", libcellml::Generator::equationCode(analyserModel->analyserEquation(7)->ast()));
    EXPECT_EQ("i = 2.0+tanh(3.0-z3)", libcellml::Generator::equationCode(analyserModel->analyserEquation(8)->ast()));
    EXPECT_EQ("j = 0.5-0.5*sech(z1)", libcellml::Generator::equationCode(analyserModel->analyserEquation(9)->ast()));
    EXPECT_EQ("k = csch(4.0+z2)", libcellml::Generator::equationCode(analyserModel->analyserEquation(10)->ast()));
    EXPECT_EQ("l = 2.0+coth(3.0-z3)", libcellml::Generator::equationCode(analyserModel->analyserEquation(11)->ast()));
    EXPECT_EQ("m = 0.5-0.5*asin(z1)", libcellml::Generator::equationCode(analyserModel->analyserEquation(12)->ast()));
    EXPECT_EQ("n = acos(4.0+z2)", libcellml::Generator::equationCode(analyserModel->analyserEquation(13)->ast()));
    EXPECT_EQ("o = 2.0+atan(3.0-z3)", libcellml::Generator::equationCode(analyserModel->analyserEquation(14)->ast()));
    EXPECT_EQ("p = 0.5-0.5*asec(z1)", libcellml::Generator::equationCode(analyserModel->analyserEquation(15)->ast()));
    EXPECT_EQ("q = acsc(4.0+z2)", libcellml::Generator::equationCode(analyserModel->analyserEquation(16)->ast()));
    EXPECT_EQ("r = 2.0+acot(3.0-z3)", libcellml::Generator::equationCode(analyserModel->analyserEquation(17)->ast()));
    EXPECT_EQ("s = 0.5-0.5*asinh(z1)", libcellml::Generator::equationCode(analyserModel->analyserEquation(18)->ast()));
    EXPECT_EQ("t = acosh(4.0+z2)", libcellml::Generator::equationCode(analyserModel->analyserEquation(19)->ast()));
    EXPECT_EQ("u = 2.0+atanh(3.0-z3)", libcellml::Generator::equationCode(analyserModel->analyserEquation(20)->ast()));
    EXPECT_EQ("v = 0.5-0.5*asech(z1)", libcellml::Generator::equationCode(analyserModel->analyserEquation(21)->ast()));
    EXPECT_EQ("w = acsch(4.0+z2)", libcellml::Generator::equationCode(analyserModel->analyserEquation(22)->ast()));
    EXPECT_EQ("x = 2.0+acoth(3.0-z3)", libcellml::Generator::equationCode(analyserModel->analyserEquation(23)->ast()));
}

TEST(AnalyserSymEngine, rearrangeEquationsWithConstants)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("analyser/symengine/constants.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    auto analyser = libcellml::Analyser::create();

    analyser->analyseModel(model);

    auto analyserModel = analyser->analyserModel();

    EXPECT_EQ(libcellml::AnalyserModel::Type::ALGEBRAIC, analyserModel->type());

    EXPECT_EQ("a = 8.65-x", libcellml::Generator::equationCode(analyserModel->analyserEquation(0)->ast()));
    EXPECT_EQ("b = 400000.0/w", libcellml::Generator::equationCode(analyserModel->analyserEquation(1)->ast()));
    EXPECT_EQ("c = y*2.71828182845905", libcellml::Generator::equationCode(analyserModel->analyserEquation(2)->ast()));
#ifdef __linux__
    EXPECT_EQ("d = 3.14159265358979+z", libcellml::Generator::equationCode(analyserModel->analyserEquation(3)->ast()));
#else
    EXPECT_EQ("d = z+3.14159265358979", libcellml::Generator::equationCode(analyserModel->analyserEquation(3)->ast()));
#endif

    EXPECT_EQ("e = INFINITY-w", libcellml::Generator::equationCode(analyserModel->analyserEquation(4)->ast()));
}

TEST(AnalyserSymEngine, rearrangePolynomialEquations)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("analyser/symengine/polynomials.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    auto analyser = libcellml::Analyser::create();

    analyser->analyseModel(model);

    auto analyserModel = analyser->analyserModel();

    EXPECT_EQ(libcellml::AnalyserModel::Type::ALGEBRAIC, analyserModel->type());

    EXPECT_EQ("a = 3.0", libcellml::Generator::equationCode(analyserModel->analyserEquation(0)->ast()));
    EXPECT_EQ("b = -2.0", libcellml::Generator::equationCode(analyserModel->analyserEquation(1)->ast()));
    EXPECT_EQ("c = 3.0", libcellml::Generator::equationCode(analyserModel->analyserEquation(2)->ast()));
    EXPECT_EQ("d = pow(w, 0.333333333333333)", libcellml::Generator::equationCode(analyserModel->analyserEquation(3)->ast()));
}

TEST(AnalyserSymEngine, rearrangeExponentialEquations)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("analyser/symengine/exponential.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    auto analyser = libcellml::Analyser::create();

    analyser->analyseModel(model);

    auto analyserModel = analyser->analyserModel();

    EXPECT_EQ(libcellml::AnalyserModel::Type::ALGEBRAIC, analyserModel->type());

    EXPECT_EQ("a = 200.0+exp(-10.0+w)", libcellml::Generator::equationCode(analyserModel->analyserEquation(0)->ast()));
    EXPECT_EQ("b = -7.22597376812575e+86", libcellml::Generator::equationCode(analyserModel->analyserEquation(1)->ast()));
}

TEST(AnalyserSymEngine, rearrangeLogarithmicEquations)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("analyser/symengine/logarithmic.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    auto analyser = libcellml::Analyser::create();

    analyser->analyseModel(model);

    auto analyserModel = analyser->analyserModel();

    EXPECT_EQ(libcellml::AnalyserModel::Type::ALGEBRAIC, analyserModel->type());

    EXPECT_EQ("a = 5.0-log(x)", libcellml::Generator::equationCode(analyserModel->analyserEquation(0)->ast()));
#ifdef _WIN32
    EXPECT_EQ("b = -y+0.477121254719662", libcellml::Generator::equationCode(analyserModel->analyserEquation(1)->ast()));
#else
    EXPECT_EQ("b = 0.477121254719662-y", libcellml::Generator::equationCode(analyserModel->analyserEquation(1)->ast()));
#endif
    EXPECT_EQ("c = 2.5-1.44269504088896*log(z)", libcellml::Generator::equationCode(analyserModel->analyserEquation(2)->ast()));
}

TEST(AnalyserSymEngine, rearrangeUncommonArithmeticEquations)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("analyser/symengine/uncommon_arithmetic.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    auto analyser = libcellml::Analyser::create();

    analyser->analyseModel(model);

    auto analyserModel = analyser->analyserModel();

    EXPECT_EQ(libcellml::AnalyserModel::Type::ALGEBRAIC, analyserModel->type());

    EXPECT_EQ("a = 2.0-sqrt(w)", libcellml::Generator::equationCode(analyserModel->analyserEquation(0)->ast()));
    EXPECT_EQ("b = pow(w, -0.25)", libcellml::Generator::equationCode(analyserModel->analyserEquation(1)->ast()));
#ifdef _WIN32
    EXPECT_EQ("c = 3.0*fabs(x-y)", libcellml::Generator::equationCode(analyserModel->analyserEquation(2)->ast()));
#else
    EXPECT_EQ("c = 3.0*fabs(-y+x)", libcellml::Generator::equationCode(analyserModel->analyserEquation(2)->ast()));
#endif
    EXPECT_EQ("d = w-ceil(0.4+x)", libcellml::Generator::equationCode(analyserModel->analyserEquation(3)->ast()));
    EXPECT_EQ("e = 1.0+floor(0.5*z)", libcellml::Generator::equationCode(analyserModel->analyserEquation(4)->ast()));
    EXPECT_EQ("f = 0.2*min(x, y)", libcellml::Generator::equationCode(analyserModel->analyserEquation(5)->ast()));
    EXPECT_EQ("g = w/max(y, z)", libcellml::Generator::equationCode(analyserModel->analyserEquation(6)->ast()));
    EXPECT_EQ("h = -fmod(z, w)", libcellml::Generator::equationCode(analyserModel->analyserEquation(7)->ast()));
}

TEST(AnalyserSymEngine, rearrangeDifferentialEquations)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("analyser/symengine/differential.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    auto analyser = libcellml::Analyser::create();

    analyser->analyseModel(model);

    auto analyserModel = analyser->analyserModel();

    EXPECT_EQ(libcellml::AnalyserModel::Type::ODE, analyserModel->type());

    EXPECT_EQ("x = -dy/dt", libcellml::Generator::equationCode(analyserModel->analyserEquation(0)->ast()));
}

TEST(AnalyserSymEngine, unrearrangeableEquations)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("analyser/symengine/unrearrangeable.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    auto analyser = libcellml::Analyser::create();

    analyser->analyseModel(model);

    auto analyserModel = analyser->analyserModel();

    EXPECT_EQ(libcellml::AnalyserModel::Type::NLA, analyserModel->type());

#ifdef _WIN32
    EXPECT_EQ("2.0*x1+sin(a)-1.0", libcellml::Generator::equationCode(analyserModel->analyserEquation(0)->ast()));
    EXPECT_EQ("csc(4.0+b)-x2", libcellml::Generator::equationCode(analyserModel->analyserEquation(1)->ast()));
    EXPECT_EQ("x1-tanh(3.0-c)-2.0", libcellml::Generator::equationCode(analyserModel->analyserEquation(2)->ast()));
    EXPECT_EQ("sech(d)+x2-1.0", libcellml::Generator::equationCode(analyserModel->analyserEquation(3)->ast()));
    EXPECT_EQ("acos(e)-x1-0.5", libcellml::Generator::equationCode(analyserModel->analyserEquation(4)->ast()));
#else
    EXPECT_EQ("sin(a)+2.0*x1-1.0", libcellml::Generator::equationCode(analyserModel->analyserEquation(0)->ast()));
    EXPECT_EQ("-x2+csc(4.0+b)", libcellml::Generator::equationCode(analyserModel->analyserEquation(1)->ast()));
    EXPECT_EQ("-tanh(3.0-c)+x1-2.0", libcellml::Generator::equationCode(analyserModel->analyserEquation(2)->ast()));
    EXPECT_EQ("x2+sech(d)-1.0", libcellml::Generator::equationCode(analyserModel->analyserEquation(3)->ast()));
    EXPECT_EQ("-x1+acos(e)-0.5", libcellml::Generator::equationCode(analyserModel->analyserEquation(4)->ast()));
#endif
    EXPECT_EQ("x2-acot(2.0+f)", libcellml::Generator::equationCode(analyserModel->analyserEquation(5)->ast()));
#ifdef _WIN32
    EXPECT_EQ("x1+asinh(g)-1.0", libcellml::Generator::equationCode(analyserModel->analyserEquation(6)->ast()));
    EXPECT_EQ("-acsch(1.0-h)-x1", libcellml::Generator::equationCode(analyserModel->analyserEquation(7)->ast()));
    EXPECT_EQ("-2.0+pow(i, 2.0)-3.0*i", libcellml::Generator::equationCode(analyserModel->analyserEquation(8)->ast()));
#else
    EXPECT_EQ("asinh(g)+x1-1.0", libcellml::Generator::equationCode(analyserModel->analyserEquation(6)->ast()));
    EXPECT_EQ("-x1-acsch(1.0-h)", libcellml::Generator::equationCode(analyserModel->analyserEquation(7)->ast()));
    EXPECT_EQ("-2.0-3.0*i+pow(i, 2.0)", libcellml::Generator::equationCode(analyserModel->analyserEquation(8)->ast()));
#endif
    EXPECT_EQ("x1-log(j)", libcellml::Generator::equationCode(analyserModel->analyserEquation(9)->ast()));
    EXPECT_EQ("-0.434294481903251*log(k)+x2", libcellml::Generator::equationCode(analyserModel->analyserEquation(10)->ast()));
#ifdef _WIN32
    EXPECT_EQ("exp(l)+x1-3.0", libcellml::Generator::equationCode(analyserModel->analyserEquation(11)->ast()));
#else
    EXPECT_EQ("x1+exp(l)-3.0", libcellml::Generator::equationCode(analyserModel->analyserEquation(11)->ast()));
#endif
    EXPECT_EQ("pow(m, 2.5)-30.0", libcellml::Generator::equationCode(analyserModel->analyserEquation(12)->ast()));
    EXPECT_EQ("pow(2.0, n)-16.0", libcellml::Generator::equationCode(analyserModel->analyserEquation(13)->ast()));
    EXPECT_EQ("x2-((x1 == 0.0)?x1:o)", libcellml::Generator::equationCode(analyserModel->analyserEquation(14)->ast()));
    EXPECT_EQ("x3-p*exp(p)", libcellml::Generator::equationCode(analyserModel->analyserEquation(15)->ast()));
#ifdef _WIN32
    EXPECT_EQ("fabs(q)-x1", libcellml::Generator::equationCode(analyserModel->analyserEquation(16)->ast()));
#else
    EXPECT_EQ("-x1+fabs(q)", libcellml::Generator::equationCode(analyserModel->analyserEquation(16)->ast()));
#endif
    EXPECT_EQ("ceil(r)-5.0", libcellml::Generator::equationCode(analyserModel->analyserEquation(17)->ast()));
#ifdef _WIN32
    EXPECT_EQ("floor(s)+x2-3.0", libcellml::Generator::equationCode(analyserModel->analyserEquation(18)->ast()));
#else
    EXPECT_EQ("x2+floor(s)-3.0", libcellml::Generator::equationCode(analyserModel->analyserEquation(18)->ast()));
#endif
    EXPECT_EQ("x2-min(t, x1)", libcellml::Generator::equationCode(analyserModel->analyserEquation(19)->ast()));
    EXPECT_EQ("-x1+max(2.0, u)-1.0", libcellml::Generator::equationCode(analyserModel->analyserEquation(20)->ast()));
    EXPECT_EQ("x2-fmod(v, 3.0)", libcellml::Generator::equationCode(analyserModel->analyserEquation(21)->ast()));
}

TEST(AnalyserSymEngine, breakAlgebraicLoop)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("analyser/symengine/simple_capillary.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    auto analyser = libcellml::Analyser::create();

    analyser->analyseModel(model);

    auto analyserModel = analyser->analyserModel();

    EXPECT_EQ(libcellml::AnalyserModel::Type::ODE, analyserModel->type());

    EXPECT_EQ("v_y = v_in-v_z", libcellml::Generator::equationCode(analyserModel->analyserEquation(0)->ast()));
    EXPECT_EQ("P_x = P_out+P_R", libcellml::Generator::equationCode(analyserModel->analyserEquation(1)->ast()));
#if defined(_WIN32)
    EXPECT_EQ("v_z = -R_v*v_in/(-R_v-R)-P_C/(-R_v-R)+P_out/(-R_v-R)", libcellml::Generator::equationCode(analyserModel->analyserEquation(2)->ast()));
#elif defined(__linux__)
    EXPECT_EQ("v_z = -P_C/(-R-R_v)-R_v*v_in/(-R-R_v)+P_out/(-R-R_v)", libcellml::Generator::equationCode(analyserModel->analyserEquation(2)->ast()));
#else
    EXPECT_EQ("v_z = -R_v*v_in/(-R-R_v)+P_out/(-R-R_v)-P_C/(-R-R_v)", libcellml::Generator::equationCode(analyserModel->analyserEquation(2)->ast()));
#endif
    EXPECT_EQ("P_R = v_z*R", libcellml::Generator::equationCode(analyserModel->analyserEquation(3)->ast()));
    EXPECT_EQ("P_R_v = v_y*R_v", libcellml::Generator::equationCode(analyserModel->analyserEquation(4)->ast()));
    EXPECT_EQ("dq/dt = v_y", libcellml::Generator::equationCode(analyserModel->analyserEquation(5)->ast()));
    EXPECT_EQ("P_C = q/C", libcellml::Generator::equationCode(analyserModel->analyserEquation(6)->ast()));
}

TEST(AnalyserSymEngine, breakTwoIndependentAlgebraicLoops)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("analyser/symengine/winograd_destexhe_sanchezvives_2008.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    auto analyser = libcellml::Analyser::create();

    analyser->analyseModel(model);

    auto analyserModel = analyser->analyserModel();

    EXPECT_EQ(libcellml::AnalyserModel::Type::ODE, analyserModel->type());

#ifdef _WIN32
    EXPECT_EQ("p_1 = k_1Ca/(k_1Ca+k_2)", libcellml::Generator::equationCode(analyserModel->analyserEquation(37)->ast()));
#else
    EXPECT_EQ("p_1 = k_1Ca/(k_2+k_1Ca)", libcellml::Generator::equationCode(analyserModel->analyserEquation(37)->ast()));
#endif
#if defined(_WIN32) || defined(__linux__)
    EXPECT_EQ("o_1 = pow(p_C, n_exp)*alpha/(pow(p_C, n_exp)*beta+pow(p_C, n_exp)*alpha+pow(p_1, n_exp)*alpha)", libcellml::Generator::equationCode(analyserModel->analyserEquation(40)->ast()));
#else
    EXPECT_EQ("o_1 = pow(p_C, n_exp)*alpha/(pow(p_C, n_exp)*alpha+pow(p_C, n_exp)*beta+pow(p_1, n_exp)*alpha)", libcellml::Generator::equationCode(analyserModel->analyserEquation(40)->ast()));
#endif
}

TEST(AnalyserSymEngine, break2dLinearSystem)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("analyser/symengine/linear_system_2d.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    auto analyser = libcellml::Analyser::create();

    analyser->analyseModel(model);

    auto analyserModel = analyser->analyserModel();

    EXPECT_EQ(libcellml::AnalyserModel::Type::ALGEBRAIC, analyserModel->type());

    EXPECT_EQ("x = 1.0", libcellml::Generator::equationCode(analyserModel->analyserEquation(0)->ast()));
    EXPECT_EQ("y = 2.0", libcellml::Generator::equationCode(analyserModel->analyserEquation(1)->ast()));
}

TEST(AnalyserSymEngine, break3dLinearSystem)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("analyser/symengine/linear_system_3d.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    auto analyser = libcellml::Analyser::create();

    analyser->analyseModel(model);

    auto analyserModel = analyser->analyserModel();

    EXPECT_EQ(libcellml::AnalyserModel::Type::ALGEBRAIC, analyserModel->type());

    EXPECT_EQ("x = 2.0", libcellml::Generator::equationCode(analyserModel->analyserEquation(0)->ast()));
    EXPECT_EQ("y = 1.0", libcellml::Generator::equationCode(analyserModel->analyserEquation(1)->ast()));
    EXPECT_EQ("z = 3.0", libcellml::Generator::equationCode(analyserModel->analyserEquation(2)->ast()));
}

TEST(AnalyserSymEngine, break4dLinearSystem)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("analyser/symengine/linear_system_4d.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    auto analyser = libcellml::Analyser::create();

    analyser->analyseModel(model);

    auto analyserModel = analyser->analyserModel();

    EXPECT_EQ(libcellml::AnalyserModel::Type::ALGEBRAIC, analyserModel->type());

    EXPECT_EQ("a = 2.0", libcellml::Generator::equationCode(analyserModel->analyserEquation(0)->ast()));
    EXPECT_EQ("b = 1.0", libcellml::Generator::equationCode(analyserModel->analyserEquation(1)->ast()));
    EXPECT_EQ("c = 3.0", libcellml::Generator::equationCode(analyserModel->analyserEquation(2)->ast()));
    EXPECT_EQ("d = 4.0", libcellml::Generator::equationCode(analyserModel->analyserEquation(3)->ast()));
}

TEST(AnalyserSymEngine, intercomponentRearrangement)
{
    const std::string issue = "Given model is a CellML 1.1 model, the parser will try to represent this model in CellML 2.0.";

    auto parser = libcellml::Parser::create(false);
    auto model = parser->parseModel(fileContents("analyser/symengine/capillary_network/capillary_network.cellml"));

    EXPECT_EQ(size_t(1), parser->issueCount());
    EXPECT_EQ(issue, parser->issue(0)->description());

    auto importer = libcellml::Importer::create(false);

    importer->resolveImports(model, resourcePath("analyser/symengine/capillary_network"));

    auto importedModel = importer->flattenModel(model);

    EXPECT_EQ(size_t(0), importer->issueCount());

    auto analyser = libcellml::Analyser::create();

    analyser->analyseModel(importedModel);

    EXPECT_EQ(libcellml::AnalyserModel::Type::ODE, analyser->analyserModel()->type());
}

TEST(AnalyserSymEngine, relationalAndLogicalSimplifications)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("analyser/symengine/relational_and_logical_simplifications.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    auto analyser = libcellml::Analyser::create();

    analyser->analyseModel(model);

    EXPECT_EQ(size_t(0), analyser->issueCount());

    auto analyserModel = analyser->analyserModel();
    auto generator = libcellml::Generator::create();

    EXPECT_EQ_FILE_CONTENTS("analyser/symengine/relational_and_logical_simplifications.c", generator->implementationCode(analyserModel));
}

TEST(AnalyserSymEngine, arithmeticSimplifications)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("analyser/symengine/arithmetic_simplifications.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    auto analyser = libcellml::Analyser::create();

    analyser->analyseModel(model);

    EXPECT_EQ(size_t(0), analyser->issueCount());

    auto analyserModel = analyser->analyserModel();
    auto generator = libcellml::Generator::create();

    EXPECT_EQ_FILE_CONTENTS("analyser/symengine/arithmetic_simplifications.c", generator->implementationCode(analyserModel));
}

TEST(AnalyserSymEngine, trigonometricSimplifications)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("analyser/symengine/trigonometric_simplifications.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    auto analyser = libcellml::Analyser::create();

    analyser->analyseModel(model);

    EXPECT_EQ(size_t(0), analyser->issueCount());

    auto analyserModel = analyser->analyserModel();
    auto generator = libcellml::Generator::create();

    EXPECT_EQ_FILE_CONTENTS("analyser/symengine/trigonometric_simplifications.c", generator->implementationCode(analyserModel));
}

TEST(AnalyserSymEngine, coverage)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("analyser/symengine/coverage.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    auto analyser = libcellml::Analyser::create();

    analyser->analyseModel(model);

    EXPECT_EQ(size_t(0), analyser->issueCount());

    auto analyserModel = analyser->analyserModel();
    auto generator = libcellml::Generator::create();

    EXPECT_EQ_FILE_CONTENTS("analyser/symengine/coverage" OS_FILE_SUFFIX ".c", generator->implementationCode(analyserModel));
}

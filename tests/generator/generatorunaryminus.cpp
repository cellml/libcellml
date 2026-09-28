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

TEST(GeneratorUnaryMinus, example01)
{
    // rates[0] = --1.0;
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("generator/unary_minus/example_01.cellml"));

    EXPECT_NE(nullptr, model);

    auto analyser = libcellml::Analyser::create();
    analyser->analyseModel(model);

    EXPECT_EQ(size_t(0), analyser->issueCount());

    auto generator = libcellml::Generator::create();

    auto implementationCode = generator->implementationCode(analyser->analyserModel());

    EXPECT_TRUE(implementationCode.find("rates[0] = -(-1.0);\n") != std::string::npos);
}

TEST(GeneratorUnaryMinus, example02)
{
    // rates[0] = --2.0*constants[0];
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("generator/unary_minus/example_02.cellml"));

    EXPECT_NE(nullptr, model);

    auto analyser = libcellml::Analyser::create();
    analyser->analyseModel(model);

    EXPECT_EQ(size_t(0), analyser->issueCount());

    auto generator = libcellml::Generator::create();

    auto implementationCode = generator->implementationCode(analyser->analyserModel());

    EXPECT_TRUE(implementationCode.find("rates[0] = -(-2.0*constants[0]);\n") != std::string::npos);
}

TEST(GeneratorUnaryMinus, example03)
{
    // rates[0] = --constants[1]/constants[0];
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("generator/unary_minus/example_03.cellml"));

    EXPECT_NE(nullptr, model);

    auto analyser = libcellml::Analyser::create();
    analyser->analyseModel(model);

    EXPECT_EQ(size_t(0), analyser->issueCount());

    auto generator = libcellml::Generator::create();

    auto implementationCode = generator->implementationCode(analyser->analyserModel());

    EXPECT_TRUE(implementationCode.find("rates[0] = -(-constants[1]/constants[0]);\n") != std::string::npos);
}

TEST(GeneratorUnaryMinus, example04)
{
    // rates[0] = -(-1.0);
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("generator/unary_minus/example_04.cellml"));

    EXPECT_NE(nullptr, model);

    auto analyser = libcellml::Analyser::create();
    analyser->analyseModel(model);

    EXPECT_EQ(size_t(0), analyser->issueCount());

    auto generator = libcellml::Generator::create();

    auto implementationCode = generator->implementationCode(analyser->analyserModel());

    EXPECT_TRUE(implementationCode.find("rates[0] = -(-1.0);\n") != std::string::npos);
}

TEST(GeneratorUnaryMinus, example05)
{
    // rates[0] = -(-constants[1]+constants[0]);
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("generator/unary_minus/example_05.cellml"));

    EXPECT_NE(nullptr, model);

    auto analyser = libcellml::Analyser::create();
    analyser->analyseModel(model);

    EXPECT_EQ(size_t(0), analyser->issueCount());

    auto generator = libcellml::Generator::create();

    auto implementationCode = generator->implementationCode(analyser->analyserModel());

    EXPECT_TRUE(implementationCode.find("rates[0] = -(-constants[1]+constants[0]);\n") != std::string::npos);
}

TEST(GeneratorUnaryMinus, example06)
{
    // rates[0] = -pow(-constants[1], constants[0]);
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("generator/unary_minus/example_06.cellml"));

    EXPECT_NE(nullptr, model);

    auto analyser = libcellml::Analyser::create();
    analyser->analyseModel(model);

    EXPECT_EQ(size_t(0), analyser->issueCount());

    auto generator = libcellml::Generator::create();

    auto implementationCode = generator->implementationCode(analyser->analyserModel());

    EXPECT_TRUE(implementationCode.find("rates[0] = -pow(-constants[1], constants[0]);\n") != std::string::npos);
}

TEST(GeneratorUnaryMinus, example07)
{
    // rates[0] = constants[1]-(-constants[0]);
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("generator/unary_minus/example_07.cellml"));

    EXPECT_NE(nullptr, model);

    auto analyser = libcellml::Analyser::create();
    analyser->analyseModel(model);

    EXPECT_EQ(size_t(0), analyser->issueCount());

    auto generator = libcellml::Generator::create();

    auto implementationCode = generator->implementationCode(analyser->analyserModel());

    EXPECT_TRUE(implementationCode.find("rates[0] = constants[1]-(-constants[0]);\n") != std::string::npos);
}

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

namespace {

std::string implementationCode(const std::string &fileName, bool needMinFunction, bool needMaxFunction)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents(fileName));

    EXPECT_NE(nullptr, model);

    auto analyser = libcellml::Analyser::create();

    analyser->analyseModel(model);

    EXPECT_EQ(size_t(0), analyser->issueCount());

    auto analyserModel = analyser->analyserModel();

    EXPECT_EQ(needMinFunction, analyserModel->needMinFunction());
    EXPECT_EQ(needMaxFunction, analyserModel->needMaxFunction());

    return libcellml::Generator::create()->implementationCode(analyserModel);
}

} // namespace

TEST(GeneratorUnaryMinMax, example01)
{
    // algebraicVariables[0] = min(voi);

    auto code = implementationCode("generator/unary_min_max/example_01.cellml", false, false);

    EXPECT_TRUE(code.find("algebraicVariables[0] = voi;\n") != std::string::npos);
}

TEST(GeneratorUnaryMinMax, example02)
{
    // algebraicVariables[0] = max(voi);

    auto code = implementationCode("generator/unary_min_max/example_02.cellml", false, false);

    EXPECT_TRUE(code.find("algebraicVariables[0] = voi;\n") != std::string::npos);
}

TEST(GeneratorUnaryMinMax, example03)
{
    // computedConstants[0] = 2.0*min(constants[1]+constants[0]);

    auto code = implementationCode("generator/unary_min_max/example_03.cellml", false, false);

    EXPECT_TRUE(code.find("computedConstants[0] = 2.0*(constants[1]+constants[0]);\n") != std::string::npos);
}

TEST(GeneratorUnaryMinMax, example04)
{
    // computedConstants[0] = 2.0*max(constants[1]+constants[0]);

    auto code = implementationCode("generator/unary_min_max/example_04.cellml", false, false);

    EXPECT_TRUE(code.find("computedConstants[0] = 2.0*(constants[1]+constants[0]);\n") != std::string::npos);
}

TEST(GeneratorUnaryMinMax, example05)
{
    // algebraicVariables[0] = max(min(voi), constants[0]);

    auto code = implementationCode("generator/unary_min_max/example_05.cellml", false, true);

    EXPECT_TRUE(code.find("algebraicVariables[0] = max(voi, constants[0]);\n") != std::string::npos);
}

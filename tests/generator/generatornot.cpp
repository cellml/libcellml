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

TEST(GeneratorNot, operandWithParentheses)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("generator/not/model.cellml"));

    EXPECT_NE(nullptr, model);

    auto analyser = libcellml::Analyser::create();

    analyser->analyseModel(model);

    EXPECT_EQ(size_t(0), analyser->issueCount());

    auto generator = libcellml::Generator::create();
    auto implementationCode = generator->implementationCode(analyser->analyserModel());

    EXPECT_NE(std::string::npos, implementationCode.find("computedConstants[0] = !constants[0];\n"));
    EXPECT_NE(std::string::npos, implementationCode.find("algebraicVariables[0] = !(voi > 5.5);\n"));
    EXPECT_NE(std::string::npos, implementationCode.find("algebraicVariables[1] = !((voi > 5.5) && (voi < 2.5));\n"));
    EXPECT_NE(std::string::npos, implementationCode.find("algebraicVariables[2] = !!(voi > 5.5);\n"));
    EXPECT_NE(std::string::npos, implementationCode.find("algebraicVariables[3] = !(voi > 5.5) && (voi < 2.5);\n"));
    EXPECT_NE(std::string::npos, implementationCode.find("algebraicVariables[4] = (!(voi > 5.5))?1.0:0.0;\n"));
    EXPECT_NE(std::string::npos, implementationCode.find("algebraicVariables[5] = !(voi+constants[0]);\n"));
    EXPECT_NE(std::string::npos, implementationCode.find("algebraicVariables[6] = !-voi;\n"));
    EXPECT_NE(std::string::npos, implementationCode.find("algebraicVariables[7] = !(voi*constants[0]);\n"));
    EXPECT_NE(std::string::npos, implementationCode.find("algebraicVariables[8] = !((voi > 5.5) || constants[0]);\n"));
    EXPECT_NE(std::string::npos, implementationCode.find("algebraicVariables[9] = !(voi/constants[0]);\n"));
}

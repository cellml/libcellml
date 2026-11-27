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

TEST(GeneratorLeadingPlusSign, numbersWithALeadingPlusSign)
{
    // CellML 2.0 section 1.3.3.2: a real number string may begin with a '+' sign. The sign is not
    // needed in the generated code and, in C, "voi + +2.0" written as "voi++2.0" doesn't compile.
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("generator/leading_plus_sign/model.cellml"));

    EXPECT_NE(nullptr, model);

    auto analyser = libcellml::Analyser::create();

    analyser->analyseModel(model);

    EXPECT_EQ(size_t(0), analyser->issueCount());

    auto generator = libcellml::Generator::create();
    auto implementationCode = generator->implementationCode(analyser->analyserModel());

    EXPECT_NE(std::string::npos, implementationCode.find("states[0] = 2.0;\n"));
    EXPECT_NE(std::string::npos, implementationCode.find("constants[0] = 1.5;\n"));
    EXPECT_NE(std::string::npos, implementationCode.find("computedConstants[0] = -2.0;\n"));
    EXPECT_NE(std::string::npos, implementationCode.find("algebraicVariables[0] = voi+2.0;\n"));
    EXPECT_NE(std::string::npos, implementationCode.find("algebraicVariables[1] = voi-2.0;\n"));
    EXPECT_NE(std::string::npos, implementationCode.find("algebraicVariables[2] = voi+1.5e+3;\n"));
    EXPECT_NE(std::string::npos, implementationCode.find("algebraicVariables[3] = constants[0]+voi;\n"));
}

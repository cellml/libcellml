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

#include "test_resources.h"

#include "gtest/gtest.h"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <libcellml>
#include <sstream>
#include <vector>

TEST(ResolveImports, resolveSineModelFromFile) {
    std::ifstream t(TestResources::getLocation(
                    TestResources::CELLML_SINE_MODEL_RESOURCE));

    std::stringstream buffer;
    buffer << t.rdbuf();

    libcellml::Parser p;
    libcellml::ModelPtr model = p.parseModel(buffer.str());

    EXPECT_EQ(0u, p.errorCount());
    EXPECT_FALSE(model->hasUnresolvedImports());
}

TEST(ResolveImports, resolveSineImportsModelFromFile) {
    const std::string modelLocation = TestResources::getLocation(
                TestResources::CELLML_SINE_IMPORTS_MODEL_RESOURCE);
    std::ifstream t(modelLocation);
    std::stringstream buffer;
    buffer << t.rdbuf();

    libcellml::Parser p;
    libcellml::ModelPtr model = p.parseModel(buffer.str());
    EXPECT_EQ(0u, p.errorCount());

    EXPECT_TRUE(model->hasUnresolvedImports());
    model->resolveImports(modelLocation);
    EXPECT_FALSE(model->hasUnresolvedImports());
}

TEST(ResolveImports, resolveComplexImportsModelFromFile) {
    const std::string modelLocation = TestResources::getLocation(
                TestResources::CELLML_COMPLEX_IMPORTS_MODEL_RESOURCE);
    std::ifstream t(modelLocation);
    std::stringstream buffer;
    buffer << t.rdbuf();

    libcellml::Parser p;
    libcellml::ModelPtr model = p.parseModel(buffer.str());
    EXPECT_EQ(0u, p.errorCount());

    EXPECT_TRUE(model->hasUnresolvedImports());
    model->resolveImports(modelLocation);
    EXPECT_FALSE(model->hasUnresolvedImports());
}

TEST(ResolveImports, resolveUnitsImportFromFile) {
    const std::string modelLocation = TestResources::getLocation(
                TestResources::CELLML_UNITS_IMPORT_MODEL_RESOURCE);
    std::ifstream t(modelLocation);
    std::stringstream buffer;
    buffer << t.rdbuf();

    libcellml::Parser p;
    libcellml::ModelPtr model = p.parseModel(buffer.str());

    EXPECT_EQ(0u, p.errorCount());

    EXPECT_TRUE(model->hasUnresolvedImports());
    model->resolveImports(modelLocation);
    EXPECT_FALSE(model->hasUnresolvedImports());
}

TEST(ResolveImports, resolveImportsFromFileLevel0) {
    const std::string modelLocation = TestResources::getLocation(
                TestResources::CELLML_IMPORT_LEVEL0_MODEL_RESOURCE);
    std::ifstream t(modelLocation);
    std::stringstream buffer;
    buffer << t.rdbuf();

    libcellml::Parser p;
    libcellml::ModelPtr model = p.parseModel(buffer.str());

    EXPECT_EQ(0u, p.errorCount());

    EXPECT_TRUE(model->hasUnresolvedImports());
    model->resolveImports(modelLocation);
    EXPECT_FALSE(model->hasUnresolvedImports());
}

TEST(ResolveImports, resolveImportsFromFileLevel0Unresolvable) {
    const std::string modelLocation = TestResources::getLocation(
                TestResources::CELLML_IMPORT_LEVEL0_UNRESOLVABLE_MODEL_RESOURCE);
    std::ifstream t(modelLocation);
    std::stringstream buffer;
    buffer << t.rdbuf();

    libcellml::Parser p;
    libcellml::ModelPtr model = p.parseModel(buffer.str());

    EXPECT_EQ(0u, p.errorCount());

    EXPECT_TRUE(model->hasUnresolvedImports());
    model->resolveImports(modelLocation);
    EXPECT_TRUE(model->hasUnresolvedImports());
}

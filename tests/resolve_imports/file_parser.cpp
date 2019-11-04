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
#include "test_utils.h"

#include "gtest/gtest.h"

#include <algorithm>
#include <fstream>
#include <libcellml>
#include <sstream>
#include <vector>

TEST(ResolveImports, resolveSineModelFromFile)
{
    libcellml::Parser p;
    libcellml::ModelPtr model = p.parseModel(fileContents("sine_approximations.xml"));

    EXPECT_EQ(size_t(0), p.errorCount());
    EXPECT_FALSE(model->hasUnresolvedImports());
}

TEST(ResolveImports, resolveSineImportsModelFromFile)
{
    libcellml::Parser p;
    libcellml::ModelPtr model = p.parseModel(fileContents("sine_approximations_import.xml"));
    EXPECT_EQ(size_t(0), p.errorCount());

    EXPECT_TRUE(model->hasUnresolvedImports());
    model->resolveImports(resourcePath());
    EXPECT_FALSE(model->hasUnresolvedImports());
}

TEST(ResolveImports, resolveComplexImportsModelFromFile)
{
    libcellml::Parser p;
    libcellml::ModelPtr model = p.parseModel(fileContents("complex_imports.xml"));
    EXPECT_EQ(size_t(0), p.errorCount());

    EXPECT_TRUE(model->hasUnresolvedImports());
    model->resolveImports(resourcePath());
    EXPECT_FALSE(model->hasUnresolvedImports());
}

TEST(ResolveImports, resolveUnitsImportFromFile)
{
    libcellml::Parser p;
    libcellml::ModelPtr model = p.parseModel(fileContents("import_units_model.cellml"));

    EXPECT_EQ(size_t(0), p.errorCount());

    EXPECT_TRUE(model->hasUnresolvedImports());
    model->resolveImports(resourcePath());
    EXPECT_FALSE(model->hasUnresolvedImports());
}

TEST(ResolveImports, resolveImportsFromFileLevel0)
{
    libcellml::Parser p;
    libcellml::ModelPtr model = p.parseModel(fileContents("level0.xml"));

    EXPECT_EQ(size_t(0), p.errorCount());

    EXPECT_TRUE(model->hasUnresolvedImports());
    model->resolveImports(resourcePath());
    EXPECT_FALSE(model->hasUnresolvedImports());
}

TEST(ResolveImports, resolveImportsFromFileLevel0Unresolvable)
{
    libcellml::Parser p;
    libcellml::ModelPtr model = p.parseModel(fileContents("level0-broken-imports.xml"));

    EXPECT_EQ(size_t(0), p.errorCount());

    EXPECT_TRUE(model->hasUnresolvedImports());
    model->resolveImports(resourcePath());
    EXPECT_TRUE(model->hasUnresolvedImports());
}

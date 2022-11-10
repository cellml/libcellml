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

TEST(ImporterStrict, sineCellml11Import)
{
    libcellml::ParserPtr parser = libcellml::Parser::create(false);
    libcellml::ImporterPtr importer = libcellml::Importer::create(false);
    auto model = parser->parseModel(fileContents("cellml1X/sin_approximations_import.xml"));

    EXPECT_EQ(size_t(3), parser->issueCount());
    EXPECT_TRUE(model->hasUnresolvedImports());
    importer->resolveImports(model, resourcePath("cellml1X"));
    EXPECT_EQ(size_t(3), importer->issueCount());
    EXPECT_FALSE(model->hasUnresolvedImports());
}

TEST(ImporterStrict, sineCellml11ImportInStrictMode)
{
    libcellml::ParserPtr parser = libcellml::Parser::create(false);
    libcellml::ImporterPtr importer = libcellml::Importer::create();
    auto model = parser->parseModel(fileContents("cellml1X/sin_approximations_import.xml"));

    EXPECT_EQ(size_t(3), parser->issueCount());
    EXPECT_TRUE(model->hasUnresolvedImports());
    importer->resolveImports(model, resourcePath("cellml1X"));
    EXPECT_EQ(size_t(3), importer->issueCount());
    EXPECT_TRUE(model->hasUnresolvedImports());
}

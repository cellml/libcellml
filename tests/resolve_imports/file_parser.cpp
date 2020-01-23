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

#include <libcellml>

#include <algorithm>
#include <fstream>
#include <sstream>
#include <vector>

TEST(ResolveImports, resolveSineModelFromFile)
{
    libcellml::ParserPtr p = libcellml::Parser::create();
    libcellml::ModelPtr model = p->parseModel(fileContents("sine_approximations.xml"));

    EXPECT_EQ(size_t(0), p->errorCount());
    EXPECT_FALSE(model->hasUnresolvedImports());
}

TEST(ResolveImports, resolveSineImportsModelFromFile)
{
    libcellml::ParserPtr p = libcellml::Parser::create();
    libcellml::ModelPtr model = p->parseModel(fileContents("sine_approximations_import.xml"));
    EXPECT_EQ(size_t(0), p->errorCount());

    EXPECT_TRUE(model->hasUnresolvedImports());
    model->resolveImports(resourcePath());
    EXPECT_FALSE(model->hasUnresolvedImports());
}

TEST(ResolveImports, resolveComplexImportsModelFromFile)
{
    libcellml::ParserPtr p = libcellml::Parser::create();
    libcellml::ModelPtr model = p->parseModel(fileContents("complex_imports.xml"));
    EXPECT_EQ(size_t(0), p->errorCount());

    EXPECT_TRUE(model->hasUnresolvedImports());
    model->resolveImports(resourcePath());
    EXPECT_FALSE(model->hasUnresolvedImports());
}

TEST(ResolveImports, resolveUnitsImportFromFile)
{
    libcellml::ParserPtr p = libcellml::Parser::create();
    libcellml::ModelPtr model = p->parseModel(fileContents("import_units_model.cellml"));

    EXPECT_EQ(size_t(0), p->errorCount());

    EXPECT_TRUE(model->hasUnresolvedImports());
    model->resolveImports(resourcePath());
    EXPECT_FALSE(model->hasUnresolvedImports());
}

TEST(ResolveImports, noWarningForkedImport)
{
    libcellml::ParserPtr p = libcellml::Parser::create();
    libcellml::ModelPtr model = p->parseModel(fileContents("circularimports/forkedImport.cellml"));

    EXPECT_EQ(size_t(0), p->errorCount());

    EXPECT_TRUE(model->hasUnresolvedImports());
    model->resolveImports(resourcePath("circularimports/"));
    printIssues(model);
    EXPECT_FALSE(model->hasUnresolvedImports());
}

TEST(ResolveImports, noWarningDiamondImport)
{
    libcellml::ParserPtr p = libcellml::Parser::create();
    libcellml::ModelPtr model = p->parseModel(fileContents("circularimports/diamond.cellml"));

    EXPECT_EQ(size_t(0), p->errorCount());

    EXPECT_TRUE(model->hasUnresolvedImports());
    model->resolveImports(resourcePath("circularimports/"));
    printIssues(model);
    EXPECT_FALSE(model->hasUnresolvedImports());
}

TEST(ResolveImports, warningCircularImportReferences)
{
    std::string warningMessage = "Cyclic dependencies were found when attempting to resolve components. The dependency loop is:\n"
                                 "    component 'i_am_cyclic' imports 'c2' from 'circularImport_2.cellml',\n"
                                 "    component 'c2' imports 'c3' from 'circularImport_3.cellml',\n"
                                 "    component 'c3' imports 'i_am_cyclic' from 'circularImport_1.cellml',\n"
                                 "    component 'i_am_cyclic' imports 'c2' from 'circularImport_2.cellml'.";
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("circularimports/circularImport_1.cellml"));

    model->resolveImports(resourcePath("circularimports/"));
    printIssues(model);
    EXPECT_EQ(size_t(1), model->issueCount());
    EXPECT_EQ(size_t(1), model->warningCount());
    EXPECT_EQ(warningMessage, model->warning(0)->description());
}

TEST(ResolveImports, resolveImportsFromFileLevel0)
{
    libcellml::ParserPtr p = libcellml::Parser::create();
    libcellml::ModelPtr model = p->parseModel(fileContents("level0.xml"));

    EXPECT_EQ(size_t(0), p->errorCount());

    EXPECT_TRUE(model->hasUnresolvedImports());
    model->resolveImports(resourcePath());
    EXPECT_FALSE(model->hasUnresolvedImports());
}

TEST(ResolveImports, resolveImportsFromFileLevel0Unresolvable)
{
    libcellml::ParserPtr p = libcellml::Parser::create();
    libcellml::ModelPtr model = p->parseModel(fileContents("level0-broken-imports.xml"));

    EXPECT_EQ(size_t(0), p->errorCount());

    EXPECT_TRUE(model->hasUnresolvedImports());
    model->resolveImports(resourcePath());
    EXPECT_TRUE(model->hasUnresolvedImports());
}

TEST(ResolveImports, componentNotInResolvingModel)
{
    const std::string modelImportingComponent =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/2.0#\" xmlns:cellml=\"http://www.cellml.org/cellml/2.0#\" xmlns:xlink=\"http://www.w3.org/1999/xlink\" name=\"sin_approximations_import\" id=\"sin_approximations_import\">\n"
        "  <import xlink:href=\"level0.xml\">\n"
        "    <component name=\"real_component\" component_ref=\"this_name_not_a_component_in_level0_model\"/>\n"
        "  </import>\n"
        "  <component name=\"main\" id=\"main\"/>\n"
        "  <encapsulation>\n"
        "    <component_ref component=\"main\">\n"
        "      <component_ref component=\"real_component\"/>\n"
        "    </component_ref>\n"
        "  </encapsulation>\n"
        "</model>\n";

    libcellml::ParserPtr p = libcellml::Parser::create();
    libcellml::ModelPtr model = p->parseModel(modelImportingComponent);

    EXPECT_EQ(size_t(0), p->errorCount());

    EXPECT_TRUE(model->hasUnresolvedImports());
    model->resolveImports(resourcePath());
    EXPECT_TRUE(model->hasUnresolvedImports());
}

// *** KRM Adding tests for warning-type issues here

// TEST(ResolveImports, warningCircularImportReferences)
// {
//     auto parser = libcellml::Parser::create();
//     auto validator = libcellml::Validator::create();
//     auto model1 = parser->parseModel(fileContents("circularimports/circularImport_1.cellml"));

//     model1->resolveImports(resourcePath("circularimports/"));

//     validator->validateModel(model1);
//     printIssues(validator);

//     EXPECT_EQ(size_t(1), validator->issueCount());
// }

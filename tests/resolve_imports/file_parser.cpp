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

    EXPECT_EQ(size_t(0), p->issueCount());
    EXPECT_FALSE(model->hasUnresolvedImports());
}

TEST(ResolveImports, resolveSineImportsModelFromFile)
{
    libcellml::ParserPtr p = libcellml::Parser::create();
    libcellml::ImporterPtr importer = libcellml::Importer::create();
    libcellml::ModelPtr model = p->parseModel(fileContents("sine_approximations_import.xml"));
    EXPECT_EQ(size_t(0), p->issueCount());

    EXPECT_TRUE(model->hasUnresolvedImports());
    importer->resolveImports(resourcePath(), model);
    EXPECT_FALSE(model->hasUnresolvedImports());
}

TEST(ResolveImports, resolveComplexImportsModelFromFile)
{
    libcellml::ParserPtr p = libcellml::Parser::create();
    libcellml::ImporterPtr importer = libcellml::Importer::create();
    libcellml::ModelPtr model = p->parseModel(fileContents("complex_imports.xml"));
    EXPECT_EQ(size_t(0), p->issueCount());

    EXPECT_TRUE(model->hasUnresolvedImports());
    importer->resolveImports(resourcePath(), model);
    EXPECT_FALSE(model->hasUnresolvedImports());
}

TEST(ResolveImports, resolveUnitsImportFromFile)
{
    libcellml::ParserPtr p = libcellml::Parser::create();
    libcellml::ImporterPtr importer = libcellml::Importer::create();
    libcellml::ModelPtr model = p->parseModel(fileContents("import_units_model.cellml"));

    EXPECT_EQ(size_t(0), p->issueCount());

    EXPECT_TRUE(model->hasUnresolvedImports());
    importer->resolveImports(resourcePath(), model);
    EXPECT_FALSE(model->hasUnresolvedImports());
}

TEST(ResolveImports, resolveImportsFromFileLevel0)
{
    libcellml::ParserPtr p = libcellml::Parser::create();
    libcellml::ImporterPtr importer = libcellml::Importer::create();
    libcellml::ModelPtr model = p->parseModel(fileContents("level0.xml"));

    EXPECT_EQ(size_t(0), p->issueCount());

    EXPECT_TRUE(model->hasUnresolvedImports());
    importer->resolveImports(resourcePath(), model);
    EXPECT_FALSE(model->hasUnresolvedImports());
}

TEST(ResolveImports, resolveImportsFromFileLevel0Unresolvable)
{
    libcellml::ParserPtr p = libcellml::Parser::create();
    libcellml::ImporterPtr importer = libcellml::Importer::create();
    libcellml::ModelPtr model = p->parseModel(fileContents("level0-broken-imports.xml"));

    EXPECT_EQ(size_t(0), p->issueCount());

    EXPECT_TRUE(model->hasUnresolvedImports());
    importer->resolveImports(resourcePath(), model);
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
    libcellml::ImporterPtr importer = libcellml::Importer::create();
    libcellml::ModelPtr model = p->parseModel(modelImportingComponent);

    EXPECT_EQ(size_t(0), p->issueCount());

    EXPECT_TRUE(model->hasUnresolvedImports());
    importer->resolveImports(resourcePath(), model);
    EXPECT_TRUE(model->hasUnresolvedImports());
}

TEST(ResolveImports, noWarningForkedImport)
{
    libcellml::ParserPtr p = libcellml::Parser::create();
    libcellml::ImporterPtr importer = libcellml::Importer::create();
    libcellml::ModelPtr model = p->parseModel(fileContents("resolveimports/forkedImport.cellml"));

    EXPECT_EQ(size_t(0), p->errorCount());

    EXPECT_TRUE(model->hasUnresolvedImports());
    importer->resolveImports(resourcePath("resolveimports/"), model);
    printIssues(importer);
    EXPECT_FALSE(model->hasUnresolvedImports());
}

TEST(ResolveImports, noWarningDiamondImport)
{
    libcellml::ParserPtr p = libcellml::Parser::create();
    libcellml::ImporterPtr importer = libcellml::Importer::create();
    libcellml::ModelPtr model = p->parseModel(fileContents("resolveimports/diamond.cellml"));

    EXPECT_EQ(size_t(0), p->errorCount());

    EXPECT_TRUE(model->hasUnresolvedImports());
    importer->resolveImports(resourcePath("resolveimports/"), model);
    printIssues(importer);
    EXPECT_FALSE(model->hasUnresolvedImports());
}

TEST(ResolveImports, warningCircularImportReferencesComponent)
{
    std::string warningMessage = "Cyclic dependencies were found when attempting to resolve components in model 'circularImport1'. The dependency loop is:\n"
                                 "    component 'i_am_cyclic' imports 'c2' from 'circularImport_2.cellml',\n"
                                 "    component 'c2' imports 'c3' from 'circularImport_3.cellml',\n"
                                 "    component 'c3' imports 'i_am_cyclic' from 'circularImport_1.cellml',\n"
                                 "    component 'i_am_cyclic' imports 'c2' from 'circularImport_2.cellml'.";
    auto parser = libcellml::Parser::create();
    auto importer = libcellml::Importer::create();
    auto model = parser->parseModel(fileContents("resolveimports/circularImport_1.cellml"));
    EXPECT_EQ(size_t(0), parser->issueCount());
    importer->resolveImports(resourcePath("resolveimports/"), model);

    EXPECT_EQ(size_t(1), importer->issueCount());
    EXPECT_EQ(size_t(1), importer->warningCount());
    EXPECT_EQ(warningMessage, importer->warning(0)->description());
}

TEST(ResolveImports, warningCircularImportReferencesUnits)
{
    std::string warningMessage = "Cyclic dependencies were found when attempting to resolve units in model 'circularImport1'. The dependency loop is:\n"
                                 "    units 'i_am_cyclic' imports 'u2' from 'circularUnits_2.cellml',\n"
                                 "    units 'u2' imports 'u3' from 'circularUnits_3.cellml',\n"
                                 "    units 'u3' imports 'i_am_cyclic' from 'circularUnits_1.cellml',\n"
                                 "    units 'i_am_cyclic' imports 'u2' from 'circularUnits_2.cellml'.";
    auto parser = libcellml::Parser::create();
    auto importer = libcellml::Importer::create();
    auto model = parser->parseModel(fileContents("resolveimports/circularUnits_1.cellml"));
    EXPECT_EQ(size_t(0), parser->issueCount());
    importer->resolveImports(resourcePath("resolveimports/"), model);
    EXPECT_EQ(size_t(1), importer->issueCount());
    EXPECT_EQ(size_t(1), importer->warningCount());
    EXPECT_EQ(warningMessage, importer->warning(0)->description());
}

TEST(ResolveImports, warningUnrequiredCircularDependencyComponent)
{
    // This test in intended to show what happens when one model attempts to import a concrete component from a
    // second model, where the second model has unrelated circular dependencies:
    //   - model1 imports component1 from model2
    //   - model2 defines component1
    //   - model2 also defines a circular dependency unrelated to component1

    std::string warningMessage = "Cyclic dependencies were found when attempting to resolve components in model 'circularImport1'. The dependency loop is:\n"
                                 "    component 'c' imports 'i_am_ok_but_my_sibling_is_cyclic' from 'circularImport_1.cellml',\n"
                                 "    component 'i_am_cyclic' imports 'c2' from 'circularImport_2.cellml',\n"
                                 "    component 'c2' imports 'c3' from 'circularImport_3.cellml',\n"
                                 "    component 'c3' imports 'i_am_cyclic' from 'circularImport_1.cellml',\n"
                                 "    component 'i_am_cyclic' imports 'c2' from 'circularImport_2.cellml'.";

    auto parser = libcellml::Parser::create();
    auto importer = libcellml::Importer::create();
    auto model = parser->parseModel(fileContents("resolveimports/master1.cellml"));
    EXPECT_EQ(size_t(0), parser->issueCount());
    importer->resolveImports(resourcePath("resolveimports/"), model);
    EXPECT_EQ(size_t(1), importer->issueCount());
    EXPECT_EQ(size_t(1), importer->warningCount());
    EXPECT_EQ(warningMessage, importer->warning(0)->description());
}

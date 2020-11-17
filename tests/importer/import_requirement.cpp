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

TEST(ImportRequirement, create)
{
    auto model = libcellml::Model::create("model");
    auto url = "this.is.a.url";
    auto ir = libcellml::ImportRequirement::create(url, model);
    EXPECT_NE(nullptr, ir);
    EXPECT_EQ(url, ir->url());
    EXPECT_EQ(model, ir->model());
}

TEST(ImportRequirement, nullModel)
{
    libcellml::ModelPtr nullModel;
    auto ir = libcellml::ImportRequirement::create("null-model-url", nullModel);
    EXPECT_EQ(nullptr, ir->model());
}

TEST(ImportRequirement, requirementsFixCircularRef)
{
    std::vector<std::string> expectedKeys = {
        "importExample2units.cellml",
        "importExample3.cellml",
        "importExample2components.cellml"};

    std::string e1 = "The model has unresolved imports.  Please resolve the imports before calling for a requirements list.";
    std::string e2 = "Cyclic dependencies were found when attempting to resolve components in model 'circularImport1'. The dependency loop is:\n - component 'myUnits' is imported from 'importedUnits' in 'importExample2units.cellml';\n - component 'importedUnits' is imported from 'myUnits' in 'importExample3.cellml';\n - component 'myComponent' is imported from 'importedComponent' in 'importExample2components.cellml';\n - component 'importedComponent' is imported from 'myComponent' in 'importExample3.cellml';\n - component 'circular' is imported from 'circular1' in 'circularImport1.cellml';\n - component 'circular1' is imported from 'circular2' in 'circularImport2.cellml';\n - component 'circular2' is imported from 'circular1' in 'circularImport1.cellml'; and\n - component 'circular1' is imported from 'circular2' in 'circularImport2.cellml'.";

    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("importer/requirements/importExample1.cellml"));
    auto importer = libcellml::Importer::create();

    // Pass model to the importer for requirements list before the imports are resolved,
    // expect empty set returned.
    EXPECT_EQ(size_t(0), importer->requirements(model).size());
    EXPECT_EQ(size_t(1), importer->issueCount());
    EXPECT_EQ(e1, importer->issue(0)->description());

    // Resolve imports and repeat, expect circular reference warning.
    importer->removeAllIssues();
    importer->resolveImports(model, resourcePath("importer/requirements/"));
    EXPECT_EQ(size_t(1), importer->issueCount());
    EXPECT_EQ(e2, importer->issue(0)->description());

    // Fix circular reference by removing component which calls it.
    model->removeComponent("circular");
    importer->removeAllIssues();
    importer->resolveImports(model, resourcePath("importer/requirements/"));
    EXPECT_EQ(size_t(0), importer->issueCount());

    // Get requirements, and expect that it's not including the unneeded circular ones now.
    auto requirements = importer->requirements(model);
    EXPECT_EQ(size_t(3), requirements.size());
    EXPECT_EQ(size_t(5), importer->libraryCount());

    size_t i = 0;
    for (auto &r : requirements) {
        EXPECT_EQ(expectedKeys[i], r->url());
        EXPECT_EQ(importer->library(resourcePath("importer/requirements/" + expectedKeys[i])), r->model());
        i++;
    }
}

TEST(ImportRequirement, requirementsEncapsulationUnitsWithChildren)
{
    std::vector<std::string> expectedKeys = {
        "complicatedComponents.cellml",
        "components.cellml",
        "complicatedUnits.cellml",
        "units1.cellml",
        "units2.cellml"};

    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("importer/requirements/complicatedExample.cellml"));
    EXPECT_EQ(size_t(0), parser->issueCount());

    auto importer = libcellml::Importer::create();
    importer->resolveImports(model, resourcePath("importer/requirements/"));
    EXPECT_EQ(size_t(0), importer->issueCount());

    auto requirements = importer->requirements(model);
    EXPECT_EQ(expectedKeys.size(), requirements.size());

    size_t i = 0;
    for (auto &r : requirements) {
        EXPECT_EQ(expectedKeys.at(i), r->url());
        EXPECT_EQ(importer->library(resourcePath("importer/requirements/" + expectedKeys[i])), r->model());
        i++;
    }
}

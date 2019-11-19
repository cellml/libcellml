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

TEST(ModelFlattening, flattenSingleLevelComponentImport)
{
    const std::string e =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/2.0#\" name=\"sin_approximations_import__flattened\">\n"
        "  <component name=\"main\"/>\n"
        "  <component name=\"actual_sin_flattened\"/>\n"
        "  <component name=\"deriv_approx_sin_flattened\"/>\n"
        "  <component name=\"parabolic_approx_sin_flattened\"/>\n"
        "  <encapsulation>\n"
        "    <component_ref component=\"main\">\n"
        "      <component_ref component=\"actual_sin_flattened\"/>\n"
        "      <component_ref component=\"deriv_approx_sin_flattened\"/>\n"
        "      <component_ref component=\"parabolic_approx_sin_flattened\"/>\n"
        "    </component_ref>\n"
        "  </encapsulation>\n"
        "</model>\n";

    libcellml::Parser p;
    libcellml::ModelPtr model = p.parseModel(fileContents("sine_approximations_import.xml"));
    EXPECT_EQ(size_t(0), p.errorCount());
    libcellml::Printer printer;
    std::string s = printer.printModel(model);
    debug("Source model:");
    debug(s);

    EXPECT_TRUE(model->hasUnresolvedImports());
    model->resolveImports(resourcePath());
    EXPECT_FALSE(model->hasUnresolvedImports());
    libcellml::ModelPtr flattenedModel = libcellml::Model::flatCopy(model);
    s = printer.printModel(flattenedModel);
    debug("Flat model:");
    debug(s);
    EXPECT_EQ(e, s);
}

#if 0
TEST(ResolveImports, flattenComplexImports)
{
    libcellml::Parser p;
    libcellml::ModelPtr model = p.parseModel(fileContents("complex_imports.xml"));
    EXPECT_EQ(size_t(0), p.errorCount());

    EXPECT_TRUE(model->hasUnresolvedImports());
    model->resolveImports(resourcePath());
    EXPECT_FALSE(model->hasUnresolvedImports());
    libcellml::
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
    l
        
        
        
        ibcellml::ModelPtr model = p.parseModel(fileContents("level0-broken-imports.xml"));

    EXPECT_EQ(size_t(0), p.errorCount());

    EXPECT_TRUE(model->hasUnresolvedImports());
    model->resolveImports(resourcePath());
    EXPECT_TRUE(model->hasUnresolvedImports());
}
#endif
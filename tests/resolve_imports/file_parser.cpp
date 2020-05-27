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
    libcellml::ModelPtr model = p->parseModel(fileContents("sine_approximations_import.xml"));
    EXPECT_EQ(size_t(0), p->issueCount());

    EXPECT_TRUE(model->hasUnresolvedImports());
    model->resolveImports(resourcePath());
    EXPECT_FALSE(model->hasUnresolvedImports());
}

TEST(ResolveImports, resolveComplexImportsModelFromFile)
{
    libcellml::ParserPtr p = libcellml::Parser::create();
    libcellml::ModelPtr model = p->parseModel(fileContents("complex_imports.xml"));
    EXPECT_EQ(size_t(0), p->issueCount());

    EXPECT_TRUE(model->hasUnresolvedImports());
    model->resolveImports(resourcePath());
    EXPECT_FALSE(model->hasUnresolvedImports());
}

TEST(ResolveImports, resolveUnitsImportFromFile)
{
    libcellml::ParserPtr p = libcellml::Parser::create();
    libcellml::ModelPtr model = p->parseModel(fileContents("import_units_model.cellml"));

    EXPECT_EQ(size_t(0), p->issueCount());

    EXPECT_TRUE(model->hasUnresolvedImports());
    model->resolveImports(resourcePath());
    EXPECT_FALSE(model->hasUnresolvedImports());
}

TEST(ResolveImports, resolveImportsFromFileLevel0)
{
    libcellml::ParserPtr p = libcellml::Parser::create();
    libcellml::ModelPtr model = p->parseModel(fileContents("level0.xml"));

    EXPECT_EQ(size_t(0), p->issueCount());

    EXPECT_TRUE(model->hasUnresolvedImports());
    model->resolveImports(resourcePath());
    EXPECT_FALSE(model->hasUnresolvedImports());
}

TEST(ResolveImports, resolveImportsFromFileLevel0Unresolvable)
{
    libcellml::ParserPtr p = libcellml::Parser::create();
    libcellml::ModelPtr model = p->parseModel(fileContents("level0-broken-imports.xml"));

    EXPECT_EQ(size_t(0), p->issueCount());

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

    EXPECT_EQ(size_t(0), p->issueCount());

    EXPECT_TRUE(model->hasUnresolvedImports());
    model->resolveImports(resourcePath());
    EXPECT_TRUE(model->hasUnresolvedImports());
}

TEST(ResolveImports, circularImportReferencesUnits)
{
    /*
    ---------------- circularUnits_1.cellml -----------------------

    <?xml version="1.0" encoding="UTF-8"?>
    <model xmlns="http://www.cellml.org/cellml/2.0#"
    	xmlns:cellml="http://www.cellml.org/cellml/2.0#"
    	xmlns:xlink="http://www.w3.org/1999/xlink" name="circularImport1">
    	<import xlink:href="circularUnits_2.cellml">
    		<units name="i_am_cyclic" units_ref="u2" />
    	</import>
    </model>

    ---------------- circularUnits_2.cellml -----------------------

    <?xml version="1.0" encoding="UTF-8"?>
    <model xmlns="http://www.cellml.org/cellml/2.0#"
    	xmlns:cellml="http://www.cellml.org/cellml/2.0#"
    	xmlns:xlink="http://www.w3.org/1999/xlink" name="circularImport2">
    	<import xlink:href="circularUnits_3.cellml">
    		<units name="u2" units_ref="u3" />
    	</import>
    </model>

    ---------------- circularUnits_3.cellml -----------------------

    <?xml version="1.0" encoding="UTF-8"?>
    <model xmlns="http://www.cellml.org/cellml/2.0#"
    	xmlns:cellml="http://www.cellml.org/cellml/2.0#"
    	xmlns:xlink="http://www.w3.org/1999/xlink" name="circularImport3">
    	<import xlink:href="circularUnits_1.cellml">
    		<units name="u3" units_ref="i_am_cyclic" />
    	</import>
    </model>
    */

    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("resolveimports/circularUnits_1.cellml"));
    EXPECT_EQ(size_t(0), parser->errorCount());
    EXPECT_TRUE(model->hasUnresolvedImports());
    model->resolveImports(resourcePath("resolveimports/")); // goes bananas until it reaches the recursion depth ...
    EXPECT_FALSE(model->hasUnresolvedImports());
    model->flatten(); // segfaults
}

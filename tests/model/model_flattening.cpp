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

#include "gtest/gtest.h"

#include <libcellml>

#include "test_utils.h"

TEST(ModelFlattening, importedUnits)
{
    const std::string unitsDefiniitonModel =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/2.0#\" xmlns:cellml=\"http://www.cellml.org/cellml/2.0#\" xmlns:xlink=\"http://www.w3.org/1999/xlink\" name=\"units\">\n"
        "  <units name=\"ms\">\n"
        "    <unit units=\"second\" prefix=\"milli\"/>\n"
        "  </units>\n"
        "</model>\n";

    const std::string modelImportingUnits =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model name=\"importer_of_units\" xmlns=\"http://www.cellml.org/cellml/2.0#\">\n"
        "  <import xlink:href=\"unitsdefinitions.xml\" xmlns:xlink=\"http://www.w3.org/1999/xlink\">\n"
        "    <units units_ref=\"ms\" name=\"my_ms\"/>\n"
        "  </import>\n"
        "</model>\n";

    const std::string e =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/2.0#\" name=\"importer_of_units\">\n"
        "  <units name=\"my_ms\">\n"
        "    <unit prefix=\"milli\" units=\"second\"/>\n"
        "  </units>\n"
        "</model>\n";

    auto parser = libcellml::Parser::create();

    auto modelWithUnitsImports = parser->parseModel(modelImportingUnits);
    auto modelUnitsDefinitions = parser->parseModel(unitsDefiniitonModel);

    EXPECT_TRUE(modelWithUnitsImports->hasUnresolvedImports());

    auto units = modelWithUnitsImports->units(0);
    auto importSource = units->importSource();
    importSource->setModel(modelUnitsDefinitions);

    EXPECT_FALSE(modelWithUnitsImports->hasUnresolvedImports());

    modelWithUnitsImports->flatten();

    auto printer = libcellml::Printer::create();

    auto a = printer->printModel(modelWithUnitsImports);
    EXPECT_EQ(e, a);
}

TEST(ModelFlattening, importedComponent)
{
    const std::string sineDefinitionModel =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/2.0#\" xmlns:cellml=\"http://www.cellml.org/cellml/2.0#\" xmlns:xlink=\"http://www.w3.org/1999/xlink\" name=\"sin\" id=\"sin\">\n"
        "  <component name=\"sin\" id=\"sin\">\n"
        "    <variable name=\"x\" units=\"dimensionless\" interface=\"public_and_private\"/>\n"
        "    <variable id=\"sin\" units=\"dimensionless\" name=\"sin\" interface=\"public_and_private\"/>\n"
        "    <math xmlns=\"http://www.w3.org/1998/Math/MathML\">\n"
        "  <apply id=\"actual_sin\"><eq/>\n"
        "    <ci>sin</ci>\n"
        "    <apply><sin/>\n"
        "      <ci>x</ci>\n"
        "    </apply>\n"
        "  </apply>\n"
        "</math>\n"
        "  </component>\n"
        "</model>\n";

    const std::string modelImportingComponent =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/2.0#\" xmlns:cellml=\"http://www.cellml.org/cellml/2.0#\" xmlns:xlink=\"http://www.w3.org/1999/xlink\" name=\"sin_approximations_import\" id=\"sin_approximations_import\">\n"
        "  <import xlink:href=\"sin.xml\">\n"
        "    <component name=\"actual_sin\" component_ref=\"sin\"/>\n"
        "  </import>\n"
        "  <component name=\"main\" id=\"main\"/>\n"
        "  <encapsulation>\n"
        "    <component_ref component=\"main\">\n"
        "      <component_ref component=\"actual_sin\"/>\n"
        "    </component_ref>\n"
        "  </encapsulation>\n"
        "</model>\n";

    const std::string e =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/2.0#\" name=\"sin_approximations_import\" id=\"sin_approximations_import\">\n"
        "  <component name=\"main\" id=\"main\"/>\n"
        "  <component name=\"actual_sin\" id=\"sin\">\n"
        "    <variable name=\"x\" units=\"dimensionless\" interface=\"public_and_private\"/>\n"
        "    <variable name=\"sin\" units=\"dimensionless\" interface=\"public_and_private\" id=\"sin\"/>\n"
        "    <math xmlns=\"http://www.w3.org/1998/Math/MathML\">\n"
        "      <apply id=\"actual_sin\"><eq/>\n"
        "        <ci>sin</ci>\n"
        "        <apply><sin/>\n"
        "          <ci>x</ci>\n"
        "        </apply>\n"
        "      </apply>\n"
        "    </math>\n"
        "  </component>\n"
        "  <encapsulation>\n"
        "    <component_ref component=\"main\">\n"
        "      <component_ref component=\"actual_sin\"/>\n"
        "    </component_ref>\n"
        "  </encapsulation>\n"
        "</model>\n";

    auto parser = libcellml::Parser::create();

    auto modelWithComponentImport = parser->parseModel(modelImportingComponent);
    auto modelSineDefinition = parser->parseModel(sineDefinitionModel);

    EXPECT_TRUE(modelWithComponentImport->hasUnresolvedImports());

    auto component = modelWithComponentImport->component(0)->component(0);
    auto importSource = component->importSource();
    importSource->setModel(modelSineDefinition);

    EXPECT_TRUE(component->isImport());
    EXPECT_FALSE(modelWithComponentImport->hasUnresolvedImports());

    modelWithComponentImport->flatten();

    auto printer = libcellml::Printer::create();

    auto a = printer->printModel(modelWithComponentImport);
    EXPECT_EQ(e, a);
}

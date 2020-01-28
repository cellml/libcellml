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

#if 0
TEST(ModelFlattening, modelWithoutImports)
{
    const std::string e =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/2.0#\" name=\"units\">\n"
        "  <units name=\"ms\">\n"
        "    <unit prefix=\"milli\" units=\"second\"/>\n"
        "  </units>\n"
        "</model>\n";

    auto parser = libcellml::Parser::create();
    auto importer = libcellml::Importer::create();
    auto modelUnitsDefinitions = parser->parseModel(e);

    EXPECT_FALSE(modelUnitsDefinitions->hasUnresolvedImports());

    importer->flatten(modelUnitsDefinitions);

    auto printer = libcellml::Printer::create();

    auto a = printer->printModel(modelUnitsDefinitions);
    EXPECT_EQ(e, a);
}

TEST(ModelFlattening, modelWithUnresolvedImports)
{
    const std::string modelImportingUnits =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/2.0#\" name=\"importer_of_units\">\n"
        "  <import xmlns:xlink=\"http://www.w3.org/1999/xlink\" xlink:href=\"unitsdefinitions.xml\">\n"
        "    <units units_ref=\"ms\" name=\"my_ms\"/>\n"
        "  </import>\n"
        "</model>\n";

    auto parser = libcellml::Parser::create();
    auto importer = libcellml::Importer::create();
    auto modelWithUnitsImports = parser->parseModel(modelImportingUnits);

    EXPECT_TRUE(modelWithUnitsImports->hasUnresolvedImports());

    importer->flatten(modelWithUnitsImports);

    auto printer = libcellml::Printer::create();

    auto a = printer->printModel(modelWithUnitsImports);
    EXPECT_EQ(modelImportingUnits, a);
}

TEST(ModelFlattening, importedUnits)
{
    const std::string unitsDefinitionModel =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/2.0#\" xmlns:cellml=\"http://www.cellml.org/cellml/2.0#\" xmlns:xlink=\"http://www.w3.org/1999/xlink\" name=\"units\">\n"
        "  <units name=\"ms\">\n"
        "    <unit units=\"second\" prefix=\"milli\"/>\n"
        "  </units>\n"
        "</model>\n";

    const std::string modelImportingUnits =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model name=\"importer_of_units\" xmlns=\"http://www.cellml.org/cellml/2.0#\">\n"
        "  <import xmlns:xlink=\"http://www.w3.org/1999/xlink\" xlink:href=\"unitsdefinitions.xml\">\n"
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
    auto importer = libcellml::Importer::create();

    auto modelWithUnitsImports = parser->parseModel(modelImportingUnits);
    auto modelUnitsDefinitions = parser->parseModel(unitsDefinitionModel);

    EXPECT_TRUE(modelWithUnitsImports->hasUnresolvedImports());

    auto units = modelWithUnitsImports->units(0);
    auto importSource = units->importSource();
    importSource->setModel(modelUnitsDefinitions);

    EXPECT_FALSE(modelWithUnitsImports->hasUnresolvedImports());

    importer->flatten(modelWithUnitsImports);

    auto printer = libcellml::Printer::create();

    auto a = printer->printModel(modelWithUnitsImports);
    EXPECT_EQ(e, a);

    // Check that we haven't changed the imported model.
    auto aModelUnitsDefinitions = printer->printModel(modelUnitsDefinitions);
    auto eModelUnitsDefinitions = printer->printModel(parser->parseModel(unitsDefinitionModel));
    EXPECT_EQ(eModelUnitsDefinitions, aModelUnitsDefinitions);
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
        "      <apply id=\"actual_sin\">\n"
        "        <eq/>\n"
        "        <ci>sin</ci>\n"
        "        <apply>\n"
        "          <sin/>\n"
        "          <ci>x</ci>\n"
        "        </apply>\n"
        "      </apply>\n"
        "    </math>\n"
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
        "      <apply id=\"actual_sin\">\n"
        "        <eq/>\n"
        "        <ci>sin</ci>\n"
        "        <apply>\n"
        "          <sin/>\n"
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
    auto importer = libcellml::Importer::create();
    auto modelWithComponentImport = parser->parseModel(modelImportingComponent);
    auto modelSineDefinition = parser->parseModel(sineDefinitionModel);

    EXPECT_TRUE(modelWithComponentImport->hasUnresolvedImports());

    auto component = modelWithComponentImport->component(0)->component(0);
    auto importSource = component->importSource();
    importSource->setModel(modelSineDefinition);

    EXPECT_TRUE(component->isImport());
    EXPECT_FALSE(modelWithComponentImport->hasUnresolvedImports());

    importer->flatten(modelWithComponentImport);

    auto printer = libcellml::Printer::create();

    auto a = printer->printModel(modelWithComponentImport);
    EXPECT_EQ(e, a);
}

TEST(ModelFlattening, importedComponentWithEquivalentVariables)
{
    const std::string e =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/2.0#\" name=\"main_model\">\n"
        "  <component name=\"main_model_component\">\n"
        "    <variable name=\"v\" units=\"dimensionless\" initial_value=\"1\" interface=\"public_and_private\"/>\n"
        "  </component>\n"
        "  <component name=\"other_component\">\n"
        "    <variable name=\"time\" units=\"dimensionless\" interface=\"public\"/>\n"
        "    <variable name=\"parameter\" units=\"dimensionless\" interface=\"public\"/>\n"
        "    <variable name=\"cosine\" units=\"dimensionless\" initial_value=\"0\" interface=\"public\"/>\n"
        "    <math xmlns=\"http://www.w3.org/1998/Math/MathML\">\n"
        "      <apply>\n"
        "        <eq/>\n"
        "        <apply>\n"
        "          <diff/>\n"
        "          <bvar>\n"
        "            <ci>time</ci>\n"
        "          </bvar>\n"
        "          <ci>cosine</ci>\n"
        "        </apply>\n"
        "        <apply>\n"
        "          <sin/>\n"
        "          <apply>\n"
        "            <times/>\n"
        "            <ci>parameter</ci>\n"
        "            <ci>time</ci>\n"
        "          </apply>\n"
        "        </apply>\n"
        "      </apply>\n"
        "    </math>\n"
        "  </component>\n"
        "  <connection component_1=\"main_model_component\" component_2=\"other_component\">\n"
        "    <map_variables variable_1=\"v\" variable_2=\"parameter\"/>\n"
        "  </connection>\n"
        "  <encapsulation>\n"
        "    <component_ref component=\"main_model_component\">\n"
        "      <component_ref component=\"other_component\"/>\n"
        "    </component_ref>\n"
        "  </encapsulation>\n"
        "</model>\n";

    auto parser = libcellml::Parser::create();
    auto importer = libcellml::Importer::create();

    auto model = parser->parseModel(fileContents("modelflattening/equivalentimportedvariable.xml"));

    EXPECT_TRUE(model->hasUnresolvedImports());
    importer->resolveImports(resourcePath("modelflattening/"), model);
    EXPECT_FALSE(model->hasUnresolvedImports());

    // Want to make sure that we haven't damaged the import model after flattening.
    auto importModel = model->component(0)->component(0)->importSource()->model();

    importer->flatten(model);

    auto printer = libcellml::Printer::create();

    auto a = printer->printModel(model);
    EXPECT_EQ(e, a);

    // Check that we haven't changed the imported model.
    auto aImportModel = printer->printModel(importModel);
    auto eImportModel = printer->printModel(parser->parseModel(fileContents("modelflattening/reusable.xml")));
    EXPECT_EQ(eImportModel, aImportModel);
}

TEST(ModelFlattening, importedComponentWithInternalEquivalentVariables)
{
    const std::string e =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/2.0#\" name=\"main_model\">\n"
        "  <component name=\"main_model_component\">\n"
        "    <variable name=\"v\" units=\"dimensionless\" initial_value=\"1\" interface=\"public_and_private\"/>\n"
        "  </component>\n"
        "  <component name=\"other_component\">\n"
        "    <variable name=\"time\" units=\"dimensionless\" interface=\"public_and_private\"/>\n"
        "    <variable name=\"parameter\" units=\"dimensionless\" interface=\"public\"/>\n"
        "    <variable name=\"cosine\" units=\"dimensionless\" initial_value=\"0\" interface=\"public\"/>\n"
        "    <math xmlns=\"http://www.w3.org/1998/Math/MathML\">\n"
        "      <apply>\n"
        "        <eq/>\n"
        "        <apply>\n"
        "          <diff/>\n"
        "          <bvar>\n"
        "            <ci>time</ci>\n"
        "          </bvar>\n"
        "          <ci>cosine</ci>\n"
        "        </apply>\n"
        "        <apply>\n"
        "          <sin/>\n"
        "          <apply>\n"
        "            <times/>\n"
        "            <ci>parameter</ci>\n"
        "            <ci>time</ci>\n"
        "          </apply>\n"
        "        </apply>\n"
        "      </apply>\n"
        "    </math>\n"
        "  </component>\n"
        "  <component name=\"reusable_child_1\">\n"
        "    <variable name=\"time\" units=\"dimensionless\" interface=\"public\"/>\n"
        "  </component>\n"
        "  <component name=\"reusable_child_2\">\n"
        "    <variable name=\"time\" units=\"dimensionless\" interface=\"public\"/>\n"
        "  </component>\n"
        "  <connection component_1=\"other_component\" component_2=\"reusable_child_1\">\n"
        "    <map_variables variable_1=\"time\" variable_2=\"time\"/>\n"
        "  </connection>\n"
        "  <connection component_1=\"reusable_child_1\" component_2=\"reusable_child_2\">\n"
        "    <map_variables variable_1=\"time\" variable_2=\"time\"/>\n"
        "  </connection>\n"
        "  <encapsulation>\n"
        "    <component_ref component=\"main_model_component\">\n"
        "      <component_ref component=\"other_component\">\n"
        "        <component_ref component=\"reusable_child_1\"/>\n"
        "        <component_ref component=\"reusable_child_2\"/>\n"
        "      </component_ref>\n"
        "    </component_ref>\n"
        "  </encapsulation>\n"
        "</model>\n";

    auto parser = libcellml::Parser::create();
    auto importer = libcellml::Importer::create();
    auto model = parser->parseModel(fileContents("modelflattening/internalequivalentvariables.xml"));

    EXPECT_TRUE(model->hasUnresolvedImports());
    importer->resolveImports(resourcePath("modelflattening/"), model);
    EXPECT_FALSE(model->hasUnresolvedImports());

    // Want to make sure that we haven't damaged the import model after flattening.
    auto importModel = model->component(0)->component(0)->importSource()->model();

    importer->flatten(model);

    auto printer = libcellml::Printer::create();

    auto a = printer->printModel(model);
    EXPECT_EQ(e, a);

    // Check that we haven't changed the imported model.
    auto aImportModel = printer->printModel(importModel);
    auto eImportModel = printer->printModel(parser->parseModel(fileContents("modelflattening/reusable2.xml")));
    EXPECT_EQ(eImportModel, aImportModel);
}

TEST(ModelFlattening, importedComponentWithEquivalentVariablesReferencingVariablesOutsideOfImportedComponent)
{
    const std::string e =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/2.0#\" name=\"main_model\">\n"
        "  <component name=\"main_model_component\">\n"
        "    <variable name=\"v\" units=\"dimensionless\" initial_value=\"1\" interface=\"public_and_private\"/>\n"
        "  </component>\n"
        "  <component name=\"other_component\">\n"
        "    <variable name=\"time\" units=\"dimensionless\" interface=\"public_and_private\"/>\n"
        "    <variable name=\"parameter\" units=\"dimensionless\" interface=\"public\"/>\n"
        "    <variable name=\"cosine\" units=\"dimensionless\" initial_value=\"0\" interface=\"public\"/>\n"
        "    <math xmlns=\"http://www.w3.org/1998/Math/MathML\">\n"
        "      <apply>\n"
        "        <eq/>\n"
        "        <apply>\n"
        "          <diff/>\n"
        "          <bvar>\n"
        "            <ci>time</ci>\n"
        "          </bvar>\n"
        "          <ci>cosine</ci>\n"
        "        </apply>\n"
        "        <apply>\n"
        "          <sin/>\n"
        "          <apply>\n"
        "            <times/>\n"
        "            <ci>parameter</ci>\n"
        "            <ci>time</ci>\n"
        "          </apply>\n"
        "        </apply>\n"
        "      </apply>\n"
        "    </math>\n"
        "  </component>\n"
        "  <component name=\"reusable_child_1\">\n"
        "    <variable name=\"time\" units=\"dimensionless\" interface=\"public\"/>\n"
        "  </component>\n"
        "  <component name=\"reusable_child_2\">\n"
        "    <variable name=\"time\" units=\"dimensionless\" interface=\"public\"/>\n"
        "  </component>\n"
        "  <connection component_1=\"other_component\" component_2=\"reusable_child_1\">\n"
        "    <map_variables variable_1=\"time\" variable_2=\"time\"/>\n"
        "  </connection>\n"
        "  <connection component_1=\"reusable_child_1\" component_2=\"reusable_child_2\">\n"
        "    <map_variables variable_1=\"time\" variable_2=\"time\"/>\n"
        "  </connection>\n"
        "  <encapsulation>\n"
        "    <component_ref component=\"main_model_component\">\n"
        "      <component_ref component=\"other_component\">\n"
        "        <component_ref component=\"reusable_child_1\"/>\n"
        "        <component_ref component=\"reusable_child_2\"/>\n"
        "      </component_ref>\n"
        "    </component_ref>\n"
        "  </encapsulation>\n"
        "</model>\n";

    auto parser = libcellml::Parser::create();
    auto importer = libcellml::Importer::create();
    auto model = parser->parseModel(fileContents("modelflattening/outsidecomponentequivalentvariables.xml"));

    EXPECT_TRUE(model->hasUnresolvedImports());
    importer->resolveImports(resourcePath("modelflattening/"), model);
    EXPECT_FALSE(model->hasUnresolvedImports());

    importer->flatten(model);

    auto printer = libcellml::Printer::create();

    auto a = printer->printModel(model);
    EXPECT_EQ(e, a);
}

TEST(ModelFlattening, importedComponentUsingUnitsDefinedInImportedModel)
{
    const std::string e =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/2.0#\" name=\"main_model\">\n"
        "  <units name=\"fergie_time\">\n"
        "    <unit prefix=\"mega\" units=\"second\"/>\n"
        "  </units>\n"
        "  <component name=\"my_component\">\n"
        "    <variable name=\"time\" units=\"fergie_time\" interface=\"public_and_private\"/>\n"
        "  </component>\n"
        "</model>\n";

    auto parser = libcellml::Parser::create();
    auto importer = libcellml::Importer::create();
    auto model = parser->parseModel(fileContents("modelflattening/unitsdefinedinimportedmodel.xml"));

    EXPECT_TRUE(model->hasUnresolvedImports());
    importer->resolveImports(resourcePath("modelflattening/"), model);
    EXPECT_FALSE(model->hasUnresolvedImports());

    importer->flatten(model);

    auto printer = libcellml::Printer::create();

    auto a = printer->printModel(model);
    EXPECT_EQ(e, a);
}

TEST(ModelFlattening, importedComponentUsingImportedComponent)
{
    const std::string e =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/2.0#\" name=\"main_model\">\n"
        "  <component name=\"my_component\">\n"
        "    <variable name=\"time\" units=\"dimensionless\" interface=\"public_and_private\"/>\n"
        "    <variable name=\"parameter\" units=\"dimensionless\" interface=\"public\"/>\n"
        "    <variable name=\"cosine\" units=\"dimensionless\" initial_value=\"0\" interface=\"public\"/>\n"
        "    <math xmlns=\"http://www.w3.org/1998/Math/MathML\">\n"
        "      <apply>\n"
        "        <eq/>\n"
        "        <apply>\n"
        "          <diff/>\n"
        "          <bvar>\n"
        "            <ci>time</ci>\n"
        "          </bvar>\n"
        "          <ci>cosine</ci>\n"
        "        </apply>\n"
        "        <apply>\n"
        "          <sin/>\n"
        "          <apply>\n"
        "            <times/>\n"
        "            <ci>parameter</ci>\n"
        "            <ci>time</ci>\n"
        "          </apply>\n"
        "        </apply>\n"
        "      </apply>\n"
        "    </math>\n"
        "  </component>\n"
        "</model>\n";

    auto parser = libcellml::Parser::create();
    auto importer = libcellml::Importer::create();
    auto model = parser->parseModel(fileContents("modelflattening/importedcomponentusingimportedcomponent.xml"));

    EXPECT_TRUE(model->hasUnresolvedImports());
    importer->resolveImports(resourcePath("modelflattening/"), model);
    EXPECT_FALSE(model->hasUnresolvedImports());
    EXPECT_TRUE(model->hasImports());

    importer->flatten(model);
    EXPECT_FALSE(model->hasImports());

    auto printer = libcellml::Printer::create();

    auto a = printer->printModel(model);
    EXPECT_EQ(e, a);
}

TEST(ModelFlattening, repeatedImportOfSameUnitsViaDifferentComponents)
{
    const std::string e =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/2.0#\" name=\"main_model\">\n"
        "  <units name=\"fergie_time\">\n"
        "    <unit prefix=\"mega\" units=\"second\"/>\n"
        "  </units>\n"
        "  <component name=\"average_component\">\n"
        "    <variable name=\"time\" units=\"fergie_time\" interface=\"public_and_private\"/>\n"
        "  </component>\n"
        "  <component name=\"good_component\">\n"
        "    <variable name=\"sometime\" units=\"fergie_time\" interface=\"public_and_private\"/>\n"
        "  </component>\n"
        "</model>\n";

    auto parser = libcellml::Parser::create();
    auto importer = libcellml::Importer::create();
    auto model = parser->parseModel(fileContents("modelflattening/repeatedimportofsameunitsviadifferentcomponents.xml"));

    EXPECT_TRUE(model->hasUnresolvedImports());
    importer->resolveImports(resourcePath("modelflattening/"), model);
    EXPECT_FALSE(model->hasUnresolvedImports());

    importer->flatten(model);

    auto printer = libcellml::Printer::create();

    auto a = printer->printModel(model);
    EXPECT_EQ(e, a);
}

TEST(ModelFlattening, importedUnitsWithNameClashes)
{
    const std::string e =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/2.0#\" name=\"main_model\">\n"
        "  <units name=\"common_units\">\n"
        "    <unit units=\"second\"/>\n"
        "  </units>\n"
        "  <units name=\"common_units_1\">\n"
        "    <unit prefix=\"hecto\" units=\"second\"/>\n"
        "  </units>\n"
        "  <component name=\"my_component\">\n"
        "    <variable name=\"v\" units=\"common_units_1\" interface=\"public_and_private\"/>\n"
        "  </component>\n"
        "  <component name=\"best_component\">\n"
        "    <variable name=\"v\" units=\"common_units\" initial_value=\"1\" interface=\"public_and_private\"/>\n"
        "  </component>\n"
        "</model>\n";

    auto parser = libcellml::Parser::create();
    auto importer = libcellml::Importer::create();
    auto model = parser->parseModel(fileContents("modelflattening/importedunitswithnameclashes.xml"));

    EXPECT_TRUE(model->hasUnresolvedImports());
    importer->resolveImports(resourcePath("modelflattening/"), model);
    EXPECT_FALSE(model->hasUnresolvedImports());

    importer->flatten(model);

    auto printer = libcellml::Printer::create();

    auto a = printer->printModel(model);
    EXPECT_EQ(e, a);
}

TEST(ModelFlattening, importedComponentWithNameClashes)
{
    const std::string e =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/2.0#\" name=\"main_model\">\n"
        "  <units name=\"common_units\">\n"
        "    <unit units=\"second\"/>\n"
        "  </units>\n"
        "  <component name=\"my_component\"/>\n"
        "  <component name=\"best_component_1\"/>\n"
        "  <component name=\"best_component\">\n"
        "    <variable name=\"v\" units=\"common_units\" initial_value=\"1\" interface=\"public_and_private\"/>\n"
        "  </component>\n"
        "  <encapsulation>\n"
        "    <component_ref component=\"my_component\">\n"
        "      <component_ref component=\"best_component_1\"/>\n"
        "    </component_ref>\n"
        "  </encapsulation>\n"
        "</model>\n";

    auto parser = libcellml::Parser::create();
    auto importer = libcellml::Importer::create();
    auto model = parser->parseModel(fileContents("modelflattening/importedcomponentswithnameclashes.xml"));

    EXPECT_TRUE(model->hasUnresolvedImports());
    importer->resolveImports(resourcePath("modelflattening/"), model);
    EXPECT_FALSE(model->hasUnresolvedImports());

    importer->flatten(model);

    auto printer = libcellml::Printer::create();

    auto a = printer->printModel(model);
    EXPECT_EQ(e, a);
}

// The variable ordering changes when using the HH model defined with imports.
TEST(ModelFlattening, hodgkinHuxleyDefinedUsingImports)
{
    auto parser = libcellml::Parser::create();
    auto importer = libcellml::Importer::create();
    auto model = parser->parseModel(fileContents("modelflattening/hodgkin_huxley_squid_axon_model_1952/model.cellml"));

    EXPECT_TRUE(model->hasUnresolvedImports());

    importer->resolveImports(resourcePath("modelflattening/hodgkin_huxley_squid_axon_model_1952/"), model);
    EXPECT_FALSE(model->hasUnresolvedImports());

    importer->flatten(model);

    auto printer = libcellml::Printer::create();

    auto a = printer->printModel(model);
    auto modelNonImportVersion = parser->parseModel(fileContents("generator/hodgkin_huxley_squid_axon_model_1952/model.cellml"));
    auto e = printer->printModel(modelNonImportVersion);
    EXPECT_EQ(e, a);

    auto generator = libcellml::Generator::create();

    generator->processModel(model);

    EXPECT_EQ(fileContents("generator/hodgkin_huxley_squid_axon_model_1952/model.h"), generator->interfaceCode());
    EXPECT_EQ(fileContents("generator/hodgkin_huxley_squid_axon_model_1952/model.c"), generator->implementationCode());

    libcellml::GeneratorProfilePtr profile = libcellml::GeneratorProfile::create(libcellml::GeneratorProfile::Profile::PYTHON);

    generator->setProfile(profile);

    EXPECT_EQ("", generator->interfaceCode());
    EXPECT_EQ(fileContents("generator/hodgkin_huxley_squid_axon_model_1952/model.py"), generator->implementationCode());
}

#endif

TEST(ModelFlattening, importingComponentThatAlsoHasAnImportedComponentAsAChild)
{
    const std::string e =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/2.0#\" name=\"a_model\">\n"
        "  <units name=\"mV\">\n"
        "    <unit prefix=\"milli\" units=\"volt\"/>\n"
        "  </units>\n"
        "  <units name=\"ms\">\n"
        "    <unit prefix=\"milli\" units=\"second\"/>\n"
        "  </units>\n"
        "  <units name=\"microA_per_cm2\">\n"
        "    <unit prefix=\"micro\" units=\"ampere\"/>\n"
        "    <unit exponent=\"-2\" prefix=\"centi\" units=\"metre\"/>\n"
        "  </units>\n"
        "  <units name=\"microF_per_cm2\">\n"
        "    <unit prefix=\"micro\" units=\"farad\"/>\n"
        "    <unit exponent=\"-2\" prefix=\"centi\" units=\"metre\"/>\n"
        "  </units>\n"
        "  <units name=\"mS_per_cm2\">\n"
        "    <unit prefix=\"milli\" units=\"siemens\"/>\n"
        "    <unit exponent=\"-2\" prefix=\"centi\" units=\"metre\"/>\n"
        "  </units>\n"
        "  <units name=\"mM\">\n"
        "    <unit prefix=\"milli\" units=\"mole\"/>\n"
        "  </units>\n"
        "  <units name=\"per_ms\">\n"
        "    <unit exponent=\"-1\" prefix=\"milli\" units=\"second\"/>\n"
        "  </units>\n"
        "  <component name=\"membrane\">\n"
        "    <variable name=\"V\" units=\"mV\" interface=\"public_and_private\"/>\n"
        "    <variable name=\"t\" units=\"ms\" interface=\"public_and_private\"/>\n"
        "    <variable name=\"i_K\" units=\"microA_per_cm2\" interface=\"public_and_private\"/>\n"
        "    <variable name=\"i_Na\" units=\"microA_per_cm2\" interface=\"public_and_private\"/>\n"
        "    <variable name=\"i_L\" units=\"microA_per_cm2\" interface=\"public_and_private\"/>\n"
        "    <variable name=\"i_stim\" units=\"microA_per_cm2\" interface=\"public_and_private\"/>\n"
        "    <variable name=\"i_tot\" units=\"microA_per_cm2\" interface=\"public_and_private\"/>\n"
        "    <variable name=\"Cm\" units=\"microF_per_cm2\" initial_value=\"1\"/>\n"
        "    <math xmlns=\"http://www.w3.org/1998/Math/MathML\" xmlns:cellml=\"http://www.cellml.org/cellml/2.0#\">\n"
        "      <apply>\n"
        "        <eq/>\n"
        "        <ci>i_stim</ci>\n"
        "        <piecewise>\n"
        "          <piece>\n"
        "            <cn cellml:units=\"microA_per_cm2\">0</cn>\n"
        "            <apply>\n"
        "              <lt/>\n"
        "              <ci>t</ci>\n"
        "              <cn cellml:units=\"ms\">1</cn>\n"
        "            </apply>\n"
        "          </piece>\n"
        "          <piece>\n"
        "            <cn cellml:units=\"microA_per_cm2\">0</cn>\n"
        "            <apply>\n"
        "              <gt/>\n"
        "              <ci>t</ci>\n"
        "              <cn cellml:units=\"ms\">1.2</cn>\n"
        "            </apply>\n"
        "          </piece>\n"
        "          <otherwise>\n"
        "            <cn cellml:units=\"microA_per_cm2\">100</cn>\n"
        "          </otherwise>\n"
        "        </piecewise>\n"
        "      </apply>\n"
        "      <apply>\n"
        "        <eq/>\n"
        "        <apply>\n"
        "          <diff/>\n"
        "          <bvar>\n"
        "            <ci>t</ci>\n"
        "          </bvar>\n"
        "          <ci>V</ci>\n"
        "        </apply>\n"
        "        <apply>\n"
        "          <divide/>\n"
        "          <apply>\n"
        "            <plus/>\n"
        "            <ci>i_stim</ci>\n"
        "            <ci>i_K</ci>\n"
        "            <ci>i_Na</ci>\n"
        "            <ci>i_L</ci>\n"
        "          </apply>\n"
        "          <ci>Cm</ci>\n"
        "        </apply>\n"
        "      </apply>\n"
        "    </math>\n"
        "  </component>\n"
        "  <component name=\"sodium_channel_1\">\n"
        "    <variable name=\"V\" units=\"mV\" interface=\"public_and_private\"/>\n"
        "    <variable name=\"t\" units=\"ms\" interface=\"public_and_private\"/>\n"
        "    <variable name=\"h\" units=\"dimensionless\" interface=\"private\"/>\n"
        "    <variable name=\"m\" units=\"dimensionless\" interface=\"private\"/>\n"
        "    <variable name=\"g_Na\" units=\"mS_per_cm2\" initial_value=\"120\"/>\n"
        "    <variable name=\"E_Na\" units=\"mV\"/>\n"
        "    <variable name=\"i_Na\" units=\"microA_per_cm2\"/>\n"
        "    <variable name=\"Nao\" units=\"mM\" initial_value=\"140\"/>\n"
        "    <variable name=\"Nai\" units=\"mM\" initial_value=\"30\"/>\n"
        "    <variable name=\"RTF\" units=\"mV\" initial_value=\"25\"/>\n"
        "    <variable name=\"Na_conductance\" units=\"mS_per_cm2\"/>\n"
        "    <math xmlns=\"http://www.w3.org/1998/Math/MathML\" xmlns:cellml=\"http://www.cellml.org/cellml/2.0#\">\n"
        "      <apply>\n"
        "        <eq/>\n"
        "        <ci>E_Na</ci>\n"
        "        <apply>\n"
        "          <times/>\n"
        "          <ci>RTF</ci>\n"
        "          <apply>\n"
        "            <log/>\n"
        "            <apply>\n"
        "              <divide/>\n"
        "              <ci>Nao</ci>\n"
        "              <ci>Nai</ci>\n"
        "            </apply>\n"
        "          </apply>\n"
        "        </apply>\n"
        "      </apply>\n"
        "      <apply>\n"
        "        <eq/>\n"
        "        <ci>Na_conductance</ci>\n"
        "        <apply>\n"
        "          <times/>\n"
        "          <ci>g_Na</ci>\n"
        "          <apply>\n"
        "            <power/>\n"
        "            <ci>m</ci>\n"
        "            <apply>\n"
        "              <times/>\n"
        "              <cn cellml:units=\"dimensionless\">3</cn>\n"
        "              <ci>h</ci>\n"
        "            </apply>\n"
        "          </apply>\n"
        "        </apply>\n"
        "      </apply>\n"
        "      <apply>\n"
        "        <eq/>\n"
        "        <ci>i_Na</ci>\n"
        "        <apply>\n"
        "          <times/>\n"
        "          <ci>Na_conductance</ci>\n"
        "          <apply>\n"
        "            <minus/>\n"
        "            <ci>V</ci>\n"
        "            <ci>E_Na</ci>\n"
        "          </apply>\n"
        "        </apply>\n"
        "      </apply>\n"
        "    </math>\n"
        "  </component>\n"
        "  <component name=\"mGate\">\n"
        "    <variable name=\"V\" units=\"mV\" interface=\"public\"/>\n"
        "    <variable name=\"t\" units=\"ms\" interface=\"public\"/>\n"
        "    <variable name=\"alpha_m\" units=\"per_ms\"/>\n"
        "    <variable name=\"beta_m\" units=\"per_ms\"/>\n"
        "    <variable name=\"m\" units=\"dimensionless\" initial_value=\"0.05\" interface=\"public\"/>\n"
        "    <math xmlns=\"http://www.w3.org/1998/Math/MathML\" xmlns:cellml=\"http://www.cellml.org/cellml/2.0#\">\n"
        "      <apply>\n"
        "        <eq/>\n"
        "        <ci>alpha_m</ci>\n"
        "        <apply>\n"
        "          <divide/>\n"
        "          <apply>\n"
        "            <times/>\n"
        "            <cn cellml:units=\"per_mV_ms\">0.1</cn>\n"
        "            <apply>\n"
        "              <plus/>\n"
        "              <ci>V</ci>\n"
        "              <cn cellml:units=\"mV\">25</cn>\n"
        "            </apply>\n"
        "          </apply>\n"
        "          <apply>\n"
        "            <minus/>\n"
        "            <apply>\n"
        "              <exp/>\n"
        "              <apply>\n"
        "                <divide/>\n"
        "                <apply>\n"
        "                  <plus/>\n"
        "                  <ci>V</ci>\n"
        "                  <cn cellml:units=\"mV\">25</cn>\n"
        "                </apply>\n"
        "                <cn cellml:units=\"mV\">10</cn>\n"
        "              </apply>\n"
        "            </apply>\n"
        "            <cn cellml:units=\"dimensionless\">1</cn>\n"
        "          </apply>\n"
        "        </apply>\n"
        "      </apply>\n"
        "      <apply>\n"
        "        <eq/>\n"
        "        <ci>beta_m</ci>\n"
        "        <apply>\n"
        "          <times/>\n"
        "          <cn cellml:units=\"per_ms\">4</cn>\n"
        "          <apply>\n"
        "            <exp/>\n"
        "            <apply>\n"
        "              <divide/>\n"
        "              <ci>V</ci>\n"
        "              <cn cellml:units=\"mV\">18</cn>\n"
        "            </apply>\n"
        "          </apply>\n"
        "        </apply>\n"
        "      </apply>\n"
        "      <apply>\n"
        "        <eq/>\n"
        "        <apply>\n"
        "          <diff/>\n"
        "          <bvar>\n"
        "            <ci>t</ci>\n"
        "          </bvar>\n"
        "          <ci>m</ci>\n"
        "        </apply>\n"
        "        <apply>\n"
        "          <minus/>\n"
        "          <apply>\n"
        "            <times/>\n"
        "            <ci>alpha_m</ci>\n"
        "            <apply>\n"
        "              <minus/>\n"
        "              <cn cellml:units=\"dimensionless\">1</cn>\n"
        "              <ci>m</ci>\n"
        "            </apply>\n"
        "          </apply>\n"
        "          <apply>\n"
        "            <times/>\n"
        "            <ci>m</ci>\n"
        "            <ci>beta_m</ci>\n"
        "          </apply>\n"
        "        </apply>\n"
        "      </apply>\n"
        "    </math>\n"
        "  </component>\n"
        "  <component name=\"hGate\">\n"
        "    <variable name=\"V\" units=\"mV\" interface=\"public\"/>\n"
        "    <variable name=\"t\" units=\"ms\" interface=\"public\"/>\n"
        "    <variable name=\"alpha_h\" units=\"per_ms\"/>\n"
        "    <variable name=\"beta_h\" units=\"per_ms\"/>\n"
        "    <variable name=\"h\" units=\"dimensionless\" initial_value=\"1\" interface=\"public\"/>\n"
        "    <math xmlns=\"http://www.w3.org/1998/Math/MathML\" xmlns:cellml=\"http://www.cellml.org/cellml/2.0#\">\n"
        "      <apply>\n"
        "        <eq/>\n"
        "        <ci>alpha_h</ci>\n"
        "        <apply>\n"
        "          <times/>\n"
        "          <cn cellml:units=\"per_ms\">0.07</cn>\n"
        "          <apply>\n"
        "            <exp/>\n"
        "            <apply>\n"
        "              <divide/>\n"
        "              <ci>V</ci>\n"
        "              <cn cellml:units=\"mV\">20</cn>\n"
        "            </apply>\n"
        "          </apply>\n"
        "        </apply>\n"
        "      </apply>\n"
        "      <apply>\n"
        "        <eq/>\n"
        "        <ci>beta_h</ci>\n"
        "        <apply>\n"
        "          <divide/>\n"
        "          <cn cellml:units=\"per_ms\">1</cn>\n"
        "          <apply>\n"
        "            <exp/>\n"
        "            <apply>\n"
        "              <divide/>\n"
        "              <apply>\n"
        "                <plus/>\n"
        "                <ci>V</ci>\n"
        "                <cn cellml:units=\"mV\">30</cn>\n"
        "              </apply>\n"
        "              <cn cellml:units=\"mV\">10</cn>\n"
        "            </apply>\n"
        "          </apply>\n"
        "        </apply>\n"
        "      </apply>\n"
        "      <apply>\n"
        "        <eq/>\n"
        "        <apply>\n"
        "          <diff/>\n"
        "          <bvar>\n"
        "            <ci>t</ci>\n"
        "          </bvar>\n"
        "          <ci>h</ci>\n"
        "        </apply>\n"
        "        <apply>\n"
        "          <minus/>\n"
        "          <apply>\n"
        "            <times/>\n"
        "            <ci>alpha_h</ci>\n"
        "            <apply>\n"
        "              <minus/>\n"
        "              <cn cellml:units=\"dimensionless\">1</cn>\n"
        "              <ci>h</ci>\n"
        "            </apply>\n"
        "          </apply>\n"
        "          <apply>\n"
        "            <times/>\n"
        "            <ci>h</ci>\n"
        "            <ci>beta_h</ci>\n"
        "          </apply>\n"
        "        </apply>\n"
        "      </apply>\n"
        "    </math>\n"
        "  </component>\n"
        "  <connection component_1=\"sodium_channel_1\" component_2=\"mGate\">\n"
        "    <map_variables variable_1=\"V\" variable_2=\"V\"/>\n"
        "    <map_variables variable_1=\"t\" variable_2=\"t\"/>\n"
        "    <map_variables variable_1=\"m\" variable_2=\"m\"/>\n"
        "  </connection>\n"
        "  <connection component_1=\"sodium_channel_1\" component_2=\"hGate\">\n"
        "    <map_variables variable_1=\"V\" variable_2=\"V\"/>\n"
        "    <map_variables variable_1=\"t\" variable_2=\"t\"/>\n"
        "    <map_variables variable_1=\"h\" variable_2=\"h\"/>\n"
        "  </connection>\n"
        "  <encapsulation>\n"
        "    <component_ref component=\"membrane\">\n"
        "      <component_ref component=\"sodium_channel_1\">\n"
        "        <component_ref component=\"mGate\"/>\n"
        "        <component_ref component=\"hGate\"/>\n"
        "      </component_ref>\n"
        "    </component_ref>\n"
        "  </encapsulation>\n"
        "</model>\n";

    auto parser = libcellml::Parser::create();
    auto e_model = parser->parseModel(e);

    // KRM Currently there's a bug in the model above but it's fixed in another PR.
    // The 'per_mV_ms' units from the sodium channel are not being imported, and this model is invalid.

    auto model = libcellml::Model::create("a_model");

    // Import the membrane component from a file
    auto membrane = libcellml::Component::create("membrane");
    model->addComponent(membrane);

    auto membraneImporter = libcellml::ImportSource::create();
    membraneImporter->setUrl("membranemodel.cellml");

    membrane->setImportSource(membraneImporter);
    membrane->setImportReference("membrane_for_importing");

    // Import the sodium channel from a file, and set as encapsulated child of the membrane
    auto sodiumChannel = libcellml::Component::create("sodium_channel");
    membrane->addComponent(sodiumChannel);

    auto sodiumImporter = libcellml::ImportSource::create();
    sodiumImporter->setUrl("sodiumchannel.cellml");

    sodiumChannel->setImportSource(sodiumImporter);
    sodiumChannel->setImportReference("sodiumChannel");

    // Resolve both the imports
    EXPECT_TRUE(model->hasUnresolvedImports());
    auto importer = libcellml::Importer::create();

    importer->resolveImports(resourcePath("modelflattening/"), model);
    EXPECT_EQ(size_t(0), importer->issueCount());
    printIssues(importer);

    EXPECT_FALSE(model->hasUnresolvedImports());
    importer->flatten(model);

    auto printer = libcellml::Printer::create();

    auto a = printer->printModel(model);
    EXPECT_EQ(e, a);
}

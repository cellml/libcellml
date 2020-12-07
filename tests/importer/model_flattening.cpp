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
    auto modelUnitsDefinitions = parser->parseModel(e);
    auto importer = libcellml::Importer::create();

    EXPECT_FALSE(modelUnitsDefinitions->hasUnresolvedImports());

    auto flatModel = importer->flattenModel(modelUnitsDefinitions);

    auto printer = libcellml::Printer::create();

    auto a = printer->printModel(flatModel);
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
    auto modelWithUnitsImports = parser->parseModel(modelImportingUnits);

    EXPECT_TRUE(modelWithUnitsImports->hasUnresolvedImports());

    auto importer = libcellml::Importer::create();
    auto flatModel = importer->flattenModel(modelWithUnitsImports);

    EXPECT_EQ(nullptr, flatModel);
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

    auto modelWithUnitsImports = parser->parseModel(modelImportingUnits);
    auto modelUnitsDefinitions = parser->parseModel(unitsDefinitionModel);

    EXPECT_TRUE(modelWithUnitsImports->hasUnresolvedImports());

    auto units = modelWithUnitsImports->units(0);
    auto importSource = units->importSource();
    importSource->setModel(modelUnitsDefinitions);

    EXPECT_FALSE(modelWithUnitsImports->hasUnresolvedImports());

    auto importer = libcellml::Importer::create();

    modelWithUnitsImports = importer->flattenModel(modelWithUnitsImports);
    EXPECT_EQ(size_t(0), modelWithUnitsImports->importSourceCount());

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

    auto modelWithComponentImport = parser->parseModel(modelImportingComponent);
    auto modelSineDefinition = parser->parseModel(sineDefinitionModel);

    EXPECT_TRUE(modelWithComponentImport->hasUnresolvedImports());

    auto component = modelWithComponentImport->component(0)->component(0);
    auto importSource = component->importSource();
    importSource->setModel(modelSineDefinition);

    EXPECT_TRUE(component->isImport());
    EXPECT_FALSE(modelWithComponentImport->hasUnresolvedImports());

    auto importer = libcellml::Importer::create();
    modelWithComponentImport = importer->flattenModel(modelWithComponentImport);

    EXPECT_EQ(size_t(0), modelWithComponentImport->importSourceCount());

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
    auto model = parser->parseModel(fileContents("modelflattening/equivalentimportedvariable.xml"));
    auto importer = libcellml::Importer::create();

    EXPECT_TRUE(model->hasUnresolvedImports());

    importer->resolveImports(model, resourcePath("modelflattening/"));

    EXPECT_FALSE(model->hasUnresolvedImports());

    // Want to make sure that we haven't damaged the import model after flattening.
    auto importModel = model->component(0)->component(0)->importSource()->model();

    model = importer->flattenModel(model);

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
    auto model = parser->parseModel(fileContents("modelflattening/internalequivalentvariables.xml"));
    auto importer = libcellml::Importer::create();

    EXPECT_TRUE(model->hasUnresolvedImports());
    importer->resolveImports(model, resourcePath("modelflattening/"));
    EXPECT_FALSE(model->hasUnresolvedImports());

    // Want to make sure that we haven't damaged the import model after flattening.
    auto importModel = model->component(0)->component(0)->importSource()->model();

    model = importer->flattenModel(model);

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
    auto model = parser->parseModel(fileContents("modelflattening/outsidecomponentequivalentvariables.xml"));
    auto importer = libcellml::Importer::create();

    EXPECT_TRUE(model->hasUnresolvedImports());
    importer->resolveImports(model, resourcePath("modelflattening/"));
    EXPECT_FALSE(model->hasUnresolvedImports());

    model = importer->flattenModel(model);

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
    auto model = parser->parseModel(fileContents("modelflattening/unitsdefinedinimportedmodel.xml"));
    auto importer = libcellml::Importer::create();

    EXPECT_TRUE(model->hasUnresolvedImports());
    importer->resolveImports(model, resourcePath("modelflattening/"));
    EXPECT_FALSE(model->hasUnresolvedImports());

    model = importer->flattenModel(model);

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
    auto model = parser->parseModel(fileContents("modelflattening/importedcomponentusingimportedcomponent.xml"));
    auto importer = libcellml::Importer::create();

    EXPECT_TRUE(model->hasUnresolvedImports());

    importer->resolveImports(model, resourcePath("modelflattening/"));
    EXPECT_FALSE(model->hasUnresolvedImports());
    EXPECT_TRUE(model->hasImports());

    model = importer->flattenModel(model);
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
    auto model = parser->parseModel(fileContents("modelflattening/repeatedimportofsameunitsviadifferentcomponents.xml"));
    auto importer = libcellml::Importer::create();

    EXPECT_TRUE(model->hasUnresolvedImports());
    importer->resolveImports(model, resourcePath("modelflattening/"));
    EXPECT_FALSE(model->hasUnresolvedImports());

    model = importer->flattenModel(model);

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
    auto model = parser->parseModel(fileContents("modelflattening/importedunitswithnameclashes.xml"));
    auto importer = libcellml::Importer::create();

    EXPECT_TRUE(model->hasUnresolvedImports());
    importer->resolveImports(model, resourcePath("modelflattening/"));
    EXPECT_FALSE(model->hasUnresolvedImports());

    model = importer->flattenModel(model);

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
    auto model = parser->parseModel(fileContents("modelflattening/importedcomponentswithnameclashes.xml"));
    auto importer = libcellml::Importer::create();

    EXPECT_TRUE(model->hasUnresolvedImports());
    importer->resolveImports(model, resourcePath("modelflattening/"));
    EXPECT_FALSE(model->hasUnresolvedImports());

    model = importer->flattenModel(model);

    auto printer = libcellml::Printer::create();

    auto a = printer->printModel(model);
    EXPECT_EQ(e, a);
}

TEST(ModelFlattening, importingComponentThatAlsoHasAnImportedComponentAsAChild)
{
    const std::string e =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/2.0#\" name=\"a_model\">\n"
        "  <component name=\"membrane\"/>\n"
        "  <component name=\"sodium_channel_1\"/>\n"
        "  <encapsulation>\n"
        "    <component_ref component=\"membrane\">\n"
        "      <component_ref component=\"sodium_channel_1\"/>\n"
        "    </component_ref>\n"
        "  </encapsulation>\n"
        "</model>\n";

    auto model = libcellml::Model::create("a_model");
    auto importer = libcellml::Importer::create();

    // Import the membrane component from a file.
    auto membrane = libcellml::Component::create("membrane");
    model->addComponent(membrane);

    auto membraneImporter = libcellml::ImportSource::create();
    membraneImporter->setUrl("basic_membrane_model.cellml");

    membrane->setImportSource(membraneImporter);
    membrane->setImportReference("membrane_for_importing");

    // Import the sodium channel from a file, and set as encapsulated child of the membrane.
    auto sodiumChannel = libcellml::Component::create("sodium_channel");
    membrane->addComponent(sodiumChannel);

    auto sodiumImporter = libcellml::ImportSource::create();
    sodiumImporter->setUrl("basic_sodium_channel.cellml");

    sodiumChannel->setImportSource(sodiumImporter);
    sodiumChannel->setImportReference("sodium_channel_for_importing");

    EXPECT_TRUE(model->hasUnresolvedImports());
    importer->resolveImports(model, resourcePath("modelflattening/"));
    EXPECT_FALSE(model->hasUnresolvedImports());

    model = importer->flattenModel(model);
    auto printer = libcellml::Printer::create();
    auto a = printer->printModel(model);
    EXPECT_EQ(e, a);
}

TEST(ModelFlattening, unitsUsedByVariableNotInDirectlyImportedComponent)
{
    const std::string e =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/2.0#\" name=\"a_model\">\n"
        "  <units name=\"per_ms\">\n"
        "    <unit exponent=\"-1\" prefix=\"milli\" units=\"second\"/>\n"
        "  </units>\n"
        "  <component name=\"imported_hierarchy\"/>\n"
        "  <component name=\"mGate\">\n"
        "    <variable name=\"alpha_m\" units=\"per_ms\"/>\n"
        "  </component>\n"
        "  <encapsulation>\n"
        "    <component_ref component=\"imported_hierarchy\">\n"
        "      <component_ref component=\"mGate\"/>\n"
        "    </component_ref>\n"
        "  </encapsulation>\n"
        "</model>\n";

    auto model = libcellml::Model::create("a_model");
    auto importer = libcellml::Importer::create();
    // Import the component hierarchy from a file
    auto channel = libcellml::Component::create("imported_hierarchy");
    model->addComponent(channel);

    auto channelImporter = libcellml::ImportSource::create();
    channelImporter->setUrl("imported_hierarchy_model.cellml");

    channel->setImportSource(channelImporter);
    channel->setImportReference("sodium_channel");

    EXPECT_TRUE(model->hasUnresolvedImports());
    importer->resolveImports(model, resourcePath("modelflattening/"));
    EXPECT_FALSE(model->hasUnresolvedImports());

    model = importer->flattenModel(model);

    auto printer = libcellml::Printer::create();

    auto a = printer->printModel(model);
    EXPECT_EQ(e, a);
}

// The variable ordering changes when using the HH model defined with imports.
TEST(ModelFlattening, hodgkinHuxleyDefinedUsingImports)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("modelflattening/hodgkin_huxley_squid_axon_model_1952/model.cellml"));
    auto importer = libcellml::Importer::create();

    EXPECT_TRUE(model->hasUnresolvedImports());
    importer->resolveImports(model, resourcePath("modelflattening/hodgkin_huxley_squid_axon_model_1952/"));
    EXPECT_FALSE(model->hasUnresolvedImports());

    model = importer->flattenModel(model);

    auto printer = libcellml::Printer::create();

    auto a = printer->printModel(model);
    auto modelNonImportVersion = parser->parseModel(fileContents("generator/hodgkin_huxley_squid_axon_model_1952/model.cellml"));
    auto e = printer->printModel(modelNonImportVersion);
    EXPECT_EQ(e, a);

    auto analyser = libcellml::Analyser::create();

    analyser->analyseModel(model);

    auto generator = libcellml::Generator::create();

    generator->setModel(analyser->model());

    EXPECT_EQ(fileContents("generator/hodgkin_huxley_squid_axon_model_1952/model.h"), generator->interfaceCode());
    EXPECT_EQ(fileContents("generator/hodgkin_huxley_squid_axon_model_1952/model.c"), generator->implementationCode());

    libcellml::GeneratorProfilePtr profile = libcellml::GeneratorProfile::create(libcellml::GeneratorProfile::Profile::PYTHON);

    generator->setProfile(profile);

    EXPECT_EQ("", generator->interfaceCode());
    EXPECT_EQ(fileContents("generator/hodgkin_huxley_squid_axon_model_1952/model.py"), generator->implementationCode());
}

TEST(ModelFlattening, importedComponentsWithConnectionsToChildren)
{
    const std::string modelConnectionsParentChild =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/2.0#\" xmlns:cellml=\"http://www.cellml.org/cellml/2.0#\" xmlns:xlink=\"http://www.w3.org/1999/xlink\" name=\"units\">\n"
        "  <units name=\"ms\">\n"
        "    <unit units=\"second\" prefix=\"milli\"/>\n"
        "  </units>\n"
        "    <units name=\"per_ms\">\n"
        "    <unit exponent=\"-1\" prefix=\"milli\" units=\"second\"/>\n"
        "  </units>\n"
        "  <component name=\"gate\">\n"
        "    <variable name=\"t\" units=\"ms\" interface=\"public_and_private\"/>\n"
        "    <variable name=\"X\" units=\"dimensionless\" interface=\"public_and_private\"/>\n"
        "  </component>\n"
        "  <component name=\"gateEquations\">\n"
        "    <variable name=\"t\" units=\"ms\" interface=\"public\"/>\n"
        "    <variable name=\"alpha_X\" units=\"per_ms\" interface=\"public\"/>\n"
        "    <variable name=\"X\" units=\"dimensionless\" interface=\"public\"/>\n"
        "  </component>\n"
        "  <connection component_1=\"gate\" component_2=\"gateEquations\">\n"
        "    <map_variables variable_1=\"t\" variable_2=\"t\"/>\n"
        "    <map_variables variable_1=\"X\" variable_2=\"X\"/>\n"
        "  </connection>\n"
        "  <encapsulation>\n"
        "    <component_ref component=\"gate\">\n"
        "      <component_ref component=\"gateEquations\"/>\n"
        "    </component_ref>\n"
        "  </encapsulation>\n"
        "</model>\n";

    const std::string importingModel =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model name=\"importer_of_units\" xmlns=\"http://www.cellml.org/cellml/2.0#\">\n"
        "  <import xmlns:xlink=\"http://www.w3.org/1999/xlink\" xlink:href=\"GateModel.cellml\">\n"
        "    <component component_ref=\"gateEquations\" name=\"importedGateH\"/>\n"
        "  </import>\n"
        "  <component name=\"hGateEquations\">\n"
        "    <variable name=\"V\" units=\"mV\" interface=\"public\"/>\n"
        "  </component>\n"
        "  <encapsulation>\n"
        "    <component_ref component=\"hGateEquations\">\n"
        "      <component_ref component=\"importedGateH\"/>\n"
        "    </component_ref>\n"
        "  </encapsulation>\n"
        "</model>\n";

    const std::string e =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/2.0#\" name=\"importer_of_units\">\n"
        "  <units name=\"ms\">\n"
        "    <unit prefix=\"milli\" units=\"second\"/>\n"
        "  </units>\n"
        "  <units name=\"per_ms\">\n"
        "    <unit exponent=\"-1\" prefix=\"milli\" units=\"second\"/>\n"
        "  </units>\n"
        "  <component name=\"hGateEquations\">\n"
        "    <variable name=\"V\" units=\"mV\" interface=\"public\"/>\n"
        "  </component>\n"
        "  <component name=\"importedGateH\">\n"
        "    <variable name=\"t\" units=\"ms\" interface=\"public\"/>\n"
        "    <variable name=\"alpha_X\" units=\"per_ms\" interface=\"public\"/>\n"
        "    <variable name=\"X\" units=\"dimensionless\" interface=\"public\"/>\n"
        "  </component>\n"
        "  <encapsulation>\n"
        "    <component_ref component=\"hGateEquations\">\n"
        "      <component_ref component=\"importedGateH\"/>\n"
        "    </component_ref>\n"
        "  </encapsulation>\n"
        "</model>\n";

    auto parser = libcellml::Parser::create();

    auto modelUsingImports = parser->parseModel(importingModel);
    auto modelComponentDefinition = parser->parseModel(modelConnectionsParentChild);

    EXPECT_TRUE(modelUsingImports->hasUnresolvedImports());

    auto component = modelUsingImports->component(0)->component(0);
    auto importSource = component->importSource();
    importSource->setModel(modelComponentDefinition);

    EXPECT_FALSE(modelUsingImports->hasUnresolvedImports());

    auto importer = libcellml::Importer::create();

    modelUsingImports = importer->flattenModel(modelUsingImports);
    EXPECT_EQ(size_t(0), modelUsingImports->importSourceCount());

    auto printer = libcellml::Printer::create();

    auto a = printer->printModel(modelUsingImports);
    EXPECT_EQ(e, a);
}

TEST(ModelFlattening, resolveFlattenCircularImportsComponents)
{
    std::string resolveError = "Cyclic dependencies were found when attempting to resolve components in model 'importExample2b'. The dependency loop is:\n"
                               " - component 'sideB' is imported from 'shared' in 'circularImport1.cellml';\n"
                               " - component 'shared' is imported from 'circular2' in 'circularImport2.cellml';\n"
                               " - component 'circular2' is imported from 'shared' in 'circularImport1.cellml'; and\n"
                               " - component 'shared' is imported from 'circular2' in 'circularImport2.cellml'.";
    std::string flattenError = "Cyclic dependencies were found when attempting to flatten components in model 'importExample2b'. The dependency loop is:\n"
                               " - component 'sideB' is imported from 'shared' in 'circularImport1.cellml';\n"
                               " - component 'shared' is imported from 'circular2' in 'circularImport2.cellml';\n"
                               " - component 'circular2' is imported from 'shared' in 'circularImport1.cellml'; and\n"
                               " - component 'shared' is imported from 'circular2' in 'circularImport2.cellml'.";

    auto parser = libcellml::Parser::create();
    auto originalModel = parser->parseModel(fileContents("modelflattening/importExample2b.cellml"));
    auto importer = libcellml::Importer::create();

    auto printer = libcellml::Printer::create();
    std::cout << printer->printModel(originalModel) << std::endl;

    // Resolve the imports.
    importer->resolveImports(originalModel, resourcePath("modelflattening/"));

    // Check for issues: expect one reporting the circular import.
    EXPECT_EQ(size_t(1), importer->issueCount());
    EXPECT_EQ(resolveError, importer->issue(0)->description());

    // Create a flattened version to demonstrate the diagnostics.
    importer->removeAllIssues();
    auto flatModel = importer->flattenModel(originalModel);
    EXPECT_EQ(size_t(1), importer->issueCount());
    EXPECT_EQ(flattenError, importer->issue(0)->description());
    EXPECT_EQ(nullptr, flatModel);
}

TEST(ModelFlattening, resolveFlattenCircularImportsUnits)
{
    std::string resolveError = "Cyclic dependencies were found when attempting to resolve units in model 'importExampleUnits'. The dependency loop is:\n"
                               " - units 'sideB' is imported from 'myChildIsCircular' in 'circularImport1units.cellml';\n"
                               " - units 'shared' is imported from 'circular2' in 'circularImport2units.cellml';\n"
                               " - units 'circular2' is imported from 'shared' in 'circularImport1units.cellml'; and\n"
                               " - units 'shared' is imported from 'circular2' in 'circularImport2units.cellml'.";
    std::string flattenError = "Cyclic dependencies were found when attempting to flatten units in model 'importExampleUnits'. The dependency loop is:\n"
                               " - units 'sideB' is imported from 'myChildIsCircular' in 'circularImport1units.cellml';\n"
                               " - units 'shared' is imported from 'circular2' in 'circularImport2units.cellml';\n"
                               " - units 'circular2' is imported from 'shared' in 'circularImport1units.cellml'; and\n"
                               " - units 'shared' is imported from 'circular2' in 'circularImport2units.cellml'.";

    auto parser = libcellml::Parser::create();
    auto originalModel = parser->parseModel(fileContents("modelflattening/importExampleUnits.cellml"));
    auto importer = libcellml::Importer::create();

    // Resolve the imports.
    importer->resolveImports(originalModel, resourcePath("modelflattening/"));

    // Check for issues: expect one reporting the circular import.
    EXPECT_EQ(size_t(1), importer->issueCount());
    EXPECT_EQ(resolveError, importer->issue(0)->description());

    // Create a flattened version to demonstrate the diagnostics.
    importer->removeAllIssues();
    auto flatModel = importer->flattenModel(originalModel);
    EXPECT_EQ(size_t(1), importer->issueCount());
    EXPECT_EQ(flattenError, importer->issue(0)->description());
    EXPECT_EQ(nullptr, flatModel);
}

TEST(ModelFlattening, resolveFlattenMissingModel)
{
    auto e = "Component 'left' requires a model imported from 'diamond_point.cellml' which is not available in the importer.";
    auto parser = libcellml::Parser::create();
    auto originalModel = parser->parseModel(fileContents("importer/diamond.cellml"));
    auto importer = libcellml::Importer::create();

    // Resolve imports.
    importer->resolveImports(originalModel, resourcePath("importer/"));
    EXPECT_EQ(size_t(0), importer->issueCount());

    // Corrupt the importer library by removing a model that's required.
    importer->replaceModel(nullptr, importer->key(1));

    // Attempt to flatten the model.
    auto flatModel = importer->flattenModel(originalModel);
    EXPECT_EQ(size_t(1), importer->issueCount());
    EXPECT_EQ(e, importer->issue(0)->description());
}

TEST(ModelFlattening, resolveFlattenMissingComponent)
{
    auto e = "Component 'left' imports a component named 'pointyBit' from the model imported from 'diamond_point.cellml'. The component could not be found.";
    auto parser = libcellml::Parser::create();
    auto originalModel = parser->parseModel(fileContents("importer/diamond.cellml"));
    auto importer = libcellml::Importer::create();

    // Resolve imports.
    importer->resolveImports(originalModel, resourcePath("importer/"));
    EXPECT_EQ(size_t(0), importer->issueCount());

    // Corrupt the importer library by removing a component from a model that's required.
    auto pointModel = importer->library(1);
    pointModel->removeComponent("pointyBit");

    // Attempt to flatten the model.
    auto flatModel = importer->flattenModel(originalModel);
    EXPECT_EQ(size_t(1), importer->issueCount());
    EXPECT_EQ(e, importer->issue(0)->description());
}

TEST(ModelFlattening, resolveFlattenMissingUnits)
{
    auto e = "Units 'units1_imported' imports units named 'units1' from the model imported from 'units_source.cellml'. The units could not be found.";
    auto parser = libcellml::Parser::create();
    auto originalModel = parser->parseModel(fileContents("importer/units_imported.cellml"));
    auto importer = libcellml::Importer::create();

    // Resolve imports.
    importer->resolveImports(originalModel, resourcePath("importer/"));
    EXPECT_EQ(size_t(0), importer->issueCount());

    // Corrupt the importer library by renaming units from a model that's required.
    auto importedModel = importer->library(0);
    importedModel->units(0)->setName("someOtherName");

    // Attempt to flatten the model.
    auto flatModel = importer->flattenModel(originalModel);
    EXPECT_EQ(size_t(1), importer->issueCount());
    EXPECT_EQ(e, importer->issue(0)->description());
}

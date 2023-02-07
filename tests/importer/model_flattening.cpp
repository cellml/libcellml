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

TEST(ModelFlattening, invalidInput)
{
    auto importer = libcellml::Importer::create();

    auto flatModel = importer->flattenModel(nullptr);

    EXPECT_EQ(nullptr, flatModel);
    EXPECT_EQ(size_t(1), importer->issueCount());
    EXPECT_EQ("The model is null.", importer->issue(0)->description());
    EXPECT_EQ(libcellml::Issue::ReferenceRule::INVALID_ARGUMENT, importer->issue(0)->referenceRule());
}

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

    auto printer = libcellml::Printer::create();

    auto a = printer->printModel(modelUsingImports);
    EXPECT_EQ(e, a);
}

TEST(ModelFlattening, resolveFlattenCircularImportsComponents)
{
    const std::string resolveError =
        std::string("Cyclic dependencies were found when attempting to resolve a component in the model 'importExample2b'. The dependency loop is:\n")
        + " - component 'sideB' specifies an import from ':this:' to '" + resourcePath("modelflattening/") + "circularImport1.cellml';\n"
        + " - component 'shared' specifies an import from '" + resourcePath("modelflattening/") + "circularImport1.cellml' to '" + resourcePath("modelflattening/") + "circularImport2.cellml'; and\n"
        + " - component 'circular2' specifies an import from '" + resourcePath("modelflattening/") + "circularImport2.cellml' to '" + resourcePath("modelflattening/") + "circularImport1.cellml'.";

    const std::string flattenError =
        std::string("Cyclic dependencies were found when attempting to flatten a component in the model 'importExample2b'. The dependency loop is:\n")
        + " - component 'sideB' specifies an import from ':this:' to '" + resourcePath("modelflattening/") + "circularImport1.cellml';\n"
        + " - component 'shared' specifies an import from '" + resourcePath("modelflattening/") + "circularImport1.cellml' to '" + resourcePath("modelflattening/") + "circularImport2.cellml'; and\n"
        + " - component 'circular2' specifies an import from '" + resourcePath("modelflattening/") + "circularImport2.cellml' to '" + resourcePath("modelflattening/") + "circularImport1.cellml'.";

    auto parser = libcellml::Parser::create();
    auto originalModel = parser->parseModel(fileContents("modelflattening/importExample2b.cellml"));
    auto importer = libcellml::Importer::create();

    // Resolve the imports.
    importer->resolveImports(originalModel, resourcePath("modelflattening/"));

    // Check for issues: expect one reporting the circular import.
    EXPECT_EQ(size_t(1), importer->issueCount());
    EXPECT_EQ(resolveError, importer->issue(0)->description());

    // Create a flattened version to demonstrate the diagnostics.
    auto flatModel = importer->flattenModel(originalModel);
    EXPECT_EQ(size_t(1), importer->issueCount());
    EXPECT_EQ(flattenError, importer->issue(0)->description());
    EXPECT_EQ(nullptr, flatModel);
}

TEST(ModelFlattening, resolveFlattenNonCircularImportsUnits)
{
    auto importer = libcellml::Importer::create();
    auto model = libcellml::Model::create("model");
    auto importModel = libcellml::Model::create("importModel");

    auto unitsWithImportedUnit = libcellml::Units::create("one_imported_unit");
    unitsWithImportedUnit->addUnit("metre");
    unitsWithImportedUnit->addUnit("importedUnit");

    auto fancyUnits = libcellml::Units::create("fancyUnits");
    fancyUnits->addUnit("per_becquerel");

    auto perBecquerel = libcellml::Units::create("per_becquerel");
    perBecquerel->addUnit(libcellml::Units::StandardUnit::BECQUEREL, -1.0);

    importModel->addUnits(fancyUnits);
    importModel->addUnits(perBecquerel);

    auto importSource = libcellml::ImportSource::create();
    importSource->setUrl("here.cellml");
    importSource->setModel(importModel);

    auto importedUnit = libcellml::Units::create("importedUnit");
    importedUnit->setImportReference("fancyUnits");
    importedUnit->setImportSource(importSource);

    model->addUnits(unitsWithImportedUnit);
    model->addUnits(importedUnit);

    EXPECT_FALSE(model->hasUnresolvedImports());

    auto flatModel = importer->flattenModel(model);
    EXPECT_EQ(size_t(0), importer->issueCount());
}

TEST(ModelFlattening, resolveFlattenCircularImportsUnits)
{
    const std::string resolveError =
        std::string("Cyclic dependencies were found when attempting to resolve units in the model 'importExampleUnits'. The dependency loop is:\n")
        + " - units 'sideB' specifies an import from ':this:' to '" + resourcePath("modelflattening/") + "circularImport1units.cellml';\n"
        + " - units 'shared' specifies an import from '" + resourcePath("modelflattening/") + "circularImport1units.cellml' to '" + resourcePath("modelflattening/") + "circularImport2units.cellml'; and\n"
        + " - units 'circular2' specifies an import from '" + resourcePath("modelflattening/") + "circularImport2units.cellml' to '" + resourcePath("modelflattening/") + "circularImport1units.cellml'.";

    const std::string flattenError =
        std::string("Cyclic dependencies were found when attempting to flatten units in the model 'importExampleUnits'. The dependency loop is:\n")
        + " - units 'sideB' specifies an import from ':this:' to '" + resourcePath("modelflattening/") + "circularImport1units.cellml';\n"
        + " - units 'shared' specifies an import from '" + resourcePath("modelflattening/") + "circularImport1units.cellml' to '" + resourcePath("modelflattening/") + "circularImport2units.cellml'; and\n"
        + " - units 'circular2' specifies an import from '" + resourcePath("modelflattening/") + "circularImport2units.cellml' to '" + resourcePath("modelflattening/") + "circularImport1units.cellml'.";

    auto parser = libcellml::Parser::create();
    auto originalModel = parser->parseModel(fileContents("modelflattening/importExampleUnits.cellml"));
    auto importer = libcellml::Importer::create();

    // Resolve the imports.
    importer->resolveImports(originalModel, resourcePath("modelflattening/"));

    // Check for issues: expect one reporting the circular import.
    EXPECT_EQ(size_t(1), importer->issueCount());
    EXPECT_EQ(resolveError, importer->issue(0)->description());

    // Create a flattened version to demonstrate the diagnostics.
    auto flatModel = importer->flattenModel(originalModel);
    EXPECT_EQ(size_t(1), importer->issueCount());
    EXPECT_EQ(flattenError, importer->issue(0)->description());
    EXPECT_EQ(nullptr, flatModel);
}

TEST(ModelFlattening, resolveFlattenMissingModel)
{
    const std::string expectedError = "Component 'left' requires a model imported from 'diamond_point.cellml' which is not available in the importer.";
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
    EXPECT_EQ(expectedError, importer->issue(0)->description());
}

TEST(ModelFlattening, resolveFlattenMissingComponent)
{
    const std::string e =
        "Component 'left' imports a component named 'pointyBit' from the model imported from '" + resourcePath("importer/") + "diamond_point.cellml'. The component could not be found.";
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
    const std::string e =
        "Units 'units1_imported' imports units named 'units1' from the model imported from '" + resourcePath("importer/") + "units_source.cellml'. The units could not be found.";
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

TEST(ModelFlattening, importSameUnitsMultipleTimes)
{
    auto importer = libcellml::Importer::create();

    auto model = libcellml::Model::create("model");
    auto modelDefinitions = libcellml::Model::create("definitions");
    auto importModel1 = libcellml::Model::create("importModel1");
    auto importModel2 = libcellml::Model::create("importModel2");

    auto metresPerSecondUnits = libcellml::Units::create("metres_per_second");
    metresPerSecondUnits->addUnit("metre");
    metresPerSecondUnits->addUnit("second", -1.0);

    modelDefinitions->addUnits(metresPerSecondUnits);

    auto modelUnits = libcellml::Units::create("m_p_s");
    modelUnits->addUnit("metres_per_second");

    auto importedUnitsDefinitions = libcellml::Units::create("metres_per_second");

    auto importedUnits1 = libcellml::Units::create("mps");
//    importedUnits1->addUnit("metres_per_second");

    auto importedUnits2 = libcellml::Units::create("m_per_s");
//    importedUnits2->addUnit("metres_per_second");

    auto printer = libcellml::Printer::create();

    model->addUnits(modelUnits);
//    importModel1->addUnits(modelUnits->clone());
    auto b = importedUnits1->clone();
    b->addUnit("metres_per_second");
    importModel1->addUnits(b);
    importModel1->addUnits(importedUnitsDefinitions);
//    importModel2->addUnits(modelUnits->clone());
    auto a = importedUnits2->clone();
    a->addUnit("metres_per_second");
    importModel2->addUnits(a);
    importModel2->addUnits(importedUnitsDefinitions);

    auto importSourceDefinitions = libcellml::ImportSource::create();
    importSourceDefinitions->setUrl("modelDefinitions.cellml");
    importSourceDefinitions->setModel(modelDefinitions);

    importedUnitsDefinitions->setImportSource(importSourceDefinitions);
    importedUnitsDefinitions->setImportReference("metres_per_second");

    auto importSource1 = libcellml::ImportSource::create();
    importSource1->setUrl("model1.cellml");
    importSource1->setModel(importModel1);

    importedUnits1->setImportSource(importSource1);
    importedUnits1->setImportReference("mps");

    auto importSource2 = libcellml::ImportSource::create();
    importSource2->setUrl("model2.cellml");
    importSource2->setModel(importModel2);

    importedUnits2->setImportSource(importSource2);
    importedUnits2->setImportReference("m_per_s");

    model->addUnits(importedUnits1);
    model->addUnits(importedUnits2);
    model->addUnits(importedUnitsDefinitions);
//    model->addUnits(mps1);
//    model->addUnits(mps2);
    auto v = libcellml::Validator::create();
    v->validateModel(model);
    printIssues(v);

    Debug() << printer->printModel(model);
    EXPECT_FALSE(model->hasUnresolvedImports());

    auto flatModel = importer->flattenModel(model);
    EXPECT_EQ(size_t(0), importer->issueCount());

    Debug() << printer->printModel(flatModel);
}

TEST(Coverage, proposedImportedUnitsAlreadyDefinedInModel)
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

    auto u = libcellml::Units::create("common_units_1");
    u->addUnit(libcellml::Units::StandardUnit::SECOND, libcellml::Units::Prefix::HECTO);
    model->addUnits(u);

    EXPECT_TRUE(model->hasUnresolvedImports());
    importer->resolveImports(model, resourcePath("modelflattening/"));
    EXPECT_FALSE(model->hasUnresolvedImports());

    model = importer->flattenModel(model);

    auto printer = libcellml::Printer::create();

    auto a = printer->printModel(model);
    EXPECT_EQ(e, a);
}

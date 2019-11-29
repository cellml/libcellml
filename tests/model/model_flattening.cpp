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

    EXPECT_FALSE(modelUnitsDefinitions->hasUnresolvedImports());

    modelUnitsDefinitions->flatten();

    auto printer = libcellml::Printer::create();

    auto a = printer->printModel(modelUnitsDefinitions);
    EXPECT_EQ(e, a);
}

TEST(ModelFlattening, modelWithUnresolvedImports)
{
    const std::string e = "";

    const std::string modelImportingUnits =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/2.0#\" name=\"importer_of_units\">\n"
        "  <import xlink:href=\"unitsdefinitions.xml\" xmlns:xlink=\"http://www.w3.org/1999/xlink\">\n"
        "    <units units_ref=\"ms\" name=\"my_ms\"/>\n"
        "  </import>\n"
        "</model>\n";

    auto parser = libcellml::Parser::create();
    auto modelWithUnitsImports = parser->parseModel(modelImportingUnits);

    EXPECT_TRUE(modelWithUnitsImports->hasUnresolvedImports());

    modelWithUnitsImports->flatten();

    auto printer = libcellml::Printer::create();

    auto a = printer->printModel(modelWithUnitsImports);
    EXPECT_EQ(modelImportingUnits, a);
}

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

    // Check that we haven't changed the imported model.
    auto aModelUnitsDefinitions = printer->printModel(modelUnitsDefinitions);
    auto eModelUnitsDefinitions = printer->printModel(parser->parseModel(unitsDefiniitonModel));
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


    EXPECT_TRUE(model->hasUnresolvedImports());
    model->resolveImports(resourcePath("modelflattening/"));
    EXPECT_FALSE(model->hasUnresolvedImports());

    // Want to make sure that we haven't damaged the import model after flattening.
    auto importModel = model->component(0)->component(0)->importSource()->model();

    model->flatten();

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


    EXPECT_TRUE(model->hasUnresolvedImports());
    model->resolveImports(resourcePath("modelflattening/"));
    EXPECT_FALSE(model->hasUnresolvedImports());

    // Want to make sure that we haven't damaged the import model after flattening.
    auto importModel = model->component(0)->component(0)->importSource()->model();

    model->flatten();

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


    EXPECT_TRUE(model->hasUnresolvedImports());
    model->resolveImports(resourcePath("modelflattening/"));
    EXPECT_FALSE(model->hasUnresolvedImports());

    model->flatten();

    auto printer = libcellml::Printer::create();

    auto a = printer->printModel(model);
    EXPECT_EQ(e, a);
}

/*
TEST(ModelFlattening, importedComponentUsingUnitsDefinedInImportedModel)
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
    auto model = parser->parseModel(fileContents("modelflattening/equivalentimportedvariable.xml"));

    EXPECT_TRUE(model->hasUnresolvedImports());
    model->resolveImports(resourcePath("modelflattening/"));
    EXPECT_FALSE(model->hasUnresolvedImports());

    model->flatten();

    auto printer = libcellml::Printer::create();

    auto a = printer->printModel(model);
//    EXPECT_EQ(e, a);
}

TEST(ModelFlattening, importedComponentWithEquivalentVariablesOutsideTheComponent)
{
    const std::string e = "";
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("modelflattening/equivalentimportedvariable.xml"));

    EXPECT_TRUE(model->hasUnresolvedImports());
    model->resolveImports(resourcePath("modelflattening/"));
    EXPECT_FALSE(model->hasUnresolvedImports());

    model->flatten();

    auto printer = libcellml::Printer::create();

    auto a = printer->printModel(model);
//    EXPECT_EQ(e, a);
}

TEST(ModelFlattening, importedComponentUsingImportedUnits)
{
    const std::string e = "";
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("modelflattening/equivalentimportedvariable.xml"));

    EXPECT_TRUE(model->hasUnresolvedImports());
    model->resolveImports(resourcePath("modelflattening/"));
    EXPECT_FALSE(model->hasUnresolvedImports());

    model->flatten();

    auto printer = libcellml::Printer::create();

    auto a = printer->printModel(model);
//    EXPECT_EQ(e, a);
}

TEST(ModelFlattening, importedComponentUsingImportedComponent)
{
    const std::string e = "";
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("modelflattening/equivalentimportedvariable.xml"));

    EXPECT_TRUE(model->hasUnresolvedImports());
    model->resolveImports(resourcePath("modelflattening/"));
    EXPECT_FALSE(model->hasUnresolvedImports());

    model->flatten();

    auto printer = libcellml::Printer::create();

    auto a = printer->printModel(model);
//    EXPECT_EQ(e, a);
}

TEST(ModelFlattening, multipleImportedUnits)
{
    const std::string e = "";
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("modelflattening/equivalentimportedvariable.xml"));

    EXPECT_TRUE(model->hasUnresolvedImports());
    model->resolveImports(resourcePath("modelflattening/"));
    EXPECT_FALSE(model->hasUnresolvedImports());

    model->flatten();

    auto printer = libcellml::Printer::create();

    auto a = printer->printModel(model);
//    EXPECT_EQ(e, a);
}

TEST(ModelFlattening, multipleImportedComponents)
{
    const std::string e = "";
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("modelflattening/equivalentimportedvariable.xml"));

    EXPECT_TRUE(model->hasUnresolvedImports());
    model->resolveImports(resourcePath("modelflattening/"));
    EXPECT_FALSE(model->hasUnresolvedImports());

    model->flatten();

    auto printer = libcellml::Printer::create();

    auto a = printer->printModel(model);
//    EXPECT_EQ(e, a);
}

TEST(ModelFlattening, importedComponentWithNameClashes)
{
    const std::string e = "";
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("modelflattening/equivalentimportedvariable.xml"));

    EXPECT_TRUE(model->hasUnresolvedImports());
    model->resolveImports(resourcePath("modelflattening/"));
    EXPECT_FALSE(model->hasUnresolvedImports());

    model->flatten();

    auto printer = libcellml::Printer::create();

    auto a = printer->printModel(model);
//    EXPECT_EQ(e, a);
}

TEST(ModelFlattening, importedUnitsWithNameClashes)
{
    const std::string e = "";
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("modelflattening/equivalentimportedvariable.xml"));

    EXPECT_TRUE(model->hasUnresolvedImports());
    model->resolveImports(resourcePath("modelflattening/"));
    EXPECT_FALSE(model->hasUnresolvedImports());

    model->flatten();

    auto printer = libcellml::Printer::create();

    auto a = printer->printModel(model);
//    EXPECT_EQ(e, a);
}
*/

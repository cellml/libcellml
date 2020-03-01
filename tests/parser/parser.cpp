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

#include <algorithm>
#include <string>
#include <vector>

TEST(Parser, invalidXMLElements)
{
    const std::string input =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<fellowship>\n"
        "  <Dwarf bearded>Gimli</ShortGuy>\n"
        "  <Hobbit>Frodo</EvenShorterGuy>\n"
        "  <Wizard>Gandalf</SomeGuyWithAStaff>\n"
        "  <Elf>\n"
        "</fellows>\n";
    const std::vector<std::string> expectedErrors = {
        "Specification mandate value for attribute bearded.",
        "Specification mandates value for attribute bearded.",
        "LibXml2 error: Opening and ending tag mismatch: Dwarf line 3 and ShortGuy.",
        "LibXml2 error: Opening and ending tag mismatch: Hobbit line 4 and EvenShorterGuy.",
        "LibXml2 error: Opening and ending tag mismatch: Wizard line 5 and SomeGuyWithAStaff.",
        "LibXml2 error: Opening and ending tag mismatch: Elf line 6 and fellows.",
        "LibXml2 error: Premature end of data in tag fellowship line 2.",
        "Could not get a valid XML root node from the provided input.",
    };

    libcellml::ParserPtr p = libcellml::Parser::create();
    p->parseModel(input);

    EXPECT_EQ(expectedErrors.size() - 1, p->errorCount());
    for (size_t i = 0; i < p->errorCount(); ++i) {
        if (i == 0) {
            EXPECT_TRUE((p->error(i)->description() != expectedErrors.at(0))
                        || (p->error(i)->description() != expectedErrors.at(1)));
        } else {
            EXPECT_EQ(expectedErrors.at(i + 1), p->error(i)->description());
        }
    }
}

TEST(Parser, parse)
{
    const std::string e =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/2.0#\"/>\n";

    libcellml::ParserPtr parser = libcellml::Parser::create();
    libcellml::ModelPtr model = parser->parseModel(e);
    libcellml::PrinterPtr printer = libcellml::Printer::create();
    const std::string a = printer->printModel(model);
    EXPECT_EQ(e, a);
}

TEST(Parser, parseNamedModel)
{
    const std::string n = "name";
    const std::string e =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/2.0#\" name=\"name\"/>\n";

    libcellml::ParserPtr parser = libcellml::Parser::create();
    libcellml::ModelPtr model = parser->parseModel(e);
    EXPECT_EQ(n, model->name());

    libcellml::PrinterPtr printer = libcellml::Printer::create();
    const std::string a = printer->printModel(model);
    EXPECT_EQ(e, a);
}

TEST(Parser, makeError)
{
    const std::string ex;

    libcellml::ErrorPtr e = libcellml::Error::create();

    EXPECT_EQ(ex, e->description());
}

TEST(Parser, emptyModelString)
{
    const std::string e;
    const std::vector<std::string> expectedErrors = {
        "Model is empty.",
    };

    libcellml::ParserPtr p = libcellml::Parser::create();
    p->parseModel(e);
    EXPECT_EQ_ERRORS(expectedErrors, p);
}

TEST(Parser, nonXmlString)
{
    const std::string ex = "Not an xml string.";
    const std::vector<std::string> expectedErrors = {
        "LibXml2 error: Start tag expected, '<' not found.",
        "Could not get a valid XML root node from the provided input.",
    };

    libcellml::ParserPtr p = libcellml::Parser::create();
    p->parseModel(ex);
    EXPECT_EQ_ERRORS(expectedErrors, p);
}

TEST(Parser, invalidRootNode)
{
    const std::string ex =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<yodel xmlns=\"http://www.cellml.org/cellml/2.0#\" name=\"model_name\">\n"
        "</yodel>\n";
    const std::vector<std::string> expectedErrors = {
        "Model element is of invalid type 'yodel'. A valid CellML root node should be of type 'model'.",
    };

    libcellml::ParserPtr p = libcellml::Parser::create();
    p->parseModel(ex);
    EXPECT_EQ_ERRORS(expectedErrors, p);
}

TEST(Parser, noModelNamespace)
{
    const std::string ex =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model/>\n";
    const std::vector<std::string> expectedErrors = {
        "Model element is in invalid namespace 'null'. A valid CellML root node should be in namespace 'http://www.cellml.org/cellml/2.0#'.",
    };

    libcellml::ParserPtr p = libcellml::Parser::create();
    p->parseModel(ex);
    EXPECT_EQ_ERRORS(expectedErrors, p);
}

TEST(Parser, invalidModelNamespace)
{
    const std::string ex =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/1.2#\"/>\n";
    const std::vector<std::string> expectedErrors = {
        "Model element is in invalid namespace 'http://www.cellml.org/cellml/1.2#'. A valid CellML root node should be in namespace 'http://www.cellml.org/cellml/2.0#'.",
    };

    libcellml::ParserPtr p = libcellml::Parser::create();
    p->parseModel(ex);
    EXPECT_EQ_ERRORS(expectedErrors, p);
}

TEST(Parser, invalidModelAttribute)
{
    const std::string ex =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/2.0#\" game=\"model_name\"/>\n";
    const std::vector<std::string> expectedErrors = {
        "Model '' has an invalid attribute 'game'.",
    };

    libcellml::ParserPtr p = libcellml::Parser::create();
    p->parseModel(ex);
    EXPECT_EQ_ERRORS(expectedErrors, p);
}

TEST(Parser, invalidModelElement)
{
    const std::string ex =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/2.0#\" name=\"model_name\">\n"
        "  <uknits/>\n"
        "</model>\n";
    const std::vector<std::string> expectedErrors = {
        "Model 'model_name' has an invalid child element 'uknits'.",
    };

    libcellml::ParserPtr p = libcellml::Parser::create();
    p->parseModel(ex);
    EXPECT_EQ_ERRORS(expectedErrors, p);
}

TEST(Parser, modelWithInvalidElement)
{
    const std::string input1 =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/2.0#\" name=\"bilbo\">\n"
        "  <hobbit/>\n"
        "</model>\n";
    const std::vector<std::string> expectedErrors1 = {
        "Model 'bilbo' has an invalid child element 'hobbit'.",
    };
    const std::string input2 =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/2.0#\">\n"
        "  <hobbit/>\n"
        "</model>\n";
    const std::vector<std::string> expectedErrors2 = {
        "Model '' has an invalid child element 'hobbit'.",
    };

    libcellml::ParserPtr p = libcellml::Parser::create();
    p->parseModel(input1);
    EXPECT_EQ_ERRORS(expectedErrors1, p);

    p->removeAllErrors();
    p->parseModel(input2);
    EXPECT_EQ_ERRORS(expectedErrors2, p);
}

TEST(Parser, parseModelWithInvalidAttributeAndGetError)
{
    const std::string input =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/2.0#\" name=\"modelName\" nonsense=\"oops\"/>\n";
    const std::vector<std::string> expectedErrors = {
        "Model 'modelName' has an invalid attribute 'nonsense'.",
    };

    libcellml::ParserPtr parser = libcellml::Parser::create();
    libcellml::ModelPtr model = parser->parseModel(input);

    EXPECT_EQ_ERRORS(expectedErrors, parser);

    // Get ModelError and check.
    EXPECT_EQ(model, parser->error(0)->model());
    // Get const modelError and check.
    const libcellml::ErrorPtr err = parser->error(0);
    libcellml::Error *rawErr = err.get();
    const libcellml::ModelPtr modelFromError = rawErr->model();
    EXPECT_EQ(model, modelFromError);
}

TEST(Parser, parseNamedModelWithNamedComponent)
{
    const std::string mName = "modelName";
    const std::string cName = "componentName";
    const std::string e =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/2.0#\" name=\"modelName\">\n"
        "  <component name=\"componentName\"/>\n"
        "</model>\n";

    libcellml::ParserPtr parser = libcellml::Parser::create();
    libcellml::ModelPtr model = parser->parseModel(e);
    EXPECT_EQ(mName, model->name());
    libcellml::ComponentPtr c = model->component(cName);
    EXPECT_EQ(cName, c->name());

    libcellml::PrinterPtr printer = libcellml::Printer::create();
    const std::string a = printer->printModel(model);
    EXPECT_EQ(e, a);
}

TEST(Parser, parseModelWithUnitsAndNamedComponent)
{
    const std::string in =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/2.0#\" name=\"model_name\">\n"
        "  <units name=\"fahrenheitish\">\n"
        "    <unit multiplier=\"1.8\" units=\"kelvin\"/>\n"
        "  </units>\n"
        "  <units name=\"dimensionless\"/>\n"
        "  <component name=\"component_name\"/>\n"
        "</model>\n";
    const std::string e =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/2.0#\" name=\"model_name\">\n"
        "  <units name=\"fahrenheitish\">\n"
        "    <unit multiplier=\"1.8\" units=\"kelvin\"/>\n"
        "  </units>\n"
        "  <component name=\"component_name\"/>\n"
        "</model>\n";

    libcellml::ParserPtr parser = libcellml::Parser::create();
    libcellml::ModelPtr model = parser->parseModel(in);

    libcellml::PrinterPtr printer = libcellml::Printer::create();
    const std::string a = printer->printModel(model);
    EXPECT_EQ(e, a);
}

TEST(Parser, unitsAttributeError)
{
    const std::string e =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/2.0#\" name=\"model_name\">\n"
        "  <units name=\"pH\" invalid_attribute=\"yes\"/>\n"
        "</model>\n";
    const std::vector<std::string> expectedErrors = {
        "Units 'pH' has an invalid attribute 'invalid_attribute'.",
    };

    libcellml::ParserPtr p = libcellml::Parser::create();
    p->parseModel(e);
    EXPECT_EQ_ERRORS(expectedErrors, p);
}

TEST(Parser, unitsElementErrors)
{
    const std::string input1 =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/2.0#\" name=\"model_name\">\n"
        "  <units>\n"
        "    <son name=\"stan\"/>\n"
        "  </units>\n"
        "</model>\n";
    const std::vector<std::string> expectedErrors1 = {
        "Units '' has an invalid child element 'son'.",
    };
    const std::string input2 =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/2.0#\" name=\"model_name\">\n"
        "  <units name=\"randy\">\n"
        "    <son name=\"stan\"/>\n"
        "  </units>\n"
        "</model>\n";
    const std::vector<std::string> expectedErrors2 = {
        "Units 'randy' has an invalid child element 'son'.",
    };

    libcellml::ParserPtr p = libcellml::Parser::create();
    p->parseModel(input1);
    EXPECT_EQ_ERRORS(expectedErrors1, p);

    p->removeAllErrors();
    p->parseModel(input2);
    EXPECT_EQ_ERRORS(expectedErrors2, p);
}

TEST(Parser, parseModelWithNamedComponentWithInvalidBaseUnitsAttributeAndGetError)
{
    const std::string in =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/2.0#\" name=\"model_name\">\n"
        "  <units name=\"unit_name\" base_unit=\"yes\"/>\n"
        "  <component name=\"component_name\">\n"
        "  </component>\n"
        "</model>\n";
    const std::vector<std::string> expectedErrors = {
        "Units 'unit_name' has an invalid attribute 'base_unit'.",
    };

    libcellml::ParserPtr parser = libcellml::Parser::create();
    libcellml::ModelPtr model = parser->parseModel(in);

    EXPECT_EQ_ERRORS(expectedErrors, parser);

    libcellml::UnitsPtr unitsExpected = model->units("unit_name");

    // Get units from error and check.
    EXPECT_EQ(unitsExpected, parser->error(0)->units());

    // Get const units from error and check.
    const libcellml::ErrorPtr err = parser->error(0);
    const libcellml::UnitsPtr unitsFromError = err->units();
    EXPECT_EQ(unitsExpected, unitsFromError);
}

TEST(Parser, parseModelWithInvalidComponentAttributeAndGetError)
{
    const std::string cName = "componentName";
    const std::string input =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/2.0#\" name=\"modelName\">\n"
        "  <component name=\"componentName\" nonsense=\"oops\"/>\n"
        "</model>\n";
    const std::vector<std::string> expectedErrors = {
        "Component 'componentName' has an invalid attribute 'nonsense'.",
    };

    libcellml::ParserPtr parser = libcellml::Parser::create();
    libcellml::ModelPtr model = parser->parseModel(input);
    libcellml::ComponentPtr component = model->component(cName);

    EXPECT_EQ_ERRORS(expectedErrors, parser);

    // Get component from error and check.
    EXPECT_EQ(component, parser->error(0)->component());
    // Get const component from error and check.
    const libcellml::ErrorPtr err = parser->error(0);
    libcellml::Error *rawErr = err.get();
    const libcellml::ComponentPtr componentFromError = rawErr->component();
    EXPECT_EQ(component, componentFromError);

    // Get non-existent error
    EXPECT_EQ(nullptr, parser->error(1));
}

TEST(Parser, componentAttributeErrors)
{
    const std::string input1 =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/2.0#\" name=\"model_name\">\n"
        "  <component lame=\"randy\"/>\n"
        "</model>\n";
    const std::vector<std::string> expectedErrors1 = {
        "Component '' has an invalid attribute 'lame'.",
    };
    const std::string input2 =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/2.0#\" name=\"model_name\">\n"
        "  <component name=\"randy\" son=\"stan\"/>\n"
        "</model>\n";
    const std::vector<std::string> expectedErrors2 = {
        "Component 'randy' has an invalid attribute 'son'.",
    };
    const std::string input3 =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/2.0#\" name=\"model_name\">\n"
        "  <component son=\"stan\" name=\"randy\"/>\n"
        "</model>\n";
    const std::vector<std::string> expectedErrors3 = {
        "Component 'randy' has an invalid attribute 'son'.",
    };

    libcellml::ParserPtr p = libcellml::Parser::create();
    p->parseModel(input1);
    EXPECT_EQ_ERRORS(expectedErrors1, p);

    p->removeAllErrors();
    p->parseModel(input2);
    EXPECT_EQ_ERRORS(expectedErrors2, p);

    p->removeAllErrors();
    p->parseModel(input3);
    EXPECT_EQ_ERRORS(expectedErrors3, p);
}

TEST(Parser, componentElementErrors)
{
    const std::string input1 =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/2.0#\" name=\"model_name\">\n"
        "  <component>\n"
        "    <son name=\"stan\"/>\n"
        "  </component>\n"
        "</model>\n";
    const std::string expectError1 = "Component '' has an invalid child element 'son'.";
    const std::string input2 =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/2.0#\" name=\"model_name\">\n"
        "  <component name=\"randy\">\n"
        "    <son name=\"stan\"/>\n"
        "  </component>\n"
        "</model>\n";
    const std::string expectError2 = "Component 'randy' has an invalid child element 'son'.";

    libcellml::ParserPtr p = libcellml::Parser::create();
    p->parseModel(input1);
    EXPECT_EQ(size_t(1), p->errorCount());
    EXPECT_EQ(expectError1, p->error(0)->description());

    p->removeAllErrors();
    p->parseModel(input2);
    EXPECT_EQ(size_t(1), p->errorCount());
    EXPECT_EQ(expectError2, p->error(0)->description());
}

TEST(Parser, parseModelWithTwoComponents)
{
    const std::string e =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/2.0#\" name=\"modelName\">\n"
        "  <component name=\"component1\"/>\n"
        "  <component name=\"component2\"/>\n"
        "</model>\n";

    libcellml::ParserPtr parser = libcellml::Parser::create();
    libcellml::ModelPtr model = parser->parseModel(e);

    libcellml::PrinterPtr printer = libcellml::Printer::create();
    const std::string a = printer->printModel(model);
    EXPECT_EQ(e, a);
}

TEST(Parser, parseModelWithComponentHierarchyWaterfall)
{
    const std::string e =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/2.0#\">\n"
        "  <component name=\"dave\"/>\n"
        "  <component name=\"bob\"/>\n"
        "  <component name=\"angus\"/>\n"
        "  <encapsulation>\n"
        "    <component_ref component=\"dave\">\n"
        "      <component_ref component=\"bob\">\n"
        "        <component_ref component=\"angus\"/>\n"
        "      </component_ref>\n"
        "    </component_ref>\n"
        "  </encapsulation>\n"
        "</model>\n";

    libcellml::ParserPtr parser = libcellml::Parser::create();
    libcellml::ModelPtr model = parser->parseModel(e);

    libcellml::PrinterPtr printer = libcellml::Printer::create();
    const std::string a = printer->printModel(model);
    EXPECT_EQ(e, a);
}

TEST(Parser, parseModelWithMultipleComponentHierarchyWaterfalls)
{
    const std::string e =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/2.0#\">\n"
        "  <component name=\"ignatio\"/>\n"
        "  <component name=\"dave\"/>\n"
        "  <component name=\"bob\"/>\n"
        "  <component name=\"angus\"/>\n"
        "  <component name=\"jackie\"/>\n"
        "  <component name=\"mildred\"/>\n"
        "  <component name=\"sue\"/>\n"
        "  <encapsulation>\n"
        "    <component_ref component=\"dave\">\n"
        "      <component_ref component=\"bob\">\n"
        "        <component_ref component=\"angus\"/>\n"
        "        <component_ref component=\"jackie\"/>\n"
        "      </component_ref>\n"
        "    </component_ref>\n"
        "    <component_ref component=\"mildred\">\n"
        "      <component_ref component=\"sue\"/>\n"
        "    </component_ref>\n"
        "  </encapsulation>\n"
        "</model>\n";

    libcellml::ParserPtr parser = libcellml::Parser::create();
    libcellml::ModelPtr model = parser->parseModel(e);

    libcellml::PrinterPtr printer = libcellml::Printer::create();
    const std::string a = printer->printModel(model);
    EXPECT_EQ(e, a);
}

TEST(Parser, modelWithUnits)
{
    const std::string in =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/2.0#\" name=\"model_name\">\n"
        "  <units name=\"fahrenheitish\">\n"
        "    <unit multiplier=\"1.8\" units=\"kelvin\"/>\n"
        "  </units>\n"
        "  <units name=\"dimensionless\"/>\n"
        "</model>\n";
    const std::string e =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/2.0#\" name=\"model_name\">\n"
        "  <units name=\"fahrenheitish\">\n"
        "    <unit multiplier=\"1.8\" units=\"kelvin\"/>\n"
        "  </units>\n"
        "</model>\n";

    libcellml::ParserPtr parser = libcellml::Parser::create();
    libcellml::ModelPtr model = parser->parseModel(in);

    libcellml::PrinterPtr printer = libcellml::Printer::create();
    const std::string a = printer->printModel(model);
    EXPECT_EQ(e, a);
}

TEST(Parser, modelWithInvalidUnits)
{
    const std::string in =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/2.0#\" name=\"model_name\">\n"
        "  <units name=\"fahrenheitish\" temperature=\"451\">\n"
        "    <unit multiplier=\"Z\" exponent=\"35.0E+310\" units=\"kelvin\" bill=\"murray\">\n"
        "      <degrees/>\n"
        "    </unit>\n"
        "    <bobshouse address=\"34 Rich Lane\"/>\n"
        "    <unit GUnit=\"50c\"/>\n"
        "  </units>\n"
        "  <units name=\"dimensionless\"/>\n"
        "  <units jerry=\"seinfeld\">\n"
        "    <unit units=\"friends\" neighbor=\"kramer\"/>\n"
        "    <unit george=\"friends\"/>\n"
        "  </units>\n"
        "</model>\n";
    const std::string e =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/2.0#\" name=\"model_name\">\n"
        "  <units name=\"fahrenheitish\">\n"
        "    <unit exponent=\"inf\" units=\"kelvin\"/>\n"
        "    <unit units=\"\"/>\n"
        "  </units>\n"
        "  <units>\n"
        "    <unit units=\"friends\"/>\n"
        "    <unit units=\"\"/>\n"
        "  </units>\n"
        "</model>\n";

    const std::vector<std::string> expectedErrors = {
        "Units 'fahrenheitish' has an invalid attribute 'temperature'.",
        "Unit referencing 'kelvin' in units 'fahrenheitish' has an invalid child element 'degrees'.",
        "Unit referencing 'kelvin' in units 'fahrenheitish' has a multiplier with the value 'Z' that is not a representation of a CellML real valued number.",
        "Unit referencing 'kelvin' in units 'fahrenheitish' has an invalid attribute 'bill'.",
        "Units 'fahrenheitish' has an invalid child element 'bobshouse'.",
        "Unit referencing '' in units 'fahrenheitish' has an invalid attribute 'GUnit'.",
        "Units '' has an invalid attribute 'jerry'.",
        "Unit referencing 'friends' in units '' has an invalid attribute 'neighbor'.",
        "Unit referencing '' in units '' has an invalid attribute 'george'.",
    };

    libcellml::ParserPtr parser = libcellml::Parser::create();
    libcellml::ModelPtr model = parser->parseModel(in);

    EXPECT_EQ_ERRORS(expectedErrors, parser);

    libcellml::PrinterPtr printer = libcellml::Printer::create();
    const std::string a = printer->printModel(model);
    EXPECT_EQ(e, a);
}

TEST(Parser, emptyEncapsulation)
{
    const std::string ex =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/2.0#\" name=\"model_name\">\n"
        "  <encapsulation/>\n"
        "</model>\n";

    const std::vector<std::string> expectedErrors = {
        "Encapsulation in model 'model_name' does not contain any child elements.",
    };

    libcellml::ParserPtr p = libcellml::Parser::create();
    p->parseModel(ex);
    EXPECT_EQ_ERRORS(expectedErrors, p);
}

TEST(Parser, validEncapsulation)
{
    const std::string ex =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/2.0#\" name=\"model_name\">\n"
        "  <component name=\"bob\"/>\n"
        "  <component name=\"jim\"/>\n"
        "  <encapsulation>\n"
        "    <component_ref component=\"bob\">\n"
        "      <component_ref component=\"jim\">\n"
        "      </component_ref>\n"
        "    </component_ref>\n"
        "  </encapsulation>\n"
        "</model>\n";

    libcellml::ParserPtr p = libcellml::Parser::create();
    p->parseModel(ex);

    EXPECT_EQ(size_t(0), p->errorCount());
}

TEST(Parser, encapsulationWithCycleDefined)
{
    const std::string ex =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/2.0#\" name=\"model_name\">\n"
        "  <component name=\"bob\"/>\n"
        "  <component name=\"jim\"/>\n"
        "  <component name=\"dave\"/>\n"
        "  <component name=\"bob\"/>\n"
        "  <encapsulation>\n"
        "    <component_ref component=\"bob\">\n"
        "      <component_ref component=\"jim\">\n"
        "        <component_ref component=\"dave\">\n"
        "          <component_ref component=\"bob\"/>\n"
        "        </component_ref>\n"
        "      </component_ref>\n"
        "    </component_ref>\n"
        "  </encapsulation>\n"
        "</model>\n";

    const std::vector<std::string> expectedErrors = {
        "Model 'model_name' contains multiple components with the name 'bob'. Valid component names must be unique to their model.",
    };

    libcellml::ParserPtr p = libcellml::Parser::create();
    auto m = p->parseModel(ex);

    EXPECT_EQ(size_t(0), p->errorCount());

    libcellml::PrinterPtr printer = libcellml::Printer::create();
    auto output = printer->printModel(m);
    EXPECT_EQ(output, ex);

    libcellml::ValidatorPtr v = libcellml::Validator::create();
    v->validateModel(m);

    EXPECT_EQ_ERRORS(expectedErrors, v);
}

TEST(Parser, encapsulationWithNoComponentAttribute)
{
    const std::string ex =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/2.0#\" name=\"model_name\">\n"
        "  <encapsulation>\n"
        "    <component_ref/>\n"
        "  </encapsulation>\n"
        "</model>\n";

    const std::vector<std::string> expectedErrors = {
        "Encapsulation in model 'model_name' does not have a valid component attribute in a component_ref element.",
        "Encapsulation in model 'model_name' specifies an invalid parent component_ref that also does not have any children.",
    };

    libcellml::ParserPtr p = libcellml::Parser::create();
    p->parseModel(ex);

    EXPECT_EQ_ERRORS(expectedErrors, p);
}

TEST(Parser, encapsulationWithNoComponentRef)
{
    const std::vector<std::string> expectedErrors = {
        "Encapsulation in model 'model_name' has an invalid child element 'component_free'.",
    };

    const std::string ex =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/2.0#\" name=\"model_name\">\n"
        "  <encapsulation>\n"
        "    <component_free/>\n"
        "  </encapsulation>\n"
        "</model>\n";

    libcellml::ParserPtr p = libcellml::Parser::create();
    p->parseModel(ex);

    EXPECT_EQ_ERRORS(expectedErrors, p);
}

TEST(Parser, encapsulationWithNoComponent)
{
    const std::vector<std::string> expectedErrors = {
        "Encapsulation in model 'model_name' specifies 'bob' as a component in a component_ref but it does not exist in the model.",
        "Encapsulation in model 'model_name' does not have a valid component attribute in a component_ref element.",
        "Encapsulation in model 'model_name' specifies an invalid parent component_ref that also does not have any children.",
    };

    const std::string ex =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/2.0#\" name=\"model_name\">\n"
        "  <encapsulation>\n"
        "    <component_ref component=\"bob\">\n"
        "      <component_ref/>\n"
        "    </component_ref>\n"
        "  </encapsulation>\n"
        "</model>\n";

    libcellml::ParserPtr p = libcellml::Parser::create();
    p->parseModel(ex);

    EXPECT_EQ_ERRORS(expectedErrors, p);
}

TEST(Parser, encapsulationWithMissingComponent)
{
    const std::vector<std::string> expectedErrors = {
        "Encapsulation in model 'model_name' specifies 'dave' as a component in a component_ref but it does not exist in the model.",
        "Encapsulation in model 'model_name' specifies 'bob' as a parent component_ref but it does not have any children.",
    };

    const std::string ex =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/2.0#\" name=\"model_name\">\n"
        "  <component name=\"bob\"/>\n"
        "  <encapsulation>\n"
        "    <component_ref component=\"bob\">\n"
        "      <component_ref component=\"dave\"/>\n"
        "    </component_ref>\n"
        "  </encapsulation>\n"
        "</model>\n";

    libcellml::ParserPtr p = libcellml::Parser::create();
    p->parseModel(ex);

    EXPECT_EQ_ERRORS(expectedErrors, p);
}

TEST(Parser, encapsulationWithNoComponentChild)
{
    const std::string ex =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/2.0#\" name=\"model_name\">\n"
        "  <component name=\"bob\"/>\n"
        "  <encapsulation>\n"
        "    <component_ref component=\"bob\"/>\n"
        "  </encapsulation>\n"
        "</model>\n";
    const std::vector<std::string> expectedErrors = {
        "Encapsulation in model 'model_name' specifies 'bob' as a parent component_ref but it does not have any children.",
    };

    libcellml::ParserPtr p = libcellml::Parser::create();
    p->parseModel(ex);
    EXPECT_EQ_ERRORS(expectedErrors, p);
}

TEST(Parser, encapsulationNoChildComponentRef)
{
    const std::string ex =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/2.0#\" name=\"model_name\">\n"
        "  <component name=\"bob\"/>\n"
        "  <encapsulation>\n"
        "    <component_ref component=\"bob\">\n"
        "      <component_free/>\n"
        "    </component_ref>\n"
        "  </encapsulation>\n"
        "</model>\n";

    const std::vector<std::string> expectedErrors = {
        "Encapsulation in model 'model_name' has an invalid child element 'component_free'.",
        "Encapsulation in model 'model_name' specifies 'bob' as a parent component_ref but it does not have any children.",
    };

    libcellml::ParserPtr p = libcellml::Parser::create();
    p->parseModel(ex);

    EXPECT_EQ_ERRORS(expectedErrors, p);
}

TEST(Parser, encapsulationWithNoGrandchildComponentRef)
{
    const std::string ex =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/2.0#\" name=\"model_name\">\n"
        "  <component name=\"bob\"/>\n"
        "  <component name=\"jim\"/>\n"
        "  <encapsulation>\n"
        "    <component_ref component=\"bob\">\n"
        "      <component_ref component=\"jim\">\n"
        "        <component_free/>\n"
        "      </component_ref>\n"
        "    </component_ref>\n"
        "  </encapsulation>\n"
        "</model>\n";

    const std::vector<std::string> expectedErrors = {
        "Encapsulation in model 'model_name' has an invalid child element 'component_free'.",
    };

    libcellml::ParserPtr p = libcellml::Parser::create();
    p->parseModel(ex);

    EXPECT_EQ_ERRORS(expectedErrors, p);
}

TEST(Parser, invalidEncapsulations)
{
    const std::string e =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/2.0#\" name=\"ringo\">\n"
        "  <component name=\"dave\"/>\n"
        "  <component name=\"bob\"/>\n"
        "  <encapsulation relationship=\"friends\">\n"
        "    <component_ref component=\"dave\" bogus=\"oops\">\n"
        "      <component_ref component=\"bob\" bogus=\"oops\"/>\n"
        "      <component_ref enemy=\"ignatio\"/>\n"
        "    </component_ref>\n"
        "    <component_ref component=\"ignatio\"/>\n"
        "    <component_ref>\n"
        "      <component_ref/>\n"
        "    </component_ref>\n"
        "  </encapsulation>\n"
        "  <encapsulation>\n"
        "    <component_ref component=\"bob\"/>\n"
        "  </encapsulation>\n"
        "</model>\n";

    const std::vector<std::string> expectedErrors = {
        "Encapsulation in model 'ringo' has an invalid attribute 'relationship'.",
        "Encapsulation in model 'ringo' has an invalid component_ref attribute 'bogus'.",
        "Encapsulation in model 'ringo' has an invalid component_ref attribute 'bogus'.",
        "Encapsulation in model 'ringo' has an invalid component_ref attribute 'enemy'.",
        "Encapsulation in model 'ringo' does not have a valid component attribute in a component_ref element.",
        "Encapsulation in model 'ringo' specifies 'ignatio' as a component in a component_ref but it does not exist in the model.",
        "Encapsulation in model 'ringo' specifies an invalid parent component_ref that also does not have any children.",
        "Encapsulation in model 'ringo' does not have a valid component attribute in a component_ref element.",
        "Encapsulation in model 'ringo' does not have a valid component attribute in a component_ref element.",
        "Encapsulation in model 'ringo' specifies an invalid parent component_ref that also does not have any children.",
        "Model 'ringo' has more than one encapsulation element.",
    };

    libcellml::ParserPtr parser = libcellml::Parser::create();
    parser->parseModel(e);

    EXPECT_EQ_ERRORS(expectedErrors, parser);
}

TEST(Parser, invalidVariableAttributesAndGetVariableError)
{
    const std::string in =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/2.0#\">\n"
        "  <component name=\"componentA\">\n"
        "    <variable name=\"quixote\" don=\"true\"/>\n"
        "    <variable windmill=\"tilted\"/>\n"
        "  </component>\n"
        "</model>\n";
    const std::vector<std::string> expectedErrors = {
        "Variable 'quixote' has an invalid attribute 'don'.",
        "Variable '' has an invalid attribute 'windmill'.",
    };

    libcellml::ParserPtr p = libcellml::Parser::create();
    libcellml::ModelPtr model = p->parseModel(in);
    EXPECT_EQ(expectedErrors.size(), p->errorCount());
    for (size_t i = 0; i < p->errorCount(); ++i) {
        EXPECT_EQ(expectedErrors.at(i), p->error(i)->description());
    }

    libcellml::VariablePtr variableExpected = model->component("componentA")->variable("quixote");
    // Get variable from error and check.
    EXPECT_EQ(variableExpected, p->error(0)->variable());
    // Get const variable from error and check.
    libcellml::ErrorPtr err = p->error(0);
    libcellml::Error *rawErr = err.get();
    const libcellml::VariablePtr variableFromError = rawErr->variable();
    EXPECT_EQ(variableExpected, variableFromError);
}

TEST(Parser, variableAttributeAndChildErrors)
{
    const std::string input1 =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/2.0#\" name=\"model_name\">\n"
        "  <component name=\"randy\">\n"
        "    <variable lame=\"randy\" name=\"Na\" units=\"daves\"/>\n"
        "  </component>\n"
        "</model>\n";
    const std::string expectError1 = "Variable 'Na' has an invalid attribute 'lame'.";
    const std::string input2 =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/2.0#\" name=\"model_name\">\n"
        "  <component name=\"randy\">\n"
        "    <variable name=\"randy\" son=\"stan\" units=\"second\">\n"
        "      <daughter name=\"shelly\"/>\n"
        "    </variable>\n"
        "  </component>\n"
        "</model>\n";
    const std::string expectError2 = "Variable 'randy' has an invalid child element 'daughter'.";
    const std::string expectError3 = "Variable 'randy' has an invalid attribute 'son'.";

    libcellml::ParserPtr p = libcellml::Parser::create();
    p->parseModel(input1);
    EXPECT_EQ(size_t(1), p->errorCount());
    EXPECT_EQ(expectError1, p->error(0)->description());

    p->removeAllErrors();
    p->parseModel(input2);
    EXPECT_EQ(size_t(2), p->errorCount());
    EXPECT_EQ(expectError2, p->error(0)->description());
    EXPECT_EQ(expectError3, p->error(1)->description());
}

TEST(Parser, emptyConnections)
{
    const std::string ex =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/2.0#\" name=\"model_name\">\n"
        "  <connection/>\n"
        "</model>\n";
    const std::vector<std::string> expectedErrors = {
        "Connection in model 'model_name' does not have a valid component_1 in a connection element.",
        "Connection in model 'model_name' does not have a valid component_2 in a connection element.",
        "Connection in model 'model_name' must contain one or more 'map_variables' elements.",
    };

    libcellml::ParserPtr p = libcellml::Parser::create();
    p->parseModel(ex);
    EXPECT_EQ_ERRORS(expectedErrors, p);
}

TEST(Parser, connectionErrorNoComponent2)
{
    const std::string in =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/2.0#\" name=\"modelA\">\n"
        "  <component name=\"componentA\">\n"
        "    <variable name=\"variable1\" units=\"dimensionless\"/>\n"
        "  </component>\n"
        "  <connection component_1=\"component1\">\n"
        "    <map_variables variable_1=\"variable1\" variable_2=\"variable2\"/>\n"
        "  </connection>\n"
        "</model>\n";
    const std::vector<std::string> expectedErrors = {
        "Connection in model 'modelA' does not have a valid component_2 in a connection element.",
        "Connection in model 'modelA' specifies 'component1' as component_1 but it does not exist in the model.",
        "Connection in model 'modelA' specifies 'variable1' as variable_1 but the corresponding component_1 is invalid.",
        "Connection in model 'modelA' specifies 'variable2' as variable_2 but the corresponding component_2 is invalid.",
    };

    libcellml::ParserPtr p = libcellml::Parser::create();
    p->parseModel(in);

    EXPECT_EQ_ERRORS(expectedErrors, p);
}

TEST(Parser, connectionErrorNoComponent2InModel)
{
    const std::string in =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/2.0#\" name=\"modelName\">\n"
        "  <component name=\"component1\">\n"
        "    <variable name=\"variable1\" units=\"dimensionless\"/>\n"
        "  </component>\n"
        "  <connection  component_1=\"component1\"  component_2=\"component2\">\n"
        "    <map_variables variable_1=\"variable1\" variable_2=\"variable2\"/>\n"
        "  </connection>\n"
        "</model>\n";
    const std::vector<std::string> expectedErrors = {
        "Connection in model 'modelName' specifies 'component2' as component_2 but it does not exist in the model.",
        "Connection in model 'modelName' specifies 'variable2' as variable_2 but the corresponding component_2 is invalid.",
    };

    libcellml::ParserPtr p = libcellml::Parser::create();
    p->parseModel(in);
    EXPECT_EQ_ERRORS(expectedErrors, p);
}

TEST(Parser, connectionErrorNoComponent1)
{
    const std::string in =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/2.0#\" name=\"modelName\">\n"
        "<component name=\"componentA\">\n"
        "  <variable name=\"variable1\" units=\"dimensionless\"/>\n"
        "</component>\n"
        "<connection  component_2=\"componentA\">\n"
        "  <map_variables variable_1=\"variable1\" variable_2=\"variable2\"/>\n"
        "</connection>\n"
        "</model>\n";
    const std::vector<std::string> expectedErrors = {
        "Connection in model 'modelName' does not have a valid component_1 in a connection element.",
        "Connection in model 'modelName' specifies 'variable1' as variable_1 but the corresponding component_1 is invalid.",
        "Variable 'variable2' is specified as variable_2 in a connection but it does not exist in component_2 component 'componentA' of model 'modelName'.",
    };

    libcellml::ParserPtr p = libcellml::Parser::create();
    p->parseModel(in);
    EXPECT_EQ_ERRORS(expectedErrors, p);
}

TEST(Parser, connectionErrorNoMapComponents)
{
    const std::string in =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/2.0#\" name=\"modelName\">\n"
        "  <component name=\"componentA\">\n"
        "    <variable name=\"variable1\" units=\"dimensionless\"/>\n"
        "  </component>\n"
        "  <connection name=\"invalid\">\n"
        "    <map_variables variable_1=\"variable1\" variable_2=\"variable2\" variable_3=\"variable3\">\n"
        "      <map_units/>\n"
        "    </map_variables>\n"
        "  </connection>\n"
        "</model>\n";
    const std::vector<std::string> expectedErrors = {
        "Connection in model 'modelName' has an invalid connection attribute 'name'.",
        "Connection in model 'modelName' does not have a valid component_1 in a connection element.",
        "Connection in model 'modelName' does not have a valid component_2 in a connection element.",
        "Connection in model 'modelName' has an invalid child element 'map_units' of element 'map_variables'.",
        "Connection in model 'modelName' has an invalid map_variables attribute 'variable_3'.",
        "Connection in model 'modelName' specifies 'variable1' as variable_1 but the corresponding component_1 is invalid.",
        "Connection in model 'modelName' specifies 'variable2' as variable_2 but the corresponding component_2 is invalid.",
    };

    libcellml::ParserPtr parser = libcellml::Parser::create();
    parser->parseModel(in);
    EXPECT_EQ_ERRORS(expectedErrors, parser);
}

TEST(Parser, connectionErrorNoMapVariables)
{
    const std::string in =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/2.0#\">\n"
        "  <component name=\"componentA\">\n"
        "    <variable name=\"variable1\" units=\"dimensionless\"/>\n"
        "  </component>\n"
        "  <connection component_2=\"componentA\" component_1=\"componentA\" component_3=\"componentA\"/>\n"
        "  <connection component_2=\"componentA\" component_1=\"componentA\"/>\n"
        "</model>\n";
    const std::vector<std::string> expectedErrors = {
        "Connection in model '' has an invalid connection attribute 'component_3'.",
        "Connection in model '' must contain one or more 'map_variables' elements.",
        "Connection in model '' must contain one or more 'map_variables' elements.",
    };

    libcellml::ParserPtr p = libcellml::Parser::create();
    p->parseModel(in);
    EXPECT_EQ_ERRORS(expectedErrors, p);
}

TEST(Parser, importedComponent2Connection)
{
    const std::string e =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/2.0#\">\n"
        "  <import xmlns:xlink=\"http://www.w3.org/1999/xlink\" xlink:href=\"some-other-model.xml\">\n"
        "    <component component_ref=\"component_in_that_model\" name=\"component_in_this_model\"/>\n"
        "  </import>\n"
        "  <component name=\"component_bob\">\n"
        "    <variable name=\"variable_bob\" units=\"dimensionless\"/>\n"
        "  </component>\n"
        "  <connection component_2=\"component_in_this_model\" component_1=\"component_bob\">\n"
        "    <map_variables variable_2=\"variable_import\" variable_1=\"variable_bob\"/>\n"
        "  </connection>\n"
        "</model>\n";

    // Parse
    libcellml::ParserPtr parser = libcellml::Parser::create();
    parser->parseModel(e);
    EXPECT_EQ(size_t(0), parser->errorCount());
}

TEST(Parser, validConnectionMapVariablesFirst)
{
    const std::string e =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/2.0#\">\n"
        "  <component name=\"robert\">\n"
        "    <variable name=\"bob\" units=\"dimensionless\"/>\n"
        "  </component>\n"
        "  <component name=\"james\">\n"
        "    <variable name=\"jimbo\" units=\"dimensionless\"/>\n"
        "  </component>\n"
        "  <connection component_1=\"robert\" component_2=\"james\">\n"
        "    <map_variables variable_2=\"jimbo\" variable_1=\"bob\"/>\n"
        "  </connection>\n"
        "</model>\n";

    libcellml::ParserPtr parser = libcellml::Parser::create();
    parser->parseModel(e);
    EXPECT_EQ(size_t(0), parser->errorCount());
}

TEST(Parser, component2ConnectionVariableMissing)
{
    const std::string e =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/2.0#\">\n"
        "  <component name=\"component_bob\">\n"
        "    <variable name=\"variable_bob\" units=\"dimensionless\"/>\n"
        "  </component>\n"
        "  <component name=\"component_dave\">\n"
        "    <variable name=\"variable_dave\" units=\"dimensionless\"/>\n"
        "  </component>\n"
        "  <connection component_2=\"component_dave\" component_1=\"component_bob\">\n"
        "    <map_variables variable_2=\"variable_angus\" variable_1=\"variable_bob\"/>\n"
        "  </connection>\n"
        "</model>\n";
    const std::vector<std::string> expectedErrors = {
        "Variable 'variable_angus' is specified as variable_2 in a connection but it does not exist in component_2 component 'component_dave' of model ''.",
    };

    // Parse
    libcellml::ParserPtr p = libcellml::Parser::create();
    p->parseModel(e);
    EXPECT_EQ_ERRORS(expectedErrors, p);
}

TEST(Parser, component2InConnectionMissing)
{
    const std::string in =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/2.0#\">\n"
        "  <component name=\"component_bob\">\n"
        "    <variable name=\"variable_bob\" units=\"dimensionless\"/>\n"
        "  </component>\n"
        "  <component name=\"component_dave\">\n"
        "    <variable name=\"variable_dave\" units=\"dimensionless\"/>\n"
        "  </component>\n"
        "  <connection component_1=\"component_bob\">\n"
        "    <map_variables variable_2=\"variable_angus\" variable_1=\"variable_bob\"/>\n"
        "  </connection>\n"
        "</model>\n";
    const std::string e =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/2.0#\">\n"
        "  <component name=\"component_bob\">\n"
        "    <variable name=\"variable_bob\" units=\"dimensionless\"/>\n"
        "  </component>\n"
        "  <component name=\"component_dave\">\n"
        "    <variable name=\"variable_dave\" units=\"dimensionless\"/>\n"
        "  </component>\n"
        "</model>\n";

    const std::vector<std::string> expectedErrors = {
        "Connection in model '' does not have a valid component_2 in a connection element.",
        "Connection in model '' specifies 'variable_angus' as variable_2 but the corresponding component_2 is invalid.",
    };

    // Parse
    libcellml::ParserPtr p = libcellml::Parser::create();
    libcellml::ModelPtr m = p->parseModel(in);
    EXPECT_EQ_ERRORS(expectedErrors, p);

    libcellml::PrinterPtr printer = libcellml::Printer::create();
    const std::string a = printer->printModel(m);
    EXPECT_EQ(e, a);
}

TEST(Parser, connectionVariable2Missing)
{
    const std::string e =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/2.0#\">\n"
        "  <component name=\"component_bob\">\n"
        "    <variable name=\"variable_bob\" units=\"dimensionless\"/>\n"
        "  </component>\n"
        "  <component name=\"component_dave\">\n"
        "    <variable name=\"variable_dave\" units=\"dimensionless\"/>\n"
        "  </component>\n"
        "  <connection component_2=\"component_dave\" component_1=\"component_bob\">\n"
        "    <map_variables variable_1=\"variable_bob\"/>\n"
        "  </connection>\n"
        "</model>\n";

    const std::vector<std::string> expectedErrors = {
        "Connection in model '' does not have a valid variable_2 in a map_variables element.",
    };

    // Parse
    libcellml::ParserPtr p = libcellml::Parser::create();
    p->parseModel(e);
    EXPECT_EQ_ERRORS(expectedErrors, p);
}

TEST(Parser, connectionVariable1Missing)
{
    const std::string e =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/2.0#\">\n"
        "  <component name=\"component_bob\">\n"
        "    <variable name=\"variable_bob\" units=\"scrat\"/>\n"
        "  </component>\n"
        "  <component name=\"component_dave\">\n"
        "    <variable name=\"variable_dave\" units=\"gone\"/>\n"
        "  </component>\n"
        "  <connection component_2=\"component_dave\" component_1=\"component_bob\">\n"
        "    <map_variables variable_2=\"variable_dave\"/>\n"
        "  </connection>\n"
        "</model>\n";
    const std::vector<std::string> expectedErrors = {
        "Connection in model '' does not have a valid variable_1 in a map_variables element.",
    };

    // Parse
    libcellml::ParserPtr p = libcellml::Parser::create();
    p->parseModel(e);
    EXPECT_EQ_ERRORS(expectedErrors, p);
}

TEST(Parser, connectionErrorNoMapVariablesType)
{
    const std::string in =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/2.0#\">\n"
        "  <component name=\"component1\">\n"
        "    <variable name=\"variable1\" units=\"scrat\"/>\n"
        "  </component>\n"
        "  <component name=\"component2\">\n"
        "    <variable name=\"variable2\" units=\"phils\"/>\n"
        "  </component>\n"
        "  <connection component_1=\"component1\"  component_2=\"component2\">\n"
        "    <map_variabels variable_1=\"variable1\" variable_2=\"variable2\"/>\n"
        "  </connection>\n"
        "</model>\n";
    const std::vector<std::string> expectedErrors = {
        "Connection in model '' has an invalid child element 'map_variabels'.",
        "Connection in model '' does not have a map_variables element.",
    };

    libcellml::ParserPtr p = libcellml::Parser::create();
    p->parseModel(in);
    EXPECT_EQ_ERRORS(expectedErrors, p);
}

TEST(Parser, invalidImportsAndGetError)
{
    const std::string input =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/2.0#\">\n"
        "  <import xmlns:xlink=\"http://www.w3.org/1999/xlink\" xlink:href=\"some-other-model.xml\" sauce=\"hollandaise\">\n"
        "    <units units_ref=\"a_units_in_that_model\" name=\"units_in_this_model\"/>\n"
        "    <component component_ref=\"a_component_in_that_model\" name=\"component_in_this_model\"/>\n"
        "    <invalid_nonsense/>\n"
        "    <units units_ruff=\"dog\" name=\"fido\"/>\n"
        "    <component component_meow=\"cat\" name=\"frank\"/>\n"
        "  </import>\n"
        "</model>\n";
    const std::string expectError1 = "Import from 'some-other-model.xml' has an invalid attribute 'sauce'.";
    const std::string expectError2 = "Import from 'some-other-model.xml' has an invalid child element 'invalid_nonsense'.";
    const std::string expectError3 = "Import of units 'fido' from 'some-other-model.xml' has an invalid attribute 'units_ruff'.";
    const std::string expectError4 = "Import of component 'frank' from 'some-other-model.xml' has an invalid attribute 'component_meow'.";
    const std::string output =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/2.0#\">\n"
        "  <import xmlns:xlink=\"http://www.w3.org/1999/xlink\" xlink:href=\"some-other-model.xml\">\n"
        "    <component component_ref=\"a_component_in_that_model\" name=\"component_in_this_model\"/>\n"
        "  </import>\n"
        "  <import xmlns:xlink=\"http://www.w3.org/1999/xlink\" xlink:href=\"some-other-model.xml\">\n"
        "    <units units_ref=\"a_units_in_that_model\" name=\"units_in_this_model\"/>\n"
        "  </import>\n"
        "</model>\n";

    libcellml::ParserPtr p = libcellml::Parser::create();
    libcellml::ModelPtr m = p->parseModel(input);
    EXPECT_EQ(size_t(4), p->errorCount());
    EXPECT_EQ(expectError1, p->error(0)->description());
    EXPECT_EQ(expectError2, p->error(1)->description());
    EXPECT_EQ(expectError3, p->error(2)->description());
    EXPECT_EQ(expectError4, p->error(3)->description());

    libcellml::PrinterPtr printer = libcellml::Printer::create();
    const std::string a = printer->printModel(m);
    EXPECT_EQ(output, a);

    libcellml::ImportSourcePtr import = m->units("units_in_this_model")->importSource();
    // Get import from error and check.
    EXPECT_EQ(import, p->error(0)->importSource());
    // Get const import from error and check.
    const libcellml::ErrorPtr err = p->error(0);
    libcellml::Error *rawErr = err.get();
    const libcellml::ImportSourcePtr importFromError = rawErr->importSource();
    EXPECT_EQ(import, importFromError);
}

TEST(Parser, invalidModelWithAllKindsOfErrors)
{
    // Check for all kinds of errors.
    std::vector<bool> foundKind(9, false);

    // Trigger CellML entity errors
    const std::string input =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/2.0#\" name=\"starwars\" episode=\"four\">\n"
        "  <import princess=\"leia\"/>\n"
        "  <units jedi=\"luke\"/>\n"
        "  <component ship=\"falcon\">\n"
        "    <variable pilot=\"han\"/>\n"
        "  </component>\n"
        "  <connection wookie=\"chewie\"/>\n"
        "  <encapsulation yoda=\"green\"/>\n"
        "</model>\n";

    const std::vector<std::string> expectedErrors = {
        "Model 'starwars' has an invalid attribute 'episode'.",
        "Import from '' has an invalid attribute 'princess'.",
        "Units '' has an invalid attribute 'jedi'.",
        "Component '' has an invalid attribute 'ship'.",
        "Variable '' has an invalid attribute 'pilot'.",
        "Encapsulation in model 'starwars' has an invalid attribute 'yoda'.",
        "Encapsulation in model 'starwars' does not contain any child elements.",
        "Connection in model 'starwars' has an invalid connection attribute 'wookie'.",
        "Connection in model 'starwars' does not have a valid component_1 in a connection element.",
        "Connection in model 'starwars' does not have a valid component_2 in a connection element.",
        "Connection in model 'starwars' must contain one or more 'map_variables' elements.",
    };

    // Parse and check for CellML errors.
    libcellml::ParserPtr parser = libcellml::Parser::create();
    parser->parseModel(input);

    EXPECT_EQ_ERRORS(expectedErrors, parser);

    for (size_t i = 0; i < parser->errorCount(); ++i) {
        switch (parser->error(i)->kind()) {
        case libcellml::Error::Kind::COMPONENT:
            foundKind.at(0) = true;
            break;
        case (libcellml::Error::Kind::CONNECTION):
            foundKind.at(1) = true;
            break;
        case (libcellml::Error::Kind::ENCAPSULATION):
            foundKind.at(2) = true;
            break;
        case (libcellml::Error::Kind::IMPORT):
            foundKind.at(3) = true;
            break;
        case (libcellml::Error::Kind::MODEL):
            foundKind.at(4) = true;
            break;
        case (libcellml::Error::Kind::UNITS):
            foundKind.at(5) = true;
            break;
        case (libcellml::Error::Kind::VARIABLE):
            foundKind.at(6) = true;
            break;
        case libcellml::Error::Kind::MATHML:
        case libcellml::Error::Kind::RESET:
        case libcellml::Error::Kind::UNDEFINED:
        case libcellml::Error::Kind::XML:
        case libcellml::Error::Kind::GENERATOR:
            break;
        }
    }

    // Trigger undefined error
    libcellml::ParserPtr parser2 = libcellml::Parser::create();
    // Add an undefined error
    libcellml::ErrorPtr undefinedError = libcellml::Error::create();
    parser2->addError(undefinedError);
    EXPECT_EQ(size_t(1), parser2->errorCount());
    if (parser2->error(0)->isKind(libcellml::Error::Kind::UNDEFINED)) {
        foundKind.at(7) = true;
    }

    // Trigger an XML error
    const std::string input3 = "jarjarbinks";
    const std::vector<std::string> expectedErrors3 = {
        "LibXml2 error: Start tag expected, '<' not found.",
        "Could not get a valid XML root node from the provided input.",
    };
    libcellml::ParserPtr parser3 = libcellml::Parser::create();
    parser3->parseModel(input3);
    EXPECT_EQ_ERRORS(expectedErrors3, parser3);
    for (size_t i = 0; i < parser3->errorCount(); ++i) {
        if (parser3->error(i)->isKind(libcellml::Error::Kind::XML)) {
            foundKind.at(8) = true;
        }
    }

    // Check that we've found all the possible error types
    bool foundAllKinds = false;
    if (std::all_of(foundKind.begin(), foundKind.end(), [](bool i) { return i; })) {
        foundAllKinds = true;
    }
    EXPECT_TRUE(foundAllKinds);
}

TEST(Parser, invalidModelWithTextInAllElements)
{
    const std::string input =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/2.0#\" name=\"starwars\">\n"
        "  episode7\n"
        "  <import xmlns:xlink=\"http://www.w3.org/1999/xlink\" xlink:href=\"sith.xml\">\n"
        "    kylo\n"
        "  </import>\n"
        "  <units name=\"robot\">\n"
        "    bb-8\n"
        "    <unit units=\"ball\">\n"
        "      rolls\n"
        "    </unit>\n"
        "  </units>\n"
        "  <component name=\"ship\">\n"
        "    falcon\n"
        "    <variable name=\"jedi\">\n"
        "      rey\n"
        "    </variable>\n"
        "  </component>\n"
        "  <connection>\n"
        "    finn\n"
        "    <map_variables>\n"
        "      trooper\n"
        "    </map_variables>\n"
        "  </connection>\n"
        "  <encapsulation>\n"
        "    awakens\n"
        "    <component_ref component=\"ship\">\n"
        "      force\n"
        "    </component_ref>\n"
        "  </encapsulation>\n"
        "</model>\n";

    const std::vector<std::string> expectedErrors = {
        "Model 'starwars' has an invalid non-whitespace child text element '\n  episode7\n  '.",
        "Import from 'sith.xml' has an invalid non-whitespace child text element '\n    kylo\n  '.",
        "Units 'robot' has an invalid non-whitespace child text element '\n    bb-8\n    '.",
        "Unit referencing 'ball' in units 'robot' has an invalid non-whitespace child text element '\n      rolls\n    '.",
        "Component 'ship' has an invalid non-whitespace child text element '\n    falcon\n    '.",
        "Variable 'jedi' has an invalid non-whitespace child text element '\n      rey\n    '.",
        "Encapsulation in model 'starwars' has an invalid non-whitespace child text element '\n    awakens\n    '.",
        "Encapsulation in model 'starwars' has an invalid non-whitespace child text element '\n      force\n    '.",
        "Encapsulation in model 'starwars' specifies 'ship' as a parent component_ref but it does not have any children.",
        "Connection in model 'starwars' does not have a valid component_1 in a connection element.",
        "Connection in model 'starwars' does not have a valid component_2 in a connection element.",
        "Connection in model 'starwars' has an invalid non-whitespace child text element '\n    finn\n    '.",
        "Connection in model 'starwars' has an invalid non-whitespace child text element '\n      trooper\n    '.",
        "Connection in model 'starwars' does not have a valid variable_1 in a map_variables element.",
        "Connection in model 'starwars' does not have a valid variable_2 in a map_variables element.",
        "Connection in model 'starwars' specifies '' as variable_1 but the corresponding component_1 is invalid.",
        "Connection in model 'starwars' specifies '' as variable_2 but the corresponding component_2 is invalid.",
    };

    // Parse and check for CellML errors.
    libcellml::ParserPtr parser = libcellml::Parser::create();
    parser->parseModel(input);

    EXPECT_EQ_ERRORS(expectedErrors, parser);
}

TEST(Parser, parseIds)
{
    const std::string input =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/2.0#\" id=\"mid\">\n"
        "  <import xmlns:xlink=\"http://www.w3.org/1999/xlink\" xlink:href=\"some-other-model.xml\" id=\"i1id\">\n"
        "    <component component_ref=\"a_component_in_that_model\" name=\"component1\" id=\"c1id\"/>\n"
        "  </import>\n"
        "  <import xmlns:xlink=\"http://www.w3.org/1999/xlink\" xlink:href=\"some-other-model.xml\" id=\"i2id\">\n"
        "    <units units_ref=\"a_units_in_that_model\" name=\"units1\" id=\"u1id\"/>\n"
        "  </import>\n"
        "  <units name=\"units2\" id=\"u2id\"/>\n"
        "  <units name=\"units3\" id=\"u3id\"/>\n"
        "  <component name=\"component2\" id=\"c2id\">\n"
        "    <variable name=\"variable1\" units=\"blob\" id=\"vid\"/>\n"
        "  </component>\n"
        "</model>\n";

    libcellml::ParserPtr p = libcellml::Parser::create();
    libcellml::ModelPtr model = p->parseModel(input);

    EXPECT_EQ(size_t(0), p->errorCount());
    EXPECT_EQ("mid", model->id());
    EXPECT_EQ("c1id", model->component("component1")->id());
    EXPECT_EQ("i1id", model->component("component1")->importSource()->id());
    EXPECT_EQ("u1id", model->units("units1")->id());
    EXPECT_EQ("i2id", model->units("units1")->importSource()->id());
    EXPECT_EQ("u2id", model->units("units2")->id());
    EXPECT_EQ("c2id", model->component("component2")->id());
    EXPECT_EQ("u3id", model->units("units3")->id());
    EXPECT_EQ("vid", model->component("component2")->variable("variable1")->id());
}

TEST(Parser, parseIdsOnEverythingButMath)
{
    const std::string input =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/2.0#\" name=\"everything\" id=\"mid\">\n"
        "  <import xmlns:xlink=\"http://www.w3.org/1999/xlink\" xlink:href=\"some-other-model.xml\" id=\"i1id\">\n"
        "    <component component_ref=\"a_component_in_that_model\" name=\"component1\" id=\"c1id\"/>\n"
        "  </import>\n"
        "  <import xmlns:xlink=\"http://www.w3.org/1999/xlink\" xlink:href=\"some-other-model.xml\" id=\"i2id\">\n"
        "    <units units_ref=\"a_units_in_that_model\" name=\"units1\" id=\"u1id\"/>\n"
        "  </import>\n"
        "  <units name=\"units2\" id=\"u2id\">\n"
        "    <unit units=\"second\" id=\"unit1id\"/>\n"
        "  </units>\n"
        "  <units name=\"units3\" id=\"u3id\"/>\n"
        "  <units name=\"blob\"/>\n"
        "  <component name=\"component2\" id=\"c2id\">\n"
        "    <variable name=\"variable1\" units=\"blob\" id=\"v1id\"/>\n"
        "    <variable name=\"variable2\" units=\"blob\" id=\"v2id\"/>\n"
        "    <reset variable=\"variable1\" test_variable=\"variable2\" order=\"1\" id=\"r1id\">\n"
        "      <test_value id=\"tv1id\">\n"
        "        <math xmlns=\"http://www.w3.org/1998/Math/MathML\" id=\"math1when1\">\n"
        "          <apply>\n"
        "            <eq/>\n"
        "            <ci>variable1</ci>\n"
        "            <cn>3.4</cn>\n"
        "          </apply>\n"
        "        </math>\n"
        "      </test_value>\n"
        "      <reset_value id=\"rv1id\">\n"
        "        <math xmlns=\"http://www.w3.org/1998/Math/MathML\" id=\"math2when1\">\n"
        "          <apply>\n"
        "            <eq/>\n"
        "            <ci>variable1</ci>\n"
        "            <cn>9.0</cn>\n"
        "          </apply>\n"
        "        </math>\n"
        "      </reset_value>\n"
        "    </reset>\n"
        "  </component>\n"
        "  <component name=\"component3\" id=\"c3id\">\n"
        "    <variable name=\"variable2\" units=\"ampere\" id=\"c3v2id\"/>\n"
        "  </component>\n"
        "  <connection component_1=\"component2\" component_2=\"component3\" id=\"con1id\">\n"
        "    <map_variables variable_1=\"variable1\" variable_2=\"variable2\" id=\"map1id\"/>\n"
        "  </connection>\n"
        "  <encapsulation id=\"encap1id\">\n"
        "    <component_ref component=\"component2\" id=\"cref1id\">\n"
        "      <component_ref component=\"component3\" id=\"crefchild1id\"/>\n"
        "    </component_ref>\n"
        "  </encapsulation>\n"
        "</model>\n";

    libcellml::ParserPtr parser = libcellml::Parser::create();
    libcellml::ModelPtr model = parser->parseModel(input);

    EXPECT_EQ(size_t(0), parser->errorCount());
    EXPECT_EQ("mid", model->id());
    EXPECT_EQ("c1id", model->component("component1")->id());
    EXPECT_EQ("i1id", model->component("component1")->importSource()->id());
    EXPECT_EQ("u1id", model->units("units1")->id());
    EXPECT_EQ("i2id", model->units("units1")->importSource()->id());
    EXPECT_EQ("u2id", model->units("units2")->id());
    EXPECT_EQ("c2id", model->component("component2")->id());
    EXPECT_EQ("u3id", model->units("units3")->id());
    EXPECT_EQ("v1id", model->component("component2")->variable("variable1")->id());
    EXPECT_EQ("r1id", model->component("component2")->reset(0)->id());
    EXPECT_EQ("tv1id", model->component("component2")->reset(0)->testValueId());
    EXPECT_EQ("rv1id", model->component("component2")->reset(0)->resetValueId());

    libcellml::PrinterPtr printer = libcellml::Printer::create();
    EXPECT_EQ(input, printer->printModel(model));
}

TEST(Parser, parseResets)
{
    const std::string input =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/2.0#\" id=\"mid\">\n"
        "  <component name=\"component2\" id=\"c2id\">\n"
        "    <variable name=\"variable1\" id=\"vid\"/>\n"
        "    <variable name=\"variable2\" id=\"vid2\"/>\n"
        "    <reset order=\"1\" id=\"rid\" variable=\"variable1\" test_variable=\"variable2\">\n"
        "      <test_value>\n"
        "        <math xmlns=\"http://www.w3.org/1998/Math/MathML\">\n"
        "          some condition in mathml\n"
        "        </math>\n"
        "      </test_value>\n"
        "      <reset_value>\n"
        "        <math xmlns=\"http://www.w3.org/1998/Math/MathML\">\n"
        "          some value in mathml\n"
        "        </math>\n"
        "      </reset_value>\n"
        "    </reset>\n"
        "  </component>\n"
        "</model>\n";

    libcellml::ParserPtr p = libcellml::Parser::create();
    libcellml::ModelPtr model = p->parseModel(input);

    libcellml::ComponentPtr c = model->component(0);
    EXPECT_EQ(size_t(1), c->resetCount());

    libcellml::ResetPtr r = c->reset(0);
    EXPECT_EQ(1, r->order());

    libcellml::VariablePtr v1 = r->variable();
    EXPECT_EQ("variable1", v1->name());

    libcellml::VariablePtr v2 = r->testVariable();
    EXPECT_EQ("variable2", v2->name());

    std::string testValueString = r->testValue();
    std::string t =
        "<math xmlns=\"http://www.w3.org/1998/Math/MathML\">\n"
        "          some condition in mathml\n"
        "        </math>\n";
    EXPECT_EQ(t, testValueString);

    std::string resetValueString = r->resetValue();
    std::string rt =
        "<math xmlns=\"http://www.w3.org/1998/Math/MathML\">\n"
        "          some value in mathml\n"
        "        </math>\n";
    EXPECT_EQ(rt, resetValueString);
}

TEST(Parser, parseResetsWithErrors)
{
    const std::string input =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/2.0#\" id=\"mid\">\n"
        "  <component name=\"component1\">\n"
        "    <variable name=\"variable1\" id=\"vid\" units=\"dimensionless\"/>\n" // reset variable not in the same component
        "  </component>\n"
        "  <component name=\"component2\" id=\"c2id\">\n"
        "    <variable name=\"variable2\" id=\"vid2\" units=\"dimensionless\"/>\n"
        "    <variable name=\"variable4\" id=\"vid4\" units=\"dimensionless\"/>\n"

        // variable1 does not exist in this component, variable3 does not exist at all
        "    <reset order=\"33\" variable=\"variable3\" test_variable=\"variable1\">\n"
        "      <test_value one_invalid_attribute=\"apples\">\n" // invalid attribute
        "        <math xmlns=\"http://www.w3.org/1998/Math/MathML\">\n"
        "          <apply>\n"
        "          <eq/>\n"
        "            <ci>C1</ci>\n"
        "            <apply>\n"
        "              <plus/>\n"
        "              <ci>A1</ci>\n"
        "              <ci>B1</ci>\n"
        "            </apply>\n"
        "          </apply>\n"
        "        </math>\n"
        "      </test_value>\n"
        "      <test_value>\n" // duplicated test_value block inside reset
        "        <math xmlns=\"http://www.w3.org/1998/Math/MathML\">\n"
        "          some value in mathml\n"
        "        </math>\n"
        "      </test_value>\n"
        "      <reset_value another_invalid_attribute=\"bananas\">\n" // invalid attribute
        "        <math xmlns=\"http://www.w3.org/1998/Math/MathML\">\n"
        "          some value in mathml\n"
        "        </math>\n"
        "      </reset_value>\n"
        "      <test_value>\n" // duplicated test_value block inside reset
        "        <math xmlns=\"http://www.w3.org/1998/Math/MathML\">\n"
        "          some value in mathml\n"
        "        </math>\n"
        "      </test_value>\n"
        "      <reset_value>\n"
        "        <math xmlns=\"http://www.w3.org/1998/Math/MathML\">\n"
        "          some value in mathml\n"
        "        </math>\n"
        "      </reset_value>\n" // duplicated reset_value block inside reset
        "    </reset>\n"

        // order not specified
        "    <reset variable=\"variable2\" test_variable=\"variable4\">\n"
        "      lost text here\n"
        "      <test_value>\n"
        "        <some_invalid_tag/>\n" // test_value should only contain MathML
        "      </test_value>\n"
        "      <reset_value>\n"
        "        <some_other_invalid_tag/>\n" // reset_value should only contain MathML
        "      </reset_value>\n"
        "    </reset>\n"

        //order not specified, unknown attribute
        "    <reset variable=\"variable2\" test_variable=\"variable4\" i_dont_belong_here=\"yep_really_i_dont\">\n"

        //test_value missing
        //reset_value missing
        "    </reset>\n"
        "  </component>\n"
        "</model>\n";

    const std::vector<std::string> expectedErrors = {
        "Reset referencing variable 'variable3' is not a valid reference for a variable in component 'component2'.",
        "Reset referencing test_variable 'variable1' is not a valid reference for a variable in component 'component2'.",
        "Reset in component 'component2' referencing variable '' and test_variable '' has an unexpected attribute in the test_value block of 'one_invalid_attribute'.",
        "Reset in component 'component2' referencing variable '' and test_variable '' has an unexpected attribute in the reset_value block of 'another_invalid_attribute'.",
        "Reset in component 'component2' referencing variable '' and test_variable '' has 3 test_value blocks.",
        "Reset in component 'component2' referencing variable '' and test_variable '' has 2 reset_value blocks.",
        "Reset in component 'component2' does not have its order set.",
        "Reset has an invalid non-whitespace child text element '\n      lost text here\n      '. Either a test_value block or a reset_value block is expected.",
        "The test_value in the reset in component 'component2' referencing variable 'variable2' and test_variable 'variable4' should have a MathML block as a child.",
        "The reset_value in the reset in component 'component2' referencing variable 'variable2' and test_variable 'variable4' should have a MathML block as a child.",
        "Reset in component 'component2' has an invalid attribute 'i_dont_belong_here'.",
        "Reset in component 'component2' does not have its order set.",
        "Reset in component 'component2' referencing variable 'variable2' and test_variable 'variable4' does not have a test_value block defined.",
        "Reset in component 'component2' referencing variable 'variable2' and test_variable 'variable4' does not have a reset_value block defined.",
    };

    libcellml::ParserPtr p = libcellml::Parser::create();
    libcellml::ModelPtr model = p->parseModel(input);

    libcellml::ResetPtr resetExpected = model->component(1)->reset(0);

    EXPECT_EQ_ERRORS(expectedErrors, p);

    EXPECT_EQ(resetExpected, p->error(0)->reset());
}

TEST(Parser, unitsWithCellMLRealVariations)
{
    const std::string input =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/2.0#\" name=\"model_name\">\n"
        "  <units name=\"fahrenheitish\">\n"
        "    <unit multiplier=\"1.8\" exponent=\"-0.23E-13\" units=\"kelvin\"/>\n"
        "  </units>\n"
        "  <units name=\"units_invalid_reals\">\n"
        "    <unit multiplier=\"1.8.0\" exponent=\"4.87f87\" units=\"kelvin\"/>\n"
        "    <unit multiplier=\"+9.87\" exponent=\"4.87e+16\" units=\"oranges\"/>\n"
        "    <unit multiplier=\"AB8e34\" exponent=\"4.87ee32\" units=\"apples\"/>\n"
        "    <unit multiplier=\"AB8\" exponent=\"4.87eE32\" units=\"bananas\"/>\n"
        "    <unit multiplier=\"e7\" exponent=\"4.87e\" units=\"mangoes\"/>\n"
        "    <unit multiplier=\"3.4e7.8\" units=\"fruit\"/>\n"
        "  </units>\n"
        "</model>\n";

    const std::string e =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/2.0#\" name=\"model_name\">\n"
        "  <units name=\"fahrenheitish\">\n"
        "    <unit exponent=\"-2.3e-14\" multiplier=\"1.8\" units=\"kelvin\"/>\n"
        "  </units>\n"
        "  <units name=\"units_invalid_reals\">\n"
        "    <unit units=\"kelvin\"/>\n"
        "    <unit exponent=\"4.87e+16\" units=\"oranges\"/>\n"
        "    <unit units=\"apples\"/>\n"
        "    <unit units=\"bananas\"/>\n"
        "    <unit units=\"mangoes\"/>\n"
        "    <unit units=\"fruit\"/>\n"
        "  </units>\n"
        "</model>\n";

    libcellml::ParserPtr parser = libcellml::Parser::create();
    libcellml::ModelPtr model = parser->parseModel(input);

    libcellml::PrinterPtr printer = libcellml::Printer::create();
    const std::string a = printer->printModel(model);
    EXPECT_EQ(e, a);
}

TEST(Parser, xmlComments)
{
    const std::string input =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<!-- THIS COMMENT SHOULD BE IGNORED 0 -->\n"
        "<model xmlns=\"http://www.cellml.org/cellml/2.0#\" name=\"model_name\">\n"
        "  <!-- THIS COMMENT SHOULD BE IGNORED 1 -->\n"
        "  <units name=\"fahrenheitish\">\n"
        "    <!-- THIS COMMENT SHOULD BE IGNORED 2 -->\n"
        "    <unit units=\"kelvin\"><!-- THIS COMMENT SHOULD BE IGNORED 2a --></unit>\n"
        "  </units>\n"
        "  <component name=\"main\">\n"
        "    <!-- THIS COMMENT SHOULD BE IGNORED 3 -->\n"
        "    <variable name=\"stan\" units=\"dimensionless\"/>\n"
        "    <variable name=\"V_k\" units=\"dimensionless\"><!-- THIS COMMENT SHOULD BE IGNORED 3a --></variable>\n"
        "    <reset variable=\"V_k\" order=\"2\" id=\"rid\" test_variable=\"stan\">\n"
        "      <!-- THIS COMMENT SHOULD BE IGNORED 4 -->\n"
        "      <test_value>\n"
        "        <!-- THIS COMMENT SHOULD BE IGNORED 5 -->\n"
        "        <math xmlns=\"http://www.w3.org/1998/Math/MathML\">\n"
        "          some condition in mathml\n"
        "        </math>\n"
        "      </test_value>\n"
        "      <reset_value>\n"
        "        <!-- THIS COMMENT SHOULD BE IGNORED 6 -->\n"
        "        <math xmlns=\"http://www.w3.org/1998/Math/MathML\">\n"
        "          some condition in mathml\n"
        "        </math>\n"
        "      </reset_value>\n"
        "    </reset>\n"
        "  </component>\n"
        "  <component name=\"child\"/>\n"
        "  <encapsulation>\n"
        "    <!-- THIS COMMENT SHOULD BE IGNORED 7 -->\n"
        "    <component_ref component=\"main\">\n"
        "       <!-- THIS COMMENT SHOULD BE IGNORED 8 -->\n"
        "       <component_ref component=\"child\"/>\n"
        "    </component_ref>\n"
        "  </encapsulation>\n"
        "</model>\n";

    libcellml::ParserPtr parser = libcellml::Parser::create();
    parser->parseModel(input);

    EXPECT_EQ(size_t(0), parser->errorCount());
}

TEST(Parser, mathWithNamespacesDefinedOnTheMathNode)
{
    const std::string input =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/2.0#\" name=\"model_name\">\n"
        "  <component>\n"
        "  <math xmlns=\"http://www.w3.org/1998/Math/MathML\" xmlns:cellml=\"http://www.cellml.org/cellml/2.0#\">\n"
        "    <apply>\n"
        "      <eq/>\n"
        "      <ci>b2</ci>\n"
        "      <apply>\n"
        "        <times/>\n"
        "        <cn cellml:units=\"dimensionless\">2.0</cn>\n"
        "        <ci>d</ci>\n"
        "      </apply>\n"
        "    </apply>\n"
        "  </math>\n"
        "  </component>\n"
        "</model>\n";

    libcellml::ParserPtr parser = libcellml::Parser::create();
    parser->parseModel(input);

    EXPECT_EQ(size_t(0), parser->errorCount());
}

TEST(Parser, mathWithNamespacesDefinedOnTheNodeThatUsesNamespace)
{
    const std::string input =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/2.0#\" name=\"model_name\">\n"
        "  <component>\n"
        "  <math xmlns=\"http://www.w3.org/1998/Math/MathML\">\n"
        "    <apply>\n"
        "      <eq/>\n"
        "      <ci>b2</ci>\n"
        "      <apply>\n"
        "        <times/>\n"
        "        <cn xmlns:cellml=\"http://www.cellml.org/cellml/2.0#\" cellml:units=\"dimensionless\">2.0</cn>\n"
        "        <ci>d</ci>\n"
        "      </apply>\n"
        "    </apply>\n"
        "  </math>\n"
        "  </component>\n"
        "</model>\n";

    libcellml::ParserPtr parser = libcellml::Parser::create();
    parser->parseModel(input);

    EXPECT_EQ(size_t(0), parser->errorCount());
}

TEST(Parser, mathWithNonStandardCellMLPrefix)
{
    const std::string input =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/2.0#\" xmlns:ns_1=\"http://www.cellml.org/cellml/2.0#\" name=\"model_name\">\n"
        "  <component>\n"
        "    <math xmlns=\"http://www.w3.org/1998/Math/MathML\">\n"
        "      <apply>\n"
        "        <eq/>\n"
        "        <ci>b2</ci>\n"
        "        <apply>\n"
        "          <times/>\n"
        "          <cn ns_1:units=\"dimensionless\">2.0</cn>\n"
        "          <ci>d</ci>\n"
        "        </apply>\n"
        "      </apply>\n"
        "    </math>\n"
        "  </component>\n"
        "</model>\n";

    libcellml::ParserPtr parser = libcellml::Parser::create();
    parser->parseModel(input);

    EXPECT_EQ(size_t(0), parser->errorCount());
}

TEST(Parser, mathWithMathmlNamespaceOnModel)
{
    const std::string input =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/2.0#\" xmlns:ns_2=\"http://www.w3.org/1998/Math/MathML\" xmlns:ns_1=\"http://www.cellml.org/cellml/2.0#\" name=\"model_name\">\n"
        "  <component>\n"
        "    <ns_2:math>\n"
        "      <ns_2:apply>\n"
        "        <ns_2:eq/>\n"
        "        <ns_2:ci>b2</ns_2:ci>\n"
        "        <ns_2:apply>\n"
        "          <ns_2:times/>\n"
        "          <ns_2:cn ns_1:units=\"dimensionless\">2.0</ns_2:cn>\n"
        "          <ns_2:ci>d</ns_2:ci>\n"
        "        </ns_2:apply>\n"
        "      </ns_2:apply>\n"
        "    </ns_2:math>\n"
        "  </component>\n"
        "</model>\n";

    libcellml::ParserPtr parser = libcellml::Parser::create();
    parser->parseModel(input);

    EXPECT_EQ(size_t(0), parser->errorCount());
}

TEST(Parser, repeatedMathParsePrintBehaviour)
{
    const std::string input =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/2.0#\">\n"
        "  <component name=\"component\">\n"
        "    <variable name=\"A\" initial_value=\"1.0\"/>\n"
        "    <variable name=\"B\" initial_value=\"-1.0\"/>\n"
        "    <math xmlns=\"http://www.w3.org/1998/Math/MathML\">\n"
        "      <apply>\n"
        "        <eq/>\n"
        "        <ci>C</ci>\n"
        "        <apply>\n"
        "          <plus/>\n"
        "          <ci>A</ci>\n"
        "          <ci>B</ci>\n"
        "        </apply>\n"
        "      </apply>\n"
        "    </math>\n"
        "  </component>\n"
        "</model>\n";

    libcellml::ParserPtr parser = libcellml::Parser::create();
    libcellml::PrinterPtr printer = libcellml::Printer::create();

    libcellml::ModelPtr model1 = parser->parseModel(input);
    std::string output1 = printer->printModel(model1);

    libcellml::ModelPtr model2 = parser->parseModel(output1);
    std::string output2 = printer->printModel(model2);

    EXPECT_EQ(input, output2);
}

TEST(Parser, repeatedMathParsePrintBehaviourWithReset)
{
    const std::string input =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/2.0#\">\n"
        "  <units name=\"blob\"/>\n"
        "  <component name=\"component\">\n"
        "    <variable name=\"variable1\" units=\"blob\" id=\"v1id\"/>\n"
        "    <variable name=\"variable2\" units=\"blob\" id=\"v2id\"/>\n"
        "    <reset variable=\"variable1\" test_variable=\"variable2\" order=\"1\" id=\"r1id\">\n"
        "      <test_value>\n"
        "        <math xmlns=\"http://www.w3.org/1998/Math/MathML\" id=\"math1when1\">\n"
        "          <apply>\n"
        "            <eq/>\n"
        "            <ci>variable1</ci>\n"
        "            <cn>3.4</cn>\n"
        "          </apply>\n"
        "        </math>\n"
        "      </test_value>\n"
        "      <reset_value>\n"
        "        <math xmlns=\"http://www.w3.org/1998/Math/MathML\" id=\"math2when1\">\n"
        "          <apply>\n"
        "            <eq/>\n"
        "            <ci>variable1</ci>\n"
        "            <cn>9.0</cn>\n"
        "          </apply>\n"
        "        </math>\n"
        "      </reset_value>\n"
        "    </reset>\n"
        "  </component>\n"
        "</model>\n";

    libcellml::ParserPtr parser = libcellml::Parser::create();
    libcellml::PrinterPtr printer = libcellml::Printer::create();

    libcellml::ModelPtr model1 = parser->parseModel(input);
    std::string output1 = printer->printModel(model1);

    libcellml::ModelPtr model2 = parser->parseModel(output1);
    std::string output2 = printer->printModel(model2);

    EXPECT_EQ(input, output2);
}

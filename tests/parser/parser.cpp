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

#include <algorithm>
#include <iostream>
#include <libcellml>
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
        "Opening and ending tag mismatch: Dwarf line 3 and ShortGuy.",
        "Opening and ending tag mismatch: Hobbit line 4 and EvenShorterGuy.",
        "Opening and ending tag mismatch: Wizard line 5 and SomeGuyWithAStaff.",
        "Opening and ending tag mismatch: Elf line 6 and fellows.",
        "Premature end of data in tag fellowship line 2.",
        "Could not get a valid XML root node from the provided input."};

    libcellml::Parser p;
    p.parseModel(input);

    EXPECT_EQ(expectedErrors.size() - 1, p.errorCount());
    for (size_t i = 0; i < p.errorCount(); ++i) {
        if (i == 0) {
            EXPECT_TRUE((p.error(i)->description() != expectedErrors.at(0))
                        || (p.error(i)->description() != expectedErrors.at(1)));
        } else {
            EXPECT_EQ(expectedErrors.at(i + 1), p.error(i)->description());
        }
    }
}

TEST(Parser, parse)
{
    const std::string e =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/2.0#\"/>\n";

    libcellml::Parser parser;
    libcellml::ModelPtr model = parser.parseModel(e);
    libcellml::Printer printer;
    const std::string a = printer.printModel(model);
    EXPECT_EQ(e, a);
}

TEST(Parser, parseNamedModel)
{
    const std::string n = "name";
    const std::string e =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/2.0#\" name=\"name\"/>\n";

    libcellml::Parser parser;
    libcellml::ModelPtr model = parser.parseModel(e);
    EXPECT_EQ(n, model->name());

    libcellml::Printer printer;
    const std::string a = printer.printModel(model);
    EXPECT_EQ(e, a);
}

TEST(Parser, moveParser)
{
    libcellml::Parser p;
    libcellml::Parser pm;
    libcellml::Parser pa;
    pa = p;
    pm = std::move(p);

    libcellml::Parser pc(pm);
}

TEST(Parser, makeError)
{
    const std::string ex;

    libcellml::ErrorPtr e = std::make_shared<libcellml::Error>();

    EXPECT_EQ(ex, e->description());
}

TEST(Parser, emptyModelString)
{
    const std::string ex;
    const std::string expectedError = "Document is empty.";

    libcellml::Parser p;
    p.parseModel(ex);
    EXPECT_EQ(expectedError, p.error(0)->description());
}

TEST(Parser, nonXmlString)
{
    const std::string ex = "Not an xml string.";
    std::vector<std::string> expectedErrors = {
        "Start tag expected, '<' not found.",
        "Could not get a valid XML root node from the provided input."};

    libcellml::Parser p;
    p.parseModel(ex);
    EXPECT_EQ(expectedErrors.size(), p.errorCount());
    for (size_t i = 0; i < p.errorCount(); ++i) {
        EXPECT_EQ(expectedErrors.at(i), p.error(i)->description());
    }
}

TEST(Parser, invalidRootNode)
{
    const std::string ex =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<yodel xmlns=\"http://www.cellml.org/cellml/2.0#\" name=\"model_name\">\n"
        "</yodel>\n";
    const std::string expectedError1 = "Model element is of invalid type 'yodel'. A valid CellML root node should be of type 'model'.";

    libcellml::Parser p;
    p.parseModel(ex);
    EXPECT_EQ(size_t(1), p.errorCount());
    EXPECT_EQ(expectedError1, p.error(0)->description());
}

TEST(Parser, noModelNamespace)
{
    const std::string ex =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model/>\n";
    const std::string expectedError1 = "Model element is in invalid namespace 'null'. A valid CellML root node should be in namespace 'http://www.cellml.org/cellml/2.0#'.";

    libcellml::Parser p;
    p.parseModel(ex);
    EXPECT_EQ(size_t(1), p.errorCount());
    EXPECT_EQ(expectedError1, p.error(0)->description());
}

TEST(Parser, invalidModelNamespace)
{
    const std::string ex =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/1.2#\"/>\n";
    const std::string expectedError1 = "Model element is in invalid namespace 'http://www.cellml.org/cellml/1.2#'. A valid CellML root node should be in namespace 'http://www.cellml.org/cellml/2.0#'.";

    libcellml::Parser p;
    p.parseModel(ex);
    EXPECT_EQ(size_t(1), p.errorCount());
    EXPECT_EQ(expectedError1, p.error(0)->description());
}

TEST(Parser, invalidModelAttribute)
{
    const std::string ex =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/2.0#\" game=\"model_name\"/>\n";
    const std::string expectedError1 = "Model '' has an invalid attribute 'game'.";

    libcellml::Parser p;
    p.parseModel(ex);
    EXPECT_EQ(size_t(1), p.errorCount());
    EXPECT_EQ(expectedError1, p.error(0)->description());
}

TEST(Parser, invalidModelElement)
{
    const std::string ex =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/2.0#\" name=\"model_name\">\n"
        "  <uknits/>\n"
        "</model>\n";
    const std::string expectedError1 = "Model 'model_name' has an invalid child element 'uknits'.";

    libcellml::Parser p;
    p.parseModel(ex);
    EXPECT_EQ(size_t(1), p.errorCount());
    EXPECT_EQ(expectedError1, p.error(0)->description());
}

TEST(Parser, modelWithInvalidElement)
{
    const std::string input1 =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/2.0#\" name=\"bilbo\">\n"
        "  <hobbit/>\n"
        "</model>\n";
    const std::string expectError1 = "Model 'bilbo' has an invalid child element 'hobbit'.";
    const std::string input2 =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/2.0#\">\n"
        "  <hobbit/>\n"
        "</model>\n";
    const std::string expectError2 = "Model '' has an invalid child element 'hobbit'.";

    libcellml::Parser p;
    p.parseModel(input1);
    EXPECT_EQ(size_t(1), p.errorCount());
    EXPECT_EQ(expectError1, p.error(0)->description());

    p.clearErrors();
    p.parseModel(input2);
    EXPECT_EQ(size_t(1), p.errorCount());
    EXPECT_EQ(expectError2, p.error(0)->description());
}

TEST(Parser, parseModelWithInvalidAttributeAndGetError)
{
    const std::string input =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/2.0#\" name=\"modelName\" nonsense=\"oops\"/>\n";
    const std::string expectedError = "Model 'modelName' has an invalid attribute 'nonsense'.";

    libcellml::Parser parser;
    libcellml::ModelPtr model = parser.parseModel(input);

    EXPECT_EQ(size_t(1), parser.errorCount());
    EXPECT_EQ(expectedError, parser.error(0)->description());

    // Get ModelError and check.
    EXPECT_EQ(model, parser.error(0)->model());
    // Get const modelError and check.
    const libcellml::ErrorPtr err = parser.error(0);
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

    libcellml::Parser parser;
    libcellml::ModelPtr model = parser.parseModel(e);
    EXPECT_EQ(mName, model->name());
    libcellml::ComponentPtr c = model->component(cName);
    EXPECT_EQ(cName, c->name());

    libcellml::Printer printer;
    const std::string a = printer.printModel(model);
    EXPECT_EQ(e, a);
}

TEST(Parser, parseModelWithUnitsAndNamedComponent)
{
    const std::string e =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/2.0#\" name=\"model_name\">\n"
        "  <units name=\"fahrenheitish\">\n"
        "    <unit multiplier=\"1.8\" units=\"kelvin\"/>\n"
        "  </units>\n"
        "  <units name=\"dimensionless\"/>\n"
        "  <component name=\"component_name\"/>\n"
        "</model>\n";

    libcellml::Parser parser;
    libcellml::ModelPtr model = parser.parseModel(e);

    libcellml::Printer printer;
    const std::string a = printer.printModel(model);
    EXPECT_EQ(e, a);
}

TEST(Parser, unitsAttributeError)
{
    const std::string ex =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/2.0#\" name=\"model_name\">\n"
        "  <units name=\"pH\" invalid_attribute=\"yes\"/>\n"
        "</model>\n";
    const std::string expectedError1 = "Units 'pH' has an invalid attribute 'invalid_attribute'.";

    libcellml::Parser p;
    p.parseModel(ex);
    EXPECT_EQ(size_t(1), p.errorCount());
    EXPECT_EQ(expectedError1, p.error(0)->description());
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
    const std::string expectError1 = "Units '' has an invalid child element 'son'.";
    const std::string input2 =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/2.0#\" name=\"model_name\">\n"
        "  <units name=\"randy\">\n"
        "    <son name=\"stan\"/>\n"
        "  </units>\n"
        "</model>\n";
    const std::string expectError2 = "Units 'randy' has an invalid child element 'son'.";

    libcellml::Parser p;
    p.parseModel(input1);
    EXPECT_EQ(size_t(1), p.errorCount());
    EXPECT_EQ(expectError1, p.error(0)->description());

    p.clearErrors();
    p.parseModel(input2);
    EXPECT_EQ(size_t(1), p.errorCount());
    EXPECT_EQ(expectError2, p.error(0)->description());
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
    const std::string expectedError1 = "Units 'unit_name' has an invalid attribute 'base_unit'.";

    libcellml::Parser parser;
    libcellml::ModelPtr model = parser.parseModel(in);

    EXPECT_EQ(size_t(1), parser.errorCount());
    EXPECT_EQ(expectedError1, parser.error(0)->description());

    libcellml::UnitsPtr unitsExpected = model->units("unit_name");

    // Get units from error and check.
    EXPECT_EQ(unitsExpected, parser.error(0)->units());

    // Get const units from error and check.
    const libcellml::ErrorPtr err = parser.error(0);
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
    const std::string expectedError = "Component 'componentName' has an invalid attribute 'nonsense'.";

    libcellml::Parser parser;
    libcellml::ModelPtr model = parser.parseModel(input);
    libcellml::ComponentPtr component = model->component(cName);

    EXPECT_EQ(size_t(1), parser.errorCount());
    EXPECT_EQ(expectedError, parser.error(0)->description());

    // Get component from error and check.
    EXPECT_EQ(component, parser.error(0)->component());
    // Get const component from error and check.
    const libcellml::ErrorPtr err = parser.error(0);
    libcellml::Error *rawErr = err.get();
    const libcellml::ComponentPtr componentFromError = rawErr->component();
    EXPECT_EQ(component, componentFromError);

    // Get non-existent error
    EXPECT_EQ(nullptr, parser.error(1));
}

TEST(Parser, componentAttributeErrors)
{
    const std::string input1 =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/2.0#\" name=\"model_name\">\n"
        "  <component lame=\"randy\"/>\n"
        "</model>\n";
    const std::string expectError1 = "Component '' has an invalid attribute 'lame'.";
    const std::string input2 =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/2.0#\" name=\"model_name\">\n"
        "  <component name=\"randy\" son=\"stan\"/>\n"
        "</model>\n";
    const std::string expectError2 = "Component 'randy' has an invalid attribute 'son'.";
    const std::string input3 =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/2.0#\" name=\"model_name\">\n"
        "  <component son=\"stan\" name=\"randy\"/>\n"
        "</model>\n";
    const std::string expectError3 = "Component 'randy' has an invalid attribute 'son'.";

    libcellml::Parser p;
    p.parseModel(input1);
    EXPECT_EQ(size_t(1), p.errorCount());
    EXPECT_EQ(expectError1, p.error(0)->description());

    p.clearErrors();
    p.parseModel(input2);
    EXPECT_EQ(size_t(1), p.errorCount());
    EXPECT_EQ(expectError2, p.error(0)->description());

    p.clearErrors();
    p.parseModel(input3);
    EXPECT_EQ(size_t(1), p.errorCount());
    EXPECT_EQ(expectError3, p.error(0)->description());
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

    libcellml::Parser p;
    p.parseModel(input1);
    EXPECT_EQ(size_t(1), p.errorCount());
    EXPECT_EQ(expectError1, p.error(0)->description());

    p.clearErrors();
    p.parseModel(input2);
    EXPECT_EQ(size_t(1), p.errorCount());
    EXPECT_EQ(expectError2, p.error(0)->description());
}

TEST(Parser, parseModelWithTwoComponents)
{
    const std::string e =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/2.0#\" name=\"modelName\">\n"
        "  <component name=\"component1\"/>\n"
        "  <component name=\"component2\"/>\n"
        "</model>\n";

    libcellml::Parser parser;
    libcellml::ModelPtr model = parser.parseModel(e);

    libcellml::Printer printer;
    const std::string a = printer.printModel(model);
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

    libcellml::Parser parser;
    libcellml::ModelPtr model = parser.parseModel(e);

    libcellml::Printer printer;
    const std::string a = printer.printModel(model);
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

    libcellml::Parser parser;
    libcellml::ModelPtr model = parser.parseModel(e);

    libcellml::Printer printer;
    const std::string a = printer.printModel(model);
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
        "  <units name=\"dimensionless\"/>\n"
        "</model>\n";

    libcellml::Parser parser;
    libcellml::ModelPtr model = parser.parseModel(in);

    libcellml::Printer printer;
    const std::string a = printer.printModel(model);
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
        "  <units name=\"dimensionless\"/>\n"
        "  <units>\n"
        "    <unit units=\"friends\"/>\n"
        "    <unit units=\"\"/>\n"
        "  </units>\n"
        "</model>\n";

    std::vector<std::string> expectedErrors = {
        "Units 'fahrenheitish' has an invalid attribute 'temperature'.",
        "Unit referencing 'kelvin' in units 'fahrenheitish' has an invalid child element 'degrees'.",
        "Unit referencing 'kelvin' in units 'fahrenheitish' has a multiplier with the value 'Z' that is not a representation of a CellML real valued number.",
        "Unit referencing 'kelvin' in units 'fahrenheitish' has an invalid attribute 'bill'.",
        "Units 'fahrenheitish' has an invalid child element 'bobshouse'.",
        "Unit referencing '' in units 'fahrenheitish' has an invalid attribute 'GUnit'.",
        "Units '' has an invalid attribute 'jerry'.",
        "Unit referencing 'friends' in units '' has an invalid attribute 'neighbor'.",
        "Unit referencing '' in units '' has an invalid attribute 'george'."};

    libcellml::Parser parser;
    libcellml::ModelPtr model = parser.parseModel(in);

    EXPECT_EQ(expectedErrors.size(), parser.errorCount());
    for (size_t i = 0; i < parser.errorCount(); ++i) {
        EXPECT_EQ(expectedErrors.at(i), parser.error(i)->description());
    }

    libcellml::Printer printer;
    const std::string a = printer.printModel(model);
    EXPECT_EQ(e, a);
}

TEST(Parser, emptyEncapsulation)
{
    const std::string ex =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/2.0#\" name=\"model_name\">\n"
        "  <encapsulation/>\n"
        "</model>\n";

    const std::string expectedError = "Encapsulation in model 'model_name' does not contain any child elements.";

    libcellml::Parser p;
    p.parseModel(ex);
    EXPECT_EQ(size_t(1), p.errorCount());
    EXPECT_EQ(expectedError, p.error(0)->description());
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
    const std::string expectedError1 = "Encapsulation in model 'model_name' does not have a valid component attribute in a component_ref element.";
    const std::string expectedError2 = "Encapsulation in model 'model_name' specifies an invalid parent component_ref that also does not have any children.";

    libcellml::Parser p;
    p.parseModel(ex);
    EXPECT_EQ(size_t(2), p.errorCount());
    EXPECT_EQ(expectedError1, p.error(0)->description());
    EXPECT_EQ(expectedError2, p.error(1)->description());
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

    libcellml::Parser p;
    p.parseModel(ex);

    expectEqualErrors(expectedErrors, p);
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

    libcellml::Parser p;
    p.parseModel(ex);

    expectEqualErrors(expectedErrors, p);
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

    libcellml::Parser p;
    p.parseModel(ex);

    expectEqualErrors(expectedErrors, p);
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
    const std::string expectedError = "Encapsulation in model 'model_name' specifies 'bob' as a parent component_ref but it does not have any children.";

    libcellml::Parser p;
    p.parseModel(ex);
    EXPECT_EQ(size_t(1), p.errorCount());
    EXPECT_EQ(expectedError, p.error(0)->description());
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

    libcellml::Parser p;
    p.parseModel(ex);

    expectEqualErrors(expectedErrors, p);
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

    libcellml::Parser p;
    p.parseModel(ex);

    expectEqualErrors(expectedErrors, p);
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

    libcellml::Parser parser;
    parser.parseModel(e);

    expectEqualErrors(expectedErrors, parser);
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

    libcellml::Parser p;
    libcellml::ModelPtr model = p.parseModel(in);
    EXPECT_EQ(expectedErrors.size(), p.errorCount());
    for (size_t i = 0; i < p.errorCount(); ++i) {
        EXPECT_EQ(expectedErrors.at(i), p.error(i)->description());
    }

    libcellml::VariablePtr variableExpected = model->component("componentA")->variable("quixote");
    // Get variable from error and check.
    EXPECT_EQ(variableExpected, p.error(0)->variable());
    // Get const variable from error and check.
    libcellml::ErrorPtr err = p.error(0);
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

    libcellml::Parser p;
    p.parseModel(input1);
    EXPECT_EQ(size_t(1), p.errorCount());
    EXPECT_EQ(expectError1, p.error(0)->description());

    p.clearErrors();
    p.parseModel(input2);
    EXPECT_EQ(size_t(2), p.errorCount());
    EXPECT_EQ(expectError2, p.error(0)->description());
    EXPECT_EQ(expectError3, p.error(1)->description());
}

TEST(Parser, emptyConnections)
{
    const std::string ex =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/2.0#\" name=\"model_name\">\n"
        "  <connection/>\n"
        "</model>\n";
    const std::string expectedError1 = "Connection in model 'model_name' does not have a valid component_1 in a connection element.";
    const std::string expectedError2 = "Connection in model 'model_name' does not have a valid component_2 in a connection element.";
    const std::string expectedError3 = "Connection in model 'model_name' must contain one or more 'map_variables' elements.";

    libcellml::Parser p;
    p.parseModel(ex);
    EXPECT_EQ(size_t(3), p.errorCount());
    EXPECT_EQ(expectedError1, p.error(0)->description());
    EXPECT_EQ(expectedError2, p.error(1)->description());
    EXPECT_EQ(expectedError3, p.error(2)->description());
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
    const std::string expectedError1 = "Connection in model 'modelA' does not have a valid component_2 in a connection element.";
    const std::string expectedError2 = "Connection in model 'modelA' specifies 'component1' as component_1 but it does not exist in the model.";
    const std::string expectedError3 = "Connection in model 'modelA' specifies 'variable1' as variable_1 but the corresponding component_1 is invalid.";
    const std::string expectedError4 = "Connection in model 'modelA' specifies 'variable2' as variable_2 but the corresponding component_2 is invalid.";

    libcellml::Parser p;
    p.parseModel(in);
    EXPECT_EQ(size_t(4), p.errorCount());
    EXPECT_EQ(expectedError1, p.error(0)->description());
    EXPECT_EQ(expectedError2, p.error(1)->description());
    EXPECT_EQ(expectedError3, p.error(2)->description());
    EXPECT_EQ(expectedError4, p.error(3)->description());
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
    const std::string expectedError1 = "Connection in model 'modelName' specifies 'component2' as component_2 but it does not exist in the model.";
    const std::string expectedError2 = "Connection in model 'modelName' specifies 'variable2' as variable_2 but the corresponding component_2 is invalid.";

    libcellml::Parser p;
    p.parseModel(in);
    EXPECT_EQ(size_t(2), p.errorCount());
    EXPECT_EQ(expectedError1, p.error(0)->description());
    EXPECT_EQ(expectedError2, p.error(1)->description());
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
    const std::string expectedError1 = "Connection in model 'modelName' does not have a valid component_1 in a connection element.";
    const std::string expectedError2 = "Connection in model 'modelName' specifies 'variable1' as variable_1 but the corresponding component_1 is invalid.";
    const std::string expectedError3 = "Variable 'variable2' is specified as variable_2 in a connection but it does not exist in component_2 component 'componentA' of model 'modelName'.";

    libcellml::Parser p;
    p.parseModel(in);
    EXPECT_EQ(size_t(3), p.errorCount());
    EXPECT_EQ(expectedError1, p.error(0)->description());
    EXPECT_EQ(expectedError2, p.error(1)->description());
    EXPECT_EQ(expectedError3, p.error(2)->description());
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
        "Connection in model 'modelName' specifies 'variable2' as variable_2 but the corresponding component_2 is invalid."};

    libcellml::Parser parser;
    parser.parseModel(in);

    EXPECT_EQ(expectedErrors.size(), parser.errorCount());
    for (size_t i = 0; i < parser.errorCount(); ++i) {
        EXPECT_EQ(expectedErrors.at(i), parser.error(i)->description());
    }
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
    const std::string expectedError1 = "Connection in model '' has an invalid connection attribute 'component_3'.";
    const std::string expectedError2 = "Connection in model '' must contain one or more 'map_variables' elements.";
    const std::string expectedError3 = "Connection in model '' must contain one or more 'map_variables' elements.";

    libcellml::Parser p;
    p.parseModel(in);
    EXPECT_EQ(size_t(3), p.errorCount());
    EXPECT_EQ(expectedError1, p.error(0)->description());
    EXPECT_EQ(expectedError2, p.error(1)->description());
    EXPECT_EQ(expectedError3, p.error(2)->description());
}

TEST(Parser, importedComponent2Connection)
{
    const std::string e =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/2.0#\">\n"
        "  <import xlink:href=\"some-other-model.xml\" xmlns:xlink=\"http://www.w3.org/1999/xlink\">\n"
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
    libcellml::Parser parser;
    parser.parseModel(e);
    EXPECT_EQ(size_t(0), parser.errorCount());
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

    libcellml::Parser parser;
    parser.parseModel(e);
    EXPECT_EQ(size_t(0), parser.errorCount());
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
    const std::string expectedError = "Variable 'variable_angus' is specified as variable_2 in a connection but it does not exist in component_2 component 'component_dave' of model ''.";

    // Parse
    libcellml::Parser p;
    p.parseModel(e);
    EXPECT_EQ(size_t(1), p.errorCount());
    EXPECT_EQ(expectedError, p.error(0)->description());
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
    const std::string expectedError1 = "Connection in model '' does not have a valid component_2 in a connection element.";
    const std::string expectedError2 = "Connection in model '' specifies 'variable_angus' as variable_2 but the corresponding component_2 is invalid.";

    // Parse
    libcellml::Parser p;
    libcellml::ModelPtr m = p.parseModel(in);
    EXPECT_EQ(size_t(2), p.errorCount());

    libcellml::Printer printer;
    const std::string a = printer.printModel(m);
    EXPECT_EQ(e, a);
    EXPECT_EQ(expectedError1, p.error(0)->description());
    EXPECT_EQ(expectedError2, p.error(1)->description());
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
    const std::string expectedError1 = "Connection in model '' does not have a valid variable_2 in a map_variables element.";

    // Parse
    libcellml::Parser p;
    p.parseModel(e);
    EXPECT_EQ(size_t(1), p.errorCount());
    EXPECT_EQ(expectedError1, p.error(0)->description());
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
    const std::string expectedError1 = "Connection in model '' does not have a valid variable_1 in a map_variables element.";

    // Parse
    libcellml::Parser p;
    p.parseModel(e);
    EXPECT_EQ(size_t(1), p.errorCount());
    EXPECT_EQ(expectedError1, p.error(0)->description());
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
    const std::string expectedError1 = "Connection in model '' has an invalid child element 'map_variabels'.";
    const std::string expectedError2 = "Connection in model '' does not have a map_variables element.";

    libcellml::Parser p;
    p.parseModel(in);
    EXPECT_EQ(size_t(2), p.errorCount());
    EXPECT_EQ(expectedError1, p.error(0)->description());
    EXPECT_EQ(expectedError2, p.error(1)->description());
}

TEST(Parser, invalidImportsAndGetError)
{
    const std::string input =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/2.0#\">\n"
        "  <import xlink:href=\"some-other-model.xml\" xmlns:xlink=\"http://www.w3.org/1999/xlink\" sauce=\"hollandaise\">\n"
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
        "  <import xlink:href=\"some-other-model.xml\" xmlns:xlink=\"http://www.w3.org/1999/xlink\">\n"
        "    <component component_ref=\"a_component_in_that_model\" name=\"component_in_this_model\"/>\n"
        "  </import>\n"
        "  <import xlink:href=\"some-other-model.xml\" xmlns:xlink=\"http://www.w3.org/1999/xlink\">\n"
        "    <units units_ref=\"a_units_in_that_model\" name=\"units_in_this_model\"/>\n"
        "  </import>\n"
        "</model>\n";

    libcellml::Parser p;
    libcellml::ModelPtr m = p.parseModel(input);
    EXPECT_EQ(size_t(4), p.errorCount());
    EXPECT_EQ(expectError1, p.error(0)->description());
    EXPECT_EQ(expectError2, p.error(1)->description());
    EXPECT_EQ(expectError3, p.error(2)->description());
    EXPECT_EQ(expectError4, p.error(3)->description());

    libcellml::Printer printer;
    const std::string a = printer.printModel(m);
    EXPECT_EQ(output, a);

    libcellml::ImportSourcePtr import = m->units("units_in_this_model")->importSource();
    // Get import from error and check.
    EXPECT_EQ(import, p.error(0)->importSource());
    // Get const import from error and check.
    const libcellml::ErrorPtr err = p.error(0);
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
    libcellml::Parser parser;
    parser.parseModel(input);
    EXPECT_EQ(expectedErrors.size(), parser.errorCount());
    for (size_t i = 0; i < parser.errorCount(); ++i) {
        EXPECT_EQ(expectedErrors.at(i), parser.error(i)->description());
        switch (parser.error(i)->kind()) {
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
        case libcellml::Error::Kind::WHEN:
        case libcellml::Error::Kind::XML:
        case libcellml::Error::Kind::GENERATOR:
            break;
        }
    }

    // Trigger undefined error
    libcellml::Parser parser2;
    // Add an undefined error
    libcellml::ErrorPtr undefinedError = std::make_shared<libcellml::Error>();
    parser2.addError(undefinedError);
    EXPECT_EQ(size_t(1), parser2.errorCount());
    if (parser2.error(0)->isKind(libcellml::Error::Kind::UNDEFINED)) {
        foundKind.at(7) = true;
    }

    // Trigger an XML error
    const std::string input3 = "jarjarbinks";
    std::vector<std::string> expectedErrors3 = {
        "Start tag expected, '<' not found.",
        "Could not get a valid XML root node from the provided input."};
    libcellml::Parser parser3;
    parser3.parseModel(input3);
    EXPECT_EQ(expectedErrors3.size(), parser3.errorCount());
    for (size_t i = 0; i < parser3.errorCount(); ++i) {
        EXPECT_EQ(expectedErrors3.at(i), parser3.error(i)->description());
        if (parser3.error(i)->isKind(libcellml::Error::Kind::XML)) {
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
        "  <import xlink:href=\"sith.xml\" xmlns:xlink=\"http://www.w3.org/1999/xlink\">\n"
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
    libcellml::Parser parser;
    parser.parseModel(input);

    expectEqualErrors(expectedErrors, parser);
}

TEST(Parser, parseIds)
{
    const std::string input =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/2.0#\" id=\"mid\">\n"
        "  <import xlink:href=\"some-other-model.xml\" xmlns:xlink=\"http://www.w3.org/1999/xlink\" id=\"i1id\">\n"
        "    <component component_ref=\"a_component_in_that_model\" name=\"component1\" id=\"c1id\"/>\n"
        "  </import>\n"
        "  <import xlink:href=\"some-other-model.xml\" xmlns:xlink=\"http://www.w3.org/1999/xlink\" id=\"i2id\">\n"
        "    <units units_ref=\"a_units_in_that_model\" name=\"units1\" id=\"u1id\"/>\n"
        "  </import>\n"
        "  <units name=\"units2\" id=\"u2id\"/>\n"
        "  <units name=\"units3\" id=\"u3id\"/>\n"
        "  <component name=\"component2\" id=\"c2id\">\n"
        "    <variable name=\"variable1\" units=\"blob\" id=\"vid\"/>\n"
        "  </component>\n"
        "</model>\n";

    libcellml::Parser p;
    libcellml::ModelPtr model = p.parseModel(input);

    EXPECT_EQ(size_t(0), p.errorCount());
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

TEST(Parser, parseIdsOnEverything)
{
    const std::string input =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/2.0#\" name=\"everything\" id=\"mid\">\n"
        "  <import xlink:href=\"some-other-model.xml\" xmlns:xlink=\"http://www.w3.org/1999/xlink\" id=\"i1id\">\n"
        "    <component component_ref=\"a_component_in_that_model\" name=\"component1\" id=\"c1id\"/>\n"
        "  </import>\n"
        "  <import xlink:href=\"some-other-model.xml\" xmlns:xlink=\"http://www.w3.org/1999/xlink\" id=\"i2id\">\n"
        "    <units units_ref=\"a_units_in_that_model\" name=\"units1\" id=\"u1id\"/>\n"
        "  </import>\n"
        "  <units name=\"units2\" id=\"u2id\">\n"
        "    <unit units=\"second\" id=\"unit1id\"/>\n"
        "  </units>\n"
        "  <units name=\"units3\" id=\"u3id\"/>\n"
        "  <component name=\"component2\" id=\"c2id\">\n"
        "    <variable name=\"variable1\" units=\"blob\" id=\"v1id\"/>\n"
        "    <reset variable=\"variable1\" order=\"1\" id=\"r1id\">\n"
        "      <when order=\"5\" id=\"w1id\">\n"
        "        <math xmlns=\"http://www.w3.org/1998/Math/MathML\" id=\"math1when1\">\n"
        "          <apply>\n"
        "            <eq/>\n"
        "            <ci>variable1</ci>\n"
        "            <cn>3.4</cn>\n"
        "          </apply>\n"
        "        </math>\n"
        "        <math xmlns=\"http://www.w3.org/1998/Math/MathML\" id=\"math2when2\">\n"
        "          <apply>\n"
        "            <eq/>\n"
        "            <ci>variable1</ci>\n"
        "            <cn>9.0</cn>\n"
        "          </apply>\n"
        "        </math>\n"
        "      </when>\n"
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

    libcellml::Parser parser;
    libcellml::ModelPtr model = parser.parseModel(input);

    printErrors(parser);
    EXPECT_EQ(size_t(0), parser.errorCount());
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
    EXPECT_EQ("w1id", model->component("component2")->reset(0)->when(0)->id());

    libcellml::Printer printer;
    EXPECT_EQ(input, printer.printModel(model));
}

TEST(Parser, parseResets)
{
    const std::string input =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/2.0#\" id=\"mid\">\n"
        "  <component name=\"component2\" id=\"c2id\">\n"
        "    <variable name=\"variable1\" id=\"vid\"/>\n"
        "    <reset order=\"1\" id=\"rid\">\n"
        "      <when order=\"5\">\n"
        "        <math xmlns=\"http://www.w3.org/1998/Math/MathML\">\n"
        "          some condition in mathml\n"
        "        </math>\n"
        "        <math xmlns=\"http://www.w3.org/1998/Math/MathML\">\n"
        "          some value in mathml\n"
        "        </math>\n"
        "      </when>\n"
        "      <when order=\"3\" id=\"wid\">\n"
        "        <math xmlns=\"http://www.w3.org/1998/Math/MathML\">\n"
        "          some condition in mathml\n"
        "        </math>\n"
        "        <math xmlns=\"http://www.w3.org/1998/Math/MathML\">\n"
        "          some value in mathml\n"
        "        </math>\n"
        "      </when>\n"
        "    </reset>\n"
        "  </component>\n"
        "</model>\n";

    libcellml::Parser p;
    libcellml::ModelPtr model = p.parseModel(input);

    libcellml::ComponentPtr c = model->component(0);
    EXPECT_EQ(size_t(1), c->resetCount());

    libcellml::ResetPtr r = c->reset(0);
    EXPECT_EQ(1, r->order());
    EXPECT_EQ(size_t(2), r->whenCount());

    libcellml::WhenPtr w = r->when(1);
    EXPECT_EQ(3, w->order());
}

TEST(Parser, parseResetsWithNumerousErrors)
{
    const std::string input =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/2.0#\" id=\"mid\">\n"
        "  <component name=\"component2\" id=\"c2id\">\n"
        "    <variable name=\"variable1\" id=\"vid\" units=\"plough\"/>\n"
        "    <variable name=\"V_k\" id=\"vid\" units=\"siemens\"/>\n"
        "    <reset order=\"1.3\" id=\"rid\">\n"
        "      <when order=\"-0\" change=\"$4.50\">\n"
        "        <math xmlns=\"http://www.w3.org/1998/Math/MathML\">\n"
        "          some condition in mathml\n"
        "        </math>\n"
        "        <math xmlns=\"http://www.w3.org/1998/Math/MathML\">\n"
        "          some value in mathml\n"
        "        </math>\n"
        "        <math xmlns=\"http://www.w3.org/1998/Math/MathML\">\n"
        "          extra mathml node\n"
        "        </math>\n"
        "      </when>\n"
        "      <when order=\"3\" id=\"wid\">\n"
        "        <math xmlns=\"http://www.w3.org/1998/Math/MathML\">\n"
        "          some condition in mathml\n"
        "        </math>\n"
        "        <math xmlns=\"http://www.w3.org/1998/Math/MathML\">\n"
        "          some value in mathml\n"
        "        </math>\n"
        "      </when>\n"
        "      <when order=\"3\" id=\"wid\">\n"
        "        <math xmlns=\"http://www.w3.org/1998/Math/MathML\">\n"
        "          some condition in mathml\n"
        "        </math>\n"
        "        <math xmlns=\"http://www.w3.org/1998/Math/MathML\">\n"
        "          some value in mathml\n"
        "        </math>\n"
        "      </when>\n"
        "    </reset>\n"
        "    <reset variable=\"I_na\" order=\"2\" id=\"rid\">\n"
        "      <when order=\"5.9\" goods=\"socks\">\n"
        "        <math xmlns=\"http://www.w3.org/1998/Math/MathML\">\n"
        "          some condition in mathml\n"
        "        </math>\n"
        "      </when>\n"
        "    </reset>\n"
        "    <reset variable=\"I_na\" order=\"2\" id=\"rid\">\n"
        "      <when />\n"
        "    </reset>\n"
        "    <reset id=\"r3id\">\n"
        "      <when order=\"\"/>\n"
        "    <about>\n"
        "      Some description of importance.\n"
        "    </about>\n"
        "    </reset>\n"
        "    <reset variable=\"V_k\" order=\"-\" start=\"now\"/>\n"
        "    <reset variable=\"variable1\" order=\"0\">\n"
        "      non empty whitespace.\n"
        "      <when order=\"1\">\n"
        "        illegal content.\n"
        "        <math xmlns=\"http://www.w3.org/1998/Math/MathML\">\n"
        "          some condition in mathml\n"
        "        </math>\n"
        "        <math xmlns=\"http://www.w3.org/1998/Math/MathML\">\n"
        "          some value in mathml\n"
        "        </math>\n"
        "        <variable/>\n"
        "      </when>\n"
        "    </reset>\n"
        "  </component>\n"
        "</model>\n";
    const std::vector<std::string> expectedErrors = {
        "Reset in component 'component2' referencing variable '' has a non-integer order value '1.3'.",
        "Reset in component 'component2' does not reference a variable in the component.",
        "When in reset referencing variable '' with order '' has an invalid attribute 'change'.",
        "When in reset referencing variable '' with order '' contains more than two MathML child elements.",
        "Reset referencing variable 'I_na' is not a valid reference for a variable in component 'component2'.",
        "Reset in component 'component2' does not reference a variable in the component.",
        "When in reset referencing variable '' with order '2' has an invalid attribute 'goods'.",
        "When in reset referencing variable '' with order '2' does not have an order defined.",
        "When in reset referencing variable '' with order '2' contains only one MathML child element.",
        "Reset referencing variable 'I_na' is not a valid reference for a variable in component 'component2'.",
        "Reset in component 'component2' does not reference a variable in the component.",
        "When in reset referencing variable '' with order '2' does not have an order defined.",
        "When in reset referencing variable '' with order '2' contains zero MathML child elements.",
        "Reset in component 'component2' does not reference a variable in the component.",
        "Reset in component 'component2' referencing variable '' does not have an order defined.",
        "When in reset referencing variable '' with order '' does not have an order defined.",
        "When in reset referencing variable '' with order '' contains zero MathML child elements.",
        "Reset in component 'component2' referencing variable '' has an invalid child element 'about'.",
        "Reset in component 'component2' referencing variable 'V_k' has a non-integer order value '-'.",
        "Reset in component 'component2' has an invalid attribute 'start'.",
        "Reset in component 'component2' referencing variable 'variable1' has an invalid non-whitespace child text element '\n      non empty whitespace.\n      '.",
        "When in reset referencing variable 'variable1' with order '0' has an invalid non-whitespace child text element '\n        illegal content.\n        '.",
        "When in reset referencing variable 'variable1' with order '0' has an invalid child element 'variable'."};

    libcellml::Parser parser;
    parser.parseModel(input);
    EXPECT_EQ(expectedErrors.size(), parser.errorCount());
    for (size_t i = 0; i < parser.errorCount(); ++i) {
        EXPECT_EQ(expectedErrors.at(i), parser.error(i)->description());
    }
}

TEST(Parser, parseResetsCheckResetObjectCheckWhenObject)
{
    const std::string input =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/2.0#\" id=\"mid\">\n"
        "  <component name=\"component2\" id=\"c2id\">\n"
        "    <variable name=\"variable1\" id=\"vid\"/>\n"
        "    <variable name=\"V_k\" id=\"vid\"/>\n"
        "    <reset variable=\"V_k\" order=\"a\" id=\"rid\">\n"
        "      <when order=\"5.9\" goods=\"socks\">\n"
        "        <math xmlns=\"http://www.w3.org/1998/Math/MathML\">\n"
        "          some condition in mathml\n"
        "        </math>\n"
        "      </when>\n"
        "    </reset>\n"
        "  </component>\n"
        "</model>\n";
    const std::vector<std::string> expectedErrors = {
        "Reset in component 'component2' referencing variable 'V_k' has a non-integer order value 'a'.",
        "When in reset referencing variable 'V_k' with order '' has an invalid attribute 'goods'.",
        "When in reset referencing variable 'V_k' with order '' does not have an order defined.",
        "When in reset referencing variable 'V_k' with order '' contains only one MathML child element.",
    };

    libcellml::Parser parser;
    libcellml::ModelPtr model = parser.parseModel(input);

    libcellml::ResetPtr resetExpected = model->component(0)->reset(0);
    libcellml::WhenPtr whenExpected = resetExpected->when(0);

    EXPECT_EQ(size_t(4), parser.errorCount());

    for (size_t i = 0; i < parser.errorCount(); ++i) {
        EXPECT_EQ(expectedErrors.at(i), parser.error(i)->description());
    }

    EXPECT_EQ(resetExpected, parser.error(0)->reset());
    EXPECT_EQ(whenExpected, parser.error(1)->when());
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

    libcellml::Parser parser;
    libcellml::ModelPtr model = parser.parseModel(input);

    libcellml::Printer printer;
    const std::string a = printer.printModel(model);
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
        "  <component>\n"
        "    <!-- THIS COMMENT SHOULD BE IGNORED 3 -->\n"
        "    <variable name=\"stan\" units=\"dimensionless\"/>\n"
        "    <variable name=\"V_k\" units=\"dimensionless\"><!-- THIS COMMENT SHOULD BE IGNORED 3a --></variable>\n"
        "    <reset variable=\"V_k\" order=\"2\" id=\"rid\">\n"
        "      <!-- THIS COMMENT SHOULD BE IGNORED 4 -->\n"
        "      <when order=\"5\">\n"
        "        <!-- THIS COMMENT SHOULD BE IGNORED 5 -->\n"
        "        <math xmlns=\"http://www.w3.org/1998/Math/MathML\">\n"
        "          some condition in mathml\n"
        "        </math>\n"
        "        <math xmlns=\"http://www.w3.org/1998/Math/MathML\">\n"
        "          some condition in mathml\n"
        "        </math>\n"
        "      </when>\n"
        "    </reset>\n"
        "  </component>\n"
        "</model>\n";

    libcellml::Parser parser;
    parser.parseModel(input);
    printErrors(parser);

    EXPECT_EQ(size_t(0), parser.errorCount());
}

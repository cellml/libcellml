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

#include <algorithm>
#include <iostream>
#include <libcellml>
#include <string>
#include <vector>

TEST(Parser, invalidXMLElements) {
    const std::string input =
            "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
            "<fellowship>"
                "<Dwarf bearded>Gimli</ShortGuy>"
                "<Hobbit>Frodo</EvenShorterGuy>"
                "<Wizard>Gandalf</SomeGuyWithAStaff>"
                "<Elf>"
            "</fellows>";

    std::vector<std::string> expectedErrors = {
        "Specification mandate value for attribute bearded.",
        "Specification mandates value for attribute bearded.",
        "Opening and ending tag mismatch: Dwarf line 2 and ShortGuy.",
        "Opening and ending tag mismatch: Hobbit line 2 and EvenShorterGuy.",
        "Opening and ending tag mismatch: Wizard line 2 and SomeGuyWithAStaff.",
        "Opening and ending tag mismatch: Elf line 2 and fellows.",
        "Premature end of data in tag fellowship line 2.",
        "Could not get a valid XML root node from the provided input."
    };

    libcellml::Parser p;
    p.parseModel(input);

    EXPECT_EQ(expectedErrors.size()-1, p.errorCount());
    for (size_t i = 0; i < p.errorCount(); ++i) {
        if (i == 0) {
            EXPECT_TRUE(   !p.getError(i)->getDescription().compare(expectedErrors.at(0))
                        || !p.getError(i)->getDescription().compare(expectedErrors.at(1)));
        } else {
            EXPECT_EQ(expectedErrors.at(i+1), p.getError(i)->getDescription());
        }
    }
}

TEST(Parser, parse) {
    const std::string e =
            "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
            "<model xmlns=\"http://www.cellml.org/cellml/2.0#\"/>";

    libcellml::Parser parser;
    libcellml::ModelPtr model = parser.parseModel(e);
    libcellml::Printer printer;
    const std::string a = printer.printModel(model);
    EXPECT_EQ(e, a);
}

TEST(Parser, parseNamedModel) {
    const std::string n = "name";
    const std::string e =
            "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
            "<model xmlns=\"http://www.cellml.org/cellml/2.0#\" name=\"name\"/>";

    libcellml::Parser parser;
    libcellml::ModelPtr model = parser.parseModel(e);
    EXPECT_EQ(n, model->getName());

    libcellml::Printer printer;
    const std::string a = printer.printModel(model);
    EXPECT_EQ(e, a);
}

TEST(Parser, moveParser) {
    libcellml::Parser p, pm, pa;
    pa = p;
    pm = std::move(p);

    libcellml::Parser pc(pm);
}

TEST(Parser, makeError) {
    const std::string ex = "";

    libcellml::ErrorPtr e = std::make_shared<libcellml::Error>();

    EXPECT_EQ(ex, e->getDescription());
}

TEST(Parser, emptyModelString) {
    const std::string ex = "";
    const std::string expectedError = "Document is empty.";

    libcellml::Parser p;
    p.parseModel(ex);
    EXPECT_EQ(expectedError, p.getError(0)->getDescription());
}

TEST(Parser, nonXmlString) {
    const std::string ex = "Not an xml string.";
    std::vector<std::string> expectedErrors = {
        "Start tag expected, '<' not found.",
        "Could not get a valid XML root node from the provided input."
    };

    libcellml::Parser p;
    p.parseModel(ex);
    EXPECT_EQ(expectedErrors.size(), p.errorCount());
    for (size_t i = 0; i < p.errorCount(); ++i) {
        EXPECT_EQ(expectedErrors.at(i), p.getError(i)->getDescription());
    }
}

TEST(Parser, invalidRootNode) {
    const std::string ex =
            "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
            "<yodel xmlns=\"http://www.cellml.org/cellml/2.0#\" name=\"model_name\">"
            "</yodel>";

    const std::string expectedError1 = "Model root node is of invalid type 'yodel'. A valid CellML root node should be of type 'model'.";

    libcellml::Parser p;
    p.parseModel(ex);
    EXPECT_EQ(1, p.errorCount());
    EXPECT_EQ(expectedError1, p.getError(0)->getDescription());
}

TEST(Parser, invalidModelAttribute) {
    const std::string ex =
            "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
            "<model xmlns=\"http://www.cellml.org/cellml/2.0#\" game=\"model_name\"/>";

    const std::string expectedError1 = "Model '' has an invalid attribute 'game'.";

    libcellml::Parser p;
    p.parseModel(ex);
    EXPECT_EQ(1, p.errorCount());
    EXPECT_EQ(expectedError1, p.getError(0)->getDescription());
}

TEST(Parser, invalidModelElement) {
    const std::string ex =
            "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
            "<model xmlns=\"http://www.cellml.org/cellml/2.0#\" name=\"model_name\">"
                "<uknits/>"
            "</model>";

    const std::string expectedError1 = "Model 'model_name' has an invalid child element 'uknits'.";

    libcellml::Parser p;
    p.parseModel(ex);
    EXPECT_EQ(1, p.errorCount());
    EXPECT_EQ(expectedError1, p.getError(0)->getDescription());
}

TEST(Parser, modelWithInvalidElement) {
    const std::string input1 =
            "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
            "<model xmlns=\"http://www.cellml.org/cellml/2.0#\" name=\"bilbo\">"
                "<hobbit/>"
            "</model>";

    const std::string expectError1 = "Model 'bilbo' has an invalid child element 'hobbit'.";

    const std::string input2 =
            "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
            "<model xmlns=\"http://www.cellml.org/cellml/2.0#\">"
                "<hobbit/>"
            "</model>";

    const std::string expectError2 = "Model '' has an invalid child element 'hobbit'.";

    libcellml::Parser p;
    p.parseModel(input1);
    EXPECT_EQ(1, p.errorCount());
    EXPECT_EQ(expectError1, p.getError(0)->getDescription());

    p.clearErrors();
    p.parseModel(input2);
    EXPECT_EQ(1, p.errorCount());
    EXPECT_EQ(expectError2, p.getError(0)->getDescription());
}

TEST(Parser, parseModelWithInvalidAttributeAndGetError) {
    const std::string input =
            "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
            "<model xmlns=\"http://www.cellml.org/cellml/2.0#\" name=\"modelName\" nonsense=\"oops\"/>";

    const std::string expectedError = "Model 'modelName' has an invalid attribute 'nonsense'.";

    libcellml::Parser parser;
    libcellml::ModelPtr model = parser.parseModel(input);

    EXPECT_EQ(1, parser.errorCount());
    EXPECT_EQ(expectedError, parser.getError(0)->getDescription());

    // Get ModelError and check.
    EXPECT_EQ(model, parser.getError(0)->getModel());
    // Get const modelError and check.
    const libcellml::ErrorPtr err = static_cast<const libcellml::Parser>(parser).getError(0);
    libcellml::Error *rawErr = err.get();
    const libcellml::ModelPtr modelFromError = static_cast<const libcellml::Error*>(rawErr)->getModel();
    EXPECT_EQ(model, modelFromError);
}

TEST(Parser, parseNamedModelWithNamedComponent) {
    const std::string mName = "modelName";
    const std::string cName = "componentName";
    const std::string e =
            "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
            "<model xmlns=\"http://www.cellml.org/cellml/2.0#\" name=\"modelName\">"
                "<component name=\"componentName\"/>"
            "</model>";

    libcellml::Parser parser;
    libcellml::ModelPtr model = parser.parseModel(e);
    EXPECT_EQ(mName, model->getName());
    libcellml::ComponentPtr c = model->getComponent(cName);
    EXPECT_EQ(cName, c->getName());

    libcellml::Printer printer;
    const std::string a = printer.printModel(model);
    EXPECT_EQ(e, a);
}

TEST(Parser, parseModelWithUnitsAndNamedComponent) {
    const std::string e =
            "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
            "<model xmlns=\"http://www.cellml.org/cellml/2.0#\" name=\"model_name\">"
                "<units name=\"fahrenheitish\">"
                    "<unit multiplier=\"1.8\" units=\"celsius\"/>"
                "</units>"
                "<units name=\"dimensionless\"/>"
                "<component name=\"component_name\"/>"
            "</model>";

    libcellml::Parser parser;
    libcellml::ModelPtr model = parser.parseModel(e);

    libcellml::Printer printer;
    const std::string a = printer.printModel(model);
    EXPECT_EQ(e, a);
}

TEST(Parser, unitsAttributeError) {
    const std::string ex =
            "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
            "<model xmlns=\"http://www.cellml.org/cellml/2.0#\" name=\"model_name\">"
                "<units name=\"pH\" invalid_attribute=\"yes\"/>"
            "</model>";

    const std::string expectedError1 = "Units 'pH' has an invalid attribute 'invalid_attribute'.";

    libcellml::Parser p;
    p.parseModel(ex);
    EXPECT_EQ(1, p.errorCount());
    EXPECT_EQ(expectedError1, p.getError(0)->getDescription());
}

TEST(Parser, unitsElementErrors) {
    const std::string input1 =
            "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
            "<model xmlns=\"http://www.cellml.org/cellml/2.0#\" name=\"model_name\">"
                "<units>"
                    "<son name=\"stan\"/>"
                "</units>"
            "</model>";

    const std::string expectError1 = "Units '' has an invalid child element 'son'.";

    const std::string input2 =
            "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
            "<model xmlns=\"http://www.cellml.org/cellml/2.0#\" name=\"model_name\">"
                "<units name=\"randy\">"
                    "<son name=\"stan\"/>"
                "</units>"
            "</model>";

    const std::string expectError2 = "Units 'randy' has an invalid child element 'son'.";

    libcellml::Parser p;
    p.parseModel(input1);
    EXPECT_EQ(1, p.errorCount());
    EXPECT_EQ(expectError1, p.getError(0)->getDescription());

    p.clearErrors();
    p.parseModel(input2);
    EXPECT_EQ(1, p.errorCount());
    EXPECT_EQ(expectError2, p.getError(0)->getDescription());
}

TEST(Parser, parseModelWithNamedComponentWithInvalidBaseUnitsAttributeAndGetError) {
    const std::string in =
            "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
            "<model xmlns=\"http://www.cellml.org/cellml/2.0#\" name=\"model_name\">"
                "<units name=\"unit_name\" base_unit=\"yes\"/>"
                "<component name=\"component_name\">"
                "</component>"
            "</model>";

    const std::string expectedError1 = "Units 'unit_name' has an invalid attribute 'base_unit'.";

    libcellml::Parser parser;
    libcellml::ModelPtr model = parser.parseModel(in);

    EXPECT_EQ(1, parser.errorCount());
    EXPECT_EQ(expectedError1, parser.getError(0)->getDescription());

    libcellml::UnitsPtr unitsExpected = model->getUnits("unit_name");

    // Get units from error and check.
    EXPECT_EQ(unitsExpected, parser.getError(0)->getUnits());

    // Get const units from error and check.
    const libcellml::ErrorPtr err = static_cast<const libcellml::Parser>(parser).getError(0);
    const libcellml::UnitsPtr unitsFromError = err->getUnits();
    EXPECT_EQ(unitsExpected, unitsFromError);
}

TEST(Parser, parseModelWithInvalidComponentAttributeAndGetError) {
    const std::string cName = "componentName";
    const std::string input =
            "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
            "<model xmlns=\"http://www.cellml.org/cellml/2.0#\" name=\"modelName\">"
                "<component name=\"componentName\" nonsense=\"oops\"/>"
            "</model>";

    const std::string expectedError = "Component 'componentName' has an invalid attribute 'nonsense'.";

    libcellml::Parser parser;
    libcellml::ModelPtr model = parser.parseModel(input);
    libcellml::ComponentPtr component = model->getComponent(cName);

    EXPECT_EQ(1, parser.errorCount());
    EXPECT_EQ(expectedError, parser.getError(0)->getDescription());

    // Get component from error and check.
    EXPECT_EQ(component, parser.getError(0)->getComponent());
    // Get const component from error and check.
    const libcellml::ErrorPtr err = static_cast<const libcellml::Parser>(parser).getError(0);
    libcellml::Error *rawErr = err.get();
    const libcellml::ComponentPtr componentFromError = static_cast<const libcellml::Error*>(rawErr)->getComponent();
    EXPECT_EQ(component, componentFromError);

    // Get non-existent error
    EXPECT_EQ(nullptr, parser.getError(1));
}

TEST(Parser, componentAttributeErrors) {
    const std::string input1 =
            "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
            "<model xmlns=\"http://www.cellml.org/cellml/2.0#\" name=\"model_name\">"
                "<component lame=\"randy\"/>"
            "</model>";

    const std::string expectError1 = "Component '' has an invalid attribute 'lame'.";

    const std::string input2 =
            "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
            "<model xmlns=\"http://www.cellml.org/cellml/2.0#\" name=\"model_name\">"
                "<component name=\"randy\" son=\"stan\"/>"
            "</model>";

    const std::string expectError2 = "Component 'randy' has an invalid attribute 'son'.";

    const std::string input3 =
            "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
            "<model xmlns=\"http://www.cellml.org/cellml/2.0#\" name=\"model_name\">"
                "<component son=\"stan\" name=\"randy\"/>"
            "</model>";

    const std::string expectError3 = "Component 'randy' has an invalid attribute 'son'.";

    libcellml::Parser p;
    p.parseModel(input1);
    EXPECT_EQ(1, p.errorCount());
    EXPECT_EQ(expectError1, p.getError(0)->getDescription());

    p.clearErrors();
    p.parseModel(input2);
    EXPECT_EQ(1, p.errorCount());
    EXPECT_EQ(expectError2, p.getError(0)->getDescription());

    p.clearErrors();
    p.parseModel(input3);
    EXPECT_EQ(1, p.errorCount());
    EXPECT_EQ(expectError3, p.getError(0)->getDescription());
}

TEST(Parser, componentElementErrors) {
    const std::string input1 =
            "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
            "<model xmlns=\"http://www.cellml.org/cellml/2.0#\" name=\"model_name\">"
                "<component>"
                    "<son name=\"stan\"/>"
                "</component>"
            "</model>";

    const std::string expectError1 = "Component '' has an invalid child element 'son'.";

    const std::string input2 =
            "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
            "<model xmlns=\"http://www.cellml.org/cellml/2.0#\" name=\"model_name\">"
                "<component name=\"randy\">"
                    "<son name=\"stan\"/>"
                "</component>"
            "</model>";

    const std::string expectError2 = "Component 'randy' has an invalid child element 'son'.";

    libcellml::Parser p;
    p.parseModel(input1);
    EXPECT_EQ(1, p.errorCount());
    EXPECT_EQ(expectError1, p.getError(0)->getDescription());

    p.clearErrors();
    p.parseModel(input2);
    EXPECT_EQ(1, p.errorCount());
    EXPECT_EQ(expectError2, p.getError(0)->getDescription());
}

TEST(Parser, parseModelWithTwoComponents) {
    const std::string e =
            "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
            "<model xmlns=\"http://www.cellml.org/cellml/2.0#\" name=\"modelName\">"
                "<component name=\"component1\"/>"
                "<component name=\"component2\"/>"
            "</model>";

    libcellml::Parser parser;
    libcellml::ModelPtr model = parser.parseModel(e);

    libcellml::Printer printer;
    const std::string a = printer.printModel(model);
    EXPECT_EQ(e, a);
}

TEST(Parser, parseModelWithComponentHierarchyWaterfall) {
    const std::string e =
            "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
            "<model xmlns=\"http://www.cellml.org/cellml/2.0#\">"
                "<component name=\"dave\"/>"
                "<component name=\"bob\"/>"
                "<component name=\"angus\"/>"
                "<encapsulation>"
                    "<component_ref component=\"dave\">"
                        "<component_ref component=\"bob\">"
                            "<component_ref component=\"angus\"/>"
                        "</component_ref>"
                    "</component_ref>"
                "</encapsulation>"
            "</model>";

    libcellml::Parser parser;
    libcellml::ModelPtr model = parser.parseModel(e);

    libcellml::Printer printer;
    const std::string a = printer.printModel(model);
    EXPECT_EQ(e, a);
}

TEST(Parser, parseModelWithMultipleComponentHierarchyWaterfalls) {
    const std::string e =
            "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
            "<model xmlns=\"http://www.cellml.org/cellml/2.0#\">"
                "<component name=\"ignatio\"/>"
                "<component name=\"dave\"/>"
                "<component name=\"bob\"/>"
                "<component name=\"angus\"/>"
                "<component name=\"jackie\"/>"
                "<encapsulation>"
                    "<component_ref component=\"dave\">"
                        "<component_ref component=\"bob\">"
                            "<component_ref component=\"angus\"/>"
                            "<component_ref component=\"jackie\"/>"
                        "</component_ref>"
                    "</component_ref>"
                "</encapsulation>"
                "<component name=\"mildred\"/>"
                "<component name=\"sue\"/>"
                "<encapsulation>"
                    "<component_ref component=\"mildred\">"
                        "<component_ref component=\"sue\"/>"
                    "</component_ref>"
                "</encapsulation>"
            "</model>";

    libcellml::Parser parser;
    libcellml::ModelPtr model = parser.parseModel(e);

    libcellml::Printer printer;
    const std::string a = printer.printModel(model);
    EXPECT_EQ(e, a);
}

TEST(Parser, modelWithUnits) {
    const std::string in =
            "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
            "<model xmlns=\"http://www.cellml.org/cellml/2.0#\" name=\"model_name\">"
                "<units name=\"fahrenheitish\">"
                    "<unit multiplier=\"1.8\" units=\"celsius\"/>"
                "</units>"
                "<units name=\"dimensionless\"/>"
            "</model>";

    const std::string e =
            "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
            "<model xmlns=\"http://www.cellml.org/cellml/2.0#\" name=\"model_name\">"
                "<units name=\"fahrenheitish\">"
                    "<unit multiplier=\"1.8\" units=\"celsius\"/>"
                "</units>"
                "<units name=\"dimensionless\"/>"
            "</model>";

    libcellml::Parser parser;
    libcellml::ModelPtr model = parser.parseModel(in);

    libcellml::Printer printer;
    const std::string a = printer.printModel(model);
    EXPECT_EQ(e, a);
}

TEST(Parser, modelWithInvalidUnits) {
    const std::string in =
            "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
            "<model xmlns=\"http://www.cellml.org/cellml/2.0#\" name=\"model_name\">"
                "<units name=\"fahrenheitish\" temperature=\"451\">"
                    "<unit multiplier=\"Z\" exponent=\"35.0E+310\" units=\"celsius\" bill=\"murray\">"
                        "<degrees/>"
                    "</unit>"
                    "<bobshouse address=\"34 Rich Lane\"/>"
                    "<unit GUnit=\"50c\"/>"
                "</units>"
                "<units name=\"dimensionless\"/>"
                "<units jerry=\"seinfeld\">"
                    "<unit units=\"friends\" neighbor=\"kramer\"/>"
                    "<unit george=\"friends\"/>"
                "</units>"
            "</model>";

    const std::string e =
            "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
            "<model xmlns=\"http://www.cellml.org/cellml/2.0#\" name=\"model_name\">"
                "<units name=\"fahrenheitish\">"
                    "<unit units=\"celsius\"/>"
                    "<unit units=\"\"/>"
                "</units>"
                "<units name=\"dimensionless\"/>"
            "</model>";

    std::vector<std::string> expectedErrors = {
        "Units 'fahrenheitish' has an invalid attribute 'temperature'.",
        "Unit referencing 'celsius' in units 'fahrenheitish' has an invalid child element 'degrees'.",
        "Unit referencing 'celsius' in units 'fahrenheitish' has a multiplier with the value 'Z' that cannot be converted to a decimal number.",
        "Unit referencing 'celsius' in units 'fahrenheitish' has an exponent with the value '35.0E+310' that cannot be converted to a decimal number.",
        "Unit referencing 'celsius' in units 'fahrenheitish' has an invalid attribute 'bill'.",
        "Units 'fahrenheitish' has an invalid child element 'bobshouse'.",
        "Unit referencing '' in units 'fahrenheitish' has an invalid attribute 'GUnit'.",
        "Units '' has an invalid attribute 'jerry'.",
        "Unit referencing 'friends' in units '' has an invalid attribute 'neighbor'.",
        "Unit referencing '' in units '' has an invalid attribute 'george'."
    };

    libcellml::Parser parser;
    libcellml::ModelPtr model = parser.parseModel(in);

    EXPECT_EQ(expectedErrors.size(), parser.errorCount());
    for (size_t i = 0; i < parser.errorCount(); ++i) {
        EXPECT_EQ(expectedErrors.at(i), parser.getError(i)->getDescription());
    }

    libcellml::Printer printer;
    const std::string a = printer.printModel(model);
    EXPECT_EQ(e, a);
}

TEST(Parser, emptyEncapsulation) {
    const std::string ex =
            "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
            "<model xmlns=\"http://www.cellml.org/cellml/2.0#\" name=\"model_name\">"
                "<encapsulation/>"
            "</model>";

    const std::string expectedError = "Encapsulation in model 'model_name' does not contain any child elements.";

    libcellml::Parser p;
    p.parseModel(ex);
    EXPECT_EQ(1, p.errorCount());
    EXPECT_EQ(expectedError, p.getError(0)->getDescription());
}

TEST(Parser, encapsulationWithNoComponentAttribute) {
    const std::string ex =
            "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
            "<model xmlns=\"http://www.cellml.org/cellml/2.0#\" name=\"model_name\">"
                "<encapsulation>"
                    "<component_ref/>"
                "</encapsulation>"
            "</model>";

    const std::string expectedError1 = "Encapsulation in model 'model_name' does not have a valid component attribute in a component_ref element.";
    const std::string expectedError2 = "Encapsulation in model 'model_name' specifies an invalid parent component_ref that also does not have any children.";

    libcellml::Parser p;
    p.parseModel(ex);
    EXPECT_EQ(2, p.errorCount());
    EXPECT_EQ(expectedError1, p.getError(0)->getDescription());
    EXPECT_EQ(expectedError2, p.getError(1)->getDescription());
}

TEST(Parser, encapsulationWithNoComponentRef) {
    const std::string ex =
            "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
            "<model xmlns=\"http://www.cellml.org/cellml/2.0#\" name=\"model_name\">"
                "<encapsulation>"
                    "<component_free/>"
                "</encapsulation>"
            "</model>";

    const std::string expectedError1 = "Encapsulation in model 'model_name' has an invalid child element 'component_free'.";
    const std::string expectedError2 = "Encapsulation in model 'model_name' specifies an invalid parent component_ref that also does not have any children.";

    libcellml::Parser p;
    p.parseModel(ex);
    EXPECT_EQ(2, p.errorCount());
    EXPECT_EQ(expectedError1, p.getError(0)->getDescription());
    EXPECT_EQ(expectedError2, p.getError(1)->getDescription());
}

TEST(Parser, encapsulationWithNoComponent) {
    const std::string ex =
            "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
            "<model xmlns=\"http://www.cellml.org/cellml/2.0#\" name=\"model_name\">"
                "<encapsulation>"
                    "<component_ref component=\"bob\">"
                        "<component_ref/>"
                    "</component_ref>"
                "</encapsulation>"
            "</model>";

    const std::string expectedError1 = "Encapsulation in model 'model_name' specifies 'bob' as a component in a component_ref but it does not exist in the model.";
    const std::string expectedError2 = "Encapsulation in model 'model_name' does not have a valid component attribute in a component_ref that is a child of invalid parent component 'bob'.";

    libcellml::Parser p;
    p.parseModel(ex);
    EXPECT_EQ(2, p.errorCount());
    EXPECT_EQ(expectedError1, p.getError(0)->getDescription());
    EXPECT_EQ(expectedError2, p.getError(1)->getDescription());
}

TEST(Parser, encapsulationWithMissingComponent) {
    const std::string ex =
            "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
            "<model xmlns=\"http://www.cellml.org/cellml/2.0#\" name=\"model_name\">"
                "<component name=\"bob\"/>"
                "<encapsulation>"
                    "<component_ref component=\"bob\">"
                        "<component_ref component=\"dave\"/>"
                    "</component_ref>"
                "</encapsulation>"
            "</model>";

    const std::string expectedError1 = "Encapsulation in model 'model_name' specifies 'dave' as a component in a component_ref but it does not exist in the model.";

    libcellml::Parser p;
    p.parseModel(ex);
    EXPECT_EQ(1, p.errorCount());
    EXPECT_EQ(expectedError1, p.getError(0)->getDescription());
}

TEST(Parser, encapsulationWithNoComponentChild) {
    const std::string ex =
            "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
            "<model xmlns=\"http://www.cellml.org/cellml/2.0#\" name=\"model_name\">"
                "<component name=\"bob\"/>"
                "<encapsulation>"
                    "<component_ref component=\"bob\"/>"
                "</encapsulation>"
            "</model>";

    const std::string expectedError = "Encapsulation in model 'model_name' specifies 'bob' as a parent component_ref but it does not have any children.";

    libcellml::Parser p;
    p.parseModel(ex);
    EXPECT_EQ(1, p.errorCount());
    EXPECT_EQ(expectedError, p.getError(0)->getDescription());
}

TEST(Parser, encapsulationNoChildComponentRef) {
    const std::string ex =
            "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
            "<model xmlns=\"http://www.cellml.org/cellml/2.0#\" name=\"model_name\">"
                "<component name=\"bob\"/>"
                "<encapsulation>"
                    "<component_ref component=\"bob\">"
                        "<component_free/>"
                    "</component_ref>"
                "</encapsulation>"
            "</model>";

    const std::string expectedError = "Encapsulation in model 'model_name' has an invalid child element 'component_free'.";

    libcellml::Parser p;
    p.parseModel(ex);
    EXPECT_EQ(1, p.errorCount());
    EXPECT_EQ(expectedError, p.getError(0)->getDescription());
}

TEST(Parser, encapsulationWithNoGrandchildComponentRef) {
    const std::string ex =
            "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
            "<model xmlns=\"http://www.cellml.org/cellml/2.0#\" name=\"model_name\">"
                "<component name=\"bob\"/>"
                "<component name=\"jim\"/>"
                "<encapsulation>"
                    "<component_ref component=\"bob\">"
                        "<component_ref component=\"jim\">"
                            "<component_free/>"
                        "</component_ref>"
                    "</component_ref>"
                "</encapsulation>"
            "</model>";

    const std::string expectedError = "Encapsulation in model 'model_name' has an invalid child element 'component_free'.";

    libcellml::Parser p;
    p.parseModel(ex);
    EXPECT_EQ(1, p.errorCount());
    EXPECT_EQ(expectedError, p.getError(0)->getDescription());
}

TEST(Parser, invalidEncapsulations) {
    const std::string e =
            "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
            "<model xmlns=\"http://www.cellml.org/cellml/2.0#\" name=\"ringo\">"
                "<component name=\"dave\"/>"
                "<component name=\"bob\"/>"
                "<encapsulation relationship=\"friends\">"
                    "<component_ref component=\"dave\" bogus=\"oops\">"
                        "<component_ref component=\"bob\" bogus=\"oops\"/>"
                        "<component_ref enemy=\"ignatio\"/>"
                    "</component_ref>"
                    "<component_ref component=\"ignatio\"/>"
                    "<component_ref>"
                        "<component_ref/>"
                    "</component_ref>"
                "</encapsulation>"
            "</model>";

    std::vector<std::string> expectedErrors = {
        "Encapsulation in model 'ringo' has an invalid attribute 'relationship'.",
        "Encapsulation in model 'ringo' has an invalid component_ref attribute 'bogus'.",
        "Encapsulation in model 'ringo' has an invalid component_ref attribute 'bogus'.",
        "Encapsulation in model 'ringo' has an invalid component_ref attribute 'enemy'.",
        "Encapsulation in model 'ringo' does not have a valid component attribute in a component_ref that is a child of 'dave'.",
        "Encapsulation in model 'ringo' specifies 'ignatio' as a component in a component_ref but it does not exist in the model.",
        "Encapsulation in model 'ringo' specifies an invalid parent component_ref that also does not have any children.",
        "Encapsulation in model 'ringo' does not have a valid component attribute in a component_ref element.",
        "Encapsulation in model 'ringo' does not have a valid component attribute in a component_ref that is a child of an invalid parent component."
    };

    libcellml::Parser parser;
    parser.parseModel(e);

    EXPECT_EQ(expectedErrors.size(), parser.errorCount());
    for (size_t i = 0; i < parser.errorCount(); ++i) {
        EXPECT_EQ(expectedErrors.at(i), parser.getError(i)->getDescription());
    }
}

TEST(Parser, invalidVariableAttributesAndGetVariableError) {
    const std::string in =
            "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
            "<model xmlns=\"http://www.cellml.org/cellml/2.0#\">"
                "<component name=\"componentA\">"
                    "<variable name=\"quixote\" don=\"true\"/>"
                    "<variable windmill=\"tilted\"/>"
                "</component>"
            "</model>";

    const std::string expectError1 = "Variable 'quixote' has an invalid attribute 'don'.";
    const std::string expectError2 = "Variable '' has an invalid attribute 'windmill'.";

    libcellml::Parser p;
    libcellml::ModelPtr model = p.parseModel(in);
    EXPECT_EQ(2, p.errorCount());
    EXPECT_EQ(expectError1, p.getError(0)->getDescription());
    EXPECT_EQ(expectError2, p.getError(1)->getDescription());

    libcellml::VariablePtr variableExpected = model->getComponent("componentA")->getVariable("quixote");
    // Get variable from error and check.
    EXPECT_EQ(variableExpected, p.getError(0)->getVariable());
    // Get const variable from error and check.
    libcellml::ErrorPtr err = static_cast<const libcellml::Parser>(p).getError(0);
    libcellml::Error *rawErr = err.get();
    const libcellml::VariablePtr variableFromError = static_cast<const libcellml::Error*>(rawErr)->getVariable();
    EXPECT_EQ(variableExpected, variableFromError);
}

TEST(Parser, variableAttributeAndChildErrors) {
    const std::string input1 =
            "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
            "<model xmlns=\"http://www.cellml.org/cellml/2.0#\" name=\"model_name\">"
                "<component name=\"randy\">"
                    "<variable lame=\"randy\"/>"
                "</component>"
            "</model>";

    const std::string expectError1 = "Variable '' has an invalid attribute 'lame'.";

    const std::string input2 =
            "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
            "<model xmlns=\"http://www.cellml.org/cellml/2.0#\" name=\"model_name\">"
                "<component name=\"randy\">"
                    "<variable name=\"randy\" son=\"stan\">"
                        "<daughter name=\"shelly\"/>"
                    "</variable>"
                "</component>"
            "</model>";

    const std::string expectError2 = "Variable 'randy' has an invalid child element 'daughter'.";
    const std::string expectError3 = "Variable 'randy' has an invalid attribute 'son'.";


    libcellml::Parser p;
    p.parseModel(input1);
    EXPECT_EQ(1, p.errorCount());
    EXPECT_EQ(expectError1, p.getError(0)->getDescription());

    p.clearErrors();
    p.parseModel(input2);
    EXPECT_EQ(2, p.errorCount());
    EXPECT_EQ(expectError2, p.getError(0)->getDescription());
    EXPECT_EQ(expectError3, p.getError(1)->getDescription());
}

TEST(Parser, emptyConnections) {
    const std::string ex =
            "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
            "<model xmlns=\"http://www.cellml.org/cellml/2.0#\" name=\"model_name\">"
                "<connection/>"
            "</model>";

    const std::string expectedError1 = "Connection in model 'model_name' does not have a valid component_1 in a connection element.";
    const std::string expectedError2 = "Connection in model 'model_name' does not have a valid component_2 in a connection element.";
    const std::string expectedError3 = "Connection in model 'model_name' must contain one or more 'map_variables' elements.";

    libcellml::Parser p;
    p.parseModel(ex);
    EXPECT_EQ(3, p.errorCount());
    EXPECT_EQ(expectedError1, p.getError(0)->getDescription());
    EXPECT_EQ(expectedError2, p.getError(1)->getDescription());
    EXPECT_EQ(expectedError3, p.getError(2)->getDescription());
}

TEST(Parser, connectionErrorNoComponent2) {
    const std::string in =
            "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
            "<model xmlns=\"http://www.cellml.org/cellml/2.0#\" name=\"modelA\">"
                "<component name=\"componentA\">"
                    "<variable name=\"variable1\"/>"
                "</component>"
                "<connection component_1=\"component1\">"
                    "<map_variables variable_1=\"variable1\" variable_2=\"variable2\"/>"
                "</connection>"
            "</model>";

    const std::string expectedError1 = "Connection in model 'modelA' does not have a valid component_2 in a connection element.";
    const std::string expectedError2 = "Connection in model 'modelA' specifies 'component1' as component_1 but it does not exist in the model.";
    const std::string expectedError3 = "Connection in model 'modelA' specifies 'variable1' as variable_1 but the corresponding component_1 is invalid.";
    const std::string expectedError4 = "Connection in model 'modelA' specifies 'variable2' as variable_2 but the corresponding component_2 is invalid.";

    libcellml::Parser p;
    p.parseModel(in);
    EXPECT_EQ(4, p.errorCount());
    EXPECT_EQ(expectedError1, p.getError(0)->getDescription());
    EXPECT_EQ(expectedError2, p.getError(1)->getDescription());
    EXPECT_EQ(expectedError3, p.getError(2)->getDescription());
    EXPECT_EQ(expectedError4, p.getError(3)->getDescription());
}

TEST(Parser, connectionErrorNoComponent2InModel) {
    const std::string in =
            "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
            "<model xmlns=\"http://www.cellml.org/cellml/2.0#\" name=\"modelName\">"
                "<component name=\"component1\">"
                    "<variable name=\"variable1\"/>"
                "</component>"
                "<connection  component_1=\"component1\"  component_2=\"component2\">"
                    "<map_variables variable_1=\"variable1\" variable_2=\"variable2\"/>"
                "</connection>"
            "</model>";

    const std::string expectedError1 = "Connection in model 'modelName' specifies 'component2' as component_2 but it does not exist in the model.";
    const std::string expectedError2 = "Connection in model 'modelName' specifies 'variable2' as variable_2 but the corresponding component_2 is invalid.";

    libcellml::Parser p;
    p.parseModel(in);
    EXPECT_EQ(2, p.errorCount());
    EXPECT_EQ(expectedError1, p.getError(0)->getDescription());
    EXPECT_EQ(expectedError2, p.getError(1)->getDescription());
}

TEST(Parser, connectionErrorNoComponent1) {
    const std::string in =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/2.0#\" name=\"modelName\">"
            "<component name=\"componentA\">"
                "<variable name=\"variable1\"/>"
            "</component>"
            "<connection  component_2=\"componentA\">"
                "<map_variables variable_1=\"variable1\" variable_2=\"variable2\"/>"
            "</connection>"
        "</model>";

    const std::string expectedError1 = "Connection in model 'modelName' does not have a valid component_1 in a connection element.";
    const std::string expectedError2 = "Connection in model 'modelName' specifies 'variable1' as variable_1 but the corresponding component_1 is invalid.";
    const std::string expectedError3 = "Variable 'variable2' is specified as variable_2 in a connection but it does not exist in component_2 component 'componentA' of model 'modelName'.";

    libcellml::Parser p;
    p.parseModel(in);
    EXPECT_EQ(3, p.errorCount());
    EXPECT_EQ(expectedError1, p.getError(0)->getDescription());
    EXPECT_EQ(expectedError2, p.getError(1)->getDescription());
    EXPECT_EQ(expectedError3, p.getError(2)->getDescription());
}

TEST(Parser, connectionErrorNoMapComponents) {
    const std::string in =
            "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
            "<model xmlns=\"http://www.cellml.org/cellml/2.0#\" name=\"modelName\">"
                "<component name=\"componentA\">"
                    "<variable name=\"variable1\"/>"
                "</component>"
                "<connection name=\"invalid\">"
                    "<map_variables variable_1=\"variable1\" variable_2=\"variable2\" variable_3=\"variable3\">"
                        "<map_units/>"
                    "</map_variables>"
                "</connection>"
            "</model>";

    std::vector<std::string> expectedErrors = {
        "Connection in model 'modelName' has an invalid connection attribute 'name'.",
        "Connection in model 'modelName' does not have a valid component_1 in a connection element.",
        "Connection in model 'modelName' does not have a valid component_2 in a connection element.",
        "Connection in model 'modelName' has an invalid child element 'map_units' of element 'map_variables'.",
        "Connection in model 'modelName' has an invalid map_variables attribute 'variable_3'.",
        "Connection in model 'modelName' specifies 'variable1' as variable_1 but the corresponding component_1 is invalid.",
        "Connection in model 'modelName' specifies 'variable2' as variable_2 but the corresponding component_2 is invalid."
    };

    libcellml::Parser parser;
    parser.parseModel(in);

    EXPECT_EQ(expectedErrors.size(), parser.errorCount());
    for (size_t i = 0; i < parser.errorCount(); ++i) {
        EXPECT_EQ(expectedErrors.at(i), parser.getError(i)->getDescription());
    }
}

TEST(Parser, connectionErrorNoMapVariables) {
    const std::string in =
            "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
            "<model xmlns=\"http://www.cellml.org/cellml/2.0#\">"
                "<component name=\"componentA\">"
                    "<variable name=\"variable1\"/>"
                "</component>"
                "<connection component_2=\"componentA\" component_1=\"componentA\" component_3=\"componentA\"/>"
                "<connection component_2=\"componentA\" component_1=\"componentA\"/>"
            "</model>";

    const std::string expectedError1 = "Connection in model '' has an invalid connection attribute 'component_3'.";
    const std::string expectedError2 = "Connection in model '' must contain one or more 'map_variables' elements.";
    const std::string expectedError3 = "Connection in model '' must contain one or more 'map_variables' elements.";

    libcellml::Parser p;
    p.parseModel(in);
    EXPECT_EQ(3, p.errorCount());
    EXPECT_EQ(expectedError1, p.getError(0)->getDescription());
    EXPECT_EQ(expectedError2, p.getError(1)->getDescription());
    EXPECT_EQ(expectedError3, p.getError(2)->getDescription());
}

TEST(Parser, importedComponent2Connection) {
    const std::string e =
            "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
            "<model xmlns=\"http://www.cellml.org/cellml/2.0#\">"
                "<import xlink:href=\"some-other-model.xml\" xmlns:xlink=\"http://www.w3.org/1999/xlink\">"
                    "<component component_ref=\"component_in_that_model\" name=\"component_in_this_model\"/>"
                "</import>"
                "<component name=\"component_bob\">"
                    "<variable name=\"variable_bob\"/>"
                "</component>"
                "<connection component_2=\"component_in_this_model\" component_1=\"component_bob\">"
                    "<map_variables variable_2=\"variable_import\" variable_1=\"variable_bob\"/>"
                "</connection>"
            "</model>";

    // Parse
    libcellml::Parser parser;
    parser.parseModel(e);
    EXPECT_EQ(0, parser.errorCount());
}

TEST(Parser, validConnectionMapVariablesFirst) {
    const std::string e =
            "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
            "<model xmlns=\"http://www.cellml.org/cellml/2.0#\">"
                "<component name=\"robert\">"
                    "<variable name=\"bob\"/>"
                "</component>"
                "<component name=\"james\">"
                    "<variable name=\"jimbo\"/>"
                "</component>"
                "<connection component_1=\"robert\" component_2=\"james\">"
                    "<map_variables variable_2=\"jimbo\" variable_1=\"bob\"/>"
                "</connection>"
            "</model>";

    libcellml::Parser parser;
    parser.parseModel(e);
    EXPECT_EQ(0, parser.errorCount());
}

TEST(Parser, component2ConnectionVariableMissing) {
    const std::string e =
            "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
            "<model xmlns=\"http://www.cellml.org/cellml/2.0#\">"
                "<component name=\"component_bob\">"
                    "<variable name=\"variable_bob\"/>"
                "</component>"
                "<component name=\"component_dave\">"
                    "<variable name=\"variable_dave\"/>"
                "</component>"
                "<connection component_2=\"component_dave\" component_1=\"component_bob\">"
                    "<map_variables variable_2=\"variable_angus\" variable_1=\"variable_bob\"/>"
                "</connection>"
            "</model>";

    const std::string expectedError = "Variable 'variable_angus' is specified as variable_2 in a connection but it does not exist in component_2 component 'component_dave' of model ''.";

    // Parse
    libcellml::Parser p;
    p.parseModel(e);
    EXPECT_EQ(1, p.errorCount());
    EXPECT_EQ(expectedError, p.getError(0)->getDescription());
}

TEST(Parser, component2InConnectionMissing) {
    const std::string in =
            "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
            "<model xmlns=\"http://www.cellml.org/cellml/2.0#\">"
                "<component name=\"component_bob\">"
                    "<variable name=\"variable_bob\"/>"
                "</component>"
                "<component name=\"component_dave\">"
                    "<variable name=\"variable_dave\"/>"
                "</component>"
                "<connection component_1=\"component_bob\">"
                    "<map_variables variable_2=\"variable_angus\" variable_1=\"variable_bob\"/>"
                "</connection>"
            "</model>";

    const std::string e =
            "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
            "<model xmlns=\"http://www.cellml.org/cellml/2.0#\">"
                "<component name=\"component_bob\">"
                    "<variable name=\"variable_bob\"/>"
                "</component>"
                "<component name=\"component_dave\">"
                    "<variable name=\"variable_dave\"/>"
                "</component>"
            "</model>";

    const std::string expectedError1 = "Connection in model '' does not have a valid component_2 in a connection element.";
    const std::string expectedError2 = "Connection in model '' specifies 'variable_angus' as variable_2 but the corresponding component_2 is invalid.";

    // Parse
    libcellml::Parser p;
    libcellml::ModelPtr m = p.parseModel(in);
    EXPECT_EQ(2, p.errorCount());

    libcellml::Printer printer;
    const std::string a = printer.printModel(m);
    EXPECT_EQ(e, a);
    EXPECT_EQ(expectedError1, p.getError(0)->getDescription());
    EXPECT_EQ(expectedError2, p.getError(1)->getDescription());
}

TEST(Parser, connectionVariable2Missing) {
    const std::string e =
            "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
            "<model xmlns=\"http://www.cellml.org/cellml/2.0#\">"
                "<component name=\"component_bob\">"
                    "<variable name=\"variable_bob\"/>"
                "</component>"
                "<component name=\"component_dave\">"
                    "<variable name=\"variable_dave\"/>"
                "</component>"
                "<connection component_2=\"component_dave\" component_1=\"component_bob\">"
                    "<map_variables variable_1=\"variable_bob\"/>"
                "</connection>"
            "</model>";

    const std::string expectedError1 = "Connection in model '' does not have a valid variable_2 in a map_variables element.";

    // Parse
    libcellml::Parser p;
    p.parseModel(e);
    EXPECT_EQ(1, p.errorCount());
    EXPECT_EQ(expectedError1, p.getError(0)->getDescription());
}

TEST(Parser, connectionVariable1Missing) {
    const std::string e =
            "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
            "<model xmlns=\"http://www.cellml.org/cellml/2.0#\">"
                "<component name=\"component_bob\">"
                    "<variable name=\"variable_bob\"/>"
                "</component>"
                "<component name=\"component_dave\">"
                    "<variable name=\"variable_dave\"/>"
                "</component>"
                "<connection component_2=\"component_dave\" component_1=\"component_bob\">"
                    "<map_variables variable_2=\"variable_dave\"/>"
                "</connection>"
            "</model>";

    const std::string expectedError1 = "Connection in model '' does not have a valid variable_1 in a map_variables element.";

    // Parse
    libcellml::Parser p;
    p.parseModel(e);
    EXPECT_EQ(1, p.errorCount());
    EXPECT_EQ(expectedError1, p.getError(0)->getDescription());
}

TEST(Parser, connectionErrorNoMapVariablesType) {
    const std::string in =
            "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
            "<model xmlns=\"http://www.cellml.org/cellml/2.0#\">"
                "<component name=\"component1\">"
                    "<variable name=\"variable1\"/>"
                "</component>"
                "<component name=\"component2\">"
                    "<variable name=\"variable2\"/>"
                "</component>"
                "<connection component_1=\"component1\"  component_2=\"component2\">"
                    "<map_variabels variable_1=\"variable1\" variable_2=\"variable2\"/>"
                "</connection>"
            "</model>";

    const std::string expectedError1 = "Connection in model '' has an invalid child element 'map_variabels'.";
    const std::string expectedError2 = "Connection in model '' does not have a map_variables element.";

    libcellml::Parser p;
    p.parseModel(in);
    EXPECT_EQ(2, p.errorCount());
    EXPECT_EQ(expectedError1, p.getError(0)->getDescription());
    EXPECT_EQ(expectedError2, p.getError(1)->getDescription());
}

TEST(Parser, invalidImportsAndGetError) {
    const std::string input =
            "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
            "<model xmlns=\"http://www.cellml.org/cellml/2.0#\">"
                "<import xlink:href=\"some-other-model.xml\" xmlns:xlink=\"http://www.w3.org/1999/xlink\" sauce=\"hollandaise\">"
                    "<units units_ref=\"a_units_in_that_model\" name=\"units_in_this_model\"/>"
                    "<component component_ref=\"a_component_in_that_model\" name=\"component_in_this_model\"/>"
                    "<invalid_nonsense/>"
                    "<units units_ruff=\"dog\" name=\"fido\"/>"
                    "<component component_meow=\"cat\" name=\"frank\"/>"
                "</import>"
            "</model>";

    const std::string expectError1 = "Import from 'some-other-model.xml' has an invalid attribute 'sauce'.";
    const std::string expectError2 = "Import from 'some-other-model.xml' has an invalid child element 'invalid_nonsense'.";
    const std::string expectError3 = "Import of units 'fido' from 'some-other-model.xml' has an invalid attribute 'units_ruff'.";
    const std::string expectError4 = "Import of component 'frank' from 'some-other-model.xml' has an invalid attribute 'component_meow'.";

    const std::string output =
            "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
            "<model xmlns=\"http://www.cellml.org/cellml/2.0#\">"
                "<import xlink:href=\"some-other-model.xml\" xmlns:xlink=\"http://www.w3.org/1999/xlink\">"
                    "<component component_ref=\"a_component_in_that_model\" name=\"component_in_this_model\"/>"
                "</import>"
                "<import xlink:href=\"some-other-model.xml\" xmlns:xlink=\"http://www.w3.org/1999/xlink\">"
                    "<units units_ref=\"a_units_in_that_model\" name=\"units_in_this_model\"/>"
                "</import>"
            "</model>";

    libcellml::Parser p;
    libcellml::ModelPtr m = p.parseModel(input);
    EXPECT_EQ(4, p.errorCount());
    EXPECT_EQ(expectError1, p.getError(0)->getDescription());
    EXPECT_EQ(expectError2, p.getError(1)->getDescription());
    EXPECT_EQ(expectError3, p.getError(2)->getDescription());
    EXPECT_EQ(expectError4, p.getError(3)->getDescription());

    libcellml::Printer printer;
    const std::string a = printer.printModel(m);
    EXPECT_EQ(output, a);

    libcellml::ImportSourcePtr import = m->getUnits("units_in_this_model")->getImportSource();
    // Get import from error and check.
    EXPECT_EQ(import, p.getError(0)->getSourceImport());
    // Get const import from error and check.
    const libcellml::ErrorPtr err = static_cast<const libcellml::Parser>(p).getError(0);
    libcellml::Error *rawErr = err.get();
    const libcellml::ImportSourcePtr importFromError = static_cast<const libcellml::Error*>(rawErr)->getSourceImport();
    EXPECT_EQ(import, importFromError);
}

TEST(Parser, invalidModelWithAllKindsOfErrors) {

    // Check for all kinds of errors.
    std::vector<bool> foundKind(9, false);

    // Trigger CellML entity errors
    const std::string input =
            "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
            "<model xmlns=\"http://www.cellml.org/cellml/2.0#\" name=\"starwars\" episode=\"four\">"
                "<import princess=\"leia\"/>"
                "<units jedi=\"luke\"/>"
                "<component ship=\"falcon\">"
                    "<variable pilot=\"han\"/>"
                "</component>"
                "<connection wookie=\"chewie\"/>"
                "<encapsulation yoda=\"green\"/>"
            "</model>";

    std::vector<std::string> expectedErrors = {
        "Model 'starwars' has an invalid attribute 'episode'.",
        "Import from '' has an invalid attribute 'princess'.",
        "Units '' has an invalid attribute 'jedi'.",
        "Component '' has an invalid attribute 'ship'.",
        "Variable '' has an invalid attribute 'pilot'.",
        "Connection in model 'starwars' has an invalid connection attribute 'wookie'.",
        "Connection in model 'starwars' does not have a valid component_1 in a connection element.",
        "Connection in model 'starwars' does not have a valid component_2 in a connection element.",
        "Connection in model 'starwars' must contain one or more 'map_variables' elements.",
        "Encapsulation in model 'starwars' has an invalid attribute 'yoda'.",
        "Encapsulation in model 'starwars' does not contain any child elements."
    };

    // Parse and check for CellML errors.
    libcellml::Parser parser;
    parser.parseModel(input);
    EXPECT_EQ(expectedErrors.size(), parser.errorCount());
    for (size_t i = 0; i < parser.errorCount(); ++i) {
        EXPECT_EQ(expectedErrors.at(i), parser.getError(i)->getDescription());
        switch (parser.getError(i)->getKind()) {
            case (libcellml::Error::Kind::COMPONENT): {
                foundKind.at(0) = true;
                break;
            }
            case (libcellml::Error::Kind::CONNECTION): {
                foundKind.at(1) = true;
                break;
            }
            case (libcellml::Error::Kind::ENCAPSULATION): {
                foundKind.at(2) = true;
                break;
            }
            case (libcellml::Error::Kind::IMPORT): {
                foundKind.at(3) = true;
                break;
            }
            case (libcellml::Error::Kind::MODEL): {
                foundKind.at(4) = true;
                break;
            }
            case (libcellml::Error::Kind::UNITS): {
                foundKind.at(5) = true;
                break;
            }
            case (libcellml::Error::Kind::VARIABLE): {
                foundKind.at(6) = true;
                break;
            }
            default:{
            }
        }
    }

    // Trigger undefined error
    libcellml::Parser parser2;
    // Add an undefined error
    libcellml::ErrorPtr undefinedError = std::make_shared<libcellml::Error>();
    parser2.addError(undefinedError);
    EXPECT_EQ(1, parser2.errorCount());
    if (parser2.getError(0)->isKind(libcellml::Error::Kind::UNDEFINED)) {
        foundKind.at(7) = true;
    }

    // Trigger an XML error
    const std::string input3 = "jarjarbinks";
    std::vector<std::string> expectedErrors3 = {
        "Start tag expected, '<' not found.",
        "Could not get a valid XML root node from the provided input."
    };
    libcellml::Parser parser3;
    parser3.parseModel(input3);
    EXPECT_EQ(expectedErrors3.size(), parser3.errorCount());
    for (size_t i = 0; i < parser3.errorCount(); ++i) {
        EXPECT_EQ(expectedErrors3.at(i), parser3.getError(i)->getDescription());
        if (parser3.getError(i)->isKind(libcellml::Error::Kind::XML)) {
            foundKind.at(8) = true;
        }
    }

    // Check that we've found all the possible error types
    bool foundAllKinds = false;
    if (std::all_of(foundKind.begin(), foundKind.end(), [](bool i) {return i;})) {
        foundAllKinds = true;
    }
    EXPECT_TRUE(foundAllKinds);
}

TEST(Parser, invalidModelWithTextInAllElements) {
    const std::string input =
            "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
            "<model xmlns=\"http://www.cellml.org/cellml/2.0#\" name=\"starwars\">\n"
                "episode7\n"
                "<import xlink:href=\"sith.xml\" xmlns:xlink=\"http://www.w3.org/1999/xlink\">kylo</import>\n"
                "<units name=\"robot\">"
                    "bb-8"
                    "<unit units=\"ball\">rolls</unit>"
                "</units>\n"
                "<component name=\"ship\">falcon\n"
                    "    <variable name=\"jedi\">rey</variable>\n"
                "</component>\n"
                "<connection>"
                    "finn"
                    "<map_variables>"
                        "trooper"
                    "</map_variables>"
                "</connection>\n"
                "<encapsulation>"
                    "awakens"
                    "<component_ref component=\"ship\">"
                        "force"
                    "</component_ref>"
                "</encapsulation>\n"
            "</model>";

    std::vector<std::string> expectedErrors = {
        "Model 'starwars' has an invalid non-whitespace child text element '\nepisode7\n'.",
        "Import from 'sith.xml' has an invalid non-whitespace child text element 'kylo'.",
        "Units 'robot' has an invalid non-whitespace child text element 'bb-8'.",
        "Unit referencing 'ball' in units 'robot' has an invalid non-whitespace child text element 'rolls'.",
        "Component 'ship' has an invalid non-whitespace child text element 'falcon\n    '.",
        "Variable 'jedi' has an invalid non-whitespace child text element 'rey'.",
        "Connection in model 'starwars' does not have a valid component_1 in a connection element.",
        "Connection in model 'starwars' does not have a valid component_2 in a connection element.",
        "Connection in model 'starwars' has an invalid non-whitespace child text element 'finn'.",
        "Connection in model 'starwars' has an invalid non-whitespace child text element 'trooper'.",
        "Connection in model 'starwars' does not have a valid variable_1 in a map_variables element.",
        "Connection in model 'starwars' does not have a valid variable_2 in a map_variables element.",
        "Connection in model 'starwars' specifies '' as variable_1 but the corresponding component_1 is invalid.",
        "Connection in model 'starwars' specifies '' as variable_2 but the corresponding component_2 is invalid.",
        "Encapsulation in model 'starwars' has an invalid non-whitespace child text element 'awakens'.",
        "Encapsulation in model 'starwars' specifies an invalid parent component_ref that also does not have any children.",
        "Encapsulation in model 'starwars' has an invalid non-whitespace child text element 'force'."
    };

    // Parse and check for CellML errors.
    libcellml::Parser parser;
    parser.parseModel(input);
    EXPECT_EQ(expectedErrors.size(), parser.errorCount());
    for (size_t i = 0; i < parser.errorCount(); ++i) {
        EXPECT_EQ(expectedErrors.at(i), parser.getError(i)->getDescription());
    }
}

TEST(Parser, parseIds) {
    const std::string in =
            "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
            "<model xmlns=\"http://www.cellml.org/cellml/2.0#\" id=\"mid\">"
                "<import xlink:href=\"some-other-model.xml\" xmlns:xlink=\"http://www.w3.org/1999/xlink\" id=\"i1id\">"
                    "<component component_ref=\"a_component_in_that_model\" name=\"component1\" id=\"c1id\"/>"
                "</import>"
                "<import xlink:href=\"some-other-model.xml\" xmlns:xlink=\"http://www.w3.org/1999/xlink\" id=\"i2id\">"
                    "<units units_ref=\"a_units_in_that_model\" name=\"units1\" id=\"u1id\"/>"
                "</import>"
                "<units name=\"units2\" id=\"u2id\"/>"
                "<units name=\"units3\" id=\"u3id\"/>"
                "<component name=\"component2\" id=\"c2id\">"
                    "<variable name=\"variable1\" id=\"vid\"/>"
                "</component>"
            "</model>";

    libcellml::Parser p;
    libcellml::ModelPtr model = p.parseModel(in);

    EXPECT_EQ(0, p.errorCount());
    EXPECT_EQ("mid", model->getId());
    EXPECT_EQ("c1id", model->getComponent("component1")->getId());
    EXPECT_EQ("i1id", model->getComponent("component1")->getImportSource()->getId());
    EXPECT_EQ("u1id", model->getUnits("units1")->getId());
    EXPECT_EQ("i2id", model->getUnits("units1")->getImportSource()->getId());
    EXPECT_EQ("u2id", model->getUnits("units2")->getId());
    EXPECT_EQ("c2id", model->getComponent("component2")->getId());
    EXPECT_EQ("u3id", model->getUnits("units3")->getId());
    EXPECT_EQ("vid", model->getComponent("component2")->getVariable("variable1")->getId());
}

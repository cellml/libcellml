/*
Copyright 2015 University of Auckland

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
#include <vector>

TEST(Parser, invalidXMLElements) {
    std::string input =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<fellowship>"
            "<Dwarf bearded>Gimli</ShortGuy>"
            "<Hobbit>Frodo</EvenShorterGuy>"
            "<Wizard>Gandalf</SomeGuyWithAStaff>"
            "<Elf>"
        "</fellows>";

    std::string expectError1 = "Specification mandate value for attribute bearded.";
    std::string expectError2 = "Opening and ending tag mismatch: Dwarf line 2 and ShortGuy.";
    std::string expectError3 = "Opening and ending tag mismatch: Hobbit line 2 and EvenShorterGuy.";
    std::string expectError4 = "Opening and ending tag mismatch: Wizard line 2 and SomeGuyWithAStaff.";
    std::string expectError5 = "Opening and ending tag mismatch: Elf line 2 and fellows.";
    std::string expectError6 = "Premature end of data in tag fellowship line 2.";

    libcellml::Parser p(libcellml::Format::XML);
    EXPECT_THROW(p.parseModel(input), std::invalid_argument);
    EXPECT_EQ(6, p.errorCount());
    EXPECT_EQ(expectError1, p.getError(0)->getDescription());
    EXPECT_EQ(expectError2, p.getError(1)->getDescription());
    EXPECT_EQ(expectError3, p.getError(2)->getDescription());
    EXPECT_EQ(expectError4, p.getError(3)->getDescription());
    EXPECT_EQ(expectError5, p.getError(4)->getDescription());
    EXPECT_EQ(expectError6, p.getError(5)->getDescription());
}

TEST(Parser, parse) {
    const std::string e = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n<model xmlns=\"http://www.cellml.org/cellml/1.2#\"/>";
    libcellml::Parser parser(libcellml::Format::XML);
    libcellml::ModelPtr model = parser.parseModel(e);
    std::string a = model->serialise(libcellml::Format::XML);
    EXPECT_EQ(e, a);
}

TEST(Parser, parseNamedModel) {
    std::string n = "name";
    const std::string e = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n<model xmlns=\"http://www.cellml.org/cellml/1.2#\" name=\"" + n + "\"/>";
    libcellml::Parser parser(libcellml::Format::XML);
    libcellml::ModelPtr model = parser.parseModel(e);
    EXPECT_EQ(n, model->getName());
    std::string a = model->serialise(libcellml::Format::XML);
    EXPECT_EQ(e, a);
}

TEST(Parser, moveParser) {
    libcellml::Parser p(libcellml::Format::XML), pm(libcellml::Format::XML), pa(libcellml::Format::XML);
    pa = p;
    pm = std::move(p);

    libcellml::Parser pc(pm);
}

TEST(Parser, makeError) {
    std::string ex = "";

    libcellml::ErrorPtr e = std::make_shared<libcellml::Error>();

    EXPECT_EQ(ex, e->getDescription());
}

TEST(Parser, emptyModelString) {
    std::string ex = "";

    libcellml::Parser p(libcellml::Format::XML);
    EXPECT_THROW(p.parseModel(ex), std::invalid_argument);
}

TEST(Parser, nonXmlString) {
    std::string ex = "Not an xml string.";

    libcellml::Parser p(libcellml::Format::XML);
    EXPECT_THROW(p.parseModel(ex), std::invalid_argument);
}

TEST(Parser, invalidRootNode) {
    std::string ex =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<yodel xmlns=\"http://www.cellml.org/cellml/1.2#\" name=\"model_name\">"
        "</yodel>";
    std::string expectedError1 = "Model root node is of invalid type 'yodel'. A valid CellML root node should be of type 'model'.";

    libcellml::Parser p(libcellml::Format::XML);
    p.parseModel(ex);
    EXPECT_EQ(1, p.errorCount());
    EXPECT_EQ(expectedError1, p.getError(0)->getDescription());
}

TEST(Parser, invalidModelAttribute) {
    std::string ex =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/1.2#\" game=\"model_name\"/>";
    std::string expectedError1 = "Model '' has an invalid attribute 'game'.";

    libcellml::Parser p(libcellml::Format::XML);
    p.parseModel(ex);
    EXPECT_EQ(1, p.errorCount());
    EXPECT_EQ(expectedError1, p.getError(0)->getDescription());
}

TEST(Parser, invalidModelElement) {
    std::string ex =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/1.2#\" name=\"model_name\">"
            "<uknits/>"
        "</model>";
    std::string expectedError1 = "Model 'model_name' has an invalid child element 'uknits'.";

    libcellml::Parser p(libcellml::Format::XML);
    p.parseModel(ex);
    EXPECT_EQ(1, p.errorCount());
    EXPECT_EQ(expectedError1, p.getError(0)->getDescription());
}

TEST(Parser, modelWithInvalidElement) {
    std::string input1 =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/1.2#\" name=\"bilbo\">"
            "<hobbit/>"
        "</model>";
    std::string expectError1 = "Model 'bilbo' has an invalid child element 'hobbit'.";

    std::string input2 =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/1.2#\">"
            "<hobbit/>"
        "</model>";
    std::string expectError2 = "Model '' has an invalid child element 'hobbit'.";

    libcellml::Parser p(libcellml::Format::XML);
    p.parseModel(input1);
    EXPECT_EQ(1, p.errorCount());
    EXPECT_EQ(expectError1, p.getError(0)->getDescription());

    p.clearErrors();
    p.parseModel(input2);
    EXPECT_EQ(1, p.errorCount());
    EXPECT_EQ(expectError2, p.getError(0)->getDescription());
}

TEST(Parser, parseModelWithInvalidAttributeAndGetError) {
    const std::string mName = "modelName";
    const std::string input =
            "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
            "<model xmlns=\"http://www.cellml.org/cellml/1.2#\" name=\"" + mName + "\" nonsense=\"oops\"/>";
    const std::string expectedError = "Model 'modelName' has an invalid attribute 'nonsense'.";

    libcellml::Parser parser(libcellml::Format::XML);
    libcellml::ModelPtr model = parser.parseModel(input);

    EXPECT_EQ(1, parser.errorCount());
    EXPECT_EQ(expectedError, parser.getError(0)->getDescription());

    // Get ModelError and check.
    EXPECT_EQ(model, parser.getError(0)->getModel());
    // Get const modelError and check.
    const libcellml::ErrorPtr err = static_cast<const libcellml::Parser>(parser).getError(0);
    const libcellml::ModelPtr modelFromError = err->getModel();
    EXPECT_EQ(model, modelFromError);
}

TEST(Parser, parseNamedModelWithNamedComponent) {
    std::string mName = "modelName";
    std::string cName = "componentName";
    const std::string e =
            "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
            "<model xmlns=\"http://www.cellml.org/cellml/1.2#\" name=\"" + mName + "\">"
              "<component name=\"" + cName + "\"/>"
            "</model>";
    libcellml::Parser parser(libcellml::Format::XML);
    libcellml::ModelPtr model = parser.parseModel(e);
    EXPECT_EQ(mName, model->getName());
    libcellml::ComponentPtr c = model->getComponent(cName);
    EXPECT_EQ(cName, c->getName());
    std::string a = model->serialise(libcellml::Format::XML);
    EXPECT_EQ(e, a);
}

TEST(Parser, parseModelWithNamedComponentWithUnits) {
    const std::string e =
            "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
            "<model xmlns=\"http://www.cellml.org/cellml/1.2#\" name=\"model_name\">"
              "<component name=\"component_name\">"
                "<units name=\"fahrenheit\">"
                  "<unit multiplier=\"1.8\" offset=\"32\" units=\"celsius\"/>"
                "</units>"
                "<units name=\"dimensionless\" base_unit=\"yes\"/>"
              "</component>"
            "</model>";
    libcellml::Parser parser(libcellml::Format::XML);
    libcellml::ModelPtr model = parser.parseModel(e);
    std::string a = model->serialise(libcellml::Format::XML);
    EXPECT_EQ(e, a);
}

TEST(Parser, parseModelWithNamedComponentWithInvalidBaseUnitsAndGetError) {
    const std::string in =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/1.2#\" name=\"model_name\">"
          "<component name=\"component_name\">"
            "<units name=\"fahrenheit\">"
              "<unit multiplier=\"1.8\" offset=\"32\" units=\"celsius\"/>"
            "</units>"
            "<units name=\"dimensionless\" base_unit=\"joe\"/>"
          "</component>"
        "</model>";
    const std::string e =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/1.2#\" name=\"model_name\">"
          "<component name=\"component_name\">"
            "<units name=\"fahrenheit\">"
              "<unit multiplier=\"1.8\" offset=\"32\" units=\"celsius\"/>"
            "</units>"
            "<units name=\"dimensionless\"/>"
          "</component>"
        "</model>";
    std::string expectedError1 = "Units 'dimensionless' has an invalid base_unit attribute value 'joe'. Valid options are 'yes' or 'no'.";

    libcellml::Parser parser(libcellml::Format::XML);
    libcellml::ModelPtr model = parser.parseModel(in);
    std::string a = model->serialise(libcellml::Format::XML);
    EXPECT_EQ(e, a);
    EXPECT_EQ(1, parser.errorCount());
    EXPECT_EQ(expectedError1, parser.getError(0)->getDescription());

    libcellml::UnitsPtr unitsExpected = model->getComponent("component_name")->getUnits("dimensionless");
    // Get units from error and check.
    EXPECT_EQ(unitsExpected, parser.getError(0)->getUnits());
    // Get const units from error and check.
    const libcellml::ErrorPtr err = static_cast<const libcellml::Parser>(parser).getError(0);
    const libcellml::UnitsPtr unitsFromError = err->getUnits();
    EXPECT_EQ(unitsExpected, unitsFromError);
}

TEST(Parser, unitsAttributeError) {
    std::string ex =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/1.2#\" name=\"model_name\">"
            "<units name=\"pH\" base_unit=\"yes\" invalid_attribute=\"yes\"/>"
        "</model>";
    std::string expectedError1 = "Units 'pH' has an invalid attribute 'invalid_attribute'.";

    libcellml::Parser p(libcellml::Format::XML);
    p.parseModel(ex);
    EXPECT_EQ(1, p.errorCount());
    EXPECT_EQ(expectedError1, p.getError(0)->getDescription());
}

TEST(Parser, unitsElementErrors) {
    std::string input1 =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/1.2#\" name=\"model_name\">"
          "<units>"
            "<son name=\"stan\"/>"
          "</units>"
        "</model>";
    std::string expectError1 = "Units '' has an invalid child element 'son'.";

    std::string input2 =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/1.2#\" name=\"model_name\">"
          "<units name=\"randy\">"
            "<son name=\"stan\"/>"
          "</units>"
        "</model>";
    std::string expectError2 = "Units 'randy' has an invalid child element 'son'.";

    libcellml::Parser p(libcellml::Format::XML);
    p.parseModel(input1);
    EXPECT_EQ(1, p.errorCount());
    EXPECT_EQ(expectError1, p.getError(0)->getDescription());

    p.clearErrors();
    p.parseModel(input2);
    EXPECT_EQ(1, p.errorCount());
    EXPECT_EQ(expectError2, p.getError(0)->getDescription());
}

TEST(Parser, parseModelWithInvalidComponentAttributeAndGetError) {
    const std::string mName = "modelName";
    const std::string cName = "componentName";
    const std::string input =
            "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
            "<model xmlns=\"http://www.cellml.org/cellml/1.2#\" name=\"" + mName + "\">"
              "<component name=\"" + cName + "\" nonsense=\"oops\"/>"
            "</model>";
    const std::string expectedError = "Component 'componentName' has an invalid attribute 'nonsense'.";

    libcellml::Parser parser(libcellml::Format::XML);
    libcellml::ModelPtr model = parser.parseModel(input);
    libcellml::ComponentPtr component = model->getComponent(cName);

    EXPECT_EQ(1, parser.errorCount());
    EXPECT_EQ(expectedError, parser.getError(0)->getDescription());

    // Get component from error and check.
    EXPECT_EQ(component, parser.getError(0)->getComponent());
    // Get const component from error and check.
    const libcellml::ErrorPtr err = static_cast<const libcellml::Parser>(parser).getError(0);
    const libcellml::ComponentPtr componentFromError = err->getComponent();
    EXPECT_EQ(component, componentFromError);
}

TEST(Parser, componentAttributeErrors) {
    std::string input1 =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/1.2#\" name=\"model_name\">"
          "<component lame=\"randy\"/>"
        "</model>";
    std::string expectError1 = "Component '' has an invalid attribute 'lame'.";

    std::string input2 =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/1.2#\" name=\"model_name\">"
          "<component name=\"randy\" son=\"stan\"/>"
        "</model>";
    std::string expectError2 = "Component 'randy' has an invalid attribute 'son'.";

    std::string input3 =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/1.2#\" name=\"model_name\">"
          "<component son=\"stan\" name=\"randy\"/>"
        "</model>";
    std::string expectError3 = "Component 'randy' has an invalid attribute 'son'.";

    libcellml::Parser p(libcellml::Format::XML);
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
    std::string input1 =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/1.2#\" name=\"model_name\">"
          "<component>"
            "<son name=\"stan\"/>"
          "</component>"
        "</model>";
    std::string expectError1 = "Component '' has an invalid child element 'son'.";

    std::string input2 =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/1.2#\" name=\"model_name\">"
          "<component name=\"randy\">"
            "<son name=\"stan\"/>"
          "</component>"
        "</model>";
    std::string expectError2 = "Component 'randy' has an invalid child element 'son'.";

    libcellml::Parser p(libcellml::Format::XML);
    p.parseModel(input1);
    EXPECT_EQ(1, p.errorCount());
    EXPECT_EQ(expectError1, p.getError(0)->getDescription());

    p.clearErrors();
    p.parseModel(input2);
    EXPECT_EQ(1, p.errorCount());
    EXPECT_EQ(expectError2, p.getError(0)->getDescription());
}

TEST(Parser, parseModelWithTwoComponents) {
    std::string mName = "modelName";
    std::string cName1 = "component1";
    std::string cName2 = "component2";
    const std::string e =
            "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
            "<model xmlns=\"http://www.cellml.org/cellml/1.2#\" name=\"" + mName + "\">"
              "<component name=\"" + cName1 + "\"/>"
              "<component name=\"" + cName2 + "\"/>"
            "</model>";
    libcellml::Parser parser(libcellml::Format::XML);
    libcellml::ModelPtr model = parser.parseModel(e);
    std::string a = model->serialise(libcellml::Format::XML);
    EXPECT_EQ(e, a);
}

TEST(Parser, parseModelWithComponentHierarchyWaterfall) {
    const std::string e =
            "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
            "<model xmlns=\"http://www.cellml.org/cellml/1.2#\">"
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
    libcellml::Parser parser(libcellml::Format::XML);
    libcellml::ModelPtr model = parser.parseModel(e);
    std::string a = model->serialise(libcellml::Format::XML);
    EXPECT_EQ(e, a);
}

TEST(Parser, parseModelWithMultipleComponentHierarchyWaterfalls) {
    const std::string e =
            "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
            "<model xmlns=\"http://www.cellml.org/cellml/1.2#\">"

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
    libcellml::Parser parser(libcellml::Format::XML);
    libcellml::ModelPtr model = parser.parseModel(e);
    std::string a = model->serialise(libcellml::Format::XML);
    EXPECT_EQ(e, a);
}

TEST(Parser, modelWithNamedComponentWithUnits) {
    const std::string in =
            "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
            "<model xmlns=\"http://www.cellml.org/cellml/1.2#\" name=\"model_name\">"
              "<component name=\"component_name\">"
                "<units name=\"fahrenheit\">"
                  "<unit multiplier=\"1.8\" offset=\"32\" units=\"celsius\"/>"
                "</units>"
                "<units name=\"dimensionless\" base_unit=\"no\"/>"
              "</component>"
            "</model>";
    const std::string e =
            "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
            "<model xmlns=\"http://www.cellml.org/cellml/1.2#\" name=\"model_name\">"
              "<component name=\"component_name\">"
                "<units name=\"fahrenheit\">"
                  "<unit multiplier=\"1.8\" offset=\"32\" units=\"celsius\"/>"
                "</units>"
                "<units name=\"dimensionless\"/>"
              "</component>"
            "</model>";
    libcellml::Parser parser(libcellml::Format::XML);
    libcellml::ModelPtr model = parser.parseModel(in);
    std::string a = model->serialise(libcellml::Format::XML);
    EXPECT_EQ(e, a);
}

TEST(Parser, modelWithNamedComponentWithInvalidUnits) {
    const std::string in =
            "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
            "<model xmlns=\"http://www.cellml.org/cellml/1.2#\" name=\"model_name\">"
              "<component name=\"component_name\">"
                "<units name=\"fahrenheit\" temperature=\"451\">"
                  "<unit multiplier=\"Z\" offset=\"MM\" exponent=\"35.0E+310\" units=\"celsius\" bill=\"murray\">"
                    "<degrees/>"
                  "</unit>"
                  "<bobshouse address=\"34 Rich Lane\"/>"
                  "<unit GUnit=\"50c\"/>"
                "</units>"
                "<units name=\"dimensionless\" base_unit=\"no\"/>"
                "<units jerry=\"seinfeld\">"
                  "<unit units=\"friends\" neighbor=\"kramer\"/>"
                  "<unit george=\"friends\"/>"
                "</units>"
              "</component>"
            "</model>";
    const std::string e =
            "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
            "<model xmlns=\"http://www.cellml.org/cellml/1.2#\" name=\"model_name\">"
              "<component name=\"component_name\">"
                "<units name=\"fahrenheit\">"
                  "<unit units=\"celsius\"/>"
                  "<unit units=\"\"/>"
                "</units>"
                "<units name=\"dimensionless\"/>"
              "</component>"
            "</model>";
    std::vector<std::string> expectedErrors = {
        "Units 'fahrenheit' has an invalid attribute 'temperature'.",
        "Unit 'celsius' in units 'fahrenheit' has an invalid child element 'degrees'.",
        "Unit 'celsius' in units 'fahrenheit' has an attribute 'multiplier' with a value 'Z' that cannot be converted to a decimal number.",
        "Unit 'celsius' in units 'fahrenheit' has an attribute 'offset' with a value 'MM' that cannot be converted to a decimal number.",
        "Unit 'celsius' in units 'fahrenheit' has an attribute 'exponent' with a value '35.0E+310' that cannot be converted to a decimal number.",
        "Unit 'celsius' in units 'fahrenheit' has an invalid attribute 'bill'.",
        "Units 'fahrenheit' has an invalid child element 'bobshouse'.",
        "Unit '' in units 'fahrenheit' has an invalid attribute 'GUnit'.",
        "Units '' has an invalid attribute 'jerry'.",
        "Unit 'friends' in units '' has an invalid attribute 'neighbor'.",
        "Unit '' in units '' has an invalid attribute 'george'."
    };

    libcellml::Parser parser(libcellml::Format::XML);
    libcellml::ModelPtr model = parser.parseModel(in);

    EXPECT_EQ(expectedErrors.size(), parser.errorCount());
    for (size_t i = 0; i < parser.errorCount(); ++i) {
        EXPECT_EQ(expectedErrors.at(i), parser.getError(i)->getDescription());
    }

    std::string a = model->serialise(libcellml::Format::XML);
    EXPECT_EQ(e, a);
}

TEST(Parser, emptyEncapsulation) {
    std::string ex =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/1.2#\" name=\"model_name\">"
            "<encapsulation/>"
        "</model>";
    std::string expectedError = "Encapsulation in model 'model_name' does not contain any child elements.";

    libcellml::Parser p(libcellml::Format::XML);
    p.parseModel(ex);
    EXPECT_EQ(1, p.errorCount());
    EXPECT_EQ(expectedError, p.getError(0)->getDescription());
}

TEST(Parser, encapsulationWithNoComponentAttribute) {
    std::string ex =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/1.2#\" name=\"model_name\">"
            "<encapsulation>"
                "<component_ref/>"
            "</encapsulation>"
        "</model>";
    std::string expectedError1 = "Encapsulation in model 'model_name' does not have a valid component attribute in a component_ref element.";
    std::string expectedError2 = "Encapsulation in model 'model_name' specifies an invalid parent component_ref that also does not have any children.";

    libcellml::Parser p(libcellml::Format::XML);
    p.parseModel(ex);
    EXPECT_EQ(2, p.errorCount());
    EXPECT_EQ(expectedError1, p.getError(0)->getDescription());
    EXPECT_EQ(expectedError2, p.getError(1)->getDescription());
}

TEST(Parser, encapsulationWithNoComponentRef) {
    std::string ex =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/1.2#\" name=\"model_name\">"
            "<encapsulation>"
                "<component_free/>"
            "</encapsulation>"
        "</model>";
    std::string expectedError1 = "Encapsulation in model 'model_name' has an invalid child element 'component_free'.";
    std::string expectedError2 = "Encapsulation in model 'model_name' specifies an invalid parent component_ref that also does not have any children.";

    libcellml::Parser p(libcellml::Format::XML);
    p.parseModel(ex);
    EXPECT_EQ(2, p.errorCount());
    EXPECT_EQ(expectedError1, p.getError(0)->getDescription());
    EXPECT_EQ(expectedError2, p.getError(1)->getDescription());
}

TEST(Parser, encapsulationWithNoComponent) {
    std::string ex =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/1.2#\" name=\"model_name\">"
            "<encapsulation>"
                "<component_ref component=\"bob\">"
                    "<component_ref/>"
                "</component_ref>"
            "</encapsulation>"
        "</model>";
    std::string expectedError1 = "Encapsulation in model 'model_name' specifies 'bob' as a component in a component_ref but it does not exist in the model.";
    std::string expectedError2 = "Encapsulation in model 'model_name' does not have a valid component attribute in a component_ref that is a child of invalid parent component 'bob'.";



    libcellml::Parser p(libcellml::Format::XML);
    p.parseModel(ex);
    EXPECT_EQ(2, p.errorCount());
    EXPECT_EQ(expectedError1, p.getError(0)->getDescription());
    EXPECT_EQ(expectedError2, p.getError(1)->getDescription());
}

TEST(Parser, encapsulationWithMissingComponent) {
    std::string ex =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/1.2#\" name=\"model_name\">"
            "<component name=\"bob\"/>"
            "<encapsulation>"
            "<component_ref component=\"bob\">"
                "<component_ref component=\"dave\"/>"
            "</component_ref>"
            "</encapsulation>"
        "</model>";
    std::string expectedError1 = "Encapsulation in model 'model_name' specifies 'dave' as a component in a component_ref but it does not exist in the model.";

    libcellml::Parser p(libcellml::Format::XML);
    p.parseModel(ex);
    EXPECT_EQ(1, p.errorCount());
    EXPECT_EQ(expectedError1, p.getError(0)->getDescription());
}

TEST(Parser, encapsulationWithNoComponentChild) {
    std::string ex =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/1.2#\" name=\"model_name\">"
            "<component name=\"bob\"/>"
            "<encapsulation>"
              "<component_ref component=\"bob\"/>"
            "</encapsulation>"
        "</model>";
    std::string expectedError = "Encapsulation in model 'model_name' specifies 'bob' as a parent component_ref but it does not have any children.";

    libcellml::Parser p(libcellml::Format::XML);
    p.parseModel(ex);
    EXPECT_EQ(1, p.errorCount());
    EXPECT_EQ(expectedError, p.getError(0)->getDescription());
}

TEST(Parser, encapsulationNoChildComponentRef) {
    std::string ex =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/1.2#\" name=\"model_name\">"
            "<component name=\"bob\"/>"
            "<encapsulation>"
              "<component_ref component=\"bob\">"
                "<component_free/>"
              "</component_ref>"
            "</encapsulation>"
        "</model>";
    std::string expectedError = "Encapsulation in model 'model_name' has an invalid child element 'component_free'.";

    libcellml::Parser p(libcellml::Format::XML);
    p.parseModel(ex);
    EXPECT_EQ(1, p.errorCount());
    EXPECT_EQ(expectedError, p.getError(0)->getDescription());
}

TEST(Parser, encapsulationWithNoGrandchildComponentRef) {
    std::string ex =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/1.2#\" name=\"model_name\">"
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
    std::string expectedError = "Encapsulation in model 'model_name' has an invalid child element 'component_free'.";

    libcellml::Parser p(libcellml::Format::XML);
    p.parseModel(ex);
    EXPECT_EQ(1, p.errorCount());
    EXPECT_EQ(expectedError, p.getError(0)->getDescription());
}

TEST(Parser, invalidEncapsulations) {
    const std::string e =
            "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
            "<model xmlns=\"http://www.cellml.org/cellml/1.2#\" name=\"ringo\">"
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

    libcellml::Parser parser(libcellml::Format::XML);
    parser.parseModel(e);

    EXPECT_EQ(expectedErrors.size(), parser.errorCount());
    for (size_t i = 0; i < parser.errorCount(); ++i) {
        EXPECT_EQ(expectedErrors.at(i), parser.getError(i)->getDescription());
    }
}

TEST(Parser, invalidVariableAttributesAndGetVariableError) {
    const std::string in =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/1.2#\">"
            "<component name=\"componentA\">"
                "<variable name=\"quixote\" don=\"true\"/>"
                "<variable windmill=\"tilted\"/>"
            "</component>"
        "</model>";
    std::string expectError1 = "Variable 'quixote' has an invalid attribute 'don'.";
    std::string expectError2 = "Variable '' has an invalid attribute 'windmill'.";

    libcellml::Parser p(libcellml::Format::XML);
    libcellml::ModelPtr model = p.parseModel(in);
    EXPECT_EQ(2, p.errorCount());
    EXPECT_EQ(expectError1, p.getError(0)->getDescription());
    EXPECT_EQ(expectError2, p.getError(1)->getDescription());

    libcellml::VariablePtr variableExpected = model->getComponent("componentA")->getVariable("quixote");
    // Get variable from error and check.
    EXPECT_EQ(variableExpected, p.getError(0)->getVariable());
    // Get const variable from error and check.
    const libcellml::ErrorPtr err = static_cast<const libcellml::Parser>(p).getError(0);
    const libcellml::VariablePtr variableFromError = err->getVariable();
    EXPECT_EQ(variableExpected, variableFromError);
}

TEST(Parser, variableAttributeAndChildErrors) {
    std::string input1 =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/1.2#\" name=\"model_name\">"
            "<component name=\"randy\">"
                "<variable lame=\"randy\"/>"
            "</component>"
        "</model>";
    std::string expectError1 = "Variable '' has an invalid attribute 'lame'.";

    std::string input2 =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/1.2#\" name=\"model_name\">"
            "<component name=\"randy\">"
                "<variable name=\"randy\" son=\"stan\">"
                    "<daughter name=\"shelly\"/>"
                "</variable>"
            "</component>"
        "</model>";
    std::string expectError2 = "Variable 'randy' has an invalid child element 'daughter'.";
    std::string expectError3 = "Variable 'randy' has an invalid attribute 'son'.";


    libcellml::Parser p(libcellml::Format::XML);
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
    std::string ex =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/1.2#\" name=\"model_name\">"
            "<connection>"
            "</connection>"
            "<connection/>"
        "</model>";
    std::string expectedError = "Connection in model 'model_name' does not contain any child elements.";

    libcellml::Parser p(libcellml::Format::XML);
    p.parseModel(ex);
    EXPECT_EQ(2, p.errorCount());
    EXPECT_EQ(expectedError, p.getError(0)->getDescription());
    EXPECT_EQ(expectedError, p.getError(1)->getDescription());
}

TEST(Parser, connectionErrorNoComponent2) {
    const std::string in =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/1.2#\" name=\"modelA\">"
            "<component name=\"componentA\">"
                "<variable name=\"variable1\"/>"
            "</component>"
            "<connection>"
                "<map_components component_1=\"component1\"/>"
                "<map_variables variable_1=\"variable1\" variable_2=\"variable2\"/>"
            "</connection>"
        "</model>";
    std::string expectedError1 = "Connection in model 'modelA' does not have a valid component_2 in a map_components element.";
    std::string expectedError2 = "Connection in model 'modelA' specifies 'component1' as component_1 but it does not exist in the model.";
    std::string expectedError3 = "Connection in model 'modelA' specifies 'variable1' as variable_1 but the corresponding component_1 is invalid.";
    std::string expectedError4 = "Connection in model 'modelA' specifies 'variable2' as variable_2 but the corresponding component_2 is invalid.";

    libcellml::Parser p(libcellml::Format::XML);
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
        "<model xmlns=\"http://www.cellml.org/cellml/1.2#\" name=\"modelName\">"
            "<component name=\"component1\">"
                "<variable name=\"variable1\"/>"
            "</component>"
            "<connection>"
                "<map_components component_1=\"component1\"  component_2=\"component2\"/>"
                "<map_variables variable_1=\"variable1\" variable_2=\"variable2\"/>"
            "</connection>"
        "</model>";
    std::string expectedError1 = "Connection in model 'modelName' specifies 'component2' as component_2 but it does not exist in the model.";
    std::string expectedError2 = "Connection in model 'modelName' specifies 'variable2' as variable_2 but the corresponding component_2 is invalid.";

    libcellml::Parser p(libcellml::Format::XML);
    p.parseModel(in);
    EXPECT_EQ(2, p.errorCount());
    EXPECT_EQ(expectedError1, p.getError(0)->getDescription());
    EXPECT_EQ(expectedError2, p.getError(1)->getDescription());
}

TEST(Parser, connectionErrorNoComponent1) {
    const std::string in =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/1.2#\" name=\"modelName\">"
            "<component name=\"componentA\">"
                "<variable name=\"variable1\"/>"
            "</component>"
            "<connection>"
                "<map_components component_2=\"componentA\"/>"
                "<map_variables variable_1=\"variable1\" variable_2=\"variable2\"/>"
            "</connection>"
        "</model>";
    std::string expectedError1 = "Connection in model 'modelName' does not have a valid component_1 in a map_components element.";
    std::string expectedError2 = "Connection in model 'modelName' specifies 'variable1' as variable_1 but the corresponding component_1 is invalid.";
    std::string expectedError3 = "Variable 'variable2' is specified as variable_2 in a connection but it does not exist in component_2 component 'componentA' of model 'modelName'.";

    libcellml::Parser p(libcellml::Format::XML);
    p.parseModel(in);
    EXPECT_EQ(3, p.errorCount());
    EXPECT_EQ(expectedError1, p.getError(0)->getDescription());
    EXPECT_EQ(expectedError2, p.getError(1)->getDescription());
    EXPECT_EQ(expectedError3, p.getError(2)->getDescription());
}

TEST(Parser, connectionErrorNoMapComponents) {
    const std::string in =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/1.2#\" name=\"modelName\">"
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
        "Connection in model 'modelName' has an invalid attribute 'name'.",
        "Connection in model 'modelName' has an invalid child element 'map_units' of element 'map_variables'.",
        "Connection in model 'modelName' has an invalid map_variables attribute 'variable_3'.",
        "Connection in model 'modelName' does not have a map_components element.",
        "Connection in model 'modelName' specifies 'variable1' as variable_1 but the corresponding component_1 is invalid.",
        "Connection in model 'modelName' specifies 'variable2' as variable_2 but the corresponding component_2 is invalid."
    };

    libcellml::Parser parser(libcellml::Format::XML);
    parser.parseModel(in);

    EXPECT_EQ(expectedErrors.size(), parser.errorCount());
    for (size_t i = 0; i < parser.errorCount(); ++i) {
        EXPECT_EQ(expectedErrors.at(i), parser.getError(i)->getDescription());
    }
}

TEST(Parser, connectionErrorNoMapVariables) {
    const std::string in =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/1.2#\">"
            "<component name=\"componentA\">"
                "<variable name=\"variable1\"/>"
            "</component>"
            "<connection>"
                "<map_components component_2=\"componentA\" component_1=\"componentA\" component_3=\"componentA\"/>"
                "<map_components component_2=\"componentA\" component_1=\"componentA\"/>"
            "</connection>"
        "</model>";
    std::string expectedError1 = "Connection in model '' has an invalid map_components attribute 'component_3'.";
    std::string expectedError2 = "Connection in model '' has more than one map_components element.";
    std::string expectedError3 = "Connection in model '' does not have a map_variables element.";

    libcellml::Parser p(libcellml::Format::XML);
    p.parseModel(in);
    EXPECT_EQ(3, p.errorCount());
    EXPECT_EQ(expectedError1, p.getError(0)->getDescription());
    EXPECT_EQ(expectedError2, p.getError(1)->getDescription());
    EXPECT_EQ(expectedError3, p.getError(2)->getDescription());
}

TEST(Parser, importedComponent2Connection) {
    const std::string e =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/1.2#\">"
          "<import xlink:href=\"some-other-model.xml\" "
              "xmlns:xlink=\"http://www.w3.org/1999/xlink\">"
              "<component component_ref=\"component_in_that_model\" name=\"component_in_this_model\"/>"
          "</import>"
          "<component name=\"component_bob\">"
            "<variable name=\"variable_bob\"/>"
          "</component>"
          "<connection>"
            "<map_components component_2=\"component_in_this_model\" component_1=\"component_bob\"/>"
            "<map_variables variable_2=\"variable_import\" variable_1=\"variable_bob\"/>"
          "</connection>"
        "</model>";

    // Parse
    libcellml::Parser parser(libcellml::Format::XML);
    parser.parseModel(e);
    EXPECT_EQ(0, parser.errorCount());
}

TEST(Parser, validConnectionMapVariablesFirst) {
    const std::string e =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/1.2#\">"
          "<component name=\"robert\">"
            "<variable name=\"bob\"/>"
          "</component>"
          "<component name=\"james\">"
            "<variable name=\"jimbo\"/>"
          "</component>"
          "<connection>"
            "<map_variables variable_2=\"jimbo\" variable_1=\"bob\"/>"
            "<map_components component_1=\"robert\" component_2=\"james\"/>"
          "</connection>"
        "</model>";

    libcellml::Parser parser(libcellml::Format::XML);
    parser.parseModel(e);
    EXPECT_EQ(0, parser.errorCount());
}

TEST(Parser, component2ConnectionVariableMissing) {
    const std::string e =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/1.2#\">"
            "<component name=\"component_bob\">"
                "<variable name=\"variable_bob\"/>"
            "</component>"
            "<component name=\"component_dave\">"
                "<variable name=\"variable_dave\"/>"
            "</component>"
            "<connection>"
                "<map_components component_2=\"component_dave\" component_1=\"component_bob\"/>"
                "<map_variables variable_2=\"variable_angus\" variable_1=\"variable_bob\"/>"
            "</connection>"
        "</model>";
    std::string expectedError = "Variable 'variable_angus' is specified as variable_2 in a connection but it does not exist in component_2 component 'component_dave' of model ''.";

    // Parse
    libcellml::Parser p(libcellml::Format::XML);
    p.parseModel(e);
    EXPECT_EQ(1, p.errorCount());
    EXPECT_EQ(expectedError, p.getError(0)->getDescription());
}

TEST(Parser, component2InConnectionMissing) {
    const std::string in =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/1.2#\">"
            "<component name=\"component_bob\">"
                "<variable name=\"variable_bob\"/>"
            "</component>"
            "<component name=\"component_dave\">"
                "<variable name=\"variable_dave\"/>"
            "</component>"
            "<connection>"
                "<map_components component_1=\"component_bob\"/>"
                "<map_variables variable_2=\"variable_angus\" variable_1=\"variable_bob\"/>"
            "</connection>"
        "</model>";
    const std::string e =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/1.2#\">"
            "<component name=\"component_bob\">"
                "<variable name=\"variable_bob\"/>"
            "</component>"
            "<component name=\"component_dave\">"
                "<variable name=\"variable_dave\"/>"
            "</component>"
        "</model>";
    std::string expectedError1 = "Connection in model '' does not have a valid component_2 in a map_components element.";
    std::string expectedError2 = "Connection in model '' specifies 'variable_angus' as variable_2 but the corresponding component_2 is invalid.";

    // Parse
    libcellml::Parser p(libcellml::Format::XML);
    libcellml::ModelPtr m = p.parseModel(in);
    EXPECT_EQ(2, p.errorCount());
    EXPECT_EQ(e, m->serialise(libcellml::Format::XML));
    EXPECT_EQ(expectedError1, p.getError(0)->getDescription());
    EXPECT_EQ(expectedError2, p.getError(1)->getDescription());

}

TEST(Parser, connectionVariable2Missing) {
    const std::string e =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/1.2#\">"
            "<component name=\"component_bob\">"
                "<variable name=\"variable_bob\"/>"
            "</component>"
            "<component name=\"component_dave\">"
                "<variable name=\"variable_dave\"/>"
            "</component>"
            "<connection>"
                "<map_components component_2=\"component_dave\" component_1=\"component_bob\"/>"
                "<map_variables variable_1=\"variable_bob\"/>"
            "</connection>"
        "</model>";
    std::string expectedError1 = "Connection in model '' does not have a valid variable_2 in a map_variables element.";

    // Parse
    libcellml::Parser p(libcellml::Format::XML);
    p.parseModel(e);
    EXPECT_EQ(1, p.errorCount());
    EXPECT_EQ(expectedError1, p.getError(0)->getDescription());
}

TEST(Parser, connectionVariable1Missing) {
    const std::string e =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/1.2#\">"
            "<component name=\"component_bob\">"
                "<variable name=\"variable_bob\"/>"
            "</component>"
            "<component name=\"component_dave\">"
                "<variable name=\"variable_dave\"/>"
            "</component>"
            "<connection>"
                "<map_components component_2=\"component_dave\" component_1=\"component_bob\"/>"
                "<map_variables variable_2=\"variable_dave\"/>"
            "</connection>"
        "</model>";
    std::string expectedError1 = "Connection in model '' does not have a valid variable_1 in a map_variables element.";

    // Parse
    libcellml::Parser p(libcellml::Format::XML);
    p.parseModel(e);
    EXPECT_EQ(1, p.errorCount());
    EXPECT_EQ(expectedError1, p.getError(0)->getDescription());
}

TEST(Parser, connectionErrorNoMapVariablesType) {
    const std::string in =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/1.2#\">"
            "<component name=\"component1\">"
                "<variable name=\"variable1\"/>"
            "</component>"
            "<component name=\"component2\">"
                "<variable name=\"variable2\"/>"
            "</component>"
            "<connection>"
                "<map_components component_1=\"component1\"  component_2=\"component2\"/>"
                "<map_variabels variable_1=\"variable1\" variable_2=\"variable2\"/>"
            "</connection>"
        "</model>";
    std::string expectedError1 = "Connection in model '' has an invalid child element 'map_variabels'.";
    std::string expectedError2 = "Connection in model '' does not have a map_variables element.";

    libcellml::Parser p(libcellml::Format::XML);
    p.parseModel(in);
    EXPECT_EQ(2, p.errorCount());
    EXPECT_EQ(expectedError1, p.getError(0)->getDescription());
    EXPECT_EQ(expectedError2, p.getError(1)->getDescription());
}

TEST(Parser, invalidImportsAndGetError) {
    const std::string input =
    "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
    "<model xmlns=\"http://www.cellml.org/cellml/1.2#\">"
       "<import xlink:href=\"some-other-model.xml\" "
               "xmlns:xlink=\"http://www.w3.org/1999/xlink\" sauce=\"hollandaise\">"
           "<units units_ref=\"a_units_in_that_model\" "
                      "name=\"units_in_this_model\"/>"
           "<component component_ref=\"a_component_in_that_model\" "
               "name=\"component_in_this_model\"/>"
           "<invalid_nonsense/>"
           "<units units_ruff=\"dog\" name=\"fido\"/>"
           "<component component_meow=\"cat\" name=\"frank\"/>"
       "</import>"
    "</model>";

    std::string expectError1 = "Import from 'some-other-model.xml' has an invalid attribute 'sauce'.";
    std::string expectError2 = "Import from 'some-other-model.xml' has an invalid child element 'invalid_nonsense'.";
    std::string expectError3 = "Import of units 'fido' from 'some-other-model.xml' has an invalid attribute 'units_ruff'.";
    std::string expectError4 = "Import of component 'frank' from 'some-other-model.xml' has an invalid attribute 'component_meow'.";

    const std::string output =
    "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
    "<model xmlns=\"http://www.cellml.org/cellml/1.2#\">"
       "<import xlink:href=\"some-other-model.xml\" "
         "xmlns:xlink=\"http://www.w3.org/1999/xlink\">"
         "<component component_ref=\"a_component_in_that_model\" "
           "name=\"component_in_this_model\"/>"
       "</import>"
       "<import xlink:href=\"some-other-model.xml\" "
         "xmlns:xlink=\"http://www.w3.org/1999/xlink\">"
         "<units units_ref=\"a_units_in_that_model\" "
           "name=\"units_in_this_model\"/>"
        "</import>"
    "</model>";

    libcellml::Parser p(libcellml::Format::XML);
    libcellml::ModelPtr m = p.parseModel(input);
    EXPECT_EQ(4, p.errorCount());
    EXPECT_EQ(expectError1, p.getError(0)->getDescription());
    EXPECT_EQ(expectError2, p.getError(1)->getDescription());
    EXPECT_EQ(expectError3, p.getError(2)->getDescription());
    EXPECT_EQ(expectError4, p.getError(3)->getDescription());
    EXPECT_EQ(output, m->serialise(libcellml::Format::XML));

    libcellml::ImportPtr import = m->getUnits("units_in_this_model")->getImport();
    // Get import from error and check.
    EXPECT_EQ(import, p.getError(0)->getImport());
    // Get const import from error and check.
    const libcellml::ErrorPtr err = static_cast<const libcellml::Parser>(p).getError(0);
    const libcellml::ImportPtr importFromError = err->getImport();
    EXPECT_EQ(import, importFromError);
}

TEST(Parser, invalidModelWithAllKindsOfErrors) {
    const std::string input =
    "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
    "<model xmlns=\"http://www.cellml.org/cellml/1.2#\" name=\"starwars\" episode=\"four\">"
       "<import princess=\"leia\"/>"
       "<units jedi=\"luke\" lightsaber/>"
       "<component ship=\"falcon\">"
            "<variable pilot=\"han\"/>"
       "</component>"
       "<connection wookie=\"chewie\"/>"
       "<encapsulation yoda=\"green\"/>"
    "</model>";

    std::vector<std::string> expectedErrors = {
        "Specification mandate value for attribute lightsaber.",
        "Model 'starwars' has an invalid attribute 'episode'.",
        "Import from '' has an invalid attribute 'princess'.",
        "Units '' has an invalid attribute 'jedi'.",
        "Component '' has an invalid attribute 'ship'.",
        "Variable '' has an invalid attribute 'pilot'.",
        "Connection in model 'starwars' has an invalid attribute 'wookie'.",
        "Encapsulation in model 'starwars' has an invalid attribute 'yoda'."
    };

    // Parse
    libcellml::Parser parser(libcellml::Format::XML);
    parser.parseModel(input);

    // Add an undefined error
    libcellml::ErrorPtr undefinedError = std::make_shared<libcellml::Error>();
    if (undefinedError->isKind(libcellml::Error::Kind::UNDEFINED)) {
        parser.addError(undefinedError);
    }

    // Check that we have all the expected errors.
    std::vector<bool> foundKind(9, false);
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
            case (libcellml::Error::Kind::UNDEFINED): {
                foundKind.at(5) = true;
                break;
            }
            case (libcellml::Error::Kind::UNITS): {
                foundKind.at(6) = true;
                break;
            }
            case (libcellml::Error::Kind::VARIABLE): {
                foundKind.at(7) = true;
                break;
            }
            case (libcellml::Error::Kind::XML): {
                foundKind.at(8) = true;
                break;
            }
        }
    }
    bool foundAllKinds = false;
    if (std::all_of(foundKind.begin(), foundKind.end(), [](bool i) {return i;})) {
        foundAllKinds = true;
    }
    EXPECT_TRUE(foundAllKinds);
}

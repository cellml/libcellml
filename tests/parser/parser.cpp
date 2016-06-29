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

#include <libcellml>
#include <iostream>
/*
 * The tests in this file are here to catch any branches of code that
 * are not picked up by the main tests testing the API of the library
 */

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

TEST(Parser, parseModelWithNamedComponentWithInvalidBaseUnits) {
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
    libcellml::Parser parser(libcellml::Format::XML);
    libcellml::ModelPtr model = parser.parseModel(in);
    std::string a = model->serialise(libcellml::Format::XML);

    EXPECT_EQ(1, parser.errorCount());
    EXPECT_EQ("Invalid base_unit attribute in units 'dimensionless'. Should be either 'yes' or 'no', and not 'joe'.", parser.getError(0)->getDescription());

    EXPECT_EQ(e, a);
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

TEST(Parser, parser) {
    libcellml::Parser p(libcellml::Format::XML), pm(libcellml::Format::XML), pa(libcellml::Format::XML);
    pa = p;
    pm = std::move(p);

    libcellml::Parser pc(pm);
}

TEST(Parser, entityError) {
    std::string ex = "";

    libcellml::EntityErrorPtr e = std::make_shared<libcellml::EntityError>();

    EXPECT_EQ(ex, e->getDescription());
}

TEST(Parser, emptyString) {
    std::string ex = "";

    libcellml::Parser p(libcellml::Format::XML);
    EXPECT_THROW(p.parseModel(ex), std::invalid_argument);
}

TEST(Parser, nonXmlString) {
    std::string ex = "Not an xml string.";

    libcellml::Parser p(libcellml::Format::XML);
    EXPECT_THROW(p.parseModel(ex), std::invalid_argument);
}

TEST(Parser, modelWithInvalidElement) {
    std::string input1 =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/1.2#\" name=\"bilbo\">"
            "<hobbit/>"
        "</model>";
    std::string expectError1 = "Invalid XML element type 'hobbit' in model 'bilbo'.";

    std::string input2 =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/1.2#\">"
            "<hobbit/>"
        "</model>";
    std::string expectError2 = "Invalid XML element type 'hobbit' in model ''.";

    libcellml::Parser p(libcellml::Format::XML);
    p.parseModel(input1);
    EXPECT_EQ(1, p.errorCount());
    EXPECT_EQ(expectError1, p.getError(0)->getDescription());

    p.clearErrors();
    p.parseModel(input2);
    EXPECT_EQ(1, p.errorCount());
    EXPECT_EQ(expectError2, p.getError(0)->getDescription());
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
                  "<unit multiplier=\"Z\" offset=\"MM\" exponent=\"35.0E+310\" units=\"celsius\" bill=\"murray\"/>"
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
    libcellml::Parser parser(libcellml::Format::XML);
    libcellml::ModelPtr model = parser.parseModel(in);

    EXPECT_EQ(10, parser.errorCount());

    for (size_t i = 0; i < parser.errorCount(); ++i) {
        EXPECT_TRUE(parser.getError(i)->getDescription().length() > 0);
    }

    std::string a = model->serialise(libcellml::Format::XML);
    EXPECT_EQ(e, a);
}

TEST(Parser, emptyEncapsulation) {
    std::string ex =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/1.2#\" name=\"model_name\">"
            "<encapsulation>"
            "</encapsulation>"
        "</model>";

    libcellml::Parser p(libcellml::Format::XML);
    p.parseModel(ex);
    EXPECT_EQ(1, p.errorCount());
    EXPECT_EQ(47, p.getError(0)->getDescription().length());
}

TEST(Parser, encapsulationWithNoComponentAttribute) {
    std::string ex =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/1.2#\" name=\"model_name\">"
            "<encapsulation>"
                "<component_ref></component_ref>"
            "</encapsulation>"
        "</model>";

    libcellml::Parser p(libcellml::Format::XML);
    p.parseModel(ex);
    EXPECT_EQ(1, p.errorCount());
    EXPECT_EQ(57, p.getError(0)->getDescription().length());
}

TEST(Parser, encapsulationWithNoComponentRef) {
    std::string ex =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/1.2#\" name=\"model_name\">"
            "<encapsulation>"
                "<component_free></component_free>"
            "</encapsulation>"
        "</model>";

    libcellml::Parser p(libcellml::Format::XML);
    p.parseModel(ex);
    EXPECT_EQ(1, p.errorCount());
    EXPECT_EQ(47, p.getError(0)->getDescription().length());
}

TEST(Parser, encapsulationWithNoComponent) {
    std::string ex =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/1.2#\" name=\"model_name\">"
            "<encapsulation>"
            "<component_ref component=\"bob\">"
                "<component_ref></component_ref>"
            "</component_ref>"
            "</encapsulation>"
        "</model>";

    libcellml::Parser p(libcellml::Format::XML);
    p.parseModel(ex);
    EXPECT_EQ(2, p.errorCount());
    EXPECT_EQ(85, p.getError(0)->getDescription().length());
}

TEST(Parser, encapsulationWithMissingComponent) {
    std::string ex =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/1.2#\" name=\"model_name\">"
            "<component name=\"bob\"/>"
            "<encapsulation>"
            "<component_ref component=\"bob\">"
                "<component_ref component=\"dave\"></component_ref>"
            "</component_ref>"
            "</encapsulation>"
        "</model>";

    libcellml::Parser p(libcellml::Format::XML);
    p.parseModel(ex);
    EXPECT_EQ(1, p.errorCount());
    EXPECT_EQ(86, p.getError(0)->getDescription().length());
}

TEST(Parser, encapsulationWithNoComponentChild) {
    std::string ex =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/1.2#\" name=\"model_name\">"
            "<component name=\"bob\"/>"
            "<encapsulation>"
            "<component_ref component=\"bob\">"
            "</component_ref>"
            "</encapsulation>"
        "</model>";

    libcellml::Parser p(libcellml::Format::XML);
    p.parseModel(ex);
    EXPECT_EQ(1, p.errorCount());
    EXPECT_EQ(43, p.getError(0)->getDescription().length());
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

    libcellml::Parser p(libcellml::Format::XML);
    p.parseModel(ex);
    EXPECT_EQ(1, p.errorCount());
    EXPECT_EQ(47, p.getError(0)->getDescription().length());
}

TEST(Parser, encapsulationWithGrandchild) {
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

    libcellml::Parser p(libcellml::Format::XML);
    p.parseModel(ex);
    EXPECT_EQ(1, p.errorCount());
    EXPECT_EQ(47, p.getError(0)->getDescription().length());
}

TEST(Parser, parserWithEmptyConnections) {
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

TEST(Parser, invalidVariableAttributes) {
    const std::string in =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/1.2#\">"
            "<component name=\"componentA\">"
                "<variable name=\"quixote\" don=\"true\"/>"
                "<variable windmill=\"tilted\"/>"
            "</component>"
        "</model>";
    std::string expectError1 = "Invalid attribute 'don' found in variable 'quixote'.";
    std::string expectError2 = "Invalid attribute 'windmill' found in variable ''.";

    libcellml::Parser p(libcellml::Format::XML);
    p.parseModel(in);
    EXPECT_EQ(2, p.errorCount());
    EXPECT_EQ(expectError1, p.getError(0)->getDescription());
    EXPECT_EQ(expectError2, p.getError(1)->getDescription());
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
            "<connection>"
                "<map_variables variable_1=\"variable1\" variable_2=\"variable2\"/>"
            "</connection>"
        "</model>";
    std::string expectedError1 = "Connection in model 'modelName' does not have a map_components element.";
    std::string expectedError2 = "Connection in model 'modelName' specifies 'variable1' as variable_1 but the corresponding component_1 is invalid.";
    std::string expectedError3 = "Connection in model 'modelName' specifies 'variable2' as variable_2 but the corresponding component_2 is invalid.";

    libcellml::Parser p(libcellml::Format::XML);
    p.parseModel(in);
    EXPECT_EQ(3, p.errorCount());
    EXPECT_EQ(expectedError1, p.getError(0)->getDescription());
    EXPECT_EQ(expectedError2, p.getError(1)->getDescription());
    EXPECT_EQ(expectedError3, p.getError(2)->getDescription());
}

TEST(Parser, connectionErrorNoMapVariables) {
    const std::string in =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/1.2#\">"
            "<component name=\"componentA\">"
                "<variable name=\"variable1\"/>"
            "</component>"
            "<connection>"
                "<map_components component_2=\"componentA\" component_1=\"componentA\"/>"
            "</connection>"
        "</model>";
    std::string expectedError = "Connection in model '' does not have a map_variables element.";

    libcellml::Parser p(libcellml::Format::XML);
    p.parseModel(in);
    EXPECT_EQ(1, p.errorCount());
    EXPECT_EQ(expectedError, p.getError(0)->getDescription());
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

TEST(Parser, invalidRootNode) {
    std::string ex =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<yodel xmlns=\"http://www.cellml.org/cellml/1.2#\" name=\"model_name\">"
        "</yodel>";
    std::string expectedError1 = "Invalid XML element type (not a model).";

    libcellml::Parser p(libcellml::Format::XML);
    p.parseModel(ex);
    EXPECT_EQ(1, p.errorCount());
    EXPECT_EQ(expectedError1, p.getError(0)->getDescription());
}

TEST(Parser, invalidModelAttribute) {
    std::string ex =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/1.2#\" game=\"model_name\">"
        "</model>";

    libcellml::Parser p(libcellml::Format::XML);
    p.parseModel(ex);
    EXPECT_EQ(1, p.errorCount());
    EXPECT_EQ(57, p.getError(0)->getDescription().length());
}

TEST(Parser, invalidModelElement) {
    std::string ex =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/1.2#\" name=\"model_name\">"
            "<uknits/>"
        "</model>";

    libcellml::Parser p(libcellml::Format::XML);
    p.parseModel(ex);
    EXPECT_EQ(1, p.errorCount());
    EXPECT_EQ(56, p.getError(0)->getDescription().length());
}

TEST(Parser, unitsAttributeError) {
    std::string ex =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/1.2#\" name=\"model_name\">"
            "<units name=\"pH\" base_unit=\"yes\" invalid_attribute=\"yes\"/>"
        "</model>";

    libcellml::Parser p(libcellml::Format::XML);
    p.parseModel(ex);
    EXPECT_EQ(1, p.errorCount());
    EXPECT_EQ(58, p.getError(0)->getDescription().length());
}

TEST(Parser, componentAttributeErrors) {
    std::string input1 =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/1.2#\" name=\"model_name\">"
          "<component lame=\"randy\"/>"
        "</model>";
    std::string expectError1 = "Invalid attribute 'lame' found in component ''.";

    std::string input2 =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/1.2#\" name=\"model_name\">"
          "<component name=\"randy\" son=\"stan\"/>"
        "</model>";
    std::string expectError2 = "Invalid attribute 'son' found in component 'randy'.";

    std::string input3 =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/1.2#\" name=\"model_name\">"
          "<component son=\"stan\" name=\"randy\"/>"
        "</model>";
    std::string expectError3 = "Invalid attribute 'son' found in component 'randy'.";

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
    std::string expectError1 = "Invalid child element 'son' found in component ''.";

    std::string input2 =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/1.2#\" name=\"model_name\">"
          "<component name=\"randy\">"
            "<son name=\"stan\"/>"
          "</component>"
        "</model>";
    std::string expectError2 = "Invalid child element 'son' found in component 'randy'.";

    libcellml::Parser p(libcellml::Format::XML);
    p.parseModel(input1);
    EXPECT_EQ(1, p.errorCount());
    EXPECT_EQ(expectError1, p.getError(0)->getDescription());

    p.clearErrors();
    p.parseModel(input2);
    EXPECT_EQ(1, p.errorCount());
    EXPECT_EQ(expectError2, p.getError(0)->getDescription());
}

TEST(Parser, variableAttributeErrors) {
    std::string input1 =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/1.2#\" name=\"model_name\">"
            "<component name=\"randy\">"
                "<variable lame=\"randy\"/>"
            "</component>"
        "</model>";
    std::string expectError1 = "Invalid attribute 'lame' found in variable ''.";

    std::string input2 =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/1.2#\" name=\"model_name\">"
            "<component name=\"randy\">"
                "<variable name=\"randy\" son=\"stan\"/>"
            "</component>"
        "</model>";
    std::string expectError2 = "Invalid attribute 'son' found in variable 'randy'.";

    libcellml::Parser p(libcellml::Format::XML);
    p.parseModel(input1);
    EXPECT_EQ(1, p.errorCount());
    EXPECT_EQ(expectError1, p.getError(0)->getDescription());

    p.clearErrors();
    p.parseModel(input2);
    EXPECT_EQ(1, p.errorCount());
    EXPECT_EQ(expectError2, p.getError(0)->getDescription());
}

TEST(Parser, unitsElementErrors) {
    std::string input1 =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/1.2#\" name=\"model_name\">"
          "<units>"
            "<son name=\"stan\"/>"
          "</units>"
        "</model>";
    std::string expectError1 = "Invalid child element 'son' found in units ''.";

    std::string input2 =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/1.2#\" name=\"model_name\">"
          "<units name=\"randy\">"
            "<son name=\"stan\"/>"
          "</units>"
        "</model>";
    std::string expectError2 = "Invalid child element 'son' found in units 'randy'.";

    libcellml::Parser p(libcellml::Format::XML);
    p.parseModel(input1);
    EXPECT_EQ(1, p.errorCount());
    EXPECT_EQ(expectError1, p.getError(0)->getDescription());

    p.clearErrors();
    p.parseModel(input2);
    EXPECT_EQ(1, p.errorCount());
    EXPECT_EQ(expectError2, p.getError(0)->getDescription());
}

TEST(Parser, invalidImports) {
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

    std::string expectError1 = "Invalid attribute 'sauce' found in import from 'some-other-model.xml'.";
    std::string expectError2 = "Invalid child element 'invalid_nonsense' found in import from 'some-other-model.xml'.";
    std::string expectError3 = "Invalid attribute 'units_ruff' found in import of units 'fido' from 'some-other-model.xml'.";
    std::string expectError4 = "Invalid attribute 'component_meow' found in import of component 'frank' from 'some-other-model.xml'.";

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
}

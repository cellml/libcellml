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

TEST(Validator, namedModel) {
    libcellml::Validator validator;
    libcellml::ModelPtr model = std::make_shared<libcellml::Model>();
    model->setName("awesomeName");
    validator.validateModel(model);
    EXPECT_EQ(0, validator.errorCount());
}

TEST(Validator, unnamedModel) {
    std::string expectedError = "Model does not have a valid name attribute.";
    libcellml::Validator validator;
    libcellml::ModelPtr model = std::make_shared<libcellml::Model>();
    validator.validateModel(model);
    EXPECT_EQ(1, validator.errorCount());
    EXPECT_EQ(expectedError, validator.getError(0)->getDescription());
}

TEST(Validator, moveCopyValidatorWithUnnamedModel) {
    libcellml::ErrorPtr err = std::make_shared<libcellml::Error>();
    libcellml::Validator v, vm;
    libcellml::ModelPtr model = std::make_shared<libcellml::Model>();
    v.validateModel(model);

    // Move
    vm = std::move(v);
    // Copy
    libcellml::Validator vc(vm);

    // Check that the model error is in the copy.
    EXPECT_EQ(libcellml::Error::Kind::MODEL, vc.getError(0)->getKind());
}

TEST(Validator, namedModelWithUnnamedComponent) {
    std::string expectedError = "Component does not have a valid name attribute.";
    libcellml::Validator validator;
    libcellml::ModelPtr model = std::make_shared<libcellml::Model>();
    libcellml::ComponentPtr component = std::make_shared<libcellml::Component>();
    model->setName("awesomeName");
    model->addComponent(component);
    validator.validateModel(model);
    EXPECT_EQ(1, validator.errorCount());
    EXPECT_EQ(expectedError, validator.getError(0)->getDescription());
}

TEST(Validator, unnamedModelWithUnnamedComponentWithUnnamedUnits) {
    std::vector<std::string> expectedErrors = {
        "Model does not have a valid name attribute.",
        "Component does not have a valid name attribute.",
        "Units does not have a valid name attribute."
    };

    libcellml::Validator validator;
    libcellml::ModelPtr model = std::make_shared<libcellml::Model>();
    libcellml::ComponentPtr component = std::make_shared<libcellml::Component>();
    libcellml::UnitsPtr units = std::make_shared<libcellml::Units>();
    model->addComponent(component);
    component->addUnits(units);
    validator.validateModel(model);

    EXPECT_EQ(expectedErrors.size(), validator.errorCount());
    for (size_t i = 0; i < validator.errorCount(); ++i) {
        EXPECT_EQ(expectedErrors.at(i), validator.getError(i)->getDescription());
    }
}

TEST(Validator, modelWithDuplicateComponentsAndUnits) {
    std::vector<std::string> expectedErrors = {
        "Component 'michael' contains multiple units with the name 'batman'. Valid units names should be unique to their component.",
        "Model 'multiplicity' contains multiple components with the name 'michael'. Valid component names should be unique to their model.",
        "Model 'multiplicity' contains multiple units with the name 'keaton'. Valid units names should be unique to their model."
    };

    libcellml::Validator validator;
    libcellml::ModelPtr model = std::make_shared<libcellml::Model>();
    libcellml::ComponentPtr c1 = std::make_shared<libcellml::Component>();
    libcellml::ComponentPtr c2 = std::make_shared<libcellml::Component>();
    libcellml::UnitsPtr u1 = std::make_shared<libcellml::Units>();
    libcellml::UnitsPtr u2 = std::make_shared<libcellml::Units>();
    libcellml::UnitsPtr u3 = std::make_shared<libcellml::Units>();
    libcellml::UnitsPtr u4 = std::make_shared<libcellml::Units>();
    model->addComponent(c1);
    model->addComponent(c2);
    model->addUnits(u1);
    model->addUnits(u2);
    c1->addUnits(u3);
    c1->addUnits(u4);

    model->setName("multiplicity");
    c1->setName("michael");
    c2->setName("michael");
    u1->setName("keaton");
    u2->setName("keaton");
    u3->setName("batman");
    u4->setName("batman");
    validator.validateModel(model);

    EXPECT_EQ(expectedErrors.size(), validator.errorCount());
    for (size_t i = 0; i < validator.errorCount(); ++i) {
        EXPECT_EQ(expectedErrors.at(i), validator.getError(i)->getDescription());
    }
}

TEST(Validator, unnamedAndDuplicateNamedVariablesWithAndWithoutValidUnits) {
    std::vector<std::string> expectedErrors = {
        "Component 'fargo' contains multiple variables with the name 'margie'. Valid variable names should be unique to their component.",
        "Variable does not have a valid name attribute.",
        "Variable 'margie' does not have a valid units attribute."
    };

    libcellml::Validator validator;
    libcellml::ModelPtr model = std::make_shared<libcellml::Model>();
    libcellml::ComponentPtr c1 = std::make_shared<libcellml::Component>();
    libcellml::VariablePtr v1 = std::make_shared<libcellml::Variable>();
    libcellml::VariablePtr v2 = std::make_shared<libcellml::Variable>();
    libcellml::VariablePtr v3 = std::make_shared<libcellml::Variable>();
    model->addComponent(c1);
    c1->addVariable(v1);
    c1->addVariable(v2);
    c1->addVariable(v3);

    model->setName("minnesota");
    c1->setName("fargo");
    v1->setUnits("ampere");
    v2->setName("margie");
    v2->setUnits("ampere");
    v3->setName("margie");
    validator.validateModel(model);

    EXPECT_EQ(expectedErrors.size(), validator.errorCount());
    for (size_t i = 0; i < validator.errorCount(); ++i) {
        EXPECT_EQ(expectedErrors.at(i), validator.getError(i)->getDescription());
    }
}

TEST(Validator, invalidVariableInitialValuesAndInterfaces) {
    std::vector<std::string> expectedErrors = {
        "Variable 'candidate' has an invalid interface attribute value 'orange'.",
        "Variable 'candidate' has an invalid initial value 'trump'. Initial values must be a real number string or a variable reference."
    };

    libcellml::Validator validator;
    libcellml::ModelPtr model = std::make_shared<libcellml::Model>();
    libcellml::ComponentPtr c1 = std::make_shared<libcellml::Component>();
    libcellml::VariablePtr v1 = std::make_shared<libcellml::Variable>();
    model->addComponent(c1);
    c1->addVariable(v1);

    model->setName("election");
    c1->setName("republican");
    v1->setName("candidate");
    v1->setUnits("ampere");
    v1->setInterfaceType("orange");
    v1->setInitialValue("trump");

    validator.validateModel(model);

    EXPECT_EQ(expectedErrors.size(), validator.errorCount());
    for (size_t i = 0; i < validator.errorCount(); ++i) {
        EXPECT_EQ(expectedErrors.at(i), validator.getError(i)->getDescription());
    }
}

TEST(Validator, importUnits) {
    std::vector<std::string> expectedErrors = {
        "Imported units 'invalid_imported_units_in_this_model' does not have a valid units_ref attribute.",
        "Import of units 'invalid_imported_units_in_this_model' does not have a valid locator xlink:href attribute.",
        "Model 'model_name' contains multiple imported units from 'some-other-model.xml' with the same units_ref attribute 'units_in_that_model'."
    };

    libcellml::Validator v;
    libcellml::ModelPtr m = std::make_shared<libcellml::Model>();
    m->setName("model_name");

    // Valid units import
    libcellml::ImportPtr imp = std::make_shared<libcellml::Import>();
    imp->setSource("some-other-model.xml");
    libcellml::UnitsPtr importedUnits = std::make_shared<libcellml::Units>();
    importedUnits->setName("valid_imported_units_in_this_model");
    importedUnits->setSourceUnits(imp, "units_in_that_model");
    m->addUnits(importedUnits);
    v.validateModel(m);
    EXPECT_EQ(0, v.errorCount());

    // Invalid units import- missing refs
    libcellml::ImportPtr imp2 = std::make_shared<libcellml::Import>();
    libcellml::UnitsPtr importedUnits2 = std::make_shared<libcellml::Units>();
    importedUnits2->setName("invalid_imported_units_in_this_model");
    importedUnits2->setSourceUnits(imp2, "");
    m->addUnits(importedUnits2);
    v.validateModel(m);
    EXPECT_EQ(2, v.errorCount());

    // Invalid units import - duplicate refs
    libcellml::ImportPtr imp3 = std::make_shared<libcellml::Import>();
    imp3->setSource("some-other-model.xml");
    libcellml::UnitsPtr importedUnits3 = std::make_shared<libcellml::Units>();
    importedUnits3->setName("duplicate_imported_units_in_this_model");
    importedUnits3->setSourceUnits(imp3, "units_in_that_model");
    m->addUnits(importedUnits3);
    v.validateModel(m);
    EXPECT_EQ(3, v.errorCount());

    // Check for expected error messages
    for (size_t i = 0; i < v.errorCount(); ++i) {
        //std::cout << v.getError(i)->getDescription() + "\n";
        EXPECT_EQ(expectedErrors.at(i), v.getError(i)->getDescription());
    }
}

TEST(Validator, importComponents) {
    std::vector<std::string> expectedErrors = {
        "Imported component 'invalid_imported_component_in_this_model' does not have a valid component_ref attribute.",
        "Import of component 'invalid_imported_component_in_this_model' does not have a valid locator xlink:href attribute.",
        "Model 'model_name' contains multiple imported components from 'some-other-model.xml' with the same component_ref attribute 'component_in_that_model'."
    };

    libcellml::Validator v;
    libcellml::ModelPtr m = std::make_shared<libcellml::Model>();
    m->setName("model_name");

    // Valid component import
    libcellml::ImportPtr imp = std::make_shared<libcellml::Import>();
    imp->setSource("some-other-model.xml");
    libcellml::ComponentPtr importedComponent = std::make_shared<libcellml::Component>();
    importedComponent->setName("valid_imported_component_in_this_model");
    importedComponent->setSourceComponent(imp, "component_in_that_model");
    m->addComponent(importedComponent);
    v.validateModel(m);
    EXPECT_EQ(0, v.errorCount());

    // Invalid component import- missing refs
    libcellml::ImportPtr imp2 = std::make_shared<libcellml::Import>();
    libcellml::ComponentPtr importedComponent2 = std::make_shared<libcellml::Component>();
    importedComponent2->setName("invalid_imported_component_in_this_model");
    importedComponent2->setSourceComponent(imp2, "");
    m->addComponent(importedComponent2);
    v.validateModel(m);
    EXPECT_EQ(2, v.errorCount());

    // Invalid component import - duplicate refs
    libcellml::ImportPtr imp3 = std::make_shared<libcellml::Import>();
    imp3->setSource("some-other-model.xml");
    libcellml::ComponentPtr importedComponent3 = std::make_shared<libcellml::Component>();
    importedComponent3->setName("duplicate_imported_component_in_this_model");
    importedComponent3->setSourceComponent(imp3, "component_in_that_model");
    m->addComponent(importedComponent3);
    v.validateModel(m);
    EXPECT_EQ(3, v.errorCount());

    // Check for expected error messages
    for (size_t i = 0; i < v.errorCount(); ++i) {
        //std::cout << v.getError(i)->getDescription() + "\n";
        EXPECT_EQ(expectedErrors.at(i), v.getError(i)->getDescription());
    }
}

TEST(Validator, validMath) {
    std::string math =
    "<math xmlns=\"http://www.w3.org/1998/Math/MathML\">"
      "<apply><eq/>"
        "<ci>C</ci>"
        "<apply><plus/>"
          "<ci>A</ci>"
          "<ci>B</ci>"
        "</apply>"
      "</apply>"
    "</math>";

    libcellml::Validator v;
    libcellml::ModelPtr m = std::make_shared<libcellml::Model>();
    libcellml::ComponentPtr c = std::make_shared<libcellml::Component>();
    libcellml::VariablePtr v1 = std::make_shared<libcellml::Variable>();
    libcellml::VariablePtr v2 = std::make_shared<libcellml::Variable>();
    libcellml::VariablePtr v3 = std::make_shared<libcellml::Variable>();

    m->setName("modelName");
    c->setName("componentName");
    v1->setName("A");
    v2->setName("B");
    v3->setName("C");
    v1->setInitialValue("1.0");
    v2->setInitialValue("-1.0");
    v1->setUnits("dimensionless");
    v2->setUnits("dimensionless");
    v3->setUnits("dimensionless");

    c->addVariable(v1);
    c->addVariable(v2);
    c->addVariable(v3);
    c->setMath(math);
    m->addComponent(c);

    v.validateModel(m);
    EXPECT_EQ(0, v.errorCount());
}

TEST(Validator, invalidMathMLElements) {
    std::string math =
    "<math xmlns=\"http://www.w3.org/1998/Math/MathML\">"
      "<apply><equals/>"
        "<ci>C</ci>"
        "<apply><addition/>"
          "<ci>A</ci>"
          "<ci>B</ci>"
        "</apply>"
      "</apply>"
    "</math>";
    std::vector<std::string> expectedErrors = {
        "No declaration for element equals.",
        "No declaration for element addition."
    };

    libcellml::Validator v;
    libcellml::ModelPtr m = std::make_shared<libcellml::Model>();
    libcellml::ComponentPtr c = std::make_shared<libcellml::Component>();
    libcellml::VariablePtr v1 = std::make_shared<libcellml::Variable>();
    libcellml::VariablePtr v2 = std::make_shared<libcellml::Variable>();
    libcellml::VariablePtr v3 = std::make_shared<libcellml::Variable>();

    m->setName("modelName");
    c->setName("componentName");
    v1->setName("A");
    v2->setName("B");
    v3->setName("C");
    v1->setInitialValue("1.0");
    v2->setInitialValue("-1.0");
    v1->setUnits("dimensionless");
    v2->setUnits("dimensionless");
    v3->setUnits("dimensionless");

    c->addVariable(v1);
    c->addVariable(v2);
    c->addVariable(v3);
    c->setMath(math);
    m->addComponent(c);

    v.validateModel(m);
    EXPECT_EQ(4, v.errorCount());

    // Check for two expected error messages (see note above).
    for (size_t i = 0; i < 2; ++i) {
        //std::cout << v.getError(i)->getDescription() + "\n";
        EXPECT_EQ(expectedErrors.at(i), v.getError(i)->getDescription());
    }
}

TEST(Validator, invalidMathMLVariables) {
    std::string math =
        "<math xmlns=\"http://www.w3.org/1998/Math/MathML\">"
          "<apply><eq/>"
            "<ci>answer</ci>"
            "<apply><plus/>"
              "<ci>A</ci>"
              "<apply><plus/>"
                "<bvar>"
                  "<ci>new_bvar</ci>"
                "</bvar>"
                "<apply><plus/>"
                  "<ci>   </ci>"
                  "<apply><plus/>"
                    "<ci><nonsense/></ci>"
                    "<apply><plus/>"
                      "<ci/>"
                      "<bvar>"
                        "<ci>B</ci>"
                      "</bvar>"
                    "</apply>"
                  "</apply>"
                "</apply>"
              "</apply>"
            "</apply>"
          "</apply>"
        "</math>";
    std::vector<std::string> expectedErrors = {
        "No declaration for element nonsense.",
        "Element nonsense is not declared in ci list of possible children.",
        "MathML in component 'componentName' contains 'B' as a bvar ci element but it is already a variable name.",
        "MathML ci element has the child text 'answer', which does not correspond with any variable names present in component 'componentName' and is not a variable defined within a bvar element.",
        "MathML ci element has a whitespace-only child element.",
        "MathML ci element has no valid variable."
    };

    libcellml::Validator v;
    libcellml::ModelPtr m = std::make_shared<libcellml::Model>();
    libcellml::ComponentPtr c = std::make_shared<libcellml::Component>();
    libcellml::VariablePtr v1 = std::make_shared<libcellml::Variable>();
    libcellml::VariablePtr v2 = std::make_shared<libcellml::Variable>();
    libcellml::VariablePtr v3 = std::make_shared<libcellml::Variable>();

    m->setName("modelName");
    c->setName("componentName");
    v1->setName("A");
    v2->setName("B");
    v3->setName("C");
    v1->setInitialValue("1.0");
    v2->setInitialValue("-1.0");
    v1->setUnits("dimensionless");
    v2->setUnits("dimensionless");
    v3->setUnits("dimensionless");

    c->addVariable(v1);
    c->addVariable(v2);
    c->addVariable(v3);
    c->setMath(math);
    m->addComponent(c);

    v.validateModel(m);
    EXPECT_EQ(expectedErrors.size(), v.errorCount());

    // Check for two expected error messages (see note above).
    for (size_t i = 0; i < v.errorCount(); ++i) {
        //std::cout << v.getError(i)->getDescription() + "\n";
        EXPECT_EQ(expectedErrors.at(i), v.getError(i)->getDescription());
    }
}

TEST(Validator, parseAndValidateInvalidUnitErrors) {
    const std::string input =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/1.2#\" name=\"asoiaf\">"
            "<units name=\"north\"/>"
            "<units name=\"stark\">"
                "<unit units=\"volt\"/>"
                "<unit units=\"north\"/>"
                "<unit units=\"ned\"/>"
                "<unit/>"
                "<unit prefix=\"wolf\" units=\"celsius\"/>"
                "<unit exponent=\"7.0\" offset=\"-32.0\" units=\"celsius\"/>"
            "</units>"
        "</model>";
    std::vector<std::string> expectedErrors = {
        "Units reference 'ned' in units 'stark' is not a valid reference to a local units or a standard unit type.",
        "Unit in units 'stark' does not have a units reference.",
        "Prefix 'wolf' of a unit referencing 'celsius' in units 'stark' is not a valid SI prefix.",
        "Unit referencing 'celsius' has an offset of '-32' and 5 sibling(s) in units 'stark'. A valid unit with a non-zero offset should have no siblings.",
        "Unit referencing 'celsius' has an offset of '-32' and an exponent of '7'. A valid unit with a non-zero offset should have no exponent or an exponent with a value of '1'."
    };

    libcellml::Parser p(libcellml::Format::XML);
    libcellml::ModelPtr m = p.parseModel(input);
    EXPECT_EQ(0, p.errorCount());

    libcellml::Validator v;
    v.validateModel(m);
    EXPECT_EQ(expectedErrors.size(), v.errorCount());

    // Check for two expected error messages (see note above).
    for (size_t i = 0; i < v.errorCount(); ++i) {
        //std::cout << v.getError(i)->getDescription() + "\n";
        EXPECT_EQ(expectedErrors.at(i), v.getError(i)->getDescription());
    }
}

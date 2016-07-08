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

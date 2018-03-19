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
    EXPECT_EQ("4.2.1", validator.getError(0)->getSpecificationHeading());
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
    model->addUnits(units);
    validator.validateModel(model);

    EXPECT_EQ(expectedErrors.size(), validator.errorCount());
    for (size_t i = 0; i < validator.errorCount(); ++i) {
        EXPECT_EQ(expectedErrors.at(i), validator.getError(i)->getDescription());
    }
}

TEST(Validator, modelWithDuplicateComponentsAndUnits) {
    std::vector<std::string> expectedErrors = {
        "Model 'multiplicity' contains multiple components with the name 'michael'. Valid component names must be unique to their model.",
        "Model 'multiplicity' contains multiple units with the name 'keaton'. Valid units names must be unique to their model."
    };

    libcellml::Validator validator;
    libcellml::ModelPtr model = std::make_shared<libcellml::Model>();
    libcellml::ComponentPtr c1 = std::make_shared<libcellml::Component>();
    libcellml::ComponentPtr c2 = std::make_shared<libcellml::Component>();
    libcellml::UnitsPtr u1 = std::make_shared<libcellml::Units>();
    libcellml::UnitsPtr u2 = std::make_shared<libcellml::Units>();
    model->addComponent(c1);
    model->addComponent(c2);
    model->addUnits(u1);
    model->addUnits(u2);

    model->setName("multiplicity");
    c1->setName("michael");
    c2->setName("michael");
    u1->setName("keaton");
    u2->setName("keaton");
    validator.validateModel(model);

    EXPECT_EQ(expectedErrors.size(), validator.errorCount());
    for (size_t i = 0; i < validator.errorCount(); ++i) {
        EXPECT_EQ(expectedErrors.at(i), validator.getError(i)->getDescription());
    }
}

TEST(Validator, unnamedAndDuplicateNamedVariablesWithAndWithoutValidUnits) {
    std::vector<std::string> expectedErrors = {
        "Component 'fargo' contains multiple variables with the name 'margie'. Valid variable names must be unique to their component.",
        "Variable does not have a valid name attribute.",
        "Variable 'margie' does not have a valid units attribute.",
        "Variable 'ransom' has an invalid units reference 'dollars' that does not correspond with a standard unit or units in the variable's parent component or model."
    };

    libcellml::Validator validator;
    libcellml::ModelPtr model = std::make_shared<libcellml::Model>();
    libcellml::ComponentPtr c1 = std::make_shared<libcellml::Component>();
    libcellml::VariablePtr v1 = std::make_shared<libcellml::Variable>();
    libcellml::VariablePtr v2 = std::make_shared<libcellml::Variable>();
    libcellml::VariablePtr v3 = std::make_shared<libcellml::Variable>();
    libcellml::VariablePtr v4 = std::make_shared<libcellml::Variable>();
    model->addComponent(c1);
    c1->addVariable(v1);
    c1->addVariable(v2);
    c1->addVariable(v3);
    c1->addVariable(v4);

    model->setName("minnesota");
    c1->setName("fargo");
    v1->setName("2cold");
    v1->setUnits("ampere");
    v2->setName("margie");
    v2->setUnits("ampere");
    v3->setName("margie");
    v4->setName("ransom");
    v4->setUnits("dollars");
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
        "Model 'model_name' contains multiple imported units from 'some-other-model.xml' with the same units_ref attribute 'units_in_that_model'.",
        "Imported units does not have a valid name attribute."

    };

    libcellml::Validator v;
    libcellml::ModelPtr m = std::make_shared<libcellml::Model>();
    m->setName("model_name");

    // Valid units import
    libcellml::ImportSourcePtr imp = std::make_shared<libcellml::ImportSource>();
    imp->setSource("some-other-model.xml");
    libcellml::UnitsPtr importedUnits = std::make_shared<libcellml::Units>();
    importedUnits->setName("valid_imported_units_in_this_model");
    importedUnits->setSourceUnits(imp, "units_in_that_model");
    m->addUnits(importedUnits);
    v.validateModel(m);
    EXPECT_EQ(0, v.errorCount());

    // Invalid units import- missing refs
    libcellml::ImportSourcePtr imp2 = std::make_shared<libcellml::ImportSource>();
    libcellml::UnitsPtr importedUnits2 = std::make_shared<libcellml::Units>();
    importedUnits2->setName("invalid_imported_units_in_this_model");
    importedUnits2->setSourceUnits(imp2, "");
    m->addUnits(importedUnits2);
    v.validateModel(m);
    EXPECT_EQ(2, v.errorCount());

    // Invalid units import - duplicate refs
    libcellml::ImportSourcePtr imp3 = std::make_shared<libcellml::ImportSource>();
    imp3->setSource("some-other-model.xml");
    libcellml::UnitsPtr importedUnits3 = std::make_shared<libcellml::Units>();
    importedUnits3->setName("duplicate_imported_units_in_this_model");
    importedUnits3->setSourceUnits(imp3, "units_in_that_model");
    m->addUnits(importedUnits3);
    v.validateModel(m);
    EXPECT_EQ(3, v.errorCount());

    // Invalid units import - unnamed units
    libcellml::ImportSourcePtr imp4 = std::make_shared<libcellml::ImportSource>();
    imp4->setSource("some-other-different-model.xml");
    libcellml::UnitsPtr importedUnits4 = std::make_shared<libcellml::Units>();
    importedUnits4->setSourceUnits(imp4, "units_in_that_model");
    m->addUnits(importedUnits4);
    v.validateModel(m);
    EXPECT_EQ(4, v.errorCount());

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
        "Model 'model_name' contains multiple imported components from 'some-other-model.xml' with the same component_ref attribute 'component_in_that_model'.",
        "Imported component does not have a valid name attribute."
    };

    libcellml::Validator v;
    libcellml::ModelPtr m = std::make_shared<libcellml::Model>();
    m->setName("model_name");

    // Valid component import
    libcellml::ImportSourcePtr imp = std::make_shared<libcellml::ImportSource>();
    imp->setSource("some-other-model.xml");
    libcellml::ComponentPtr importedComponent = std::make_shared<libcellml::Component>();
    importedComponent->setName("valid_imported_component_in_this_model");
    importedComponent->setSourceComponent(imp, "component_in_that_model");
    m->addComponent(importedComponent);
    v.validateModel(m);
    EXPECT_EQ(0, v.errorCount());

    // Invalid component import- missing refs
    libcellml::ImportSourcePtr imp2 = std::make_shared<libcellml::ImportSource>();
    libcellml::ComponentPtr importedComponent2 = std::make_shared<libcellml::Component>();
    importedComponent2->setName("invalid_imported_component_in_this_model");
    importedComponent2->setSourceComponent(imp2, "");
    m->addComponent(importedComponent2);
    v.validateModel(m);
    EXPECT_EQ(2, v.errorCount());

    // Invalid component import - duplicate refs
    libcellml::ImportSourcePtr imp3 = std::make_shared<libcellml::ImportSource>();
    imp3->setSource("some-other-model.xml");
    libcellml::ComponentPtr importedComponent3 = std::make_shared<libcellml::Component>();
    importedComponent3->setName("duplicate_imported_component_in_this_model");
    importedComponent3->setSourceComponent(imp3, "component_in_that_model");
    m->addComponent(importedComponent3);
    v.validateModel(m);
    EXPECT_EQ(3, v.errorCount());

    // Invalid component import - unnamed component
    libcellml::ImportSourcePtr imp4 = std::make_shared<libcellml::ImportSource>();
    imp4->setSource("some-other-different-model.xml");
    libcellml::ComponentPtr importedComponent4 = std::make_shared<libcellml::Component>();
    importedComponent4->setSourceComponent(imp4, "component_in_that_model");
    m->addComponent(importedComponent4);
    v.validateModel(m);
    EXPECT_EQ(4, v.errorCount());

    // Check for expected error messages
    for (size_t i = 0; i < v.errorCount(); ++i) {
        //std::cout << v.getError(i)->getDescription() + "\n";
        EXPECT_EQ(expectedErrors.at(i), v.getError(i)->getDescription());
    }
}

TEST(Validator, validMath) {
    std::string math =
            "<math xmlns=\"http://www.w3.org/1998/Math/MathML\">"
                "<apply>"
                    "<eq/>"
                    "<ci>C</ci>"
                    "<apply>"
                        "<plus/>"
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

TEST(Validator, invalidMath) {
    std::string math1 =
            "<math>"
                "<invalid_xml></not_valid>"
            "</math>";

    std::string math2 = "<invalid_math/>";

    std::vector<std::string> expectedErrors = {
        "Opening and ending tag mismatch: invalid_xml line 1 and not_valid.",
        "Could not get a valid XML root node from the math on component 'componentName1'.",
        "Math root node is of invalid type 'invalid_math' on component 'componentName2'. A valid math root node should be of type 'math'."
    };

    libcellml::Validator v;
    libcellml::ModelPtr m = std::make_shared<libcellml::Model>();
    libcellml::ComponentPtr c1 = std::make_shared<libcellml::Component>();
    libcellml::ComponentPtr c2 = std::make_shared<libcellml::Component>();

    m->setName("modelName");
    c1->setName("componentName1");
    c2->setName("componentName2");

    c1->setMath(math1);
    c2->setMath(math2);
    m->addComponent(c1);
    m->addComponent(c2);

    v.validateModel(m);
    EXPECT_EQ(expectedErrors.size(), v.errorCount());

    for (size_t i = 0; i < v.errorCount(); ++i) {
        //std::cout << v.getError(i)->getDescription() + "\n";
        EXPECT_EQ(expectedErrors.at(i), v.getError(i)->getDescription());
    }
}

TEST(Validator, invalidMathMLElements) {
    std::string math =
            "<math xmlns=\"http://www.w3.org/1998/Math/MathML\">"
                "<apply>"
                    "<equals/>"
                    "<ci>C</ci>"
                    "<apply>"
                        "<addition/>"
                        "<ci>A</ci>"
                        "<ci>B</ci>"
                    "</apply>"
                "</apply>"
            "</math>";

    std::vector<std::string> expectedErrors = {
        "No declaration for element equals.",
        "No declaration for element addition."
    };
    // NOTE: The MathML DTD also gives errors that list every possible operator when an
    //       invalid option is given. We'll just explicitly check the less verbose errors here.

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
                "<apply>"
                    "<eq/>"
                    "<ci>answer</ci>"
                    "<apply>"
                        "<plus/>"
                        "<ci>A</ci>"
                        "<apply>"
                            "<plus/>"
                            "<bvar>"
                            "<ci>new_bvar</ci>"
                            "</bvar>"
                            "<apply>"
                                "<plus/>"
                                "<ci>   </ci>"
                                "<apply>"
                                    "<plus/>"
                                    "<ci><nonsense/></ci>"
                                    "<apply>"
                                        "<plus/>"
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
        "Math in component 'componentName' contains 'B' as a bvar ci element but it is already a variable name.",
        "MathML ci element has the child text 'answer', which does not correspond with any variable names present in component 'componentName' and is not a variable defined within a bvar element.",
        "Math bvar ci element with the value 'new_bvar' does not have a valid cellml:units attribute.",
        "MathML ci element has a whitespace-only child element.",
        "MathML ci element has no child.",
        "Math bvar ci element with the value 'B' does not have a valid cellml:units attribute.",
        "No declaration for element nonsense.",
        "Element nonsense is not declared in ci list of possible children."
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

    // Check for expected error messages.
    for (size_t i = 0; i < v.errorCount(); ++i) {
        //std::cout << v.getError(i)->getDescription() + "\n";
        EXPECT_EQ(expectedErrors.at(i), v.getError(i)->getDescription());
    }
}

TEST(Validator, invalidMathMLCiAndCnElementsWithCellMLUnits) {
    std::string math =
            "<math xmlns:cellml=\"http://www.cellml.org/cellml/2.0#\" xmlns=\"http://www.w3.org/1998/Math/MathML\">"
                "<apply>"
                    "<eq/>"
                    "<cn cellml:units=\"invalid\">oops</cn>"
                    "<apply>"
                        "<plus/>"
                        "<ci>A</ci>"
                        "<apply>"
                            "<plus/>"
                            "<bvar>"
                            "<ci cellml:units=\"dimensionless\" cellml:value=\"zero\">new_bvar</ci>"
                            "</bvar>"
                            "<apply>"
                                "<plus/>"
                                "<ci>   </ci>"
                                "<apply>"
                                    "<plus/>"
                                    "<ci>undefined_variable</ci>"
                                    "<apply>"
                                        "<plus/>"
                                        "<ci/>"
                                        "<bvar>"
                                        "<ci>B</ci>"
                                        "</bvar>"
                                        "<apply>"
                                            "<plus/>"
                                            "<cn>2.0</cn>"
                                        "</apply>"
                                    "</apply>"
                                "</apply>"
                            "</apply>"
                        "</apply>"
                    "</apply>"
                "</apply>"
            "</math>";

    std::vector<std::string> expectedErrors = {
        "Math in component 'componentName' contains 'B' as a bvar ci element but it is already a variable name.",
        "MathML cn element has the value 'oops', which cannot be converted to a real number.",
        "Math has a cn element with a cellml:units attribute 'invalid' that is not a valid reference to units in component 'componentName' or a standard unit.",
        "Math ci element has an invalid attribute type 'value' in the cellml namespace.",
        "MathML ci element has a whitespace-only child element.",
        "MathML ci element has the child text 'undefined_variable', which does not correspond with any variable names present in component 'componentName' and is not a variable defined within a bvar element.",
        "MathML ci element has no child.",
        "Math bvar ci element with the value 'B' does not have a valid cellml:units attribute.",
        "Math cn element with the value '2.0' does not have a valid cellml:units attribute.",
        "Namespace prefix cellml for value on ci is not defined.",
        "No declaration for attribute cellml:value of element ci."
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

    // NOTE: We're not checking the exact message of the last error as older versions of
    //       libxml may not include the namespace in the error message.
    for (size_t i = 0; i < v.errorCount() - 1; ++i) {
        //std::cout << v.getError(i)->getDescription() + "\n";
        EXPECT_EQ(expectedErrors.at(i), v.getError(i)->getDescription());
    }
}

TEST(Validator, parseAndValidateInvalidUnitErrors) {
    const std::string input =
            "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
            "<model xmlns=\"http://www.cellml.org/cellml/2.0#\" name=\"asoiaf\">"
                "<units name=\"ampere\"/>"
                "<units name=\"north\"/>"
                "<units name=\"stark\">"
                    "<unit units=\"volt\" prefix=\"mega\" multiplier=\"1000.0\"/>"
                    "<unit units=\"north\"/>"
                    "<unit units=\"ned\"/>"
                    "<unit units=\"king in the north\"/>"
                    "<unit prefix=\"wolf\" units=\"celsius\"/>"
                "</units>"
            "</model>";

    std::vector<std::string> expectedErrors = {
        "Units is named 'ampere', which is a protected standard unit name.",
        "Units reference 'ned' in units 'stark' is not a valid reference to a local units or a standard unit type.",
        "Unit in units 'stark' does not have a valid units reference.",
        "Prefix 'wolf' of a unit referencing 'celsius' in units 'stark' is not a valid real number or a SI prefix.",
    };

    libcellml::Parser p;
    libcellml::ModelPtr m = p.parseModel(input);
    EXPECT_EQ(0, p.errorCount());

    libcellml::Validator v;
    v.validateModel(m);
    EXPECT_EQ(expectedErrors.size(), v.errorCount());

    for (size_t i = 0; i < v.errorCount(); ++i) {
        //std::cout << v.getError(i)->getDescription() + "\n";
        EXPECT_EQ(expectedErrors.at(i), v.getError(i)->getDescription());
    }
}

TEST(Validator, validateInvalidConnections) {
    std::vector<std::string> expectedErrors = {
        "Variable 'variable4' is an equivalent variable to 'variable1_1' but has no parent component.",
        "Variable 'variable2' has an equivalent variable 'variable1_2'  which does not reciprocally have 'variable2' set as an equivalent variable.",
    };

    libcellml::Validator v;
    libcellml::ModelPtr m = std::make_shared<libcellml::Model>();
    libcellml::ComponentPtr comp1 = std::make_shared<libcellml::Component>();
    libcellml::ComponentPtr comp2 = std::make_shared<libcellml::Component>();
    libcellml::ComponentPtr comp3 = std::make_shared<libcellml::Component>();
    libcellml::ComponentPtr comp4 = std::make_shared<libcellml::Component>();
    libcellml::VariablePtr v1_1 = std::make_shared<libcellml::Variable>();
    libcellml::VariablePtr v1_2 = std::make_shared<libcellml::Variable>();
    libcellml::VariablePtr v2 = std::make_shared<libcellml::Variable>();
    libcellml::VariablePtr v3 = std::make_shared<libcellml::Variable>();
    libcellml::VariablePtr v4 = std::make_shared<libcellml::Variable>();

    m->setName("modelName");
    comp1->setName("component1");
    comp2->setName("component2");
    comp3->setName("component3");
    comp4->setName("component4");
    v1_1->setName("variable1_1");
    v1_2->setName("variable1_2");
    v2->setName("variable2");
    v3->setName("variable3");
    v4->setName("variable4");

    v1_1->setUnits("dimensionless");
    v1_2->setUnits("dimensionless");
    v2->setUnits("dimensionless");
    v3->setUnits("dimensionless");
    v4->setUnits("dimensionless");

    comp1->addVariable(v1_1);
    comp1->addVariable(v1_2);
    comp2->addVariable(v2);
    comp3->addVariable(v3);
    comp4->addVariable(v4);
    m->addComponent(comp1);
    m->addComponent(comp2);
    m->addComponent(comp3);
    m->addComponent(comp4);

    // Valid connections.
    libcellml::Variable::addEquivalence(v1_1, v2);
    libcellml::Variable::addEquivalence(v1_2, v2);
    libcellml::Variable::addEquivalence(v1_1, v3);
    libcellml::Variable::addEquivalence(v1_1, v4);
    libcellml::Variable::addEquivalence(v2, v3);
    libcellml::Variable::addEquivalence(v1_1, v3);
    // Make v4 a variable without a parent component.
    comp4->removeVariable(v4);
    // Remove all connections on v1_2, leaving dangling reciprocal connections.
    v1_2->removeAllEquivalences();

    v.validateModel(m);
    EXPECT_EQ(expectedErrors.size(), v.errorCount());
    for (size_t i = 0; i < v.errorCount(); ++i) {
        //std::cout << v.getError(i)->getDescription() + "\n";
        EXPECT_EQ(expectedErrors.at(i), v.getError(i)->getDescription());
    }
}

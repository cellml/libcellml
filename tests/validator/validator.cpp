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

/*
 * The tests in this file are here to catch any branches of code that
 * are not picked up by the main tests testing the API of the library
 */

TEST(Validator, namedModel) {
    libcellml::Validator validator;
    libcellml::ModelPtr model = std::make_shared<libcellml::Model>();
    model->setName("awesomeName");
    validator.validateModel(model);
    EXPECT_EQ(0u, validator.errorCount());
}

TEST(Validator, unnamedModel) {
    std::string expectedError = "Model does not have a valid name attribute.";
    libcellml::Validator validator;
    libcellml::ModelPtr model = std::make_shared<libcellml::Model>();
    validator.validateModel(model);
    EXPECT_EQ(2u, validator.errorCount());
    EXPECT_EQ(expectedError, validator.getError(1)->getDescription());
    EXPECT_EQ("4.2.1", validator.getError(1)->getSpecificationHeading());
}

TEST(Validator, invalidCellMLIdentifiersWithSpecificationHeading) {
    std::vector<std::string> expectedErrors = {
        "CellML identifiers must not begin with a European numeric character [0-9].",
        "Model does not have a valid name attribute.",
        "CellML identifiers must not contain any characters other than [a-zA-Z0-9_].",
        "Component does not have a valid name attribute.",
        "CellML identifiers must contain one or more basic Latin alphabetic characters.",
        "Component does not have a valid name attribute.",
        "CellML identifiers must not contain any characters other than [a-zA-Z0-9_].",
        "Component does not have a valid name attribute.",
        "CellML identifiers must contain one or more basic Latin alphabetic characters.",
        "Component does not have a valid name attribute.",
    };
    std::vector<std::string> expectedSpecificationHeadings = {
        "3.1.4",
        "4.2.1",
        "3.1.2",
        "10.1.1",
        "3.1.3",
        "10.1.1",
        "3.1.2",
        "10.1.1",
        "3.1.3",
        "10.1.1",
    };

    libcellml::Validator v;
    libcellml::ModelPtr model = std::make_shared<libcellml::Model>();
    libcellml::ComponentPtr c1 = std::make_shared<libcellml::Component>();
    libcellml::ComponentPtr c2 = std::make_shared<libcellml::Component>();
    libcellml::ComponentPtr c3 = std::make_shared<libcellml::Component>();
    libcellml::ComponentPtr c4 = std::make_shared<libcellml::Component>();
    libcellml::ComponentPtr c5 = std::make_shared<libcellml::Component>();

    model->setName("9numbernine");
    c1->setName("try.this");
    c2->setName("");
    c3->setName("or this");
    c4->setName("nice_name");

    model->addComponent(c1);
    model->addComponent(c2);
    model->addComponent(c3);
    model->addComponent(c4);
    model->addComponent(c5);

    v.validateModel(model);

    EXPECT_EQ(10u, v.errorCount());
    for (size_t i = 0; i < v.errorCount(); ++i) {
        EXPECT_EQ(expectedErrors.at(i), v.getError(i)->getDescription());
        EXPECT_EQ(expectedSpecificationHeadings.at(i), v.getError(i)->getSpecificationHeading());
    }
}

TEST(Validator, moveCopyValidatorWithUnnamedModel) {
    libcellml::Validator v, vm;
    libcellml::ModelPtr model = std::make_shared<libcellml::Model>();
    v.validateModel(model);

    // Move
    vm = std::move(v);
    // Copy
    libcellml::Validator vc(vm);

    // Check that the model error is in the copy.
    EXPECT_EQ(libcellml::Error::Kind::MODEL, vc.getError(1)->getKind());
}

TEST(Validator, namedModelWithUnnamedComponent) {
    std::string expectedError = "Component does not have a valid name attribute.";
    libcellml::Validator validator;
    libcellml::ModelPtr model = std::make_shared<libcellml::Model>();
    libcellml::ComponentPtr component = std::make_shared<libcellml::Component>();
    model->setName("awesomeName");
    model->addComponent(component);
    validator.validateModel(model);
    EXPECT_EQ(2u, validator.errorCount());
    EXPECT_EQ(expectedError, validator.getError(1)->getDescription());
}

TEST(Validator, unnamedModelWithUnnamedComponentWithUnnamedUnits) {
    std::vector<std::string> expectedErrors = {
        "CellML identifiers must contain one or more basic Latin alphabetic characters.",
        "Model does not have a valid name attribute.",
        "CellML identifiers must contain one or more basic Latin alphabetic characters.",
        "Component does not have a valid name attribute.",
        "CellML identifiers must contain one or more basic Latin alphabetic characters.",
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
        "CellML identifiers must not begin with a European numeric character [0-9].",
        "Variable does not have a valid name attribute.",
        "CellML identifiers must contain one or more basic Latin alphabetic characters.",
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
        "CellML identifiers must contain one or more basic Latin alphabetic characters.",
        "Imported units 'invalid_imported_units_in_this_model' does not have a valid units_ref attribute.",
        "Import of units 'invalid_imported_units_in_this_model' does not have a valid locator xlink:href attribute.",
        "Model 'model_name' contains multiple imported units from 'some-other-model.xml' with the same units_ref attribute 'units_in_that_model'.",
        "CellML identifiers must contain one or more basic Latin alphabetic characters.",
        "Imported units does not have a valid name attribute."

    };

    libcellml::Validator v;
    libcellml::ModelPtr m = std::make_shared<libcellml::Model>();
    m->setName("model_name");

    // Valid units import
    libcellml::ImportSourcePtr imp = std::make_shared<libcellml::ImportSource>();
    imp->setUrl("some-other-model.xml");
    libcellml::UnitsPtr importedUnits = std::make_shared<libcellml::Units>();
    importedUnits->setName("valid_imported_units_in_this_model");
    importedUnits->setSourceUnits(imp, "units_in_that_model");
    m->addUnits(importedUnits);
    v.validateModel(m);
    EXPECT_EQ(0u, v.errorCount());

    // Invalid units import- missing refs
    libcellml::ImportSourcePtr imp2 = std::make_shared<libcellml::ImportSource>();
    libcellml::UnitsPtr importedUnits2 = std::make_shared<libcellml::Units>();
    importedUnits2->setName("invalid_imported_units_in_this_model");
    importedUnits2->setSourceUnits(imp2, "");
    m->addUnits(importedUnits2);
    v.validateModel(m);
    EXPECT_EQ(3u, v.errorCount());

    // Invalid units import - duplicate refs
    libcellml::ImportSourcePtr imp3 = std::make_shared<libcellml::ImportSource>();
    imp3->setUrl("some-other-model.xml");
    libcellml::UnitsPtr importedUnits3 = std::make_shared<libcellml::Units>();
    importedUnits3->setName("duplicate_imported_units_in_this_model");
    importedUnits3->setSourceUnits(imp3, "units_in_that_model");
    m->addUnits(importedUnits3);
    v.validateModel(m);
    EXPECT_EQ(4u, v.errorCount());

    // Invalid units import - unnamed units
    libcellml::ImportSourcePtr imp4 = std::make_shared<libcellml::ImportSource>();
    imp4->setUrl("some-other-different-model.xml");
    libcellml::UnitsPtr importedUnits4 = std::make_shared<libcellml::Units>();
    importedUnits4->setSourceUnits(imp4, "units_in_that_model");
    m->addUnits(importedUnits4);
    v.validateModel(m);
    EXPECT_EQ(6u, v.errorCount());

    // Check for expected error messages
    for (size_t i = 0; i < v.errorCount(); ++i) {
        EXPECT_EQ(expectedErrors.at(i), v.getError(i)->getDescription());
    }
}

TEST(Validator, importComponents) {
    std::vector<std::string> expectedErrors = {
        "CellML identifiers must contain one or more basic Latin alphabetic characters.",
        "Imported component 'invalid_imported_component_in_this_model' does not have a valid component_ref attribute.",
        "Import of component 'invalid_imported_component_in_this_model' does not have a valid locator xlink:href attribute.",
        "Model 'model_name' contains multiple imported components from 'some-other-model.xml' with the same component_ref attribute 'component_in_that_model'.",
        "CellML identifiers must contain one or more basic Latin alphabetic characters.",
        "Imported component does not have a valid name attribute."
    };

    libcellml::Validator v;
    libcellml::ModelPtr m = std::make_shared<libcellml::Model>();
    m->setName("model_name");

    // Valid component import
    libcellml::ImportSourcePtr imp = std::make_shared<libcellml::ImportSource>();
    imp->setUrl("some-other-model.xml");
    libcellml::ComponentPtr importedComponent = std::make_shared<libcellml::Component>();
    importedComponent->setName("valid_imported_component_in_this_model");
    importedComponent->setSourceComponent(imp, "component_in_that_model");
    m->addComponent(importedComponent);
    v.validateModel(m);
    EXPECT_EQ(0u, v.errorCount());

    // Invalid component import- missing refs
    libcellml::ImportSourcePtr imp2 = std::make_shared<libcellml::ImportSource>();
    libcellml::ComponentPtr importedComponent2 = std::make_shared<libcellml::Component>();
    importedComponent2->setName("invalid_imported_component_in_this_model");
    importedComponent2->setSourceComponent(imp2, "");
    m->addComponent(importedComponent2);
    v.validateModel(m);
    EXPECT_EQ(3u, v.errorCount());

    // Invalid component import - duplicate refs
    libcellml::ImportSourcePtr imp3 = std::make_shared<libcellml::ImportSource>();
    imp3->setUrl("some-other-model.xml");
    libcellml::ComponentPtr importedComponent3 = std::make_shared<libcellml::Component>();
    importedComponent3->setName("duplicate_imported_component_in_this_model");
    importedComponent3->setSourceComponent(imp3, "component_in_that_model");
    m->addComponent(importedComponent3);
    v.validateModel(m);
    EXPECT_EQ(4u, v.errorCount());

    // Invalid component import - unnamed component
    libcellml::ImportSourcePtr imp4 = std::make_shared<libcellml::ImportSource>();
    imp4->setUrl("some-other-different-model.xml");
    libcellml::ComponentPtr importedComponent4 = std::make_shared<libcellml::Component>();
    importedComponent4->setSourceComponent(imp4, "component_in_that_model");
    m->addComponent(importedComponent4);
    v.validateModel(m);
    EXPECT_EQ(6u, v.errorCount());

    // Check for expected error messages
    for (size_t i = 0; i < v.errorCount(); ++i) {
        EXPECT_EQ(expectedErrors.at(i), v.getError(i)->getDescription());
    }
}

TEST(Validator, validMath) {
    std::string math =
            "<math xmlns=\"http://www.w3.org/1998/Math/MathML\">"
                "<apply>"
                    "<eq/>"
                    "<ci> C </ci>"
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
    EXPECT_EQ(0u, v.errorCount());
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
        "Math has a 'equals' element that is not a supported MathML element.",
        "Math has a 'addition' element that is not a supported MathML element.",
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
    EXPECT_EQ(6u, v.errorCount());

    // Check for two expected error messages (see note above).
    for (size_t i = 0; i < 2; ++i) {
        EXPECT_EQ(expectedErrors.at(i), v.getError(i)->getDescription());
    }
}

TEST(Validator, invalidMathMLVariables) {
    std::string math =
            "<math xmlns=\"http://www.w3.org/1998/Math/MathML\">"
                "<apply>"
                    "<eq/>"
                    "<ci>answer</ci>"
                    "<partialdiff/>"
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
        "Math has a 'partialdiff' element that is not a supported MathML element.",
        "Math has a 'nonsense' element that is not a supported MathML element.",
        "Math in component 'componentName' contains 'B' as a bvar ci element but it is already a variable name.",
        "MathML ci element has the child text 'answer', which does not correspond with any variable names present in component 'componentName' and is not a variable defined within a bvar element.",
        "MathML ci element has a whitespace-only child element.",
        "MathML ci element has no child.",
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
                                        "<ci cellml:units=\"9wayswrong\">B</ci>"
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
        "Math has a cn element with a cellml:units attribute 'invalid' that is not a valid reference to units in component 'componentName' or a standard unit.",
        "Math ci element has an invalid attribute type 'value' in the cellml namespace.",
        "MathML ci element has a whitespace-only child element.",
        "MathML ci element has the child text 'undefined_variable', which does not correspond with any variable names present in component 'componentName' and is not a variable defined within a bvar element.",
        "MathML ci element has no child.",
        "CellML identifiers must contain one or more basic Latin alphabetic characters.",
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
        "CellML identifiers must not contain any characters other than [a-zA-Z0-9_].",
        "Unit in units 'stark' does not have a valid units reference.",
        "Prefix 'wolf' of a unit referencing 'celsius' in units 'stark' is not a valid real number or a SI prefix.",
    };

    libcellml::Parser p;
    libcellml::ModelPtr m = p.parseModel(input);
    EXPECT_EQ(0u, p.errorCount());

    libcellml::Validator v;
    v.validateModel(m);
    EXPECT_EQ(expectedErrors.size(), v.errorCount());

    for (size_t i = 0; i < v.errorCount(); ++i) {
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
        EXPECT_EQ(expectedErrors.at(i), v.getError(i)->getDescription());
    }
}

TEST(Validator, integerStrings) {
    const std::string input =
            "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
            "<model xmlns=\"http://www.cellml.org/cellml/2.0#\" name=\"asoiaf\">"
                "<component name=\"component\">"
                    "<variable name=\"variable\" units=\"dimensionless\"/>"
                    "<reset variable=\"variable\" order=\"1\">"
                        "<when order=\"200\">"
                            "<math xmlns=\"http://www.w3.org/1998/Math/MathML\">"
                            "</math>"
                            "<math xmlns=\"http://www.w3.org/1998/Math/MathML\">"
                            "</math>"
                        "</when>"
                    "</reset>"
                    "<reset variable=\"variable\" order=\"-1\">"
                        "<when order=\"200\">"
                            "<math xmlns=\"http://www.w3.org/1998/Math/MathML\">"
                            "</math>"
                            "<math xmlns=\"http://www.w3.org/1998/Math/MathML\">"
                            "</math>"
                        "</when>"
                    "</reset>"
                    "<reset variable=\"variable\" order=\"+1\">"
                        "<when order=\"200\">"
                            "<math xmlns=\"http://www.w3.org/1998/Math/MathML\">"
                            "</math>"
                            "<math xmlns=\"http://www.w3.org/1998/Math/MathML\">"
                            "</math>"
                        "</when>"
                    "</reset>"
                    "<reset variable=\"variable\" order=\"\">"
                        "<when order=\"200\">"
                            "<math xmlns=\"http://www.w3.org/1998/Math/MathML\">"
                            "</math>"
                            "<math xmlns=\"http://www.w3.org/1998/Math/MathML\">"
                            "</math>"
                        "</when>"
                    "</reset>"
                    "<reset variable=\"variable\" order=\"-\">"
                        "<when order=\"200\">"
                            "<math xmlns=\"http://www.w3.org/1998/Math/MathML\">"
                            "</math>"
                            "<math xmlns=\"http://www.w3.org/1998/Math/MathML\">"
                            "</math>"
                        "</when>"
                    "</reset>"
                    "<reset variable=\"variable\" order=\"odd\">"
                        "<when order=\"200\">"
                            "<math xmlns=\"http://www.w3.org/1998/Math/MathML\">"
                            "</math>"
                            "<math xmlns=\"http://www.w3.org/1998/Math/MathML\">"
                            "</math>"
                        "</when>"
                    "</reset>"
                "</component>"
            "</model>";

    std::vector<std::string> expectedErrors = {
        "Reset in component 'component' does not have an order set, referencing variable 'variable'.",
        "Reset in component 'component' does not have an order set, referencing variable 'variable'.",
        "Reset in component 'component' does not have an order set, referencing variable 'variable'.",
        "Reset in component 'component' does not have an order set, referencing variable 'variable'.",
    };

    libcellml::Parser p;
    libcellml::ModelPtr m = p.parseModel(input);
    //EXPECT_EQ(4u, p.errorCount()); // errors in validator instead of parser
    EXPECT_EQ(0u, p.errorCount());

    libcellml::Validator v;
    v.validateModel(m);
    EXPECT_EQ(expectedErrors.size(), v.errorCount());
    for (size_t i = 0; i < expectedErrors.size(); ++i) {
        EXPECT_EQ(expectedErrors.at(i), v.getError(i)->getDescription());
    }
}

TEST(Validator, resets) {

    std::vector<std::string> expectedErrors = {
        "Component 'comp' contains multiple resets with order '300'.",
        "Reset in component 'comp' with order '300' does not reference a variable.",
        "Reset in component 'comp' does not have an order set, does not reference a variable.",
        "Reset in component 'comp' does not have an order set, does not reference a variable.",
        "Reset in component 'comp' with order '500' referencing variable 'var' does not have at least one child When.",
        "Reset in component 'comp' does not have an order set, referencing variable 'var'.",
        "Reset in component 'comp' does not have an order set, referencing variable 'var' does not have at least one child When.",
        "Reset in component 'comp' does not have an order set, does not reference a variable.",
        "Reset in component 'comp' does not have an order set, does not reference a variable.",
        "Reset in component 'comp' does not have an order set, does not reference a variable, does not have at least one child When.",
    };

    libcellml::ModelPtr m = std::make_shared<libcellml::Model>();
    libcellml::ComponentPtr c = std::make_shared<libcellml::Component>();
    libcellml::VariablePtr var = std::make_shared<libcellml::Variable>();
    libcellml::ResetPtr r1 = std::make_shared<libcellml::Reset>();
    libcellml::ResetPtr r2 = std::make_shared<libcellml::Reset>();
    libcellml::ResetPtr r3 = std::make_shared<libcellml::Reset>();
    libcellml::ResetPtr r4 = std::make_shared<libcellml::Reset>();
    libcellml::ResetPtr r5 = std::make_shared<libcellml::Reset>();
    libcellml::ResetPtr r6 = std::make_shared<libcellml::Reset>();
    libcellml::ResetPtr r7 = std::make_shared<libcellml::Reset>();
    libcellml::WhenPtr w1 = std::make_shared<libcellml::When>();
    libcellml::WhenPtr w2 = std::make_shared<libcellml::When>();

    w1->setOrder(776);
    w1->setCondition("<math xmlns=\"http://www.w3.org/1998/Math/MathML\"></math>");
    w1->setValue("<math xmlns=\"http://www.w3.org/1998/Math/MathML\"></math>");
    w2->setOrder(345);
    w2->setCondition("<math xmlns=\"http://www.w3.org/1998/Math/MathML\"></math>");
    w2->setValue("<math xmlns=\"http://www.w3.org/1998/Math/MathML\"></math>");

    r1->setOrder(300);
    r1->addWhen(w1);
    r6->addWhen(w1);
    r2->setOrder(300);
    r2->addWhen(w1);
    r2->addWhen(w2);
    r2->setVariable(var);
    r3->setOrder(400);
    r3->addWhen(w2);
    r3->setVariable(var);
    r4->setVariable(var);
    r4->setOrder(500);
    r5->setVariable(var);

    c->setName("comp");
    var->setName("var");
    var->setUnits("second");

    c->addVariable(var);
    c->addReset(r1);
    c->addReset(r6);
    c->addReset(r2);
    c->addReset(r3);
    c->addReset(r4);
    c->addReset(r5);
    c->addReset(r7);

    m->setName("main");
    m->addComponent(c);

    libcellml::Validator v;
    v.validateModel(m);

    EXPECT_EQ(expectedErrors.size(), v.errorCount());
    for (size_t i = 0; i < expectedErrors.size(); ++i) {
        EXPECT_EQ(expectedErrors.at(i), v.getError(i)->getDescription());
    }
}

TEST(Validator, whens) {
    std::vector<std::string> expectedErrors {
        "Reset in component 'comp' with order '300' does not reference a variable.",
        "When in reset with order '300' which does not reference a variable, does not have an order set.",
        "When in reset with order '300' which does not reference a variable, does not have an order set, does not have a MathML condition set.",
        "When in reset with order '300' which does not reference a variable, does not have an order set, does not have a MathML value set.",
        "Reset in component 'comp' does not have an order set, referencing variable 'var'.",
        "Reset in component 'comp' does not have an order set, referencing variable 'var' has multiple whens with order '250'.",
        "When in reset which does not have an order set, referencing variable 'var' with order '250' does not have a MathML value set.",
        "When in reset which does not have an order set, referencing variable 'var' with order '250' does not have a MathML condition set.",
    };

    libcellml::ModelPtr m = std::make_shared<libcellml::Model>();
    libcellml::ComponentPtr c = std::make_shared<libcellml::Component>();
    libcellml::VariablePtr var = std::make_shared<libcellml::Variable>();
    libcellml::ResetPtr r1 = std::make_shared<libcellml::Reset>();
    libcellml::ResetPtr r2 = std::make_shared<libcellml::Reset>();
    libcellml::ResetPtr r3 = std::make_shared<libcellml::Reset>();
    libcellml::WhenPtr w1 = std::make_shared<libcellml::When>();
    libcellml::WhenPtr w2 = std::make_shared<libcellml::When>();
    libcellml::WhenPtr w3 = std::make_shared<libcellml::When>();
    libcellml::WhenPtr w4 = std::make_shared<libcellml::When>();

    r1->setOrder(300);
    r1->addWhen(w1);
    //r2->setOrder(400);
    r2->addWhen(w2);
    r2->addWhen(w3);
    r3->setOrder(500);
    r3->addWhen(w4);
    // r1->setVariable(var);
    r2->setVariable(var);
    r3->setVariable(var);

    c->setName("comp");
    var->setName("var");
    var->setUnits("second");

    w2->setOrder(250);
    w2->setCondition("<math xmlns=\"http://www.w3.org/1998/Math/MathML\"></math>");
    w3->setOrder(250);
    w3->setValue("<math xmlns=\"http://www.w3.org/1998/Math/MathML\"></math>");
    w4->setOrder(365);
    w4->setCondition("<math xmlns=\"http://www.w3.org/1998/Math/MathML\"></math>");
    w4->setValue("<math xmlns=\"http://www.w3.org/1998/Math/MathML\"></math>");

    c->addVariable(var);
    c->addReset(r1);
    c->addReset(r2);
    c->addReset(r3);

    m->setName("main");
    m->addComponent(c);

    libcellml::Validator v;
    v.validateModel(m);

    EXPECT_EQ(expectedErrors.size(), v.errorCount());
    for (size_t i = 0; i < expectedErrors.size(); ++i) {
        EXPECT_EQ(expectedErrors.at(i), v.getError(i)->getDescription());
    }
}

TEST(Validator, validMathCnElements) {
    std::string math =
            "<math xmlns:cellml=\"http://www.cellml.org/cellml/2.0#\" xmlns=\"http://www.w3.org/1998/Math/MathML\">"
                "<apply>"
                    "<eq/>"
                    "<ci>C</ci>"
                    "<apply>"
                        "<plus/>"
                        "<cn cellml:units=\"dimensionless\">3.44<sep/>2</cn>"
                        "<cn cellml:units=\"dimensionless\">-9.612</cn>"
                    "</apply>"
                "</apply>"
            "</math>";

    libcellml::Validator v;
    libcellml::ModelPtr m = std::make_shared<libcellml::Model>();
    libcellml::ComponentPtr c = std::make_shared<libcellml::Component>();
    libcellml::VariablePtr v1 = std::make_shared<libcellml::Variable>();

    m->setName("modelName");
    c->setName("componentName");
    v1->setName("C");
    v1->setInitialValue("3.5");
    v1->setUnits("dimensionless");

    c->addVariable(v1);
    c->setMath(math);
    m->addComponent(c);

    v.validateModel(m);
    EXPECT_EQ(0u, v.errorCount());
}

TEST(Validator, importDuplicateInfoset) {
	/// @cellml2_5 5.1.3 __TODO?__ Validate TEST Check for semantic equivalence between parent and child infoset: you cannot import yourself
}

TEST(Validator, variableEquivalentUnits) {
	/// @cellml2_19 19.10.6 Validate TEST Check unit reduction is the same for equivalent variables
	
	/*std::vector<std::string> expectedErrors = {
		"Variable 'potayto' has units of 'testunit3' and an equivalent variable 'tomahto' with non-matching units of 'testunit2'. The mismatch is: kilogram^1.000000, metre^-2.000000, second^-2.000000, ",
		"Variable 'tomahto' has units of 'testunit2' and an equivalent variable 'potayto' with non-matching units of 'testunit3'. The mismatch is: kilogram^-1.000000, metre^2.000000, second^2.000000, ",
		"Variable 'pjs' has units of 'testunit13' and an equivalent variable 'pajamas' with non-matching units of 'testunit14'. The mismatch is: metre^1.000000, ",
		"Variable 'pajamas' has units of 'testunit14' and an equivalent variable 'pjs' with non-matching units of 'testunit13'. The mismatch is: metre^-1.000000, "
	};*/
    std::vector<std::string> expectedErrors = {

        "Variable 'potayto' has units of 'testunit3' and an equivalent variable 'tomahto' with non-matching units of 'testunit2'. ERROR: Unit mismatch in kilogram^1.000000, ERROR: Unit mismatch in metre^-2.000000, ERROR: Unit mismatch in second^-2.000000, ",
        "Variable 'oncle' has units of 'testunit12' and an equivalent variable 'oom' with non-matching units of 'testunit10'. WARNING: Multiplier mismatch in kilogram(0.001000), ",
        "Variable 'tomahto' has units of 'testunit2' and an equivalent variable 'potayto' with non-matching units of 'testunit3'. ERROR: Unit mismatch in kilogram^-1.000000, ERROR: Unit mismatch in metre^2.000000, ERROR: Unit mismatch in second^2.000000, ",
        "Variable 'oom' has units of 'testunit10' and an equivalent variable 'uncle' with non-matching units of 'testunit11'. WARNING: Multiplier mismatch in kilogram(1000.000000), ",
        "Variable 'oom' has units of 'testunit10' and an equivalent variable 'oncle' with non-matching units of 'testunit12'. WARNING: Multiplier mismatch in kilogram(1000.000000), ",
        "Variable 'pjs' has units of 'testunit13' and an equivalent variable 'pajamas' with non-matching units of 'testunit14'. ERROR: Unit mismatch in metre^1.000000, ",
        "Variable 'uncle' has units of 'testunit11' and an equivalent variable 'oom' with non-matching units of 'testunit10'. WARNING: Multiplier mismatch in kilogram(0.001000), ",
        "Variable 'pajamas' has units of 'testunit14' and an equivalent variable 'pjs' with non-matching units of 'testunit13'. ERROR: Unit mismatch in metre^-1.000000, ",
    };

	libcellml::Validator validator;
	libcellml::ModelPtr m = std::make_shared<libcellml::Model>();
	libcellml::ComponentPtr comp1 = std::make_shared<libcellml::Component>();
	libcellml::ComponentPtr comp2 = std::make_shared<libcellml::Component>();
	libcellml::ComponentPtr comp3 = std::make_shared<libcellml::Component>();

	libcellml::VariablePtr v1 = std::make_shared<libcellml::Variable>();
	libcellml::VariablePtr v2 = std::make_shared<libcellml::Variable>();
	libcellml::VariablePtr v3 = std::make_shared<libcellml::Variable>();
	libcellml::VariablePtr v4 = std::make_shared<libcellml::Variable>();
	libcellml::VariablePtr v5 = std::make_shared<libcellml::Variable>();
	libcellml::VariablePtr v6 = std::make_shared<libcellml::Variable>();
	libcellml::VariablePtr v7 = std::make_shared<libcellml::Variable>();
	libcellml::VariablePtr v8 = std::make_shared<libcellml::Variable>();
	libcellml::VariablePtr v9 = std::make_shared<libcellml::Variable>();

	libcellml::VariablePtr v10 = std::make_shared<libcellml::Variable>();
	libcellml::VariablePtr v11 = std::make_shared<libcellml::Variable>();
	libcellml::VariablePtr v12 = std::make_shared<libcellml::Variable>();

	libcellml::VariablePtr v13 = std::make_shared<libcellml::Variable>();
	libcellml::VariablePtr v14 = std::make_shared<libcellml::Variable>();

    v1->setName("tomayto");
    v2->setName("tomahto");
    v3->setName("potayto");
    v4->setName("potahto");
    v5->setName("aunty");
    v6->setName("tante");
    v7->setName("auntie");

    v8->setName("neether");
    v9->setName("nyther");

    v10->setName("oom");
    v11->setName("uncle");
    v12->setName("oncle");

    v13->setName("pjs");
    v14->setName("pajamas");

    comp1->setName("isay");
    comp2->setName("yousay");
    comp3->setName("wesay");

    m->setName("callthewholethingoff");

	comp1->addVariable(v1);
	comp2->addVariable(v2);
	comp1->addVariable(v3);
	comp2->addVariable(v4);

	comp1->addVariable(v5);
	comp2->addVariable(v6);
	comp3->addVariable(v7);

	comp2->addVariable(v8);
	comp3->addVariable(v9);

	comp2->addVariable(v10);
	comp3->addVariable(v11);

	comp1->addVariable(v12);
	comp2->addVariable(v13);
	comp3->addVariable(v14);

	m->addComponent(comp1);
	m->addComponent(comp2);
	m->addComponent(comp3);

	
	libcellml::UnitsPtr u1 = std::make_shared<libcellml::Units>();
	u1->setName("testunit1");
	u1->addUnit("metre");

	libcellml::UnitsPtr u2 = std::make_shared<libcellml::Units>();
	u2->setName("testunit2");
	u2->addUnit("meter");

	libcellml::UnitsPtr u3 = std::make_shared<libcellml::Units>();
	u3->setName("testunit3");
	u3->addUnit("pascal");

	libcellml::UnitsPtr u4 = std::make_shared<libcellml::Units>();
	u4->setName("testunit4");
	u4->addUnit("metre", 1, -1.0, 1.0); // prefix, exp, mult
	u4->addUnit("kilogram", 1, 1.0, 1.0);
	u4->addUnit("second", 1, -2.0, 1.0);

	libcellml::UnitsPtr u5 = std::make_shared<libcellml::Units>();
	u5->setName("testunit5");
	u5->addUnit("metre", 1, -2.0, 1.0);
	u5->addUnit("meter", 1, 2.0, 1.0);

	libcellml::UnitsPtr u6 = std::make_shared<libcellml::Units>();
	u6->setName("testunit6");
	u6->addUnit("dimensionless");

	libcellml::UnitsPtr u7 = std::make_shared<libcellml::Units>();
	u7->setName("testunit7");
	u7->addUnit("steradian");

	libcellml::UnitsPtr u8 = std::make_shared<libcellml::Units>();
	u8->setName("testunit8");
	u8->addUnit("newton", 1, 1, 1);
	u8->addUnit("pascal", 1, -1, 1);
	u8->addUnit("sievert", 1, -1, 1);

	libcellml::UnitsPtr u9 = std::make_shared<libcellml::Units>();
	u9->setName("testunit9");
	u9->addUnit("second", 1, 2, 1);
	u9->addUnit("radian", 1, -4, 1);
	u9->addUnit("steradian", 1, 2, 1);

	libcellml::UnitsPtr u10 = std::make_shared<libcellml::Units>();
	u10->setName("testunit10");
	u10->addUnit("metre", "kilo", 2, 1.0);
    //u10->addUnit("kilogram",0,2,10.0);

	libcellml::UnitsPtr u11 = std::make_shared<libcellml::Units>();
	u11->setName("testunit11");
	u11->addUnit("metre",0,2,1.0);

	libcellml::UnitsPtr u12 = std::make_shared<libcellml::Units>();
	u12->setName("testunit12");
	u12->addUnit("gram", "mega", 1.0, 1.0);

	libcellml::UnitsPtr u13 = std::make_shared<libcellml::Units>();
	u13->setName("testunit13");
	u13->addUnit("testunit2", 1, 2.0, 1.0);
	u13->addUnit("testunit8", 1, 2.0, 1.0);

	libcellml::UnitsPtr u14 = std::make_shared<libcellml::Units>();
	u14->setName("testunit14");
	u14->addUnit("testunit1", 1, 1.0, 1.0);
	u14->addUnit("testunit9", 1, 2.0, 1.0);

	v1->setUnits(u1);
	v2->setUnits(u2);
	v3->setUnits(u3);
	v4->setUnits(u4);
	v5->setUnits(u5);
	v6->setUnits(u6);
	v7->setUnits(u7);
	v8->setUnits(u8);
	v9->setUnits(u9);
	v10->setUnits(u10);
	v11->setUnits(u11);
	v12->setUnits(u12);
	v13->setUnits(u13);
	v14->setUnits(u14);

	m->addUnits(u1);
	m->addUnits(u2);
	m->addUnits(u3);
	m->addUnits(u4);
	m->addUnits(u5);
	m->addUnits(u6);
	m->addUnits(u7);
	m->addUnits(u8);
	m->addUnits(u9);
	m->addUnits(u10);
	m->addUnits(u11);
	m->addUnits(u12);
	m->addUnits(u13);
	m->addUnits(u14);

	//// This one is fine : metre vs meter
	//libcellml::Variable::addEquivalence(v1, v2);

	//// This one is NOT fine: metre vs pascal
	//libcellml::Variable::addEquivalence(v2, v3);

	//// This one is fine: pascal vs kg/(m.s^2)
	//libcellml::Variable::addEquivalence(v3, v4);

	//// This one is fine: m^2/m^2 vs dimensionless
	//libcellml::Variable::addEquivalence(v5, v6);
	//
	//// This one is fine: dimensionless vs steradians
	//libcellml::Variable::addEquivalence(v6, v7);

	//// This one is fine but complicated: newton/(siever.pascal) = second^2.radian^3.steradian^-4
	//libcellml::Variable::addEquivalence(v8, v9);	

	//// Fine: testing the multipliers 1000*grams = 1*kilograms 
	//libcellml::Variable::addEquivalence(v10, v11);

	//// Not fine: testing prefix mega*gram != kilogram
	//libcellml::Variable::addEquivalence(v10, v12); 

	//// Off by (meter)^1: super-complicated nested units
	//libcellml::Variable::addEquivalence(v13, v14);

    libcellml::Variable::addEquivalence(v10, v11);

	validator.validateModel(m);
	
    //EXPECT_EQ(8u, validator.errorCount());

	// Check for expected error messages
	for (size_t i = 0; i < validator.errorCount(); ++i) {
        std::cout << validator.getError(i)->getDescription() << std::endl;
		//EXPECT_EQ(expectedErrors.at(i), validator.getError(i)->getDescription());
	}
}

TEST(Validator, emptyEncapsulation) {

    const std::string ex =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/2.0#\" name=\"model_name\">"
        "<encapsulation/>"
        "</model>";

    const std::string expectedError = "Encapsulation in model 'model_name' does not contain any child elements.";

    libcellml::Parser p;
    libcellml::ModelPtr model = p.parseModel(ex);
    libcellml::Validator v;
    // Parser returns error for empty encapsulation - validator needs to do that too
    v.validateModel(model);

}

TEST(Validator, encapuslationWithNoComponentAttribute) {
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
    libcellml::ModelPtr m = p.parseModel(ex);
    libcellml::Validator v;

    v.validateModel(m);
    printErrors(v);

    // KRM TODO 
    EXPECT_EQ(2u, p.errorCount());
    EXPECT_EQ(expectedError1, p.getError(0)->getDescription());
    EXPECT_EQ(expectedError2, p.getError(1)->getDescription());
}
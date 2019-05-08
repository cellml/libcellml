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

#include "test_resources.h"
#include "test_utils.h"

#include "gtest/gtest.h"

#include <fstream>
#include <libcellml>

/*
 * The tests in this file are here to catch any branches of code that
 * are not picked up by the main tests testing the API of the library
 */

TEST(Validator, namedModel) {
    /// @cellml2_4 4.2.1 Validate TEST model name format
    libcellml::Validator validator;
    libcellml::ModelPtr model = std::make_shared<libcellml::Model>();
    model->setName("awesomeName");
    validator.validateModel(model);
    EXPECT_EQ(0u, validator.errorCount());
}

TEST(Validator, unnamedModel) {
    /// @cellml2_4 4.2.1 Validate TEST mode name format
    std::string expectedError = "Model does not have a valid name attribute.";
    libcellml::Validator validator;
    libcellml::ModelPtr model = std::make_shared<libcellml::Model>();
    validator.validateModel(model);
    EXPECT_EQ(2u, validator.errorCount());
    EXPECT_EQ(expectedError, validator.getError(1)->getDescription());
    EXPECT_EQ("4.2.1", validator.getError(1)->getSpecificationHeading());
}

TEST(Validator, invalidCellMLIdentifiersWithSpecificationHeading) {
    /// @cellml2_10 10.1.1 Validate TEST component name format
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
    /// @cellml2_10 10.1.1 Validate TEST component name is not empty
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
    /// @cellml2_4 4.2.1 Validate TEST unnamed model with unnamed units
    /// @cellml2_8 8.1.1 Validate TEST unnamed units in model
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
    /// @cellml2_8 8.1.2 Validate TEST Valid units names must be unique to the model
    /// @cellml2_10 10.1.1 Validate TEST Valid names must be unique to the model
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

TEST(Validator, unitsWithPrefixOutOfRange) {
    // int limit is 18,446,744,073,709,551,615

    libcellml::Validator validator;
    libcellml::ModelPtr m = std::make_shared<libcellml::Model>();
    m->setName("myModel");
    libcellml::ComponentPtr c = std::make_shared<libcellml::Component>();
    c->setName("myComponent");
    libcellml::VariablePtr v = std::make_shared<libcellml::Variable>();
    v->setName("myVariable");
    libcellml::UnitsPtr u = std::make_shared<libcellml::Units>();

    u->setName("myUnits");
    u->addUnit("second", "18446744073709551616");

    v->setUnits(u);
    c->addVariable(v);
    m->addComponent(c);
    m->addUnits(u);

    validator.validateModel(m);
    
    EXPECT_EQ(1u, validator.errorCount());
    EXPECT_EQ("Prefix '18446744073709551616' of a unit referencing 'second' in units 'myUnits' is out of the integer range.",
              validator.getError(0)->getDescription());
}

TEST(Validator, unnamedAndDuplicateNamedVariablesWithAndWithoutValidUnits) {
    /// @cellml2_11 11.1.1.1 Validate TEST variable names must be unique to their component
    /// @cellml2_11 11.1.1.1 Validate TEST variable name must be valid
    /// @cellml2_8 8.1.1 Validate TEST units name must be valid
    /// @cellml2_11 11.1.1.2 Validate TEST variable units name is a valid reference  
    /// @cellml2_19 19.7.1 Validate TEST variable units name is a valid reference

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
    /// @cellml2_11 11.1.2.1 Validate TEST variable interface value is valid
    /// @cellml2_11 11.1.2.2 Validate TEST initial_value attrbute is real number string or variable reference
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
    /// @cellml2_6 6.1.2 Validate TEST import units has valid units_ref attribute
    /// @cellml2_6 6.1.1 Validate TEST import units have a valid name
    /// @cellml2_6 6.1.2 Validate TEST import units have a units_ref unique to this model
    /// @cellml2_6 6.1.1 Validate TEST import units has a name unique in this model
    /// @cellml2_5 5.1.1 Validate TEST import element has a valid href formatted attribute TODO This is very restrictive at present, check ...
    
    std::vector<std::string> expectedErrors = {
        "CellML identifiers must contain one or more basic Latin alphabetic characters.",
        "Imported units 'invalid_imported_units_in_this_model' does not have a valid units_ref attribute.",
        "Import of units 'invalid_imported_units_in_this_model' does not have a valid locator xlink:href attribute.",
        "Import of units 'name_for_invalid_import' has an invalid URI in the href attribute, 'not @ valid url'. ",
        "Model 'model_name' contains multiple units with the name 'units_to_be_duplicated'. Valid units names must be unique to their model.",
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
    EXPECT_EQ(3u, v.errorCount());

    // Invalid units import - unnamed units
    libcellml::ImportSourcePtr imp4 = std::make_shared<libcellml::ImportSource>();
    imp4->setUrl("some-other-different-model.xml");
    libcellml::UnitsPtr importedUnits4 = std::make_shared<libcellml::Units>();
    importedUnits4->setSourceUnits(imp4, "units_in_that_model");
    m->addUnits(importedUnits4);
    v.validateModel(m); 
    EXPECT_EQ(5u, v.errorCount());

    // Invalid html ref 
    libcellml::ImportSourcePtr imp5 = std::make_shared<libcellml::ImportSource>();
    imp5->setUrl("not @ valid url");
    libcellml::UnitsPtr importedUnits5 = std::make_shared<libcellml::Units>();
    importedUnits5->setName("name_for_invalid_import");
    importedUnits5->setSourceUnits(imp5, "units_in_that_model");
    m->addUnits(importedUnits5);
    v.validateModel(m); 
    EXPECT_EQ(6u, v.errorCount());

    // Duplicated units name
    libcellml::UnitsPtr manualUnits1 = std::make_shared<libcellml::Units>();
    manualUnits1->setName("units_to_be_duplicated");
    manualUnits1->addUnit("dimensionless");

    libcellml::UnitsPtr manualUnits2 = std::make_shared<libcellml::Units>();
    manualUnits2->setName("units_to_be_duplicated");
    manualUnits1->addUnit("dimensionless");

    m->addUnits(manualUnits1);
    m->addUnits(manualUnits2);

    v.validateModel(m); 
    EXPECT_EQ(7u, v.errorCount());

    // Check for expected error messages
    for (size_t i = 0; i < v.errorCount(); ++i) {
        EXPECT_EQ(expectedErrors.at(i), v.getError(i)->getDescription());
    }
}

TEST(Validator, importComponents) {
    /// @cellml2_7 7.1.1 Validate TEST import component must have valid name format
    /// @cellml2_7 7.1.2 Validate TEST import component must have unique component_ref
    /// @cellml2_7 7.1.1 Validate TEST import component must have unique name
    /// @cellml2_5 5.1.1 Validate TEST import has valid href attribute
    
    std::vector<std::string> expectedErrors = {
        "CellML identifiers must contain one or more basic Latin alphabetic characters.",
        "Imported component 'invalid_imported_component_in_this_model' does not have a valid component_ref attribute.",
        "Import of component 'invalid_imported_component_in_this_model' does not have a valid locator xlink:href attribute.",
        "CellML identifiers must contain one or more basic Latin alphabetic characters.",
        "Imported component does not have a valid name attribute.",
        "Import of component 'a_bad_imported_component' has an invalid URI in the href attribute, 'not @ valid url'. ",
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

    // Another valid component import 
    libcellml::ImportSourcePtr imp5 = std::make_shared<libcellml::ImportSource>();
    imp5->setUrl("yet-another-other-model.xml");
    libcellml::ComponentPtr importedComponent5 = std::make_shared<libcellml::Component>();
    importedComponent5->setName("another_valid_imported_component_in_this_model");
    importedComponent5->setSourceComponent(imp5, "new_shiny_component_ref");
    m->addComponent(importedComponent5);
    v.validateModel(m); 
    EXPECT_EQ(0u, v.errorCount());

    // Invalid component import - missing refs
    libcellml::ImportSourcePtr imp2 = std::make_shared<libcellml::ImportSource>();
    libcellml::ComponentPtr importedComponent2 = std::make_shared<libcellml::Component>();
    importedComponent2->setName("invalid_imported_component_in_this_model");
    importedComponent2->setSourceComponent(imp2, "");
    m->addComponent(importedComponent2);
    v.validateModel(m); 
    EXPECT_EQ(3u, v.errorCount());

    // Invalid component import - duplicate refs  TODO but is this allowed after all ?? #280, #298
    libcellml::ImportSourcePtr imp3 = std::make_shared<libcellml::ImportSource>();
    imp3->setUrl("some-other-model.xml");
    libcellml::ComponentPtr importedComponent3 = std::make_shared<libcellml::Component>();
    importedComponent3->setName("duplicate_imported_component_in_this_model");
    importedComponent3->setSourceComponent(imp3, "component_in_that_model");
    m->addComponent(importedComponent3);
    v.validateModel(m); 
    EXPECT_EQ(3u, v.errorCount());

    libcellml::ImportSourcePtr imp4 = std::make_shared<libcellml::ImportSource>();
    imp4->setUrl("some-other-different-model.xml");
    libcellml::ComponentPtr importedComponent4 = std::make_shared<libcellml::Component>();
    importedComponent4->setSourceComponent(imp4, "component_in_that_model");
    m->addComponent(importedComponent4);
    v.validateModel(m); 
    EXPECT_EQ(5u, v.errorCount());
    
    // Invalid: duplicating component_ref and source TODO but is this allowed after all ?? #280, #298
    libcellml::ImportSourcePtr imp6 = std::make_shared<libcellml::ImportSource>();
    imp6->setUrl("yet-another-other-model.xml");
    libcellml::ComponentPtr importedComponent6 = std::make_shared<libcellml::Component>();
    importedComponent6->setName("another_duplicate_imported_component");
    importedComponent6->setSourceComponent(imp6, "new_shiny_component_ref");
    m->addComponent(importedComponent6);
    v.validateModel(m); 
    EXPECT_EQ(5u, v.errorCount());

    // Valid: duplicate component_ref from a different source
    libcellml::ImportSourcePtr imp7 = std::make_shared<libcellml::ImportSource>();
    imp7->setUrl("yet-another-other-model.xml"); // source used before
    libcellml::ComponentPtr importedComponent7 = std::make_shared<libcellml::Component>();
    importedComponent7->setName("a_good_imported_component");
    importedComponent7->setSourceComponent(imp7, "component_in_that_model");
    m->addComponent(importedComponent7);
    v.validateModel(m); 
    EXPECT_EQ(5u, v.errorCount());

    // Invalid: component_ref is not valid html
    libcellml::ImportSourcePtr imp8 = std::make_shared<libcellml::ImportSource>();
    imp8->setUrl("not @ valid url"); // source used before
    libcellml::ComponentPtr importedComponent8 = std::make_shared<libcellml::Component>();
    importedComponent8->setName("a_bad_imported_component");
    importedComponent8->setSourceComponent(imp8, "component_in_some_model");
    m->addComponent(importedComponent8);
    v.validateModel(m); 
    EXPECT_EQ(6u, v.errorCount());
 
    // Check for expected error messages
    for (size_t i = 0; i < v.errorCount(); ++i) {
        EXPECT_EQ(expectedErrors.at(i), v.getError(i)->getDescription());
    }
}

TEST(Validator, validMath) {
    /// @cellml2_14 14.1 Validate TEST valid maths input works
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
    /// @cellml2_14 14.1.2 Validate TEST mismatch opening and closing tags
    /// @cellml2_14 14.1.1 Validate TEST valid XML root node for math on a component
    /// @cellml2_14 14.1.1 Validate TEST root node type is of type math
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
    /// @cellml2_14 14.1.2 Validate TEST maths elements are supported MathML elements
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
    /// @cellml2_14 14.1.2 Validate TEST math elements are supported MathML elements
    /// @cellml2_14 14.1.3 Validate TEST ci children point to valid variables in this component
    /// @cellml2_14 14.1.3 Validate TEST check for duplicate names between bound variables and variables in this component
    /// @cellml2_14 14.1.3 Validate TEST check for empty ci element or whitespace only 
    /// @cellml2_14 14.1.3 Validate TEST check that ci variables have been declared

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
        "Component 'componentName' contains multiple variables with the name 'C'. Valid variable names must be unique to their component.",
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

    /// @cellml2_14 14.1.3 Validate TEST check for duplication between bound variable name and variable name in the same component
    /// @cellml2_14 14.1.4 Validate TEST check for valid units reference inside cn
    /// @cellml2_14 14.1.2 Validate TEST check for valid type specification (ie: real, e-notation)
    /// @cellml2_14 14.1.3 Validate TEST check for whitespace only ci element
    /// @cellml2_14 14.1.3 Validate TEST ci has valid variable reference in ths component
    /// @cellml2_14 14.1.3 Validate TEST ci is not empty
    /// @cellml2_14 14.1.3 Validate TEST ci units has valid name
    /// @cellml2_14 14.1.4 Validate TEST cn units are specified
    /// @cellml2_14 "Namespace prefix cellml for value on ci is not defined."
    /// @cellml2_14 "No declaration for attribute cellml:value of element ci."

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

    /// @cellml2_8 8.1.3 Validate TEST Units name does not overload a built-in units name
    /// @cellml2_9 9.1.1 Validate TEST Unit units attribute is valid reference to local or built-in units
    /// @cellml2_9 9.1.1 Validate TEST Unit units attribute must be valid cellml identifier format
    /// @cellml2_9 9.2.1 Validate TEST Unit prefix must be valid real number or SI prefix

    std::vector<std::string> expectedErrors = {
        "Units is named 'ampere', which is a protected standard unit name.",
        "Units reference 'ned' in units 'stark' is not a valid reference to a local units or a standard unit type.",
        "CellML identifiers must not contain any characters other than [a-zA-Z0-9_].",
        "Unit in units 'stark' does not have a valid units reference.",
        "Prefix 'wolf' of a unit referencing 'celsius' in units 'stark' is not a valid integer or a SI prefix.",
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
    /// @cellml2_18 18.1.1 Validate TEST check parent component for variable
    /// @cellml2_18 Validate TEST reciprocity check of equivalent variables.  See 19.10.3
    /// @cellml2_19 19.10.3 Validate TEST reciprocity check that equivalence goes both ways

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
    libcellml::ComponentPtr comp5 = std::make_shared<libcellml::Component>();
    libcellml::ComponentPtr comp6 = std::make_shared<libcellml::Component>();
    libcellml::ComponentPtr comp7 = std::make_shared<libcellml::Component>();

    libcellml::VariablePtr v1_1 = std::make_shared<libcellml::Variable>();
    libcellml::VariablePtr v1_2 = std::make_shared<libcellml::Variable>();
    libcellml::VariablePtr v2 = std::make_shared<libcellml::Variable>();
    libcellml::VariablePtr v3 = std::make_shared<libcellml::Variable>();
    libcellml::VariablePtr v4 = std::make_shared<libcellml::Variable>();
    libcellml::VariablePtr v5 = std::make_shared<libcellml::Variable>();
    libcellml::VariablePtr v6 = std::make_shared<libcellml::Variable>();
    libcellml::VariablePtr v7 = std::make_shared<libcellml::Variable>();

    m->setName("modelName");
    comp1->setName("component1");
    comp2->setName("component2");
    comp3->setName("component3");
    comp4->setName("component4");
    comp5->setName("component5");
    comp6->setName("component6");
    comp7->setName("component7");

    v1_1->setName("variable1_1");
    v1_2->setName("variable1_2");
    v2->setName("variable2");
    v3->setName("variable3");
    v4->setName("variable4");
    v5->setName("variable5");
    v6->setName("variable6");
    v7->setName("variable7");

    v1_1->setUnits("dimensionless");
    v1_2->setUnits("dimensionless");
    v2->setUnits("dimensionless");
    v3->setUnits("dimensionless");
    v4->setUnits("dimensionless");
    v5->setUnits("dimensionless");
    v6->setUnits("dimensionless");
    v7->setUnits("dimensionless");

    comp1->addVariable(v1_1);
    comp1->addVariable(v1_2);
    comp2->addVariable(v2);
    comp3->addVariable(v3);
    comp4->addVariable(v4);
    comp5->addVariable(v5);
    comp6->addVariable(v6);
    comp7->addVariable(v7);
    m->addComponent(comp1);
    m->addComponent(comp2);
    m->addComponent(comp3);
    m->addComponent(comp4);
    m->addComponent(comp5); 
    m->addComponent(comp6);
    m->addComponent(comp7);

    // Valid connections.
    libcellml::Variable::addEquivalence(v1_1, v2);  
    libcellml::Variable::addEquivalence(v1_2, v2);
    // Removed the line below to prevent the cycles from appearing here.  Cycles are tested separately in validateNoCycles
    // libcellml::Variable::addEquivalence(v1_1, v3);  // !! creates cycle with v1_1, v2, v3
    libcellml::Variable::addEquivalence(v1_1, v4);
    libcellml::Variable::addEquivalence(v2, v3);    
    libcellml::Variable::addEquivalence(v5, v6);	// valid here but duplicated below

    // Not valid connections
    libcellml::Variable::addEquivalence(v6, v5);    // duplicated above, does not overwrite, skips silently
    
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

TEST(Validator, validateConnectionComponent1NotEqualComponent2) {

    std::vector<std::string> expectedErrors = {
        "Variable 'doppelganger' has an equivalent variable 'doppelganger' equal to itself. ",
    };
    libcellml::Validator validator;
    libcellml::ModelPtr m = std::make_shared<libcellml::Model>();
    libcellml::ComponentPtr c = std::make_shared<libcellml::Component>();
    libcellml::VariablePtr v = std::make_shared<libcellml::Variable>();
    m->setName("modelName");
    v->setName("doppelganger");
    v->setUnits("dimensionless");
    c->setName("bucket");
    c->addVariable(v);
    m->addComponent(c);
    libcellml::Variable::addEquivalence(v, v);          
    validator.validateModel(m);

    EXPECT_EQ(1u, validator.errorCount());
    for (size_t i = 0; i < validator.errorCount(); ++i) {
        EXPECT_EQ(validator.getError(i)->getDescription(), expectedErrors[i]);
    }
}

TEST(Validator, validateNoCyclesSimple) {
    /// @cellml2_19 19.10.5 Validate that no variable equivalence network has cycles - simple test
    /// @cellml2_19 19.10.5 TODO Can two sibling variables in the same component be equivalent to one variable in another?

    libcellml::Validator v;
    libcellml::ModelPtr m = std::make_shared<libcellml::Model>();
    libcellml::ComponentPtr comp1 = std::make_shared<libcellml::Component>();
    libcellml::ComponentPtr comp2 = std::make_shared<libcellml::Component>();
    libcellml::ComponentPtr comp3 = std::make_shared<libcellml::Component>();
    
    libcellml::VariablePtr v1 = std::make_shared<libcellml::Variable>();
    libcellml::VariablePtr v2 = std::make_shared<libcellml::Variable>();
    libcellml::VariablePtr v3 = std::make_shared<libcellml::Variable>();
    
    m->setName("modelName");
    comp1->setName("component1");
    comp2->setName("component2");
    comp3->setName("component3");
    
    v1->setName("variable1");
    v2->setName("variable2");
    v3->setName("variable3");

    v1->setUnits("dimensionless");
    v2->setUnits("dimensionless");
    v3->setUnits("dimensionless");
  
    comp1->addVariable(v1);
    comp2->addVariable(v2);
    comp3->addVariable(v3);
    
    m->addComponent(comp1);
    m->addComponent(comp2);
    m->addComponent(comp3);
   
    libcellml::Variable::addEquivalence(v1, v2); 
    libcellml::Variable::addEquivalence(v2, v3);
    libcellml::Variable::addEquivalence(v3, v1); 
   
    v.validateModel(m);
    EXPECT_EQ(1u, v.errorCount());

    if (v.errorCount() == 1) {
        size_t pos = 0;
        std::string split = "Loop: ";
        std::string msg = v.getError(0)->getDescription();
        std::vector<std::string> split_msg;

        while ((pos = msg.find(split)) != std::string::npos) {
            split_msg.push_back(msg.substr(0, pos));
            msg.erase(0, pos + split.length());
        }
        split_msg.push_back(msg);

        EXPECT_EQ(2u, split_msg.size());

        if (split_msg.size() == 2) {
            bool found = false;
            if (split_msg[1].find("variable1") &&
                split_msg[1].find("variable2") &&
                split_msg[1].find("variable3")) {
                found = true;
            }
            EXPECT_TRUE(found);
        }
    }   
}

TEST(Validator, validateNoCyclesComplicated) {
    /// @cellml2_19 19.10.5 Validate that no variable equivalence network has cycles, complicated example
    /// @cellml2_19 19.10.5 TODO Can two sibling variables in the same component be equivalent to one variable in another?
 
    libcellml::Validator v;
    libcellml::ModelPtr m = std::make_shared<libcellml::Model>();
    libcellml::ComponentPtr comp1 = std::make_shared<libcellml::Component>();
    libcellml::ComponentPtr comp2 = std::make_shared<libcellml::Component>();
    libcellml::ComponentPtr comp3 = std::make_shared<libcellml::Component>();
    libcellml::ComponentPtr comp4 = std::make_shared<libcellml::Component>();
    libcellml::ComponentPtr comp5 = std::make_shared<libcellml::Component>();
    libcellml::ComponentPtr comp6 = std::make_shared<libcellml::Component>();
    libcellml::ComponentPtr comp7 = std::make_shared<libcellml::Component>();
    libcellml::ComponentPtr comp8 = std::make_shared<libcellml::Component>();
    libcellml::ComponentPtr comp9 = std::make_shared<libcellml::Component>();
    libcellml::ComponentPtr comp10 = std::make_shared<libcellml::Component>();
    libcellml::ComponentPtr comp11 = std::make_shared<libcellml::Component>();
    libcellml::ComponentPtr comp12 = std::make_shared<libcellml::Component>();
    libcellml::ComponentPtr comp13 = std::make_shared<libcellml::Component>();
    libcellml::ComponentPtr comp14 = std::make_shared<libcellml::Component>();
    libcellml::ComponentPtr comp15 = std::make_shared<libcellml::Component>();
    libcellml::ComponentPtr comp16 = std::make_shared<libcellml::Component>();
    libcellml::ComponentPtr comp17 = std::make_shared<libcellml::Component>();

    libcellml::VariablePtr v1_1 = std::make_shared<libcellml::Variable>();
    libcellml::VariablePtr v1_2 = std::make_shared<libcellml::Variable>();
    libcellml::VariablePtr v1_3 = std::make_shared<libcellml::Variable>();
    libcellml::VariablePtr v1_4 = std::make_shared<libcellml::Variable>();
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
    libcellml::VariablePtr v15 = std::make_shared<libcellml::Variable>();
    libcellml::VariablePtr v16 = std::make_shared<libcellml::Variable>();
    libcellml::VariablePtr v17 = std::make_shared<libcellml::Variable>();

    m->setName("modelName");
    comp1->setName("component1");
    comp2->setName("component2");
    comp3->setName("component3");
    comp4->setName("component4");
    comp5->setName("component5");
    comp6->setName("component6");
    comp7->setName("component7");
    comp8->setName("component8");
    comp9->setName("component9");
    comp10->setName("component10");
    comp11->setName("component11");
    comp12->setName("component12");
    comp13->setName("component13");
    comp14->setName("component14");
    comp15->setName("component15");
    comp16->setName("component16");
    comp17->setName("component17");

    v1_1->setName("variable1_1");
    v1_2->setName("variable1_2");
    v1_3->setName("variable1_3");
    v1_4->setName("variable1_4");
    v2->setName("variable2");
    v3->setName("variable3");
    v4->setName("variable4");
    v5->setName("variable5");
    v6->setName("variable6");
    v7->setName("variable7");
    v8->setName("variable8");
    v9->setName("variable9");
    v10->setName("variable10");
    v11->setName("variable11");
    v12->setName("variable12");
    v13->setName("variable13");
    v14->setName("variable14");
    v15->setName("variable15");
    v16->setName("variable16");
    v17->setName("variable17");

    v1_1->setUnits("dimensionless");
    v1_2->setUnits("dimensionless");
    v1_3->setUnits("dimensionless");
    v1_4->setUnits("dimensionless");
    v2->setUnits("dimensionless");
    v3->setUnits("dimensionless");
    v4->setUnits("dimensionless");
    v5->setUnits("dimensionless");
    v6->setUnits("dimensionless");
    v7->setUnits("dimensionless");
    v8->setUnits("dimensionless");
    v9->setUnits("dimensionless");
    v10->setUnits("dimensionless");
    v11->setUnits("dimensionless");
    v12->setUnits("dimensionless");
    v13->setUnits("dimensionless");
    v14->setUnits("dimensionless");
    v15->setUnits("dimensionless");
    v16->setUnits("dimensionless");
    v17->setUnits("dimensionless");

    comp1->addVariable(v1_1);
    comp1->addVariable(v1_2);
    comp1->addVariable(v1_3);
    comp1->addVariable(v1_4);

    comp2->addVariable(v2);
    comp3->addVariable(v3);
    comp4->addVariable(v4);
    comp5->addVariable(v5);
    comp6->addVariable(v6);
    comp7->addVariable(v7);
    comp8->addVariable(v8);
    comp9->addVariable(v9);
    comp10->addVariable(v10);
    comp11->addVariable(v11);
    comp12->addVariable(v12);
    comp13->addVariable(v13);
    comp14->addVariable(v14);
    comp15->addVariable(v15);
    comp16->addVariable(v16);
    comp17->addVariable(v17);

    m->addComponent(comp1);
    m->addComponent(comp2);
    m->addComponent(comp3);
    m->addComponent(comp4);
    m->addComponent(comp5); 
    m->addComponent(comp6);
    m->addComponent(comp7);
    m->addComponent(comp8);
    m->addComponent(comp9); 
    m->addComponent(comp10);
    m->addComponent(comp11);
    m->addComponent(comp12);
    m->addComponent(comp13);
    m->addComponent(comp14);
    m->addComponent(comp15);
    m->addComponent(comp16);
    m->addComponent(comp17);

    libcellml::Variable::addEquivalence(v2, v4); 
    libcellml::Variable::addEquivalence(v3, v4);
    libcellml::Variable::addEquivalence(v8, v6); 
    libcellml::Variable::addEquivalence(v2, v8);    
    libcellml::Variable::addEquivalence(v3, v6);    // Loop formed: 2, 4, 3, 6, 8, 2 

    libcellml::Variable::addEquivalence(v6, v7);    
    
    // NB Attached loops (ie: a-b-c-a and b-c-d-b) *are* detected and handled but return too many variations of the loop 
    // (eg a-b-c-d, a-b-c, b-c-d, etc) to be viable as a hard-coded test, so have broken the attachment here.
    // libcellml::Variable::addEquivalence(v3, v7);    // Second attached loop: 3, 6, 7 

    libcellml::Variable::addEquivalence(v9, v5); 
    libcellml::Variable::addEquivalence(v5, v1_2);
    libcellml::Variable::addEquivalence(v1_2, v9);  // Unattached loop: 5, 9, 1_2

    libcellml::Variable::addEquivalence(v11, v4); 
    libcellml::Variable::addEquivalence(v11, v14);
    libcellml::Variable::addEquivalence(v11, v13);
    libcellml::Variable::addEquivalence(v11, v12);
    libcellml::Variable::addEquivalence(v12, v15);
    libcellml::Variable::addEquivalence(v12, v17);
    libcellml::Variable::addEquivalence(v17, v16);   // Complicated tree, no loops 

    libcellml::Variable::addEquivalence(v1_1, v8);  
    libcellml::Variable::addEquivalence(v1_3, v2);  
    // libcellml::Variable::addEquivalence(v1_4, v2);  // TODO Can two sibling variables in the same component be equivalent to one in another?

    v.validateModel(m);
    EXPECT_EQ(1u, v.errorCount());

    // Two loops are present, split error message at "Loop":
    // Check that one loop contains 'variable6' <-> 'variable8' <-> 'variable2' <-> 'variable4' <-> 'variable3' <-> 'variable6',
    // Check that the other contains 'variable1_2' <-> 'variable9' <-> 'variable5' <-> 'variable1_2',
    // "Cyclic variables exist, 2 loops found (Variable(Component)). Loop: 'variable4'(in 'component4') <-> 'variable3'(in 'component3') <-> 'variable6'(in 'component6') <-> 'variable8'(in 'component8') <-> '...
    if (v.errorCount() == 1) {
        size_t pos = 0;
        std::string split = "Loop: ";
        std::string msg = v.getError(0)->getDescription();
        std::vector<std::string> split_msg;

        while ((pos = msg.find(split)) != std::string::npos) {
            split_msg.push_back(msg.substr(0, pos));
            msg.erase(0, pos + split.length());
        }
        split_msg.push_back(msg);

        EXPECT_EQ(3u, split_msg.size());

        if (split_msg.size() == 3) {
        // Check that we have each of the variables present in the two loops
            int found = 0;
            if (((split_msg[1].find("variable6")) &&
                (split_msg[1].find("variable8")) &&
                 (split_msg[1].find("variable2")) &&
                 (split_msg[1].find("variable4")) &&
                 (split_msg[1].find("variable3")))
                || ((split_msg[2].find("variable6")) &&
                (split_msg[2].find("variable8")) &&
                    (split_msg[2].find("variable2")) &&
                    (split_msg[2].find("variable4")) &&
                    (split_msg[2].find("variable3")))) {
                found++;
            }
            if (((split_msg[1].find("variable9")) && (split_msg[1].find("variable5")) && (split_msg[1].find("variable1_2")))
                || ((split_msg[2].find("variable9")) && (split_msg[2].find("variable5")) && (split_msg[2].find("variable1_2")))) {
                found++;
            }
            EXPECT_EQ(2, found);
        }
    }
}

TEST(Validator, integerStrings) {

    /// @cellml2_12 12.1.1.2 Validate TEST order is an integer string (ok: 1, -1; not ok: +1, '', -, string)

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
        "Component 'component' contains a reset referencing variable 'variable' which does not have an order set.",
        "Component 'component' contains a reset referencing variable 'variable' which does not have an order set.",
        "Component 'component' contains a reset referencing variable 'variable' which does not have an order set.",
        "Component 'component' contains a reset referencing variable 'variable' which does not have an order set.",
    };

    libcellml::Parser p;
    libcellml::ModelPtr m = p.parseModel(input);
    EXPECT_EQ(4u, p.errorCount());

    libcellml::Validator v;
    v.validateModel(m);
    EXPECT_EQ(expectedErrors.size(), v.errorCount());

}

TEST(Validator, resets) {
    /// @cellml2_12 12.1.1.2 Validate TEST Resets in a component have duplicated order values
    /// @cellml2_12 12.1.1.1 Validate TEST Reset does not reference a variable
    /// @cellml2_12 12.1.1.1-2 Validate TEST Reset does not have an order or reference a variable
    /// @cellml2_12 12.1.2 Validate TEST Reset does not contain when item
    /// @cellml2_12 12.1.1.1 and 12.1.2 Validate TEST Reset without order also missing child when
    /// @cellml2_12 12.1.1.1-2 Validate TEST Reset without order does not reference a variable
    /// @cellml2_12 12.1.1.1-2 and 12.1.2 Validate TEST Reset without order, variable and any child whens

    std::vector<std::string> expectedErrors1 = {
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

    // adding reset to second component which does not contain the variable needed
    /// @cellml2_12 12.1.1.1 TODO Validate TEST that variable attribute in a reset must be defined within the component parent
    /// of that reset
    libcellml::ModelPtr m2 = std::make_shared<libcellml::Model>();
    libcellml::ComponentPtr c2 = std::make_shared<libcellml::Component>();
    libcellml::VariablePtr var2 = std::make_shared<libcellml::Variable>();
    libcellml::ResetPtr r8 = std::make_shared<libcellml::Reset>();
    libcellml::WhenPtr w3 = std::make_shared<libcellml::When>();

    w3->setOrder(20);
    w3->setCondition("<math xmlns=\"http://www.w3.org/1998/Math/MathML\"></math>");
    w3->setValue("<math xmlns=\"http://www.w3.org/1998/Math/MathML\"></math>");

    var2->setName("var2");
    var2->setUnits("metre");

    libcellml::Validator v1;

    v1.validateModel(m);
    EXPECT_EQ(expectedErrors1.size(), v1.errorCount());
    for (size_t i = 0; i < expectedErrors1.size(); ++i) {
        EXPECT_EQ(expectedErrors1.at(i), v1.getError(i)->getDescription());
    }
    /* TODO This should fail but doesn't because we're not checking resets properly ...*/
    /// @cellml2_12 12.1.1 TODO Validate that reset variable exists in component.  Code to check commented out here
    /*r8->setOrder(20);
    r8->addWhen(w3);
    r8->setVariable(var); // not inside this component ...

    c2->addVariable(var2);
    c2->addReset(r8); 
    c2->setName("comp2");

    m2->setName("main2");
    m2->addComponent(c2);

    libcellml::Validator v2;
    v2.validateModel(m2);
    EXPECT_EQ(1u, v2.errorCount());*/

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

    /// @cellml2_13 13.1.1 Validate TEST When item has an order
    /// @cellml2_12 12.1.1 Validate TEST When item has a reset which references a variable
    /// @cellml2_13 13.1.2 Validate TEST When item has a reset which references a variable, contains a MathML condition
    /// @cellml2_13 13.1.2 Validate TEST When item has a reset which references a variable, contains a MathML value
    /// @cellml2_12 12.1.2 Validate TEST Reset item has an order
    /// @cellml2_12 12.1.2 Validate TEST Reset item has duplicated order values
    /// @cellml2_13 13.1.2 Validate TEST Reset item references a when which does not have a MathML value 
    /// @cellml2_13 13.1.2 Validate TEST Reset item references a when which does not have a MathML condition
    /// @cellml2_13 13.1.1 Validate TEST When item has unique order amongst siblings

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

    /// @cellml2_14 14.1.4 Validate TEST Tests that valid ci entries pass the tests

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

TEST(Validator, setUnitsWithNoChildUnit) {
    /// @cellml2_19 19.10.6 Validate TEST Check unit reduction is the same for equivalent variables, user-defined base variables
    std::vector<std::string> expectedErrors = {
        "Variable 'v1' has units of 'bushell_of_apples' and an equivalent variable 'v2' with non-matching units of 'bunch_of_bananas'. The mismatch is: apple^10.000000, banana^-5.000000, ",
        "Variable 'v4' has units of 'gram' and an equivalent variable 'v3' with non-matching units of 'litre'. The mismatch is: kilogram^1.000000, metre^-3.000000, ",
        "Variable 'v7' has units of 'apple' and an equivalent variable 'v8' with non-matching units of 'banana'. The mismatch is: apple^1.000000, banana^-1.000000, ",
        "Variable 'v2' has units of 'bunch_of_bananas' and an equivalent variable 'v1' with non-matching units of 'bushell_of_apples'. The mismatch is: apple^-10.000000, banana^5.000000, ",
        "Variable 'v5' has units of 'metre' and an equivalent variable 'v6' with non-matching units of 'second'. The mismatch is: metre^1.000000, second^-1.000000, ",
        "Variable 'v8' has units of 'banana' and an equivalent variable 'v7' with non-matching units of 'apple'. The mismatch is: apple^-1.000000, banana^1.000000, ",
        "Variable 'v3' has units of 'litre' and an equivalent variable 'v4' with non-matching units of 'gram'. The mismatch is: kilogram^-1.000000, metre^3.000000, ",
        "Variable 'v6' has units of 'second' and an equivalent variable 'v5' with non-matching units of 'metre'. The mismatch is: metre^-1.000000, second^1.000000, ",
    };

    libcellml::Validator validator;
    libcellml::ModelPtr m = std::make_shared<libcellml::Model>();

    libcellml::ComponentPtr c1 = std::make_shared<libcellml::Component>();
    libcellml::ComponentPtr c2 = std::make_shared<libcellml::Component>();
    libcellml::ComponentPtr c3 = std::make_shared<libcellml::Component>();

    libcellml::VariablePtr v1 = std::make_shared<libcellml::Variable>();
    libcellml::VariablePtr v2 = std::make_shared<libcellml::Variable>();
    libcellml::VariablePtr v3 = std::make_shared<libcellml::Variable>();
    libcellml::VariablePtr v4 = std::make_shared<libcellml::Variable>();
    libcellml::VariablePtr v5 = std::make_shared<libcellml::Variable>();
    libcellml::VariablePtr v6 = std::make_shared<libcellml::Variable>();
    libcellml::VariablePtr v7 = std::make_shared<libcellml::Variable>();
    libcellml::VariablePtr v8 = std::make_shared<libcellml::Variable>();
    libcellml::VariablePtr v9 = std::make_shared<libcellml::Variable>();

    m->setName("m");
    c1->setName("c1");
    c2->setName("c2");
    c3->setName("c3");
    
    v1->setName("v1");
    v2->setName("v2");
    v3->setName("v3");
    v4->setName("v4");
    v5->setName("v5");
    v6->setName("v6");
    v7->setName("v7");
    v8->setName("v8");
    v9->setName("v9");

    libcellml::UnitsPtr uApple = std::make_shared<libcellml::Units>();
    uApple->setName("apple");

    libcellml::UnitsPtr uBanana = std::make_shared<libcellml::Units>();
    uBanana->setName("banana");

    libcellml::UnitsPtr u1 = std::make_shared<libcellml::Units>();
    u1->setName("bushell_of_apples"); 
    u1->addUnit("apple", 0, 10.0, 1.0);

    libcellml::UnitsPtr u2 = std::make_shared<libcellml::Units>();
    u2->setName("bunch_of_bananas");
    u2->addUnit("banana", 0, 5.0, 1.0);

    libcellml::UnitsPtr u9 = std::make_shared<libcellml::Units>();
    u9->setName("big_barrel"); 
    u9->addUnit("metre", 0, 3.0, 1.0);

    v1->setUnits(u1); // bushell of apples - testing user-defined base units
    v2->setUnits(u2); // bunch of bananas - testing user-defined base units
    
    v3->setUnits("litre"); // testing standard units which are not base units
    v4->setUnits("gram");

    v5->setUnits("metre"); // testing built-in base units
    v6->setUnits("second");

    v7->setUnits("apple");
    v8->setUnits("banana");

    v9->setUnits(u9);

    c1->addVariable(v1);
    c2->addVariable(v2);
    c3->addVariable(v3);

    c1->addVariable(v4);
    c2->addVariable(v5);
    c3->addVariable(v6);

    c1->addVariable(v7);
    c2->addVariable(v8);
    c3->addVariable(v9);

    m->addComponent(c1);
    m->addComponent(c2);
    m->addComponent(c3);

    m->addUnits(u1);
    m->addUnits(u2);
    m->addUnits(u9);
    m->addUnits(uApple);
    m->addUnits(uBanana);
       
    libcellml::Variable::addEquivalence(v1, v2); // bushell of apples != bunch of bananas
    libcellml::Variable::addEquivalence(v3, v4); // litre != gram
    libcellml::Variable::addEquivalence(v5, v6); // metre != second
    libcellml::Variable::addEquivalence(v7, v8); // apple != banana
    libcellml::Variable::addEquivalence(v3, v9); // litre = big_barrel (excluding multipliers)

    validator.validateModel(m);

    EXPECT_EQ(8u, validator.errorCount());

    for (size_t i = 0; i < validator.errorCount(); ++i) {
        EXPECT_EQ(expectedErrors.at(i), validator.getError(i)->getDescription());
    }
}

TEST(Validator, variableEquivalentUnits) {
    /// @cellml2_19 19.10.6 Validate TEST Check unit reduction is the same for equivalent variables, built-in base variables  
    std::vector<std::string> expectedErrors = {
        "Variable 'potayto' has units of 'testunit3' and an equivalent variable 'tomahto' with non-matching units of 'testunit2'. The mismatch is: kilogram^1.000000, metre^-2.000000, second^-2.000000, ",
        "Variable 'tomahto' has units of 'testunit2' and an equivalent variable 'potayto' with non-matching units of 'testunit3'. The mismatch is: kilogram^-1.000000, metre^2.000000, second^2.000000, ",
        "Variable 'pjs' has units of 'testunit13' and an equivalent variable 'pajamas' with non-matching units of 'testunit14'. The mismatch is: metre^1.000000, ",
        "Variable 'pajamas' has units of 'testunit14' and an equivalent variable 'pjs' with non-matching units of 'testunit13'. The mismatch is: metre^-1.000000, "
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
    u4->addUnit("metre", 0, -1.0, 1.0); // prefix, exp, mult
    u4->addUnit("kilogram", 0, 1.0, 1.0);
    u4->addUnit("second", 0, -2.0, 1.0);

    libcellml::UnitsPtr u5 = std::make_shared<libcellml::Units>();
    u5->setName("testunit5");
    u5->addUnit("metre", 0, -2.0, 1.0);
    u5->addUnit("meter", 0, 2.0, 1.0);

    libcellml::UnitsPtr u6 = std::make_shared<libcellml::Units>();
    u6->setName("testunit6");
    u6->addUnit("dimensionless");

    libcellml::UnitsPtr u7 = std::make_shared<libcellml::Units>();
    u7->setName("testunit7");
    u7->addUnit("steradian");

    libcellml::UnitsPtr u8 = std::make_shared<libcellml::Units>();
    u8->setName("testunit8");
    u8->addUnit("newton", 0, 1, 1);
    u8->addUnit("pascal", 0, -1, 1);
    u8->addUnit("sievert", 0, -1, 1);

    libcellml::UnitsPtr u9 = std::make_shared<libcellml::Units>();
    u9->setName("testunit9");
    u9->addUnit("second", 0, 2, 1);
    u9->addUnit("radian", 0, -4, 1);
    u9->addUnit("steradian", 0, 2, 1);

    libcellml::UnitsPtr u10 = std::make_shared<libcellml::Units>();
    u10->setName("testunit10");
    u10->addUnit("gram", 0, 1, 1000.0);

    libcellml::UnitsPtr u11 = std::make_shared<libcellml::Units>();
    u11->setName("testunit11");
    u11->addUnit("kilogram");

    libcellml::UnitsPtr u12 = std::make_shared<libcellml::Units>();
    u12->setName("testunit12");
    u12->addUnit("gram", "kilo", 1.0, 1.0);

    libcellml::UnitsPtr u13 = std::make_shared<libcellml::Units>();
    u13->setName("testunit13");
    u13->addUnit("testunit2", 0, 2.0, 1.0);
    u13->addUnit("testunit8", 0, 2.0, 1.0);

    libcellml::UnitsPtr u14 = std::make_shared<libcellml::Units>();
    u14->setName("testunit14");
    u14->addUnit("testunit1", 0, 1.0, 1.0);
    u14->addUnit("testunit9", 0, 2.0, 1.0);

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

    // This one is fine : metre vs meter
    libcellml::Variable::addEquivalence(v1, v2);

    // This one is NOT fine: metre vs pascal
    libcellml::Variable::addEquivalence(v2, v3);

    // This one is fine: pascal vs kg/(m.s^2)
    libcellml::Variable::addEquivalence(v3, v4);

    // This one is fine: m^2/m^2 vs dimensionless
    libcellml::Variable::addEquivalence(v5, v6);
    
    // This one is fine: dimensionless vs steradians
    libcellml::Variable::addEquivalence(v6, v7);

    // This one is fine but complicated: newton/(siever.pascal) = second^2.radian^3.steradian^-4
    libcellml::Variable::addEquivalence(v8, v9);	

    // Fine: testing the multipliers 1000*grams = 1*kilograms 
    // ** NB multipliers not tested!
    libcellml::Variable::addEquivalence(v10, v11);

    // Fine: testing prefix kilo*gram = kilogram
    // ** NB multipliers not tested!
    libcellml::Variable::addEquivalence(v10, v12); 

    // Off by (meter)^1: super-complicated nested units
    libcellml::Variable::addEquivalence(v13, v14);

    validator.validateModel(m);

    EXPECT_EQ(4u, validator.errorCount());

    // Check for expected error messages
    for (size_t i = 0; i < validator.errorCount(); ++i) {
        EXPECT_EQ(expectedErrors.at(i), validator.getError(i)->getDescription());
    }
}

TEST(Validator, validateNoCyclesUnits) {
    /// @cellml2_9 9.1.1.1-2 TEST Cyclic definitions in units
    std::vector<std::string> expectedErrors = {
        "Cyclic units exist: 'grandfather' -> 'brotherFromAnotherMother' -> 'father' -> 'grandfather'",
        "Cyclic units exist: 'father' -> 'grandfather' -> 'brotherFromAnotherMother' -> 'father'",
        "Cyclic units exist: 'brotherFromAnotherMother' -> 'father' -> 'grandfather' -> 'brotherFromAnotherMother'",
    };

    libcellml::Validator v;
    libcellml::ModelPtr m = std::make_shared<libcellml::Model>();
    libcellml::ComponentPtr c = std::make_shared<libcellml::Component>();

    libcellml::VariablePtr v1 = std::make_shared<libcellml::Variable>();
    libcellml::VariablePtr v2 = std::make_shared<libcellml::Variable>();
    libcellml::VariablePtr v3 = std::make_shared<libcellml::Variable>();

    libcellml::UnitsPtr u1 = std::make_shared<libcellml::Units>();
    libcellml::UnitsPtr u2 = std::make_shared<libcellml::Units>();
    libcellml::UnitsPtr u3 = std::make_shared<libcellml::Units>();
    libcellml::UnitsPtr u4 = std::make_shared<libcellml::Units>();
    libcellml::UnitsPtr u5 = std::make_shared<libcellml::Units>();
    libcellml::UnitsPtr u6 = std::make_shared<libcellml::Units>();

    m->setName("model");

    m->addUnits(u1);
    m->addUnits(u2);
    m->addUnits(u3);
    m->addUnits(u4);    
    m->addUnits(u5);
    m->addUnits(u6);

    u1->setName("grandfather"); // base unit

    u2->setName("father"); // first generation
    u2->addUnit("grandfather", 0, 1.0, 1.0);

    u3->setName("mother"); // first generation
    u3->addUnit("grandfather", 0, 1.0, 1.0);

    u4->setName("brotherFromAnotherMother"); // second generation
    u4->addUnit("father", 0, 1.0, 1.0);

    // second generation depending on both first gen children, still valid, no loops because of directionality
    u5->setName("childOfIncest_ButThatsOKApparently"); 
    u5->addUnit("mother", 0, 1.0, 1.0);
    u5->addUnit("father", 0, 1.0, 1.0);

    u6->setName("sisterFromAnotherMister"); // second generation
    u6->addUnit("mother", 0, 1.0, 1.0);

    v.validateModel(m);
    EXPECT_EQ(0u, v.errorCount());
    
    // Time loop Grandfather paradox created! u1 no longer a base variable: u1 -> u4 -> u2 -> u1
    u1->addUnit("brotherFromAnotherMother", 0, 1.0, 1.0);
    v.validateModel(m);

    EXPECT_EQ(3u, v.errorCount());
    for (size_t i = 0; i < v.errorCount(); i++) {
        EXPECT_EQ(expectedErrors.at(i), v.getError(i)->getDescription());
    }   
}

TEST(Validator, importNameNotFoundInFile) {
    // Check that component/unit name to import exists in specified import location
    std::ifstream t(TestResources::getLocation(TestResources::CELLML_RECURSIVE_FILE_IMPORT));
    std::stringstream buffer;
    buffer << t.rdbuf();

    libcellml::Parser p;
    libcellml::ModelPtr m = p.parseModel(buffer.str());

    libcellml::Validator v;
    v.validateModel(m,TestResources::getLocation(TestResources::CELLML_RECURSIVE_FILE_IMPORT));
    EXPECT_EQ(1u, v.errorCount());

    std::vector<std::string> expected = { 
        "Import of units 'sandiness' has failed. Tried:",
        "recursive_import.cellml) which was not found in the file." 
    };

    std::string a = v.getError(0)->getDescription();
    std::size_t f1 = a.find(expected.at(0));
    std::size_t f2 = a.find(expected.at(1));
    EXPECT_NE(f1, std::string::npos);
    EXPECT_NE(f2, std::string::npos);
 }

TEST(Validator, importFileDoesNotExist) {
    // Check import file exists
    std::ifstream t(TestResources::getLocation(TestResources::CELLML_FILE_WITH_NONEXISTENT_REF));
    std::stringstream buffer;
    buffer << t.rdbuf();

    libcellml::Parser p;
    libcellml::ModelPtr m = p.parseModel(buffer.str());

    libcellml::Validator v;
    v.validateModel(m,TestResources::getLocation(TestResources::CELLML_FILE_WITH_NONEXISTENT_REF));

    EXPECT_EQ(2u, v.errorCount());

    std::vector<std::vector<std::string>> expected;
    expected.push_back({"Import of component 'duplicating_the_beach' has failed:",
                       "('duplicating_the_beach' in import_missing_file.cellml) which imports",
                       "this_one_does_not_exist.cellml) but the file was not found.",});
    expected.push_back({ "Import of units 'sandiness' has failed:",
                       "('sandiness' in import_missing_file.cellml) which imports",
                       "this_one_does_not_exist_either.cellml) but the file was not found." });

    for (size_t i = 0; i < expected.size(); ++i) {
        for (size_t j = 0; j < expected.at(i).size(); ++j) {
            std::string e = v.getError(i)->getDescription();
            std::size_t found = e.find(expected.at(i).at(j));
            EXPECT_NE(found, std::string::npos);
        }
    }
}

TEST(Validator, importLayer) {
    // Check changes in directory are permitted
    std::ifstream t(TestResources::getLocation(TestResources::CELLML_LAYERED_IMPORT_FILE));
    std::stringstream buffer;
    buffer << t.rdbuf();

    libcellml::Parser p;
    libcellml::ModelPtr m = p.parseModel(buffer.str());

    libcellml::Validator v;
    v.validateModel(m,TestResources::getLocation(TestResources::CELLML_LAYERED_IMPORT_FILE));

    EXPECT_EQ(1u, v.errorCount());
    std::vector<std::string> expected = {"Import of units 'u1' has failed. Tried:",
                       "('u1' in recursiveImport_1.cellml) imports",
                       "recursiveImport_3.cellml) which was not found in the file.",};
    std::string e = v.getError(0)->getDescription();
    for (size_t j = 0; j < expected.size(); ++j) {
        std::size_t found = e.find(expected.at(j));
        EXPECT_NE(found, std::string::npos);
    }
}

TEST(Validator, validateCircularImportReferences) {
    // Check true circular references are identified and execution stops
    // Check false circular references are allowed (eg: reference to another name in already-used file)

    std::ifstream t(TestResources::getLocation(TestResources::CELLML_CIRCULAR_IMPORT_FILE));
    std::stringstream buffer;
    buffer << t.rdbuf();

    libcellml::Parser p;
    libcellml::ModelPtr m = p.parseModel(buffer.str());

    libcellml::Validator v;
    v.validateModel(m,TestResources::getLocation(TestResources::CELLML_CIRCULAR_IMPORT_FILE));

    EXPECT_EQ(2u, v.errorCount());

    std::vector<std::vector<std::string>> expected;
    expected.push_back({"Import of component 'i_am_cyclic' has circular dependencies:",
                       "('i_am_cyclic' in circularImport_1.cellml) which imports",
                       "circularImport_2a.cellml) which imports",
                       "circularImport_3.cellml) which imports",
    });
    expected.push_back({"Import of units 'u1' has failed. Tried:",
                       "('u1' in circularImport_1.cellml) imports",
                       "circularImport_2b.cellml) imports",
                       "circularImport_3.cellml) which was not found in the file."});

    for (size_t i = 0; i < expected.size(); ++i) {
        for (size_t j = 0; j < expected.at(i).size(); ++j) {
            std::string e = v.getError(i)->getDescription();
            std::size_t found = e.find(expected.at(i).at(j));
            EXPECT_NE(found, std::string::npos);
        }
    }
}

TEST(Validator, validateImportsInMultipleLocations) {
    // Check import from same filename in another directory
    // Check ../  notation in href to go to parent directory
    std::ifstream t(TestResources::getLocation(TestResources::CELLML_SAME_FILE_OTHER_DIR_RESOURCE));
    std::stringstream buffer;
    buffer << t.rdbuf();

    libcellml::Parser p;
    libcellml::ModelPtr m = p.parseModel(buffer.str());

    libcellml::Validator v;
    v.validateModel(m,TestResources::getLocation(TestResources::CELLML_SAME_FILE_OTHER_DIR_RESOURCE));

    EXPECT_EQ(0u, v.errorCount());
}

TEST(Validator, validateGenerationalImport) {
    // Check non-absolute references in child imports change working directory 

    std::ifstream t(TestResources::getLocation(TestResources::CELLML_RECURSIVE_FILE_IMPORT_PATH));
    std::stringstream buffer;
    buffer << t.rdbuf();

    libcellml::Parser p;
    libcellml::ModelPtr m = p.parseModel(buffer.str());

    libcellml::Validator v;
    v.validateModel(m,TestResources::getLocation(TestResources::CELLML_RECURSIVE_FILE_IMPORT_PATH));

    EXPECT_EQ(0u, v.errorCount());
}

TEST(Validator, validateAbsolutePathImports) {
    // In these tests all initial filenames returned from getLocation() are absolute.  All referenced
    // files inside those resources are relative (as we don't know ahead of time where they will be found).
    // This test is intended to provide coverage for the relative vs absolute file options in the validator.

    std::string full_filename = TestResources::getLocation(TestResources::CELLML_RECURSIVE_FILE_IMPORT_PATH);
    std::ifstream t(full_filename);
    std::stringstream buffer;
    buffer << t.rdbuf();

    libcellml::Parser parser;
    libcellml::ModelPtr model = parser.parseModel(buffer.str());
    libcellml::Validator validator;

    std::string filename = "";
    std::string path = "";
    size_t i = filename.find_last_of("/\\");

    if (i != std::string::npos) {
        filename = full_filename.substr(i+1, full_filename.length()-i);
        path = full_filename.substr(0, i+1);
    }
    validator.validateModel(model, filename, path); // no errors
    EXPECT_EQ(0u, validator.errorCount());
    validator.validateModel(model, full_filename); // no errors
    EXPECT_EQ(0u, validator.errorCount());
    validator.validateModel(model, filename); // TODO warning that full depth is not checked?
    EXPECT_EQ(0u, validator.errorCount());
    validator.validateModel(model); // TODO warning that full depth is not checked?
    EXPECT_EQ(0u, validator.errorCount());

    // These is a fake file to give test coverage to the isRelativePath() function
    validator.validateModel(model, "C:/hello/hello.cellml");
    EXPECT_EQ(1u, validator.errorCount());
    std::vector<std::string> expected = {
        "Import of component 'latte' has failed:",
        "('latte' in hello.cellml) which imports",
        "recursive_import_path2.cellml) but the file was not found."
    };
    for (size_t j = 0; j < expected.size(); ++j) {
        std::string e = validator.getError(0)->getDescription();
        std::size_t found = e.find(expected.at(j));
        EXPECT_NE(found, std::string::npos);
    }
}

TEST(Validator, parseInvalidModelFromFile) {
    std::string filename = TestResources::getLocation(TestResources::CELLML_ABSOLUTE_RELATIVE_FILES);
    std::ifstream t(filename);
    std::stringstream buffer;
    buffer << t.rdbuf();

    libcellml::Parser parser;
    libcellml::ModelPtr m = parser.parseModel(buffer.str());
    libcellml::Validator v;

    size_t i = filename.find_last_of("/\\", filename.length());
    std::string path = "";
    if (i != std::string::npos) {
        path = filename.substr(0,i+1);
    }
    // Deliberately giving the full filename to test handling ...
    v.validateModel(m, filename, path);

    std::vector<std::string> expectedErrors = {
        "Model element is of invalid type 'not_a_model'. A valid CellML root node should be of type 'model'.",
        "Model element is in invalid namespace 'http://www.cellml.org/cellml/wrong'. A valid CellML root node should be in namespace 'http://www.cellml.org/cellml/2.0#'.",
        "Import of component 'i_am_not_real_either' has failed",
        "Start tag expected, '<' not found.",
        "Could not get a valid XML root node from the provided input.",
        "Model element is of invalid type 'not_a_real_tag'. A valid CellML root node should be of type 'model'.",
        "model_wrong_attribute.cellml' has an invalid attribute 'not_an_attribute'.",
        "i_am_almost_ok.cellml' has an invalid attribute 'not_here_either'.",
        "i_am_almost_ok.cellml' has an invalid child element 'not_a_child'.",
        "has an invalid non-whitespace child text element 'shouldnt_be_here",
        "i_am_almost_ok.cellml' has an invalid attribute 'not_an_attribute'",
        "i_am_almost_ok.cellml' has an invalid child element 'not_an_import'.",
        "i_am_almost_ok.cellml has an invalid non-whitespace child text element 'or_even_here",
        "Import of component 'not_an_attribute' has failed. Tried:",
        "Model element is in invalid namespace 'null'. A valid CellML root node should be in namespace 'http://www.cellml.org/cellml/2.0#'",
    };

    EXPECT_EQ(expectedErrors.size(), v.errorCount());

    for (size_t i = 0; i < expectedErrors.size(); ++i) {
        std::string e = v.getError(i)->getDescription();
        std::size_t found = e.find(expectedErrors.at(i));
        EXPECT_NE(found, std::string::npos);
    }
}









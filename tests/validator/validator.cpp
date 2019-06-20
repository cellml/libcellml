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

TEST(Validator, namedModel)
{
    libcellml::Validator validator;
    libcellml::ModelPtr model = std::make_shared<libcellml::Model>();
    model->setName("awesomeName");
    validator.validateModel(model);
    EXPECT_EQ(size_t(0), validator.errorCount());
}

TEST(Validator, unnamedModel)
{
    const std::string expectedError = "Model does not have a valid name attribute.";
    libcellml::Validator validator;
    libcellml::ModelPtr model = std::make_shared<libcellml::Model>();
    validator.validateModel(model);
    EXPECT_EQ(size_t(2), validator.errorCount());
    EXPECT_EQ(expectedError, validator.error(1)->description());
    EXPECT_EQ("4.2.1", validator.error(1)->specificationHeading());
}

TEST(Validator, invalidCellMLIdentifiersWithSpecificationHeading)
{
    const std::vector<std::string> expectedErrors = {
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
    const std::vector<std::string> expectedSpecificationHeadings = {
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

    EXPECT_EQ(size_t(10), v.errorCount());
    for (size_t i = 0; i < v.errorCount(); ++i) {
        EXPECT_EQ(expectedErrors.at(i), v.error(i)->description());
        EXPECT_EQ(expectedSpecificationHeadings.at(i), v.error(i)->specificationHeading());
    }
}

TEST(Validator, moveCopyValidatorWithUnnamedModel)
{
    libcellml::Validator v;
    libcellml::Validator vm;
    libcellml::ModelPtr model = std::make_shared<libcellml::Model>();
    v.validateModel(model);

    // Move
    vm = std::move(v);
    // Copy
    libcellml::Validator vc(vm);

    // Check that the model error is in the copy.
    EXPECT_EQ(libcellml::Error::Kind::MODEL, vc.error(1)->kind());
}

TEST(Validator, namedModelWithUnnamedComponent)
{
    const std::string expectedError = "Component does not have a valid name attribute.";
    libcellml::Validator validator;
    libcellml::ModelPtr model = std::make_shared<libcellml::Model>();
    libcellml::ComponentPtr component = std::make_shared<libcellml::Component>();
    model->setName("awesomeName");
    model->addComponent(component);
    validator.validateModel(model);
    EXPECT_EQ(size_t(2), validator.errorCount());
    EXPECT_EQ(expectedError, validator.error(1)->description());
}

TEST(Validator, unnamedModelWithUnnamedComponentWithUnnamedUnits)
{
    const std::vector<std::string> expectedErrors = {
        "CellML identifiers must contain one or more basic Latin alphabetic characters.",
        "Model does not have a valid name attribute.",
        "CellML identifiers must contain one or more basic Latin alphabetic characters.",
        "Component does not have a valid name attribute.",
        "CellML identifiers must contain one or more basic Latin alphabetic characters.",
        "Units does not have a valid name attribute."};

    libcellml::Validator validator;
    libcellml::ModelPtr model = std::make_shared<libcellml::Model>();
    libcellml::ComponentPtr component = std::make_shared<libcellml::Component>();
    libcellml::UnitsPtr units = std::make_shared<libcellml::Units>();
    model->addComponent(component);
    model->addUnits(units);
    validator.validateModel(model);

    EXPECT_EQ(expectedErrors.size(), validator.errorCount());
    for (size_t i = 0; i < validator.errorCount(); ++i) {
        EXPECT_EQ(expectedErrors.at(i), validator.error(i)->description());
    }
}

TEST(Validator, modelWithDuplicateComponentsAndUnits)
{
    const std::vector<std::string> expectedErrors = {
        "Model 'multiplicity' contains multiple components with the name 'michael'. Valid component names must be unique to their model.",
        "Model 'multiplicity' contains multiple units with the name 'keaton'. Valid units names must be unique to their model."};

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
        EXPECT_EQ(expectedErrors.at(i), validator.error(i)->description());
    }
}

TEST(Validator, unnamedAndDuplicateNamedVariablesWithAndWithoutValidUnits)
{
    const std::vector<std::string> expectedErrors = {
        "Component 'fargo' contains multiple variables with the name 'margie'. Valid variable names must be unique to their component.",
        "CellML identifiers must not begin with a European numeric character [0-9].",
        "Variable does not have a valid name attribute.",
        "CellML identifiers must contain one or more basic Latin alphabetic characters.",
        "Variable 'margie' does not have a valid units attribute.",
        "Variable 'ransom' has an invalid units reference 'dollars' that does not correspond with a standard unit or units in the variable's parent component or model."};

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
        EXPECT_EQ(expectedErrors.at(i), validator.error(i)->description());
    }
}

TEST(Validator, invalidVariableInitialValuesAndInterfaces)
{
    const std::vector<std::string> expectedErrors = {
        "Variable 'candidate' has an invalid interface attribute value 'orange'.",
        "Variable 'candidate' has an invalid initial value 'trump'. Initial values must be a real number string or a variable reference."};

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
        EXPECT_EQ(expectedErrors.at(i), validator.error(i)->description());
    }
}

TEST(Validator, importUnits)
{
    const std::vector<std::string> expectedErrors = {
        "CellML identifiers must contain one or more basic Latin alphabetic characters.",
        "Imported units 'invalid_imported_units_in_this_model' does not have a valid units_ref attribute.",
        "Import of units 'invalid_imported_units_in_this_model' does not have a valid locator xlink:href attribute.",
        "Model 'model_name' contains multiple imported units from 'some-other-model.xml' with the same units_ref attribute 'units_in_that_model'.",
        "CellML identifiers must contain one or more basic Latin alphabetic characters.",
        "Imported units does not have a valid name attribute."};

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
    EXPECT_EQ(size_t(0), v.errorCount());

    // Invalid units import- missing refs
    libcellml::ImportSourcePtr imp2 = std::make_shared<libcellml::ImportSource>();
    libcellml::UnitsPtr importedUnits2 = std::make_shared<libcellml::Units>();
    importedUnits2->setName("invalid_imported_units_in_this_model");
    importedUnits2->setSourceUnits(imp2, "");
    m->addUnits(importedUnits2);
    v.validateModel(m);
    EXPECT_EQ(size_t(3), v.errorCount());

    // Invalid units import - duplicate refs
    libcellml::ImportSourcePtr imp3 = std::make_shared<libcellml::ImportSource>();
    imp3->setUrl("some-other-model.xml");
    libcellml::UnitsPtr importedUnits3 = std::make_shared<libcellml::Units>();
    importedUnits3->setName("duplicate_imported_units_in_this_model");
    importedUnits3->setSourceUnits(imp3, "units_in_that_model");
    m->addUnits(importedUnits3);
    v.validateModel(m);
    EXPECT_EQ(size_t(4), v.errorCount());

    // Invalid units import - unnamed units
    libcellml::ImportSourcePtr imp4 = std::make_shared<libcellml::ImportSource>();
    imp4->setUrl("some-other-different-model.xml");
    libcellml::UnitsPtr importedUnits4 = std::make_shared<libcellml::Units>();
    importedUnits4->setSourceUnits(imp4, "units_in_that_model");
    m->addUnits(importedUnits4);
    v.validateModel(m);
    EXPECT_EQ(size_t(6), v.errorCount());

    // Check for expected error messages
    for (size_t i = 0; i < v.errorCount(); ++i) {
        EXPECT_EQ(expectedErrors.at(i), v.error(i)->description());
    }
}

TEST(Validator, importComponents)
{
    const std::vector<std::string> expectedErrors = {
        "CellML identifiers must contain one or more basic Latin alphabetic characters.",
        "Imported component 'invalid_imported_component_in_this_model' does not have a valid component_ref attribute.",
        "Import of component 'invalid_imported_component_in_this_model' does not have a valid locator xlink:href attribute.",
        "CellML identifiers must contain one or more basic Latin alphabetic characters.",
        "Imported component does not have a valid name attribute.",
        "Import of component 'a_bad_imported_component' has an invalid URI in the href attribute."};

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
    EXPECT_EQ(size_t(0), v.errorCount());

    // Another valid component import
    libcellml::ImportSourcePtr imp2 = std::make_shared<libcellml::ImportSource>();
    imp2->setUrl("yet-another-other-model.xml");
    libcellml::ComponentPtr importedComponent2 = std::make_shared<libcellml::Component>();
    importedComponent2->setName("another_valid_imported_component_in_this_model");
    importedComponent2->setSourceComponent(imp2, "new_shiny_component_ref");
    m->addComponent(importedComponent2);
    v.validateModel(m);
    EXPECT_EQ(size_t(0), v.errorCount());

    // Invalid component import - missing ref to source component
    libcellml::ImportSourcePtr imp3 = std::make_shared<libcellml::ImportSource>();
    libcellml::ComponentPtr importedComponent3 = std::make_shared<libcellml::Component>();
    importedComponent3->setName("invalid_imported_component_in_this_model");
    importedComponent3->setSourceComponent(imp3, "");
    m->addComponent(importedComponent3);
    v.validateModel(m);
    EXPECT_EQ(size_t(3), v.errorCount());

    // Valid component import - two components imported from the same place is allowed
    libcellml::ImportSourcePtr imp4 = std::make_shared<libcellml::ImportSource>();
    imp4->setUrl("some-other-model.xml");
    libcellml::ComponentPtr importedComponent4 = std::make_shared<libcellml::Component>();
    importedComponent4->setName("duplicate_imported_component_in_this_model");
    importedComponent4->setSourceComponent(imp4, "component_in_that_model");
    m->addComponent(importedComponent4);
    v.validateModel(m);
    EXPECT_EQ(size_t(3), v.errorCount());

    // Invalid - name missing from component
    libcellml::ImportSourcePtr imp5 = std::make_shared<libcellml::ImportSource>();
    imp5->setUrl("some-other-different-model.xml");
    libcellml::ComponentPtr importedComponent5 = std::make_shared<libcellml::Component>();
    importedComponent5->setSourceComponent(imp5, "component_in_that_model");
    m->addComponent(importedComponent5);
    v.validateModel(m);
    EXPECT_EQ(size_t(5), v.errorCount());

    // Valid - two components from the same source is allowed
    libcellml::ImportSourcePtr imp7 = std::make_shared<libcellml::ImportSource>();
    imp7->setUrl("yet-another-other-model.xml");
    libcellml::ComponentPtr importedComponent7 = std::make_shared<libcellml::Component>();
    importedComponent7->setName("another_duplicate_imported_component");
    importedComponent7->setSourceComponent(imp7, "new_shiny_component_ref");
    m->addComponent(importedComponent7);
    v.validateModel(m);
    EXPECT_EQ(size_t(5), v.errorCount());

    // Valid - duplicate component_ref from a different source
    libcellml::ImportSourcePtr imp8 = std::make_shared<libcellml::ImportSource>();
    imp8->setUrl("yet-another-other-model.xml"); // source used before
    libcellml::ComponentPtr importedComponent8 = std::make_shared<libcellml::Component>();
    importedComponent8->setName("a_good_imported_component");
    importedComponent8->setSourceComponent(imp8, "component_in_that_model");
    m->addComponent(importedComponent8);
    v.validateModel(m);
    EXPECT_EQ(size_t(5), v.errorCount());

    // Invalid: component_ref url is not valid html
    libcellml::ImportSourcePtr imp9 = std::make_shared<libcellml::ImportSource>();
    imp9->setUrl("not @ valid url");
    libcellml::ComponentPtr importedComponent9 = std::make_shared<libcellml::Component>();
    importedComponent9->setName("a_bad_imported_component");
    importedComponent9->setSourceComponent(imp9, "component_in_some_model");
    m->addComponent(importedComponent9);
    v.validateModel(m);
    EXPECT_EQ(size_t(6), v.errorCount());

    // Check for expected error messages
    for (size_t i = 0; i < v.errorCount(); ++i) {
        EXPECT_EQ(expectedErrors.at(i), v.error(i)->description());
    }
}

TEST(Validator, validMath)
{
    const std::string math =
        "<math xmlns=\"http://www.w3.org/1998/Math/MathML\">\n"
        "  <apply>\n"
        "    <eq/>\n"
        "    <ci>C</ci>\n"
        "    <apply>\n"
        "      <plus/>\n"
        "      <ci>A</ci>\n"
        "      <ci>B</ci>\n"
        "    </apply>\n"
        "  </apply>\n"
        "</math>\n";

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
    EXPECT_EQ(size_t(0), v.errorCount());
}

TEST(Validator, invalidMath)
{
    const std::string math1 =
        "<math>\n"
        "  <invalid_xml></not_valid>\n"
        "</math>\n";
    const std::string math2 = "<invalid_math/>\n";
    const std::vector<std::string> expectedErrors = {
        "Opening and ending tag mismatch: invalid_xml line 2 and not_valid.",
        "Could not get a valid XML root node from the math on component 'componentName1'.",
        "Math root node is of invalid type 'invalid_math' on component 'componentName2'. A valid math root node should be of type 'math'."};

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
        EXPECT_EQ(expectedErrors.at(i), v.error(i)->description());
    }
}

TEST(Validator, invalidMathMLElements)
{
    const std::string math =
        "<math xmlns=\"http://www.w3.org/1998/Math/MathML\">\n"
        "  <apply>\n"
        "    <equals/>\n"
        "    <ci>C</ci>\n"
        "    <apply>\n"
        "      <addition/>\n"
        "      <ci>A</ci>\n"
        "      <ci>B</ci>\n"
        "    </apply>\n"
        "  </apply>\n"
        "</math>\n";
    const std::vector<std::string> expectedErrors = {
        "Math has a 'equals' element that is not a supported MathML element.",
        "Math has a 'addition' element that is not a supported MathML element.",
        "No declaration for element equals.",
        "No declaration for element addition."};
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
    EXPECT_EQ(size_t(6), v.errorCount());

    // Check for two expected error messages (see note above).
    for (size_t i = 0; i < 2; ++i) {
        EXPECT_EQ(expectedErrors.at(i), v.error(i)->description());
    }
}

TEST(Validator, invalidMathMLVariables)
{
    const std::string math =
        "<math xmlns=\"http://www.w3.org/1998/Math/MathML\">\n"
        "  <apply>\n"
        "    <eq/>\n"
        "    <ci>answer</ci>\n"
        "    <partialdiff/>\n"
        "    <apply>\n"
        "      <plus/>\n"
        "      <ci>A</ci>\n"
        "      <apply>\n"
        "        <plus/>\n"
        "        <bvar>\n"
        "          <ci>new_bvar</ci>\n"
        "        </bvar>\n"
        "        <apply>\n"
        "          <plus/>\n"
        "          <ci>   </ci>\n"
        "          <apply>\n"
        "            <plus/>\n"
        "            <ci><nonsense/></ci>\n"
        "            <apply>\n"
        "              <plus/>\n"
        "              <ci/>\n"
        "              <bvar>\n"
        "                <ci>\n"
        "                  <!-- Invalid bvar -->\n"
        "                  B\n"
        "                </ci>\n"
        "              </bvar>\n"
        "            </apply>\n"
        "          </apply>\n"
        "        </apply>\n"
        "      </apply>\n"
        "    </apply>\n"
        "  </apply>\n"
        "</math>\n";
    const std::vector<std::string> expectedErrors = {
        "Math has a 'partialdiff' element that is not a supported MathML element.",
        "Math has a 'nonsense' element that is not a supported MathML element.",
        "Math in component 'componentName' contains 'B' as a bvar ci element but it is already a variable name.",
        "MathML ci element has the child text 'answer', which does not correspond with any variable names present in component 'componentName' and is not a variable defined within a bvar element.",
        "MathML ci element has an empty child element.",
        "MathML ci element has no child.",
        "MathML ci element has an empty child element.",
        "No declaration for element nonsense.",
        "Element nonsense is not declared in ci list of possible children."};

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
        EXPECT_EQ(expectedErrors.at(i), v.error(i)->description());
    }
}

TEST(Validator, invalidMathMLCiAndCnElementsWithCellMLUnits)
{
    const std::string math =
        "<math xmlns:cellml=\"http://www.cellml.org/cellml/2.0#\" xmlns=\"http://www.w3.org/1998/Math/MathML\">\n"
        "  <apply>\n"
        "    <eq/>\n"
        "    <cn cellml:units=\"invalid\">oops</cn>\n"
        "    <apply>\n"
        "      <plus/>\n"
        "      <ci>A</ci>\n"
        "      <apply>\n"
        "        <plus/>\n"
        "        <bvar>\n"
        "          <ci cellml:units=\"dimensionless\" cellml:value=\"zero\">new_bvar</ci>\n"
        "        </bvar>\n"
        "        <apply>\n"
        "          <plus/>\n"
        "          <ci>   </ci>\n"
        "          <apply>\n"
        "            <plus/>\n"
        "            <ci>undefined_variable</ci>\n"
        "            <apply>\n"
        "              <plus/>\n"
        "              <ci/>\n"
        "              <bvar>\n"
        "                <ci cellml:units=\"9wayswrong\">B</ci>\n"
        "              </bvar>\n"
        "              <apply>\n"
        "                <plus/>\n"
        "                <cn>2.0</cn>\n"
        "              </apply>\n"
        "            </apply>\n"
        "          </apply>\n"
        "        </apply>\n"
        "      </apply>\n"
        "    </apply>\n"
        "  </apply>\n"
        "</math>\n";
    const std::vector<std::string> expectedErrors = {
        "Math in component 'componentName' contains 'B' as a bvar ci element but it is already a variable name.",
        "Math has a cn element with a cellml:units attribute 'invalid' that is not a valid reference to units in component 'componentName' or a standard unit.",
        "Math ci element has an invalid attribute type 'value' in the cellml namespace.",
        "MathML ci element has an empty child element.",
        "MathML ci element has the child text 'undefined_variable', which does not correspond with any variable names present in component 'componentName' and is not a variable defined within a bvar element.",
        "MathML ci element has no child.",
        "CellML identifiers must contain one or more basic Latin alphabetic characters.",
        "Math cn element with the value '2.0' does not have a valid cellml:units attribute.",
        "Namespace prefix cellml for value on ci is not defined.",
        "No declaration for attribute cellml:value of element ci."};

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
        EXPECT_EQ(expectedErrors.at(i), v.error(i)->description());
    }
}

TEST(Validator, parseAndValidateInvalidUnitErrors)
{
    const std::string input =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/2.0#\" name=\"asoiaf\">\n"
        "  <units name=\"ampere\"/>\n"
        "  <units name=\"north\"/>\n"
        "  <units name=\"stark\">\n"
        "    <unit units=\"volt\" prefix=\"mega\" multiplier=\"1000.0\"/>\n"
        "    <unit units=\"north\"/>\n"
        "    <unit units=\"ned\"/>\n"
        "    <unit units=\"king in the north\"/>\n"
        "    <unit prefix=\"wolf\" units=\"metre\"/>\n"
        "  </units>\n"
        "</model>\n";
    const std::vector<std::string> expectedErrors = {
        "Units is named 'ampere', which is a protected standard unit name.",
        "Units reference 'ned' in units 'stark' is not a valid reference to a local units or a standard unit type.",
        "CellML identifiers must not contain any characters other than [a-zA-Z0-9_].",
        "Unit in units 'stark' does not have a valid units reference.",
        "Prefix 'wolf' of a unit referencing 'metre' in units 'stark' is not a valid real number or a SI prefix.",
    };

    libcellml::Parser p;
    libcellml::ModelPtr m = p.parseModel(input);
    EXPECT_EQ(size_t(0), p.errorCount());

    libcellml::Validator v;
    v.validateModel(m);
    EXPECT_EQ(expectedErrors.size(), v.errorCount());

    for (size_t i = 0; i < v.errorCount(); ++i) {
        EXPECT_EQ(expectedErrors.at(i), v.error(i)->description());
    }
}

TEST(Validator, validateInvalidConnections)
{
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
    libcellml::Variable::addEquivalence(v1_1, v4);
    libcellml::Variable::addEquivalence(v2, v3);
    libcellml::Variable::addEquivalence(v5, v6); // valid here but duplicated below

    // Not valid connections
    libcellml::Variable::addEquivalence(v6, v5); // duplicated above, does not overwrite, skips silently

    // Make v4 a variable without a parent component.
    comp4->removeVariable(v4);
    // Remove all connections on v1_2, leaving dangling reciprocal connections.
    v1_2->removeAllEquivalences();

    v.validateModel(m);

    EXPECT_EQ(expectedErrors.size(), v.errorCount());
    for (size_t i = 0; i < v.errorCount(); ++i) {
        EXPECT_EQ(expectedErrors.at(i), v.error(i)->description());
    }
}

TEST(Validator, integerStrings)
{
    const std::string input =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/2.0#\" name=\"asoiaf\">\n"
        "  <component name=\"component\">\n"
        "    <variable name=\"variable\" units=\"dimensionless\"/>\n"
        "    <reset variable=\"variable\" order=\"1\">\n"
        "      <when order=\"200\">\n"
        "        <math xmlns=\"http://www.w3.org/1998/Math/MathML\">\n"
        "        </math>\n"
        "        <math xmlns=\"http://www.w3.org/1998/Math/MathML\">\n"
        "        </math>\n"
        "      </when>\n"
        "    </reset>\n"
        "    <reset variable=\"variable\" order=\"-1\">\n"
        "      <when order=\"200\">\n"
        "        <math xmlns=\"http://www.w3.org/1998/Math/MathML\">\n"
        "        </math>\n"
        "        <math xmlns=\"http://www.w3.org/1998/Math/MathML\">\n"
        "        </math>\n"
        "      </when>\n"
        "    </reset>\n"
        "    <reset variable=\"variable\" order=\"+1\">\n"
        "      <when order=\"200\">\n"
        "        <math xmlns=\"http://www.w3.org/1998/Math/MathML\">\n"
        "        </math>\n"
        "        <math xmlns=\"http://www.w3.org/1998/Math/MathML\">\n"
        "        </math>\n"
        "      </when>\n"
        "    </reset>\n"
        "    <reset variable=\"variable\" order=\"\">\n"
        "      <when order=\"200\">\n"
        "        <math xmlns=\"http://www.w3.org/1998/Math/MathML\">\n"
        "        </math>\n"
        "        <math xmlns=\"http://www.w3.org/1998/Math/MathML\">\n"
        "        </math>\n"
        "      </when>\n"
        "    </reset>\n"
        "    <reset variable=\"variable\" order=\"-\">\n"
        "      <when order=\"200\">\n"
        "        <math xmlns=\"http://www.w3.org/1998/Math/MathML\">\n"
        "        </math>\n"
        "        <math xmlns=\"http://www.w3.org/1998/Math/MathML\">\n"
        "        </math>\n"
        "      </when>\n"
        "    </reset>\n"
        "    <reset variable=\"variable\" order=\"odd\">\n"
        "      <when order=\"200\">\n"
        "        <math xmlns=\"http://www.w3.org/1998/Math/MathML\">\n"
        "        </math>\n"
        "        <math xmlns=\"http://www.w3.org/1998/Math/MathML\">\n"
        "        </math>\n"
        "      </when>\n"
        "    </reset>\n"
        "  </component>\n"
        "</model>\n";
    const std::vector<std::string> expectedParsingErrors = {
        "Reset in component 'component' referencing variable 'variable' has a non-integer order value '+1'.",
        "Reset in component 'component' referencing variable 'variable' has a non-integer order value ''.",
        "Reset in component 'component' referencing variable 'variable' has a non-integer order value '-'.",
        "Reset in component 'component' referencing variable 'variable' has a non-integer order value 'odd'.",
    };
    const std::vector<std::string> expectedValidationErrors = {
        "Reset in component 'component' does not have an order set, referencing variable 'variable'.",
        "Reset in component 'component' does not have an order set, referencing variable 'variable'.",
        "Reset in component 'component' does not have an order set, referencing variable 'variable'.",
        "Reset in component 'component' does not have an order set, referencing variable 'variable'.",
    };

    libcellml::Parser p;
    libcellml::ModelPtr m = p.parseModel(input);
    EXPECT_EQ(expectedParsingErrors.size(), p.errorCount());
    for (size_t i = 0; i < expectedParsingErrors.size(); ++i) {
        EXPECT_EQ(expectedParsingErrors.at(i), p.error(i)->description());
    }

    libcellml::Validator v;
    v.validateModel(m);
    EXPECT_EQ(expectedValidationErrors.size(), v.errorCount());
    for (size_t i = 0; i < expectedValidationErrors.size(); ++i) {
        EXPECT_EQ(expectedValidationErrors.at(i), v.error(i)->description());
    }
}

static const std::string emptyMath = "<math xmlns=\"http://www.w3.org/1998/Math/MathML\"/>\n";

TEST(Validator, resets)
{
    const std::vector<std::string> expectedErrors = {
        // "Component 'comp' contains multiple resets with order '300'.",
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
    w1->setCondition(emptyMath);
    w1->setValue(emptyMath);
    w2->setOrder(345);
    w2->setCondition(emptyMath);
    w2->setValue(emptyMath);

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
        EXPECT_EQ(expectedErrors.at(i), v.error(i)->description());
    }
}

TEST(Validator, whens)
{
    const std::vector<std::string> expectedErrors {
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
    w2->setCondition(emptyMath);
    w3->setOrder(250);
    w3->setValue(emptyMath);
    w4->setOrder(365);
    w4->setCondition(emptyMath);
    w4->setValue(emptyMath);

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
        EXPECT_EQ(expectedErrors.at(i), v.error(i)->description());
    }
}

TEST(Validator, validMathCnElements)
{
    const std::string math =
        "<math xmlns:cellml=\"http://www.cellml.org/cellml/2.0#\" xmlns=\"http://www.w3.org/1998/Math/MathML\">\n"
        "  <apply>\n"
        "    <eq/>\n"
        "    <ci>C</ci>\n"
        "    <apply>\n"
        "      <plus/>\n"
        "      <cn cellml:units=\"dimensionless\">3.44<sep/>2</cn>\n"
        "      <cn cellml:units=\"dimensionless\">-9.612</cn>\n"
        "    </apply>\n"
        "  </apply>\n"
        "</math>\n";

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
    EXPECT_EQ(size_t(0), v.errorCount());
}

TEST(Validator, validateNoCyclesSimple)
{
    // TODO Can two sibling variables in the same component be equivalent to one variable in another?

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

    std::string error = "Cyclic variables exist, 1 loop found (Component, Variable):\n"
                        "('component1', 'variable1') -> ('component2', 'variable2') -> ('component3', 'variable3') -> ('component1', 'variable1')\n";
    EXPECT_EQ(size_t(1), v.errorCount());
    EXPECT_EQ(error, v.error(0)->description());
}

TEST(Validator, validateNoCyclesComplicated)
{
    // TODO Can two sibling variables in the same component be equivalent to one variable in another?

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
    libcellml::Variable::addEquivalence(v3, v6); // Loop formed: 2, 4, 3, 6, 8, 2

    libcellml::Variable::addEquivalence(v6, v7);

    // NB Attached loops (ie: a-b-c-a and b-c-d-b) *are* detected and handled but return too many variations of the loop
    // (eg a-b-c-d, a-b-c, b-c-d, etc) to be viable as a hard-coded test, so have broken the attachment here.
    // libcellml::Variable::addEquivalence(v3, v7);    // Second attached loop: 3, 6, 7

    libcellml::Variable::addEquivalence(v9, v5);
    libcellml::Variable::addEquivalence(v5, v1_2);
    libcellml::Variable::addEquivalence(v1_2, v9); // Unattached loop: 5, 9, 1_2

    libcellml::Variable::addEquivalence(v11, v4);
    libcellml::Variable::addEquivalence(v11, v14);
    libcellml::Variable::addEquivalence(v11, v13);
    libcellml::Variable::addEquivalence(v11, v12);
    libcellml::Variable::addEquivalence(v12, v15);
    libcellml::Variable::addEquivalence(v12, v17);
    libcellml::Variable::addEquivalence(v17, v16); // Complicated tree, no loops

    libcellml::Variable::addEquivalence(v1_1, v8);
    libcellml::Variable::addEquivalence(v1_3, v2);
    // libcellml::Variable::addEquivalence(v1_4, v2);  // TODO Can two sibling variables in the same component be equivalent to one in another?

    v.validateModel(m);

    std::string error = "Cyclic variables exist, 2 loops found (Component, Variable):\n"
                        "('component1', 'variable1_2') -> ('component5', 'variable5') -> ('component9', 'variable9') -> ('component1', 'variable1_2')\n"
                        "('component2', 'variable2') -> ('component4', 'variable4') -> ('component3', 'variable3') -> ('component6', 'variable6') -> "
                        "('component8', 'variable8') -> ('component2', 'variable2')\n";
    EXPECT_EQ(size_t(1), v.errorCount());
    EXPECT_EQ(error, v.error(0)->description());
}

TEST(Validator, figureEightVariableDependency)
{
    libcellml::Validator v;
    libcellml::ModelPtr m = std::make_shared<libcellml::Model>();
    libcellml::ComponentPtr comp1 = std::make_shared<libcellml::Component>();
    libcellml::ComponentPtr comp2 = std::make_shared<libcellml::Component>();
    libcellml::ComponentPtr comp3 = std::make_shared<libcellml::Component>();
    libcellml::ComponentPtr comp4 = std::make_shared<libcellml::Component>();
    libcellml::ComponentPtr comp5 = std::make_shared<libcellml::Component>();
    libcellml::ComponentPtr comp6 = std::make_shared<libcellml::Component>();

    libcellml::VariablePtr v1 = std::make_shared<libcellml::Variable>();
    libcellml::VariablePtr v2 = std::make_shared<libcellml::Variable>();
    libcellml::VariablePtr v3 = std::make_shared<libcellml::Variable>();
    libcellml::VariablePtr v4 = std::make_shared<libcellml::Variable>();
    libcellml::VariablePtr v5 = std::make_shared<libcellml::Variable>();
    libcellml::VariablePtr v6 = std::make_shared<libcellml::Variable>();

    m->setName("modelName");
    comp1->setName("component1");
    comp2->setName("component2");
    comp3->setName("component3");
    comp4->setName("component4");
    comp5->setName("component5");
    comp6->setName("component6");

    v1->setName("variable1");
    v2->setName("variable2");
    v3->setName("variable3");
    v4->setName("variable4");
    v5->setName("variable5");
    v6->setName("variable6");

    v1->setUnits("dimensionless");
    v2->setUnits("dimensionless");
    v3->setUnits("dimensionless");
    v4->setUnits("dimensionless");
    v5->setUnits("dimensionless");
    v6->setUnits("dimensionless");

    comp1->addVariable(v1);
    comp2->addVariable(v2);
    comp3->addVariable(v3);
    comp4->addVariable(v4);
    comp5->addVariable(v5);
    comp6->addVariable(v6);

    m->addComponent(comp1);
    m->addComponent(comp2);
    m->addComponent(comp3);
    m->addComponent(comp4);
    m->addComponent(comp5);
    m->addComponent(comp6);

    libcellml::Variable::addEquivalence(v1, v2);
    libcellml::Variable::addEquivalence(v1, v3);
    libcellml::Variable::addEquivalence(v1, v4);
    libcellml::Variable::addEquivalence(v1, v5);
    libcellml::Variable::addEquivalence(v2, v3);
    libcellml::Variable::addEquivalence(v4, v5);

    v.validateModel(m);

    std::string error = "Cyclic variables exist, 2 loops found (Component, Variable):\n"
                        "('component1', 'variable1') -> ('component2', 'variable2') -> ('component3', 'variable3') -> ('component1', 'variable1')\n"
                        "('component1', 'variable1') -> ('component4', 'variable4') -> ('component5', 'variable5') -> ('component1', 'variable1')\n";
    EXPECT_EQ(size_t(1), v.errorCount());
    EXPECT_EQ(error, v.error(0)->description());
}

TEST(Validator, resetOrderUniqueness)
{
    const std::vector<std::string> expectedErrors = {
        "Non-unique reset order of '10' found within equivalent variable set:"
        "\n  - variable 'v1' in component 'c1' reset with order '10'"
        "\n  - variable 'v3' in component 'c3' reset with order '10'",
    };

    libcellml::ModelPtr m = std::make_shared<libcellml::Model>();
    libcellml::ComponentPtr c1 = std::make_shared<libcellml::Component>();
    libcellml::ComponentPtr c2 = std::make_shared<libcellml::Component>();
    libcellml::ComponentPtr c3 = std::make_shared<libcellml::Component>();
    libcellml::VariablePtr v1 = std::make_shared<libcellml::Variable>();
    libcellml::VariablePtr v2 = std::make_shared<libcellml::Variable>();
    libcellml::VariablePtr v3 = std::make_shared<libcellml::Variable>();
    libcellml::ResetPtr r1 = std::make_shared<libcellml::Reset>();
    libcellml::ResetPtr r2 = std::make_shared<libcellml::Reset>();
    libcellml::ResetPtr r3 = std::make_shared<libcellml::Reset>();

    libcellml::WhenPtr w1 = std::make_shared<libcellml::When>();
    libcellml::WhenPtr w2 = std::make_shared<libcellml::When>();
    libcellml::WhenPtr w3 = std::make_shared<libcellml::When>();

    w1->setOrder(0);
    w1->setCondition(emptyMath);
    w1->setValue(emptyMath);
    w2->setOrder(0);
    w2->setCondition(emptyMath);
    w2->setValue(emptyMath);
    w3->setOrder(0);
    w3->setCondition(emptyMath);
    w3->setValue(emptyMath);
    r1->addWhen(w1);
    r2->addWhen(w2);
    r3->addWhen(w3);

    r1->setOrder(10);
    r1->setVariable(v1);
    v1->setName("v1");
    v1->setUnits("dimensionless");
    c1->setName("c1");
    c1->addVariable(v1);
    c1->addReset(r1);

    r2->setOrder(20);
    r2->setVariable(v2);
    v2->setName("v2");
    v2->setUnits("dimensionless");
    c2->setName("c2");
    c2->addVariable(v2);
    c2->addReset(r2);

    r3->setOrder(10); // duplicated order
    r3->setVariable(v3);
    v3->setName("v3");
    v3->setUnits("dimensionless");
    c3->setName("c3");
    c3->addVariable(v3);
    c3->addReset(r3);

    libcellml::Variable::addEquivalence(v1, v2);
    libcellml::Variable::addEquivalence(v2, v3);

    m->setName("main");
    m->addComponent(c1);
    m->addComponent(c2);
    m->addComponent(c3);

    libcellml::Validator v;
    v.validateModel(m);

    EXPECT_EQ(expectedErrors.size(), v.errorCount());
    for (size_t i = 0; i < expectedErrors.size(); ++i) {
        EXPECT_EQ(expectedErrors.at(i), v.error(i)->description());
    }
}

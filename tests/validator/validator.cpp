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
        "Component does not have a valid name attribute."};
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

    checkExpectedErrors(expectedErrors, validator);
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

    checkExpectedErrors(expectedErrors, validator);
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

    checkExpectedErrors(expectedErrors, validator);
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

    checkExpectedErrors(expectedErrors, validator);
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

    checkExpectedErrors(expectedErrors, v);
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

    checkExpectedErrors(expectedErrors, v);
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

    checkExpectedErrors(expectedErrors, v);
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
    // Note: the MathML DTD also gives errors that list every possible operator when an
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
        "MathML ci element has the child text 'answer' which does not correspond with any variable names present in component 'componentName' and is not a variable defined within a bvar element.",
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

    checkExpectedErrors(expectedErrors, v);
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
        "MathML ci element has the child text 'undefined_variable' which does not correspond with any variable names present in component 'componentName' and is not a variable defined within a bvar element.",
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

    // Note: we are not checking the exact message of the last error as older
    //       versions of libxml may not include the namespace in the error
    //       message.
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
        "Units is named 'ampere' which is a protected standard unit name.",
        "Units reference 'ned' in units 'stark' is not a valid reference to a local units or a standard unit type.",
        "CellML identifiers must not contain any characters other than [a-zA-Z0-9_].",
        "Unit in units 'stark' does not have a valid units reference.",
        "Prefix 'wolf' of a unit referencing 'metre' in units 'stark' is not a valid integer or an SI prefix."};

    libcellml::Parser p;
    libcellml::ModelPtr m = p.parseModel(input);
    EXPECT_EQ(size_t(0), p.errorCount());

    libcellml::Validator v;
    v.validateModel(m);

    checkExpectedErrors(expectedErrors, v);
}

// TODO removed until the removeVariable bug is fixed ...
// TEST(Validator, validateInvalidConnectionsParentlessVariable)
// {
//     const std::vector<std::string> expectedErrors = {
//         "Variable 'variable1' has an equivalent variable 'variable2' which does not reciprocally have 'variable1' set as an equivalent variable.",
//     };

//     libcellml::Validator v;
//     libcellml::ModelPtr m = std::make_shared<libcellml::Model>();
//     libcellml::ComponentPtr comp1 = std::make_shared<libcellml::Component>();
//     libcellml::ComponentPtr comp2 = std::make_shared<libcellml::Component>();

//     libcellml::VariablePtr v1 = std::make_shared<libcellml::Variable>();
//     libcellml::VariablePtr v2 = std::make_shared<libcellml::Variable>();

//     m->setName("modelName");
//     comp1->setName("component1");
//     comp2->setName("component2");

//     v1->setName("variable1");
//     v2->setName("variable2");

//     v1->setUnits("dimensionless");
//     v2->setUnits("dimensionless");

//     v1->setInterfaceType("public");
//     v2->setInterfaceType("public");

//     comp1->addVariable(v1);
//     comp2->addVariable(v2);
//     m->addComponent(comp1);
//     m->addComponent(comp2);

//     // Valid connections.
//     libcellml::Variable::addEquivalence(v1, v2);

//     // Not valid connections
//     libcellml::Variable::addEquivalence(v2, v1); // opposite to above, equivalence already made so effectively a no-op.

//     // Make v4 a variable without a parent component.
//     comp2->removeVariable(v2);

//     std::cout<<comp2->variableCount()<<"\n";
//     std::cout<<v2->parentComponent()->name()<<"\n";

//     v.validateModel(m);
//     printErrors(v);

//     EXPECT_EQ(expectedErrors.size(), v.errorCount());
//     for (size_t i = 0; i < v.errorCount(); ++i) {
//         EXPECT_EQ(expectedErrors.at(i), v.error(i)->description());
//     }
// }

TEST(Validator, equivalentVariablesInSameComponent)
{
    const std::vector<std::string> expectedErrors = {
        "Variable 'variable2' is an equivalent variable to 'variable1' but they are in the same component, 'component1'.",
        "Variable 'variable1' is an equivalent variable to 'variable2' but they are in the same component, 'component1'.",
    };

    libcellml::Validator v;
    libcellml::ModelPtr m = std::make_shared<libcellml::Model>();
    libcellml::ComponentPtr comp1 = std::make_shared<libcellml::Component>();
    libcellml::ComponentPtr comp2 = std::make_shared<libcellml::Component>();

    libcellml::VariablePtr v1 = std::make_shared<libcellml::Variable>();
    libcellml::VariablePtr v2 = std::make_shared<libcellml::Variable>();

    m->setName("modelName");
    comp1->setName("component1");

    v1->setName("variable1");
    v2->setName("variable2");

    v1->setUnits("dimensionless");
    v2->setUnits("dimensionless");

    v1->setInterfaceType("public");
    v2->setInterfaceType("public");

    comp1->addVariable(v1);
    comp1->addVariable(v2);
    m->addComponent(comp1);

    // Equivalence for variables in the same component.
    libcellml::Variable::addEquivalence(v1, v2);

    v.validateModel(m);
    checkExpectedErrors(expectedErrors, v);
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

    checkExpectedErrors(expectedParsingErrors, p);

    libcellml::Validator v;
    v.validateModel(m);

    checkExpectedErrors(expectedValidationErrors, v);
}

TEST(Validator, validReset)
{
    libcellml::ModelPtr m = std::make_shared<libcellml::Model>();
    libcellml::ComponentPtr c = std::make_shared<libcellml::Component>();
    libcellml::VariablePtr v = std::make_shared<libcellml::Variable>();

    libcellml::ResetPtr r = std::make_shared<libcellml::Reset>();
    libcellml::WhenPtr w = std::make_shared<libcellml::When>();

    w->setOrder(1);
    w->setCondition(EMPTY_MATH);
    w->setValue(EMPTY_MATH);

    c->setName("comp");
    v->setName("var");
    v->setUnits("second");

    r->addWhen(w);
    r->setOrder(3);
    r->setVariable(v);

    c->addVariable(v);
    c->addReset(r);

    m->setName("main");
    m->addComponent(c);

    libcellml::Validator validator;
    validator.validateModel(m);

    EXPECT_EQ(size_t(0), validator.errorCount());
}

TEST(Validator, invalidResets)
{
    const std::vector<std::string> expectedErrors = {
        "Reset in component 'comp' with order '300' does not reference a variable.",
        "Reset in component 'comp' does not have an order set, does not reference a variable.",
        "Reset in component 'comp' does not have an order set, does not reference a variable.",
        "Reset in component 'comp' with order '400' referencing variable 'var' does not have at least one child When.",
    };

    libcellml::ModelPtr m = std::make_shared<libcellml::Model>();
    libcellml::ComponentPtr c = std::make_shared<libcellml::Component>();
    libcellml::VariablePtr v = std::make_shared<libcellml::Variable>();

    libcellml::ResetPtr r1 = std::make_shared<libcellml::Reset>();
    libcellml::ResetPtr r2 = std::make_shared<libcellml::Reset>();
    libcellml::ResetPtr r3 = std::make_shared<libcellml::Reset>();

    libcellml::WhenPtr w = std::make_shared<libcellml::When>();

    w->setOrder(776);
    w->setCondition(EMPTY_MATH);
    w->setValue(EMPTY_MATH);

    r1->setOrder(300);
    r1->addWhen(w);

    r2->addWhen(w);

    r3->setOrder(400);
    r3->setVariable(v);

    c->setName("comp");
    v->setName("var");
    v->setUnits("second");

    c->addVariable(v);
    c->addReset(r1);
    c->addReset(r2);
    c->addReset(r3);

    m->setName("main");
    m->addComponent(c);

    libcellml::Validator validator;
    validator.validateModel(m);

    checkExpectedErrors(expectedErrors, validator);
}

TEST(Validator, resetsWithDuplicatedOrder)
{
    const std::vector<std::string> expectedErrors = {
        "Non-unique reset order of '153' found within the reset set of the variable 'var' in component 'comp'.",
    };

    libcellml::ModelPtr m = std::make_shared<libcellml::Model>();
    libcellml::ComponentPtr c = std::make_shared<libcellml::Component>();
    libcellml::VariablePtr v = std::make_shared<libcellml::Variable>();

    libcellml::ResetPtr r1 = std::make_shared<libcellml::Reset>();
    libcellml::ResetPtr r2 = std::make_shared<libcellml::Reset>();

    libcellml::WhenPtr w = std::make_shared<libcellml::When>();

    w->setOrder(776);
    w->setCondition(EMPTY_MATH);
    w->setValue(EMPTY_MATH);

    r1->setOrder(153);
    r1->addWhen(w);
    r1->setVariable(v);

    r2->setOrder(153);
    r2->addWhen(w);
    r2->setVariable(v);

    c->setName("comp");
    v->setName("var");
    v->setUnits("second");

    c->addVariable(v);
    c->addReset(r1);
    c->addReset(r2);

    m->setName("main");
    m->addComponent(c);

    libcellml::Validator validator;
    validator.validateModel(m);

    checkExpectedErrors(expectedErrors, validator);
}

TEST(Validator, resetsWithDuplicatedOrderAcrossConnectedVariables)
{
    const std::vector<std::string> expectedErrors = {
        "Non-unique reset order of '236' found within equivalent variable set:\n  - variable 'var2' in component 'comp2' reset with order '236'\n  - variable 'var1' in component 'comp1' reset with order '236'.",
    };

    libcellml::ModelPtr m = std::make_shared<libcellml::Model>();
    libcellml::ComponentPtr c1 = std::make_shared<libcellml::Component>();
    libcellml::ComponentPtr c2 = std::make_shared<libcellml::Component>();
    libcellml::VariablePtr v1 = std::make_shared<libcellml::Variable>();
    libcellml::VariablePtr v2 = std::make_shared<libcellml::Variable>();

    libcellml::ResetPtr r1 = std::make_shared<libcellml::Reset>();
    libcellml::ResetPtr r2 = std::make_shared<libcellml::Reset>();

    libcellml::WhenPtr w = std::make_shared<libcellml::When>();

    w->setOrder(776);
    w->setCondition(EMPTY_MATH);
    w->setValue(EMPTY_MATH);

    r1->setOrder(236);
    r1->addWhen(w);
    r1->setVariable(v1);

    r2->setOrder(236);
    r2->addWhen(w);
    r2->setVariable(v2);

    c1->setName("comp1");
    c2->setName("comp2");

    v1->setName("var1");
    v1->setUnits("second");
    v1->setInterfaceType("public");
    v2->setName("var2");
    v2->setUnits("second");
    v2->setInterfaceType("public");

    c1->addVariable(v1);
    c1->addReset(r1);

    c2->addVariable(v2);
    c2->addReset(r2);

    m->setName("main");
    m->addComponent(c1);
    m->addComponent(c2);

    libcellml::Variable::addEquivalence(v1, v2);

    libcellml::Validator validator;
    validator.validateModel(m);

    checkExpectedErrors(expectedErrors, validator);
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
    r2->addWhen(w2);
    r2->addWhen(w3);
    r3->setOrder(500);
    r3->addWhen(w4);
    r2->setVariable(var);
    r3->setVariable(var);

    c->setName("comp");
    var->setName("var");
    var->setUnits("second");

    w2->setOrder(250);
    w2->setCondition(EMPTY_MATH);
    w3->setOrder(250);
    w3->setValue(EMPTY_MATH);
    w4->setOrder(365);
    w4->setCondition(EMPTY_MATH);
    w4->setValue(EMPTY_MATH);

    c->addVariable(var);
    c->addReset(r1);
    c->addReset(r2);
    c->addReset(r3);

    m->setName("main");
    m->addComponent(c);

    libcellml::Validator v;
    v.validateModel(m);

    checkExpectedErrors(expectedErrors, v);
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

TEST(Validator, equivalentUnitsInSameComponent)
{
    libcellml::Validator validator;
    libcellml::ModelPtr model = std::make_shared<libcellml::Model>();
    libcellml::ComponentPtr component = std::make_shared<libcellml::Component>();
    libcellml::VariablePtr variable1 = std::make_shared<libcellml::Variable>();
    libcellml::VariablePtr variable2 = std::make_shared<libcellml::Variable>();
    libcellml::Variable::addEquivalence(variable1, variable2);

    const std::vector<std::string> expectedErrors = {
        "Variable 'variable2' is an equivalent variable to 'variable1' but they are in the same component, 'component'.",
        "Variable 'variable1' is an equivalent variable to 'variable2' but they are in the same component, 'component'."};

    variable1->setName("variable1");
    variable1->setUnits("dimensionless");
    variable2->setName("variable2");
    variable2->setUnits("dimensionless");
    variable1->setInterfaceType("public");
    variable2->setInterfaceType("public");
    component->setName("component");
    component->addVariable(variable1);
    component->addVariable(variable2);
    model->setName("modelName");
    model->addComponent(component);

    validator.validateModel(model);
    EXPECT_EQ(expectedErrors.size(), validator.errorCount());
    for (size_t i = 0; i < expectedErrors.size(); ++i) {
        EXPECT_EQ(expectedErrors.at(i), validator.error(i)->description());
    }
}

TEST(Validator, removeUsSpellingsFromUnits)
{
    const std::vector<std::string> expectedErrors = {
        "Variable 'tomayto' has units of 'testunit1' and an equivalent variable 'tomahto' has units of 'testunit2' which do not match. The mismatch is: metre^1.",
        "Variable 'tomahto' has units of 'testunit2' and an equivalent variable 'tomayto' has units of 'testunit1' which do not match. The mismatch is: metre^-1.",
        "Units reference 'meter' in units 'testunit2' is not a valid reference to a local units or a standard unit type.",
    };
    libcellml::Validator validator;
    libcellml::ModelPtr m = std::make_shared<libcellml::Model>();
    libcellml::ComponentPtr comp1 = std::make_shared<libcellml::Component>();
    libcellml::ComponentPtr comp2 = std::make_shared<libcellml::Component>();

    libcellml::VariablePtr v1 = std::make_shared<libcellml::Variable>();
    libcellml::VariablePtr v2 = std::make_shared<libcellml::Variable>();

    v1->setName("tomayto");
    v2->setName("tomahto");
    m->setName("callthewholethingoff");
    comp1->addVariable(v1);
    comp2->addVariable(v2);
    comp1->setName("comp1");
    comp2->setName("comp2");
    m->addComponent(comp1);
    m->addComponent(comp2);

    // u1 = u2: different spelling of meter/metre.
    libcellml::UnitsPtr u1 = std::make_shared<libcellml::Units>();
    u1->setName("testunit1");
    u1->addUnit("metre");
    libcellml::UnitsPtr u2 = std::make_shared<libcellml::Units>();
    u2->setName("testunit2");
    u2->addUnit("meter");

    v1->setUnits(u1);
    v2->setUnits(u2);
    v1->setInterfaceType("public");
    v2->setInterfaceType("public");
    m->addUnits(u1);
    m->addUnits(u2);

    // This one is now an error.
    libcellml::Variable::addEquivalence(v1, v2);
    validator.validateModel(m);

    checkExpectedErrors(expectedErrors, validator);
}

TEST(Validator, unitEquivalenceStandardUnitsToBaseUnits)
{
    libcellml::Validator validator;
    libcellml::ModelPtr m = std::make_shared<libcellml::Model>();
    libcellml::ComponentPtr comp1 = std::make_shared<libcellml::Component>();
    libcellml::ComponentPtr comp2 = std::make_shared<libcellml::Component>();
    libcellml::VariablePtr v1 = std::make_shared<libcellml::Variable>();
    libcellml::VariablePtr v2 = std::make_shared<libcellml::Variable>();
    libcellml::UnitsPtr base = std::make_shared<libcellml::Units>();
    libcellml::UnitsPtr standard = std::make_shared<libcellml::Units>();

    const std::map<std::string, std::map<std::string, double>> standardToBaseUnitList = {
        {"ampere", {{"ampere", 1.0}}},
        {"becquerel", {{"second", -1.0}}},
        {"candela", {{"candela", 1.0}}},
        {"coulomb", {{"ampere", -1.0}, {"second", 1.0}}},
        {"dimensionless", {{"dimensionless", 1.0}}},
        {"farad", {{"ampere", 2.0}, {"kilogram", -1.0}, {"metre", -2.0}, {"second", -4.0}}},
        {"gram", {{"kilogram", 1.0}}},
        {"gray", {{"metre", 2.0}, {"second", -2.0}}},
        {"henry", {{"ampere", -2.0}, {"kilogram", 1.0}, {"metre", 2.0}, {"second", -2.0}}},
        {"hertz", {{"second", -1.0}}},
        {"joule", {{"kilogram", 1.0}, {"metre", 2.0}, {"second", -2.0}}},
        {"katal", {{"mole", 1.0}, {"second", -1.0}}},
        {"kelvin", {{"kelvin", 1.0}}},
        {"kilogram", {{"kilogram", 1.0}}},
        {"litre", {{"metre", 3.0}}},
        {"lumen", {{"candela", 1.0}}},
        {"lux", {{"candela", 1.0}, {"metre", -2.0}}},
        {"metre", {{"metre", 1.0}}},
        {"mole", {{"mole", 1.0}}},
        {"newton", {{"kilogram", 1.0}, {"metre", 1.0}, {"second", -2.0}}},
        {"ohm", {{"ampere", -2.0}, {"kilogram", 1.0}, {"metre", 2.0}, {"second", -3.0}}},
        {"pascal", {{"kilogram", 1.0}, {"metre", -1.0}, {"second", -2.0}}},
        {"radian", {{"dimensionless", 1.0}}},
        {"second", {{"second", 1.0}}},
        {"siemens", {{"ampere", 2.0}, {"kilogram", -1.0}, {"metre", -2.0}, {"second", 3.0}}},
        {"sievert", {{"metre", 2.0}, {"second", -2.0}}},
        {"steradian", {{"dimensionless", 1.0}}},
        {"tesla", {{"ampere", -1.0}, {"kilogram", 1.0}, {"second", -2.0}}},
        {"volt", {{"ampere", -1.0}, {"kilogram", 1.0}, {"metre", 2.0}, {"second", -3.0}}},
        {"watt", {{"kilogram", 1.0}, {"metre", 2.0}, {"second", -3.0}}},
        {"weber", {{"ampere", -1.0}, {"kilogram", 1.0}, {"metre", 2.0}, {"second", -2.0}}}};

    v1->setName("tomayto");
    v2->setName("tomahto");
    m->setName("callthewholethingoff");
    comp1->addVariable(v1);
    comp2->addVariable(v2);
    comp1->setName("comp1");
    comp2->setName("comp2");
    m->addComponent(comp1);
    m->addComponent(comp2);
    base->setName("base");
    standard->setName("standard");
    v1->setUnits(base);
    v2->setUnits(standard);
    m->addUnits(base);
    m->addUnits(standard);

    for (const auto &line : standardToBaseUnitList) {
        standard->removeAllUnits();
        base->removeAllUnits();
        standard->addUnit(line.first);
        for (const auto &baseUnits : line.second) {
            base->addUnit(baseUnits.first, 0, baseUnits.second, 1.0);
        }
        validator.validateModel(m);
        EXPECT_EQ(size_t(0), validator.errorCount());
    }
}

TEST(Validator, unitEquivalenceBasicDimensionlessUnits)
{
    libcellml::Validator validator;
    libcellml::ModelPtr m = std::make_shared<libcellml::Model>();
    libcellml::ComponentPtr comp1 = std::make_shared<libcellml::Component>();
    libcellml::ComponentPtr comp2 = std::make_shared<libcellml::Component>();

    libcellml::VariablePtr v1 = std::make_shared<libcellml::Variable>();
    libcellml::VariablePtr v2 = std::make_shared<libcellml::Variable>();

    v1->setName("tomayto");
    v2->setName("tomahto");

    v1->setInterfaceType("public");
    v2->setInterfaceType("public");

    m->setName("callthewholethingoff");
    comp1->addVariable(v1);
    comp2->addVariable(v2);
    comp1->setName("comp1");
    comp2->setName("comp2");
    m->addComponent(comp1);
    m->addComponent(comp2);

    // u1 = u2: testing that cancelled units become dimensionless.
    libcellml::UnitsPtr u1 = std::make_shared<libcellml::Units>();
    u1->setName("metrepermetre");
    u1->addUnit("metre");
    u1->addUnit("metre", -1.0);
    libcellml::UnitsPtr u2 = std::make_shared<libcellml::Units>();
    u2->setName("ratio");
    u2->addUnit("dimensionless");

    v1->setUnits(u1);
    v2->setUnits(u2);

    m->addUnits(u1);
    m->addUnits(u2);

    libcellml::Variable::addEquivalence(v1, v2);

    validator.validateModel(m);
    EXPECT_EQ(size_t(0), validator.errorCount());
}

TEST(Validator, unitEquivalenceDimensionlessUnits)
{
    libcellml::Validator validator;
    libcellml::ModelPtr m = std::make_shared<libcellml::Model>();
    libcellml::ComponentPtr comp1 = std::make_shared<libcellml::Component>();
    libcellml::ComponentPtr comp2 = std::make_shared<libcellml::Component>();
    libcellml::ComponentPtr comp3 = std::make_shared<libcellml::Component>();

    libcellml::VariablePtr v1 = std::make_shared<libcellml::Variable>();
    libcellml::VariablePtr v2 = std::make_shared<libcellml::Variable>();
    libcellml::VariablePtr v3 = std::make_shared<libcellml::Variable>();

    v1->setName("tomayto");
    v2->setName("tomahto");
    v3->setName("tomaat");
    v1->setInterfaceType("public");
    v2->setInterfaceType("public");
    v3->setInterfaceType("public");

    m->setName("callthewholethingoff");
    comp1->addVariable(v1);
    comp2->addVariable(v2);
    comp3->addVariable(v3);
    comp1->setName("comp1");
    comp2->setName("comp2");
    comp3->setName("comp3");
    m->addComponent(comp1);
    m->addComponent(comp2);
    m->addComponent(comp3);

    // u1 = u2 = u3: testing that cancelled units become dimensionless and equivalent to radians, steradians, etc.
    libcellml::UnitsPtr u1 = std::make_shared<libcellml::Units>();
    u1->setName("testunit5");
    u1->addUnit("metre", -2.0);
    u1->addUnit("metre", 2.0);
    libcellml::UnitsPtr u2 = std::make_shared<libcellml::Units>();
    u2->setName("testunit6");
    u2->addUnit("dimensionless");
    libcellml::UnitsPtr u3 = std::make_shared<libcellml::Units>();
    u3->setName("testunit7");
    u3->addUnit("steradian");

    v1->setUnits(u1);
    v2->setUnits(u2);
    v3->setUnits(u3);

    m->addUnits(u1);
    m->addUnits(u2);
    m->addUnits(u3);

    libcellml::Variable::addEquivalence(v1, v2);
    libcellml::Variable::addEquivalence(v2, v3);

    validator.validateModel(m);
    EXPECT_EQ(size_t(0), validator.errorCount());
}

TEST(Validator, unitEquivalenceMultiplierPrefix)
{
    libcellml::Validator validator;
    libcellml::ModelPtr m = std::make_shared<libcellml::Model>();
    libcellml::ComponentPtr comp1 = std::make_shared<libcellml::Component>();
    libcellml::ComponentPtr comp2 = std::make_shared<libcellml::Component>();
    libcellml::ComponentPtr comp3 = std::make_shared<libcellml::Component>();

    libcellml::VariablePtr v1 = std::make_shared<libcellml::Variable>();
    libcellml::VariablePtr v2 = std::make_shared<libcellml::Variable>();
    libcellml::VariablePtr v3 = std::make_shared<libcellml::Variable>();

    v1->setName("tomayto");
    v2->setName("tomahto");
    v3->setName("tomaat");

    m->setName("callthewholethingoff");
    comp1->setName("comp1");
    comp2->setName("comp2");
    comp3->setName("comp3");
    m->addComponent(comp1);
    m->addComponent(comp2);
    m->addComponent(comp3);

    // u1 = u2 = u3: testing multiplier or prefix don't affect base unit equivalence.
    libcellml::UnitsPtr u1 = std::make_shared<libcellml::Units>();
    u1->setName("testunit10");
    u1->addUnit("gram", 2, 1000.0);
    libcellml::UnitsPtr u2 = std::make_shared<libcellml::Units>();
    u2->setName("testunit11");
    u2->addUnit("kilogram", 2.0);
    libcellml::UnitsPtr u3 = std::make_shared<libcellml::Units>();
    u3->setName("testunit12");
    u3->addUnit("gram", "kilo", 2.0);

    v1->setUnits(u1);
    v2->setUnits(u2);
    v3->setUnits(u3);

    m->addUnits(u1);
    m->addUnits(u2);
    m->addUnits(u3);

    libcellml::Variable::addEquivalence(v1, v2);
    libcellml::Variable::addEquivalence(v2, v3);

    validator.validateModel(m);
    EXPECT_EQ(size_t(0), validator.errorCount());
}

TEST(Validator, unitEquivalenceInvalidNestedUnits)
{
    std::vector<std::string> expectedErrors = {
        "Variable 'pjs' has units of 'testunit13' and an equivalent variable 'pajamas' has units of 'testunit14' which do not match. The mismatch is: metre^1.",
        "Variable 'pajamas' has units of 'testunit14' and an equivalent variable 'pjs' has units of 'testunit13' which do not match. The mismatch is: metre^-1.",
    };

    libcellml::Validator validator;
    libcellml::ModelPtr m = std::make_shared<libcellml::Model>();
    libcellml::ComponentPtr comp1 = std::make_shared<libcellml::Component>();
    libcellml::ComponentPtr comp2 = std::make_shared<libcellml::Component>();

    libcellml::VariablePtr v13 = std::make_shared<libcellml::Variable>();
    libcellml::VariablePtr v14 = std::make_shared<libcellml::Variable>();

    v13->setName("pjs");
    v14->setName("pajamas");
    v13->setInterfaceType("public");
    v14->setInterfaceType("public");

    comp1->setName("isay");
    comp2->setName("yousay");

    m->setName("callthewholethingoff");

    comp1->addVariable(v13);
    comp2->addVariable(v14);

    m->addComponent(comp1);
    m->addComponent(comp2);

    libcellml::UnitsPtr u1 = std::make_shared<libcellml::Units>();
    u1->setName("testunit1");
    u1->addUnit("metre");

    // u13 != u14: testing that the mismatch is reported correctly.
    libcellml::UnitsPtr u13 = std::make_shared<libcellml::Units>();
    u13->setName("testunit13");
    u13->addUnit("testunit1", "kilo", 2.0);
    libcellml::UnitsPtr u14 = std::make_shared<libcellml::Units>();
    u14->setName("testunit14");
    u14->addUnit("testunit1", 1.0);

    v13->setUnits(u13);
    v14->setUnits(u14);

    m->addUnits(u1);
    m->addUnits(u13);
    m->addUnits(u14);

    // Off by (metre)^1.
    libcellml::Variable::addEquivalence(v13, v14);

    validator.validateModel(m);

    EXPECT_EQ(expectedErrors.size(), validator.errorCount());
    for (size_t i = 0; i < validator.errorCount(); ++i) {
        EXPECT_EQ(expectedErrors.at(i), validator.error(i)->description());
    }
}

TEST(Validator, unitEquivalenceComplicatedValidNestedUnits)
{
    libcellml::Validator validator;
    libcellml::ModelPtr m = std::make_shared<libcellml::Model>();
    libcellml::ComponentPtr comp1 = std::make_shared<libcellml::Component>();
    libcellml::ComponentPtr comp2 = std::make_shared<libcellml::Component>();

    libcellml::VariablePtr v1 = std::make_shared<libcellml::Variable>();
    libcellml::VariablePtr v8 = std::make_shared<libcellml::Variable>();
    libcellml::VariablePtr v9 = std::make_shared<libcellml::Variable>();

    v1->setName("tomayto");
    v8->setName("neether");
    v9->setName("nyther");
    v1->setInterfaceType("public");
    v8->setInterfaceType("public");
    v9->setInterfaceType("public");

    comp1->setName("isay");
    comp2->setName("yousay");

    m->setName("callthewholethingoff");

    comp1->addVariable(v1);
    comp1->addVariable(v8);
    comp2->addVariable(v9);

    m->addComponent(comp1);
    m->addComponent(comp2);

    libcellml::UnitsPtr u1 = std::make_shared<libcellml::Units>();
    u1->setName("testunit1");
    u1->addUnit("metre");

    // u8 = u9: testing more complicated compound units, newton/(sievert.pascal) = second^2.radian^3.steradian^-4.
    libcellml::UnitsPtr u8 = std::make_shared<libcellml::Units>();
    u8->setName("testunit8");
    u8->addUnit("newton", 1.0);
    u8->addUnit("pascal", -1.0);
    u8->addUnit("sievert", -1.0);
    libcellml::UnitsPtr u9 = std::make_shared<libcellml::Units>();
    u9->setName("testunit9");
    u9->addUnit("second", 2.0);
    u9->addUnit("radian", -4.0);
    u9->addUnit("steradian", 2.0);

    v1->setUnits(u1);
    v8->setUnits(u8);
    v9->setUnits(u9);

    m->addUnits(u1);
    m->addUnits(u8);
    m->addUnits(u9);

    // This one is fine but complicated: newton/(sievert.pascal) = second^2.radian^3.steradian^-4.
    libcellml::Variable::addEquivalence(v8, v9);

    validator.validateModel(m);

    EXPECT_EQ(size_t(0), validator.errorCount());
}

TEST(Validator, unitEquivalenceExponentMultiplierPrefixExponent)
{
    // This test is intended to demonstrate that the effect of different multiplicator sources (prefix, multiplier term)
    // does not affect the equivalence of the underlying base variables.
    // TODO: when warnings are implemented then the multiplier testing can be reinstated.

    libcellml::Validator validator;
    libcellml::ModelPtr model = std::make_shared<libcellml::Model>();

    libcellml::ComponentPtr comp1 = std::make_shared<libcellml::Component>();
    libcellml::ComponentPtr comp2 = std::make_shared<libcellml::Component>();

    libcellml::VariablePtr v1 = std::make_shared<libcellml::Variable>();
    libcellml::VariablePtr v2 = std::make_shared<libcellml::Variable>();

    v1->setName("v1");
    v2->setName("v2");
    v1->setInterfaceType("public");
    v2->setInterfaceType("public");

    // millimetres
    libcellml::UnitsPtr u1 = std::make_shared<libcellml::Units>();
    u1->setName("u1");
    u1->addUnit("metre", "milli"); // standard, prefix.

    // mm^3
    libcellml::UnitsPtr u2 = std::make_shared<libcellml::Units>();
    u2->setName("u2");
    u2->addUnit("u1", 3.0); // standard, exponent.

    // mm^6
    libcellml::UnitsPtr u3 = std::make_shared<libcellml::Units>();
    u3->setName("u3");
    u3->addUnit("u2", 2.0); // standard, exponent.

    // m^6
    libcellml::UnitsPtr u4 = std::make_shared<libcellml::Units>();
    u4->setName("u4");
    u4->addUnit("u3", 15, 1.0); // standard, prefix, exponent.

    libcellml::UnitsPtr u5 = std::make_shared<libcellml::Units>();
    u5->setName("u5");
    u5->addUnit("metre", 6.0); // standard, exponent.

    // u4 ~= u5: Units will be equivalent, testing that prefix, multiplier, and exponent validation is correct.
    // Note: there is a factor of 1000 between u4 and u5 since u4 = 10^15*u3 (rather than 10^18*u3), which is
    //       fine since we only need units to be equivalent.
    // TODO: see issue in specification: https://github.com/cellml/cellml-specification/issues/19.
    v1->setUnits(u4);
    v2->setUnits(u5);

    comp1->setName("component1");
    comp1->addVariable(v1);

    comp2->setName("component2");
    comp2->addVariable(v2);

    model->setName("model");
    model->addComponent(comp1);
    model->addComponent(comp2);

    model->addUnits(u1);
    model->addUnits(u2);
    model->addUnits(u3);
    model->addUnits(u4);
    model->addUnits(u5);

    libcellml::Variable::addEquivalence(v1, v2);

    validator.validateModel(model);
    EXPECT_EQ(size_t(0), validator.errorCount());
}

TEST(Validator, unitMismatchedUnits)
{
    std::vector<std::string> expectedErrors = {
        "Variable 'v2' has units of 'gram' and an equivalent variable 'v1' has units of 'litre' which do not match. The mismatch is: kilogram^1, metre^-3.",
        "Variable 'v3' has units of 'metre' and an equivalent variable 'v4' has units of 'second' which do not match. The mismatch is: metre^1, second^-1.",
        "Variable 'v1' has units of 'litre' and an equivalent variable 'v2' has units of 'gram' which do not match. The mismatch is: kilogram^-1, metre^3.",
        "Variable 'v4' has units of 'second' and an equivalent variable 'v3' has units of 'metre' which do not match. The mismatch is: metre^-1, second^1.",
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

    m->setName("m");
    c1->setName("c1");
    c2->setName("c2");
    c3->setName("c3");

    v1->setName("v1");
    v2->setName("v2");
    v3->setName("v3");
    v4->setName("v4");
    v5->setName("v5");

    v1->setInterfaceType("public");
    v2->setInterfaceType("public");
    v3->setInterfaceType("public");
    v4->setInterfaceType("public");
    v5->setInterfaceType("public");

    libcellml::UnitsPtr u1 = std::make_shared<libcellml::Units>();
    u1->setName("big_barrel");
    u1->addUnit("metre", 3.0);

    v1->setUnits("litre"); // Testing standard units which are not base units.
    v2->setUnits("gram");

    v3->setUnits("metre"); // Testing built-in base units.
    v4->setUnits("second");

    v5->setUnits(u1);

    c3->addVariable(v1);

    c1->addVariable(v2);
    c2->addVariable(v3);
    c3->addVariable(v4);

    c1->addVariable(v5);

    m->addComponent(c1);
    m->addComponent(c2);
    m->addComponent(c3);

    m->addUnits(u1);

    libcellml::Variable::addEquivalence(v1, v2); // Litre != gram.
    libcellml::Variable::addEquivalence(v3, v4); // Metre != second.
    libcellml::Variable::addEquivalence(v1, v5); // Litre != big_barrel, multiplier factor difference.

    validator.validateModel(m);

    EXPECT_EQ(expectedErrors.size(), validator.errorCount());

    for (size_t i = 0; i < expectedErrors.size(); ++i) {
        EXPECT_EQ(expectedErrors.at(i), validator.error(i)->description());
    }
}

TEST(Validator, unitMismatchedUserDefinedUnits)
{
    std::vector<std::string> expectedErrors = {
        "Variable 'v1' has units of 'bushell_of_apples' and an equivalent variable 'v2' has units of 'bunch_of_bananas' which do not match. The mismatch is: apple^10, banana^-5.",
        "Variable 'v2' has units of 'bunch_of_bananas' and an equivalent variable 'v1' has units of 'bushell_of_apples' which do not match. The mismatch is: apple^-10, banana^5.",
        "Variable 'v4' has units of 'banana' and an equivalent variable 'v3' has units of 'apple' which do not match. The mismatch is: apple^-1, banana^1.",
        "Variable 'v3' has units of 'apple' and an equivalent variable 'v4' has units of 'banana' which do not match. The mismatch is: apple^1, banana^-1.",
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

    v1->setInterfaceType("public");
    v2->setInterfaceType("public");
    v3->setInterfaceType("public");
    v4->setInterfaceType("public");

    m->setName("m");
    c1->setName("c1");
    c2->setName("c2");
    c3->setName("c3");

    v1->setName("v1");
    v2->setName("v2");
    v3->setName("v3");
    v4->setName("v4");

    libcellml::UnitsPtr uApple = std::make_shared<libcellml::Units>();
    uApple->setName("apple");

    libcellml::UnitsPtr uBanana = std::make_shared<libcellml::Units>();
    uBanana->setName("banana");

    libcellml::UnitsPtr u1 = std::make_shared<libcellml::Units>();
    u1->setName("bushell_of_apples");
    u1->addUnit("apple", 10.0);

    libcellml::UnitsPtr u2 = std::make_shared<libcellml::Units>();
    u2->setName("bunch_of_bananas");
    u2->addUnit("banana", 5.0);

    v1->setUnits(u1); // Bushell of apples - testing user-defined base units.
    v2->setUnits(u2); // Bunch of bananas - testing user-defined base units.

    v3->setUnits("apple");
    v4->setUnits("banana");

    c1->addVariable(v1);
    c2->addVariable(v2);

    c2->addVariable(v4);
    c3->addVariable(v3);

    m->addComponent(c1);
    m->addComponent(c2);
    m->addComponent(c3);

    m->addUnits(u1);
    m->addUnits(u2);
    m->addUnits(uApple);
    m->addUnits(uBanana);

    libcellml::Variable::addEquivalence(v1, v2); // Bushell of apples != bunch of bananas.
    libcellml::Variable::addEquivalence(v3, v4); // Apple != banana.

    validator.validateModel(m);

    EXPECT_EQ(expectedErrors.size(), validator.errorCount());

    checkExpectedErrors(expectedErrors, validator);
}

TEST(Validator, unitSimpleCycle)
{
    // Testing that indirect dependence is caught in the unit cycles. The network is:
    //
    //      grandfather(u1) <- father(u2) <- child (u3) <-+
    //           |                                        |
    //           +----------------------------------------+

    const std::string expectedError = "Cyclic units exist: 'grandfather' -> 'child' -> 'father' -> 'grandfather'";

    libcellml::Validator v;
    libcellml::ModelPtr m = std::make_shared<libcellml::Model>();

    libcellml::UnitsPtr u1 = std::make_shared<libcellml::Units>();
    libcellml::UnitsPtr u2 = std::make_shared<libcellml::Units>();
    libcellml::UnitsPtr u3 = std::make_shared<libcellml::Units>();

    m->setName("model");

    m->addUnits(u1);
    m->addUnits(u2);
    m->addUnits(u3);

    u1->setName("grandfather"); // Base unit.

    u2->setName("father"); // First generation.
    u2->addUnit("grandfather");

    u3->setName("child"); // Second generation.
    u3->addUnit("father");

    // Network valid at this stage.
    v.validateModel(m);
    EXPECT_EQ(size_t(0), v.errorCount());

    // Time loop Grandfather paradox created! u1 no longer a base variable: u1 -> u3 -> u2 -> u1.
    u1->addUnit("child");
    v.validateModel(m);

    EXPECT_EQ(size_t(1), v.errorCount());
    EXPECT_EQ(expectedError, v.error(0)->description());
}

TEST(Validator, unitComplexCycle)
{
    // Simple testing for the directional dependency of units. The first network is:
    //
    //                            <- brotherFromAnotherMother (u4)
    //                 <- father (u2)  <-+
    //     grandfather (u1)              | <- childOfIncest (u5)
    //                 <- mother (u3)  <-+
    //                            <- sisterFromAnotherFather (u6)
    //
    // There is an _undirected_ loop between u1-u2-u3-u5 but the directionality of the
    // dependencies here means the network is still valid. Keeping this here to test that
    // the directionality does indeed protect it from forming a cycle.

    libcellml::Validator v;
    libcellml::ModelPtr m = std::make_shared<libcellml::Model>();

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

    u1->setName("grandfather"); // Base unit.

    u2->setName("father"); // First generation.
    u2->addUnit("grandfather");

    u3->setName("mother"); // First generation.
    u3->addUnit("grandfather");

    u4->setName("brotherFromAnotherMother"); // Second generation.
    u4->addUnit("father");

    // Second generation depending on both first gen children, still valid, no loops because of directionality.
    u5->setName("childOfIncest_ButThatsOKApparently");
    u5->addUnit("mother");
    u5->addUnit("father");

    u6->setName("sisterFromAnotherFather"); // Second generation.
    u6->addUnit("mother");

    v.validateModel(m);
    EXPECT_EQ(size_t(0), v.errorCount());

    // As soon as a dependency of the grandfather on the brotherFromAnotherMother is added, then a
    // _directed_ loop (u1->u2->u4->u1) is created and the network is no longer valid:
    //
    //     +----------------------------------------------------------+
    //     |                                                          |
    //     |                       <- brotherFromAnotherMother (u4) <-+
    //     |            <- father (u2)  <-+
    //     +- grandfather (u1)            | <- childOfIncest (u5)
    //                  <- mother (u3)  <-+
    //                             <- sisterFromAnotherFather (u6)

    const std::string expectedError = "Cyclic units exist: 'grandfather' -> 'brotherFromAnotherMother' -> 'father' -> 'grandfather'";

    // Time loop Grandfather paradox created! u1 no longer a base variable: u1 -> u4 -> u2 -> u1.
    u1->addUnit("brotherFromAnotherMother");
    v.validateModel(m);

    EXPECT_EQ(size_t(1), v.errorCount());
    EXPECT_EQ(expectedError, v.error(0)->description());
}

TEST(Validator, encapsulationHierarchyNoCycles)
{
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

    // comp1( comp2 ( comp3 )) -> valid
    m->addComponent(comp1);
    comp1->addComponent(comp2);
    comp2->addComponent(comp3);

    v.validateModel(m);
    EXPECT_EQ(size_t(0), v.errorCount());

    // Breaking the encapsulation hierarchy by creating a loop
    comp3->addComponent(comp1);
    // ... but this is prevented inside the addComponent function - fails silently - and model is unchanged
    v.validateModel(m);
    EXPECT_EQ(size_t(0), v.errorCount());
}

TEST(Validator, interfaceTestingValid)
{
    libcellml::Validator validator;
    libcellml::ModelPtr m = std::make_shared<libcellml::Model>();
    libcellml::ComponentPtr c_parent = std::make_shared<libcellml::Component>();
    libcellml::ComponentPtr c = std::make_shared<libcellml::Component>();
    libcellml::ComponentPtr c_child1 = std::make_shared<libcellml::Component>();
    libcellml::ComponentPtr c_child2 = std::make_shared<libcellml::Component>();

    libcellml::VariablePtr v_parent = std::make_shared<libcellml::Variable>();
    libcellml::VariablePtr v = std::make_shared<libcellml::Variable>();
    libcellml::VariablePtr v_child1 = std::make_shared<libcellml::Variable>();
    libcellml::VariablePtr v_child2 = std::make_shared<libcellml::Variable>();

    m->setName("modelName");
    c_parent->setName("c_parent");
    c->setName("c");
    c_child1->setName("c_child1");
    c_child2->setName("c_child2");

    v_parent->setName("v_parent");
    v->setName("v");
    v_child1->setName("v_child1");
    v_child2->setName("v_child2");

    v_parent->setUnits("dimensionless");
    v->setUnits("dimensionless");
    v_child1->setUnits("dimensionless");
    v_child2->setUnits("dimensionless");

    c_parent->addVariable(v_parent);
    c->addVariable(v);
    c_child1->addVariable(v_child1);
    c_child2->addVariable(v_child2);

    // model ( c_parent (c (c_child1, c_child2)))
    m->addComponent(c_parent);
    c_parent->addComponent(c);
    c->addComponent(c_child1);
    c->addComponent(c_child2);

    libcellml::Variable::addEquivalence(v_child1, v_child2); // sibling components, needs public interface
    v_child1->setInterfaceType("public");
    v_child2->setInterfaceType("public");

    libcellml::Variable::addEquivalence(v, v_parent); // parent and child, needs public on child and private on parent
    v_parent->setInterfaceType("public");
    v->setInterfaceType("private");

    validator.validateModel(m);
    EXPECT_EQ(size_t(0), validator.errorCount());
}

TEST(Validator, interfaceTestingNotValid)
{
    std::vector<std::string> expectedErrors = {
        "Variable 'v_parent' in component 'c_parent' specifies an interface type of 'private' which is incompatible with connecting to the variable 'v', in component 'c'.",
        "Variable 'v_parent' in component 'c_parent' specifies an equivalent variable 'v_child2b' in component 'c_child2', which is not in the available component set.",
        "Variable 'v_parent' in component 'c_parent' specifies an interface type of 'private' which is incompatible with connecting to the variable 'v2', in component 'c2'.",
        "Variable 'v' in component 'c' specifies an interface type of 'public' which is incompatible with connecting to the variable 'v_parent', in component 'c_parent'.",
        "Variable 'v_child1' in component 'c_child1' specifies an interface type of 'private' which is incompatible with connecting to the variable 'v_child2a', in component 'c_child2'.",
        "Variable 'v_child2a' specifies connections to equivalent variables but has an 'none' interface type which prevents them.",
        "Variable 'v_child2b' in component 'c_child2' specifies an equivalent variable 'v_parent' in component 'c_parent', which is not in the available component set.",
        "Variable 'v2' specifies connections to equivalent variables but has an 'unspecified' interface type which prevents them.",
    };

    libcellml::Validator validator;
    libcellml::ModelPtr m = std::make_shared<libcellml::Model>();
    libcellml::ComponentPtr c_parent = std::make_shared<libcellml::Component>();
    libcellml::ComponentPtr c = std::make_shared<libcellml::Component>();
    libcellml::ComponentPtr c2 = std::make_shared<libcellml::Component>();
    libcellml::ComponentPtr c_child1 = std::make_shared<libcellml::Component>();
    libcellml::ComponentPtr c_child2 = std::make_shared<libcellml::Component>();
    libcellml::ComponentPtr c_child3 = std::make_shared<libcellml::Component>();

    libcellml::VariablePtr v_parent = std::make_shared<libcellml::Variable>();
    libcellml::VariablePtr v = std::make_shared<libcellml::Variable>();
    libcellml::VariablePtr v2 = std::make_shared<libcellml::Variable>();
    libcellml::VariablePtr v_child1 = std::make_shared<libcellml::Variable>();
    libcellml::VariablePtr v_child3 = std::make_shared<libcellml::Variable>();
    libcellml::VariablePtr v_child2a = std::make_shared<libcellml::Variable>();
    libcellml::VariablePtr v_child2b = std::make_shared<libcellml::Variable>();

    m->setName("modelName");
    c_parent->setName("c_parent");
    c->setName("c");
    c2->setName("c2");
    c_child1->setName("c_child1");
    c_child2->setName("c_child2");
    c_child3->setName("c_child3");

    v_parent->setName("v_parent");
    v->setName("v");
    v2->setName("v2");
    v_child1->setName("v_child1");
    v_child2a->setName("v_child2a");
    v_child2b->setName("v_child2b");
    v_child3->setName("v_child3");

    v_parent->setUnits("dimensionless");
    v->setUnits("dimensionless");
    v2->setUnits("dimensionless");
    v_child1->setUnits("dimensionless");
    v_child2a->setUnits("dimensionless");
    v_child2b->setUnits("dimensionless");
    v_child3->setUnits("dimensionless");

    c_parent->addVariable(v_parent);
    c->addVariable(v);
    c2->addVariable(v2);
    c_child1->addVariable(v_child1);
    c_child2->addVariable(v_child2a);
    c_child2->addVariable(v_child2b);
    c_child3->addVariable(v_child3);

    // model ( c_parent (c (c_child1, c_child2, c) , c2 ))
    m->addComponent(c_parent);
    c_parent->addComponent(c);
    c_parent->addComponent(c2);
    c->addComponent(c_child1);
    c->addComponent(c_child2);
    c->addComponent(c_child3);

    // Variable 'v_child1' in component 'c_child1' specifies an interface type of 'private' which is incompatible with connecting to the variable 'v_child2a', in component 'c_child2'.
    libcellml::Variable::addEquivalence(v_child1, v_child2a); // sibling components, needs public interface - both will fail
    v_child1->setInterfaceType("private");
    // Variable 'v_child2a' specifies connections to equivalent variables but has an 'none' interface type which prevents them.
    v_child2a->setInterfaceType("none");

    // Variable 'v_parent' in component 'c_parent' specifies an interface type of 'private' which is incompatible with connecting to the variable 'v', in component 'c'.,
    // Variable 'v' in component 'c' specifies an interface type of 'public' which is incompatible with connecting to the variable 'v_parent', in component 'c_parent'.
    libcellml::Variable::addEquivalence(v, v_parent);
    v_parent->setInterfaceType("private");
    v->setInterfaceType("public");

    // Variable 'v_parent' in component 'c_parent' specifies an equivalent variable 'v_child2b' in component 'c_child2', which is not in the available component set.,
    // Variable 'v_child2b' in component 'c_child2' specifies an equivalent variable 'v_parent' in component 'c_parent', which is not in the available component set.
    libcellml::Variable::addEquivalence(v_parent, v_child2b);
    v_child2b->setInterfaceType("public_and_private");

    // Variable 'v_parent' in component 'c_parent' specifies an interface type of 'private' which is incompatible with connecting to the variable 'v2', in component 'c2'
    // Variable 'v2' specifies connections to equivalent variables but has an 'unspecified' interface type which prevents them.,
    libcellml::Variable::addEquivalence(v_parent, v2);

    // libcellml::Variable::addEquivalence(v_child2b, v_child3);
    // v_child3->setInterfaceType("public");
    // c_child3->removeVariable(v_child3);  // this is *supposed* to orphan the variable from the component, but it currently has a bug ...

    validator.validateModel(m);

    EXPECT_EQ(size_t(8), validator.errorCount());
    checkExpectedErrors(expectedErrors, validator);
}

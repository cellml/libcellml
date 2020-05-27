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

#include "test_utils.h"

/*
 * The tests in this file are here to catch any branches of code that
 * are not picked up by the main tests testing the API of the library
 */

TEST(Validator, namedModel)
{
    libcellml::ValidatorPtr validator = libcellml::Validator::create();
    libcellml::ModelPtr model = libcellml::Model::create();
    model->setName("awesomeName");
    validator->validateModel(model);
    EXPECT_EQ(size_t(0), validator->issueCount());
}

TEST(Validator, unnamedModel)
{
    const std::vector<std::string> expectedIssues = {
        "CellML identifiers must contain one or more basic Latin alphabetic characters.",
        "Model does not have a valid name attribute.",
    };
    const std::vector<std::string> expectedSpecificationHeadings = {
        "3.1.3",
        "4.2.1",
    };
    libcellml::ValidatorPtr validator = libcellml::Validator::create();
    libcellml::ModelPtr model = libcellml::Model::create();
    validator->validateModel(model);
    EXPECT_EQ_ISSUES_SPECIFICATION_HEADINGS(expectedIssues, expectedSpecificationHeadings, validator);
}

TEST(Validator, invalidCellMLIdentifiersWithSpecificationHeading)
{
    const std::vector<std::string> expectedIssues = {
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

    libcellml::ValidatorPtr v = libcellml::Validator::create();
    libcellml::ModelPtr model = libcellml::Model::create();
    libcellml::ComponentPtr c1 = libcellml::Component::create();
    libcellml::ComponentPtr c2 = libcellml::Component::create();
    libcellml::ComponentPtr c3 = libcellml::Component::create();
    libcellml::ComponentPtr c4 = libcellml::Component::create();
    libcellml::ComponentPtr c5 = libcellml::Component::create();

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

    v->validateModel(model);

    EXPECT_EQ_ISSUES_SPECIFICATION_HEADINGS(expectedIssues, expectedSpecificationHeadings, v);
}

TEST(Validator, namedModelWithUnnamedComponent)
{
    const std::vector<std::string> expectedIssues = {
        "CellML identifiers must contain one or more basic Latin alphabetic characters.",
        "Component does not have a valid name attribute.",
    };
    libcellml::ValidatorPtr validator = libcellml::Validator::create();
    libcellml::ModelPtr model = libcellml::Model::create();
    libcellml::ComponentPtr component = libcellml::Component::create();
    model->setName("awesomeName");
    model->addComponent(component);
    validator->validateModel(model);
    EXPECT_EQ_ISSUES(expectedIssues, validator);
}

TEST(Validator, unnamedModelWithUnnamedComponentWithUnnamedUnits)
{
    const std::vector<std::string> expectedIssues = {
        "CellML identifiers must contain one or more basic Latin alphabetic characters.",
        "Model does not have a valid name attribute.",
        "CellML identifiers must contain one or more basic Latin alphabetic characters.",
        "Component does not have a valid name attribute.",
        "CellML identifiers must contain one or more basic Latin alphabetic characters.",
        "Units does not have a valid name attribute.",
    };

    libcellml::ValidatorPtr validator = libcellml::Validator::create();
    libcellml::ModelPtr model = libcellml::Model::create();
    libcellml::ComponentPtr component = libcellml::Component::create();
    libcellml::UnitsPtr units = libcellml::Units::create();
    model->addComponent(component);
    model->addUnits(units);
    validator->validateModel(model);

    EXPECT_EQ_ISSUES(expectedIssues, validator);
}

TEST(Validator, modelWithDuplicateComponentsAndUnits)
{
    const std::vector<std::string> expectedIssues = {
        "Model 'multiplicity' contains multiple components with the name 'michael'. Valid component names must be unique to their model.",
        "Model 'multiplicity' contains multiple units with the name 'keaton'. Valid units names must be unique to their model.",
    };

    libcellml::ValidatorPtr validator = libcellml::Validator::create();
    libcellml::ModelPtr model = libcellml::Model::create();
    libcellml::ComponentPtr c1 = libcellml::Component::create();
    libcellml::ComponentPtr c2 = libcellml::Component::create();
    libcellml::UnitsPtr u1 = libcellml::Units::create();
    libcellml::UnitsPtr u2 = libcellml::Units::create();
    model->addComponent(c1);
    model->addComponent(c2);
    model->addUnits(u1);
    model->addUnits(u2);

    model->setName("multiplicity");
    c1->setName("michael");
    c2->setName("michael");
    u1->setName("keaton");
    u2->setName("keaton");
    validator->validateModel(model);

    EXPECT_EQ_ISSUES(expectedIssues, validator);
}

TEST(Validator, unnamedAndDuplicateNamedVariablesWithAndWithoutValidUnits)
{
    const std::vector<std::string> expectedIssues = {
        "Component 'fargo' contains multiple variables with the name 'margie'. Valid variable names must be unique to their component.",
        "CellML identifiers must not begin with a European numeric character [0-9].",
        "Variable does not have a valid name attribute.",
        "CellML identifiers must contain one or more basic Latin alphabetic characters.",
        "Variable 'margie' does not have a valid units attribute.",
        "Variable 'ransom' in component 'fargo' has a units reference 'dollars' which is neither standard nor defined in the parent model.",
    };

    libcellml::ValidatorPtr validator = libcellml::Validator::create();
    libcellml::ModelPtr model = libcellml::Model::create();
    libcellml::ComponentPtr c1 = libcellml::Component::create();
    libcellml::VariablePtr v1 = libcellml::Variable::create();
    libcellml::VariablePtr v2 = libcellml::Variable::create();
    libcellml::VariablePtr v3 = libcellml::Variable::create();
    libcellml::VariablePtr v4 = libcellml::Variable::create();
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
    validator->validateModel(model);

    EXPECT_EQ_ISSUES(expectedIssues, validator);
}

TEST(Validator, invalidVariableInitialValuesAndInterfaces)
{
    const std::vector<std::string> expectedIssues = {
        "Variable 'candidate' has an invalid interface attribute value 'orange'.",
        "Variable 'candidate' has an invalid initial value 'trump'. Initial values must be a real number string or a variable reference.",
    };

    libcellml::ValidatorPtr validator = libcellml::Validator::create();
    libcellml::ModelPtr model = libcellml::Model::create();
    libcellml::ComponentPtr c1 = libcellml::Component::create();
    libcellml::VariablePtr v1 = libcellml::Variable::create();
    model->addComponent(c1);
    c1->addVariable(v1);

    model->setName("election");
    c1->setName("republican");
    v1->setName("candidate");
    v1->setUnits("ampere");
    v1->setInterfaceType("orange");
    v1->setInitialValue("trump");

    validator->validateModel(model);

    EXPECT_EQ_ISSUES(expectedIssues, validator);
}

TEST(Validator, importUnits)
{
    const std::vector<std::string> expectedIssues = {
        "CellML identifiers must contain one or more basic Latin alphabetic characters.",
        "Imported units 'invalid_imported_units_in_this_model' does not have a valid units_ref attribute.",
        "Import of units 'invalid_imported_units_in_this_model' does not have a valid locator xlink:href attribute.",
        "Model 'model_name' contains multiple imported units from 'some-other-model.xml' with the same units_ref attribute 'units_in_that_model'.",
        "CellML identifiers must contain one or more basic Latin alphabetic characters.",
        "Imported units does not have a valid name attribute.",
    };

    libcellml::ValidatorPtr v = libcellml::Validator::create();
    libcellml::ModelPtr m = libcellml::Model::create();
    m->setName("model_name");

    // Valid units import
    libcellml::ImportSourcePtr imp = libcellml::ImportSource::create();
    imp->setUrl("some-other-model.xml");
    libcellml::UnitsPtr importedUnits = libcellml::Units::create();
    importedUnits->setName("valid_imported_units_in_this_model");
    importedUnits->setSourceUnits(imp, "units_in_that_model");
    m->addUnits(importedUnits);
    v->validateModel(m);
    EXPECT_EQ(size_t(0), v->issueCount());

    // Invalid units import- missing refs
    libcellml::ImportSourcePtr imp2 = libcellml::ImportSource::create();
    libcellml::UnitsPtr importedUnits2 = libcellml::Units::create();
    importedUnits2->setName("invalid_imported_units_in_this_model");
    importedUnits2->setSourceUnits(imp2, "");
    m->addUnits(importedUnits2);
    v->validateModel(m);
    EXPECT_EQ(size_t(3), v->issueCount());

    // Invalid units import - duplicate refs
    libcellml::ImportSourcePtr imp3 = libcellml::ImportSource::create();
    imp3->setUrl("some-other-model.xml");
    libcellml::UnitsPtr importedUnits3 = libcellml::Units::create();
    importedUnits3->setName("duplicate_imported_units_in_this_model");
    importedUnits3->setSourceUnits(imp3, "units_in_that_model");
    m->addUnits(importedUnits3);
    v->validateModel(m);
    EXPECT_EQ(size_t(4), v->issueCount());

    // Invalid units import - unnamed units
    libcellml::ImportSourcePtr imp4 = libcellml::ImportSource::create();
    imp4->setUrl("some-other-different-model.xml");
    libcellml::UnitsPtr importedUnits4 = libcellml::Units::create();
    importedUnits4->setSourceUnits(imp4, "units_in_that_model");
    m->addUnits(importedUnits4);
    v->validateModel(m);

    // Check for expected error messages
    EXPECT_EQ_ISSUES(expectedIssues, v);
}

TEST(Validator, importComponents)
{
    const std::vector<std::string> expectedIssues = {
        "CellML identifiers must contain one or more basic Latin alphabetic characters.",
        "Imported component 'invalid_imported_component_in_this_model' does not have a valid component_ref attribute.",
        "Import of component 'invalid_imported_component_in_this_model' does not have a valid locator xlink:href attribute.",
        "CellML identifiers must contain one or more basic Latin alphabetic characters.",
        "Imported component does not have a valid name attribute.",
        "Import of component 'a_bad_imported_component' has an invalid URI in the href attribute.",
    };

    libcellml::ValidatorPtr v = libcellml::Validator::create();
    libcellml::ModelPtr m = libcellml::Model::create();
    m->setName("model_name");

    // Valid component import
    libcellml::ImportSourcePtr imp = libcellml::ImportSource::create();
    imp->setUrl("some-other-model.xml");
    libcellml::ComponentPtr importedComponent = libcellml::Component::create();
    importedComponent->setName("valid_imported_component_in_this_model");
    importedComponent->setSourceComponent(imp, "component_in_that_model");
    m->addComponent(importedComponent);
    v->validateModel(m);
    EXPECT_EQ(size_t(0), v->issueCount());

    // Another valid component import
    libcellml::ImportSourcePtr imp2 = libcellml::ImportSource::create();
    imp2->setUrl("yet-another-other-model.xml");
    libcellml::ComponentPtr importedComponent2 = libcellml::Component::create();
    importedComponent2->setName("another_valid_imported_component_in_this_model");
    importedComponent2->setSourceComponent(imp2, "new_shiny_component_ref");
    m->addComponent(importedComponent2);
    v->validateModel(m);
    EXPECT_EQ(size_t(0), v->issueCount());

    // Invalid component import - missing ref to source component
    libcellml::ImportSourcePtr imp3 = libcellml::ImportSource::create();
    libcellml::ComponentPtr importedComponent3 = libcellml::Component::create();
    importedComponent3->setName("invalid_imported_component_in_this_model");
    importedComponent3->setSourceComponent(imp3, "");
    m->addComponent(importedComponent3);
    v->validateModel(m);
    EXPECT_EQ(size_t(3), v->issueCount());

    // Valid component import - two components imported from the same place is allowed
    libcellml::ImportSourcePtr imp4 = libcellml::ImportSource::create();
    imp4->setUrl("some-other-model.xml");
    libcellml::ComponentPtr importedComponent4 = libcellml::Component::create();
    importedComponent4->setName("duplicate_imported_component_in_this_model");
    importedComponent4->setSourceComponent(imp4, "component_in_that_model");
    m->addComponent(importedComponent4);
    v->validateModel(m);
    EXPECT_EQ(size_t(3), v->issueCount());

    // Invalid - name missing from component
    libcellml::ImportSourcePtr imp5 = libcellml::ImportSource::create();
    imp5->setUrl("some-other-different-model.xml");
    libcellml::ComponentPtr importedComponent5 = libcellml::Component::create();
    importedComponent5->setSourceComponent(imp5, "component_in_that_model");
    m->addComponent(importedComponent5);
    v->validateModel(m);
    EXPECT_EQ(size_t(5), v->issueCount());

    // Valid - two components from the same source is allowed
    libcellml::ImportSourcePtr imp7 = libcellml::ImportSource::create();
    imp7->setUrl("yet-another-other-model.xml");
    libcellml::ComponentPtr importedComponent7 = libcellml::Component::create();
    importedComponent7->setName("another_duplicate_imported_component");
    importedComponent7->setSourceComponent(imp7, "new_shiny_component_ref");
    m->addComponent(importedComponent7);
    v->validateModel(m);
    EXPECT_EQ(size_t(5), v->issueCount());

    // Valid - duplicate component_ref from a different source
    libcellml::ImportSourcePtr imp8 = libcellml::ImportSource::create();
    imp8->setUrl("yet-another-other-model.xml"); // source used before
    libcellml::ComponentPtr importedComponent8 = libcellml::Component::create();
    importedComponent8->setName("a_good_imported_component");
    importedComponent8->setSourceComponent(imp8, "component_in_that_model");
    m->addComponent(importedComponent8);
    v->validateModel(m);
    EXPECT_EQ(size_t(5), v->issueCount());

    // Invalid: component_ref url is not valid html
    libcellml::ImportSourcePtr imp9 = libcellml::ImportSource::create();
    imp9->setUrl("not @ valid url");
    libcellml::ComponentPtr importedComponent9 = libcellml::Component::create();
    importedComponent9->setName("a_bad_imported_component");
    importedComponent9->setSourceComponent(imp9, "component_in_some_model");
    m->addComponent(importedComponent9);
    v->validateModel(m);

    // Check for expected error messages
    EXPECT_EQ_ISSUES(expectedIssues, v);
}

TEST(Validator, importsDummyVariablesNotCheckedForUnitsInterfaces)
{
    auto validator = libcellml::Validator::create();
    auto model = libcellml::Model::create("model");

    // Create a concrete component and variable.
    // This should be checked for variable validity: units, interface.
    auto component = libcellml::Component::create("component");
    auto variable = libcellml::Variable::create("variable");
    variable->setUnits("dimensionless");
    variable->setInterfaceType("public");
    component->addVariable(variable);
    model->addComponent(component);

    // Create an imported component and dummy variable.
    // This should *not* be checked for variable validity.
    auto importer = libcellml::ImportSource::create();
    importer->setUrl("some-other-model.xml");
    auto dummyComponent = libcellml::Component::create("dummy_component");
    dummyComponent->setSourceComponent(importer, "component_in_that_model");
    auto dummyVariable = libcellml::Variable::create("I_dont_need_units_or_interface");
    dummyComponent->addVariable(dummyVariable);
    model->addComponent(dummyComponent);

    validator->validateModel(model);
    EXPECT_EQ(size_t(0), validator->issueCount());

    // As soon as a connection is made between the dummyVariable and the variable, the validator
    // checks the dummyVariable and fails the model.
    libcellml::Variable::addEquivalence(variable, dummyVariable);
    validator->validateModel(model);

    EXPECT_EQ(size_t(0), validator->issueCount());
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

    libcellml::ValidatorPtr v = libcellml::Validator::create();
    libcellml::ModelPtr m = libcellml::Model::create();
    libcellml::ComponentPtr c = libcellml::Component::create();
    libcellml::VariablePtr v1 = libcellml::Variable::create();
    libcellml::VariablePtr v2 = libcellml::Variable::create();
    libcellml::VariablePtr v3 = libcellml::Variable::create();

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

    v->validateModel(m);
    EXPECT_EQ(size_t(0), v->issueCount());
}

TEST(Validator, validMathInMultipleMathMLBlocks)
{
    const std::string math =
        "<math xmlns:cellml=\"http://www.cellml.org/cellml/2.0#\" xmlns=\"http://www.w3.org/1998/Math/MathML\">\n"
        "  <apply>\n"
        "    <eq/>\n"
        "    <ci>A</ci>\n"
        "    <apply>\n"
        "      <cn cellml:units=\"dimensionless\">1</cn>\n"
        "    </apply>\n"
        "  </apply>\n"
        "</math>\n"
        "<math xmlns:cellml=\"http://www.cellml.org/cellml/2.0#\" xmlns=\"http://www.w3.org/1998/Math/MathML\">\n"
        "  <apply>\n"
        "    <eq/>\n"
        "    <ci>B</ci>\n"
        "    <apply>\n"
        "      <cn cellml:units=\"dimensionless\">2</cn>\n"
        "    </apply>\n"
        "  </apply>\n"
        "</math>\n";

    libcellml::ValidatorPtr v = libcellml::Validator::create();
    libcellml::ModelPtr m = libcellml::Model::create();
    libcellml::ComponentPtr c = libcellml::Component::create();
    libcellml::VariablePtr v1 = libcellml::Variable::create();
    libcellml::VariablePtr v2 = libcellml::Variable::create();

    m->setName("modelName");
    c->setName("componentName");
    v1->setName("A");
    v2->setName("B");
    v1->setUnits("dimensionless");
    v2->setUnits("dimensionless");

    c->addVariable(v1);
    c->addVariable(v2);
    c->setMath(math);
    m->addComponent(c);

    v->validateModel(m);
    EXPECT_EQ(size_t(0), v->errorCount());
}

TEST(Validator, invalidMath)
{
    const std::string math1 =
        "<math>\n"
        "  <invalid_xml></not_valid>\n"
        "</math>\n";
    const std::string math2 = "<invalid_math/>\n";
    const std::vector<std::string> expectedIssues = {
        "LibXml2 error: Opening and ending tag mismatch: invalid_xml line 2 and not_valid.",
        "Could not get a valid XML root node from the math on component 'componentName1'.",
        "Math root node is of invalid type 'invalid_math' on component 'componentName2'. A valid math root node should be of type 'math'.",
    };

    libcellml::ValidatorPtr v = libcellml::Validator::create();
    libcellml::ModelPtr m = libcellml::Model::create();
    libcellml::ComponentPtr c1 = libcellml::Component::create();
    libcellml::ComponentPtr c2 = libcellml::Component::create();

    m->setName("modelName");
    c1->setName("componentName1");
    c2->setName("componentName2");

    c1->setMath(math1);
    c2->setMath(math2);
    m->addComponent(c1);
    m->addComponent(c2);

    v->validateModel(m);

    EXPECT_EQ_ISSUES(expectedIssues, v);
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
    const std::vector<std::string> expectedIssues = {
        "Math has a 'equals' element that is not a supported MathML element.",
        "Math has a 'addition' element that is not a supported MathML element.",
        "No declaration for element equals.",
        "No declaration for element addition.",
    };
    // Note: the MathML DTD also gives issues that list every possible operator when an
    //       invalid option is given. We'll just explicitly check the less verbose issues here.

    libcellml::ValidatorPtr v = libcellml::Validator::create();
    libcellml::ModelPtr m = libcellml::Model::create();
    libcellml::ComponentPtr c = libcellml::Component::create();
    libcellml::VariablePtr v1 = libcellml::Variable::create();
    libcellml::VariablePtr v2 = libcellml::Variable::create();
    libcellml::VariablePtr v3 = libcellml::Variable::create();

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

    v->validateModel(m);

    // Check for two expected error messages (see note above).
    for (size_t i = 0; i < 2; ++i) {
        EXPECT_EQ(expectedIssues.at(i), v->issue(i)->description());
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
    const std::vector<std::string> expectedIssues = {
        "Math has a 'partialdiff' element that is not a supported MathML element.",
        "Math has a 'nonsense' element that is not a supported MathML element.",
        "MathML ci element has the child text 'answer' which does not correspond with any variable names present in component 'componentName'.",
        "MathML ci element has the child text 'new_bvar' which does not correspond with any variable names present in component 'componentName'.",
        "W3C MathML DTD error: No declaration for element nonsense.",
        "W3C MathML DTD error: Element nonsense is not declared in ci list of possible children.",
    };

    libcellml::ValidatorPtr v = libcellml::Validator::create();
    libcellml::ModelPtr m = libcellml::Model::create();
    libcellml::ComponentPtr c = libcellml::Component::create();
    libcellml::VariablePtr v1 = libcellml::Variable::create();
    libcellml::VariablePtr v2 = libcellml::Variable::create();
    libcellml::VariablePtr v3 = libcellml::Variable::create();

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

    v->validateModel(m);

    EXPECT_EQ_ISSUES(expectedIssues, v);
}

TEST(Validator, invalidSimpleMathmlCellMLUnits)
{
    const std::string math =
        "<math xmlns:cellml=\"http://www.cellml.org/cellml/2.0#\" xmlns=\"http://www.w3.org/1998/Math/MathML\">\n"
        "  <apply>\""
        "    <bvar>\n"
        "      <ci cellml:units=\"dimensionless\">B</ci>\n"
        "    </bvar>\n"
        "  </apply>\n"
        "</math>";
    const std::vector<std::string> expectedIssues = {
        "CellML identifiers must contain one or more basic Latin alphabetic characters.",
        "Model does not have a valid name attribute.",
        "CellML identifiers must contain one or more basic Latin alphabetic characters.",
        "Component does not have a valid name attribute.",
        "MathML ci element has the child text 'B' which does not correspond with any variable names present in component ''.",
        "W3C MathML DTD error: No declaration for attribute units of element ci.",
        "W3C MathML DTD error: Element apply content does not follow the DTD, expecting (csymbol | ci | cn | apply | reln | lambda | condition | declare | sep | semantics | annotation | annotation-xml | integers | reals | rationals | naturalnumbers | complexes | primes | exponentiale | imaginaryi | notanumber | true | false | emptyset | pi | eulergamma | infinity | interval | list | matrix | matrixrow | set | vector | piecewise | lowlimit | uplimit | bvar | degree | logbase | momentabout | domainofapplication | inverse | ident | domain | codomain | image | abs | conjugate | exp | factorial | arg | real | imaginary | floor | ceiling | not | ln | sin | cos | tan | sec | csc | cot | sinh | cosh | tanh | sech | csch | coth | arcsin | arccos | arctan | arccosh | arccot | arccoth | arccsc | arccsch | arcsec | arcsech | arcsinh | arctanh | determinant | transpose | card | quotient | divide | power | rem | implies | vectorproduct | scalarproduct | outerproduct | setdiff | fn | compose | plus | times | max | min | gcd | lcm | and | or | xor | union | intersect | cartesianproduct | mean | sdev | variance | median | mode | selector | root | minus | log | int | diff | partialdiff | divergence | grad | curl | laplacian | sum | product | limit | moment | exists | forall | neq | factorof | in | notin | notsubset | notprsubset | tendsto | eq | leq | lt | geq | gt | equivalent | approx | subset | prsubset | mi | mn | mo | mtext | ms | mspace | mrow | mfrac | msqrt | mroot | menclose | mstyle | merror | mpadded | mphantom | mfenced | msub | msup | msubsup | munder | mover | munderover | mmultiscripts | mtable | mtr | mlabeledtr | mtd | maligngroup | malignmark | maction)*, got (CDATA bvar ).",
    };
    libcellml::ValidatorPtr v = libcellml::Validator::create();
    libcellml::ModelPtr m = libcellml::Model::create();
    libcellml::ComponentPtr c = libcellml::Component::create();

    c->setMath(math);
    m->addComponent(c);

    v->validateModel(m);
    EXPECT_EQ_ISSUES(expectedIssues, v);
}

TEST(Validator, invalidMathmlCellMLNsOnNode)
{
    const std::string math =
        "<math  xmlns:cellml=\"http://www.cellml.org/cellml/2.0#\" xmlns=\"http://www.w3.org/1998/Math/MathML\"><apply><cellml:bvar><ci cellml:units=\"dimensionless\">B</ci></cellml:bvar></apply></math>";
    const std::vector<std::string> expectedIssues = {
        "CellML identifiers must contain one or more basic Latin alphabetic characters.",
        "Model does not have a valid name attribute.",
        "CellML identifiers must contain one or more basic Latin alphabetic characters.",
        "Component does not have a valid name attribute.",
        "Math has a 'bvar' element that is not a supported MathML element.",
        "MathML ci element has the child text 'B' which does not correspond with any variable names present in component ''.",
        "W3C MathML DTD error: No declaration for attribute units of element ci.",
    };
    libcellml::ValidatorPtr v = libcellml::Validator::create();
    libcellml::ModelPtr m = libcellml::Model::create();
    libcellml::ComponentPtr c = libcellml::Component::create();

    c->setMath(math);
    m->addComponent(c);

    v->validateModel(m);
    EXPECT_EQ_ISSUES(expectedIssues, v);
}

TEST(Validator, invalidMathMLCiAndCnElementsWithCellMLUnits)
{
    const std::string math =
        "<math xmlns:cellml=\"http://www.cellml.org/cellml/2.0#\" xmlns=\"http://www.w3.org/1998/Math/MathML\">\n"
        "  <apply>\n"
        "    <eq/>\n"
        "    <cn cellml:units=\"invalid\" cellml:value=\"zero\">oops</cn>\n"
        "    <apply>\n"
        "      <plus/>\n"
        "      <ci>A</ci>\n"
        "      <apply>\n"
        "        <plus/>\n"
        "        <bvar>\n"
        "          <ci cellml:units=\"dimensionless\">new_bvar</ci>\n"
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
    const std::vector<std::string> expectedIssues = {
        "Math cn element has an invalid attribute type 'value' in the cellml namespace.  Attribute 'units' is the only CellML namespace attribute allowed.",
        "Math has a cn element with a cellml:units attribute 'invalid' that is not a valid reference to units in the model 'modelName' or a standard unit.",
        "MathML ci element has the child text 'new_bvar' which does not correspond with any variable names present in component 'componentName'.",
        "MathML ci element has the child text 'undefined_variable' which does not correspond with any variable names present in component 'componentName'.",
        "CellML identifiers must contain one or more basic Latin alphabetic characters.",
        "Math cn element with the value '2.0' does not have a valid cellml:units attribute.",
        "W3C MathML DTD error: No declaration for attribute units of element ci.",
        "W3C MathML DTD error: No declaration for attribute units of element ci.",
    };

    libcellml::ValidatorPtr v = libcellml::Validator::create();
    libcellml::ModelPtr m = libcellml::Model::create();
    libcellml::ComponentPtr c = libcellml::Component::create();
    libcellml::VariablePtr v1 = libcellml::Variable::create();
    libcellml::VariablePtr v2 = libcellml::Variable::create();
    libcellml::VariablePtr v3 = libcellml::Variable::create();

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

    v->validateModel(m);

    EXPECT_EQ_ISSUES(expectedIssues, v);
}

TEST(Validator, validMathMLCiAndCnElementsWithCellMLUnits)
{
    const std::string math =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<math xmlns=\"http://www.w3.org/1998/Math/MathML\" xmlns:cellml=\"http://www.cellml.org/cellml/2.0#\">\n"
        "  <apply>\n"
        "    <eq/>\n"
        "    <cn cellml:units=\"dimensionless\">3</cn>\n"
        "    <apply>\n"
        "      <plus/>\n"
        "      <ci>A</ci>\n"
        "      <apply>\n"
        "        <plus/>\n"
        "        <ci>C</ci>\n"
        "        <cn cellml:units=\"dimensionless\">7</cn>\n"
        "      </apply>\n"
        "    </apply>\n"
        "  </apply>\n"
        "</math>\n";

    libcellml::ValidatorPtr v = libcellml::Validator::create();
    libcellml::ModelPtr m = libcellml::Model::create();
    libcellml::ComponentPtr c = libcellml::Component::create();
    libcellml::VariablePtr v1 = libcellml::Variable::create();
    libcellml::VariablePtr v2 = libcellml::Variable::create();
    libcellml::VariablePtr v3 = libcellml::Variable::create();

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

    v->validateModel(m);
    EXPECT_EQ(size_t(0), v->issueCount());
}

TEST(Validator, parseAndValidateInvalidUnitIssues)
{
    const std::string in =
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
    const std::vector<std::string> expectedIssues = {
        "Units is named 'ampere' which is a protected standard unit name.",
        "Units reference 'ned' in units 'stark' is not a valid reference to a local units or a standard unit type.",
        "CellML identifiers must not contain any characters other than [a-zA-Z0-9_].",
        "Unit in units 'stark' does not have a valid units reference.",
        "Prefix 'wolf' of a unit referencing 'metre' in units 'stark' is not a valid integer or an SI prefix.",
    };

    libcellml::ParserPtr p = libcellml::Parser::create();
    libcellml::ModelPtr m = p->parseModel(in);
    EXPECT_EQ(size_t(0), p->issueCount());

    libcellml::ValidatorPtr v = libcellml::Validator::create();
    v->validateModel(m);
    EXPECT_EQ_ISSUES(expectedIssues, v);
}

TEST(Validator, validateInvalidConnectionsVariableWithoutParentComponent)
{
    const std::vector<std::string> expectedIssues = {
        "Variable 'variable2' is an equivalent variable to 'variable1' but 'variable2' has no parent component.",
    };
    libcellml::ModelPtr m = libcellml::Model::create();
    libcellml::ComponentPtr comp1 = libcellml::Component::create();
    libcellml::ComponentPtr comp2 = libcellml::Component::create();
    libcellml::VariablePtr v1 = libcellml::Variable::create();
    libcellml::VariablePtr v2 = libcellml::Variable::create();

    m->setName("modelName");
    comp1->setName("component1");
    comp2->setName("component2");

    v1->setName("variable1");
    v2->setName("variable2");
    v1->setUnits("dimensionless");
    v2->setUnits("dimensionless");

    comp1->addVariable(v1);
    comp2->addVariable(v2);

    m->addComponent(comp1);
    m->addComponent(comp2);

    libcellml::Variable::addEquivalence(v1, v2);

    comp2->removeVariable(v2);

    libcellml::ValidatorPtr v = libcellml::Validator::create();
    v->validateModel(m);
    EXPECT_EQ_ISSUES(expectedIssues, v);
}

TEST(Validator, integerStrings)
{
    const std::string in =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/2.0#\" name=\"asoiaf\">\n"
        "  <component name=\"component\">\n"
        "    <variable name=\"variable\" units=\"dimensionless\"/>\n"
        "    <variable name=\"other_variable\" units=\"dimensionless\"/>\n"
        "    <reset variable=\"variable\" test_variable=\"other_variable\" order=\"1\">\n"
        "      <test_value>\n"
        "        <math xmlns=\"http://www.w3.org/1998/Math/MathML\">\n"
        "        </math>\n"
        "      </test_value>\n"
        "      <reset_value>\n"
        "        <math xmlns=\"http://www.w3.org/1998/Math/MathML\">\n"
        "        </math>\n"
        "      </reset_value>\n"
        "    </reset>\n"
        "    <reset variable=\"variable\" test_variable=\"other_variable\" order=\"+1\">\n"
        "      <test_value>\n"
        "        <math xmlns=\"http://www.w3.org/1998/Math/MathML\">\n"
        "        </math>\n"
        "      </test_value>\n"
        "      <reset_value>\n"
        "        <math xmlns=\"http://www.w3.org/1998/Math/MathML\">\n"
        "        </math>\n"
        "      </reset_value>\n"
        "    </reset>\n"
        "    <reset variable=\"variable\" test_variable=\"other_variable\" order=\"\">\n"
        "      <test_value>\n"
        "        <math xmlns=\"http://www.w3.org/1998/Math/MathML\">\n"
        "        </math>\n"
        "      </test_value>\n"
        "      <reset_value>\n"
        "        <math xmlns=\"http://www.w3.org/1998/Math/MathML\">\n"
        "        </math>\n"
        "      </reset_value>\n"
        "    </reset>\n"
        "    <reset variable=\"variable\" test_variable=\"other_variable\" order=\"-\">\n"
        "      <test_value>\n"
        "        <math xmlns=\"http://www.w3.org/1998/Math/MathML\">\n"
        "        </math>\n"
        "      </test_value>\n"
        "      <reset_value>\n"
        "        <math xmlns=\"http://www.w3.org/1998/Math/MathML\">\n"
        "        </math>\n"
        "      </reset_value>\n"
        "    </reset>\n"
        "    <reset variable=\"variable\" test_variable=\"other_variable\" order=\"odd\">\n"
        "      <test_value>\n"
        "        <math xmlns=\"http://www.w3.org/1998/Math/MathML\">\n"
        "        </math>\n"
        "      </test_value>\n"
        "      <reset_value>\n"
        "        <math xmlns=\"http://www.w3.org/1998/Math/MathML\">\n"
        "        </math>\n"
        "      </reset_value>\n"
        "    </reset>\n"
        "    <reset variable=\"variable\" test_variable=\"other_variable\" order=\"12345678901\">\n"
        "      <test_value>\n"
        "        <math xmlns=\"http://www.w3.org/1998/Math/MathML\">\n"
        "        </math>\n"
        "      </test_value>\n"
        "      <reset_value>\n"
        "        <math xmlns=\"http://www.w3.org/1998/Math/MathML\">\n"
        "        </math>\n"
        "      </reset_value>\n"
        "    </reset>\n"
        "  </component>\n"
        "</model>\n";

    const std::vector<std::string> expectedParsingErrors = {
        "Reset in component 'component' referencing variable 'variable' has a non-integer order value '+1'.",
        "Reset in component 'component' referencing variable 'variable' has a non-integer order value ''.",
        "Reset in component 'component' referencing variable 'variable' has a non-integer order value '-'.",
        "Reset in component 'component' referencing variable 'variable' has a non-integer order value 'odd'.",
        "Reset in component 'component' referencing variable 'variable' has an out of range integer order value '12345678901'.",
    };

    const std::vector<std::string> expectedValidationErrors = {
        "Reset in component 'component' with variable 'variable', with test_variable 'other_variable', does not have an order set.",
        "Reset in component 'component' with variable 'variable', with test_variable 'other_variable', does not have an order set.",
        "Reset in component 'component' with variable 'variable', with test_variable 'other_variable', does not have an order set.",
        "Reset in component 'component' with variable 'variable', with test_variable 'other_variable', does not have an order set.",
        "Reset in component 'component' with variable 'variable', with test_variable 'other_variable', does not have an order set.",
    };

    libcellml::ParserPtr p = libcellml::Parser::create();
    libcellml::ModelPtr m = p->parseModel(in);

    EXPECT_EQ_ISSUES(expectedParsingErrors, p);

    libcellml::ValidatorPtr v = libcellml::Validator::create();
    v->validateModel(m);

    EXPECT_EQ_ISSUES(expectedValidationErrors, v);
}

TEST(Validator, resetValid)
{
    libcellml::ModelPtr m = libcellml::Model::create();
    libcellml::ComponentPtr c = libcellml::Component::create();
    libcellml::VariablePtr v1 = libcellml::Variable::create();
    libcellml::VariablePtr v2 = libcellml::Variable::create();
    libcellml::ResetPtr r = libcellml::Reset::create();

    r->setVariable(v1);
    r->setTestVariable(v2);
    r->setOrder(1);
    r->setResetValue(NON_EMPTY_MATH);
    r->setTestValue(NON_EMPTY_MATH);

    c->setName("comp");
    v1->setName("var");
    v1->setUnits("second");
    v2->setName("var2");
    v2->setUnits("second");

    c->addVariable(v1);
    c->addVariable(v2);

    c->addReset(r);

    m->setName("main");
    m->addComponent(c);

    libcellml::ValidatorPtr validator = libcellml::Validator::create();
    validator->validateModel(m);

    EXPECT_EQ(size_t(0), validator->issueCount());
}

TEST(Validator, resetNoVariable)
{
    const std::string expectedError =
        "Reset in component 'comp' with order '3', with test_variable 'var2', does not reference a variable.";

    libcellml::ModelPtr m = libcellml::Model::create();
    libcellml::ComponentPtr c = libcellml::Component::create();
    libcellml::VariablePtr v1 = libcellml::Variable::create();
    libcellml::VariablePtr v2 = libcellml::Variable::create();
    libcellml::ResetPtr r = libcellml::Reset::create();

    // No variable
    r->setTestVariable(v2);
    r->setOrder(3);
    r->setResetValue(NON_EMPTY_MATH);
    r->setTestValue(NON_EMPTY_MATH);

    c->setName("comp");
    v1->setName("var");
    v1->setUnits("second");
    v2->setName("var2");
    v2->setUnits("second");

    c->addVariable(v1);
    c->addVariable(v2);

    c->addReset(r);

    m->setName("main");
    m->addComponent(c);

    libcellml::ValidatorPtr validator = libcellml::Validator::create();
    validator->validateModel(m);

    EXPECT_EQ(size_t(1), validator->issueCount());
    EXPECT_EQ(expectedError, validator->issue(0)->description());
}

TEST(Validator, resetNoTestVariable)
{
    const std::string expectedError =
        "Reset in component 'comp' with order '4', with variable 'var', does not reference a test_variable.";

    libcellml::ModelPtr m = libcellml::Model::create();
    libcellml::ComponentPtr c = libcellml::Component::create();
    libcellml::VariablePtr v1 = libcellml::Variable::create();
    libcellml::VariablePtr v2 = libcellml::Variable::create();
    libcellml::ResetPtr r = libcellml::Reset::create();

    // No test_variable
    r->setVariable(v1);
    r->setOrder(4);
    r->setResetValue(NON_EMPTY_MATH);
    r->setTestValue(NON_EMPTY_MATH);

    c->setName("comp");
    v1->setName("var");
    v1->setUnits("second");
    v2->setName("var2");
    v2->setUnits("second");

    c->addVariable(v1);
    c->addVariable(v2);

    c->addReset(r);

    m->setName("main");
    m->addComponent(c);

    libcellml::ValidatorPtr validator = libcellml::Validator::create();
    validator->validateModel(m);

    EXPECT_EQ(size_t(1), validator->issueCount());
    EXPECT_EQ(expectedError, validator->issue(0)->description());
}

TEST(Validator, resetNoOrder)
{
    const std::string expectedError =
        "Reset in component 'comp' with variable 'var', with test_variable 'var2', does not have an order set.";

    libcellml::ModelPtr m = libcellml::Model::create();
    libcellml::ComponentPtr c = libcellml::Component::create();
    libcellml::VariablePtr v1 = libcellml::Variable::create();
    libcellml::VariablePtr v2 = libcellml::Variable::create();
    libcellml::ResetPtr r = libcellml::Reset::create();

    // No order
    r->setVariable(v1);
    r->setTestVariable(v2);
    r->setResetValue(NON_EMPTY_MATH);
    r->setTestValue(NON_EMPTY_MATH);

    c->setName("comp");
    v1->setName("var");
    v1->setUnits("second");
    v2->setName("var2");
    v2->setUnits("second");

    c->addVariable(v1);
    c->addVariable(v2);

    c->addReset(r);

    m->setName("main");
    m->addComponent(c);

    libcellml::ValidatorPtr validator = libcellml::Validator::create();
    validator->validateModel(m);
    EXPECT_EQ(size_t(1), validator->issueCount());
    EXPECT_EQ(expectedError, validator->issue(0)->description());
}

TEST(Validator, resetNoResetValue)
{
    const std::string expectedError = "Reset in component 'comp' with order '6', with variable 'var', with test_variable 'var2', does not have a reset_value specified.";

    libcellml::ModelPtr m = libcellml::Model::create();
    libcellml::ComponentPtr c = libcellml::Component::create();
    libcellml::VariablePtr v1 = libcellml::Variable::create();
    libcellml::VariablePtr v2 = libcellml::Variable::create();
    libcellml::ResetPtr r = libcellml::Reset::create();

    // No reset_value
    r->setVariable(v1);
    r->setTestVariable(v2);
    r->setOrder(6);
    r->setTestValue(NON_EMPTY_MATH);

    c->setName("comp");
    v1->setName("var");
    v1->setUnits("second");
    v2->setName("var2");
    v2->setUnits("second");

    c->addVariable(v1);
    c->addVariable(v2);

    c->addReset(r);

    m->setName("main");
    m->addComponent(c);

    libcellml::ValidatorPtr validator = libcellml::Validator::create();
    validator->validateModel(m);

    EXPECT_EQ(size_t(1), validator->issueCount());
    EXPECT_EQ(expectedError, validator->issue(0)->description());
}

TEST(Validator, resetMultipleMathMLInResetValue)
{
    libcellml::ModelPtr m = libcellml::Model::create();
    libcellml::ComponentPtr c = libcellml::Component::create();
    libcellml::VariablePtr v1 = libcellml::Variable::create();
    libcellml::VariablePtr v2 = libcellml::Variable::create();
    libcellml::ResetPtr r = libcellml::Reset::create();

    // Multiple MathML in reset_value
    r->setVariable(v1);
    r->setTestVariable(v2);
    r->setOrder(6);
    r->setResetValue(NON_EMPTY_MATH + NON_EMPTY_MATH);
    r->setTestValue(NON_EMPTY_MATH);

    c->setName("comp");
    v1->setName("var");
    v1->setUnits("second");
    v2->setName("var2");
    v2->setUnits("second");

    c->addVariable(v1);
    c->addVariable(v2);

    c->addReset(r);

    m->setName("main");
    m->addComponent(c);

    libcellml::ValidatorPtr validator = libcellml::Validator::create();
    validator->validateModel(m);
    EXPECT_EQ(size_t(0), validator->errorCount());
}

TEST(Validator, resetNoTestValue)
{
    const std::vector<std::string> expectedIssues = {
        "Reset in component 'comp' with order '7', with variable 'var', with test_variable 'var2', does not have a test_value specified.",
    };

    libcellml::ModelPtr m = libcellml::Model::create();
    libcellml::ComponentPtr c = libcellml::Component::create();
    libcellml::VariablePtr v1 = libcellml::Variable::create();
    libcellml::VariablePtr v2 = libcellml::Variable::create();
    libcellml::ResetPtr r = libcellml::Reset::create();

    // No test_value
    r->setVariable(v1);
    r->setTestVariable(v2);
    r->setOrder(7);
    r->setResetValue(NON_EMPTY_MATH);

    c->setName("comp");
    v1->setName("var");
    v1->setUnits("second");
    v2->setName("var2");
    v2->setUnits("second");

    c->addVariable(v1);
    c->addVariable(v2);

    c->addReset(r);

    m->setName("main");
    m->addComponent(c);

    libcellml::ValidatorPtr validator = libcellml::Validator::create();
    validator->validateModel(m);

    EXPECT_EQ_ISSUES(expectedIssues, validator);
}

TEST(Validator, resetMultipleMathMLInTestValue)
{
    libcellml::ModelPtr m = libcellml::Model::create();
    libcellml::ComponentPtr c = libcellml::Component::create();
    libcellml::VariablePtr v1 = libcellml::Variable::create();
    libcellml::VariablePtr v2 = libcellml::Variable::create();
    libcellml::ResetPtr r = libcellml::Reset::create();

    // Multiple MathML blocks in test_value
    r->setVariable(v1);
    r->setTestVariable(v2);
    r->setOrder(6);
    r->setResetValue(NON_EMPTY_MATH);
    r->setTestValue(NON_EMPTY_MATH + NON_EMPTY_MATH);

    c->setName("comp");
    v1->setName("var");
    v1->setUnits("second");
    v2->setName("var2");
    v2->setUnits("second");

    c->addVariable(v1);
    c->addVariable(v2);

    c->addReset(r);

    m->setName("main");
    m->addComponent(c);

    libcellml::ValidatorPtr validator = libcellml::Validator::create();
    validator->validateModel(m);
    EXPECT_EQ(size_t(0), validator->errorCount());
}

TEST(Validator, resetWhitespaceAsMaths)
{
    const std::vector<std::string> expectedIssues = {
        "Reset in component 'comp' with order '8', with variable 'var', with test_variable 'var2', does not have a test_value specified.",
        "Reset in component 'comp' with order '8', with variable 'var', with test_variable 'var2', does not have a reset_value specified.",
    };

    libcellml::ModelPtr m = libcellml::Model::create();
    libcellml::ComponentPtr c = libcellml::Component::create();
    libcellml::VariablePtr v1 = libcellml::Variable::create();
    libcellml::VariablePtr v2 = libcellml::Variable::create();
    libcellml::ResetPtr r = libcellml::Reset::create();

    // Whitespace test_value and reset_value
    r->setVariable(v1);
    r->setTestVariable(v2);
    r->setOrder(8);
    r->setResetValue(" ");
    r->setTestValue(" ");

    c->setName("comp");
    v1->setName("var");
    v1->setUnits("second");
    v2->setName("var2");
    v2->setUnits("second");

    c->addVariable(v1);
    c->addVariable(v2);

    c->addReset(r);

    m->setName("main");
    m->addComponent(c);

    libcellml::ValidatorPtr validator = libcellml::Validator::create();
    validator->validateModel(m);

    EXPECT_EQ_ISSUES(expectedIssues, validator);
}

TEST(Validator, resetEmptyMathML)
{
    libcellml::ModelPtr m = libcellml::Model::create();
    libcellml::ComponentPtr c = libcellml::Component::create();
    libcellml::VariablePtr v1 = libcellml::Variable::create();
    libcellml::VariablePtr v2 = libcellml::Variable::create();
    libcellml::ResetPtr r = libcellml::Reset::create();

    // Empty test_value and reset_value math block
    // TODO: For now, empty maths blocks are valid. Issue #365.
    r->setVariable(v1);
    r->setTestVariable(v2);
    r->setOrder(9);
    r->setResetValue(EMPTY_MATH);
    r->setTestValue(EMPTY_MATH);

    c->setName("comp");
    v1->setName("var");
    v1->setUnits("second");
    v2->setName("var2");
    v2->setUnits("second");

    c->addVariable(v1);
    c->addVariable(v2);

    c->addReset(r);

    m->setName("main");
    m->addComponent(c);

    libcellml::ValidatorPtr validator = libcellml::Validator::create();
    validator->validateModel(m);

    EXPECT_EQ(size_t(0), validator->issueCount());
}

TEST(Validator, resetNegativeOrder)
{
    libcellml::ModelPtr m = libcellml::Model::create();
    libcellml::ComponentPtr c = libcellml::Component::create();
    libcellml::VariablePtr v1 = libcellml::Variable::create();
    libcellml::VariablePtr v2 = libcellml::Variable::create();
    libcellml::ResetPtr r = libcellml::Reset::create();

    // Negative order value should be allowed
    r->setVariable(v1);
    r->setTestVariable(v2);
    r->setOrder(-100);
    r->setResetValue(NON_EMPTY_MATH);
    r->setTestValue(NON_EMPTY_MATH);

    c->setName("comp");
    v1->setName("var");
    v1->setUnits("second");
    v2->setName("var2");
    v2->setUnits("second");

    c->addVariable(v1);
    c->addVariable(v2);

    c->addReset(r);

    m->setName("main");
    m->addComponent(c);

    libcellml::ValidatorPtr validator = libcellml::Validator::create();
    validator->validateModel(m);

    EXPECT_EQ(size_t(0), validator->issueCount());
}

TEST(Validator, resetVariableOutsideComponent)
{
    const std::vector<std::string> expectedIssues = {
        "Reset in component 'c1' with order '1', with variable 'v2', with test_variable 'v1', refers to a variable 'v2' in a different component 'c2'.",
        "Reset in component 'c2' with order '1', with variable 'v2', with test_variable 'v1', refers to a test_variable 'v1' in a different component 'c1'.",
    };

    libcellml::ModelPtr m = libcellml::Model::create();
    libcellml::ComponentPtr c1 = libcellml::Component::create();
    libcellml::ComponentPtr c2 = libcellml::Component::create();
    libcellml::VariablePtr v1 = libcellml::Variable::create();
    libcellml::VariablePtr v2 = libcellml::Variable::create();
    libcellml::ResetPtr r1 = libcellml::Reset::create();
    libcellml::ResetPtr r2 = libcellml::Reset::create();
    libcellml::ValidatorPtr validator = libcellml::Validator::create();

    v1->setName("v1");
    v1->setUnits("dimensionless");
    v2->setName("v2");
    v2->setUnits("dimensionless");

    c1->setName("c1");
    c2->setName("c2");

    c1->addVariable(v1);
    c2->addVariable(v2);

    c1->addReset(r1);
    c2->addReset(r2);

    r1->setVariable(v2); // variable outside parent component
    r1->setTestVariable(v1);
    r1->setOrder(1);
    r1->setResetValue(EMPTY_MATH);
    r1->setTestValue(EMPTY_MATH);

    r2->setVariable(v2);
    r2->setTestVariable(v1); // test_variable outside parent component
    r2->setOrder(1);
    r2->setResetValue(EMPTY_MATH);
    r2->setTestValue(EMPTY_MATH);

    m->setName("model");
    m->addComponent(c1);
    m->addComponent(c2);

    validator->validateModel(m);

    EXPECT_EQ_ISSUES(expectedIssues, validator);
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

    libcellml::ValidatorPtr v = libcellml::Validator::create();
    libcellml::ModelPtr m = libcellml::Model::create();
    libcellml::ComponentPtr c = libcellml::Component::create();
    libcellml::VariablePtr v1 = libcellml::Variable::create();

    m->setName("modelName");
    c->setName("componentName");
    v1->setName("C");
    v1->setInitialValue("3.5");
    v1->setUnits("dimensionless");

    c->addVariable(v1);
    c->setMath(math);
    m->addComponent(c);

    v->validateModel(m);
    EXPECT_EQ(size_t(0), v->issueCount());
}

TEST(Validator, validMathCnElementsMissingCellMLNamespace)
{
    const std::string math =
        "<math xmlns=\"http://www.w3.org/1998/Math/MathML\">\n"
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

    const std::vector<std::string> expectedIssues {
        "LibXml2 error: Namespace prefix cellml for units on cn is not defined.",
        "LibXml2 error: Namespace prefix cellml for units on cn is not defined.",
        "CellML identifiers must contain one or more basic Latin alphabetic characters.",
        "Math cn element with the value '3.44' does not have a valid cellml:units attribute.",
        "CellML identifiers must contain one or more basic Latin alphabetic characters.",
        "Math cn element with the value '-9.612' does not have a valid cellml:units attribute.",
        "W3C MathML DTD error: Namespace prefix cellml for units on cn is not defined.",
        "W3C MathML DTD error: No declaration for attribute cellml:units of element cn.",
        "W3C MathML DTD error: Namespace prefix cellml for units on cn is not defined.",
        "W3C MathML DTD error: No declaration for attribute cellml:units of element cn.",
    };

    libcellml::ValidatorPtr v = libcellml::Validator::create();
    libcellml::ModelPtr m = libcellml::Model::create();
    libcellml::ComponentPtr c = libcellml::Component::create();
    libcellml::VariablePtr v1 = libcellml::Variable::create();

    m->setName("modelName");
    c->setName("componentName");
    v1->setName("C");
    v1->setInitialValue("3.5");
    v1->setUnits("dimensionless");

    c->addVariable(v1);
    c->setMath(math);
    m->addComponent(c);

    v->validateModel(m);
    EXPECT_EQ_ISSUES(expectedIssues, v);
}

TEST(Validator, unitAmericanSpellingOfUnitsRemoved)
{
    const std::vector<std::string> expectedErrors = {
        "Variable 'tomahto' in component 'comp2' has a units reference 'testunit2' which is neither standard nor defined in the parent model.",
        "Units reference 'meter' in units 'testunit2' is not a valid reference to a local units or a standard unit type.",
        "Variable 'tomayto' has units of 'testunit1' and an equivalent variable 'tomahto' with non-matching units of 'testunit2'. The mismatch is: metre^1.",
    };

    libcellml::ValidatorPtr validator = libcellml::Validator::create();
    libcellml::ModelPtr m = libcellml::Model::create();
    libcellml::ComponentPtr comp1 = libcellml::Component::create();
    libcellml::ComponentPtr comp2 = libcellml::Component::create();

    libcellml::VariablePtr v1 = libcellml::Variable::create();
    libcellml::VariablePtr v2 = libcellml::Variable::create();

    v1->setName("tomayto");
    v1->setInterfaceType("public");
    v2->setName("tomahto");
    v2->setInterfaceType("public");
    m->setName("callthewholethingoff");
    comp1->addVariable(v1);
    comp2->addVariable(v2);
    comp1->setName("comp1");
    comp2->setName("comp2");
    m->addComponent(comp1);
    m->addComponent(comp2);

    // u1 = u2: different spelling of meter/metre.
    libcellml::UnitsPtr u1 = libcellml::Units::create();
    u1->setName("testunit1");
    u1->addUnit("metre");
    libcellml::UnitsPtr u2 = libcellml::Units::create();
    u2->setName("testunit2");
    u2->addUnit("meter");

    v1->setUnits(u1);
    v2->setUnits(u2);
    m->addUnits(u1);
    m->addUnits(u2);

    const std::vector<std::string> expectedIssues = {
        "Variable 'tomahto' in component 'comp2' has a units reference 'testunit2' which is neither standard nor defined in the parent model.",
        "Units reference 'meter' in units 'testunit2' is not a valid reference to a local units or a standard unit type.",
        "Variable 'tomayto' in component 'comp1' has units of 'testunit1' and an equivalent variable 'tomahto' in component 'comp2' with non-matching units of 'testunit2'. The mismatch is: metre^1.",
    };

    // This one is now an issue.
    libcellml::Variable::addEquivalence(v1, v2);
    validator->validateModel(m);

    EXPECT_EQ_ISSUES(expectedIssues, validator);
}

TEST(Validator, unitEquivalenceStandardUnitsToBaseUnits)
{
    libcellml::ValidatorPtr validator = libcellml::Validator::create();
    libcellml::ModelPtr m = libcellml::Model::create();
    libcellml::ComponentPtr comp1 = libcellml::Component::create();
    libcellml::ComponentPtr comp2 = libcellml::Component::create();
    libcellml::VariablePtr v1 = libcellml::Variable::create();
    libcellml::VariablePtr v2 = libcellml::Variable::create();
    libcellml::UnitsPtr base = libcellml::Units::create();
    libcellml::UnitsPtr standard = libcellml::Units::create();

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
        validator->validateModel(m);
        EXPECT_EQ(size_t(0), validator->issueCount());
    }
}

TEST(Validator, unitEquivalenceBasicDimensionlessUnits)
{
    libcellml::ValidatorPtr validator = libcellml::Validator::create();
    libcellml::ModelPtr m = libcellml::Model::create();
    libcellml::ComponentPtr comp1 = libcellml::Component::create();
    libcellml::ComponentPtr comp2 = libcellml::Component::create();

    libcellml::VariablePtr v1 = libcellml::Variable::create();
    libcellml::VariablePtr v2 = libcellml::Variable::create();

    v1->setName("tomayto");
    v1->setInterfaceType("public");
    v2->setName("tomahto");
    v2->setInterfaceType("public");

    m->setName("callthewholethingoff");
    comp1->addVariable(v1);
    comp2->addVariable(v2);
    comp1->setName("comp1");
    comp2->setName("comp2");
    m->addComponent(comp1);
    m->addComponent(comp2);

    // u1 = u2: testing that cancelled units become dimensionless.
    libcellml::UnitsPtr u1 = libcellml::Units::create();
    u1->setName("metrepermetre");
    u1->addUnit("metre");
    u1->addUnit("metre", -1.0);
    libcellml::UnitsPtr u2 = libcellml::Units::create();
    u2->setName("ratio");
    u2->addUnit("dimensionless");

    v1->setUnits(u1);
    v2->setUnits(u2);

    m->addUnits(u1);
    m->addUnits(u2);

    libcellml::Variable::addEquivalence(v1, v2);

    validator->validateModel(m);
    EXPECT_EQ(size_t(0), validator->issueCount());
}

TEST(Validator, unitEquivalenceDimensionlessUnits)
{
    libcellml::ValidatorPtr validator = libcellml::Validator::create();
    libcellml::ModelPtr m = libcellml::Model::create();
    libcellml::ComponentPtr comp1 = libcellml::Component::create();
    libcellml::ComponentPtr comp2 = libcellml::Component::create();
    libcellml::ComponentPtr comp3 = libcellml::Component::create();

    libcellml::VariablePtr v1 = libcellml::Variable::create();
    libcellml::VariablePtr v2 = libcellml::Variable::create();
    libcellml::VariablePtr v3 = libcellml::Variable::create();

    v1->setName("tomayto");
    v2->setName("tomahto");
    v3->setName("tomaat");

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
    libcellml::UnitsPtr u1 = libcellml::Units::create();
    u1->setName("testunit5");
    u1->addUnit("metre", -2.0);
    u1->addUnit("metre", 2.0);
    libcellml::UnitsPtr u2 = libcellml::Units::create();
    u2->setName("testunit6");
    u2->addUnit("dimensionless");
    libcellml::UnitsPtr u3 = libcellml::Units::create();
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

    m->fixVariableInterfaces();

    validator->validateModel(m);
    EXPECT_EQ(size_t(0), validator->issueCount());
}

TEST(Validator, unitEquivalenceMultiplierPrefix)
{
    libcellml::ValidatorPtr validator = libcellml::Validator::create();
    libcellml::ModelPtr m = libcellml::Model::create();
    libcellml::ComponentPtr comp1 = libcellml::Component::create();
    libcellml::ComponentPtr comp2 = libcellml::Component::create();
    libcellml::ComponentPtr comp3 = libcellml::Component::create();

    libcellml::VariablePtr v1 = libcellml::Variable::create();
    libcellml::VariablePtr v2 = libcellml::Variable::create();
    libcellml::VariablePtr v3 = libcellml::Variable::create();

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
    libcellml::UnitsPtr u1 = libcellml::Units::create();
    u1->setName("testunit10");
    u1->addUnit("gram", 2, 1000.0);
    libcellml::UnitsPtr u2 = libcellml::Units::create();
    u2->setName("testunit11");
    u2->addUnit("kilogram", 2.0);
    libcellml::UnitsPtr u3 = libcellml::Units::create();
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

    validator->validateModel(m);
    EXPECT_EQ(size_t(0), validator->issueCount());
}

TEST(Validator, unitEquivalenceComplicatedNestedUnits)
{
    const std::vector<std::string> expectedIssues = {
        "Variable 'pjs' in component 'yousay' has units of 'testunit13' and an equivalent variable 'pajamas' in component 'wesay' with non-matching units of 'testunit14'. The mismatch is: metre^1, multiplication factor of 10^3.",
    };

    libcellml::ValidatorPtr validator = libcellml::Validator::create();
    libcellml::ModelPtr m = libcellml::Model::create();
    libcellml::ComponentPtr comp1 = libcellml::Component::create();
    libcellml::ComponentPtr comp2 = libcellml::Component::create();
    libcellml::ComponentPtr comp3 = libcellml::Component::create();

    libcellml::VariablePtr v1 = libcellml::Variable::create();
    libcellml::VariablePtr v8 = libcellml::Variable::create();
    libcellml::VariablePtr v9 = libcellml::Variable::create();
    libcellml::VariablePtr v13 = libcellml::Variable::create();
    libcellml::VariablePtr v14 = libcellml::Variable::create();

    v1->setName("tomayto");
    v8->setName("neether");
    v9->setName("nyther");
    v13->setName("pjs");
    v14->setName("pajamas");

    comp1->setName("isay");
    comp2->setName("yousay");
    comp3->setName("wesay");

    m->setName("callthewholethingoff");

    comp1->addVariable(v1);
    comp2->addVariable(v8);
    comp3->addVariable(v9);
    comp2->addVariable(v13);
    comp3->addVariable(v14);

    m->addComponent(comp1);
    m->addComponent(comp2);
    m->addComponent(comp3);

    libcellml::UnitsPtr u1 = libcellml::Units::create();
    u1->setName("testunit1");
    u1->addUnit("metre");

    // u8 = u9: testing more complicated compound units, newton/(sievert.pascal) = second^2.radian^3.steradian^-4.
    libcellml::UnitsPtr u8 = libcellml::Units::create();
    u8->setName("testunit8");
    u8->addUnit("newton", 1.0);
    u8->addUnit("pascal", -1.0);
    u8->addUnit("sievert", -1.0);
    libcellml::UnitsPtr u9 = libcellml::Units::create();
    u9->setName("testunit9");
    u9->addUnit("second", 2.0);
    u9->addUnit("radian", -4.0);
    u9->addUnit("steradian", 2.0);

    // u13 != u14: testing that the mismatch is reported correctly.
    libcellml::UnitsPtr u13 = libcellml::Units::create();
    u13->setName("testunit13");
    u13->addUnit("testunit1", "kilo", 2.0);
    u13->addUnit("testunit8", 2.0);
    libcellml::UnitsPtr u14 = libcellml::Units::create();
    u14->setName("testunit14");
    u14->addUnit("testunit1", 1.0);
    u14->addUnit("testunit9", 2.0);

    v1->setUnits(u1);
    v8->setUnits(u8);
    v9->setUnits(u9);
    v13->setUnits(u13);
    v14->setUnits(u14);

    m->addUnits(u1);
    m->addUnits(u8);
    m->addUnits(u9);
    m->addUnits(u13);
    m->addUnits(u14);

    // This one is fine but complicated: newton/(sievert.pascal) = second^2.radian^3.steradian^-4.
    libcellml::Variable::addEquivalence(v8, v9);

    // Off by (metre)^1: testing nested unit equivalence.
    libcellml::Variable::addEquivalence(v13, v14);

    m->fixVariableInterfaces();

    validator->validateModel(m);

    EXPECT_EQ_ISSUES(expectedIssues, validator);
}

TEST(Validator, unitUserCreatedUnitsBananasAndApples)
{
    const std::vector<std::string> expectedIssues = {
        "Variable 'v1' in component 'c1' has units of 'bushell_of_apples' and an equivalent variable 'v2' in component 'c2' with non-matching units of 'bunch_of_bananas'. The mismatch is: apple^10, banana^-5.",
    };

    libcellml::ValidatorPtr validator = libcellml::Validator::create();
    libcellml::ModelPtr m = createModelTwoComponentsWithOneVariableEach("m", "c1", "c2", "v1", "v2");
    auto c1 = m->component(0);
    auto c2 = m->component(1);
    auto v1 = c1->variable(0);
    auto v2 = c2->variable(0);

    libcellml::UnitsPtr uApple = libcellml::Units::create();
    uApple->setName("apple");

    libcellml::UnitsPtr uBanana = libcellml::Units::create();
    uBanana->setName("banana");

    libcellml::UnitsPtr u1 = libcellml::Units::create();
    u1->setName("bushell_of_apples");
    u1->addUnit("apple", 10.0);

    libcellml::UnitsPtr u2 = libcellml::Units::create();
    u2->setName("bunch_of_bananas");
    u2->addUnit("banana", 5.0);

    v1->setUnits(u1);
    v2->setUnits(u2);

    m->addUnits(uApple);
    m->addUnits(uBanana);
    m->addUnits(u1);
    m->addUnits(u2);

    libcellml::Variable::addEquivalence(v1, v2); // Bushell of apples != bunch of bananas.

    validator->validateModel(m);

    EXPECT_EQ_ISSUES(expectedIssues, validator);
}

TEST(Validator, unitIllDefinedEquivalentUnits)
{
    const std::vector<std::string> expectedIssues = {
        "CellML identifiers must contain one or more basic Latin alphabetic characters.",
        "Variable 'v1' does not have a valid units attribute.",
        "CellML identifiers must contain one or more basic Latin alphabetic characters.",
        "Variable 'v2' does not have a valid units attribute.",
        "Variable 'v1' in component 'c1' has units of '' and an equivalent variable 'v2' in component 'c2' with non-matching units of ''. The mismatch is: ",
    };

    libcellml::ValidatorPtr validator = libcellml::Validator::create();
    libcellml::ModelPtr m = createModelTwoComponentsWithOneVariableEach("m", "c1", "c2", "v1", "v2");
    auto c1 = m->component(0);
    auto c2 = m->component(1);
    auto v1 = c1->variable(0);
    auto v2 = c2->variable(0);

    libcellml::Variable::addEquivalence(v1, v2);

    validator->validateModel(m);

    EXPECT_EQ_ISSUES(expectedIssues, validator);
}

TEST(Validator, unitStandardUnitsWhichAreBaseUnits)
{
    const std::vector<std::string> expectedIssues = {
        "Variable 'v1' in component 'c1' has units of 'metre' and an equivalent variable 'v2' in component 'c2' with non-matching units of 'second'. The mismatch is: metre^1, second^-1.",
    };

    libcellml::ValidatorPtr validator = libcellml::Validator::create();
    libcellml::ModelPtr m = createModelTwoComponentsWithOneVariableEach("m", "c1", "c2", "v1", "v2");
    auto c1 = m->component(0);
    auto c2 = m->component(1);
    auto v1 = c1->variable(0);
    auto v2 = c2->variable(0);

    v1->setUnits("metre");
    v2->setUnits("second");

    libcellml::Variable::addEquivalence(v1, v2); // metre != second.

    validator->validateModel(m);

    EXPECT_EQ_ISSUES(expectedIssues, validator);
}

TEST(Validator, unitStandardUnitsWhichAreNotBaseUnits)
{
    const std::vector<std::string> expectedIssues = {
        "Variable 'v1' in component 'c1' has units of 'litre' and an equivalent variable 'v2' in component 'c2' with non-matching units of 'gram'. The mismatch is: kilogram^-1, metre^3.",
    };

    libcellml::ValidatorPtr validator = libcellml::Validator::create();
    libcellml::ModelPtr m = createModelTwoComponentsWithOneVariableEach("m", "c1", "c2", "v1", "v2");
    auto c1 = m->component(0);
    auto c2 = m->component(1);
    auto v1 = c1->variable(0);
    auto v2 = c2->variable(0);

    v1->setUnits("litre");
    v2->setUnits("gram");

    libcellml::Variable::addEquivalence(v1, v2); // litre != gram.

    validator->validateModel(m);

    EXPECT_EQ_ISSUES(expectedIssues, validator);
}

TEST(Validator, unitSimpleCycle)
{
    // Testing that indirect dependence is caught in the unit cycles. The network is:
    //
    //      grandfather(u1) <- father(u2) <- child (u3) <-+
    //           |                                        |
    //           +----------------------------------------+

    const std::vector<std::string> expectedIssues = {
        "Cyclic units exist: 'grandfather' -> 'child' -> 'father' -> 'grandfather'",
    };

    libcellml::ValidatorPtr v = libcellml::Validator::create();
    libcellml::ModelPtr m = libcellml::Model::create();

    libcellml::UnitsPtr u1 = libcellml::Units::create();
    libcellml::UnitsPtr u2 = libcellml::Units::create();
    libcellml::UnitsPtr u3 = libcellml::Units::create();

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
    v->validateModel(m);
    EXPECT_EQ(size_t(0), v->issueCount());

    // Time loop Grandfather paradox created! u1 no longer a base variable: u1 -> u3 -> u2 -> u1.
    u1->addUnit("child");
    v->validateModel(m);

    EXPECT_EQ_ISSUES(expectedIssues, v);
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

    libcellml::ValidatorPtr v = libcellml::Validator::create();
    libcellml::ModelPtr m = libcellml::Model::create();

    libcellml::UnitsPtr u1 = libcellml::Units::create();
    libcellml::UnitsPtr u2 = libcellml::Units::create();
    libcellml::UnitsPtr u3 = libcellml::Units::create();
    libcellml::UnitsPtr u4 = libcellml::Units::create();
    libcellml::UnitsPtr u5 = libcellml::Units::create();
    libcellml::UnitsPtr u6 = libcellml::Units::create();

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

    v->validateModel(m);
    EXPECT_EQ(size_t(0), v->issueCount());

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

    const std::vector<std::string> expectedIssues = {
        "Cyclic units exist: 'grandfather' -> 'brotherFromAnotherMother' -> 'father' -> 'grandfather'",
    };

    // Time loop Grandfather paradox created! u1 no longer a base variable: u1 -> u4 -> u2 -> u1.
    u1->addUnit("brotherFromAnotherMother");
    v->validateModel(m);

    EXPECT_EQ_ISSUES(expectedIssues, v);
}

TEST(Validator, duplicatedCellMLUnitsOnCiElement)
{
    const std::string math =
        "<math xmlns:cellml=\"http://www.cellml.org/cellml/2.0#\" xmlns=\"http://www.w3.org/1998/Math/MathML\">\n"
        "  <ci cellml:units=\"dimensionless\" cellml:units=\"second\">B</ci>\n"
        "</math>\n";

    const std::vector<std::string> expectedIssues = {
        "LibXml2 error: Attribute cellml:units redefined.",
        "Could not get a valid XML root node from the math on component 'componentName'.",
    };

    libcellml::ValidatorPtr v = libcellml::Validator::create();
    libcellml::ModelPtr m = libcellml::Model::create();
    libcellml::ComponentPtr c = libcellml::Component::create();
    libcellml::VariablePtr v1 = libcellml::Variable::create();

    m->setName("modelName");
    c->setName("componentName");
    v1->setName("B");
    v1->setUnits("second");
    c->addVariable(v1);

    c->setMath(math);
    m->addComponent(c);

    v->validateModel(m);

    EXPECT_EQ_ISSUES(expectedIssues, v);
}

TEST(Validator, multipleDefinitionsOfCellMLNamespace)
{
    libcellml::ParserPtr parser = libcellml::Parser::create();
    libcellml::ModelPtr model = parser->parseModel(fileContents("multiplecellmlnamespaces.cellml"));

    libcellml::ValidatorPtr validator = libcellml::Validator::create();
    validator->validateModel(model);

    EXPECT_EQ(size_t(0), validator->issueCount());
}

TEST(Validator, validateModelWithoutAndWithMath)
{
    libcellml::ModelPtr model = libcellml::Model::create();
    libcellml::ComponentPtr c1 = libcellml::Component::create();
    libcellml::ComponentPtr c2 = libcellml::Component::create();
    libcellml::ComponentPtr c3 = libcellml::Component::create();

    libcellml::ValidatorPtr validator = libcellml::Validator::create();

    model->setName("model");
    c1->setName("c1");
    c2->setName("c2");
    c3->setName("c3");

    model->addComponent(c1);
    model->addComponent(c2);
    c2->addComponent(c3);

    libcellml::VariablePtr v = libcellml::Variable::create();
    v->setName("v");
    v->setUnits("dimensionless");
    c3->addVariable(v);

    validator->validateModel(model);
    EXPECT_EQ(size_t(0), validator->issueCount());

    const std::string math =
        "<math xmlns=\"http://www.w3.org/1998/Math/MathML\" xmlns:cellml=\"http://www.cellml.org/cellml/2.0#\">\n"
        "  <apply>\n"
        "    <eq/>\n"
        "    <ci>v</ci>\n"
        "    <cn cellml:units=\"dimensionless\">1</cn>\n"
        "  </apply>\n"
        "</math>\n";

    c3->setMath(math);

    validator->validateModel(model);
    EXPECT_EQ(size_t(0), validator->issueCount());
}

TEST(Validator, unfoundUnitsInEncapsulatedComponents)
{
    const std::vector<std::string> expectedIssues = {
        "Variable 'v' in component 'c3' has a units reference 'non_existent_deep' which is neither standard nor defined in the parent model.",
        "Variable 'v' in component 'c2' has a units reference 'non_existent_shallow' which is neither standard nor defined in the parent model.",
    };

    libcellml::ModelPtr model = libcellml::Model::create();
    libcellml::ComponentPtr c1 = libcellml::Component::create();
    libcellml::ComponentPtr c2 = libcellml::Component::create();
    libcellml::ComponentPtr c3 = libcellml::Component::create();

    libcellml::ValidatorPtr v = libcellml::Validator::create();

    model->setName("model");
    c1->setName("c1");
    c2->setName("c2");
    c3->setName("c3");

    model->addComponent(c1);
    model->addComponent(c2);
    c2->addComponent(c3);

    c1->addVariable(createVariableWithUnits("v", "dimensionless"));
    c2->addVariable(createVariableWithUnits("v", "non_existent_shallow"));
    c3->addVariable(createVariableWithUnits("v", "non_existent_deep"));

    EXPECT_TRUE(model->hasUnlinkedUnits());

    model->linkUnits();
    v->validateModel(model);

    EXPECT_EQ_ISSUES(expectedIssues, v);
}

TEST(Validator, variableEquivalenceValidNetwork)
{
    libcellml::ModelPtr model = libcellml::Model::create();
    libcellml::ComponentPtr c1 = libcellml::Component::create();
    libcellml::ComponentPtr c2 = libcellml::Component::create();
    libcellml::ComponentPtr c3 = libcellml::Component::create();

    libcellml::ValidatorPtr validator = libcellml::Validator::create();

    model->setName("model");
    c1->setName("c1");
    c2->setName("c2");
    c3->setName("c3");

    model->addComponent(c1);
    model->addComponent(c2);
    c2->addComponent(c3);

    libcellml::VariablePtr v1 = libcellml::Variable::create();
    v1->setName("v1");
    v1->setUnits("dimensionless");

    libcellml::VariablePtr v2 = libcellml::Variable::create();
    v2->setName("v2");
    v2->setUnits("dimensionless");

    libcellml::VariablePtr v3 = libcellml::Variable::create();
    v3->setName("v3");
    v3->setUnits("dimensionless");

    c1->addVariable(v1);
    c2->addVariable(v2);
    c3->addVariable(v3);

    libcellml::Variable::addEquivalence(v1, v2);
    libcellml::Variable::addEquivalence(v2, v3);

    v1->setInterfaceType("public");
    v2->setInterfaceType("public_and_private");
    v3->setInterfaceType("public");

    validator->validateModel(model);
    EXPECT_EQ(size_t(0), validator->errorCount());
}

TEST(Validator, variableEquivalenceUnreachable)
{
    const std::vector<std::string> expectedIssues {
        "The equivalence between 'v1' in component 'c1'  and 'v3' in component 'c3' is invalid. Component 'c1' and 'c3' are neither siblings nor in a parent/child relationship.",
    };

    libcellml::ModelPtr model = libcellml::Model::create();
    libcellml::ComponentPtr c1 = libcellml::Component::create();
    libcellml::ComponentPtr c2 = libcellml::Component::create();
    libcellml::ComponentPtr c3 = libcellml::Component::create();

    libcellml::ValidatorPtr validator = libcellml::Validator::create();

    model->setName("model");
    c1->setName("c1");
    c2->setName("c2");
    c3->setName("c3");

    model->addComponent(c1);
    model->addComponent(c2);
    c2->addComponent(c3);

    libcellml::VariablePtr v1 = libcellml::Variable::create();
    v1->setName("v1");
    v1->setUnits("dimensionless");

    libcellml::VariablePtr v2 = libcellml::Variable::create();
    v2->setName("v2");
    v2->setUnits("dimensionless");

    libcellml::VariablePtr v3 = libcellml::Variable::create();
    v3->setName("v3");
    v3->setUnits("dimensionless");

    c1->addVariable(v1);
    c2->addVariable(v2);
    c3->addVariable(v3);

    // invalid equivalence, too far away
    libcellml::Variable::addEquivalence(v1, v3);
    validator->validateModel(model);

    EXPECT_EQ_ISSUES(expectedIssues, validator);
}

TEST(Validator, variableEquivalenceUnreachableAndReachableTogether)
{
    const std::vector<std::string> expectedIssues = {
        "Variable 'v1' in component 'c1' has an interface type set to 'public' which is not the correct interface type for this variable. The interface type required is 'private'.",
        "The equivalence between 'v2' in component 'c2'  and 'v4' in component 'c4' is invalid. Component 'c2' and 'c4' are neither siblings nor in a parent/child relationship.",
    };

    libcellml::ModelPtr model = libcellml::Model::create();
    libcellml::ComponentPtr c1 = libcellml::Component::create();
    libcellml::ComponentPtr c2 = libcellml::Component::create();
    libcellml::ComponentPtr c3 = libcellml::Component::create();
    libcellml::ComponentPtr c4 = libcellml::Component::create();
    libcellml::ComponentPtr c5 = libcellml::Component::create();

    libcellml::ValidatorPtr validator = libcellml::Validator::create();

    model->setName("model");
    c1->setName("c1");
    c2->setName("c2");
    c3->setName("c3");
    c4->setName("c4");
    c5->setName("c5");

    model->addComponent(c1);
    c1->addComponent(c2);
    c1->addComponent(c3);
    c2->addComponent(c5);
    c3->addComponent(c4);

    libcellml::VariablePtr v1 = libcellml::Variable::create();
    v1->setName("v1");
    v1->setUnits("dimensionless");
    v1->setInterfaceType("public");

    libcellml::VariablePtr v2 = libcellml::Variable::create();
    v2->setName("v2");
    v2->setUnits("dimensionless");
    v2->setInterfaceType("public_and_private");

    libcellml::VariablePtr v3 = libcellml::Variable::create();
    v3->setName("v3");
    v3->setUnits("dimensionless");
    v3->setInterfaceType("public");

    libcellml::VariablePtr v4 = libcellml::Variable::create();
    v4->setName("v4");
    v4->setUnits("dimensionless");

    libcellml::VariablePtr v5 = libcellml::Variable::create();
    v5->setName("v5");
    v5->setUnits("dimensionless");
    v5->setInterfaceType("public");

    c1->addVariable(v1);
    c2->addVariable(v2);
    c3->addVariable(v3);
    c4->addVariable(v4);
    c5->addVariable(v5);

    libcellml::Variable::addEquivalence(v2, v4); // invalid equivalence, too far away
    libcellml::Variable::addEquivalence(v1, v2);
    libcellml::Variable::addEquivalence(v2, v3);
    libcellml::Variable::addEquivalence(v2, v5);

    validator->validateModel(model);

    EXPECT_EQ_ISSUES(expectedIssues, validator);
}

TEST(Validator, variableInterfaceShouldBePublic)
{
    const std::vector<std::string> expectedIssues = {
        "Variable 'v1' in component 'c1' has no interface type set. The interface type required is 'public'.",
        "Variable 'v2' in component 'c2' has an interface type set to 'private' which is not the correct interface type for this variable. The interface type required is 'public'.",
    };

    libcellml::ModelPtr model = libcellml::Model::create();
    libcellml::ComponentPtr c1 = libcellml::Component::create();
    libcellml::ComponentPtr c2 = libcellml::Component::create();

    libcellml::ValidatorPtr validator = libcellml::Validator::create();

    model->setName("model");
    c1->setName("c1");
    c2->setName("c2");

    model->addComponent(c1);
    model->addComponent(c2);

    libcellml::VariablePtr v1 = libcellml::Variable::create();
    v1->setName("v1");
    v1->setUnits("dimensionless");

    libcellml::VariablePtr v2 = libcellml::Variable::create();
    v2->setName("v2");
    v2->setUnits("dimensionless");

    c1->addVariable(v1);
    c2->addVariable(v2);

    libcellml::Variable::addEquivalence(v1, v2);

    v2->setInterfaceType(libcellml::Variable::InterfaceType::PRIVATE);

    validator->validateModel(model);

    EXPECT_EQ_ISSUES(expectedIssues, validator);
}

TEST(Validator, variableInterfaceShouldBePrivate)
{
    const std::vector<std::string> expectedIssues = {
        "Variable 'v1' in component 'c1' has an interface type set to 'public' which is not the correct interface type for this variable. The interface type required is 'private'.",
    };

    libcellml::ModelPtr model = libcellml::Model::create();
    libcellml::ComponentPtr c1 = libcellml::Component::create();
    libcellml::ComponentPtr c2 = libcellml::Component::create();

    libcellml::ValidatorPtr validator = libcellml::Validator::create();

    model->setName("model");
    c1->setName("c1");
    c2->setName("c2");

    model->addComponent(c1);
    c1->addComponent(c2);

    libcellml::VariablePtr v1 = libcellml::Variable::create();
    v1->setName("v1");
    v1->setUnits("dimensionless");

    libcellml::VariablePtr v2 = libcellml::Variable::create();
    v2->setName("v2");
    v2->setUnits("dimensionless");

    c1->addVariable(v1);
    c2->addVariable(v2);

    libcellml::Variable::addEquivalence(v1, v2);

    v1->setInterfaceType(libcellml::Variable::InterfaceType::PUBLIC);
    v2->setInterfaceType(libcellml::Variable::InterfaceType::PUBLIC);

    validator->validateModel(model);

    EXPECT_EQ_ISSUES(expectedIssues, validator);
}

TEST(Validator, variableInterfaceCouldBePrivateButSetToPublicAndPrivate)
{
    libcellml::ModelPtr model = libcellml::Model::create();
    libcellml::ComponentPtr c1 = libcellml::Component::create();
    libcellml::ComponentPtr c2 = libcellml::Component::create();

    libcellml::ValidatorPtr validator = libcellml::Validator::create();

    model->setName("model");
    c1->setName("c1");
    c2->setName("c2");

    model->addComponent(c1);
    c1->addComponent(c2);

    libcellml::VariablePtr v1 = libcellml::Variable::create();
    v1->setName("v1");
    v1->setUnits("dimensionless");

    libcellml::VariablePtr v2 = libcellml::Variable::create();
    v2->setName("v2");
    v2->setUnits("dimensionless");

    c1->addVariable(v1);
    c2->addVariable(v2);

    libcellml::Variable::addEquivalence(v1, v2);

    v1->setInterfaceType(libcellml::Variable::InterfaceType::PUBLIC_AND_PRIVATE);
    v2->setInterfaceType(libcellml::Variable::InterfaceType::PUBLIC_AND_PRIVATE);

    validator->validateModel(model);

    EXPECT_EQ(size_t(0), validator->issueCount());
}

TEST(Validator, variableInterfaceShouldBePublicAndPrivate)
{
    const std::vector<std::string> expectedIssues = {
        "Variable 'v2' in component 'c2' has an interface type set to 'private' which is not the correct interface type for this variable. The interface type required is 'public_and_private'.",
    };

    libcellml::ModelPtr model = libcellml::Model::create();
    libcellml::ComponentPtr c1 = libcellml::Component::create();
    libcellml::ComponentPtr c2 = libcellml::Component::create();
    libcellml::ComponentPtr c3 = libcellml::Component::create();

    libcellml::ValidatorPtr validator = libcellml::Validator::create();

    model->setName("model");
    c1->setName("c1");
    c2->setName("c2");
    c3->setName("c3");

    model->addComponent(c1);
    c1->addComponent(c2);
    c2->addComponent(c3);

    libcellml::VariablePtr v1 = libcellml::Variable::create();
    v1->setName("v1");
    v1->setUnits("dimensionless");

    libcellml::VariablePtr v2 = libcellml::Variable::create();
    v2->setName("v2");
    v2->setUnits("dimensionless");

    libcellml::VariablePtr v3 = libcellml::Variable::create();
    v3->setName("v3");
    v3->setUnits("dimensionless");

    c1->addVariable(v1);
    c2->addVariable(v2);
    c3->addVariable(v3);

    libcellml::Variable::addEquivalence(v1, v2);
    libcellml::Variable::addEquivalence(v2, v3);

    model->fixVariableInterfaces();

    v2->setInterfaceType(libcellml::Variable::InterfaceType::PRIVATE);

    validator->validateModel(model);

    EXPECT_EQ_ISSUES(expectedIssues, validator);
}

TEST(Validator, refToUnitsByNameNeedsLinkUnitsToValidate)
{
    auto parser = libcellml::Parser::create();
    auto validator = libcellml::Validator::create();

    std::string in = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>"
                     "<model xmlns=\"http://www.cellml.org/cellml/2.0#\" name=\"error_in_units\">"
                     "  <units name=\"millisecond\">"
                     "    <unit prefix=\"milli\" units=\"second\"/>"
                     "  </units>"
                     "  <component name=\"IonChannel\">"
                     "    <variable name=\"t\" units=\"millisecond\"/>"
                     "  </component>"
                     "</model>";

    auto model = parser->parseModel(in);
    validator->validateModel(model);
    EXPECT_EQ(size_t(0), validator->issueCount());

    auto nGate = libcellml::Component::create("nGate");
    model->addComponent(nGate);

    // Adding the variable *before* its units are added results in unfound units in the validator
    auto t2 = libcellml::Variable::create("t2");
    nGate->addVariable(t2);
    t2->setUnits("millisecond");

    validator->validateModel(model);
    EXPECT_EQ(size_t(1), validator->errorCount());

    // Linking the units to the model fixes the problem
    model->linkUnits();
    validator->validateModel(model);
    EXPECT_EQ(size_t(0), validator->errorCount());
}

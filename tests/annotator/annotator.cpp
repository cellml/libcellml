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

#include <any>
#include <libcellml>
#include <map>
#include <sstream>

#include "test_utils.h"

using AnyItem = std::pair<std::string, std::any>;

TEST(Annotator, getEntityFromId)
{
    auto model = libcellml::Model::create("model");
    auto component = libcellml::Component::create("component");
    auto variable = libcellml::Variable::create("variable");
    auto reset = libcellml::Reset::create();
    auto units = libcellml::Units::create("units");
    auto importSource = libcellml::ImportSource::create();

    auto annotator = libcellml::Annotator::create();

    model->setId("model_id");
    component->setId("component_id");
    reset->setId("reset_id");
    variable->setId("variable_id");
    units->setId("units_id");
    importSource->setId("import_id");

    component->addVariable(variable);
    component->addReset(reset);
    component->setImportSource(importSource);
    model->addComponent(component);
    model->addUnits(units);

    annotator->build(model);

    EXPECT_EQ(libcellml::Annotator::Type::MODEL, annotator->item("model_id").first);
    EXPECT_EQ(model, std::any_cast<libcellml::ModelPtr>(annotator->item("model_id").second));
    EXPECT_EQ(libcellml::Annotator::Type::COMPONENT, annotator->item("component_id").first);
    EXPECT_EQ(component, std::any_cast<libcellml::ComponentPtr>(annotator->item("component_id").second));
    EXPECT_EQ(libcellml::Annotator::Type::VARIABLE, annotator->item("variable_id").first);
    EXPECT_EQ(variable, std::any_cast<libcellml::VariablePtr>(annotator->item("variable_id").second));
    EXPECT_EQ(libcellml::Annotator::Type::RESET, annotator->item("reset_id").first);
    EXPECT_EQ(reset, std::any_cast<libcellml::ResetPtr>(annotator->item("reset_id").second));
    EXPECT_EQ(libcellml::Annotator::Type::UNITS, annotator->item("units_id").first);
    EXPECT_EQ(units, std::any_cast<libcellml::UnitsPtr>(annotator->item("units_id").second));
    EXPECT_EQ(libcellml::Annotator::Type::IMPORT, annotator->item("import_id").first);
    EXPECT_EQ(importSource, std::any_cast<libcellml::ImportSourcePtr>(annotator->item("import_id").second));
}

TEST(Annotator, getNonEntityFromId)
{
    auto model = createModelTwoComponentsWithOneVariableEach("model", "c1", "c2", "v1", "v2");
    auto annotator = libcellml::Annotator::create();

    // Unit items.
    auto units = libcellml::Units::create("units");
    units->addUnit("metre", 1.0, "unit1_id");
    units->addUnit("second", 1.0, "unit2_id");
    units->addUnit("newton", 1.0, "unit3_id");
    model->addUnits(units);

    // Encapsulation structure.
    auto c1 = model->component("c1");
    auto c2 = model->component("c2");
    auto v3 = libcellml::Variable::create("v3");
    auto v4 = libcellml::Variable::create("v4");
    c1->addVariable(v3);
    c2->addVariable(v4);
    auto v1v2 = std::make_pair(c1->variable("v1"), c2->variable("v2"));
    auto v3v4 = std::make_pair(c1->variable("v3"), c2->variable("v4"));

    c1->addComponent(c2);
    model->setEncapsulationId("encapsulation_id");
    c1->setEncapsulationId("component_ref1_id");
    c2->setEncapsulationId("component_ref2_id");

    // Connections and mappings.
    c1->variable("v1")->setInterfaceType("public_and_private");
    c2->variable("v2")->setInterfaceType("public_and_private");
    c1->variable("v3")->setInterfaceType("public_and_private");
    c2->variable("v4")->setInterfaceType("public_and_private");
    libcellml::Variable::addEquivalence(c1->variable("v1"), c2->variable("v2"));
    libcellml::Variable::addEquivalence(c1->variable("v3"), c2->variable("v4"));
    libcellml::Variable::setEquivalenceMappingId(c1->variable("v1"), c2->variable("v2"), "map_id");
    libcellml::Variable::setEquivalenceConnectionId(c1->variable("v1"), c2->variable("v2"), "connection_id");

    // Reset children.
    auto reset = libcellml::Reset::create();
    reset->setResetValueId("reset_value_id");
    reset->setTestValueId("test_value_id");
    c1->addReset(reset);

    annotator->build(model);

    // Unit items are returned as name string and pair of UnitsPtr parent and index:
    EXPECT_EQ(libcellml::Annotator::Type::UNIT, annotator->item("unit1_id").first);
    EXPECT_EQ(units, std::any_cast<libcellml::UnitItem>(annotator->item("unit1_id").second).first);
    EXPECT_EQ(size_t(0), std::any_cast<libcellml::UnitItem>(annotator->item("unit1_id").second).second);
    EXPECT_EQ(libcellml::Annotator::Type::UNIT, annotator->item("unit2_id").first);
    EXPECT_EQ(units, std::any_cast<libcellml::UnitItem>(annotator->item("unit2_id").second).first);
    EXPECT_EQ(size_t(1), std::any_cast<libcellml::UnitItem>(annotator->item("unit2_id").second).second);
    EXPECT_EQ(libcellml::Annotator::Type::UNIT, annotator->item("unit3_id").first);
    EXPECT_EQ(units, std::any_cast<libcellml::UnitItem>(annotator->item("unit3_id").second).first);
    EXPECT_EQ(size_t(2), std::any_cast<libcellml::UnitItem>(annotator->item("unit3_id").second).second);

    // Connections and map variables are returned as VariablePairs.  Note that connection ids could be
    // represented by any one of the pairs of variables in that connection.
    EXPECT_EQ(libcellml::Annotator::Type::MAP_VARIABLES, annotator->item("map_id").first);
    EXPECT_EQ(v1v2, std::any_cast<libcellml::VariablePair>(annotator->item("map_id").second));
    EXPECT_EQ(libcellml::Annotator::Type::CONNECTION, annotator->item("connection_id").first);
    EXPECT_TRUE((v1v2 == std::any_cast<libcellml::VariablePair>(annotator->item("connection_id").second) || (v3v4 == std::any_cast<libcellml::VariablePair>(annotator->item("connection_id").second))));

    // Component refs are returned as name string and ComponentPtr:
    EXPECT_EQ(libcellml::Annotator::Type::COMPONENT_REF, annotator->item("component_ref1_id").first);
    EXPECT_EQ(c1, std::any_cast<libcellml::ComponentPtr>(annotator->item("component_ref1_id").second));

    // Encapsulation is returned as name string and empty string:
    EXPECT_EQ(libcellml::Annotator::Type::ENCAPSULATION, annotator->item("encapsulation_id").first);
    EXPECT_EQ("", std::any_cast<std::string>(annotator->item("encapsulation_id").second));

    // Reset children are returned as name string and reset pointer:
    EXPECT_EQ(libcellml::Annotator::Type::RESET_VALUE, annotator->item("reset_value_id").first);
    EXPECT_EQ(reset, std::any_cast<libcellml::ResetPtr>(annotator->item("reset_value_id").second));
    EXPECT_EQ(libcellml::Annotator::Type::TEST_VALUE, annotator->item("test_value_id").first);
    EXPECT_EQ(reset, std::any_cast<libcellml::ResetPtr>(annotator->item("test_value_id").second));
}

TEST(Annotator, errorHandling)
{
    auto model = libcellml::Model::create("model");

    auto annotator = libcellml::Annotator::create();

    // Searching before the map is built should return an error.
    EXPECT_EQ(libcellml::Annotator::Type::ISSUE, annotator->item("i_dont_exist").first);
    EXPECT_EQ(size_t(1), annotator->issueCount());
    EXPECT_EQ(annotator->issue(0)->description(), "Please call the Annotator::build function before attempting to access items by their id.");

    // Building an empty model will result in an empty map and return an error.
    annotator->build(model);
    EXPECT_EQ(libcellml::Annotator::Type::ISSUE, annotator->item("i_dont_exist").first);
    EXPECT_EQ(size_t(1), annotator->issueCount());
    EXPECT_EQ(annotator->issue(0)->description(), "The id map is empty; the supplied model has no id attributes.");

    model->setId("model_id"); // Add an id into the model and rebuild.
    annotator->build(model);

    // Test that an Issue is created and logged when an id is not found:
    EXPECT_EQ(libcellml::Annotator::Type::ISSUE, annotator->item("i_dont_exist").first);
    EXPECT_EQ(size_t(1), annotator->issueCount());
    EXPECT_EQ(annotator->issue(0), std::any_cast<libcellml::IssuePtr>(annotator->item("i_dont_exist").second));

    // Test that repeated calls to the same unfound id do not generate new errors:
    EXPECT_EQ(libcellml::Annotator::Type::ISSUE, annotator->item("i_dont_exist").first);
    EXPECT_EQ(size_t(1), annotator->issueCount());
    EXPECT_EQ(annotator->issue(0), std::any_cast<libcellml::IssuePtr>(annotator->item("i_dont_exist").second));

    // Test bad casting handling:
    try {
        auto m = std::any_cast<libcellml::ComponentPtr>(annotator->item("model_id"));
    } catch (const std::bad_any_cast &e) {
        std::stringstream s;
        s << e.what();
        // MacOS, Windows, Ubuntu cast messages differ:
        EXPECT_TRUE(("bad any cast" == s.str()) || ("Bad any_cast" == s.str()) || ("bad any_cast" == s.str()));
    }
}

TEST(Annotator, getItemByIdSpecific)
{
    std::string in = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
                     "<model xmlns=\"http://www.cellml.org/cellml/2.0#\" name=\"everything\" id=\"model_1\">\n"
                     "  <import xmlns:xlink=\"http://www.w3.org/1999/xlink\" xlink:href=\"some-other-model.xml\" id=\"import_1\">\n"
                     "    <component component_ref=\"a_component_in_that_model\" name=\"component1\" id=\"component_1\"/>\n"
                     "  </import>\n"
                     "  <import xmlns:xlink=\"http://www.w3.org/1999/xlink\" xlink:href=\"some-other-model.xml\" id=\"import_2\">\n"
                     "    <units units_ref=\"a_units_in_that_model\" name=\"units1\" id=\"units_1\"/>\n"
                     "  </import>\n"
                     "  <units name=\"units2\" id=\"units_2\">\n"
                     "    <unit units=\"second\" id=\"unit_1\"/>\n"
                     "  </units>\n"
                     "  <units name=\"units3\" id=\"units_3\"/>\n"
                     "  <units name=\"blob\" id=\"units_4\"/>\n"
                     "  <component name=\"component2\" id=\"component_2\">\n"
                     "    <variable name=\"variable1\" units=\"units2\" interface=\"private\" id=\"variable_1\"/>\n"
                     "    <variable name=\"variable2\" units=\"units2\" id=\"variable_2\"/>\n"
                     "    <reset variable=\"variable1\" test_variable=\"variable2\" order=\"1\" id=\"reset_1\">\n"
                     "      <test_value id=\"test_value_1\">\n"
                     "        <math xmlns=\"http://www.w3.org/1998/Math/MathML\" xmlns:cellml=\"http://www.cellml.org/cellml/2.0#\" id=\"math_1\">\n"
                     "          <apply id=\"apply_1\">\n"
                     "            <eq id=\"eq_1\"/>\n"
                     "            <ci id=\"ci_1\">variable1</ci>\n"
                     "            <cn cellml:units=\"units2\" id=\"cn_1\">3.4</cn>\n"
                     "          </apply>\n"
                     "        </math>\n"
                     "      </test_value>\n"
                     "      <reset_value id=\"reset_value_1\">\n"
                     "        <math xmlns=\"http://www.w3.org/1998/Math/MathML\" xmlns:cellml=\"http://www.cellml.org/cellml/2.0#\" id=\"math_2\">\n"
                     "          <apply id=\"apply_2\">\n"
                     "            <eq id=\"eq_2\"/>\n"
                     "            <ci id=\"ci_2\">variable1</ci>\n"
                     "            <cn cellml:units=\"units2\" id=\"cn_2\">9.0</cn>\n"
                     "          </apply>\n"
                     "        </math>\n"
                     "      </reset_value>\n"
                     "    </reset>\n"
                     "  </component>\n"
                     "  <component name=\"component3\" id=\"component_3\">\n"
                     "    <variable name=\"variable4\" units=\"units2\" interface=\"public\" id=\"variable_3\"/>\n"
                     "    <variable name=\"variable2\" units=\"units2\" interface=\"public\" id=\"variable_4\"/>\n"
                     "    <math xmlns=\"http://www.w3.org/1998/Math/MathML\" xmlns:cellml=\"http://www.cellml.org/cellml/2.0#\" id=\"math_3\">\n"
                     "      <apply id=\"apply_3\">\n"
                     "        <eq id=\"eq_3\"/>\n"
                     "        <ci id=\"ci_3\">variable4</ci>\n"
                     "        <cn cellml:units=\"units2\" id=\"cn_3\">9.0</cn>\n"
                     "      </apply>\n"
                     "    </math>\n"
                     "  </component>\n"
                     "  <connection component_1=\"component2\" component_2=\"component3\" id=\"connection_1\">\n"
                     "    <map_variables variable_1=\"variable1\" variable_2=\"variable2\" id=\"map_variables_1\"/>\n"
                     "    <map_variables variable_1=\"variable1\" variable_2=\"variable4\" id=\"map_variables_2\"/>\n"
                     "  </connection>\n"
                     "  <encapsulation id=\"encapsulation_1\">\n"
                     "    <component_ref component=\"component2\" id=\"component_ref_1\">\n"
                     "      <component_ref component=\"component3\" id=\"component_ref_2\"/>\n"
                     "    </component_ref>\n"
                     "  </encapsulation>\n"
                     "</model>\n";

    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(in);
    auto annotator = libcellml::Annotator::create();
    auto v1v2 = std::make_pair(model->component("component2")->variable("variable1"), model->component("component2")->component("component3")->variable("variable2"));
    auto v1v4 = std::make_pair(model->component("component2")->variable("variable1"), model->component("component2")->component("component3")->variable("variable4"));

    annotator->build(model);

    EXPECT_EQ(model, annotator->model("model_1"));
    EXPECT_EQ(model->component("component1"), annotator->component("component_1"));
    EXPECT_EQ(model->component("component2"), annotator->component("component_2"));
    EXPECT_EQ(model->component("component2"), annotator->component("component_ref_1"));
    EXPECT_EQ(model->component("component2")->component("component3"), annotator->component("component_3"));
    EXPECT_EQ(model->component("component2")->component("component3"), annotator->componentRef("component_ref_2"));
    EXPECT_EQ(model->component("component1")->importSource(), annotator->importSource("import_1"));
    EXPECT_EQ(model->units("units1"), annotator->units("units_1"));
    EXPECT_EQ(model->units("units1")->importSource(), annotator->importSource("import_2"));
    EXPECT_EQ(model->units("units2"), annotator->units("units_2"));
    EXPECT_EQ(model->units("units2"), annotator->unit("unit_1").first);
    EXPECT_EQ(size_t(0), annotator->unit("unit_1").second);
    EXPECT_EQ(model->component("component2")->variable("variable1"), annotator->variable("variable_1"));
    EXPECT_EQ(model->component("component2")->variable("variable2"), annotator->variable("variable_2"));
    EXPECT_EQ(model->component("component2")->reset(0), annotator->reset("reset_1"));
    EXPECT_EQ(model->component("component2")->reset(0), annotator->testValue("test_value_1"));
    EXPECT_EQ(model->component("component2")->reset(0), annotator->resetValue("reset_value_1"));
    EXPECT_EQ(model->component("component2")->component("component3")->variable("variable4"), annotator->variable("variable_3"));
    EXPECT_EQ(model->component("component2")->component("component3")->variable("variable2"), annotator->variable("variable_4"));
    EXPECT_EQ(v1v2, annotator->connection("connection_1"));
    EXPECT_EQ(v1v2, annotator->mapVariables("map_variables_1"));
    EXPECT_EQ(v1v4, annotator->mapVariables("map_variables_2"));

    EXPECT_EQ(nullptr, annotator->model("i_dont_exist"));
    EXPECT_EQ(nullptr, annotator->component("i_dont_exist"));
    EXPECT_EQ(nullptr, annotator->variable("i_dont_exist"));
    EXPECT_EQ(nullptr, annotator->units("i_dont_exist"));
    EXPECT_EQ(nullptr, annotator->unit("i_dont_exist").first);
    EXPECT_EQ(nullptr, annotator->reset("i_dont_exist"));
    EXPECT_EQ(nullptr, annotator->resetValue("i_dont_exist"));
    EXPECT_EQ(nullptr, annotator->testValue("i_dont_exist"));
    EXPECT_EQ(nullptr, annotator->componentRef("i_dont_exist"));
    EXPECT_EQ(nullptr, annotator->connection("i_dont_exist").first);
    EXPECT_EQ(nullptr, annotator->connection("i_dont_exist").second);
    EXPECT_EQ(nullptr, annotator->mapVariables("i_dont_exist").first);
    EXPECT_EQ(nullptr, annotator->mapVariables("i_dont_exist").second);
    EXPECT_EQ(nullptr, annotator->importSource("i_dont_exist"));
}

TEST(Annotator, castingOnRetrieval)
{
    auto model = libcellml::Model::create("model");
    auto component = libcellml::Component::create("component");
    auto variable = libcellml::Variable::create("variable");
    auto reset = libcellml::Reset::create();
    auto units = libcellml::Units::create("units");
    auto importSource = libcellml::ImportSource::create();

    model->setId("model_id");
    component->addVariable(variable);
    component->addReset(reset);
    component->setImportSource(importSource);
    model->addComponent(component);
    model->addUnits(units);

    auto annotator = libcellml::Annotator::create();
    annotator->build(model);

    libcellml::AnyItem itemInfo = annotator->item("model_id");

    // In order to be able to use the switch below, we have to manually
    // declare all possible return types ... :(
    libcellml::ModelPtr itemModel;
    libcellml::ComponentPtr itemComponent;
    libcellml::ResetPtr itemReset;
    libcellml::VariablePtr itemVariable;
    libcellml::VariablePair itemVariablePair;
    libcellml::UnitItem itemUnit;
    libcellml::UnitsPtr itemUnits;
    libcellml::ImportSourcePtr itemImportItem;
    std::string itemEncapsulation;

    switch (itemInfo.first) {
    case libcellml::Annotator::Type::COMPONENT:
    case libcellml::Annotator::Type::COMPONENT_REF:
        itemComponent = std::any_cast<libcellml::ComponentPtr>(itemInfo.second);
        break;
    case libcellml::Annotator::Type::CONNECTION:
    case libcellml::Annotator::Type::MAP_VARIABLES:
        itemVariablePair = std::any_cast<libcellml::VariablePair>(itemInfo.second);
        break;
    case libcellml::Annotator::Type::ENCAPSULATION:
        itemEncapsulation = "encapsulation";
        break;
    case libcellml::Annotator::Type::IMPORT:
        itemImportItem = std::any_cast<libcellml::ImportSourcePtr>(itemInfo.second);
        break;
    case libcellml::Annotator::Type::MODEL:
        itemModel = std::any_cast<libcellml::ModelPtr>(itemInfo.second);
        break;
    case libcellml::Annotator::Type::RESET:
    case libcellml::Annotator::Type::RESET_VALUE:
    case libcellml::Annotator::Type::TEST_VALUE:
        itemReset = std::any_cast<libcellml::ResetPtr>(itemInfo.second);
        break;
    case libcellml::Annotator::Type::UNIT:
        itemUnit = std::any_cast<libcellml::UnitItem>(itemInfo.second);
        break;
    case libcellml::Annotator::Type::UNITS:
        itemUnits = std::any_cast<libcellml::UnitsPtr>(itemInfo.second);
        break;
    case libcellml::Annotator::Type::VARIABLE:
        itemVariable = std::any_cast<libcellml::VariablePtr>(itemInfo.second);
        break;
    }
}

TEST(Annotator, getItemByIndexList)
{
    std::string in = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
                     "<model xmlns=\"http://www.cellml.org/cellml/2.0#\" name=\"everything\" id=\"model_1\">\n"
                     "  <import xmlns:xlink=\"http://www.w3.org/1999/xlink\" xlink:href=\"some-other-model.xml\" id=\"import_1\">\n"
                     "    <component component_ref=\"a_component_in_that_model\" name=\"component1\" id=\"component_1\"/>\n"
                     "  </import>\n"
                     "  <import xmlns:xlink=\"http://www.w3.org/1999/xlink\" xlink:href=\"some-other-model.xml\" id=\"import_2\">\n"
                     "    <units units_ref=\"a_units_in_that_model\" name=\"units1\" id=\"units_1\"/>\n"
                     "  </import>\n"
                     "  <units name=\"units2\" id=\"units_2\">\n"
                     "    <unit units=\"second\" id=\"unit_1\"/>\n"
                     "  </units>\n"
                     "  <units name=\"units3\" id=\"units_3\"/>\n"
                     "  <units name=\"blob\" id=\"units_4\"/>\n"
                     "  <component name=\"component2\" id=\"component_2\">\n"
                     "    <variable name=\"variable1\" units=\"units2\" interface=\"private\" id=\"variable_1\"/>\n"
                     "    <variable name=\"variable2\" units=\"units2\" id=\"variable_2\"/>\n"
                     "    <reset variable=\"variable1\" test_variable=\"variable2\" order=\"1\" id=\"reset_1\">\n"
                     "      <test_value id=\"test_value_1\">\n"
                     "        <math xmlns=\"http://www.w3.org/1998/Math/MathML\" xmlns:cellml=\"http://www.cellml.org/cellml/2.0#\" id=\"math_1\">\n"
                     "          <apply id=\"apply_1\">\n"
                     "            <eq id=\"eq_1\"/>\n"
                     "            <ci id=\"ci_1\">variable1</ci>\n"
                     "            <cn cellml:units=\"units2\" id=\"cn_1\">3.4</cn>\n"
                     "          </apply>\n"
                     "        </math>\n"
                     "      </test_value>\n"
                     "      <reset_value id=\"reset_value_1\">\n"
                     "        <math xmlns=\"http://www.w3.org/1998/Math/MathML\" xmlns:cellml=\"http://www.cellml.org/cellml/2.0#\" id=\"math_2\">\n"
                     "          <apply id=\"apply_2\">\n"
                     "            <eq id=\"eq_2\"/>\n"
                     "            <ci id=\"ci_2\">variable1</ci>\n"
                     "            <cn cellml:units=\"units2\" id=\"cn_2\">9.0</cn>\n"
                     "          </apply>\n"
                     "        </math>\n"
                     "      </reset_value>\n"
                     "    </reset>\n"
                     "    <reset variable=\"variable2\" test_variable=\"variable1\" order=\"1\" id=\"reset_2\">\n"
                     "      <test_value id=\"test_value_2\"/>\n"
                     "      <reset_value id=\"reset_value_2\"/>\n"
                     "    </reset>\n"
                     "  </component>\n"
                     "  <component name=\"component3\" id=\"component_3\">\n"
                     "    <variable name=\"variable3\" units=\"units2\" interface=\"public\" id=\"variable_3\"/>\n"
                     "    <variable name=\"variable4\" units=\"units2\" interface=\"public\" id=\"variable_4\"/>\n"
                     "    <math xmlns=\"http://www.w3.org/1998/Math/MathML\" xmlns:cellml=\"http://www.cellml.org/cellml/2.0#\" id=\"math_3\">\n"
                     "      <apply id=\"apply_3\">\n"
                     "        <eq id=\"eq_3\"/>\n"
                     "        <ci id=\"ci_3\">variable4</ci>\n"
                     "        <cn cellml:units=\"units2\" id=\"cn_3\">9.0</cn>\n"
                     "      </apply>\n"
                     "    </math>\n"
                     "  </component>\n"
                     "  <component name=\"component4\" id=\"component_4\"/>\n"
                     "  <connection component_1=\"component2\" component_2=\"component3\" id=\"connection_1\">\n"
                     "    <map_variables variable_1=\"variable1\" variable_2=\"variable3\" id=\"map_variables_1\"/>\n"
                     "    <map_variables variable_1=\"variable1\" variable_2=\"variable4\" id=\"map_variables_2\"/>\n"
                     "  </connection>\n"
                     "  <encapsulation id=\"encapsulation_1\">\n"
                     "    <component_ref component=\"component2\" id=\"component_ref_1\">\n"
                     "      <component_ref component=\"component3\" id=\"component_ref_2\"/>\n"
                     "      <component_ref component=\"component4\" id=\"component_ref_3\"/>\n"
                     "    </component_ref>\n"
                     "  </encapsulation>\n"
                     "</model>\n";
    std::vector<std::string> ids = {
        "model_1",
        "units_1",
        "units_2",
        "units_3",
        "units_4",
        "unit_1",
        "component_1",
        "component_2",
        "component_3",
        "variable_1",
        "variable_2",
        "variable_3",
        "variable_4",
        "reset_1",
        "reset_value_1",
        "test_value_1",
        "reset_2",
        "reset_value_2",
        "test_value_2",
        "component_ref_1",
        "component_ref_2",
        "component_ref_3",
        "encapsulation_1",
        "import_1",
        "import_2",
        "doesnt_exist_will_cause_an_issue",
        "doesnt_exist_will_cause_a_second_issue"};
    std::vector<std::vector<size_t>> expectedIndices = {
        {},
        {0},
        {1},
        {2},
        {3},
        {1, 0},
        {0},
        {1},
        {1, 0},
        {1, 0},
        {1, 1},
        {1, 0, 0},
        {1, 0, 1},
        {1, 0},
        {1, 0},
        {1, 0},
        {1, 1},
        {1, 1},
        {1, 1},
        {1},
        {1, 0},
        {1, 1},
        {},
        {},
        {},
        {0},
        {1}};

    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(in);
    auto annotator = libcellml::Annotator::create();

    annotator->build(model);

    // Have to test the mappings and connections separately because they are not definitive.
    // Map variables 1.
    auto indexList = annotator->indicesToItem("map_variables_1");
    std::vector<size_t> a = {0, 1, 0};
    std::vector<size_t> b = {1, 0, 0, 0};
    EXPECT_TRUE((a == indexList.second) || (b == indexList.second));

    // Map variables 2.
    indexList = annotator->indicesToItem("map_variables_2");
    std::vector<size_t> c = {1, 1, 0};
    std::vector<size_t> d = {1, 0, 1, 0};
    EXPECT_TRUE((c == indexList.second) || (d == indexList.second));

    // Parent connection could be either of them.
    indexList = annotator->indicesToItem("connection_1");
    EXPECT_TRUE((a == indexList.second) || (b == indexList.second) || (c == indexList.second) || (d == indexList.second));

    // Iterate through the other items' indices.
    size_t i = 0;
    for (const auto &id : ids) {
        indexList = annotator->indicesToItem(id);
        EXPECT_EQ(expectedIndices.at(i), indexList.second);
        i++;
    }
}

TEST(Annotator, getItemByInstructions)
{
    std::string in = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
                     "<model xmlns=\"http://www.cellml.org/cellml/2.0#\" name=\"everything\" id=\"model_1\">\n"
                     "  <import xmlns:xlink=\"http://www.w3.org/1999/xlink\" xlink:href=\"some-other-model.xml\" id=\"import_1\">\n"
                     "    <component component_ref=\"a_component_in_that_model\" name=\"component1\" id=\"component_1\"/>\n"
                     "  </import>\n"
                     "  <import xmlns:xlink=\"http://www.w3.org/1999/xlink\" xlink:href=\"some-other-model.xml\" id=\"import_2\">\n"
                     "    <units units_ref=\"a_units_in_that_model\" name=\"units1\" id=\"units_1\"/>\n"
                     "  </import>\n"
                     "  <units name=\"units2\" id=\"units_2\">\n"
                     "    <unit units=\"second\" id=\"unit_1\"/>\n"
                     "  </units>\n"
                     "  <units name=\"units3\" id=\"units_3\"/>\n"
                     "  <units name=\"blob\" id=\"units_4\"/>\n"
                     "  <component name=\"component2\" id=\"component_2\">\n"
                     "    <variable name=\"variable1\" units=\"units2\" interface=\"private\" id=\"variable_1\"/>\n"
                     "    <variable name=\"variable2\" units=\"units2\" id=\"variable_2\"/>\n"
                     "    <reset variable=\"variable1\" test_variable=\"variable2\" order=\"1\" id=\"reset_1\">\n"
                     "      <test_value id=\"test_value_1\">\n"
                     "        <math xmlns=\"http://www.w3.org/1998/Math/MathML\" xmlns:cellml=\"http://www.cellml.org/cellml/2.0#\" id=\"math_1\">\n"
                     "          <apply id=\"apply_1\">\n"
                     "            <eq id=\"eq_1\"/>\n"
                     "            <ci id=\"ci_1\">variable1</ci>\n"
                     "            <cn cellml:units=\"units2\" id=\"cn_1\">3.4</cn>\n"
                     "          </apply>\n"
                     "        </math>\n"
                     "      </test_value>\n"
                     "      <reset_value id=\"reset_value_1\">\n"
                     "        <math xmlns=\"http://www.w3.org/1998/Math/MathML\" xmlns:cellml=\"http://www.cellml.org/cellml/2.0#\" id=\"math_2\">\n"
                     "          <apply id=\"apply_2\">\n"
                     "            <eq id=\"eq_2\"/>\n"
                     "            <ci id=\"ci_2\">variable1</ci>\n"
                     "            <cn cellml:units=\"units2\" id=\"cn_2\">9.0</cn>\n"
                     "          </apply>\n"
                     "        </math>\n"
                     "      </reset_value>\n"
                     "    </reset>\n"
                     "  </component>\n"
                     "  <component name=\"component3\" id=\"component_3\">\n"
                     "    <variable name=\"variable3\" units=\"units2\" interface=\"public\" id=\"variable_3\"/>\n"
                     "    <variable name=\"variable4\" units=\"units2\" interface=\"public\" id=\"variable_4\"/>\n"
                     "    <math xmlns=\"http://www.w3.org/1998/Math/MathML\" xmlns:cellml=\"http://www.cellml.org/cellml/2.0#\" id=\"math_3\">\n"
                     "      <apply id=\"apply_3\">\n"
                     "        <eq id=\"eq_3\"/>\n"
                     "        <ci id=\"ci_3\">variable4</ci>\n"
                     "        <cn cellml:units=\"units2\" id=\"cn_3\">9.0</cn>\n"
                     "      </apply>\n"
                     "    </math>\n"
                     "  </component>\n"
                     "  <connection component_1=\"component2\" component_2=\"component3\" id=\"connection_1\">\n"
                     "    <map_variables variable_1=\"variable1\" variable_2=\"variable3\" id=\"map_variables_1\"/>\n"
                     "    <map_variables variable_1=\"variable2\" variable_2=\"variable4\" id=\"map_variables_2\"/>\n"
                     "  </connection>\n"
                     "  <encapsulation id=\"encapsulation_1\">\n"
                     "    <component_ref component=\"component2\" id=\"component_ref_1\">\n"
                     "      <component_ref component=\"component3\" id=\"component_ref_2\"/>\n"
                     "    </component_ref>\n"
                     "  </encapsulation>\n"
                     "</model>\n";
    std::vector<std::string> ids = {
        "model_1",
        "units_1",
        "units_2",
        "units_3",
        "units_4",
        "unit_1",
        "component_1",
        "component_2",
        "component_3",
        "variable_1",
        "variable_2",
        "variable_3",
        "variable_4",
        "reset_1",
        "reset_value_1",
        "test_value_1",
        "component_ref_1",
        "component_ref_2",
        "encapsulation_1",
        "import_1",
        "import_2",
        "doesnt_exist_will_cause_an_issue",
        "map_variables_1",
        "map_variables_2",
        "connection_1",
    };
    std::vector<std::string> expectedInstructions = {
        "Model",
        "Units: model->units(0)",
        "Units: model->units(1)",
        "Units: model->units(2)",
        "Units: model->units(3)",
        "Unit in Units: model->units(1)->unit(0)",
        "Component: model->component(0)",
        "Component: model->component(1)",
        "Component: model->component(1)->component(0)",
        "Variable: model->component(1)->variable(0)",
        "Variable: model->component(1)->variable(1)",
        "Variable: model->component(1)->component(0)->variable(0)",
        "Variable: model->component(1)->component(0)->variable(1)",
        "Reset: model->component(1)->reset(0)",
        "Reset value: model->component(1)->reset(0)->resetValue()",
        "Test value: model->component(1)->reset(0)->testValue()",
        "Component position in encapsulation hierarchy: model->component(1)",
        "Component position in encapsulation hierarchy: model->component(1)->component(0)",
        "Model encapsulation",
        "Can't deal with imports yet.",
        "Can't deal with imports yet.",
        "Could not find an item with id='doesnt_exist_will_cause_an_issue' in the model.",
        "Variable equivalence between: \n  model->component(1)->variable(0)\n  model->component(1)->component(0)->component(0)->variable(1)",
        "Variable equivalence between: \n  model->component(1)->variable(1)\n  model->component(1)->component(0)->component(1)->variable(1)",
        "Connection caused by the variable equivalence between: \n  model->component(1)->variable(0)\n  model->component(1)->component(0)->component(0)->variable(1)",
    };

    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(in);
    auto annotator = libcellml::Annotator::create();

    annotator->build(model);

    size_t i = 0;
    for (const auto &id : ids) {
        EXPECT_EQ(expectedInstructions.at(i), annotator->instructions(id));
        i++;
    }
}

// TEST(Annotator, getItemByNamedInstructions)
// {
//     std::string in = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
//                      "<model xmlns=\"http://www.cellml.org/cellml/2.0#\" name=\"everything\" id=\"model_1\">\n"
//                      "  <import xmlns:xlink=\"http://www.w3.org/1999/xlink\" xlink:href=\"some-other-model.xml\" id=\"import_1\">\n"
//                      "    <component component_ref=\"a_component_in_that_model\" name=\"component1\" id=\"component_1\"/>\n"
//                      "  </import>\n"
//                      "  <import xmlns:xlink=\"http://www.w3.org/1999/xlink\" xlink:href=\"some-other-model.xml\" id=\"import_2\">\n"
//                      "    <units units_ref=\"a_units_in_that_model\" name=\"units1\" id=\"units_1\"/>\n"
//                      "  </import>\n"
//                      "  <units name=\"units2\" id=\"units_2\">\n"
//                      "    <unit units=\"second\" id=\"unit_1\"/>\n"
//                      "  </units>\n"
//                      "  <units name=\"units3\" id=\"units_3\"/>\n"
//                      "  <units name=\"blob\" id=\"units_4\"/>\n"
//                      "  <component name=\"component2\" id=\"component_2\">\n"
//                      "    <variable name=\"variable1\" units=\"units2\" interface=\"private\" id=\"variable_1\"/>\n"
//                      "    <variable name=\"variable2\" units=\"units2\" id=\"variable_2\"/>\n"
//                      "    <reset variable=\"variable1\" test_variable=\"variable2\" order=\"1\" id=\"reset_1\">\n"
//                      "      <test_value id=\"test_value_1\">\n"
//                      "        <math xmlns=\"http://www.w3.org/1998/Math/MathML\" xmlns:cellml=\"http://www.cellml.org/cellml/2.0#\" id=\"math_1\">\n"
//                      "          <apply id=\"apply_1\">\n"
//                      "            <eq id=\"eq_1\"/>\n"
//                      "            <ci id=\"ci_1\">variable1</ci>\n"
//                      "            <cn cellml:units=\"units2\" id=\"cn_1\">3.4</cn>\n"
//                      "          </apply>\n"
//                      "        </math>\n"
//                      "      </test_value>\n"
//                      "      <reset_value id=\"reset_value_1\">\n"
//                      "        <math xmlns=\"http://www.w3.org/1998/Math/MathML\" xmlns:cellml=\"http://www.cellml.org/cellml/2.0#\" id=\"math_2\">\n"
//                      "          <apply id=\"apply_2\">\n"
//                      "            <eq id=\"eq_2\"/>\n"
//                      "            <ci id=\"ci_2\">variable1</ci>\n"
//                      "            <cn cellml:units=\"units2\" id=\"cn_2\">9.0</cn>\n"
//                      "          </apply>\n"
//                      "        </math>\n"
//                      "      </reset_value>\n"
//                      "    </reset>\n"
//                      "  </component>\n"
//                      "  <component name=\"component3\" id=\"component_3\">\n"
//                      "    <variable name=\"variable3\" units=\"units2\" interface=\"public\" id=\"variable_3\"/>\n"
//                      "    <variable name=\"variable4\" units=\"units2\" interface=\"public\" id=\"variable_4\"/>\n"
//                      "    <math xmlns=\"http://www.w3.org/1998/Math/MathML\" xmlns:cellml=\"http://www.cellml.org/cellml/2.0#\" id=\"math_3\">\n"
//                      "      <apply id=\"apply_3\">\n"
//                      "        <eq id=\"eq_3\"/>\n"
//                      "        <ci id=\"ci_3\">variable4</ci>\n"
//                      "        <cn cellml:units=\"units2\" id=\"cn_3\">9.0</cn>\n"
//                      "      </apply>\n"
//                      "    </math>\n"
//                      "  </component>\n"
//                      "  <connection component_1=\"component2\" component_2=\"component3\" id=\"connection_1\">\n"
//                      "    <map_variables variable_1=\"variable1\" variable_2=\"variable3\" id=\"map_variables_1\"/>\n"
//                      "    <map_variables variable_1=\"variable2\" variable_2=\"variable4\" id=\"map_variables_2\"/>\n"
//                      "  </connection>\n"
//                      "  <encapsulation id=\"encapsulation_1\">\n"
//                      "    <component_ref component=\"component2\" id=\"component_ref_1\">\n"
//                      "      <component_ref component=\"component3\" id=\"component_ref_2\"/>\n"
//                      "    </component_ref>\n"
//                      "  </encapsulation>\n"
//                      "</model>\n";
//     std::vector<std::string> ids = {
//         "model_1",
//         "units_1",
//         "units_2",
//         "units_3",
//         "units_4",
//         "unit_1",
//         "component_1",
//         "component_2",
//         "component_3",
//         "variable_1",
//         "variable_2",
//         "variable_3",
//         "variable_4",
//         "reset_1",
//         "reset_value_1",
//         "test_value_1",
//         "component_ref_1",
//         "component_ref_2",
//         "encapsulation_1",
//         "import_1",
//         "import_2",
//         "doesnt_exist_will_cause_an_issue",
//         "map_variables_1",
//         "map_variables_2",
//         "connection_1",
//     };
//     std::vector<std::string> expectedInstructions = {
//         "Model",
//         "Units: model->units(0)",
//         "Units: model->units(1)",
//         "Units: model->units(2)",
//         "Units: model->units(3)",
//         "Unit in Units: model->units(1)->unit(0)",
//         "Component: model->component(0)",
//         "Component: model->component(1)",
//         "Component: model->component(1)->component(0)",
//         "Variable: model->component(1)->variable(0)",
//         "Variable: model->component(1)->variable(1)",
//         "Variable: model->component(1)->component(0)->variable(0)",
//         "Variable: model->component(1)->component(0)->variable(1)",
//         "Reset: model->component(1)->reset(0)",
//         "Reset value: model->component(1)->reset(0)->resetValue()",
//         "Test value: model->component(1)->reset(0)->testValue()",
//         "Component position in encapsulation hierarchy: model->component(1)",
//         "Component position in encapsulation hierarchy: model->component(1)->component(0)",
//         "Model encapsulation",
//         "Can't deal with imports yet.",
//         "Can't deal with imports yet.",
//         "Could not find an item with id='doesnt_exist_will_cause_an_issue' in the model.",
//         "Variable equivalence between: \n  model->component(1)->variable(0)\n  model->component(1)->component(0)->component(0)->variable(1)",
//         "Variable equivalence between: \n  model->component(1)->variable(1)\n  model->component(1)->component(0)->component(1)->variable(1)",
//         "Connection caused by the variable equivalence between: \n  model->component(1)->variable(0)\n  model->component(1)->component(0)->component(0)->variable(1)",
//     };

//     auto parser = libcellml::Parser::create();
//     auto model = parser->parseModel(in);
//     auto annotator = libcellml::Annotator::create();

//     annotator->build(model);

//     size_t i = 0;
//     for (const auto &id : ids) {
//         EXPECT_EQ(expectedInstructions.at(i), annotator->instructions(id));
//         i++;
//     }
// }

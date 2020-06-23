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

#include "test_utils.h"

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

    EXPECT_EQ(model, annotator->model("model_id"));
    EXPECT_EQ(component, annotator->component("component_id"));
    EXPECT_EQ(reset, annotator->reset("reset_id"));
    EXPECT_EQ(variable, annotator->variable("variable_id"));
    EXPECT_EQ(units, annotator->units("units_id"));
    EXPECT_EQ(importSource, annotator->import("import_id"));
    EXPECT_EQ("issue", annotator->item("I_dont_exist").first);
}

TEST(Annotator, getNonEntityFromId)
{
    auto model = createModelTwoComponentsWithOneVariableEach("model", "c1", "c2", "v1", "v2");
    auto annotator = libcellml::Annotator::create();

    // Encapsulation structure.
    auto c1 = model->component("c1");
    auto c2 = model->component("c2");
    auto v1v2 = std::make_pair(c1->variable("v1"), c2->variable("v2"));

    c1->addComponent(c2);
    model->setEncapsulationId("encapsulation_id");
    c1->setEncapsulationId("component_ref1_id");
    c2->setEncapsulationId("component_ref2_id");

    // Connections and mappings.
    c1->variable("v1")->setInterfaceType("public_and_private");
    c2->variable("v2")->setInterfaceType("public_and_private");
    libcellml::Variable::addEquivalence(c1->variable("v1"), c2->variable("v2"));
    libcellml::Variable::setEquivalenceMappingId(c1->variable("v1"), c2->variable("v2"), "map_id");
    libcellml::Variable::setEquivalenceConnectionId(c1->variable("v1"), c2->variable("v2"), "connection_id");

    annotator->build(model);

    EXPECT_EQ(v1v2, annotator->map_variables("map_id"));
    EXPECT_EQ(v1v2, annotator->connection("connection_id"));
    EXPECT_EQ(c1, annotator->component_ref("component_ref1_id"));
}

TEST(Annotator, getEntityTypeFromId)
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

    EXPECT_EQ("model", annotator->item("model_id").first);
    EXPECT_EQ("component", annotator->item("component_id").first);
    EXPECT_EQ("reset", annotator->item("reset_id").first);
    EXPECT_EQ("variable", annotator->item("variable_id").first);
    EXPECT_EQ("units", annotator->item("units_id").first);
    EXPECT_EQ("import", annotator->item("import_id").first);
    EXPECT_EQ("issue", annotator->item("I_dont_exist").first);
}

TEST(Annotator, getItemsById)
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
    EXPECT_EQ(model->component("component2")->component("component3"), annotator->component_ref("component_ref_2"));
    EXPECT_EQ(model->component("component1")->importSource(), annotator->import("import_1"));
    EXPECT_EQ(model->units("units1"), annotator->units("units_1"));
    EXPECT_EQ(model->units("units1")->importSource(), annotator->import("import_2"));
    EXPECT_EQ(model->units("units2"), annotator->units("units_2"));
    EXPECT_EQ(model->units("units2"), annotator->unit("unit_1").first);
    EXPECT_EQ(size_t(0), annotator->unit("unit_1").second);
    EXPECT_EQ(model->component("component2")->variable("variable1"), annotator->variable("variable_1"));
    EXPECT_EQ(model->component("component2")->variable("variable2"), annotator->variable("variable_2"));
    EXPECT_EQ(model->component("component2")->reset(0), annotator->reset("reset_1"));
    EXPECT_EQ(model->component("component2")->reset(0)->testValue(), annotator->test_value("test_value_1"));
    EXPECT_EQ(model->component("component2")->reset(0)->resetValue(), annotator->reset_value("reset_value_1"));
    EXPECT_EQ(model->component("component2")->component("component3")->variable("variable4"), annotator->variable("variable_3"));
    EXPECT_EQ(model->component("component2")->component("component3")->variable("variable2"), annotator->variable("variable_4"));
    EXPECT_EQ(v1v2, annotator->connection("connection_1"));
    EXPECT_EQ(v1v2, annotator->map_variables("map_variables_1"));
    EXPECT_EQ(v1v4, annotator->map_variables("map_variables_2"));

    EXPECT_EQ(nullptr, annotator->model("i_dont_exist"));
    EXPECT_EQ(nullptr, annotator->component("i_dont_exist"));
    EXPECT_EQ(nullptr, annotator->variable("i_dont_exist"));
    EXPECT_EQ(nullptr, annotator->units("i_dont_exist"));
    EXPECT_EQ(nullptr, annotator->unit("i_dont_exist").first);
    EXPECT_EQ(nullptr, annotator->reset("i_dont_exist"));
    EXPECT_EQ("", annotator->math("i_dont_exist"));
    EXPECT_EQ("", annotator->reset_value("i_dont_exist"));
    EXPECT_EQ("", annotator->test_value("i_dont_exist"));
    EXPECT_EQ(nullptr, annotator->component_ref("i_dont_exist"));
    EXPECT_EQ(nullptr, annotator->connection("i_dont_exist").first);
    EXPECT_EQ(nullptr, annotator->connection("i_dont_exist").second);
    EXPECT_EQ(nullptr, annotator->map_variables("i_dont_exist").first);
    EXPECT_EQ(nullptr, annotator->map_variables("i_dont_exist").second);
}

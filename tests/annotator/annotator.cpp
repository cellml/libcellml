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

const std::string modelStringDuplicateIds = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
                                            "<model xmlns=\"http://www.cellml.org/cellml/2.0#\" name=\"everything\" id=\"duplicateId\" >\n"
                                            "  <import xmlns:xlink=\"http://www.w3.org/1999/xlink\" xlink:href=\"some-other-model.xml\" id=\"duplicateId\">\n"
                                            "    <component component_ref=\"a_component_in_that_model\" name=\"component1\" id=\"duplicateId\"/>\n"
                                            "  </import>\n"
                                            "  <import xmlns:xlink=\"http://www.w3.org/1999/xlink\" xlink:href=\"some-other-model.xml\" id=\"duplicateId\" >\n"
                                            "    <units units_ref=\"a_units_in_that_model\" name=\"units1\" id=\"duplicateId\" />\n"
                                            "  </import>\n"
                                            "  <units name=\"units2\" id=\"duplicateId\">\n"
                                            "    <unit units=\"second\" id=\"duplicateId\"/>\n"
                                            "  </units>\n"
                                            "  <units name=\"units3\" id=\"duplicateId\"/>\n"
                                            "  <units name=\"blob\" id=\"duplicateId\"/>\n"
                                            "  <component name=\"component2\">\n"
                                            "    <variable name=\"variable1\" units=\"units2\" interface=\"private\" id=\"duplicateId\"/>\n"
                                            "    <variable name=\"variable2\" units=\"units2\" id=\"duplicateId\"/>\n"
                                            "    <reset variable=\"variable1\" test_variable=\"variable2\" order=\"1\" id=\"duplicateId\">\n"
                                            "      <test_value id=\"duplicateId\">\n"
                                            "        <math xmlns=\"http://www.w3.org/1998/Math/MathML\" xmlns:cellml=\"http://www.cellml.org/cellml/2.0#\">\n"
                                            "          <apply>\n"
                                            "            <eq/>\n"
                                            "            <ci>variable1</ci>\n"
                                            "            <cn cellml:units=\"units2\">3.4</cn>\n"
                                            "          </apply>\n"
                                            "        </math>\n"
                                            "      </test_value>\n"
                                            "      <reset_value id=\"duplicateId\">\n"
                                            "        <math xmlns=\"http://www.w3.org/1998/Math/MathML\" xmlns:cellml=\"http://www.cellml.org/cellml/2.0#\">\n"
                                            "          <apply>\n"
                                            "            <eq/>\n"
                                            "            <ci>variable1</ci>\n"
                                            "            <cn cellml:units=\"units2\">9.0</cn>\n"
                                            "          </apply>\n"
                                            "        </math>\n"
                                            "      </reset_value>\n"
                                            "    </reset>\n"
                                            "  </component>\n"
                                            "  <component name=\"component3\" id=\"duplicateId\">\n"
                                            "    <variable name=\"variable1\" units=\"units2\" interface=\"public\" id=\"duplicateId\" />\n"
                                            "    <variable name=\"variable2\" units=\"units2\" interface=\"public\" id=\"duplicateId\" />\n"
                                            "    <math xmlns=\"http://www.w3.org/1998/Math/MathML\" xmlns:cellml=\"http://www.cellml.org/cellml/2.0#\">\n"
                                            "      <apply>\n"
                                            "        <eq/>\n"
                                            "        <ci>variable4</ci>\n"
                                            "        <cn cellml:units=\"units2\">9.0</cn>\n"
                                            "      </apply>\n"
                                            "    </math>\n"
                                            "  </component>\n"
                                            "  <component name=\"component4\" id=\"duplicateId\">\n"
                                            "    <variable name=\"variable1\" units=\"units2\" interface=\"public\" id=\"duplicateId\" />\n"
                                            "    <variable name=\"variable2\" units=\"units2\" interface=\"public\" id=\"duplicateId\" />\n"
                                            "    <math xmlns=\"http://www.w3.org/1998/Math/MathML\" xmlns:cellml=\"http://www.cellml.org/cellml/2.0#\">\n"
                                            "      <apply>\n"
                                            "        <eq/>\n"
                                            "        <ci>variable4</ci>\n"
                                            "        <cn cellml:units=\"units2\">9.0</cn>\n"
                                            "      </apply>\n"
                                            "    </math>\n"
                                            "  </component>\n"
                                            "  <connection component_1=\"component2\" component_2=\"component3\" id=\"duplicateId\">\n"
                                            "    <map_variables variable_1=\"variable1\" variable_2=\"variable1\" id=\"duplicateId\"/>\n"
                                            "    <map_variables variable_1=\"variable2\" variable_2=\"variable2\" id=\"duplicateId\"/>\n"
                                            "  </connection>\n"
                                            "  <connection component_1=\"component2\" component_2=\"component4\" id=\"duplicateId\">\n"
                                            "    <map_variables variable_1=\"variable1\" variable_2=\"variable1\" id=\"duplicateId\"/>\n"
                                            "    <map_variables variable_1=\"variable2\" variable_2=\"variable2\" id=\"duplicateId\"/>\n"
                                            "  </connection>\n"
                                            "  <encapsulation id=\"duplicateId\">\n"
                                            "    <component_ref component=\"component2\" id=\"duplicateId\">\n"
                                            "      <component_ref component=\"component3\" id=\"duplicateId\"/>\n"
                                            "    </component_ref>\n"
                                            "  </encapsulation>\n"
                                            "</model>\n";

const std::string modelStringLotsOfDuplicateIds = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
                                                  "<model xmlns=\"http://www.cellml.org/cellml/2.0#\" name=\"everything\" id=\"duplicateId2\" >\n"
                                                  "  <import xmlns:xlink=\"http://www.w3.org/1999/xlink\" xlink:href=\"some-other-model.xml\" id=\"duplicateId1\">\n"
                                                  "    <component component_ref=\"a_component_in_that_model\" name=\"component1\" id=\"duplicateId4\"/>\n"
                                                  "  </import>\n"
                                                  "  <import xmlns:xlink=\"http://www.w3.org/1999/xlink\" xlink:href=\"some-other-model.xml\" id=\"duplicateId3\" >\n"
                                                  "    <units units_ref=\"a_units_in_that_model\" name=\"units1\" id=\"duplicateId2\" />\n"
                                                  "  </import>\n"
                                                  "  <units name=\"units2\" id=\"duplicateId1\">\n"
                                                  "    <unit units=\"second\" id=\"duplicateId4\"/>\n"
                                                  "  </units>\n"
                                                  "  <units name=\"units3\" id=\"duplicateId3\"/>\n"
                                                  "  <units name=\"blob\" id=\"duplicateId2\"/>\n"
                                                  "  <component name=\"component2\" id=\"duplicateId1\">\n"
                                                  "    <variable name=\"variable1\" units=\"units2\" interface=\"private\" id=\"duplicateId4\"/>\n"
                                                  "    <variable name=\"variable2\" units=\"units2\" id=\"duplicateId3\"/>\n"
                                                  "    <reset variable=\"variable1\" test_variable=\"variable2\" order=\"1\" id=\"duplicateId2\">\n"
                                                  "      <test_value id=\"duplicateId1\">\n"
                                                  "        <math xmlns=\"http://www.w3.org/1998/Math/MathML\" xmlns:cellml=\"http://www.cellml.org/cellml/2.0#\">\n"
                                                  "          <apply>\n"
                                                  "            <eq/>\n"
                                                  "            <ci>variable1</ci>\n"
                                                  "            <cn cellml:units=\"units2\">3.4</cn>\n"
                                                  "          </apply>\n"
                                                  "        </math>\n"
                                                  "      </test_value>\n"
                                                  "      <reset_value id=\"duplicateId4\">\n"
                                                  "        <math xmlns=\"http://www.w3.org/1998/Math/MathML\" xmlns:cellml=\"http://www.cellml.org/cellml/2.0#\">\n"
                                                  "          <apply>\n"
                                                  "            <eq/>\n"
                                                  "            <ci>variable1</ci>\n"
                                                  "            <cn cellml:units=\"units2\">9.0</cn>\n"
                                                  "          </apply>\n"
                                                  "        </math>\n"
                                                  "      </reset_value>\n"
                                                  "    </reset>\n"
                                                  "  </component>\n"
                                                  "  <component name=\"component3\" id=\"duplicateId3\">\n"
                                                  "    <variable name=\"variable1\" units=\"units2\" interface=\"public\" id=\"duplicateId2\" />\n"
                                                  "    <variable name=\"variable2\" units=\"units2\" interface=\"public\" id=\"duplicateId1\" />\n"
                                                  "    <math xmlns=\"http://www.w3.org/1998/Math/MathML\" xmlns:cellml=\"http://www.cellml.org/cellml/2.0#\">\n"
                                                  "      <apply>\n"
                                                  "        <eq/>\n"
                                                  "        <ci>variable4</ci>\n"
                                                  "        <cn cellml:units=\"units2\">9.0</cn>\n"
                                                  "      </apply>\n"
                                                  "    </math>\n"
                                                  "  </component>\n"
                                                  "  <component name=\"component4\" id=\"duplicateId4\">\n"
                                                  "    <variable name=\"variable1\" units=\"units2\" interface=\"public\" id=\"duplicateId3\" />\n"
                                                  "    <variable name=\"variable2\" units=\"units2\" interface=\"public\" id=\"duplicateId2\" />\n"
                                                  "    <math xmlns=\"http://www.w3.org/1998/Math/MathML\" xmlns:cellml=\"http://www.cellml.org/cellml/2.0#\">\n"
                                                  "      <apply>\n"
                                                  "        <eq/>\n"
                                                  "        <ci>variable4</ci>\n"
                                                  "        <cn cellml:units=\"units2\">9.0</cn>\n"
                                                  "      </apply>\n"
                                                  "    </math>\n"
                                                  "  </component>\n"
                                                  "  <connection component_1=\"component2\" component_2=\"component3\" id=\"duplicateId1\">\n"
                                                  "    <map_variables variable_1=\"variable1\" variable_2=\"variable1\" id=\"duplicateId4\"/>\n"
                                                  "    <map_variables variable_1=\"variable2\" variable_2=\"variable2\" id=\"duplicateId3\"/>\n"
                                                  "  </connection>\n"
                                                  "  <connection component_1=\"component2\" component_2=\"component4\" id=\"duplicateId2\">\n"
                                                  "    <map_variables variable_1=\"variable1\" variable_2=\"variable1\" id=\"duplicateId1\"/>\n"
                                                  "    <map_variables variable_1=\"variable2\" variable_2=\"variable2\" id=\"duplicateId4\"/>\n"
                                                  "  </connection>\n"
                                                  "  <encapsulation id=\"duplicateId3\">\n"
                                                  "    <component_ref component=\"component2\" id=\"duplicateId2\">\n"
                                                  "      <component_ref component=\"component3\" id=\"duplicateId1\"/>\n"
                                                  "    </component_ref>\n"
                                                  "  </encapsulation>\n"
                                                  "</model>\n";

const std::string modelStringNoIds = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
                                     "<model xmlns=\"http://www.cellml.org/cellml/2.0#\" name=\"everything\">\n"
                                     "  <import xmlns:xlink=\"http://www.w3.org/1999/xlink\" xlink:href=\"some-other-model.xml\">\n"
                                     "    <component component_ref=\"a_component_in_that_model\" name=\"component1\" />\n"
                                     "  </import>\n"
                                     "  <import xmlns:xlink=\"http://www.w3.org/1999/xlink\" xlink:href=\"some-other-model.xml\">\n"
                                     "    <units units_ref=\"a_units_in_that_model\" name=\"units1\"/>\n"
                                     "  </import>\n"
                                     "  <units name=\"units2\">\n"
                                     "    <unit units=\"second\"/>\n"
                                     "  </units>\n"
                                     "  <units name=\"units3\"/>\n"
                                     "  <units name=\"blob\"/>\n"
                                     "  <component name=\"component2\">\n"
                                     "    <variable name=\"variable1\" units=\"units2\" interface=\"private\"/>\n"
                                     "    <variable name=\"variable2\" units=\"units2\"/>\n"
                                     "    <reset variable=\"variable1\" test_variable=\"variable2\" order=\"1\">\n"
                                     "      <test_value>\n"
                                     "        <math xmlns=\"http://www.w3.org/1998/Math/MathML\" xmlns:cellml=\"http://www.cellml.org/cellml/2.0#\">\n"
                                     "          <apply>\n"
                                     "            <eq/>\n"
                                     "            <ci>variable1</ci>\n"
                                     "            <cn cellml:units=\"units2\">3.4</cn>\n"
                                     "          </apply>\n"
                                     "        </math>\n"
                                     "      </test_value>\n"
                                     "      <reset_value>\n"
                                     "        <math xmlns=\"http://www.w3.org/1998/Math/MathML\" xmlns:cellml=\"http://www.cellml.org/cellml/2.0#\">\n"
                                     "          <apply>\n"
                                     "            <eq/>\n"
                                     "            <ci>variable1</ci>\n"
                                     "            <cn cellml:units=\"units2\">9.0</cn>\n"
                                     "          </apply>\n"
                                     "        </math>\n"
                                     "      </reset_value>\n"
                                     "    </reset>\n"
                                     "  </component>\n"
                                     "  <component name=\"component3\">\n"
                                     "    <variable name=\"variable1\" units=\"units2\" interface=\"public\"/>\n"
                                     "    <variable name=\"variable2\" units=\"units2\" interface=\"public\"/>\n"
                                     "    <math xmlns=\"http://www.w3.org/1998/Math/MathML\" xmlns:cellml=\"http://www.cellml.org/cellml/2.0#\">\n"
                                     "      <apply>\n"
                                     "        <eq/>\n"
                                     "        <ci>variable4</ci>\n"
                                     "        <cn cellml:units=\"units2\">9.0</cn>\n"
                                     "      </apply>\n"
                                     "    </math>\n"
                                     "  </component>\n"
                                     "  <component name=\"component4\">\n"
                                     "    <variable name=\"variable1\" units=\"units2\" interface=\"public\"/>\n"
                                     "    <variable name=\"variable2\" units=\"units2\" interface=\"public\"/>\n"
                                     "    <math xmlns=\"http://www.w3.org/1998/Math/MathML\" xmlns:cellml=\"http://www.cellml.org/cellml/2.0#\">\n"
                                     "      <apply>\n"
                                     "        <eq/>\n"
                                     "        <ci>variable4</ci>\n"
                                     "        <cn cellml:units=\"units2\">9.0</cn>\n"
                                     "      </apply>\n"
                                     "    </math>\n"
                                     "  </component>\n"
                                     "  <connection component_1=\"component2\" component_2=\"component3\">\n"
                                     "    <map_variables variable_1=\"variable1\" variable_2=\"variable1\"/>\n"
                                     "    <map_variables variable_1=\"variable2\" variable_2=\"variable2\"/>\n"
                                     "  </connection>\n"
                                     "  <connection component_1=\"component2\" component_2=\"component4\">\n"
                                     "    <map_variables variable_1=\"variable1\" variable_2=\"variable1\"/>\n"
                                     "    <map_variables variable_1=\"variable2\" variable_2=\"variable2\"/>\n"
                                     "  </connection>\n"
                                     "  <encapsulation>\n"
                                     "    <component_ref component=\"component2\">\n"
                                     "      <component_ref component=\"component3\"/>\n"
                                     "    </component_ref>\n"
                                     "  </encapsulation>\n"
                                     "</model>\n";

const std::string modelStringUniqueIds = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
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
                                         "    <variable name=\"variable1\" units=\"units2\" interface=\"public\" id=\"variable_3\"/>\n"
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
                                         "    <map_variables variable_1=\"variable1\" variable_2=\"variable1\" id=\"map_variables_1\"/>\n"
                                         "    <map_variables variable_1=\"variable2\" variable_2=\"variable2\" id=\"map_variables_2\"/>\n"
                                         "  </connection>\n"
                                         "  <encapsulation id=\"encapsulation_1\">\n"
                                         "    <component_ref component=\"component2\" id=\"component_ref_1\">\n"
                                         "      <component_ref component=\"component3\" id=\"component_ref_2\"/>\n"
                                         "    </component_ref>\n"
                                         "  </encapsulation>\n"
                                         "</model>\n";

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

    annotator->buildModelIndex(model);

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

    annotator->buildModelIndex(model);

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

    // Encapsulation is returned as name string and ModelPtr :
    EXPECT_EQ(libcellml::Annotator::Type::ENCAPSULATION, annotator->item("encapsulation_id").first);
    EXPECT_EQ(model, std::any_cast<libcellml::ModelPtr>(annotator->item("encapsulation_id").second));

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
    EXPECT_EQ(size_t(2), annotator->issueCount());
    EXPECT_EQ(annotator->issue(0)->description(), "No model is stored; no action has been taken.");
    EXPECT_EQ(annotator->issue(1)->description(), "The model index is out-of-date.  Please (re)build it before attempting to access items by their id.");

    // Building an empty model will result in an empty map and return an error.
    annotator->buildModelIndex(model);
    EXPECT_EQ(libcellml::Annotator::Type::ISSUE, annotator->item("i_dont_exist").first);
    EXPECT_EQ(size_t(1), annotator->issueCount());
    EXPECT_EQ(annotator->issue(0)->description(), "Could not find an item with an id of 'i_dont_exist' in the model.");

    model->setId("model_id"); // Add an id into the model and rebuild.
    annotator->buildModelIndex(model);

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

TEST(Annotator, duplicateIdBehaviour)
{
    std::vector<std::string> expectedErrors = {
        "The id 'duplicateId' occurs 3 times in the model.",
        "The id 'duplicateId' occurs 3 times in the model so a unique item cannot be located."};
    auto model = libcellml::Model::create("model");
    auto annotator = libcellml::Annotator::create();
    auto component = libcellml::Component::create();
    auto variable = libcellml::Variable::create();

    model->setId("duplicateId");
    component->setId("duplicateId");
    variable->setId("duplicateId");

    component->addVariable(variable);
    model->addComponent(component);

    annotator->buildModelIndex(model);

    auto item = annotator->item("duplicateId");
    EXPECT_EQ(size_t(2), annotator->issueCount());
    EXPECT_EQ(expectedErrors[0], annotator->issue(0)->description());
    EXPECT_EQ(expectedErrors[1], annotator->issue(1)->description());
}

TEST(Annotator, getItemByIdSpecificType)
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

    annotator->buildModelIndex(model);

    EXPECT_EQ(model, annotator->model("model_1"));
    EXPECT_EQ(model, annotator->encapsulation("encapsulation_1"));
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
    EXPECT_EQ(nullptr, annotator->encapsulation("i_dont_exist"));
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

TEST(Annotator, getItemBySpecificTypeDuplicateId)
{
    auto parser = libcellml::Parser::create();
    auto annotator = libcellml::Annotator::create();
    auto model = parser->parseModel(modelStringDuplicateIds);

    EXPECT_EQ(nullptr, annotator->model("duplicateId"));
    EXPECT_EQ(nullptr, annotator->encapsulation("duplicateId"));
    EXPECT_EQ(nullptr, annotator->component("duplicateId"));
    EXPECT_EQ(nullptr, annotator->variable("duplicateId"));
    EXPECT_EQ(nullptr, annotator->units("duplicateId"));
    EXPECT_EQ(nullptr, annotator->unit("duplicateId").first);
    EXPECT_EQ(nullptr, annotator->reset("duplicateId"));
    EXPECT_EQ(nullptr, annotator->resetValue("duplicateId"));
    EXPECT_EQ(nullptr, annotator->testValue("duplicateId"));
    EXPECT_EQ(nullptr, annotator->componentRef("duplicateId"));
    EXPECT_EQ(nullptr, annotator->connection("duplicateId").first);
    EXPECT_EQ(nullptr, annotator->connection("duplicateId").second);
    EXPECT_EQ(nullptr, annotator->mapVariables("duplicateId").first);
    EXPECT_EQ(nullptr, annotator->mapVariables("duplicateId").second);
    EXPECT_EQ(nullptr, annotator->importSource("duplicateId"));

    // Expect errors because the annotator library hasn't been built and no model exists.
    EXPECT_EQ(size_t(30), annotator->errorCount());

    annotator->buildModelIndex(model);

    // Expect that the errors have been cleared.
    EXPECT_EQ(size_t(0), annotator->errorCount());

    EXPECT_EQ(nullptr, annotator->model("duplicateId"));
    EXPECT_EQ(nullptr, annotator->encapsulation("duplicateId"));
    EXPECT_EQ(nullptr, annotator->component("duplicateId"));
    EXPECT_EQ(nullptr, annotator->variable("duplicateId"));
    EXPECT_EQ(nullptr, annotator->units("duplicateId"));
    EXPECT_EQ(nullptr, annotator->unit("duplicateId").first);
    EXPECT_EQ(nullptr, annotator->reset("duplicateId"));
    EXPECT_EQ(nullptr, annotator->resetValue("duplicateId"));
    EXPECT_EQ(nullptr, annotator->testValue("duplicateId"));
    EXPECT_EQ(nullptr, annotator->componentRef("duplicateId"));
    EXPECT_EQ(nullptr, annotator->connection("duplicateId").first);
    EXPECT_EQ(nullptr, annotator->connection("duplicateId").second);
    EXPECT_EQ(nullptr, annotator->mapVariables("duplicateId").first);
    EXPECT_EQ(nullptr, annotator->mapVariables("duplicateId").second);
    EXPECT_EQ(nullptr, annotator->importSource("duplicateId"));
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
    annotator->buildModelIndex(model);

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

TEST(Annotator, automaticIdsOnEverything)
{
    auto expectedError = "No model is stored; no action has been taken.";
    auto annotator = libcellml::Annotator::create();
    auto parser = libcellml::Parser::create();
    auto printer = libcellml::Printer::create();
    auto model = parser->parseModel(modelStringNoIds);

    auto c2v1 = model->component("component2")->variable("variable1");
    auto c2v2 = model->component("component2")->variable("variable2");
    auto c3v1 = model->component("component3")->variable("variable1");
    auto c3v2 = model->component("component3")->variable("variable2");
    auto c4v1 = model->component("component4")->variable("variable1");
    auto c4v2 = model->component("component4")->variable("variable2");

    EXPECT_FALSE(annotator->assignAllIds());
    EXPECT_EQ(size_t(1), annotator->errorCount());
    EXPECT_EQ(expectedError, annotator->error(0)->description());

    annotator->buildModelIndex(model);
    EXPECT_TRUE(annotator->assignAllIds());

    EXPECT_EQ("b4da55", model->id());
    EXPECT_EQ("b4da56", model->importSource(0)->id());
    EXPECT_EQ("b4da57", model->importSource(1)->id());
    EXPECT_EQ("b4da58", model->units(0)->id());
    EXPECT_EQ("b4da59", model->units(1)->id());
    EXPECT_EQ("b4da5a", model->units(2)->id());
    EXPECT_EQ("b4da5b", model->units(3)->id());
    EXPECT_EQ("b4da5c", model->units(1)->unitId(0));

    EXPECT_EQ("b4da65", model->component("component2")->id());
    EXPECT_EQ("b4da66", model->component("component2")->component(0)->id());
    EXPECT_EQ("b4da67", model->component("component2")->variable(0)->id());
    EXPECT_EQ("b4da68", model->component("component2")->variable(1)->id());
    EXPECT_EQ("b4da69", model->component("component2")->component(0)->variable(0)->id());
    EXPECT_EQ("b4da6a", model->component("component2")->component(0)->variable(1)->id());
    EXPECT_EQ("b4da6b", model->component("component2")->reset(0)->id());
    EXPECT_EQ("b4da6c", model->component("component2")->reset(0)->resetValueId());
    EXPECT_EQ("b4da6d", model->component("component2")->reset(0)->testValueId());
    EXPECT_EQ("b4da6e", libcellml::Variable::equivalenceConnectionId(c2v1, c3v1));
    EXPECT_EQ("b4da61", libcellml::Variable::equivalenceConnectionId(c2v1, c4v1));
    EXPECT_EQ("b4da70", libcellml::Variable::equivalenceMappingId(c2v1, c3v1));
    EXPECT_EQ("b4da71", libcellml::Variable::equivalenceMappingId(c2v2, c3v2));
    EXPECT_EQ("b4da72", model->component("component2")->encapsulationId());
    EXPECT_EQ("b4da73", model->component("component3")->encapsulationId());
    EXPECT_EQ("b4da74", model->encapsulationId());
}

TEST(Annotator, automaticIdsComponents)
{
    auto annotator = libcellml::Annotator::create();
    auto model = libcellml::Model::create();
    auto component1 = libcellml::Component::create("c1");
    auto component2 = libcellml::Component::create("c2");
    auto component3 = libcellml::Component::create("c3");

    model->addComponent(component1);
    model->addComponent(component2);
    component2->addComponent(component3);

    annotator->buildModelIndex(model);

    EXPECT_EQ("", model->id());
    EXPECT_EQ("", component1->id());
    EXPECT_EQ("", component2->id());
    EXPECT_EQ("", component3->id());

    annotator->assignIds(libcellml::Annotator::Type::COMPONENT);

    EXPECT_TRUE(annotator->isBuilt());

    EXPECT_EQ("", model->id());
    EXPECT_EQ("b4da55", component1->id());
    EXPECT_EQ("b4da56", component2->id());
    EXPECT_EQ("b4da57", component3->id());
}

TEST(Annotator, automaticIdsComponentRefs)
{
    auto annotator = libcellml::Annotator::create();
    auto model = libcellml::Model::create();
    auto component1 = libcellml::Component::create("c1");
    auto component2 = libcellml::Component::create("c2");
    auto component3 = libcellml::Component::create("c3");

    model->addComponent(component1);
    model->addComponent(component2);
    component2->addComponent(component3);

    annotator->buildModelIndex(model);

    EXPECT_EQ("", model->id());
    EXPECT_EQ("", component1->id());
    EXPECT_EQ("", component2->id());
    EXPECT_EQ("", component3->id());
    EXPECT_EQ("", component1->encapsulationId());
    EXPECT_EQ("", component2->encapsulationId());
    EXPECT_EQ("", component3->encapsulationId());

    annotator->assignIds(libcellml::Annotator::Type::COMPONENT_REF);
    EXPECT_TRUE(annotator->isBuilt());

    EXPECT_EQ("", model->id());
    EXPECT_EQ("", component1->id());
    EXPECT_EQ("", component2->id());
    EXPECT_EQ("", component3->id());
    EXPECT_EQ("", component1->encapsulationId());
    EXPECT_EQ("b4da55", component2->encapsulationId());
    EXPECT_EQ("b4da56", component3->encapsulationId());
}

TEST(Annotator, automaticIdsConnection)
{
    auto annotator = libcellml::Annotator::create();
    auto model = libcellml::Model::create();
    auto component1 = libcellml::Component::create("c1");
    auto component2 = libcellml::Component::create("c2");
    auto variable1 = libcellml::Variable::create("v1");
    auto variable2 = libcellml::Variable::create("v2");
    auto variable3 = libcellml::Variable::create("v3");
    auto variable4 = libcellml::Variable::create("v4");
    component1->addVariable(variable1);
    component1->addVariable(variable2);
    component2->addVariable(variable3);
    component2->addVariable(variable4);

    model->addComponent(component1);
    model->addComponent(component2);

    libcellml::Variable::addEquivalence(variable1, variable3);
    libcellml::Variable::addEquivalence(variable2, variable4);

    annotator->buildModelIndex(model);

    EXPECT_EQ("", model->id());
    EXPECT_EQ("", component1->id());
    EXPECT_EQ("", component2->id());
    EXPECT_EQ("", variable1->id());
    EXPECT_EQ("", variable2->id());
    EXPECT_EQ("", variable3->id());
    EXPECT_EQ("", variable4->id());
    EXPECT_EQ("", libcellml::Variable::equivalenceConnectionId(variable1, variable3));
    EXPECT_EQ("", libcellml::Variable::equivalenceConnectionId(variable4, variable2));

    annotator->assignIds(libcellml::Annotator::Type::CONNECTION);
    EXPECT_TRUE(annotator->isBuilt());

    EXPECT_EQ("", model->id());
    EXPECT_EQ("", component1->id());
    EXPECT_EQ("", component2->id());
    EXPECT_EQ("", variable1->id());
    EXPECT_EQ("", variable2->id());
    EXPECT_EQ("", variable3->id());
    EXPECT_EQ("", variable4->id());
    EXPECT_EQ("b4da55", libcellml::Variable::equivalenceConnectionId(variable1, variable3));
    EXPECT_EQ("b4da56", libcellml::Variable::equivalenceConnectionId(variable2, variable4));
}

TEST(Annotator, automaticIdsEncapsulation)
{
    auto annotator = libcellml::Annotator::create();
    auto model = libcellml::Model::create();

    annotator->buildModelIndex(model);

    EXPECT_EQ("", model->encapsulationId());
    annotator->assignIds(libcellml::Annotator::Type::ENCAPSULATION);
    EXPECT_TRUE(annotator->isBuilt());

    EXPECT_EQ("b4da55", model->encapsulationId());
}

TEST(Annotator, automaticIdsImportSource)
{
    const std::string in = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
                           "<model xmlns=\"http://www.cellml.org/cellml/2.0#\" name=\"everything\">\n"
                           "  <import xmlns:xlink=\"http://www.w3.org/1999/xlink\" xlink:href=\"some-other-model.xml\">\n"
                           "    <component component_ref=\"a_component_in_that_model\" name=\"component1\" />\n"
                           "  </import>\n"
                           "  <import xmlns:xlink=\"http://www.w3.org/1999/xlink\" xlink:href=\"some-other-model.xml\">\n"
                           "    <units units_ref=\"a_units_in_that_model\" name=\"units1\"/>\n"
                           "  </import>\n"
                           "</model>";
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(in);
    auto annotator = libcellml::Annotator::create();

    annotator->buildModelIndex(model);

    EXPECT_EQ("", model->id());
    EXPECT_EQ("", model->importSource(0)->id());
    EXPECT_EQ("", model->importSource(1)->id());
    EXPECT_EQ("", model->units(0)->id());
    EXPECT_EQ("", model->component(0)->id());

    annotator->assignIds(libcellml::Annotator::Type::IMPORT);
    EXPECT_TRUE(annotator->isBuilt());

    EXPECT_EQ("", model->id());
    EXPECT_EQ("b4da55", model->importSource(0)->id());
    EXPECT_EQ("b4da56", model->importSource(1)->id());
    EXPECT_EQ("", model->units(0)->id());
    EXPECT_EQ("", model->component(0)->id());
}

TEST(Annotator, automaticIdsMapVariables)
{
    auto annotator = libcellml::Annotator::create();
    auto model = libcellml::Model::create();
    auto component1 = libcellml::Component::create("c1");
    auto component2 = libcellml::Component::create("c2");
    auto variable1 = libcellml::Variable::create("v1");
    auto variable2 = libcellml::Variable::create("v2");
    auto variable3 = libcellml::Variable::create("v3");
    auto variable4 = libcellml::Variable::create("v4");
    component1->addVariable(variable1);
    component1->addVariable(variable2);
    component2->addVariable(variable3);
    component2->addVariable(variable4);

    model->addComponent(component1);
    model->addComponent(component2);

    libcellml::Variable::addEquivalence(variable1, variable3);
    libcellml::Variable::addEquivalence(variable2, variable4);

    annotator->buildModelIndex(model);

    EXPECT_EQ("", model->id());
    EXPECT_EQ("", component1->id());
    EXPECT_EQ("", component2->id());
    EXPECT_EQ("", variable1->id());
    EXPECT_EQ("", variable2->id());
    EXPECT_EQ("", variable3->id());
    EXPECT_EQ("", variable4->id());
    EXPECT_EQ("", libcellml::Variable::equivalenceMappingId(variable1, variable3));
    EXPECT_EQ("", libcellml::Variable::equivalenceMappingId(variable2, variable4));

    annotator->assignIds(libcellml::Annotator::Type::MAP_VARIABLES);
    EXPECT_TRUE(annotator->isBuilt());

    EXPECT_EQ("", model->id());
    EXPECT_EQ("", component1->id());
    EXPECT_EQ("", component2->id());
    EXPECT_EQ("", variable1->id());
    EXPECT_EQ("", variable2->id());
    EXPECT_EQ("", variable3->id());
    EXPECT_EQ("", variable4->id());
    EXPECT_EQ("b4da55", libcellml::Variable::equivalenceMappingId(variable1, variable3));
    EXPECT_EQ("b4da56", libcellml::Variable::equivalenceMappingId(variable2, variable4));
}

TEST(Annotator, automaticIdsModel)
{
    auto annotator = libcellml::Annotator::create();
    auto model = libcellml::Model::create();

    annotator->buildModelIndex(model);

    EXPECT_EQ("", model->id());

    annotator->assignIds(libcellml::Annotator::Type::MODEL);
    EXPECT_TRUE(annotator->isBuilt());

    EXPECT_EQ("b4da55", model->id());
}

TEST(Annotator, automaticIdsResets)
{
    auto annotator = libcellml::Annotator::create();
    auto model = libcellml::Model::create();
    auto component1 = libcellml::Component::create("c1");
    auto component2 = libcellml::Component::create("c2");
    auto component3 = libcellml::Component::create("c3");
    auto reset1 = libcellml::Reset::create();
    auto reset2 = libcellml::Reset::create();
    auto reset3 = libcellml::Reset::create();

    component1->addReset(reset1);
    component2->addReset(reset2);
    component3->addReset(reset3);

    model->addComponent(component1);
    model->addComponent(component2);
    component2->addComponent(component3);

    annotator->buildModelIndex(model);

    EXPECT_EQ("", model->id());
    EXPECT_EQ("", component1->id());
    EXPECT_EQ("", component2->id());
    EXPECT_EQ("", component3->id());
    EXPECT_EQ("", reset1->id());
    EXPECT_EQ("", reset2->id());
    EXPECT_EQ("", reset3->id());

    annotator->assignIds(libcellml::Annotator::Type::RESET);
    EXPECT_TRUE(annotator->isBuilt());

    EXPECT_EQ("", model->id());
    EXPECT_EQ("", component1->id());
    EXPECT_EQ("", component2->id());
    EXPECT_EQ("", component3->id());
    EXPECT_EQ("b4da55", reset1->id());
    EXPECT_EQ("b4da56", reset2->id());
    EXPECT_EQ("b4da57", reset3->id());
}

TEST(Annotator, automaticIdsResetValues)
{
    auto annotator = libcellml::Annotator::create();
    auto model = libcellml::Model::create();
    auto component1 = libcellml::Component::create("c1");
    auto component2 = libcellml::Component::create("c2");
    auto component3 = libcellml::Component::create("c3");
    auto reset1 = libcellml::Reset::create();
    auto reset2 = libcellml::Reset::create();
    auto reset3 = libcellml::Reset::create();
    reset1->setResetValue(NON_EMPTY_MATH);
    reset2->setResetValue(NON_EMPTY_MATH);
    reset3->setResetValue(NON_EMPTY_MATH);

    component1->addReset(reset1);
    component2->addReset(reset2);
    component3->addReset(reset3);

    model->addComponent(component1);
    model->addComponent(component2);
    component2->addComponent(component3);

    annotator->buildModelIndex(model);

    EXPECT_EQ("", model->id());
    EXPECT_EQ("", component1->id());
    EXPECT_EQ("", component2->id());
    EXPECT_EQ("", component3->id());
    EXPECT_EQ("", reset1->id());
    EXPECT_EQ("", reset2->id());
    EXPECT_EQ("", reset3->id());
    EXPECT_EQ("", reset1->resetValueId());
    EXPECT_EQ("", reset2->resetValueId());
    EXPECT_EQ("", reset3->resetValueId());

    annotator->assignIds(libcellml::Annotator::Type::RESET_VALUE);
    EXPECT_TRUE(annotator->isBuilt());

    EXPECT_EQ("", model->id());
    EXPECT_EQ("", component1->id());
    EXPECT_EQ("", component2->id());
    EXPECT_EQ("", component3->id());
    EXPECT_EQ("", reset1->id());
    EXPECT_EQ("", reset2->id());
    EXPECT_EQ("", reset3->id());
    EXPECT_EQ("b4da55", reset1->resetValueId());
    EXPECT_EQ("b4da56", reset2->resetValueId());
    EXPECT_EQ("b4da57", reset3->resetValueId());
}

TEST(Annotator, automaticIdsTestValues)
{
    auto annotator = libcellml::Annotator::create();
    auto model = libcellml::Model::create();
    auto component1 = libcellml::Component::create("c1");
    auto component2 = libcellml::Component::create("c2");
    auto component3 = libcellml::Component::create("c3");
    auto reset1 = libcellml::Reset::create();
    auto reset2 = libcellml::Reset::create();
    auto reset3 = libcellml::Reset::create();
    reset1->setTestValue(NON_EMPTY_MATH);
    reset2->setTestValue(NON_EMPTY_MATH);
    reset3->setTestValue(NON_EMPTY_MATH);

    component1->addReset(reset1);
    component2->addReset(reset2);
    component3->addReset(reset3);

    model->addComponent(component1);
    model->addComponent(component2);
    component2->addComponent(component3);

    annotator->buildModelIndex(model);

    EXPECT_EQ("", model->id());
    EXPECT_EQ("", component1->id());
    EXPECT_EQ("", component2->id());
    EXPECT_EQ("", component3->id());
    EXPECT_EQ("", reset1->id());
    EXPECT_EQ("", reset2->id());
    EXPECT_EQ("", reset3->id());
    EXPECT_EQ("", reset1->testValueId());
    EXPECT_EQ("", reset2->testValueId());
    EXPECT_EQ("", reset3->testValueId());

    annotator->assignIds(libcellml::Annotator::Type::TEST_VALUE);
    EXPECT_TRUE(annotator->isBuilt());

    EXPECT_EQ("", model->id());
    EXPECT_EQ("", component1->id());
    EXPECT_EQ("", component2->id());
    EXPECT_EQ("", component3->id());
    EXPECT_EQ("", reset1->id());
    EXPECT_EQ("", reset2->id());
    EXPECT_EQ("", reset3->id());
    EXPECT_EQ("b4da55", reset1->testValueId());
    EXPECT_EQ("b4da56", reset2->testValueId());
    EXPECT_EQ("b4da57", reset3->testValueId());
}

TEST(Annotator, automaticIdsUnitItems)
{
    auto annotator = libcellml::Annotator::create();
    auto model = libcellml::Model::create();
    auto units = libcellml::Units::create();

    units->addUnit("second");
    units->addUnit("metre");

    model->addUnits(units);

    annotator->buildModelIndex(model);

    EXPECT_EQ("", model->id());
    EXPECT_EQ("", units->id());
    EXPECT_EQ("", units->unitId(0));
    EXPECT_EQ("", units->unitId(1));

    annotator->assignIds(libcellml::Annotator::Type::UNIT);
    EXPECT_TRUE(annotator->isBuilt());

    EXPECT_EQ("", model->id());
    EXPECT_EQ("", units->id());
    EXPECT_EQ("b4da55", units->unitId(0));
    EXPECT_EQ("b4da56", units->unitId(1));
}

TEST(Annotator, automaticIdsUnitsItems)
{
    auto annotator = libcellml::Annotator::create();
    auto model = libcellml::Model::create();
    auto units1 = libcellml::Units::create("u1");
    auto units2 = libcellml::Units::create("u2");

    units1->addUnit("second");
    units1->addUnit("metre");

    model->addUnits(units1);
    model->addUnits(units2);

    annotator->buildModelIndex(model);

    EXPECT_EQ("", model->id());
    EXPECT_EQ("", units1->id());
    EXPECT_EQ("", units1->unitId(0));
    EXPECT_EQ("", units1->unitId(1));
    EXPECT_EQ("", units1->id());

    annotator->assignIds(libcellml::Annotator::Type::UNITS);
    EXPECT_TRUE(annotator->isBuilt());

    EXPECT_EQ("", model->id());
    EXPECT_EQ("b4da55", units1->id());
    EXPECT_EQ("", units1->unitId(0));
    EXPECT_EQ("", units1->unitId(1));
    EXPECT_EQ("b4da56", units2->id());
}

TEST(Annotator, automaticIdsVariables)
{
    auto annotator = libcellml::Annotator::create();
    auto model = libcellml::Model::create();
    auto component1 = libcellml::Component::create("c1");
    auto component2 = libcellml::Component::create("c2");
    auto variable1 = libcellml::Variable::create("v1");
    auto variable2 = libcellml::Variable::create("v2");
    auto variable3 = libcellml::Variable::create("v3");
    auto variable4 = libcellml::Variable::create("v4");
    component1->addVariable(variable1);
    component1->addVariable(variable2);
    component2->addVariable(variable3);
    component2->addVariable(variable4);

    model->addComponent(component1);
    model->addComponent(component2);

    annotator->buildModelIndex(model);

    EXPECT_EQ("", model->id());
    EXPECT_EQ("", component1->id());
    EXPECT_EQ("", component2->id());
    EXPECT_EQ("", variable1->id());
    EXPECT_EQ("", variable2->id());
    EXPECT_EQ("", variable3->id());
    EXPECT_EQ("", variable4->id());

    annotator->assignIds(libcellml::Annotator::Type::VARIABLE);
    EXPECT_TRUE(annotator->isBuilt());

    EXPECT_EQ("", model->id());
    EXPECT_EQ("", component1->id());
    EXPECT_EQ("", component2->id());
    EXPECT_EQ("b4da55", variable1->id());
    EXPECT_EQ("b4da56", variable2->id());
    EXPECT_EQ("b4da57", variable3->id());
    EXPECT_EQ("b4da58", variable4->id());
}

TEST(Annotator, automaticIdsIssue)
{
    auto annotator = libcellml::Annotator::create();
    auto model = libcellml::Model::create();

    annotator->buildModelIndex(model);

    EXPECT_FALSE(annotator->assignIds(libcellml::Annotator::Type::ISSUE));
    EXPECT_TRUE(annotator->isBuilt());
}

TEST(Annotator, automaticIdAllItemsNoId)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(modelStringNoIds);
    auto annotator = libcellml::Annotator::create();
    libcellml::VariablePair p1 = std::make_pair(model->component("component2")->variable("variable1"), model->component("component2")->component("component3")->variable("variable1"));
    libcellml::VariablePair p2 = std::make_pair(model->component("component2")->variable("variable2"), model->component("component2")->component("component3")->variable("variable2"));

    libcellml::UnitItem unit = std::make_pair(model->units(1), 0);

    libcellml::AnyItem itemComponent = std::make_pair(libcellml::Annotator::Type::COMPONENT, model->component("component1"));
    libcellml::AnyItem itemComponentRef = std::make_pair(libcellml::Annotator::Type::COMPONENT_REF, model->component("component2"));
    libcellml::AnyItem itemConnection = std::make_pair(libcellml::Annotator::Type::CONNECTION, p1);
    libcellml::AnyItem itemEncapsulation = std::make_pair(libcellml::Annotator::Type::ENCAPSULATION, model);
    libcellml::AnyItem itemImportSource = std::make_pair(libcellml::Annotator::Type::IMPORT, model->importSource(0));
    libcellml::AnyItem itemMapVariables = std::make_pair(libcellml::Annotator::Type::MAP_VARIABLES, p2);
    libcellml::AnyItem itemModel = std::make_pair(libcellml::Annotator::Type::MODEL, model);
    libcellml::AnyItem itemReset = std::make_pair(libcellml::Annotator::Type::RESET, model->component("component2")->reset(0));
    libcellml::AnyItem itemResetValue = std::make_pair(libcellml::Annotator::Type::RESET_VALUE, model->component("component2")->reset(0));
    libcellml::AnyItem itemTestValue = std::make_pair(libcellml::Annotator::Type::TEST_VALUE, model->component("component2")->reset(0));
    libcellml::AnyItem itemUnit = std::make_pair(libcellml::Annotator::Type::UNIT, unit);
    libcellml::AnyItem itemUnits = std::make_pair(libcellml::Annotator::Type::UNITS, model->units(1));
    libcellml::AnyItem itemVariable = std::make_pair(libcellml::Annotator::Type::VARIABLE, model->component("component2")->variable(0));

    annotator->buildModelIndex(model);
    EXPECT_TRUE(annotator->isBuilt());

    // Expect each have had a change of id.
    EXPECT_EQ("b4da55", annotator->assignId(itemComponent));
    EXPECT_TRUE(annotator->isBuilt());
    EXPECT_EQ("b4da56", annotator->assignId(itemComponentRef));
    EXPECT_TRUE(annotator->isBuilt());
    EXPECT_EQ("b4da57", annotator->assignId(itemConnection));
    EXPECT_TRUE(annotator->isBuilt());
    EXPECT_EQ("b4da58", annotator->assignId(itemImportSource));
    EXPECT_TRUE(annotator->isBuilt());
    EXPECT_EQ("b4da59", annotator->assignId(itemMapVariables));
    EXPECT_TRUE(annotator->isBuilt());
    EXPECT_EQ("b4da5a", annotator->assignId(itemModel));
    EXPECT_TRUE(annotator->isBuilt());
    EXPECT_EQ("b4da5b", annotator->assignId(itemReset));
    EXPECT_TRUE(annotator->isBuilt());
    EXPECT_EQ("b4da5c", annotator->assignId(itemResetValue));
    EXPECT_TRUE(annotator->isBuilt());
    EXPECT_EQ("b4da5d", annotator->assignId(itemTestValue));
    EXPECT_TRUE(annotator->isBuilt());
    EXPECT_EQ("b4da5e", annotator->assignId(itemUnit));
    EXPECT_TRUE(annotator->isBuilt());
    EXPECT_EQ("b4da5f", annotator->assignId(itemUnits));
    EXPECT_TRUE(annotator->isBuilt());
    EXPECT_EQ("b4da60", annotator->assignId(itemVariable));
    EXPECT_TRUE(annotator->isBuilt());
    EXPECT_EQ("b4da61", annotator->assignId(itemEncapsulation));
    EXPECT_TRUE(annotator->isBuilt());

    EXPECT_EQ("b4da55", model->component(0)->id());
    EXPECT_EQ("b4da56", model->component("component2")->encapsulationId());
    EXPECT_EQ("b4da57", libcellml::Variable::equivalenceConnectionId(model->component("component2")->variable("variable1"), model->component("component2")->component("component3")->variable("variable1")));
    EXPECT_EQ("b4da58", model->importSource(0)->id());
    EXPECT_EQ("b4da59", libcellml::Variable::equivalenceMappingId(model->component("component2")->variable("variable2"), model->component("component2")->component("component3")->variable("variable2")));
    EXPECT_EQ("b4da5a", model->id());
    EXPECT_EQ("b4da5b", model->component("component2")->reset(0)->id());
    EXPECT_EQ("b4da5c", model->component("component2")->reset(0)->resetValueId());
    EXPECT_EQ("b4da5d", model->component("component2")->reset(0)->testValueId());
    EXPECT_EQ("b4da5e", model->units(1)->unitId(0));
    EXPECT_EQ("b4da5f", model->units(1)->id());
    EXPECT_EQ("b4da60", model->component("component2")->variable(0)->id());
    EXPECT_EQ("b4da61", model->encapsulationId());

    // Doing the extra set of connections and mappings.
    libcellml::VariablePair r1 = std::make_pair(model->component("component2")->variable("variable1"), model->component("component4")->variable("variable1"));
    libcellml::VariablePair r2 = std::make_pair(model->component("component2")->variable("variable2"), model->component("component4")->variable("variable2"));
    libcellml::AnyItem itemConnection2 = std::make_pair(libcellml::Annotator::Type::CONNECTION, r1);
    libcellml::AnyItem itemMapVariables2 = std::make_pair(libcellml::Annotator::Type::MAP_VARIABLES, r2);
    EXPECT_EQ("b4da62", annotator->assignId(itemConnection2));
    EXPECT_EQ("b4da63", annotator->assignId(itemMapVariables2));

    EXPECT_TRUE(annotator->isBuilt());
}

TEST(Annotator, automaticIdAllItemsAllDuplicated)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(modelStringDuplicateIds);
    auto annotator = libcellml::Annotator::create();

    libcellml::VariablePair connection = std::make_pair(
        model->component("component2")->variable("variable1"),
        model->component("component2")->variable("variable1")->equivalentVariable(0));
    libcellml::VariablePair mapping = std::make_pair(
        model->component("component2")->variable("variable2"),
        model->component("component2")->variable("variable2")->equivalentVariable(0));
    libcellml::UnitItem unit = std::make_pair(model->units(1), 0);

    libcellml::AnyItem itemComponent = std::make_pair(libcellml::Annotator::Type::COMPONENT, model->component(0));
    libcellml::AnyItem itemComponentRef = std::make_pair(libcellml::Annotator::Type::COMPONENT_REF, model->component("component2"));
    libcellml::AnyItem itemConnection = std::make_pair(libcellml::Annotator::Type::CONNECTION, connection);
    libcellml::AnyItem itemEncapsulation = std::make_pair(libcellml::Annotator::Type::ENCAPSULATION, model);
    libcellml::AnyItem itemImportSource = std::make_pair(libcellml::Annotator::Type::IMPORT, model->importSource(0));
    libcellml::AnyItem itemMapVariables = std::make_pair(libcellml::Annotator::Type::MAP_VARIABLES, mapping);
    libcellml::AnyItem itemModel = std::make_pair(libcellml::Annotator::Type::MODEL, model);
    libcellml::AnyItem itemReset = std::make_pair(libcellml::Annotator::Type::RESET, model->component("component2")->reset(0));
    libcellml::AnyItem itemResetValue = std::make_pair(libcellml::Annotator::Type::RESET_VALUE, model->component("component2")->reset(0));
    libcellml::AnyItem itemTestValue = std::make_pair(libcellml::Annotator::Type::TEST_VALUE, model->component("component2")->reset(0));
    libcellml::AnyItem itemUnit = std::make_pair(libcellml::Annotator::Type::UNIT, unit);
    libcellml::AnyItem itemUnits = std::make_pair(libcellml::Annotator::Type::UNITS, model->units(1));
    libcellml::AnyItem itemVariable = std::make_pair(libcellml::Annotator::Type::VARIABLE, model->component("component2")->variable(0));

    annotator->buildModelIndex(model);

    EXPECT_EQ(model, owningModel(std::any_cast<libcellml::ComponentPtr>(itemComponent.second)));
    EXPECT_EQ(model, owningModel(std::any_cast<libcellml::ComponentPtr>(itemComponentRef.second)));
    EXPECT_EQ(model, owningModel(std::any_cast<libcellml::VariablePair>(itemConnection.second).first));
    EXPECT_EQ(model, owningModel(std::any_cast<libcellml::ImportSourcePtr>(itemImportSource.second)));
    EXPECT_EQ(model, owningModel(std::any_cast<libcellml::VariablePair>(itemMapVariables.second).first));
    EXPECT_EQ(model, owningModel(std::any_cast<libcellml::ResetPtr>(itemReset.second)));
    EXPECT_EQ(model, owningModel(std::any_cast<libcellml::ResetPtr>(itemResetValue.second)));
    EXPECT_EQ(model, owningModel(std::any_cast<libcellml::ResetPtr>(itemTestValue.second)));
    EXPECT_EQ(model, owningModel(std::any_cast<libcellml::UnitItem>(itemUnit.second).first));
    EXPECT_EQ(model, owningModel(std::any_cast<libcellml::UnitsPtr>(itemUnits.second)));
    EXPECT_EQ(model, owningModel(std::any_cast<libcellml::VariablePtr>(itemVariable.second)));

    // Expect each have had a change of id.
    EXPECT_EQ("b4da55", annotator->assignId(itemComponent));
    EXPECT_EQ("b4da56", annotator->assignId(itemComponentRef));
    EXPECT_EQ("b4da57", annotator->assignId(itemConnection));
    EXPECT_EQ("b4da58", annotator->assignId(itemImportSource));
    EXPECT_EQ("b4da59", annotator->assignId(itemMapVariables));
    EXPECT_EQ("b4da5a", annotator->assignId(itemModel));
    EXPECT_EQ("b4da5b", annotator->assignId(itemReset));
    EXPECT_EQ("b4da5c", annotator->assignId(itemResetValue));
    EXPECT_EQ("b4da5d", annotator->assignId(itemTestValue));
    EXPECT_EQ("b4da5e", annotator->assignId(itemUnit));
    EXPECT_EQ("b4da5f", annotator->assignId(itemUnits));
    EXPECT_EQ("b4da60", annotator->assignId(itemVariable));
    EXPECT_EQ("b4da61", annotator->assignId(itemEncapsulation));

    EXPECT_EQ("b4da55", model->component(0)->id());
    EXPECT_EQ("b4da56", model->component("component2")->encapsulationId());
    EXPECT_EQ("b4da57", libcellml::Variable::equivalenceConnectionId(connection.first, connection.second));
    EXPECT_EQ("b4da58", model->importSource(0)->id());
    EXPECT_EQ("b4da59", libcellml::Variable::equivalenceMappingId(mapping.first, mapping.second));
    EXPECT_EQ("b4da5a", model->id());
    EXPECT_EQ("b4da5b", model->component("component2")->reset(0)->id());
    EXPECT_EQ("b4da5c", model->component("component2")->reset(0)->resetValueId());
    EXPECT_EQ("b4da5d", model->component("component2")->reset(0)->testValueId());
    EXPECT_EQ("b4da5e", model->units(1)->unitId(0));
    EXPECT_EQ("b4da5f", model->units(1)->id());
    EXPECT_EQ("b4da60", model->component("component2")->variable(0)->id());
    EXPECT_EQ("b4da61", model->encapsulationId());

    libcellml::VariablePair connection2 = std::make_pair(
        model->component("component2")->variable("variable1")->equivalentVariable(0),
        model->component("component2")->variable("variable1"));
    libcellml::VariablePair mapping2 = std::make_pair(
        model->component("component4")->variable("variable2")->equivalentVariable(0),
        model->component("component4")->variable("variable2"));

    libcellml::AnyItem itemConnection2 = std::make_pair(libcellml::Annotator::Type::CONNECTION, connection2);
    libcellml::AnyItem itemMapVariables2 = std::make_pair(libcellml::Annotator::Type::MAP_VARIABLES, mapping2);

    EXPECT_EQ("b4da62", annotator->assignId(itemConnection2));
    EXPECT_EQ("b4da62", libcellml::Variable::equivalenceConnectionId(connection2.first, connection2.second));

    EXPECT_EQ("b4da63", annotator->assignId(itemMapVariables2));
    EXPECT_EQ("b4da63", libcellml::Variable::equivalenceMappingId(mapping2.first, mapping2.second));
}

TEST(Annotator, automaticIdAllItemsNoneDuplicated)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(modelStringUniqueIds);
    auto annotator = libcellml::Annotator::create();

    libcellml::VariablePair connection = std::make_pair(
        model->component("component2")->variable(0),
        model->component("component2")->variable(0)->equivalentVariable(0));
    libcellml::VariablePair mapping = std::make_pair(
        model->component("component2")->variable(1),
        model->component("component2")->variable(1)->equivalentVariable(0));
    libcellml::UnitItem unit = std::make_pair(model->units(1), 0);

    libcellml::AnyItem itemComponent = std::make_pair(libcellml::Annotator::Type::COMPONENT, model->component(0));
    libcellml::AnyItem itemComponentRef = std::make_pair(libcellml::Annotator::Type::COMPONENT_REF, model->component("component2"));
    libcellml::AnyItem itemConnection = std::make_pair(libcellml::Annotator::Type::CONNECTION, connection);
    libcellml::AnyItem itemEncapsulation = std::make_pair(libcellml::Annotator::Type::ENCAPSULATION, model);
    libcellml::AnyItem itemImportSource = std::make_pair(libcellml::Annotator::Type::IMPORT, model->importSource(0));
    libcellml::AnyItem itemMapVariables = std::make_pair(libcellml::Annotator::Type::MAP_VARIABLES, mapping);
    libcellml::AnyItem itemModel = std::make_pair(libcellml::Annotator::Type::MODEL, model);
    libcellml::AnyItem itemReset = std::make_pair(libcellml::Annotator::Type::RESET, model->component("component2")->reset(0));
    libcellml::AnyItem itemResetValue = std::make_pair(libcellml::Annotator::Type::RESET_VALUE, model->component("component2")->reset(0));
    libcellml::AnyItem itemTestValue = std::make_pair(libcellml::Annotator::Type::TEST_VALUE, model->component("component2")->reset(0));
    libcellml::AnyItem itemUnit = std::make_pair(libcellml::Annotator::Type::UNIT, unit);
    libcellml::AnyItem itemUnits = std::make_pair(libcellml::Annotator::Type::UNITS, model->units(1));
    libcellml::AnyItem itemVariable = std::make_pair(libcellml::Annotator::Type::VARIABLE, model->component("component2")->variable(0));

    annotator->buildModelIndex(model);

    EXPECT_EQ(model, owningModel(std::any_cast<libcellml::ComponentPtr>(itemComponent.second)));
    EXPECT_EQ(model, owningModel(std::any_cast<libcellml::ComponentPtr>(itemComponentRef.second)));
    EXPECT_EQ(model, owningModel(std::any_cast<libcellml::VariablePair>(itemConnection.second).first));
    EXPECT_EQ(model, owningModel(std::any_cast<libcellml::ImportSourcePtr>(itemImportSource.second)));
    EXPECT_EQ(model, owningModel(std::any_cast<libcellml::VariablePair>(itemMapVariables.second).first));
    EXPECT_EQ(model, owningModel(std::any_cast<libcellml::ResetPtr>(itemReset.second)));
    EXPECT_EQ(model, owningModel(std::any_cast<libcellml::ResetPtr>(itemResetValue.second)));
    EXPECT_EQ(model, owningModel(std::any_cast<libcellml::ResetPtr>(itemTestValue.second)));
    EXPECT_EQ(model, owningModel(std::any_cast<libcellml::UnitItem>(itemUnit.second).first));
    EXPECT_EQ(model, owningModel(std::any_cast<libcellml::UnitsPtr>(itemUnits.second)));
    EXPECT_EQ(model, owningModel(std::any_cast<libcellml::VariablePtr>(itemVariable.second)));

    // Expect each to change, even though the existing ids were fine.
    EXPECT_EQ("b4da55", annotator->assignId(itemComponent));
    EXPECT_EQ("b4da56", annotator->assignId(itemComponentRef));
    EXPECT_EQ("b4da57", annotator->assignId(itemConnection));
    EXPECT_EQ("b4da58", annotator->assignId(itemEncapsulation));
    EXPECT_EQ("b4da59", annotator->assignId(itemImportSource));
    EXPECT_EQ("b4da5a", annotator->assignId(itemMapVariables));
    EXPECT_EQ("b4da5b", annotator->assignId(itemModel));
    EXPECT_EQ("b4da5c", annotator->assignId(itemReset));
    EXPECT_EQ("b4da5d", annotator->assignId(itemResetValue));
    EXPECT_EQ("b4da5e", annotator->assignId(itemTestValue));
    EXPECT_EQ("b4da5f", annotator->assignId(itemUnit));
    EXPECT_EQ("b4da60", annotator->assignId(itemUnits));
    EXPECT_EQ("b4da61", annotator->assignId(itemVariable));
}

TEST(Annotator, automaticIdAllItemsWrongModel)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(modelStringUniqueIds);
    auto annotator = libcellml::Annotator::create();

    libcellml::VariablePair connection = std::make_pair(
        model->component("component2")->variable(0)->equivalentVariable(0),
        model->component("component2")->variable(0));
    libcellml::VariablePair mapping = std::make_pair(
        model->component("component2")->variable(1),
        model->component("component2")->variable(1)->equivalentVariable(0));
    libcellml::UnitItem unit = std::make_pair(model->units(1), 0);

    libcellml::AnyItem itemComponent = std::make_pair(libcellml::Annotator::Type::COMPONENT, model->component(0));
    libcellml::AnyItem itemComponentRef = std::make_pair(libcellml::Annotator::Type::COMPONENT_REF, model->component("component2"));
    libcellml::AnyItem itemConnection = std::make_pair(libcellml::Annotator::Type::CONNECTION, connection);
    libcellml::AnyItem itemEncapsulation = std::make_pair(libcellml::Annotator::Type::ENCAPSULATION, model);
    libcellml::AnyItem itemImportSource = std::make_pair(libcellml::Annotator::Type::IMPORT, model->importSource(0));
    libcellml::AnyItem itemMapVariables = std::make_pair(libcellml::Annotator::Type::MAP_VARIABLES, mapping);
    libcellml::AnyItem itemModel = std::make_pair(libcellml::Annotator::Type::MODEL, model);
    libcellml::AnyItem itemReset = std::make_pair(libcellml::Annotator::Type::RESET, model->component("component2")->reset(0));
    libcellml::AnyItem itemResetValue = std::make_pair(libcellml::Annotator::Type::RESET_VALUE, model->component("component2")->reset(0));
    libcellml::AnyItem itemTestValue = std::make_pair(libcellml::Annotator::Type::TEST_VALUE, model->component("component2")->reset(0));
    libcellml::AnyItem itemUnit = std::make_pair(libcellml::Annotator::Type::UNIT, unit);
    libcellml::AnyItem itemUnits = std::make_pair(libcellml::Annotator::Type::UNITS, model->units(1));
    libcellml::AnyItem itemVariable = std::make_pair(libcellml::Annotator::Type::VARIABLE, model->component("component2")->variable(0));

    // Make a different model and build the annotator around that.
    auto model2 = libcellml::Model::create();
    annotator->buildModelIndex(model2);

    // Expect each have no change, since they are in a different model.
    EXPECT_EQ("", annotator->assignId(itemComponent));
    EXPECT_EQ("", annotator->assignId(itemComponentRef));
    EXPECT_EQ("", annotator->assignId(itemConnection));
    EXPECT_EQ("", annotator->assignId(itemEncapsulation));
    EXPECT_EQ("", annotator->assignId(itemImportSource));
    EXPECT_EQ("", annotator->assignId(itemMapVariables));
    EXPECT_EQ("", annotator->assignId(itemModel));
    EXPECT_EQ("", annotator->assignId(itemReset));
    EXPECT_EQ("", annotator->assignId(itemResetValue));
    EXPECT_EQ("", annotator->assignId(itemTestValue));
    EXPECT_EQ("", annotator->assignId(itemUnit));
    EXPECT_EQ("", annotator->assignId(itemUnits));
    EXPECT_EQ("", annotator->assignId(itemVariable));
}

TEST(Annotator, automaticIdAllItemsEntityType)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(modelStringNoIds);
    auto annotator = libcellml::Annotator::create();

    libcellml::VariablePair connection = std::make_pair(
        model->component("component2")->variable("variable1"),
        model->component("component2")->variable("variable1")->equivalentVariable(0));
    libcellml::VariablePair mapping = std::make_pair(
        model->component("component2")->variable("variable2"),
        model->component("component2")->variable("variable2")->equivalentVariable(0));
    libcellml::UnitItem unit = std::make_pair(model->units(1), 0);

    annotator->buildModelIndex(model);

    // Expect each have had a change of id since the old one is duplicated.
    EXPECT_EQ("b4da55", annotator->assignId(libcellml::Annotator::Type::COMPONENT, model->component(0)));
    EXPECT_EQ("b4da55", model->component(0)->id());

    EXPECT_EQ("b4da56", annotator->assignId(libcellml::Annotator::Type::COMPONENT_REF, model->component("component2")));
    EXPECT_EQ("b4da56", model->component("component2")->encapsulationId());

    EXPECT_EQ("b4da57", annotator->assignId(libcellml::Annotator::Type::CONNECTION, connection));
    EXPECT_EQ("b4da57", libcellml::Variable::equivalenceConnectionId(connection.first, connection.second));

    EXPECT_EQ("b4da58", annotator->assignId(libcellml::Annotator::Type::ENCAPSULATION, model));
    EXPECT_EQ("b4da58", model->encapsulationId());

    EXPECT_EQ("b4da59", annotator->assignId(libcellml::Annotator::Type::IMPORT, model->importSource(0)));
    EXPECT_EQ("b4da59", model->importSource(0)->id());

    EXPECT_EQ("b4da5a", annotator->assignId(libcellml::Annotator::Type::MAP_VARIABLES, mapping));
    EXPECT_EQ("b4da5a", libcellml::Variable::equivalenceMappingId(mapping.first, mapping.second));

    EXPECT_EQ("b4da5b", annotator->assignId(libcellml::Annotator::Type::MODEL, model));
    EXPECT_EQ("b4da5b", model->id());

    EXPECT_EQ("b4da5c", annotator->assignId(libcellml::Annotator::Type::RESET, model->component("component2")->reset(0)));
    EXPECT_EQ("b4da5c", model->component("component2")->reset(0)->id());

    EXPECT_EQ("b4da5d", annotator->assignId(libcellml::Annotator::Type::RESET_VALUE, model->component("component2")->reset(0)));
    EXPECT_EQ("b4da5d", model->component("component2")->reset(0)->resetValueId());

    EXPECT_EQ("b4da5e", annotator->assignId(libcellml::Annotator::Type::TEST_VALUE, model->component("component2")->reset(0)));
    EXPECT_EQ("b4da5e", model->component("component2")->reset(0)->testValueId());

    EXPECT_EQ("b4da5f", annotator->assignId(libcellml::Annotator::Type::UNIT, unit));
    EXPECT_EQ("b4da5f", model->units(1)->unitId(0));

    EXPECT_EQ("b4da60", annotator->assignId(libcellml::Annotator::Type::UNITS, model->units(1)));
    EXPECT_EQ("b4da60", model->units(1)->id());

    EXPECT_EQ("b4da61", annotator->assignId(libcellml::Annotator::Type::VARIABLE, model->component("component2")->variable(0)));
    EXPECT_EQ("b4da61", model->component("component2")->variable(0)->id());

    // For coverage doing the other pair combo too.
    libcellml::Variable::setEquivalenceConnectionId(connection.first, connection.second, "");
    libcellml::Variable::setEquivalenceMappingId(mapping.first, mapping.second, "");

    libcellml::VariablePair connection2 = std::make_pair(
        model->component("component2")->variable("variable1")->equivalentVariable(0),
        model->component("component2")->variable("variable1"));
    libcellml::VariablePair mapping2 = std::make_pair(
        model->component("component2")->variable("variable2")->equivalentVariable(0),
        model->component("component2")->variable("variable2"));

    EXPECT_EQ("b4da62", annotator->assignId(libcellml::Annotator::Type::CONNECTION, connection2));
    EXPECT_EQ("b4da62", libcellml::Variable::equivalenceConnectionId(connection2.first, connection2.second));

    EXPECT_EQ("b4da63", annotator->assignId(libcellml::Annotator::Type::MAP_VARIABLES, mapping2));
    EXPECT_EQ("b4da63", libcellml::Variable::equivalenceMappingId(mapping2.first, mapping2.second));
}

TEST(Annotator, assignAllIds)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(modelStringNoIds);
    auto annotator = libcellml::Annotator::create();

    annotator->assignAllIds(model);
    EXPECT_EQ(size_t(0), annotator->errorCount());

    libcellml::ModelPtr nullModel;
    annotator->assignAllIds(nullModel);
    EXPECT_EQ(size_t(0), annotator->errorCount());
}

TEST(Annotator, clearAllIds)
{
    std::vector<std::string> expectedErrors = {
        "No model is stored; no action has been taken.",
        "The model index is out-of-date.  Please (re)build it before attempting to access items by their id."};

    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(modelStringDuplicateIds);
    auto annotator = libcellml::Annotator::create();

    annotator->clearAllIds();
    EXPECT_EQ(size_t(1), annotator->errorCount());
    EXPECT_EQ(expectedErrors[0], annotator->error(0)->description());

    // Coverage.
    libcellml::ModelPtr nullModel;
    annotator->clearAllIds(nullModel);

    annotator->clearAllIds(model);
    EXPECT_EQ(size_t(0), annotator->errorCount());

    auto retrievalError = annotator->item("duplicateId");
    EXPECT_EQ(libcellml::Annotator::Type::ISSUE, retrievalError.first);
    EXPECT_EQ(expectedErrors[1], std::any_cast<libcellml::IssuePtr>(retrievalError.second)->description());
}

TEST(Annotator, listDuplicateIds)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(modelStringLotsOfDuplicateIds);
    auto annotator = libcellml::Annotator::create();
    std::vector<std::string> expectedIds = {"duplicateId1", "duplicateId2", "duplicateId3", "duplicateId4"};

    annotator->buildModelIndex(model);
    auto ids = annotator->duplicateIds();
    EXPECT_EQ(expectedIds, ids);
}

TEST(Annotator, retrieveDuplicateIdItemLists)
{
    std::vector<std::string> ids = {"duplicateId1", "duplicateId2", "duplicateId3", "duplicateId4"};

    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(modelStringLotsOfDuplicateIds);

    auto c2v1 = model->component("component2")->variable("variable1");
    auto c2v2 = model->component("component2")->variable("variable2");
    auto c3v1 = model->component("component2")->component("component3")->variable("variable1");
    auto c3v2 = model->component("component2")->component("component3")->variable("variable2");
    auto c4v1 = model->component("component4")->variable("variable1");
    auto c4v2 = model->component("component4")->variable("variable2");

    std::map<std::string, std::vector<libcellml::AnyItem>> expectedItems = {
        {"duplicateId1", {
                             std::make_pair(libcellml::Annotator::Type::UNITS, std::any(model->units("units2"))),
                             std::make_pair(libcellml::Annotator::Type::IMPORT, std::any(model->importSource(0))),
                             std::make_pair(libcellml::Annotator::Type::MAP_VARIABLES, std::any(libcellml::VariablePair(c4v1, c2v1))),
                             std::make_pair(libcellml::Annotator::Type::COMPONENT, std::any(model->component("component2"))),
                             std::make_pair(libcellml::Annotator::Type::CONNECTION, std::any(libcellml::VariablePair(c2v1, c3v1))),
                             std::make_pair(libcellml::Annotator::Type::TEST_VALUE, std::any(model->component("component2")->reset(0))),
                             std::make_pair(libcellml::Annotator::Type::COMPONENT_REF, std::any(model->component("component2")->component("component3"))),
                             std::make_pair(libcellml::Annotator::Type::VARIABLE, std::any(model->component("component2")->component("component3")->variable("variable2"))),
                         }},
        {"duplicateId2", {
                             std::make_pair(libcellml::Annotator::Type::MODEL, std::any(model)),
                             std::make_pair(libcellml::Annotator::Type::UNITS, std::any(model->units("units1"))),
                             std::make_pair(libcellml::Annotator::Type::UNITS, std::any(model->units("blob"))),
                             std::make_pair(libcellml::Annotator::Type::CONNECTION, std::any(libcellml::VariablePair(c4v2, c2v2))),
                             std::make_pair(libcellml::Annotator::Type::VARIABLE, std::any(c4v2)),
                             std::make_pair(libcellml::Annotator::Type::COMPONENT_REF, std::any(model->component("component2"))),
                             std::make_pair(libcellml::Annotator::Type::RESET, std::any(model->component("component2")->reset(0))),
                             std::make_pair(libcellml::Annotator::Type::VARIABLE, std::any(c3v1)),
                         }},
        {"duplicateId3", {
                             std::make_pair(libcellml::Annotator::Type::IMPORT, std::any(model->importSource(1))),
                             std::make_pair(libcellml::Annotator::Type::UNITS, std::any(model->units("units3"))),
                             std::make_pair(libcellml::Annotator::Type::VARIABLE, std::any(c4v1)),
                             std::make_pair(libcellml::Annotator::Type::VARIABLE, std::any(c2v2)),
                             std::make_pair(libcellml::Annotator::Type::MAP_VARIABLES, std::any(libcellml::VariablePair(c2v2, c4v2))),
                             std::make_pair(libcellml::Annotator::Type::COMPONENT, std::any(model->component("component2")->component("component3"))),
                             std::make_pair(libcellml::Annotator::Type::ENCAPSULATION, std::any(model)),
                         }},
        {"duplicateId4", {
                             std::make_pair(libcellml::Annotator::Type::UNIT, std::any(libcellml::UnitItem(std::make_pair(model->units("units2"), 0)))),
                             std::make_pair(libcellml::Annotator::Type::COMPONENT, std::any(model->component("component1"))),
                             std::make_pair(libcellml::Annotator::Type::COMPONENT, std::any(model->component("component4"))),
                             std::make_pair(libcellml::Annotator::Type::MAP_VARIABLES, std::any(libcellml::VariablePair(c2v1, c3v1))),
                             std::make_pair(libcellml::Annotator::Type::VARIABLE, std::any(c2v1)),
                             std::make_pair(libcellml::Annotator::Type::MAP_VARIABLES, std::any(libcellml::VariablePair(c2v2, c4v2))),
                             std::make_pair(libcellml::Annotator::Type::RESET_VALUE, std::any(model->component("component2")->reset(0))),
                         }},

    };

    libcellml::VariablePair pair;
    libcellml::VariablePair reversePair;
    libcellml::VariablePair testPair;

    auto annotator = libcellml::Annotator::create();
    annotator->buildModelIndex(model);

    EXPECT_EQ(ids, annotator->duplicateIds());

    for (const auto &id : ids) {
        std::vector<libcellml::AnyItem> items = annotator->items(id);
        size_t index = 0;

        for (const auto &item : items) {
            EXPECT_EQ(expectedItems[id][index].first, item.first);
            switch (item.first) {
            case libcellml::Annotator::Type::COMPONENT:
            case libcellml::Annotator::Type::COMPONENT_REF:
                EXPECT_EQ(std::any_cast<libcellml::ComponentPtr>(expectedItems[id][index].second), std::any_cast<libcellml::ComponentPtr>(item.second));
                break;
            case libcellml::Annotator::Type::CONNECTION:
            case libcellml::Annotator::Type::MAP_VARIABLES:
                pair = std::any_cast<libcellml::VariablePair>(expectedItems[id][index].second);
                testPair = std::any_cast<libcellml::VariablePair>(item.second);
                // TODO not sure how best to test these.
                // EXPECT_TRUE(((pair.first == testPair.first) && (pair.second == testPair.second)) || ((pair.second == testPair.first) && (pair.first == testPair.second)));

                // EXPECT_TRUE(((std::any_cast<libcellml::VariablePair>(expectedItems[id][index].second).first == std::any_cast<libcellml::VariablePair>(item.second).first) &&
                // (std::any_cast<libcellml::VariablePair>(expectedItems[id][index].second).second == std::any_cast<libcellml::VariablePair>(item.second).second))||
                // ((std::any_cast<libcellml::VariablePair>(expectedItems[id][index].second).second == std::any_cast<libcellml::VariablePair>(item.second).first) &&
                // (std::any_cast<libcellml::VariablePair>(expectedItems[id][index].second).first == std::any_cast<libcellml::VariablePair>(item.second).second)));
                break;
            case libcellml::Annotator::Type::ENCAPSULATION:
                EXPECT_EQ(std::any_cast<libcellml::ModelPtr>(expectedItems[id][index].second), std::any_cast<libcellml::ModelPtr>(item.second));
                break;
            case libcellml::Annotator::Type::IMPORT:
                EXPECT_EQ(std::any_cast<libcellml::ImportSourcePtr>(expectedItems[id][index].second), std::any_cast<libcellml::ImportSourcePtr>(item.second));
                break;
            case libcellml::Annotator::Type::MODEL:
                EXPECT_EQ(std::any_cast<libcellml::ModelPtr>(expectedItems[id][index].second), std::any_cast<libcellml::ModelPtr>(item.second));
                break;
            case libcellml::Annotator::Type::RESET:
            case libcellml::Annotator::Type::RESET_VALUE:
            case libcellml::Annotator::Type::TEST_VALUE:
                EXPECT_EQ(std::any_cast<libcellml::ResetPtr>(expectedItems[id][index].second), std::any_cast<libcellml::ResetPtr>(item.second));
                break;
            case libcellml::Annotator::Type::UNIT:
                EXPECT_EQ(std::any_cast<libcellml::UnitItem>(expectedItems[id][index].second), std::any_cast<libcellml::UnitItem>(item.second));
                break;
            case libcellml::Annotator::Type::UNITS:
                EXPECT_EQ(std::any_cast<libcellml::UnitsPtr>(expectedItems[id][index].second), std::any_cast<libcellml::UnitsPtr>(item.second));
                break;
            case libcellml::Annotator::Type::VARIABLE:
                EXPECT_EQ(std::any_cast<libcellml::VariablePtr>(expectedItems[id][index].second), std::any_cast<libcellml::VariablePtr>(item.second));
                break;
            }
            ++index;
        }
    }
}

TEST(Annotator, retrieveDuplicateIdItemsWithIndex)
{
    std::vector<std::string> ids = {"duplicateId1", "duplicateId2", "duplicateId3", "duplicateId4"};

    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(modelStringLotsOfDuplicateIds);

    auto c2v1 = model->component("component2")->variable("variable1");
    auto c2v2 = model->component("component2")->variable("variable2");
    auto c3v1 = model->component("component2")->component("component3")->variable("variable1");
    auto c3v2 = model->component("component2")->component("component3")->variable("variable2");
    auto c4v1 = model->component("component4")->variable("variable1");
    auto c4v2 = model->component("component4")->variable("variable2");

    std::map<std::string, std::vector<libcellml::AnyItem>> expectedItems = {
        {"duplicateId1", {
                             std::make_pair(libcellml::Annotator::Type::UNITS, std::any(model->units("units2"))),
                             std::make_pair(libcellml::Annotator::Type::IMPORT, std::any(model->importSource(0))),
                             std::make_pair(libcellml::Annotator::Type::MAP_VARIABLES, std::any(libcellml::VariablePair(c4v1, c2v1))),
                             std::make_pair(libcellml::Annotator::Type::COMPONENT, std::any(model->component("component2"))),
                             std::make_pair(libcellml::Annotator::Type::CONNECTION, std::any(libcellml::VariablePair(c2v1, c3v1))),
                             std::make_pair(libcellml::Annotator::Type::TEST_VALUE, std::any(model->component("component2")->reset(0))),
                             std::make_pair(libcellml::Annotator::Type::COMPONENT_REF, std::any(model->component("component2")->component("component3"))),
                             std::make_pair(libcellml::Annotator::Type::VARIABLE, std::any(model->component("component2")->component("component3")->variable("variable2"))),
                         }},
        {"duplicateId2", {
                             std::make_pair(libcellml::Annotator::Type::MODEL, std::any(model)),
                             std::make_pair(libcellml::Annotator::Type::UNITS, std::any(model->units("units1"))),
                             std::make_pair(libcellml::Annotator::Type::UNITS, std::any(model->units("blob"))),
                             std::make_pair(libcellml::Annotator::Type::CONNECTION, std::any(libcellml::VariablePair(c4v2, c2v2))),
                             std::make_pair(libcellml::Annotator::Type::VARIABLE, std::any(c4v2)),
                             std::make_pair(libcellml::Annotator::Type::COMPONENT_REF, std::any(model->component("component2"))),
                             std::make_pair(libcellml::Annotator::Type::RESET, std::any(model->component("component2")->reset(0))),
                             std::make_pair(libcellml::Annotator::Type::VARIABLE, std::any(c3v1)),
                         }},
        {"duplicateId3", {
                             std::make_pair(libcellml::Annotator::Type::IMPORT, std::any(model->importSource(1))),
                             std::make_pair(libcellml::Annotator::Type::UNITS, std::any(model->units("units3"))),
                             std::make_pair(libcellml::Annotator::Type::VARIABLE, std::any(c4v1)),
                             std::make_pair(libcellml::Annotator::Type::VARIABLE, std::any(c2v2)),
                             std::make_pair(libcellml::Annotator::Type::MAP_VARIABLES, std::any(libcellml::VariablePair(c2v2, c4v2))),
                             std::make_pair(libcellml::Annotator::Type::COMPONENT, std::any(model->component("component2")->component("component3"))),
                             std::make_pair(libcellml::Annotator::Type::ENCAPSULATION, std::any(model)),
                         }},
        {"duplicateId4", {
                             std::make_pair(libcellml::Annotator::Type::UNIT, std::any(libcellml::UnitItem(std::make_pair(model->units("units2"), 0)))),
                             std::make_pair(libcellml::Annotator::Type::COMPONENT, std::any(model->component("component1"))),
                             std::make_pair(libcellml::Annotator::Type::COMPONENT, std::any(model->component("component4"))),
                             std::make_pair(libcellml::Annotator::Type::MAP_VARIABLES, std::any(libcellml::VariablePair(c2v1, c3v1))),
                             std::make_pair(libcellml::Annotator::Type::VARIABLE, std::any(c2v1)),
                             std::make_pair(libcellml::Annotator::Type::MAP_VARIABLES, std::any(libcellml::VariablePair(c2v2, c4v2))),
                             std::make_pair(libcellml::Annotator::Type::RESET_VALUE, std::any(model->component("component2")->reset(0))),
                         }},

    };

    libcellml::VariablePair pair;
    libcellml::VariablePair reversePair;
    libcellml::VariablePair testPair;

    auto annotator = libcellml::Annotator::create();
    annotator->buildModelIndex(model);

    EXPECT_EQ(ids, annotator->duplicateIds());

    for (const auto &id : ids) {
        auto num = annotator->duplicateCount(id);
        for (size_t index = 0; index < num; ++index) {
            libcellml::AnyItem item = annotator->item(id, index);

            EXPECT_EQ(expectedItems[id][index].first, item.first);

            switch (item.first) {
            case libcellml::Annotator::Type::COMPONENT:
            case libcellml::Annotator::Type::COMPONENT_REF:
                EXPECT_EQ(std::any_cast<libcellml::ComponentPtr>(expectedItems[id][index].second), std::any_cast<libcellml::ComponentPtr>(item.second));
                break;
            case libcellml::Annotator::Type::CONNECTION:
            case libcellml::Annotator::Type::MAP_VARIABLES:
                pair = std::any_cast<libcellml::VariablePair>(expectedItems[id][index].second);
                testPair = std::any_cast<libcellml::VariablePair>(item.second);
                // TODO not sure how best to test these.
                // EXPECT_TRUE(((pair.first == testPair.first) && (pair.second == testPair.second)) || ((pair.second == testPair.first) && (pair.first == testPair.second)));

                // EXPECT_TRUE(((std::any_cast<libcellml::VariablePair>(expectedItems[id][index].second).first == std::any_cast<libcellml::VariablePair>(item.second).first) &&
                // (std::any_cast<libcellml::VariablePair>(expectedItems[id][index].second).second == std::any_cast<libcellml::VariablePair>(item.second).second))||
                // ((std::any_cast<libcellml::VariablePair>(expectedItems[id][index].second).second == std::any_cast<libcellml::VariablePair>(item.second).first) &&
                // (std::any_cast<libcellml::VariablePair>(expectedItems[id][index].second).first == std::any_cast<libcellml::VariablePair>(item.second).second)));
                break;
            case libcellml::Annotator::Type::ENCAPSULATION:
                EXPECT_EQ(std::any_cast<libcellml::ModelPtr>(expectedItems[id][index].second), std::any_cast<libcellml::ModelPtr>(item.second));
                break;
            case libcellml::Annotator::Type::IMPORT:
                EXPECT_EQ(std::any_cast<libcellml::ImportSourcePtr>(expectedItems[id][index].second), std::any_cast<libcellml::ImportSourcePtr>(item.second));
                break;
            case libcellml::Annotator::Type::MODEL:
                EXPECT_EQ(std::any_cast<libcellml::ModelPtr>(expectedItems[id][index].second), std::any_cast<libcellml::ModelPtr>(item.second));
                break;
            case libcellml::Annotator::Type::RESET:
            case libcellml::Annotator::Type::RESET_VALUE:
            case libcellml::Annotator::Type::TEST_VALUE:
                EXPECT_EQ(std::any_cast<libcellml::ResetPtr>(expectedItems[id][index].second), std::any_cast<libcellml::ResetPtr>(item.second));
                break;
            case libcellml::Annotator::Type::UNIT:
                EXPECT_EQ(std::any_cast<libcellml::UnitItem>(expectedItems[id][index].second), std::any_cast<libcellml::UnitItem>(item.second));
                break;
            case libcellml::Annotator::Type::UNITS:
                EXPECT_EQ(std::any_cast<libcellml::UnitsPtr>(expectedItems[id][index].second), std::any_cast<libcellml::UnitsPtr>(item.second));
                break;
            case libcellml::Annotator::Type::VARIABLE:
                EXPECT_EQ(std::any_cast<libcellml::VariablePtr>(expectedItems[id][index].second), std::any_cast<libcellml::VariablePtr>(item.second));
                break;
            }
        }
    }
}

TEST(Annotator, badAnyCastWithIndices)
{
    auto parser = libcellml::Parser::create();
    auto m = parser->parseModel(modelStringDuplicateIds);
    auto annotator = libcellml::Annotator::create();
    annotator->buildModelIndex(m);

    // Trigger errors on all items because of miscasting:
    EXPECT_EQ(nullptr, annotator->component("duplicateId", 0));
    EXPECT_EQ(nullptr, annotator->componentRef("duplicateId", 0));
    EXPECT_EQ(nullptr, annotator->connection("duplicateId", 0).first);
    EXPECT_EQ(nullptr, annotator->encapsulation("duplicateId", 1));
    EXPECT_EQ(nullptr, annotator->importSource("duplicateId", 0));
    EXPECT_EQ(nullptr, annotator->model("duplicateId", 1));
    EXPECT_EQ(nullptr, annotator->mapVariables("duplicateId", 0).first);
    EXPECT_EQ(nullptr, annotator->reset("duplicateId", 0));
    EXPECT_EQ(nullptr, annotator->resetValue("duplicateId", 0));
    EXPECT_EQ(nullptr, annotator->testValue("duplicateId", 0));
    EXPECT_EQ(nullptr, annotator->unit("duplicateId", 0).first);
    EXPECT_EQ(nullptr, annotator->units("duplicateId", 0));
    EXPECT_EQ(nullptr, annotator->variable("duplicateId", 0));

    EXPECT_EQ(nullptr, annotator->component("duplicateId", 99));
    EXPECT_EQ(nullptr, annotator->componentRef("duplicateId", 99));
    EXPECT_EQ(nullptr, annotator->connection("duplicateId", 99).first);
    EXPECT_EQ(nullptr, annotator->encapsulation("duplicateId", 99));
    EXPECT_EQ(nullptr, annotator->importSource("duplicateId", 99));
    EXPECT_EQ(nullptr, annotator->model("duplicateId", 99));
    EXPECT_EQ(nullptr, annotator->mapVariables("duplicateId", 99).first);
    EXPECT_EQ(nullptr, annotator->reset("duplicateId", 99));
    EXPECT_EQ(nullptr, annotator->resetValue("duplicateId", 99));
    EXPECT_EQ(nullptr, annotator->testValue("duplicateId", 99));
    EXPECT_EQ(nullptr, annotator->unit("duplicateId", 99).first);
    EXPECT_EQ(nullptr, annotator->units("duplicateId", 99));
    EXPECT_EQ(nullptr, annotator->variable("duplicateId", 99));
}

TEST(Annotator, pythonBindingFunctionsCoverage)
{
    // Several functions are provided so that bindings are easier to use.
    // This test is to provide coverage rather than demonstrate functionality.

    auto parser = libcellml::Parser::create();
    auto annotator = libcellml::Annotator::create();
    auto model = parser->parseModel(modelStringNoIds);

    // Expect failure as no model is built.
    EXPECT_EQ("", annotator->assignId(libcellml::Annotator::Type::UNIT, model->units("units2"), 0));
    EXPECT_EQ("", annotator->assignId(libcellml::Annotator::Type::CONNECTION, model->component("component2")->variable("variable1"), model->component("component3")->variable("variable1")));
    EXPECT_EQ("", annotator->assignId(libcellml::Annotator::Type::MAP_VARIABLES, model->component("component2")->variable("variable1"), model->component("component3")->variable("variable1")));

    annotator->buildModelIndex(model);

    // Expect success.
    EXPECT_EQ("b4da55", annotator->assignId(libcellml::Annotator::Type::UNIT, model->units("units2"), 0));
    EXPECT_EQ("b4da56", annotator->assignId(libcellml::Annotator::Type::CONNECTION, model->component("component2")->variable("variable1"), model->component("component3")->variable("variable1")));
    EXPECT_EQ("b4da57", annotator->assignId(libcellml::Annotator::Type::MAP_VARIABLES, model->component("component2")->variable("variable1"), model->component("component3")->variable("variable1")));

    EXPECT_EQ("component", annotator->typeString(libcellml::Annotator::Type::COMPONENT));
    EXPECT_EQ("component_ref", annotator->typeString(libcellml::Annotator::Type::COMPONENT_REF));
    EXPECT_EQ("connection", annotator->typeString(libcellml::Annotator::Type::CONNECTION));
    EXPECT_EQ("issue", annotator->typeString(libcellml::Annotator::Type::ISSUE));
    EXPECT_EQ("import", annotator->typeString(libcellml::Annotator::Type::IMPORT));
    EXPECT_EQ("map_variables", annotator->typeString(libcellml::Annotator::Type::MAP_VARIABLES));
    EXPECT_EQ("model", annotator->typeString(libcellml::Annotator::Type::MODEL));
    EXPECT_EQ("encapsulation", annotator->typeString(libcellml::Annotator::Type::ENCAPSULATION));
    EXPECT_EQ("reset", annotator->typeString(libcellml::Annotator::Type::RESET));
    EXPECT_EQ("reset_value", annotator->typeString(libcellml::Annotator::Type::RESET_VALUE));
    EXPECT_EQ("test_value", annotator->typeString(libcellml::Annotator::Type::TEST_VALUE));
    EXPECT_EQ("unit", annotator->typeString(libcellml::Annotator::Type::UNIT));
    EXPECT_EQ("units", annotator->typeString(libcellml::Annotator::Type::UNITS));
    EXPECT_EQ("variable", annotator->typeString(libcellml::Annotator::Type::VARIABLE));

    std::vector<std::string> expectedStrings = {
        "component",
        "component_ref",
        "connection",
        "encapsulation",
        "import",
        "issue",
        "map_variables",
        "model",
        "reset",
        "reset_value",
        "test_value",
        "unit",
        "units",
        "variable",
    };

    // The type has to be overlaoded with uint64_t type so that the Annotator::Type can exist as a member
    // of the annotator and have member functions with an argument of Annotator::Type.
    size_t index = 0;
    for (std::uint64_t type = 0; type <= 13; ++type) {
        EXPECT_EQ(expectedStrings[index], annotator->typeString(type));
        ++index;
    }
}

TEST(Annotator, hashChangesAndUpdates)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(modelStringUniqueIds);
    auto annotator = libcellml::Annotator::create();

    EXPECT_FALSE(annotator->isBuilt());

    annotator->buildModelIndex(model);
    EXPECT_TRUE(annotator->isBuilt());

    model->setId("iHaveChangedSinceTheLastBuild");
    EXPECT_FALSE(annotator->isBuilt());

    // Can set id, but does not rebuild.
    EXPECT_EQ("b4da55", annotator->assignId(libcellml::Annotator::Type::COMPONENT, model->component(0)));
    EXPECT_FALSE(annotator->isBuilt());

    // Shouldn't be able to retrieve anything since the build is out of date.
    EXPECT_EQ(nullptr, annotator->model("model_1"));
    EXPECT_EQ(nullptr, annotator->encapsulation("encapsulation_1"));
    EXPECT_EQ(nullptr, annotator->component("component_1"));
    EXPECT_EQ(nullptr, annotator->component("component_2"));
    EXPECT_EQ(nullptr, annotator->component("component_ref_1"));
    EXPECT_EQ(nullptr, annotator->component("component_3"));
    EXPECT_EQ(nullptr, annotator->componentRef("component_ref_2"));
    EXPECT_EQ(nullptr, annotator->importSource("import_1"));
    EXPECT_EQ(nullptr, annotator->units("units_1"));
    EXPECT_EQ(nullptr, annotator->importSource("import_2"));
    EXPECT_EQ(nullptr, annotator->units("units_2"));
    EXPECT_EQ(nullptr, annotator->unit("unit_1").first);
    EXPECT_EQ(size_t(0), annotator->unit("unit_1").second);
    EXPECT_EQ(nullptr, annotator->variable("variable_1"));
    EXPECT_EQ(nullptr, annotator->variable("variable_2"));
    EXPECT_EQ(nullptr, annotator->reset("reset_1"));
    EXPECT_EQ(nullptr, annotator->testValue("test_value_1"));
    EXPECT_EQ(nullptr, annotator->resetValue("reset_value_1"));
    EXPECT_EQ(nullptr, annotator->variable("variable_3"));
    EXPECT_EQ(nullptr, annotator->variable("variable_4"));
    EXPECT_EQ(nullptr, annotator->connection("connection_1").first);
    EXPECT_EQ(nullptr, annotator->mapVariables("map_variables_1").first);
    EXPECT_EQ(nullptr, annotator->mapVariables("map_variables_2").first);
}

TEST(Annotator, hashUpdatedWithAllAutomaticIds)
{
    // Expect that using the local Annotator functionality to set automatic ids will
    // not make the build hash out of date.
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(modelStringUniqueIds);
    auto annotator = libcellml::Annotator::create();

    annotator->buildModelIndex(model);
    EXPECT_TRUE(annotator->isBuilt());

    annotator->assignAllIds();
    EXPECT_TRUE(annotator->isBuilt());
}

TEST(Annotator, autoIdOnOutOfDateBuild)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(modelStringUniqueIds);
    auto annotator = libcellml::Annotator::create();

    annotator->buildModelIndex(model);
    EXPECT_TRUE(annotator->isBuilt());

    model->component(0)->setId("changed");
    EXPECT_FALSE(annotator->isBuilt());
    EXPECT_EQ("b4da55", annotator->assignId(libcellml::Annotator::Type::COMPONENT, model->component(0)));
    EXPECT_EQ("b4da55", model->component(0)->id());

    model->component("component2")->setEncapsulationId("changed");
    EXPECT_FALSE(annotator->isBuilt());
    EXPECT_EQ("b4da56", annotator->assignId(libcellml::Annotator::Type::COMPONENT_REF, model->component("component2")));
    EXPECT_EQ("b4da56", model->component("component2")->encapsulationId());

    libcellml::VariablePair connection = std::make_pair(
        model->component("component2")->variable("variable1"),
        model->component("component2")->variable("variable1")->equivalentVariable(0));
    libcellml::Variable::setEquivalenceConnectionId(connection.first, connection.second, "changed");
    EXPECT_FALSE(annotator->isBuilt());
    EXPECT_EQ("b4da57", annotator->assignId(libcellml::Annotator::Type::CONNECTION, connection));
    EXPECT_EQ("b4da57", libcellml::Variable::equivalenceConnectionId(connection.first, connection.second));

    model->setEncapsulationId("changed");
    EXPECT_FALSE(annotator->isBuilt());
    EXPECT_EQ("b4da58", annotator->assignId(libcellml::Annotator::Type::ENCAPSULATION, model));
    EXPECT_EQ("b4da58", model->encapsulationId());

    model->importSource(0)->setId("changed");
    EXPECT_FALSE(annotator->isBuilt());
    EXPECT_EQ("b4da59", annotator->assignId(libcellml::Annotator::Type::IMPORT, model->importSource(0)));
    EXPECT_EQ("b4da59", model->importSource(0)->id());

    libcellml::VariablePair mapping = std::make_pair(
        model->component("component2")->variable("variable2"),
        model->component("component2")->variable("variable2")->equivalentVariable(0));
    libcellml::Variable::setEquivalenceMappingId(mapping.first, mapping.second, "changed");
    EXPECT_FALSE(annotator->isBuilt());
    EXPECT_EQ("b4da5a", annotator->assignId(libcellml::Annotator::Type::MAP_VARIABLES, mapping));
    EXPECT_EQ("b4da5a", libcellml::Variable::equivalenceMappingId(mapping.first, mapping.second));

    model->setId("changed");
    EXPECT_FALSE(annotator->isBuilt());
    EXPECT_EQ("b4da5b", annotator->assignId(libcellml::Annotator::Type::MODEL, model));
    EXPECT_EQ("b4da5b", model->id());

    model->component("component2")->reset(0)->setId("changed");
    EXPECT_FALSE(annotator->isBuilt());
    EXPECT_EQ("b4da5c", annotator->assignId(libcellml::Annotator::Type::RESET, model->component("component2")->reset(0)));
    EXPECT_EQ("b4da5c", model->component("component2")->reset(0)->id());

    model->component("component2")->reset(0)->setResetValueId("changed");
    EXPECT_FALSE(annotator->isBuilt());
    EXPECT_EQ("b4da5d", annotator->assignId(libcellml::Annotator::Type::RESET_VALUE, model->component("component2")->reset(0)));
    EXPECT_EQ("b4da5d", model->component("component2")->reset(0)->resetValueId());

    model->component("component2")->reset(0)->setTestValueId("changed");
    EXPECT_FALSE(annotator->isBuilt());
    EXPECT_EQ("b4da5e", annotator->assignId(libcellml::Annotator::Type::TEST_VALUE, model->component("component2")->reset(0)));
    EXPECT_EQ("b4da5e", model->component("component2")->reset(0)->testValueId());

    libcellml::UnitItem unit = std::make_pair(model->units(1), 0);
    model->units(1)->setUnitId(0, "changed");
    EXPECT_FALSE(annotator->isBuilt());
    EXPECT_EQ("b4da5f", annotator->assignId(libcellml::Annotator::Type::UNIT, unit));
    EXPECT_EQ("b4da5f", model->units(1)->unitId(0));

    EXPECT_FALSE(annotator->isBuilt());
    model->units(1)->setId("changed");
    EXPECT_EQ("b4da60", annotator->assignId(libcellml::Annotator::Type::UNITS, model->units(1)));
    EXPECT_EQ("b4da60", model->units(1)->id());

    EXPECT_FALSE(annotator->isBuilt());
    model->component("component2")->variable(0)->setId("changed");
    EXPECT_EQ("b4da61", annotator->assignId(libcellml::Annotator::Type::VARIABLE, model->component("component2")->variable(0)));
    EXPECT_EQ("b4da61", model->component("component2")->variable(0)->id());
}

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
#include <variant>

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
    auto item = annotator->item("model_id");

    // std::cout << m << std::endl;

    // EXPECT_EQ(model, std::get_if<0>(&annotator->item("model_id").second));
    // EXPECT_EQ(component, annotator->item("component_id").second);
    // EXPECT_EQ(reset, annotator->item("reset_id").second);
    // EXPECT_EQ(variable, annotator->item("variable_id").second);
    // EXPECT_EQ(units, annotator->item("units_id").second);
    // EXPECT_EQ(importSource, annotator->item("import_id").second);
    // EXPECT_EQ("issue", annotator->item("I_dont_exist").first);
}

TEST(Annotator, getNonEntityFromId)
{
    auto model = createModelTwoComponentsWithOneVariableEach("model", "c1", "c2", "v1", "v2");
    auto annotator = libcellml::Annotator::create();

    // Encapsulation structure
    auto c1 = model->component("c1");
    auto c2 = model->component("c2");
    c1->addComponent(c2);
    model->setEncapsulationId("encapsulation_id");
    c1->setEncapsulationId("component_ref1_id");
    c2->setEncapsulationId("component_ref2_id");

    // Connections
    c1->variable("v1")->setInterfaceType("public_and_private");
    c2->variable("v2")->setInterfaceType("public_and_private");
    libcellml::Variable::addEquivalence(c1->variable("v1"), c2->variable("v2"));
    libcellml::Variable::setEquivalenceMappingId(c1->variable("v1"), c2->variable("v2"), "map_id");
    libcellml::Variable::setEquivalenceConnectionId(c1->variable("v1"), c2->variable("v2"), "connection_id");
    auto v1v2 = std::make_pair(c1->variable("v1"), c2->variable("v2"));

    // annotator->build(model);

    // KRM: Need to have a structure by which to return information about the type of thing returned, when it is
    // not a NamedEntity class (as in previous test). Things like connections and mappings are both identified by
    // pairs of variables, and encapsulation ids for components by their components.  The encapsulation has no
    // item in libCellML at all, so should probably be a string?
    // EXPECT_EQ(v1v2, annotator->itemFromId("map_id"));
    // EXPECT_EQ(v1v2, annotator->itemFromId("connection_id"));
    // EXPECT_EQ(c1, annotator->itemFromId("component_ref1_id"));
    // EXPECT_EQ("encapsulation", annotator->itemFromId("encapsulation_id"));
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

    // annotator->build(model);

    // EXPECT_EQ(typeid(model).name(), annotator->typeFromId("model_id"));
    // EXPECT_EQ(typeid(component).name(), annotator->typeFromId("component_id"));
    // EXPECT_EQ(typeid(reset).name(), annotator->typeFromId("reset_id"));
    // EXPECT_EQ(typeid(variable).name(), annotator->typeFromId("variable_id"));
    // EXPECT_EQ(typeid(units).name(), annotator->typeFromId("units_id"));
    // EXPECT_EQ(typeid(importSource).name(), annotator->typeFromId("import_id"));
    // EXPECT_EQ("", annotator->typeFromId("I_dont_exist"));
}

TEST(Annotator, setAutomaticIdsOnEverything)
{
    // KRM: This functionality should go into the Printer instead?
    EXPECT_TRUE(true);
}

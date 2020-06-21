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

TEST(Annotator, getItemsFromId)
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

    EXPECT_EQ(model, annotator->itemFromId("model_id"));
    EXPECT_EQ(component, annotator->itemFromId("component_id"));
    EXPECT_EQ(reset, annotator->itemFromId("reset_id"));
    EXPECT_EQ(variable, annotator->itemFromId("variable_id"));
    EXPECT_EQ(units, annotator->itemFromId("units_id"));
    EXPECT_EQ(importSource, annotator->itemFromId("import_id"));
    // EXPECT_EQ(nullptr, annotator->itemFromId("I_dont_exist"));
}

TEST(Annotator, getItemTypeFromId)
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

    EXPECT_EQ(typeid(model).name(), annotator->typeFromId("model_id"));
    EXPECT_EQ(typeid(component).name(), annotator->typeFromId("component_id"));
    EXPECT_EQ(typeid(reset).name(), annotator->typeFromId("reset_id"));
    EXPECT_EQ(typeid(variable).name(), annotator->typeFromId("variable_id"));
    EXPECT_EQ(typeid(units).name(), annotator->typeFromId("units_id"));
    EXPECT_EQ(typeid(importSource).name(), annotator->typeFromId("import_id"));
    EXPECT_EQ("", annotator->typeFromId("I_dont_exist"));
}

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

const std::string modelStringUniqueIds = fileContents("annotator/unique_ids.cellml");
const std::string modelStringDuplicateIds = fileContents("annotator/duplicate_ids.cellml");
const std::string modelStringLotsOfDuplicateIds = fileContents("annotator/lots_of_duplicate_ids.cellml");
const std::string modelStringNoIds = fileContents("annotator/no_ids.cellml");

TEST(Annotator, getSetHasModel)
{
    auto model = libcellml::Model::create("model");
    auto annotator = libcellml::Annotator::create();

    EXPECT_FALSE(annotator->hasModel());
    EXPECT_EQ(nullptr, annotator->model());

    annotator->setModel(model);

    EXPECT_TRUE(annotator->hasModel());
    EXPECT_NE(nullptr, annotator->model());
}

TEST(Annotator, itemFromNoModel)
{
    auto annotator = libcellml::Annotator::create();

    EXPECT_EQ(libcellml::CellMLElement::UNDEFINED, annotator->item("model_id").first);
    EXPECT_EQ(libcellml::CellMLElement::UNDEFINED, annotator->item("model_id", 3).first);
}

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

    annotator->setModel(model);

    EXPECT_EQ(libcellml::CellMLElement::MODEL, annotator->item("model_id").first);
    EXPECT_EQ(model, std::any_cast<libcellml::ModelPtr>(annotator->item("model_id").second));
    EXPECT_EQ(libcellml::CellMLElement::COMPONENT, annotator->item("component_id").first);
    EXPECT_EQ(component, std::any_cast<libcellml::ComponentPtr>(annotator->item("component_id").second));
    EXPECT_EQ(libcellml::CellMLElement::VARIABLE, annotator->item("variable_id").first);
    EXPECT_EQ(variable, std::any_cast<libcellml::VariablePtr>(annotator->item("variable_id").second));
    EXPECT_EQ(libcellml::CellMLElement::RESET, annotator->item("reset_id").first);
    EXPECT_EQ(reset, std::any_cast<libcellml::ResetPtr>(annotator->item("reset_id").second));
    EXPECT_EQ(libcellml::CellMLElement::UNITS, annotator->item("units_id").first);
    EXPECT_EQ(units, std::any_cast<libcellml::UnitsPtr>(annotator->item("units_id").second));
    EXPECT_EQ(libcellml::CellMLElement::IMPORT, annotator->item("import_id").first);
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

    annotator->setModel(model);

    // Unit items are returned as name string and pair of UnitsPtr parent and index:
    EXPECT_EQ(libcellml::CellMLElement::UNIT, annotator->item("unit1_id").first);
    EXPECT_EQ(units, std::any_cast<libcellml::UnitItem>(annotator->item("unit1_id").second).first);
    EXPECT_EQ(size_t(0), std::any_cast<libcellml::UnitItem>(annotator->item("unit1_id").second).second);
    EXPECT_EQ(libcellml::CellMLElement::UNIT, annotator->item("unit2_id").first);
    EXPECT_EQ(units, std::any_cast<libcellml::UnitItem>(annotator->item("unit2_id").second).first);
    EXPECT_EQ(size_t(1), std::any_cast<libcellml::UnitItem>(annotator->item("unit2_id").second).second);
    EXPECT_EQ(libcellml::CellMLElement::UNIT, annotator->item("unit3_id").first);
    EXPECT_EQ(units, std::any_cast<libcellml::UnitItem>(annotator->item("unit3_id").second).first);
    EXPECT_EQ(size_t(2), std::any_cast<libcellml::UnitItem>(annotator->item("unit3_id").second).second);

    // Connections and map variables are returned as VariablePairs.  Note that connection ids could be
    // represented by any one of the pairs of variables in that connection.
    EXPECT_EQ(libcellml::CellMLElement::MAP_VARIABLES, annotator->item("map_id").first);
    EXPECT_EQ(v1v2, std::any_cast<libcellml::VariablePair>(annotator->item("map_id").second));
    EXPECT_EQ(libcellml::CellMLElement::CONNECTION, annotator->item("connection_id").first);
    EXPECT_TRUE((v1v2 == std::any_cast<libcellml::VariablePair>(annotator->item("connection_id").second) || (v3v4 == std::any_cast<libcellml::VariablePair>(annotator->item("connection_id").second))));

    // Component refs are returned as name string and ComponentPtr:
    EXPECT_EQ(libcellml::CellMLElement::COMPONENT_REF, annotator->item("component_ref1_id").first);
    EXPECT_EQ(c1, std::any_cast<libcellml::ComponentPtr>(annotator->item("component_ref1_id").second));

    // Encapsulation is returned as name string and ModelPtr :
    EXPECT_EQ(libcellml::CellMLElement::ENCAPSULATION, annotator->item("encapsulation_id").first);
    EXPECT_EQ(model, std::any_cast<libcellml::ModelPtr>(annotator->item("encapsulation_id").second));

    // Reset children are returned as name string and reset pointer:
    EXPECT_EQ(libcellml::CellMLElement::RESET_VALUE, annotator->item("reset_value_id").first);
    EXPECT_EQ(reset, std::any_cast<libcellml::ResetPtr>(annotator->item("reset_value_id").second));
    EXPECT_EQ(libcellml::CellMLElement::TEST_VALUE, annotator->item("test_value_id").first);
    EXPECT_EQ(reset, std::any_cast<libcellml::ResetPtr>(annotator->item("test_value_id").second));
}

TEST(Annotator, errorHandling)
{
    auto model = libcellml::Model::create("model");
    auto annotator = libcellml::Annotator::create();

    EXPECT_EQ(libcellml::CellMLElement::UNDEFINED, annotator->item("i_dont_exist").first);
    EXPECT_EQ(size_t(1), annotator->issueCount());

    // Building an empty model will result in an empty map and return an error.
    annotator->setModel(model);
    EXPECT_EQ(libcellml::CellMLElement::UNDEFINED, annotator->item("i_dont_exist").first);
    EXPECT_EQ(size_t(1), annotator->issueCount());

    model->setId("model_id"); // Add an id into the model and rebuild.
    annotator->setModel(model);

    // Test that an Issue is created and logged when an id is not found:
    EXPECT_EQ(libcellml::CellMLElement::UNDEFINED, annotator->item("i_dont_exist").first);
    EXPECT_EQ(size_t(1), annotator->issueCount());

    // Test that repeated calls to the same unfound id generate new errors:
    EXPECT_EQ(libcellml::CellMLElement::UNDEFINED, annotator->item("i_dont_exist").first);
    EXPECT_EQ(size_t(2), annotator->issueCount());
}

TEST(Annotator, duplicateIdBehaviour)
{
    std::vector<std::string> expectedErrors = {
        "The id 'duplicateId' occurs 3 times in the model so a unique item cannot be located.",
    };
    auto model = libcellml::Model::create("model");
    auto annotator = libcellml::Annotator::create();
    auto component = libcellml::Component::create();
    auto variable = libcellml::Variable::create();

    model->setId("duplicateId");
    component->setId("duplicateId");
    variable->setId("duplicateId");

    component->addVariable(variable);
    model->addComponent(component);

    annotator->setModel(model);

    EXPECT_EQ(libcellml::CellMLElement::UNDEFINED, annotator->item("duplicateId").first);
    EXPECT_EQ(size_t(1), annotator->issueCount());
    EXPECT_EQ(expectedErrors[0], annotator->issue(0)->description());

    EXPECT_FALSE(annotator->isUnique("duplicateId"));
    EXPECT_EQ(size_t(3), annotator->duplicateCount("duplicateId"));
}

TEST(Annotator, getItemByIdSpecificType)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(modelStringUniqueIds);
    auto annotator = libcellml::Annotator::create();
    auto v1v1 = std::make_pair(model->component("component2")->variable("variable1"), model->component("component2")->component("component3")->variable("variable1"));
    auto v2v2 = std::make_pair(model->component("component2")->variable("variable2"), model->component("component2")->component("component3")->variable("variable2"));

    annotator->setModel(model);

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
    EXPECT_EQ(model->component("component2")->component("component3")->variable("variable1"), annotator->variable("variable_3"));
    EXPECT_EQ(model->component("component2")->component("component3")->variable("variable2"), annotator->variable("variable_4"));
    EXPECT_EQ(v1v1, annotator->connection("connection_1"));
    EXPECT_EQ(v1v1, annotator->mapVariables("map_variables_1"));
    EXPECT_EQ(v2v2, annotator->mapVariables("map_variables_2"));

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
    EXPECT_EQ(size_t(15), annotator->issueCount());
    EXPECT_EQ(size_t(15), annotator->errorCount());
    for (size_t i = 0; i < 15; ++i) {
        EXPECT_EQ("This Annotator object does not have a model to work with.", annotator->error(i)->description());
    }

    annotator->setModel(model);

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

    EXPECT_EQ(size_t(15), annotator->issueCount());
    EXPECT_EQ(size_t(15), annotator->warningCount());
    for (size_t i = 0; i < 15; ++i) {
        EXPECT_EQ("The id 'duplicateId' occurs 29 times in the model so a unique item cannot be located.", annotator->warning(i)->description());
    }
}

TEST(Annotator, castingOnRetrieval)
{
    std::vector<std::string> idList = {
        "component_1",
        "component_ref_1",
        "connection_1",
        "encapsulation_1",
        "import_1",
        "map_variables_1",
        "model_1",
        "reset_1",
        "reset_value_1",
        "test_value_1",
        "unit_1",
        "units_1",
        "variable_1",
    };
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(modelStringUniqueIds);
    auto annotator = libcellml::Annotator::create();
    annotator->setModel(model);

    libcellml::AnyItem itemInfo;

    libcellml::VariablePair v1v2;
    libcellml::ComponentPtr c1;
    libcellml::ComponentPtr c2;

    for (auto const &id : idList) {
        itemInfo = annotator->item(id);
        switch (itemInfo.first) {
        case libcellml::CellMLElement::COMPONENT:
            EXPECT_EQ(model->component("component1"), std::any_cast<libcellml::ComponentPtr>(itemInfo.second));
            break;
        case libcellml::CellMLElement::COMPONENT_REF:
        case libcellml::CellMLElement::MATHML:
            EXPECT_EQ(model->component("component2"), std::any_cast<libcellml::ComponentPtr>(itemInfo.second));
            break;
        case libcellml::CellMLElement::CONNECTION:
            v1v2 = std::any_cast<libcellml::VariablePair>(itemInfo.second);
            c1 = owningComponent(v1v2.first);
            c2 = owningComponent(v1v2.second);
            EXPECT_TRUE((model->component("component2") == c1) || (model->component("component2") == c2));
            EXPECT_TRUE((model->component("component2")->component("component3") == c1) || (model->component("component2")->component("component3") == c2));
            break;
        case libcellml::CellMLElement::MAP_VARIABLES:
            v1v2 = std::any_cast<libcellml::VariablePair>(itemInfo.second);
            EXPECT_TRUE((v1v2.first == model->component("component2")->variable("variable1")) || (v1v2.first == model->component("component2")->component("component3")->variable("variable1")));
            EXPECT_TRUE((v1v2.second == model->component("component2")->variable("variable1")) || (v1v2.second == model->component("component2")->component("component3")->variable("variable1")));
            break;
        case libcellml::CellMLElement::IMPORT:
            EXPECT_EQ(model->importSource(0), std::any_cast<libcellml::ImportSourcePtr>(itemInfo.second));
            break;
        case libcellml::CellMLElement::ENCAPSULATION:
        case libcellml::CellMLElement::MODEL:
            EXPECT_EQ(model, std::any_cast<libcellml::ModelPtr>(itemInfo.second));
            break;
        case libcellml::CellMLElement::RESET:
        case libcellml::CellMLElement::RESET_VALUE:
        case libcellml::CellMLElement::TEST_VALUE:
            EXPECT_EQ(model->component("component2")->reset(0), std::any_cast<libcellml::ResetPtr>(itemInfo.second));
            break;
        case libcellml::CellMLElement::UNIT:
            EXPECT_EQ(model->units("units2"), std::any_cast<libcellml::UnitItem>(itemInfo.second).first);
            EXPECT_EQ(size_t(0), std::any_cast<libcellml::UnitItem>(itemInfo.second).second);
            break;
        case libcellml::CellMLElement::UNITS:
            EXPECT_EQ(model->units("units1"), std::any_cast<libcellml::UnitsPtr>(itemInfo.second));
            break;
        case libcellml::CellMLElement::VARIABLE:
            EXPECT_EQ(model->component("component2")->variable("variable1"), std::any_cast<libcellml::VariablePtr>(itemInfo.second));
            break;
        case libcellml::CellMLElement::UNDEFINED:
            break;
        }
    }
}

TEST(Annotator, automaticIdsOnEverything)
{
    auto expectedError = "This Annotator object does not have a model to work with.";
    auto annotator = libcellml::Annotator::create();
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(modelStringNoIds);

    auto c2v1 = model->component("component2")->variable("variable1");
    auto c2v2 = model->component("component2")->variable("variable2");
    auto c3v1 = model->component("component3")->variable("variable1");
    auto c3v2 = model->component("component3")->variable("variable2");
    auto c4v1 = model->component("component4")->variable("variable1");

    EXPECT_FALSE(annotator->assignAllIds());
    EXPECT_EQ(size_t(1), annotator->errorCount());
    EXPECT_EQ(expectedError, annotator->error(0)->description());

    annotator->setModel(model);
    EXPECT_TRUE(annotator->assignAllIds());

    EXPECT_EQ("b4da55", model->id());
    EXPECT_EQ("b4da56", model->importSource(0)->id());
    EXPECT_EQ("b4da57", model->importSource(1)->id());
    EXPECT_EQ("b4da58", model->units(0)->id());
    EXPECT_EQ("b4da59", model->units(1)->id());
    EXPECT_EQ("b4da5a", model->units(2)->id());
    EXPECT_EQ("b4da5b", model->units(3)->id());
    EXPECT_EQ("b4da5c", model->units(1)->unitId(0));

    EXPECT_EQ("b4da64", model->component("component2")->id());
    EXPECT_EQ("b4da65", model->component("component2")->component(0)->id());
    EXPECT_EQ("b4da66", model->component("component2")->variable(0)->id());
    EXPECT_EQ("b4da67", model->component("component2")->variable(1)->id());
    EXPECT_EQ("b4da68", model->component("component2")->component(0)->variable(0)->id());
    EXPECT_EQ("b4da69", model->component("component2")->component(0)->variable(1)->id());
    EXPECT_EQ("b4da6a", model->component("component2")->reset(0)->id());
    EXPECT_EQ("b4da6b", model->component("component2")->reset(0)->resetValueId());
    EXPECT_EQ("b4da6c", model->component("component2")->reset(0)->testValueId());
    EXPECT_EQ("b4da6d", libcellml::Variable::equivalenceConnectionId(c2v1, c3v1));
    EXPECT_EQ("b4da61", libcellml::Variable::equivalenceConnectionId(c2v1, c4v1));
    EXPECT_EQ("b4da6e", libcellml::Variable::equivalenceMappingId(c2v1, c3v1));
    EXPECT_EQ("b4da6f", libcellml::Variable::equivalenceMappingId(c2v2, c3v2));
    EXPECT_EQ("b4da70", model->component("component2")->encapsulationId());
    EXPECT_EQ("b4da71", model->component("component3")->encapsulationId());
    EXPECT_EQ("b4da72", model->encapsulationId());
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

    annotator->setModel(model);

    EXPECT_EQ("", model->id());
    EXPECT_EQ("", component1->id());
    EXPECT_EQ("", component2->id());
    EXPECT_EQ("", component3->id());

    annotator->assignIds(libcellml::CellMLElement::COMPONENT);

    EXPECT_TRUE(annotator->hasModel());

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

    annotator->setModel(model);

    EXPECT_EQ("", model->id());
    EXPECT_EQ("", component1->id());
    EXPECT_EQ("", component2->id());
    EXPECT_EQ("", component3->id());
    EXPECT_EQ("", component1->encapsulationId());
    EXPECT_EQ("", component2->encapsulationId());
    EXPECT_EQ("", component3->encapsulationId());

    annotator->assignIds(libcellml::CellMLElement::COMPONENT_REF);
    EXPECT_TRUE(annotator->hasModel());

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

    annotator->setModel(model);

    EXPECT_EQ("", model->id());
    EXPECT_EQ("", component1->id());
    EXPECT_EQ("", component2->id());
    EXPECT_EQ("", variable1->id());
    EXPECT_EQ("", variable2->id());
    EXPECT_EQ("", variable3->id());
    EXPECT_EQ("", variable4->id());
    EXPECT_EQ("", libcellml::Variable::equivalenceConnectionId(variable1, variable3));
    EXPECT_EQ("", libcellml::Variable::equivalenceConnectionId(variable4, variable2));

    annotator->assignIds(libcellml::CellMLElement::CONNECTION);
    EXPECT_TRUE(annotator->hasModel());

    EXPECT_EQ("", model->id());
    EXPECT_EQ("", component1->id());
    EXPECT_EQ("", component2->id());
    EXPECT_EQ("", variable1->id());
    EXPECT_EQ("", variable2->id());
    EXPECT_EQ("", variable3->id());
    EXPECT_EQ("", variable4->id());
    EXPECT_EQ("b4da55", libcellml::Variable::equivalenceConnectionId(variable1, variable3));
    EXPECT_EQ("b4da55", libcellml::Variable::equivalenceConnectionId(variable2, variable4));
}

TEST(Annotator, automaticIdsEncapsulation)
{
    auto annotator = libcellml::Annotator::create();
    auto model = libcellml::Model::create();

    annotator->setModel(model);

    EXPECT_EQ("", model->encapsulationId());
    annotator->assignIds(libcellml::CellMLElement::ENCAPSULATION);
    EXPECT_TRUE(annotator->hasModel());

    EXPECT_EQ("", model->id());
    EXPECT_EQ("b4da55", model->encapsulationId());
}

TEST(Annotator, automaticIdsImportSource)
{
    const std::string in =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
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

    annotator->setModel(model);

    EXPECT_EQ("", model->id());
    EXPECT_EQ("", model->importSource(0)->id());
    EXPECT_EQ("", model->importSource(1)->id());
    EXPECT_EQ("", model->units(0)->id());
    EXPECT_EQ("", model->component(0)->id());

    annotator->assignIds(libcellml::CellMLElement::IMPORT);
    EXPECT_TRUE(annotator->hasModel());

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

    annotator->setModel(model);

    EXPECT_EQ("", model->id());
    EXPECT_EQ("", component1->id());
    EXPECT_EQ("", component2->id());
    EXPECT_EQ("", variable1->id());
    EXPECT_EQ("", variable2->id());
    EXPECT_EQ("", variable3->id());
    EXPECT_EQ("", variable4->id());
    EXPECT_EQ("", libcellml::Variable::equivalenceMappingId(variable1, variable3));
    EXPECT_EQ("", libcellml::Variable::equivalenceMappingId(variable2, variable4));

    annotator->assignIds(libcellml::CellMLElement::MAP_VARIABLES);
    EXPECT_TRUE(annotator->hasModel());

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

    annotator->setModel(model);

    EXPECT_EQ("", model->id());

    annotator->assignIds(libcellml::CellMLElement::MODEL);
    EXPECT_TRUE(annotator->hasModel());

    EXPECT_EQ("b4da55", model->id());
}

TEST(Annotator, automaticIdsNoModel)
{
    const std::string e = "This Annotator object does not have a model to work with.";
    auto annotator = libcellml::Annotator::create();

    annotator->assignIds(libcellml::CellMLElement::MODEL);
    EXPECT_FALSE(annotator->hasModel());

    EXPECT_EQ(size_t(1), annotator->errorCount());
    EXPECT_EQ(e, annotator->error(0)->description());
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

    annotator->setModel(model);

    EXPECT_EQ("", model->id());
    EXPECT_EQ("", component1->id());
    EXPECT_EQ("", component2->id());
    EXPECT_EQ("", component3->id());
    EXPECT_EQ("", reset1->id());
    EXPECT_EQ("", reset2->id());
    EXPECT_EQ("", reset3->id());

    annotator->assignIds(libcellml::CellMLElement::RESET);
    EXPECT_TRUE(annotator->hasModel());

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

    annotator->setModel(model);

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

    annotator->assignIds(libcellml::CellMLElement::RESET_VALUE);
    EXPECT_TRUE(annotator->hasModel());

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

    annotator->setModel(model);

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

    annotator->assignIds(libcellml::CellMLElement::TEST_VALUE);
    EXPECT_TRUE(annotator->hasModel());

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

    annotator->setModel(model);

    EXPECT_EQ("", model->id());
    EXPECT_EQ("", units->id());
    EXPECT_EQ("", units->unitId(0));
    EXPECT_EQ("", units->unitId(1));

    annotator->assignIds(libcellml::CellMLElement::UNIT);
    EXPECT_TRUE(annotator->hasModel());

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

    annotator->setModel(model);

    EXPECT_EQ("", model->id());
    EXPECT_EQ("", units1->id());
    EXPECT_EQ("", units1->unitId(0));
    EXPECT_EQ("", units1->unitId(1));
    EXPECT_EQ("", units2->id());

    annotator->assignIds(libcellml::CellMLElement::UNITS);
    EXPECT_TRUE(annotator->hasModel());

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

    annotator->setModel(model);

    EXPECT_EQ("", model->id());
    EXPECT_EQ("", component1->id());
    EXPECT_EQ("", component2->id());
    EXPECT_EQ("", variable1->id());
    EXPECT_EQ("", variable2->id());
    EXPECT_EQ("", variable3->id());
    EXPECT_EQ("", variable4->id());

    annotator->assignIds(libcellml::CellMLElement::VARIABLE);
    EXPECT_TRUE(annotator->hasModel());

    EXPECT_EQ("", model->id());
    EXPECT_EQ("", component1->id());
    EXPECT_EQ("", component2->id());
    EXPECT_EQ("b4da55", variable1->id());
    EXPECT_EQ("b4da56", variable2->id());
    EXPECT_EQ("b4da57", variable3->id());
    EXPECT_EQ("b4da58", variable4->id());
}

TEST(Annotator, automaticIdsUndefined)
{
    auto annotator = libcellml::Annotator::create();
    auto model = libcellml::Model::create();

    annotator->setModel(model);

    EXPECT_FALSE(annotator->assignIds(libcellml::CellMLElement::UNDEFINED));
    EXPECT_TRUE(annotator->hasModel());
}

TEST(Annotator, automaticIdAllItemsNoId)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(modelStringNoIds);
    auto annotator = libcellml::Annotator::create();
    libcellml::VariablePair p1 = std::make_pair(model->component("component2")->variable("variable1"), model->component("component2")->component("component3")->variable("variable1"));
    libcellml::VariablePair p2 = std::make_pair(model->component("component2")->variable("variable2"), model->component("component2")->component("component3")->variable("variable2"));

    libcellml::UnitItem unit = std::make_pair(model->units(1), 0);

    libcellml::AnyItem itemComponent = std::make_pair(libcellml::CellMLElement::COMPONENT, model->component("component1"));
    libcellml::AnyItem itemComponentRef = std::make_pair(libcellml::CellMLElement::COMPONENT_REF, model->component("component2"));
    libcellml::AnyItem itemConnection = std::make_pair(libcellml::CellMLElement::CONNECTION, p1);
    libcellml::AnyItem itemEncapsulation = std::make_pair(libcellml::CellMLElement::ENCAPSULATION, model);
    libcellml::AnyItem itemImportSource = std::make_pair(libcellml::CellMLElement::IMPORT, model->importSource(0));
    libcellml::AnyItem itemMapVariables = std::make_pair(libcellml::CellMLElement::MAP_VARIABLES, p2);
    libcellml::AnyItem itemModel = std::make_pair(libcellml::CellMLElement::MODEL, model);
    libcellml::AnyItem itemReset = std::make_pair(libcellml::CellMLElement::RESET, model->component("component2")->reset(0));
    libcellml::AnyItem itemResetValue = std::make_pair(libcellml::CellMLElement::RESET_VALUE, model->component("component2")->reset(0));
    libcellml::AnyItem itemTestValue = std::make_pair(libcellml::CellMLElement::TEST_VALUE, model->component("component2")->reset(0));
    libcellml::AnyItem itemUnit = std::make_pair(libcellml::CellMLElement::UNIT, unit);
    libcellml::AnyItem itemUnits = std::make_pair(libcellml::CellMLElement::UNITS, model->units(1));
    libcellml::AnyItem itemVariable = std::make_pair(libcellml::CellMLElement::VARIABLE, model->component("component2")->variable(0));

    annotator->setModel(model);
    EXPECT_TRUE(annotator->hasModel());

    // Expect each have had a change of id.
    EXPECT_EQ("b4da55", annotator->assignId(itemComponent));
    EXPECT_TRUE(annotator->hasModel());
    EXPECT_EQ("b4da56", annotator->assignId(itemComponentRef));
    EXPECT_TRUE(annotator->hasModel());
    EXPECT_EQ("b4da57", annotator->assignId(itemConnection));
    EXPECT_TRUE(annotator->hasModel());
    EXPECT_EQ("b4da58", annotator->assignId(itemImportSource));
    EXPECT_TRUE(annotator->hasModel());
    EXPECT_EQ("b4da59", annotator->assignId(itemMapVariables));
    EXPECT_TRUE(annotator->hasModel());
    EXPECT_EQ("b4da5a", annotator->assignId(itemModel));
    EXPECT_TRUE(annotator->hasModel());
    EXPECT_EQ("b4da5b", annotator->assignId(itemReset));
    EXPECT_TRUE(annotator->hasModel());
    EXPECT_EQ("b4da5c", annotator->assignId(itemResetValue));
    EXPECT_TRUE(annotator->hasModel());
    EXPECT_EQ("b4da5d", annotator->assignId(itemTestValue));
    EXPECT_TRUE(annotator->hasModel());
    EXPECT_EQ("b4da5e", annotator->assignId(itemUnit));
    EXPECT_TRUE(annotator->hasModel());
    EXPECT_EQ("b4da5f", annotator->assignId(itemUnits));
    EXPECT_TRUE(annotator->hasModel());
    EXPECT_EQ("b4da60", annotator->assignId(itemVariable));
    EXPECT_TRUE(annotator->hasModel());
    EXPECT_EQ("b4da61", annotator->assignId(itemEncapsulation));
    EXPECT_TRUE(annotator->hasModel());

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
    libcellml::AnyItem itemConnection2 = std::make_pair(libcellml::CellMLElement::CONNECTION, r1);
    libcellml::AnyItem itemMapVariables2 = std::make_pair(libcellml::CellMLElement::MAP_VARIABLES, r2);
    EXPECT_EQ("b4da62", annotator->assignId(itemConnection2));
    EXPECT_EQ("b4da63", annotator->assignId(itemMapVariables2));

    EXPECT_TRUE(annotator->hasModel());
}

TEST(Annotator, automaticIdResetItemBadInput)
{
    auto annotator = libcellml::Annotator::create();

    libcellml::AnyItem itemReset = std::make_pair(libcellml::CellMLElement::RESET, nullptr);
    EXPECT_EQ("", annotator->assignId(itemReset));
}

TEST(Annotator, assignModelIdBadInput)
{
    auto annotator = libcellml::Annotator::create();
    EXPECT_EQ("", annotator->assignModelId(nullptr));

    libcellml::AnyItem itemModel = std::make_pair(libcellml::CellMLElement::MODEL, libcellml::Variable::create());
    EXPECT_EQ("", annotator->assignId(itemModel));
}

TEST(Annotator, assignVariableIdBadInput)
{
    auto annotator = libcellml::Annotator::create();
    EXPECT_EQ("", annotator->assignVariableId(nullptr));
}

TEST(Annotator, assignComponentIdBadInput)
{
    auto annotator = libcellml::Annotator::create();
    EXPECT_EQ("", annotator->assignComponentId(nullptr));
    EXPECT_EQ("", annotator->assignEncapsulationId(nullptr));
}

TEST(Annotator, assignUnitsIdBadInput)
{
    auto annotator = libcellml::Annotator::create();
    EXPECT_EQ("", annotator->assignUnitsId(nullptr));
}

TEST(Annotator, assignUnitIdBadInput)
{
    auto annotator = libcellml::Annotator::create();
    EXPECT_EQ("", annotator->assignUnitId(std::make_pair(nullptr, 0)));

    EXPECT_EQ("", annotator->assignId(std::make_pair(nullptr, -1)));

    libcellml::AnyItem itemUnit = std::make_pair(libcellml::CellMLElement::UNIT, libcellml::Variable::create());
    EXPECT_EQ("", annotator->assignId(itemUnit));
}

TEST(Annotator, assignResetIdBadInput)
{
    auto annotator = libcellml::Annotator::create();
    EXPECT_EQ("", annotator->assignResetId(nullptr));
    EXPECT_EQ("", annotator->assignResetValueId(nullptr));
    EXPECT_EQ("", annotator->assignTestValueId(nullptr));
}

TEST(Annotator, assignImportSourceIdBadInput)
{
    auto annotator = libcellml::Annotator::create();
    EXPECT_EQ("", annotator->assignImportSourceId(nullptr));

    libcellml::AnyItem itemImportSource = std::make_pair(libcellml::CellMLElement::IMPORT, libcellml::Variable::create());
    EXPECT_EQ("", annotator->assignId(itemImportSource));
}

TEST(Annotator, assignVariablePairIdBadInput)
{
    auto annotator = libcellml::Annotator::create();
    EXPECT_EQ("", annotator->assignConnectionId(std::make_pair(nullptr, nullptr)));

    libcellml::AnyItem itemModel = std::make_pair(libcellml::CellMLElement::MAP_VARIABLES, libcellml::Variable::create());
    EXPECT_EQ("", annotator->assignId(itemModel));
}

TEST(Annotator, assignImportSourceId)
{
    auto annotator = libcellml::Annotator::create();
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(modelStringNoIds);

    auto importSource = model->importSource(0);

    annotator->setModel(model);

    EXPECT_EQ("", importSource->id());

    annotator->assignImportSourceId(importSource);
    EXPECT_EQ("b4da55", importSource->id());
}

TEST(Annotator, assignVariableVariableId)
{
    auto annotator = libcellml::Annotator::create();
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(modelStringNoIds);

    libcellml::VariablePair variablePair = std::make_pair(
        model->component("component2")->variable("variable1"),
        model->component("component2")->variable("variable1")->equivalentVariable(0));

    annotator->setModel(model);

    EXPECT_EQ("", libcellml::Variable::equivalenceConnectionId(variablePair.first, variablePair.second));
    EXPECT_EQ("", libcellml::Variable::equivalenceMappingId(variablePair.first, variablePair.second));

    annotator->assignConnectionId(variablePair);
    EXPECT_EQ("b4da55", libcellml::Variable::equivalenceConnectionId(variablePair.first, variablePair.second));
    annotator->assignMapVariablesId(variablePair);
    EXPECT_EQ("b4da56", libcellml::Variable::equivalenceMappingId(variablePair.first, variablePair.second));
}

TEST(Annotator, assignUnitId)
{
    auto annotator = libcellml::Annotator::create();
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(modelStringNoIds);

    auto units = model->units(1);

    annotator->setModel(model);

    EXPECT_EQ("", units->unitId(1));

    annotator->assignUnitId(std::make_pair(units, 0));
    EXPECT_EQ("b4da55", units->unitId(0));
}

TEST(Annotator, assignComponentId)
{
    auto annotator = libcellml::Annotator::create();
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(modelStringNoIds);

    auto component = model->component(0);

    annotator->setModel(model);

    EXPECT_EQ("", component->id());
    EXPECT_EQ("", component->encapsulationId());

    annotator->assignComponentId(component);
    EXPECT_EQ("b4da55", component->id());
    annotator->assignComponentRefId(component);
    EXPECT_EQ("b4da56", component->encapsulationId());
}

TEST(Annotator, assignModelId)
{
    auto annotator = libcellml::Annotator::create();
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(modelStringNoIds);

    annotator->setModel(model);

    EXPECT_EQ("", model->id());
    EXPECT_EQ("", model->encapsulationId());

    annotator->assignModelId(model);
    EXPECT_EQ("b4da55", model->id());
    annotator->assignEncapsulationId(model);
    EXPECT_EQ("b4da56", model->encapsulationId());
}

TEST(Annotator, assignVariableId)
{
    auto annotator = libcellml::Annotator::create();
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(modelStringNoIds);

    auto variable = model->component(2)->variable(0);

    annotator->setModel(model);

    EXPECT_EQ("", variable->id());

    annotator->assignVariableId(variable);
    EXPECT_EQ("b4da55", variable->id());
}

TEST(Annotator, assignResetId)
{
    auto annotator = libcellml::Annotator::create();
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(modelStringNoIds);

    auto reset = model->component("component2")->reset(0);

    annotator->setModel(model);

    EXPECT_EQ("", reset->id());
    EXPECT_EQ("", reset->testValueId());
    EXPECT_EQ("", reset->resetValueId());

    annotator->assignResetId(reset);
    EXPECT_EQ("b4da55", reset->id());
    annotator->assignTestValueId(reset);
    EXPECT_EQ("b4da56", reset->testValueId());
    annotator->assignResetValueId(reset);
    EXPECT_EQ("b4da57", reset->resetValueId());
}

TEST(Annotator, assignUnitsId)
{
    auto annotator = libcellml::Annotator::create();
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(modelStringNoIds);

    auto units = model->units(0);

    annotator->setModel(model);

    EXPECT_EQ("", units->id());

    annotator->assignUnitsId(units);
    EXPECT_EQ("b4da55", units->id());
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

    libcellml::AnyItem itemComponent = std::make_pair(libcellml::CellMLElement::COMPONENT, model->component(0));
    libcellml::AnyItem itemComponentRef = std::make_pair(libcellml::CellMLElement::COMPONENT_REF, model->component("component2"));
    libcellml::AnyItem itemConnection = std::make_pair(libcellml::CellMLElement::CONNECTION, connection);
    libcellml::AnyItem itemEncapsulation = std::make_pair(libcellml::CellMLElement::ENCAPSULATION, model);
    libcellml::AnyItem itemImportSource = std::make_pair(libcellml::CellMLElement::IMPORT, model->importSource(0));
    libcellml::AnyItem itemMapVariables = std::make_pair(libcellml::CellMLElement::MAP_VARIABLES, mapping);
    libcellml::AnyItem itemModel = std::make_pair(libcellml::CellMLElement::MODEL, model);
    libcellml::AnyItem itemReset = std::make_pair(libcellml::CellMLElement::RESET, model->component("component2")->reset(0));
    libcellml::AnyItem itemResetValue = std::make_pair(libcellml::CellMLElement::RESET_VALUE, model->component("component2")->reset(0));
    libcellml::AnyItem itemTestValue = std::make_pair(libcellml::CellMLElement::TEST_VALUE, model->component("component2")->reset(0));
    libcellml::AnyItem itemUnit = std::make_pair(libcellml::CellMLElement::UNIT, unit);
    libcellml::AnyItem itemUnits = std::make_pair(libcellml::CellMLElement::UNITS, model->units(1));
    libcellml::AnyItem itemVariable = std::make_pair(libcellml::CellMLElement::VARIABLE, model->component("component2")->variable(0));

    annotator->setModel(model);

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

    libcellml::AnyItem itemConnection2 = std::make_pair(libcellml::CellMLElement::CONNECTION, connection2);
    libcellml::AnyItem itemMapVariables2 = std::make_pair(libcellml::CellMLElement::MAP_VARIABLES, mapping2);

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

    libcellml::AnyItem itemComponent = std::make_pair(libcellml::CellMLElement::COMPONENT, model->component(0));
    libcellml::AnyItem itemComponentRef = std::make_pair(libcellml::CellMLElement::COMPONENT_REF, model->component("component2"));
    libcellml::AnyItem itemConnection = std::make_pair(libcellml::CellMLElement::CONNECTION, connection);
    libcellml::AnyItem itemEncapsulation = std::make_pair(libcellml::CellMLElement::ENCAPSULATION, model);
    libcellml::AnyItem itemImportSource = std::make_pair(libcellml::CellMLElement::IMPORT, model->importSource(0));
    libcellml::AnyItem itemMapVariables = std::make_pair(libcellml::CellMLElement::MAP_VARIABLES, mapping);
    libcellml::AnyItem itemModel = std::make_pair(libcellml::CellMLElement::MODEL, model);
    libcellml::AnyItem itemReset = std::make_pair(libcellml::CellMLElement::RESET, model->component("component2")->reset(0));
    libcellml::AnyItem itemResetValue = std::make_pair(libcellml::CellMLElement::RESET_VALUE, model->component("component2")->reset(0));
    libcellml::AnyItem itemTestValue = std::make_pair(libcellml::CellMLElement::TEST_VALUE, model->component("component2")->reset(0));
    libcellml::AnyItem itemUnit = std::make_pair(libcellml::CellMLElement::UNIT, unit);
    libcellml::AnyItem itemUnits = std::make_pair(libcellml::CellMLElement::UNITS, model->units(1));
    libcellml::AnyItem itemVariable = std::make_pair(libcellml::CellMLElement::VARIABLE, model->component("component2")->variable(0));

    annotator->setModel(model);

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

    libcellml::AnyItem itemComponent = std::make_pair(libcellml::CellMLElement::COMPONENT, model->component(0));
    libcellml::AnyItem itemComponentRef = std::make_pair(libcellml::CellMLElement::COMPONENT_REF, model->component("component2"));
    libcellml::AnyItem itemConnection = std::make_pair(libcellml::CellMLElement::CONNECTION, connection);
    libcellml::AnyItem itemEncapsulation = std::make_pair(libcellml::CellMLElement::ENCAPSULATION, model);
    libcellml::AnyItem itemImportSource = std::make_pair(libcellml::CellMLElement::IMPORT, model->importSource(0));
    libcellml::AnyItem itemMapVariables = std::make_pair(libcellml::CellMLElement::MAP_VARIABLES, mapping);
    libcellml::AnyItem itemModel = std::make_pair(libcellml::CellMLElement::MODEL, model);
    libcellml::AnyItem itemReset = std::make_pair(libcellml::CellMLElement::RESET, model->component("component2")->reset(0));
    libcellml::AnyItem itemResetValue = std::make_pair(libcellml::CellMLElement::RESET_VALUE, model->component("component2")->reset(0));
    libcellml::AnyItem itemTestValue = std::make_pair(libcellml::CellMLElement::TEST_VALUE, model->component("component2")->reset(0));
    libcellml::AnyItem itemUnit = std::make_pair(libcellml::CellMLElement::UNIT, unit);
    libcellml::AnyItem itemUnits = std::make_pair(libcellml::CellMLElement::UNITS, model->units(1));
    libcellml::AnyItem itemVariable = std::make_pair(libcellml::CellMLElement::VARIABLE, model->component("component2")->variable(0));

    // Make a different model and build the annotator around that.
    auto model2 = libcellml::Model::create();
    annotator->setModel(model2);

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

TEST(Annotator, issueIdWithModelThatWasDeleted)
{
    libcellml::ModelPtr model;
    auto parser = libcellml::Parser::create();
    model = parser->parseModel(modelStringUniqueIds);
    auto annotator = libcellml::Annotator::create();

    annotator->setModel(model);

    auto component = model->component(0);
    libcellml::AnyItem itemComponent = std::make_pair(libcellml::CellMLElement::COMPONENT, model->component(0));
    EXPECT_EQ("component_1", component->id());

    EXPECT_TRUE(annotator->hasModel());
    model.reset();
    EXPECT_FALSE(annotator->hasModel());

    EXPECT_EQ("", annotator->assignId(itemComponent));
    EXPECT_EQ("component_1", component->id());
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

    annotator->setModel(model);

    // Expect each to change since there were no ids in the first place.
    EXPECT_EQ("b4da55", annotator->assignId(model->component(0)));
    EXPECT_EQ("b4da55", model->component(0)->id());

    EXPECT_EQ("b4da56", annotator->assignId(model->component("component2"), libcellml::CellMLElement::COMPONENT_REF));
    EXPECT_EQ("b4da56", model->component("component2")->encapsulationId());

    EXPECT_EQ("b4da57", annotator->assignId(connection, libcellml::CellMLElement::CONNECTION));
    EXPECT_EQ("b4da57", libcellml::Variable::equivalenceConnectionId(connection.first, connection.second));

    EXPECT_EQ("b4da58", annotator->assignId(model, libcellml::CellMLElement::ENCAPSULATION));
    EXPECT_EQ("b4da58", model->encapsulationId());

    EXPECT_EQ("b4da59", annotator->assignId(model->importSource(0)));
    EXPECT_EQ("b4da59", model->importSource(0)->id());

    EXPECT_EQ("b4da5a", annotator->assignId(mapping));
    EXPECT_EQ("b4da5a", libcellml::Variable::equivalenceMappingId(mapping.first, mapping.second));

    EXPECT_EQ("b4da5b", annotator->assignId(model));
    EXPECT_EQ("b4da5b", model->id());

    EXPECT_EQ("b4da5c", annotator->assignId(model->component("component2")->reset(0)));
    EXPECT_EQ("b4da5c", model->component("component2")->reset(0)->id());

    EXPECT_EQ("b4da5d", annotator->assignId(model->component("component2")->reset(0), libcellml::CellMLElement::RESET_VALUE));
    EXPECT_EQ("b4da5d", model->component("component2")->reset(0)->resetValueId());

    EXPECT_EQ("b4da5e", annotator->assignId(model->component("component2")->reset(0), libcellml::CellMLElement::TEST_VALUE));
    EXPECT_EQ("b4da5e", model->component("component2")->reset(0)->testValueId());

    EXPECT_EQ("b4da5f", annotator->assignId(unit));
    EXPECT_EQ("b4da5f", model->units(1)->unitId(0));

    EXPECT_EQ("b4da60", annotator->assignId(model->units(1)));
    EXPECT_EQ("b4da60", model->units(1)->id());

    EXPECT_EQ("b4da61", annotator->assignId(model->component("component2")->variable(0)));
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

    EXPECT_EQ("b4da62", annotator->assignId(connection2, libcellml::CellMLElement::CONNECTION));
    EXPECT_EQ("b4da62", libcellml::Variable::equivalenceConnectionId(connection2.first, connection2.second));

    EXPECT_EQ("b4da63", annotator->assignId(mapping2, libcellml::CellMLElement::MAP_VARIABLES));
    EXPECT_EQ("b4da63", libcellml::Variable::equivalenceMappingId(mapping2.first, mapping2.second));
}

TEST(Annotator, assignAllIdsBlankModel)
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

TEST(Annotator, assignAllIdsNonblankModel)
{
    auto parser = libcellml::Parser::create();
    auto printer = libcellml::Printer::create();
    auto model = parser->parseModel(modelStringUniqueIds);
    auto annotator = libcellml::Annotator::create();

    annotator->assignAllIds(model);
    EXPECT_EQ(size_t(0), annotator->errorCount());
    EXPECT_EQ(modelStringUniqueIds, printer->printModel(model));
}

TEST(Annotator, clearAllIdsNoModelPresent)
{
    std::vector<std::string> expectedErrors = {
        "This Annotator object does not have a model to work with.",
    };

    auto annotator = libcellml::Annotator::create();

    annotator->clearAllIds();
    EXPECT_EQ(size_t(1), annotator->errorCount());
    EXPECT_EQ(expectedErrors[0], annotator->error(0)->description());
}

TEST(Annotator, clearAllIdsNullModelPresent)
{
    std::vector<std::string> expectedErrors = {
        "This Annotator object does not have a model to work with.",
    };

    auto annotator = libcellml::Annotator::create();

    libcellml::ModelPtr nullModel;
    annotator->clearAllIds(nullModel);
    EXPECT_EQ(size_t(1), annotator->errorCount());
    EXPECT_EQ(expectedErrors[0], annotator->error(0)->description());
}

TEST(Annotator, clearAllIdsModelPresent)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(modelStringDuplicateIds);
    auto annotator = libcellml::Annotator::create();

    annotator->clearAllIds(model);
    EXPECT_EQ(size_t(0), annotator->errorCount());

    libcellml::AnyItem item = annotator->item("duplicateId");
    EXPECT_EQ(libcellml::CellMLElement::UNDEFINED, item.first);
}

TEST(Annotator, assignIdInvalidType)
{
    const std::string e = "The given type 'reset' is invalid for this method.";

    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(modelStringNoIds);
    auto annotator = libcellml::Annotator::create();

    annotator->assignId(model, libcellml::CellMLElement::RESET);
    EXPECT_EQ(size_t(1), annotator->errorCount());
    EXPECT_EQ(e, annotator->error(0)->description());
}

TEST(Annotator, listDuplicateIds)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(modelStringLotsOfDuplicateIds);
    auto annotator = libcellml::Annotator::create();
    std::vector<std::string> expectedIds = {
        "duplicateId1",
        "duplicateId2",
        "duplicateId3",
        "duplicateId4",
    };

    annotator->setModel(model);
    auto ids = annotator->duplicateIds();
    EXPECT_EQ(expectedIds, ids);

    // Repeat with no duplicates and verify that none are returned.
    model = parser->parseModel(modelStringUniqueIds);
    annotator->setModel(model);
    ids = annotator->duplicateIds();
    EXPECT_EQ(std::vector<std::string>(), ids);
}

TEST(Annotator, listAllIds)
{
    std::vector<std::string> uniqueIds = {
        "component_1",
        "component_2",
        "component_3",
        "component_ref_1",
        "component_ref_2",
        "connection_1",
        "encapsulation_1",
        "import_1",
        "import_2",
        "map_variables_1",
        "map_variables_2",
        "model_1",
        "reset_1",
        "reset_value_1",
        "test_value_1",
        "unit_1",
        "units_1",
        "units_2",
        "units_3",
        "units_4",
        "variable_1",
        "variable_2",
        "variable_3",
        "variable_4",
    };
    std::vector<std::string> duplicatedIds = {
        "duplicateId1",
        "duplicateId2",
        "duplicateId3",
        "duplicateId4",
    };
    auto parser = libcellml::Parser::create();

    auto model1 = parser->parseModel(modelStringLotsOfDuplicateIds);
    auto annotator = libcellml::Annotator::create();
    annotator->setModel(model1);
    auto ids = annotator->ids();
    EXPECT_EQ(duplicatedIds, ids);

    auto model2 = parser->parseModel(modelStringUniqueIds);
    annotator->setModel(model2);
    ids = annotator->ids();
    EXPECT_EQ(uniqueIds, ids);

    auto model3 = parser->parseModel(modelStringNoIds);
    annotator->setModel(model3);
    ids = annotator->ids();
    EXPECT_EQ(std::vector<std::string>(), ids);
}

TEST(Annotator, retrieveDuplicateIdItemLists)
{
    std::vector<std::string> ids = {
        "duplicateId1",
        "duplicateId2",
        "duplicateId3",
        "duplicateId4",
    };

    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(modelStringLotsOfDuplicateIds);

    auto c2v1 = model->component("component2")->variable("variable1");
    auto c2v2 = model->component("component2")->variable("variable2");
    auto c3v1 = model->component("component2")->component("component3")->variable("variable1");
    auto c4v1 = model->component("component4")->variable("variable1");
    auto c4v2 = model->component("component4")->variable("variable2");

    std::map<std::string, std::vector<libcellml::AnyItem>> expectedItems = {
        {"duplicateId1", {
                             std::make_pair(libcellml::CellMLElement::UNITS, std::any(model->units("units2"))),
                             std::make_pair(libcellml::CellMLElement::IMPORT, std::any(model->importSource(0))),
                             std::make_pair(libcellml::CellMLElement::MAP_VARIABLES, std::any(libcellml::VariablePair(c4v1, c2v1))),
                             std::make_pair(libcellml::CellMLElement::COMPONENT, std::any(model->component("component2"))),
                             std::make_pair(libcellml::CellMLElement::CONNECTION, std::any(libcellml::VariablePair(c2v1, c3v1))),
                             std::make_pair(libcellml::CellMLElement::TEST_VALUE, std::any(model->component("component2")->reset(0))),
                             std::make_pair(libcellml::CellMLElement::COMPONENT_REF, std::any(model->component("component2")->component("component3"))),
                             std::make_pair(libcellml::CellMLElement::VARIABLE, std::any(model->component("component2")->component("component3")->variable("variable2"))),
                         }},
        {"duplicateId2", {
                             std::make_pair(libcellml::CellMLElement::MODEL, std::any(model)),
                             std::make_pair(libcellml::CellMLElement::UNITS, std::any(model->units("units1"))),
                             std::make_pair(libcellml::CellMLElement::UNITS, std::any(model->units("blob"))),
                             std::make_pair(libcellml::CellMLElement::CONNECTION, std::any(libcellml::VariablePair(c4v2, c2v2))),
                             std::make_pair(libcellml::CellMLElement::VARIABLE, std::any(c4v2)),
                             std::make_pair(libcellml::CellMLElement::COMPONENT_REF, std::any(model->component("component2"))),
                             std::make_pair(libcellml::CellMLElement::RESET, std::any(model->component("component2")->reset(0))),
                             std::make_pair(libcellml::CellMLElement::VARIABLE, std::any(c3v1)),
                         }},
        {"duplicateId3", {
                             std::make_pair(libcellml::CellMLElement::IMPORT, std::any(model->importSource(1))),
                             std::make_pair(libcellml::CellMLElement::UNITS, std::any(model->units("units3"))),
                             std::make_pair(libcellml::CellMLElement::VARIABLE, std::any(c4v1)),
                             std::make_pair(libcellml::CellMLElement::VARIABLE, std::any(c2v2)),
                             std::make_pair(libcellml::CellMLElement::MAP_VARIABLES, std::any(libcellml::VariablePair(c2v2, c4v2))),
                             std::make_pair(libcellml::CellMLElement::COMPONENT, std::any(model->component("component2")->component("component3"))),
                             std::make_pair(libcellml::CellMLElement::ENCAPSULATION, std::any(model)),
                         }},
        {"duplicateId4", {
                             std::make_pair(libcellml::CellMLElement::UNIT, std::any(libcellml::UnitItem(std::make_pair(model->units("units2"), 0)))),
                             std::make_pair(libcellml::CellMLElement::COMPONENT, std::any(model->component("component1"))),
                             std::make_pair(libcellml::CellMLElement::COMPONENT, std::any(model->component("component4"))),
                             std::make_pair(libcellml::CellMLElement::MAP_VARIABLES, std::any(libcellml::VariablePair(c2v1, c3v1))),
                             std::make_pair(libcellml::CellMLElement::VARIABLE, std::any(c2v1)),
                             std::make_pair(libcellml::CellMLElement::MAP_VARIABLES, std::any(libcellml::VariablePair(c2v2, c4v2))),
                             std::make_pair(libcellml::CellMLElement::RESET_VALUE, std::any(model->component("component2")->reset(0))),
                         }},

    };

    libcellml::VariablePair testPair;

    auto annotator = libcellml::Annotator::create();
    annotator->setModel(model);

    EXPECT_EQ(ids, annotator->duplicateIds());

    for (const auto &id : ids) {
        std::vector<libcellml::AnyItem> items = annotator->items(id);
        size_t index = 0;

        for (const auto &item : items) {
            EXPECT_EQ(expectedItems[id][index].first, item.first);
            switch (item.first) {
            case libcellml::CellMLElement::COMPONENT:
            case libcellml::CellMLElement::COMPONENT_REF:
                EXPECT_EQ(std::any_cast<libcellml::ComponentPtr>(expectedItems[id][index].second), std::any_cast<libcellml::ComponentPtr>(item.second));
                break;
            case libcellml::CellMLElement::CONNECTION:
                // A bit of a nonsense test because 'variable1' and 'variable2' are the only variables in this particular model.
                testPair = std::any_cast<libcellml::VariablePair>(item.second);
                EXPECT_TRUE("variable1" == testPair.first->name() || "variable2" == testPair.first->name());
                EXPECT_TRUE("variable1" == testPair.second->name() || "variable2" == testPair.second->name());
                break;
            case libcellml::CellMLElement::MAP_VARIABLES:
                testPair = std::any_cast<libcellml::VariablePair>(item.second);
                if (id == "duplicateId1") {
                    EXPECT_EQ("variable1", testPair.first->name());
                    EXPECT_EQ("variable1", testPair.second->name());
                } else if (id == "duplicateId3") {
                    EXPECT_EQ("variable2", testPair.first->name());
                    EXPECT_EQ("variable2", testPair.second->name());
                } else if (id == "duplicateId4") {
                    if (testPair.first->name() == "variable1") {
                        EXPECT_EQ("variable1", testPair.first->name());
                        EXPECT_EQ("variable1", testPair.second->name());
                    } else {
                        EXPECT_EQ("variable2", testPair.first->name());
                        EXPECT_EQ("variable2", testPair.second->name());
                    }
                }
                break;
            case libcellml::CellMLElement::ENCAPSULATION:
                EXPECT_EQ(std::any_cast<libcellml::ModelPtr>(expectedItems[id][index].second), std::any_cast<libcellml::ModelPtr>(item.second));
                break;
            case libcellml::CellMLElement::IMPORT:
                EXPECT_EQ(std::any_cast<libcellml::ImportSourcePtr>(expectedItems[id][index].second), std::any_cast<libcellml::ImportSourcePtr>(item.second));
                break;
            case libcellml::CellMLElement::MODEL:
                EXPECT_EQ(std::any_cast<libcellml::ModelPtr>(expectedItems[id][index].second), std::any_cast<libcellml::ModelPtr>(item.second));
                break;
            case libcellml::CellMLElement::RESET:
            case libcellml::CellMLElement::RESET_VALUE:
            case libcellml::CellMLElement::TEST_VALUE:
                EXPECT_EQ(std::any_cast<libcellml::ResetPtr>(expectedItems[id][index].second), std::any_cast<libcellml::ResetPtr>(item.second));
                break;
            case libcellml::CellMLElement::UNIT:
                EXPECT_EQ(std::any_cast<libcellml::UnitItem>(expectedItems[id][index].second), std::any_cast<libcellml::UnitItem>(item.second));
                break;
            case libcellml::CellMLElement::UNITS:
                EXPECT_EQ(std::any_cast<libcellml::UnitsPtr>(expectedItems[id][index].second), std::any_cast<libcellml::UnitsPtr>(item.second));
                break;
            case libcellml::CellMLElement::VARIABLE:
                EXPECT_EQ(std::any_cast<libcellml::VariablePtr>(expectedItems[id][index].second), std::any_cast<libcellml::VariablePtr>(item.second));
                break;
            case libcellml::CellMLElement::MATHML:
            case libcellml::CellMLElement::UNDEFINED:
                break;
            }
            ++index;
        }
    }
}

TEST(Annotator, retrieveDuplicateIdItemsWithIndex)
{
    std::vector<std::string> ids = {
        "duplicateId1",
        "duplicateId2",
        "duplicateId3",
        "duplicateId4",
    };

    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(modelStringLotsOfDuplicateIds);

    auto c2v1 = model->component("component2")->variable("variable1");
    auto c2v2 = model->component("component2")->variable("variable2");
    auto c3v1 = model->component("component2")->component("component3")->variable("variable1");
    auto c4v1 = model->component("component4")->variable("variable1");
    auto c4v2 = model->component("component4")->variable("variable2");

    std::map<std::string, std::vector<libcellml::AnyItem>> expectedItems = {
        {"duplicateId1", {
                             std::make_pair(libcellml::CellMLElement::UNITS, std::any(model->units("units2"))),
                             std::make_pair(libcellml::CellMLElement::IMPORT, std::any(model->importSource(0))),
                             std::make_pair(libcellml::CellMLElement::MAP_VARIABLES, std::any(libcellml::VariablePair(c4v1, c2v1))),
                             std::make_pair(libcellml::CellMLElement::COMPONENT, std::any(model->component("component2"))),
                             std::make_pair(libcellml::CellMLElement::CONNECTION, std::any(libcellml::VariablePair(c2v1, c3v1))),
                             std::make_pair(libcellml::CellMLElement::TEST_VALUE, std::any(model->component("component2")->reset(0))),
                             std::make_pair(libcellml::CellMLElement::COMPONENT_REF, std::any(model->component("component2")->component("component3"))),
                             std::make_pair(libcellml::CellMLElement::VARIABLE, std::any(model->component("component2")->component("component3")->variable("variable2"))),
                         }},
        {"duplicateId2", {
                             std::make_pair(libcellml::CellMLElement::MODEL, std::any(model)),
                             std::make_pair(libcellml::CellMLElement::UNITS, std::any(model->units("units1"))),
                             std::make_pair(libcellml::CellMLElement::UNITS, std::any(model->units("blob"))),
                             std::make_pair(libcellml::CellMLElement::CONNECTION, std::any(libcellml::VariablePair(c4v2, c2v2))),
                             std::make_pair(libcellml::CellMLElement::VARIABLE, std::any(c4v2)),
                             std::make_pair(libcellml::CellMLElement::COMPONENT_REF, std::any(model->component("component2"))),
                             std::make_pair(libcellml::CellMLElement::RESET, std::any(model->component("component2")->reset(0))),
                             std::make_pair(libcellml::CellMLElement::VARIABLE, std::any(c3v1)),
                         }},
        {"duplicateId3", {
                             std::make_pair(libcellml::CellMLElement::IMPORT, std::any(model->importSource(1))),
                             std::make_pair(libcellml::CellMLElement::UNITS, std::any(model->units("units3"))),
                             std::make_pair(libcellml::CellMLElement::VARIABLE, std::any(c4v1)),
                             std::make_pair(libcellml::CellMLElement::VARIABLE, std::any(c2v2)),
                             std::make_pair(libcellml::CellMLElement::MAP_VARIABLES, std::any(libcellml::VariablePair(c2v2, c4v2))),
                             std::make_pair(libcellml::CellMLElement::COMPONENT, std::any(model->component("component2")->component("component3"))),
                             std::make_pair(libcellml::CellMLElement::ENCAPSULATION, std::any(model)),
                         }},
        {"duplicateId4", {
                             std::make_pair(libcellml::CellMLElement::UNIT, std::any(libcellml::UnitItem(std::make_pair(model->units("units2"), 0)))),
                             std::make_pair(libcellml::CellMLElement::COMPONENT, std::any(model->component("component1"))),
                             std::make_pair(libcellml::CellMLElement::COMPONENT, std::any(model->component("component4"))),
                             std::make_pair(libcellml::CellMLElement::MAP_VARIABLES, std::any(libcellml::VariablePair(c2v1, c3v1))),
                             std::make_pair(libcellml::CellMLElement::VARIABLE, std::any(c2v1)),
                             std::make_pair(libcellml::CellMLElement::MAP_VARIABLES, std::any(libcellml::VariablePair(c2v2, c4v2))),
                             std::make_pair(libcellml::CellMLElement::RESET_VALUE, std::any(model->component("component2")->reset(0))),
                         }},

    };

    libcellml::VariablePair pair;
    libcellml::VariablePair testPair;

    auto annotator = libcellml::Annotator::create();
    annotator->setModel(model);

    EXPECT_EQ(ids, annotator->duplicateIds());

    for (const auto &id : ids) {
        auto num = annotator->duplicateCount(id);
        for (size_t index = 0; index < num; ++index) {
            libcellml::AnyItem item = annotator->item(id, index);

            EXPECT_EQ(expectedItems[id][index].first, item.first);

            switch (item.first) {
            case libcellml::CellMLElement::COMPONENT:
            case libcellml::CellMLElement::COMPONENT_REF:
                EXPECT_EQ(std::any_cast<libcellml::ComponentPtr>(expectedItems[id][index].second), std::any_cast<libcellml::ComponentPtr>(item.second));
                break;
            case libcellml::CellMLElement::CONNECTION:
            case libcellml::CellMLElement::MAP_VARIABLES:
                pair = std::any_cast<libcellml::VariablePair>(expectedItems[id][index].second);
                testPair = std::any_cast<libcellml::VariablePair>(item.second);
                break;
            case libcellml::CellMLElement::ENCAPSULATION:
                EXPECT_EQ(std::any_cast<libcellml::ModelPtr>(expectedItems[id][index].second), std::any_cast<libcellml::ModelPtr>(item.second));
                break;
            case libcellml::CellMLElement::IMPORT:
                EXPECT_EQ(std::any_cast<libcellml::ImportSourcePtr>(expectedItems[id][index].second), std::any_cast<libcellml::ImportSourcePtr>(item.second));
                break;
            case libcellml::CellMLElement::MODEL:
                EXPECT_EQ(std::any_cast<libcellml::ModelPtr>(expectedItems[id][index].second), std::any_cast<libcellml::ModelPtr>(item.second));
                break;
            case libcellml::CellMLElement::RESET:
            case libcellml::CellMLElement::RESET_VALUE:
            case libcellml::CellMLElement::TEST_VALUE:
                EXPECT_EQ(std::any_cast<libcellml::ResetPtr>(expectedItems[id][index].second), std::any_cast<libcellml::ResetPtr>(item.second));
                break;
            case libcellml::CellMLElement::UNIT:
                EXPECT_EQ(std::any_cast<libcellml::UnitItem>(expectedItems[id][index].second), std::any_cast<libcellml::UnitItem>(item.second));
                break;
            case libcellml::CellMLElement::UNITS:
                EXPECT_EQ(std::any_cast<libcellml::UnitsPtr>(expectedItems[id][index].second), std::any_cast<libcellml::UnitsPtr>(item.second));
                break;
            case libcellml::CellMLElement::VARIABLE:
                EXPECT_EQ(std::any_cast<libcellml::VariablePtr>(expectedItems[id][index].second), std::any_cast<libcellml::VariablePtr>(item.second));
                break;
            case libcellml::CellMLElement::MATHML:
            case libcellml::CellMLElement::UNDEFINED:
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
    annotator->setModel(m);

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
    // This test is to provide coverage for those rather than to demonstrate functionality.

    auto parser = libcellml::Parser::create();
    auto annotator = libcellml::Annotator::create();
    auto model = parser->parseModel(modelStringNoIds);

    // Expect failure as no model is built.
    EXPECT_EQ("", annotator->assignId(model->units("units2"), 0));
    EXPECT_EQ("", annotator->assignId(model->component("component2")->variable("variable1"), model->component("component3")->variable("variable1"), libcellml::CellMLElement::CONNECTION));
    EXPECT_EQ("", annotator->assignId(model->component("component2")->variable("variable1"), model->component("component3")->variable("variable1"), libcellml::CellMLElement::MAP_VARIABLES));

    annotator->setModel(model);

    // Expect success.
    EXPECT_EQ("b4da55", annotator->assignId(model->units("units2"), 0));
    EXPECT_EQ("b4da56", annotator->assignId(model->component("component2")->variable("variable1"), model->component("component3")->variable("variable1"), libcellml::CellMLElement::CONNECTION));
    EXPECT_EQ("b4da57", annotator->assignId(model->component("component2")->variable("variable1"), model->component("component3")->variable("variable1"), libcellml::CellMLElement::MAP_VARIABLES));
}

TEST(Annotator, assignIdInvalidArguments)
{
    const std::vector<std::string> expectedIssues = {
        "The given type 'undefined' is invalid for this method.",
        "The given type 'variable' is invalid for this method.",
        "The given type 'component' is invalid for this method.",
        "The given type 'units' is invalid for this method.",
    };
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(modelStringUniqueIds);
    auto annotator = libcellml::Annotator::create();

    EXPECT_EQ("", annotator->assignId(model->component("component2"), libcellml::CellMLElement::UNDEFINED));
    EXPECT_EQ(size_t(1), annotator->errorCount());
    EXPECT_EQ(expectedIssues[0], annotator->error(0)->description());

    EXPECT_EQ("", annotator->assignId(model->component("component2")->reset(0), libcellml::CellMLElement::VARIABLE));
    EXPECT_EQ(size_t(2), annotator->errorCount());
    EXPECT_EQ(expectedIssues[1], annotator->error(1)->description());

    libcellml::VariablePair connection = std::make_pair(
        model->component("component2")->variable("variable1"),
        model->component("component2")->variable("variable1")->equivalentVariable(0));

    EXPECT_EQ("", annotator->assignId(connection, libcellml::CellMLElement::COMPONENT));
    EXPECT_EQ(size_t(3), annotator->errorCount());
    EXPECT_EQ(expectedIssues[2], annotator->error(2)->description());

    EXPECT_EQ("", annotator->assignId(model->component("component2")->variable("variable1"), model->component("component2")->variable("variable1")->equivalentVariable(0), libcellml::CellMLElement::UNITS));
    EXPECT_EQ(size_t(4), annotator->errorCount());
    EXPECT_EQ(expectedIssues[3], annotator->error(3)->description());
}

TEST(Annotator, hashChangesAndUpdates)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(modelStringUniqueIds);
    auto annotator = libcellml::Annotator::create();

    EXPECT_FALSE(annotator->hasModel());

    // Model is set and the id map is not created.
    annotator->setModel(model);

    // Can set id manually, this does not trigger a rebuild of the id map.
    model->setId("iHaveChanged");

    // The id map is built when a query is made.
    EXPECT_EQ(nullptr, annotator->model("model_1"));

    // Can set id automatically, this does not trigger a rebuild of the id map.
    EXPECT_EQ("b4da55", annotator->assignId(model->component(0)));

    EXPECT_NE(nullptr, annotator->encapsulation("encapsulation_1"));
}

TEST(Annotator, hashUpdatedWithAllAutomaticIds)
{
    // Expect that using the annotator functionality to set automatic ids will
    // not make the build hash out of date.
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(modelStringUniqueIds);
    auto annotator = libcellml::Annotator::create();

    annotator->setModel(model);
    EXPECT_TRUE(annotator->hasModel());

    annotator->assignAllIds();
    EXPECT_TRUE(annotator->hasModel());
}

TEST(Annotator, autoIdOnOutOfDateBuild)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(modelStringUniqueIds);
    auto annotator = libcellml::Annotator::create();

    annotator->setModel(model);

    model->component(0)->setId("changed");
    EXPECT_EQ("changed", model->component(0)->id());
    EXPECT_EQ("b4da55", annotator->assignId(model->component(0), libcellml::CellMLElement::COMPONENT));
    EXPECT_EQ("b4da55", model->component(0)->id());

    model->component("component2")->setEncapsulationId("changed");
    EXPECT_EQ("changed", model->component("component2")->encapsulationId());
    EXPECT_EQ("b4da56", annotator->assignId(model->component("component2"), libcellml::CellMLElement::COMPONENT_REF));
    EXPECT_EQ("b4da56", model->component("component2")->encapsulationId());

    libcellml::VariablePair connection = std::make_pair(
        model->component("component2")->variable("variable1"),
        model->component("component2")->variable("variable1")->equivalentVariable(0));
    libcellml::Variable::setEquivalenceConnectionId(connection.first, connection.second, "changed");
    EXPECT_EQ("changed", libcellml::Variable::equivalenceConnectionId(connection.first, connection.second));
    EXPECT_EQ("b4da57", annotator->assignId(connection, libcellml::CellMLElement::CONNECTION));
    EXPECT_EQ("b4da57", libcellml::Variable::equivalenceConnectionId(connection.first, connection.second));

    model->setEncapsulationId("changed");
    EXPECT_EQ("changed", model->encapsulationId());
    EXPECT_EQ("b4da58", annotator->assignId(model, libcellml::CellMLElement::ENCAPSULATION));
    EXPECT_EQ("b4da58", model->encapsulationId());

    model->importSource(0)->setId("changed");
    EXPECT_EQ("changed", model->importSource(0)->id());
    EXPECT_EQ("b4da59", annotator->assignId(model->importSource(0)));
    EXPECT_EQ("b4da59", model->importSource(0)->id());

    libcellml::VariablePair mapping = std::make_pair(
        model->component("component2")->variable("variable2"),
        model->component("component2")->variable("variable2")->equivalentVariable(0));
    libcellml::Variable::setEquivalenceMappingId(mapping.first, mapping.second, "changed");
    EXPECT_EQ("changed", libcellml::Variable::equivalenceMappingId(mapping.first, mapping.second));
    EXPECT_EQ("b4da5a", annotator->assignId(mapping, libcellml::CellMLElement::MAP_VARIABLES));
    EXPECT_EQ("b4da5a", libcellml::Variable::equivalenceMappingId(mapping.first, mapping.second));

    model->setId("changed");
    EXPECT_EQ("changed", model->id());
    EXPECT_EQ("b4da5b", annotator->assignId(model));
    EXPECT_EQ("b4da5b", model->id());

    model->component("component2")->reset(0)->setId("changed");
    EXPECT_EQ("changed", model->component("component2")->reset(0)->id());
    EXPECT_EQ("b4da5c", annotator->assignId(model->component("component2")->reset(0), libcellml::CellMLElement::RESET));
    EXPECT_EQ("b4da5c", model->component("component2")->reset(0)->id());

    model->component("component2")->reset(0)->setResetValueId("changed");
    EXPECT_EQ("changed", model->component("component2")->reset(0)->resetValueId());
    EXPECT_EQ("b4da5d", annotator->assignId(model->component("component2")->reset(0), libcellml::CellMLElement::RESET_VALUE));
    EXPECT_EQ("b4da5d", model->component("component2")->reset(0)->resetValueId());

    model->component("component2")->reset(0)->setTestValueId("changed");
    EXPECT_EQ("changed", model->component("component2")->reset(0)->testValueId());
    EXPECT_EQ("b4da5e", annotator->assignId(model->component("component2")->reset(0), libcellml::CellMLElement::TEST_VALUE));
    EXPECT_EQ("b4da5e", model->component("component2")->reset(0)->testValueId());

    libcellml::UnitItem unit = std::make_pair(model->units(1), 0);
    model->units(1)->setUnitId(0, "changed");
    EXPECT_EQ("changed", model->units(1)->unitId(0));
    EXPECT_EQ("b4da5f", annotator->assignId(unit));
    EXPECT_EQ("b4da5f", model->units(1)->unitId(0));

    model->units(1)->setId("changed");
    EXPECT_EQ("changed", model->units(1)->id());
    EXPECT_EQ("b4da60", annotator->assignId(model->units(1)));
    EXPECT_EQ("b4da60", model->units(1)->id());

    model->component("component2")->variable(0)->setId("changed");
    EXPECT_EQ("changed", model->component("component2")->variable(0)->id());
    EXPECT_EQ("b4da61", annotator->assignId(model->component("component2")->variable(0)));
    EXPECT_EQ("b4da61", model->component("component2")->variable(0)->id());
}

TEST(Annotator, retrieveItemByIndex)
{
    auto annotator = libcellml::Annotator::create();
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(modelStringLotsOfDuplicateIds);

    annotator->setModel(model);

    EXPECT_EQ(nullptr, annotator->component("duplicateId4", 5));
    EXPECT_EQ("component1", annotator->component("duplicateId4", 1)->name());
    EXPECT_EQ("component4", annotator->component("duplicateId4", 2)->name());
}

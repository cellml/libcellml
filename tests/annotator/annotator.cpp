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

    EXPECT_EQ(libcellml::Annotator::TYPE::MODEL, annotator->item("model_id").first);
    EXPECT_EQ(model, std::any_cast<libcellml::ModelPtr>(annotator->item("model_id").second));
    EXPECT_EQ(libcellml::Annotator::TYPE::COMPONENT, annotator->item("component_id").first);
    EXPECT_EQ(component, std::any_cast<libcellml::ComponentPtr>(annotator->item("component_id").second));
    EXPECT_EQ(libcellml::Annotator::TYPE::VARIABLE, annotator->item("variable_id").first);
    EXPECT_EQ(variable, std::any_cast<libcellml::VariablePtr>(annotator->item("variable_id").second));
    EXPECT_EQ(libcellml::Annotator::TYPE::RESET, annotator->item("reset_id").first);
    EXPECT_EQ(reset, std::any_cast<libcellml::ResetPtr>(annotator->item("reset_id").second));
    EXPECT_EQ(libcellml::Annotator::TYPE::UNITS, annotator->item("units_id").first);
    EXPECT_EQ(units, std::any_cast<libcellml::UnitsPtr>(annotator->item("units_id").second));
    EXPECT_EQ(libcellml::Annotator::TYPE::IMPORT, annotator->item("import_id").first);
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
    EXPECT_EQ(libcellml::Annotator::TYPE::UNIT, annotator->item("unit1_id").first);
    EXPECT_EQ(units, std::any_cast<libcellml::UnitItem>(annotator->item("unit1_id").second).first);
    EXPECT_EQ(size_t(0), std::any_cast<libcellml::UnitItem>(annotator->item("unit1_id").second).second);
    EXPECT_EQ(libcellml::Annotator::TYPE::UNIT, annotator->item("unit2_id").first);
    EXPECT_EQ(units, std::any_cast<libcellml::UnitItem>(annotator->item("unit2_id").second).first);
    EXPECT_EQ(size_t(1), std::any_cast<libcellml::UnitItem>(annotator->item("unit2_id").second).second);
    EXPECT_EQ(libcellml::Annotator::TYPE::UNIT, annotator->item("unit3_id").first);
    EXPECT_EQ(units, std::any_cast<libcellml::UnitItem>(annotator->item("unit3_id").second).first);
    EXPECT_EQ(size_t(2), std::any_cast<libcellml::UnitItem>(annotator->item("unit3_id").second).second);

    // Connections and map variables are returned as VariablePairs.  Note that connection ids could be
    // represented by any one of the pairs of variables in that connection.
    EXPECT_EQ(libcellml::Annotator::TYPE::MAP_VARIABLES, annotator->item("map_id").first);
    EXPECT_EQ(v1v2, std::any_cast<libcellml::VariablePair>(annotator->item("map_id").second));
    EXPECT_EQ(libcellml::Annotator::TYPE::CONNECTION, annotator->item("connection_id").first);
    EXPECT_TRUE((v1v2 == std::any_cast<libcellml::VariablePair>(annotator->item("connection_id").second) || (v3v4 == std::any_cast<libcellml::VariablePair>(annotator->item("connection_id").second))));

    // Component refs are returned as name string and ComponentPtr:
    EXPECT_EQ(libcellml::Annotator::TYPE::COMPONENT_REF, annotator->item("component_ref1_id").first);
    EXPECT_EQ(c1, std::any_cast<libcellml::ComponentPtr>(annotator->item("component_ref1_id").second));

    // Encapsulation is returned as name string and empty string:
    EXPECT_EQ(libcellml::Annotator::TYPE::ENCAPSULATION, annotator->item("encapsulation_id").first);
    EXPECT_EQ("", std::any_cast<std::string>(annotator->item("encapsulation_id").second));

    // Reset children are returned as name string and reset pointer:
    EXPECT_EQ(libcellml::Annotator::TYPE::RESET_VALUE, annotator->item("reset_value_id").first);
    EXPECT_EQ(reset, std::any_cast<libcellml::ResetPtr>(annotator->item("reset_value_id").second));
    EXPECT_EQ(libcellml::Annotator::TYPE::TEST_VALUE, annotator->item("test_value_id").first);
    EXPECT_EQ(reset, std::any_cast<libcellml::ResetPtr>(annotator->item("test_value_id").second));
}

TEST(Annotator, errorHandling)
{
    auto model = libcellml::Model::create("model");

    auto annotator = libcellml::Annotator::create();

    // Searching before the map is built should return an error.
    EXPECT_EQ(libcellml::Annotator::TYPE::ISSUE, annotator->item("i_dont_exist").first);
    EXPECT_EQ(size_t(1), annotator->issueCount());
    EXPECT_EQ(annotator->issue(0)->description(), "Please call the Annotator::build function before attempting to access items by their id.");

    // Building an empty model will result in an empty map and return an error.
    annotator->build(model);
    EXPECT_EQ(libcellml::Annotator::TYPE::ISSUE, annotator->item("i_dont_exist").first);
    EXPECT_EQ(size_t(1), annotator->issueCount());
    EXPECT_EQ(annotator->issue(0)->description(), "The id map is empty; the supplied model has no id attributes.");

    model->setId("model_id"); // Add an id into the model and rebuild.
    annotator->build(model);

    // Test that an Issue is created and logged when an id is not found:
    EXPECT_EQ(libcellml::Annotator::TYPE::ISSUE, annotator->item("i_dont_exist").first);
    EXPECT_EQ(size_t(1), annotator->issueCount());
    EXPECT_EQ(annotator->issue(0), std::any_cast<libcellml::IssuePtr>(annotator->item("i_dont_exist").second));

    // Test that repeated calls to the same unfound id do not generate new errors:
    EXPECT_EQ(libcellml::Annotator::TYPE::ISSUE, annotator->item("i_dont_exist").first);
    EXPECT_EQ(size_t(1), annotator->issueCount());
    EXPECT_EQ(annotator->issue(0), std::any_cast<libcellml::IssuePtr>(annotator->item("i_dont_exist").second));

    // Test bad casting handling:
    try {
        auto m = std::any_cast<libcellml::ComponentPtr>(annotator->item("model_id"));
    } catch (const std::bad_any_cast &e) {
        std::stringstream s;
        s << e.what();
        EXPECT_EQ("bad any cast", s.str());
    }
}

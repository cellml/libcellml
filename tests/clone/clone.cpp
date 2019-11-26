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

void compareUnit(const libcellml::UnitsPtr &u1, const libcellml::UnitsPtr &u2)
{
    EXPECT_EQ(u1->unitCount(), u2->unitCount());

    std::string reference1, prefix1, id1, reference2, prefix2, id2;
    double exponent1, multiplier1, exponent2, multiplier2;
    for (size_t index = 0; index < u1->unitCount(); ++index) {
        u1->unitAttributes(index, reference1, prefix1, exponent1, multiplier1, id1);
        u2->unitAttributes(index, reference2, prefix2, exponent2, multiplier2, id2);

        EXPECT_EQ(reference1, reference2);
        EXPECT_EQ(prefix1, prefix2);
        EXPECT_EQ(exponent1, exponent2);
        EXPECT_EQ(multiplier1, multiplier2);
        EXPECT_EQ(id1, id2);
    }
}

void compareUnits(const libcellml::UnitsPtr &u1, const libcellml::UnitsPtr &u2)
{
    EXPECT_EQ(u1->id(), u2->id());
    EXPECT_EQ(u1->isBaseUnit(), u2->isBaseUnit());
    EXPECT_EQ(u1->isImport(), u2->isImport());
    EXPECT_EQ(u1->importReference(), u2->importReference());
    EXPECT_EQ(u1->name(), u2->name());
    EXPECT_EQ(nullptr, u2->parent());

    compareUnit(u1, u2);
}

TEST(Clone, importSource)
{
    auto i = libcellml::ImportSource::create();

    i->setId("import");
    i->setUrl("this_is_a_url");

    auto iClone = i->clone();

    EXPECT_EQ(i->id(), iClone->id());
    EXPECT_EQ(i->url(), iClone->url());
    EXPECT_EQ(i->hasModel(), iClone->hasModel());
}

TEST(Clone, unitsBaseUnits)
{
    auto u = libcellml::Units::create();

    u->setId("unique_id");
    u->setName("units");
    u->setImportReference("a_url");

    auto uClone = u->clone();

    compareUnits(u, uClone);
}

TEST(Clone, unitsImportedUnits)
{
    auto u = libcellml::Units::create();

    auto import = libcellml::ImportSource::create();
    import->setUrl("some-other-model.xml");

    u->setId("unique_id");
    u->setName("units");
    u->setSourceUnits(import, "imported_units_name");

    auto uClone = u->clone();

    compareUnits(u, uClone);
}

TEST(Clone, unitsImportedUnitsWithAdditionalUnit)
{
    auto u = libcellml::Units::create();

    auto import = libcellml::ImportSource::create();
    import->setUrl("some-other-model.xml");

    u->setId("unique_id");
    u->setName("units");
    u->setSourceUnits(import, "imported_units_name");
    u->addUnit(libcellml::Units::StandardUnit::LUMEN);
    u->addUnit("a", "milli", -2.0);

    auto uClone = u->clone();

    compareUnits(u, uClone);
}

TEST(Clone, unitsInModel)
{
    auto m = libcellml::Model::create();
    auto u = libcellml::Units::create();

    u->setId("unique_id");
    u->setName("units");

    m->addUnits(u);

    auto uClone = u->clone();

    compareUnits(u, uClone);
}

TEST(Clone, variable)
{
    auto v = libcellml::Variable::create();
    v->setUnits("lightning");
    v->setInitialValue(-3.0);
    v->setInterfaceType(libcellml::Variable::InterfaceType::PRIVATE);
    v->setId("id_unique");
    v->setName("variable");

    auto vClone = v->clone();

    EXPECT_EQ(nullptr, vClone->parent());
    EXPECT_NE(v->units(), vClone->units());
    EXPECT_EQ(v->initialValue(), vClone->initialValue());
    EXPECT_EQ(v->interfaceType(), vClone->interfaceType());
    EXPECT_EQ(v->id(), vClone->id());
    EXPECT_EQ(v->name(), vClone->name());

    vClone->setUnits("on_my_own");
    vClone->setInitialValue("45.0");
    vClone->setInterfaceType("public");
    vClone->setId("unique_again");
    vClone->setName("on_my_own");

    EXPECT_NE(v->units(), vClone->units());
    EXPECT_EQ(v->initialValue(), "-3");
    EXPECT_EQ(v->interfaceType(), "private");
    EXPECT_EQ(v->id(), "id_unique");
    EXPECT_EQ(v->name(), "variable");
}

TEST(Clone, variableWithUnitsPtrSet)
{
    auto u = libcellml::Units::create();
    u->setName("daves");

    auto v = libcellml::Variable::create();
    v->setUnits(u);

    auto vClone = v->clone();

    EXPECT_NE(v->units(), vClone->units());
    EXPECT_EQ(v->units()->name(), vClone->units()->name());
    EXPECT_EQ(nullptr, vClone->units()->parent());
}

TEST(Clone, variableInModel)
{
    auto m = libcellml::Model::create();
    auto u = libcellml::Units::create();
    u->setName("daves");
    m->addUnits(u);

    auto c = libcellml::Component::create();
    m->addComponent(c);

    auto v = libcellml::Variable::create();
    v->setUnits(u);

    c->addVariable(v);

    auto vClone = v->clone();

    EXPECT_EQ(nullptr, vClone->parent());
    EXPECT_NE(v->units(), vClone->units());
    EXPECT_EQ(nullptr, vClone->units()->parent());
}

void compareReset(const libcellml::ResetPtr &r1, const libcellml::ResetPtr &r2)
{
    EXPECT_EQ(r1->id(), r2->id());
    EXPECT_EQ(r1->order(), r2->order());
    if (r1->variable() != nullptr) {
        EXPECT_NE(r1->variable(), r2->variable());
        EXPECT_EQ(r1->variable()->name(), r2->variable()->name());
    }
    if (r1->testVariable() != nullptr) {
        EXPECT_NE(r1->testVariable(), r2->testVariable());
        EXPECT_EQ(r1->testVariable()->name(), r2->testVariable()->name());
    }
}

TEST(Clone, reset)
{
    auto r = libcellml::Reset::create();
    r->setId("unique");
    r->setOrder(32);

    auto rClone = r->clone();

    compareReset(r, rClone);
}

TEST(Clone, resetWithVariable)
{
    auto r = libcellml::Reset::create();
    auto v = libcellml::Variable::create();

    r->setId("unique");
    r->setOrder(22);
    r->setVariable(v);

    auto rClone = r->clone();

    compareReset(r, rClone);
}

TEST(Clone, resetWithTestVariable)
{
    auto r = libcellml::Reset::create();
    auto v = libcellml::Variable::create();

    r->setId("unique");
    r->setOrder(43);
    r->setTestVariable(v);

    auto rClone = r->clone();

    compareReset(r, rClone);
}

TEST(Clone, resetWithMath)
{
    auto r = libcellml::Reset::create();
    r->setId("unique");
    r->setOrder(32);
    r->setTestValue(NON_EMPTY_MATH);
    r->setResetValue(EMPTY_MATH);

    auto rClone = r->clone();

    compareReset(r, rClone);
}

TEST(Clone, resetAllIdsSet)
{
    auto r = libcellml::Reset::create();
    r->setId("unique");
    r->setResetValueId("rId");
    r->setTestValueId("tId");

    auto rClone = r->clone();

    compareReset(r, rClone);
}

void compareComponent(const libcellml::ComponentPtr &c1, const libcellml::ComponentPtr &c2, const libcellml::EntityPtr &expectedParent = nullptr)
{
    EXPECT_EQ(c1->name(), c2->name());
    EXPECT_EQ(c1->id(), c2->id());
    EXPECT_EQ(c1->isImport(), c2->isImport());
    EXPECT_EQ(c1->importSource(), c2->importSource());
    EXPECT_EQ(c1->importReference(), c2->importReference());
    EXPECT_EQ(c1->componentCount(), c2->componentCount());
    EXPECT_EQ(c1->resetCount(), c2->resetCount());
    EXPECT_EQ(c1->variableCount(), c2->variableCount());
    EXPECT_EQ(expectedParent, c2->parent());
    for (size_t index = 0; index < c1->componentCount(); ++index) {
        auto c1i = c1->component(index);
        auto c2i = c2->component(index);
        compareComponent(c1i, c2i, c2);
    }
}

TEST(Clone, component)
{
    auto c = libcellml::Component::create();
    c->setId("unique");
    c->setName("copy");
    c->setMath(NON_EMPTY_MATH);

    auto cClone = c->clone();

    compareComponent(c, cClone);

    cClone->setName("on_my_own");
    EXPECT_NE(c->name(), cClone->name());
}

TEST(Clone, componentWithVariables)
{
    auto c = libcellml::Component::create();
    auto u = libcellml::Units::create();
    auto v1 = libcellml::Variable::create();
    auto v2 = libcellml::Variable::create();

    u->setName("daves");
    v1->setUnits(u);

    c->setId("unique");
    c->setName("copy");

    c->addVariable(v1);
    c->addVariable(v2);

    auto cClone = c->clone();

    compareComponent(c, cClone);
}

TEST(Clone, componentWithResets)
{
    auto c = libcellml::Component::create();
    auto r1 = libcellml::Reset::create();
    auto r2 = libcellml::Reset::create();

    c->setId("unique");
    c->setName("copy");

    c->addReset(r1);
    c->addReset(r2);

    auto cClone = c->clone();

    compareComponent(c, cClone);
}

TEST(Clone, componentWithChildren)
{
    auto c = libcellml::Component::create();
    auto c1 = libcellml::Component::create();
    auto c2 = libcellml::Component::create();

    c->setId("unique");
    c->setName("copy");

    c->addComponent(c1);
    c->addComponent(c2);

    auto cClone = c->clone();

    compareComponent(c, cClone);
}

TEST(Clone, componentWithImport)
{
    auto c = libcellml::Component::create();
    auto import = libcellml::ImportSource::create();
    import->setUrl("some-other-model.xml");

    c->setId("unique");
    c->setName("copy");
    c->setSourceComponent(import, "imported_component_name");

    auto cClone = c->clone();

    compareComponent(c, cClone);
}

TEST(Clone, componentWithImportAndChildren)
{
    auto c = libcellml::Component::create();
    auto c1 = libcellml::Component::create();
    auto c2 = libcellml::Component::create();
    auto import = libcellml::ImportSource::create();

    import->setUrl("some-other-model.xml");
    c->setId("unique");
    c->setName("copy");
    c1->setName("child_1");
    c2->setName("child_2");

    c->addComponent(c1);
    c->addComponent(c2);
    c->setSourceComponent(import, "my_component_name");

    auto cClone = c->clone();

    compareComponent(c, cClone);
}

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

TEST(Clone, variableWithEquivalences)
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

    auto vClone = v->clone(true);
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

TEST(Clone, component)
{
    auto c = libcellml::Component::create();
    c->setName("copy");

    auto cClone = c->clone();

    EXPECT_EQ(c->name(), cClone->name());

    cClone->setName("on_my_own");
    EXPECT_NE(c->name(), cClone->name());
}


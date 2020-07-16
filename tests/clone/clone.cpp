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

    std::string reference1;
    std::string prefix1;
    std::string id1;
    std::string reference2;
    std::string prefix2;
    std::string id2;
    double exponent1;
    double multiplier1;
    double exponent2;
    double multiplier2;
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

void compareUnits(const libcellml::UnitsPtr &u1, const libcellml::UnitsPtr &u2, const libcellml::EntityPtr &expectedParent = nullptr)
{
    EXPECT_EQ(u1->id(), u2->id());
    EXPECT_EQ(u1->isBaseUnit(), u2->isBaseUnit());
    EXPECT_EQ(u1->isImport(), u2->isImport());
    if (u1->isImport() && u2->isImport()) {
        EXPECT_EQ(u1->importSource()->url(), u2->importSource()->url());
        EXPECT_EQ(u1->importSource()->id(), u2->importSource()->id());
    }
    EXPECT_EQ(u1->importReference(), u2->importReference());
    EXPECT_EQ(u1->name(), u2->name());
    EXPECT_EQ(expectedParent, u2->parent());

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

TEST(Clone, unitsWithUnit)
{
    auto u = libcellml::Units::create();

    u->setId("unique_id");
    u->setName("units");
    u->addUnit(libcellml::Units::StandardUnit::LUMEN);
    u->addUnit("meter", "milli", -2.0);

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
    if (c1->isImport() && c2->isImport()) {
        EXPECT_EQ(c1->importSource()->url(), c2->importSource()->url());
        EXPECT_EQ(c1->importSource()->id(), c2->importSource()->id());
    }
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
    for (size_t index = 0; index < c2->resetCount(); ++index) {
        auto r = c2->reset(index);
        if (r->variable() != nullptr) {
            EXPECT_TRUE(c2->hasVariable(r->variable()));
        }
        if (r->testVariable() != nullptr) {
            EXPECT_TRUE(c2->hasVariable(r->testVariable()));
        }
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

TEST(Clone, componentWithResetsAndVariables)
{
    auto c = libcellml::Component::create();
    auto r1 = libcellml::Reset::create();
    auto r2 = libcellml::Reset::create();
    auto v1 = libcellml::Variable::create();
    auto v2 = libcellml::Variable::create();
    auto v3 = libcellml::Variable::create();
    auto v4 = libcellml::Variable::create();

    c->setId("unique");
    c->setName("copy");

    v1->setName("variable1");
    v2->setName("variable2");
    v3->setName("variable3");
    v4->setName("variable4");

    r1->setVariable(v2);
    r1->setTestVariable(v3);

    r2->setTestVariable(v4);

    c->addVariable(v1);
    c->addVariable(v2);
    c->addVariable(v3);
    c->addVariable(v4);

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

void compareModel(const libcellml::ModelPtr &m1, const libcellml::ModelPtr &m2)
{
    EXPECT_EQ(m1->id(), m2->id());
    EXPECT_EQ(m1->name(), m2->name());

    EXPECT_EQ(m1->unitsCount(), m2->unitsCount());
    EXPECT_EQ(m1->componentCount(), m2->componentCount());

    for (size_t index = 0; index < m1->unitsCount(); ++index) {
        auto u1 = m1->units(index);
        auto u2 = m2->units(index);
        compareUnits(u1, u2, m2);
    }

    for (size_t index = 0; index < m1->componentCount(); ++index) {
        auto c1 = m1->component(index);
        auto c2 = m2->component(index);
        compareComponent(c1, c2, m2);
    }
}

TEST(Clone, model)
{
    auto m = libcellml::Model::create();
    m->setId("unique_model");
    m->setName("model");
    m->setEncapsulationId("encapsulation_id");

    auto mClone = m->clone();

    compareModel(m, mClone);
}

TEST(Clone, modelWithUnits)
{
    auto m = libcellml::Model::create();
    auto u = libcellml::Units::create();

    u->setName("jangle");
    m->setId("unique_model");
    m->setName("model");

    m->addUnits(u);

    auto mClone = m->clone();

    compareModel(m, mClone);
}

TEST(Clone, modelWithComponents)
{
    auto m = libcellml::Model::create();
    m->setId("unique_model");
    m->setName("model");

    auto c = libcellml::Component::create();
    auto c1 = libcellml::Component::create();
    auto c2 = libcellml::Component::create();

    c->setId("unique");
    c->setName("copy");
    c1->setName("child_1");
    c2->setName("child_2");

    c->addComponent(c1);
    c->addComponent(c2);

    m->addComponent(c);

    auto mClone = m->clone();

    compareModel(m, mClone);
}

TEST(Clone, modelWithVariableEquivalences)
{
    auto m = libcellml::Model::create();
    m->setId("unique_model");
    m->setName("model");

    auto c = libcellml::Component::create();
    auto c1 = libcellml::Component::create();
    auto c2 = libcellml::Component::create();
    auto v1 = libcellml::Variable::create();
    auto v2 = libcellml::Variable::create();
    auto u = libcellml::Units::create();

    u->setName("second");

    v1->setUnits(u);
    v2->setUnits(u);
    m->addUnits(u);

    c->setId("unique");
    c->setName("copy");
    c1->setName("child_1");
    c1->addVariable(v1);
    c2->setName("child_2");
    c2->addVariable(v2);

    c->addComponent(c1);
    c->addComponent(c2);

    m->addComponent(c);

    libcellml::Variable::addEquivalence(v1, v2);

    auto mClone = m->clone();

    compareModel(m, mClone);

    libcellml::PrinterPtr p = libcellml::Printer::create();

    EXPECT_EQ(p->printModel(m), p->printModel(mClone));
}

TEST(Clone, generateFromClonedModel)
{
    libcellml::ParserPtr parser = libcellml::Parser::create();
    libcellml::ModelPtr model = parser->parseModel(fileContents("generator/hodgkin_huxley_squid_axon_model_1952/model.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    auto clonedModel = model->clone();

    compareModel(model, clonedModel);

    libcellml::AnalyserPtr analyser = libcellml::Analyser::create();

    analyser->analyseModel(clonedModel);

    libcellml::GeneratorPtr generator = libcellml::Generator::create();

    EXPECT_EQ(fileContents("generator/hodgkin_huxley_squid_axon_model_1952/model.c"), generator->implementationCode(analyser->model()));

    libcellml::PrinterPtr p = libcellml::Printer::create();

    EXPECT_EQ(p->printModel(model), p->printModel(clonedModel));
}

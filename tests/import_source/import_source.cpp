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

#include "test_utils.h"

#include "gtest/gtest.h"

#include <libcellml>

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
    EXPECT_EQ(u1->importReference(), u2->importReference());
    EXPECT_EQ(u1->name(), u2->name());
    EXPECT_EQ(expectedParent, u2->parent());

    compareUnit(u1, u2);
}

TEST(ImportSource, createImportSource)
{
    auto imp1 = libcellml::ImportSource::create();
}

TEST(ImportSource, addToModel)
{
    auto model = libcellml::Model::create("so_much_importing");

    // Add component to model, then import to component:
    auto imp1 = libcellml::ImportSource::create();
    std::string url1 = "http://www.example.com#hello";
    imp1->setUrl(url1);

    EXPECT_TRUE(model->addImportSource(imp1));
    EXPECT_EQ(size_t(1), model->importSourceCount());
    EXPECT_EQ(imp1, model->importSource(0));

    // Add the same one again:
    EXPECT_FALSE(model->addImportSource(imp1));
    EXPECT_EQ(size_t(1), model->importSourceCount());
    EXPECT_EQ(imp1, model->importSource(0));

    // Add another with the same url:
    auto imp2 = libcellml::ImportSource::create();
    imp2->setUrl(url1);

    EXPECT_TRUE(model->addImportSource(imp2));
    EXPECT_EQ(size_t(2), model->importSourceCount());
    EXPECT_EQ(imp2, model->importSource(1));

    // Add another with a new url:
    auto imp3 = libcellml::ImportSource::create();
    auto url3 = "http://www.example.com#bonjour";
    imp3->setUrl(url3);

    EXPECT_TRUE(model->addImportSource(imp3));
    EXPECT_EQ(size_t(3), model->importSourceCount());
    EXPECT_EQ(imp3, model->importSource(2));
}

TEST(ImportSource, importSourceDetailsCoverage)
{
    auto model = libcellml::Model::create("importing_model");
    auto imp = libcellml::ImportSource::create();
    auto component1 = libcellml::Component::create("Bart");
    auto component2 = libcellml::Component::create("Lisa");
    auto units1 = libcellml::Units::create("Maggie");
    auto units2 = libcellml::Units::create("Marge");

    model->addComponent(component1);
    model->addComponent(component2);
    model->addUnits(units1);
    model->addUnits(units2);

    model->addImportSource(imp);
    EXPECT_TRUE(model->hasImportSource(imp));

    // Set up component so it's an import.
    component1->setImportSource(imp);

    EXPECT_TRUE(component1->isImport());
    EXPECT_EQ(size_t(1), imp->componentCount());
    EXPECT_EQ(component1, imp->component(0));
    EXPECT_EQ(nullptr, imp->component(99));

    // Add the other direction, expect false as it's already there.
    EXPECT_FALSE(imp->addComponent(component1));

    // Add the other component so it's an import.
    component2->setImportSource(imp);
    EXPECT_TRUE(component2->isImport());
    EXPECT_EQ(size_t(2), imp->componentCount());
    EXPECT_EQ(component2, imp->component(1));

    // Remove a component from the import source by index.
    EXPECT_TRUE(imp->removeComponent(0));
    EXPECT_EQ(size_t(1), imp->componentCount());
    EXPECT_FALSE(component1->isImport());

    // Remove component by pointer.
    EXPECT_TRUE(imp->removeComponent(component2));
    EXPECT_FALSE(component2->isImport());
    EXPECT_EQ(size_t(0), imp->componentCount());

    // Remove a component that doesn't exist.
    EXPECT_FALSE(imp->removeComponent(99));
    EXPECT_FALSE(imp->removeComponent(component2));
    libcellml::ComponentPtr nullComponent = nullptr;
    EXPECT_FALSE(imp->removeComponent(nullComponent));

    // Set up units so it's an import.
    units1->setImportSource(imp);

    EXPECT_TRUE(units1->isImport());
    EXPECT_EQ(size_t(1), imp->unitsCount());
    EXPECT_EQ(units1, imp->units(0));
    EXPECT_EQ(nullptr, imp->units(99));

    // Add the other direction, expect false as it's already there.
    EXPECT_FALSE(imp->addUnits(units1));

    // Add the other units so it's an import.
    units2->setImportSource(imp);

    EXPECT_TRUE(units2->isImport());
    EXPECT_EQ(size_t(2), imp->unitsCount());
    EXPECT_EQ(units2, imp->units(1));

    // Remove a units from the import source by index.
    EXPECT_TRUE(imp->removeUnits(0));
    EXPECT_EQ(size_t(1), imp->unitsCount());
    EXPECT_FALSE(units1->isImport());

    // Remove units by pointer.
    EXPECT_TRUE(imp->removeUnits(units2));
    EXPECT_FALSE(units2->isImport());

    // Remove a units that doesn't exist.
    EXPECT_FALSE(imp->removeUnits(99));
    EXPECT_FALSE(imp->removeUnits(units2));
    libcellml::UnitsPtr nullUnits = nullptr;
    EXPECT_FALSE(imp->removeUnits(nullUnits));

    EXPECT_TRUE(model->removeImportSource(0));
    EXPECT_FALSE(model->removeImportSource(0));
    model->addImportSource(imp);
    EXPECT_TRUE(model->removeImportSource(imp));
    EXPECT_FALSE(model->removeImportSource(imp));
}

TEST(ImportSource, importSourceMove)
{
    auto m1 = libcellml::Model::create("m1");
    auto imp = libcellml::ImportSource::create();

    EXPECT_TRUE(m1->addImportSource(imp));
    EXPECT_EQ(m1, imp->parent());

    // Add import source to another model.
    auto m2 = libcellml::Model::create("m2");
    EXPECT_TRUE(m2->addImportSource(imp));
    EXPECT_EQ(m2, imp->parent());

    // Expect that we can't delete from first model any more.
    EXPECT_EQ(size_t(0), m1->importSourceCount());
    EXPECT_FALSE(m1->removeImportSource(imp));

    // ... but that we can get it and remove it from the second.
    EXPECT_EQ(size_t(1), m2->importSourceCount());
    EXPECT_EQ(imp, m2->importSource(0));
    EXPECT_TRUE(m2->removeImportSource(imp));
    EXPECT_EQ(nullptr, imp->parent());
}

TEST(ImportSource, addRemoveFromModel)
{
    auto imp = libcellml::ImportSource::create();
    auto model = libcellml::Model::create();

    model->addImportSource(imp);
    EXPECT_EQ(size_t(1), model->importSourceCount());
    EXPECT_EQ(imp, model->importSource(0));

    model->removeImportSource(imp);
    EXPECT_EQ(size_t(0), model->importSourceCount());
    EXPECT_EQ(nullptr, model->importSource(0));

    auto imp1 = libcellml::ImportSource::create();
    auto imp2 = libcellml::ImportSource::create();
    auto c1 = libcellml::Component::create("c1");
    auto c2 = libcellml::Component::create("c2");
    auto u1 = libcellml::Units::create("u1");
    auto u2 = libcellml::Units::create("u2");

    c1->setSourceComponent(imp1, "cc1");
    c2->setSourceComponent(imp1, "cc2");
    u1->setSourceUnits(imp2, "uu1");
    u2->setSourceUnits(imp2, "uu2");

    EXPECT_TRUE(c1->isImport());
    EXPECT_TRUE(c2->isImport());
    EXPECT_TRUE(u1->isImport());
    EXPECT_TRUE(u2->isImport());

    model->addImportSource(imp1);
    model->addImportSource(imp2);

    EXPECT_EQ(size_t(2), model->importSourceCount());

    model->removeAllImportSources();

    EXPECT_EQ(size_t(0), model->importSourceCount());

    EXPECT_TRUE(c1->isImport());
    EXPECT_TRUE(c2->isImport());
    EXPECT_TRUE(u1->isImport());
    EXPECT_TRUE(u2->isImport());
}

TEST(ImportSource, moveToAnotherModel)
{
    auto imp = libcellml::ImportSource::create();
    auto model1 = libcellml::Model::create();
    auto model2 = libcellml::Model::create();

    model1->addImportSource(imp);
    EXPECT_EQ(size_t(1), model1->importSourceCount());
    EXPECT_EQ(imp, model1->importSource(0));

    model2->addImportSource(imp);
    EXPECT_EQ(size_t(1), model2->importSourceCount());
    EXPECT_EQ(imp, model2->importSource(0));
    EXPECT_EQ(size_t(0), model1->importSourceCount());
    EXPECT_EQ(nullptr, model1->importSource(0));

    EXPECT_EQ(model2, imp->parent());
}

TEST(ImportSource, createLinkedMultiple)
{
    auto model = libcellml::Model::create();
    auto c1 = libcellml::Component::create("c1");
    auto c2 = libcellml::Component::create("c2");
    auto u1 = libcellml::Units::create("u1");
    auto u2 = libcellml::Units::create("u2");
    auto imp = libcellml::ImportSource::create();

    model->addComponent(c1);
    model->addComponent(c2);
    model->addUnits(u1);
    model->addUnits(u2);

    c1->setImportSource(imp);
    c2->setImportSource(imp);
    u1->setImportSource(imp);
    u2->setImportSource(imp);

    EXPECT_EQ(size_t(2), imp->componentCount());
    EXPECT_EQ(size_t(2), imp->unitsCount());
    EXPECT_EQ(size_t(1), model->importSourceCount());

    // Change to another import source:
    auto imp2 = libcellml::ImportSource::create();
    c2->setImportSource(imp2);
    u2->setImportSource(imp2);

    EXPECT_EQ(size_t(1), imp->componentCount());
    EXPECT_EQ(size_t(1), imp->unitsCount());
    EXPECT_EQ(size_t(1), imp2->componentCount());
    EXPECT_EQ(size_t(1), imp2->unitsCount());
    EXPECT_EQ(size_t(2), model->importSourceCount());

    imp->removeAllComponents();
    imp->removeAllUnits();
    EXPECT_EQ(size_t(0), imp->componentCount());
    EXPECT_EQ(size_t(0), imp->unitsCount());
    EXPECT_FALSE(c1->isImport());
    EXPECT_FALSE(u1->isImport());
}

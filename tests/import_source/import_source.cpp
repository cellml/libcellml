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

TEST(ImportSource, createImportSource)
{
    auto imp1 = libcellml::ImportSource::create();
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

TEST(ImportSource, cloneEmpty)
{
    auto imp = libcellml::ImportSource::create();

    imp->setUrl("http://example.com");
    imp->setId("mySuperDooperId");

    auto cloned = imp->clone();

    EXPECT_EQ(imp->url(), cloned->url());
    EXPECT_EQ(imp->id(), cloned->id());
}

TEST(ImportSource, cloneLinkedSingle)
{
    auto model = libcellml::Model::create();
    auto c = libcellml::Component::create("c");

    auto imp = libcellml::ImportSource::create();
    imp->setId("myId");
    imp->setUrl("myUrl");

    model->addComponent(c);
    c->setImportSource(imp);
    c->setImportReference("myRef");

    auto cloned = imp->clone();

    EXPECT_EQ(imp->url(), cloned->url());
    EXPECT_EQ(imp->id(), cloned->id());

    // Not sure whether the cloned import source should be added to this model?
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
}

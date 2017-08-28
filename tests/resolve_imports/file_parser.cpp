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

#include <algorithm>
#include <fstream>
#include <iostream>
#include <libcellml>
#include <sstream>
#include <vector>

// generated with test resource locations
#include "test_resources.h"

static std::string resolvePath(const std::string& filename, const std::string& base)
{
    // we can be naive here as we know what we are dealing with
    std::string path = base.substr(0, base.find_last_of('/')+1) + filename;
    return path;
}

static size_t countImportedChildren(libcellml::ComponentPtr parent)
{
    size_t numberImportedChildren = 0;
    for (size_t n = 0; n < parent->componentCount();  ++n)
    {
        libcellml::ComponentPtr c = parent->getComponent(n);
        if (c->isImport()) ++numberImportedChildren;
        numberImportedChildren += countImportedChildren(c);
    }
    return numberImportedChildren;
}

static size_t countUnresolvedC(libcellml::ComponentPtr component);
static size_t countUnresolvedComponents(libcellml::ComponentPtr component);
static size_t countUnresolvedImportedComponents(libcellml::ModelPtr model);

static size_t countUnresolvedC(libcellml::ComponentPtr component)
{
    size_t count = 0;
    if (component->isImport())
    {
        libcellml::ImportPtr imp = component->getImport();
        if (! imp->isResolved()) ++count;
        else
        {
            libcellml::ModelPtr iModel = imp->getResolvingModel();
            count += countUnresolvedImportedComponents(iModel);
        }
    }
    return count;
}

static size_t countUnresolvedComponents(libcellml::ComponentPtr component)
{
    size_t count = countUnresolvedC(component);
    for (size_t n = 0; n < component->componentCount();  ++n)
    {
        libcellml::ComponentPtr c = component->getComponent(n);
        count += countUnresolvedC(c);
    }
    return count;
}

static size_t countUnresolvedImportedComponents(libcellml::ModelPtr model)
{
    size_t count = 0;
    for (size_t m = 0; m < model->componentCount();  ++m)
    {
        libcellml::ComponentPtr c = model->getComponent(m);
        count += countUnresolvedComponents(c);
    }
    return count;
}

static void resolveComponents(libcellml::ComponentPtr component,
                              const std::string& baseFile);
static void resolveImportedComponents(libcellml::ModelPtr model,
                                      const std::string& baseFile);

static void resolveComponent(libcellml::ComponentPtr component,
                             const std::string& baseFile)
{
    if (component->isImport())
    {
        libcellml::ImportPtr imp = component->getImport();
        if (! imp->isResolved())
        {
            std::string url = resolvePath(imp->getSource(), baseFile);
            std::cout << "URL: " << url << std::endl;
            std::ifstream t(url);
            std::stringstream buffer;
            buffer << t.rdbuf();
            libcellml::Parser p(libcellml::Format::XML);
            libcellml::ModelPtr model = p.parseModel(buffer.str());
            EXPECT_EQ(0, p.errorCount());
            if (model)
            {
                imp->resolveImport(model);
                resolveImportedComponents(model, url);
            }
        }
    }
}

static void resolveComponents(libcellml::ComponentPtr component,
                              const std::string& baseFile)
{
    for (size_t n = 0; n < component->componentCount();  ++n)
    {
        libcellml::ComponentPtr c = component->getComponent(n);
        resolveComponent(c, baseFile);
    }
}

static void resolveImportedComponents(libcellml::ModelPtr model,
                                      const std::string& baseFile)
{
    for (size_t n = 0; n < model->componentCount();  ++n)
    {
        libcellml::ComponentPtr c = model->getComponent(n);
        resolveComponents(c, baseFile);
    }
}

TEST(ResolveImports, resolveSineModelFromFile) {
    std::ifstream t(TestResources::getLocation(
                    TestResources::CELLML_SINE_MODEL_RESOURCE));
    std::stringstream buffer;
    buffer << t.rdbuf();

    libcellml::Parser p(libcellml::Format::XML);
    libcellml::ModelPtr model = p.parseModel(buffer.str());

    EXPECT_EQ(0, p.errorCount());

    size_t nImportedComponents = 0;
    for (size_t n = 0; n < model->componentCount();  ++n)
    {
        libcellml::ComponentPtr c = model->getComponent(n);
        if (c->isImport()) ++nImportedComponents;
        nImportedComponents += countImportedChildren(c);
    }
    EXPECT_EQ(0, nImportedComponents);
}

TEST(ResolveImports, resolveSineImportsModelFromFile) {
    std::string sineModelLocation = TestResources::getLocation(
                TestResources::CELLML_SINE_IMPORTS_MODEL_RESOURCE);
    std::ifstream t(sineModelLocation);
    std::stringstream buffer;
    buffer << t.rdbuf();

    libcellml::Parser p(libcellml::Format::XML);
    libcellml::ModelPtr model = p.parseModel(buffer.str());
    EXPECT_EQ(0, p.errorCount());

    size_t nImportedComponents = 0;
    for (size_t n = 0; n < model->componentCount();  ++n)
    {
        libcellml::ComponentPtr c = model->getComponent(n);
        if (c->isImport()) ++nImportedComponents;
        nImportedComponents += countImportedChildren(c);
    }
    EXPECT_EQ(3, nImportedComponents);

    EXPECT_EQ(3, countUnresolvedImportedComponents(model));
    resolveImportedComponents(model, sineModelLocation);
    EXPECT_EQ(0, countUnresolvedImportedComponents(model));
}

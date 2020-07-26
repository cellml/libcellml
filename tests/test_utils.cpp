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

#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>

#include "test_resources.h"

std::string resourcePath(const std::string &resourceRelativePath)
{
    return TESTS_RESOURCE_LOCATION + "/" + resourceRelativePath;
}

std::string fileContents(const std::string &fileName)
{
    std::ifstream file(resourcePath(fileName));
    std::stringstream buffer;

    buffer << file.rdbuf();

    return buffer.str();
}

void printIssues(const libcellml::LoggerPtr &l, bool headings, bool causes, bool rule)
{
    int width = int(floor(log10(l->errorCount())));
    for (size_t i = 0; i < l->issueCount(); ++i) {
        switch (l->issue(i)->level()) {
        case libcellml::Issue::Level::ERROR:
            std::cout << "Error " << std::setw(width) << i + 1 << ": ";
            break;
        case libcellml::Issue::Level::WARNING:
            std::cout << "Warning " << std::setw(width) << i + 1 << ": ";
            break;
        case libcellml::Issue::Level::HINT:
            std::cout << "Hint " << std::setw(width) << i + 1 << ": ";
            break;
        default:
            break;
        }

        if (headings) {
            std::cout << ", " << l->issue(i)->referenceHeading();
        }
        if (causes) {
            std::cout << ", " << static_cast<int>(l->issue(i)->cause());
        }
        if (rule) {
            std::cout << ", " << static_cast<int>(l->issue(i)->referenceRule());
        }
        std::cout << std::endl
                  << l->issue(i)->description() << std::endl;
    }
}

void printModel(const libcellml::ModelPtr &model)
{
    std::cout << "The model name is: '" << model->name() << "'" << std::endl;
    if (model->id() != "") {
        std::cout << "The model id is: '" << model->id() << "'" << std::endl;
    }

    // 2.a    Print any custom units of the model
    std::cout << "The model defines " << model->unitsCount()
              << " custom units:" << std::endl;
    for (size_t u = 0; u < model->unitsCount(); ++u) {
        std::cout << "  Units[" << u << "] is '" << model->units(u)->name() << "'"
                  << std::endl;
    }

    // 2.b    Print the components of the model
    std::cout << "The model has " << model->componentCount()
              << " components:" << std::endl;
    for (size_t c = 0; c < model->componentCount(); ++c) {
        // 2.c  Printing the attributes of the component
        auto component = model->component(c);
        std::string spacer = "  ";
        printComponent(component, c, spacer);
    }
}

void printComponent(const libcellml::ComponentPtr &component, size_t const c, std::string const spacer)
{
    std::cout << spacer << "Component[" << c << "] has name: '"
              << component->name() << "'" << std::endl;
    if (component->id() != "") {
        std::cout << spacer << "Component[" << c << "] has id: '"
                  << component->id() << "'" << std::endl;
    }

    std::cout << spacer << "Component[" << c << "] has "
              << component->variableCount()
              << " variables:" << std::endl;

    // Printing the variables within the component
    for (size_t vIndex = 0; vIndex < component->variableCount(); vIndex++) {
        auto v = component->variable(vIndex);
        std::cout << spacer << "  Variable[" << vIndex << "] has name: '"
                  << v->name() << "'" << std::endl;
        if (v->initialValue() != "") {
            std::cout << spacer << "  Variable[" << vIndex << "] has initial_value: '"
                      << v->initialValue() << "'"
                      << std::endl;
        }
        if (v->units() != nullptr) {
            std::cout << spacer << "  Variable[" << vIndex << "] has units: '"
                      << v->units()->name() << "'" << std::endl;
        }
        std::cout << spacer << "  Variable[" << vIndex << "] has " << v->equivalentVariableCount() << " equivalent variable(s): ";
        for (size_t eIndex = 0; eIndex < v->equivalentVariableCount(); ++eIndex) {
            auto equivVariable = v->equivalentVariable(eIndex);
            std::cout << equivVariable->name() << ", ";
        }
        std::cout << std::endl;
    }

    // Print the maths within the component
    if (component->math() != "") {
        std::cout << spacer << "  Maths in the component is:" << std::endl;
        std::cout << component->math() << std::endl;
    }

    // Print the encapsulated components
    if (component->componentCount() > 0) {
        std::cout << spacer << "Component[" << c << "] has "
                  << component->componentCount()
                  << " child components:" << std::endl;

        for (size_t c2 = 0; c2 < component->componentCount(); c2++) {
            auto child = component->component(c2);
            std::string oneMoreSpacer = spacer + "  ";
            printComponent(child, c2, oneMoreSpacer);
        }
    }
}

void expectEqualIssues(const std::vector<std::string> &issues, const libcellml::LoggerPtr &logger)

{
    EXPECT_EQ(issues.size(), logger->issueCount());
    for (size_t i = 0; i < logger->issueCount() && i < issues.size(); ++i) {
        EXPECT_EQ(issues.at(i), logger->issue(i)->description());
    }
}

void expectEqualIssuesSpecificationHeadings(const std::vector<std::string> &issues,
                                            const std::vector<std::string> &specificationHeadings,
                                            const libcellml::LoggerPtr &logger)
{
    EXPECT_EQ(issues.size(), logger->issueCount());
    EXPECT_EQ(specificationHeadings.size(), logger->issueCount());
    for (size_t i = 0; i < logger->issueCount() && i < issues.size(); ++i) {
        EXPECT_EQ(issues.at(i), logger->issue(i)->description());
        EXPECT_EQ(specificationHeadings.at(i), logger->issue(i)->referenceHeading());
    }
}

void expectEqualIssuesCauses(const std::vector<std::string> &issues,
                             const std::vector<libcellml::Issue::Cause> &causes,
                             const libcellml::LoggerPtr &logger)
{
    EXPECT_EQ(issues.size(), logger->issueCount());
    EXPECT_EQ(causes.size(), logger->issueCount());
    for (size_t i = 0; i < logger->issueCount() && i < issues.size(); ++i) {
        EXPECT_EQ(issues.at(i), logger->issue(i)->description());
        EXPECT_EQ(causes.at(i), logger->issue(i)->cause());
    }
}

libcellml::ModelPtr createModel(const std::string &name)
{
    libcellml::ModelPtr model = libcellml::Model::create();
    model->setName(name);
    return model;
}

libcellml::ComponentPtr createComponentInModel(const libcellml::ModelPtr &model, const std::string &componentName)
{
    libcellml::ComponentPtr component = libcellml::Component::create();
    component->setName(componentName);
    model->addComponent(component);
    return component;
}

libcellml::ModelPtr createModelWithComponent(const std::string &modelName, const std::string &componentName)
{
    libcellml::ModelPtr model = libcellml::Model::create();
    model->setName(modelName);
    createComponentInModel(model, componentName);
    return model;
}

libcellml::VariablePtr createVariableWithUnits(const std::string &name, const std::string &units)
{
    libcellml::VariablePtr v = libcellml::Variable::create();
    v->setName(name);
    v->setUnits(units);

    return v;
}

libcellml::ModelPtr createModelTwoComponentsWithOneVariableEach(const std::string &modelName, const std::string &c1Name, const std::string &c2Name, const std::string &v1Name, const std::string &v2Name)
{
    libcellml::ModelPtr model = libcellml::Model::create();
    model->setName(modelName);
    auto c1 = createComponentInModel(model, c1Name);
    auto c2 = createComponentInModel(model, c2Name);

    libcellml::VariablePtr v1 = libcellml::Variable::create();
    v1->setName(v1Name);
    v1->setInterfaceType("public");
    c1->addVariable(v1);
    libcellml::VariablePtr v2 = libcellml::Variable::create();
    v2->setName(v2Name);
    v2->setInterfaceType("public");
    c2->addVariable(v2);

    return model;
}

libcellml::ComponentPtr createImportInModel(const libcellml::ModelPtr &model,
                                            const std::string &componentName,
                                            const std::string &importSourceUrl,
                                            const std::string &importReference)
{
    model->addComponent(libcellml::Component::create(componentName));
    model->component(componentName)->setImportSource(libcellml::ImportSource::create());
    model->component(componentName)->importSource()->setUrl(importSourceUrl);
    model->component(componentName)->setImportReference(importReference);
    return model->component(componentName);
}

libcellml::ComponentPtr createImportInComponent(const libcellml::ComponentPtr &component,
                                                const std::string &componentName,
                                                const std::string &importSourceUrl,
                                                const std::string &importReference)
{
    component->addComponent(libcellml::Component::create(componentName));
    component->component(componentName)->setImportSource(libcellml::ImportSource::create());
    component->component(componentName)->importSource()->setUrl(importSourceUrl);
    component->component(componentName)->setImportReference(importReference);
    return component->component(componentName);
}

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

void compareUnits(const libcellml::UnitsPtr &u1, const libcellml::UnitsPtr &u2, const libcellml::EntityPtr &expectedParent)
{
    EXPECT_EQ(u1->id(), u2->id());
    EXPECT_EQ(u1->isBaseUnit(), u2->isBaseUnit());
    EXPECT_EQ(u1->isImport(), u2->isImport());
    EXPECT_EQ(u1->importReference(), u2->importReference());
    EXPECT_EQ(u1->name(), u2->name());
    EXPECT_EQ(expectedParent, u2->parent());

    compareUnit(u1, u2);
}

void compareComponent(const libcellml::ComponentPtr &c1, const libcellml::ComponentPtr &c2, const libcellml::EntityPtr &expectedParent)
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

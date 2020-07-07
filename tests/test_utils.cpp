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
        std::cout << "Issue " << std::setw(width) << i + 1 << ": ";
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

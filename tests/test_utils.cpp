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
    for (size_t i = 0; i < l->issueCount(); ++i) {
        std::cout << "Issue " << std::setw(3) << i + 1 << ": ";
        std::cout << l->issue(i)->description();
        if (headings) {
            std::cout << ", " << l->issue(i)->referenceHeading();
        }
        if (causes) {
            std::cout << ", " << static_cast<int>(l->issue(i)->cause());
        }
        if (rule) {
            std::cout << ", " << static_cast<int>(l->issue(i)->rule());
        }
        std::cout << std::endl;
    }
}

void printModel(libcellml::ModelPtr &model)
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
    for (size_t v = 0; v < component->variableCount(); v++) {
        std::cout << spacer << "  Variable[" << v << "] has name: '"
                  << component->variable(v)->name() << "'" << std::endl;
        if (component->variable(v)->initialValue() != "") {
            std::cout << spacer << "  Variable[" << v << "] has initial_value: '"
                      << component->variable(v)->initialValue() << "'"
                      << std::endl;
        }
        if (component->variable(v)->units() != nullptr) {
            std::cout << spacer << "  Variable[" << v << "] has units: '"
                      << component->variable(v)->units()->name() << "'" << std::endl;
        }
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

libcellml::ModelPtr createModelWithComponent(const std::string &name)
{
    libcellml::ModelPtr model = libcellml::Model::create();
    model->setName(name);
    createComponentInModel(model, "");
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
    c1->addVariable(v1);
    libcellml::VariablePtr v2 = libcellml::Variable::create();
    v2->setName(v2Name);
    c2->addVariable(v2);

    return model;
}

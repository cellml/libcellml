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

static const std::string INDENT = "    ";

void printComponent(const libcellml::ComponentPtr &component, size_t c, const std::string &indent, bool includeMaths)
{
    if (c == -1) {
        std::cout << "COMPONENT: '" << component->name() << "'";
    } else {
        std::cout << indent << "[" << c + 1 << "]: " << component->name();
    }

    if (component->id() != "") {
        std::cout << ", id: " << component->id();
    }

    std::cout << std::endl;
    std::cout << indent << INDENT << "VARIABLES: " << component->variableCount() << " variables" << std::endl;

    // Printing the variables within the component.
    for (size_t v = 0; v < component->variableCount(); ++v) {
        std::cout << indent << INDENT << INDENT;
        std::cout << "[" << v + 1 << "]: " << component->variable(v)->name();
        if (component->variable(v)->units() != nullptr) {
            std::cout << " [" << component->variable(v)->units()->name() << "]";
        }
        if (component->variable(v)->initialValue() != "") {
            std::cout << ", initial = " << component->variable(v)->initialValue();
        }
        std::cout << std::endl;
        if (component->variable(v)->equivalentVariableCount() > 0) {
            std::cout << indent << INDENT << INDENT << INDENT;
            std::string con = "  └──> ";
            for (size_t e = 0; e < component->variable(v)->equivalentVariableCount(); ++e) {
                auto ev = component->variable(v)->equivalentVariable(e);
                if (ev == nullptr) {
                    std::cout << "WHOOPS! Null equivalent variable!";
                    continue;
                }
                libcellml::ComponentPtr ev_parent = std::dynamic_pointer_cast<libcellml::Component>(ev->parent());
                if (ev_parent == nullptr) {
                    std::cout << "WHOOPS! Null parent component for equivalent variable!";
                    continue;
                }
                std::cout << con << ev_parent->name() << ":" << ev->name();
                if (ev->units() != nullptr) {
                    std::cout << " [" << ev->units()->name() << "]";
                }
                con = ", ";
            }
            std::cout << std::endl;
        }
    }

    // Print the maths within the component.
    if (includeMaths) {
        if (component->math() != "") {
            std::cout << indent << "  Maths in the component is:" << std::endl;
            std::cout << component->math() << std::endl;
        }
    }

    // Print the encapsulated components
    if (component->componentCount() > 0) {
        std::cout << indent << INDENT << "CHILD COMPONENTS: " << component->componentCount()
                  << " child components" << std::endl;
        std::string newIndent = indent + INDENT + INDENT;

        for (size_t c2 = 0; c2 < component->componentCount(); ++c2) {
            auto child = component->component(c2);
            printComponent(child, c2, newIndent, includeMaths);
        }
    }
}

void printComponent(const libcellml::ComponentPtr &component, bool includeMaths)
{
    printComponent(component, -1, {}, includeMaths);
}

void printModel(const libcellml::ModelPtr &model, bool includeMaths)
{
    std::cout << "MODEL: '" << model->name() << "'";
    if (model->id() != "") {
        std::cout << ", id: '" << model->id() << "'";
    }
    std::cout << std::endl;

    std::cout << INDENT << "UNITS: " << model->unitsCount() << " custom units" << std::endl;
    for (size_t u = 0; u < model->unitsCount(); ++u) {
        std::cout << INDENT << INDENT << "[" << u + 1 << "]: " << model->units(u)->name() << std::endl;
    }

    std::cout << INDENT << "COMPONENTS: " << model->componentCount() << " components" << std::endl;
    for (size_t c = 0; c < model->componentCount(); ++c) {
        auto component = model->component(c);
        printComponent(component, c, INDENT + INDENT, includeMaths);
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

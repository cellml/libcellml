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

void expectEqualErrors(const std::vector<std::string> &issues, const libcellml::LoggerPtr &logger)
{
    EXPECT_EQ(issues.size(), logger->errorCount());
    for (size_t i = 0; i < logger->errorCount() && i < issues.size(); ++i) {
        EXPECT_EQ(issues.at(i), logger->error(i)->description());
    }
}

void expectEqualIssues(const std::vector<std::string> &issues, const libcellml::LoggerPtr &logger)
{
    EXPECT_EQ(issues.size(), logger->issueCount());
    for (size_t i = 0; i < logger->issueCount() && i < issues.size(); ++i) {
        EXPECT_EQ(issues.at(i), logger->issue(i)->description());
    }
}

void expectEqualErrorsSpecificationHeadings(const std::vector<std::string> &issues,
                                            const std::vector<std::string> &specificationHeadings,
                                            const libcellml::LoggerPtr &logger)
{
    EXPECT_EQ(issues.size(), logger->errorCount());
    EXPECT_EQ(specificationHeadings.size(), logger->errorCount());
    for (size_t i = 0; i < logger->errorCount() && i < issues.size(); ++i) {
        EXPECT_EQ(issues.at(i), logger->error(i)->description());
        EXPECT_EQ(specificationHeadings.at(i), logger->error(i)->referenceHeading());
    }
}

void expectEqualErrorsCauses(const std::vector<std::string> &issues,
                             const std::vector<libcellml::Issue::Cause> &causes,
                             const libcellml::LoggerPtr &logger)
{
    EXPECT_EQ(issues.size(), logger->errorCount());
    EXPECT_EQ(causes.size(), logger->errorCount());
    for (size_t i = 0; i < logger->errorCount() && i < issues.size(); ++i) {
        EXPECT_EQ(issues.at(i), logger->error(i)->description());
        EXPECT_EQ(causes.at(i), logger->error(i)->cause());
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

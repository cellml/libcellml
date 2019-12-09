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

void printErrors(const libcellml::LoggerPtr &l, bool headings, bool kinds, bool rule)
{
    for (size_t i = 0; i < l->errorCount(); ++i) {
        std::cout << "Error " << std::setw(3) << i + 1 << ": ";
        std::cout << l->error(i)->description();
        if (headings) {
            std::cout << ", " << l->error(i)->specificationHeading();
        }
        if (kinds) {
            std::cout << ", " << static_cast<int>(l->error(i)->kind());
        }
        if (rule) {
            std::cout << ", " << static_cast<int>(l->error(i)->rule());
        }

        std::cout << std::endl;
    }
}

void expectEqualErrors(const std::vector<std::string> &errors, const libcellml::LoggerPtr &logger)
{
    EXPECT_EQ(errors.size(), logger->errorCount());
    for (size_t i = 0; i < logger->errorCount() && i < errors.size(); ++i) {
        EXPECT_EQ(errors.at(i), logger->error(i)->description());
    }
}

void expectEqualErrorsSpecificationHeadings(const std::vector<std::string> &errors,
                                            const std::vector<std::string> &specificationHeadings,
                                            const libcellml::LoggerPtr &logger)
{
    EXPECT_EQ(errors.size(), logger->errorCount());
    EXPECT_EQ(specificationHeadings.size(), logger->errorCount());
    for (size_t i = 0; i < logger->errorCount() && i < errors.size(); ++i) {
        EXPECT_EQ(errors.at(i), logger->error(i)->description());
        EXPECT_EQ(specificationHeadings.at(i), logger->error(i)->specificationHeading());
    }
}

void expectEqualErrorsKinds(const std::vector<std::string> &errors,
                            const std::vector<libcellml::Error::Kind> &kinds,
                            const libcellml::LoggerPtr &logger)
{
    EXPECT_EQ(errors.size(), logger->errorCount());
    EXPECT_EQ(kinds.size(), logger->errorCount());
    for (size_t i = 0; i < logger->errorCount() && i < errors.size(); ++i) {
        EXPECT_EQ(errors.at(i), logger->error(i)->description());
        EXPECT_EQ(kinds.at(i), logger->error(i)->kind());
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
    v1->setInterfaceType("public");
    c1->addVariable(v1);
    libcellml::VariablePtr v2 = libcellml::Variable::create();
    v2->setName(v2Name);
    v2->setInterfaceType("public");
    c2->addVariable(v2);

    return model;
}

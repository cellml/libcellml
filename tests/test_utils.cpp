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

#include "test_resources.h"
#include "test_utils.h"

#include "gtest/gtest.h"

#include <fstream>
#include <iostream>
#include <sstream>

std::string resourcePath(const std::string &resourceRelativePath)
{
    return std::string(TESTS_RESOURCE_LOCATION + "/").append(resourceRelativePath);
}

std::string fileContents(const std::string &fileName)
{
    std::ifstream file(resourcePath(fileName));
    std::stringstream buffer;

    buffer << file.rdbuf();

    return buffer.str();
}

void printErrors(const libcellml::Validator &v)
{
    for (size_t i = 0; i < v.errorCount(); ++i) {
        std::cout << v.error(i)->description() << ", " << v.error(i)->specificationHeading() << std::endl;
    }
}

void printErrors(const libcellml::Parser &p)
{
    for (size_t i = 0; i < p.errorCount(); ++i) {
        std::cout << p.error(i)->description() << ", " << std::endl;
        std::cout << static_cast<int>(p.error(i)->rule()) << std::endl;
        std::cout << p.error(i)->specificationHeading() << std::endl;
    }
}

void expectEqualErrors(const std::vector<std::string> &errors, const libcellml::Logger &logger)
{
    EXPECT_EQ(errors.size(), logger.errorCount());
    for (size_t i = 0; i < logger.errorCount() && i < errors.size(); ++i) {
        EXPECT_EQ(errors.at(i), logger.error(i)->description());
    }
}

void expectEqualErrorsSpecificationHeadings(const std::vector<std::string> &errors,
                                            const std::vector<std::string> &specificationHeadings,
                                            const libcellml::Logger &logger)
{
    EXPECT_EQ(errors.size(), logger.errorCount());
    EXPECT_EQ(specificationHeadings.size(), logger.errorCount());
    for (size_t i = 0; i < logger.errorCount() && i < errors.size(); ++i) {
        EXPECT_EQ(errors.at(i), logger.error(i)->description());
        EXPECT_EQ(specificationHeadings.at(i), logger.error(i)->specificationHeading());
    }
}

void expectEqualErrorsKinds(const std::vector<std::string> &errors,
                            const std::vector<libcellml::Error::Kind> &kinds,
                            const libcellml::Logger &logger)
{
    EXPECT_EQ(errors.size(), logger.errorCount());
    EXPECT_EQ(kinds.size(), logger.errorCount());
    for (size_t i = 0; i < logger.errorCount() && i < errors.size(); ++i) {
        EXPECT_EQ(errors.at(i), logger.error(i)->description());
        EXPECT_EQ(kinds.at(i), logger.error(i)->kind());
    }
}

libcellml::ModelPtr createModel(const std::string &name)
{
    libcellml::ModelPtr model = std::make_shared<libcellml::Model>();
    model->setName(name);
    return model;
}

libcellml::ModelPtr createModelWithComponent(const std::string &name)
{
    libcellml::ModelPtr model = std::make_shared<libcellml::Model>();
    model->setName(name);
    libcellml::ComponentPtr component = std::make_shared<libcellml::Component>();
    model->addComponent(component);
    return model;
}

libcellml::VariablePtr createVariableWithUnits(const std::string &name, const std::string &units)
{
    libcellml::VariablePtr v = std::make_shared<libcellml::Variable>();
    v->setName(name);
    v->setUnits(units);

    return v;
}

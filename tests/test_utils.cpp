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

#include <iostream>

void printErrors(const libcellml::Validator &v)
{
    for (size_t i = 0; i < v.errorCount(); ++i) {
        std::cout << v.getError(i)->getDescription() << ", " << v.getError(i)->getSpecificationHeading() << std::endl;
    }
}

void printErrors(const libcellml::Parser &p)
{
    for (size_t i = 0; i < p.errorCount(); ++i) {
        std::cout << p.getError(i)->getDescription() << ", " << std::endl;
        std::cout << static_cast<int>(p.getError(i)->getRule()) << std::endl;
        std::cout << p.getError(i)->getSpecificationHeading() << std::endl;
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

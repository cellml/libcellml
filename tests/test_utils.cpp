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

libcellml::ModelPtr createModel(const std::string name)
{
    libcellml::ModelPtr model = std::make_shared<libcellml::Model>();
    model->setName(name);
    return model;
}

libcellml::ModelPtr createModelWithComponent(const std::string name)
{
    libcellml::ModelPtr model = std::make_shared<libcellml::Model>();
    model->setName(name);
    libcellml::ComponentPtr component = std::make_shared<libcellml::Component>();
    model->addComponent(component);
    return model;
}

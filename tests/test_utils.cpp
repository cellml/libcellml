#include "test_resources.h"
#include "test_utils.h"

#include <fstream>
#include <iostream>
#include <sstream>

std::string fileContents(const std::string &fileName)
{
    std::ifstream file(TestResources::getResourcePath(fileName));
    std::stringstream buffer;

    buffer << file.rdbuf();

    return buffer.str();
}

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

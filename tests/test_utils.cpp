#include "test_utils.h"

#include <iostream>

void printErrors(const libcellml::Validator &v)
{
    for (size_t i = 0; i < v.errorCount(); ++i) {
        std::cout << v.getError(i)->description() << ", " << v.getError(i)->specificationHeading() << std::endl;
    }
}

void printErrors(const libcellml::Parser &p)
{
    for (size_t i = 0; i < p.errorCount(); ++i) {
        std::cout << p.getError(i)->description() << ", " << std::endl;
        std::cout << static_cast<int>(p.getError(i)->rule()) << std::endl;
        std::cout << p.getError(i)->specificationHeading() << std::endl;
    }
}

#include "test_utils.h"

#include <iostream>

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

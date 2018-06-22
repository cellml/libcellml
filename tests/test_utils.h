
#ifndef TEST_UTILS_H
#define TEST_UTILS_H

#include <libcellml>

void printErrors(const libcellml::Validator &v);
void printErrors(const libcellml::Parser &p);

#endif



#ifndef TEST_UTILS_H
#define TEST_UTILS_H

#include <libcellml>

std::string fileContents(const std::string &fileName);

void printErrors(const libcellml::Validator &v);
void printErrors(const libcellml::Parser &p);

#endif

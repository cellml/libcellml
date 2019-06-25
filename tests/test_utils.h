
#ifndef TEST_UTILS_H
#define TEST_UTILS_H

#include <libcellml>

void printErrors(const libcellml::Validator &v);
void printErrors(const libcellml::Parser &p);

void checkExpectedErrors(const std::vector<std::string> &expectedErrors, const libcellml::Logger &logger);

libcellml::ModelPtr createModel(const std::string &name = "");
libcellml::ModelPtr createModelWithComponent(const std::string &name = "");

#endif


#ifndef TEST_UTILS_H
#define TEST_UTILS_H

#include <libcellml>

void printErrors(const libcellml::Validator &v);
void printErrors(const libcellml::Parser &p);

libcellml::ModelPtr createModel(const std::string &name = "");
libcellml::ModelPtr createModelWithComponent(const std::string &name = "");

static const std::string emptyMath =
    "<math xmlns=\"http://www.w3.org/1998/Math/MathML\">\n"
    "</math>\n";

#endif

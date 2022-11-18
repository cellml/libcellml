
#include <fstream>
#include <string>

#include <libcellml/generatorprofile.h>

#include "profiletools.h"
#include "utilities.h"

int main()
{
    auto c_profile = libcellml::GeneratorProfile::create();
    auto py_profile = libcellml::GeneratorProfile::create(libcellml::GeneratorProfile::Profile::PYTHON);

    auto c_profile_repr = libcellml::formProfileRepresentation(c_profile);
    std::string c_sha1_value = libcellml::sha1(c_profile_repr);

    auto py_profile_repr = libcellml::formProfileRepresentation(py_profile);
    std::string py_sha1_value = libcellml::sha1(py_profile_repr);

    std::ofstream outFile("profilesha1values.cmake");

    outFile << "set(C_PROFILE_SHA1_VALUE " << c_sha1_value << ")" << std::endl;
    outFile << "set(PYTHON_PROFILE_SHA1_VALUE " << py_sha1_value << ")" << std::endl;

    outFile.close();

    return 0;
};

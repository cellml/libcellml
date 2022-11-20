
#include <fstream>
#include <string>

#include <libcellml/generatorprofile.h>

#include "profiletools.h"
#include "utilities.h"

int main()
{
    auto cProfile = libcellml::GeneratorProfile::create();
    auto pyProfile = libcellml::GeneratorProfile::create(libcellml::GeneratorProfile::Profile::PYTHON);

    auto cProfileRepr = libcellml::formProfileRepresentation(cProfile);
    std::string cSha1Value = libcellml::sha1(cProfileRepr);

    auto pyProfileRepr = libcellml::formProfileRepresentation(pyProfile);
    std::string pySha1Value = libcellml::sha1(pyProfileRepr);

    std::ofstream outFile("generatorprofilesha1values.cmake");

    outFile << "set(C_PROFILE_SHA1_VALUE " << cSha1Value << ")" << std::endl;
    outFile << "set(PYTHON_PROFILE_SHA1_VALUE " << pySha1Value << ")" << std::endl;

    outFile.close();

    return 0;
};

#include <array>
#include <iomanip>
#include <iostream>
#include <libcellml>
#include <sstream>
#include <string>

#include "../src/sha1.cpp.inl"

int usage(char *argv0)
{
    auto exec = std::string(argv0);

    std::cerr << "Usage: " << exec.substr(exec.find_last_of('/') + 1) << " C|Python" << std::endl;

    return 1;
}

int main(int argc, char *argv[])
{
    if (argc != 2) {
        return usage(argv[0]);
    }

    int profileType = 0;

    if (strcmp(argv[1], "C") == 0) {
        profileType = 1;
    } else if (strcmp(argv[1], "Python") == 0) {
        profileType = 2;
    }

    if (profileType == 0) {
        return usage(argv[0]);
    }

    auto generatorProfile = libcellml::GeneratorProfile::create();

    if (profileType == 2) {
        generatorProfile->setProfile(libcellml::GeneratorProfile::Profile::PYTHON);
    }

    std::cout << sha1(generatorProfile) << std::endl;

    return 0;
}

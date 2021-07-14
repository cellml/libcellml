#include <array>
#include <iomanip>
#include <iostream>
#include <libcellml>
#include <sstream>
#include <string>

#include "../src/sha1.cpp.inl"

int usage(const std::string &argv0)
{
    std::cerr << "Usage: " << argv0.substr(argv0.find_last_of('/') + 1) << " C|Python" << std::endl;

    return 1;
}

int main(int argc, char *argv[])
{
    auto argv0 = std::string(argv[0]);

    if (argc != 2) {
        return usage(argv0);
    }

    int profileType = 0;
    auto argv1 = std::string(argv[1]);

    if (argv1 == "C") {
        profileType = 1;
    } else if (argv1 == "Python") {
        profileType = 2;
    }

    if (profileType == 0) {
        return usage(argv0);
    }

    auto generatorProfile = libcellml::GeneratorProfile::create();

    if (profileType == 2) {
        generatorProfile->setProfile(libcellml::GeneratorProfile::Profile::PYTHON);
    }

    std::cout << sha1(generatorProfile) << std::endl;

    return 0;
}

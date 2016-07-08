/*
Copyright 2015 University of Auckland

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/

#include "gtest/gtest.h"

#include <algorithm>
#include <iostream>
#include <libcellml>
#include <sstream>
#include <fstream>
#include <vector>

// generated with test resource locations
#include "test_resources.h"

TEST(Parser, parseSineModelFromFile) {
    std::ifstream t(TestResources::getLocation(
                        TestResources::CELLML_SINE_MODEL_RESOURCE));
    std::stringstream buffer;
    buffer << t.rdbuf();
    std::vector<std::string> expectedErrors = {
        "Specification mandate value for attribute bearded.",
        "Opening and ending tag mismatch: Dwarf line 2 and ShortGuy.",
        "Opening and ending tag mismatch: Hobbit line 2 and EvenShorterGuy.",
        "Opening and ending tag mismatch: Wizard line 2 and SomeGuyWithAStaff.",
        "Opening and ending tag mismatch: Elf line 2 and fellows.",
        "Premature end of data in tag fellowship line 2.",
        "Could not get a valid XML root node from the provided input."
    };

    libcellml::Parser p(libcellml::Format::XML);
    p.parseModel(buffer.str());

    EXPECT_EQ(expectedErrors.size(), p.errorCount());
    for (size_t i = 0; i < p.errorCount(); ++i) {
        EXPECT_EQ(expectedErrors.at(i), p.getError(i)->getDescription());
    }
}


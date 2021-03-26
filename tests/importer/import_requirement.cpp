/*
Copyright libCellML Contributors

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

#include "test_resources.h"
#include "test_utils.h"

#include "gtest/gtest.h"

#include <libcellml>

TEST(ImportRequirement, create)
{
    auto model = libcellml::Model::create("model");
}

TEST(ImportRequirement, requirementsFixCircularRef)
{
    std::vector<std::string> expectedKeys = {
        "importExample2units.cellml",
        "importExample3.cellml",
        "importExample2components.cellml"};

    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("importer/requirements/importExample1.cellml"));
}

TEST(ImportRequirement, requirementsEncapsulationUnitsWithChildren)
{
    std::vector<std::string> expectedKeys = {
        "complicatedComponents.cellml",
        "components.cellml",
        "complicatedUnits.cellml",
        "units1.cellml",
        "units2.cellml"};

    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("importer/requirements/complicatedExample.cellml"));
}

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

#include "test_utils.h"

#include "gtest/gtest.h"

#include <libcellml>

TEST(AnalyserUnits, ci)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("analyser/units/ci.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    const std::vector<std::string> expectedIssues = {
        "The units in 'b = bCst' in component 'main' are not equivalent. The unit mismatch is second^-1.",
        "The units in 'c = cCst' in component 'main' are not equivalent. The unit mismatch is frog^-1.",
    };

    const std::vector<libcellml::CellmlElementType> expectedCellmlElementTypes = {
        libcellml::CellmlElementType::UNDEFINED,
        libcellml::CellmlElementType::UNDEFINED,
    };
    const std::vector<libcellml::Issue::Level> expectedLevels = {
        libcellml::Issue::Level::MESSAGE,
        libcellml::Issue::Level::MESSAGE,
    };
    const std::vector<libcellml::Issue::ReferenceRule> expectedReferenceRules = {
        libcellml::Issue::ReferenceRule::ANALYSER_UNITS,
        libcellml::Issue::ReferenceRule::ANALYSER_UNITS,
    };

    auto analyser = libcellml::Analyser::create();

    analyser->analyseModel(model);

    EXPECT_EQ_ISSUES_CELLMLELEMENTTYPES_LEVELS_REFERENCERULES(expectedIssues, expectedCellmlElementTypes, expectedLevels, expectedReferenceRules, analyser);
}

TEST(AnalyserUnits, cn)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("analyser/units/cn.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    const std::vector<std::string> expectedIssues = {
        "The units in 'b = 3.0' in component 'main' are not equivalent. The unit mismatch is second^-1.",
        "The units in 'c = 5.0' in component 'main' are not equivalent. The unit mismatch is frog^-1.",
        "The units in 'e = 9.0e3' in component 'main' are not equivalent. The unit mismatch is second^-1.",
        "The units in 'f = 11.0e5' in component 'main' are not equivalent. The unit mismatch is frog^-1.",
    };

    const std::vector<libcellml::CellmlElementType> expectedCellmlElementTypes = {
        libcellml::CellmlElementType::UNDEFINED,
        libcellml::CellmlElementType::UNDEFINED,
        libcellml::CellmlElementType::UNDEFINED,
        libcellml::CellmlElementType::UNDEFINED,
    };
    const std::vector<libcellml::Issue::Level> expectedLevels = {
        libcellml::Issue::Level::MESSAGE,
        libcellml::Issue::Level::MESSAGE,
        libcellml::Issue::Level::MESSAGE,
        libcellml::Issue::Level::MESSAGE,
    };
    const std::vector<libcellml::Issue::ReferenceRule> expectedReferenceRules = {
        libcellml::Issue::ReferenceRule::ANALYSER_UNITS,
        libcellml::Issue::ReferenceRule::ANALYSER_UNITS,
        libcellml::Issue::ReferenceRule::ANALYSER_UNITS,
        libcellml::Issue::ReferenceRule::ANALYSER_UNITS,
    };

    auto analyser = libcellml::Analyser::create();

    analyser->analyseModel(model);

    EXPECT_EQ_ISSUES_CELLMLELEMENTTYPES_LEVELS_REFERENCERULES(expectedIssues, expectedCellmlElementTypes, expectedLevels, expectedReferenceRules, analyser);
}

TEST(AnalyserUnits, piecewise)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("analyser/units/piecewise.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    const std::vector<std::string> expectedIssues = {
        "The units in 'b > 9.0' in equation 'b = (b > 9.0)?7.0:11.0' in component 'main' are not equivalent. The unit mismatch is metre^-1.",
        "The units in '(b > 9.0)?7.0:11.0' in equation 'b = (b > 9.0)?7.0:11.0' in component 'main' are not equivalent. The unit mismatch is mole^-1, second^1.",
        "The units in 'b = (b > 9.0)?7.0:11.0' in component 'main' are not equivalent. The unit mismatch is second^-1.",
        "The units in 'c > 15.0' in equation 'c = (c > 15.0)?13.0:17.0' in component 'main' are not equivalent. The unit mismatch is rooster^-1.",
        "The units in '(c > 15.0)?13.0:17.0' in equation 'c = (c > 15.0)?13.0:17.0' in component 'main' are not equivalent. The unit mismatch is dove^-1, frog^1.",
        "The units in 'c = (c > 15.0)?13.0:17.0' in component 'main' are not equivalent. The unit mismatch is frog^-1.",
    };

    const std::vector<libcellml::CellmlElementType> expectedCellmlElementTypes = {
        libcellml::CellmlElementType::UNDEFINED,
        libcellml::CellmlElementType::UNDEFINED,
        libcellml::CellmlElementType::UNDEFINED,
        libcellml::CellmlElementType::UNDEFINED,
        libcellml::CellmlElementType::UNDEFINED,
        libcellml::CellmlElementType::UNDEFINED,
    };
    const std::vector<libcellml::Issue::Level> expectedLevels = {
        libcellml::Issue::Level::MESSAGE,
        libcellml::Issue::Level::MESSAGE,
        libcellml::Issue::Level::MESSAGE,
        libcellml::Issue::Level::MESSAGE,
        libcellml::Issue::Level::MESSAGE,
        libcellml::Issue::Level::MESSAGE,
    };
    const std::vector<libcellml::Issue::ReferenceRule> expectedReferenceRules = {
        libcellml::Issue::ReferenceRule::ANALYSER_UNITS,
        libcellml::Issue::ReferenceRule::ANALYSER_UNITS,
        libcellml::Issue::ReferenceRule::ANALYSER_UNITS,
        libcellml::Issue::ReferenceRule::ANALYSER_UNITS,
        libcellml::Issue::ReferenceRule::ANALYSER_UNITS,
        libcellml::Issue::ReferenceRule::ANALYSER_UNITS,
    };

    auto analyser = libcellml::Analyser::create();

    analyser->analyseModel(model);

    EXPECT_EQ_ISSUES_CELLMLELEMENTTYPES_LEVELS_REFERENCERULES(expectedIssues, expectedCellmlElementTypes, expectedLevels, expectedReferenceRules, analyser);
}

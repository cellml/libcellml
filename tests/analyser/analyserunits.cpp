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

TEST(AnalyserUnits, builtInUnits)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("analyser/units/built_in_units.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    const std::vector<std::string> expectedIssues = {
        "The units in 'ampere = 1.0' in component 'main' are not equivalent. The unit mismatch is ampere^-1.",
        "The units in 'becquerel = 1.0' in component 'main' are not equivalent. The unit mismatch is second^1.",
        "The units in 'candela = 1.0' in component 'main' are not equivalent. The unit mismatch is candela^-1.",
        "The units in 'coulomb = 1.0' in component 'main' are not equivalent. The unit mismatch is ampere^-1 x second^-1.",
        "The units in 'farad = 1.0' in component 'main' are not equivalent. The unit mismatch is ampere^-2 x kilogram^1 x metre^2 x second^-4.",
        "The units in 'gram = 1.0' in component 'main' are not equivalent and have a multiplier mismatch. The unit mismatch is kilogram^-1 and the multiplier mismatch is 10^3.",
        "The units in 'gray = 1.0' in component 'main' are not equivalent. The unit mismatch is metre^-2 x second^2.",
        "The units in 'henry = 1.0' in component 'main' are not equivalent. The unit mismatch is ampere^2 x kilogram^-1 x metre^-2 x second^2.",
        "The units in 'hertz = 1.0' in component 'main' are not equivalent. The unit mismatch is second^1.",
        "The units in 'joule = 1.0' in component 'main' are not equivalent. The unit mismatch is kilogram^-1 x metre^-2 x second^2.",
        "The units in 'katal = 1.0' in component 'main' are not equivalent. The unit mismatch is mole^-1 x second^1.",
        "The units in 'kelvin = 1.0' in component 'main' are not equivalent. The unit mismatch is kelvin^-1.",
        "The units in 'kilogram = 1.0' in component 'main' are not equivalent. The unit mismatch is kilogram^-1.",
        "The units in 'litre = 1.0' in component 'main' are not equivalent and have a multiplier mismatch. The unit mismatch is metre^-3 and the multiplier mismatch is 10^3.",
        "The units in 'lumen = 1.0' in component 'main' are not equivalent. The unit mismatch is candela^-1.",
        "The units in 'lux = 1.0' in component 'main' are not equivalent. The unit mismatch is candela^-1 x metre^2.",
        "The units in 'metre = 1.0' in component 'main' are not equivalent. The unit mismatch is metre^-1.",
        "The units in 'mole = 1.0' in component 'main' are not equivalent. The unit mismatch is mole^-1.",
        "The units in 'newton = 1.0' in component 'main' are not equivalent. The unit mismatch is kilogram^-1 x metre^-1 x second^2.",
        "The units in 'ohm = 1.0' in component 'main' are not equivalent. The unit mismatch is ampere^2 x kilogram^-1 x metre^-2 x second^3.",
        "The units in 'pascal = 1.0' in component 'main' are not equivalent. The unit mismatch is kilogram^-1 x metre^1 x second^2.",
        "The units in 'second = 1.0' in component 'main' are not equivalent. The unit mismatch is second^-1.",
        "The units in 'siemens = 1.0' in component 'main' are not equivalent. The unit mismatch is ampere^-2 x kilogram^1 x metre^2 x second^-3.",
        "The units in 'sievert = 1.0' in component 'main' are not equivalent. The unit mismatch is metre^-2 x second^2.",
        "The units in 'tesla = 1.0' in component 'main' are not equivalent. The unit mismatch is ampere^1 x kilogram^-1 x second^2.",
        "The units in 'volt = 1.0' in component 'main' are not equivalent. The unit mismatch is ampere^1 x kilogram^-1 x metre^-2 x second^3.",
        "The units in 'watt = 1.0' in component 'main' are not equivalent. The unit mismatch is kilogram^-1 x metre^-2 x second^3.",
        "The units in 'weber = 1.0' in component 'main' are not equivalent. The unit mismatch is ampere^1 x kilogram^-1 x metre^-2 x second^2.",
    };
    const std::vector<libcellml::CellmlElementType> expectedCellmlElementTypes = {
        libcellml::CellmlElementType::UNDEFINED,
        libcellml::CellmlElementType::UNDEFINED,
        libcellml::CellmlElementType::UNDEFINED,
        libcellml::CellmlElementType::UNDEFINED,
        libcellml::CellmlElementType::UNDEFINED,
        libcellml::CellmlElementType::UNDEFINED,
        libcellml::CellmlElementType::UNDEFINED,
        libcellml::CellmlElementType::UNDEFINED,
        libcellml::CellmlElementType::UNDEFINED,
        libcellml::CellmlElementType::UNDEFINED,
        libcellml::CellmlElementType::UNDEFINED,
        libcellml::CellmlElementType::UNDEFINED,
        libcellml::CellmlElementType::UNDEFINED,
        libcellml::CellmlElementType::UNDEFINED,
        libcellml::CellmlElementType::UNDEFINED,
        libcellml::CellmlElementType::UNDEFINED,
        libcellml::CellmlElementType::UNDEFINED,
        libcellml::CellmlElementType::UNDEFINED,
        libcellml::CellmlElementType::UNDEFINED,
        libcellml::CellmlElementType::UNDEFINED,
        libcellml::CellmlElementType::UNDEFINED,
        libcellml::CellmlElementType::UNDEFINED,
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
        libcellml::Issue::Level::MESSAGE,
        libcellml::Issue::Level::MESSAGE,
        libcellml::Issue::Level::MESSAGE,
        libcellml::Issue::Level::MESSAGE,
        libcellml::Issue::Level::MESSAGE,
        libcellml::Issue::Level::MESSAGE,
        libcellml::Issue::Level::MESSAGE,
        libcellml::Issue::Level::MESSAGE,
        libcellml::Issue::Level::MESSAGE,
        libcellml::Issue::Level::MESSAGE,
        libcellml::Issue::Level::MESSAGE,
        libcellml::Issue::Level::MESSAGE,
        libcellml::Issue::Level::MESSAGE,
        libcellml::Issue::Level::MESSAGE,
        libcellml::Issue::Level::MESSAGE,
        libcellml::Issue::Level::MESSAGE,
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
        libcellml::Issue::ReferenceRule::ANALYSER_UNITS,
        libcellml::Issue::ReferenceRule::ANALYSER_UNITS,
        libcellml::Issue::ReferenceRule::ANALYSER_UNITS,
        libcellml::Issue::ReferenceRule::ANALYSER_UNITS,
        libcellml::Issue::ReferenceRule::ANALYSER_UNITS,
        libcellml::Issue::ReferenceRule::ANALYSER_UNITS,
        libcellml::Issue::ReferenceRule::ANALYSER_UNITS,
        libcellml::Issue::ReferenceRule::ANALYSER_UNITS,
        libcellml::Issue::ReferenceRule::ANALYSER_UNITS,
        libcellml::Issue::ReferenceRule::ANALYSER_UNITS,
        libcellml::Issue::ReferenceRule::ANALYSER_UNITS,
        libcellml::Issue::ReferenceRule::ANALYSER_UNITS,
        libcellml::Issue::ReferenceRule::ANALYSER_UNITS,
        libcellml::Issue::ReferenceRule::ANALYSER_UNITS,
        libcellml::Issue::ReferenceRule::ANALYSER_UNITS,
        libcellml::Issue::ReferenceRule::ANALYSER_UNITS,
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

TEST(AnalyserUnits, ci)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("analyser/units/ci.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    const std::vector<std::string> expectedIssues = {
        "The units in 'b = bCst' in component 'main' are not equivalent. The unit mismatch is second^-1.",
        "The units in 'c = cCst' in component 'main' are not equivalent. The unit mismatch is ampere^1 x kilogram^-1 x metre^-2 x second^3.",
        "The units in 'd = dCst' in component 'main' are not equivalent. The unit mismatch is frog^-1.",
    };
    const std::vector<libcellml::CellmlElementType> expectedCellmlElementTypes = {
        libcellml::CellmlElementType::UNDEFINED,
        libcellml::CellmlElementType::UNDEFINED,
        libcellml::CellmlElementType::UNDEFINED,
    };
    const std::vector<libcellml::Issue::Level> expectedLevels = {
        libcellml::Issue::Level::MESSAGE,
        libcellml::Issue::Level::MESSAGE,
        libcellml::Issue::Level::MESSAGE,
    };
    const std::vector<libcellml::Issue::ReferenceRule> expectedReferenceRules = {
        libcellml::Issue::ReferenceRule::ANALYSER_UNITS,
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
        "The units in 'c = 5.0' in component 'main' are not equivalent. The unit mismatch is ampere^1 x kilogram^-1 x metre^-2 x second^3.",
        "The units in 'd = 7.0' in component 'main' are not equivalent. The unit mismatch is frog^-1.",
        "The units in 'f = 11.0e3' in component 'main' are not equivalent. The unit mismatch is second^-1.",
        "The units in 'g = 13.0e5' in component 'main' are not equivalent. The unit mismatch is ampere^1 x kilogram^-1 x metre^-2 x second^3.",
        "The units in 'h = 15.0e7' in component 'main' are not equivalent. The unit mismatch is frog^-1.",
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

TEST(AnalyserUnits, piecewise)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("analyser/units/piecewise.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    const std::vector<std::string> expectedIssues = {
        "The units in 'bLHS > 13.0' in equation 'bLHS = (bLHS > 13.0)?11.0:(bLHS > 17.0)?15.0:19.0' in component 'main' are not equivalent. The unit mismatch is metre^-1.",
        "The units in 'bLHS > 17.0' in equation 'bLHS = (bLHS > 13.0)?11.0:(bLHS > 17.0)?15.0:19.0' in component 'main' are not equivalent. The unit mismatch is candela^-1.",
        "The units in 'bLHS = (bLHS > 13.0)?11.0:(bLHS > 17.0)?15.0:19.0' in component 'main' are not equivalent. The unit mismatches are ampere^-1, mole^-1 and second^-1.",
        "The units in 'bRHS > 13.0' in equation '(bRHS > 13.0)?11.0:(bRHS > 17.0)?15.0:19.0 = bRHS' in component 'main' are not equivalent. The unit mismatch is metre^-1.",
        "The units in 'bRHS > 17.0' in equation '(bRHS > 13.0)?11.0:(bRHS > 17.0)?15.0:19.0 = bRHS' in component 'main' are not equivalent. The unit mismatch is candela^-1.",
        "The units in '(bRHS > 13.0)?11.0:(bRHS > 17.0)?15.0:19.0 = bRHS' in component 'main' are not equivalent. The unit mismatches are ampere^1, mole^1 and second^1.",
        "The units in 'cLHS > 23.0' in equation 'cLHS = (cLHS > 23.0)?21.0:(cLHS > 27.0)?25.0:29.0' in component 'main' are not equivalent. The unit mismatch is rooster^-1.",
        "The units in 'cLHS > 27.0' in equation 'cLHS = (cLHS > 23.0)?21.0:(cLHS > 27.0)?25.0:29.0' in component 'main' are not equivalent. The unit mismatch is cat^-1.",
        "The units in 'cLHS = (cLHS > 23.0)?21.0:(cLHS > 27.0)?25.0:29.0' in component 'main' are not equivalent. The unit mismatches are dog^-1, dove^-1 and frog^-1.",
        "The units in 'cRHS > 23.0' in equation '(cRHS > 23.0)?21.0:(cRHS > 27.0)?25.0:29.0 = cRHS' in component 'main' are not equivalent. The unit mismatch is rooster^-1.",
        "The units in 'cRHS > 27.0' in equation '(cRHS > 23.0)?21.0:(cRHS > 27.0)?25.0:29.0 = cRHS' in component 'main' are not equivalent. The unit mismatch is cat^-1.",
        "The units in '(cRHS > 23.0)?21.0:(cRHS > 27.0)?25.0:29.0 = cRHS' in component 'main' are not equivalent. The unit mismatches are dog^1, dove^1 and frog^1.",
        "The units in 'dLHS > 23.0' in equation '(dLHS > 23.0)?21.0:(dLHS > 27.0)?25.0:29.0 = (dRHS > 33.0)?31.0:(dRHS > 37.0)?35.0:39.0' in component 'main' are not equivalent. The unit mismatch is metre^-1.",
        "The units in 'dLHS > 27.0' in equation '(dLHS > 23.0)?21.0:(dLHS > 27.0)?25.0:29.0 = (dRHS > 33.0)?31.0:(dRHS > 37.0)?35.0:39.0' in component 'main' are not equivalent. The unit mismatch is candela^-1.",
        "The units in 'dRHS > 33.0' in equation '(dLHS > 23.0)?21.0:(dLHS > 27.0)?25.0:29.0 = (dRHS > 33.0)?31.0:(dRHS > 37.0)?35.0:39.0' in component 'main' are not equivalent. The unit mismatch is rooster^-1.",
        "The units in 'dRHS > 37.0' in equation '(dLHS > 23.0)?21.0:(dLHS > 27.0)?25.0:29.0 = (dRHS > 33.0)?31.0:(dRHS > 37.0)?35.0:39.0' in component 'main' are not equivalent. The unit mismatch is cat^-1.",
        "The units in '(dLHS > 23.0)?21.0:(dLHS > 27.0)?25.0:29.0 = (dRHS > 33.0)?31.0:(dRHS > 37.0)?35.0:39.0' in component 'main' are not equivalent. The unit mismatches are ampere^1 x dog^-1, ampere^1 x dove^-1, ampere^1 x frog^-1, dog^-1 x mole^1, dog^-1 x second^1, dove^-1 x mole^1, dove^-1 x second^1, frog^-1 x mole^1 and frog^-1 x second^1.",
        "The unit of '43.0' in '(43.0)?41.0' in equation 'eLHS = (43.0)?41.0:45.0' in component 'main' is not dimensionless. The unit mismatch is second^1.",
        "The unit of '43.0' in '(43.0)?41.0' in equation '(43.0)?41.0:45.0 = eRHS' in component 'main' is not dimensionless. The unit mismatch is second^1.",
        "Variable 'dLHS' in component 'main' is unused.",
        "Variable 'dRHS' in component 'main' is unused.",
    };
    const std::vector<libcellml::CellmlElementType> expectedCellmlElementTypes = {
        libcellml::CellmlElementType::UNDEFINED,
        libcellml::CellmlElementType::UNDEFINED,
        libcellml::CellmlElementType::UNDEFINED,
        libcellml::CellmlElementType::UNDEFINED,
        libcellml::CellmlElementType::UNDEFINED,
        libcellml::CellmlElementType::UNDEFINED,
        libcellml::CellmlElementType::UNDEFINED,
        libcellml::CellmlElementType::UNDEFINED,
        libcellml::CellmlElementType::UNDEFINED,
        libcellml::CellmlElementType::UNDEFINED,
        libcellml::CellmlElementType::UNDEFINED,
        libcellml::CellmlElementType::UNDEFINED,
        libcellml::CellmlElementType::UNDEFINED,
        libcellml::CellmlElementType::UNDEFINED,
        libcellml::CellmlElementType::UNDEFINED,
        libcellml::CellmlElementType::UNDEFINED,
        libcellml::CellmlElementType::UNDEFINED,
        libcellml::CellmlElementType::UNDEFINED,
        libcellml::CellmlElementType::UNDEFINED,
        libcellml::CellmlElementType::VARIABLE,
        libcellml::CellmlElementType::VARIABLE,
    };
    const std::vector<libcellml::Issue::Level> expectedLevels = {
        libcellml::Issue::Level::MESSAGE,
        libcellml::Issue::Level::MESSAGE,
        libcellml::Issue::Level::MESSAGE,
        libcellml::Issue::Level::MESSAGE,
        libcellml::Issue::Level::MESSAGE,
        libcellml::Issue::Level::MESSAGE,
        libcellml::Issue::Level::MESSAGE,
        libcellml::Issue::Level::MESSAGE,
        libcellml::Issue::Level::MESSAGE,
        libcellml::Issue::Level::MESSAGE,
        libcellml::Issue::Level::MESSAGE,
        libcellml::Issue::Level::MESSAGE,
        libcellml::Issue::Level::MESSAGE,
        libcellml::Issue::Level::MESSAGE,
        libcellml::Issue::Level::MESSAGE,
        libcellml::Issue::Level::MESSAGE,
        libcellml::Issue::Level::MESSAGE,
        libcellml::Issue::Level::MESSAGE,
        libcellml::Issue::Level::MESSAGE,
        libcellml::Issue::Level::ERROR,
        libcellml::Issue::Level::ERROR,
    };
    const std::vector<libcellml::Issue::ReferenceRule> expectedReferenceRules = {
        libcellml::Issue::ReferenceRule::ANALYSER_UNITS,
        libcellml::Issue::ReferenceRule::ANALYSER_UNITS,
        libcellml::Issue::ReferenceRule::ANALYSER_UNITS,
        libcellml::Issue::ReferenceRule::ANALYSER_UNITS,
        libcellml::Issue::ReferenceRule::ANALYSER_UNITS,
        libcellml::Issue::ReferenceRule::ANALYSER_UNITS,
        libcellml::Issue::ReferenceRule::ANALYSER_UNITS,
        libcellml::Issue::ReferenceRule::ANALYSER_UNITS,
        libcellml::Issue::ReferenceRule::ANALYSER_UNITS,
        libcellml::Issue::ReferenceRule::ANALYSER_UNITS,
        libcellml::Issue::ReferenceRule::ANALYSER_UNITS,
        libcellml::Issue::ReferenceRule::ANALYSER_UNITS,
        libcellml::Issue::ReferenceRule::ANALYSER_UNITS,
        libcellml::Issue::ReferenceRule::ANALYSER_UNITS,
        libcellml::Issue::ReferenceRule::ANALYSER_UNITS,
        libcellml::Issue::ReferenceRule::ANALYSER_UNITS,
        libcellml::Issue::ReferenceRule::ANALYSER_UNITS,
        libcellml::Issue::ReferenceRule::ANALYSER_UNITS,
        libcellml::Issue::ReferenceRule::ANALYSER_UNITS,
        libcellml::Issue::ReferenceRule::ANALYSER_VARIABLE_UNUSED,
        libcellml::Issue::ReferenceRule::ANALYSER_VARIABLE_UNUSED,
    };

    auto analyser = libcellml::Analyser::create();

    analyser->analyseModel(model);

    EXPECT_EQ_ISSUES_CELLMLELEMENTTYPES_LEVELS_REFERENCERULES(expectedIssues, expectedCellmlElementTypes, expectedLevels, expectedReferenceRules, analyser);
}

TEST(AnalyserUnits, eq)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("analyser/units/eq.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    const std::vector<std::string> expectedIssues = {
        "The units in 'bCst == 3.0' in equation 'b = bCst == 3.0' in component 'main' are not equivalent. The unit mismatch is second^1.",
        "The units in 'cCst == 5.0' in equation 'c = cCst == 5.0' in component 'main' are not equivalent. The unit mismatch is ampere^-1 x kilogram^1 x metre^2 x second^-3.",
        "The units in 'dCst == 7.0' in equation 'd = dCst == 7.0' in component 'main' are not equivalent. The unit mismatch is frog^1.",
    };
    const std::vector<libcellml::CellmlElementType> expectedCellmlElementTypes = {
        libcellml::CellmlElementType::UNDEFINED,
        libcellml::CellmlElementType::UNDEFINED,
        libcellml::CellmlElementType::UNDEFINED,
    };
    const std::vector<libcellml::Issue::Level> expectedLevels = {
        libcellml::Issue::Level::MESSAGE,
        libcellml::Issue::Level::MESSAGE,
        libcellml::Issue::Level::MESSAGE,
    };
    const std::vector<libcellml::Issue::ReferenceRule> expectedReferenceRules = {
        libcellml::Issue::ReferenceRule::ANALYSER_UNITS,
        libcellml::Issue::ReferenceRule::ANALYSER_UNITS,
        libcellml::Issue::ReferenceRule::ANALYSER_UNITS,
    };

    auto analyser = libcellml::Analyser::create();

    analyser->analyseModel(model);

    EXPECT_EQ_ISSUES_CELLMLELEMENTTYPES_LEVELS_REFERENCERULES(expectedIssues, expectedCellmlElementTypes, expectedLevels, expectedReferenceRules, analyser);
}

TEST(AnalyserUnits, neq)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("analyser/units/neq.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    const std::vector<std::string> expectedIssues = {
        "The units in 'bCst != 3.0' in equation 'b = bCst != 3.0' in component 'main' are not equivalent. The unit mismatch is second^1.",
        "The units in 'cCst != 5.0' in equation 'c = cCst != 5.0' in component 'main' are not equivalent. The unit mismatch is ampere^-1 x kilogram^1 x metre^2 x second^-3.",
        "The units in 'dCst != 7.0' in equation 'd = dCst != 7.0' in component 'main' are not equivalent. The unit mismatch is frog^1.",
    };
    const std::vector<libcellml::CellmlElementType> expectedCellmlElementTypes = {
        libcellml::CellmlElementType::UNDEFINED,
        libcellml::CellmlElementType::UNDEFINED,
        libcellml::CellmlElementType::UNDEFINED,
    };
    const std::vector<libcellml::Issue::Level> expectedLevels = {
        libcellml::Issue::Level::MESSAGE,
        libcellml::Issue::Level::MESSAGE,
        libcellml::Issue::Level::MESSAGE,
    };
    const std::vector<libcellml::Issue::ReferenceRule> expectedReferenceRules = {
        libcellml::Issue::ReferenceRule::ANALYSER_UNITS,
        libcellml::Issue::ReferenceRule::ANALYSER_UNITS,
        libcellml::Issue::ReferenceRule::ANALYSER_UNITS,
    };

    auto analyser = libcellml::Analyser::create();

    analyser->analyseModel(model);

    EXPECT_EQ_ISSUES_CELLMLELEMENTTYPES_LEVELS_REFERENCERULES(expectedIssues, expectedCellmlElementTypes, expectedLevels, expectedReferenceRules, analyser);
}

TEST(AnalyserUnits, lt)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("analyser/units/lt.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    const std::vector<std::string> expectedIssues = {
        "The units in 'bCst < 3.0' in equation 'b = bCst < 3.0' in component 'main' are not equivalent. The unit mismatch is second^1.",
        "The units in 'cCst < 5.0' in equation 'c = cCst < 5.0' in component 'main' are not equivalent. The unit mismatch is ampere^-1 x kilogram^1 x metre^2 x second^-3.",
        "The units in 'dCst < 7.0' in equation 'd = dCst < 7.0' in component 'main' are not equivalent. The unit mismatch is frog^1.",
    };
    const std::vector<libcellml::CellmlElementType> expectedCellmlElementTypes = {
        libcellml::CellmlElementType::UNDEFINED,
        libcellml::CellmlElementType::UNDEFINED,
        libcellml::CellmlElementType::UNDEFINED,
    };
    const std::vector<libcellml::Issue::Level> expectedLevels = {
        libcellml::Issue::Level::MESSAGE,
        libcellml::Issue::Level::MESSAGE,
        libcellml::Issue::Level::MESSAGE,
    };
    const std::vector<libcellml::Issue::ReferenceRule> expectedReferenceRules = {
        libcellml::Issue::ReferenceRule::ANALYSER_UNITS,
        libcellml::Issue::ReferenceRule::ANALYSER_UNITS,
        libcellml::Issue::ReferenceRule::ANALYSER_UNITS,
    };

    auto analyser = libcellml::Analyser::create();

    analyser->analyseModel(model);

    EXPECT_EQ_ISSUES_CELLMLELEMENTTYPES_LEVELS_REFERENCERULES(expectedIssues, expectedCellmlElementTypes, expectedLevels, expectedReferenceRules, analyser);
}

TEST(AnalyserUnits, leq)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("analyser/units/leq.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    const std::vector<std::string> expectedIssues = {
        "The units in 'bCst <= 3.0' in equation 'b = bCst <= 3.0' in component 'main' are not equivalent. The unit mismatch is second^1.",
        "The units in 'cCst <= 5.0' in equation 'c = cCst <= 5.0' in component 'main' are not equivalent. The unit mismatch is ampere^-1 x kilogram^1 x metre^2 x second^-3.",
        "The units in 'dCst <= 7.0' in equation 'd = dCst <= 7.0' in component 'main' are not equivalent. The unit mismatch is frog^1.",
    };
    const std::vector<libcellml::CellmlElementType> expectedCellmlElementTypes = {
        libcellml::CellmlElementType::UNDEFINED,
        libcellml::CellmlElementType::UNDEFINED,
        libcellml::CellmlElementType::UNDEFINED,
    };
    const std::vector<libcellml::Issue::Level> expectedLevels = {
        libcellml::Issue::Level::MESSAGE,
        libcellml::Issue::Level::MESSAGE,
        libcellml::Issue::Level::MESSAGE,
    };
    const std::vector<libcellml::Issue::ReferenceRule> expectedReferenceRules = {
        libcellml::Issue::ReferenceRule::ANALYSER_UNITS,
        libcellml::Issue::ReferenceRule::ANALYSER_UNITS,
        libcellml::Issue::ReferenceRule::ANALYSER_UNITS,
    };

    auto analyser = libcellml::Analyser::create();

    analyser->analyseModel(model);

    EXPECT_EQ_ISSUES_CELLMLELEMENTTYPES_LEVELS_REFERENCERULES(expectedIssues, expectedCellmlElementTypes, expectedLevels, expectedReferenceRules, analyser);
}

TEST(AnalyserUnits, gt)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("analyser/units/gt.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    const std::vector<std::string> expectedIssues = {
        "The units in 'bCst > 3.0' in equation 'b = bCst > 3.0' in component 'main' are not equivalent. The unit mismatch is second^1.",
        "The units in 'cCst > 5.0' in equation 'c = cCst > 5.0' in component 'main' are not equivalent. The unit mismatch is ampere^-1 x kilogram^1 x metre^2 x second^-3.",
        "The units in 'dCst > 7.0' in equation 'd = dCst > 7.0' in component 'main' are not equivalent. The unit mismatch is frog^1.",
    };
    const std::vector<libcellml::CellmlElementType> expectedCellmlElementTypes = {
        libcellml::CellmlElementType::UNDEFINED,
        libcellml::CellmlElementType::UNDEFINED,
        libcellml::CellmlElementType::UNDEFINED,
    };
    const std::vector<libcellml::Issue::Level> expectedLevels = {
        libcellml::Issue::Level::MESSAGE,
        libcellml::Issue::Level::MESSAGE,
        libcellml::Issue::Level::MESSAGE,
    };
    const std::vector<libcellml::Issue::ReferenceRule> expectedReferenceRules = {
        libcellml::Issue::ReferenceRule::ANALYSER_UNITS,
        libcellml::Issue::ReferenceRule::ANALYSER_UNITS,
        libcellml::Issue::ReferenceRule::ANALYSER_UNITS,
    };

    auto analyser = libcellml::Analyser::create();

    analyser->analyseModel(model);

    EXPECT_EQ_ISSUES_CELLMLELEMENTTYPES_LEVELS_REFERENCERULES(expectedIssues, expectedCellmlElementTypes, expectedLevels, expectedReferenceRules, analyser);
}

TEST(AnalyserUnits, geq)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("analyser/units/geq.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    const std::vector<std::string> expectedIssues = {
        "The units in 'bCst >= 3.0' in equation 'b = bCst >= 3.0' in component 'main' are not equivalent. The unit mismatch is second^1.",
        "The units in 'cCst >= 5.0' in equation 'c = cCst >= 5.0' in component 'main' are not equivalent. The unit mismatch is ampere^-1 x kilogram^1 x metre^2 x second^-3.",
        "The units in 'dCst >= 7.0' in equation 'd = dCst >= 7.0' in component 'main' are not equivalent. The unit mismatch is frog^1.",
    };
    const std::vector<libcellml::CellmlElementType> expectedCellmlElementTypes = {
        libcellml::CellmlElementType::UNDEFINED,
        libcellml::CellmlElementType::UNDEFINED,
        libcellml::CellmlElementType::UNDEFINED,
    };
    const std::vector<libcellml::Issue::Level> expectedLevels = {
        libcellml::Issue::Level::MESSAGE,
        libcellml::Issue::Level::MESSAGE,
        libcellml::Issue::Level::MESSAGE,
    };
    const std::vector<libcellml::Issue::ReferenceRule> expectedReferenceRules = {
        libcellml::Issue::ReferenceRule::ANALYSER_UNITS,
        libcellml::Issue::ReferenceRule::ANALYSER_UNITS,
        libcellml::Issue::ReferenceRule::ANALYSER_UNITS,
    };

    auto analyser = libcellml::Analyser::create();

    analyser->analyseModel(model);

    EXPECT_EQ_ISSUES_CELLMLELEMENTTYPES_LEVELS_REFERENCERULES(expectedIssues, expectedCellmlElementTypes, expectedLevels, expectedReferenceRules, analyser);
}

TEST(AnalyserUnits, andOp)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("analyser/units/and.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    const std::vector<std::string> expectedIssues = {
        "The unit of 'bCst' in 'bCst && 3.0' in equation 'b = bCst && 3.0' in component 'main' is not dimensionless. The unit mismatch is second^1.",
        "The unit of 'cCst' in 'cCst && 5.0' in equation 'c = cCst && 5.0' in component 'main' is not dimensionless. The unit mismatch is ampere^-1 x kilogram^1 x metre^2 x second^-3.",
        "The unit of 'dCst' in 'dCst && 7.0' in equation 'd = dCst && 7.0' in component 'main' is not dimensionless. The unit mismatch is frog^1.",
        "The units of 'eCst' and '9.0' in 'eCst && 9.0' in equation 'e = eCst && 9.0' in component 'main' are not dimensionless. The unit mismatches are second^1 and ampere^-1 x kilogram^1 x metre^2 x second^-3.",
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

TEST(AnalyserUnits, orOp)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("analyser/units/or.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    const std::vector<std::string> expectedIssues = {
        "The unit of 'bCst' in 'bCst || 3.0' in equation 'b = bCst || 3.0' in component 'main' is not dimensionless. The unit mismatch is second^1.",
        "The unit of 'cCst' in 'cCst || 5.0' in equation 'c = cCst || 5.0' in component 'main' is not dimensionless. The unit mismatch is ampere^-1 x kilogram^1 x metre^2 x second^-3.",
        "The unit of 'dCst' in 'dCst || 7.0' in equation 'd = dCst || 7.0' in component 'main' is not dimensionless. The unit mismatch is frog^1.",
        "The units of 'eCst' and '9.0' in 'eCst || 9.0' in equation 'e = eCst || 9.0' in component 'main' are not dimensionless. The unit mismatches are second^1 and ampere^-1 x kilogram^1 x metre^2 x second^-3.",
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

TEST(AnalyserUnits, xorOp)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("analyser/units/xor.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    const std::vector<std::string> expectedIssues = {
        "The unit of 'bCst' in 'xor(bCst, 3.0)' in equation 'b = xor(bCst, 3.0)' in component 'main' is not dimensionless. The unit mismatch is second^1.",
        "The unit of 'cCst' in 'xor(cCst, 5.0)' in equation 'c = xor(cCst, 5.0)' in component 'main' is not dimensionless. The unit mismatch is ampere^-1 x kilogram^1 x metre^2 x second^-3.",
        "The unit of 'dCst' in 'xor(dCst, 7.0)' in equation 'd = xor(dCst, 7.0)' in component 'main' is not dimensionless. The unit mismatch is frog^1.",
        "The units of 'eCst' and '9.0' in 'xor(eCst, 9.0)' in equation 'e = xor(eCst, 9.0)' in component 'main' are not dimensionless. The unit mismatches are second^1 and ampere^-1 x kilogram^1 x metre^2 x second^-3.",
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

TEST(AnalyserUnits, notOp)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("analyser/units/not.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    const std::vector<std::string> expectedIssues = {
        "The unit of 'bCst' in '!bCst' in equation 'b = !bCst' in component 'main' is not dimensionless. The unit mismatch is second^1.",
        "The unit of 'cCst' in '!cCst' in equation 'c = !cCst' in component 'main' is not dimensionless. The unit mismatch is ampere^-1 x kilogram^1 x metre^2 x second^-3.",
        "The unit of 'dCst' in '!dCst' in equation 'd = !dCst' in component 'main' is not dimensionless. The unit mismatch is frog^1.",
    };
    const std::vector<libcellml::CellmlElementType> expectedCellmlElementTypes = {
        libcellml::CellmlElementType::UNDEFINED,
        libcellml::CellmlElementType::UNDEFINED,
        libcellml::CellmlElementType::UNDEFINED,
    };
    const std::vector<libcellml::Issue::Level> expectedLevels = {
        libcellml::Issue::Level::MESSAGE,
        libcellml::Issue::Level::MESSAGE,
        libcellml::Issue::Level::MESSAGE,
    };
    const std::vector<libcellml::Issue::ReferenceRule> expectedReferenceRules = {
        libcellml::Issue::ReferenceRule::ANALYSER_UNITS,
        libcellml::Issue::ReferenceRule::ANALYSER_UNITS,
        libcellml::Issue::ReferenceRule::ANALYSER_UNITS,
    };

    auto analyser = libcellml::Analyser::create();

    analyser->analyseModel(model);

    EXPECT_EQ_ISSUES_CELLMLELEMENTTYPES_LEVELS_REFERENCERULES(expectedIssues, expectedCellmlElementTypes, expectedLevels, expectedReferenceRules, analyser);
}

TEST(AnalyserUnits, plus)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("analyser/units/plus.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    const std::vector<std::string> expectedIssues = {
        "The units in 'bCst+3.0' in equation 'b = bCst+3.0' in component 'main' are not equivalent. The unit mismatch is second^1.",
        "The units in 'b = bCst+3.0' in component 'main' are not equivalent. The unit mismatch is second^-1.",
        "The units in 'cCst+5.0' in equation 'c = cCst+5.0' in component 'main' are not equivalent. The unit mismatch is ampere^-1 x kilogram^1 x metre^2 x second^-3.",
        "The units in 'c = cCst+5.0' in component 'main' are not equivalent. The unit mismatch is ampere^1 x kilogram^-1 x metre^-2 x second^3.",
        "The units in 'dCst+7.0' in equation 'd = dCst+7.0' in component 'main' are not equivalent. The unit mismatch is frog^1.",
        "The units in 'd = dCst+7.0' in component 'main' are not equivalent. The unit mismatch is frog^-1.",
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

TEST(AnalyserUnits, minus)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("analyser/units/minus.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    const std::vector<std::string> expectedIssues = {
        "The units in 'bCst-3.0' in equation 'b = bCst-3.0' in component 'main' are not equivalent. The unit mismatch is second^1.",
        "The units in 'b = bCst-3.0' in component 'main' are not equivalent. The unit mismatch is second^-1.",
        "The units in 'cCst-5.0' in equation 'c = cCst-5.0' in component 'main' are not equivalent. The unit mismatch is ampere^-1 x kilogram^1 x metre^2 x second^-3.",
        "The units in 'c = cCst-5.0' in component 'main' are not equivalent. The unit mismatch is ampere^1 x kilogram^-1 x metre^-2 x second^3.",
        "The units in 'dCst-7.0' in equation 'd = dCst-7.0' in component 'main' are not equivalent. The unit mismatch is frog^1.",
        "The units in 'd = dCst-7.0' in component 'main' are not equivalent. The unit mismatch is frog^-1.",
        "The units in 'f = -fCst' in component 'main' are not equivalent. The unit mismatch is second^-1.",
        "The units in 'g = -gCst' in component 'main' are not equivalent. The unit mismatch is ampere^1 x kilogram^-1 x metre^-2 x second^3.",
        "The units in 'h = -hCst' in component 'main' are not equivalent. The unit mismatch is frog^-1.",
    };
    const std::vector<libcellml::CellmlElementType> expectedCellmlElementTypes = {
        libcellml::CellmlElementType::UNDEFINED,
        libcellml::CellmlElementType::UNDEFINED,
        libcellml::CellmlElementType::UNDEFINED,
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
        libcellml::Issue::ReferenceRule::ANALYSER_UNITS,
        libcellml::Issue::ReferenceRule::ANALYSER_UNITS,
        libcellml::Issue::ReferenceRule::ANALYSER_UNITS,
    };

    auto analyser = libcellml::Analyser::create();

    analyser->analyseModel(model);

    EXPECT_EQ_ISSUES_CELLMLELEMENTTYPES_LEVELS_REFERENCERULES(expectedIssues, expectedCellmlElementTypes, expectedLevels, expectedReferenceRules, analyser);
}

TEST(AnalyserUnits, times)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("analyser/units/times.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    const std::vector<std::string> expectedIssues = {
        "The units in 'b = bCst*3.0' in component 'main' are not equivalent. The unit mismatch is second^-1.",
        "The units in 'c = cCst*5.0' in component 'main' are not equivalent. The unit mismatch is ampere^1 x kilogram^-1 x metre^-2 x second^3.",
        "The units in 'd = dCst*7.0' in component 'main' are not equivalent. The unit mismatch is frog^-1.",
        "The units in 'e = eCst*9.0' in component 'main' are not equivalent. The unit mismatch is ampere^-1 x kilogram^1 x metre^2 x second^-3.",
        "The units in 'f = fCst*11.0' in component 'main' are not equivalent. The unit mismatch is ampere^-1 x kilogram^1 x metre^2 x second^-3.",
        "The units in 'g = gCst*13.0' in component 'main' are not equivalent. The unit mismatch is ampere^-1 x kilogram^1 x metre^2 x second^-3.",
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

TEST(AnalyserUnits, divide)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("analyser/units/divide.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    const std::vector<std::string> expectedIssues = {
        "The units in 'b = bCst/3.0' in component 'main' are not equivalent. The unit mismatch is second^-1.",
        "The units in 'c = cCst/5.0' in component 'main' are not equivalent. The unit mismatch is ampere^1 x kilogram^-1 x metre^-2 x second^3.",
        "The units in 'd = dCst/7.0' in component 'main' are not equivalent. The unit mismatch is frog^-1.",
        "The units in 'e = eCst/9.0' in component 'main' are not equivalent. The unit mismatch is ampere^1 x kilogram^-1 x metre^-2 x second^3.",
        "The units in 'f = fCst/11.0' in component 'main' are not equivalent. The unit mismatch is ampere^1 x kilogram^-1 x metre^-2 x second^3.",
        "The units in 'g = gCst/13.0' in component 'main' are not equivalent. The unit mismatch is ampere^1 x kilogram^-1 x metre^-2 x second^3.",
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

TEST(AnalyserUnits, power)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("analyser/units/power.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    const std::vector<std::string> expectedIssues = {
        "The units in 'b = pow(bCst, 3.0)' in component 'main' are not equivalent. The unit mismatch is second^-3.",
        "The units in 'c = pow(cCst, 5.0)' in component 'main' are not equivalent. The unit mismatch is ampere^5 x kilogram^-5 x metre^-10 x second^15.",
        "The units in 'd = pow(dCst, 7.0)' in component 'main' are not equivalent. The unit mismatch is frog^-7.",
        "The unit of '9.0' in 'pow(eCst, 9.0)' in equation 'e = pow(eCst, 9.0)' in component 'main' is not dimensionless. The unit mismatch is ampere^-1 x kilogram^1 x metre^2 x second^-3.",
        "The units in 'e = pow(eCst, 9.0)' in component 'main' are not equivalent. The unit mismatch is second^-9.",
    };
    const std::vector<libcellml::CellmlElementType> expectedCellmlElementTypes = {
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
    };
    const std::vector<libcellml::Issue::ReferenceRule> expectedReferenceRules = {
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

TEST(AnalyserUnits, root)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("analyser/units/root.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    const std::vector<std::string> expectedIssues = {
        "The units in 'b = pow(bCst, 1.0/3.0)' in component 'main' are not equivalent. The unit mismatch is second^-0.333333.",
        "The units in 'c = pow(cCst, 1.0/5.0)' in component 'main' are not equivalent. The unit mismatch is ampere^0.2 x kilogram^-0.2 x metre^-0.4 x second^0.6.",
        "The units in 'd = pow(dCst, 1.0/7.0)' in component 'main' are not equivalent. The unit mismatch is frog^-0.142857.",
        "The unit of '9.0' in 'pow(eCst, 1.0/9.0)' in equation 'e = pow(eCst, 1.0/9.0)' in component 'main' is not dimensionless. The unit mismatch is ampere^-1 x kilogram^1 x metre^2 x second^-3.",
        "The units in 'e = pow(eCst, 1.0/9.0)' in component 'main' are not equivalent. The unit mismatch is second^-0.111111.",
    };
    const std::vector<libcellml::CellmlElementType> expectedCellmlElementTypes = {
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
    };
    const std::vector<libcellml::Issue::ReferenceRule> expectedReferenceRules = {
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

TEST(AnalyserUnits, abs)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("analyser/units/abs.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    const std::vector<std::string> expectedIssues = {
        "The units in 'b = abs(3.0)' in component 'main' are not equivalent. The unit mismatch is second^-1.",
        "The units in 'c = abs(5.0)' in component 'main' are not equivalent. The unit mismatch is ampere^1 x kilogram^-1 x metre^-2 x second^3.",
        "The units in 'd = abs(7.0)' in component 'main' are not equivalent. The unit mismatch is frog^-1.",
    };
    const std::vector<libcellml::CellmlElementType> expectedCellmlElementTypes = {
        libcellml::CellmlElementType::UNDEFINED,
        libcellml::CellmlElementType::UNDEFINED,
        libcellml::CellmlElementType::UNDEFINED,
    };
    const std::vector<libcellml::Issue::Level> expectedLevels = {
        libcellml::Issue::Level::MESSAGE,
        libcellml::Issue::Level::MESSAGE,
        libcellml::Issue::Level::MESSAGE,
    };
    const std::vector<libcellml::Issue::ReferenceRule> expectedReferenceRules = {
        libcellml::Issue::ReferenceRule::ANALYSER_UNITS,
        libcellml::Issue::ReferenceRule::ANALYSER_UNITS,
        libcellml::Issue::ReferenceRule::ANALYSER_UNITS,
    };

    auto analyser = libcellml::Analyser::create();

    analyser->analyseModel(model);

    EXPECT_EQ_ISSUES_CELLMLELEMENTTYPES_LEVELS_REFERENCERULES(expectedIssues, expectedCellmlElementTypes, expectedLevels, expectedReferenceRules, analyser);
}

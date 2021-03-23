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
        "The units in 'ampere = 1.0' in component 'main' are not the same. 'ampere' is in 'ampere' while '1.0' is dimensionless.",
        "The units in 'becquerel = 1.0' in component 'main' are not the same. 'becquerel' is in 'becquerel' while '1.0' is dimensionless.",
        "The units in 'candela = 1.0' in component 'main' are not the same. 'candela' is in 'candela' while '1.0' is dimensionless.",
        "The units in 'coulomb = 1.0' in component 'main' are not the same. 'coulomb' is in 'coulomb' while '1.0' is dimensionless.",
        "The units in 'farad = 1.0' in component 'main' are not the same. 'farad' is in 'farad' while '1.0' is dimensionless.",
        "The units in 'gram = 1.0' in component 'main' are not the same. 'gram' is in 'gram' while '1.0' is dimensionless.",
        "The units in 'gray = 1.0' in component 'main' are not the same. 'gray' is in 'gray' while '1.0' is dimensionless.",
        "The units in 'henry = 1.0' in component 'main' are not the same. 'henry' is in 'henry' while '1.0' is dimensionless.",
        "The units in 'hertz = 1.0' in component 'main' are not the same. 'hertz' is in 'hertz' while '1.0' is dimensionless.",
        "The units in 'joule = 1.0' in component 'main' are not the same. 'joule' is in 'joule' while '1.0' is dimensionless.",
        "The units in 'katal = 1.0' in component 'main' are not the same. 'katal' is in 'katal' while '1.0' is dimensionless.",
        "The units in 'kelvin = 1.0' in component 'main' are not the same. 'kelvin' is in 'kelvin' while '1.0' is dimensionless.",
        "The units in 'kilogram = 1.0' in component 'main' are not the same. 'kilogram' is in 'kilogram' while '1.0' is dimensionless.",
        "The units in 'litre = 1.0' in component 'main' are not the same. 'litre' is in 'litre' while '1.0' is dimensionless.",
        "The units in 'lumen = 1.0' in component 'main' are not the same. 'lumen' is in 'lumen' while '1.0' is dimensionless.",
        "The units in 'lux = 1.0' in component 'main' are not the same. 'lux' is in 'lux' while '1.0' is dimensionless.",
        "The units in 'metre = 1.0' in component 'main' are not the same. 'metre' is in 'metre' while '1.0' is dimensionless.",
        "The units in 'mole = 1.0' in component 'main' are not the same. 'mole' is in 'mole' while '1.0' is dimensionless.",
        "The units in 'newton = 1.0' in component 'main' are not the same. 'newton' is in 'newton' while '1.0' is dimensionless.",
        "The units in 'ohm = 1.0' in component 'main' are not the same. 'ohm' is in 'ohm' while '1.0' is dimensionless.",
        "The units in 'pascal = 1.0' in component 'main' are not the same. 'pascal' is in 'pascal' while '1.0' is dimensionless.",
        "The units in 'second = 1.0' in component 'main' are not the same. 'second' is in 'second' while '1.0' is dimensionless.",
        "The units in 'siemens = 1.0' in component 'main' are not the same. 'siemens' is in 'siemens' while '1.0' is dimensionless.",
        "The units in 'sievert = 1.0' in component 'main' are not the same. 'sievert' is in 'sievert' while '1.0' is dimensionless.",
        "The units in 'tesla = 1.0' in component 'main' are not the same. 'tesla' is in 'tesla' while '1.0' is dimensionless.",
        "The units in 'volt = 1.0' in component 'main' are not the same. 'volt' is in 'volt' while '1.0' is dimensionless.",
        "The units in 'watt = 1.0' in component 'main' are not the same. 'watt' is in 'watt' while '1.0' is dimensionless.",
        "The units in 'weber = 1.0' in component 'main' are not the same. 'weber' is in 'weber' while '1.0' is dimensionless.",
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
        "The units in 'b = bCst' in component 'main' are not the same. 'b' is dimensionless while 'bCst' is in 'second'.",
        "The units in 'c = cCst' in component 'main' are not the same. 'c' is dimensionless while 'cCst' is in 'volt'.",
        "The units in 'd = dCst' in component 'main' are not the same. 'd' is dimensionless while 'dCst' is in 'frog'.",
        "The units in 'e = eCst' in component 'main' are not the same. 'e' is dimensionless while 'eCst' is in 'metre_per_second'.",
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

TEST(AnalyserUnits, cn)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("analyser/units/cn.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    const std::vector<std::string> expectedIssues = {
        "The units in 'b = 3.0' in component 'main' are not the same. 'b' is dimensionless while '3.0' is in 'second'.",
        "The units in 'c = 5.0' in component 'main' are not the same. 'c' is dimensionless while '5.0' is in 'volt'.",
        "The units in 'd = 7.0' in component 'main' are not the same. 'd' is dimensionless while '7.0' is in 'frog'.",
        "The units in 'e = 9.0' in component 'main' are not the same. 'e' is dimensionless while '9.0' is in 'metre_per_second'.",
        "The units in 'g = 13.0e3' in component 'main' are not the same. 'g' is dimensionless while '13.0e3' is in 'second'.",
        "The units in 'h = 15.0e5' in component 'main' are not the same. 'h' is dimensionless while '15.0e5' is in 'volt'.",
        "The units in 'i = 17.0e7' in component 'main' are not the same. 'i' is dimensionless while '17.0e7' is in 'frog'.",
        "The units in 'j = 19.0e9' in component 'main' are not the same. 'j' is dimensionless while '19.0e9' is in 'metre_per_second'.",
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
        "The units in 'b > 9.0' in '(b > 9.0)?7.0' in '(b > 9.0)?7.0:11.0' in equation 'b = (b > 9.0)?7.0:11.0' in component 'main' are not the same. 'b' is dimensionless while '9.0' is in 'second'.",
        "The units in 'c > 15.0' in '(c > 15.0)?13.0' in '(c > 15.0)?13.0:17.0' in equation 'c = (c > 15.0)?13.0:17.0' in component 'main' are not the same. 'c' is dimensionless while '15.0' is in 'volt'.",
        "The units in 'd > 21.0' in '(d > 21.0)?19.0' in '(d > 21.0)?19.0:23.0' in equation 'd = (d > 21.0)?19.0:23.0' in component 'main' are not the same. 'd' is dimensionless while '21.0' is in 'frog'.",
        "The units in 'e > 27.0' in '(e > 27.0)?25.0' in '(e > 27.0)?25.0:29.0' in equation 'e = (e > 27.0)?25.0:29.0' in component 'main' are not the same. 'e' is dimensionless while '27.0' is in 'metre_per_second'.",
        "The units in 'f = (f > 33.0)?31.0:(f > 37.0)?35.0:(f > 41.0)?39.0:(f > 45.0)?43.0:(f > 49.0)?47.0:51.0' in component 'main' are not the same. 'f' is dimensionless while '(f > 33.0)?31.0:(f > 37.0)?35.0:(f > 41.0)?39.0:(f > 45.0)?43.0:(f > 49.0)?47.0:51.0' is in 'second', 'volt', 'frog' and 'metre_per_second'.",
        "The unit of '55.0' in '(55.0)?53.0' in '(55.0)?53.0:57.0' in equation 'g = (55.0)?53.0:57.0' in component 'main' is not dimensionless. '55.0' is in 'second'.",
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

TEST(AnalyserUnits, eq)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("analyser/units/eq.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    const std::vector<std::string> expectedIssues = {
        "The units in 'bCst == 3.0' in equation 'b = bCst == 3.0' in component 'main' are not the same. 'bCst' is in 'second' while '3.0' is dimensionless.",
        "The units in 'cCst == 5.0' in equation 'c = cCst == 5.0' in component 'main' are not the same. 'cCst' is in 'volt' while '5.0' is dimensionless.",
        "The units in 'dCst == 7.0' in equation 'd = dCst == 7.0' in component 'main' are not the same. 'dCst' is in 'frog' while '7.0' is dimensionless.",
        "The units in 'eCst == 9.0' in equation 'e = eCst == 9.0' in component 'main' are not the same. 'eCst' is in 'metre_per_second' while '9.0' is dimensionless.",
        "The units in 'fCst == 11.0' in equation 'f = fCst == 11.0' in component 'main' are not the same. 'fCst' is in 'second' while '11.0' is in 'metre_per_second'.",
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

TEST(AnalyserUnits, neq)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("analyser/units/neq.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    const std::vector<std::string> expectedIssues = {
        "The units in 'bCst != 3.0' in equation 'b = bCst != 3.0' in component 'main' are not the same. 'bCst' is in 'second' while '3.0' is dimensionless.",
        "The units in 'cCst != 5.0' in equation 'c = cCst != 5.0' in component 'main' are not the same. 'cCst' is in 'volt' while '5.0' is dimensionless.",
        "The units in 'dCst != 7.0' in equation 'd = dCst != 7.0' in component 'main' are not the same. 'dCst' is in 'frog' while '7.0' is dimensionless.",
        "The units in 'eCst != 9.0' in equation 'e = eCst != 9.0' in component 'main' are not the same. 'eCst' is in 'metre_per_second' while '9.0' is dimensionless.",
        "The units in 'fCst != 11.0' in equation 'f = fCst != 11.0' in component 'main' are not the same. 'fCst' is in 'second' while '11.0' is in 'metre_per_second'.",
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

TEST(AnalyserUnits, lt)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("analyser/units/lt.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    const std::vector<std::string> expectedIssues = {
        "The units in 'bCst < 3.0' in equation 'b = bCst < 3.0' in component 'main' are not the same. 'bCst' is in 'second' while '3.0' is dimensionless.",
        "The units in 'cCst < 5.0' in equation 'c = cCst < 5.0' in component 'main' are not the same. 'cCst' is in 'volt' while '5.0' is dimensionless.",
        "The units in 'dCst < 7.0' in equation 'd = dCst < 7.0' in component 'main' are not the same. 'dCst' is in 'frog' while '7.0' is dimensionless.",
        "The units in 'eCst < 9.0' in equation 'e = eCst < 9.0' in component 'main' are not the same. 'eCst' is in 'metre_per_second' while '9.0' is dimensionless.",
        "The units in 'fCst < 11.0' in equation 'f = fCst < 11.0' in component 'main' are not the same. 'fCst' is in 'second' while '11.0' is in 'metre_per_second'.",
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

TEST(AnalyserUnits, leq)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("analyser/units/leq.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    const std::vector<std::string> expectedIssues = {
        "The units in 'bCst <= 3.0' in equation 'b = bCst <= 3.0' in component 'main' are not the same. 'bCst' is in 'second' while '3.0' is dimensionless.",
        "The units in 'cCst <= 5.0' in equation 'c = cCst <= 5.0' in component 'main' are not the same. 'cCst' is in 'volt' while '5.0' is dimensionless.",
        "The units in 'dCst <= 7.0' in equation 'd = dCst <= 7.0' in component 'main' are not the same. 'dCst' is in 'frog' while '7.0' is dimensionless.",
        "The units in 'eCst <= 9.0' in equation 'e = eCst <= 9.0' in component 'main' are not the same. 'eCst' is in 'metre_per_second' while '9.0' is dimensionless.",
        "The units in 'fCst <= 11.0' in equation 'f = fCst <= 11.0' in component 'main' are not the same. 'fCst' is in 'second' while '11.0' is in 'metre_per_second'.",
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

TEST(AnalyserUnits, gt)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("analyser/units/gt.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    const std::vector<std::string> expectedIssues = {
        "The units in 'bCst > 3.0' in equation 'b = bCst > 3.0' in component 'main' are not the same. 'bCst' is in 'second' while '3.0' is dimensionless.",
        "The units in 'cCst > 5.0' in equation 'c = cCst > 5.0' in component 'main' are not the same. 'cCst' is in 'volt' while '5.0' is dimensionless.",
        "The units in 'dCst > 7.0' in equation 'd = dCst > 7.0' in component 'main' are not the same. 'dCst' is in 'frog' while '7.0' is dimensionless.",
        "The units in 'eCst > 9.0' in equation 'e = eCst > 9.0' in component 'main' are not the same. 'eCst' is in 'metre_per_second' while '9.0' is dimensionless.",
        "The units in 'fCst > 11.0' in equation 'f = fCst > 11.0' in component 'main' are not the same. 'fCst' is in 'second' while '11.0' is in 'metre_per_second'.",
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

TEST(AnalyserUnits, geq)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("analyser/units/geq.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    const std::vector<std::string> expectedIssues = {
        "The units in 'bCst >= 3.0' in equation 'b = bCst >= 3.0' in component 'main' are not the same. 'bCst' is in 'second' while '3.0' is dimensionless.",
        "The units in 'cCst >= 5.0' in equation 'c = cCst >= 5.0' in component 'main' are not the same. 'cCst' is in 'volt' while '5.0' is dimensionless.",
        "The units in 'dCst >= 7.0' in equation 'd = dCst >= 7.0' in component 'main' are not the same. 'dCst' is in 'frog' while '7.0' is dimensionless.",
        "The units in 'eCst >= 9.0' in equation 'e = eCst >= 9.0' in component 'main' are not the same. 'eCst' is in 'metre_per_second' while '9.0' is dimensionless.",
        "The units in 'fCst >= 11.0' in equation 'f = fCst >= 11.0' in component 'main' are not the same. 'fCst' is in 'second' while '11.0' is in 'metre_per_second'.",
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

TEST(AnalyserUnits, andOp)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("analyser/units/and.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    const std::vector<std::string> expectedIssues = {
        "The unit of 'bCst' in 'bCst && 3.0' in equation 'b = bCst && 3.0' in component 'main' is not dimensionless. 'bCst' is in 'second'.",
        "The unit of 'cCst' in 'cCst && 5.0' in equation 'c = cCst && 5.0' in component 'main' is not dimensionless. 'cCst' is in 'volt'.",
        "The unit of 'dCst' in 'dCst && 7.0' in equation 'd = dCst && 7.0' in component 'main' is not dimensionless. 'dCst' is in 'frog'.",
        "The unit of 'eCst' in 'eCst && 9.0' in equation 'e = eCst && 9.0' in component 'main' is not dimensionless. 'eCst' is in 'metre_per_second'.",
        "The units of 'fCst' and '11.0' in 'fCst && 11.0' in equation 'f = fCst && 11.0' in component 'main' are not dimensionless. 'fCst' is in 'second' while '11.0' is in 'metre_per_second'.",
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

TEST(AnalyserUnits, orOp)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("analyser/units/or.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    const std::vector<std::string> expectedIssues = {
        "The unit of 'bCst' in 'bCst || 3.0' in equation 'b = bCst || 3.0' in component 'main' is not dimensionless. 'bCst' is in 'second'.",
        "The unit of 'cCst' in 'cCst || 5.0' in equation 'c = cCst || 5.0' in component 'main' is not dimensionless. 'cCst' is in 'volt'.",
        "The unit of 'dCst' in 'dCst || 7.0' in equation 'd = dCst || 7.0' in component 'main' is not dimensionless. 'dCst' is in 'frog'.",
        "The unit of 'eCst' in 'eCst || 9.0' in equation 'e = eCst || 9.0' in component 'main' is not dimensionless. 'eCst' is in 'metre_per_second'.",
        "The units of 'fCst' and '11.0' in 'fCst || 11.0' in equation 'f = fCst || 11.0' in component 'main' are not dimensionless. 'fCst' is in 'second' while '11.0' is in 'metre_per_second'.",
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

TEST(AnalyserUnits, xorOp)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("analyser/units/xor.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    const std::vector<std::string> expectedIssues = {
        "The unit of 'bCst' in 'xor(bCst, 3.0)' in equation 'b = xor(bCst, 3.0)' in component 'main' is not dimensionless. 'bCst' is in 'second'.",
        "The unit of 'cCst' in 'xor(cCst, 5.0)' in equation 'c = xor(cCst, 5.0)' in component 'main' is not dimensionless. 'cCst' is in 'volt'.",
        "The unit of 'dCst' in 'xor(dCst, 7.0)' in equation 'd = xor(dCst, 7.0)' in component 'main' is not dimensionless. 'dCst' is in 'frog'.",
        "The unit of 'eCst' in 'xor(eCst, 9.0)' in equation 'e = xor(eCst, 9.0)' in component 'main' is not dimensionless. 'eCst' is in 'metre_per_second'.",
        "The units of 'fCst' and '11.0' in 'xor(fCst, 11.0)' in equation 'f = xor(fCst, 11.0)' in component 'main' are not dimensionless. 'fCst' is in 'second' while '11.0' is in 'metre_per_second'.",
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

TEST(AnalyserUnits, notOp)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("analyser/units/not.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    const std::vector<std::string> expectedIssues = {
        "The unit of 'bCst' in '!bCst' in equation 'b = !bCst' in component 'main' is not dimensionless. 'bCst' is in 'second'.",
        "The unit of 'cCst' in '!cCst' in equation 'c = !cCst' in component 'main' is not dimensionless. 'cCst' is in 'volt'.",
        "The unit of 'dCst' in '!dCst' in equation 'd = !dCst' in component 'main' is not dimensionless. 'dCst' is in 'frog'.",
        "The unit of 'eCst' in '!eCst' in equation 'e = !eCst' in component 'main' is not dimensionless. 'eCst' is in 'metre_per_second'.",
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

TEST(AnalyserUnits, plus)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("analyser/units/plus.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    const std::vector<std::string> expectedIssues = {
        "The units in 'bCst+3.0' in equation 'b = bCst+3.0' in component 'main' are not the same. 'bCst' is in 'second' while '3.0' is dimensionless.",
        "The units in 'cCst+5.0' in equation 'c = cCst+5.0' in component 'main' are not the same. 'cCst' is in 'volt' while '5.0' is dimensionless.",
        "The units in 'dCst+7.0' in equation 'd = dCst+7.0' in component 'main' are not the same. 'dCst' is in 'frog' while '7.0' is dimensionless.",
        "The units in 'eCst+9.0' in equation 'e = eCst+9.0' in component 'main' are not the same. 'eCst' is in 'metre_per_second' while '9.0' is dimensionless.",
        "The units in 'fCst+11.0' in equation 'f = fCst+11.0' in component 'main' are not the same. 'fCst' is in 'second' while '11.0' is in 'metre_per_second'.",
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

TEST(AnalyserUnits, minus)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("analyser/units/minus.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    const std::vector<std::string> expectedIssues = {
        "The units in 'b = -bCst' in component 'main' are not the same. 'b' is dimensionless while '-bCst' is in 'second'.",
        "The units in 'c = -cCst' in component 'main' are not the same. 'c' is dimensionless while '-cCst' is in 'volt'.",
        "The units in 'd = -dCst' in component 'main' are not the same. 'd' is dimensionless while '-dCst' is in 'frog'.",
        "The units in 'e = -eCst' in component 'main' are not the same. 'e' is dimensionless while '-eCst' is in 'metre_per_second'.",
        "The units in 'gCst-3.0' in equation 'g = gCst-3.0' in component 'main' are not the same. 'gCst' is in 'second' while '3.0' is dimensionless.",
        "The units in 'hCst-5.0' in equation 'h = hCst-5.0' in component 'main' are not the same. 'hCst' is in 'volt' while '5.0' is dimensionless.",
        "The units in 'iCst-7.0' in equation 'i = iCst-7.0' in component 'main' are not the same. 'iCst' is in 'frog' while '7.0' is dimensionless.",
        "The units in 'jCst-9.0' in equation 'j = jCst-9.0' in component 'main' are not the same. 'jCst' is in 'metre_per_second' while '9.0' is dimensionless.",
        "The units in 'kCst-11.0' in equation 'k = kCst-11.0' in component 'main' are not the same. 'kCst' is in 'second' while '11.0' is in 'metre_per_second'.",
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
        "The units in 'b = bCst*3.0' in component 'main' are not the same. 'b' is dimensionless while 'bCst*3.0' is in 'second'.",
        "The units in 'c = cCst*5.0' in component 'main' are not the same. 'c' is dimensionless while 'cCst*5.0' is in 'volt'.",
        "The units in 'd = dCst*7.0' in component 'main' are not the same. 'd' is dimensionless while 'dCst*7.0' is in 'frog'.",
        "The units in 'e = eCst*9.0' in component 'main' are not the same. 'e' is dimensionless while 'eCst*9.0' is in 'metre_per_second'.",
        "The units in 'f = fCst*11.0' in component 'main' are not the same. 'f' is dimensionless while 'fCst*11.0' is in 'metre_per_second x second'.",
        "The units in 'g = gCst*13.0' in component 'main' are not the same. 'g' is in 'second_by_volt' while 'gCst*13.0' is in 'second'.",
        "The units in 'h = hCst*15.0' in component 'main' are not the same. 'h' is in 'volt_by_volt' while 'hCst*15.0' is in 'volt'.",
        "The units in 'i = iCst*17.0' in component 'main' are not the same. 'i' is in 'frog_by_volt' while 'iCst*17.0' is in 'frog'.",
        "The units in 'j = jCst*19.0' in component 'main' are not the same. 'j' is in 'metre_per_second_by_volt' while 'jCst*19.0' is in 'metre_per_second'.",
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

TEST(AnalyserUnits, divide)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("analyser/units/divide.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    const std::vector<std::string> expectedIssues = {
        "The units in 'b = bCst/3.0' in component 'main' are not the same. 'b' is dimensionless while 'bCst/3.0' is in 'second'.",
        "The units in 'c = cCst/5.0' in component 'main' are not the same. 'c' is dimensionless while 'cCst/5.0' is in 'volt'.",
        "The units in 'd = dCst/7.0' in component 'main' are not the same. 'd' is dimensionless while 'dCst/7.0' is in 'frog'.",
        "The units in 'e = eCst/9.0' in component 'main' are not the same. 'e' is dimensionless while 'eCst/9.0' is in 'metre_per_second'.",
        "The units in 'f = fCst/11.0' in component 'main' are not the same. 'f' is dimensionless while 'fCst/11.0' is in 'metre_per_second^-1 x second'.",
        "The units in 'g = gCst/13.0' in component 'main' are not the same. 'g' is in 'second_per_volt' while 'gCst/13.0' is in 'second'.",
        "The units in 'h = hCst/15.0' in component 'main' are not the same. 'h' is in 'volt_per_volt' while 'hCst/15.0' is in 'volt'.",
        "The units in 'i = iCst/17.0' in component 'main' are not the same. 'i' is in 'frog_per_volt' while 'iCst/17.0' is in 'frog'.",
        "The units in 'j = jCst/19.0' in component 'main' are not the same. 'j' is in 'metre_per_second_per_volt' while 'jCst/19.0' is in 'metre_per_second'.",
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

TEST(AnalyserUnits, power)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("analyser/units/power.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    const std::vector<std::string> expectedIssues = {
        "The unit of '3.0' in 'pow(bCst, 3.0)' in equation 'b = pow(bCst, 3.0)' in component 'main' is not dimensionless. '3.0' is in 'second'.",
        "The unit of '5.0' in 'pow(cCst, 5.0)' in equation 'c = pow(cCst, 5.0)' in component 'main' is not dimensionless. '5.0' is in 'volt'.",
        "The unit of '7.0' in 'pow(dCst, 7.0)' in equation 'd = pow(dCst, 7.0)' in component 'main' is not dimensionless. '7.0' is in 'frog'.",
        "The unit of '9.0' in 'pow(eCst, 9.0)' in equation 'e = pow(eCst, 9.0)' in component 'main' is not dimensionless. '9.0' is in 'metre_per_second'.",
        "The units in 'f = pow(fCst, 11.0)' in component 'main' are not the same. 'f' is dimensionless while 'pow(fCst, 11.0)' is in 'second^11'.",
        "The units in 'g = pow(gCst, 13.0)' in component 'main' are not the same. 'g' is dimensionless while 'pow(gCst, 13.0)' is in 'volt^13'.",
        "The units in 'h = pow(hCst, 15.0)' in component 'main' are not the same. 'h' is dimensionless while 'pow(hCst, 15.0)' is in 'frog^15'.",
        "The units in 'i = pow(iCst, 17.0)' in component 'main' are not the same. 'i' is dimensionless while 'pow(iCst, 17.0)' is in 'metre_per_second^17'.",
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
        "The units in 'b = sqrt(bCst)' in component 'main' are not the same. 'b' is dimensionless while 'sqrt(bCst)' is in 'second^0.5'.",
        "The units in 'c = sqrt(cCst)' in component 'main' are not the same. 'c' is dimensionless while 'sqrt(cCst)' is in 'volt^0.5'.",
        "The units in 'd = sqrt(dCst)' in component 'main' are not the same. 'd' is dimensionless while 'sqrt(dCst)' is in 'frog^0.5'.",
        "The units in 'e = sqrt(eCst)' in component 'main' are not the same. 'e' is dimensionless while 'sqrt(eCst)' is in 'metre_per_second^0.5'.",
        "The unit of '3.0' in 'pow(kCst, 1.0/3.0)' in equation 'k = pow(kCst, 1.0/3.0)' in component 'main' is not dimensionless. '3.0' is in 'second'.",
        "The unit of '5.0' in 'pow(lCst, 1.0/5.0)' in equation 'l = pow(lCst, 1.0/5.0)' in component 'main' is not dimensionless. '5.0' is in 'volt'.",
        "The unit of '7.0' in 'pow(mCst, 1.0/7.0)' in equation 'm = pow(mCst, 1.0/7.0)' in component 'main' is not dimensionless. '7.0' is in 'frog'.",
        "The unit of '9.0' in 'pow(nCst, 1.0/9.0)' in equation 'n = pow(nCst, 1.0/9.0)' in component 'main' is not dimensionless. '9.0' is in 'metre_per_second'.",
        "The units in 'o = pow(oCst, 1.0/11.0)' in component 'main' are not the same. 'o' is dimensionless while 'pow(oCst, 1.0/11.0)' is in 'second^0.0909091'.",
        "The units in 'p = pow(pCst, 1.0/13.0)' in component 'main' are not the same. 'p' is dimensionless while 'pow(pCst, 1.0/13.0)' is in 'volt^0.0769231'.",
        "The units in 'q = pow(qCst, 1.0/15.0)' in component 'main' are not the same. 'q' is dimensionless while 'pow(qCst, 1.0/15.0)' is in 'frog^0.0666667'.",
        "The units in 'r = pow(rCst, 1.0/17.0)' in component 'main' are not the same. 'r' is dimensionless while 'pow(rCst, 1.0/17.0)' is in 'metre_per_second^0.0588235'.",
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
        "The units in 'b = abs(3.0)' in component 'main' are not the same. 'b' is dimensionless while 'abs(3.0)' is in 'second'.",
        "The units in 'c = abs(5.0)' in component 'main' are not the same. 'c' is dimensionless while 'abs(5.0)' is in 'volt'.",
        "The units in 'd = abs(7.0)' in component 'main' are not the same. 'd' is dimensionless while 'abs(7.0)' is in 'frog'.",
        "The units in 'e = abs(9.0)' in component 'main' are not the same. 'e' is dimensionless while 'abs(9.0)' is in 'metre_per_second'.",
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

TEST(AnalyserUnits, exp)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("analyser/units/exp.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    const std::vector<std::string> expectedIssues = {
        "The unit of 'bCst' in 'exp(bCst)' in equation 'b = exp(bCst)' in component 'main' is not dimensionless. 'bCst' is in 'second'.",
        "The unit of 'cCst' in 'exp(cCst)' in equation 'c = exp(cCst)' in component 'main' is not dimensionless. 'cCst' is in 'volt'.",
        "The unit of 'dCst' in 'exp(dCst)' in equation 'd = exp(dCst)' in component 'main' is not dimensionless. 'dCst' is in 'frog'.",
        "The unit of 'eCst' in 'exp(eCst)' in equation 'e = exp(eCst)' in component 'main' is not dimensionless. 'eCst' is in 'metre_per_second'.",
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

TEST(AnalyserUnits, ln)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("analyser/units/ln.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    const std::vector<std::string> expectedIssues = {
        "The unit of 'bCst' in 'ln(bCst)' in equation 'b = ln(bCst)' in component 'main' is not dimensionless. 'bCst' is in 'second'.",
        "The unit of 'cCst' in 'ln(cCst)' in equation 'c = ln(cCst)' in component 'main' is not dimensionless. 'cCst' is in 'volt'.",
        "The unit of 'dCst' in 'ln(dCst)' in equation 'd = ln(dCst)' in component 'main' is not dimensionless. 'dCst' is in 'frog'.",
        "The unit of 'eCst' in 'ln(eCst)' in equation 'e = ln(eCst)' in component 'main' is not dimensionless. 'eCst' is in 'metre_per_second'.",
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

TEST(AnalyserUnits, log)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("analyser/units/log.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    const std::vector<std::string> expectedIssues = {
        "The unit of 'bCst' in 'log(bCst)' in equation 'b = log(bCst)' in component 'main' is not dimensionless. 'bCst' is in 'second'.",
        "The unit of 'cCst' in 'log(cCst)' in equation 'c = log(cCst)' in component 'main' is not dimensionless. 'cCst' is in 'volt'.",
        "The unit of 'dCst' in 'log(dCst)' in equation 'd = log(dCst)' in component 'main' is not dimensionless. 'dCst' is in 'frog'.",
        "The unit of 'eCst' in 'log(eCst)' in equation 'e = log(eCst)' in component 'main' is not dimensionless. 'eCst' is in 'metre_per_second'.",
        "The units of '3.0' and 'gCst' in 'ln(gCst)/ln(3.0)' in equation 'g = ln(gCst)/ln(3.0)' in component 'main' are not dimensionless. '3.0' is in 'second' while 'gCst' is in 'second'.",
        "The units of '5.0' and 'hCst' in 'ln(hCst)/ln(5.0)' in equation 'h = ln(hCst)/ln(5.0)' in component 'main' are not dimensionless. '5.0' is in 'volt' while 'hCst' is in 'volt'.",
        "The units of '7.0' and 'iCst' in 'ln(iCst)/ln(7.0)' in equation 'i = ln(iCst)/ln(7.0)' in component 'main' are not dimensionless. '7.0' is in 'frog' while 'iCst' is in 'frog'.",
        "The units of '9.0' and 'jCst' in 'ln(jCst)/ln(9.0)' in equation 'j = ln(jCst)/ln(9.0)' in component 'main' are not dimensionless. '9.0' is in 'metre_per_second' while 'jCst' is in 'metre_per_second'.",
        "The unit of '13.0' in 'ln(lCst)/ln(13.0)' in equation 'l = ln(lCst)/ln(13.0)' in component 'main' is not dimensionless. '13.0' is in 'second'.",
        "The unit of '15.0' in 'ln(mCst)/ln(15.0)' in equation 'm = ln(mCst)/ln(15.0)' in component 'main' is not dimensionless. '15.0' is in 'volt'.",
        "The unit of '17.0' in 'ln(nCst)/ln(17.0)' in equation 'n = ln(nCst)/ln(17.0)' in component 'main' is not dimensionless. '17.0' is in 'frog'.",
        "The unit of '19.0' in 'ln(oCst)/ln(19.0)' in equation 'o = ln(oCst)/ln(19.0)' in component 'main' is not dimensionless. '19.0' is in 'metre_per_second'.",
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
    };

    auto analyser = libcellml::Analyser::create();

    analyser->analyseModel(model);

    EXPECT_EQ_ISSUES_CELLMLELEMENTTYPES_LEVELS_REFERENCERULES(expectedIssues, expectedCellmlElementTypes, expectedLevels, expectedReferenceRules, analyser);
}

TEST(AnalyserUnits, floor)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("analyser/units/floor.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    const std::vector<std::string> expectedIssues = {
        "The units in 'b = floor(3.0)' in component 'main' are not the same. 'b' is dimensionless while 'floor(3.0)' is in 'second'.",
        "The units in 'c = floor(5.0)' in component 'main' are not the same. 'c' is dimensionless while 'floor(5.0)' is in 'volt'.",
        "The units in 'd = floor(7.0)' in component 'main' are not the same. 'd' is dimensionless while 'floor(7.0)' is in 'frog'.",
        "The units in 'e = floor(9.0)' in component 'main' are not the same. 'e' is dimensionless while 'floor(9.0)' is in 'metre_per_second'.",
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

TEST(AnalyserUnits, ceiling)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("analyser/units/ceiling.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    const std::vector<std::string> expectedIssues = {
        "The units in 'b = ceil(3.0)' in component 'main' are not the same. 'b' is dimensionless while 'ceil(3.0)' is in 'second'.",
        "The units in 'c = ceil(5.0)' in component 'main' are not the same. 'c' is dimensionless while 'ceil(5.0)' is in 'volt'.",
        "The units in 'd = ceil(7.0)' in component 'main' are not the same. 'd' is dimensionless while 'ceil(7.0)' is in 'frog'.",
        "The units in 'e = ceil(9.0)' in component 'main' are not the same. 'e' is dimensionless while 'ceil(9.0)' is in 'metre_per_second'.",
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

TEST(AnalyserUnits, min)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("analyser/units/min.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    const std::vector<std::string> expectedIssues = {
        "The units in 'min(bCst, 3.0)' in equation 'b = min(bCst, 3.0)' in component 'main' are not the same. 'bCst' is in 'second' while '3.0' is dimensionless.",
        "The units in 'min(cCst, 5.0)' in equation 'c = min(cCst, 5.0)' in component 'main' are not the same. 'cCst' is in 'volt' while '5.0' is dimensionless.",
        "The units in 'min(dCst, 7.0)' in equation 'd = min(dCst, 7.0)' in component 'main' are not the same. 'dCst' is in 'frog' while '7.0' is dimensionless.",
        "The units in 'min(eCst, 9.0)' in equation 'e = min(eCst, 9.0)' in component 'main' are not the same. 'eCst' is in 'metre_per_second' while '9.0' is dimensionless.",
        "The units in 'min(fCst, 11.0)' in equation 'f = min(fCst, 11.0)' in component 'main' are not the same. 'fCst' is in 'second' while '11.0' is in 'metre_per_second'.",
        "The units in 'min(13.0, 15.0)' in 'min(gCst, min(13.0, 15.0))' in equation 'g = min(gCst, min(13.0, 15.0))' in component 'main' are not the same. '13.0' is in 'frog' while '15.0' is in 'metre_per_second'.",
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

TEST(AnalyserUnits, max)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("analyser/units/max.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    const std::vector<std::string> expectedIssues = {
        "The units in 'max(bCst, 3.0)' in equation 'b = max(bCst, 3.0)' in component 'main' are not the same. 'bCst' is in 'second' while '3.0' is dimensionless.",
        "The units in 'max(cCst, 5.0)' in equation 'c = max(cCst, 5.0)' in component 'main' are not the same. 'cCst' is in 'volt' while '5.0' is dimensionless.",
        "The units in 'max(dCst, 7.0)' in equation 'd = max(dCst, 7.0)' in component 'main' are not the same. 'dCst' is in 'frog' while '7.0' is dimensionless.",
        "The units in 'max(eCst, 9.0)' in equation 'e = max(eCst, 9.0)' in component 'main' are not the same. 'eCst' is in 'metre_per_second' while '9.0' is dimensionless.",
        "The units in 'max(fCst, 11.0)' in equation 'f = max(fCst, 11.0)' in component 'main' are not the same. 'fCst' is in 'second' while '11.0' is in 'metre_per_second'.",
        "The units in 'max(13.0, 15.0)' in 'max(gCst, max(13.0, 15.0))' in equation 'g = max(gCst, max(13.0, 15.0))' in component 'main' are not the same. '13.0' is in 'frog' while '15.0' is in 'metre_per_second'.",
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

TEST(AnalyserUnits, rem)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("analyser/units/rem.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    const std::vector<std::string> expectedIssues = {
        "The units in 'rem(bCst, 3.0)' in equation 'b = rem(bCst, 3.0)' in component 'main' are not the same. 'bCst' is in 'second' while '3.0' is dimensionless.",
        "The units in 'rem(cCst, 5.0)' in equation 'c = rem(cCst, 5.0)' in component 'main' are not the same. 'cCst' is in 'volt' while '5.0' is dimensionless.",
        "The units in 'rem(dCst, 7.0)' in equation 'd = rem(dCst, 7.0)' in component 'main' are not the same. 'dCst' is in 'frog' while '7.0' is dimensionless.",
        "The units in 'rem(eCst, 9.0)' in equation 'e = rem(eCst, 9.0)' in component 'main' are not the same. 'eCst' is in 'metre_per_second' while '9.0' is dimensionless.",
        "The units in 'rem(fCst, 11.0)' in equation 'f = rem(fCst, 11.0)' in component 'main' are not the same. 'fCst' is in 'second' while '11.0' is in 'metre_per_second'.",
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

TEST(AnalyserUnits, constants)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("analyser/units/constants.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    const std::vector<std::string> expectedIssues = {
        "The units in 'a = true' in component 'main' are not the same. 'a' is in 'second' while 'true' is dimensionless.",
        "The units in 'b = false' in component 'main' are not the same. 'b' is in 'second' while 'false' is dimensionless.",
        "The units in 'c = exponentiale' in component 'main' are not the same. 'c' is in 'second' while 'exponentiale' is dimensionless.",
        "The units in 'd = pi' in component 'main' are not the same. 'd' is in 'second' while 'pi' is dimensionless.",
        "The units in 'e = infinity' in component 'main' are not the same. 'e' is in 'second' while 'infinity' is dimensionless.",
        "The units in 'f = notanumber' in component 'main' are not the same. 'f' is in 'second' while 'notanumber' is dimensionless.",
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

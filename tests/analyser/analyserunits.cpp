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
        "The units in 'bLHS > 13.0' in '(bLHS > 13.0)?11.0' in '(bLHS > 13.0)?11.0:(bLHS > 17.0)?15.0:19.0' in equation 'bLHS = (bLHS > 13.0)?11.0:(bLHS > 17.0)?15.0:19.0' in component 'main' are not the same. 'bLHS' is dimensionless while '13.0' is in 'metre'.",
        "The units in 'bLHS > 17.0' in '(bLHS > 17.0)?15.0' in '(bLHS > 17.0)?15.0:19.0' in '(bLHS > 13.0)?11.0:(bLHS > 17.0)?15.0:19.0' in equation 'bLHS = (bLHS > 13.0)?11.0:(bLHS > 17.0)?15.0:19.0' in component 'main' are not the same. 'bLHS' is dimensionless while '17.0' is in 'candela'.",
        "The units in 'bLHS = (bLHS > 13.0)?11.0:(bLHS > 17.0)?15.0:19.0' in component 'main' are not the same. 'bLHS' is dimensionless while '(bLHS > 13.0)?11.0:(bLHS > 17.0)?15.0:19.0' is in 'second', 'ampere' and 'mole'.",
        "The units in 'bRHS > 13.0' in '(bRHS > 13.0)?11.0' in '(bRHS > 13.0)?11.0:(bRHS > 17.0)?15.0:19.0' in equation '(bRHS > 13.0)?11.0:(bRHS > 17.0)?15.0:19.0 = bRHS' in component 'main' are not the same. 'bRHS' is dimensionless while '13.0' is in 'metre'.",
        "The units in 'bRHS > 17.0' in '(bRHS > 17.0)?15.0' in '(bRHS > 17.0)?15.0:19.0' in '(bRHS > 13.0)?11.0:(bRHS > 17.0)?15.0:19.0' in equation '(bRHS > 13.0)?11.0:(bRHS > 17.0)?15.0:19.0 = bRHS' in component 'main' are not the same. 'bRHS' is dimensionless while '17.0' is in 'candela'.",
        "The units in '(bRHS > 13.0)?11.0:(bRHS > 17.0)?15.0:19.0 = bRHS' in component 'main' are not the same. '(bRHS > 13.0)?11.0:(bRHS > 17.0)?15.0:19.0' is in 'second', 'ampere' and 'mole' while 'bRHS' is dimensionless.",
        "The units in 'cLHS > 23.0' in '(cLHS > 23.0)?21.0' in '(cLHS > 23.0)?21.0:(cLHS > 27.0)?25.0:29.0' in equation 'cLHS = (cLHS > 23.0)?21.0:(cLHS > 27.0)?25.0:29.0' in component 'main' are not the same. 'cLHS' is dimensionless while '23.0' is in 'rooster'.",
        "The units in 'cLHS > 27.0' in '(cLHS > 27.0)?25.0' in '(cLHS > 27.0)?25.0:29.0' in '(cLHS > 23.0)?21.0:(cLHS > 27.0)?25.0:29.0' in equation 'cLHS = (cLHS > 23.0)?21.0:(cLHS > 27.0)?25.0:29.0' in component 'main' are not the same. 'cLHS' is dimensionless while '27.0' is in 'cat'.",
        "The units in 'cLHS = (cLHS > 23.0)?21.0:(cLHS > 27.0)?25.0:29.0' in component 'main' are not the same. 'cLHS' is dimensionless while '(cLHS > 23.0)?21.0:(cLHS > 27.0)?25.0:29.0' is in 'frog', 'dog' and 'dove'.",
        "The units in 'cRHS > 23.0' in '(cRHS > 23.0)?21.0' in '(cRHS > 23.0)?21.0:(cRHS > 27.0)?25.0:29.0' in equation '(cRHS > 23.0)?21.0:(cRHS > 27.0)?25.0:29.0 = cRHS' in component 'main' are not the same. 'cRHS' is dimensionless while '23.0' is in 'rooster'.",
        "The units in 'cRHS > 27.0' in '(cRHS > 27.0)?25.0' in '(cRHS > 27.0)?25.0:29.0' in '(cRHS > 23.0)?21.0:(cRHS > 27.0)?25.0:29.0' in equation '(cRHS > 23.0)?21.0:(cRHS > 27.0)?25.0:29.0 = cRHS' in component 'main' are not the same. 'cRHS' is dimensionless while '27.0' is in 'cat'.",
        "The units in '(cRHS > 23.0)?21.0:(cRHS > 27.0)?25.0:29.0 = cRHS' in component 'main' are not the same. '(cRHS > 23.0)?21.0:(cRHS > 27.0)?25.0:29.0' is in 'frog', 'dog' and 'dove' while 'cRHS' is dimensionless.",
        "The units in 'dLHS > 23.0' in '(dLHS > 23.0)?21.0' in '(dLHS > 23.0)?21.0:(dLHS > 27.0)?25.0:29.0' in equation '(dLHS > 23.0)?21.0:(dLHS > 27.0)?25.0:29.0 = (dRHS > 33.0)?31.0:(dRHS > 37.0)?35.0:39.0' in component 'main' are not the same. 'dLHS' is dimensionless while '23.0' is in 'metre'.",
        "The units in 'dLHS > 27.0' in '(dLHS > 27.0)?25.0' in '(dLHS > 27.0)?25.0:29.0' in '(dLHS > 23.0)?21.0:(dLHS > 27.0)?25.0:29.0' in equation '(dLHS > 23.0)?21.0:(dLHS > 27.0)?25.0:29.0 = (dRHS > 33.0)?31.0:(dRHS > 37.0)?35.0:39.0' in component 'main' are not the same. 'dLHS' is dimensionless while '27.0' is in 'candela'.",
        "The units in 'dRHS > 33.0' in '(dRHS > 33.0)?31.0' in '(dRHS > 33.0)?31.0:(dRHS > 37.0)?35.0:39.0' in equation '(dLHS > 23.0)?21.0:(dLHS > 27.0)?25.0:29.0 = (dRHS > 33.0)?31.0:(dRHS > 37.0)?35.0:39.0' in component 'main' are not the same. 'dRHS' is dimensionless while '33.0' is in 'rooster'.",
        "The units in 'dRHS > 37.0' in '(dRHS > 37.0)?35.0' in '(dRHS > 37.0)?35.0:39.0' in '(dRHS > 33.0)?31.0:(dRHS > 37.0)?35.0:39.0' in equation '(dLHS > 23.0)?21.0:(dLHS > 27.0)?25.0:29.0 = (dRHS > 33.0)?31.0:(dRHS > 37.0)?35.0:39.0' in component 'main' are not the same. 'dRHS' is dimensionless while '37.0' is in 'cat'.",
        "The units in '(dLHS > 23.0)?21.0:(dLHS > 27.0)?25.0:29.0 = (dRHS > 33.0)?31.0:(dRHS > 37.0)?35.0:39.0' in component 'main' are not the same. '(dLHS > 23.0)?21.0:(dLHS > 27.0)?25.0:29.0' is in 'second', 'ampere' and 'mole' while '(dRHS > 33.0)?31.0:(dRHS > 37.0)?35.0:39.0' is in 'frog', 'dog' and 'dove'.",
        "The unit of '43.0' in '(43.0)?41.0' in '(43.0)?41.0:45.0' in equation 'eLHS = (43.0)?41.0:45.0' in component 'main' is not dimensionless. '43.0' is in 'second'.",
        "The unit of '43.0' in '(43.0)?41.0' in '(43.0)?41.0:45.0' in equation '(43.0)?41.0:45.0 = eRHS' in component 'main' is not dimensionless. '43.0' is in 'second'.",
        "",
        "",
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
        "The units in 'b = pow(bCst, 3.0)' in component 'main' are not the same. The unit mismatch is second^-3.",
        "The units in 'c = pow(cCst, 5.0)' in component 'main' are not the same. The unit mismatch is ampere^5 x kilogram^-5 x metre^-10 x second^15.",
        "The units in 'd = pow(dCst, 7.0)' in component 'main' are not the same. The unit mismatch is frog^-7.",
        "The unit of '9.0' in 'pow(eCst, 9.0)' in equation 'e = pow(eCst, 9.0)' in component 'main' is not dimensionless. The unit mismatch is ampere^-1 x kilogram^1 x metre^2 x second^-3.",
        "The units in 'e = pow(eCst, 9.0)' in component 'main' are not the same. The unit mismatch is second^-9.",
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
        "The units in 'b = pow(bCst, 1.0/3.0)' in component 'main' are not the same. The unit mismatch is second^-0.333333.",
        "The units in 'c = pow(cCst, 1.0/5.0)' in component 'main' are not the same. The unit mismatch is ampere^0.2 x kilogram^-0.2 x metre^-0.4 x second^0.6.",
        "The units in 'd = pow(dCst, 1.0/7.0)' in component 'main' are not the same. The unit mismatch is frog^-0.142857.",
        "The unit of '9.0' in 'pow(eCst, 1.0/9.0)' in equation 'e = pow(eCst, 1.0/9.0)' in component 'main' is not dimensionless. The unit mismatch is ampere^-1 x kilogram^1 x metre^2 x second^-3.",
        "The units in 'e = pow(eCst, 1.0/9.0)' in component 'main' are not the same. The unit mismatch is second^-0.111111.",
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

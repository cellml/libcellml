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
        "The units in 'ampere = 1.0' in component 'main' are not equivalent. 'ampere' is in 'ampere' while '1.0' is 'dimensionless'.",
        "The units in 'becquerel = 1.0' in component 'main' are not equivalent. 'becquerel' is in 'becquerel' (i.e. 'second^-1') while '1.0' is 'dimensionless'.",
        "The units in 'candela = 1.0' in component 'main' are not equivalent. 'candela' is in 'candela' while '1.0' is 'dimensionless'.",
        "The units in 'coulomb = 1.0' in component 'main' are not equivalent. 'coulomb' is in 'coulomb' (i.e. 'ampere x second') while '1.0' is 'dimensionless'.",
        "The units in 'farad = 1.0' in component 'main' are not equivalent. 'farad' is in 'farad' (i.e. 'ampere^2 x kilogram^-1 x metre^-2 x second^4') while '1.0' is 'dimensionless'.",
        "The units in 'gram = 1.0' in component 'main' are not equivalent. 'gram' is in 'gram' (i.e. '10^-3 x kilogram') while '1.0' is 'dimensionless'.",
        "The units in 'gray = 1.0' in component 'main' are not equivalent. 'gray' is in 'gray' (i.e. 'metre^2 x second^-2') while '1.0' is 'dimensionless'.",
        "The units in 'henry = 1.0' in component 'main' are not equivalent. 'henry' is in 'henry' (i.e. 'ampere^-2 x kilogram x metre^2 x second^-2') while '1.0' is 'dimensionless'.",
        "The units in 'hertz = 1.0' in component 'main' are not equivalent. 'hertz' is in 'hertz' (i.e. 'second^-1') while '1.0' is 'dimensionless'.",
        "The units in 'joule = 1.0' in component 'main' are not equivalent. 'joule' is in 'joule' (i.e. 'kilogram x metre^2 x second^-2') while '1.0' is 'dimensionless'.",
        "The units in 'katal = 1.0' in component 'main' are not equivalent. 'katal' is in 'katal' (i.e. 'mole x second^-1') while '1.0' is 'dimensionless'.",
        "The units in 'kelvin = 1.0' in component 'main' are not equivalent. 'kelvin' is in 'kelvin' while '1.0' is 'dimensionless'.",
        "The units in 'kilogram = 1.0' in component 'main' are not equivalent. 'kilogram' is in 'kilogram' while '1.0' is 'dimensionless'.",
        "The units in 'litre = 1.0' in component 'main' are not equivalent. 'litre' is in 'litre' (i.e. '10^-3 x metre^3') while '1.0' is 'dimensionless'.",
        "The units in 'lumen = 1.0' in component 'main' are not equivalent. 'lumen' is in 'lumen' (i.e. 'candela') while '1.0' is 'dimensionless'.",
        "The units in 'lux = 1.0' in component 'main' are not equivalent. 'lux' is in 'lux' (i.e. 'candela x metre^-2') while '1.0' is 'dimensionless'.",
        "The units in 'metre = 1.0' in component 'main' are not equivalent. 'metre' is in 'metre' while '1.0' is 'dimensionless'.",
        "The units in 'mole = 1.0' in component 'main' are not equivalent. 'mole' is in 'mole' while '1.0' is 'dimensionless'.",
        "The units in 'newton = 1.0' in component 'main' are not equivalent. 'newton' is in 'newton' (i.e. 'kilogram x metre x second^-2') while '1.0' is 'dimensionless'.",
        "The units in 'ohm = 1.0' in component 'main' are not equivalent. 'ohm' is in 'ohm' (i.e. 'ampere^-2 x kilogram x metre^2 x second^-3') while '1.0' is 'dimensionless'.",
        "The units in 'pascal = 1.0' in component 'main' are not equivalent. 'pascal' is in 'pascal' (i.e. 'kilogram x metre^-1 x second^-2') while '1.0' is 'dimensionless'.",
        "The units in 'second = 1.0' in component 'main' are not equivalent. 'second' is in 'second' while '1.0' is 'dimensionless'.",
        "The units in 'siemens = 1.0' in component 'main' are not equivalent. 'siemens' is in 'siemens' (i.e. 'ampere^2 x kilogram^-1 x metre^-2 x second^3') while '1.0' is 'dimensionless'.",
        "The units in 'sievert = 1.0' in component 'main' are not equivalent. 'sievert' is in 'sievert' (i.e. 'metre^2 x second^-2') while '1.0' is 'dimensionless'.",
        "The units in 'tesla = 1.0' in component 'main' are not equivalent. 'tesla' is in 'tesla' (i.e. 'ampere^-1 x kilogram x second^-2') while '1.0' is 'dimensionless'.",
        "The units in 'volt = 1.0' in component 'main' are not equivalent. 'volt' is in 'volt' (i.e. 'ampere^-1 x kilogram x metre^2 x second^-3') while '1.0' is 'dimensionless'.",
        "The units in 'watt = 1.0' in component 'main' are not equivalent. 'watt' is in 'watt' (i.e. 'kilogram x metre^2 x second^-3') while '1.0' is 'dimensionless'.",
        "The units in 'weber = 1.0' in component 'main' are not equivalent. 'weber' is in 'weber' (i.e. 'ampere^-1 x kilogram x metre^2 x second^-2') while '1.0' is 'dimensionless'.",
    };

    auto analyser = libcellml::Analyser::create();

    analyser->analyseModel(model);

    EXPECT_EQ_ISSUES_CELLMLELEMENTTYPES_LEVELS_REFERENCERULES_URLS(expectedIssues,
                                                                   expectedCellmlElementTypes(expectedIssues.size(), libcellml::CellmlElementType::UNDEFINED),
                                                                   expectedLevels(expectedIssues.size(), libcellml::Issue::Level::WARNING),
                                                                   expectedReferenceRules(expectedIssues.size(), libcellml::Issue::ReferenceRule::ANALYSER_UNITS),
                                                                   expectedUrls(expectedIssues.size(), "https://libcellml.org/documentation/guides/latest/runtime_codes/index?issue=ANALYSER_UNITS"),
                                                                   analyser);
}

TEST(AnalyserUnits, basic)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("analyser/units/basic.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    auto analyser = libcellml::Analyser::create();

    analyser->analyseModel(model);

    EXPECT_EQ(size_t(0), analyser->issueCount());
}

TEST(AnalyserUnits, ci)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("analyser/units/ci.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    const std::vector<std::string> expectedIssues = {
        "The units in 'b = bCst' in component 'main' are not equivalent. 'b' is 'dimensionless' while 'bCst' is in 'second'.",
        "The units in 'c = cCst' in component 'main' are not equivalent. 'c' is 'dimensionless' while 'cCst' is in 'volt' (i.e. 'ampere^-1 x kilogram x metre^2 x second^-3').",
        "The units in 'd = dCst' in component 'main' are not equivalent. 'd' is 'dimensionless' while 'dCst' is in 'frog'.",
        "The units in 'e = eCst' in component 'main' are not equivalent. 'e' is 'dimensionless' while 'eCst' is in 'imaginary' (i.e. '10^-30 x ampere^-6 x frog^10 x kilogram^6 x metre^12 x second^-16').",
    };

    auto analyser = libcellml::Analyser::create();

    analyser->analyseModel(model);

    EXPECT_EQ_ISSUES(expectedIssues, analyser);
}

TEST(AnalyserUnits, cn)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("analyser/units/cn.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    const std::vector<std::string> expectedIssues = {
        "The units in 'b = 3.0' in component 'main' are not equivalent. 'b' is 'dimensionless' while '3.0' is in 'second'.",
        "The units in 'c = 5.0' in component 'main' are not equivalent. 'c' is 'dimensionless' while '5.0' is in 'volt' (i.e. 'ampere^-1 x kilogram x metre^2 x second^-3').",
        "The units in 'd = 7.0' in component 'main' are not equivalent. 'd' is 'dimensionless' while '7.0' is in 'frog'.",
        "The units in 'e = 9.0' in component 'main' are not equivalent. 'e' is 'dimensionless' while '9.0' is in 'imaginary' (i.e. '10^-30 x ampere^-6 x frog^10 x kilogram^6 x metre^12 x second^-16').",
        "The units in 'g = 13.0e3' in component 'main' are not equivalent. 'g' is 'dimensionless' while '13.0e3' is in 'second'.",
        "The units in 'h = 15.0e5' in component 'main' are not equivalent. 'h' is 'dimensionless' while '15.0e5' is in 'volt' (i.e. 'ampere^-1 x kilogram x metre^2 x second^-3').",
        "The units in 'i = 17.0e7' in component 'main' are not equivalent. 'i' is 'dimensionless' while '17.0e7' is in 'frog'.",
        "The units in 'j = 19.0e9' in component 'main' are not equivalent. 'j' is 'dimensionless' while '19.0e9' is in 'imaginary' (i.e. '10^-30 x ampere^-6 x frog^10 x kilogram^6 x metre^12 x second^-16').",
    };

    auto analyser = libcellml::Analyser::create();

    analyser->analyseModel(model);

    EXPECT_EQ_ISSUES(expectedIssues, analyser);
}

TEST(AnalyserUnits, piecewise)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("analyser/units/piecewise.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    const std::vector<std::string> expectedIssues = {
        "The units in 'b > 9.0' in '(b > 9.0)?7.0' in '(b > 9.0)?7.0:11.0' in equation 'b = (b > 9.0)?7.0:11.0' in component 'main' are not equivalent. 'b' is 'dimensionless' while '9.0' is in 'second'.",
        "The units in 'c > 15.0' in '(c > 15.0)?13.0' in '(c > 15.0)?13.0:17.0' in equation 'c = (c > 15.0)?13.0:17.0' in component 'main' are not equivalent. 'c' is 'dimensionless' while '15.0' is in 'volt' (i.e. 'ampere^-1 x kilogram x metre^2 x second^-3').",
        "The units in 'd > 21.0' in '(d > 21.0)?19.0' in '(d > 21.0)?19.0:23.0' in equation 'd = (d > 21.0)?19.0:23.0' in component 'main' are not equivalent. 'd' is 'dimensionless' while '21.0' is in 'frog'.",
        "The units in 'e > 27.0' in '(e > 27.0)?25.0' in '(e > 27.0)?25.0:29.0' in equation 'e = (e > 27.0)?25.0:29.0' in component 'main' are not equivalent. 'e' is 'dimensionless' while '27.0' is in 'imaginary' (i.e. '10^-30 x ampere^-6 x frog^10 x kilogram^6 x metre^12 x second^-16').",
        "The units in 'f = (f > 33.0)?31.0:(f > 37.0)?35.0:(f > 41.0)?39.0:(f > 45.0)?43.0:(f > 49.0)?47.0:51.0' in component 'main' are not equivalent. 'f' is 'dimensionless' while '(f > 33.0)?31.0:(f > 37.0)?35.0:(f > 41.0)?39.0:(f > 45.0)?43.0:(f > 49.0)?47.0:51.0' is in 'second', 'volt', 'frog' and 'imaginary' (i.e. 'second', 'ampere^-1 x kilogram x metre^2 x second^-3', 'frog' and '10^-30 x ampere^-6 x frog^10 x kilogram^6 x metre^12 x second^-16').",
        "The unit of '55.0' in '(55.0)?53.0' in '(55.0)?53.0:57.0' in equation 'g = (55.0)?53.0:57.0' in component 'main' is not dimensionless. '55.0' is in 'second'.",
    };

    auto analyser = libcellml::Analyser::create();

    analyser->analyseModel(model);

    EXPECT_EQ_ISSUES(expectedIssues, analyser);
}

TEST(AnalyserUnits, eq)
{
    std::vector<std::pair<std::string, std::string>> operators = {
        {"eq", "=="},
        {"neq", "!="},
        {"lt", "<"},
        {"leq", "<="},
        {"gt", ">"},
        {"geq", ">="},
    };

    for (const auto &op : operators) {
        auto parser = libcellml::Parser::create();
        auto model = parser->parseModel(fileContents("analyser/units/" + op.first + ".cellml"));

        EXPECT_EQ(size_t(0), parser->issueCount());

        const std::vector<std::string> expectedIssues = {
            "The units in 'bCst " + op.second + " 3.0' in equation 'b = bCst " + op.second + " 3.0' in component 'main' are not equivalent. 'bCst' is in 'second' while '3.0' is 'dimensionless'.",
            "The units in 'cCst " + op.second + " 5.0' in equation 'c = cCst " + op.second + " 5.0' in component 'main' are not equivalent. 'cCst' is in 'volt' (i.e. 'ampere^-1 x kilogram x metre^2 x second^-3') while '5.0' is 'dimensionless'.",
            "The units in 'dCst " + op.second + " 7.0' in equation 'd = dCst " + op.second + " 7.0' in component 'main' are not equivalent. 'dCst' is in 'frog' while '7.0' is 'dimensionless'.",
            "The units in 'eCst " + op.second + " 9.0' in equation 'e = eCst " + op.second + " 9.0' in component 'main' are not equivalent. 'eCst' is in 'imaginary' (i.e. '10^-30 x ampere^-6 x frog^10 x kilogram^6 x metre^12 x second^-16') while '9.0' is 'dimensionless'.",
            "The units in 'fCst " + op.second + " 11.0' in equation 'f = fCst " + op.second + " 11.0' in component 'main' are not equivalent. 'fCst' is in 'second' while '11.0' is in 'imaginary' (i.e. '10^-30 x ampere^-6 x frog^10 x kilogram^6 x metre^12 x second^-16').",
        };

        auto analyser = libcellml::Analyser::create();

        analyser->analyseModel(model);

        EXPECT_EQ_ISSUES(expectedIssues, analyser);
    }
}

TEST(AnalyserUnits, andOrOperators)
{
    std::vector<std::pair<std::string, std::string>> operators = {
        {"and", "&&"},
        {"or", "||"},
    };

    for (const auto &op : operators) {
        auto parser = libcellml::Parser::create();
        auto model = parser->parseModel(fileContents("analyser/units/" + op.first + ".cellml"));

        EXPECT_EQ(size_t(0), parser->issueCount());

        const std::vector<std::string> expectedIssues = {
            "The unit of 'bCst' in 'bCst " + op.second + " 3.0' in equation 'b = bCst " + op.second + " 3.0' in component 'main' is not dimensionless. 'bCst' is in 'second'.",
            "The unit of 'cCst' in 'cCst " + op.second + " 5.0' in equation 'c = cCst " + op.second + " 5.0' in component 'main' is not dimensionless. 'cCst' is in 'volt' (i.e. 'ampere^-1 x kilogram x metre^2 x second^-3').",
            "The unit of 'dCst' in 'dCst " + op.second + " 7.0' in equation 'd = dCst " + op.second + " 7.0' in component 'main' is not dimensionless. 'dCst' is in 'frog'.",
            "The unit of 'eCst' in 'eCst " + op.second + " 9.0' in equation 'e = eCst " + op.second + " 9.0' in component 'main' is not dimensionless. 'eCst' is in 'imaginary' (i.e. '10^-30 x ampere^-6 x frog^10 x kilogram^6 x metre^12 x second^-16').",
            "The units of 'fCst' and '11.0' in 'fCst " + op.second + " 11.0' in equation 'f = fCst " + op.second + " 11.0' in component 'main' are not dimensionless. 'fCst' is in 'second' while '11.0' is in 'imaginary' (i.e. '10^-30 x ampere^-6 x frog^10 x kilogram^6 x metre^12 x second^-16').",
        };

        auto analyser = libcellml::Analyser::create();

        analyser->analyseModel(model);

        EXPECT_EQ_ISSUES(expectedIssues, analyser);
    }
}

TEST(AnalyserUnits, xorOp)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("analyser/units/xor.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    const std::vector<std::string> expectedIssues = {
        "The unit of 'bCst' in 'xor(bCst, 3.0)' in equation 'b = xor(bCst, 3.0)' in component 'main' is not dimensionless. 'bCst' is in 'second'.",
        "The unit of 'cCst' in 'xor(cCst, 5.0)' in equation 'c = xor(cCst, 5.0)' in component 'main' is not dimensionless. 'cCst' is in 'volt' (i.e. 'ampere^-1 x kilogram x metre^2 x second^-3').",
        "The unit of 'dCst' in 'xor(dCst, 7.0)' in equation 'd = xor(dCst, 7.0)' in component 'main' is not dimensionless. 'dCst' is in 'frog'.",
        "The unit of 'eCst' in 'xor(eCst, 9.0)' in equation 'e = xor(eCst, 9.0)' in component 'main' is not dimensionless. 'eCst' is in 'imaginary' (i.e. '10^-30 x ampere^-6 x frog^10 x kilogram^6 x metre^12 x second^-16').",
        "The units of 'fCst' and '11.0' in 'xor(fCst, 11.0)' in equation 'f = xor(fCst, 11.0)' in component 'main' are not dimensionless. 'fCst' is in 'second' while '11.0' is in 'imaginary' (i.e. '10^-30 x ampere^-6 x frog^10 x kilogram^6 x metre^12 x second^-16').",
    };

    auto analyser = libcellml::Analyser::create();

    analyser->analyseModel(model);

    EXPECT_EQ_ISSUES(expectedIssues, analyser);
}

TEST(AnalyserUnits, notOp)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("analyser/units/not.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    const std::vector<std::string> expectedIssues = {
        "The unit of 'bCst' in '!bCst' in equation 'b = !bCst' in component 'main' is not dimensionless. 'bCst' is in 'second'.",
        "The unit of 'cCst' in '!cCst' in equation 'c = !cCst' in component 'main' is not dimensionless. 'cCst' is in 'volt' (i.e. 'ampere^-1 x kilogram x metre^2 x second^-3').",
        "The unit of 'dCst' in '!dCst' in equation 'd = !dCst' in component 'main' is not dimensionless. 'dCst' is in 'frog'.",
        "The unit of 'eCst' in '!eCst' in equation 'e = !eCst' in component 'main' is not dimensionless. 'eCst' is in 'imaginary' (i.e. '10^-30 x ampere^-6 x frog^10 x kilogram^6 x metre^12 x second^-16').",
    };

    auto analyser = libcellml::Analyser::create();

    analyser->analyseModel(model);

    EXPECT_EQ_ISSUES(expectedIssues, analyser);
}

TEST(AnalyserUnits, plus)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("analyser/units/plus.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    const std::vector<std::string> expectedIssues = {
        "The units in 'bCst+3.0' in equation 'b = bCst+3.0' in component 'main' are not equivalent. 'bCst' is in 'second' while '3.0' is 'dimensionless'.",
        "The units in 'cCst+5.0' in equation 'c = cCst+5.0' in component 'main' are not equivalent. 'cCst' is in 'volt' (i.e. 'ampere^-1 x kilogram x metre^2 x second^-3') while '5.0' is 'dimensionless'.",
        "The units in 'dCst+7.0' in equation 'd = dCst+7.0' in component 'main' are not equivalent. 'dCst' is in 'frog' while '7.0' is 'dimensionless'.",
        "The units in 'eCst+9.0' in equation 'e = eCst+9.0' in component 'main' are not equivalent. 'eCst' is in 'imaginary' (i.e. '10^-30 x ampere^-6 x frog^10 x kilogram^6 x metre^12 x second^-16') while '9.0' is 'dimensionless'.",
        "The units in 'fCst+11.0' in equation 'f = fCst+11.0' in component 'main' are not equivalent. 'fCst' is in 'second' while '11.0' is in 'imaginary' (i.e. '10^-30 x ampere^-6 x frog^10 x kilogram^6 x metre^12 x second^-16').",
    };

    auto analyser = libcellml::Analyser::create();

    analyser->analyseModel(model);

    EXPECT_EQ_ISSUES(expectedIssues, analyser);
}

TEST(AnalyserUnits, minus)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("analyser/units/minus.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    const std::vector<std::string> expectedIssues = {
        "The units in 'b = -bCst' in component 'main' are not equivalent. 'b' is 'dimensionless' while '-bCst' is in 'second'.",
        "The units in 'c = -cCst' in component 'main' are not equivalent. 'c' is 'dimensionless' while '-cCst' is in 'volt' (i.e. 'ampere^-1 x kilogram x metre^2 x second^-3').",
        "The units in 'd = -dCst' in component 'main' are not equivalent. 'd' is 'dimensionless' while '-dCst' is in 'frog'.",
        "The units in 'e = -eCst' in component 'main' are not equivalent. 'e' is 'dimensionless' while '-eCst' is in 'imaginary' (i.e. '10^-30 x ampere^-6 x frog^10 x kilogram^6 x metre^12 x second^-16').",
        "The units in 'gCst-3.0' in equation 'g = gCst-3.0' in component 'main' are not equivalent. 'gCst' is in 'second' while '3.0' is 'dimensionless'.",
        "The units in 'hCst-5.0' in equation 'h = hCst-5.0' in component 'main' are not equivalent. 'hCst' is in 'volt' (i.e. 'ampere^-1 x kilogram x metre^2 x second^-3') while '5.0' is 'dimensionless'.",
        "The units in 'iCst-7.0' in equation 'i = iCst-7.0' in component 'main' are not equivalent. 'iCst' is in 'frog' while '7.0' is 'dimensionless'.",
        "The units in 'jCst-9.0' in equation 'j = jCst-9.0' in component 'main' are not equivalent. 'jCst' is in 'imaginary' (i.e. '10^-30 x ampere^-6 x frog^10 x kilogram^6 x metre^12 x second^-16') while '9.0' is 'dimensionless'.",
        "The units in 'kCst-11.0' in equation 'k = kCst-11.0' in component 'main' are not equivalent. 'kCst' is in 'second' while '11.0' is in 'imaginary' (i.e. '10^-30 x ampere^-6 x frog^10 x kilogram^6 x metre^12 x second^-16').",
    };

    auto analyser = libcellml::Analyser::create();

    analyser->analyseModel(model);

    EXPECT_EQ_ISSUES(expectedIssues, analyser);
}

TEST(AnalyserUnits, times)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("analyser/units/times.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    const std::vector<std::string> expectedIssues = {
        "The units in 'b = bCst*3.0' in component 'main' are not equivalent. 'b' is 'dimensionless' while 'bCst*3.0' is in 'second'.",
        "The units in 'c = cCst*5.0' in component 'main' are not equivalent. 'c' is 'dimensionless' while 'cCst*5.0' is in 'volt' (i.e. 'ampere^-1 x kilogram x metre^2 x second^-3').",
        "The units in 'd = dCst*7.0' in component 'main' are not equivalent. 'd' is 'dimensionless' while 'dCst*7.0' is in 'frog'.",
        "The units in 'e = eCst*9.0' in component 'main' are not equivalent. 'e' is 'dimensionless' while 'eCst*9.0' is in 'imaginary' (i.e. '10^-30 x ampere^-6 x frog^10 x kilogram^6 x metre^12 x second^-16').",
        "The units in 'f = fCst*11.0' in component 'main' are not equivalent. 'f' is 'dimensionless' while 'fCst*11.0' is in 'imaginary x second' (i.e. '10^-30 x ampere^-6 x frog^10 x kilogram^6 x metre^12 x second^-15').",
        "The units in 'g = gCst*13.0' in component 'main' are not equivalent. 'g' is in 'second_by_volt' (i.e. 'ampere^-1 x kilogram x metre^2 x second^-2') while 'gCst*13.0' is in 'second'.",
        "The units in 'h = hCst*15.0' in component 'main' are not equivalent. 'h' is in 'volt_by_volt' (i.e. 'ampere^-2 x kilogram^2 x metre^4 x second^-6') while 'hCst*15.0' is in 'volt' (i.e. 'ampere^-1 x kilogram x metre^2 x second^-3').",
        "The units in 'i = iCst*17.0' in component 'main' are not equivalent. 'i' is in 'frog_by_volt' (i.e. 'ampere^-1 x frog x kilogram x metre^2 x second^-3') while 'iCst*17.0' is in 'frog'.",
        "The units in 'j = jCst*19.0' in component 'main' are not equivalent. 'j' is in 'imaginary_by_volt' (i.e. '10^-30 x ampere^-7 x frog^10 x kilogram^7 x metre^14 x second^-19') while 'jCst*19.0' is in 'imaginary' (i.e. '10^-30 x ampere^-6 x frog^10 x kilogram^6 x metre^12 x second^-16').",
    };

    auto analyser = libcellml::Analyser::create();

    analyser->analyseModel(model);

    EXPECT_EQ_ISSUES(expectedIssues, analyser);
}

TEST(AnalyserUnits, divide)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("analyser/units/divide.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    const std::vector<std::string> expectedIssues = {
        "The units in 'b = bCst/3.0' in component 'main' are not equivalent. 'b' is 'dimensionless' while 'bCst/3.0' is in 'second'.",
        "The units in 'c = cCst/5.0' in component 'main' are not equivalent. 'c' is 'dimensionless' while 'cCst/5.0' is in 'volt' (i.e. 'ampere^-1 x kilogram x metre^2 x second^-3').",
        "The units in 'd = dCst/7.0' in component 'main' are not equivalent. 'd' is 'dimensionless' while 'dCst/7.0' is in 'frog'.",
        "The units in 'e = eCst/9.0' in component 'main' are not equivalent. 'e' is 'dimensionless' while 'eCst/9.0' is in 'imaginary' (i.e. '10^-30 x ampere^-6 x frog^10 x kilogram^6 x metre^12 x second^-16').",
        "The units in 'f = fCst/11.0' in component 'main' are not equivalent. 'f' is 'dimensionless' while 'fCst/11.0' is in 'imaginary^-1 x second' (i.e. '10^30 x ampere^6 x frog^-10 x kilogram^-6 x metre^-12 x second^17').",
        "The units in 'g = gCst/13.0' in component 'main' are not equivalent. 'g' is in 'second_per_volt' (i.e. 'ampere x kilogram^-1 x metre^-2 x second^4') while 'gCst/13.0' is in 'second'.",
        "The units in 'h = hCst/15.0' in component 'main' are not equivalent. 'h' is in 'volt_per_volt' while 'hCst/15.0' is in 'volt' (i.e. 'ampere^-1 x kilogram x metre^2 x second^-3').",
        "The units in 'i = iCst/17.0' in component 'main' are not equivalent. 'i' is in 'frog_per_volt' (i.e. 'ampere x frog x kilogram^-1 x metre^-2 x second^3') while 'iCst/17.0' is in 'frog'.",
        "The units in 'j = jCst/19.0' in component 'main' are not equivalent. 'j' is in 'imaginary_per_volt' (i.e. '10^-30 x ampere^-5 x frog^10 x kilogram^5 x metre^10 x second^-13') while 'jCst/19.0' is in 'imaginary' (i.e. '10^-30 x ampere^-6 x frog^10 x kilogram^6 x metre^12 x second^-16').",
    };

    auto analyser = libcellml::Analyser::create();

    analyser->analyseModel(model);

    EXPECT_EQ_ISSUES(expectedIssues, analyser);
}

TEST(AnalyserUnits, power)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("analyser/units/power.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    const std::vector<std::string> expectedIssues = {
        "The unit of '3.0' in 'pow(bCst, 3.0)' in equation 'b = pow(bCst, 3.0)' in component 'main' is not dimensionless. '3.0' is in 'second'.",
        "The unit of '5.0' in 'pow(cCst, 5.0)' in equation 'c = pow(cCst, 5.0)' in component 'main' is not dimensionless. '5.0' is in 'volt' (i.e. 'ampere^-1 x kilogram x metre^2 x second^-3').",
        "The unit of '7.0' in 'pow(dCst, 7.0)' in equation 'd = pow(dCst, 7.0)' in component 'main' is not dimensionless. '7.0' is in 'frog'.",
        "The unit of '9.0' in 'pow(eCst, 9.0)' in equation 'e = pow(eCst, 9.0)' in component 'main' is not dimensionless. '9.0' is in 'imaginary' (i.e. '10^-30 x ampere^-6 x frog^10 x kilogram^6 x metre^12 x second^-16').",
        "The units in 'f = pow(fCst, 11.0)' in component 'main' are not equivalent. 'f' is 'dimensionless' while 'pow(fCst, 11.0)' is in 'second^11'.",
        "The units in 'g = pow(gCst, 13.0)' in component 'main' are not equivalent. 'g' is 'dimensionless' while 'pow(gCst, 13.0)' is in 'volt^13' (i.e. 'ampere^-13 x kilogram^13 x metre^26 x second^-39').",
        "The units in 'h = pow(hCst, 15.0)' in component 'main' are not equivalent. 'h' is 'dimensionless' while 'pow(hCst, 15.0)' is in 'frog^15'.",
        "The units in 'i = pow(iCst, 17.0)' in component 'main' are not equivalent. 'i' is 'dimensionless' while 'pow(iCst, 17.0)' is in 'imaginary^17' (i.e. '10^-510 x ampere^-102 x frog^170 x kilogram^102 x metre^204 x second^-272').",
    };

    auto analyser = libcellml::Analyser::create();

    analyser->analyseModel(model);

    EXPECT_EQ_ISSUES(expectedIssues, analyser);
}

TEST(AnalyserUnits, root)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("analyser/units/root.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    const std::vector<std::string> expectedIssues = {
        "The units in 'b = sqrt(bCst)' in component 'main' are not equivalent. 'b' is 'dimensionless' while 'sqrt(bCst)' is in 'second^0.5'.",
        "The units in 'c = sqrt(cCst)' in component 'main' are not equivalent. 'c' is 'dimensionless' while 'sqrt(cCst)' is in 'volt^0.5' (i.e. 'ampere^-0.5 x kilogram^0.5 x metre x second^-1.5').",
        "The units in 'd = sqrt(dCst)' in component 'main' are not equivalent. 'd' is 'dimensionless' while 'sqrt(dCst)' is in 'frog^0.5'.",
        "The units in 'e = sqrt(eCst)' in component 'main' are not equivalent. 'e' is 'dimensionless' while 'sqrt(eCst)' is in 'imaginary^0.5' (i.e. '10^-15 x ampere^-3 x frog^5 x kilogram^3 x metre^6 x second^-8').",
        "The unit of '3.0' in 'pow(kCst, 1.0/3.0)' in equation 'k = pow(kCst, 1.0/3.0)' in component 'main' is not dimensionless. '3.0' is in 'second'.",
        "The unit of '5.0' in 'pow(lCst, 1.0/5.0)' in equation 'l = pow(lCst, 1.0/5.0)' in component 'main' is not dimensionless. '5.0' is in 'volt' (i.e. 'ampere^-1 x kilogram x metre^2 x second^-3').",
        "The unit of '7.0' in 'pow(mCst, 1.0/7.0)' in equation 'm = pow(mCst, 1.0/7.0)' in component 'main' is not dimensionless. '7.0' is in 'frog'.",
        "The unit of '9.0' in 'pow(nCst, 1.0/9.0)' in equation 'n = pow(nCst, 1.0/9.0)' in component 'main' is not dimensionless. '9.0' is in 'imaginary' (i.e. '10^-30 x ampere^-6 x frog^10 x kilogram^6 x metre^12 x second^-16').",
        "The units in 'o = pow(oCst, 1.0/11.0)' in component 'main' are not equivalent. 'o' is 'dimensionless' while 'pow(oCst, 1.0/11.0)' is in 'second^0.0909091'.",
        "The units in 'p = pow(pCst, 1.0/13.0)' in component 'main' are not equivalent. 'p' is 'dimensionless' while 'pow(pCst, 1.0/13.0)' is in 'volt^0.0769231' (i.e. 'ampere^-0.0769231 x kilogram^0.0769231 x metre^0.153846 x second^-0.230769').",
        "The units in 'q = pow(qCst, 1.0/15.0)' in component 'main' are not equivalent. 'q' is 'dimensionless' while 'pow(qCst, 1.0/15.0)' is in 'frog^0.0666667'.",
        "The units in 'r = pow(rCst, 1.0/17.0)' in component 'main' are not equivalent. 'r' is 'dimensionless' while 'pow(rCst, 1.0/17.0)' is in 'imaginary^0.0588235' (i.e. '10^-1.76471 x ampere^-0.352941 x frog^0.588235 x kilogram^0.352941 x metre^0.705882 x second^-0.941176').",
    };

    auto analyser = libcellml::Analyser::create();

    analyser->analyseModel(model);

    EXPECT_EQ_ISSUES(expectedIssues, analyser);
}

TEST(AnalyserUnits, abs)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("analyser/units/abs.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    const std::vector<std::string> expectedIssues = {
        "The units in 'b = abs(3.0)' in component 'main' are not equivalent. 'b' is 'dimensionless' while 'abs(3.0)' is in 'second'.",
        "The units in 'c = abs(5.0)' in component 'main' are not equivalent. 'c' is 'dimensionless' while 'abs(5.0)' is in 'volt' (i.e. 'ampere^-1 x kilogram x metre^2 x second^-3').",
        "The units in 'd = abs(7.0)' in component 'main' are not equivalent. 'd' is 'dimensionless' while 'abs(7.0)' is in 'frog'.",
        "The units in 'e = abs(9.0)' in component 'main' are not equivalent. 'e' is 'dimensionless' while 'abs(9.0)' is in 'imaginary' (i.e. '10^-30 x ampere^-6 x frog^10 x kilogram^6 x metre^12 x second^-16').",
    };

    auto analyser = libcellml::Analyser::create();

    analyser->analyseModel(model);

    EXPECT_EQ_ISSUES(expectedIssues, analyser);
}

TEST(AnalyserUnits, expLnOperators)
{
    std::vector<std::string> operators = {"exp", "ln"};

    for (const auto &op : operators) {
        auto parser = libcellml::Parser::create();
        auto model = parser->parseModel(fileContents("analyser/units/" + op + ".cellml"));

        EXPECT_EQ(size_t(0), parser->issueCount());

        const std::vector<std::string> expectedIssues = {
            "The unit of 'bCst' in '" + op + "(bCst)' in equation 'b = " + op + "(bCst)' in component 'main' is not dimensionless. 'bCst' is in 'second'.",
            "The unit of 'cCst' in '" + op + "(cCst)' in equation 'c = " + op + "(cCst)' in component 'main' is not dimensionless. 'cCst' is in 'volt' (i.e. 'ampere^-1 x kilogram x metre^2 x second^-3').",
            "The unit of 'dCst' in '" + op + "(dCst)' in equation 'd = " + op + "(dCst)' in component 'main' is not dimensionless. 'dCst' is in 'frog'.",
            "The unit of 'eCst' in '" + op + "(eCst)' in equation 'e = " + op + "(eCst)' in component 'main' is not dimensionless. 'eCst' is in 'imaginary' (i.e. '10^-30 x ampere^-6 x frog^10 x kilogram^6 x metre^12 x second^-16').",
        };

        auto analyser = libcellml::Analyser::create();

        analyser->analyseModel(model);

        EXPECT_EQ_ISSUES(expectedIssues, analyser);
    }
}

TEST(AnalyserUnits, log)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("analyser/units/log.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    const std::vector<std::string> expectedIssues = {
        "The unit of 'bCst' in 'log(bCst)' in equation 'b = log(bCst)' in component 'main' is not dimensionless. 'bCst' is in 'second'.",
        "The unit of 'cCst' in 'log(cCst)' in equation 'c = log(cCst)' in component 'main' is not dimensionless. 'cCst' is in 'volt' (i.e. 'ampere^-1 x kilogram x metre^2 x second^-3').",
        "The unit of 'dCst' in 'log(dCst)' in equation 'd = log(dCst)' in component 'main' is not dimensionless. 'dCst' is in 'frog'.",
        "The unit of 'eCst' in 'log(eCst)' in equation 'e = log(eCst)' in component 'main' is not dimensionless. 'eCst' is in 'imaginary' (i.e. '10^-30 x ampere^-6 x frog^10 x kilogram^6 x metre^12 x second^-16').",
        "The units of '3.0' and 'gCst' in 'ln(gCst)/ln(3.0)' in equation 'g = ln(gCst)/ln(3.0)' in component 'main' are not dimensionless. '3.0' is in 'second' while 'gCst' is in 'second'.",
        "The units of '5.0' and 'hCst' in 'ln(hCst)/ln(5.0)' in equation 'h = ln(hCst)/ln(5.0)' in component 'main' are not dimensionless. '5.0' is in 'volt' (i.e. 'ampere^-1 x kilogram x metre^2 x second^-3') while 'hCst' is in 'volt' (i.e. 'ampere^-1 x kilogram x metre^2 x second^-3').",
        "The units of '7.0' and 'iCst' in 'ln(iCst)/ln(7.0)' in equation 'i = ln(iCst)/ln(7.0)' in component 'main' are not dimensionless. '7.0' is in 'frog' while 'iCst' is in 'frog'.",
        "The units of '9.0' and 'jCst' in 'ln(jCst)/ln(9.0)' in equation 'j = ln(jCst)/ln(9.0)' in component 'main' are not dimensionless. '9.0' is in 'imaginary' (i.e. '10^-30 x ampere^-6 x frog^10 x kilogram^6 x metre^12 x second^-16') while 'jCst' is in 'imaginary' (i.e. '10^-30 x ampere^-6 x frog^10 x kilogram^6 x metre^12 x second^-16').",
        "The unit of '13.0' in 'ln(lCst)/ln(13.0)' in equation 'l = ln(lCst)/ln(13.0)' in component 'main' is not dimensionless. '13.0' is in 'second'.",
        "The unit of '15.0' in 'ln(mCst)/ln(15.0)' in equation 'm = ln(mCst)/ln(15.0)' in component 'main' is not dimensionless. '15.0' is in 'volt' (i.e. 'ampere^-1 x kilogram x metre^2 x second^-3').",
        "The unit of '17.0' in 'ln(nCst)/ln(17.0)' in equation 'n = ln(nCst)/ln(17.0)' in component 'main' is not dimensionless. '17.0' is in 'frog'.",
        "The unit of '19.0' in 'ln(oCst)/ln(19.0)' in equation 'o = ln(oCst)/ln(19.0)' in component 'main' is not dimensionless. '19.0' is in 'imaginary' (i.e. '10^-30 x ampere^-6 x frog^10 x kilogram^6 x metre^12 x second^-16').",
    };

    auto analyser = libcellml::Analyser::create();

    analyser->analyseModel(model);

    EXPECT_EQ_ISSUES(expectedIssues, analyser);
}

TEST(AnalyserUnits, floorCeilingOperators)
{
    std::vector<std::pair<std::string, std::string>> operators = {
        {"floor", "floor"},
        {"ceiling", "ceil"},
    };

    for (const auto &op : operators) {
        auto parser = libcellml::Parser::create();
        auto model = parser->parseModel(fileContents("analyser/units/" + op.first + ".cellml"));

        EXPECT_EQ(size_t(0), parser->issueCount());

        const std::vector<std::string> expectedIssues = {
            "The units in 'b = " + op.second + "(3.0)' in component 'main' are not equivalent. 'b' is 'dimensionless' while '" + op.second + "(3.0)' is in 'second'.",
            "The units in 'c = " + op.second + "(5.0)' in component 'main' are not equivalent. 'c' is 'dimensionless' while '" + op.second + "(5.0)' is in 'volt' (i.e. 'ampere^-1 x kilogram x metre^2 x second^-3').",
            "The units in 'd = " + op.second + "(7.0)' in component 'main' are not equivalent. 'd' is 'dimensionless' while '" + op.second + "(7.0)' is in 'frog'.",
            "The units in 'e = " + op.second + "(9.0)' in component 'main' are not equivalent. 'e' is 'dimensionless' while '" + op.second + "(9.0)' is in 'imaginary' (i.e. '10^-30 x ampere^-6 x frog^10 x kilogram^6 x metre^12 x second^-16').",
        };

        auto analyser = libcellml::Analyser::create();

        analyser->analyseModel(model);

        EXPECT_EQ_ISSUES(expectedIssues, analyser);
    }
}

TEST(AnalyserUnits, minMaxOperators)
{
    std::vector<std::string> operators = {"min", "max"};

    for (const auto &op : operators) {
        auto parser = libcellml::Parser::create();
        auto model = parser->parseModel(fileContents("analyser/units/" + op + ".cellml"));

        EXPECT_EQ(size_t(0), parser->issueCount());

        const std::vector<std::string> expectedIssues = {
            "The units in '" + op + "(bCst, 3.0)' in equation 'b = " + op + "(bCst, 3.0)' in component 'main' are not equivalent. 'bCst' is in 'second' while '3.0' is 'dimensionless'.",
            "The units in '" + op + "(cCst, 5.0)' in equation 'c = " + op + "(cCst, 5.0)' in component 'main' are not equivalent. 'cCst' is in 'volt' (i.e. 'ampere^-1 x kilogram x metre^2 x second^-3') while '5.0' is 'dimensionless'.",
            "The units in '" + op + "(dCst, 7.0)' in equation 'd = " + op + "(dCst, 7.0)' in component 'main' are not equivalent. 'dCst' is in 'frog' while '7.0' is 'dimensionless'.",
            "The units in '" + op + "(eCst, 9.0)' in equation 'e = " + op + "(eCst, 9.0)' in component 'main' are not equivalent. 'eCst' is in 'imaginary' (i.e. '10^-30 x ampere^-6 x frog^10 x kilogram^6 x metre^12 x second^-16') while '9.0' is 'dimensionless'.",
            "The units in '" + op + "(fCst, 11.0)' in equation 'f = " + op + "(fCst, 11.0)' in component 'main' are not equivalent. 'fCst' is in 'second' while '11.0' is in 'imaginary' (i.e. '10^-30 x ampere^-6 x frog^10 x kilogram^6 x metre^12 x second^-16').",
            "The units in '" + op + "(13.0, 15.0)' in '" + op + "(gCst, " + op + "(13.0, 15.0))' in equation 'g = " + op + "(gCst, " + op + "(13.0, 15.0))' in component 'main' are not equivalent. '13.0' is in 'frog' while '15.0' is in 'imaginary' (i.e. '10^-30 x ampere^-6 x frog^10 x kilogram^6 x metre^12 x second^-16').",
        };

        auto analyser = libcellml::Analyser::create();

        analyser->analyseModel(model);

        EXPECT_EQ_ISSUES(expectedIssues, analyser);
    }
}

TEST(AnalyserUnits, rem)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("analyser/units/rem.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    const std::vector<std::string> expectedIssues = {
        "The units in 'rem(bCst, 3.0)' in equation 'b = rem(bCst, 3.0)' in component 'main' are not equivalent. 'bCst' is in 'second' while '3.0' is 'dimensionless'.",
        "The units in 'rem(cCst, 5.0)' in equation 'c = rem(cCst, 5.0)' in component 'main' are not equivalent. 'cCst' is in 'volt' (i.e. 'ampere^-1 x kilogram x metre^2 x second^-3') while '5.0' is 'dimensionless'.",
        "The units in 'rem(dCst, 7.0)' in equation 'd = rem(dCst, 7.0)' in component 'main' are not equivalent. 'dCst' is in 'frog' while '7.0' is 'dimensionless'.",
        "The units in 'rem(eCst, 9.0)' in equation 'e = rem(eCst, 9.0)' in component 'main' are not equivalent. 'eCst' is in 'imaginary' (i.e. '10^-30 x ampere^-6 x frog^10 x kilogram^6 x metre^12 x second^-16') while '9.0' is 'dimensionless'.",
        "The units in 'rem(fCst, 11.0)' in equation 'f = rem(fCst, 11.0)' in component 'main' are not equivalent. 'fCst' is in 'second' while '11.0' is in 'imaginary' (i.e. '10^-30 x ampere^-6 x frog^10 x kilogram^6 x metre^12 x second^-16').",
    };

    auto analyser = libcellml::Analyser::create();

    analyser->analyseModel(model);

    EXPECT_EQ_ISSUES(expectedIssues, analyser);
}

TEST(AnalyserUnits, trigonometricOperators)
{
    std::vector<std::string> operators = {"sin", "cos", "tan", "sec", "csc", "cot", "sinh", "cosh", "tanh", "sech", "csch", "coth", "arcsin", "arccos", "arctan", "arcsec", "arccsc", "arccot", "arcsinh", "arccosh", "arctanh", "arcsech", "arccsch", "arccoth"};

    for (const auto &op : operators) {
        auto parser = libcellml::Parser::create();
        auto model = parser->parseModel(fileContents("analyser/units/" + op + ".cellml"));

        EXPECT_EQ(size_t(0), parser->issueCount());

        const std::vector<std::string> expectedIssues = {
            "The unit of '3.0' in '" + op + "(3.0)' in equation 'b = " + op + "(3.0)' in component 'main' is not dimensionless. '3.0' is in 'second'.",
            "The unit of '5.0' in '" + op + "(5.0)' in equation 'c = " + op + "(5.0)' in component 'main' is not dimensionless. '5.0' is in 'volt' (i.e. 'ampere^-1 x kilogram x metre^2 x second^-3').",
            "The unit of '7.0' in '" + op + "(7.0)' in equation 'd = " + op + "(7.0)' in component 'main' is not dimensionless. '7.0' is in 'frog'.",
            "The unit of '9.0' in '" + op + "(9.0)' in equation 'e = " + op + "(9.0)' in component 'main' is not dimensionless. '9.0' is in 'imaginary' (i.e. '10^-30 x ampere^-6 x frog^10 x kilogram^6 x metre^12 x second^-16').",
        };

        auto analyser = libcellml::Analyser::create();

        analyser->analyseModel(model);

        EXPECT_EQ_ISSUES(expectedIssues, analyser);
    }
}

TEST(AnalyserUnits, constants)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("analyser/units/constants.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    const std::vector<std::string> expectedIssues = {
        "The units in 'a = true' in component 'main' are not equivalent. 'a' is in 'second' while 'true' is 'dimensionless'.",
        "The units in 'b = false' in component 'main' are not equivalent. 'b' is in 'second' while 'false' is 'dimensionless'.",
        "The units in 'c = exponentiale' in component 'main' are not equivalent. 'c' is in 'second' while 'exponentiale' is 'dimensionless'.",
        "The units in 'd = pi' in component 'main' are not equivalent. 'd' is in 'second' while 'pi' is 'dimensionless'.",
        "The units in 'e = infinity' in component 'main' are not equivalent. 'e' is in 'second' while 'infinity' is 'dimensionless'.",
        "The units in 'f = notanumber' in component 'main' are not equivalent. 'f' is in 'second' while 'notanumber' is 'dimensionless'.",
    };

    auto analyser = libcellml::Analyser::create();

    analyser->analyseModel(model);

    EXPECT_EQ_ISSUES(expectedIssues, analyser);
}

TEST(AnalyserUnits, multipliers)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("analyser/units/multipliers.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    const std::vector<std::string> expectedIssues = {
        "The units in 'a = 1.0' in component 'main' are not equivalent. 'a' is in 'second' while '1.0' is in 'millisecond' (i.e. '10^-3 x second').",
        "The units in 'b = 3.0' in component 'main' are not equivalent. 'b' is in 'volt' (i.e. 'ampere^-1 x kilogram x metre^2 x second^-3') while '3.0' is in 'millivolt' (i.e. '10^-3 x ampere^-1 x kilogram x metre^2 x second^-3').",
        "The units in 'c = 5.0' in component 'main' are not equivalent. 'c' is in 'frog' while '5.0' is in 'millifrog' (i.e. '10^-3 x frog').",
        "The units in 'd = 7.0' in component 'main' are not equivalent. 'd' is in 'imaginary' (i.e. '10^-30 x ampere^-6 x frog^10 x kilogram^6 x metre^12 x second^-16') while '7.0' is in 'milliimaginary' (i.e. '10^-48 x ampere^-6 x frog^10 x kilogram^6 x metre^12 x second^-16').",
    };

    auto analyser = libcellml::Analyser::create();

    analyser->analyseModel(model);

    EXPECT_EQ_ISSUES(expectedIssues, analyser);
}

TEST(AnalyserUnits, rhs)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("analyser/units/rhs.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    const std::vector<std::string> expectedIssues = {
        "The unit of '1.0' in 'sin(1.0)' in equation 'sin(1.0) = a' in component 'main' is not dimensionless. '1.0' is in 'second'.",
    };

    auto analyser = libcellml::Analyser::create();

    analyser->analyseModel(model);

    EXPECT_EQ_ISSUES(expectedIssues, analyser);
}

TEST(AnaylserUnits, compoundEquivalentUnits)
{
    auto m = libcellml::Model::create("compound_units");
    auto c = libcellml::Component::create("main");
    auto a = libcellml::Variable::create("a");
    auto o = libcellml::Variable::create("o");

    auto gas = libcellml::Units::create("gas_constant");
    gas->addUnit(libcellml::Units::StandardUnit::KELVIN, -1.0);
    gas->addUnit(libcellml::Units::StandardUnit::METRE, 3.0);
    gas->addUnit(libcellml::Units::StandardUnit::MOLE, -1.0);
    gas->addUnit(libcellml::Units::StandardUnit::PASCAL);

    auto apple = libcellml::Units::create("apple");
    apple->addUnit(libcellml::Units::StandardUnit::METRE, 3.0);
    apple->addUnit(libcellml::Units::StandardUnit::PASCAL);

    auto orange = libcellml::Units::create("orange");
    orange->addUnit("gas_constant");
    orange->addUnit(libcellml::Units::StandardUnit::KELVIN);
    orange->addUnit(libcellml::Units::StandardUnit::MOLE);

    c->addVariable(a);
    a->setUnits(apple);

    c->addVariable(o);
    o->setUnits(orange);
    o->setInitialValue(3.5);

    m->addUnits(apple);
    m->addUnits(orange);
    m->addUnits(gas);

    m->addComponent(c);

    c->setMath(
        "<math xmlns=\"http://www.w3.org/1998/Math/MathML\">"
        "  <apply>"
        "    <eq/>"
        "    <ci>a</ci>"
        "    <ci>o</ci>"
        "  </apply>"
        "</math>");

    auto analyser = libcellml::Analyser::create();
    analyser->analyseModel(m);

    EXPECT_EQ(size_t(0), analyser->warningCount());
}

TEST(AnaylserUnits, compoundEquivalentUnitsMismatch)
{
    const std::vector<std::string> expectedIssues = {
        "The units in 'a = o' in component 'main' are not equivalent. 'a' is in 'apple' (i.e. 'kilogram x metre^2 x second^-2') while 'o' is in 'orange' (i.e. 'ampere^-2 x kilogram x metre^5 x second^-3').",
    };

    auto m = libcellml::Model::create("compound_units");
    auto c = libcellml::Component::create("main");
    auto a = libcellml::Variable::create("a");
    auto o = libcellml::Variable::create("o");

    auto gas = libcellml::Units::create("gas_constant");
    gas->addUnit(libcellml::Units::StandardUnit::KELVIN, -1.0);
    gas->addUnit(libcellml::Units::StandardUnit::METRE, 3.0);
    gas->addUnit(libcellml::Units::StandardUnit::MOLE, -1.0);
    gas->addUnit(libcellml::Units::StandardUnit::OHM);

    auto apple = libcellml::Units::create("apple");
    apple->addUnit(libcellml::Units::StandardUnit::METRE, 3.0);
    apple->addUnit(libcellml::Units::StandardUnit::PASCAL);

    auto orange = libcellml::Units::create("orange");
    orange->addUnit("gas_constant");
    orange->addUnit(libcellml::Units::StandardUnit::KELVIN);
    orange->addUnit(libcellml::Units::StandardUnit::MOLE);

    c->addVariable(a);
    a->setUnits(apple);

    c->addVariable(o);
    o->setUnits(orange);
    o->setInitialValue(3.5);

    m->addUnits(apple);
    m->addUnits(orange);
    m->addUnits(gas);

    m->addComponent(c);

    c->setMath(
        "<math xmlns=\"http://www.w3.org/1998/Math/MathML\">"
        "  <apply>"
        "    <eq/>"
        "    <ci>a</ci>"
        "    <ci>o</ci>"
        "  </apply>"
        "</math>");

    auto analyser = libcellml::Analyser::create();
    analyser->analyseModel(m);

    EXPECT_EQ(size_t(1), analyser->warningCount());
    EXPECT_EQ_ISSUES(expectedIssues, analyser);
}

TEST(AnalyserUnits, complexUnits)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("analyser/units/complex_units.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    const std::vector<std::string> expectedIssues = {
        "The units in 'a = 1.0' in component 'main' are not equivalent. 'a' is in 'apple' (i.e. '10^-27 x second^3') while '1.0' is in 'orange' (i.e. '10^-9 x second^7').",
        "The units in 'b = 1.0/1.0' in component 'main' are not equivalent. 'b' is in 'apple' (i.e. '10^-27 x second^3') while '1.0/1.0' is in 'orange x second_2^-1' (i.e. '10^-9 x second^5').",
        "The units in 'c = 1.0/(1.0/1.0)' in component 'main' are not equivalent. 'c' is in 'apple' (i.e. '10^-27 x second^3') while '1.0/(1.0/1.0)' is in 'atto_second x orange x second_2^-1' (i.e. '10^-27 x second^6').",
        "The units in 'd = 1.0/(1.0/1.0)/1.0' in component 'main' are not equivalent. 'd' is in 'apple' (i.e. '10^-27 x second^3') while '1.0/(1.0/1.0)/1.0' is in 'atto_second x orange x second_2^-2' (i.e. '10^-27 x second^4').",
    };

    auto analyser = libcellml::Analyser::create();

    analyser->analyseModel(model);

    EXPECT_EQ_ISSUES(expectedIssues, analyser);
}

TEST(AnalyserUnits, fabbriFantiniWildersSeveriHumanSanModel2017WithIncompatibleUnits)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("analyser/units/fabbri_fantini_wilders_severi_human_san_model_2017_with_incompatible_units.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    const std::vector<std::string> expectedIssues = {
        "The unit of '1.2' in 'pow(Km_Kp/Ko, 1.2)' in '1.0+pow(Km_Kp/Ko, 1.2)' in 'pow(1.0+pow(Km_Kp/Ko, 1.2), -1.0)' in 'pow(1.0+pow(Km_Kp/Ko, 1.2), -1.0)*pow(1.0+pow(Km_Nap/Nai, 1.3), -1.0)*pow(1.0+exp(-(V-E_Na+110.0)/20.0), -1.0)' in 'i_NaK_max*pow(1.0+pow(Km_Kp/Ko, 1.2), -1.0)*pow(1.0+pow(Km_Nap/Nai, 1.3), -1.0)*pow(1.0+exp(-(V-E_Na+110.0)/20.0), -1.0)' in 'Iso_increase*i_NaK_max*pow(1.0+pow(Km_Kp/Ko, 1.2), -1.0)*pow(1.0+pow(Km_Nap/Nai, 1.3), -1.0)*pow(1.0+exp(-(V-E_Na+110.0)/20.0), -1.0)' in equation 'i_NaK = Iso_increase*i_NaK_max*pow(1.0+pow(Km_Kp/Ko, 1.2), -1.0)*pow(1.0+pow(Km_Nap/Nai, 1.3), -1.0)*pow(1.0+exp(-(V-E_Na+110.0)/20.0), -1.0)' in component 'i_NaK' is not dimensionless. '1.2' is in 'second'.",
        "The units in 'ACh > 0.0' in '(ACh > 0.0)?0.7*ACh/(0.00009+ACh)' in '(ACh > 0.0)?0.7*ACh/(0.00009+ACh):0.0' in '(Iso_1_uM > 0.0)?-0.25:(ACh > 0.0)?0.7*ACh/(0.00009+ACh):0.0' in equation 'b_up = (Iso_1_uM > 0.0)?-0.25:(ACh > 0.0)?0.7*ACh/(0.00009+ACh):0.0' in component 'Ca_intracellular_fluxes' are not equivalent. 'ACh' is in 'millimolar' (i.e. 'metre^-3 x mole') while '0.0' is in 'millimolar4' (i.e. 'metre^-12 x mole^4').",
        "The unit of 'ACh > 0.0' in '(ACh > 0.0)?0.7*ACh/(0.00009+ACh)' in '(ACh > 0.0)?0.7*ACh/(0.00009+ACh):0.0' in '(Iso_1_uM > 0.0)?-0.25:(ACh > 0.0)?0.7*ACh/(0.00009+ACh):0.0' in equation 'b_up = (Iso_1_uM > 0.0)?-0.25:(ACh > 0.0)?0.7*ACh/(0.00009+ACh):0.0' in component 'Ca_intracellular_fluxes' is not dimensionless. 'ACh > 0.0' is in 'millimolar' (i.e. 'metre^-3 x mole').",
        "The units in '-1.0-9.898*pow(1.0*ACh, 0.618)/(pow(1.0*ACh, 0.618)+0.00122423)' in '(ACh > 0.0)?-1.0-9.898*pow(1.0*ACh, 0.618)/(pow(1.0*ACh, 0.618)+0.00122423)' in '(ACh > 0.0)?-1.0-9.898*pow(1.0*ACh, 0.618)/(pow(1.0*ACh, 0.618)+0.00122423):0.0' in equation 'ACh_shift = (ACh > 0.0)?-1.0-9.898*pow(1.0*ACh, 0.618)/(pow(1.0*ACh, 0.618)+0.00122423):0.0' in component 'i_f_y_gate' are not equivalent. '-1.0' is in 'millivolt' (i.e. '10^-3 x ampere^-1 x kilogram x metre^2 x second^-3') while '9.898*pow(1.0*ACh, 0.618)/(pow(1.0*ACh, 0.618)+0.00122423)' is in 'volt' (i.e. 'ampere^-1 x kilogram x metre^2 x second^-3').",
        "The units in '0.36*(V+148.8-ACh_shift-Iso_shift)/(exp(0.066*(V+148.8-ACh_shift-Iso_shift))-1.0)+0.1*(V+87.3-ACh_shift-Iso_shift)/(1.0-exp(-0.2*(V+87.3-ACh_shift-Iso_shift)))' in '1.0/(0.36*(V+148.8-ACh_shift-Iso_shift)/(exp(0.066*(V+148.8-ACh_shift-Iso_shift))-1.0)+0.1*(V+87.3-ACh_shift-Iso_shift)/(1.0-exp(-0.2*(V+87.3-ACh_shift-Iso_shift))))' in '1.0/(0.36*(V+148.8-ACh_shift-Iso_shift)/(exp(0.066*(V+148.8-ACh_shift-Iso_shift))-1.0)+0.1*(V+87.3-ACh_shift-Iso_shift)/(1.0-exp(-0.2*(V+87.3-ACh_shift-Iso_shift))))-0.054' in equation 'tau_y = 1.0/(0.36*(V+148.8-ACh_shift-Iso_shift)/(exp(0.066*(V+148.8-ACh_shift-Iso_shift))-1.0)+0.1*(V+87.3-ACh_shift-Iso_shift)/(1.0-exp(-0.2*(V+87.3-ACh_shift-Iso_shift))))-0.054' in component 'i_f_y_gate' are not equivalent. '0.36*(V+148.8-ACh_shift-Iso_shift)/(exp(0.066*(V+148.8-ACh_shift-Iso_shift))-1.0)' is 'dimensionless' while '0.1*(V+87.3-ACh_shift-Iso_shift)/(1.0-exp(-0.2*(V+87.3-ACh_shift-Iso_shift)))' is in 'millivolt x per_millivolt_second' (i.e. 'second^-1').",
        "The units in '0.01329+0.99921/(1.0+exp((V+97.134-ACh_shift-Iso_shift-y_shift)/8.1752))' in '(V < -(80.0-ACh_shift-Iso_shift-y_shift))?0.01329+0.99921/(1.0+exp((V+97.134-ACh_shift-Iso_shift-y_shift)/8.1752))' in '(V < -(80.0-ACh_shift-Iso_shift-y_shift))?0.01329+0.99921/(1.0+exp((V+97.134-ACh_shift-Iso_shift-y_shift)/8.1752)):0.0002501*exp(-(V-ACh_shift-Iso_shift-y_shift)/12.861)' in equation 'y_infinity = (V < -(80.0-ACh_shift-Iso_shift-y_shift))?0.01329+0.99921/(1.0+exp((V+97.134-ACh_shift-Iso_shift-y_shift)/8.1752)):0.0002501*exp(-(V-ACh_shift-Iso_shift-y_shift)/12.861)' in component 'i_f_y_gate' are not equivalent. '0.01329' is 'dimensionless' while '0.99921/(1.0+exp((V+97.134-ACh_shift-Iso_shift-y_shift)/8.1752))' is in 'ampere'.",
        "The units in 'V+42.0504' in '-(V+42.0504)' in '-(V+42.0504)/8.3106' in 'exp(-(V+42.0504)/8.3106)' in '1.0+exp(-(V+42.0504)/8.3106)' in '1.0/(1.0+exp(-(V+42.0504)/8.3106))' in equation 'm_infinity = 1.0/(1.0+exp(-(V+42.0504)/8.3106))' in component 'i_Na_m_gate' are not equivalent. 'V' is in 'millivolt' (i.e. '10^-3 x ampere^-1 x kilogram x metre^2 x second^-3') while '42.0504' is in 'per_millivolt' (i.e. '10^3 x ampere x kilogram^-1 x metre^-2 x second^3').",
        "The units in '1.0+exp((V+69.804)/4.4565)' in '1.0/(1.0+exp((V+69.804)/4.4565))' in equation 'h_infinity = 1.0/(1.0+exp((V+69.804)/4.4565))' in component 'i_Na_h_gate' are not equivalent. '1.0' is 'dimensionless' while 'exp((V+69.804)/4.4565)' is in 'millivolt x volt^-1' (i.e. '10^-3').",
        "The units in '320.0*exp(-0.1*(V+75.0))+1.0' in '2000.0/(320.0*exp(-0.1*(V+75.0))+1.0)' in equation 'beta_h = 2000.0/(320.0*exp(-0.1*(V+75.0))+1.0)' in component 'i_Na_h_gate' are not equivalent. '320.0*exp(-0.1*(V+75.0))' is in 'millivolt x per_millivolt x per_second' (i.e. 'second^-1') while '1.0' is 'dimensionless'.",
        "The units in 'i_CaL = (i_siCa+i_siK+i_siNa)*(1.0-ACh_block)*1.0*Iso_increase' in component 'i_CaL' are not equivalent. 'i_CaL' is in 'nanoA' (i.e. '10^-9 x ampere') while '(i_siCa+i_siK+i_siNa)*(1.0-ACh_block)*1.0*Iso_increase' is in 'millivolt x nanoA' (i.e. '10^-12 x kilogram x metre^2 x second^-3').",
        "The units in '-0.02839*(adVm+41.8)/(exp(-(adVm+41.8)/2.5)-1.0)-0.0849*(adVm+6.8)/(exp(-(adVm+6.8)/4.8)-1.0)' in equation 'alpha_dL = -0.02839*(adVm+41.8)/(exp(-(adVm+41.8)/2.5)-1.0)-0.0849*(adVm+6.8)/(exp(-(adVm+6.8)/4.8)-1.0)' in component 'i_CaL_dL_gate' are not equivalent. '-0.02839*(adVm+41.8)/(exp(-(adVm+41.8)/2.5)-1.0)' is in 'millivolt x per_millivolt_second' (i.e. 'second^-1') while '0.0849*(adVm+6.8)/(exp(-(adVm+6.8)/4.8)-1.0)' is in 'millivolt x per_second' (i.e. '10^-3 x ampere^-1 x kilogram x metre^2 x second^-4').",
        "The unit of '-pow((V+36.0)/10.0, 2.0)' in 'exp(-pow((V+36.0)/10.0, 2.0))' in '230.0*exp(-pow((V+36.0)/10.0, 2.0))' in '44.3+230.0*exp(-pow((V+36.0)/10.0, 2.0))' in '0.001*(44.3+230.0*exp(-pow((V+36.0)/10.0, 2.0)))' in equation 'tau_fL = 0.001*(44.3+230.0*exp(-pow((V+36.0)/10.0, 2.0)))' in component 'i_CaL_fL_gate' is not dimensionless. '-pow((V+36.0)/10.0, 2.0)' is in 'ampere^-2 x millivolt^2' (i.e. '10^-6 x ampere^-4 x kilogram^2 x metre^4 x second^-6').",
        "The units in 'i_KACh = (ACh > 0.0)?ACh_on*g_KACh*(V-E_K)*(1.0+exp((V+20.0)/20.0))*a:0.0' in component 'i_KACh' are not equivalent. 'i_KACh' is in 'nanoA' (i.e. '10^-9 x ampere') while '(ACh > 0.0)?ACh_on*g_KACh*(V-E_K)*(1.0+exp((V+20.0)/20.0))*a:0.0' is in 'microS x millivolt' and 'ampere' (i.e. '10^-9 x ampere' and 'ampere').",
    };

    auto analyser = libcellml::Analyser::create();

    analyser->analyseModel(model);

    EXPECT_EQ_ISSUES(expectedIssues, analyser);
}

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
        "The units in 'e = eCst' in component 'main' are not equivalent. 'e' is 'dimensionless' while 'eCst' is in 'imaginary' (i.e. '10^-66 x ampere^-6 x frog^10 x kilogram^6 x metre^12 x second^-16').",
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
        "The units in 'e = 9.0' in component 'main' are not equivalent. 'e' is 'dimensionless' while '9.0' is in 'imaginary' (i.e. '10^-66 x ampere^-6 x frog^10 x kilogram^6 x metre^12 x second^-16').",
        "The units in 'g = 13.0e3' in component 'main' are not equivalent. 'g' is 'dimensionless' while '13.0e3' is in 'second'.",
        "The units in 'h = 15.0e5' in component 'main' are not equivalent. 'h' is 'dimensionless' while '15.0e5' is in 'volt' (i.e. 'ampere^-1 x kilogram x metre^2 x second^-3').",
        "The units in 'i = 17.0e7' in component 'main' are not equivalent. 'i' is 'dimensionless' while '17.0e7' is in 'frog'.",
        "The units in 'j = 19.0e9' in component 'main' are not equivalent. 'j' is 'dimensionless' while '19.0e9' is in 'imaginary' (i.e. '10^-66 x ampere^-6 x frog^10 x kilogram^6 x metre^12 x second^-16').",
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
        "The units in 'e > 27.0' in '(e > 27.0)?25.0' in '(e > 27.0)?25.0:29.0' in equation 'e = (e > 27.0)?25.0:29.0' in component 'main' are not equivalent. 'e' is 'dimensionless' while '27.0' is in 'imaginary' (i.e. '10^-66 x ampere^-6 x frog^10 x kilogram^6 x metre^12 x second^-16').",
        "The units in 'f = (f > 33.0)?31.0:(f > 37.0)?35.0:(f > 41.0)?39.0:(f > 45.0)?43.0:(f > 49.0)?47.0:51.0' in component 'main' are not equivalent. 'f' is 'dimensionless' while '(f > 33.0)?31.0:(f > 37.0)?35.0:(f > 41.0)?39.0:(f > 45.0)?43.0:(f > 49.0)?47.0:51.0' is in 'second', 'volt', 'frog' and 'imaginary' (i.e. 'second', 'ampere^-1 x kilogram x metre^2 x second^-3', 'frog' and '10^-66 x ampere^-6 x frog^10 x kilogram^6 x metre^12 x second^-16').",
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
            "The units in 'eCst " + op.second + " 9.0' in equation 'e = eCst " + op.second + " 9.0' in component 'main' are not equivalent. 'eCst' is in 'imaginary' (i.e. '10^-66 x ampere^-6 x frog^10 x kilogram^6 x metre^12 x second^-16') while '9.0' is 'dimensionless'.",
            "The units in 'fCst " + op.second + " 11.0' in equation 'f = fCst " + op.second + " 11.0' in component 'main' are not equivalent. 'fCst' is in 'second' while '11.0' is in 'imaginary' (i.e. '10^-66 x ampere^-6 x frog^10 x kilogram^6 x metre^12 x second^-16').",
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
            "The unit of 'eCst' in 'eCst " + op.second + " 9.0' in equation 'e = eCst " + op.second + " 9.0' in component 'main' is not dimensionless. 'eCst' is in 'imaginary' (i.e. '10^-66 x ampere^-6 x frog^10 x kilogram^6 x metre^12 x second^-16').",
            "The units of 'fCst' and '11.0' in 'fCst " + op.second + " 11.0' in equation 'f = fCst " + op.second + " 11.0' in component 'main' are not dimensionless. 'fCst' is in 'second' while '11.0' is in 'imaginary' (i.e. '10^-66 x ampere^-6 x frog^10 x kilogram^6 x metre^12 x second^-16').",
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
        "The unit of 'eCst' in 'xor(eCst, 9.0)' in equation 'e = xor(eCst, 9.0)' in component 'main' is not dimensionless. 'eCst' is in 'imaginary' (i.e. '10^-66 x ampere^-6 x frog^10 x kilogram^6 x metre^12 x second^-16').",
        "The units of 'fCst' and '11.0' in 'xor(fCst, 11.0)' in equation 'f = xor(fCst, 11.0)' in component 'main' are not dimensionless. 'fCst' is in 'second' while '11.0' is in 'imaginary' (i.e. '10^-66 x ampere^-6 x frog^10 x kilogram^6 x metre^12 x second^-16').",
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
        "The unit of 'eCst' in '!eCst' in equation 'e = !eCst' in component 'main' is not dimensionless. 'eCst' is in 'imaginary' (i.e. '10^-66 x ampere^-6 x frog^10 x kilogram^6 x metre^12 x second^-16').",
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
        "The units in 'eCst+9.0' in equation 'e = eCst+9.0' in component 'main' are not equivalent. 'eCst' is in 'imaginary' (i.e. '10^-66 x ampere^-6 x frog^10 x kilogram^6 x metre^12 x second^-16') while '9.0' is 'dimensionless'.",
        "The units in 'fCst+11.0' in equation 'f = fCst+11.0' in component 'main' are not equivalent. 'fCst' is in 'second' while '11.0' is in 'imaginary' (i.e. '10^-66 x ampere^-6 x frog^10 x kilogram^6 x metre^12 x second^-16').",
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
        "The units in 'e = -eCst' in component 'main' are not equivalent. 'e' is 'dimensionless' while '-eCst' is in 'imaginary' (i.e. '10^-66 x ampere^-6 x frog^10 x kilogram^6 x metre^12 x second^-16').",
        "The units in 'gCst-3.0' in equation 'g = gCst-3.0' in component 'main' are not equivalent. 'gCst' is in 'second' while '3.0' is 'dimensionless'.",
        "The units in 'hCst-5.0' in equation 'h = hCst-5.0' in component 'main' are not equivalent. 'hCst' is in 'volt' (i.e. 'ampere^-1 x kilogram x metre^2 x second^-3') while '5.0' is 'dimensionless'.",
        "The units in 'iCst-7.0' in equation 'i = iCst-7.0' in component 'main' are not equivalent. 'iCst' is in 'frog' while '7.0' is 'dimensionless'.",
        "The units in 'jCst-9.0' in equation 'j = jCst-9.0' in component 'main' are not equivalent. 'jCst' is in 'imaginary' (i.e. '10^-66 x ampere^-6 x frog^10 x kilogram^6 x metre^12 x second^-16') while '9.0' is 'dimensionless'.",
        "The units in 'kCst-11.0' in equation 'k = kCst-11.0' in component 'main' are not equivalent. 'kCst' is in 'second' while '11.0' is in 'imaginary' (i.e. '10^-66 x ampere^-6 x frog^10 x kilogram^6 x metre^12 x second^-16').",
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
        "The units in 'e = eCst*9.0' in component 'main' are not equivalent. 'e' is 'dimensionless' while 'eCst*9.0' is in 'imaginary' (i.e. '10^-66 x ampere^-6 x frog^10 x kilogram^6 x metre^12 x second^-16').",
        "The units in 'f = fCst*11.0' in component 'main' are not equivalent. 'f' is 'dimensionless' while 'fCst*11.0' is in 'imaginary x second' (i.e. '10^-66 x ampere^-6 x frog^10 x kilogram^6 x metre^12 x second^-15').",
        "The units in 'g = gCst*13.0' in component 'main' are not equivalent. 'g' is in 'second_by_volt' (i.e. 'ampere^-1 x kilogram x metre^2 x second^-2') while 'gCst*13.0' is in 'second'.",
        "The units in 'h = hCst*15.0' in component 'main' are not equivalent. 'h' is in 'volt_by_volt' (i.e. 'ampere^-2 x kilogram^2 x metre^4 x second^-6') while 'hCst*15.0' is in 'volt' (i.e. 'ampere^-1 x kilogram x metre^2 x second^-3').",
        "The units in 'i = iCst*17.0' in component 'main' are not equivalent. 'i' is in 'frog_by_volt' (i.e. 'ampere^-1 x frog x kilogram x metre^2 x second^-3') while 'iCst*17.0' is in 'frog'.",
        "The units in 'j = jCst*19.0' in component 'main' are not equivalent. 'j' is in 'imaginary_by_volt' (i.e. '10^-66 x ampere^-7 x frog^10 x kilogram^7 x metre^14 x second^-19') while 'jCst*19.0' is in 'imaginary' (i.e. '10^-66 x ampere^-6 x frog^10 x kilogram^6 x metre^12 x second^-16').",
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
        "The units in 'e = eCst/9.0' in component 'main' are not equivalent. 'e' is 'dimensionless' while 'eCst/9.0' is in 'imaginary' (i.e. '10^-66 x ampere^-6 x frog^10 x kilogram^6 x metre^12 x second^-16').",
        "The units in 'f = fCst/11.0' in component 'main' are not equivalent. 'f' is 'dimensionless' while 'fCst/11.0' is in 'imaginary^-1 x second' (i.e. '10^66 x ampere^6 x frog^-10 x kilogram^-6 x metre^-12 x second^17').",
        "The units in 'g = gCst/13.0' in component 'main' are not equivalent. 'g' is in 'second_per_volt' (i.e. 'ampere x kilogram^-1 x metre^-2 x second^4') while 'gCst/13.0' is in 'second'.",
        "The units in 'h = hCst/15.0' in component 'main' are not equivalent. 'h' is in 'volt_per_volt' (i.e. 'dimensionless') while 'hCst/15.0' is in 'volt' (i.e. 'ampere^-1 x kilogram x metre^2 x second^-3').",
        "The units in 'i = iCst/17.0' in component 'main' are not equivalent. 'i' is in 'frog_per_volt' (i.e. 'ampere x frog x kilogram^-1 x metre^-2 x second^3') while 'iCst/17.0' is in 'frog'.",
        "The units in 'j = jCst/19.0' in component 'main' are not equivalent. 'j' is in 'imaginary_per_volt' (i.e. '10^-66 x ampere^-5 x frog^10 x kilogram^5 x metre^10 x second^-13') while 'jCst/19.0' is in 'imaginary' (i.e. '10^-66 x ampere^-6 x frog^10 x kilogram^6 x metre^12 x second^-16').",
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
        "The unit of '9.0' in 'pow(eCst, 9.0)' in equation 'e = pow(eCst, 9.0)' in component 'main' is not dimensionless. '9.0' is in 'imaginary' (i.e. '10^-66 x ampere^-6 x frog^10 x kilogram^6 x metre^12 x second^-16').",
        "The units in 'f = pow(fCst, 11.0)' in component 'main' are not equivalent. 'f' is 'dimensionless' while 'pow(fCst, 11.0)' is in 'second^11'.",
        "The units in 'g = pow(gCst, 13.0)' in component 'main' are not equivalent. 'g' is 'dimensionless' while 'pow(gCst, 13.0)' is in 'volt^13' (i.e. 'ampere^-13 x kilogram^13 x metre^26 x second^-39').",
        "The units in 'h = pow(hCst, 15.0)' in component 'main' are not equivalent. 'h' is 'dimensionless' while 'pow(hCst, 15.0)' is in 'frog^15'.",
        "The units in 'i = pow(iCst, 17.0)' in component 'main' are not equivalent. 'i' is 'dimensionless' while 'pow(iCst, 17.0)' is in 'imaginary^17' (i.e. '10^-1122 x ampere^-102 x frog^170 x kilogram^102 x metre^204 x second^-272').",
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
        "The units in 'e = sqrt(eCst)' in component 'main' are not equivalent. 'e' is 'dimensionless' while 'sqrt(eCst)' is in 'imaginary^0.5' (i.e. '10^-33 x ampere^-3 x frog^5 x kilogram^3 x metre^6 x second^-8').",
        "The unit of '3.0' in 'pow(kCst, 1.0/3.0)' in equation 'k = pow(kCst, 1.0/3.0)' in component 'main' is not dimensionless. '3.0' is in 'second'.",
        "The unit of '5.0' in 'pow(lCst, 1.0/5.0)' in equation 'l = pow(lCst, 1.0/5.0)' in component 'main' is not dimensionless. '5.0' is in 'volt' (i.e. 'ampere^-1 x kilogram x metre^2 x second^-3').",
        "The unit of '7.0' in 'pow(mCst, 1.0/7.0)' in equation 'm = pow(mCst, 1.0/7.0)' in component 'main' is not dimensionless. '7.0' is in 'frog'.",
        "The unit of '9.0' in 'pow(nCst, 1.0/9.0)' in equation 'n = pow(nCst, 1.0/9.0)' in component 'main' is not dimensionless. '9.0' is in 'imaginary' (i.e. '10^-66 x ampere^-6 x frog^10 x kilogram^6 x metre^12 x second^-16').",
        "The units in 'o = pow(oCst, 1.0/11.0)' in component 'main' are not equivalent. 'o' is 'dimensionless' while 'pow(oCst, 1.0/11.0)' is in 'second^0.0909091'.",
        "The units in 'p = pow(pCst, 1.0/13.0)' in component 'main' are not equivalent. 'p' is 'dimensionless' while 'pow(pCst, 1.0/13.0)' is in 'volt^0.0769231' (i.e. 'ampere^-0.0769231 x kilogram^0.0769231 x metre^0.153846 x second^-0.230769').",
        "The units in 'q = pow(qCst, 1.0/15.0)' in component 'main' are not equivalent. 'q' is 'dimensionless' while 'pow(qCst, 1.0/15.0)' is in 'frog^0.0666667'.",
        "The units in 'r = pow(rCst, 1.0/17.0)' in component 'main' are not equivalent. 'r' is 'dimensionless' while 'pow(rCst, 1.0/17.0)' is in 'imaginary^0.0588235' (i.e. '10^-3.88235 x ampere^-0.352941 x frog^0.588235 x kilogram^0.352941 x metre^0.705882 x second^-0.941176').",
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
        "The units in 'e = abs(9.0)' in component 'main' are not equivalent. 'e' is 'dimensionless' while 'abs(9.0)' is in 'imaginary' (i.e. '10^-66 x ampere^-6 x frog^10 x kilogram^6 x metre^12 x second^-16').",
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
            "The unit of 'eCst' in '" + op + "(eCst)' in equation 'e = " + op + "(eCst)' in component 'main' is not dimensionless. 'eCst' is in 'imaginary' (i.e. '10^-66 x ampere^-6 x frog^10 x kilogram^6 x metre^12 x second^-16').",
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
        "The unit of 'eCst' in 'log(eCst)' in equation 'e = log(eCst)' in component 'main' is not dimensionless. 'eCst' is in 'imaginary' (i.e. '10^-66 x ampere^-6 x frog^10 x kilogram^6 x metre^12 x second^-16').",
        "The units of '3.0' and 'gCst' in 'ln(gCst)/ln(3.0)' in equation 'g = ln(gCst)/ln(3.0)' in component 'main' are not dimensionless. '3.0' is in 'second' while 'gCst' is in 'second'.",
        "The units of '5.0' and 'hCst' in 'ln(hCst)/ln(5.0)' in equation 'h = ln(hCst)/ln(5.0)' in component 'main' are not dimensionless. '5.0' is in 'volt' (i.e. 'ampere^-1 x kilogram x metre^2 x second^-3') while 'hCst' is in 'volt' (i.e. 'ampere^-1 x kilogram x metre^2 x second^-3').",
        "The units of '7.0' and 'iCst' in 'ln(iCst)/ln(7.0)' in equation 'i = ln(iCst)/ln(7.0)' in component 'main' are not dimensionless. '7.0' is in 'frog' while 'iCst' is in 'frog'.",
        "The units of '9.0' and 'jCst' in 'ln(jCst)/ln(9.0)' in equation 'j = ln(jCst)/ln(9.0)' in component 'main' are not dimensionless. '9.0' is in 'imaginary' (i.e. '10^-66 x ampere^-6 x frog^10 x kilogram^6 x metre^12 x second^-16') while 'jCst' is in 'imaginary' (i.e. '10^-66 x ampere^-6 x frog^10 x kilogram^6 x metre^12 x second^-16').",
        "The unit of '13.0' in 'ln(lCst)/ln(13.0)' in equation 'l = ln(lCst)/ln(13.0)' in component 'main' is not dimensionless. '13.0' is in 'second'.",
        "The unit of '15.0' in 'ln(mCst)/ln(15.0)' in equation 'm = ln(mCst)/ln(15.0)' in component 'main' is not dimensionless. '15.0' is in 'volt' (i.e. 'ampere^-1 x kilogram x metre^2 x second^-3').",
        "The unit of '17.0' in 'ln(nCst)/ln(17.0)' in equation 'n = ln(nCst)/ln(17.0)' in component 'main' is not dimensionless. '17.0' is in 'frog'.",
        "The unit of '19.0' in 'ln(oCst)/ln(19.0)' in equation 'o = ln(oCst)/ln(19.0)' in component 'main' is not dimensionless. '19.0' is in 'imaginary' (i.e. '10^-66 x ampere^-6 x frog^10 x kilogram^6 x metre^12 x second^-16').",
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
            "The units in 'e = " + op.second + "(9.0)' in component 'main' are not equivalent. 'e' is 'dimensionless' while '" + op.second + "(9.0)' is in 'imaginary' (i.e. '10^-66 x ampere^-6 x frog^10 x kilogram^6 x metre^12 x second^-16').",
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
            "The units in '" + op + "(eCst, 9.0)' in equation 'e = " + op + "(eCst, 9.0)' in component 'main' are not equivalent. 'eCst' is in 'imaginary' (i.e. '10^-66 x ampere^-6 x frog^10 x kilogram^6 x metre^12 x second^-16') while '9.0' is 'dimensionless'.",
            "The units in '" + op + "(fCst, 11.0)' in equation 'f = " + op + "(fCst, 11.0)' in component 'main' are not equivalent. 'fCst' is in 'second' while '11.0' is in 'imaginary' (i.e. '10^-66 x ampere^-6 x frog^10 x kilogram^6 x metre^12 x second^-16').",
            "The units in '" + op + "(13.0, 15.0)' in '" + op + "(gCst, " + op + "(13.0, 15.0))' in equation 'g = " + op + "(gCst, " + op + "(13.0, 15.0))' in component 'main' are not equivalent. '13.0' is in 'frog' while '15.0' is in 'imaginary' (i.e. '10^-66 x ampere^-6 x frog^10 x kilogram^6 x metre^12 x second^-16').",
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
        "The units in 'rem(eCst, 9.0)' in equation 'e = rem(eCst, 9.0)' in component 'main' are not equivalent. 'eCst' is in 'imaginary' (i.e. '10^-66 x ampere^-6 x frog^10 x kilogram^6 x metre^12 x second^-16') while '9.0' is 'dimensionless'.",
        "The units in 'rem(fCst, 11.0)' in equation 'f = rem(fCst, 11.0)' in component 'main' are not equivalent. 'fCst' is in 'second' while '11.0' is in 'imaginary' (i.e. '10^-66 x ampere^-6 x frog^10 x kilogram^6 x metre^12 x second^-16').",
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
            "The unit of '9.0' in '" + op + "(9.0)' in equation 'e = " + op + "(9.0)' in component 'main' is not dimensionless. '9.0' is in 'imaginary' (i.e. '10^-66 x ampere^-6 x frog^10 x kilogram^6 x metre^12 x second^-16').",
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
        "The units in 'd = 7.0' in component 'main' are not equivalent. 'd' is in 'imaginary' (i.e. '10^-66 x ampere^-6 x frog^10 x kilogram^6 x metre^12 x second^-16') while '7.0' is in 'milliimaginary' (i.e. '10^-69 x ampere^-6 x frog^10 x kilogram^6 x metre^12 x second^-16').",
    };

    auto analyser = libcellml::Analyser::create();

    analyser->analyseModel(model);

    EXPECT_EQ_ISSUES(expectedIssues, analyser);
}

TEST(AnalyserUnits, scalingFactorWithMinuteAndPerMinuteUnits)
{
    auto m = libcellml::Model::create("per_minute");
    auto c = libcellml::Component::create("main");
    auto minute = libcellml::Units::create("minute");

    minute->addUnit("second", "", 1.0, 60.0);

    auto perMinute = libcellml::Units::create("per_minute");

    perMinute->addUnit("second", "", -1.0, 1.0 / 60.0);

    auto t = libcellml::Variable::create("t");

    t->setUnits(minute);

    auto x = libcellml::Variable::create("x");

    x->setUnits("mole");
    x->setInitialValue(1.0);

    auto k = libcellml::Variable::create("k");

    k->setUnits(perMinute);
    k->setInitialValue(0.1);

    c->addVariable(t);
    c->addVariable(x);
    c->addVariable(k);

    m->addUnits(minute);
    m->addUnits(perMinute);

    m->addComponent(c);

    c->setMath(
        "<math xmlns=\"http://www.w3.org/1998/Math/MathML\">"
        "  <apply>"
        "    <eq/>"
        "    <apply>"
        "      <diff/>"
        "      <bvar><ci>t</ci></bvar>"
        "      <ci>x</ci>"
        "    </apply>"
        "    <apply>"
        "      <times/>"
        "      <ci>k</ci>"
        "      <ci>x</ci>"
        "    </apply>"
        "  </apply>"
        "</math>");

    auto analyser = libcellml::Analyser::create();

    analyser->analyseModel(m);

    EXPECT_EQ(size_t(0), analyser->issueCount());
}

TEST(AnalyserUnits, scalingFactorWithCustomUnits)
{
    auto m = libcellml::Model::create("prefix");
    auto c = libcellml::Component::create("main");
    auto b = libcellml::Units::create("b");

    b->addUnit("metre");

    auto a = libcellml::Units::create("a");

    a->addUnit("b", "kilo", 2.0, 1.0);

    auto cUnits = libcellml::Units::create("c");

    cUnits->addUnit("metre", "kilo", 2.0, 1.0);

    auto xa = libcellml::Variable::create("xa");

    xa->setUnits(a);
    xa->setInitialValue(1.0);

    auto xc = libcellml::Variable::create("xc");

    xc->setUnits(cUnits);

    c->addVariable(xa);
    c->addVariable(xc);

    m->addUnits(b);
    m->addUnits(a);
    m->addUnits(cUnits);

    m->addComponent(c);

    c->setMath(
        "<math xmlns=\"http://www.w3.org/1998/Math/MathML\">"
        "  <apply>"
        "    <eq/>"
        "    <ci>xa</ci>"
        "    <ci>xc</ci>"
        "  </apply>"
        "</math>");

    auto analyser = libcellml::Analyser::create();

    analyser->analyseModel(m);

    EXPECT_EQ(size_t(0), analyser->issueCount());
}

TEST(AnalyserUnits, inheritedMultiplierAppliedOncePerBranch)
{
    auto m = libcellml::Model::create("per_branch");
    auto c = libcellml::Component::create("main");
    auto b = libcellml::Units::create("b");

    b->addUnit("second");
    b->addUnit("metre");

    auto a = libcellml::Units::create("a");

    a->addUnit("b", "kilo", 2.0, 1.0);

    auto cUnits = libcellml::Units::create("c");

    cUnits->addUnit("second", "", 2.0, 1.0);
    cUnits->addUnit("metre", "", 2.0, 1.0);
    cUnits->addUnit("dimensionless", "", 1.0, 1.0e6);

    auto xa = libcellml::Variable::create("xa");

    xa->setUnits(a);
    xa->setInitialValue(1.0);

    auto xc = libcellml::Variable::create("xc");

    xc->setUnits(cUnits);

    c->addVariable(xa);
    c->addVariable(xc);

    m->addUnits(b);
    m->addUnits(a);
    m->addUnits(cUnits);

    m->addComponent(c);

    c->setMath(
        "<math xmlns=\"http://www.w3.org/1998/Math/MathML\">"
        "  <apply>"
        "    <eq/>"
        "    <ci>xa</ci>"
        "    <ci>xc</ci>"
        "  </apply>"
        "</math>");

    auto analyser = libcellml::Analyser::create();

    analyser->analyseModel(m);

    EXPECT_EQ(size_t(0), analyser->issueCount());
}

TEST(AnalyserUnits, dimensionlessProductWithCancellingUnitsAsFirstOperand)
{
    static const std::string MODEL_START =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/2.0#\" xmlns:cellml=\"http://www.cellml.org/cellml/2.0#\" name=\"m\">\n"
        "  <units name=\"mV\">\n"
        "    <unit prefix=\"milli\" units=\"volt\"/>\n"
        "  </units>\n"
        "  <units name=\"V_per_mV\">\n"
        "    <unit units=\"volt\"/>\n"
        "    <unit exponent=\"-1\" units=\"mV\"/>\n"
        "  </units>\n"
        "  <units name=\"per_V\">\n"
        "    <unit exponent=\"-1\" units=\"volt\"/>\n"
        "  </units>\n"
        "  <component name=\"c\">\n"
        "    <variable name=\"V\" units=\"mV\" initial_value=\"1\"/>\n"
        "    <variable name=\"k\" units=\"per_V\" initial_value=\"1\"/>\n"
        "    <variable name=\"x\" units=\"dimensionless\"/>\n"
        "    <math xmlns=\"http://www.w3.org/1998/Math/MathML\">\n"
        "      <apply>\n"
        "        <eq/>\n"
        "        <ci>x</ci>\n"
        "        <apply>\n"
        "          <exp/>\n"
        "          <apply>\n"
        "            <times/>\n";
    static const std::string MODEL_END =
        "          </apply>\n"
        "        </apply>\n"
        "      </apply>\n"
        "    </math>\n"
        "  </component>\n"
        "</model>\n";
    static const std::string CN = "<cn cellml:units=\"V_per_mV\">2</cn>";
    static const std::string V = "<ci>V</ci>";
    static const std::string K = "<ci>k</ci>";

    auto parser = libcellml::Parser::create();
    auto analyser = libcellml::Analyser::create();

    for (const auto &product : {CN + V + K, V + CN + K, V + K + CN}) {
        analyser->analyseModel(parser->parseModel(MODEL_START + product + MODEL_END));

        EXPECT_EQ(size_t(0), analyser->issueCount());
    }
}

TEST(AnalyserUnits, tinyExponentAmplifiedByPower)
{
    // Raise a constant in units with a tiny exponent (i.e. as tiny as, or tinier than, the machine epsilon) to a power
    // that amplifies that exponent and check that we get the expected units.
    // Note: a tiny exponent must only be discarded if it is genuinely cancelled out by another exponent.

    struct TestCase
    {
        std::string tinySecondUnits;
        std::string base;
        std::string expectedUnits;
    };

    static const std::string TINY_SECOND = "<unit exponent=\"1e-16\" units=\"second\"/>";
    static const std::string MINUS_TINY_SECOND = "<unit exponent=\"-1e-16\" units=\"second\"/>";
    static const std::string ZERO_SECOND = "<unit exponent=\"0\" units=\"second\"/>";
    static const std::string CN = "<cn cellml:units=\"tiny_second\">2</cn>";
    static const std::vector<TestCase> testCases = {
        {TINY_SECOND, CN, "second"},
        {TINY_SECOND + ZERO_SECOND, CN, "second"},
        {ZERO_SECOND + TINY_SECOND, CN, "second"},
        {TINY_SECOND + TINY_SECOND, CN, "second_squared"},
        {TINY_SECOND + MINUS_TINY_SECOND, CN, "dimensionless"},
        {MINUS_TINY_SECOND + TINY_SECOND, CN, "dimensionless"},
        {TINY_SECOND, "<apply><times/>" + CN + CN + "</apply>", "second_squared"},
        {TINY_SECOND, "<apply><divide/>" + CN + CN + "</apply>", "dimensionless"},
    };

    auto parser = libcellml::Parser::create();
    auto analyser = libcellml::Analyser::create();

    for (const auto &testCase : testCases) {
        auto model = parser->parseModel(
            "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
            "<model xmlns=\"http://www.cellml.org/cellml/2.0#\" xmlns:cellml=\"http://www.cellml.org/cellml/2.0#\" name=\"m\">\n"
            "  <units name=\"tiny_second\">\n"
            "    "
            + testCase.tinySecondUnits + "\n"
                                         "  </units>\n"
                                         "  <units name=\"second_squared\">\n"
                                         "    <unit exponent=\"2\" units=\"second\"/>\n"
                                         "  </units>\n"
                                         "  <component name=\"c\">\n"
                                         "    <variable name=\"x\" units=\""
            + testCase.expectedUnits + "\"/>\n"
                                       "    <math xmlns=\"http://www.w3.org/1998/Math/MathML\">\n"
                                       "      <apply>\n"
                                       "        <eq/>\n"
                                       "        <ci>x</ci>\n"
                                       "        <apply>\n"
                                       "          <power/>\n"
                                       "          "
            + testCase.base + "\n"
                              "          <cn cellml:units=\"dimensionless\" type=\"e-notation\">1<sep/>16</cn>\n"
                              "        </apply>\n"
                              "      </apply>\n"
                              "    </math>\n"
                              "  </component>\n"
                              "</model>\n");

        analyser->analyseModel(model);

        EXPECT_EQ(size_t(0), analyser->issueCount()) << testCase.tinySecondUnits << " | " << testCase.base;
    }
}

TEST(AnalyserUnits, tinyExponentNotEquivalentToDimensionless)
{
    // Units with a tiny exponent (i.e., as tiny as, or tinier than, the machine epsilon) are not dimensionless, so they
    // must not be considered as equivalent to dimensionless, but they must be considered as equivalent to themselves.

    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/2.0#\" xmlns:cellml=\"http://www.cellml.org/cellml/2.0#\" name=\"m\">\n"
        "  <units name=\"tiny_second\">\n"
        "    <unit exponent=\"1e-16\" units=\"second\"/>\n"
        "  </units>\n"
        "  <component name=\"c\">\n"
        "    <variable name=\"x\" units=\"dimensionless\"/>\n"
        "    <variable name=\"y\" units=\"tiny_second\"/>\n"
        "    <math xmlns=\"http://www.w3.org/1998/Math/MathML\">\n"
        "      <apply>\n"
        "        <eq/>\n"
        "        <ci>x</ci>\n"
        "        <cn cellml:units=\"tiny_second\">2</cn>\n"
        "      </apply>\n"
        "      <apply>\n"
        "        <eq/>\n"
        "        <ci>y</ci>\n"
        "        <cn cellml:units=\"tiny_second\">3</cn>\n"
        "      </apply>\n"
        "    </math>\n"
        "  </component>\n"
        "</model>\n");
    auto analyser = libcellml::Analyser::create();

    analyser->analyseModel(model);

    const std::vector<std::string> expectedIssues = {
        "The units in 'x = 2.0' in component 'c' are not equivalent. 'x' is 'dimensionless' while '2.0' is in 'tiny_second' (i.e. 'second^1e-16').",
    };

    EXPECT_EQ_ISSUES(expectedIssues, analyser);
}

TEST(AnalyserUnits, overflowingExponent)
{
    // Units with exponents that overflow when added together (i.e. resulting in an infinite exponent) are not
    // dimensionless, so they must not be considered as cancelling each other.

    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/2.0#\" xmlns:cellml=\"http://www.cellml.org/cellml/2.0#\" name=\"m\">\n"
        "  <units name=\"huge_second\">\n"
        "    <unit exponent=\"1e308\" units=\"second\"/>\n"
        "    <unit exponent=\"1e308\" units=\"second\"/>\n"
        "    <unit exponent=\"1\" units=\"second\"/>\n"
        "  </units>\n"
        "  <component name=\"c\">\n"
        "    <variable name=\"x\" units=\"dimensionless\"/>\n"
        "    <math xmlns=\"http://www.w3.org/1998/Math/MathML\">\n"
        "      <apply>\n"
        "        <eq/>\n"
        "        <ci>x</ci>\n"
        "        <apply>\n"
        "          <exp/>\n"
        "          <cn cellml:units=\"huge_second\">2</cn>\n"
        "        </apply>\n"
        "      </apply>\n"
        "    </math>\n"
        "  </component>\n"
        "</model>\n");
    auto analyser = libcellml::Analyser::create();

    analyser->analyseModel(model);

    const std::vector<std::string> expectedIssues = {
        "The unit of '2.0' in 'exp(2.0)' in equation 'x = exp(2.0)' in component 'c' is not dimensionless. '2.0' is in 'huge_second' (i.e. 'second^inf').",
    };

    EXPECT_EQ_ISSUES(expectedIssues, analyser);
}

TEST(AnalyserUnits, hugeExponentWithOverflowingError)
{
    // Units with a huge, but finite, exponent are not dimensionless, even if computing the error of that exponent
    // overflows (e.g., 1e-200^2 when inverting a root degree of 1e-200 or 0.5^-1024 when differentiating 0.5^-1023), so
    // they must not be considered as negligible. The same holds for units with a finite exponent which error does
    // overflow (e.g., 1e300^(1e300-1e300+1e-300) is 1, but its error is about 1e300*1e285).

    struct TestCase
    {
        std::string rhs;
        std::string expectedIssue;
    };

    static const std::vector<TestCase> testCases = {
        {"<apply><root/><degree><cn cellml:units=\"dimensionless\" type=\"e-notation\">1<sep/>-200</cn></degree><ci>m</ci></apply>",
         "The units in 'x = pow(m, 1.0/1.0e-200)' in component 'c' are not equivalent. 'x' is 'dimensionless' while 'pow(m, 1.0/1.0e-200)' is in 'metre^1e+200'."},
        {"<apply><power/><ci>m</ci><apply><power/><cn cellml:units=\"dimensionless\">0.5</cn><cn cellml:units=\"dimensionless\">-1023</cn></apply></apply>",
         "The units in 'x = pow(m, pow(0.5, -1023.0))' in component 'c' are not equivalent. 'x' is 'dimensionless' while 'pow(m, pow(0.5, -1023.0))' is in 'metre^8.98847e+307'."},
        {"<apply><power/><apply><power/><ci>m</ci><cn cellml:units=\"dimensionless\" type=\"e-notation\">1<sep/>300</cn></apply><apply><plus/><apply><minus/><cn cellml:units=\"dimensionless\" type=\"e-notation\">1<sep/>300</cn><cn cellml:units=\"dimensionless\" type=\"e-notation\">1<sep/>300</cn></apply><cn cellml:units=\"dimensionless\" type=\"e-notation\">1<sep/>-300</cn></apply></apply>",
         "The units in 'x = pow(pow(m, 1.0e300), 1.0e300-1.0e300+1.0e-300)' in component 'c' are not equivalent. 'x' is 'dimensionless' while 'pow(pow(m, 1.0e300), 1.0e300-1.0e300+1.0e-300)' is in 'metre'."},
    };

    auto parser = libcellml::Parser::create();
    auto analyser = libcellml::Analyser::create();

    for (const auto &testCase : testCases) {
        analyser->analyseModel(parser->parseModel(
            "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
            "<model xmlns=\"http://www.cellml.org/cellml/2.0#\" xmlns:cellml=\"http://www.cellml.org/cellml/2.0#\" name=\"m\">\n"
            "  <component name=\"c\">\n"
            "    <variable name=\"m\" units=\"metre\" initial_value=\"1\"/>\n"
            "    <variable name=\"x\" units=\"dimensionless\"/>\n"
            "    <math xmlns=\"http://www.w3.org/1998/Math/MathML\">\n"
            "      <apply>\n"
            "        <eq/>\n"
            "        <ci>x</ci>\n"
            "        "
            + testCase.rhs + "\n"
                             "      </apply>\n"
                             "    </math>\n"
                             "  </component>\n"
                             "</model>\n"));

        EXPECT_EQ_ISSUES(std::vector<std::string>({testCase.expectedIssue}), analyser);
    }
}

TEST(AnalyserUnits, nonFiniteUnitsMultiplier)
{
    // Units raised to a non-finite power (e.g., 1/0, ln(0), 1e400, or 0/0) have a non-finite exponent, but their units
    // multiplier is only non-finite if it is not zero (e.g., km^inf is 10^inf x metre^inf while metre^inf is metre^inf
    // rather than 10^nan x metre^inf). Either way, it must not be converted to an int when describing the units.

    struct TestCase
    {
        std::string rhs;
        std::string expectedIssue;
    };

    static const std::vector<TestCase> testCases = {
        {"<apply><root/><degree><cn cellml:units=\"dimensionless\">0</cn></degree><ci>m</ci></apply>",
         "The units in 'x = pow(m, 1.0/0.0)' in component 'c' are not equivalent. 'x' is 'dimensionless' while 'pow(m, 1.0/0.0)' is in 'metre^inf'."},
        {"<apply><power/><ci>m</ci><apply><ln/><cn cellml:units=\"dimensionless\">0</cn></apply></apply>",
         "The units in 'x = pow(m, ln(0.0))' in component 'c' are not equivalent. 'x' is 'dimensionless' while 'pow(m, ln(0.0))' is in 'metre^-inf'."},
        {"<apply><power/><ci>k</ci><cn cellml:units=\"dimensionless\" type=\"e-notation\">1<sep/>400</cn></apply>",
         "The units in 'x = pow(k, 1.0e400)' in component 'c' are not equivalent. 'x' is 'dimensionless' while 'pow(k, 1.0e400)' is in 'km^inf' (i.e. '10^inf x metre^inf')."},
        {"<apply><power/><ci>k</ci><apply><divide/><cn cellml:units=\"dimensionless\">0</cn><cn cellml:units=\"dimensionless\">0</cn></apply></apply>",
         "The units in 'x = pow(k, 0.0/0.0)' in component 'c' are not equivalent. 'x' is 'dimensionless' while 'pow(k, 0.0/0.0)' is in 'km^nan' (i.e. '10^nan x metre^nan')."},
    };

    auto parser = libcellml::Parser::create();
    auto analyser = libcellml::Analyser::create();

    for (const auto &testCase : testCases) {
        analyser->analyseModel(parser->parseModel(
            "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
            "<model xmlns=\"http://www.cellml.org/cellml/2.0#\" xmlns:cellml=\"http://www.cellml.org/cellml/2.0#\" name=\"m\">\n"
            "  <units name=\"km\">\n"
            "    <unit prefix=\"kilo\" units=\"metre\"/>\n"
            "  </units>\n"
            "  <component name=\"c\">\n"
            "    <variable name=\"m\" units=\"metre\" initial_value=\"1\"/>\n"
            "    <variable name=\"k\" units=\"km\" initial_value=\"1\"/>\n"
            "    <variable name=\"x\" units=\"dimensionless\"/>\n"
            "    <math xmlns=\"http://www.w3.org/1998/Math/MathML\">\n"
            "      <apply>\n"
            "        <eq/>\n"
            "        <ci>x</ci>\n"
            "        "
            + testCase.rhs + "\n"
                             "      </apply>\n"
                             "    </math>\n"
                             "  </component>\n"
                             "</model>\n"));

        EXPECT_EQ_ISSUES(std::vector<std::string>({testCase.expectedIssue}), analyser);
    }
}

TEST(AnalyserUnits, hugeIntegerExponentsNotCancellingEachOther)
{
    // Units with huge integer exponents that nearly cancel each other (i.e. resulting in an exponent that is
    // negligible compared to them) are not dimensionless since integer exponents are represented exactly, so they must
    // not be considered as cancelling each other.

    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/2.0#\" xmlns:cellml=\"http://www.cellml.org/cellml/2.0#\" name=\"m\">\n"
        "  <units name=\"huge_second\">\n"
        "    <unit exponent=\"1000000000000000\" units=\"second\"/>\n"
        "    <unit exponent=\"-999999999999999\" units=\"second\"/>\n"
        "  </units>\n"
        "  <component name=\"c\">\n"
        "    <variable name=\"x\" units=\"dimensionless\"/>\n"
        "    <math xmlns=\"http://www.w3.org/1998/Math/MathML\">\n"
        "      <apply>\n"
        "        <eq/>\n"
        "        <ci>x</ci>\n"
        "        <apply>\n"
        "          <exp/>\n"
        "          <cn cellml:units=\"huge_second\">2</cn>\n"
        "        </apply>\n"
        "      </apply>\n"
        "    </math>\n"
        "  </component>\n"
        "</model>\n");
    auto analyser = libcellml::Analyser::create();

    analyser->analyseModel(model);

    const std::vector<std::string> expectedIssues = {
        "The unit of '2.0' in 'exp(2.0)' in equation 'x = exp(2.0)' in component 'c' is not dimensionless. '2.0' is in 'huge_second' (i.e. 'second').",
    };

    EXPECT_EQ_ISSUES(expectedIssues, analyser);
}

TEST(AnalyserUnits, largestExponentsCancellingEachOther)
{
    // Units with exponents that are close to the largest double and that are within their representation error of
    // each other cancel each other, whether those exponents are scaled by a factor that carries no error (e.g., 1 when
    // converting second to its base units) or by one that may carry an error (e.g., 0.5 when raising to a power), so
    // computing the error of a scaled exponent must neither yield a NaN error (i.e. 0*inf) nor an infinite error.

    static const std::string LARGEST_SECOND = "<cn cellml:units=\"largest_second\">2</cn>";
    static const std::vector<std::string> testCases = {
        "<apply><times/>" + LARGEST_SECOND + "<cn cellml:units=\"minus_largest_second\">2</cn></apply>",
        "<apply><times/><apply><power/>" + LARGEST_SECOND + "<cn cellml:units=\"dimensionless\">0.5</cn></apply><cn cellml:units=\"minus_half_largest_second\">2</cn></apply>",
    };

    auto parser = libcellml::Parser::create();
    auto analyser = libcellml::Analyser::create();

    for (const auto &testCase : testCases) {
        analyser->analyseModel(parser->parseModel(
            "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
            "<model xmlns=\"http://www.cellml.org/cellml/2.0#\" xmlns:cellml=\"http://www.cellml.org/cellml/2.0#\" name=\"m\">\n"
            "  <units name=\"largest_second\">\n"
            "    <unit exponent=\"1.7976931348623157e308\" units=\"second\"/>\n"
            "  </units>\n"
            "  <units name=\"minus_largest_second\">\n"
            "    <unit exponent=\"-1.7976931348623155e308\" units=\"second\"/>\n"
            "  </units>\n"
            "  <units name=\"minus_half_largest_second\">\n"
            "    <unit exponent=\"-8.9884656743115775e307\" units=\"second\"/>\n"
            "  </units>\n"
            "  <component name=\"c\">\n"
            "    <variable name=\"x\" units=\"dimensionless\"/>\n"
            "    <math xmlns=\"http://www.w3.org/1998/Math/MathML\">\n"
            "      <apply>\n"
            "        <eq/>\n"
            "        <ci>x</ci>\n"
            "        <apply>\n"
            "          <exp/>\n"
            "          "
            + testCase + "\n"
                         "        </apply>\n"
                         "      </apply>\n"
                         "    </math>\n"
                         "  </component>\n"
                         "</model>\n"));

        EXPECT_EQ(size_t(0), analyser->issueCount()) << testCase;
    }
}

TEST(AnalyserUnits, zeroExponent)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/2.0#\" xmlns:cellml=\"http://www.cellml.org/cellml/2.0#\" name=\"m\">\n"
        "  <units name=\"second_to_the_zero\">\n"
        "    <unit exponent=\"0\" units=\"second\"/>\n"
        "  </units>\n"
        "  <component name=\"c\">\n"
        "    <variable name=\"x\" units=\"dimensionless\"/>\n"
        "    <math xmlns=\"http://www.w3.org/1998/Math/MathML\">\n"
        "      <apply>\n"
        "        <eq/>\n"
        "        <ci>x</ci>\n"
        "        <apply>\n"
        "          <exp/>\n"
        "          <cn cellml:units=\"second_to_the_zero\">2</cn>\n"
        "        </apply>\n"
        "      </apply>\n"
        "    </math>\n"
        "  </component>\n"
        "</model>\n");
    auto analyser = libcellml::Analyser::create();

    analyser->analyseModel(model);

    EXPECT_EQ(size_t(0), analyser->issueCount());
}

TEST(AnalyserUnits, cancellingDecimalExponents)
{
    // Units with decimal exponents that cancel each other (e.g., 2.3-2.2-0.1) are dimensionless, even though the sum
    // of their exponents is not exactly zero in floating-point arithmetic (and is not negligible compared to the last
    // exponents that are added together).

    static const std::string UNITS =
        "  <units name=\"a\">\n"
        "    <unit exponent=\"2.3\" units=\"metre\"/>\n"
        "  </units>\n"
        "  <units name=\"b\">\n"
        "    <unit exponent=\"-2.2\" units=\"metre\"/>\n"
        "  </units>\n"
        "  <units name=\"c\">\n"
        "    <unit exponent=\"0.1\" units=\"metre\"/>\n"
        "  </units>\n"
        "  <units name=\"abc\">\n"
        "    <unit exponent=\"2.3\" units=\"metre\"/>\n"
        "    <unit exponent=\"-2.2\" units=\"metre\"/>\n"
        "    <unit exponent=\"-0.1\" units=\"metre\"/>\n"
        "  </units>\n";
    static const std::string CN_ABC = "<apply><exp/><cn cellml:units=\"abc\">2</cn></apply>";
    static const std::string A_TIMES_B_DIVIDED_BY_C = "<apply><divide/><apply><times/><ci>A</ci><ci>B</ci></apply><ci>C</ci></apply>";

    auto parser = libcellml::Parser::create();
    auto analyser = libcellml::Analyser::create();

    for (const auto &rhs : {CN_ABC, A_TIMES_B_DIVIDED_BY_C}) {
        analyser->analyseModel(parser->parseModel(
            "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
            "<model xmlns=\"http://www.cellml.org/cellml/2.0#\" xmlns:cellml=\"http://www.cellml.org/cellml/2.0#\" name=\"m\">\n"
            + UNITS
            + "  <component name=\"c\">\n"
              "    <variable name=\"A\" units=\"a\" initial_value=\"1\"/>\n"
              "    <variable name=\"B\" units=\"b\" initial_value=\"1\"/>\n"
              "    <variable name=\"C\" units=\"c\" initial_value=\"1\"/>\n"
              "    <variable name=\"x\" units=\"dimensionless\"/>\n"
              "    <math xmlns=\"http://www.w3.org/1998/Math/MathML\">\n"
              "      <apply>\n"
              "        <eq/>\n"
              "        <ci>x</ci>\n"
              "        "
            + rhs + "\n"
                    "      </apply>\n"
                    "    </math>\n"
                    "  </component>\n"
                    "</model>\n"));

        EXPECT_EQ(size_t(0), analyser->issueCount()) << rhs;
    }
}

TEST(AnalyserUnits, cancellingDecimalExponentsOfScaledUnits)
{
    // Scaled units with decimal exponents (e.g., mV^0.1) that add up to an integer exponent (e.g., mV^2) are equivalent
    // to the corresponding scaled units, even though the sum of their units multipliers (e.g., 20 times 10^-0.3) is not
    // exactly equal to the units multiplier of the corresponding scaled units (e.g., 10^-6) in floating-point arithmetic.
    // However, units that are not scaled in the same way are still not equivalent, even if the difference is tiny.

    static const std::string UNITS =
        "  <units name=\"mV\">\n"
        "    <unit prefix=\"milli\" units=\"volt\"/>\n"
        "  </units>\n"
        "  <units name=\"mV_0_1\">\n"
        "    <unit exponent=\"0.1\" units=\"mV\"/>\n"
        "  </units>\n"
        "  <units name=\"mV2\">\n"
        "    <unit exponent=\"2\" units=\"mV\"/>\n"
        "  </units>\n"
        "  <units name=\"V2\">\n"
        "    <unit exponent=\"2\" units=\"volt\"/>\n"
        "  </units>\n"
        "  <units name=\"almost_mV2\">\n"
        "    <unit multiplier=\"1.0000000001\" exponent=\"2\" units=\"mV\"/>\n"
        "  </units>\n";
    static const std::string A_POWER_20 = "<apply><power/><ci>A</ci><cn cellml:units=\"dimensionless\">20</cn></apply>";

    auto model = [](const std::string &yUnits, const std::string &rhs) {
        return "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
               "<model xmlns=\"http://www.cellml.org/cellml/2.0#\" xmlns:cellml=\"http://www.cellml.org/cellml/2.0#\" name=\"m\">\n"
               + UNITS
               + "  <component name=\"c\">\n"
                 "    <variable name=\"A\" units=\"mV_0_1\" initial_value=\"1\"/>\n"
                 "    <variable name=\"y\" units=\""
               + yUnits + "\"/>\n"
                          "    <math xmlns=\"http://www.w3.org/1998/Math/MathML\">\n"
                          "      <apply>\n"
                          "        <eq/>\n"
                          "        <ci>y</ci>\n"
                          "        "
               + rhs + "\n"
                       "      </apply>\n"
                       "    </math>\n"
                       "  </component>\n"
                       "</model>\n";
    };
    auto repeatedA = [](size_t count) {
        std::string res;

        for (size_t i = 0; i < count; ++i) {
            res += "<ci>A</ci>";
        }

        return res;
    };

    auto parser = libcellml::Parser::create();
    auto analyser = libcellml::Analyser::create();

    for (const auto &rhs : {"<apply><times/>" + repeatedA(20) + "</apply>",
                            "<apply><divide/><apply><times/>" + repeatedA(50) + "</apply><apply><times/>" + repeatedA(30) + "</apply></apply>",
                            A_POWER_20}) {
        analyser->analyseModel(parser->parseModel(model("mV2", rhs)));

        EXPECT_EQ(size_t(0), analyser->issueCount()) << rhs;
    }

    const std::vector<std::string> expectedIssues = {
        "The units in 'y = pow(A, 20.0)' in component 'c' are not equivalent. 'y' is in 'V2' (i.e. 'ampere^-2 x kilogram^2 x metre^4 x second^-6') while 'pow(A, 20.0)' is in 'mV_0_1^20' (i.e. '10^-6 x ampere^-2 x kilogram^2 x metre^4 x second^-6').",
    };

    analyser->analyseModel(parser->parseModel(model("V2", A_POWER_20)));

    EXPECT_EQ_ISSUES(expectedIssues, analyser);

    analyser->analyseModel(parser->parseModel(model("almost_mV2", A_POWER_20)));

    EXPECT_EQ(size_t(1), analyser->issueCount());
}

TEST(AnalyserUnits, tinyUnitsMultiplier)
{
    // A tiny units multiplier (e.g., 10^4.34295e-11 for a multiplier of 1.0000000001) is genuine, so it must neither be
    // ignored nor be rounded to zero when describing the units.

    static const std::vector<std::string> expectedIssues = {
        "The units in 'x = a' in component 'c' are not equivalent. 'x' is in 'metre' while 'a' is in 'almost_metre' (i.e. '10^4.34295e-11 x metre').",
    };

    auto parser = libcellml::Parser::create();
    auto analyser = libcellml::Analyser::create();

    analyser->analyseModel(parser->parseModel(
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/2.0#\" name=\"m\">\n"
        "  <units name=\"almost_metre\">\n"
        "    <unit multiplier=\"1.0000000001\" units=\"metre\"/>\n"
        "  </units>\n"
        "  <component name=\"c\">\n"
        "    <variable name=\"a\" units=\"almost_metre\" initial_value=\"1\"/>\n"
        "    <variable name=\"x\" units=\"metre\"/>\n"
        "    <math xmlns=\"http://www.w3.org/1998/Math/MathML\">\n"
        "      <apply>\n"
        "        <eq/>\n"
        "        <ci>x</ci>\n"
        "        <ci>a</ci>\n"
        "      </apply>\n"
        "    </math>\n"
        "  </component>\n"
        "</model>\n"));

    EXPECT_EQ_ISSUES(expectedIssues, analyser);
}

TEST(AnalyserUnits, infiniteUnitsMultipliers)
{
    // Units multipliers that overflow (e.g., yotta^1e307, i.e. 10^(24*1e307)) are infinite, even though the units
    // exponents are not (e.g., metre^1e307). Two units multipliers that are equally infinite are equal (even though
    // their difference is NaN), but an infinite units multiplier is not equal to a finite one.

    static const std::vector<std::string> expectedIssues = {
        "The units in 'y = c' in component 'c' are not equivalent. 'y' is in 'huge' (i.e. '10^inf x metre^1e+307') while 'c' is in 'large' (i.e. '10^9e+307 x metre^1e+307').",
    };

    auto parser = libcellml::Parser::create();
    auto analyser = libcellml::Analyser::create();

    analyser->analyseModel(parser->parseModel(
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/2.0#\" name=\"m\">\n"
        "  <units name=\"huge\">\n"
        "    <unit prefix=\"yotta\" exponent=\"1e307\" units=\"metre\"/>\n"
        "  </units>\n"
        "  <units name=\"large\">\n"
        "    <unit prefix=\"giga\" exponent=\"1e307\" units=\"metre\"/>\n"
        "  </units>\n"
        "  <component name=\"c\">\n"
        "    <variable name=\"a\" units=\"huge\" initial_value=\"1\"/>\n"
        "    <variable name=\"c\" units=\"large\" initial_value=\"1\"/>\n"
        "    <variable name=\"x\" units=\"huge\"/>\n"
        "    <variable name=\"y\" units=\"huge\"/>\n"
        "    <math xmlns=\"http://www.w3.org/1998/Math/MathML\">\n"
        "      <apply>\n"
        "        <eq/>\n"
        "        <ci>x</ci>\n"
        "        <ci>a</ci>\n"
        "      </apply>\n"
        "      <apply>\n"
        "        <eq/>\n"
        "        <ci>y</ci>\n"
        "        <ci>c</ci>\n"
        "      </apply>\n"
        "    </math>\n"
        "  </component>\n"
        "</model>\n"));

    EXPECT_EQ_ISSUES(expectedIssues, analyser);
}

TEST(AnalyserUnits, reciprocalUnitsMultipliersCloseToOne)
{
    // Units multipliers that are close to 1 and reciprocal within their representation error (e.g., 1.0000001 and
    // 0.9999999000000099) cancel each other, even though their units multipliers (i.e. their log10) are so tiny that
    // the error that log10() may itself carry is negligible compared to that representation error. However, units
    // multipliers that are close to 1 and not reciprocal (e.g., 1.0000001 and 0.9999999) still do not cancel each
    // other.

    static const std::vector<std::string> expectedIssues = {
        "The units in 'y = A*C' in component 'c' are not equivalent. 'y' is 'dimensionless' while 'A*C' is in 'a x c' (i.e. '10^-4.29473e-15').",
    };

    auto parser = libcellml::Parser::create();
    auto analyser = libcellml::Analyser::create();

    analyser->analyseModel(parser->parseModel(
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/2.0#\" name=\"m\">\n"
        "  <units name=\"a\">\n"
        "    <unit multiplier=\"1.0000001\" units=\"metre\"/>\n"
        "  </units>\n"
        "  <units name=\"b\">\n"
        "    <unit multiplier=\"0.9999999000000099\" exponent=\"-1\" units=\"metre\"/>\n"
        "  </units>\n"
        "  <units name=\"c\">\n"
        "    <unit multiplier=\"0.9999999\" exponent=\"-1\" units=\"metre\"/>\n"
        "  </units>\n"
        "  <component name=\"c\">\n"
        "    <variable name=\"A\" units=\"a\" initial_value=\"1\"/>\n"
        "    <variable name=\"B\" units=\"b\" initial_value=\"1\"/>\n"
        "    <variable name=\"C\" units=\"c\" initial_value=\"1\"/>\n"
        "    <variable name=\"x\" units=\"dimensionless\"/>\n"
        "    <variable name=\"y\" units=\"dimensionless\"/>\n"
        "    <math xmlns=\"http://www.w3.org/1998/Math/MathML\">\n"
        "      <apply>\n"
        "        <eq/>\n"
        "        <ci>x</ci>\n"
        "        <apply>\n"
        "          <times/>\n"
        "          <ci>A</ci>\n"
        "          <ci>B</ci>\n"
        "        </apply>\n"
        "      </apply>\n"
        "      <apply>\n"
        "        <eq/>\n"
        "        <ci>y</ci>\n"
        "        <apply>\n"
        "          <times/>\n"
        "          <ci>A</ci>\n"
        "          <ci>C</ci>\n"
        "        </apply>\n"
        "      </apply>\n"
        "    </math>\n"
        "  </component>\n"
        "</model>\n"));

    EXPECT_EQ_ISSUES(expectedIssues, analyser);
}

TEST(AnalyserUnits, reciprocalUnitsMultipliersCloseToOneToInfinitePower)
{
    // Units multipliers that cancel each other (e.g., 1.0000001 and 0.9999999000000099, see
    // reciprocalUnitsMultipliersCloseToOne) yield a negligible, but not necessarily zero, units multiplier, which must
    // remain negligible when raised to an infinite power (e.g., 1/0). However, units multipliers that do not cancel
    // each other (e.g., 1.0000001 and 0.9999999) still yield an infinite units multiplier.

    static const std::vector<std::string> expectedIssues = {
        "The units in 'y = pow(A*C, 1.0/0.0)' in component 'c' are not equivalent. 'y' is 'dimensionless' while 'pow(A*C, 1.0/0.0)' is in 'a^inf x c^inf' (i.e. '10^-inf').",
    };

    auto parser = libcellml::Parser::create();
    auto analyser = libcellml::Analyser::create();

    analyser->analyseModel(parser->parseModel(
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/2.0#\" xmlns:cellml=\"http://www.cellml.org/cellml/2.0#\" name=\"m\">\n"
        "  <units name=\"a\">\n"
        "    <unit multiplier=\"1.0000001\" units=\"metre\"/>\n"
        "  </units>\n"
        "  <units name=\"b\">\n"
        "    <unit multiplier=\"0.9999999000000099\" exponent=\"-1\" units=\"metre\"/>\n"
        "  </units>\n"
        "  <units name=\"c\">\n"
        "    <unit multiplier=\"0.9999999\" exponent=\"-1\" units=\"metre\"/>\n"
        "  </units>\n"
        "  <component name=\"c\">\n"
        "    <variable name=\"A\" units=\"a\" initial_value=\"1\"/>\n"
        "    <variable name=\"B\" units=\"b\" initial_value=\"1\"/>\n"
        "    <variable name=\"C\" units=\"c\" initial_value=\"1\"/>\n"
        "    <variable name=\"x\" units=\"dimensionless\"/>\n"
        "    <variable name=\"y\" units=\"dimensionless\"/>\n"
        "    <math xmlns=\"http://www.w3.org/1998/Math/MathML\">\n"
        "      <apply>\n"
        "        <eq/>\n"
        "        <ci>x</ci>\n"
        "        <apply>\n"
        "          <power/>\n"
        "          <apply>\n"
        "            <times/>\n"
        "            <ci>A</ci>\n"
        "            <ci>B</ci>\n"
        "          </apply>\n"
        "          <apply>\n"
        "            <divide/>\n"
        "            <cn cellml:units=\"dimensionless\">1</cn>\n"
        "            <cn cellml:units=\"dimensionless\">0</cn>\n"
        "          </apply>\n"
        "        </apply>\n"
        "      </apply>\n"
        "      <apply>\n"
        "        <eq/>\n"
        "        <ci>y</ci>\n"
        "        <apply>\n"
        "          <power/>\n"
        "          <apply>\n"
        "            <times/>\n"
        "            <ci>A</ci>\n"
        "            <ci>C</ci>\n"
        "          </apply>\n"
        "          <apply>\n"
        "            <divide/>\n"
        "            <cn cellml:units=\"dimensionless\">1</cn>\n"
        "            <cn cellml:units=\"dimensionless\">0</cn>\n"
        "          </apply>\n"
        "        </apply>\n"
        "      </apply>\n"
        "    </math>\n"
        "  </component>\n"
        "</model>\n"));

    EXPECT_EQ_ISSUES(expectedIssues, analyser);
}

TEST(AnalyserUnits, infiniteUnitsExponents)
{
    // Units exponents that overflow (e.g., 1e308+1e308) are infinite. Two units exponents that are equally infinite are
    // equal (even though their difference is NaN), but an infinite units exponent is not equal to a finite one.

    static const std::vector<std::string> expectedIssues = {
        "The units in 'u = s' in component 'c' are not equivalent. 'u' is in 'second' while 's' is in 'huge_second' (i.e. 'second^inf').",
    };

    auto parser = libcellml::Parser::create();
    auto analyser = libcellml::Analyser::create();

    analyser->analyseModel(parser->parseModel(
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/2.0#\" name=\"m\">\n"
        "  <units name=\"huge_second\">\n"
        "    <unit exponent=\"1e308\" units=\"second\"/>\n"
        "    <unit exponent=\"1e308\" units=\"second\"/>\n"
        "  </units>\n"
        "  <units name=\"other_huge_second\">\n"
        "    <unit exponent=\"1e308\" units=\"second\"/>\n"
        "    <unit exponent=\"1e308\" units=\"second\"/>\n"
        "  </units>\n"
        "  <component name=\"c\">\n"
        "    <variable name=\"s\" units=\"huge_second\" initial_value=\"1\"/>\n"
        "    <variable name=\"t\" units=\"other_huge_second\"/>\n"
        "    <variable name=\"u\" units=\"second\"/>\n"
        "    <math xmlns=\"http://www.w3.org/1998/Math/MathML\">\n"
        "      <apply>\n"
        "        <eq/>\n"
        "        <ci>t</ci>\n"
        "        <ci>s</ci>\n"
        "      </apply>\n"
        "      <apply>\n"
        "        <eq/>\n"
        "        <ci>u</ci>\n"
        "        <ci>s</ci>\n"
        "      </apply>\n"
        "    </math>\n"
        "  </component>\n"
        "</model>\n"));

    EXPECT_EQ_ISSUES(expectedIssues, analyser);
}

TEST(AnalyserUnits, powerOfZero)
{
    // Units raised to the power of zero are dimensionless.

    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/2.0#\" xmlns:cellml=\"http://www.cellml.org/cellml/2.0#\" name=\"m\">\n"
        "  <units name=\"mV\">\n"
        "    <unit prefix=\"milli\" units=\"volt\"/>\n"
        "  </units>\n"
        "  <component name=\"c\">\n"
        "    <variable name=\"V\" units=\"mV\" initial_value=\"1\"/>\n"
        "    <variable name=\"x\" units=\"dimensionless\"/>\n"
        "    <math xmlns=\"http://www.w3.org/1998/Math/MathML\">\n"
        "      <apply>\n"
        "        <eq/>\n"
        "        <ci>x</ci>\n"
        "        <apply>\n"
        "          <exp/>\n"
        "          <apply>\n"
        "            <power/>\n"
        "            <ci>V</ci>\n"
        "            <cn cellml:units=\"dimensionless\">0</cn>\n"
        "          </apply>\n"
        "        </apply>\n"
        "      </apply>\n"
        "    </math>\n"
        "  </component>\n"
        "</model>\n");
    auto analyser = libcellml::Analyser::create();

    analyser->analyseModel(model);

    EXPECT_EQ(size_t(0), analyser->issueCount());
}

TEST(AnalyserUnits, powerOfComputedZero)
{
    // Units raised to the power of a computed zero (e.g., 1/infinity) are dimensionless, even though the error of that
    // zero may not be finite (e.g., 0*infinity).

    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/2.0#\" xmlns:cellml=\"http://www.cellml.org/cellml/2.0#\" name=\"m\">\n"
        "  <component name=\"c\">\n"
        "    <variable name=\"V\" units=\"metre\" initial_value=\"1\"/>\n"
        "    <variable name=\"x\" units=\"dimensionless\"/>\n"
        "    <math xmlns=\"http://www.w3.org/1998/Math/MathML\">\n"
        "      <apply>\n"
        "        <eq/>\n"
        "        <ci>x</ci>\n"
        "        <apply>\n"
        "          <exp/>\n"
        "          <apply>\n"
        "            <power/>\n"
        "            <ci>V</ci>\n"
        "            <apply>\n"
        "              <divide/>\n"
        "              <cn cellml:units=\"dimensionless\">1</cn>\n"
        "              <infinity/>\n"
        "            </apply>\n"
        "          </apply>\n"
        "        </apply>\n"
        "      </apply>\n"
        "    </math>\n"
        "  </component>\n"
        "</model>\n");
    auto analyser = libcellml::Analyser::create();

    analyser->analyseModel(model);

    EXPECT_EQ(size_t(0), analyser->issueCount());
}

TEST(AnalyserUnits, tinyExponentIndependentOfOperandOrder)
{
    // A tiny exponent (i.e. as tiny as, or tinier than, the machine epsilon) is genuine, so it must not be cancelled
    // by units that cancel each other, whatever the order and the grouping of the operands. It must also be preserved
    // exactly, i.e. it must not drift (e.g., to 1.11022e-16) when added to and then subtracted from a larger exponent.

    static const std::string T = "<ci>T</ci>";
    static const std::string SECOND = "<cn cellml:units=\"second\">1</cn>";
    static const std::string PER_SECOND = "<cn cellml:units=\"per_second\">1</cn>";
    static const auto times = [](const std::string &a, const std::string &b, const std::string &c = "") {
        return "<apply><times/>" + a + b + c + "</apply>";
    };
    static const auto divide = [](const std::string &a, const std::string &b) {
        return "<apply><divide/>" + a + b + "</apply>";
    };

    struct TestCase
    {
        std::string xUnits;
        std::string rhs;
    };

    static const std::vector<TestCase> testCases = {
        {"dimensionless", "<apply><exp/>" + times(T, SECOND, PER_SECOND) + "</apply>"},
        {"dimensionless", "<apply><exp/>" + times(SECOND, T, PER_SECOND) + "</apply>"},
        {"dimensionless", "<apply><exp/>" + times(SECOND, PER_SECOND, T) + "</apply>"},
        {"dimensionless", "<apply><exp/>" + times(times(T, SECOND), PER_SECOND) + "</apply>"},
        {"dimensionless", "<apply><exp/>" + times(T, times(SECOND, PER_SECOND)) + "</apply>"},
        {"dimensionless", "<apply><exp/>" + times(times(SECOND, T), PER_SECOND) + "</apply>"},
        {"dimensionless", "<apply><exp/>" + times(SECOND, times(T, PER_SECOND)) + "</apply>"},
        {"dimensionless", "<apply><exp/>" + times(times(SECOND, PER_SECOND), T) + "</apply>"},
        {"dimensionless", "<apply><exp/>" + times(SECOND, times(PER_SECOND, T)) + "</apply>"},
        {"dimensionless", "<apply><exp/>" + divide(times(T, SECOND), SECOND) + "</apply>"},
        {"dimensionless", "<apply><exp/>" + divide(SECOND, divide(SECOND, T)) + "</apply>"},
        {"tiny_second", times(times(T, SECOND), PER_SECOND)},
        {"tiny_second", divide(times(T, SECOND), SECOND)},
        {"tiny_second", times(SECOND, times(PER_SECOND, T))},
    };

    auto parser = libcellml::Parser::create();
    auto analyser = libcellml::Analyser::create();

    for (const auto &testCase : testCases) {
        analyser->analyseModel(parser->parseModel(
            "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
            "<model xmlns=\"http://www.cellml.org/cellml/2.0#\" xmlns:cellml=\"http://www.cellml.org/cellml/2.0#\" name=\"m\">\n"
            "  <units name=\"tiny_second\">\n"
            "    <unit exponent=\"1e-16\" units=\"second\"/>\n"
            "  </units>\n"
            "  <units name=\"per_second\">\n"
            "    <unit exponent=\"-1\" units=\"second\"/>\n"
            "  </units>\n"
            "  <component name=\"c\">\n"
            "    <variable name=\"T\" units=\"tiny_second\" initial_value=\"1\"/>\n"
            "    <variable name=\"x\" units=\""
            + testCase.xUnits + "\"/>\n"
                                "    <math xmlns=\"http://www.w3.org/1998/Math/MathML\">\n"
                                "      <apply>\n"
                                "        <eq/>\n"
                                "        <ci>x</ci>\n"
                                "        "
            + testCase.rhs + "\n"
                             "      </apply>\n"
                             "    </math>\n"
                             "  </component>\n"
                             "</model>\n"));

        if (testCase.xUnits == "dimensionless") {
            ASSERT_EQ(size_t(1), analyser->issueCount()) << testCase.rhs;
            EXPECT_NE(std::string::npos, analyser->issue(0)->description().find("'second^1e-16'")) << analyser->issue(0)->description();
        } else {
            EXPECT_EQ(size_t(0), analyser->issueCount()) << testCase.rhs;
        }
    }
}

TEST(AnalyserUnits, cancellingComputedPowerExponents)
{
    // Power/root exponents that are computed (e.g., 2.3-2.2) inherit the errors of their operands, which are amplified
    // relative to their result, so units raised to such exponents must cancel each other when expected (e.g., 2.3-2.2
    // is 0.09999999999999964 rather than 0.1 in floating-point arithmetic), while a genuine tiny exponent (e.g., 1e-16)
    // must not be discarded.

    static const auto d = [](const std::string &value) {
        return "<cn cellml:units=\"dimensionless\">" + value + "</cn>";
    };
    static const auto apply = [](const std::string &op, const std::string &a, const std::string &b = "") {
        return "<apply><" + op + "/>" + a + b + "</apply>";
    };
    static const auto power = [](const std::string &exponent) {
        return "<apply><power/><ci>V</ci>" + exponent + "</apply>";
    };

    struct TestCase
    {
        std::string xUnits;
        std::string rhs;
    };

    static const std::vector<TestCase> testCases = {
        {"dimensionless", apply("times", power(apply("minus", d("2.3"), d("2.2"))), power(d("-0.1")))},
        {"dimensionless", apply("divide", power(apply("plus", d("2.2"), d("-2.3"))), power(d("-0.1")))},
        {"dimensionless", power(apply("minus", apply("times", d("0.7"), d("3")), d("2.1")))},
        {"dimensionless", apply("divide", power(apply("divide", d("0.21"), d("0.1"))), power(d("2.1")))},
        {"dimensionless", apply("times", power(apply("minus", apply("minus", d("2.3"), d("2.2")))), power(d("0.1")))},
        {"metre_to_the_10", "<apply><root/><degree>" + apply("minus", d("2.3"), d("2.2")) + "</degree><ci>V</ci></apply>"},
        {"dimensionless", apply("divide", power(apply("abs", apply("minus", d("2.2"), d("2.3")))), power(d("0.1")))},
        {"dimensionless", apply("divide", power(apply("min", apply("minus", d("2.3"), d("2.2")), d("5"))), power(d("0.1")))},
        {"dimensionless", apply("divide", power(apply("max", apply("minus", d("2.3"), d("2.2")), d("0"))), power(d("0.1")))},
        {"dimensionless", apply("divide", power(apply("power", apply("minus", d("2.3"), d("2.2")), d("1"))), power(d("0.1")))},
        {"dimensionless", power(apply("power", apply("minus", d("2.3"), d("2.3")), d("2")))},
        {"dimensionless", apply("divide", power(apply("root", apply("minus", d("2.3"), d("2.2")))), power(apply("root", d("0.1"))))},
        {"dimensionless", apply("divide", power("<apply><root/><degree>" + apply("divide", d("1"), apply("minus", d("2.3"), d("2.2"))) + "</degree>" + d("2") + "</apply>"), power("<apply><root/><degree>" + d("10") + "</degree>" + d("2") + "</apply>"))},
    };

    auto parser = libcellml::Parser::create();
    auto analyser = libcellml::Analyser::create();

    for (const auto &testCase : testCases) {
        analyser->analyseModel(parser->parseModel(
            "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
            "<model xmlns=\"http://www.cellml.org/cellml/2.0#\" xmlns:cellml=\"http://www.cellml.org/cellml/2.0#\" name=\"m\">\n"
            "  <units name=\"metre_to_the_10\">\n"
            "    <unit exponent=\"10\" units=\"metre\"/>\n"
            "  </units>\n"
            "  <component name=\"c\">\n"
            "    <variable name=\"V\" units=\"metre\" initial_value=\"1\"/>\n"
            "    <variable name=\"x\" units=\""
            + testCase.xUnits + "\"/>\n"
                                "    <math xmlns=\"http://www.w3.org/1998/Math/MathML\">\n"
                                "      <apply>\n"
                                "        <eq/>\n"
                                "        <ci>x</ci>\n"
                                "        "
            + testCase.rhs + "\n"
                             "      </apply>\n"
                             "    </math>\n"
                             "  </component>\n"
                             "</model>\n"));

        EXPECT_EQ(size_t(0), analyser->issueCount()) << testCase.rhs;
    }

    // A genuine tiny computed exponent is not discarded.

    const std::vector<std::string> expectedIssues = {
        "The units in 'x = pow(V, 1.0-1.0+1.0e-16)' in component 'c' are not equivalent. 'x' is 'dimensionless' while 'pow(V, 1.0-1.0+1.0e-16)' is in 'metre^1e-16'.",
    };

    analyser->analyseModel(parser->parseModel(
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/2.0#\" xmlns:cellml=\"http://www.cellml.org/cellml/2.0#\" name=\"m\">\n"
        "  <component name=\"c\">\n"
        "    <variable name=\"V\" units=\"metre\" initial_value=\"1\"/>\n"
        "    <variable name=\"x\" units=\"dimensionless\"/>\n"
        "    <math xmlns=\"http://www.w3.org/1998/Math/MathML\">\n"
        "      <apply>\n"
        "        <eq/>\n"
        "        <ci>x</ci>\n"
        "        "
        + power(apply("plus", apply("minus", d("1"), d("1")), "<cn cellml:units=\"dimensionless\" type=\"e-notation\">1<sep/>-16</cn>"))
        + "\n"
          "      </apply>\n"
          "    </math>\n"
          "  </component>\n"
          "</model>\n"));

    EXPECT_EQ_ISSUES(expectedIssues, analyser);
}

TEST(AnalyserUnits, cancellingComputedPowerExponentsThroughFunctions)
{
    // Power exponents that are computed using a function (e.g., sin(2.3-2.2) or rem(2.3, 2.2)) inherit the error of
    // their operands, so units raised to such exponents must cancel each other when expected and must be dimensionless
    // when such exponents are mathematically zero (e.g., sin(pi) is 1.2246467991473532e-16 rather than 0 in
    // floating-point arithmetic), while a genuine tiny exponent (e.g., 1e-16) must not be discarded.

    static const auto d = [](const std::string &value) {
        return "<cn cellml:units=\"dimensionless\">" + value + "</cn>";
    };
    static const auto apply = [](const std::string &op, const std::string &a, const std::string &b = "") {
        return "<apply><" + op + "/>" + a + b + "</apply>";
    };
    static const auto power = [](const std::string &exponent) {
        return "<apply><power/><ci>V</ci>" + exponent + "</apply>";
    };
    static const auto cancellingPowers = [](const std::string &op) {
        return apply("divide", power(apply(op, apply("minus", d("2.3"), d("2.2")))), power(apply(op, d("0.1"))));
    };
    static const std::string TINY = "<cn cellml:units=\"dimensionless\" type=\"e-notation\">1<sep/>-16</cn>";

    struct TestCase
    {
        std::string xUnits;
        std::string rhs;
    };

    static const std::vector<TestCase> testCases = {
        {"dimensionless", cancellingPowers("exp")},
        {"dimensionless", cancellingPowers("ln")},
        {"dimensionless", cancellingPowers("log")},
        {"dimensionless", cancellingPowers("sin")},
        {"dimensionless", cancellingPowers("cos")},
        {"dimensionless", cancellingPowers("tan")},
        {"dimensionless", cancellingPowers("sec")},
        {"dimensionless", cancellingPowers("csc")},
        {"dimensionless", cancellingPowers("cot")},
        {"dimensionless", cancellingPowers("sinh")},
        {"dimensionless", cancellingPowers("cosh")},
        {"dimensionless", cancellingPowers("tanh")},
        {"dimensionless", cancellingPowers("sech")},
        {"dimensionless", cancellingPowers("csch")},
        {"dimensionless", cancellingPowers("coth")},
        {"dimensionless", cancellingPowers("arcsin")},
        {"dimensionless", cancellingPowers("arccos")},
        {"dimensionless", cancellingPowers("arctan")},
        {"dimensionless", cancellingPowers("arccot")},
        {"dimensionless", cancellingPowers("arcsinh")},
        {"dimensionless", cancellingPowers("arctanh")},
        {"dimensionless", cancellingPowers("arcsech")},
        {"dimensionless", cancellingPowers("arccsch")},
        {"dimensionless", apply("divide", power(apply("arcsec", apply("plus", apply("minus", d("2.3"), d("2.2")), d("1")))), power(apply("arcsec", d("1.1"))))},
        {"dimensionless", apply("divide", power(apply("arccsc", apply("plus", apply("minus", d("2.3"), d("2.2")), d("1")))), power(apply("arccsc", d("1.1"))))},
        {"dimensionless", apply("divide", power(apply("arccosh", apply("plus", apply("minus", d("2.3"), d("2.2")), d("1")))), power(apply("arccosh", d("1.1"))))},
        {"dimensionless", apply("divide", power(apply("arccoth", apply("plus", apply("minus", d("2.3"), d("2.2")), d("1")))), power(apply("arccoth", d("1.1"))))},
        {"dimensionless", apply("divide", power(apply("abs", apply("minus", d("2.2"), d("2.3")))), power(d("0.1")))},
        {"dimensionless", apply("divide", power(apply("min", apply("minus", d("2.3"), d("2.2")), d("5"))), power(d("0.1")))},
        {"dimensionless", apply("divide", power(apply("max", apply("minus", d("2.3"), d("2.2")), d("-5"))), power(d("0.1")))},
        {"dimensionless", apply("divide", "<apply><root/><degree>" + apply("minus", d("2.3"), d("2.2")) + "</degree><ci>V</ci></apply>", "<apply><root/><degree>" + d("0.1") + "</degree><ci>V</ci></apply>")},
        {"dimensionless", apply("divide", power("<apply><log/><logbase>" + d("2") + "</logbase>" + apply("minus", d("2.3"), d("2.2")) + "</apply>"), power("<apply><log/><logbase>" + d("2") + "</logbase>" + d("0.1") + "</apply>"))},
        {"dimensionless", apply("divide", power(apply("rem", d("2.3"), d("2.2"))), power(d("0.1")))},
        {"dimensionless", apply("divide", power(apply("rem", d("-2.3"), d("2.2"))), power(d("-0.1")))},
        {"dimensionless", apply("divide", power(apply("rem", d("0.1"), apply("plus", apply("minus", d("2.3"), d("2.2")), d("1")))), power(d("0.1")))},
        {"dimensionless", power(apply("sin", "<pi/>"))},
        {"dimensionless", power(apply("cos", apply("divide", "<pi/>", d("2"))))},
        {"dimensionless", power(apply("tan", "<pi/>"))},
        {"metre_cubed", power(apply("floor", apply("times", apply("times", d("0.1"), d("3")), d("10"))))},
    };

    auto parser = libcellml::Parser::create();
    auto analyser = libcellml::Analyser::create();

    for (const auto &testCase : testCases) {
        analyser->analyseModel(parser->parseModel(
            "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
            "<model xmlns=\"http://www.cellml.org/cellml/2.0#\" xmlns:cellml=\"http://www.cellml.org/cellml/2.0#\" name=\"m\">\n"
            "  <units name=\"metre_cubed\">\n"
            "    <unit exponent=\"3\" units=\"metre\"/>\n"
            "  </units>\n"
            "  <component name=\"c\">\n"
            "    <variable name=\"V\" units=\"metre\" initial_value=\"1\"/>\n"
            "    <variable name=\"x\" units=\""
            + testCase.xUnits + "\"/>\n"
                                "    <math xmlns=\"http://www.w3.org/1998/Math/MathML\">\n"
                                "      <apply>\n"
                                "        <eq/>\n"
                                "        <ci>x</ci>\n"
                                "        "
            + testCase.rhs + "\n"
                             "      </apply>\n"
                             "    </math>\n"
                             "  </component>\n"
                             "</model>\n"));

        EXPECT_EQ(size_t(0), analyser->issueCount()) << testCase.rhs;
    }

    // A genuine tiny computed exponent is not discarded.

    for (const auto &exponent : {apply("sin", TINY), apply("rem", TINY, d("1"))}) {
        analyser->analyseModel(parser->parseModel(
            "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
            "<model xmlns=\"http://www.cellml.org/cellml/2.0#\" xmlns:cellml=\"http://www.cellml.org/cellml/2.0#\" name=\"m\">\n"
            "  <component name=\"c\">\n"
            "    <variable name=\"V\" units=\"metre\" initial_value=\"1\"/>\n"
            "    <variable name=\"x\" units=\"dimensionless\"/>\n"
            "    <math xmlns=\"http://www.w3.org/1998/Math/MathML\">\n"
            "      <apply>\n"
            "        <eq/>\n"
            "        <ci>x</ci>\n"
            "        "
            + power(exponent) + "\n"
                                "      </apply>\n"
                                "    </math>\n"
                                "  </component>\n"
                                "</model>\n"));

        ASSERT_EQ(size_t(1), analyser->issueCount()) << exponent;
        EXPECT_NE(std::string::npos, analyser->issue(0)->description().find("'metre^1e-16'")) << analyser->issue(0)->description();
    }
}

TEST(AnalyserUnits, cancellingComputedPowerExponentsWithNonFiniteOperands)
{
    // Power exponents that are computed using a non-finite operand (e.g., 1/0 or 1e308*10) must cancel each other when
    // expected, whatever the order of the operands. This means that a non-finite operand must not yield a NaN error
    // (e.g., 0*infinity or 0*0^-1 for 0^0) and that the huge error of an operand must not be inherited by min()/max()
    // when that operand is certainly not selected (e.g., min(1e308*10, 2.3-2.2)), while a genuine tiny computed
    // exponent (e.g., 1e-16) must not be discarded. Also, min()/max() must account for the errors of both operands when
    // they are equal within their errors (e.g., min(2.3-2.2, 0.1)), and must not depend on the order of its operands
    // when one of them is NaN (e.g., sin(1e308*10)). Finally, a power that is finite even though its base or exponent
    // is NaN (i.e. 1^NaN and NaN^0) must not yield a NaN error.

    static const auto d = [](const std::string &value) {
        return "<cn cellml:units=\"dimensionless\">" + value + "</cn>";
    };
    static const auto apply = [](const std::string &op, const std::string &a, const std::string &b = "") {
        return "<apply><" + op + "/>" + a + b + "</apply>";
    };
    static const auto power = [](const std::string &exponent) {
        return "<apply><power/><ci>V</ci>" + exponent + "</apply>";
    };
    static const std::string COMPUTED_0_1 = apply("minus", d("2.3"), d("2.2"));
    static const std::string POSITIVE_INFINITY = apply("divide", d("1"), d("0"));
    static const std::string NEGATIVE_INFINITY = apply("divide", d("-1"), d("0"));
    static const std::string OVERFLOWING_PRODUCT = apply("times", d("2"), apply("times", "<cn cellml:units=\"dimensionless\" type=\"e-notation\">1<sep/>308</cn>", d("10")));
    static const std::string TINY = "<cn cellml:units=\"dimensionless\" type=\"e-notation\">1<sep/>-16</cn>";
    static const auto cancellingPowers = [](const std::string &exponent) {
        return apply("divide", power(exponent), power(d("0.1")));
    };

    static const std::vector<std::string> rhss = {
        cancellingPowers(apply("min", POSITIVE_INFINITY, COMPUTED_0_1)),
        cancellingPowers(apply("min", COMPUTED_0_1, POSITIVE_INFINITY)),
        cancellingPowers(apply("max", NEGATIVE_INFINITY, COMPUTED_0_1)),
        cancellingPowers(apply("max", COMPUTED_0_1, NEGATIVE_INFINITY)),
        cancellingPowers(apply("min", OVERFLOWING_PRODUCT, COMPUTED_0_1)),
        cancellingPowers(apply("min", COMPUTED_0_1, OVERFLOWING_PRODUCT)),
        cancellingPowers(apply("plus", apply("exp", apply("minus", POSITIVE_INFINITY)), COMPUTED_0_1)),
        cancellingPowers(apply("plus", apply("arctan", OVERFLOWING_PRODUCT), apply("minus", COMPUTED_0_1, apply("arctan", POSITIVE_INFINITY)))),
        cancellingPowers(apply("plus", apply("power", d("0"), d("0.1")), COMPUTED_0_1)),
        cancellingPowers(apply("plus", apply("divide", d("1"), apply("exp", OVERFLOWING_PRODUCT)), COMPUTED_0_1)),
        cancellingPowers(apply("min", apply("sin", OVERFLOWING_PRODUCT), COMPUTED_0_1)),
        cancellingPowers(apply("min", COMPUTED_0_1, d("0.1"))),
        cancellingPowers(apply("max", d("0.1"), COMPUTED_0_1)),
        cancellingPowers(apply("times", apply("power", apply("minus", d("0.1"), d("0.1")), d("0")), COMPUTED_0_1)),
        cancellingPowers(apply("times", apply("power", d("1"), apply("divide", d("0"), d("0"))), COMPUTED_0_1)),
        cancellingPowers(apply("times", apply("power", d("1"), apply("sin", OVERFLOWING_PRODUCT)), COMPUTED_0_1)),
        cancellingPowers(apply("times", apply("power", apply("divide", d("0"), d("0")), d("0")), COMPUTED_0_1)),
        cancellingPowers(apply("times", apply("power", apply("sin", OVERFLOWING_PRODUCT), d("0")), COMPUTED_0_1)),
    };

    auto parser = libcellml::Parser::create();
    auto analyser = libcellml::Analyser::create();
    static const auto model = [](const std::string &rhs) {
        return "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
               "<model xmlns=\"http://www.cellml.org/cellml/2.0#\" xmlns:cellml=\"http://www.cellml.org/cellml/2.0#\" name=\"m\">\n"
               "  <component name=\"c\">\n"
               "    <variable name=\"V\" units=\"metre\" initial_value=\"1\"/>\n"
               "    <variable name=\"x\" units=\"dimensionless\"/>\n"
               "    <math xmlns=\"http://www.w3.org/1998/Math/MathML\">\n"
               "      <apply>\n"
               "        <eq/>\n"
               "        <ci>x</ci>\n"
               "        "
               + rhs + "\n"
                       "      </apply>\n"
                       "    </math>\n"
                       "  </component>\n"
                       "</model>\n";
    };

    for (const auto &rhs : rhss) {
        analyser->analyseModel(parser->parseModel(model(rhs)));

        EXPECT_EQ(size_t(0), analyser->issueCount()) << rhs;
    }

    // A genuine tiny computed exponent is not discarded.

    for (const auto &exponent : {apply("min", OVERFLOWING_PRODUCT, TINY), apply("max", apply("minus", OVERFLOWING_PRODUCT), TINY)}) {
        analyser->analyseModel(parser->parseModel(model(power(exponent))));

        ASSERT_EQ(size_t(1), analyser->issueCount()) << exponent;
        EXPECT_NE(std::string::npos, analyser->issue(0)->description().find("'metre^1e-16'")) << analyser->issue(0)->description();
    }
}

TEST(AnalyserUnits, outOfRangeOrNonNumericalPowerExponent)
{
    // A power exponent that is out of range (e.g., 1e400 or 1e-320) is treated as the closest representable value
    // (i.e. infinity or a subnormal value) while a power exponent that is a variable initialised using another variable
    // has no constant value. Either way, analysing the model must not throw an exception.

    static const std::vector<std::pair<std::string, std::string>> testCases = {
        {"<cn cellml:units=\"dimensionless\" type=\"e-notation\">1<sep/>400</cn>", "'metre^inf'"},
        {"<cn cellml:units=\"dimensionless\" type=\"e-notation\">1<sep/>-320</cn>", "'metre^9.99989e-321'"},
        {"<ci>k1</ci>", "'metre^inf'"},
        {"<ci>k2</ci>", "may result in 'pow(V, k2)' having different units"},
    };

    auto parser = libcellml::Parser::create();
    auto analyser = libcellml::Analyser::create();

    for (const auto &testCase : testCases) {
        auto model = parser->parseModel(
            "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
            "<model xmlns=\"http://www.cellml.org/cellml/2.0#\" xmlns:cellml=\"http://www.cellml.org/cellml/2.0#\" name=\"m\">\n"
            "  <component name=\"c\">\n"
            "    <variable name=\"V\" units=\"metre\" initial_value=\"1\"/>\n"
            "    <variable name=\"k1\" units=\"dimensionless\" initial_value=\"1e400\"/>\n"
            "    <variable name=\"k2\" units=\"dimensionless\" initial_value=\"k3\"/>\n"
            "    <variable name=\"k3\" units=\"dimensionless\" initial_value=\"0.1\"/>\n"
            "    <variable name=\"x\" units=\"second\"/>\n"
            "    <math xmlns=\"http://www.w3.org/1998/Math/MathML\">\n"
            "      <apply>\n"
            "        <eq/>\n"
            "        <ci>x</ci>\n"
            "        <apply>\n"
            "          <power/>\n"
            "          <ci>V</ci>\n"
            "          "
            + testCase.first + "\n"
                               "        </apply>\n"
                               "      </apply>\n"
                               "    </math>\n"
                               "  </component>\n"
                               "</model>\n");

        EXPECT_NO_THROW(analyser->analyseModel(model)) << testCase.first;
        ASSERT_EQ(size_t(1), analyser->issueCount()) << testCase.first;
        EXPECT_NE(std::string::npos, analyser->issue(0)->description().find(testCase.second)) << analyser->issue(0)->description();
    }
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
        "The units in 'a = 1.0' in component 'main' are not equivalent. 'a' is in 'apple' (i.e. '10^-21 x second^3') while '1.0' is in 'orange' (i.e. '10^-9 x second^7').",
        "The units in 'b = 1.0/1.0' in component 'main' are not equivalent. 'b' is in 'apple' (i.e. '10^-21 x second^3') while '1.0/1.0' is in 'orange x second_2^-1' (i.e. '10^-9 x second^5').",
        "The units in 'c = 1.0/(1.0/1.0)' in component 'main' are not equivalent. 'c' is in 'apple' (i.e. '10^-21 x second^3') while '1.0/(1.0/1.0)' is in 'atto_second x orange x second_2^-1' (i.e. '10^-27 x second^6').",
        "The units in 'd = 1.0/(1.0/1.0)/1.0' in component 'main' are not equivalent. 'd' is in 'apple' (i.e. '10^-21 x second^3') while '1.0/(1.0/1.0)/1.0' is in 'atto_second x orange x second_2^-2' (i.e. '10^-27 x second^4').",
        "The units in 'e = 1.0/(1.0/1.0)/pow(1.0, 3.0/2.0)' in component 'main' are not equivalent. 'e' is in 'apple' (i.e. '10^-21 x second^3') while '1.0/(1.0/1.0)/pow(1.0, 3.0/2.0)' is in 'atto_second x orange x second_2^-2.5' (i.e. '10^-27 x second^3').",
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

TEST(AnalyserUnits, powerValues)
{
    auto parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("analyser/units/power_values.cellml"));

    EXPECT_EQ(size_t(0), parser->issueCount());

    const std::vector<std::string> expectedIssues = {
        "The units in 'eqnEq = pow(x, 3.0 == 5.0)' in component 'my_component' are not equivalent. 'eqnEq' is in 'second' while 'pow(x, 3.0 == 5.0)' is 'dimensionless'.",
        "The units in 'eqnGt = pow(x, 3.0 > 5.0)' in component 'my_component' are not equivalent. 'eqnGt' is in 'second' while 'pow(x, 3.0 > 5.0)' is 'dimensionless'.",
        "The units in 'eqnGeq = pow(x, 3.0 >= 5.0)' in component 'my_component' are not equivalent. 'eqnGeq' is in 'second' while 'pow(x, 3.0 >= 5.0)' is 'dimensionless'.",
        "The units in 'eqnAnd2 = pow(x, !3.0 && 5.0)' in component 'my_component' are not equivalent. 'eqnAnd2' is in 'second' while 'pow(x, !3.0 && 5.0)' is 'dimensionless'.",
        "The units in 'eqnAnd3 = pow(x, 3.0 && !5.0)' in component 'my_component' are not equivalent. 'eqnAnd3' is in 'second' while 'pow(x, 3.0 && !5.0)' is 'dimensionless'.",
        "The units in 'eqnOr3 = pow(x, !3.0 || !5.0)' in component 'my_component' are not equivalent. 'eqnOr3' is in 'second' while 'pow(x, !3.0 || !5.0)' is 'dimensionless'.",
        "The units in 'eqnXor = pow(x, xor(3.0, 5.0))' in component 'my_component' are not equivalent. 'eqnXor' is in 'second' while 'pow(x, xor(3.0, 5.0))' is 'dimensionless'.",
        "The units in 'eqnNot = pow(x, !3.0)' in component 'my_component' are not equivalent. 'eqnNot' is in 'second' while 'pow(x, !3.0)' is 'dimensionless'.",
        "The units in 'eqnPlus = pow(x, 3.0)' in component 'my_component' are not equivalent. 'eqnPlus' is in 'second' while 'pow(x, 3.0)' is in 'second^3'.",
        "The units in 'eqnPlus2 = pow(x, 3.0+5.0)' in component 'my_component' are not equivalent. 'eqnPlus2' is in 'second' while 'pow(x, 3.0+5.0)' is in 'second^8'.",
        "The units in 'eqnMinus = pow(x, -3.0)' in component 'my_component' are not equivalent. 'eqnMinus' is in 'second' while 'pow(x, -3.0)' is in 'second^-3'.",
        "The units in 'eqnMinus2 = pow(x, 3.0-5.0)' in component 'my_component' are not equivalent. 'eqnMinus2' is in 'second' while 'pow(x, 3.0-5.0)' is in 'second^-2'.",
        "The units in 'eqnTimes = pow(x, 3.0*5.0)' in component 'my_component' are not equivalent. 'eqnTimes' is in 'second' while 'pow(x, 3.0*5.0)' is in 'second^15'.",
        "The units in 'eqnDivide = pow(x, 3.0/5.0)' in component 'my_component' are not equivalent. 'eqnDivide' is in 'second' while 'pow(x, 3.0/5.0)' is in 'second^0.6'.",
        "The units in 'eqnPower = pow(x, pow(3.0, 5.0))' in component 'my_component' are not equivalent. 'eqnPower' is in 'second' while 'pow(x, pow(3.0, 5.0))' is in 'second^243'.",
        "The units in 'eqnRoot = pow(x, pow(3.0, 1.0/5.0))' in component 'my_component' are not equivalent. 'eqnRoot' is in 'second' while 'pow(x, pow(3.0, 1.0/5.0))' is in 'second^1.24573'.",
        "The units in 'eqnRoot2 = pow(x, sqrt(3.0))' in component 'my_component' are not equivalent. 'eqnRoot2' is in 'second' while 'pow(x, sqrt(3.0))' is in 'second^1.73205'.",
        "The units in 'eqnAbs = pow(x, abs(-3.0))' in component 'my_component' are not equivalent. 'eqnAbs' is in 'second' while 'pow(x, abs(-3.0))' is in 'second^3'.",
        "The units in 'eqnExp = pow(x, exp(3.0))' in component 'my_component' are not equivalent. 'eqnExp' is in 'second' while 'pow(x, exp(3.0))' is in 'second^20.0855'.",
        "The units in 'eqnLn = pow(x, ln(3.0))' in component 'my_component' are not equivalent. 'eqnLn' is in 'second' while 'pow(x, ln(3.0))' is in 'second^1.09861'.",
        "The units in 'eqnLog = pow(x, log(3.0))' in component 'my_component' are not equivalent. 'eqnLog' is in 'second' while 'pow(x, log(3.0))' is in 'second^0.477121'.",
        "The units in 'eqnLog2 = pow(x, ln(3.0)/ln(2.0))' in component 'my_component' are not equivalent. 'eqnLog2' is in 'second' while 'pow(x, ln(3.0)/ln(2.0))' is in 'second^1.58496'.",
        "The units in 'eqnLog10 = pow(x, log(3.0))' in component 'my_component' are not equivalent. 'eqnLog10' is in 'second' while 'pow(x, log(3.0))' is in 'second^0.477121'.",
        "The units in 'eqnCeiling = pow(x, ceil(3.21))' in component 'my_component' are not equivalent. 'eqnCeiling' is in 'second' while 'pow(x, ceil(3.21))' is in 'second^4'.",
        "The units in 'eqnFloor = pow(x, floor(3.21))' in component 'my_component' are not equivalent. 'eqnFloor' is in 'second' while 'pow(x, floor(3.21))' is in 'second^3'.",
        "The units in 'eqnMin = pow(x, min(3.0, 5.0))' in component 'my_component' are not equivalent. 'eqnMin' is in 'second' while 'pow(x, min(3.0, 5.0))' is in 'second^3'.",
        "The units in 'eqnMin2 = pow(x, min(5.0, 3.0))' in component 'my_component' are not equivalent. 'eqnMin2' is in 'second' while 'pow(x, min(5.0, 3.0))' is in 'second^3'.",
        "The units in 'eqnMax = pow(x, max(3.0, 5.0))' in component 'my_component' are not equivalent. 'eqnMax' is in 'second' while 'pow(x, max(3.0, 5.0))' is in 'second^5'.",
        "The units in 'eqnMax2 = pow(x, max(5.0, 3.0))' in component 'my_component' are not equivalent. 'eqnMax2' is in 'second' while 'pow(x, max(5.0, 3.0))' is in 'second^5'.",
        "The units in 'eqnRem = pow(x, rem(3.0, 5.0))' in component 'my_component' are not equivalent. 'eqnRem' is in 'second' while 'pow(x, rem(3.0, 5.0))' is in 'second^3'.",
        "The units in 'eqnDiff = pow(x, dx/dt)' in component 'my_component' may not be equivalent. 'eqnDiff' is in 'second' while 'dx/dt' may result in 'pow(x, dx/dt)' having different units.",
        "The units in 'pow(x, dx/dt) = eqnDiff2' in component 'my_component' may not be equivalent. 'dx/dt' may result in 'pow(x, dx/dt)' having different units while 'eqnDiff2' is in 'second'.",
        "The units in 'pow(x, dx/dt) = pow(xx, dxx/dt)' in component 'my_component' may not be equivalent. 'dx/dt' may result in 'pow(x, dx/dt)' having different units while 'dxx/dt' may result in 'pow(xx, dxx/dt)' having different units.",
        "The units in 'eqnSin = pow(x, sin(3.0))' in component 'my_component' are not equivalent. 'eqnSin' is in 'second' while 'pow(x, sin(3.0))' is in 'second^0.14112'.",
        "The units in 'eqnCos = pow(x, cos(3.0))' in component 'my_component' are not equivalent. 'eqnCos' is in 'second' while 'pow(x, cos(3.0))' is in 'second^-0.989992'.",
        "The units in 'eqnTan = pow(x, tan(3.0))' in component 'my_component' are not equivalent. 'eqnTan' is in 'second' while 'pow(x, tan(3.0))' is in 'second^-0.142547'.",
        "The units in 'eqnSec = pow(x, sec(3.0))' in component 'my_component' are not equivalent. 'eqnSec' is in 'second' while 'pow(x, sec(3.0))' is in 'second^-1.01011'.",
        "The units in 'eqnCsc = pow(x, csc(3.0))' in component 'my_component' are not equivalent. 'eqnCsc' is in 'second' while 'pow(x, csc(3.0))' is in 'second^7.08617'.",
        "The units in 'eqnCot = pow(x, cot(3.0))' in component 'my_component' are not equivalent. 'eqnCot' is in 'second' while 'pow(x, cot(3.0))' is in 'second^-7.01525'.",
        "The units in 'eqnSinh = pow(x, sinh(3.0))' in component 'my_component' are not equivalent. 'eqnSinh' is in 'second' while 'pow(x, sinh(3.0))' is in 'second^10.0179'.",
        "The units in 'eqnCosh = pow(x, cosh(3.0))' in component 'my_component' are not equivalent. 'eqnCosh' is in 'second' while 'pow(x, cosh(3.0))' is in 'second^10.0677'.",
        "The units in 'eqnTanh = pow(x, tanh(3.0))' in component 'my_component' are not equivalent. 'eqnTanh' is in 'second' while 'pow(x, tanh(3.0))' is in 'second^0.995055'.",
        "The units in 'eqnSech = pow(x, sech(3.0))' in component 'my_component' are not equivalent. 'eqnSech' is in 'second' while 'pow(x, sech(3.0))' is in 'second^0.0993279'.",
        "The units in 'eqnCsch = pow(x, csch(3.0))' in component 'my_component' are not equivalent. 'eqnCsch' is in 'second' while 'pow(x, csch(3.0))' is in 'second^0.0998216'.",
        "The units in 'eqnCoth = pow(x, coth(3.0))' in component 'my_component' are not equivalent. 'eqnCoth' is in 'second' while 'pow(x, coth(3.0))' is in 'second^1.00497'.",
        "The units in 'eqnArcsin = pow(x, arcsin(0.3))' in component 'my_component' are not equivalent. 'eqnArcsin' is in 'second' while 'pow(x, arcsin(0.3))' is in 'second^0.304693'.",
        "The units in 'eqnArccos = pow(x, arccos(0.3))' in component 'my_component' are not equivalent. 'eqnArccos' is in 'second' while 'pow(x, arccos(0.3))' is in 'second^1.2661'.",
        "The units in 'eqnArctan = pow(x, arctan(3.0))' in component 'my_component' are not equivalent. 'eqnArctan' is in 'second' while 'pow(x, arctan(3.0))' is in 'second^1.24905'.",
        "The units in 'eqnArcsec = pow(x, arcsec(3.0))' in component 'my_component' are not equivalent. 'eqnArcsec' is in 'second' while 'pow(x, arcsec(3.0))' is in 'second^1.23096'.",
        "The units in 'eqnArccsc = pow(x, arccsc(3.0))' in component 'my_component' are not equivalent. 'eqnArccsc' is in 'second' while 'pow(x, arccsc(3.0))' is in 'second^0.339837'.",
        "The units in 'eqnArccot = pow(x, arccot(3.0))' in component 'my_component' are not equivalent. 'eqnArccot' is in 'second' while 'pow(x, arccot(3.0))' is in 'second^0.321751'.",
        "The units in 'eqnArcsinh = pow(x, arcsinh(3.0))' in component 'my_component' are not equivalent. 'eqnArcsinh' is in 'second' while 'pow(x, arcsinh(3.0))' is in 'second^1.81845'.",
        "The units in 'eqnArccosh = pow(x, arccosh(3.0))' in component 'my_component' are not equivalent. 'eqnArccosh' is in 'second' while 'pow(x, arccosh(3.0))' is in 'second^1.76275'.",
        "The units in 'eqnArctanh = pow(x, arctanh(0.3))' in component 'my_component' are not equivalent. 'eqnArctanh' is in 'second' while 'pow(x, arctanh(0.3))' is in 'second^0.30952'.",
        "The units in 'eqnArcsech = pow(x, arcsech(0.3))' in component 'my_component' are not equivalent. 'eqnArcsech' is in 'second' while 'pow(x, arcsech(0.3))' is in 'second^1.87382'.",
        "The units in 'eqnArccsch = pow(x, arccsch(3.0))' in component 'my_component' are not equivalent. 'eqnArccsch' is in 'second' while 'pow(x, arccsch(3.0))' is in 'second^0.32745'.",
        "The units in 'eqnArccoth = pow(x, arccoth(3.0))' in component 'my_component' are not equivalent. 'eqnArccoth' is in 'second' while 'pow(x, arccoth(3.0))' is in 'second^0.346574'.",
        "The units in 'eqnPiecewise = pow(x, (y > 5.0)?3.0:7.0)' in component 'my_component' may not be equivalent. 'eqnPiecewise' is in 'second' while '(y > 5.0)?3.0:7.0' may result in 'pow(x, (y > 5.0)?3.0:7.0)' having different units.",
        "The units in 'eqnCi = pow(x, y)' in component 'my_component' are not equivalent. 'eqnCi' is in 'second' while 'pow(x, y)' is in 'second^3'.",
        "The units in 'eqnCi2 = pow(x, z)' in component 'my_component' are equivalent as long as the value of 'z' is equal to '1.0'.",
        "The units in 'eqnCi3 = pow(x, 3.0*z)' in component 'my_component' are equivalent as long as the value of '3.0*z' is equal to '3.0'.",
        "The units in 'eqnCi4 = pow(x, y+z)' in component 'my_component' are equivalent as long as the value of 'y+z' is equal to '4.0'.",
        "The units in 'eqnCi5 = pow(x, pow(y-z, y-z)+1.0)' in component 'my_component' are equivalent as long as the value of 'pow(y-z, y-z)+1.0' is equal to '5.0'.",
        "The units in 'eqnCn = pow(x, 3.0)' in component 'my_component' are not equivalent. 'eqnCn' is in 'second' while 'pow(x, 3.0)' is in 'second^3'.",
        "The units in 'eqnFalse = pow(x, false)' in component 'my_component' are not equivalent. 'eqnFalse' is in 'second' while 'pow(x, false)' is 'dimensionless'.",
        "The units in 'eqnExponentiale = pow(x, exponentiale)' in component 'my_component' are not equivalent. 'eqnExponentiale' is in 'second' while 'pow(x, exponentiale)' is in 'second^2.71828'.",
        "The units in 'eqnPi = pow(x, pi)' in component 'my_component' are not equivalent. 'eqnPi' is in 'second' while 'pow(x, pi)' is in 'second^3.14159'.",
        "The units in 'eqnInfinity = pow(x, infinity)' in component 'my_component' are not equivalent. 'eqnInfinity' is in 'second' while 'pow(x, infinity)' is in 'second^inf'.",
        "The units in 'eqnNotanumber = pow(x, notanumber)' in component 'my_component' are not equivalent. 'eqnNotanumber' is in 'second' while 'pow(x, notanumber)' is in 'second^nan'.",
        "The type of variable 'u' in component 'my_component' is unknown.",
        "The type of variable 'eqnCoverage' in component 'my_component' is unknown.",
        "The type of variable 'eqnCoverage2' in component 'my_component' is unknown.",
        "The type of variable 'eqnCoverage3' in component 'my_component' is unknown.",
    };

    auto analyser = libcellml::Analyser::create();

    analyser->analyseModel(model);

    EXPECT_EQ_ISSUES(expectedIssues, analyser);
}

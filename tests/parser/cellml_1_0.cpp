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

TEST(ParserTransform, emptyCellml10)
{
    const std::string e =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/1.0#\"/>\n";

    libcellml::ParserPtr parser = libcellml::Parser::create();
    libcellml::ModelPtr model = parser->parseModel(e, true);
    EXPECT_EQ(size_t(1), parser->issueCount());
    EXPECT_EQ(libcellml::Issue::Level::MESSAGE, parser->issue(0)->level());
    EXPECT_EQ("Given model is a CellML 1.0 model, the parser will try to represent this model in CellML 2.0.",
              parser->issue(0)->description());
}

TEST(ParserTransform, parseNamedModelCellml10WithoutAuthority)
{
    const std::string n = "name";
    const std::string e =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/1.0#\" name=\"name\"/>\n";

    libcellml::ParserPtr parser = libcellml::Parser::create();
    libcellml::ModelPtr model = parser->parseModel(e);

    EXPECT_EQ("", model->name());
    EXPECT_EQ(size_t(1), parser->issueCount());
    EXPECT_EQ(libcellml::Issue::Level::ERROR, parser->issue(0)->level());
    EXPECT_EQ("Given model is a CellML 1.0 model, explicitly set parseVersion1XModels parameter true,"
              " if you want the parser to try and represent this model in CellML 2.0.",
              parser->issue(0)->description());
}

TEST(ParserTransform, parseNamedModelCellml10)
{
    const std::string n = "name";
    const std::string e =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<model xmlns=\"http://www.cellml.org/cellml/1.0#\" name=\"name\"/>\n";

    libcellml::ParserPtr parser = libcellml::Parser::create();
    libcellml::ModelPtr model = parser->parseModel(e, true);
    EXPECT_EQ(n, model->name());
}

TEST(ParserTransform, hodgkinHuxleyCellml10)
{
    libcellml::ParserPtr parser = libcellml::Parser::create();
    auto model = parser->parseModel(fileContents("cellml1X/Hodgkin_Huxley_1952_modified.cellml"), true);

    EXPECT_EQ(size_t(7), model->unitsCount());
    EXPECT_EQ(size_t(5), model->componentCount());
    EXPECT_EQ(size_t(4), parser->issueCount());

    auto validator = libcellml::Validator::create();
    validator->validateModel(model);

    EXPECT_EQ(size_t(0), validator->issueCount());
}

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

#include "gtest/gtest.h"

#include <libcellml>

#include "test_utils.h"

TEST(AnyItem, createDefault)
{
    auto anyItem = libcellml::AnyItemNew::create();
    EXPECT_EQ(libcellml::CellmlElementType::UNDEFINED, anyItem->type());
}

TEST(AnyItem, createWithArguments)
{
    auto model = libcellml::Model::create();
    auto item = libcellml::AnyItemNew::create(std::any(model), libcellml::CellmlElementType::MODEL);
    EXPECT_EQ(libcellml::CellmlElementType::MODEL, item->type());
    EXPECT_EQ(model, std::any_cast<libcellml::ModelPtr>(item->item()));
}

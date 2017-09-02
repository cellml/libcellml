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

TEST(When, create) {
    libcellml::WhenPtr w = std::make_shared<libcellml::When>();

    EXPECT_NE(nullptr, w);
}

TEST(When, order) {
    libcellml::WhenPtr w = std::make_shared<libcellml::When>();

    w->setOrder(1);

    EXPECT_EQ(1, w->getOrder());
}

TEST(When, condition) {
    libcellml::WhenPtr w = std::make_shared<libcellml::When>();

    w->setCondition("<some mathml type string for condition.>");

    EXPECT_EQ("<some mathml type string for condition.>", w->getCondition());
}

TEST(When, value) {
    libcellml::WhenPtr w = std::make_shared<libcellml::When>();

    w->setCondition("<some mathml type string for value.>");

    EXPECT_EQ("<some mathml type string for value.>", w->getCondition());
}

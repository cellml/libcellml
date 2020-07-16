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

TEST(Logger, addError)
{
    auto issue = libcellml::Issue::create();
    issue->setLevel(libcellml::Issue::Level::ERROR);
    auto logger = libcellml::Validator::create();

    logger->addIssue(issue);
    EXPECT_EQ(size_t(1), logger->issueCount());
    EXPECT_EQ(size_t(1), logger->errorCount());
    EXPECT_EQ(size_t(0), logger->warningCount());
    EXPECT_EQ(size_t(0), logger->hintCount());
    EXPECT_EQ(logger->error(0), issue);
    EXPECT_EQ(logger->issue(0), issue);
}

TEST(Logger, addWarning)
{
    auto issue = libcellml::Issue::create();
    issue->setLevel(libcellml::Issue::Level::WARNING);
    auto logger = libcellml::Validator::create();

    logger->addIssue(issue);
    EXPECT_EQ(size_t(1), logger->issueCount());
    EXPECT_EQ(size_t(0), logger->errorCount());
    EXPECT_EQ(size_t(1), logger->warningCount());
    EXPECT_EQ(size_t(0), logger->hintCount());
    EXPECT_EQ(logger->warning(0), issue);
    EXPECT_EQ(logger->issue(0), issue);
}

TEST(Logger, addHint)
{
    auto issue = libcellml::Issue::create();
    issue->setLevel(libcellml::Issue::Level::HINT);
    auto logger = libcellml::Validator::create();

    logger->addIssue(issue);
    EXPECT_EQ(size_t(1), logger->issueCount());
    EXPECT_EQ(size_t(0), logger->errorCount());
    EXPECT_EQ(size_t(0), logger->warningCount());
    EXPECT_EQ(size_t(1), logger->hintCount());
    EXPECT_EQ(logger->hint(0), issue);
    EXPECT_EQ(logger->issue(0), issue);
}

TEST(Logger, addInformation)
{
    auto issue = libcellml::Issue::create();
    issue->setLevel(libcellml::Issue::Level::INFORMATION);
    auto logger = libcellml::Validator::create();

    logger->addIssue(issue);
    EXPECT_EQ(size_t(1), logger->issueCount());
    EXPECT_EQ(size_t(0), logger->errorCount());
    EXPECT_EQ(size_t(0), logger->warningCount());
    EXPECT_EQ(size_t(1), logger->informationCount());
    EXPECT_EQ(logger->information(0), issue);
    EXPECT_EQ(logger->issue(0), issue);
}

TEST(Logger, getIssueByLevelFunction)
{
    auto error1 = libcellml::Issue::create();
    error1->setLevel(libcellml::Issue::Level::ERROR);

    auto warning1 = libcellml::Issue::create();
    warning1->setLevel(libcellml::Issue::Level::WARNING);

    auto hint1 = libcellml::Issue::create();
    hint1->setLevel(libcellml::Issue::Level::HINT);

    auto information1 = libcellml::Issue::create();
    information1->setLevel(libcellml::Issue::Level::INFORMATION);

    auto error2 = libcellml::Issue::create();
    error2->setLevel(libcellml::Issue::Level::ERROR);

    auto warning2 = libcellml::Issue::create();
    warning2->setLevel(libcellml::Issue::Level::WARNING);

    auto hint2 = libcellml::Issue::create();
    hint2->setLevel(libcellml::Issue::Level::HINT);

    auto information2 = libcellml::Issue::create();
    information2->setLevel(libcellml::Issue::Level::INFORMATION);

    auto validator = libcellml::Validator::create();
    validator->addIssue(error1);
    validator->addIssue(warning1);
    validator->addIssue(hint1);
    validator->addIssue(information1);
    validator->addIssue(information2);
    validator->addIssue(hint2);
    validator->addIssue(warning2);
    validator->addIssue(error2);

    // Expect to be able to call issue(0-7) and have the appropriate one returned
    // in the order they were added, irrespective of their level.
    EXPECT_EQ(size_t(8), validator->issueCount());
    EXPECT_EQ(error1, validator->issue(0));
    EXPECT_EQ(warning1, validator->issue(1));
    EXPECT_EQ(hint1, validator->issue(2));
    EXPECT_EQ(information1, validator->issue(3));
    EXPECT_EQ(information2, validator->issue(4));
    EXPECT_EQ(hint2, validator->issue(5));
    EXPECT_EQ(warning2, validator->issue(6));
    EXPECT_EQ(error2, validator->issue(7));

    // Expect to call error(0-1) and get the ERROR level issues only
    EXPECT_EQ(error1, validator->error(0));
    EXPECT_EQ(error2, validator->error(1));

    // Expect to call warning(0-1) and get the WARNING level issues only
    EXPECT_EQ(warning1, validator->warning(0));
    EXPECT_EQ(warning2, validator->warning(1));

    // Expect to call hint(0-1) and get the HINT level issues only
    EXPECT_EQ(hint1, validator->hint(0));
    EXPECT_EQ(hint2, validator->hint(1));

    // Expect to call hint(0-1) and get the INFORMATION level issues only
    EXPECT_EQ(information1, validator->information(0));
    EXPECT_EQ(information2, validator->information(1));
}

TEST(Logger, outOfRangeIndex)
{
    auto error1 = libcellml::Issue::create();
    auto warning1 = libcellml::Issue::create();
    auto hint1 = libcellml::Issue::create();
    auto information1 = libcellml::Issue::create();

    error1->setLevel(libcellml::Issue::Level::ERROR);
    warning1->setLevel(libcellml::Issue::Level::WARNING);
    hint1->setLevel(libcellml::Issue::Level::HINT);
    information1->setLevel(libcellml::Issue::Level::INFORMATION);

    auto validator = libcellml::Validator::create();
    validator->addIssue(error1);
    validator->addIssue(warning1);
    validator->addIssue(hint1);
    validator->addIssue(information1);

    EXPECT_EQ(nullptr, validator->issue(10));
    EXPECT_EQ(nullptr, validator->error(10));
    EXPECT_EQ(nullptr, validator->warning(10));
    EXPECT_EQ(nullptr, validator->hint(10));
    EXPECT_EQ(nullptr, validator->information(10));
}

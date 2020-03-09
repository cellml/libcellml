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

#pragma once

#include <iostream>
#include <libcellml>
#include <sstream>

#include "test_exportdefinitions.h"

const std::string EMPTY_MATH = "<math xmlns=\"http://www.w3.org/1998/Math/MathML\"/>\n";

const std::string NON_EMPTY_MATH =
    "<math xmlns:cellml=\"http://www.cellml.org/cellml/2.0#\" xmlns=\"http://www.w3.org/1998/Math/MathML\">\n"
    "  <apply>\n"
    "    <eq/>\n"
    "    <ci>var</ci>\n"
    "    <apply>\n"
    "      <plus/>\n"
    "      <cn cellml:units=\"dimensionless\">3.44<sep/>2</cn>\n"
    "      <cn cellml:units=\"dimensionless\">-9.612</cn>\n"
    "    </apply>\n"
    "  </apply>\n"
    "</math>\n";

struct Debug
{
    explicit Debug(bool newLine = true)
        : mNewLine(newLine)
    {
    }

    ~Debug()
    {
        std::cout << mSS.str();
        if (mNewLine) {
            std::cout << std::endl;
        }
    }

    Debug &operator<<(const void *p)
    {
        std::ostringstream ss;
        ss << static_cast<const void *>(p);
        mSS << ss.str();
        return *this;
    }

    // Accept just about anything.
    template<class T>
    Debug &operator<<(const T &x)
    {
        mSS << x;
        return *this;
    }

private:
    std::ostringstream mSS;
    bool mNewLine;
};

std::string TEST_EXPORT resourcePath(const std::string &resourceRelativePath = "");

std::string TEST_EXPORT fileContents(const std::string &fileName);

void TEST_EXPORT printErrors(const libcellml::LoggerPtr &l, bool headings = false, bool kinds = false, bool rule = false);

void TEST_EXPORT printComponent(const libcellml::ComponentPtr &component, size_t const c, std::string const spacer);

void TEST_EXPORT printModel(const libcellml::ModelPtr &model);

void TEST_EXPORT expectEqualErrors(const std::vector<std::string> &errors,
                                   const libcellml::LoggerPtr &logger);
void TEST_EXPORT expectEqualErrorsSpecificationHeadings(const std::vector<std::string> &errors,
                                                        const std::vector<std::string> &specificationHeadings,
                                                        const libcellml::LoggerPtr &logger);
void TEST_EXPORT expectEqualErrorsKinds(const std::vector<std::string> &errors,
                                        const std::vector<libcellml::Error::Kind> &kinds,
                                        const libcellml::LoggerPtr &logger);

libcellml::ModelPtr TEST_EXPORT createModel(const std::string &name = "");
libcellml::ModelPtr TEST_EXPORT createModelWithComponent(const std::string &name = "");
libcellml::VariablePtr TEST_EXPORT createVariableWithUnits(const std::string &name, const std::string &units);
libcellml::ModelPtr TEST_EXPORT createModelTwoComponentsWithOneVariableEach(const std::string &modelName = "", const std::string &c1Name = "", const std::string &c2Name = "", const std::string &v1Name = "", const std::string &v2Name = "");

#define EXPECT_EQ_ERRORS(errors, logger) \
    SCOPED_TRACE("Error occured here."); \
    expectEqualErrors(errors, logger)

#define EXPECT_EQ_ERRORS_SPECIFICATION_HEADINGS(errors, specificationHeadings, logger) \
    SCOPED_TRACE("Error occured here."); \
    expectEqualErrorsSpecificationHeadings(errors, specificationHeadings, logger)

#define EXPECT_EQ_ERRORS_KINDS(errors, kinds, logger) \
    SCOPED_TRACE("Error occured here."); \
    expectEqualErrorsKinds(errors, kinds, logger)

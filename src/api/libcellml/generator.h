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

#include "libcellml/logger.h"
#include "libcellml/types.h"

#include <string>

namespace libcellml {

class LIBCELLML_EXPORT Generator: public Logger
{
public:
    Generator(); /**< Constructor */
    ~Generator() override; /**< Destructor */
    Generator(const Generator &rhs); /**< Copy constructor */
    Generator(Generator &&rhs); /**< Move constructor */
    Generator& operator=(Generator rhs); /**< Assignment operator */

    void analyzeModel(const ModelPtr &model);

    void setWithNames(bool withNames);

    size_t stateCount() const;
    size_t rateCount() const;
    size_t variableCount() const;

    std::string initializeVariables() const;
    std::string computeConstantEquations() const;
    std::string computeRateEquations() const;
    std::string computeAlgebraicEquations() const;

private:
    void swap(Generator &rhs); /**< Swap method required for C++ 11 move semantics. */

    struct GeneratorImpl;
    GeneratorImpl *mPimpl;
};

}

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

#include "libcellml/generator.h"
#include "libcellml/model.h"

#include <vector>

#include <iostream>
namespace libcellml{

struct GeneratorVariable
{
};

typedef std::shared_ptr<GeneratorVariable> GeneratorVariablePtr;

struct Generator::GeneratorImpl
{
    std::vector<GeneratorVariablePtr> mStates;
    std::vector<GeneratorVariablePtr> mVariables;
};

Generator::Generator()
    : mPimpl(new GeneratorImpl())
{
}

Generator::~Generator()
{
    delete mPimpl;
}

Generator::Generator(const Generator &rhs)
    : Logger(rhs)
    , mPimpl(new GeneratorImpl())
{
    mPimpl->mStates = rhs.mPimpl->mStates;
    mPimpl->mVariables = rhs.mPimpl->mVariables;
}

Generator::Generator(Generator &&rhs)
    : Logger(std::move(rhs))
    , mPimpl(rhs.mPimpl)
{
    rhs.mPimpl = nullptr;
}

Generator& Generator::operator=(Generator rhs)
{
    Logger::operator =(rhs);
    rhs.swap(*this);
    return *this;
}

void Generator::swap(Generator &rhs)
{
    std::swap(this->mPimpl, rhs.mPimpl);
}

void Generator::analyzeModel(const ModelPtr &model)
{
    (void) model;
}

size_t Generator::stateCount() const
{
    return mPimpl->mStates.size();
}

size_t Generator::rateCount() const
{
    return stateCount();
}

size_t Generator::variableCount() const
{
    return mPimpl->mVariables.size();
}

std::string Generator::initializeVariables() const
{
    return "";
}

std::string Generator::computeConstantEquations() const
{
    return "";
}

std::string Generator::computeRateEquations() const
{
    return "";
}

std::string Generator::computeAlgebraicEquations() const
{
    return "";
}

}

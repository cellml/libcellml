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

#include "libcellml/analyserequation.h"

#include <algorithm>

#include "analyserequation_p.h"

namespace libcellml {

void AnalyserEquation::AnalyserEquationImpl::populate(AnalyserEquation::Type type,
                                                      const AnalyserEquationAstPtr &ast,
                                                      const std::vector<AnalyserEquationPtr> &dependencies,
                                                      const AnalyserVariablePtr &variable)
{
    mType = type;
    mAst = ast;

    for (const auto &dependency : dependencies) {
        mDependencies.push_back(dependency);
    }

    mVariable = variable;
}

bool AnalyserEquation::AnalyserEquationImpl::isEmptyDependency(const AnalyserEquationWeakPtr &dependency)
{
    auto dep = dependency.lock();

    if (dep != nullptr) {
        return dep->variable() == nullptr;
    }

    return true;
}

void AnalyserEquation::AnalyserEquationImpl::cleanUpDependencies()
{
    mDependencies.erase(std::remove_if(mDependencies.begin(), mDependencies.end(), isEmptyDependency), mDependencies.end());
}

AnalyserEquation::AnalyserEquation()
    : mPimpl(new AnalyserEquationImpl())
{
}

AnalyserEquation::~AnalyserEquation()
{
    delete mPimpl;
}

AnalyserEquation::Type AnalyserEquation::type() const
{
    return mPimpl->mType;
}

std::string AnalyserEquation::typeAsString() const
{
    if (mPimpl->mType == Type::TRUE_CONSTANT) {
        return "TRUE_CONSTANT";
    }

    if (mPimpl->mType == Type::VARIABLE_BASED_CONSTANT) {
        return "VARIABLE_BASED_CONSTANT";
    }

    if (mPimpl->mType == Type::RATE) {
        return "RATE";
    }

    if (mPimpl->mType == Type::ALGEBRAIC) {
        return "ALGEBRAIC";
    }

    // mPimpl->mType == Type::EXTERNAL.

    return "EXTERNAL";
}

AnalyserEquationAstPtr AnalyserEquation::ast() const
{
    return mPimpl->mAst.lock();
}

std::vector<AnalyserEquationPtr> AnalyserEquation::dependencies() const
{
    std::vector<AnalyserEquationPtr> res;

    for (const auto &dependency : mPimpl->mDependencies) {
        res.push_back(dependency.lock());
    }

    return res;
}

bool AnalyserEquation::isStateRateBased() const
{
    return mPimpl->mIsStateRateBased;
}

AnalyserVariablePtr AnalyserEquation::variable() const
{
    return mPimpl->mVariable.lock();
}

} // namespace libcellml

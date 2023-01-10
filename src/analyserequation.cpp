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
#include "commonutils.h"

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
    auto res = true;
    auto dep = dependency.lock();

    if (dep != nullptr) {
        res = dep->variable() == nullptr;
    }

    return res;
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

AnalyserEquationAstPtr AnalyserEquation::ast() const
{
    return mPimpl->mAst.lock();
}

std::vector<AnalyserEquationPtr> AnalyserEquation::dependencies() const
{
    std::vector<AnalyserEquationPtr> res;

    for (const auto &dependency : mPimpl->mDependencies) {
        // Note: see the llvm-cov section in src/README.rst.

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

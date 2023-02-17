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
#include <iterator>

#include "analyserequation_p.h"

namespace libcellml {

AnalyserEquationPtr AnalyserEquation::AnalyserEquationImpl::create()
{
    return std::shared_ptr<AnalyserEquation> {new AnalyserEquation {}};
}

void AnalyserEquation::AnalyserEquationImpl::populate(AnalyserEquation::Type type,
                                                      const AnalyserEquationAstPtr &ast,
                                                      const std::vector<AnalyserEquationPtr> &dependencies,
                                                      const std::vector<AnalyserVariablePtr> &variables)
{
    mType = type;
    mAst = ast;

    std::copy(dependencies.begin(), dependencies.end(), back_inserter(mDependencies));
    std::copy(variables.begin(), variables.end(), back_inserter(mVariables));
}

bool AnalyserEquation::AnalyserEquationImpl::isEmptyDependency(const AnalyserEquationWeakPtr &dependency)
{
    auto dep = dependency.lock();

    if (dep != nullptr) {
        auto variables = dep->variables();

        if (std::any_of(variables.begin(), variables.end(), [](const auto &v) { return v != nullptr; })) {
            return false;
        }
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

AnalyserEquationAstPtr AnalyserEquation::ast() const
{
    return mPimpl->mAst.lock();
}

size_t AnalyserEquation::dependencyCount() const
{
    return mPimpl->mDependencies.size();
}

std::vector<AnalyserEquationPtr> AnalyserEquation::dependencies() const
{
    std::vector<AnalyserEquationPtr> res;

    for (const auto &dependency : mPimpl->mDependencies) {
        res.push_back(dependency.lock());
    }

    return res;
}

AnalyserEquationPtr AnalyserEquation::dependency(size_t index) const
{
    if (index >= mPimpl->mDependencies.size()) {
        return {};
    }

    return mPimpl->mDependencies[index].lock();
}

bool AnalyserEquation::isStateRateBased() const
{
    return mPimpl->mIsStateRateBased;
}

size_t AnalyserEquation::variableCount() const
{
    return mPimpl->mVariables.size();
}

std::vector<AnalyserVariablePtr> AnalyserEquation::variables() const
{
    std::vector<AnalyserVariablePtr> res;

    for (const auto &variable : mPimpl->mVariables) {
        res.push_back(variable.lock());
    }

    return res;
}

AnalyserVariablePtr AnalyserEquation::variable(size_t index) const
{
    if (index >= mPimpl->mVariables.size()) {
        return {};
    }

    return mPimpl->mVariables[index].lock();
}

} // namespace libcellml

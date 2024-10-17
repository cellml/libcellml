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
#include "utilities.h"

namespace libcellml {

AnalyserEquationPtr AnalyserEquation::AnalyserEquationImpl::create()
{
    return std::shared_ptr<AnalyserEquation> {new AnalyserEquation {}};
}

bool AnalyserEquation::AnalyserEquationImpl::isEmptyDependency(const AnalyserEquationWeakPtr &dependency)
{
    auto variables = libcellml::variables(dependency.lock());

    if (std::any_of(variables.begin(), variables.end(), [](const auto &v) { return v != nullptr; })) {
        return false;
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

static const std::map<AnalyserEquation::Type, std::string> typeToString = {
    {AnalyserEquation::Type::TRUE_CONSTANT, "true_constant"},
    {AnalyserEquation::Type::VARIABLE_BASED_CONSTANT, "variable_based_constant"},
    {AnalyserEquation::Type::ODE, "ode"},
    {AnalyserEquation::Type::NLA, "nla"},
    {AnalyserEquation::Type::ALGEBRAIC, "algebraic"},
    {AnalyserEquation::Type::EXTERNAL, "external"}};

std::string AnalyserEquation::typeAsString(Type type)
{
    return typeToString.at(type);
}

AnalyserEquationAstPtr AnalyserEquation::ast() const
{
    return mPimpl->mAst;
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

size_t AnalyserEquation::nlaSystemIndex() const
{
    return mPimpl->mNlaSystemIndex;
}

size_t AnalyserEquation::nlaSiblingCount() const
{
    return mPimpl->mNlaSiblings.size();
}

std::vector<AnalyserEquationPtr> AnalyserEquation::nlaSiblings() const
{
    std::vector<AnalyserEquationPtr> res;

    for (const auto &nlaSibling : mPimpl->mNlaSiblings) {
        res.push_back(nlaSibling.lock());
    }

    return res;
}

AnalyserEquationPtr AnalyserEquation::nlaSibling(size_t index) const
{
    if (index >= mPimpl->mNlaSiblings.size()) {
        return {};
    }

    return mPimpl->mNlaSiblings[index].lock();
}

bool AnalyserEquation::isStateRateBased() const
{
    return mPimpl->mIsStateRateBased;
}

size_t AnalyserEquation::stateCount() const
{
    return mPimpl->mStates.size();
}

std::vector<AnalyserVariablePtr> AnalyserEquation::states() const
{
    return mPimpl->mStates;
}

AnalyserVariablePtr AnalyserEquation::state(size_t index) const
{
    if (index >= mPimpl->mStates.size()) {
        return {};
    }

    return mPimpl->mStates[index];
}

size_t AnalyserEquation::computedConstantCount() const
{
    return mPimpl->mComputedConstants.size();
}

std::vector<AnalyserVariablePtr> AnalyserEquation::computedConstants() const
{
    return mPimpl->mComputedConstants;
}

AnalyserVariablePtr AnalyserEquation::computedConstant(size_t index) const
{
    if (index >= mPimpl->mComputedConstants.size()) {
        return {};
    }

    return mPimpl->mComputedConstants[index];
}

size_t AnalyserEquation::algebraicCount() const
{
    return mPimpl->mAlgebraic.size();
}

std::vector<AnalyserVariablePtr> AnalyserEquation::algebraic() const
{
    return mPimpl->mAlgebraic;
}

AnalyserVariablePtr AnalyserEquation::algebraic(size_t index) const
{
    if (index >= mPimpl->mAlgebraic.size()) {
        return {};
    }

    return mPimpl->mAlgebraic[index];
}

size_t AnalyserEquation::externalCount() const
{
    return mPimpl->mExternals.size();
}

std::vector<AnalyserVariablePtr> AnalyserEquation::externals() const
{
    return mPimpl->mExternals;
}

AnalyserVariablePtr AnalyserEquation::external(size_t index) const
{
    if (index >= mPimpl->mExternals.size()) {
        return {};
    }

    return mPimpl->mExternals[index];
}

} // namespace libcellml

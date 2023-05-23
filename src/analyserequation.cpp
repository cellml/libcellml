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
                                                      size_t nlaSystemIndex,
                                                      const std::vector<AnalyserEquationPtr> &nlaSiblings,
                                                      const std::vector<AnalyserVariablePtr> &variables)
{
    mType = type;
    mAst = ast;
    mNlaSystemIndex = nlaSystemIndex;

    std::copy(dependencies.begin(), dependencies.end(), back_inserter(mDependencies));
    std::copy(nlaSiblings.begin(), nlaSiblings.end(), back_inserter(mNlaSiblings));
    std::copy(variables.begin(), variables.end(), back_inserter(mVariables));
}

bool AnalyserEquation::AnalyserEquationImpl::isEmptyDependency(const AnalyserEquationWeakPtr &dependency)
{
    auto variables = dependency.lock()->variables();

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

size_t AnalyserEquation::variableCount() const
{
    return mPimpl->mVariables.size();
}

std::vector<AnalyserVariablePtr> AnalyserEquation::variables() const
{
    return mPimpl->mVariables;
}

AnalyserVariablePtr AnalyserEquation::variable(size_t index) const
{
    if (index >= mPimpl->mVariables.size()) {
        return {};
    }

    return mPimpl->mVariables[index];
}

} // namespace libcellml

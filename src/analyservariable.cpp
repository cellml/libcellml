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

#include "libcellml/analyservariable.h"

#include <iterator>

#include "analyservariable_p.h"

namespace libcellml {

AnalyserVariablePtr AnalyserVariable::AnalyserVariableImpl::create()
{
    return std::shared_ptr<AnalyserVariable> {new AnalyserVariable {}};
}

void AnalyserVariable::AnalyserVariableImpl::populate(AnalyserVariable::Type type,
                                                      size_t index,
                                                      const VariablePtr &initialisingVariable,
                                                      const VariablePtr &variable,
                                                      const std::vector<AnalyserEquationPtr> &equations)
{
    mType = type;
    mIndex = index;
    mInitialisingVariable = initialisingVariable;
    mVariable = variable;

    std::copy(equations.begin(), equations.end(), back_inserter(mEquations));
}

AnalyserVariable::AnalyserVariable()
    : mPimpl(new AnalyserVariableImpl())
{
}

AnalyserVariable::~AnalyserVariable()
{
    delete mPimpl;
}

AnalyserVariable::Type AnalyserVariable::type() const
{
    return mPimpl->mType;
}

static const std::map<AnalyserVariable::Type, std::string> typeToString = {
    {AnalyserVariable::Type::VARIABLE_OF_INTEGRATION, "variable_of_integration"},
    {AnalyserVariable::Type::STATE, "state"},
    {AnalyserVariable::Type::CONSTANT, "constant"},
    {AnalyserVariable::Type::COMPUTED_CONSTANT, "computed_constant"},
    {AnalyserVariable::Type::ALGEBRAIC, "algebraic"},
    {AnalyserVariable::Type::EXTERNAL, "external"}};

std::string AnalyserVariable::typeAsString(Type type)
{
    return typeToString.at(type);
}

size_t AnalyserVariable::index() const
{
    return mPimpl->mIndex;
}

VariablePtr AnalyserVariable::initialisingVariable() const
{
    return mPimpl->mInitialisingVariable;
}

VariablePtr AnalyserVariable::variable() const
{
    return mPimpl->mVariable;
}

size_t AnalyserVariable::equationCount() const
{
    return mPimpl->mEquations.size();
}

std::vector<AnalyserEquationPtr> AnalyserVariable::equations() const
{
    std::vector<AnalyserEquationPtr> res;

    for (const auto &equation : mPimpl->mEquations) {
        res.push_back(equation.lock());
    }

    return res;
}

AnalyserEquationPtr AnalyserVariable::equation(size_t index) const
{
    if (index >= mPimpl->mEquations.size()) {
        return {};
    }

    return mPimpl->mEquations[index].lock();
}

} // namespace libcellml

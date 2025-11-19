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

#include "libcellml/variable.h"

#include "analyservariable_p.h"
#include "commonutils.h"

namespace libcellml {

AnalyserVariablePtr AnalyserVariable::AnalyserVariableImpl::create()
{
    return std::shared_ptr<AnalyserVariable> {new AnalyserVariable {}};
}

void AnalyserVariable::AnalyserVariableImpl::populate(AnalyserVariable::Type type,
                                                      size_t index,
                                                      const VariablePtr &initialisingVariable,
                                                      const VariablePtr &variable,
                                                      const AnalyserModelPtr &model,
                                                      const std::vector<AnalyserEquationPtr> &equations)
{
    mType = type;
    mIndex = index;
    mInitialisingVariable = initialisingVariable;
    mVariable = variable;
    mModel = model;

    std::copy(equations.begin(), equations.end(), back_inserter(mEquations));
}

bool AnalyserVariable::AnalyserVariableImpl::constantWithDummyEquation() const
{
    return (mType == Type::CONSTANT) && (mEquations.front().lock() == nullptr);
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
    {AnalyserVariable::Type::ALGEBRAIC_VARIABLE, "algebraic_variable"},
    {AnalyserVariable::Type::EXTERNAL_VARIABLE, "external_variable"}};

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

AnalyserModelPtr AnalyserVariable::model() const
{
    return mPimpl->mModel.lock();
}

// Note: our equation-related methods must account for the fact that a constant initialised using the `initial_value`
//       attribute (rather than through an equation; e.g. x = 3) will have a dummy equation associated with it which
//       we don't want to be accessible, hence the calls to constantWithDummyEquation() in the following methods.

size_t AnalyserVariable::equationCount() const
{
    if (mPimpl->constantWithDummyEquation()) {
        return 0;
    }

    return mPimpl->mEquations.size();
}

std::vector<AnalyserEquationPtr> AnalyserVariable::equations() const
{
    if (mPimpl->constantWithDummyEquation()) {
        return {};
    }

    std::vector<AnalyserEquationPtr> res;

    for (const auto &equation : mPimpl->mEquations) {
        res.push_back(equation.lock());
    }

    return res;
}

AnalyserEquationPtr AnalyserVariable::equation(size_t index) const
{
    if (mPimpl->constantWithDummyEquation() || (index >= mPimpl->mEquations.size())) {
        return {};
    }

    return mPimpl->mEquations[index].lock();
}

} // namespace libcellml

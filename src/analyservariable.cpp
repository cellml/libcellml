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
                                                      const AnalyserEquationPtr &equation)
{
    mType = type;
    mIndex = index;
    mInitialisingVariable = initialisingVariable;
    mVariable = variable;
    mEquation = equation;
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

std::string AnalyserVariable::typeAsString() const
{
    if (mPimpl->mType == Type::VARIABLE_OF_INTEGRATION) {
        return "VARIABLE_OF_INTEGRATION";
    }

    if (mPimpl->mType == Type::STATE) {
        return "STATE";
    }

    if (mPimpl->mType == Type::CONSTANT) {
        return "CONSTANT";
    }

    if (mPimpl->mType == Type::COMPUTED_CONSTANT) {
        return "COMPUTED_CONSTANT";
    }

    if (mPimpl->mType == Type::ALGEBRAIC) {
        return "ALGEBRAIC";
    }

    // mPimpl->mType == Type::EXTERNAL.

    return "EXTERNAL";
}

size_t AnalyserVariable::index() const
{
    return mPimpl->mIndex;
}

VariablePtr AnalyserVariable::initialisingVariable() const
{
    return mPimpl->mInitialisingVariable.lock();
}

VariablePtr AnalyserVariable::variable() const
{
    return mPimpl->mVariable.lock();
}

AnalyserEquationPtr AnalyserVariable::equation() const
{
    return mPimpl->mEquation.lock();
}

} // namespace libcellml

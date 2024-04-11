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
#include "libcellml/variable.h"

#include "interpreterstatement.h"

#include <cassert>

#include "libcellml/interpreter.h"

#include "interpreterstatement_p.h"

#include "libcellml/undefines.h"

namespace libcellml {

InterpreterStatement::InterpreterStatementImpl::InterpreterStatementImpl(Type type,
                                                                         const InterpreterStatementPtr &leftChild,
                                                                         const InterpreterStatementPtr &rightChild)
    : mType(type)
    , mLeftChild(leftChild)
    , mRightChild(rightChild)
{
}

InterpreterStatement::InterpreterStatementImpl::InterpreterStatementImpl(const AnalyserVariablePtr &variable)
    : mType(Type::CI)
    , mVariable(variable)
{
}

InterpreterStatement::InterpreterStatementImpl::InterpreterStatementImpl(double value)
    : mType(Type::CN)
    , mValue(value)
{
}

InterpreterStatementPtr InterpreterStatement::InterpreterStatementImpl::createEquality(const AnalyserVariablePtr &variable, double value)
{
    auto leftChild = InterpreterStatementPtr {new InterpreterStatement {variable}};
    auto rightChild = InterpreterStatementPtr {new InterpreterStatement {value}};

    return InterpreterStatementPtr {new InterpreterStatement {Type::EQUALITY, leftChild, rightChild}};
}

void InterpreterStatement::InterpreterStatementImpl::evaluate(double *states, double *rates, double *variables) const
{
    //---GRY--- AT THIS STAGE, WE ONLY HANDLE AN EQUALITY STATEMENT.

    assert(mType == Type::EQUALITY);

    auto rightChildValue = mRightChild->mPimpl->evaluateToDouble(states, rates, variables);

    if (mLeftChild->mPimpl->mVariable->type() == AnalyserVariable::Type::STATE) {
        states[mLeftChild->mPimpl->mVariable->index()] = rightChildValue;
    } else {
        variables[mLeftChild->mPimpl->mVariable->index()] = rightChildValue;
    }
}

double InterpreterStatement::InterpreterStatementImpl::evaluateToDouble(double *states, double *rates, double *variables) const
{
    //---GRY--- AT THIS STAGE, WE ONLY HANDLE A CN ELEMENT.

    (void)states;
    (void)rates;
    (void)variables;

    assert(mType == Type::CN);

    return mValue;
}

InterpreterStatement::InterpreterStatement(Type type,
                                           const InterpreterStatementPtr &leftChild,
                                           const InterpreterStatementPtr &rightChild)
    : mPimpl(new InterpreterStatementImpl(type, leftChild, rightChild))
{
}

InterpreterStatement::InterpreterStatement(const AnalyserVariablePtr &variable)
    : mPimpl(new InterpreterStatementImpl(variable))
{
}

InterpreterStatement::InterpreterStatement(double value)
    : mPimpl(new InterpreterStatementImpl(value))
{
}

InterpreterStatement::~InterpreterStatement()
{
    delete mPimpl;
}

InterpreterStatementPtr InterpreterStatement::createEquality(const AnalyserVariablePtr &variable, double value) noexcept
{
    return InterpreterStatementImpl::createEquality(variable, value);
}

void InterpreterStatement::evaluate(double *states, double *rates, double *variables) const
{
    mPimpl->evaluate(states, rates, variables);
}

} // namespace libcellml

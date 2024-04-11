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

InterpreterStatement::InterpreterStatementImpl::InterpreterStatementImpl(const AnalyserVariablePtr &variable,
                                                                         bool state)
    : mType(Type::CI)
    , mVariable(variable)
    , mState(state)
{
}

InterpreterStatement::InterpreterStatementImpl::InterpreterStatementImpl(double value)
    : mType(Type::CN)
    , mValue(value)
{
}

void InterpreterStatement::InterpreterStatementImpl::evaluate(double *states, double *rates, double *variables) const
{
    //---GRY--- AT THIS STAGE, WE ONLY HANDLE AN EQUALITY STATEMENT.

    assert(mType == Type::EQUALITY);

    if (mLeftChild->mPimpl->mVariable->type() == AnalyserVariable::Type::STATE) {
        if (mLeftChild->mPimpl->mState) {
            states[mLeftChild->mPimpl->mVariable->index()] = mRightChild->mPimpl->evaluateToDouble(states, rates, variables);
        } else {
            rates[mLeftChild->mPimpl->mVariable->index()] = mRightChild->mPimpl->evaluateToDouble(states, rates, variables);
        }
    } else {
        variables[mLeftChild->mPimpl->mVariable->index()] = mRightChild->mPimpl->evaluateToDouble(states, rates, variables);
    }
}

double InterpreterStatement::InterpreterStatementImpl::evaluateToDouble(double *states, double *rates, double *variables) const
{
    //---GRY--- AT THIS STAGE, WE ONLY HANDLE A CN ELEMENT.

    (void)states;
    (void)rates;
    (void)variables;

    switch (mType) {
        // Arithmetic operators.

    case Type::TIMES:
        return mLeftChild->mPimpl->evaluateToDouble(states, rates, variables) * mRightChild->mPimpl->evaluateToDouble(states, rates, variables);

        // Token elements.

    case Type::CI:
        /*---GRY---
        if (mVariable->type() == AnalyserVariable::Type::STATE) {
            return mState ?
                       states[mVariable->index()] :
                       rates[mVariable->index()];
        } else {
        */
        return variables[mVariable->index()];
        /*---GRY---
        }
        */
    default:
        assert(mType == Type::CN);

        return mValue;
    }
}

InterpreterStatement::InterpreterStatement(Type type,
                                           const InterpreterStatementPtr &leftChild,
                                           const InterpreterStatementPtr &rightChild)
    : mPimpl(new InterpreterStatementImpl(type, leftChild, rightChild))
{
}

InterpreterStatement::InterpreterStatement(const AnalyserVariablePtr &variable, bool state)
    : mPimpl(new InterpreterStatementImpl(variable, state))
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

InterpreterStatementPtr InterpreterStatement::create(Type type,
                                                     const InterpreterStatementPtr &leftChild,
                                                     const InterpreterStatementPtr &rightChild) noexcept
{
    return InterpreterStatementPtr {new InterpreterStatement {type, leftChild, rightChild}};
}

InterpreterStatementPtr InterpreterStatement::create(const AnalyserVariablePtr &variable, bool state) noexcept
{
    return InterpreterStatementPtr {new InterpreterStatement {variable, state}};
}

InterpreterStatementPtr InterpreterStatement::create(double value) noexcept
{
    return InterpreterStatementPtr {new InterpreterStatement {value}};
}

void InterpreterStatement::evaluate(double *states, double *rates, double *variables) const
{
    mPimpl->evaluate(states, rates, variables);
}

} // namespace libcellml

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
        // Relational and logical operators.

    case Type::EQ:
        return mLeftChild->mPimpl->evaluateToDouble(states, rates, variables) == mRightChild->mPimpl->evaluateToDouble(states, rates, variables);
    case Type::NEQ:
        return mLeftChild->mPimpl->evaluateToDouble(states, rates, variables) != mRightChild->mPimpl->evaluateToDouble(states, rates, variables);
    case Type::LT:
        return mLeftChild->mPimpl->evaluateToDouble(states, rates, variables) < mRightChild->mPimpl->evaluateToDouble(states, rates, variables);
    case Type::LEQ:
        return mLeftChild->mPimpl->evaluateToDouble(states, rates, variables) <= mRightChild->mPimpl->evaluateToDouble(states, rates, variables);
    case Type::GT:
        return mLeftChild->mPimpl->evaluateToDouble(states, rates, variables) > mRightChild->mPimpl->evaluateToDouble(states, rates, variables);
    case Type::GEQ:
        return mLeftChild->mPimpl->evaluateToDouble(states, rates, variables) >= mRightChild->mPimpl->evaluateToDouble(states, rates, variables);
    case Type::AND:
        return mLeftChild->mPimpl->evaluateToDouble(states, rates, variables) && mRightChild->mPimpl->evaluateToDouble(states, rates, variables);
    case Type::OR:
        return mLeftChild->mPimpl->evaluateToDouble(states, rates, variables) || mRightChild->mPimpl->evaluateToDouble(states, rates, variables);
    case Type::XOR:
        return (mLeftChild->mPimpl->evaluateToDouble(states, rates, variables) != 0.0) ^ (mRightChild->mPimpl->evaluateToDouble(states, rates, variables) != 0.0);
    case Type::NOT:
        return !mLeftChild->mPimpl->evaluateToDouble(states, rates, variables);

        // Arithmetic operators.

    case Type::PLUS:
        return mLeftChild->mPimpl->evaluateToDouble(states, rates, variables) + mRightChild->mPimpl->evaluateToDouble(states, rates, variables);
    case Type::MINUS:
        if (mRightChild != nullptr) {
            return mLeftChild->mPimpl->evaluateToDouble(states, rates, variables) - mRightChild->mPimpl->evaluateToDouble(states, rates, variables);
        }

        return -mLeftChild->mPimpl->evaluateToDouble(states, rates, variables);
    case Type::TIMES:
        return mLeftChild->mPimpl->evaluateToDouble(states, rates, variables) * mRightChild->mPimpl->evaluateToDouble(states, rates, variables);
    case Type::DIVIDE:
        return mLeftChild->mPimpl->evaluateToDouble(states, rates, variables) / mRightChild->mPimpl->evaluateToDouble(states, rates, variables);
    case Type::POWER:
        return pow(mLeftChild->mPimpl->evaluateToDouble(states, rates, variables), mRightChild->mPimpl->evaluateToDouble(states, rates, variables));
    case Type::SQUARE_ROOT:
        return sqrt(mLeftChild->mPimpl->evaluateToDouble(states, rates, variables));
    case Type::SQUARE: {
        auto x = mLeftChild->mPimpl->evaluateToDouble(states, rates, variables);

        return x * x;
    }
    case Type::ABS:
        return fabs(mLeftChild->mPimpl->evaluateToDouble(states, rates, variables));
    case Type::EXP:
        return exp(mLeftChild->mPimpl->evaluateToDouble(states, rates, variables));
    case Type::LN:
        return log(mLeftChild->mPimpl->evaluateToDouble(states, rates, variables));
    case Type::LOG:
        return log10(mLeftChild->mPimpl->evaluateToDouble(states, rates, variables));
    case Type::CEILING:
        return ceil(mLeftChild->mPimpl->evaluateToDouble(states, rates, variables));
    case Type::FLOOR:
        return floor(mLeftChild->mPimpl->evaluateToDouble(states, rates, variables));
    case Type::MIN:
        return fmin(mLeftChild->mPimpl->evaluateToDouble(states, rates, variables), mRightChild->mPimpl->evaluateToDouble(states, rates, variables));
    case Type::MAX:
        return fmax(mLeftChild->mPimpl->evaluateToDouble(states, rates, variables), mRightChild->mPimpl->evaluateToDouble(states, rates, variables));
    case Type::REM:
        return fmod(mLeftChild->mPimpl->evaluateToDouble(states, rates, variables), mRightChild->mPimpl->evaluateToDouble(states, rates, variables));

        // Token elements.

    case Type::CI:
        if (mVariable->type() == AnalyserVariable::Type::STATE) {
            return mState ?
                       states[mVariable->index()] :
                       rates[mVariable->index()];
        } else {
            return variables[mVariable->index()];
        }
    case Type::CN:
        return mValue;

        // Constants.

    case Type::TRUE:
        return 1.0;
    case Type::FALSE:
        return 0.0;
    case Type::E:
        return M_E;
    case Type::PI:
        return M_PI;
    case Type::INF:
        static const auto INF = std::numeric_limits<double>::infinity();

        return INF;
    default: // Type::NAN:
        assert(mType == Type::NAN);

        static const auto NAN = std::numeric_limits<double>::quiet_NaN();

        return NAN;
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

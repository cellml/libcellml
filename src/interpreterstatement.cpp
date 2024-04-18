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

#ifdef _WIN32
#    define _USE_MATH_DEFINES
#endif

#include "interpreterstatement.h"

#include <cassert>
#include <cmath>

#include "libcellml/interpreter.h"
#include "libcellml/variable.h"

#include "commonutils.h"
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
                                                                         bool rate)
    : mType(Type::CI)
    , mVariable(variable)
    , mRate(rate)
{
}

InterpreterStatement::InterpreterStatementImpl::InterpreterStatementImpl(double value)
    : mType(Type::CN)
    , mValue(value)
{
}

InterpreterStatement::InterpreterStatementImpl::InterpreterStatementImpl(size_t index)
    : mType(Type::EXTERNAL)
    , mIndex(index)
{
}

void InterpreterStatement::InterpreterStatementImpl::evaluate(double *states, double *rates, double *variables) const
{
    //---GRY--- ONLY HANDLE AN EQUALITY STATEMENT FOR NOW.

    assert(mType == Type::EQUALITY);

    if (mLeftChild->mPimpl->mVariable->type() == AnalyserVariable::Type::STATE) {
        if (mLeftChild->mPimpl->mRate) {
            rates[mLeftChild->mPimpl->mVariable->index()] = mRightChild->mPimpl->evaluateToDouble(states, rates, variables);
        } else {
            states[mLeftChild->mPimpl->mVariable->index()] = mRightChild->mPimpl->evaluateToDouble(states, rates, variables);
        }
    } else {
        variables[mLeftChild->mPimpl->mVariable->index()] = mRightChild->mPimpl->evaluateToDouble(states, rates, variables);
    }
}

double InterpreterStatement::InterpreterStatementImpl::evaluateToDouble(double *states, double *rates, double *variables) const
{
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

        // Trigonometric operators.

    case Type::SIN:
        return sin(mLeftChild->mPimpl->evaluateToDouble(states, rates, variables));
    case Type::COS:
        return cos(mLeftChild->mPimpl->evaluateToDouble(states, rates, variables));
    case Type::TAN:
        return tan(mLeftChild->mPimpl->evaluateToDouble(states, rates, variables));
    case Type::SEC:
        return 1.0 / cos(mLeftChild->mPimpl->evaluateToDouble(states, rates, variables));
    case Type::CSC:
        return 1.0 / sin(mLeftChild->mPimpl->evaluateToDouble(states, rates, variables));
    case Type::COT:
        return 1.0 / tan(mLeftChild->mPimpl->evaluateToDouble(states, rates, variables));
    case Type::SINH:
        return sinh(mLeftChild->mPimpl->evaluateToDouble(states, rates, variables));
    case Type::COSH:
        return cosh(mLeftChild->mPimpl->evaluateToDouble(states, rates, variables));
    case Type::TANH:
        return tanh(mLeftChild->mPimpl->evaluateToDouble(states, rates, variables));
    case Type::SECH:
        return 1.0 / cosh(mLeftChild->mPimpl->evaluateToDouble(states, rates, variables));
    case Type::CSCH:
        return 1.0 / sinh(mLeftChild->mPimpl->evaluateToDouble(states, rates, variables));
    case Type::COTH:
        return 1.0 / tanh(mLeftChild->mPimpl->evaluateToDouble(states, rates, variables));
    case Type::ASIN:
        return asin(mLeftChild->mPimpl->evaluateToDouble(states, rates, variables));
    case Type::ACOS:
        return acos(mLeftChild->mPimpl->evaluateToDouble(states, rates, variables));
    case Type::ATAN:
        return atan(mLeftChild->mPimpl->evaluateToDouble(states, rates, variables));
    case Type::ASEC:
        return acos(1.0 / mLeftChild->mPimpl->evaluateToDouble(states, rates, variables));
    case Type::ACSC:
        return asin(1.0 / mLeftChild->mPimpl->evaluateToDouble(states, rates, variables));
    case Type::ACOT:
        return atan(1.0 / mLeftChild->mPimpl->evaluateToDouble(states, rates, variables));
    case Type::ASINH:
        return asinh(mLeftChild->mPimpl->evaluateToDouble(states, rates, variables));
    case Type::ACOSH:
        return acosh(mLeftChild->mPimpl->evaluateToDouble(states, rates, variables));
    case Type::ATANH:
        return atanh(mLeftChild->mPimpl->evaluateToDouble(states, rates, variables));
    case Type::ASECH:
        return acosh(1.0 / mLeftChild->mPimpl->evaluateToDouble(states, rates, variables));
    case Type::ACSCH:
        return asinh(1.0 / mLeftChild->mPimpl->evaluateToDouble(states, rates, variables));
    case Type::ACOTH:
        return atanh(1.0 / mLeftChild->mPimpl->evaluateToDouble(states, rates, variables));

        // Token elements.

    case Type::CI:
        if (mVariable->type() == AnalyserVariable::Type::STATE) {
            return mRate ?
                       rates[mVariable->index()] :
                       states[mVariable->index()];
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
    case Type::INF: {
        static const auto INF = std::numeric_limits<double>::infinity();

        return INF;
    }
    case Type::NAN: {
        static const auto NAN = std::numeric_limits<double>::quiet_NaN();

        return NAN;
    }
    default: { // Type::EXTERNAL:
        //---GRY--- JUST RETURN NAN FOR NOW.

        assert(mType == Type::EXTERNAL);

        static const auto NAN = std::numeric_limits<double>::quiet_NaN();

        return NAN;
    }
    }
}

InterpreterStatement::InterpreterStatement(Type type,
                                           const InterpreterStatementPtr &leftChild,
                                           const InterpreterStatementPtr &rightChild)
    : mPimpl(new InterpreterStatementImpl(type, leftChild, rightChild))
{
}

InterpreterStatement::InterpreterStatement(const AnalyserVariablePtr &variable, bool rate)
    : mPimpl(new InterpreterStatementImpl(variable, rate))
{
}

InterpreterStatement::InterpreterStatement(double value)
    : mPimpl(new InterpreterStatementImpl(value))
{
}

InterpreterStatement::InterpreterStatement(size_t index)
    : mPimpl(new InterpreterStatementImpl(index))
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

InterpreterStatementPtr InterpreterStatement::create(const AnalyserVariablePtr &variable, bool rate) noexcept
{
    return InterpreterStatementPtr {new InterpreterStatement {variable, rate}};
}

InterpreterStatementPtr InterpreterStatement::create(double value) noexcept
{
    return InterpreterStatementPtr {new InterpreterStatement {value}};
}

InterpreterStatementPtr InterpreterStatement::create(size_t index) noexcept
{
    return InterpreterStatementPtr {new InterpreterStatement {index}};
}

void InterpreterStatement::evaluate(double *states, double *rates, double *variables) const
{
    mPimpl->evaluate(states, rates, variables);
}

} // namespace libcellml

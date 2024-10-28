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
    : mType((variable->type() == AnalyserVariable::Type::STATE) ?
                (rate ?
                     Type::RATE :
                     Type::STATE) :
                ((variable->type() == AnalyserVariable::Type::CONSTANT) ?
                     Type::CONSTANT :
                     ((variable->type() == AnalyserVariable::Type::COMPUTED_CONSTANT) ?
                          Type::COMPUTED_CONSTANT :
                          ((variable->type() == AnalyserVariable::Type::ALGEBRAIC) ?
                               Type::ALGEBRAIC :
                               Type::EXTERNAL))))
    , mVariable(variable)
    , mIndex(variable->index())
{
}

InterpreterStatement::InterpreterStatementImpl::InterpreterStatementImpl(double value)
    : mType(Type::NUMBER)
    , mValue(value)
{
}

InterpreterStatement::InterpreterStatementImpl::InterpreterStatementImpl(size_t index)
    : mType(Type::EXTERNAL_VARIABLE_CALL)
    , mIndex(index)
{
}

void InterpreterStatement::InterpreterStatementImpl::evaluate(double voi, double *states, double *rates, double *constants, double *computedConstants, double *algebraic, double *externals, AlgebraicModelExternalVariable algebraicModelExternalVariable, DifferentialModelExternalVariable differentialModelExternalVariable) const
{
    if (mLeftChild->mPimpl->mType == Type::STATE) {
        states[mLeftChild->mPimpl->mIndex] = mRightChild->mPimpl->evaluateToDouble(voi, states, rates, constants, computedConstants, algebraic, externals, algebraicModelExternalVariable, differentialModelExternalVariable);
    } else if (mLeftChild->mPimpl->mType == Type::RATE) {
        rates[mLeftChild->mPimpl->mIndex] = mRightChild->mPimpl->evaluateToDouble(voi, states, rates, constants, computedConstants, algebraic, externals, algebraicModelExternalVariable, differentialModelExternalVariable);
    } else if (mLeftChild->mPimpl->mType == Type::CONSTANT) {
        constants[mLeftChild->mPimpl->mIndex] = mRightChild->mPimpl->evaluateToDouble(voi, states, rates, constants, computedConstants, algebraic, externals, algebraicModelExternalVariable, differentialModelExternalVariable);
    } else if (mLeftChild->mPimpl->mType == Type::COMPUTED_CONSTANT) {
        computedConstants[mLeftChild->mPimpl->mIndex] = mRightChild->mPimpl->evaluateToDouble(voi, states, rates, constants, computedConstants, algebraic, externals, algebraicModelExternalVariable, differentialModelExternalVariable);
    } else if (mLeftChild->mPimpl->mType == Type::ALGEBRAIC) {
        algebraic[mLeftChild->mPimpl->mIndex] = mRightChild->mPimpl->evaluateToDouble(voi, states, rates, constants, computedConstants, algebraic, externals, algebraicModelExternalVariable, differentialModelExternalVariable);
    } else {
        externals[mLeftChild->mPimpl->mIndex] = mRightChild->mPimpl->evaluateToDouble(voi, states, rates, constants, computedConstants, algebraic, externals, algebraicModelExternalVariable, differentialModelExternalVariable);
    }
}

double InterpreterStatement::InterpreterStatementImpl::evaluateToDouble(double voi, double *states, double *rates, double *constants, double *computedConstants, double *algebraic, double *externals, AlgebraicModelExternalVariable algebraicModelExternalVariable, DifferentialModelExternalVariable differentialModelExternalVariable) const
{
    switch (mType) {
        // Relational and logical operators.

    case Type::EQ:
        return mLeftChild->mPimpl->evaluateToDouble(voi, states, rates, constants, computedConstants, algebraic, externals, algebraicModelExternalVariable, differentialModelExternalVariable) == mRightChild->mPimpl->evaluateToDouble(voi, states, rates, constants, computedConstants, algebraic, externals, algebraicModelExternalVariable, differentialModelExternalVariable);
    case Type::NEQ:
        return mLeftChild->mPimpl->evaluateToDouble(voi, states, rates, constants, computedConstants, algebraic, externals, algebraicModelExternalVariable, differentialModelExternalVariable) != mRightChild->mPimpl->evaluateToDouble(voi, states, rates, constants, computedConstants, algebraic, externals, algebraicModelExternalVariable, differentialModelExternalVariable);
    case Type::LT:
        return mLeftChild->mPimpl->evaluateToDouble(voi, states, rates, constants, computedConstants, algebraic, externals, algebraicModelExternalVariable, differentialModelExternalVariable) < mRightChild->mPimpl->evaluateToDouble(voi, states, rates, constants, computedConstants, algebraic, externals, algebraicModelExternalVariable, differentialModelExternalVariable);
    case Type::LEQ:
        return mLeftChild->mPimpl->evaluateToDouble(voi, states, rates, constants, computedConstants, algebraic, externals, algebraicModelExternalVariable, differentialModelExternalVariable) <= mRightChild->mPimpl->evaluateToDouble(voi, states, rates, constants, computedConstants, algebraic, externals, algebraicModelExternalVariable, differentialModelExternalVariable);
    case Type::GT:
        return mLeftChild->mPimpl->evaluateToDouble(voi, states, rates, constants, computedConstants, algebraic, externals, algebraicModelExternalVariable, differentialModelExternalVariable) > mRightChild->mPimpl->evaluateToDouble(voi, states, rates, constants, computedConstants, algebraic, externals, algebraicModelExternalVariable, differentialModelExternalVariable);
    case Type::GEQ:
        return mLeftChild->mPimpl->evaluateToDouble(voi, states, rates, constants, computedConstants, algebraic, externals, algebraicModelExternalVariable, differentialModelExternalVariable) >= mRightChild->mPimpl->evaluateToDouble(voi, states, rates, constants, computedConstants, algebraic, externals, algebraicModelExternalVariable, differentialModelExternalVariable);
    case Type::AND:
        return mLeftChild->mPimpl->evaluateToDouble(voi, states, rates, constants, computedConstants, algebraic, externals, algebraicModelExternalVariable, differentialModelExternalVariable) && mRightChild->mPimpl->evaluateToDouble(voi, states, rates, constants, computedConstants, algebraic, externals, algebraicModelExternalVariable, differentialModelExternalVariable);
    case Type::OR:
        return mLeftChild->mPimpl->evaluateToDouble(voi, states, rates, constants, computedConstants, algebraic, externals, algebraicModelExternalVariable, differentialModelExternalVariable) || mRightChild->mPimpl->evaluateToDouble(voi, states, rates, constants, computedConstants, algebraic, externals, algebraicModelExternalVariable, differentialModelExternalVariable);
    case Type::XOR:
        return (mLeftChild->mPimpl->evaluateToDouble(voi, states, rates, constants, computedConstants, algebraic, externals, algebraicModelExternalVariable, differentialModelExternalVariable) != 0.0) ^ (mRightChild->mPimpl->evaluateToDouble(voi, states, rates, constants, computedConstants, algebraic, externals, algebraicModelExternalVariable, differentialModelExternalVariable) != 0.0);
    case Type::NOT:
        return !mLeftChild->mPimpl->evaluateToDouble(voi, states, rates, constants, computedConstants, algebraic, externals, algebraicModelExternalVariable, differentialModelExternalVariable);

        // Arithmetic operators.

    case Type::PLUS:
        return mLeftChild->mPimpl->evaluateToDouble(voi, states, rates, constants, computedConstants, algebraic, externals, algebraicModelExternalVariable, differentialModelExternalVariable) + mRightChild->mPimpl->evaluateToDouble(voi, states, rates, constants, computedConstants, algebraic, externals, algebraicModelExternalVariable, differentialModelExternalVariable);
    case Type::MINUS:
        if (mRightChild != nullptr) {
            return mLeftChild->mPimpl->evaluateToDouble(voi, states, rates, constants, computedConstants, algebraic, externals, algebraicModelExternalVariable, differentialModelExternalVariable) - mRightChild->mPimpl->evaluateToDouble(voi, states, rates, constants, computedConstants, algebraic, externals, algebraicModelExternalVariable, differentialModelExternalVariable);
        }

        return -mLeftChild->mPimpl->evaluateToDouble(voi, states, rates, constants, computedConstants, algebraic, externals, algebraicModelExternalVariable, differentialModelExternalVariable);
    case Type::TIMES:
        return mLeftChild->mPimpl->evaluateToDouble(voi, states, rates, constants, computedConstants, algebraic, externals, algebraicModelExternalVariable, differentialModelExternalVariable) * mRightChild->mPimpl->evaluateToDouble(voi, states, rates, constants, computedConstants, algebraic, externals, algebraicModelExternalVariable, differentialModelExternalVariable);
    case Type::DIVIDE:
        return mLeftChild->mPimpl->evaluateToDouble(voi, states, rates, constants, computedConstants, algebraic, externals, algebraicModelExternalVariable, differentialModelExternalVariable) / mRightChild->mPimpl->evaluateToDouble(voi, states, rates, constants, computedConstants, algebraic, externals, algebraicModelExternalVariable, differentialModelExternalVariable);
    case Type::POWER:
        return pow(mLeftChild->mPimpl->evaluateToDouble(voi, states, rates, constants, computedConstants, algebraic, externals, algebraicModelExternalVariable, differentialModelExternalVariable), mRightChild->mPimpl->evaluateToDouble(voi, states, rates, constants, computedConstants, algebraic, externals, algebraicModelExternalVariable, differentialModelExternalVariable));
    case Type::SQUARE_ROOT:
        return sqrt(mLeftChild->mPimpl->evaluateToDouble(voi, states, rates, constants, computedConstants, algebraic, externals, algebraicModelExternalVariable, differentialModelExternalVariable));
    case Type::SQUARE: {
        auto x = mLeftChild->mPimpl->evaluateToDouble(voi, states, rates, constants, computedConstants, algebraic, externals, algebraicModelExternalVariable, differentialModelExternalVariable);

        return x * x;
    }
    case Type::ABS:
        return fabs(mLeftChild->mPimpl->evaluateToDouble(voi, states, rates, constants, computedConstants, algebraic, externals, algebraicModelExternalVariable, differentialModelExternalVariable));
    case Type::EXP:
        return exp(mLeftChild->mPimpl->evaluateToDouble(voi, states, rates, constants, computedConstants, algebraic, externals, algebraicModelExternalVariable, differentialModelExternalVariable));
    case Type::LN:
        return log(mLeftChild->mPimpl->evaluateToDouble(voi, states, rates, constants, computedConstants, algebraic, externals, algebraicModelExternalVariable, differentialModelExternalVariable));
    case Type::LOG:
        return log10(mLeftChild->mPimpl->evaluateToDouble(voi, states, rates, constants, computedConstants, algebraic, externals, algebraicModelExternalVariable, differentialModelExternalVariable));
    case Type::CEILING:
        return ceil(mLeftChild->mPimpl->evaluateToDouble(voi, states, rates, constants, computedConstants, algebraic, externals, algebraicModelExternalVariable, differentialModelExternalVariable));
    case Type::FLOOR:
        return floor(mLeftChild->mPimpl->evaluateToDouble(voi, states, rates, constants, computedConstants, algebraic, externals, algebraicModelExternalVariable, differentialModelExternalVariable));
    case Type::MIN:
        return fmin(mLeftChild->mPimpl->evaluateToDouble(voi, states, rates, constants, computedConstants, algebraic, externals, algebraicModelExternalVariable, differentialModelExternalVariable), mRightChild->mPimpl->evaluateToDouble(voi, states, rates, constants, computedConstants, algebraic, externals, algebraicModelExternalVariable, differentialModelExternalVariable));
    case Type::MAX:
        return fmax(mLeftChild->mPimpl->evaluateToDouble(voi, states, rates, constants, computedConstants, algebraic, externals, algebraicModelExternalVariable, differentialModelExternalVariable), mRightChild->mPimpl->evaluateToDouble(voi, states, rates, constants, computedConstants, algebraic, externals, algebraicModelExternalVariable, differentialModelExternalVariable));
    case Type::REM:
        return fmod(mLeftChild->mPimpl->evaluateToDouble(voi, states, rates, constants, computedConstants, algebraic, externals, algebraicModelExternalVariable, differentialModelExternalVariable), mRightChild->mPimpl->evaluateToDouble(voi, states, rates, constants, computedConstants, algebraic, externals, algebraicModelExternalVariable, differentialModelExternalVariable));

        // Trigonometric operators.

    case Type::SIN:
        return sin(mLeftChild->mPimpl->evaluateToDouble(voi, states, rates, constants, computedConstants, algebraic, externals, algebraicModelExternalVariable, differentialModelExternalVariable));
    case Type::COS:
        return cos(mLeftChild->mPimpl->evaluateToDouble(voi, states, rates, constants, computedConstants, algebraic, externals, algebraicModelExternalVariable, differentialModelExternalVariable));
    case Type::TAN:
        return tan(mLeftChild->mPimpl->evaluateToDouble(voi, states, rates, constants, computedConstants, algebraic, externals, algebraicModelExternalVariable, differentialModelExternalVariable));
    case Type::SEC:
        return 1.0 / cos(mLeftChild->mPimpl->evaluateToDouble(voi, states, rates, constants, computedConstants, algebraic, externals, algebraicModelExternalVariable, differentialModelExternalVariable));
    case Type::CSC:
        return 1.0 / sin(mLeftChild->mPimpl->evaluateToDouble(voi, states, rates, constants, computedConstants, algebraic, externals, algebraicModelExternalVariable, differentialModelExternalVariable));
    case Type::COT:
        return 1.0 / tan(mLeftChild->mPimpl->evaluateToDouble(voi, states, rates, constants, computedConstants, algebraic, externals, algebraicModelExternalVariable, differentialModelExternalVariable));
    case Type::SINH:
        return sinh(mLeftChild->mPimpl->evaluateToDouble(voi, states, rates, constants, computedConstants, algebraic, externals, algebraicModelExternalVariable, differentialModelExternalVariable));
    case Type::COSH:
        return cosh(mLeftChild->mPimpl->evaluateToDouble(voi, states, rates, constants, computedConstants, algebraic, externals, algebraicModelExternalVariable, differentialModelExternalVariable));
    case Type::TANH:
        return tanh(mLeftChild->mPimpl->evaluateToDouble(voi, states, rates, constants, computedConstants, algebraic, externals, algebraicModelExternalVariable, differentialModelExternalVariable));
    case Type::SECH:
        return 1.0 / cosh(mLeftChild->mPimpl->evaluateToDouble(voi, states, rates, constants, computedConstants, algebraic, externals, algebraicModelExternalVariable, differentialModelExternalVariable));
    case Type::CSCH:
        return 1.0 / sinh(mLeftChild->mPimpl->evaluateToDouble(voi, states, rates, constants, computedConstants, algebraic, externals, algebraicModelExternalVariable, differentialModelExternalVariable));
    case Type::COTH:
        return 1.0 / tanh(mLeftChild->mPimpl->evaluateToDouble(voi, states, rates, constants, computedConstants, algebraic, externals, algebraicModelExternalVariable, differentialModelExternalVariable));
    case Type::ASIN:
        return asin(mLeftChild->mPimpl->evaluateToDouble(voi, states, rates, constants, computedConstants, algebraic, externals, algebraicModelExternalVariable, differentialModelExternalVariable));
    case Type::ACOS:
        return acos(mLeftChild->mPimpl->evaluateToDouble(voi, states, rates, constants, computedConstants, algebraic, externals, algebraicModelExternalVariable, differentialModelExternalVariable));
    case Type::ATAN:
        return atan(mLeftChild->mPimpl->evaluateToDouble(voi, states, rates, constants, computedConstants, algebraic, externals, algebraicModelExternalVariable, differentialModelExternalVariable));
    case Type::ASEC:
        return acos(1.0 / mLeftChild->mPimpl->evaluateToDouble(voi, states, rates, constants, computedConstants, algebraic, externals, algebraicModelExternalVariable, differentialModelExternalVariable));
    case Type::ACSC:
        return asin(1.0 / mLeftChild->mPimpl->evaluateToDouble(voi, states, rates, constants, computedConstants, algebraic, externals, algebraicModelExternalVariable, differentialModelExternalVariable));
    case Type::ACOT:
        return atan(1.0 / mLeftChild->mPimpl->evaluateToDouble(voi, states, rates, constants, computedConstants, algebraic, externals, algebraicModelExternalVariable, differentialModelExternalVariable));
    case Type::ASINH:
        return asinh(mLeftChild->mPimpl->evaluateToDouble(voi, states, rates, constants, computedConstants, algebraic, externals, algebraicModelExternalVariable, differentialModelExternalVariable));
    case Type::ACOSH:
        return acosh(mLeftChild->mPimpl->evaluateToDouble(voi, states, rates, constants, computedConstants, algebraic, externals, algebraicModelExternalVariable, differentialModelExternalVariable));
    case Type::ATANH:
        return atanh(mLeftChild->mPimpl->evaluateToDouble(voi, states, rates, constants, computedConstants, algebraic, externals, algebraicModelExternalVariable, differentialModelExternalVariable));
    case Type::ASECH:
        return acosh(1.0 / mLeftChild->mPimpl->evaluateToDouble(voi, states, rates, constants, computedConstants, algebraic, externals, algebraicModelExternalVariable, differentialModelExternalVariable));
    case Type::ACSCH:
        return asinh(1.0 / mLeftChild->mPimpl->evaluateToDouble(voi, states, rates, constants, computedConstants, algebraic, externals, algebraicModelExternalVariable, differentialModelExternalVariable));
    case Type::ACOTH:
        return atanh(1.0 / mLeftChild->mPimpl->evaluateToDouble(voi, states, rates, constants, computedConstants, algebraic, externals, algebraicModelExternalVariable, differentialModelExternalVariable));

        // Piecewise statement.

    case Type::PIECEWISE: {
        return (mLeftChild->mPimpl->mRightChild->mPimpl->evaluateToDouble(voi, states, rates, constants, computedConstants, algebraic, externals, algebraicModelExternalVariable, differentialModelExternalVariable) ?
                    mLeftChild->mPimpl->mLeftChild->mPimpl->evaluateToDouble(voi, states, rates, constants, computedConstants, algebraic, externals, algebraicModelExternalVariable, differentialModelExternalVariable) :
                    mRightChild->mPimpl->evaluateToDouble(voi, states, rates, constants, computedConstants, algebraic, externals, algebraicModelExternalVariable, differentialModelExternalVariable));
    }

        // Token elements.

    case Type::VOI:
        return voi;
    case Type::STATE:
        return states[mIndex];
    case Type::RATE:
        return rates[mIndex];
    case Type::CONSTANT:
        return constants[mIndex];
    case Type::COMPUTED_CONSTANT:
        return computedConstants[mIndex];
    case Type::ALGEBRAIC:
        return algebraic[mIndex];
    case Type::EXTERNAL:
        return externals[mIndex];
    case Type::NUMBER:
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
    default: // Type::EXTERNAL_VARIABLE_CALL:
        if (algebraicModelExternalVariable != nullptr) {
            return algebraicModelExternalVariable(constants, computedConstants, algebraic, externals, mIndex);
        }

        return differentialModelExternalVariable(voi, states, rates, constants, computedConstants, algebraic, externals, mIndex);
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

void InterpreterStatement::evaluate(double voi, double *states, double *rates, double *constants, double *computedConstants, double *algebraic, double *externals, AlgebraicModelExternalVariable algebraicModelExternalVariable, DifferentialModelExternalVariable differentialModelExternalVariable) const
{
    mPimpl->evaluate(voi, states, rates, constants, computedConstants, algebraic, externals, algebraicModelExternalVariable, differentialModelExternalVariable);
}

} // namespace libcellml

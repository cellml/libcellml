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

#include "interpreterrpnstatement.h"

#include <cassert>
#include <cmath>

#include "libcellml/interpreter.h"
#include "libcellml/variable.h"

#include "commonutils.h"
#include "interpreterrpnstatement_p.h"

#include "libcellml/undefines.h"

namespace libcellml {

InterpreterRpnStatement::InterpreterRpnStatementImpl::InterpreterRpnStatementImpl(Type type)
    : mType(type)
{
}

InterpreterRpnStatement::InterpreterRpnStatementImpl::InterpreterRpnStatementImpl(const AnalyserVariablePtr &variable,
                                                                                  bool rate)
    : mType((variable->type() == AnalyserVariable::Type::STATE) ?
                (rate ?
                     Type::RATE :
                     Type::STATE) :
                Type::VARIABLE)
    , mVariable(variable)
    , mIndex(variable->index())
{
}

InterpreterRpnStatement::InterpreterRpnStatementImpl::InterpreterRpnStatementImpl(double value)
    : mType(Type::NUMBER)
    , mValue(value)
{
}

InterpreterRpnStatement::InterpreterRpnStatementImpl::InterpreterRpnStatementImpl(size_t externalIndex)
    : mType(Type::EXTERNAL)
    , mExternalIndex(externalIndex)
{
}

double InterpreterRpnStatement::InterpreterRpnStatementImpl::stackTopValue(double *states, double *rates, double *variables,
                                                                           std::stack<InterpreterStackElement> &stack) const
{
    auto top = stack.top();

    stack.pop();

    return (top.mType == InterpreterStackElement::Type::NUMBER) ?
               top.mValue :
               ((top.mType == InterpreterStackElement::Type::STATE) ?
                    states[top.mIndex] :
                    ((top.mType == InterpreterStackElement::Type::RATE) ?
                         rates[top.mIndex] :
                         variables[top.mIndex]));
}

void InterpreterRpnStatement::InterpreterRpnStatementImpl::evaluate(double voi, double *states, double *rates, double *variables,
                                                                    std::stack<InterpreterStackElement> &stack) const
{
    switch (mType) {
        // Equality.

    case Type::EQUALITY: {
        assert(stack.size() == 2);

        auto rhsValue = stackTopValue(states, rates, variables, stack);
        auto lhs = stack.top();

        stack.pop();

        if (lhs.mType == InterpreterStackElement::Type::STATE) {
            states[lhs.mIndex] = rhsValue;
        } else if (lhs.mType == InterpreterStackElement::Type::RATE) {
            rates[lhs.mIndex] = rhsValue;
        } else {
            variables[lhs.mIndex] = rhsValue;
        }
    } break;

        // Relational and logical operators.

    case Type::EQ: {
        auto rhsValue = stackTopValue(states, rates, variables, stack);
        auto lhsValue = stackTopValue(states, rates, variables, stack);

        stack.push(InterpreterStackElement {static_cast<double>(lhsValue == rhsValue)});
    } break;
    case Type::NEQ: {
        auto rhsValue = stackTopValue(states, rates, variables, stack);
        auto lhsValue = stackTopValue(states, rates, variables, stack);

        stack.push(InterpreterStackElement {static_cast<double>(lhsValue != rhsValue)});
    } break;
    case Type::LT: {
        auto rhsValue = stackTopValue(states, rates, variables, stack);
        auto lhsValue = stackTopValue(states, rates, variables, stack);

        stack.push(InterpreterStackElement {static_cast<double>(lhsValue < rhsValue)});
    } break;
    case Type::LEQ: {
        auto rhsValue = stackTopValue(states, rates, variables, stack);
        auto lhsValue = stackTopValue(states, rates, variables, stack);

        stack.push(InterpreterStackElement {static_cast<double>(lhsValue <= rhsValue)});
    } break;
    case Type::GT: {
        auto rhsValue = stackTopValue(states, rates, variables, stack);
        auto lhsValue = stackTopValue(states, rates, variables, stack);

        stack.push(InterpreterStackElement {static_cast<double>(lhsValue > rhsValue)});
    } break;
    case Type::GEQ: {
        auto rhsValue = stackTopValue(states, rates, variables, stack);
        auto lhsValue = stackTopValue(states, rates, variables, stack);

        stack.push(InterpreterStackElement {static_cast<double>(lhsValue >= rhsValue)});
    } break;
    case Type::AND: {
        auto rhsValue = stackTopValue(states, rates, variables, stack);
        auto lhsValue = stackTopValue(states, rates, variables, stack);

        stack.push(InterpreterStackElement {static_cast<double>(lhsValue && rhsValue)});
    } break;
    case Type::OR: {
        auto rhsValue = stackTopValue(states, rates, variables, stack);
        auto lhsValue = stackTopValue(states, rates, variables, stack);

        stack.push(InterpreterStackElement {static_cast<double>(lhsValue || rhsValue)});
    } break;
    case Type::XOR: {
        auto rhsValue = stackTopValue(states, rates, variables, stack);
        auto lhsValue = stackTopValue(states, rates, variables, stack);

        stack.push(InterpreterStackElement {static_cast<double>((lhsValue != 0.0) ^ (rhsValue != 0.0))});
    } break;
    case Type::NOT: {
        stack.push(InterpreterStackElement {static_cast<double>(!stackTopValue(states, rates, variables, stack))});
    } break;

        // Arithmetic operators.

    case Type::PLUS: {
        auto rhsValue = stackTopValue(states, rates, variables, stack);
        auto lhsValue = stackTopValue(states, rates, variables, stack);

        stack.push(InterpreterStackElement {lhsValue + rhsValue});
    } break;
    case Type::UNARY_MINUS:
        stack.push(InterpreterStackElement {-stackTopValue(states, rates, variables, stack)});

        break;
    case Type::MINUS: {
        auto rhsValue = stackTopValue(states, rates, variables, stack);
        auto lhsValue = stackTopValue(states, rates, variables, stack);

        stack.push(InterpreterStackElement {lhsValue - rhsValue});
    } break;
    case Type::TIMES: {
        auto rhsValue = stackTopValue(states, rates, variables, stack);
        auto lhsValue = stackTopValue(states, rates, variables, stack);

        stack.push(InterpreterStackElement {lhsValue * rhsValue});
    } break;
    case Type::DIVIDE: {
        auto rhsValue = stackTopValue(states, rates, variables, stack);
        auto lhsValue = stackTopValue(states, rates, variables, stack);

        stack.push(InterpreterStackElement {lhsValue / rhsValue});
    } break;
    case Type::POWER: {
        auto rhsValue = stackTopValue(states, rates, variables, stack);
        auto lhsValue = stackTopValue(states, rates, variables, stack);

        stack.push(InterpreterStackElement {pow(lhsValue, rhsValue)});
    } break;
    case Type::SQUARE_ROOT: {
        auto lhsValue = stackTopValue(states, rates, variables, stack);

        stack.push(InterpreterStackElement {sqrt(lhsValue)});
    } break;
    case Type::SQUARE: {
        auto lhsValue = stackTopValue(states, rates, variables, stack);

        stack.push(InterpreterStackElement {lhsValue * lhsValue});
    } break;
    case Type::ABS: {
        auto lhsValue = stackTopValue(states, rates, variables, stack);

        stack.push(InterpreterStackElement {fabs(lhsValue)});
    } break;
    case Type::EXP: {
        auto lhsValue = stackTopValue(states, rates, variables, stack);

        stack.push(InterpreterStackElement {exp(lhsValue)});
    } break;
    case Type::LN: {
        auto lhsValue = stackTopValue(states, rates, variables, stack);

        stack.push(InterpreterStackElement {log(lhsValue)});
    } break;
    case Type::LOG: {
        auto lhsValue = stackTopValue(states, rates, variables, stack);

        stack.push(InterpreterStackElement {log10(lhsValue)});
    } break;
    case Type::CEILING: {
        auto lhsValue = stackTopValue(states, rates, variables, stack);

        stack.push(InterpreterStackElement {ceil(lhsValue)});
    } break;
    case Type::FLOOR: {
        auto lhsValue = stackTopValue(states, rates, variables, stack);

        stack.push(InterpreterStackElement {floor(lhsValue)});
    } break;
    case Type::MIN: {
        auto rhsValue = stackTopValue(states, rates, variables, stack);
        auto lhsValue = stackTopValue(states, rates, variables, stack);

        stack.push(InterpreterStackElement {fmin(lhsValue, rhsValue)});
    } break;
    case Type::MAX: {
        auto rhsValue = stackTopValue(states, rates, variables, stack);
        auto lhsValue = stackTopValue(states, rates, variables, stack);

        stack.push(InterpreterStackElement {fmax(lhsValue, rhsValue)});
    } break;
    case Type::REM: {
        auto rhsValue = stackTopValue(states, rates, variables, stack);
        auto lhsValue = stackTopValue(states, rates, variables, stack);

        stack.push(InterpreterStackElement {fmod(lhsValue, rhsValue)});
    } break;

        // Trigonometric operators.

    case Type::SIN: {
        auto lhsValue = stackTopValue(states, rates, variables, stack);

        stack.push(InterpreterStackElement {sin(lhsValue)});
    } break;
    case Type::COS: {
        auto lhsValue = stackTopValue(states, rates, variables, stack);

        stack.push(InterpreterStackElement {cos(lhsValue)});
    } break;
    case Type::TAN: {
        auto lhsValue = stackTopValue(states, rates, variables, stack);

        stack.push(InterpreterStackElement {tan(lhsValue)});
    } break;
    case Type::SEC: {
        auto lhsValue = stackTopValue(states, rates, variables, stack);

        stack.push(InterpreterStackElement {1.0 / cos(lhsValue)});
    } break;
    case Type::CSC: {
        auto lhsValue = stackTopValue(states, rates, variables, stack);

        stack.push(InterpreterStackElement {1.0 / sin(lhsValue)});
    } break;
    case Type::COT: {
        auto lhsValue = stackTopValue(states, rates, variables, stack);

        stack.push(InterpreterStackElement {1.0 / tan(lhsValue)});
    } break;
    case Type::SINH: {
        auto lhsValue = stackTopValue(states, rates, variables, stack);

        stack.push(InterpreterStackElement {sinh(lhsValue)});
    } break;
    case Type::COSH: {
        auto lhsValue = stackTopValue(states, rates, variables, stack);

        stack.push(InterpreterStackElement {cosh(lhsValue)});
    } break;
    case Type::TANH: {
        auto lhsValue = stackTopValue(states, rates, variables, stack);

        stack.push(InterpreterStackElement {tanh(lhsValue)});
    } break;
    case Type::SECH: {
        auto lhsValue = stackTopValue(states, rates, variables, stack);

        stack.push(InterpreterStackElement {1.0 / cosh(lhsValue)});
    } break;
    case Type::CSCH: {
        auto lhsValue = stackTopValue(states, rates, variables, stack);

        stack.push(InterpreterStackElement {1.0 / sinh(lhsValue)});
    } break;
    case Type::COTH: {
        auto lhsValue = stackTopValue(states, rates, variables, stack);

        stack.push(InterpreterStackElement {1.0 / tanh(lhsValue)});
    } break;
    case Type::ASIN: {
        auto lhsValue = stackTopValue(states, rates, variables, stack);

        stack.push(InterpreterStackElement {asin(lhsValue)});
    } break;
    case Type::ACOS: {
        auto lhsValue = stackTopValue(states, rates, variables, stack);

        stack.push(InterpreterStackElement {acos(lhsValue)});
    } break;
    case Type::ATAN: {
        auto lhsValue = stackTopValue(states, rates, variables, stack);

        stack.push(InterpreterStackElement {atan(lhsValue)});
    } break;
    case Type::ASEC: {
        auto lhsValue = stackTopValue(states, rates, variables, stack);

        stack.push(InterpreterStackElement {acos(1.0 / lhsValue)});
    } break;
    case Type::ACSC: {
        auto lhsValue = stackTopValue(states, rates, variables, stack);

        stack.push(InterpreterStackElement {asin(1.0 / lhsValue)});
    } break;
    case Type::ACOT: {
        auto lhsValue = stackTopValue(states, rates, variables, stack);

        stack.push(InterpreterStackElement {atan(1.0 / lhsValue)});
    } break;
    case Type::ASINH: {
        auto lhsValue = stackTopValue(states, rates, variables, stack);

        stack.push(InterpreterStackElement {asinh(lhsValue)});
    } break;
    case Type::ACOSH: {
        auto lhsValue = stackTopValue(states, rates, variables, stack);

        stack.push(InterpreterStackElement {acosh(lhsValue)});
    } break;
    case Type::ATANH: {
        auto lhsValue = stackTopValue(states, rates, variables, stack);

        stack.push(InterpreterStackElement {atanh(lhsValue)});
    } break;
    case Type::ASECH: {
        auto lhsValue = stackTopValue(states, rates, variables, stack);

        stack.push(InterpreterStackElement {acosh(1.0 / lhsValue)});
    } break;
    case Type::ACSCH: {
        auto lhsValue = stackTopValue(states, rates, variables, stack);

        stack.push(InterpreterStackElement {asinh(1.0 / lhsValue)});
    } break;
    case Type::ACOTH: {
        auto lhsValue = stackTopValue(states, rates, variables, stack);

        stack.push(InterpreterStackElement {atanh(1.0 / lhsValue)});
    } break;

        // Piecewise statement.

    case Type::PIECEWISE: {
        auto condValue = stackTopValue(states, rates, variables, stack);
        auto rhsValue = stackTopValue(states, rates, variables, stack);
        auto lhsValue = stackTopValue(states, rates, variables, stack);

        stack.push(InterpreterStackElement {condValue ? lhsValue : rhsValue});
    } break;

        // Token elements.

    case Type::VOI:
        stack.push(InterpreterStackElement {voi});

        break;
    case Type::STATE:
        stack.push(InterpreterStackElement {InterpreterStackElement::Type::STATE, mIndex});

        break;
    case Type::RATE:
        stack.push(InterpreterStackElement {InterpreterStackElement::Type::RATE, mIndex});

        break;
    case Type::VARIABLE:
        stack.push(InterpreterStackElement {InterpreterStackElement::Type::VARIABLE, mIndex});

        break;
    case Type::NUMBER:
        stack.push(InterpreterStackElement {mValue});

        break;

        // Constants.

    case Type::TRUE:
        stack.push(InterpreterStackElement {1.0});

        break;
    case Type::FALSE:
        stack.push(InterpreterStackElement {0.0});

        break;
    case Type::E:
        stack.push(InterpreterStackElement {M_E});

        break;
    case Type::PI:
        stack.push(InterpreterStackElement {M_PI});

        break;
    case Type::INF: {
        static const auto INF = std::numeric_limits<double>::infinity();

        stack.push(InterpreterStackElement {INF});
    } break;
    case Type::NAN: {
        static const auto NAN = std::numeric_limits<double>::quiet_NaN();

        stack.push(InterpreterStackElement {NAN});
    } break;
    default: { // Type::EXTERNAL:
        //---GRY--- JUST RETURN NAN FOR NOW.

        assert(mType == Type::EXTERNAL);

        static const auto NAN = std::numeric_limits<double>::quiet_NaN();

        stack.push(InterpreterStackElement {NAN});
    } break;
    }
}

InterpreterRpnStatement::InterpreterRpnStatement(Type type)
    : mPimpl(new InterpreterRpnStatementImpl(type))
{
}

InterpreterRpnStatement::InterpreterRpnStatement(const AnalyserVariablePtr &variable, bool rate)
    : mPimpl(new InterpreterRpnStatementImpl(variable, rate))
{
}

InterpreterRpnStatement::InterpreterRpnStatement(double value)
    : mPimpl(new InterpreterRpnStatementImpl(value))
{
}

InterpreterRpnStatement::InterpreterRpnStatement(size_t externalIndex)
    : mPimpl(new InterpreterRpnStatementImpl(externalIndex))
{
}

InterpreterRpnStatement::~InterpreterRpnStatement()
{
    delete mPimpl;
}

InterpreterRpnStatementPtr InterpreterRpnStatement::create(Type type) noexcept
{
    return InterpreterRpnStatementPtr {new InterpreterRpnStatement {type}};
}

InterpreterRpnStatementPtr InterpreterRpnStatement::create(const AnalyserVariablePtr &variable, bool rate) noexcept
{
    return InterpreterRpnStatementPtr {new InterpreterRpnStatement {variable, rate}};
}

InterpreterRpnStatementPtr InterpreterRpnStatement::create(double value) noexcept
{
    return InterpreterRpnStatementPtr {new InterpreterRpnStatement {value}};
}

InterpreterRpnStatementPtr InterpreterRpnStatement::create(size_t externalIndex) noexcept
{
    return InterpreterRpnStatementPtr {new InterpreterRpnStatement {externalIndex}};
}

void InterpreterRpnStatement::evaluate(double voi, double *states, double *rates, double *variables,
                                       std::stack<InterpreterStackElement> &stack) const
{
    mPimpl->evaluate(voi, states, rates, variables, stack);
}

} // namespace libcellml

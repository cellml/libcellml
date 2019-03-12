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

#include "operatorlibrary.h"

namespace libcellml {

namespace operators {

BinaryOperator::BinaryOperator() :
    mArg1(RepresentablePtr()),
    mArg2(RepresentablePtr())
{}

ArithmeticOperator::ArithmeticOperator(std::string op) :
    BinaryOperator(),
    mOp(op)
{}

std::string ArithmeticOperator::repr()
{
    return "(" + mArg1->repr() + " " + mOp + " " + mArg2->repr() + ")";
}

Addition::Addition() :
    ArithmeticOperator(std::string("+"))
{}

Subtraction::Subtraction() :
    ArithmeticOperator(std::string("-"))
{}

Multiplication::Multiplication() :
    ArithmeticOperator(std::string("*"))
{}

Division::Division() :
    ArithmeticOperator(std::string("/"))
{}

And::And() :
    ArithmeticOperator(std::string("&&"))
{}

Or::Or() :
    ArithmeticOperator(std::string("||"))
{}

Less::Less() :
    ArithmeticOperator(std::string("<"))
{}

LessOrEqual::LessOrEqual() :
    ArithmeticOperator(std::string("<="))
{}

GreaterOrEqual::GreaterOrEqual() :
    ArithmeticOperator(std::string(">="))
{}

Greater::Greater() :
    ArithmeticOperator(std::string(">"))
{}

Power::Power() :
    BinaryOperator()
{}

std::string Power::repr()
{
    return "std::pow(" + mArg1->repr() + ", " + mArg2->repr() + ")";
}

UnaryOperator::UnaryOperator() :
    mArg(RepresentablePtr())
{}

Positive::Positive() :
    UnaryOperator()
{}

std::string Positive::repr()
{
    return "+(" + mArg->repr() + ")";
}

Negative::Negative() :
    UnaryOperator()
{}

std::string Negative::repr()
{
    return "-(" + mArg->repr() + ")";
}

Not::Not() :
    UnaryOperator()
{}

std::string Not::repr()
{
    return "!(" + mArg->repr() + ")";
}

StdOperator::StdOperator(std::string fun) :
    UnaryOperator(),
    fun(fun)
{}

std::string StdOperator::repr()
{
    return "std::" + fun + "(" + mArg->repr() + ")";
}

AbsoluteValue::AbsoluteValue() :
    StdOperator(std::string("abs"))
{}

Sine::Sine() :
    StdOperator(std::string("sin"))
{}

Cosine::Cosine() :
    StdOperator(std::string("cos"))
{}

Floor::Floor() :
    StdOperator(std::string("floor"))
{}

Variable::Variable(std::string name) : name(name)
{}

std::string Variable::repr()
{
    return name;
}

Constant::Constant (double val) : value(val)
{}

std::string Constant::repr()
{
    std::ostringstream oss;
    oss << std::setprecision(std::numeric_limits<double>::max_digits10) << value;
    return oss.str();
}

Derivative::Derivative (std::string variableName) :
    variableName(variableName)
{}

std::string Derivative::repr()
{
    return "D" + variableName;
}

Equation::Equation() :
    BinaryOperator()
{}

std::string Equation::repr()
{
    return mArg1->repr() + " = " + mArg2->repr();
}

}

}

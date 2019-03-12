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
    std::ostringstream oss;
    oss << "(" << mArg1->repr()
        << " " << mOp << " "
        << mArg2->repr() << ")";
    return oss.str();
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
    std::ostringstream oss;
    oss << "std::pow(" << mArg1->repr() << ", " << mArg2->repr() << ")";
    return oss.str();
}

UnaryOperator::UnaryOperator() :
    mArg(RepresentablePtr())
{}

Positive::Positive() :
    UnaryOperator()
{}

std::string Positive::repr()
{
    std::ostringstream oss;
    oss << "+" << "(" << mArg->repr() << ")";
    return oss.str();
}

Negative::Negative() :
    UnaryOperator()
{}

std::string Negative::repr()
{
    std::ostringstream oss;
    oss << "-" << "(" << mArg->repr() << ")";
    return oss.str();
}

Not::Not() :
    UnaryOperator()
{}

std::string Not::repr()
{
    std::ostringstream oss;
    oss << "!" << "(" << mArg->repr() << ")";
    return oss.str();
}

STDOperator::STDOperator(std::string fun) :
    UnaryOperator(),
    fun(fun)
{}

std::string STDOperator::repr()
{
    std::ostringstream oss;
    oss << "std::" << fun << "(" << mArg->repr() << ")";
    return oss.str();
}

AbsoluteValue::AbsoluteValue() :
    STDOperator(std::string("abs"))
{}

Sine::Sine() :
    STDOperator(std::string("sin"))
{}

Cosine::Cosine() :
    STDOperator(std::string("cos"))
{}

Floor::Floor() :
    STDOperator(std::string("floor"))
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
    oss << std::setprecision(16) << value;
    return oss.str();
}

Derivative::Derivative (std::string variableName) :
    variableName(variableName)
{}

std::string Derivative::repr()
{
    std::ostringstream oss;
    oss << "D" << variableName;
    return oss.str();
}

Equation::Equation() :
    BinaryOperator()
{}

std::string Equation::repr()
{
    std::ostringstream oss;
    oss << mArg1->repr();
    oss << " = ";
    oss << mArg2->repr();
    return oss.str();
}

}

}

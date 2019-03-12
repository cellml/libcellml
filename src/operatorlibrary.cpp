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

#include <limits>

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
    ArithmeticOperator("+")
{}

Subtraction::Subtraction() :
    ArithmeticOperator("-")
{}

Multiplication::Multiplication() :
    ArithmeticOperator("*")
{}

Division::Division() :
    ArithmeticOperator("/")
{}

And::And() :
    ArithmeticOperator("&&")
{}

Or::Or() :
    ArithmeticOperator("||")
{}

Less::Less() :
    ArithmeticOperator("<")
{}

LessOrEqual::LessOrEqual() :
    ArithmeticOperator("<=")
{}

GreaterOrEqual::GreaterOrEqual() :
    ArithmeticOperator(">=")
{}

Greater::Greater() :
    ArithmeticOperator(">")
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

StdOperator::StdOperator(std::string function) :
    UnaryOperator(),
    mFunction(function)
{}

std::string StdOperator::repr()
{
    return "std::" + mFunction + "(" + mArg->repr() + ")";
}

AbsoluteValue::AbsoluteValue() :
    StdOperator("abs")
{}

Sine::Sine() :
    StdOperator("sin")
{}

Cosine::Cosine() :
    StdOperator("cos")
{}

Floor::Floor() :
    StdOperator("floor")
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
    // Use the C++03 way of converting a double to a std::string rather than the
    // C++11 way (i.e. std::to_string()). Indeed, the latter has too many
    // limitations (e.g. 23.43 ---> 23.430000, 1e-09 ---> 0.000000), as can be
    // seen at https://en.cppreference.com/w/cpp/string/basic_string/to_string.
    std::ostringstream oss;
    oss << std::setprecision(std::numeric_limits<double>::max_digits10) << value;
    return oss.str();
}

Derivative::Derivative (std::string variableName) :
    mVariableName(variableName)
{}

std::string Derivative::repr()
{
    return "D" + mVariableName;
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

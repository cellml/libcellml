#include "libcellml/operatorlibrary.h"

namespace libcellml {

namespace operators {

BinaryOperator::BinaryOperator() :
    arg1(std::shared_ptr<Representable>()),
    arg2(std::shared_ptr<Representable>())
{}

ArithmeticOperator::ArithmeticOperator(std::string opr) :
    BinaryOperator(),
    operatorRepresentation(opr)
{}

std::string ArithmeticOperator::repr()
{
    std::ostringstream oss;
    oss << "(" << arg1->repr();
    oss << " " << operatorRepresentation << " ";
    oss << arg2->repr() << ")";
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
    oss << "std::pow(" << arg1->repr() << ", " << arg2->repr() << ")";
    return oss.str();
}

UnaryOperator::UnaryOperator() :
    arg(std::shared_ptr<Representable>())
{}

Positive::Positive() :
    UnaryOperator()
{}

std::string Positive::repr()
{
    std::ostringstream oss;
    oss << "+" << "(" << arg->repr() << ")";
    return oss.str();
}

Negative::Negative() :
    UnaryOperator()
{}

std::string Negative::repr()
{
    std::ostringstream oss;
    oss << "-" << "(" << arg->repr() << ")";
    return oss.str();
}

Not::Not() :
    UnaryOperator()
{}

std::string Not::repr()
{
    std::ostringstream oss;
    oss << "!" << "(" << arg->repr() << ")";
    return oss.str();
}

STDOperator::STDOperator(std::string fun) :
    UnaryOperator(),
    fun(fun)
{}

std::string STDOperator::repr()
{
    std::ostringstream oss;
    oss << "std::" << fun << "(" << arg->repr() << ")";
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
    oss << arg1->repr();
    oss << " = ";
    oss << arg2->repr();
    return oss.str();
}

}

}

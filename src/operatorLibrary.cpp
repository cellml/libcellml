#include "libcellml/operatorLibrary.h"

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

}

}

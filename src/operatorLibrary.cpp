#include "libcellml/operatorLibrary.h"

BinaryOperator::BinaryOperator() :
    arg1(std::shared_ptr<Representable>()),
    arg2(std::shared_ptr<Representable>())
{}

BinaryOperator::BinaryOperator(std::shared_ptr<Representable> arg1,
        std::shared_ptr<Representable> arg2) :
    arg1(arg1),
    arg2(arg2)
{}

ArithmeticOperator::ArithmeticOperator(std::string opr) :
    BinaryOperator(),
    operatorRepresentation(opr)
{}

ArithmeticOperator::ArithmeticOperator(std::shared_ptr<Representable> arg1,
        std::shared_ptr<Representable> arg2,
        std::string opr) :
    BinaryOperator(arg1,arg2),
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

Addition::Addition(std::shared_ptr<Representable> arg1,
        std::shared_ptr<Representable> arg2) :
    ArithmeticOperator(arg1,arg2,std::string("+"))
{}

Subtraction::Subtraction() :
    ArithmeticOperator(std::string("-"))
{}

Subtraction::Subtraction(std::shared_ptr<Representable> arg1,
        std::shared_ptr<Representable> arg2) :
    ArithmeticOperator(arg1,arg2,std::string("-"))
{}

Multiplication::Multiplication() :
    ArithmeticOperator(std::string("*"))
{}

Multiplication::Multiplication(std::shared_ptr<Representable> arg1,
        std::shared_ptr<Representable> arg2) :
    ArithmeticOperator(arg1,arg2,std::string("*"))
{}

Division::Division() :
    ArithmeticOperator(std::string("/"))
{}

Division::Division(std::shared_ptr<Representable> arg1,
        std::shared_ptr<Representable> arg2) :
    ArithmeticOperator(arg1,arg2,std::string("/"))
{}

Power::Power(std::shared_ptr<Representable> b,
        std::shared_ptr<Representable> e) :
    BinaryOperator(b,e)
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

UnaryOperator::UnaryOperator(std::shared_ptr<Representable> arg) :
    arg(arg)
{}

STDOperator::STDOperator(std::string fun) :
    UnaryOperator(),
    fun(fun)
{}

STDOperator::STDOperator(std::shared_ptr<Representable> arg,
        std::string fun) :
    UnaryOperator(arg),
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

AbsoluteValue::AbsoluteValue(std::shared_ptr<Representable> arg) :
    STDOperator(arg,std::string("abs"))
{}

Sine::Sine() :
    STDOperator(std::string("sin"))
{}

Sine::Sine(std::shared_ptr<Representable> arg) :
    STDOperator(arg,std::string("sin"))
{}

Cosine::Cosine() :
    STDOperator(std::string("cos"))
{}

Cosine::Cosine(std::shared_ptr<Representable> arg) :
    STDOperator(arg,std::string("cos"))
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

#include <iomanip>
#include <memory>
#include <sstream>
#include <string>

namespace libcellml {

namespace operators {

class Representable
{
public:
    virtual std::string repr() = 0;
};

class BinaryOperator : public Representable
{
public:
    BinaryOperator();
    BinaryOperator(std::shared_ptr<Representable> arg1,
            std::shared_ptr<Representable> arg2);

    std::shared_ptr<Representable> getArg1() const {return arg1;}
    void setArg1(const std::shared_ptr<Representable> a1) {arg1 = a1;}
    std::shared_ptr<Representable> getArg2() const {return arg2;}
    void setArg2(const std::shared_ptr<Representable> a2) {arg2 = a2;}

protected:
    std::shared_ptr<Representable> arg1;
    std::shared_ptr<Representable> arg2;
};

class ArithmeticOperator : public BinaryOperator
{
public:
    ArithmeticOperator(std::string opr);
    ArithmeticOperator(std::shared_ptr<Representable> arg1,
            std::shared_ptr<Representable> arg2,
            std::string opr);

    virtual std::string repr() override;

private:
    std::string operatorRepresentation;
};

class Addition : public ArithmeticOperator
{
public:
    Addition();
    Addition(std::shared_ptr<Representable> arg1,
            std::shared_ptr<Representable> arg2);
};

class Subtraction : public ArithmeticOperator
{
public:
    Subtraction();
    Subtraction(std::shared_ptr<Representable> arg1,
            std::shared_ptr<Representable> arg2);
};

class Multiplication : public ArithmeticOperator
{
public:
    Multiplication();
    Multiplication(std::shared_ptr<Representable> arg1,
            std::shared_ptr<Representable> arg2);
};

class Division : public ArithmeticOperator
{
public:
    Division();
    Division(std::shared_ptr<Representable> arg1,
            std::shared_ptr<Representable> arg2);
};

class Power : public BinaryOperator
{
public:
    Power(std::shared_ptr<Representable> b,
            std::shared_ptr<Representable> e);

    virtual std::string repr() override;
};

class UnaryOperator : public Representable
{
public:
    UnaryOperator();
    UnaryOperator(std::shared_ptr<Representable> arg);

    std::shared_ptr<Representable> getArg() const {return arg;}
    void setArg(const std::shared_ptr<Representable> a) {arg = a;}

protected:
    std::shared_ptr<Representable> arg;
};

class STDOperator : public UnaryOperator
{
public:
    STDOperator(std::string fun);
    STDOperator(std::shared_ptr<Representable> arg,
            std::string fun);

    virtual std::string repr() override;

private:
    std::string fun;
};

class AbsoluteValue : public STDOperator
{
public:
    AbsoluteValue();
    AbsoluteValue(std::shared_ptr<Representable> arg);
};

class Sine : public STDOperator
{
public:
    Sine();
    Sine(std::shared_ptr<Representable> arg);
};

class Cosine : public STDOperator
{
public:
    Cosine();
    Cosine(std::shared_ptr<Representable> arg);
};

class Variable : public Representable
{
public:
    Variable() = default;
    Variable(std::string name);

    virtual std::string repr() override;

private:
    std::string name;
};

class Constant : public Representable
{
public:
    Constant() = default;
    Constant (double val);

    virtual std::string repr() override;

private:
    double value;
};

}

}

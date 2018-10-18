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

    virtual std::string repr() override;

private:
    std::string operatorRepresentation;
};

class Addition : public ArithmeticOperator
{
public:
    Addition();
};

class Subtraction : public ArithmeticOperator
{
public:
    Subtraction();
};

class Multiplication : public ArithmeticOperator
{
public:
    Multiplication();
};

class Division : public ArithmeticOperator
{
public:
    Division();
};

class Power : public BinaryOperator
{
public:
    Power();

    virtual std::string repr() override;
};

class UnaryOperator : public Representable
{
public:
    UnaryOperator();

    std::shared_ptr<Representable> getArg() const {return arg;}
    void setArg(const std::shared_ptr<Representable> a) {arg = a;}

protected:
    std::shared_ptr<Representable> arg;
};

class STDOperator : public UnaryOperator
{
public:
    STDOperator(std::string fun);

    virtual std::string repr() override;

private:
    std::string fun;
};

class AbsoluteValue : public STDOperator
{
public:
    AbsoluteValue();
};

class Sine : public STDOperator
{
public:
    Sine();
};

class Cosine : public STDOperator
{
public:
    Cosine();
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

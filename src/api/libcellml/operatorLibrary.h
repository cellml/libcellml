#include <iomanip>
#include <memory>
#include <sstream>
#include <string>

namespace libcellml {

namespace operators {

class Representable
{
public:
    virtual ~Representable() = default;
    virtual std::string repr() = 0;
};

class BinaryOperator : public Representable
{
public:
    BinaryOperator();
    BinaryOperator(std::shared_ptr<Representable> arg1,
            std::shared_ptr<Representable> arg2);
    virtual ~BinaryOperator() = default;

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
    virtual ~ArithmeticOperator() = default;

    virtual std::string repr() override;

private:
    std::string operatorRepresentation;
};

class Addition : public ArithmeticOperator
{
public:
    Addition();
    virtual ~Addition() = default;
};

class Subtraction : public ArithmeticOperator
{
public:
    Subtraction();
    virtual ~Subtraction() = default;
};

class Multiplication : public ArithmeticOperator
{
public:
    Multiplication();
    virtual ~Multiplication() = default;
};

class Division : public ArithmeticOperator
{
public:
    Division();
    virtual ~Division() = default;
};

class Power : public BinaryOperator
{
public:
    Power();
    virtual ~Power() = default;

    virtual std::string repr() override;
};

class UnaryOperator : public Representable
{
public:
    UnaryOperator();
    virtual ~UnaryOperator() = default;

    std::shared_ptr<Representable> getArg() const {return arg;}
    void setArg(const std::shared_ptr<Representable> a) {arg = a;}

protected:
    std::shared_ptr<Representable> arg;
};

class STDOperator : public UnaryOperator
{
public:
    STDOperator(std::string fun);
    virtual ~STDOperator() = default;

    virtual std::string repr() override;

private:
    std::string fun;
};

class AbsoluteValue : public STDOperator
{
public:
    AbsoluteValue();
    virtual ~AbsoluteValue() = default;
};

class Sine : public STDOperator
{
public:
    Sine();
    virtual ~Sine() = default;
};

class Cosine : public STDOperator
{
public:
    Cosine();
    virtual ~Cosine() = default;
};

class Variable : public Representable
{
public:
    Variable(std::string name);
    virtual ~Variable() = default;

    virtual std::string repr() override;

private:
    std::string name;
};

class Constant : public Representable
{
public:
    Constant (double val);
    virtual ~Constant() = default;

    virtual std::string repr() override;

private:
    double value;
};

}

}

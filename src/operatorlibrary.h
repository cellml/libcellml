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

#include <iomanip>
#include <memory>
#include <sstream>
#include <string>

namespace libcellml {

/**
 * @brief A namespace for operators supported by @c Generator objects
 *
 * The main reason to have a separate namespace here is that the classes defined
 * in here are auxiliary classes for the implementation of @c Generator and it
 * is unlikely that they will be used in other parts of the code, so it seems
 * natural to provide logical grouping for them.
 * Also, they have quite common names and having a separate namespace reduces
 * the risk for names clashing. For example, this namespace resolves a class
 * between @c libcellml::Variable and what is now @c
 * libcellml::operators::Variable.
 */
namespace operators {

class Representable; /**< Forward declaration of the internal Representable class. */
typedef std::shared_ptr<Representable> RepresentablePtr; /**< Type definition for shared representable pointer. */

/* @brief A common base class for every object that can be represented by a
 * @c Generator instance.
 *
 * @c Representable instances are characterized by having a pure virtual method
 * called @c repr, that takes care of representing the object in the generated
 * code.
 */
class Representable
{
public:
    virtual ~Representable() = default;
    virtual std::string repr() = 0;
};

/**
 * @brief A class representing any operator with arity equal to two.
 *
 * A @c BinaryOperator is a @Representable in which you can plug two arguments.
 * Its interface consists mainly of access methods.
 *
 * The idea behind this and all other classes that have pluggable arguments is
 * to create an evaluation tree for the formula described in the input MathML
 * string. After building this intermediate representation, the idea is to use
 * polymorphism to call @c repr() of the root node that will then recursively
 * call the same method of its arguments, generating the full representation of
 * the given tree.
 */
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

/**
 * @brief A class representing arithmetic operations.
 *
 * An arithmetic operator is a binary operator whose representation consists of
 * the representation of its arguments separated by the representation of the
 * operator.
 */
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

/**
 * @brief A class representing the logical and.
 *
 * Binary logical operators satisfy the requirements of arithmetic operators,
 * thus it makes sense to re-use the code even though they are not arithmetic
 * operators in the mathematical sense.
 */
class And : public ArithmeticOperator
{
public:
    And();
    virtual ~And() = default;
};

/**
 * @brief A class representing the logical or.
 *
 * Binary logical operators satisfy the requirements of arithmetic operators,
 * thus it makes sense to re-use the code even though they are not arithmetic
 * operators in the mathematical sense.
 */
class Or : public ArithmeticOperator
{
public:
    Or();
    virtual ~Or() = default;
};

/**
 * @brief A class representing the comparison <.
 *
 * Binary comparison operators satisfy the requirements of arithmetic operators,
 * thus it makes sense to re-use the code even though they are not arithmetic
 * operators in the mathematical sense.
 */
class Less : public ArithmeticOperator
{
public:
    Less();
    virtual ~Less() = default;
};

/**
 * @brief A class representing the comparison <=.
 *
 * Binary comparison operators satisfy the requirements of arithmetic operators,
 * thus it makes sense to re-use the code even though they are not arithmetic
 * operators in the mathematical sense.
 */
class LessOrEqual : public ArithmeticOperator
{
public:
    LessOrEqual();
    virtual ~LessOrEqual() = default;
};

/**
 * @brief A class representing the comparison >=.
 *
 * Binary comparison operators satisfy the requirements of arithmetic operators,
 * thus it makes sense to re-use the code even though they are not arithmetic
 * operators in the mathematical sense.
 */
class GreaterOrEqual : public ArithmeticOperator
{
public:
    GreaterOrEqual();
    virtual ~GreaterOrEqual() = default;
};

/**
 * @brief A class representing the comparison >.
 *
 * Binary comparison operators satisfy the requirements of arithmetic operators,
 * thus it makes sense to re-use the code even though they are not arithmetic
 * operators in the mathematical sense.
 */
class Greater : public ArithmeticOperator
{
public:
    Greater();
    virtual ~Greater() = default;
};

class Power : public BinaryOperator
{
public:
    Power();
    virtual ~Power() = default;

    virtual std::string repr() override;
};

/**
 * @brief A class representing any operator with arity equal to one.
 *
 * A @c UnaryOperator is a @Representable in which you can plug one argument.
 * Its interface consists mainly of access methods.
 *
 * The idea behind this and all other classes that have pluggable arguments is
 * to create an evaluation tree for the formula described in the input MathML
 * string. After building this intermediate representation, the idea is to use
 * polymorphism to call @c repr() of the root node that will then recursively
 * call the same method of its arguments, generating the full representation of
 * the given tree.
 */
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

/**
 * @brief A class representing the unary plus operator.
 */
class Positive : public UnaryOperator
{
public:
    Positive();
    virtual ~Positive() = default;

    virtual std::string repr() override;
};

/**
 * @brief A class representing the unary minus operator.
 */
class Negative : public UnaryOperator
{
public:
    Negative();
    virtual ~Negative() = default;

    virtual std::string repr() override;
};

/**
 * @brief A class representing the logical not.
 */
class Not : public UnaryOperator
{
public:
    Not();
    virtual ~Not() = default;

    virtual std::string repr() override;
};

/**
 * @brief A class representing operators from the C++ standard library.
 *
 * An @c STDOperator is a unary operator whose representation consists of
 * the string @c std:: followed by the representation of the operator and a
 * single argument between parentheses.
 * Examples include @c std::sin, @c cos, @c abs, @c tan...
 */
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

class Floor : public STDOperator
{
public:
    Floor();
    virtual ~Floor() = default;
};

/**
 * @brief A class representing variables in an expression.
 */
class Variable : public Representable
{
public:
    Variable(std::string name);
    virtual ~Variable() = default;

    virtual std::string repr() override;

private:
    std::string name;
};

/**
 * @brief A class representing constants in an expression.
 */
class Constant : public Representable
{
public:
    Constant (double val);
    virtual ~Constant() = default;

    virtual std::string repr() override;

private:
    double value;
};

/**
 * @brief A class representing the derivative of a variable.
 */
class Derivative : public Representable
{
public:
    Derivative(std::string variableName);
    virtual ~Derivative() = default;

    virtual std::string repr() override;

private:
    std::string variableName;
};

/**
 * @brief A class representing an equation (or assignment) between two
 * quantities.
 */
class Equation : public BinaryOperator
{
public:
    Equation();
    virtual ~Equation() = default;

    virtual std::string repr() override;
};

}

}

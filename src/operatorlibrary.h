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

    RepresentablePtr getArg1() const { return mArg1; }
    void setArg1(const RepresentablePtr arg1) { mArg1 = arg1; }
    RepresentablePtr getArg2() const { return mArg2; }
    void setArg2(const RepresentablePtr arg2) { mArg2 = arg2; }

protected:
    RepresentablePtr mArg1;
    RepresentablePtr mArg2;
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
    ArithmeticOperator(std::string op);

    std::string repr() override;

private:
    std::string mOp;
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
};

class Power : public BinaryOperator
{
public:
    Power();

    std::string repr() override;
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

    RepresentablePtr getArg() const { return mArg; }
    void setArg(const RepresentablePtr arg) { mArg = arg; }

protected:
    RepresentablePtr mArg;
};

/**
 * @brief A class representing the unary plus operator.
 */
class Positive : public UnaryOperator
{
public:
    Positive();

    std::string repr() override;
};

/**
 * @brief A class representing the unary minus operator.
 */
class Negative : public UnaryOperator
{
public:
    Negative();

    std::string repr() override;
};

/**
 * @brief A class representing the logical not.
 */
class Not : public UnaryOperator
{
public:
    Not();

    std::string repr() override;
};

/**
 * @brief A class representing operators from the C++ standard library.
 *
 * An @c StdOperator is a unary operator whose representation consists of
 * the string @c std:: followed by the representation of the operator and a
 * single argument between parentheses.
 * Examples include @c std::sin, @c cos, @c abs, @c tan...
 */
class StdOperator : public UnaryOperator
{
public:
    StdOperator(std::string function);

    std::string repr() override;

private:
    std::string mFunction;
};

class AbsoluteValue : public StdOperator
{
public:
    AbsoluteValue();
};

class Sine : public StdOperator
{
public:
    Sine();
};

class Cosine : public StdOperator
{
public:
    Cosine();
};

class Floor : public StdOperator
{
public:
    Floor();
};

/**
 * @brief A class representing variables in an expression.
 */
class Variable : public Representable
{
public:
    Variable(std::string name);

    std::string repr() override;

private:
    std::string mName;
};

/**
 * @brief A class representing constants in an expression.
 */
class Constant : public Representable
{
public:
    Constant (double value);

    std::string repr() override;

private:
    double mValue;
};

/**
 * @brief A class representing the derivative of a variable.
 */
class Derivative : public Representable
{
public:
    Derivative(std::string variableName);

    std::string repr() override;

private:
    std::string mVariableName;
};

/**
 * @brief A class representing an equation (or assignment) between two
 * quantities.
 */
class Equation : public BinaryOperator
{
public:
    Equation();

    std::string repr() override;
};

}

}

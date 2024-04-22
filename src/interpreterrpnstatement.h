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

#pragma once

#include <memory>
#include <stack>

#include "libcellml/analyservariable.h"

#include "interpreter_p.h"

#include "libcellml/undefines.h"

namespace libcellml {

/**
 * @brief The InterpreterRpnStatement class.
 *
 * The InterpreterRpnStatement class is for representing a CellML Interpreter Statement.
 */
class InterpreterRpnStatement
{
public:
    /**
     * @brief The type of a statement.
     *
     * The type of a statement, i.e. whether it is an equality type, a relational or a logical operator, an arithmetic
     * operator, a calculus element, a trigonometric operator, a piecewise statement, a token element, a qualifier
     * element, or a constant.
     */
    enum class Type
    {
        // Equality.

        EQUALITY, /**< The equality operator. */

        // Relational and logical operators.

        EQ, /**< The equal to operator. */
        NEQ, /**< The not equal to operator. */
        LT, /**< The less than operator. */
        LEQ, /**< The less than or equal to operator. */
        GT, /**< The greater than operator. */
        GEQ, /**< The greater than or equal to operator. */
        AND, /**< The and operator. */
        OR, /**< The or operator. */
        XOR, /**< The exclusive or operator. */
        NOT, /**< The not operator. */

        // Arithmetic operators.

        PLUS, /**< The plus operator. */
        UNARY_MINUS, /**< The unary minus operator. */
        MINUS, /**< The minus operator. */
        TIMES, /**< The times operator. */
        DIVIDE, /**< The divide operator. */
        POWER, /**< The power operator. */
        SQUARE_ROOT, /**< The square root operator. */
        SQUARE, /**< The square operator. */
        ABS, /**< The absolute value function. */
        EXP, /**< The exponential function. */
        LN, /**< The natural logarithm function. */
        LOG, /**< The common logarithm function. */
        CEILING, /**< The ceiling function. */
        FLOOR, /**< The floor function. */
        MIN, /**< The minimum function. */
        MAX, /**< The maximum function. */
        REM, /**< The remainder function. */

        // Trigonometric operators.

        SIN, /**< The sine function. */
        COS, /**< The cosine function. */
        TAN, /**< The tangent function. */
        SEC, /**< The secant function. */
        CSC, /**< The cosecant function. */
        COT, /**< The cotangent function. */
        SINH, /**< The hyperbolic sine function. */
        COSH, /**< The hyperbolic cosine function. */
        TANH, /**< The hyperbolic tangent function. */
        SECH, /**< The hyperbolic secant function. */
        CSCH, /**< The hyperbolic cosecant function. */
        COTH, /**< The hyperbolic cotangent function. */
        ASIN, /**< The arc sine function. */
        ACOS, /**< The arc cosine function. */
        ATAN, /**< The arc tangent function. */
        ASEC, /**< The arc secant function. */
        ACSC, /**< The arc cosecant function. */
        ACOT, /**< The arc cotangent function. */
        ASINH, /**< The arc hyperbolic sine function. */
        ACOSH, /**< The arc hyperbolic cosine function. */
        ATANH, /**< The arc hyperbolic tangent function. */
        ASECH, /**< The arc hyperbolic secant function. */
        ACSCH, /**< The arc hyperbolic cosecant function. */
        ACOTH, /**< The arc hyperbolic cotangent function. */

        // Piecewise statement.

        PIECEWISE, /**< The "piecewise" statement. */

        // Token elements.

        VOI, /**< The variable of integration. */
        STATE, /**< A state variable. */
        RATE, /**< A rate variable. */
        VARIABLE, /**< A variable. */
        NUMBER, /**< A number. */

        // Qualifier elements.

        DEGREE, /**< The degree of a root operator (it is only used when its value is not 2). */
        LOGBASE, /**< The base with respect to which the logarithm is taken. */
        BVAR, /**< The bound variable of a differential equation. */

        // Constants.

        TRUE, /**< The "true" boolean. */
        FALSE, /**< The "false" boolean. */
        E, /**< Euler's number. */
        PI, /**< The π constant. */
        INF, /**< The infinity value. */
        NAN, /**< The not-a-number value. */

        // Miscellaneous.

        EXTERNAL /**< An external variable. */
    };

    ~InterpreterRpnStatement(); /**< Destructor, @private. */
    InterpreterRpnStatement(const InterpreterRpnStatement &rhs) = delete; /**< Copy constructor, @private. */
    InterpreterRpnStatement(InterpreterRpnStatement &&rhs) noexcept = delete; /**< Move constructor, @private. */
    InterpreterRpnStatement &operator=(InterpreterRpnStatement rhs) = delete; /**< Assignment operator, @private. */

    /**
     * @brief Create an @ref InterpreterRpnStatement object.
     *
     * Factory method to create an @ref InterpreterRpnStatement for an element of the given type. Create such an
     * interpreter statement with::
     *
     * @code
     *   auto InterpreterRpnStatement = libcellml::InterpreterRpnStatement::create(type);
     * @endcode
     *
     * @param type The type of the statement.
     *
     * @return A smart pointer to an @ref InterpreterRpnStatement object.
     */
    static InterpreterRpnStatementPtr create(Type type) noexcept;

    /**
     * @brief Create an @ref InterpreterRpnStatement object.
     *
     * Factory method to create an @ref InterpreterRpnStatement for a CI element. Create such an interpreter statement
     * with::
     *
     * @code
     *   auto InterpreterRpnStatement = libcellml::InterpreterRpnStatement::create(variable, rate);
     * @endcode
     *
     * @param variable The variable associated with the CI element.
     * @param rate Whether the variable is a rate.
     *
     * @return A smart pointer to an @ref InterpreterRpnStatement object.
     */
    static InterpreterRpnStatementPtr create(const AnalyserVariablePtr &variable, bool rate = false) noexcept;

    /**
     * @brief Create an @ref InterpreterRpnStatement object.
     *
     * Factory method to create an @ref InterpreterRpnStatement for a CN element. Create such an interpreter statement
     * with::
     *
     * @code
     *   auto InterpreterRpnStatement = libcellml::InterpreterRpnStatement::create(value);
     * @endcode
     *
     * @param value The value associated with the CN element.
     *
     * @return A smart pointer to an @ref InterpreterRpnStatement object.
     */
    static InterpreterRpnStatementPtr create(double value) noexcept;

    /**
     * @brief Create an @ref InterpreterRpnStatement object.
     *
     * Factory method to create an @ref InterpreterRpnStatement for an external variable. Create such an interpreter
     * statement with::
     *
     * @code
     *   auto InterpreterRpnStatement = libcellml::InterpreterRpnStatement::create(externalIndex);
     * @endcode
     *
     * @param externalIndex
     *
     * @return A smart pointer to an @ref InterpreterRpnStatement object.
     */
    static InterpreterRpnStatementPtr create(size_t externalIndex) noexcept;

#ifdef DEBUG
    /**
     * @brief Get the type of the statement.
     *
     * Return the type of the statement.
     *
     * @return The type of the statement.
     */
    Type type() const;

    /**
     * @brief Get the variable associated with the statement.
     *
     * Return the variable associated with the statement.
     *
     * @return The variable associated with the statement.
     */
    AnalyserVariablePtr variable() const;

    /**
     * @brief Get the value associated with the statement.
     *
     * Return the value associated with the statement.
     *
     * @return The value associated with the statement.
     */
    double value() const;

    /**
     * @brief Get the external index associated with the statement.
     *
     * Return the external index associated with the statement.
     *
     * @return The external index associated with the statement.
     */
    size_t externalIndex() const;
#endif

    /**
     * @brief Evaluate the statement.
     *
     * Evaluate the statement using the given variable of integration and arrays of states, rates, and variables.
     *
     * @param voi The variable of integration.
     * @param states The array of states.
     * @param rates The array of rates.
     * @param variables The array of variables.
     * @param stack The stack to use for the evaluation.
     */
    void evaluate(double voi, double *states, double *rates, double *variables,
                  std::stack<InterpreterStackElement> &stack) const;

private:
    InterpreterRpnStatement(Type type); /**< Constructor, @private. */
    InterpreterRpnStatement(const AnalyserVariablePtr &variable, bool rate); /**< Constructor, @private. */
    InterpreterRpnStatement(double value); /**< Constructor, @private. */
    InterpreterRpnStatement(size_t externalIndex); /**< Constructor, @private. */

    struct InterpreterRpnStatementImpl;
    InterpreterRpnStatementImpl *mPimpl; /**< Private member to implementation pointer, @private. */
};

} // namespace libcellml

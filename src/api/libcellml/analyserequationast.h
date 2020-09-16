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

#include "libcellml/analyser.h"
#include "libcellml/generator.h"

#ifdef NAN
#    undef NAN
#endif

namespace libcellml {

/**
 * @brief The AnalyserEquationAst class.
 *
 * The AnalyserEquationAst class is for representing an equation abstract syntax
 * tree (AST) in the context of a CellML Analyser.
 */
class LIBCELLML_EXPORT AnalyserEquationAst
{
    friend class Analyser;

public:
    /**
     * @brief The type of a node in an abstract syntax tree (AST).
     *
     * A node in an abstract syntax tree (AST) can be of one of the following
     * types:
     *  - Assignment type:
     *     - ASSIGNMENT: the assignment operator
     *  - Relational and logical operators:
     *    - EQ: the equal to function;
     *    - NEQ: the not equal to function;
     *    - LT: the less than function;
     *    - LEQ: the less than or equal to function;
     *    - GT: the greater than function;
     *    - GEQ: the greater than or equal to function;
     *    - AND: the and function;
     *    - OR: the or function
     *    - XOR: the exclusive or function;
     *    - NOT: the not function;
     *  - Arithmetic operators:
     *    - PLUS: the plus operator;
     *    - MINUS: the minus operator;
     *    - TIMES: the times operator;
     *    - DIVIDE: the divide operator;
     *    - POWER: the power operator;
     *    - ROOT: the root operator;
     *    - ABS: the absolute value function;
     *    - EXP: the exponential function;
     *    - LN: the Napierian logarithm function;
     *    - LOG: the common logarithm function;
     *    - CEILING: the ceiling function;
     *    - FLOOR: the floor function;
     *    - MIN: the minimum function;
     *    - MAX: the maximum function;
     *    - REM: the remainder function;
     *  - Calculus elements:
     *    - DIFF: the differentiation operator;
     *  - Trigonometric operators:
     *    - SIN: the sine function;
     *    - COS: the cosine function;
     *    - TAN: the tangent function;
     *    - SEC: the secant function;
     *    - CSC: the cosecant function;
     *    - COT: the cotangent function;
     *    - SINH: the hyperbolic sine function;
     *    - COSH: the hyperbolic cosine function;
     *    - TANH: the hyperbolic tangent function;
     *    - SECH: the hyperbolic secant function;
     *    - CSCH: the hyperbolic cosecant function;
     *    - COTH: the hyperbolic cotangent function;
     *    - ASIN: the arc sine function;
     *    - ACOS: the arc cosine function;
     *    - ATAN: the arc tangent function;
     *    - ASEC: the arc secant function;
     *    - ACSC: the arc cosecant function;
     *    - ACOT: the arc cotangent function;
     *    - ASINH: the arc hyperbolic sine function;
     *    - ACOSH: the arc hyperbolic cosine function;
     *    - ATANH: the arc hyperbolic tangent function;
     *    - ASECH: the arc hyperbolic secant function;
     *    - ACSCH: the arc hyperbolic cosecant function;
     *    - ACOTH: the arc hyperbolic cotangent function;
     *  - Piecewise statement:
     *    - PIECEWISE: the "piecewise" statement;
     *    - PIECE: the "piece" part of a "piecewise" statement;
     *    - OTHERWISE: the "otherwise" part of a "piecewise" statement;
     *  - Token elements:
     *    - CI: an identifier (i.e. the name of a model variable);
     *    - CN: a number;
     *  - Qualifier elements:
     *    - DEGREE: the degree (or oder) of a differential equation;
     *    - LOGBASE: the base with respect to which the logarithm is taken;
     *    - BVAR: the bound variable of a differential equation;
     *  - Constants:
     *    - TRUE: the "true" boolean;
     *    - FALSE: the "false" boolean;
     *    - E: Euler's number;
     *    - PI: the πconstant;
     *    - INF: the infinity value; or
     *    - NAN: the not-a-number value.
     */
    enum class Type
    {
        // Assignment.

        ASSIGNMENT,

        // Relational and logical operators.

        EQ,
        NEQ,
        LT,
        LEQ,
        GT,
        GEQ,
        AND,
        OR,
        XOR,
        NOT,

        // Arithmetic operators.

        PLUS,
        MINUS,
        TIMES,
        DIVIDE,
        POWER,
        ROOT,
        ABS,
        EXP,
        LN,
        LOG,
        CEILING,
        FLOOR,
        MIN,
        MAX,
        REM,

        // Calculus elements.

        DIFF,

        // Trigonometric operators.

        SIN,
        COS,
        TAN,
        SEC,
        CSC,
        COT,
        SINH,
        COSH,
        TANH,
        SECH,
        CSCH,
        COTH,
        ASIN,
        ACOS,
        ATAN,
        ASEC,
        ACSC,
        ACOT,
        ASINH,
        ACOSH,
        ATANH,
        ASECH,
        ACSCH,
        ACOTH,

        // Piecewise statement.

        PIECEWISE,
        PIECE,
        OTHERWISE,

        // Token elements.

        CI,
        CN,

        // Qualifier elements.

        DEGREE,
        LOGBASE,
        BVAR,

        // Constants.

        TRUE,
        FALSE,
        E,
        PI,
        INF,
        NAN
    };

    ~AnalyserEquationAst(); /**< Destructor */
    AnalyserEquationAst(const AnalyserEquationAst &rhs) = delete; /**< Copy constructor */
    AnalyserEquationAst(AnalyserEquationAst &&rhs) noexcept = delete; /**< Move constructor */
    AnalyserEquationAst &operator=(AnalyserEquationAst rhs) = delete; /**< Assignment operator */

    /**
     * @brief Create an @c AnalyserEquationAst object.
     *
     * Factory method to create an @c AnalyserEquationAst. Create a blank
     * equation AST with::
     *
     * @code
     *   auto ast = libcellml::AnalyserEquationAst::create();
     * @endcode
     *
     * @return A smart pointer to a @c AnalyserEquationAst object.
     */
    static AnalyserEquationAstPtr create() noexcept;

    /**
     * @brief Get the @c Type of this @c AnalyserEquationAst.
     *
     * Return the @c Type of this @c AnalyserEquationAst.
     *
     * @return The @c Type.
     */
    Type type() const;

    /**
     * @brief Set the type of this @c AnalyserEquationAst.
     *
     * Set the type of this @c AnalyserEquationAst.
     *
     * @param parent The @c AnalyserEquationAst to be set as the type of this
     * @c AnalyserEquationAst.
     */
    void setType(Type type);

    /**
     * @brief Get the value for this @c AnalyserEquationAst.
     *
     * Return the value for this @c AnalyserEquationAst.
     *
     * @return The value.
     */
    std::string value() const;

    /**
     * @brief Set the value for this @c AnalyserEquationAst.
     *
     * Set the value for this @c AnalyserEquationAst.
     *
     * @param value The @c std::string to be set as the value for this
     * @c AnalyserEquationAst.
     */
    void setValue(const std::string &value);

    /**
     * @brief Get the variable for this @c AnalyserEquationAst.
     *
     * Return the variable for this @c AnalyserEquationAst.
     *
     * @return The variable.
     */
    VariablePtr variable() const;

    /**
     * @brief Set the variable for this @c AnalyserEquationAst.
     *
     * Set the variable for this @c AnalyserEquationAst.
     *
     * @param variable The @c Variable to be set as the variable for this
     * @c AnalyserEquationAst.
     */
    void setVariable(const VariablePtr &variable);

    /**
     * @brief Get the parent of this @c AnalyserEquationAst.
     *
     * Return the parent of this @c AnalyserEquationAst.
     *
     * @return The parent.
     */
    AnalyserEquationAstPtr parent() const;

    /**
     * @brief Set the parent of this @c AnalyserEquationAst.
     *
     * Set the parent of this @c AnalyserEquationAst.
     *
     * @param parent The @c AnalyserEquationAst to be set as the parent of this
     * @c AnalyserEquationAst.
     */
    void setParent(const AnalyserEquationAstPtr &parent);

    /**
     * @brief Get the left child for this @c AnalyserEquationAst.
     *
     * Return the left child of this @c AnalyserEquationAst.
     *
     * @return The left child.
     */
    AnalyserEquationAstPtr leftChild() const;

    /**
     * @brief Set the left child of this @c AnalyserEquationAst.
     *
     * Set the left child of this @c AnalyserEquationAst.
     *
     * @param leftChild The @c AnalyserEquationAst to be set as the left child
     * of this @c AnalyserEquationAst.
     */
    void setLeftChild(const AnalyserEquationAstPtr &leftChild);

    /**
     * @brief Get the right child for this @c AnalyserEquationAst.
     *
     * Return the right child of this @c AnalyserEquationAst.
     *
     * @return The right child.
     */
    AnalyserEquationAstPtr rightChild() const;

    /**
     * @brief Set the right child of this @c AnalyserEquationAst.
     *
     * Set the right child of this @c AnalyserEquationAst.
     *
     * @param rightChild The @c AnalyserEquationAst to be set as the right child
     * of this @c AnalyserEquationAst.
     */
    void setRightChild(const AnalyserEquationAstPtr &rightChild);

private:
    AnalyserEquationAst(); /**< Constructor */

    struct AnalyserEquationAstImpl;
    AnalyserEquationAstImpl *mPimpl;
};

} // namespace libcellml

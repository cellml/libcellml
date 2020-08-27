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
     *   AnalyserEquationAstPtr ast = libcellml::AnalyserEquationAst::create();
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

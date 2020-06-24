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

#include "libcellml/variable.h"

#undef NAN

#ifdef __linux__
#    undef TRUE
#    undef FALSE
#endif

namespace libcellml {

class GeneratorEquationAst;

using GeneratorEquationAstPtr = std::shared_ptr<GeneratorEquationAst>;
using GeneratorEquationAstWeakPtr = std::weak_ptr<GeneratorEquationAst>;

class GeneratorEquationAst
{
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

    Type mType = Type::ASSIGNMENT;

    std::string mValue;
    VariablePtr mVariable = nullptr;

    GeneratorEquationAstWeakPtr mParent;

    GeneratorEquationAstPtr mLeft = nullptr;
    GeneratorEquationAstPtr mRight = nullptr;

    explicit GeneratorEquationAst();
    explicit GeneratorEquationAst(Type type,
                                  const GeneratorEquationAstPtr &parent);
    explicit GeneratorEquationAst(Type type, const std::string &value,
                                  const GeneratorEquationAstPtr &parent);
    explicit GeneratorEquationAst(Type type, const VariablePtr &variable,
                                  const GeneratorEquationAstPtr &parent);
    explicit GeneratorEquationAst(const GeneratorEquationAstPtr &ast,
                                  const GeneratorEquationAstPtr &parent);
};

} // namespace libcellml

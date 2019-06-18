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

#ifdef _WIN32
#   define _USE_MATH_DEFINES
#endif

#include "utilities.h"
#include "xmldoc.h"

#include "libcellml/component.h"
#include "libcellml/generator.h"
#include "libcellml/model.h"
#include "libcellml/validator.h"
#include "libcellml/variable.h"

#include <algorithm>
#include <cmath>
#include <limits>
#include <vector>

#undef NAN

#ifdef __linux__
#   undef TRUE
#   undef FALSE
#endif

//TODO: remove the below code once we are done testing things...
#define TRACES
#ifdef TRACES
#   include <iostream>
#endif
namespace libcellml {

class GeneratorEquationAst;
using GeneratorEquationAstPtr = std::shared_ptr<GeneratorEquationAst>;

class GeneratorEquationAst
{
public:
    enum class Type {
        // Relational operators

        EQ, EQEQ, NEQ, LT, LEQ, GT, GEQ,

        // Arithmetic operators

        PLUS, MINUS, TIMES, DIVIDE,
        POWER, ROOT,
        ABS,
        EXP, LN, LOG,
        CEILING, FLOOR, FACTORIAL,

        // Logical operators

        AND, OR, XOR, NOT,

        // Calculus elements

        DIFF,

        // Min/max operators

        MIN, MAX,

        // Gcd/lcm operators

        GCD, LCM,

        // Trigonometric operators

        SIN, COS, TAN, SEC, CSC, COT,
        SINH, COSH, TANH, SECH, CSCH, COTH,
        ASIN, ACOS, ATAN, ASEC, ACSC, ACOT,
        ASINH, ACOSH, ATANH, ASECH, ACSCH, ACOTH,

        // Extra operators

        REM,

        // Piecewise statement

        PIECEWISE, PIECE, OTHERWISE,

        // Token elements

        CN, CI,

        // Qualifier elements

        DEGREE, LOGBASE, BVAR,

        // Constants

        TRUE, FALSE, E, PI, INF, NAN
    };

    explicit GeneratorEquationAst();
    explicit GeneratorEquationAst(Type type,
                                  const GeneratorEquationAstPtr &parent);
    explicit GeneratorEquationAst(Type type, const std::string &value,
                                  const GeneratorEquationAstPtr &parent);
    explicit GeneratorEquationAst(Type type, const VariablePtr &variable,
                                  const GeneratorEquationAstPtr &parent);

    Type type() const;

    std::string value() const;
    VariablePtr variable() const;

    GeneratorEquationAstPtr parent() const;
    void setParent(const GeneratorEquationAstPtr &parent);

    GeneratorEquationAstPtr &left();
    GeneratorEquationAstPtr &right();

private:
    Type mType;

    std::string mValue;
    VariablePtr mVariable;

    GeneratorEquationAstPtr mParent;

    GeneratorEquationAstPtr mLeft;
    GeneratorEquationAstPtr mRight;

    explicit GeneratorEquationAst(Type type, const std::string &value,
                                  const VariablePtr &variable,
                                  const GeneratorEquationAstPtr &parent);
};

GeneratorEquationAst::GeneratorEquationAst(Type type, const std::string &value,
                                           const VariablePtr &variable,
                                           const GeneratorEquationAstPtr &parent)
    : mType(type)
    , mValue(value)
    , mVariable(variable)
    , mParent(parent)
    , mLeft(nullptr)
    , mRight(nullptr)
{
}

GeneratorEquationAst::GeneratorEquationAst()
    : GeneratorEquationAst(Type::EQ, "", nullptr, nullptr)
{
}

GeneratorEquationAst::GeneratorEquationAst(Type type,
                                           const GeneratorEquationAstPtr &parent)
    : GeneratorEquationAst(type, "", nullptr, parent)
{
}

GeneratorEquationAst::GeneratorEquationAst(Type type, const std::string &value,
                                           const GeneratorEquationAstPtr &parent)
    : GeneratorEquationAst(type, value, nullptr, parent)
{
}

GeneratorEquationAst::GeneratorEquationAst(Type type, const VariablePtr &variable,
                                           const GeneratorEquationAstPtr &parent)
    : GeneratorEquationAst(type, "", variable, parent)
{
}

GeneratorEquationAst::Type GeneratorEquationAst::type() const
{
    return mType;
}

std::string GeneratorEquationAst::value() const
{
    return mValue;
}

VariablePtr GeneratorEquationAst::variable() const
{
    return mVariable;
}

GeneratorEquationAstPtr GeneratorEquationAst::parent() const
{
    return mParent;
}

void GeneratorEquationAst::setParent(const GeneratorEquationAstPtr &parent)
{
    mParent = parent;
}

GeneratorEquationAstPtr &GeneratorEquationAst::left()
{
    return mLeft;
}

GeneratorEquationAstPtr &GeneratorEquationAst::right()
{
    return mRight;
}

class GeneratorEquation;
using GeneratorEquationPtr = std::shared_ptr<GeneratorEquation>;

class GeneratorEquation
{
public:
    enum class Type {
        UNKNOWN,
        RATE,
        ALGEBRAIC
    };

    explicit GeneratorEquation(const ComponentPtr &component);

    Type type() const;

//TODO: needed?
//    ComponentPtr component() const;

    GeneratorEquationAstPtr &ast();

    std::vector<VariablePtr> variables() const;

    void addVariable(const VariablePtr &variable);
    void replaceVariable(const VariablePtr &oldVariable,
                         const VariablePtr &newVariable);

private:
    Type mType = Type::UNKNOWN;

    ComponentPtr mComponent;

    GeneratorEquationAstPtr mAst;

    std::vector<VariablePtr> mVariables;
};

GeneratorEquation::GeneratorEquation(const ComponentPtr &component)
    : mComponent(component)
    , mAst(std::make_shared<GeneratorEquationAst>())
{
}

GeneratorEquation::Type GeneratorEquation::type() const
{
    return mType;
}

//TODO: needed?
//ComponentPtr GeneratorEquation::component() const
//{
//    return mComponent;
//}

GeneratorEquationAstPtr &GeneratorEquation::ast()
{
    return mAst;
}

std::vector<VariablePtr> GeneratorEquation::variables() const
{
    return mVariables;
}

void GeneratorEquation::addVariable(const VariablePtr &variable)
{
    if (std::find(mVariables.begin(), mVariables.end(), variable) == mVariables.end()) {
        mVariables.push_back(variable);
    }
}

void GeneratorEquation::replaceVariable(const VariablePtr &oldVariable,
                                        const VariablePtr &newVariable)
{
    std::replace(mVariables.begin(), mVariables.end(), oldVariable, newVariable);
}

class GeneratorVariable;
using GeneratorVariablePtr = std::shared_ptr<GeneratorVariable>;

class GeneratorVariable
{
public:
    enum class Type {
        UNKNOWN,
        SHOULD_BE_STATE,
        VARIABLE_OF_INTEGRATION,
        STATE,
        ALGEBRAIC,
        CONSTANT,
        COMPUTED_CONSTANT
    };

    Type type() const;

    VariablePtr variable() const;
    void setVariable(const VariablePtr &variable);

    GeneratorEquationAstPtr variableAst() const;
    void setVariableAst(const GeneratorEquationAstPtr &ast);

    void makeVariableOfIntegration();
    void makeState();

private:
    Type mType = Type::UNKNOWN;

    VariablePtr mVariable = nullptr;
    GeneratorEquationAstPtr mAst = nullptr;
};

GeneratorVariable::Type GeneratorVariable::type() const
{
    return mType;
}

VariablePtr GeneratorVariable::variable() const
{
    return mVariable;
}

void GeneratorVariable::setVariable(const VariablePtr &variable)
{
    mVariable = variable;

    if (!variable->initialValue().empty()) {
        // The variable has an initial value, so it can either be a constant or
        // a state. If the type of the variable is currently unknown then we
        // consider it to be a constant (then, if we find an ODE for that
        // variable, we will that it was actually a state). On the other hand,
        // if it was thought that the variable should be a state, then we now
        // know that it is indeed one.

        if (mType == Type::UNKNOWN) {
            mType = Type::CONSTANT;
        } else if (mType == Type::SHOULD_BE_STATE) {
            mType = Type::STATE;
        }
    }
}

void GeneratorVariable::makeVariableOfIntegration()
{
    mType = Type::VARIABLE_OF_INTEGRATION;
}

void GeneratorVariable::makeState()
{
    if (mType == Type::UNKNOWN) {
        mType = Type::SHOULD_BE_STATE;
    } else if (mType == Type::CONSTANT) {
        mType = Type::STATE;
    }
}

GeneratorEquationAstPtr GeneratorVariable::variableAst() const
{
    return mAst;
}

void GeneratorVariable::setVariableAst(const GeneratorEquationAstPtr &ast)
{
    mAst = ast;
}

struct Generator::GeneratorImpl
{
    Generator *mGenerator = nullptr;

    bool mOptimize = true;
    bool mWithNames = true;

    VariablePtr mVariableOfIntegration;

    std::vector<GeneratorVariablePtr> mVariables;
    std::vector<GeneratorEquationPtr> mEquations;

    // Relational operators

    std::string mEq = " = ";
    std::string mEqEq = " == ";
    std::string mNeq = " != ";
    std::string mLt = " < ";
    std::string mLeq = " <= ";
    std::string mGt = " > ";
    std::string mGeq = " >= ";

    // Arithmetic operators

    std::string mPlus = "+";
    std::string mMinus = "-";
    std::string mTimes = "*";
    std::string mDivide = "/";
    std::string mPower = "pow";
    std::string mSquareRoot = "sqrt";
    std::string mSquare = "sqr";
    std::string mAbsoluteValue = "fabs";
    std::string mExponential = "exp";
    std::string mNapierianLogarithm = "log";
    std::string mCommonLogarithm = "log10";
    std::string mCeiling = "ceil";
    std::string mFloor = "floor";
    std::string mFactorial = "fact";

    bool mNeedFactorial = false;

    bool mHasPowerOperator = false;

    // Logical operators

    std::string mAnd = " && ";
    std::string mOr = " || ";
    std::string mXor = "^";
    std::string mNot = "!";

    bool mHasXorOperator = true;

    // Min/max operators

    std::string mMin = "min";
    std::string mMax = "max";

    bool mNeedMin = false;
    bool mNeedMax = false;

    // Gcd/lcm operators

    std::string mGcd = "gcd";
    std::string mLcm = "lcm";

    bool mNeedGcd = false;
    bool mNeedLcm = false;

    // Trigonometric operators

    std::string mSin = "sin";
    std::string mCos = "cos";
    std::string mTan = "tan";
    std::string mSec = "sec";
    std::string mCsc = "csc";
    std::string mCot = "cot";
    std::string mSinh = "sinh";
    std::string mCosh = "cosh";
    std::string mTanh = "tanh";
    std::string mSech = "sech";
    std::string mCsch = "csch";
    std::string mCoth = "coth";
    std::string mAsin = "asin";
    std::string mAcos = "acos";
    std::string mAtan = "atan";
    std::string mAsec = "asec";
    std::string mAcsc = "acsc";
    std::string mAcot = "acot";
    std::string mAsinh = "asinh";
    std::string mAcosh = "acosh";
    std::string mAtanh = "atanh";
    std::string mAsech = "asech";
    std::string mAcsch = "acsch";
    std::string mAcoth = "acoth";

    bool mNeedSec = false;
    bool mNeedCsc = false;
    bool mNeedCot = false;
    bool mNeedSech = false;
    bool mNeedCsch = false;
    bool mNeedCoth = false;
    bool mNeedAsec = false;
    bool mNeedAcsc = false;
    bool mNeedAcot = false;
    bool mNeedAsech = false;
    bool mNeedAcsch = false;
    bool mNeedAcoth = false;

    // Extra operators

    std::string mRem = "fmod";

    // Piecewise statement
    // Note: the parentheses around #cond is not needed (because of precedence
    //       rules). It's just that it looks better/clearer to have them
    //       (somewhat subjective indeed).

    std::string mConditionalOperatorIf = "(#cond)?#if";
    std::string mConditionalOperatorElse = ":#else";
    std::string mPiecewiseIf = "piecewise(#cond, #if";
    std::string mPiecewiseElse = ", #else)";

    bool mHasConditionalOperator = true;

    // Constants

    std::string mTrue = "true";
    std::string mFalse = "false";
    std::string mE = convertDoubleToString(exp(1.0));
    std::string mPi = convertDoubleToString(M_PI);
    std::string mInf = "1.0/0.0";
    std::string mNan = "sqrt(-1.0)";

    // Miscellaneous

    std::string mCommandSeparator = ";";

    size_t mathmlChildCount(const XmlNodePtr &node) const;
    XmlNodePtr mathmlChildNode(const XmlNodePtr &node, size_t index) const;

    GeneratorVariablePtr generatorVariable(const VariablePtr &variable) const;

    void processNode(const XmlNodePtr &node, GeneratorEquationAstPtr &ast,
                     const GeneratorEquationAstPtr &astParent,
                     const ComponentPtr &component,
                     const GeneratorEquationPtr &equation);
    GeneratorEquationPtr processNode(const XmlNodePtr &node,
                                     const ComponentPtr &component);
    void processComponent(const ComponentPtr &component);
    void processEquationAst(const GeneratorEquationAstPtr &ast);
    void processEquation(const GeneratorEquationPtr &equation);
    void processModel(const ModelPtr &model);

    std::string neededMathMethods() const;
    std::string initializeVariables() const;
    std::string computeConstantEquations() const;
    std::string computeRateEquations() const;
    std::string computeAlgebraicEquations() const;

    bool isRelationalOperator(const GeneratorEquationAstPtr &ast) const;
    bool isPlusOperator(const GeneratorEquationAstPtr &ast) const;
    bool isMinusOperator(const GeneratorEquationAstPtr &ast) const;
    bool isTimesOperator(const GeneratorEquationAstPtr &ast) const;
    bool isDivideOperator(const GeneratorEquationAstPtr &ast) const;
    bool isPowerOperator(const GeneratorEquationAstPtr &ast) const;
    bool isRootOperator(const GeneratorEquationAstPtr &ast) const;
    bool isLogicalOrBitwiseOperator(const GeneratorEquationAstPtr &ast) const;
    bool isAndOperator(const GeneratorEquationAstPtr &ast) const;
    bool isOrOperator(const GeneratorEquationAstPtr &ast) const;
    bool isXorOperator(const GeneratorEquationAstPtr &ast) const;
    bool isPiecewiseStatement(const GeneratorEquationAstPtr &ast) const;

    std::string generateOperatorCode(const std::string &op,
                                     const GeneratorEquationAstPtr &ast) const;
    std::string generateMinusUnaryCode(const GeneratorEquationAstPtr &ast) const;
    std::string generatePiecewiseIfCode(const std::string &condition,
                                        const std::string &value) const;
    std::string generatePiecewiseElseCode(const std::string &value) const;
    std::string generateCode(const GeneratorEquationAstPtr &ast,
                             const GeneratorEquationAstPtr &parentAst = nullptr) const;
};

size_t Generator::GeneratorImpl::mathmlChildCount(const XmlNodePtr &node) const
{
    // Return the number of child elements, in the MathML namespace, for the
    // given node

    XmlNodePtr childNode = node->firstChild();
    size_t res = (childNode->isMathmlElement())?1:0;

    while (childNode != nullptr) {
        childNode = childNode->next();

        if (childNode && childNode->isMathmlElement()) {
            ++res;
        }
    }

    return res;
}

XmlNodePtr Generator::GeneratorImpl::mathmlChildNode(const XmlNodePtr &node, size_t index) const
{
    // Return the nth child element of the given node, skipping anything that is
    // not int he MathML namespace

    static const size_t MAX_SIZE_T = std::numeric_limits<std::size_t>::max();

    XmlNodePtr res = node->firstChild();
    size_t childNodeIndex = (res->isMathmlElement())?0:MAX_SIZE_T;

    while ((res != nullptr) && (childNodeIndex != index)) {
        res = res->next();

        if (res && res->isMathmlElement()) {
            ++childNodeIndex;
        }
    }

    return res;
}

GeneratorVariablePtr Generator::GeneratorImpl::generatorVariable(const VariablePtr &variable) const
{
    for (const auto &generatorVariable : mVariables) {
        if (variable->isEquivalentVariable(generatorVariable->variable())) {
            return generatorVariable;
        }
    }

    return {};
}

void Generator::GeneratorImpl::processNode(const XmlNodePtr &node,
                                           GeneratorEquationAstPtr &ast,
                                           const GeneratorEquationAstPtr &astParent,
                                           const ComponentPtr &component,
                                           const GeneratorEquationPtr &equation)
{
    // Basic content elements

    if (node->isMathmlElement("apply")) {
        // We may have 2, 3 or more child nodes, e.g.
        //
        //                 +--------+
        //                 |   +    |
        //        "+a" ==> |  / \   |
        //                 | a  nil |
        //                 +--------+
        //
        //                 +-------+
        //                 |   +   |
        //       "a+b" ==> |  / \  |
        //                 | a   b |
        //                 +-------+
        //
        //                 +-------------+
        //                 |   +         |
        //                 |  / \        |
        //                 | a   +       |
        //                 |    / \      |
        // "a+b+c+d+e" ==> |   b   +     |
        //                 |      / \    |
        //                 |     c   +   |
        //                 |        / \  |
        //                 |       d   e |
        //                 +-------------+

        size_t childCount = mathmlChildCount(node);

        processNode(mathmlChildNode(node, 0), ast, astParent, component, equation);
        processNode(mathmlChildNode(node, 1), ast->left(), ast, component, equation);

        if (childCount >= 3) {
            GeneratorEquationAstPtr astRight;
            GeneratorEquationAstPtr tempAst;

            processNode(mathmlChildNode(node, childCount-1), astRight, nullptr, component, equation);

            for (size_t i = childCount-2; i > 1; --i) {
                processNode(mathmlChildNode(node, 0), tempAst, nullptr, component, equation);
                processNode(mathmlChildNode(node, i), tempAst->left(), tempAst, component, equation);

                astRight->setParent(tempAst);

                tempAst->right() = astRight;
                astRight = tempAst;
            }

            astRight->setParent(ast);

            ast->right() = astRight;
        }

    // Relational operators

    } else if (node->isMathmlElement("eq")) {
        // This element is used both to describe "a = b" and "a == b". We can
        // distinguish between the two by checking its grand-parent. If it's a
        // "math" MathML element then it means that it is used to describe
        // "a = b" otherwise it is used to describe "a == b". In the former
        // case, there is nothing more we need to do since ast is already of
        // GeneratorEquationAst::Type::EQ type.

        if (!node->parent()->parent()->isMathmlElement("math")) {
            ast = std::make_shared<GeneratorEquationAst>(GeneratorEquationAst::Type::EQEQ, astParent);
        }
    } else if (node->isMathmlElement("neq")) {
        ast = std::make_shared<GeneratorEquationAst>(GeneratorEquationAst::Type::NEQ, astParent);
    } else if (node->isMathmlElement("lt")) {
        ast = std::make_shared<GeneratorEquationAst>(GeneratorEquationAst::Type::LT, astParent);
    } else if (node->isMathmlElement("leq")) {
        ast = std::make_shared<GeneratorEquationAst>(GeneratorEquationAst::Type::LEQ, astParent);
    } else if (node->isMathmlElement("gt")) {
        ast = std::make_shared<GeneratorEquationAst>(GeneratorEquationAst::Type::GT, astParent);
    } else if (node->isMathmlElement("geq")) {
        ast = std::make_shared<GeneratorEquationAst>(GeneratorEquationAst::Type::GEQ, astParent);

    // Arithmetic operators

    } else if (node->isMathmlElement("plus")) {
        ast = std::make_shared<GeneratorEquationAst>(GeneratorEquationAst::Type::PLUS, astParent);
    } else if (node->isMathmlElement("minus")) {
        ast = std::make_shared<GeneratorEquationAst>(GeneratorEquationAst::Type::MINUS, astParent);
    } else if (node->isMathmlElement("times")) {
        ast = std::make_shared<GeneratorEquationAst>(GeneratorEquationAst::Type::TIMES, astParent);
    } else if (node->isMathmlElement("divide")) {
        ast = std::make_shared<GeneratorEquationAst>(GeneratorEquationAst::Type::DIVIDE, astParent);
    } else if (node->isMathmlElement("power")) {
        ast = std::make_shared<GeneratorEquationAst>(GeneratorEquationAst::Type::POWER, astParent);
    } else if (node->isMathmlElement("root")) {
        ast = std::make_shared<GeneratorEquationAst>(GeneratorEquationAst::Type::ROOT, astParent);
    } else if (node->isMathmlElement("abs")) {
        ast = std::make_shared<GeneratorEquationAst>(GeneratorEquationAst::Type::ABS, astParent);
    } else if (node->isMathmlElement("exp")) {
        ast = std::make_shared<GeneratorEquationAst>(GeneratorEquationAst::Type::EXP, astParent);
    } else if (node->isMathmlElement("ln")) {
        ast = std::make_shared<GeneratorEquationAst>(GeneratorEquationAst::Type::LN, astParent);
    } else if (node->isMathmlElement("log")) {
        ast = std::make_shared<GeneratorEquationAst>(GeneratorEquationAst::Type::LOG, astParent);
    } else if (node->isMathmlElement("ceiling")) {
        ast = std::make_shared<GeneratorEquationAst>(GeneratorEquationAst::Type::CEILING, astParent);
    } else if (node->isMathmlElement("floor")) {
        ast = std::make_shared<GeneratorEquationAst>(GeneratorEquationAst::Type::FLOOR, astParent);
    } else if (node->isMathmlElement("factorial")) {
        ast = std::make_shared<GeneratorEquationAst>(GeneratorEquationAst::Type::FACTORIAL, astParent);

        mNeedFactorial = true;

    // Logical operators

    } else if (node->isMathmlElement("and")) {
        ast = std::make_shared<GeneratorEquationAst>(GeneratorEquationAst::Type::AND, astParent);
    } else if (node->isMathmlElement("or")) {
        ast = std::make_shared<GeneratorEquationAst>(GeneratorEquationAst::Type::OR, astParent);
    } else if (node->isMathmlElement("xor")) {
        ast = std::make_shared<GeneratorEquationAst>(GeneratorEquationAst::Type::XOR, astParent);
    } else if (node->isMathmlElement("not")) {
        ast = std::make_shared<GeneratorEquationAst>(GeneratorEquationAst::Type::NOT, astParent);

    // Calculus elements

    } else if (node->isMathmlElement("diff")) {
        ast = std::make_shared<GeneratorEquationAst>(GeneratorEquationAst::Type::DIFF, astParent);

    // Min/max operators

    } else if (node->isMathmlElement("min")) {
        ast = std::make_shared<GeneratorEquationAst>(GeneratorEquationAst::Type::MIN, astParent);

        mNeedMin = true;
    } else if (node->isMathmlElement("max")) {
        ast = std::make_shared<GeneratorEquationAst>(GeneratorEquationAst::Type::MAX, astParent);

        mNeedMax = true;

    // Gcd/lcm operators

    } else if (node->isMathmlElement("gcd")) {
        ast = std::make_shared<GeneratorEquationAst>(GeneratorEquationAst::Type::GCD, astParent);

        mNeedGcd = true;
    } else if (node->isMathmlElement("lcm")) {
        ast = std::make_shared<GeneratorEquationAst>(GeneratorEquationAst::Type::LCM, astParent);

        mNeedLcm = true;

    // Trigonometric operators

    } else if (node->isMathmlElement("sin")) {
        ast = std::make_shared<GeneratorEquationAst>(GeneratorEquationAst::Type::SIN, astParent);
    } else if (node->isMathmlElement("cos")) {
        ast = std::make_shared<GeneratorEquationAst>(GeneratorEquationAst::Type::COS, astParent);
    } else if (node->isMathmlElement("tan")) {
        ast = std::make_shared<GeneratorEquationAst>(GeneratorEquationAst::Type::TAN, astParent);
    } else if (node->isMathmlElement("sec")) {
        ast = std::make_shared<GeneratorEquationAst>(GeneratorEquationAst::Type::SEC, astParent);

        mNeedSec = true;
    } else if (node->isMathmlElement("csc")) {
        ast = std::make_shared<GeneratorEquationAst>(GeneratorEquationAst::Type::CSC, astParent);

        mNeedCsc = true;
    } else if (node->isMathmlElement("cot")) {
        ast = std::make_shared<GeneratorEquationAst>(GeneratorEquationAst::Type::COT, astParent);

        mNeedCot = true;
    } else if (node->isMathmlElement("sinh")) {
        ast = std::make_shared<GeneratorEquationAst>(GeneratorEquationAst::Type::SINH, astParent);
    } else if (node->isMathmlElement("cosh")) {
        ast = std::make_shared<GeneratorEquationAst>(GeneratorEquationAst::Type::COSH, astParent);
    } else if (node->isMathmlElement("tanh")) {
        ast = std::make_shared<GeneratorEquationAst>(GeneratorEquationAst::Type::TANH, astParent);
    } else if (node->isMathmlElement("sech")) {
        ast = std::make_shared<GeneratorEquationAst>(GeneratorEquationAst::Type::SECH, astParent);

        mNeedSech = true;
    } else if (node->isMathmlElement("csch")) {
        ast = std::make_shared<GeneratorEquationAst>(GeneratorEquationAst::Type::CSCH, astParent);

        mNeedCsch = true;
    } else if (node->isMathmlElement("coth")) {
        ast = std::make_shared<GeneratorEquationAst>(GeneratorEquationAst::Type::COTH, astParent);

        mNeedCoth = true;
    } else if (node->isMathmlElement("arcsin")) {
        ast = std::make_shared<GeneratorEquationAst>(GeneratorEquationAst::Type::ASIN, astParent);
    } else if (node->isMathmlElement("arccos")) {
        ast = std::make_shared<GeneratorEquationAst>(GeneratorEquationAst::Type::ACOS, astParent);
    } else if (node->isMathmlElement("arctan")) {
        ast = std::make_shared<GeneratorEquationAst>(GeneratorEquationAst::Type::ATAN, astParent);
    } else if (node->isMathmlElement("arcsec")) {
        ast = std::make_shared<GeneratorEquationAst>(GeneratorEquationAst::Type::ASEC, astParent);

        mNeedAsec = true;
    } else if (node->isMathmlElement("arccsc")) {
        ast = std::make_shared<GeneratorEquationAst>(GeneratorEquationAst::Type::ACSC, astParent);

        mNeedAcsc = true;
    } else if (node->isMathmlElement("arccot")) {
        ast = std::make_shared<GeneratorEquationAst>(GeneratorEquationAst::Type::ACOT, astParent);

        mNeedAcot = true;
    } else if (node->isMathmlElement("arcsinh")) {
        ast = std::make_shared<GeneratorEquationAst>(GeneratorEquationAst::Type::ASINH, astParent);
    } else if (node->isMathmlElement("arccosh")) {
        ast = std::make_shared<GeneratorEquationAst>(GeneratorEquationAst::Type::ACOSH, astParent);
    } else if (node->isMathmlElement("arctanh")) {
        ast = std::make_shared<GeneratorEquationAst>(GeneratorEquationAst::Type::ATANH, astParent);
    } else if (node->isMathmlElement("arcsech")) {
        ast = std::make_shared<GeneratorEquationAst>(GeneratorEquationAst::Type::ASECH, astParent);

        mNeedAsech = true;
    } else if (node->isMathmlElement("arccsch")) {
        ast = std::make_shared<GeneratorEquationAst>(GeneratorEquationAst::Type::ACSCH, astParent);

        mNeedAcsch = true;
    } else if (node->isMathmlElement("arccoth")) {
        ast = std::make_shared<GeneratorEquationAst>(GeneratorEquationAst::Type::ACOTH, astParent);

        mNeedAcoth = true;

    // Extra operators

    } else if (node->isMathmlElement("rem")) {
        ast = std::make_shared<GeneratorEquationAst>(GeneratorEquationAst::Type::REM, astParent);

    // Piecewise statement

    } else if (node->isMathmlElement("piecewise")) {
        size_t childCount = mathmlChildCount(node);

        ast = std::make_shared<GeneratorEquationAst>(GeneratorEquationAst::Type::PIECEWISE, astParent);

        processNode(mathmlChildNode(node, 0), ast->left(), ast, component, equation);

        if (childCount >= 2) {
            GeneratorEquationAstPtr astRight;
            GeneratorEquationAstPtr tempAst;

            processNode(mathmlChildNode(node, childCount-1), astRight, nullptr, component, equation);

            for (size_t i = childCount-2; i > 0; --i) {
                tempAst = std::make_shared<GeneratorEquationAst>(GeneratorEquationAst::Type::PIECEWISE, astParent);

                processNode(mathmlChildNode(node, i), tempAst->left(), tempAst, component, equation);

                astRight->setParent(tempAst);

                tempAst->right() = astRight;
                astRight = tempAst;
            }

            astRight->setParent(ast);

            ast->right() = astRight;
        }
    } else if (node->isMathmlElement("piece")) {
        ast = std::make_shared<GeneratorEquationAst>(GeneratorEquationAst::Type::PIECE, astParent);

        processNode(mathmlChildNode(node, 0), ast->left(), ast, component, equation);
        processNode(mathmlChildNode(node, 1), ast->right(), ast, component, equation);
    } else if (node->isMathmlElement("otherwise")) {
        ast = std::make_shared<GeneratorEquationAst>(GeneratorEquationAst::Type::OTHERWISE, astParent);

        processNode(mathmlChildNode(node, 0), ast->left(), ast, component, equation);

    // Token elements

    } else if (node->isMathmlElement("cn")) {
        ast = std::make_shared<GeneratorEquationAst>(GeneratorEquationAst::Type::CN, node->firstChild()->convertToString(), astParent);
    } else if (node->isMathmlElement("ci")) {
        VariablePtr variable = component->variable(node->firstChild()->convertToString());

        ast = std::make_shared<GeneratorEquationAst>(GeneratorEquationAst::Type::CI, variable, astParent);

        equation->addVariable(variable);

    // Qualifier elements

    } else if (node->isMathmlElement("degree")) {
        ast = std::make_shared<GeneratorEquationAst>(GeneratorEquationAst::Type::DEGREE, astParent);

        processNode(mathmlChildNode(node, 0), ast->left(), ast, component, equation);
    } else if (node->isMathmlElement("logbase")) {
        ast = std::make_shared<GeneratorEquationAst>(GeneratorEquationAst::Type::LOGBASE, astParent);

        processNode(mathmlChildNode(node, 0), ast->left(), ast, component, equation);
    } else if (node->isMathmlElement("bvar")) {
        ast = std::make_shared<GeneratorEquationAst>(GeneratorEquationAst::Type::BVAR, astParent);

        processNode(mathmlChildNode(node, 0), ast->left(), ast, component, equation);

        XmlNodePtr rightNode = mathmlChildNode(node, 1);

        if (rightNode != nullptr) {
            processNode(rightNode, ast->right(), ast, component, equation);
        }

    // Constants

    } else if (node->isMathmlElement("true")) {
        ast = std::make_shared<GeneratorEquationAst>(GeneratorEquationAst::Type::TRUE, astParent);
    } else if (node->isMathmlElement("false")) {
        ast = std::make_shared<GeneratorEquationAst>(GeneratorEquationAst::Type::FALSE, astParent);
    } else if (node->isMathmlElement("exponentiale")) {
        ast = std::make_shared<GeneratorEquationAst>(GeneratorEquationAst::Type::E, astParent);
    } else if (node->isMathmlElement("pi")) {
        ast = std::make_shared<GeneratorEquationAst>(GeneratorEquationAst::Type::PI, astParent);
    } else if (node->isMathmlElement("infinity")) {
        ast = std::make_shared<GeneratorEquationAst>(GeneratorEquationAst::Type::INF, astParent);
    } else if (node->isMathmlElement("notanumber")) {
        ast = std::make_shared<GeneratorEquationAst>(GeneratorEquationAst::Type::NAN, astParent);
    }
}

GeneratorEquationPtr Generator::GeneratorImpl::processNode(const XmlNodePtr &node,
                                                           const ComponentPtr &component)
{
    // Create and keep track of the equation associated with the given node

    GeneratorEquationPtr equation = std::make_shared<GeneratorEquation>(component);

    mEquations.push_back(equation);

    // Actually process the node

    processNode(node, equation->ast(), equation->ast()->parent(), component, equation);

    return equation;
}

void Generator::GeneratorImpl::processComponent(const ComponentPtr &component)
{
    // Retrieve the math string associated with the given component and process
    // it, one equation at a time

    XmlDocPtr xmlDoc = std::make_shared<XmlDoc>();
    std::string math = component->math();
    std::vector<GeneratorEquationPtr> equations;

    if (!math.empty()) {
        xmlDoc->parseMathML(math);

        XmlNodePtr mathNode = xmlDoc->rootNode();

        for (XmlNodePtr node = mathNode->firstChild();
             node != nullptr; node = node->next()) {
            if (node->isMathmlElement()) {
                equations.push_back(processNode(node, component));
            }
        }
    }

    // Go trhough the given component's variable and make sure that everything
    // makes sense

    for (size_t i = 0; i < component->variableCount(); ++i) {
        // Check whether the variable is already tracked and, if not, track it

        bool componentVariableTracked = false;
        VariablePtr componentVariable = component->variable(i);
        GeneratorVariablePtr trackedVariable;

        for (const auto &variable : mVariables) {
            if (componentVariable->isEquivalentVariable(variable->variable())) {
                componentVariableTracked = true;
                trackedVariable = variable;

                break;
            }
        }

        if (!componentVariableTracked) {
            trackedVariable = std::make_shared<GeneratorVariable>();

            mVariables.push_back(trackedVariable);
        }

        // Set the variable held by trackedVariable, in case there was none
        // before or in case the existing one has no initial value while
        // componentVariable does. Otherwise, generate an error if the variable
        // held by trackedVariable and componentVariable are both initialised.

        if (   (trackedVariable->variable() == nullptr)
            || (   !componentVariable->initialValue().empty()
                &&  trackedVariable->variable()->initialValue().empty())) {
            trackedVariable->setVariable(componentVariable);
        } else if (   !componentVariable->initialValue().empty()
                   && !trackedVariable->variable()->initialValue().empty()) {
            ModelPtr model = component->parentModel();
            ComponentPtr trackedVariableComponent = trackedVariable->variable()->parentComponent();
            ModelPtr trackedVariableModel = trackedVariableComponent->parentModel();
            ErrorPtr err = std::make_shared<Error>();

            err->setDescription("Variable '"+componentVariable->name()+"' in component '"+component->name()+"' of model '"+model->name()+"' and "
                                "variable '"+trackedVariable->variable()->name()+"' in component '"+trackedVariableComponent->name()+"' of model '"+trackedVariableModel->name()+"' are equivalent and cannot therefore both be initialised.");
            err->setKind(Error::Kind::GENERATOR);

            mGenerator->addError(err);
        }
    }

    // Do the same for the components encapsulated by the given component

    for (size_t i = 0; i < component->componentCount(); ++i) {
        processComponent(component->component(i));
    }
}

void Generator::GeneratorImpl::processEquationAst(const GeneratorEquationAstPtr &ast)
{
    // Look for the definition of a variable of integration and make sure that
    // we don't have more than one of them and that it's not initialised

    GeneratorEquationAstPtr astParent = ast->parent();
    GeneratorEquationAstPtr astGrandParent = (astParent != nullptr)?astParent->parent():nullptr;
    GeneratorEquationAstPtr astGreatGrandParent = (astGrandParent != nullptr)?astGrandParent->parent():nullptr;

    if (   (ast->type() == GeneratorEquationAst::Type::CI)
        && (astParent != nullptr) && (astParent->type() == GeneratorEquationAst::Type::BVAR)
        && (astGrandParent != nullptr) && (astGrandParent->type() == GeneratorEquationAst::Type::DIFF)) {
        VariablePtr variable = ast->variable();

        generatorVariable(variable)->makeVariableOfIntegration();
        // Note: we must make the variable a variable of integration in all
        //       cases (i.e. even if there is, for example, already another
        //       variable of integration) otherwise unnecessary error messages
        //       may be added (since the variable would be of unknown type).

        if (mVariableOfIntegration == nullptr) {
            // Before keeping track of the variable of integration, make sure
            // that it is not initialised

            if (!variable->initialValue().empty()) {
                ComponentPtr component = variable->parentComponent();
                ModelPtr model = component->parentModel();
                ErrorPtr err = std::make_shared<Error>();

                err->setDescription("Variable '"+variable->name()+"' in component '"+component->name()+"' of model '"+model->name()+"' cannot be both a variable of integration and initialised.");
                err->setKind(Error::Kind::GENERATOR);

                mGenerator->addError(err);
            } else {
                mVariableOfIntegration = variable;
            }
        } else if (!variable->isEquivalentVariable(mVariableOfIntegration)) {
            ComponentPtr voiComponent = mVariableOfIntegration->parentComponent();
            ModelPtr voiModel = voiComponent->parentModel();
            ComponentPtr component = variable->parentComponent();
            ModelPtr model = component->parentModel();
            ErrorPtr err = std::make_shared<Error>();

            err->setDescription("Variable '"+mVariableOfIntegration->name()+"' in component '"+voiComponent->name()+"' of model '"+voiModel->name()+"' and variable '"+variable->name()+"' in component '"+component->name()+"' of model '"+model->name()+"' cannot both be a variable of integration.");
            err->setKind(Error::Kind::GENERATOR);

            mGenerator->addError(err);
        }
    }

    // Make sure that we only use first-order ODEs

    if (   (ast->type() == GeneratorEquationAst::Type::CN)
        && (astParent != nullptr) && (astParent->type() == GeneratorEquationAst::Type::DEGREE)
        && (astGrandParent != nullptr) && (astGrandParent->type() == GeneratorEquationAst::Type::BVAR)
        && (astGreatGrandParent != nullptr) && (astGreatGrandParent->type() == GeneratorEquationAst::Type::DIFF)) {
        if (convertToDouble(ast->value()) != 1.0) {
            VariablePtr variable = astGreatGrandParent->right()->variable();
            ComponentPtr component = variable->parentComponent();
            ModelPtr model = component->parentModel();
            ErrorPtr err = std::make_shared<Error>();

            err->setDescription("The differential equation for variable '"+variable->name()+"' in component '"+component->name()+"' of model '"+model->name()+"' must be of the first order.");
            err->setKind(Error::Kind::GENERATOR);

            mGenerator->addError(err);
        }
    }

    // Make a variable a state if it is used in an ODE

    if (   (ast->type() == GeneratorEquationAst::Type::CI)
        && (astParent != nullptr) && (astParent->type() == GeneratorEquationAst::Type::DIFF)) {
        generatorVariable(ast->variable())->makeState();
    }

    // Recursively check the given AST's children

    if (ast->left() != nullptr) {
        processEquationAst(ast->left());
    }

    if (ast->right() != nullptr) {
        processEquationAst(ast->right());
    }
}

void Generator::GeneratorImpl::processEquation(const GeneratorEquationPtr &equation)
{
    // Update the equation's variables with those that have become our reference

    for (const auto &equationVariable : equation->variables()) {
        for (const auto &variable : mVariables) {
            if (equationVariable->isEquivalentVariable(variable->variable())) {
                equation->replaceVariable(equationVariable, variable->variable());
            }
        }
    }

    // Process the equation's AST

    processEquationAst(equation->ast());
}

void Generator::GeneratorImpl::processModel(const ModelPtr &model)
{
    // Reset a few things in case we were to process the model more than once
    // Note: one would normally process the model only once, so we shouldn't
    //       need to do this, but better be safe than sorry.

    mVariableOfIntegration = nullptr;

    mVariables.clear();
    mEquations.clear();

    mNeedFactorial = false;

    mNeedMin = false;
    mNeedMax = false;

    mNeedGcd = false;
    mNeedLcm = false;

    mNeedSec = false;
    mNeedCsc = false;
    mNeedCot = false;
    mNeedSech = false;
    mNeedCsch = false;
    mNeedCoth = false;
    mNeedAsec = false;
    mNeedAcsc = false;
    mNeedAcot = false;
    mNeedAsech = false;
    mNeedAcsch = false;
    mNeedAcoth = false;

    // Recursively process the model's components, so that we end up with an AST
    // for each of the model's equations

    for (size_t i = 0; i < model->componentCount(); ++i) {
        processComponent(model->component(i));
    }

    // Process our different equations

    for (const auto &equation : mEquations) {
        processEquation(equation);
    }

    // Make sure that all our variables are valid

    for (const auto &variable : mVariables) {
        std::string errorType;

        switch (variable->type()) {
        case GeneratorVariable::Type::UNKNOWN:
            errorType = "is of unknown type";

            break;
        case GeneratorVariable::Type::SHOULD_BE_STATE:
            errorType = "is used in an ODE, but it is not initialised";

            break;
        case GeneratorVariable::Type::VARIABLE_OF_INTEGRATION:
        case GeneratorVariable::Type::STATE:
        case GeneratorVariable::Type::ALGEBRAIC:
        case GeneratorVariable::Type::CONSTANT:
        case GeneratorVariable::Type::COMPUTED_CONSTANT:
            break;
        }

        if (!errorType.empty()) {
            ErrorPtr err = std::make_shared<Error>();
            VariablePtr realVariable = variable->variable();
            ComponentPtr realComponent = realVariable->parentComponent();
            ModelPtr realModel = realComponent->parentModel();

            err->setDescription("Variable '"+realVariable->name()+"' in component '"+realComponent->name()+"' of model '"+realModel->name()+"' "+errorType+".");
            err->setKind(Error::Kind::GENERATOR);

            mGenerator->addError(err);
        }
    }

    // Optimise the model (e.g. X+0 ===> X), if requested and if there are no
    // errors

    if (mOptimize && (mGenerator->errorCount() == 0)) {
//TODO: to be done...
    }

//TODO: remove the below code once we are done testing things...
#ifdef TRACES
std::cout << "Number of variables: " << mVariables.size() << std::endl;
int i = 0;
for (const auto &variable : mVariables) {
    std::cout << "Variable #" << ++i << " [" << int(variable->type())
              << "]: " << variable->variable()->name().c_str()
              << " " << (variable->variable()->initialValue().empty()?
                             "":
                             std::string("[init: "+variable->variable()->initialValue()+"] "))
              << "[comp: " << variable->variable()->parentComponent()->name() << "]" << std::endl;
}
std::cout << "[neededMathMethods()]---------------------------------------[BEGIN]" << std::endl;
std::cout << neededMathMethods() << std::endl;
std::cout << "[neededMathMethods()]---------------------------------------[END]" << std::endl;
std::cout << "[initializeVariables()]---------------------------------------[BEGIN]" << std::endl;
std::cout << initializeVariables() << std::endl;
std::cout << "[initializeVariables()]---------------------------------------[END]" << std::endl;
std::cout << "[computeConstantEquations()]---------------------------------------[BEGIN]" << std::endl;
std::cout << computeConstantEquations() << std::endl;
std::cout << "[computeConstantEquations()]---------------------------------------[END]" << std::endl;
std::cout << "[computeRateEquations()]---------------------------------------[BEGIN]" << std::endl;
std::cout << computeRateEquations() << std::endl;
std::cout << "[computeRateEquations()]---------------------------------------[END]" << std::endl;
std::cout << "[computeAlgebraicEquations()]---------------------------------------[BEGIN]" << std::endl;
std::cout << computeAlgebraicEquations() << std::endl;
std::cout << "[computeAlgebraicEquations()]---------------------------------------[END]" << std::endl;
#endif
}

std::string Generator::GeneratorImpl::neededMathMethods() const
{
    return {};
}

std::string Generator::GeneratorImpl::initializeVariables() const
{
    std::string res;

    for (const auto &variable : mVariables) {
        if (variable->type() == GeneratorVariable::Type::CONSTANT) {
            res += variable->variable()->name()+" = "+variable->variable()->initialValue()+mCommandSeparator+"\n";
        }
    }

    return res;
}

std::string Generator::GeneratorImpl::computeConstantEquations() const
{
    std::string res;

    for (const auto &variable : mVariables) {
        if (variable->type() == GeneratorVariable::Type::COMPUTED_CONSTANT) {
//TODO: to be done...
        }
    }

    return res;
}

std::string Generator::GeneratorImpl::computeRateEquations() const
{
    std::string res;

    for (const auto &equation : mEquations) {
        if (equation->type() == GeneratorEquation::Type::RATE) {
            res += generateCode(equation->ast());
        }
    }

    return res;
}

std::string Generator::GeneratorImpl::computeAlgebraicEquations() const
{
    std::string res;

    for (const auto &equation : mEquations) {
//        if (equation->type() == GeneratorEquation::Type::ALGEBRAIC) {
            res += generateCode(equation->ast())+mCommandSeparator+"\n";
//        }
    }

    return res;
}

std::string replace(const std::string &string, const std::string &from, const std::string &to)
{
    return std::string(string).replace(string.find(from), from.length(), to);
}

bool Generator::GeneratorImpl::isRelationalOperator(const GeneratorEquationAstPtr &ast) const
{
    return    (ast->type() == GeneratorEquationAst::Type::EQEQ)
           || (ast->type() == GeneratorEquationAst::Type::NEQ)
           || (ast->type() == GeneratorEquationAst::Type::LT)
           || (ast->type() == GeneratorEquationAst::Type::LEQ)
           || (ast->type() == GeneratorEquationAst::Type::GT)
           || (ast->type() == GeneratorEquationAst::Type::GEQ);
}

bool Generator::GeneratorImpl::isPlusOperator(const GeneratorEquationAstPtr &ast) const
{
    return ast->type() == GeneratorEquationAst::Type::PLUS;
}

bool Generator::GeneratorImpl::isMinusOperator(const GeneratorEquationAstPtr &ast) const
{
    return ast->type() == GeneratorEquationAst::Type::MINUS;
}

bool Generator::GeneratorImpl::isTimesOperator(const GeneratorEquationAstPtr &ast) const
{
    return ast->type() == GeneratorEquationAst::Type::TIMES;
}

bool Generator::GeneratorImpl::isDivideOperator(const GeneratorEquationAstPtr &ast) const
{
    return ast->type() == GeneratorEquationAst::Type::DIVIDE;
}

bool Generator::GeneratorImpl::isPowerOperator(const GeneratorEquationAstPtr &ast) const
{
    return ast->type() == GeneratorEquationAst::Type::POWER;
}

bool Generator::GeneratorImpl::isRootOperator(const GeneratorEquationAstPtr &ast) const
{
    return ast->type() == GeneratorEquationAst::Type::ROOT;
}

bool Generator::GeneratorImpl::isAndOperator(const GeneratorEquationAstPtr &ast) const
{
    return ast->type() == GeneratorEquationAst::Type::AND;
}

bool Generator::GeneratorImpl::isOrOperator(const GeneratorEquationAstPtr &ast) const
{
    return ast->type() == GeneratorEquationAst::Type::OR;
}

bool Generator::GeneratorImpl::isXorOperator(const GeneratorEquationAstPtr &ast) const
{
    return ast->type() == GeneratorEquationAst::Type::XOR;
}

bool Generator::GeneratorImpl::isLogicalOrBitwiseOperator(const GeneratorEquationAstPtr &ast) const
{
    // Note: GeneratorEquationAst::Type::NOT is a unary logical operator hence
    //       we don't include it here since this method is only used to
    //       determine whether parentheses should be added around some code.

    return    (ast->type() == GeneratorEquationAst::Type::AND)
           || (ast->type() == GeneratorEquationAst::Type::OR)
           || (ast->type() == GeneratorEquationAst::Type::XOR);
}

bool Generator::GeneratorImpl::isPiecewiseStatement(const GeneratorEquationAstPtr &ast) const
{
    return ast->type() == GeneratorEquationAst::Type::PIECEWISE;
}

std::string Generator::GeneratorImpl::generateOperatorCode(const std::string &op,
                                                           const GeneratorEquationAstPtr &ast) const
{
    // Generate the code for the left and right branches of the given AST

    std::string left = generateCode(ast->left());
    std::string right = generateCode(ast->right());

    // Determine whether parentheses should be added around the left and/or
    // right piece of code, and this based on the precedence of the operators
    // used in CellML, which are listed below from higher to lower precedence:
    //  1. Parentheses                                           [Left to right]
    //  2. POWER (as an operator, not as a function, i.e.        [Left to right]
    //            as in Matlab and not in C, for example)
    //  3. Unary PLUS, Unary MINUS, NOT                          [Right to left]
    //  4. TIMES, DIVIDE                                         [Left to right]
    //  5. PLUS, MINUS                                           [Left to right]
    //  6. LT, LEQ, GT, GEQ                                      [Left to right]
    //  7. EQEQ, NEQ                                             [Left to right]
    //  8. XOR (bitwise)                                         [Left to right]
    //  9. AND (logical)                                         [Left to right]
    // 10. OR (logical)                                          [Left to right]
    // 11. PIECEWISE (as an operator)                            [Right to left]

    if (isPlusOperator(ast)) {
        if (   isRelationalOperator(ast->left())
            || isLogicalOrBitwiseOperator(ast->left())
            || isPiecewiseStatement(ast->left())) {
            left = "("+left+")";
        }

        if (   isRelationalOperator(ast->right())
            || isLogicalOrBitwiseOperator(ast->right())
            || isPiecewiseStatement(ast->right())) {
            right = "("+right+")";
        }
    } else if (isMinusOperator(ast)) {
        if (   isRelationalOperator(ast->left())
            || isLogicalOrBitwiseOperator(ast->left())
            || isPiecewiseStatement(ast->left())) {
            left = "("+left+")";
        }

        if (   isRelationalOperator(ast->right())
            || isMinusOperator(ast->right())
            || isLogicalOrBitwiseOperator(ast->right())
            || isPiecewiseStatement(ast->right())) {
            right = "("+right+")";
        } else if (isPlusOperator(ast->right())) {
            if (ast->right()->right() != nullptr) {
                right = "("+right+")";
            }
        }
    } else if (isTimesOperator(ast)) {
        if (   isRelationalOperator(ast->left())
            || isLogicalOrBitwiseOperator(ast->left())
            || isPiecewiseStatement(ast->left())) {
            left = "("+left+")";
        } else if (   isPlusOperator(ast->left())
                   || isMinusOperator(ast->left())) {
            if (ast->left()->right() != nullptr) {
                left = "("+left+")";
            }
        }

        if (   isRelationalOperator(ast->right())
            || isLogicalOrBitwiseOperator(ast->right())
            || isPiecewiseStatement(ast->right())) {
            right = "("+right+")";
        } else if (   isPlusOperator(ast->right())
                   || isMinusOperator(ast->right())) {
            if (ast->right()->right() != nullptr) {
                right = "("+right+")";
            }
        }
    } else if (isDivideOperator(ast)) {
        if (   isRelationalOperator(ast->left())
            || isLogicalOrBitwiseOperator(ast->left())
            || isPiecewiseStatement(ast->left())) {
            left = "("+left+")";
        } else if (   isPlusOperator(ast->left())
                   || isMinusOperator(ast->left())) {
            if (ast->left()->right() != nullptr) {
                left = "("+left+")";
            }
        }

        if (   isRelationalOperator(ast->right())
            || isTimesOperator(ast->right())
            || isDivideOperator(ast->right())
            || isLogicalOrBitwiseOperator(ast->right())
            || isPiecewiseStatement(ast->right())) {
            right = "("+right+")";
        } else if (   isPlusOperator(ast->right())
                   || isMinusOperator(ast->right())) {
            if (ast->right()->right() != nullptr) {
                right = "("+right+")";
            }
        }
    } else if (isAndOperator(ast)) {
        // Note: according to the precedence rules above, we only need to add
        //       parentheses around OR and PIECEWISE. It's just that it looks
        //       better/clearer to have some around some other operators
        //       (somewhat subjective indeed).

        if (   isRelationalOperator(ast->left())
            || isOrOperator(ast->left())
            || isXorOperator(ast->left())
            || isPiecewiseStatement(ast->left())) {
            left = "("+left+")";
        } else if (   isPlusOperator(ast->left())
                   || isMinusOperator(ast->left())) {
            if (ast->left()->right() != nullptr) {
                left = "("+left+")";
            }
        } else if (isPowerOperator(ast->left())) {
            if (mHasPowerOperator) {
                left = "("+left+")";
            }
        } else if (isRootOperator(ast->left())) {
            if (mHasPowerOperator) {
                left = "("+left+")";
            }
        }

        if (   isRelationalOperator(ast->right())
            || isOrOperator(ast->right())
            || isXorOperator(ast->right())
            || isPiecewiseStatement(ast->right())) {
            right = "("+right+")";
        } else if (   isPlusOperator(ast->right())
                   || isMinusOperator(ast->right())) {
            if (ast->right()->right() != nullptr) {
                right = "("+right+")";
            }
        } else if (isPowerOperator(ast->right())) {
            if (mHasPowerOperator) {
                right = "("+right+")";
            }
        } else if (isRootOperator(ast->right())) {
            if (mHasPowerOperator) {
                right = "("+right+")";
            }
        }
    } else if (isOrOperator(ast)) {
        // Note: according to the precedence rules above, we only need to add
        //       parentheses around PIECEWISE. It's just that it looks
        //       better/clearer to have some around some other operators
        //       (somewhat subjective indeed).

        if (   isRelationalOperator(ast->left())
            || isAndOperator(ast->left())
            || isXorOperator(ast->left())
            || isPiecewiseStatement(ast->left())) {
            left = "("+left+")";
        } else if (   isPlusOperator(ast->left())
                   || isMinusOperator(ast->left())) {
            if (ast->left()->right() != nullptr) {
                left = "("+left+")";
            }
        } else if (isPowerOperator(ast->left())) {
            if (mHasPowerOperator) {
                left = "("+left+")";
            }
        } else if (isRootOperator(ast->left())) {
            if (mHasPowerOperator) {
                left = "("+left+")";
            }
        }

        if (   isRelationalOperator(ast->right())
            || isAndOperator(ast->right())
            || isXorOperator(ast->right())
            || isPiecewiseStatement(ast->right())) {
            right = "("+right+")";
        } else if (   isPlusOperator(ast->right())
                   || isMinusOperator(ast->right())) {
            if (ast->right()->right() != nullptr) {
                right = "("+right+")";
            }
        } else if (isPowerOperator(ast->right())) {
            if (mHasPowerOperator) {
                right = "("+right+")";
            }
        } else if (isRootOperator(ast->right())) {
            if (mHasPowerOperator) {
                right = "("+right+")";
            }
        }
    } else if (isXorOperator(ast)) {
        // Note: according to the precedence rules above, we only need to add
        //       parentheses around AND, OR and PIECEWISE. It's just that it
        //       looks better/clearer to have some around some other operators
        //       (somewhat subjective indeed).

        if (   isRelationalOperator(ast->left())
            || isAndOperator(ast->left())
            || isOrOperator(ast->left())
            || isPiecewiseStatement(ast->left())) {
            left = "("+left+")";
        } else if (   isPlusOperator(ast->left())
                   || isMinusOperator(ast->left())) {
            if (ast->left()->right() != nullptr) {
                left = "("+left+")";
            }
        } else if (isPowerOperator(ast->left())) {
            if (mHasPowerOperator) {
                left = "("+left+")";
            }
        } else if (isRootOperator(ast->left())) {
            if (mHasPowerOperator) {
                left = "("+left+")";
            }
        }

        if (   isRelationalOperator(ast->right())
            || isAndOperator(ast->right())
            || isOrOperator(ast->right())
            || isPiecewiseStatement(ast->right())) {
            right = "("+right+")";
        } else if (   isPlusOperator(ast->right())
                   || isMinusOperator(ast->right())) {
            if (ast->right()->right() != nullptr) {
                right = "("+right+")";
            }
        } else if (isPowerOperator(ast->right())) {
            if (mHasPowerOperator) {
                right = "("+right+")";
            }
        } else if (isRootOperator(ast->right())) {
            if (mHasPowerOperator) {
                right = "("+right+")";
            }
        }
    } else if (isPowerOperator(ast)) {
        if (   isRelationalOperator(ast->left())
            || isMinusOperator(ast->left())
            || isTimesOperator(ast->left())
            || isDivideOperator(ast->left())
            || isLogicalOrBitwiseOperator(ast->left())
            || isPiecewiseStatement(ast->left())) {
            left = "("+left+")";
        } else if (isPlusOperator(ast->left())) {
            if (ast->left()->right() != nullptr) {
                left = "("+left+")";
            }
        }

        if (   isRelationalOperator(ast->right())
            || isMinusOperator(ast->left())
            || isTimesOperator(ast->right())
            || isDivideOperator(ast->right())
            || isPowerOperator(ast->right())
            || isRootOperator(ast->right())
            || isLogicalOrBitwiseOperator(ast->right())
            || isPiecewiseStatement(ast->right())) {
            right = "("+right+")";
        } else if (isPlusOperator(ast->right())) {
            if (ast->right()->right() != nullptr) {
                right = "("+right+")";
            }
        }
    } else if (isRootOperator(ast)) {
        if (   isRelationalOperator(ast->right())
            || isMinusOperator(ast->right())
            || isTimesOperator(ast->right())
            || isDivideOperator(ast->right())
            || isLogicalOrBitwiseOperator(ast->right())
            || isPiecewiseStatement(ast->right())) {
            right = "("+right+")";
        } else if (isPlusOperator(ast->right())) {
            if (ast->right()->right() != nullptr) {
                right = "("+right+")";
            }
        }

        if (   isRelationalOperator(ast->left())
            || isMinusOperator(ast->left())
            || isTimesOperator(ast->left())
            || isDivideOperator(ast->left())
            || isPowerOperator(ast->left())
            || isRootOperator(ast->left())
            || isLogicalOrBitwiseOperator(ast->left())
            || isPiecewiseStatement(ast->left())) {
            left = "("+left+")";
        } else if (isPlusOperator(ast->left())) {
            if (ast->left()->right() != nullptr) {
                left = "("+left+")";
            }
        }

        return right+op+"(1.0/"+left+")";
    }

    return left+op+right;
}

std::string Generator::GeneratorImpl::generateMinusUnaryCode(const GeneratorEquationAstPtr &ast) const
{
    // Generate the code for the left branch of the given AST

    std::string left = generateCode(ast->left());

    // Determine whether parentheses should be added around the left code

    if (   isRelationalOperator(ast->left())
        || isPlusOperator(ast->left())
        || isMinusOperator(ast->left())
        || isLogicalOrBitwiseOperator(ast->left())
        || isPiecewiseStatement(ast->left())) {
        left = "("+left+")";
    }

    return mMinus+left;
}

std::string Generator::GeneratorImpl::generatePiecewiseIfCode(const std::string &condition,
                                                              const std::string &value) const
{
    return replace(replace(mHasConditionalOperator?
                               mConditionalOperatorIf:
                               mPiecewiseIf, "#cond", condition), "#if", value);
}

std::string Generator::GeneratorImpl::generatePiecewiseElseCode(const std::string &value) const
{
    return replace(mHasConditionalOperator?
                       mConditionalOperatorElse:
                       mPiecewiseElse, "#else", value);
}

std::string Generator::GeneratorImpl::generateCode(const GeneratorEquationAstPtr &ast,
                                                   const GeneratorEquationAstPtr &parentAst) const
{
    // Generate the code for the given AST

    switch (ast->type()) {
    // Relational operators

    case GeneratorEquationAst::Type::EQ:
        return generateOperatorCode(mEq, ast);
    case GeneratorEquationAst::Type::EQEQ:
        return generateOperatorCode(mEqEq, ast);
    case GeneratorEquationAst::Type::NEQ:
        return generateOperatorCode(mNeq, ast);
    case GeneratorEquationAst::Type::LT:
        return generateOperatorCode(mLt, ast);
    case GeneratorEquationAst::Type::LEQ:
        return generateOperatorCode(mLeq, ast);
    case GeneratorEquationAst::Type::GT:
        return generateOperatorCode(mGt, ast);
    case GeneratorEquationAst::Type::GEQ:
        return generateOperatorCode(mGeq, ast);

    // Arithmetic operators

    case GeneratorEquationAst::Type::PLUS:
        if (ast->right() != nullptr) {
            return generateOperatorCode(mPlus, ast);
        }

        return generateCode(ast->left());
    case GeneratorEquationAst::Type::MINUS:
        if (ast->right() != nullptr) {
            return generateOperatorCode(mMinus, ast);
        }

        return generateMinusUnaryCode(ast);
    case GeneratorEquationAst::Type::TIMES:
        return generateOperatorCode(mTimes, ast);
    case GeneratorEquationAst::Type::DIVIDE:
        return generateOperatorCode(mDivide, ast);
    case GeneratorEquationAst::Type::POWER: {
        std::string stringValue = generateCode(ast->right());
        double doubleValue = convertToDouble(stringValue);

        if (isEqual(doubleValue, 0.5)) {
            return mSquareRoot+"("+generateCode(ast->left())+")";
        }

        if (isEqual(doubleValue, 2.0)) {
            return mSquare+"("+generateCode(ast->left())+")";
        }

        return mHasPowerOperator?
                   generateOperatorCode(mPower, ast):
                   mPower+"("+generateCode(ast->left())+", "+stringValue+")";
    }
    case GeneratorEquationAst::Type::ROOT:
        if (ast->right() != nullptr) {
            std::string stringValue = generateCode(ast->left());
            double doubleValue = convertToDouble(stringValue);

            if (isEqual(doubleValue, 2.0)) {
                return mSquareRoot+"("+generateCode(ast->right())+")";
            }

            return mHasPowerOperator?
                       generateOperatorCode(mPower, ast):
                       mPower+"("+generateCode(ast->right())+", 1.0/"+stringValue+")";
        }

        return mSquareRoot+"("+generateCode(ast->left())+")";
    case GeneratorEquationAst::Type::ABS:
        return mAbsoluteValue+"("+generateCode(ast->left())+")";
    case GeneratorEquationAst::Type::EXP:
        return mExponential+"("+generateCode(ast->left())+")";
    case GeneratorEquationAst::Type::LN:
        return mNapierianLogarithm+"("+generateCode(ast->left())+")";
    case GeneratorEquationAst::Type::LOG:
        if (ast->right() != nullptr) {
            std::string stringValue = generateCode(ast->left());
            double doubleValue = convertToDouble(stringValue);

            if (isEqual(doubleValue, 10.0)) {
                return mCommonLogarithm+"("+generateCode(ast->right())+")";
            }

            return mNapierianLogarithm+"("+generateCode(ast->right())+")/"+mNapierianLogarithm+"("+stringValue+")";
        }

        return mCommonLogarithm+"("+generateCode(ast->left())+")";
    case GeneratorEquationAst::Type::CEILING:
        return mCeiling+"("+generateCode(ast->left())+")";
    case GeneratorEquationAst::Type::FLOOR:
        return mFloor+"("+generateCode(ast->left())+")";
    case GeneratorEquationAst::Type::FACTORIAL:
        return mFactorial+"("+generateCode(ast->left())+")";

    // Logical operators

    case GeneratorEquationAst::Type::AND:
        return generateOperatorCode(mAnd, ast);
    case GeneratorEquationAst::Type::OR:
        return generateOperatorCode(mOr, ast);
    case GeneratorEquationAst::Type::XOR:
        if (mHasXorOperator) {
            return generateOperatorCode(mXor, ast);
        }

        return mXor+"("+generateCode(ast->left())+", "+generateCode(ast->right())+")";
    case GeneratorEquationAst::Type::NOT:
        return mNot+generateCode(ast->left());

    // Calculus elements

    case GeneratorEquationAst::Type::DIFF:
        return "d("+generateCode(ast->right())+")/d("+generateCode(ast->left())+")";

    // Min/max operators

    case GeneratorEquationAst::Type::MIN:
        if (parentAst == nullptr) {
            return mMin+"("+generateCode(ast->left(), ast)+", "+generateCode(ast->right(), ast)+")";
        }

        return generateCode(ast->left(), ast)+", "+generateCode(ast->right(), ast);
    case GeneratorEquationAst::Type::MAX:
        if (parentAst == nullptr) {
            return mMax+"("+generateCode(ast->left(), ast)+", "+generateCode(ast->right(), ast)+")";
        }

        return generateCode(ast->left(), ast)+", "+generateCode(ast->right(), ast);

    // Gcd/lcm operators

    case GeneratorEquationAst::Type::GCD:
        if (parentAst == nullptr) {
            return mGcd+"("+generateCode(ast->left(), ast)+", "+generateCode(ast->right(), ast)+")";
        }

        return generateCode(ast->left(), ast)+", "+generateCode(ast->right(), ast);
    case GeneratorEquationAst::Type::LCM:
        if (parentAst == nullptr) {
            return mLcm+"("+generateCode(ast->left(), ast)+", "+generateCode(ast->right(), ast)+")";
        }

        return generateCode(ast->left(), ast)+", "+generateCode(ast->right(), ast);

    // Trigonometric operators

    case GeneratorEquationAst::Type::SIN:
        return mSin+"("+generateCode(ast->left())+")";
    case GeneratorEquationAst::Type::COS:
        return mCos+"("+generateCode(ast->left())+")";
    case GeneratorEquationAst::Type::TAN:
        return mTan+"("+generateCode(ast->left())+")";
    case GeneratorEquationAst::Type::SEC:
        return mSec+"("+generateCode(ast->left())+")";
    case GeneratorEquationAst::Type::CSC:
        return mCsc+"("+generateCode(ast->left())+")";
    case GeneratorEquationAst::Type::COT:
        return mCot+"("+generateCode(ast->left())+")";
    case GeneratorEquationAst::Type::SINH:
        return mSinh+"("+generateCode(ast->left())+")";
    case GeneratorEquationAst::Type::COSH:
        return mCosh+"("+generateCode(ast->left())+")";
    case GeneratorEquationAst::Type::TANH:
        return mTanh+"("+generateCode(ast->left())+")";
    case GeneratorEquationAst::Type::SECH:
        return mSech+"("+generateCode(ast->left())+")";
    case GeneratorEquationAst::Type::CSCH:
        return mCsch+"("+generateCode(ast->left())+")";
    case GeneratorEquationAst::Type::COTH:
        return mCoth+"("+generateCode(ast->left())+")";
    case GeneratorEquationAst::Type::ASIN:
        return mAsin+"("+generateCode(ast->left())+")";
    case GeneratorEquationAst::Type::ACOS:
        return mAcos+"("+generateCode(ast->left())+")";
    case GeneratorEquationAst::Type::ATAN:
        return mAtan+"("+generateCode(ast->left())+")";
    case GeneratorEquationAst::Type::ASEC:
        return mAsec+"("+generateCode(ast->left())+")";
    case GeneratorEquationAst::Type::ACSC:
        return mAcsc+"("+generateCode(ast->left())+")";
    case GeneratorEquationAst::Type::ACOT:
        return mAcot+"("+generateCode(ast->left())+")";
    case GeneratorEquationAst::Type::ASINH:
        return mAsinh+"("+generateCode(ast->left())+")";
    case GeneratorEquationAst::Type::ACOSH:
        return mAcosh+"("+generateCode(ast->left())+")";
    case GeneratorEquationAst::Type::ATANH:
        return mAtanh+"("+generateCode(ast->left())+")";
    case GeneratorEquationAst::Type::ASECH:
        return mAsech+"("+generateCode(ast->left())+")";
    case GeneratorEquationAst::Type::ACSCH:
        return mAcsch+"("+generateCode(ast->left())+")";
    case GeneratorEquationAst::Type::ACOTH:
        return mAcoth+"("+generateCode(ast->left())+")";

    // Extra operators

    case GeneratorEquationAst::Type::REM:
        return mRem+"("+generateCode(ast->left())+", "+generateCode(ast->right())+")";

    // Piecewise statement

    case GeneratorEquationAst::Type::PIECEWISE:
        if (ast->right() != nullptr) {
            if (ast->right()->type() == GeneratorEquationAst::Type::PIECE) {
                return generateCode(ast->left())+generatePiecewiseElseCode(generateCode(ast->right())+generatePiecewiseElseCode(mNan));
            }

            return generateCode(ast->left())+generatePiecewiseElseCode(generateCode(ast->right()));
        }

        return generateCode(ast->left())+generatePiecewiseElseCode(mNan);
    case GeneratorEquationAst::Type::PIECE:
        return generatePiecewiseIfCode(generateCode(ast->right()), generateCode(ast->left()));
    case GeneratorEquationAst::Type::OTHERWISE:
        return generateCode(ast->left());

    // Token elements

    case GeneratorEquationAst::Type::CN:
        return ast->value();
    case GeneratorEquationAst::Type::CI:
        return ast->variable()->name();

    // Qualifier elements

    case GeneratorEquationAst::Type::DEGREE:
    case GeneratorEquationAst::Type::LOGBASE:
    case GeneratorEquationAst::Type::BVAR:
        return generateCode(ast->left());

    // Constants

    case GeneratorEquationAst::Type::TRUE:
        return mTrue;
    case GeneratorEquationAst::Type::FALSE:
        return mFalse;
    case GeneratorEquationAst::Type::E:
        return mE;
    case GeneratorEquationAst::Type::PI:
        return mPi;
    case GeneratorEquationAst::Type::INF:
        return mInf;
    case GeneratorEquationAst::Type::NAN:
        return mNan;
    }

    return {}; // We can never reach this point, but it is needed to make MSVC happy...
}

Generator::Generator()
    : mPimpl(new GeneratorImpl())
{
    mPimpl->mGenerator = this;
}

Generator::~Generator()
{
    delete mPimpl;
}

Generator::Generator(const Generator &rhs)
    : Logger(rhs)
    , mPimpl(new GeneratorImpl())
{
//TODO: need to list all our private properties.
    mPimpl->mGenerator = rhs.mPimpl->mGenerator;

    mPimpl->mVariables = rhs.mPimpl->mVariables;
}

Generator::Generator(Generator &&rhs) noexcept
    : Logger(std::move(rhs))
    , mPimpl(rhs.mPimpl)
{
    rhs.mPimpl = nullptr;
}

Generator& Generator::operator=(Generator rhs)
{
    Logger::operator =(rhs);
    rhs.swap(*this);
    return *this;
}

void Generator::swap(Generator &rhs)
{
    std::swap(mPimpl, rhs.mPimpl);
}

void Generator::processModel(const ModelPtr &model)
{
    // Make sure that the model is valid before processing it

/*TODO: reenable the validation once it is known to work fine.
    libcellml::Validator validator;

    validator.validateModel(model);

    if (validator.errorCount() > 0) {
        // The model is not valid, so retrieve the validation errors and keep a
        // copy of them

        for (size_t i = 0; i < validator.errorCount(); ++i)
            addError(validator.getError(i));

        return;
    }
*/

    // Process the model

    mPimpl->processModel(model);
//TODO: remove the below code once we are done testing things...
for (size_t i = 0; i < errorCount(); ++i) {
    std::cout << "Generator error #" << i+1 << ": " << error(i)->description() << std::endl;
}
}

void Generator::setOptimize(bool optimize)
{
    mPimpl->mOptimize = optimize;
}

void Generator::setWithNames(bool withNames)
{
    mPimpl->mWithNames = withNames;
}

Generator::Type Generator::type() const
{
    if (errorCount() != 0) {
        return Generator::Type::UNKNOWN;
    }

    if (mPimpl->mVariableOfIntegration != nullptr) {
        return Generator::Type::ODE;
    }

    return Generator::Type::ALGEBRAIC;
}

size_t Generator::stateCount() const
{
    if (errorCount() != 0) {
        return 0;
    }

    size_t res = 0;

    for (const auto &variable : mPimpl->mVariables) {
        if (variable->type() == GeneratorVariable::Type::STATE) {
            ++res;
        }
    }

    return res;
}

size_t Generator::rateCount() const
{
    return stateCount();
}

size_t Generator::variableCount() const
{
    if (errorCount() != 0) {
        return 0;
    }

    size_t res = 0;

    for (const auto &variable : mPimpl->mVariables) {
        if (   (variable->type() == GeneratorVariable::Type::ALGEBRAIC)
            || (variable->type() == GeneratorVariable::Type::CONSTANT)
            || (variable->type() == GeneratorVariable::Type::COMPUTED_CONSTANT)) {
            ++res;
        }
    }

    return res;
}

std::string Generator::neededMathMethods() const
{
    return mPimpl->neededMathMethods();
}

std::string Generator::initializeVariables() const
{
    return mPimpl->initializeVariables();
}

std::string Generator::computeConstantEquations() const
{
    return mPimpl->computeConstantEquations();
}

std::string Generator::computeRateEquations() const
{
    return mPimpl->computeRateEquations();
}

std::string Generator::computeAlgebraicEquations() const
{
    return mPimpl->computeAlgebraicEquations();
}

} // namespace libcellml

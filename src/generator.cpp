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

#include "utilities.h"
#include "xmldoc.h"

#include <cmath>
#include <limits>
#include <vector>

#include "libcellml/component.h"
#include "libcellml/generator.h"
#include "libcellml/model.h"
#include "libcellml/validator.h"

#undef NAN

namespace libcellml{

class GeneratorEquationAst;
typedef std::shared_ptr<GeneratorEquationAst> GeneratorEquationAstPtr;

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

        // Token elements

        CN, CI,

        // Qualifier elements

        DEGREE, LOGBASE, BVAR,

        // Constants

        TRUE, FALSE, E, PI, INF, NAN
    };

    explicit GeneratorEquationAst(Type type, const std::string &value = "");

    Type type() const;

    std::string value() const;

    GeneratorEquationAstPtr &left();
    GeneratorEquationAstPtr &right();

private:
    Type mType;

    std::string mValue;

    GeneratorEquationAstPtr mLeft;
    GeneratorEquationAstPtr mRight;
};

GeneratorEquationAst::GeneratorEquationAst(Type type, const std::string &value)
    : mType(type)
    , mValue(value)
    , mLeft(nullptr)
    , mRight(nullptr)
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

GeneratorEquationAstPtr &GeneratorEquationAst::left()
{
    return mLeft;
}

GeneratorEquationAstPtr &GeneratorEquationAst::right()
{
    return mRight;
}

class GeneratorEquation;
typedef std::shared_ptr<GeneratorEquation> GeneratorEquationPtr;

class GeneratorEquation
{
public:
    explicit GeneratorEquation();

    GeneratorEquationAstPtr &binTree();

private:
    GeneratorEquationAstPtr mBinTree;
};

GeneratorEquation::GeneratorEquation()
    : mBinTree(std::make_shared<GeneratorEquationAst>(GeneratorEquationAst::Type::EQ))
{
}

GeneratorEquationAstPtr &GeneratorEquation::binTree()
{
    return mBinTree;
}

struct GeneratorVariable
{
};

typedef std::shared_ptr<GeneratorVariable> GeneratorVariablePtr;

struct Generator::GeneratorImpl
{
    bool mWithNames = true;

    std::vector<GeneratorEquationPtr> mEquations;

    std::vector<GeneratorVariablePtr> mStates;
    std::vector<GeneratorVariablePtr> mVariables;

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
    std::string mPow = "pow";
    std::string mSqrt = "sqrt";
    std::string mSqr = "sqr";
    std::string mAbs = "fabs";
    std::string mExp = "exp";
    std::string mLn = "log";
    std::string mLog = "log10";
    std::string mCeiling = "ceil";
    std::string mFloor = "floor";
    std::string mFactorial = "fact";

    bool mNeedFactorial = false;

    // Logical operators

    std::string mAnd = " && ";
    std::string mOr = " || ";
    std::string mXor = "^";
    std::string mNot = "!";

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

    // Constants

    std::string mTrue = "true";
    std::string mFalse = "false";
    std::string mE = convertDoubleToString(exp(1.0));
    std::string mPi = convertDoubleToString(M_PI);
    std::string mInf = "1.0/0.0";
    std::string mNan = "sqrt(-1.0)";

    size_t mathmlChildCount(const XmlNodePtr &node) const;
    XmlNodePtr mathmlChildNode(const XmlNodePtr &node, size_t index) const;

    void processNode(const XmlNodePtr &node);
    void processNode(const XmlNodePtr &node, GeneratorEquationAstPtr &binTree);

    std::string neededMathMethods() const;
    std::string initializeVariables() const;
    std::string computeConstantEquations() const;
    std::string computeRateEquations() const;
    std::string computeAlgebraicEquations() const;

    std::string generateCode(const GeneratorEquationAstPtr &binTree,
                             const GeneratorEquationAstPtr &parentBinTree = nullptr) const;
};

size_t Generator::GeneratorImpl::mathmlChildCount(const XmlNodePtr &node) const
{
    // Return the number of child elements, in the MathML namespace, for the
    // given node

    XmlNodePtr childNode = node->getFirstChild();
    size_t res = (childNode->isMathmlElement())?1:0;

    while (childNode != nullptr) {
        childNode = childNode->getNext();

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

    XmlNodePtr res = node->getFirstChild();
    size_t childNodeIndex = (res->isMathmlElement())?0:SIZE_T_MAX;

    while ((res != nullptr) && (childNodeIndex != index)) {
        res = res->getNext();

        if (res && res->isMathmlElement()) {
            ++childNodeIndex;
        }
    }

    return res;
}

void Generator::GeneratorImpl::processNode(const XmlNodePtr &node)
{
    // Create and keep track of the equation for the given node

    GeneratorEquationPtr equation = std::make_shared<GeneratorEquation>();

    mEquations.push_back(equation);

    // Actually process the node

    processNode(node, equation->binTree());
}

void Generator::GeneratorImpl::processNode(const XmlNodePtr &node,
                                           GeneratorEquationAstPtr &binTree)
{
    // Basic content elements

    if (node->isMathmlElement("apply")) {
        size_t childCount = mathmlChildCount(node);

        if (childCount <= 3) {
            // Case where we have 2 or 3 child nodes, e.g. "sin(a)" and "a+b",
            // which would translate into:
            //
            //     sin      and      +
            //     / \              / \
            //    a  nil           a   b

            processNode(mathmlChildNode(node, 0), binTree);
            processNode(mathmlChildNode(node, 1), binTree->left());

            if (childCount == 3) {
                processNode(mathmlChildNode(node, 2), binTree->right());
            }
        } else {
            // Case where we have more than 3 child nodes, e.g. "a+b+c+d+e",
            // which would translate into:
            //
            //      +
            //     / \
            //    a   +
            //       / \
            //      b   +
            //         / \
            //        c   +
            //           / \
            //          d   e

            GeneratorEquationAstPtr subBinTree;

            processNode(mathmlChildNode(node, 0), subBinTree);
            processNode(mathmlChildNode(node, childCount-2), subBinTree->left());
            processNode(mathmlChildNode(node, childCount-1), subBinTree->right());

            for (size_t i = childCount-3; i >= 1; --i) {
                processNode(mathmlChildNode(node, 0), binTree);
                processNode(mathmlChildNode(node, i), binTree->left());

                binTree->right() = subBinTree;
                subBinTree = binTree;
            }
        }

    // Relational operators

    } else if (node->isMathmlElement("eq")) {
        // This element is used both to describe "a = b" and "a == b". We can
        // distinguish between the two by checking its grand-parent. If it's a
        // "math" MathML element then it means that it is used to describe
        // "a = b" otherwise it is used to describe "a == b". In the former
        // case, there is nothing more we need to do since binTree is already of
        // GeneratorEquationBinTree::Type::EQ type.

        if (!node->getParent()->getParent()->isMathmlElement("math")) {
            binTree = std::make_shared<GeneratorEquationAst>(GeneratorEquationAst::Type::EQEQ);
        }
    } else if (node->isMathmlElement("neq")) {
        binTree = std::make_shared<GeneratorEquationAst>(GeneratorEquationAst::Type::NEQ);
    } else if (node->isMathmlElement("lt")) {
        binTree = std::make_shared<GeneratorEquationAst>(GeneratorEquationAst::Type::LT);
    } else if (node->isMathmlElement("leq")) {
        binTree = std::make_shared<GeneratorEquationAst>(GeneratorEquationAst::Type::LEQ);
    } else if (node->isMathmlElement("gt")) {
        binTree = std::make_shared<GeneratorEquationAst>(GeneratorEquationAst::Type::GT);
    } else if (node->isMathmlElement("geq")) {
        binTree = std::make_shared<GeneratorEquationAst>(GeneratorEquationAst::Type::GEQ);

    // Arithmetic operators

    } else if (node->isMathmlElement("plus")) {
        binTree = std::make_shared<GeneratorEquationAst>(GeneratorEquationAst::Type::PLUS);
    } else if (node->isMathmlElement("minus")) {
        binTree = std::make_shared<GeneratorEquationAst>(GeneratorEquationAst::Type::MINUS);
    } else if (node->isMathmlElement("times")) {
        binTree = std::make_shared<GeneratorEquationAst>(GeneratorEquationAst::Type::TIMES);
    } else if (node->isMathmlElement("divide")) {
        binTree = std::make_shared<GeneratorEquationAst>(GeneratorEquationAst::Type::DIVIDE);
    } else if (node->isMathmlElement("power")) {
        binTree = std::make_shared<GeneratorEquationAst>(GeneratorEquationAst::Type::POWER);
    } else if (node->isMathmlElement("root")) {
        binTree = std::make_shared<GeneratorEquationAst>(GeneratorEquationAst::Type::ROOT);
    } else if (node->isMathmlElement("abs")) {
        binTree = std::make_shared<GeneratorEquationAst>(GeneratorEquationAst::Type::ABS);
    } else if (node->isMathmlElement("exp")) {
        binTree = std::make_shared<GeneratorEquationAst>(GeneratorEquationAst::Type::EXP);
    } else if (node->isMathmlElement("ln")) {
        binTree = std::make_shared<GeneratorEquationAst>(GeneratorEquationAst::Type::LN);
    } else if (node->isMathmlElement("log")) {
        binTree = std::make_shared<GeneratorEquationAst>(GeneratorEquationAst::Type::LOG);
    } else if (node->isMathmlElement("ceiling")) {
        binTree = std::make_shared<GeneratorEquationAst>(GeneratorEquationAst::Type::CEILING);
    } else if (node->isMathmlElement("floor")) {
        binTree = std::make_shared<GeneratorEquationAst>(GeneratorEquationAst::Type::FLOOR);
    } else if (node->isMathmlElement("factorial")) {
        binTree = std::make_shared<GeneratorEquationAst>(GeneratorEquationAst::Type::FACTORIAL);

        mNeedFactorial = true;

    // Logical operators

    } else if (node->isMathmlElement("and")) {
        binTree = std::make_shared<GeneratorEquationAst>(GeneratorEquationAst::Type::AND);
    } else if (node->isMathmlElement("or")) {
        binTree = std::make_shared<GeneratorEquationAst>(GeneratorEquationAst::Type::OR);
    } else if (node->isMathmlElement("xor")) {
        binTree = std::make_shared<GeneratorEquationAst>(GeneratorEquationAst::Type::XOR);
    } else if (node->isMathmlElement("not")) {
        binTree = std::make_shared<GeneratorEquationAst>(GeneratorEquationAst::Type::NOT);

    // Calculus elements

    } else if (node->isMathmlElement("diff")) {
        binTree = std::make_shared<GeneratorEquationAst>(GeneratorEquationAst::Type::DIFF);

    // Min/max operators

    } else if (node->isMathmlElement("min")) {
        binTree = std::make_shared<GeneratorEquationAst>(GeneratorEquationAst::Type::MIN);

        mNeedMin = true;
    } else if (node->isMathmlElement("max")) {
        binTree = std::make_shared<GeneratorEquationAst>(GeneratorEquationAst::Type::MAX);

        mNeedMax = true;

    // Gcd/lcm operators

    } else if (node->isMathmlElement("gcd")) {
        binTree = std::make_shared<GeneratorEquationAst>(GeneratorEquationAst::Type::GCD);

        mNeedGcd = true;
    } else if (node->isMathmlElement("lcm")) {
        binTree = std::make_shared<GeneratorEquationAst>(GeneratorEquationAst::Type::LCM);

        mNeedLcm = true;

    // Trigonometric operators

    } else if (node->isMathmlElement("sin")) {
        binTree = std::make_shared<GeneratorEquationAst>(GeneratorEquationAst::Type::SIN);
    } else if (node->isMathmlElement("cos")) {
        binTree = std::make_shared<GeneratorEquationAst>(GeneratorEquationAst::Type::COS);
    } else if (node->isMathmlElement("tan")) {
        binTree = std::make_shared<GeneratorEquationAst>(GeneratorEquationAst::Type::TAN);
    } else if (node->isMathmlElement("sec")) {
        binTree = std::make_shared<GeneratorEquationAst>(GeneratorEquationAst::Type::SEC);

        mNeedSec = true;
    } else if (node->isMathmlElement("csc")) {
        binTree = std::make_shared<GeneratorEquationAst>(GeneratorEquationAst::Type::CSC);

        mNeedCsc = true;
    } else if (node->isMathmlElement("cot")) {
        binTree = std::make_shared<GeneratorEquationAst>(GeneratorEquationAst::Type::COT);

        mNeedCot = true;
    } else if (node->isMathmlElement("sinh")) {
        binTree = std::make_shared<GeneratorEquationAst>(GeneratorEquationAst::Type::SINH);
    } else if (node->isMathmlElement("cosh")) {
        binTree = std::make_shared<GeneratorEquationAst>(GeneratorEquationAst::Type::COSH);
    } else if (node->isMathmlElement("tanh")) {
        binTree = std::make_shared<GeneratorEquationAst>(GeneratorEquationAst::Type::TANH);
    } else if (node->isMathmlElement("sech")) {
        binTree = std::make_shared<GeneratorEquationAst>(GeneratorEquationAst::Type::SECH);

        mNeedSech = true;
    } else if (node->isMathmlElement("csch")) {
        binTree = std::make_shared<GeneratorEquationAst>(GeneratorEquationAst::Type::CSCH);

        mNeedCsch = true;
    } else if (node->isMathmlElement("coth")) {
        binTree = std::make_shared<GeneratorEquationAst>(GeneratorEquationAst::Type::COTH);

        mNeedCoth = true;
    } else if (node->isMathmlElement("arcsin")) {
        binTree = std::make_shared<GeneratorEquationAst>(GeneratorEquationAst::Type::ASIN);
    } else if (node->isMathmlElement("arccos")) {
        binTree = std::make_shared<GeneratorEquationAst>(GeneratorEquationAst::Type::ACOS);
    } else if (node->isMathmlElement("arctan")) {
        binTree = std::make_shared<GeneratorEquationAst>(GeneratorEquationAst::Type::ATAN);
    } else if (node->isMathmlElement("arcsec")) {
        binTree = std::make_shared<GeneratorEquationAst>(GeneratorEquationAst::Type::ASEC);

        mNeedAsec = true;
    } else if (node->isMathmlElement("arccsc")) {
        binTree = std::make_shared<GeneratorEquationAst>(GeneratorEquationAst::Type::ACSC);

        mNeedAcsc = true;
    } else if (node->isMathmlElement("arccot")) {
        binTree = std::make_shared<GeneratorEquationAst>(GeneratorEquationAst::Type::ACOT);

        mNeedAcot = true;
    } else if (node->isMathmlElement("arcsinh")) {
        binTree = std::make_shared<GeneratorEquationAst>(GeneratorEquationAst::Type::ASINH);
    } else if (node->isMathmlElement("arccosh")) {
        binTree = std::make_shared<GeneratorEquationAst>(GeneratorEquationAst::Type::ACOSH);
    } else if (node->isMathmlElement("arctanh")) {
        binTree = std::make_shared<GeneratorEquationAst>(GeneratorEquationAst::Type::ATANH);
    } else if (node->isMathmlElement("arcsech")) {
        binTree = std::make_shared<GeneratorEquationAst>(GeneratorEquationAst::Type::ASECH);

        mNeedAsech = true;
    } else if (node->isMathmlElement("arccsch")) {
        binTree = std::make_shared<GeneratorEquationAst>(GeneratorEquationAst::Type::ACSCH);

        mNeedAcsch = true;
    } else if (node->isMathmlElement("arccoth")) {
        binTree = std::make_shared<GeneratorEquationAst>(GeneratorEquationAst::Type::ACOTH);

        mNeedAcoth = true;

    // Extra operators

    } else if (node->isMathmlElement("rem")) {
        binTree = std::make_shared<GeneratorEquationAst>(GeneratorEquationAst::Type::REM);

    // Token elements

    } else if (node->isMathmlElement("cn")) {
        binTree = std::make_shared<GeneratorEquationAst>(GeneratorEquationAst::Type::CN, node->getFirstChild()->convertToString());
    } else if (node->isMathmlElement("ci")) {
        binTree = std::make_shared<GeneratorEquationAst>(GeneratorEquationAst::Type::CI, node->getFirstChild()->convertToString());

    // Qualifier elements

    } else if (node->isMathmlElement("degree")) {
        binTree = std::make_shared<GeneratorEquationAst>(GeneratorEquationAst::Type::DEGREE);

        processNode(mathmlChildNode(node, 0), binTree->left());
    } else if (node->isMathmlElement("logbase")) {
        binTree = std::make_shared<GeneratorEquationAst>(GeneratorEquationAst::Type::LOGBASE);

        processNode(mathmlChildNode(node, 0), binTree->left());
    } else if (node->isMathmlElement("bvar")) {
        binTree = std::make_shared<GeneratorEquationAst>(GeneratorEquationAst::Type::BVAR);

        processNode(mathmlChildNode(node, 0), binTree->left());

    // Constants

    } else if (node->isMathmlElement("true")) {
        binTree = std::make_shared<GeneratorEquationAst>(GeneratorEquationAst::Type::TRUE);
    } else if (node->isMathmlElement("false")) {
        binTree = std::make_shared<GeneratorEquationAst>(GeneratorEquationAst::Type::FALSE);
    } else if (node->isMathmlElement("exponentiale")) {
        binTree = std::make_shared<GeneratorEquationAst>(GeneratorEquationAst::Type::E);
    } else if (node->isMathmlElement("pi")) {
        binTree = std::make_shared<GeneratorEquationAst>(GeneratorEquationAst::Type::PI);
    } else if (node->isMathmlElement("infinity")) {
        binTree = std::make_shared<GeneratorEquationAst>(GeneratorEquationAst::Type::INF);
    } else if (node->isMathmlElement("notanumber")) {
        binTree = std::make_shared<GeneratorEquationAst>(GeneratorEquationAst::Type::NAN);
    }
}

std::string Generator::GeneratorImpl::neededMathMethods() const
{
    return "";
}

std::string Generator::GeneratorImpl::initializeVariables() const
{
    return "";
}

std::string Generator::GeneratorImpl::computeConstantEquations() const
{
    return "";
}

std::string Generator::GeneratorImpl::computeRateEquations() const
{
    return "";
}

std::string Generator::GeneratorImpl::computeAlgebraicEquations() const
{
    return "";
}

std::string Generator::GeneratorImpl::generateCode(const GeneratorEquationAstPtr &binTree,
                                                   const GeneratorEquationAstPtr &parentBinTree) const
{
    // Generate the code for the given (equation) binary tree

    std::string stringValue;
    double doubleValue;

    switch (binTree->type()) {
    // Relational operators

    case GeneratorEquationAst::Type::EQ:
        return generateCode(binTree->left())+mEq+generateCode(binTree->right());
    case GeneratorEquationAst::Type::EQEQ:
        return generateCode(binTree->left())+mEqEq+generateCode(binTree->right());
    case GeneratorEquationAst::Type::NEQ:
        return generateCode(binTree->left())+mNeq+generateCode(binTree->right());
    case GeneratorEquationAst::Type::LT:
        return generateCode(binTree->left())+mLt+generateCode(binTree->right());
    case GeneratorEquationAst::Type::LEQ:
        return generateCode(binTree->left())+mLeq+generateCode(binTree->right());
    case GeneratorEquationAst::Type::GT:
        return generateCode(binTree->left())+mGt+generateCode(binTree->right());
    case GeneratorEquationAst::Type::GEQ:
        return generateCode(binTree->left())+mGeq+generateCode(binTree->right());

    // Arithmetic operators

    case GeneratorEquationAst::Type::PLUS:
        if (binTree->right()) {
            return generateCode(binTree->left())+mPlus+generateCode(binTree->right());
        }

        return mPlus+generateCode(binTree->left());
    case GeneratorEquationAst::Type::MINUS:
        if (binTree->right()) {
            return generateCode(binTree->left())+mMinus+generateCode(binTree->right());
        }

        return mMinus+generateCode(binTree->left());
    case GeneratorEquationAst::Type::TIMES:
        return generateCode(binTree->left())+mTimes+generateCode(binTree->right());
    case GeneratorEquationAst::Type::DIVIDE:
        return generateCode(binTree->left())+mDivide+generateCode(binTree->right());
    case GeneratorEquationAst::Type::POWER:
        stringValue = generateCode(binTree->right());
        doubleValue = convertToDouble(stringValue);

        if (isEqual(doubleValue, 0.5)) {
            return mSqrt+"("+generateCode(binTree->left())+")";
        }

        if (isEqual(doubleValue, 2.0)) {
            return mSqr+"("+generateCode(binTree->left())+")";
        }

        return mPow+"("+generateCode(binTree->left())+", "+stringValue+")";
    case GeneratorEquationAst::Type::ROOT:
        if (binTree->right()) {
            stringValue = generateCode(binTree->left());
            doubleValue = convertToDouble(stringValue);

            if (isEqual(doubleValue, 2.0)) {
                return mSqrt+"("+generateCode(binTree->right())+")";
            }

            return mPow+"("+generateCode(binTree->right())+", 1.0/"+stringValue+")";
        }

        return mSqrt+"("+generateCode(binTree->left())+")";
    case GeneratorEquationAst::Type::ABS:
        return mAbs+"("+generateCode(binTree->left())+")";
    case GeneratorEquationAst::Type::EXP:
        return mExp+"("+generateCode(binTree->left())+")";
    case GeneratorEquationAst::Type::LN:
        return mLn+"("+generateCode(binTree->left())+")";
    case GeneratorEquationAst::Type::LOG:
        if (binTree->right()) {
            stringValue = generateCode(binTree->left());
            doubleValue = convertToDouble(stringValue);

            if (isEqual(doubleValue, 10.0)) {
                return mLog+"("+generateCode(binTree->right())+")";
            }

            return mLn+"("+generateCode(binTree->right())+")/"+mLn+"("+stringValue+")";
        }

        return mLog+"("+generateCode(binTree->left())+")";
    case GeneratorEquationAst::Type::CEILING:
        return mCeiling+"("+generateCode(binTree->left())+")";
    case GeneratorEquationAst::Type::FLOOR:
        return mFloor+"("+generateCode(binTree->left())+")";
    case GeneratorEquationAst::Type::FACTORIAL:
        return mFactorial+"("+generateCode(binTree->left())+")";

    // Logical operators

    case GeneratorEquationAst::Type::AND:
        return generateCode(binTree->left())+mAnd+generateCode(binTree->right());
    case GeneratorEquationAst::Type::OR:
        return generateCode(binTree->left())+mOr+generateCode(binTree->right());
    case GeneratorEquationAst::Type::XOR:
        return generateCode(binTree->left())+mXor+generateCode(binTree->right());
    case GeneratorEquationAst::Type::NOT:
        return mNot+generateCode(binTree->left());

    // Calculus elements

    case GeneratorEquationAst::Type::DIFF:
        return "d("+generateCode(binTree->right())+")/d("+generateCode(binTree->left())+")";

    // Min/max operators

    case GeneratorEquationAst::Type::MIN:
        if (parentBinTree == nullptr) {
            return mMin+"("+generateCode(binTree->left(), binTree)+", "+generateCode(binTree->right(), binTree)+")";
        }

        return generateCode(binTree->left(), binTree)+", "+generateCode(binTree->right(), binTree);
    case GeneratorEquationAst::Type::MAX:
        if (parentBinTree == nullptr) {
            return mMax+"("+generateCode(binTree->left(), binTree)+", "+generateCode(binTree->right(), binTree)+")";
        }

        return generateCode(binTree->left(), binTree)+", "+generateCode(binTree->right(), binTree);

    // Gcd/lcm operators

    case GeneratorEquationAst::Type::GCD:
        if (parentBinTree == nullptr) {
            return mGcd+"("+generateCode(binTree->left(), binTree)+", "+generateCode(binTree->right(), binTree)+")";
        }

        return generateCode(binTree->left(), binTree)+", "+generateCode(binTree->right(), binTree);
    case GeneratorEquationAst::Type::LCM:
        if (parentBinTree == nullptr) {
            return mLcm+"("+generateCode(binTree->left(), binTree)+", "+generateCode(binTree->right(), binTree)+")";
        }

        return generateCode(binTree->left(), binTree)+", "+generateCode(binTree->right(), binTree);

    // Trigonometric operators

    case GeneratorEquationAst::Type::SIN:
        return mSin+"("+generateCode(binTree->left())+")";
    case GeneratorEquationAst::Type::COS:
        return mCos+"("+generateCode(binTree->left())+")";
    case GeneratorEquationAst::Type::TAN:
        return mTan+"("+generateCode(binTree->left())+")";
    case GeneratorEquationAst::Type::SEC:
        return mSec+"("+generateCode(binTree->left())+")";
    case GeneratorEquationAst::Type::CSC:
        return mCsc+"("+generateCode(binTree->left())+")";
    case GeneratorEquationAst::Type::COT:
        return mCot+"("+generateCode(binTree->left())+")";
    case GeneratorEquationAst::Type::SINH:
        return mSinh+"("+generateCode(binTree->left())+")";
    case GeneratorEquationAst::Type::COSH:
        return mCosh+"("+generateCode(binTree->left())+")";
    case GeneratorEquationAst::Type::TANH:
        return mTanh+"("+generateCode(binTree->left())+")";
    case GeneratorEquationAst::Type::SECH:
        return mSech+"("+generateCode(binTree->left())+")";
    case GeneratorEquationAst::Type::CSCH:
        return mCsch+"("+generateCode(binTree->left())+")";
    case GeneratorEquationAst::Type::COTH:
        return mCoth+"("+generateCode(binTree->left())+")";
    case GeneratorEquationAst::Type::ASIN:
        return mAsin+"("+generateCode(binTree->left())+")";
    case GeneratorEquationAst::Type::ACOS:
        return mAcos+"("+generateCode(binTree->left())+")";
    case GeneratorEquationAst::Type::ATAN:
        return mAtan+"("+generateCode(binTree->left())+")";
    case GeneratorEquationAst::Type::ASEC:
        return mAsec+"("+generateCode(binTree->left())+")";
    case GeneratorEquationAst::Type::ACSC:
        return mAcsc+"("+generateCode(binTree->left())+")";
    case GeneratorEquationAst::Type::ACOT:
        return mAcot+"("+generateCode(binTree->left())+")";
    case GeneratorEquationAst::Type::ASINH:
        return mAsinh+"("+generateCode(binTree->left())+")";
    case GeneratorEquationAst::Type::ACOSH:
        return mAcosh+"("+generateCode(binTree->left())+")";
    case GeneratorEquationAst::Type::ATANH:
        return mAtanh+"("+generateCode(binTree->left())+")";
    case GeneratorEquationAst::Type::ASECH:
        return mAsech+"("+generateCode(binTree->left())+")";
    case GeneratorEquationAst::Type::ACSCH:
        return mAcsch+"("+generateCode(binTree->left())+")";
    case GeneratorEquationAst::Type::ACOTH:
        return mAcoth+"("+generateCode(binTree->left())+")";

    // Extra operators

    case GeneratorEquationAst::Type::REM:
        return mRem+"("+generateCode(binTree->left())+", "+generateCode(binTree->right())+")";

    // Token elements

    case GeneratorEquationAst::Type::CN:
    case GeneratorEquationAst::Type::CI:
        return binTree->value();

    // Qualifier elements

    case GeneratorEquationAst::Type::DEGREE:
    case GeneratorEquationAst::Type::LOGBASE:
    case GeneratorEquationAst::Type::BVAR:
        return generateCode(binTree->left());

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
}

Generator::Generator()
    : mPimpl(new GeneratorImpl())
{
}

Generator::~Generator()
{
    delete mPimpl;
}

Generator::Generator(const Generator &rhs)
    : Logger(rhs)
    , mPimpl(new GeneratorImpl())
{
    mPimpl->mStates = rhs.mPimpl->mStates;
    mPimpl->mVariables = rhs.mPimpl->mVariables;
}

Generator::Generator(Generator &&rhs)
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
    std::swap(this->mPimpl, rhs.mPimpl);
}

void Generator::processModel(const ModelPtr &model)
{
    // Make sure that the model is valid before processing it

/*TODO: reenable the validation once it is known to work fine...
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

    // Determine the order in which equations should be executed by processing
    // each of the components in the given model

    for (size_t i = 0; i < model->componentCount(); ++i) {
        // Retrieve the math string associated with the given component and
        // process it, one equation at a time
        // Note: at this stage, we know the model is valid, so no point in
        //       revalidating each math string...

        ComponentPtr component = model->getComponent(i);
        XmlDocPtr xmlDoc = std::make_shared<XmlDoc>();
        std::string math = component->getMath();

        if (!math.empty()) {
            xmlDoc->parse(math);

            XmlNodePtr mathNode = xmlDoc->getRootNode();

            for (XmlNodePtr node = mathNode->getFirstChild();
                 node != nullptr; node = node->getNext()) {
                if (node->isMathmlElement()) {
                    mPimpl->processNode(node);
                }
            }
        }
    }

    // Generate the code for our different equations
//TODO: remove the below once we are done testing things...

    printf("%s", mPimpl->neededMathMethods().c_str());

    for (auto equation : mPimpl->mEquations) {
        printf("%s;\n", mPimpl->generateCode(equation->binTree()).c_str());
    }
}

void Generator::setWithNames(bool withNames)
{
    mPimpl->mWithNames = withNames;
}

size_t Generator::stateCount() const
{
    return mPimpl->mStates.size();
}

size_t Generator::rateCount() const
{
    return stateCount();
}

size_t Generator::variableCount() const
{
    return mPimpl->mVariables.size();
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

}

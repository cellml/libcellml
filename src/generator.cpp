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

#include <cmath>
#include <limits>
#include <vector>

#include "libcellml/component.h"
#include "libcellml/generator.h"
#include "libcellml/model.h"
#include "libcellml/validator.h"

#undef NAN

#ifdef __linux__
#   undef TRUE
#   undef FALSE
#endif

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

        // Piecewise statement

        PIECEWISE, PIECE, OTHERWISE,

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

    GeneratorEquationAstPtr &ast();

private:
    GeneratorEquationAstPtr mAst;
};

GeneratorEquation::GeneratorEquation()
    : mAst(std::make_shared<GeneratorEquationAst>(GeneratorEquationAst::Type::EQ))
{
}

GeneratorEquationAstPtr &GeneratorEquation::ast()
{
    return mAst;
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
    void processNode(const XmlNodePtr &node, GeneratorEquationAstPtr &ast);

    void processComponent(const ComponentPtr &component);

    std::string neededMathMethods() const;
    std::string initializeVariables() const;
    std::string computeConstantEquations() const;
    std::string computeRateEquations() const;
    std::string computeAlgebraicEquations() const;

    std::string generateCode(const GeneratorEquationAstPtr &ast,
                             const GeneratorEquationAstPtr &parentAst = nullptr) const;
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

    static const size_t MAX_SIZE_T = std::numeric_limits<std::size_t>::max();

    XmlNodePtr res = node->getFirstChild();
    size_t childNodeIndex = (res->isMathmlElement())?0:MAX_SIZE_T;

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

    processNode(node, equation->ast());
}

void Generator::GeneratorImpl::processNode(const XmlNodePtr &node,
                                           GeneratorEquationAstPtr &ast)
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

        processNode(mathmlChildNode(node, 0), ast);
        processNode(mathmlChildNode(node, 1), ast->left());

        if (childCount >= 3) {
            GeneratorEquationAstPtr astRight;
            GeneratorEquationAstPtr tempAst;

            processNode(mathmlChildNode(node, childCount-1), astRight);

            for (size_t i = childCount-2; i > 1; --i) {
                processNode(mathmlChildNode(node, 0), tempAst);
                processNode(mathmlChildNode(node, i), tempAst->left());

                tempAst->right() = astRight;
                astRight = tempAst;
            }

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

        if (!node->getParent()->getParent()->isMathmlElement("math")) {
            ast = std::make_shared<GeneratorEquationAst>(GeneratorEquationAst::Type::EQEQ);
        }
    } else if (node->isMathmlElement("neq")) {
        ast = std::make_shared<GeneratorEquationAst>(GeneratorEquationAst::Type::NEQ);
    } else if (node->isMathmlElement("lt")) {
        ast = std::make_shared<GeneratorEquationAst>(GeneratorEquationAst::Type::LT);
    } else if (node->isMathmlElement("leq")) {
        ast = std::make_shared<GeneratorEquationAst>(GeneratorEquationAst::Type::LEQ);
    } else if (node->isMathmlElement("gt")) {
        ast = std::make_shared<GeneratorEquationAst>(GeneratorEquationAst::Type::GT);
    } else if (node->isMathmlElement("geq")) {
        ast = std::make_shared<GeneratorEquationAst>(GeneratorEquationAst::Type::GEQ);

    // Arithmetic operators

    } else if (node->isMathmlElement("plus")) {
        ast = std::make_shared<GeneratorEquationAst>(GeneratorEquationAst::Type::PLUS);
    } else if (node->isMathmlElement("minus")) {
        ast = std::make_shared<GeneratorEquationAst>(GeneratorEquationAst::Type::MINUS);
    } else if (node->isMathmlElement("times")) {
        ast = std::make_shared<GeneratorEquationAst>(GeneratorEquationAst::Type::TIMES);
    } else if (node->isMathmlElement("divide")) {
        ast = std::make_shared<GeneratorEquationAst>(GeneratorEquationAst::Type::DIVIDE);
    } else if (node->isMathmlElement("power")) {
        ast = std::make_shared<GeneratorEquationAst>(GeneratorEquationAst::Type::POWER);
    } else if (node->isMathmlElement("root")) {
        ast = std::make_shared<GeneratorEquationAst>(GeneratorEquationAst::Type::ROOT);
    } else if (node->isMathmlElement("abs")) {
        ast = std::make_shared<GeneratorEquationAst>(GeneratorEquationAst::Type::ABS);
    } else if (node->isMathmlElement("exp")) {
        ast = std::make_shared<GeneratorEquationAst>(GeneratorEquationAst::Type::EXP);
    } else if (node->isMathmlElement("ln")) {
        ast = std::make_shared<GeneratorEquationAst>(GeneratorEquationAst::Type::LN);
    } else if (node->isMathmlElement("log")) {
        ast = std::make_shared<GeneratorEquationAst>(GeneratorEquationAst::Type::LOG);
    } else if (node->isMathmlElement("ceiling")) {
        ast = std::make_shared<GeneratorEquationAst>(GeneratorEquationAst::Type::CEILING);
    } else if (node->isMathmlElement("floor")) {
        ast = std::make_shared<GeneratorEquationAst>(GeneratorEquationAst::Type::FLOOR);
    } else if (node->isMathmlElement("factorial")) {
        ast = std::make_shared<GeneratorEquationAst>(GeneratorEquationAst::Type::FACTORIAL);

        mNeedFactorial = true;

    // Logical operators

    } else if (node->isMathmlElement("and")) {
        ast = std::make_shared<GeneratorEquationAst>(GeneratorEquationAst::Type::AND);
    } else if (node->isMathmlElement("or")) {
        ast = std::make_shared<GeneratorEquationAst>(GeneratorEquationAst::Type::OR);
    } else if (node->isMathmlElement("xor")) {
        ast = std::make_shared<GeneratorEquationAst>(GeneratorEquationAst::Type::XOR);
    } else if (node->isMathmlElement("not")) {
        ast = std::make_shared<GeneratorEquationAst>(GeneratorEquationAst::Type::NOT);

    // Calculus elements

    } else if (node->isMathmlElement("diff")) {
        ast = std::make_shared<GeneratorEquationAst>(GeneratorEquationAst::Type::DIFF);

    // Min/max operators

    } else if (node->isMathmlElement("min")) {
        ast = std::make_shared<GeneratorEquationAst>(GeneratorEquationAst::Type::MIN);

        mNeedMin = true;
    } else if (node->isMathmlElement("max")) {
        ast = std::make_shared<GeneratorEquationAst>(GeneratorEquationAst::Type::MAX);

        mNeedMax = true;

    // Gcd/lcm operators

    } else if (node->isMathmlElement("gcd")) {
        ast = std::make_shared<GeneratorEquationAst>(GeneratorEquationAst::Type::GCD);

        mNeedGcd = true;
    } else if (node->isMathmlElement("lcm")) {
        ast = std::make_shared<GeneratorEquationAst>(GeneratorEquationAst::Type::LCM);

        mNeedLcm = true;

    // Trigonometric operators

    } else if (node->isMathmlElement("sin")) {
        ast = std::make_shared<GeneratorEquationAst>(GeneratorEquationAst::Type::SIN);
    } else if (node->isMathmlElement("cos")) {
        ast = std::make_shared<GeneratorEquationAst>(GeneratorEquationAst::Type::COS);
    } else if (node->isMathmlElement("tan")) {
        ast = std::make_shared<GeneratorEquationAst>(GeneratorEquationAst::Type::TAN);
    } else if (node->isMathmlElement("sec")) {
        ast = std::make_shared<GeneratorEquationAst>(GeneratorEquationAst::Type::SEC);

        mNeedSec = true;
    } else if (node->isMathmlElement("csc")) {
        ast = std::make_shared<GeneratorEquationAst>(GeneratorEquationAst::Type::CSC);

        mNeedCsc = true;
    } else if (node->isMathmlElement("cot")) {
        ast = std::make_shared<GeneratorEquationAst>(GeneratorEquationAst::Type::COT);

        mNeedCot = true;
    } else if (node->isMathmlElement("sinh")) {
        ast = std::make_shared<GeneratorEquationAst>(GeneratorEquationAst::Type::SINH);
    } else if (node->isMathmlElement("cosh")) {
        ast = std::make_shared<GeneratorEquationAst>(GeneratorEquationAst::Type::COSH);
    } else if (node->isMathmlElement("tanh")) {
        ast = std::make_shared<GeneratorEquationAst>(GeneratorEquationAst::Type::TANH);
    } else if (node->isMathmlElement("sech")) {
        ast = std::make_shared<GeneratorEquationAst>(GeneratorEquationAst::Type::SECH);

        mNeedSech = true;
    } else if (node->isMathmlElement("csch")) {
        ast = std::make_shared<GeneratorEquationAst>(GeneratorEquationAst::Type::CSCH);

        mNeedCsch = true;
    } else if (node->isMathmlElement("coth")) {
        ast = std::make_shared<GeneratorEquationAst>(GeneratorEquationAst::Type::COTH);

        mNeedCoth = true;
    } else if (node->isMathmlElement("arcsin")) {
        ast = std::make_shared<GeneratorEquationAst>(GeneratorEquationAst::Type::ASIN);
    } else if (node->isMathmlElement("arccos")) {
        ast = std::make_shared<GeneratorEquationAst>(GeneratorEquationAst::Type::ACOS);
    } else if (node->isMathmlElement("arctan")) {
        ast = std::make_shared<GeneratorEquationAst>(GeneratorEquationAst::Type::ATAN);
    } else if (node->isMathmlElement("arcsec")) {
        ast = std::make_shared<GeneratorEquationAst>(GeneratorEquationAst::Type::ASEC);

        mNeedAsec = true;
    } else if (node->isMathmlElement("arccsc")) {
        ast = std::make_shared<GeneratorEquationAst>(GeneratorEquationAst::Type::ACSC);

        mNeedAcsc = true;
    } else if (node->isMathmlElement("arccot")) {
        ast = std::make_shared<GeneratorEquationAst>(GeneratorEquationAst::Type::ACOT);

        mNeedAcot = true;
    } else if (node->isMathmlElement("arcsinh")) {
        ast = std::make_shared<GeneratorEquationAst>(GeneratorEquationAst::Type::ASINH);
    } else if (node->isMathmlElement("arccosh")) {
        ast = std::make_shared<GeneratorEquationAst>(GeneratorEquationAst::Type::ACOSH);
    } else if (node->isMathmlElement("arctanh")) {
        ast = std::make_shared<GeneratorEquationAst>(GeneratorEquationAst::Type::ATANH);
    } else if (node->isMathmlElement("arcsech")) {
        ast = std::make_shared<GeneratorEquationAst>(GeneratorEquationAst::Type::ASECH);

        mNeedAsech = true;
    } else if (node->isMathmlElement("arccsch")) {
        ast = std::make_shared<GeneratorEquationAst>(GeneratorEquationAst::Type::ACSCH);

        mNeedAcsch = true;
    } else if (node->isMathmlElement("arccoth")) {
        ast = std::make_shared<GeneratorEquationAst>(GeneratorEquationAst::Type::ACOTH);

        mNeedAcoth = true;

    // Extra operators

    } else if (node->isMathmlElement("rem")) {
        ast = std::make_shared<GeneratorEquationAst>(GeneratorEquationAst::Type::REM);

    // Piecewise statement

    } else if (node->isMathmlElement("piecewise")) {
        size_t childCount = mathmlChildCount(node);

        ast = std::make_shared<GeneratorEquationAst>(GeneratorEquationAst::Type::PIECEWISE);

        processNode(mathmlChildNode(node, 0), ast->left());

        if (childCount >= 2) {
            GeneratorEquationAstPtr astRight;
            GeneratorEquationAstPtr tempAst;

            processNode(mathmlChildNode(node, childCount-1), astRight);

            for (size_t i = childCount-2; i > 0; --i) {
                tempAst = std::make_shared<GeneratorEquationAst>(GeneratorEquationAst::Type::PIECEWISE);

                processNode(mathmlChildNode(node, i), tempAst->left());

                tempAst->right() = astRight;
                astRight = tempAst;
            }

            ast->right() = astRight;
        }
    } else if (node->isMathmlElement("piece")) {
        ast = std::make_shared<GeneratorEquationAst>(GeneratorEquationAst::Type::PIECE);

        processNode(mathmlChildNode(node, 0), ast->left());
        processNode(mathmlChildNode(node, 1), ast->right());
    } else if (node->isMathmlElement("otherwise")) {
        ast = std::make_shared<GeneratorEquationAst>(GeneratorEquationAst::Type::OTHERWISE);

        processNode(mathmlChildNode(node, 0), ast->left());

    // Token elements

    } else if (node->isMathmlElement("cn")) {
        ast = std::make_shared<GeneratorEquationAst>(GeneratorEquationAst::Type::CN, node->getFirstChild()->convertToString());
    } else if (node->isMathmlElement("ci")) {
        ast = std::make_shared<GeneratorEquationAst>(GeneratorEquationAst::Type::CI, node->getFirstChild()->convertToString());

    // Qualifier elements

    } else if (node->isMathmlElement("degree")) {
        ast = std::make_shared<GeneratorEquationAst>(GeneratorEquationAst::Type::DEGREE);

        processNode(mathmlChildNode(node, 0), ast->left());
    } else if (node->isMathmlElement("logbase")) {
        ast = std::make_shared<GeneratorEquationAst>(GeneratorEquationAst::Type::LOGBASE);

        processNode(mathmlChildNode(node, 0), ast->left());
    } else if (node->isMathmlElement("bvar")) {
        ast = std::make_shared<GeneratorEquationAst>(GeneratorEquationAst::Type::BVAR);

        processNode(mathmlChildNode(node, 0), ast->left());

    // Constants

    } else if (node->isMathmlElement("true")) {
        ast = std::make_shared<GeneratorEquationAst>(GeneratorEquationAst::Type::TRUE);
    } else if (node->isMathmlElement("false")) {
        ast = std::make_shared<GeneratorEquationAst>(GeneratorEquationAst::Type::FALSE);
    } else if (node->isMathmlElement("exponentiale")) {
        ast = std::make_shared<GeneratorEquationAst>(GeneratorEquationAst::Type::E);
    } else if (node->isMathmlElement("pi")) {
        ast = std::make_shared<GeneratorEquationAst>(GeneratorEquationAst::Type::PI);
    } else if (node->isMathmlElement("infinity")) {
        ast = std::make_shared<GeneratorEquationAst>(GeneratorEquationAst::Type::INF);
    } else if (node->isMathmlElement("notanumber")) {
        ast = std::make_shared<GeneratorEquationAst>(GeneratorEquationAst::Type::NAN);
    }
}

void Generator::GeneratorImpl::processComponent(const ComponentPtr &component)
{
    // Retrieve the math string associated with the given component and process
    // it, one equation at a time

    XmlDocPtr xmlDoc = std::make_shared<XmlDoc>();
    std::string math = component->getMath();

    if (!math.empty()) {
        xmlDoc->parse(math);

        XmlNodePtr mathNode = xmlDoc->getRootNode();

        for (XmlNodePtr node = mathNode->getFirstChild();
             node != nullptr; node = node->getNext()) {
            if (node->isMathmlElement()) {
                processNode(node);
            }
        }
    }

    // Do the same for the components encapsulated by the given component

    for (size_t i = 0; i < component->componentCount(); ++i) {
        processComponent(component->getComponent(i));
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

std::string Generator::GeneratorImpl::generateCode(const GeneratorEquationAstPtr &ast,
                                                   const GeneratorEquationAstPtr &parentAst) const
{
    // Generate the code for the given AST

    switch (ast->type()) {
    // Relational operators

    case GeneratorEquationAst::Type::EQ:
        return generateCode(ast->left())+mEq+generateCode(ast->right());
    case GeneratorEquationAst::Type::EQEQ:
        return generateCode(ast->left())+mEqEq+generateCode(ast->right());
    case GeneratorEquationAst::Type::NEQ:
        return generateCode(ast->left())+mNeq+generateCode(ast->right());
    case GeneratorEquationAst::Type::LT:
        return generateCode(ast->left())+mLt+generateCode(ast->right());
    case GeneratorEquationAst::Type::LEQ:
        return generateCode(ast->left())+mLeq+generateCode(ast->right());
    case GeneratorEquationAst::Type::GT:
        return generateCode(ast->left())+mGt+generateCode(ast->right());
    case GeneratorEquationAst::Type::GEQ:
        return generateCode(ast->left())+mGeq+generateCode(ast->right());

    // Arithmetic operators

    case GeneratorEquationAst::Type::PLUS:
        if (ast->right()) {
            return generateCode(ast->left())+mPlus+generateCode(ast->right());
        }

        return mPlus+generateCode(ast->left());
    case GeneratorEquationAst::Type::MINUS:
        if (ast->right()) {
            return generateCode(ast->left())+mMinus+generateCode(ast->right());
        }

        return mMinus+generateCode(ast->left());
    case GeneratorEquationAst::Type::TIMES:
        return generateCode(ast->left())+mTimes+generateCode(ast->right());
    case GeneratorEquationAst::Type::DIVIDE:
        return generateCode(ast->left())+mDivide+generateCode(ast->right());
    case GeneratorEquationAst::Type::POWER: {
        std::string stringValue = generateCode(ast->right());
        double doubleValue = convertToDouble(stringValue);

        if (isEqual(doubleValue, 0.5)) {
            return mSqrt+"("+generateCode(ast->left())+")";
        }

        if (isEqual(doubleValue, 2.0)) {
            return mSqr+"("+generateCode(ast->left())+")";
        }

        return mPow+"("+generateCode(ast->left())+", "+stringValue+")";
    }
    case GeneratorEquationAst::Type::ROOT:
        if (ast->right()) {
            std::string stringValue = generateCode(ast->left());
            double doubleValue = convertToDouble(stringValue);

            if (isEqual(doubleValue, 2.0)) {
                return mSqrt+"("+generateCode(ast->right())+")";
            }

            return mPow+"("+generateCode(ast->right())+", 1.0/"+stringValue+")";
        }

        return mSqrt+"("+generateCode(ast->left())+")";
    case GeneratorEquationAst::Type::ABS:
        return mAbs+"("+generateCode(ast->left())+")";
    case GeneratorEquationAst::Type::EXP:
        return mExp+"("+generateCode(ast->left())+")";
    case GeneratorEquationAst::Type::LN:
        return mLn+"("+generateCode(ast->left())+")";
    case GeneratorEquationAst::Type::LOG:
        if (ast->right()) {
            std::string stringValue = generateCode(ast->left());
            double doubleValue = convertToDouble(stringValue);

            if (isEqual(doubleValue, 10.0)) {
                return mLog+"("+generateCode(ast->right())+")";
            }

            return mLn+"("+generateCode(ast->right())+")/"+mLn+"("+stringValue+")";
        }

        return mLog+"("+generateCode(ast->left())+")";
    case GeneratorEquationAst::Type::CEILING:
        return mCeiling+"("+generateCode(ast->left())+")";
    case GeneratorEquationAst::Type::FLOOR:
        return mFloor+"("+generateCode(ast->left())+")";
    case GeneratorEquationAst::Type::FACTORIAL:
        return mFactorial+"("+generateCode(ast->left())+")";

    // Logical operators

    case GeneratorEquationAst::Type::AND:
        return generateCode(ast->left())+mAnd+generateCode(ast->right());
    case GeneratorEquationAst::Type::OR:
        return generateCode(ast->left())+mOr+generateCode(ast->right());
    case GeneratorEquationAst::Type::XOR:
        return generateCode(ast->left())+mXor+generateCode(ast->right());
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
                return generateCode(ast->left())+":"+generateCode(ast->right())+":"+mNan;
            } else {
                return generateCode(ast->left())+":"+generateCode(ast->right());
            }
        }

        return generateCode(ast->left())+":"+mNan;
    case GeneratorEquationAst::Type::PIECE:
        return generateCode(ast->right())+"?"+generateCode(ast->left());
    case GeneratorEquationAst::Type::OTHERWISE:
        return generateCode(ast->left());

    // Token elements

    case GeneratorEquationAst::Type::CN:
    case GeneratorEquationAst::Type::CI:
        return ast->value();

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

    // Process the model itself

    for (size_t i = 0; i < model->componentCount(); ++i) {
        mPimpl->processComponent(model->getComponent(i));
    }

    // Generate the code for our different equations
//TODO: remove the below once we are done testing things...

    printf("%s", mPimpl->neededMathMethods().c_str());

    for (auto equation : mPimpl->mEquations) {
        printf("%s;\n", mPimpl->generateCode(equation->ast()).c_str());
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

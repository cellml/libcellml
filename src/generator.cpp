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
#    define _USE_MATH_DEFINES
#endif

#include "utilities.h"
#include "xmldoc.h"

#include "libcellml/component.h"
#include "libcellml/generator.h"
#include "libcellml/generatorprofile.h"
#include "libcellml/model.h"
#include "libcellml/validator.h"
#include "libcellml/variable.h"

#include <algorithm>
#include <limits>
#include <vector>

#undef NAN

#ifdef __linux__
#    undef TRUE
#    undef FALSE
#endif

//TODO: remove the below code once we are done testing things...
//#define TRACES
#ifdef TRACES
#    include <iostream>
#endif
namespace libcellml {

struct GeneratorEquationAstPimpl;
using GeneratorEquationAstPimplPtr = std::shared_ptr<GeneratorEquationAstPimpl>;

struct GeneratorEquationAstPimpl
{
    enum class Type
    {
        // Relational operators

        EQ,
        EQEQ,
        NEQ,
        LT,
        LEQ,
        GT,
        GEQ,

        // Arithmetic operators

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
        FACTORIAL,

        // Logical operators

        AND,
        OR,
        XOR,
        NOT,

        // Calculus elements

        DIFF,

        // Min/max operators

        MIN,
        MAX,

        // Gcd/lcm operators

        GCD,
        LCM,

        // Trigonometric operators

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

        // Extra operators

        REM,

        // Piecewise statement

        PIECEWISE,
        PIECE,
        OTHERWISE,

        // Token elements

        CN,
        CI,

        // Qualifier elements

        DEGREE,
        LOGBASE,
        BVAR,

        // Constants

        TRUE,
        FALSE,
        E,
        PI,
        INF,
        NAN
    };

    Type mType;

    std::string mValue;
    VariablePtr mVariable;

    GeneratorEquationAstPimplPtr mParent;

    GeneratorEquationAstPimplPtr mLeft;
    GeneratorEquationAstPimplPtr mRight;

    explicit GeneratorEquationAstPimpl(Type type, const std::string &value,
                                       const VariablePtr &variable,
                                       const GeneratorEquationAstPimplPtr &parent);
    explicit GeneratorEquationAstPimpl();
    explicit GeneratorEquationAstPimpl(Type type,
                                       const GeneratorEquationAstPimplPtr &parent);
    explicit GeneratorEquationAstPimpl(Type type, const std::string &value,
                                       const GeneratorEquationAstPimplPtr &parent);
    explicit GeneratorEquationAstPimpl(Type type, const VariablePtr &variable,
                                       const GeneratorEquationAstPimplPtr &parent);
};

GeneratorEquationAstPimpl::GeneratorEquationAstPimpl(Type type, const std::string &value,
                                                     const VariablePtr &variable,
                                                     const GeneratorEquationAstPimplPtr &parent)
    : mType(type)
    , mValue(value)
    , mVariable(variable)
    , mParent(parent)
    , mLeft(nullptr)
    , mRight(nullptr)
{
}

GeneratorEquationAstPimpl::GeneratorEquationAstPimpl()
    : GeneratorEquationAstPimpl(Type::EQ, "", nullptr, nullptr)
{
}

GeneratorEquationAstPimpl::GeneratorEquationAstPimpl(Type type,
                                                     const GeneratorEquationAstPimplPtr &parent)
    : GeneratorEquationAstPimpl(type, "", nullptr, parent)
{
}

GeneratorEquationAstPimpl::GeneratorEquationAstPimpl(Type type, const std::string &value,
                                                     const GeneratorEquationAstPimplPtr &parent)
    : GeneratorEquationAstPimpl(type, value, nullptr, parent)
{
}

GeneratorEquationAstPimpl::GeneratorEquationAstPimpl(Type type, const VariablePtr &variable,
                                                     const GeneratorEquationAstPimplPtr &parent)
    : GeneratorEquationAstPimpl(type, "", variable, parent)
{
}

struct GeneratorEquationPimpl;
using GeneratorEquationPimplPtr = std::shared_ptr<GeneratorEquationPimpl>;

struct GeneratorEquationPimpl
{
    enum class Type
    {
        UNKNOWN,
        RATE,
        ALGEBRAIC
    };

    Type mType = Type::UNKNOWN;

    GeneratorEquationAstPimplPtr mAst;

    std::vector<VariablePtr> mVariables;

    explicit GeneratorEquationPimpl();

    void addVariable(const VariablePtr &variable);
    void replaceVariable(const VariablePtr &oldVariable,
                         const VariablePtr &newVariable);
};

GeneratorEquationPimpl::GeneratorEquationPimpl()
    : mAst(std::make_shared<GeneratorEquationAstPimpl>())
{
}

void GeneratorEquationPimpl::addVariable(const VariablePtr &variable)
{
    if (std::find(mVariables.begin(), mVariables.end(), variable) == mVariables.end()) {
        mVariables.push_back(variable);
    }
}

void GeneratorEquationPimpl::replaceVariable(const VariablePtr &oldVariable,
                                             const VariablePtr &newVariable)
{
    std::replace(mVariables.begin(), mVariables.end(), oldVariable, newVariable);
}

struct GeneratorVariablePimpl;
using GeneratorVariablePimplPtr = std::shared_ptr<GeneratorVariablePimpl>;

struct GeneratorVariablePimpl
{
    enum class Type
    {
        UNKNOWN,
        SHOULD_BE_STATE,
        VARIABLE_OF_INTEGRATION,
        STATE,
        ALGEBRAIC,
        CONSTANT,
        COMPUTED_CONSTANT
    };

    Type mType = Type::UNKNOWN;

    VariablePtr mVariable = nullptr;
    GeneratorEquationAstPimplPtr mAst = nullptr;

    void setVariable(const VariablePtr &variable);

    void makeVariableOfIntegration();
    void makeState();
};

void GeneratorVariablePimpl::setVariable(const VariablePtr &variable)
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

void GeneratorVariablePimpl::makeVariableOfIntegration()
{
    mType = Type::VARIABLE_OF_INTEGRATION;
}

void GeneratorVariablePimpl::makeState()
{
    if (mType == Type::UNKNOWN) {
        mType = Type::SHOULD_BE_STATE;
    } else if (mType == Type::CONSTANT) {
        mType = Type::STATE;
    }
}

struct Generator::GeneratorImpl
{
    Generator *mGenerator = nullptr;

    bool mHasModel = false;

    VariablePtr mVariableOfIntegration;

    std::vector<GeneratorVariablePimplPtr> mVariables;
    std::vector<GeneratorEquationPimplPtr> mEquations;

    GeneratorProfilePtr mProfile = std::make_shared<libcellml::GeneratorProfile>();

    bool mNeedFactorial = false;

    bool mNeedMin = false;
    bool mNeedMax = false;

    bool mNeedGcd = false;
    bool mNeedLcm = false;

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

    bool hasValidModel() const;

    size_t mathmlChildCount(const XmlNodePtr &node) const;
    XmlNodePtr mathmlChildNode(const XmlNodePtr &node, size_t index) const;

    GeneratorVariablePimplPtr generatorVariable(const VariablePtr &variable) const;

    void processNode(const XmlNodePtr &node, GeneratorEquationAstPimplPtr &ast,
                     const GeneratorEquationAstPimplPtr &astParent,
                     const ComponentPtr &component,
                     const GeneratorEquationPimplPtr &equation);
    GeneratorEquationPimplPtr processNode(const XmlNodePtr &node,
                                          const ComponentPtr &component);
    void processComponent(const ComponentPtr &component);
    void processEquationAst(const GeneratorEquationAstPimplPtr &ast);
    void processEquation(const GeneratorEquationPimplPtr &equation);
    void processModel(const ModelPtr &model);

    std::string neededMathMethods() const;
    std::string initializeVariables() const;
    std::string computeConstantEquations() const;
    std::string computeRateEquations() const;
    std::string computeAlgebraicEquations() const;

    bool isRelationalOperator(const GeneratorEquationAstPimplPtr &ast) const;
    bool isPlusOperator(const GeneratorEquationAstPimplPtr &ast) const;
    bool isMinusOperator(const GeneratorEquationAstPimplPtr &ast) const;
    bool isTimesOperator(const GeneratorEquationAstPimplPtr &ast) const;
    bool isDivideOperator(const GeneratorEquationAstPimplPtr &ast) const;
    bool isPowerOperator(const GeneratorEquationAstPimplPtr &ast) const;
    bool isRootOperator(const GeneratorEquationAstPimplPtr &ast) const;
    bool isLogicalOrBitwiseOperator(const GeneratorEquationAstPimplPtr &ast) const;
    bool isAndOperator(const GeneratorEquationAstPimplPtr &ast) const;
    bool isOrOperator(const GeneratorEquationAstPimplPtr &ast) const;
    bool isXorOperator(const GeneratorEquationAstPimplPtr &ast) const;
    bool isPiecewiseStatement(const GeneratorEquationAstPimplPtr &ast) const;

    std::string generateOperatorCode(const std::string &op,
                                     const GeneratorEquationAstPimplPtr &ast) const;
    std::string generateMinusUnaryCode(const GeneratorEquationAstPimplPtr &ast) const;
    std::string generatePiecewiseIfCode(const std::string &condition,
                                        const std::string &value) const;
    std::string generatePiecewiseElseCode(const std::string &value) const;
    std::string generateCode(const GeneratorEquationAstPimplPtr &ast,
                             const GeneratorEquationAstPimplPtr &parentAst = nullptr) const;
};

bool Generator::GeneratorImpl::hasValidModel() const
{
    return mHasModel && (mGenerator->errorCount() != 0);
}

size_t Generator::GeneratorImpl::mathmlChildCount(const XmlNodePtr &node) const
{
    // Return the number of child elements, in the MathML namespace, for the
    // given node

    XmlNodePtr childNode = node->firstChild();
    size_t res = (childNode->isMathmlElement()) ? 1 : 0;

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
    size_t childNodeIndex = (res->isMathmlElement()) ? 0 : MAX_SIZE_T;

    while ((res != nullptr) && (childNodeIndex != index)) {
        res = res->next();

        if (res && res->isMathmlElement()) {
            ++childNodeIndex;
        }
    }

    return res;
}

GeneratorVariablePimplPtr Generator::GeneratorImpl::generatorVariable(const VariablePtr &variable) const
{
    for (const auto &generatorVariable : mVariables) {
        if (variable->isEquivalentVariable(generatorVariable->mVariable)) {
            return generatorVariable;
        }
    }

    return {};
}

void Generator::GeneratorImpl::processNode(const XmlNodePtr &node,
                                           GeneratorEquationAstPimplPtr &ast,
                                           const GeneratorEquationAstPimplPtr &astParent,
                                           const ComponentPtr &component,
                                           const GeneratorEquationPimplPtr &equation)
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
        processNode(mathmlChildNode(node, 1), ast->mLeft, ast, component, equation);

        if (childCount >= 3) {
            GeneratorEquationAstPimplPtr astRight;
            GeneratorEquationAstPimplPtr tempAst;

            processNode(mathmlChildNode(node, childCount - 1), astRight, nullptr, component, equation);

            for (size_t i = childCount - 2; i > 1; --i) {
                processNode(mathmlChildNode(node, 0), tempAst, nullptr, component, equation);
                processNode(mathmlChildNode(node, i), tempAst->mLeft, tempAst, component, equation);

                astRight->mParent = tempAst;

                tempAst->mRight = astRight;
                astRight = tempAst;
            }

            astRight->mParent = ast;

            ast->mRight = astRight;
        }

        // Relational operators

    } else if (node->isMathmlElement("eq")) {
        // This element is used both to describe "a = b" and "a == b". We can
        // distinguish between the two by checking its grand-parent. If it's a
        // "math" MathML element then it means that it is used to describe
        // "a = b" otherwise it is used to describe "a == b". In the former
        // case, there is nothing more we need to do since ast is already of
        // GeneratorEquationAstPimpl::Type::EQ type.

        if (!node->parent()->parent()->isMathmlElement("math")) {
            ast = std::make_shared<GeneratorEquationAstPimpl>(GeneratorEquationAstPimpl::Type::EQEQ, astParent);
        }
    } else if (node->isMathmlElement("neq")) {
        ast = std::make_shared<GeneratorEquationAstPimpl>(GeneratorEquationAstPimpl::Type::NEQ, astParent);
    } else if (node->isMathmlElement("lt")) {
        ast = std::make_shared<GeneratorEquationAstPimpl>(GeneratorEquationAstPimpl::Type::LT, astParent);
    } else if (node->isMathmlElement("leq")) {
        ast = std::make_shared<GeneratorEquationAstPimpl>(GeneratorEquationAstPimpl::Type::LEQ, astParent);
    } else if (node->isMathmlElement("gt")) {
        ast = std::make_shared<GeneratorEquationAstPimpl>(GeneratorEquationAstPimpl::Type::GT, astParent);
    } else if (node->isMathmlElement("geq")) {
        ast = std::make_shared<GeneratorEquationAstPimpl>(GeneratorEquationAstPimpl::Type::GEQ, astParent);

        // Arithmetic operators

    } else if (node->isMathmlElement("plus")) {
        ast = std::make_shared<GeneratorEquationAstPimpl>(GeneratorEquationAstPimpl::Type::PLUS, astParent);
    } else if (node->isMathmlElement("minus")) {
        ast = std::make_shared<GeneratorEquationAstPimpl>(GeneratorEquationAstPimpl::Type::MINUS, astParent);
    } else if (node->isMathmlElement("times")) {
        ast = std::make_shared<GeneratorEquationAstPimpl>(GeneratorEquationAstPimpl::Type::TIMES, astParent);
    } else if (node->isMathmlElement("divide")) {
        ast = std::make_shared<GeneratorEquationAstPimpl>(GeneratorEquationAstPimpl::Type::DIVIDE, astParent);
    } else if (node->isMathmlElement("power")) {
        ast = std::make_shared<GeneratorEquationAstPimpl>(GeneratorEquationAstPimpl::Type::POWER, astParent);
    } else if (node->isMathmlElement("root")) {
        ast = std::make_shared<GeneratorEquationAstPimpl>(GeneratorEquationAstPimpl::Type::ROOT, astParent);
    } else if (node->isMathmlElement("abs")) {
        ast = std::make_shared<GeneratorEquationAstPimpl>(GeneratorEquationAstPimpl::Type::ABS, astParent);
    } else if (node->isMathmlElement("exp")) {
        ast = std::make_shared<GeneratorEquationAstPimpl>(GeneratorEquationAstPimpl::Type::EXP, astParent);
    } else if (node->isMathmlElement("ln")) {
        ast = std::make_shared<GeneratorEquationAstPimpl>(GeneratorEquationAstPimpl::Type::LN, astParent);
    } else if (node->isMathmlElement("log")) {
        ast = std::make_shared<GeneratorEquationAstPimpl>(GeneratorEquationAstPimpl::Type::LOG, astParent);
    } else if (node->isMathmlElement("ceiling")) {
        ast = std::make_shared<GeneratorEquationAstPimpl>(GeneratorEquationAstPimpl::Type::CEILING, astParent);
    } else if (node->isMathmlElement("floor")) {
        ast = std::make_shared<GeneratorEquationAstPimpl>(GeneratorEquationAstPimpl::Type::FLOOR, astParent);
    } else if (node->isMathmlElement("factorial")) {
        ast = std::make_shared<GeneratorEquationAstPimpl>(GeneratorEquationAstPimpl::Type::FACTORIAL, astParent);

        mNeedFactorial = true;

        // Logical operators

    } else if (node->isMathmlElement("and")) {
        ast = std::make_shared<GeneratorEquationAstPimpl>(GeneratorEquationAstPimpl::Type::AND, astParent);
    } else if (node->isMathmlElement("or")) {
        ast = std::make_shared<GeneratorEquationAstPimpl>(GeneratorEquationAstPimpl::Type::OR, astParent);
    } else if (node->isMathmlElement("xor")) {
        ast = std::make_shared<GeneratorEquationAstPimpl>(GeneratorEquationAstPimpl::Type::XOR, astParent);
    } else if (node->isMathmlElement("not")) {
        ast = std::make_shared<GeneratorEquationAstPimpl>(GeneratorEquationAstPimpl::Type::NOT, astParent);

        // Calculus elements

    } else if (node->isMathmlElement("diff")) {
        ast = std::make_shared<GeneratorEquationAstPimpl>(GeneratorEquationAstPimpl::Type::DIFF, astParent);

        // Min/max operators

    } else if (node->isMathmlElement("min")) {
        ast = std::make_shared<GeneratorEquationAstPimpl>(GeneratorEquationAstPimpl::Type::MIN, astParent);

        mNeedMin = true;
    } else if (node->isMathmlElement("max")) {
        ast = std::make_shared<GeneratorEquationAstPimpl>(GeneratorEquationAstPimpl::Type::MAX, astParent);

        mNeedMax = true;

        // Gcd/lcm operators

    } else if (node->isMathmlElement("gcd")) {
        ast = std::make_shared<GeneratorEquationAstPimpl>(GeneratorEquationAstPimpl::Type::GCD, astParent);

        mNeedGcd = true;
    } else if (node->isMathmlElement("lcm")) {
        ast = std::make_shared<GeneratorEquationAstPimpl>(GeneratorEquationAstPimpl::Type::LCM, astParent);

        mNeedLcm = true;

        // Trigonometric operators

    } else if (node->isMathmlElement("sin")) {
        ast = std::make_shared<GeneratorEquationAstPimpl>(GeneratorEquationAstPimpl::Type::SIN, astParent);
    } else if (node->isMathmlElement("cos")) {
        ast = std::make_shared<GeneratorEquationAstPimpl>(GeneratorEquationAstPimpl::Type::COS, astParent);
    } else if (node->isMathmlElement("tan")) {
        ast = std::make_shared<GeneratorEquationAstPimpl>(GeneratorEquationAstPimpl::Type::TAN, astParent);
    } else if (node->isMathmlElement("sec")) {
        ast = std::make_shared<GeneratorEquationAstPimpl>(GeneratorEquationAstPimpl::Type::SEC, astParent);

        mNeedSec = true;
    } else if (node->isMathmlElement("csc")) {
        ast = std::make_shared<GeneratorEquationAstPimpl>(GeneratorEquationAstPimpl::Type::CSC, astParent);

        mNeedCsc = true;
    } else if (node->isMathmlElement("cot")) {
        ast = std::make_shared<GeneratorEquationAstPimpl>(GeneratorEquationAstPimpl::Type::COT, astParent);

        mNeedCot = true;
    } else if (node->isMathmlElement("sinh")) {
        ast = std::make_shared<GeneratorEquationAstPimpl>(GeneratorEquationAstPimpl::Type::SINH, astParent);
    } else if (node->isMathmlElement("cosh")) {
        ast = std::make_shared<GeneratorEquationAstPimpl>(GeneratorEquationAstPimpl::Type::COSH, astParent);
    } else if (node->isMathmlElement("tanh")) {
        ast = std::make_shared<GeneratorEquationAstPimpl>(GeneratorEquationAstPimpl::Type::TANH, astParent);
    } else if (node->isMathmlElement("sech")) {
        ast = std::make_shared<GeneratorEquationAstPimpl>(GeneratorEquationAstPimpl::Type::SECH, astParent);

        mNeedSech = true;
    } else if (node->isMathmlElement("csch")) {
        ast = std::make_shared<GeneratorEquationAstPimpl>(GeneratorEquationAstPimpl::Type::CSCH, astParent);

        mNeedCsch = true;
    } else if (node->isMathmlElement("coth")) {
        ast = std::make_shared<GeneratorEquationAstPimpl>(GeneratorEquationAstPimpl::Type::COTH, astParent);

        mNeedCoth = true;
    } else if (node->isMathmlElement("arcsin")) {
        ast = std::make_shared<GeneratorEquationAstPimpl>(GeneratorEquationAstPimpl::Type::ASIN, astParent);
    } else if (node->isMathmlElement("arccos")) {
        ast = std::make_shared<GeneratorEquationAstPimpl>(GeneratorEquationAstPimpl::Type::ACOS, astParent);
    } else if (node->isMathmlElement("arctan")) {
        ast = std::make_shared<GeneratorEquationAstPimpl>(GeneratorEquationAstPimpl::Type::ATAN, astParent);
    } else if (node->isMathmlElement("arcsec")) {
        ast = std::make_shared<GeneratorEquationAstPimpl>(GeneratorEquationAstPimpl::Type::ASEC, astParent);

        mNeedAsec = true;
    } else if (node->isMathmlElement("arccsc")) {
        ast = std::make_shared<GeneratorEquationAstPimpl>(GeneratorEquationAstPimpl::Type::ACSC, astParent);

        mNeedAcsc = true;
    } else if (node->isMathmlElement("arccot")) {
        ast = std::make_shared<GeneratorEquationAstPimpl>(GeneratorEquationAstPimpl::Type::ACOT, astParent);

        mNeedAcot = true;
    } else if (node->isMathmlElement("arcsinh")) {
        ast = std::make_shared<GeneratorEquationAstPimpl>(GeneratorEquationAstPimpl::Type::ASINH, astParent);
    } else if (node->isMathmlElement("arccosh")) {
        ast = std::make_shared<GeneratorEquationAstPimpl>(GeneratorEquationAstPimpl::Type::ACOSH, astParent);
    } else if (node->isMathmlElement("arctanh")) {
        ast = std::make_shared<GeneratorEquationAstPimpl>(GeneratorEquationAstPimpl::Type::ATANH, astParent);
    } else if (node->isMathmlElement("arcsech")) {
        ast = std::make_shared<GeneratorEquationAstPimpl>(GeneratorEquationAstPimpl::Type::ASECH, astParent);

        mNeedAsech = true;
    } else if (node->isMathmlElement("arccsch")) {
        ast = std::make_shared<GeneratorEquationAstPimpl>(GeneratorEquationAstPimpl::Type::ACSCH, astParent);

        mNeedAcsch = true;
    } else if (node->isMathmlElement("arccoth")) {
        ast = std::make_shared<GeneratorEquationAstPimpl>(GeneratorEquationAstPimpl::Type::ACOTH, astParent);

        mNeedAcoth = true;

        // Extra operators

    } else if (node->isMathmlElement("rem")) {
        ast = std::make_shared<GeneratorEquationAstPimpl>(GeneratorEquationAstPimpl::Type::REM, astParent);

        // Piecewise statement

    } else if (node->isMathmlElement("piecewise")) {
        size_t childCount = mathmlChildCount(node);

        ast = std::make_shared<GeneratorEquationAstPimpl>(GeneratorEquationAstPimpl::Type::PIECEWISE, astParent);

        processNode(mathmlChildNode(node, 0), ast->mLeft, ast, component, equation);

        if (childCount >= 2) {
            GeneratorEquationAstPimplPtr astRight;
            GeneratorEquationAstPimplPtr tempAst;

            processNode(mathmlChildNode(node, childCount - 1), astRight, nullptr, component, equation);

            for (size_t i = childCount - 2; i > 0; --i) {
                tempAst = std::make_shared<GeneratorEquationAstPimpl>(GeneratorEquationAstPimpl::Type::PIECEWISE, astParent);

                processNode(mathmlChildNode(node, i), tempAst->mLeft, tempAst, component, equation);

                astRight->mParent = tempAst;

                tempAst->mRight = astRight;
                astRight = tempAst;
            }

            astRight->mParent = ast;

            ast->mRight = astRight;
        }
    } else if (node->isMathmlElement("piece")) {
        ast = std::make_shared<GeneratorEquationAstPimpl>(GeneratorEquationAstPimpl::Type::PIECE, astParent);

        processNode(mathmlChildNode(node, 0), ast->mLeft, ast, component, equation);
        processNode(mathmlChildNode(node, 1), ast->mRight, ast, component, equation);
    } else if (node->isMathmlElement("otherwise")) {
        ast = std::make_shared<GeneratorEquationAstPimpl>(GeneratorEquationAstPimpl::Type::OTHERWISE, astParent);

        processNode(mathmlChildNode(node, 0), ast->mLeft, ast, component, equation);

        // Token elements

    } else if (node->isMathmlElement("cn")) {
        ast = std::make_shared<GeneratorEquationAstPimpl>(GeneratorEquationAstPimpl::Type::CN, node->firstChild()->convertToString(), astParent);
    } else if (node->isMathmlElement("ci")) {
        VariablePtr variable = component->variable(node->firstChild()->convertToString());

        ast = std::make_shared<GeneratorEquationAstPimpl>(GeneratorEquationAstPimpl::Type::CI, variable, astParent);

        equation->addVariable(variable);

        // Qualifier elements

    } else if (node->isMathmlElement("degree")) {
        ast = std::make_shared<GeneratorEquationAstPimpl>(GeneratorEquationAstPimpl::Type::DEGREE, astParent);

        processNode(mathmlChildNode(node, 0), ast->mLeft, ast, component, equation);
    } else if (node->isMathmlElement("logbase")) {
        ast = std::make_shared<GeneratorEquationAstPimpl>(GeneratorEquationAstPimpl::Type::LOGBASE, astParent);

        processNode(mathmlChildNode(node, 0), ast->mLeft, ast, component, equation);
    } else if (node->isMathmlElement("bvar")) {
        ast = std::make_shared<GeneratorEquationAstPimpl>(GeneratorEquationAstPimpl::Type::BVAR, astParent);

        processNode(mathmlChildNode(node, 0), ast->mLeft, ast, component, equation);

        XmlNodePtr rightNode = mathmlChildNode(node, 1);

        if (rightNode != nullptr) {
            processNode(rightNode, ast->mRight, ast, component, equation);
        }

        // Constants

    } else if (node->isMathmlElement("true")) {
        ast = std::make_shared<GeneratorEquationAstPimpl>(GeneratorEquationAstPimpl::Type::TRUE, astParent);
    } else if (node->isMathmlElement("false")) {
        ast = std::make_shared<GeneratorEquationAstPimpl>(GeneratorEquationAstPimpl::Type::FALSE, astParent);
    } else if (node->isMathmlElement("exponentiale")) {
        ast = std::make_shared<GeneratorEquationAstPimpl>(GeneratorEquationAstPimpl::Type::E, astParent);
    } else if (node->isMathmlElement("pi")) {
        ast = std::make_shared<GeneratorEquationAstPimpl>(GeneratorEquationAstPimpl::Type::PI, astParent);
    } else if (node->isMathmlElement("infinity")) {
        ast = std::make_shared<GeneratorEquationAstPimpl>(GeneratorEquationAstPimpl::Type::INF, astParent);
    } else if (node->isMathmlElement("notanumber")) {
        ast = std::make_shared<GeneratorEquationAstPimpl>(GeneratorEquationAstPimpl::Type::NAN, astParent);
    }
}

GeneratorEquationPimplPtr Generator::GeneratorImpl::processNode(const XmlNodePtr &node,
                                                                const ComponentPtr &component)
{
    // Create and keep track of the equation associated with the given node

    GeneratorEquationPimplPtr equation = std::make_shared<GeneratorEquationPimpl>();

    mEquations.push_back(equation);

    // Actually process the node

    processNode(node, equation->mAst, equation->mAst->mParent, component, equation);

    return equation;
}

void Generator::GeneratorImpl::processComponent(const ComponentPtr &component)
{
    // Retrieve the math string associated with the given component and process
    // it, one equation at a time

    XmlDocPtr xmlDoc = std::make_shared<XmlDoc>();
    std::string math = component->math();

    if (!math.empty()) {
        xmlDoc->parseMathML(math);

        XmlNodePtr mathNode = xmlDoc->rootNode();

        for (XmlNodePtr node = mathNode->firstChild(); node != nullptr; node = node->next()) {
            if (node->isMathmlElement()) {
                processNode(node, component);
            }
        }
    }

    // Go through the given component's variable and make sure that everything
    // makes sense

    for (size_t i = 0; i < component->variableCount(); ++i) {
        // Track the variable if it isn't already being tracked

        bool componentVariableTracked = false;
        VariablePtr componentVariable = component->variable(i);
        GeneratorVariablePimplPtr trackedVariable;

        for (const auto &variable : mVariables) {
            if (componentVariable->isEquivalentVariable(variable->mVariable)) {
                componentVariableTracked = true;
                trackedVariable = variable;

                break;
            }
        }

        if (!componentVariableTracked) {
            trackedVariable = std::make_shared<GeneratorVariablePimpl>();

            mVariables.push_back(trackedVariable);
        }

        // Set the variable held by trackedVariable, in case there was none
        // before or in case the existing one has no initial value while
        // componentVariable does. Otherwise, generate an error if the variable
        // held by trackedVariable and componentVariable are both initialised.

        if ((trackedVariable->mVariable == nullptr)
            || (!componentVariable->initialValue().empty()
                && trackedVariable->mVariable->initialValue().empty())) {
            trackedVariable->setVariable(componentVariable);
        } else if (!componentVariable->initialValue().empty()
                   && !trackedVariable->mVariable->initialValue().empty()) {
            ModelPtr model = component->parentModel();
            ComponentPtr trackedVariableComponent = trackedVariable->mVariable->parentComponent();
            ModelPtr trackedVariableModel = trackedVariableComponent->parentModel();
            ErrorPtr err = std::make_shared<Error>();

            err->setDescription("Variable '" + componentVariable->name() + "' in component '" + component->name() + "' of model '" + model->name() + "' and "
                                                                                                                                                     "variable '"
                                + trackedVariable->mVariable->name() + "' in component '" + trackedVariableComponent->name() + "' of model '" + trackedVariableModel->name() + "' are equivalent and cannot therefore both be initialised.");
            err->setKind(Error::Kind::GENERATOR);

            mGenerator->addError(err);
        }
    }

    // Do the same for the components encapsulated by the given component

    for (size_t i = 0; i < component->componentCount(); ++i) {
        processComponent(component->component(i));
    }
}

void Generator::GeneratorImpl::processEquationAst(const GeneratorEquationAstPimplPtr &ast)
{
    // Look for the definition of a variable of integration and make sure that
    // we don't have more than one of them and that it's not initialised

    GeneratorEquationAstPimplPtr astParent = ast->mParent;
    GeneratorEquationAstPimplPtr astGrandParent = (astParent != nullptr) ? astParent->mParent : nullptr;
    GeneratorEquationAstPimplPtr astGreatGrandParent = (astGrandParent != nullptr) ? astGrandParent->mParent : nullptr;

    if ((ast->mType == GeneratorEquationAstPimpl::Type::CI)
        && (astParent != nullptr) && (astParent->mType == GeneratorEquationAstPimpl::Type::BVAR)
        && (astGrandParent != nullptr) && (astGrandParent->mType == GeneratorEquationAstPimpl::Type::DIFF)) {
        VariablePtr variable = ast->mVariable;

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

                err->setDescription("Variable '" + variable->name() + "' in component '" + component->name() + "' of model '" + model->name() + "' cannot be both a variable of integration and initialised.");
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

            err->setDescription("Variable '" + mVariableOfIntegration->name() + "' in component '" + voiComponent->name() + "' of model '" + voiModel->name() + "' and variable '" + variable->name() + "' in component '" + component->name() + "' of model '" + model->name() + "' cannot both be a variable of integration.");
            err->setKind(Error::Kind::GENERATOR);

            mGenerator->addError(err);
        }
    }

    // Make sure that we only use first-order ODEs

    if ((ast->mType == GeneratorEquationAstPimpl::Type::CN)
        && (astParent != nullptr) && (astParent->mType == GeneratorEquationAstPimpl::Type::DEGREE)
        && (astGrandParent != nullptr) && (astGrandParent->mType == GeneratorEquationAstPimpl::Type::BVAR)
        && (astGreatGrandParent != nullptr) && (astGreatGrandParent->mType == GeneratorEquationAstPimpl::Type::DIFF)) {
        if (convertToDouble(ast->mValue) != 1.0) {
            VariablePtr variable = astGreatGrandParent->mRight->mVariable;
            ComponentPtr component = variable->parentComponent();
            ModelPtr model = component->parentModel();
            ErrorPtr err = std::make_shared<Error>();

            err->setDescription("The differential equation for variable '" + variable->name() + "' in component '" + component->name() + "' of model '" + model->name() + "' must be of the first order.");
            err->setKind(Error::Kind::GENERATOR);

            mGenerator->addError(err);
        }
    }

    // Make a variable a state if it is used in an ODE

    if ((ast->mType == GeneratorEquationAstPimpl::Type::CI)
        && (astParent != nullptr) && (astParent->mType == GeneratorEquationAstPimpl::Type::DIFF)) {
        generatorVariable(ast->mVariable)->makeState();
    }

    // Recursively check the given AST's children

    if (ast->mLeft != nullptr) {
        processEquationAst(ast->mLeft);
    }

    if (ast->mRight != nullptr) {
        processEquationAst(ast->mRight);
    }
}

void Generator::GeneratorImpl::processEquation(const GeneratorEquationPimplPtr &equation)
{
    // Update the equation's variables with those that have become our reference

    for (const auto &equationVariable : equation->mVariables) {
        for (const auto &variable : mVariables) {
            if (equationVariable->isEquivalentVariable(variable->mVariable)) {
                equation->replaceVariable(equationVariable, variable->mVariable);
            }
        }
    }

    // Process the equation's AST

    processEquationAst(equation->mAst);
}

void Generator::GeneratorImpl::processModel(const ModelPtr &model)
{
    // Reset a few things in case we were to process the model more than once
    // Note: one would normally process the model only once, so we shouldn't
    //       need to do this, but better be safe than sorry.

    mHasModel = true;

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

        switch (variable->mType) {
        case GeneratorVariablePimpl::Type::UNKNOWN:
            errorType = "is of unknown type";

            break;
        case GeneratorVariablePimpl::Type::SHOULD_BE_STATE:
            errorType = "is used in an ODE, but it is not initialised";

            break;
        case GeneratorVariablePimpl::Type::VARIABLE_OF_INTEGRATION:
        case GeneratorVariablePimpl::Type::STATE:
        case GeneratorVariablePimpl::Type::ALGEBRAIC:
        case GeneratorVariablePimpl::Type::CONSTANT:
        case GeneratorVariablePimpl::Type::COMPUTED_CONSTANT:
            break;
        }

        if (!errorType.empty()) {
            ErrorPtr err = std::make_shared<Error>();
            VariablePtr realVariable = variable->mVariable;
            ComponentPtr realComponent = realVariable->parentComponent();
            ModelPtr realModel = realComponent->parentModel();

            err->setDescription("Variable '" + realVariable->name() + "' in component '" + realComponent->name() + "' of model '" + realModel->name() + "' " + errorType + ".");
            err->setKind(Error::Kind::GENERATOR);

            mGenerator->addError(err);
        }
    }

//TODO: remove the below code once we are done testing things...
#ifdef TRACES
    std::cout << "Number of variables: " << mVariables.size() << std::endl;
    int i = 0;
    for (const auto &variable : mVariables) {
        std::cout << "Variable #" << ++i << " [" << int(variable->mType)
                  << "]: " << variable->mVariable->name().c_str()
                  << " " << (variable->mVariable->initialValue().empty() ? "" : std::string("[init: " + variable->mVariable->initialValue() + "] "))
                  << "[comp: " << variable->mVariable->parentComponent()->name() << "]" << std::endl;
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
        if (variable->mType == GeneratorVariablePimpl::Type::CONSTANT) {
            res += variable->mVariable->name() + " = " + variable->mVariable->initialValue() + mProfile->commandSeparatorString() + "\n";
        }
    }

    return res;
}

std::string Generator::GeneratorImpl::computeConstantEquations() const
{
    std::string res;

    for (const auto &variable : mVariables) {
        if (variable->mType == GeneratorVariablePimpl::Type::COMPUTED_CONSTANT) {
            //TODO: to be done...
        }
    }

    return res;
}

std::string Generator::GeneratorImpl::computeRateEquations() const
{
    std::string res;

    for (const auto &equation : mEquations) {
        if (equation->mType == GeneratorEquationPimpl::Type::RATE) {
            res += generateCode(equation->mAst);
        }
    }

    return res;
}

std::string Generator::GeneratorImpl::computeAlgebraicEquations() const
{
    std::string res;

    for (const auto &equation : mEquations) {
        //        if (equation->mType == GeneratorEquationPimpl::Type::ALGEBRAIC) {
        res += generateCode(equation->mAst) + mProfile->commandSeparatorString() + "\n";
        //        }
    }

    return res;
}

std::string replace(const std::string &string, const std::string &from, const std::string &to)
{
    return std::string(string).replace(string.find(from), from.length(), to);
}

bool Generator::GeneratorImpl::isRelationalOperator(const GeneratorEquationAstPimplPtr &ast) const
{
    return (ast->mType == GeneratorEquationAstPimpl::Type::EQEQ)
           || (ast->mType == GeneratorEquationAstPimpl::Type::NEQ)
           || (ast->mType == GeneratorEquationAstPimpl::Type::LT)
           || (ast->mType == GeneratorEquationAstPimpl::Type::LEQ)
           || (ast->mType == GeneratorEquationAstPimpl::Type::GT)
           || (ast->mType == GeneratorEquationAstPimpl::Type::GEQ);
}

bool Generator::GeneratorImpl::isPlusOperator(const GeneratorEquationAstPimplPtr &ast) const
{
    return ast->mType == GeneratorEquationAstPimpl::Type::PLUS;
}

bool Generator::GeneratorImpl::isMinusOperator(const GeneratorEquationAstPimplPtr &ast) const
{
    return ast->mType == GeneratorEquationAstPimpl::Type::MINUS;
}

bool Generator::GeneratorImpl::isTimesOperator(const GeneratorEquationAstPimplPtr &ast) const
{
    return ast->mType == GeneratorEquationAstPimpl::Type::TIMES;
}

bool Generator::GeneratorImpl::isDivideOperator(const GeneratorEquationAstPimplPtr &ast) const
{
    return ast->mType == GeneratorEquationAstPimpl::Type::DIVIDE;
}

bool Generator::GeneratorImpl::isPowerOperator(const GeneratorEquationAstPimplPtr &ast) const
{
    return ast->mType == GeneratorEquationAstPimpl::Type::POWER;
}

bool Generator::GeneratorImpl::isRootOperator(const GeneratorEquationAstPimplPtr &ast) const
{
    return ast->mType == GeneratorEquationAstPimpl::Type::ROOT;
}

bool Generator::GeneratorImpl::isAndOperator(const GeneratorEquationAstPimplPtr &ast) const
{
    return ast->mType == GeneratorEquationAstPimpl::Type::AND;
}

bool Generator::GeneratorImpl::isOrOperator(const GeneratorEquationAstPimplPtr &ast) const
{
    return ast->mType == GeneratorEquationAstPimpl::Type::OR;
}

bool Generator::GeneratorImpl::isXorOperator(const GeneratorEquationAstPimplPtr &ast) const
{
    return ast->mType == GeneratorEquationAstPimpl::Type::XOR;
}

bool Generator::GeneratorImpl::isLogicalOrBitwiseOperator(const GeneratorEquationAstPimplPtr &ast) const
{
    // Note: GeneratorEquationAstPimpl::Type::NOT is a unary logical operator hence
    //       we don't include it here since this method is only used to
    //       determine whether parentheses should be added around some code.

    return (ast->mType == GeneratorEquationAstPimpl::Type::AND)
           || (ast->mType == GeneratorEquationAstPimpl::Type::OR)
           || (ast->mType == GeneratorEquationAstPimpl::Type::XOR);
}

bool Generator::GeneratorImpl::isPiecewiseStatement(const GeneratorEquationAstPimplPtr &ast) const
{
    return ast->mType == GeneratorEquationAstPimpl::Type::PIECEWISE;
}

std::string Generator::GeneratorImpl::generateOperatorCode(const std::string &op,
                                                           const GeneratorEquationAstPimplPtr &ast) const
{
    // Generate the code for the left and right branches of the given AST

    std::string left = generateCode(ast->mLeft);
    std::string right = generateCode(ast->mRight);

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
        if (isRelationalOperator(ast->mLeft)
            || isLogicalOrBitwiseOperator(ast->mLeft)
            || isPiecewiseStatement(ast->mLeft)) {
            left = "(" + left + ")";
        }

        if (isRelationalOperator(ast->mRight)
            || isLogicalOrBitwiseOperator(ast->mRight)
            || isPiecewiseStatement(ast->mRight)) {
            right = "(" + right + ")";
        }
    } else if (isMinusOperator(ast)) {
        if (isRelationalOperator(ast->mLeft)
            || isLogicalOrBitwiseOperator(ast->mLeft)
            || isPiecewiseStatement(ast->mLeft)) {
            left = "(" + left + ")";
        }

        if (isRelationalOperator(ast->mRight)
            || isMinusOperator(ast->mRight)
            || isLogicalOrBitwiseOperator(ast->mRight)
            || isPiecewiseStatement(ast->mRight)) {
            right = "(" + right + ")";
        } else if (isPlusOperator(ast->mRight)) {
            if (ast->mRight->mRight != nullptr) {
                right = "(" + right + ")";
            }
        }
    } else if (isTimesOperator(ast)) {
        if (isRelationalOperator(ast->mLeft)
            || isLogicalOrBitwiseOperator(ast->mLeft)
            || isPiecewiseStatement(ast->mLeft)) {
            left = "(" + left + ")";
        } else if (isPlusOperator(ast->mLeft)
                   || isMinusOperator(ast->mLeft)) {
            if (ast->mLeft->mRight != nullptr) {
                left = "(" + left + ")";
            }
        }

        if (isRelationalOperator(ast->mRight)
            || isLogicalOrBitwiseOperator(ast->mRight)
            || isPiecewiseStatement(ast->mRight)) {
            right = "(" + right + ")";
        } else if (isPlusOperator(ast->mRight)
                   || isMinusOperator(ast->mRight)) {
            if (ast->mRight->mRight != nullptr) {
                right = "(" + right + ")";
            }
        }
    } else if (isDivideOperator(ast)) {
        if (isRelationalOperator(ast->mLeft)
            || isLogicalOrBitwiseOperator(ast->mLeft)
            || isPiecewiseStatement(ast->mLeft)) {
            left = "(" + left + ")";
        } else if (isPlusOperator(ast->mLeft)
                   || isMinusOperator(ast->mLeft)) {
            if (ast->mLeft->mRight != nullptr) {
                left = "(" + left + ")";
            }
        }

        if (isRelationalOperator(ast->mRight)
            || isTimesOperator(ast->mRight)
            || isDivideOperator(ast->mRight)
            || isLogicalOrBitwiseOperator(ast->mRight)
            || isPiecewiseStatement(ast->mRight)) {
            right = "(" + right + ")";
        } else if (isPlusOperator(ast->mRight)
                   || isMinusOperator(ast->mRight)) {
            if (ast->mRight->mRight != nullptr) {
                right = "(" + right + ")";
            }
        }
    } else if (isAndOperator(ast)) {
        // Note: according to the precedence rules above, we only need to add
        //       parentheses around OR and PIECEWISE. It's just that it looks
        //       better/clearer to have some around some other operators
        //       (somewhat subjective indeed).

        if (isRelationalOperator(ast->mLeft)
            || isOrOperator(ast->mLeft)
            || isXorOperator(ast->mLeft)
            || isPiecewiseStatement(ast->mLeft)) {
            left = "(" + left + ")";
        } else if (isPlusOperator(ast->mLeft)
                   || isMinusOperator(ast->mLeft)) {
            if (ast->mLeft->mRight != nullptr) {
                left = "(" + left + ")";
            }
        } else if (isPowerOperator(ast->mLeft)) {
            if (mProfile->hasPowerOperator()) {
                left = "(" + left + ")";
            }
        } else if (isRootOperator(ast->mLeft)) {
            if (mProfile->hasPowerOperator()) {
                left = "(" + left + ")";
            }
        }

        if (isRelationalOperator(ast->mRight)
            || isOrOperator(ast->mRight)
            || isXorOperator(ast->mRight)
            || isPiecewiseStatement(ast->mRight)) {
            right = "(" + right + ")";
        } else if (isPlusOperator(ast->mRight)
                   || isMinusOperator(ast->mRight)) {
            if (ast->mRight->mRight != nullptr) {
                right = "(" + right + ")";
            }
        } else if (isPowerOperator(ast->mRight)) {
            if (mProfile->hasPowerOperator()) {
                right = "(" + right + ")";
            }
        } else if (isRootOperator(ast->mRight)) {
            if (mProfile->hasPowerOperator()) {
                right = "(" + right + ")";
            }
        }
    } else if (isOrOperator(ast)) {
        // Note: according to the precedence rules above, we only need to add
        //       parentheses around PIECEWISE. It's just that it looks
        //       better/clearer to have some around some other operators
        //       (somewhat subjective indeed).

        if (isRelationalOperator(ast->mLeft)
            || isAndOperator(ast->mLeft)
            || isXorOperator(ast->mLeft)
            || isPiecewiseStatement(ast->mLeft)) {
            left = "(" + left + ")";
        } else if (isPlusOperator(ast->mLeft)
                   || isMinusOperator(ast->mLeft)) {
            if (ast->mLeft->mRight != nullptr) {
                left = "(" + left + ")";
            }
        } else if (isPowerOperator(ast->mLeft)) {
            if (mProfile->hasPowerOperator()) {
                left = "(" + left + ")";
            }
        } else if (isRootOperator(ast->mLeft)) {
            if (mProfile->hasPowerOperator()) {
                left = "(" + left + ")";
            }
        }

        if (isRelationalOperator(ast->mRight)
            || isAndOperator(ast->mRight)
            || isXorOperator(ast->mRight)
            || isPiecewiseStatement(ast->mRight)) {
            right = "(" + right + ")";
        } else if (isPlusOperator(ast->mRight)
                   || isMinusOperator(ast->mRight)) {
            if (ast->mRight->mRight != nullptr) {
                right = "(" + right + ")";
            }
        } else if (isPowerOperator(ast->mRight)) {
            if (mProfile->hasPowerOperator()) {
                right = "(" + right + ")";
            }
        } else if (isRootOperator(ast->mRight)) {
            if (mProfile->hasPowerOperator()) {
                right = "(" + right + ")";
            }
        }
    } else if (isXorOperator(ast)) {
        // Note: according to the precedence rules above, we only need to add
        //       parentheses around AND, OR and PIECEWISE. It's just that it
        //       looks better/clearer to have some around some other operators
        //       (somewhat subjective indeed).

        if (isRelationalOperator(ast->mLeft)
            || isAndOperator(ast->mLeft)
            || isOrOperator(ast->mLeft)
            || isPiecewiseStatement(ast->mLeft)) {
            left = "(" + left + ")";
        } else if (isPlusOperator(ast->mLeft)
                   || isMinusOperator(ast->mLeft)) {
            if (ast->mLeft->mRight != nullptr) {
                left = "(" + left + ")";
            }
        } else if (isPowerOperator(ast->mLeft)) {
            if (mProfile->hasPowerOperator()) {
                left = "(" + left + ")";
            }
        } else if (isRootOperator(ast->mLeft)) {
            if (mProfile->hasPowerOperator()) {
                left = "(" + left + ")";
            }
        }

        if (isRelationalOperator(ast->mRight)
            || isAndOperator(ast->mRight)
            || isOrOperator(ast->mRight)
            || isPiecewiseStatement(ast->mRight)) {
            right = "(" + right + ")";
        } else if (isPlusOperator(ast->mRight)
                   || isMinusOperator(ast->mRight)) {
            if (ast->mRight->mRight != nullptr) {
                right = "(" + right + ")";
            }
        } else if (isPowerOperator(ast->mRight)) {
            if (mProfile->hasPowerOperator()) {
                right = "(" + right + ")";
            }
        } else if (isRootOperator(ast->mRight)) {
            if (mProfile->hasPowerOperator()) {
                right = "(" + right + ")";
            }
        }
    } else if (isPowerOperator(ast)) {
        if (isRelationalOperator(ast->mLeft)
            || isMinusOperator(ast->mLeft)
            || isTimesOperator(ast->mLeft)
            || isDivideOperator(ast->mLeft)
            || isLogicalOrBitwiseOperator(ast->mLeft)
            || isPiecewiseStatement(ast->mLeft)) {
            left = "(" + left + ")";
        } else if (isPlusOperator(ast->mLeft)) {
            if (ast->mLeft->mRight != nullptr) {
                left = "(" + left + ")";
            }
        }

        if (isRelationalOperator(ast->mRight)
            || isMinusOperator(ast->mLeft)
            || isTimesOperator(ast->mRight)
            || isDivideOperator(ast->mRight)
            || isPowerOperator(ast->mRight)
            || isRootOperator(ast->mRight)
            || isLogicalOrBitwiseOperator(ast->mRight)
            || isPiecewiseStatement(ast->mRight)) {
            right = "(" + right + ")";
        } else if (isPlusOperator(ast->mRight)) {
            if (ast->mRight->mRight != nullptr) {
                right = "(" + right + ")";
            }
        }
    } else if (isRootOperator(ast)) {
        if (isRelationalOperator(ast->mRight)
            || isMinusOperator(ast->mRight)
            || isTimesOperator(ast->mRight)
            || isDivideOperator(ast->mRight)
            || isLogicalOrBitwiseOperator(ast->mRight)
            || isPiecewiseStatement(ast->mRight)) {
            right = "(" + right + ")";
        } else if (isPlusOperator(ast->mRight)) {
            if (ast->mRight->mRight != nullptr) {
                right = "(" + right + ")";
            }
        }

        if (isRelationalOperator(ast->mLeft)
            || isMinusOperator(ast->mLeft)
            || isTimesOperator(ast->mLeft)
            || isDivideOperator(ast->mLeft)
            || isPowerOperator(ast->mLeft)
            || isRootOperator(ast->mLeft)
            || isLogicalOrBitwiseOperator(ast->mLeft)
            || isPiecewiseStatement(ast->mLeft)) {
            left = "(" + left + ")";
        } else if (isPlusOperator(ast->mLeft)) {
            if (ast->mLeft->mRight != nullptr) {
                left = "(" + left + ")";
            }
        }

        return right + op + "(1.0/" + left + ")";
    }

    return left + op + right;
}

std::string Generator::GeneratorImpl::generateMinusUnaryCode(const GeneratorEquationAstPimplPtr &ast) const
{
    // Generate the code for the left branch of the given AST

    std::string left = generateCode(ast->mLeft);

    // Determine whether parentheses should be added around the left code

    if (isRelationalOperator(ast->mLeft)
        || isPlusOperator(ast->mLeft)
        || isMinusOperator(ast->mLeft)
        || isLogicalOrBitwiseOperator(ast->mLeft)
        || isPiecewiseStatement(ast->mLeft)) {
        left = "(" + left + ")";
    }

    return mProfile->minusString() + left;
}

std::string Generator::GeneratorImpl::generatePiecewiseIfCode(const std::string &condition,
                                                              const std::string &value) const
{
    return replace(replace(mProfile->hasConditionalOperator() ?
                               mProfile->conditionalOperatorIfString() :
                               mProfile->piecewiseIfString(),
                           "#cond", condition),
                   "#if", value);
}

std::string Generator::GeneratorImpl::generatePiecewiseElseCode(const std::string &value) const
{
    return replace(mProfile->hasConditionalOperator() ?
                       mProfile->conditionalOperatorElseString() :
                       mProfile->piecewiseElseString(),
                   "#else", value);
}

std::string Generator::GeneratorImpl::generateCode(const GeneratorEquationAstPimplPtr &ast,
                                                   const GeneratorEquationAstPimplPtr &parentAst) const
{
    // Generate the code for the given AST

    switch (ast->mType) {
        // Relational operators

    case GeneratorEquationAstPimpl::Type::EQ:
        return generateOperatorCode(mProfile->eqString(), ast);
    case GeneratorEquationAstPimpl::Type::EQEQ:
        return generateOperatorCode(mProfile->eqEqString(), ast);
    case GeneratorEquationAstPimpl::Type::NEQ:
        return generateOperatorCode(mProfile->neqString(), ast);
    case GeneratorEquationAstPimpl::Type::LT:
        return generateOperatorCode(mProfile->ltString(), ast);
    case GeneratorEquationAstPimpl::Type::LEQ:
        return generateOperatorCode(mProfile->leqString(), ast);
    case GeneratorEquationAstPimpl::Type::GT:
        return generateOperatorCode(mProfile->gtString(), ast);
    case GeneratorEquationAstPimpl::Type::GEQ:
        return generateOperatorCode(mProfile->geqString(), ast);

        // Arithmetic operators

    case GeneratorEquationAstPimpl::Type::PLUS:
        if (ast->mRight != nullptr) {
            return generateOperatorCode(mProfile->plusString(), ast);
        }

        return generateCode(ast->mLeft);
    case GeneratorEquationAstPimpl::Type::MINUS:
        if (ast->mRight != nullptr) {
            return generateOperatorCode(mProfile->minusString(), ast);
        }

        return generateMinusUnaryCode(ast);
    case GeneratorEquationAstPimpl::Type::TIMES:
        return generateOperatorCode(mProfile->timesString(), ast);
    case GeneratorEquationAstPimpl::Type::DIVIDE:
        return generateOperatorCode(mProfile->divideString(), ast);
    case GeneratorEquationAstPimpl::Type::POWER: {
        std::string stringValue = generateCode(ast->mRight);
        double doubleValue = convertToDouble(stringValue);

        if (isEqual(doubleValue, 0.5)) {
            return mProfile->squareRootString() + "(" + generateCode(ast->mLeft) + ")";
        }

        if (isEqual(doubleValue, 2.0)) {
            return mProfile->squareString() + "(" + generateCode(ast->mLeft) + ")";
        }

        return mProfile->hasPowerOperator() ?
                   generateOperatorCode(mProfile->powerString(), ast) :
                   mProfile->powerString() + "(" + generateCode(ast->mLeft) + ", " + stringValue + ")";
    }
    case GeneratorEquationAstPimpl::Type::ROOT:
        if (ast->mRight != nullptr) {
            std::string stringValue = generateCode(ast->mLeft);
            double doubleValue = convertToDouble(stringValue);

            if (isEqual(doubleValue, 2.0)) {
                return mProfile->squareRootString() + "(" + generateCode(ast->mRight) + ")";
            }

            return mProfile->hasPowerOperator() ?
                       generateOperatorCode(mProfile->powerString(), ast) :
                       mProfile->powerString() + "(" + generateCode(ast->mRight) + ", 1.0/" + stringValue + ")";
        }

        return mProfile->squareRootString() + "(" + generateCode(ast->mLeft) + ")";
    case GeneratorEquationAstPimpl::Type::ABS:
        return mProfile->absoluteValueString() + "(" + generateCode(ast->mLeft) + ")";
    case GeneratorEquationAstPimpl::Type::EXP:
        return mProfile->exponentialString() + "(" + generateCode(ast->mLeft) + ")";
    case GeneratorEquationAstPimpl::Type::LN:
        return mProfile->napierianLogarithmString() + "(" + generateCode(ast->mLeft) + ")";
    case GeneratorEquationAstPimpl::Type::LOG:
        if (ast->mRight != nullptr) {
            std::string stringValue = generateCode(ast->mLeft);
            double doubleValue = convertToDouble(stringValue);

            if (isEqual(doubleValue, 10.0)) {
                return mProfile->commonLogarithmString() + "(" + generateCode(ast->mRight) + ")";
            }

            return mProfile->napierianLogarithmString() + "(" + generateCode(ast->mRight) + ")/" + mProfile->napierianLogarithmString() + "(" + stringValue + ")";
        }

        return mProfile->commonLogarithmString() + "(" + generateCode(ast->mLeft) + ")";
    case GeneratorEquationAstPimpl::Type::CEILING:
        return mProfile->ceilingString() + "(" + generateCode(ast->mLeft) + ")";
    case GeneratorEquationAstPimpl::Type::FLOOR:
        return mProfile->floorString() + "(" + generateCode(ast->mLeft) + ")";
    case GeneratorEquationAstPimpl::Type::FACTORIAL:
        return mProfile->factorialString() + "(" + generateCode(ast->mLeft) + ")";

        // Logical operators

    case GeneratorEquationAstPimpl::Type::AND:
        return generateOperatorCode(mProfile->andString(), ast);
    case GeneratorEquationAstPimpl::Type::OR:
        return generateOperatorCode(mProfile->orString(), ast);
    case GeneratorEquationAstPimpl::Type::XOR:
        if (mProfile->hasXorOperator()) {
            return generateOperatorCode(mProfile->xorString(), ast);
        }

        return mProfile->xorString() + "(" + generateCode(ast->mLeft) + ", " + generateCode(ast->mRight) + ")";
    case GeneratorEquationAstPimpl::Type::NOT:
        return mProfile->notString() + generateCode(ast->mLeft);

        // Calculus elements

    case GeneratorEquationAstPimpl::Type::DIFF:
        return "d(" + generateCode(ast->mRight) + ")/d(" + generateCode(ast->mLeft) + ")";

        // Min/max operators

    case GeneratorEquationAstPimpl::Type::MIN:
        if (parentAst == nullptr) {
            return mProfile->minString() + "(" + generateCode(ast->mLeft, ast) + ", " + generateCode(ast->mRight, ast) + ")";
        }

        return generateCode(ast->mLeft, ast) + ", " + generateCode(ast->mRight, ast);
    case GeneratorEquationAstPimpl::Type::MAX:
        if (parentAst == nullptr) {
            return mProfile->maxString() + "(" + generateCode(ast->mLeft, ast) + ", " + generateCode(ast->mRight, ast) + ")";
        }

        return generateCode(ast->mLeft, ast) + ", " + generateCode(ast->mRight, ast);

        // Gcd/lcm operators

    case GeneratorEquationAstPimpl::Type::GCD:
        if (parentAst == nullptr) {
            return mProfile->gcdString() + "(" + generateCode(ast->mLeft, ast) + ", " + generateCode(ast->mRight, ast) + ")";
        }

        return generateCode(ast->mLeft, ast) + ", " + generateCode(ast->mRight, ast);
    case GeneratorEquationAstPimpl::Type::LCM:
        if (parentAst == nullptr) {
            return mProfile->lcmString() + "(" + generateCode(ast->mLeft, ast) + ", " + generateCode(ast->mRight, ast) + ")";
        }

        return generateCode(ast->mLeft, ast) + ", " + generateCode(ast->mRight, ast);

        // Trigonometric operators

    case GeneratorEquationAstPimpl::Type::SIN:
        return mProfile->sinString() + "(" + generateCode(ast->mLeft) + ")";
    case GeneratorEquationAstPimpl::Type::COS:
        return mProfile->cosString() + "(" + generateCode(ast->mLeft) + ")";
    case GeneratorEquationAstPimpl::Type::TAN:
        return mProfile->tanString() + "(" + generateCode(ast->mLeft) + ")";
    case GeneratorEquationAstPimpl::Type::SEC:
        return mProfile->secString() + "(" + generateCode(ast->mLeft) + ")";
    case GeneratorEquationAstPimpl::Type::CSC:
        return mProfile->cscString() + "(" + generateCode(ast->mLeft) + ")";
    case GeneratorEquationAstPimpl::Type::COT:
        return mProfile->cotString() + "(" + generateCode(ast->mLeft) + ")";
    case GeneratorEquationAstPimpl::Type::SINH:
        return mProfile->sinhString() + "(" + generateCode(ast->mLeft) + ")";
    case GeneratorEquationAstPimpl::Type::COSH:
        return mProfile->coshString() + "(" + generateCode(ast->mLeft) + ")";
    case GeneratorEquationAstPimpl::Type::TANH:
        return mProfile->tanhString() + "(" + generateCode(ast->mLeft) + ")";
    case GeneratorEquationAstPimpl::Type::SECH:
        return mProfile->sechString() + "(" + generateCode(ast->mLeft) + ")";
    case GeneratorEquationAstPimpl::Type::CSCH:
        return mProfile->cschString() + "(" + generateCode(ast->mLeft) + ")";
    case GeneratorEquationAstPimpl::Type::COTH:
        return mProfile->cothString() + "(" + generateCode(ast->mLeft) + ")";
    case GeneratorEquationAstPimpl::Type::ASIN:
        return mProfile->asinString() + "(" + generateCode(ast->mLeft) + ")";
    case GeneratorEquationAstPimpl::Type::ACOS:
        return mProfile->acosString() + "(" + generateCode(ast->mLeft) + ")";
    case GeneratorEquationAstPimpl::Type::ATAN:
        return mProfile->atanString() + "(" + generateCode(ast->mLeft) + ")";
    case GeneratorEquationAstPimpl::Type::ASEC:
        return mProfile->asecString() + "(" + generateCode(ast->mLeft) + ")";
    case GeneratorEquationAstPimpl::Type::ACSC:
        return mProfile->acscString() + "(" + generateCode(ast->mLeft) + ")";
    case GeneratorEquationAstPimpl::Type::ACOT:
        return mProfile->acotString() + "(" + generateCode(ast->mLeft) + ")";
    case GeneratorEquationAstPimpl::Type::ASINH:
        return mProfile->asinhString() + "(" + generateCode(ast->mLeft) + ")";
    case GeneratorEquationAstPimpl::Type::ACOSH:
        return mProfile->acoshString() + "(" + generateCode(ast->mLeft) + ")";
    case GeneratorEquationAstPimpl::Type::ATANH:
        return mProfile->atanhString() + "(" + generateCode(ast->mLeft) + ")";
    case GeneratorEquationAstPimpl::Type::ASECH:
        return mProfile->asechString() + "(" + generateCode(ast->mLeft) + ")";
    case GeneratorEquationAstPimpl::Type::ACSCH:
        return mProfile->acschString() + "(" + generateCode(ast->mLeft) + ")";
    case GeneratorEquationAstPimpl::Type::ACOTH:
        return mProfile->acothString() + "(" + generateCode(ast->mLeft) + ")";

        // Extra operators

    case GeneratorEquationAstPimpl::Type::REM:
        return mProfile->remString() + "(" + generateCode(ast->mLeft) + ", " + generateCode(ast->mRight) + ")";

        // Piecewise statement

    case GeneratorEquationAstPimpl::Type::PIECEWISE:
        if (ast->mRight != nullptr) {
            if (ast->mRight->mType == GeneratorEquationAstPimpl::Type::PIECE) {
                return generateCode(ast->mLeft) + generatePiecewiseElseCode(generateCode(ast->mRight) + generatePiecewiseElseCode(mProfile->nanString()));
            }

            return generateCode(ast->mLeft) + generatePiecewiseElseCode(generateCode(ast->mRight));
        }

        return generateCode(ast->mLeft) + generatePiecewiseElseCode(mProfile->nanString());
    case GeneratorEquationAstPimpl::Type::PIECE:
        return generatePiecewiseIfCode(generateCode(ast->mRight), generateCode(ast->mLeft));
    case GeneratorEquationAstPimpl::Type::OTHERWISE:
        return generateCode(ast->mLeft);

        // Token elements

    case GeneratorEquationAstPimpl::Type::CN:
        return ast->mValue;
    case GeneratorEquationAstPimpl::Type::CI:
        return ast->mVariable->name();

        // Qualifier elements

    case GeneratorEquationAstPimpl::Type::DEGREE:
    case GeneratorEquationAstPimpl::Type::LOGBASE:
    case GeneratorEquationAstPimpl::Type::BVAR:
        return generateCode(ast->mLeft);

        // Constants

    case GeneratorEquationAstPimpl::Type::TRUE:
        return mProfile->trueString();
    case GeneratorEquationAstPimpl::Type::FALSE:
        return mProfile->falseString();
    case GeneratorEquationAstPimpl::Type::E:
        return mProfile->eString();
    case GeneratorEquationAstPimpl::Type::PI:
        return mProfile->piString();
    case GeneratorEquationAstPimpl::Type::INF:
        return mProfile->infString();
    case GeneratorEquationAstPimpl::Type::NAN:
        return mProfile->nanString();
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
    mPimpl->mGenerator = rhs.mPimpl->mGenerator;

    mPimpl->mHasModel = rhs.mPimpl->mHasModel;

    mPimpl->mVariableOfIntegration = rhs.mPimpl->mVariableOfIntegration;

    mPimpl->mVariables = rhs.mPimpl->mVariables;
    mPimpl->mEquations = rhs.mPimpl->mEquations;

    mPimpl->mProfile = rhs.mPimpl->mProfile;

    mPimpl->mNeedFactorial = rhs.mPimpl->mNeedFactorial;

    mPimpl->mNeedMin = rhs.mPimpl->mNeedMin;
    mPimpl->mNeedMax = rhs.mPimpl->mNeedMax;

    mPimpl->mNeedGcd = rhs.mPimpl->mNeedGcd;
    mPimpl->mNeedLcm = rhs.mPimpl->mNeedLcm;

    mPimpl->mNeedSec = rhs.mPimpl->mNeedSec;
    mPimpl->mNeedCsc = rhs.mPimpl->mNeedCsc;
    mPimpl->mNeedCot = rhs.mPimpl->mNeedCot;
    mPimpl->mNeedSech = rhs.mPimpl->mNeedSech;
    mPimpl->mNeedCsch = rhs.mPimpl->mNeedCsch;
    mPimpl->mNeedCoth = rhs.mPimpl->mNeedCoth;
    mPimpl->mNeedAsec = rhs.mPimpl->mNeedAsec;
    mPimpl->mNeedAcsc = rhs.mPimpl->mNeedAcsc;
    mPimpl->mNeedAcot = rhs.mPimpl->mNeedAcot;
    mPimpl->mNeedAsech = rhs.mPimpl->mNeedAsech;
    mPimpl->mNeedAcsch = rhs.mPimpl->mNeedAcsch;
    mPimpl->mNeedAcoth = rhs.mPimpl->mNeedAcoth;
}

Generator::Generator(Generator &&rhs) noexcept
    : Logger(std::move(rhs))
    , mPimpl(rhs.mPimpl)
{
    rhs.mPimpl = nullptr;
}

Generator &Generator::operator=(Generator rhs)
{
    Logger::operator=(rhs);
    rhs.swap(*this);
    return *this;
}

void Generator::swap(Generator &rhs)
{
    std::swap(mPimpl, rhs.mPimpl);
}

void Generator::setProfile(const GeneratorProfilePtr &profile)
{
    mPimpl->mProfile = profile;
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
#ifdef TRACES
    for (size_t i = 0; i < errorCount(); ++i) {
        std::cout << "Generator error #" << i + 1 << ": " << error(i)->description() << std::endl;
    }
#endif
}

Generator::ModelType Generator::modelType() const
{
    if (!mPimpl->hasValidModel()) {
        return Generator::ModelType::UNKNOWN;
    }

    if (mPimpl->mVariableOfIntegration != nullptr) {
        return Generator::ModelType::ODE;
    }

    return Generator::ModelType::ALGEBRAIC;
}

size_t Generator::stateCount() const
{
    if (!mPimpl->hasValidModel()) {
        return 0;
    }

    size_t res = 0;

    for (const auto &variable : mPimpl->mVariables) {
        if (variable->mType == GeneratorVariablePimpl::Type::STATE) {
            ++res;
        }
    }

    return res;
}

size_t Generator::variableCount() const
{
    if (!mPimpl->hasValidModel()) {
        return 0;
    }

    size_t res = 0;

    for (const auto &variable : mPimpl->mVariables) {
        if ((variable->mType == GeneratorVariablePimpl::Type::ALGEBRAIC)
            || (variable->mType == GeneratorVariablePimpl::Type::CONSTANT)
            || (variable->mType == GeneratorVariablePimpl::Type::COMPUTED_CONSTANT)) {
            ++res;
        }
    }

    return res;
}

GeneratorVariablePtr Generator::variableOfIntegration() const
{
    //TODO: to be done...
    return {};
}

GeneratorVariablePtr Generator::state(size_t index) const
{
    //TODO: to be done...
    (void)index;

    return {};
}

GeneratorVariablePtr Generator::variable(size_t index) const
{
    //TODO: to be done...
    (void)index;

    return {};
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

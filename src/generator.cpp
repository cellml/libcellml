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
#include <list>
#include <vector>

#undef NAN

#ifdef __linux__
#    undef TRUE
#    undef FALSE
#endif

//ISSUE359: remove the below code once we are done testing things.
#define TRACES
#ifdef TRACES
#    include <iostream>
#endif
namespace libcellml {

struct GeneratorVariableImpl
{
    enum class Type
    {
        UNKNOWN,
        SHOULD_BE_STATE,
        VARIABLE_OF_INTEGRATION,
        STATE,
        CONSTANT,
        COMPUTED_CONSTANT,
        ALGEBRAIC
    };

    Type mType = Type::UNKNOWN;

    VariablePtr mVariable;

    bool mComputed = false;

    explicit GeneratorVariableImpl(const VariablePtr &variable);

    void setVariable(const VariablePtr &variable);

    void makeVariableOfIntegration();
    void makeState();
};

using GeneratorVariableImplPtr = std::shared_ptr<GeneratorVariableImpl>;

GeneratorVariableImpl::GeneratorVariableImpl(const VariablePtr &variable)
{
    setVariable(variable);
}

void GeneratorVariableImpl::setVariable(const VariablePtr &variable)
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

void GeneratorVariableImpl::makeVariableOfIntegration()
{
    mType = Type::VARIABLE_OF_INTEGRATION;
}

void GeneratorVariableImpl::makeState()
{
    if (mType == Type::UNKNOWN) {
        mType = Type::SHOULD_BE_STATE;
    } else if (mType == Type::CONSTANT) {
        mType = Type::STATE;
    }
}

struct GeneratorEquationAstImpl;
using GeneratorEquationAstImplPtr = std::shared_ptr<GeneratorEquationAstImpl>;

struct GeneratorEquationAstImpl
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

    GeneratorEquationAstImplPtr mParent;

    GeneratorEquationAstImplPtr mLeft;
    GeneratorEquationAstImplPtr mRight;

    explicit GeneratorEquationAstImpl(Type type, const std::string &value,
                                      const VariablePtr &variable,
                                      const GeneratorEquationAstImplPtr &parent);
    explicit GeneratorEquationAstImpl();
    explicit GeneratorEquationAstImpl(Type type,
                                      const GeneratorEquationAstImplPtr &parent);
    explicit GeneratorEquationAstImpl(Type type, const std::string &value,
                                      const GeneratorEquationAstImplPtr &parent);
    explicit GeneratorEquationAstImpl(Type type, const VariablePtr &variable,
                                      const GeneratorEquationAstImplPtr &parent);
};

GeneratorEquationAstImpl::GeneratorEquationAstImpl(Type type, const std::string &value,
                                                   const VariablePtr &variable,
                                                   const GeneratorEquationAstImplPtr &parent)
    : mType(type)
    , mValue(value)
    , mVariable(variable)
    , mParent(parent)
    , mLeft(nullptr)
    , mRight(nullptr)
{
}

GeneratorEquationAstImpl::GeneratorEquationAstImpl()
    : GeneratorEquationAstImpl(Type::EQ, "", nullptr, nullptr)
{
}

GeneratorEquationAstImpl::GeneratorEquationAstImpl(Type type,
                                                   const GeneratorEquationAstImplPtr &parent)
    : GeneratorEquationAstImpl(type, "", nullptr, parent)
{
}

GeneratorEquationAstImpl::GeneratorEquationAstImpl(Type type, const std::string &value,
                                                   const GeneratorEquationAstImplPtr &parent)
    : GeneratorEquationAstImpl(type, value, nullptr, parent)
{
}

GeneratorEquationAstImpl::GeneratorEquationAstImpl(Type type, const VariablePtr &variable,
                                                   const GeneratorEquationAstImplPtr &parent)
    : GeneratorEquationAstImpl(type, "", variable, parent)
{
}

struct GeneratorEquationImpl
{
    enum class Type
    {
        UNKNOWN,
        CONSTANT,
        RATE,
        ALGEBRAIC
    };

    Type mType = Type::UNKNOWN;

    size_t mOrder = 0;

    GeneratorEquationAstImplPtr mAst;

    std::list<GeneratorVariableImplPtr> mVariables;
    std::list<GeneratorVariableImplPtr> mOdeVariables;

    bool mConstant = true;

    explicit GeneratorEquationImpl();

    void addVariable(const GeneratorVariableImplPtr &variable);
    void addOdeVariable(const GeneratorVariableImplPtr &odeVariable);

    static bool containsNonConstantVariable(const std::list<GeneratorVariableImplPtr> &variables);

    static bool knownVariable(const GeneratorVariableImplPtr &variable);
    static bool knownOdeVariable(const GeneratorVariableImplPtr &odeVariable);

    void check(size_t &order);
};

using GeneratorEquationImplPtr = std::shared_ptr<GeneratorEquationImpl>;

GeneratorEquationImpl::GeneratorEquationImpl()
    : mAst(std::make_shared<GeneratorEquationAstImpl>())
{
}

void GeneratorEquationImpl::addVariable(const GeneratorVariableImplPtr &variable)
{
    if (std::find(mVariables.begin(), mVariables.end(), variable) == mVariables.end()) {
        mVariables.push_back(variable);
    }
}

void GeneratorEquationImpl::addOdeVariable(const GeneratorVariableImplPtr &odeVariable)
{
    if (std::find(mOdeVariables.begin(), mOdeVariables.end(), odeVariable) == mOdeVariables.end()) {
        mOdeVariables.push_back(odeVariable);
    }
}

bool GeneratorEquationImpl::containsNonConstantVariable(const std::list<GeneratorVariableImplPtr> &variables)
{
    return std::find_if(variables.begin(), variables.end(), [](const GeneratorVariableImplPtr &variable) {
               return (variable->mType != GeneratorVariableImpl::Type::UNKNOWN)
                      && (variable->mType != GeneratorVariableImpl::Type::CONSTANT);
           })
           != std::end(variables);
}

bool GeneratorEquationImpl::knownVariable(const GeneratorVariableImplPtr &variable)
{
    return variable->mComputed
           || (variable->mType == GeneratorVariableImpl::Type::VARIABLE_OF_INTEGRATION)
           || (variable->mType == GeneratorVariableImpl::Type::STATE)
           || (variable->mType == GeneratorVariableImpl::Type::CONSTANT);
}

bool GeneratorEquationImpl::knownOdeVariable(const GeneratorVariableImplPtr &odeVariable)
{
    return odeVariable->mComputed
           || (odeVariable->mType == GeneratorVariableImpl::Type::VARIABLE_OF_INTEGRATION);
}

#ifdef TRACES
void outputVariables(const std::list<GeneratorVariableImplPtr> &variables, bool ode)
{
    for (const auto &variable : variables) {
        std::string type;
        switch (variable->mType) {
        case GeneratorVariableImpl::Type::UNKNOWN:
            type = "unknown";
            break;
        case GeneratorVariableImpl::Type::SHOULD_BE_STATE:
            type = "should be state";
            break;
        case GeneratorVariableImpl::Type::VARIABLE_OF_INTEGRATION:
            type = "variable of integration";
            break;
        case GeneratorVariableImpl::Type::STATE:
            type = ode ? "rate" : "state";
            break;
        case GeneratorVariableImpl::Type::CONSTANT:
            type = "constant";
            break;
        case GeneratorVariableImpl::Type::COMPUTED_CONSTANT:
            type = "computed constant";
            break;
        case GeneratorVariableImpl::Type::ALGEBRAIC:
            type = "algebraic";
            break;
        }
        std::cout << "                 " << variable->mVariable->name() << ": " << type << std::endl;
    }
}
#endif

void GeneratorEquationImpl::check(size_t &order)
{
    // Nothing to check if the equation has already been given an order (i.e.
    // everything is fine) or if there is one known variable / ODE variable left
    // (i.e. this equation is an overconstraint)

    if (mOrder != 0) {
        return;
    }

    if (mVariables.size() + mOdeVariables.size() == 1) {
        GeneratorVariableImplPtr variable = (mVariables.size() == 1) ? mVariables.front() : mOdeVariables.front();

        if (variable->mType != GeneratorVariableImpl::Type::UNKNOWN) {
            return;
        }
    }

    // Determine, from the (new) known variables / ODE variables, whether the
    // equation is constant

    mConstant = mConstant
                && !containsNonConstantVariable(mVariables)
                && !containsNonConstantVariable(mOdeVariables);

    // Stop tracking (new) known variables / ODE variables
#ifdef TRACES
    std::cout << "---------------------------------------" << std::endl;
    std::cout << "[" << this << "] [BEFORE] " << mVariables.size() << " | " << mOdeVariables.size() << std::endl;
    outputVariables(mVariables, false);
    std::cout << "                 ---" << std::endl;
    outputVariables(mOdeVariables, true);
#endif

    mVariables.remove_if(knownVariable);
    mOdeVariables.remove_if(knownOdeVariable);

    // If there is one variable of one ODE variable left and it is of unknown
    // type then update the type of that variable / ODE variable and set the
    // order of the equation

    if (mVariables.size() + mOdeVariables.size() == 1) {
        GeneratorVariableImplPtr variable = (mVariables.size() == 1) ? mVariables.front() : mOdeVariables.front();

        if (variable->mType == GeneratorVariableImpl::Type::UNKNOWN) {
            variable->mType = mConstant ? GeneratorVariableImpl::Type::COMPUTED_CONSTANT : GeneratorVariableImpl::Type::ALGEBRAIC;
            variable->mComputed = true;

            mOrder = ++order;
        }
    }
#ifdef TRACES
    std::cout << "[" << this << "] [AFTER]  " << mVariables.size() << " | " << mOdeVariables.size() << std::endl;
    outputVariables(mVariables, false);
    std::cout << "                 ---" << std::endl;
    outputVariables(mOdeVariables, true);
    std::cout << "---------------------------------------" << std::endl;
#endif
}

struct Generator::GeneratorImpl
{
    Generator *mGenerator = nullptr;

    bool mHasModel = false;

    VariablePtr mVariableOfIntegration;

    std::vector<GeneratorVariableImplPtr> mVariables;
    std::vector<GeneratorEquationImplPtr> mEquations;

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

    GeneratorVariableImplPtr generatorVariable(const VariablePtr &variable);

    void processNode(const XmlNodePtr &node, GeneratorEquationAstImplPtr &ast,
                     const GeneratorEquationAstImplPtr &astParent,
                     const ComponentPtr &component,
                     const GeneratorEquationImplPtr &equation);
    GeneratorEquationImplPtr processNode(const XmlNodePtr &node,
                                         const ComponentPtr &component);
    void processComponent(const ComponentPtr &component);
    void processEquationAst(const GeneratorEquationAstImplPtr &ast);
    void processModel(const ModelPtr &model);

    bool isRelationalOperator(const GeneratorEquationAstImplPtr &ast) const;
    bool isPlusOperator(const GeneratorEquationAstImplPtr &ast) const;
    bool isMinusOperator(const GeneratorEquationAstImplPtr &ast) const;
    bool isTimesOperator(const GeneratorEquationAstImplPtr &ast) const;
    bool isDivideOperator(const GeneratorEquationAstImplPtr &ast) const;
    bool isPowerOperator(const GeneratorEquationAstImplPtr &ast) const;
    bool isRootOperator(const GeneratorEquationAstImplPtr &ast) const;
    bool isLogicalOrBitwiseOperator(const GeneratorEquationAstImplPtr &ast) const;
    bool isAndOperator(const GeneratorEquationAstImplPtr &ast) const;
    bool isOrOperator(const GeneratorEquationAstImplPtr &ast) const;
    bool isXorOperator(const GeneratorEquationAstImplPtr &ast) const;
    bool isPiecewiseStatement(const GeneratorEquationAstImplPtr &ast) const;

    std::string generateOperatorCode(const std::string &op,
                                     const GeneratorEquationAstImplPtr &ast) const;
    std::string generateMinusUnaryCode(const GeneratorEquationAstImplPtr &ast) const;
    std::string generatePiecewiseIfCode(const std::string &condition,
                                        const std::string &value) const;
    std::string generatePiecewiseElseCode(const std::string &value) const;
    std::string generateCode(const GeneratorEquationAstImplPtr &ast,
                             const GeneratorEquationAstImplPtr &parentAst = nullptr) const;
};

bool Generator::GeneratorImpl::hasValidModel() const
{
    return mHasModel && (mGenerator->errorCount() == 0);
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

GeneratorVariableImplPtr Generator::GeneratorImpl::generatorVariable(const VariablePtr &variable)
{
    // Find and return, if there is one, the generator variable associated with
    // given variable

    for (const auto &generatorVariable : mVariables) {
        if (variable->isEquivalentVariable(generatorVariable->mVariable)) {
            return generatorVariable;
        }
    }

    // No generator variable exists for the given variable, so create one, track
    // it and return it

    GeneratorVariableImplPtr generatorVariable = std::make_shared<GeneratorVariableImpl>(variable);

    mVariables.push_back(generatorVariable);

    return generatorVariable;
}

void Generator::GeneratorImpl::processNode(const XmlNodePtr &node,
                                           GeneratorEquationAstImplPtr &ast,
                                           const GeneratorEquationAstImplPtr &astParent,
                                           const ComponentPtr &component,
                                           const GeneratorEquationImplPtr &equation)
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
            GeneratorEquationAstImplPtr astRight;
            GeneratorEquationAstImplPtr tempAst;

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
        // GeneratorEquationAstImpl::Type::EQ type.

        if (!node->parent()->parent()->isMathmlElement("math")) {
            ast = std::make_shared<GeneratorEquationAstImpl>(GeneratorEquationAstImpl::Type::EQEQ, astParent);
        }
    } else if (node->isMathmlElement("neq")) {
        ast = std::make_shared<GeneratorEquationAstImpl>(GeneratorEquationAstImpl::Type::NEQ, astParent);
    } else if (node->isMathmlElement("lt")) {
        ast = std::make_shared<GeneratorEquationAstImpl>(GeneratorEquationAstImpl::Type::LT, astParent);
    } else if (node->isMathmlElement("leq")) {
        ast = std::make_shared<GeneratorEquationAstImpl>(GeneratorEquationAstImpl::Type::LEQ, astParent);
    } else if (node->isMathmlElement("gt")) {
        ast = std::make_shared<GeneratorEquationAstImpl>(GeneratorEquationAstImpl::Type::GT, astParent);
    } else if (node->isMathmlElement("geq")) {
        ast = std::make_shared<GeneratorEquationAstImpl>(GeneratorEquationAstImpl::Type::GEQ, astParent);

        // Arithmetic operators

    } else if (node->isMathmlElement("plus")) {
        ast = std::make_shared<GeneratorEquationAstImpl>(GeneratorEquationAstImpl::Type::PLUS, astParent);
    } else if (node->isMathmlElement("minus")) {
        ast = std::make_shared<GeneratorEquationAstImpl>(GeneratorEquationAstImpl::Type::MINUS, astParent);
    } else if (node->isMathmlElement("times")) {
        ast = std::make_shared<GeneratorEquationAstImpl>(GeneratorEquationAstImpl::Type::TIMES, astParent);
    } else if (node->isMathmlElement("divide")) {
        ast = std::make_shared<GeneratorEquationAstImpl>(GeneratorEquationAstImpl::Type::DIVIDE, astParent);
    } else if (node->isMathmlElement("power")) {
        ast = std::make_shared<GeneratorEquationAstImpl>(GeneratorEquationAstImpl::Type::POWER, astParent);
    } else if (node->isMathmlElement("root")) {
        ast = std::make_shared<GeneratorEquationAstImpl>(GeneratorEquationAstImpl::Type::ROOT, astParent);
    } else if (node->isMathmlElement("abs")) {
        ast = std::make_shared<GeneratorEquationAstImpl>(GeneratorEquationAstImpl::Type::ABS, astParent);
    } else if (node->isMathmlElement("exp")) {
        ast = std::make_shared<GeneratorEquationAstImpl>(GeneratorEquationAstImpl::Type::EXP, astParent);
    } else if (node->isMathmlElement("ln")) {
        ast = std::make_shared<GeneratorEquationAstImpl>(GeneratorEquationAstImpl::Type::LN, astParent);
    } else if (node->isMathmlElement("log")) {
        ast = std::make_shared<GeneratorEquationAstImpl>(GeneratorEquationAstImpl::Type::LOG, astParent);
    } else if (node->isMathmlElement("ceiling")) {
        ast = std::make_shared<GeneratorEquationAstImpl>(GeneratorEquationAstImpl::Type::CEILING, astParent);
    } else if (node->isMathmlElement("floor")) {
        ast = std::make_shared<GeneratorEquationAstImpl>(GeneratorEquationAstImpl::Type::FLOOR, astParent);
    } else if (node->isMathmlElement("factorial")) {
        ast = std::make_shared<GeneratorEquationAstImpl>(GeneratorEquationAstImpl::Type::FACTORIAL, astParent);

        mNeedFactorial = true;

        // Logical operators

    } else if (node->isMathmlElement("and")) {
        ast = std::make_shared<GeneratorEquationAstImpl>(GeneratorEquationAstImpl::Type::AND, astParent);
    } else if (node->isMathmlElement("or")) {
        ast = std::make_shared<GeneratorEquationAstImpl>(GeneratorEquationAstImpl::Type::OR, astParent);
    } else if (node->isMathmlElement("xor")) {
        ast = std::make_shared<GeneratorEquationAstImpl>(GeneratorEquationAstImpl::Type::XOR, astParent);
    } else if (node->isMathmlElement("not")) {
        ast = std::make_shared<GeneratorEquationAstImpl>(GeneratorEquationAstImpl::Type::NOT, astParent);

        // Calculus elements

    } else if (node->isMathmlElement("diff")) {
        ast = std::make_shared<GeneratorEquationAstImpl>(GeneratorEquationAstImpl::Type::DIFF, astParent);

        // Min/max operators

    } else if (node->isMathmlElement("min")) {
        ast = std::make_shared<GeneratorEquationAstImpl>(GeneratorEquationAstImpl::Type::MIN, astParent);

        mNeedMin = true;
    } else if (node->isMathmlElement("max")) {
        ast = std::make_shared<GeneratorEquationAstImpl>(GeneratorEquationAstImpl::Type::MAX, astParent);

        mNeedMax = true;

        // Gcd/lcm operators

    } else if (node->isMathmlElement("gcd")) {
        ast = std::make_shared<GeneratorEquationAstImpl>(GeneratorEquationAstImpl::Type::GCD, astParent);

        mNeedGcd = true;
    } else if (node->isMathmlElement("lcm")) {
        ast = std::make_shared<GeneratorEquationAstImpl>(GeneratorEquationAstImpl::Type::LCM, astParent);

        mNeedLcm = true;

        // Trigonometric operators

    } else if (node->isMathmlElement("sin")) {
        ast = std::make_shared<GeneratorEquationAstImpl>(GeneratorEquationAstImpl::Type::SIN, astParent);
    } else if (node->isMathmlElement("cos")) {
        ast = std::make_shared<GeneratorEquationAstImpl>(GeneratorEquationAstImpl::Type::COS, astParent);
    } else if (node->isMathmlElement("tan")) {
        ast = std::make_shared<GeneratorEquationAstImpl>(GeneratorEquationAstImpl::Type::TAN, astParent);
    } else if (node->isMathmlElement("sec")) {
        ast = std::make_shared<GeneratorEquationAstImpl>(GeneratorEquationAstImpl::Type::SEC, astParent);

        mNeedSec = true;
    } else if (node->isMathmlElement("csc")) {
        ast = std::make_shared<GeneratorEquationAstImpl>(GeneratorEquationAstImpl::Type::CSC, astParent);

        mNeedCsc = true;
    } else if (node->isMathmlElement("cot")) {
        ast = std::make_shared<GeneratorEquationAstImpl>(GeneratorEquationAstImpl::Type::COT, astParent);

        mNeedCot = true;
    } else if (node->isMathmlElement("sinh")) {
        ast = std::make_shared<GeneratorEquationAstImpl>(GeneratorEquationAstImpl::Type::SINH, astParent);
    } else if (node->isMathmlElement("cosh")) {
        ast = std::make_shared<GeneratorEquationAstImpl>(GeneratorEquationAstImpl::Type::COSH, astParent);
    } else if (node->isMathmlElement("tanh")) {
        ast = std::make_shared<GeneratorEquationAstImpl>(GeneratorEquationAstImpl::Type::TANH, astParent);
    } else if (node->isMathmlElement("sech")) {
        ast = std::make_shared<GeneratorEquationAstImpl>(GeneratorEquationAstImpl::Type::SECH, astParent);

        mNeedSech = true;
    } else if (node->isMathmlElement("csch")) {
        ast = std::make_shared<GeneratorEquationAstImpl>(GeneratorEquationAstImpl::Type::CSCH, astParent);

        mNeedCsch = true;
    } else if (node->isMathmlElement("coth")) {
        ast = std::make_shared<GeneratorEquationAstImpl>(GeneratorEquationAstImpl::Type::COTH, astParent);

        mNeedCoth = true;
    } else if (node->isMathmlElement("arcsin")) {
        ast = std::make_shared<GeneratorEquationAstImpl>(GeneratorEquationAstImpl::Type::ASIN, astParent);
    } else if (node->isMathmlElement("arccos")) {
        ast = std::make_shared<GeneratorEquationAstImpl>(GeneratorEquationAstImpl::Type::ACOS, astParent);
    } else if (node->isMathmlElement("arctan")) {
        ast = std::make_shared<GeneratorEquationAstImpl>(GeneratorEquationAstImpl::Type::ATAN, astParent);
    } else if (node->isMathmlElement("arcsec")) {
        ast = std::make_shared<GeneratorEquationAstImpl>(GeneratorEquationAstImpl::Type::ASEC, astParent);

        mNeedAsec = true;
    } else if (node->isMathmlElement("arccsc")) {
        ast = std::make_shared<GeneratorEquationAstImpl>(GeneratorEquationAstImpl::Type::ACSC, astParent);

        mNeedAcsc = true;
    } else if (node->isMathmlElement("arccot")) {
        ast = std::make_shared<GeneratorEquationAstImpl>(GeneratorEquationAstImpl::Type::ACOT, astParent);

        mNeedAcot = true;
    } else if (node->isMathmlElement("arcsinh")) {
        ast = std::make_shared<GeneratorEquationAstImpl>(GeneratorEquationAstImpl::Type::ASINH, astParent);
    } else if (node->isMathmlElement("arccosh")) {
        ast = std::make_shared<GeneratorEquationAstImpl>(GeneratorEquationAstImpl::Type::ACOSH, astParent);
    } else if (node->isMathmlElement("arctanh")) {
        ast = std::make_shared<GeneratorEquationAstImpl>(GeneratorEquationAstImpl::Type::ATANH, astParent);
    } else if (node->isMathmlElement("arcsech")) {
        ast = std::make_shared<GeneratorEquationAstImpl>(GeneratorEquationAstImpl::Type::ASECH, astParent);

        mNeedAsech = true;
    } else if (node->isMathmlElement("arccsch")) {
        ast = std::make_shared<GeneratorEquationAstImpl>(GeneratorEquationAstImpl::Type::ACSCH, astParent);

        mNeedAcsch = true;
    } else if (node->isMathmlElement("arccoth")) {
        ast = std::make_shared<GeneratorEquationAstImpl>(GeneratorEquationAstImpl::Type::ACOTH, astParent);

        mNeedAcoth = true;

        // Extra operators

    } else if (node->isMathmlElement("rem")) {
        ast = std::make_shared<GeneratorEquationAstImpl>(GeneratorEquationAstImpl::Type::REM, astParent);

        // Piecewise statement

    } else if (node->isMathmlElement("piecewise")) {
        size_t childCount = mathmlChildCount(node);

        ast = std::make_shared<GeneratorEquationAstImpl>(GeneratorEquationAstImpl::Type::PIECEWISE, astParent);

        processNode(mathmlChildNode(node, 0), ast->mLeft, ast, component, equation);

        if (childCount >= 2) {
            GeneratorEquationAstImplPtr astRight;
            GeneratorEquationAstImplPtr tempAst;

            processNode(mathmlChildNode(node, childCount - 1), astRight, nullptr, component, equation);

            for (size_t i = childCount - 2; i > 0; --i) {
                tempAst = std::make_shared<GeneratorEquationAstImpl>(GeneratorEquationAstImpl::Type::PIECEWISE, astParent);

                processNode(mathmlChildNode(node, i), tempAst->mLeft, tempAst, component, equation);

                astRight->mParent = tempAst;

                tempAst->mRight = astRight;
                astRight = tempAst;
            }

            astRight->mParent = ast;

            ast->mRight = astRight;
        }
    } else if (node->isMathmlElement("piece")) {
        ast = std::make_shared<GeneratorEquationAstImpl>(GeneratorEquationAstImpl::Type::PIECE, astParent);

        processNode(mathmlChildNode(node, 0), ast->mLeft, ast, component, equation);
        processNode(mathmlChildNode(node, 1), ast->mRight, ast, component, equation);
    } else if (node->isMathmlElement("otherwise")) {
        ast = std::make_shared<GeneratorEquationAstImpl>(GeneratorEquationAstImpl::Type::OTHERWISE, astParent);

        processNode(mathmlChildNode(node, 0), ast->mLeft, ast, component, equation);

        // Token elements

    } else if (node->isMathmlElement("cn")) {
        ast = std::make_shared<GeneratorEquationAstImpl>(GeneratorEquationAstImpl::Type::CN, node->firstChild()->convertToString(), astParent);
    } else if (node->isMathmlElement("ci")) {
        VariablePtr variable = component->variable(node->firstChild()->convertToString());

        ast = std::make_shared<GeneratorEquationAstImpl>(GeneratorEquationAstImpl::Type::CI, variable, astParent);

        // Have our equation track the variable / ODE variable (by ODE variable,
        // we mean a variable that is used in a `diff` element, i.e. a "normal"
        // variable or the variable of integration)

        GeneratorVariableImplPtr generatorVariable = Generator::GeneratorImpl::generatorVariable(variable);

        if ((node->parent()->firstChild()->isMathmlElement("diff")
             || (node->parent()->isMathmlElement("bvar")
                 && node->parent()->parent()->firstChild()->isMathmlElement("diff")))) {
            equation->addOdeVariable(generatorVariable);
        } else {
            equation->addVariable(generatorVariable);
        }

        // Qualifier elements

    } else if (node->isMathmlElement("degree")) {
        ast = std::make_shared<GeneratorEquationAstImpl>(GeneratorEquationAstImpl::Type::DEGREE, astParent);

        processNode(mathmlChildNode(node, 0), ast->mLeft, ast, component, equation);
    } else if (node->isMathmlElement("logbase")) {
        ast = std::make_shared<GeneratorEquationAstImpl>(GeneratorEquationAstImpl::Type::LOGBASE, astParent);

        processNode(mathmlChildNode(node, 0), ast->mLeft, ast, component, equation);
    } else if (node->isMathmlElement("bvar")) {
        ast = std::make_shared<GeneratorEquationAstImpl>(GeneratorEquationAstImpl::Type::BVAR, astParent);

        processNode(mathmlChildNode(node, 0), ast->mLeft, ast, component, equation);

        XmlNodePtr rightNode = mathmlChildNode(node, 1);

        if (rightNode != nullptr) {
            processNode(rightNode, ast->mRight, ast, component, equation);
        }

        // Constants

    } else if (node->isMathmlElement("true")) {
        ast = std::make_shared<GeneratorEquationAstImpl>(GeneratorEquationAstImpl::Type::TRUE, astParent);
    } else if (node->isMathmlElement("false")) {
        ast = std::make_shared<GeneratorEquationAstImpl>(GeneratorEquationAstImpl::Type::FALSE, astParent);
    } else if (node->isMathmlElement("exponentiale")) {
        ast = std::make_shared<GeneratorEquationAstImpl>(GeneratorEquationAstImpl::Type::E, astParent);
    } else if (node->isMathmlElement("pi")) {
        ast = std::make_shared<GeneratorEquationAstImpl>(GeneratorEquationAstImpl::Type::PI, astParent);
    } else if (node->isMathmlElement("infinity")) {
        ast = std::make_shared<GeneratorEquationAstImpl>(GeneratorEquationAstImpl::Type::INF, astParent);
    } else if (node->isMathmlElement("notanumber")) {
        ast = std::make_shared<GeneratorEquationAstImpl>(GeneratorEquationAstImpl::Type::NAN, astParent);
    }
}

GeneratorEquationImplPtr Generator::GeneratorImpl::processNode(const XmlNodePtr &node,
                                                               const ComponentPtr &component)
{
    // Create and keep track of the equation associated with the given node

    GeneratorEquationImplPtr equation = std::make_shared<GeneratorEquationImpl>();

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
        // Retrieve the corresponding generator variable

        VariablePtr variable = component->variable(i);

        GeneratorVariableImplPtr generatorVariable = Generator::GeneratorImpl::generatorVariable(variable);

        // Replace the variable held by generatorVariable, in case the existing
        // one has no initial value while componentVariable does. Otherwise,
        // generate an error if the variable held by generatorVariable and
        // componentVariable are both initialised

        if (!variable->initialValue().empty()
            && generatorVariable->mVariable->initialValue().empty()) {
            generatorVariable->setVariable(variable);
        } else if ((variable != generatorVariable->mVariable)
                   && !variable->initialValue().empty()
                   && !generatorVariable->mVariable->initialValue().empty()) {
            ModelPtr model = component->parentModel();
            ComponentPtr trackedVariableComponent = generatorVariable->mVariable->parentComponent();
            ModelPtr trackedVariableModel = trackedVariableComponent->parentModel();
            ErrorPtr err = std::make_shared<Error>();

            err->setDescription("Variable '" + variable->name() + "' in component '" + component->name() + "' of model '" + model->name() + "' and "
                                                                                                                                            "variable '"
                                + generatorVariable->mVariable->name() + "' in component '" + trackedVariableComponent->name() + "' of model '" + trackedVariableModel->name() + "' are equivalent and cannot therefore both be initialised.");
            err->setKind(Error::Kind::GENERATOR);

            mGenerator->addError(err);
        }
    }

    // Do the same for the components encapsulated by the given component

    for (size_t i = 0; i < component->componentCount(); ++i) {
        processComponent(component->component(i));
    }
}

void Generator::GeneratorImpl::processEquationAst(const GeneratorEquationAstImplPtr &ast)
{
    // Look for the definition of a variable of integration and make sure that
    // we don't have more than one of them and that it's not initialised

    GeneratorEquationAstImplPtr astParent = ast->mParent;
    GeneratorEquationAstImplPtr astGrandParent = (astParent != nullptr) ? astParent->mParent : nullptr;
    GeneratorEquationAstImplPtr astGreatGrandParent = (astGrandParent != nullptr) ? astGrandParent->mParent : nullptr;

    if ((ast->mType == GeneratorEquationAstImpl::Type::CI)
        && (astParent != nullptr) && (astParent->mType == GeneratorEquationAstImpl::Type::BVAR)
        && (astGrandParent != nullptr) && (astGrandParent->mType == GeneratorEquationAstImpl::Type::DIFF)) {
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

    if ((ast->mType == GeneratorEquationAstImpl::Type::CN)
        && (astParent != nullptr) && (astParent->mType == GeneratorEquationAstImpl::Type::DEGREE)
        && (astGrandParent != nullptr) && (astGrandParent->mType == GeneratorEquationAstImpl::Type::BVAR)
        && (astGreatGrandParent != nullptr) && (astGreatGrandParent->mType == GeneratorEquationAstImpl::Type::DIFF)) {
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

    if ((ast->mType == GeneratorEquationAstImpl::Type::CI)
        && (astParent != nullptr) && (astParent->mType == GeneratorEquationAstImpl::Type::DIFF)) {
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

    // Process our different equations' AST

    if (mGenerator->errorCount() == 0) {
        for (const auto &equation : mEquations) {
            processEquationAst(equation->mAst);
        }
    }

    // Loop over our equations, checking wich variable, if any, can be
    // determined using a given equation

    size_t order = 0;

    if (mGenerator->errorCount() == 0) {
        for (;;) {
            size_t oldAllVariableCount = 0;
            size_t newAllVariableCount = 0;

            for (const auto &equation : mEquations) {
                oldAllVariableCount += equation->mVariables.size() + equation->mOdeVariables.size();

                equation->check(order);

                newAllVariableCount += equation->mVariables.size() + equation->mOdeVariables.size();
            }

            if ((newAllVariableCount == mEquations.size()) || (oldAllVariableCount == newAllVariableCount)) {
                break;
            }
        }
    }

    // Make sure that all our variables are valid

    if (mGenerator->errorCount() == 0) {
        for (const auto &variable : mVariables) {
            std::string errorType;

            switch (variable->mType) {
            case GeneratorVariableImpl::Type::UNKNOWN:
                errorType = "is of unknown type";

                break;
            case GeneratorVariableImpl::Type::SHOULD_BE_STATE:
                errorType = "is used in an ODE, but it is not initialised";

                break;
            case GeneratorVariableImpl::Type::VARIABLE_OF_INTEGRATION:
            case GeneratorVariableImpl::Type::STATE:
            case GeneratorVariableImpl::Type::CONSTANT:
            case GeneratorVariableImpl::Type::COMPUTED_CONSTANT:
            case GeneratorVariableImpl::Type::ALGEBRAIC:
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
    }
}

std::string replace(const std::string &string, const std::string &from, const std::string &to)
{
    return std::string(string).replace(string.find(from), from.length(), to);
}

bool Generator::GeneratorImpl::isRelationalOperator(const GeneratorEquationAstImplPtr &ast) const
{
    return (ast->mType == GeneratorEquationAstImpl::Type::EQEQ)
           || (ast->mType == GeneratorEquationAstImpl::Type::NEQ)
           || (ast->mType == GeneratorEquationAstImpl::Type::LT)
           || (ast->mType == GeneratorEquationAstImpl::Type::LEQ)
           || (ast->mType == GeneratorEquationAstImpl::Type::GT)
           || (ast->mType == GeneratorEquationAstImpl::Type::GEQ);
}

bool Generator::GeneratorImpl::isPlusOperator(const GeneratorEquationAstImplPtr &ast) const
{
    return ast->mType == GeneratorEquationAstImpl::Type::PLUS;
}

bool Generator::GeneratorImpl::isMinusOperator(const GeneratorEquationAstImplPtr &ast) const
{
    return ast->mType == GeneratorEquationAstImpl::Type::MINUS;
}

bool Generator::GeneratorImpl::isTimesOperator(const GeneratorEquationAstImplPtr &ast) const
{
    return ast->mType == GeneratorEquationAstImpl::Type::TIMES;
}

bool Generator::GeneratorImpl::isDivideOperator(const GeneratorEquationAstImplPtr &ast) const
{
    return ast->mType == GeneratorEquationAstImpl::Type::DIVIDE;
}

bool Generator::GeneratorImpl::isPowerOperator(const GeneratorEquationAstImplPtr &ast) const
{
    return ast->mType == GeneratorEquationAstImpl::Type::POWER;
}

bool Generator::GeneratorImpl::isRootOperator(const GeneratorEquationAstImplPtr &ast) const
{
    return ast->mType == GeneratorEquationAstImpl::Type::ROOT;
}

bool Generator::GeneratorImpl::isAndOperator(const GeneratorEquationAstImplPtr &ast) const
{
    return ast->mType == GeneratorEquationAstImpl::Type::AND;
}

bool Generator::GeneratorImpl::isOrOperator(const GeneratorEquationAstImplPtr &ast) const
{
    return ast->mType == GeneratorEquationAstImpl::Type::OR;
}

bool Generator::GeneratorImpl::isXorOperator(const GeneratorEquationAstImplPtr &ast) const
{
    return ast->mType == GeneratorEquationAstImpl::Type::XOR;
}

bool Generator::GeneratorImpl::isLogicalOrBitwiseOperator(const GeneratorEquationAstImplPtr &ast) const
{
    // Note: GeneratorEquationAstImpl::Type::NOT is a unary logical operator
    //       hence we don't include it here since this method is only used to
    //       determine whether parentheses should be added around some code.

    return (ast->mType == GeneratorEquationAstImpl::Type::AND)
           || (ast->mType == GeneratorEquationAstImpl::Type::OR)
           || (ast->mType == GeneratorEquationAstImpl::Type::XOR);
}

bool Generator::GeneratorImpl::isPiecewiseStatement(const GeneratorEquationAstImplPtr &ast) const
{
    return ast->mType == GeneratorEquationAstImpl::Type::PIECEWISE;
}

std::string Generator::GeneratorImpl::generateOperatorCode(const std::string &op,
                                                           const GeneratorEquationAstImplPtr &ast) const
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

std::string Generator::GeneratorImpl::generateMinusUnaryCode(const GeneratorEquationAstImplPtr &ast) const
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

std::string Generator::GeneratorImpl::generateCode(const GeneratorEquationAstImplPtr &ast,
                                                   const GeneratorEquationAstImplPtr &parentAst) const
{
    // Generate the code for the given AST

    switch (ast->mType) {
        // Relational operators

    case GeneratorEquationAstImpl::Type::EQ:
        return generateOperatorCode(mProfile->eqString(), ast);
    case GeneratorEquationAstImpl::Type::EQEQ:
        return generateOperatorCode(mProfile->eqEqString(), ast);
    case GeneratorEquationAstImpl::Type::NEQ:
        return generateOperatorCode(mProfile->neqString(), ast);
    case GeneratorEquationAstImpl::Type::LT:
        return generateOperatorCode(mProfile->ltString(), ast);
    case GeneratorEquationAstImpl::Type::LEQ:
        return generateOperatorCode(mProfile->leqString(), ast);
    case GeneratorEquationAstImpl::Type::GT:
        return generateOperatorCode(mProfile->gtString(), ast);
    case GeneratorEquationAstImpl::Type::GEQ:
        return generateOperatorCode(mProfile->geqString(), ast);

        // Arithmetic operators

    case GeneratorEquationAstImpl::Type::PLUS:
        if (ast->mRight != nullptr) {
            return generateOperatorCode(mProfile->plusString(), ast);
        }

        return generateCode(ast->mLeft);
    case GeneratorEquationAstImpl::Type::MINUS:
        if (ast->mRight != nullptr) {
            return generateOperatorCode(mProfile->minusString(), ast);
        }

        return generateMinusUnaryCode(ast);
    case GeneratorEquationAstImpl::Type::TIMES:
        return generateOperatorCode(mProfile->timesString(), ast);
    case GeneratorEquationAstImpl::Type::DIVIDE:
        return generateOperatorCode(mProfile->divideString(), ast);
    case GeneratorEquationAstImpl::Type::POWER: {
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
    case GeneratorEquationAstImpl::Type::ROOT:
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
    case GeneratorEquationAstImpl::Type::ABS:
        return mProfile->absoluteValueString() + "(" + generateCode(ast->mLeft) + ")";
    case GeneratorEquationAstImpl::Type::EXP:
        return mProfile->exponentialString() + "(" + generateCode(ast->mLeft) + ")";
    case GeneratorEquationAstImpl::Type::LN:
        return mProfile->napierianLogarithmString() + "(" + generateCode(ast->mLeft) + ")";
    case GeneratorEquationAstImpl::Type::LOG:
        if (ast->mRight != nullptr) {
            std::string stringValue = generateCode(ast->mLeft);
            double doubleValue = convertToDouble(stringValue);

            if (isEqual(doubleValue, 10.0)) {
                return mProfile->commonLogarithmString() + "(" + generateCode(ast->mRight) + ")";
            }

            return mProfile->napierianLogarithmString() + "(" + generateCode(ast->mRight) + ")/" + mProfile->napierianLogarithmString() + "(" + stringValue + ")";
        }

        return mProfile->commonLogarithmString() + "(" + generateCode(ast->mLeft) + ")";
    case GeneratorEquationAstImpl::Type::CEILING:
        return mProfile->ceilingString() + "(" + generateCode(ast->mLeft) + ")";
    case GeneratorEquationAstImpl::Type::FLOOR:
        return mProfile->floorString() + "(" + generateCode(ast->mLeft) + ")";
    case GeneratorEquationAstImpl::Type::FACTORIAL:
        return mProfile->factorialString() + "(" + generateCode(ast->mLeft) + ")";

        // Logical operators

    case GeneratorEquationAstImpl::Type::AND:
        return generateOperatorCode(mProfile->andString(), ast);
    case GeneratorEquationAstImpl::Type::OR:
        return generateOperatorCode(mProfile->orString(), ast);
    case GeneratorEquationAstImpl::Type::XOR:
        if (mProfile->hasXorOperator()) {
            return generateOperatorCode(mProfile->xorString(), ast);
        }

        return mProfile->xorString() + "(" + generateCode(ast->mLeft) + ", " + generateCode(ast->mRight) + ")";
    case GeneratorEquationAstImpl::Type::NOT:
        return mProfile->notString() + generateCode(ast->mLeft);

        // Calculus elements

    case GeneratorEquationAstImpl::Type::DIFF:
        return "d(" + generateCode(ast->mRight) + ")/d(" + generateCode(ast->mLeft) + ")";

        // Min/max operators

    case GeneratorEquationAstImpl::Type::MIN:
        if (parentAst == nullptr) {
            return mProfile->minString() + "(" + generateCode(ast->mLeft, ast) + ", " + generateCode(ast->mRight, ast) + ")";
        }

        return generateCode(ast->mLeft, ast) + ", " + generateCode(ast->mRight, ast);
    case GeneratorEquationAstImpl::Type::MAX:
        if (parentAst == nullptr) {
            return mProfile->maxString() + "(" + generateCode(ast->mLeft, ast) + ", " + generateCode(ast->mRight, ast) + ")";
        }

        return generateCode(ast->mLeft, ast) + ", " + generateCode(ast->mRight, ast);

        // Gcd/lcm operators

    case GeneratorEquationAstImpl::Type::GCD:
        if (parentAst == nullptr) {
            return mProfile->gcdString() + "(" + generateCode(ast->mLeft, ast) + ", " + generateCode(ast->mRight, ast) + ")";
        }

        return generateCode(ast->mLeft, ast) + ", " + generateCode(ast->mRight, ast);
    case GeneratorEquationAstImpl::Type::LCM:
        if (parentAst == nullptr) {
            return mProfile->lcmString() + "(" + generateCode(ast->mLeft, ast) + ", " + generateCode(ast->mRight, ast) + ")";
        }

        return generateCode(ast->mLeft, ast) + ", " + generateCode(ast->mRight, ast);

        // Trigonometric operators

    case GeneratorEquationAstImpl::Type::SIN:
        return mProfile->sinString() + "(" + generateCode(ast->mLeft) + ")";
    case GeneratorEquationAstImpl::Type::COS:
        return mProfile->cosString() + "(" + generateCode(ast->mLeft) + ")";
    case GeneratorEquationAstImpl::Type::TAN:
        return mProfile->tanString() + "(" + generateCode(ast->mLeft) + ")";
    case GeneratorEquationAstImpl::Type::SEC:
        return mProfile->secString() + "(" + generateCode(ast->mLeft) + ")";
    case GeneratorEquationAstImpl::Type::CSC:
        return mProfile->cscString() + "(" + generateCode(ast->mLeft) + ")";
    case GeneratorEquationAstImpl::Type::COT:
        return mProfile->cotString() + "(" + generateCode(ast->mLeft) + ")";
    case GeneratorEquationAstImpl::Type::SINH:
        return mProfile->sinhString() + "(" + generateCode(ast->mLeft) + ")";
    case GeneratorEquationAstImpl::Type::COSH:
        return mProfile->coshString() + "(" + generateCode(ast->mLeft) + ")";
    case GeneratorEquationAstImpl::Type::TANH:
        return mProfile->tanhString() + "(" + generateCode(ast->mLeft) + ")";
    case GeneratorEquationAstImpl::Type::SECH:
        return mProfile->sechString() + "(" + generateCode(ast->mLeft) + ")";
    case GeneratorEquationAstImpl::Type::CSCH:
        return mProfile->cschString() + "(" + generateCode(ast->mLeft) + ")";
    case GeneratorEquationAstImpl::Type::COTH:
        return mProfile->cothString() + "(" + generateCode(ast->mLeft) + ")";
    case GeneratorEquationAstImpl::Type::ASIN:
        return mProfile->asinString() + "(" + generateCode(ast->mLeft) + ")";
    case GeneratorEquationAstImpl::Type::ACOS:
        return mProfile->acosString() + "(" + generateCode(ast->mLeft) + ")";
    case GeneratorEquationAstImpl::Type::ATAN:
        return mProfile->atanString() + "(" + generateCode(ast->mLeft) + ")";
    case GeneratorEquationAstImpl::Type::ASEC:
        return mProfile->asecString() + "(" + generateCode(ast->mLeft) + ")";
    case GeneratorEquationAstImpl::Type::ACSC:
        return mProfile->acscString() + "(" + generateCode(ast->mLeft) + ")";
    case GeneratorEquationAstImpl::Type::ACOT:
        return mProfile->acotString() + "(" + generateCode(ast->mLeft) + ")";
    case GeneratorEquationAstImpl::Type::ASINH:
        return mProfile->asinhString() + "(" + generateCode(ast->mLeft) + ")";
    case GeneratorEquationAstImpl::Type::ACOSH:
        return mProfile->acoshString() + "(" + generateCode(ast->mLeft) + ")";
    case GeneratorEquationAstImpl::Type::ATANH:
        return mProfile->atanhString() + "(" + generateCode(ast->mLeft) + ")";
    case GeneratorEquationAstImpl::Type::ASECH:
        return mProfile->asechString() + "(" + generateCode(ast->mLeft) + ")";
    case GeneratorEquationAstImpl::Type::ACSCH:
        return mProfile->acschString() + "(" + generateCode(ast->mLeft) + ")";
    case GeneratorEquationAstImpl::Type::ACOTH:
        return mProfile->acothString() + "(" + generateCode(ast->mLeft) + ")";

        // Extra operators

    case GeneratorEquationAstImpl::Type::REM:
        return mProfile->remString() + "(" + generateCode(ast->mLeft) + ", " + generateCode(ast->mRight) + ")";

        // Piecewise statement

    case GeneratorEquationAstImpl::Type::PIECEWISE:
        if (ast->mRight != nullptr) {
            if (ast->mRight->mType == GeneratorEquationAstImpl::Type::PIECE) {
                return generateCode(ast->mLeft) + generatePiecewiseElseCode(generateCode(ast->mRight) + generatePiecewiseElseCode(mProfile->nanString()));
            }

            return generateCode(ast->mLeft) + generatePiecewiseElseCode(generateCode(ast->mRight));
        }

        return generateCode(ast->mLeft) + generatePiecewiseElseCode(mProfile->nanString());
    case GeneratorEquationAstImpl::Type::PIECE:
        return generatePiecewiseIfCode(generateCode(ast->mRight), generateCode(ast->mLeft));
    case GeneratorEquationAstImpl::Type::OTHERWISE:
        return generateCode(ast->mLeft);

        // Token elements

    case GeneratorEquationAstImpl::Type::CN:
        return ast->mValue;
    case GeneratorEquationAstImpl::Type::CI:
        return ast->mVariable->name();

        // Qualifier elements

    case GeneratorEquationAstImpl::Type::DEGREE:
    case GeneratorEquationAstImpl::Type::LOGBASE:
    case GeneratorEquationAstImpl::Type::BVAR:
        return generateCode(ast->mLeft);

        // Constants

    case GeneratorEquationAstImpl::Type::TRUE:
        return mProfile->trueString();
    case GeneratorEquationAstImpl::Type::FALSE:
        return mProfile->falseString();
    case GeneratorEquationAstImpl::Type::E:
        return mProfile->eString();
    case GeneratorEquationAstImpl::Type::PI:
        return mProfile->piString();
    case GeneratorEquationAstImpl::Type::INF:
        return mProfile->infString();
    case GeneratorEquationAstImpl::Type::NAN:
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

    /*ISSUE359: reenable the validation once it is known to work fine.
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
    //ISSUE359: remove the below code once we are done testing things.
#ifdef TRACES
    for (size_t i = 0; i < errorCount(); ++i) {
        std::cout << "Generator error #" << i + 1 << ": " << error(i)->description() << std::endl;
    }
    if (errorCount() == 0) {
        std::cout << "Number of variables: " << mPimpl->mVariables.size() << std::endl;
        int i = 0;
        for (const auto &variable : mPimpl->mVariables) {
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
        if (variable->mType == GeneratorVariableImpl::Type::STATE) {
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
        if ((variable->mType == GeneratorVariableImpl::Type::ALGEBRAIC)
            || (variable->mType == GeneratorVariableImpl::Type::CONSTANT)
            || (variable->mType == GeneratorVariableImpl::Type::COMPUTED_CONSTANT)) {
            ++res;
        }
    }

    return res;
}

GeneratorVariablePtr Generator::variableOfIntegration() const
{
    //ISSUE359: to be done...
    return {};
}

GeneratorVariablePtr Generator::state(size_t index) const
{
    //ISSUE359: to be done...
    (void)index;

    return {};
}

GeneratorVariablePtr Generator::variable(size_t index) const
{
    //ISSUE359: to be done...
    (void)index;

    return {};
}

std::string Generator::neededMathMethods() const
{
    return {};
}

std::string Generator::initializeVariables() const
{
    if (errorCount() != 0) {
        return {};
    }

    std::string res;

    for (const auto &variable : mPimpl->mVariables) {
        if (variable->mType == GeneratorVariableImpl::Type::CONSTANT) {
            res += variable->mVariable->name() + " = " + variable->mVariable->initialValue() + mPimpl->mProfile->commandSeparatorString() + "\n";
        }
    }

    return res;
}

std::string Generator::computeConstantEquations() const
{
    if (errorCount() != 0) {
        return {};
    }

    std::string res;

    for (const auto &equation : mPimpl->mEquations) {
        if (equation->mType == GeneratorEquationImpl::Type::CONSTANT) {
            res += mPimpl->generateCode(equation->mAst) + mPimpl->mProfile->commandSeparatorString() + "\n";
        }
    }

    return res;
}

std::string Generator::computeRateEquations() const
{
    if (errorCount() != 0) {
        return {};
    }

    std::string res;

    for (const auto &equation : mPimpl->mEquations) {
        if (equation->mType == GeneratorEquationImpl::Type::RATE) {
            res += mPimpl->generateCode(equation->mAst);
        }
    }

    return res;
}

std::string Generator::computeAlgebraicEquations() const
{
    if (errorCount() != 0) {
        return {};
    }

    std::string res;

    for (const auto &equation : mPimpl->mEquations) {
        if (equation->mType == GeneratorEquationImpl::Type::ALGEBRAIC) {
            res += mPimpl->generateCode(equation->mAst) + mPimpl->mProfile->commandSeparatorString() + "\n";
        }
    }

    return res;
}

} // namespace libcellml

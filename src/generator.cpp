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

#include "libcellml/component.h"
#include "libcellml/generator.h"
#include "libcellml/generatorprofile.h"
#include "libcellml/model.h"
#include "libcellml/validator.h"
#include "libcellml/variable.h"

#include <algorithm>
#include <limits>
#include <list>
#include <sstream>
#include <vector>

#undef NAN

#ifdef __linux__
#    undef TRUE
#    undef FALSE
#endif

namespace libcellml {

static const size_t MAX_SIZE_T = std::numeric_limits<size_t>::max();

struct GeneratorEquationImpl;
using GeneratorEquationImplPtr = std::shared_ptr<GeneratorEquationImpl>;
using GeneratorEquationImplWeakPtr = std::weak_ptr<GeneratorEquationImpl>;

struct GeneratorVariableImpl
{
    enum struct Type
    {
        UNKNOWN,
        SHOULD_BE_STATE,
        VARIABLE_OF_INTEGRATION,
        STATE,
        CONSTANT,
        COMPUTED_TRUE_CONSTANT,
        COMPUTED_VARIABLE_BASED_CONSTANT,
        ALGEBRAIC,
        OVERCONSTRAINED
    };

    Type mType = Type::UNKNOWN;
    size_t mIndex = MAX_SIZE_T;

    VariablePtr mVariable;

    bool mProcessed = false;

    GeneratorEquationImplWeakPtr mEquation;

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
        // a state. By default, we consider it to be a constant and, if we find
        // an ODE for that variable, we will know that it was actually a state.

        mType = Type::CONSTANT;
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
using GeneratorEquationAstImplWeakPtr = std::weak_ptr<GeneratorEquationAstImpl>;

struct GeneratorEquationAstImpl
{
    enum struct Type
    {
        // Relational and logical operators

        EQ,
        EQEQ,
        NEQ,
        LT,
        LEQ,
        GT,
        GEQ,
        AND,
        OR,
        XOR,
        NOT,

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

        // Calculus elements

        DIFF,

        // Min/max operators

        MIN,
        MAX,

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

    Type mType = Type::EQ;

    std::string mValue;
    VariablePtr mVariable = nullptr;

    GeneratorEquationAstImplWeakPtr mParent;

    GeneratorEquationAstImplPtr mLeft = nullptr;
    GeneratorEquationAstImplPtr mRight = nullptr;

    explicit GeneratorEquationAstImpl();
    explicit GeneratorEquationAstImpl(Type type,
                                      const GeneratorEquationAstImplPtr &parent);
    explicit GeneratorEquationAstImpl(Type type, const std::string &value,
                                      const GeneratorEquationAstImplPtr &parent);
    explicit GeneratorEquationAstImpl(Type type, const VariablePtr &variable,
                                      const GeneratorEquationAstImplPtr &parent);
};

GeneratorEquationAstImpl::GeneratorEquationAstImpl() = default;

GeneratorEquationAstImpl::GeneratorEquationAstImpl(Type type,
                                                   const GeneratorEquationAstImplPtr &parent)
    : mType(type)
    , mParent(parent)
{
}

GeneratorEquationAstImpl::GeneratorEquationAstImpl(Type type, const std::string &value,
                                                   const GeneratorEquationAstImplPtr &parent)
    : mType(type)
    , mValue(value)
    , mParent(parent)
{
}

GeneratorEquationAstImpl::GeneratorEquationAstImpl(Type type, const VariablePtr &variable,
                                                   const GeneratorEquationAstImplPtr &parent)
    : mType(type)
    , mVariable(variable)
    , mParent(parent)
{
}

#ifdef SWIG
struct GeneratorEquationImpl
#else
struct GeneratorEquationImpl: public std::enable_shared_from_this<GeneratorEquationImpl>
#endif
{
    enum struct Type
    {
        UNKNOWN,
        TRUE_CONSTANT,
        VARIABLE_BASED_CONSTANT,
        DEPENDENCY,
        RATE,
        ALGEBRAIC
    };

    Type mType = Type::UNKNOWN;

    std::list<GeneratorEquationImplPtr> mDependencies;

    bool mProcessed = false;

    GeneratorEquationAstImplPtr mAst;

    std::list<GeneratorVariableImplPtr> mVariables;
    std::list<GeneratorVariableImplPtr> mOdeVariables;

    GeneratorVariableImplPtr mVariable = nullptr;

    bool mTrulyConstant = true;
    bool mVariableBasedConstant = true;

    explicit GeneratorEquationImpl();

    void addVariable(const GeneratorVariableImplPtr &variable);
    void addOdeVariable(const GeneratorVariableImplPtr &odeVariable);

    static bool containsNonTrueConstantVariables(const std::list<GeneratorVariableImplPtr> &variables);
    static bool containsNonConstantVariables(const std::list<GeneratorVariableImplPtr> &variables);

    static bool knownVariable(const GeneratorVariableImplPtr &variable);
    static bool knownOdeVariable(const GeneratorVariableImplPtr &odeVariable);

    bool check(size_t & stateIndex, size_t & variableIndex);
};

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

bool GeneratorEquationImpl::containsNonTrueConstantVariables(const std::list<GeneratorVariableImplPtr> &variables)
{
    return std::find_if(variables.begin(), variables.end(), [](const GeneratorVariableImplPtr &variable) {
               return (variable->mType != GeneratorVariableImpl::Type::UNKNOWN);
           })
           != std::end(variables);
}

bool GeneratorEquationImpl::containsNonConstantVariables(const std::list<GeneratorVariableImplPtr> &variables)
{
    return std::find_if(variables.begin(), variables.end(), [](const GeneratorVariableImplPtr &variable) {
               return (variable->mType != GeneratorVariableImpl::Type::UNKNOWN)
                      && (variable->mType != GeneratorVariableImpl::Type::CONSTANT);
           })
           != std::end(variables);
}

bool GeneratorEquationImpl::knownVariable(const GeneratorVariableImplPtr &variable)
{
    return variable->mProcessed
           || (variable->mType == GeneratorVariableImpl::Type::VARIABLE_OF_INTEGRATION)
           || (variable->mType == GeneratorVariableImpl::Type::STATE)
           || (variable->mType == GeneratorVariableImpl::Type::CONSTANT);
}

bool GeneratorEquationImpl::knownOdeVariable(const GeneratorVariableImplPtr &odeVariable)
{
    return odeVariable->mProcessed
           || (odeVariable->mType == GeneratorVariableImpl::Type::VARIABLE_OF_INTEGRATION);
}

bool GeneratorEquationImpl::check(size_t &stateIndex, size_t &variableIndex)
{
    // Nothing to check if the equation has already been given an order (i.e.
    // everything is fine) or if there is one known (ODE) variable left (i.e.
    // this equation is an overconstraint).

    if (mProcessed) {
        return false;
    }

    if (mVariables.size() + mOdeVariables.size() == 1) {
        GeneratorVariableImplPtr variable = (mVariables.size() == 1) ? mVariables.front() : mOdeVariables.front();

        if ((variable->mType != GeneratorVariableImpl::Type::UNKNOWN)
            && (variable->mType != GeneratorVariableImpl::Type::SHOULD_BE_STATE)
            && (variable->mIndex != MAX_SIZE_T)) {
            variable->mType = GeneratorVariableImpl::Type::OVERCONSTRAINED;

            return false;
        }
    }

    // Determine, from the (new) known (ODE) variables, whether the equation is
    // truly constant or variable-based constant.

    mTrulyConstant = mTrulyConstant
                     && !containsNonTrueConstantVariables(mVariables)
                     && !containsNonTrueConstantVariables(mOdeVariables);
    mVariableBasedConstant = mVariableBasedConstant
                             && !containsNonConstantVariables(mVariables)
                             && !containsNonConstantVariables(mOdeVariables);

    // Add, as a dependency, the equations used to compute the (new) known
    // variables. (Note that we don't account for the (new) known ODE variables
    // since their corresponding equation can obviously not be of algebraic
    // type.)

    for (const auto &variable : mVariables) {
        GeneratorEquationImplPtr equation = variable->mEquation.lock();

        if (knownVariable(variable) && (equation != nullptr)) {
            if (equation->mType == Type::ALGEBRAIC) {
                equation->mType = Type::DEPENDENCY;

                mDependencies.push_back(equation);
            }
        }
    }

    // Stop tracking (new) known (ODE) variables.

    mVariables.remove_if(knownVariable);
    mOdeVariables.remove_if(knownOdeVariable);

    // If there is one (ODE) variable left then update its type (if it is
    // currently unknown), determine its index, consider it computed, and
    // determine the type of our equation and set its order, if the (ODE)
    // variable is a state, computed constant or algebraic variable.

    bool relevantCheck = false;

    if (mVariables.size() + mOdeVariables.size() == 1) {
        GeneratorVariableImplPtr variable = (mVariables.size() == 1) ? mVariables.front() : mOdeVariables.front();

        if (variable->mType == GeneratorVariableImpl::Type::UNKNOWN) {
            variable->mType = mTrulyConstant ?
                                  GeneratorVariableImpl::Type::COMPUTED_TRUE_CONSTANT :
                                  mVariableBasedConstant ?
                                  GeneratorVariableImpl::Type::COMPUTED_VARIABLE_BASED_CONSTANT :
                                  GeneratorVariableImpl::Type::ALGEBRAIC;
        }

        if ((variable->mType == GeneratorVariableImpl::Type::STATE)
            || (variable->mType == GeneratorVariableImpl::Type::COMPUTED_TRUE_CONSTANT)
            || (variable->mType == GeneratorVariableImpl::Type::COMPUTED_VARIABLE_BASED_CONSTANT)
            || (variable->mType == GeneratorVariableImpl::Type::ALGEBRAIC)) {
            variable->mIndex = (variable->mType == GeneratorVariableImpl::Type::STATE) ?
                                   ++stateIndex :
                                   ++variableIndex;

            variable->mProcessed = true;
            variable->mEquation = shared_from_this();

            mType = (variable->mType == GeneratorVariableImpl::Type::STATE) ?
                        Type::RATE :
                        (variable->mType == GeneratorVariableImpl::Type::COMPUTED_TRUE_CONSTANT) ?
                        Type::TRUE_CONSTANT :
                        (variable->mType == GeneratorVariableImpl::Type::COMPUTED_VARIABLE_BASED_CONSTANT) ?
                        Type::VARIABLE_BASED_CONSTANT :
                        Type::ALGEBRAIC;

            mProcessed = true;
            mVariable = variable;

            relevantCheck = true;
        }
    }

    return relevantCheck;
}

struct Generator::GeneratorImpl
{
    Generator *mGenerator = nullptr;

    Generator::ModelType mModelType = Generator::ModelType::UNKNOWN;

    VariablePtr mVariableOfIntegration;

    std::list<GeneratorVariableImplPtr> mVariables;
    std::list<GeneratorEquationImplPtr> mEquations;

    GeneratorProfilePtr mProfile = std::make_shared<libcellml::GeneratorProfile>();

    bool mNeedMin = false;
    bool mNeedMax = false;

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

    static bool compareVariablesByName(const GeneratorVariableImplPtr &variable1,
                                       const GeneratorVariableImplPtr &variable2);
    static bool compareVariablesByTypeAndIndex(const GeneratorVariableImplPtr &variable1,
                                               const GeneratorVariableImplPtr &variable2);

    static bool compareEquationsByVariable(const GeneratorEquationImplPtr &equation1,
                                           const GeneratorEquationImplPtr &equation2);

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

    std::string generateDouble(const std::string &value);
    std::string generateVariableName(const VariablePtr &variable, const GeneratorEquationAstImplPtr &ast = nullptr);

    std::string generateOperatorCode(const std::string &op,
                                     const GeneratorEquationAstImplPtr &ast);
    std::string generateMinusUnaryCode(const GeneratorEquationAstImplPtr &ast);
    std::string generatePiecewiseIfCode(const std::string &condition,
                                        const std::string &value);
    std::string generatePiecewiseElseCode(const std::string &value);
    std::string generateCode(const GeneratorEquationAstImplPtr &ast,
                             const GeneratorEquationAstImplPtr &parentAst = nullptr);

    std::string generateInitializationCode(const GeneratorVariableImplPtr &variable);
    std::string generateEquationCode(const GeneratorEquationImplPtr &equation);
};

bool Generator::GeneratorImpl::hasValidModel() const
{
    return (mModelType == Generator::ModelType::ALGEBRAIC)
           || (mModelType == Generator::ModelType::ODE);
}

size_t Generator::GeneratorImpl::mathmlChildCount(const XmlNodePtr &node) const
{
    // Return the number of child elements, in the MathML namespace, for the
    // given node.

    XmlNodePtr childNode = node->firstChild();
    size_t res = childNode->isMathmlElement() ? 1 : 0;

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
    // not int he MathML namespace.

    XmlNodePtr res = node->firstChild();
    size_t childNodeIndex = res->isMathmlElement() ? 0 : MAX_SIZE_T;

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
    // the given variable.

    for (const auto &generatorVariable : mVariables) {
        if ((variable == generatorVariable->mVariable)
            || variable->hasEquivalentVariable(generatorVariable->mVariable)) {
            return generatorVariable;
        }
    }

    // No generator variable exists for the given variable, so create one, track
    // it and return it.

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

            if (astRight != nullptr) {
                astRight->mParent = ast;
            }

            ast->mRight = astRight;
        }

        // Relational and logical operators

    } else if (node->isMathmlElement("eq")) {
        // This element is used both to describe "a = b" and "a == b". We can
        // distinguish between the two by checking its grand-parent. If it's a
        // "math" element then it means that it is used to describe "a = b"
        // otherwise it is used to describe "a == b". In the former case, there
        // is nothing more we need to do since `ast` is already of
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
    } else if (node->isMathmlElement("and")) {
        ast = std::make_shared<GeneratorEquationAstImpl>(GeneratorEquationAstImpl::Type::AND, astParent);
    } else if (node->isMathmlElement("or")) {
        ast = std::make_shared<GeneratorEquationAstImpl>(GeneratorEquationAstImpl::Type::OR, astParent);
    } else if (node->isMathmlElement("xor")) {
        ast = std::make_shared<GeneratorEquationAstImpl>(GeneratorEquationAstImpl::Type::XOR, astParent);
    } else if (node->isMathmlElement("not")) {
        ast = std::make_shared<GeneratorEquationAstImpl>(GeneratorEquationAstImpl::Type::NOT, astParent);

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
        if (mathmlChildCount(node) == 1) {
            // E-notation based CN value

            ast = std::make_shared<GeneratorEquationAstImpl>(GeneratorEquationAstImpl::Type::CN, node->firstChild()->convertToString() + "e" + node->firstChild()->next()->next()->convertToString(), astParent);
        } else {
            ast = std::make_shared<GeneratorEquationAstImpl>(GeneratorEquationAstImpl::Type::CN, node->firstChild()->convertToString(), astParent);
        }
    } else if (node->isMathmlElement("ci")) {
        std::string variableName = node->firstChild()->convertToString();
        VariablePtr variable = component->variable(variableName);

        if (variable != nullptr) {
            ast = std::make_shared<GeneratorEquationAstImpl>(GeneratorEquationAstImpl::Type::CI, variable, astParent);

            // Have our equation track the (ODE) variable (by ODE variable, we
            // mean a variable that is used in a "diff" element)

            GeneratorVariableImplPtr generatorVariable = Generator::GeneratorImpl::generatorVariable(variable);

            if (node->parent()->firstChild()->isMathmlElement("diff")) {
                equation->addOdeVariable(generatorVariable);
            } else if (!(node->parent()->isMathmlElement("bvar")
                         && node->parent()->parent()->firstChild()->isMathmlElement("diff"))) {
                equation->addVariable(generatorVariable);
            }
        } else {
            ModelPtr model = component->parentModel();
            ErrorPtr err = std::make_shared<Error>();

            err->setDescription("Variable '" + variableName
                                + "' in component '" + component->name()
                                + "' of model '" + model->name()
                                + "' is referenced in an equation, but it is not defined anywhere.");
            err->setKind(Error::Kind::GENERATOR);

            mGenerator->addError(err);
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
    // Create and keep track of the equation associated with the given node.

    GeneratorEquationImplPtr equation = std::make_shared<GeneratorEquationImpl>();

    mEquations.push_back(equation);

    // Actually process the node and return its corresponding equation.

    processNode(node, equation->mAst, equation->mAst->mParent.lock(), component, equation);

    return equation;
}

void Generator::GeneratorImpl::processComponent(const ComponentPtr &component)
{
    // Retrieve the math string associated with the given component and process
    // it, one equation at a time.

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

    // Go through the given component's variables and make sure that everything
    // makes sense.

    for (size_t i = 0; i < component->variableCount(); ++i) {
        // Retrieve the variable's corresponding generator variable.

        VariablePtr variable = component->variable(i);
        GeneratorVariableImplPtr generatorVariable = Generator::GeneratorImpl::generatorVariable(variable);

        // Replace the variable held by `generatorVariable`, in case the
        // existing one has no initial value while `variable` does. Otherwise,
        // generate an error if the variable held by `generatorVariable` and
        // `variable` are both initialised.

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

            err->setDescription("Variable '" + variable->name()
                                + "' in component '" + component->name()
                                + "' of model '" + model->name()
                                + "' and variable '" + generatorVariable->mVariable->name()
                                + "' in component '" + trackedVariableComponent->name()
                                + "' of model '" + trackedVariableModel->name()
                                + "' are equivalent and cannot therefore both be initialised.");
            err->setKind(Error::Kind::GENERATOR);

            mGenerator->addError(err);
        }
    }

    // Do the same for the components encapsulated by the given component.

    for (size_t i = 0; i < component->componentCount(); ++i) {
        processComponent(component->component(i));
    }
}

void Generator::GeneratorImpl::processEquationAst(const GeneratorEquationAstImplPtr &ast)
{
    // Look for the definition of a variable of integration and make sure that
    // we don't have more than one of it and that it's not initialised.

    GeneratorEquationAstImplPtr astParent = ast->mParent.lock();
    GeneratorEquationAstImplPtr astGrandParent = (astParent != nullptr) ? astParent->mParent.lock() : nullptr;
    GeneratorEquationAstImplPtr astGreatGrandParent = (astGrandParent != nullptr) ? astGrandParent->mParent.lock() : nullptr;

    if ((ast->mType == GeneratorEquationAstImpl::Type::CI)
        && (astParent != nullptr) && (astParent->mType == GeneratorEquationAstImpl::Type::BVAR)
        && (astGrandParent != nullptr) && (astGrandParent->mType == GeneratorEquationAstImpl::Type::DIFF)) {
        VariablePtr variable = ast->mVariable;

        generatorVariable(variable)->makeVariableOfIntegration();
        // Note: we must make the variable a variable of integration in all
        //       cases (i.e. even if there is, for example, already another
        //       variable of integration) otherwise unnecessary error messages
        //       may be reported (since the type of the variable would be
        //       unknown).

        if (mVariableOfIntegration == nullptr) {
            // Before keeping track of the variable of integration, make sure
            // that it is not initialised.

            if (!variable->initialValue().empty()) {
                ComponentPtr component = variable->parentComponent();
                ModelPtr model = component->parentModel();
                ErrorPtr err = std::make_shared<Error>();

                err->setDescription("Variable '" + variable->name()
                                    + "' in component '" + component->name()
                                    + "' of model '" + model->name()
                                    + "' cannot be both a variable of integration and initialised.");
                err->setKind(Error::Kind::GENERATOR);

                mGenerator->addError(err);
            } else {
                mVariableOfIntegration = variable;
            }
        } else if ((variable != mVariableOfIntegration)
                   && !variable->hasEquivalentVariable(mVariableOfIntegration)) {
            ComponentPtr voiComponent = mVariableOfIntegration->parentComponent();
            ModelPtr voiModel = voiComponent->parentModel();
            ComponentPtr component = variable->parentComponent();
            ModelPtr model = component->parentModel();
            ErrorPtr err = std::make_shared<Error>();

            err->setDescription("Variable '" + mVariableOfIntegration->name()
                                + "' in component '" + voiComponent->name()
                                + "' of model '" + voiModel->name()
                                + "' and variable '" + variable->name()
                                + "' in component '" + component->name()
                                + "' of model '" + model->name()
                                + "' cannot both be a variable of integration.");
            err->setKind(Error::Kind::GENERATOR);

            mGenerator->addError(err);
        }
    }

    // Make sure that we only use first-order ODEs.

    if ((ast->mType == GeneratorEquationAstImpl::Type::CN)
        && (astParent != nullptr) && (astParent->mType == GeneratorEquationAstImpl::Type::DEGREE)
        && (astGrandParent != nullptr) && (astGrandParent->mType == GeneratorEquationAstImpl::Type::BVAR)
        && (astGreatGrandParent != nullptr) && (astGreatGrandParent->mType == GeneratorEquationAstImpl::Type::DIFF)) {
        if (convertToDouble(ast->mValue) != 1.0) {
            VariablePtr variable = astGreatGrandParent->mRight->mVariable;
            ComponentPtr component = variable->parentComponent();
            ModelPtr model = component->parentModel();
            ErrorPtr err = std::make_shared<Error>();

            err->setDescription("The differential equation for variable '" + variable->name()
                                + "' in component '" + component->name()
                                + "' of model '" + model->name()
                                + "' must be of the first order.");
            err->setKind(Error::Kind::GENERATOR);

            mGenerator->addError(err);
        }
    }

    // Make a variable a state if it is used in an ODE.

    if ((ast->mType == GeneratorEquationAstImpl::Type::CI)
        && (astParent != nullptr) && (astParent->mType == GeneratorEquationAstImpl::Type::DIFF)) {
        generatorVariable(ast->mVariable)->makeState();
    }

    // Recursively check the given AST's children.

    if (ast->mLeft != nullptr) {
        processEquationAst(ast->mLeft);
    }

    if (ast->mRight != nullptr) {
        processEquationAst(ast->mRight);
    }
}

bool Generator::GeneratorImpl::compareVariablesByName(const GeneratorVariableImplPtr &variable1,
                                                      const GeneratorVariableImplPtr &variable2)
{
    // TODO: we can't currently instatiate imports, which means that we can't
    //       have variables in different models. This also means that we can't
    //       have code to check for the name of a model since this would fail
    //       coverage test.
    VariablePtr realVariable1 = variable1->mVariable;
    VariablePtr realVariable2 = variable2->mVariable;
    ComponentPtr realComponent1 = realVariable1->parentComponent();
    ComponentPtr realComponent2 = realVariable2->parentComponent();

    if (realComponent1->name() == realComponent2->name()) {
        return realVariable1->name() < realVariable2->name();
    }

    return realComponent1->name() < realComponent2->name();
}

bool Generator::GeneratorImpl::compareVariablesByTypeAndIndex(const GeneratorVariableImplPtr &variable1,
                                                              const GeneratorVariableImplPtr &variable2)
{
    if (variable1->mType == variable2->mType) {
        return variable1->mIndex < variable2->mIndex;
    }

    return variable1->mType < variable2->mType;
}

bool Generator::GeneratorImpl::compareEquationsByVariable(const GeneratorEquationImplPtr &equation1,
                                                          const GeneratorEquationImplPtr &equation2)
{
    return compareVariablesByTypeAndIndex(equation1->mVariable, equation2->mVariable);
}

void Generator::GeneratorImpl::processModel(const ModelPtr &model)
{
    // Reset a few things in case we were to process the model more than once.
    // Note: one would normally process the model only once, so we shouldn't
    //       need to do this, but better be safe than sorry.

    mModelType = Generator::ModelType::UNKNOWN;

    mVariableOfIntegration = nullptr;

    mVariables.clear();
    mEquations.clear();

    mNeedMin = false;
    mNeedMax = false;

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
    // for each of the model's equations.

    for (size_t i = 0; i < model->componentCount(); ++i) {
        processComponent(model->component(i));
    }

    // Process our different equations' AST to determine the type of each of all
    // our variables.

    if (mGenerator->errorCount() == 0) {
        for (const auto &equation : mEquations) {
            processEquationAst(equation->mAst);
        }
    }

    // Sort our variables, determine the index of our constant variables and
    // then loop over our equations, checking wich variables, if any, can be
    // determined using a given equation.

    if (mGenerator->errorCount() == 0) {
        mVariables.sort(compareVariablesByName);

        size_t variableIndex = MAX_SIZE_T;

        for (const auto &variable : mVariables) {
            if (variable->mType == GeneratorVariableImpl::Type::CONSTANT) {
                variable->mIndex = ++variableIndex;
            }
        }

        size_t stateIndex = MAX_SIZE_T;

        for (;;) {
            bool relevantCheck = false;

            for (const auto &equation : mEquations) {
                relevantCheck = equation->check(stateIndex, variableIndex)
                                || relevantCheck;
            }

            if (!relevantCheck) {
                break;
            }
        }
    } else {
        mModelType = Generator::ModelType::INVALID;
    }

    // Make sure that all our variables are valid.

    if (mGenerator->errorCount() == 0) {
        for (const auto &variable : mVariables) {
            std::string errorType;

            switch (variable->mType) {
            case GeneratorVariableImpl::Type::UNKNOWN:
                errorType = "is not computed";

                break;
            case GeneratorVariableImpl::Type::SHOULD_BE_STATE:
                errorType = "is used in an ODE, but it is not initialised";

                break;
            case GeneratorVariableImpl::Type::VARIABLE_OF_INTEGRATION:
            case GeneratorVariableImpl::Type::STATE:
            case GeneratorVariableImpl::Type::CONSTANT:
            case GeneratorVariableImpl::Type::COMPUTED_TRUE_CONSTANT:
            case GeneratorVariableImpl::Type::COMPUTED_VARIABLE_BASED_CONSTANT:
            case GeneratorVariableImpl::Type::ALGEBRAIC:
                break;
            case GeneratorVariableImpl::Type::OVERCONSTRAINED:
                errorType = "is computed more than once";

                break;
            }

            if (!errorType.empty()) {
                ErrorPtr err = std::make_shared<Error>();
                VariablePtr realVariable = variable->mVariable;
                ComponentPtr realComponent = realVariable->parentComponent();
                ModelPtr realModel = realComponent->parentModel();

                err->setDescription("Variable '" + realVariable->name()
                                    + "' in component '" + realComponent->name()
                                    + "' of model '" + realModel->name() + "' " + errorType + ".");
                err->setKind(Error::Kind::GENERATOR);

                mGenerator->addError(err);
            }
        }
    }

    // Determine the type of our model, if it hasn't already been categorised as
    // being invalid

    if (mModelType != Generator::ModelType::INVALID) {
        bool hasUnderconstrainedVariables = std::find_if(mVariables.begin(), mVariables.end(), [](const GeneratorVariableImplPtr &variable) {
                                                return (variable->mType == GeneratorVariableImpl::Type::UNKNOWN)
                                                       || (variable->mType == GeneratorVariableImpl::Type::SHOULD_BE_STATE);
                                            })
                                            != std::end(mVariables);
        bool hasOverconstrainedVariables = std::find_if(mVariables.begin(), mVariables.end(), [](const GeneratorVariableImplPtr &variable) {
                                               return variable->mType == GeneratorVariableImpl::Type::OVERCONSTRAINED;
                                           })
                                           != std::end(mVariables);

        if (hasUnderconstrainedVariables) {
            if (hasOverconstrainedVariables) {
                mModelType = Generator::ModelType::UNSUITABLY_CONSTRAINED;
            } else {
                mModelType = Generator::ModelType::UNDERCONSTRAINED;
            }
        } else if (hasOverconstrainedVariables) {
            mModelType = Generator::ModelType::OVERCONSTRAINED;
        } else if (mVariableOfIntegration != nullptr) {
            mModelType = Generator::ModelType::ODE;
        } else if (!mVariables.empty()) {
            mModelType = Generator::ModelType::ALGEBRAIC;
        }
    }

    // Sort our variables and equations (and their dependencies), if we have a
    // valid model

    if ((mModelType == Generator::ModelType::ODE)
        || (mModelType == Generator::ModelType::ALGEBRAIC)) {
        mVariables.sort(compareVariablesByTypeAndIndex);
        mEquations.sort(compareEquationsByVariable);

        for (const auto &equation : mEquations) {
            equation->mDependencies.sort(compareEquationsByVariable);
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
    // Note: GeneratorEquationAstImpl::Type::NOT is a unary logical operator,
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

std::string Generator::GeneratorImpl::generateDouble(const std::string &value)
{
    if (value.find('.') != std::string::npos) {
        return value;
    }

    size_t ePos = value.find('e');

    if (ePos == std::string::npos) {
        return value + ".0";
    }

    return value.substr(0, ePos) + ".0" + value.substr(ePos);
}

std::string Generator::GeneratorImpl::generateVariableName(const VariablePtr &variable, const GeneratorEquationAstImplPtr &ast)
{
    GeneratorVariableImplPtr generatorVariable = Generator::GeneratorImpl::generatorVariable(variable);

    if (generatorVariable->mType == GeneratorVariableImpl::Type::VARIABLE_OF_INTEGRATION) {
        return mProfile->variableOfIntegrationString();
    }

    std::string arrayName;

    if (generatorVariable->mType == GeneratorVariableImpl::Type::STATE) {
        arrayName = ((ast != nullptr) && (ast->mParent.lock()->mType == GeneratorEquationAstImpl::Type::DIFF)) ?
                        mProfile->ratesArrayString() :
                        mProfile->statesArrayString();
    } else {
        arrayName = mProfile->variablesArrayString();
    }

    std::ostringstream index;

    index << generatorVariable->mIndex;

    return arrayName + mProfile->openArrayString() + index.str() + mProfile->closeArrayString();
}

std::string Generator::GeneratorImpl::generateOperatorCode(const std::string &op,
                                                           const GeneratorEquationAstImplPtr &ast)
{
    // Generate the code for the left and right branches of the given AST.

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
        //       parentheses around OR and PIECEWISE. However, it looks
        //       better/clearer to have some around some other operators
        //       (agreed, this is somewhat subjective).

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
        //       parentheses around PIECEWISE. However, it looks better/clearer
        //       to have some around some other operators (agreed, this is
        //       somewhat subjective).

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
        //       parentheses around AND, OR and PIECEWISE. However, it looks
        //       better/clearer to have some around some other operators
        //       (agreed, this is somewhat subjective).

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

std::string Generator::GeneratorImpl::generateMinusUnaryCode(const GeneratorEquationAstImplPtr &ast)
{
    // Generate the code for the left branch of the given AST.

    std::string left = generateCode(ast->mLeft);

    // Determine whether parentheses should be added around the left code.

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
                                                              const std::string &value)
{
    return replace(replace(mProfile->hasConditionalOperator() ?
                               mProfile->conditionalOperatorIfString() :
                               mProfile->piecewiseIfString(),
                           "#cond", condition),
                   "#if", value);
}

std::string Generator::GeneratorImpl::generatePiecewiseElseCode(const std::string &value)
{
    return replace(mProfile->hasConditionalOperator() ?
                       mProfile->conditionalOperatorElseString() :
                       mProfile->piecewiseElseString(),
                   "#else", value);
}

std::string Generator::GeneratorImpl::generateCode(const GeneratorEquationAstImplPtr &ast,
                                                   const GeneratorEquationAstImplPtr &parentAst)
{
    // Generate the code for the given AST.

    std::string code;

    switch (ast->mType) {
        // Relational and logical operators

    case GeneratorEquationAstImpl::Type::EQ:
        code = generateOperatorCode(mProfile->eqString(), ast);

        break;
    case GeneratorEquationAstImpl::Type::EQEQ:
        code = generateOperatorCode(mProfile->eqEqString(), ast);

        break;
    case GeneratorEquationAstImpl::Type::NEQ:
        code = generateOperatorCode(mProfile->neqString(), ast);

        break;
    case GeneratorEquationAstImpl::Type::LT:
        code = generateOperatorCode(mProfile->ltString(), ast);

        break;
    case GeneratorEquationAstImpl::Type::LEQ:
        code = generateOperatorCode(mProfile->leqString(), ast);

        break;
    case GeneratorEquationAstImpl::Type::GT:
        code = generateOperatorCode(mProfile->gtString(), ast);

        break;
    case GeneratorEquationAstImpl::Type::GEQ:
        code = generateOperatorCode(mProfile->geqString(), ast);

        break;
    case GeneratorEquationAstImpl::Type::AND:
        code = generateOperatorCode(mProfile->andString(), ast);

        break;
    case GeneratorEquationAstImpl::Type::OR:
        code = generateOperatorCode(mProfile->orString(), ast);

        break;
    case GeneratorEquationAstImpl::Type::XOR:
        if (mProfile->hasXorOperator()) {
            code = generateOperatorCode(mProfile->xorString(), ast);
        } else {
            code = mProfile->xorString() + "(" + generateCode(ast->mLeft) + ", " + generateCode(ast->mRight) + ")";
        }

        break;
    case GeneratorEquationAstImpl::Type::NOT:
        code = mProfile->notString() + generateCode(ast->mLeft);

        break;

        // Arithmetic operators

    case GeneratorEquationAstImpl::Type::PLUS:
        if (ast->mRight != nullptr) {
            code = generateOperatorCode(mProfile->plusString(), ast);
        } else {
            code = generateCode(ast->mLeft);
        }

        break;
    case GeneratorEquationAstImpl::Type::MINUS:
        if (ast->mRight != nullptr) {
            code = generateOperatorCode(mProfile->minusString(), ast);
        } else {
            code = generateMinusUnaryCode(ast);
        }

        break;
    case GeneratorEquationAstImpl::Type::TIMES:
        code = generateOperatorCode(mProfile->timesString(), ast);

        break;
    case GeneratorEquationAstImpl::Type::DIVIDE:
        code = generateOperatorCode(mProfile->divideString(), ast);

        break;
    case GeneratorEquationAstImpl::Type::POWER: {
        std::string stringValue = generateCode(ast->mRight);
        double doubleValue = convertToDouble(stringValue);

        if (isEqual(doubleValue, 0.5)) {
            code = mProfile->squareRootString() + "(" + generateCode(ast->mLeft) + ")";
        } else if (isEqual(doubleValue, 2.0)) {
            code = mProfile->squareString() + "(" + generateCode(ast->mLeft) + ")";
        } else {
            code = mProfile->hasPowerOperator() ?
                       generateOperatorCode(mProfile->powerString(), ast) :
                       mProfile->powerString() + "(" + generateCode(ast->mLeft) + ", " + stringValue + ")";
        }

        break;
    }
    case GeneratorEquationAstImpl::Type::ROOT:
        if (ast->mRight != nullptr) {
            std::string stringValue = generateCode(ast->mLeft);
            double doubleValue = convertToDouble(stringValue);

            if (isEqual(doubleValue, 2.0)) {
                code = mProfile->squareRootString() + "(" + generateCode(ast->mRight) + ")";
            } else {
                code = mProfile->hasPowerOperator() ?
                           generateOperatorCode(mProfile->powerString(), ast) :
                           mProfile->powerString() + "(" + generateCode(ast->mRight) + ", 1.0/" + stringValue + ")";
            }
        } else {
            code = mProfile->squareRootString() + "(" + generateCode(ast->mLeft) + ")";
        }

        break;
    case GeneratorEquationAstImpl::Type::ABS:
        code = mProfile->absoluteValueString() + "(" + generateCode(ast->mLeft) + ")";

        break;
    case GeneratorEquationAstImpl::Type::EXP:
        code = mProfile->exponentialString() + "(" + generateCode(ast->mLeft) + ")";

        break;
    case GeneratorEquationAstImpl::Type::LN:
        code = mProfile->napierianLogarithmString() + "(" + generateCode(ast->mLeft) + ")";

        break;
    case GeneratorEquationAstImpl::Type::LOG:
        if (ast->mRight != nullptr) {
            std::string stringValue = generateCode(ast->mLeft);
            double doubleValue = convertToDouble(stringValue);

            if (isEqual(doubleValue, 10.0)) {
                code = mProfile->commonLogarithmString() + "(" + generateCode(ast->mRight) + ")";
            } else {
                code = mProfile->napierianLogarithmString() + "(" + generateCode(ast->mRight) + ")/" + mProfile->napierianLogarithmString() + "(" + stringValue + ")";
            }
        } else {
            code = mProfile->commonLogarithmString() + "(" + generateCode(ast->mLeft) + ")";
        }

        break;
    case GeneratorEquationAstImpl::Type::CEILING:
        code = mProfile->ceilingString() + "(" + generateCode(ast->mLeft) + ")";

        break;
    case GeneratorEquationAstImpl::Type::FLOOR:
        code = mProfile->floorString() + "(" + generateCode(ast->mLeft) + ")";

        break;
        // Calculus elements

    case GeneratorEquationAstImpl::Type::DIFF:
        code = generateCode(ast->mRight);

        break;

        // Min/max operators

    case GeneratorEquationAstImpl::Type::MIN:
        if (parentAst == nullptr) {
            code = mProfile->minString() + "(" + generateCode(ast->mLeft, ast) + ", " + generateCode(ast->mRight, ast) + ")";
        } else {
            code = generateCode(ast->mLeft, ast) + ", " + generateCode(ast->mRight, ast);
        }

        break;
    case GeneratorEquationAstImpl::Type::MAX:
        if (parentAst == nullptr) {
            code = mProfile->maxString() + "(" + generateCode(ast->mLeft, ast) + ", " + generateCode(ast->mRight, ast) + ")";
        } else {
            code = generateCode(ast->mLeft, ast) + ", " + generateCode(ast->mRight, ast);
        }

        break;

        // Trigonometric operators

    case GeneratorEquationAstImpl::Type::SIN:
        code = mProfile->sinString() + "(" + generateCode(ast->mLeft) + ")";

        break;
    case GeneratorEquationAstImpl::Type::COS:
        code = mProfile->cosString() + "(" + generateCode(ast->mLeft) + ")";

        break;
    case GeneratorEquationAstImpl::Type::TAN:
        code = mProfile->tanString() + "(" + generateCode(ast->mLeft) + ")";

        break;
    case GeneratorEquationAstImpl::Type::SEC:
        code = mProfile->secString() + "(" + generateCode(ast->mLeft) + ")";

        break;
    case GeneratorEquationAstImpl::Type::CSC:
        code = mProfile->cscString() + "(" + generateCode(ast->mLeft) + ")";

        break;
    case GeneratorEquationAstImpl::Type::COT:
        code = mProfile->cotString() + "(" + generateCode(ast->mLeft) + ")";

        break;
    case GeneratorEquationAstImpl::Type::SINH:
        code = mProfile->sinhString() + "(" + generateCode(ast->mLeft) + ")";

        break;
    case GeneratorEquationAstImpl::Type::COSH:
        code = mProfile->coshString() + "(" + generateCode(ast->mLeft) + ")";

        break;
    case GeneratorEquationAstImpl::Type::TANH:
        code = mProfile->tanhString() + "(" + generateCode(ast->mLeft) + ")";

        break;
    case GeneratorEquationAstImpl::Type::SECH:
        code = mProfile->sechString() + "(" + generateCode(ast->mLeft) + ")";

        break;
    case GeneratorEquationAstImpl::Type::CSCH:
        code = mProfile->cschString() + "(" + generateCode(ast->mLeft) + ")";

        break;
    case GeneratorEquationAstImpl::Type::COTH:
        code = mProfile->cothString() + "(" + generateCode(ast->mLeft) + ")";

        break;
    case GeneratorEquationAstImpl::Type::ASIN:
        code = mProfile->asinString() + "(" + generateCode(ast->mLeft) + ")";

        break;
    case GeneratorEquationAstImpl::Type::ACOS:
        code = mProfile->acosString() + "(" + generateCode(ast->mLeft) + ")";

        break;
    case GeneratorEquationAstImpl::Type::ATAN:
        code = mProfile->atanString() + "(" + generateCode(ast->mLeft) + ")";

        break;
    case GeneratorEquationAstImpl::Type::ASEC:
        code = mProfile->asecString() + "(" + generateCode(ast->mLeft) + ")";

        break;
    case GeneratorEquationAstImpl::Type::ACSC:
        code = mProfile->acscString() + "(" + generateCode(ast->mLeft) + ")";

        break;
    case GeneratorEquationAstImpl::Type::ACOT:
        code = mProfile->acotString() + "(" + generateCode(ast->mLeft) + ")";

        break;
    case GeneratorEquationAstImpl::Type::ASINH:
        code = mProfile->asinhString() + "(" + generateCode(ast->mLeft) + ")";

        break;
    case GeneratorEquationAstImpl::Type::ACOSH:
        code = mProfile->acoshString() + "(" + generateCode(ast->mLeft) + ")";

        break;
    case GeneratorEquationAstImpl::Type::ATANH:
        code = mProfile->atanhString() + "(" + generateCode(ast->mLeft) + ")";

        break;
    case GeneratorEquationAstImpl::Type::ASECH:
        code = mProfile->asechString() + "(" + generateCode(ast->mLeft) + ")";

        break;
    case GeneratorEquationAstImpl::Type::ACSCH:
        code = mProfile->acschString() + "(" + generateCode(ast->mLeft) + ")";

        break;
    case GeneratorEquationAstImpl::Type::ACOTH:
        code = mProfile->acothString() + "(" + generateCode(ast->mLeft) + ")";

        break;

        // Extra operators

    case GeneratorEquationAstImpl::Type::REM:
        code = mProfile->remString() + "(" + generateCode(ast->mLeft) + ", " + generateCode(ast->mRight) + ")";

        break;

        // Piecewise statement

    case GeneratorEquationAstImpl::Type::PIECEWISE:
        if (ast->mRight != nullptr) {
            if (ast->mRight->mType == GeneratorEquationAstImpl::Type::PIECE) {
                code = generateCode(ast->mLeft) + generatePiecewiseElseCode(generateCode(ast->mRight) + generatePiecewiseElseCode(mProfile->nanString()));
            } else {
                code = generateCode(ast->mLeft) + generatePiecewiseElseCode(generateCode(ast->mRight));
            }
        } else {
            code = generateCode(ast->mLeft) + generatePiecewiseElseCode(mProfile->nanString());
        }

        break;
    case GeneratorEquationAstImpl::Type::PIECE:
        code = generatePiecewiseIfCode(generateCode(ast->mRight), generateCode(ast->mLeft));

        break;
    case GeneratorEquationAstImpl::Type::OTHERWISE:
        code = generateCode(ast->mLeft);

        break;

        // Token elements

    case GeneratorEquationAstImpl::Type::CN:
        code = generateDouble(ast->mValue);

        break;
    case GeneratorEquationAstImpl::Type::CI:
        code = generateVariableName(ast->mVariable, ast);

        break;

        // Qualifier elements

    case GeneratorEquationAstImpl::Type::DEGREE:
    case GeneratorEquationAstImpl::Type::LOGBASE:
    case GeneratorEquationAstImpl::Type::BVAR:
        code = generateCode(ast->mLeft);

        break;

        // Constants

    case GeneratorEquationAstImpl::Type::TRUE:
        code = mProfile->trueString();

        break;
    case GeneratorEquationAstImpl::Type::FALSE:
        code = mProfile->falseString();

        break;
    case GeneratorEquationAstImpl::Type::E:
        code = mProfile->eString();

        break;
    case GeneratorEquationAstImpl::Type::PI:
        code = mProfile->piString();

        break;
    case GeneratorEquationAstImpl::Type::INF:
        code = mProfile->infString();

        break;
    case GeneratorEquationAstImpl::Type::NAN:
        code = mProfile->nanString();

        break;
    }

    return code;
}

std::string Generator::GeneratorImpl::generateInitializationCode(const GeneratorVariableImplPtr &variable)
{
    return mProfile->indentString() + generateVariableName(variable->mVariable) + " = " + generateDouble(variable->mVariable->initialValue()) + mProfile->commandSeparatorString() + "\n";
}

std::string Generator::GeneratorImpl::generateEquationCode(const GeneratorEquationImplPtr &equation)
{
    std::string res;

    for (const auto &dependency : equation->mDependencies) {
        res += generateEquationCode(dependency);
    }

    res += mProfile->indentString() + generateCode(equation->mAst) + mProfile->commandSeparatorString() + "\n";

    return res;
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

    mPimpl->mModelType = rhs.mPimpl->mModelType;

    mPimpl->mVariableOfIntegration = rhs.mPimpl->mVariableOfIntegration;

    mPimpl->mVariables = rhs.mPimpl->mVariables;
    mPimpl->mEquations = rhs.mPimpl->mEquations;

    mPimpl->mProfile = rhs.mPimpl->mProfile;

    mPimpl->mNeedMin = rhs.mPimpl->mNeedMin;
    mPimpl->mNeedMax = rhs.mPimpl->mNeedMax;

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
    // Make sure that the model is valid before processing it.

    /*TODO: enable the below code once validation is known to work fine.
    libcellml::Validator validator;

    validator.validateModel(model);

    if (validator.errorCount() > 0) {
        // The model is not valid, so retrieve the validation errors and make
        // them our own.

        for (size_t i = 0; i < validator.errorCount(); ++i) {
            addError(validator.error(i));
        }

        return;
    }
*/

    // Process the model.

    mPimpl->processModel(model);
}

Generator::ModelType Generator::modelType() const
{
    return mPimpl->mModelType;
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
            || (variable->mType == GeneratorVariableImpl::Type::COMPUTED_TRUE_CONSTANT)
            || (variable->mType == GeneratorVariableImpl::Type::COMPUTED_VARIABLE_BASED_CONSTANT)) {
            ++res;
        }
    }

    return res;
}

/*ISSUE359: to be done.
GeneratorVariablePtr Generator::variableOfIntegration() const
{
    return {};
}
*/

/*ISSUE359: to be done.
GeneratorVariablePtr Generator::state(size_t index) const
{
    (void)index;

    return {};
}
*/

/*ISSUE359: to be done.
GeneratorVariablePtr Generator::variable(size_t index) const
{
    (void)index;

    return {};
}
*/

std::string Generator::code() const
{
    if (!mPimpl->hasValidModel()) {
        return {};
    }

    // Generate code for extra mathematical functions.

    std::string res;

    if (mPimpl->mNeedMin) {
        res += mPimpl->mProfile->minFunctionString();
    }

    if (mPimpl->mNeedMax) {
        if (!res.empty()) {
            res += "\n";
        }

        res += mPimpl->mProfile->maxFunctionString();
    }

    // Generate code to initialise the model.

    std::string body;

    for (const auto &variable : mPimpl->mVariables) {
        if ((variable->mType == GeneratorVariableImpl::Type::STATE)
            || (variable->mType == GeneratorVariableImpl::Type::CONSTANT)) {
            body += mPimpl->generateInitializationCode(variable);
        }
    }

    for (const auto &equation : mPimpl->mEquations) {
        if (equation->mType == GeneratorEquationImpl::Type::TRUE_CONSTANT) {
            body += mPimpl->generateEquationCode(equation);
        }
    }

    if (!body.empty()) {
        if (!res.empty()) {
            res += "\n";
        }

        res += mPimpl->mProfile->beginInitializeModelMethodString();
        res += body;
        res += mPimpl->mProfile->endInitializeModelMethodString();
    }

    // Generate code to compute the constant equations.

    body = "";

    for (const auto &equation : mPimpl->mEquations) {
        if (equation->mType == GeneratorEquationImpl::Type::VARIABLE_BASED_CONSTANT) {
            body += mPimpl->generateEquationCode(equation);
        }
    }

    if (!body.empty()) {
        if (!res.empty()) {
            res += "\n";
        }

        res += mPimpl->mProfile->beginComputeConstantEquationsMethodString();
        res += body;
        res += mPimpl->mProfile->endComputeConstantEquationsMethodString();
    }

    // Generate code to compute the rate equations (and the algebraic equations
    // on which they depend).

    body = "";

    for (const auto &equation : mPimpl->mEquations) {
        if (equation->mType == GeneratorEquationImpl::Type::RATE) {
            body += mPimpl->generateEquationCode(equation);
        }
    }

    if (!body.empty()) {
        if (!res.empty()) {
            res += "\n";
        }

        res += mPimpl->mProfile->beginComputeRateEquationsMethodString();
        res += body;
        res += mPimpl->mProfile->endComputeRateEquationsMethodString();
    }

    // Generate code to compute the (remaining) algebraic equations.

    body = "";

    for (const auto &equation : mPimpl->mEquations) {
        if (equation->mType == GeneratorEquationImpl::Type::ALGEBRAIC) {
            body += mPimpl->generateEquationCode(equation);
        }
    }

    if (!body.empty()) {
        if (!res.empty()) {
            res += "\n";
        }

        res += mPimpl->mProfile->beginComputeAlgebraicEquationsMethodString();
        res += body;
        res += mPimpl->mProfile->endComputeAlgebraicEquationsMethodString();
    }

    return res;
}

} // namespace libcellml

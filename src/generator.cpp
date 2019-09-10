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
#include "libcellml/version.h"

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

struct GeneratorVariable::GeneratorVariableImpl
{
    VariablePtr mVariable;
    GeneratorVariable::Type mType = GeneratorVariable::Type::CONSTANT;

    void populate(const VariablePtr &variable, GeneratorVariable::Type type);
};

void GeneratorVariable::GeneratorVariableImpl::populate(const VariablePtr &variable,
                                                        GeneratorVariable::Type type)
{
    mVariable = variable;
    mType = type;
}

GeneratorVariable::GeneratorVariable()
    : mPimpl(new GeneratorVariableImpl())
{
}

GeneratorVariable::~GeneratorVariable()
{
    delete mPimpl;
}

GeneratorVariable::GeneratorVariable(const GeneratorVariable &rhs)
    : mPimpl(new GeneratorVariableImpl())
{
    mPimpl->mVariable = rhs.mPimpl->mVariable;
    mPimpl->mType = rhs.mPimpl->mType;
}

GeneratorVariable::GeneratorVariable(GeneratorVariable &&rhs) noexcept
    : mPimpl(rhs.mPimpl)
{
    rhs.mPimpl = nullptr;
}

GeneratorVariable &GeneratorVariable::operator=(GeneratorVariable rhs)
{
    rhs.swap(*this);
    return *this;
}

void GeneratorVariable::swap(GeneratorVariable &rhs)
{
    std::swap(mPimpl, rhs.mPimpl);
}

VariablePtr GeneratorVariable::variable() const
{
    return mPimpl->mVariable;
}

GeneratorVariable::Type GeneratorVariable::type() const
{
    return mPimpl->mType;
}

struct GeneratorEquation;
using GeneratorEquationPtr = std::shared_ptr<GeneratorEquation>;
using GeneratorEquationWeakPtr = std::weak_ptr<GeneratorEquation>;

struct GeneratorInternalVariable
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

    size_t mIndex = MAX_SIZE_T;
    Type mType = Type::UNKNOWN;

    VariablePtr mVariable;

    GeneratorEquationWeakPtr mEquation;

    explicit GeneratorInternalVariable(const VariablePtr &variable);

    void setVariable(const VariablePtr &variable);

    void makeVoi();
    void makeState();
};

using GeneratorInternalVariablePtr = std::shared_ptr<GeneratorInternalVariable>;

GeneratorInternalVariable::GeneratorInternalVariable(const VariablePtr &variable)
{
    setVariable(variable);
}

void GeneratorInternalVariable::setVariable(const VariablePtr &variable)
{
    mVariable = variable;

    if (!variable->initialValue().empty()) {
        // The variable has an initial value, so it can either be a constant or
        // a state. By default, we consider it to be a constant and, if we find
        // an ODE for that variable, we will know that it was actually a state.

        mType = Type::CONSTANT;
    }
}

void GeneratorInternalVariable::makeVoi()
{
    mType = Type::VARIABLE_OF_INTEGRATION;
}

void GeneratorInternalVariable::makeState()
{
    if (mType == Type::UNKNOWN) {
        mType = Type::SHOULD_BE_STATE;
    } else if (mType == Type::CONSTANT) {
        mType = Type::STATE;
    }
}

struct GeneratorEquationAst;
using GeneratorEquationAstPtr = std::shared_ptr<GeneratorEquationAst>;
using GeneratorEquationAstWeakPtr = std::weak_ptr<GeneratorEquationAst>;

struct GeneratorEquationAst
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
        MIN,
        MAX,
        REM,

        // Calculus elements

        DIFF,

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

        // Piecewise statement

        PIECEWISE,
        PIECE,
        OTHERWISE,

        // Token elements

        CI,
        CN,

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

GeneratorEquationAst::GeneratorEquationAst() = default;

GeneratorEquationAst::GeneratorEquationAst(Type type,
                                           const GeneratorEquationAstPtr &parent)
    : mType(type)
    , mParent(parent)
{
}

GeneratorEquationAst::GeneratorEquationAst(Type type, const std::string &value,
                                           const GeneratorEquationAstPtr &parent)
    : mType(type)
    , mValue(value)
    , mParent(parent)
{
}

GeneratorEquationAst::GeneratorEquationAst(Type type, const VariablePtr &variable,
                                           const GeneratorEquationAstPtr &parent)
    : mType(type)
    , mVariable(variable)
    , mParent(parent)
{
}

GeneratorEquationAst::GeneratorEquationAst(const GeneratorEquationAstPtr &ast,
                                           const GeneratorEquationAstPtr &parent)
    : mType(ast->mType)
    , mVariable(ast->mVariable)
    , mParent(parent)
    , mLeft(ast->mLeft)
    , mRight(ast->mRight)
{
}

#ifdef SWIG
struct GeneratorEquation
#else
struct GeneratorEquation: public std::enable_shared_from_this<GeneratorEquation>
#endif
{
    enum struct Type
    {
        UNKNOWN,
        TRUE_CONSTANT,
        VARIABLE_BASED_CONSTANT,
        RATE,
        ALGEBRAIC
    };

    size_t mOrder = MAX_SIZE_T;
    Type mType = Type::UNKNOWN;

    std::list<GeneratorEquationPtr> mDependencies;

    GeneratorEquationAstPtr mAst;

    std::list<GeneratorInternalVariablePtr> mVariables;
    std::list<GeneratorInternalVariablePtr> mOdeVariables;

    GeneratorInternalVariablePtr mVariable = nullptr;

    bool mComputedTrueConstant = true;
    bool mComputedVariableBasedConstant = true;

    bool mIsStateRateBased = false;

    explicit GeneratorEquation();

    void addVariable(const GeneratorInternalVariablePtr &variable);
    void addOdeVariable(const GeneratorInternalVariablePtr &odeVariable);

    static bool containsNonUnknownVariables(const std::list<GeneratorInternalVariablePtr> &variables);
    static bool containsNonConstantVariables(const std::list<GeneratorInternalVariablePtr> &variables);

    static bool knownVariable(const GeneratorInternalVariablePtr &variable);
    static bool knownOdeVariable(const GeneratorInternalVariablePtr &odeVariable);

    bool check(size_t & equationOrder, size_t & stateIndex, size_t & variableIndex);
};

GeneratorEquation::GeneratorEquation()
    : mAst(std::make_shared<GeneratorEquationAst>())
{
}

void GeneratorEquation::addVariable(const GeneratorInternalVariablePtr &variable)
{
    if (std::find(mVariables.begin(), mVariables.end(), variable) == mVariables.end()) {
        mVariables.push_back(variable);
    }
}

void GeneratorEquation::addOdeVariable(const GeneratorInternalVariablePtr &odeVariable)
{
    if (std::find(mOdeVariables.begin(), mOdeVariables.end(), odeVariable) == mOdeVariables.end()) {
        mOdeVariables.push_back(odeVariable);
    }
}

bool GeneratorEquation::containsNonUnknownVariables(const std::list<GeneratorInternalVariablePtr> &variables)
{
    return std::find_if(variables.begin(), variables.end(), [](const GeneratorInternalVariablePtr &variable) {
               return (variable->mType != GeneratorInternalVariable::Type::UNKNOWN);
           })
           != std::end(variables);
}

bool GeneratorEquation::containsNonConstantVariables(const std::list<GeneratorInternalVariablePtr> &variables)
{
    return std::find_if(variables.begin(), variables.end(), [](const GeneratorInternalVariablePtr &variable) {
               return (variable->mType != GeneratorInternalVariable::Type::UNKNOWN)
                      && (variable->mType != GeneratorInternalVariable::Type::CONSTANT)
                      && (variable->mType != GeneratorInternalVariable::Type::COMPUTED_TRUE_CONSTANT)
                      && (variable->mType != GeneratorInternalVariable::Type::COMPUTED_VARIABLE_BASED_CONSTANT);
           })
           != std::end(variables);
}

bool GeneratorEquation::knownVariable(const GeneratorInternalVariablePtr &variable)
{
    return (variable->mIndex != MAX_SIZE_T)
           || (variable->mType == GeneratorInternalVariable::Type::VARIABLE_OF_INTEGRATION)
           || (variable->mType == GeneratorInternalVariable::Type::STATE)
           || (variable->mType == GeneratorInternalVariable::Type::CONSTANT)
           || (variable->mType == GeneratorInternalVariable::Type::COMPUTED_TRUE_CONSTANT)
           || (variable->mType == GeneratorInternalVariable::Type::COMPUTED_VARIABLE_BASED_CONSTANT);
}

bool GeneratorEquation::knownOdeVariable(const GeneratorInternalVariablePtr &odeVariable)
{
    return (odeVariable->mIndex != MAX_SIZE_T)
           || (odeVariable->mType == GeneratorInternalVariable::Type::VARIABLE_OF_INTEGRATION);
}

bool GeneratorEquation::check(size_t &equationOrder, size_t &stateIndex,
                              size_t &variableIndex)
{
    // Nothing to check if the equation has already been given an order (i.e.
    // everything is fine) or if there is one known (ODE) variable left (i.e.
    // this equation is an overconstraint).

    if (mOrder != MAX_SIZE_T) {
        return false;
    }

    if (mVariables.size() + mOdeVariables.size() == 1) {
        GeneratorInternalVariablePtr variable = (mVariables.size() == 1) ? mVariables.front() : mOdeVariables.front();

        if ((variable->mIndex != MAX_SIZE_T)
            && (variable->mType != GeneratorInternalVariable::Type::UNKNOWN)
            && (variable->mType != GeneratorInternalVariable::Type::SHOULD_BE_STATE)) {
            variable->mType = GeneratorInternalVariable::Type::OVERCONSTRAINED;

            return false;
        }
    }

    // Determine, from the (new) known (ODE) variables, whether the equation is
    // truly constant or variable-based constant.

    mComputedTrueConstant = mComputedTrueConstant
                            && !containsNonUnknownVariables(mVariables)
                            && !containsNonUnknownVariables(mOdeVariables);
    mComputedVariableBasedConstant = mComputedVariableBasedConstant
                                     && !containsNonConstantVariables(mVariables)
                                     && !containsNonConstantVariables(mOdeVariables);

    // Determine whether the equation is state/rate based and add, as a
    // dependency, the equations used to compute the (new) known variables.
    // (Note that we don't account for the (new) known ODE variables since their
    // corresponding equation can obviously not be of algebraic type.)

    if (!mIsStateRateBased) {
        mIsStateRateBased = !mOdeVariables.empty();
    }

    for (const auto &variable : mVariables) {
        if (knownVariable(variable)) {
            GeneratorEquationPtr equation = variable->mEquation.lock();

            if (!mIsStateRateBased) {
                mIsStateRateBased = (equation == nullptr) ?
                                        (variable->mType == GeneratorInternalVariable::Type::STATE) :
                                        equation->mIsStateRateBased;
            }

            if (equation != nullptr) {
                mDependencies.push_back(equation);
            }
        }
    }

    // Stop tracking (new) known (ODE) variables.

    mVariables.remove_if(knownVariable);
    mOdeVariables.remove_if(knownOdeVariable);

    // If there is one (ODE) variable left then update its type (if it is
    // currently unknown), determine its index and determine the type of our
    // equation and set its order, if the (ODE) variable is a state, computed
    // constant or algebraic variable.

    bool relevantCheck = false;

    if (mVariables.size() + mOdeVariables.size() == 1) {
        GeneratorInternalVariablePtr variable = (mVariables.size() == 1) ? mVariables.front() : mOdeVariables.front();

        if (variable->mType == GeneratorInternalVariable::Type::UNKNOWN) {
            variable->mType = mComputedTrueConstant ?
                                  GeneratorInternalVariable::Type::COMPUTED_TRUE_CONSTANT :
                                  mComputedVariableBasedConstant ?
                                  GeneratorInternalVariable::Type::COMPUTED_VARIABLE_BASED_CONSTANT :
                                  GeneratorInternalVariable::Type::ALGEBRAIC;
        }

        if ((variable->mType == GeneratorInternalVariable::Type::STATE)
            || (variable->mType == GeneratorInternalVariable::Type::COMPUTED_TRUE_CONSTANT)
            || (variable->mType == GeneratorInternalVariable::Type::COMPUTED_VARIABLE_BASED_CONSTANT)
            || (variable->mType == GeneratorInternalVariable::Type::ALGEBRAIC)) {
            variable->mIndex = (variable->mType == GeneratorInternalVariable::Type::STATE) ?
                                   ++stateIndex :
                                   ++variableIndex;

            variable->mEquation = shared_from_this();

            mOrder = ++equationOrder;
            mType = (variable->mType == GeneratorInternalVariable::Type::STATE) ?
                        Type::RATE :
                        (variable->mType == GeneratorInternalVariable::Type::COMPUTED_TRUE_CONSTANT) ?
                        Type::TRUE_CONSTANT :
                        (variable->mType == GeneratorInternalVariable::Type::COMPUTED_VARIABLE_BASED_CONSTANT) ?
                        Type::VARIABLE_BASED_CONSTANT :
                        Type::ALGEBRAIC;

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

    std::list<GeneratorInternalVariablePtr> mInternalVariables;
    std::list<GeneratorEquationPtr> mEquations;

    VariablePtr mVoi;
    std::vector<VariablePtr> mStates;
    std::vector<GeneratorVariablePtr> mVariables;

    GeneratorProfilePtr mProfile = std::make_shared<libcellml::GeneratorProfile>();

    bool mNeedEqEq = false;
    bool mNeedNeq = false;
    bool mNeedLt = false;
    bool mNeedLeq = false;
    bool mNeedGt = false;
    bool mNeedGeq = false;
    bool mNeedAnd = false;
    bool mNeedOr = false;
    bool mNeedXor = false;
    bool mNeedNot = false;

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

    GeneratorInternalVariablePtr generatorVariable(const VariablePtr &variable);

    static bool compareVariablesByName(const GeneratorInternalVariablePtr &variable1,
                                       const GeneratorInternalVariablePtr &variable2);
    static bool compareVariablesByTypeAndIndex(const GeneratorInternalVariablePtr &variable1,
                                               const GeneratorInternalVariablePtr &variable2);

    static bool compareEquationsByVariable(const GeneratorEquationPtr &equation1,
                                           const GeneratorEquationPtr &equation2);

    void processNode(const XmlNodePtr &node, GeneratorEquationAstPtr &ast,
                     const GeneratorEquationAstPtr &astParent,
                     const ComponentPtr &component,
                     const GeneratorEquationPtr &equation);
    GeneratorEquationPtr processNode(const XmlNodePtr &node,
                                     const ComponentPtr &component);
    void processComponent(const ComponentPtr &component);
    void processEquationAst(const GeneratorEquationAstPtr &ast);
    void processModel(const ModelPtr &model);

    bool isRelationalOperator(const GeneratorEquationAstPtr &ast) const;
    bool isAndOperator(const GeneratorEquationAstPtr &ast) const;
    bool isOrOperator(const GeneratorEquationAstPtr &ast) const;
    bool isXorOperator(const GeneratorEquationAstPtr &ast) const;
    bool isLogicalOperator(const GeneratorEquationAstPtr &ast) const;
    bool isPlusOperator(const GeneratorEquationAstPtr &ast) const;
    bool isMinusOperator(const GeneratorEquationAstPtr &ast) const;
    bool isTimesOperator(const GeneratorEquationAstPtr &ast) const;
    bool isDivideOperator(const GeneratorEquationAstPtr &ast) const;
    bool isPowerOperator(const GeneratorEquationAstPtr &ast) const;
    bool isRootOperator(const GeneratorEquationAstPtr &ast) const;
    bool isPiecewiseStatement(const GeneratorEquationAstPtr &ast) const;

    std::string replace(std::string string, const std::string &from,
                        const std::string &to);

    void updateVariableInfoSizes(size_t &componentSize, size_t &nameSize,
                                 size_t &unitsSize,
                                 const VariablePtr &variable);

    std::string generateVariableInfoObjectCode();
    std::string generateVariableInfoEntryCode(const std::string &component,
                                              const std::string &name,
                                              const std::string &units);
    std::string generateVoiInfoCode();
    std::string generateStateInfoCode();
    std::string generateVariableInfoCode();

    std::string generateDoubleCode(const std::string &value);
    std::string generateVariableNameCode(const VariablePtr &variable,
                                         const GeneratorEquationAstPtr &ast = nullptr);

    std::string generateOperatorCode(const std::string &op,
                                     const GeneratorEquationAstPtr &ast);
    std::string generateMinusUnaryCode(const GeneratorEquationAstPtr &ast);
    std::string generateOneParameterFunctionCode(const std::string &function,
                                                 const GeneratorEquationAstPtr &ast);
    std::string generateTwoParameterFunctionCode(const std::string &function,
                                                 const GeneratorEquationAstPtr &ast);
    std::string generatePiecewiseIfCode(const std::string &condition,
                                        const std::string &value);
    std::string generatePiecewiseElseCode(const std::string &value);
    std::string generateCode(const GeneratorEquationAstPtr &ast);

    std::string generateCreateArrayCode(size_t arraySize);
    std::string replaceTemplateValue(const std::string &templateString,
                                     size_t value);
    std::string replaceTemplateValue(const std::string &templateString,
                                     const std::string &value);
    std::string replaceMultipleTemplateValues(std::string templateString,
                                              const std::vector<std::string> &replacements);
    std::string replaceMultipleTemplateValues(std::string templateString,
                                              const std::vector<size_t> &replacements);

    std::string generateInitializationCode(const GeneratorInternalVariablePtr &variable);
    std::string generateEquationCode(const GeneratorEquationPtr &equation,
                                     std::vector<GeneratorEquationPtr> &remainingEquations,
                                     bool onlyStateRateBasedEquations = false);

    std::string generateMethodBodyCode(const std::string &methodBody);
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

GeneratorInternalVariablePtr Generator::GeneratorImpl::generatorVariable(const VariablePtr &variable)
{
    // Find and return, if there is one, the generator variable associated with
    // the given variable.

    for (const auto &internalVariable : mInternalVariables) {
        if ((variable == internalVariable->mVariable)
            || variable->hasEquivalentVariable(internalVariable->mVariable)) {
            return internalVariable;
        }
    }

    // No generator variable exists for the given variable, so create one, track
    // it and return it.

    GeneratorInternalVariablePtr internalVariable = std::make_shared<GeneratorInternalVariable>(variable);

    mInternalVariables.push_back(internalVariable);

    return internalVariable;
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
        processNode(mathmlChildNode(node, 1), ast->mLeft, ast, component, equation);

        if (childCount >= 3) {
            GeneratorEquationAstPtr astRight;
            GeneratorEquationAstPtr tempAst;

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
        // GeneratorEquationAst::Type::EQ type.

        if (!node->parent()->parent()->isMathmlElement("math")) {
            ast = std::make_shared<GeneratorEquationAst>(GeneratorEquationAst::Type::EQEQ, astParent);

            mNeedEqEq = true;
        }
    } else if (node->isMathmlElement("neq")) {
        ast = std::make_shared<GeneratorEquationAst>(GeneratorEquationAst::Type::NEQ, astParent);

        mNeedNeq = true;
    } else if (node->isMathmlElement("lt")) {
        ast = std::make_shared<GeneratorEquationAst>(GeneratorEquationAst::Type::LT, astParent);

        mNeedLt = true;
    } else if (node->isMathmlElement("leq")) {
        ast = std::make_shared<GeneratorEquationAst>(GeneratorEquationAst::Type::LEQ, astParent);

        mNeedLeq = true;
    } else if (node->isMathmlElement("gt")) {
        ast = std::make_shared<GeneratorEquationAst>(GeneratorEquationAst::Type::GT, astParent);

        mNeedGt = true;
    } else if (node->isMathmlElement("geq")) {
        ast = std::make_shared<GeneratorEquationAst>(GeneratorEquationAst::Type::GEQ, astParent);

        mNeedGeq = true;
    } else if (node->isMathmlElement("and")) {
        ast = std::make_shared<GeneratorEquationAst>(GeneratorEquationAst::Type::AND, astParent);

        mNeedAnd = true;
    } else if (node->isMathmlElement("or")) {
        ast = std::make_shared<GeneratorEquationAst>(GeneratorEquationAst::Type::OR, astParent);

        mNeedOr = true;
    } else if (node->isMathmlElement("xor")) {
        ast = std::make_shared<GeneratorEquationAst>(GeneratorEquationAst::Type::XOR, astParent);

        mNeedXor = true;
    } else if (node->isMathmlElement("not")) {
        ast = std::make_shared<GeneratorEquationAst>(GeneratorEquationAst::Type::NOT, astParent);

        mNeedNot = true;

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
    } else if (node->isMathmlElement("min")) {
        ast = std::make_shared<GeneratorEquationAst>(GeneratorEquationAst::Type::MIN, astParent);

        mNeedMin = true;
    } else if (node->isMathmlElement("max")) {
        ast = std::make_shared<GeneratorEquationAst>(GeneratorEquationAst::Type::MAX, astParent);

        mNeedMax = true;
    } else if (node->isMathmlElement("rem")) {
        ast = std::make_shared<GeneratorEquationAst>(GeneratorEquationAst::Type::REM, astParent);

        // Calculus elements

    } else if (node->isMathmlElement("diff")) {
        ast = std::make_shared<GeneratorEquationAst>(GeneratorEquationAst::Type::DIFF, astParent);

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

        // Piecewise statement

    } else if (node->isMathmlElement("piecewise")) {
        size_t childCount = mathmlChildCount(node);

        ast = std::make_shared<GeneratorEquationAst>(GeneratorEquationAst::Type::PIECEWISE, astParent);

        processNode(mathmlChildNode(node, 0), ast->mLeft, ast, component, equation);

        if (childCount >= 2) {
            GeneratorEquationAstPtr astRight;
            GeneratorEquationAstPtr tempAst;

            processNode(mathmlChildNode(node, childCount - 1), astRight, nullptr, component, equation);

            for (size_t i = childCount - 2; i > 0; --i) {
                tempAst = std::make_shared<GeneratorEquationAst>(GeneratorEquationAst::Type::PIECEWISE, astParent);

                processNode(mathmlChildNode(node, i), tempAst->mLeft, tempAst, component, equation);

                astRight->mParent = tempAst;

                tempAst->mRight = astRight;
                astRight = tempAst;
            }

            astRight->mParent = ast;

            ast->mRight = astRight;
        }
    } else if (node->isMathmlElement("piece")) {
        ast = std::make_shared<GeneratorEquationAst>(GeneratorEquationAst::Type::PIECE, astParent);

        processNode(mathmlChildNode(node, 0), ast->mLeft, ast, component, equation);
        processNode(mathmlChildNode(node, 1), ast->mRight, ast, component, equation);
    } else if (node->isMathmlElement("otherwise")) {
        ast = std::make_shared<GeneratorEquationAst>(GeneratorEquationAst::Type::OTHERWISE, astParent);

        processNode(mathmlChildNode(node, 0), ast->mLeft, ast, component, equation);

        // Token elements

    } else if (node->isMathmlElement("ci")) {
        std::string variableName = node->firstChild()->convertToString();
        VariablePtr variable = component->variable(variableName);

        if (variable != nullptr) {
            ast = std::make_shared<GeneratorEquationAst>(GeneratorEquationAst::Type::CI, variable, astParent);

            // Have our equation track the (ODE) variable (by ODE variable, we
            // mean a variable that is used in a "diff" element).

            GeneratorInternalVariablePtr generatorVariable = Generator::GeneratorImpl::generatorVariable(variable);

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
    } else if (node->isMathmlElement("cn")) {
        if (mathmlChildCount(node) == 1) {
            // We are dealing with an e-notation based CN value.

            ast = std::make_shared<GeneratorEquationAst>(GeneratorEquationAst::Type::CN, node->firstChild()->convertToString() + "e" + node->firstChild()->next()->next()->convertToString(), astParent);
        } else {
            ast = std::make_shared<GeneratorEquationAst>(GeneratorEquationAst::Type::CN, node->firstChild()->convertToString(), astParent);
        }

        // Qualifier elements

    } else if (node->isMathmlElement("degree")) {
        ast = std::make_shared<GeneratorEquationAst>(GeneratorEquationAst::Type::DEGREE, astParent);

        processNode(mathmlChildNode(node, 0), ast->mLeft, ast, component, equation);
    } else if (node->isMathmlElement("logbase")) {
        ast = std::make_shared<GeneratorEquationAst>(GeneratorEquationAst::Type::LOGBASE, astParent);

        processNode(mathmlChildNode(node, 0), ast->mLeft, ast, component, equation);
    } else if (node->isMathmlElement("bvar")) {
        ast = std::make_shared<GeneratorEquationAst>(GeneratorEquationAst::Type::BVAR, astParent);

        processNode(mathmlChildNode(node, 0), ast->mLeft, ast, component, equation);

        XmlNodePtr rightNode = mathmlChildNode(node, 1);

        if (rightNode != nullptr) {
            processNode(rightNode, ast->mRight, ast, component, equation);
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
    // Create and keep track of the equation associated with the given node.

    GeneratorEquationPtr equation = std::make_shared<GeneratorEquation>();

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
        GeneratorInternalVariablePtr generatorVariable = Generator::GeneratorImpl::generatorVariable(variable);

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

void Generator::GeneratorImpl::processEquationAst(const GeneratorEquationAstPtr &ast)
{
    // Look for the definition of a variable of integration and make sure that
    // we don't have more than one of it and that it's not initialised.

    GeneratorEquationAstPtr astParent = ast->mParent.lock();
    GeneratorEquationAstPtr astGrandParent = (astParent != nullptr) ? astParent->mParent.lock() : nullptr;
    GeneratorEquationAstPtr astGreatGrandParent = (astGrandParent != nullptr) ? astGrandParent->mParent.lock() : nullptr;

    if ((ast->mType == GeneratorEquationAst::Type::CI)
        && (astParent != nullptr) && (astParent->mType == GeneratorEquationAst::Type::BVAR)
        && (astGrandParent != nullptr) && (astGrandParent->mType == GeneratorEquationAst::Type::DIFF)) {
        VariablePtr variable = ast->mVariable;

        generatorVariable(variable)->makeVoi();
        // Note: we must make the variable a variable of integration in all
        //       cases (i.e. even if there is, for example, already another
        //       variable of integration) otherwise unnecessary error messages
        //       may be reported (since the type of the variable would be
        //       unknown).

        if (mVoi == nullptr) {
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
                mVoi = variable;
            }
        } else if ((variable != mVoi)
                   && !variable->hasEquivalentVariable(mVoi)) {
            ComponentPtr voiComponent = mVoi->parentComponent();
            ModelPtr voiModel = voiComponent->parentModel();
            ComponentPtr component = variable->parentComponent();
            ModelPtr model = component->parentModel();
            ErrorPtr err = std::make_shared<Error>();

            err->setDescription("Variable '" + mVoi->name()
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

    if ((ast->mType == GeneratorEquationAst::Type::CN)
        && (astParent != nullptr) && (astParent->mType == GeneratorEquationAst::Type::DEGREE)
        && (astGrandParent != nullptr) && (astGrandParent->mType == GeneratorEquationAst::Type::BVAR)
        && (astGreatGrandParent != nullptr) && (astGreatGrandParent->mType == GeneratorEquationAst::Type::DIFF)) {
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

    if ((ast->mType == GeneratorEquationAst::Type::CI)
        && (astParent != nullptr) && (astParent->mType == GeneratorEquationAst::Type::DIFF)) {
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

bool Generator::GeneratorImpl::compareVariablesByName(const GeneratorInternalVariablePtr &variable1,
                                                      const GeneratorInternalVariablePtr &variable2)
{
    // TODO: we can't currently instatiate imports, which means that we can't
    //       have variables in different models. This also means that we can't
    //       have code to check for the name of a model since this would fail
    //       coverage test. So, once we can instantiate imports, we will need to
    //       account the name of a model.
    VariablePtr realVariable1 = variable1->mVariable;
    VariablePtr realVariable2 = variable2->mVariable;
    ComponentPtr realComponent1 = realVariable1->parentComponent();
    ComponentPtr realComponent2 = realVariable2->parentComponent();

    if (realComponent1->name() == realComponent2->name()) {
        return realVariable1->name() < realVariable2->name();
    }

    return realComponent1->name() < realComponent2->name();
}

bool Generator::GeneratorImpl::compareVariablesByTypeAndIndex(const GeneratorInternalVariablePtr &variable1,
                                                              const GeneratorInternalVariablePtr &variable2)
{
    if (variable1->mType == variable2->mType) {
        return variable1->mIndex < variable2->mIndex;
    }

    return variable1->mType < variable2->mType;
}

bool Generator::GeneratorImpl::compareEquationsByVariable(const GeneratorEquationPtr &equation1,
                                                          const GeneratorEquationPtr &equation2)
{
    return compareVariablesByTypeAndIndex(equation1->mVariable, equation2->mVariable);
}

void Generator::GeneratorImpl::processModel(const ModelPtr &model)
{
    // Reset a few things in case we were to process the model more than once.
    // Note: one would normally process the model only once, so we shouldn't
    //       need to do this, but better be safe than sorry.

    mModelType = Generator::ModelType::UNKNOWN;

    mInternalVariables.clear();
    mEquations.clear();

    mVoi = nullptr;
    mStates.clear();
    mVariables.clear();

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
        mInternalVariables.sort(compareVariablesByName);

        size_t variableIndex = MAX_SIZE_T;

        for (const auto &internalVariable : mInternalVariables) {
            if (internalVariable->mType == GeneratorInternalVariable::Type::CONSTANT) {
                internalVariable->mIndex = ++variableIndex;
            }
        }

        size_t equationOrder = MAX_SIZE_T;
        size_t stateIndex = MAX_SIZE_T;

        for (;;) {
            bool relevantCheck = false;

            for (const auto &equation : mEquations) {
                relevantCheck = equation->check(equationOrder, stateIndex, variableIndex)
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
        for (const auto &internalVariable : mInternalVariables) {
            std::string errorType;

            switch (internalVariable->mType) {
            case GeneratorInternalVariable::Type::UNKNOWN:
                errorType = "is not computed";

                break;
            case GeneratorInternalVariable::Type::SHOULD_BE_STATE:
                errorType = "is used in an ODE, but it is not initialised";

                break;
            case GeneratorInternalVariable::Type::VARIABLE_OF_INTEGRATION:
            case GeneratorInternalVariable::Type::STATE:
            case GeneratorInternalVariable::Type::CONSTANT:
            case GeneratorInternalVariable::Type::COMPUTED_TRUE_CONSTANT:
            case GeneratorInternalVariable::Type::COMPUTED_VARIABLE_BASED_CONSTANT:
            case GeneratorInternalVariable::Type::ALGEBRAIC:
                break;
            case GeneratorInternalVariable::Type::OVERCONSTRAINED:
                errorType = "is computed more than once";

                break;
            }

            if (!errorType.empty()) {
                ErrorPtr err = std::make_shared<Error>();
                VariablePtr realVariable = internalVariable->mVariable;
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
    // being invalid.

    if (mModelType != Generator::ModelType::INVALID) {
        bool hasUnderconstrainedVariables = std::find_if(mInternalVariables.begin(), mInternalVariables.end(), [](const GeneratorInternalVariablePtr &variable) {
                                                return (variable->mType == GeneratorInternalVariable::Type::UNKNOWN)
                                                       || (variable->mType == GeneratorInternalVariable::Type::SHOULD_BE_STATE);
                                            })
                                            != std::end(mInternalVariables);
        bool hasOverconstrainedVariables = std::find_if(mInternalVariables.begin(), mInternalVariables.end(), [](const GeneratorInternalVariablePtr &variable) {
                                               return variable->mType == GeneratorInternalVariable::Type::OVERCONSTRAINED;
                                           })
                                           != std::end(mInternalVariables);

        if (hasUnderconstrainedVariables) {
            if (hasOverconstrainedVariables) {
                mModelType = Generator::ModelType::UNSUITABLY_CONSTRAINED;
            } else {
                mModelType = Generator::ModelType::UNDERCONSTRAINED;
            }
        } else if (hasOverconstrainedVariables) {
            mModelType = Generator::ModelType::OVERCONSTRAINED;
        } else if (mVoi != nullptr) {
            mModelType = Generator::ModelType::ODE;
        } else if (!mInternalVariables.empty()) {
            mModelType = Generator::ModelType::ALGEBRAIC;
        }
    }

    // Sort our variables and equations, should we have a valid model, and make
    // our internal variables available through our API.

    if ((mModelType == Generator::ModelType::ODE)
        || (mModelType == Generator::ModelType::ALGEBRAIC)) {
        mInternalVariables.sort(compareVariablesByTypeAndIndex);
        mEquations.sort(compareEquationsByVariable);

        for (const auto &internalVariable : mInternalVariables) {
            if (internalVariable->mType == GeneratorInternalVariable::Type::STATE) {
                mStates.push_back(internalVariable->mVariable);
            } else if ((internalVariable->mType == GeneratorInternalVariable::Type::CONSTANT)
                       || (internalVariable->mType == GeneratorInternalVariable::Type::COMPUTED_TRUE_CONSTANT)
                       || (internalVariable->mType == GeneratorInternalVariable::Type::COMPUTED_VARIABLE_BASED_CONSTANT)
                       || (internalVariable->mType == GeneratorInternalVariable::Type::ALGEBRAIC)) {
                GeneratorVariablePtr variable = std::make_shared<GeneratorVariable>();

                mVariables.push_back(variable);

                if (internalVariable->mType == GeneratorInternalVariable::Type::CONSTANT) {
                    variable->mPimpl->populate(internalVariable->mVariable, GeneratorVariable::Type::CONSTANT);
                } else if ((internalVariable->mType == GeneratorInternalVariable::Type::COMPUTED_TRUE_CONSTANT)
                           || (internalVariable->mType == GeneratorInternalVariable::Type::COMPUTED_VARIABLE_BASED_CONSTANT)) {
                    variable->mPimpl->populate(internalVariable->mVariable, GeneratorVariable::Type::COMPUTED_CONSTANT);
                } else {
                    variable->mPimpl->populate(internalVariable->mVariable, GeneratorVariable::Type::ALGEBRAIC);
                }
            }
        }
    }
}

bool Generator::GeneratorImpl::isRelationalOperator(const GeneratorEquationAstPtr &ast) const
{
    return ((ast->mType == GeneratorEquationAst::Type::EQEQ)
            && mProfile->hasEqEqOperator())
           || ((ast->mType == GeneratorEquationAst::Type::NEQ)
               && mProfile->hasNeqOperator())
           || ((ast->mType == GeneratorEquationAst::Type::LT)
               && mProfile->hasLtOperator())
           || ((ast->mType == GeneratorEquationAst::Type::LEQ)
               && mProfile->hasLeqOperator())
           || ((ast->mType == GeneratorEquationAst::Type::GT)
               && mProfile->hasGtOperator())
           || ((ast->mType == GeneratorEquationAst::Type::GEQ)
               && mProfile->hasGeqOperator());
}

bool Generator::GeneratorImpl::isAndOperator(const GeneratorEquationAstPtr &ast) const
{
    return (ast->mType == GeneratorEquationAst::Type::AND)
           && mProfile->hasAndOperator();
}

bool Generator::GeneratorImpl::isOrOperator(const GeneratorEquationAstPtr &ast) const
{
    return (ast->mType == GeneratorEquationAst::Type::OR)
           && mProfile->hasOrOperator();
}

bool Generator::GeneratorImpl::isXorOperator(const GeneratorEquationAstPtr &ast) const
{
    return (ast->mType == GeneratorEquationAst::Type::XOR)
           && mProfile->hasXorOperator();
}

bool Generator::GeneratorImpl::isLogicalOperator(const GeneratorEquationAstPtr &ast) const
{
    // Note: GeneratorEquationAst::Type::NOT is a unary logical operator, hence
    //       we don't include it here since this method is only used to
    //       determine whether parentheses should be added around some code.

    return isAndOperator(ast) || isOrOperator(ast) || isXorOperator(ast);
}

bool Generator::GeneratorImpl::isPlusOperator(const GeneratorEquationAstPtr &ast) const
{
    return ast->mType == GeneratorEquationAst::Type::PLUS;
}

bool Generator::GeneratorImpl::isMinusOperator(const GeneratorEquationAstPtr &ast) const
{
    return ast->mType == GeneratorEquationAst::Type::MINUS;
}

bool Generator::GeneratorImpl::isTimesOperator(const GeneratorEquationAstPtr &ast) const
{
    return ast->mType == GeneratorEquationAst::Type::TIMES;
}

bool Generator::GeneratorImpl::isDivideOperator(const GeneratorEquationAstPtr &ast) const
{
    return ast->mType == GeneratorEquationAst::Type::DIVIDE;
}

bool Generator::GeneratorImpl::isPowerOperator(const GeneratorEquationAstPtr &ast) const
{
    return (ast->mType == GeneratorEquationAst::Type::POWER)
           && mProfile->hasPowerOperator();
}

bool Generator::GeneratorImpl::isRootOperator(const GeneratorEquationAstPtr &ast) const
{
    return (ast->mType == GeneratorEquationAst::Type::ROOT)
           && mProfile->hasPowerOperator();
}

bool Generator::GeneratorImpl::isPiecewiseStatement(const GeneratorEquationAstPtr &ast) const
{
    return (ast->mType == GeneratorEquationAst::Type::PIECEWISE)
           && mProfile->hasConditionalOperator();
}

std::string Generator::GeneratorImpl::replace(std::string string,
                                              const std::string &from,
                                              const std::string &to)
{
    auto index = string.find(from);

    return (string.empty() || (index == std::string::npos)) ?
               "" :
               string.replace(index, from.length(), to);
}

void Generator::GeneratorImpl::updateVariableInfoSizes(size_t &componentSize,
                                                       size_t &nameSize,
                                                       size_t &unitsSize,
                                                       const VariablePtr &variable)
{
    auto variableComponentSize = variable->parentComponent()->name().length() + 1;
    auto variableNameSize = variable->name().length() + 1;
    auto variableUnitsSize = variable->units().length() + 1;
    // Note: +1 to account for the end of string termination.

    componentSize = (componentSize > variableComponentSize) ? componentSize : variableComponentSize;
    nameSize = (nameSize > variableNameSize) ? nameSize : variableNameSize;
    unitsSize = (unitsSize > variableUnitsSize) ? unitsSize : variableUnitsSize;
}

std::string Generator::GeneratorImpl::generateVariableInfoObjectCode()
{
    size_t componentSize = 0;
    size_t nameSize = 0;
    size_t unitsSize = 0;

    if (mVoi != nullptr) {
        updateVariableInfoSizes(componentSize, nameSize, unitsSize, mVoi);
    }

    for (const auto &state : mStates) {
        updateVariableInfoSizes(componentSize, nameSize, unitsSize, state);
    }

    for (const auto &generatorVariable : mVariables) {
        auto variable = generatorVariable->variable();

        updateVariableInfoSizes(componentSize, nameSize, unitsSize, variable);
    }

    return replace(replace(replace(mProfile->variableInfoObjectString(),
                                   "<COMPONENT_SIZE>", std::to_string(componentSize)),
                           "<NAME_SIZE>", std::to_string(nameSize)),
                   "<UNITS_SIZE>", std::to_string(unitsSize));
}

std::string Generator::GeneratorImpl::generateVariableInfoEntryCode(const std::string &component,
                                                                    const std::string &name,
                                                                    const std::string &units)
{
    return replace(replace(replace(mProfile->variableInfoEntryString(),
                                   "<COMPONENT>", component),
                           "<NAME>", name),
                   "<UNITS>", units);
}

std::string Generator::GeneratorImpl::generateVoiInfoCode()
{
    std::string component = (mVoi != nullptr) ? mVoi->parentComponent()->name() : "";
    std::string name = (mVoi != nullptr) ? mVoi->name() : "";
    std::string units = (mVoi != nullptr) ? mVoi->units() : "";

    return mProfile->beginVoiInfoString()
           + generateVariableInfoEntryCode(component, name, units)
           + mProfile->endVoiInfoString();
}

std::string Generator::GeneratorImpl::generateStateInfoCode()
{
    std::string stateInfoElements;

    for (const auto &state : mStates) {
        if (!stateInfoElements.empty()) {
            stateInfoElements += mProfile->arrayElementSeparatorString() + "\n";
        }

        stateInfoElements += mProfile->indentString()
                             + generateVariableInfoEntryCode(state->parentComponent()->name(),
                                                             state->name(), state->units());
    }

    if (!stateInfoElements.empty()) {
        stateInfoElements += "\n";
    }

    return mProfile->beginStateInfoString()
           + stateInfoElements
           + mProfile->endStateInfoString();
}

std::string Generator::GeneratorImpl::generateVariableInfoCode()
{
    std::string variableInfoElements;

    for (const auto &generatorVariable : mVariables) {
        auto variable = generatorVariable->variable();

        if (!variableInfoElements.empty()) {
            variableInfoElements += mProfile->arrayElementSeparatorString() + "\n";
        }

        variableInfoElements += mProfile->indentString()
                                + generateVariableInfoEntryCode(variable->parentComponent()->name(),
                                                                variable->name(),
                                                                variable->units());
    }

    if (!variableInfoElements.empty()) {
        variableInfoElements += "\n";
    }

    return mProfile->beginVariableInfoString()
           + variableInfoElements
           + mProfile->endVariableInfoString();
}

std::string Generator::GeneratorImpl::generateDoubleCode(const std::string &value)
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

std::string Generator::GeneratorImpl::generateVariableNameCode(const VariablePtr &variable, const GeneratorEquationAstPtr &ast)
{
    GeneratorInternalVariablePtr generatorVariable = Generator::GeneratorImpl::generatorVariable(variable);

    if (generatorVariable->mType == GeneratorInternalVariable::Type::VARIABLE_OF_INTEGRATION) {
        return mProfile->voiString();
    }

    std::string arrayName;

    if (generatorVariable->mType == GeneratorInternalVariable::Type::STATE) {
        arrayName = ((ast != nullptr) && (ast->mParent.lock()->mType == GeneratorEquationAst::Type::DIFF)) ?
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
                                                           const GeneratorEquationAstPtr &ast)
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
            || isLogicalOperator(ast->mLeft)
            || isPiecewiseStatement(ast->mLeft)) {
            left = "(" + left + ")";
        }

        if (isRelationalOperator(ast->mRight)
            || isLogicalOperator(ast->mRight)
            || isPiecewiseStatement(ast->mRight)) {
            right = "(" + right + ")";
        }
    } else if (isMinusOperator(ast)) {
        if (isRelationalOperator(ast->mLeft)
            || isLogicalOperator(ast->mLeft)
            || isPiecewiseStatement(ast->mLeft)) {
            left = "(" + left + ")";
        }

        if (isRelationalOperator(ast->mRight)
            || isLogicalOperator(ast->mRight)
            || isMinusOperator(ast->mRight)
            || isPiecewiseStatement(ast->mRight)) {
            right = "(" + right + ")";
        } else if (isPlusOperator(ast->mRight)) {
            if (ast->mRight->mRight != nullptr) {
                right = "(" + right + ")";
            }
        }
    } else if (isTimesOperator(ast)) {
        if (isRelationalOperator(ast->mLeft)
            || isLogicalOperator(ast->mLeft)
            || isPiecewiseStatement(ast->mLeft)) {
            left = "(" + left + ")";
        } else if (isPlusOperator(ast->mLeft)
                   || isMinusOperator(ast->mLeft)) {
            if (ast->mLeft->mRight != nullptr) {
                left = "(" + left + ")";
            }
        }

        if (isRelationalOperator(ast->mRight)
            || isLogicalOperator(ast->mRight)
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
            || isLogicalOperator(ast->mLeft)
            || isPiecewiseStatement(ast->mLeft)) {
            left = "(" + left + ")";
        } else if (isPlusOperator(ast->mLeft)
                   || isMinusOperator(ast->mLeft)) {
            if (ast->mLeft->mRight != nullptr) {
                left = "(" + left + ")";
            }
        }

        if (isRelationalOperator(ast->mRight)
            || isLogicalOperator(ast->mRight)
            || isTimesOperator(ast->mRight)
            || isDivideOperator(ast->mRight)
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
            left = "(" + left + ")";
        } else if (isRootOperator(ast->mLeft)) {
            left = "(" + left + ")";
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
            right = "(" + right + ")";
        } else if (isRootOperator(ast->mRight)) {
            right = "(" + right + ")";
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
            left = "(" + left + ")";
        } else if (isRootOperator(ast->mLeft)) {
            left = "(" + left + ")";
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
            right = "(" + right + ")";
        } else if (isRootOperator(ast->mRight)) {
            right = "(" + right + ")";
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
            left = "(" + left + ")";
        } else if (isRootOperator(ast->mLeft)) {
            left = "(" + left + ")";
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
            right = "(" + right + ")";
        } else if (isRootOperator(ast->mRight)) {
            right = "(" + right + ")";
        }
    } else if (isPowerOperator(ast)) {
        if (isRelationalOperator(ast->mLeft)
            || isLogicalOperator(ast->mLeft)
            || isMinusOperator(ast->mLeft)
            || isTimesOperator(ast->mLeft)
            || isDivideOperator(ast->mLeft)
            || isPiecewiseStatement(ast->mLeft)) {
            left = "(" + left + ")";
        } else if (isPlusOperator(ast->mLeft)) {
            if (ast->mLeft->mRight != nullptr) {
                left = "(" + left + ")";
            }
        }

        if (isRelationalOperator(ast->mRight)
            || isLogicalOperator(ast->mRight)
            || isMinusOperator(ast->mLeft)
            || isTimesOperator(ast->mRight)
            || isDivideOperator(ast->mRight)
            || isPowerOperator(ast->mRight)
            || isRootOperator(ast->mRight)
            || isPiecewiseStatement(ast->mRight)) {
            right = "(" + right + ")";
        } else if (isPlusOperator(ast->mRight)) {
            if (ast->mRight->mRight != nullptr) {
                right = "(" + right + ")";
            }
        }
    } else if (isRootOperator(ast)) {
        if (isRelationalOperator(ast->mRight)
            || isLogicalOperator(ast->mRight)
            || isMinusOperator(ast->mRight)
            || isTimesOperator(ast->mRight)
            || isDivideOperator(ast->mRight)
            || isPiecewiseStatement(ast->mRight)) {
            right = "(" + right + ")";
        } else if (isPlusOperator(ast->mRight)) {
            if (ast->mRight->mRight != nullptr) {
                right = "(" + right + ")";
            }
        }

        if (isRelationalOperator(ast->mLeft)
            || isLogicalOperator(ast->mLeft)
            || isMinusOperator(ast->mLeft)
            || isTimesOperator(ast->mLeft)
            || isDivideOperator(ast->mLeft)
            || isPowerOperator(ast->mLeft)
            || isRootOperator(ast->mLeft)
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

std::string Generator::GeneratorImpl::generateMinusUnaryCode(const GeneratorEquationAstPtr &ast)
{
    // Generate the code for the left branch of the given AST.

    std::string left = generateCode(ast->mLeft);

    // Determine whether parentheses should be added around the left code.

    if (isRelationalOperator(ast->mLeft)
        || isLogicalOperator(ast->mLeft)
        || isPlusOperator(ast->mLeft)
        || isMinusOperator(ast->mLeft)
        || isPiecewiseStatement(ast->mLeft)) {
        left = "(" + left + ")";
    }

    return mProfile->minusString() + left;
}

std::string Generator::GeneratorImpl::generateOneParameterFunctionCode(const std::string &function,
                                                                       const GeneratorEquationAstPtr &ast)
{
    return function + "(" + generateCode(ast->mLeft) + ")";
}

std::string Generator::GeneratorImpl::generateTwoParameterFunctionCode(const std::string &function,
                                                                       const GeneratorEquationAstPtr &ast)
{
    return function + "(" + generateCode(ast->mLeft) + ", " + generateCode(ast->mRight) + ")";
}

std::string Generator::GeneratorImpl::generatePiecewiseIfCode(const std::string &condition,
                                                              const std::string &value)
{
    return replace(replace(mProfile->hasConditionalOperator() ?
                               mProfile->conditionalOperatorIfString() :
                               mProfile->piecewiseIfString(),
                           "<CONDITION>", condition),
                   "<IF_STATEMENT>", value);
}

std::string Generator::GeneratorImpl::generatePiecewiseElseCode(const std::string &value)
{
    return replace(mProfile->hasConditionalOperator() ?
                       mProfile->conditionalOperatorElseString() :
                       mProfile->piecewiseElseString(),
                   "<ELSE_STATEMENT>", value);
}

std::string Generator::GeneratorImpl::generateCode(const GeneratorEquationAstPtr &ast)
{
    // Generate the code for the given AST.

    std::string code;

    switch (ast->mType) {
        // Relational and logical operators

    case GeneratorEquationAst::Type::EQ:
        code = generateOperatorCode(mProfile->eqString(), ast);

        break;
    case GeneratorEquationAst::Type::EQEQ:
        if (mProfile->hasEqEqOperator()) {
            code = generateOperatorCode(mProfile->eqEqString(), ast);
        } else {
            code = generateTwoParameterFunctionCode(mProfile->eqEqString(), ast);
        }

        break;
    case GeneratorEquationAst::Type::NEQ:
        if (mProfile->hasNeqOperator()) {
            code = generateOperatorCode(mProfile->neqString(), ast);
        } else {
            code = generateTwoParameterFunctionCode(mProfile->neqString(), ast);
        }

        break;
    case GeneratorEquationAst::Type::LT:
        if (mProfile->hasLtOperator()) {
            code = generateOperatorCode(mProfile->ltString(), ast);
        } else {
            code = generateTwoParameterFunctionCode(mProfile->ltString(), ast);
        }

        break;
    case GeneratorEquationAst::Type::LEQ:
        if (mProfile->hasLeqOperator()) {
            code = generateOperatorCode(mProfile->leqString(), ast);
        } else {
            code = generateTwoParameterFunctionCode(mProfile->leqString(), ast);
        }

        break;
    case GeneratorEquationAst::Type::GT:
        if (mProfile->hasGtOperator()) {
            code = generateOperatorCode(mProfile->gtString(), ast);
        } else {
            code = generateTwoParameterFunctionCode(mProfile->gtString(), ast);
        }

        break;
    case GeneratorEquationAst::Type::GEQ:
        if (mProfile->hasGeqOperator()) {
            code = generateOperatorCode(mProfile->geqString(), ast);
        } else {
            code = generateTwoParameterFunctionCode(mProfile->geqString(), ast);
        }

        break;
    case GeneratorEquationAst::Type::AND:
        if (mProfile->hasAndOperator()) {
            code = generateOperatorCode(mProfile->andString(), ast);
        } else {
            code = generateTwoParameterFunctionCode(mProfile->andString(), ast);
        }

        break;
    case GeneratorEquationAst::Type::OR:
        if (mProfile->hasOrOperator()) {
            code = generateOperatorCode(mProfile->orString(), ast);
        } else {
            code = generateTwoParameterFunctionCode(mProfile->orString(), ast);
        }

        break;
    case GeneratorEquationAst::Type::XOR:
        if (mProfile->hasXorOperator()) {
            code = generateOperatorCode(mProfile->xorString(), ast);
        } else {
            code = generateTwoParameterFunctionCode(mProfile->xorString(), ast);
        }

        break;
    case GeneratorEquationAst::Type::NOT:
        if (mProfile->hasNotOperator()) {
            code = mProfile->notString() + generateCode(ast->mLeft);
        } else {
            code = generateOneParameterFunctionCode(mProfile->notString(), ast);
        }

        break;

        // Arithmetic operators

    case GeneratorEquationAst::Type::PLUS:
        if (ast->mRight != nullptr) {
            code = generateOperatorCode(mProfile->plusString(), ast);
        } else {
            code = generateCode(ast->mLeft);
        }

        break;
    case GeneratorEquationAst::Type::MINUS:
        if (ast->mRight != nullptr) {
            code = generateOperatorCode(mProfile->minusString(), ast);
        } else {
            code = generateMinusUnaryCode(ast);
        }

        break;
    case GeneratorEquationAst::Type::TIMES:
        code = generateOperatorCode(mProfile->timesString(), ast);

        break;
    case GeneratorEquationAst::Type::DIVIDE:
        code = generateOperatorCode(mProfile->divideString(), ast);

        break;
    case GeneratorEquationAst::Type::POWER: {
        std::string stringValue = generateCode(ast->mRight);
        double doubleValue = convertToDouble(stringValue);

        if (isEqual(doubleValue, 0.5)) {
            code = generateOneParameterFunctionCode(mProfile->squareRootString(), ast);
        } else if (isEqual(doubleValue, 2.0) && !mProfile->squareString().empty()) {
            code = generateOneParameterFunctionCode(mProfile->squareString(), ast);
        } else {
            code = mProfile->hasPowerOperator() ?
                       generateOperatorCode(mProfile->powerString(), ast) :
                       mProfile->powerString() + "(" + generateCode(ast->mLeft) + ", " + stringValue + ")";
        }

        break;
    }
    case GeneratorEquationAst::Type::ROOT:
        if (ast->mRight != nullptr) {
            double doubleValue = convertToDouble(generateCode(ast->mLeft));

            if (isEqual(doubleValue, 2.0)) {
                code = mProfile->squareRootString() + "(" + generateCode(ast->mRight) + ")";
            } else {
                GeneratorEquationAstPtr rootValueAst = std::make_shared<GeneratorEquationAst>(GeneratorEquationAst::Type::DIVIDE, ast);

                rootValueAst->mLeft = std::make_shared<GeneratorEquationAst>(GeneratorEquationAst::Type::CN, "1.0", rootValueAst);
                rootValueAst->mRight = std::make_shared<GeneratorEquationAst>(ast->mLeft, rootValueAst);

                code = mProfile->hasPowerOperator() ?
                           generateOperatorCode(mProfile->powerString(), ast) :
                           mProfile->powerString() + "(" + generateCode(ast->mRight) + ", " + generateOperatorCode(mProfile->divideString(), rootValueAst) + ")";
            }
        } else {
            code = generateOneParameterFunctionCode(mProfile->squareRootString(), ast);
        }

        break;
    case GeneratorEquationAst::Type::ABS:
        code = generateOneParameterFunctionCode(mProfile->absoluteValueString(), ast);

        break;
    case GeneratorEquationAst::Type::EXP:
        code = generateOneParameterFunctionCode(mProfile->exponentialString(), ast);

        break;
    case GeneratorEquationAst::Type::LN:
        code = generateOneParameterFunctionCode(mProfile->napierianLogarithmString(), ast);

        break;
    case GeneratorEquationAst::Type::LOG:
        if (ast->mRight != nullptr) {
            std::string stringValue = generateCode(ast->mLeft);
            double doubleValue = convertToDouble(stringValue);

            if (isEqual(doubleValue, 10.0)) {
                code = mProfile->commonLogarithmString() + "(" + generateCode(ast->mRight) + ")";
            } else {
                code = mProfile->napierianLogarithmString() + "(" + generateCode(ast->mRight) + ")/" + mProfile->napierianLogarithmString() + "(" + stringValue + ")";
            }
        } else {
            code = generateOneParameterFunctionCode(mProfile->commonLogarithmString(), ast);
        }

        break;
    case GeneratorEquationAst::Type::CEILING:
        code = generateOneParameterFunctionCode(mProfile->ceilingString(), ast);

        break;
    case GeneratorEquationAst::Type::FLOOR:
        code = generateOneParameterFunctionCode(mProfile->floorString(), ast);

        break;
    case GeneratorEquationAst::Type::MIN:
        code = generateTwoParameterFunctionCode(mProfile->minString(), ast);

        break;
    case GeneratorEquationAst::Type::MAX:
        code = generateTwoParameterFunctionCode(mProfile->maxString(), ast);

        break;
    case GeneratorEquationAst::Type::REM:
        code = generateTwoParameterFunctionCode(mProfile->remString(), ast);

        break;

        // Calculus elements

    case GeneratorEquationAst::Type::DIFF:
        code = generateCode(ast->mRight);

        break;

        // Trigonometric operators

    case GeneratorEquationAst::Type::SIN:
        code = generateOneParameterFunctionCode(mProfile->sinString(), ast);

        break;
    case GeneratorEquationAst::Type::COS:
        code = generateOneParameterFunctionCode(mProfile->cosString(), ast);

        break;
    case GeneratorEquationAst::Type::TAN:
        code = generateOneParameterFunctionCode(mProfile->tanString(), ast);

        break;
    case GeneratorEquationAst::Type::SEC:
        code = generateOneParameterFunctionCode(mProfile->secString(), ast);

        break;
    case GeneratorEquationAst::Type::CSC:
        code = generateOneParameterFunctionCode(mProfile->cscString(), ast);

        break;
    case GeneratorEquationAst::Type::COT:
        code = generateOneParameterFunctionCode(mProfile->cotString(), ast);

        break;
    case GeneratorEquationAst::Type::SINH:
        code = generateOneParameterFunctionCode(mProfile->sinhString(), ast);

        break;
    case GeneratorEquationAst::Type::COSH:
        code = generateOneParameterFunctionCode(mProfile->coshString(), ast);

        break;
    case GeneratorEquationAst::Type::TANH:
        code = generateOneParameterFunctionCode(mProfile->tanhString(), ast);

        break;
    case GeneratorEquationAst::Type::SECH:
        code = generateOneParameterFunctionCode(mProfile->sechString(), ast);

        break;
    case GeneratorEquationAst::Type::CSCH:
        code = generateOneParameterFunctionCode(mProfile->cschString(), ast);

        break;
    case GeneratorEquationAst::Type::COTH:
        code = generateOneParameterFunctionCode(mProfile->cothString(), ast);

        break;
    case GeneratorEquationAst::Type::ASIN:
        code = generateOneParameterFunctionCode(mProfile->asinString(), ast);

        break;
    case GeneratorEquationAst::Type::ACOS:
        code = generateOneParameterFunctionCode(mProfile->acosString(), ast);

        break;
    case GeneratorEquationAst::Type::ATAN:
        code = generateOneParameterFunctionCode(mProfile->atanString(), ast);

        break;
    case GeneratorEquationAst::Type::ASEC:
        code = generateOneParameterFunctionCode(mProfile->asecString(), ast);

        break;
    case GeneratorEquationAst::Type::ACSC:
        code = generateOneParameterFunctionCode(mProfile->acscString(), ast);

        break;
    case GeneratorEquationAst::Type::ACOT:
        code = generateOneParameterFunctionCode(mProfile->acotString(), ast);

        break;
    case GeneratorEquationAst::Type::ASINH:
        code = generateOneParameterFunctionCode(mProfile->asinhString(), ast);

        break;
    case GeneratorEquationAst::Type::ACOSH:
        code = generateOneParameterFunctionCode(mProfile->acoshString(), ast);

        break;
    case GeneratorEquationAst::Type::ATANH:
        code = generateOneParameterFunctionCode(mProfile->atanhString(), ast);

        break;
    case GeneratorEquationAst::Type::ASECH:
        code = generateOneParameterFunctionCode(mProfile->asechString(), ast);

        break;
    case GeneratorEquationAst::Type::ACSCH:
        code = generateOneParameterFunctionCode(mProfile->acschString(), ast);

        break;
    case GeneratorEquationAst::Type::ACOTH:
        code = generateOneParameterFunctionCode(mProfile->acothString(), ast);

        break;

        // Piecewise statement

    case GeneratorEquationAst::Type::PIECEWISE:
        if (ast->mRight != nullptr) {
            if (ast->mRight->mType == GeneratorEquationAst::Type::PIECE) {
                code = generateCode(ast->mLeft) + generatePiecewiseElseCode(generateCode(ast->mRight) + generatePiecewiseElseCode(mProfile->nanString()));
            } else {
                code = generateCode(ast->mLeft) + generatePiecewiseElseCode(generateCode(ast->mRight));
            }
        } else {
            code = generateCode(ast->mLeft) + generatePiecewiseElseCode(mProfile->nanString());
        }

        break;
    case GeneratorEquationAst::Type::PIECE:
        code = generatePiecewiseIfCode(generateCode(ast->mRight), generateCode(ast->mLeft));

        break;
    case GeneratorEquationAst::Type::OTHERWISE:
        code = generateCode(ast->mLeft);

        break;

        // Token elements

    case GeneratorEquationAst::Type::CI:
        code = generateVariableNameCode(ast->mVariable, ast);

        break;
    case GeneratorEquationAst::Type::CN:
        code = generateDoubleCode(ast->mValue);

        break;

        // Qualifier elements

    case GeneratorEquationAst::Type::DEGREE:
    case GeneratorEquationAst::Type::LOGBASE:
    case GeneratorEquationAst::Type::BVAR:
        code = generateCode(ast->mLeft);

        break;

        // Constants

    case GeneratorEquationAst::Type::TRUE:
        code = mProfile->trueString();

        break;
    case GeneratorEquationAst::Type::FALSE:
        code = mProfile->falseString();

        break;
    case GeneratorEquationAst::Type::E:
        code = mProfile->eString();

        break;
    case GeneratorEquationAst::Type::PI:
        code = mProfile->piString();

        break;
    case GeneratorEquationAst::Type::INF:
        code = mProfile->infString();

        break;
    case GeneratorEquationAst::Type::NAN:
        code = mProfile->nanString();

        break;
    }

    return code;
}

std::string Generator::GeneratorImpl::generateCreateArrayCode(size_t arraySize)
{
    return replaceTemplateValue(mProfile->indentString() + mProfile->templateReturnCreatedArrayString(), arraySize);
}

std::string Generator::GeneratorImpl::replaceTemplateValue(const std::string &templateString, size_t value)
{
    std::string valueString = std::to_string(value);
    return replaceTemplateValue(templateString, valueString);
}

std::string Generator::GeneratorImpl::replaceTemplateValue(const std::string &templateString, const std::string &value)
{
    return replace(templateString, mProfile->templateReplacementString(), value);
}

std::string Generator::GeneratorImpl::replaceMultipleTemplateValues(std::string templateString, const std::vector<std::string> &replacements)
{
    for (const auto &entry : replacements) {
        templateString = replace(templateString, mProfile->templateReplacementString(), entry);
    }

    return templateString;
}

std::string Generator::GeneratorImpl::replaceMultipleTemplateValues(std::string templateString, const std::vector<size_t> &replacements)
{
    for (const auto &entry : replacements) {
        templateString = replace(templateString, mProfile->templateReplacementString(), std::to_string(entry));
    }

    return templateString;
}

std::string Generator::GeneratorImpl::generateInitializationCode(const GeneratorInternalVariablePtr &variable)
{
    return mProfile->indentString() + generateVariableNameCode(variable->mVariable) + " = " + generateDoubleCode(variable->mVariable->initialValue()) + mProfile->commandSeparatorString() + "\n";
}

std::string Generator::GeneratorImpl::generateEquationCode(const GeneratorEquationPtr &equation,
                                                           std::vector<GeneratorEquationPtr> &remainingEquations,
                                                           bool onlyStateRateBasedEquations)
{
    std::string res;

    for (const auto &dependency : equation->mDependencies) {
        if (!onlyStateRateBasedEquations
            || ((dependency->mType == GeneratorEquation::Type::ALGEBRAIC)
                && dependency->mIsStateRateBased)) {
            res += generateEquationCode(dependency, remainingEquations, onlyStateRateBasedEquations);
        }
    }

    auto equationIter = std::find(remainingEquations.begin(), remainingEquations.end(), equation);

    if (equationIter != remainingEquations.end()) {
        res += mProfile->indentString() + generateCode(equation->mAst) + mProfile->commandSeparatorString() + "\n";

        remainingEquations.erase(equationIter);
    }

    return res;
}

std::string Generator::GeneratorImpl::generateMethodBodyCode(const std::string &methodBody)
{
    return methodBody.empty() ?
               mProfile->emptyMethodString().empty() ?
               "" :
               mProfile->indentString() + mProfile->emptyMethodString() :
               methodBody;
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

    mPimpl->mInternalVariables = rhs.mPimpl->mInternalVariables;
    mPimpl->mEquations = rhs.mPimpl->mEquations;

    mPimpl->mVoi = rhs.mPimpl->mVoi;
    mPimpl->mStates = rhs.mPimpl->mStates;
    mPimpl->mVariables = rhs.mPimpl->mVariables;

    mPimpl->mProfile = rhs.mPimpl->mProfile;

    mPimpl->mNeedEqEq = rhs.mPimpl->mNeedEqEq;
    mPimpl->mNeedNeq = rhs.mPimpl->mNeedNeq;
    mPimpl->mNeedLt = rhs.mPimpl->mNeedLt;
    mPimpl->mNeedLeq = rhs.mPimpl->mNeedLeq;
    mPimpl->mNeedGt = rhs.mPimpl->mNeedGt;
    mPimpl->mNeedGeq = rhs.mPimpl->mNeedGeq;
    mPimpl->mNeedAnd = rhs.mPimpl->mNeedAnd;
    mPimpl->mNeedOr = rhs.mPimpl->mNeedOr;
    mPimpl->mNeedXor = rhs.mPimpl->mNeedXor;
    mPimpl->mNeedNot = rhs.mPimpl->mNeedNot;

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

    return mPimpl->mStates.size();
}

size_t Generator::variableCount() const
{
    if (!mPimpl->hasValidModel()) {
        return 0;
    }

    return mPimpl->mVariables.size();
}

VariablePtr Generator::voi() const
{
    if (!mPimpl->hasValidModel()) {
        return {};
    }

    return mPimpl->mVoi;
}

VariablePtr Generator::state(size_t index) const
{
    if (!mPimpl->hasValidModel() || (index >= mPimpl->mStates.size())) {
        return {};
    }

    return mPimpl->mStates[index];
}

GeneratorVariablePtr Generator::variable(size_t index) const
{
    if (!mPimpl->hasValidModel() || (index >= mPimpl->mVariables.size())) {
        return {};
    }

    return mPimpl->mVariables[index];
}

std::string Generator::code() const
{
    if (!mPimpl->hasValidModel()) {
        return {};
    }

    // Generate code for the origin comment.

    std::string res;
    std::string originComment = mPimpl->replace(mPimpl->mProfile->originCommentString(), "<VERSION>", versionString());

    if (!originComment.empty()) {
        res += mPimpl->mProfile->beginCommentString() + originComment + mPimpl->mProfile->endCommentString() + "\n";
    }

    // Generate code for the header.

    if (!mPimpl->mProfile->headerString().empty()) {
        if (!res.empty()) {
            res += "\n";
        }

        res += mPimpl->mProfile->headerString();
    }

    // Generate code for the version of libCellML.

    std::string version = mPimpl->replace(mPimpl->mProfile->versionString(), "<VERSION>", versionString());

    if (!version.empty()) {
        if (!res.empty()) {
            res += "\n";
        }

        res += version;
    }

    // Generate code for the number of states and variables.

    std::string stateCount = mPimpl->replace(mPimpl->mProfile->stateCountString(), "<STATE_COUNT>", std::to_string(mPimpl->mStates.size()));
    std::string variableCount = mPimpl->replace(mPimpl->mProfile->variableCountString(), "<VARIABLE_COUNT>", std::to_string(mPimpl->mVariables.size()));

    if (!stateCount.empty() || !variableCount.empty()) {
        if (!res.empty()) {
            res += "\n";
        }

        res += stateCount;
        res += variableCount;
    }

    // Generate code for the data structure.

    if (!mPimpl->mProfile->variableInfoObjectString().empty()) {
        if (!res.empty()) {
            res += "\n";
        }

        res += mPimpl->generateVariableInfoObjectCode();
    }

    // Generate code for the information about the variable of integration,
    // states and (other) variables.

    std::string voiInfo = mPimpl->generateVoiInfoCode();

    if (!voiInfo.empty()) {
        if (!res.empty()) {
            res += "\n";
        }

        res += voiInfo;
    }

    std::string stateInfo = mPimpl->generateStateInfoCode();

    if (!stateInfo.empty()) {
        if (!res.empty()) {
            res += "\n";
        }

        res += stateInfo;
    }

    std::string variableInfo = mPimpl->generateVariableInfoCode();

    if (!variableInfo.empty()) {
        if (!res.empty()) {
            res += "\n";
        }

        res += variableInfo;
    }

    // Generate code for extra mathematical functions.

    if (mPimpl->mNeedEqEq && !mPimpl->mProfile->hasEqEqOperator()
        && !mPimpl->mProfile->eqEqFunctionString().empty()) {
        if (!res.empty()) {
            res += "\n";
        }

        res += mPimpl->mProfile->eqEqFunctionString();
    }

    if (mPimpl->mNeedNeq && !mPimpl->mProfile->hasNeqOperator()
        && !mPimpl->mProfile->neqFunctionString().empty()) {
        if (!res.empty()) {
            res += "\n";
        }

        res += mPimpl->mProfile->neqFunctionString();
    }

    if (mPimpl->mNeedLt && !mPimpl->mProfile->hasLtOperator()
        && !mPimpl->mProfile->ltFunctionString().empty()) {
        if (!res.empty()) {
            res += "\n";
        }

        res += mPimpl->mProfile->ltFunctionString();
    }

    if (mPimpl->mNeedLeq && !mPimpl->mProfile->hasLeqOperator()
        && !mPimpl->mProfile->leqFunctionString().empty()) {
        if (!res.empty()) {
            res += "\n";
        }

        res += mPimpl->mProfile->leqFunctionString();
    }

    if (mPimpl->mNeedGt && !mPimpl->mProfile->hasGtOperator()
        && !mPimpl->mProfile->gtFunctionString().empty()) {
        if (!res.empty()) {
            res += "\n";
        }

        res += mPimpl->mProfile->gtFunctionString();
    }

    if (mPimpl->mNeedGeq && !mPimpl->mProfile->hasGeqOperator()
        && !mPimpl->mProfile->geqFunctionString().empty()) {
        if (!res.empty()) {
            res += "\n";
        }

        res += mPimpl->mProfile->geqFunctionString();
    }

    if (mPimpl->mNeedAnd && !mPimpl->mProfile->hasAndOperator()
        && !mPimpl->mProfile->andFunctionString().empty()) {
        if (!res.empty()) {
            res += "\n";
        }

        res += mPimpl->mProfile->andFunctionString();
    }

    if (mPimpl->mNeedOr && !mPimpl->mProfile->hasOrOperator()
        && !mPimpl->mProfile->orFunctionString().empty()) {
        if (!res.empty()) {
            res += "\n";
        }

        res += mPimpl->mProfile->orFunctionString();
    }

    if (mPimpl->mNeedXor && !mPimpl->mProfile->hasXorOperator()
        && !mPimpl->mProfile->xorFunctionString().empty()) {
        if (!res.empty()) {
            res += "\n";
        }

        res += mPimpl->mProfile->xorFunctionString();
    }

    if (mPimpl->mNeedNot && !mPimpl->mProfile->hasNotOperator()
        && !mPimpl->mProfile->notFunctionString().empty()) {
        if (!res.empty()) {
            res += "\n";
        }

        res += mPimpl->mProfile->notFunctionString();
    }

    if (mPimpl->mNeedMin) {
        if (!res.empty()) {
            res += "\n";
        }

        res += mPimpl->mProfile->minFunctionString();
    }

    if (mPimpl->mNeedMax) {
        if (!res.empty()) {
            res += "\n";
        }

        res += mPimpl->mProfile->maxFunctionString();
    }

    if (mPimpl->mNeedSec) {
        if (!res.empty()) {
            res += "\n";
        }

        res += mPimpl->mProfile->secFunctionString();
    }

    if (mPimpl->mNeedCsc) {
        if (!res.empty()) {
            res += "\n";
        }

        res += mPimpl->mProfile->cscFunctionString();
    }

    if (mPimpl->mNeedCot) {
        if (!res.empty()) {
            res += "\n";
        }

        res += mPimpl->mProfile->cotFunctionString();
    }

    if (mPimpl->mNeedSech) {
        if (!res.empty()) {
            res += "\n";
        }

        res += mPimpl->mProfile->sechFunctionString();
    }

    if (mPimpl->mNeedCsch) {
        if (!res.empty()) {
            res += "\n";
        }

        res += mPimpl->mProfile->cschFunctionString();
    }

    if (mPimpl->mNeedCoth) {
        if (!res.empty()) {
            res += "\n";
        }

        res += mPimpl->mProfile->cothFunctionString();
    }

    if (mPimpl->mNeedAsec) {
        if (!res.empty()) {
            res += "\n";
        }

        res += mPimpl->mProfile->asecFunctionString();
    }

    if (mPimpl->mNeedAcsc) {
        if (!res.empty()) {
            res += "\n";
        }

        res += mPimpl->mProfile->acscFunctionString();
    }

    if (mPimpl->mNeedAcot) {
        if (!res.empty()) {
            res += "\n";
        }

        res += mPimpl->mProfile->acotFunctionString();
    }

    if (mPimpl->mNeedAsech) {
        if (!res.empty()) {
            res += "\n";
        }

        res += mPimpl->mProfile->asechFunctionString();
    }

    if (mPimpl->mNeedAcsch) {
        if (!res.empty()) {
            res += "\n";
        }

        res += mPimpl->mProfile->acschFunctionString();
    }

    if (mPimpl->mNeedAcoth) {
        if (!res.empty()) {
            res += "\n";
        }

        res += mPimpl->mProfile->acothFunctionString();
    }

    // Generate code to initialise the model.

    if (!res.empty()) {
        res += "\n";
    }

    std::string methodBody;

    res += mPimpl->mProfile->beginCreateStatesArrayMethodString();

    methodBody = mPimpl->generateCreateArrayCode(mPimpl->mStates.size());
    res += mPimpl->generateMethodBodyCode(methodBody);

    res += mPimpl->mProfile->endCreateStatesArrayMethodString();

    res += "\n";
    res += mPimpl->mProfile->beginCreateVariablesArrayMethodString();

    methodBody = mPimpl->generateCreateArrayCode(mPimpl->mVariables.size());
    res += mPimpl->generateMethodBodyCode(methodBody);

    res += mPimpl->mProfile->endCreateVariablesArrayMethodString();

    if (!mPimpl->mProfile->deleteArrayMethodString().empty()) {
        res += "\n";
        res += mPimpl->mProfile->deleteArrayMethodString();
    }

    res += "\n";
    res += mPimpl->mProfile->beginInitializeConstantsMethodString();

    methodBody = "";

    for (const auto &internalVariable : mPimpl->mInternalVariables) {
        if ((internalVariable->mType == GeneratorInternalVariable::Type::STATE)
            || (internalVariable->mType == GeneratorInternalVariable::Type::CONSTANT)) {
            methodBody += mPimpl->generateInitializationCode(internalVariable);
        }
    }

    std::vector<GeneratorEquationPtr> remainingEquations {std::begin(mPimpl->mEquations), std::end(mPimpl->mEquations)};

    for (const auto &equation : mPimpl->mEquations) {
        if (equation->mType == GeneratorEquation::Type::TRUE_CONSTANT) {
            methodBody += mPimpl->generateEquationCode(equation, remainingEquations);
        }
    }

    res += mPimpl->generateMethodBodyCode(methodBody);
    res += mPimpl->mProfile->endInitializeConstantsMethodString();

    // Generate code to compute our computed constants.

    res += "\n";
    res += mPimpl->mProfile->beginComputeComputedConstantsMethodString();

    methodBody = "";

    for (const auto &equation : mPimpl->mEquations) {
        if (equation->mType == GeneratorEquation::Type::VARIABLE_BASED_CONSTANT) {
            methodBody += mPimpl->generateEquationCode(equation, remainingEquations);
        }
    }

    res += mPimpl->generateMethodBodyCode(methodBody);
    res += mPimpl->mProfile->endComputeComputedConstantsMethodString();

    // Generate code to compute our rates (and any variables on which they
    // depend).

    res += "\n";
    res += mPimpl->mProfile->beginComputeRatesMethodString();

    methodBody = "";

    for (const auto &equation : mPimpl->mEquations) {
        if (equation->mType == GeneratorEquation::Type::RATE) {
            methodBody += mPimpl->generateEquationCode(equation, remainingEquations);
        }
    }

    res += mPimpl->generateMethodBodyCode(methodBody);
    res += mPimpl->mProfile->endComputeRatesMethodString();

    // Generate code to compute our variables.
    // Note: this method computes all the remaining variables, i.e. the ones not
    //       needed to compute our rates, but also the variables that depend on
    //       the value of some states/rates. Indeed, this method is typically
    //       called after having integrated a model, thus ensuring that
    //       variables that rely on the value of some states/rates are fine.

    std::vector<GeneratorEquationPtr> newRemainingEquations {std::begin(mPimpl->mEquations), std::end(mPimpl->mEquations)};

    res += "\n";
    res += mPimpl->mProfile->beginComputeVariablesMethodString();

    methodBody = "";

    for (const auto &equation : mPimpl->mEquations) {
        if ((std::find(remainingEquations.begin(), remainingEquations.end(), equation) != remainingEquations.end())
            || ((equation->mType == GeneratorEquation::Type::ALGEBRAIC)
                && equation->mIsStateRateBased)) {
            methodBody += mPimpl->generateEquationCode(equation, newRemainingEquations, true);
        }
    }

    res += mPimpl->generateMethodBodyCode(methodBody);
    res += mPimpl->mProfile->endComputeVariablesMethodString();

    return res;
}

} // namespace libcellml

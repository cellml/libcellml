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

#include "libcellml/generator.h"

#include <algorithm>
#include <cfloat>
#include <cmath>
#include <limits>
#include <list>
#include <regex>
#include <sstream>
#include <stack>
#include <vector>

#include "libcellml/component.h"
#include "libcellml/generatorprofile.h"
#include "libcellml/model.h"
#include "libcellml/units.h"
#include "libcellml/validator.h"
#include "libcellml/variable.h"
#include "libcellml/version.h"
#include "utilities.h"
#include "xmldoc.h"

#undef NAN

#ifdef __linux__
#    undef TRUE
#    undef FALSE
#endif

namespace libcellml {

static const size_t MAX_SIZE_T = std::numeric_limits<size_t>::max();

/**
 * @brief The GeneratorVariable::GeneratorVariableImpl struct.
 *
 * The private implementation for the GeneratorVariable class.
 */
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

GeneratorVariablePtr GeneratorVariable::create() noexcept
{
    return std::shared_ptr<GeneratorVariable> {new GeneratorVariable {}};
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
    UnitsPtr mUnits = nullptr;

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

/**
 * @brief The Generator::GeneratorImpl struct.
 *
 * The private implementation for the Generator class.
 */
struct Generator::GeneratorImpl
{
    Generator *mGenerator = nullptr;

    Generator::ModelType mModelType = Generator::ModelType::UNKNOWN;

    std::list<GeneratorInternalVariablePtr> mInternalVariables;
    std::list<GeneratorEquationPtr> mEquations;

    VariablePtr mVoi;
    std::vector<VariablePtr> mStates;
    std::vector<GeneratorVariablePtr> mVariables;

    GeneratorProfilePtr mProfile = libcellml::GeneratorProfile::create();

    bool mNeedEq = false;
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
    void processEquationUnits(const GeneratorEquationAstPtr &ast);
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

    bool modifiedProfile() const;

    void addOriginCommentCode(std::string &code);

    void addInterfaceHeaderCode(std::string &code);
    void addImplementationHeaderCode(std::string &code);

    void addVersionAndLibcellmlVersionCode(std::string &code,
                                           bool interface = false);

    void addStateAndVariableCountCode(std::string &code,
                                      bool interface = false);

    void addVariableTypeObjectCode(std::string &code);

    std::string generateVariableInfoObjectCode(const std::string &objectString);

    void addVariableInfoObjectCode(std::string &code);
    void addVariableInfoWithTypeObjectCode(std::string &code);

    std::string generateVariableInfoEntryCode(const std::string &name,
                                              const std::string &units,
                                              const std::string &component);

    void addInterfaceVoiStateAndVariableInfoCode(std::string &code);
    void addImplementationVoiInfoCode(std::string &code);
    void addImplementationStateInfoCode(std::string &code);
    void addImplementationVariableInfoCode(std::string &code);

    void addArithmeticFunctionsCode(std::string &code);
    void addTrigonometricFunctionsCode(std::string &code);

    std::string generateCreateArrayCode(size_t arraySize);

    void addInterfaceCreateDeleteArrayMethodsCode(std::string &code);
    void addImplementationCreateStatesArrayMethodCode(std::string &code);
    void addImplementationCreateVariablesArrayMethodCode(std::string &code);
    void addImplementationDeleteArrayMethodCode(std::string &code);

    std::string generateMethodBodyCode(const std::string &methodBody);

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

    std::string generateInitializationCode(const GeneratorInternalVariablePtr &variable);
    std::string generateEquationCode(const GeneratorEquationPtr &equation,
                                     std::vector<GeneratorEquationPtr> &remainingEquations,
                                     bool onlyStateRateBasedEquations = false);

    void addInterfaceComputeModelMethodsCode(std::string &code);
    void addImplementationInitializeStatesAndConstantsMethodCode(std::string &code,
                                                                 std::vector<GeneratorEquationPtr> &remainingEquations);
    void addImplementationComputeComputedConstantsMethodCode(std::string &code,
                                                             std::vector<GeneratorEquationPtr> &remainingEquations);
    void addImplementationComputeRatesMethodCode(std::string &code,
                                                 std::vector<GeneratorEquationPtr> &remainingEquations);
    void addImplementationComputeVariablesMethodCode(std::string &code,
                                                     std::vector<GeneratorEquationPtr> &remainingEquations);
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
    // not in the MathML namespace.

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
            || variable->hasEquivalentVariable(internalVariable->mVariable, true)) {
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
    // Basic content elements.

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

        // Assignment, and relational and logical operators.

    } else if (node->isMathmlElement("eq")) {
        // This element is used both to describe "a = b" and "a == b". We can
        // distinguish between the two by checking its grand-parent. If it's a
        // "math" element then it means that it is used to describe "a = b"
        // otherwise it is used to describe "a == b". In the former case, there
        // is nothing more we need to do since `ast` is already of
        // GeneratorEquationAst::Type::ASSIGNMENT type.

        if (!node->parent()->parent()->isMathmlElement("math")) {
            ast = std::make_shared<GeneratorEquationAst>(GeneratorEquationAst::Type::EQ, astParent);

            mNeedEq = true;
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

        // Arithmetic operators.

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

        // Calculus elements.

    } else if (node->isMathmlElement("diff")) {
        ast = std::make_shared<GeneratorEquationAst>(GeneratorEquationAst::Type::DIFF, astParent);

        // Trigonometric operators.

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

        // Piecewise statement.

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

        // Token elements.

    } else if (node->isMathmlElement("ci")) {
        std::string variableName = node->firstChild()->convertToString();
        VariablePtr variable = component->variable(variableName);

        if (variable != nullptr) {
            ast = std::make_shared<GeneratorEquationAst>(GeneratorEquationAst::Type::CI, variable, astParent);
            ast->mUnits = variable->units();

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
            std::string modelName = entityName(owningModel(component));
            ErrorPtr err = Error::create();

            err->setDescription("Variable '" + variableName
                                + "' in component '" + component->name()
                                + "' of model '" + modelName
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

        // Checking if the <cn> element has a unit associated with it. If it does, then return the unit name as a string.
        std::string nodeString = node->convertToString();
        std::size_t findUnitPos = nodeString.find("cellml:units");
        if (findUnitPos != std::string::npos) {
            std::string unitName;
            findUnitPos += 14; // Getting to the start of the unit name string, which begins after "cellml:units=\"
            while (nodeString[findUnitPos] != '"') {
                unitName.push_back(nodeString[findUnitPos]);
                ++findUnitPos;
            }

            // We are not allowed to redefine standard units, so if we have a standard unit name we construct the unit.
            if (isStandardUnitName(unitName) && unitName != "dimensionless") {
                UnitsPtr u = libcellml::Units::create();
                u->setName(unitName);
                ast->mUnits = u; // Add the unit to the AST node
            } else {
                ModelPtr model = owningModel(component);
                ast->mUnits = model->units(unitName);
            }
        }

        // Qualifier elements.

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

        // Constants.

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
            ModelPtr model = owningModel(component);
            ComponentPtr trackedVariableComponent = std::dynamic_pointer_cast<Component>(generatorVariable->mVariable->parent());
            ModelPtr trackedVariableModel = owningModel(trackedVariableComponent);
            ErrorPtr err = Error::create();

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
                ComponentPtr component = std::dynamic_pointer_cast<Component>(variable->parent());
                std::string modelName = entityName(owningModel(component));
                ErrorPtr err = Error::create();

                err->setDescription("Variable '" + variable->name()
                                    + "' in component '" + component->name()
                                    + "' of model '" + modelName
                                    + "' cannot be both a variable of integration and initialised.");
                err->setKind(Error::Kind::GENERATOR);

                mGenerator->addError(err);
            } else {
                mVoi = variable;
            }
        } else if ((variable != mVoi)
                   && !variable->hasEquivalentVariable(mVoi, true)) {
            ComponentPtr voiComponent = std::dynamic_pointer_cast<Component>(mVoi->parent());
            ModelPtr voiModel = owningModel(voiComponent);
            ComponentPtr component = std::dynamic_pointer_cast<Component>(variable->parent());
            ModelPtr model = owningModel(component);
            ErrorPtr err = Error::create();

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
            ComponentPtr component = std::dynamic_pointer_cast<Component>(variable->parent());
            ModelPtr model = owningModel(component);
            ErrorPtr err = Error::create();

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

// Functions to determine type of operation on the internal node, which dictates how we treat child unit mappings.
bool isDirectComparisonOperator(const GeneratorEquationAstPtr &ast)
{
    const GeneratorEquationAst::Type type = ast->mType;
    return (type == libcellml::GeneratorEquationAst::Type::ASSIGNMENT)
           || (type == libcellml::GeneratorEquationAst::Type::PLUS)
           || (type == libcellml::GeneratorEquationAst::Type::MINUS)
           || (type == libcellml::GeneratorEquationAst::Type::EQ)
           || (type == libcellml::GeneratorEquationAst::Type::LEQ)
           || (type == libcellml::GeneratorEquationAst::Type::NEQ)
           || (type == libcellml::GeneratorEquationAst::Type::GEQ)
           || (type == libcellml::GeneratorEquationAst::Type::LT)
           || (type == libcellml::GeneratorEquationAst::Type::GT)
           || (type == libcellml::GeneratorEquationAst::Type::MIN)
           || (type == libcellml::GeneratorEquationAst::Type::MAX);
}

bool isMultiplicativeOperator(const GeneratorEquationAstPtr &ast)
{
    const GeneratorEquationAst::Type type = ast->mType;
    return (type == libcellml::GeneratorEquationAst::Type::TIMES)
           || (type == libcellml::GeneratorEquationAst::Type::DIVIDE);
}

bool isExponentOperator(const GeneratorEquationAstPtr &ast)
{
    const GeneratorEquationAst::Type type = ast->mType;
    return (type == libcellml::GeneratorEquationAst::Type::POWER)
           || (type == libcellml::GeneratorEquationAst::Type::ROOT);
}

bool isLogarithmicOperator(const GeneratorEquationAstPtr &ast)
{
    const GeneratorEquationAst::Type type = ast->mType;
    return (type == libcellml::GeneratorEquationAst::Type::LN)
           || (type == libcellml::GeneratorEquationAst::Type::LOG)
           || (type == libcellml::GeneratorEquationAst::Type::EXP);
}

bool isTrigonometricOperator(const GeneratorEquationAstPtr &ast)
{
    const GeneratorEquationAst::Type type = ast->mType;
    return (type == libcellml::GeneratorEquationAst::Type::ASIN)
           || (type == libcellml::GeneratorEquationAst::Type::ASINH)
           || (type == libcellml::GeneratorEquationAst::Type::SIN)
           || (type == libcellml::GeneratorEquationAst::Type::SINH)
           || (type == libcellml::GeneratorEquationAst::Type::ACOS)
           || (type == libcellml::GeneratorEquationAst::Type::ACOSH)
           || (type == libcellml::GeneratorEquationAst::Type::COS)
           || (type == libcellml::GeneratorEquationAst::Type::COSH)
           || (type == libcellml::GeneratorEquationAst::Type::ATAN)
           || (type == libcellml::GeneratorEquationAst::Type::ATANH)
           || (type == libcellml::GeneratorEquationAst::Type::TAN)
           || (type == libcellml::GeneratorEquationAst::Type::TANH)
           || (type == libcellml::GeneratorEquationAst::Type::ASEC)
           || (type == libcellml::GeneratorEquationAst::Type::ASECH)
           || (type == libcellml::GeneratorEquationAst::Type::SECH)
           || (type == libcellml::GeneratorEquationAst::Type::SEC)
           || (type == libcellml::GeneratorEquationAst::Type::ACSC)
           || (type == libcellml::GeneratorEquationAst::Type::ACSCH)
           || (type == libcellml::GeneratorEquationAst::Type::CSC)
           || (type == libcellml::GeneratorEquationAst::Type::CSCH)
           || (type == libcellml::GeneratorEquationAst::Type::ACOT)
           || (type == libcellml::GeneratorEquationAst::Type::ACOTH)
           || (type == libcellml::GeneratorEquationAst::Type::COT)
           || (type == libcellml::GeneratorEquationAst::Type::COTH);
}

bool isDerivativeOperator(const GeneratorEquationAstPtr &ast)
{
    const GeneratorEquationAst::Type type = ast->mType;
    return type == libcellml::GeneratorEquationAst::Type::DIFF;
}

bool isBottomVariableOperator(const GeneratorEquationAstPtr &ast)
{
    const GeneratorEquationAst::Type type = ast->mType;
    return type == libcellml::GeneratorEquationAst::Type::BVAR;
}

// Units mapping declared to implement when checking units for variables
using UnitsMap = std::map<std::string, double>;

// Function which adds the unit mappings together if we have a times or divide operator in the AST.
UnitsMap addMappings(UnitsMap firstMap, const UnitsMap &secondMap, int operation)
{
    for (const auto &unit : secondMap) {
        auto it = firstMap.find(unit.first);
        if (it == firstMap.end()) {
            firstMap.emplace(std::pair<std::string, double>(unit.first, operation * unit.second));
        } else {
            it->second += operation * unit.second;
        }
    }
    return firstMap;
}

// Function which multiplies mappings if we have a power or root operator in the AST.
UnitsMap multiplyMappings(UnitsMap map, const GeneratorEquationAstPtr &ast, double power)
{
    if (ast->mType == libcellml::GeneratorEquationAst::Type::POWER) {
        for (auto &unit : map) {
            unit.second = unit.second * power;
        }
    } else {
        for (auto &unit : map) {
            unit.second = unit.second / power;
        }
    }
    return map;
}

// Helper function to check map equivalences
bool mapsAreEquivalent(const UnitsMap &firstMap, const UnitsMap &secondMap, std::string &hints)
{
    UnitsMap mapping;
    for (const auto &baseUnits : baseUnitsList) {
        mapping[baseUnits] = 0.0;
    }
    for (const auto &unit : firstMap) {
        mapping[unit.first] += unit.second;
    }
    for (const auto &unit : secondMap) {
        mapping[unit.first] -= unit.second;
    }

    // Remove "dimensionless" from base unit testing.
    mapping.erase("dimensionless");
    bool equivalent = true;
    for (const auto &unit : mapping) {
        if (unit.second != 0.0) {
            std::string num = std::to_string(unit.second);
            num.erase(num.find_last_not_of('0') + 1, num.length());
            if (num.back() == '.') {
                num.pop_back();
            }
            hints += unit.first + "^" + num + ", ";
            equivalent = false;
        }
    }

    // Remove the final trailing comma from the hints string.
    if (hints.length() > 2) {
        hints.pop_back();
        hints.back() = '.';
    }
    return equivalent;
}

// Helper function to check dimensionlessness
bool isDimensionless(const UnitsMap &map)
{
    for (const auto &u : map) {
        if (u.second != 0.0) {
            return false;
        }
    }
    return true;
}

void updateBaseUnitCount(const ModelPtr &model,
                         std::map<std::string, double> &unitMap,
                         double &multiplier,
                         const std::string &uName,
                         double uExp, double logMult,
                         int direction)
{
    if (isStandardUnitName(uName)) {
        for (const auto &iter : standardUnitsList.at(uName)) {
            if (unitMap.find(iter.first) == unitMap.end()) {
                unitMap.emplace(std::pair<std::string, double>(iter.first, 0.0));
            }
            unitMap.at(iter.first) += direction * (iter.second * uExp);
        }
        multiplier += direction * logMult;

    } else if (model->hasUnits(uName)) {
        UnitsPtr u = model->units(uName);
        if (!u->isBaseUnit()) {
            std::string ref;
            std::string pre;
            std::string id;
            double exp;
            double mult;
            double expMult;
            for (size_t i = 0; i < u->unitCount(); ++i) {
                u->unitAttributes(i, ref, pre, exp, expMult, id);
                mult = std::log10(expMult);
                if (!isStandardUnitName(ref)) {
                    updateBaseUnitCount(model, unitMap, multiplier, ref, exp * uExp, logMult + mult * uExp + standardPrefixList.at(pre) * uExp, direction);
                } else {
                    for (const auto &iter : standardUnitsList.at(ref)) {
                        if (unitMap.find(iter.first) == unitMap.end()) {
                            unitMap.emplace(std::pair<std::string, double>(iter.first, 0.0));
                        }
                        unitMap.at(iter.first) += direction * (iter.second * exp * uExp);
                    }
                    multiplier += direction * (logMult + (standardMultiplierList.at(ref) + mult + standardPrefixList.at(pre)) * exp);
                }
            }
        }

        // Leaving this as a comment for the moment: This would only be necessary if we had a base unit which was *not* in the standard units list - uncertain if this will ever occur within a formal model.
        /*
        else if (unitMap.find(uName) == unitMap.end()) {
            unitMap.emplace(std::pair<std::string, double>(uName, direction * uExp));
            multiplier += direction * logMult;
        }*/
    }
}

// Grabs a variable associated with the model, so we can return an error message
VariablePtr getVariable(const GeneratorEquationAstPtr &ast)
{
    if (ast->mVariable != nullptr) {
        return ast->mVariable;
    }
    if (ast->mLeft != nullptr) {
        return getVariable(ast->mLeft);
    }
    return nullptr;
}

// Gets the power for a given node. (this needs to be redone so we will always be guaranteed to find the power for an operation)
double getPower(const GeneratorEquationAstPtr &ast)
{
    if (ast == nullptr) {
        return 0; // Return 0 for case where there is a null node
    }
    if (ast->mValue.empty()) {
        // If we have a variable then we return 0 and just make sure both mappings are dimensionless
        if (ast->mLeft == nullptr && ast->mRight == nullptr) {
            return 0;
        }

        if (ast->mType == GeneratorEquationAst::Type::TIMES) {
            return getPower(ast->mLeft) * getPower(ast->mRight);
        }
        if (ast->mType == GeneratorEquationAst::Type::DIVIDE) {
            return getPower(ast->mLeft) / getPower(ast->mRight);
        }
        if (ast->mType == GeneratorEquationAst::Type::PLUS) {
            return getPower(ast->mLeft) + getPower(ast->mRight);
        }
        if (ast->mType == GeneratorEquationAst::Type::MINUS) {
            return getPower(ast->mLeft) - getPower(ast->mRight);
        }
    }

    // In the special case where the terminating node is a variable, eliminates the possibility of making an invalid std::stod call
    if (ast->mValue.empty()) {
        return 0;
    }

    return std::stod(ast->mValue);
}

static const std::map<GeneratorEquationAst::Type, std::string> AstTypeToString = {
    {GeneratorEquationAst::Type::ASSIGNMENT, " = "},
    {GeneratorEquationAst::Type::EQ, " == "},
    {GeneratorEquationAst::Type::NEQ, " != "},
    {GeneratorEquationAst::Type::LT, " < "},
    {GeneratorEquationAst::Type::GT, " > "},
    {GeneratorEquationAst::Type::LEQ, " <= "},
    {GeneratorEquationAst::Type::GEQ, " >= "},
    {GeneratorEquationAst::Type::PLUS, " + "},
    {GeneratorEquationAst::Type::MINUS, " - "},
    {GeneratorEquationAst::Type::AND, " && "},
    {GeneratorEquationAst::Type::OR, " || "},
    {GeneratorEquationAst::Type::XOR, " xor "},
    {GeneratorEquationAst::Type::NOT, " ! "},
    {GeneratorEquationAst::Type::TIMES, " * "},
    {GeneratorEquationAst::Type::DIVIDE, " / "},
    {GeneratorEquationAst::Type::POWER, " pow "},
    {GeneratorEquationAst::Type::ROOT, " root "},
    {GeneratorEquationAst::Type::ABS, " fabs "},
    {GeneratorEquationAst::Type::EXP, " exp "},
    {GeneratorEquationAst::Type::LN, " ln "},
    {GeneratorEquationAst::Type::LOG, " log "},
    {GeneratorEquationAst::Type::CEILING, " ceil "},
    {GeneratorEquationAst::Type::FLOOR, " floor "},
    {GeneratorEquationAst::Type::MIN, " min "},
    {GeneratorEquationAst::Type::MAX, " max "},
    {GeneratorEquationAst::Type::REM, " rem "},
    {GeneratorEquationAst::Type::ASIN, " asin "},
    {GeneratorEquationAst::Type::ASINH, " asinh "},
    {GeneratorEquationAst::Type::SIN, " sin "},
    {GeneratorEquationAst::Type::SINH, " sinh "},
    {GeneratorEquationAst::Type::ACOS, " acos "},
    {GeneratorEquationAst::Type::ACOSH, " acosh "},
    {GeneratorEquationAst::Type::COS, " cos "},
    {GeneratorEquationAst::Type::COSH, " cosh "},
    {GeneratorEquationAst::Type::ATAN, " atan "},
    {GeneratorEquationAst::Type::ATANH, " atanh "},
    {GeneratorEquationAst::Type::TAN, " tan "},
    {GeneratorEquationAst::Type::TANH, " tanh "},
    {GeneratorEquationAst::Type::ASEC, " asec "},
    {GeneratorEquationAst::Type::ASECH, " asech "},
    {GeneratorEquationAst::Type::SECH, " sech "},
    {GeneratorEquationAst::Type::SEC, " sec "},
    {GeneratorEquationAst::Type::ACSC, " acsc "},
    {GeneratorEquationAst::Type::ACSCH, " acsch "},
    {GeneratorEquationAst::Type::CSC, " csc "},
    {GeneratorEquationAst::Type::CSCH, " csch "},
    {GeneratorEquationAst::Type::ACOT, " acot "},
    {GeneratorEquationAst::Type::ACOTH, " acoth "},
    {GeneratorEquationAst::Type::COT, " cot "},
    {GeneratorEquationAst::Type::COTH, " coth "}};

// Get the units in the mapping if we have an incorrect test case.
std::string getHints(const UnitsMap &map)
{
    std::string hints;
    for (const auto &unit : map) {
        if (unit.second != 0.0) {
            std::string num = std::to_string(unit.second);
            num.erase(num.find_last_not_of('0') + 1, num.length());
            if (num.back() == '.') {
                num.pop_back();
            }
            hints += unit.first + "^" + num + ", ";
        }
    }
    if (hints.length() > 2) {
        hints.pop_back();
        hints.back() = '.';
    }
    return hints;
}

UnitsMap processEquationUnitsAst(const GeneratorEquationAstPtr &ast, UnitsMap unitMap, std::vector<std::string> &errors, double &multiplier, int direction)
{
    if (ast != nullptr) {
        if (ast->mLeft == nullptr && ast->mRight == nullptr) {
            ModelPtr model;
            std::string uName;

            // If we have a unit associated with the value of a number we add it to the units mapping.
            if (ast->mType == GeneratorEquationAst::Type::CN && ast->mUnits != nullptr) {
                model = owningModel(ast->mUnits);
                uName = ast->mUnits->name();
                updateBaseUnitCount(model, unitMap, multiplier, uName, 1, 0, direction);
            }

            if (ast->mType == GeneratorEquationAst::Type::CI) {
                model = (ast->mVariable != nullptr) ? owningModel(ast->mVariable) : nullptr;
                uName = (ast->mUnits != nullptr) ? ast->mUnits->name() : "dimensionless";
                if (!(uName == "dimensionless")) {
                    updateBaseUnitCount(model, unitMap, multiplier, uName, 1, 0, direction);
                }
            }
            return unitMap;
        }

        // We know if we have reached an internal vertex that we have a mathematical operation as it's type.
        if (ast->mLeft != nullptr || ast->mRight != nullptr) {
            // Evaluate left, right subtrees first
            UnitsMap leftMap = processEquationUnitsAst(ast->mLeft, unitMap, errors, multiplier, 1);
            UnitsMap rightMap = processEquationUnitsAst(ast->mRight, unitMap, errors, multiplier, 1);

            // Plus, Minus, any unit comparisons where units have to be exactly the same.
            if (isDirectComparisonOperator(ast)) {
                std::string hints;
                if (!(mapsAreEquivalent(leftMap, rightMap, hints) || rightMap.empty())) {
                    //return leftMap;
                    VariablePtr variable = getVariable(ast);
                    ComponentPtr component = (variable != nullptr) ? std::dynamic_pointer_cast<Component>(variable->parent()) : nullptr;
                    ModelPtr model = (component != nullptr) ? owningModel(component) : nullptr;
                    std::string compName = (component != nullptr) ? component->name() : "";
                    std::string modelName = (model != nullptr) ? model->name() : "";

                    std::string err = "The units in the expression '" + AstTypeToString.find(ast->mType)->second
                                      + "' in component '" + compName
                                      + "' of model '" + modelName
                                      + "' are not equivalent. The unit mismatch is " + hints;
                    errors.push_back(err);
                }
            }

            // Multiply, Divide: add mappings, no interest in unit compatibility.
            if (isMultiplicativeOperator(ast)) {
                UnitsMap newMapping;
                if (ast->mType == GeneratorEquationAst::Type::TIMES) {
                    newMapping = addMappings(leftMap, rightMap, 1);
                } else {
                    newMapping = addMappings(leftMap, rightMap, -1);
                }
                return newMapping;
            }

            // Checks for exponential operators, multiplies unit mappings with power
            if (isExponentOperator(ast)) {
                double power = getPower(ast->mRight);
                bool correctUnits = false;
                if (power == 0.0 && ast->mRight != nullptr) {
                    correctUnits = isDimensionless(leftMap) && isDimensionless(rightMap); // If we have a variable as our power both the power and the quantity it is being applied to must be dimensionless
                } else {
                    correctUnits = isDimensionless(rightMap); // Otherwise we just check the power for dimensionlessness
                }

                // If we have a sqaure root operation
                if (power == 0.0 && ast->mRight == nullptr) {
                    power = 2.0;
                }

                // Otherwise, for a non-dimensionless case, we return what the units are in the expression.
                if (!correctUnits) {
                    std::string hints = getHints(rightMap);
                    VariablePtr variable = getVariable(ast);
                    ComponentPtr component = (variable != nullptr) ? std::dynamic_pointer_cast<Component>(variable->parent()) : nullptr;
                    ModelPtr model = (component != nullptr) ? owningModel(component) : nullptr;
                    std::string compName = (component != nullptr) ? component->name() : "";
                    std::string modelName = (model != nullptr) ? model->name() : "";

                    std::string err = "The units in the expression '" + AstTypeToString.find(ast->mType)->second
                                      + "' in component '" + compName
                                      + "' of model '" + modelName
                                      + "' are not dimensionless. The units in the expression are " + hints;
                    errors.push_back(err);
                }
                return multiplyMappings(leftMap, ast, power); // Reduce potential for errors as we continue to traverse up the tree
            }

            // Check logarithms to ensure we have the same base and units inside the logarithmic expression, or both are dimensionless.
            if (isLogarithmicOperator(ast)) {
                std::string hints;
                if (!mapsAreEquivalent(rightMap, leftMap, hints)) {
                    VariablePtr variable = getVariable(ast);
                    ComponentPtr component = (variable != nullptr) ? std::dynamic_pointer_cast<Component>(variable->parent()) : nullptr;
                    ModelPtr model = (component != nullptr) ? owningModel(component) : nullptr;
                    std::string compName = (component != nullptr) ? component->name() : "";
                    std::string modelName = (model != nullptr) ? model->name() : "";

                    std::string err = "The units in the argument of '" + AstTypeToString.find(ast->mType)->second
                                      + "' in component '" + compName
                                      + "' of model '" + modelName
                                      + "' are not consistent with the base. The mismatch is: " + hints;
                    errors.push_back(err);
                }
                rightMap.clear();
                return rightMap;
            }

            // All trig arguments should be dimensionless
            if (isTrigonometricOperator(ast)) {
                if (!isDimensionless(leftMap)) {
                    std::string hints = getHints(leftMap);
                    VariablePtr variable = getVariable(ast);
                    ComponentPtr component = (variable != nullptr) ? std::dynamic_pointer_cast<Component>(variable->parent()) : nullptr;
                    ModelPtr model = (component != nullptr) ? owningModel(component) : nullptr;
                    std::string compName = (component != nullptr) ? component->name() : "";
                    std::string modelName = (model != nullptr) ? model->name() : "";

                    std::string err = "The argument in the expression '" + AstTypeToString.find(ast->mType)->second
                                      + "' in component '" + compName
                                      + "' of model '" + modelName
                                      + "' is not dimensionless. The units in the argument are: " + hints;
                    errors.push_back(err);
                    leftMap.clear(); // Clear our mapping to reduce the potential for errors further up the tree.
                }
            }

            if (isDerivativeOperator(ast)) {
                return addMappings(leftMap, rightMap, 1);
            }

            if (isBottomVariableOperator(ast)) {
                for (auto &unit : leftMap) {
                    unit.second *= -1.0; // Bottom variable will be "per" the unit on the top
                }
            }
            return leftMap;
        }
    }
    return unitMap;
}

double processEquationMultiplierAst(const GeneratorEquationAstPtr &ast, std::vector<std::string> &errors, double &multiplier, int direction)
{
    if (ast != nullptr) {
        // Evaluate multiplier if we are at a variable
        if (ast->mLeft == nullptr && ast->mRight == nullptr) {
            ModelPtr model;
            std::string uName;
            UnitsMap unitMap;

            // If we have a unit associated with the value of a number we add it to the units mapping.
            if (ast->mType == GeneratorEquationAst::Type::CN && ast->mUnits != nullptr) {
                model = owningModel(ast->mUnits);
                uName = ast->mUnits->name();
                updateBaseUnitCount(model, unitMap, multiplier, uName, 1, 0, direction);
            }

            if (ast->mType == GeneratorEquationAst::Type::CI) {
                model = (ast->mVariable != nullptr) ? owningModel(ast->mVariable) : nullptr;
                uName = (ast->mUnits != nullptr) ? ast->mUnits->name() : "dimensionless";
                if (!(uName == "dimensionless")) {
                    updateBaseUnitCount(model, unitMap, multiplier, uName, 1, 0, direction);
                }
            }
            return multiplier;
        }

        // We know if we have reached an internal vertex that we have a mathematical operation as it's type.
        if (ast->mLeft != nullptr || ast->mRight != nullptr) {
            // Evaluate left, right subtrees first
            double leftMult = processEquationMultiplierAst(ast->mLeft, errors, multiplier, 1);
            double rightMult = processEquationMultiplierAst(ast->mRight, errors, multiplier, 1);

            // The only time we check multiplier mismatch is in a comparision operation.
            if (isDirectComparisonOperator(ast)) {
                if (leftMult != rightMult) {
                    
                    VariablePtr variable = getVariable(ast);
                    ComponentPtr component = (variable != nullptr) ? std::dynamic_pointer_cast<Component>(variable->parent()) : nullptr;
                    ModelPtr model = (component != nullptr) ? owningModel(component) : nullptr;
                    std::string compName = (component != nullptr) ? component->name() : "";
                    std::string modelName = (model != nullptr) ? model->name() : "";

                    std::string err = "The argument in the expression '" + AstTypeToString.find(ast->mType)->second
                                      + "' in component '" + compName
                                      + "' of model '" + modelName
                                      + "' has a multiplier mismatch. The mismatch is: " + std::to_string(leftMult-rightMult);
                    errors.push_back(err);
                    multiplier = leftMult;
                }
            }

            // Otherwise for all the other cases we change the multiplier
            if (isMultiplicativeOperator(ast)) {
            }

            if (isExponentOperator(ast)) {
            }

            if (isLogarithmicOperator(ast)) {
            }

            if (isTrigonometricOperator(ast)) {
            }

            if (isDerivativeOperator(ast)) {
                //leftMult = leftm
            }

            if (isBottomVariableOperator(ast)) {
                //leftMult = 1.0 / leftMult;
            }
        }
        return multiplier
    }
    return 1.0;
}

// Shim function to create a contiguous void declaration in the private implementation
void Generator::GeneratorImpl::processEquationUnits(const GeneratorEquationAstPtr &ast)
{
    UnitsMap unitMap;
    std::vector<std::string> errors;
    double multiplier = 0.0;
    unitMap = processEquationUnitsAst(ast, unitMap, errors, multiplier, 0);

    // We only check for multiplier issues if we don't have any issues with units.
    if (!errors.empty()) {
        multiplier = processEquationMultiplierAst(ast, errors, multiplier, 0);
    }

    if (!errors.empty()) {
        for (const auto &error : errors) {
            ErrorPtr err = Error::create();
            err->setDescription(error);
            err->setKind(Error::Kind::UNITS);
            mGenerator->addError(err);
        }
    }
}

bool Generator::GeneratorImpl::compareVariablesByName(const GeneratorInternalVariablePtr &variable1,
                                                      const GeneratorInternalVariablePtr &variable2)
{
    // TODO: we can't currently instatiate imports, which means that we can't
    //       have variables in different models. This also means that we can't
    //       have code to check for the name of a model since this would fail
    //       coverage test. So, once we can instantiate imports, we will need to
    //       account for the name of a model.
    VariablePtr realVariable1 = variable1->mVariable;
    VariablePtr realVariable2 = variable2->mVariable;
    ComponentPtr realComponent1 = std::dynamic_pointer_cast<Component>(realVariable1->parent());
    ComponentPtr realComponent2 = std::dynamic_pointer_cast<Component>(realVariable2->parent());

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

    mGenerator->removeAllErrors();

    // Recursively process the model's components, so that we end up with an AST
    // for each of the model's equations.

    for (size_t i = 0; i < model->componentCount(); ++i) {
        processComponent(model->component(i));
    }

    // Process our different equations' AST to determine the type of our
    // variables.

    if (mGenerator->errorCount() == 0) {
        for (const auto &equation : mEquations) {
            processEquationAst(equation->mAst);
        }
    }

    if (mGenerator->errorCount() == 0) {
        for (const auto &equation : mEquations) {
            processEquationUnits(equation->mAst);
        }
    }

    // Sort our variables, determine the index of our constant variables and
    // then loop over our equations, checking which variables, if any, can be
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

    // Make sure that our variables are valid.

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
                ErrorPtr err = Error::create();
                VariablePtr realVariable = internalVariable->mVariable;
                ComponentPtr realComponent = std::dynamic_pointer_cast<Component>(realVariable->parent());
                ModelPtr realModel = owningModel(realComponent);

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
                GeneratorVariablePtr variable = GeneratorVariable::create();

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
    return ((ast->mType == GeneratorEquationAst::Type::EQ)
            && mProfile->hasEqOperator())
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

    return (index == std::string::npos) ?
               string :
               string.replace(index, from.length(), to);
}

void Generator::GeneratorImpl::updateVariableInfoSizes(size_t &componentSize,
                                                       size_t &nameSize,
                                                       size_t &unitsSize,
                                                       const VariablePtr &variable)
{
    auto variableComponentSize = entityName(variable->parent()).length() + 1;
    auto variableNameSize = variable->name().length() + 1;
    auto variableUnitsSize = variable->units()->name().length() + 1;
    // Note: +1 to account for the end of string termination.

    componentSize = (componentSize > variableComponentSize) ? componentSize : variableComponentSize;
    nameSize = (nameSize > variableNameSize) ? nameSize : variableNameSize;
    unitsSize = (unitsSize > variableUnitsSize) ? unitsSize : variableUnitsSize;
}

bool Generator::GeneratorImpl::modifiedProfile() const
{
    // Whether the profile requires an interface to be generated.

    const std::string trueValue = "true";
    const std::string falseValue = "false";

    std::string profileContents = mProfile->hasInterface() ?
                                      trueValue :
                                      falseValue;

    // Assignment.

    profileContents += mProfile->assignmentString();

    // Relational and logical operators.

    profileContents += mProfile->eqString()
                       + mProfile->neqString()
                       + mProfile->ltString()
                       + mProfile->leqString()
                       + mProfile->gtString()
                       + mProfile->geqString()
                       + mProfile->andString()
                       + mProfile->orString()
                       + mProfile->xorString()
                       + mProfile->notString();

    profileContents += (mProfile->hasEqOperator() ?
                            trueValue :
                            falseValue)
                       + (mProfile->hasNeqOperator() ?
                              trueValue :
                              falseValue)
                       + (mProfile->hasLtOperator() ?
                              trueValue :
                              falseValue)
                       + (mProfile->hasLeqOperator() ?
                              trueValue :
                              falseValue)
                       + (mProfile->hasGtOperator() ?
                              trueValue :
                              falseValue)
                       + (mProfile->hasGeqOperator() ?
                              trueValue :
                              falseValue)
                       + (mProfile->hasAndOperator() ?
                              trueValue :
                              falseValue)
                       + (mProfile->hasOrOperator() ?
                              trueValue :
                              falseValue)
                       + (mProfile->hasXorOperator() ?
                              trueValue :
                              falseValue)
                       + (mProfile->hasNotOperator() ?
                              trueValue :
                              falseValue);

    // Arithmetic operators.

    profileContents += mProfile->plusString()
                       + mProfile->minusString()
                       + mProfile->timesString()
                       + mProfile->divideString()
                       + mProfile->powerString()
                       + mProfile->squareRootString()
                       + mProfile->squareString()
                       + mProfile->absoluteValueString()
                       + mProfile->exponentialString()
                       + mProfile->napierianLogarithmString()
                       + mProfile->commonLogarithmString()
                       + mProfile->ceilingString()
                       + mProfile->floorString()
                       + mProfile->minString()
                       + mProfile->maxString()
                       + mProfile->remString();

    profileContents += mProfile->hasPowerOperator() ?
                           trueValue :
                           falseValue;

    // Trigonometric operators.

    profileContents += mProfile->sinString()
                       + mProfile->cosString()
                       + mProfile->tanString()
                       + mProfile->secString()
                       + mProfile->cscString()
                       + mProfile->cotString()
                       + mProfile->sinhString()
                       + mProfile->coshString()
                       + mProfile->tanhString()
                       + mProfile->sechString()
                       + mProfile->cschString()
                       + mProfile->cothString()
                       + mProfile->asinString()
                       + mProfile->acosString()
                       + mProfile->atanString()
                       + mProfile->asecString()
                       + mProfile->acscString()
                       + mProfile->acotString()
                       + mProfile->asinhString()
                       + mProfile->acoshString()
                       + mProfile->atanhString()
                       + mProfile->asechString()
                       + mProfile->acschString()
                       + mProfile->acothString();

    // Piecewise statement.

    profileContents += mProfile->conditionalOperatorIfString()
                       + mProfile->conditionalOperatorElseString()
                       + mProfile->piecewiseIfString()
                       + mProfile->piecewiseElseString();

    profileContents += mProfile->hasConditionalOperator() ?
                           trueValue :
                           falseValue;

    // Constants.

    profileContents += mProfile->trueString()
                       + mProfile->falseString()
                       + mProfile->eString()
                       + mProfile->piString()
                       + mProfile->infString()
                       + mProfile->nanString();

    // Arithmetic functions.

    profileContents += mProfile->eqFunctionString()
                       + mProfile->neqFunctionString()
                       + mProfile->ltFunctionString()
                       + mProfile->leqFunctionString()
                       + mProfile->gtFunctionString()
                       + mProfile->geqFunctionString()
                       + mProfile->andFunctionString()
                       + mProfile->orFunctionString()
                       + mProfile->xorFunctionString()
                       + mProfile->notFunctionString()
                       + mProfile->minFunctionString()
                       + mProfile->maxFunctionString();

    // Trigonometric functions.

    profileContents += mProfile->secFunctionString()
                       + mProfile->cscFunctionString()
                       + mProfile->cotFunctionString()
                       + mProfile->sechFunctionString()
                       + mProfile->cschFunctionString()
                       + mProfile->cothFunctionString()
                       + mProfile->asecFunctionString()
                       + mProfile->acscFunctionString()
                       + mProfile->acotFunctionString()
                       + mProfile->asechFunctionString()
                       + mProfile->acschFunctionString()
                       + mProfile->acothFunctionString();

    // Miscellaneous.

    profileContents += mProfile->commentString()
                       + mProfile->originCommentString();

    profileContents += mProfile->interfaceFileNameString();

    profileContents += mProfile->interfaceHeaderString()
                       + mProfile->implementationHeaderString();

    profileContents += mProfile->interfaceVersionString()
                       + mProfile->implementationVersionString();

    profileContents += mProfile->interfaceLibcellmlVersionString()
                       + mProfile->implementationLibcellmlVersionString();

    profileContents += mProfile->interfaceStateCountString()
                       + mProfile->implementationStateCountString();

    profileContents += mProfile->interfaceVariableCountString()
                       + mProfile->implementationVariableCountString();

    profileContents += mProfile->variableTypeObjectString();

    profileContents += mProfile->constantVariableTypeString()
                       + mProfile->computedConstantVariableTypeString()
                       + mProfile->algebraicVariableTypeString();

    profileContents += mProfile->variableInfoObjectString()
                       + mProfile->variableInfoWithTypeObjectString();

    profileContents += mProfile->interfaceVoiInfoString()
                       + mProfile->implementationVoiInfoString();

    profileContents += mProfile->interfaceStateInfoString()
                       + mProfile->implementationStateInfoString();

    profileContents += mProfile->interfaceVariableInfoString()
                       + mProfile->implementationVariableInfoString();

    profileContents += mProfile->variableInfoEntryString()
                       + mProfile->variableInfoWithTypeEntryString();

    profileContents += mProfile->voiString();

    profileContents += mProfile->statesArrayString()
                       + mProfile->ratesArrayString()
                       + mProfile->variablesArrayString();

    profileContents += mProfile->returnCreatedArrayString();

    profileContents += mProfile->interfaceCreateStatesArrayMethodString()
                       + mProfile->implementationCreateStatesArrayMethodString();

    profileContents += mProfile->interfaceCreateVariablesArrayMethodString()
                       + mProfile->implementationCreateVariablesArrayMethodString();

    profileContents += mProfile->interfaceDeleteArrayMethodString()
                       + mProfile->implementationDeleteArrayMethodString();

    profileContents += mProfile->interfaceInitializeStatesAndConstantsMethodString()
                       + mProfile->implementationInitializeStatesAndConstantsMethodString();

    profileContents += mProfile->interfaceComputeComputedConstantsMethodString()
                       + mProfile->implementationComputeComputedConstantsMethodString();

    profileContents += mProfile->interfaceComputeRatesMethodString()
                       + mProfile->implementationComputeRatesMethodString();

    profileContents += mProfile->interfaceComputeVariablesMethodString()
                       + mProfile->implementationComputeVariablesMethodString();

    profileContents += mProfile->emptyMethodString();

    profileContents += mProfile->indentString();

    profileContents += mProfile->openArrayInitializerString()
                       + mProfile->closeArrayInitializerString();

    profileContents += mProfile->openArrayString()
                       + mProfile->closeArrayString();

    profileContents += mProfile->arrayElementSeparatorString();

    profileContents += mProfile->stringDelimiterString();

    profileContents += mProfile->commandSeparatorString();

    // Compute and check the hash of our profile contents.

    bool res = false;
    std::string profileContentsSha1 = sha1(profileContents);

    switch (mProfile->profile()) {
    case GeneratorProfile::Profile::C:
        res = profileContentsSha1 != "e387c94ec0debf68566379f214c250a28907e90c";

        break;
    case GeneratorProfile::Profile::PYTHON:
        res = profileContentsSha1 != "42d407f85ab07649516b55f7c626553034f892a9";

        break;
    }

    return res;
}

void Generator::GeneratorImpl::addOriginCommentCode(std::string &code)
{
    if (!mProfile->commentString().empty()
        && !mProfile->originCommentString().empty()) {
        std::string profileInformation = modifiedProfile() ?
                                             "a modified " :
                                             "the ";

        switch (mProfile->profile()) {
        case GeneratorProfile::Profile::C:
            profileInformation += "C";

            break;
        case GeneratorProfile::Profile::PYTHON:
            profileInformation += "Python";

            break;
        }

        profileInformation += " profile of";

        std::string commentCode = replace(replace(mProfile->originCommentString(),
                                                  "<PROFILE_INFORMATION>", profileInformation),
                                          "<LIBCELLML_VERSION>", versionString());

        code += replace(mProfile->commentString(),
                        "<CODE>", commentCode);
    }
}

void Generator::GeneratorImpl::addInterfaceHeaderCode(std::string &code)
{
    if (!mProfile->interfaceHeaderString().empty()) {
        if (!code.empty()) {
            code += "\n";
        }

        code += mProfile->interfaceHeaderString();
    }
}

void Generator::GeneratorImpl::addImplementationHeaderCode(std::string &code)
{
    if (!mProfile->implementationHeaderString().empty()) {
        if (!code.empty()) {
            code += "\n";
        }

        code += replace(mProfile->implementationHeaderString(),
                        "<INTERFACE_FILE_NAME>", mProfile->interfaceFileNameString());
    }
}

void Generator::GeneratorImpl::addVersionAndLibcellmlVersionCode(std::string &code,
                                                                 bool interface)
{
    std::string versionAndLibcellmlCode;

    if ((interface && !mProfile->interfaceVersionString().empty())
        || (!interface && !mProfile->implementationVersionString().empty())) {
        if (interface) {
            versionAndLibcellmlCode += mProfile->interfaceVersionString();
        } else {
            if (modifiedProfile()) {
                std::regex regEx("([0-9]+\\.[0-9]+\\.[0-9]+)");

                versionAndLibcellmlCode += std::regex_replace(mProfile->implementationVersionString(), regEx, "$1.post0");
            } else {
                versionAndLibcellmlCode += mProfile->implementationVersionString();
            }
        }
    }

    if ((interface && !mProfile->interfaceLibcellmlVersionString().empty())
        || (!interface && !mProfile->implementationLibcellmlVersionString().empty())) {
        versionAndLibcellmlCode += interface ?
                                       mProfile->interfaceLibcellmlVersionString() :
                                       replace(mProfile->implementationLibcellmlVersionString(),
                                               "<LIBCELLML_VERSION>", versionString());
    }

    if (!versionAndLibcellmlCode.empty()) {
        code += "\n";
    }

    code += versionAndLibcellmlCode;
}

void Generator::GeneratorImpl::addStateAndVariableCountCode(std::string &code,
                                                            bool interface)
{
    std::string stateAndVariableCountCode;

    if ((interface && !mProfile->interfaceStateCountString().empty())
        || (!interface && !mProfile->implementationStateCountString().empty())) {
        stateAndVariableCountCode += interface ?
                                         mProfile->interfaceStateCountString() :
                                         replace(mProfile->implementationStateCountString(),
                                                 "<STATE_COUNT>", std::to_string(mStates.size()));
    }

    if ((interface && !mProfile->interfaceVariableCountString().empty())
        || (!interface && !mProfile->implementationVariableCountString().empty())) {
        stateAndVariableCountCode += interface ?
                                         mProfile->interfaceVariableCountString() :
                                         replace(mProfile->implementationVariableCountString(),
                                                 "<VARIABLE_COUNT>", std::to_string(mVariables.size()));
    }

    if (!stateAndVariableCountCode.empty()) {
        code += "\n";
    }

    code += stateAndVariableCountCode;
}

void Generator::GeneratorImpl::addVariableTypeObjectCode(std::string &code)
{
    if (!mProfile->variableTypeObjectString().empty()) {
        if (!code.empty()) {
            code += "\n";
        }

        code += mProfile->variableTypeObjectString();
    }
}

std::string Generator::GeneratorImpl::generateVariableInfoObjectCode(const std::string &objectString)
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

    return replace(replace(replace(objectString,
                                   "<COMPONENT_SIZE>", std::to_string(componentSize)),
                           "<NAME_SIZE>", std::to_string(nameSize)),
                   "<UNITS_SIZE>", std::to_string(unitsSize));
}

void Generator::GeneratorImpl::addVariableInfoObjectCode(std::string &code)
{
    if (!mProfile->variableInfoObjectString().empty()) {
        if (!code.empty()) {
            code += "\n";
        }

        code += generateVariableInfoObjectCode(mProfile->variableInfoObjectString());
    }
}

void Generator::GeneratorImpl::addVariableInfoWithTypeObjectCode(std::string &code)
{
    if (!mProfile->variableInfoWithTypeObjectString().empty()) {
        if (!code.empty()) {
            code += "\n";
        }

        code += generateVariableInfoObjectCode(mProfile->variableInfoWithTypeObjectString());
    }
}

std::string Generator::GeneratorImpl::generateVariableInfoEntryCode(const std::string &name,
                                                                    const std::string &units,
                                                                    const std::string &component)
{
    return replace(replace(replace(mProfile->variableInfoEntryString(),
                                   "<NAME>", name),
                           "<UNITS>", units),
                   "<COMPONENT>", component);
}

void Generator::GeneratorImpl::addInterfaceVoiStateAndVariableInfoCode(std::string &code)
{
    std::string interfaceVoiStateAndVariableInfoCode;

    if (!mProfile->interfaceVoiInfoString().empty()) {
        interfaceVoiStateAndVariableInfoCode += mProfile->interfaceVoiInfoString();
    }

    if (!mProfile->interfaceStateInfoString().empty()) {
        interfaceVoiStateAndVariableInfoCode += mProfile->interfaceStateInfoString();
    }

    if (!mProfile->interfaceVariableInfoString().empty()) {
        interfaceVoiStateAndVariableInfoCode += mProfile->interfaceVariableInfoString();
    }

    if (!interfaceVoiStateAndVariableInfoCode.empty()) {
        code += "\n";
    }

    code += interfaceVoiStateAndVariableInfoCode;
}

void Generator::GeneratorImpl::addImplementationVoiInfoCode(std::string &code)
{
    if (!mProfile->implementationVoiInfoString().empty()
        && !mProfile->variableInfoEntryString().empty()) {
        if (!code.empty()) {
            code += "\n";
        }

        std::string name = (mVoi != nullptr) ? mVoi->name() : "";
        std::string units = (mVoi != nullptr) ? mVoi->units()->name() : "";
        std::string component = (mVoi != nullptr) ? entityName(mVoi->parent()) : "";

        code += replace(mProfile->implementationVoiInfoString(),
                        "<CODE>", generateVariableInfoEntryCode(name, units, component));
    }
}

void Generator::GeneratorImpl::addImplementationStateInfoCode(std::string &code)
{
    if (!mProfile->implementationStateInfoString().empty()
        && !mProfile->variableInfoEntryString().empty()
        && !mProfile->arrayElementSeparatorString().empty()) {
        if (!code.empty()) {
            code += "\n";
        }

        std::string infoElementsCode;

        for (const auto &state : mStates) {
            if (!infoElementsCode.empty()) {
                infoElementsCode += mProfile->arrayElementSeparatorString() + "\n";
            }

            infoElementsCode += mProfile->indentString()
                                + generateVariableInfoEntryCode(state->name(),
                                                                state->units()->name(),
                                                                entityName(state->parent()));
        }

        if (!infoElementsCode.empty()) {
            infoElementsCode += "\n";
        }

        code += replace(mProfile->implementationStateInfoString(),
                        "<CODE>", infoElementsCode);
    }
}

void Generator::GeneratorImpl::addImplementationVariableInfoCode(std::string &code)
{
    if (!mProfile->implementationVariableInfoString().empty()
        && !mProfile->variableInfoWithTypeEntryString().empty()
        && !mProfile->arrayElementSeparatorString().empty()
        && !mProfile->constantVariableTypeString().empty()
        && !mProfile->computedConstantVariableTypeString().empty()
        && !mProfile->algebraicVariableTypeString().empty()) {
        if (!code.empty()) {
            code += "\n";
        }

        std::string infoElementsCode;

        for (const auto &variable : mVariables) {
            if (!infoElementsCode.empty()) {
                infoElementsCode += mProfile->arrayElementSeparatorString() + "\n";
            }

            std::string variableType;

            switch (variable->type()) {
            case GeneratorVariable::Type::CONSTANT:
                variableType = mProfile->constantVariableTypeString();

                break;
            case GeneratorVariable::Type::COMPUTED_CONSTANT:
                variableType = mProfile->computedConstantVariableTypeString();

                break;
            case GeneratorVariable::Type::ALGEBRAIC:
                variableType = mProfile->algebraicVariableTypeString();

                break;
            }

            infoElementsCode += mProfile->indentString()
                                + replace(replace(replace(replace(mProfile->variableInfoWithTypeEntryString(),
                                                                  "<NAME>", variable->variable()->name()),
                                                          "<UNITS>", variable->variable()->units()->name()),
                                                  "<COMPONENT>", entityName(variable->variable()->parent())),
                                          "<TYPE>", variableType);
        }

        if (!infoElementsCode.empty()) {
            infoElementsCode += "\n";
        }

        code += replace(mProfile->implementationVariableInfoString(),
                        "<CODE>", infoElementsCode);
    }
}

void Generator::GeneratorImpl::addArithmeticFunctionsCode(std::string &code)
{
    if (mNeedEq && !mProfile->hasEqOperator()
        && !mProfile->eqFunctionString().empty()) {
        if (!code.empty()) {
            code += "\n";
        }

        code += mProfile->eqFunctionString();
    }

    if (mNeedNeq && !mProfile->hasNeqOperator()
        && !mProfile->neqFunctionString().empty()) {
        if (!code.empty()) {
            code += "\n";
        }

        code += mProfile->neqFunctionString();
    }

    if (mNeedLt && !mProfile->hasLtOperator()
        && !mProfile->ltFunctionString().empty()) {
        if (!code.empty()) {
            code += "\n";
        }

        code += mProfile->ltFunctionString();
    }

    if (mNeedLeq && !mProfile->hasLeqOperator()
        && !mProfile->leqFunctionString().empty()) {
        if (!code.empty()) {
            code += "\n";
        }

        code += mProfile->leqFunctionString();
    }

    if (mNeedGt && !mProfile->hasGtOperator()
        && !mProfile->gtFunctionString().empty()) {
        if (!code.empty()) {
            code += "\n";
        }

        code += mProfile->gtFunctionString();
    }

    if (mNeedGeq && !mProfile->hasGeqOperator()
        && !mProfile->geqFunctionString().empty()) {
        if (!code.empty()) {
            code += "\n";
        }

        code += mProfile->geqFunctionString();
    }

    if (mNeedAnd && !mProfile->hasAndOperator()
        && !mProfile->andFunctionString().empty()) {
        if (!code.empty()) {
            code += "\n";
        }

        code += mProfile->andFunctionString();
    }

    if (mNeedOr && !mProfile->hasOrOperator()
        && !mProfile->orFunctionString().empty()) {
        if (!code.empty()) {
            code += "\n";
        }

        code += mProfile->orFunctionString();
    }

    if (mNeedXor && !mProfile->hasXorOperator()
        && !mProfile->xorFunctionString().empty()) {
        if (!code.empty()) {
            code += "\n";
        }

        code += mProfile->xorFunctionString();
    }

    if (mNeedNot && !mProfile->hasNotOperator()
        && !mProfile->notFunctionString().empty()) {
        if (!code.empty()) {
            code += "\n";
        }

        code += mProfile->notFunctionString();
    }

    if (mNeedMin
        && !mProfile->minFunctionString().empty()) {
        if (!code.empty()) {
            code += "\n";
        }

        code += mProfile->minFunctionString();
    }

    if (mNeedMax
        && !mProfile->maxFunctionString().empty()) {
        if (!code.empty()) {
            code += "\n";
        }

        code += mProfile->maxFunctionString();
    }
}

void Generator::GeneratorImpl::addTrigonometricFunctionsCode(std::string &code)
{
    if (mNeedSec
        && !mProfile->secFunctionString().empty()) {
        if (!code.empty()) {
            code += "\n";
        }

        code += mProfile->secFunctionString();
    }

    if (mNeedCsc
        && !mProfile->cscFunctionString().empty()) {
        if (!code.empty()) {
            code += "\n";
        }

        code += mProfile->cscFunctionString();
    }

    if (mNeedCot
        && !mProfile->cotFunctionString().empty()) {
        if (!code.empty()) {
            code += "\n";
        }

        code += mProfile->cotFunctionString();
    }

    if (mNeedSech
        && !mProfile->sechFunctionString().empty()) {
        if (!code.empty()) {
            code += "\n";
        }

        code += mProfile->sechFunctionString();
    }

    if (mNeedCsch
        && !mProfile->cschFunctionString().empty()) {
        if (!code.empty()) {
            code += "\n";
        }

        code += mProfile->cschFunctionString();
    }

    if (mNeedCoth
        && !mProfile->cothFunctionString().empty()) {
        if (!code.empty()) {
            code += "\n";
        }

        code += mProfile->cothFunctionString();
    }

    if (mNeedAsec
        && !mProfile->asecFunctionString().empty()) {
        if (!code.empty()) {
            code += "\n";
        }

        code += mProfile->asecFunctionString();
    }

    if (mNeedAcsc
        && !mProfile->acscFunctionString().empty()) {
        if (!code.empty()) {
            code += "\n";
        }

        code += mProfile->acscFunctionString();
    }

    if (mNeedAcot
        && !mProfile->acotFunctionString().empty()) {
        if (!code.empty()) {
            code += "\n";
        }

        code += mProfile->acotFunctionString();
    }

    if (mNeedAsech
        && !mProfile->asechFunctionString().empty()) {
        if (!code.empty()) {
            code += "\n";
        }

        code += mProfile->asechFunctionString();
    }

    if (mNeedAcsch
        && !mProfile->acschFunctionString().empty()) {
        if (!code.empty()) {
            code += "\n";
        }

        code += mProfile->acschFunctionString();
    }

    if (mNeedAcoth
        && !mProfile->acothFunctionString().empty()) {
        if (!code.empty()) {
            code += "\n";
        }

        code += mProfile->acothFunctionString();
    }
}

std::string Generator::GeneratorImpl::generateCreateArrayCode(size_t arraySize)
{
    return replace(mProfile->returnCreatedArrayString(),
                   "<ARRAY_SIZE>", std::to_string(arraySize));
}

void Generator::GeneratorImpl::addInterfaceCreateDeleteArrayMethodsCode(std::string &code)
{
    std::string interfaceCreateDeleteArraysCode;

    if (!mProfile->interfaceCreateStatesArrayMethodString().empty()) {
        interfaceCreateDeleteArraysCode += mProfile->interfaceCreateStatesArrayMethodString();
    }

    if (!mProfile->interfaceCreateVariablesArrayMethodString().empty()) {
        interfaceCreateDeleteArraysCode += mProfile->interfaceCreateVariablesArrayMethodString();
    }

    if (!mProfile->interfaceDeleteArrayMethodString().empty()) {
        interfaceCreateDeleteArraysCode += mProfile->interfaceDeleteArrayMethodString();
    }

    if (!interfaceCreateDeleteArraysCode.empty()) {
        code += "\n";
    }

    code += interfaceCreateDeleteArraysCode;
}

void Generator::GeneratorImpl::addImplementationCreateStatesArrayMethodCode(std::string &code)
{
    if (!mProfile->implementationCreateStatesArrayMethodString().empty()
        && !mProfile->returnCreatedArrayString().empty()) {
        if (!code.empty()) {
            code += "\n";
        }

        code += replace(mProfile->implementationCreateStatesArrayMethodString(),
                        "<CODE>", mProfile->indentString() + generateCreateArrayCode(mStates.size()));
    }
}

void Generator::GeneratorImpl::addImplementationCreateVariablesArrayMethodCode(std::string &code)
{
    if (!mProfile->implementationCreateVariablesArrayMethodString().empty()
        && !mProfile->returnCreatedArrayString().empty()) {
        if (!code.empty()) {
            code += "\n";
        }

        code += replace(mProfile->implementationCreateVariablesArrayMethodString(),
                        "<CODE>", mProfile->indentString() + generateCreateArrayCode(mVariables.size()));
    }
}

void Generator::GeneratorImpl::addImplementationDeleteArrayMethodCode(std::string &code)
{
    if (!mProfile->implementationDeleteArrayMethodString().empty()) {
        if (!code.empty()) {
            code += "\n";
        }

        code += mProfile->implementationDeleteArrayMethodString();
    }
}

std::string Generator::GeneratorImpl::generateMethodBodyCode(const std::string &methodBody)
{
    return methodBody.empty() ?
               mProfile->emptyMethodString().empty() ?
               "" :
               mProfile->indentString() + mProfile->emptyMethodString() :
               methodBody;
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
    //  7. EQ, NEQ                                               [Left to right]
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
        // Assignment.

    case GeneratorEquationAst::Type::ASSIGNMENT:
        code = generateOperatorCode(mProfile->assignmentString(), ast);

        break;

        // Relational and logical operators.

    case GeneratorEquationAst::Type::EQ:
        if (mProfile->hasEqOperator()) {
            code = generateOperatorCode(mProfile->eqString(), ast);
        } else {
            code = generateTwoParameterFunctionCode(mProfile->eqString(), ast);
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

        // Arithmetic operators.

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

        if (areEqual(doubleValue, 0.5)) {
            code = generateOneParameterFunctionCode(mProfile->squareRootString(), ast);
        } else if (areEqual(doubleValue, 2.0) && !mProfile->squareString().empty()) {
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

            if (areEqual(doubleValue, 2.0)) {
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

            if (areEqual(doubleValue, 10.0)) {
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

        // Calculus elements.

    case GeneratorEquationAst::Type::DIFF:
        code = generateCode(ast->mRight);

        break;

        // Trigonometric operators.

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

        // Piecewise statement.

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

        // Token elements.

    case GeneratorEquationAst::Type::CI:
        code = generateVariableNameCode(ast->mVariable, ast);

        break;
    case GeneratorEquationAst::Type::CN:
        code = generateDoubleCode(ast->mValue);

        break;

        // Qualifier elements.

    case GeneratorEquationAst::Type::DEGREE:
    case GeneratorEquationAst::Type::LOGBASE:
    case GeneratorEquationAst::Type::BVAR:
        code = generateCode(ast->mLeft);

        break;

        // Constants.

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
void Generator::GeneratorImpl::addInterfaceComputeModelMethodsCode(std::string &code)
{
    std::string interfaceComputeModelMethodsCode;

    if (!mProfile->interfaceInitializeStatesAndConstantsMethodString().empty()) {
        interfaceComputeModelMethodsCode += mProfile->interfaceInitializeStatesAndConstantsMethodString();
    }

    if (!mProfile->interfaceComputeComputedConstantsMethodString().empty()) {
        interfaceComputeModelMethodsCode += mProfile->interfaceComputeComputedConstantsMethodString();
    }

    if (!mProfile->interfaceComputeRatesMethodString().empty()) {
        interfaceComputeModelMethodsCode += mProfile->interfaceComputeRatesMethodString();
    }

    if (!mProfile->interfaceComputeVariablesMethodString().empty()) {
        interfaceComputeModelMethodsCode += mProfile->interfaceComputeVariablesMethodString();
    }

    if (!interfaceComputeModelMethodsCode.empty()) {
        code += "\n";
    }

    code += interfaceComputeModelMethodsCode;
}

void Generator::GeneratorImpl::addImplementationInitializeStatesAndConstantsMethodCode(std::string &code,
                                                                                       std::vector<GeneratorEquationPtr> &remainingEquations)
{
    if (!mProfile->implementationInitializeStatesAndConstantsMethodString().empty()) {
        if (!code.empty()) {
            code += "\n";
        }

        std::string methodBody;

        for (const auto &internalVariable : mInternalVariables) {
            if ((internalVariable->mType == GeneratorInternalVariable::Type::STATE)
                || (internalVariable->mType == GeneratorInternalVariable::Type::CONSTANT)) {
                methodBody += generateInitializationCode(internalVariable);
            }
        }

        for (const auto &equation : mEquations) {
            if (equation->mType == GeneratorEquation::Type::TRUE_CONSTANT) {
                methodBody += generateEquationCode(equation, remainingEquations);
            }
        }

        code += replace(mProfile->implementationInitializeStatesAndConstantsMethodString(),
                        "<CODE>", generateMethodBodyCode(methodBody));
    }
}

void Generator::GeneratorImpl::addImplementationComputeComputedConstantsMethodCode(std::string &code,
                                                                                   std::vector<GeneratorEquationPtr> &remainingEquations)
{
    if (!mProfile->implementationComputeComputedConstantsMethodString().empty()) {
        if (!code.empty()) {
            code += "\n";
        }

        std::string methodBody;

        for (const auto &equation : mEquations) {
            if (equation->mType == GeneratorEquation::Type::VARIABLE_BASED_CONSTANT) {
                methodBody += generateEquationCode(equation, remainingEquations);
            }
        }

        code += replace(mProfile->implementationComputeComputedConstantsMethodString(),
                        "<CODE>", generateMethodBodyCode(methodBody));
    }
}

void Generator::GeneratorImpl::addImplementationComputeRatesMethodCode(std::string &code,
                                                                       std::vector<GeneratorEquationPtr> &remainingEquations)
{
    if (!mProfile->implementationComputeRatesMethodString().empty()) {
        if (!code.empty()) {
            code += "\n";
        }

        std::string methodBody;

        for (const auto &equation : mEquations) {
            if (equation->mType == GeneratorEquation::Type::RATE) {
                methodBody += generateEquationCode(equation, remainingEquations);
            }
        }

        code += replace(mProfile->implementationComputeRatesMethodString(),
                        "<CODE>", generateMethodBodyCode(methodBody));
    }
}

void Generator::GeneratorImpl::addImplementationComputeVariablesMethodCode(std::string &code,
                                                                           std::vector<GeneratorEquationPtr> &remainingEquations)
{
    if (!mProfile->implementationComputeVariablesMethodString().empty()) {
        if (!code.empty()) {
            code += "\n";
        }

        std::vector<GeneratorEquationPtr> newRemainingEquations {std::begin(mEquations), std::end(mEquations)};

        std::string methodBody;

        for (const auto &equation : mEquations) {
            if ((std::find(remainingEquations.begin(), remainingEquations.end(), equation) != remainingEquations.end())
                || ((equation->mType == GeneratorEquation::Type::ALGEBRAIC)
                    && equation->mIsStateRateBased)) {
                methodBody += generateEquationCode(equation, newRemainingEquations, true);
            }
        }

        code += replace(mProfile->implementationComputeVariablesMethodString(),
                        "<CODE>", generateMethodBodyCode(methodBody));
    }
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

GeneratorPtr Generator::create() noexcept
{
    return std::shared_ptr<Generator> {new Generator {}};
}

GeneratorProfilePtr Generator::profile()
{
    return mPimpl->mProfile;
}

void Generator::setProfile(const GeneratorProfilePtr &profile)
{
    mPimpl->mProfile = profile;
}

void Generator::processModel(const ModelPtr &model)
{
    // Make sure that the model is valid before processing it.

    /*TODO: enable the below code once validation is known to work fine.
    ValidatorPtr validator = Validator::create();

    validator->validateModel(model);

    if (validator->errorCount() > 0) {
        // The model is not valid, so retrieve the validation errors and make
        // them our own.

        for (size_t i = 0; i < validator->errorCount(); ++i) {
            addError(validator->error(i));
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

std::string Generator::interfaceCode() const
{
    if (!mPimpl->hasValidModel() || !mPimpl->mProfile->hasInterface()) {
        return {};
    }

    // Add code for the origin comment.

    std::string res;

    mPimpl->addOriginCommentCode(res);

    // Add code for the header.

    mPimpl->addInterfaceHeaderCode(res);

    // Add code for the interface of the version of the profile and libCellML.

    mPimpl->addVersionAndLibcellmlVersionCode(res, true);

    // Add code for the interface of the number of states and variables.

    mPimpl->addStateAndVariableCountCode(res, true);

    // Add code for the variable information related objects.

    if (mPimpl->mProfile->hasInterface()) {
        mPimpl->addVariableTypeObjectCode(res);
        mPimpl->addVariableInfoObjectCode(res);
        mPimpl->addVariableInfoWithTypeObjectCode(res);
    }

    // Add code for the interface of the information about the variable of
    // integration, states and (other) variables.

    mPimpl->addInterfaceVoiStateAndVariableInfoCode(res);

    // Add code for the interface to create and delete arrays.

    mPimpl->addInterfaceCreateDeleteArrayMethodsCode(res);

    // Add code for the interface to compute the model.

    mPimpl->addInterfaceComputeModelMethodsCode(res);

    return res;
}

std::string Generator::implementationCode() const
{
    if (!mPimpl->hasValidModel()) {
        return {};
    }

    std::string res;

    // Add code for the origin comment.

    mPimpl->addOriginCommentCode(res);

    // Add code for the header.

    mPimpl->addImplementationHeaderCode(res);

    // Add code for the implementation of the version of the profile and
    // libCellML.

    mPimpl->addVersionAndLibcellmlVersionCode(res);

    // Add code for the implementation of the number of states and variables.

    mPimpl->addStateAndVariableCountCode(res);

    // Add code for the variable information related objects.

    if (!mPimpl->mProfile->hasInterface()) {
        mPimpl->addVariableTypeObjectCode(res);
        mPimpl->addVariableInfoObjectCode(res);
        mPimpl->addVariableInfoWithTypeObjectCode(res);
    }

    // Add code for the implementation of the information about the variable of
    // integration, states and (other) variables.

    mPimpl->addImplementationVoiInfoCode(res);
    mPimpl->addImplementationStateInfoCode(res);
    mPimpl->addImplementationVariableInfoCode(res);

    // Add code for the arithmetic and trigonometric functions.

    mPimpl->addArithmeticFunctionsCode(res);
    mPimpl->addTrigonometricFunctionsCode(res);

    // Add code for the implementation to create and delete arrays.

    mPimpl->addImplementationCreateStatesArrayMethodCode(res);
    mPimpl->addImplementationCreateVariablesArrayMethodCode(res);
    mPimpl->addImplementationDeleteArrayMethodCode(res);

    // Add code for the implementation to initialise our states and constants.

    std::vector<GeneratorEquationPtr> remainingEquations {std::begin(mPimpl->mEquations), std::end(mPimpl->mEquations)};

    mPimpl->addImplementationInitializeStatesAndConstantsMethodCode(res, remainingEquations);

    // Add code for the implementation to compute our computed constants.

    mPimpl->addImplementationComputeComputedConstantsMethodCode(res, remainingEquations);

    // Add code for the implementation to compute our rates (and any variables
    // on which they depend).

    mPimpl->addImplementationComputeRatesMethodCode(res, remainingEquations);

    // Add code for the implementation to compute our variables.
    // Note: this method computes the remaining variables, i.e. the ones not
    //       needed to compute our rates, but also the variables that depend on
    //       the value of some states/rates. Indeed, this method is typically
    //       called after having integrated a model, thus ensuring that
    //       variables that rely on the value of some states/rates are up to
    //       date.

    mPimpl->addImplementationComputeVariablesMethodCode(res, remainingEquations);

    return res;
}

} // namespace libcellml

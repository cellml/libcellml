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

#include "libcellml/analyser.h"

#include "libcellml/analyserequation.h"
#include "libcellml/analyserequationast.h"
#include "libcellml/analyserexternalvariable.h"
#include "libcellml/analysermodel.h"
#include "libcellml/analyservariable.h"
#include "libcellml/component.h"
#include "libcellml/model.h"
#include "libcellml/units.h"
#include "libcellml/validator.h"
#include "libcellml/variable.h"

#include "analyserequation_p.h"
#include "analyserequationast_p.h"
#include "analysermodel_p.h"
#include "analyservariable_p.h"
#include "utilities.h"
#include "xmldoc.h"
#include "xmlutils.h"

#ifdef TRUE
#    undef TRUE
#endif

#ifdef FALSE
#    undef FALSE
#endif

#ifdef NAN
#    undef NAN
#endif

namespace libcellml {

static const size_t MAX_SIZE_T = std::numeric_limits<size_t>::max();

struct AnalyserInternalEquation;
using AnalyserInternalEquationPtr = std::shared_ptr<AnalyserInternalEquation>;

struct AnalyserInternalVariable
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

    VariablePtr mInitialisingVariable;
    VariablePtr mVariable;

    explicit AnalyserInternalVariable(const VariablePtr &variable);

    void setVariable(const VariablePtr &variable,
                     bool checkInitialValue = true);

    void makeVoi();
    void makeState();
};

using AnalyserInternalVariablePtr = std::shared_ptr<AnalyserInternalVariable>;

AnalyserInternalVariable::AnalyserInternalVariable(const VariablePtr &variable)
{
    setVariable(variable);
}

void AnalyserInternalVariable::setVariable(const VariablePtr &variable,
                                           bool checkInitialValue)
{
    if (checkInitialValue && !variable->initialValue().empty()) {
        // The variable has an initial value, so it can either be a constant or
        // a state. By default, we consider it to be a constant and, if we find
        // an ODE for that variable, we will know that it was actually a state.

        mType = Type::CONSTANT;

        mInitialisingVariable = variable;
    }

    mVariable = variable;
}

void AnalyserInternalVariable::makeVoi()
{
    mType = Type::VARIABLE_OF_INTEGRATION;
}

void AnalyserInternalVariable::makeState()
{
    if (mType == Type::UNKNOWN) {
        mType = Type::SHOULD_BE_STATE;
    } else if (mType == Type::CONSTANT) {
        mType = Type::STATE;
    }
}

struct AnalyserInternalEquation
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

    std::vector<VariablePtr> mDependencies;

    AnalyserEquationAstPtr mAst;

    std::vector<AnalyserInternalVariablePtr> mVariables;
    std::vector<AnalyserInternalVariablePtr> mOdeVariables;
    std::vector<AnalyserInternalVariablePtr> mAllVariables;

    AnalyserInternalVariablePtr mVariable;
    ComponentPtr mComponent = nullptr;

    bool mComputedTrueConstant = true;
    bool mComputedVariableBasedConstant = true;

    explicit AnalyserInternalEquation(const ComponentPtr &component);
    explicit AnalyserInternalEquation(const AnalyserInternalVariablePtr &variable);

    void addVariable(const AnalyserInternalVariablePtr &variable);
    void addOdeVariable(const AnalyserInternalVariablePtr &odeVariable);

    static bool isKnownVariable(const AnalyserInternalVariablePtr &variable);
    static bool isKnownOdeVariable(const AnalyserInternalVariablePtr &odeVariable);

    static bool hasKnownVariables(const std::vector<AnalyserInternalVariablePtr> &variables);
    static bool hasNonConstantVariables(const std::vector<AnalyserInternalVariablePtr> &variables);

    bool check(size_t &equationOrder, size_t &stateIndex, size_t &variableIndex,
               const AnalyserModelPtr &model);
};

AnalyserInternalEquation::AnalyserInternalEquation(const ComponentPtr &component)
    : mAst(AnalyserEquationAst::create())
    , mComponent(component)
{
}

AnalyserInternalEquation::AnalyserInternalEquation(const AnalyserInternalVariablePtr &variable)
    : mVariable(variable)
    , mComponent(owningComponent(variable->mVariable))
{
}

void AnalyserInternalEquation::addVariable(const AnalyserInternalVariablePtr &variable)
{
    if (std::find(mVariables.begin(), mVariables.end(), variable) == mVariables.end()) {
        mVariables.push_back(variable);
        mAllVariables.push_back(variable);
    }
}

void AnalyserInternalEquation::addOdeVariable(const AnalyserInternalVariablePtr &odeVariable)
{
    if (std::find(mOdeVariables.begin(), mOdeVariables.end(), odeVariable) == mOdeVariables.end()) {
        mOdeVariables.push_back(odeVariable);
        mAllVariables.push_back(odeVariable);
    }
}

bool AnalyserInternalEquation::isKnownVariable(const AnalyserInternalVariablePtr &variable)
{
    return variable->mType != AnalyserInternalVariable::Type::UNKNOWN;
}

bool AnalyserInternalEquation::isKnownOdeVariable(const AnalyserInternalVariablePtr &odeVariable)
{
    return odeVariable->mIndex != MAX_SIZE_T;
}

bool AnalyserInternalEquation::hasKnownVariables(const std::vector<AnalyserInternalVariablePtr> &variables)
{
    return std::find_if(variables.begin(), variables.end(), [](const AnalyserInternalVariablePtr &variable) {
               return isKnownVariable(variable);
           })
           != std::end(variables);
}

bool AnalyserInternalEquation::hasNonConstantVariables(const std::vector<AnalyserInternalVariablePtr> &variables)
{
    return std::find_if(variables.begin(), variables.end(), [](const AnalyserInternalVariablePtr &variable) {
               return (variable->mType != AnalyserInternalVariable::Type::UNKNOWN)
                      && (variable->mType != AnalyserInternalVariable::Type::CONSTANT)
                      && (variable->mType != AnalyserInternalVariable::Type::COMPUTED_TRUE_CONSTANT)
                      && (variable->mType != AnalyserInternalVariable::Type::COMPUTED_VARIABLE_BASED_CONSTANT);
           })
           != std::end(variables);
}

bool AnalyserInternalEquation::check(size_t &equationOrder, size_t &stateIndex,
                                     size_t &variableIndex,
                                     const AnalyserModelPtr &model)
{
    // Nothing to check if the equation has already been given an order (i.e.
    // everything is fine).

    if (mOrder != MAX_SIZE_T) {
        return false;
    }

    // Determine, from the (new) known (ODE) variables, whether the equation is
    // used to compute a true constant or a variable-based constant.

    mComputedTrueConstant = mComputedTrueConstant
                            && !hasKnownVariables(mVariables)
                            && !hasKnownVariables(mOdeVariables);
    mComputedVariableBasedConstant = mComputedVariableBasedConstant
                                     && !hasNonConstantVariables(mVariables)
                                     && !hasNonConstantVariables(mOdeVariables);

    // Add, as a dependency, the variables used to compute the (new) known (ODE)
    // variables.

    for (const auto &variable : mVariables) {
        if (isKnownVariable(variable)) {
            mDependencies.push_back(variable->mVariable);
        }
    }

    // Stop tracking (new) known (ODE) variables.

    mVariables.erase(std::remove_if(mVariables.begin(), mVariables.end(), isKnownVariable), mVariables.end());
    mOdeVariables.erase(std::remove_if(mOdeVariables.begin(), mOdeVariables.end(), isKnownOdeVariable), mOdeVariables.end());

    // If there is no (ODE) variable left then it means that the equation is an
    // overconstraint).

    auto unknownVariablesOrOdeVariablesLeft = mVariables.size() + mOdeVariables.size();

    if (unknownVariablesOrOdeVariablesLeft == 0) {
        for (const auto &variable : mAllVariables) {
            variable->mType = AnalyserInternalVariable::Type::OVERCONSTRAINED;
        }

        return false;
    }

    // If there is one (ODE) variable left then update its variable (to be the
    // corresponding one in the component in which the equation is), its type
    // (if it is currently unknown), determine its index and determine the type
    // of our equation and set its order, if the (ODE) variable is a state,
    // computed constant or algebraic variable.

    if (unknownVariablesOrOdeVariablesLeft == 1) {
        auto variable = (mVariables.size() == 1) ? mVariables.front() : mOdeVariables.front();

        for (size_t i = 0; i < mComponent->variableCount(); ++i) {
            auto localVariable = mComponent->variable(i);

            if (model->areEquivalentVariables(variable->mVariable, localVariable)) {
                variable->setVariable(localVariable, false);

                break;
            }
        }

        if (variable->mType == AnalyserInternalVariable::Type::UNKNOWN) {
            variable->mType = mComputedTrueConstant ?
                                  AnalyserInternalVariable::Type::COMPUTED_TRUE_CONSTANT :
                              mComputedVariableBasedConstant ?
                                  AnalyserInternalVariable::Type::COMPUTED_VARIABLE_BASED_CONSTANT :
                                  AnalyserInternalVariable::Type::ALGEBRAIC;
        }

        if ((variable->mType == AnalyserInternalVariable::Type::STATE)
            || (variable->mType == AnalyserInternalVariable::Type::COMPUTED_TRUE_CONSTANT)
            || (variable->mType == AnalyserInternalVariable::Type::COMPUTED_VARIABLE_BASED_CONSTANT)
            || (variable->mType == AnalyserInternalVariable::Type::ALGEBRAIC)) {
            variable->mIndex = (variable->mType == AnalyserInternalVariable::Type::STATE) ?
                                   ++stateIndex :
                                   ++variableIndex;

            mOrder = ++equationOrder;
            mType = (variable->mType == AnalyserInternalVariable::Type::STATE) ?
                        Type::RATE :
                    (variable->mType == AnalyserInternalVariable::Type::COMPUTED_TRUE_CONSTANT) ?
                        Type::TRUE_CONSTANT :
                    (variable->mType == AnalyserInternalVariable::Type::COMPUTED_VARIABLE_BASED_CONSTANT) ?
                        Type::VARIABLE_BASED_CONSTANT :
                        Type::ALGEBRAIC;

            mVariable = variable;

            return true;
        }
    }

    return false;
}

/**
 * @brief The Analyser::AnalyserImpl struct.
 *
 * The private implementation for the Analyser class.
 */
struct Analyser::AnalyserImpl
{
    Analyser *mAnalyser = nullptr;

    AnalyserModelPtr mModel = nullptr;
    std::vector<AnalyserExternalVariablePtr> mExternalVariables;

    std::vector<AnalyserInternalVariablePtr> mInternalVariables;
    std::vector<AnalyserInternalEquationPtr> mInternalEquations;

    explicit AnalyserImpl(Analyser *analyser);

    static bool compareVariablesByComponentAndName(const AnalyserInternalVariablePtr &variable1,
                                                   const AnalyserInternalVariablePtr &variable2);

    static bool isStateVariable(const AnalyserInternalVariablePtr &variable);
    static bool isConstantOrAlgebraicVariable(const AnalyserInternalVariablePtr &variable);

    static bool compareVariablesByTypeAndIndex(const AnalyserInternalVariablePtr &variable1,
                                               const AnalyserInternalVariablePtr &variable2);

    static bool compareEquationsByVariable(const AnalyserInternalEquationPtr &equation1,
                                           const AnalyserInternalEquationPtr &equation2);

    size_t mathmlChildCount(const XmlNodePtr &node) const;
    XmlNodePtr mathmlChildNode(const XmlNodePtr &node, size_t index) const;

    AnalyserInternalVariablePtr internalVariable(const VariablePtr &variable);

    VariablePtr voiFirstOccurrence(const VariablePtr &variable,
                                   const ComponentPtr &component);

    void analyseNode(const XmlNodePtr &node, AnalyserEquationAstPtr &ast,
                     const AnalyserEquationAstPtr &astParent,
                     const ComponentPtr &component,
                     const AnalyserInternalEquationPtr &equation);
    void analyseComponent(const ComponentPtr &component);

    void doEquivalentVariables(const VariablePtr &variable,
                               std::vector<VariablePtr> &equivalentVariables) const;
    std::vector<VariablePtr> equivalentVariables(const VariablePtr &variable) const;

    void analyseEquationAst(const AnalyserEquationAstPtr &ast);

    double scalingFactor(const VariablePtr &variable);

    void scaleAst(const AnalyserEquationAstPtr &ast,
                  const AnalyserEquationAstPtr &astParent,
                  double scalingFactor);
    void scaleEquationAst(const AnalyserEquationAstPtr &ast);

    bool isStateRateBased(const AnalyserEquationPtr &equation,
                          std::vector<AnalyserEquationPtr> &checkedEquations);

    void analyseModel(const ModelPtr &model);

    std::vector<AnalyserExternalVariablePtr>::iterator findExternalVariable(const ModelPtr &model,
                                                                            const std::string &componentName,
                                                                            const std::string &variableName);
    std::vector<AnalyserExternalVariablePtr>::iterator findExternalVariable(const AnalyserExternalVariablePtr &externalVariable);
};

Analyser::AnalyserImpl::AnalyserImpl(Analyser *analyser)
    : mAnalyser(analyser)
    , mModel(std::shared_ptr<AnalyserModel> {new AnalyserModel {}})
{
}

bool Analyser::AnalyserImpl::compareVariablesByComponentAndName(const AnalyserInternalVariablePtr &variable1,
                                                                const AnalyserInternalVariablePtr &variable2)
{
    auto realComponent1 = owningComponent(variable1->mVariable);
    auto realComponent2 = owningComponent(variable2->mVariable);

    if (realComponent1->name() == realComponent2->name()) {
        return variable1->mVariable->name() < variable2->mVariable->name();
    }

    return realComponent1->name() < realComponent2->name();
}

bool Analyser::AnalyserImpl::isStateVariable(const AnalyserInternalVariablePtr &variable)
{
    return variable->mType == AnalyserInternalVariable::Type::STATE;
}

bool Analyser::AnalyserImpl::isConstantOrAlgebraicVariable(const AnalyserInternalVariablePtr &variable)
{
    return (variable->mType == AnalyserInternalVariable::Type::CONSTANT)
           || (variable->mType == AnalyserInternalVariable::Type::COMPUTED_TRUE_CONSTANT)
           || (variable->mType == AnalyserInternalVariable::Type::COMPUTED_VARIABLE_BASED_CONSTANT)
           || (variable->mType == AnalyserInternalVariable::Type::ALGEBRAIC);
}

bool Analyser::AnalyserImpl::compareVariablesByTypeAndIndex(const AnalyserInternalVariablePtr &variable1,
                                                            const AnalyserInternalVariablePtr &variable2)
{
    if (isStateVariable(variable1) && isConstantOrAlgebraicVariable(variable2)) {
        return true;
    }

    if (isConstantOrAlgebraicVariable(variable1) && isStateVariable(variable2)) {
        return false;
    }

    return variable1->mIndex < variable2->mIndex;
}

bool Analyser::AnalyserImpl::compareEquationsByVariable(const AnalyserInternalEquationPtr &equation1,
                                                        const AnalyserInternalEquationPtr &equation2)
{
    return compareVariablesByTypeAndIndex(equation1->mVariable, equation2->mVariable);
}

size_t Analyser::AnalyserImpl::mathmlChildCount(const XmlNodePtr &node) const
{
    // Return the number of child elements, in the MathML namespace, for the
    // given node.

    auto childNode = node->firstChild();
    size_t res = childNode->isMathmlElement() ? 1 : 0;

    while (childNode != nullptr) {
        childNode = childNode->next();

        if (childNode && childNode->isMathmlElement()) {
            ++res;
        }
    }

    return res;
}

XmlNodePtr Analyser::AnalyserImpl::mathmlChildNode(const XmlNodePtr &node,
                                                   size_t index) const
{
    // Return the nth child element of the given node, skipping anything that is
    // not int the MathML namespace.

    auto res = node->firstChild();
    auto childNodeIndex = res->isMathmlElement() ? 0 : MAX_SIZE_T;

    while ((res != nullptr) && (childNodeIndex != index)) {
        res = res->next();

        if (res && res->isMathmlElement()) {
            ++childNodeIndex;
        }
    }

    return res;
}

AnalyserInternalVariablePtr Analyser::AnalyserImpl::internalVariable(const VariablePtr &variable)
{
    // Find and return, if there is one, the internal variable associated with
    // the given variable.

    AnalyserInternalVariablePtr res = nullptr;

    for (const auto &internalVariable : mInternalVariables) {
        if (mModel->areEquivalentVariables(variable, internalVariable->mVariable)) {
            res = internalVariable;

            break;
        }
    }

    if (res != nullptr) {
        return res;
    }

    // No internal variable exists for the given variable, so create one, track
    // it and return it.

    res = std::shared_ptr<AnalyserInternalVariable> {new AnalyserInternalVariable {variable}};

    mInternalVariables.push_back(res);

    return res;
}

VariablePtr Analyser::AnalyserImpl::voiFirstOccurrence(const VariablePtr &variable,
                                                       const ComponentPtr &component)
{
    // Recursively look for the first occurrence of the given variable in the
    // given component.

    for (size_t i = 0; i < component->variableCount(); ++i) {
        auto componentVariable = component->variable(i);

        if (mModel->areEquivalentVariables(variable, componentVariable)) {
            return componentVariable;
        }
    }

    VariablePtr res = nullptr;

    for (size_t i = 0; i < component->componentCount() && res == nullptr; ++i) {
        res = voiFirstOccurrence(variable, component->component(i));
    }

    return res;
}

void Analyser::AnalyserImpl::analyseNode(const XmlNodePtr &node,
                                         AnalyserEquationAstPtr &ast,
                                         const AnalyserEquationAstPtr &astParent,
                                         const ComponentPtr &component,
                                         const AnalyserInternalEquationPtr &equation)
{
    // Create the AST, if needed.

    if (ast.get() == nullptr) {
        ast.reset(new AnalyserEquationAst {});
    }

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

        auto childCount = mathmlChildCount(node);

        analyseNode(mathmlChildNode(node, 0), ast, astParent, component, equation);
        analyseNode(mathmlChildNode(node, 1), ast->mPimpl->mOwnedLeftChild, ast, component, equation);

        if (childCount >= 3) {
            AnalyserEquationAstPtr astRightChild;
            AnalyserEquationAstPtr tempAst;

            analyseNode(mathmlChildNode(node, childCount - 1), astRightChild, nullptr, component, equation);

            for (auto i = childCount - 2; i > 1; --i) {
                tempAst = AnalyserEquationAst::create();

                analyseNode(mathmlChildNode(node, 0), tempAst, nullptr, component, equation);
                analyseNode(mathmlChildNode(node, i), tempAst->mPimpl->mOwnedLeftChild, tempAst, component, equation);

                astRightChild->mPimpl->mParent = tempAst;

                tempAst->mPimpl->mOwnedRightChild = astRightChild;
                astRightChild = tempAst;
            }

            if (astRightChild != nullptr) {
                astRightChild->mPimpl->mParent = ast;
            }

            ast->mPimpl->mOwnedRightChild = astRightChild;
        }

        // Assignment, and relational and logical operators.

    } else if (node->isMathmlElement("eq")) {
        // This element is used both to describe "a = b" and "a == b". We can
        // distinguish between the two by checking its grand-parent. If it's a
        // "math" element then it means that it is used to describe "a = b"
        // otherwise it is used to describe "a == b". In the former case, there
        // is nothing more we need to do since `ast` is already of
        // AnalyserEquationAst::Type::ASSIGNMENT type.

        if (!node->parent()->parent()->isMathmlElement("math")) {
            ast->mPimpl->populate(AnalyserEquationAst::Type::EQ, astParent);

            mModel->mPimpl->mNeedEqFunction = true;
        }
    } else if (node->isMathmlElement("neq")) {
        ast->mPimpl->populate(AnalyserEquationAst::Type::NEQ, astParent);

        mModel->mPimpl->mNeedNeqFunction = true;
    } else if (node->isMathmlElement("lt")) {
        ast->mPimpl->populate(AnalyserEquationAst::Type::LT, astParent);

        mModel->mPimpl->mNeedLtFunction = true;
    } else if (node->isMathmlElement("leq")) {
        ast->mPimpl->populate(AnalyserEquationAst::Type::LEQ, astParent);

        mModel->mPimpl->mNeedLeqFunction = true;
    } else if (node->isMathmlElement("gt")) {
        ast->mPimpl->populate(AnalyserEquationAst::Type::GT, astParent);

        mModel->mPimpl->mNeedGtFunction = true;
    } else if (node->isMathmlElement("geq")) {
        ast->mPimpl->populate(AnalyserEquationAst::Type::GEQ, astParent);

        mModel->mPimpl->mNeedGeqFunction = true;
    } else if (node->isMathmlElement("and")) {
        ast->mPimpl->populate(AnalyserEquationAst::Type::AND, astParent);

        mModel->mPimpl->mNeedAndFunction = true;
    } else if (node->isMathmlElement("or")) {
        ast->mPimpl->populate(AnalyserEquationAst::Type::OR, astParent);

        mModel->mPimpl->mNeedOrFunction = true;
    } else if (node->isMathmlElement("xor")) {
        ast->mPimpl->populate(AnalyserEquationAst::Type::XOR, astParent);

        mModel->mPimpl->mNeedXorFunction = true;
    } else if (node->isMathmlElement("not")) {
        ast->mPimpl->populate(AnalyserEquationAst::Type::NOT, astParent);

        mModel->mPimpl->mNeedNotFunction = true;

        // Arithmetic operators.

    } else if (node->isMathmlElement("plus")) {
        ast->mPimpl->populate(AnalyserEquationAst::Type::PLUS, astParent);
    } else if (node->isMathmlElement("minus")) {
        ast->mPimpl->populate(AnalyserEquationAst::Type::MINUS, astParent);
    } else if (node->isMathmlElement("times")) {
        ast->mPimpl->populate(AnalyserEquationAst::Type::TIMES, astParent);
    } else if (node->isMathmlElement("divide")) {
        ast->mPimpl->populate(AnalyserEquationAst::Type::DIVIDE, astParent);
    } else if (node->isMathmlElement("power")) {
        ast->mPimpl->populate(AnalyserEquationAst::Type::POWER, astParent);
    } else if (node->isMathmlElement("root")) {
        ast->mPimpl->populate(AnalyserEquationAst::Type::ROOT, astParent);
    } else if (node->isMathmlElement("abs")) {
        ast->mPimpl->populate(AnalyserEquationAst::Type::ABS, astParent);
    } else if (node->isMathmlElement("exp")) {
        ast->mPimpl->populate(AnalyserEquationAst::Type::EXP, astParent);
    } else if (node->isMathmlElement("ln")) {
        ast->mPimpl->populate(AnalyserEquationAst::Type::LN, astParent);
    } else if (node->isMathmlElement("log")) {
        ast->mPimpl->populate(AnalyserEquationAst::Type::LOG, astParent);
    } else if (node->isMathmlElement("ceiling")) {
        ast->mPimpl->populate(AnalyserEquationAst::Type::CEILING, astParent);
    } else if (node->isMathmlElement("floor")) {
        ast->mPimpl->populate(AnalyserEquationAst::Type::FLOOR, astParent);
    } else if (node->isMathmlElement("min")) {
        ast->mPimpl->populate(AnalyserEquationAst::Type::MIN, astParent);

        mModel->mPimpl->mNeedMinFunction = true;
    } else if (node->isMathmlElement("max")) {
        ast->mPimpl->populate(AnalyserEquationAst::Type::MAX, astParent);

        mModel->mPimpl->mNeedMaxFunction = true;
    } else if (node->isMathmlElement("rem")) {
        ast->mPimpl->populate(AnalyserEquationAst::Type::REM, astParent);

        // Calculus elements.

    } else if (node->isMathmlElement("diff")) {
        ast->mPimpl->populate(AnalyserEquationAst::Type::DIFF, astParent);

        // Trigonometric operators.

    } else if (node->isMathmlElement("sin")) {
        ast->mPimpl->populate(AnalyserEquationAst::Type::SIN, astParent);
    } else if (node->isMathmlElement("cos")) {
        ast->mPimpl->populate(AnalyserEquationAst::Type::COS, astParent);
    } else if (node->isMathmlElement("tan")) {
        ast->mPimpl->populate(AnalyserEquationAst::Type::TAN, astParent);
    } else if (node->isMathmlElement("sec")) {
        ast->mPimpl->populate(AnalyserEquationAst::Type::SEC, astParent);

        mModel->mPimpl->mNeedSecFunction = true;
    } else if (node->isMathmlElement("csc")) {
        ast->mPimpl->populate(AnalyserEquationAst::Type::CSC, astParent);

        mModel->mPimpl->mNeedCscFunction = true;
    } else if (node->isMathmlElement("cot")) {
        ast->mPimpl->populate(AnalyserEquationAst::Type::COT, astParent);

        mModel->mPimpl->mNeedCotFunction = true;
    } else if (node->isMathmlElement("sinh")) {
        ast->mPimpl->populate(AnalyserEquationAst::Type::SINH, astParent);
    } else if (node->isMathmlElement("cosh")) {
        ast->mPimpl->populate(AnalyserEquationAst::Type::COSH, astParent);
    } else if (node->isMathmlElement("tanh")) {
        ast->mPimpl->populate(AnalyserEquationAst::Type::TANH, astParent);
    } else if (node->isMathmlElement("sech")) {
        ast->mPimpl->populate(AnalyserEquationAst::Type::SECH, astParent);

        mModel->mPimpl->mNeedSechFunction = true;
    } else if (node->isMathmlElement("csch")) {
        ast->mPimpl->populate(AnalyserEquationAst::Type::CSCH, astParent);

        mModel->mPimpl->mNeedCschFunction = true;
    } else if (node->isMathmlElement("coth")) {
        ast->mPimpl->populate(AnalyserEquationAst::Type::COTH, astParent);

        mModel->mPimpl->mNeedCothFunction = true;
    } else if (node->isMathmlElement("arcsin")) {
        ast->mPimpl->populate(AnalyserEquationAst::Type::ASIN, astParent);
    } else if (node->isMathmlElement("arccos")) {
        ast->mPimpl->populate(AnalyserEquationAst::Type::ACOS, astParent);
    } else if (node->isMathmlElement("arctan")) {
        ast->mPimpl->populate(AnalyserEquationAst::Type::ATAN, astParent);
    } else if (node->isMathmlElement("arcsec")) {
        ast->mPimpl->populate(AnalyserEquationAst::Type::ASEC, astParent);

        mModel->mPimpl->mNeedAsecFunction = true;
    } else if (node->isMathmlElement("arccsc")) {
        ast->mPimpl->populate(AnalyserEquationAst::Type::ACSC, astParent);

        mModel->mPimpl->mNeedAcscFunction = true;
    } else if (node->isMathmlElement("arccot")) {
        ast->mPimpl->populate(AnalyserEquationAst::Type::ACOT, astParent);

        mModel->mPimpl->mNeedAcotFunction = true;
    } else if (node->isMathmlElement("arcsinh")) {
        ast->mPimpl->populate(AnalyserEquationAst::Type::ASINH, astParent);
    } else if (node->isMathmlElement("arccosh")) {
        ast->mPimpl->populate(AnalyserEquationAst::Type::ACOSH, astParent);
    } else if (node->isMathmlElement("arctanh")) {
        ast->mPimpl->populate(AnalyserEquationAst::Type::ATANH, astParent);
    } else if (node->isMathmlElement("arcsech")) {
        ast->mPimpl->populate(AnalyserEquationAst::Type::ASECH, astParent);

        mModel->mPimpl->mNeedAsechFunction = true;
    } else if (node->isMathmlElement("arccsch")) {
        ast->mPimpl->populate(AnalyserEquationAst::Type::ACSCH, astParent);

        mModel->mPimpl->mNeedAcschFunction = true;
    } else if (node->isMathmlElement("arccoth")) {
        ast->mPimpl->populate(AnalyserEquationAst::Type::ACOTH, astParent);

        mModel->mPimpl->mNeedAcothFunction = true;

        // Piecewise statement.

    } else if (node->isMathmlElement("piecewise")) {
        auto childCount = mathmlChildCount(node);

        ast->mPimpl->populate(AnalyserEquationAst::Type::PIECEWISE, astParent);

        analyseNode(mathmlChildNode(node, 0), ast->mPimpl->mOwnedLeftChild, ast, component, equation);

        if (childCount >= 2) {
            AnalyserEquationAstPtr astRight;
            AnalyserEquationAstPtr tempAst;

            analyseNode(mathmlChildNode(node, childCount - 1), astRight, nullptr, component, equation);

            for (auto i = childCount - 2; i > 0; --i) {
                tempAst = AnalyserEquationAst::create();

                tempAst->mPimpl->populate(AnalyserEquationAst::Type::PIECEWISE, astParent);

                analyseNode(mathmlChildNode(node, i), tempAst->mPimpl->mOwnedLeftChild, tempAst, component, equation);

                astRight->mPimpl->mParent = tempAst;

                tempAst->mPimpl->mOwnedRightChild = astRight;
                astRight = tempAst;
            }

            astRight->mPimpl->mParent = ast;

            ast->mPimpl->mOwnedRightChild = astRight;
        }
    } else if (node->isMathmlElement("piece")) {
        ast->mPimpl->populate(AnalyserEquationAst::Type::PIECE, astParent);

        analyseNode(mathmlChildNode(node, 0), ast->mPimpl->mOwnedLeftChild, ast, component, equation);
        analyseNode(mathmlChildNode(node, 1), ast->mPimpl->mOwnedRightChild, ast, component, equation);
    } else if (node->isMathmlElement("otherwise")) {
        ast->mPimpl->populate(AnalyserEquationAst::Type::OTHERWISE, astParent);

        analyseNode(mathmlChildNode(node, 0), ast->mPimpl->mOwnedLeftChild, ast, component, equation);

        // Token elements.

    } else if (node->isMathmlElement("ci")) {
        auto variableName = node->firstChild()->convertToStrippedString();
        auto variable = component->variable(variableName);
        // Note: we always have a variable. Indeed, if we were not to have one,
        //       it would mean that `variableName` is the name of a variable
        //       that is referenced in an equation, but not defined anywhere,
        //       something that is not allowed in CellML and will therefore be
        //       reported when we validate the model.

        // Have our equation track the (ODE) variable (by ODE variable, we mean
        // a variable that is used in a "diff" element).

        if (node->parent()->firstChild()->isMathmlElement("diff")) {
            equation->addOdeVariable(internalVariable(variable));
        } else if (!(node->parent()->isMathmlElement("bvar")
                     && node->parent()->parent()->firstChild()->isMathmlElement("diff"))) {
            equation->addVariable(internalVariable(variable));
        }

        // Add the variable to our AST.

        ast->mPimpl->populate(AnalyserEquationAst::Type::CI, variable, astParent);
    } else if (node->isMathmlElement("cn")) {
        if (mathmlChildCount(node) == 1) {
            // We are dealing with an e-notation based CN value.

            ast->mPimpl->populate(AnalyserEquationAst::Type::CN, node->firstChild()->convertToStrippedString() + "e" + node->firstChild()->next()->next()->convertToStrippedString(), astParent);
        } else {
            ast->mPimpl->populate(AnalyserEquationAst::Type::CN, node->firstChild()->convertToStrippedString(), astParent);
        }

        // Qualifier elements.

    } else if (node->isMathmlElement("degree")) {
        ast->mPimpl->populate(AnalyserEquationAst::Type::DEGREE, astParent);

        analyseNode(mathmlChildNode(node, 0), ast->mPimpl->mOwnedLeftChild, ast, component, equation);
    } else if (node->isMathmlElement("logbase")) {
        ast->mPimpl->populate(AnalyserEquationAst::Type::LOGBASE, astParent);

        analyseNode(mathmlChildNode(node, 0), ast->mPimpl->mOwnedLeftChild, ast, component, equation);
    } else if (node->isMathmlElement("bvar")) {
        ast->mPimpl->populate(AnalyserEquationAst::Type::BVAR, astParent);

        analyseNode(mathmlChildNode(node, 0), ast->mPimpl->mOwnedLeftChild, ast, component, equation);

        auto rightNode = mathmlChildNode(node, 1);

        if (rightNode != nullptr) {
            analyseNode(rightNode, ast->mPimpl->mOwnedRightChild, ast, component, equation);
        }

        // Constants.

    } else if (node->isMathmlElement("true")) {
        ast->mPimpl->populate(AnalyserEquationAst::Type::TRUE, astParent);
    } else if (node->isMathmlElement("false")) {
        ast->mPimpl->populate(AnalyserEquationAst::Type::FALSE, astParent);
    } else if (node->isMathmlElement("exponentiale")) {
        ast->mPimpl->populate(AnalyserEquationAst::Type::E, astParent);
    } else if (node->isMathmlElement("pi")) {
        ast->mPimpl->populate(AnalyserEquationAst::Type::PI, astParent);
    } else if (node->isMathmlElement("infinity")) {
        ast->mPimpl->populate(AnalyserEquationAst::Type::INF, astParent);
    } else if (node->isMathmlElement("notanumber")) {
        ast->mPimpl->populate(AnalyserEquationAst::Type::NAN, astParent);
    }
}

void Analyser::AnalyserImpl::analyseComponent(const ComponentPtr &component)
{
    // Retrieve the math string associated with the given component and analyse
    // it, one equation at a time, keeping in mind that it may consist of
    // several <math> elements, hence our use of multiRootXml().

    if (!component->math().empty()) {
        for (const auto &doc : multiRootXml(component->math())) {
            for (auto node = doc->rootNode()->firstChild(); node != nullptr; node = node->next()) {
                if (node->isMathmlElement()) {
                    // Create and keep track of the equation associated with the
                    // given node.

                    auto internalEquation = std::shared_ptr<AnalyserInternalEquation> {new AnalyserInternalEquation {component}};

                    mInternalEquations.push_back(internalEquation);

                    // Actually analyse the node.

                    analyseNode(node, internalEquation->mAst, internalEquation->mAst->parent(), component, internalEquation);
                }
            }
        }
    }

    // Go through the given component's variables and make sure that everything
    // makes sense.

    for (size_t i = 0; i < component->variableCount(); ++i) {
        // Retrieve the variable's corresponding internal variable.

        auto variable = component->variable(i);
        auto internalVariable = Analyser::AnalyserImpl::internalVariable(variable);

        // If `variable` has an initial value and the variable held by
        // `internalVariable` doesn't, then replace the variable held by
        // `internalVariable`. If `variable` and the variable held by
        // `internalVariable` are different and both of them have an initial
        // value then generate an error.

        if (!variable->initialValue().empty()
            && internalVariable->mVariable->initialValue().empty()) {
            internalVariable->setVariable(variable);
        } else if ((variable != internalVariable->mVariable)
                   && !variable->initialValue().empty()
                   && !internalVariable->mVariable->initialValue().empty()) {
            auto issue = Issue::create();
            auto trackedVariableComponent = owningComponent(internalVariable->mVariable);

            issue->setDescription("Variable '" + variable->name()
                                  + "' in component '" + component->name()
                                  + "' and variable '" + internalVariable->mVariable->name()
                                  + "' in component '" + trackedVariableComponent->name()
                                  + "' are equivalent and cannot therefore both be initialised.");
            issue->setReferenceRule(Issue::ReferenceRule::ANALYSER_VARIABLE_INITIALISED_MORE_THAN_ONCE);
            issue->setVariable(variable);

            mAnalyser->addIssue(issue);
        }

        if (!internalVariable->mVariable->initialValue().empty()
            && !isCellMLReal(internalVariable->mVariable->initialValue())) {
            // The initial value is not a double, so it has to be an existing
            // variable of constant type.
            // Note: we always have an initialising variable. Indeed, if we were
            //       not to have one, it would mean that the variable is
            //       initialised using a reference to a variable that is not
            //       defined anywhere, something that is not allowed in CellML
            //       and will therefore be reported when we validate the model.

            auto initialisingComponent = owningComponent(internalVariable->mVariable);
            auto initialisingVariable = initialisingComponent->variable(internalVariable->mVariable->initialValue());
            auto initialisingInternalVariable = Analyser::AnalyserImpl::internalVariable(initialisingVariable);

            if (initialisingInternalVariable->mType != AnalyserInternalVariable::Type::CONSTANT) {
                auto issue = Issue::create();

                issue->setDescription("Variable '" + variable->name()
                                      + "' in component '" + component->name()
                                      + "' is initialised using variable '" + internalVariable->mVariable->initialValue()
                                      + "', which is not a constant.");
                issue->setReferenceRule(Issue::ReferenceRule::ANALYSER_VARIABLE_NON_CONSTANT_INITIALISATION);
                issue->setVariable(variable);

                mAnalyser->addIssue(issue);
            }
        }
    }

    // Do the same for the components encapsulated by the given component.

    for (size_t i = 0; i < component->componentCount(); ++i) {
        analyseComponent(component->component(i));
    }
}

void Analyser::AnalyserImpl::doEquivalentVariables(const VariablePtr &variable,
                                                   std::vector<VariablePtr> &equivalentVariables) const
{
    for (size_t i = 0; i < variable->equivalentVariableCount(); ++i) {
        auto equivalentVariable = variable->equivalentVariable(i);

        if (std::find(equivalentVariables.begin(), equivalentVariables.end(), equivalentVariable) == equivalentVariables.end()) {
            equivalentVariables.push_back(equivalentVariable);

            doEquivalentVariables(equivalentVariable, equivalentVariables);
        }
    }
}

std::vector<VariablePtr> Analyser::AnalyserImpl::equivalentVariables(const VariablePtr &variable) const
{
    std::vector<VariablePtr> res = {variable};

    doEquivalentVariables(variable, res);

    return res;
}

void Analyser::AnalyserImpl::analyseEquationAst(const AnalyserEquationAstPtr &ast)
{
    // Look for the definition of a variable of integration and make sure that
    // we don't have more than one of it and that it's not initialised.

    auto astParent = ast->parent();
    auto astGrandParent = (astParent != nullptr) ? astParent->parent() : nullptr;
    auto astGreatGrandParent = (astGrandParent != nullptr) ? astGrandParent->parent() : nullptr;

    if ((ast->mPimpl->mType == AnalyserEquationAst::Type::CI)
        && (astParent != nullptr) && (astParent->mPimpl->mType == AnalyserEquationAst::Type::BVAR)
        && (astGrandParent != nullptr) && (astGrandParent->mPimpl->mType == AnalyserEquationAst::Type::DIFF)) {
        auto variable = ast->variable();

        internalVariable(variable)->makeVoi();
        // Note: we must make the variable a variable of integration in all
        //       cases (i.e. even if there is, for example, already another
        //       variable of integration) otherwise unnecessary issue messages
        //       may be reported (since the type of the variable would be
        //       unknown).

        if (mModel->mPimpl->mVoi == nullptr) {
            // We have found our variable of integration, but this may not be
            // the one defined in our first component (i.e. the component under
            // which we are likely to expect to see the variable of integration
            // to be defined), so go through our components and look for the
            // first occurrence of our variable of integration.

            auto model = owningModel(variable);

            for (size_t i = 0; i < model->componentCount(); ++i) {
                auto voi = voiFirstOccurrence(variable, model->component(i));

                if (voi != nullptr) {
                    // We have found the first occurrence of our variable of
                    // integration, but now we must ensure neither it (nor any
                    // of its equivalent variables) is initialised.

                    bool isVoiInitialised = false;

                    for (const auto &voiEquivalentVariable : equivalentVariables(voi)) {
                        if (!voiEquivalentVariable->initialValue().empty()) {
                            auto issue = Issue::create();

                            issue->setDescription("Variable '" + voiEquivalentVariable->name()
                                                  + "' in component '" + owningComponent(voiEquivalentVariable)->name()
                                                  + "' cannot be both a variable of integration and initialised.");
                            issue->setReferenceRule(Issue::ReferenceRule::ANALYSER_VOI_INITIALISED);
                            issue->setVariable(voiEquivalentVariable);

                            mAnalyser->addIssue(issue);

                            isVoiInitialised = true;
                        }
                    }

                    if (!isVoiInitialised) {
                        mModel->mPimpl->mVoi = std::shared_ptr<AnalyserVariable> {new AnalyserVariable {}};

                        mModel->mPimpl->mVoi->mPimpl->populate(AnalyserVariable::Type::VARIABLE_OF_INTEGRATION,
                                                               0, nullptr, voi, nullptr);
                    }

                    break;
                }
            }
        } else if (!mModel->areEquivalentVariables(variable, mModel->mPimpl->mVoi->variable())) {
            auto issue = Issue::create();

            issue->setDescription("Variable '" + mModel->mPimpl->mVoi->variable()->name()
                                  + "' in component '" + owningComponent(mModel->mPimpl->mVoi->variable())->name()
                                  + "' and variable '" + variable->name()
                                  + "' in component '" + owningComponent(variable)->name()
                                  + "' cannot both be the variable of integration.");
            issue->setReferenceRule(Issue::ReferenceRule::ANALYSER_VOI_SEVERAL);
            issue->setVariable(variable);

            mAnalyser->addIssue(issue);
        }
    }

    // Make sure that we only use first-order ODEs.

    if ((ast->mPimpl->mType == AnalyserEquationAst::Type::CN)
        && (astParent != nullptr) && (astParent->mPimpl->mType == AnalyserEquationAst::Type::DEGREE)
        && (astGrandParent != nullptr) && (astGrandParent->mPimpl->mType == AnalyserEquationAst::Type::BVAR)
        && (astGreatGrandParent != nullptr) && (astGreatGrandParent->mPimpl->mType == AnalyserEquationAst::Type::DIFF)) {
        double value;

        if (!convertToDouble(ast->mPimpl->mValue, value) || !areEqual(value, 1.0)) {
            auto issue = Issue::create();
            auto variable = astGreatGrandParent->mPimpl->mOwnedRightChild->variable();

            issue->setDescription("The differential equation for variable '" + variable->name()
                                  + "' in component '" + owningComponent(variable)->name()
                                  + "' must be of the first order.");
            issue->setMath(owningComponent(variable));
            issue->setReferenceRule(Issue::ReferenceRule::ANALYSER_ODE_NOT_FIRST_ORDER);

            mAnalyser->addIssue(issue);
        }
    }

    // Make a variable a state if it is used in an ODE.

    if ((ast->mPimpl->mType == AnalyserEquationAst::Type::CI)
        && (astParent != nullptr) && (astParent->mPimpl->mType == AnalyserEquationAst::Type::DIFF)) {
        internalVariable(ast->variable())->makeState();
    }

    // Recursively check the given AST's children.

    if (ast->mPimpl->mOwnedLeftChild != nullptr) {
        analyseEquationAst(ast->mPimpl->mOwnedLeftChild);
    }

    if (ast->mPimpl->mOwnedRightChild != nullptr) {
        analyseEquationAst(ast->mPimpl->mOwnedRightChild);
    }
}

double Analyser::AnalyserImpl::scalingFactor(const VariablePtr &variable)
{
    return Units::scalingFactor(variable->units(), internalVariable(variable)->mVariable->units());
}

void Analyser::AnalyserImpl::scaleAst(const AnalyserEquationAstPtr &ast,
                                      const AnalyserEquationAstPtr &astParent,
                                      double scalingFactor)
{
    // Scale the given AST using the given scaling factor.

    auto scaledAst = AnalyserEquationAst::create();

    scaledAst->mPimpl->populate(AnalyserEquationAst::Type::TIMES, astParent);

    scaledAst->mPimpl->mOwnedLeftChild = AnalyserEquationAst::create();
    scaledAst->mPimpl->mOwnedRightChild = ast;

    scaledAst->mPimpl->mOwnedLeftChild->mPimpl->populate(AnalyserEquationAst::Type::CN, convertToString(scalingFactor), scaledAst);

    ast->mPimpl->mParent = scaledAst;

    if (astParent->mPimpl->mOwnedLeftChild == ast) {
        astParent->mPimpl->mOwnedLeftChild = scaledAst;
    } else {
        astParent->mPimpl->mOwnedRightChild = scaledAst;
    }
}

void Analyser::AnalyserImpl::scaleEquationAst(const AnalyserEquationAstPtr &ast)
{
    // Make sure that we have an AST to scale.

    if (ast == nullptr) {
        return;
    }

    // Recursively scale the given AST's children.

    if (ast->mPimpl->mOwnedLeftChild != nullptr) {
        scaleEquationAst(ast->mPimpl->mOwnedLeftChild);
    }

    if (ast->mPimpl->mOwnedRightChild != nullptr) {
        scaleEquationAst(ast->mPimpl->mOwnedRightChild);
    }

    // If the given AST node is a variable (i.e. a CI node) then we may need to
    // do some scaling.

    if (ast->mPimpl->mType == AnalyserEquationAst::Type::CI) {
        // The kind of scaling we may end up doing depends on whether we are
        // dealing with a rate or some other variable, i.e. whether or not it
        // has a DIFF node as a parent.

        auto astParent = ast->parent();

        if (astParent->mPimpl->mType == AnalyserEquationAst::Type::DIFF) {
            // We are dealing with a rate, so retrieve the scaling factor for
            // its corresponding variable of integration and apply it, if
            // needed.

            auto scalingFactor = Analyser::AnalyserImpl::scalingFactor(astParent->mPimpl->mOwnedLeftChild->mPimpl->mOwnedLeftChild->variable());

            if (!areEqual(scalingFactor, 1.0)) {
                // We need to scale using the inverse of the scaling factor, but
                // how we do it depends on whether the rate is to be computed or
                // used.

                auto astGrandParent = astParent->parent();

                if ((astGrandParent->mPimpl->mType == AnalyserEquationAst::Type::ASSIGNMENT)
                    && (astGrandParent->mPimpl->mOwnedLeftChild == astParent)) {
                    scaleAst(astGrandParent->mPimpl->mOwnedRightChild, astGrandParent, 1.0 / scalingFactor);
                } else {
                    scaleAst(astParent, astGrandParent, 1.0 / scalingFactor);
                }
            }
        }

        if (((astParent->mPimpl->mType != AnalyserEquationAst::Type::ASSIGNMENT)
             || (astParent->mPimpl->mOwnedLeftChild != ast))
            && (astParent->mPimpl->mType != AnalyserEquationAst::Type::BVAR)) {
            // We are dealing with a variable which is neither a computed
            // variable nor our variable of integration, so retrieve its scaling
            // factor and apply it, if needed, distinguishing between a rate
            // variable and an algebraic variable.

            auto scalingFactor = Analyser::AnalyserImpl::scalingFactor(ast->variable());

            if (!areEqual(scalingFactor, 1.0)) {
                if (astParent->mPimpl->mType == AnalyserEquationAst::Type::DIFF) {
                    scaleAst(astParent, astParent->parent(), scalingFactor);
                } else {
                    scaleAst(ast, astParent, scalingFactor);
                }
            }
        }
    }
}

bool Analyser::AnalyserImpl::isStateRateBased(const AnalyserEquationPtr &equation,
                                              std::vector<AnalyserEquationPtr> &checkedEquations)
{
    if (std::find(checkedEquations.begin(), checkedEquations.end(), equation) != checkedEquations.end()) {
        return false;
    }

    checkedEquations.push_back(equation);

    for (const auto &dependency : equation->dependencies()) {
        if ((dependency->type() == AnalyserEquation::Type::RATE)
            || isStateRateBased(dependency, checkedEquations)) {
            return true;
        }
    }

    return false;
}

void Analyser::AnalyserImpl::analyseModel(const ModelPtr &model)
{
    // Reset a few things in case this analyser was to be used to analyse more
    // than one model.

    mAnalyser->removeAllIssues();

    mModel = std::shared_ptr<AnalyserModel> {new AnalyserModel {}};

    mInternalVariables.clear();
    mInternalEquations.clear();

    // Recursively analyse the model's components, so that we end up with an AST
    // for each of the model's equations.

    for (size_t i = 0; i < model->componentCount(); ++i) {
        analyseComponent(model->component(i));
    }

    // Some more analysis is needed, but it can only be done if we didn't come
    // across any errors during the analysis of our components.

    if (mAnalyser->errorCount() == 0) {
        // Analyse our different equations' AST to determine the type of our
        // variables.

        for (const auto &internalEquation : mInternalEquations) {
            analyseEquationAst(internalEquation->mAst);
        }
    }

    // Some post-analysis is now needed, but it can only be done if we didn't
    // come across any errors during the analysis of our equations' AST.

    if (mAnalyser->errorCount() == 0) {
        // Sort our variables, determine the index of our constant variables and
        // then loop over our equations, checking which variables, if any, can
        // be determined using a given equation.

        std::sort(mInternalVariables.begin(), mInternalVariables.end(),
                  compareVariablesByComponentAndName);

        auto variableIndex = MAX_SIZE_T;

        for (const auto &internalVariable : mInternalVariables) {
            if (internalVariable->mType == AnalyserInternalVariable::Type::CONSTANT) {
                internalVariable->mIndex = ++variableIndex;
            }
        }

        auto equationOrder = MAX_SIZE_T;
        auto stateIndex = MAX_SIZE_T;
        bool relevantCheck;

        do {
            relevantCheck = false;

            for (const auto &internalEquation : mInternalEquations) {
                relevantCheck = internalEquation->check(equationOrder, stateIndex, variableIndex, mModel)
                                || relevantCheck;
            }
        } while (relevantCheck);

        // Make sure that our variables are valid.

        for (const auto &internalVariable : mInternalVariables) {
            std::string issueType;
            Issue::ReferenceRule referenceRule = Issue::ReferenceRule::UNSPECIFIED;

            if (internalVariable->mType == AnalyserInternalVariable::Type::UNKNOWN) {
                issueType = "is unused";
                referenceRule = Issue::ReferenceRule::ANALYSER_VARIABLE_UNUSED;
            } else if (internalVariable->mType == AnalyserInternalVariable::Type::SHOULD_BE_STATE) {
                issueType = "is used in an ODE, but it is not initialised";
                referenceRule = Issue::ReferenceRule::ANALYSER_STATE_NOT_INITIALISED;
            } else if (internalVariable->mType == AnalyserInternalVariable::Type::OVERCONSTRAINED) {
                issueType = "is computed more than once";
                referenceRule = Issue::ReferenceRule::ANALYSER_VARIABLE_COMPUTED_MORE_THAN_ONCE;
            }

            if (!issueType.empty()) {
                auto issue = Issue::create();
                auto realVariable = internalVariable->mVariable;

                issue->setDescription("Variable '" + realVariable->name()
                                      + "' in component '" + owningComponent(realVariable)->name()
                                      + "' " + issueType + ".");
                issue->setReferenceRule(referenceRule);
                issue->setVariable(realVariable);

                mAnalyser->addIssue(issue);
            }
        }

        // Determine the type of our model.

        auto hasUnderconstrainedVariables = std::find_if(mInternalVariables.begin(), mInternalVariables.end(), [](const AnalyserInternalVariablePtr &variable) {
                                                return (variable->mType == AnalyserInternalVariable::Type::UNKNOWN)
                                                       || (variable->mType == AnalyserInternalVariable::Type::SHOULD_BE_STATE);
                                            })
                                            != std::end(mInternalVariables);
        auto hasOverconstrainedVariables = std::find_if(mInternalVariables.begin(), mInternalVariables.end(), [](const AnalyserInternalVariablePtr &variable) {
                                               return variable->mType == AnalyserInternalVariable::Type::OVERCONSTRAINED;
                                           })
                                           != std::end(mInternalVariables);

        if (hasUnderconstrainedVariables) {
            if (hasOverconstrainedVariables) {
                mModel->mPimpl->mType = AnalyserModel::Type::UNSUITABLY_CONSTRAINED;
            } else {
                mModel->mPimpl->mType = AnalyserModel::Type::UNDERCONSTRAINED;
            }
        } else if (hasOverconstrainedVariables) {
            mModel->mPimpl->mType = AnalyserModel::Type::OVERCONSTRAINED;
        } else if (mModel->mPimpl->mVoi != nullptr) {
            mModel->mPimpl->mType = AnalyserModel::Type::ODE;
        } else if (!mInternalVariables.empty()) {
            mModel->mPimpl->mType = AnalyserModel::Type::ALGEBRAIC;
        }
    } else {
        mModel->mPimpl->mType = AnalyserModel::Type::INVALID;
    }

    // Some final post-analysis is now needed, if we have a valid model.

    if ((mModel->mPimpl->mType == AnalyserModel::Type::ODE)
        || (mModel->mPimpl->mType == AnalyserModel::Type::ALGEBRAIC)) {
        // Add a dummy equation for each of our true (i.e. non-computed)
        // constants.
        // Note: this is only so that we can mark a constant as an external
        //       variable.

        for (const auto &internalVariable : mInternalVariables) {
            if (internalVariable->mType == AnalyserInternalVariable::Type::CONSTANT) {
                mInternalEquations.push_back(std::shared_ptr<AnalyserInternalEquation> {new AnalyserInternalEquation {internalVariable}});
            }
        }

        // Mark some variables as external variables, if needed.

        std::map<AnalyserInternalVariablePtr, std::vector<VariablePtr>> externalVariables;

        if (!mExternalVariables.empty()) {
            // Check whether an external variable belongs to the model being
            // analysed, or whether it is marked as an external variable more
            // than once through equivalence or is (equivalent to) the variable
            // of integration.

            std::map<VariablePtr, std::vector<VariablePtr>> primaryExternalVariables;

            for (const auto &externalVariable : mExternalVariables) {
                auto variable = externalVariable->variable();

                if (variable != nullptr) {
                    if (owningModel(variable) != model) {
                        auto issue = Issue::create();

                        issue->setDescription("Variable '" + variable->name()
                                              + "' in component '" + owningComponent(variable)->name()
                                              + "' is marked as an external variable, but it belongs to a different model and will therefore be ignored.");
                        issue->setLevel(Issue::Level::MESSAGE);
                        issue->setReferenceRule(Issue::ReferenceRule::ANALYSER_EXTERNAL_VARIABLE_DIFFERENT_MODEL);
                        issue->setVariable(variable);

                        mAnalyser->addIssue(issue);
                    } else {
                        auto internalVariable = AnalyserImpl::internalVariable(variable);

                        primaryExternalVariables[internalVariable->mVariable].push_back(variable);

                        if (((mModel->mPimpl->mVoi == nullptr)
                             || (internalVariable->mVariable != mModel->mPimpl->mVoi->variable()))
                            && (externalVariables.count(internalVariable) == 0)) {
                            std::vector<VariablePtr> dependencies;

                            for (const auto &dependency : externalVariable->dependencies()) {
                                dependencies.push_back(AnalyserImpl::internalVariable(dependency)->mVariable);
                            }

                            externalVariables[internalVariable] = dependencies;
                        }
                    }
                }
            }

            for (const auto &primaryExternalVariable : primaryExternalVariables) {
                std::string description;
                auto isVoi = (mModel->mPimpl->mVoi != nullptr)
                             && (primaryExternalVariable.first == mModel->mPimpl->mVoi->variable());
                auto equivalentVariableCount = primaryExternalVariable.second.size();
                auto hasPrimaryVariable = std::find(primaryExternalVariable.second.begin(),
                                                    primaryExternalVariable.second.end(),
                                                    primaryExternalVariable.first)
                                          != primaryExternalVariable.second.end();

                if (isVoi || (equivalentVariableCount > 1) || !hasPrimaryVariable) {
                    description += (equivalentVariableCount == 2) ? "Both " : "";

                    for (size_t i = 0; i < equivalentVariableCount; ++i) {
                        if (i != 0) {
                            description += (i != equivalentVariableCount - 1) ? ", " : " and ";
                        }

                        auto variableString = ((i == 0) && (equivalentVariableCount != 2)) ? std::string("Variable") : std::string("variable");

                        description += variableString + " '" + primaryExternalVariable.second[i]->name()
                                       + "' in component '" + owningComponent(primaryExternalVariable.second[i])->name()
                                       + "'";
                    }

                    Issue::ReferenceRule referenceRule;

                    if (isVoi) {
                        description += (equivalentVariableCount == 1) ?
                                           " is marked as an external variable, but it is" :
                                           " are marked as external variables, but they are";

                        if ((equivalentVariableCount == 1) && hasPrimaryVariable) {
                            description += " the";
                        } else {
                            description += " equivalent to variable '" + primaryExternalVariable.first->name()
                                           + "' in component '" + owningComponent(primaryExternalVariable.first)->name()
                                           + "', the primary";
                        }

                        description += " variable of integration which cannot be used as an external variable.";

                        referenceRule = Issue::ReferenceRule::ANALYSER_EXTERNAL_VARIABLE_VOI;
                    } else {
                        description += (equivalentVariableCount == 1) ?
                                           " is marked as an external variable, but it is not a primary variable." :
                                           " are marked as external variables, but they are";
                        description += (equivalentVariableCount > 2) ? " all" : "";
                        description += (equivalentVariableCount == 1) ? "" : " equivalent.";
                        description += " Variable '" + primaryExternalVariable.first->name()
                                       + "' in component '" + owningComponent(primaryExternalVariable.first)->name()
                                       + "' is";
                        description += hasPrimaryVariable ?
                                           " the" :
                                       (equivalentVariableCount == 1) ?
                                           " its corresponding" :
                                           " their corresponding";
                        description += " primary variable and will therefore be the one used as an external variable.";

                        referenceRule = Issue::ReferenceRule::ANALYSER_EXTERNAL_VARIABLE_USE_PRIMARY_VARIABLE;
                    }

                    auto issue = Issue::create();

                    issue->setDescription(description);
                    issue->setLevel(Issue::Level::MESSAGE);
                    issue->setReferenceRule(referenceRule);
                    issue->setVariable(primaryExternalVariable.first);

                    mAnalyser->addIssue(issue);
                }
            }
        }

        // Carry on, but only if there are no errors (i.e. warnings are fine).

        if (mAnalyser->errorCount() == 0) {
            // Make it known through our API whether the model has some external
            // variables.

            mModel->mPimpl->mHasExternalVariables = !externalVariables.empty();

            // Sort our internal variables and equations.

            std::sort(mInternalVariables.begin(), mInternalVariables.end(),
                      compareVariablesByTypeAndIndex);
            std::sort(mInternalEquations.begin(), mInternalEquations.end(),
                      compareEquationsByVariable);

            std::map<VariablePtr, AnalyserEquationPtr> equationMappings;
            std::map<AnalyserEquationPtr, AnalyserVariablePtr> variableMappings;

            for (const auto &internalEquation : mInternalEquations) {
                equationMappings[internalEquation->mVariable->mVariable] = std::shared_ptr<AnalyserEquation> {new AnalyserEquation {}};
            }

            // Make our internal variables available through our API.

            auto stateIndex = MAX_SIZE_T;
            auto variableIndex = MAX_SIZE_T;

            for (const auto &internalVariable : mInternalVariables) {
                // Determine the type of the variable.

                AnalyserVariable::Type type;

                if (externalVariables.count(internalVariable) == 1) {
                    type = AnalyserVariable::Type::EXTERNAL;
                } else if (internalVariable->mType == AnalyserInternalVariable::Type::STATE) {
                    type = AnalyserVariable::Type::STATE;
                } else if (internalVariable->mType == AnalyserInternalVariable::Type::CONSTANT) {
                    type = AnalyserVariable::Type::CONSTANT;
                } else if ((internalVariable->mType == AnalyserInternalVariable::Type::COMPUTED_TRUE_CONSTANT)
                           || (internalVariable->mType == AnalyserInternalVariable::Type::COMPUTED_VARIABLE_BASED_CONSTANT)) {
                    type = AnalyserVariable::Type::COMPUTED_CONSTANT;
                } else if (internalVariable->mType == AnalyserInternalVariable::Type::ALGEBRAIC) {
                    type = AnalyserVariable::Type::ALGEBRAIC;
                } else {
                    // This is the variable of integration, so skip it.

                    continue;
                }

                // Populate and keep track of the state/variable.

                auto stateOrVariable = std::shared_ptr<AnalyserVariable> {new AnalyserVariable {}};
                auto equation = equationMappings[internalVariable->mVariable];

                stateOrVariable->mPimpl->populate(type,
                                                  (type == AnalyserVariable::Type::STATE) ?
                                                      ++stateIndex :
                                                      ++variableIndex,
                                                  (type == AnalyserVariable::Type::EXTERNAL) ?
                                                      nullptr :
                                                      internalVariable->mInitialisingVariable,
                                                  internalVariable->mVariable,
                                                  equation);

                variableMappings[equation] = stateOrVariable;

                if (type == AnalyserVariable::Type::STATE) {
                    mModel->mPimpl->mStates.push_back(stateOrVariable);
                } else {
                    mModel->mPimpl->mVariables.push_back(stateOrVariable);
                }
            }

            // Make our internal equations available through our API.

            for (const auto &internalEquation : mInternalEquations) {
                // Determine the type of the equation.

                auto equation = equationMappings[internalEquation->mVariable->mVariable];
                auto stateOrVariable = variableMappings[equation];
                AnalyserEquation::Type type;

                if (stateOrVariable->type() == AnalyserVariable::Type::EXTERNAL) {
                    type = AnalyserEquation::Type::EXTERNAL;
                } else if (internalEquation->mType == AnalyserInternalEquation::Type::TRUE_CONSTANT) {
                    type = AnalyserEquation::Type::TRUE_CONSTANT;
                } else if (internalEquation->mType == AnalyserInternalEquation::Type::VARIABLE_BASED_CONSTANT) {
                    type = AnalyserEquation::Type::VARIABLE_BASED_CONSTANT;
                } else if (internalEquation->mType == AnalyserInternalEquation::Type::RATE) {
                    type = AnalyserEquation::Type::RATE;
                } else if (internalEquation->mType == AnalyserInternalEquation::Type::ALGEBRAIC) {
                    type = AnalyserEquation::Type::ALGEBRAIC;
                } else {
                    // The equation type is unknown, which means that it is a
                    // dummy equation for a true (i.e. non-computed) constant
                    // (so that it could have been marked as an external
                    // variable), so we skip it since the constant wasn't marked
                    // as an external variable.

                    continue;
                }

                // Scale our internal equation's AST to take into account the
                // fact that we may have mapped variables that use compatible
                // units rather than equivalent ones.

                scaleEquationAst(internalEquation->mAst);

                // Determine the equation's dependencies, i.e. the equations for
                // the variables on which this equation depends.
                // Note: an equation may depend on the variable of integration,
                //       for which there is no equation, hence we need to test
                //       equationDependency against nullptr.

                std::vector<VariablePtr> variableDependencies = (type == AnalyserEquation::Type::EXTERNAL) ?
                                                                    externalVariables.find(internalEquation->mVariable)->second :
                                                                    internalEquation->mDependencies;
                std::vector<AnalyserEquationPtr> equationDependencies;

                for (const auto &variableDependency : variableDependencies) {
                    auto equationDependency = equationMappings[variableDependency];

                    if (equationDependency != nullptr) {
                        equationDependencies.push_back(equationDependency);
                    }
                }

                // Populate and keep track of the equation.

                equation->mPimpl->populate(type,
                                           (type == AnalyserEquation::Type::EXTERNAL) ?
                                               nullptr :
                                               internalEquation->mAst,
                                           equationDependencies,
                                           stateOrVariable);

                mModel->mPimpl->mEquations.push_back(equation);
            }

            // Clean up our equations' dependencies.
            // Note: indeed, some equations may have a dependency on one or
            //       several true (i.e. non-computed) constants, for which there
            //       are no proper equations. So, we need to remove those
            //       dependencies, and obviously this can only be done once all
            //       our equations are ready.

            for (const auto &equation : mModel->mPimpl->mEquations) {
                equation->mPimpl->cleanUpDependencies();
            }

            // Determine whether our equations are state/rate based.
            // Note: obviously, this can only be done once all our equations are
            //       ready.

            for (const auto &equation : mModel->mPimpl->mEquations) {
                std::vector<AnalyserEquationPtr> checkedEquations;

                equation->mPimpl->mIsStateRateBased = isStateRateBased(equation, checkedEquations);
            }
        }
    }
}

std::vector<AnalyserExternalVariablePtr>::iterator Analyser::AnalyserImpl::findExternalVariable(const ModelPtr &model,
                                                                                                const std::string &componentName,
                                                                                                const std::string &variableName)
{
    return std::find_if(mExternalVariables.begin(), mExternalVariables.end(), [=](const AnalyserExternalVariablePtr &ev) {
        auto v = ev->variable();

        return (v != nullptr)
               && (owningModel(v) == model)
               && (owningComponent(v)->name() == componentName)
               && (v->name() == variableName);
    });
}

std::vector<AnalyserExternalVariablePtr>::iterator Analyser::AnalyserImpl::findExternalVariable(const AnalyserExternalVariablePtr &externalVariable)
{
    return std::find_if(mExternalVariables.begin(), mExternalVariables.end(), [=](const AnalyserExternalVariablePtr &ev) {
        return ev == externalVariable;
    });
}

Analyser::Analyser()
    : mPimpl(new AnalyserImpl {this})
{
}

Analyser::~Analyser()
{
    delete mPimpl;
}

AnalyserPtr Analyser::create() noexcept
{
    return std::shared_ptr<Analyser> {new Analyser {}};
}

void Analyser::analyseModel(const ModelPtr &model)
{
    // Make sure that we have a model and that it is valid before analysing it.

    if (model == nullptr) {
        return;
    }

    auto validator = Validator::create();

    validator->validateModel(model);

    if (validator->issueCount() > 0) {
        // The model is not valid, so retrieve the validation issues and make
        // them our own.

        for (size_t i = 0; i < validator->issueCount(); ++i) {
            addIssue(validator->issue(i));
        }

        mPimpl->mModel->mPimpl->mType = AnalyserModel::Type::INVALID;

        return;
    }

    // Analyse the model.

    mPimpl->analyseModel(model);
}

bool Analyser::addExternalVariable(const AnalyserExternalVariablePtr &externalVariable)
{
    if (std::find(mPimpl->mExternalVariables.begin(), mPimpl->mExternalVariables.end(), externalVariable) == mPimpl->mExternalVariables.end()) {
        mPimpl->mExternalVariables.push_back(externalVariable);

        return true;
    }

    return false;
}

bool Analyser::removeExternalVariable(size_t index)
{
    if (index < mPimpl->mExternalVariables.size()) {
        mPimpl->mExternalVariables.erase(mPimpl->mExternalVariables.begin() + int64_t(index));

        return true;
    }

    return false;
}

bool Analyser::removeExternalVariable(const ModelPtr &model,
                                      const std::string &componentName,
                                      const std::string &variableName)
{
    auto result = mPimpl->findExternalVariable(model, componentName, variableName);

    if (result != mPimpl->mExternalVariables.end()) {
        mPimpl->mExternalVariables.erase(result);

        return true;
    }

    return false;
}

bool Analyser::removeExternalVariable(const AnalyserExternalVariablePtr &externalVariable)
{
    auto result = mPimpl->findExternalVariable(externalVariable);

    if (result != mPimpl->mExternalVariables.end()) {
        mPimpl->mExternalVariables.erase(result);

        return true;
    }

    return false;
}

void Analyser::removeAllExternalVariables()
{
    mPimpl->mExternalVariables.clear();
}

bool Analyser::containsExternalVariable(const ModelPtr &model,
                                        const std::string &componentName,
                                        const std::string &variableName) const
{
    return mPimpl->findExternalVariable(model, componentName, variableName) != mPimpl->mExternalVariables.end();
}

bool Analyser::containsExternalVariable(const AnalyserExternalVariablePtr &externalVariable) const
{
    return mPimpl->findExternalVariable(externalVariable) != mPimpl->mExternalVariables.end();
}

AnalyserExternalVariablePtr Analyser::externalVariable(size_t index) const
{
    if (index < mPimpl->mExternalVariables.size()) {
        return mPimpl->mExternalVariables.at(index);
    }

    return nullptr;
}

AnalyserExternalVariablePtr Analyser::externalVariable(const ModelPtr &model,
                                                       const std::string &componentName,
                                                       const std::string &variableName) const
{
    auto result = mPimpl->findExternalVariable(model, componentName, variableName);

    if (result != mPimpl->mExternalVariables.end()) {
        return *result;
    }

    return nullptr;
}

size_t Analyser::externalVariableCount() const
{
    return mPimpl->mExternalVariables.size();
}

AnalyserModelPtr Analyser::model() const
{
    return mPimpl->mModel;
}

/*
// This comment holds the changes done to the validator which were to be used in the analyser class.
void processEquationAst(const GeneratorEquationAstPtr &ast);
void processEquationUnits(const GeneratorEquationAstPtr &ast); // in the private declaration


// The call when processing the model in the generator
if (mGenerator->errorCount() == 0) {
        for (const auto &equation : mEquations) {
            processEquationUnits(equation->mAst);
        }
}


// The main AST construction also had a few elements where the CellML markup had to be analysed.
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


// Everything from here down was used to check the units within each equation model.

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
           || (type == libcellml::GeneratorEquationAst::Type::MAX)
           || (type == libcellml::GeneratorEquationAst::Type::AND)
           || (type == libcellml::GeneratorEquationAst::Type::OR)
           || (type == libcellml::GeneratorEquationAst::Type::NOT)
           || (type == libcellml::GeneratorEquationAst::Type::XOR)
           || (type == libcellml::GeneratorEquationAst::Type::PIECEWISE);
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

bool isBoundVariableOperator(const GeneratorEquationAstPtr &ast)
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
                         const std::string &uName,
                         double uExp, double logMult)
{
    if (isStandardUnitName(uName)) {
        for (const auto &iter : standardUnitsList.at(uName)) {
            if (unitMap.find(iter.first) == unitMap.end()) {
                unitMap.emplace(std::pair<std::string, double>(iter.first, 0.0));
            }
            unitMap.at(iter.first) += (iter.second * uExp);
        }
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
                    updateBaseUnitCount(model, unitMap, ref, exp * uExp, logMult + mult * uExp + standardPrefixList.at(pre) * uExp);
                } else {
                    for (const auto &iter : standardUnitsList.at(ref)) {
                        if (unitMap.find(iter.first) == unitMap.end()) {
                            unitMap.emplace(std::pair<std::string, double>(iter.first, 0.0));
                        }
                        unitMap.at(iter.first) += (iter.second * exp * uExp);
                    }
                }
            }
        }

        // Leaving this as a comment for the moment: This would only be necessary if we had a base unit which was *not* in the standard units list - uncertain if this will ever occur within a formal model.
        else if (unitMap.find(uName) == unitMap.end()) {
            unitMap.emplace(std::pair<std::string, double>(uName, 1.0 * uExp));
        } else {
            const auto &iter = unitMap.find(uName);
            unitMap.at(iter->first) += (iter->second * uExp);
        }
    }
}

void updateBaseMultiplier(const ModelPtr &model,
                          double &multiplier,
                          const std::string &uName,
                          double uExp, double logMult)
{
    if (isStandardUnitName(uName)) {
        multiplier += (logMult + (standardMultiplierList.at(uName)));
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
                    updateBaseMultiplier(model, multiplier, ref, exp * uExp, logMult + mult * uExp + standardPrefixList.at(pre) * uExp);
                } else {
                    multiplier += (logMult + (standardMultiplierList.at(ref) + mult + standardPrefixList.at(pre)) * exp * uExp);
                }
            }
        }

        // Leaving this as a comment for the moment: This would only be necessary if we had a base unit which was *not* in the standard units list - uncertain if this will ever occur within a formal model.
        else {
            multiplier += 1.0 * logMult;
        }
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
        return 0.0; // Return 0 for case where there is a null node
    }
    if (ast->mValue.empty()) {
        // If we have a variable then we return 0 and just make sure both mappings are dimensionless
        if (ast->mLeft == nullptr && ast->mRight == nullptr) {
            return 0.0;
        }

        if (ast->mType == GeneratorEquationAst::Type::TIMES) {
            return getPower(ast->mLeft) * getPower(ast->mRight);
        }
        if (ast->mType == GeneratorEquationAst::Type::DIVIDE) {
            return (getPower(ast->mRight) != 0.0) ? getPower(ast->mLeft) / getPower(ast->mRight) : 0.0;
        }
        if (ast->mType == GeneratorEquationAst::Type::PLUS) {
            return getPower(ast->mLeft) + getPower(ast->mRight);
        }
        if (ast->mType == GeneratorEquationAst::Type::MINUS) {
            return getPower(ast->mLeft) - getPower(ast->mRight);
        }
        if (ast->mType == GeneratorEquationAst::Type::DEGREE) {
            return getPower(ast->mLeft);
        }
    }

    // In the special case where the terminating node is a variable, eliminates the possibility of making an invalid std::stod call
    if (ast->mValue.empty()) {
        return 0.0;
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
    {GeneratorEquationAst::Type::POWER, "pow"},
    {GeneratorEquationAst::Type::ROOT, "root"},
    {GeneratorEquationAst::Type::ABS, "fabs"},
    {GeneratorEquationAst::Type::EXP, "exp"},
    {GeneratorEquationAst::Type::LN, "ln"},
    {GeneratorEquationAst::Type::LOG, "log"},
    {GeneratorEquationAst::Type::CEILING, "ceil"},
    {GeneratorEquationAst::Type::FLOOR, "floor"},
    {GeneratorEquationAst::Type::MIN, "min"},
    {GeneratorEquationAst::Type::MAX, "max"},
    {GeneratorEquationAst::Type::REM, "rem"},
    {GeneratorEquationAst::Type::ASIN, "asin"},
    {GeneratorEquationAst::Type::ASINH, "asinh"},
    {GeneratorEquationAst::Type::SIN, "sin"},
    {GeneratorEquationAst::Type::SINH, "sinh"},
    {GeneratorEquationAst::Type::ACOS, "acos"},
    {GeneratorEquationAst::Type::ACOSH, "acosh"},
    {GeneratorEquationAst::Type::COS, "cos"},
    {GeneratorEquationAst::Type::COSH, "cosh"},
    {GeneratorEquationAst::Type::ATAN, "atan"},
    {GeneratorEquationAst::Type::ATANH, "atanh"},
    {GeneratorEquationAst::Type::TAN, "tan"},
    {GeneratorEquationAst::Type::TANH, "tanh"},
    {GeneratorEquationAst::Type::ASEC, "asec"},
    {GeneratorEquationAst::Type::ASECH, "asech"},
    {GeneratorEquationAst::Type::SECH, "sech"},
    {GeneratorEquationAst::Type::SEC, "sec"},
    {GeneratorEquationAst::Type::ACSC, "acsc"},
    {GeneratorEquationAst::Type::ACSCH, "acsch"},
    {GeneratorEquationAst::Type::CSC, "csc"},
    {GeneratorEquationAst::Type::CSCH, "csch"},
    {GeneratorEquationAst::Type::ACOT, "acot"},
    {GeneratorEquationAst::Type::ACOTH, "acoth"},
    {GeneratorEquationAst::Type::COT, "cot"},
    {GeneratorEquationAst::Type::COTH, "coth"}};

std::string expression(std::string first, std::string second, const GeneratorEquationAstPtr &ast)
{
    // Statement capturing all expressions which require one operand only.
    if (isTrigonometricOperator(ast) || isLogarithmicOperator(ast) || ast->mType == GeneratorEquationAst::Type::REM
        || ast->mType == GeneratorEquationAst::Type::CEILING || ast->mType == GeneratorEquationAst::Type::FLOOR
        || ast->mType == GeneratorEquationAst::Type::ABS || ast->mType == GeneratorEquationAst::Type::NOT) {
        return AstTypeToString.find(ast->mType)->second + "(" + first + ")";
    }

    // The ordering of nodes beneath a power node in the tree means we consider it as it's own case
    if (ast->mType == GeneratorEquationAst::Type::POWER) {
        return AstTypeToString.find(ast->mType)->second + "(" + first + "," + second + ")";
    }

    // Likewise for root nodes, which are constructed in the reverse order
    if (ast->mType == GeneratorEquationAst::Type::ROOT) {
        if (second.empty()) {
            second = "2";
        }
        return AstTypeToString.find(ast->mType)->second + "(" + first + "," + second + ")";
    }

    // If we have degree or logbase we just return the number
    if (ast->mType == GeneratorEquationAst::Type::LOGBASE || ast->mType == GeneratorEquationAst::Type::DEGREE) {
        return first;
    }

    // If we have an assignment operator we don't include the outer braces
    if (ast->mType == GeneratorEquationAst::Type::ASSIGNMENT) {
        return first + AstTypeToString.find(ast->mType)->second + second;
    }

    return "(" + first + AstTypeToString.find(ast->mType)->second + second + ")";
}

// Function to return the part of the equation in error as a string
std::string getEquation(const GeneratorEquationAstPtr &ast)
{
    if (ast != nullptr) {
        if (ast->mVariable != nullptr) {
            return ast->mVariable->name();
        }
        if (!ast->mValue.empty()) {
            return ast->mValue;
        }
        std::string first = getEquation(ast->mLeft);
        std::string second = getEquation(ast->mRight);
        return expression(first, second, ast);
    }
    return std::string();
}

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

UnitsMap processEquationUnitsAst(const GeneratorEquationAstPtr &ast, std::vector<std::string> &errors)
{
    UnitsMap unitMap;

    if (ast != nullptr) {
        if (ast->mLeft == nullptr && ast->mRight == nullptr) {
            ModelPtr model;
            std::string uName;

            // If we have a unit associated with the value of a number we add it to the units mapping.
            if (ast->mType == GeneratorEquationAst::Type::CN && ast->mUnits != nullptr) {
                model = owningModel(ast->mUnits);
                uName = ast->mUnits->name();
                updateBaseUnitCount(model, unitMap, uName, 1, 0);
            }

            if (ast->mType == GeneratorEquationAst::Type::CI) {
                model = (ast->mVariable != nullptr) ? owningModel(ast->mVariable) : nullptr;
                uName = (ast->mUnits != nullptr) ? ast->mUnits->name() : "dimensionless";
                if (!(uName == "dimensionless")) {
                    updateBaseUnitCount(model, unitMap, uName, 1, 0);
                }
            }
            return unitMap;
        }

        // We know if we have reached an internal vertex that we have a mathematical operation as it's type.
        if (ast->mLeft != nullptr || ast->mRight != nullptr) {
            // Evaluate left, right subtrees first
            UnitsMap leftMap = processEquationUnitsAst(ast->mLeft, errors);
            UnitsMap rightMap = processEquationUnitsAst(ast->mRight, errors);

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

                    std::string err = "The units in the expression '" + getEquation(ast)
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
                double power = 0.0;
                if (ast->mType == GeneratorEquationAst::Type::POWER) {
                    power = getPower(ast->mRight);
                } else {
                    if (ast->mLeft->mType == GeneratorEquationAst::Type::DEGREE) {
                        power = getPower(ast->mLeft);
                    } else {
                        power = getPower(ast->mRight);
                    }
                }

                //double power = getPower(ast->mRight);
                bool correctUnits = false;
                if (power == 0.0 && ast->mRight != nullptr && ast->mType == GeneratorEquationAst::Type::POWER) {
                    correctUnits = isDimensionless(leftMap) && isDimensionless(rightMap); // If we have a variable as our power both the power and the quantity it is being applied to must be dimensionless
                } else if (ast->mLeft->mType == GeneratorEquationAst::Type::DEGREE) {
                    correctUnits = isDimensionless(leftMap);
                    leftMap = rightMap;
                } else {
                    correctUnits = isDimensionless(rightMap); // Otherwise we just check the power for dimensionlessness
                }

                // If we have a square root operation
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

                    std::string err = "The units in the expression '" + getEquation(ast)
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

                    std::string err = "The units in the expression '" + getEquation(ast)
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

                    std::string err = "The argument in the expression '" + getEquation(ast)
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

            if (isBoundVariableOperator(ast)) {
                for (auto &unit : leftMap) {
                    unit.second *= -1.0; // Bottom variable will be "per" the unit on the top
                }
            }
            return leftMap;
        }
    }
    return unitMap;
}

double processEquationMultiplierAst(const GeneratorEquationAstPtr &ast, std::vector<std::string> &errors, double multiplier)
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
                updateBaseMultiplier(model, multiplier, uName, 1, 0);
            }

            if (ast->mType == GeneratorEquationAst::Type::CI) {
                model = (ast->mVariable != nullptr) ? owningModel(ast->mVariable) : nullptr;
                uName = (ast->mUnits != nullptr) ? ast->mUnits->name() : "dimensionless";
                if (!(uName == "dimensionless")) {
                    updateBaseMultiplier(model, multiplier, uName, 1, 0);
                } else {
                    multiplier = 0.0;
                }
            }
            return multiplier;
        }

        // We know if we have reached an internal vertex that we have a mathematical operation as it's type.
        if (ast->mLeft != nullptr || ast->mRight != nullptr) {
            // Evaluate left, right subtrees first
            double leftMult = processEquationMultiplierAst(ast->mLeft, errors, multiplier);
            double rightMult = processEquationMultiplierAst(ast->mRight, errors, multiplier);

            // The only time we check multiplier mismatch is in a comparision operation.
            if (isDirectComparisonOperator(ast)) {
                if (!areEqual(leftMult, rightMult) && ast->mLeft != nullptr && ast->mRight != nullptr) {
                    VariablePtr variable = getVariable(ast);
                    ComponentPtr component = (variable != nullptr) ? std::dynamic_pointer_cast<Component>(variable->parent()) : nullptr;
                    ModelPtr model = (component != nullptr) ? owningModel(component) : nullptr;
                    std::string compName = (component != nullptr) ? component->name() : "";
                    std::string modelName = (model != nullptr) ? model->name() : "";

                    std::string err = "The expression '" + getEquation(ast)
                                      + "' in component '" + compName
                                      + "' of model '" + modelName
                                      + "' has a multiplier mismatch. The mismatch is: " + std::to_string(leftMult - rightMult)
                                      + ". A variable in the expression is " + variable->name();
                    errors.push_back(err);
                }
            }

            // Otherwise for all the other cases we change the multiplier
            if (isMultiplicativeOperator(ast)) {
                if (ast->mType == GeneratorEquationAst::Type::TIMES) {
                    leftMult += rightMult;
                } else {
                    leftMult -= rightMult;
                }
            }

            if (isExponentOperator(ast)) {
                double power = (ast->mRight != nullptr) ? getPower(ast->mRight) : getPower(ast->mLeft);
                if (ast->mType == GeneratorEquationAst::Type::POWER && power != 0.0) {
                    leftMult *= power;
                } else if (ast->mType == GeneratorEquationAst::Type::ROOT) {
                    if ((ast->mRight != nullptr || ast->mLeft != nullptr) && power != 0.0) {
                        leftMult /= power;
                    } else {
                        leftMult *= 0.5;
                    }
                } else {
                    leftMult = 0.0;
                }
            }

            if (isLogarithmicOperator(ast) || isTrigonometricOperator(ast)) {
                leftMult = 0.0;
            }

            if (isDerivativeOperator(ast)) {
                leftMult = leftMult + rightMult;
            }

            if (isBoundVariableOperator(ast)) {
                leftMult = 0.0 - leftMult;
            }
            return leftMult;
        }
    }
    return multiplier;
}

// Shim function to create a contiguous void declaration in the private implementation
void Generator::GeneratorImpl::processEquationUnits(const GeneratorEquationAstPtr &ast)
{
    UnitsMap unitMap;
    std::vector<std::string> errors;
    double multiplier = 0.0;
    unitMap = processEquationUnitsAst(ast, errors);
    multiplier = processEquationMultiplierAst(ast, errors, multiplier);

    if (!errors.empty()) {
        for (const auto &error : errors) {
            ErrorPtr err = Error::create();
            err->setDescription(error);
            err->setKind(Error::Kind::UNITS);
            mGenerator->addError(err);
        }
    }
}
*/

} // namespace libcellml

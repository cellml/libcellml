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

#include <cmath>

#include "analyserequation_p.h"
#include "analyserequationast_p.h"
#include "analysermodel_p.h"
#include "analyservariable_p.h"
#include "anycellmlelement_p.h"
#include "generator_p.h"
#include "issue_p.h"
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

    VariablePtrs mDependencies;

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
using UnitsMap = std::map<std::string, double>;
using UnitsMaps = std::vector<UnitsMap>;
using UnitsMultipliers = std::vector<double>;

struct Analyser::AnalyserImpl
{
    Analyser *mAnalyser = nullptr;

    AnalyserModelPtr mModel = AnalyserModel::AnalyserModelImpl::create();
    std::vector<AnalyserExternalVariablePtr> mExternalVariables;

    std::vector<AnalyserInternalVariablePtr> mInternalVariables;
    std::vector<AnalyserInternalEquationPtr> mInternalEquations;

    GeneratorPtr mGenerator = libcellml::Generator::create();

    std::map<std::string, UnitsPtr> mStandardUnits;
    std::map<AnalyserEquationAstPtr, UnitsWeakPtr> mCiCnUnits;

    explicit AnalyserImpl(Analyser *analyser);
    ~AnalyserImpl();

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
                               VariablePtrs &equivalentVariables) const;
    VariablePtrs equivalentVariables(const VariablePtr &variable) const;

    void analyseEquationAst(const AnalyserEquationAstPtr &ast);

    void updateUnitsMapWithStandardUnit(const std::string &unitsName,
                                        UnitsMap &unitsMap,
                                        double unitsExponent);
    void updateUnitsMap(const ModelPtr &model, const std::string &unitsName,
                        UnitsMap &unitsMap, bool userUnitsMap = false,
                        double unitsExponent = 1.0,
                        double unitsMultiplier = 0.0);
    UnitsMap multiplyDivideUnitsMaps(const UnitsMap &firstUnitsMap,
                                     const UnitsMap &secondUnitsMap,
                                     bool multiply);
    UnitsMaps multiplyDivideUnitsMaps(const UnitsMaps &firstUnitsMaps,
                                      const UnitsMaps &secondUnitsMaps,
                                      bool multiply = true);
    UnitsMaps multiplyDivideUnitsMaps(const UnitsMaps &unitsMaps,
                                      double factor, bool multiply);
    double multiplyDivideUnitsMultipliers(double firstUnitsMultiplier,
                                          double secondUnitsMultiplier,
                                          bool multiply);
    UnitsMultipliers multiplyDivideUnitsMultipliers(const UnitsMultipliers &firstUnitsMultipliers,
                                                    const UnitsMultipliers &secondUnitsMultipliers,
                                                    bool multiply = true);
    UnitsMultipliers multiplyDivideUnitsMultipliers(double firstUnitsMultiplier,
                                                    const UnitsMultipliers &secondUnitsMultipliers,
                                                    bool multiply);
    UnitsMultipliers powerRootUnitsMultipliers(const UnitsMultipliers &unitsMultipliers,
                                               double factor, bool power);
    bool areSameUnitsMaps(const UnitsMaps &firstUnitsMaps,
                          const UnitsMaps &secondUnitsMaps);
    bool isDimensionlessUnitsMaps(const UnitsMaps &unitsMaps);
    bool areSameUnitsMultipliers(const UnitsMultipliers &firstUnitsMultipliers,
                                 const UnitsMultipliers &secondUnitsMultipliers);
    void updateUnitsMultiplier(const ModelPtr &model,
                               const std::string &unitsName,
                               double &newUnitsMultiplier,
                               double unitsExponent = 1.0,
                               double unitsMultiplier = 0.0);
    std::string componentName(const AnalyserEquationAstPtr &ast);
    double powerValue(const AnalyserEquationAstPtr &ast);
    std::string expression(const AnalyserEquationAstPtr &ast,
                           bool includeHierarchy = true);
    std::string expressionUnits(const UnitsMaps &unitsMaps,
                                const UnitsMultipliers &unitsMultipliers = {});
    std::string expressionUnits(const AnalyserEquationAstPtr &ast,
                                const UnitsMaps &unitsMaps,
                                const UnitsMaps &userUnitsMaps,
                                const UnitsMultipliers &unitsMultipliers);
    void defaultUnitsMapsAndMultipliers(UnitsMaps &unitsMaps,
                                        UnitsMaps &userUnitsMaps,
                                        UnitsMultipliers &unitsMultipliers);
    void analyseEquationUnits(const AnalyserEquationAstPtr &ast,
                              UnitsMaps &unitsMaps, UnitsMaps &userUnitsMaps,
                              UnitsMultipliers &unitsMultipliers,
                              Strings &issueDescriptions);

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
{
    // Customise our generator's profile.

    auto profile = mGenerator->profile();

    profile->setAbsoluteValueString("abs");
    profile->setNaturalLogarithmString("ln");
    profile->setCommonLogarithmString("log");
    profile->setRemString("rem");
    profile->setAsinString("arcsin");
    profile->setAcosString("arccos");
    profile->setAtanString("arctan");
    profile->setAsecString("arcsec");
    profile->setAcscString("arccsc");
    profile->setAcotString("arccot");
    profile->setAsinhString("arcsinh");
    profile->setAcoshString("arccosh");
    profile->setAtanhString("arctanh");
    profile->setAsechString("arcsech");
    profile->setAcschString("arccsch");
    profile->setAcothString("arccoth");
    profile->setTrueString("true");
    profile->setFalseString("false");
    profile->setEString("exponentiale");
    profile->setPiString("pi");
    profile->setInfString("infinity");
    profile->setNanString("notanumber");

    // Retrieve our generator's profile.

    mGenerator->mPimpl->retrieveLockedModelAndProfile();
}

Analyser::AnalyserImpl::~AnalyserImpl()
{
    // Reset our generator's profile.

    mGenerator->mPimpl->resetLockedModelAndProfile();
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
    // not in the MathML namespace.

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

        // Add the variable to our AST and keep track of its unit.

        ast->mPimpl->populate(AnalyserEquationAst::Type::CI, variable, astParent);

        mCiCnUnits.emplace(ast, variable->units());
    } else if (node->isMathmlElement("cn")) {
        // Add the number to our AST and keep track of its unit. Note that in
        // the case of a standard unit, we need to create a units since it's
        // not declared in the model.

        if (mathmlChildCount(node) == 1) {
            // We are dealing with an e-notation based CN value.

            ast->mPimpl->populate(AnalyserEquationAst::Type::CN, node->firstChild()->convertToStrippedString() + "e" + node->firstChild()->next()->next()->convertToStrippedString(), astParent);
        } else {
            ast->mPimpl->populate(AnalyserEquationAst::Type::CN, node->firstChild()->convertToStrippedString(), astParent);
        }

        std::string unitsName = node->attribute("units");

        if (isStandardUnitName(unitsName)) {
            auto iter = mStandardUnits.find(unitsName);

            if (iter == mStandardUnits.end()) {
                auto units = libcellml::Units::create(unitsName);

                mCiCnUnits.emplace(ast, units);
                mStandardUnits.emplace(unitsName, units);
            } else {
                mCiCnUnits.emplace(ast, iter->second);
            }
        } else {
            mCiCnUnits.emplace(ast, owningModel(component)->units(unitsName));
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
            auto issue = Issue::IssueImpl::create();
            auto trackedVariableComponent = owningComponent(internalVariable->mVariable);

            issue->mPimpl->setDescription("Variable '" + variable->name()
                                          + "' in component '" + component->name()
                                          + "' and variable '" + internalVariable->mVariable->name()
                                          + "' in component '" + trackedVariableComponent->name()
                                          + "' are equivalent and cannot therefore both be initialised.");
            issue->mPimpl->setReferenceRule(Issue::ReferenceRule::ANALYSER_VARIABLE_INITIALISED_MORE_THAN_ONCE);
            issue->mPimpl->mItem->mPimpl->setVariable(variable);

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
                auto issue = Issue::IssueImpl::create();

                issue->mPimpl->setDescription("Variable '" + variable->name()
                                              + "' in component '" + component->name()
                                              + "' is initialised using variable '" + internalVariable->mVariable->initialValue()
                                              + "', which is not a constant.");
                issue->mPimpl->setReferenceRule(Issue::ReferenceRule::ANALYSER_VARIABLE_NON_CONSTANT_INITIALISATION);
                issue->mPimpl->mItem->mPimpl->setVariable(variable);

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
                                                   VariablePtrs &equivalentVariables) const
{
    for (size_t i = 0; i < variable->equivalentVariableCount(); ++i) {
        auto equivalentVariable = variable->equivalentVariable(i);

        if (std::find(equivalentVariables.begin(), equivalentVariables.end(), equivalentVariable) == equivalentVariables.end()) {
            equivalentVariables.push_back(equivalentVariable);

            doEquivalentVariables(equivalentVariable, equivalentVariables);
        }
    }
}

VariablePtrs Analyser::AnalyserImpl::equivalentVariables(const VariablePtr &variable) const
{
    VariablePtrs res = {variable};

    doEquivalentVariables(variable, res);

    return res;
}

void Analyser::AnalyserImpl::analyseEquationAst(const AnalyserEquationAstPtr &ast)
{
    // Make sure that we have an AST to analyse.

    if (ast == nullptr) {
        return;
    }

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
                            auto issue = Issue::IssueImpl::create();

                            issue->mPimpl->setDescription("Variable '" + voiEquivalentVariable->name()
                                                          + "' in component '" + owningComponent(voiEquivalentVariable)->name()
                                                          + "' cannot be both a variable of integration and initialised.");
                            issue->mPimpl->setReferenceRule(Issue::ReferenceRule::ANALYSER_VOI_INITIALISED);
                            issue->mPimpl->mItem->mPimpl->setVariable(voiEquivalentVariable);

                            mAnalyser->addIssue(issue);

                            isVoiInitialised = true;
                        }
                    }

                    if (!isVoiInitialised) {
                        mModel->mPimpl->mVoi = AnalyserVariable::AnalyserVariableImpl::create();

                        mModel->mPimpl->mVoi->mPimpl->populate(AnalyserVariable::Type::VARIABLE_OF_INTEGRATION,
                                                               0, nullptr, voi, nullptr);
                    }

                    break;
                }
            }
        } else if (!mModel->areEquivalentVariables(variable, mModel->mPimpl->mVoi->variable())) {
            auto issue = Issue::IssueImpl::create();

            issue->mPimpl->setDescription("Variable '" + mModel->mPimpl->mVoi->variable()->name()
                                          + "' in component '" + owningComponent(mModel->mPimpl->mVoi->variable())->name()
                                          + "' and variable '" + variable->name()
                                          + "' in component '" + owningComponent(variable)->name()
                                          + "' cannot both be the variable of integration.");
            issue->mPimpl->setReferenceRule(Issue::ReferenceRule::ANALYSER_VOI_SEVERAL);
            issue->mPimpl->mItem->mPimpl->setVariable(variable);

            mAnalyser->addIssue(issue);
        }
    }

    // Make sure that we only use first-order ODEs.

    if ((ast->mPimpl->mType == AnalyserEquationAst::Type::CN)
        && (astParent != nullptr) && (astParent->mPimpl->mType == AnalyserEquationAst::Type::DEGREE)
        && (astGrandParent != nullptr) && (astGrandParent->mPimpl->mType == AnalyserEquationAst::Type::BVAR)
        && (astGreatGrandParent != nullptr) && (astGreatGrandParent->mPimpl->mType == AnalyserEquationAst::Type::DIFF)) {
        bool validValue;
        double value = convertToDouble(ast->mPimpl->mValue, &validValue);

        if (!validValue || !areEqual(value, 1.0)) {
            auto issue = Issue::IssueImpl::create();
            auto variable = astGreatGrandParent->mPimpl->mOwnedRightChild->variable();

            issue->mPimpl->setDescription("The differential equation for variable '" + variable->name()
                                          + "' in component '" + owningComponent(variable)->name()
                                          + "' must be of the first order.");
            issue->mPimpl->mItem->mPimpl->setMath(owningComponent(variable));
            issue->mPimpl->setReferenceRule(Issue::ReferenceRule::ANALYSER_ODE_NOT_FIRST_ORDER);

            mAnalyser->addIssue(issue);
        }
    }

    // Make a variable a state if it is used in an ODE.

    if ((ast->mPimpl->mType == AnalyserEquationAst::Type::CI)
        && (astParent != nullptr) && (astParent->mPimpl->mType == AnalyserEquationAst::Type::DIFF)) {
        internalVariable(ast->variable())->makeState();
    }

    // Recursively check the given AST's children.

    analyseEquationAst(ast->mPimpl->mOwnedLeftChild);
    analyseEquationAst(ast->mPimpl->mOwnedRightChild);
}

void Analyser::AnalyserImpl::updateUnitsMapWithStandardUnit(const std::string &unitsName,
                                                            UnitsMap &unitsMap,
                                                            double unitsExponent)
{
    // Update the given units map using the given standard unit.

    for (const auto &iter : standardUnitsList.at(unitsName)) {
        if (unitsMap.find(iter.first) == unitsMap.end()) {
            unitsMap.emplace(iter.first, 0.0);
        }

        unitsMap[iter.first] += iter.second * unitsExponent;
    }
}

void Analyser::AnalyserImpl::updateUnitsMap(const ModelPtr &model,
                                            const std::string &unitsName,
                                            UnitsMap &unitsMap,
                                            bool userUnitsMap,
                                            double unitsExponent,
                                            double unitsMultiplier)
{
    // Update the given units map using the given information.

    if (userUnitsMap) {
        if (unitsName != "dimensionless") {
            unitsMap.emplace(unitsName, unitsExponent);
        }
    } else {
        if (isStandardUnitName(unitsName)) {
            updateUnitsMapWithStandardUnit(unitsName, unitsMap, unitsExponent);
        } else {
            UnitsPtr units = model->units(unitsName);

            if (units->isBaseUnit()) {
                auto iter = unitsMap.find(unitsName);

                if (iter == unitsMap.end()) {
                    unitsMap.emplace(unitsName, unitsExponent);
                } else {
                    unitsMap[iter->first] += unitsExponent;
                }
            } else {
                std::string reference;
                std::string prefix;
                double exponent;
                double multiplier;
                std::string id;

                for (size_t i = 0; i < units->unitCount(); ++i) {
                    units->unitAttributes(i, reference, prefix, exponent, multiplier, id);

                    if (isStandardUnitName(reference)) {
                        updateUnitsMapWithStandardUnit(reference, unitsMap, exponent * unitsExponent);
                    } else {
                        updateUnitsMap(model, reference, unitsMap, userUnitsMap,
                                       exponent * unitsExponent,
                                       unitsMultiplier + (std::log10(multiplier) + convertPrefixToInt(prefix)) * unitsExponent);
                    }
                }
            }
        }
    }
}

UnitsMap Analyser::AnalyserImpl::multiplyDivideUnitsMaps(const UnitsMap &firstUnitsMap,
                                                         const UnitsMap &secondUnitsMap,
                                                         bool multiply)
{
    // Multiply/divide the given units maps together, following a multiplication
    // (multiply = true) or a division (multiply = false).

    UnitsMap res = firstUnitsMap;
    double sign = multiply ? 1.0 : -1.0;

    for (const auto &units : secondUnitsMap) {
        auto it = res.find(units.first);

        if (it == res.end()) {
            res.emplace(units.first, sign * units.second);
        } else {
            it->second += sign * units.second;

            if (areNearlyEqual(it->second, 0.0)) {
                // The units has now an exponent value of zero, so no need to
                // track it anymore.

                res.erase(it);
            }
        }
    }

    return res;
}

UnitsMaps Analyser::AnalyserImpl::multiplyDivideUnitsMaps(const UnitsMaps &firstUnitsMaps,
                                                          const UnitsMaps &secondUnitsMaps,
                                                          bool multiply)
{
    // Multiply/divide the given units maps together, following a multiplication
    // (multiply = true) or a division (multiply = false).

    UnitsMaps res;

    for (const auto &firstUnitsMap : firstUnitsMaps) {
        for (const auto &secondUnitsMap : secondUnitsMaps) {
            res.push_back(multiplyDivideUnitsMaps(firstUnitsMap, secondUnitsMap, multiply));
        }
    }

    return res;
}

UnitsMaps Analyser::AnalyserImpl::multiplyDivideUnitsMaps(const UnitsMaps &unitsMaps,
                                                          double factor,
                                                          bool multiply)
{
    // Multiply/divide the given units maps by the given factor, following a
    // multiplication (multiply = true) or a division (multiply = false).

    UnitsMaps res = unitsMaps;
    double realFactor = multiply ? factor : 1.0 / factor;

    for (auto &unitsMap : res) {
        for (auto &unitsItem : unitsMap) {
            unitsItem.second *= realFactor;
        }
    }

    return res;
}

double Analyser::AnalyserImpl::multiplyDivideUnitsMultipliers(double firstUnitsMultiplier,
                                                              double secondUnitsMultiplier,
                                                              bool multiply)
{
    // Multiply/divide the given units multipliers together, following a
    // multiplication (multiply = true) or a division (multiply = false).

    return firstUnitsMultiplier + (multiply ? 1.0 : -1.0) * secondUnitsMultiplier;
}

UnitsMultipliers Analyser::AnalyserImpl::multiplyDivideUnitsMultipliers(const UnitsMultipliers &firstUnitsMultipliers,
                                                                        const UnitsMultipliers &secondUnitsMultipliers,
                                                                        bool multiply)
{
    // Multiply/divide the given units multipliers together, following a
    // multiplication (multiply = true) or a division (multiply = false).

    UnitsMultipliers res;

    for (const auto &firstUnitsMultiplier : firstUnitsMultipliers) {
        for (const auto &secondUnitsMultiplier : secondUnitsMultipliers) {
            res.push_back(multiplyDivideUnitsMultipliers(firstUnitsMultiplier,
                                                         secondUnitsMultiplier,
                                                         multiply));
        }
    }

    return res;
}

UnitsMultipliers Analyser::AnalyserImpl::multiplyDivideUnitsMultipliers(double firstUnitsMultiplier,
                                                                        const UnitsMultipliers &secondUnitsMultipliers,
                                                                        bool multiply)
{
    // Multiply/divide the given units multipliers together, following a
    // multiplication (multiply = true) or a division (multiply = false).

    UnitsMultipliers res;

    for (const auto &secondUnitsMultiplier : secondUnitsMultipliers) {
        res.push_back(multiplyDivideUnitsMultipliers(firstUnitsMultiplier,
                                                     secondUnitsMultiplier,
                                                     multiply));
    }

    return res;
}

UnitsMultipliers Analyser::AnalyserImpl::powerRootUnitsMultipliers(const UnitsMultipliers &unitsMultipliers,
                                                                   double factor,
                                                                   bool power)
{
    // Power/root the given units multipliers to the given factor, following a
    // power (power = true) or a root (power = false) operation.

    UnitsMultipliers res;
    double realFactor = power ? factor : 1.0 / factor;

    for (const auto &unitsMultiplier : unitsMultipliers) {
        res.push_back(realFactor * unitsMultiplier);
    }

    return res;
}

bool Analyser::AnalyserImpl::areSameUnitsMaps(const UnitsMaps &firstUnitsMaps,
                                              const UnitsMaps &secondUnitsMaps)
{
    // Check whether the given units maps are the same by checking their
    // exponents.

    for (const auto &firstUnitsMap : firstUnitsMaps) {
        for (const auto &secondUnitsMap : secondUnitsMaps) {
            UnitsMap unitsMap;

            for (const auto &units : firstUnitsMap) {
                if (units.first != "dimensionless") {
                    unitsMap[units.first] += units.second;
                }
            }

            for (const auto &units : secondUnitsMap) {
                if (units.first != "dimensionless") {
                    unitsMap[units.first] -= units.second;
                }
            }

            for (const auto &unitsItem : unitsMap) {
                if (!areNearlyEqual(unitsItem.second, 0.0)) {
                    return false;
                }
            }
        }
    }

    return true;
}

bool Analyser::AnalyserImpl::isDimensionlessUnitsMaps(const UnitsMaps &unitsMaps)
{
    // Check whether the given units maps is dimensionless.

    for (const auto &unitsMap : unitsMaps) {
        for (const auto &unitsItem : unitsMap) {
            if (unitsItem.first != "dimensionless") {
                return false;
            }
        }
    }

    return true;
}

bool Analyser::AnalyserImpl::areSameUnitsMultipliers(const UnitsMultipliers &firstUnitsMultipliers,
                                                     const UnitsMultipliers &secondUnitsMultipliers)
{
    // Return whether the units multipliers are equals.

    for (const auto &firstUnitsMultiplier : firstUnitsMultipliers) {
        for (const auto &secondUnitsMultiplier : secondUnitsMultipliers) {
            if (!areNearlyEqual(firstUnitsMultiplier, secondUnitsMultiplier)) {
                return false;
            }
        }
    }

    return true;
}

void Analyser::AnalyserImpl::updateUnitsMultiplier(const ModelPtr &model,
                                                   const std::string &unitsName,
                                                   double &newUnitsMultiplier,
                                                   double unitsExponent,
                                                   double unitsMultiplier)
{
    // Update the given units multiplier using the given information.

    if (isStandardUnitName(unitsName)) {
        newUnitsMultiplier += unitsMultiplier + standardMultiplierList.at(unitsName);
    } else {
        UnitsPtr units = model->units(unitsName);

        if (units->isBaseUnit()) {
            newUnitsMultiplier += unitsMultiplier;
        } else {
            std::string reference;
            std::string prefix;
            double exponent;
            double multiplier;
            std::string id;

            for (size_t i = 0; i < units->unitCount(); ++i) {
                units->unitAttributes(i, reference, prefix, exponent, multiplier, id);

                if (isStandardUnitName(reference)) {
                    newUnitsMultiplier += unitsMultiplier + (standardMultiplierList.at(reference) + std::log10(multiplier) + convertPrefixToInt(prefix)) * exponent * unitsExponent;
                } else {
                    updateUnitsMultiplier(model, reference, newUnitsMultiplier,
                                          exponent * unitsExponent,
                                          unitsMultiplier + (std::log10(multiplier) + convertPrefixToInt(prefix)) * unitsExponent);
                }
            }
        }
    }
}

std::string Analyser::AnalyserImpl::componentName(const AnalyserEquationAstPtr &ast)
{
    // Return the name of the component in which the given AST is, by going
    // through the AST, if needed, and returning the component of the first
    // variable we find on the LHS/RHS.

    auto variable = ast->variable();

    if (variable != nullptr) {
        return std::dynamic_pointer_cast<Component>(variable->parent())->name();
    }

    auto res = (ast->mPimpl->mOwnedLeftChild != nullptr) ?
                   componentName(ast->mPimpl->mOwnedLeftChild) :
                   "";

    if (res.empty()) {
        res = (ast->mPimpl->mOwnedRightChild != nullptr) ?
                  componentName(ast->mPimpl->mOwnedRightChild) :
                  "";
    }

    return res;
}

double Analyser::AnalyserImpl::powerValue(const AnalyserEquationAstPtr &ast)
{
    // Return the power value for the given AST.

    if (ast == nullptr) {
        return 0.0;
    }

    if (ast->value().empty()) {
        if ((ast->mPimpl->mOwnedLeftChild == nullptr) && (ast->mPimpl->mOwnedRightChild == nullptr)) {
            return 0.0;
        }

        if (ast->mPimpl->mType == AnalyserEquationAst::Type::TIMES) {
            return powerValue(ast->mPimpl->mOwnedLeftChild) * powerValue(ast->mPimpl->mOwnedRightChild);
        }

        if (ast->mPimpl->mType == AnalyserEquationAst::Type::DIVIDE) {
            return areNearlyEqual(powerValue(ast->mPimpl->mOwnedRightChild), 0.0) ?
                       0.0 :
                       powerValue(ast->mPimpl->mOwnedLeftChild) / powerValue(ast->mPimpl->mOwnedRightChild);
        }

        if (ast->mPimpl->mType == AnalyserEquationAst::Type::PLUS) {
            return powerValue(ast->mPimpl->mOwnedLeftChild) + powerValue(ast->mPimpl->mOwnedRightChild);
        }

        if (ast->mPimpl->mType == AnalyserEquationAst::Type::MINUS) {
            return powerValue(ast->mPimpl->mOwnedLeftChild) - powerValue(ast->mPimpl->mOwnedRightChild);
        }

        if (ast->mPimpl->mType == AnalyserEquationAst::Type::DEGREE) {
            return powerValue(ast->mPimpl->mOwnedLeftChild);
        }

        return 0.0;
    }

    return std::stod(ast->value());
}

std::string Analyser::AnalyserImpl::expression(const AnalyserEquationAstPtr &ast,
                                               bool includeHierarchy)
{
    // Return the generated code for the given AST, specifying the equation and
    // component in which it is, if needed and requested.

    std::string res = "'" + mGenerator->mPimpl->generateCode(ast) + "'";

    if (includeHierarchy) {
        AnalyserEquationAstPtr equationAst = ast;
        AnalyserEquationAstPtr equationAstParent = ast->parent();
        AnalyserEquationAstPtr equationAstGrandParent = (equationAstParent != nullptr) ?
                                                            equationAstParent->parent() :
                                                            nullptr;

        while (equationAstParent != nullptr) {
            equationAst = equationAstParent;
            equationAstParent = equationAstGrandParent;
            equationAstGrandParent = (equationAstParent != nullptr) ?
                                         equationAstParent->parent() :
                                         nullptr;

            res += std::string(" in")
                   + (((equationAstParent == nullptr) && equationAstGrandParent == nullptr) ? " equation" : "")
                   + " '" + mGenerator->mPimpl->generateCode(equationAst) + "'";
        }

        res += " in component '" + componentName(equationAst) + "'";
    }

    return res;
}

std::string Analyser::AnalyserImpl::expressionUnits(const UnitsMaps &unitsMaps,
                                                    const UnitsMultipliers &unitsMultipliers)
{
    // Return a string version of the given units maps and units multipliers.

    Strings units;

    for (size_t i = 0; i < unitsMaps.size(); ++i) {
        auto unitsMap = unitsMaps[i];
        std::string unit;

        if (!unitsMultipliers.empty()) {
            auto intExponent = int(unitsMultipliers[i]);
            auto exponent = areNearlyEqual(unitsMultipliers[i], intExponent) ?
                                convertToString(intExponent) :
                                convertToString(unitsMultipliers[i], false);

            if (exponent != "0") {
                unit += "10";

                if (exponent != "1") {
                    unit += "^" + exponent;
                }
            }
        }

        for (const auto &unitsItem : unitsMap) {
            if ((unitsItem.first != "dimensionless")
                && !areNearlyEqual(unitsItem.second, 0.0)) {
                auto intExponent = int(unitsItem.second);
                auto exponent = areNearlyEqual(unitsItem.second, intExponent) ?
                                    convertToString(intExponent) :
                                    convertToString(unitsItem.second, false);

                if (!unit.empty()) {
                    unit += " x ";
                }

                unit += unitsItem.first;

                if (exponent != "1") {
                    unit += "^" + exponent;
                }
            }
        }

        if (!unit.empty()) {
            units.push_back(unit);
        }
    }

    std::string unitsString;

    for (size_t i = 0; i < units.size(); ++i) {
        if (i > 0) {
            unitsString += (i == units.size() - 1) ? " and " : ", ";
        }

        unitsString += "'" + units[i] + "'";
    }

    return unitsString;
}

std::string Analyser::AnalyserImpl::expressionUnits(const AnalyserEquationAstPtr &ast,
                                                    const UnitsMaps &unitsMaps,
                                                    const UnitsMaps &userUnitsMaps,
                                                    const UnitsMultipliers &unitsMultipliers)
{
    // Return a string version of the given AST and (user) units maps and units
    // multipliers.

    auto res = expression(ast, false) + " is ";
    auto unitsString = expressionUnits(unitsMaps, unitsMultipliers);
    auto userUnitsString = expressionUnits(userUnitsMaps);

    if (userUnitsString.empty()) {
        res += "'dimensionless'";
    } else {
        res += "in " + userUnitsString;

        if (!unitsString.empty() && (unitsString != userUnitsString)) {
            res += " (i.e. " + unitsString + ")";
        }
    }

    return res;
}

void Analyser::AnalyserImpl::defaultUnitsMapsAndMultipliers(UnitsMaps &unitsMaps,
                                                            UnitsMaps &userUnitsMaps,
                                                            UnitsMultipliers &unitsMultipliers)
{
    // Default units maps and multipliers.

    unitsMaps = {UnitsMap()};
    userUnitsMaps = {UnitsMap()};
    unitsMultipliers = {0.0};
}

void Analyser::AnalyserImpl::analyseEquationUnits(const AnalyserEquationAstPtr &ast,
                                                  UnitsMaps &unitsMaps,
                                                  UnitsMaps &userUnitsMaps,
                                                  UnitsMultipliers &unitsMultipliers,
                                                  Strings &issueDescriptions)
{
    // Analyse the units used with different MathML elements (table 2.1 of the
    // CellML 2.0 normative specification; see https://bit.ly/3vBbyO5):
    //  - Simple operands ('ci' and 'cn'; note: 'sep' is not relevant here): the
    //    operand can have any unit.
    //  - Basic structural (note: 'apply' is not relevant here):
    //     - 'piecewise': the returned value of the different 'piece' and
    //       'otherwise' statements should have equivalent units.
    //     - 'piece': the returned value can have any unit while the condition
    //       should be dimensionless.
    //     - 'otherwise': the returned value can have any unit.
    //  - Relational operators ('eq', 'neq', 'gt', 'lt', 'geq' and 'leq'): the
    //    two operands should have equivalent units. (The result of the
    //    comparison is dimensionless.)
    //  - Logical operators:
    //     - 'and', 'or', 'xor': the two operands should be dimensionless.
    //     - 'not': the operand should be dimensionless.
    //  - Arithmetic operators:
    //     - 'plus': the two operands should have equivalent units.
    //     - 'minus': if there is one operand, then it can have any unit. If
    //       there are two operands, then they should have equivalent units.
    //     - 'times' and 'divide': the two operands can have any units.
    //     - 'power': the base can have any unit while the exponent should be
    //       dimensionless.
    //     - 'root': the base can have any unit while the exponent, if present,
    //       should be dimensionless.
    //     - 'abs': the argument can have any unit.
    //     - 'exp' and 'ln': the argument should be dimensionless.
    //     - 'log': the argument and the base, if present, should be
    //       dimensionless.
    //     - 'floor' and 'ceiling': the argument can have any unit.
    //     - 'min' and 'max': all the arguments should have equivalent units.
    //     - 'rem': the two arguments should have equivalent units.
    //  - Calculus elements ('diff'): the differentiated variable can have any
    //    unit. (See 'bvar' below for the bounding variable.)
    //  - Qualifier elements:
    //     - 'bvar': a bounding variable can have any unit.
    //     - 'degree': a degree should be dimensionless.
    //     - 'logbase': a base should be dimensionless.
    //  - Trigonometric operators ('sin', 'cos', 'tan', etc.): the argument
    //    should be dimensionless.
    //  - Mathematical and logical constants ('pi', 'exponentiale',
    //    'notanumber','infinity', 'true' and 'false'): those constants are
    //    dimensionless.

    // Make sure that we have an AST to analyse.

    if (ast == nullptr) {
        unitsMaps = {};
        userUnitsMaps = {};
        unitsMultipliers = {};

        return;
    }

    // Check whether we are dealing with a CI/CN element and, if so, retrieve
    // both its units maps and multipliers.

    if ((ast->mPimpl->mType == AnalyserEquationAst::Type::CI)
        || (ast->mPimpl->mType == AnalyserEquationAst::Type::CN)) {
        auto units = mCiCnUnits[ast].lock();
        auto model = owningModel(units);

        defaultUnitsMapsAndMultipliers(unitsMaps, userUnitsMaps, unitsMultipliers);

        for (auto &unitsMap : unitsMaps) {
            updateUnitsMap(model, units->name(), unitsMap);
        }

        for (auto &userUnitsMap : userUnitsMaps) {
            updateUnitsMap(model, units->name(), userUnitsMap, true);
        }

        for (auto &unitsMultiplier : unitsMultipliers) {
            updateUnitsMultiplier(model, units->name(), unitsMultiplier);
        }

        return;
    }

    // Check the left and right children.

    auto oldNbOfIssueDescriptions = issueDescriptions.size();
    UnitsMaps rightUnitsMaps;
    UnitsMaps rightUserUnitsMaps;
    UnitsMultipliers rightUnitsMultipliers;

    analyseEquationUnits(ast->mPimpl->mOwnedLeftChild, unitsMaps, userUnitsMaps, unitsMultipliers, issueDescriptions);
    analyseEquationUnits(ast->mPimpl->mOwnedRightChild, rightUnitsMaps, rightUserUnitsMaps, rightUnitsMultipliers, issueDescriptions);

    if ((ast->mPimpl->mType == AnalyserEquationAst::Type::ASSIGNMENT)
        || (ast->mPimpl->mType == AnalyserEquationAst::Type::EQ)
        || (ast->mPimpl->mType == AnalyserEquationAst::Type::NEQ)
        || (ast->mPimpl->mType == AnalyserEquationAst::Type::LT)
        || (ast->mPimpl->mType == AnalyserEquationAst::Type::LEQ)
        || (ast->mPimpl->mType == AnalyserEquationAst::Type::GT)
        || (ast->mPimpl->mType == AnalyserEquationAst::Type::GEQ)
        || (ast->mPimpl->mType == AnalyserEquationAst::Type::PLUS)
        || (ast->mPimpl->mType == AnalyserEquationAst::Type::MINUS)
        || (ast->mPimpl->mType == AnalyserEquationAst::Type::MIN)
        || (ast->mPimpl->mType == AnalyserEquationAst::Type::MAX)
        || (ast->mPimpl->mType == AnalyserEquationAst::Type::REM)) {
        bool sameUnitsMaps = rightUnitsMaps.empty()
                             || areSameUnitsMaps(unitsMaps, rightUnitsMaps);
        bool sameUnitsMultipliers = rightUnitsMaps.empty()
                                    || areSameUnitsMultipliers(unitsMultipliers, rightUnitsMultipliers);

        if (sameUnitsMaps && sameUnitsMultipliers) {
            // Relational operators result in a dimensionless unit.

            if ((ast->mPimpl->mType == AnalyserEquationAst::Type::EQ)
                || (ast->mPimpl->mType == AnalyserEquationAst::Type::NEQ)
                || (ast->mPimpl->mType == AnalyserEquationAst::Type::LT)
                || (ast->mPimpl->mType == AnalyserEquationAst::Type::LEQ)
                || (ast->mPimpl->mType == AnalyserEquationAst::Type::GT)
                || (ast->mPimpl->mType == AnalyserEquationAst::Type::GEQ)) {
                defaultUnitsMapsAndMultipliers(unitsMaps, userUnitsMaps, unitsMultipliers);
            }
        } else if (issueDescriptions.size() == oldNbOfIssueDescriptions) {
            // Only report inner issues.

            std::string issueDescription = "The units in " + expression(ast) + " are not equivalent. ";

            issueDescription += expressionUnits(ast->mPimpl->mOwnedLeftChild, unitsMaps, userUnitsMaps, unitsMultipliers) + " while "
                                + expressionUnits(ast->mPimpl->mOwnedRightChild, rightUnitsMaps, rightUserUnitsMaps, rightUnitsMultipliers) + ".";

            issueDescriptions.push_back(issueDescription);
        }
    } else if (ast->mPimpl->mType == AnalyserEquationAst::Type::PIECEWISE) {
        unitsMaps.insert(std::end(unitsMaps),
                         std::begin(rightUnitsMaps),
                         std::end(rightUnitsMaps));
        userUnitsMaps.insert(std::end(userUnitsMaps),
                             std::begin(rightUserUnitsMaps),
                             std::end(rightUserUnitsMaps));
        unitsMultipliers.insert(std::end(unitsMultipliers),
                                std::begin(rightUnitsMultipliers),
                                std::end(rightUnitsMultipliers));
    } else if (ast->mPimpl->mType == AnalyserEquationAst::Type::PIECE) {
        if (!Analyser::AnalyserImpl::isDimensionlessUnitsMaps(rightUnitsMaps)) {
            issueDescriptions.push_back("The unit of " + expression(ast->mPimpl->mOwnedRightChild)
                                        + " is not dimensionless. "
                                        + expressionUnits(ast->mPimpl->mOwnedRightChild, rightUnitsMaps, rightUserUnitsMaps, rightUnitsMultipliers) + ".");
        }
    } else if ((ast->mPimpl->mType == AnalyserEquationAst::Type::AND)
               || (ast->mPimpl->mType == AnalyserEquationAst::Type::OR)
               || (ast->mPimpl->mType == AnalyserEquationAst::Type::XOR)
               || (ast->mPimpl->mType == AnalyserEquationAst::Type::NOT)
               || (ast->mPimpl->mType == AnalyserEquationAst::Type::EXP)
               || (ast->mPimpl->mType == AnalyserEquationAst::Type::LN)
               || (ast->mPimpl->mType == AnalyserEquationAst::Type::LOG)) {
        bool isDimensionlessUnitsMaps = Analyser::AnalyserImpl::isDimensionlessUnitsMaps(unitsMaps);
        bool isDimensionlessRightUnitsMaps = Analyser::AnalyserImpl::isDimensionlessUnitsMaps(rightUnitsMaps);

        if (!isDimensionlessUnitsMaps || !isDimensionlessRightUnitsMaps) {
            std::string issueDescription = "The unit";

            if (!isDimensionlessUnitsMaps && !isDimensionlessRightUnitsMaps) {
                issueDescription += "s";
            }

            issueDescription += " of ";

            if (!isDimensionlessUnitsMaps) {
                issueDescription += expression(ast->mPimpl->mOwnedLeftChild, false);
            }

            if (!isDimensionlessUnitsMaps && !isDimensionlessRightUnitsMaps) {
                issueDescription += " and ";
            }

            if (!isDimensionlessRightUnitsMaps) {
                issueDescription += expression(ast->mPimpl->mOwnedRightChild, false);
            }

            issueDescription += " in " + expression(ast);

            if (!isDimensionlessUnitsMaps && !isDimensionlessRightUnitsMaps) {
                issueDescription += " are ";
            } else {
                issueDescription += " is ";
            }

            issueDescription += "not dimensionless. ";

            if (!isDimensionlessUnitsMaps) {
                issueDescription += expressionUnits(ast->mPimpl->mOwnedLeftChild, unitsMaps, userUnitsMaps, unitsMultipliers);
            }

            if (!isDimensionlessUnitsMaps && !isDimensionlessRightUnitsMaps) {
                issueDescription += " while ";
            }

            if (!isDimensionlessRightUnitsMaps) {
                issueDescription += expressionUnits(ast->mPimpl->mOwnedRightChild, rightUnitsMaps, rightUserUnitsMaps, rightUnitsMultipliers);
            }

            issueDescription += ".";

            issueDescriptions.push_back(issueDescription);
        }
    } else if ((ast->mPimpl->mType == AnalyserEquationAst::Type::TIMES)
               || (ast->mPimpl->mType == AnalyserEquationAst::Type::DIVIDE)) {
        unitsMaps = multiplyDivideUnitsMaps(unitsMaps, rightUnitsMaps,
                                            ast->mPimpl->mType == AnalyserEquationAst::Type::TIMES);
        userUnitsMaps = multiplyDivideUnitsMaps(userUnitsMaps, rightUserUnitsMaps,
                                                ast->mPimpl->mType == AnalyserEquationAst::Type::TIMES);
        unitsMultipliers = multiplyDivideUnitsMultipliers(unitsMultipliers, rightUnitsMultipliers,
                                                          ast->mPimpl->mType == AnalyserEquationAst::Type::TIMES);
    } else if ((ast->mPimpl->mType == AnalyserEquationAst::Type::POWER)
               || (ast->mPimpl->mType == AnalyserEquationAst::Type::ROOT)) {
        bool isDimensionlessExponent = true;

        if ((ast->mPimpl->mType == AnalyserEquationAst::Type::POWER)
            || (ast->mPimpl->mOwnedLeftChild->type() == AnalyserEquationAst::Type::DEGREE)) {
            isDimensionlessExponent = Analyser::AnalyserImpl::isDimensionlessUnitsMaps((ast->mPimpl->mType == AnalyserEquationAst::Type::POWER) ?
                                                                                           rightUnitsMaps :
                                                                                           unitsMaps);

            if (!isDimensionlessExponent) {
                auto baseAst = (ast->mPimpl->mType == AnalyserEquationAst::Type::POWER) ?
                                   ast->mPimpl->mOwnedRightChild :
                                   ast->mPimpl->mOwnedLeftChild;
                auto exponentUnitsMaps = (ast->mPimpl->mType == AnalyserEquationAst::Type::POWER) ?
                                             rightUnitsMaps :
                                             unitsMaps;
                auto exponentUserUnitsMaps = (ast->mPimpl->mType == AnalyserEquationAst::Type::POWER) ?
                                                 rightUserUnitsMaps :
                                                 userUnitsMaps;
                auto exponentUnitsMultipliers = (ast->mPimpl->mType == AnalyserEquationAst::Type::POWER) ?
                                                    rightUnitsMultipliers :
                                                    unitsMultipliers;

                issueDescriptions.push_back("The unit of " + expression(baseAst)
                                            + " is not dimensionless. "
                                            + expressionUnits(baseAst, exponentUnitsMaps, exponentUserUnitsMaps, exponentUnitsMultipliers) + ".");
            }
        }

        // Retrieve the exponent and apply it to our units maps and multipliers.

        if (isDimensionlessExponent) {
            double powerRootValue = 0.0;

            if (ast->mPimpl->mType == AnalyserEquationAst::Type::POWER) {
                powerRootValue = Analyser::AnalyserImpl::powerValue(ast->mPimpl->mOwnedRightChild);
            } else {
                // Root case.

                if (ast->mPimpl->mOwnedLeftChild->type() == AnalyserEquationAst::Type::DEGREE) {
                    unitsMaps = rightUnitsMaps;
                    userUnitsMaps = rightUserUnitsMaps;
                    unitsMultipliers = rightUnitsMultipliers;

                    powerRootValue = Analyser::AnalyserImpl::powerValue(ast->mPimpl->mOwnedLeftChild);
                } else {
                    // No DEGREE element, which means that we are dealing with a
                    // square root.

                    powerRootValue = 2.0;
                }
            }

            unitsMaps = multiplyDivideUnitsMaps(unitsMaps, powerRootValue,
                                                ast->mPimpl->mType == AnalyserEquationAst::Type::POWER);
            userUnitsMaps = multiplyDivideUnitsMaps(userUnitsMaps, powerRootValue,
                                                    ast->mPimpl->mType == AnalyserEquationAst::Type::POWER);
            unitsMultipliers = powerRootUnitsMultipliers(unitsMultipliers, powerRootValue,
                                                         ast->mPimpl->mType == AnalyserEquationAst::Type::POWER);
        }
    } else if ((ast->mPimpl->mType == AnalyserEquationAst::Type::SIN)
               || (ast->mPimpl->mType == AnalyserEquationAst::Type::COS)
               || (ast->mPimpl->mType == AnalyserEquationAst::Type::TAN)
               || (ast->mPimpl->mType == AnalyserEquationAst::Type::SEC)
               || (ast->mPimpl->mType == AnalyserEquationAst::Type::CSC)
               || (ast->mPimpl->mType == AnalyserEquationAst::Type::COT)
               || (ast->mPimpl->mType == AnalyserEquationAst::Type::SINH)
               || (ast->mPimpl->mType == AnalyserEquationAst::Type::COSH)
               || (ast->mPimpl->mType == AnalyserEquationAst::Type::TANH)
               || (ast->mPimpl->mType == AnalyserEquationAst::Type::SECH)
               || (ast->mPimpl->mType == AnalyserEquationAst::Type::CSCH)
               || (ast->mPimpl->mType == AnalyserEquationAst::Type::COTH)
               || (ast->mPimpl->mType == AnalyserEquationAst::Type::ASIN)
               || (ast->mPimpl->mType == AnalyserEquationAst::Type::ACOS)
               || (ast->mPimpl->mType == AnalyserEquationAst::Type::ATAN)
               || (ast->mPimpl->mType == AnalyserEquationAst::Type::ASEC)
               || (ast->mPimpl->mType == AnalyserEquationAst::Type::ACSC)
               || (ast->mPimpl->mType == AnalyserEquationAst::Type::ACOT)
               || (ast->mPimpl->mType == AnalyserEquationAst::Type::ASINH)
               || (ast->mPimpl->mType == AnalyserEquationAst::Type::ACOSH)
               || (ast->mPimpl->mType == AnalyserEquationAst::Type::ATANH)
               || (ast->mPimpl->mType == AnalyserEquationAst::Type::ASECH)
               || (ast->mPimpl->mType == AnalyserEquationAst::Type::ACSCH)
               || (ast->mPimpl->mType == AnalyserEquationAst::Type::ACOTH)) {
        if (!Analyser::AnalyserImpl::isDimensionlessUnitsMaps(unitsMaps)) {
            issueDescriptions.push_back("The unit of " + expression(ast->mPimpl->mOwnedLeftChild)
                                        + " is not dimensionless. "
                                        + expressionUnits(ast->mPimpl->mOwnedLeftChild, unitsMaps, userUnitsMaps, unitsMultipliers) + ".");
        }
    } else if (ast->mPimpl->mType == AnalyserEquationAst::Type::DIFF) {
        unitsMaps = multiplyDivideUnitsMaps(unitsMaps, rightUnitsMaps);
        userUnitsMaps = multiplyDivideUnitsMaps(userUnitsMaps, rightUserUnitsMaps);
        unitsMultipliers = multiplyDivideUnitsMultipliers(unitsMultipliers, rightUnitsMultipliers);
    } else if (ast->mPimpl->mType == AnalyserEquationAst::Type::BVAR) {
        for (auto &unitsMap : unitsMaps) {
            for (auto &unitsItem : unitsMap) {
                unitsItem.second *= -1.0;
            }
        }

        for (auto &userUnitsMap : userUnitsMaps) {
            for (auto &userUnits : userUnitsMap) {
                userUnits.second *= -1.0;
            }
        }

        unitsMultipliers = multiplyDivideUnitsMultipliers(0.0, unitsMultipliers, false);
    } else if ((ast->mPimpl->mType == AnalyserEquationAst::Type::TRUE)
               || (ast->mPimpl->mType == AnalyserEquationAst::Type::FALSE)
               || (ast->mPimpl->mType == AnalyserEquationAst::Type::E)
               || (ast->mPimpl->mType == AnalyserEquationAst::Type::PI)
               || (ast->mPimpl->mType == AnalyserEquationAst::Type::INF)
               || (ast->mPimpl->mType == AnalyserEquationAst::Type::NAN)) {
        defaultUnitsMapsAndMultipliers(unitsMaps, userUnitsMaps, unitsMultipliers);
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

    scaleEquationAst(ast->mPimpl->mOwnedLeftChild);
    scaleEquationAst(ast->mPimpl->mOwnedRightChild);

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

            if (!areNearlyEqual(scalingFactor, 1.0)) {
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

            if (!areNearlyEqual(scalingFactor, 1.0)) {
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

    mModel = AnalyserModel::AnalyserModelImpl::create();

    mInternalVariables.clear();
    mInternalEquations.clear();

    mCiCnUnits.clear();

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

    if (mAnalyser->errorCount() == 0) {
        // Analyse our different equations' units to make sure that everything
        // is consistent.

        for (const auto &internalEquation : mInternalEquations) {
            UnitsMaps unitsMaps;
            UnitsMaps userUnitsMaps;
            UnitsMultipliers unitsMultipliers;
            Strings issueDescriptions;

            analyseEquationUnits(internalEquation->mAst, unitsMaps,
                                 userUnitsMaps, unitsMultipliers,
                                 issueDescriptions);

            for (const auto &issueDescription : issueDescriptions) {
                auto issue = Issue::IssueImpl::create();

                issue->mPimpl->setDescription(issueDescription);
                issue->mPimpl->setLevel(Issue::Level::WARNING);
                issue->mPimpl->setReferenceRule(Issue::ReferenceRule::ANALYSER_UNITS);

                mAnalyser->addIssue(issue);
            }
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
                auto issue = Issue::IssueImpl::create();
                auto realVariable = internalVariable->mVariable;

                issue->mPimpl->setDescription("Variable '" + realVariable->name()
                                              + "' in component '" + owningComponent(realVariable)->name()
                                              + "' " + issueType + ".");
                issue->mPimpl->setReferenceRule(referenceRule);
                issue->mPimpl->mItem->mPimpl->setVariable(realVariable);

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

        std::map<AnalyserInternalVariablePtr, VariablePtrs> externalVariables;

        if (!mExternalVariables.empty()) {
            // Check whether an external variable belongs to the model being
            // analysed, or whether it is marked as an external variable more
            // than once through equivalence or is (equivalent to) the variable
            // of integration.

            std::map<VariablePtr, VariablePtrs> primaryExternalVariables;

            for (const auto &externalVariable : mExternalVariables) {
                auto variable = externalVariable->variable();

                if (variable != nullptr) {
                    if (owningModel(variable) != model) {
                        auto issue = Issue::IssueImpl::create();

                        issue->mPimpl->setDescription("Variable '" + variable->name()
                                                      + "' in component '" + owningComponent(variable)->name()
                                                      + "' is marked as an external variable, but it belongs to a different model and will therefore be ignored.");
                        issue->mPimpl->setLevel(Issue::Level::MESSAGE);
                        issue->mPimpl->setReferenceRule(Issue::ReferenceRule::ANALYSER_EXTERNAL_VARIABLE_DIFFERENT_MODEL);
                        issue->mPimpl->mItem->mPimpl->setVariable(variable);

                        mAnalyser->addIssue(issue);
                    } else {
                        auto internalVariable = Analyser::AnalyserImpl::internalVariable(variable);

                        primaryExternalVariables[internalVariable->mVariable].push_back(variable);

                        if (((mModel->mPimpl->mVoi == nullptr)
                             || (internalVariable->mVariable != mModel->mPimpl->mVoi->variable()))
                            && (externalVariables.count(internalVariable) == 0)) {
                            VariablePtrs dependencies;

                            for (const auto &dependency : externalVariable->dependencies()) {
                                dependencies.push_back(Analyser::AnalyserImpl::internalVariable(dependency)->mVariable);
                            }

                            externalVariables.emplace(internalVariable, dependencies);
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

                        auto variableString = ((i == 0) && (equivalentVariableCount != 2)) ?
                                                  std::string("Variable") :
                                                  std::string("variable");

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

                    auto issue = Issue::IssueImpl::create();

                    issue->mPimpl->setDescription(description);
                    issue->mPimpl->setLevel(Issue::Level::MESSAGE);
                    issue->mPimpl->setReferenceRule(referenceRule);
                    issue->mPimpl->mItem->mPimpl->setVariable(primaryExternalVariable.first);

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
                equationMappings.emplace(internalEquation->mVariable->mVariable, std::shared_ptr<AnalyserEquation> {new AnalyserEquation {}});
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

                auto stateOrVariable = AnalyserVariable::AnalyserVariableImpl::create();
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

                variableMappings.emplace(equation, stateOrVariable);

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

                VariablePtrs variableDependencies = (type == AnalyserEquation::Type::EXTERNAL) ?
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
        mPimpl->mExternalVariables.erase(mPimpl->mExternalVariables.begin() + ptrdiff_t(index));

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
        return mPimpl->mExternalVariables[index];
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

} // namespace libcellml

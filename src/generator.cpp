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

#include <regex>
#include <sstream>

#include "libcellml/analyserequation.h"
#include "libcellml/analyserequationast.h"
#include "libcellml/analysermodel.h"
#include "libcellml/analyservariable.h"
#include "libcellml/component.h"
#include "libcellml/units.h"
#include "libcellml/version.h"

#include "analyserequation_p.h"
#include "analysermodel_p.h"
#include "commonutils.h"
#include "generator_p.h"
#include "generatorprofilesha1values.h"
#include "generatorprofiletools.h"
#include "utilities.h"

#include "libcellml/undefines.h"

namespace libcellml {

void Generator::GeneratorImpl::reset()
{
    mCode = {};
}

std::string Generator::GeneratorImpl::analyserVariableIndexString(const AnalyserModelPtr &analyserModel,
                                                                  const AnalyserVariablePtr &analyserVariable)
{
    // Determine the actual index of the analyser variable in the list of analyser variables by accounting for the fact
    // that some analyser variables may be untracked.

    auto variables = libcellml::analyserVariables(analyserVariable);

    if (variables.empty()) {
        return convertToString(analyserVariable->index());
    }

    size_t i = MAX_SIZE_T;
    size_t res = MAX_SIZE_T;

    for (;;) {
        auto var = variables[++i];

        if (doIsTrackedVariable(analyserModel, var)) {
            ++res;
        }

        if (analyserVariable == var) {
            break;
        }
    }

    return convertToString(res);
}

bool Generator::GeneratorImpl::doIsTrackedEquation(const AnalyserEquationPtr &analyserEquation, bool tracked)
{
    AnalyserVariablePtr analyserVariable;

    switch (analyserEquation->type()) {
    case AnalyserEquation::Type::COMPUTED_CONSTANT:
        analyserVariable = analyserEquation->computedConstants().front();

        return doIsTrackedVariable(analyserVariable->model(), analyserVariable) == tracked;
    case AnalyserEquation::Type::ALGEBRAIC:
        analyserVariable = analyserEquation->algebraicVariables().front();

        return doIsTrackedVariable(analyserVariable->model(), analyserVariable) == tracked;
    default:
        return true;
    }
}

bool Generator::GeneratorImpl::isTrackedEquation(const AnalyserEquationPtr &analyserEquation)
{
    return doIsTrackedEquation(analyserEquation, true);
}

bool Generator::GeneratorImpl::isUntrackedEquation(const AnalyserEquationPtr &analyserEquation)
{
    return doIsTrackedEquation(analyserEquation, false);
}

bool Generator::GeneratorImpl::doIsTrackedVariable(const AnalyserModelPtr &analyserModel, const AnalyserVariablePtr &analyserVariable,
                                                   bool tracked)
{
    // By default an analyser variable is always tracked.

    if (mTrackedVariables[analyserModel].find(analyserVariable) == mTrackedVariables[analyserModel].end()) {
        mTrackedVariables[analyserModel][analyserVariable] = true;
    }

    return mTrackedVariables[analyserModel][analyserVariable] == tracked;
}

bool Generator::GeneratorImpl::doIsTrackedVariable(const AnalyserVariablePtr &analyserVariable, bool tracked)
{
    if (analyserVariable == nullptr) {
        return false;
    }

    return doIsTrackedVariable(analyserVariable->model(), analyserVariable, tracked);
}

bool Generator::GeneratorImpl::isTrackedVariable(const AnalyserVariablePtr &analyserVariable)
{
    return doIsTrackedVariable(analyserVariable, true);
}

bool Generator::GeneratorImpl::isUntrackedVariable(const AnalyserVariablePtr &analyserVariable)
{
    return doIsTrackedVariable(analyserVariable, false);
}

void Generator::GeneratorImpl::addNeededToComputeExternalVariableIssue(const AnalyserVariablePtr &analyserVariable, bool tracked)
{
    auto issue = Issue::IssueImpl::create();

    issue->mPimpl->setDescription("Variable '" + analyserVariable->variable()->name()
                                  + "' in component '" + owningComponent(analyserVariable->variable())->name()
                                  + "' is needed to compute an external variable and "
                                  + (tracked ?
                                         "is therefore always tracked." :
                                         "cannot therefore be untracked."));
    issue->mPimpl->setReferenceRule(tracked ?
                                        Issue::ReferenceRule::GENERATOR_EXTERNALLY_NEEDED_VARIABLE_ALWAYS_TRACKED :
                                        Issue::ReferenceRule::GENERATOR_EXTERNALLY_NEEDED_VARIABLE_NOT_UNTRACKABLE);

    if (tracked) {
        issue->mPimpl->setLevel(Issue::Level::MESSAGE);
    }

    addIssue(issue);
}

bool Generator::GeneratorImpl::trackableVariable(const AnalyserVariablePtr &analyserVariable, bool tracked, bool canAddIssue)
{
    // A trackable analyser variable is an analyser variable that is not a variable of integration, a state, or an
    // external variable, which is already the case when we reach this point. However, a trackable analyser variable is
    // also an analyser variable that is not computed using an NLA system.

    for (const auto &analyserEquation : analyserVariable->analyserEquations()) {
        if (analyserEquation->type() == AnalyserEquation::Type::NLA) {
            if (canAddIssue) {
                auto issue = Issue::IssueImpl::create();

                issue->mPimpl->setDescription("Variable '" + analyserVariable->variable()->name()
                                              + "' in component '" + owningComponent(analyserVariable->variable())->name()
                                              + "' is computed using an NLA system and "
                                              + (tracked ?
                                                     "is therefore always tracked." :
                                                     "cannot therefore be untracked."));
                issue->mPimpl->setReferenceRule(tracked ?
                                                    Issue::ReferenceRule::GENERATOR_NLA_BASED_VARIABLE_ALWAYS_TRACKED :
                                                    Issue::ReferenceRule::GENERATOR_NLA_BASED_VARIABLE_NOT_UNTRACKABLE);

                if (tracked) {
                    issue->mPimpl->setLevel(Issue::Level::MESSAGE);
                }

                addIssue(issue);
            }

            return false;
        }
    }

    // A trackable analyser variable is also not an analyser variable that is needed to compute an external variable.

    for (const auto &externalVariable : analyserVariable->model()->externalVariables()) {
        auto externalEquationPimpl = externalVariable->analyserEquations().front()->mPimpl;

        // Check whether the analyser variable is a constant dependency.

        for (const auto &constantDependency : externalEquationPimpl->mConstantDependencies) {
            if (analyserVariable == constantDependency) {
                if (canAddIssue) {
                    addNeededToComputeExternalVariableIssue(analyserVariable, tracked);
                }

                return false;
            }
        }

        // Check whether the analyser variable is a computed constant dependency or an algebraic dependency.

        for (const auto &dependency : externalEquationPimpl->mDependencies) {
            auto dependencyPimpl = dependency.lock()->mPimpl;

            for (const auto &computedConstant : dependencyPimpl->mComputedConstants) {
                if (analyserVariable == computedConstant) {
                    if (canAddIssue) {
                        addNeededToComputeExternalVariableIssue(analyserVariable, tracked);
                    }

                    return false;
                }
            }

            for (const auto &algebraicVariable : dependencyPimpl->mAlgebraicVariables) {
                if (analyserVariable == algebraicVariable) {
                    if (canAddIssue) {
                        addNeededToComputeExternalVariableIssue(analyserVariable, tracked);
                    }

                    return false;
                }
            }
        }
    }

    return true;
}

bool Generator::GeneratorImpl::specialVariable(const AnalyserVariablePtr &analyserVariable,
                                               const AnalyserVariablePtr &specialAnalyserVariable, bool tracked,
                                               Issue::ReferenceRule trackedReferenceRule,
                                               Issue::ReferenceRule untrackedReferenceRule)
{
    if (analyserVariable == specialAnalyserVariable) {
        auto issue = Issue::IssueImpl::create();
        auto variableType = (specialAnalyserVariable->type() == AnalyserVariable::Type::VARIABLE_OF_INTEGRATION) ?
                                "the variable of integration" :
                                ((specialAnalyserVariable->type() == AnalyserVariable::Type::STATE) ?
                                     "a state variable" :
                                     "an external variable");

        issue->mPimpl->setDescription("Variable '" + analyserVariable->variable()->name()
                                      + "' in component '" + owningComponent(analyserVariable->variable())->name()
                                      + "' is " + variableType + " and "
                                      + (tracked ?
                                             "is therefore always tracked." :
                                             "cannot therefore be untracked."));
        issue->mPimpl->setReferenceRule(tracked ? trackedReferenceRule : untrackedReferenceRule);

        if (tracked) {
            issue->mPimpl->setLevel(Issue::Level::MESSAGE);
        }

        addIssue(issue);

        return true;
    }

    return false;
}

void Generator::GeneratorImpl::trackVariable(const AnalyserVariablePtr &analyserVariable, bool tracked,
                                             bool needRemoveAllIssues)
{
    // Make sure that we have a variable.

    if (needRemoveAllIssues) {
        removeAllIssues();
    }

    if (analyserVariable == nullptr) {
        auto issue = Issue::IssueImpl::create();

        issue->mPimpl->setDescription("The variable is null.");
        issue->mPimpl->setReferenceRule(Issue::ReferenceRule::GENERATOR_NULL_VARIABLE);

        addIssue(issue);

        return;
    }

    // Check whether we want to track/untrack a constant, a computed constant, or an algebraic variable though we can
    // only track/untrack a variable if it is actually trackable.

    auto analyserModel = analyserVariable->model();

    for (const auto &analyserModelVariable : analyserVariables(analyserVariable)) {
        if (analyserVariable == analyserModelVariable) {
            if (trackableVariable(analyserVariable, tracked)) {
                mTrackedVariables[analyserModelVariable->model()][analyserModelVariable] = tracked;
            }

            return;
        }
    }

    // Check whether we tried to track/untrack a state variable.

    for (const auto &state : analyserModel->states()) {
        if (specialVariable(analyserVariable, state, tracked,
                            Issue::ReferenceRule::GENERATOR_STATE_VARIABLE_ALWAYS_TRACKED,
                            Issue::ReferenceRule::GENERATOR_STATE_VARIABLE_NOT_UNTRACKABLE)) {
            return;
        }
    }

    // Check whether we tried to track/untrack an external variable.

    for (const auto &externalVariable : analyserModel->externalVariables()) {
        if (specialVariable(analyserVariable, externalVariable, tracked,
                            Issue::ReferenceRule::GENERATOR_EXTERNAL_VARIABLE_ALWAYS_TRACKED,
                            Issue::ReferenceRule::GENERATOR_EXTERNAL_VARIABLE_NOT_UNTRACKABLE)) {
            return;
        }
    }

    // In the end, we tried to track/untrack the variable of integration.

    specialVariable(analyserVariable, analyserModel->voi(), tracked,
                    Issue::ReferenceRule::GENERATOR_VOI_VARIABLE_ALWAYS_TRACKED,
                    Issue::ReferenceRule::GENERATOR_VOI_VARIABLE_NOT_UNTRACKABLE);
}

void Generator::GeneratorImpl::trackVariable(const AnalyserVariablePtr &analyserVariable)
{
    return trackVariable(analyserVariable, true);
}

void Generator::GeneratorImpl::untrackVariable(const AnalyserVariablePtr &analyserVariable)
{
    return trackVariable(analyserVariable, false);
}

void Generator::GeneratorImpl::trackVariables(const std::vector<AnalyserVariablePtr> &analyserVariables, bool tracked)
{
    removeAllIssues();

    for (const auto &analyserVariable : analyserVariables) {
        trackVariable(analyserVariable, tracked, false);
    }
}

bool Generator::GeneratorImpl::validModel(const AnalyserModelPtr &analyserModel)
{
    removeAllIssues();

    if (analyserModel == nullptr) {
        auto issue = Issue::IssueImpl::create();

        issue->mPimpl->setDescription("The model is null.");
        issue->mPimpl->setReferenceRule(Issue::ReferenceRule::GENERATOR_NULL_MODEL);

        addIssue(issue);

        return false;
    }

    return true;
}

void Generator::GeneratorImpl::trackAllConstants(const AnalyserModelPtr &analyserModel)
{
    if (validModel(analyserModel)) {
        trackVariables(analyserModel->constants(), true);
    }
}

void Generator::GeneratorImpl::untrackAllConstants(const AnalyserModelPtr &analyserModel)
{
    if (validModel(analyserModel)) {
        trackVariables(analyserModel->constants(), false);
    }
}

void Generator::GeneratorImpl::trackAllComputedConstants(const AnalyserModelPtr &analyserModel)
{
    if (validModel(analyserModel)) {
        trackVariables(analyserModel->computedConstants(), true);
    }
}

void Generator::GeneratorImpl::untrackAllComputedConstants(const AnalyserModelPtr &analyserModel)
{
    if (validModel(analyserModel)) {
        trackVariables(analyserModel->computedConstants(), false);
    }
}

void Generator::GeneratorImpl::trackAllAlgebraic(const AnalyserModelPtr &analyserModel)
{
    if (validModel(analyserModel)) {
        trackVariables(analyserModel->algebraicVariables(), true);
    }
}

void Generator::GeneratorImpl::untrackAllAlgebraic(const AnalyserModelPtr &analyserModel)
{
    if (validModel(analyserModel)) {
        trackVariables(analyserModel->algebraicVariables(), false);
    }
}

std::vector<AnalyserVariablePtr> Generator::GeneratorImpl::trackableVariables(const AnalyserModelPtr &analyserModel) const
{
    auto res = analyserModel->constants();
    auto computedConstants = analyserModel->computedConstants();
    auto algebraic = analyserModel->algebraicVariables();

    res.insert(res.end(), computedConstants.begin(), computedConstants.end());
    res.insert(res.end(), algebraic.begin(), algebraic.end());

    return res;
}

void Generator::GeneratorImpl::trackAllVariables(const AnalyserModelPtr &analyserModel)
{
    if (validModel(analyserModel)) {
        trackVariables(trackableVariables(analyserModel), true);
    }
}

void Generator::GeneratorImpl::untrackAllVariables(const AnalyserModelPtr &analyserModel)
{
    if (validModel(analyserModel)) {
        trackVariables(trackableVariables(analyserModel), false);
    }
}

size_t Generator::GeneratorImpl::doTrackedVariableCount(const AnalyserModelPtr &analyserModel,
                                                        const std::vector<AnalyserVariablePtr> &analyserVariables, bool tracked)
{
    size_t res = 0;

    for (const auto &analyserVariable : analyserVariables) {
        if (trackableVariable(analyserVariable, tracked, false)) {
            if (doIsTrackedVariable(analyserModel, analyserVariable, tracked)) {
                ++res;
            }
        } else {
            // The analyser variable is not trackable per se, which means that it is always tracked.

            ++res;
        }
    }

    return res;
}

size_t Generator::GeneratorImpl::trackedConstantCount(const AnalyserModelPtr &analyserModel)
{
    if (analyserModel == nullptr) {
        return 0;
    }

    return doTrackedVariableCount(analyserModel, analyserModel->constants(), true);
}

size_t Generator::GeneratorImpl::untrackedConstantCount(const AnalyserModelPtr &analyserModel)
{
    if (analyserModel == nullptr) {
        return 0;
    }

    return doTrackedVariableCount(analyserModel, analyserModel->constants(), false);
}

size_t Generator::GeneratorImpl::trackedComputedConstantCount(const AnalyserModelPtr &analyserModel)
{
    if (analyserModel == nullptr) {
        return 0;
    }

    return doTrackedVariableCount(analyserModel, analyserModel->computedConstants(), true);
}

size_t Generator::GeneratorImpl::untrackedComputedConstantCount(const AnalyserModelPtr &analyserModel)
{
    if (analyserModel == nullptr) {
        return 0;
    }

    return doTrackedVariableCount(analyserModel, analyserModel->computedConstants(), false);
}

size_t Generator::GeneratorImpl::trackedAlgebraicCount(const AnalyserModelPtr &analyserModel)
{
    if (analyserModel == nullptr) {
        return 0;
    }

    return doTrackedVariableCount(analyserModel, analyserModel->algebraicVariables(), true);
}

size_t Generator::GeneratorImpl::untrackedAlgebraicCount(const AnalyserModelPtr &analyserModel)
{
    if (analyserModel == nullptr) {
        return 0;
    }

    return doTrackedVariableCount(analyserModel, analyserModel->algebraicVariables(), false);
}

size_t Generator::GeneratorImpl::trackedVariableCount(const AnalyserModelPtr &analyserModel)
{
    if (analyserModel == nullptr) {
        return 0;
    }

    return doTrackedVariableCount(analyserModel, trackableVariables(analyserModel), true);
}

size_t Generator::GeneratorImpl::untrackedVariableCount(const AnalyserModelPtr &analyserModel)
{
    if (analyserModel == nullptr) {
        return 0;
    }

    return doTrackedVariableCount(analyserModel, trackableVariables(analyserModel), false);
}

bool Generator::GeneratorImpl::modelHasOdes(const AnalyserModelPtr &analyserModel) const
{
    switch (analyserModel->type()) {
    case AnalyserModel::Type::ODE:
    case AnalyserModel::Type::DAE:
        return true;
    default:
        return false;
    }
}

bool Generator::GeneratorImpl::modelHasNlas(const AnalyserModelPtr &analyserModel) const
{
    switch (analyserModel->type()) {
    case AnalyserModel::Type::NLA:
    case AnalyserModel::Type::DAE:
        return true;
    default:
        return false;
    }
}

AnalyserVariablePtr Generator::GeneratorImpl::analyserVariable(const AnalyserModelPtr &analyserModel,
                                                               const VariablePtr &variable) const
{
    // Find and return the analyser variable associated with the given variable.

    AnalyserVariablePtr res;
    auto modelVoi = analyserModel->voi();
    VariablePtr modelVoiVariable = (modelVoi != nullptr) ? modelVoi->variable() : nullptr;

    if ((modelVoiVariable != nullptr)
        && analyserModel->areEquivalentVariables(variable, modelVoiVariable)) {
        res = modelVoi;
    } else {
        auto modelAnalyserVariables = analyserVariables(analyserModel);

        res = *std::find_if(modelAnalyserVariables.begin(), modelAnalyserVariables.end(), [=](const auto &modelAnalyserVariable) {
            return analyserModel->areEquivalentVariables(modelAnalyserVariable->variable(), variable);
        });
    }

    return res;
}

double Generator::GeneratorImpl::scalingFactor(const AnalyserModelPtr &analyserModel, const VariablePtr &variable) const
{
    // Return the scaling factor for the given variable, accounting for the fact that a constant may be initialised by
    // another variable which initial value may be defined in a different component.

    auto analyserVariable = analyserModel->analyserVariable(variable);

    if ((analyserVariable->type() == AnalyserVariable::Type::CONSTANT)
        && !isCellMLReal(variable->initialValue())) {
        auto variableComponent = owningComponent(variable);
        auto initialValueVariable = variableComponent->variable(variable->initialValue());
        auto initialValueAnalyserVariable = analyserModel->analyserVariable(initialValueVariable);

        if (variableComponent != owningComponent(initialValueAnalyserVariable->variable())) {
            return Units::scalingFactor(initialValueVariable->units(), variable->units());
        }
    }

    return Units::scalingFactor(analyserVariable->variable()->units(), variable->units());
}

bool Generator::GeneratorImpl::isNegativeNumber(const AnalyserEquationAstPtr &ast) const
{
    if (ast->type() == AnalyserEquationAst::Type::CN) {
        double doubleValue;

        convertToDouble(ast->value(), doubleValue);

        return doubleValue < 0.0;
    }

    return false;
}

bool Generator::GeneratorImpl::isRelationalOperator(const AnalyserEquationAstPtr &ast) const
{
    switch (ast->type()) {
    case AnalyserEquationAst::Type::EQ:
        return mProfile->hasEqOperator();
    case AnalyserEquationAst::Type::NEQ:
        return mProfile->hasNeqOperator();
    case AnalyserEquationAst::Type::LT:
        return mProfile->hasLtOperator();
    case AnalyserEquationAst::Type::LEQ:
        return mProfile->hasLeqOperator();
    case AnalyserEquationAst::Type::GT:
        return mProfile->hasGtOperator();
    case AnalyserEquationAst::Type::GEQ:
        return mProfile->hasGeqOperator();
    default:
        return false;
    }
}

bool Generator::GeneratorImpl::isAndOperator(const AnalyserEquationAstPtr &ast) const
{
    return (ast->type() == AnalyserEquationAst::Type::AND)
           && mProfile->hasAndOperator();
}

bool Generator::GeneratorImpl::isOrOperator(const AnalyserEquationAstPtr &ast) const
{
    return (ast->type() == AnalyserEquationAst::Type::OR)
           && mProfile->hasOrOperator();
}

bool Generator::GeneratorImpl::isXorOperator(const AnalyserEquationAstPtr &ast) const
{
    return (ast->type() == AnalyserEquationAst::Type::XOR)
           && mProfile->hasXorOperator();
}

bool Generator::GeneratorImpl::isLogicalOperator(const AnalyserEquationAstPtr &ast) const
{
    // Note: AnalyserEquationAst::Type::NOT is a unary logical operator, hence
    //       we don't include it here since this method is only used to
    //       determine whether parentheses should be added around some code.

    return isAndOperator(ast) || isOrOperator(ast) || isXorOperator(ast);
}

bool Generator::GeneratorImpl::isPlusOperator(const AnalyserEquationAstPtr &ast) const
{
    return ast->type() == AnalyserEquationAst::Type::PLUS;
}

bool Generator::GeneratorImpl::isMinusOperator(const AnalyserEquationAstPtr &ast) const
{
    return ast->type() == AnalyserEquationAst::Type::MINUS;
}

bool Generator::GeneratorImpl::isTimesOperator(const AnalyserEquationAstPtr &ast) const
{
    return ast->type() == AnalyserEquationAst::Type::TIMES;
}

bool Generator::GeneratorImpl::isDivideOperator(const AnalyserEquationAstPtr &ast) const
{
    return ast->type() == AnalyserEquationAst::Type::DIVIDE;
}

bool Generator::GeneratorImpl::isPowerOperator(const AnalyserEquationAstPtr &ast) const
{
    return (ast->type() == AnalyserEquationAst::Type::POWER)
           && mProfile->hasPowerOperator();
}

bool Generator::GeneratorImpl::isRootOperator(const AnalyserEquationAstPtr &ast) const
{
    return (ast->type() == AnalyserEquationAst::Type::ROOT)
           && mProfile->hasPowerOperator();
}

bool Generator::GeneratorImpl::isPiecewiseStatement(const AnalyserEquationAstPtr &ast) const
{
    return (ast->type() == AnalyserEquationAst::Type::PIECEWISE)
           && mProfile->hasConditionalOperator();
}

void Generator::GeneratorImpl::updateVariableInfoSizes(size_t &componentSize,
                                                       size_t &nameSize,
                                                       size_t &unitsSize,
                                                       const AnalyserVariablePtr &analyserVariable) const
{
    auto analyserVariableVariable = analyserVariable->variable();
    auto variableComponentSize = owningComponent(analyserVariableVariable)->name().length() + 1;
    auto variableNameSize = analyserVariableVariable->name().length() + 1;
    auto variableUnitsSize = analyserVariableVariable->units()->name().length() + 1;
    // Note: +1 to account for the end of string termination.

    componentSize = (componentSize > variableComponentSize) ? componentSize : variableComponentSize;
    nameSize = (nameSize > variableNameSize) ? nameSize : variableNameSize;
    unitsSize = (unitsSize > variableUnitsSize) ? unitsSize : variableUnitsSize;
}

bool Generator::GeneratorImpl::modifiedProfile() const
{
    std::string profileContents = generatorProfileAsString(mProfile);

    return (mProfile->profile() == GeneratorProfile::Profile::C) ?
               sha1(profileContents) != C_GENERATOR_PROFILE_SHA1 :
               sha1(profileContents) != PYTHON_GENERATOR_PROFILE_SHA1;
}

std::string Generator::GeneratorImpl::newLineIfNeeded()
{
    return mCode.empty() ? "" : "\n";
}

void Generator::GeneratorImpl::addOriginCommentCode()
{
    if (!mProfile->commentString().empty()
        && !mProfile->originCommentString().empty()) {
        std::string profileInformation = modifiedProfile() ?
                                             "a modified " :
                                             "the ";

        profileInformation += (mProfile->profile() == GeneratorProfile::Profile::C) ?
                                  "C" :
                                  "Python";
        profileInformation += " profile of";

        mCode += newLineIfNeeded()
                 + replace(mProfile->commentString(),
                           "[CODE]", replace(replace(mProfile->originCommentString(), "[PROFILE_INFORMATION]", profileInformation), "[LIBCELLML_VERSION]", versionString()));
    }
}

void Generator::GeneratorImpl::addInterfaceHeaderCode()
{
    if (!mProfile->interfaceHeaderString().empty()) {
        mCode += newLineIfNeeded()
                 + mProfile->interfaceHeaderString();
    }
}

void Generator::GeneratorImpl::addImplementationHeaderCode()
{
    auto hasInterfaceFileName = mProfile->implementationHeaderString().empty() ?
                                    false :
                                    (mProfile->implementationHeaderString().find("[INTERFACE_FILE_NAME]") != std::string::npos);

    if (!mProfile->implementationHeaderString().empty()
        && ((hasInterfaceFileName && !mProfile->interfaceFileNameString().empty())
            || !hasInterfaceFileName)) {
        mCode += newLineIfNeeded()
                 + replace(mProfile->implementationHeaderString(),
                           "[INTERFACE_FILE_NAME]", mProfile->interfaceFileNameString());
    }
}

void Generator::GeneratorImpl::addVersionAndLibcellmlVersionCode(bool interface)
{
    std::string code;

    if ((interface && !mProfile->interfaceVersionString().empty())
        || (!interface && !mProfile->implementationVersionString().empty())) {
        if (interface) {
            code += mProfile->interfaceVersionString();
        } else {
            if (modifiedProfile()) {
                static const std::regex regEx("([0-9]+\\.[0-9]+\\.[0-9]+)");

                code += std::regex_replace(mProfile->implementationVersionString(), regEx, "$1.post0");
            } else {
                code += mProfile->implementationVersionString();
            }
        }
    }

    if ((interface && !mProfile->interfaceLibcellmlVersionString().empty())
        || (!interface && !mProfile->implementationLibcellmlVersionString().empty())) {
        code += interface ?
                    mProfile->interfaceLibcellmlVersionString() :
                    replace(mProfile->implementationLibcellmlVersionString(),
                            "[LIBCELLML_VERSION]", versionString());
    }

    if (!code.empty()) {
        mCode += newLineIfNeeded()
                 + code;
    }
}

void Generator::GeneratorImpl::addStateAndVariableCountCode(const AnalyserModelPtr &analyserModel, bool interface)
{
    std::string code;

    if (modelHasOdes(analyserModel)
        && ((interface && !mProfile->interfaceStateCountString().empty())
            || (!interface && !mProfile->implementationStateCountString().empty()))) {
        code += interface ?
                    mProfile->interfaceStateCountString() :
                    replace(mProfile->implementationStateCountString(),
                            "[STATE_COUNT]", std::to_string(analyserModel->stateCount()));
    }

    if ((interface && !mProfile->interfaceConstantCountString().empty())
        || (!interface && !mProfile->implementationConstantCountString().empty())) {
        code += interface ?
                    mProfile->interfaceConstantCountString() :
                    replace(mProfile->implementationConstantCountString(),
                            "[CONSTANT_COUNT]", std::to_string(doTrackedVariableCount(analyserModel, analyserModel->constants(), true)));
    }

    if ((interface && !mProfile->interfaceComputedConstantCountString().empty())
        || (!interface && !mProfile->implementationComputedConstantCountString().empty())) {
        code += interface ?
                    mProfile->interfaceComputedConstantCountString() :
                    replace(mProfile->implementationComputedConstantCountString(),
                            "[COMPUTED_CONSTANT_COUNT]", std::to_string(doTrackedVariableCount(analyserModel, analyserModel->computedConstants(), true)));
    }

    if ((interface && !mProfile->interfaceAlgebraicVariableCountString().empty())
        || (!interface && !mProfile->implementationAlgebraicVariableCountString().empty())) {
        code += interface ?
                    mProfile->interfaceAlgebraicVariableCountString() :
                    replace(mProfile->implementationAlgebraicVariableCountString(),
                            "[ALGEBRAIC_VARIABLE_COUNT]", std::to_string(doTrackedVariableCount(analyserModel, analyserModel->algebraicVariables(), true)));
    }

    if ((analyserModel->externalVariableCount() != 0)
        && ((interface && !mProfile->interfaceExternalVariableCountString().empty())
            || (!interface && !mProfile->implementationExternalVariableCountString().empty()))) {
        code += interface ?
                    mProfile->interfaceExternalVariableCountString() :
                    replace(mProfile->implementationExternalVariableCountString(),
                            "[EXTERNAL_VARIABLE_COUNT]", std::to_string(analyserModel->externalVariableCount()));
    }

    if (!code.empty()) {
        mCode += newLineIfNeeded()
                 + code;
    }
}

std::string Generator::GeneratorImpl::generateVariableInfoObjectCode(const AnalyserModelPtr &analyserModel,
                                                                     const std::string &objectString)
{
    size_t componentSize = 0;
    size_t nameSize = 0;
    size_t unitsSize = 0;

    for (const auto &analyserVariable : analyserVariables(analyserModel)) {
        if (doIsTrackedVariable(analyserModel, analyserVariable)) {
            updateVariableInfoSizes(componentSize, nameSize, unitsSize, analyserVariable);
        }
    }

    return replace(replace(replace(objectString,
                                   "[COMPONENT_SIZE]", std::to_string(componentSize)),
                           "[NAME_SIZE]", std::to_string(nameSize)),
                   "[UNITS_SIZE]", std::to_string(unitsSize));
}

void Generator::GeneratorImpl::addVariableInfoObjectCode(const AnalyserModelPtr &analyserModel)
{
    if (!mProfile->variableInfoObjectString().empty()) {
        mCode += newLineIfNeeded()
                 + generateVariableInfoObjectCode(analyserModel, mProfile->variableInfoObjectString());
    }
}

std::string Generator::GeneratorImpl::generateVariableInfoEntryCode(const std::string &name,
                                                                    const std::string &units,
                                                                    const std::string &component) const
{
    return replace(replace(replace(mProfile->variableInfoEntryString(),
                                   "[NAME]", name),
                           "[UNITS]", units),
                   "[COMPONENT]", component);
}

void Generator::GeneratorImpl::addInterfaceVariableInfoCode(const AnalyserModelPtr &analyserModel)
{
    std::string code;

    if (modelHasOdes(analyserModel)
        && !mProfile->interfaceVoiInfoString().empty()) {
        code += mProfile->interfaceVoiInfoString();
    }

    if (modelHasOdes(analyserModel)
        && !mProfile->interfaceStateInfoString().empty()) {
        code += mProfile->interfaceStateInfoString();
    }

    if (!mProfile->interfaceConstantInfoString().empty()) {
        code += mProfile->interfaceConstantInfoString();
    }

    if (!mProfile->interfaceComputedConstantInfoString().empty()) {
        code += mProfile->interfaceComputedConstantInfoString();
    }

    if (!mProfile->interfaceAlgebraicVariableInfoString().empty()) {
        code += mProfile->interfaceAlgebraicVariableInfoString();
    }

    if (analyserModel->hasExternalVariables()
        && !mProfile->interfaceExternalVariableInfoString().empty()) {
        code += mProfile->interfaceExternalVariableInfoString();
    }

    if (!code.empty()) {
        mCode += newLineIfNeeded()
                 + code;
    }
}

void Generator::GeneratorImpl::addImplementationVariableInfoCode(const std::string &variableInfoString,
                                                                 const std::vector<AnalyserVariablePtr> &analyserVariables,
                                                                 bool voiVariable)
{
    if (!variableInfoString.empty()
        && !mProfile->variableInfoEntryString().empty()
        && !mProfile->arrayElementSeparatorString().empty()) {
        auto analyserModel = analyserVariables.empty() ? nullptr : analyserVariables.front()->model();
        std::string infoElementsCode;

        for (const auto &analyserVariable : analyserVariables) {
            if (doIsTrackedVariable(analyserModel, analyserVariable)) {
                if (!infoElementsCode.empty()) {
                    infoElementsCode += mProfile->arrayElementSeparatorString() + "\n";
                }

                auto analyserVariableVariable = analyserVariable->variable();

                infoElementsCode += (voiVariable ? "" : mProfile->indentString())
                                    + generateVariableInfoEntryCode(analyserVariableVariable->name(),
                                                                    analyserVariableVariable->units()->name(),
                                                                    owningComponent(analyserVariableVariable)->name());
            }
        }

        if (!voiVariable && !infoElementsCode.empty()) {
            infoElementsCode += "\n";
        }

        mCode += newLineIfNeeded()
                 + replace(variableInfoString, "[CODE]", infoElementsCode);
    }
}

void Generator::GeneratorImpl::addImplementationVariableInfoCode(const AnalyserModelPtr &analyserModel)
{
    if (modelHasOdes(analyserModel)) {
        addImplementationVariableInfoCode(mProfile->implementationVoiInfoString(), {analyserModel->voi()}, true);
        addImplementationVariableInfoCode(mProfile->implementationStateInfoString(), analyserModel->states(), false);
    }

    addImplementationVariableInfoCode(mProfile->implementationConstantInfoString(), analyserModel->constants(), false);
    addImplementationVariableInfoCode(mProfile->implementationComputedConstantInfoString(), analyserModel->computedConstants(), false);
    addImplementationVariableInfoCode(mProfile->implementationAlgebraicVariableInfoString(), analyserModel->algebraicVariables(), false);

    if (analyserModel->hasExternalVariables()) {
        addImplementationVariableInfoCode(mProfile->implementationExternalVariableInfoString(), analyserModel->externalVariables(), false);
    }
}

void Generator::GeneratorImpl::addArithmeticFunctionsCode(const AnalyserModelPtr &analyserModel)
{
    if (analyserModel->needEqFunction() && !mProfile->hasEqOperator()
        && !mProfile->eqFunctionString().empty()) {
        mCode += newLineIfNeeded()
                 + mProfile->eqFunctionString();
    }

    if (analyserModel->needNeqFunction() && !mProfile->hasNeqOperator()
        && !mProfile->neqFunctionString().empty()) {
        mCode += newLineIfNeeded()
                 + mProfile->neqFunctionString();
    }

    if (analyserModel->needLtFunction() && !mProfile->hasLtOperator()
        && !mProfile->ltFunctionString().empty()) {
        mCode += newLineIfNeeded()
                 + mProfile->ltFunctionString();
    }

    if (analyserModel->needLeqFunction() && !mProfile->hasLeqOperator()
        && !mProfile->leqFunctionString().empty()) {
        mCode += newLineIfNeeded()
                 + mProfile->leqFunctionString();
    }

    if (analyserModel->needGtFunction() && !mProfile->hasGtOperator()
        && !mProfile->gtFunctionString().empty()) {
        mCode += newLineIfNeeded()
                 + mProfile->gtFunctionString();
    }

    if (analyserModel->needGeqFunction() && !mProfile->hasGeqOperator()
        && !mProfile->geqFunctionString().empty()) {
        mCode += newLineIfNeeded()
                 + mProfile->geqFunctionString();
    }

    if (analyserModel->needAndFunction() && !mProfile->hasAndOperator()
        && !mProfile->andFunctionString().empty()) {
        mCode += newLineIfNeeded()
                 + mProfile->andFunctionString();
    }

    if (analyserModel->needOrFunction() && !mProfile->hasOrOperator()
        && !mProfile->orFunctionString().empty()) {
        mCode += newLineIfNeeded()
                 + mProfile->orFunctionString();
    }

    if (analyserModel->needXorFunction() && !mProfile->hasXorOperator()
        && !mProfile->xorFunctionString().empty()) {
        mCode += newLineIfNeeded()
                 + mProfile->xorFunctionString();
    }

    if (analyserModel->needNotFunction() && !mProfile->hasNotOperator()
        && !mProfile->notFunctionString().empty()) {
        mCode += newLineIfNeeded()
                 + mProfile->notFunctionString();
    }

    if (analyserModel->needMinFunction()
        && !mProfile->minFunctionString().empty()) {
        mCode += newLineIfNeeded()
                 + mProfile->minFunctionString();
    }

    if (analyserModel->needMaxFunction()
        && !mProfile->maxFunctionString().empty()) {
        mCode += newLineIfNeeded()
                 + mProfile->maxFunctionString();
    }
}

void Generator::GeneratorImpl::addTrigonometricFunctionsCode(const AnalyserModelPtr &analyserModel)
{
    if (analyserModel->needSecFunction()
        && !mProfile->secFunctionString().empty()) {
        mCode += newLineIfNeeded()
                 + mProfile->secFunctionString();
    }

    if (analyserModel->needCscFunction()
        && !mProfile->cscFunctionString().empty()) {
        mCode += newLineIfNeeded()
                 + mProfile->cscFunctionString();
    }

    if (analyserModel->needCotFunction()
        && !mProfile->cotFunctionString().empty()) {
        mCode += newLineIfNeeded()
                 + mProfile->cotFunctionString();
    }

    if (analyserModel->needSechFunction()
        && !mProfile->sechFunctionString().empty()) {
        mCode += newLineIfNeeded()
                 + mProfile->sechFunctionString();
    }

    if (analyserModel->needCschFunction()
        && !mProfile->cschFunctionString().empty()) {
        mCode += newLineIfNeeded()
                 + mProfile->cschFunctionString();
    }

    if (analyserModel->needCothFunction()
        && !mProfile->cothFunctionString().empty()) {
        mCode += newLineIfNeeded()
                 + mProfile->cothFunctionString();
    }

    if (analyserModel->needAsecFunction()
        && !mProfile->asecFunctionString().empty()) {
        mCode += newLineIfNeeded()
                 + mProfile->asecFunctionString();
    }

    if (analyserModel->needAcscFunction()
        && !mProfile->acscFunctionString().empty()) {
        mCode += newLineIfNeeded()
                 + mProfile->acscFunctionString();
    }

    if (analyserModel->needAcotFunction()
        && !mProfile->acotFunctionString().empty()) {
        mCode += newLineIfNeeded()
                 + mProfile->acotFunctionString();
    }

    if (analyserModel->needAsechFunction()
        && !mProfile->asechFunctionString().empty()) {
        mCode += newLineIfNeeded()
                 + mProfile->asechFunctionString();
    }

    if (analyserModel->needAcschFunction()
        && !mProfile->acschFunctionString().empty()) {
        mCode += newLineIfNeeded()
                 + mProfile->acschFunctionString();
    }

    if (analyserModel->needAcothFunction()
        && !mProfile->acothFunctionString().empty()) {
        mCode += newLineIfNeeded()
                 + mProfile->acothFunctionString();
    }
}

void Generator::GeneratorImpl::addInterfaceCreateDeleteArrayMethodsCode(const AnalyserModelPtr &analyserModel)
{
    std::string code;

    if (modelHasOdes(analyserModel)
        && !mProfile->interfaceCreateStatesArrayMethodString().empty()) {
        code += mProfile->interfaceCreateStatesArrayMethodString();
    }

    if (!mProfile->interfaceCreateConstantsArrayMethodString().empty()) {
        code += mProfile->interfaceCreateConstantsArrayMethodString();
    }

    if (!mProfile->interfaceCreateComputedConstantsArrayMethodString().empty()) {
        code += mProfile->interfaceCreateComputedConstantsArrayMethodString();
    }

    if (!mProfile->interfaceCreateAlgebraicVariablesArrayMethodString().empty()) {
        code += mProfile->interfaceCreateAlgebraicVariablesArrayMethodString();
    }

    if (analyserModel->hasExternalVariables()
        && !mProfile->interfaceCreateExternalVariablesArrayMethodString().empty()) {
        code += mProfile->interfaceCreateExternalVariablesArrayMethodString();
    }

    if (!mProfile->interfaceDeleteArrayMethodString().empty()) {
        code += "\n"
                + mProfile->interfaceDeleteArrayMethodString();
    }

    if (!code.empty()) {
        mCode += newLineIfNeeded()
                 + code;
    }
}

void Generator::GeneratorImpl::addImplementationCreateDeleteArrayMethodsCode(const AnalyserModelPtr &analyserModel)
{
    if (modelHasOdes(analyserModel)
        && !mProfile->implementationCreateStatesArrayMethodString().empty()) {
        mCode += newLineIfNeeded()
                 + mProfile->implementationCreateStatesArrayMethodString();
    }

    if (!mProfile->implementationCreateConstantsArrayMethodString().empty()) {
        mCode += newLineIfNeeded()
                 + mProfile->implementationCreateConstantsArrayMethodString();
    }

    if (!mProfile->implementationCreateComputedConstantsArrayMethodString().empty()) {
        mCode += newLineIfNeeded()
                 + mProfile->implementationCreateComputedConstantsArrayMethodString();
    }

    if (!mProfile->implementationCreateAlgebraicVariablesArrayMethodString().empty()) {
        mCode += newLineIfNeeded()
                 + mProfile->implementationCreateAlgebraicVariablesArrayMethodString();
    }

    if (analyserModel->hasExternalVariables()
        && !mProfile->implementationCreateExternalVariablesArrayMethodString().empty()) {
        mCode += newLineIfNeeded()
                 + mProfile->implementationCreateExternalVariablesArrayMethodString();
    }

    if (!mProfile->implementationDeleteArrayMethodString().empty()) {
        mCode += newLineIfNeeded()
                 + mProfile->implementationDeleteArrayMethodString();
    }
}

void Generator::GeneratorImpl::addExternalVariableMethodTypeDefinitionCode(const AnalyserModelPtr &analyserModel)
{
    if (analyserModel->hasExternalVariables()) {
        auto externalVariableMethodTypeDefinitionString = mProfile->externalVariableMethodTypeDefinitionString(modelHasOdes(analyserModel));

        if (!externalVariableMethodTypeDefinitionString.empty()) {
            mCode += newLineIfNeeded()
                     + externalVariableMethodTypeDefinitionString;
        }
    }
}

void Generator::GeneratorImpl::addRootFindingInfoObjectCode(const AnalyserModelPtr &analyserModel)
{
    if (!mProfile->rootFindingInfoObjectString(modelHasOdes(analyserModel), analyserModel->hasExternalVariables()).empty()) {
        mCode += newLineIfNeeded()
                 + mProfile->rootFindingInfoObjectString(modelHasOdes(analyserModel), analyserModel->hasExternalVariables());
    }
}

void Generator::GeneratorImpl::addExternNlaSolveMethodCode()
{
    if (!mProfile->externNlaSolveMethodString().empty()) {
        mCode += newLineIfNeeded()
                 + mProfile->externNlaSolveMethodString();
    }
}

void Generator::GeneratorImpl::addNlaSystemsCode(const AnalyserModelPtr &analyserModel)
{
    if (!mProfile->objectiveFunctionMethodString(modelHasOdes(analyserModel), analyserModel->hasExternalVariables()).empty()
        && !mProfile->findRootMethodString(modelHasOdes(analyserModel), analyserModel->hasExternalVariables()).empty()
        && !mProfile->nlaSolveCallString(modelHasOdes(analyserModel), analyserModel->hasExternalVariables()).empty()) {
        // Note: only states and algebraic variables can be computed through an NLA system. Constants, computed
        //       constants, and external variables cannot, by definition, be computed through an NLA system.

        std::vector<AnalyserEquationPtr> handledNlaAnalyserEquations;

        for (const auto &analyserEquation : analyserModel->analyserEquations()) {
            if ((analyserEquation->type() == AnalyserEquation::Type::NLA)
                && (std::find(handledNlaAnalyserEquations.begin(), handledNlaAnalyserEquations.end(), analyserEquation) == handledNlaAnalyserEquations.end())) {
                // 1) Generate some code for the objectiveFunction[INDEX]() method.
                //     a) Retrieve the values from our NLA solver's u array.

                std::string methodBody;
                auto i = MAX_SIZE_T;
                auto analyserVariables = libcellml::analyserVariables(analyserEquation);

                for (const auto &analyserVariable : analyserVariables) {
                    auto arrayString = (analyserVariable->type() == AnalyserVariable::Type::STATE) ?
                                           mProfile->ratesArrayString() :
                                           mProfile->algebraicVariablesArrayString();

                    methodBody += mProfile->indentString()
                                  + arrayString + mProfile->openArrayString() + analyserVariableIndexString(analyserModel, analyserVariable) + mProfile->closeArrayString()
                                  + mProfile->equalityString()
                                  + mProfile->uArrayString() + mProfile->openArrayString() + convertToString(++i) + mProfile->closeArrayString()
                                  + mProfile->commandSeparatorString() + "\n";
                }

                //     b) Initialise any untracked constant, computed constant, or algebraic variable that is needed by
                //        our NLA system.

                methodBody += "\n";

                auto methodBodySize = methodBody.size();

                for (const auto &constantDependency : analyserEquation->mPimpl->mConstantDependencies) {
                    if (doIsTrackedVariable(analyserModel, constantDependency, false)) {
                        methodBody += generateInitialisationCode(analyserModel, constantDependency, true);
                    }
                }

                std::vector<AnalyserEquationPtr> dummyRemainingAnalyserEquations = analyserModel->analyserEquations();
                std::vector<AnalyserEquationPtr> dummyAnalyserEquationsForDependencies;
                std::vector<AnalyserVariablePtr> dummyGeneratedConstantDependencies;

                for (const auto &dependency : analyserEquation->dependencies()) {
                    if (((dependency->type() == AnalyserEquation::Type::COMPUTED_CONSTANT)
                         || (dependency->type() == AnalyserEquation::Type::ALGEBRAIC))
                        && isUntrackedEquation(dependency)) {
                        methodBody += generateEquationCode(analyserModel, dependency, dummyRemainingAnalyserEquations,
                                                           dummyAnalyserEquationsForDependencies,
                                                           dummyGeneratedConstantDependencies, false,
                                                           GenerateEquationCodeTarget::OBJECTIVE_FUNCTION);
                    }
                }

                //     c) Generate our NLA system's objective functions.

                methodBody += (methodBody.size() == methodBodySize) ? "" : "\n";

                i = MAX_SIZE_T;

                methodBody += mProfile->indentString()
                              + mProfile->fArrayString() + mProfile->openArrayString() + convertToString(++i) + mProfile->closeArrayString()
                              + mProfile->equalityString()
                              + generateCode(analyserModel, analyserEquation->ast())
                              + mProfile->commandSeparatorString() + "\n";

                handledNlaAnalyserEquations.push_back(analyserEquation);

                for (const auto &nlaSibling : analyserEquation->nlaSiblings()) {
                    methodBody += mProfile->indentString()
                                  + mProfile->fArrayString() + mProfile->openArrayString() + convertToString(++i) + mProfile->closeArrayString()
                                  + mProfile->equalityString()
                                  + generateCode(analyserModel, nlaSibling->ast())
                                  + mProfile->commandSeparatorString() + "\n";

                    handledNlaAnalyserEquations.push_back(nlaSibling);
                }

                mCode += newLineIfNeeded()
                         + replace(replace(mProfile->objectiveFunctionMethodString(modelHasOdes(analyserModel), analyserModel->hasExternalVariables()),
                                           "[INDEX]", convertToString(analyserEquation->nlaSystemIndex())),
                                   "[CODE]", generateMethodBodyCode(methodBody));

                // 2) Generate some code for the findRoot[INDEX]() method.
                //     a) Assign the values to our NLA solver's u array.

                methodBody = {};

                i = MAX_SIZE_T;

                for (const auto &analyserVariable : analyserVariables) {
                    auto arrayString = (analyserVariable->type() == AnalyserVariable::Type::STATE) ?
                                           mProfile->ratesArrayString() :
                                           mProfile->algebraicVariablesArrayString();

                    methodBody += mProfile->indentString()
                                  + mProfile->uArrayString() + mProfile->openArrayString() + convertToString(++i) + mProfile->closeArrayString()
                                  + mProfile->equalityString()
                                  + arrayString + mProfile->openArrayString() + analyserVariableIndexString(analyserModel, analyserVariable) + mProfile->closeArrayString()
                                  + mProfile->commandSeparatorString() + "\n";
                }

                //     b) Call our NLA solver.

                auto analyserVariablesCount = analyserVariables.size();

                methodBody += "\n"
                              + mProfile->indentString()
                              + replace(replace(mProfile->nlaSolveCallString(modelHasOdes(analyserModel), analyserModel->hasExternalVariables()),
                                                "[INDEX]", convertToString(analyserEquation->nlaSystemIndex())),
                                        "[SIZE]", convertToString(analyserVariablesCount));

                //     c) Retrieve the values from our NLA solver's u array.

                i = MAX_SIZE_T;

                methodBody += "\n";

                for (const auto &analyserVariable : analyserVariables) {
                    auto arrayString = (analyserVariable->type() == AnalyserVariable::Type::STATE) ?
                                           mProfile->ratesArrayString() :
                                           mProfile->algebraicVariablesArrayString();

                    methodBody += mProfile->indentString()
                                  + arrayString + mProfile->openArrayString() + analyserVariableIndexString(analyserModel, analyserVariable) + mProfile->closeArrayString()
                                  + mProfile->equalityString()
                                  + mProfile->uArrayString() + mProfile->openArrayString() + convertToString(++i) + mProfile->closeArrayString()
                                  + mProfile->commandSeparatorString() + "\n";
                }

                mCode += newLineIfNeeded()
                         + replace(replace(replace(mProfile->findRootMethodString(modelHasOdes(analyserModel), analyserModel->hasExternalVariables()),
                                                   "[INDEX]", convertToString(analyserEquation->nlaSystemIndex())),
                                           "[SIZE]", convertToString(analyserVariablesCount)),
                                   "[CODE]", generateMethodBodyCode(methodBody));
            }
        }
    }
}

std::string Generator::GeneratorImpl::generateMethodBodyCode(const std::string &methodBody) const
{
    return methodBody.empty() ?
               mProfile->emptyMethodString().empty() ?
               "" :
               mProfile->indentString() + mProfile->emptyMethodString() :
               methodBody;
}

std::string generateDoubleCode(const std::string &value)
{
    if (value.find('.') != std::string::npos) {
        return value;
    }

    auto ePos = value.find_first_of("eE");

    if (ePos == std::string::npos) {
        return value + ".0";
    }

    return value.substr(0, ePos) + ".0" + value.substr(ePos);
}

std::string Generator::GeneratorImpl::generateDoubleOrConstantVariableNameCode(const AnalyserModelPtr &analyserModel,
                                                                               const VariablePtr &variable)
{
    if (isCellMLReal(variable->initialValue())) {
        return generateDoubleCode(variable->initialValue());
    }

    auto initialValueVariable = owningComponent(variable)->variable(variable->initialValue());
    auto analyserInitialValueVariable = analyserModel->analyserVariable(initialValueVariable);

    return mProfile->constantsArrayString() + mProfile->openArrayString() + analyserVariableIndexString(analyserModel, analyserInitialValueVariable) + mProfile->closeArrayString();
}

std::string Generator::GeneratorImpl::generateVariableNameCode(const AnalyserModelPtr &analyserModel,
                                                               const VariablePtr &variable,
                                                               bool state)
{
    // Generate some code for a variable name, but only if we have an analyser model. If we don't have an analyser
    // model, it means that we are using the generator from the analyser, in which case we just want to return the
    // original name of the variable.

    if (analyserModel == nullptr) {
        return variable->name();
    }

    auto analyserVariable = analyserModel->analyserVariable(variable);

    if (analyserVariable->type() == AnalyserVariable::Type::VARIABLE_OF_INTEGRATION) {
        return mProfile->voiString();
    }

    if (doIsTrackedVariable(analyserModel, analyserVariable, false)) {
        return owningComponent(analyserVariable->variable())->name() + "_" + analyserVariable->variable()->name();
    }

    std::string arrayName;

    if (analyserVariable->type() == AnalyserVariable::Type::STATE) {
        arrayName = state ?
                        mProfile->statesArrayString() :
                        mProfile->ratesArrayString();
    } else if (analyserVariable->type() == AnalyserVariable::Type::CONSTANT) {
        arrayName = mProfile->constantsArrayString();
    } else if (analyserVariable->type() == AnalyserVariable::Type::COMPUTED_CONSTANT) {
        arrayName = mProfile->computedConstantsArrayString();
    } else if (analyserVariable->type() == AnalyserVariable::Type::ALGEBRAIC_VARIABLE) {
        arrayName = mProfile->algebraicVariablesArrayString();
    } else {
        arrayName = mProfile->externalVariablesArrayString();
    }

    return arrayName + mProfile->openArrayString() + analyserVariableIndexString(analyserModel, analyserVariable) + mProfile->closeArrayString();
}

std::string Generator::GeneratorImpl::generateOperatorCode(const AnalyserModelPtr &analyserModel, const std::string &op,
                                                           const AnalyserEquationAstPtr &ast)
{
    // Generate the code for the left and right branches of the given AST.

    std::string res;
    auto astLeftChild = ast->leftChild();
    auto astRightChild = ast->rightChild();
    auto astLeftChildCode = generateCode(analyserModel, astLeftChild);
    auto astRightChildCode = generateCode(analyserModel, astRightChild);

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
        if (isRelationalOperator(astLeftChild)
            || isLogicalOperator(astLeftChild)
            || isPiecewiseStatement(astLeftChild)) {
            astLeftChildCode = "(" + astLeftChildCode + ")";
        }

        if (isRelationalOperator(astRightChild)
            || isLogicalOperator(astRightChild)
            || isPiecewiseStatement(astRightChild)) {
            astRightChildCode = "(" + astRightChildCode + ")";
        }
    } else if (isMinusOperator(ast)) {
        if (isRelationalOperator(astLeftChild)
            || isLogicalOperator(astLeftChild)
            || isPiecewiseStatement(astLeftChild)) {
            astLeftChildCode = "(" + astLeftChildCode + ")";
        }

        if (isNegativeNumber(astRightChild)
            || isRelationalOperator(astRightChild)
            || isLogicalOperator(astRightChild)
            || isMinusOperator(astRightChild)
            || isPiecewiseStatement(astRightChild)
            || (astRightChildCode.rfind(mProfile->minusString(), 0) == 0)) {
            astRightChildCode = "(" + astRightChildCode + ")";
        } else if (isPlusOperator(astRightChild)) {
            if (astRightChild->rightChild() != nullptr) {
                astRightChildCode = "(" + astRightChildCode + ")";
            }
        }
    } else if (isTimesOperator(ast)) {
        if (isRelationalOperator(astLeftChild)
            || isLogicalOperator(astLeftChild)
            || isPiecewiseStatement(astLeftChild)) {
            astLeftChildCode = "(" + astLeftChildCode + ")";
        } else if (isPlusOperator(astLeftChild)
                   || isMinusOperator(astLeftChild)) {
            if (astLeftChild->rightChild() != nullptr) {
                astLeftChildCode = "(" + astLeftChildCode + ")";
            }
        }

        if (isRelationalOperator(astRightChild)
            || isLogicalOperator(astRightChild)
            || isPiecewiseStatement(astRightChild)) {
            astRightChildCode = "(" + astRightChildCode + ")";
        } else if (isPlusOperator(astRightChild)
                   || isMinusOperator(astRightChild)) {
            if (astRightChild->rightChild() != nullptr) {
                astRightChildCode = "(" + astRightChildCode + ")";
            }
        }
    } else if (isDivideOperator(ast)) {
        if (isRelationalOperator(astLeftChild)
            || isLogicalOperator(astLeftChild)
            || isPiecewiseStatement(astLeftChild)) {
            astLeftChildCode = "(" + astLeftChildCode + ")";
        } else if (isPlusOperator(astLeftChild)
                   || isMinusOperator(astLeftChild)) {
            if (astLeftChild->rightChild() != nullptr) {
                astLeftChildCode = "(" + astLeftChildCode + ")";
            }
        }

        if (isRelationalOperator(astRightChild)
            || isLogicalOperator(astRightChild)
            || isTimesOperator(astRightChild)
            || isDivideOperator(astRightChild)
            || isPiecewiseStatement(astRightChild)) {
            astRightChildCode = "(" + astRightChildCode + ")";
        } else if (isPlusOperator(astRightChild)
                   || isMinusOperator(astRightChild)) {
            if (astRightChild->rightChild() != nullptr) {
                astRightChildCode = "(" + astRightChildCode + ")";
            }
        }
    } else if (isAndOperator(ast)) {
        // Note: according to the precedence rules above, we only need to
        //       add parentheses around OR and PIECEWISE. However, it looks
        //       better/clearer to have some around some other operators
        //       (agreed, this is somewhat subjective).

        if (isRelationalOperator(astLeftChild)
            || isOrOperator(astLeftChild)
            || isXorOperator(astLeftChild)
            || isPiecewiseStatement(astLeftChild)) {
            astLeftChildCode = "(" + astLeftChildCode + ")";
        } else if (isPlusOperator(astLeftChild)
                   || isMinusOperator(astLeftChild)) {
            if (astLeftChild->rightChild() != nullptr) {
                astLeftChildCode = "(" + astLeftChildCode + ")";
            }
        } else if (isPowerOperator(astLeftChild)) {
            astLeftChildCode = "(" + astLeftChildCode + ")";
        } else if (isRootOperator(astLeftChild)) {
            astLeftChildCode = "(" + astLeftChildCode + ")";
        }

        if (isRelationalOperator(astRightChild)
            || isOrOperator(astRightChild)
            || isXorOperator(astRightChild)
            || isPiecewiseStatement(astRightChild)) {
            astRightChildCode = "(" + astRightChildCode + ")";
        } else if (isPlusOperator(astRightChild)
                   || isMinusOperator(astRightChild)) {
            if (astRightChild->rightChild() != nullptr) {
                astRightChildCode = "(" + astRightChildCode + ")";
            }
        } else if (isPowerOperator(astRightChild)) {
            astRightChildCode = "(" + astRightChildCode + ")";
        } else if (isRootOperator(astRightChild)) {
            astRightChildCode = "(" + astRightChildCode + ")";
        }
    } else if (isOrOperator(ast)) {
        // Note: according to the precedence rules above, we only need to
        //       add parentheses around PIECEWISE. However, it looks
        //       better/clearer to have some around some other operators
        //       (agreed, this is somewhat subjective).

        if (isRelationalOperator(astLeftChild)
            || isAndOperator(astLeftChild)
            || isXorOperator(astLeftChild)
            || isPiecewiseStatement(astLeftChild)) {
            astLeftChildCode = "(" + astLeftChildCode + ")";
        } else if (isPlusOperator(astLeftChild)
                   || isMinusOperator(astLeftChild)) {
            if (astLeftChild->rightChild() != nullptr) {
                astLeftChildCode = "(" + astLeftChildCode + ")";
            }
        } else if (isPowerOperator(astLeftChild)) {
            astLeftChildCode = "(" + astLeftChildCode + ")";
        } else if (isRootOperator(astLeftChild)) {
            astLeftChildCode = "(" + astLeftChildCode + ")";
        }

        if (isRelationalOperator(astRightChild)
            || isAndOperator(astRightChild)
            || isXorOperator(astRightChild)
            || isPiecewiseStatement(astRightChild)) {
            astRightChildCode = "(" + astRightChildCode + ")";
        } else if (isPlusOperator(astRightChild)
                   || isMinusOperator(astRightChild)) {
            if (astRightChild->rightChild() != nullptr) {
                astRightChildCode = "(" + astRightChildCode + ")";
            }
        } else if (isPowerOperator(astRightChild)) {
            astRightChildCode = "(" + astRightChildCode + ")";
        } else if (isRootOperator(astRightChild)) {
            astRightChildCode = "(" + astRightChildCode + ")";
        }
    } else if (isXorOperator(ast)) {
        // Note: according to the precedence rules above, we only need to
        //       add parentheses around AND, OR and PIECEWISE. However, it
        //       looks better/clearer to have some around some other
        //       operators (agreed, this is somewhat subjective).

        if (isRelationalOperator(astLeftChild)
            || isAndOperator(astLeftChild)
            || isOrOperator(astLeftChild)
            || isPiecewiseStatement(astLeftChild)) {
            astLeftChildCode = "(" + astLeftChildCode + ")";
        } else if (isPlusOperator(astLeftChild)
                   || isMinusOperator(astLeftChild)) {
            if (astLeftChild->rightChild() != nullptr) {
                astLeftChildCode = "(" + astLeftChildCode + ")";
            }
        } else if (isPowerOperator(astLeftChild)) {
            astLeftChildCode = "(" + astLeftChildCode + ")";
        } else if (isRootOperator(astLeftChild)) {
            astLeftChildCode = "(" + astLeftChildCode + ")";
        }

        if (isRelationalOperator(astRightChild)
            || isAndOperator(astRightChild)
            || isOrOperator(astRightChild)
            || isPiecewiseStatement(astRightChild)) {
            astRightChildCode = "(" + astRightChildCode + ")";
        } else if (isPlusOperator(astRightChild)
                   || isMinusOperator(astRightChild)) {
            if (astRightChild->rightChild() != nullptr) {
                astRightChildCode = "(" + astRightChildCode + ")";
            }
        } else if (isPowerOperator(astRightChild)) {
            astRightChildCode = "(" + astRightChildCode + ")";
        } else if (isRootOperator(astRightChild)) {
            astRightChildCode = "(" + astRightChildCode + ")";
        }
    } else if (isPowerOperator(ast)) {
        if (isRelationalOperator(astLeftChild)
            || isLogicalOperator(astLeftChild)
            || isMinusOperator(astLeftChild)
            || isTimesOperator(astLeftChild)
            || isDivideOperator(astLeftChild)
            || isPiecewiseStatement(astLeftChild)) {
            astLeftChildCode = "(" + astLeftChildCode + ")";
        } else if (isPlusOperator(astLeftChild)) {
            if (astLeftChild->rightChild() != nullptr) {
                astLeftChildCode = "(" + astLeftChildCode + ")";
            }
        }

        if (isRelationalOperator(astRightChild)
            || isLogicalOperator(astRightChild)
            || isMinusOperator(astLeftChild)
            || isTimesOperator(astRightChild)
            || isDivideOperator(astRightChild)
            || isPowerOperator(astRightChild)
            || isRootOperator(astRightChild)
            || isPiecewiseStatement(astRightChild)) {
            astRightChildCode = "(" + astRightChildCode + ")";
        } else if (isPlusOperator(astRightChild)) {
            if (astRightChild->rightChild() != nullptr) {
                astRightChildCode = "(" + astRightChildCode + ")";
            }
        }
    } else if (isRootOperator(ast)) {
        if (isRelationalOperator(astRightChild)
            || isLogicalOperator(astRightChild)
            || isMinusOperator(astRightChild)
            || isTimesOperator(astRightChild)
            || isDivideOperator(astRightChild)
            || isPiecewiseStatement(astRightChild)) {
            astRightChildCode = "(" + astRightChildCode + ")";
        } else if (isPlusOperator(astRightChild)) {
            if (astRightChild->rightChild() != nullptr) {
                astRightChildCode = "(" + astRightChildCode + ")";
            }
        }

        auto astLeftChildLeftChild = astLeftChild->leftChild();

        if (isRelationalOperator(astLeftChildLeftChild)
            || isLogicalOperator(astLeftChildLeftChild)
            || isMinusOperator(astLeftChildLeftChild)
            || isTimesOperator(astLeftChildLeftChild)
            || isDivideOperator(astLeftChildLeftChild)
            || isPowerOperator(astLeftChildLeftChild)
            || isRootOperator(astLeftChildLeftChild)
            || isPiecewiseStatement(astLeftChildLeftChild)) {
            astLeftChildCode = "(" + astLeftChildCode + ")";
        } else if (isPlusOperator(astLeftChildLeftChild)) {
            if (astLeftChildLeftChild->rightChild() != nullptr) {
                astLeftChildCode = "(" + astLeftChildCode + ")";
            }
        }

        return astRightChildCode + op + "(1.0/" + astLeftChildCode + ")";
    }

    return astLeftChildCode + op + astRightChildCode;
}

std::string Generator::GeneratorImpl::generateMinusUnaryCode(const AnalyserModelPtr &analyserModel,
                                                             const AnalyserEquationAstPtr &ast)
{
    // Generate the code for the left branch of the given AST.

    auto astLeftChild = ast->leftChild();
    auto code = generateCode(analyserModel, astLeftChild);

    // Determine whether parentheses should be added around the left code.

    if (isRelationalOperator(astLeftChild)
        || isLogicalOperator(astLeftChild)
        || isPlusOperator(astLeftChild)
        || isMinusOperator(astLeftChild)
        || isPiecewiseStatement(astLeftChild)) {
        code = "(" + code + ")";
    }

    return mProfile->minusString() + code;
}

std::string Generator::GeneratorImpl::generateOneParameterFunctionCode(const AnalyserModelPtr &analyserModel,
                                                                       const std::string &function,
                                                                       const AnalyserEquationAstPtr &ast)
{
    return function + "(" + generateCode(analyserModel, ast->leftChild()) + ")";
}

std::string Generator::GeneratorImpl::generateTwoParameterFunctionCode(const AnalyserModelPtr &analyserModel,
                                                                       const std::string &function,
                                                                       const AnalyserEquationAstPtr &ast)
{
    return function + "(" + generateCode(analyserModel, ast->leftChild()) + ", " + generateCode(analyserModel, ast->rightChild()) + ")";
}

std::string Generator::GeneratorImpl::generatePiecewiseIfCode(const std::string &condition,
                                                              const std::string &value) const
{
    return replace(replace(mProfile->hasConditionalOperator() ?
                               mProfile->conditionalOperatorIfString() :
                               mProfile->piecewiseIfString(),
                           "[CONDITION]", condition),
                   "[IF_STATEMENT]", value);
}

std::string Generator::GeneratorImpl::generatePiecewiseElseCode(const std::string &value) const
{
    return replace(mProfile->hasConditionalOperator() ?
                       mProfile->conditionalOperatorElseString() :
                       mProfile->piecewiseElseString(),
                   "[ELSE_STATEMENT]", value);
}

std::string Generator::GeneratorImpl::generateCode(const AnalyserModelPtr &analyserModel,
                                                   const AnalyserEquationAstPtr &ast)
{
    // Generate the code for the given AST.
    // Note: AnalyserEquationAst::Type::BVAR is only relevant when there is no analyser model (in which case we want to
    //       generate something like dx/dt, as is in the case of the analyser when we want to mention an equation) since
    //       otherwise we don't need to generate any code for it (since we will, instead, want to generate something
    //       like rates[0]).

    std::string code;

    switch (ast->type()) {
    case AnalyserEquationAst::Type::EQUALITY:
        code = generateOperatorCode(analyserModel, mProfile->equalityString(), ast);

        break;
    case AnalyserEquationAst::Type::EQ:
        if (mProfile->hasEqOperator()) {
            code = generateOperatorCode(analyserModel, mProfile->eqString(), ast);
        } else {
            code = generateTwoParameterFunctionCode(analyserModel, mProfile->eqString(), ast);
        }

        break;
    case AnalyserEquationAst::Type::NEQ:
        if (mProfile->hasNeqOperator()) {
            code = generateOperatorCode(analyserModel, mProfile->neqString(), ast);
        } else {
            code = generateTwoParameterFunctionCode(analyserModel, mProfile->neqString(), ast);
        }

        break;
    case AnalyserEquationAst::Type::LT:
        if (mProfile->hasLtOperator()) {
            code = generateOperatorCode(analyserModel, mProfile->ltString(), ast);
        } else {
            code = generateTwoParameterFunctionCode(analyserModel, mProfile->ltString(), ast);
        }

        break;
    case AnalyserEquationAst::Type::LEQ:
        if (mProfile->hasLeqOperator()) {
            code = generateOperatorCode(analyserModel, mProfile->leqString(), ast);
        } else {
            code = generateTwoParameterFunctionCode(analyserModel, mProfile->leqString(), ast);
        }

        break;
    case AnalyserEquationAst::Type::GT:
        if (mProfile->hasGtOperator()) {
            code = generateOperatorCode(analyserModel, mProfile->gtString(), ast);
        } else {
            code = generateTwoParameterFunctionCode(analyserModel, mProfile->gtString(), ast);
        }

        break;
    case AnalyserEquationAst::Type::GEQ:
        if (mProfile->hasGeqOperator()) {
            code = generateOperatorCode(analyserModel, mProfile->geqString(), ast);
        } else {
            code = generateTwoParameterFunctionCode(analyserModel, mProfile->geqString(), ast);
        }

        break;
    case AnalyserEquationAst::Type::AND:
        if (mProfile->hasAndOperator()) {
            code = generateOperatorCode(analyserModel, mProfile->andString(), ast);
        } else {
            code = generateTwoParameterFunctionCode(analyserModel, mProfile->andString(), ast);
        }

        break;
    case AnalyserEquationAst::Type::OR:
        if (mProfile->hasOrOperator()) {
            code = generateOperatorCode(analyserModel, mProfile->orString(), ast);
        } else {
            code = generateTwoParameterFunctionCode(analyserModel, mProfile->orString(), ast);
        }

        break;
    case AnalyserEquationAst::Type::XOR:
        if (mProfile->hasXorOperator()) {
            code = generateOperatorCode(analyserModel, mProfile->xorString(), ast);
        } else {
            code = generateTwoParameterFunctionCode(analyserModel, mProfile->xorString(), ast);
        }

        break;
    case AnalyserEquationAst::Type::NOT:
        if (mProfile->hasNotOperator()) {
            code = mProfile->notString() + generateCode(analyserModel, ast->leftChild());
        } else {
            code = generateOneParameterFunctionCode(analyserModel, mProfile->notString(), ast);
        }

        break;
    case AnalyserEquationAst::Type::PLUS:
        if (ast->rightChild() != nullptr) {
            code = generateOperatorCode(analyserModel, mProfile->plusString(), ast);
        } else {
            code = generateCode(analyserModel, ast->leftChild());
        }

        break;
    case AnalyserEquationAst::Type::MINUS:
        if (ast->rightChild() != nullptr) {
            code = generateOperatorCode(analyserModel, mProfile->minusString(), ast);
        } else {
            code = generateMinusUnaryCode(analyserModel, ast);
        }

        break;
    case AnalyserEquationAst::Type::TIMES:
        code = generateOperatorCode(analyserModel, mProfile->timesString(), ast);

        break;
    case AnalyserEquationAst::Type::DIVIDE:
        code = generateOperatorCode(analyserModel, mProfile->divideString(), ast);

        break;
    case AnalyserEquationAst::Type::POWER: {
        auto stringValue = generateCode(analyserModel, ast->rightChild());
        double doubleValue;
        auto validConversion = convertToDouble(stringValue, doubleValue);

        if (validConversion && areEqual(doubleValue, 0.5)) {
            code = generateOneParameterFunctionCode(analyserModel, mProfile->squareRootString(), ast);
        } else if (validConversion && areEqual(doubleValue, 2.0)
                   && !mProfile->squareString().empty()) {
            code = generateOneParameterFunctionCode(analyserModel, mProfile->squareString(), ast);
        } else {
            code = mProfile->hasPowerOperator() ?
                       generateOperatorCode(analyserModel, mProfile->powerString(), ast) :
                       mProfile->powerString() + "(" + generateCode(analyserModel, ast->leftChild()) + ", " + stringValue + ")";
        }
    } break;
    case AnalyserEquationAst::Type::ROOT: {
        auto astRightChild = ast->rightChild();

        if (astRightChild != nullptr) {
            auto astLeftChild = ast->leftChild();
            double doubleValue;

            if (convertToDouble(generateCode(analyserModel, astLeftChild), doubleValue)
                && areEqual(doubleValue, 2.0)) {
                code = mProfile->squareRootString() + "(" + generateCode(analyserModel, astRightChild) + ")";
            } else {
                if (mProfile->hasPowerOperator()) {
                    code = generateOperatorCode(analyserModel, mProfile->powerString(), ast);
                } else {
                    auto rootValueAst = AnalyserEquationAst::create();

                    rootValueAst->setType(AnalyserEquationAst::Type::DIVIDE);
                    rootValueAst->setParent(ast);

                    auto leftChild = AnalyserEquationAst::create();

                    leftChild->setType(AnalyserEquationAst::Type::CN);
                    leftChild->setValue("1.0");
                    leftChild->setParent(rootValueAst);

                    rootValueAst->setLeftChild(leftChild);
                    rootValueAst->setRightChild(astLeftChild->leftChild());

                    code = mProfile->powerString() + "(" + generateCode(analyserModel, astRightChild) + ", " + generateOperatorCode(analyserModel, mProfile->divideString(), rootValueAst) + ")";
                }
            }
        } else {
            code = generateOneParameterFunctionCode(analyserModel, mProfile->squareRootString(), ast);
        }
    } break;
    case AnalyserEquationAst::Type::ABS:
        code = generateOneParameterFunctionCode(analyserModel, mProfile->absoluteValueString(), ast);

        break;
    case AnalyserEquationAst::Type::EXP:
        code = generateOneParameterFunctionCode(analyserModel, mProfile->exponentialString(), ast);

        break;
    case AnalyserEquationAst::Type::LN:
        code = generateOneParameterFunctionCode(analyserModel, mProfile->naturalLogarithmString(), ast);

        break;
    case AnalyserEquationAst::Type::LOG: {
        auto astRightChild = ast->rightChild();

        if (astRightChild != nullptr) {
            auto stringValue = generateCode(analyserModel, ast->leftChild());
            double doubleValue;

            if (convertToDouble(stringValue, doubleValue)
                && areEqual(doubleValue, 10.0)) {
                code = mProfile->commonLogarithmString() + "(" + generateCode(analyserModel, astRightChild) + ")";
            } else {
                code = mProfile->naturalLogarithmString() + "(" + generateCode(analyserModel, astRightChild) + ")/" + mProfile->naturalLogarithmString() + "(" + stringValue + ")";
            }
        } else {
            code = generateOneParameterFunctionCode(analyserModel, mProfile->commonLogarithmString(), ast);
        }
    } break;
    case AnalyserEquationAst::Type::CEILING:
        code = generateOneParameterFunctionCode(analyserModel, mProfile->ceilingString(), ast);

        break;
    case AnalyserEquationAst::Type::FLOOR:
        code = generateOneParameterFunctionCode(analyserModel, mProfile->floorString(), ast);

        break;
    case AnalyserEquationAst::Type::MIN:
        code = generateTwoParameterFunctionCode(analyserModel, mProfile->minString(), ast);

        break;
    case AnalyserEquationAst::Type::MAX:
        code = generateTwoParameterFunctionCode(analyserModel, mProfile->maxString(), ast);

        break;
    case AnalyserEquationAst::Type::REM:
        code = generateTwoParameterFunctionCode(analyserModel, mProfile->remString(), ast);

        break;
    case AnalyserEquationAst::Type::DIFF:
        if (analyserModel != nullptr) {
            code = generateCode(analyserModel, ast->rightChild());
        } else {
            code = "d" + generateCode(analyserModel, ast->rightChild()) + "/d" + generateCode(analyserModel, ast->leftChild());
        }

        break;
    case AnalyserEquationAst::Type::SIN:
        code = generateOneParameterFunctionCode(analyserModel, mProfile->sinString(), ast);

        break;
    case AnalyserEquationAst::Type::COS:
        code = generateOneParameterFunctionCode(analyserModel, mProfile->cosString(), ast);

        break;
    case AnalyserEquationAst::Type::TAN:
        code = generateOneParameterFunctionCode(analyserModel, mProfile->tanString(), ast);

        break;
    case AnalyserEquationAst::Type::SEC:
        code = generateOneParameterFunctionCode(analyserModel, mProfile->secString(), ast);

        break;
    case AnalyserEquationAst::Type::CSC:
        code = generateOneParameterFunctionCode(analyserModel, mProfile->cscString(), ast);

        break;
    case AnalyserEquationAst::Type::COT:
        code = generateOneParameterFunctionCode(analyserModel, mProfile->cotString(), ast);

        break;
    case AnalyserEquationAst::Type::SINH:
        code = generateOneParameterFunctionCode(analyserModel, mProfile->sinhString(), ast);

        break;
    case AnalyserEquationAst::Type::COSH:
        code = generateOneParameterFunctionCode(analyserModel, mProfile->coshString(), ast);

        break;
    case AnalyserEquationAst::Type::TANH:
        code = generateOneParameterFunctionCode(analyserModel, mProfile->tanhString(), ast);

        break;
    case AnalyserEquationAst::Type::SECH:
        code = generateOneParameterFunctionCode(analyserModel, mProfile->sechString(), ast);

        break;
    case AnalyserEquationAst::Type::CSCH:
        code = generateOneParameterFunctionCode(analyserModel, mProfile->cschString(), ast);

        break;
    case AnalyserEquationAst::Type::COTH:
        code = generateOneParameterFunctionCode(analyserModel, mProfile->cothString(), ast);

        break;
    case AnalyserEquationAst::Type::ASIN:
        code = generateOneParameterFunctionCode(analyserModel, mProfile->asinString(), ast);

        break;
    case AnalyserEquationAst::Type::ACOS:
        code = generateOneParameterFunctionCode(analyserModel, mProfile->acosString(), ast);

        break;
    case AnalyserEquationAst::Type::ATAN:
        code = generateOneParameterFunctionCode(analyserModel, mProfile->atanString(), ast);

        break;
    case AnalyserEquationAst::Type::ASEC:
        code = generateOneParameterFunctionCode(analyserModel, mProfile->asecString(), ast);

        break;
    case AnalyserEquationAst::Type::ACSC:
        code = generateOneParameterFunctionCode(analyserModel, mProfile->acscString(), ast);

        break;
    case AnalyserEquationAst::Type::ACOT:
        code = generateOneParameterFunctionCode(analyserModel, mProfile->acotString(), ast);

        break;
    case AnalyserEquationAst::Type::ASINH:
        code = generateOneParameterFunctionCode(analyserModel, mProfile->asinhString(), ast);

        break;
    case AnalyserEquationAst::Type::ACOSH:
        code = generateOneParameterFunctionCode(analyserModel, mProfile->acoshString(), ast);

        break;
    case AnalyserEquationAst::Type::ATANH:
        code = generateOneParameterFunctionCode(analyserModel, mProfile->atanhString(), ast);

        break;
    case AnalyserEquationAst::Type::ASECH:
        code = generateOneParameterFunctionCode(analyserModel, mProfile->asechString(), ast);

        break;
    case AnalyserEquationAst::Type::ACSCH:
        code = generateOneParameterFunctionCode(analyserModel, mProfile->acschString(), ast);

        break;
    case AnalyserEquationAst::Type::ACOTH:
        code = generateOneParameterFunctionCode(analyserModel, mProfile->acothString(), ast);

        break;
    case AnalyserEquationAst::Type::PIECEWISE: {
        auto astRightChild = ast->rightChild();

        if (astRightChild != nullptr) {
            if (astRightChild->type() == AnalyserEquationAst::Type::PIECE) {
                code = generateCode(analyserModel, ast->leftChild()) + generatePiecewiseElseCode(generateCode(analyserModel, astRightChild) + generatePiecewiseElseCode(mProfile->nanString()));
            } else {
                code = generateCode(analyserModel, ast->leftChild()) + generatePiecewiseElseCode(generateCode(analyserModel, astRightChild));
            }
        } else {
            code = generateCode(analyserModel, ast->leftChild()) + generatePiecewiseElseCode(mProfile->nanString());
        }
    } break;
    case AnalyserEquationAst::Type::PIECE:
        code = generatePiecewiseIfCode(generateCode(analyserModel, ast->rightChild()), generateCode(analyserModel, ast->leftChild()));

        break;
    case AnalyserEquationAst::Type::OTHERWISE:
        code = generateCode(analyserModel, ast->leftChild());

        break;
    case AnalyserEquationAst::Type::CI: {
        code = generateVariableNameCode(analyserModel, ast->variable(), ast->parent()->type() != AnalyserEquationAst::Type::DIFF);

        auto astParent = ast->parent();

        if ((analyserModel != nullptr)
            && (astParent->type() == AnalyserEquationAst::Type::EQUALITY)
            && (astParent->leftChild() == ast)
            && doIsTrackedVariable(analyserModel, analyserModel->analyserVariable(ast->variable()), false)) {
            // Note: we want this AST to be its parent's left child since a declaration is always of the form x = RHS,
            //       not LHS = x.

            code = replace(mProfile->variableDeclarationString(), "[CODE]", code);
        }
    }

    break;
    case AnalyserEquationAst::Type::CN:
        code = generateDoubleCode(ast->value());

        break;
    case AnalyserEquationAst::Type::DEGREE:
    case AnalyserEquationAst::Type::LOGBASE:
        code = generateCode(analyserModel, ast->leftChild());

        break;
    case AnalyserEquationAst::Type::BVAR:
        code = generateCode(analyserModel, ast->leftChild());

        break;
    case AnalyserEquationAst::Type::TRUE:
        code = mProfile->trueString();

        break;
    case AnalyserEquationAst::Type::FALSE:
        code = mProfile->falseString();

        break;
    case AnalyserEquationAst::Type::E:
        code = mProfile->eString();

        break;
    case AnalyserEquationAst::Type::PI:
        code = mProfile->piString();

        break;
    case AnalyserEquationAst::Type::INF:
        code = mProfile->infString();

        break;
    default: // AnalyserEquationAst::Type::NAN.
        code = mProfile->nanString();

        break;
    }

    return code;
}

bool Generator::GeneratorImpl::isToBeComputedAgain(const AnalyserEquationPtr &analyserEquation)
{
    // NLA and algebraic equations that are state/rate-based and external equations are to be computed again (in the
    // computeVariables() method) unless the variables they compute are not tracked.

    switch (analyserEquation->type()) {
    case AnalyserEquation::Type::NLA:
    case AnalyserEquation::Type::ALGEBRAIC:
        if (analyserEquation->isStateRateBased()) {
            for (const auto &analyserVariable : analyserVariables(analyserEquation)) {
                if (doIsTrackedVariable(analyserVariable->model(), analyserVariable)) {
                    return true;
                }
            }

            return false;
        }

        return false;
    case AnalyserEquation::Type::EXTERNAL:
        return isTrackedEquation(analyserEquation);
    default:
        return false;
    }
}

bool Generator::GeneratorImpl::isSomeConstant(const AnalyserEquationPtr &analyserEquation,
                                              bool includeComputedConstants) const
{
    return (analyserEquation->type() == AnalyserEquation::Type::CONSTANT)
           || (!includeComputedConstants && (analyserEquation->type() == AnalyserEquation::Type::COMPUTED_CONSTANT));
}

std::string Generator::GeneratorImpl::generateZeroInitialisationCode(const AnalyserModelPtr &analyserModel,
                                                                     const AnalyserVariablePtr &analyserVariable)
{
    return mProfile->indentString()
           + generateVariableNameCode(analyserModel, analyserVariable->variable(), false)
           + mProfile->equalityString()
           + "0.0"
           + mProfile->commandSeparatorString() + "\n";
}

std::string Generator::GeneratorImpl::generateInitialisationCode(const AnalyserModelPtr &analyserModel,
                                                                 const AnalyserVariablePtr &analyserVariable, bool force)
{
    if (!force && doIsTrackedVariable(analyserModel, analyserVariable, false)) {
        return {};
    }

    auto initialisingVariable = analyserVariable->initialisingVariable();
    auto scalingFactor = Generator::GeneratorImpl::scalingFactor(analyserModel, initialisingVariable);
    std::string scalingFactorCode;

    if (!areNearlyEqual(scalingFactor, 1.0)) {
        scalingFactorCode = generateDoubleCode(convertToString(scalingFactor)) + mProfile->timesString();
    }

    auto code = generateVariableNameCode(analyserModel, analyserVariable->variable())
                + mProfile->equalityString()
                + scalingFactorCode + generateDoubleOrConstantVariableNameCode(analyserModel, initialisingVariable)
                + mProfile->commandSeparatorString() + "\n";

    if (doIsTrackedVariable(analyserModel, analyserVariable, false)) {
        code = replace(mProfile->variableDeclarationString(), "[CODE]", code);
    }

    return mProfile->indentString()
           + code;
}

std::string Generator::GeneratorImpl::generateEquationCode(const AnalyserModelPtr &analyserModel,
                                                           const AnalyserEquationPtr &analyserEquation,
                                                           std::vector<AnalyserEquationPtr> &remainingAnalyserEquations,
                                                           std::vector<AnalyserEquationPtr> &analyserEquationsForDependencies,
                                                           std::vector<AnalyserVariablePtr> &generatedConstantDependencies,
                                                           bool includeComputedConstants,
                                                           GenerateEquationCodeTarget target)
{
    std::string res;

    if (std::find(remainingAnalyserEquations.begin(), remainingAnalyserEquations.end(), analyserEquation) != remainingAnalyserEquations.end()) {
        // Stop tracking the analyser equation and its NLA siblings, if any.
        // Note: we need to do this as soon as possible to avoid recursive
        //       calls, something that would happen if we were to do this at the
        //       end of this if statement.

        remainingAnalyserEquations.erase(std::find(remainingAnalyserEquations.begin(), remainingAnalyserEquations.end(), analyserEquation));

        for (const auto &nlaSibling : analyserEquation->nlaSiblings()) {
            remainingAnalyserEquations.erase(std::find(remainingAnalyserEquations.begin(), remainingAnalyserEquations.end(), nlaSibling));
        }

        // Generate any dependency that this analyser equation may have.

        for (const auto &constantDependency : analyserEquation->mPimpl->mConstantDependencies) {
            if ((analyserEquation->type() != AnalyserEquation::Type::NLA)
                && doIsTrackedVariable(analyserModel, constantDependency, false)
                && (std::find(generatedConstantDependencies.begin(), generatedConstantDependencies.end(), constantDependency) == generatedConstantDependencies.end())) {
                res += generateInitialisationCode(analyserModel, constantDependency, true);

                generatedConstantDependencies.push_back(constantDependency);
            }
        }

        if (!isSomeConstant(analyserEquation, includeComputedConstants)) {
            for (const auto &dependency : analyserEquation->dependencies()) {
                if (((analyserEquation->type() != AnalyserEquation::Type::NLA)
                     && (dependency->type() == AnalyserEquation::Type::COMPUTED_CONSTANT)
                     && isUntrackedEquation(dependency))
                    || (((target == GenerateEquationCodeTarget::NORMAL)
                         || ((target == GenerateEquationCodeTarget::COMPUTE_VARIABLES)
                             && ((dependency->type() != AnalyserEquation::Type::NLA)
                                 || isToBeComputedAgain(dependency)
                                 || (std::find(analyserEquationsForDependencies.begin(), analyserEquationsForDependencies.end(), dependency) != analyserEquationsForDependencies.end()))))
                        && (dependency->type() != AnalyserEquation::Type::ODE)
                        && (isTrackedEquation(dependency)
                            || (analyserEquation->type() != AnalyserEquation::Type::NLA))
                        && !isSomeConstant(dependency, includeComputedConstants)
                        && (analyserEquationsForDependencies.empty()
                            || isToBeComputedAgain(dependency)
                            || (std::find(analyserEquationsForDependencies.begin(), analyserEquationsForDependencies.end(), dependency) != analyserEquationsForDependencies.end())))) {
                    res += generateEquationCode(analyserModel, dependency, remainingAnalyserEquations, analyserEquationsForDependencies,
                                                generatedConstantDependencies, includeComputedConstants, target);
                }
            }
        }

        // Generate the analyser equation code itself, based on the analyser equation type.

        switch (analyserEquation->type()) {
        case AnalyserEquation::Type::EXTERNAL:
            for (const auto &analyserVariable : analyserVariables(analyserEquation)) {
                res += mProfile->indentString()
                       + generateVariableNameCode(analyserModel, analyserVariable->variable())
                       + mProfile->equalityString()
                       + replace(mProfile->externalVariableMethodCallString(modelHasOdes(analyserModel)),
                                 "[INDEX]", analyserVariableIndexString(analyserModel, analyserVariable))
                       + mProfile->commandSeparatorString() + "\n";
            }

            break;
        case AnalyserEquation::Type::NLA: {
            auto modelHasOdes = this->modelHasOdes(analyserModel);

            if (!mProfile->findRootCallString(modelHasOdes, analyserModel->hasExternalVariables()).empty()) {
                res += mProfile->indentString()
                       + replace(mProfile->findRootCallString(modelHasOdes, analyserModel->hasExternalVariables()),
                                 "[INDEX]", convertToString(analyserEquation->nlaSystemIndex()));
            }
        } break;
        default:
            res += mProfile->indentString() + generateCode(analyserModel, analyserEquation->ast()) + mProfile->commandSeparatorString() + "\n";

            break;
        }
    }

    return res;
}

std::string Generator::GeneratorImpl::generateEquationCode(const AnalyserModelPtr &analyserModel,
                                                           const AnalyserEquationPtr &analyserEquation,
                                                           std::vector<AnalyserEquationPtr> &remainingAnalyserEquations,
                                                           std::vector<AnalyserVariablePtr> &generatedConstantDependencies)
{
    std::vector<AnalyserEquationPtr> dummyAnalyserEquationsForComputeVariables;

    return generateEquationCode(analyserModel, analyserEquation, remainingAnalyserEquations, dummyAnalyserEquationsForComputeVariables,
                                generatedConstantDependencies, true);
}

void Generator::GeneratorImpl::addInterfaceComputeModelMethodsCode(const AnalyserModelPtr &analyserModel)
{
    auto interfaceInitialiseArraysMethodString = mProfile->interfaceInitialiseArraysMethodString(modelHasOdes(analyserModel));
    std::string code;

    if (!interfaceInitialiseArraysMethodString.empty()) {
        code += interfaceInitialiseArraysMethodString;
    }

    if (!mProfile->interfaceComputeComputedConstantsMethodString().empty()) {
        code += mProfile->interfaceComputeComputedConstantsMethodString();
    }

    auto interfaceComputeRatesMethodString = mProfile->interfaceComputeRatesMethodString(analyserModel->hasExternalVariables());

    if (modelHasOdes(analyserModel)
        && !interfaceComputeRatesMethodString.empty()) {
        code += interfaceComputeRatesMethodString;
    }

    auto interfaceComputeVariablesMethodString = mProfile->interfaceComputeVariablesMethodString(modelHasOdes(analyserModel),
                                                                                                 analyserModel->hasExternalVariables());

    if (!interfaceComputeVariablesMethodString.empty()) {
        code += interfaceComputeVariablesMethodString;
    }

    if (!code.empty()) {
        mCode += newLineIfNeeded()
                 + code;
    }
}

std::string Generator::GeneratorImpl::generateConstantInitialisationCode(const AnalyserModelPtr &analyserModel,
                                                                         const std::vector<AnalyserVariablePtr>::iterator constant,
                                                                         std::vector<AnalyserVariablePtr> &remainingConstants)
{
    auto initialisingVariable = (*constant)->initialisingVariable();
    auto initialValue = initialisingVariable->initialValue();

    if (!isCellMLReal(initialValue)) {
        auto initialisingComponent = owningComponent(initialisingVariable);
        auto crtConstant = std::find_if(remainingConstants.begin(), remainingConstants.end(),
                                        [=](const AnalyserVariablePtr &av) -> bool {
                                            return initialisingComponent->variable(initialValue) == av->variable();
                                        });

        if (crtConstant != remainingConstants.end()) {
            return generateConstantInitialisationCode(analyserModel, crtConstant, remainingConstants);
        }
    }

    auto code = generateInitialisationCode(analyserModel, *constant);

    remainingConstants.erase(constant);

    return code;
}

void Generator::GeneratorImpl::addImplementationInitialiseArraysMethodCode(const AnalyserModelPtr &analyserModel,
                                                                           std::vector<AnalyserEquationPtr> &remainingAnalyserEquations)
{
    auto implementationInitialiseArraysMethodString = mProfile->implementationInitialiseArraysMethodString(modelHasOdes(analyserModel));

    if (!implementationInitialiseArraysMethodString.empty()) {
        // Initialise our states (after, if needed, initialising the constant on which it depends).

        std::string methodBody;
        auto constants = analyserModel->constants();

        for (const auto &state : analyserModel->states()) {
            auto initialisingVariable = state->initialisingVariable();
            auto initialValue = initialisingVariable->initialValue();

            if (!isCellMLReal(initialValue)) {
                // The initial value references a constant.

                auto initialisingComponent = owningComponent(initialisingVariable);
                auto constant = std::find_if(constants.begin(), constants.end(),
                                             [=](const AnalyserVariablePtr &av) -> bool {
                                                 return initialisingComponent->variable(initialValue)->hasEquivalentVariable(av->variable());
                                             });

                methodBody += generateConstantInitialisationCode(analyserModel, constant, constants);
            }

            methodBody += generateInitialisationCode(analyserModel, state);
        }

        // Use an initial guess of zero for rates computed using an NLA system
        // (see the note below).

        for (const auto &state : analyserModel->states()) {
            if (state->analyserEquation(0)->type() == AnalyserEquation::Type::NLA) {
                methodBody += generateZeroInitialisationCode(analyserModel, state);
            }
        }

        // Initialise our (remaining) constants.

        while (!constants.empty()) {
            methodBody += generateConstantInitialisationCode(analyserModel, constants.begin(), constants);
        }

        // Initialise our computed constants that are initialised using an equation (e.g., x = 3 rather than x with an
        // initial value of 3).

        std::vector<AnalyserVariablePtr> generatedConstantDependencies;

        for (const auto &analyserEquation : analyserModel->analyserEquations()) {
            if (analyserEquation->type() == AnalyserEquation::Type::CONSTANT) {
                methodBody += generateEquationCode(analyserModel, analyserEquation, remainingAnalyserEquations, generatedConstantDependencies);
            }
        }

        // Initialise our algebraic variables that have an initial value. Also use an initial guess of zero for
        // algebraic variables computed using an NLA system.
        // Note: a variable which is the only unknown in an equation, but which is not on its own on either the LHS or
        //       RHS of that equation (e.g., x = y+z with x and y known and z unknown) is (currently) to be computed
        //       using an NLA system for which we need an initial guess. We use an initial guess of zero, which is fine
        //       since such an NLA system has only one solution.

        for (const auto &algebraicVariable : analyserModel->algebraicVariables()) {
            if (algebraicVariable->initialisingVariable() != nullptr) {
                methodBody += generateInitialisationCode(analyserModel, algebraicVariable);
            } else if (algebraicVariable->analyserEquation(0)->type() == AnalyserEquation::Type::NLA) {
                methodBody += generateZeroInitialisationCode(analyserModel, algebraicVariable);
            }
        }

        mCode += newLineIfNeeded()
                 + replace(implementationInitialiseArraysMethodString,
                           "[CODE]", generateMethodBodyCode(methodBody));
    }
}

void Generator::GeneratorImpl::addImplementationComputeComputedConstantsMethodCode(const AnalyserModelPtr &analyserModel,
                                                                                   std::vector<AnalyserEquationPtr> &remainingAnalyserEquations)
{
    if (!mProfile->implementationComputeComputedConstantsMethodString().empty()) {
        std::string methodBody;
        std::vector<AnalyserVariablePtr> generatedConstantDependencies;

        for (const auto &analyserEquation : analyserModel->analyserEquations()) {
            if ((analyserEquation->type() == AnalyserEquation::Type::COMPUTED_CONSTANT)
                && isTrackedEquation(analyserEquation)) {
                methodBody += generateEquationCode(analyserModel, analyserEquation, remainingAnalyserEquations, generatedConstantDependencies);
            }
        }

        mCode += newLineIfNeeded()
                 + replace(mProfile->implementationComputeComputedConstantsMethodString(),
                           "[CODE]", generateMethodBodyCode(methodBody));
    }
}

void Generator::GeneratorImpl::addImplementationComputeRatesMethodCode(const AnalyserModelPtr &analyserModel,
                                                                       std::vector<AnalyserEquationPtr> &remainingAnalyserEquations)
{
    auto implementationComputeRatesMethodString = mProfile->implementationComputeRatesMethodString(analyserModel->hasExternalVariables());

    if (modelHasOdes(analyserModel)
        && !implementationComputeRatesMethodString.empty()) {
        std::string methodBody;
        std::vector<AnalyserVariablePtr> generatedConstantDependencies;

        for (const auto &analyserEquation : analyserModel->analyserEquations()) {
            // A rate is computed either through an ODE equation or through an
            // NLA equation in case the rate is not on its own on either the LHS
            // or RHS of the equation.

            auto analyserVariables = libcellml::analyserVariables(analyserEquation);

            if ((analyserEquation->type() == AnalyserEquation::Type::ODE)
                || ((analyserEquation->type() == AnalyserEquation::Type::NLA)
                    && (analyserVariables.size() == 1)
                    && (analyserVariables[0]->type() == AnalyserVariable::Type::STATE))) {
                methodBody += generateEquationCode(analyserModel, analyserEquation, remainingAnalyserEquations, generatedConstantDependencies);
            }
        }

        mCode += newLineIfNeeded()
                 + replace(implementationComputeRatesMethodString,
                           "[CODE]", generateMethodBodyCode(methodBody));
    }
}

void Generator::GeneratorImpl::addImplementationComputeVariablesMethodCode(const AnalyserModelPtr &analyserModel,
                                                                           std::vector<AnalyserEquationPtr> &remainingAnalyserEquations)
{
    auto implementationComputeVariablesMethodString = mProfile->implementationComputeVariablesMethodString(modelHasOdes(analyserModel),
                                                                                                           analyserModel->hasExternalVariables());

    if (!implementationComputeVariablesMethodString.empty()) {
        std::string methodBody;
        auto analyserEquations = analyserModel->analyserEquations();
        std::vector<AnalyserEquationPtr> newRemainingAnalyserEquations {std::begin(analyserEquations), std::end(analyserEquations)};
        std::vector<AnalyserVariablePtr> generatedConstantDependencies;

        for (const auto &analyserEquation : analyserEquations) {
            if (((std::find(remainingAnalyserEquations.begin(), remainingAnalyserEquations.end(), analyserEquation) != remainingAnalyserEquations.end())
                 || isToBeComputedAgain(analyserEquation))
                && isTrackedEquation(analyserEquation)) {
                methodBody += generateEquationCode(analyserModel, analyserEquation, newRemainingAnalyserEquations, remainingAnalyserEquations,
                                                   generatedConstantDependencies, false,
                                                   GenerateEquationCodeTarget::COMPUTE_VARIABLES);
            }
        }

        mCode += newLineIfNeeded()
                 + replace(implementationComputeVariablesMethodString,
                           "[CODE]", generateMethodBodyCode(methodBody));
    }
}

Generator::GeneratorImpl *Generator::pFunc()
{
    return reinterpret_cast<Generator::GeneratorImpl *>(Logger::pFunc());
}

/*TODO
const Generator::GeneratorImpl *Generator::pFunc() const
{
    return reinterpret_cast<Generator::GeneratorImpl const *>(Logger::pFunc());
}
*/

Generator::Generator()
    : Logger(new GeneratorImpl())
{
}

Generator::~Generator()
{
    delete pFunc();
}

GeneratorPtr Generator::create() noexcept
{
    return std::shared_ptr<Generator> {new Generator {}};
}

GeneratorProfilePtr Generator::profile()
{
    return pFunc()->mProfile;
}

void Generator::setProfile(const GeneratorProfilePtr &profile)
{
    pFunc()->mProfile = profile;
}

bool Generator::isTrackedVariable(const AnalyserVariablePtr &analyserVariable)
{
    return pFunc()->isTrackedVariable(analyserVariable);
}

bool Generator::isUntrackedVariable(const AnalyserVariablePtr &analyserVariable)
{
    return pFunc()->isUntrackedVariable(analyserVariable);
}

void Generator::trackVariable(const AnalyserVariablePtr &analyserVariable)
{
    pFunc()->trackVariable(analyserVariable);
}

void Generator::untrackVariable(const AnalyserVariablePtr &analyserVariable)
{
    pFunc()->untrackVariable(analyserVariable);
}

void Generator::trackAllConstants(const AnalyserModelPtr &analyserModel)
{
    pFunc()->trackAllConstants(analyserModel);
}

void Generator::untrackAllConstants(const AnalyserModelPtr &analyserModel)
{
    pFunc()->untrackAllConstants(analyserModel);
}

void Generator::trackAllComputedConstants(const AnalyserModelPtr &analyserModel)
{
    pFunc()->trackAllComputedConstants(analyserModel);
}

void Generator::untrackAllComputedConstants(const AnalyserModelPtr &analyserModel)
{
    pFunc()->untrackAllComputedConstants(analyserModel);
}

void Generator::trackAllAlgebraic(const AnalyserModelPtr &analyserModel)
{
    pFunc()->trackAllAlgebraic(analyserModel);
}

void Generator::untrackAllAlgebraic(const AnalyserModelPtr &analyserModel)
{
    pFunc()->untrackAllAlgebraic(analyserModel);
}

void Generator::trackAllVariables(const AnalyserModelPtr &analyserModel)
{
    pFunc()->trackAllVariables(analyserModel);
}

void Generator::untrackAllVariables(const AnalyserModelPtr &analyserModel)
{
    pFunc()->untrackAllVariables(analyserModel);
}

size_t Generator::trackedConstantCount(const AnalyserModelPtr &analyserModel)
{
    return pFunc()->trackedConstantCount(analyserModel);
}

size_t Generator::untrackedConstantCount(const AnalyserModelPtr &analyserModel)
{
    return pFunc()->untrackedConstantCount(analyserModel);
}

size_t Generator::trackedComputedConstantCount(const AnalyserModelPtr &analyserModel)
{
    return pFunc()->trackedComputedConstantCount(analyserModel);
}

size_t Generator::untrackedComputedConstantCount(const AnalyserModelPtr &analyserModel)
{
    return pFunc()->untrackedComputedConstantCount(analyserModel);
}

size_t Generator::trackedAlgebraicCount(const AnalyserModelPtr &analyserModel)
{
    return pFunc()->trackedAlgebraicCount(analyserModel);
}

size_t Generator::untrackedAlgebraicCount(const AnalyserModelPtr &analyserModel)
{
    return pFunc()->untrackedAlgebraicCount(analyserModel);
}

size_t Generator::trackedVariableCount(const AnalyserModelPtr &analyserModel)
{
    return pFunc()->trackedVariableCount(analyserModel);
}

size_t Generator::untrackedVariableCount(const AnalyserModelPtr &analyserModel)
{
    return pFunc()->untrackedVariableCount(analyserModel);
}

std::string Generator::interfaceCode(const AnalyserModelPtr &analyserModel)
{
    if ((analyserModel == nullptr)
        || (pFunc()->mProfile == nullptr)
        || !analyserModel->isValid()
        || !pFunc()->mProfile->hasInterface()) {
        return {};
    }

    // Get ourselves ready.

    pFunc()->reset();

    // Add code for the origin comment.

    pFunc()->addOriginCommentCode();

    // Add code for the header.

    pFunc()->addInterfaceHeaderCode();

    // Add code for the interface of the version of the profile and libCellML.

    pFunc()->addVersionAndLibcellmlVersionCode(true);

    // Add code for the interface of the number of states and variables.

    pFunc()->addStateAndVariableCountCode(analyserModel, true);

    // Add code for the variable information related objects.

    pFunc()->addVariableInfoObjectCode(analyserModel);

    // Add code for the interface of the information about the variable of integration, states, constants, computed
    // constants, algebraic variables, and external variables.

    pFunc()->addInterfaceVariableInfoCode(analyserModel);

    // Add code for the interface to create and delete arrays.

    pFunc()->addInterfaceCreateDeleteArrayMethodsCode(analyserModel);

    // Add code for the external variable method type definition.

    pFunc()->addExternalVariableMethodTypeDefinitionCode(analyserModel);

    // Add code for the interface to compute the model.

    pFunc()->addInterfaceComputeModelMethodsCode(analyserModel);

    return pFunc()->mCode;
}

std::string Generator::implementationCode(const AnalyserModelPtr &analyserModel)
{
    if ((analyserModel == nullptr)
        || (pFunc()->mProfile == nullptr)
        || !analyserModel->isValid()) {
        return {};
    }

    // Get ourselves ready.

    pFunc()->reset();

    // Add code for the origin comment.

    pFunc()->addOriginCommentCode();

    // Add code for the header.

    pFunc()->addImplementationHeaderCode();

    // Add code for the implementation of the version of the profile and
    // libCellML.

    pFunc()->addVersionAndLibcellmlVersionCode();

    // Add code for the implementation of the number of states and variables.

    pFunc()->addStateAndVariableCountCode(analyserModel);

    // Add code for the variable information related objects.

    if (!pFunc()->mProfile->hasInterface()) {
        pFunc()->addVariableInfoObjectCode(analyserModel);
    }

    // Add code for the implementation of the information about the variable of integration, states, constants, computed
    // constants, algebraic variables, and external variables.

    pFunc()->addImplementationVariableInfoCode(analyserModel);

    // Add code for the arithmetic and trigonometric functions.

    pFunc()->addArithmeticFunctionsCode(analyserModel);
    pFunc()->addTrigonometricFunctionsCode(analyserModel);

    // Add code for the implementation to create and delete arrays.

    pFunc()->addImplementationCreateDeleteArrayMethodsCode(analyserModel);

    // Add code for the NLA solver.

    auto needNlaSolving = false;

    for (const auto &analyserEquation : analyserModel->analyserEquations()) {
        if (analyserEquation->type() == AnalyserEquation::Type::NLA) {
            needNlaSolving = true;

            break;
        }
    }

    if (needNlaSolving) {
        pFunc()->addRootFindingInfoObjectCode(analyserModel);
        pFunc()->addExternNlaSolveMethodCode();
        pFunc()->addNlaSystemsCode(analyserModel);
    }

    // Add code for the implementation to initialise our arrays.

    auto equations = analyserModel->analyserEquations();
    std::vector<AnalyserEquationPtr> remainingAnalyserEquations {std::begin(equations), std::end(equations)};

    pFunc()->addImplementationInitialiseArraysMethodCode(analyserModel, remainingAnalyserEquations);

    // Add code for the implementation to compute our computed constants.

    pFunc()->addImplementationComputeComputedConstantsMethodCode(analyserModel, remainingAnalyserEquations);

    // Add code for the implementation to compute our rates (and any variables
    // on which they depend).

    pFunc()->addImplementationComputeRatesMethodCode(analyserModel, remainingAnalyserEquations);

    // Add code for the implementation to compute our variables.
    // Note: this method computes the remaining variables, i.e. the ones not
    //       needed to compute our rates, but also the variables that depend on
    //       the value of some states/rates and all the external variables.
    //       This method is typically called after having integrated a model,
    //       thus ensuring that variables that rely on the value of some
    //       states/rates are up to date.

    pFunc()->addImplementationComputeVariablesMethodCode(analyserModel, remainingAnalyserEquations);

    return pFunc()->mCode;
}

std::string Generator::equationCode(const AnalyserEquationAstPtr &ast,
                                    const GeneratorProfilePtr &generatorProfile)
{
    GeneratorPtr generator = Generator::create();

    if (generatorProfile != nullptr) {
        generator->setProfile(generatorProfile);
    }

    return generator->pFunc()->generateCode(nullptr, ast);
}

std::string Generator::equationCode(const AnalyserEquationAstPtr &ast)
{
    return Generator::equationCode(ast, nullptr);
}

} // namespace libcellml

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

std::string Generator::GeneratorImpl::variableIndexString(const AnalyserModelPtr &model,
                                                          const AnalyserVariablePtr &variable)
{
    // Determine the actual index of the variable in the list of variables by accounting for the fact that some
    // variables may be untracked.

    auto variables = libcellml::variables(variable);

    if (variables.empty()) {
        return convertToString(variable->index());
    }

    size_t i = MAX_SIZE_T;
    size_t res = MAX_SIZE_T;

    for (;;) {
        auto var = variables[++i];

        if (doIsTrackedVariable(model, var)) {
            ++res;
        }

        if (variable == var) {
            break;
        }
    }

    return convertToString(res);
}

bool Generator::GeneratorImpl::doIsTrackedEquation(const AnalyserEquationPtr &equation, bool tracked)
{
    AnalyserVariablePtr variable;

    switch (equation->type()) {
    case AnalyserEquation::Type::COMPUTED_CONSTANT:
        variable = equation->computedConstants().front();

        return doIsTrackedVariable(variable->model(), variable) == tracked;
    case AnalyserEquation::Type::ALGEBRAIC:
        variable = equation->algebraic().front();

        return doIsTrackedVariable(variable->model(), variable) == tracked;
    default:
        return true;
    }
}

bool Generator::GeneratorImpl::isTrackedEquation(const AnalyserEquationPtr &equation)
{
    return doIsTrackedEquation(equation, true);
}

bool Generator::GeneratorImpl::isUntrackedEquation(const AnalyserEquationPtr &equation)
{
    return doIsTrackedEquation(equation, false);
}

bool Generator::GeneratorImpl::doIsTrackedVariable(const AnalyserModelPtr &model, const AnalyserVariablePtr &variable,
                                                   bool tracked)
{
    // By default a variable is always tracked.

    if (mTrackedVariables[model].find(variable) == mTrackedVariables[model].end()) {
        mTrackedVariables[model][variable] = true;
    }

    return mTrackedVariables[model][variable] == tracked;
}

bool Generator::GeneratorImpl::doIsTrackedVariable(const AnalyserVariablePtr &variable, bool tracked)
{
    if (variable == nullptr) {
        return false;
    }

    return doIsTrackedVariable(variable->model(), variable, tracked);
}

bool Generator::GeneratorImpl::isTrackedVariable(const AnalyserVariablePtr &variable)
{
    return doIsTrackedVariable(variable, true);
}

bool Generator::GeneratorImpl::isUntrackedVariable(const AnalyserVariablePtr &variable)
{
    return doIsTrackedVariable(variable, false);
}

void Generator::GeneratorImpl::addNeededToComputeExternalVariableIssue(const AnalyserVariablePtr &variable, bool tracked)
{
    auto issue = Issue::IssueImpl::create();

    issue->mPimpl->setDescription("Variable '" + variable->variable()->name()
                                  + "' in component '" + owningComponent(variable->variable())->name()
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

bool Generator::GeneratorImpl::trackableVariable(const AnalyserVariablePtr &variable, bool tracked, bool canAddIssue)
{
    // A trackable variable is a variable that is not a variable of integration, a state, or an external variable, which
    // is already the case when we reach this point. However, a trackable variable is also a variable that is not
    // computed using an NLA system.

    for (const auto &equation : variable->equations()) {
        if (equation->type() == AnalyserEquation::Type::NLA) {
            if (canAddIssue) {
                auto issue = Issue::IssueImpl::create();

                issue->mPimpl->setDescription("Variable '" + variable->variable()->name()
                                              + "' in component '" + owningComponent(variable->variable())->name()
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

    // A trackable variable is also not a variable that is needed to compute an external variable.

    for (const auto &external : variable->model()->externals()) {
        auto externalEquationPimpl = external->equations().front()->mPimpl;

        // Check whether the variable is a constant dependency.

        for (const auto &constantDependency : externalEquationPimpl->mConstantDependencies) {
            if (variable == constantDependency) {
                if (canAddIssue) {
                    addNeededToComputeExternalVariableIssue(variable, tracked);
                }

                return false;
            }
        }

        // Check whether the variable is a computed constant dependency or an algebraic dependency.

        for (const auto &dependency : externalEquationPimpl->mDependencies) {
            auto dependencyPimpl = dependency.lock()->mPimpl;

            for (const auto &computedConstant : dependencyPimpl->mComputedConstants) {
                if (variable == computedConstant) {
                    if (canAddIssue) {
                        addNeededToComputeExternalVariableIssue(variable, tracked);
                    }

                    return false;
                }
            }

            for (const auto &algebraic : dependencyPimpl->mAlgebraic) {
                if (variable == algebraic) {
                    if (canAddIssue) {
                        addNeededToComputeExternalVariableIssue(variable, tracked);
                    }

                    return false;
                }
            }
        }
    }

    return true;
}

bool Generator::GeneratorImpl::specialVariable(const AnalyserVariablePtr &variable,
                                               const AnalyserVariablePtr &specialVariable, bool tracked,
                                               Issue::ReferenceRule trackedReferenceRule,
                                               Issue::ReferenceRule untrackedReferenceRule)
{
    if (variable == specialVariable) {
        auto issue = Issue::IssueImpl::create();
        auto variableType = (specialVariable->type() == AnalyserVariable::Type::VARIABLE_OF_INTEGRATION) ?
                                "the variable of integration" :
                                ((specialVariable->type() == AnalyserVariable::Type::STATE) ?
                                     "a state variable" :
                                     "an external variable");

        issue->mPimpl->setDescription("Variable '" + variable->variable()->name()
                                      + "' in component '" + owningComponent(variable->variable())->name()
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

void Generator::GeneratorImpl::doTrackVariable(const AnalyserVariablePtr &variable, bool tracked,
                                               bool needRemoveAllIssues)
{
    // Make sure that we have a variable.

    if (needRemoveAllIssues) {
        removeAllIssues();
    }

    if (variable == nullptr) {
        auto issue = Issue::IssueImpl::create();

        issue->mPimpl->setDescription("The variable is null.");
        issue->mPimpl->setReferenceRule(Issue::ReferenceRule::GENERATOR_NULL_VARIABLE);

        addIssue(issue);

        return;
    }

    // Check whether we want to track/untrack a constant, a computed constant, or an algebraic variable though we can
    // only track/untrack a variable if it is actually trackable.

    auto model = variable->model();

    for (const auto &modelVariable : variables(variable)) {
        if (variable == modelVariable) {
            if (trackableVariable(variable, tracked)) {
                mTrackedVariables[modelVariable->model()][modelVariable] = tracked;
            }

            return;
        }
    }

    // Check whether we tried to track/untrack a state variable.

    for (const auto &state : model->states()) {
        if (specialVariable(variable, state, tracked,
                            Issue::ReferenceRule::GENERATOR_STATE_VARIABLE_ALWAYS_TRACKED,
                            Issue::ReferenceRule::GENERATOR_STATE_VARIABLE_NOT_UNTRACKABLE)) {
            return;
        }
    }

    // Check whether we tried to track/untrack an external variable.

    for (const auto &external : model->externals()) {
        if (specialVariable(variable, external, tracked,
                            Issue::ReferenceRule::GENERATOR_EXTERNAL_VARIABLE_ALWAYS_TRACKED,
                            Issue::ReferenceRule::GENERATOR_EXTERNAL_VARIABLE_NOT_UNTRACKABLE)) {
            return;
        }
    }

    // In the end, we tried to track/untrack the variable of integration.

    specialVariable(variable, model->voi(), tracked,
                    Issue::ReferenceRule::GENERATOR_VOI_VARIABLE_ALWAYS_TRACKED,
                    Issue::ReferenceRule::GENERATOR_VOI_VARIABLE_NOT_UNTRACKABLE);
}

void Generator::GeneratorImpl::trackVariable(const AnalyserVariablePtr &variable)
{
    return doTrackVariable(variable, true);
}

void Generator::GeneratorImpl::untrackVariable(const AnalyserVariablePtr &variable)
{
    return doTrackVariable(variable, false);
}

void Generator::GeneratorImpl::doTrackVariables(const std::vector<AnalyserVariablePtr> &variables, bool tracked)
{
    removeAllIssues();

    for (const auto &variable : variables) {
        doTrackVariable(variable, tracked, false);
    }
}

bool Generator::GeneratorImpl::validModel(const AnalyserModelPtr &model)
{
    removeAllIssues();

    if (model == nullptr) {
        auto issue = Issue::IssueImpl::create();

        issue->mPimpl->setDescription("The model is null.");
        issue->mPimpl->setReferenceRule(Issue::ReferenceRule::GENERATOR_NULL_MODEL);

        addIssue(issue);

        return false;
    }

    return true;
}

void Generator::GeneratorImpl::trackAllConstants(const AnalyserModelPtr &model)
{
    if (validModel(model)) {
        doTrackVariables(model->constants(), true);
    }
}

void Generator::GeneratorImpl::untrackAllConstants(const AnalyserModelPtr &model)
{
    if (validModel(model)) {
        doTrackVariables(model->constants(), false);
    }
}

void Generator::GeneratorImpl::trackAllComputedConstants(const AnalyserModelPtr &model)
{
    if (validModel(model)) {
        doTrackVariables(model->computedConstants(), true);
    }
}

void Generator::GeneratorImpl::untrackAllComputedConstants(const AnalyserModelPtr &model)
{
    if (validModel(model)) {
        doTrackVariables(model->computedConstants(), false);
    }
}

void Generator::GeneratorImpl::trackAllAlgebraic(const AnalyserModelPtr &model)
{
    if (validModel(model)) {
        doTrackVariables(model->algebraic(), true);
    }
}

void Generator::GeneratorImpl::untrackAllAlgebraic(const AnalyserModelPtr &model)
{
    if (validModel(model)) {
        doTrackVariables(model->algebraic(), false);
    }
}

std::vector<AnalyserVariablePtr> Generator::GeneratorImpl::trackableVariables(const AnalyserModelPtr &model) const
{
    auto res = model->constants();
    auto computedConstants = model->computedConstants();
    auto algebraic = model->algebraic();

    res.insert(res.end(), computedConstants.begin(), computedConstants.end());
    res.insert(res.end(), algebraic.begin(), algebraic.end());

    return res;
}

void Generator::GeneratorImpl::trackAllVariables(const AnalyserModelPtr &model)
{
    if (validModel(model)) {
        doTrackVariables(trackableVariables(model), true);
    }
}

void Generator::GeneratorImpl::untrackAllVariables(const AnalyserModelPtr &model)
{
    if (validModel(model)) {
        doTrackVariables(trackableVariables(model), false);
    }
}

size_t Generator::GeneratorImpl::doTrackedVariableCount(const AnalyserModelPtr &model,
                                                        const std::vector<AnalyserVariablePtr> &variables, bool tracked)
{
    size_t res = 0;

    for (const auto &variable : variables) {
        if (trackableVariable(variable, tracked, false)) {
            if (doIsTrackedVariable(model, variable, tracked)) {
                ++res;
            }
        } else {
            // The variable is not trackable per se, which means that it is always tracked.

            ++res;
        }
    }

    return res;
}

size_t Generator::GeneratorImpl::trackedConstantCount(const AnalyserModelPtr &model)
{
    if (model == nullptr) {
        return 0;
    }

    return doTrackedVariableCount(model, model->constants(), true);
}

size_t Generator::GeneratorImpl::untrackedConstantCount(const AnalyserModelPtr &model)
{
    if (model == nullptr) {
        return 0;
    }

    return doTrackedVariableCount(model, model->constants(), false);
}

size_t Generator::GeneratorImpl::trackedComputedConstantCount(const AnalyserModelPtr &model)
{
    if (model == nullptr) {
        return 0;
    }

    return doTrackedVariableCount(model, model->computedConstants(), true);
}

size_t Generator::GeneratorImpl::untrackedComputedConstantCount(const AnalyserModelPtr &model)
{
    if (model == nullptr) {
        return 0;
    }

    return doTrackedVariableCount(model, model->computedConstants(), false);
}

size_t Generator::GeneratorImpl::trackedAlgebraicCount(const AnalyserModelPtr &model)
{
    if (model == nullptr) {
        return 0;
    }

    return doTrackedVariableCount(model, model->algebraic(), true);
}

size_t Generator::GeneratorImpl::untrackedAlgebraicCount(const AnalyserModelPtr &model)
{
    if (model == nullptr) {
        return 0;
    }

    return doTrackedVariableCount(model, model->algebraic(), false);
}

size_t Generator::GeneratorImpl::trackedVariableCount(const AnalyserModelPtr &model)
{
    if (model == nullptr) {
        return 0;
    }

    return doTrackedVariableCount(model, trackableVariables(model), true);
}

size_t Generator::GeneratorImpl::untrackedVariableCount(const AnalyserModelPtr &model)
{
    if (model == nullptr) {
        return 0;
    }

    return doTrackedVariableCount(model, trackableVariables(model), false);
}

bool Generator::GeneratorImpl::modelHasOdes(const AnalyserModelPtr &model) const
{
    switch (model->type()) {
    case AnalyserModel::Type::ODE:
    case AnalyserModel::Type::DAE:
        return true;
    default:
        return false;
    }
}

double Generator::GeneratorImpl::scalingFactor(const AnalyserModelPtr &model, const VariablePtr &variable) const
{
    // Return the scaling factor for the given variable, accounting for the fact that a constant may be initialised by
    // another variable which initial value may be defined in a different component.

    auto analyserVariable = model->variable(variable);

    if ((analyserVariable->type() == AnalyserVariable::Type::CONSTANT)
        && !isCellMLReal(variable->initialValue())) {
        auto initialValueVariable = owningComponent(variable)->variable(variable->initialValue());
        auto initialValueAnalyserVariable = model->variable(initialValueVariable);

        if (owningComponent(variable) != owningComponent(initialValueAnalyserVariable->variable())) {
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
                                                       const AnalyserVariablePtr &variable) const
{
    auto variableVariable = variable->variable();
    auto variableComponentSize = owningComponent(variableVariable)->name().length() + 1;
    auto variableNameSize = variableVariable->name().length() + 1;
    auto variableUnitsSize = variableVariable->units()->name().length() + 1;
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

void Generator::GeneratorImpl::addStateAndVariableCountCode(const AnalyserModelPtr &model, bool interface)
{
    std::string code;

    if (modelHasOdes(model)
        && ((interface && !mProfile->interfaceStateCountString().empty())
            || (!interface && !mProfile->implementationStateCountString().empty()))) {
        code += interface ?
                    mProfile->interfaceStateCountString() :
                    replace(mProfile->implementationStateCountString(),
                            "[STATE_COUNT]", std::to_string(model->stateCount()));
    }

    if ((interface && !mProfile->interfaceConstantCountString().empty())
        || (!interface && !mProfile->implementationConstantCountString().empty())) {
        code += interface ?
                    mProfile->interfaceConstantCountString() :
                    replace(mProfile->implementationConstantCountString(),
                            "[CONSTANT_COUNT]", std::to_string(doTrackedVariableCount(model, model->constants(), true)));
    }

    if ((interface && !mProfile->interfaceComputedConstantCountString().empty())
        || (!interface && !mProfile->implementationComputedConstantCountString().empty())) {
        code += interface ?
                    mProfile->interfaceComputedConstantCountString() :
                    replace(mProfile->implementationComputedConstantCountString(),
                            "[COMPUTED_CONSTANT_COUNT]", std::to_string(doTrackedVariableCount(model, model->computedConstants(), true)));
    }

    if ((interface && !mProfile->interfaceAlgebraicCountString().empty())
        || (!interface && !mProfile->implementationAlgebraicCountString().empty())) {
        code += interface ?
                    mProfile->interfaceAlgebraicCountString() :
                    replace(mProfile->implementationAlgebraicCountString(),
                            "[ALGEBRAIC_COUNT]", std::to_string(doTrackedVariableCount(model, model->algebraic(), true)));
    }

    if ((model->externalCount() != 0)
        && ((interface && !mProfile->interfaceExternalCountString().empty())
            || (!interface && !mProfile->implementationExternalCountString().empty()))) {
        code += interface ?
                    mProfile->interfaceExternalCountString() :
                    replace(mProfile->implementationExternalCountString(),
                            "[EXTERNAL_COUNT]", std::to_string(model->externalCount()));
    }

    if (!code.empty()) {
        mCode += newLineIfNeeded()
                 + code;
    }
}

std::string Generator::GeneratorImpl::generateVariableInfoObjectCode(const AnalyserModelPtr &model,
                                                                     const std::string &objectString)
{
    size_t componentSize = 0;
    size_t nameSize = 0;
    size_t unitsSize = 0;

    for (const auto &variable : variables(model)) {
        if (doIsTrackedVariable(model, variable)) {
            updateVariableInfoSizes(componentSize, nameSize, unitsSize, variable);
        }
    }

    return replace(replace(replace(objectString,
                                   "[COMPONENT_SIZE]", std::to_string(componentSize)),
                           "[NAME_SIZE]", std::to_string(nameSize)),
                   "[UNITS_SIZE]", std::to_string(unitsSize));
}

void Generator::GeneratorImpl::addVariableInfoObjectCode(const AnalyserModelPtr &model)
{
    if (!mProfile->variableInfoObjectString().empty()) {
        mCode += newLineIfNeeded()
                 + generateVariableInfoObjectCode(model, mProfile->variableInfoObjectString());
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

void Generator::GeneratorImpl::addInterfaceVariableInfoCode(const AnalyserModelPtr &model)
{
    std::string code;

    if (modelHasOdes(model)
        && !mProfile->interfaceVoiInfoString().empty()) {
        code += mProfile->interfaceVoiInfoString();
    }

    if (modelHasOdes(model)
        && !mProfile->interfaceStateInfoString().empty()) {
        code += mProfile->interfaceStateInfoString();
    }

    if (!mProfile->interfaceConstantInfoString().empty()) {
        code += mProfile->interfaceConstantInfoString();
    }

    if (!mProfile->interfaceComputedConstantInfoString().empty()) {
        code += mProfile->interfaceComputedConstantInfoString();
    }

    if (!mProfile->interfaceAlgebraicInfoString().empty()) {
        code += mProfile->interfaceAlgebraicInfoString();
    }

    if (model->hasExternalVariables()
        && !mProfile->interfaceExternalInfoString().empty()) {
        code += mProfile->interfaceExternalInfoString();
    }

    if (!code.empty()) {
        mCode += newLineIfNeeded()
                 + code;
    }
}

void Generator::GeneratorImpl::doAddImplementationVariableInfoCode(const std::string &variableInfoString,
                                                                   const std::vector<AnalyserVariablePtr> &variables,
                                                                   bool voiVariable)
{
    if (!variableInfoString.empty()
        && !mProfile->variableInfoEntryString().empty()
        && !mProfile->arrayElementSeparatorString().empty()) {
        auto model = variables.empty() ? nullptr : variables.front()->model();
        std::string infoElementsCode;

        for (const auto &variable : variables) {
            if (doIsTrackedVariable(model, variable)) {
                if (!infoElementsCode.empty()) {
                    infoElementsCode += mProfile->arrayElementSeparatorString() + "\n";
                }

                auto variableVariable = variable->variable();

                infoElementsCode += (voiVariable ? "" : mProfile->indentString())
                                    + generateVariableInfoEntryCode(variableVariable->name(),
                                                                    variableVariable->units()->name(),
                                                                    owningComponent(variableVariable)->name());
            }
        }

        if (!voiVariable && !infoElementsCode.empty()) {
            infoElementsCode += "\n";
        }

        mCode += newLineIfNeeded()
                 + replace(variableInfoString, "[CODE]", infoElementsCode);
    }
}

void Generator::GeneratorImpl::addImplementationVariableInfoCode(const AnalyserModelPtr &model)
{
    if (modelHasOdes(model)) {
        doAddImplementationVariableInfoCode(mProfile->implementationVoiInfoString(), {model->voi()}, true);
    }

    if (modelHasOdes(model)) {
        doAddImplementationVariableInfoCode(mProfile->implementationStateInfoString(), model->states(), false);
    }

    doAddImplementationVariableInfoCode(mProfile->implementationConstantInfoString(), model->constants(), false);
    doAddImplementationVariableInfoCode(mProfile->implementationComputedConstantInfoString(), model->computedConstants(), false);
    doAddImplementationVariableInfoCode(mProfile->implementationAlgebraicInfoString(), model->algebraic(), false);

    if (model->hasExternalVariables()) {
        doAddImplementationVariableInfoCode(mProfile->implementationExternalInfoString(), model->externals(), false);
    }
}

void Generator::GeneratorImpl::addArithmeticFunctionsCode(const AnalyserModelPtr &model)
{
    if (model->needEqFunction() && !mProfile->hasEqOperator()
        && !mProfile->eqFunctionString().empty()) {
        mCode += newLineIfNeeded()
                 + mProfile->eqFunctionString();
    }

    if (model->needNeqFunction() && !mProfile->hasNeqOperator()
        && !mProfile->neqFunctionString().empty()) {
        mCode += newLineIfNeeded()
                 + mProfile->neqFunctionString();
    }

    if (model->needLtFunction() && !mProfile->hasLtOperator()
        && !mProfile->ltFunctionString().empty()) {
        mCode += newLineIfNeeded()
                 + mProfile->ltFunctionString();
    }

    if (model->needLeqFunction() && !mProfile->hasLeqOperator()
        && !mProfile->leqFunctionString().empty()) {
        mCode += newLineIfNeeded()
                 + mProfile->leqFunctionString();
    }

    if (model->needGtFunction() && !mProfile->hasGtOperator()
        && !mProfile->gtFunctionString().empty()) {
        mCode += newLineIfNeeded()
                 + mProfile->gtFunctionString();
    }

    if (model->needGeqFunction() && !mProfile->hasGeqOperator()
        && !mProfile->geqFunctionString().empty()) {
        mCode += newLineIfNeeded()
                 + mProfile->geqFunctionString();
    }

    if (model->needAndFunction() && !mProfile->hasAndOperator()
        && !mProfile->andFunctionString().empty()) {
        mCode += newLineIfNeeded()
                 + mProfile->andFunctionString();
    }

    if (model->needOrFunction() && !mProfile->hasOrOperator()
        && !mProfile->orFunctionString().empty()) {
        mCode += newLineIfNeeded()
                 + mProfile->orFunctionString();
    }

    if (model->needXorFunction() && !mProfile->hasXorOperator()
        && !mProfile->xorFunctionString().empty()) {
        mCode += newLineIfNeeded()
                 + mProfile->xorFunctionString();
    }

    if (model->needNotFunction() && !mProfile->hasNotOperator()
        && !mProfile->notFunctionString().empty()) {
        mCode += newLineIfNeeded()
                 + mProfile->notFunctionString();
    }

    if (model->needMinFunction()
        && !mProfile->minFunctionString().empty()) {
        mCode += newLineIfNeeded()
                 + mProfile->minFunctionString();
    }

    if (model->needMaxFunction()
        && !mProfile->maxFunctionString().empty()) {
        mCode += newLineIfNeeded()
                 + mProfile->maxFunctionString();
    }
}

void Generator::GeneratorImpl::addTrigonometricFunctionsCode(const AnalyserModelPtr &model)
{
    if (model->needSecFunction()
        && !mProfile->secFunctionString().empty()) {
        mCode += newLineIfNeeded()
                 + mProfile->secFunctionString();
    }

    if (model->needCscFunction()
        && !mProfile->cscFunctionString().empty()) {
        mCode += newLineIfNeeded()
                 + mProfile->cscFunctionString();
    }

    if (model->needCotFunction()
        && !mProfile->cotFunctionString().empty()) {
        mCode += newLineIfNeeded()
                 + mProfile->cotFunctionString();
    }

    if (model->needSechFunction()
        && !mProfile->sechFunctionString().empty()) {
        mCode += newLineIfNeeded()
                 + mProfile->sechFunctionString();
    }

    if (model->needCschFunction()
        && !mProfile->cschFunctionString().empty()) {
        mCode += newLineIfNeeded()
                 + mProfile->cschFunctionString();
    }

    if (model->needCothFunction()
        && !mProfile->cothFunctionString().empty()) {
        mCode += newLineIfNeeded()
                 + mProfile->cothFunctionString();
    }

    if (model->needAsecFunction()
        && !mProfile->asecFunctionString().empty()) {
        mCode += newLineIfNeeded()
                 + mProfile->asecFunctionString();
    }

    if (model->needAcscFunction()
        && !mProfile->acscFunctionString().empty()) {
        mCode += newLineIfNeeded()
                 + mProfile->acscFunctionString();
    }

    if (model->needAcotFunction()
        && !mProfile->acotFunctionString().empty()) {
        mCode += newLineIfNeeded()
                 + mProfile->acotFunctionString();
    }

    if (model->needAsechFunction()
        && !mProfile->asechFunctionString().empty()) {
        mCode += newLineIfNeeded()
                 + mProfile->asechFunctionString();
    }

    if (model->needAcschFunction()
        && !mProfile->acschFunctionString().empty()) {
        mCode += newLineIfNeeded()
                 + mProfile->acschFunctionString();
    }

    if (model->needAcothFunction()
        && !mProfile->acothFunctionString().empty()) {
        mCode += newLineIfNeeded()
                 + mProfile->acothFunctionString();
    }
}

void Generator::GeneratorImpl::addInterfaceCreateDeleteArrayMethodsCode(const AnalyserModelPtr &model)
{
    std::string code;

    if (modelHasOdes(model)
        && !mProfile->interfaceCreateStatesArrayMethodString().empty()) {
        code += mProfile->interfaceCreateStatesArrayMethodString();
    }

    if (!mProfile->interfaceCreateConstantsArrayMethodString().empty()) {
        code += mProfile->interfaceCreateConstantsArrayMethodString();
    }

    if (!mProfile->interfaceCreateComputedConstantsArrayMethodString().empty()) {
        code += mProfile->interfaceCreateComputedConstantsArrayMethodString();
    }

    if (!mProfile->interfaceCreateAlgebraicArrayMethodString().empty()) {
        code += mProfile->interfaceCreateAlgebraicArrayMethodString();
    }

    if (model->hasExternalVariables()
        && !mProfile->interfaceCreateExternalsArrayMethodString().empty()) {
        code += mProfile->interfaceCreateExternalsArrayMethodString();
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

void Generator::GeneratorImpl::addImplementationCreateDeleteArrayMethodsCode(const AnalyserModelPtr &model)
{
    if (modelHasOdes(model)
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

    if (!mProfile->implementationCreateAlgebraicArrayMethodString().empty()) {
        mCode += newLineIfNeeded()
                 + mProfile->implementationCreateAlgebraicArrayMethodString();
    }

    if (model->hasExternalVariables()
        && !mProfile->implementationCreateExternalsArrayMethodString().empty()) {
        mCode += newLineIfNeeded()
                 + mProfile->implementationCreateExternalsArrayMethodString();
    }

    if (!mProfile->implementationDeleteArrayMethodString().empty()) {
        mCode += newLineIfNeeded()
                 + mProfile->implementationDeleteArrayMethodString();
    }
}

void Generator::GeneratorImpl::addExternalVariableMethodTypeDefinitionCode(const AnalyserModelPtr &model)
{
    if (model->hasExternalVariables()) {
        auto externalVariableMethodTypeDefinitionString = mProfile->externalVariableMethodTypeDefinitionString(modelHasOdes(model));

        if (!externalVariableMethodTypeDefinitionString.empty()) {
            mCode += newLineIfNeeded()
                     + externalVariableMethodTypeDefinitionString;
        }
    }
}

void Generator::GeneratorImpl::addRootFindingInfoObjectCode(const AnalyserModelPtr &model)
{
    if (!mProfile->rootFindingInfoObjectString(modelHasOdes(model), model->hasExternalVariables()).empty()) {
        mCode += newLineIfNeeded()
                 + mProfile->rootFindingInfoObjectString(modelHasOdes(model), model->hasExternalVariables());
    }
}

void Generator::GeneratorImpl::addExternNlaSolveMethodCode()
{
    if (!mProfile->externNlaSolveMethodString().empty()) {
        mCode += newLineIfNeeded()
                 + mProfile->externNlaSolveMethodString();
    }
}

void Generator::GeneratorImpl::addNlaSystemsCode(const AnalyserModelPtr &model)
{
    if (!mProfile->objectiveFunctionMethodString(modelHasOdes(model), model->hasExternalVariables()).empty()
        && !mProfile->findRootMethodString(modelHasOdes(model), model->hasExternalVariables()).empty()
        && !mProfile->nlaSolveCallString(modelHasOdes(model), model->hasExternalVariables()).empty()) {
        // Note: only states and algebraic variables can be computed through an NLA system. Constants, computed
        //       constants, and external variables cannot, by definition, be computed through an NLA system.

        std::vector<AnalyserEquationPtr> handledNlaEquations;

        for (const auto &equation : model->equations()) {
            if ((equation->type() == AnalyserEquation::Type::NLA)
                && (std::find(handledNlaEquations.begin(), handledNlaEquations.end(), equation) == handledNlaEquations.end())) {
                // 1) Generate some code for the objectiveFunction[INDEX]() method.
                //     a) Retrieve the values from our NLA solver's u array.

                std::string methodBody;
                auto i = MAX_SIZE_T;
                auto variables = libcellml::variables(equation);

                for (const auto &variable : variables) {
                    auto arrayString = (variable->type() == AnalyserVariable::Type::STATE) ?
                                           mProfile->ratesArrayString() :
                                           mProfile->algebraicArrayString();

                    methodBody += mProfile->indentString()
                                  + arrayString + mProfile->openArrayString() + variableIndexString(model, variable) + mProfile->closeArrayString()
                                  + mProfile->equalityString()
                                  + mProfile->uArrayString() + mProfile->openArrayString() + convertToString(++i) + mProfile->closeArrayString()
                                  + mProfile->commandSeparatorString() + "\n";
                }

                //     b) Initialise any untracked constant, computed constant, or algebraic variable that is needed by
                //        our NLA system.

                methodBody += "\n";

                auto methodBodySize = methodBody.size();

                for (const auto &constantDependency : equation->mPimpl->mConstantDependencies) {
                    if (doIsTrackedVariable(model, constantDependency, false)) {
                        methodBody += generateInitialisationCode(model, constantDependency, true);
                    }
                }

                std::vector<AnalyserEquationPtr> dummyRemainingEquations = model->equations();
                std::vector<AnalyserEquationPtr> dummyEquationsForDependencies;
                std::vector<AnalyserVariablePtr> dummyGeneratedConstantDependencies;

                for (const auto &dependency : equation->dependencies()) {
                    if (((dependency->type() == AnalyserEquation::Type::COMPUTED_CONSTANT)
                         || (dependency->type() == AnalyserEquation::Type::ALGEBRAIC))
                        && isUntrackedEquation(dependency)) {
                        methodBody += generateEquationCode(model, dependency, dummyRemainingEquations,
                                                           dummyEquationsForDependencies,
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
                              + generateCode(model, equation->ast())
                              + mProfile->commandSeparatorString() + "\n";

                handledNlaEquations.push_back(equation);

                for (const auto &nlaSibling : equation->nlaSiblings()) {
                    methodBody += mProfile->indentString()
                                  + mProfile->fArrayString() + mProfile->openArrayString() + convertToString(++i) + mProfile->closeArrayString()
                                  + mProfile->equalityString()
                                  + generateCode(model, nlaSibling->ast())
                                  + mProfile->commandSeparatorString() + "\n";

                    handledNlaEquations.push_back(nlaSibling);
                }

                mCode += newLineIfNeeded()
                         + replace(replace(mProfile->objectiveFunctionMethodString(modelHasOdes(model), model->hasExternalVariables()),
                                           "[INDEX]", convertToString(equation->nlaSystemIndex())),
                                   "[CODE]", generateMethodBodyCode(methodBody));

                // 2) Generate some code for the findRoot[INDEX]() method.
                //     a) Assign the values to our NLA solver's u array.

                methodBody = {};

                i = MAX_SIZE_T;

                for (const auto &variable : variables) {
                    auto arrayString = (variable->type() == AnalyserVariable::Type::STATE) ?
                                           mProfile->ratesArrayString() :
                                           mProfile->algebraicArrayString();

                    methodBody += mProfile->indentString()
                                  + mProfile->uArrayString() + mProfile->openArrayString() + convertToString(++i) + mProfile->closeArrayString()
                                  + mProfile->equalityString()
                                  + arrayString + mProfile->openArrayString() + variableIndexString(model, variable) + mProfile->closeArrayString()
                                  + mProfile->commandSeparatorString() + "\n";
                }

                //     b) Call our NLA solver.

                auto variablesCount = variables.size();

                methodBody += "\n"
                              + mProfile->indentString()
                              + replace(replace(mProfile->nlaSolveCallString(modelHasOdes(model), model->hasExternalVariables()),
                                                "[INDEX]", convertToString(equation->nlaSystemIndex())),
                                        "[SIZE]", convertToString(variablesCount));

                //     c) Retrieve the values from our NLA solver's u array.

                i = MAX_SIZE_T;

                methodBody += "\n";

                for (const auto &variable : variables) {
                    auto arrayString = (variable->type() == AnalyserVariable::Type::STATE) ?
                                           mProfile->ratesArrayString() :
                                           mProfile->algebraicArrayString();

                    methodBody += mProfile->indentString()
                                  + arrayString + mProfile->openArrayString() + variableIndexString(model, variable) + mProfile->closeArrayString()
                                  + mProfile->equalityString()
                                  + mProfile->uArrayString() + mProfile->openArrayString() + convertToString(++i) + mProfile->closeArrayString()
                                  + mProfile->commandSeparatorString() + "\n";
                }

                mCode += newLineIfNeeded()
                         + replace(replace(replace(mProfile->findRootMethodString(modelHasOdes(model), model->hasExternalVariables()),
                                                   "[INDEX]", convertToString(equation->nlaSystemIndex())),
                                           "[SIZE]", convertToString(variablesCount)),
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

std::string Generator::GeneratorImpl::generateDoubleOrVariableNameCode(const AnalyserModelPtr &model,
                                                                       const VariablePtr &variable)
{
    if (isCellMLReal(variable->initialValue())) {
        return generateDoubleCode(variable->initialValue());
    }

    auto initialValueVariable = owningComponent(variable)->variable(variable->initialValue());
    auto initialValueAnalyserVariable = model->variable(initialValueVariable);
    std::string arrayName;

    switch (initialValueAnalyserVariable->type()) {
    case AnalyserVariable::Type::STATE:
        arrayName = mProfile->statesArrayString();

        break;
    case AnalyserVariable::Type::CONSTANT:
        arrayName = mProfile->constantsArrayString();

        break;
    case AnalyserVariable::Type::COMPUTED_CONSTANT:
        arrayName = mProfile->computedConstantsArrayString();

        break;
    default: // If it is not one of the above types then it has to be an algebraic variable.
        arrayName = mProfile->algebraicArrayString();

        break;
    }

    return arrayName + mProfile->openArrayString() + variableIndexString(model, initialValueAnalyserVariable) + mProfile->closeArrayString();
}

std::string Generator::GeneratorImpl::generateVariableNameCode(const AnalyserModelPtr &model,
                                                               const VariablePtr &variable,
                                                               bool state)
{
    // Generate some code for a variable name, but only if we have a model. If
    // we don't have a model, it means that we are using the generator from the
    // analyser, in which case we just want to return the original name of the
    // variable.

    if (model == nullptr) {
        return variable->name();
    }

    auto analyserVariable = model->variable(variable);

    if (analyserVariable->type() == AnalyserVariable::Type::VARIABLE_OF_INTEGRATION) {
        return mProfile->voiString();
    }

    if (doIsTrackedVariable(model, analyserVariable, false)) {
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
    } else if (analyserVariable->type() == AnalyserVariable::Type::ALGEBRAIC) {
        arrayName = mProfile->algebraicArrayString();
    } else {
        arrayName = mProfile->externalArrayString();
    }

    return arrayName + mProfile->openArrayString() + variableIndexString(model, analyserVariable) + mProfile->closeArrayString();
}

std::string Generator::GeneratorImpl::generateOperatorCode(const AnalyserModelPtr &model, const std::string &op,
                                                           const AnalyserEquationAstPtr &ast)
{
    // Generate the code for the left and right branches of the given AST.

    std::string res;
    auto astLeftChild = ast->leftChild();
    auto astRightChild = ast->rightChild();
    auto astLeftChildCode = generateCode(model, astLeftChild);
    auto astRightChildCode = generateCode(model, astRightChild);

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

std::string Generator::GeneratorImpl::generateMinusUnaryCode(const AnalyserModelPtr &model,
                                                             const AnalyserEquationAstPtr &ast)
{
    // Generate the code for the left branch of the given AST.

    auto astLeftChild = ast->leftChild();
    auto code = generateCode(model, astLeftChild);

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

std::string Generator::GeneratorImpl::generateOneParameterFunctionCode(const AnalyserModelPtr &model,
                                                                       const std::string &function,
                                                                       const AnalyserEquationAstPtr &ast)
{
    return function + "(" + generateCode(model, ast->leftChild()) + ")";
}

std::string Generator::GeneratorImpl::generateTwoParameterFunctionCode(const AnalyserModelPtr &model,
                                                                       const std::string &function,
                                                                       const AnalyserEquationAstPtr &ast)
{
    return function + "(" + generateCode(model, ast->leftChild()) + ", " + generateCode(model, ast->rightChild()) + ")";
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

std::string Generator::GeneratorImpl::generateCode(const AnalyserModelPtr &model,
                                                   const AnalyserEquationAstPtr &ast)
{
    // Generate the code for the given AST.
    // Note: AnalyserEquationAst::Type::BVAR is only relevant when there is no
    //       model (in which case we want to generate something like dx/dt, as
    //       is in the case of the analyser when we want to mention an equation)
    //       since otherwise we don't need to generate any code for it (since we
    //       will, instead, want to generate something like rates[0]).

    std::string code;

    switch (ast->type()) {
    case AnalyserEquationAst::Type::EQUALITY:
        code = generateOperatorCode(model, mProfile->equalityString(), ast);

        break;
    case AnalyserEquationAst::Type::EQ:
        if (mProfile->hasEqOperator()) {
            code = generateOperatorCode(model, mProfile->eqString(), ast);
        } else {
            code = generateTwoParameterFunctionCode(model, mProfile->eqString(), ast);
        }

        break;
    case AnalyserEquationAst::Type::NEQ:
        if (mProfile->hasNeqOperator()) {
            code = generateOperatorCode(model, mProfile->neqString(), ast);
        } else {
            code = generateTwoParameterFunctionCode(model, mProfile->neqString(), ast);
        }

        break;
    case AnalyserEquationAst::Type::LT:
        if (mProfile->hasLtOperator()) {
            code = generateOperatorCode(model, mProfile->ltString(), ast);
        } else {
            code = generateTwoParameterFunctionCode(model, mProfile->ltString(), ast);
        }

        break;
    case AnalyserEquationAst::Type::LEQ:
        if (mProfile->hasLeqOperator()) {
            code = generateOperatorCode(model, mProfile->leqString(), ast);
        } else {
            code = generateTwoParameterFunctionCode(model, mProfile->leqString(), ast);
        }

        break;
    case AnalyserEquationAst::Type::GT:
        if (mProfile->hasGtOperator()) {
            code = generateOperatorCode(model, mProfile->gtString(), ast);
        } else {
            code = generateTwoParameterFunctionCode(model, mProfile->gtString(), ast);
        }

        break;
    case AnalyserEquationAst::Type::GEQ:
        if (mProfile->hasGeqOperator()) {
            code = generateOperatorCode(model, mProfile->geqString(), ast);
        } else {
            code = generateTwoParameterFunctionCode(model, mProfile->geqString(), ast);
        }

        break;
    case AnalyserEquationAst::Type::AND:
        if (mProfile->hasAndOperator()) {
            code = generateOperatorCode(model, mProfile->andString(), ast);
        } else {
            code = generateTwoParameterFunctionCode(model, mProfile->andString(), ast);
        }

        break;
    case AnalyserEquationAst::Type::OR:
        if (mProfile->hasOrOperator()) {
            code = generateOperatorCode(model, mProfile->orString(), ast);
        } else {
            code = generateTwoParameterFunctionCode(model, mProfile->orString(), ast);
        }

        break;
    case AnalyserEquationAst::Type::XOR:
        if (mProfile->hasXorOperator()) {
            code = generateOperatorCode(model, mProfile->xorString(), ast);
        } else {
            code = generateTwoParameterFunctionCode(model, mProfile->xorString(), ast);
        }

        break;
    case AnalyserEquationAst::Type::NOT:
        if (mProfile->hasNotOperator()) {
            code = mProfile->notString() + generateCode(model, ast->leftChild());
        } else {
            code = generateOneParameterFunctionCode(model, mProfile->notString(), ast);
        }

        break;
    case AnalyserEquationAst::Type::PLUS:
        if (ast->rightChild() != nullptr) {
            code = generateOperatorCode(model, mProfile->plusString(), ast);
        } else {
            code = generateCode(model, ast->leftChild());
        }

        break;
    case AnalyserEquationAst::Type::MINUS:
        if (ast->rightChild() != nullptr) {
            code = generateOperatorCode(model, mProfile->minusString(), ast);
        } else {
            code = generateMinusUnaryCode(model, ast);
        }

        break;
    case AnalyserEquationAst::Type::TIMES:
        code = generateOperatorCode(model, mProfile->timesString(), ast);

        break;
    case AnalyserEquationAst::Type::DIVIDE:
        code = generateOperatorCode(model, mProfile->divideString(), ast);

        break;
    case AnalyserEquationAst::Type::POWER: {
        auto stringValue = generateCode(model, ast->rightChild());
        double doubleValue;
        auto validConversion = convertToDouble(stringValue, doubleValue);

        if (validConversion && areEqual(doubleValue, 0.5)) {
            code = generateOneParameterFunctionCode(model, mProfile->squareRootString(), ast);
        } else if (validConversion && areEqual(doubleValue, 2.0)
                   && !mProfile->squareString().empty()) {
            code = generateOneParameterFunctionCode(model, mProfile->squareString(), ast);
        } else {
            code = mProfile->hasPowerOperator() ?
                       generateOperatorCode(model, mProfile->powerString(), ast) :
                       mProfile->powerString() + "(" + generateCode(model, ast->leftChild()) + ", " + stringValue + ")";
        }
    } break;
    case AnalyserEquationAst::Type::ROOT: {
        auto astRightChild = ast->rightChild();

        if (astRightChild != nullptr) {
            auto astLeftChild = ast->leftChild();
            double doubleValue;

            if (convertToDouble(generateCode(model, astLeftChild), doubleValue)
                && areEqual(doubleValue, 2.0)) {
                code = mProfile->squareRootString() + "(" + generateCode(model, astRightChild) + ")";
            } else {
                if (mProfile->hasPowerOperator()) {
                    code = generateOperatorCode(model, mProfile->powerString(), ast);
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

                    code = mProfile->powerString() + "(" + generateCode(model, astRightChild) + ", " + generateOperatorCode(model, mProfile->divideString(), rootValueAst) + ")";
                }
            }
        } else {
            code = generateOneParameterFunctionCode(model, mProfile->squareRootString(), ast);
        }
    } break;
    case AnalyserEquationAst::Type::ABS:
        code = generateOneParameterFunctionCode(model, mProfile->absoluteValueString(), ast);

        break;
    case AnalyserEquationAst::Type::EXP:
        code = generateOneParameterFunctionCode(model, mProfile->exponentialString(), ast);

        break;
    case AnalyserEquationAst::Type::LN:
        code = generateOneParameterFunctionCode(model, mProfile->naturalLogarithmString(), ast);

        break;
    case AnalyserEquationAst::Type::LOG: {
        auto astRightChild = ast->rightChild();

        if (astRightChild != nullptr) {
            auto stringValue = generateCode(model, ast->leftChild());
            double doubleValue;

            if (convertToDouble(stringValue, doubleValue)
                && areEqual(doubleValue, 10.0)) {
                code = mProfile->commonLogarithmString() + "(" + generateCode(model, astRightChild) + ")";
            } else {
                code = mProfile->naturalLogarithmString() + "(" + generateCode(model, astRightChild) + ")/" + mProfile->naturalLogarithmString() + "(" + stringValue + ")";
            }
        } else {
            code = generateOneParameterFunctionCode(model, mProfile->commonLogarithmString(), ast);
        }
    } break;
    case AnalyserEquationAst::Type::CEILING:
        code = generateOneParameterFunctionCode(model, mProfile->ceilingString(), ast);

        break;
    case AnalyserEquationAst::Type::FLOOR:
        code = generateOneParameterFunctionCode(model, mProfile->floorString(), ast);

        break;
    case AnalyserEquationAst::Type::MIN:
        code = generateTwoParameterFunctionCode(model, mProfile->minString(), ast);

        break;
    case AnalyserEquationAst::Type::MAX:
        code = generateTwoParameterFunctionCode(model, mProfile->maxString(), ast);

        break;
    case AnalyserEquationAst::Type::REM:
        code = generateTwoParameterFunctionCode(model, mProfile->remString(), ast);

        break;
    case AnalyserEquationAst::Type::DIFF:
        if (model != nullptr) {
            code = generateCode(model, ast->rightChild());
        } else {
            code = "d" + generateCode(model, ast->rightChild()) + "/d" + generateCode(model, ast->leftChild());
        }

        break;
    case AnalyserEquationAst::Type::SIN:
        code = generateOneParameterFunctionCode(model, mProfile->sinString(), ast);

        break;
    case AnalyserEquationAst::Type::COS:
        code = generateOneParameterFunctionCode(model, mProfile->cosString(), ast);

        break;
    case AnalyserEquationAst::Type::TAN:
        code = generateOneParameterFunctionCode(model, mProfile->tanString(), ast);

        break;
    case AnalyserEquationAst::Type::SEC:
        code = generateOneParameterFunctionCode(model, mProfile->secString(), ast);

        break;
    case AnalyserEquationAst::Type::CSC:
        code = generateOneParameterFunctionCode(model, mProfile->cscString(), ast);

        break;
    case AnalyserEquationAst::Type::COT:
        code = generateOneParameterFunctionCode(model, mProfile->cotString(), ast);

        break;
    case AnalyserEquationAst::Type::SINH:
        code = generateOneParameterFunctionCode(model, mProfile->sinhString(), ast);

        break;
    case AnalyserEquationAst::Type::COSH:
        code = generateOneParameterFunctionCode(model, mProfile->coshString(), ast);

        break;
    case AnalyserEquationAst::Type::TANH:
        code = generateOneParameterFunctionCode(model, mProfile->tanhString(), ast);

        break;
    case AnalyserEquationAst::Type::SECH:
        code = generateOneParameterFunctionCode(model, mProfile->sechString(), ast);

        break;
    case AnalyserEquationAst::Type::CSCH:
        code = generateOneParameterFunctionCode(model, mProfile->cschString(), ast);

        break;
    case AnalyserEquationAst::Type::COTH:
        code = generateOneParameterFunctionCode(model, mProfile->cothString(), ast);

        break;
    case AnalyserEquationAst::Type::ASIN:
        code = generateOneParameterFunctionCode(model, mProfile->asinString(), ast);

        break;
    case AnalyserEquationAst::Type::ACOS:
        code = generateOneParameterFunctionCode(model, mProfile->acosString(), ast);

        break;
    case AnalyserEquationAst::Type::ATAN:
        code = generateOneParameterFunctionCode(model, mProfile->atanString(), ast);

        break;
    case AnalyserEquationAst::Type::ASEC:
        code = generateOneParameterFunctionCode(model, mProfile->asecString(), ast);

        break;
    case AnalyserEquationAst::Type::ACSC:
        code = generateOneParameterFunctionCode(model, mProfile->acscString(), ast);

        break;
    case AnalyserEquationAst::Type::ACOT:
        code = generateOneParameterFunctionCode(model, mProfile->acotString(), ast);

        break;
    case AnalyserEquationAst::Type::ASINH:
        code = generateOneParameterFunctionCode(model, mProfile->asinhString(), ast);

        break;
    case AnalyserEquationAst::Type::ACOSH:
        code = generateOneParameterFunctionCode(model, mProfile->acoshString(), ast);

        break;
    case AnalyserEquationAst::Type::ATANH:
        code = generateOneParameterFunctionCode(model, mProfile->atanhString(), ast);

        break;
    case AnalyserEquationAst::Type::ASECH:
        code = generateOneParameterFunctionCode(model, mProfile->asechString(), ast);

        break;
    case AnalyserEquationAst::Type::ACSCH:
        code = generateOneParameterFunctionCode(model, mProfile->acschString(), ast);

        break;
    case AnalyserEquationAst::Type::ACOTH:
        code = generateOneParameterFunctionCode(model, mProfile->acothString(), ast);

        break;
    case AnalyserEquationAst::Type::PIECEWISE: {
        auto astRightChild = ast->rightChild();

        if (astRightChild != nullptr) {
            if (astRightChild->type() == AnalyserEquationAst::Type::PIECE) {
                code = generateCode(model, ast->leftChild()) + generatePiecewiseElseCode(generateCode(model, astRightChild) + generatePiecewiseElseCode(mProfile->nanString()));
            } else {
                code = generateCode(model, ast->leftChild()) + generatePiecewiseElseCode(generateCode(model, astRightChild));
            }
        } else {
            code = generateCode(model, ast->leftChild()) + generatePiecewiseElseCode(mProfile->nanString());
        }
    } break;
    case AnalyserEquationAst::Type::PIECE:
        code = generatePiecewiseIfCode(generateCode(model, ast->rightChild()), generateCode(model, ast->leftChild()));

        break;
    case AnalyserEquationAst::Type::OTHERWISE:
        code = generateCode(model, ast->leftChild());

        break;
    case AnalyserEquationAst::Type::CI: {
        code = generateVariableNameCode(model, ast->variable(), ast->parent()->type() != AnalyserEquationAst::Type::DIFF);

        auto astParent = ast->parent();

        if ((model != nullptr)
            && (astParent->type() == AnalyserEquationAst::Type::EQUALITY)
            && (astParent->leftChild() == ast)
            && doIsTrackedVariable(model, model->variable(ast->variable()), false)) {
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
        code = generateCode(model, ast->leftChild());

        break;
    case AnalyserEquationAst::Type::BVAR:
        code = generateCode(model, ast->leftChild());

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

bool Generator::GeneratorImpl::isToBeComputedAgain(const AnalyserEquationPtr &equation)
{
    // NLA and algebraic equations that are state/rate-based and external equations are to be computed again (in the
    // computeVariables() method) unless the variables they compute are not tracked.

    switch (equation->type()) {
    case AnalyserEquation::Type::NLA:
    case AnalyserEquation::Type::ALGEBRAIC:
        if (equation->isStateRateBased()) {
            for (const auto &variable : variables(equation)) {
                if (doIsTrackedVariable(variable->model(), variable)) {
                    return true;
                }
            }

            return false;
        }

        return false;
    case AnalyserEquation::Type::EXTERNAL:
        return isTrackedEquation(equation);
    default:
        return false;
    }
}

bool Generator::GeneratorImpl::isSomeConstant(const AnalyserEquationPtr &equation,
                                              bool includeComputedConstants) const
{
    return (equation->type() == AnalyserEquation::Type::CONSTANT)
           || (!includeComputedConstants && (equation->type() == AnalyserEquation::Type::COMPUTED_CONSTANT));
}

std::string Generator::GeneratorImpl::generateZeroInitialisationCode(const AnalyserModelPtr &model,
                                                                     const AnalyserVariablePtr &variable)
{
    return mProfile->indentString()
           + generateVariableNameCode(model, variable->variable(), false)
           + mProfile->equalityString()
           + "0.0"
           + mProfile->commandSeparatorString() + "\n";
}

std::string Generator::GeneratorImpl::generateInitialisationCode(const AnalyserModelPtr &model,
                                                                 const AnalyserVariablePtr &variable, bool force)
{
    if (!force && doIsTrackedVariable(model, variable, false)) {
        return {};
    }

    auto initialisingVariable = variable->initialisingVariable();
    auto scalingFactor = Generator::GeneratorImpl::scalingFactor(model, initialisingVariable);
    std::string scalingFactorCode;

    if (!areNearlyEqual(scalingFactor, 1.0)) {
        scalingFactorCode = generateDoubleCode(convertToString(scalingFactor)) + mProfile->timesString();
    }

    auto code = generateVariableNameCode(model, variable->variable())
                + mProfile->equalityString()
                + scalingFactorCode + generateDoubleOrVariableNameCode(model, initialisingVariable)
                + mProfile->commandSeparatorString() + "\n";

    if (doIsTrackedVariable(model, variable, false)) {
        code = replace(mProfile->variableDeclarationString(), "[CODE]", code);
    }

    return mProfile->indentString()
           + code;
}

std::string Generator::GeneratorImpl::generateEquationCode(const AnalyserModelPtr &model,
                                                           const AnalyserEquationPtr &equation,
                                                           std::vector<AnalyserEquationPtr> &remainingEquations,
                                                           std::vector<AnalyserEquationPtr> &equationsForDependencies,
                                                           std::vector<AnalyserVariablePtr> &generatedConstantDependencies,
                                                           bool includeComputedConstants,
                                                           GenerateEquationCodeTarget target)
{
    std::string res;

    if (std::find(remainingEquations.begin(), remainingEquations.end(), equation) != remainingEquations.end()) {
        // Stop tracking the equation and its NLA siblings, if any.
        // Note: we need to do this as soon as possible to avoid recursive
        //       calls, something that would happen if we were to do this at the
        //       end of this if statement.

        remainingEquations.erase(std::find(remainingEquations.begin(), remainingEquations.end(), equation));

        for (const auto &nlaSibling : equation->nlaSiblings()) {
            remainingEquations.erase(std::find(remainingEquations.begin(), remainingEquations.end(), nlaSibling));
        }

        // Generate any dependency that this equation may have.

        for (const auto &constantDependency : equation->mPimpl->mConstantDependencies) {
            if ((equation->type() != AnalyserEquation::Type::NLA)
                && doIsTrackedVariable(model, constantDependency, false)
                && (std::find(generatedConstantDependencies.begin(), generatedConstantDependencies.end(), constantDependency) == generatedConstantDependencies.end())) {
                res += generateInitialisationCode(model, constantDependency, true);

                generatedConstantDependencies.push_back(constantDependency);
            }
        }

        if (!isSomeConstant(equation, includeComputedConstants)) {
            for (const auto &dependency : equation->dependencies()) {
                if (((equation->type() != AnalyserEquation::Type::NLA)
                     && (dependency->type() == AnalyserEquation::Type::COMPUTED_CONSTANT)
                     && isUntrackedEquation(dependency))
                    || (((target == GenerateEquationCodeTarget::NORMAL)
                         || ((target == GenerateEquationCodeTarget::COMPUTE_VARIABLES)
                             && ((dependency->type() != AnalyserEquation::Type::NLA)
                                 || isToBeComputedAgain(dependency)
                                 || (std::find(equationsForDependencies.begin(), equationsForDependencies.end(), dependency) != equationsForDependencies.end()))))
                        && (dependency->type() != AnalyserEquation::Type::ODE)
                        && (isTrackedEquation(dependency)
                            || (equation->type() != AnalyserEquation::Type::NLA))
                        && !isSomeConstant(dependency, includeComputedConstants)
                        && (equationsForDependencies.empty()
                            || isToBeComputedAgain(dependency)
                            || (std::find(equationsForDependencies.begin(), equationsForDependencies.end(), dependency) != equationsForDependencies.end())))) {
                    res += generateEquationCode(model, dependency, remainingEquations, equationsForDependencies,
                                                generatedConstantDependencies, includeComputedConstants, target);
                }
            }
        }

        // Generate the equation code itself, based on the equation type.

        switch (equation->type()) {
        case AnalyserEquation::Type::EXTERNAL:
            for (const auto &variable : variables(equation)) {
                res += mProfile->indentString()
                       + generateVariableNameCode(model, variable->variable())
                       + mProfile->equalityString()
                       + replace(mProfile->externalVariableMethodCallString(modelHasOdes(model)),
                                 "[INDEX]", variableIndexString(model, variable))
                       + mProfile->commandSeparatorString() + "\n";
            }

            break;
        case AnalyserEquation::Type::NLA:
            if (!mProfile->findRootCallString(modelHasOdes(model), model->hasExternalVariables()).empty()) {
                res += mProfile->indentString()
                       + replace(mProfile->findRootCallString(modelHasOdes(model), model->hasExternalVariables()),
                                 "[INDEX]", convertToString(equation->nlaSystemIndex()));
            }

            break;
        default:
            res += mProfile->indentString() + generateCode(model, equation->ast()) + mProfile->commandSeparatorString() + "\n";

            break;
        }
    }

    return res;
}

std::string Generator::GeneratorImpl::generateEquationCode(const AnalyserModelPtr &model,
                                                           const AnalyserEquationPtr &equation,
                                                           std::vector<AnalyserEquationPtr> &remainingEquations,
                                                           std::vector<AnalyserVariablePtr> &generatedConstantDependencies)
{
    std::vector<AnalyserEquationPtr> dummyEquationsForComputeVariables;

    return generateEquationCode(model, equation, remainingEquations, dummyEquationsForComputeVariables,
                                generatedConstantDependencies, true);
}

bool Generator::GeneratorImpl::hasComputedConstantDependency(const AnalyserModelPtr &model,
                                                             const AnalyserVariablePtr &variable)
{
    // Check if the variable has a direct or indirect dependency on a computed constant.

    if (variable->type() == AnalyserVariable::Type::COMPUTED_CONSTANT) {
        return true;
    }

    auto initialisingVariable = variable->initialisingVariable();
    auto initialValueVariable = owningComponent(initialisingVariable)->variable(initialisingVariable->initialValue());

    if (initialValueVariable == nullptr) {
        return false;
    }

    return hasComputedConstantDependency(model, model->variable(initialValueVariable));
}

std::string Generator::GeneratorImpl::generateInitialiseVariableCode(const AnalyserModelPtr &model,
                                                                     const AnalyserVariablePtr &variable,
                                                                     std::vector<AnalyserEquationPtr> &remainingEquations,
                                                                     std::vector<AnalyserVariablePtr> &remainingStates,
                                                                     std::vector<AnalyserVariablePtr> &remainingConstants,
                                                                     std::vector<AnalyserVariablePtr> &remainingComputedConstants,
                                                                     std::vector<AnalyserVariablePtr> &remainingAlgebraic,
                                                                     std::vector<AnalyserVariablePtr> *generatedConstantDependencies)
{
    std::string res;

    // Check if the variable is initialised using a constant value or an initialising variable.

    auto initialisingVariable = variable->initialisingVariable();
    auto initialValueVariable = (initialisingVariable != nullptr) ? owningComponent(initialisingVariable)->variable(initialisingVariable->initialValue()) : nullptr;
    auto initialiseAnalyserVariable = true;

    if (initialValueVariable != nullptr) {
        // The initial value references a state, a constant, a computed constant, or an algebraic variable, so generate
        // initialisation code for that variable first, if conditions are met.

        auto initialValueAnalyserVariable = model->variable(initialValueVariable);
        auto &remainingVariables = (initialValueAnalyserVariable->type() == AnalyserVariable::Type::STATE) ?
                                       remainingStates :
                                   (initialValueAnalyserVariable->type() == AnalyserVariable::Type::CONSTANT) ?
                                       remainingConstants :
                                   (initialValueAnalyserVariable->type() == AnalyserVariable::Type::COMPUTED_CONSTANT) ?
                                       remainingComputedConstants :
                                       remainingAlgebraic;

        if (((generatedConstantDependencies == nullptr) && !hasComputedConstantDependency(model, initialValueAnalyserVariable))
            || (generatedConstantDependencies != nullptr)) {
            auto initialisingAnalyserVariable = std::find_if(remainingVariables.begin(), remainingVariables.end(),
                                                             [&](const AnalyserVariablePtr &av) {
                                                                 return areEquivalentVariables(initialValueVariable, av->variable());
                                                             });

            if (initialisingAnalyserVariable != remainingVariables.end()) {
                res += generateInitialiseVariableCode(model, AnalyserVariablePtr(*initialisingAnalyserVariable),
                                                      remainingEquations, remainingStates, remainingConstants,
                                                      remainingComputedConstants, remainingAlgebraic,
                                                      generatedConstantDependencies);
            }
        } else {
            initialiseAnalyserVariable = false;
        }
    }

    // Now initialise the variable itself, if we can.

    if (initialiseAnalyserVariable) {
        auto &remainingVariables = (variable->type() == AnalyserVariable::Type::STATE) ?
                                       remainingStates :
                                   (variable->type() == AnalyserVariable::Type::CONSTANT) ?
                                       remainingConstants :
                                   (variable->type() == AnalyserVariable::Type::COMPUTED_CONSTANT) ?
                                       remainingComputedConstants :
                                       remainingAlgebraic;
        auto remainingVariable = std::find(remainingVariables.begin(), remainingVariables.end(), variable);

        if (remainingVariable != remainingVariables.end()) {
            if (remainingVariables != remainingComputedConstants) {
                res += generateInitialisationCode(model, AnalyserVariablePtr(*remainingVariable));
            } else {
                res += generateEquationCode(model, variable->equation(0), remainingEquations, *generatedConstantDependencies);
            }

            remainingVariables.erase(remainingVariable);
        }
    }

    return res;
}

void Generator::GeneratorImpl::addInterfaceComputeModelMethodsCode(const AnalyserModelPtr &model)
{
    auto interfaceInitialiseVariablesMethodString = mProfile->interfaceInitialiseVariablesMethodString(modelHasOdes(model));
    std::string code;

    if (!interfaceInitialiseVariablesMethodString.empty()) {
        code += interfaceInitialiseVariablesMethodString;
    }

    if (!mProfile->interfaceComputeComputedConstantsMethodString(modelHasOdes(model)).empty()) {
        code += mProfile->interfaceComputeComputedConstantsMethodString(modelHasOdes(model));
    }

    auto interfaceComputeRatesMethodString = mProfile->interfaceComputeRatesMethodString(model->hasExternalVariables());

    if (modelHasOdes(model)
        && !interfaceComputeRatesMethodString.empty()) {
        code += interfaceComputeRatesMethodString;
    }

    auto interfaceComputeVariablesMethodString = mProfile->interfaceComputeVariablesMethodString(modelHasOdes(model),
                                                                                                 model->hasExternalVariables());

    if (!interfaceComputeVariablesMethodString.empty()) {
        code += interfaceComputeVariablesMethodString;
    }

    if (!code.empty()) {
        mCode += newLineIfNeeded()
                 + code;
    }
}

void Generator::GeneratorImpl::addImplementationInitialiseVariablesMethodCode(const AnalyserModelPtr &model,
                                                                              std::vector<AnalyserEquationPtr> &remainingEquations,
                                                                              std::vector<AnalyserVariablePtr> &remainingStates,
                                                                              std::vector<AnalyserVariablePtr> &remainingConstants,
                                                                              std::vector<AnalyserVariablePtr> &remainingComputedConstants,
                                                                              std::vector<AnalyserVariablePtr> &remainingAlgebraic)
{
    // Note: we must always generate the method body (even if we don't end up generating the method itself) because
    //       addImplementationComputeComputedConstantsMethodCode() expects our "remaining" parameters to be updated
    //       correctly.

    // Initialise our states.

    std::string methodBody;

    for (const auto &state : model->states()) {
        methodBody += generateInitialiseVariableCode(model, state,
                                                     remainingEquations, remainingStates, remainingConstants,
                                                     remainingComputedConstants, remainingAlgebraic);
    }

    // Use an initial guess of zero for rates computed using an NLA system (see the note below).

    for (const auto &state : model->states()) {
        if (state->equation(0)->type() == AnalyserEquation::Type::NLA) {
            methodBody += generateZeroInitialisationCode(model, state);
        }
    }

    // Initialise our remaining constants.

    while (!remainingConstants.empty()) {
        methodBody += generateInitialiseVariableCode(model, AnalyserVariablePtr(*remainingConstants.begin()),
                                                     remainingEquations, remainingStates, remainingConstants,
                                                     remainingComputedConstants, remainingAlgebraic);
    }

    // Initialise our computed constants that are initialised using an equation (e.g., x = 3 rather than x with an
    // initial value of 3).

    std::vector<AnalyserVariablePtr> generatedConstantDependencies;

    for (const auto &equation : model->equations()) {
        if (equation->type() == AnalyserEquation::Type::CONSTANT) {
            methodBody += generateEquationCode(model, equation, remainingEquations, generatedConstantDependencies);
        }
    }

    // Initialise our algebraic variables that have an initial value. Also use an initial guess of zero for algebraic
    // variables computed using an NLA system.
    // Note: a variable which is the only unknown in an equation, but which is not on its own on either the LHS or RHS
    //       of that equation (e.g., x = y+z with x and y known and z unknown) is (currently) to be computed using an
    //       NLA system for which we need an initial guess. We use an initial guess of zero, which is fine since such an
    //       NLA system has only one solution.

    for (const auto &algebraic : model->algebraic()) {
        if (algebraic->initialisingVariable() != nullptr) {
            methodBody += generateInitialiseVariableCode(model, algebraic,
                                                         remainingEquations, remainingStates, remainingConstants,
                                                         remainingComputedConstants, remainingAlgebraic);
        }
    }

    // Generate the method itself, if needed.

    auto implementationInitialiseVariablesMethodString = mProfile->implementationInitialiseVariablesMethodString(modelHasOdes(model));

    if (!implementationInitialiseVariablesMethodString.empty()) {
        mCode += newLineIfNeeded()
                 + replace(implementationInitialiseVariablesMethodString,
                           "[CODE]", generateMethodBodyCode(methodBody));
    }
}

void Generator::GeneratorImpl::addImplementationComputeComputedConstantsMethodCode(const AnalyserModelPtr &model,
                                                                                   std::vector<AnalyserEquationPtr> &remainingEquations,
                                                                                   std::vector<AnalyserVariablePtr> &remainingStates,
                                                                                   std::vector<AnalyserVariablePtr> &remainingConstants,
                                                                                   std::vector<AnalyserVariablePtr> &remainingComputedConstants,
                                                                                   std::vector<AnalyserVariablePtr> &remainingAlgebraic)
{
    if (!mProfile->implementationComputeComputedConstantsMethodString(modelHasOdes(model)).empty()) {
        // Initialise our remaining states (which are initialised using a computed constant).

        std::string methodBody;
        std::vector<AnalyserVariablePtr> generatedConstantDependencies;

        for (const auto &state : model->states()) {
            methodBody += generateInitialiseVariableCode(model, state,
                                                         remainingEquations, remainingStates, remainingConstants,
                                                         remainingComputedConstants, remainingAlgebraic,
                                                         &generatedConstantDependencies);
        }

        // Initialise our remaining computed constants.

        for (const auto &equation : model->equations()) {
            if ((equation->type() == AnalyserEquation::Type::COMPUTED_CONSTANT)
                && isTrackedEquation(equation)) {
                methodBody += generateInitialiseVariableCode(model, equation->computedConstant(0),
                                                             remainingEquations, remainingStates, remainingConstants,
                                                             remainingComputedConstants, remainingAlgebraic,
                                                             &generatedConstantDependencies);
            }
        }

        // Initialise our algebraic variables that are initialised using a computed constant.

        for (const auto &algebraic : model->algebraic()) {
            if (algebraic->initialisingVariable() != nullptr) {
                methodBody += generateInitialiseVariableCode(model, algebraic,
                                                             remainingEquations, remainingStates, remainingConstants,
                                                             remainingComputedConstants, remainingAlgebraic,
                                                             &generatedConstantDependencies);
            }
        }

        mCode += newLineIfNeeded()
                 + replace(mProfile->implementationComputeComputedConstantsMethodString(modelHasOdes(model)),
                           "[CODE]", generateMethodBodyCode(methodBody));
    }
}

void Generator::GeneratorImpl::addImplementationComputeRatesMethodCode(const AnalyserModelPtr &model,
                                                                       std::vector<AnalyserEquationPtr> &remainingEquations)
{
    auto implementationComputeRatesMethodString = mProfile->implementationComputeRatesMethodString(model->hasExternalVariables());

    if (modelHasOdes(model)
        && !implementationComputeRatesMethodString.empty()) {
        std::string methodBody;
        std::vector<AnalyserVariablePtr> generatedConstantDependencies;

        for (const auto &equation : model->equations()) {
            // A rate is computed either through an ODE equation or through an
            // NLA equation in case the rate is not on its own on either the LHS
            // or RHS of the equation.

            auto variables = libcellml::variables(equation);

            if ((equation->type() == AnalyserEquation::Type::ODE)
                || ((equation->type() == AnalyserEquation::Type::NLA)
                    && (variables.size() == 1)
                    && (variables[0]->type() == AnalyserVariable::Type::STATE))) {
                methodBody += generateEquationCode(model, equation, remainingEquations, generatedConstantDependencies);
            }
        }

        mCode += newLineIfNeeded()
                 + replace(implementationComputeRatesMethodString,
                           "[CODE]", generateMethodBodyCode(methodBody));
    }
}

void Generator::GeneratorImpl::addImplementationComputeVariablesMethodCode(const AnalyserModelPtr &model,
                                                                           std::vector<AnalyserEquationPtr> &remainingEquations)
{
    auto implementationComputeVariablesMethodString = mProfile->implementationComputeVariablesMethodString(modelHasOdes(model),
                                                                                                           model->hasExternalVariables());

    if (!implementationComputeVariablesMethodString.empty()) {
        std::string methodBody;
        auto equations = model->equations();
        auto newRemainingEquations = equations;
        std::vector<AnalyserVariablePtr> generatedConstantDependencies;

        for (const auto &equation : equations) {
            if (((std::find(remainingEquations.begin(), remainingEquations.end(), equation) != remainingEquations.end())
                 || isToBeComputedAgain(equation))
                && isTrackedEquation(equation)) {
                methodBody += generateEquationCode(model, equation, newRemainingEquations, remainingEquations,
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

bool Generator::isTrackedVariable(const AnalyserVariablePtr &variable)
{
    return pFunc()->isTrackedVariable(variable);
}

bool Generator::isUntrackedVariable(const AnalyserVariablePtr &variable)
{
    return pFunc()->isUntrackedVariable(variable);
}

void Generator::trackVariable(const AnalyserVariablePtr &variable)
{
    pFunc()->trackVariable(variable);
}

void Generator::untrackVariable(const AnalyserVariablePtr &variable)
{
    pFunc()->untrackVariable(variable);
}

void Generator::trackAllConstants(const AnalyserModelPtr &model)
{
    pFunc()->trackAllConstants(model);
}

void Generator::untrackAllConstants(const AnalyserModelPtr &model)
{
    pFunc()->untrackAllConstants(model);
}

void Generator::trackAllComputedConstants(const AnalyserModelPtr &model)
{
    pFunc()->trackAllComputedConstants(model);
}

void Generator::untrackAllComputedConstants(const AnalyserModelPtr &model)
{
    pFunc()->untrackAllComputedConstants(model);
}

void Generator::trackAllAlgebraic(const AnalyserModelPtr &model)
{
    pFunc()->trackAllAlgebraic(model);
}

void Generator::untrackAllAlgebraic(const AnalyserModelPtr &model)
{
    pFunc()->untrackAllAlgebraic(model);
}

void Generator::trackAllVariables(const AnalyserModelPtr &model)
{
    pFunc()->trackAllVariables(model);
}

void Generator::untrackAllVariables(const AnalyserModelPtr &model)
{
    pFunc()->untrackAllVariables(model);
}

size_t Generator::trackedConstantCount(const AnalyserModelPtr &model)
{
    return pFunc()->trackedConstantCount(model);
}

size_t Generator::untrackedConstantCount(const AnalyserModelPtr &model)
{
    return pFunc()->untrackedConstantCount(model);
}

size_t Generator::trackedComputedConstantCount(const AnalyserModelPtr &model)
{
    return pFunc()->trackedComputedConstantCount(model);
}

size_t Generator::untrackedComputedConstantCount(const AnalyserModelPtr &model)
{
    return pFunc()->untrackedComputedConstantCount(model);
}

size_t Generator::trackedAlgebraicCount(const AnalyserModelPtr &model)
{
    return pFunc()->trackedAlgebraicCount(model);
}

size_t Generator::untrackedAlgebraicCount(const AnalyserModelPtr &model)
{
    return pFunc()->untrackedAlgebraicCount(model);
}

size_t Generator::trackedVariableCount(const AnalyserModelPtr &model)
{
    return pFunc()->trackedVariableCount(model);
}

size_t Generator::untrackedVariableCount(const AnalyserModelPtr &model)
{
    return pFunc()->untrackedVariableCount(model);
}

std::string Generator::interfaceCode(const AnalyserModelPtr &model)
{
    if ((model == nullptr)
        || (pFunc()->mProfile == nullptr)
        || !model->isValid()
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

    pFunc()->addStateAndVariableCountCode(model, true);

    // Add code for the variable information related objects.

    pFunc()->addVariableInfoObjectCode(model);

    // Add code for the interface of the information about the variable of integration, states, constants, computed
    // constants, algebraic variables, and external variables.

    pFunc()->addInterfaceVariableInfoCode(model);

    // Add code for the interface to create and delete arrays.

    pFunc()->addInterfaceCreateDeleteArrayMethodsCode(model);

    // Add code for the external variable method type definition.

    pFunc()->addExternalVariableMethodTypeDefinitionCode(model);

    // Add code for the interface to compute the model.

    pFunc()->addInterfaceComputeModelMethodsCode(model);

    return pFunc()->mCode;
}

std::string Generator::implementationCode(const AnalyserModelPtr &model)
{
    if ((model == nullptr)
        || (pFunc()->mProfile == nullptr)
        || !model->isValid()) {
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

    pFunc()->addStateAndVariableCountCode(model);

    // Add code for the variable information related objects.

    if (!pFunc()->mProfile->hasInterface()) {
        pFunc()->addVariableInfoObjectCode(model);
    }

    // Add code for the implementation of the information about the variable of integration, states, constants, computed
    // constants, algebraic variables, and external variables.

    pFunc()->addImplementationVariableInfoCode(model);

    // Add code for the arithmetic and trigonometric functions.

    pFunc()->addArithmeticFunctionsCode(model);
    pFunc()->addTrigonometricFunctionsCode(model);

    // Add code for the implementation to create and delete arrays.

    pFunc()->addImplementationCreateDeleteArrayMethodsCode(model);

    // Add code for the NLA solver.

    auto needNlaSolving = false;

    for (const auto &equation : model->equations()) {
        if (equation->type() == AnalyserEquation::Type::NLA) {
            needNlaSolving = true;

            break;
        }
    }

    if (needNlaSolving) {
        pFunc()->addRootFindingInfoObjectCode(model);
        pFunc()->addExternNlaSolveMethodCode();
        pFunc()->addNlaSystemsCode(model);
    }

    // Add code for the implementation to initialise our variables.

    auto remainingEquations = model->equations();
    auto remainingStates = model->states();
    auto remainingConstants = model->constants();
    auto remainingComputedConstants = model->computedConstants();
    auto remainingAlgebraic = model->algebraic();

    pFunc()->addImplementationInitialiseVariablesMethodCode(model, remainingEquations, remainingStates,
                                                            remainingConstants, remainingComputedConstants,
                                                            remainingAlgebraic);

    // Add code for the implementation to compute our computed constants.

    pFunc()->addImplementationComputeComputedConstantsMethodCode(model, remainingEquations, remainingStates,
                                                                 remainingConstants, remainingComputedConstants,
                                                                 remainingAlgebraic);

    // Add code for the implementation to compute our rates (and any variables
    // on which they depend).

    pFunc()->addImplementationComputeRatesMethodCode(model, remainingEquations);

    // Add code for the implementation to compute our variables.
    // Note: this method computes the remaining variables, i.e. the ones not
    //       needed to compute our rates, but also the variables that depend on
    //       the value of some states/rates and all the external variables.
    //       This method is typically called after having integrated a model,
    //       thus ensuring that variables that rely on the value of some
    //       states/rates are up to date.

    pFunc()->addImplementationComputeVariablesMethodCode(model, remainingEquations);

    return pFunc()->mCode;
}

std::string Generator::equationCode(const AnalyserEquationAstPtr &ast,
                                    const GeneratorProfilePtr &generatorProfile)
{
    GeneratorPtr generator = libcellml::Generator::create();

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

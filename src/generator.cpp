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

bool Generator::GeneratorImpl::doTrackVariable(const ModelPtr &model, const VariablePtr &variable, bool tracked)
{
    mTrackedVariables[model][variable] = tracked;

    return true;
}

bool Generator::GeneratorImpl::doTrackVariable(const AnalyserModelPtr &model, const VariablePtr &variable, bool tracked)
{
    if ((model == nullptr) || (variable == nullptr)) {
        return false;
    }

    auto owningModel = libcellml::owningModel(variable);

    if (owningModel == nullptr) {
        return false;
    }

    for (const auto &untrackableVariable : variables(model, false)) {
        if (model->areEquivalentVariables(variable, untrackableVariable->variable())) {
            return doTrackVariable(owningModel, variable, tracked);
        }
    }

    return false;
}

bool Generator::GeneratorImpl::trackVariable(const AnalyserModelPtr &model, const VariablePtr &variable)
{
    return doTrackVariable(model, variable, true);
}

bool Generator::GeneratorImpl::untrackVariable(const AnalyserModelPtr &model, const VariablePtr &variable)
{
    return doTrackVariable(model, variable, false);
}

bool Generator::GeneratorImpl::doTrackAllVariables(const AnalyserModelPtr &model, bool tracked)
{
    if (model == nullptr) {
        return false;
    }

    for (const auto &variable : variables(model, false)) {
        doTrackVariable(model->mPimpl->mModel, variable->variable(), tracked);
    }

    return true;
}

bool Generator::GeneratorImpl::trackAllVariables(const AnalyserModelPtr &model)
{
    return doTrackAllVariables(model, true);
}

bool Generator::GeneratorImpl::untrackAllVariables(const AnalyserModelPtr &model)
{
    return doTrackAllVariables(model, false);
}

size_t Generator::GeneratorImpl::doTrackedVariableCount(const AnalyserModelPtr &model, bool tracked)
{
    if (model == nullptr) {
        return 0;
    }

    size_t res = 0;

    for (const auto &variable : variables(model, false)) {
        if (mTrackedVariables[model->mPimpl->mModel].find(variable->variable()) == mTrackedVariables[model->mPimpl->mModel].end()) {
            mTrackedVariables[model->mPimpl->mModel][variable->variable()] = true;
        }

        if (mTrackedVariables[model->mPimpl->mModel][variable->variable()] == tracked) {
            ++res;
        }
    }

    return res;
}

size_t Generator::GeneratorImpl::trackedVariableCount(const AnalyserModelPtr &model)
{
    return doTrackedVariableCount(model, true);
}

size_t Generator::GeneratorImpl::untrackedVariableCount(const AnalyserModelPtr &model)
{
    return doTrackedVariableCount(model, false);
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

bool Generator::GeneratorImpl::modelHasNlas(const AnalyserModelPtr &model) const
{
    switch (model->type()) {
    case AnalyserModel::Type::NLA:
    case AnalyserModel::Type::DAE:
        return true;
    default:
        return false;
    }
}

AnalyserVariablePtr Generator::GeneratorImpl::analyserVariable(const AnalyserModelPtr &model,
                                                               const VariablePtr &variable) const
{
    // Find and return the analyser variable associated with the given variable.

    AnalyserVariablePtr res;
    auto modelVoi = model->voi();
    VariablePtr modelVoiVariable = (modelVoi != nullptr) ? modelVoi->variable() : nullptr;

    if ((modelVoiVariable != nullptr)
        && model->areEquivalentVariables(variable, modelVoiVariable)) {
        res = modelVoi;
    } else {
        // Normally, we would have something like:
        //
        //     for (const auto &modelVariable : variables(model)) {
        //         if (model->areEquivalentVariables(variable, modelVariable->variable())) {
        //             res = modelVariable;
        //
        //             break;
        //         }
        //     }
        //
        // but we always have variables, so llvm-cov will complain that the false branch of our for loop is never
        // reached. The below code is a bit more verbose but at least it makes llvm-cov happy.

        auto modelVariables = variables(model);
        auto modelVariable = modelVariables.begin();

        do {
            if (model->areEquivalentVariables(variable, (*modelVariable)->variable())) {
                res = *modelVariable;
            } else {
                ++modelVariable;
            }
        } while (res == nullptr);
    }

    return res;
}

double Generator::GeneratorImpl::scalingFactor(const AnalyserModelPtr &model, const VariablePtr &variable) const
{
    // Return the scaling factor for the given variable, accounting for the fact that a constant may be initialised by
    // another variable which initial value may be defined in a different component.

    auto analyserVariable = Generator::GeneratorImpl::analyserVariable(model, variable);

    if ((analyserVariable->type() == AnalyserVariable::Type::CONSTANT)
        && !isCellMLReal(variable->initialValue())) {
        auto initialValueVariable = owningComponent(variable)->variable(variable->initialValue());
        auto initialValueAnalyserVariable = Generator::GeneratorImpl::analyserVariable(model, initialValueVariable);

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
                            "[CONSTANT_COUNT]", std::to_string(model->constantCount()));
    }

    if ((interface && !mProfile->interfaceComputedConstantCountString().empty())
        || (!interface && !mProfile->implementationComputedConstantCountString().empty())) {
        code += interface ?
                    mProfile->interfaceComputedConstantCountString() :
                    replace(mProfile->implementationComputedConstantCountString(),
                            "[COMPUTED_CONSTANT_COUNT]", std::to_string(model->computedConstantCount()));
    }

    if ((interface && !mProfile->interfaceAlgebraicCountString().empty())
        || (!interface && !mProfile->implementationAlgebraicCountString().empty())) {
        code += interface ?
                    mProfile->interfaceAlgebraicCountString() :
                    replace(mProfile->implementationAlgebraicCountString(),
                            "[ALGEBRAIC_COUNT]", std::to_string(model->algebraicCount()));
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
                                                                     const std::string &objectString) const
{
    size_t componentSize = 0;
    size_t nameSize = 0;
    size_t unitsSize = 0;

    for (const auto &variable : variables(model)) {
        updateVariableInfoSizes(componentSize, nameSize, unitsSize, variable);
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
        std::string infoElementsCode;

        for (const auto &variable : variables) {
            if (!infoElementsCode.empty()) {
                infoElementsCode += mProfile->arrayElementSeparatorString() + "\n";
            }

            auto variableVariable = variable->variable();

            infoElementsCode += (voiVariable ? "" : mProfile->indentString())
                                + generateVariableInfoEntryCode(variableVariable->name(),
                                                                variableVariable->units()->name(),
                                                                owningComponent(variableVariable)->name());
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
    if (modelHasNlas(model)
        && !mProfile->rootFindingInfoObjectString(modelHasOdes(model), model->hasExternalVariables()).empty()) {
        mCode += newLineIfNeeded()
                 + mProfile->rootFindingInfoObjectString(modelHasOdes(model), model->hasExternalVariables());
    }
}

void Generator::GeneratorImpl::addExternNlaSolveMethodCode(const AnalyserModelPtr &model)
{
    if (modelHasNlas(model)
        && !mProfile->externNlaSolveMethodString().empty()) {
        mCode += newLineIfNeeded()
                 + mProfile->externNlaSolveMethodString();
    }
}

void Generator::GeneratorImpl::addNlaSystemsCode(const AnalyserModelPtr &model)
{
    if (modelHasNlas(model)
        && !mProfile->objectiveFunctionMethodString(modelHasOdes(model), model->hasExternalVariables()).empty()
        && !mProfile->findRootMethodString(modelHasOdes(model), model->hasExternalVariables()).empty()
        && !mProfile->nlaSolveCallString(modelHasOdes(model), model->hasExternalVariables()).empty()) {
        // Note: only states and algebraic variables can be computed through an NLA system. Constants, computed
        //       constants, and external variables cannot, by definition, be computed through an NLA system.

        std::vector<AnalyserEquationPtr> handledNlaEquations;

        for (const auto &equation : model->equations()) {
            if ((equation->type() == AnalyserEquation::Type::NLA)
                && (std::find(handledNlaEquations.begin(), handledNlaEquations.end(), equation) == handledNlaEquations.end())) {
                std::string methodBody;
                auto i = MAX_SIZE_T;
                auto variables = libcellml::variables(equation);

                for (const auto &variable : variables) {
                    auto arrayString = (variable->type() == AnalyserVariable::Type::STATE) ?
                                           mProfile->ratesArrayString() :
                                           mProfile->algebraicArrayString();

                    methodBody += mProfile->indentString()
                                  + arrayString + mProfile->openArrayString() + convertToString(variable->index()) + mProfile->closeArrayString()
                                  + mProfile->equalityString()
                                  + mProfile->uArrayString() + mProfile->openArrayString() + convertToString(++i) + mProfile->closeArrayString()
                                  + mProfile->commandSeparatorString() + "\n";
                }

                methodBody += newLineIfNeeded();

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

                methodBody = {};

                i = MAX_SIZE_T;

                for (const auto &variable : variables) {
                    auto arrayString = (variable->type() == AnalyserVariable::Type::STATE) ?
                                           mProfile->ratesArrayString() :
                                           mProfile->algebraicArrayString();

                    methodBody += mProfile->indentString()
                                  + mProfile->uArrayString() + mProfile->openArrayString() + convertToString(++i) + mProfile->closeArrayString()
                                  + mProfile->equalityString()
                                  + arrayString + mProfile->openArrayString() + convertToString(variable->index()) + mProfile->closeArrayString()
                                  + mProfile->commandSeparatorString() + "\n";
                }

                auto variablesCount = variables.size();

                methodBody += newLineIfNeeded()
                              + mProfile->indentString()
                              + replace(replace(mProfile->nlaSolveCallString(modelHasOdes(model), model->hasExternalVariables()),
                                                "[INDEX]", convertToString(equation->nlaSystemIndex())),
                                        "[SIZE]", convertToString(variablesCount));

                methodBody += newLineIfNeeded();

                i = MAX_SIZE_T;

                for (const auto &variable : variables) {
                    auto arrayString = (variable->type() == AnalyserVariable::Type::STATE) ?
                                           mProfile->ratesArrayString() :
                                           mProfile->algebraicArrayString();

                    methodBody += mProfile->indentString()
                                  + arrayString + mProfile->openArrayString() + convertToString(variable->index()) + mProfile->closeArrayString()
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

    auto ePos = value.find('e');

    if (ePos == std::string::npos) {
        return value + ".0";
    }

    return value.substr(0, ePos) + ".0" + value.substr(ePos);
}

std::string Generator::GeneratorImpl::generateDoubleOrConstantVariableNameCode(const AnalyserModelPtr &model,
                                                                               const VariablePtr &variable) const
{
    if (isCellMLReal(variable->initialValue())) {
        return generateDoubleCode(variable->initialValue());
    }

    auto initialValueVariable = owningComponent(variable)->variable(variable->initialValue());
    auto analyserInitialValueVariable = analyserVariable(model, initialValueVariable);

    return mProfile->constantsArrayString() + mProfile->openArrayString() + convertToString(analyserInitialValueVariable->index()) + mProfile->closeArrayString();
}

std::string Generator::GeneratorImpl::generateVariableNameCode(const AnalyserModelPtr &model,
                                                               const VariablePtr &variable,
                                                               bool state) const
{
    // Generate some code for a variable name, but only if we have a model. If
    // we don't have a model, it means that we are using the generator from the
    // analyser, in which case we just want to return the original name of the
    // variable.

    if (model == nullptr) {
        return variable->name();
    }

    auto analyserVariable = Generator::GeneratorImpl::analyserVariable(model, variable);

    if (analyserVariable->type() == AnalyserVariable::Type::VARIABLE_OF_INTEGRATION) {
        return mProfile->voiString();
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

    return arrayName + mProfile->openArrayString() + convertToString(analyserVariable->index()) + mProfile->closeArrayString();
}

std::string Generator::GeneratorImpl::generateOperatorCode(const AnalyserModelPtr &model, const std::string &op,
                                                           const AnalyserEquationAstPtr &ast) const
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
                                                             const AnalyserEquationAstPtr &ast) const
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
                                                                       const AnalyserEquationAstPtr &ast) const
{
    return function + "(" + generateCode(model, ast->leftChild()) + ")";
}

std::string Generator::GeneratorImpl::generateTwoParameterFunctionCode(const AnalyserModelPtr &model,
                                                                       const std::string &function,
                                                                       const AnalyserEquationAstPtr &ast) const
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
                                                   const AnalyserEquationAstPtr &ast) const
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
    case AnalyserEquationAst::Type::CI:
        code = generateVariableNameCode(model, ast->variable(), ast->parent()->type() != AnalyserEquationAst::Type::DIFF);

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

bool Generator::GeneratorImpl::isToBeComputedAgain(const AnalyserEquationPtr &equation) const
{
    // NLA and algebraic equations that are state/rate-based and external
    // equations are to be computed again (in the computeVariables() method).

    switch (equation->type()) {
    case AnalyserEquation::Type::NLA:
    case AnalyserEquation::Type::ALGEBRAIC:
        return equation->isStateRateBased();
    case AnalyserEquation::Type::EXTERNAL:
        return true;
    default:
        return false;
    }
}

bool Generator::GeneratorImpl::isSomeConstant(const AnalyserEquationPtr &equation,
                                              bool includeComputedConstants) const
{
    auto type = equation->type();

    return (type == AnalyserEquation::Type::TRUE_CONSTANT)
           || (!includeComputedConstants && (type == AnalyserEquation::Type::VARIABLE_BASED_CONSTANT));
}

std::string Generator::GeneratorImpl::generateZeroInitialisationCode(const AnalyserModelPtr &model,
                                                                     const AnalyserVariablePtr &variable) const
{
    return mProfile->indentString()
           + generateVariableNameCode(model, variable->variable(), false)
           + mProfile->equalityString()
           + "0.0"
           + mProfile->commandSeparatorString() + "\n";
}

std::string Generator::GeneratorImpl::generateInitialisationCode(const AnalyserModelPtr &model,
                                                                 const AnalyserVariablePtr &variable) const
{
    auto initialisingVariable = variable->initialisingVariable();
    auto scalingFactor = Generator::GeneratorImpl::scalingFactor(model, initialisingVariable);
    std::string scalingFactorCode;

    if (!areNearlyEqual(scalingFactor, 1.0)) {
        scalingFactorCode = generateDoubleCode(convertToString(scalingFactor)) + mProfile->timesString();
    }

    return mProfile->indentString()
           + generateVariableNameCode(model, variable->variable())
           + mProfile->equalityString()
           + scalingFactorCode + generateDoubleOrConstantVariableNameCode(model, initialisingVariable)
           + mProfile->commandSeparatorString() + "\n";
}

std::string Generator::GeneratorImpl::generateEquationCode(const AnalyserModelPtr &model,
                                                           const AnalyserEquationPtr &equation,
                                                           std::vector<AnalyserEquationPtr> &remainingEquations,
                                                           std::vector<AnalyserEquationPtr> &equationsForDependencies,
                                                           bool includeComputedConstants)
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

        if (!isSomeConstant(equation, includeComputedConstants)) {
            for (const auto &dependency : equation->dependencies()) {
                if ((dependency->type() != AnalyserEquation::Type::ODE)
                    && !isSomeConstant(dependency, includeComputedConstants)
                    && (equationsForDependencies.empty()
                        || isToBeComputedAgain(dependency)
                        || (std::find(equationsForDependencies.begin(), equationsForDependencies.end(), dependency) != equationsForDependencies.end()))) {
                    res += generateEquationCode(model, dependency, remainingEquations, equationsForDependencies, includeComputedConstants);
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
                                 "[INDEX]", convertToString(variable->index()))
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
                                                           std::vector<AnalyserEquationPtr> &remainingEquations)
{
    std::vector<AnalyserEquationPtr> dummyEquationsForComputeVariables;

    return generateEquationCode(model, equation, remainingEquations, dummyEquationsForComputeVariables, true);
}

void Generator::GeneratorImpl::addInterfaceComputeModelMethodsCode(const AnalyserModelPtr &model)
{
    auto interfaceInitialiseVariablesMethodString = mProfile->interfaceInitialiseVariablesMethodString(modelHasOdes(model));
    std::string code;

    if (!interfaceInitialiseVariablesMethodString.empty()) {
        code += interfaceInitialiseVariablesMethodString;
    }

    if (!mProfile->interfaceComputeComputedConstantsMethodString().empty()) {
        code += mProfile->interfaceComputeComputedConstantsMethodString();
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

std::string Generator::GeneratorImpl::generateConstantInitialisationCode(const AnalyserModelPtr &model,
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
            return generateConstantInitialisationCode(model, crtConstant, remainingConstants);
        }
    }

    auto code = generateInitialisationCode(model, *constant);

    remainingConstants.erase(constant);

    return code;
}

void Generator::GeneratorImpl::addImplementationInitialiseVariablesMethodCode(const AnalyserModelPtr &model,
                                                                              std::vector<AnalyserEquationPtr> &remainingEquations)
{
    auto implementationInitialiseVariablesMethodString = mProfile->implementationInitialiseVariablesMethodString(modelHasOdes(model));

    if (!implementationInitialiseVariablesMethodString.empty()) {
        // Initialise our states (after, if needed, initialising the constant on which it depends).

        std::string methodBody;
        auto constants = model->constants();

        for (const auto &state : model->states()) {
            auto initialisingVariable = state->initialisingVariable();
            auto initialValue = initialisingVariable->initialValue();

            if (!isCellMLReal(initialValue)) {
                // The initial value references a constant.

                auto initialisingComponent = owningComponent(initialisingVariable);
                auto constant = std::find_if(constants.begin(), constants.end(),
                                             [=](const AnalyserVariablePtr &av) -> bool {
                                                 return initialisingComponent->variable(initialValue)->hasEquivalentVariable(av->variable());
                                             });

                methodBody += generateConstantInitialisationCode(model, constant, constants);
            }

            methodBody += generateInitialisationCode(model, state);
        }

        // Use an initial guess of zero for rates computed using an NLA system
        // (see the note below).

        for (const auto &state : model->states()) {
            if (state->equation(0)->type() == AnalyserEquation::Type::NLA) {
                methodBody += generateZeroInitialisationCode(model, state);
            }
        }

        // Initialise our (remaining) constants.

        while (!constants.empty()) {
            methodBody += generateConstantInitialisationCode(model, constants.begin(), constants);
        }

        // Initialise our computed constants that are initialised using an equation (e.g., x = 3 rather than x with an
        // initial value of 3).

        auto equations = model->equations();

        for (const auto &equation : equations) {
            if (equation->type() == AnalyserEquation::Type::TRUE_CONSTANT) {
                methodBody += generateEquationCode(model, equation, remainingEquations);
            }
        }

        // Initialise our algebraic variables that have an initial value. Also use an initial guess of zero for
        // algebraic variables computed using an NLA system.
        // Note: a variable which is the only unknown in an equation, but which is not on its own on either the LHS or
        //       RHS of that equation (e.g., x = y+z with x and y known and z unknown) is (currently) to be computed
        //       using an NLA system for which we need an initial guess. We use an initial guess of zero, which is fine
        //       since such an NLA system has only one solution.

        for (const auto &algebraic : model->algebraic()) {
            if (algebraic->initialisingVariable() != nullptr) {
                methodBody += generateInitialisationCode(model, algebraic);
            } else if (algebraic->equation(0)->type() == AnalyserEquation::Type::NLA) {
                methodBody += generateZeroInitialisationCode(model, algebraic);
            }
        }

        mCode += newLineIfNeeded()
                 + replace(implementationInitialiseVariablesMethodString,
                           "[CODE]", generateMethodBodyCode(methodBody));
    }
}

void Generator::GeneratorImpl::addImplementationComputeComputedConstantsMethodCode(const AnalyserModelPtr &model,
                                                                                   std::vector<AnalyserEquationPtr> &remainingEquations)
{
    if (!mProfile->implementationComputeComputedConstantsMethodString().empty()) {
        std::string methodBody;

        for (const auto &equation : model->equations()) {
            if (equation->type() == AnalyserEquation::Type::VARIABLE_BASED_CONSTANT) {
                methodBody += generateEquationCode(model, equation, remainingEquations);
            }
        }

        mCode += newLineIfNeeded()
                 + replace(mProfile->implementationComputeComputedConstantsMethodString(),
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

        for (const auto &equation : model->equations()) {
            // A rate is computed either through an ODE equation or through an
            // NLA equation in case the rate is not on its own on either the LHS
            // or RHS of the equation.

            auto variables = libcellml::variables(equation);

            if ((equation->type() == AnalyserEquation::Type::ODE)
                || ((equation->type() == AnalyserEquation::Type::NLA)
                    && (variables.size() == 1)
                    && (variables[0]->type() == AnalyserVariable::Type::STATE))) {
                methodBody += generateEquationCode(model, equation, remainingEquations);
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
        std::vector<AnalyserEquationPtr> newRemainingEquations {std::begin(equations), std::end(equations)};

        for (const auto &equation : equations) {
            if ((std::find(remainingEquations.begin(), remainingEquations.end(), equation) != remainingEquations.end())
                || isToBeComputedAgain(equation)) {
                methodBody += generateEquationCode(model, equation, newRemainingEquations, remainingEquations, false);
            }
        }

        mCode += newLineIfNeeded()
                 + replace(implementationComputeVariablesMethodString,
                           "[CODE]", generateMethodBodyCode(methodBody));
    }
}

Generator::Generator()
    : mPimpl(new GeneratorImpl())
{
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

bool Generator::trackVariable(const AnalyserModelPtr &model, const VariablePtr &variable)
{
    return mPimpl->trackVariable(model, variable);
}

bool Generator::untrackVariable(const AnalyserModelPtr &model, const VariablePtr &variable)
{
    return mPimpl->untrackVariable(model, variable);
}

bool Generator::trackAllVariables(const AnalyserModelPtr &model)
{
    return mPimpl->trackAllVariables(model);
}

bool Generator::untrackAllVariables(const AnalyserModelPtr &model)
{
    return mPimpl->untrackAllVariables(model);
}

size_t Generator::trackedVariableCount(const AnalyserModelPtr &model)
{
    return mPimpl->trackedVariableCount(model);
}

size_t Generator::untrackedVariableCount(const AnalyserModelPtr &model)
{
    return mPimpl->untrackedVariableCount(model);
}

std::string Generator::interfaceCode(const AnalyserModelPtr &model) const
{
    if ((model == nullptr)
        || (mPimpl->mProfile == nullptr)
        || !model->isValid()
        || !mPimpl->mProfile->hasInterface()) {
        return {};
    }

    // Get ourselves ready.

    mPimpl->reset();

    // Add code for the origin comment.

    mPimpl->addOriginCommentCode();

    // Add code for the header.

    mPimpl->addInterfaceHeaderCode();

    // Add code for the interface of the version of the profile and libCellML.

    mPimpl->addVersionAndLibcellmlVersionCode(true);

    // Add code for the interface of the number of states and variables.

    mPimpl->addStateAndVariableCountCode(model, true);

    // Add code for the variable information related objects.

    mPimpl->addVariableInfoObjectCode(model);

    // Add code for the interface of the information about the variable of integration, states, constants, computed
    // constants, algebraic variables, and external variables.

    mPimpl->addInterfaceVariableInfoCode(model);

    // Add code for the interface to create and delete arrays.

    mPimpl->addInterfaceCreateDeleteArrayMethodsCode(model);

    // Add code for the external variable method type definition.

    mPimpl->addExternalVariableMethodTypeDefinitionCode(model);

    // Add code for the interface to compute the model.

    mPimpl->addInterfaceComputeModelMethodsCode(model);

    return mPimpl->mCode;
}

std::string Generator::implementationCode(const AnalyserModelPtr &model) const
{
    if ((model == nullptr)
        || (mPimpl->mProfile == nullptr)
        || !model->isValid()) {
        return {};
    }

    // Get ourselves ready.

    mPimpl->reset();

    // Add code for the origin comment.

    mPimpl->addOriginCommentCode();

    // Add code for the header.

    mPimpl->addImplementationHeaderCode();

    // Add code for the implementation of the version of the profile and
    // libCellML.

    mPimpl->addVersionAndLibcellmlVersionCode();

    // Add code for the implementation of the number of states and variables.

    mPimpl->addStateAndVariableCountCode(model);

    // Add code for the variable information related objects.

    if (!mPimpl->mProfile->hasInterface()) {
        mPimpl->addVariableInfoObjectCode(model);
    }

    // Add code for the implementation of the information about the variable of integration, states, constants, computed
    // constants, algebraic variables, and external variables.

    mPimpl->addImplementationVariableInfoCode(model);

    // Add code for the arithmetic and trigonometric functions.

    mPimpl->addArithmeticFunctionsCode(model);
    mPimpl->addTrigonometricFunctionsCode(model);

    // Add code for the implementation to create and delete arrays.

    mPimpl->addImplementationCreateDeleteArrayMethodsCode(model);

    // Add code for the NLA solver.

    mPimpl->addRootFindingInfoObjectCode(model);
    mPimpl->addExternNlaSolveMethodCode(model);
    mPimpl->addNlaSystemsCode(model);

    // Add code for the implementation to initialise our variables.

    auto equations = model->equations();
    std::vector<AnalyserEquationPtr> remainingEquations {std::begin(equations), std::end(equations)};

    mPimpl->addImplementationInitialiseVariablesMethodCode(model, remainingEquations);

    // Add code for the implementation to compute our computed constants.

    mPimpl->addImplementationComputeComputedConstantsMethodCode(model, remainingEquations);

    // Add code for the implementation to compute our rates (and any variables
    // on which they depend).

    mPimpl->addImplementationComputeRatesMethodCode(model, remainingEquations);

    // Add code for the implementation to compute our variables.
    // Note: this method computes the remaining variables, i.e. the ones not
    //       needed to compute our rates, but also the variables that depend on
    //       the value of some states/rates and all the external variables.
    //       This method is typically called after having integrated a model,
    //       thus ensuring that variables that rely on the value of some
    //       states/rates are up to date.

    mPimpl->addImplementationComputeVariablesMethodCode(model, remainingEquations);

    return mPimpl->mCode;
}

std::string Generator::equationCode(const AnalyserEquationAstPtr &ast,
                                    const GeneratorProfilePtr &generatorProfile)
{
    GeneratorPtr generator = libcellml::Generator::create();

    if (generatorProfile != nullptr) {
        generator->setProfile(generatorProfile);
    }

    return generator->mPimpl->generateCode(nullptr, ast);
}

std::string Generator::equationCode(const AnalyserEquationAstPtr &ast)
{
    return Generator::equationCode(ast, nullptr);
}

} // namespace libcellml

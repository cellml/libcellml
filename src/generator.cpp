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

#include "analyserequationast_p.h"
#include "generator_p.h"
#include "utilities.h"

#ifdef NAN
#    undef NAN
#endif

namespace libcellml {

bool Generator::GeneratorImpl::retrieveLockedModelAndProfile()
{
    mLockedModel = mGenerator->model();
    mLockedProfile = mGenerator->profile();

    return (mLockedModel != nullptr) && (mLockedProfile != nullptr);
}

void Generator::GeneratorImpl::resetLockedModelAndProfile()
{
    mLockedModel = nullptr;
    mLockedProfile = nullptr;
}

AnalyserVariablePtr Generator::GeneratorImpl::analyserVariable(const VariablePtr &variable) const
{
    // Find and return the analyser variable associated with the given variable.

    AnalyserVariablePtr res;
    auto modelVoi = mLockedModel->voi();

    if ((modelVoi != nullptr)
        && mLockedModel->areEquivalentVariables(variable, modelVoi->variable())) {
        res = modelVoi;
    } else {
        for (const auto &modelState : mLockedModel->states()) {
            if (mLockedModel->areEquivalentVariables(variable, modelState->variable())) {
                res = modelState;

                break;
            }
        }

        if (res == nullptr) {
            for (const auto &modelVariable : mLockedModel->variables()) {
                if (mLockedModel->areEquivalentVariables(variable, modelVariable->variable())) {
                    res = modelVariable;

                    break;
                }
            }
        }
    }

    return res;
}

double Generator::GeneratorImpl::scalingFactor(const VariablePtr &variable) const
{
    // Return the scaling factor for the given variable.

    return Units::scalingFactor(variable->units(), analyserVariable(variable)->variable()->units());
}

bool Generator::GeneratorImpl::isRelationalOperator(const AnalyserEquationAstPtr &ast) const
{
    return ((ast->type() == AnalyserEquationAst::Type::EQ)
            && mLockedProfile->hasEqOperator())
           || ((ast->type() == AnalyserEquationAst::Type::NEQ)
               && mLockedProfile->hasNeqOperator())
           || ((ast->type() == AnalyserEquationAst::Type::LT)
               && mLockedProfile->hasLtOperator())
           || ((ast->type() == AnalyserEquationAst::Type::LEQ)
               && mLockedProfile->hasLeqOperator())
           || ((ast->type() == AnalyserEquationAst::Type::GT)
               && mLockedProfile->hasGtOperator())
           || ((ast->type() == AnalyserEquationAst::Type::GEQ)
               && mLockedProfile->hasGeqOperator());
}

bool Generator::GeneratorImpl::isAndOperator(const AnalyserEquationAstPtr &ast) const
{
    return (ast->type() == AnalyserEquationAst::Type::AND)
           && mLockedProfile->hasAndOperator();
}

bool Generator::GeneratorImpl::isOrOperator(const AnalyserEquationAstPtr &ast) const
{
    return (ast->type() == AnalyserEquationAst::Type::OR)
           && mLockedProfile->hasOrOperator();
}

bool Generator::GeneratorImpl::isXorOperator(const AnalyserEquationAstPtr &ast) const
{
    return (ast->type() == AnalyserEquationAst::Type::XOR)
           && mLockedProfile->hasXorOperator();
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
           && mLockedProfile->hasPowerOperator();
}

bool Generator::GeneratorImpl::isRootOperator(const AnalyserEquationAstPtr &ast) const
{
    return (ast->type() == AnalyserEquationAst::Type::ROOT)
           && mLockedProfile->hasPowerOperator();
}

bool Generator::GeneratorImpl::isPiecewiseStatement(const AnalyserEquationAstPtr &ast) const
{
    return (ast->type() == AnalyserEquationAst::Type::PIECEWISE)
           && mLockedProfile->hasConditionalOperator();
}

void Generator::GeneratorImpl::updateVariableInfoSizes(size_t &componentSize,
                                                       size_t &nameSize,
                                                       size_t &unitsSize,
                                                       const AnalyserVariablePtr &variable) const
{
    auto variableComponentSize = owningComponent(variable->variable())->name().length() + 1;
    auto variableNameSize = variable->variable()->name().length() + 1;
    auto variableUnitsSize = variable->variable()->units()->name().length() + 1;
    // Note: +1 to account for the end of string termination.

    componentSize = (componentSize > variableComponentSize) ? componentSize : variableComponentSize;
    nameSize = (nameSize > variableNameSize) ? nameSize : variableNameSize;
    unitsSize = (unitsSize > variableUnitsSize) ? unitsSize : variableUnitsSize;
}

bool Generator::GeneratorImpl::modifiedProfile() const
{
    // Whether the profile requires an interface to be generated.

    static const std::string TRUE_VALUE = "true";
    static const std::string FALSE_VALUE = "false";

    auto profileContents = mLockedProfile->hasInterface() ?
                               TRUE_VALUE :
                               FALSE_VALUE;

    // Assignment.

    profileContents += mLockedProfile->assignmentString();

    // Relational and logical operators.

    profileContents += mLockedProfile->eqString()
                       + mLockedProfile->neqString()
                       + mLockedProfile->ltString()
                       + mLockedProfile->leqString()
                       + mLockedProfile->gtString()
                       + mLockedProfile->geqString()
                       + mLockedProfile->andString()
                       + mLockedProfile->orString()
                       + mLockedProfile->xorString()
                       + mLockedProfile->notString();

    profileContents += (mLockedProfile->hasEqOperator() ?
                            TRUE_VALUE :
                            FALSE_VALUE)
                       + (mLockedProfile->hasNeqOperator() ?
                              TRUE_VALUE :
                              FALSE_VALUE)
                       + (mLockedProfile->hasLtOperator() ?
                              TRUE_VALUE :
                              FALSE_VALUE)
                       + (mLockedProfile->hasLeqOperator() ?
                              TRUE_VALUE :
                              FALSE_VALUE)
                       + (mLockedProfile->hasGtOperator() ?
                              TRUE_VALUE :
                              FALSE_VALUE)
                       + (mLockedProfile->hasGeqOperator() ?
                              TRUE_VALUE :
                              FALSE_VALUE)
                       + (mLockedProfile->hasAndOperator() ?
                              TRUE_VALUE :
                              FALSE_VALUE)
                       + (mLockedProfile->hasOrOperator() ?
                              TRUE_VALUE :
                              FALSE_VALUE)
                       + (mLockedProfile->hasXorOperator() ?
                              TRUE_VALUE :
                              FALSE_VALUE)
                       + (mLockedProfile->hasNotOperator() ?
                              TRUE_VALUE :
                              FALSE_VALUE);

    // Arithmetic operators.

    profileContents += mLockedProfile->plusString()
                       + mLockedProfile->minusString()
                       + mLockedProfile->timesString()
                       + mLockedProfile->divideString()
                       + mLockedProfile->powerString()
                       + mLockedProfile->squareRootString()
                       + mLockedProfile->squareString()
                       + mLockedProfile->absoluteValueString()
                       + mLockedProfile->exponentialString()
                       + mLockedProfile->naturalLogarithmString()
                       + mLockedProfile->commonLogarithmString()
                       + mLockedProfile->ceilingString()
                       + mLockedProfile->floorString()
                       + mLockedProfile->minString()
                       + mLockedProfile->maxString()
                       + mLockedProfile->remString();

    profileContents += mLockedProfile->hasPowerOperator() ?
                           TRUE_VALUE :
                           FALSE_VALUE;

    // Trigonometric operators.

    profileContents += mLockedProfile->sinString()
                       + mLockedProfile->cosString()
                       + mLockedProfile->tanString()
                       + mLockedProfile->secString()
                       + mLockedProfile->cscString()
                       + mLockedProfile->cotString()
                       + mLockedProfile->sinhString()
                       + mLockedProfile->coshString()
                       + mLockedProfile->tanhString()
                       + mLockedProfile->sechString()
                       + mLockedProfile->cschString()
                       + mLockedProfile->cothString()
                       + mLockedProfile->asinString()
                       + mLockedProfile->acosString()
                       + mLockedProfile->atanString()
                       + mLockedProfile->asecString()
                       + mLockedProfile->acscString()
                       + mLockedProfile->acotString()
                       + mLockedProfile->asinhString()
                       + mLockedProfile->acoshString()
                       + mLockedProfile->atanhString()
                       + mLockedProfile->asechString()
                       + mLockedProfile->acschString()
                       + mLockedProfile->acothString();

    // Piecewise statement.

    profileContents += mLockedProfile->conditionalOperatorIfString()
                       + mLockedProfile->conditionalOperatorElseString()
                       + mLockedProfile->piecewiseIfString()
                       + mLockedProfile->piecewiseElseString();

    profileContents += mLockedProfile->hasConditionalOperator() ?
                           TRUE_VALUE :
                           FALSE_VALUE;

    // Constants.

    profileContents += mLockedProfile->trueString()
                       + mLockedProfile->falseString()
                       + mLockedProfile->eString()
                       + mLockedProfile->piString()
                       + mLockedProfile->infString()
                       + mLockedProfile->nanString();

    // Arithmetic functions.

    profileContents += mLockedProfile->eqFunctionString()
                       + mLockedProfile->neqFunctionString()
                       + mLockedProfile->ltFunctionString()
                       + mLockedProfile->leqFunctionString()
                       + mLockedProfile->gtFunctionString()
                       + mLockedProfile->geqFunctionString()
                       + mLockedProfile->andFunctionString()
                       + mLockedProfile->orFunctionString()
                       + mLockedProfile->xorFunctionString()
                       + mLockedProfile->notFunctionString()
                       + mLockedProfile->minFunctionString()
                       + mLockedProfile->maxFunctionString();

    // Trigonometric functions.

    profileContents += mLockedProfile->secFunctionString()
                       + mLockedProfile->cscFunctionString()
                       + mLockedProfile->cotFunctionString()
                       + mLockedProfile->sechFunctionString()
                       + mLockedProfile->cschFunctionString()
                       + mLockedProfile->cothFunctionString()
                       + mLockedProfile->asecFunctionString()
                       + mLockedProfile->acscFunctionString()
                       + mLockedProfile->acotFunctionString()
                       + mLockedProfile->asechFunctionString()
                       + mLockedProfile->acschFunctionString()
                       + mLockedProfile->acothFunctionString();

    // Miscellaneous.
    // Note: we do NOT include interfaceFileNameString() since it may be the
    //       only thing that someone might change, so that the generated file
    //       works with the file name it is to be given.

    profileContents += mLockedProfile->commentString()
                       + mLockedProfile->originCommentString();

    profileContents += mLockedProfile->interfaceHeaderString()
                       + mLockedProfile->implementationHeaderString();

    profileContents += mLockedProfile->interfaceVersionString()
                       + mLockedProfile->implementationVersionString();

    profileContents += mLockedProfile->interfaceLibcellmlVersionString()
                       + mLockedProfile->implementationLibcellmlVersionString();

    profileContents += mLockedProfile->interfaceStateCountString()
                       + mLockedProfile->implementationStateCountString();

    profileContents += mLockedProfile->interfaceVariableCountString()
                       + mLockedProfile->implementationVariableCountString();

    profileContents += mLockedProfile->variableTypeObjectInAlgebraicModelString();
    profileContents += mLockedProfile->variableTypeObjectExternalTypeInAlgebraicModelString();
    profileContents += mLockedProfile->variableTypeObjectInDifferentialModelString();
    profileContents += mLockedProfile->variableTypeObjectExternalTypeInDifferentialModelString();

    profileContents += mLockedProfile->variableOfIntegrationVariableTypeString()
                       + mLockedProfile->stateVariableTypeString()
                       + mLockedProfile->constantVariableTypeString()
                       + mLockedProfile->computedConstantVariableTypeString()
                       + mLockedProfile->algebraicVariableTypeString()
                       + mLockedProfile->externalVariableTypeString();

    profileContents += mLockedProfile->variableInfoObjectString();

    profileContents += mLockedProfile->interfaceVoiInfoString()
                       + mLockedProfile->implementationVoiInfoString();

    profileContents += mLockedProfile->interfaceStateInfoString()
                       + mLockedProfile->implementationStateInfoString();

    profileContents += mLockedProfile->interfaceVariableInfoString()
                       + mLockedProfile->implementationVariableInfoString();

    profileContents += mLockedProfile->variableInfoEntryString();

    profileContents += mLockedProfile->voiString();

    profileContents += mLockedProfile->statesArrayString()
                       + mLockedProfile->ratesArrayString()
                       + mLockedProfile->variablesArrayString();

    profileContents += mLockedProfile->externalVariableMethodTypeDefinitionInAlgebraicModelString()
                       + mLockedProfile->externalVariableMethodTypeDefinitionInDifferentialModelString()
                       + mLockedProfile->externalVariableMethodParameterString()
                       + mLockedProfile->externalVariableMethodCallInAlgebraicModelString()
                       + mLockedProfile->externalVariableMethodCallInDifferentialModelString();

    profileContents += mLockedProfile->interfaceCreateStatesArrayMethodString()
                       + mLockedProfile->implementationCreateStatesArrayMethodString();

    profileContents += mLockedProfile->interfaceCreateVariablesArrayMethodString()
                       + mLockedProfile->implementationCreateVariablesArrayMethodString();

    profileContents += mLockedProfile->interfaceDeleteArrayMethodString()
                       + mLockedProfile->implementationDeleteArrayMethodString();

    profileContents += mLockedProfile->interfaceInitialiseConstantsMethodString()
                       + mLockedProfile->implementationInitialiseConstantsMethodString();

    profileContents += mLockedProfile->interfaceInitialiseStatesAndConstantsMethodString()
                       + mLockedProfile->implementationInitialiseStatesAndConstantsMethodString();

    profileContents += mLockedProfile->interfaceComputeComputedConstantsMethodString()
                       + mLockedProfile->implementationComputeComputedConstantsMethodString();

    profileContents += mLockedProfile->interfaceComputeRatesMethodString()
                       + mLockedProfile->implementationComputeRatesMethodString();

    profileContents += mLockedProfile->interfaceComputeVariablesMethodInAlgebraicModelString()
                       + mLockedProfile->implementationComputeVariablesMethodInAlgebraicModelString();

    profileContents += mLockedProfile->interfaceComputeVariablesMethodInDifferentialModelString()
                       + mLockedProfile->implementationComputeVariablesMethodInDifferentialModelString();

    profileContents += mLockedProfile->emptyMethodString();

    profileContents += mLockedProfile->indentString();

    profileContents += mLockedProfile->openArrayInitialiserString()
                       + mLockedProfile->closeArrayInitialiserString();

    profileContents += mLockedProfile->openArrayString()
                       + mLockedProfile->closeArrayString();

    profileContents += mLockedProfile->arrayElementSeparatorString();

    profileContents += mLockedProfile->stringDelimiterString();

    profileContents += mLockedProfile->commandSeparatorString();

    // Compute and check the SHA-1 value of our profile contents.

    return (mLockedProfile->profile() == GeneratorProfile::Profile::C) ?
               sha1(profileContents) != "f5ea88b858589944f8ec0efa0d0d2d95858362c7" :
               sha1(profileContents) != "c5d72615c86e26c21a45ebf4d13261c3c68d7332";
}

void Generator::GeneratorImpl::addOriginCommentCode()
{
    if (!mLockedProfile->commentString().empty()
        && !mLockedProfile->originCommentString().empty()) {
        std::string profileInformation = modifiedProfile() ?
                                             "a modified " :
                                             "the ";

        profileInformation += (mLockedProfile->profile() == GeneratorProfile::Profile::C) ?
                                  "C" :
                                  "Python";
        profileInformation += " profile of";

        mCode += replace(mLockedProfile->commentString(),
                         "[CODE]", replace(replace(mLockedProfile->originCommentString(), "[PROFILE_INFORMATION]", profileInformation), "[LIBCELLML_VERSION]", versionString()));
    }
}

void Generator::GeneratorImpl::addInterfaceHeaderCode()
{
    if (!mLockedProfile->interfaceHeaderString().empty()) {
        if (!mCode.empty()) {
            mCode += "\n";
        }

        mCode += mLockedProfile->interfaceHeaderString();
    }
}

void Generator::GeneratorImpl::addImplementationHeaderCode()
{
    bool hasInterfaceFileName = mLockedProfile->implementationHeaderString().empty() ?
                                    false :
                                    (mLockedProfile->implementationHeaderString().find("[INTERFACE_FILE_NAME]") != std::string::npos);

    if (!mLockedProfile->implementationHeaderString().empty()
        && ((hasInterfaceFileName && !mLockedProfile->interfaceFileNameString().empty())
            || !hasInterfaceFileName)) {
        if (!mCode.empty()) {
            mCode += "\n";
        }

        mCode += replace(mLockedProfile->implementationHeaderString(),
                         "[INTERFACE_FILE_NAME]", mLockedProfile->interfaceFileNameString());
    }
}

void Generator::GeneratorImpl::addVersionAndLibcellmlVersionCode(bool interface)
{
    std::string versionAndLibcellmlCode;

    if ((interface && !mLockedProfile->interfaceVersionString().empty())
        || (!interface && !mLockedProfile->implementationVersionString().empty())) {
        if (interface) {
            versionAndLibcellmlCode += mLockedProfile->interfaceVersionString();
        } else {
            if (modifiedProfile()) {
                std::regex regEx("([0-9]+\\.[0-9]+\\.[0-9]+)");

                versionAndLibcellmlCode += std::regex_replace(mLockedProfile->implementationVersionString(), regEx, "$1.post0");
            } else {
                versionAndLibcellmlCode += mLockedProfile->implementationVersionString();
            }
        }
    }

    if ((interface && !mLockedProfile->interfaceLibcellmlVersionString().empty())
        || (!interface && !mLockedProfile->implementationLibcellmlVersionString().empty())) {
        versionAndLibcellmlCode += interface ?
                                       mLockedProfile->interfaceLibcellmlVersionString() :
                                       replace(mLockedProfile->implementationLibcellmlVersionString(),
                                               "[LIBCELLML_VERSION]", versionString());
    }

    if (!versionAndLibcellmlCode.empty()) {
        mCode += "\n";
    }

    mCode += versionAndLibcellmlCode;
}

void Generator::GeneratorImpl::addStateAndVariableCountCode(bool interface)
{
    std::string stateAndVariableCountCode;

    if ((mLockedModel->type() == AnalyserModel::Type::ODE)
        && ((interface && !mLockedProfile->interfaceStateCountString().empty())
            || (!interface && !mLockedProfile->implementationStateCountString().empty()))) {
        stateAndVariableCountCode += interface ?
                                         mLockedProfile->interfaceStateCountString() :
                                         replace(mLockedProfile->implementationStateCountString(),
                                                 "[STATE_COUNT]", std::to_string(mLockedModel->stateCount()));
    }

    if ((interface && !mLockedProfile->interfaceVariableCountString().empty())
        || (!interface && !mLockedProfile->implementationVariableCountString().empty())) {
        stateAndVariableCountCode += interface ?
                                         mLockedProfile->interfaceVariableCountString() :
                                         replace(mLockedProfile->implementationVariableCountString(),
                                                 "[VARIABLE_COUNT]", std::to_string(mLockedModel->variableCount()));
    }

    if (!stateAndVariableCountCode.empty()) {
        mCode += "\n";
    }

    mCode += stateAndVariableCountCode;
}

void Generator::GeneratorImpl::addVariableTypeObjectCode()
{
    if ((((mLockedModel->type() == AnalyserModel::Type::ALGEBRAIC)
          && !mLockedProfile->variableTypeObjectInAlgebraicModelString().empty())
         || ((mLockedModel->type() == AnalyserModel::Type::ODE)
             && !mLockedProfile->variableTypeObjectInDifferentialModelString().empty()))
        && ((mLockedModel->hasExternalVariables()
             && (((mLockedModel->type() == AnalyserModel::Type::ALGEBRAIC)
                  && !mLockedProfile->variableTypeObjectExternalTypeInAlgebraicModelString().empty())
                 || ((mLockedModel->type() == AnalyserModel::Type::ODE)
                     && !mLockedProfile->variableTypeObjectExternalTypeInDifferentialModelString().empty())))
            || !mLockedModel->hasExternalVariables())) {
        if (!mCode.empty()) {
            mCode += "\n";
        }

        mCode += replace((mLockedModel->type() == AnalyserModel::Type::ALGEBRAIC) ?
                             mLockedProfile->variableTypeObjectInAlgebraicModelString() :
                             mLockedProfile->variableTypeObjectInDifferentialModelString(),
                         "[OPTIONAL_TYPE]", mLockedModel->hasExternalVariables() ? (mLockedModel->type() == AnalyserModel::Type::ALGEBRAIC) ? mLockedProfile->variableTypeObjectExternalTypeInAlgebraicModelString() : mLockedProfile->variableTypeObjectExternalTypeInDifferentialModelString() : "");
    }
}

std::string Generator::GeneratorImpl::generateVariableInfoObjectCode(const std::string &objectString) const
{
    size_t componentSize = 0;
    size_t nameSize = 0;
    size_t unitsSize = 0;

    if (mLockedModel->type() == AnalyserModel::Type::ODE) {
        updateVariableInfoSizes(componentSize, nameSize, unitsSize, mLockedModel->voi());

        for (const auto &state : mLockedModel->states()) {
            updateVariableInfoSizes(componentSize, nameSize, unitsSize, state);
        }
    }

    for (const auto &variable : mLockedModel->variables()) {
        updateVariableInfoSizes(componentSize, nameSize, unitsSize, variable);
    }

    return replace(replace(replace(objectString,
                                   "[COMPONENT_SIZE]", std::to_string(componentSize)),
                           "[NAME_SIZE]", std::to_string(nameSize)),
                   "[UNITS_SIZE]", std::to_string(unitsSize));
}

void Generator::GeneratorImpl::addVariableInfoObjectCode()
{
    if (!mLockedProfile->variableInfoObjectString().empty()) {
        if (!mCode.empty()) {
            mCode += "\n";
        }

        mCode += generateVariableInfoObjectCode(mLockedProfile->variableInfoObjectString());
    }
}

std::string Generator::GeneratorImpl::generateVariableInfoEntryCode(const std::string &name,
                                                                    const std::string &units,
                                                                    const std::string &component,
                                                                    const std::string &type) const
{
    return replace(replace(replace(replace(mLockedProfile->variableInfoEntryString(),
                                           "[NAME]", name),
                                   "[UNITS]", units),
                           "[COMPONENT]", component),
                   "[TYPE]", type);
}

void Generator::GeneratorImpl::addInterfaceVoiStateAndVariableInfoCode()
{
    std::string interfaceVoiStateAndVariableInfoCode;

    if ((mLockedModel->type() == AnalyserModel::Type::ODE)
        && !mLockedProfile->interfaceVoiInfoString().empty()) {
        interfaceVoiStateAndVariableInfoCode += mLockedProfile->interfaceVoiInfoString();
    }

    if ((mLockedModel->type() == AnalyserModel::Type::ODE)
        && !mLockedProfile->interfaceStateInfoString().empty()) {
        interfaceVoiStateAndVariableInfoCode += mLockedProfile->interfaceStateInfoString();
    }

    if (!mLockedProfile->interfaceVariableInfoString().empty()) {
        interfaceVoiStateAndVariableInfoCode += mLockedProfile->interfaceVariableInfoString();
    }

    if (!interfaceVoiStateAndVariableInfoCode.empty()) {
        mCode += "\n";
    }

    mCode += interfaceVoiStateAndVariableInfoCode;
}

void Generator::GeneratorImpl::addImplementationVoiInfoCode()
{
    if ((mLockedModel->type() == AnalyserModel::Type::ODE)
        && !mLockedProfile->implementationVoiInfoString().empty()
        && !mLockedProfile->variableInfoEntryString().empty()
        && !mLockedProfile->variableOfIntegrationVariableTypeString().empty()) {
        if (!mCode.empty()) {
            mCode += "\n";
        }

        auto name = mLockedModel->voi()->variable()->name();
        auto units = mLockedModel->voi()->variable()->units()->name();
        auto component = owningComponent(mLockedModel->voi()->variable())->name();
        auto type = mLockedProfile->variableOfIntegrationVariableTypeString();

        mCode += replace(mLockedProfile->implementationVoiInfoString(),
                         "[CODE]", generateVariableInfoEntryCode(name, units, component, type));
    }
}

void Generator::GeneratorImpl::addImplementationStateInfoCode()
{
    if ((mLockedModel->type() == AnalyserModel::Type::ODE)
        && !mLockedProfile->implementationStateInfoString().empty()
        && !mLockedProfile->variableInfoEntryString().empty()
        && !mLockedProfile->stateVariableTypeString().empty()
        && !mLockedProfile->arrayElementSeparatorString().empty()) {
        if (!mCode.empty()) {
            mCode += "\n";
        }

        std::string infoElementsCode;
        auto type = mLockedProfile->stateVariableTypeString();

        for (const auto &state : mLockedModel->states()) {
            if (!infoElementsCode.empty()) {
                infoElementsCode += mLockedProfile->arrayElementSeparatorString() + "\n";
            }

            infoElementsCode += mLockedProfile->indentString()
                                + generateVariableInfoEntryCode(state->variable()->name(),
                                                                state->variable()->units()->name(),
                                                                owningComponent(state->variable())->name(),
                                                                type);
        }

        if (!infoElementsCode.empty()) {
            infoElementsCode += "\n";
        }

        mCode += replace(mLockedProfile->implementationStateInfoString(),
                         "[CODE]", infoElementsCode);
    }
}

void Generator::GeneratorImpl::addImplementationVariableInfoCode()
{
    if (!mLockedProfile->implementationVariableInfoString().empty()
        && !mLockedProfile->variableInfoEntryString().empty()
        && !mLockedProfile->arrayElementSeparatorString().empty()
        && !mLockedProfile->variableOfIntegrationVariableTypeString().empty()
        && !mLockedProfile->stateVariableTypeString().empty()
        && !mLockedProfile->constantVariableTypeString().empty()
        && !mLockedProfile->computedConstantVariableTypeString().empty()
        && !mLockedProfile->algebraicVariableTypeString().empty()
        && !mLockedProfile->externalVariableTypeString().empty()) {
        if (!mCode.empty()) {
            mCode += "\n";
        }

        std::string infoElementsCode;

        for (const auto &variable : mLockedModel->variables()) {
            if (!infoElementsCode.empty()) {
                infoElementsCode += mLockedProfile->arrayElementSeparatorString() + "\n";
            }

            std::string variableType;

            if (variable->type() == AnalyserVariable::Type::CONSTANT) {
                variableType = mLockedProfile->constantVariableTypeString();
            } else if (variable->type() == AnalyserVariable::Type::COMPUTED_CONSTANT) {
                variableType = mLockedProfile->computedConstantVariableTypeString();
            } else if (variable->type() == AnalyserVariable::Type::ALGEBRAIC) {
                variableType = mLockedProfile->algebraicVariableTypeString();
            } else if (variable->type() == AnalyserVariable::Type::EXTERNAL) {
                variableType = mLockedProfile->externalVariableTypeString();
            }

            infoElementsCode += mLockedProfile->indentString()
                                + replace(replace(replace(replace(mLockedProfile->variableInfoEntryString(),
                                                                  "[NAME]", variable->variable()->name()),
                                                          "[UNITS]", variable->variable()->units()->name()),
                                                  "[COMPONENT]", owningComponent(variable->variable())->name()),
                                          "[TYPE]", variableType);
        }

        if (!infoElementsCode.empty()) {
            infoElementsCode += "\n";
        }

        mCode += replace(mLockedProfile->implementationVariableInfoString(),
                         "[CODE]", infoElementsCode);
    }
}

void Generator::GeneratorImpl::addArithmeticFunctionsCode()
{
    if (mLockedModel->needEqFunction() && !mLockedProfile->hasEqOperator()
        && !mLockedProfile->eqFunctionString().empty()) {
        if (!mCode.empty()) {
            mCode += "\n";
        }

        mCode += mLockedProfile->eqFunctionString();
    }

    if (mLockedModel->needNeqFunction() && !mLockedProfile->hasNeqOperator()
        && !mLockedProfile->neqFunctionString().empty()) {
        if (!mCode.empty()) {
            mCode += "\n";
        }

        mCode += mLockedProfile->neqFunctionString();
    }

    if (mLockedModel->needLtFunction() && !mLockedProfile->hasLtOperator()
        && !mLockedProfile->ltFunctionString().empty()) {
        if (!mCode.empty()) {
            mCode += "\n";
        }

        mCode += mLockedProfile->ltFunctionString();
    }

    if (mLockedModel->needLeqFunction() && !mLockedProfile->hasLeqOperator()
        && !mLockedProfile->leqFunctionString().empty()) {
        if (!mCode.empty()) {
            mCode += "\n";
        }

        mCode += mLockedProfile->leqFunctionString();
    }

    if (mLockedModel->needGtFunction() && !mLockedProfile->hasGtOperator()
        && !mLockedProfile->gtFunctionString().empty()) {
        if (!mCode.empty()) {
            mCode += "\n";
        }

        mCode += mLockedProfile->gtFunctionString();
    }

    if (mLockedModel->needGeqFunction() && !mLockedProfile->hasGeqOperator()
        && !mLockedProfile->geqFunctionString().empty()) {
        if (!mCode.empty()) {
            mCode += "\n";
        }

        mCode += mLockedProfile->geqFunctionString();
    }

    if (mLockedModel->needAndFunction() && !mLockedProfile->hasAndOperator()
        && !mLockedProfile->andFunctionString().empty()) {
        if (!mCode.empty()) {
            mCode += "\n";
        }

        mCode += mLockedProfile->andFunctionString();
    }

    if (mLockedModel->needOrFunction() && !mLockedProfile->hasOrOperator()
        && !mLockedProfile->orFunctionString().empty()) {
        if (!mCode.empty()) {
            mCode += "\n";
        }

        mCode += mLockedProfile->orFunctionString();
    }

    if (mLockedModel->needXorFunction() && !mLockedProfile->hasXorOperator()
        && !mLockedProfile->xorFunctionString().empty()) {
        if (!mCode.empty()) {
            mCode += "\n";
        }

        mCode += mLockedProfile->xorFunctionString();
    }

    if (mLockedModel->needNotFunction() && !mLockedProfile->hasNotOperator()
        && !mLockedProfile->notFunctionString().empty()) {
        if (!mCode.empty()) {
            mCode += "\n";
        }

        mCode += mLockedProfile->notFunctionString();
    }

    if (mLockedModel->needMinFunction()
        && !mLockedProfile->minFunctionString().empty()) {
        if (!mCode.empty()) {
            mCode += "\n";
        }

        mCode += mLockedProfile->minFunctionString();
    }

    if (mLockedModel->needMaxFunction()
        && !mLockedProfile->maxFunctionString().empty()) {
        if (!mCode.empty()) {
            mCode += "\n";
        }

        mCode += mLockedProfile->maxFunctionString();
    }
}

void Generator::GeneratorImpl::addTrigonometricFunctionsCode()
{
    if (mLockedModel->needSecFunction()
        && !mLockedProfile->secFunctionString().empty()) {
        if (!mCode.empty()) {
            mCode += "\n";
        }

        mCode += mLockedProfile->secFunctionString();
    }

    if (mLockedModel->needCscFunction()
        && !mLockedProfile->cscFunctionString().empty()) {
        if (!mCode.empty()) {
            mCode += "\n";
        }

        mCode += mLockedProfile->cscFunctionString();
    }

    if (mLockedModel->needCotFunction()
        && !mLockedProfile->cotFunctionString().empty()) {
        if (!mCode.empty()) {
            mCode += "\n";
        }

        mCode += mLockedProfile->cotFunctionString();
    }

    if (mLockedModel->needSechFunction()
        && !mLockedProfile->sechFunctionString().empty()) {
        if (!mCode.empty()) {
            mCode += "\n";
        }

        mCode += mLockedProfile->sechFunctionString();
    }

    if (mLockedModel->needCschFunction()
        && !mLockedProfile->cschFunctionString().empty()) {
        if (!mCode.empty()) {
            mCode += "\n";
        }

        mCode += mLockedProfile->cschFunctionString();
    }

    if (mLockedModel->needCothFunction()
        && !mLockedProfile->cothFunctionString().empty()) {
        if (!mCode.empty()) {
            mCode += "\n";
        }

        mCode += mLockedProfile->cothFunctionString();
    }

    if (mLockedModel->needAsecFunction()
        && !mLockedProfile->asecFunctionString().empty()) {
        if (!mCode.empty()) {
            mCode += "\n";
        }

        mCode += mLockedProfile->asecFunctionString();
    }

    if (mLockedModel->needAcscFunction()
        && !mLockedProfile->acscFunctionString().empty()) {
        if (!mCode.empty()) {
            mCode += "\n";
        }

        mCode += mLockedProfile->acscFunctionString();
    }

    if (mLockedModel->needAcotFunction()
        && !mLockedProfile->acotFunctionString().empty()) {
        if (!mCode.empty()) {
            mCode += "\n";
        }

        mCode += mLockedProfile->acotFunctionString();
    }

    if (mLockedModel->needAsechFunction()
        && !mLockedProfile->asechFunctionString().empty()) {
        if (!mCode.empty()) {
            mCode += "\n";
        }

        mCode += mLockedProfile->asechFunctionString();
    }

    if (mLockedModel->needAcschFunction()
        && !mLockedProfile->acschFunctionString().empty()) {
        if (!mCode.empty()) {
            mCode += "\n";
        }

        mCode += mLockedProfile->acschFunctionString();
    }

    if (mLockedModel->needAcothFunction()
        && !mLockedProfile->acothFunctionString().empty()) {
        if (!mCode.empty()) {
            mCode += "\n";
        }

        mCode += mLockedProfile->acothFunctionString();
    }
}

void Generator::GeneratorImpl::addInterfaceCreateDeleteArrayMethodsCode()
{
    std::string interfaceCreateDeleteArraysCode;

    if ((mLockedModel->type() == AnalyserModel::Type::ODE)
        && !mLockedProfile->interfaceCreateStatesArrayMethodString().empty()) {
        interfaceCreateDeleteArraysCode += mLockedProfile->interfaceCreateStatesArrayMethodString();
    }

    if (!mLockedProfile->interfaceCreateVariablesArrayMethodString().empty()) {
        interfaceCreateDeleteArraysCode += mLockedProfile->interfaceCreateVariablesArrayMethodString();
    }

    if (!mLockedProfile->interfaceDeleteArrayMethodString().empty()) {
        interfaceCreateDeleteArraysCode += mLockedProfile->interfaceDeleteArrayMethodString();
    }

    if (!interfaceCreateDeleteArraysCode.empty()) {
        mCode += "\n";
    }

    mCode += interfaceCreateDeleteArraysCode;
}

void Generator::GeneratorImpl::addExternalVariableMethodTypeDefinitionCode()
{
    if (mLockedModel->hasExternalVariables()) {
        std::string externalVariableMethodTypeDefinitionCode;

        if (((mLockedModel->type() == AnalyserModel::Type::ALGEBRAIC)
             && !mLockedProfile->externalVariableMethodTypeDefinitionInAlgebraicModelString().empty())
            || ((mLockedModel->type() == AnalyserModel::Type::ODE)
                && !mLockedProfile->externalVariableMethodTypeDefinitionInDifferentialModelString().empty())) {
            externalVariableMethodTypeDefinitionCode += (mLockedModel->type() == AnalyserModel::Type::ALGEBRAIC) ?
                                                            mLockedProfile->externalVariableMethodTypeDefinitionInAlgebraicModelString() :
                                                            mLockedProfile->externalVariableMethodTypeDefinitionInDifferentialModelString();
        }

        if (!externalVariableMethodTypeDefinitionCode.empty()) {
            mCode += "\n";
        }

        mCode += externalVariableMethodTypeDefinitionCode;
    }
}

void Generator::GeneratorImpl::addImplementationCreateStatesArrayMethodCode()
{
    if ((mLockedModel->type() == AnalyserModel::Type::ODE)
        && !mLockedProfile->implementationCreateStatesArrayMethodString().empty()) {
        if (!mCode.empty()) {
            mCode += "\n";
        }

        mCode += mLockedProfile->implementationCreateStatesArrayMethodString();
    }
}

void Generator::GeneratorImpl::addImplementationCreateVariablesArrayMethodCode()
{
    if (!mLockedProfile->implementationCreateVariablesArrayMethodString().empty()) {
        if (!mCode.empty()) {
            mCode += "\n";
        }

        mCode += mLockedProfile->implementationCreateVariablesArrayMethodString();
    }
}

void Generator::GeneratorImpl::addImplementationDeleteArrayMethodCode()
{
    if (!mLockedProfile->implementationDeleteArrayMethodString().empty()) {
        if (!mCode.empty()) {
            mCode += "\n";
        }

        mCode += mLockedProfile->implementationDeleteArrayMethodString();
    }
}

std::string Generator::GeneratorImpl::generateMethodBodyCode(const std::string &methodBody) const
{
    return methodBody.empty() ?
               mLockedProfile->emptyMethodString().empty() ?
               "" :
               mLockedProfile->indentString() + mLockedProfile->emptyMethodString() :
               methodBody;
}

std::string Generator::GeneratorImpl::generateDoubleCode(const std::string &value) const
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

std::string Generator::GeneratorImpl::generateDoubleOrConstantVariableNameCode(const VariablePtr &variable) const
{
    if (isCellMLReal(variable->initialValue())) {
        return generateDoubleCode(variable->initialValue());
    }

    auto initValueVariable = owningComponent(variable)->variable(variable->initialValue());
    auto analyserInitialValueVariable = analyserVariable(initValueVariable);
    std::ostringstream index;

    index << analyserInitialValueVariable->index();

    return mLockedProfile->variablesArrayString() + mLockedProfile->openArrayString() + index.str() + mLockedProfile->closeArrayString();
}

std::string Generator::GeneratorImpl::generateVariableNameCode(const VariablePtr &variable,
                                                               const AnalyserEquationAstPtr &ast) const
{
    // Generate some code for a variable name, but only if we have a model. If
    // we don't have a model, it means that we are using the generator from the
    // analyser, in which case we just want to return the original name of the
    // variable.

    if (mLockedModel == nullptr) {
        return variable->name();
    }

    auto analyserVariable = Generator::GeneratorImpl::analyserVariable(variable);

    if (analyserVariable->type() == AnalyserVariable::Type::VARIABLE_OF_INTEGRATION) {
        return mLockedProfile->voiString();
    }

    std::string arrayName;

    if (analyserVariable->type() == AnalyserVariable::Type::STATE) {
        arrayName = ((ast != nullptr) && (ast->parent()->type() == AnalyserEquationAst::Type::DIFF)) ?
                        mLockedProfile->ratesArrayString() :
                        mLockedProfile->statesArrayString();
    } else {
        arrayName = mLockedProfile->variablesArrayString();
    }

    std::ostringstream index;

    index << analyserVariable->index();

    return arrayName + mLockedProfile->openArrayString() + index.str() + mLockedProfile->closeArrayString();
}

std::string Generator::GeneratorImpl::generateOperatorCode(const std::string &op,
                                                           const AnalyserEquationAstPtr &ast) const
{
    // Generate the code for the left and right branches of the given AST.

    auto astLeftChild = ast->leftChild();
    auto astRightChild = ast->rightChild();
    auto astLeftChildCode = generateCode(astLeftChild);
    auto astRightChildCode = generateCode(astRightChild);

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

        if (isRelationalOperator(astRightChild)
            || isLogicalOperator(astRightChild)
            || isMinusOperator(astRightChild)
            || isPiecewiseStatement(astRightChild)) {
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
        // Note: according to the precedence rules above, we only need to add
        //       parentheses around OR and PIECEWISE. However, it looks
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
        // Note: according to the precedence rules above, we only need to add
        //       parentheses around PIECEWISE. However, it looks better/clearer
        //       to have some around some other operators (agreed, this is
        //       somewhat subjective).

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
        // Note: according to the precedence rules above, we only need to add
        //       parentheses around AND, OR and PIECEWISE. However, it looks
        //       better/clearer to have some around some other operators
        //       (agreed, this is somewhat subjective).

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

std::string Generator::GeneratorImpl::generateMinusUnaryCode(const AnalyserEquationAstPtr &ast) const
{
    // Generate the code for the left branch of the given AST.

    auto astLeftChild = ast->leftChild();
    auto code = generateCode(astLeftChild);

    // Determine whether parentheses should be added around the left code.

    if (isRelationalOperator(astLeftChild)
        || isLogicalOperator(astLeftChild)
        || isPlusOperator(astLeftChild)
        || isMinusOperator(astLeftChild)
        || isPiecewiseStatement(astLeftChild)) {
        code = "(" + code + ")";
    }

    return mLockedProfile->minusString() + code;
}

std::string Generator::GeneratorImpl::generateOneParameterFunctionCode(const std::string &function,
                                                                       const AnalyserEquationAstPtr &ast) const
{
    return function + "(" + generateCode(ast->leftChild()) + ")";
}

std::string Generator::GeneratorImpl::generateTwoParameterFunctionCode(const std::string &function,
                                                                       const AnalyserEquationAstPtr &ast) const
{
    return function + "(" + generateCode(ast->leftChild()) + ", " + generateCode(ast->rightChild()) + ")";
}

std::string Generator::GeneratorImpl::generatePiecewiseIfCode(const std::string &condition,
                                                              const std::string &value) const
{
    return replace(replace(mLockedProfile->hasConditionalOperator() ?
                               mLockedProfile->conditionalOperatorIfString() :
                               mLockedProfile->piecewiseIfString(),
                           "[CONDITION]", condition),
                   "[IF_STATEMENT]", value);
}

std::string Generator::GeneratorImpl::generatePiecewiseElseCode(const std::string &value) const
{
    return replace(mLockedProfile->hasConditionalOperator() ?
                       mLockedProfile->conditionalOperatorElseString() :
                       mLockedProfile->piecewiseElseString(),
                   "[ELSE_STATEMENT]", value);
}

std::string Generator::GeneratorImpl::generateCode(const AnalyserEquationAstPtr &ast) const
{
    // Generate the code for the given AST.

    std::string code;

    switch (ast->type()) {
    case AnalyserEquationAst::Type::ASSIGNMENT:
        code = generateOperatorCode(mLockedProfile->assignmentString(), ast);

        break;
    case AnalyserEquationAst::Type::EQ:
        if (mLockedProfile->hasEqOperator()) {
            code = generateOperatorCode(mLockedProfile->eqString(), ast);
        } else {
            code = generateTwoParameterFunctionCode(mLockedProfile->eqString(), ast);
        }

        break;
    case AnalyserEquationAst::Type::NEQ:
        if (mLockedProfile->hasNeqOperator()) {
            code = generateOperatorCode(mLockedProfile->neqString(), ast);
        } else {
            code = generateTwoParameterFunctionCode(mLockedProfile->neqString(), ast);
        }

        break;
    case AnalyserEquationAst::Type::LT:
        if (mLockedProfile->hasLtOperator()) {
            code = generateOperatorCode(mLockedProfile->ltString(), ast);
        } else {
            code = generateTwoParameterFunctionCode(mLockedProfile->ltString(), ast);
        }

        break;
    case AnalyserEquationAst::Type::LEQ:
        if (mLockedProfile->hasLeqOperator()) {
            code = generateOperatorCode(mLockedProfile->leqString(), ast);
        } else {
            code = generateTwoParameterFunctionCode(mLockedProfile->leqString(), ast);
        }

        break;
    case AnalyserEquationAst::Type::GT:
        if (mLockedProfile->hasGtOperator()) {
            code = generateOperatorCode(mLockedProfile->gtString(), ast);
        } else {
            code = generateTwoParameterFunctionCode(mLockedProfile->gtString(), ast);
        }

        break;
    case AnalyserEquationAst::Type::GEQ:
        if (mLockedProfile->hasGeqOperator()) {
            code = generateOperatorCode(mLockedProfile->geqString(), ast);
        } else {
            code = generateTwoParameterFunctionCode(mLockedProfile->geqString(), ast);
        }

        break;
    case AnalyserEquationAst::Type::AND:
        if (mLockedProfile->hasAndOperator()) {
            code = generateOperatorCode(mLockedProfile->andString(), ast);
        } else {
            code = generateTwoParameterFunctionCode(mLockedProfile->andString(), ast);
        }

        break;
    case AnalyserEquationAst::Type::OR:
        if (mLockedProfile->hasOrOperator()) {
            code = generateOperatorCode(mLockedProfile->orString(), ast);
        } else {
            code = generateTwoParameterFunctionCode(mLockedProfile->orString(), ast);
        }

        break;
    case AnalyserEquationAst::Type::XOR:
        if (mLockedProfile->hasXorOperator()) {
            code = generateOperatorCode(mLockedProfile->xorString(), ast);
        } else {
            code = generateTwoParameterFunctionCode(mLockedProfile->xorString(), ast);
        }

        break;
    case AnalyserEquationAst::Type::NOT:
        if (mLockedProfile->hasNotOperator()) {
            code = mLockedProfile->notString() + generateCode(ast->leftChild());
        } else {
            code = generateOneParameterFunctionCode(mLockedProfile->notString(), ast);
        }

        break;
    case AnalyserEquationAst::Type::PLUS:
        if (ast->rightChild() != nullptr) {
            code = generateOperatorCode(mLockedProfile->plusString(), ast);
        } else {
            code = generateCode(ast->leftChild());
        }

        break;
    case AnalyserEquationAst::Type::MINUS:
        if (ast->rightChild() != nullptr) {
            code = generateOperatorCode(mLockedProfile->minusString(), ast);
        } else {
            code = generateMinusUnaryCode(ast);
        }

        break;
    case AnalyserEquationAst::Type::TIMES:
        code = generateOperatorCode(mLockedProfile->timesString(), ast);

        break;
    case AnalyserEquationAst::Type::DIVIDE:
        code = generateOperatorCode(mLockedProfile->divideString(), ast);

        break;
    case AnalyserEquationAst::Type::POWER: {
        auto stringValue = generateCode(ast->rightChild());
        bool validConversion;
        double doubleValue = convertToDouble(stringValue, &validConversion);

        if (validConversion && areEqual(doubleValue, 0.5)) {
            code = generateOneParameterFunctionCode(mLockedProfile->squareRootString(), ast);
        } else if (validConversion && areEqual(doubleValue, 2.0)
                   && !mLockedProfile->squareString().empty()) {
            code = generateOneParameterFunctionCode(mLockedProfile->squareString(), ast);
        } else {
            code = mLockedProfile->hasPowerOperator() ?
                       generateOperatorCode(mLockedProfile->powerString(), ast) :
                       mLockedProfile->powerString() + "(" + generateCode(ast->leftChild()) + ", " + stringValue + ")";
        }
    }

    break;
    case AnalyserEquationAst::Type::ROOT: {
        auto astRightChild = ast->rightChild();

        if (astRightChild != nullptr) {
            auto astLeftChild = ast->leftChild();
            bool validConversion;
            double doubleValue = convertToDouble(generateCode(astLeftChild), &validConversion);

            if (validConversion && areEqual(doubleValue, 2.0)) {
                code = mLockedProfile->squareRootString() + "(" + generateCode(astRightChild) + ")";
            } else {
                if (mLockedProfile->hasPowerOperator()) {
                    code = generateOperatorCode(mLockedProfile->powerString(), ast);
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

                    code = mLockedProfile->powerString() + "(" + generateCode(astRightChild) + ", " + generateOperatorCode(mLockedProfile->divideString(), rootValueAst) + ")";
                }
            }
        } else {
            code = generateOneParameterFunctionCode(mLockedProfile->squareRootString(), ast);
        }
    }

    break;
    case AnalyserEquationAst::Type::ABS:
        code = generateOneParameterFunctionCode(mLockedProfile->absoluteValueString(), ast);

        break;
    case AnalyserEquationAst::Type::EXP:
        code = generateOneParameterFunctionCode(mLockedProfile->exponentialString(), ast);

        break;
    case AnalyserEquationAst::Type::LN:
        code = generateOneParameterFunctionCode(mLockedProfile->naturalLogarithmString(), ast);

        break;
    case AnalyserEquationAst::Type::LOG: {
        auto astRightChild = ast->rightChild();

        if (astRightChild != nullptr) {
            auto stringValue = generateCode(ast->leftChild());
            bool validConversion;
            double doubleValue = convertToDouble(stringValue, &validConversion);

            if (validConversion && areEqual(doubleValue, 10.0)) {
                code = mLockedProfile->commonLogarithmString() + "(" + generateCode(astRightChild) + ")";
            } else {
                code = mLockedProfile->naturalLogarithmString() + "(" + generateCode(astRightChild) + ")/" + mLockedProfile->naturalLogarithmString() + "(" + stringValue + ")";
            }
        } else {
            code = generateOneParameterFunctionCode(mLockedProfile->commonLogarithmString(), ast);
        }
    }

    break;
    case AnalyserEquationAst::Type::CEILING:
        code = generateOneParameterFunctionCode(mLockedProfile->ceilingString(), ast);

        break;
    case AnalyserEquationAst::Type::FLOOR:
        code = generateOneParameterFunctionCode(mLockedProfile->floorString(), ast);

        break;
    case AnalyserEquationAst::Type::MIN:
        code = generateTwoParameterFunctionCode(mLockedProfile->minString(), ast);

        break;
    case AnalyserEquationAst::Type::MAX:
        code = generateTwoParameterFunctionCode(mLockedProfile->maxString(), ast);

        break;
    case AnalyserEquationAst::Type::REM:
        code = generateTwoParameterFunctionCode(mLockedProfile->remString(), ast);

        break;
    case AnalyserEquationAst::Type::DIFF:
        code = generateCode(ast->rightChild());

        break;
    case AnalyserEquationAst::Type::SIN:
        code = generateOneParameterFunctionCode(mLockedProfile->sinString(), ast);

        break;
    case AnalyserEquationAst::Type::COS:
        code = generateOneParameterFunctionCode(mLockedProfile->cosString(), ast);

        break;
    case AnalyserEquationAst::Type::TAN:
        code = generateOneParameterFunctionCode(mLockedProfile->tanString(), ast);

        break;
    case AnalyserEquationAst::Type::SEC:
        code = generateOneParameterFunctionCode(mLockedProfile->secString(), ast);

        break;
    case AnalyserEquationAst::Type::CSC:
        code = generateOneParameterFunctionCode(mLockedProfile->cscString(), ast);

        break;
    case AnalyserEquationAst::Type::COT:
        code = generateOneParameterFunctionCode(mLockedProfile->cotString(), ast);

        break;
    case AnalyserEquationAst::Type::SINH:
        code = generateOneParameterFunctionCode(mLockedProfile->sinhString(), ast);

        break;
    case AnalyserEquationAst::Type::COSH:
        code = generateOneParameterFunctionCode(mLockedProfile->coshString(), ast);

        break;
    case AnalyserEquationAst::Type::TANH:
        code = generateOneParameterFunctionCode(mLockedProfile->tanhString(), ast);

        break;
    case AnalyserEquationAst::Type::SECH:
        code = generateOneParameterFunctionCode(mLockedProfile->sechString(), ast);

        break;
    case AnalyserEquationAst::Type::CSCH:
        code = generateOneParameterFunctionCode(mLockedProfile->cschString(), ast);

        break;
    case AnalyserEquationAst::Type::COTH:
        code = generateOneParameterFunctionCode(mLockedProfile->cothString(), ast);

        break;
    case AnalyserEquationAst::Type::ASIN:
        code = generateOneParameterFunctionCode(mLockedProfile->asinString(), ast);

        break;
    case AnalyserEquationAst::Type::ACOS:
        code = generateOneParameterFunctionCode(mLockedProfile->acosString(), ast);

        break;
    case AnalyserEquationAst::Type::ATAN:
        code = generateOneParameterFunctionCode(mLockedProfile->atanString(), ast);

        break;
    case AnalyserEquationAst::Type::ASEC:
        code = generateOneParameterFunctionCode(mLockedProfile->asecString(), ast);

        break;
    case AnalyserEquationAst::Type::ACSC:
        code = generateOneParameterFunctionCode(mLockedProfile->acscString(), ast);

        break;
    case AnalyserEquationAst::Type::ACOT:
        code = generateOneParameterFunctionCode(mLockedProfile->acotString(), ast);

        break;
    case AnalyserEquationAst::Type::ASINH:
        code = generateOneParameterFunctionCode(mLockedProfile->asinhString(), ast);

        break;
    case AnalyserEquationAst::Type::ACOSH:
        code = generateOneParameterFunctionCode(mLockedProfile->acoshString(), ast);

        break;
    case AnalyserEquationAst::Type::ATANH:
        code = generateOneParameterFunctionCode(mLockedProfile->atanhString(), ast);

        break;
    case AnalyserEquationAst::Type::ASECH:
        code = generateOneParameterFunctionCode(mLockedProfile->asechString(), ast);

        break;
    case AnalyserEquationAst::Type::ACSCH:
        code = generateOneParameterFunctionCode(mLockedProfile->acschString(), ast);

        break;
    case AnalyserEquationAst::Type::ACOTH:
        code = generateOneParameterFunctionCode(mLockedProfile->acothString(), ast);

        break;
    case AnalyserEquationAst::Type::PIECEWISE: {
        auto astRightChild = ast->rightChild();

        if (astRightChild != nullptr) {
            if (astRightChild->type() == AnalyserEquationAst::Type::PIECE) {
                code = generateCode(ast->leftChild()) + generatePiecewiseElseCode(generateCode(astRightChild) + generatePiecewiseElseCode(mLockedProfile->nanString()));
            } else {
                code = generateCode(ast->leftChild()) + generatePiecewiseElseCode(generateCode(astRightChild));
            }
        } else {
            code = generateCode(ast->leftChild()) + generatePiecewiseElseCode(mLockedProfile->nanString());
        }
    }

    break;
    case AnalyserEquationAst::Type::PIECE:
        code = generatePiecewiseIfCode(generateCode(ast->rightChild()), generateCode(ast->leftChild()));

        break;
    case AnalyserEquationAst::Type::OTHERWISE:
        code = generateCode(ast->leftChild());

        break;
    case AnalyserEquationAst::Type::CI:
        code = generateVariableNameCode(ast->variable(), ast);

        break;
    case AnalyserEquationAst::Type::CN:
        code = generateDoubleCode(ast->value());

        break;
    case AnalyserEquationAst::Type::DEGREE:
    case AnalyserEquationAst::Type::LOGBASE:
    case AnalyserEquationAst::Type::BVAR:
        code = generateCode(ast->leftChild());

        break;
    case AnalyserEquationAst::Type::TRUE:
        code = mLockedProfile->trueString();

        break;
    case AnalyserEquationAst::Type::FALSE:
        code = mLockedProfile->falseString();

        break;
    case AnalyserEquationAst::Type::E:
        code = mLockedProfile->eString();

        break;
    case AnalyserEquationAst::Type::PI:
        code = mLockedProfile->piString();

        break;
    case AnalyserEquationAst::Type::INF:
        code = mLockedProfile->infString();

        break;
    case AnalyserEquationAst::Type::NAN:
        code = mLockedProfile->nanString();

        break;
    }

    return code;
}

std::string Generator::GeneratorImpl::generateInitializationCode(const AnalyserVariablePtr &variable) const
{
    std::string scalingFactorCode;
    auto scalingFactor = Generator::GeneratorImpl::scalingFactor(variable->initialisingVariable());

    if (!areNearlyEqual(scalingFactor, 1.0)) {
        scalingFactorCode = generateDoubleCode(convertToString(1.0 / scalingFactor)) + mLockedProfile->timesString();
    }

    return mLockedProfile->indentString() + generateVariableNameCode(variable->variable()) + " = "
           + scalingFactorCode + generateDoubleOrConstantVariableNameCode(variable->initialisingVariable())
           + mLockedProfile->commandSeparatorString() + "\n";
}

std::string Generator::GeneratorImpl::generateEquationCode(const AnalyserEquationPtr &equation,
                                                           std::vector<AnalyserEquationPtr> &remainingEquations,
                                                           bool onlyStateRateBasedEquations) const
{
    std::string res;

    if (std::find(remainingEquations.begin(), remainingEquations.end(), equation) != remainingEquations.end()) {
        if ((equation->type() == AnalyserEquation::Type::RATE)
            || (equation->type() == AnalyserEquation::Type::ALGEBRAIC)
            || (equation->type() == AnalyserEquation::Type::EXTERNAL)) {
            for (const auto &dependency : equation->dependencies()) {
                if ((dependency->type() != AnalyserEquation::Type::RATE)
                    && (!onlyStateRateBasedEquations
                        || (((dependency->type() == AnalyserEquation::Type::ALGEBRAIC)
                             || (dependency->type() == AnalyserEquation::Type::EXTERNAL))
                            && dependency->isStateRateBased()))) {
                    res += generateEquationCode(dependency, remainingEquations, onlyStateRateBasedEquations);
                }
            }
        }

        if (equation->type() == AnalyserEquation::Type::EXTERNAL) {
            std::ostringstream index;

            index << equation->variable()->index();

            res += mLockedProfile->indentString() + generateVariableNameCode(equation->variable()->variable()) + " = "
                   + replace((mLockedModel->type() == AnalyserModel::Type::ALGEBRAIC) ?
                                 mLockedProfile->externalVariableMethodCallInAlgebraicModelString() :
                                 mLockedProfile->externalVariableMethodCallInDifferentialModelString(),
                             "[INDEX]", index.str())
                   + mLockedProfile->commandSeparatorString() + "\n";
        } else {
            res += mLockedProfile->indentString() + generateCode(equation->ast()) + mLockedProfile->commandSeparatorString() + "\n";
        }

        remainingEquations.erase(std::find(remainingEquations.begin(), remainingEquations.end(), equation));
    }

    return res;
}

void Generator::GeneratorImpl::addInterfaceComputeModelMethodsCode()
{
    std::string interfaceComputeModelMethodsCode;

    if (((mLockedModel->type() == AnalyserModel::Type::ALGEBRAIC)
         && !mLockedProfile->interfaceInitialiseConstantsMethodString().empty())
        || ((mLockedModel->type() == AnalyserModel::Type::ODE)
            && !mLockedProfile->interfaceInitialiseStatesAndConstantsMethodString().empty())) {
        interfaceComputeModelMethodsCode += (mLockedModel->type() == AnalyserModel::Type::ALGEBRAIC) ?
                                                mLockedProfile->interfaceInitialiseConstantsMethodString() :
                                                mLockedProfile->interfaceInitialiseStatesAndConstantsMethodString();
    }

    if (!mLockedProfile->interfaceComputeComputedConstantsMethodString().empty()) {
        interfaceComputeModelMethodsCode += mLockedProfile->interfaceComputeComputedConstantsMethodString();
    }

    if ((mLockedModel->type() == AnalyserModel::Type::ODE)
        && !mLockedProfile->interfaceComputeRatesMethodString().empty()
        && ((mLockedModel->hasExternalVariables() && !mLockedProfile->externalVariableMethodParameterString().empty())
            || !mLockedModel->hasExternalVariables())) {
        interfaceComputeModelMethodsCode += replace(mLockedProfile->interfaceComputeRatesMethodString(),
                                                    "[OPTIONAL_PARAMETER]", mLockedModel->hasExternalVariables() ? mLockedProfile->externalVariableMethodParameterString() : "");
    }

    if ((((mLockedModel->type() == AnalyserModel::Type::ALGEBRAIC)
          && !mLockedProfile->interfaceComputeVariablesMethodInAlgebraicModelString().empty())
         || ((mLockedModel->type() == AnalyserModel::Type::ODE)
             && !mLockedProfile->interfaceComputeVariablesMethodInDifferentialModelString().empty()))
        && ((mLockedModel->hasExternalVariables() && !mLockedProfile->externalVariableMethodParameterString().empty())
            || !mLockedModel->hasExternalVariables())) {
        std::string interfaceMethodString = (mLockedModel->type() == AnalyserModel::Type::ALGEBRAIC) ?
                                                mLockedProfile->interfaceComputeVariablesMethodInAlgebraicModelString() :
                                                mLockedProfile->interfaceComputeVariablesMethodInDifferentialModelString();

        interfaceComputeModelMethodsCode += replace(interfaceMethodString,
                                                    "[OPTIONAL_PARAMETER]",
                                                    mLockedModel->hasExternalVariables() ?
                                                        mLockedProfile->externalVariableMethodParameterString() :
                                                        "");
    }

    if (!interfaceComputeModelMethodsCode.empty()) {
        mCode += "\n";
    }

    mCode += interfaceComputeModelMethodsCode;
}

void Generator::GeneratorImpl::addImplementationInitialiseStatesAndConstantsMethodCode(std::vector<AnalyserEquationPtr> &remainingEquations)
{
    if (((mLockedModel->type() == AnalyserModel::Type::ALGEBRAIC)
         && !mLockedProfile->implementationInitialiseConstantsMethodString().empty())
        || ((mLockedModel->type() == AnalyserModel::Type::ODE)
            && !mLockedProfile->implementationInitialiseStatesAndConstantsMethodString().empty())) {
        if (!mCode.empty()) {
            mCode += "\n";
        }

        std::string methodBody;

        for (const auto &variable : mLockedModel->variables()) {
            if (variable->type() == AnalyserVariable::Type::CONSTANT) {
                methodBody += generateInitializationCode(variable);
            }
        }

        for (const auto &equation : mLockedModel->equations()) {
            if (equation->type() == AnalyserEquation::Type::TRUE_CONSTANT) {
                methodBody += generateEquationCode(equation, remainingEquations);
            }
        }

        for (const auto &state : mLockedModel->states()) {
            methodBody += generateInitializationCode(state);
        }

        std::string interfaceMethodString = (mLockedModel->type() == AnalyserModel::Type::ALGEBRAIC) ?
                                                mLockedProfile->implementationInitialiseConstantsMethodString() :
                                                mLockedProfile->implementationInitialiseStatesAndConstantsMethodString();

        mCode += replace(interfaceMethodString, "[CODE]", generateMethodBodyCode(methodBody));
    }
}

void Generator::GeneratorImpl::addImplementationComputeComputedConstantsMethodCode(std::vector<AnalyserEquationPtr> &remainingEquations)
{
    if (!mLockedProfile->implementationComputeComputedConstantsMethodString().empty()) {
        if (!mCode.empty()) {
            mCode += "\n";
        }

        std::string methodBody;

        for (const auto &equation : mLockedModel->equations()) {
            if (equation->type() == AnalyserEquation::Type::VARIABLE_BASED_CONSTANT) {
                methodBody += generateEquationCode(equation, remainingEquations);
            }
        }

        mCode += replace(mLockedProfile->implementationComputeComputedConstantsMethodString(),
                         "[CODE]", generateMethodBodyCode(methodBody));
    }
}

void Generator::GeneratorImpl::addImplementationComputeRatesMethodCode(std::vector<AnalyserEquationPtr> &remainingEquations)
{
    if ((mLockedModel->type() == AnalyserModel::Type::ODE)
        && !mLockedProfile->implementationComputeRatesMethodString().empty()
        && ((mLockedModel->hasExternalVariables() && !mLockedProfile->externalVariableMethodParameterString().empty())
            || !mLockedModel->hasExternalVariables())) {
        if (!mCode.empty()) {
            mCode += "\n";
        }

        std::string methodBody;

        for (const auto &equation : mLockedModel->equations()) {
            if (equation->type() == AnalyserEquation::Type::RATE) {
                methodBody += generateEquationCode(equation, remainingEquations);
            }
        }

        mCode += replace(replace(mLockedProfile->implementationComputeRatesMethodString(),
                                 "[OPTIONAL_PARAMETER]", mLockedModel->hasExternalVariables() ? mLockedProfile->externalVariableMethodParameterString() : ""),
                         "[CODE]", generateMethodBodyCode(methodBody));
    }
}

void Generator::GeneratorImpl::addImplementationComputeVariablesMethodCode(std::vector<AnalyserEquationPtr> &remainingEquations)
{
    if ((((mLockedModel->type() == AnalyserModel::Type::ALGEBRAIC)
          && !mLockedProfile->implementationComputeVariablesMethodInAlgebraicModelString().empty())
         || ((mLockedModel->type() == AnalyserModel::Type::ODE)
             && !mLockedProfile->implementationComputeVariablesMethodInDifferentialModelString().empty()))
        && ((mLockedModel->hasExternalVariables() && !mLockedProfile->externalVariableMethodParameterString().empty())
            || !mLockedModel->hasExternalVariables())) {
        if (!mCode.empty()) {
            mCode += "\n";
        }

        std::string methodBody;
        auto equations = mLockedModel->equations();
        std::vector<AnalyserEquationPtr> newRemainingEquations {std::begin(equations), std::end(equations)};

        for (const auto &equation : equations) {
            if ((std::find(remainingEquations.begin(), remainingEquations.end(), equation) != remainingEquations.end())
                || (((equation->type() == AnalyserEquation::Type::ALGEBRAIC)
                     || (equation->type() == AnalyserEquation::Type::EXTERNAL))
                    && equation->isStateRateBased())) {
                methodBody += generateEquationCode(equation, newRemainingEquations, true);
            }
        }

        mCode += (mLockedModel->type() == AnalyserModel::Type::ALGEBRAIC) ?
                     replace(replace(mLockedProfile->implementationComputeVariablesMethodInAlgebraicModelString(),
                                     "[OPTIONAL_PARAMETER]", mLockedModel->hasExternalVariables() ? mLockedProfile->externalVariableMethodParameterString() : ""),
                             "[CODE]", generateMethodBodyCode(methodBody)) :
                     replace(replace(mLockedProfile->implementationComputeVariablesMethodInDifferentialModelString(),
                                     "[OPTIONAL_PARAMETER]", mLockedModel->hasExternalVariables() ? mLockedProfile->externalVariableMethodParameterString() : ""),
                             "[CODE]", generateMethodBodyCode(methodBody));
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
    if (mPimpl->mOwnedProfile != nullptr) {
        return mPimpl->mOwnedProfile;
    }

    return mPimpl->mProfile.lock();
}

void Generator::setProfile(const GeneratorProfilePtr &profile)
{
    mPimpl->mOwnedProfile = nullptr;
    mPimpl->mProfile = profile;
}

AnalyserModelPtr Generator::model()
{
    return mPimpl->mModel.lock();
}

void Generator::setModel(const AnalyserModelPtr &model)
{
    mPimpl->mModel = model;
}

std::string Generator::interfaceCode() const
{
    if (!mPimpl->retrieveLockedModelAndProfile()
        || !mPimpl->mLockedModel->isValid()
        || !mPimpl->mLockedProfile->hasInterface()) {
        mPimpl->resetLockedModelAndProfile();

        return {};
    }

    // Add code for the origin comment.

    mPimpl->mCode = {};

    mPimpl->addOriginCommentCode();

    // Add code for the header.

    mPimpl->addInterfaceHeaderCode();

    // Add code for the interface of the version of the profile and libCellML.

    mPimpl->addVersionAndLibcellmlVersionCode(true);

    // Add code for the interface of the number of states and variables.

    mPimpl->addStateAndVariableCountCode(true);

    // Add code for the variable information related objects.

    mPimpl->addVariableTypeObjectCode();
    mPimpl->addVariableInfoObjectCode();

    // Add code for the interface of the information about the variable of
    // integration, states and (other) variables.

    mPimpl->addInterfaceVoiStateAndVariableInfoCode();

    // Add code for the interface to create and delete arrays.

    mPimpl->addInterfaceCreateDeleteArrayMethodsCode();

    // Add code for the external variable method type definition.

    mPimpl->addExternalVariableMethodTypeDefinitionCode();

    // Add code for the interface to compute the model.

    mPimpl->addInterfaceComputeModelMethodsCode();

    mPimpl->resetLockedModelAndProfile();

    return mPimpl->mCode;
}

std::string Generator::implementationCode() const
{
    if (!mPimpl->retrieveLockedModelAndProfile()
        || !mPimpl->mLockedModel->isValid()) {
        mPimpl->resetLockedModelAndProfile();

        return {};
    }

    // Add code for the origin comment.

    mPimpl->mCode = {};

    mPimpl->addOriginCommentCode();

    // Add code for the header.

    mPimpl->addImplementationHeaderCode();

    // Add code for the implementation of the version of the profile and
    // libCellML.

    mPimpl->addVersionAndLibcellmlVersionCode();

    // Add code for the implementation of the number of states and variables.

    mPimpl->addStateAndVariableCountCode();

    // Add code for the variable information related objects.

    if (!mPimpl->mLockedProfile->hasInterface()) {
        mPimpl->addVariableTypeObjectCode();
        mPimpl->addVariableInfoObjectCode();
    }

    // Add code for the implementation of the information about the variable of
    // integration, states and (other) variables.

    mPimpl->addImplementationVoiInfoCode();
    mPimpl->addImplementationStateInfoCode();
    mPimpl->addImplementationVariableInfoCode();

    // Add code for the arithmetic and trigonometric functions.

    mPimpl->addArithmeticFunctionsCode();
    mPimpl->addTrigonometricFunctionsCode();

    // Add code for the implementation to create and delete arrays.

    mPimpl->addImplementationCreateStatesArrayMethodCode();
    mPimpl->addImplementationCreateVariablesArrayMethodCode();
    mPimpl->addImplementationDeleteArrayMethodCode();

    // Add code for the implementation to initialise our states and constants.

    auto equations = mPimpl->mLockedModel->equations();
    std::vector<AnalyserEquationPtr> remainingEquations {std::begin(equations), std::end(equations)};

    mPimpl->addImplementationInitialiseStatesAndConstantsMethodCode(remainingEquations);

    // Add code for the implementation to compute our computed constants.

    mPimpl->addImplementationComputeComputedConstantsMethodCode(remainingEquations);

    // Add code for the implementation to compute our rates (and any variables
    // on which they depend).

    mPimpl->addImplementationComputeRatesMethodCode(remainingEquations);

    // Add code for the implementation to compute our variables.
    // Note: this method computes the remaining variables, i.e. the ones not
    //       needed to compute our rates, but also the variables that depend on
    //       the value of some states/rates. Indeed, this method is typically
    //       called after having integrated a model, thus ensuring that
    //       variables that rely on the value of some states/rates are up to
    //       date.

    mPimpl->addImplementationComputeVariablesMethodCode(remainingEquations);

    mPimpl->resetLockedModelAndProfile();

    return mPimpl->mCode;
}

} // namespace libcellml

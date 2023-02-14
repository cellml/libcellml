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

#include "generator_p.h"
#include "generatorprofilesha1values.h"
#include "generatorprofiletools.h"
#include "utilities.h"

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

void Generator::GeneratorImpl::reset()
{
    mCode = {};
    mNlaSystemIndex = MAX_SIZE_T;
}

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

bool Generator::GeneratorImpl::modelHasOdes() const
{
    return (mLockedModel->type() == AnalyserModel::Type::ODE)
           || (mLockedModel->type() == AnalyserModel::Type::DAE);
}

bool Generator::GeneratorImpl::modelHasNlas() const
{
    return (mLockedModel->type() == AnalyserModel::Type::NLA)
           || (mLockedModel->type() == AnalyserModel::Type::DAE);
}

AnalyserVariablePtr Generator::GeneratorImpl::analyserVariable(const VariablePtr &variable) const
{
    // Find and return the analyser variable associated with the given variable.

    AnalyserVariablePtr res;
    auto modelVoi = mLockedModel->voi();
    VariablePtr modelVoiVariable = (modelVoi != nullptr) ? modelVoi->variable() : nullptr;

    if ((modelVoiVariable != nullptr)
        && mLockedModel->areEquivalentVariables(variable, modelVoiVariable)) {
        res = modelVoi;
    } else {
        for (const auto &modelState : mLockedModel->states()) {
            if (mLockedModel->areEquivalentVariables(variable, modelState->variable())) {
                res = modelState;

                break;
            }
        }

        if (res == nullptr) {
            // Normally, we would have:
            //
            //     for (const auto &modelVariable : mLockedModel->variables()) {
            //         if (mLockedModel->areEquivalentVariables(variable, modelVariable->variable())) {
            //             res = modelVariable;
            //
            //             break;
            //         }
            //     }
            //
            // but we always have variables, so llvm-cov will complain that the
            // false branch of our for loop is never reached. The below code is
            // a bit more verbose but at least it makes llvm-cov happy.

            auto modelVariables = mLockedModel->variables();
            auto modelVariable = modelVariables.begin();

            do {
                if (mLockedModel->areEquivalentVariables(variable, (*modelVariable)->variable())) {
                    res = *modelVariable;
                } else {
                    ++modelVariable;
                }
            } while (res == nullptr);
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
    auto astType = ast->type();

    return ((astType == AnalyserEquationAst::Type::EQ) && mLockedProfile->hasEqOperator())
           || ((astType == AnalyserEquationAst::Type::NEQ) && mLockedProfile->hasNeqOperator())
           || ((astType == AnalyserEquationAst::Type::LT) && mLockedProfile->hasLtOperator())
           || ((astType == AnalyserEquationAst::Type::LEQ) && mLockedProfile->hasLeqOperator())
           || ((astType == AnalyserEquationAst::Type::GT) && mLockedProfile->hasGtOperator())
           || ((astType == AnalyserEquationAst::Type::GEQ) && mLockedProfile->hasGeqOperator());
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
    std::string profileContents = generatorProfileAsString(mLockedProfile);

    return (mLockedProfile->profile() == GeneratorProfile::Profile::C) ?
               sha1(profileContents) != C_GENERATOR_PROFILE_SHA1 :
               sha1(profileContents) != PYTHON_GENERATOR_PROFILE_SHA1;
}

std::string Generator::GeneratorImpl::newLineIfNeeded()
{
    return mCode.empty() ? "" : "\n";
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
        mCode += newLineIfNeeded()
                 + mLockedProfile->interfaceHeaderString();
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
        mCode += newLineIfNeeded()
                 + replace(mLockedProfile->implementationHeaderString(),
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
                static const std::regex regEx("([0-9]+\\.[0-9]+\\.[0-9]+)");

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

    if (modelHasOdes()
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
    auto variableTypeObjectString = mLockedProfile->variableTypeObjectString(modelHasOdes(),
                                                                             mLockedModel->hasExternalVariables());

    if (!variableTypeObjectString.empty()) {
        mCode += newLineIfNeeded()
                 + variableTypeObjectString;
    }
}

std::string Generator::GeneratorImpl::generateVariableInfoObjectCode(const std::string &objectString) const
{
    size_t componentSize = 0;
    size_t nameSize = 0;
    size_t unitsSize = 0;

    if (modelHasOdes()) {
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
        mCode += newLineIfNeeded()
                 + generateVariableInfoObjectCode(mLockedProfile->variableInfoObjectString());
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

    if (modelHasOdes()
        && !mLockedProfile->interfaceVoiInfoString().empty()) {
        interfaceVoiStateAndVariableInfoCode += mLockedProfile->interfaceVoiInfoString();
    }

    if (modelHasOdes()
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
    if (modelHasOdes()
        && !mLockedProfile->implementationVoiInfoString().empty()
        && !mLockedProfile->variableInfoEntryString().empty()
        && !mLockedProfile->variableOfIntegrationVariableTypeString().empty()) {
        auto voiVariable = mLockedModel->voi()->variable();
        auto name = voiVariable->name();
        auto units = voiVariable->units()->name();
        auto component = owningComponent(voiVariable)->name();
        auto type = mLockedProfile->variableOfIntegrationVariableTypeString();

        mCode += newLineIfNeeded()
                 + replace(mLockedProfile->implementationVoiInfoString(),
                           "[CODE]", generateVariableInfoEntryCode(name, units, component, type));
    }
}

void Generator::GeneratorImpl::addImplementationStateInfoCode()
{
    if (modelHasOdes()
        && !mLockedProfile->implementationStateInfoString().empty()
        && !mLockedProfile->variableInfoEntryString().empty()
        && !mLockedProfile->stateVariableTypeString().empty()
        && !mLockedProfile->arrayElementSeparatorString().empty()) {
        std::string infoElementsCode;
        auto type = mLockedProfile->stateVariableTypeString();

        for (const auto &state : mLockedModel->states()) {
            if (!infoElementsCode.empty()) {
                infoElementsCode += mLockedProfile->arrayElementSeparatorString() + "\n";
            }

            auto stateVariable = state->variable();

            infoElementsCode += mLockedProfile->indentString()
                                + generateVariableInfoEntryCode(stateVariable->name(),
                                                                stateVariable->units()->name(),
                                                                owningComponent(stateVariable)->name(),
                                                                type);
        }

        infoElementsCode += "\n";

        mCode += newLineIfNeeded()
                 + replace(mLockedProfile->implementationStateInfoString(),
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
            } else { // AnalyserVariable::Type::EXTERNAL.
                variableType = mLockedProfile->externalVariableTypeString();
            }

            auto variableVariable = variable->variable();

            infoElementsCode += mLockedProfile->indentString()
                                + replace(replace(replace(replace(mLockedProfile->variableInfoEntryString(),
                                                                  "[NAME]", variableVariable->name()),
                                                          "[UNITS]", variableVariable->units()->name()),
                                                  "[COMPONENT]", owningComponent(variableVariable)->name()),
                                          "[TYPE]", variableType);
        }

        if (!infoElementsCode.empty()) {
            infoElementsCode += "\n";
        }

        mCode += newLineIfNeeded()
                 + replace(mLockedProfile->implementationVariableInfoString(),
                           "[CODE]", infoElementsCode);
    }
}

void Generator::GeneratorImpl::addArithmeticFunctionsCode()
{
    if (mLockedModel->needEqFunction() && !mLockedProfile->hasEqOperator()
        && !mLockedProfile->eqFunctionString().empty()) {
        mCode += newLineIfNeeded()
                 + mLockedProfile->eqFunctionString();
    }

    if (mLockedModel->needNeqFunction() && !mLockedProfile->hasNeqOperator()
        && !mLockedProfile->neqFunctionString().empty()) {
        mCode += newLineIfNeeded()
                 + mLockedProfile->neqFunctionString();
    }

    if (mLockedModel->needLtFunction() && !mLockedProfile->hasLtOperator()
        && !mLockedProfile->ltFunctionString().empty()) {
        mCode += newLineIfNeeded()
                 + mLockedProfile->ltFunctionString();
    }

    if (mLockedModel->needLeqFunction() && !mLockedProfile->hasLeqOperator()
        && !mLockedProfile->leqFunctionString().empty()) {
        mCode += newLineIfNeeded()
                 + mLockedProfile->leqFunctionString();
    }

    if (mLockedModel->needGtFunction() && !mLockedProfile->hasGtOperator()
        && !mLockedProfile->gtFunctionString().empty()) {
        mCode += newLineIfNeeded()
                 + mLockedProfile->gtFunctionString();
    }

    if (mLockedModel->needGeqFunction() && !mLockedProfile->hasGeqOperator()
        && !mLockedProfile->geqFunctionString().empty()) {
        mCode += newLineIfNeeded()
                 + mLockedProfile->geqFunctionString();
    }

    if (mLockedModel->needAndFunction() && !mLockedProfile->hasAndOperator()
        && !mLockedProfile->andFunctionString().empty()) {
        mCode += newLineIfNeeded()
                 + mLockedProfile->andFunctionString();
    }

    if (mLockedModel->needOrFunction() && !mLockedProfile->hasOrOperator()
        && !mLockedProfile->orFunctionString().empty()) {
        mCode += newLineIfNeeded()
                 + mLockedProfile->orFunctionString();
    }

    if (mLockedModel->needXorFunction() && !mLockedProfile->hasXorOperator()
        && !mLockedProfile->xorFunctionString().empty()) {
        mCode += newLineIfNeeded()
                 + mLockedProfile->xorFunctionString();
    }

    if (mLockedModel->needNotFunction() && !mLockedProfile->hasNotOperator()
        && !mLockedProfile->notFunctionString().empty()) {
        mCode += newLineIfNeeded()
                 + mLockedProfile->notFunctionString();
    }

    if (mLockedModel->needMinFunction()
        && !mLockedProfile->minFunctionString().empty()) {
        mCode += newLineIfNeeded()
                 + mLockedProfile->minFunctionString();
    }

    if (mLockedModel->needMaxFunction()
        && !mLockedProfile->maxFunctionString().empty()) {
        mCode += newLineIfNeeded()
                 + mLockedProfile->maxFunctionString();
    }
}

void Generator::GeneratorImpl::addTrigonometricFunctionsCode()
{
    if (mLockedModel->needSecFunction()
        && !mLockedProfile->secFunctionString().empty()) {
        mCode += newLineIfNeeded()
                 + mLockedProfile->secFunctionString();
    }

    if (mLockedModel->needCscFunction()
        && !mLockedProfile->cscFunctionString().empty()) {
        mCode += newLineIfNeeded()
                 + mLockedProfile->cscFunctionString();
    }

    if (mLockedModel->needCotFunction()
        && !mLockedProfile->cotFunctionString().empty()) {
        mCode += newLineIfNeeded()
                 + mLockedProfile->cotFunctionString();
    }

    if (mLockedModel->needSechFunction()
        && !mLockedProfile->sechFunctionString().empty()) {
        mCode += newLineIfNeeded()
                 + mLockedProfile->sechFunctionString();
    }

    if (mLockedModel->needCschFunction()
        && !mLockedProfile->cschFunctionString().empty()) {
        mCode += newLineIfNeeded()
                 + mLockedProfile->cschFunctionString();
    }

    if (mLockedModel->needCothFunction()
        && !mLockedProfile->cothFunctionString().empty()) {
        mCode += newLineIfNeeded()
                 + mLockedProfile->cothFunctionString();
    }

    if (mLockedModel->needAsecFunction()
        && !mLockedProfile->asecFunctionString().empty()) {
        mCode += newLineIfNeeded()
                 + mLockedProfile->asecFunctionString();
    }

    if (mLockedModel->needAcscFunction()
        && !mLockedProfile->acscFunctionString().empty()) {
        mCode += newLineIfNeeded()
                 + mLockedProfile->acscFunctionString();
    }

    if (mLockedModel->needAcotFunction()
        && !mLockedProfile->acotFunctionString().empty()) {
        mCode += newLineIfNeeded()
                 + mLockedProfile->acotFunctionString();
    }

    if (mLockedModel->needAsechFunction()
        && !mLockedProfile->asechFunctionString().empty()) {
        mCode += newLineIfNeeded()
                 + mLockedProfile->asechFunctionString();
    }

    if (mLockedModel->needAcschFunction()
        && !mLockedProfile->acschFunctionString().empty()) {
        mCode += newLineIfNeeded()
                 + mLockedProfile->acschFunctionString();
    }

    if (mLockedModel->needAcothFunction()
        && !mLockedProfile->acothFunctionString().empty()) {
        mCode += newLineIfNeeded()
                 + mLockedProfile->acothFunctionString();
    }
}

void Generator::GeneratorImpl::addInterfaceCreateDeleteArrayMethodsCode()
{
    std::string interfaceCreateDeleteArraysCode;

    if (modelHasOdes()
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
        auto externalVariableMethodTypeDefinitionString = mLockedProfile->externalVariableMethodTypeDefinitionString(modelHasOdes());

        if (!externalVariableMethodTypeDefinitionString.empty()) {
            mCode += "\n"
                     + externalVariableMethodTypeDefinitionString;
        }
    }
}

void Generator::GeneratorImpl::addImplementationCreateStatesArrayMethodCode()
{
    if (modelHasOdes()
        && !mLockedProfile->implementationCreateStatesArrayMethodString().empty()) {
        mCode += newLineIfNeeded()
                 + mLockedProfile->implementationCreateStatesArrayMethodString();
    }
}

void Generator::GeneratorImpl::addImplementationCreateVariablesArrayMethodCode()
{
    if (!mLockedProfile->implementationCreateVariablesArrayMethodString().empty()) {
        mCode += newLineIfNeeded()
                 + mLockedProfile->implementationCreateVariablesArrayMethodString();
    }
}

void Generator::GeneratorImpl::addImplementationDeleteArrayMethodCode()
{
    if (!mLockedProfile->implementationDeleteArrayMethodString().empty()) {
        mCode += newLineIfNeeded()
                 + mLockedProfile->implementationDeleteArrayMethodString();
    }
}

void Generator::GeneratorImpl::addRootFindingInfoObjectCode()
{
    if (modelHasNlas()
        && !mLockedProfile->rootFindingInfoObjectString().empty()) {
        mCode += newLineIfNeeded()
                 + mLockedProfile->rootFindingInfoObjectString();
    }
}

void Generator::GeneratorImpl::addExternNlaSolveMethodCode()
{
    if (modelHasNlas()
        && !mLockedProfile->externNlaSolveMethodString().empty()) {
        mCode += newLineIfNeeded()
                 + mLockedProfile->externNlaSolveMethodString();
    }
}

void Generator::GeneratorImpl::addNlaSystemsCode()
{
    if (modelHasNlas()
        && !mLockedProfile->objectiveFunctionMethodString().empty()
        && !mLockedProfile->findRootMethodString().empty()
        && !mLockedProfile->nlaSolveCallString().empty()) {
        auto nlaSystemIndex = MAX_SIZE_T;

        for (const auto &equation : mLockedModel->equations()) {
            if (equation->type() == AnalyserEquation::Type::NLA) {
                std::string methodBody;
                auto i = MAX_SIZE_T;
                auto variables = equation->variables();
                auto variablesSize = variables.size();

                for (i = 0; i < variablesSize; ++i) {
                    methodBody += mLockedProfile->indentString()
                                  + mLockedProfile->variablesArrayString() + mLockedProfile->openArrayString() + convertToString(variables[i]->index()) + mLockedProfile->closeArrayString()
                                  + mLockedProfile->assignmentString()
                                  + mLockedProfile->uArrayString() + mLockedProfile->openArrayString() + convertToString(i) + mLockedProfile->closeArrayString()
                                  + mLockedProfile->commandSeparatorString() + "\n";
                }

                methodBody += newLineIfNeeded();

                for (i = 0; i < variablesSize; ++i) {
                    methodBody += mLockedProfile->indentString()
                                  + mLockedProfile->fArrayString() + mLockedProfile->openArrayString() + convertToString(i) + mLockedProfile->closeArrayString()
                                  + mLockedProfile->assignmentString()
                                  + generateCode(equation->ast())
                                  + mLockedProfile->commandSeparatorString() + "\n";
                }

                mCode += newLineIfNeeded()
                         + replace(replace(mLockedProfile->objectiveFunctionMethodString(),
                                           "[INDEX]", convertToString(++nlaSystemIndex)),
                                   "[CODE]", generateMethodBodyCode(methodBody));

                methodBody = {};

                for (i = 0; i < variablesSize; ++i) {
                    methodBody += mLockedProfile->indentString()
                                  + mLockedProfile->uArrayString() + mLockedProfile->openArrayString() + convertToString(i) + mLockedProfile->closeArrayString()
                                  + mLockedProfile->assignmentString()
                                  + mLockedProfile->variablesArrayString() + mLockedProfile->openArrayString() + convertToString(variables[i]->index()) + mLockedProfile->closeArrayString()
                                  + mLockedProfile->commandSeparatorString() + "\n";
                }

                methodBody += newLineIfNeeded()
                              + mLockedProfile->indentString()
                              + replace(replace(mLockedProfile->nlaSolveCallString(),
                                                "[INDEX]", convertToString(nlaSystemIndex)),
                                        "[SIZE]", convertToString(1));

                methodBody += newLineIfNeeded();

                for (i = 0; i < variablesSize; ++i) {
                    methodBody += mLockedProfile->indentString()
                                  + mLockedProfile->variablesArrayString() + mLockedProfile->openArrayString() + convertToString(variables[i]->index()) + mLockedProfile->closeArrayString()
                                  + mLockedProfile->assignmentString()
                                  + mLockedProfile->uArrayString() + mLockedProfile->openArrayString() + convertToString(i) + mLockedProfile->closeArrayString()
                                  + mLockedProfile->commandSeparatorString() + "\n";
                }

                mCode += newLineIfNeeded()
                         + replace(replace(replace(mLockedProfile->findRootMethodString(),
                                                   "[INDEX]", convertToString(nlaSystemIndex)),
                                           "[SIZE]", convertToString(variablesSize)),
                                   "[CODE]", generateMethodBodyCode(methodBody));
            }
        }
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

    return mLockedProfile->variablesArrayString() + mLockedProfile->openArrayString() + convertToString(analyserInitialValueVariable->index()) + mLockedProfile->closeArrayString();
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
        auto astParent = (ast != nullptr) ? ast->parent() : nullptr;

        arrayName = ((astParent != nullptr) && (astParent->type() == AnalyserEquationAst::Type::DIFF)) ?
                        mLockedProfile->ratesArrayString() :
                        mLockedProfile->statesArrayString();
    } else {
        arrayName = mLockedProfile->variablesArrayString();
    }

    return arrayName + mLockedProfile->openArrayString() + convertToString(analyserVariable->index()) + mLockedProfile->closeArrayString();
}

std::string Generator::GeneratorImpl::generateOperatorCode(const std::string &op,
                                                           const AnalyserEquationAstPtr &ast) const
{
    // Generate the code for the left and right branches of the given AST.

    std::string res;
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
    // Note: we don't handle the case of AnalyserEquationAst::Type::BVAR since
    //       we don't need to generate any code for it.

    std::string code;
    auto astType = ast->type();

    if (astType == AnalyserEquationAst::Type::EQUALITY) {
        code = generateOperatorCode(mLockedProfile->assignmentString(), ast);
    } else if (astType == AnalyserEquationAst::Type::EQ) {
        if (mLockedProfile->hasEqOperator()) {
            code = generateOperatorCode(mLockedProfile->eqString(), ast);
        } else {
            code = generateTwoParameterFunctionCode(mLockedProfile->eqString(), ast);
        }
    } else if (astType == AnalyserEquationAst::Type::NEQ) {
        if (mLockedProfile->hasNeqOperator()) {
            code = generateOperatorCode(mLockedProfile->neqString(), ast);
        } else {
            code = generateTwoParameterFunctionCode(mLockedProfile->neqString(), ast);
        }
    } else if (astType == AnalyserEquationAst::Type::LT) {
        if (mLockedProfile->hasLtOperator()) {
            code = generateOperatorCode(mLockedProfile->ltString(), ast);
        } else {
            code = generateTwoParameterFunctionCode(mLockedProfile->ltString(), ast);
        }
    } else if (astType == AnalyserEquationAst::Type::LEQ) {
        if (mLockedProfile->hasLeqOperator()) {
            code = generateOperatorCode(mLockedProfile->leqString(), ast);
        } else {
            code = generateTwoParameterFunctionCode(mLockedProfile->leqString(), ast);
        }
    } else if (astType == AnalyserEquationAst::Type::GT) {
        if (mLockedProfile->hasGtOperator()) {
            code = generateOperatorCode(mLockedProfile->gtString(), ast);
        } else {
            code = generateTwoParameterFunctionCode(mLockedProfile->gtString(), ast);
        }
    } else if (astType == AnalyserEquationAst::Type::GEQ) {
        if (mLockedProfile->hasGeqOperator()) {
            code = generateOperatorCode(mLockedProfile->geqString(), ast);
        } else {
            code = generateTwoParameterFunctionCode(mLockedProfile->geqString(), ast);
        }
    } else if (astType == AnalyserEquationAst::Type::AND) {
        if (mLockedProfile->hasAndOperator()) {
            code = generateOperatorCode(mLockedProfile->andString(), ast);
        } else {
            code = generateTwoParameterFunctionCode(mLockedProfile->andString(), ast);
        }
    } else if (astType == AnalyserEquationAst::Type::OR) {
        if (mLockedProfile->hasOrOperator()) {
            code = generateOperatorCode(mLockedProfile->orString(), ast);
        } else {
            code = generateTwoParameterFunctionCode(mLockedProfile->orString(), ast);
        }
    } else if (astType == AnalyserEquationAst::Type::XOR) {
        if (mLockedProfile->hasXorOperator()) {
            code = generateOperatorCode(mLockedProfile->xorString(), ast);
        } else {
            code = generateTwoParameterFunctionCode(mLockedProfile->xorString(), ast);
        }
    } else if (astType == AnalyserEquationAst::Type::NOT) {
        if (mLockedProfile->hasNotOperator()) {
            code = mLockedProfile->notString() + generateCode(ast->leftChild());
        } else {
            code = generateOneParameterFunctionCode(mLockedProfile->notString(), ast);
        }
    } else if (astType == AnalyserEquationAst::Type::PLUS) {
        if (ast->rightChild() != nullptr) {
            code = generateOperatorCode(mLockedProfile->plusString(), ast);
        } else {
            code = generateCode(ast->leftChild());
        }
    } else if (astType == AnalyserEquationAst::Type::MINUS) {
        if (ast->rightChild() != nullptr) {
            code = generateOperatorCode(mLockedProfile->minusString(), ast);
        } else {
            code = generateMinusUnaryCode(ast);
        }
    } else if (astType == AnalyserEquationAst::Type::TIMES) {
        code = generateOperatorCode(mLockedProfile->timesString(), ast);
    } else if (astType == AnalyserEquationAst::Type::DIVIDE) {
        code = generateOperatorCode(mLockedProfile->divideString(), ast);
    } else if (astType == AnalyserEquationAst::Type::POWER) {
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
    } else if (astType == AnalyserEquationAst::Type::ROOT) {
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
    } else if (astType == AnalyserEquationAst::Type::ABS) {
        code = generateOneParameterFunctionCode(mLockedProfile->absoluteValueString(), ast);
    } else if (astType == AnalyserEquationAst::Type::EXP) {
        code = generateOneParameterFunctionCode(mLockedProfile->exponentialString(), ast);
    } else if (astType == AnalyserEquationAst::Type::LN) {
        code = generateOneParameterFunctionCode(mLockedProfile->naturalLogarithmString(), ast);
    } else if (astType == AnalyserEquationAst::Type::LOG) {
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
    } else if (astType == AnalyserEquationAst::Type::CEILING) {
        code = generateOneParameterFunctionCode(mLockedProfile->ceilingString(), ast);
    } else if (astType == AnalyserEquationAst::Type::FLOOR) {
        code = generateOneParameterFunctionCode(mLockedProfile->floorString(), ast);
    } else if (astType == AnalyserEquationAst::Type::MIN) {
        code = generateTwoParameterFunctionCode(mLockedProfile->minString(), ast);
    } else if (astType == AnalyserEquationAst::Type::MAX) {
        code = generateTwoParameterFunctionCode(mLockedProfile->maxString(), ast);
    } else if (astType == AnalyserEquationAst::Type::REM) {
        code = generateTwoParameterFunctionCode(mLockedProfile->remString(), ast);
    } else if (astType == AnalyserEquationAst::Type::DIFF) {
        code = generateCode(ast->rightChild());
    } else if (astType == AnalyserEquationAst::Type::SIN) {
        code = generateOneParameterFunctionCode(mLockedProfile->sinString(), ast);
    } else if (astType == AnalyserEquationAst::Type::COS) {
        code = generateOneParameterFunctionCode(mLockedProfile->cosString(), ast);
    } else if (astType == AnalyserEquationAst::Type::TAN) {
        code = generateOneParameterFunctionCode(mLockedProfile->tanString(), ast);
    } else if (astType == AnalyserEquationAst::Type::SEC) {
        code = generateOneParameterFunctionCode(mLockedProfile->secString(), ast);
    } else if (astType == AnalyserEquationAst::Type::CSC) {
        code = generateOneParameterFunctionCode(mLockedProfile->cscString(), ast);
    } else if (astType == AnalyserEquationAst::Type::COT) {
        code = generateOneParameterFunctionCode(mLockedProfile->cotString(), ast);
    } else if (astType == AnalyserEquationAst::Type::SINH) {
        code = generateOneParameterFunctionCode(mLockedProfile->sinhString(), ast);
    } else if (astType == AnalyserEquationAst::Type::COSH) {
        code = generateOneParameterFunctionCode(mLockedProfile->coshString(), ast);
    } else if (astType == AnalyserEquationAst::Type::TANH) {
        code = generateOneParameterFunctionCode(mLockedProfile->tanhString(), ast);
    } else if (astType == AnalyserEquationAst::Type::SECH) {
        code = generateOneParameterFunctionCode(mLockedProfile->sechString(), ast);
    } else if (astType == AnalyserEquationAst::Type::CSCH) {
        code = generateOneParameterFunctionCode(mLockedProfile->cschString(), ast);
    } else if (astType == AnalyserEquationAst::Type::COTH) {
        code = generateOneParameterFunctionCode(mLockedProfile->cothString(), ast);
    } else if (astType == AnalyserEquationAst::Type::ASIN) {
        code = generateOneParameterFunctionCode(mLockedProfile->asinString(), ast);
    } else if (astType == AnalyserEquationAst::Type::ACOS) {
        code = generateOneParameterFunctionCode(mLockedProfile->acosString(), ast);
    } else if (astType == AnalyserEquationAst::Type::ATAN) {
        code = generateOneParameterFunctionCode(mLockedProfile->atanString(), ast);
    } else if (astType == AnalyserEquationAst::Type::ASEC) {
        code = generateOneParameterFunctionCode(mLockedProfile->asecString(), ast);
    } else if (astType == AnalyserEquationAst::Type::ACSC) {
        code = generateOneParameterFunctionCode(mLockedProfile->acscString(), ast);
    } else if (astType == AnalyserEquationAst::Type::ACOT) {
        code = generateOneParameterFunctionCode(mLockedProfile->acotString(), ast);
    } else if (astType == AnalyserEquationAst::Type::ASINH) {
        code = generateOneParameterFunctionCode(mLockedProfile->asinhString(), ast);
    } else if (astType == AnalyserEquationAst::Type::ACOSH) {
        code = generateOneParameterFunctionCode(mLockedProfile->acoshString(), ast);
    } else if (astType == AnalyserEquationAst::Type::ATANH) {
        code = generateOneParameterFunctionCode(mLockedProfile->atanhString(), ast);
    } else if (astType == AnalyserEquationAst::Type::ASECH) {
        code = generateOneParameterFunctionCode(mLockedProfile->asechString(), ast);
    } else if (astType == AnalyserEquationAst::Type::ACSCH) {
        code = generateOneParameterFunctionCode(mLockedProfile->acschString(), ast);
    } else if (astType == AnalyserEquationAst::Type::ACOTH) {
        code = generateOneParameterFunctionCode(mLockedProfile->acothString(), ast);
    } else if (astType == AnalyserEquationAst::Type::PIECEWISE) {
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
    } else if (astType == AnalyserEquationAst::Type::PIECE) {
        code = generatePiecewiseIfCode(generateCode(ast->rightChild()), generateCode(ast->leftChild()));
    } else if (astType == AnalyserEquationAst::Type::OTHERWISE) {
        code = generateCode(ast->leftChild());
    } else if (astType == AnalyserEquationAst::Type::CI) {
        code = generateVariableNameCode(ast->variable(), ast);
    } else if (astType == AnalyserEquationAst::Type::CN) {
        code = generateDoubleCode(ast->value());
    } else if ((astType == AnalyserEquationAst::Type::DEGREE)
               || (astType == AnalyserEquationAst::Type::LOGBASE)) {
        code = generateCode(ast->leftChild());
    } else if (astType == AnalyserEquationAst::Type::TRUE) {
        code = mLockedProfile->trueString();
    } else if (astType == AnalyserEquationAst::Type::FALSE) {
        code = mLockedProfile->falseString();
    } else if (astType == AnalyserEquationAst::Type::E) {
        code = mLockedProfile->eString();
    } else if (astType == AnalyserEquationAst::Type::PI) {
        code = mLockedProfile->piString();
    } else if (astType == AnalyserEquationAst::Type::INF) {
        code = mLockedProfile->infString();
    } else { // AnalyserEquationAst::Type::NAN.
        code = mLockedProfile->nanString();
    }

    return code;
}

bool Generator::GeneratorImpl::isStateRateBasedAlgebraicEqnOrExternalEqn(const AnalyserEquationPtr &equation) const
{
    return ((equation->type() == AnalyserEquation::Type::ALGEBRAIC)
            && equation->isStateRateBased())
           || (equation->type() == AnalyserEquation::Type::EXTERNAL);
}

std::string Generator::GeneratorImpl::generateInitialisationCode(const AnalyserVariablePtr &variable) const
{
    auto initialisingVariable = variable->initialisingVariable();
    auto scalingFactor = Generator::GeneratorImpl::scalingFactor(initialisingVariable);
    std::string scalingFactorCode;

    if (!areNearlyEqual(scalingFactor, 1.0)) {
        scalingFactorCode = generateDoubleCode(convertToString(1.0 / scalingFactor)) + mLockedProfile->timesString();
    }

    return mLockedProfile->indentString()
           + generateVariableNameCode(variable->variable())
           + mLockedProfile->assignmentString()
           + scalingFactorCode + generateDoubleOrConstantVariableNameCode(initialisingVariable)
           + mLockedProfile->commandSeparatorString() + "\n";
}

std::string Generator::GeneratorImpl::generateEquationCode(const AnalyserEquationPtr &equation,
                                                           std::vector<AnalyserEquationPtr> &remainingEquations,
                                                           bool forComputeVariables)
{
    std::string res;

    if (std::find(remainingEquations.begin(), remainingEquations.end(), equation) != remainingEquations.end()) {
        if ((equation->type() != AnalyserEquation::Type::TRUE_CONSTANT)
            && (equation->type() != AnalyserEquation::Type::VARIABLE_BASED_CONSTANT)) {
            for (const auto &dependency : equation->dependencies()) {
                if ((dependency->type() != AnalyserEquation::Type::ODE)
                    && (!forComputeVariables
                        || isStateRateBasedAlgebraicEqnOrExternalEqn(dependency))) {
                    res += generateEquationCode(dependency, remainingEquations, forComputeVariables);
                }
            }
        }

        if (equation->type() == AnalyserEquation::Type::EXTERNAL) {
            for (const auto &variable : equation->variables()) {
                res += mLockedProfile->indentString()
                       + generateVariableNameCode(variable->variable())
                       + mLockedProfile->assignmentString()
                       + replace(mLockedProfile->externalVariableMethodCallString(modelHasOdes()),
                                 "[INDEX]", convertToString(variable->index()))
                       + mLockedProfile->commandSeparatorString() + "\n";
            }
        } else if (equation->type() == AnalyserEquation::Type::NLA) {
            if (!mLockedProfile->findRootCallString().empty()) {
                res += mLockedProfile->indentString()
                       + replace(mLockedProfile->findRootCallString(),
                                 "[INDEX]", convertToString(++mNlaSystemIndex));
            }
        } else {
            res += mLockedProfile->indentString() + generateCode(equation->ast()) + mLockedProfile->commandSeparatorString() + "\n";
        }

        remainingEquations.erase(std::find(remainingEquations.begin(), remainingEquations.end(), equation));
    }

    return res;
}

void Generator::GeneratorImpl::addInterfaceComputeModelMethodsCode()
{
    auto interfaceInitialiseVariablesMethodString = mLockedProfile->interfaceInitialiseVariablesMethodString(modelHasOdes(),
                                                                                                             mLockedModel->hasExternalVariables());
    std::string interfaceComputeModelMethodsCode;

    if (!interfaceInitialiseVariablesMethodString.empty()) {
        interfaceComputeModelMethodsCode += interfaceInitialiseVariablesMethodString;
    }

    if (!mLockedProfile->interfaceComputeComputedConstantsMethodString().empty()) {
        interfaceComputeModelMethodsCode += mLockedProfile->interfaceComputeComputedConstantsMethodString();
    }

    auto interfaceComputeRatesMethodString = mLockedProfile->interfaceComputeRatesMethodString(mLockedModel->hasExternalVariables());

    if (modelHasOdes()
        && !interfaceComputeRatesMethodString.empty()) {
        interfaceComputeModelMethodsCode += interfaceComputeRatesMethodString;
    }

    auto interfaceComputeVariablesMethodString = mLockedProfile->interfaceComputeVariablesMethodString(modelHasOdes(),
                                                                                                       mLockedModel->hasExternalVariables());

    if (!interfaceComputeVariablesMethodString.empty()) {
        interfaceComputeModelMethodsCode += interfaceComputeVariablesMethodString;
    }

    if (!interfaceComputeModelMethodsCode.empty()) {
        mCode += "\n";
    }

    mCode += interfaceComputeModelMethodsCode;
}

void Generator::GeneratorImpl::addImplementationInitialiseVariablesMethodCode(std::vector<AnalyserEquationPtr> &remainingEquations)
{
    auto implementationInitialiseVariablesMethodString = mLockedProfile->implementationInitialiseVariablesMethodString(modelHasOdes(),
                                                                                                                       mLockedModel->hasExternalVariables());

    if (!implementationInitialiseVariablesMethodString.empty()) {
        std::string methodBody;

        for (const auto &variable : mLockedModel->variables()) {
            if (variable->type() == AnalyserVariable::Type::CONSTANT) {
                methodBody += generateInitialisationCode(variable);
            } else if ((variable->type() == AnalyserVariable::Type::ALGEBRAIC)
                       && (variable->initialisingVariable() != nullptr)) {
                methodBody += generateInitialisationCode(variable);
            }
        }

        for (const auto &equation : mLockedModel->equations()) {
            if (equation->type() == AnalyserEquation::Type::TRUE_CONSTANT) {
                methodBody += generateEquationCode(equation, remainingEquations);
            }
        }

        for (const auto &state : mLockedModel->states()) {
            methodBody += generateInitialisationCode(state);
        }

        if (mLockedModel->hasExternalVariables()) {
            auto equations = mLockedModel->equations();
            std::vector<AnalyserEquationPtr> remainingExternalEquations;

            std::copy_if(equations.begin(), equations.end(),
                         std::back_inserter(remainingExternalEquations),
                         [](const AnalyserEquationPtr &equation) { return equation->type() == AnalyserEquation::Type::EXTERNAL; });

            for (const auto &equation : mLockedModel->equations()) {
                if (equation->type() == AnalyserEquation::Type::EXTERNAL) {
                    methodBody += generateEquationCode(equation, remainingExternalEquations);
                }
            }
        }

        mCode += newLineIfNeeded()
                 + replace(implementationInitialiseVariablesMethodString,
                           "[CODE]", generateMethodBodyCode(methodBody));
    }
}

void Generator::GeneratorImpl::addImplementationComputeComputedConstantsMethodCode(std::vector<AnalyserEquationPtr> &remainingEquations)
{
    if (!mLockedProfile->implementationComputeComputedConstantsMethodString().empty()) {
        std::string methodBody;

        for (const auto &equation : mLockedModel->equations()) {
            if (equation->type() == AnalyserEquation::Type::VARIABLE_BASED_CONSTANT) {
                methodBody += generateEquationCode(equation, remainingEquations);
            }
        }

        mCode += newLineIfNeeded()
                 + replace(mLockedProfile->implementationComputeComputedConstantsMethodString(),
                           "[CODE]", generateMethodBodyCode(methodBody));
    }
}

void Generator::GeneratorImpl::addImplementationComputeRatesMethodCode(std::vector<AnalyserEquationPtr> &remainingEquations)
{
    auto implementationComputeRatesMethodString = mLockedProfile->implementationComputeRatesMethodString(mLockedModel->hasExternalVariables());

    if (modelHasOdes()
        && !implementationComputeRatesMethodString.empty()) {
        std::string methodBody;

        for (const auto &equation : mLockedModel->equations()) {
            if (equation->type() == AnalyserEquation::Type::ODE) {
                methodBody += generateEquationCode(equation, remainingEquations);
            }
        }

        mCode += newLineIfNeeded()
                 + replace(implementationComputeRatesMethodString,
                           "[CODE]", generateMethodBodyCode(methodBody));
    }
}

void Generator::GeneratorImpl::addImplementationComputeVariablesMethodCode(std::vector<AnalyserEquationPtr> &remainingEquations)
{
    auto implementationComputeVariablesMethodString = mLockedProfile->implementationComputeVariablesMethodString(modelHasOdes(),
                                                                                                                 mLockedModel->hasExternalVariables());

    if (!implementationComputeVariablesMethodString.empty()) {
        std::string methodBody;
        auto equations = mLockedModel->equations();
        std::vector<AnalyserEquationPtr> newRemainingEquations {std::begin(equations), std::end(equations)};

        for (const auto &equation : equations) {
            if ((std::find(remainingEquations.begin(), remainingEquations.end(), equation) != remainingEquations.end())
                || isStateRateBasedAlgebraicEqnOrExternalEqn(equation)) {
                methodBody += generateEquationCode(equation, newRemainingEquations, true);
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

    // Get ourselves ready.

    mPimpl->reset();

    // Add code for the origin comment.

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

    // Add code for the NLA solver.

    auto equations = mPimpl->mLockedModel->equations();

    mPimpl->addRootFindingInfoObjectCode();
    mPimpl->addExternNlaSolveMethodCode();
    mPimpl->addNlaSystemsCode();

    // Add code for the implementation to initialise our variables.

    std::vector<AnalyserEquationPtr> remainingEquations {std::begin(equations), std::end(equations)};

    mPimpl->addImplementationInitialiseVariablesMethodCode(remainingEquations);

    // Add code for the implementation to compute our computed constants.

    mPimpl->addImplementationComputeComputedConstantsMethodCode(remainingEquations);

    // Add code for the implementation to compute our rates (and any variables
    // on which they depend).

    mPimpl->addImplementationComputeRatesMethodCode(remainingEquations);

    // Add code for the implementation to compute our variables.
    // Note: this method computes the remaining variables, i.e. the ones not
    //       needed to compute our rates, but also the variables that depend on
    //       the value of some states/rates and all the external variables.
    //       This method is typically called after having integrated a model,
    //       thus ensuring that variables that rely on the value of some
    //       states/rates are up to date.

    mPimpl->addImplementationComputeVariablesMethodCode(remainingEquations);

    mPimpl->resetLockedModelAndProfile();

    return mPimpl->mCode;
}

} // namespace libcellml

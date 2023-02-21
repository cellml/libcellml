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

#ifdef NAN
#    undef NAN
#endif

namespace libcellml {

GeneratorProfilePtr Generator::GeneratorImpl::profile() const
{
    if (mOwnedProfile != nullptr) {
        return mOwnedProfile;
    }

    return mProfile;
}

AnalyserVariablePtr Generator::GeneratorImpl::analyserVariable(const VariablePtr &variable) const
{
    // Find and return the analyser variable associated with the given variable.

    AnalyserVariablePtr res;
    auto modelVoi = mModel->voi();
    VariablePtr modelVoiVariable = (modelVoi != nullptr) ? modelVoi->variable() : nullptr;

    if ((modelVoiVariable != nullptr)
        && mModel->areEquivalentVariables(variable, modelVoiVariable)) {
        res = modelVoi;
    } else {
        for (const auto &modelState : mModel->states()) {
            if (mModel->areEquivalentVariables(variable, modelState->variable())) {
                res = modelState;

                break;
            }
        }

        if (res == nullptr) {
            // Normally, we would have:
            //
            //     for (const auto &modelVariable : mModel->variables()) {
            //         if (mModel->areEquivalentVariables(variable, modelVariable->variable())) {
            //             res = modelVariable;
            //
            //             break;
            //         }
            //     }
            //
            // but we always have variables, so llvm-cov will complain that the
            // false branch of our for loop is never reached. The below code is
            // a bit more verbose but at least it makes llvm-cov happy.

            auto modelVariables = mModel->variables();
            auto modelVariable = modelVariables.begin();

            do {
                if (mModel->areEquivalentVariables(variable, (*modelVariable)->variable())) {
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

    return ((astType == AnalyserEquationAst::Type::EQ) && mUsedProfile->hasEqOperator())
           || ((astType == AnalyserEquationAst::Type::NEQ) && mUsedProfile->hasNeqOperator())
           || ((astType == AnalyserEquationAst::Type::LT) && mUsedProfile->hasLtOperator())
           || ((astType == AnalyserEquationAst::Type::LEQ) && mUsedProfile->hasLeqOperator())
           || ((astType == AnalyserEquationAst::Type::GT) && mUsedProfile->hasGtOperator())
           || ((astType == AnalyserEquationAst::Type::GEQ) && mUsedProfile->hasGeqOperator());
}

bool Generator::GeneratorImpl::isAndOperator(const AnalyserEquationAstPtr &ast) const
{
    return (ast->type() == AnalyserEquationAst::Type::AND)
           && mUsedProfile->hasAndOperator();
}

bool Generator::GeneratorImpl::isOrOperator(const AnalyserEquationAstPtr &ast) const
{
    return (ast->type() == AnalyserEquationAst::Type::OR)
           && mUsedProfile->hasOrOperator();
}

bool Generator::GeneratorImpl::isXorOperator(const AnalyserEquationAstPtr &ast) const
{
    return (ast->type() == AnalyserEquationAst::Type::XOR)
           && mUsedProfile->hasXorOperator();
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
           && mUsedProfile->hasPowerOperator();
}

bool Generator::GeneratorImpl::isRootOperator(const AnalyserEquationAstPtr &ast) const
{
    return (ast->type() == AnalyserEquationAst::Type::ROOT)
           && mUsedProfile->hasPowerOperator();
}

bool Generator::GeneratorImpl::isPiecewiseStatement(const AnalyserEquationAstPtr &ast) const
{
    return (ast->type() == AnalyserEquationAst::Type::PIECEWISE)
           && mUsedProfile->hasConditionalOperator();
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
    std::string profileContents = generatorProfileAsString(mUsedProfile);

    return (mUsedProfile->profile() == GeneratorProfile::Profile::C) ?
               sha1(profileContents) != C_GENERATOR_PROFILE_SHA1 :
               sha1(profileContents) != PYTHON_GENERATOR_PROFILE_SHA1;
}

std::string Generator::GeneratorImpl::newLineIfNeeded()
{
    return mCode.empty() ? "" : "\n";
}

void Generator::GeneratorImpl::addOriginCommentCode()
{
    if (!mUsedProfile->commentString().empty()
        && !mUsedProfile->originCommentString().empty()) {
        std::string profileInformation = modifiedProfile() ?
                                             "a modified " :
                                             "the ";

        profileInformation += (mUsedProfile->profile() == GeneratorProfile::Profile::C) ?
                                  "C" :
                                  "Python";
        profileInformation += " profile of";

        mCode += replace(mUsedProfile->commentString(),
                         "[CODE]", replace(replace(mUsedProfile->originCommentString(), "[PROFILE_INFORMATION]", profileInformation), "[LIBCELLML_VERSION]", versionString()));
    }
}

void Generator::GeneratorImpl::addInterfaceHeaderCode()
{
    if (!mUsedProfile->interfaceHeaderString().empty()) {
        mCode += newLineIfNeeded()
                 + mUsedProfile->interfaceHeaderString();
    }
}

void Generator::GeneratorImpl::addImplementationHeaderCode()
{
    bool hasInterfaceFileName = mUsedProfile->implementationHeaderString().empty() ?
                                    false :
                                    (mUsedProfile->implementationHeaderString().find("[INTERFACE_FILE_NAME]") != std::string::npos);

    if (!mUsedProfile->implementationHeaderString().empty()
        && ((hasInterfaceFileName && !mUsedProfile->interfaceFileNameString().empty())
            || !hasInterfaceFileName)) {
        mCode += newLineIfNeeded()
                 + replace(mUsedProfile->implementationHeaderString(),
                           "[INTERFACE_FILE_NAME]", mUsedProfile->interfaceFileNameString());
    }
}

void Generator::GeneratorImpl::addVersionAndLibcellmlVersionCode(bool interface)
{
    std::string versionAndLibcellmlCode;

    if ((interface && !mUsedProfile->interfaceVersionString().empty())
        || (!interface && !mUsedProfile->implementationVersionString().empty())) {
        if (interface) {
            versionAndLibcellmlCode += mUsedProfile->interfaceVersionString();
        } else {
            if (modifiedProfile()) {
                std::regex regEx("([0-9]+\\.[0-9]+\\.[0-9]+)");

                versionAndLibcellmlCode += std::regex_replace(mUsedProfile->implementationVersionString(), regEx, "$1.post0");
            } else {
                versionAndLibcellmlCode += mUsedProfile->implementationVersionString();
            }
        }
    }

    if ((interface && !mUsedProfile->interfaceLibcellmlVersionString().empty())
        || (!interface && !mUsedProfile->implementationLibcellmlVersionString().empty())) {
        versionAndLibcellmlCode += interface ?
                                       mUsedProfile->interfaceLibcellmlVersionString() :
                                       replace(mUsedProfile->implementationLibcellmlVersionString(),
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

    if ((mModel->type() == AnalyserModel::Type::ODE)
        && ((interface && !mUsedProfile->interfaceStateCountString().empty())
            || (!interface && !mUsedProfile->implementationStateCountString().empty()))) {
        stateAndVariableCountCode += interface ?
                                         mUsedProfile->interfaceStateCountString() :
                                         replace(mUsedProfile->implementationStateCountString(),
                                                 "[STATE_COUNT]", std::to_string(mModel->stateCount()));
    }

    if ((interface && !mUsedProfile->interfaceVariableCountString().empty())
        || (!interface && !mUsedProfile->implementationVariableCountString().empty())) {
        stateAndVariableCountCode += interface ?
                                         mUsedProfile->interfaceVariableCountString() :
                                         replace(mUsedProfile->implementationVariableCountString(),
                                                 "[VARIABLE_COUNT]", std::to_string(mModel->variableCount()));
    }

    if (!stateAndVariableCountCode.empty()) {
        mCode += "\n";
    }

    mCode += stateAndVariableCountCode;
}

void Generator::GeneratorImpl::addVariableTypeObjectCode()
{
    auto variableTypeObjectString = mUsedProfile->variableTypeObjectString(mModel->type() == AnalyserModel::Type::ODE,
                                                                           mModel->hasExternalVariables());

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

    if (mModel->type() == AnalyserModel::Type::ODE) {
        updateVariableInfoSizes(componentSize, nameSize, unitsSize, mModel->voi());

        for (const auto &state : mModel->states()) {
            updateVariableInfoSizes(componentSize, nameSize, unitsSize, state);
        }
    }

    for (const auto &variable : mModel->variables()) {
        updateVariableInfoSizes(componentSize, nameSize, unitsSize, variable);
    }

    return replace(replace(replace(objectString,
                                   "[COMPONENT_SIZE]", std::to_string(componentSize)),
                           "[NAME_SIZE]", std::to_string(nameSize)),
                   "[UNITS_SIZE]", std::to_string(unitsSize));
}

void Generator::GeneratorImpl::addVariableInfoObjectCode()
{
    if (!mUsedProfile->variableInfoObjectString().empty()) {
        mCode += newLineIfNeeded()
                 + generateVariableInfoObjectCode(mUsedProfile->variableInfoObjectString());
    }
}

std::string Generator::GeneratorImpl::generateVariableInfoEntryCode(const std::string &name,
                                                                    const std::string &units,
                                                                    const std::string &component,
                                                                    const std::string &type) const
{
    return replace(replace(replace(replace(mUsedProfile->variableInfoEntryString(),
                                           "[NAME]", name),
                                   "[UNITS]", units),
                           "[COMPONENT]", component),
                   "[TYPE]", type);
}

void Generator::GeneratorImpl::addInterfaceVoiStateAndVariableInfoCode()
{
    std::string interfaceVoiStateAndVariableInfoCode;

    if ((mModel->type() == AnalyserModel::Type::ODE)
        && !mUsedProfile->interfaceVoiInfoString().empty()) {
        interfaceVoiStateAndVariableInfoCode += mUsedProfile->interfaceVoiInfoString();
    }

    if ((mModel->type() == AnalyserModel::Type::ODE)
        && !mUsedProfile->interfaceStateInfoString().empty()) {
        interfaceVoiStateAndVariableInfoCode += mUsedProfile->interfaceStateInfoString();
    }

    if (!mUsedProfile->interfaceVariableInfoString().empty()) {
        interfaceVoiStateAndVariableInfoCode += mUsedProfile->interfaceVariableInfoString();
    }

    if (!interfaceVoiStateAndVariableInfoCode.empty()) {
        mCode += "\n";
    }

    mCode += interfaceVoiStateAndVariableInfoCode;
}

void Generator::GeneratorImpl::addImplementationVoiInfoCode()
{
    if ((mModel->type() == AnalyserModel::Type::ODE)
        && !mUsedProfile->implementationVoiInfoString().empty()
        && !mUsedProfile->variableInfoEntryString().empty()
        && !mUsedProfile->variableOfIntegrationVariableTypeString().empty()) {
        auto voiVariable = mModel->voi()->variable();
        auto name = voiVariable->name();
        auto units = voiVariable->units()->name();
        auto component = owningComponent(voiVariable)->name();
        auto type = mUsedProfile->variableOfIntegrationVariableTypeString();

        mCode += newLineIfNeeded()
                 + replace(mUsedProfile->implementationVoiInfoString(),
                           "[CODE]", generateVariableInfoEntryCode(name, units, component, type));
    }
}

void Generator::GeneratorImpl::addImplementationStateInfoCode()
{
    if ((mModel->type() == AnalyserModel::Type::ODE)
        && !mUsedProfile->implementationStateInfoString().empty()
        && !mUsedProfile->variableInfoEntryString().empty()
        && !mUsedProfile->stateVariableTypeString().empty()
        && !mUsedProfile->arrayElementSeparatorString().empty()) {
        std::string infoElementsCode;
        auto type = mUsedProfile->stateVariableTypeString();

        for (const auto &state : mModel->states()) {
            if (!infoElementsCode.empty()) {
                infoElementsCode += mUsedProfile->arrayElementSeparatorString() + "\n";
            }

            auto stateVariable = state->variable();

            infoElementsCode += mUsedProfile->indentString()
                                + generateVariableInfoEntryCode(stateVariable->name(),
                                                                stateVariable->units()->name(),
                                                                owningComponent(stateVariable)->name(),
                                                                type);
        }

        infoElementsCode += "\n";

        mCode += newLineIfNeeded()
                 + replace(mUsedProfile->implementationStateInfoString(),
                           "[CODE]", infoElementsCode);
    }
}

void Generator::GeneratorImpl::addImplementationVariableInfoCode()
{
    if (!mUsedProfile->implementationVariableInfoString().empty()
        && !mUsedProfile->variableInfoEntryString().empty()
        && !mUsedProfile->arrayElementSeparatorString().empty()
        && !mUsedProfile->variableOfIntegrationVariableTypeString().empty()
        && !mUsedProfile->stateVariableTypeString().empty()
        && !mUsedProfile->constantVariableTypeString().empty()
        && !mUsedProfile->computedConstantVariableTypeString().empty()
        && !mUsedProfile->algebraicVariableTypeString().empty()
        && !mUsedProfile->externalVariableTypeString().empty()) {
        std::string infoElementsCode;

        for (const auto &variable : mModel->variables()) {
            if (!infoElementsCode.empty()) {
                infoElementsCode += mUsedProfile->arrayElementSeparatorString() + "\n";
            }

            std::string variableType;

            if (variable->type() == AnalyserVariable::Type::CONSTANT) {
                variableType = mUsedProfile->constantVariableTypeString();
            } else if (variable->type() == AnalyserVariable::Type::COMPUTED_CONSTANT) {
                variableType = mUsedProfile->computedConstantVariableTypeString();
            } else if (variable->type() == AnalyserVariable::Type::ALGEBRAIC) {
                variableType = mUsedProfile->algebraicVariableTypeString();
            } else { // AnalyserVariable::Type::EXTERNAL.
                variableType = mUsedProfile->externalVariableTypeString();
            }

            auto variableVariable = variable->variable();

            infoElementsCode += mUsedProfile->indentString()
                                + replace(replace(replace(replace(mUsedProfile->variableInfoEntryString(),
                                                                  "[NAME]", variableVariable->name()),
                                                          "[UNITS]", variableVariable->units()->name()),
                                                  "[COMPONENT]", owningComponent(variableVariable)->name()),
                                          "[TYPE]", variableType);
        }

        if (!infoElementsCode.empty()) {
            infoElementsCode += "\n";
        }

        mCode += newLineIfNeeded()
                 + replace(mUsedProfile->implementationVariableInfoString(),
                           "[CODE]", infoElementsCode);
    }
}

void Generator::GeneratorImpl::addArithmeticFunctionsCode()
{
    if (mModel->needEqFunction() && !mUsedProfile->hasEqOperator()
        && !mUsedProfile->eqFunctionString().empty()) {
        mCode += newLineIfNeeded()
                 + mUsedProfile->eqFunctionString();
    }

    if (mModel->needNeqFunction() && !mUsedProfile->hasNeqOperator()
        && !mUsedProfile->neqFunctionString().empty()) {
        mCode += newLineIfNeeded()
                 + mUsedProfile->neqFunctionString();
    }

    if (mModel->needLtFunction() && !mUsedProfile->hasLtOperator()
        && !mUsedProfile->ltFunctionString().empty()) {
        mCode += newLineIfNeeded()
                 + mUsedProfile->ltFunctionString();
    }

    if (mModel->needLeqFunction() && !mUsedProfile->hasLeqOperator()
        && !mUsedProfile->leqFunctionString().empty()) {
        mCode += newLineIfNeeded()
                 + mUsedProfile->leqFunctionString();
    }

    if (mModel->needGtFunction() && !mUsedProfile->hasGtOperator()
        && !mUsedProfile->gtFunctionString().empty()) {
        mCode += newLineIfNeeded()
                 + mUsedProfile->gtFunctionString();
    }

    if (mModel->needGeqFunction() && !mUsedProfile->hasGeqOperator()
        && !mUsedProfile->geqFunctionString().empty()) {
        mCode += newLineIfNeeded()
                 + mUsedProfile->geqFunctionString();
    }

    if (mModel->needAndFunction() && !mUsedProfile->hasAndOperator()
        && !mUsedProfile->andFunctionString().empty()) {
        mCode += newLineIfNeeded()
                 + mUsedProfile->andFunctionString();
    }

    if (mModel->needOrFunction() && !mUsedProfile->hasOrOperator()
        && !mUsedProfile->orFunctionString().empty()) {
        mCode += newLineIfNeeded()
                 + mUsedProfile->orFunctionString();
    }

    if (mModel->needXorFunction() && !mUsedProfile->hasXorOperator()
        && !mUsedProfile->xorFunctionString().empty()) {
        mCode += newLineIfNeeded()
                 + mUsedProfile->xorFunctionString();
    }

    if (mModel->needNotFunction() && !mUsedProfile->hasNotOperator()
        && !mUsedProfile->notFunctionString().empty()) {
        mCode += newLineIfNeeded()
                 + mUsedProfile->notFunctionString();
    }

    if (mModel->needMinFunction()
        && !mUsedProfile->minFunctionString().empty()) {
        mCode += newLineIfNeeded()
                 + mUsedProfile->minFunctionString();
    }

    if (mModel->needMaxFunction()
        && !mUsedProfile->maxFunctionString().empty()) {
        mCode += newLineIfNeeded()
                 + mUsedProfile->maxFunctionString();
    }
}

void Generator::GeneratorImpl::addTrigonometricFunctionsCode()
{
    if (mModel->needSecFunction()
        && !mUsedProfile->secFunctionString().empty()) {
        mCode += newLineIfNeeded()
                 + mUsedProfile->secFunctionString();
    }

    if (mModel->needCscFunction()
        && !mUsedProfile->cscFunctionString().empty()) {
        mCode += newLineIfNeeded()
                 + mUsedProfile->cscFunctionString();
    }

    if (mModel->needCotFunction()
        && !mUsedProfile->cotFunctionString().empty()) {
        mCode += newLineIfNeeded()
                 + mUsedProfile->cotFunctionString();
    }

    if (mModel->needSechFunction()
        && !mUsedProfile->sechFunctionString().empty()) {
        mCode += newLineIfNeeded()
                 + mUsedProfile->sechFunctionString();
    }

    if (mModel->needCschFunction()
        && !mUsedProfile->cschFunctionString().empty()) {
        mCode += newLineIfNeeded()
                 + mUsedProfile->cschFunctionString();
    }

    if (mModel->needCothFunction()
        && !mUsedProfile->cothFunctionString().empty()) {
        mCode += newLineIfNeeded()
                 + mUsedProfile->cothFunctionString();
    }

    if (mModel->needAsecFunction()
        && !mUsedProfile->asecFunctionString().empty()) {
        mCode += newLineIfNeeded()
                 + mUsedProfile->asecFunctionString();
    }

    if (mModel->needAcscFunction()
        && !mUsedProfile->acscFunctionString().empty()) {
        mCode += newLineIfNeeded()
                 + mUsedProfile->acscFunctionString();
    }

    if (mModel->needAcotFunction()
        && !mUsedProfile->acotFunctionString().empty()) {
        mCode += newLineIfNeeded()
                 + mUsedProfile->acotFunctionString();
    }

    if (mModel->needAsechFunction()
        && !mUsedProfile->asechFunctionString().empty()) {
        mCode += newLineIfNeeded()
                 + mUsedProfile->asechFunctionString();
    }

    if (mModel->needAcschFunction()
        && !mUsedProfile->acschFunctionString().empty()) {
        mCode += newLineIfNeeded()
                 + mUsedProfile->acschFunctionString();
    }

    if (mModel->needAcothFunction()
        && !mUsedProfile->acothFunctionString().empty()) {
        mCode += newLineIfNeeded()
                 + mUsedProfile->acothFunctionString();
    }
}

void Generator::GeneratorImpl::addInterfaceCreateDeleteArrayMethodsCode()
{
    std::string interfaceCreateDeleteArraysCode;

    if ((mModel->type() == AnalyserModel::Type::ODE)
        && !mUsedProfile->interfaceCreateStatesArrayMethodString().empty()) {
        interfaceCreateDeleteArraysCode += mUsedProfile->interfaceCreateStatesArrayMethodString();
    }

    if (!mUsedProfile->interfaceCreateVariablesArrayMethodString().empty()) {
        interfaceCreateDeleteArraysCode += mUsedProfile->interfaceCreateVariablesArrayMethodString();
    }

    if (!mUsedProfile->interfaceDeleteArrayMethodString().empty()) {
        interfaceCreateDeleteArraysCode += mUsedProfile->interfaceDeleteArrayMethodString();
    }

    if (!interfaceCreateDeleteArraysCode.empty()) {
        mCode += "\n";
    }

    mCode += interfaceCreateDeleteArraysCode;
}

void Generator::GeneratorImpl::addExternalVariableMethodTypeDefinitionCode()
{
    if (mModel->hasExternalVariables()) {
        auto externalVariableMethodTypeDefinitionString = mUsedProfile->externalVariableMethodTypeDefinitionString(mModel->type() == AnalyserModel::Type::ODE);

        if (!externalVariableMethodTypeDefinitionString.empty()) {
            mCode += "\n"
                     + externalVariableMethodTypeDefinitionString;
        }
    }
}

void Generator::GeneratorImpl::addImplementationCreateStatesArrayMethodCode()
{
    if ((mModel->type() == AnalyserModel::Type::ODE)
        && !mUsedProfile->implementationCreateStatesArrayMethodString().empty()) {
        mCode += newLineIfNeeded()
                 + mUsedProfile->implementationCreateStatesArrayMethodString();
    }
}

void Generator::GeneratorImpl::addImplementationCreateVariablesArrayMethodCode()
{
    if (!mUsedProfile->implementationCreateVariablesArrayMethodString().empty()) {
        mCode += newLineIfNeeded()
                 + mUsedProfile->implementationCreateVariablesArrayMethodString();
    }
}

void Generator::GeneratorImpl::addImplementationDeleteArrayMethodCode()
{
    if (!mUsedProfile->implementationDeleteArrayMethodString().empty()) {
        mCode += newLineIfNeeded()
                 + mUsedProfile->implementationDeleteArrayMethodString();
    }
}

std::string Generator::GeneratorImpl::generateMethodBodyCode(const std::string &methodBody) const
{
    return methodBody.empty() ?
               mUsedProfile->emptyMethodString().empty() ?
               "" :
               mUsedProfile->indentString() + mUsedProfile->emptyMethodString() :
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

    return mUsedProfile->variablesArrayString() + mUsedProfile->openArrayString() + index.str() + mUsedProfile->closeArrayString();
}

std::string Generator::GeneratorImpl::generateVariableNameCode(const VariablePtr &variable,
                                                               const AnalyserEquationAstPtr &ast) const
{
    // Generate some code for a variable name, but only if we have a model. If
    // we don't have a model, it means that we are using the generator from the
    // analyser, in which case we just want to return the original name of the
    // variable.

    if (mModel == nullptr) {
        return variable->name();
    }

    auto analyserVariable = Generator::GeneratorImpl::analyserVariable(variable);

    if (analyserVariable->type() == AnalyserVariable::Type::VARIABLE_OF_INTEGRATION) {
        return mUsedProfile->voiString();
    }

    std::string arrayName;

    if (analyserVariable->type() == AnalyserVariable::Type::STATE) {
        auto astParent = (ast != nullptr) ? ast->parent() : nullptr;

        arrayName = ((astParent != nullptr) && (astParent->type() == AnalyserEquationAst::Type::DIFF)) ?
                        mUsedProfile->ratesArrayString() :
                        mUsedProfile->statesArrayString();
    } else {
        arrayName = mUsedProfile->variablesArrayString();
    }

    std::ostringstream index;

    index << analyserVariable->index();

    return arrayName + mUsedProfile->openArrayString() + index.str() + mUsedProfile->closeArrayString();
}

std::string Generator::GeneratorImpl::generateOperatorCode(const std::string &op,
                                                           const AnalyserEquationAstPtr &ast)
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

std::string Generator::GeneratorImpl::generateMinusUnaryCode(const AnalyserEquationAstPtr &ast)
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

    return mUsedProfile->minusString() + code;
}

std::string Generator::GeneratorImpl::generateOneParameterFunctionCode(const std::string &function,
                                                                       const AnalyserEquationAstPtr &ast)
{
    return function + "(" + generateCode(ast->leftChild()) + ")";
}

std::string Generator::GeneratorImpl::generateTwoParameterFunctionCode(const std::string &function,
                                                                       const AnalyserEquationAstPtr &ast)
{
    return function + "(" + generateCode(ast->leftChild()) + ", " + generateCode(ast->rightChild()) + ")";
}

std::string Generator::GeneratorImpl::generatePiecewiseIfCode(const std::string &condition,
                                                              const std::string &value) const
{
    return replace(replace(mUsedProfile->hasConditionalOperator() ?
                               mUsedProfile->conditionalOperatorIfString() :
                               mUsedProfile->piecewiseIfString(),
                           "[CONDITION]", condition),
                   "[IF_STATEMENT]", value);
}

std::string Generator::GeneratorImpl::generatePiecewiseElseCode(const std::string &value) const
{
    return replace(mUsedProfile->hasConditionalOperator() ?
                       mUsedProfile->conditionalOperatorElseString() :
                       mUsedProfile->piecewiseElseString(),
                   "[ELSE_STATEMENT]", value);
}

std::string Generator::GeneratorImpl::generateCode(const AnalyserEquationAstPtr &ast)
{
    // Generate the code for the given AST.
    // Note: we don't handle the case of AnalyserEquationAst::Type::BVAR since
    //       we don't need to generate any code for it.

    std::string code;
    auto astType = ast->type();

    mUsedProfile = profile();

    if (astType == AnalyserEquationAst::Type::ASSIGNMENT) {
        code = generateOperatorCode(mUsedProfile->assignmentString(), ast);
    } else if (astType == AnalyserEquationAst::Type::EQ) {
        if (mUsedProfile->hasEqOperator()) {
            code = generateOperatorCode(mUsedProfile->eqString(), ast);
        } else {
            code = generateTwoParameterFunctionCode(mUsedProfile->eqString(), ast);
        }
    } else if (astType == AnalyserEquationAst::Type::NEQ) {
        if (mUsedProfile->hasNeqOperator()) {
            code = generateOperatorCode(mUsedProfile->neqString(), ast);
        } else {
            code = generateTwoParameterFunctionCode(mUsedProfile->neqString(), ast);
        }
    } else if (astType == AnalyserEquationAst::Type::LT) {
        if (mUsedProfile->hasLtOperator()) {
            code = generateOperatorCode(mUsedProfile->ltString(), ast);
        } else {
            code = generateTwoParameterFunctionCode(mUsedProfile->ltString(), ast);
        }
    } else if (astType == AnalyserEquationAst::Type::LEQ) {
        if (mUsedProfile->hasLeqOperator()) {
            code = generateOperatorCode(mUsedProfile->leqString(), ast);
        } else {
            code = generateTwoParameterFunctionCode(mUsedProfile->leqString(), ast);
        }
    } else if (astType == AnalyserEquationAst::Type::GT) {
        if (mUsedProfile->hasGtOperator()) {
            code = generateOperatorCode(mUsedProfile->gtString(), ast);
        } else {
            code = generateTwoParameterFunctionCode(mUsedProfile->gtString(), ast);
        }
    } else if (astType == AnalyserEquationAst::Type::GEQ) {
        if (mUsedProfile->hasGeqOperator()) {
            code = generateOperatorCode(mUsedProfile->geqString(), ast);
        } else {
            code = generateTwoParameterFunctionCode(mUsedProfile->geqString(), ast);
        }
    } else if (astType == AnalyserEquationAst::Type::AND) {
        if (mUsedProfile->hasAndOperator()) {
            code = generateOperatorCode(mUsedProfile->andString(), ast);
        } else {
            code = generateTwoParameterFunctionCode(mUsedProfile->andString(), ast);
        }
    } else if (astType == AnalyserEquationAst::Type::OR) {
        if (mUsedProfile->hasOrOperator()) {
            code = generateOperatorCode(mUsedProfile->orString(), ast);
        } else {
            code = generateTwoParameterFunctionCode(mUsedProfile->orString(), ast);
        }
    } else if (astType == AnalyserEquationAst::Type::XOR) {
        if (mUsedProfile->hasXorOperator()) {
            code = generateOperatorCode(mUsedProfile->xorString(), ast);
        } else {
            code = generateTwoParameterFunctionCode(mUsedProfile->xorString(), ast);
        }
    } else if (astType == AnalyserEquationAst::Type::NOT) {
        if (mUsedProfile->hasNotOperator()) {
            code = mUsedProfile->notString() + generateCode(ast->leftChild());
        } else {
            code = generateOneParameterFunctionCode(mUsedProfile->notString(), ast);
        }
    } else if (astType == AnalyserEquationAst::Type::PLUS) {
        if (ast->rightChild() != nullptr) {
            code = generateOperatorCode(mUsedProfile->plusString(), ast);
        } else {
            code = generateCode(ast->leftChild());
        }
    } else if (astType == AnalyserEquationAst::Type::MINUS) {
        if (ast->rightChild() != nullptr) {
            code = generateOperatorCode(mUsedProfile->minusString(), ast);
        } else {
            code = generateMinusUnaryCode(ast);
        }
    } else if (astType == AnalyserEquationAst::Type::TIMES) {
        code = generateOperatorCode(mUsedProfile->timesString(), ast);
    } else if (astType == AnalyserEquationAst::Type::DIVIDE) {
        code = generateOperatorCode(mUsedProfile->divideString(), ast);
    } else if (astType == AnalyserEquationAst::Type::POWER) {
        auto stringValue = generateCode(ast->rightChild());
        bool validConversion;
        double doubleValue = convertToDouble(stringValue, &validConversion);

        if (validConversion && areEqual(doubleValue, 0.5)) {
            code = generateOneParameterFunctionCode(mUsedProfile->squareRootString(), ast);
        } else if (validConversion && areEqual(doubleValue, 2.0)
                   && !mUsedProfile->squareString().empty()) {
            code = generateOneParameterFunctionCode(mUsedProfile->squareString(), ast);
        } else {
            code = mUsedProfile->hasPowerOperator() ?
                       generateOperatorCode(mUsedProfile->powerString(), ast) :
                       mUsedProfile->powerString() + "(" + generateCode(ast->leftChild()) + ", " + stringValue + ")";
        }
    } else if (astType == AnalyserEquationAst::Type::ROOT) {
        auto astRightChild = ast->rightChild();

        if (astRightChild != nullptr) {
            auto astLeftChild = ast->leftChild();

            bool validConversion;
            double doubleValue = convertToDouble(generateCode(astLeftChild), &validConversion);

            if (validConversion && areEqual(doubleValue, 2.0)) {
                code = mUsedProfile->squareRootString() + "(" + generateCode(astRightChild) + ")";
            } else {
                if (mUsedProfile->hasPowerOperator()) {
                    code = generateOperatorCode(mUsedProfile->powerString(), ast);
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

                    code = mUsedProfile->powerString() + "(" + generateCode(astRightChild) + ", " + generateOperatorCode(mUsedProfile->divideString(), rootValueAst) + ")";
                }
            }
        } else {
            code = generateOneParameterFunctionCode(mUsedProfile->squareRootString(), ast);
        }
    } else if (astType == AnalyserEquationAst::Type::ABS) {
        code = generateOneParameterFunctionCode(mUsedProfile->absoluteValueString(), ast);
    } else if (astType == AnalyserEquationAst::Type::EXP) {
        code = generateOneParameterFunctionCode(mUsedProfile->exponentialString(), ast);
    } else if (astType == AnalyserEquationAst::Type::LN) {
        code = generateOneParameterFunctionCode(mUsedProfile->naturalLogarithmString(), ast);
    } else if (astType == AnalyserEquationAst::Type::LOG) {
        auto astRightChild = ast->rightChild();

        if (astRightChild != nullptr) {
            auto stringValue = generateCode(ast->leftChild());
            bool validConversion;
            double doubleValue = convertToDouble(stringValue, &validConversion);

            if (validConversion && areEqual(doubleValue, 10.0)) {
                code = mUsedProfile->commonLogarithmString() + "(" + generateCode(astRightChild) + ")";
            } else {
                code = mUsedProfile->naturalLogarithmString() + "(" + generateCode(astRightChild) + ")/" + mUsedProfile->naturalLogarithmString() + "(" + stringValue + ")";
            }
        } else {
            code = generateOneParameterFunctionCode(mUsedProfile->commonLogarithmString(), ast);
        }
    } else if (astType == AnalyserEquationAst::Type::CEILING) {
        code = generateOneParameterFunctionCode(mUsedProfile->ceilingString(), ast);
    } else if (astType == AnalyserEquationAst::Type::FLOOR) {
        code = generateOneParameterFunctionCode(mUsedProfile->floorString(), ast);
    } else if (astType == AnalyserEquationAst::Type::MIN) {
        code = generateTwoParameterFunctionCode(mUsedProfile->minString(), ast);
    } else if (astType == AnalyserEquationAst::Type::MAX) {
        code = generateTwoParameterFunctionCode(mUsedProfile->maxString(), ast);
    } else if (astType == AnalyserEquationAst::Type::REM) {
        code = generateTwoParameterFunctionCode(mUsedProfile->remString(), ast);
    } else if (astType == AnalyserEquationAst::Type::DIFF) {
        code = generateCode(ast->rightChild());
    } else if (astType == AnalyserEquationAst::Type::SIN) {
        code = generateOneParameterFunctionCode(mUsedProfile->sinString(), ast);
    } else if (astType == AnalyserEquationAst::Type::COS) {
        code = generateOneParameterFunctionCode(mUsedProfile->cosString(), ast);
    } else if (astType == AnalyserEquationAst::Type::TAN) {
        code = generateOneParameterFunctionCode(mUsedProfile->tanString(), ast);
    } else if (astType == AnalyserEquationAst::Type::SEC) {
        code = generateOneParameterFunctionCode(mUsedProfile->secString(), ast);
    } else if (astType == AnalyserEquationAst::Type::CSC) {
        code = generateOneParameterFunctionCode(mUsedProfile->cscString(), ast);
    } else if (astType == AnalyserEquationAst::Type::COT) {
        code = generateOneParameterFunctionCode(mUsedProfile->cotString(), ast);
    } else if (astType == AnalyserEquationAst::Type::SINH) {
        code = generateOneParameterFunctionCode(mUsedProfile->sinhString(), ast);
    } else if (astType == AnalyserEquationAst::Type::COSH) {
        code = generateOneParameterFunctionCode(mUsedProfile->coshString(), ast);
    } else if (astType == AnalyserEquationAst::Type::TANH) {
        code = generateOneParameterFunctionCode(mUsedProfile->tanhString(), ast);
    } else if (astType == AnalyserEquationAst::Type::SECH) {
        code = generateOneParameterFunctionCode(mUsedProfile->sechString(), ast);
    } else if (astType == AnalyserEquationAst::Type::CSCH) {
        code = generateOneParameterFunctionCode(mUsedProfile->cschString(), ast);
    } else if (astType == AnalyserEquationAst::Type::COTH) {
        code = generateOneParameterFunctionCode(mUsedProfile->cothString(), ast);
    } else if (astType == AnalyserEquationAst::Type::ASIN) {
        code = generateOneParameterFunctionCode(mUsedProfile->asinString(), ast);
    } else if (astType == AnalyserEquationAst::Type::ACOS) {
        code = generateOneParameterFunctionCode(mUsedProfile->acosString(), ast);
    } else if (astType == AnalyserEquationAst::Type::ATAN) {
        code = generateOneParameterFunctionCode(mUsedProfile->atanString(), ast);
    } else if (astType == AnalyserEquationAst::Type::ASEC) {
        code = generateOneParameterFunctionCode(mUsedProfile->asecString(), ast);
    } else if (astType == AnalyserEquationAst::Type::ACSC) {
        code = generateOneParameterFunctionCode(mUsedProfile->acscString(), ast);
    } else if (astType == AnalyserEquationAst::Type::ACOT) {
        code = generateOneParameterFunctionCode(mUsedProfile->acotString(), ast);
    } else if (astType == AnalyserEquationAst::Type::ASINH) {
        code = generateOneParameterFunctionCode(mUsedProfile->asinhString(), ast);
    } else if (astType == AnalyserEquationAst::Type::ACOSH) {
        code = generateOneParameterFunctionCode(mUsedProfile->acoshString(), ast);
    } else if (astType == AnalyserEquationAst::Type::ATANH) {
        code = generateOneParameterFunctionCode(mUsedProfile->atanhString(), ast);
    } else if (astType == AnalyserEquationAst::Type::ASECH) {
        code = generateOneParameterFunctionCode(mUsedProfile->asechString(), ast);
    } else if (astType == AnalyserEquationAst::Type::ACSCH) {
        code = generateOneParameterFunctionCode(mUsedProfile->acschString(), ast);
    } else if (astType == AnalyserEquationAst::Type::ACOTH) {
        code = generateOneParameterFunctionCode(mUsedProfile->acothString(), ast);
    } else if (astType == AnalyserEquationAst::Type::PIECEWISE) {
        auto astRightChild = ast->rightChild();

        if (astRightChild != nullptr) {
            if (astRightChild->type() == AnalyserEquationAst::Type::PIECE) {
                code = generateCode(ast->leftChild()) + generatePiecewiseElseCode(generateCode(astRightChild) + generatePiecewiseElseCode(mUsedProfile->nanString()));
            } else {
                code = generateCode(ast->leftChild()) + generatePiecewiseElseCode(generateCode(astRightChild));
            }
        } else {
            code = generateCode(ast->leftChild()) + generatePiecewiseElseCode(mUsedProfile->nanString());
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
        code = mUsedProfile->trueString();
    } else if (astType == AnalyserEquationAst::Type::FALSE) {
        code = mUsedProfile->falseString();
    } else if (astType == AnalyserEquationAst::Type::E) {
        code = mUsedProfile->eString();
    } else if (astType == AnalyserEquationAst::Type::PI) {
        code = mUsedProfile->piString();
    } else if (astType == AnalyserEquationAst::Type::INF) {
        code = mUsedProfile->infString();
    } else { // AnalyserEquationAst::Type::NAN.
        code = mUsedProfile->nanString();
    }

    return code;
}

std::string Generator::GeneratorImpl::generateInitialisationCode(const AnalyserVariablePtr &variable) const
{
    auto initialisingVariable = variable->initialisingVariable();
    auto scalingFactor = Generator::GeneratorImpl::scalingFactor(initialisingVariable);
    std::string scalingFactorCode;

    if (!areNearlyEqual(scalingFactor, 1.0)) {
        scalingFactorCode = generateDoubleCode(convertToString(1.0 / scalingFactor)) + mUsedProfile->timesString();
    }

    return mUsedProfile->indentString() + generateVariableNameCode(variable->variable()) + " = "
           + scalingFactorCode + generateDoubleOrConstantVariableNameCode(initialisingVariable)
           + mUsedProfile->commandSeparatorString() + "\n";
}

std::string Generator::GeneratorImpl::generateEquationCode(const AnalyserEquationPtr &equation,
                                                           std::vector<AnalyserEquationPtr> &remainingEquations,
                                                           bool forComputeVariables)
{
    std::string res;

    if (std::find(remainingEquations.begin(), remainingEquations.end(), equation) != remainingEquations.end()) {
        if ((equation->type() == AnalyserEquation::Type::RATE)
            || (equation->type() == AnalyserEquation::Type::ALGEBRAIC)
            || (equation->type() == AnalyserEquation::Type::EXTERNAL)) {
            for (const auto &dependency : equation->dependencies()) {
                if ((dependency->type() != AnalyserEquation::Type::RATE)
                    && (!forComputeVariables
                        || ((dependency->type() == AnalyserEquation::Type::ALGEBRAIC)
                            && dependency->isStateRateBased())
                        || (dependency->type() == AnalyserEquation::Type::EXTERNAL))) {
                    res += generateEquationCode(dependency, remainingEquations, forComputeVariables);
                }
            }
        }

        if (equation->type() == AnalyserEquation::Type::EXTERNAL) {
            std::ostringstream index;
            auto variable = equation->variable();

            index << variable->index();

            res += mUsedProfile->indentString() + generateVariableNameCode(variable->variable()) + " = "
                   + replace(mUsedProfile->externalVariableMethodCallString(mModel->type() == AnalyserModel::Type::ODE),
                             "[INDEX]", index.str())
                   + mUsedProfile->commandSeparatorString() + "\n";
        } else {
            res += mUsedProfile->indentString() + generateCode(equation->ast()) + mUsedProfile->commandSeparatorString() + "\n";
        }

        remainingEquations.erase(std::find(remainingEquations.begin(), remainingEquations.end(), equation));
    }

    return res;
}

void Generator::GeneratorImpl::addInterfaceComputeModelMethodsCode()
{
    auto interfaceInitialiseVariablesMethodString = mUsedProfile->interfaceInitialiseVariablesMethodString(mModel->type() == AnalyserModel::Type::ODE,
                                                                                                           mModel->hasExternalVariables());
    std::string interfaceComputeModelMethodsCode;

    if (!interfaceInitialiseVariablesMethodString.empty()) {
        interfaceComputeModelMethodsCode += interfaceInitialiseVariablesMethodString;
    }

    if (!mUsedProfile->interfaceComputeComputedConstantsMethodString().empty()) {
        interfaceComputeModelMethodsCode += mUsedProfile->interfaceComputeComputedConstantsMethodString();
    }

    auto interfaceComputeRatesMethodString = mUsedProfile->interfaceComputeRatesMethodString(mModel->hasExternalVariables());

    if ((mModel->type() == AnalyserModel::Type::ODE)
        && !interfaceComputeRatesMethodString.empty()) {
        interfaceComputeModelMethodsCode += interfaceComputeRatesMethodString;
    }

    auto interfaceComputeVariablesMethodString = mUsedProfile->interfaceComputeVariablesMethodString(mModel->type() == AnalyserModel::Type::ODE,
                                                                                                     mModel->hasExternalVariables());

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
    auto implementationInitialiseVariablesMethodString = mUsedProfile->implementationInitialiseVariablesMethodString(mModel->type() == AnalyserModel::Type::ODE,
                                                                                                                     mModel->hasExternalVariables());

    if (!implementationInitialiseVariablesMethodString.empty()) {
        std::string methodBody;

        for (const auto &variable : mModel->variables()) {
            if (variable->type() == AnalyserVariable::Type::CONSTANT) {
                methodBody += generateInitialisationCode(variable);
            }
        }

        for (const auto &equation : mModel->equations()) {
            if (equation->type() == AnalyserEquation::Type::TRUE_CONSTANT) {
                methodBody += generateEquationCode(equation, remainingEquations);
            }
        }

        for (const auto &state : mModel->states()) {
            methodBody += generateInitialisationCode(state);
        }

        if (mModel->hasExternalVariables()) {
            auto equations = mModel->equations();
            std::vector<AnalyserEquationPtr> remainingExternalEquations;

            std::copy_if(equations.begin(), equations.end(),
                         std::back_inserter(remainingExternalEquations),
                         [](const AnalyserEquationPtr &equation) { return equation->type() == AnalyserEquation::Type::EXTERNAL; });

            for (const auto &equation : mModel->equations()) {
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
    if (!mUsedProfile->implementationComputeComputedConstantsMethodString().empty()) {
        std::string methodBody;

        for (const auto &equation : mModel->equations()) {
            if (equation->type() == AnalyserEquation::Type::VARIABLE_BASED_CONSTANT) {
                methodBody += generateEquationCode(equation, remainingEquations);
            }
        }

        mCode += newLineIfNeeded()
                 + replace(mUsedProfile->implementationComputeComputedConstantsMethodString(),
                           "[CODE]", generateMethodBodyCode(methodBody));
    }
}

void Generator::GeneratorImpl::addImplementationComputeRatesMethodCode(std::vector<AnalyserEquationPtr> &remainingEquations)
{
    auto implementationComputeRatesMethodString = mUsedProfile->implementationComputeRatesMethodString(mModel->hasExternalVariables());

    if ((mModel->type() == AnalyserModel::Type::ODE)
        && !implementationComputeRatesMethodString.empty()) {
        std::string methodBody;

        for (const auto &equation : mModel->equations()) {
            if (equation->type() == AnalyserEquation::Type::RATE) {
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
    auto implementationComputeVariablesMethodString = mUsedProfile->implementationComputeVariablesMethodString(mModel->type() == AnalyserModel::Type::ODE,
                                                                                                               mModel->hasExternalVariables());

    if (!implementationComputeVariablesMethodString.empty()) {
        std::string methodBody;
        auto equations = mModel->equations();
        std::vector<AnalyserEquationPtr> newRemainingEquations {std::begin(equations), std::end(equations)};

        for (const auto &equation : equations) {
            if ((std::find(remainingEquations.begin(), remainingEquations.end(), equation) != remainingEquations.end())
                || ((equation->type() == AnalyserEquation::Type::ALGEBRAIC)
                    && equation->isStateRateBased())
                || (equation->type() == AnalyserEquation::Type::EXTERNAL)) {
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
    return mPimpl->profile();
}

void Generator::setProfile(const GeneratorProfilePtr &profile)
{
    mPimpl->mOwnedProfile = nullptr;
    mPimpl->mProfile = profile;
}

AnalyserModelPtr Generator::model()
{
    return mPimpl->mModel;
}

void Generator::setModel(const AnalyserModelPtr &model)
{
    mPimpl->mModel = model;
}

std::string Generator::interfaceCode()
{
    mPimpl->mUsedProfile = profile();

    if ((mPimpl->mModel == nullptr)
        || (mPimpl->mUsedProfile == nullptr)
        || !mPimpl->mModel->isValid()
        || !mPimpl->mUsedProfile->hasInterface()) {
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

    return mPimpl->mCode;
}

std::string Generator::implementationCode()
{
    mPimpl->mUsedProfile = profile();

    if ((mPimpl->mModel == nullptr)
        || (mPimpl->mUsedProfile == nullptr)
        || !mPimpl->mModel->isValid()) {
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

    if (!mPimpl->mUsedProfile->hasInterface()) {
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

    // Add code for the implementation to initialise our variables.

    auto equations = mPimpl->mModel->equations();
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

    return mPimpl->mCode;
}

} // namespace libcellml

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

#include "libcellml/analyservariable.h"
#include "libcellml/version.h"

#include "commonutils.h"
#include "generator_p.h"
#include "generatorinterpreter_p.h"
#include "generatorprofilesha1values.h"
#include "generatorprofiletools.h"

namespace libcellml {

void Generator::GeneratorImpl::reset()
{
    mCode = {};
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

        mCode += replace(mProfile->commentString(),
                         "[CODE]", replace(replace(mProfile->originCommentString(), "[PROFILE_INFORMATION]", profileInformation), "[LIBCELLML_VERSION]", versionString()));
    }
}

void Generator::GeneratorImpl::addInterfaceHeaderCode()
{
    if (!mProfile->interfaceHeaderString().empty()) {
        mCode += newLineIfNotEmpty(mCode)
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
        mCode += newLineIfNotEmpty(mCode)
                 + replace(mProfile->implementationHeaderString(),
                           "[INTERFACE_FILE_NAME]", mProfile->interfaceFileNameString());
    }
}

void Generator::GeneratorImpl::addVersionAndLibcellmlVersionCode(bool interface)
{
    std::string versionAndLibcellmlCode;

    if ((interface && !mProfile->interfaceVersionString().empty())
        || (!interface && !mProfile->implementationVersionString().empty())) {
        if (interface) {
            versionAndLibcellmlCode += mProfile->interfaceVersionString();
        } else {
            if (modifiedProfile()) {
                static const std::regex regEx("([0-9]+\\.[0-9]+\\.[0-9]+)");

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

    if (mModelHasOdes
        && ((interface && !mProfile->interfaceStateCountString().empty())
            || (!interface && !mProfile->implementationStateCountString().empty()))) {
        stateAndVariableCountCode += interface ?
                                         mProfile->interfaceStateCountString() :
                                         replace(mProfile->implementationStateCountString(),
                                                 "[STATE_COUNT]", std::to_string(mModel->stateCount()));
    }

    if ((interface && !mProfile->interfaceVariableCountString().empty())
        || (!interface && !mProfile->implementationVariableCountString().empty())) {
        stateAndVariableCountCode += interface ?
                                         mProfile->interfaceVariableCountString() :
                                         replace(mProfile->implementationVariableCountString(),
                                                 "[VARIABLE_COUNT]", std::to_string(mModel->variableCount()));
    }

    if (!stateAndVariableCountCode.empty()) {
        mCode += "\n";
    }

    mCode += stateAndVariableCountCode;
}

void Generator::GeneratorImpl::addVariableTypeObjectCode()
{
    auto variableTypeObjectString = mProfile->variableTypeObjectString(mModelHasOdes,
                                                                       mModel->hasExternalVariables());

    if (!variableTypeObjectString.empty()) {
        mCode += newLineIfNotEmpty(mCode)
                 + variableTypeObjectString;
    }
}

std::string Generator::GeneratorImpl::generateVariableInfoObjectCode(const std::string &objectString) const
{
    size_t componentSize = 0;
    size_t nameSize = 0;
    size_t unitsSize = 0;

    if (mModelHasOdes) {
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
    if (!mProfile->variableInfoObjectString().empty()) {
        mCode += newLineIfNotEmpty(mCode)
                 + generateVariableInfoObjectCode(mProfile->variableInfoObjectString());
    }
}

std::string Generator::GeneratorImpl::generateVariableInfoEntryCode(const std::string &name,
                                                                    const std::string &units,
                                                                    const std::string &component,
                                                                    const std::string &type) const
{
    return replace(replace(replace(replace(mProfile->variableInfoEntryString(),
                                           "[NAME]", name),
                                   "[UNITS]", units),
                           "[COMPONENT]", component),
                   "[TYPE]", type);
}

void Generator::GeneratorImpl::addInterfaceVoiStateAndVariableInfoCode()
{
    std::string interfaceVoiStateAndVariableInfoCode;

    if (mModelHasOdes
        && !mProfile->interfaceVoiInfoString().empty()) {
        interfaceVoiStateAndVariableInfoCode += mProfile->interfaceVoiInfoString();
    }

    if (mModelHasOdes
        && !mProfile->interfaceStateInfoString().empty()) {
        interfaceVoiStateAndVariableInfoCode += mProfile->interfaceStateInfoString();
    }

    if (!mProfile->interfaceVariableInfoString().empty()) {
        interfaceVoiStateAndVariableInfoCode += mProfile->interfaceVariableInfoString();
    }

    if (!interfaceVoiStateAndVariableInfoCode.empty()) {
        mCode += "\n";
    }

    mCode += interfaceVoiStateAndVariableInfoCode;
}

void Generator::GeneratorImpl::addImplementationVoiInfoCode()
{
    if (mModelHasOdes
        && !mProfile->implementationVoiInfoString().empty()
        && !mProfile->variableInfoEntryString().empty()
        && !mProfile->variableOfIntegrationVariableTypeString().empty()) {
        auto voiVariable = mModel->voi()->variable();
        auto name = voiVariable->name();
        auto units = voiVariable->units()->name();
        auto component = owningComponent(voiVariable)->name();
        auto type = mProfile->variableOfIntegrationVariableTypeString();

        mCode += newLineIfNotEmpty(mCode)
                 + replace(mProfile->implementationVoiInfoString(),
                           "[CODE]", generateVariableInfoEntryCode(name, units, component, type));
    }
}

void Generator::GeneratorImpl::addImplementationStateInfoCode()
{
    if (mModelHasOdes
        && !mProfile->implementationStateInfoString().empty()
        && !mProfile->variableInfoEntryString().empty()
        && !mProfile->stateVariableTypeString().empty()
        && !mProfile->arrayElementSeparatorString().empty()) {
        std::string infoElementsCode;
        auto type = mProfile->stateVariableTypeString();

        for (const auto &state : mModel->states()) {
            if (!infoElementsCode.empty()) {
                infoElementsCode += mProfile->arrayElementSeparatorString() + "\n";
            }

            auto stateVariable = state->variable();

            infoElementsCode += mProfile->indentString()
                                + generateVariableInfoEntryCode(stateVariable->name(),
                                                                stateVariable->units()->name(),
                                                                owningComponent(stateVariable)->name(),
                                                                type);
        }

        infoElementsCode += "\n";

        mCode += newLineIfNotEmpty(mCode)
                 + replace(mProfile->implementationStateInfoString(),
                           "[CODE]", infoElementsCode);
    }
}

void Generator::GeneratorImpl::addImplementationVariableInfoCode()
{
    if (!mProfile->implementationVariableInfoString().empty()
        && !mProfile->variableInfoEntryString().empty()
        && !mProfile->arrayElementSeparatorString().empty()
        && !mProfile->variableOfIntegrationVariableTypeString().empty()
        && !mProfile->stateVariableTypeString().empty()
        && !mProfile->constantVariableTypeString().empty()
        && !mProfile->computedConstantVariableTypeString().empty()
        && !mProfile->algebraicVariableTypeString().empty()
        && !mProfile->externalVariableTypeString().empty()) {
        std::string infoElementsCode;

        for (const auto &variable : mModel->variables()) {
            if (!infoElementsCode.empty()) {
                infoElementsCode += mProfile->arrayElementSeparatorString() + "\n";
            }

            std::string variableType;

            switch (variable->type()) {
            case AnalyserVariable::Type::CONSTANT:
                variableType = mProfile->constantVariableTypeString();

                break;
            case AnalyserVariable::Type::COMPUTED_CONSTANT:
                variableType = mProfile->computedConstantVariableTypeString();

                break;
            case AnalyserVariable::Type::ALGEBRAIC:
                variableType = mProfile->algebraicVariableTypeString();

                break;
            default: // AnalyserVariable::Type::EXTERNAL.
                variableType = mProfile->externalVariableTypeString();

                break;
            }

            auto variableVariable = variable->variable();

            infoElementsCode += mProfile->indentString()
                                + replace(replace(replace(replace(mProfile->variableInfoEntryString(),
                                                                  "[NAME]", variableVariable->name()),
                                                          "[UNITS]", variableVariable->units()->name()),
                                                  "[COMPONENT]", owningComponent(variableVariable)->name()),
                                          "[TYPE]", variableType);
        }

        if (!infoElementsCode.empty()) {
            infoElementsCode += "\n";
        }

        mCode += newLineIfNotEmpty(mCode)
                 + replace(mProfile->implementationVariableInfoString(),
                           "[CODE]", infoElementsCode);
    }
}

void Generator::GeneratorImpl::addArithmeticFunctionsCode()
{
    if (mModel->needEqFunction() && !mProfile->hasEqOperator()
        && !mProfile->eqFunctionString().empty()) {
        mCode += newLineIfNotEmpty(mCode)
                 + mProfile->eqFunctionString();
    }

    if (mModel->needNeqFunction() && !mProfile->hasNeqOperator()
        && !mProfile->neqFunctionString().empty()) {
        mCode += newLineIfNotEmpty(mCode)
                 + mProfile->neqFunctionString();
    }

    if (mModel->needLtFunction() && !mProfile->hasLtOperator()
        && !mProfile->ltFunctionString().empty()) {
        mCode += newLineIfNotEmpty(mCode)
                 + mProfile->ltFunctionString();
    }

    if (mModel->needLeqFunction() && !mProfile->hasLeqOperator()
        && !mProfile->leqFunctionString().empty()) {
        mCode += newLineIfNotEmpty(mCode)
                 + mProfile->leqFunctionString();
    }

    if (mModel->needGtFunction() && !mProfile->hasGtOperator()
        && !mProfile->gtFunctionString().empty()) {
        mCode += newLineIfNotEmpty(mCode)
                 + mProfile->gtFunctionString();
    }

    if (mModel->needGeqFunction() && !mProfile->hasGeqOperator()
        && !mProfile->geqFunctionString().empty()) {
        mCode += newLineIfNotEmpty(mCode)
                 + mProfile->geqFunctionString();
    }

    if (mModel->needAndFunction() && !mProfile->hasAndOperator()
        && !mProfile->andFunctionString().empty()) {
        mCode += newLineIfNotEmpty(mCode)
                 + mProfile->andFunctionString();
    }

    if (mModel->needOrFunction() && !mProfile->hasOrOperator()
        && !mProfile->orFunctionString().empty()) {
        mCode += newLineIfNotEmpty(mCode)
                 + mProfile->orFunctionString();
    }

    if (mModel->needXorFunction() && !mProfile->hasXorOperator()
        && !mProfile->xorFunctionString().empty()) {
        mCode += newLineIfNotEmpty(mCode)
                 + mProfile->xorFunctionString();
    }

    if (mModel->needNotFunction() && !mProfile->hasNotOperator()
        && !mProfile->notFunctionString().empty()) {
        mCode += newLineIfNotEmpty(mCode)
                 + mProfile->notFunctionString();
    }

    if (mModel->needMinFunction()
        && !mProfile->minFunctionString().empty()) {
        mCode += newLineIfNotEmpty(mCode)
                 + mProfile->minFunctionString();
    }

    if (mModel->needMaxFunction()
        && !mProfile->maxFunctionString().empty()) {
        mCode += newLineIfNotEmpty(mCode)
                 + mProfile->maxFunctionString();
    }
}

void Generator::GeneratorImpl::addTrigonometricFunctionsCode()
{
    if (mModel->needSecFunction()
        && !mProfile->secFunctionString().empty()) {
        mCode += newLineIfNotEmpty(mCode)
                 + mProfile->secFunctionString();
    }

    if (mModel->needCscFunction()
        && !mProfile->cscFunctionString().empty()) {
        mCode += newLineIfNotEmpty(mCode)
                 + mProfile->cscFunctionString();
    }

    if (mModel->needCotFunction()
        && !mProfile->cotFunctionString().empty()) {
        mCode += newLineIfNotEmpty(mCode)
                 + mProfile->cotFunctionString();
    }

    if (mModel->needSechFunction()
        && !mProfile->sechFunctionString().empty()) {
        mCode += newLineIfNotEmpty(mCode)
                 + mProfile->sechFunctionString();
    }

    if (mModel->needCschFunction()
        && !mProfile->cschFunctionString().empty()) {
        mCode += newLineIfNotEmpty(mCode)
                 + mProfile->cschFunctionString();
    }

    if (mModel->needCothFunction()
        && !mProfile->cothFunctionString().empty()) {
        mCode += newLineIfNotEmpty(mCode)
                 + mProfile->cothFunctionString();
    }

    if (mModel->needAsecFunction()
        && !mProfile->asecFunctionString().empty()) {
        mCode += newLineIfNotEmpty(mCode)
                 + mProfile->asecFunctionString();
    }

    if (mModel->needAcscFunction()
        && !mProfile->acscFunctionString().empty()) {
        mCode += newLineIfNotEmpty(mCode)
                 + mProfile->acscFunctionString();
    }

    if (mModel->needAcotFunction()
        && !mProfile->acotFunctionString().empty()) {
        mCode += newLineIfNotEmpty(mCode)
                 + mProfile->acotFunctionString();
    }

    if (mModel->needAsechFunction()
        && !mProfile->asechFunctionString().empty()) {
        mCode += newLineIfNotEmpty(mCode)
                 + mProfile->asechFunctionString();
    }

    if (mModel->needAcschFunction()
        && !mProfile->acschFunctionString().empty()) {
        mCode += newLineIfNotEmpty(mCode)
                 + mProfile->acschFunctionString();
    }

    if (mModel->needAcothFunction()
        && !mProfile->acothFunctionString().empty()) {
        mCode += newLineIfNotEmpty(mCode)
                 + mProfile->acothFunctionString();
    }
}

void Generator::GeneratorImpl::addInterfaceCreateDeleteArrayMethodsCode()
{
    std::string interfaceCreateDeleteArraysCode;

    if (mModelHasOdes
        && !mProfile->interfaceCreateStatesArrayMethodString().empty()) {
        interfaceCreateDeleteArraysCode += mProfile->interfaceCreateStatesArrayMethodString();
    }

    if (!mProfile->interfaceCreateVariablesArrayMethodString().empty()) {
        interfaceCreateDeleteArraysCode += mProfile->interfaceCreateVariablesArrayMethodString();
    }

    if (!mProfile->interfaceDeleteArrayMethodString().empty()) {
        interfaceCreateDeleteArraysCode += mProfile->interfaceDeleteArrayMethodString();
    }

    if (!interfaceCreateDeleteArraysCode.empty()) {
        mCode += "\n";
    }

    mCode += interfaceCreateDeleteArraysCode;
}

void Generator::GeneratorImpl::addExternalVariableMethodTypeDefinitionCode()
{
    if (mModel->hasExternalVariables()) {
        auto externalVariableMethodTypeDefinitionString = mProfile->externalVariableMethodTypeDefinitionString(mModelHasOdes);

        if (!externalVariableMethodTypeDefinitionString.empty()) {
            mCode += "\n"
                     + externalVariableMethodTypeDefinitionString;
        }
    }
}

void Generator::GeneratorImpl::addImplementationCreateStatesArrayMethodCode()
{
    if (mModelHasOdes
        && !mProfile->implementationCreateStatesArrayMethodString().empty()) {
        mCode += newLineIfNotEmpty(mCode)
                 + mProfile->implementationCreateStatesArrayMethodString();
    }
}

void Generator::GeneratorImpl::addImplementationCreateVariablesArrayMethodCode()
{
    if (!mProfile->implementationCreateVariablesArrayMethodString().empty()) {
        mCode += newLineIfNotEmpty(mCode)
                 + mProfile->implementationCreateVariablesArrayMethodString();
    }
}

void Generator::GeneratorImpl::addImplementationDeleteArrayMethodCode()
{
    if (!mProfile->implementationDeleteArrayMethodString().empty()) {
        mCode += newLineIfNotEmpty(mCode)
                 + mProfile->implementationDeleteArrayMethodString();
    }
}

void Generator::GeneratorImpl::addRootFindingInfoObjectCode()
{
    if (mModelHasNlas
        && !mProfile->rootFindingInfoObjectString(mModelHasOdes).empty()) {
        mCode += newLineIfNotEmpty(mCode)
                 + mProfile->rootFindingInfoObjectString(mModelHasOdes);
    }
}

void Generator::GeneratorImpl::addExternNlaSolveMethodCode()
{
    if (mModelHasNlas
        && !mProfile->externNlaSolveMethodString().empty()) {
        mCode += newLineIfNotEmpty(mCode)
                 + mProfile->externNlaSolveMethodString();
    }
}

void Generator::GeneratorImpl::addInterfaceComputeModelMethodsCode()
{
    auto interfaceInitialiseVariablesMethodString = mProfile->interfaceInitialiseVariablesMethodString(mModelHasOdes,
                                                                                                       mModel->hasExternalVariables());
    std::string interfaceComputeModelMethodsCode;

    if (!interfaceInitialiseVariablesMethodString.empty()) {
        interfaceComputeModelMethodsCode += interfaceInitialiseVariablesMethodString;
    }

    if (!mProfile->interfaceComputeComputedConstantsMethodString().empty()) {
        interfaceComputeModelMethodsCode += mProfile->interfaceComputeComputedConstantsMethodString();
    }

    auto interfaceComputeRatesMethodString = mProfile->interfaceComputeRatesMethodString(mModel->hasExternalVariables());

    if (mModelHasOdes
        && !interfaceComputeRatesMethodString.empty()) {
        interfaceComputeModelMethodsCode += interfaceComputeRatesMethodString;
    }

    auto interfaceComputeVariablesMethodString = mProfile->interfaceComputeVariablesMethodString(mModelHasOdes,
                                                                                                 mModel->hasExternalVariables());

    if (!interfaceComputeVariablesMethodString.empty()) {
        interfaceComputeModelMethodsCode += interfaceComputeVariablesMethodString;
    }

    if (!interfaceComputeModelMethodsCode.empty()) {
        mCode += "\n";
    }

    mCode += interfaceComputeModelMethodsCode;
}

void Generator::GeneratorImpl::addImplementationComputeModelMethodsCode()
{
    auto generatorInterpreter = GeneratorInterpreter::create(mModel, mProfile, mCode);

    mCode = generatorInterpreter->code();
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

AnalyserModelPtr Generator::model()
{
    return mPimpl->mModel;
}

void Generator::setModel(const AnalyserModelPtr &model)
{
    mPimpl->mModel = model;
    mPimpl->mModelHasOdes = modelHasOdes(model);
    mPimpl->mModelHasNlas = modelHasNlas(model);
}

std::string Generator::interfaceCode() const
{
    if ((mPimpl->mModel == nullptr)
        || (mPimpl->mProfile == nullptr)
        || !mPimpl->mModel->isValid()
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

std::string Generator::implementationCode() const
{
    if ((mPimpl->mModel == nullptr)
        || (mPimpl->mProfile == nullptr)
        || !mPimpl->mModel->isValid()) {
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

    if (!mPimpl->mProfile->hasInterface()) {
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

    mPimpl->addRootFindingInfoObjectCode();
    mPimpl->addExternNlaSolveMethodCode();

    // Add code for the implementation to compute the model.

    mPimpl->addImplementationComputeModelMethodsCode();

    return mPimpl->mCode;
}

std::string Generator::equationCode(const AnalyserEquationAstPtr &ast, const GeneratorProfilePtr &profile)
{
    auto generatorInterpreter = GeneratorInterpreter::create(ast, profile);

    return generatorInterpreter->code();
}

std::string Generator::equationCode(const AnalyserEquationAstPtr &ast)
{
    return Generator::equationCode(ast, nullptr);
}

} // namespace libcellml

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
#include "generatorinterpreter_p.h"
#include "generatorprofilesha1values.h"
#include "generatorprofiletools.h"
#include "utilities.h"

#include "libcellml/undefines.h"

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

        mCode += newLineIfNeeded(mCode)
                 + replace(mProfile->commentString(),
                           "[CODE]", replace(replace(mProfile->originCommentString(), "[PROFILE_INFORMATION]", profileInformation), "[LIBCELLML_VERSION]", versionString()));
    }
}

void Generator::GeneratorImpl::addInterfaceHeaderCode()
{
    if (!mProfile->interfaceHeaderString().empty()) {
        mCode += newLineIfNeeded(mCode)
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
        mCode += newLineIfNeeded(mCode)
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
        mCode += newLineIfNeeded(mCode)
                 + code;
    }
}

void Generator::GeneratorImpl::addStateAndVariableCountCode(bool interface)
{
    std::string code;

    if (mModelHasOdes
        && ((interface && !mProfile->interfaceStateCountString().empty())
            || (!interface && !mProfile->implementationStateCountString().empty()))) {
        code += interface ?
                    mProfile->interfaceStateCountString() :
                    replace(mProfile->implementationStateCountString(),
                            "[STATE_COUNT]", std::to_string(mModel->stateCount()));
    }

    if ((interface && !mProfile->interfaceConstantCountString().empty())
        || (!interface && !mProfile->implementationConstantCountString().empty())) {
        code += interface ?
                    mProfile->interfaceConstantCountString() :
                    replace(mProfile->implementationConstantCountString(),
                            "[CONSTANT_COUNT]", std::to_string(mModel->constantCount()));
    }

    if ((interface && !mProfile->interfaceComputedConstantCountString().empty())
        || (!interface && !mProfile->implementationComputedConstantCountString().empty())) {
        code += interface ?
                    mProfile->interfaceComputedConstantCountString() :
                    replace(mProfile->implementationComputedConstantCountString(),
                            "[COMPUTED_CONSTANT_COUNT]", std::to_string(mModel->computedConstantCount()));
    }

    if ((interface && !mProfile->interfaceAlgebraicCountString().empty())
        || (!interface && !mProfile->implementationAlgebraicCountString().empty())) {
        code += interface ?
                    mProfile->interfaceAlgebraicCountString() :
                    replace(mProfile->implementationAlgebraicCountString(),
                            "[ALGEBRAIC_COUNT]", std::to_string(mModel->algebraicCount()));
    }

    if ((mModel->externalCount() != 0)
        && ((interface && !mProfile->interfaceExternalCountString().empty())
            || (!interface && !mProfile->implementationExternalCountString().empty()))) {
        code += interface ?
                    mProfile->interfaceExternalCountString() :
                    replace(mProfile->implementationExternalCountString(),
                            "[EXTERNAL_COUNT]", std::to_string(mModel->externalCount()));
    }

    if (!code.empty()) {
        mCode += newLineIfNeeded(mCode)
                 + code;
    }
}

std::string Generator::GeneratorImpl::generateVariableInfoObjectCode(const std::string &objectString) const
{
    size_t componentSize = 0;
    size_t nameSize = 0;
    size_t unitsSize = 0;

    for (const auto &variable : variables(mModel)) {
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
        mCode += newLineIfNeeded(mCode)
                 + generateVariableInfoObjectCode(mProfile->variableInfoObjectString());
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

void Generator::GeneratorImpl::addInterfaceVariableInfoCode()
{
    std::string code;

    if (mModelHasOdes
        && !mProfile->interfaceVoiInfoString().empty()) {
        code += mProfile->interfaceVoiInfoString();
    }

    if (mModelHasOdes
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

    if (mModel->hasExternalVariables()
        && !mProfile->interfaceExternalInfoString().empty()) {
        code += mProfile->interfaceExternalInfoString();
    }

    if (!code.empty()) {
        mCode += newLineIfNeeded(mCode)
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

        mCode += newLineIfNeeded(mCode)
                 + replace(variableInfoString, "[CODE]", infoElementsCode);
    }
}

void Generator::GeneratorImpl::addImplementationVariableInfoCode()
{
    if (mModelHasOdes) {
        doAddImplementationVariableInfoCode(mProfile->implementationVoiInfoString(), {mModel->voi()}, true);
    }

    if (mModelHasOdes) {
        doAddImplementationVariableInfoCode(mProfile->implementationStateInfoString(), mModel->states(), false);
    }

    doAddImplementationVariableInfoCode(mProfile->implementationConstantInfoString(), mModel->constants(), false);
    doAddImplementationVariableInfoCode(mProfile->implementationComputedConstantInfoString(), mModel->computedConstants(), false);
    doAddImplementationVariableInfoCode(mProfile->implementationAlgebraicInfoString(), mModel->algebraic(), false);

    if (mModel->hasExternalVariables()) {
        doAddImplementationVariableInfoCode(mProfile->implementationExternalInfoString(), mModel->externals(), false);
    }
}

void Generator::GeneratorImpl::addArithmeticFunctionsCode()
{
    if (mModel->needEqFunction() && !mProfile->hasEqOperator()
        && !mProfile->eqFunctionString().empty()) {
        mCode += newLineIfNeeded(mCode)
                 + mProfile->eqFunctionString();
    }

    if (mModel->needNeqFunction() && !mProfile->hasNeqOperator()
        && !mProfile->neqFunctionString().empty()) {
        mCode += newLineIfNeeded(mCode)
                 + mProfile->neqFunctionString();
    }

    if (mModel->needLtFunction() && !mProfile->hasLtOperator()
        && !mProfile->ltFunctionString().empty()) {
        mCode += newLineIfNeeded(mCode)
                 + mProfile->ltFunctionString();
    }

    if (mModel->needLeqFunction() && !mProfile->hasLeqOperator()
        && !mProfile->leqFunctionString().empty()) {
        mCode += newLineIfNeeded(mCode)
                 + mProfile->leqFunctionString();
    }

    if (mModel->needGtFunction() && !mProfile->hasGtOperator()
        && !mProfile->gtFunctionString().empty()) {
        mCode += newLineIfNeeded(mCode)
                 + mProfile->gtFunctionString();
    }

    if (mModel->needGeqFunction() && !mProfile->hasGeqOperator()
        && !mProfile->geqFunctionString().empty()) {
        mCode += newLineIfNeeded(mCode)
                 + mProfile->geqFunctionString();
    }

    if (mModel->needAndFunction() && !mProfile->hasAndOperator()
        && !mProfile->andFunctionString().empty()) {
        mCode += newLineIfNeeded(mCode)
                 + mProfile->andFunctionString();
    }

    if (mModel->needOrFunction() && !mProfile->hasOrOperator()
        && !mProfile->orFunctionString().empty()) {
        mCode += newLineIfNeeded(mCode)
                 + mProfile->orFunctionString();
    }

    if (mModel->needXorFunction() && !mProfile->hasXorOperator()
        && !mProfile->xorFunctionString().empty()) {
        mCode += newLineIfNeeded(mCode)
                 + mProfile->xorFunctionString();
    }

    if (mModel->needNotFunction() && !mProfile->hasNotOperator()
        && !mProfile->notFunctionString().empty()) {
        mCode += newLineIfNeeded(mCode)
                 + mProfile->notFunctionString();
    }

    if (mModel->needMinFunction()
        && !mProfile->minFunctionString().empty()) {
        mCode += newLineIfNeeded(mCode)
                 + mProfile->minFunctionString();
    }

    if (mModel->needMaxFunction()
        && !mProfile->maxFunctionString().empty()) {
        mCode += newLineIfNeeded(mCode)
                 + mProfile->maxFunctionString();
    }
}

void Generator::GeneratorImpl::addTrigonometricFunctionsCode()
{
    if (mModel->needSecFunction()
        && !mProfile->secFunctionString().empty()) {
        mCode += newLineIfNeeded(mCode)
                 + mProfile->secFunctionString();
    }

    if (mModel->needCscFunction()
        && !mProfile->cscFunctionString().empty()) {
        mCode += newLineIfNeeded(mCode)
                 + mProfile->cscFunctionString();
    }

    if (mModel->needCotFunction()
        && !mProfile->cotFunctionString().empty()) {
        mCode += newLineIfNeeded(mCode)
                 + mProfile->cotFunctionString();
    }

    if (mModel->needSechFunction()
        && !mProfile->sechFunctionString().empty()) {
        mCode += newLineIfNeeded(mCode)
                 + mProfile->sechFunctionString();
    }

    if (mModel->needCschFunction()
        && !mProfile->cschFunctionString().empty()) {
        mCode += newLineIfNeeded(mCode)
                 + mProfile->cschFunctionString();
    }

    if (mModel->needCothFunction()
        && !mProfile->cothFunctionString().empty()) {
        mCode += newLineIfNeeded(mCode)
                 + mProfile->cothFunctionString();
    }

    if (mModel->needAsecFunction()
        && !mProfile->asecFunctionString().empty()) {
        mCode += newLineIfNeeded(mCode)
                 + mProfile->asecFunctionString();
    }

    if (mModel->needAcscFunction()
        && !mProfile->acscFunctionString().empty()) {
        mCode += newLineIfNeeded(mCode)
                 + mProfile->acscFunctionString();
    }

    if (mModel->needAcotFunction()
        && !mProfile->acotFunctionString().empty()) {
        mCode += newLineIfNeeded(mCode)
                 + mProfile->acotFunctionString();
    }

    if (mModel->needAsechFunction()
        && !mProfile->asechFunctionString().empty()) {
        mCode += newLineIfNeeded(mCode)
                 + mProfile->asechFunctionString();
    }

    if (mModel->needAcschFunction()
        && !mProfile->acschFunctionString().empty()) {
        mCode += newLineIfNeeded(mCode)
                 + mProfile->acschFunctionString();
    }

    if (mModel->needAcothFunction()
        && !mProfile->acothFunctionString().empty()) {
        mCode += newLineIfNeeded(mCode)
                 + mProfile->acothFunctionString();
    }
}

void Generator::GeneratorImpl::addInterfaceCreateDeleteArrayMethodsCode()
{
    std::string code;

    if (mModelHasOdes
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

    if (mModel->hasExternalVariables()
        && !mProfile->interfaceCreateExternalsArrayMethodString().empty()) {
        code += mProfile->interfaceCreateExternalsArrayMethodString();
    }

    if (!mProfile->interfaceDeleteArrayMethodString().empty()) {
        code += "\n"
                + mProfile->interfaceDeleteArrayMethodString();
    }

    if (!code.empty()) {
        mCode += newLineIfNeeded(mCode)
                 + code;
    }
}

void Generator::GeneratorImpl::addImplementationCreateDeleteArrayMethodsCode()
{
    if (mModelHasOdes
        && !mProfile->implementationCreateStatesArrayMethodString().empty()) {
        mCode += newLineIfNeeded(mCode)
                 + mProfile->implementationCreateStatesArrayMethodString();
    }

    if (!mProfile->implementationCreateConstantsArrayMethodString().empty()) {
        mCode += newLineIfNeeded(mCode)
                 + mProfile->implementationCreateConstantsArrayMethodString();
    }

    if (!mProfile->implementationCreateComputedConstantsArrayMethodString().empty()) {
        mCode += newLineIfNeeded(mCode)
                 + mProfile->implementationCreateComputedConstantsArrayMethodString();
    }

    if (!mProfile->implementationCreateAlgebraicArrayMethodString().empty()) {
        mCode += newLineIfNeeded(mCode)
                 + mProfile->implementationCreateAlgebraicArrayMethodString();
    }

    if (mModel->hasExternalVariables()
        && !mProfile->implementationCreateExternalsArrayMethodString().empty()) {
        mCode += newLineIfNeeded(mCode)
                 + mProfile->implementationCreateExternalsArrayMethodString();
    }

    if (!mProfile->implementationDeleteArrayMethodString().empty()) {
        mCode += newLineIfNeeded(mCode)
                 + mProfile->implementationDeleteArrayMethodString();
    }
}

void Generator::GeneratorImpl::addExternalVariableMethodTypeDefinitionCode()
{
    if (mModel->hasExternalVariables()) {
        auto externalVariableMethodTypeDefinitionString = mProfile->externalVariableMethodTypeDefinitionString(mModelHasOdes);

        if (!externalVariableMethodTypeDefinitionString.empty()) {
            mCode += newLineIfNeeded(mCode)
                     + externalVariableMethodTypeDefinitionString;
        }
    }
}

void Generator::GeneratorImpl::addRootFindingInfoObjectCode()
{
    if (mModelHasNlas
        && !mProfile->rootFindingInfoObjectString(mModelHasOdes, mModel->hasExternalVariables()).empty()) {
        mCode += newLineIfNeeded(mCode)
                 + mProfile->rootFindingInfoObjectString(mModelHasOdes, mModel->hasExternalVariables());
    }
}

void Generator::GeneratorImpl::addExternNlaSolveMethodCode()
{
    if (mModelHasNlas
        && !mProfile->externNlaSolveMethodString().empty()) {
        mCode += newLineIfNeeded(mCode)
                 + mProfile->externNlaSolveMethodString();
    }
}

void Generator::GeneratorImpl::addInterfaceComputeModelMethodsCode()
{
    auto interfaceInitialiseVariablesMethodString = mProfile->interfaceInitialiseVariablesMethodString(mModelHasOdes);
    std::string code;

    if (!interfaceInitialiseVariablesMethodString.empty()) {
        code += interfaceInitialiseVariablesMethodString;
    }

    if (!mProfile->interfaceComputeComputedConstantsMethodString().empty()) {
        code += mProfile->interfaceComputeComputedConstantsMethodString();
    }

    auto interfaceComputeRatesMethodString = mProfile->interfaceComputeRatesMethodString(mModel->hasExternalVariables());

    if (mModelHasOdes
        && !interfaceComputeRatesMethodString.empty()) {
        code += interfaceComputeRatesMethodString;
    }

    auto interfaceComputeVariablesMethodString = mProfile->interfaceComputeVariablesMethodString(mModelHasOdes,
                                                                                                 mModel->hasExternalVariables());

    if (!interfaceComputeVariablesMethodString.empty()) {
        code += interfaceComputeVariablesMethodString;
    }

    if (!code.empty()) {
        mCode += newLineIfNeeded(mCode)
                 + code;
    }
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

    mPimpl->addVariableInfoObjectCode();

    // Add code for the interface of the information about the variable of integration, states, constants, computed
    // constants, algebraic variables, and external variables.

    mPimpl->addInterfaceVariableInfoCode();

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
        mPimpl->addVariableInfoObjectCode();
    }

    // Add code for the implementation of the information about the variable of integration, states, constants, computed
    // constants, algebraic variables, and external variables.

    mPimpl->addImplementationVariableInfoCode();

    // Add code for the arithmetic and trigonometric functions.

    mPimpl->addArithmeticFunctionsCode();
    mPimpl->addTrigonometricFunctionsCode();

    // Add code for the implementation to create and delete arrays.

    mPimpl->addImplementationCreateDeleteArrayMethodsCode();

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

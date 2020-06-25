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

#include <algorithm>
#include <limits>
#include <regex>
#include <sstream>
#include <vector>

#include "libcellml/analyserequation.h"
#include "libcellml/analyserequationast.h"
#include "libcellml/analysermodel.h"
#include "libcellml/analyservariable.h"
#include "libcellml/component.h"
#include "libcellml/generatorequationast.h"
#include "libcellml/generatorprofile.h"
#include "libcellml/model.h"
#include "libcellml/units.h"
#include "libcellml/validator.h"
#include "libcellml/variable.h"
#include "libcellml/version.h"

#include "utilities.h"
#include "xmldoc.h"

#ifdef __linux__
#    undef TRUE
#    undef FALSE
#endif

namespace libcellml {

/**
 * @brief The Generator::GeneratorImpl struct.
 *
 * The private implementation for the Generator class.
 */
struct Generator::GeneratorImpl
{
    Generator *mGenerator = nullptr;

    AnalyserModelPtr mModel = nullptr;

    std::string mCode;

    GeneratorProfilePtr mProfile = libcellml::GeneratorProfile::create();

    AnalyserVariablePtr analyserVariable(const VariablePtr &variable) const;

    double scalingFactor(const VariablePtr &variable) const;

    bool isRelationalOperator(const AnalyserEquationAstPtr &ast) const;
    bool isAndOperator(const AnalyserEquationAstPtr &ast) const;
    bool isOrOperator(const AnalyserEquationAstPtr &ast) const;
    bool isXorOperator(const AnalyserEquationAstPtr &ast) const;
    bool isLogicalOperator(const AnalyserEquationAstPtr &ast) const;
    bool isPlusOperator(const AnalyserEquationAstPtr &ast) const;
    bool isMinusOperator(const AnalyserEquationAstPtr &ast) const;
    bool isTimesOperator(const AnalyserEquationAstPtr &ast) const;
    bool isDivideOperator(const AnalyserEquationAstPtr &ast) const;
    bool isPowerOperator(const AnalyserEquationAstPtr &ast) const;
    bool isRootOperator(const AnalyserEquationAstPtr &ast) const;
    bool isPiecewiseStatement(const AnalyserEquationAstPtr &ast) const;

    std::string replace(std::string string, const std::string &from,
                        const std::string &to);

    void updateVariableInfoSizes(size_t &componentSize, size_t &nameSize,
                                 size_t &unitsSize,
                                 const AnalyserVariablePtr &variable);

    bool modifiedProfile() const;

    void addOriginCommentCode();

    void addInterfaceHeaderCode();
    void addImplementationHeaderCode();

    void addVersionAndLibcellmlVersionCode(bool interface = false);

    void addStateAndVariableCountCode(bool interface = false);

    void addVariableTypeObjectCode();

    std::string generateVariableInfoObjectCode(const std::string &objectString);

    void addVariableInfoObjectCode();
    void addVariableInfoWithTypeObjectCode();

    std::string generateVariableInfoEntryCode(const std::string &name,
                                              const std::string &units,
                                              const std::string &component);

    void addInterfaceVoiStateAndVariableInfoCode();
    void addImplementationVoiInfoCode();
    void addImplementationStateInfoCode();
    void addImplementationVariableInfoCode();

    void addArithmeticFunctionsCode();
    void addTrigonometricFunctionsCode();

    void addInterfaceCreateDeleteArrayMethodsCode();
    void addImplementationCreateStatesArrayMethodCode();
    void addImplementationCreateVariablesArrayMethodCode();
    void addImplementationDeleteArrayMethodCode();

    std::string generateMethodBodyCode(const std::string &methodBody) const;

    std::string generateDoubleCode(const std::string &value);
    std::string generateDoubleOrConstantVariableNameCode(const VariablePtr &variable);
    std::string generateVariableNameCode(const VariablePtr &variable,
                                         const AnalyserEquationAstPtr &ast = nullptr) const;

    std::string generateOperatorCode(const std::string &op,
                                     const AnalyserEquationAstPtr &ast);
    std::string generateMinusUnaryCode(const AnalyserEquationAstPtr &ast);
    std::string generateOneParameterFunctionCode(const std::string &function,
                                                 const AnalyserEquationAstPtr &ast);
    std::string generateTwoParameterFunctionCode(const std::string &function,
                                                 const AnalyserEquationAstPtr &ast);
    std::string generatePiecewiseIfCode(const std::string &condition,
                                        const std::string &value);
    std::string generatePiecewiseElseCode(const std::string &value);
    std::string generateCode(const AnalyserEquationAstPtr &ast);

    std::string generateInitializationCode(const AnalyserVariablePtr &variable);
    std::string generateEquationCode(const AnalyserEquationPtr &equation,
                                     std::vector<AnalyserEquationPtr> &remainingEquations,
                                     bool onlyStateRateBasedEquations = false);

    void addInterfaceComputeModelMethodsCode();
    void addImplementationInitializeStatesAndConstantsMethodCode(std::vector<AnalyserEquationPtr> &remainingEquations);
    void addImplementationComputeComputedConstantsMethodCode(std::vector<AnalyserEquationPtr> &remainingEquations);
    void addImplementationComputeRatesMethodCode(std::vector<AnalyserEquationPtr> &remainingEquations);
    void addImplementationComputeVariablesMethodCode(std::vector<AnalyserEquationPtr> &remainingEquations);
};

AnalyserVariablePtr Generator::GeneratorImpl::analyserVariable(const VariablePtr &variable) const
{
    // Find and return the analyser variable associated with the given variable.

    auto modelVoi = mModel->voi();

    if ((modelVoi != nullptr)
        && isSameOrEquivalentVariable(variable, modelVoi->variable())) {
        return modelVoi;
    }

    for (size_t i = 0; i < mModel->stateCount(); ++i) {
        auto modelState = mModel->state(i);

        if (isSameOrEquivalentVariable(variable, modelState->variable())) {
            return modelState;
        }
    }

    for (size_t i = 0; i < mModel->variableCount(); ++i) {
        auto modelVariable = mModel->variable(i);

        if (isSameOrEquivalentVariable(variable, modelVariable->variable())) {
            return modelVariable;
        }
    }

    return {};
}

double Generator::GeneratorImpl::scalingFactor(const VariablePtr &variable) const
{
    // Return the scaling factor for the given variable.

    return Units::scalingFactor(variable->units(),
                                analyserVariable(variable)->variable()->units());
}

bool Generator::GeneratorImpl::isRelationalOperator(const AnalyserEquationAstPtr &ast) const
{
    return ((ast->type() == AnalyserEquationAst::Type::EQ)
            && mProfile->hasEqOperator())
           || ((ast->type() == AnalyserEquationAst::Type::NEQ)
               && mProfile->hasNeqOperator())
           || ((ast->type() == AnalyserEquationAst::Type::LT)
               && mProfile->hasLtOperator())
           || ((ast->type() == AnalyserEquationAst::Type::LEQ)
               && mProfile->hasLeqOperator())
           || ((ast->type() == AnalyserEquationAst::Type::GT)
               && mProfile->hasGtOperator())
           || ((ast->type() == AnalyserEquationAst::Type::GEQ)
               && mProfile->hasGeqOperator());
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

std::string Generator::GeneratorImpl::replace(std::string string,
                                              const std::string &from,
                                              const std::string &to)
{
    auto index = string.find(from);

    return (index == std::string::npos) ?
               string :
               string.replace(index, from.length(), to);
}

void Generator::GeneratorImpl::updateVariableInfoSizes(size_t &componentSize,
                                                       size_t &nameSize,
                                                       size_t &unitsSize,
                                                       const AnalyserVariablePtr &variable)
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

    const std::string trueValue = "true";
    const std::string falseValue = "false";

    std::string profileContents = mProfile->hasInterface() ?
                                      trueValue :
                                      falseValue;

    // Assignment.

    profileContents += mProfile->assignmentString();

    // Relational and logical operators.

    profileContents += mProfile->eqString()
                       + mProfile->neqString()
                       + mProfile->ltString()
                       + mProfile->leqString()
                       + mProfile->gtString()
                       + mProfile->geqString()
                       + mProfile->andString()
                       + mProfile->orString()
                       + mProfile->xorString()
                       + mProfile->notString();

    profileContents += (mProfile->hasEqOperator() ?
                            trueValue :
                            falseValue)
                       + (mProfile->hasNeqOperator() ?
                              trueValue :
                              falseValue)
                       + (mProfile->hasLtOperator() ?
                              trueValue :
                              falseValue)
                       + (mProfile->hasLeqOperator() ?
                              trueValue :
                              falseValue)
                       + (mProfile->hasGtOperator() ?
                              trueValue :
                              falseValue)
                       + (mProfile->hasGeqOperator() ?
                              trueValue :
                              falseValue)
                       + (mProfile->hasAndOperator() ?
                              trueValue :
                              falseValue)
                       + (mProfile->hasOrOperator() ?
                              trueValue :
                              falseValue)
                       + (mProfile->hasXorOperator() ?
                              trueValue :
                              falseValue)
                       + (mProfile->hasNotOperator() ?
                              trueValue :
                              falseValue);

    // Arithmetic operators.

    profileContents += mProfile->plusString()
                       + mProfile->minusString()
                       + mProfile->timesString()
                       + mProfile->divideString()
                       + mProfile->powerString()
                       + mProfile->squareRootString()
                       + mProfile->squareString()
                       + mProfile->absoluteValueString()
                       + mProfile->exponentialString()
                       + mProfile->napierianLogarithmString()
                       + mProfile->commonLogarithmString()
                       + mProfile->ceilingString()
                       + mProfile->floorString()
                       + mProfile->minString()
                       + mProfile->maxString()
                       + mProfile->remString();

    profileContents += mProfile->hasPowerOperator() ?
                           trueValue :
                           falseValue;

    // Trigonometric operators.

    profileContents += mProfile->sinString()
                       + mProfile->cosString()
                       + mProfile->tanString()
                       + mProfile->secString()
                       + mProfile->cscString()
                       + mProfile->cotString()
                       + mProfile->sinhString()
                       + mProfile->coshString()
                       + mProfile->tanhString()
                       + mProfile->sechString()
                       + mProfile->cschString()
                       + mProfile->cothString()
                       + mProfile->asinString()
                       + mProfile->acosString()
                       + mProfile->atanString()
                       + mProfile->asecString()
                       + mProfile->acscString()
                       + mProfile->acotString()
                       + mProfile->asinhString()
                       + mProfile->acoshString()
                       + mProfile->atanhString()
                       + mProfile->asechString()
                       + mProfile->acschString()
                       + mProfile->acothString();

    // Piecewise statement.

    profileContents += mProfile->conditionalOperatorIfString()
                       + mProfile->conditionalOperatorElseString()
                       + mProfile->piecewiseIfString()
                       + mProfile->piecewiseElseString();

    profileContents += mProfile->hasConditionalOperator() ?
                           trueValue :
                           falseValue;

    // Constants.

    profileContents += mProfile->trueString()
                       + mProfile->falseString()
                       + mProfile->eString()
                       + mProfile->piString()
                       + mProfile->infString()
                       + mProfile->nanString();

    // Arithmetic functions.

    profileContents += mProfile->eqFunctionString()
                       + mProfile->neqFunctionString()
                       + mProfile->ltFunctionString()
                       + mProfile->leqFunctionString()
                       + mProfile->gtFunctionString()
                       + mProfile->geqFunctionString()
                       + mProfile->andFunctionString()
                       + mProfile->orFunctionString()
                       + mProfile->xorFunctionString()
                       + mProfile->notFunctionString()
                       + mProfile->minFunctionString()
                       + mProfile->maxFunctionString();

    // Trigonometric functions.

    profileContents += mProfile->secFunctionString()
                       + mProfile->cscFunctionString()
                       + mProfile->cotFunctionString()
                       + mProfile->sechFunctionString()
                       + mProfile->cschFunctionString()
                       + mProfile->cothFunctionString()
                       + mProfile->asecFunctionString()
                       + mProfile->acscFunctionString()
                       + mProfile->acotFunctionString()
                       + mProfile->asechFunctionString()
                       + mProfile->acschFunctionString()
                       + mProfile->acothFunctionString();

    // Miscellaneous.

    profileContents += mProfile->commentString()
                       + mProfile->originCommentString();

    profileContents += mProfile->interfaceFileNameString();

    profileContents += mProfile->interfaceHeaderString()
                       + mProfile->implementationHeaderString();

    profileContents += mProfile->interfaceVersionString()
                       + mProfile->implementationVersionString();

    profileContents += mProfile->interfaceLibcellmlVersionString()
                       + mProfile->implementationLibcellmlVersionString();

    profileContents += mProfile->interfaceStateCountString()
                       + mProfile->implementationStateCountString();

    profileContents += mProfile->interfaceVariableCountString()
                       + mProfile->implementationVariableCountString();

    profileContents += mProfile->variableTypeObjectString();

    profileContents += mProfile->constantVariableTypeString()
                       + mProfile->computedConstantVariableTypeString()
                       + mProfile->algebraicVariableTypeString();

    profileContents += mProfile->variableInfoObjectString()
                       + mProfile->variableInfoWithTypeObjectString();

    profileContents += mProfile->interfaceVoiInfoString()
                       + mProfile->implementationVoiInfoString();

    profileContents += mProfile->interfaceStateInfoString()
                       + mProfile->implementationStateInfoString();

    profileContents += mProfile->interfaceVariableInfoString()
                       + mProfile->implementationVariableInfoString();

    profileContents += mProfile->variableInfoEntryString()
                       + mProfile->variableInfoWithTypeEntryString();

    profileContents += mProfile->voiString();

    profileContents += mProfile->statesArrayString()
                       + mProfile->ratesArrayString()
                       + mProfile->variablesArrayString();

    profileContents += mProfile->interfaceCreateStatesArrayMethodString()
                       + mProfile->implementationCreateStatesArrayMethodString();

    profileContents += mProfile->interfaceCreateVariablesArrayMethodString()
                       + mProfile->implementationCreateVariablesArrayMethodString();

    profileContents += mProfile->interfaceDeleteArrayMethodString()
                       + mProfile->implementationDeleteArrayMethodString();

    profileContents += mProfile->interfaceInitializeStatesAndConstantsMethodString()
                       + mProfile->implementationInitializeStatesAndConstantsMethodString();

    profileContents += mProfile->interfaceComputeComputedConstantsMethodString()
                       + mProfile->implementationComputeComputedConstantsMethodString();

    profileContents += mProfile->interfaceComputeRatesMethodString()
                       + mProfile->implementationComputeRatesMethodString();

    profileContents += mProfile->interfaceComputeVariablesMethodString()
                       + mProfile->implementationComputeVariablesMethodString();

    profileContents += mProfile->emptyMethodString();

    profileContents += mProfile->indentString();

    profileContents += mProfile->openArrayInitializerString()
                       + mProfile->closeArrayInitializerString();

    profileContents += mProfile->openArrayString()
                       + mProfile->closeArrayString();

    profileContents += mProfile->arrayElementSeparatorString();

    profileContents += mProfile->stringDelimiterString();

    profileContents += mProfile->commandSeparatorString();

    // Compute and check the hash of our profile contents.

    bool res = false;
    std::string profileContentsSha1 = sha1(profileContents);

    switch (mProfile->profile()) {
    case GeneratorProfile::Profile::C:
        res = profileContentsSha1 != "e2aa9af2767ab84b217cf996c491c485ae876563";

        break;
    case GeneratorProfile::Profile::PYTHON:
        res = profileContentsSha1 != "1abb41ecb908526b51c2ac8c44bc9542942a9652";

        break;
    }

    return res;
}

void Generator::GeneratorImpl::addOriginCommentCode()
{
    if (!mProfile->commentString().empty()
        && !mProfile->originCommentString().empty()) {
        std::string profileInformation = modifiedProfile() ?
                                             "a modified " :
                                             "the ";

        switch (mProfile->profile()) {
        case GeneratorProfile::Profile::C:
            profileInformation += "C";

            break;
        case GeneratorProfile::Profile::PYTHON:
            profileInformation += "Python";

            break;
        }

        profileInformation += " profile of";

        std::string commentCode = replace(replace(mProfile->originCommentString(),
                                                  "<PROFILE_INFORMATION>", profileInformation),
                                          "<LIBCELLML_VERSION>", versionString());

        mCode += replace(mProfile->commentString(),
                         "<CODE>", commentCode);
    }
}

void Generator::GeneratorImpl::addInterfaceHeaderCode()
{
    if (!mProfile->interfaceHeaderString().empty()) {
        if (!mCode.empty()) {
            mCode += "\n";
        }

        mCode += mProfile->interfaceHeaderString();
    }
}

void Generator::GeneratorImpl::addImplementationHeaderCode()
{
    if (!mProfile->implementationHeaderString().empty()) {
        if (!mCode.empty()) {
            mCode += "\n";
        }

        mCode += replace(mProfile->implementationHeaderString(),
                         "<INTERFACE_FILE_NAME>", mProfile->interfaceFileNameString());
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
                std::regex regEx("([0-9]+\\.[0-9]+\\.[0-9]+)");

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
                                               "<LIBCELLML_VERSION>", versionString());
    }

    if (!versionAndLibcellmlCode.empty()) {
        mCode += "\n";
    }

    mCode += versionAndLibcellmlCode;
}

void Generator::GeneratorImpl::addStateAndVariableCountCode(bool interface)
{
    std::string stateAndVariableCountCode;

    if ((interface && !mProfile->interfaceStateCountString().empty())
        || (!interface && !mProfile->implementationStateCountString().empty())) {
        stateAndVariableCountCode += interface ?
                                         mProfile->interfaceStateCountString() :
                                         replace(mProfile->implementationStateCountString(),
                                                 "<STATE_COUNT>", std::to_string(mModel->stateCount()));
    }

    if ((interface && !mProfile->interfaceVariableCountString().empty())
        || (!interface && !mProfile->implementationVariableCountString().empty())) {
        stateAndVariableCountCode += interface ?
                                         mProfile->interfaceVariableCountString() :
                                         replace(mProfile->implementationVariableCountString(),
                                                 "<VARIABLE_COUNT>", std::to_string(mModel->variableCount()));
    }

    if (!stateAndVariableCountCode.empty()) {
        mCode += "\n";
    }

    mCode += stateAndVariableCountCode;
}

void Generator::GeneratorImpl::addVariableTypeObjectCode()
{
    if (!mProfile->variableTypeObjectString().empty()) {
        if (!mCode.empty()) {
            mCode += "\n";
        }

        mCode += mProfile->variableTypeObjectString();
    }
}

std::string Generator::GeneratorImpl::generateVariableInfoObjectCode(const std::string &objectString)
{
    size_t componentSize = 0;
    size_t nameSize = 0;
    size_t unitsSize = 0;

    if (mModel->voi() != nullptr) {
        updateVariableInfoSizes(componentSize, nameSize, unitsSize, mModel->voi());
    }

    for (size_t i = 0; i < mModel->stateCount(); ++i) {
        updateVariableInfoSizes(componentSize, nameSize, unitsSize, mModel->state(i));
    }

    for (size_t i = 0; i < mModel->variableCount(); ++i) {
        updateVariableInfoSizes(componentSize, nameSize, unitsSize, mModel->variable(i));
    }

    return replace(replace(replace(objectString,
                                   "<COMPONENT_SIZE>", std::to_string(componentSize)),
                           "<NAME_SIZE>", std::to_string(nameSize)),
                   "<UNITS_SIZE>", std::to_string(unitsSize));
}

void Generator::GeneratorImpl::addVariableInfoObjectCode()
{
    if (!mProfile->variableInfoObjectString().empty()) {
        if (!mCode.empty()) {
            mCode += "\n";
        }

        mCode += generateVariableInfoObjectCode(mProfile->variableInfoObjectString());
    }
}

void Generator::GeneratorImpl::addVariableInfoWithTypeObjectCode()
{
    if (!mProfile->variableInfoWithTypeObjectString().empty()) {
        if (!mCode.empty()) {
            mCode += "\n";
        }

        mCode += generateVariableInfoObjectCode(mProfile->variableInfoWithTypeObjectString());
    }
}

std::string Generator::GeneratorImpl::generateVariableInfoEntryCode(const std::string &name,
                                                                    const std::string &units,
                                                                    const std::string &component)
{
    return replace(replace(replace(mProfile->variableInfoEntryString(),
                                   "<NAME>", name),
                           "<UNITS>", units),
                   "<COMPONENT>", component);
}

void Generator::GeneratorImpl::addInterfaceVoiStateAndVariableInfoCode()
{
    std::string interfaceVoiStateAndVariableInfoCode;

    if (!mProfile->interfaceVoiInfoString().empty()) {
        interfaceVoiStateAndVariableInfoCode += mProfile->interfaceVoiInfoString();
    }

    if (!mProfile->interfaceStateInfoString().empty()) {
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
    if (!mProfile->implementationVoiInfoString().empty()
        && !mProfile->variableInfoEntryString().empty()) {
        if (!mCode.empty()) {
            mCode += "\n";
        }

        std::string name = (mModel->voi() != nullptr) ? mModel->voi()->variable()->name() : "";
        std::string units = (mModel->voi() != nullptr) ? mModel->voi()->variable()->units()->name() : "";
        std::string component = (mModel->voi() != nullptr) ? owningComponent(mModel->voi()->variable())->name() : "";

        mCode += replace(mProfile->implementationVoiInfoString(),
                         "<CODE>", generateVariableInfoEntryCode(name, units, component));
    }
}

void Generator::GeneratorImpl::addImplementationStateInfoCode()
{
    if (!mProfile->implementationStateInfoString().empty()
        && !mProfile->variableInfoEntryString().empty()
        && !mProfile->arrayElementSeparatorString().empty()) {
        if (!mCode.empty()) {
            mCode += "\n";
        }

        std::string infoElementsCode;

        for (size_t i = 0; i < mModel->stateCount(); ++i) {
            if (!infoElementsCode.empty()) {
                infoElementsCode += mProfile->arrayElementSeparatorString() + "\n";
            }

            auto state = mModel->state(i);

            infoElementsCode += mProfile->indentString()
                                + generateVariableInfoEntryCode(state->variable()->name(),
                                                                state->variable()->units()->name(),
                                                                owningComponent(state->variable())->name());
        }

        if (!infoElementsCode.empty()) {
            infoElementsCode += "\n";
        }

        mCode += replace(mProfile->implementationStateInfoString(),
                         "<CODE>", infoElementsCode);
    }
}

void Generator::GeneratorImpl::addImplementationVariableInfoCode()
{
    if (!mProfile->implementationVariableInfoString().empty()
        && !mProfile->variableInfoWithTypeEntryString().empty()
        && !mProfile->arrayElementSeparatorString().empty()
        && !mProfile->constantVariableTypeString().empty()
        && !mProfile->computedConstantVariableTypeString().empty()
        && !mProfile->algebraicVariableTypeString().empty()) {
        if (!mCode.empty()) {
            mCode += "\n";
        }

        std::string infoElementsCode;

        for (size_t i = 0; i < mModel->variableCount(); ++i) {
            if (!infoElementsCode.empty()) {
                infoElementsCode += mProfile->arrayElementSeparatorString() + "\n";
            }

            std::string variableType;

            auto variable = mModel->variable(i);

            if (variable->type() == AnalyserVariable::Type::CONSTANT) {
                variableType = mProfile->constantVariableTypeString();
            } else if (variable->type() == AnalyserVariable::Type::COMPUTED_CONSTANT) {
                variableType = mProfile->computedConstantVariableTypeString();
            } else if (variable->type() == AnalyserVariable::Type::ALGEBRAIC) {
                variableType = mProfile->algebraicVariableTypeString();
            }

            infoElementsCode += mProfile->indentString()
                                + replace(replace(replace(replace(mProfile->variableInfoWithTypeEntryString(),
                                                                  "<NAME>", variable->variable()->name()),
                                                          "<UNITS>", variable->variable()->units()->name()),
                                                  "<COMPONENT>", owningComponent(variable->variable())->name()),
                                          "<TYPE>", variableType);
        }

        if (!infoElementsCode.empty()) {
            infoElementsCode += "\n";
        }

        mCode += replace(mProfile->implementationVariableInfoString(),
                         "<CODE>", infoElementsCode);
    }
}

void Generator::GeneratorImpl::addArithmeticFunctionsCode()
{
    if (mModel->needEqFunction() && !mProfile->hasEqOperator()
        && !mProfile->eqFunctionString().empty()) {
        if (!mCode.empty()) {
            mCode += "\n";
        }

        mCode += mProfile->eqFunctionString();
    }

    if (mModel->needNeqFunction() && !mProfile->hasNeqOperator()
        && !mProfile->neqFunctionString().empty()) {
        if (!mCode.empty()) {
            mCode += "\n";
        }

        mCode += mProfile->neqFunctionString();
    }

    if (mModel->needLtFunction() && !mProfile->hasLtOperator()
        && !mProfile->ltFunctionString().empty()) {
        if (!mCode.empty()) {
            mCode += "\n";
        }

        mCode += mProfile->ltFunctionString();
    }

    if (mModel->needLeqFunction() && !mProfile->hasLeqOperator()
        && !mProfile->leqFunctionString().empty()) {
        if (!mCode.empty()) {
            mCode += "\n";
        }

        mCode += mProfile->leqFunctionString();
    }

    if (mModel->needGtFunction() && !mProfile->hasGtOperator()
        && !mProfile->gtFunctionString().empty()) {
        if (!mCode.empty()) {
            mCode += "\n";
        }

        mCode += mProfile->gtFunctionString();
    }

    if (mModel->needGeqFunction() && !mProfile->hasGeqOperator()
        && !mProfile->geqFunctionString().empty()) {
        if (!mCode.empty()) {
            mCode += "\n";
        }

        mCode += mProfile->geqFunctionString();
    }

    if (mModel->needAndFunction() && !mProfile->hasAndOperator()
        && !mProfile->andFunctionString().empty()) {
        if (!mCode.empty()) {
            mCode += "\n";
        }

        mCode += mProfile->andFunctionString();
    }

    if (mModel->needOrFunction() && !mProfile->hasOrOperator()
        && !mProfile->orFunctionString().empty()) {
        if (!mCode.empty()) {
            mCode += "\n";
        }

        mCode += mProfile->orFunctionString();
    }

    if (mModel->needXorFunction() && !mProfile->hasXorOperator()
        && !mProfile->xorFunctionString().empty()) {
        if (!mCode.empty()) {
            mCode += "\n";
        }

        mCode += mProfile->xorFunctionString();
    }

    if (mModel->needNotFunction() && !mProfile->hasNotOperator()
        && !mProfile->notFunctionString().empty()) {
        if (!mCode.empty()) {
            mCode += "\n";
        }

        mCode += mProfile->notFunctionString();
    }

    if (mModel->needMinFunction()
        && !mProfile->minFunctionString().empty()) {
        if (!mCode.empty()) {
            mCode += "\n";
        }

        mCode += mProfile->minFunctionString();
    }

    if (mModel->needMaxFunction()
        && !mProfile->maxFunctionString().empty()) {
        if (!mCode.empty()) {
            mCode += "\n";
        }

        mCode += mProfile->maxFunctionString();
    }
}

void Generator::GeneratorImpl::addTrigonometricFunctionsCode()
{
    if (mModel->needSecFunction()
        && !mProfile->secFunctionString().empty()) {
        if (!mCode.empty()) {
            mCode += "\n";
        }

        mCode += mProfile->secFunctionString();
    }

    if (mModel->needCscFunction()
        && !mProfile->cscFunctionString().empty()) {
        if (!mCode.empty()) {
            mCode += "\n";
        }

        mCode += mProfile->cscFunctionString();
    }

    if (mModel->needCotFunction()
        && !mProfile->cotFunctionString().empty()) {
        if (!mCode.empty()) {
            mCode += "\n";
        }

        mCode += mProfile->cotFunctionString();
    }

    if (mModel->needSechFunction()
        && !mProfile->sechFunctionString().empty()) {
        if (!mCode.empty()) {
            mCode += "\n";
        }

        mCode += mProfile->sechFunctionString();
    }

    if (mModel->needCschFunction()
        && !mProfile->cschFunctionString().empty()) {
        if (!mCode.empty()) {
            mCode += "\n";
        }

        mCode += mProfile->cschFunctionString();
    }

    if (mModel->needCothFunction()
        && !mProfile->cothFunctionString().empty()) {
        if (!mCode.empty()) {
            mCode += "\n";
        }

        mCode += mProfile->cothFunctionString();
    }

    if (mModel->needAsecFunction()
        && !mProfile->asecFunctionString().empty()) {
        if (!mCode.empty()) {
            mCode += "\n";
        }

        mCode += mProfile->asecFunctionString();
    }

    if (mModel->needAcscFunction()
        && !mProfile->acscFunctionString().empty()) {
        if (!mCode.empty()) {
            mCode += "\n";
        }

        mCode += mProfile->acscFunctionString();
    }

    if (mModel->needAcotFunction()
        && !mProfile->acotFunctionString().empty()) {
        if (!mCode.empty()) {
            mCode += "\n";
        }

        mCode += mProfile->acotFunctionString();
    }

    if (mModel->needAsechFunction()
        && !mProfile->asechFunctionString().empty()) {
        if (!mCode.empty()) {
            mCode += "\n";
        }

        mCode += mProfile->asechFunctionString();
    }

    if (mModel->needAcschFunction()
        && !mProfile->acschFunctionString().empty()) {
        if (!mCode.empty()) {
            mCode += "\n";
        }

        mCode += mProfile->acschFunctionString();
    }

    if (mModel->needAcothFunction()
        && !mProfile->acothFunctionString().empty()) {
        if (!mCode.empty()) {
            mCode += "\n";
        }

        mCode += mProfile->acothFunctionString();
    }
}

void Generator::GeneratorImpl::addInterfaceCreateDeleteArrayMethodsCode()
{
    std::string interfaceCreateDeleteArraysCode;

    if (!mProfile->interfaceCreateStatesArrayMethodString().empty()) {
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

void Generator::GeneratorImpl::addImplementationCreateStatesArrayMethodCode()
{
    if (!mProfile->implementationCreateStatesArrayMethodString().empty()) {
        if (!mCode.empty()) {
            mCode += "\n";
        }

        mCode += mProfile->implementationCreateStatesArrayMethodString();
    }
}

void Generator::GeneratorImpl::addImplementationCreateVariablesArrayMethodCode()
{
    if (!mProfile->implementationCreateVariablesArrayMethodString().empty()) {
        if (!mCode.empty()) {
            mCode += "\n";
        }

        mCode += mProfile->implementationCreateVariablesArrayMethodString();
    }
}

void Generator::GeneratorImpl::addImplementationDeleteArrayMethodCode()
{
    if (!mProfile->implementationDeleteArrayMethodString().empty()) {
        if (!mCode.empty()) {
            mCode += "\n";
        }

        mCode += mProfile->implementationDeleteArrayMethodString();
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

std::string Generator::GeneratorImpl::generateDoubleCode(const std::string &value)
{
    if (value.find('.') != std::string::npos) {
        return value;
    }

    size_t ePos = value.find('e');

    if (ePos == std::string::npos) {
        return value + ".0";
    }

    return value.substr(0, ePos) + ".0" + value.substr(ePos);
}

std::string Generator::GeneratorImpl::generateDoubleOrConstantVariableNameCode(const VariablePtr &variable)
{
    if (isCellMLReal(variable->initialValue())) {
        return generateDoubleCode(variable->initialValue());
    }

    VariablePtr initValueVariable = owningComponent(variable)->variable(variable->initialValue());
    AnalyserVariablePtr analyserInitialValueVariable = Generator::GeneratorImpl::analyserVariable(initValueVariable);
    std::ostringstream index;

    index << analyserInitialValueVariable->index();

    return mProfile->variablesArrayString() + mProfile->openArrayString() + index.str() + mProfile->closeArrayString();
}

std::string Generator::GeneratorImpl::generateVariableNameCode(const VariablePtr &variable,
                                                               const AnalyserEquationAstPtr &ast) const
{
    AnalyserVariablePtr analyserVariable = Generator::GeneratorImpl::analyserVariable(variable);

    if (analyserVariable->type() == AnalyserVariable::Type::VARIABLE_OF_INTEGRATION) {
        return mProfile->voiString();
    }

    std::string arrayName;

    if (analyserVariable->type() == AnalyserVariable::Type::STATE) {
        arrayName = ((ast != nullptr) && (ast->parent()->type() == AnalyserEquationAst::Type::DIFF)) ?
                        mProfile->ratesArrayString() :
                        mProfile->statesArrayString();
    } else {
        arrayName = mProfile->variablesArrayString();
    }

    std::ostringstream index;

    index << analyserVariable->index();

    return arrayName + mProfile->openArrayString() + index.str() + mProfile->closeArrayString();
}

std::string Generator::GeneratorImpl::generateOperatorCode(const std::string &op,
                                                           const AnalyserEquationAstPtr &ast)
{
    // Generate the code for the left and right branches of the given AST.

    std::string leftChild = generateCode(ast->leftChild());
    std::string rightChild = generateCode(ast->rightChild());

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
        if (isRelationalOperator(ast->leftChild())
            || isLogicalOperator(ast->leftChild())
            || isPiecewiseStatement(ast->leftChild())) {
            leftChild = "(" + leftChild + ")";
        }

        if (isRelationalOperator(ast->rightChild())
            || isLogicalOperator(ast->rightChild())
            || isPiecewiseStatement(ast->rightChild())) {
            rightChild = "(" + rightChild + ")";
        }
    } else if (isMinusOperator(ast)) {
        if (isRelationalOperator(ast->leftChild())
            || isLogicalOperator(ast->leftChild())
            || isPiecewiseStatement(ast->leftChild())) {
            leftChild = "(" + leftChild + ")";
        }

        if (isRelationalOperator(ast->rightChild())
            || isLogicalOperator(ast->rightChild())
            || isMinusOperator(ast->rightChild())
            || isPiecewiseStatement(ast->rightChild())) {
            rightChild = "(" + rightChild + ")";
        } else if (isPlusOperator(ast->rightChild())) {
            if (ast->rightChild()->rightChild() != nullptr) {
                rightChild = "(" + rightChild + ")";
            }
        }
    } else if (isTimesOperator(ast)) {
        if (isRelationalOperator(ast->leftChild())
            || isLogicalOperator(ast->leftChild())
            || isPiecewiseStatement(ast->leftChild())) {
            leftChild = "(" + leftChild + ")";
        } else if (isPlusOperator(ast->leftChild())
                   || isMinusOperator(ast->leftChild())) {
            if (ast->leftChild()->rightChild() != nullptr) {
                leftChild = "(" + leftChild + ")";
            }
        }

        if (isRelationalOperator(ast->rightChild())
            || isLogicalOperator(ast->rightChild())
            || isPiecewiseStatement(ast->rightChild())) {
            rightChild = "(" + rightChild + ")";
        } else if (isPlusOperator(ast->rightChild())
                   || isMinusOperator(ast->rightChild())) {
            if (ast->rightChild()->rightChild() != nullptr) {
                rightChild = "(" + rightChild + ")";
            }
        }
    } else if (isDivideOperator(ast)) {
        if (isRelationalOperator(ast->leftChild())
            || isLogicalOperator(ast->leftChild())
            || isPiecewiseStatement(ast->leftChild())) {
            leftChild = "(" + leftChild + ")";
        } else if (isPlusOperator(ast->leftChild())
                   || isMinusOperator(ast->leftChild())) {
            if (ast->leftChild()->rightChild() != nullptr) {
                leftChild = "(" + leftChild + ")";
            }
        }

        if (isRelationalOperator(ast->rightChild())
            || isLogicalOperator(ast->rightChild())
            || isTimesOperator(ast->rightChild())
            || isDivideOperator(ast->rightChild())
            || isPiecewiseStatement(ast->rightChild())) {
            rightChild = "(" + rightChild + ")";
        } else if (isPlusOperator(ast->rightChild())
                   || isMinusOperator(ast->rightChild())) {
            if (ast->rightChild()->rightChild() != nullptr) {
                rightChild = "(" + rightChild + ")";
            }
        }
    } else if (isAndOperator(ast)) {
        // Note: according to the precedence rules above, we only need to add
        //       parentheses around OR and PIECEWISE. However, it looks
        //       better/clearer to have some around some other operators
        //       (agreed, this is somewhat subjective).

        if (isRelationalOperator(ast->leftChild())
            || isOrOperator(ast->leftChild())
            || isXorOperator(ast->leftChild())
            || isPiecewiseStatement(ast->leftChild())) {
            leftChild = "(" + leftChild + ")";
        } else if (isPlusOperator(ast->leftChild())
                   || isMinusOperator(ast->leftChild())) {
            if (ast->leftChild()->rightChild() != nullptr) {
                leftChild = "(" + leftChild + ")";
            }
        } else if (isPowerOperator(ast->leftChild())) {
            leftChild = "(" + leftChild + ")";
        } else if (isRootOperator(ast->leftChild())) {
            leftChild = "(" + leftChild + ")";
        }

        if (isRelationalOperator(ast->rightChild())
            || isOrOperator(ast->rightChild())
            || isXorOperator(ast->rightChild())
            || isPiecewiseStatement(ast->rightChild())) {
            rightChild = "(" + rightChild + ")";
        } else if (isPlusOperator(ast->rightChild())
                   || isMinusOperator(ast->rightChild())) {
            if (ast->rightChild()->rightChild() != nullptr) {
                rightChild = "(" + rightChild + ")";
            }
        } else if (isPowerOperator(ast->rightChild())) {
            rightChild = "(" + rightChild + ")";
        } else if (isRootOperator(ast->rightChild())) {
            rightChild = "(" + rightChild + ")";
        }
    } else if (isOrOperator(ast)) {
        // Note: according to the precedence rules above, we only need to add
        //       parentheses around PIECEWISE. However, it looks better/clearer
        //       to have some around some other operators (agreed, this is
        //       somewhat subjective).

        if (isRelationalOperator(ast->leftChild())
            || isAndOperator(ast->leftChild())
            || isXorOperator(ast->leftChild())
            || isPiecewiseStatement(ast->leftChild())) {
            leftChild = "(" + leftChild + ")";
        } else if (isPlusOperator(ast->leftChild())
                   || isMinusOperator(ast->leftChild())) {
            if (ast->leftChild()->rightChild() != nullptr) {
                leftChild = "(" + leftChild + ")";
            }
        } else if (isPowerOperator(ast->leftChild())) {
            leftChild = "(" + leftChild + ")";
        } else if (isRootOperator(ast->leftChild())) {
            leftChild = "(" + leftChild + ")";
        }

        if (isRelationalOperator(ast->rightChild())
            || isAndOperator(ast->rightChild())
            || isXorOperator(ast->rightChild())
            || isPiecewiseStatement(ast->rightChild())) {
            rightChild = "(" + rightChild + ")";
        } else if (isPlusOperator(ast->rightChild())
                   || isMinusOperator(ast->rightChild())) {
            if (ast->rightChild()->rightChild() != nullptr) {
                rightChild = "(" + rightChild + ")";
            }
        } else if (isPowerOperator(ast->rightChild())) {
            rightChild = "(" + rightChild + ")";
        } else if (isRootOperator(ast->rightChild())) {
            rightChild = "(" + rightChild + ")";
        }
    } else if (isXorOperator(ast)) {
        // Note: according to the precedence rules above, we only need to add
        //       parentheses around AND, OR and PIECEWISE. However, it looks
        //       better/clearer to have some around some other operators
        //       (agreed, this is somewhat subjective).

        if (isRelationalOperator(ast->leftChild())
            || isAndOperator(ast->leftChild())
            || isOrOperator(ast->leftChild())
            || isPiecewiseStatement(ast->leftChild())) {
            leftChild = "(" + leftChild + ")";
        } else if (isPlusOperator(ast->leftChild())
                   || isMinusOperator(ast->leftChild())) {
            if (ast->leftChild()->rightChild() != nullptr) {
                leftChild = "(" + leftChild + ")";
            }
        } else if (isPowerOperator(ast->leftChild())) {
            leftChild = "(" + leftChild + ")";
        } else if (isRootOperator(ast->leftChild())) {
            leftChild = "(" + leftChild + ")";
        }

        if (isRelationalOperator(ast->rightChild())
            || isAndOperator(ast->rightChild())
            || isOrOperator(ast->rightChild())
            || isPiecewiseStatement(ast->rightChild())) {
            rightChild = "(" + rightChild + ")";
        } else if (isPlusOperator(ast->rightChild())
                   || isMinusOperator(ast->rightChild())) {
            if (ast->rightChild()->rightChild() != nullptr) {
                rightChild = "(" + rightChild + ")";
            }
        } else if (isPowerOperator(ast->rightChild())) {
            rightChild = "(" + rightChild + ")";
        } else if (isRootOperator(ast->rightChild())) {
            rightChild = "(" + rightChild + ")";
        }
    } else if (isPowerOperator(ast)) {
        if (isRelationalOperator(ast->leftChild())
            || isLogicalOperator(ast->leftChild())
            || isMinusOperator(ast->leftChild())
            || isTimesOperator(ast->leftChild())
            || isDivideOperator(ast->leftChild())
            || isPiecewiseStatement(ast->leftChild())) {
            leftChild = "(" + leftChild + ")";
        } else if (isPlusOperator(ast->leftChild())) {
            if (ast->leftChild()->rightChild() != nullptr) {
                leftChild = "(" + leftChild + ")";
            }
        }

        if (isRelationalOperator(ast->rightChild())
            || isLogicalOperator(ast->rightChild())
            || isMinusOperator(ast->leftChild())
            || isTimesOperator(ast->rightChild())
            || isDivideOperator(ast->rightChild())
            || isPowerOperator(ast->rightChild())
            || isRootOperator(ast->rightChild())
            || isPiecewiseStatement(ast->rightChild())) {
            rightChild = "(" + rightChild + ")";
        } else if (isPlusOperator(ast->rightChild())) {
            if (ast->rightChild()->rightChild() != nullptr) {
                rightChild = "(" + rightChild + ")";
            }
        }
    } else if (isRootOperator(ast)) {
        if (isRelationalOperator(ast->rightChild())
            || isLogicalOperator(ast->rightChild())
            || isMinusOperator(ast->rightChild())
            || isTimesOperator(ast->rightChild())
            || isDivideOperator(ast->rightChild())
            || isPiecewiseStatement(ast->rightChild())) {
            rightChild = "(" + rightChild + ")";
        } else if (isPlusOperator(ast->rightChild())) {
            if (ast->rightChild()->rightChild() != nullptr) {
                rightChild = "(" + rightChild + ")";
            }
        }

        if (isRelationalOperator(ast->leftChild())
            || isLogicalOperator(ast->leftChild())
            || isMinusOperator(ast->leftChild())
            || isTimesOperator(ast->leftChild())
            || isDivideOperator(ast->leftChild())
            || isPowerOperator(ast->leftChild())
            || isRootOperator(ast->leftChild())
            || isPiecewiseStatement(ast->leftChild())) {
            leftChild = "(" + leftChild + ")";
        } else if (isPlusOperator(ast->leftChild())) {
            if (ast->leftChild()->rightChild() != nullptr) {
                leftChild = "(" + leftChild + ")";
            }
        }

        return rightChild + op + "(1.0/" + leftChild + ")";
    }

    return leftChild + op + rightChild;
}

std::string Generator::GeneratorImpl::generateMinusUnaryCode(const AnalyserEquationAstPtr &ast)
{
    // Generate the code for the left branch of the given AST.

    std::string left = generateCode(ast->leftChild());

    // Determine whether parentheses should be added around the left code.

    if (isRelationalOperator(ast->leftChild())
        || isLogicalOperator(ast->leftChild())
        || isPlusOperator(ast->leftChild())
        || isMinusOperator(ast->leftChild())
        || isPiecewiseStatement(ast->leftChild())) {
        left = "(" + left + ")";
    }

    return mProfile->minusString() + left;
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
                                                              const std::string &value)
{
    return replace(replace(mProfile->hasConditionalOperator() ?
                               mProfile->conditionalOperatorIfString() :
                               mProfile->piecewiseIfString(),
                           "<CONDITION>", condition),
                   "<IF_STATEMENT>", value);
}

std::string Generator::GeneratorImpl::generatePiecewiseElseCode(const std::string &value)
{
    return replace(mProfile->hasConditionalOperator() ?
                       mProfile->conditionalOperatorElseString() :
                       mProfile->piecewiseElseString(),
                   "<ELSE_STATEMENT>", value);
}

std::string Generator::GeneratorImpl::generateCode(const AnalyserEquationAstPtr &ast)
{
    // Generate the code for the given AST.

    std::string code;

    switch (ast->type()) {
        // Assignment.

    case AnalyserEquationAst::Type::ASSIGNMENT:
        code = generateOperatorCode(mProfile->assignmentString(), ast);

        break;

        // Relational and logical operators.

    case AnalyserEquationAst::Type::EQ:
        if (mProfile->hasEqOperator()) {
            code = generateOperatorCode(mProfile->eqString(), ast);
        } else {
            code = generateTwoParameterFunctionCode(mProfile->eqString(), ast);
        }

        break;
    case AnalyserEquationAst::Type::NEQ:
        if (mProfile->hasNeqOperator()) {
            code = generateOperatorCode(mProfile->neqString(), ast);
        } else {
            code = generateTwoParameterFunctionCode(mProfile->neqString(), ast);
        }

        break;
    case AnalyserEquationAst::Type::LT:
        if (mProfile->hasLtOperator()) {
            code = generateOperatorCode(mProfile->ltString(), ast);
        } else {
            code = generateTwoParameterFunctionCode(mProfile->ltString(), ast);
        }

        break;
    case AnalyserEquationAst::Type::LEQ:
        if (mProfile->hasLeqOperator()) {
            code = generateOperatorCode(mProfile->leqString(), ast);
        } else {
            code = generateTwoParameterFunctionCode(mProfile->leqString(), ast);
        }

        break;
    case AnalyserEquationAst::Type::GT:
        if (mProfile->hasGtOperator()) {
            code = generateOperatorCode(mProfile->gtString(), ast);
        } else {
            code = generateTwoParameterFunctionCode(mProfile->gtString(), ast);
        }

        break;
    case AnalyserEquationAst::Type::GEQ:
        if (mProfile->hasGeqOperator()) {
            code = generateOperatorCode(mProfile->geqString(), ast);
        } else {
            code = generateTwoParameterFunctionCode(mProfile->geqString(), ast);
        }

        break;
    case AnalyserEquationAst::Type::AND:
        if (mProfile->hasAndOperator()) {
            code = generateOperatorCode(mProfile->andString(), ast);
        } else {
            code = generateTwoParameterFunctionCode(mProfile->andString(), ast);
        }

        break;
    case AnalyserEquationAst::Type::OR:
        if (mProfile->hasOrOperator()) {
            code = generateOperatorCode(mProfile->orString(), ast);
        } else {
            code = generateTwoParameterFunctionCode(mProfile->orString(), ast);
        }

        break;
    case AnalyserEquationAst::Type::XOR:
        if (mProfile->hasXorOperator()) {
            code = generateOperatorCode(mProfile->xorString(), ast);
        } else {
            code = generateTwoParameterFunctionCode(mProfile->xorString(), ast);
        }

        break;
    case AnalyserEquationAst::Type::NOT:
        if (mProfile->hasNotOperator()) {
            code = mProfile->notString() + generateCode(ast->leftChild());
        } else {
            code = generateOneParameterFunctionCode(mProfile->notString(), ast);
        }

        break;

        // Arithmetic operators.

    case AnalyserEquationAst::Type::PLUS:
        if (ast->rightChild() != nullptr) {
            code = generateOperatorCode(mProfile->plusString(), ast);
        } else {
            code = generateCode(ast->leftChild());
        }

        break;
    case AnalyserEquationAst::Type::MINUS:
        if (ast->rightChild() != nullptr) {
            code = generateOperatorCode(mProfile->minusString(), ast);
        } else {
            code = generateMinusUnaryCode(ast);
        }

        break;
    case AnalyserEquationAst::Type::TIMES:
        code = generateOperatorCode(mProfile->timesString(), ast);

        break;
    case AnalyserEquationAst::Type::DIVIDE:
        code = generateOperatorCode(mProfile->divideString(), ast);

        break;
    case AnalyserEquationAst::Type::POWER: {
        std::string stringValue = generateCode(ast->rightChild());
        double doubleValue;
        bool validConversion = convertToDouble(stringValue, doubleValue);

        if (validConversion && areEqual(doubleValue, 0.5)) {
            code = generateOneParameterFunctionCode(mProfile->squareRootString(), ast);
        } else if (validConversion && areEqual(doubleValue, 2.0)
                   && !mProfile->squareString().empty()) {
            code = generateOneParameterFunctionCode(mProfile->squareString(), ast);
        } else {
            code = mProfile->hasPowerOperator() ?
                       generateOperatorCode(mProfile->powerString(), ast) :
                       mProfile->powerString() + "(" + generateCode(ast->leftChild()) + ", " + stringValue + ")";
        }

        break;
    }
    case AnalyserEquationAst::Type::ROOT:
        if (ast->rightChild() != nullptr) {
            double doubleValue;

            if (convertToDouble(generateCode(ast->leftChild()), doubleValue)
                && areEqual(doubleValue, 2.0)) {
                code = mProfile->squareRootString() + "(" + generateCode(ast->rightChild()) + ")";
            } else {
                AnalyserEquationAstPtr rootValueAst = AnalyserEquationAst::create(AnalyserEquationAst::Type::DIVIDE, ast);

                rootValueAst->setLeftChild(AnalyserEquationAst::create(AnalyserEquationAst::Type::CN, "1.0", rootValueAst));
                rootValueAst->setRightChild(AnalyserEquationAst::create(ast->leftChild(), rootValueAst));

                code = mProfile->hasPowerOperator() ?
                           generateOperatorCode(mProfile->powerString(), ast) :
                           mProfile->powerString() + "(" + generateCode(ast->rightChild()) + ", " + generateOperatorCode(mProfile->divideString(), rootValueAst) + ")";
            }
        } else {
            code = generateOneParameterFunctionCode(mProfile->squareRootString(), ast);
        }

        break;
    case AnalyserEquationAst::Type::ABS:
        code = generateOneParameterFunctionCode(mProfile->absoluteValueString(), ast);

        break;
    case AnalyserEquationAst::Type::EXP:
        code = generateOneParameterFunctionCode(mProfile->exponentialString(), ast);

        break;
    case AnalyserEquationAst::Type::LN:
        code = generateOneParameterFunctionCode(mProfile->napierianLogarithmString(), ast);

        break;
    case AnalyserEquationAst::Type::LOG:
        if (ast->rightChild() != nullptr) {
            std::string stringValue = generateCode(ast->leftChild());
            double doubleValue;

            if (convertToDouble(stringValue, doubleValue)
                && areEqual(doubleValue, 10.0)) {
                code = mProfile->commonLogarithmString() + "(" + generateCode(ast->rightChild()) + ")";
            } else {
                code = mProfile->napierianLogarithmString() + "(" + generateCode(ast->rightChild()) + ")/" + mProfile->napierianLogarithmString() + "(" + stringValue + ")";
            }
        } else {
            code = generateOneParameterFunctionCode(mProfile->commonLogarithmString(), ast);
        }

        break;
    case AnalyserEquationAst::Type::CEILING:
        code = generateOneParameterFunctionCode(mProfile->ceilingString(), ast);

        break;
    case AnalyserEquationAst::Type::FLOOR:
        code = generateOneParameterFunctionCode(mProfile->floorString(), ast);

        break;
    case AnalyserEquationAst::Type::MIN:
        code = generateTwoParameterFunctionCode(mProfile->minString(), ast);

        break;
    case AnalyserEquationAst::Type::MAX:
        code = generateTwoParameterFunctionCode(mProfile->maxString(), ast);

        break;
    case AnalyserEquationAst::Type::REM:
        code = generateTwoParameterFunctionCode(mProfile->remString(), ast);

        break;

        // Calculus elements.

    case AnalyserEquationAst::Type::DIFF:
        code = generateCode(ast->rightChild());

        break;

        // Trigonometric operators.

    case AnalyserEquationAst::Type::SIN:
        code = generateOneParameterFunctionCode(mProfile->sinString(), ast);

        break;
    case AnalyserEquationAst::Type::COS:
        code = generateOneParameterFunctionCode(mProfile->cosString(), ast);

        break;
    case AnalyserEquationAst::Type::TAN:
        code = generateOneParameterFunctionCode(mProfile->tanString(), ast);

        break;
    case AnalyserEquationAst::Type::SEC:
        code = generateOneParameterFunctionCode(mProfile->secString(), ast);

        break;
    case AnalyserEquationAst::Type::CSC:
        code = generateOneParameterFunctionCode(mProfile->cscString(), ast);

        break;
    case AnalyserEquationAst::Type::COT:
        code = generateOneParameterFunctionCode(mProfile->cotString(), ast);

        break;
    case AnalyserEquationAst::Type::SINH:
        code = generateOneParameterFunctionCode(mProfile->sinhString(), ast);

        break;
    case AnalyserEquationAst::Type::COSH:
        code = generateOneParameterFunctionCode(mProfile->coshString(), ast);

        break;
    case AnalyserEquationAst::Type::TANH:
        code = generateOneParameterFunctionCode(mProfile->tanhString(), ast);

        break;
    case AnalyserEquationAst::Type::SECH:
        code = generateOneParameterFunctionCode(mProfile->sechString(), ast);

        break;
    case AnalyserEquationAst::Type::CSCH:
        code = generateOneParameterFunctionCode(mProfile->cschString(), ast);

        break;
    case AnalyserEquationAst::Type::COTH:
        code = generateOneParameterFunctionCode(mProfile->cothString(), ast);

        break;
    case AnalyserEquationAst::Type::ASIN:
        code = generateOneParameterFunctionCode(mProfile->asinString(), ast);

        break;
    case AnalyserEquationAst::Type::ACOS:
        code = generateOneParameterFunctionCode(mProfile->acosString(), ast);

        break;
    case AnalyserEquationAst::Type::ATAN:
        code = generateOneParameterFunctionCode(mProfile->atanString(), ast);

        break;
    case AnalyserEquationAst::Type::ASEC:
        code = generateOneParameterFunctionCode(mProfile->asecString(), ast);

        break;
    case AnalyserEquationAst::Type::ACSC:
        code = generateOneParameterFunctionCode(mProfile->acscString(), ast);

        break;
    case AnalyserEquationAst::Type::ACOT:
        code = generateOneParameterFunctionCode(mProfile->acotString(), ast);

        break;
    case AnalyserEquationAst::Type::ASINH:
        code = generateOneParameterFunctionCode(mProfile->asinhString(), ast);

        break;
    case AnalyserEquationAst::Type::ACOSH:
        code = generateOneParameterFunctionCode(mProfile->acoshString(), ast);

        break;
    case AnalyserEquationAst::Type::ATANH:
        code = generateOneParameterFunctionCode(mProfile->atanhString(), ast);

        break;
    case AnalyserEquationAst::Type::ASECH:
        code = generateOneParameterFunctionCode(mProfile->asechString(), ast);

        break;
    case AnalyserEquationAst::Type::ACSCH:
        code = generateOneParameterFunctionCode(mProfile->acschString(), ast);

        break;
    case AnalyserEquationAst::Type::ACOTH:
        code = generateOneParameterFunctionCode(mProfile->acothString(), ast);

        break;

        // Piecewise statement.

    case AnalyserEquationAst::Type::PIECEWISE:
        if (ast->rightChild() != nullptr) {
            if (ast->rightChild()->type() == AnalyserEquationAst::Type::PIECE) {
                code = generateCode(ast->leftChild()) + generatePiecewiseElseCode(generateCode(ast->rightChild()) + generatePiecewiseElseCode(mProfile->nanString()));
            } else {
                code = generateCode(ast->leftChild()) + generatePiecewiseElseCode(generateCode(ast->rightChild()));
            }
        } else {
            code = generateCode(ast->leftChild()) + generatePiecewiseElseCode(mProfile->nanString());
        }

        break;
    case AnalyserEquationAst::Type::PIECE:
        code = generatePiecewiseIfCode(generateCode(ast->rightChild()), generateCode(ast->leftChild()));

        break;
    case AnalyserEquationAst::Type::OTHERWISE:
        code = generateCode(ast->leftChild());

        break;

        // Token elements.

    case AnalyserEquationAst::Type::CI:
        code = generateVariableNameCode(ast->variable(), ast);

        break;
    case AnalyserEquationAst::Type::CN:
        code = generateDoubleCode(ast->value());

        break;

        // Qualifier elements.

    case AnalyserEquationAst::Type::DEGREE:
    case AnalyserEquationAst::Type::LOGBASE:
    case AnalyserEquationAst::Type::BVAR:
        code = generateCode(ast->leftChild());

        break;

        // Constants.

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
    case AnalyserEquationAst::Type::NAN:
        code = mProfile->nanString();

        break;
    }

    return code;
}

std::string Generator::GeneratorImpl::generateInitializationCode(const AnalyserVariablePtr &variable)
{
    std::string scalingFactorCode;
    double scalingFactor = Generator::GeneratorImpl::scalingFactor(variable->initialisingVariable());

    if (!areEqual(scalingFactor, 1.0)) {
        scalingFactorCode = generateDoubleCode(convertToString(1.0 / scalingFactor)) + mProfile->timesString();
    }

    return mProfile->indentString() + generateVariableNameCode(variable->variable()) + " = " + scalingFactorCode + generateDoubleOrConstantVariableNameCode(variable->initialisingVariable()) + mProfile->commandSeparatorString() + "\n";
}

std::string Generator::GeneratorImpl::generateEquationCode(const AnalyserEquationPtr &equation,
                                                           std::vector<AnalyserEquationPtr> &remainingEquations,
                                                           bool onlyStateRateBasedEquations)
{
    std::string res;

    for (const auto &dependency : equation->dependencies()) {
        if (!onlyStateRateBasedEquations
            || ((dependency->type() == AnalyserEquation::Type::ALGEBRAIC)
                && dependency->isStateRateBased())) {
            res += generateEquationCode(dependency, remainingEquations, onlyStateRateBasedEquations);
        }
    }

    auto equationIter = std::find(remainingEquations.begin(), remainingEquations.end(), equation);

    if (equationIter != remainingEquations.end()) {
        res += mProfile->indentString() + generateCode(equation->ast()) + mProfile->commandSeparatorString() + "\n";

        remainingEquations.erase(equationIter);
    }

    return res;
}

void Generator::GeneratorImpl::addInterfaceComputeModelMethodsCode()
{
    std::string interfaceComputeModelMethodsCode;

    if (!mProfile->interfaceInitializeStatesAndConstantsMethodString().empty()) {
        interfaceComputeModelMethodsCode += mProfile->interfaceInitializeStatesAndConstantsMethodString();
    }

    if (!mProfile->interfaceComputeComputedConstantsMethodString().empty()) {
        interfaceComputeModelMethodsCode += mProfile->interfaceComputeComputedConstantsMethodString();
    }

    if (!mProfile->interfaceComputeRatesMethodString().empty()) {
        interfaceComputeModelMethodsCode += mProfile->interfaceComputeRatesMethodString();
    }

    if (!mProfile->interfaceComputeVariablesMethodString().empty()) {
        interfaceComputeModelMethodsCode += mProfile->interfaceComputeVariablesMethodString();
    }

    if (!interfaceComputeModelMethodsCode.empty()) {
        mCode += "\n";
    }

    mCode += interfaceComputeModelMethodsCode;
}

void Generator::GeneratorImpl::addImplementationInitializeStatesAndConstantsMethodCode(std::vector<AnalyserEquationPtr> &remainingEquations)
{
    if (!mProfile->implementationInitializeStatesAndConstantsMethodString().empty()) {
        if (!mCode.empty()) {
            mCode += "\n";
        }

        std::string methodBody;

        for (const auto &variable : mModel->variables()) {
            if (variable->type() == AnalyserVariable::Type::CONSTANT) {
                methodBody += generateInitializationCode(variable);
            }
        }

        for (const auto &equation : mModel->equations()) {
            if (equation->type() == AnalyserEquation::Type::TRUE_CONSTANT) {
                methodBody += generateEquationCode(equation, remainingEquations);
            }
        }

        for (const auto &state : mModel->states()) {
            methodBody += generateInitializationCode(state);
        }

        mCode += replace(mProfile->implementationInitializeStatesAndConstantsMethodString(),
                         "<CODE>", generateMethodBodyCode(methodBody));
    }
}

void Generator::GeneratorImpl::addImplementationComputeComputedConstantsMethodCode(std::vector<AnalyserEquationPtr> &remainingEquations)
{
    if (!mProfile->implementationComputeComputedConstantsMethodString().empty()) {
        if (!mCode.empty()) {
            mCode += "\n";
        }

        std::string methodBody;

        for (const auto &equation : mModel->equations()) {
            if (equation->type() == AnalyserEquation::Type::VARIABLE_BASED_CONSTANT) {
                methodBody += generateEquationCode(equation, remainingEquations);
            }
        }

        mCode += replace(mProfile->implementationComputeComputedConstantsMethodString(),
                         "<CODE>", generateMethodBodyCode(methodBody));
    }
}

void Generator::GeneratorImpl::addImplementationComputeRatesMethodCode(std::vector<AnalyserEquationPtr> &remainingEquations)
{
    if (!mProfile->implementationComputeRatesMethodString().empty()) {
        if (!mCode.empty()) {
            mCode += "\n";
        }

        std::string methodBody;

        for (const auto &equation : mModel->equations()) {
            if (equation->type() == AnalyserEquation::Type::RATE) {
                methodBody += generateEquationCode(equation, remainingEquations);
            }
        }

        mCode += replace(mProfile->implementationComputeRatesMethodString(),
                         "<CODE>", generateMethodBodyCode(methodBody));
    }
}

void Generator::GeneratorImpl::addImplementationComputeVariablesMethodCode(std::vector<AnalyserEquationPtr> &remainingEquations)
{
    if (!mProfile->implementationComputeVariablesMethodString().empty()) {
        if (!mCode.empty()) {
            mCode += "\n";
        }

        auto equations = mModel->equations();
        std::vector<AnalyserEquationPtr> newRemainingEquations {std::begin(equations), std::end(equations)};

        std::string methodBody;

        for (const auto &equation : equations) {
            if ((std::find(remainingEquations.begin(), remainingEquations.end(), equation) != remainingEquations.end())
                || ((equation->type() == AnalyserEquation::Type::ALGEBRAIC)
                    && equation->isStateRateBased())) {
                methodBody += generateEquationCode(equation, newRemainingEquations, true);
            }
        }

        mCode += replace(mProfile->implementationComputeVariablesMethodString(),
                         "<CODE>", generateMethodBodyCode(methodBody));
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
    return mPimpl->mProfile;
}

void Generator::setProfile(const GeneratorProfilePtr &profile)
{
    mPimpl->mProfile = profile;
}

std::string Generator::interfaceCode(const AnalyserModelPtr &model) const
{
    if (!model->isValid() || !mPimpl->mProfile->hasInterface()) {
        return {};
    }

    // Keep track of the model (so we don't have to keep passing it around).

    mPimpl->mModel = model;

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

    if (mPimpl->mProfile->hasInterface()) {
        mPimpl->addVariableTypeObjectCode();
        mPimpl->addVariableInfoObjectCode();
        mPimpl->addVariableInfoWithTypeObjectCode();
    }

    // Add code for the interface of the information about the variable of
    // integration, states and (other) variables.

    mPimpl->addInterfaceVoiStateAndVariableInfoCode();

    // Add code for the interface to create and delete arrays.

    mPimpl->addInterfaceCreateDeleteArrayMethodsCode();

    // Add code for the interface to compute the model.

    mPimpl->addInterfaceComputeModelMethodsCode();

    return mPimpl->mCode;
}

std::string Generator::implementationCode(const AnalyserModelPtr &model) const
{
    if (!model->isValid()) {
        return {};
    }

    // Keep track of the model (so we don't have to keep passing it around).

    mPimpl->mModel = model;

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

    if (!mPimpl->mProfile->hasInterface()) {
        mPimpl->addVariableTypeObjectCode();
        mPimpl->addVariableInfoObjectCode();
        mPimpl->addVariableInfoWithTypeObjectCode();
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

    auto equations = mPimpl->mModel->equations();
    std::vector<AnalyserEquationPtr> remainingEquations {std::begin(equations), std::end(equations)};

    mPimpl->addImplementationInitializeStatesAndConstantsMethodCode(remainingEquations);

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

    return mPimpl->mCode;
}

} // namespace libcellml

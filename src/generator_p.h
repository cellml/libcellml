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

#pragma once

#include "libcellml/generator.h"

#include "libcellml/generatorprofile.h"

namespace libcellml {

using AnalyserModelWeakPtr = std::weak_ptr<AnalyserModel>; /**< Type definition for weak analyser model pointer. */
using GeneratorProfileWeakPtr = std::weak_ptr<GeneratorProfile>; /**< Type definition for weak generator profile pointer. */

/**
 * @brief The Generator::GeneratorImpl struct.
 *
 * The private implementation for the Generator class.
 */
struct Generator::GeneratorImpl
{
    Generator *mGenerator = nullptr;

    AnalyserModelWeakPtr mModel;
    AnalyserModelPtr mLockedModel;

    std::string mCode;

    GeneratorProfilePtr mOwnedProfile = GeneratorProfile::create();
    GeneratorProfileWeakPtr mProfile;
    GeneratorProfilePtr mLockedProfile;

    bool retrieveLockedModelAndProfile();
    void resetLockedModelAndProfile();

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

    void updateVariableInfoSizes(size_t &componentSize, size_t &nameSize,
                                 size_t &unitsSize,
                                 const AnalyserVariablePtr &variable) const;

    bool modifiedProfile() const;

    std::string newLineIfNeeded();

    void addOriginCommentCode();

    void addInterfaceHeaderCode();
    void addImplementationHeaderCode();

    void addVersionAndLibcellmlVersionCode(bool interface = false);

    void addStateAndVariableCountCode(bool interface = false);

    void addVariableTypeObjectCode();

    std::string generateVariableInfoObjectCode(const std::string &objectString) const;

    void addVariableInfoObjectCode();

    std::string generateVariableInfoEntryCode(const std::string &name,
                                              const std::string &units,
                                              const std::string &component,
                                              const std::string &type) const;

    void addInterfaceVoiStateAndVariableInfoCode();
    void addImplementationVoiInfoCode();
    void addImplementationStateInfoCode();
    void addImplementationVariableInfoCode();

    void addArithmeticFunctionsCode();
    void addTrigonometricFunctionsCode();

    void addInterfaceCreateDeleteArrayMethodsCode();
    void addExternalVariableMethodTypeDefinitionCode();
    void addImplementationCreateStatesArrayMethodCode();
    void addImplementationCreateVariablesArrayMethodCode();
    void addImplementationDeleteArrayMethodCode();

    void addRootFindingInfoObjectCode();
    void addExternNlaSolveMethodCode();

    std::string generateMethodBodyCode(const std::string &methodBody) const;

    std::string generateDoubleCode(const std::string &value) const;
    std::string generateDoubleOrConstantVariableNameCode(const VariablePtr &variable) const;
    std::string generateVariableNameCode(const VariablePtr &variable,
                                         const AnalyserEquationAstPtr &ast = nullptr) const;

    std::string generateOperatorCode(const std::string &op,
                                     const AnalyserEquationAstPtr &ast) const;
    std::string generateMinusUnaryCode(const AnalyserEquationAstPtr &ast) const;
    std::string generateOneParameterFunctionCode(const std::string &function,
                                                 const AnalyserEquationAstPtr &ast) const;
    std::string generateTwoParameterFunctionCode(const std::string &function,
                                                 const AnalyserEquationAstPtr &ast) const;
    std::string generatePiecewiseIfCode(const std::string &condition,
                                        const std::string &value) const;
    std::string generatePiecewiseElseCode(const std::string &value) const;
    std::string generateCode(const AnalyserEquationAstPtr &ast) const;

    std::string generateInitialisationCode(const AnalyserVariablePtr &variable) const;
    std::string generateEquationCode(const AnalyserEquationPtr &equation,
                                     std::vector<AnalyserEquationPtr> &remainingEquations,
                                     bool forComputeVariables = false) const;

    void addInterfaceComputeModelMethodsCode();
    void addImplementationInitialiseVariablesMethodCode(std::vector<AnalyserEquationPtr> &remainingEquations);
    void addImplementationComputeComputedConstantsMethodCode(std::vector<AnalyserEquationPtr> &remainingEquations);
    void addImplementationComputeRatesMethodCode(std::vector<AnalyserEquationPtr> &remainingEquations);
    void addImplementationComputeVariablesMethodCode(std::vector<AnalyserEquationPtr> &remainingEquations);
};

} // namespace libcellml

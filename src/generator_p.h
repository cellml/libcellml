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

#include "issue_p.h"
#include "logger_p.h"
#include "utilities.h"

namespace libcellml {

std::string generateDoubleCode(const std::string &value);

/**
 * @brief The Generator::GeneratorImpl struct.
 *
 * The private implementation for the Generator class.
 */
struct Generator::GeneratorImpl: public Logger::LoggerImpl
{
    std::string mCode;

    GeneratorContextPtr mContext;
    GeneratorProfilePtr mProfile = GeneratorProfile::create();

    std::map<AnalyserModelPtr, std::map<AnalyserVariablePtr, bool>> mTrackedVariables;

    void reset();

    std::string analyserVariableIndexString(const AnalyserModelPtr &analyserModel,
                                            const AnalyserVariablePtr &analyserVariable);

    bool isTrackedEquation(const AnalyserEquationPtr &analyserEquation, bool tracked);

    bool isTrackedVariable(const AnalyserModelPtr &analyserModel, const AnalyserVariablePtr &analyserVariable, bool tracked); //---GRY--- TO BE DELETED.
    bool isTrackedVariable(const AnalyserVariablePtr &analyserVariable, bool tracked); //---GRY--- TO BE DELETED.

    void addTrackingIssue(const AnalyserVariablePtr &analyserVariable, bool tracked, const std::string &variableInfo, //---GRY--- TO BE DELETED.
                          const std::string &trackedInfo, const std::string &untrackedInfo,
                          Issue::ReferenceRule trackedReferenceRule, Issue::ReferenceRule untrackedReferenceRule);

    void addNeededToComputeExternalVariableIssue(const AnalyserVariablePtr &analyserVariable, bool tracked); //---GRY--- TO BE DELETED.

    bool trackableVariable(const AnalyserVariablePtr &analyserVariable, bool tracked, bool canAddIssue = true); //---GRY--- TO BE DELETED.
    bool specialVariable(const AnalyserVariablePtr &analyserVariable, const AnalyserVariablePtr &specialAnalyserVariable, bool tracked, //---GRY--- TO BE DELETED.
                         Issue::ReferenceRule trackedReferenceRule, Issue::ReferenceRule untrackedReferenceRule);

    void trackVariable(const AnalyserVariablePtr &analyserVariable, bool tracked, bool needRemoveAllIssues = true); //---GRY--- TO BE DELETED.

    void trackVariables(const std::vector<AnalyserVariablePtr> &analyserVariables, bool tracked); //---GRY--- TO BE DELETED.

    bool validAnalyserModel(const AnalyserModelPtr &analyserModel); //---GRY--- TO BE DELETED.

    void trackAllConstants(const AnalyserModelPtr &analyserModel, bool tracked); //---GRY--- TO BE DELETED.
    void trackAllComputedConstants(const AnalyserModelPtr &analyserModel, bool tracked); //---GRY--- TO BE DELETED.
    void trackAllAlgebraicVariables(const AnalyserModelPtr &analyserModel, bool tracked); //---GRY--- TO BE DELETED.

    std::vector<AnalyserVariablePtr> trackableVariables(const AnalyserModelPtr &analyserModel) const; //---GRY--- TO BE DELETED.

    void trackAllVariables(const AnalyserModelPtr &analyserModel, bool tracked); //---GRY--- TO BE DELETED.

    size_t trackedVariableCount(const AnalyserModelPtr &analyserModel, //---GRY--- TO BE DELETED.
                                const std::vector<AnalyserVariablePtr> &analyserVariables, bool tracked);

    size_t trackedConstantCount(const AnalyserModelPtr &analyserModel, bool tracked); //---GRY--- TO BE DELETED.
    size_t trackedComputedConstantCount(const AnalyserModelPtr &analyserModel, bool tracked); //---GRY--- TO BE DELETED.
    size_t trackedAlgebraicCount(const AnalyserModelPtr &analyserModel, bool tracked); //---GRY--- TO BE DELETED.
    size_t trackedVariableCount(const AnalyserModelPtr &analyserModel, bool tracked); //---GRY--- TO BE DELETED.

    bool modelHasOdes(const AnalyserModelPtr &analyserModel) const;

    double scalingFactor(const AnalyserModelPtr &analyserModel, const VariablePtr &variable) const;

    bool isNegativeNumber(const AnalyserEquationAstPtr &ast) const;

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
                                 const AnalyserVariablePtr &analyserVariable) const;

    bool modifiedProfile() const;

    std::string newLineIfNeeded();

    void addOriginCommentCode();

    void addInterfaceHeaderCode();
    void addImplementationHeaderCode();

    void addVersionAndLibcellmlVersionCode(bool interface = false);

    void addStateAndVariableCountCode(const AnalyserModelPtr &analyserModel, bool interface = false);

    std::string generateVariableInfoObjectCode(const AnalyserModelPtr &analyserModel, const std::string &objectString);

    void addVariableInfoObjectCode(const AnalyserModelPtr &analyserModel);

    std::string generateVariableInfoEntryCode(const std::string &name,
                                              const std::string &units,
                                              const std::string &component) const;

    void addInterfaceVariableInfoCode(const AnalyserModelPtr &analyserModel);

    void addImplementationVariableInfoCode(const std::string &variableInfoString,
                                           const std::vector<AnalyserVariablePtr> &analyserVariables, bool voiVariable);
    void addImplementationVariableInfoCode(const AnalyserModelPtr &analyserModel);

    void addArithmeticFunctionsCode(const AnalyserModelPtr &analyserModel);
    void addTrigonometricFunctionsCode(const AnalyserModelPtr &analyserModel);

    void addInterfaceCreateDeleteArrayMethodsCode(const AnalyserModelPtr &analyserModel);
    void addImplementationCreateDeleteArrayMethodsCode(const AnalyserModelPtr &analyserModel);

    void addExternalVariableMethodTypeDefinitionCode(const AnalyserModelPtr &analyserModel);

    void addRootFindingInfoObjectCode(const AnalyserModelPtr &analyserModel);
    void addExternNlaSolveMethodCode();
    void addNlaSystemsCode(const AnalyserModelPtr &analyserModel);

    std::string generateMethodBodyCode(const std::string &methodBody) const;

    std::string generateDoubleOrVariableNameCode(const AnalyserModelPtr &analyserModel, const VariablePtr &variable);
    std::string generateVariableNameCode(const AnalyserModelPtr &analyserModel, const VariablePtr &variable,
                                         bool state = true);

    std::string generateOperatorCode(const AnalyserModelPtr &analyserModel, const std::string &op,
                                     const AnalyserEquationAstPtr &ast);
    std::string generateMinusUnaryCode(const AnalyserModelPtr &analyserModel, const AnalyserEquationAstPtr &ast);
    std::string generateOneParameterFunctionCode(const AnalyserModelPtr &analyserModel, const std::string &function,
                                                 const AnalyserEquationAstPtr &ast);
    std::string generateTwoParameterFunctionCode(const AnalyserModelPtr &analyserModel, const std::string &function,
                                                 const AnalyserEquationAstPtr &ast);
    std::string generatePiecewiseIfCode(const std::string &condition,
                                        const std::string &value) const;
    std::string generatePiecewiseElseCode(const std::string &value) const;
    std::string generateCode(const AnalyserModelPtr &analyserModel, const AnalyserEquationAstPtr &ast);

    bool isToBeComputedAgain(const AnalyserEquationPtr &analyserEquation);
    bool isSomeConstant(const AnalyserEquationPtr &analyserEquation,
                        bool includeComputedConstants) const;

    enum class GenerateEquationCodeTarget
    {
        NORMAL,
        OBJECTIVE_FUNCTION,
        COMPUTE_VARIABLES
    };

    std::string generateZeroInitialisationCode(const AnalyserModelPtr &analyserModel,
                                               const AnalyserVariablePtr &analyserVariable);
    std::string generateInitialisationCode(const AnalyserModelPtr &analyserModel,
                                           const AnalyserVariablePtr &analyserVariable, bool force = false);
    std::string generateEquationCode(const AnalyserModelPtr &analyserModel, const AnalyserEquationPtr &analyserEquation,
                                     std::vector<AnalyserEquationPtr> &remainingAnalyserEquations,
                                     std::vector<AnalyserEquationPtr> &analyserEquationsForDependencies,
                                     std::vector<AnalyserVariablePtr> &generatedConstantDependencies,
                                     bool includeComputedConstants,
                                     GenerateEquationCodeTarget target = GenerateEquationCodeTarget::NORMAL);
    std::string generateEquationCode(const AnalyserModelPtr &analyserModel, const AnalyserEquationPtr &analyserEquation,
                                     std::vector<AnalyserEquationPtr> &remainingAnalyserEquations,
                                     std::vector<AnalyserVariablePtr> &generatedConstantDependencies);
    bool hasComputedConstantDependency(const AnalyserModelPtr &analyserModel,
                                       const AnalyserVariablePtr &analyserVariable);
    std::string generateInitialiseVariableCode(const AnalyserModelPtr &analyserModel,
                                               const AnalyserVariablePtr &analyserVariable,
                                               std::vector<AnalyserEquationPtr> &remainingAnalyserEquations,
                                               std::vector<AnalyserVariablePtr> &remainingStates,
                                               std::vector<AnalyserVariablePtr> &remainingConstants,
                                               std::vector<AnalyserVariablePtr> &remainingComputedConstants,
                                               std::vector<AnalyserVariablePtr> &remainingAlgebraic,
                                               std::vector<AnalyserVariablePtr> *generatedConstantDependencies = nullptr);

    void addInterfaceComputeModelMethodsCode(const AnalyserModelPtr &analyserModel);
    void addImplementationInitialiseArraysMethodCode(const AnalyserModelPtr &analyserModel,
                                                     std::vector<AnalyserEquationPtr> &remainingEquations,
                                                     std::vector<AnalyserVariablePtr> &remainingStates,
                                                     std::vector<AnalyserVariablePtr> &remainingConstants,
                                                     std::vector<AnalyserVariablePtr> &remainingComputedConstants,
                                                     std::vector<AnalyserVariablePtr> &remainingAlgebraic);
    void addImplementationComputeComputedConstantsMethodCode(const AnalyserModelPtr &analyserModel,
                                                             std::vector<AnalyserEquationPtr> &remainingEquations,
                                                             std::vector<AnalyserVariablePtr> &remainingStates,
                                                             std::vector<AnalyserVariablePtr> &remainingConstants,
                                                             std::vector<AnalyserVariablePtr> &remainingComputedConstants,
                                                             std::vector<AnalyserVariablePtr> &remainingAlgebraic);
    void addImplementationComputeRatesMethodCode(const AnalyserModelPtr &analyserModel,
                                                 std::vector<AnalyserEquationPtr> &remainingEquations);
    void addImplementationComputeVariablesMethodCode(const AnalyserModelPtr &analyserModel,
                                                     std::vector<AnalyserEquationPtr> &remainingEquations);
};

} // namespace libcellml

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

    GeneratorProfilePtr mProfile = GeneratorProfile::create();

    std::map<AnalyserModelPtr, std::map<AnalyserVariablePtr, bool>> mTrackedVariables;

    void reset();

    bool doIsTrackedEquation(const AnalyserEquationPtr &equation, bool tracked);

    bool isTrackedEquation(const AnalyserEquationPtr &equation);
    bool isUntrackedEquation(const AnalyserEquationPtr &equation);

    bool doIsTrackedVariable(const AnalyserModelPtr &model, const AnalyserVariablePtr &variable, bool tracked);
    bool doIsTrackedVariable(const AnalyserVariablePtr &variable, bool tracked);

    bool isTrackedVariable(const AnalyserVariablePtr &variable);
    bool isUntrackedVariable(const AnalyserVariablePtr &variable);

    void addNeededToComputeExternalVariableIssue(const AnalyserVariablePtr &variable, bool tracked);

    bool trackableVariable(const AnalyserVariablePtr &variable, bool tracked, bool canAddIssue = true);
    bool specialVariable(const AnalyserVariablePtr &variable, const AnalyserVariablePtr &specialVariable, bool tracked,
                         Issue::ReferenceRule trackedReferenceRule, Issue::ReferenceRule untrackedReferenceRule);

    void doTrackVariable(const AnalyserVariablePtr &variable, bool tracked, bool needRemoveAllIssues = true);

    void trackVariable(const AnalyserVariablePtr &variable);
    void untrackVariable(const AnalyserVariablePtr &variable);

    void doTrackVariables(const std::vector<AnalyserVariablePtr> &variables, bool tracked);

    bool validModel(const AnalyserModelPtr &model);

    void trackAllConstants(const AnalyserModelPtr &model);
    void untrackAllConstants(const AnalyserModelPtr &model);

    void trackAllComputedConstants(const AnalyserModelPtr &model);
    void untrackAllComputedConstants(const AnalyserModelPtr &model);

    void trackAllAlgebraic(const AnalyserModelPtr &model);
    void untrackAllAlgebraic(const AnalyserModelPtr &model);

    void trackAllVariables(const AnalyserModelPtr &model);
    void untrackAllVariables(const AnalyserModelPtr &model);

    size_t doTrackedVariableCount(const AnalyserModelPtr &model, const std::vector<AnalyserVariablePtr> &variables,
                                  bool tracked);

    size_t trackedConstantCount(const AnalyserModelPtr &model);
    size_t untrackedConstantCount(const AnalyserModelPtr &model);

    size_t trackedComputedConstantCount(const AnalyserModelPtr &model);
    size_t untrackedComputedConstantCount(const AnalyserModelPtr &model);

    size_t trackedAlgebraicCount(const AnalyserModelPtr &model);
    size_t untrackedAlgebraicCount(const AnalyserModelPtr &model);

    size_t trackedVariableCount(const AnalyserModelPtr &model);
    size_t untrackedVariableCount(const AnalyserModelPtr &model);

    bool modelHasOdes(const AnalyserModelPtr &model) const;

    double scalingFactor(const AnalyserModelPtr &model, const VariablePtr &variable) const;

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
                                 const AnalyserVariablePtr &variable) const;

    bool modifiedProfile() const;

    std::string newLineIfNeeded();

    void addOriginCommentCode();

    void addInterfaceHeaderCode();
    void addImplementationHeaderCode();

    void addVersionAndLibcellmlVersionCode(bool interface = false);

    void addStateAndVariableCountCode(const AnalyserModelPtr &model, bool interface = false);

    std::string generateVariableInfoObjectCode(const AnalyserModelPtr &model, const std::string &objectString);

    void addVariableInfoObjectCode(const AnalyserModelPtr &model);

    std::string generateVariableInfoEntryCode(const std::string &name,
                                              const std::string &units,
                                              const std::string &component) const;

    void addInterfaceVariableInfoCode(const AnalyserModelPtr &model);

    void doAddImplementationVariableInfoCode(const std::string &variableInfoString,
                                             const std::vector<AnalyserVariablePtr> &variables, bool voiVariable);
    void addImplementationVariableInfoCode(const AnalyserModelPtr &model);

    void addArithmeticFunctionsCode(const AnalyserModelPtr &model);
    void addTrigonometricFunctionsCode(const AnalyserModelPtr &model);

    void addInterfaceCreateDeleteArrayMethodsCode(const AnalyserModelPtr &model);
    void addImplementationCreateDeleteArrayMethodsCode(const AnalyserModelPtr &model);

    void addExternalVariableMethodTypeDefinitionCode(const AnalyserModelPtr &model);

    void addRootFindingInfoObjectCode(const AnalyserModelPtr &model);
    void addExternNlaSolveMethodCode();
    void addNlaSystemsCode(const AnalyserModelPtr &model);

    std::string generateMethodBodyCode(const std::string &methodBody) const;

    std::string generateDoubleOrConstantVariableNameCode(const AnalyserModelPtr &model,
                                                         const VariablePtr &variable) const;
    std::string generateVariableNameCode(const AnalyserModelPtr &model, const VariablePtr &variable,
                                         bool state = true);

    std::string generateOperatorCode(const AnalyserModelPtr &model, const std::string &op,
                                     const AnalyserEquationAstPtr &ast);
    std::string generateMinusUnaryCode(const AnalyserModelPtr &model, const AnalyserEquationAstPtr &ast);
    std::string generateOneParameterFunctionCode(const AnalyserModelPtr &model, const std::string &function,
                                                 const AnalyserEquationAstPtr &ast);
    std::string generateTwoParameterFunctionCode(const AnalyserModelPtr &model, const std::string &function,
                                                 const AnalyserEquationAstPtr &ast);
    std::string generatePiecewiseIfCode(const std::string &condition,
                                        const std::string &value) const;
    std::string generatePiecewiseElseCode(const std::string &value) const;
    std::string generateCode(const AnalyserModelPtr &model, const AnalyserEquationAstPtr &ast);

    bool isToBeComputedAgain(const AnalyserEquationPtr &equation);
    bool isSomeConstant(const AnalyserEquationPtr &equation,
                        bool includeComputedConstants) const;

    std::string generateZeroInitialisationCode(const AnalyserModelPtr &model,
                                               const AnalyserVariablePtr &variable);
    std::string generateInitialisationCode(const AnalyserModelPtr &model, const AnalyserVariablePtr &variable,
                                           bool force = false);
    std::string generateEquationCode(const AnalyserModelPtr &model, const AnalyserEquationPtr &equation,
                                     std::vector<AnalyserEquationPtr> &remainingEquations,
                                     std::vector<AnalyserEquationPtr> &equationsForDependencies,
                                     std::vector<AnalyserVariablePtr> &generatedConstantDependencies,
                                     bool includeComputedConstants, bool forNlaSystem = false);
    std::string generateEquationCode(const AnalyserModelPtr &model, const AnalyserEquationPtr &equation,
                                     std::vector<AnalyserEquationPtr> &remainingEquations,
                                     std::vector<AnalyserVariablePtr> &generatedConstantDependencies);

    void addInterfaceComputeModelMethodsCode(const AnalyserModelPtr &model);
    std::string generateConstantInitialisationCode(const AnalyserModelPtr &model,
                                                   const std::vector<AnalyserVariablePtr>::iterator constant,
                                                   std::vector<AnalyserVariablePtr> &remainingConstants);
    void addImplementationInitialiseVariablesMethodCode(const AnalyserModelPtr &model,
                                                        std::vector<AnalyserEquationPtr> &remainingEquations);
    void addImplementationComputeComputedConstantsMethodCode(const AnalyserModelPtr &model,
                                                             std::vector<AnalyserEquationPtr> &remainingEquations);
    void addImplementationComputeRatesMethodCode(const AnalyserModelPtr &model,
                                                 std::vector<AnalyserEquationPtr> &remainingEquations);
    void addImplementationComputeVariablesMethodCode(const AnalyserModelPtr &model,
                                                     std::vector<AnalyserEquationPtr> &remainingEquations);
};

} // namespace libcellml

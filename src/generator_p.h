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

#include "utilities.h"

namespace libcellml {

std::string generateDoubleCode(const std::string &value);

/**
 * @brief The Generator::GeneratorImpl struct.
 *
 * The private implementation for the Generator class.
 */
struct Generator::GeneratorImpl
{
    std::string mCode;

    GeneratorProfilePtr mProfile = GeneratorProfile::create();

    std::map<ModelPtr, std::map<VariablePtr, bool>> mTrackedVariables;

    void reset();

    bool doTrackVariable(const ModelPtr &model, const VariablePtr &variable, bool tracked);
    bool doTrackVariable(const AnalyserModelPtr &model, const VariablePtr &variable, bool tracked);

    bool trackVariable(const AnalyserModelPtr &model, const VariablePtr &variable);
    bool untrackVariable(const AnalyserModelPtr &model, const VariablePtr &variable);

    bool doTrackAllVariables(const AnalyserModelPtr &model, bool tracked);

    bool trackAllVariables(const AnalyserModelPtr &model);
    bool untrackAllVariables(const AnalyserModelPtr &model);

    size_t doTrackedVariableCount(const AnalyserModelPtr &model, bool tracked);

    size_t trackedVariableCount(const AnalyserModelPtr &model);
    size_t untrackedVariableCount(const AnalyserModelPtr &model);

    bool modelHasOdes(const AnalyserModelPtr &model) const;
    bool modelHasNlas(const AnalyserModelPtr &model) const;

    AnalyserVariablePtr analyserVariable(const AnalyserModelPtr &model, const VariablePtr &variable) const;

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

    std::string generateVariableInfoObjectCode(const AnalyserModelPtr &model, const std::string &objectString) const;

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
    void addExternNlaSolveMethodCode(const AnalyserModelPtr &model);
    void addNlaSystemsCode(const AnalyserModelPtr &model);

    std::string generateMethodBodyCode(const std::string &methodBody) const;

    std::string generateDoubleOrConstantVariableNameCode(const AnalyserModelPtr &model,
                                                         const VariablePtr &variable) const;
    std::string generateVariableNameCode(const AnalyserModelPtr &model, const VariablePtr &variable,
                                         bool state = true) const;

    std::string generateOperatorCode(const AnalyserModelPtr &model, const std::string &op,
                                     const AnalyserEquationAstPtr &ast) const;
    std::string generateMinusUnaryCode(const AnalyserModelPtr &model, const AnalyserEquationAstPtr &ast) const;
    std::string generateOneParameterFunctionCode(const AnalyserModelPtr &model, const std::string &function,
                                                 const AnalyserEquationAstPtr &ast) const;
    std::string generateTwoParameterFunctionCode(const AnalyserModelPtr &model, const std::string &function,
                                                 const AnalyserEquationAstPtr &ast) const;
    std::string generatePiecewiseIfCode(const std::string &condition,
                                        const std::string &value) const;
    std::string generatePiecewiseElseCode(const std::string &value) const;
    std::string generateCode(const AnalyserModelPtr &model, const AnalyserEquationAstPtr &ast) const;

    bool isToBeComputedAgain(const AnalyserEquationPtr &equation) const;
    bool isSomeConstant(const AnalyserEquationPtr &equation,
                        bool includeComputedConstants) const;

    std::string generateZeroInitialisationCode(const AnalyserModelPtr &model,
                                               const AnalyserVariablePtr &variable) const;
    std::string generateInitialisationCode(const AnalyserModelPtr &model, const AnalyserVariablePtr &variable) const;
    std::string generateEquationCode(const AnalyserModelPtr &model, const AnalyserEquationPtr &equation,
                                     std::vector<AnalyserEquationPtr> &remainingEquations,
                                     std::vector<AnalyserEquationPtr> &equationsForDependencies,
                                     bool includeComputedConstants);
    std::string generateEquationCode(const AnalyserModelPtr &model, const AnalyserEquationPtr &equation,
                                     std::vector<AnalyserEquationPtr> &remainingEquations);

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

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
    AnalyserModelPtr mModel;

    std::string mCode;

    GeneratorProfilePtr mProfile = GeneratorProfile::create();

    void reset();

    bool modelHasOdes() const;
    bool modelHasNlas() const;

    AnalyserVariablePtr analyserVariable(const VariablePtr &variable) const;

    double scalingFactor(const VariablePtr &variable) const;

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

    void addStateAndVariableCountCode(bool interface = false);

    std::string generateVariableInfoObjectCode(const std::string &objectString) const;

    void addVariableInfoObjectCode();

    std::string generateVariableInfoEntryCode(const std::string &name,
                                              const std::string &units,
                                              const std::string &component) const;

    void addInterfaceVariableInfoCode();

    void addImplementationVariableInfoCode(const std::string &variableInfoString,
                                           const std::vector<AnalyserVariablePtr> &variables, bool voiVariable);
    void addImplementationVariableInfoCode();

    void addArithmeticFunctionsCode();
    void addTrigonometricFunctionsCode();

    void addInterfaceCreateDeleteArrayMethodsCode();
    void addImplementationCreateDeleteArrayMethodsCode();

    void addExternalVariableMethodTypeDefinitionCode();

    void addRootFindingInfoObjectCode();
    void addExternNlaSolveMethodCode();
    void addNlaSystemsCode();

    std::string generateMethodBodyCode(const std::string &methodBody) const;

    std::string generateDoubleOrConstantVariableNameCode(const VariablePtr &variable) const;
    std::string generateVariableNameCode(const VariablePtr &variable,
                                         bool state = true) const;

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

    bool isToBeComputedAgain(const AnalyserEquationPtr &equation) const;
    bool isSomeConstant(const AnalyserEquationPtr &equation,
                        bool includeComputedConstants) const;

    std::string generateZeroInitialisationCode(const AnalyserVariablePtr &variable) const;
    std::string generateInitialisationCode(const AnalyserVariablePtr &variable) const;
    std::string generateEquationCode(const AnalyserEquationPtr &equation,
                                     std::vector<AnalyserEquationPtr> &remainingEquations,
                                     std::vector<AnalyserEquationPtr> &equationsForDependencies,
                                     bool includeComputedConstants);
    std::string generateEquationCode(const AnalyserEquationPtr &equation,
                                     std::vector<AnalyserEquationPtr> &remainingEquations);

    void addInterfaceComputeModelMethodsCode();
    std::string generateConstantInitialisationCode(const std::vector<AnalyserVariablePtr>::iterator constant,
                                                   std::vector<AnalyserVariablePtr> &remainingConstants);
    void addImplementationInitialiseVariablesMethodCode(std::vector<AnalyserEquationPtr> &remainingEquations);
    void addImplementationComputeComputedConstantsMethodCode(std::vector<AnalyserEquationPtr> &remainingEquations);
    void addImplementationComputeRatesMethodCode(std::vector<AnalyserEquationPtr> &remainingEquations);
    void addImplementationComputeVariablesMethodCode(std::vector<AnalyserEquationPtr> &remainingEquations);
};

} // namespace libcellml

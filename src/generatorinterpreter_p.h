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

#include "generatorinterpreter.h"

#include "libcellml/generatorprofile.h"

namespace libcellml {

bool modelHasOdes(const AnalyserModelPtr &model);
bool modelHasNlas(const AnalyserModelPtr &model);

AnalyserVariablePtr analyserVariable(const AnalyserModelPtr &model, const VariablePtr &variable);

std::string newLineIfNotEmpty(const std::string &code);

std::string generateDoubleCode(const std::string &value);

/**
 * @brief The GeneratorInterpreter::GeneratorInterpreterImpl struct.
 *
 * The private implementation for the GeneratorInterpreter class.
 */
struct GeneratorInterpreter::GeneratorInterpreterImpl
{
    AnalyserModelPtr mModel;
    bool mModelHasOdes = false;
    bool mModelHasNlas = false;

    GeneratorProfilePtr mProfile = GeneratorProfile::create();
    std::string mCode;

    InterpreterStatementPtrs mStatements;
    InterpreterStatementPtrs mInitialiseVariablesStatements;
    InterpreterStatementPtrs mComputeComputedConstantsStatements;
    InterpreterStatementPtrs mComputeRatesStatements;
    InterpreterStatementPtrs mComputeVariablesStatements;

    explicit GeneratorInterpreterImpl(const AnalyserModelPtr &model, const GeneratorProfilePtr &profile,
                                      const std::string &code);
    explicit GeneratorInterpreterImpl(const AnalyserModelPtr &model);
    explicit GeneratorInterpreterImpl(const AnalyserEquationAstPtr &ast, const GeneratorProfilePtr &profile);

    void initialise(const AnalyserModelPtr &model, const GeneratorProfilePtr &profile, const std::string &code);

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

    std::string generateMethodBodyCode(const std::string &methodBody) const;

    std::string generateVariableNameCode(const VariablePtr &variable,
                                         bool rate = false) const;

    std::string generateOperatorCode(const std::string &op,
                                     const AnalyserEquationAstPtr &ast,
                                     const InterpreterStatementPtr &statement = nullptr) const;
    std::string generateMinusUnaryCode(const AnalyserEquationAstPtr &ast,
                                       const InterpreterStatementPtr &statement) const;
    std::string generateOneParameterFunctionCode(const std::string &function,
                                                 const AnalyserEquationAstPtr &ast,
                                                 const InterpreterStatementPtr &statement = nullptr) const;
    std::string generateTwoParameterFunctionCode(const std::string &function,
                                                 const AnalyserEquationAstPtr &ast,
                                                 const InterpreterStatementPtr &statement = nullptr) const;
    std::string generatePiecewiseIfCode(const std::string &condition,
                                        const std::string &value) const;
    std::string generatePiecewiseElseCode(const std::string &value) const;
    std::tuple<std::string, InterpreterStatementPtr> generateCode(const AnalyserEquationAstPtr &ast) const;

    bool isToBeComputedAgain(const AnalyserEquationPtr &equation) const;
    bool isSomeConstant(const AnalyserEquationPtr &equation,
                        bool includeComputedConstants) const;

    std::string generateZeroInitialisationCode(const AnalyserVariablePtr &variable);
    std::string generateInitialisationCode(const AnalyserVariablePtr &variable);
    std::string generateEquationCode(const AnalyserEquationPtr &equation,
                                     std::vector<AnalyserEquationPtr> &remainingEquations,
                                     std::vector<AnalyserEquationPtr> &equationsForDependencies,
                                     bool includeComputedConstants);
    std::string generateEquationCode(const AnalyserEquationPtr &equation,
                                     std::vector<AnalyserEquationPtr> &remainingEquations);

    void nlaSystems();
    void initialiseVariables(std::vector<AnalyserEquationPtr> &remainingEquations);
    void computeComputedConstants(std::vector<AnalyserEquationPtr> &remainingEquations);
    void computeRates(std::vector<AnalyserEquationPtr> &remainingEquations);
    void computeVariables(std::vector<AnalyserEquationPtr> &remainingEquations);
};

} // namespace libcellml

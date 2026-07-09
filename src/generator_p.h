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

    AnalyserModelPtr mAnalyserModel;
    GeneratorProfilePtr mDefaultProfile = GeneratorProfile::create();
    GeneratorProfilePtr mProfile;
    GeneratorVariableTrackerPtr mVariableTracker;

    /**
     * @brief Cached profile accessors to avoid virtual dispatch overhead.
     *
     * Populated by initProfileCache() at the start of each code generation run.
     */
    struct ProfileCache
    {
        // Boolean operator flags.

        bool hasEqOperator = false;
        bool hasNeqOperator = false;
        bool hasLtOperator = false;
        bool hasLeqOperator = false;
        bool hasGtOperator = false;
        bool hasGeqOperator = false;
        bool hasAndOperator = false;
        bool hasOrOperator = false;
        bool hasXorOperator = false;
        bool hasNotOperator = false;
        bool hasPowerOperator = false;
        bool hasConditionalOperator = false;

        // Hot-path strings.

        std::string equalityString;
        std::string eqString;
        std::string neqString;
        std::string ltString;
        std::string leqString;
        std::string gtString;
        std::string geqString;
        std::string andString;
        std::string orString;
        std::string xorString;
        std::string notString;
        std::string plusString;
        std::string minusString;
        std::string timesString;
        std::string divideString;
        std::string powerString;
        std::string squareRootString;
        std::string squareString;
        std::string absoluteValueString;
        std::string exponentialString;
        std::string naturalLogarithmString;
        std::string commonLogarithmString;
        std::string ceilingString;
        std::string floorString;
        std::string minString;
        std::string maxString;
        std::string remString;
        std::string sinString;
        std::string cosString;
        std::string tanString;
        std::string secString;
        std::string cscString;
        std::string cotString;
        std::string sinhString;
        std::string coshString;
        std::string tanhString;
        std::string sechString;
        std::string cschString;
        std::string cothString;
        std::string asinString;
        std::string acosString;
        std::string atanString;
        std::string asecString;
        std::string acscString;
        std::string acotString;
        std::string asinhString;
        std::string acoshString;
        std::string atanhString;
        std::string asechString;
        std::string acschString;
        std::string acothString;
        std::string trueString;
        std::string falseString;
        std::string eString;
        std::string piString;
        std::string infString;
        std::string nanString;
        std::string indentString;
        std::string openArrayString;
        std::string closeArrayString;
        std::string commandSeparatorString;
        std::string arrayElementSeparatorString;
        std::string variableDeclarationString;
        std::string statesArrayString;
        std::string ratesArrayString;
        std::string constantsArrayString;
        std::string computedConstantsArrayString;
        std::string algebraicVariablesArrayString;
        std::string externalVariablesArrayString;
        std::string voiString;
        std::string uArrayString;
        std::string fArrayString;
        std::string conditionalOperatorIfString;
        std::string conditionalOperatorElseString;
        std::string piecewiseIfString;
        std::string piecewiseElseString;
    } mutable mProfileCache;

    void initProfileCache();

    void reset();

    std::string analyserVariableIndexString(const AnalyserVariablePtr &analyserVariable);

    bool isTrackedEquation(const AnalyserEquationPtr &analyserEquation, bool tracked);
    bool isTrackedVariable(const AnalyserVariablePtr &analyserVariable, bool tracked);

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

    void addCode(const std::string &code);

    void addOriginCommentCode();

    void addInterfaceHeaderCode();
    void addImplementationHeaderCode();

    void addVersionAndLibcellmlVersionCode(bool interface = false);

    void addStateAndVariableCountCode(bool interface = false);

    std::string generateVariableInfoObjectCode(const std::string &objectString);

    void addVariableInfoObjectCode();

    std::string generateVariableInfoEntryCode(const std::string &name,
                                              const std::string &units,
                                              const std::string &component) const;

    void addInterfaceVariableInfoCode();

    void addImplementationVariableInfoCode(const std::string &variableInfoString,
                                           const std::vector<AnalyserVariablePtr> &analyserVariables, bool voiVariable);
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

    std::string generateDoubleOrVariableNameCode(const VariablePtr &variable);
    std::string generateVariableNameCode(const VariablePtr &variable, bool state = true);

    std::string generateOperatorCode(const std::string &op, const AnalyserEquationAstPtr &ast);
    std::string generateMinusUnaryCode(const AnalyserEquationAstPtr &ast);
    std::string generateOneParameterFunctionCode(const std::string &function, const AnalyserEquationAstPtr &ast);
    std::string generateTwoParameterFunctionCode(const std::string &function, const AnalyserEquationAstPtr &ast);
    std::string generatePiecewiseIfCode(const std::string &condition, const std::string &value) const;
    std::string generatePiecewiseElseCode(const std::string &value) const;
    std::string generateCode(const AnalyserEquationAstPtr &ast);

    bool isToBeComputedAgain(const AnalyserEquationPtr &analyserEquation);
    bool isSomeConstant(const AnalyserEquationPtr &analyserEquation,
                        bool includeComputedConstants) const;

    enum class GenerateEquationCodeTarget
    {
        NORMAL,
        OBJECTIVE_FUNCTION,
        COMPUTE_VARIABLES
    };

    std::string generateZeroInitialisationCode(const AnalyserVariablePtr &analyserVariable);
    std::string generateInitialisationCode(const AnalyserVariablePtr &analyserVariable, bool force = false);
    std::string generateEquationCode(const AnalyserEquationPtr &analyserEquation,
                                     std::unordered_set<AnalyserEquationPtr> &remainingAnalyserEquations,
                                     std::unordered_set<AnalyserEquationPtr> &analyserEquationsForDependencies,
                                     std::unordered_set<AnalyserVariablePtr> &generatedConstantDependencies,
                                     bool includeComputedConstants,
                                     GenerateEquationCodeTarget target = GenerateEquationCodeTarget::NORMAL);
    std::string generateEquationCode(const AnalyserEquationPtr &analyserEquation,
                                     std::unordered_set<AnalyserEquationPtr> &remainingAnalyserEquations,
                                     std::unordered_set<AnalyserVariablePtr> &generatedConstantDependencies);
    bool hasComputedConstantDependency(const AnalyserVariablePtr &analyserVariable);
    std::string generateInitialiseVariableCode(const AnalyserVariablePtr &analyserVariable,
                                               std::unordered_set<AnalyserEquationPtr> &remainingAnalyserEquations,
                                               std::vector<AnalyserVariablePtr> &remainingStates,
                                               std::vector<AnalyserVariablePtr> &remainingConstants,
                                               std::vector<AnalyserVariablePtr> &remainingComputedConstants,
                                               std::vector<AnalyserVariablePtr> &remainingAlgebraicVariables,
                                               std::unordered_set<AnalyserVariablePtr> *generatedConstantDependencies = nullptr);

    void addInterfaceComputeModelMethodsCode();
    void addImplementationInitialiseArraysMethodCode(std::unordered_set<AnalyserEquationPtr> &remainingAnalyserEquations,
                                                     std::vector<AnalyserVariablePtr> &remainingStates,
                                                     std::vector<AnalyserVariablePtr> &remainingConstants,
                                                     std::vector<AnalyserVariablePtr> &remainingComputedConstants,
                                                     std::vector<AnalyserVariablePtr> &remainingAlgebraicVariables);
    void addImplementationComputeComputedConstantsMethodCode(std::unordered_set<AnalyserEquationPtr> &remainingAnalyserEquations,
                                                             std::vector<AnalyserVariablePtr> &remainingStates,
                                                             std::vector<AnalyserVariablePtr> &remainingConstants,
                                                             std::vector<AnalyserVariablePtr> &remainingComputedConstants,
                                                             std::vector<AnalyserVariablePtr> &remainingAlgebraicVariables);
    void addImplementationComputeRatesMethodCode(std::unordered_set<AnalyserEquationPtr> &remainingAnalyserEquations);
    void addImplementationComputeVariablesMethodCode(std::unordered_set<AnalyserEquationPtr> &remainingAnalyserEquations);
};

} // namespace libcellml

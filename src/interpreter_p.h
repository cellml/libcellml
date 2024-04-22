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

#include "libcellml/interpreter.h"

#include "internaltypes.h"

namespace libcellml {

struct InterpreterStackElement
{
    enum class Type
    {
        NUMBER,
        STATE,
        RATE,
        VARIABLE
    };

    Type mType = Type::NUMBER;
    double mValue = std::numeric_limits<double>::quiet_NaN();
    size_t mIndex = 0;

    explicit InterpreterStackElement(double value);
    explicit InterpreterStackElement(Type type, size_t index);
};

/**
 * @brief The Interpreter::InterpreterImpl struct.
 *
 * The private implementation for the Interpreter class.
 */
struct Interpreter::InterpreterImpl
{
    AnalyserModelPtr mModel;

    std::vector<InterpreterAstStatementPtr> mInitialiseVariablesAstStatements;
    std::vector<InterpreterAstStatementPtr> mComputeComputedConstantsAstStatements;
    std::vector<InterpreterAstStatementPtr> mComputeRatesAstStatements;
    std::vector<InterpreterAstStatementPtr> mComputeVariablesAstStatements;

    std::vector<InterpreterRpnStatementPtr> mInitialiseVariablesRpnStatements;
    std::vector<InterpreterRpnStatementPtr> mComputeComputedConstantsRpnStatements;
    std::vector<InterpreterRpnStatementPtr> mComputeRatesRpnStatements;
    std::vector<InterpreterRpnStatementPtr> mComputeVariablesRpnStatements;

    double mVoi = 0.0;
    std::vector<double> mStates;
    std::vector<double> mRates;
    std::vector<double> mVariables;
    double *mStatesData = nullptr;
    double *mRatesData = nullptr;
    double *mVariablesData = nullptr;

    void setModel(const AnalyserModelPtr &model);
};

} // namespace libcellml

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

/**
 * @brief The Interpreter::InterpreterImpl struct.
 *
 * The private implementation for the Interpreter class.
 */
struct Interpreter::InterpreterImpl
{
    AnalyserModelPtr mModel;

    std::vector<InterpreterStatementPtr> mInitialiseVariablesStatements;
    std::vector<InterpreterStatementPtr> mComputeComputedConstantsStatements;
    std::vector<InterpreterStatementPtr> mComputeRatesStatements;
    std::vector<InterpreterStatementPtr> mComputeVariablesStatements;

    double mVoi = 0.0;
    double *mStates;
    double *mRates;
    double *mVariables;
    double *mStatesData = nullptr;
    double *mRatesData = nullptr;
    double *mVariablesData = nullptr;

    void setModel(const AnalyserModelPtr &model);
};

} // namespace libcellml

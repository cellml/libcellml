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

#include "libcellml/analyservariable.h"

namespace libcellml {

/**
 * @brief The InterpreterRpnStatement::InterpreterRpnStatementImpl struct.
 *
 * The private implementation for the InterpreterRpnStatement class.
 */
struct InterpreterRpnStatement::InterpreterRpnStatementImpl
{
    InterpreterRpnStatement::Type mType = Type::EQUALITY;
    AnalyserVariablePtr mVariable;
    size_t mIndex = 0;
    double mValue = std::numeric_limits<double>::quiet_NaN();
    size_t mExternalIndex = 0;

    explicit InterpreterRpnStatementImpl(Type type);
    explicit InterpreterRpnStatementImpl(const AnalyserVariablePtr &variable, bool rate);
    explicit InterpreterRpnStatementImpl(double value);
    explicit InterpreterRpnStatementImpl(size_t index);

    double stackTopValue(double *states, double *rates, double *variables,
                         std::stack<InterpreterStackElement> &stack) const;

    void evaluate(double voi, double *states, double *rates, double *variables,
                  std::stack<InterpreterStackElement> &stack) const;
};

} // namespace libcellml

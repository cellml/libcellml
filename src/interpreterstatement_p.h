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
 * @brief The InterpreterStatement::InterpreterStatementImpl struct.
 *
 * The private implementation for the InterpreterStatement class.
 */
struct InterpreterStatement::InterpreterStatementImpl
{
    InterpreterStatement::Type mType = Type::EQUALITY;
    InterpreterStatementPtr mLeftChild;
    InterpreterStatementPtr mRightChild;
    AnalyserVariablePtr mVariable;
    bool mState = true;
    double mValue = std::numeric_limits<double>::quiet_NaN();
    size_t mIndex = 0;

    explicit InterpreterStatementImpl(Type type,
                                      const InterpreterStatementPtr &leftChild,
                                      const InterpreterStatementPtr &rightChild);
    explicit InterpreterStatementImpl(const AnalyserVariablePtr &variable, bool state);
    explicit InterpreterStatementImpl(double value);
    explicit InterpreterStatementImpl(size_t index);

    void evaluate(double *states, double *rates, double *variables) const;
    double evaluateToDouble(double *states, double *rates, double *variables) const;
};

} // namespace libcellml

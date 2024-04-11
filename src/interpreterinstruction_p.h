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
 * @brief The InterpreterInstruction::InterpreterInstructionImpl struct.
 *
 * The private implementation for the InterpreterInstruction class.
 */
struct InterpreterInstruction::InterpreterInstructionImpl
{
    InterpreterInstruction::Type mType = Type::EQUALITY;
    InterpreterInstructionPtr mLeftChild;
    InterpreterInstructionPtr mRightChild;
    AnalyserVariablePtr mVariable;
    double mValue = std::numeric_limits<double>::quiet_NaN();

    static InterpreterInstructionPtr createEquality(const AnalyserVariablePtr &variable, double value);

    explicit InterpreterInstructionImpl(Type type,
                                        const InterpreterInstructionPtr &leftChild,
                                        const InterpreterInstructionPtr &rightChild);
    explicit InterpreterInstructionImpl(const AnalyserVariablePtr &variable);
    explicit InterpreterInstructionImpl(double value);

    void evaluate(double *states, double *rates, double *variables) const;
    double evaluateToDouble(double *states, double *rates, double *variables) const;
};

} // namespace libcellml

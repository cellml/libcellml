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
#include "libcellml/variable.h"

#include "interpreterstatement.h"

#include <cassert>

#include "libcellml/interpreter.h"

#include "interpreterstatement_p.h"

#include "libcellml/undefines.h"

namespace libcellml {

InterpreterInstruction::InterpreterInstructionImpl::InterpreterInstructionImpl(Type type,
                                                                               const InterpreterInstructionPtr &leftChild,
                                                                               const InterpreterInstructionPtr &rightChild)
    : mType(type)
    , mLeftChild(leftChild)
    , mRightChild(rightChild)
{
}

InterpreterInstruction::InterpreterInstructionImpl::InterpreterInstructionImpl(const AnalyserVariablePtr &variable)
    : mType(Type::CI)
    , mVariable(variable)
{
}

InterpreterInstruction::InterpreterInstructionImpl::InterpreterInstructionImpl(double value)
    : mType(Type::CN)
    , mValue(value)
{
}

InterpreterInstructionPtr InterpreterInstruction::InterpreterInstructionImpl::createEquality(const AnalyserVariablePtr &variable, double value)
{
    auto leftChild = InterpreterInstructionPtr {new InterpreterInstruction {variable}};
    auto rightChild = InterpreterInstructionPtr {new InterpreterInstruction {value}};

    return InterpreterInstructionPtr {new InterpreterInstruction {Type::EQUALITY, leftChild, rightChild}};
}

void InterpreterInstruction::InterpreterInstructionImpl::evaluate(double *states, double *rates, double *variables) const
{
    if (mType == Type::EQUALITY) {
        auto rightChildValue = mRightChild->mPimpl->evaluateToDouble(states, rates, variables);

        if (mLeftChild->mPimpl->mVariable->type() == AnalyserVariable::Type::STATE) {
            states[mLeftChild->mPimpl->mVariable->index()] = rightChildValue;
        } else {
            variables[mLeftChild->mPimpl->mVariable->index()] = rightChildValue;
        }
    }
}

double InterpreterInstruction::InterpreterInstructionImpl::evaluateToDouble(double *states, double *rates, double *variables) const
{
    (void)states;
    (void)rates;
    (void)variables;

    switch (mType) {
    default: // Something else, but in fact it should be a CN element.
        assert(mType == Type::CN);

        return mValue;
    }
}

InterpreterInstruction::InterpreterInstruction(Type type,
                                               const InterpreterInstructionPtr &leftChild,
                                               const InterpreterInstructionPtr &rightChild)
    : mPimpl(new InterpreterInstructionImpl(type, leftChild, rightChild))
{
}

InterpreterInstruction::InterpreterInstruction(const AnalyserVariablePtr &variable)
    : mPimpl(new InterpreterInstructionImpl(variable))
{
}

InterpreterInstruction::InterpreterInstruction(double value)
    : mPimpl(new InterpreterInstructionImpl(value))
{
}

InterpreterInstruction::~InterpreterInstruction()
{
    delete mPimpl;
}

InterpreterInstructionPtr InterpreterInstruction::createEquality(const AnalyserVariablePtr &variable, double value) noexcept
{
    return InterpreterInstructionImpl::createEquality(variable, value);
}

void InterpreterInstruction::evaluate(double *states, double *rates, double *variables) const
{
    mPimpl->evaluate(states, rates, variables);
}

} // namespace libcellml

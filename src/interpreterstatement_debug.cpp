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

#include "interpreterstatement_p.h"

namespace libcellml {

InterpreterStatementPtr InterpreterStatement::leftChild() const
{
    return mPimpl->mLeftChild;
}

InterpreterStatementPtr InterpreterStatement::rightChild() const
{
    return mPimpl->mRightChild;
}

InterpreterStatement::Type InterpreterStatement::type() const
{
    return mPimpl->mType;
}

AnalyserVariablePtr InterpreterStatement::variable() const
{
    return mPimpl->mVariable;
}

bool InterpreterStatement::rate() const
{
    return mPimpl->mRate;
}

double InterpreterStatement::value() const
{
    return mPimpl->mValue;
}

size_t InterpreterStatement::index() const
{
    return mPimpl->mIndex;
}

} // namespace libcellml

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

#include "interpreteraststatement_p.h"

namespace libcellml {

InterpreterAstStatementPtr InterpreterAstStatement::leftChild() const
{
    return mPimpl->mLeftChild;
}

InterpreterAstStatementPtr InterpreterAstStatement::rightChild() const
{
    return mPimpl->mRightChild;
}

InterpreterAstStatement::Type InterpreterAstStatement::type() const
{
    return mPimpl->mType;
}

AnalyserVariablePtr InterpreterAstStatement::variable() const
{
    return mPimpl->mVariable;
}

double InterpreterAstStatement::value() const
{
    return mPimpl->mValue;
}

size_t InterpreterAstStatement::externalIndex() const
{
    return mPimpl->mExternalIndex;
}

} // namespace libcellml

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

#include "libcellml/analysermodel.h"

#include "analysermodel_p.h"

namespace libcellml {

AnalyserModel::AnalyserModel()
    : mPimpl(new AnalyserModelImpl())
{
}

AnalyserModel::~AnalyserModel()
{
    delete mPimpl;
}

bool AnalyserModel::isValid() const
{
    return (mPimpl->mType == AnalyserModel::Type::ALGEBRAIC)
           || (mPimpl->mType == AnalyserModel::Type::ODE);
}

AnalyserModel::Type AnalyserModel::type() const
{
    return mPimpl->mType;
}

size_t AnalyserModel::stateCount() const
{
    if (!isValid()) {
        return 0;
    }

    return mPimpl->mStates.size();
}

size_t AnalyserModel::variableCount() const
{
    if (!isValid()) {
        return 0;
    }

    return mPimpl->mVariables.size();
}

AnalyserVariablePtr AnalyserModel::voi() const
{
    if (!isValid()) {
        return {};
    }

    return mPimpl->mVoi;
}

AnalyserVariablePtr AnalyserModel::state(size_t index) const
{
    if (!isValid()
        || (index >= mPimpl->mStates.size())) {
        return {};
    }

    return mPimpl->mStates[index];
}

AnalyserVariablePtr AnalyserModel::variable(size_t index) const
{
    if (!isValid() || (index >= mPimpl->mVariables.size())) {
        return {};
    }

    return mPimpl->mVariables[index];
}

} // namespace libcellml

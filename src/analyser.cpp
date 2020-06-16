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

#include "libcellml/analyser.h"

namespace libcellml {

/**
 * @brief The Analyser::AnalyserImpl struct.
 *
 * The private implementation for the Analyser class.
 */
struct Analyser::AnalyserImpl
{
    Analyser::ModelType mModelType = Analyser::ModelType::UNKNOWN;

    AnalyserVariablePtr mVoi = nullptr;
    std::vector<AnalyserVariablePtr> mStates;
    std::vector<AnalyserVariablePtr> mVariables;

    void processModel(const ModelPtr &model);

    bool hasValidModel() const;
};

void Analyser::AnalyserImpl::processModel(const ModelPtr &model)
{
    (void)model;
}

bool Analyser::AnalyserImpl::hasValidModel() const
{
    return (mModelType == Analyser::ModelType::ALGEBRAIC)
           || (mModelType == Analyser::ModelType::ODE);
}

Analyser::Analyser()
    : mPimpl(new AnalyserImpl())
{
}

Analyser::~Analyser()
{
    delete mPimpl;
}

AnalyserPtr Analyser::create() noexcept
{
    return AnalyserPtr {new Analyser {}};
}

void Analyser::processModel(const ModelPtr &model)
{
    // Process the model.

    mPimpl->processModel(model);
}

Analyser::ModelType Analyser::modelType() const
{
    return mPimpl->mModelType;
}

size_t Analyser::stateCount() const
{
    if (!mPimpl->hasValidModel()) {
        return 0;
    }

    return mPimpl->mStates.size();
}

size_t Analyser::variableCount() const
{
    if (!mPimpl->hasValidModel()) {
        return 0;
    }

    return mPimpl->mVariables.size();
}

AnalyserVariablePtr Analyser::voi() const
{
    if (!mPimpl->hasValidModel()) {
        return {};
    }

    return mPimpl->mVoi;
}

AnalyserVariablePtr Analyser::state(size_t index) const
{
    if (!mPimpl->hasValidModel() || (index >= mPimpl->mStates.size())) {
        return {};
    }

    return mPimpl->mStates[index];
}

AnalyserVariablePtr Analyser::variable(size_t index) const
{
    if (!mPimpl->hasValidModel() || (index >= mPimpl->mVariables.size())) {
        return {};
    }

    return mPimpl->mVariables[index];
}

} // namespace libcellml

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
#include "utilities.h"

namespace libcellml {

AnalyserModelPtr AnalyserModel::AnalyserModelImpl::create()
{
    return std::shared_ptr<AnalyserModel> {new AnalyserModel {}};
}

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

bool AnalyserModel::hasExternalVariables() const
{
    if (!isValid()) {
        return false;
    }

    return mPimpl->mHasExternalVariables;
}

AnalyserVariablePtr AnalyserModel::voi() const
{
    if (!isValid()) {
        return {};
    }

    return mPimpl->mVoi;
}

size_t AnalyserModel::stateCount() const
{
    if (!isValid()) {
        return 0;
    }

    return mPimpl->mStates.size();
}

std::vector<AnalyserVariablePtr> AnalyserModel::states() const
{
    if (!isValid()) {
        return {};
    }

    return mPimpl->mStates;
}

AnalyserVariablePtr AnalyserModel::state(size_t index) const
{
    if (!isValid()
        || (index >= mPimpl->mStates.size())) {
        return {};
    }

    return mPimpl->mStates[index];
}

size_t AnalyserModel::variableCount() const
{
    if (!isValid()) {
        return 0;
    }

    return mPimpl->mVariables.size();
}

std::vector<AnalyserVariablePtr> AnalyserModel::variables() const
{
    if (!isValid()) {
        return {};
    }

    return mPimpl->mVariables;
}

AnalyserVariablePtr AnalyserModel::variable(size_t index) const
{
    if (!isValid() || (index >= mPimpl->mVariables.size())) {
        return {};
    }

    return mPimpl->mVariables[index];
}

size_t AnalyserModel::equationCount() const
{
    if (!isValid()) {
        return 0;
    }

    return mPimpl->mEquations.size();
}

std::vector<AnalyserEquationPtr> AnalyserModel::equations() const
{
    if (!isValid()) {
        return {};
    }

    return mPimpl->mEquations;
}

AnalyserEquationPtr AnalyserModel::equation(size_t index) const
{
    if (!isValid() || (index >= mPimpl->mEquations.size())) {
        return {};
    }

    return mPimpl->mEquations[index];
}

bool AnalyserModel::needEqFunction() const
{
    if (!isValid()) {
        return false;
    }

    return mPimpl->mNeedEqFunction;
}

bool AnalyserModel::needNeqFunction() const
{
    if (!isValid()) {
        return false;
    }

    return mPimpl->mNeedNeqFunction;
}

bool AnalyserModel::needLtFunction() const
{
    if (!isValid()) {
        return false;
    }

    return mPimpl->mNeedLtFunction;
}

bool AnalyserModel::needLeqFunction() const
{
    if (!isValid()) {
        return false;
    }

    return mPimpl->mNeedLeqFunction;
}

bool AnalyserModel::needGtFunction() const
{
    if (!isValid()) {
        return false;
    }

    return mPimpl->mNeedGtFunction;
}

bool AnalyserModel::needGeqFunction() const
{
    if (!isValid()) {
        return false;
    }

    return mPimpl->mNeedGeqFunction;
}

bool AnalyserModel::needAndFunction() const
{
    if (!isValid()) {
        return false;
    }

    return mPimpl->mNeedAndFunction;
}

bool AnalyserModel::needOrFunction() const
{
    if (!isValid()) {
        return false;
    }

    return mPimpl->mNeedOrFunction;
}

bool AnalyserModel::needXorFunction() const
{
    if (!isValid()) {
        return false;
    }

    return mPimpl->mNeedXorFunction;
}

bool AnalyserModel::needNotFunction() const
{
    if (!isValid()) {
        return false;
    }

    return mPimpl->mNeedNotFunction;
}

bool AnalyserModel::needMinFunction() const
{
    if (!isValid()) {
        return false;
    }

    return mPimpl->mNeedMinFunction;
}

bool AnalyserModel::needMaxFunction() const
{
    if (!isValid()) {
        return false;
    }

    return mPimpl->mNeedMaxFunction;
}

bool AnalyserModel::needSecFunction() const
{
    if (!isValid()) {
        return false;
    }

    return mPimpl->mNeedSecFunction;
}

bool AnalyserModel::needCscFunction() const
{
    if (!isValid()) {
        return false;
    }

    return mPimpl->mNeedCscFunction;
}

bool AnalyserModel::needCotFunction() const
{
    if (!isValid()) {
        return false;
    }

    return mPimpl->mNeedCotFunction;
}

bool AnalyserModel::needSechFunction() const
{
    if (!isValid()) {
        return false;
    }

    return mPimpl->mNeedSechFunction;
}

bool AnalyserModel::needCschFunction() const
{
    if (!isValid()) {
        return false;
    }

    return mPimpl->mNeedCschFunction;
}

bool AnalyserModel::needCothFunction() const
{
    if (!isValid()) {
        return false;
    }

    return mPimpl->mNeedCothFunction;
}

bool AnalyserModel::needAsecFunction() const
{
    if (!isValid()) {
        return false;
    }

    return mPimpl->mNeedAsecFunction;
}

bool AnalyserModel::needAcscFunction() const
{
    if (!isValid()) {
        return false;
    }

    return mPimpl->mNeedAcscFunction;
}

bool AnalyserModel::needAcotFunction() const
{
    if (!isValid()) {
        return false;
    }

    return mPimpl->mNeedAcotFunction;
}

bool AnalyserModel::needAsechFunction() const
{
    if (!isValid()) {
        return false;
    }

    return mPimpl->mNeedAsechFunction;
}

bool AnalyserModel::needAcschFunction() const
{
    if (!isValid()) {
        return false;
    }

    return mPimpl->mNeedAcschFunction;
}

bool AnalyserModel::needAcothFunction() const
{
    if (!isValid()) {
        return false;
    }

    return mPimpl->mNeedAcothFunction;
}

bool AnalyserModel::areEquivalentVariables(const VariablePtr &variable1,
                                           const VariablePtr &variable2)
{
    // This is a cached version of the areEquivalentVariables() utility. Indeed,
    // an AnalyserModel object refers to a static version of a model, which
    // means that we can safely cache the result of a call to that utility. In
    // turn, this means that we can speed up any feature (e.g., code generation)
    // that also relies on that utility. When it comes to the key for the cache,
    // we use the Cantor pairing function with the address of the two variables
    // as parameters, thus ensuring the uniqueness of the key (see
    // https://en.wikipedia.org/wiki/Pairing_function#Cantor_pairing_function).

    auto v1 = reinterpret_cast<uintptr_t>(variable1.get());
    auto v2 = reinterpret_cast<uintptr_t>(variable2.get());

    if (v2 < v1) {
        v1 += v2;
        v2 = v1 - v2;
        v1 = v1 - v2;
    }

    auto key = ((v1 + v2) * (v1 + v2 + 1) >> 1U) + v2;
    auto cacheKey = mPimpl->mCachedEquivalentVariables.find(key);

    if (cacheKey != mPimpl->mCachedEquivalentVariables.end()) {
        return cacheKey->second;
    }

    bool res = libcellml::areEquivalentVariables(variable1, variable2);

    mPimpl->mCachedEquivalentVariables.emplace(key, res);

    return res;
}

} // namespace libcellml

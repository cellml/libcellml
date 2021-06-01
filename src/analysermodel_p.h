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

#include "libcellml/analysermodel.h"

namespace libcellml {

/**
 * @brief The AnalyserModel::AnalyserModelImpl struct.
 *
 * The private implementation for the AnalyserModel class.
 */
struct AnalyserModel::AnalyserModelImpl
{
    AnalyserModel::Type mType = Type::UNKNOWN;

    bool mHasExternalVariables = false;

    AnalyserVariablePtr mVoi = nullptr;
    std::vector<AnalyserVariablePtr> mStates;
    std::vector<AnalyserVariablePtr> mVariables;
    std::vector<AnalyserEquationPtr> mEquations;

    bool mNeedEqFunction = false;
    bool mNeedNeqFunction = false;
    bool mNeedLtFunction = false;
    bool mNeedLeqFunction = false;
    bool mNeedGtFunction = false;
    bool mNeedGeqFunction = false;
    bool mNeedAndFunction = false;
    bool mNeedOrFunction = false;
    bool mNeedXorFunction = false;
    bool mNeedNotFunction = false;

    bool mNeedMinFunction = false;
    bool mNeedMaxFunction = false;

    bool mNeedSecFunction = false;
    bool mNeedCscFunction = false;
    bool mNeedCotFunction = false;
    bool mNeedSechFunction = false;
    bool mNeedCschFunction = false;
    bool mNeedCothFunction = false;
    bool mNeedAsecFunction = false;
    bool mNeedAcscFunction = false;
    bool mNeedAcotFunction = false;
    bool mNeedAsechFunction = false;
    bool mNeedAcschFunction = false;
    bool mNeedAcothFunction = false;

    std::map<uintptr_t, bool> mCachedEquivalentVariables;

    static AnalyserModelPtr create();
};

} // namespace libcellml

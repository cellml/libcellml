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

namespace libcellml {

/**
 * @brief The AnalyserModel::AnalyserModelImpl struct.
 *
 * The private implementation for the AnalyserModel class.
 */
struct AnalyserModel::AnalyserModelImpl
{
    AnalyserModel::Type mType = Type::UNKNOWN;

    AnalyserVariablePtr mVoi = nullptr;
    std::vector<AnalyserVariablePtr> mStates;
    std::vector<AnalyserVariablePtr> mVariables;
    std::vector<AnalyserEquationPtr> mEquations;

    bool mNeedEq = false;
    bool mNeedNeq = false;
    bool mNeedLt = false;
    bool mNeedLeq = false;
    bool mNeedGt = false;
    bool mNeedGeq = false;
    bool mNeedAnd = false;
    bool mNeedOr = false;
    bool mNeedXor = false;
    bool mNeedNot = false;

    bool mNeedMin = false;
    bool mNeedMax = false;

    bool mNeedSec = false;
    bool mNeedCsc = false;
    bool mNeedCot = false;
    bool mNeedSech = false;
    bool mNeedCsch = false;
    bool mNeedCoth = false;
    bool mNeedAsec = false;
    bool mNeedAcsc = false;
    bool mNeedAcot = false;
    bool mNeedAsech = false;
    bool mNeedAcsch = false;
    bool mNeedAcoth = false;
};

} // namespace libcellml

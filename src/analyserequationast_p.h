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

#include "libcellml/analyserequationast.h"

namespace libcellml {

using AnalyserEquationAstWeakPtr = std::weak_ptr<AnalyserEquationAst>; /**< Type definition for weak analyser equation AST pointer. */
using VariableWeakPtr = std::weak_ptr<Variable>; /**< Type definition for weak variable pointer. */

/**
 * @brief The AnalyserEquationAst::AnalyserEquationAstImpl struct.
 *
 * The private implementation for the AnalyserEquationAst class.
 */
struct AnalyserEquationAst::AnalyserEquationAstImpl
{
    AnalyserEquationAst::Type mType = Type::ASSIGNMENT;
    std::string mValue;
    VariableWeakPtr mVariable;
    AnalyserEquationAstWeakPtr mParent;
    AnalyserEquationAstPtr mOwnedLeftChild = nullptr;
    AnalyserEquationAstPtr mOwnedRightChild = nullptr;
    AnalyserEquationAstWeakPtr mLeftChild;
    AnalyserEquationAstWeakPtr mRightChild;

    void populate(AnalyserEquationAst::Type type,
                  const AnalyserEquationAstPtr &parent);
    void populate(AnalyserEquationAst::Type type, const std::string &value,
                  const AnalyserEquationAstPtr &parent);
    void populate(AnalyserEquationAst::Type type, const VariablePtr &variable,
                  const AnalyserEquationAstPtr &parent);
};

} // namespace libcellml

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

#include "libcellml/analyserexternalvariable.h"

namespace libcellml {

/**
 * @brief The AnalyserExternalVariable::AnalyserExternalVariableImpl struct.
 *
 * The private implementation for the AnalyserExternalVariable class.
 */
struct AnalyserExternalVariable::AnalyserExternalVariableImpl
{
    VariablePtr mVariable;

    explicit AnalyserExternalVariableImpl(const VariablePtr &variable);
};

AnalyserExternalVariable::AnalyserExternalVariableImpl::AnalyserExternalVariableImpl(const VariablePtr &variable)
    : mVariable(variable)
{
}

AnalyserExternalVariable::AnalyserExternalVariable(const VariablePtr &variable)
    : mPimpl(new AnalyserExternalVariableImpl(variable))
{
}

AnalyserExternalVariable::~AnalyserExternalVariable()
{
    delete mPimpl;
}

AnalyserExternalVariablePtr AnalyserExternalVariable::create(const VariablePtr &variable) noexcept
{
    return std::shared_ptr<AnalyserExternalVariable> {new AnalyserExternalVariable {variable}};
}

} // namespace libcellml

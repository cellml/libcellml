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

#include "libcellml/analyservariable.h"

#include "analyservariable_p.h"

namespace libcellml {

void AnalyserVariable::AnalyserVariableImpl::populate(const VariablePtr &initialisingVariable,
                                                      const VariablePtr &variable,
                                                      size_t index,
                                                      AnalyserVariable::Type type)
{
    mInitialisingVariable = initialisingVariable;
    mVariable = variable;
    mIndex = index;
    mType = type;
}

AnalyserVariable::AnalyserVariable()
    : mPimpl(new AnalyserVariableImpl())
{
}

AnalyserVariable::~AnalyserVariable()
{
    delete mPimpl;
}

AnalyserVariablePtr AnalyserVariable::create() noexcept
{
    return std::shared_ptr<AnalyserVariable> {new AnalyserVariable {}};
}

VariablePtr AnalyserVariable::initialisingVariable() const
{
    return mPimpl->mInitialisingVariable;
}

VariablePtr AnalyserVariable::variable() const
{
    return mPimpl->mVariable;
}

size_t AnalyserVariable::index() const
{
    return mPimpl->mIndex;
}

AnalyserVariable::Type AnalyserVariable::type() const
{
    return mPimpl->mType;
}

} // namespace libcellml

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

#include "generatorinterpreter.h"

#include "generatorinterpreter_p.h"

namespace libcellml {

GeneratorInterpreter::GeneratorInterpreterImpl::GeneratorInterpreterImpl(const AnalyserModelPtr &model,
                                                                         const GeneratorProfilePtr &profile)
    : mModel(model)
    , mProfile(profile)
{
}

GeneratorInterpreter::GeneratorInterpreter(const AnalyserModelPtr &model, const GeneratorProfilePtr &profile)
    : mPimpl(new GeneratorInterpreterImpl(model, profile))
{
}

GeneratorInterpreter::~GeneratorInterpreter()
{
    delete mPimpl;
}

GeneratorInterpreterPtr GeneratorInterpreter::create(const AnalyserModelPtr &model, const GeneratorProfilePtr &profile) noexcept
{
    return std::shared_ptr<GeneratorInterpreter> {new GeneratorInterpreter {model, profile}};
}

std::string GeneratorInterpreter::code() const
{
    return mPimpl->mCode;
}

} // namespace libcellml

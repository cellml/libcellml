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

#include "libcellml/generator.h"
#include "libcellml/model.h"

#include <vector>

namespace libcellml{

struct Generator::GeneratorImpl
{
    std::vector<std::string> mConstants;
    std::vector<std::string> mStates;
    std::vector<std::string> mRates;
    std::vector<std::string> mAlgebraic;

    std::string generateCode(const ModelPtr &model);
};

std::string Generator::GeneratorImpl::generateCode(const ModelPtr &model)
{
    (void) model;

    return "";
}

Generator::Generator()
    : mPimpl(new GeneratorImpl())
{
}

Generator::~Generator()
{
    delete mPimpl;
}

size_t Generator::constantCount() const
{
    return mPimpl->mConstants.size();
}

size_t Generator::stateCount() const
{
    return mPimpl->mStates.size();
}

size_t Generator::rateCount() const
{
    return mPimpl->mRates.size();
}

size_t Generator::algebraicCount() const
{
    return mPimpl->mAlgebraic.size();
}

std::string Generator::generateCode(const ModelPtr &model)
{
    return mPimpl->generateCode(model);
}

}

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

#include "libcellml/interpreter.h"

#include "libcellml/analysermodel.h"

#include "interpreter_p.h"

namespace libcellml {

void Interpreter::InterpreterImpl::setModel(const AnalyserModelPtr &model)
{
    mModel = model;

    mVoi = 0.0;

    if (mModel != nullptr) {
        static const auto NaN = std::numeric_limits<double>::quiet_NaN();

        mStates = std::vector<double>(mModel->stateCount(), NaN);
        mRates = std::vector<double>(mModel->stateCount(), NaN);
        mVariables = std::vector<double>(mModel->variableCount(), NaN);
    } else {
        mStates.clear();
        mRates.clear();
        mVariables.clear();
    }
}

Interpreter::Interpreter()
    : mPimpl(new InterpreterImpl())
{
}

Interpreter::~Interpreter()
{
    delete mPimpl;
}

InterpreterPtr Interpreter::create() noexcept
{
    return std::shared_ptr<Interpreter> {new Interpreter {}};
}

AnalyserModelPtr Interpreter::model()
{
    return mPimpl->mModel;
}

void Interpreter::setModel(const AnalyserModelPtr &model)
{
    mPimpl->setModel(model);
}

double Interpreter::voi()
{
    return mPimpl->mVoi;
}

std::vector<double> Interpreter::states()
{
    return mPimpl->mStates;
}

std::vector<double> Interpreter::rates()
{
    return mPimpl->mRates;
}

std::vector<double> Interpreter::variables()
{
    return mPimpl->mVariables;
}

void Interpreter::initialiseVariables()
{
}

void Interpreter::computeComputedConstants()
{
}

void Interpreter::computeRates()
{
}

void Interpreter::computeVariables()
{
}

} // namespace libcellml

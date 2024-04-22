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

#include "generatorinterpreter_p.h"
#include "interpreter_p.h"

#include "libcellml/undefines.h"

namespace libcellml {

InterpreterStackElement::InterpreterStackElement(double value)
    : mType(Type::NUMBER)
    , mValue(value)
{
}

InterpreterStackElement::InterpreterStackElement(Type type, size_t index)
    : mType(type)
    , mIndex(index)
{
}

void Interpreter::InterpreterImpl::setModel(const AnalyserModelPtr &model)
{
    mModel = model;

    mVoi = 0.0;

    if (mModel != nullptr) {
        static const auto NAN = std::numeric_limits<double>::quiet_NaN();

        mStates = std::vector<double>(mModel->stateCount(), NAN);
        mRates = std::vector<double>(mModel->stateCount(), NAN);
        mVariables = std::vector<double>(mModel->variableCount(), NAN);

        mStatesData = mStates.data();
        mRatesData = mRates.data();
        mVariablesData = mVariables.data();

        auto generatorInterpreter = GeneratorInterpreter::create(mModel);

        mInitialiseVariablesAstStatements = generatorInterpreter->initialiseVariablesAstStatements();
        mComputeComputedConstantsAstStatements = generatorInterpreter->computeComputedConstantsAstStatements();
        mComputeRatesAstStatements = generatorInterpreter->computeRatesAstStatements();
        mComputeVariablesAstStatements = generatorInterpreter->computeVariablesAstStatements();

        mInitialiseVariablesRpnStatements = generatorInterpreter->initialiseVariablesRpnStatements();
        mComputeComputedConstantsRpnStatements = generatorInterpreter->computeComputedConstantsRpnStatements();
        mComputeRatesRpnStatements = generatorInterpreter->computeRatesRpnStatements();
        mComputeVariablesRpnStatements = generatorInterpreter->computeVariablesRpnStatements();
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

std::vector<double> &Interpreter::states()
{
    return mPimpl->mStates;
}

std::vector<double> &Interpreter::rates()
{
    return mPimpl->mRates;
}

std::vector<double> &Interpreter::variables()
{
    return mPimpl->mVariables;
}

void Interpreter::initialiseAstVariables()
{
    for (const auto &statement : mPimpl->mInitialiseVariablesAstStatements) {
        statement->evaluate(0.0, mPimpl->mStatesData, mPimpl->mRatesData, mPimpl->mVariablesData);
    }
}

void Interpreter::computeAstComputedConstants()
{
    for (const auto &statement : mPimpl->mComputeComputedConstantsAstStatements) {
        statement->evaluate(0.0, mPimpl->mStatesData, mPimpl->mRatesData, mPimpl->mVariablesData);
    }
}

void Interpreter::computeAstRates(double voi)
{
    for (const auto &statement : mPimpl->mComputeRatesAstStatements) {
        statement->evaluate(voi, mPimpl->mStatesData, mPimpl->mRatesData, mPimpl->mVariablesData);
    }
}

void Interpreter::computeAstVariables(double voi)
{
    for (const auto &statement : mPimpl->mComputeVariablesAstStatements) {
        statement->evaluate(voi, mPimpl->mStatesData, mPimpl->mRatesData, mPimpl->mVariablesData);
    }
}

void Interpreter::initialiseRpnVariables()
{
    std::stack<InterpreterStackElement> stack;

    for (const auto &statement : mPimpl->mInitialiseVariablesRpnStatements) {
        statement->evaluate(0.0, mPimpl->mStatesData, mPimpl->mRatesData, mPimpl->mVariablesData, stack);
    }
}

void Interpreter::computeRpnComputedConstants()
{
    std::stack<InterpreterStackElement> stack;

    for (const auto &statement : mPimpl->mComputeComputedConstantsRpnStatements) {
        statement->evaluate(0.0, mPimpl->mStatesData, mPimpl->mRatesData, mPimpl->mVariablesData, stack);
    }
}

void Interpreter::computeRpnRates(double voi)
{
    std::stack<InterpreterStackElement> stack;

    for (const auto &statement : mPimpl->mComputeRatesRpnStatements) {
        statement->evaluate(voi, mPimpl->mStatesData, mPimpl->mRatesData, mPimpl->mVariablesData, stack);
    }
}

void Interpreter::computeRpnVariables(double voi)
{
    std::stack<InterpreterStackElement> stack;

    for (const auto &statement : mPimpl->mComputeVariablesRpnStatements) {
        statement->evaluate(voi, mPimpl->mStatesData, mPimpl->mRatesData, mPimpl->mVariablesData, stack);
    }
}

} // namespace libcellml

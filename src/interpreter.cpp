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

void Interpreter::InterpreterImpl::setModel(const AnalyserModelPtr &model)
{
    mModel = model;

    if (mModel != nullptr) {
        auto generatorInterpreter = GeneratorInterpreter::create(mModel);

        mInitialiseVariablesStatements = generatorInterpreter->initialiseVariablesStatements();
        mComputeComputedConstantsStatements = generatorInterpreter->computeComputedConstantsStatements();
        mComputeRatesStatements = generatorInterpreter->computeRatesStatements();
        mComputeVariablesStatements = generatorInterpreter->computeVariablesStatements();
    } else {
        mInitialiseVariablesStatements.clear();
        mComputeComputedConstantsStatements.clear();
        mComputeRatesStatements.clear();
        mComputeVariablesStatements.clear();
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

void Interpreter::initialiseVariablesForAlgebraicModel(double *constants, double *computedConstants, double *algebraic) const
{
    for (const auto &statement : mPimpl->mInitialiseVariablesStatements) {
        statement->evaluate(0.0, nullptr, nullptr, constants, computedConstants, algebraic);
    }
}

void Interpreter::initialiseVariablesForDifferentialModel(double *states, double *rates, double *constants, double *computedConstants, double *algebraic) const
{
    for (const auto &statement : mPimpl->mInitialiseVariablesStatements) {
        statement->evaluate(0.0, states, rates, constants, computedConstants, algebraic);
    }
}

void Interpreter::computeComputedConstants(double *constants, double *computedConstants) const
{
    for (const auto &statement : mPimpl->mComputeComputedConstantsStatements) {
        statement->evaluate(0.0, nullptr, nullptr, constants, computedConstants, nullptr);
    }
}

void Interpreter::computeRates(double voi, double *states, double *rates, double *constants, double *computedConstants, double *algebraic) const
{
    for (const auto &statement : mPimpl->mComputeRatesStatements) {
        statement->evaluate(voi, states, rates, constants, computedConstants, algebraic);
    }
}

void Interpreter::computeVariablesForAlgebraicModel(double *constants, double *computedConstants, double *algebraic) const
{
    for (const auto &statement : mPimpl->mComputeVariablesStatements) {
        statement->evaluate(0.0, nullptr, nullptr, constants, computedConstants, algebraic);
    }
}

void Interpreter::computeVariablesForDifferentialModel(double voi, double *states, double *rates, double *constants, double *computedConstants, double *algebraic) const
{
    for (const auto &statement : mPimpl->mComputeVariablesStatements) {
        statement->evaluate(voi, states, rates, constants, computedConstants, algebraic);
    }
}

} // namespace libcellml

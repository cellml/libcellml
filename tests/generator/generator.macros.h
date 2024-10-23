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

#include <limits>

static const auto NAN = std::numeric_limits<double>::quiet_NaN();

typedef struct
{
    char name[256];
    char units[256];
    char component[256];
} VariableInfo;

#define NLA_SOLVE_METHOD \
    void nlaSolve(void (*)(double *, double *, void *), double *, size_t, void *) \
    { \
    }

#define ALGEBRAIC_MODEL_EXTERNAL_VARIABLE_METHOD \
    double externalVariable(double *, double *, double *, double *, size_t) \
    { \
        return 1.23; \
    }

#define DIFFERENTIAL_MODEL_EXTERNAL_VARIABLE_METHOD \
    double externalVariable(double, double *, double *, double *, double *, double *, double *, size_t) \
    { \
        return 7.89; \
    }

#define TEST_ALGEBRAIC_MODEL(analyserModel, model) \
    auto interpreter = libcellml::Interpreter::create(); \
\
    interpreter->setModel(analyserModel); \
\
    auto *constants = new double[analyserModel->constantCount()]; \
    auto *computedConstants = new double[analyserModel->computedConstantCount()]; \
    auto *algebraic = new double[analyserModel->algebraicCount()]; \
\
    interpreter->initialiseVariables(constants, computedConstants, algebraic); \
    interpreter->computeComputedConstants(constants, computedConstants); \
    interpreter->computeVariables(constants, computedConstants, algebraic); \
\
    auto *expectedConstantsData = model::createConstantsArray(); \
    auto *expectedComputedConstantsData = model::createComputedConstantsArray(); \
    auto *expectedAlgebraicData = model::createAlgebraicArray(); \
\
    model::initialiseVariables(expectedConstantsData, expectedComputedConstantsData, expectedAlgebraicData); \
    model::computeComputedConstants(expectedConstantsData, expectedComputedConstantsData); \
    model::computeVariables(expectedConstantsData, expectedComputedConstantsData, expectedAlgebraicData); \
\
    std::vector<double> expectedConstants(expectedConstantsData, expectedConstantsData + model::CONSTANT_COUNT); \
    std::vector<double> expectedComputedConstants(expectedComputedConstantsData, expectedComputedConstantsData + model::COMPUTED_CONSTANT_COUNT); \
    std::vector<double> expectedAlgebraic(expectedAlgebraicData, expectedAlgebraicData + model::ALGEBRAIC_COUNT); \
\
    expectEqualValues(expectedConstants, constants, analyserModel->constantCount()); \
    expectEqualValues(expectedComputedConstants, computedConstants, analyserModel->computedConstantCount()); \
    expectEqualValues(expectedAlgebraic, algebraic, analyserModel->algebraicCount()); \
\
    delete[] expectedConstantsData; \
    delete[] expectedComputedConstantsData; \
    delete[] expectedAlgebraicData; \
\
    delete[] constants; \
    delete[] computedConstants; \
    delete[] algebraic;

#define TEST_ALGEBRAIC_MODEL_EXTERNAL(analyserModel, model) \
    auto interpreter = libcellml::Interpreter::create(); \
\
    interpreter->setModel(analyserModel); \
\
    auto *constants = new double[analyserModel->constantCount()]; \
    auto *computedConstants = new double[analyserModel->computedConstantCount()]; \
    auto *algebraic = new double[analyserModel->algebraicCount()]; \
    auto *externals = new double[analyserModel->externalCount()]; \
\
    interpreter->initialiseVariables(constants, computedConstants, algebraic); \
    interpreter->computeComputedConstants(constants, computedConstants); \
    interpreter->computeVariables(constants, computedConstants, algebraic, externals, model::externalVariable); \
\
    auto *expectedConstantsData = model::createConstantsArray(); \
    auto *expectedComputedConstantsData = model::createComputedConstantsArray(); \
    auto *expectedAlgebraicData = model::createAlgebraicArray(); \
    auto *expectedAlgebraicExternals = model::createExternalsArray(); \
\
    model::initialiseVariables(expectedConstantsData, expectedComputedConstantsData, expectedAlgebraicData); \
    model::computeComputedConstants(expectedConstantsData, expectedComputedConstantsData); \
    model::computeVariables(expectedConstantsData, expectedComputedConstantsData, expectedAlgebraicData, expectedAlgebraicExternals, model::externalVariable); \
\
    std::vector<double> expectedConstants(expectedConstantsData, expectedConstantsData + model::CONSTANT_COUNT); \
    std::vector<double> expectedComputedConstants(expectedComputedConstantsData, expectedComputedConstantsData + model::COMPUTED_CONSTANT_COUNT); \
    std::vector<double> expectedAlgebraic(expectedAlgebraicData, expectedAlgebraicData + model::ALGEBRAIC_COUNT); \
    std::vector<double> expectedExternals(expectedAlgebraicExternals, expectedAlgebraicExternals + model::EXTERNAL_COUNT); \
\
    expectEqualValues(expectedConstants, constants, analyserModel->constantCount()); \
    expectEqualValues(expectedComputedConstants, computedConstants, analyserModel->computedConstantCount()); \
    expectEqualValues(expectedAlgebraic, algebraic, analyserModel->algebraicCount()); \
    expectEqualValues(expectedExternals, externals, analyserModel->externalCount()); \
\
    delete[] expectedConstantsData; \
    delete[] expectedComputedConstantsData; \
    delete[] expectedAlgebraicData; \
    delete[] expectedAlgebraicExternals; \
\
    delete[] constants; \
    delete[] computedConstants; \
    delete[] algebraic; \
    delete[] externals;

#define TEST_DIFFERENTIAL_MODEL(analyserModel, model) \
    auto interpreter = libcellml::Interpreter::create(); \
\
    interpreter->setModel(analyserModel); \
\
    auto *states = new double[analyserModel->stateCount()]; \
    auto *rates = new double[analyserModel->stateCount()]; \
    auto *constants = new double[analyserModel->constantCount()]; \
    auto *computedConstants = new double[analyserModel->computedConstantCount()]; \
    auto *algebraic = new double[analyserModel->algebraicCount()]; \
\
    interpreter->initialiseVariables(states, rates, constants, computedConstants, algebraic); \
    interpreter->computeComputedConstants(constants, computedConstants); \
    interpreter->computeRates(0.0, states, rates, constants, computedConstants, algebraic); \
    interpreter->computeVariables(0.0, states, rates, constants, computedConstants, algebraic); \
\
    auto *expectedStatesData = model::createStatesArray(); \
    auto *expectedRatesData = model::createStatesArray(); \
    auto *expectedConstantsData = model::createConstantsArray(); \
    auto *expectedComputedConstantsData = model::createComputedConstantsArray(); \
    auto *expectedAlgebraicData = model::createAlgebraicArray(); \
\
    model::initialiseVariables(expectedStatesData, expectedRatesData, expectedConstantsData, expectedComputedConstantsData, expectedAlgebraicData); \
    model::computeComputedConstants(expectedConstantsData, expectedComputedConstantsData); \
    model::computeRates(0.0, expectedStatesData, expectedRatesData, expectedConstantsData, expectedComputedConstantsData, expectedAlgebraicData); \
    model::computeVariables(0.0, expectedStatesData, expectedRatesData, expectedConstantsData, expectedComputedConstantsData, expectedAlgebraicData); \
\
    std::vector<double> expectedStates(expectedStatesData, expectedStatesData + model::STATE_COUNT); \
    std::vector<double> expectedRates(expectedRatesData, expectedRatesData + model::STATE_COUNT); \
    std::vector<double> expectedConstants(expectedConstantsData, expectedConstantsData + model::CONSTANT_COUNT); \
    std::vector<double> expectedComputedConstants(expectedComputedConstantsData, expectedComputedConstantsData + model::COMPUTED_CONSTANT_COUNT); \
    std::vector<double> expectedAlgebraic(expectedAlgebraicData, expectedAlgebraicData + model::ALGEBRAIC_COUNT); \
\
    expectEqualValues(expectedStates, states, analyserModel->stateCount()); \
    expectEqualValues(expectedRates, rates, analyserModel->stateCount()); \
    expectEqualValues(expectedConstants, constants, analyserModel->constantCount()); \
    expectEqualValues(expectedComputedConstants, computedConstants, analyserModel->computedConstantCount()); \
    expectEqualValues(expectedAlgebraic, algebraic, analyserModel->algebraicCount()); \
\
    delete[] expectedStatesData; \
    delete[] expectedRatesData; \
    delete[] expectedConstantsData; \
    delete[] expectedComputedConstantsData; \
    delete[] expectedAlgebraicData; \
\
    delete[] states; \
    delete[] rates; \
    delete[] constants; \
    delete[] computedConstants; \
    delete[] algebraic;

#define TEST_DIFFERENTIAL_MODEL_EXTERNAL(analyserModel, model) \
    auto interpreter = libcellml::Interpreter::create(); \
\
    interpreter->setModel(analyserModel); \
\
    auto *states = new double[analyserModel->stateCount()]; \
    auto *rates = new double[analyserModel->stateCount()]; \
    auto *constants = new double[analyserModel->constantCount()]; \
    auto *computedConstants = new double[analyserModel->computedConstantCount()]; \
    auto *algebraic = new double[analyserModel->algebraicCount()]; \
    auto *externals = new double[analyserModel->externalCount()]; \
\
    interpreter->initialiseVariables(states, rates, constants, computedConstants, algebraic); \
    interpreter->computeComputedConstants(constants, computedConstants); \
    interpreter->computeRates(0.0, states, rates, constants, computedConstants, algebraic, externals, model::externalVariable); \
    interpreter->computeVariables(0.0, states, rates, constants, computedConstants, algebraic, externals, model::externalVariable); \
\
    auto *expectedStatesData = model::createStatesArray(); \
    auto *expectedRatesData = model::createStatesArray(); \
    auto *expectedConstantsData = model::createConstantsArray(); \
    auto *expectedComputedConstantsData = model::createComputedConstantsArray(); \
    auto *expectedAlgebraicData = model::createAlgebraicArray(); \
    auto *expectedAlgebraicExternals = model::createExternalsArray(); \
\
    model::initialiseVariables(expectedStatesData, expectedRatesData, expectedConstantsData, expectedComputedConstantsData, expectedAlgebraicData); \
    model::computeComputedConstants(expectedConstantsData, expectedComputedConstantsData); \
    model::computeRates(0.0, expectedStatesData, expectedRatesData, expectedConstantsData, expectedComputedConstantsData, expectedAlgebraicData, expectedAlgebraicExternals, model::externalVariable); \
    model::computeVariables(0.0, expectedStatesData, expectedRatesData, expectedConstantsData, expectedComputedConstantsData, expectedAlgebraicData, expectedAlgebraicExternals, model::externalVariable); \
\
    std::vector<double> expectedStates(expectedStatesData, expectedStatesData + model::STATE_COUNT); \
    std::vector<double> expectedRates(expectedRatesData, expectedRatesData + model::STATE_COUNT); \
    std::vector<double> expectedConstants(expectedConstantsData, expectedConstantsData + model::CONSTANT_COUNT); \
    std::vector<double> expectedComputedConstants(expectedComputedConstantsData, expectedComputedConstantsData + model::COMPUTED_CONSTANT_COUNT); \
    std::vector<double> expectedAlgebraic(expectedAlgebraicData, expectedAlgebraicData + model::ALGEBRAIC_COUNT); \
    std::vector<double> expectedExternals(expectedAlgebraicExternals, expectedAlgebraicExternals + model::EXTERNAL_COUNT); \
\
    expectEqualValues(expectedStates, states, analyserModel->stateCount()); \
    expectEqualValues(expectedRates, rates, analyserModel->stateCount()); \
    expectEqualValues(expectedConstants, constants, analyserModel->constantCount()); \
    expectEqualValues(expectedComputedConstants, computedConstants, analyserModel->computedConstantCount()); \
    expectEqualValues(expectedAlgebraic, algebraic, analyserModel->algebraicCount()); \
    expectEqualValues(expectedExternals, externals, analyserModel->externalCount()); \
\
    delete[] expectedStatesData; \
    delete[] expectedRatesData; \
    delete[] expectedConstantsData; \
    delete[] expectedComputedConstantsData; \
    delete[] expectedAlgebraicData; \
    delete[] expectedAlgebraicExternals; \
\
    delete[] states; \
    delete[] rates; \
    delete[] constants; \
    delete[] computedConstants; \
    delete[] algebraic; \
    delete[] externals;

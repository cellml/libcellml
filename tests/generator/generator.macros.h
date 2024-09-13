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

#define TEST_ALGEBRAIC_MODEL(analyserModel, model) \
    auto interpreter = libcellml::Interpreter::create(); \
\
    interpreter->setModel(analyserModel); \
\
    auto *constants = new double[analyserModel->constantCount()]; \
    auto *computedConstants = new double[analyserModel->computedConstantCount()]; \
    auto *algebraic = new double[analyserModel->algebraicCount()]; \
\
    interpreter->initialiseVariablesForAlgebraicModel(constants, computedConstants, algebraic); \
    interpreter->computeComputedConstants(constants, computedConstants); \
    interpreter->computeVariablesForAlgebraicModel(constants, computedConstants, algebraic); \
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
    interpreter->initialiseVariablesForDifferentialModel(states, rates, constants, computedConstants, algebraic); \
    interpreter->computeComputedConstants(constants, computedConstants); \
    interpreter->computeRates(0.0, states, rates, constants, computedConstants, algebraic); \
    interpreter->computeVariablesForDifferentialModel(0.0, states, rates, constants, computedConstants, algebraic); \
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

#define INITIALISE_INTERPRETED_ALGEBRAIC_MODEL(analyserModel) \
    double *expectedStatesData = nullptr; \
    double *expectedRatesData = nullptr; \
    double *expectedConstantsData = nullptr; \
    double *expectedComputedConstantsData = nullptr; \
    double *expectedAlgebraicData = nullptr; \
    double *states = nullptr; \
    double *rates = nullptr; \
    auto *constants = new double[analyserModel->constantCount()]; \
    auto *computedConstants = new double[analyserModel->computedConstantCount()]; \
    auto *algebraic = new double[analyserModel->algebraicCount()]; \
\
    (void)expectedStatesData; \
    (void)expectedRatesData; \
    (void)expectedConstantsData; \
    (void)expectedComputedConstantsData; \
    (void)expectedAlgebraicData; \
    interpreter->initialiseVariablesForAlgebraicModel(constants, computedConstants, algebraic); \
    interpreter->computeComputedConstants(constants, computedConstants); \
    interpreter->computeVariablesForAlgebraicModel(constants, computedConstants, algebraic);

#define INITIALISE_INTERPRETED_DIFFERENTIAL_MODEL(analyserModel) \
    double *expectedStatesData = nullptr; \
    double *expectedRatesData = nullptr; \
    double *expectedConstantsData = nullptr; \
    double *expectedComputedConstantsData = nullptr; \
    double *expectedAlgebraicData = nullptr; \
    auto *states = new double[analyserModel->stateCount()]; \
    auto *rates = new double[analyserModel->stateCount()]; \
    auto *constants = new double[analyserModel->constantCount()]; \
    auto *computedConstants = new double[analyserModel->computedConstantCount()]; \
    auto *algebraic = new double[analyserModel->algebraicCount()]; \
\
    (void)expectedStatesData; \
    (void)expectedRatesData; \
    (void)expectedConstantsData; \
    (void)expectedComputedConstantsData; \
    (void)expectedAlgebraicData; \
    interpreter->initialiseVariablesForDifferentialModel(states, rates, constants, computedConstants, algebraic); \
    interpreter->computeComputedConstants(constants, computedConstants); \
    interpreter->computeRates(0.0, states, rates, constants, computedConstants, algebraic); \
    interpreter->computeVariablesForDifferentialModel(0.0, states, rates, constants, computedConstants, algebraic);

#define INITIALISE_COMPILED_DIFFERENTIAL_MODEL(model) \
    expectedStatesData = model::createStatesArray(); \
    expectedRatesData = model::createStatesArray(); \
    expectedConstantsData = model::createConstantsArray(); \
    expectedComputedConstantsData = model::createComputedConstantsArray(); \
    expectedAlgebraicData = model::createAlgebraicArray(); \
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
    std::vector<double> expectedAlgebraic(expectedAlgebraicData, expectedAlgebraicData + model::ALGEBRAIC_COUNT);

#define FINALISE_MODEL() \
    delete[] expectedStatesData; \
    delete[] expectedRatesData; \
    delete[] expectedConstantsData; \
    delete[] expectedComputedConstantsData; \
    delete[] expectedAlgebraicData; \
    delete[] states; \
    delete[] rates; \
    delete[] constants; \
    delete[] computedConstants; \
    delete[] algebraic;

#define STRINGIFY(x) #x

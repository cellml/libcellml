/* The content of this file was generated using the C profile of libCellML 0.6.0. */

#include "model.untracked.variables.with.externals.h"

#include <math.h>
#include <stdlib.h>

const char VERSION[] = "0.6.0";
const char LIBCELLML_VERSION[] = "0.6.0";

const size_t STATE_COUNT = 3;
const size_t CONSTANT_COUNT = 0;
const size_t COMPUTED_CONSTANT_COUNT = 0;
const size_t ALGEBRAIC_COUNT = 0;
const size_t EXTERNAL_COUNT = 0;

const VariableInfo VOI_INFO = {"time", "millisecond", "environment"};

const VariableInfo STATE_INFO[] = {
    {"h", "dimensionless", "sodium_channel_h_gate"},
    {"m", "dimensionless", "sodium_channel_m_gate"},
    {"n", "dimensionless", "potassium_channel_n_gate"}
};

const VariableInfo CONSTANT_INFO[] = {
};

const VariableInfo COMPUTED_CONSTANT_INFO[] = {
};

const VariableInfo ALGEBRAIC_INFO[] = {
};

const VariableInfo EXTERNAL_INFO[] = {
};

double * createStatesArray()
{
    double *res = (double *) malloc(STATE_COUNT*sizeof(double));

    for (size_t i = 0; i < STATE_COUNT; ++i) {
        res[i] = NAN;
    }

    return res;
}

double * createConstantsArray()
{
    double *res = (double *) malloc(CONSTANT_COUNT*sizeof(double));

    for (size_t i = 0; i < CONSTANT_COUNT; ++i) {
        res[i] = NAN;
    }

    return res;
}

double * createComputedConstantsArray()
{
    double *res = (double *) malloc(COMPUTED_CONSTANT_COUNT*sizeof(double));

    for (size_t i = 0; i < COMPUTED_CONSTANT_COUNT; ++i) {
        res[i] = NAN;
    }

    return res;
}

double * createAlgebraicArray()
{
    double *res = (double *) malloc(ALGEBRAIC_COUNT*sizeof(double));

    for (size_t i = 0; i < ALGEBRAIC_COUNT; ++i) {
        res[i] = NAN;
    }

    return res;
}

double * createExternalsArray()
{
    double *res = (double *) malloc(EXTERNAL_COUNT*sizeof(double));

    for (size_t i = 0; i < EXTERNAL_COUNT; ++i) {
        res[i] = NAN;
    }

    return res;
}

void deleteArray(double *array)
{
    free(array);
}

void initialiseVariables(double *states, double *rates, double *constants, double *computedConstants, double *algebraic)
{
    states[0] = 0.6;
    states[1] = 0.05;
    states[2] = 0.325;
}

void computeComputedConstants(double *constants, double *computedConstants)
{
}

void computeRates(double voi, double *states, double *rates, double *constants, double *computedConstants, double *algebraic, double *externals, ExternalVariable externalVariable)
{
    double membrane_V = externalVariable(voi, states, rates, constants, computedConstants, algebraic, externals, 0);
    double sodium_channel_m_gate_alpha_m = 0.1*(membrane_V+25.0)/(exp((membrane_V+25.0)/10.0)-1.0);
    double sodium_channel_m_gate_beta_m = 4.0*exp(membrane_V/18.0);
    rates[1] = sodium_channel_m_gate_alpha_m*(1.0-states[1])-sodium_channel_m_gate_beta_m*states[1];
    double sodium_channel_h_gate_alpha_h = 0.07*exp(membrane_V/20.0);
    double sodium_channel_h_gate_beta_h = 1.0/(exp((membrane_V+30.0)/10.0)+1.0);
    rates[0] = sodium_channel_h_gate_alpha_h*(1.0-states[0])-sodium_channel_h_gate_beta_h*states[0];
    double potassium_channel_n_gate_alpha_n = externalVariable(voi, states, rates, constants, computedConstants, algebraic, externals, 2);
    double potassium_channel_n_gate_beta_n = 0.125*exp(membrane_V/80.0);
    rates[2] = potassium_channel_n_gate_alpha_n*(1.0-states[2])-potassium_channel_n_gate_beta_n*states[2];
}

void computeVariables(double voi, double *states, double *rates, double *constants, double *computedConstants, double *algebraic, double *externals, ExternalVariable externalVariable)
{
}

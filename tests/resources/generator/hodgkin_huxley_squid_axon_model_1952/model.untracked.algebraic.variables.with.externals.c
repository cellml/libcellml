/* The content of this file was generated using the C profile of libCellML 0.6.2. */

#include "model.untracked.algebraic.variables.with.externals.h"

#include <math.h>
#include <stdlib.h>

const char VERSION[] = "0.6.0";
const char LIBCELLML_VERSION[] = "0.6.2";

const size_t STATE_COUNT = 3;
const size_t CONSTANT_COUNT = 5;
const size_t COMPUTED_CONSTANT_COUNT = 3;
const size_t ALGEBRAIC_COUNT = 0;
const size_t EXTERNAL_COUNT = 3;

const VariableInfo VOI_INFO = {"time", "millisecond", "environment"};

const VariableInfo STATE_INFO[] = {
    {"h", "dimensionless", "sodium_channel_h_gate"},
    {"m", "dimensionless", "sodium_channel_m_gate"},
    {"n", "dimensionless", "potassium_channel_n_gate"}
};

const VariableInfo CONSTANT_INFO[] = {
    {"Cm", "microF_per_cm2", "membrane"},
    {"E_R", "millivolt", "membrane"},
    {"g_L", "milliS_per_cm2", "leakage_current"},
    {"g_Na", "milliS_per_cm2", "sodium_channel"},
    {"g_K", "milliS_per_cm2", "potassium_channel"}
};

const VariableInfo COMPUTED_CONSTANT_INFO[] = {
    {"E_L", "millivolt", "leakage_current"},
    {"E_Na", "millivolt", "sodium_channel"},
    {"E_K", "millivolt", "potassium_channel"}
};

const VariableInfo ALGEBRAIC_INFO[] = {
};

const VariableInfo EXTERNAL_INFO[] = {
    {"V", "millivolt", "membrane"},
    {"i_Na", "microA_per_cm2", "sodium_channel"},
    {"alpha_n", "per_millisecond", "potassium_channel_n_gate"}
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
    constants[0] = 1.0;
    constants[1] = 0.0;
    constants[2] = 0.3;
    constants[3] = 120.0;
    constants[4] = 36.0;
}

void computeComputedConstants(double *constants, double *computedConstants)
{
    computedConstants[0] = constants[1]-10.613;
    computedConstants[1] = constants[1]-115.0;
    computedConstants[2] = constants[1]+12.0;
}

void computeRates(double voi, double *states, double *rates, double *constants, double *computedConstants, double *algebraic, double *externals, ExternalVariable externalVariable)
{
    externals[0] = externalVariable(voi, states, rates, constants, computedConstants, algebraic, externals, 0);
    double sodium_channel_m_gate_alpha_m = 0.1*(externals[0]+25.0)/(exp((externals[0]+25.0)/10.0)-1.0);
    double sodium_channel_m_gate_beta_m = 4.0*exp(externals[0]/18.0);
    rates[1] = sodium_channel_m_gate_alpha_m*(1.0-states[1])-sodium_channel_m_gate_beta_m*states[1];
    double sodium_channel_h_gate_alpha_h = 0.07*exp(externals[0]/20.0);
    double sodium_channel_h_gate_beta_h = 1.0/(exp((externals[0]+30.0)/10.0)+1.0);
    rates[0] = sodium_channel_h_gate_alpha_h*(1.0-states[0])-sodium_channel_h_gate_beta_h*states[0];
    externals[2] = externalVariable(voi, states, rates, constants, computedConstants, algebraic, externals, 2);
    double potassium_channel_n_gate_beta_n = 0.125*exp(externals[0]/80.0);
    rates[2] = externals[2]*(1.0-states[2])-potassium_channel_n_gate_beta_n*states[2];
}

void computeVariables(double voi, double *states, double *rates, double *constants, double *computedConstants, double *algebraic, double *externals, ExternalVariable externalVariable)
{
    externals[0] = externalVariable(voi, states, rates, constants, computedConstants, algebraic, externals, 0);
    externals[2] = externalVariable(voi, states, rates, constants, computedConstants, algebraic, externals, 2);
    externals[1] = externalVariable(voi, states, rates, constants, computedConstants, algebraic, externals, 1);
}

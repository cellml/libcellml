/* The content of this file was generated using the C profile of libCellML 0.5.0. */

#include "model.dependent.state.h"

#include <math.h>
#include <stdlib.h>

const char VERSION[] = "0.6.0";
const char LIBCELLML_VERSION[] = "0.5.0";

const size_t STATE_COUNT = 2;
const size_t CONSTANT_COUNT = 5;
const size_t COMPUTED_CONSTANT_COUNT = 3;
const size_t ALGEBRAIC_COUNT = 10;
const size_t EXTERNAL_COUNT = 2;

const VariableInfo VOI_INFO = {"time", "millisecond", "environment"};

const VariableInfo STATE_INFO[] = {
    {"h", "dimensionless", "sodium_channel_h_gate"},
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
    {"i_Stim", "microA_per_cm2", "membrane"},
    {"i_L", "microA_per_cm2", "leakage_current"},
    {"i_K", "microA_per_cm2", "potassium_channel"},
    {"i_Na", "microA_per_cm2", "sodium_channel"},
    {"alpha_m", "per_millisecond", "sodium_channel_m_gate"},
    {"beta_m", "per_millisecond", "sodium_channel_m_gate"},
    {"alpha_h", "per_millisecond", "sodium_channel_h_gate"},
    {"beta_h", "per_millisecond", "sodium_channel_h_gate"},
    {"alpha_n", "per_millisecond", "potassium_channel_n_gate"},
    {"beta_n", "per_millisecond", "potassium_channel_n_gate"}
};

const VariableInfo EXTERNAL_INFO[] = {
    {"V", "millivolt", "membrane"},
    {"m", "dimensionless", "sodium_channel_m_gate"}
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

void initialiseVariables(double voi, double *states, double *rates, double *constants, double *algebraic)
{
    states[0] = 0.6;
    states[1] = 0.325;
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

void computeRates(double voi, double *states, double *rates, double *constants, double *computedConstants, double *algebraic, ExternalVariable externalVariable)
{
    external[1] = externalVariable(voi, states, rates, variables, 1);
    algebraic[8] = 0.07*exp(external[1]/20.0);
    algebraic[9] = 1.0/(exp((external[1]+30.0)/10.0)+1.0);
    rates[0] = algebraic[8]*(1.0-states[0])-algebraic[9]*states[0];
    algebraic[10] = 0.01*(external[1]+10.0)/(exp((external[1]+10.0)/10.0)-1.0);
    algebraic[11] = 0.125*exp(external[1]/80.0);
    rates[1] = algebraic[10]*(1.0-states[1])-algebraic[11]*states[1];
}

void computeVariables(double voi, double *states, double *rates, double *constants, double *computedConstants, double *algebraic, ExternalVariable externalVariable)
{
    algebraic[0] = ((voi >= 10.0) && (voi <= 10.5))?-20.0:0.0;
    external[1] = externalVariable(voi, states, rates, variables, 1);
    algebraic[2] = constants[2]*(external[1]-computedConstants[0]);
    external[5] = externalVariable(voi, states, rates, variables, 5);
    algebraic[4] = constants[3]*pow(external[5], 3.0)*states[0]*(external[1]-computedConstants[1]);
    algebraic[6] = 0.1*(external[1]+25.0)/(exp((external[1]+25.0)/10.0)-1.0);
    algebraic[7] = 4.0*exp(external[1]/18.0);
    algebraic[3] = constants[4]*pow(states[1], 4.0)*(external[1]-computedConstants[2]);
}

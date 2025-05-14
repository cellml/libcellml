/* The content of this file was generated using the C profile of libCellML 0.6.3. */

#include "model.untracked.constants.h"

#include <math.h>
#include <stdlib.h>

const char VERSION[] = "0.6.0";
const char LIBCELLML_VERSION[] = "0.6.3";

const size_t STATE_COUNT = 4;
const size_t CONSTANT_COUNT = 0;
const size_t COMPUTED_CONSTANT_COUNT = 3;
const size_t ALGEBRAIC_COUNT = 10;

const VariableInfo VOI_INFO = {"time", "millisecond", "environment"};

const VariableInfo STATE_INFO[] = {
    {"V", "millivolt", "membrane"},
    {"h", "dimensionless", "sodium_channel_h_gate"},
    {"m", "dimensionless", "sodium_channel_m_gate"},
    {"n", "dimensionless", "potassium_channel_n_gate"}
};

const VariableInfo CONSTANT_INFO[] = {
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

void deleteArray(double *array)
{
    free(array);
}

void initialiseVariables(double *states, double *rates, double *constants, double *computedConstants, double *algebraic)
{
    states[0] = 0.0;
    states[1] = 0.6;
    states[2] = 0.05;
    states[3] = 0.325;
}

void computeComputedConstants(double *constants, double *computedConstants)
{
    double membrane_E_R = 0.0;
    computedConstants[0] = membrane_E_R-10.613;
    computedConstants[1] = membrane_E_R-115.0;
    computedConstants[2] = membrane_E_R+12.0;
}

void computeRates(double voi, double *states, double *rates, double *constants, double *computedConstants, double *algebraic)
{
    double membrane_Cm = 1.0;
    algebraic[0] = ((voi >= 10.0) && (voi <= 10.5))?-20.0:0.0;
    double leakage_current_g_L = 0.3;
    algebraic[1] = leakage_current_g_L*(states[0]-computedConstants[0]);
    double potassium_channel_g_K = 36.0;
    algebraic[2] = potassium_channel_g_K*pow(states[3], 4.0)*(states[0]-computedConstants[2]);
    double sodium_channel_g_Na = 120.0;
    algebraic[3] = sodium_channel_g_Na*pow(states[2], 3.0)*states[1]*(states[0]-computedConstants[1]);
    rates[0] = -(-algebraic[0]+algebraic[3]+algebraic[2]+algebraic[1])/membrane_Cm;
    algebraic[5] = 4.0*exp(states[0]/18.0);
    algebraic[4] = 0.1*(states[0]+25.0)/(exp((states[0]+25.0)/10.0)-1.0);
    rates[2] = algebraic[4]*(1.0-states[2])-algebraic[5]*states[2];
    algebraic[7] = 1.0/(exp((states[0]+30.0)/10.0)+1.0);
    algebraic[6] = 0.07*exp(states[0]/20.0);
    rates[1] = algebraic[6]*(1.0-states[1])-algebraic[7]*states[1];
    algebraic[9] = 0.125*exp(states[0]/80.0);
    algebraic[8] = 0.01*(states[0]+10.0)/(exp((states[0]+10.0)/10.0)-1.0);
    rates[3] = algebraic[8]*(1.0-states[3])-algebraic[9]*states[3];
}

void computeVariables(double voi, double *states, double *rates, double *constants, double *computedConstants, double *algebraic)
{
    double leakage_current_g_L = 0.3;
    algebraic[1] = leakage_current_g_L*(states[0]-computedConstants[0]);
    double sodium_channel_g_Na = 120.0;
    algebraic[3] = sodium_channel_g_Na*pow(states[2], 3.0)*states[1]*(states[0]-computedConstants[1]);
    algebraic[4] = 0.1*(states[0]+25.0)/(exp((states[0]+25.0)/10.0)-1.0);
    algebraic[5] = 4.0*exp(states[0]/18.0);
    algebraic[6] = 0.07*exp(states[0]/20.0);
    algebraic[7] = 1.0/(exp((states[0]+30.0)/10.0)+1.0);
    double potassium_channel_g_K = 36.0;
    algebraic[2] = potassium_channel_g_K*pow(states[3], 4.0)*(states[0]-computedConstants[2]);
    algebraic[8] = 0.01*(states[0]+10.0)/(exp((states[0]+10.0)/10.0)-1.0);
    algebraic[9] = 0.125*exp(states[0]/80.0);
}

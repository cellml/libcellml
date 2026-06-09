/* The content of this file was generated using the C profile of libCellML 0.7.0. */

#include "model.variant.untracked.control.h"

#include <math.h>
#include <stdlib.h>

const char VERSION[] = "0.8.0";
const char LIBCELLML_VERSION[] = "0.7.0";

const size_t STATE_COUNT = 4;
const size_t CONSTANT_COUNT = 5;
const size_t COMPUTED_CONSTANT_COUNT = 3;
const size_t ALGEBRAIC_VARIABLE_COUNT = 10;

const VariableInfo VOI_INFO = {"time", "millisecond", "environment"};

const VariableInfo STATE_INFO[] = {
    {"V", "millivolt", "membrane"},
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

const VariableInfo ALGEBRAIC_VARIABLE_INFO[] = {
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

double * createAlgebraicVariablesArray()
{
    double *res = (double *) malloc(ALGEBRAIC_VARIABLE_COUNT*sizeof(double));

    for (size_t i = 0; i < ALGEBRAIC_VARIABLE_COUNT; ++i) {
        res[i] = NAN;
    }

    return res;
}

void deleteArray(double *array)
{
    free(array);
}

void initialiseArrays(double *states, double *rates, double *constants, double *computedConstants, double *algebraicVariables)
{
    states[0] = 0.0;
    states[1] = 0.6;
    states[2] = 0.05;
    states[3] = 0.325;
    constants[0] = 1.0;
    constants[1] = 0.0;
    constants[2] = 0.3;
    constants[3] = 120.0;
    constants[4] = 36.0;
}

void computeComputedConstants(double voi, double *states, double *rates, double *constants, double *computedConstants, double *algebraicVariables)
{
    computedConstants[0] = -10.613+constants[1];
    computedConstants[1] = -115.0+constants[1];
    computedConstants[2] = 12.0+constants[1];
}

void computeRates(double voi, double *states, double *rates, double *constants, double *computedConstants, double *algebraicVariables)
{
    algebraicVariables[3] = states[0]*states[1]*pow(states[2], 3.0)*constants[3]-states[1]*pow(states[2], 3.0)*constants[3]*computedConstants[1];
    algebraicVariables[0] = ((voi >= 10.0) && (voi <= 10.5))?-20.0:0.0;
    algebraicVariables[1] = states[0]*constants[2]-computedConstants[0]*constants[2];
    algebraicVariables[2] = -pow(states[3], 4.0)*computedConstants[2]*constants[4]+states[0]*pow(states[3], 4.0)*constants[4];
    rates[0] = (-algebraicVariables[2]-algebraicVariables[1]+algebraicVariables[0]-algebraicVariables[3])/constants[0];
    algebraicVariables[4] = 0.1*states[0]/(-1.0+exp(2.5+0.1*states[0]))+2.5/(-1.0+exp(2.5+0.1*states[0]));
    algebraicVariables[5] = 4.0*exp(0.0555555555555556*states[0]);
    rates[2] = -states[2]*algebraicVariables[5]+(1.0-states[2])*algebraicVariables[4];
    algebraicVariables[6] = 0.07*exp(0.05*states[0]);
    algebraicVariables[7] = 1.0/(1.0+exp(3.0+0.1*states[0]));
    rates[1] = -states[1]*algebraicVariables[7]+(1.0-states[1])*algebraicVariables[6];
    algebraicVariables[8] = 0.01*states[0]/(-1.0+exp(1.0+0.1*states[0]))+0.1/(-1.0+exp(1.0+0.1*states[0]));
    algebraicVariables[9] = 0.125*exp(0.0125*states[0]);
    rates[3] = -states[3]*algebraicVariables[9]+(1.0-states[3])*algebraicVariables[8];
}

void computeVariables(double voi, double *states, double *rates, double *constants, double *computedConstants, double *algebraicVariables)
{
    algebraicVariables[1] = states[0]*constants[2]-computedConstants[0]*constants[2];
    algebraicVariables[3] = states[0]*states[1]*pow(states[2], 3.0)*constants[3]-states[1]*pow(states[2], 3.0)*constants[3]*computedConstants[1];
    algebraicVariables[4] = 0.1*states[0]/(-1.0+exp(2.5+0.1*states[0]))+2.5/(-1.0+exp(2.5+0.1*states[0]));
    algebraicVariables[5] = 4.0*exp(0.0555555555555556*states[0]);
    algebraicVariables[6] = 0.07*exp(0.05*states[0]);
    algebraicVariables[7] = 1.0/(1.0+exp(3.0+0.1*states[0]));
    algebraicVariables[2] = -pow(states[3], 4.0)*computedConstants[2]*constants[4]+states[0]*pow(states[3], 4.0)*constants[4];
    algebraicVariables[8] = 0.01*states[0]/(-1.0+exp(1.0+0.1*states[0]))+0.1/(-1.0+exp(1.0+0.1*states[0]));
    algebraicVariables[9] = 0.125*exp(0.0125*states[0]);
}

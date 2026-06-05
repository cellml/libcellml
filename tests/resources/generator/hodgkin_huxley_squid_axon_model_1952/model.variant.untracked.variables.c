/* The content of this file was generated using the C profile of libCellML 0.7.0. */

#include "model.variant.untracked.variables.h"

#include <math.h>
#include <stdlib.h>

const char VERSION[] = "0.8.0";
const char LIBCELLML_VERSION[] = "0.7.0";

const size_t STATE_COUNT = 4;
const size_t CONSTANT_COUNT = 0;
const size_t COMPUTED_CONSTANT_COUNT = 0;
const size_t ALGEBRAIC_VARIABLE_COUNT = 0;

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
};

const VariableInfo ALGEBRAIC_VARIABLE_INFO[] = {
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
}

void computeComputedConstants(double voi, double *states, double *rates, double *constants, double *computedConstants, double *algebraicVariables)
{
}

void computeRates(double voi, double *states, double *rates, double *constants, double *computedConstants, double *algebraicVariables)
{
    double membrane_Cm = 1.0;
    double sodium_channel_g_Na = 120.0;
    double membrane_E_R = 0.0;
    double sodium_channel_E_Na = -115.0+membrane_E_R;
    double sodium_channel_i_Na = states[0]*states[1]*pow(states[2], 3.0)*sodium_channel_g_Na-states[1]*pow(states[2], 3.0)*sodium_channel_g_Na*sodium_channel_E_Na;
    double membrane_i_Stim = ((voi >= 10.0) && (voi <= 10.5))?-20.0:0.0;
    double leakage_current_g_L = 0.3;
    double leakage_current_E_L = -10.613+membrane_E_R;
    double leakage_current_i_L = states[0]*leakage_current_g_L-leakage_current_E_L*leakage_current_g_L;
    double potassium_channel_g_K = 36.0;
    double potassium_channel_E_K = 12.0+membrane_E_R;
    double potassium_channel_i_K = -pow(states[3], 4.0)*potassium_channel_E_K*potassium_channel_g_K+states[0]*pow(states[3], 4.0)*potassium_channel_g_K;
    rates[0] = (-potassium_channel_i_K-leakage_current_i_L+membrane_i_Stim-sodium_channel_i_Na)/membrane_Cm;
    double sodium_channel_m_gate_alpha_m = 0.1*states[0]/(-1.0+exp(2.5+0.1*states[0]))+2.5/(-1.0+exp(2.5+0.1*states[0]));
    double sodium_channel_m_gate_beta_m = 4.0*exp(0.0555555555555556*states[0]);
    rates[2] = -states[2]*sodium_channel_m_gate_beta_m+(1.0-states[2])*sodium_channel_m_gate_alpha_m;
    double sodium_channel_h_gate_alpha_h = 0.07*exp(0.05*states[0]);
    double sodium_channel_h_gate_beta_h = 1.0/(1.0+exp(3.0+0.1*states[0]));
    rates[1] = -states[1]*sodium_channel_h_gate_beta_h+(1.0-states[1])*sodium_channel_h_gate_alpha_h;
    double potassium_channel_n_gate_alpha_n = 0.01*states[0]/(-1.0+exp(1.0+0.1*states[0]))+0.1/(-1.0+exp(1.0+0.1*states[0]));
    double potassium_channel_n_gate_beta_n = 0.125*exp(0.0125*states[0]);
    rates[3] = -states[3]*potassium_channel_n_gate_beta_n+(1.0-states[3])*potassium_channel_n_gate_alpha_n;
}

void computeVariables(double voi, double *states, double *rates, double *constants, double *computedConstants, double *algebraicVariables)
{
}

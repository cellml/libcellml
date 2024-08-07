/* The content of this file was generated using the C profile of libCellML 0.5.0. */

#include "model.dependent.state.h"

#include <math.h>
#include <stdlib.h>

const char VERSION[] = "0.6.0";
const char LIBCELLML_VERSION[] = "0.5.0";

const size_t STATE_COUNT = 2;
const size_t CONSTANT_COUNT = 0;
const size_t COMPUTED_CONSTANT_COUNT = 0;
const size_t ALGEBRAIC_COUNT = 20;

const VariableInfo VOI_INFO = {"time", "millisecond", "environment", VARIABLE_OF_INTEGRATION};

const VariableInfo STATE_INFO[] = {
    {"h", "dimensionless", "sodium_channel_h_gate", STATE},
    {"n", "dimensionless", "potassium_channel_n_gate", STATE}
};

const VariableInfo VARIABLE_INFO[] = {
    {"i_Stim", "microA_per_cm2", "membrane", ALGEBRAIC},
    {"V", "millivolt", "membrane", EXTERNAL},
    {"i_L", "microA_per_cm2", "leakage_current", ALGEBRAIC},
    {"i_K", "microA_per_cm2", "potassium_channel", ALGEBRAIC},
    {"i_Na", "microA_per_cm2", "sodium_channel", ALGEBRAIC},
    {"Cm", "microF_per_cm2", "membrane", CONSTANT},
    {"E_R", "millivolt", "membrane", CONSTANT},
    {"E_L", "millivolt", "leakage_current", COMPUTED_CONSTANT},
    {"g_L", "milliS_per_cm2", "leakage_current", CONSTANT},
    {"E_Na", "millivolt", "sodium_channel", COMPUTED_CONSTANT},
    {"g_Na", "milliS_per_cm2", "sodium_channel", CONSTANT},
    {"m", "dimensionless", "sodium_channel_m_gate", EXTERNAL},
    {"alpha_m", "per_millisecond", "sodium_channel_m_gate", ALGEBRAIC},
    {"beta_m", "per_millisecond", "sodium_channel_m_gate", ALGEBRAIC},
    {"alpha_h", "per_millisecond", "sodium_channel_h_gate", ALGEBRAIC},
    {"beta_h", "per_millisecond", "sodium_channel_h_gate", ALGEBRAIC},
    {"E_K", "millivolt", "potassium_channel", COMPUTED_CONSTANT},
    {"g_K", "milliS_per_cm2", "potassium_channel", CONSTANT},
    {"alpha_n", "per_millisecond", "potassium_channel_n_gate", ALGEBRAIC},
    {"beta_n", "per_millisecond", "potassium_channel_n_gate", ALGEBRAIC}
};

double * createStatesArray()
{
    double *res = (double *) malloc(STATE_COUNT*sizeof(double));

    for (size_t i = 0; i < STATE_COUNT; ++i) {
        res[i] = NAN;
    }

    return res;
}

double * createVariablesArray()
{
    double *res = (double *) malloc(VARIABLE_COUNT*sizeof(double));

    for (size_t i = 0; i < VARIABLE_COUNT; ++i) {
        res[i] = NAN;
    }

    return res;
}

void deleteArray(double *array)
{
    free(array);
}

void initialiseVariables(double voi, double *states, double *rates, double *constants, ExternalVariable externalVariable)
{
    constants[5] = 1.0;
    constants[6] = 0.0;
    constants[8] = 0.3;
    constants[10] = 120.0;
    constants[17] = 36.0;
    states[0] = 0.6;
    states[1] = 0.325;
    algebraic[1] = externalVariable(voi, states, rates, variables, 1);
    algebraic[11] = externalVariable(voi, states, rates, variables, 11);
}

void computeComputedConstants(double *constants, double *computedConstants)
{
    computedConstants[7] = constants[6]-10.613;
    computedConstants[9] = constants[6]-115.0;
    computedConstants[16] = constants[6]+12.0;
}

void computeRates(double voi, double *states, double *rates, double *constants, double *computedConstants, double *algebraic, ExternalVariable externalVariable)
{
    algebraic[1] = externalVariable(voi, states, rates, variables, 1);
    algebraic[14] = 0.07*exp(algebraic[1]/20.0);
    algebraic[15] = 1.0/(exp((algebraic[1]+30.0)/10.0)+1.0);
    rates[0] = algebraic[14]*(1.0-states[0])-algebraic[15]*states[0];
    algebraic[18] = 0.01*(algebraic[1]+10.0)/(exp((algebraic[1]+10.0)/10.0)-1.0);
    algebraic[19] = 0.125*exp(algebraic[1]/80.0);
    rates[1] = algebraic[18]*(1.0-states[1])-algebraic[19]*states[1];
}

void computeVariables(double voi, double *states, double *rates, double *constants, double *computedConstants, double *algebraic, ExternalVariable externalVariable)
{
    algebraic[0] = ((voi >= 10.0) && (voi <= 10.5))?-20.0:0.0;
    algebraic[1] = externalVariable(voi, states, rates, variables, 1);
    algebraic[2] = constants[8]*(algebraic[1]-computedConstants[7]);
    algebraic[11] = externalVariable(voi, states, rates, variables, 11);
    algebraic[4] = constants[10]*pow(algebraic[11], 3.0)*states[0]*(algebraic[1]-computedConstants[9]);
    algebraic[12] = 0.1*(algebraic[1]+25.0)/(exp((algebraic[1]+25.0)/10.0)-1.0);
    algebraic[13] = 4.0*exp(algebraic[1]/18.0);
    algebraic[3] = constants[17]*pow(states[1], 4.0)*(algebraic[1]-computedConstants[16]);
}

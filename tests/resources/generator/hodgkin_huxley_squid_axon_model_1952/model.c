/* The content of this file was generated using the C profile of libCellML 0.5.0. */

#include "model.h"

#include <math.h>
#include <stdlib.h>

const char VERSION[] = "0.6.0";
const char LIBCELLML_VERSION[] = "0.5.0";

const size_t STATE_COUNT = 4;
const size_t CONSTANT_COUNT = 0;
const size_t COMPUTED_CONSTANT_COUNT = 0;
const size_t ALGEBRAIC_COUNT = 18;

const VariableInfo VOI_INFO = {"time", "millisecond", "environment", VARIABLE_OF_INTEGRATION};

const VariableInfo STATE_INFO[] = {
    {"V", "millivolt", "membrane", STATE},
    {"h", "dimensionless", "sodium_channel_h_gate", STATE},
    {"m", "dimensionless", "sodium_channel_m_gate", STATE},
    {"n", "dimensionless", "potassium_channel_n_gate", STATE}
};

const VariableInfo VARIABLE_INFO[] = {
    {"i_Stim", "microA_per_cm2", "membrane", ALGEBRAIC},
    {"i_L", "microA_per_cm2", "leakage_current", ALGEBRAIC},
    {"i_K", "microA_per_cm2", "potassium_channel", ALGEBRAIC},
    {"i_Na", "microA_per_cm2", "sodium_channel", ALGEBRAIC},
    {"Cm", "microF_per_cm2", "membrane", CONSTANT},
    {"E_R", "millivolt", "membrane", CONSTANT},
    {"E_L", "millivolt", "leakage_current", COMPUTED_CONSTANT},
    {"g_L", "milliS_per_cm2", "leakage_current", CONSTANT},
    {"E_Na", "millivolt", "sodium_channel", COMPUTED_CONSTANT},
    {"g_Na", "milliS_per_cm2", "sodium_channel", CONSTANT},
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

void initialiseVariables(double *states, double *rates, double *constants)
{
    constants[4] = 1.0;
    constants[5] = 0.0;
    constants[7] = 0.3;
    constants[9] = 120.0;
    constants[15] = 36.0;
    states[0] = 0.0;
    states[1] = 0.6;
    states[2] = 0.05;
    states[3] = 0.325;
}

void computeComputedConstants(double *constants, double *computedConstants)
{
    computedConstants[6] = constants[5]-10.613;
    computedConstants[8] = constants[5]-115.0;
    computedConstants[14] = constants[5]+12.0;
}

void computeRates(double voi, double *states, double *rates, double *constants, double *computedConstants, double *algebraic)
{
    algebraic[0] = ((voi >= 10.0) && (voi <= 10.5))?-20.0:0.0;
    algebraic[1] = constants[7]*(states[0]-computedConstants[6]);
    algebraic[2] = constants[15]*pow(states[3], 4.0)*(states[0]-computedConstants[14]);
    algebraic[3] = constants[9]*pow(states[2], 3.0)*states[1]*(states[0]-computedConstants[8]);
    rates[0] = -(-algebraic[0]+algebraic[3]+algebraic[2]+algebraic[1])/constants[4];
    algebraic[10] = 0.1*(states[0]+25.0)/(exp((states[0]+25.0)/10.0)-1.0);
    algebraic[11] = 4.0*exp(states[0]/18.0);
    rates[2] = algebraic[10]*(1.0-states[2])-algebraic[11]*states[2];
    algebraic[12] = 0.07*exp(states[0]/20.0);
    algebraic[13] = 1.0/(exp((states[0]+30.0)/10.0)+1.0);
    rates[1] = algebraic[12]*(1.0-states[1])-algebraic[13]*states[1];
    algebraic[16] = 0.01*(states[0]+10.0)/(exp((states[0]+10.0)/10.0)-1.0);
    algebraic[17] = 0.125*exp(states[0]/80.0);
    rates[3] = algebraic[16]*(1.0-states[3])-algebraic[17]*states[3];
}

void computeVariables(double voi, double *states, double *rates, double *constants, double *computedConstants, double *algebraic)
{
    algebraic[1] = constants[7]*(states[0]-computedConstants[6]);
    algebraic[3] = constants[9]*pow(states[2], 3.0)*states[1]*(states[0]-computedConstants[8]);
    algebraic[10] = 0.1*(states[0]+25.0)/(exp((states[0]+25.0)/10.0)-1.0);
    algebraic[11] = 4.0*exp(states[0]/18.0);
    algebraic[12] = 0.07*exp(states[0]/20.0);
    algebraic[13] = 1.0/(exp((states[0]+30.0)/10.0)+1.0);
    algebraic[2] = constants[15]*pow(states[3], 4.0)*(states[0]-computedConstants[14]);
    algebraic[16] = 0.01*(states[0]+10.0)/(exp((states[0]+10.0)/10.0)-1.0);
    algebraic[17] = 0.125*exp(states[0]/80.0);
}

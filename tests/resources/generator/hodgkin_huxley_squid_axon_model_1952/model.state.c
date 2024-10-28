/* The content of this file was generated using the C profile of libCellML 0.6.1. */

#include "model.state.h"

#include <math.h>
#include <stdlib.h>

const char VERSION[] = "0.5.0";
const char LIBCELLML_VERSION[] = "0.6.1";

const size_t STATE_COUNT = 3;
const size_t VARIABLE_COUNT = 19;

const VariableInfo VOI_INFO = {"time", "millisecond", "environment", VARIABLE_OF_INTEGRATION};

const VariableInfo STATE_INFO[] = {
    {"V", "millivolt", "membrane", STATE},
    {"h", "dimensionless", "sodium_channel_h_gate", STATE},
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

void initialiseVariables(double voi, double *states, double *rates, double *variables, ExternalVariable externalVariable)
{
    variables[4] = 1.0;
    variables[5] = 0.0;
    variables[7] = 0.3;
    variables[9] = 120.0;
    variables[16] = 36.0;
    states[0] = 0.0;
    states[1] = 0.6;
    states[2] = 0.325;
    variables[10] = externalVariable(voi, states, rates, variables, 10);
}

void computeComputedConstants(double *variables)
{
    variables[6] = variables[5]-10.613;
    variables[8] = variables[5]-115.0;
    variables[15] = variables[5]+12.0;
}

void computeRates(double voi, double *states, double *rates, double *variables, ExternalVariable externalVariable)
{
    variables[0] = ((voi >= 10.0) && (voi <= 10.5))?-20.0:0.0;
    variables[1] = variables[7]*(states[0]-variables[6]);
    variables[2] = variables[16]*pow(states[2], 4.0)*(states[0]-variables[15]);
    variables[10] = externalVariable(voi, states, rates, variables, 10);
    variables[3] = variables[9]*pow(variables[10], 3.0)*states[1]*(states[0]-variables[8]);
    rates[0] = -(-variables[0]+variables[3]+variables[2]+variables[1])/variables[4];
    variables[13] = 0.07*exp(states[0]/20.0);
    variables[14] = 1.0/(exp((states[0]+30.0)/10.0)+1.0);
    rates[1] = variables[13]*(1.0-states[1])-variables[14]*states[1];
    variables[17] = 0.01*(states[0]+10.0)/(exp((states[0]+10.0)/10.0)-1.0);
    variables[18] = 0.125*exp(states[0]/80.0);
    rates[2] = variables[17]*(1.0-states[2])-variables[18]*states[2];
}

void computeVariables(double voi, double *states, double *rates, double *variables, ExternalVariable externalVariable)
{
    variables[1] = variables[7]*(states[0]-variables[6]);
    variables[10] = externalVariable(voi, states, rates, variables, 10);
    variables[3] = variables[9]*pow(variables[10], 3.0)*states[1]*(states[0]-variables[8]);
    variables[11] = 0.1*(states[0]+25.0)/(exp((states[0]+25.0)/10.0)-1.0);
    variables[12] = 4.0*exp(states[0]/18.0);
    variables[13] = 0.07*exp(states[0]/20.0);
    variables[14] = 1.0/(exp((states[0]+30.0)/10.0)+1.0);
    variables[2] = variables[16]*pow(states[2], 4.0)*(states[0]-variables[15]);
    variables[17] = 0.01*(states[0]+10.0)/(exp((states[0]+10.0)/10.0)-1.0);
    variables[18] = 0.125*exp(states[0]/80.0);
}

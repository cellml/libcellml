/* The content of this file was generated using the C profile of libCellML 0.2.0. */

#include "model.state.h"

#include <math.h>
#include <stdlib.h>

const char VERSION[] = "0.3.0";
const char LIBCELLML_VERSION[] = "0.2.0";

const size_t STATE_COUNT = 3;
const size_t VARIABLE_COUNT = 19;

const VariableInfo VOI_INFO = {"time", "millisecond", "environment", VARIABLE_OF_INTEGRATION};

const VariableInfo STATE_INFO[] = {
    {"h", "dimensionless", "sodium_channel_h_gate", STATE},
    {"n", "dimensionless", "potassium_channel_n_gate", STATE},
    {"V", "millivolt", "membrane", STATE}
};

const VariableInfo VARIABLE_INFO[] = {
    {"m", "dimensionless", "sodium_channel_m_gate", EXTERNAL},
    {"g_L", "milliS_per_cm2", "leakage_current", CONSTANT},
    {"Cm", "microF_per_cm2", "membrane", CONSTANT},
    {"E_R", "millivolt", "membrane", CONSTANT},
    {"g_K", "milliS_per_cm2", "potassium_channel", CONSTANT},
    {"g_Na", "milliS_per_cm2", "sodium_channel", CONSTANT},
    {"i_Stim", "microA_per_cm2", "membrane", ALGEBRAIC},
    {"E_L", "millivolt", "leakage_current", COMPUTED_CONSTANT},
    {"i_L", "microA_per_cm2", "leakage_current", ALGEBRAIC},
    {"E_Na", "millivolt", "sodium_channel", COMPUTED_CONSTANT},
    {"i_Na", "microA_per_cm2", "sodium_channel", ALGEBRAIC},
    {"alpha_m", "per_millisecond", "sodium_channel_m_gate", ALGEBRAIC},
    {"beta_m", "per_millisecond", "sodium_channel_m_gate", ALGEBRAIC},
    {"alpha_h", "per_millisecond", "sodium_channel_h_gate", ALGEBRAIC},
    {"beta_h", "per_millisecond", "sodium_channel_h_gate", ALGEBRAIC},
    {"E_K", "millivolt", "potassium_channel", COMPUTED_CONSTANT},
    {"i_K", "microA_per_cm2", "potassium_channel", ALGEBRAIC},
    {"alpha_n", "per_millisecond", "potassium_channel_n_gate", ALGEBRAIC},
    {"beta_n", "per_millisecond", "potassium_channel_n_gate", ALGEBRAIC}
};

double * createStatesArray()
{
    return malloc(STATE_COUNT*sizeof(double));
}

double * createVariablesArray()
{
    return malloc(VARIABLE_COUNT*sizeof(double));
}

void deleteArray(double *array)
{
    free(array);
}

void initialiseVariables(double voi, double *states, double *variables, ExternalVariable externalVariable)
{
    variables[1] = 0.3;
    variables[2] = 1.0;
    variables[3] = 0.0;
    variables[4] = 36.0;
    variables[5] = 120.0;
    states[0] = 0.6;
    states[1] = 0.325;
    states[2] = 0.0;
    variables[0] = externalVariable(voi, states, variables, 0);
}

void computeComputedConstants(double *variables)
{
    variables[7] = variables[3]-10.613;
    variables[9] = variables[3]-115.0;
    variables[15] = variables[3]+12.0;
}

void computeRates(double voi, double *states, double *rates, double *variables, ExternalVariable externalVariable)
{
    variables[13] = 0.07*exp(states[2]/20.0);
    variables[14] = 1.0/(exp((states[2]+30.0)/10.0)+1.0);
    rates[0] = variables[13]*(1.0-states[0])-variables[14]*states[0];
    variables[17] = 0.01*(states[2]+10.0)/(exp((states[2]+10.0)/10.0)-1.0);
    variables[18] = 0.125*exp(states[2]/80.0);
    rates[1] = variables[17]*(1.0-states[1])-variables[18]*states[1];
    variables[6] = ((voi >= 10.0) && (voi <= 10.5))?-20.0:0.0;
    variables[8] = variables[1]*(states[2]-variables[7]);
    variables[16] = variables[4]*pow(states[1], 4.0)*(states[2]-variables[15]);
    variables[0] = externalVariable(voi, states, variables, 0);
    variables[10] = variables[5]*pow(variables[0], 3.0)*states[0]*(states[2]-variables[9]);
    rates[2] = -(-variables[6]+variables[10]+variables[16]+variables[8])/variables[2];
}

void computeVariables(double voi, double *states, double *rates, double *variables, ExternalVariable externalVariable)
{
    variables[0] = externalVariable(voi, states, variables, 0);
    variables[8] = variables[1]*(states[2]-variables[7]);
    variables[10] = variables[5]*pow(variables[0], 3.0)*states[0]*(states[2]-variables[9]);
    variables[11] = 0.1*(states[2]+25.0)/(exp((states[2]+25.0)/10.0)-1.0);
    variables[12] = 4.0*exp(states[2]/18.0);
    variables[13] = 0.07*exp(states[2]/20.0);
    variables[14] = 1.0/(exp((states[2]+30.0)/10.0)+1.0);
    variables[16] = variables[4]*pow(states[1], 4.0)*(states[2]-variables[15]);
    variables[17] = 0.01*(states[2]+10.0)/(exp((states[2]+10.0)/10.0)-1.0);
    variables[18] = 0.125*exp(states[2]/80.0);
}

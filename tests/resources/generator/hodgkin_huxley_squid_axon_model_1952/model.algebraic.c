/* The content of this file was generated using the C profile of libCellML 0.3.99. */

#include "model.algebraic.h"

#include <math.h>
#include <stdlib.h>

const char VERSION[] = "0.3.0";
const char LIBCELLML_VERSION[] = "0.3.99";

const size_t STATE_COUNT = 4;
const size_t VARIABLE_COUNT = 18;

const VariableInfo VOI_INFO = {"time", "millisecond", "environment", VARIABLE_OF_INTEGRATION};

const VariableInfo STATE_INFO[] = {
    {"m", "dimensionless", "sodium_channel_m_gate", STATE},
    {"h", "dimensionless", "sodium_channel_h_gate", STATE},
    {"n", "dimensionless", "potassium_channel_n_gate", STATE},
    {"V", "millivolt", "membrane", STATE}
};

const VariableInfo VARIABLE_INFO[] = {
    {"g_L", "milliS_per_cm2", "leakage_current", CONSTANT},
    {"Cm", "microF_per_cm2", "membrane", CONSTANT},
    {"E_R", "millivolt", "membrane", CONSTANT},
    {"g_K", "milliS_per_cm2", "potassium_channel", CONSTANT},
    {"g_Na", "milliS_per_cm2", "sodium_channel", CONSTANT},
    {"i_Stim", "microA_per_cm2", "membrane", EXTERNAL},
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
    variables[0] = 0.3;
    variables[1] = 1.0;
    variables[2] = 0.0;
    variables[3] = 36.0;
    variables[4] = 120.0;
    states[0] = 0.05;
    states[1] = 0.6;
    states[2] = 0.325;
    states[3] = 0.0;
    variables[5] = externalVariable(voi, states, variables, 5);
}

void computeComputedConstants(double *variables)
{
    variables[6] = variables[2]-10.613;
    variables[8] = variables[2]-115.0;
    variables[14] = variables[2]+12.0;
}

void computeRates(double voi, double *states, double *rates, double *variables, ExternalVariable externalVariable)
{
    variables[10] = 0.1*(states[3]+25.0)/(exp((states[3]+25.0)/10.0)-1.0);
    variables[11] = 4.0*exp(states[3]/18.0);
    rates[0] = variables[10]*(1.0-states[0])-variables[11]*states[0];
    variables[12] = 0.07*exp(states[3]/20.0);
    variables[13] = 1.0/(exp((states[3]+30.0)/10.0)+1.0);
    rates[1] = variables[12]*(1.0-states[1])-variables[13]*states[1];
    variables[16] = 0.01*(states[3]+10.0)/(exp((states[3]+10.0)/10.0)-1.0);
    variables[17] = 0.125*exp(states[3]/80.0);
    rates[2] = variables[16]*(1.0-states[2])-variables[17]*states[2];
    variables[5] = externalVariable(voi, states, variables, 5);
    variables[7] = variables[0]*(states[3]-variables[6]);
    variables[15] = variables[3]*pow(states[2], 4.0)*(states[3]-variables[14]);
    variables[9] = variables[4]*pow(states[0], 3.0)*states[1]*(states[3]-variables[8]);
    rates[3] = -(-variables[5]+variables[9]+variables[15]+variables[7])/variables[1];
}

void computeVariables(double voi, double *states, double *rates, double *variables, ExternalVariable externalVariable)
{
    variables[5] = externalVariable(voi, states, variables, 5);
    variables[7] = variables[0]*(states[3]-variables[6]);
    variables[9] = variables[4]*pow(states[0], 3.0)*states[1]*(states[3]-variables[8]);
    variables[10] = 0.1*(states[3]+25.0)/(exp((states[3]+25.0)/10.0)-1.0);
    variables[11] = 4.0*exp(states[3]/18.0);
    variables[12] = 0.07*exp(states[3]/20.0);
    variables[13] = 1.0/(exp((states[3]+30.0)/10.0)+1.0);
    variables[15] = variables[3]*pow(states[2], 4.0)*(states[3]-variables[14]);
    variables[16] = 0.01*(states[3]+10.0)/(exp((states[3]+10.0)/10.0)-1.0);
    variables[17] = 0.125*exp(states[3]/80.0);
}

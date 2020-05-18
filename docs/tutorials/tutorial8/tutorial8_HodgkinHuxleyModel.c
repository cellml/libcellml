/* The content of this file was generated using the C profile of libCellML 0.2.0. */

#include "model.h"

#include <math.h>
#include <stdlib.h>

const char VERSION[] = "0.1.0";
const char LIBCELLML_VERSION[] = "0.2.0";

const size_t STATE_COUNT = 4;
const size_t VARIABLE_COUNT = 18;

const VariableInfo VOI_INFO = {"t", "ms", "membrane"};

const VariableInfo STATE_INFO[] = {
    {"m", "dimensionless", "mGate"},
    {"h", "dimensionless", "hGate"},
    {"n", "dimensionless", "nGate"},
    {"V", "mV", "membrane"}
};

const VariableInfoWithType VARIABLE_INFO[] = {
    {"Cm", "microF_per_cm2", "parameters", CONSTANT},
    {"E_K", "mV", "parameters", CONSTANT},
    {"E_L", "mV", "parameters", CONSTANT},
    {"E_Na", "mV", "parameters", CONSTANT},
    {"g_K", "mS_per_cm2", "parameters", CONSTANT},
    {"g_L", "mS_per_cm2", "parameters", CONSTANT},
    {"g_Na", "mS_per_cm2", "parameters", CONSTANT},
    {"i_stim", "microA_per_cm2", "membrane", ALGEBRAIC},
    {"Na_conductance", "mS_per_cm2", "sodium_channel", ALGEBRAIC},
    {"i_Na", "microA_per_cm2", "sodium_channel", ALGEBRAIC},
    {"alpha_m", "per_ms", "mGate", ALGEBRAIC},
    {"beta_m", "per_ms", "mGate", ALGEBRAIC},
    {"alpha_h", "per_ms", "hGate", ALGEBRAIC},
    {"beta_h", "per_ms", "hGate", ALGEBRAIC},
    {"i_K", "microA_per_cm2", "potassium_channel", ALGEBRAIC},
    {"alpha_n", "per_millisecond", "nGate", ALGEBRAIC},
    {"beta_n", "per_millisecond", "nGate", ALGEBRAIC},
    {"i_L", "microA_per_cm2", "leakage", ALGEBRAIC}
};

double * createStatesArray()
{
    return (double *) malloc(STATE_COUNT*sizeof(double));
}

double * createVariablesArray()
{
    return (double *) malloc(VARIABLE_COUNT*sizeof(double));
}

void deleteArray(double *array)
{
    free(array);
}

void initializeStatesAndConstants(double *states, double *variables)
{
    states[0] = 0.05;
    states[1] = 0.6;
    states[2] = 0.325;
    states[3] = -75.0;
    variables[0] = 1.0;
    variables[1] = -87.0;
    variables[2] = -64.387;
    variables[3] = 40.0;
    variables[4] = 36.0;
    variables[5] = 0.3;
    variables[6] = 120.0;
}

void computeComputedConstants(double *variables)
{
}

void computeRates(double voi, double *states, double *rates, double *variables)
{
    variables[10] = -0.1*(states[3]+50.0)/(exp(-(states[3]+50.0)/10.0)-1.0);
    variables[11] = 4.0*exp(-(states[3]+75.0)/18.0);
    rates[0] = variables[10]*(1.0-states[0])-variables[11]*states[0];
    variables[12] = 0.07*exp(-(states[3]+75.0)/20.0);
    variables[13] = 1.0/(exp(-(states[3]+45.0)/10.0)+1.0);
    rates[1] = variables[12]*(1.0-states[1])-variables[13]*states[1];
    variables[15] = -0.01*(states[3]+65.0)/(exp(-(states[3]+65.0)/10.0)-1.0);
    variables[16] = 0.125*exp((states[3]+75.0)/80.0);
    rates[2] = variables[15]*(1.0-states[2])-variables[16]*states[2];
    variables[7] = ((voi >= 10.0) && (voi <= 10.5))?20.0:0.0;
    variables[17] = variables[5]*(states[3]-variables[2]);
    variables[14] = pow(states[2], 4.0)*variables[4]*(states[3]-variables[1]);
    variables[8] = variables[6]*states[1]*pow(states[0], 3.0);
    variables[9] = variables[8]*(states[3]-variables[3]);
    rates[3] = -(-variables[7]+variables[9]+variables[14]+variables[17])/variables[0];
}

void computeVariables(double voi, double *states, double *rates, double *variables)
{
    variables[8] = variables[6]*states[1]*pow(states[0], 3.0);
    variables[9] = variables[8]*(states[3]-variables[3]);
    variables[10] = -0.1*(states[3]+50.0)/(exp(-(states[3]+50.0)/10.0)-1.0);
    variables[11] = 4.0*exp(-(states[3]+75.0)/18.0);
    variables[12] = 0.07*exp(-(states[3]+75.0)/20.0);
    variables[13] = 1.0/(exp(-(states[3]+45.0)/10.0)+1.0);
    variables[14] = pow(states[2], 4.0)*variables[4]*(states[3]-variables[1]);
    variables[15] = -0.01*(states[3]+65.0)/(exp(-(states[3]+65.0)/10.0)-1.0);
    variables[16] = 0.125*exp((states[3]+75.0)/80.0);
    variables[17] = variables[5]*(states[3]-variables[2]);
}

/* The content of this file was generated using the C profile of libCellML 0.2.0. */

#include "model.h"

#include <math.h>
#include <stdlib.h>

const char VERSION[] = "0.1.0";
const char LIBCELLML_VERSION[] = "0.2.0";

const size_t STATE_COUNT = 4;
const size_t VARIABLE_COUNT = 17;

const VariableInfo VOI_INFO = {"time", "millisecond", "environment"};

const VariableInfo STATE_INFO[] = {
    {"m", "dimensionless", "sodium_channel_m_gate"},
    {"h", "dimensionless", "sodium_channel_h_gate"},
    {"n", "dimensionless", "potassium_channel_n_gate"},
    {"V", "millivolt", "membrane"}
};

const VariableInfoWithType VARIABLE_INFO[] = {
    {"E_L", "millivolt", "leakage_current", CONSTANT},
    {"g_L", "milliS_per_cm2", "leakage_current", CONSTANT},
    {"Cm", "microF_per_cm2", "membrane", CONSTANT},
    {"E_Na", "millivolt", "sodium_channel", CONSTANT},
    {"g_Na_max", "milliS_per_cm2", "sodium_channel", CONSTANT},
    {"i_Leak", "microA_per_cm2", "leakage_current", ALGEBRAIC},
    {"g_Na", "milliS_per_cm2", "sodium_channel", ALGEBRAIC},
    {"i_Na", "microA_per_cm2", "sodium_channel", ALGEBRAIC},
    {"alpha_m", "per_millisecond", "sodium_channel_m_gate", ALGEBRAIC},
    {"beta_m", "per_millisecond", "sodium_channel_m_gate", ALGEBRAIC},
    {"alpha_h", "per_millisecond", "sodium_channel_h_gate", ALGEBRAIC},
    {"beta_h", "per_millisecond", "sodium_channel_h_gate", ALGEBRAIC},
    {"g_K1", "milliS_per_cm2", "potassium_channel", ALGEBRAIC},
    {"g_K2", "milliS_per_cm2", "potassium_channel", ALGEBRAIC},
    {"alpha_n", "per_millisecond", "potassium_channel_n_gate", ALGEBRAIC},
    {"beta_n", "per_millisecond", "potassium_channel_n_gate", ALGEBRAIC},
    {"i_K", "microA_per_cm2", "potassium_channel", ALGEBRAIC}
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
    variables[0] = -60.0;
    variables[1] = 0.075;
    variables[2] = 12.0;
    variables[3] = 40.0;
    variables[4] = 400.0;
    states[0] = 0.01;
    states[1] = 0.8;
    states[2] = 0.01;
    states[3] = -87.0;
}

void computeComputedConstants(double *variables)
{
}

void computeRates(double voi, double *states, double *rates, double *variables)
{
    variables[8] = 0.1*(-states[3]-48.0)/(exp((-states[3]-48.0)/15.0)-1.0);
    variables[9] = 0.12*(states[3]+8.0)/(exp((states[3]+8.0)/5.0)-1.0);
    rates[0] = variables[8]*(1.0-states[0])-variables[9]*states[0];
    variables[10] = 0.17*exp((-states[3]-90.0)/20.0);
    variables[11] = 1.0/(1.0+exp((-states[3]-42.0)/10.0));
    rates[1] = variables[10]*(1.0-states[1])-variables[11]*states[1];
    variables[14] = 0.0001*(-states[3]-50.0)/(exp((-states[3]-50.0)/10.0)-1.0);
    variables[15] = 0.002*exp((-states[3]-90.0)/80.0);
    rates[2] = variables[14]*(1.0-states[2])-variables[15]*states[2];
    variables[6] = pow(states[0], 3.0)*states[1]*variables[4];
    variables[7] = (variables[6]+0.14)*(states[3]-variables[3]);
    variables[5] = variables[1]*(states[3]-variables[0]);
    variables[12] = 1.2*exp((-states[3]-90.0)/50.0)+0.015*exp((states[3]+90.0)/60.0);
    variables[13] = 1.2*pow(states[2], 4.0);
    variables[16] = (variables[12]+variables[13])*(states[3]+100.0);
    rates[3] = -(variables[7]+variables[16]+variables[5])/variables[2];
}

void computeVariables(double voi, double *states, double *rates, double *variables)
{
    variables[5] = variables[1]*(states[3]-variables[0]);
    variables[6] = pow(states[0], 3.0)*states[1]*variables[4];
    variables[7] = (variables[6]+0.14)*(states[3]-variables[3]);
    variables[8] = 0.1*(-states[3]-48.0)/(exp((-states[3]-48.0)/15.0)-1.0);
    variables[9] = 0.12*(states[3]+8.0)/(exp((states[3]+8.0)/5.0)-1.0);
    variables[10] = 0.17*exp((-states[3]-90.0)/20.0);
    variables[11] = 1.0/(1.0+exp((-states[3]-42.0)/10.0));
    variables[12] = 1.2*exp((-states[3]-90.0)/50.0)+0.015*exp((states[3]+90.0)/60.0);
    variables[13] = 1.2*pow(states[2], 4.0);
    variables[14] = 0.0001*(-states[3]-50.0)/(exp((-states[3]-50.0)/10.0)-1.0);
    variables[15] = 0.002*exp((-states[3]-90.0)/80.0);
    variables[16] = (variables[12]+variables[13])*(states[3]+100.0);
}

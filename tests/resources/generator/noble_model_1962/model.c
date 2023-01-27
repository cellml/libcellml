/* The content of this file was generated using the C profile of libCellML 0.4.0. */

#include "model.h"

#include <math.h>
#include <stdlib.h>

const char VERSION[] = "0.3.1";
const char LIBCELLML_VERSION[] = "0.4.0";

const size_t STATE_COUNT = 4;
const size_t VARIABLE_COUNT = 17;

const VariableInfo VOI_INFO = {"time", "millisecond", "environment", VARIABLE_OF_INTEGRATION};

const VariableInfo STATE_INFO[] = {
    {"V", "millivolt", "membrane", STATE},
    {"m", "dimensionless", "sodium_channel_m_gate", STATE},
    {"h", "dimensionless", "sodium_channel_h_gate", STATE},
    {"n", "dimensionless", "potassium_channel_n_gate", STATE}
};

const VariableInfo VARIABLE_INFO[] = {
    {"i_Na", "microA_per_cm2", "sodium_channel", ALGEBRAIC},
    {"i_Leak", "microA_per_cm2", "leakage_current", ALGEBRAIC},
    {"i_K", "microA_per_cm2", "potassium_channel", ALGEBRAIC},
    {"Cm", "microF_per_cm2", "membrane", CONSTANT},
    {"g_L", "milliS_per_cm2", "leakage_current", CONSTANT},
    {"E_L", "millivolt", "leakage_current", CONSTANT},
    {"g_Na", "milliS_per_cm2", "sodium_channel", ALGEBRAIC},
    {"g_Na_max", "milliS_per_cm2", "sodium_channel", CONSTANT},
    {"E_Na", "millivolt", "sodium_channel", CONSTANT},
    {"alpha_m", "per_millisecond", "sodium_channel_m_gate", ALGEBRAIC},
    {"beta_m", "per_millisecond", "sodium_channel_m_gate", ALGEBRAIC},
    {"alpha_h", "per_millisecond", "sodium_channel_h_gate", ALGEBRAIC},
    {"beta_h", "per_millisecond", "sodium_channel_h_gate", ALGEBRAIC},
    {"g_K1", "milliS_per_cm2", "potassium_channel", ALGEBRAIC},
    {"g_K2", "milliS_per_cm2", "potassium_channel", ALGEBRAIC},
    {"alpha_n", "per_millisecond", "potassium_channel_n_gate", ALGEBRAIC},
    {"beta_n", "per_millisecond", "potassium_channel_n_gate", ALGEBRAIC}
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

void initialiseVariables(double *states, double *variables)
{
    variables[3] = 12.0;
    variables[4] = 0.075;
    variables[5] = -60.0;
    variables[7] = 400.0;
    variables[8] = 40.0;
    states[0] = -87.0;
    states[1] = 0.01;
    states[2] = 0.8;
    states[3] = 0.01;
}

void computeComputedConstants(double *variables)
{
}

void computeRates(double voi, double *states, double *rates, double *variables)
{
    variables[6] = pow(states[1], 3.0)*states[2]*variables[7];
    variables[0] = (variables[6]+0.14)*(states[0]-variables[8]);
    variables[1] = variables[4]*(states[0]-variables[5]);
    variables[13] = 1.2*exp((-states[0]-90.0)/50.0)+0.015*exp((states[0]+90.0)/60.0);
    variables[14] = 1.2*pow(states[3], 4.0);
    variables[2] = (variables[13]+variables[14])*(states[0]+100.0);
    rates[0] = -(variables[0]+variables[2]+variables[1])/variables[3];
    variables[9] = 0.1*(-states[0]-48.0)/(exp((-states[0]-48.0)/15.0)-1.0);
    variables[10] = 0.12*(states[0]+8.0)/(exp((states[0]+8.0)/5.0)-1.0);
    rates[1] = variables[9]*(1.0-states[1])-variables[10]*states[1];
    variables[11] = 0.17*exp((-states[0]-90.0)/20.0);
    variables[12] = 1.0/(1.0+exp((-states[0]-42.0)/10.0));
    rates[2] = variables[11]*(1.0-states[2])-variables[12]*states[2];
    variables[15] = 0.0001*(-states[0]-50.0)/(exp((-states[0]-50.0)/10.0)-1.0);
    variables[16] = 0.002*exp((-states[0]-90.0)/80.0);
    rates[3] = variables[15]*(1.0-states[3])-variables[16]*states[3];
}

void computeVariables(double voi, double *states, double *rates, double *variables)
{
    variables[1] = variables[4]*(states[0]-variables[5]);
    variables[6] = pow(states[1], 3.0)*states[2]*variables[7];
    variables[0] = (variables[6]+0.14)*(states[0]-variables[8]);
    variables[9] = 0.1*(-states[0]-48.0)/(exp((-states[0]-48.0)/15.0)-1.0);
    variables[10] = 0.12*(states[0]+8.0)/(exp((states[0]+8.0)/5.0)-1.0);
    variables[11] = 0.17*exp((-states[0]-90.0)/20.0);
    variables[12] = 1.0/(1.0+exp((-states[0]-42.0)/10.0));
    variables[13] = 1.2*exp((-states[0]-90.0)/50.0)+0.015*exp((states[0]+90.0)/60.0);
    variables[14] = 1.2*pow(states[3], 4.0);
    variables[2] = (variables[13]+variables[14])*(states[0]+100.0);
    variables[15] = 0.0001*(-states[0]-50.0)/(exp((-states[0]-50.0)/10.0)-1.0);
    variables[16] = 0.002*exp((-states[0]-90.0)/80.0);
}

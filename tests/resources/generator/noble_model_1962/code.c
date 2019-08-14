/* The contents of this file was generated from version 0.2.0 of libCellML. */
#include <stddef.h>
#include <stdlib.h>
#include <math.h>

const char version[] = "0.2.0";

struct VARIABLE_INFO {
    char name[9];
    char units[16];
};

const size_t STATE_VECTOR_SIZE = 4;
const size_t VARIABLE_VECTOR_SIZE = 17;
const struct VARIABLE_INFO VOI = {"time", "millisecond"};

const struct VARIABLE_INFO STATE_VECTOR_INFORMATION_ARRAY[] = {
    {"m", "dimensionless"},
    {"h", "dimensionless"},
    {"n", "dimensionless"},
    {"V", "millivolt"},
};

const struct VARIABLE_INFO VARIABLE_VECTOR_INFORMATION_ARRAY[] = {
    {"E_L", "millivolt"},
    {"g_L", "milliS_per_cm2"},
    {"Cm", "microF_per_cm2"},
    {"E_Na", "millivolt"},
    {"g_Na_max", "milliS_per_cm2"},
    {"i_Leak", "microA_per_cm2"},
    {"g_Na", "milliS_per_cm2"},
    {"i_Na", "microA_per_cm2"},
    {"alpha_m", "per_millisecond"},
    {"beta_m", "per_millisecond"},
    {"alpha_h", "per_millisecond"},
    {"beta_h", "per_millisecond"},
    {"g_K1", "milliS_per_cm2"},
    {"g_K2", "milliS_per_cm2"},
    {"alpha_n", "per_millisecond"},
    {"beta_n", "per_millisecond"},
    {"i_K", "microA_per_cm2"},
};

double *createStateVector()
{
    return (double *)malloc(4 * sizeof (double));
}

double *createRateVector()
{
    return (double *)malloc(4 * sizeof (double));
}

double *createVariableVector()
{
    return (double *)malloc(17 * sizeof (double));
}

void freeVector(double *array)
{
   free(array);
}

void initializeConstants(double *states, double *variables)
{
    states[0] = 0.01;
    states[1] = 0.8;
    states[2] = 0.01;
    states[3] = -87.0;
    variables[0] = -60.0;
    variables[1] = 0.075;
    variables[2] = 12.0;
    variables[3] = 40.0;
    variables[4] = 400.0;
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

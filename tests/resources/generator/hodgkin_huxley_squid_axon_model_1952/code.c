/* The contents of this file was generated from version 0.2.0 of libCellML. */
#include <stddef.h>
#include <stdlib.h>
#include <math.h>

const char version[] = "0.2.0";

struct VARIABLE_INFO {
    char component[25];
    char name[8];
    char units[16];
};

const size_t STATE_VECTOR_SIZE = 4;
const size_t VARIABLE_VECTOR_SIZE = 18;
const struct VARIABLE_INFO VOI = {"membrane", "time", "millisecond"};

const struct VARIABLE_INFO STATE_VECTOR_INFORMATION_ARRAY[] = {
    {"sodium_channel_m_gate", "m", "dimensionless"},
    {"sodium_channel_h_gate", "h", "dimensionless"},
    {"potassium_channel_n_gate", "n", "dimensionless"},
    {"membrane", "V", "millivolt"},
};

const struct VARIABLE_INFO VARIABLE_VECTOR_INFORMATION_ARRAY[] = {
    {"leakage_current", "g_L", "milliS_per_cm2"},
    {"membrane", "Cm", "microF_per_cm2"},
    {"membrane", "E_R", "millivolt"},
    {"potassium_channel", "g_K", "milliS_per_cm2"},
    {"sodium_channel", "g_Na", "milliS_per_cm2"},
    {"leakage_current", "E_L", "millivolt"},
    {"sodium_channel", "E_Na", "millivolt"},
    {"potassium_channel", "E_K", "millivolt"},
    {"membrane", "i_Stim", "microA_per_cm2"},
    {"membrane", "i_L", "microA_per_cm2"},
    {"membrane", "i_Na", "microA_per_cm2"},
    {"sodium_channel_m_gate", "alpha_m", "per_millisecond"},
    {"sodium_channel_m_gate", "beta_m", "per_millisecond"},
    {"sodium_channel_h_gate", "alpha_h", "per_millisecond"},
    {"sodium_channel_h_gate", "beta_h", "per_millisecond"},
    {"membrane", "i_K", "microA_per_cm2"},
    {"potassium_channel_n_gate", "alpha_n", "per_millisecond"},
    {"potassium_channel_n_gate", "beta_n", "per_millisecond"},
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
    return (double *)malloc(18 * sizeof (double));
}

void freeVector(double *array)
{
   free(array);
}

void initializeConstants(double *states, double *variables)
{
    states[0] = 0.05;
    states[1] = 0.6;
    states[2] = 0.325;
    states[3] = 0.0;
    variables[0] = 0.3;
    variables[1] = 1.0;
    variables[2] = 0.0;
    variables[3] = 36.0;
    variables[4] = 120.0;
}

void computeComputedConstants(double *variables)
{
    variables[6] = variables[2]-10.613;
    variables[8] = variables[2]-115.0;
    variables[14] = variables[2]+12.0;
}

void computeRates(double voi, double *states, double *rates, double *variables)
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
    variables[5] = ((voi >= 10.0) && (voi <= 10.5))?-20.0:0.0;
    variables[7] = variables[0]*(states[3]-variables[6]);
    variables[15] = variables[3]*pow(states[2], 4.0)*(states[3]-variables[14]);
    variables[9] = variables[4]*pow(states[0], 3.0)*states[1]*(states[3]-variables[8]);
    rates[3] = -(-variables[5]+variables[9]+variables[15]+variables[7])/variables[1];
}

void computeVariables(double voi, double *states, double *rates, double *variables)
{
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

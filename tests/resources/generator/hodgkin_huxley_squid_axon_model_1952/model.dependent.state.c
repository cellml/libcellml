/* The content of this file was generated using the C profile of libCellML 0.6.2. */

#include "model.dependent.state.h"

#include <math.h>
#include <stdlib.h>

const char VERSION[] = "0.5.0";
const char LIBCELLML_VERSION[] = "0.6.2";

const size_t STATE_COUNT = 2;
const size_t VARIABLE_COUNT = 20;

const VariableInfo VOI_INFO = {"time", "millisecond", "environment", VARIABLE_OF_INTEGRATION};

const VariableInfo STATE_INFO[] = {
    {"h", "dimensionless", "sodium_channel_h_gate", STATE},
    {"n", "dimensionless", "potassium_channel_n_gate", STATE}
};

const VariableInfo VARIABLE_INFO[] = {
    {"i_Stim", "microA_per_cm2", "membrane", ALGEBRAIC},
    {"Cm", "microF_per_cm2", "membrane", CONSTANT},
    {"i_L", "microA_per_cm2", "leakage_current", ALGEBRAIC},
    {"i_K", "microA_per_cm2", "potassium_channel", ALGEBRAIC},
    {"i_Na", "microA_per_cm2", "sodium_channel", ALGEBRAIC},
    {"V", "millivolt", "membrane", EXTERNAL},
    {"E_R", "millivolt", "membrane", CONSTANT},
    {"E_L", "millivolt", "leakage_current", COMPUTED_CONSTANT},
    {"g_L", "milliS_per_cm2", "leakage_current", CONSTANT},
    {"E_Na", "millivolt", "sodium_channel", COMPUTED_CONSTANT},
    {"m", "dimensionless", "sodium_channel_m_gate", EXTERNAL},
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

void initialiseVariables(double voi, double *states, double *rates, double *variables, ExternalVariable externalVariable)
{
    variables[1] = 1.0;
    variables[6] = 0.0;
    variables[8] = 0.3;
    variables[11] = 120.0;
    variables[17] = 36.0;
    states[0] = 0.6;
    states[1] = 0.325;
    variables[5] = externalVariable(voi, states, rates, variables, 5);
    variables[10] = externalVariable(voi, states, rates, variables, 10);
}

void computeComputedConstants(double *variables)
{
    variables[7] = variables[6]-10.613;
    variables[9] = variables[6]-115.0;
    variables[16] = variables[6]+12.0;
}

void computeRates(double voi, double *states, double *rates, double *variables, ExternalVariable externalVariable)
{
    variables[5] = externalVariable(voi, states, rates, variables, 5);
    variables[15] = 1.0/(exp((variables[5]+30.0)/10.0)+1.0);
    variables[14] = 0.07*exp(variables[5]/20.0);
    rates[0] = variables[14]*(1.0-states[0])-variables[15]*states[0];
    variables[19] = 0.125*exp(variables[5]/80.0);
    variables[18] = 0.01*(variables[5]+10.0)/(exp((variables[5]+10.0)/10.0)-1.0);
    rates[1] = variables[18]*(1.0-states[1])-variables[19]*states[1];
}

void computeVariables(double voi, double *states, double *rates, double *variables, ExternalVariable externalVariable)
{
    variables[0] = ((voi >= 10.0) && (voi <= 10.5))?-20.0:0.0;
    variables[5] = externalVariable(voi, states, rates, variables, 5);
    variables[2] = variables[8]*(variables[5]-variables[7]);
    variables[10] = externalVariable(voi, states, rates, variables, 10);
    variables[4] = variables[11]*pow(variables[10], 3.0)*states[0]*(variables[5]-variables[9]);
    variables[12] = 0.1*(variables[5]+25.0)/(exp((variables[5]+25.0)/10.0)-1.0);
    variables[13] = 4.0*exp(variables[5]/18.0);
    variables[3] = variables[17]*pow(states[1], 4.0)*(variables[5]-variables[16]);
}

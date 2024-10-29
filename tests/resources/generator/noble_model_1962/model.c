/* The content of this file was generated using the C profile of libCellML 0.6.2. */

#include "model.h"

#include <math.h>
#include <stdlib.h>

const char VERSION[] = "0.6.0";
const char LIBCELLML_VERSION[] = "0.6.2";

const size_t STATE_COUNT = 4;
const size_t CONSTANT_COUNT = 5;
const size_t COMPUTED_CONSTANT_COUNT = 0;
const size_t ALGEBRAIC_COUNT = 12;

const VariableInfo VOI_INFO = {"time", "millisecond", "environment"};

const VariableInfo STATE_INFO[] = {
    {"V", "millivolt", "membrane"},
    {"m", "dimensionless", "sodium_channel_m_gate"},
    {"h", "dimensionless", "sodium_channel_h_gate"},
    {"n", "dimensionless", "potassium_channel_n_gate"}
};

const VariableInfo CONSTANT_INFO[] = {
    {"Cm", "microF_per_cm2", "membrane"},
    {"g_L", "milliS_per_cm2", "leakage_current"},
    {"E_L", "millivolt", "leakage_current"},
    {"g_Na_max", "milliS_per_cm2", "sodium_channel"},
    {"E_Na", "millivolt", "sodium_channel"}
};

const VariableInfo COMPUTED_CONSTANT_INFO[] = {
};

const VariableInfo ALGEBRAIC_INFO[] = {
    {"i_Na", "microA_per_cm2", "sodium_channel"},
    {"i_Leak", "microA_per_cm2", "leakage_current"},
    {"i_K", "microA_per_cm2", "potassium_channel"},
    {"g_Na", "milliS_per_cm2", "sodium_channel"},
    {"alpha_m", "per_millisecond", "sodium_channel_m_gate"},
    {"beta_m", "per_millisecond", "sodium_channel_m_gate"},
    {"alpha_h", "per_millisecond", "sodium_channel_h_gate"},
    {"beta_h", "per_millisecond", "sodium_channel_h_gate"},
    {"g_K1", "milliS_per_cm2", "potassium_channel"},
    {"g_K2", "milliS_per_cm2", "potassium_channel"},
    {"alpha_n", "per_millisecond", "potassium_channel_n_gate"},
    {"beta_n", "per_millisecond", "potassium_channel_n_gate"}
};

double * createStatesArray()
{
    double *res = (double *) malloc(STATE_COUNT*sizeof(double));

    for (size_t i = 0; i < STATE_COUNT; ++i) {
        res[i] = NAN;
    }

    return res;
}

double * createConstantsArray()
{
    double *res = (double *) malloc(CONSTANT_COUNT*sizeof(double));

    for (size_t i = 0; i < CONSTANT_COUNT; ++i) {
        res[i] = NAN;
    }

    return res;
}

double * createComputedConstantsArray()
{
    double *res = (double *) malloc(COMPUTED_CONSTANT_COUNT*sizeof(double));

    for (size_t i = 0; i < COMPUTED_CONSTANT_COUNT; ++i) {
        res[i] = NAN;
    }

    return res;
}

double * createAlgebraicArray()
{
    double *res = (double *) malloc(ALGEBRAIC_COUNT*sizeof(double));

    for (size_t i = 0; i < ALGEBRAIC_COUNT; ++i) {
        res[i] = NAN;
    }

    return res;
}

void deleteArray(double *array)
{
    free(array);
}

void initialiseVariables(double *states, double *rates, double *constants, double *computedConstants, double *algebraic)
{
    states[0] = -87.0;
    states[1] = 0.01;
    states[2] = 0.8;
    states[3] = 0.01;
    constants[0] = 12.0;
    constants[1] = 0.075;
    constants[2] = -60.0;
    constants[3] = 400.0;
    constants[4] = 40.0;
}

void computeComputedConstants(double *constants, double *computedConstants)
{
}

void computeRates(double voi, double *states, double *rates, double *constants, double *computedConstants, double *algebraic)
{
    algebraic[3] = pow(states[1], 3.0)*states[2]*constants[3];
    algebraic[0] = (algebraic[3]+0.14)*(states[0]-constants[4]);
    algebraic[1] = constants[1]*(states[0]-constants[2]);
    algebraic[8] = 1.2*exp((-states[0]-90.0)/50.0)+0.015*exp((states[0]+90.0)/60.0);
    algebraic[9] = 1.2*pow(states[3], 4.0);
    algebraic[2] = (algebraic[8]+algebraic[9])*(states[0]+100.0);
    rates[0] = -(algebraic[0]+algebraic[2]+algebraic[1])/constants[0];
    algebraic[4] = 0.1*(-states[0]-48.0)/(exp((-states[0]-48.0)/15.0)-1.0);
    algebraic[5] = 0.12*(states[0]+8.0)/(exp((states[0]+8.0)/5.0)-1.0);
    rates[1] = algebraic[4]*(1.0-states[1])-algebraic[5]*states[1];
    algebraic[6] = 0.17*exp((-states[0]-90.0)/20.0);
    algebraic[7] = 1.0/(1.0+exp((-states[0]-42.0)/10.0));
    rates[2] = algebraic[6]*(1.0-states[2])-algebraic[7]*states[2];
    algebraic[10] = 0.0001*(-states[0]-50.0)/(exp((-states[0]-50.0)/10.0)-1.0);
    algebraic[11] = 0.002*exp((-states[0]-90.0)/80.0);
    rates[3] = algebraic[10]*(1.0-states[3])-algebraic[11]*states[3];
}

void computeVariables(double voi, double *states, double *rates, double *constants, double *computedConstants, double *algebraic)
{
    algebraic[1] = constants[1]*(states[0]-constants[2]);
    algebraic[3] = pow(states[1], 3.0)*states[2]*constants[3];
    algebraic[0] = (algebraic[3]+0.14)*(states[0]-constants[4]);
    algebraic[4] = 0.1*(-states[0]-48.0)/(exp((-states[0]-48.0)/15.0)-1.0);
    algebraic[5] = 0.12*(states[0]+8.0)/(exp((states[0]+8.0)/5.0)-1.0);
    algebraic[6] = 0.17*exp((-states[0]-90.0)/20.0);
    algebraic[7] = 1.0/(1.0+exp((-states[0]-42.0)/10.0));
    algebraic[8] = 1.2*exp((-states[0]-90.0)/50.0)+0.015*exp((states[0]+90.0)/60.0);
    algebraic[9] = 1.2*pow(states[3], 4.0);
    algebraic[2] = (algebraic[8]+algebraic[9])*(states[0]+100.0);
    algebraic[10] = 0.0001*(-states[0]-50.0)/(exp((-states[0]-50.0)/10.0)-1.0);
    algebraic[11] = 0.002*exp((-states[0]-90.0)/80.0);
}

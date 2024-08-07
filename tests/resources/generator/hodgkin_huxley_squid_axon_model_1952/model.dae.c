/* The content of this file was generated using the C profile of libCellML 0.5.0. */

#include "model.dae.h"

#include <math.h>
#include <stdlib.h>

const char VERSION[] = "0.5.0";
const char LIBCELLML_VERSION[] = "0.5.0";

const size_t STATE_COUNT = 4;
const size_t CONSTANT_COUNT = 0;
const size_t COMPUTED_CONSTANT_COUNT = 0;
const size_t ALGEBRAIC_COUNT = 18;

const VariableInfo VOI_INFO = {"time", "millisecond", "environment", VARIABLE_OF_INTEGRATION};

const VariableInfo STATE_INFO[] = {
    {"V", "millivolt", "membrane", STATE},
    {"h", "dimensionless", "sodium_channel_h_gate", STATE},
    {"m", "dimensionless", "sodium_channel_m_gate", STATE},
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

typedef struct {
    double voi;
    double *states;
    double *rates;
    double *variables;
} RootFindingInfo;

extern void nlaSolve(void (*objectiveFunction)(double *, double *, void *),
                     double *u, size_t n, void *data);

void objectiveFunction0(double *u, double *f, void *data)
{
    double voi = ((RootFindingInfo *) data)->voi;
    double *states = ((RootFindingInfo *) data)->states;
    double *rates = ((RootFindingInfo *) data)->rates;
    double *variables = ((RootFindingInfo *) data)->variables;

    variables[0] = u[0];

    f[0] = variables[0]-(((voi >= 10.0) && (voi <= 10.5))?-20.0:0.0)-0.0;
}

void findRoot0(double voi, double *states, double *rates, double *variables)
{
    RootFindingInfo rfi = { voi, states, rates, variables };
    double u[1];

    u[0] = variables[0];

    nlaSolve(objectiveFunction0, u, 1, &rfi);

    variables[0] = u[0];
}

void objectiveFunction1(double *u, double *f, void *data)
{
    double voi = ((RootFindingInfo *) data)->voi;
    double *states = ((RootFindingInfo *) data)->states;
    double *rates = ((RootFindingInfo *) data)->rates;
    double *variables = ((RootFindingInfo *) data)->variables;

    rates[0] = u[0];

    f[0] = rates[0]-(-(-variables[0]+variables[3]+variables[2]+variables[1])/variables[4])-0.0;
}

void findRoot1(double voi, double *states, double *rates, double *variables)
{
    RootFindingInfo rfi = { voi, states, rates, variables };
    double u[1];

    u[0] = rates[0];

    nlaSolve(objectiveFunction1, u, 1, &rfi);

    rates[0] = u[0];
}

void objectiveFunction2(double *u, double *f, void *data)
{
    double voi = ((RootFindingInfo *) data)->voi;
    double *states = ((RootFindingInfo *) data)->states;
    double *rates = ((RootFindingInfo *) data)->rates;
    double *variables = ((RootFindingInfo *) data)->variables;

    variables[6] = u[0];

    f[0] = variables[6]-(variables[5]-10.613)-0.0;
}

void findRoot2(double voi, double *states, double *rates, double *variables)
{
    RootFindingInfo rfi = { voi, states, rates, variables };
    double u[1];

    u[0] = variables[6];

    nlaSolve(objectiveFunction2, u, 1, &rfi);

    variables[6] = u[0];
}

void objectiveFunction3(double *u, double *f, void *data)
{
    double voi = ((RootFindingInfo *) data)->voi;
    double *states = ((RootFindingInfo *) data)->states;
    double *rates = ((RootFindingInfo *) data)->rates;
    double *variables = ((RootFindingInfo *) data)->variables;

    variables[1] = u[0];

    f[0] = variables[1]-variables[7]*(states[0]-variables[6])-0.0;
}

void findRoot3(double voi, double *states, double *rates, double *variables)
{
    RootFindingInfo rfi = { voi, states, rates, variables };
    double u[1];

    u[0] = variables[1];

    nlaSolve(objectiveFunction3, u, 1, &rfi);

    variables[1] = u[0];
}

void objectiveFunction4(double *u, double *f, void *data)
{
    double voi = ((RootFindingInfo *) data)->voi;
    double *states = ((RootFindingInfo *) data)->states;
    double *rates = ((RootFindingInfo *) data)->rates;
    double *variables = ((RootFindingInfo *) data)->variables;

    variables[8] = u[0];

    f[0] = variables[8]-(variables[5]-115.0)-0.0;
}

void findRoot4(double voi, double *states, double *rates, double *variables)
{
    RootFindingInfo rfi = { voi, states, rates, variables };
    double u[1];

    u[0] = variables[8];

    nlaSolve(objectiveFunction4, u, 1, &rfi);

    variables[8] = u[0];
}

void objectiveFunction5(double *u, double *f, void *data)
{
    double voi = ((RootFindingInfo *) data)->voi;
    double *states = ((RootFindingInfo *) data)->states;
    double *rates = ((RootFindingInfo *) data)->rates;
    double *variables = ((RootFindingInfo *) data)->variables;

    variables[3] = u[0];

    f[0] = variables[3]-variables[9]*pow(states[2], 3.0)*states[1]*(states[0]-variables[8])-0.0;
}

void findRoot5(double voi, double *states, double *rates, double *variables)
{
    RootFindingInfo rfi = { voi, states, rates, variables };
    double u[1];

    u[0] = variables[3];

    nlaSolve(objectiveFunction5, u, 1, &rfi);

    variables[3] = u[0];
}

void objectiveFunction6(double *u, double *f, void *data)
{
    double voi = ((RootFindingInfo *) data)->voi;
    double *states = ((RootFindingInfo *) data)->states;
    double *rates = ((RootFindingInfo *) data)->rates;
    double *variables = ((RootFindingInfo *) data)->variables;

    variables[10] = u[0];

    f[0] = variables[10]-0.1*(states[0]+25.0)/(exp((states[0]+25.0)/10.0)-1.0)-0.0;
}

void findRoot6(double voi, double *states, double *rates, double *variables)
{
    RootFindingInfo rfi = { voi, states, rates, variables };
    double u[1];

    u[0] = variables[10];

    nlaSolve(objectiveFunction6, u, 1, &rfi);

    variables[10] = u[0];
}

void objectiveFunction7(double *u, double *f, void *data)
{
    double voi = ((RootFindingInfo *) data)->voi;
    double *states = ((RootFindingInfo *) data)->states;
    double *rates = ((RootFindingInfo *) data)->rates;
    double *variables = ((RootFindingInfo *) data)->variables;

    variables[11] = u[0];

    f[0] = variables[11]-4.0*exp(states[0]/18.0)-0.0;
}

void findRoot7(double voi, double *states, double *rates, double *variables)
{
    RootFindingInfo rfi = { voi, states, rates, variables };
    double u[1];

    u[0] = variables[11];

    nlaSolve(objectiveFunction7, u, 1, &rfi);

    variables[11] = u[0];
}

void objectiveFunction8(double *u, double *f, void *data)
{
    double voi = ((RootFindingInfo *) data)->voi;
    double *states = ((RootFindingInfo *) data)->states;
    double *rates = ((RootFindingInfo *) data)->rates;
    double *variables = ((RootFindingInfo *) data)->variables;

    rates[2] = u[0];

    f[0] = rates[2]-(variables[10]*(1.0-states[2])-variables[11]*states[2])-0.0;
}

void findRoot8(double voi, double *states, double *rates, double *variables)
{
    RootFindingInfo rfi = { voi, states, rates, variables };
    double u[1];

    u[0] = rates[2];

    nlaSolve(objectiveFunction8, u, 1, &rfi);

    rates[2] = u[0];
}

void objectiveFunction9(double *u, double *f, void *data)
{
    double voi = ((RootFindingInfo *) data)->voi;
    double *states = ((RootFindingInfo *) data)->states;
    double *rates = ((RootFindingInfo *) data)->rates;
    double *variables = ((RootFindingInfo *) data)->variables;

    variables[12] = u[0];

    f[0] = variables[12]-0.07*exp(states[0]/20.0)-0.0;
}

void findRoot9(double voi, double *states, double *rates, double *variables)
{
    RootFindingInfo rfi = { voi, states, rates, variables };
    double u[1];

    u[0] = variables[12];

    nlaSolve(objectiveFunction9, u, 1, &rfi);

    variables[12] = u[0];
}

void objectiveFunction10(double *u, double *f, void *data)
{
    double voi = ((RootFindingInfo *) data)->voi;
    double *states = ((RootFindingInfo *) data)->states;
    double *rates = ((RootFindingInfo *) data)->rates;
    double *variables = ((RootFindingInfo *) data)->variables;

    variables[13] = u[0];

    f[0] = variables[13]-1.0/(exp((states[0]+30.0)/10.0)+1.0)-0.0;
}

void findRoot10(double voi, double *states, double *rates, double *variables)
{
    RootFindingInfo rfi = { voi, states, rates, variables };
    double u[1];

    u[0] = variables[13];

    nlaSolve(objectiveFunction10, u, 1, &rfi);

    variables[13] = u[0];
}

void objectiveFunction11(double *u, double *f, void *data)
{
    double voi = ((RootFindingInfo *) data)->voi;
    double *states = ((RootFindingInfo *) data)->states;
    double *rates = ((RootFindingInfo *) data)->rates;
    double *variables = ((RootFindingInfo *) data)->variables;

    rates[1] = u[0];

    f[0] = rates[1]-(variables[12]*(1.0-states[1])-variables[13]*states[1])-0.0;
}

void findRoot11(double voi, double *states, double *rates, double *variables)
{
    RootFindingInfo rfi = { voi, states, rates, variables };
    double u[1];

    u[0] = rates[1];

    nlaSolve(objectiveFunction11, u, 1, &rfi);

    rates[1] = u[0];
}

void objectiveFunction12(double *u, double *f, void *data)
{
    double voi = ((RootFindingInfo *) data)->voi;
    double *states = ((RootFindingInfo *) data)->states;
    double *rates = ((RootFindingInfo *) data)->rates;
    double *variables = ((RootFindingInfo *) data)->variables;

    variables[14] = u[0];

    f[0] = variables[14]-(variables[5]+12.0)-0.0;
}

void findRoot12(double voi, double *states, double *rates, double *variables)
{
    RootFindingInfo rfi = { voi, states, rates, variables };
    double u[1];

    u[0] = variables[14];

    nlaSolve(objectiveFunction12, u, 1, &rfi);

    variables[14] = u[0];
}

void objectiveFunction13(double *u, double *f, void *data)
{
    double voi = ((RootFindingInfo *) data)->voi;
    double *states = ((RootFindingInfo *) data)->states;
    double *rates = ((RootFindingInfo *) data)->rates;
    double *variables = ((RootFindingInfo *) data)->variables;

    variables[2] = u[0];

    f[0] = variables[2]-variables[15]*pow(states[3], 4.0)*(states[0]-variables[14])-0.0;
}

void findRoot13(double voi, double *states, double *rates, double *variables)
{
    RootFindingInfo rfi = { voi, states, rates, variables };
    double u[1];

    u[0] = variables[2];

    nlaSolve(objectiveFunction13, u, 1, &rfi);

    variables[2] = u[0];
}

void objectiveFunction14(double *u, double *f, void *data)
{
    double voi = ((RootFindingInfo *) data)->voi;
    double *states = ((RootFindingInfo *) data)->states;
    double *rates = ((RootFindingInfo *) data)->rates;
    double *variables = ((RootFindingInfo *) data)->variables;

    variables[16] = u[0];

    f[0] = variables[16]-0.01*(states[0]+10.0)/(exp((states[0]+10.0)/10.0)-1.0)-0.0;
}

void findRoot14(double voi, double *states, double *rates, double *variables)
{
    RootFindingInfo rfi = { voi, states, rates, variables };
    double u[1];

    u[0] = variables[16];

    nlaSolve(objectiveFunction14, u, 1, &rfi);

    variables[16] = u[0];
}

void objectiveFunction15(double *u, double *f, void *data)
{
    double voi = ((RootFindingInfo *) data)->voi;
    double *states = ((RootFindingInfo *) data)->states;
    double *rates = ((RootFindingInfo *) data)->rates;
    double *variables = ((RootFindingInfo *) data)->variables;

    variables[17] = u[0];

    f[0] = variables[17]-0.125*exp(states[0]/80.0)-0.0;
}

void findRoot15(double voi, double *states, double *rates, double *variables)
{
    RootFindingInfo rfi = { voi, states, rates, variables };
    double u[1];

    u[0] = variables[17];

    nlaSolve(objectiveFunction15, u, 1, &rfi);

    variables[17] = u[0];
}

void objectiveFunction16(double *u, double *f, void *data)
{
    double voi = ((RootFindingInfo *) data)->voi;
    double *states = ((RootFindingInfo *) data)->states;
    double *rates = ((RootFindingInfo *) data)->rates;
    double *variables = ((RootFindingInfo *) data)->variables;

    rates[3] = u[0];

    f[0] = rates[3]-(variables[16]*(1.0-states[3])-variables[17]*states[3])-0.0;
}

void findRoot16(double voi, double *states, double *rates, double *variables)
{
    RootFindingInfo rfi = { voi, states, rates, variables };
    double u[1];

    u[0] = rates[3];

    nlaSolve(objectiveFunction16, u, 1, &rfi);

    rates[3] = u[0];
}

void initialiseVariables(double *states, double *rates, double *constants)
{
    variables[0] = 0.0;
    variables[1] = 0.0;
    variables[2] = 0.0;
    variables[3] = 0.0;
    variables[4] = 1.0;
    variables[5] = 0.0;
    variables[6] = 0.0;
    variables[7] = 0.3;
    variables[8] = 0.0;
    variables[9] = 120.0;
    variables[10] = 0.0;
    variables[11] = 0.0;
    variables[12] = 0.0;
    variables[13] = 0.0;
    variables[14] = 0.0;
    variables[15] = 36.0;
    variables[16] = 0.0;
    variables[17] = 0.0;
    states[0] = 0.0;
    states[1] = 0.6;
    states[2] = 0.05;
    states[3] = 0.325;
    rates[0] = 0.0;
    rates[1] = 0.0;
    rates[2] = 0.0;
    rates[3] = 0.0;
}

void computeComputedConstants(double *computedConstants)
{
}

void computeRates(double voi, double *states, double *rates, double *constants, double *computedConstants, double *algebraic)
{
    findRoot0(voi, states, rates, variables);
    findRoot2(voi, states, rates, variables);
    findRoot3(voi, states, rates, variables);
    findRoot14(voi, states, rates, variables);
    findRoot15(voi, states, rates, variables);
    findRoot16(voi, states, rates, variables);
    findRoot12(voi, states, rates, variables);
    findRoot13(voi, states, rates, variables);
    findRoot9(voi, states, rates, variables);
    findRoot10(voi, states, rates, variables);
    findRoot11(voi, states, rates, variables);
    findRoot6(voi, states, rates, variables);
    findRoot7(voi, states, rates, variables);
    findRoot8(voi, states, rates, variables);
    findRoot4(voi, states, rates, variables);
    findRoot5(voi, states, rates, variables);
    findRoot1(voi, states, rates, variables);
}

void computeVariables(double voi, double *states, double *rates, double *variables)
{
    findRoot0(voi, states, rates, variables);
    findRoot2(voi, states, rates, variables);
    findRoot3(voi, states, rates, variables);
    findRoot14(voi, states, rates, variables);
    findRoot15(voi, states, rates, variables);
    findRoot16(voi, states, rates, variables);
    findRoot12(voi, states, rates, variables);
    findRoot13(voi, states, rates, variables);
    findRoot9(voi, states, rates, variables);
    findRoot10(voi, states, rates, variables);
    findRoot11(voi, states, rates, variables);
    findRoot6(voi, states, rates, variables);
    findRoot7(voi, states, rates, variables);
    findRoot8(voi, states, rates, variables);
    findRoot4(voi, states, rates, variables);
    findRoot5(voi, states, rates, variables);
    findRoot1(voi, states, rates, variables);
}

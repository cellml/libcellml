/* The content of this file was generated using the C profile of libCellML 0.6.3. */

#include "model.dae.for.tracking.untracked.constants.with.externals.h"

#include <math.h>
#include <stdlib.h>

const char VERSION[] = "0.7.0";
const char LIBCELLML_VERSION[] = "0.6.3";

const size_t STATE_COUNT = 4;
const size_t CONSTANT_COUNT = 1;
const size_t COMPUTED_CONSTANT_COUNT = 3;
const size_t ALGEBRAIC_COUNT = 12;
const size_t EXTERNAL_COUNT = 1;

const VariableInfo VOI_INFO = {"time", "millisecond", "environment"};

const VariableInfo STATE_INFO[] = {
    {"V", "millivolt", "membrane"},
    {"h", "dimensionless", "sodium_channel_h_gate"},
    {"m", "dimensionless", "sodium_channel_m_gate"},
    {"n", "dimensionless", "potassium_channel_n_gate"}
};

const VariableInfo CONSTANT_INFO[] = {
    {"Cm", "microF_per_cm2", "membrane"}
};

const VariableInfo COMPUTED_CONSTANT_INFO[] = {
    {"E_L", "millivolt", "leakage_current"},
    {"E_Na", "millivolt", "sodium_channel"},
    {"E_K", "millivolt", "potassium_channel"}
};

const VariableInfo ALGEBRAIC_INFO[] = {
    {"i_Stim", "microA_per_cm2", "membrane"},
    {"i_L", "microA_per_cm2", "leakage_current"},
    {"i_K", "microA_per_cm2", "potassium_channel"},
    {"g_L", "milliS_per_cm2", "leakage_current"},
    {"g_Na", "milliS_per_cm2", "sodium_channel"},
    {"alpha_m", "per_millisecond", "sodium_channel_m_gate"},
    {"beta_m", "per_millisecond", "sodium_channel_m_gate"},
    {"alpha_h", "per_millisecond", "sodium_channel_h_gate"},
    {"beta_h", "per_millisecond", "sodium_channel_h_gate"},
    {"g_K", "milliS_per_cm2", "potassium_channel"},
    {"alpha_n", "per_millisecond", "potassium_channel_n_gate"},
    {"beta_n", "per_millisecond", "potassium_channel_n_gate"}
};

const VariableInfo EXTERNAL_INFO[] = {
    {"i_Na", "microA_per_cm2", "sodium_channel"}
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

double * createExternalsArray()
{
    double *res = (double *) malloc(EXTERNAL_COUNT*sizeof(double));

    for (size_t i = 0; i < EXTERNAL_COUNT; ++i) {
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
    double *constants;
    double *computedConstants;
    double *algebraic;
    double *externals;
} RootFindingInfo;

extern void nlaSolve(void (*objectiveFunction)(double *, double *, void *),
                     double *u, size_t n, void *data);

void objectiveFunction0(double *u, double *f, void *data)
{
    double voi = ((RootFindingInfo *) data)->voi;
    double *states = ((RootFindingInfo *) data)->states;
    double *rates = ((RootFindingInfo *) data)->rates;
    double *constants = ((RootFindingInfo *) data)->constants;
    double *computedConstants = ((RootFindingInfo *) data)->computedConstants;
    double *algebraic = ((RootFindingInfo *) data)->algebraic;
    double *externals = ((RootFindingInfo *) data)->externals;

    algebraic[0] = u[0];

    f[0] = algebraic[0]-(((voi >= 10.0) && (voi <= 10.5))?-20.0:0.0)-0.0;
}

void findRoot0(double voi, double *states, double *rates, double *constants, double *computedConstants, double *algebraic, double *externals)
{
    RootFindingInfo rfi = { voi, states, rates, constants, computedConstants, algebraic, externals };
    double u[1];

    u[0] = algebraic[0];

    nlaSolve(objectiveFunction0, u, 1, &rfi);

    algebraic[0] = u[0];
}

void objectiveFunction1(double *u, double *f, void *data)
{
    double voi = ((RootFindingInfo *) data)->voi;
    double *states = ((RootFindingInfo *) data)->states;
    double *rates = ((RootFindingInfo *) data)->rates;
    double *constants = ((RootFindingInfo *) data)->constants;
    double *computedConstants = ((RootFindingInfo *) data)->computedConstants;
    double *algebraic = ((RootFindingInfo *) data)->algebraic;
    double *externals = ((RootFindingInfo *) data)->externals;

    rates[0] = u[0];

    f[0] = rates[0]-(-(-algebraic[0]+externals[0]+algebraic[2]+algebraic[1])/constants[0])-0.0;
}

void findRoot1(double voi, double *states, double *rates, double *constants, double *computedConstants, double *algebraic, double *externals)
{
    RootFindingInfo rfi = { voi, states, rates, constants, computedConstants, algebraic, externals };
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
    double *constants = ((RootFindingInfo *) data)->constants;
    double *computedConstants = ((RootFindingInfo *) data)->computedConstants;
    double *algebraic = ((RootFindingInfo *) data)->algebraic;
    double *externals = ((RootFindingInfo *) data)->externals;

    algebraic[3] = u[0];
    algebraic[1] = u[1];

    f[0] = algebraic[1]-algebraic[3]*(states[0]-computedConstants[0])-0.0;
}

void findRoot2(double voi, double *states, double *rates, double *constants, double *computedConstants, double *algebraic, double *externals)
{
    RootFindingInfo rfi = { voi, states, rates, constants, computedConstants, algebraic, externals };
    double u[2];

    u[0] = algebraic[3];
    u[1] = algebraic[1];

    nlaSolve(objectiveFunction2, u, 2, &rfi);

    algebraic[3] = u[0];
    algebraic[1] = u[1];
}

void objectiveFunction3(double *u, double *f, void *data)
{
    double voi = ((RootFindingInfo *) data)->voi;
    double *states = ((RootFindingInfo *) data)->states;
    double *rates = ((RootFindingInfo *) data)->rates;
    double *constants = ((RootFindingInfo *) data)->constants;
    double *computedConstants = ((RootFindingInfo *) data)->computedConstants;
    double *algebraic = ((RootFindingInfo *) data)->algebraic;
    double *externals = ((RootFindingInfo *) data)->externals;

    algebraic[4] = u[0];

    f[0] = externals[0]-algebraic[4]*pow(states[2], 3.0)*states[1]*(states[0]-computedConstants[1])-0.0;
}

void findRoot3(double voi, double *states, double *rates, double *constants, double *computedConstants, double *algebraic, double *externals)
{
    RootFindingInfo rfi = { voi, states, rates, constants, computedConstants, algebraic, externals };
    double u[1];

    u[0] = algebraic[4];

    nlaSolve(objectiveFunction3, u, 1, &rfi);

    algebraic[4] = u[0];
}

void objectiveFunction4(double *u, double *f, void *data)
{
    double voi = ((RootFindingInfo *) data)->voi;
    double *states = ((RootFindingInfo *) data)->states;
    double *rates = ((RootFindingInfo *) data)->rates;
    double *constants = ((RootFindingInfo *) data)->constants;
    double *computedConstants = ((RootFindingInfo *) data)->computedConstants;
    double *algebraic = ((RootFindingInfo *) data)->algebraic;
    double *externals = ((RootFindingInfo *) data)->externals;

    algebraic[6] = u[0];

    f[0] = algebraic[6]-4.0*exp(states[0]/18.0)-0.0;
}

void findRoot4(double voi, double *states, double *rates, double *constants, double *computedConstants, double *algebraic, double *externals)
{
    RootFindingInfo rfi = { voi, states, rates, constants, computedConstants, algebraic, externals };
    double u[1];

    u[0] = algebraic[6];

    nlaSolve(objectiveFunction4, u, 1, &rfi);

    algebraic[6] = u[0];
}

void objectiveFunction5(double *u, double *f, void *data)
{
    double voi = ((RootFindingInfo *) data)->voi;
    double *states = ((RootFindingInfo *) data)->states;
    double *rates = ((RootFindingInfo *) data)->rates;
    double *constants = ((RootFindingInfo *) data)->constants;
    double *computedConstants = ((RootFindingInfo *) data)->computedConstants;
    double *algebraic = ((RootFindingInfo *) data)->algebraic;
    double *externals = ((RootFindingInfo *) data)->externals;

    rates[2] = u[0];

    f[0] = rates[2]-(algebraic[5]*(1.0-states[2])-algebraic[6]*states[2])-0.0;
}

void findRoot5(double voi, double *states, double *rates, double *constants, double *computedConstants, double *algebraic, double *externals)
{
    RootFindingInfo rfi = { voi, states, rates, constants, computedConstants, algebraic, externals };
    double u[1];

    u[0] = rates[2];

    nlaSolve(objectiveFunction5, u, 1, &rfi);

    rates[2] = u[0];
}

void objectiveFunction6(double *u, double *f, void *data)
{
    double voi = ((RootFindingInfo *) data)->voi;
    double *states = ((RootFindingInfo *) data)->states;
    double *rates = ((RootFindingInfo *) data)->rates;
    double *constants = ((RootFindingInfo *) data)->constants;
    double *computedConstants = ((RootFindingInfo *) data)->computedConstants;
    double *algebraic = ((RootFindingInfo *) data)->algebraic;
    double *externals = ((RootFindingInfo *) data)->externals;

    algebraic[7] = u[0];

    f[0] = algebraic[7]-0.07*exp(states[0]/20.0)-0.0;
}

void findRoot6(double voi, double *states, double *rates, double *constants, double *computedConstants, double *algebraic, double *externals)
{
    RootFindingInfo rfi = { voi, states, rates, constants, computedConstants, algebraic, externals };
    double u[1];

    u[0] = algebraic[7];

    nlaSolve(objectiveFunction6, u, 1, &rfi);

    algebraic[7] = u[0];
}

void objectiveFunction7(double *u, double *f, void *data)
{
    double voi = ((RootFindingInfo *) data)->voi;
    double *states = ((RootFindingInfo *) data)->states;
    double *rates = ((RootFindingInfo *) data)->rates;
    double *constants = ((RootFindingInfo *) data)->constants;
    double *computedConstants = ((RootFindingInfo *) data)->computedConstants;
    double *algebraic = ((RootFindingInfo *) data)->algebraic;
    double *externals = ((RootFindingInfo *) data)->externals;

    algebraic[8] = u[0];

    f[0] = algebraic[8]-1.0/(exp((states[0]+30.0)/10.0)+1.0)-0.0;
}

void findRoot7(double voi, double *states, double *rates, double *constants, double *computedConstants, double *algebraic, double *externals)
{
    RootFindingInfo rfi = { voi, states, rates, constants, computedConstants, algebraic, externals };
    double u[1];

    u[0] = algebraic[8];

    nlaSolve(objectiveFunction7, u, 1, &rfi);

    algebraic[8] = u[0];
}

void objectiveFunction8(double *u, double *f, void *data)
{
    double voi = ((RootFindingInfo *) data)->voi;
    double *states = ((RootFindingInfo *) data)->states;
    double *rates = ((RootFindingInfo *) data)->rates;
    double *constants = ((RootFindingInfo *) data)->constants;
    double *computedConstants = ((RootFindingInfo *) data)->computedConstants;
    double *algebraic = ((RootFindingInfo *) data)->algebraic;
    double *externals = ((RootFindingInfo *) data)->externals;

    rates[1] = u[0];

    f[0] = rates[1]-(algebraic[7]*(1.0-states[1])-algebraic[8]*states[1])-0.0;
}

void findRoot8(double voi, double *states, double *rates, double *constants, double *computedConstants, double *algebraic, double *externals)
{
    RootFindingInfo rfi = { voi, states, rates, constants, computedConstants, algebraic, externals };
    double u[1];

    u[0] = rates[1];

    nlaSolve(objectiveFunction8, u, 1, &rfi);

    rates[1] = u[0];
}

void objectiveFunction9(double *u, double *f, void *data)
{
    double voi = ((RootFindingInfo *) data)->voi;
    double *states = ((RootFindingInfo *) data)->states;
    double *rates = ((RootFindingInfo *) data)->rates;
    double *constants = ((RootFindingInfo *) data)->constants;
    double *computedConstants = ((RootFindingInfo *) data)->computedConstants;
    double *algebraic = ((RootFindingInfo *) data)->algebraic;
    double *externals = ((RootFindingInfo *) data)->externals;

    algebraic[9] = u[0];
    algebraic[2] = u[1];

    f[0] = algebraic[2]-algebraic[9]*pow(states[3], 4.0)*(states[0]-computedConstants[2])-0.0;
}

void findRoot9(double voi, double *states, double *rates, double *constants, double *computedConstants, double *algebraic, double *externals)
{
    RootFindingInfo rfi = { voi, states, rates, constants, computedConstants, algebraic, externals };
    double u[2];

    u[0] = algebraic[9];
    u[1] = algebraic[2];

    nlaSolve(objectiveFunction9, u, 2, &rfi);

    algebraic[9] = u[0];
    algebraic[2] = u[1];
}

void objectiveFunction10(double *u, double *f, void *data)
{
    double voi = ((RootFindingInfo *) data)->voi;
    double *states = ((RootFindingInfo *) data)->states;
    double *rates = ((RootFindingInfo *) data)->rates;
    double *constants = ((RootFindingInfo *) data)->constants;
    double *computedConstants = ((RootFindingInfo *) data)->computedConstants;
    double *algebraic = ((RootFindingInfo *) data)->algebraic;
    double *externals = ((RootFindingInfo *) data)->externals;

    algebraic[10] = u[0];

    f[0] = algebraic[10]-0.01*(states[0]+10.0)/(exp((states[0]+10.0)/10.0)-1.0)-0.0;
}

void findRoot10(double voi, double *states, double *rates, double *constants, double *computedConstants, double *algebraic, double *externals)
{
    RootFindingInfo rfi = { voi, states, rates, constants, computedConstants, algebraic, externals };
    double u[1];

    u[0] = algebraic[10];

    nlaSolve(objectiveFunction10, u, 1, &rfi);

    algebraic[10] = u[0];
}

void objectiveFunction11(double *u, double *f, void *data)
{
    double voi = ((RootFindingInfo *) data)->voi;
    double *states = ((RootFindingInfo *) data)->states;
    double *rates = ((RootFindingInfo *) data)->rates;
    double *constants = ((RootFindingInfo *) data)->constants;
    double *computedConstants = ((RootFindingInfo *) data)->computedConstants;
    double *algebraic = ((RootFindingInfo *) data)->algebraic;
    double *externals = ((RootFindingInfo *) data)->externals;

    algebraic[11] = u[0];

    f[0] = algebraic[11]-0.125*exp(states[0]/80.0)-0.0;
}

void findRoot11(double voi, double *states, double *rates, double *constants, double *computedConstants, double *algebraic, double *externals)
{
    RootFindingInfo rfi = { voi, states, rates, constants, computedConstants, algebraic, externals };
    double u[1];

    u[0] = algebraic[11];

    nlaSolve(objectiveFunction11, u, 1, &rfi);

    algebraic[11] = u[0];
}

void objectiveFunction12(double *u, double *f, void *data)
{
    double voi = ((RootFindingInfo *) data)->voi;
    double *states = ((RootFindingInfo *) data)->states;
    double *rates = ((RootFindingInfo *) data)->rates;
    double *constants = ((RootFindingInfo *) data)->constants;
    double *computedConstants = ((RootFindingInfo *) data)->computedConstants;
    double *algebraic = ((RootFindingInfo *) data)->algebraic;
    double *externals = ((RootFindingInfo *) data)->externals;

    rates[3] = u[0];

    f[0] = rates[3]-(algebraic[10]*(1.0-states[3])-algebraic[11]*states[3])-0.0;
}

void findRoot12(double voi, double *states, double *rates, double *constants, double *computedConstants, double *algebraic, double *externals)
{
    RootFindingInfo rfi = { voi, states, rates, constants, computedConstants, algebraic, externals };
    double u[1];

    u[0] = rates[3];

    nlaSolve(objectiveFunction12, u, 1, &rfi);

    rates[3] = u[0];
}

void initialiseVariables(double *states, double *rates, double *constants, double *computedConstants, double *algebraic)
{
    states[0] = 0.0;
    states[1] = 0.6;
    states[2] = 0.05;
    states[3] = 0.325;
    rates[0] = 0.0;
    rates[1] = 0.0;
    rates[2] = 0.0;
    rates[3] = 0.0;
    constants[0] = 1.0;
    algebraic[0] = 0.0;
    algebraic[1] = 0.0;
    algebraic[2] = 0.0;
    algebraic[3] = 0.3;
    algebraic[4] = 120.0;
    algebraic[6] = 0.0;
    algebraic[7] = 0.0;
    algebraic[8] = 0.0;
    algebraic[9] = 36.0;
    algebraic[10] = 0.0;
    algebraic[11] = 0.0;
}

void computeComputedConstants(double *states, double *rates, double *constants, double *computedConstants, double *algebraic)
{
    double membrane_E_R = 0.0;
    computedConstants[0] = membrane_E_R-10.613;
    computedConstants[1] = membrane_E_R-115.0;
    computedConstants[2] = membrane_E_R+12.0;
}

void computeRates(double voi, double *states, double *rates, double *constants, double *computedConstants, double *algebraic, double *externals, ExternalVariable externalVariable)
{
    findRoot2(voi, states, rates, constants, computedConstants, algebraic, externals);
    findRoot11(voi, states, rates, constants, computedConstants, algebraic, externals);
    findRoot10(voi, states, rates, constants, computedConstants, algebraic, externals);
    findRoot12(voi, states, rates, constants, computedConstants, algebraic, externals);
    findRoot9(voi, states, rates, constants, computedConstants, algebraic, externals);
    algebraic[5] = 0.1*(states[0]+25.0)/(exp((states[0]+25.0)/10.0)-1.0);
    externals[0] = externalVariable(voi, states, rates, constants, computedConstants, algebraic, externals, 0);
    findRoot0(voi, states, rates, constants, computedConstants, algebraic, externals);
    findRoot1(voi, states, rates, constants, computedConstants, algebraic, externals);
    findRoot4(voi, states, rates, constants, computedConstants, algebraic, externals);
    findRoot5(voi, states, rates, constants, computedConstants, algebraic, externals);
    findRoot7(voi, states, rates, constants, computedConstants, algebraic, externals);
    findRoot6(voi, states, rates, constants, computedConstants, algebraic, externals);
    findRoot8(voi, states, rates, constants, computedConstants, algebraic, externals);
}

void computeVariables(double voi, double *states, double *rates, double *constants, double *computedConstants, double *algebraic, double *externals, ExternalVariable externalVariable)
{
    findRoot2(voi, states, rates, constants, computedConstants, algebraic, externals);
    findRoot11(voi, states, rates, constants, computedConstants, algebraic, externals);
    findRoot10(voi, states, rates, constants, computedConstants, algebraic, externals);
    findRoot12(voi, states, rates, constants, computedConstants, algebraic, externals);
    findRoot9(voi, states, rates, constants, computedConstants, algebraic, externals);
    algebraic[5] = 0.1*(states[0]+25.0)/(exp((states[0]+25.0)/10.0)-1.0);
    externals[0] = externalVariable(voi, states, rates, constants, computedConstants, algebraic, externals, 0);
    findRoot1(voi, states, rates, constants, computedConstants, algebraic, externals);
    findRoot7(voi, states, rates, constants, computedConstants, algebraic, externals);
    findRoot6(voi, states, rates, constants, computedConstants, algebraic, externals);
    findRoot8(voi, states, rates, constants, computedConstants, algebraic, externals);
    findRoot4(voi, states, rates, constants, computedConstants, algebraic, externals);
    findRoot5(voi, states, rates, constants, computedConstants, algebraic, externals);
    findRoot3(voi, states, rates, constants, computedConstants, algebraic, externals);
}

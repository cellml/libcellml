/* The content of this file was generated using the C profile of libCellML 0.5.0. */

#include "model.h"

#include <math.h>
#include <stdlib.h>

const char VERSION[] = "0.6.0";
const char LIBCELLML_VERSION[] = "0.5.0";

const size_t STATE_COUNT = 2;
const size_t CONSTANT_COUNT = 5;
const size_t COMPUTED_CONSTANT_COUNT = 0;
const size_t ALGEBRAIC_COUNT = 5;

const VariableInfo VOI_INFO = {"t", "second", "main"};

const VariableInfo STATE_INFO[] = {
    {"q_1", "coulomb", "main"},
    {"v_3", "C_per_s", "main"}
};

const VariableInfo CONSTANT_INFO[] = {
    {"v_in", "C_per_s", "main"},
    {"v_out", "C_per_s", "main"},
    {"C", "C2_per_J", "main"},
    {"R", "Js_per_C2", "main"},
    {"L", "Js2_per_C2", "main"}
};

const VariableInfo COMPUTED_CONSTANT_INFO[] = {
};

const VariableInfo ALGEBRAIC_INFO[] = {
    {"v_1", "C_per_s", "main"},
    {"v_2", "C_per_s", "main"},
    {"u_1", "J_per_C", "main"},
    {"u_2", "J_per_C", "main"},
    {"u_3", "J_per_C", "main"}
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

typedef struct {
    double voi;
    double *states;
    double *rates;
    double *constants;
    double *computedConstants;
    double *algebraic;
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

    algebraic[0] = u[0];

    f[0] = constants[0]-(algebraic[0]+algebraic[1]);
}

void findRoot0(double voi, double *states, double *rates, double *constants, double *computedConstants, double *algebraic)
{
    RootFindingInfo rfi = { voi, states, rates, constants, computedConstants, algebraic };
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

    algebraic[4] = u[0];

    f[0] = algebraic[2]-(algebraic[3]+algebraic[4]);
}

void findRoot1(double voi, double *states, double *rates, double *constants, double *computedConstants, double *algebraic)
{
    RootFindingInfo rfi = { voi, states, rates, constants, computedConstants, algebraic };
    double u[1];

    u[0] = algebraic[4];

    nlaSolve(objectiveFunction1, u, 1, &rfi);

    algebraic[4] = u[0];
}

void initialiseVariables(double *states, double *rates, double *constants, double *computedConstants, double *algebraic)
{
    states[0] = 1.0;
    states[1] = 0.0;
    constants[0] = 1.0;
    constants[1] = 1.0;
    constants[2] = 20.0;
    constants[3] = 2.0;
    constants[4] = 10.0;
    algebraic[0] = 0.0;
    algebraic[4] = 0.0;
}

void computeComputedConstants(double *constants, double *computedConstants)
{
}

void computeRates(double voi, double *states, double *rates, double *constants, double *computedConstants, double *algebraic)
{
    algebraic[1] = states[1]+constants[1];
    findRoot0(voi, states, rates, constants, computedConstants, algebraic);
    rates[0] = algebraic[0];
    algebraic[2] = states[0]/constants[2];
    algebraic[3] = constants[3]*algebraic[1];
    findRoot1(voi, states, rates, constants, computedConstants, algebraic);
    rates[1] = algebraic[4]/constants[4];
}

void computeVariables(double voi, double *states, double *rates, double *constants, double *computedConstants, double *algebraic)
{
    algebraic[1] = states[1]+constants[1];
    findRoot0(voi, states, rates, constants, computedConstants, algebraic);
    algebraic[2] = states[0]/constants[2];
    algebraic[3] = constants[3]*algebraic[1];
    findRoot1(voi, states, rates, constants, computedConstants, algebraic);
}

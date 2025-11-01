/* The content of this file was generated using the C profile of libCellML 0.6.3. */

#include "model.dae.h"

#include <math.h>
#include <stdlib.h>

const char VERSION[] = "0.7.0";
const char LIBCELLML_VERSION[] = "0.6.3";

const size_t STATE_COUNT = 2;
const size_t CONSTANT_COUNT = 3;
const size_t COMPUTED_CONSTANT_COUNT = 0;
const size_t ALGEBRAIC_COUNT = 2;

const VariableInfo VOI_INFO = {"t", "dimensionless", "main"};

const VariableInfo STATE_INFO[] = {
    {"y2", "dimensionless", "main"},
    {"y1", "dimensionless", "main"}
};

const VariableInfo CONSTANT_INFO[] = {
    {"k3", "dimensionless", "main"},
    {"k1", "dimensionless", "main"},
    {"k2", "dimensionless", "main"}
};

const VariableInfo COMPUTED_CONSTANT_INFO[] = {
};

const VariableInfo ALGEBRAIC_INFO[] = {
    {"y3", "dimensionless", "main"},
    {"y2_scaled", "dimensionless", "main"}
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

    f[0] = 1.0-(states[1]+states[0]+algebraic[0]);
}

void findRoot0(double voi, double *states, double *rates, double *constants, double *computedConstants, double *algebraic)
{
    RootFindingInfo rfi = { voi, states, rates, constants, computedConstants, algebraic };
    double u[1];

    u[0] = algebraic[0];

    nlaSolve(objectiveFunction0, u, 1, &rfi);

    algebraic[0] = u[0];
}

void initialiseVariables(double *states, double *rates, double *constants, double *computedConstants, double *algebraic)
{
    states[0] = 0.0;
    states[1] = 1.0;
    constants[0] = 1.0e4;
    constants[1] = 0.04;
    constants[2] = 3.0e7;
    algebraic[0] = 0.0;
}

void computeComputedConstants(double *states, double *rates, double *constants, double *computedConstants, double *algebraic)
{
}

void computeRates(double voi, double *states, double *rates, double *constants, double *computedConstants, double *algebraic)
{
    findRoot0(voi, states, rates, constants, computedConstants, algebraic);
    rates[1] = -constants[1]*states[1]+constants[0]*states[0]*algebraic[0];
    rates[0] = constants[1]*states[1]-constants[2]*pow(states[0], 2.0)-constants[0]*states[0]*algebraic[0];
}

void computeVariables(double voi, double *states, double *rates, double *constants, double *computedConstants, double *algebraic)
{
    findRoot0(voi, states, rates, constants, computedConstants, algebraic);
    algebraic[1] = 10000.0*states[0];
}

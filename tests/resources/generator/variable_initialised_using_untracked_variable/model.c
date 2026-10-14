/* The content of this file was generated using the C profile of libCellML 0.7.1. */

#include "model.h"

#include <math.h>
#include <stdlib.h>

const char VERSION[] = "0.8.0";
const char LIBCELLML_VERSION[] = "0.7.1";

const size_t STATE_COUNT = 3;
const size_t CONSTANT_COUNT = 0;
const size_t COMPUTED_CONSTANT_COUNT = 0;
const size_t ALGEBRAIC_VARIABLE_COUNT = 1;

const VariableInfo VOI_INFO = {"t", "dimensionless", "main"};

const VariableInfo STATE_INFO[] = {
    {"x", "dimensionless", "main"},
    {"y", "dimensionless", "main"},
    {"z", "dimensionless", "main"}
};

const VariableInfo CONSTANT_INFO[] = {
};

const VariableInfo COMPUTED_CONSTANT_INFO[] = {
};

const VariableInfo ALGEBRAIC_VARIABLE_INFO[] = {
    {"a", "dimensionless", "main"}
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

double * createAlgebraicVariablesArray()
{
    double *res = (double *) malloc(ALGEBRAIC_VARIABLE_COUNT*sizeof(double));

    for (size_t i = 0; i < ALGEBRAIC_VARIABLE_COUNT; ++i) {
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
    double *algebraicVariables;
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
    double *algebraicVariables = ((RootFindingInfo *) data)->algebraicVariables;

    algebraicVariables[0] = u[0];

    double main_q = 3.0;
    double main_k = main_q;

    f[0] = algebraicVariables[0]+sin(algebraicVariables[0])-(main_q+main_k);
}

void findRoot0(double voi, double *states, double *rates, double *constants, double *computedConstants, double *algebraicVariables)
{
    RootFindingInfo rfi = { voi, states, rates, constants, computedConstants, algebraicVariables };
    double u[1];

    u[0] = algebraicVariables[0];

    nlaSolve(objectiveFunction0, u, 1, &rfi);

    algebraicVariables[0] = u[0];
}

void initialiseArrays(double *states, double *rates, double *constants, double *computedConstants, double *algebraicVariables)
{
    double main_q = 3.0;
    double main_k = main_q;
    states[0] = main_k;
    states[1] = main_k;
    algebraicVariables[0] = 0.0;
}

void computeComputedConstants(double voi, double *states, double *rates, double *constants, double *computedConstants, double *algebraicVariables)
{
    double main_q = 3.0;
    double main_k = main_q;
    double main_cc = 2.0*main_k;
    states[2] = main_cc;
}

void computeRates(double voi, double *states, double *rates, double *constants, double *computedConstants, double *algebraicVariables)
{
    double main_q = 3.0;
    double main_k = main_q;
    rates[0] = main_q+main_k;
    double main_cc = 2.0*main_k;
    double main_kc = main_cc;
    rates[1] = main_cc+main_kc;
    findRoot0(voi, states, rates, constants, computedConstants, algebraicVariables);
    rates[2] = algebraicVariables[0];
}

void computeVariables(double voi, double *states, double *rates, double *constants, double *computedConstants, double *algebraicVariables)
{
}

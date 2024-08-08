/* The content of this file was generated using the C profile of libCellML 0.5.0. */

#include "model.dae.h"

#include <math.h>
#include <stdlib.h>

const char VERSION[] = "0.6.0";
const char LIBCELLML_VERSION[] = "0.5.0";

const size_t STATE_COUNT = 2;
const size_t CONSTANT_COUNT = 0;
const size_t COMPUTED_CONSTANT_COUNT = 0;
const size_t ALGEBRAIC_COUNT = 5;
const size_t EXTERNAL_COUNT = 0;

const VariableInfo VOI_INFO = {"t", "dimensionless", "main", VARIABLE_OF_INTEGRATION};

const VariableInfo STATE_INFO[] = {
    {"y1", "dimensionless", "main", STATE},
    {"y2", "dimensionless", "main", STATE}
};

const VariableInfo VARIABLE_INFO[] = {
    {"k1", "dimensionless", "main", CONSTANT},
    {"k3", "dimensionless", "main", CONSTANT},
    {"y3", "dimensionless", "main", ALGEBRAIC},
    {"k2", "dimensionless", "main", CONSTANT},
    {"y2_scaled", "dimensionless", "main", ALGEBRAIC}
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

    algebraic[0] = u[0];

    f[0] = 1.0-(states[0]+states[1]+algebraic[0]);
}

void findRoot0(double voi, double *states, double *rates, double *variables)
{
    RootFindingInfo rfi = { voi, states, rates, variables };
    double u[1];

    u[0] = algebraic[0];

    nlaSolve(objectiveFunction0, u, 1, &rfi);

    algebraic[0] = u[0];
}

void initialiseVariables(double *states, double *rates, double *constants)
{
    constants[0] = 0.04;
    constants[1] = 1.0e4;
    algebraic[0] = 0.0;
    constants[2] = 3.0e7;
    states[0] = 1.0;
    states[1] = 0.0;
}

void computeComputedConstants(double *constants, double *computedConstants)
{
}

void computeRates(double voi, double *states, double *rates, double *constants, double *computedConstants, double *algebraic)
{
    findRoot0(voi, states, rates, variables);
    rates[0] = -constants[0]*states[0]+constants[1]*states[1]*algebraic[0];
    rates[1] = constants[0]*states[0]-constants[2]*pow(states[1], 2.0)-constants[1]*states[1]*algebraic[0];
}

void computeVariables(double voi, double *states, double *rates, double *constants, double *computedConstants, double *algebraic)
{
    findRoot0(voi, states, rates, variables);
    algebraic[1] = 10000.0*states[1];
}

/* The content of this file was generated using the C profile of libCellML 0.5.0. */

#include "model.dae.h"

#include <math.h>
#include <stdlib.h>

const char VERSION[] = "0.4.0";
const char LIBCELLML_VERSION[] = "0.5.0";

const size_t STATE_COUNT = 2;
const size_t VARIABLE_COUNT = 5;

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
                     double *u, int n, void *data);

void objectiveFunction0(double *u, double *f, void *data)
{
    double voi = ((RootFindingInfo *) data)->voi;
    double *states = ((RootFindingInfo *) data)->states;
    double *rates = ((RootFindingInfo *) data)->rates;
    double *variables = ((RootFindingInfo *) data)->variables;

    variables[2] = u[0];

    f[0] = 1.0-(states[0]+states[1]+variables[2]);
}

void findRoot0(double voi, double *states, double *rates, double *variables)
{
    RootFindingInfo rfi = { voi, states, rates, variables };
    double u[1];

    u[0] = variables[2];

    nlaSolve(objectiveFunction0, u, 1, &rfi);

    variables[2] = u[0];
}

void initialiseVariables(double *states, double *rates, double *variables)
{
    variables[0] = 0.04;
    variables[1] = 1.0e4;
    variables[2] = 0.0;
    variables[3] = 3.0e7;
    states[0] = 1.0;
    states[1] = 0.0;
}

void computeComputedConstants(double *variables)
{
}

void computeRates(double voi, double *states, double *rates, double *variables)
{
    findRoot0(voi, states, rates, variables);
    rates[0] = -variables[0]*states[0]+variables[1]*states[1]*variables[2];
    rates[1] = variables[0]*states[0]-variables[3]*pow(states[1], 2.0)-variables[1]*states[1]*variables[2];
}

void computeVariables(double voi, double *states, double *rates, double *variables)
{
    findRoot0(voi, states, rates, variables);
    variables[4] = 10000.0*states[1];
}

/* The content of this file was generated using the C profile of libCellML 0.4.0. */

#include "ode.model.h"

#include <math.h>
#include <stdlib.h>

const char VERSION[] = "0.3.2";
const char LIBCELLML_VERSION[] = "0.4.0";

const size_t STATE_COUNT = 3;
const size_t VARIABLE_COUNT = 3;

const VariableInfo VOI_INFO = {"t", "dimensionless", "main", VARIABLE_OF_INTEGRATION};

const VariableInfo STATE_INFO[] = {
    {"y1", "dimensionless", "main", STATE},
    {"y3", "dimensionless", "main", STATE},
    {"y2", "dimensionless", "main", STATE}
};

const VariableInfo VARIABLE_INFO[] = {
    {"k1", "dimensionless", "main", CONSTANT},
    {"k3", "dimensionless", "main", CONSTANT},
    {"k2", "dimensionless", "main", CONSTANT}
};

double * createStatesArray()
{
    return (double *) malloc(STATE_COUNT*sizeof(double));
}

double * createVariablesArray()
{
    return (double *) malloc(VARIABLE_COUNT*sizeof(double));
}

void deleteArray(double *array)
{
    free(array);
}

typedef struct {
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

    variables[3] = u[0];

    f[0] = 1.0-(states[0]+states[1]+variables[3]);
}

void findRoot0(double voi, double *states, double *rates, double *variables)
{
    RootFindingInfo rfi = { voi, states, rates, variables };
    double u[1];

    u[0] = variables[3];

    nlaSolve(objectiveFunction0, u, 1, &rfi);

    variables[3] = u[0];
}

void initialiseVariables(double *states, double *variables)
{
    variables[0] = 0.04;
    variables[1] = 1.0e4;
    variables[2] = 3.0e7;
    variables[3] = 0.0;
    states[0] = 1.0;
    states[1] = 0.0;
}

void computeComputedConstants(double *variables)
{
}

void computeRates(double voi, double *states, double *rates, double *variables)
{
    findRoot0(voi, states, rates, variables);
    rates[0] = -variables[0]*states[0]+variables[1]*states[2]*states[1];
    rates[2] = variables[0]*states[0]-variables[2]*pow(states[2], 2.0)-variables[1]*states[2]*states[1];
}

void computeVariables(double voi, double *states, double *rates, double *variables)
{
    findRoot0(voi, states, rates, variables);
}

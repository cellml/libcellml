/* The content of this file was generated using the C profile of libCellML 0.5.0. */

#include "model.h"

#include <math.h>
#include <stdlib.h>

const char VERSION[] = "0.6.0";
const char LIBCELLML_VERSION[] = "0.5.0";

const size_t CONSTANT_COUNT = 0;
const size_t COMPUTED_CONSTANT_COUNT = 3;
const size_t ALGEBRAIC_COUNT = 1;

const VariableInfo VARIABLE_INFO[] = {
    {"b", "dimensionless", "my_algebraic_eqn", COMPUTED_CONSTANT},
    {"c", "dimensionless", "my_algebraic_eqn", COMPUTED_CONSTANT},
    {"d", "dimensionless", "my_algebraic_eqn", COMPUTED_CONSTANT},
    {"a", "dimensionless", "my_algebraic_eqn", ALGEBRAIC}
};

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
    double *variables;
} RootFindingInfo;

extern void nlaSolve(void (*objectiveFunction)(double *, double *, void *),
                     double *u, size_t n, void *data);

void objectiveFunction0(double *u, double *f, void *data)
{
    double *variables = ((RootFindingInfo *) data)->variables;

    algebraic[0] = u[0];

    f[0] = algebraic[0]+computedConstants[0]-(computedConstants[1]+computedConstants[2]);
}

void findRoot0(double *variables)
{
    RootFindingInfo rfi = { variables };
    double u[1];

    u[0] = algebraic[0];

    nlaSolve(objectiveFunction0, u, 1, &rfi);

    algebraic[0] = u[0];
}

void initialiseVariables(double *constants)
{
    algebraic[0] = 1.0;
    computedConstants[0] = 3.0;
    computedConstants[1] = 5.0;
    computedConstants[2] = 7.0;
}

void computeComputedConstants(double *constants, double *computedConstants)
{
}

void computeVariables(double *constants, double *computedConstants, double *algebraic)
{
    findRoot0(variables);
}

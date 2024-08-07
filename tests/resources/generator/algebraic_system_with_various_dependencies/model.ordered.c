/* The content of this file was generated using the C profile of libCellML 0.5.0. */

#include "model.ordered.h"

#include <math.h>
#include <stdlib.h>

const char VERSION[] = "0.6.0";
const char LIBCELLML_VERSION[] = "0.5.0";

const size_t CONSTANT_COUNT = 0;
const size_t COMPUTED_CONSTANT_COUNT = 0;
const size_t ALGEBRAIC_COUNT = 6;

const VariableInfo VARIABLE_INFO[] = {
    {"a", "dimensionless", "my_algebraic_system", COMPUTED_CONSTANT},
    {"x", "dimensionless", "my_algebraic_system", CONSTANT},
    {"y", "dimensionless", "my_algebraic_system", CONSTANT},
    {"c", "dimensionless", "my_algebraic_system", ALGEBRAIC},
    {"b", "dimensionless", "my_algebraic_system", ALGEBRAIC},
    {"d", "dimensionless", "my_algebraic_system", ALGEBRAIC}
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

    algebraic[3] = u[0];
    algebraic[4] = u[1];

    f[0] = 3.0*computedConstants[0]+2.0*algebraic[4]+algebraic[3]-57.0;
    f[1] = computedConstants[0]+3.0*algebraic[4]-algebraic[3]-19.0;
}

void findRoot0(double *variables)
{
    RootFindingInfo rfi = { variables };
    double u[2];

    u[0] = algebraic[3];
    u[1] = algebraic[4];

    nlaSolve(objectiveFunction0, u, 2, &rfi);

    algebraic[3] = u[0];
    algebraic[4] = u[1];
}

void initialiseVariables(double *constants)
{
    constants[1] = 3.0;
    constants[2] = 5.0;
    algebraic[3] = 1.0;
    algebraic[4] = 1.0;
}

void computeComputedConstants(double *constants, double *computedConstants)
{
    computedConstants[0] = 3.0*constants[1]+constants[2];
}

void computeVariables(double *constants, double *computedConstants, double *algebraic)
{
    findRoot0(variables);
    algebraic[5] = algebraic[4]+algebraic[3];
}

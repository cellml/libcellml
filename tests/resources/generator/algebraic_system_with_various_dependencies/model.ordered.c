/* The content of this file was generated using the C profile of libCellML 0.5.0. */

#include "model.ordered.h"

#include <math.h>
#include <stdlib.h>

const char VERSION[] = "0.6.0";
const char LIBCELLML_VERSION[] = "0.5.0";

const size_t CONSTANT_COUNT = 2;
const size_t COMPUTED_CONSTANT_COUNT = 1;
const size_t ALGEBRAIC_COUNT = 3;

const VariableInfo CONSTANT_INFO[] = {
    {"x", "dimensionless", "my_algebraic_system", CONSTANT},
    {"y", "dimensionless", "my_algebraic_system", CONSTANT}
};

const VariableInfo COMPUTED_CONSTANT_INFO[] = {
    {"a", "dimensionless", "my_algebraic_system", COMPUTED_CONSTANT}
};

const VariableInfo ALGEBRAIC_INFO[] = {
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

    algebraic[0] = u[0];
    algebraic[1] = u[1];

    f[0] = 3.0*computedConstants[0]+2.0*algebraic[1]+algebraic[0]-57.0;
    f[1] = computedConstants[0]+3.0*algebraic[1]-algebraic[0]-19.0;
}

void findRoot0(double *variables)
{
    RootFindingInfo rfi = { variables };
    double u[2];

    u[0] = algebraic[0];
    u[1] = algebraic[1];

    nlaSolve(objectiveFunction0, u, 2, &rfi);

    algebraic[0] = u[0];
    algebraic[1] = u[1];
}

void initialiseVariables(double *constants)
{
    constants[0] = 3.0;
    constants[1] = 5.0;
    algebraic[0] = 1.0;
    algebraic[1] = 1.0;
}

void computeComputedConstants(double *constants, double *computedConstants)
{
    computedConstants[0] = 3.0*constants[0]+constants[1];
}

void computeVariables(double *constants, double *computedConstants, double *algebraic)
{
    findRoot0(variables);
    algebraic[2] = algebraic[1]+algebraic[0];
}

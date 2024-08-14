/* The content of this file was generated using the C profile of libCellML 0.5.0. */

#include "model.not.ordered.h"

#include <math.h>
#include <stdlib.h>

const char VERSION[] = "0.6.0";
const char LIBCELLML_VERSION[] = "0.5.0";

const size_t CONSTANT_COUNT = 2;
const size_t COMPUTED_CONSTANT_COUNT = 1;
const size_t ALGEBRAIC_COUNT = 3;

const VariableInfo CONSTANT_INFO[] = {
    {"x", "dimensionless", "my_algebraic_system"},
    {"y", "dimensionless", "my_algebraic_system"}
};

const VariableInfo COMPUTED_CONSTANT_INFO[] = {
    {"a", "dimensionless", "my_algebraic_system"}
};

const VariableInfo ALGEBRAIC_INFO[] = {
    {"d", "dimensionless", "my_algebraic_system"},
    {"b", "dimensionless", "my_algebraic_system"},
    {"c", "dimensionless", "my_algebraic_system"}
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

    algebraic[2] = u[0];
    algebraic[1] = u[1];

    f[0] = 3.0*computedConstants[0]+2.0*algebraic[1]+algebraic[2]-57.0;
    f[1] = computedConstants[0]+3.0*algebraic[1]-algebraic[2]-19.0;
}

void findRoot0(double *variables)
{
    RootFindingInfo rfi = { variables };
    double u[2];

    u[0] = algebraic[2];
    u[1] = algebraic[1];

    nlaSolve(objectiveFunction0, u, 2, &rfi);

    algebraic[2] = u[0];
    algebraic[1] = u[1];
}

void initialiseVariables(double *constants)
{
    constants[0] = 3.0;
    constants[1] = 5.0;
    algebraic[1] = 1.0;
    algebraic[2] = 1.0;
}

void computeComputedConstants(double *constants, double *computedConstants)
{
    computedConstants[0] = 3.0*constants[0]+constants[1];
}

void computeVariables(double *constants, double *computedConstants, double *algebraic)
{
    findRoot0(variables);
    algebraic[0] = algebraic[1]+algebraic[2];
}

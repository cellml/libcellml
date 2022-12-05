/* The content of this file was generated using the C profile of libCellML 0.2.0. */

#include "model.h"

#include <math.h>
#include <stdlib.h>

const char VERSION[] = "0.3.0";
const char LIBCELLML_VERSION[] = "0.4.0";

const size_t VARIABLE_COUNT = 4;

const VariableInfoWithType VARIABLE_INFO[] = {
    {"b", "dimensionless", "my_algebraic_eqn", CONSTANT},
    {"c", "dimensionless", "my_algebraic_eqn", CONSTANT},
    {"d", "dimensionless", "my_algebraic_eqn", CONSTANT},
    {"a", "dimensionless", "my_algebraic_eqn", ALGEBRAIC}
};

double * createVariablesArray()
{
    return malloc(VARIABLE_COUNT*sizeof(double));
}

void deleteArray(double *array)
{
    free(array);
}

typedef struct {
    double *variables;
} RootFindInfo;

extern void nlaSolve(void (*objFunc)(double *, double *, void *),
                     double *u, int n, void *data);

void objFunc0(double *u, double *f, void *data)
{
    double *variables = ((RootFindInfo *) data)->variables;

    variables[3] = u[0];

    f[0] = variables[3]+variables[0]-(variables[1]+variables[2]);
}

void rootFind0(double *variables)
{
    double u[1] = { 1.0 };
    RootFindInfo rfi = { variables };

    nlaSolve(objFunc0, u, 1, &rfi);

    variables[3] = u[0];
}

void initialiseConstants(double *variables)
{
    variables[0] = 3.0;
    variables[1] = 5.0;
    variables[2] = 7.0;
}

void computeComputedConstants(double *variables)
{
    rootFind0(variables);
}

void computeVariables(double *variables)
{
}

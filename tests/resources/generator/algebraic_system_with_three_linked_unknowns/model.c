/* The content of this file was generated using the C profile of libCellML 0.4.0. */

#include "model.h"

#include <math.h>
#include <stdlib.h>

const char VERSION[] = "0.3.0";
const char LIBCELLML_VERSION[] = "0.4.0";

const size_t VARIABLE_COUNT = 3;

const VariableInfo VARIABLE_INFO[] = {
    {"x", "dimensionless", "my_algebraic_system", ALGEBRAIC},
    {"y", "dimensionless", "my_algebraic_system", ALGEBRAIC},
    {"z", "dimensionless", "my_algebraic_system", ALGEBRAIC}
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

    variables[0] = u[0];
    variables[1] = u[1];
    variables[2] = u[2];

    f[0] = 2.0*variables[0]+variables[1]-2.0*variables[2]-(-1.0);
    f[1] = 3.0*variables[0]-3.0*variables[1]-variables[2]-5.0;
    f[2] = variables[0]-2.0*variables[1]+3.0*variables[2]-6.0;
}

void rootFind0(double *variables)
{
    RootFindInfo rfi = { variables };
    double u[3];

    u[0] = variables[0];
    u[1] = variables[1];
    u[2] = variables[2];

    nlaSolve(objFunc0, u, 3, &rfi);

    variables[0] = u[0];
    variables[1] = u[1];
    variables[2] = u[2];
}

void initialiseVariables(double *variables)
{
    variables[0] = 1.0;
    variables[1] = 1.0;
    variables[2] = 1.0;
}

void computeComputedConstants(double *variables)
{
    rootFind0(variables);
}

void computeVariables(double *variables)
{
}

/* The content of this file was generated using the C profile of libCellML 0.6.2. */

#include "model.h"

#include <math.h>
#include <stdlib.h>

const char VERSION[] = "0.5.0";
const char LIBCELLML_VERSION[] = "0.6.2";

const size_t VARIABLE_COUNT = 3;

const VariableInfo VARIABLE_INFO[] = {
    {"z", "dimensionless", "my_algebraic_system", ALGEBRAIC},
    {"y", "dimensionless", "my_algebraic_system", ALGEBRAIC},
    {"x", "dimensionless", "my_algebraic_system", ALGEBRAIC}
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

    variables[0] = u[0];
    variables[1] = u[1];
    variables[2] = u[2];

    f[0] = 2.0*variables[2]+variables[1]-2.0*variables[0]-(-1.0);
    f[1] = 3.0*variables[2]-3.0*variables[1]-variables[0]-5.0;
    f[2] = variables[2]-2.0*variables[1]+3.0*variables[0]-6.0;
}

void findRoot0(double *variables)
{
    RootFindingInfo rfi = { variables };
    double u[3];

    u[0] = variables[0];
    u[1] = variables[1];
    u[2] = variables[2];

    nlaSolve(objectiveFunction0, u, 3, &rfi);

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
}

void computeVariables(double *variables)
{
    findRoot0(variables);
}

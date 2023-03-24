/* The content of this file was generated using the C profile of libCellML 0.4.0. */

#include "model.ordered.h"

#include <math.h>
#include <stdlib.h>

const char VERSION[] = "0.3.2";
const char LIBCELLML_VERSION[] = "0.4.0";

const size_t VARIABLE_COUNT = 6;

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
    double *variables = ((RootFindingInfo *) data)->variables;

    variables[3] = u[0];
    variables[4] = u[1];

    f[0] = 3.0*variables[0]+2.0*variables[4]+variables[3]-57.0;
    f[1] = variables[0]+3.0*variables[4]-variables[3]-19.0;
}

void findRoot0(double *variables)
{
    RootFindingInfo rfi = { variables };
    double u[2];

    u[0] = variables[3];
    u[1] = variables[4];

    nlaSolve(objectiveFunction0, u, 2, &rfi);

    variables[3] = u[0];
    variables[4] = u[1];
}

void initialiseVariables(double *variables)
{
    variables[1] = 3.0;
    variables[2] = 5.0;
    variables[3] = 1.0;
    variables[4] = 1.0;
}

void computeComputedConstants(double *variables)
{
    variables[0] = 3.0*variables[1]+variables[2];
}

void computeVariables(double *variables)
{
    findRoot0(variables);
    variables[5] = variables[4]+variables[3];
}

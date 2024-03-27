/* The content of this file was generated using the C profile of libCellML 0.5.0. */

#include "model.not.ordered.h"

#include <math.h>
#include <stdlib.h>

const char VERSION[] = "0.5.0";
const char LIBCELLML_VERSION[] = "0.5.0";

const size_t VARIABLE_COUNT = 6;

const VariableInfo VARIABLE_INFO[] = {
    {"d", "dimensionless", "my_algebraic_system", ALGEBRAIC},
    {"b", "dimensionless", "my_algebraic_system", ALGEBRAIC},
    {"c", "dimensionless", "my_algebraic_system", ALGEBRAIC},
    {"a", "dimensionless", "my_algebraic_system", COMPUTED_CONSTANT},
    {"x", "dimensionless", "my_algebraic_system", CONSTANT},
    {"y", "dimensionless", "my_algebraic_system", CONSTANT}
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

    variables[2] = u[0];
    variables[1] = u[1];

    f[0] = 3.0*variables[3]+2.0*variables[1]+variables[2]-57.0;
    f[1] = variables[3]+3.0*variables[1]-variables[2]-19.0;
}

void findRoot0(double *variables)
{
    RootFindingInfo rfi = { variables };
    double u[2];

    u[0] = variables[2];
    u[1] = variables[1];

    nlaSolve(objectiveFunction0, u, 2, &rfi);

    variables[2] = u[0];
    variables[1] = u[1];
}

void initialiseVariables(double *variables)
{
    variables[1] = 1.0;
    variables[2] = 1.0;
    variables[4] = 3.0;
    variables[5] = 5.0;
}

void computeComputedConstants(double *variables)
{
    variables[3] = 3.0*variables[4]+variables[5];
}

void computeVariables(double *variables)
{
    findRoot0(variables);
    variables[0] = variables[1]+variables[2];
}

/* The content of this file was generated using the C profile of libCellML 0.6.2. */

#include "model.h"

#include <math.h>
#include <stdlib.h>

const char VERSION[] = "0.5.0";
const char LIBCELLML_VERSION[] = "0.6.2";

const size_t VARIABLE_COUNT = 4;

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

    variables[3] = u[0];

    f[0] = variables[3]+variables[0]-(variables[1]+variables[2]);
}

void findRoot0(double *variables)
{
    RootFindingInfo rfi = { variables };
    double u[1];

    u[0] = variables[3];

    nlaSolve(objectiveFunction0, u, 1, &rfi);

    variables[3] = u[0];
}

void initialiseVariables(double *variables)
{
    variables[3] = 1.0;
    variables[0] = 3.0;
    variables[1] = 5.0;
    variables[2] = 7.0;
}

void computeComputedConstants(double *variables)
{
}

void computeVariables(double *variables)
{
    findRoot0(variables);
}

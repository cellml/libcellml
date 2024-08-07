/* The content of this file was generated using the C profile of libCellML 0.5.0. */

#include "model.two.externals.h"

#include <math.h>
#include <stdlib.h>

const char VERSION[] = "0.5.0";
const char LIBCELLML_VERSION[] = "0.5.0";

const size_t CONSTANT_COUNT = 0;
const size_t COMPUTED_CONSTANT_COUNT = 0;
const size_t ALGEBRAIC_COUNT = 3;

const VariableInfo VARIABLE_INFO[] = {
    {"x", "dimensionless", "my_algebraic_system", EXTERNAL},
    {"y", "dimensionless", "my_algebraic_system", ALGEBRAIC},
    {"z", "dimensionless", "my_algebraic_system", EXTERNAL}
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

    variables[1] = u[0];

    f[0] = 2.0*variables[0]+variables[1]-2.0*variables[2]-(-1.0);
}

void findRoot0(double *variables)
{
    RootFindingInfo rfi = { variables };
    double u[1];

    u[0] = variables[1];

    nlaSolve(objectiveFunction0, u, 1, &rfi);

    variables[1] = u[0];
}

void objectiveFunction1(double *u, double *f, void *data)
{
    double *variables = ((RootFindingInfo *) data)->variables;

    variables[1] = u[0];

    f[0] = 3.0*variables[0]-3.0*variables[1]-variables[2]-5.0;
}

void findRoot1(double *variables)
{
    RootFindingInfo rfi = { variables };
    double u[1];

    u[0] = variables[1];

    nlaSolve(objectiveFunction1, u, 1, &rfi);

    variables[1] = u[0];
}

void objectiveFunction2(double *u, double *f, void *data)
{
    double *variables = ((RootFindingInfo *) data)->variables;

    variables[1] = u[0];

    f[0] = variables[0]-2.0*variables[1]+3.0*variables[2]-6.0;
}

void findRoot2(double *variables)
{
    RootFindingInfo rfi = { variables };
    double u[1];

    u[0] = variables[1];

    nlaSolve(objectiveFunction2, u, 1, &rfi);

    variables[1] = u[0];
}

void initialiseVariables(double *constants, ExternalVariable externalVariable)
{
    variables[1] = 1.0;
    variables[0] = externalVariable(variables, 0);
    variables[2] = externalVariable(variables, 2);
}

void computeComputedConstants(double *computedConstants)
{
}

void computeVariables(double *variables, ExternalVariable externalVariable)
{
    variables[0] = externalVariable(variables, 0);
    variables[2] = externalVariable(variables, 2);
    findRoot0(variables);
    findRoot1(variables);
    findRoot2(variables);
}

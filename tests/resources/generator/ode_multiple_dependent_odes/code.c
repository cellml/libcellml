/* The contents of this file was generated from version 0.2.0 of libCellML. */

#include <math.h>
#include <stddef.h>
#include <stdlib.h>

const char VERSION[] = "0.2.0";

const size_t STATE_COUNT = 2;
const size_t VARIABLE_COUNT = 1;

struct VariableInfo {
    char component[9];
    char name[8];
    char units[14];
};

const struct VariableInfo VOI_INFO = {"my_x_ode", "t", "second"};

const struct VariableInfo STATE_VECTOR_INFORMATION_ARRAY[] = {
    {"my_x_ode", "x", "dimensionless"},
    {"my_y_ode", "y", "dimensionless"},
};

const struct VariableInfo VARIABLE_VECTOR_INFORMATION_ARRAY[] = {
    {"my_y_ode", "epsilon", "dimensionless"},
};

double * createStatesArray()
{
    return (double *) malloc(2 * sizeof(double));
}

double * createVariablesArray()
{
    return (double *) malloc(1 * sizeof(double));
}

void deleteArray(double *array)
{
    free(array);
}

void initializeConstants(double *states, double *variables)
{
    states[0] = -2.0;
    states[1] = 0.0;
    variables[0] = 1.0;
}

void computeComputedConstants(double *variables)
{
}

void computeRates(double voi, double *states, double *rates, double *variables)
{
    rates[0] = states[1]*1.0;
    rates[1] = (variables[0]*(1.0-pow(states[0], 2.0))*states[1]-states[0])*1.0;
}

void computeVariables(double voi, double *states, double *rates, double *variables)
{
}

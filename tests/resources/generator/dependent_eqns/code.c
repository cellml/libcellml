/* The contents of this file was generated from version 0.2.0 of libCellML. */
#include <math.h>
#include <stddef.h>
#include <stdlib.h>

const char VERSION[] = "0.2.0";

struct VariableInfo {
    char component[13];
    char name[5];
    char units[14];
};

const size_t STATE_VECTOR_SIZE = 1;
const size_t VARIABLE_VECTOR_SIZE = 2;

const struct VariableInfo VOI_INFORMATION = {"my_component", "time", "second"};

const struct VariableInfo STATE_VECTOR_INFORMATION_ARRAY[] = {
    {"my_component", "x", "dimensionless"},
};

const struct VariableInfo VARIABLE_VECTOR_INFORMATION_ARRAY[] = {
    {"my_component", "b", "second"},
    {"my_component", "a", "second"},
};

double * createStatesArray()
{
    return (double *) malloc(1 * sizeof(double));
}

double * createVariablesArray()
{
    return (double *) malloc(2 * sizeof(double));
}

void deleteArray(double *array)
{
    free(array);
}

void initializeConstants(double *states, double *variables)
{
    states[0] = 0.0;
}

void computeComputedConstants(double *variables)
{
}

void computeRates(double voi, double *states, double *rates, double *variables)
{
    rates[0] = 1.0;
}

void computeVariables(double voi, double *states, double *rates, double *variables)
{
    variables[0] = 2.0*voi;
    variables[1] = 3.0*variables[0];
}

/* The content of this file was generated from version 0.2.0 of libCellML. */

#include <math.h>
#include <stddef.h>
#include <stdlib.h>

const char LIBCELLML_VERSION[] = "0.2.0";

const size_t STATE_COUNT = 1;
const size_t VARIABLE_COUNT = 2;

struct VariableInfo {
    char component[13];
    char name[2];
    char units[14];
};

const struct VariableInfo VOI_INFO = {"my_component", "t", "second"};

const struct VariableInfo STATE_INFO[] = {
    {"my_component", "v", "dimensionless"}
};

const struct VariableInfo VARIABLE_INFO[] = {
    {"my_component", "a", "per_s"},
    {"my_component", "x", "per_s"}
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
    states[0] = 1.0;
    variables[0] = 1.0;
}

void computeComputedConstants(double *variables)
{
}

void computeRates(double voi, double *states, double *rates, double *variables)
{
    rates[0] = variables[0];
}

void computeVariables(double voi, double *states, double *rates, double *variables)
{
    variables[1] = rates[0];
}

/* The contents of this file was generated from version 0.2.0 of libCellML. */

#include <math.h>
#include <stddef.h>
#include <stdlib.h>

const char VERSION[] = "0.2.0";

const size_t STATE_COUNT = 0;
const size_t VARIABLE_COUNT = 1;

struct VariableInfo {
    char component[13];
    char name[2];
    char units[14];
};

const struct VariableInfo VOI_INFO = {"", "", ""};

const struct VariableInfo STATE_INFO[] = {
};

const struct VariableInfo VARIABLE_INFO[] = {
    {"my_component", "x", "dimensionless"},
};

double * createStatesArray()
{
    return (double *) malloc(0 * sizeof(double));
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
    variables[0] = 1.0;
}

void computeComputedConstants(double *variables)
{
}

void computeRates(double voi, double *states, double *rates, double *variables)
{
}

void computeVariables(double voi, double *states, double *rates, double *variables)
{
}

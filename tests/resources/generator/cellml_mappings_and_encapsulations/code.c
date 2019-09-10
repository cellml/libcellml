/* The contents of this file was generated from version 0.2.0 of libCellML. */

#include <math.h>
#include <stddef.h>
#include <stdlib.h>

const char VERSION[] = "0.2.0";

const size_t STATE_COUNT = 2;
const size_t VARIABLE_COUNT = 2;

struct VariableInfo {
    char component[24];
    char name[20];
    char units[11];
};

const struct VariableInfo VOI_INFO = {"circle_x", "t", "ms"};

const struct VariableInfo STATE_INFO[] = {
    {"circle_x_source", "x", "mM"},
    {"circle_y_implementation", "y", "mM"},
};

const struct VariableInfo VARIABLE_INFO[] = {
    {"circle_sibling", "local_complex_maths", "mM"},
    {"circle_x_sibling", "two_x", "milli_mole"},
};

double * createStatesArray()
{
    return (double *) malloc(2 * sizeof(double));
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
    states[1] = 1.0;
}

void computeComputedConstants(double *variables)
{
}

void computeRates(double voi, double *states, double *rates, double *variables)
{
    rates[0] = -states[1]*1.0;
    rates[1] = states[0]*1.0;
}

void computeVariables(double voi, double *states, double *rates, double *variables)
{
    variables[0] = states[1]+5.0*states[1]/3.0+1.0*exp(states[1]/2.0);
    variables[1] = 2.0*states[0];
}

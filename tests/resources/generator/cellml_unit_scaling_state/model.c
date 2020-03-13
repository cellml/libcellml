/* The content of this file was generated using the C profile of libCellML 0.2.0. */

#include "model.h"

#include <math.h>
#include <stdlib.h>

const char VERSION[] = "0.1.0";
const char LIBCELLML_VERSION[] = "0.2.0";

const size_t STATE_COUNT = 3;
const size_t VARIABLE_COUNT = 0;

const VariableInfo VOI_INFO = {"t", "ms", "environment"};

const VariableInfo STATE_INFO[] = {
    {"k", "mM", "states"},
    {"x", "mM", "main"},
    {"y", "M", "main"}
};

const VariableInfoWithType VARIABLE_INFO[] = {
};

double * createStatesArray()
{
    return (double *) malloc(STATE_COUNT*sizeof(double));
}

double * createVariablesArray()
{
    return (double *) malloc(VARIABLE_COUNT*sizeof(double));
}

void deleteArray(double *array)
{
    free(array);
}

void initializeStatesAndConstants(double *states, double *variables)
{
    states[0] = 123.0;
    states[1] = 3.0;
    states[2] = 5.0;
}

void computeComputedConstants(double *variables)
{
}

void computeRates(double voi, double *states, double *rates, double *variables)
{
    rates[0] = 789.0;
    rates[1] = states[0]+states[0];
    rates[2] = 0.001*states[0]+0.001*states[0];
}

void computeVariables(double voi, double *states, double *rates, double *variables)
{
}

/* The content of this file was generated using the C profile of libCellML 0.2.0. */

#include "model.h"

#include <math.h>
#include <stdlib.h>

const char VERSION[] = "0.1.0";
const char LIBCELLML_VERSION[] = "0.2.0";

const size_t STATE_COUNT = 2;
const size_t VARIABLE_COUNT = 0;

const VariableInfo VOI_INFO = {"t", "ms", "environment"};

const VariableInfo STATE_INFO[] = {
    {"k1", "mM", "main"},
    {"k2", "M", "main"}
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
    states[1] = 0.001*789.0;
}

void computeComputedConstants(double *variables)
{
}

void computeRates(double voi, double *states, double *rates, double *variables)
{
    rates[0] = 1.23;
    rates[1] = 7.89;
}

void computeVariables(double voi, double *states, double *rates, double *variables)
{
}

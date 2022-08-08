/* The content of this file was generated using the C profile of libCellML 0.2.0. */

#include "model.h"

#include <math.h>
#include <stdlib.h>

const char VERSION[] = "0.3.0";
const char LIBCELLML_VERSION[] = "0.2.0";

const size_t STATE_COUNT = 1;
const size_t VARIABLE_COUNT = 1;

const VariableInfo VOI_INFO = {"t", "ms", "environment", VARIABLE_OF_INTEGRATION};

const VariableInfo STATE_INFO[] = {
    {"x", "mV", "main", STATE}
};

const VariableInfo VARIABLE_INFO[] = {
    {"k", "mV", "constants", CONSTANT}
};

double * createStatesArray()
{
    return malloc(STATE_COUNT*sizeof(double));
}

double * createVariablesArray()
{
    return malloc(VARIABLE_COUNT*sizeof(double));
}

void deleteArray(double *array)
{
    free(array);
}

void initialiseVariables(double *states, double *variables)
{
    variables[0] = 123.0;
    states[0] = variables[0];
}

void computeComputedConstants(double *variables)
{
}

void computeRates(double voi, double *states, double *rates, double *variables)
{
    rates[0] = 1.23;
}

void computeVariables(double voi, double *states, double *rates, double *variables)
{
}

/* The content of this file was generated using the C profile of libCellML 0.2.0. */

#include "model.h"

#include <math.h>
#include <stdlib.h>

const char VERSION[] = "0.1.0";
const char LIBCELLML_VERSION[] = "0.2.0";

const size_t STATE_COUNT = 4;
const size_t VARIABLE_COUNT = 1;

const VariableInfo VOI_INFO = {"t", "ms", "environment"};

const VariableInfo STATE_INFO[] = {
    {"x", "mV", "t"},
    {"scaled_x", "V", "t"},
    {"x", "mV", "scaled_t"},
    {"scaled_x", "V", "scaled_t"}
};

const VariableInfoWithType VARIABLE_INFO[] = {
    {"k", "mV", "constants", CONSTANT}
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
    states[0] = 0.0;
    states[1] = 0.0;
    states[2] = 0.0;
    states[3] = 0.0;
    variables[0] = 123.0;
}

void computeComputedConstants(double *variables)
{
}

void computeRates(double voi, double *states, double *rates, double *variables)
{
    rates[0] = variables[0];
    rates[1] = 0.001*variables[0];
    rates[2] = 0.001*variables[0];
    rates[3] = 1000.0*0.001*variables[0];
}

void computeVariables(double voi, double *states, double *rates, double *variables)
{
}

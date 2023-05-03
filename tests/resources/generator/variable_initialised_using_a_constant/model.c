/* The content of this file was generated using the C profile of libCellML 0.4.0. */

#include "model.h"

#include <math.h>
#include <stdlib.h>

const char VERSION[] = "0.4.0";
const char LIBCELLML_VERSION[] = "0.4.0";

const size_t STATE_COUNT = 1;
const size_t VARIABLE_COUNT = 1;

const VariableInfo VOI_INFO = {"t", "second", "component_1", VARIABLE_OF_INTEGRATION};

const VariableInfo STATE_INFO[] = {
    {"X", "dimensionless", "component_1", STATE}
};

const VariableInfo VARIABLE_INFO[] = {
    {"X_init", "dimensionless", "component_2", CONSTANT}
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

void initialiseVariables(double *states, double *variables)
{
    variables[0] = 7.0;
    states[0] = variables[0];
}

void computeComputedConstants(double *variables)
{
}

void computeRates(double voi, double *states, double *rates, double *variables)
{
    rates[0] = 3.0;
}

void computeVariables(double voi, double *states, double *rates, double *variables)
{
}

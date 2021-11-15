/* The content of this file was generated using the C profile of libCellML 0.2.0. */

#include "model.h"

#include <math.h>
#include <stdlib.h>

const char VERSION[] = "0.3.0";
const char LIBCELLML_VERSION[] = "0.2.0";

const size_t STATE_COUNT = 2;
const size_t VARIABLE_COUNT = 0;

const VariableInfo VOI_INFO = {"t", "ms", "environment", VARIABLE_OF_INTEGRATION};

const VariableInfo STATE_INFO[] = {
    {"x", "dimensionless", "main", STATE},
    {"y", "dimensionless", "main", STATE}
};

const VariableInfo VARIABLE_INFO[] = {
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
    states[0] = 3.0;
    states[1] = 5.0;
}

void computeComputedConstants(double *variables)
{
}

void computeRates(double voi, double *states, double *rates, double *variables)
{
    rates[0] = voi/1.0;
    rates[1] = 0.001*voi/1.0;
}

void computeVariables(double voi, double *states, double *rates, double *variables)
{
}

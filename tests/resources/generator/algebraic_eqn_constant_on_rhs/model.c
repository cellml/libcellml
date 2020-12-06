/* The content of this file was generated using the C profile of libCellML 0.2.0. */

#include "model.h"

#include <math.h>
#include <stdlib.h>

const char VERSION[] = "0.2.0";
const char LIBCELLML_VERSION[] = "0.2.0";

const size_t STATE_COUNT = 0;
const size_t VARIABLE_COUNT = 1;

const VariableInfo VOI_INFO = {"", "", ""};

const VariableInfo STATE_INFO[] = {
};

const VariableInfoWithType VARIABLE_INFO[] = {
    {"x", "dimensionless", "my_component", COMPUTED_CONSTANT}
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

void initialiseStatesAndConstants(double *states, double *variables)
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

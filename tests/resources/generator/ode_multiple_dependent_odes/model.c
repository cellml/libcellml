/* The content of this file was generated using the C profile of libCellML 0.2.0. */

#include "model.h"

#include <math.h>
#include <stdlib.h>

const char VERSION[] = "0.1.0";
const char LIBCELLML_VERSION[] = "0.2.0";

const size_t STATE_COUNT = 2;
const size_t VARIABLE_COUNT = 1;

const VariableInfo VOI_INFO = {"t", "second", "environment"};

const VariableInfo STATE_INFO[] = {
    {"x", "dimensionless", "my_x_ode"},
    {"y", "dimensionless", "my_y_ode"}
};

const VariableInfoWithType VARIABLE_INFO[] = {
    {"epsilon", "dimensionless", "my_y_ode", CONSTANT}
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
    variables[0] = 1.0;
    states[0] = -2.0;
    states[1] = 0.0;
}

void computeComputedConstants(double *variables)
{
}

void computeRates(double voi, double *states, double *rates, double *variables)
{
    rates[0] = states[1]*1.0;
    rates[1] = (variables[0]*(1.0-pow(states[0], 2.0))*states[1]-states[0])*1.0;
}

void computeVariables(double voi, double *states, double *rates, double *variables)
{
}

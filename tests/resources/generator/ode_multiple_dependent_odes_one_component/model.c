/* The content of this file was generated using the C profile of libCellML 0.6.3. */

#include "model.h"

#include <math.h>
#include <stdlib.h>

const char VERSION[] = "0.5.0";
const char LIBCELLML_VERSION[] = "0.6.3";

const size_t STATE_COUNT = 2;
const size_t VARIABLE_COUNT = 1;

const VariableInfo VOI_INFO = {"t", "second", "my_component", VARIABLE_OF_INTEGRATION};

const VariableInfo STATE_INFO[] = {
    {"y", "dimensionless", "my_component", STATE},
    {"x", "dimensionless", "my_component", STATE}
};

const VariableInfo VARIABLE_INFO[] = {
    {"epsilon", "dimensionless", "my_component", CONSTANT}
};

double * createStatesArray()
{
    double *res = (double *) malloc(STATE_COUNT*sizeof(double));

    for (size_t i = 0; i < STATE_COUNT; ++i) {
        res[i] = NAN;
    }

    return res;
}

double * createVariablesArray()
{
    double *res = (double *) malloc(VARIABLE_COUNT*sizeof(double));

    for (size_t i = 0; i < VARIABLE_COUNT; ++i) {
        res[i] = NAN;
    }

    return res;
}

void deleteArray(double *array)
{
    free(array);
}

void initialiseVariables(double *states, double *rates, double *variables)
{
    variables[0] = 1.0;
    states[0] = 0.0;
    states[1] = -2.0;
}

void computeComputedConstants(double *variables)
{
}

void computeRates(double voi, double *states, double *rates, double *variables)
{
    rates[1] = states[0]*1.0;
    rates[0] = (variables[0]*(1.0-pow(states[1], 2.0))*states[0]-states[1])*1.0;
}

void computeVariables(double voi, double *states, double *rates, double *variables)
{
}

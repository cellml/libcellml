/* The content of this file was generated using the C profile of libCellML 0.6.2. */

#include "model.h"

#include <math.h>
#include <stdlib.h>

const char VERSION[] = "0.5.0";
const char LIBCELLML_VERSION[] = "0.6.2";

const size_t STATE_COUNT = 1;
const size_t VARIABLE_COUNT = 0;

const VariableInfo VOI_INFO = {"t", "second", "environment", VARIABLE_OF_INTEGRATION};

const VariableInfo STATE_INFO[] = {
    {"x", "dimensionless", "my_ode", STATE}
};

const VariableInfo VARIABLE_INFO[] = {
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
    states[0] = 1.0;
}

void computeComputedConstants(double *variables)
{
}

void computeRates(double voi, double *states, double *rates, double *variables)
{
    rates[0] = 1.0;
}

void computeVariables(double voi, double *states, double *rates, double *variables)
{
}

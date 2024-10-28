/* The content of this file was generated using the C profile of libCellML 0.6.1. */

#include "model.h"

#include <math.h>
#include <stdlib.h>

const char VERSION[] = "0.5.0";
const char LIBCELLML_VERSION[] = "0.6.1";

const size_t STATE_COUNT = 2;
const size_t VARIABLE_COUNT = 2;

const VariableInfo VOI_INFO = {"t", "ms", "environment", VARIABLE_OF_INTEGRATION};

const VariableInfo STATE_INFO[] = {
    {"y", "mM", "circle_y_implementation", STATE},
    {"x", "mM", "circle_x", STATE}
};

const VariableInfo VARIABLE_INFO[] = {
    {"local_complex_maths", "mM", "circle_sibling", ALGEBRAIC},
    {"two_x", "milli_mole", "circle_x_sibling", ALGEBRAIC}
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
    states[1] = 0.0;
}

void computeComputedConstants(double *variables)
{
}

void computeRates(double voi, double *states, double *rates, double *variables)
{
    rates[1] = -states[0]*1.0;
    rates[0] = states[1]*1.0;
}

void computeVariables(double voi, double *states, double *rates, double *variables)
{
    variables[0] = states[0]+5.0*states[0]/3.0+1.0*exp(states[0]/2.0);
    variables[1] = 2.0*states[1];
}

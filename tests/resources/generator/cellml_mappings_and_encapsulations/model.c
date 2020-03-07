/* The content of this file was generated using the C profile of libCellML 0.2.0. */

#include "model.h"

#include <math.h>
#include <stdlib.h>

const char VERSION[] = "0.1.0";
const char LIBCELLML_VERSION[] = "0.2.0";

const size_t STATE_COUNT = 2;
const size_t VARIABLE_COUNT = 2;

const VariableInfo VOI_INFO = {"t", "ms", "environment"};

const VariableInfo STATE_INFO[] = {
    {"x", "mM", "circle_x"},
    {"y", "uM", "circle_y_implementation"}
};

const VariableInfoWithType VARIABLE_INFO[] = {
    {"local_complex_maths", "mM", "circle_sibling", ALGEBRAIC},
    {"two_x", "milli_mole", "circle_x_sibling", ALGEBRAIC}
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
    states[1] = 1.0;
}

void computeComputedConstants(double *variables)
{
}

void computeRates(double voi, double *states, double *rates, double *variables)
{
    rates[0] = 0.001*-0.001*states[1]*1.0;
    rates[1] = 1000.0*states[0]*1.0;
}

void computeVariables(double voi, double *states, double *rates, double *variables)
{
    variables[0] = 0.001*states[1]+5.0*0.001*states[1]/3.0+1.0*exp(0.001*states[1]/2.0);
    variables[1] = 2.0*1000.0*states[0];
}

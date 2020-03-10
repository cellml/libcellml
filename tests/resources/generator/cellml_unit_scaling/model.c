/* The content of this file was generated using the C profile of libCellML 0.2.0. */

#include "model.h"

#include <math.h>
#include <stdlib.h>

const char VERSION[] = "0.1.0";
const char LIBCELLML_VERSION[] = "0.2.0";

const size_t STATE_COUNT = 7;
const size_t VARIABLE_COUNT = 3;

const VariableInfo VOI_INFO = {"t", "ms", "environment"};

const VariableInfo STATE_INFO[] = {
    {"y", "mV", "states"},
    {"x", "mV", "t"},
    {"scaled_x", "volt", "t"},
    {"z", "mV", "t"},
    {"x", "mV", "scaled_t"},
    {"scaled_x", "volt", "scaled_t"},
    {"scaled_z", "volt", "scaled_t"}
};

const VariableInfoWithType VARIABLE_INFO[] = {
    {"k", "mV", "constants", CONSTANT},
    {"voi", "ms", "t", ALGEBRAIC},
    {"scaled_voi", "second", "scaled_t", ALGEBRAIC}
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
    states[0] = 789.0;
    states[1] = 1.0;
    states[2] = 3.0;
    states[3] = 1.23;
    states[4] = 101.0;
    states[5] = 103.0;
    states[6] = 0.001*7.89;
    variables[0] = 123.0;
}

void computeComputedConstants(double *variables)
{
}

void computeRates(double voi, double *states, double *rates, double *variables)
{
    rates[0] = 1.23;
    rates[1] = variables[0]+states[0]+states[3];
    rates[2] = 0.001*variables[0]+0.001*states[0];
    rates[3] = variables[0]+states[0];
    rates[4] = 1000.0*(variables[0]+states[0]);
    rates[5] = 1000.0*(0.001*variables[0]+0.001*states[0]+states[6]);
    rates[6] = 1000.0*(0.001*variables[0]+0.001*states[0]);
}

void computeVariables(double voi, double *states, double *rates, double *variables)
{
    variables[1] = voi;
    variables[2] = 0.001*voi;
}

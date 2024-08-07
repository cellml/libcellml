/* The content of this file was generated using the C profile of libCellML 0.5.0. */

#include "model.ode.h"

#include <math.h>
#include <stdlib.h>

const char VERSION[] = "0.5.0";
const char LIBCELLML_VERSION[] = "0.5.0";

const size_t STATE_COUNT = 3;
const size_t CONSTANT_COUNT = 0;
const size_t COMPUTED_CONSTANT_COUNT = 0;
const size_t ALGEBRAIC_COUNT = 4;

const VariableInfo VOI_INFO = {"t", "dimensionless", "main", VARIABLE_OF_INTEGRATION};

const VariableInfo STATE_INFO[] = {
    {"y1", "dimensionless", "main", STATE},
    {"y3", "dimensionless", "main", STATE},
    {"y2", "dimensionless", "main", STATE}
};

const VariableInfo VARIABLE_INFO[] = {
    {"k1", "dimensionless", "main", CONSTANT},
    {"k3", "dimensionless", "main", CONSTANT},
    {"k2", "dimensionless", "main", CONSTANT},
    {"y2_scaled", "dimensionless", "main", ALGEBRAIC}
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

void initialiseVariables(double *states, double *rates, double *constants)
{
    variables[0] = 0.04;
    variables[1] = 1.0e4;
    variables[2] = 3.0e7;
    states[0] = 1.0;
    states[1] = 0.0;
    states[2] = 0.0;
}

void computeComputedConstants(double *computedConstants)
{
}

void computeRates(double voi, double *states, double *rates, double *constants, double *computedConstants, double *algebraic)
{
    rates[0] = -variables[0]*states[0]+variables[1]*states[2]*states[1];
    rates[2] = variables[0]*states[0]-variables[2]*pow(states[2], 2.0)-variables[1]*states[2]*states[1];
    rates[1] = variables[2]*pow(states[2], 2.0);
}

void computeVariables(double voi, double *states, double *rates, double *constants, double *computedConstants, double *algebraic)
{
    variables[3] = 10000.0*states[2];
}

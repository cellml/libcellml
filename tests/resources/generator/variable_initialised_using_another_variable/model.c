/* The content of this file was generated using the C profile of libCellML 0.6.3. */

#include "model.h"

#include <math.h>
#include <stdlib.h>

const char VERSION[] = "0.8.0";
const char LIBCELLML_VERSION[] = "0.6.3";

const size_t STATE_COUNT = 13;
const size_t CONSTANT_COUNT = 2;
const size_t COMPUTED_CONSTANT_COUNT = 1;
const size_t ALGEBRAIC_VARIABLE_COUNT = 0;

const VariableInfo VOI_INFO = {"t", "dimensionless", "main"};

const VariableInfo STATE_INFO[] = {
    {"xStateStateCst", "dimensionless", "main"},
    {"kStateStateCst", "dimensionless", "main"},
    {"xStateStateCompCst", "dimensionless", "main"},
    {"kStateStateCompCst", "dimensionless", "main"},
    {"xStateStateState", "dimensionless", "main"},
    {"kStateStateState", "dimensionless", "main"},
    {"xStateStateNla", "dimensionless", "main"},
    {"kStateStateNla", "dimensionless", "main"},
    {"xStateCst", "dimensionless", "main"},
    {"xStateCompCst", "dimensionless", "main"},
    {"xStateState", "dimensionless", "main"},
    {"kStateState", "dimensionless", "main"},
    {"xStateNla", "dimensionless", "main"}
};

const VariableInfo CONSTANT_INFO[] = {
    {"kStateCst", "dimensionless", "main"},
    {"kStateNla", "dimensionless", "main"}
};

const VariableInfo COMPUTED_CONSTANT_INFO[] = {
    {"kStateCompCst", "dimensionless", "main"}
};

const VariableInfo ALGEBRAIC_VARIABLE_INFO[] = {
};

double * createStatesArray()
{
    double *res = (double *) malloc(STATE_COUNT*sizeof(double));

    for (size_t i = 0; i < STATE_COUNT; ++i) {
        res[i] = NAN;
    }

    return res;
}

double * createConstantsArray()
{
    double *res = (double *) malloc(CONSTANT_COUNT*sizeof(double));

    for (size_t i = 0; i < CONSTANT_COUNT; ++i) {
        res[i] = NAN;
    }

    return res;
}

double * createComputedConstantsArray()
{
    double *res = (double *) malloc(COMPUTED_CONSTANT_COUNT*sizeof(double));

    for (size_t i = 0; i < COMPUTED_CONSTANT_COUNT; ++i) {
        res[i] = NAN;
    }

    return res;
}

double * createAlgebraicVariablesArray()
{
    double *res = (double *) malloc(ALGEBRAIC_VARIABLE_COUNT*sizeof(double));

    for (size_t i = 0; i < ALGEBRAIC_VARIABLE_COUNT; ++i) {
        res[i] = NAN;
    }

    return res;
}

void deleteArray(double *array)
{
    free(array);
}

void initialiseArrays(double *states, double *rates, double *constants, double *computedConstants, double *algebraicVariables)
{
    constants[0] = 3.0;
    states[1] = constants[0];
    states[0] = states[1];
    states[11] = 5.0;
    states[5] = states[11];
    states[4] = states[5];
    constants[1] = 7.0;
    states[7] = constants[1];
    states[6] = states[7];
    states[8] = constants[0];
    states[10] = states[11];
    states[12] = constants[1];
}

void computeComputedConstants(double voi, double *states, double *rates, double *constants, double *computedConstants, double *algebraicVariables)
{
    computedConstants[0] = 1.23*constants[0];
    states[3] = computedConstants[0];
    states[2] = states[3];
    states[9] = computedConstants[0];
}

void computeRates(double voi, double *states, double *rates, double *constants, double *computedConstants, double *algebraicVariables)
{
    rates[0] = 1.23;
    rates[1] = 1.23;
    rates[2] = 1.23;
    rates[3] = 1.23;
    rates[4] = 1.23;
    rates[5] = 1.23;
    rates[6] = 1.23;
    rates[7] = 1.23;
    rates[8] = 1.23;
    rates[9] = 1.23;
    rates[10] = 1.23;
    rates[11] = 1.23;
    rates[12] = 1.23;
}

void computeVariables(double voi, double *states, double *rates, double *constants, double *computedConstants, double *algebraicVariables)
{
}

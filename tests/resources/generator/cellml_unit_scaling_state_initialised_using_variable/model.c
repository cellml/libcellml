/* The content of this file was generated using the C profile of libCellML 0.6.3. */

#include "model.h"

#include <math.h>
#include <stdlib.h>

const char VERSION[] = "0.5.0";
const char LIBCELLML_VERSION[] = "0.6.3";

const size_t STATE_COUNT = 2;
const size_t VARIABLE_COUNT = 2;

const VariableInfo VOI_INFO = {"t", "ms", "environment", VARIABLE_OF_INTEGRATION};

const VariableInfo STATE_INFO[] = {
    {"k1", "mM", "main", STATE},
    {"k2", "M", "main", STATE}
};

const VariableInfo VARIABLE_INFO[] = {
    {"k1_cst", "mM", "constants", CONSTANT},
    {"k2_cst", "mM", "constants", CONSTANT}
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
    variables[0] = 123.0;
    variables[1] = 789.0;
    states[0] = variables[0];
    states[1] = 0.001*variables[1];
}

void computeComputedConstants(double *variables)
{
}

void computeRates(double voi, double *states, double *rates, double *variables)
{
    rates[0] = 1.23;
    rates[1] = 7.89;
}

void computeVariables(double voi, double *states, double *rates, double *variables)
{
}

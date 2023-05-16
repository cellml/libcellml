/* The content of this file was generated using the C profile of libCellML 0.4.0. */

#include "model.h"

#include <math.h>
#include <stdlib.h>

const char VERSION[] = "0.4.0";
const char LIBCELLML_VERSION[] = "0.4.0";

const size_t STATE_COUNT = 1;
const size_t VARIABLE_COUNT = 10;

const VariableInfo VOI_INFO = {"x", "dimensionless", "main", VARIABLE_OF_INTEGRATION};

const VariableInfo STATE_INFO[] = {
    {"sin", "dimensionless", "deriv_approx_sin", STATE}
};

const VariableInfo VARIABLE_INFO[] = {
    {"sin", "dimensionless", "actual_sin", ALGEBRAIC},
    {"deriv_approx_initial_value", "dimensionless", "main", CONSTANT},
    {"sin", "dimensionless", "parabolic_approx_sin", ALGEBRAIC},
    {"C", "dimensionless", "main", CONSTANT},
    {"k2_oPi", "dimensionless", "parabolic_approx_sin", COMPUTED_CONSTANT},
    {"k2Pi", "dimensionless", "parabolic_approx_sin", COMPUTED_CONSTANT},
    {"kPi_2", "dimensionless", "parabolic_approx_sin", COMPUTED_CONSTANT},
    {"kPi", "dimensionless", "parabolic_approx_sin", COMPUTED_CONSTANT},
    {"kPi_32", "dimensionless", "parabolic_approx_sin", COMPUTED_CONSTANT},
    {"z", "dimensionless", "parabolic_approx_sin", ALGEBRAIC}
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

void initialiseVariables(double *states, double *variables)
{
    variables[1] = 0.0;
    variables[3] = 0.75;
    variables[4] = 2.0/3.14159265358979;
    variables[5] = 2.0*3.14159265358979;
    variables[6] = 3.14159265358979/2.0;
    variables[7] = 3.14159265358979;
    variables[8] = 3.0*3.14159265358979/2.0;
    states[0] = variables[1];
}

void computeComputedConstants(double *variables)
{
}

void computeRates(double voi, double *states, double *rates, double *variables)
{
    rates[0] = cos(voi);
}

void computeVariables(double voi, double *states, double *rates, double *variables)
{
    variables[0] = sin(voi);
    variables[9] = (voi < variables[6])?voi*variables[4]-0.5:(voi < variables[7])?(3.14159265358979-voi)*variables[4]-0.5:(voi < variables[8])?(voi-3.14159265358979)*variables[4]-0.5:(variables[5]-voi)*variables[4]-0.5;
    variables[2] = (voi < variables[6])?-variables[9]*variables[9]+variables[3]+variables[9]:(voi < variables[7])?-variables[9]*variables[9]+variables[3]+variables[9]:(voi < variables[8])?variables[9]*variables[9]-variables[3]-variables[9]:variables[9]*variables[9]-variables[3]-variables[9];
}

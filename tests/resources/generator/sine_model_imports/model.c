/* The content of this file was generated using the C profile of libCellML 0.3.102. */

#include "model.h"

#include <math.h>
#include <stdlib.h>

const char VERSION[] = "0.3.0";
const char LIBCELLML_VERSION[] = "0.3.102";

const size_t STATE_COUNT = 1;
const size_t VARIABLE_COUNT = 10;

const VariableInfo VOI_INFO = {"x", "dimensionless", "main", VARIABLE_OF_INTEGRATION};

const VariableInfo STATE_INFO[] = {
    {"sin", "dimensionless", "deriv_approx_sin", STATE}
};

const VariableInfo VARIABLE_INFO[] = {
    {"C", "dimensionless", "main", CONSTANT},
    {"deriv_approx_initial_value", "dimensionless", "main", CONSTANT},
    {"sin", "dimensionless", "actual_sin", ALGEBRAIC},
    {"k2_oPi", "dimensionless", "parabolic_approx_sin", COMPUTED_CONSTANT},
    {"k2Pi", "dimensionless", "parabolic_approx_sin", COMPUTED_CONSTANT},
    {"kPi_2", "dimensionless", "parabolic_approx_sin", COMPUTED_CONSTANT},
    {"kPi", "dimensionless", "parabolic_approx_sin", COMPUTED_CONSTANT},
    {"kPi_32", "dimensionless", "parabolic_approx_sin", COMPUTED_CONSTANT},
    {"z", "dimensionless", "parabolic_approx_sin", ALGEBRAIC},
    {"sin", "dimensionless", "parabolic_approx_sin", ALGEBRAIC}
};

double * createStatesArray()
{
    return malloc(STATE_COUNT*sizeof(double));
}

double * createVariablesArray()
{
    return malloc(VARIABLE_COUNT*sizeof(double));
}

void deleteArray(double *array)
{
    free(array);
}

void initialiseVariables(double *states, double *variables)
{
    variables[0] = 0.75;
    variables[1] = 0.0;
    variables[3] = 2.0/3.14159265358979;
    variables[4] = 2.0*3.14159265358979;
    variables[5] = 3.14159265358979/2.0;
    variables[6] = 3.14159265358979;
    variables[7] = 3.0*3.14159265358979/2.0;
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
    variables[2] = sin(voi);
    variables[8] = (voi < variables[5])?voi*variables[3]-0.5:(voi < variables[6])?(3.14159265358979-voi)*variables[3]-0.5:(voi < variables[7])?(voi-3.14159265358979)*variables[3]-0.5:(variables[4]-voi)*variables[3]-0.5;
    variables[9] = (voi < variables[5])?-variables[8]*variables[8]+variables[0]+variables[8]:(voi < variables[6])?-variables[8]*variables[8]+variables[0]+variables[8]:(voi < variables[7])?variables[8]*variables[8]-variables[0]-variables[8]:variables[8]*variables[8]-variables[0]-variables[8];
}

/* The content of this file was generated using the C profile of libCellML 0.5.0. */

#include "model.h"

#include <math.h>
#include <stdlib.h>

const char VERSION[] = "0.6.0";
const char LIBCELLML_VERSION[] = "0.5.0";

const size_t STATE_COUNT = 1;
const size_t CONSTANT_COUNT = 2;
const size_t COMPUTED_CONSTANT_COUNT = 5;
const size_t ALGEBRAIC_COUNT = 3;

const VariableInfo VOI_INFO = {"x", "dimensionless", "main"};

const VariableInfo STATE_INFO[] = {
    {"sin", "dimensionless", "deriv_approx_sin"}
};

const VariableInfo CONSTANT_INFO[] = {
    {"deriv_approx_initial_value", "dimensionless", "main"},
    {"C", "dimensionless", "main"}
};

const VariableInfo COMPUTED_CONSTANT_INFO[] = {
    {"k2_oPi", "dimensionless", "parabolic_approx_sin"},
    {"k2Pi", "dimensionless", "parabolic_approx_sin"},
    {"kPi_2", "dimensionless", "parabolic_approx_sin"},
    {"kPi", "dimensionless", "parabolic_approx_sin"},
    {"kPi_32", "dimensionless", "parabolic_approx_sin"}
};

const VariableInfo ALGEBRAIC_INFO[] = {
    {"sin", "dimensionless", "actual_sin"},
    {"sin", "dimensionless", "parabolic_approx_sin"},
    {"z", "dimensionless", "parabolic_approx_sin"}
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

double * createAlgebraicArray()
{
    double *res = (double *) malloc(ALGEBRAIC_COUNT*sizeof(double));

    for (size_t i = 0; i < ALGEBRAIC_COUNT; ++i) {
        res[i] = NAN;
    }

    return res;
}

void deleteArray(double *array)
{
    free(array);
}

void initialiseVariables(double voi, double *states, double *rates, double *constants, double *algebraic)
{
    states[0] = constants[0];
    constants[0] = 0.0;
    constants[1] = 0.75;
    computedConstants[0] = 2.0/3.14159265358979;
    computedConstants[1] = 2.0*3.14159265358979;
    computedConstants[2] = 3.14159265358979/2.0;
    computedConstants[3] = 3.14159265358979;
    computedConstants[4] = 3.0*3.14159265358979/2.0;
}

void computeComputedConstants(double *constants, double *computedConstants)
{
}

void computeRates(double voi, double *states, double *rates, double *constants, double *computedConstants, double *algebraic)
{
    rates[0] = cos(voi);
}

void computeVariables(double voi, double *states, double *rates, double *constants, double *computedConstants, double *algebraic)
{
    algebraic[0] = sin(voi);
    algebraic[2] = (voi < computedConstants[2])?voi*computedConstants[0]-0.5:(voi < computedConstants[3])?(3.14159265358979-voi)*computedConstants[0]-0.5:(voi < computedConstants[4])?(voi-3.14159265358979)*computedConstants[0]-0.5:(computedConstants[1]-voi)*computedConstants[0]-0.5;
    algebraic[1] = (voi < computedConstants[2])?-algebraic[2]*algebraic[2]+constants[1]+algebraic[2]:(voi < computedConstants[3])?-algebraic[2]*algebraic[2]+constants[1]+algebraic[2]:(voi < computedConstants[4])?algebraic[2]*algebraic[2]-constants[1]-algebraic[2]:algebraic[2]*algebraic[2]-constants[1]-algebraic[2];
}

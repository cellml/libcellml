/* The content of this file was generated using the C profile of libCellML 0.5.0. */

#include "model.h"

#include <math.h>
#include <stdlib.h>

const char VERSION[] = "0.6.0";
const char LIBCELLML_VERSION[] = "0.5.0";

const size_t CONSTANT_COUNT = 2;
const size_t COMPUTED_CONSTANT_COUNT = 2;
const size_t ALGEBRAIC_COUNT = 0;

const VariableInfo CONSTANT_INFO[] = {
    {"L", "centimeter", "cell_geometry"},
    {"rad", "centimeter", "cell_geometry"}
};

const VariableInfo COMPUTED_CONSTANT_INFO[] = {
    {"vcell", "microlitre", "cell_geometry"},
    {"vss", "microlitre", "cell_geometry"}
};

const VariableInfo ALGEBRAIC_INFO[] = {
};

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

void initialiseVariables(double *constants, double *algebraic)
{
    constants[0] = 0.01;
    constants[1] = 0.0011;
}

void computeComputedConstants(double *constants, double *computedConstants)
{
    computedConstants[0] = 1000.0*3.14*constants[1]*constants[1]*constants[0];
    computedConstants[1] = 0.02*computedConstants[0];
}

void computeVariables(double *constants, double *computedConstants, double *algebraic)
{
}

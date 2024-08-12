/* The content of this file was generated using the C profile of libCellML 0.5.0. */

#include "model.h"

#include <math.h>
#include <stdlib.h>

const char VERSION[] = "0.6.0";
const char LIBCELLML_VERSION[] = "0.5.0";

const size_t CONSTANT_COUNT = 0;
const size_t COMPUTED_CONSTANT_COUNT = 2;
const size_t ALGEBRAIC_COUNT = 0;

const VariableInfo CONSTANT_INFO[] = {
};

const VariableInfo COMPUTED_CONSTANT_INFO[] = {
    {"x", "dimensionless", "my_algebraic_eqn", COMPUTED_CONSTANT},
    {"a", "dimensionless", "my_algebraic_eqn", COMPUTED_CONSTANT}
};

const VariableInfo ALGEBRAIC_INFO[] = {
};

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

void initialiseVariables(double *constants)
{
    computedConstants[1] = 1.0;
}

void computeComputedConstants(double *constants, double *computedConstants)
{
    computedConstants[0] = computedConstants[1];
}

void computeVariables(double *constants, double *computedConstants, double *algebraic)
{
}

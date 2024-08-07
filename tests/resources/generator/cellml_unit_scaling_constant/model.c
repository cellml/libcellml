/* The content of this file was generated using the C profile of libCellML 0.5.0. */

#include "model.h"

#include <math.h>
#include <stdlib.h>

const char VERSION[] = "0.5.0";
const char LIBCELLML_VERSION[] = "0.5.0";

const size_t CONSTANT_COUNT = 0;
const size_t COMPUTED_CONSTANT_COUNT = 0;
const size_t ALGEBRAIC_COUNT = 3;

const VariableInfo VARIABLE_INFO[] = {
    {"k", "mM", "constants", CONSTANT},
    {"x", "mM", "main", COMPUTED_CONSTANT},
    {"y", "M", "main", COMPUTED_CONSTANT}
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
    variables[0] = 123.0;
}

void computeComputedConstants(double *constants, double *computedConstants)
{
    variables[1] = variables[0]+variables[0];
    variables[2] = 0.001*variables[0]+0.001*variables[0];
}

void computeVariables(double *constants, double *computedConstants, double *algebraic)
{
}

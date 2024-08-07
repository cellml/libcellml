/* The content of this file was generated using the C profile of libCellML 0.5.0. */

#include "model.h"

#include <math.h>
#include <stdlib.h>

const char VERSION[] = "0.6.0";
const char LIBCELLML_VERSION[] = "0.5.0";

const size_t CONSTANT_COUNT = 0;
const size_t COMPUTED_CONSTANT_COUNT = 0;
const size_t ALGEBRAIC_COUNT = 4;

const VariableInfo VARIABLE_INFO[] = {
    {"vcell", "microlitre", "cell_geometry", COMPUTED_CONSTANT},
    {"L", "centimeter", "cell_geometry", CONSTANT},
    {"rad", "centimeter", "cell_geometry", CONSTANT},
    {"vss", "microlitre", "cell_geometry", COMPUTED_CONSTANT}
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
    constants[1] = 0.01;
    constants[2] = 0.0011;
}

void computeComputedConstants(double *constants, double *computedConstants)
{
    computedConstants[0] = 1000.0*3.14*constants[2]*constants[2]*constants[1];
    computedConstants[3] = 0.02*computedConstants[0];
}

void computeVariables(double *constants, double *computedConstants, double *algebraic)
{
}

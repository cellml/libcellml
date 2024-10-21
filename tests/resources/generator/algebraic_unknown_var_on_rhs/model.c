/* The content of this file was generated using the C profile of libCellML 0.6.0. */

#include "model.h"

#include <math.h>
#include <stdlib.h>

const char VERSION[] = "0.5.0";
const char LIBCELLML_VERSION[] = "0.6.0";

const size_t VARIABLE_COUNT = 2;

const VariableInfo VARIABLE_INFO[] = {
    {"x", "dimensionless", "my_component", COMPUTED_CONSTANT},
    {"y", "dimensionless", "my_component", COMPUTED_CONSTANT}
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

void initialiseVariables(double *variables)
{
    variables[0] = 1.0;
}

void computeComputedConstants(double *variables)
{
    variables[1] = variables[0];
}

void computeVariables(double *variables)
{
}

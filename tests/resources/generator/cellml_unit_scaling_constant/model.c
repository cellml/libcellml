/* The content of this file was generated using the C profile of libCellML 0.2.0. */

#include "model.h"

#include <math.h>
#include <stdlib.h>

const char VERSION[] = "0.3.0";
const char LIBCELLML_VERSION[] = "0.2.0";

const size_t VARIABLE_COUNT = 3;

const VariableInfoWithType VARIABLE_INFO[] = {
    {"k", "mM", "constants", CONSTANT},
    {"x", "mM", "main", COMPUTED_CONSTANT},
    {"y", "M", "main", COMPUTED_CONSTANT}
};

double * createVariablesArray()
{
    return malloc(VARIABLE_COUNT*sizeof(double));
}

void deleteArray(double *array)
{
    free(array);
}

void initialiseConstants(double *variables)
{
    variables[0] = 123.0;
}

void computeComputedConstants(double *variables)
{
    variables[1] = variables[0]+variables[0];
    variables[2] = 0.001*variables[0]+0.001*variables[0];
}

void computeVariables(double *variables)
{
}

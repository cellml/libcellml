/* The content of this file was generated using the C profile of libCellML 0.4.0. */

#include "model.h"

#include <math.h>
#include <stdlib.h>

const char VERSION[] = "0.3.0";
const char LIBCELLML_VERSION[] = "0.4.0";

const size_t VARIABLE_COUNT = 1;

const VariableInfo VARIABLE_INFO[] = {
    {"x", "dimensionless", "my_component", COMPUTED_CONSTANT}
};

double * createVariablesArray()
{
    return malloc(VARIABLE_COUNT*sizeof(double));
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
}

void computeVariables(double *variables)
{
}

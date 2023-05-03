/* The content of this file was generated using the C profile of libCellML 0.4.0. */

#include "model.h"

#include <math.h>
#include <stdlib.h>

const char VERSION[] = "0.4.0";
const char LIBCELLML_VERSION[] = "0.4.0";

const size_t VARIABLE_COUNT = 2;

const VariableInfo VARIABLE_INFO[] = {
    {"x", "dimensionless", "my_algebraic_eqn", COMPUTED_CONSTANT},
    {"a", "dimensionless", "my_algebraic_eqn", CONSTANT}
};

double * createVariablesArray()
{
    return (double *) malloc(VARIABLE_COUNT*sizeof(double));
}

void deleteArray(double *array)
{
    free(array);
}

void initialiseVariables(double *variables)
{
    variables[1] = 1.0;
}

void computeComputedConstants(double *variables)
{
    variables[0] = variables[1];
}

void computeVariables(double *variables)
{
}

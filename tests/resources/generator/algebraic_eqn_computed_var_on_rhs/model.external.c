/* The content of this file was generated using the C profile of libCellML 0.2.0. */

#include "model.external.h"

#include <math.h>
#include <stdlib.h>

const char VERSION[] = "0.3.0";
const char LIBCELLML_VERSION[] = "0.2.0";

const size_t VARIABLE_COUNT = 2;

const VariableInfoWithType VARIABLE_INFO[] = {
    {"a", "dimensionless", "my_algebraic_eqn", EXTERNAL},
    {"x", "dimensionless", "my_algebraic_eqn", COMPUTED_CONSTANT}
};

double * createVariablesArray()
{
    return (double *) malloc(VARIABLE_COUNT*sizeof(double));
}

void deleteArray(double *array)
{
    free(array);
}

void initialiseConstants(double *variables)
{
}

void computeComputedConstants(double *variables)
{
}

void computeVariables(double *variables, ExternalVariable externalVariable)
{
    variables[0] = externalVariable(variables, 0);
    variables[1] = variables[0];
}

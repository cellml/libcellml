/* The content of this file was generated using the C profile of libCellML 0.4.0. */

#include "model.three.externals.h"

#include <math.h>
#include <stdlib.h>

const char VERSION[] = "0.3.2";
const char LIBCELLML_VERSION[] = "0.4.0";

const size_t VARIABLE_COUNT = 3;

const VariableInfo VARIABLE_INFO[] = {
    {"x", "dimensionless", "my_algebraic_system", EXTERNAL},
    {"y", "dimensionless", "my_algebraic_system", EXTERNAL},
    {"z", "dimensionless", "my_algebraic_system", EXTERNAL}
};

double * createVariablesArray()
{
    return (double *) malloc(VARIABLE_COUNT*sizeof(double));
}

void deleteArray(double *array)
{
    free(array);
}

void initialiseVariables(double *variables, ExternalVariable externalVariable)
{
    variables[0] = externalVariable(variables, 0);
    variables[1] = externalVariable(variables, 1);
    variables[2] = externalVariable(variables, 2);
}

void computeComputedConstants(double *variables)
{
}

void computeVariables(double *variables, ExternalVariable externalVariable)
{
    variables[0] = externalVariable(variables, 0);
    variables[1] = externalVariable(variables, 1);
    variables[2] = externalVariable(variables, 2);
}

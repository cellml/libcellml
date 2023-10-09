/* The content of this file was generated using the C profile of libCellML 0.5.0. */

#include "model.external.h"

#include <math.h>
#include <stdlib.h>

const char VERSION[] = "0.4.0";
const char LIBCELLML_VERSION[] = "0.5.0";

const size_t VARIABLE_COUNT = 4;

const VariableInfo VARIABLE_INFO[] = {
    {"b", "dimensionless", "my_algebraic_eqn", COMPUTED_CONSTANT},
    {"c", "dimensionless", "my_algebraic_eqn", COMPUTED_CONSTANT},
    {"d", "dimensionless", "my_algebraic_eqn", COMPUTED_CONSTANT},
    {"a", "dimensionless", "my_algebraic_eqn", EXTERNAL}
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

void initialiseVariables(double *variables, ExternalVariable externalVariable)
{
    variables[0] = 3.0;
    variables[1] = 5.0;
    variables[2] = 7.0;
    variables[3] = externalVariable(variables, 3);
}

void computeComputedConstants(double *variables)
{
}

void computeVariables(double *variables, ExternalVariable externalVariable)
{
    variables[3] = externalVariable(variables, 3);
}

/* The content of this file was generated using the C profile of libCellML 0.5.0. */

#include "model.external.h"

#include <math.h>
#include <stdlib.h>

const char VERSION[] = "0.6.0";
const char LIBCELLML_VERSION[] = "0.5.0";

const size_t CONSTANT_COUNT = 0;
const size_t COMPUTED_CONSTANT_COUNT = 0;
const size_t ALGEBRAIC_COUNT = 2;

const VariableInfo VARIABLE_INFO[] = {
    {"x", "dimensionless", "my_algebraic_eqn", ALGEBRAIC},
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

void initialiseVariables(double *constants, ExternalVariable externalVariable)
{
    algebraic[1] = externalVariable(variables, 1);
}

void computeComputedConstants(double *constants, double *computedConstants)
{
}

void computeVariables(double *constants, double *computedConstants, double *algebraic, ExternalVariable externalVariable)
{
    algebraic[1] = externalVariable(variables, 1);
    algebraic[0] = algebraic[1];
}

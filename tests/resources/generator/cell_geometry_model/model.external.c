/* The content of this file was generated using the C profile of libCellML 0.4.0. */

#include "model.external.h"

#include <math.h>
#include <stdlib.h>

const char VERSION[] = "0.3.2";
const char LIBCELLML_VERSION[] = "0.4.0";

const size_t VARIABLE_COUNT = 4;

const VariableInfo VARIABLE_INFO[] = {
    {"vcell", "microlitre", "cell_geometry", ALGEBRAIC},
    {"vss", "microlitre", "cell_geometry", ALGEBRAIC},
    {"L", "centimeter", "cell_geometry", EXTERNAL},
    {"rad", "centimeter", "cell_geometry", EXTERNAL}
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
    variables[2] = externalVariable(variables, 2);
    variables[3] = externalVariable(variables, 3);
}

void computeComputedConstants(double *variables)
{
}

void computeVariables(double *variables, ExternalVariable externalVariable)
{
    variables[2] = externalVariable(variables, 2);
    variables[3] = externalVariable(variables, 3);
    variables[0] = 1000.0*3.14*variables[3]*variables[3]*variables[2];
    variables[1] = 0.02*variables[0];
}

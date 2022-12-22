/* The content of this file was generated using the C profile of libCellML 0.4.0. */

#include "model.h"

#include <math.h>
#include <stdlib.h>

const char VERSION[] = "0.3.2";
const char LIBCELLML_VERSION[] = "0.4.0";

const size_t VARIABLE_COUNT = 4;

const VariableInfo VARIABLE_INFO[] = {
    {"vcell", "microlitre", "cell_geometry", COMPUTED_CONSTANT},
    {"vss", "microlitre", "cell_geometry", COMPUTED_CONSTANT},
    {"L", "centimeter", "cell_geometry", CONSTANT},
    {"rad", "centimeter", "cell_geometry", CONSTANT}
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
    variables[2] = 0.01;
    variables[3] = 0.0011;
}

void computeComputedConstants(double *variables)
{
    variables[0] = 1000.0*3.14*variables[3]*variables[3]*variables[2];
    variables[1] = 0.02*variables[0];
}

void computeVariables(double *variables)
{
}

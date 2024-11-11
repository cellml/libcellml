/* The content of this file was generated using the C profile of libCellML 0.6.3. */

#include "model.h"

#include <math.h>
#include <stdlib.h>

const char VERSION[] = "0.5.0";
const char LIBCELLML_VERSION[] = "0.6.3";

const size_t VARIABLE_COUNT = 4;

const VariableInfo VARIABLE_INFO[] = {
    {"L", "centimeter", "cell_geometry", CONSTANT},
    {"rad", "centimeter", "cell_geometry", CONSTANT},
    {"vcell", "microlitre", "cell_geometry", COMPUTED_CONSTANT},
    {"vss", "microlitre", "cell_geometry", COMPUTED_CONSTANT}
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
    variables[0] = 0.01;
    variables[1] = 0.0011;
}

void computeComputedConstants(double *variables)
{
    variables[2] = 1000.0*3.14*variables[1]*variables[1]*variables[0];
    variables[3] = 0.02*variables[2];
}

void computeVariables(double *variables)
{
}

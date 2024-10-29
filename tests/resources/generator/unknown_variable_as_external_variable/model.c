/* The content of this file was generated using the C profile of libCellML 0.6.2. */

#include "model.h"

#include <math.h>
#include <stdlib.h>

const char VERSION[] = "0.5.0";
const char LIBCELLML_VERSION[] = "0.6.2";

const size_t VARIABLE_COUNT = 10;

const VariableInfo VARIABLE_INFO[] = {
    {"v", "fmol_per_sec", "SLC_template3_ss", ALGEBRAIC},
    {"E", "fmol", "SLC_template3_ss", CONSTANT},
    {"P_0", "per_fmol_sec4", "SLC_template3_ss", CONSTANT},
    {"q_Ao", "fmol", "SLC_template3_ss", CONSTANT},
    {"P_1", "per_fmol_sec4", "SLC_template3_ss", CONSTANT},
    {"q_Ai", "fmol", "SLC_template3_ss", CONSTANT},
    {"P_2", "per_fmol_sec3", "SLC_template3_ss", CONSTANT},
    {"P_5", "per_sec3", "SLC_template3_ss", CONSTANT},
    {"P_4", "per_fmol2_sec3", "SLC_template3_ss", CONSTANT},
    {"P_3", "per_fmol_sec3", "SLC_template3_ss", EXTERNAL}
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
    variables[1] = 1.1;
    variables[2] = 21262500.0;
    variables[3] = 150.0;
    variables[4] = 3402000.0;
    variables[5] = 2.0;
    variables[6] = 2902500.0;
    variables[7] = 810000.0;
    variables[8] = 247140.0;
    variables[9] = externalVariable(variables, 9);
}

void computeComputedConstants(double *variables)
{
}

void computeVariables(double *variables, ExternalVariable externalVariable)
{
    variables[9] = externalVariable(variables, 9);
    variables[0] = variables[1]*(variables[2]*variables[3]-variables[4]*variables[5])/(variables[6]*variables[5]+variables[9]*variables[3]+variables[8]*variables[5]*variables[3]+variables[7]);
}

/* The content of this file was generated using the C profile of libCellML 0.6.3. */

#include "model.h"

#include <math.h>
#include <stdlib.h>

const char VERSION[] = "0.5.0";
const char LIBCELLML_VERSION[] = "0.6.3";

const size_t VARIABLE_COUNT = 10;

const VariableInfo VARIABLE_INFO[] = {
    {"P_5", "per_sec3", "SLC_template3_ss", CONSTANT},
    {"q_Ao", "fmol", "SLC_template3_ss", CONSTANT},
    {"q_Ai", "fmol", "SLC_template3_ss", CONSTANT},
    {"P_4", "per_fmol2_sec3", "SLC_template3_ss", CONSTANT},
    {"P_3", "per_fmol_sec3", "SLC_template3_ss", EXTERNAL},
    {"P_2", "per_fmol_sec3", "SLC_template3_ss", CONSTANT},
    {"P_1", "per_fmol_sec4", "SLC_template3_ss", CONSTANT},
    {"P_0", "per_fmol_sec4", "SLC_template3_ss", CONSTANT},
    {"E", "fmol", "SLC_template3_ss", CONSTANT},
    {"v", "fmol_per_sec", "SLC_template3_ss", ALGEBRAIC}
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
    variables[0] = 810000.0;
    variables[1] = 150.0;
    variables[2] = 2.0;
    variables[3] = 247140.0;
    variables[5] = 2902500.0;
    variables[6] = 3402000.0;
    variables[7] = 21262500.0;
    variables[8] = 1.1;
    variables[4] = externalVariable(variables, 4);
}

void computeComputedConstants(double *variables)
{
}

void computeVariables(double *variables, ExternalVariable externalVariable)
{
    variables[4] = externalVariable(variables, 4);
    variables[9] = variables[8]*(variables[7]*variables[1]-variables[6]*variables[2])/(variables[5]*variables[2]+variables[4]*variables[1]+variables[3]*variables[2]*variables[1]+variables[0]);
}

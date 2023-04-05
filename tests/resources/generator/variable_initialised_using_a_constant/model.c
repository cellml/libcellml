/* The content of this file was generated using the C profile of libCellML 0.4.0. */

#include "model.h"

#include <math.h>
#include <stdlib.h>

const char VERSION[] = "0.3.2";
const char LIBCELLML_VERSION[] = "0.4.0";

const size_t STATE_COUNT = 2;
const size_t VARIABLE_COUNT = 15;

const VariableInfo VOI_INFO = {"t", "second", "BG_initTest", VARIABLE_OF_INTEGRATION};

const VariableInfo STATE_INFO[] = {
    {"q_Ai", "fmol", "BG_initTest", STATE},
    {"q_Ao", "fmol", "BG_initTest", STATE}
};

const VariableInfo VARIABLE_INFO[] = {
    {"mu_Ai", "J_per_mol", "BG_initTest", ALGEBRAIC},
    {"R", "J_per_K_per_mol", "BG_initTest_param", CONSTANT},
    {"K_Ai", "per_fmol", "BG_initTest_param", CONSTANT},
    {"T", "kelvin", "BG_initTest_param", CONSTANT},
    {"v_Ai", "fmol_per_sec", "BG_initTest", ALGEBRAIC},
    {"mu_Ao", "J_per_mol", "BG_initTest", ALGEBRAIC},
    {"K_Ao", "per_fmol", "BG_initTest_param", CONSTANT},
    {"v_Ao", "fmol_per_sec", "BG_initTest", ALGEBRAIC},
    {"v_Re1", "fmol_per_sec", "BG_initTest", ALGEBRAIC},
    {"kappa_Re1", "fmol_per_sec", "BG_initTest_param", CONSTANT},
    {"mu_Re1_in", "J_per_mol", "BG_initTest", ALGEBRAIC},
    {"mu_Re1_out", "J_per_mol", "BG_initTest", ALGEBRAIC},
    {"q_Ai_init", "fmol", "BG_initTest_param", CONSTANT},
    {"q_Ao_init", "fmol", "BG_initTest_param", CONSTANT},
    {"F", "C_per_mol", "BG_initTest_param", CONSTANT}
};

double * createStatesArray()
{
    return (double *) malloc(STATE_COUNT*sizeof(double));
}

double * createVariablesArray()
{
    return (double *) malloc(VARIABLE_COUNT*sizeof(double));
}

void deleteArray(double *array)
{
    free(array);
}

void initialiseVariables(double *states, double *variables)
{
    variables[1] = 8.31;
    variables[2] = 1.0;
    variables[3] = 293.0;
    variables[6] = 1.0;
    variables[9] = 1.0;
    variables[12] = 1.0;
    variables[13] = 1.0;
    variables[14] = 96485.0;
    states[0] = variables[12];
    states[1] = variables[13];
}

void computeComputedConstants(double *variables)
{
}

void computeRates(double voi, double *states, double *rates, double *variables)
{
    variables[5] = variables[1]*variables[3]*log(variables[6]*states[1]);
    variables[10] = variables[5];
    variables[0] = variables[1]*variables[3]*log(variables[2]*states[0]);
    variables[11] = variables[0];
    variables[8] = variables[9]*(exp(variables[10]/(variables[1]*variables[3]))-exp(variables[11]/(variables[1]*variables[3])));
    variables[4] = variables[8];
    rates[0] = variables[4];
    variables[7] = -variables[8];
    rates[1] = variables[7];
}

void computeVariables(double voi, double *states, double *rates, double *variables)
{
    variables[0] = variables[1]*variables[3]*log(variables[2]*states[0]);
    variables[5] = variables[1]*variables[3]*log(variables[6]*states[1]);
    variables[10] = variables[5];
    variables[11] = variables[0];
    variables[8] = variables[9]*(exp(variables[10]/(variables[1]*variables[3]))-exp(variables[11]/(variables[1]*variables[3])));
    variables[4] = variables[8];
    variables[7] = -variables[8];
}

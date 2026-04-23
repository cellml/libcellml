/* The content of this file was generated using the C profile of libCellML 0.6.3. */

#include "model.h"

#include <math.h>
#include <stdlib.h>

const char VERSION[] = "0.8.0";
const char LIBCELLML_VERSION[] = "0.6.3";

const size_t CONSTANT_COUNT = 1;
const size_t COMPUTED_CONSTANT_COUNT = 48;
const size_t ALGEBRAIC_VARIABLE_COUNT = 0;

const VariableInfo CONSTANT_INFO[] = {
    {"a", "dimensionless", "my_component"}
};

const VariableInfo COMPUTED_CONSTANT_INFO[] = {
    {"eqEqn1", "dimensionless", "my_component"},
    {"eqEqn2", "dimensionless", "my_component"},
    {"eqEqn3", "dimensionless", "my_component"},
    {"eqEqn4", "dimensionless", "my_component"},
    {"eqEqn5", "dimensionless", "my_component"},
    {"neqEqn1", "dimensionless", "my_component"},
    {"neqEqn2", "dimensionless", "my_component"},
    {"neqEqn3", "dimensionless", "my_component"},
    {"neqEqn4", "dimensionless", "my_component"},
    {"neqEqn5", "dimensionless", "my_component"},
    {"ltEqn1", "dimensionless", "my_component"},
    {"ltEqn2", "dimensionless", "my_component"},
    {"ltEqn3", "dimensionless", "my_component"},
    {"ltEqn4", "dimensionless", "my_component"},
    {"ltEqn5", "dimensionless", "my_component"},
    {"leqEqn1", "dimensionless", "my_component"},
    {"leqEqn2", "dimensionless", "my_component"},
    {"leqEqn3", "dimensionless", "my_component"},
    {"leqEqn4", "dimensionless", "my_component"},
    {"leqEqn5", "dimensionless", "my_component"},
    {"gtEqn1", "dimensionless", "my_component"},
    {"gtEqn2", "dimensionless", "my_component"},
    {"gtEqn3", "dimensionless", "my_component"},
    {"gtEqn4", "dimensionless", "my_component"},
    {"gtEqn5", "dimensionless", "my_component"},
    {"geqEqn1", "dimensionless", "my_component"},
    {"geqEqn2", "dimensionless", "my_component"},
    {"geqEqn3", "dimensionless", "my_component"},
    {"geqEqn4", "dimensionless", "my_component"},
    {"geqEqn5", "dimensionless", "my_component"},
    {"andEqn1", "dimensionless", "my_component"},
    {"andEqn2", "dimensionless", "my_component"},
    {"andEqn3", "dimensionless", "my_component"},
    {"andEqn4", "dimensionless", "my_component"},
    {"andEqn5", "dimensionless", "my_component"},
    {"orEqn1", "dimensionless", "my_component"},
    {"orEqn2", "dimensionless", "my_component"},
    {"orEqn3", "dimensionless", "my_component"},
    {"orEqn4", "dimensionless", "my_component"},
    {"orEqn5", "dimensionless", "my_component"},
    {"xorEqn1", "dimensionless", "my_component"},
    {"xorEqn2", "dimensionless", "my_component"},
    {"xorEqn3", "dimensionless", "my_component"},
    {"xorEqn4", "dimensionless", "my_component"},
    {"xorEqn5", "dimensionless", "my_component"},
    {"notEqn1", "dimensionless", "my_component"},
    {"notEqn2", "dimensionless", "my_component"},
    {"notEqn3", "dimensionless", "my_component"}
};

const VariableInfo ALGEBRAIC_VARIABLE_INFO[] = {
};

double xor(double x, double y)
{
    return (x != 0.0) ^ (y != 0.0);
}

double * createConstantsArray()
{
    double *res = (double *) malloc(CONSTANT_COUNT*sizeof(double));

    for (size_t i = 0; i < CONSTANT_COUNT; ++i) {
        res[i] = NAN;
    }

    return res;
}

double * createComputedConstantsArray()
{
    double *res = (double *) malloc(COMPUTED_CONSTANT_COUNT*sizeof(double));

    for (size_t i = 0; i < COMPUTED_CONSTANT_COUNT; ++i) {
        res[i] = NAN;
    }

    return res;
}

double * createAlgebraicVariablesArray()
{
    double *res = (double *) malloc(ALGEBRAIC_VARIABLE_COUNT*sizeof(double));

    for (size_t i = 0; i < ALGEBRAIC_VARIABLE_COUNT; ++i) {
        res[i] = NAN;
    }

    return res;
}

void deleteArray(double *array)
{
    free(array);
}

void initialiseArrays(double *constants, double *computedConstants, double *algebraicVariables)
{
    constants[0] = 1.0;
    computedConstants[3] = 1.0;
    computedConstants[4] = 0.0;
    computedConstants[8] = 1.0;
    computedConstants[9] = 0.0;
    computedConstants[13] = 1.0;
    computedConstants[14] = 0.0;
    computedConstants[18] = 1.0;
    computedConstants[19] = 0.0;
    computedConstants[23] = 1.0;
    computedConstants[24] = 0.0;
    computedConstants[28] = 1.0;
    computedConstants[29] = 0.0;
    computedConstants[33] = 1.0;
    computedConstants[34] = 0.0;
    computedConstants[38] = 1.0;
    computedConstants[39] = 0.0;
    computedConstants[43] = 1.0;
    computedConstants[44] = 0.0;
    computedConstants[46] = 1.0;
    computedConstants[47] = 0.0;
}

void computeComputedConstants(double *constants, double *computedConstants, double *algebraicVariables)
{
    computedConstants[0] = constants[0] == constants[0];
    computedConstants[1] = 1.0 == constants[0];
    computedConstants[2] = constants[0] == 1.0;
    computedConstants[5] = constants[0] != constants[0];
    computedConstants[6] = 1.0 != constants[0];
    computedConstants[7] = constants[0] != 1.0;
    computedConstants[10] = constants[0] < constants[0];
    computedConstants[11] = 1.0 < constants[0];
    computedConstants[12] = constants[0] < 1.0;
    computedConstants[15] = constants[0] <= constants[0];
    computedConstants[16] = 1.0 <= constants[0];
    computedConstants[17] = constants[0] <= 1.0;
    computedConstants[20] = constants[0] > constants[0];
    computedConstants[21] = 1.0 > constants[0];
    computedConstants[22] = constants[0] > 1.0;
    computedConstants[25] = constants[0] >= constants[0];
    computedConstants[26] = 1.0 >= constants[0];
    computedConstants[27] = constants[0] >= 1.0;
    computedConstants[30] = constants[0] && constants[0];
    computedConstants[31] = 1.0 && constants[0];
    computedConstants[32] = constants[0] && 1.0;
    computedConstants[35] = constants[0] || constants[0];
    computedConstants[36] = 1.0 || constants[0];
    computedConstants[37] = constants[0] || 1.0;
    computedConstants[40] = xor(constants[0], constants[0]);
    computedConstants[41] = xor(1.0, constants[0]);
    computedConstants[42] = xor(constants[0], 1.0);
    computedConstants[45] = !constants[0];
}

void computeVariables(double *constants, double *computedConstants, double *algebraicVariables)
{
}

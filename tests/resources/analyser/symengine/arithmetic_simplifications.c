/* The content of this file was generated using the C profile of libCellML 0.7.0. */

#include "model.h"

#include <math.h>
#include <stdlib.h>

const char VERSION[] = "0.8.0";
const char LIBCELLML_VERSION[] = "0.7.0";

const size_t CONSTANT_COUNT = 1;
const size_t COMPUTED_CONSTANT_COUNT = 76;
const size_t ALGEBRAIC_VARIABLE_COUNT = 0;

const VariableInfo CONSTANT_INFO[] = {
    {"a", "dimensionless", "my_component"}
};

const VariableInfo COMPUTED_CONSTANT_INFO[] = {
    {"plusEqn1", "dimensionless", "my_component"},
    {"plusEqn2", "dimensionless", "my_component"},
    {"plusEqn3", "dimensionless", "my_component"},
    {"plusEqn4", "dimensionless", "my_component"},
    {"plusEqn5", "dimensionless", "my_component"},
    {"plusEqn6", "dimensionless", "my_component"},
    {"plusEqn7", "dimensionless", "my_component"},
    {"minusEqn1", "dimensionless", "my_component"},
    {"minusEqn2", "dimensionless", "my_component"},
    {"minusEqn3", "dimensionless", "my_component"},
    {"minusEqn4", "dimensionless", "my_component"},
    {"minusEqn5", "dimensionless", "my_component"},
    {"minusEqn6", "dimensionless", "my_component"},
    {"minusEqn7", "dimensionless", "my_component"},
    {"minusEqn8", "dimensionless", "my_component"},
    {"minusEqn9", "dimensionless", "my_component"},
    {"minusEqn10", "dimensionless", "my_component"},
    {"minusEqn11", "dimensionless", "my_component"},
    {"minusEqn12", "dimensionless", "my_component"},
    {"minusEqn13", "dimensionless", "my_component"},
    {"minusEqn14", "dimensionless", "my_component"},
    {"timesEqn1", "dimensionless", "my_component"},
    {"timesEqn2", "dimensionless", "my_component"},
    {"timesEqn3", "dimensionless", "my_component"},
    {"timesEqn4", "dimensionless", "my_component"},
    {"timesEqn5", "dimensionless", "my_component"},
    {"timesEqn6", "dimensionless", "my_component"},
    {"timesEqn7", "dimensionless", "my_component"},
    {"timesEqn8", "dimensionless", "my_component"},
    {"timesEqn9", "dimensionless", "my_component"},
    {"timesEqn10", "dimensionless", "my_component"},
    {"divideEqn1", "dimensionless", "my_component"},
    {"divideEqn2", "dimensionless", "my_component"},
    {"divideEqn3", "dimensionless", "my_component"},
    {"divideEqn4", "dimensionless", "my_component"},
    {"divideEqn5", "dimensionless", "my_component"},
    {"divideEqn6", "dimensionless", "my_component"},
    {"divideEqn7", "dimensionless", "my_component"},
    {"divideEqn8", "dimensionless", "my_component"},
    {"powerEqn1", "dimensionless", "my_component"},
    {"powerEqn2", "dimensionless", "my_component"},
    {"powerEqn3", "dimensionless", "my_component"},
    {"powerEqn4", "dimensionless", "my_component"},
    {"powerEqn5", "dimensionless", "my_component"},
    {"powerEqn6", "dimensionless", "my_component"},
    {"powerEqn7", "dimensionless", "my_component"},
    {"rootEqn1", "dimensionless", "my_component"},
    {"rootEqn2", "dimensionless", "my_component"},
    {"rootEqn3", "dimensionless", "my_component"},
    {"rootEqn4", "dimensionless", "my_component"},
    {"rootEqn5", "dimensionless", "my_component"},
    {"rootEqn6", "dimensionless", "my_component"},
    {"absEqn1", "dimensionless", "my_component"},
    {"expEqn1", "dimensionless", "my_component"},
    {"lnEqn1", "dimensionless", "my_component"},
    {"logEqn1", "dimensionless", "my_component"},
    {"logEqn2", "dimensionless", "my_component"},
    {"logEqn3", "dimensionless", "my_component"},
    {"logEqn4", "dimensionless", "my_component"},
    {"logEqn5", "dimensionless", "my_component"},
    {"ceilingEqn1", "dimensionless", "my_component"},
    {"ceilingEqn2", "dimensionless", "my_component"},
    {"floorEqn1", "dimensionless", "my_component"},
    {"floorEqn2", "dimensionless", "my_component"},
    {"minEqn1", "dimensionless", "my_component"},
    {"minEqn2", "dimensionless", "my_component"},
    {"minEqn3", "dimensionless", "my_component"},
    {"minEqn4", "dimensionless", "my_component"},
    {"maxEqn1", "dimensionless", "my_component"},
    {"maxEqn2", "dimensionless", "my_component"},
    {"maxEqn3", "dimensionless", "my_component"},
    {"maxEqn4", "dimensionless", "my_component"},
    {"remEqn1", "dimensionless", "my_component"},
    {"remEqn2", "dimensionless", "my_component"},
    {"remEqn3", "dimensionless", "my_component"},
    {"remEqn4", "dimensionless", "my_component"}
};

const VariableInfo ALGEBRAIC_VARIABLE_INFO[] = {
};

double min(double x, double y)
{
    return (x < y)?x:y;
}

double max(double x, double y)
{
    return (x > y)?x:y;
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
    computedConstants[3] = 2.0;
    computedConstants[10] = 0.0;
    computedConstants[13] = -1.0;
    computedConstants[24] = 1.0;
    computedConstants[25] = 0.0;
    computedConstants[26] = 0.0;
    computedConstants[34] = 1.0;
    computedConstants[35] = 0.0;
    computedConstants[40] = 1.0;
    computedConstants[42] = 1.0;
    computedConstants[43] = 1.0;
    computedConstants[44] = 0.0;
    computedConstants[49] = 1.0;
    computedConstants[51] = 1.0;
    computedConstants[52] = 1.0;
    computedConstants[53] = 2.71828182845905;
    computedConstants[54] = 1.00000000001507;
    computedConstants[58] = 1.0;
    computedConstants[59] = 1.0;
    computedConstants[61] = 2.0;
    computedConstants[63] = 1.0;
    computedConstants[67] = 1.0;
    computedConstants[71] = 1.0;
    computedConstants[75] = 0.0;
}

void computeComputedConstants(double *constants, double *computedConstants, double *algebraicVariables)
{
    computedConstants[0] = constants[0]+constants[0];
    computedConstants[1] = 1.0+constants[0];
    computedConstants[2] = constants[0]+1.0;
    computedConstants[4] = constants[0];
    computedConstants[5] = constants[0];
    computedConstants[6] = constants[0];
    computedConstants[7] = constants[0]-constants[0];
    computedConstants[8] = 1.0-constants[0];
    computedConstants[9] = constants[0]-1.0;
    computedConstants[11] = -constants[0];
    computedConstants[12] = constants[0];
    computedConstants[14] = constants[0];
    computedConstants[15] = -constants[0]-constants[0];
    computedConstants[16] = -constants[0]+constants[0];
    computedConstants[17] = (-constants[0]-constants[0])*constants[0];
    computedConstants[18] = (-constants[0]+constants[0])*constants[0];
    computedConstants[19] = (-constants[0]-constants[0])/constants[0];
    computedConstants[20] = (-constants[0]+constants[0])/constants[0];
    computedConstants[21] = constants[0]*constants[0];
    computedConstants[22] = constants[0];
    computedConstants[23] = constants[0];
    computedConstants[27] = -constants[0];
    computedConstants[28] = -constants[0];
    computedConstants[29] = constants[0]/constants[0];
    computedConstants[30] = constants[0]/constants[0];
    computedConstants[31] = constants[0]/constants[0];
    computedConstants[32] = 1.0/constants[0];
    computedConstants[33] = constants[0];
    computedConstants[36] = -constants[0];
    computedConstants[37] = constants[0];
    computedConstants[38] = 1.0/(2.0/constants[0]);
    computedConstants[39] = pow(constants[0], constants[0]);
    computedConstants[41] = constants[0];
    computedConstants[45] = 1.0/constants[0];
    computedConstants[46] = pow(constants[0], 1.0/constants[0]);
    computedConstants[47] = pow(1.0, 1.0/constants[0]);
    computedConstants[48] = pow(constants[0], 1.0/1.0);
    computedConstants[50] = sqrt(constants[0]);
    computedConstants[55] = log(constants[0])/log(constants[0]);
    computedConstants[56] = log(constants[0])/log(1.0);
    computedConstants[57] = log(1.0)/log(constants[0]);
    computedConstants[60] = ceil(constants[0]);
    computedConstants[62] = floor(constants[0]);
    computedConstants[64] = min(constants[0], constants[0]);
    computedConstants[65] = min(1.0, constants[0]);
    computedConstants[66] = min(constants[0], 1.0);
    computedConstants[68] = max(constants[0], constants[0]);
    computedConstants[69] = max(1.0, constants[0]);
    computedConstants[70] = max(constants[0], 1.0);
    computedConstants[72] = fmod(constants[0], constants[0]);
    computedConstants[73] = fmod(1.0, constants[0]);
    computedConstants[74] = fmod(constants[0], 1.0);
}

void computeVariables(double *constants, double *computedConstants, double *algebraicVariables)
{
}

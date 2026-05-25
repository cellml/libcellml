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
    {"sinEqn1", "dimensionless", "my_component"},
    {"sinEqn2", "dimensionless", "my_component"},
    {"cosEqn1", "dimensionless", "my_component"},
    {"cosEqn2", "dimensionless", "my_component"},
    {"tanEqn1", "dimensionless", "my_component"},
    {"tanEqn2", "dimensionless", "my_component"},
    {"secEqn1", "dimensionless", "my_component"},
    {"secEqn2", "dimensionless", "my_component"},
    {"cscEqn1", "dimensionless", "my_component"},
    {"cscEqn2", "dimensionless", "my_component"},
    {"cotEqn1", "dimensionless", "my_component"},
    {"cotEqn2", "dimensionless", "my_component"},
    {"sinhEqn1", "dimensionless", "my_component"},
    {"sinhEqn2", "dimensionless", "my_component"},
    {"coshEqn1", "dimensionless", "my_component"},
    {"coshEqn2", "dimensionless", "my_component"},
    {"tanhEqn1", "dimensionless", "my_component"},
    {"tanhEqn2", "dimensionless", "my_component"},
    {"sechEqn1", "dimensionless", "my_component"},
    {"sechEqn2", "dimensionless", "my_component"},
    {"cschEqn1", "dimensionless", "my_component"},
    {"cschEqn2", "dimensionless", "my_component"},
    {"cothEqn1", "dimensionless", "my_component"},
    {"cothEqn2", "dimensionless", "my_component"},
    {"asinEqn1", "dimensionless", "my_component"},
    {"asinEqn2", "dimensionless", "my_component"},
    {"acosEqn1", "dimensionless", "my_component"},
    {"acosEqn2", "dimensionless", "my_component"},
    {"atanEqn1", "dimensionless", "my_component"},
    {"atanEqn2", "dimensionless", "my_component"},
    {"asecEqn1", "dimensionless", "my_component"},
    {"asecEqn2", "dimensionless", "my_component"},
    {"acscEqn1", "dimensionless", "my_component"},
    {"acscEqn2", "dimensionless", "my_component"},
    {"acotEqn1", "dimensionless", "my_component"},
    {"acotEqn2", "dimensionless", "my_component"},
    {"asinhEqn1", "dimensionless", "my_component"},
    {"asinhEqn2", "dimensionless", "my_component"},
    {"acoshEqn1", "dimensionless", "my_component"},
    {"acoshEqn2", "dimensionless", "my_component"},
    {"atanhEqn1", "dimensionless", "my_component"},
    {"atanhEqn2", "dimensionless", "my_component"},
    {"asechEqn1", "dimensionless", "my_component"},
    {"asechEqn2", "dimensionless", "my_component"},
    {"acschEqn1", "dimensionless", "my_component"},
    {"acschEqn2", "dimensionless", "my_component"},
    {"acothEqn1", "dimensionless", "my_component"},
    {"acothEqn2", "dimensionless", "my_component"}
};

const VariableInfo ALGEBRAIC_VARIABLE_INFO[] = {
};

double sec(double x)
{
    return 1.0/cos(x);
}

double csc(double x)
{
    return 1.0/sin(x);
}

double cot(double x)
{
    return 1.0/tan(x);
}

double sech(double x)
{
    return 1.0/cosh(x);
}

double csch(double x)
{
    return 1.0/sinh(x);
}

double coth(double x)
{
    return 1.0/tanh(x);
}

double asec(double x)
{
    return acos(1.0/x);
}

double acsc(double x)
{
    return asin(1.0/x);
}

double acot(double x)
{
    return atan(1.0/x);
}

double asech(double x)
{
    double oneOverX = 1.0/x;

    return log(oneOverX+sqrt(oneOverX*oneOverX-1.0));
}

double acsch(double x)
{
    double oneOverX = 1.0/x;

    return log(oneOverX+sqrt(oneOverX*oneOverX+1.0));
}

double acoth(double x)
{
    double oneOverX = 1.0/x;

    return 0.5*log((1.0+oneOverX)/(1.0-oneOverX));
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
    computedConstants[1] = 0.479425538604203;
    computedConstants[3] = 0.877582561890373;
    computedConstants[5] = 0.54630248984379;
    computedConstants[7] = 1.13949392732455;
    computedConstants[9] = 2.08582964293349;
    computedConstants[11] = 1.83048772171245;
    computedConstants[13] = 0.521095305493747;
    computedConstants[15] = 1.12762596520638;
    computedConstants[17] = 0.46211715726001;
    computedConstants[19] = 0.886818883970074;
    computedConstants[21] = 1.91903475133494;
    computedConstants[23] = 2.16395341373865;
    computedConstants[25] = 0.523598775598299;
    computedConstants[27] = 1.0471975511966;
    computedConstants[29] = 0.463647609000806;
    computedConstants[31] = 0.84106867056793;
    computedConstants[33] = 0.729727656226966;
    computedConstants[35] = 1.10714871779409;
    computedConstants[37] = 0.481211825059603;
    computedConstants[39] = 0.962423650119207;
    computedConstants[41] = 0.549306144334055;
    computedConstants[43] = 1.31695789692482;
    computedConstants[45] = 1.44363547517881;
    computedConstants[47] = 0.80471895621705;
}

void computeComputedConstants(double *constants, double *computedConstants, double *algebraicVariables)
{
    computedConstants[0] = sin(constants[0]);
    computedConstants[2] = cos(constants[0]);
    computedConstants[4] = tan(constants[0]);
    computedConstants[6] = sec(constants[0]);
    computedConstants[8] = csc(constants[0]);
    computedConstants[10] = cot(constants[0]);
    computedConstants[12] = sinh(constants[0]);
    computedConstants[14] = cosh(constants[0]);
    computedConstants[16] = tanh(constants[0]);
    computedConstants[18] = sech(constants[0]);
    computedConstants[20] = csch(constants[0]);
    computedConstants[22] = coth(constants[0]);
    computedConstants[24] = asin(constants[0]);
    computedConstants[26] = acos(constants[0]);
    computedConstants[28] = atan(constants[0]);
    computedConstants[30] = asec(constants[0]);
    computedConstants[32] = acsc(constants[0]);
    computedConstants[34] = acot(constants[0]);
    computedConstants[36] = asinh(constants[0]);
    computedConstants[38] = acosh(constants[0]);
    computedConstants[40] = atanh(constants[0]);
    computedConstants[42] = asech(constants[0]);
    computedConstants[44] = acsch(constants[0]);
    computedConstants[46] = acoth(constants[0]);
}

void computeVariables(double *constants, double *computedConstants, double *algebraicVariables)
{
}

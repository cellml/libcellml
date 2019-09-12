/* The content of this file was generated using the C profile of libCellML 0.2.0. */

#include <math.h>
#include <stddef.h>
#include <stdlib.h>

const char LIBCELLML_VERSION[] = "0.2.0";

const size_t STATE_COUNT = 1;
const size_t VARIABLE_COUNT = 186;

struct VariableInfo {
    char component[13];
    char name[38];
    char units[14];
};

const struct VariableInfo VOI_INFO = {"my_component", "t", "second"};

const struct VariableInfo STATE_INFO[] = {
    {"my_component", "x", "dimensionless"}
};

const struct VariableInfo VARIABLE_INFO[] = {
    {"my_component", "m", "dimensionless"},
    {"my_component", "n", "dimensionless"},
    {"my_component", "o", "dimensionless"},
    {"my_component", "p", "dimensionless"},
    {"my_component", "q", "dimensionless"},
    {"my_component", "r", "dimensionless"},
    {"my_component", "s", "dimensionless"},
    {"my_component", "eqnCnInteger", "dimensionless"},
    {"my_component", "eqnCnDouble", "dimensionless"},
    {"my_component", "eqnCnIntegerWithExponent", "dimensionless"},
    {"my_component", "eqnCnDoubleWithExponent", "dimensionless"},
    {"my_component", "eqnTrue", "dimensionless"},
    {"my_component", "eqnFalse", "dimensionless"},
    {"my_component", "eqnExponentiale", "dimensionless"},
    {"my_component", "eqnPi", "dimensionless"},
    {"my_component", "eqnInfinity", "dimensionless"},
    {"my_component", "eqnNotanumber", "dimensionless"},
    {"my_component", "eqnEq", "dimensionless"},
    {"my_component", "eqnEqCoverageParentheses", "dimensionless"},
    {"my_component", "eqnNeq", "dimensionless"},
    {"my_component", "eqnNeqCoverageParentheses", "dimensionless"},
    {"my_component", "eqnLt", "dimensionless"},
    {"my_component", "eqnLeq", "dimensionless"},
    {"my_component", "eqnGt", "dimensionless"},
    {"my_component", "eqnGeq", "dimensionless"},
    {"my_component", "eqnAnd", "dimensionless"},
    {"my_component", "eqnAndMultiple", "dimensionless"},
    {"my_component", "eqnAndParentheses", "dimensionless"},
    {"my_component", "eqnAndParenthesesLeftPlusWith", "dimensionless"},
    {"my_component", "eqnAndParenthesesLeftPlusWithout", "dimensionless"},
    {"my_component", "eqnAndParenthesesLeftMinusWith", "dimensionless"},
    {"my_component", "eqnAndParenthesesLeftMinusWithout", "dimensionless"},
    {"my_component", "eqnAndParenthesesLeftPower", "dimensionless"},
    {"my_component", "eqnAndParenthesesLeftRoot", "dimensionless"},
    {"my_component", "eqnAndParenthesesRightPlusWith", "dimensionless"},
    {"my_component", "eqnAndParenthesesRightPlusWithout", "dimensionless"},
    {"my_component", "eqnAndParenthesesRightMinusWith", "dimensionless"},
    {"my_component", "eqnAndParenthesesRightMinusWithout", "dimensionless"},
    {"my_component", "eqnAndParenthesesRightPower", "dimensionless"},
    {"my_component", "eqnAndParenthesesRightRoot", "dimensionless"},
    {"my_component", "eqnOr", "dimensionless"},
    {"my_component", "eqnOrMultiple", "dimensionless"},
    {"my_component", "eqnOrParentheses", "dimensionless"},
    {"my_component", "eqnOrParenthesesLeftPlusWith", "dimensionless"},
    {"my_component", "eqnOrParenthesesLeftPlusWithout", "dimensionless"},
    {"my_component", "eqnOrParenthesesLeftMinusWith", "dimensionless"},
    {"my_component", "eqnOrParenthesesLeftMinusWithout", "dimensionless"},
    {"my_component", "eqnOrParenthesesLeftPower", "dimensionless"},
    {"my_component", "eqnOrParenthesesLeftRoot", "dimensionless"},
    {"my_component", "eqnOrParenthesesRightPlusWith", "dimensionless"},
    {"my_component", "eqnOrParenthesesRightPlusWithout", "dimensionless"},
    {"my_component", "eqnOrParenthesesRightMinusWith", "dimensionless"},
    {"my_component", "eqnOrParenthesesRightMinusWithout", "dimensionless"},
    {"my_component", "eqnOrParenthesesRightPower", "dimensionless"},
    {"my_component", "eqnOrParenthesesRightRoot", "dimensionless"},
    {"my_component", "eqnXor", "dimensionless"},
    {"my_component", "eqnXorMultiple", "dimensionless"},
    {"my_component", "eqnXorParentheses", "dimensionless"},
    {"my_component", "eqnXorParenthesesLeftPlusWith", "dimensionless"},
    {"my_component", "eqnXorParenthesesLeftPlusWithout", "dimensionless"},
    {"my_component", "eqnXorParenthesesLeftMinusWith", "dimensionless"},
    {"my_component", "eqnXorParenthesesLeftMinusWithout", "dimensionless"},
    {"my_component", "eqnXorParenthesesLeftPower", "dimensionless"},
    {"my_component", "eqnXorParenthesesLeftRoot", "dimensionless"},
    {"my_component", "eqnXorParenthesesRightPlusWith", "dimensionless"},
    {"my_component", "eqnXorParenthesesRightPlusWithout", "dimensionless"},
    {"my_component", "eqnXorParenthesesRightMinusWith", "dimensionless"},
    {"my_component", "eqnXorParenthesesRightMinusWithout", "dimensionless"},
    {"my_component", "eqnXorParenthesesRightPower", "dimensionless"},
    {"my_component", "eqnXorParenthesesRightRoot", "dimensionless"},
    {"my_component", "eqnNot", "dimensionless"},
    {"my_component", "eqnPlus", "dimensionless"},
    {"my_component", "eqnPlusMultiple", "dimensionless"},
    {"my_component", "eqnPlusParentheses", "dimensionless"},
    {"my_component", "eqnPlusUnary", "dimensionless"},
    {"my_component", "eqnMinus", "dimensionless"},
    {"my_component", "eqnMinusParentheses", "dimensionless"},
    {"my_component", "eqnMinusParenthesesPlusWith", "dimensionless"},
    {"my_component", "eqnMinusParenthesesPlusWithout", "dimensionless"},
    {"my_component", "eqnMinusUnary", "dimensionless"},
    {"my_component", "eqnMinusUnaryParentheses", "dimensionless"},
    {"my_component", "eqnTimes", "dimensionless"},
    {"my_component", "eqnTimesMultiple", "dimensionless"},
    {"my_component", "eqnTimesParentheses", "dimensionless"},
    {"my_component", "eqnTimesParenthesesLeftPlusWith", "dimensionless"},
    {"my_component", "eqnTimesParenthesesLeftPlusWithout", "dimensionless"},
    {"my_component", "eqnTimesParenthesesLeftMinusWith", "dimensionless"},
    {"my_component", "eqnTimesParenthesesLeftMinusWithout", "dimensionless"},
    {"my_component", "eqnTimesParenthesesRightPlusWith", "dimensionless"},
    {"my_component", "eqnTimesParenthesesRightPlusWithout", "dimensionless"},
    {"my_component", "eqnTimesParenthesesRightMinusWith", "dimensionless"},
    {"my_component", "eqnTimesParenthesesRightMinusWithout", "dimensionless"},
    {"my_component", "eqnDivide", "dimensionless"},
    {"my_component", "eqnDivideParentheses", "dimensionless"},
    {"my_component", "eqnDivideParenthesesLeftPlusWith", "dimensionless"},
    {"my_component", "eqnDivideParenthesesLeftPlusWithout", "dimensionless"},
    {"my_component", "eqnDivideParenthesesLeftMinusWith", "dimensionless"},
    {"my_component", "eqnDivideParenthesesLeftMinusWithout", "dimensionless"},
    {"my_component", "eqnDivideParenthesesRightPlusWith", "dimensionless"},
    {"my_component", "eqnDivideParenthesesRightPlusWithout", "dimensionless"},
    {"my_component", "eqnDivideParenthesesRightMinusWith", "dimensionless"},
    {"my_component", "eqnDivideParenthesesRightMinusWithout", "dimensionless"},
    {"my_component", "eqnDivideParenthesesRightTimes", "dimensionless"},
    {"my_component", "eqnDivideParenthesesRightDivide", "dimensionless"},
    {"my_component", "eqnPowerSqrt", "dimensionless"},
    {"my_component", "eqnPowerSqr", "dimensionless"},
    {"my_component", "eqnPowerCube", "dimensionless"},
    {"my_component", "eqnPowerCi", "dimensionless"},
    {"my_component", "eqnPowerParentheses", "dimensionless"},
    {"my_component", "eqnPowerParenthesesLeftPlusWith", "dimensionless"},
    {"my_component", "eqnPowerParenthesesLeftPlusWithout", "dimensionless"},
    {"my_component", "eqnPowerParenthesesLeftMinusWith", "dimensionless"},
    {"my_component", "eqnPowerParenthesesLeftMinusWithout", "dimensionless"},
    {"my_component", "eqnPowerParenthesesLeftTimes", "dimensionless"},
    {"my_component", "eqnPowerParenthesesLeftDivide", "dimensionless"},
    {"my_component", "eqnPowerParenthesesRightPlusWith", "dimensionless"},
    {"my_component", "eqnPowerParenthesesRightPlusWithout", "dimensionless"},
    {"my_component", "eqnPowerParenthesesRightMinusWith", "dimensionless"},
    {"my_component", "eqnPowerParenthesesRightMinusWithout", "dimensionless"},
    {"my_component", "eqnPowerParenthesesRightTimes", "dimensionless"},
    {"my_component", "eqnPowerParenthesesRightDivide", "dimensionless"},
    {"my_component", "eqnPowerParenthesesRightPower", "dimensionless"},
    {"my_component", "eqnPowerParenthesesRightRoot", "dimensionless"},
    {"my_component", "eqnRootSqrt", "dimensionless"},
    {"my_component", "eqnRootSqrtOther", "dimensionless"},
    {"my_component", "eqnRootCube", "dimensionless"},
    {"my_component", "eqnRootCi", "dimensionless"},
    {"my_component", "eqnRootParentheses", "dimensionless"},
    {"my_component", "eqnRootParenthesesLeftPlusWith", "dimensionless"},
    {"my_component", "eqnRootParenthesesLeftPlusWithout", "dimensionless"},
    {"my_component", "eqnRootParenthesesLeftMinusWith", "dimensionless"},
    {"my_component", "eqnRootParenthesesLeftMinusWithout", "dimensionless"},
    {"my_component", "eqnRootParenthesesLeftTimes", "dimensionless"},
    {"my_component", "eqnRootParenthesesLeftDivide", "dimensionless"},
    {"my_component", "eqnRootParenthesesRightPlusWith", "dimensionless"},
    {"my_component", "eqnRootParenthesesRightPlusWithout", "dimensionless"},
    {"my_component", "eqnRootParenthesesRightMinusWith", "dimensionless"},
    {"my_component", "eqnRootParenthesesRightMinusWithout", "dimensionless"},
    {"my_component", "eqnRootParenthesesRightTimes", "dimensionless"},
    {"my_component", "eqnRootParenthesesRightDivide", "dimensionless"},
    {"my_component", "eqnRootParenthesesRightPower", "dimensionless"},
    {"my_component", "eqnRootParenthesesRightRoot", "dimensionless"},
    {"my_component", "eqnAbs", "dimensionless"},
    {"my_component", "eqnExp", "dimensionless"},
    {"my_component", "eqnLn", "dimensionless"},
    {"my_component", "eqnLog", "dimensionless"},
    {"my_component", "eqnLog2", "dimensionless"},
    {"my_component", "eqnLog10", "dimensionless"},
    {"my_component", "eqnLogCi", "dimensionless"},
    {"my_component", "eqnCeiling", "dimensionless"},
    {"my_component", "eqnFloor", "dimensionless"},
    {"my_component", "eqnMin", "dimensionless"},
    {"my_component", "eqnMinMultiple", "dimensionless"},
    {"my_component", "eqnMax", "dimensionless"},
    {"my_component", "eqnMaxMultiple", "dimensionless"},
    {"my_component", "eqnRem", "dimensionless"},
    {"my_component", "eqnSin", "dimensionless"},
    {"my_component", "eqnCos", "dimensionless"},
    {"my_component", "eqnTan", "dimensionless"},
    {"my_component", "eqnSec", "dimensionless"},
    {"my_component", "eqnCsc", "dimensionless"},
    {"my_component", "eqnCot", "dimensionless"},
    {"my_component", "eqnSinh", "dimensionless"},
    {"my_component", "eqnCosh", "dimensionless"},
    {"my_component", "eqnTanh", "dimensionless"},
    {"my_component", "eqnSech", "dimensionless"},
    {"my_component", "eqnCsch", "dimensionless"},
    {"my_component", "eqnCoth", "dimensionless"},
    {"my_component", "eqnArcsin", "dimensionless"},
    {"my_component", "eqnArccos", "dimensionless"},
    {"my_component", "eqnArctan", "dimensionless"},
    {"my_component", "eqnArcsec", "dimensionless"},
    {"my_component", "eqnArccsc", "dimensionless"},
    {"my_component", "eqnArccot", "dimensionless"},
    {"my_component", "eqnArcsinh", "dimensionless"},
    {"my_component", "eqnArccosh", "dimensionless"},
    {"my_component", "eqnArctanh", "dimensionless"},
    {"my_component", "eqnArcsech", "dimensionless"},
    {"my_component", "eqnArccsch", "dimensionless"},
    {"my_component", "eqnArccoth", "dimensionless"},
    {"my_component", "eqnPiecewisePiece", "dimensionless"},
    {"my_component", "eqnPiecewisePieceOtherwise", "dimensionless"},
    {"my_component", "eqnPiecewisePiecePiecePiece", "dimensionless"},
    {"my_component", "eqnPiecewisePiecePiecePieceOtherwise", "dimensionless"},
    {"my_component", "eqnWithPiecewise", "dimensionless"},
    {"my_component", "eqnCi", "dimensionless"}
};

double xor(double x, double y)
{
    return (x != 0.0) ^ (y != 0.0);
}

double min(double x, double y)
{
    return (x < y)?x:y;
}

double max(double x, double y)
{
    return (x > y)?x:y;
}

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

double * createStatesArray()
{
    return (double *) malloc(1 * sizeof(double));
}

double * createVariablesArray()
{
    return (double *) malloc(186 * sizeof(double));
}

void deleteArray(double *array)
{
    free(array);
}

void initializeConstants(double *states, double *variables)
{
    states[0] = 0.0;
    variables[0] = 1.0;
    variables[1] = 2.0;
    variables[2] = 3.0;
    variables[3] = 4.0;
    variables[4] = 5.0;
    variables[5] = 6.0;
    variables[6] = 7.0;
    variables[175] = 123.0;
    variables[176] = 123.456789;
    variables[177] = 123.0e99;
    variables[178] = 123.456789e99;
    variables[180] = 1.0;
    variables[181] = 0.0;
    variables[182] = 2.71828182845905;
    variables[183] = 3.14159265358979;
    variables[184] = 1.0/0.0;
    variables[185] = sqrt(-1.0);
}

void computeComputedConstants(double *variables)
{
    variables[7] = variables[0] == variables[1];
    variables[8] = variables[0]/(variables[1] == variables[1]);
    variables[9] = variables[0] != variables[1];
    variables[10] = variables[0]/(variables[1] != variables[2]);
    variables[11] = variables[0] < variables[1];
    variables[12] = variables[0] <= variables[1];
    variables[13] = variables[0] > variables[1];
    variables[14] = variables[0] >= variables[1];
    variables[15] = variables[0] && variables[1];
    variables[16] = variables[0] && variables[1] && variables[2];
    variables[17] = (variables[0] < variables[1]) && (variables[2] > variables[3]);
    variables[18] = (variables[0]+variables[1]) && (variables[2] > variables[3]);
    variables[19] = variables[0] && (variables[1] > variables[2]);
    variables[20] = (variables[0]-variables[1]) && (variables[2] > variables[3]);
    variables[21] = -variables[0] && (variables[1] > variables[2]);
    variables[22] = pow(variables[0], variables[1]) && (variables[2] > variables[3]);
    variables[23] = pow(variables[0], 1.0/variables[1]) && (variables[2] > variables[3]);
    variables[24] = (variables[0] < variables[1]) && (variables[2]+variables[3]);
    variables[25] = (variables[0] < variables[1]) && variables[2];
    variables[26] = (variables[0] < variables[1]) && (variables[2]-variables[3]);
    variables[27] = (variables[0] < variables[1]) && -variables[2];
    variables[28] = (variables[0] < variables[1]) && pow(variables[2], variables[3]);
    variables[29] = (variables[0] < variables[1]) && pow(variables[2], 1.0/variables[3]);
    variables[30] = variables[0] || variables[1];
    variables[31] = variables[0] || variables[1] || variables[2];
    variables[32] = (variables[0] < variables[1]) || (variables[2] > variables[3]);
    variables[33] = (variables[0]+variables[1]) || (variables[2] > variables[3]);
    variables[34] = variables[0] || (variables[1] > variables[2]);
    variables[35] = (variables[0]-variables[1]) || (variables[2] > variables[3]);
    variables[36] = -variables[0] || (variables[1] > variables[2]);
    variables[37] = pow(variables[0], variables[1]) || (variables[2] > variables[3]);
    variables[38] = pow(variables[0], 1.0/variables[1]) || (variables[2] > variables[3]);
    variables[39] = (variables[0] < variables[1]) || (variables[2]+variables[3]);
    variables[40] = (variables[0] < variables[1]) || variables[2];
    variables[41] = (variables[0] < variables[1]) || (variables[2]-variables[3]);
    variables[42] = (variables[0] < variables[1]) || -variables[2];
    variables[43] = (variables[0] < variables[1]) || pow(variables[2], variables[3]);
    variables[44] = (variables[0] < variables[1]) || pow(variables[2], 1.0/variables[3]);
    variables[45] = xor(variables[0], variables[1]);
    variables[46] = xor(variables[0], xor(variables[1], variables[2]));
    variables[47] = xor(variables[0] < variables[1], variables[2] > variables[3]);
    variables[48] = xor(variables[0]+variables[1], variables[2] > variables[3]);
    variables[49] = xor(variables[0], variables[1] > variables[2]);
    variables[50] = xor(variables[0]-variables[1], variables[2] > variables[3]);
    variables[51] = xor(-variables[0], variables[1] > variables[2]);
    variables[52] = xor(pow(variables[0], variables[1]), variables[2] > variables[3]);
    variables[53] = xor(pow(variables[0], 1.0/variables[1]), variables[2] > variables[3]);
    variables[54] = xor(variables[0] < variables[1], variables[2]+variables[3]);
    variables[55] = xor(variables[0] < variables[1], variables[2]);
    variables[56] = xor(variables[0] < variables[1], variables[2]-variables[3]);
    variables[57] = xor(variables[0] < variables[1], -variables[2]);
    variables[58] = xor(variables[0] < variables[1], pow(variables[2], variables[3]));
    variables[59] = xor(variables[0] < variables[1], pow(variables[2], 1.0/variables[3]));
    variables[60] = !variables[0];
    variables[61] = variables[0]+variables[1];
    variables[62] = variables[0]+variables[1]+variables[2];
    variables[63] = (variables[0] < variables[1])+(variables[2] > variables[3]);
    variables[64] = variables[0];
    variables[65] = variables[0]-variables[1];
    variables[66] = (variables[0] < variables[1])-(variables[2] > variables[3]);
    variables[67] = (variables[0] < variables[1])-(variables[2]+variables[3]);
    variables[68] = (variables[0] < variables[1])-variables[2];
    variables[69] = -variables[0];
    variables[70] = -(variables[0] < variables[1]);
    variables[71] = variables[0]*variables[1];
    variables[72] = variables[0]*variables[1]*variables[2];
    variables[73] = (variables[0] < variables[1])*(variables[2] > variables[3]);
    variables[74] = (variables[0]+variables[1])*(variables[2] > variables[3]);
    variables[75] = variables[0]*(variables[1] > variables[2]);
    variables[76] = (variables[0]-variables[1])*(variables[2] > variables[3]);
    variables[77] = -variables[0]*(variables[1] > variables[2]);
    variables[78] = (variables[0] < variables[1])*(variables[2]+variables[3]);
    variables[79] = (variables[0] < variables[1])*variables[2];
    variables[80] = (variables[0] < variables[1])*(variables[2]-variables[3]);
    variables[81] = (variables[0] < variables[1])*-variables[2];
    variables[82] = variables[0]/variables[1];
    variables[83] = (variables[0] < variables[1])/(variables[3] > variables[2]);
    variables[84] = (variables[0]+variables[1])/(variables[3] > variables[2]);
    variables[85] = variables[0]/(variables[2] > variables[1]);
    variables[86] = (variables[0]-variables[1])/(variables[3] > variables[2]);
    variables[87] = -variables[0]/(variables[2] > variables[1]);
    variables[88] = (variables[0] < variables[1])/(variables[2]+variables[3]);
    variables[89] = (variables[0] < variables[1])/variables[2];
    variables[90] = (variables[0] < variables[1])/(variables[2]-variables[3]);
    variables[91] = (variables[0] < variables[1])/-variables[2];
    variables[92] = (variables[0] < variables[1])/(variables[2]*variables[3]);
    variables[93] = (variables[0] < variables[1])/(variables[2]/variables[3]);
    variables[94] = sqrt(variables[0]);
    variables[95] = pow(variables[0], 2.0);
    variables[96] = pow(variables[0], 3.0);
    variables[97] = pow(variables[0], variables[1]);
    variables[98] = pow(variables[0] < variables[1], variables[2] > variables[3]);
    variables[99] = pow(variables[0]+variables[1], variables[2] > variables[3]);
    variables[100] = pow(variables[0], variables[1] > variables[2]);
    variables[101] = pow(variables[0]-variables[1], variables[2] > variables[3]);
    variables[102] = pow(-variables[0], variables[1] > variables[2]);
    variables[103] = pow(variables[0]*variables[1], variables[2] > variables[3]);
    variables[104] = pow(variables[0]/variables[1], variables[2] > variables[3]);
    variables[105] = pow(variables[0] < variables[1], variables[2]+variables[3]);
    variables[106] = pow(variables[0] < variables[1], variables[2]);
    variables[107] = pow(variables[0] < variables[1], variables[2]-variables[3]);
    variables[108] = pow(variables[0] < variables[1], -variables[2]);
    variables[109] = pow(variables[0] < variables[1], variables[2]*variables[3]);
    variables[110] = pow(variables[0] < variables[1], variables[2]/variables[3]);
    variables[111] = pow(variables[0] < variables[1], pow(variables[2], variables[3]));
    variables[112] = pow(variables[0] < variables[1], pow(variables[2], 1.0/variables[3]));
    variables[113] = sqrt(variables[0]);
    variables[114] = sqrt(variables[0]);
    variables[115] = pow(variables[0], 1.0/3.0);
    variables[116] = pow(variables[0], 1.0/variables[1]);
    variables[117] = pow(variables[0] < variables[1], 1.0/(variables[3] > variables[2]));
    variables[118] = pow(variables[0]+variables[1], 1.0/(variables[3] > variables[2]));
    variables[119] = pow(variables[0], 1.0/(variables[2] > variables[1]));
    variables[120] = pow(variables[0]-variables[1], 1.0/(variables[3] > variables[2]));
    variables[121] = pow(-variables[0], 1.0/(variables[2] > variables[1]));
    variables[122] = pow(variables[0]*variables[1], 1.0/(variables[3] > variables[2]));
    variables[123] = pow(variables[0]/variables[1], 1.0/(variables[3] > variables[2]));
    variables[124] = pow(variables[0] < variables[1], 1.0/(variables[2]+variables[3]));
    variables[125] = pow(variables[0] < variables[1], 1.0/variables[2]);
    variables[126] = pow(variables[0] < variables[1], 1.0/(variables[2]-variables[3]));
    variables[127] = pow(variables[0] < variables[1], 1.0/-variables[2]);
    variables[128] = pow(variables[0] < variables[1], 1.0/(variables[2]*variables[3]));
    variables[129] = pow(variables[0] < variables[1], 1.0/(variables[2]/variables[3]));
    variables[130] = pow(variables[0] < variables[1], 1.0/pow(variables[2], variables[3]));
    variables[131] = pow(variables[0] < variables[1], 1.0/pow(variables[2], 1.0/variables[3]));
    variables[132] = fabs(variables[0]);
    variables[133] = exp(variables[0]);
    variables[134] = log(variables[0]);
    variables[135] = log10(variables[0]);
    variables[136] = log(variables[0])/log(2.0);
    variables[137] = log10(variables[0]);
    variables[138] = log(variables[0])/log(variables[1]);
    variables[139] = ceil(variables[0]);
    variables[140] = floor(variables[0]);
    variables[141] = min(variables[0], variables[1]);
    variables[142] = min(variables[0], min(variables[1], variables[2]));
    variables[143] = max(variables[0], variables[1]);
    variables[144] = max(variables[0], max(variables[1], variables[2]));
    variables[145] = fmod(variables[0], variables[1]);
    variables[146] = sin(variables[0]);
    variables[147] = cos(variables[0]);
    variables[148] = tan(variables[0]);
    variables[149] = sec(variables[0]);
    variables[150] = csc(variables[0]);
    variables[151] = cot(variables[0]);
    variables[152] = sinh(variables[0]);
    variables[153] = cosh(variables[0]);
    variables[154] = tanh(variables[0]);
    variables[155] = sech(variables[0]);
    variables[156] = csch(variables[0]);
    variables[157] = coth(variables[0]);
    variables[158] = asin(variables[0]);
    variables[159] = acos(variables[0]);
    variables[160] = atan(variables[0]);
    variables[161] = asec(variables[0]);
    variables[162] = acsc(variables[0]);
    variables[163] = acot(variables[0]);
    variables[164] = asinh(variables[0]);
    variables[165] = acosh(variables[0]);
    variables[166] = atanh(variables[0]/2.0);
    variables[167] = asech(variables[0]);
    variables[168] = acsch(variables[0]);
    variables[169] = acoth(2.0*variables[0]);
    variables[170] = (variables[0] > variables[1])?variables[0]:sqrt(-1.0);
    variables[171] = (variables[0] > variables[1])?variables[0]:variables[2];
    variables[172] = (variables[0] > variables[1])?variables[0]:(variables[2] > variables[3])?variables[2]:(variables[4] > variables[5])?variables[4]:sqrt(-1.0);
    variables[173] = (variables[0] > variables[1])?variables[0]:(variables[2] > variables[3])?variables[2]:(variables[4] > variables[5])?variables[4]:variables[6];
    variables[174] = 123.0+((variables[0] > variables[1])?variables[0]:sqrt(-1.0));
    variables[179] = variables[0];
}

void computeRates(double voi, double *states, double *rates, double *variables)
{
    rates[0] = 1.0;
}

void computeVariables(double voi, double *states, double *rates, double *variables)
{
}

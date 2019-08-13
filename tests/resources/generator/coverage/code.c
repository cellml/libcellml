#include <stddef.h>
#include <stdlib.h>
#include <math.h>

const char version[] = "0.2.0";

struct VARIABLE_INFO {
    char name[32];
    char units[32];
};

const size_t STATE_VECTOR_SIZE = 1;
const size_t VARIABLE_VECTOR_SIZE = 185;
const struct VARIABLE_INFO VOI = {"t", "second"};

const struct VARIABLE_INFO STATE_VECTOR_INFORMATION_ARRAY[] = {
    {"x", "dimensionless"},
};

const struct VARIABLE_INFO VARIABLE_VECTOR_INFORMATION_ARRAY[] = {
    {"m", "dimensionless"},
    {"n", "dimensionless"},
    {"o", "dimensionless"},
    {"p", "dimensionless"},
    {"q", "dimensionless"},
    {"r", "dimensionless"},
    {"s", "dimensionless"},
    {"eqnCnInteger", "dimensionless"},
    {"eqnCnDouble", "dimensionless"},
    {"eqnCnIntegerWithExponent", "dimensionless"},
    {"eqnCnDoubleWithExponent", "dimensionless"},
    {"eqnTrue", "dimensionless"},
    {"eqnFalse", "dimensionless"},
    {"eqnExponentiale", "dimensionless"},
    {"eqnPi", "dimensionless"},
    {"eqnInfinity", "dimensionless"},
    {"eqnNotanumber", "dimensionless"},
    {"eqnEqEq", "dimensionless"},
    {"eqnEqEqCoverageParentheses", "dimensionless"},
    {"eqnNeq", "dimensionless"},
    {"eqnNeqCoverageParentheses", "dimensionless"},
    {"eqnLt", "dimensionless"},
    {"eqnLeq", "dimensionless"},
    {"eqnGt", "dimensionless"},
    {"eqnGeq", "dimensionless"},
    {"eqnAnd", "dimensionless"},
    {"eqnAndMultiple", "dimensionless"},
    {"eqnAndParentheses", "dimensionless"},
    {"eqnAndParenthesesLeftPlusWith", "dimensionless"},
    {"eqnAndParenthesesLeftPlusWithout", "dimensionless"},
    {"eqnAndParenthesesLeftMinusWith", "dimensionless"},
    {"eqnAndParenthesesLeftMinusWithout", "dimensionless"},
    {"eqnAndParenthesesLeftPower", "dimensionless"},
    {"eqnAndParenthesesLeftRoot", "dimensionless"},
    {"eqnAndParenthesesRightPlusWith", "dimensionless"},
    {"eqnAndParenthesesRightPlusWithout", "dimensionless"},
    {"eqnAndParenthesesRightMinusWith", "dimensionless"},
    {"eqnAndParenthesesRightMinusWithout", "dimensionless"},
    {"eqnAndParenthesesRightPower", "dimensionless"},
    {"eqnAndParenthesesRightRoot", "dimensionless"},
    {"eqnOr", "dimensionless"},
    {"eqnOrMultiple", "dimensionless"},
    {"eqnOrParentheses", "dimensionless"},
    {"eqnOrParenthesesLeftPlusWith", "dimensionless"},
    {"eqnOrParenthesesLeftPlusWithout", "dimensionless"},
    {"eqnOrParenthesesLeftMinusWith", "dimensionless"},
    {"eqnOrParenthesesLeftMinusWithout", "dimensionless"},
    {"eqnOrParenthesesLeftPower", "dimensionless"},
    {"eqnOrParenthesesLeftRoot", "dimensionless"},
    {"eqnOrParenthesesRightPlusWith", "dimensionless"},
    {"eqnOrParenthesesRightPlusWithout", "dimensionless"},
    {"eqnOrParenthesesRightMinusWith", "dimensionless"},
    {"eqnOrParenthesesRightMinusWithout", "dimensionless"},
    {"eqnOrParenthesesRightPower", "dimensionless"},
    {"eqnOrParenthesesRightRoot", "dimensionless"},
    {"eqnXor", "dimensionless"},
    {"eqnXorMultiple", "dimensionless"},
    {"eqnXorParentheses", "dimensionless"},
    {"eqnXorParenthesesLeftPlusWith", "dimensionless"},
    {"eqnXorParenthesesLeftPlusWithout", "dimensionless"},
    {"eqnXorParenthesesLeftMinusWith", "dimensionless"},
    {"eqnXorParenthesesLeftMinusWithout", "dimensionless"},
    {"eqnXorParenthesesLeftPower", "dimensionless"},
    {"eqnXorParenthesesLeftRoot", "dimensionless"},
    {"eqnXorParenthesesRightPlusWith", "dimensionless"},
    {"eqnXorParenthesesRightPlusWithout", "dimensionless"},
    {"eqnXorParenthesesRightMinusWith", "dimensionless"},
    {"eqnXorParenthesesRightMinusWithout", "dimensionless"},
    {"eqnXorParenthesesRightPower", "dimensionless"},
    {"eqnXorParenthesesRightRoot", "dimensionless"},
    {"eqnNot", "dimensionless"},
    {"eqnPlus", "dimensionless"},
    {"eqnPlusMultiple", "dimensionless"},
    {"eqnPlusParentheses", "dimensionless"},
    {"eqnPlusUnary", "dimensionless"},
    {"eqnMinus", "dimensionless"},
    {"eqnMinusParentheses", "dimensionless"},
    {"eqnMinusParenthesesPlusWith", "dimensionless"},
    {"eqnMinusParenthesesPlusWithout", "dimensionless"},
    {"eqnMinusUnary", "dimensionless"},
    {"eqnMinusUnaryParentheses", "dimensionless"},
    {"eqnTimes", "dimensionless"},
    {"eqnTimesMultiple", "dimensionless"},
    {"eqnTimesParentheses", "dimensionless"},
    {"eqnTimesParenthesesLeftPlusWith", "dimensionless"},
    {"eqnTimesParenthesesLeftPlusWithout", "dimensionless"},
    {"eqnTimesParenthesesLeftMinusWith", "dimensionless"},
    {"eqnTimesParenthesesLeftMinusWithout", "dimensionless"},
    {"eqnTimesParenthesesRightPlusWith", "dimensionless"},
    {"eqnTimesParenthesesRightPlusWithout", "dimensionless"},
    {"eqnTimesParenthesesRightMinusWith", "dimensionless"},
    {"eqnTimesParenthesesRightMinusWithout", "dimensionless"},
    {"eqnDivide", "dimensionless"},
    {"eqnDivideParentheses", "dimensionless"},
    {"eqnDivideParenthesesLeftPlusWith", "dimensionless"},
    {"eqnDivideParenthesesLeftPlusWithout", "dimensionless"},
    {"eqnDivideParenthesesLeftMinusWith", "dimensionless"},
    {"eqnDivideParenthesesLeftMinusWithout", "dimensionless"},
    {"eqnDivideParenthesesRightPlusWith", "dimensionless"},
    {"eqnDivideParenthesesRightPlusWithout", "dimensionless"},
    {"eqnDivideParenthesesRightMinusWith", "dimensionless"},
    {"eqnDivideParenthesesRightMinusWithout", "dimensionless"},
    {"eqnDivideParenthesesRightTimes", "dimensionless"},
    {"eqnDivideParenthesesRightDivide", "dimensionless"},
    {"eqnPowerSqrt", "dimensionless"},
    {"eqnPowerSqr", "dimensionless"},
    {"eqnPowerCube", "dimensionless"},
    {"eqnPowerCi", "dimensionless"},
    {"eqnPowerParentheses", "dimensionless"},
    {"eqnPowerParenthesesLeftPlusWith", "dimensionless"},
    {"eqnPowerParenthesesLeftPlusWithout", "dimensionless"},
    {"eqnPowerParenthesesLeftMinusWith", "dimensionless"},
    {"eqnPowerParenthesesLeftMinusWithout", "dimensionless"},
    {"eqnPowerParenthesesLeftTimes", "dimensionless"},
    {"eqnPowerParenthesesLeftDivide", "dimensionless"},
    {"eqnPowerParenthesesRightPlusWith", "dimensionless"},
    {"eqnPowerParenthesesRightPlusWithout", "dimensionless"},
    {"eqnPowerParenthesesRightMinusWith", "dimensionless"},
    {"eqnPowerParenthesesRightMinusWithout", "dimensionless"},
    {"eqnPowerParenthesesRightTimes", "dimensionless"},
    {"eqnPowerParenthesesRightDivide", "dimensionless"},
    {"eqnPowerParenthesesRightPower", "dimensionless"},
    {"eqnPowerParenthesesRightRoot", "dimensionless"},
    {"eqnRootSqrt", "dimensionless"},
    {"eqnRootSqrtOther", "dimensionless"},
    {"eqnRootCube", "dimensionless"},
    {"eqnRootCi", "dimensionless"},
    {"eqnRootParentheses", "dimensionless"},
    {"eqnRootParenthesesLeftPlusWith", "dimensionless"},
    {"eqnRootParenthesesLeftPlusWithout", "dimensionless"},
    {"eqnRootParenthesesLeftMinusWith", "dimensionless"},
    {"eqnRootParenthesesLeftMinusWithout", "dimensionless"},
    {"eqnRootParenthesesLeftTimes", "dimensionless"},
    {"eqnRootParenthesesLeftDivide", "dimensionless"},
    {"eqnRootParenthesesRightPlusWith", "dimensionless"},
    {"eqnRootParenthesesRightPlusWithout", "dimensionless"},
    {"eqnRootParenthesesRightMinusWith", "dimensionless"},
    {"eqnRootParenthesesRightMinusWithout", "dimensionless"},
    {"eqnRootParenthesesRightTimes", "dimensionless"},
    {"eqnRootParenthesesRightDivide", "dimensionless"},
    {"eqnRootParenthesesRightPower", "dimensionless"},
    {"eqnRootParenthesesRightRoot", "dimensionless"},
    {"eqnAbs", "dimensionless"},
    {"eqnExp", "dimensionless"},
    {"eqnLn", "dimensionless"},
    {"eqnLog", "dimensionless"},
    {"eqnLog2", "dimensionless"},
    {"eqnLog10", "dimensionless"},
    {"eqnLogCi", "dimensionless"},
    {"eqnCeiling", "dimensionless"},
    {"eqnFloor", "dimensionless"},
    {"eqnMin", "dimensionless"},
    {"eqnMinMultiple", "dimensionless"},
    {"eqnMax", "dimensionless"},
    {"eqnMaxMultiple", "dimensionless"},
    {"eqnRem", "dimensionless"},
    {"eqnSin", "dimensionless"},
    {"eqnCos", "dimensionless"},
    {"eqnTan", "dimensionless"},
    {"eqnSec", "dimensionless"},
    {"eqnCsc", "dimensionless"},
    {"eqnCot", "dimensionless"},
    {"eqnSinh", "dimensionless"},
    {"eqnCosh", "dimensionless"},
    {"eqnTanh", "dimensionless"},
    {"eqnSech", "dimensionless"},
    {"eqnCsch", "dimensionless"},
    {"eqnCoth", "dimensionless"},
    {"eqnArcsin", "dimensionless"},
    {"eqnArccos", "dimensionless"},
    {"eqnArctan", "dimensionless"},
    {"eqnArcsec", "dimensionless"},
    {"eqnArccsc", "dimensionless"},
    {"eqnArccot", "dimensionless"},
    {"eqnArcsinh", "dimensionless"},
    {"eqnArccosh", "dimensionless"},
    {"eqnArctanh", "dimensionless"},
    {"eqnArcsech", "dimensionless"},
    {"eqnArccsch", "dimensionless"},
    {"eqnArccoth", "dimensionless"},
    {"eqnPiecewisePiece", "dimensionless"},
    {"eqnPiecewisePieceOtherwise", "dimensionless"},
    {"eqnPiecewisePiecePiecePiece", "dimensionless"},
    {"eqnPiecewisePiecePiecePieceOtherwise", "dimensionless"},
    {"eqnCi", "dimensionless"},
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

double *createStateVector()
{
    return (double *)malloc(1 * sizeof (double));
}

double *createRateVector()
{
    return (double *)malloc(1 * sizeof (double));
}

double *createVariableVector()
{
    return (double *)malloc(185 * sizeof (double));
}

void freeVector(double *array)
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
    variables[174] = 123.0;
    variables[175] = 123.456789;
    variables[176] = 123.0e99;
    variables[177] = 123.456789e99;
    variables[179] = 1.0;
    variables[180] = 0.0;
    variables[181] = 2.71828182845905;
    variables[182] = 3.14159265358979;
    variables[183] = 1.0/0.0;
    variables[184] = sqrt(-1.0);
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
    variables[178] = variables[0];
}

void computeRates(double voi, double *states, double *rates, double *variables)
{
    rates[0] = 1.0;
}

void computeVariables(double voi, double *states, double *rates, double *variables)
{
}

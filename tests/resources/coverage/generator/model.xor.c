/* The content of this file was generated using a modified C profile of libCellML 0.5.0. */

#include "model.h"

#include <math.h>
#include <stdlib.h>

const char VERSION[] = "0.6.0.post0";
const char LIBCELLML_VERSION[] = "0.5.0";

const size_t STATE_COUNT = 1;
const size_t CONSTANT_COUNT = 7;
const size_t COMPUTED_CONSTANT_COUNT = 207;
const size_t ALGEBRAIC_COUNT = 5;
const size_t EXTERNAL_COUNT = 1;

const VariableInfo VOI_INFO = {"t", "second", "my_component"};

const VariableInfo STATE_INFO[] = {
    {"x", "dimensionless", "my_component"}
};

const VariableInfo CONSTANT_INFO[] = {
    {"m", "dimensionless", "my_component"},
    {"n", "dimensionless", "my_component"},
    {"o", "dimensionless", "my_component"},
    {"p", "dimensionless", "my_component"},
    {"q", "dimensionless", "my_component"},
    {"r", "dimensionless", "my_component"},
    {"s", "dimensionless", "my_component"}
};

const VariableInfo COMPUTED_CONSTANT_INFO[] = {
    {"eqnEq", "dimensionless", "my_component"},
    {"eqnEqCoverageParentheses", "dimensionless", "my_component"},
    {"eqnNeq", "dimensionless", "my_component"},
    {"eqnNeqCoverageParentheses", "dimensionless", "my_component"},
    {"eqnLt", "dimensionless", "my_component"},
    {"eqnLtCoverageParentheses", "dimensionless", "my_component"},
    {"eqnLeq", "dimensionless", "my_component"},
    {"eqnLeqCoverageParentheses", "dimensionless", "my_component"},
    {"eqnGt", "dimensionless", "my_component"},
    {"eqnGtCoverageParentheses", "dimensionless", "my_component"},
    {"eqnGeq", "dimensionless", "my_component"},
    {"eqnGeqCoverageParentheses", "dimensionless", "my_component"},
    {"eqnAnd", "dimensionless", "my_component"},
    {"eqnAndMultiple", "dimensionless", "my_component"},
    {"eqnAndParentheses", "dimensionless", "my_component"},
    {"eqnAndParenthesesLeftPlusWith", "dimensionless", "my_component"},
    {"eqnAndParenthesesLeftPlusWithout", "dimensionless", "my_component"},
    {"eqnAndParenthesesLeftMinusWith", "dimensionless", "my_component"},
    {"eqnAndParenthesesLeftMinusWithout", "dimensionless", "my_component"},
    {"eqnAndParenthesesLeftPower", "dimensionless", "my_component"},
    {"eqnAndParenthesesLeftRoot", "dimensionless", "my_component"},
    {"eqnAndParenthesesRightPlusWith", "dimensionless", "my_component"},
    {"eqnAndParenthesesRightPlusWithout", "dimensionless", "my_component"},
    {"eqnAndParenthesesRightMinusWith", "dimensionless", "my_component"},
    {"eqnAndParenthesesRightMinusWithout", "dimensionless", "my_component"},
    {"eqnAndParenthesesRightPower", "dimensionless", "my_component"},
    {"eqnAndParenthesesRightRoot", "dimensionless", "my_component"},
    {"eqnAndCoverageParentheses", "dimensionless", "my_component"},
    {"eqnOrParentheses", "dimensionless", "my_component"},
    {"eqnOrParenthesesLeftPlusWith", "dimensionless", "my_component"},
    {"eqnOrParenthesesLeftPlusWithout", "dimensionless", "my_component"},
    {"eqnOrParenthesesLeftMinusWith", "dimensionless", "my_component"},
    {"eqnOrParenthesesLeftMinusWithout", "dimensionless", "my_component"},
    {"eqnOrParenthesesLeftPower", "dimensionless", "my_component"},
    {"eqnOrParenthesesLeftRoot", "dimensionless", "my_component"},
    {"eqnOrParenthesesRightPlusWith", "dimensionless", "my_component"},
    {"eqnOrParenthesesRightPlusWithout", "dimensionless", "my_component"},
    {"eqnOrParenthesesRightMinusWith", "dimensionless", "my_component"},
    {"eqnOrParenthesesRightMinusWithout", "dimensionless", "my_component"},
    {"eqnOrParenthesesRightPower", "dimensionless", "my_component"},
    {"eqnOrParenthesesRightRoot", "dimensionless", "my_component"},
    {"eqnOrCoverageParentheses", "dimensionless", "my_component"},
    {"eqnXor", "dimensionless", "my_component"},
    {"eqnXorMultiple", "dimensionless", "my_component"},
    {"eqnXorParentheses", "dimensionless", "my_component"},
    {"eqnXorParenthesesLeftPlusWith", "dimensionless", "my_component"},
    {"eqnXorParenthesesLeftPlusWithout", "dimensionless", "my_component"},
    {"eqnXorParenthesesLeftMinusWith", "dimensionless", "my_component"},
    {"eqnXorParenthesesLeftMinusWithout", "dimensionless", "my_component"},
    {"eqnXorParenthesesLeftPower", "dimensionless", "my_component"},
    {"eqnXorParenthesesLeftRoot", "dimensionless", "my_component"},
    {"eqnXorParenthesesRightPlusWith", "dimensionless", "my_component"},
    {"eqnXorParenthesesRightPlusWithout", "dimensionless", "my_component"},
    {"eqnXorParenthesesRightMinusWith", "dimensionless", "my_component"},
    {"eqnXorParenthesesRightMinusWithout", "dimensionless", "my_component"},
    {"eqnXorParenthesesRightPower", "dimensionless", "my_component"},
    {"eqnXorParenthesesRightRoot", "dimensionless", "my_component"},
    {"eqnNot", "dimensionless", "my_component"},
    {"eqnPlusMultiple", "dimensionless", "my_component"},
    {"eqnPlusParentheses", "dimensionless", "my_component"},
    {"eqnPlusUnary", "dimensionless", "my_component"},
    {"eqnMinus", "dimensionless", "my_component"},
    {"eqnMinusParentheses", "dimensionless", "my_component"},
    {"eqnMinusParenthesesPlusWith", "dimensionless", "my_component"},
    {"eqnMinusParenthesesPlusWithout", "dimensionless", "my_component"},
    {"eqnMinusParenthesesDirectUnaryMinus", "dimensionless", "my_component"},
    {"eqnMinusParenthesesIndirectUnaryMinus", "dimensionless", "my_component"},
    {"eqnMinusUnary", "dimensionless", "my_component"},
    {"eqnMinusUnaryParentheses", "dimensionless", "my_component"},
    {"eqnTimes", "dimensionless", "my_component"},
    {"eqnTimesMultiple", "dimensionless", "my_component"},
    {"eqnTimesParentheses", "dimensionless", "my_component"},
    {"eqnTimesParenthesesLeftPlusWith", "dimensionless", "my_component"},
    {"eqnTimesParenthesesLeftPlusWithout", "dimensionless", "my_component"},
    {"eqnTimesParenthesesLeftMinusWith", "dimensionless", "my_component"},
    {"eqnTimesParenthesesLeftMinusWithout", "dimensionless", "my_component"},
    {"eqnTimesParenthesesRightPlusWith", "dimensionless", "my_component"},
    {"eqnTimesParenthesesRightPlusWithout", "dimensionless", "my_component"},
    {"eqnTimesParenthesesRightMinusWith", "dimensionless", "my_component"},
    {"eqnTimesParenthesesRightMinusWithout", "dimensionless", "my_component"},
    {"eqnDivide", "dimensionless", "my_component"},
    {"eqnDivideParentheses", "dimensionless", "my_component"},
    {"eqnDivideParenthesesLeftPlusWith", "dimensionless", "my_component"},
    {"eqnDivideParenthesesLeftPlusWithout", "dimensionless", "my_component"},
    {"eqnDivideParenthesesLeftMinusWith", "dimensionless", "my_component"},
    {"eqnDivideParenthesesLeftMinusWithout", "dimensionless", "my_component"},
    {"eqnDivideParenthesesRightPlusWith", "dimensionless", "my_component"},
    {"eqnDivideParenthesesRightPlusWithout", "dimensionless", "my_component"},
    {"eqnDivideParenthesesRightMinusWith", "dimensionless", "my_component"},
    {"eqnDivideParenthesesRightMinusWithout", "dimensionless", "my_component"},
    {"eqnDivideParenthesesRightTimes", "dimensionless", "my_component"},
    {"eqnDivideParenthesesRightDivide", "dimensionless", "my_component"},
    {"eqnPowerSqrt", "dimensionless", "my_component"},
    {"eqnPowerSqr", "dimensionless", "my_component"},
    {"eqnPowerCube", "dimensionless", "my_component"},
    {"eqnPowerCi", "dimensionless", "my_component"},
    {"eqnPowerParentheses", "dimensionless", "my_component"},
    {"eqnPowerParenthesesLeftPlusWith", "dimensionless", "my_component"},
    {"eqnPowerParenthesesLeftPlusWithout", "dimensionless", "my_component"},
    {"eqnPowerParenthesesLeftMinusWith", "dimensionless", "my_component"},
    {"eqnPowerParenthesesLeftMinusWithout", "dimensionless", "my_component"},
    {"eqnPowerParenthesesLeftTimes", "dimensionless", "my_component"},
    {"eqnPowerParenthesesLeftDivide", "dimensionless", "my_component"},
    {"eqnPowerParenthesesRightPlusWith", "dimensionless", "my_component"},
    {"eqnPowerParenthesesRightPlusWithout", "dimensionless", "my_component"},
    {"eqnPowerParenthesesRightMinusWith", "dimensionless", "my_component"},
    {"eqnPowerParenthesesRightMinusWithout", "dimensionless", "my_component"},
    {"eqnPowerParenthesesRightTimes", "dimensionless", "my_component"},
    {"eqnPowerParenthesesRightDivide", "dimensionless", "my_component"},
    {"eqnPowerParenthesesRightPower", "dimensionless", "my_component"},
    {"eqnPowerParenthesesRightRoot", "dimensionless", "my_component"},
    {"eqnRootSqrt", "dimensionless", "my_component"},
    {"eqnRootSqrtOther", "dimensionless", "my_component"},
    {"eqnRootSqr", "dimensionless", "my_component"},
    {"eqnRootCube", "dimensionless", "my_component"},
    {"eqnRootCi", "dimensionless", "my_component"},
    {"eqnRootParentheses", "dimensionless", "my_component"},
    {"eqnRootParenthesesLeftPlusWith", "dimensionless", "my_component"},
    {"eqnRootParenthesesLeftPlusWithout", "dimensionless", "my_component"},
    {"eqnRootParenthesesLeftMinusWith", "dimensionless", "my_component"},
    {"eqnRootParenthesesLeftMinusWithout", "dimensionless", "my_component"},
    {"eqnRootParenthesesLeftTimes", "dimensionless", "my_component"},
    {"eqnRootParenthesesLeftDivide", "dimensionless", "my_component"},
    {"eqnRootParenthesesRightPlusWith", "dimensionless", "my_component"},
    {"eqnRootParenthesesRightPlusWithout", "dimensionless", "my_component"},
    {"eqnRootParenthesesRightMinusWith", "dimensionless", "my_component"},
    {"eqnRootParenthesesRightMinusWithout", "dimensionless", "my_component"},
    {"eqnRootParenthesesRightTimes", "dimensionless", "my_component"},
    {"eqnRootParenthesesRightDivide", "dimensionless", "my_component"},
    {"eqnRootParenthesesRightPower", "dimensionless", "my_component"},
    {"eqnRootParenthesesRightRoot", "dimensionless", "my_component"},
    {"eqnAbs", "dimensionless", "my_component"},
    {"eqnExp", "dimensionless", "my_component"},
    {"eqnLn", "dimensionless", "my_component"},
    {"eqnLog", "dimensionless", "my_component"},
    {"eqnLog2", "dimensionless", "my_component"},
    {"eqnLog10", "dimensionless", "my_component"},
    {"eqnLogCi", "dimensionless", "my_component"},
    {"eqnCeiling", "dimensionless", "my_component"},
    {"eqnFloor", "dimensionless", "my_component"},
    {"eqnMin", "dimensionless", "my_component"},
    {"eqnMinMultiple", "dimensionless", "my_component"},
    {"eqnMax", "dimensionless", "my_component"},
    {"eqnMaxMultiple", "dimensionless", "my_component"},
    {"eqnRem", "dimensionless", "my_component"},
    {"eqnSin", "dimensionless", "my_component"},
    {"eqnCos", "dimensionless", "my_component"},
    {"eqnTan", "dimensionless", "my_component"},
    {"eqnSec", "dimensionless", "my_component"},
    {"eqnCsc", "dimensionless", "my_component"},
    {"eqnCot", "dimensionless", "my_component"},
    {"eqnSinh", "dimensionless", "my_component"},
    {"eqnCosh", "dimensionless", "my_component"},
    {"eqnTanh", "dimensionless", "my_component"},
    {"eqnSech", "dimensionless", "my_component"},
    {"eqnCsch", "dimensionless", "my_component"},
    {"eqnCoth", "dimensionless", "my_component"},
    {"eqnArcsin", "dimensionless", "my_component"},
    {"eqnArccos", "dimensionless", "my_component"},
    {"eqnArctan", "dimensionless", "my_component"},
    {"eqnArcsec", "dimensionless", "my_component"},
    {"eqnArccsc", "dimensionless", "my_component"},
    {"eqnArccot", "dimensionless", "my_component"},
    {"eqnArcsinh", "dimensionless", "my_component"},
    {"eqnArccosh", "dimensionless", "my_component"},
    {"eqnArctanh", "dimensionless", "my_component"},
    {"eqnArcsech", "dimensionless", "my_component"},
    {"eqnArccsch", "dimensionless", "my_component"},
    {"eqnArccoth", "dimensionless", "my_component"},
    {"eqnPiecewise", "dimensionless", "my_component"},
    {"eqnPiecewisePiece", "dimensionless", "my_component"},
    {"eqnPiecewisePiece2", "dimensionless", "my_component"},
    {"eqnPiecewiseOtherwise", "dimensionless", "my_component"},
    {"eqnPiecewisePieceOtherwise", "dimensionless", "my_component"},
    {"eqnPiecewisePiecePiecePiece", "dimensionless", "my_component"},
    {"eqnPiecewisePiecePiecePiece2", "dimensionless", "my_component"},
    {"eqnPiecewisePiecePiecePieceOtherwise", "dimensionless", "my_component"},
    {"eqnWithPiecewise", "dimensionless", "my_component"},
    {"eqnWithPiecewise2", "dimensionless", "my_component"},
    {"eqnCnInteger", "dimensionless", "my_component"},
    {"eqnCnDouble", "dimensionless", "my_component"},
    {"eqnCnIntegerWithExponent", "dimensionless", "my_component"},
    {"eqnCnDoubleWithExponent", "dimensionless", "my_component"},
    {"eqnCi", "dimensionless", "my_component"},
    {"eqnTrue", "dimensionless", "my_component"},
    {"eqnFalse", "dimensionless", "my_component"},
    {"eqnExponentiale", "dimensionless", "my_component"},
    {"eqnPi", "dimensionless", "my_component"},
    {"eqnInfinity", "dimensionless", "my_component"},
    {"eqnNotanumber", "dimensionless", "my_component"},
    {"eqnCoverageForPlusOperator", "dimensionless", "my_component"},
    {"eqnCoverageForPlusOperator2", "dimensionless", "my_component"},
    {"eqnCoverageForMinusOperator", "dimensionless", "my_component"},
    {"eqnCoverageForMinusOperator2", "dimensionless", "my_component"},
    {"eqnCoverageForTimesOperator", "dimensionless", "my_component"},
    {"eqnCoverageForTimesOperator2", "dimensionless", "my_component"},
    {"eqnCoverageForDivideOperator", "dimensionless", "my_component"},
    {"eqnCoverageForDivideOperator2", "dimensionless", "my_component"},
    {"eqnCoverageForAndOperator", "dimensionless", "my_component"},
    {"eqnCoverageForOrOperator", "dimensionless", "my_component"},
    {"eqnCoverageForXorOperator", "dimensionless", "my_component"},
    {"eqnCoverageForPowerOperator", "dimensionless", "my_component"},
    {"eqnCoverageForRootOperator", "dimensionless", "my_component"},
    {"eqnCoverageForMinusUnary", "dimensionless", "my_component"},
    {"eqnCoverageForMinusUnary2", "dimensionless", "my_component"},
    {"eqnComputedConstant1", "dimensionless", "my_component"},
    {"eqnComputedConstant2", "dimensionless", "my_component"}
};

const VariableInfo ALGEBRAIC_INFO[] = {
    {"eqnOr", "dimensionless", "my_component"},
    {"eqnOrMultiple", "dimensionless", "my_component"},
    {"eqnXorCoverageParentheses", "dimensionless", "my_component"},
    {"eqnNlaVariable1", "dimensionless", "my_component"},
    {"eqnNlaVariable2", "dimensionless", "my_component"}
};

const VariableInfo EXTERNAL_INFO[] = {
    {"eqnPlus", "dimensionless", "my_component"}
};

double XOR(double x, double y)
{
    return (x != 0.0) ^ (y != 0.0);
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
    return acosh(1.0/x);
}

double acsch(double x)
{
    return asinh(1.0/x);
}

double acoth(double x)
{
    return atanh(1.0/x);
}

double * createStatesArray()
{
    double *res = (double *) malloc(STATE_COUNT*sizeof(double));

    for (size_t i = 0; i < STATE_COUNT; ++i) {
        res[i] = NAN;
    }

    return res;
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

double * createAlgebraicArray()
{
    double *res = (double *) malloc(ALGEBRAIC_COUNT*sizeof(double));

    for (size_t i = 0; i < ALGEBRAIC_COUNT; ++i) {
        res[i] = NAN;
    }

    return res;
}

double * createExternalsArray()
{
    double *res = (double *) malloc(EXTERNAL_COUNT*sizeof(double));

    for (size_t i = 0; i < EXTERNAL_COUNT; ++i) {
        res[i] = NAN;
    }

    return res;
}

void deleteArray(double *array)
{
    free(array);
}

typedef struct {
    double voi;
    double *states;
    double *rates;
    double *constants;
    double *computedConstants;
    double *algebraic;
    double *externals;
} RootFindingInfo;

extern void nlaSolve(void (*objectiveFunction)(double *, double *, void *),
                     double *u, size_t n, void *data);

void objectiveFunction0(double *u, double *f, void *data)
{
    double voi = ((RootFindingInfo *) data)->voi;
    double *states = ((RootFindingInfo *) data)->states;
    double *rates = ((RootFindingInfo *) data)->rates;
    double *constants = ((RootFindingInfo *) data)->constants;
    double *computedConstants = ((RootFindingInfo *) data)->computedConstants;
    double *algebraic = ((RootFindingInfo *) data)->algebraic;
    double *externals = ((RootFindingInfo *) data)->externals;

    algebraic[3] = u[0];
    algebraic[4] = u[1];

    f[0] = algebraic[3]+algebraic[4]+states[0]-0.0;
    f[1] = algebraic[3]-algebraic[4]-(computedConstants[205]+computedConstants[206]);
}

void findRoot0(double voi, double *states, double *rates, double *constants, double *computedConstants, double *algebraic, double *externals)
{
    RootFindingInfo rfi = { voi, states, rates, constants, computedConstants, algebraic, externals };
    double u[2];

    u[0] = algebraic[3];
    u[1] = algebraic[4];

    nlaSolve(objectiveFunction0, u, 2, &rfi);

    algebraic[3] = u[0];
    algebraic[4] = u[1];
}

void initialiseVariables(double *states, double *rates, double *constants, double *computedConstants, double *algebraic)
{
    states[0] = 0.0;
    constants[0] = 1.0;
    constants[1] = 2.0;
    constants[2] = 3.0;
    constants[3] = 4.0;
    constants[4] = 5.0;
    constants[5] = 6.0;
    constants[6] = 7.0;
    computedConstants[169] = NAN;
    computedConstants[179] = 123.0;
    computedConstants[180] = 123.456789;
    computedConstants[181] = 123.0e99;
    computedConstants[182] = 123.456789e99;
    computedConstants[184] = 1.0;
    computedConstants[185] = 0.0;
    computedConstants[186] = 2.71828182845905;
    computedConstants[187] = 3.14159265358979;
    computedConstants[188] = INFINITY;
    computedConstants[189] = NAN;
    computedConstants[205] = 1.0;
    computedConstants[206] = 3.0;
    algebraic[3] = 1.0;
    algebraic[4] = 2.0;
}

void computeComputedConstants(double *constants, double *computedConstants)
{
    computedConstants[0] = constants[0] == constants[1];
    computedConstants[1] = constants[0]/(constants[1] == constants[1]);
    computedConstants[2] = constants[0] != constants[1];
    computedConstants[3] = constants[0]/(constants[1] != constants[2]);
    computedConstants[4] = constants[0] < constants[1];
    computedConstants[5] = constants[0]/(constants[1] < constants[2]);
    computedConstants[6] = constants[0] <= constants[1];
    computedConstants[7] = constants[0]/(constants[1] <= constants[2]);
    computedConstants[8] = constants[0] > constants[1];
    computedConstants[9] = constants[0]/(constants[2] > constants[1]);
    computedConstants[10] = constants[0] >= constants[1];
    computedConstants[11] = constants[0]/(constants[2] >= constants[1]);
    computedConstants[12] = constants[0] && constants[1];
    computedConstants[13] = constants[0] && constants[1] && constants[2];
    computedConstants[14] = (constants[0] < constants[1]) && (constants[2] > constants[3]);
    computedConstants[15] = (constants[0]+constants[1]) && (constants[2] > constants[3]);
    computedConstants[16] = constants[0] && (constants[1] > constants[2]);
    computedConstants[17] = (constants[0]-constants[1]) && (constants[2] > constants[3]);
    computedConstants[18] = -constants[0] && (constants[1] > constants[2]);
    computedConstants[19] = pow(constants[0], constants[1]) && (constants[2] > constants[3]);
    computedConstants[20] = pow(constants[0], 1.0/constants[1]) && (constants[2] > constants[3]);
    computedConstants[21] = (constants[0] < constants[1]) && (constants[2]+constants[3]);
    computedConstants[22] = (constants[0] < constants[1]) && constants[2];
    computedConstants[23] = (constants[0] < constants[1]) && (constants[2]-constants[3]);
    computedConstants[24] = (constants[0] < constants[1]) && -constants[2];
    computedConstants[25] = (constants[0] < constants[1]) && pow(constants[2], constants[3]);
    computedConstants[26] = (constants[0] < constants[1]) && pow(constants[2], 1.0/constants[3]);
    computedConstants[27] = constants[0]/(constants[1] && constants[2]);
    computedConstants[28] = (constants[0] < constants[1]) || (constants[2] > constants[3]);
    computedConstants[29] = (constants[0]+constants[1]) || (constants[2] > constants[3]);
    computedConstants[30] = constants[0] || (constants[1] > constants[2]);
    computedConstants[31] = (constants[0]-constants[1]) || (constants[2] > constants[3]);
    computedConstants[32] = -constants[0] || (constants[1] > constants[2]);
    computedConstants[33] = pow(constants[0], constants[1]) || (constants[2] > constants[3]);
    computedConstants[34] = pow(constants[0], 1.0/constants[1]) || (constants[2] > constants[3]);
    computedConstants[35] = (constants[0] < constants[1]) || (constants[2]+constants[3]);
    computedConstants[36] = (constants[0] < constants[1]) || constants[2];
    computedConstants[37] = (constants[0] < constants[1]) || (constants[2]-constants[3]);
    computedConstants[38] = (constants[0] < constants[1]) || -constants[2];
    computedConstants[39] = (constants[0] < constants[1]) || pow(constants[2], constants[3]);
    computedConstants[40] = (constants[0] < constants[1]) || pow(constants[2], 1.0/constants[3]);
    computedConstants[41] = constants[0]/(constants[1] || constants[2]);
    computedConstants[42] = XOR(constants[0], constants[1]);
    computedConstants[43] = XOR(constants[0], XOR(constants[1], constants[2]));
    computedConstants[44] = XOR(constants[0] < constants[1], constants[2] > constants[3]);
    computedConstants[45] = XOR(constants[0]+constants[1], constants[2] > constants[3]);
    computedConstants[46] = XOR(constants[0], constants[1] > constants[2]);
    computedConstants[47] = XOR(constants[0]-constants[1], constants[2] > constants[3]);
    computedConstants[48] = XOR(-constants[0], constants[1] > constants[2]);
    computedConstants[49] = XOR(pow(constants[0], constants[1]), constants[2] > constants[3]);
    computedConstants[50] = XOR(pow(constants[0], 1.0/constants[1]), constants[2] > constants[3]);
    computedConstants[51] = XOR(constants[0] < constants[1], constants[2]+constants[3]);
    computedConstants[52] = XOR(constants[0] < constants[1], constants[2]);
    computedConstants[53] = XOR(constants[0] < constants[1], constants[2]-constants[3]);
    computedConstants[54] = XOR(constants[0] < constants[1], -constants[2]);
    computedConstants[55] = XOR(constants[0] < constants[1], pow(constants[2], constants[3]));
    computedConstants[56] = XOR(constants[0] < constants[1], pow(constants[2], 1.0/constants[3]));
    computedConstants[57] = !constants[0];
    computedConstants[58] = constants[0]+constants[1]+constants[2];
    computedConstants[59] = (constants[0] < constants[1])+(constants[2] > constants[3]);
    computedConstants[60] = constants[0];
    computedConstants[61] = constants[0]-constants[1];
    computedConstants[62] = (constants[0] < constants[1])-(constants[2] > constants[3]);
    computedConstants[63] = (constants[0] < constants[1])-(constants[2]+constants[3]);
    computedConstants[64] = (constants[0] < constants[1])-constants[2];
    computedConstants[65] = constants[0]-(-constants[1]);
    computedConstants[66] = constants[0]-(-constants[1]*constants[2]);
    computedConstants[67] = -constants[0];
    computedConstants[68] = -(constants[0] < constants[1]);
    computedConstants[69] = constants[0]*constants[1];
    computedConstants[70] = constants[0]*constants[1]*constants[2];
    computedConstants[71] = (constants[0] < constants[1])*(constants[2] > constants[3]);
    computedConstants[72] = (constants[0]+constants[1])*(constants[2] > constants[3]);
    computedConstants[73] = constants[0]*(constants[1] > constants[2]);
    computedConstants[74] = (constants[0]-constants[1])*(constants[2] > constants[3]);
    computedConstants[75] = -constants[0]*(constants[1] > constants[2]);
    computedConstants[76] = (constants[0] < constants[1])*(constants[2]+constants[3]);
    computedConstants[77] = (constants[0] < constants[1])*constants[2];
    computedConstants[78] = (constants[0] < constants[1])*(constants[2]-constants[3]);
    computedConstants[79] = (constants[0] < constants[1])*-constants[2];
    computedConstants[80] = constants[0]/constants[1];
    computedConstants[81] = (constants[0] < constants[1])/(constants[3] > constants[2]);
    computedConstants[82] = (constants[0]+constants[1])/(constants[3] > constants[2]);
    computedConstants[83] = constants[0]/(constants[2] > constants[1]);
    computedConstants[84] = (constants[0]-constants[1])/(constants[3] > constants[2]);
    computedConstants[85] = -constants[0]/(constants[2] > constants[1]);
    computedConstants[86] = (constants[0] < constants[1])/(constants[2]+constants[3]);
    computedConstants[87] = (constants[0] < constants[1])/constants[2];
    computedConstants[88] = (constants[0] < constants[1])/(constants[2]-constants[3]);
    computedConstants[89] = (constants[0] < constants[1])/-constants[2];
    computedConstants[90] = (constants[0] < constants[1])/(constants[2]*constants[3]);
    computedConstants[91] = (constants[0] < constants[1])/(constants[2]/constants[3]);
    computedConstants[92] = sqrt(constants[0]);
    computedConstants[93] = pow(constants[0], 2.0);
    computedConstants[94] = pow(constants[0], 3.0);
    computedConstants[95] = pow(constants[0], constants[1]);
    computedConstants[96] = pow(constants[0] <= constants[1], constants[2] >= constants[3]);
    computedConstants[97] = pow(constants[0]+constants[1], constants[2] >= constants[3]);
    computedConstants[98] = pow(constants[0], constants[1] >= constants[2]);
    computedConstants[99] = pow(constants[0]-constants[1], constants[2] >= constants[3]);
    computedConstants[100] = pow(-constants[0], constants[1] >= constants[2]);
    computedConstants[101] = pow(constants[0]*constants[1], constants[2] >= constants[3]);
    computedConstants[102] = pow(constants[0]/constants[1], constants[2] >= constants[3]);
    computedConstants[103] = pow(constants[0] <= constants[1], constants[2]+constants[3]);
    computedConstants[104] = pow(constants[0] <= constants[1], constants[2]);
    computedConstants[105] = pow(constants[0] <= constants[1], constants[2]-constants[3]);
    computedConstants[106] = pow(constants[0] <= constants[1], -constants[2]);
    computedConstants[107] = pow(constants[0] <= constants[1], constants[2]*constants[3]);
    computedConstants[108] = pow(constants[0] <= constants[1], constants[2]/constants[3]);
    computedConstants[109] = pow(constants[0] <= constants[1], pow(constants[2], constants[3]));
    computedConstants[110] = pow(constants[0] <= constants[1], pow(constants[2], 1.0/constants[3]));
    computedConstants[111] = sqrt(constants[0]);
    computedConstants[112] = sqrt(constants[0]);
    computedConstants[113] = pow(constants[0], 1.0/0.5);
    computedConstants[114] = pow(constants[0], 1.0/3.0);
    computedConstants[115] = pow(constants[0], 1.0/constants[1]);
    computedConstants[116] = pow(constants[0] < constants[1], 1.0/(constants[3] > constants[2]));
    computedConstants[117] = pow(constants[0]+constants[1], 1.0/(constants[3] > constants[2]));
    computedConstants[118] = pow(constants[0], 1.0/(constants[2] > constants[1]));
    computedConstants[119] = pow(constants[0]-constants[1], 1.0/(constants[3] > constants[2]));
    computedConstants[120] = pow(-constants[0], 1.0/(constants[2] > constants[1]));
    computedConstants[121] = pow(constants[0]*constants[1], 1.0/(constants[3] > constants[2]));
    computedConstants[122] = pow(constants[0]/constants[1], 1.0/(constants[3] > constants[2]));
    computedConstants[123] = pow(constants[0] < constants[1], 1.0/(constants[2]+constants[3]));
    computedConstants[124] = pow(constants[0] < constants[1], 1.0/constants[2]);
    computedConstants[125] = pow(constants[0] < constants[1], 1.0/(constants[2]-constants[3]));
    computedConstants[126] = pow(constants[0] < constants[1], 1.0/-constants[2]);
    computedConstants[127] = pow(constants[0] < constants[1], 1.0/(constants[2]*constants[3]));
    computedConstants[128] = pow(constants[0] < constants[1], 1.0/(constants[2]/constants[3]));
    computedConstants[129] = pow(constants[0] < constants[1], 1.0/pow(constants[2], constants[3]));
    computedConstants[130] = pow(constants[0] < constants[1], 1.0/pow(constants[2], 1.0/constants[3]));
    computedConstants[131] = fabs(constants[0]);
    computedConstants[132] = exp(constants[0]);
    computedConstants[133] = log(constants[0]);
    computedConstants[134] = log10(constants[0]);
    computedConstants[135] = log(constants[0])/log(2.0);
    computedConstants[136] = log10(constants[0]);
    computedConstants[137] = log(constants[0])/log(constants[1]);
    computedConstants[138] = ceil(constants[0]);
    computedConstants[139] = floor(constants[0]);
    computedConstants[140] = fmin(constants[0], constants[1]);
    computedConstants[141] = fmin(constants[0], fmin(constants[1], constants[2]));
    computedConstants[142] = fmax(constants[0], constants[1]);
    computedConstants[143] = fmax(constants[0], fmax(constants[1], constants[2]));
    computedConstants[144] = fmod(constants[0], constants[1]);
    computedConstants[145] = sin(constants[0]);
    computedConstants[146] = cos(constants[0]);
    computedConstants[147] = tan(constants[0]);
    computedConstants[148] = sec(constants[0]);
    computedConstants[149] = csc(constants[0]);
    computedConstants[150] = cot(constants[0]);
    computedConstants[151] = sinh(constants[0]);
    computedConstants[152] = cosh(constants[0]);
    computedConstants[153] = tanh(constants[0]);
    computedConstants[154] = sech(constants[0]);
    computedConstants[155] = csch(constants[0]);
    computedConstants[156] = coth(constants[0]);
    computedConstants[157] = asin(constants[0]);
    computedConstants[158] = acos(constants[0]);
    computedConstants[159] = atan(constants[0]);
    computedConstants[160] = asec(constants[0]);
    computedConstants[161] = acsc(constants[0]);
    computedConstants[162] = acot(constants[0]);
    computedConstants[163] = asinh(constants[0]);
    computedConstants[164] = acosh(constants[0]);
    computedConstants[165] = atanh(constants[0]/2.0);
    computedConstants[166] = asech(constants[0]);
    computedConstants[167] = acsch(constants[0]);
    computedConstants[168] = acoth(2.0*constants[0]);
    computedConstants[170] = (constants[0] > constants[1])?constants[0]:NAN;
    computedConstants[171] = (constants[0] < constants[1])?constants[0]:NAN;
    computedConstants[172] = constants[0];
    computedConstants[173] = (constants[0] > constants[1])?constants[0]:constants[2];
    computedConstants[174] = (constants[0] > constants[1])?constants[0]:(constants[2] > constants[3])?constants[2]:(constants[4] > constants[5])?constants[4]:NAN;
    computedConstants[175] = (constants[0] < constants[1])?constants[0]:(constants[2] > constants[3])?constants[2]:(constants[4] > constants[5])?constants[4]:NAN;
    computedConstants[176] = (constants[0] > constants[1])?constants[0]:(constants[2] > constants[3])?constants[2]:(constants[4] > constants[5])?constants[4]:constants[6];
    computedConstants[177] = 123.0+((constants[0] > constants[1])?constants[0]:NAN);
    computedConstants[178] = 123.0+((constants[0] < constants[1])?constants[0]:NAN);
    computedConstants[183] = constants[0];
    computedConstants[190] = (constants[0] && constants[1])+((constants[2] > constants[3])?constants[1]:NAN)+constants[4]+(constants[5] && constants[6]);
    computedConstants[191] = (constants[0] && constants[1])+((constants[2] < constants[3])?constants[1]:NAN)+constants[4]+(constants[5] && constants[6]);
    computedConstants[192] = (constants[0] && constants[1])-(((constants[2] > constants[3])?constants[1]:NAN)-(constants[4]-((constants[2] > constants[3])?constants[1]:NAN)))-(constants[5] && constants[6]);
    computedConstants[193] = (constants[0] && constants[1])-(((constants[2] < constants[3])?constants[1]:NAN)-(constants[4]-((constants[2] < constants[3])?constants[1]:NAN)))-(constants[5] && constants[6]);
    computedConstants[194] = (constants[0] && constants[1])*((constants[2] > constants[3])?constants[1]:NAN)*constants[4]*((constants[2] > constants[3])?constants[1]:NAN)*(constants[5] && constants[6]);
    computedConstants[195] = (constants[0] && constants[1])*((constants[2] < constants[3])?constants[1]:NAN)*constants[4]*((constants[2] < constants[3])?constants[1]:NAN)*(constants[5] && constants[6]);
    computedConstants[196] = (constants[0] && constants[1])/(((constants[2] > constants[3])?constants[1]:NAN)/(constants[4]/((constants[2] > constants[3])?constants[1]:NAN)));
    computedConstants[197] = (constants[0] && constants[1])/(((constants[2] < constants[3])?constants[1]:NAN)/(constants[4]/((constants[2] < constants[3])?constants[1]:NAN)));
    computedConstants[198] = (constants[0] || constants[1]) && XOR(constants[0], constants[1]) && ((constants[2] > constants[3])?constants[1]:NAN) && constants[4] && ((constants[2] > constants[3])?constants[1]:NAN) && XOR(constants[0], constants[1]) && (constants[0] || constants[1]);
    computedConstants[199] = (constants[0] && constants[1]) || XOR(constants[0], constants[1]) || ((constants[2] > constants[3])?constants[1]:NAN) || constants[4] || ((constants[2] > constants[3])?constants[1]:NAN) || XOR(constants[0], constants[1]) || (constants[0] && constants[1]);
    computedConstants[200] = XOR(constants[0] && constants[1], XOR(constants[0] || constants[1], XOR((constants[2] > constants[3])?constants[1]:NAN, XOR(XOR(XOR(constants[4], (constants[2] > constants[3])?constants[1]:NAN), constants[0] || constants[1]), constants[0] && constants[1]))));
    computedConstants[201] = pow(constants[0] && constants[1], pow((constants[2] > constants[3])?constants[1]:NAN, pow(pow(constants[4], (constants[2] > constants[3])?constants[1]:NAN), constants[0] && constants[1])));
    computedConstants[202] = pow(pow(pow(constants[0] && constants[1], 1.0/pow((constants[2] > constants[3])?constants[1]:NAN, 1.0/constants[4])), 1.0/((constants[2] > constants[3])?constants[1]:NAN)), 1.0/(constants[0] && constants[1]));
    computedConstants[203] = -(constants[0] && constants[1])+-((constants[2] > constants[3])?constants[1]:NAN);
    computedConstants[204] = -(constants[0] && constants[1])+-((constants[2] < constants[3])?constants[1]:NAN);
}

void computeRates(double voi, double *states, double *rates, double *constants, double *computedConstants, double *algebraic, double *externals, ExternalVariable externalVariable)
{
    rates[0] = 1.0;
}

void computeVariables(double voi, double *states, double *rates, double *constants, double *computedConstants, double *algebraic, double *externals, ExternalVariable externalVariable)
{
    algebraic[0] = states[0] || states[0];
    algebraic[1] = states[0] || states[0] || constants[0];
    algebraic[2] = constants[0]/XOR(constants[1], states[0]);
    externals[0] = externalVariable(voi, states, rates, constants, computedConstants, algebraic, externals, 0);
    findRoot0(voi, states, rates, constants, computedConstants, algebraic, externals);
}

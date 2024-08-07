/* The content of this file was generated using a modified C profile of libCellML 0.5.0. */

#include "model.h"

#include <math.h>
#include <stdlib.h>

const char VERSION[] = "0.6.0.post0";
const char LIBCELLML_VERSION[] = "0.5.0";

const size_t STATE_COUNT = 1;
const size_t CONSTANT_COUNT = 0;
const size_t COMPUTED_CONSTANT_COUNT = 0;
const size_t ALGEBRAIC_COUNT = 209;

const VariableInfo VOI_INFO = {"t", "second", "my_component", VARIABLE_OF_INTEGRATION};

const VariableInfo STATE_INFO[] = {
    {"x", "dimensionless", "my_component", STATE}
};

const VariableInfo VARIABLE_INFO[] = {
    {"eqnEq", "dimensionless", "my_component", COMPUTED_CONSTANT},
    {"m", "dimensionless", "my_component", CONSTANT},
    {"n", "dimensionless", "my_component", CONSTANT},
    {"eqnEqCoverageParentheses", "dimensionless", "my_component", COMPUTED_CONSTANT},
    {"eqnNeq", "dimensionless", "my_component", COMPUTED_CONSTANT},
    {"eqnNeqCoverageParentheses", "dimensionless", "my_component", COMPUTED_CONSTANT},
    {"o", "dimensionless", "my_component", CONSTANT},
    {"eqnLt", "dimensionless", "my_component", COMPUTED_CONSTANT},
    {"eqnLtCoverageParentheses", "dimensionless", "my_component", COMPUTED_CONSTANT},
    {"eqnLeq", "dimensionless", "my_component", COMPUTED_CONSTANT},
    {"eqnLeqCoverageParentheses", "dimensionless", "my_component", COMPUTED_CONSTANT},
    {"eqnGt", "dimensionless", "my_component", COMPUTED_CONSTANT},
    {"eqnGtCoverageParentheses", "dimensionless", "my_component", COMPUTED_CONSTANT},
    {"eqnGeq", "dimensionless", "my_component", COMPUTED_CONSTANT},
    {"eqnGeqCoverageParentheses", "dimensionless", "my_component", COMPUTED_CONSTANT},
    {"eqnAnd", "dimensionless", "my_component", COMPUTED_CONSTANT},
    {"eqnAndMultiple", "dimensionless", "my_component", COMPUTED_CONSTANT},
    {"eqnAndParentheses", "dimensionless", "my_component", COMPUTED_CONSTANT},
    {"p", "dimensionless", "my_component", CONSTANT},
    {"eqnAndParenthesesLeftPlusWith", "dimensionless", "my_component", COMPUTED_CONSTANT},
    {"eqnAndParenthesesLeftPlusWithout", "dimensionless", "my_component", COMPUTED_CONSTANT},
    {"eqnAndParenthesesLeftMinusWith", "dimensionless", "my_component", COMPUTED_CONSTANT},
    {"eqnAndParenthesesLeftMinusWithout", "dimensionless", "my_component", COMPUTED_CONSTANT},
    {"eqnAndParenthesesLeftPower", "dimensionless", "my_component", COMPUTED_CONSTANT},
    {"eqnAndParenthesesLeftRoot", "dimensionless", "my_component", COMPUTED_CONSTANT},
    {"eqnAndParenthesesRightPlusWith", "dimensionless", "my_component", COMPUTED_CONSTANT},
    {"eqnAndParenthesesRightPlusWithout", "dimensionless", "my_component", COMPUTED_CONSTANT},
    {"eqnAndParenthesesRightMinusWith", "dimensionless", "my_component", COMPUTED_CONSTANT},
    {"eqnAndParenthesesRightMinusWithout", "dimensionless", "my_component", COMPUTED_CONSTANT},
    {"eqnAndParenthesesRightPower", "dimensionless", "my_component", COMPUTED_CONSTANT},
    {"eqnAndParenthesesRightRoot", "dimensionless", "my_component", COMPUTED_CONSTANT},
    {"eqnAndCoverageParentheses", "dimensionless", "my_component", COMPUTED_CONSTANT},
    {"eqnOr", "dimensionless", "my_component", COMPUTED_CONSTANT},
    {"eqnOrMultiple", "dimensionless", "my_component", COMPUTED_CONSTANT},
    {"eqnOrParentheses", "dimensionless", "my_component", COMPUTED_CONSTANT},
    {"eqnOrParenthesesLeftPlusWith", "dimensionless", "my_component", COMPUTED_CONSTANT},
    {"eqnOrParenthesesLeftPlusWithout", "dimensionless", "my_component", COMPUTED_CONSTANT},
    {"eqnOrParenthesesLeftMinusWith", "dimensionless", "my_component", COMPUTED_CONSTANT},
    {"eqnOrParenthesesLeftMinusWithout", "dimensionless", "my_component", COMPUTED_CONSTANT},
    {"eqnOrParenthesesLeftPower", "dimensionless", "my_component", COMPUTED_CONSTANT},
    {"eqnOrParenthesesLeftRoot", "dimensionless", "my_component", COMPUTED_CONSTANT},
    {"eqnOrParenthesesRightPlusWith", "dimensionless", "my_component", COMPUTED_CONSTANT},
    {"eqnOrParenthesesRightPlusWithout", "dimensionless", "my_component", COMPUTED_CONSTANT},
    {"eqnOrParenthesesRightMinusWith", "dimensionless", "my_component", COMPUTED_CONSTANT},
    {"eqnOrParenthesesRightMinusWithout", "dimensionless", "my_component", COMPUTED_CONSTANT},
    {"eqnOrParenthesesRightPower", "dimensionless", "my_component", COMPUTED_CONSTANT},
    {"eqnOrParenthesesRightRoot", "dimensionless", "my_component", COMPUTED_CONSTANT},
    {"eqnOrCoverageParentheses", "dimensionless", "my_component", COMPUTED_CONSTANT},
    {"eqnXor", "dimensionless", "my_component", COMPUTED_CONSTANT},
    {"eqnXorMultiple", "dimensionless", "my_component", COMPUTED_CONSTANT},
    {"eqnXorParentheses", "dimensionless", "my_component", COMPUTED_CONSTANT},
    {"eqnXorParenthesesLeftPlusWith", "dimensionless", "my_component", COMPUTED_CONSTANT},
    {"eqnXorParenthesesLeftPlusWithout", "dimensionless", "my_component", COMPUTED_CONSTANT},
    {"eqnXorParenthesesLeftMinusWith", "dimensionless", "my_component", COMPUTED_CONSTANT},
    {"eqnXorParenthesesLeftMinusWithout", "dimensionless", "my_component", COMPUTED_CONSTANT},
    {"eqnXorParenthesesLeftPower", "dimensionless", "my_component", COMPUTED_CONSTANT},
    {"eqnXorParenthesesLeftRoot", "dimensionless", "my_component", COMPUTED_CONSTANT},
    {"eqnXorParenthesesRightPlusWith", "dimensionless", "my_component", COMPUTED_CONSTANT},
    {"eqnXorParenthesesRightPlusWithout", "dimensionless", "my_component", COMPUTED_CONSTANT},
    {"eqnXorParenthesesRightMinusWith", "dimensionless", "my_component", COMPUTED_CONSTANT},
    {"eqnXorParenthesesRightMinusWithout", "dimensionless", "my_component", COMPUTED_CONSTANT},
    {"eqnXorParenthesesRightPower", "dimensionless", "my_component", COMPUTED_CONSTANT},
    {"eqnXorParenthesesRightRoot", "dimensionless", "my_component", COMPUTED_CONSTANT},
    {"eqnXorCoverageParentheses", "dimensionless", "my_component", COMPUTED_CONSTANT},
    {"eqnNot", "dimensionless", "my_component", COMPUTED_CONSTANT},
    {"eqnPlus", "dimensionless", "my_component", COMPUTED_CONSTANT},
    {"eqnPlusMultiple", "dimensionless", "my_component", COMPUTED_CONSTANT},
    {"eqnPlusParentheses", "dimensionless", "my_component", COMPUTED_CONSTANT},
    {"eqnPlusUnary", "dimensionless", "my_component", COMPUTED_CONSTANT},
    {"eqnMinus", "dimensionless", "my_component", COMPUTED_CONSTANT},
    {"eqnMinusParentheses", "dimensionless", "my_component", COMPUTED_CONSTANT},
    {"eqnMinusParenthesesPlusWith", "dimensionless", "my_component", COMPUTED_CONSTANT},
    {"eqnMinusParenthesesPlusWithout", "dimensionless", "my_component", COMPUTED_CONSTANT},
    {"eqnMinusParenthesesDirectUnaryMinus", "dimensionless", "my_component", COMPUTED_CONSTANT},
    {"eqnMinusParenthesesIndirectUnaryMinus", "dimensionless", "my_component", COMPUTED_CONSTANT},
    {"eqnMinusUnary", "dimensionless", "my_component", COMPUTED_CONSTANT},
    {"eqnMinusUnaryParentheses", "dimensionless", "my_component", COMPUTED_CONSTANT},
    {"eqnTimes", "dimensionless", "my_component", COMPUTED_CONSTANT},
    {"eqnTimesMultiple", "dimensionless", "my_component", COMPUTED_CONSTANT},
    {"eqnTimesParentheses", "dimensionless", "my_component", COMPUTED_CONSTANT},
    {"eqnTimesParenthesesLeftPlusWith", "dimensionless", "my_component", COMPUTED_CONSTANT},
    {"eqnTimesParenthesesLeftPlusWithout", "dimensionless", "my_component", COMPUTED_CONSTANT},
    {"eqnTimesParenthesesLeftMinusWith", "dimensionless", "my_component", COMPUTED_CONSTANT},
    {"eqnTimesParenthesesLeftMinusWithout", "dimensionless", "my_component", COMPUTED_CONSTANT},
    {"eqnTimesParenthesesRightPlusWith", "dimensionless", "my_component", COMPUTED_CONSTANT},
    {"eqnTimesParenthesesRightPlusWithout", "dimensionless", "my_component", COMPUTED_CONSTANT},
    {"eqnTimesParenthesesRightMinusWith", "dimensionless", "my_component", COMPUTED_CONSTANT},
    {"eqnTimesParenthesesRightMinusWithout", "dimensionless", "my_component", COMPUTED_CONSTANT},
    {"eqnDivide", "dimensionless", "my_component", COMPUTED_CONSTANT},
    {"eqnDivideParentheses", "dimensionless", "my_component", COMPUTED_CONSTANT},
    {"eqnDivideParenthesesLeftPlusWith", "dimensionless", "my_component", COMPUTED_CONSTANT},
    {"eqnDivideParenthesesLeftPlusWithout", "dimensionless", "my_component", COMPUTED_CONSTANT},
    {"eqnDivideParenthesesLeftMinusWith", "dimensionless", "my_component", COMPUTED_CONSTANT},
    {"eqnDivideParenthesesLeftMinusWithout", "dimensionless", "my_component", COMPUTED_CONSTANT},
    {"eqnDivideParenthesesRightPlusWith", "dimensionless", "my_component", COMPUTED_CONSTANT},
    {"eqnDivideParenthesesRightPlusWithout", "dimensionless", "my_component", COMPUTED_CONSTANT},
    {"eqnDivideParenthesesRightMinusWith", "dimensionless", "my_component", COMPUTED_CONSTANT},
    {"eqnDivideParenthesesRightMinusWithout", "dimensionless", "my_component", COMPUTED_CONSTANT},
    {"eqnDivideParenthesesRightTimes", "dimensionless", "my_component", COMPUTED_CONSTANT},
    {"eqnDivideParenthesesRightDivide", "dimensionless", "my_component", COMPUTED_CONSTANT},
    {"eqnPowerSqrt", "dimensionless", "my_component", COMPUTED_CONSTANT},
    {"eqnPowerSqr", "dimensionless", "my_component", COMPUTED_CONSTANT},
    {"eqnPowerCube", "dimensionless", "my_component", COMPUTED_CONSTANT},
    {"eqnPowerCi", "dimensionless", "my_component", COMPUTED_CONSTANT},
    {"eqnPowerParentheses", "dimensionless", "my_component", COMPUTED_CONSTANT},
    {"eqnPowerParenthesesLeftPlusWith", "dimensionless", "my_component", COMPUTED_CONSTANT},
    {"eqnPowerParenthesesLeftPlusWithout", "dimensionless", "my_component", COMPUTED_CONSTANT},
    {"eqnPowerParenthesesLeftMinusWith", "dimensionless", "my_component", COMPUTED_CONSTANT},
    {"eqnPowerParenthesesLeftMinusWithout", "dimensionless", "my_component", COMPUTED_CONSTANT},
    {"eqnPowerParenthesesLeftTimes", "dimensionless", "my_component", COMPUTED_CONSTANT},
    {"eqnPowerParenthesesLeftDivide", "dimensionless", "my_component", COMPUTED_CONSTANT},
    {"eqnPowerParenthesesRightPlusWith", "dimensionless", "my_component", COMPUTED_CONSTANT},
    {"eqnPowerParenthesesRightPlusWithout", "dimensionless", "my_component", COMPUTED_CONSTANT},
    {"eqnPowerParenthesesRightMinusWith", "dimensionless", "my_component", COMPUTED_CONSTANT},
    {"eqnPowerParenthesesRightMinusWithout", "dimensionless", "my_component", COMPUTED_CONSTANT},
    {"eqnPowerParenthesesRightTimes", "dimensionless", "my_component", COMPUTED_CONSTANT},
    {"eqnPowerParenthesesRightDivide", "dimensionless", "my_component", COMPUTED_CONSTANT},
    {"eqnPowerParenthesesRightPower", "dimensionless", "my_component", COMPUTED_CONSTANT},
    {"eqnPowerParenthesesRightRoot", "dimensionless", "my_component", COMPUTED_CONSTANT},
    {"eqnRootSqrt", "dimensionless", "my_component", COMPUTED_CONSTANT},
    {"eqnRootSqrtOther", "dimensionless", "my_component", COMPUTED_CONSTANT},
    {"eqnRootCube", "dimensionless", "my_component", COMPUTED_CONSTANT},
    {"eqnRootCi", "dimensionless", "my_component", COMPUTED_CONSTANT},
    {"eqnRootParentheses", "dimensionless", "my_component", COMPUTED_CONSTANT},
    {"eqnRootParenthesesLeftPlusWith", "dimensionless", "my_component", COMPUTED_CONSTANT},
    {"eqnRootParenthesesLeftPlusWithout", "dimensionless", "my_component", COMPUTED_CONSTANT},
    {"eqnRootParenthesesLeftMinusWith", "dimensionless", "my_component", COMPUTED_CONSTANT},
    {"eqnRootParenthesesLeftMinusWithout", "dimensionless", "my_component", COMPUTED_CONSTANT},
    {"eqnRootParenthesesLeftTimes", "dimensionless", "my_component", COMPUTED_CONSTANT},
    {"eqnRootParenthesesLeftDivide", "dimensionless", "my_component", COMPUTED_CONSTANT},
    {"eqnRootParenthesesRightPlusWith", "dimensionless", "my_component", COMPUTED_CONSTANT},
    {"eqnRootParenthesesRightPlusWithout", "dimensionless", "my_component", COMPUTED_CONSTANT},
    {"eqnRootParenthesesRightMinusWith", "dimensionless", "my_component", COMPUTED_CONSTANT},
    {"eqnRootParenthesesRightMinusWithout", "dimensionless", "my_component", COMPUTED_CONSTANT},
    {"eqnRootParenthesesRightTimes", "dimensionless", "my_component", COMPUTED_CONSTANT},
    {"eqnRootParenthesesRightDivide", "dimensionless", "my_component", COMPUTED_CONSTANT},
    {"eqnRootParenthesesRightPower", "dimensionless", "my_component", COMPUTED_CONSTANT},
    {"eqnRootParenthesesRightRoot", "dimensionless", "my_component", COMPUTED_CONSTANT},
    {"eqnAbs", "dimensionless", "my_component", COMPUTED_CONSTANT},
    {"eqnExp", "dimensionless", "my_component", COMPUTED_CONSTANT},
    {"eqnLn", "dimensionless", "my_component", COMPUTED_CONSTANT},
    {"eqnLog", "dimensionless", "my_component", COMPUTED_CONSTANT},
    {"eqnLog2", "dimensionless", "my_component", COMPUTED_CONSTANT},
    {"eqnLog10", "dimensionless", "my_component", COMPUTED_CONSTANT},
    {"eqnLogCi", "dimensionless", "my_component", COMPUTED_CONSTANT},
    {"eqnCeiling", "dimensionless", "my_component", COMPUTED_CONSTANT},
    {"eqnFloor", "dimensionless", "my_component", COMPUTED_CONSTANT},
    {"eqnMin", "dimensionless", "my_component", COMPUTED_CONSTANT},
    {"eqnMinMultiple", "dimensionless", "my_component", COMPUTED_CONSTANT},
    {"eqnMax", "dimensionless", "my_component", COMPUTED_CONSTANT},
    {"eqnMaxMultiple", "dimensionless", "my_component", COMPUTED_CONSTANT},
    {"eqnRem", "dimensionless", "my_component", COMPUTED_CONSTANT},
    {"eqnSin", "dimensionless", "my_component", COMPUTED_CONSTANT},
    {"eqnCos", "dimensionless", "my_component", COMPUTED_CONSTANT},
    {"eqnTan", "dimensionless", "my_component", COMPUTED_CONSTANT},
    {"eqnSec", "dimensionless", "my_component", COMPUTED_CONSTANT},
    {"eqnCsc", "dimensionless", "my_component", COMPUTED_CONSTANT},
    {"eqnCot", "dimensionless", "my_component", COMPUTED_CONSTANT},
    {"eqnSinh", "dimensionless", "my_component", COMPUTED_CONSTANT},
    {"eqnCosh", "dimensionless", "my_component", COMPUTED_CONSTANT},
    {"eqnTanh", "dimensionless", "my_component", COMPUTED_CONSTANT},
    {"eqnSech", "dimensionless", "my_component", COMPUTED_CONSTANT},
    {"eqnCsch", "dimensionless", "my_component", COMPUTED_CONSTANT},
    {"eqnCoth", "dimensionless", "my_component", COMPUTED_CONSTANT},
    {"eqnArcsin", "dimensionless", "my_component", COMPUTED_CONSTANT},
    {"eqnArccos", "dimensionless", "my_component", COMPUTED_CONSTANT},
    {"eqnArctan", "dimensionless", "my_component", COMPUTED_CONSTANT},
    {"eqnArcsec", "dimensionless", "my_component", COMPUTED_CONSTANT},
    {"eqnArccsc", "dimensionless", "my_component", COMPUTED_CONSTANT},
    {"eqnArccot", "dimensionless", "my_component", COMPUTED_CONSTANT},
    {"eqnArcsinh", "dimensionless", "my_component", COMPUTED_CONSTANT},
    {"eqnArccosh", "dimensionless", "my_component", COMPUTED_CONSTANT},
    {"eqnArctanh", "dimensionless", "my_component", COMPUTED_CONSTANT},
    {"eqnArcsech", "dimensionless", "my_component", COMPUTED_CONSTANT},
    {"eqnArccsch", "dimensionless", "my_component", COMPUTED_CONSTANT},
    {"eqnArccoth", "dimensionless", "my_component", COMPUTED_CONSTANT},
    {"eqnPiecewisePiece", "dimensionless", "my_component", COMPUTED_CONSTANT},
    {"eqnPiecewisePieceOtherwise", "dimensionless", "my_component", COMPUTED_CONSTANT},
    {"eqnPiecewisePiecePiecePiece", "dimensionless", "my_component", COMPUTED_CONSTANT},
    {"q", "dimensionless", "my_component", CONSTANT},
    {"r", "dimensionless", "my_component", CONSTANT},
    {"eqnPiecewisePiecePiecePieceOtherwise", "dimensionless", "my_component", COMPUTED_CONSTANT},
    {"s", "dimensionless", "my_component", CONSTANT},
    {"eqnWithPiecewise", "dimensionless", "my_component", COMPUTED_CONSTANT},
    {"eqnCnInteger", "dimensionless", "my_component", COMPUTED_CONSTANT},
    {"eqnCnDouble", "dimensionless", "my_component", COMPUTED_CONSTANT},
    {"eqnCnIntegerWithExponent", "dimensionless", "my_component", COMPUTED_CONSTANT},
    {"eqnCnDoubleWithExponent", "dimensionless", "my_component", COMPUTED_CONSTANT},
    {"eqnCi", "dimensionless", "my_component", COMPUTED_CONSTANT},
    {"eqnTrue", "dimensionless", "my_component", COMPUTED_CONSTANT},
    {"eqnFalse", "dimensionless", "my_component", COMPUTED_CONSTANT},
    {"eqnExponentiale", "dimensionless", "my_component", COMPUTED_CONSTANT},
    {"eqnPi", "dimensionless", "my_component", COMPUTED_CONSTANT},
    {"eqnInfinity", "dimensionless", "my_component", COMPUTED_CONSTANT},
    {"eqnNotanumber", "dimensionless", "my_component", COMPUTED_CONSTANT},
    {"eqnCoverageForPlusOperator", "dimensionless", "my_component", COMPUTED_CONSTANT},
    {"eqnCoverageForMinusOperator", "dimensionless", "my_component", COMPUTED_CONSTANT},
    {"eqnCoverageForTimesOperator", "dimensionless", "my_component", COMPUTED_CONSTANT},
    {"eqnCoverageForDivideOperator", "dimensionless", "my_component", COMPUTED_CONSTANT},
    {"eqnCoverageForAndOperator", "dimensionless", "my_component", COMPUTED_CONSTANT},
    {"eqnCoverageForOrOperator", "dimensionless", "my_component", COMPUTED_CONSTANT},
    {"eqnCoverageForXorOperator", "dimensionless", "my_component", COMPUTED_CONSTANT},
    {"eqnCoverageForPowerOperator", "dimensionless", "my_component", COMPUTED_CONSTANT},
    {"eqnCoverageForRootOperator", "dimensionless", "my_component", COMPUTED_CONSTANT},
    {"eqnCoverageForMinusUnary", "dimensionless", "my_component", COMPUTED_CONSTANT},
    {"eqnNlaVariable1", "dimensionless", "my_component", ALGEBRAIC},
    {"eqnNlaVariable2", "dimensionless", "my_component", ALGEBRAIC},
    {"eqnComputedConstant1", "dimensionless", "my_component", COMPUTED_CONSTANT},
    {"eqnComputedConstant2", "dimensionless", "my_component", COMPUTED_CONSTANT}
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

double * createStatesVector()
{
    double *res = (double *) malloc(STATE_COUNT*sizeof(double));

    for (size_t i = 0; i < STATE_COUNT; ++i) {
        res[i] = NAN;
    }

    return res;
}

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

typedef struct {
    double voi;
    double *states;
    double *rates;
    double *variables;
} RootFindingInfo;

extern void nlaSolve(void (*objectiveFunction)(double *, double *, void *),
                     double *u, size_t n, void *data);

void objectiveFunction0(double *u, double *f, void *data)
{
    double voi = ((RootFindingInfo *) data)->voi;
    double *states = ((RootFindingInfo *) data)->states;
    double *rates = ((RootFindingInfo *) data)->rates;
    double *variables = ((RootFindingInfo *) data)->variables;

    algebraic[205] = u[0];
    algebraic[206] = u[1];

    f[0] = algebraic[205]+algebraic[206]+states[0]-0.0;
    f[1] = algebraic[205]-algebraic[206]-(computedConstants[207]+computedConstants[208]);
}

void findRoot0(double voi, double *states, double *rates, double *variables)
{
    RootFindingInfo rfi = { voi, states, rates, variables };
    double u[2];

    u[0] = algebraic[205];
    u[1] = algebraic[206];

    nlaSolve(objectiveFunction0, u, 2, &rfi);

    algebraic[205] = u[0];
    algebraic[206] = u[1];
}

void initialiseVariables(double *states, double *rates, double *constants)
{
    constants[1] = 1.0;
    constants[2] = 2.0;
    constants[6] = 3.0;
    constants[18] = 4.0;
    constants[179] = 5.0;
    constants[180] = 6.0;
    constants[182] = 7.0;
    algebraic[205] = 1.0;
    algebraic[206] = 2.0;
    computedConstants[184] = 123.0;
    computedConstants[185] = 123.456789;
    computedConstants[186] = 123.0e99;
    computedConstants[187] = 123.456789e99;
    computedConstants[189] = 1.0;
    computedConstants[190] = 0.0;
    computedConstants[191] = 2.71828182845905;
    computedConstants[192] = 3.14159265358979;
    computedConstants[193] = INFINITY;
    computedConstants[194] = NAN;
    computedConstants[207] = 1.0;
    computedConstants[208] = 3.0;
    states[0] = 0.0;
}

void computeComputedConstants(double *constants, double *computedConstants)
{
    computedConstants[0] = constants[1] == constants[2];
    computedConstants[3] = constants[1]/(constants[2] == constants[2]);
    computedConstants[4] = constants[1] != constants[2];
    computedConstants[5] = constants[1]/(constants[2] != constants[6]);
    computedConstants[7] = constants[1] < constants[2];
    computedConstants[8] = constants[1]/(constants[2] < constants[6]);
    computedConstants[9] = constants[1] <= constants[2];
    computedConstants[10] = constants[1]/(constants[2] <= constants[6]);
    computedConstants[11] = constants[1] > constants[2];
    computedConstants[12] = constants[1]/(constants[2] > constants[6]);
    computedConstants[13] = constants[1] >= constants[2];
    computedConstants[14] = constants[1]/(constants[2] >= constants[6]);
    computedConstants[15] = constants[1] && constants[2];
    computedConstants[16] = constants[1] && constants[2] && constants[6];
    computedConstants[17] = (constants[1] < constants[2]) && (constants[6] > constants[18]);
    computedConstants[19] = (constants[1]+constants[2]) && (constants[6] > constants[18]);
    computedConstants[20] = constants[1] && (constants[2] > constants[6]);
    computedConstants[21] = (constants[1]-constants[2]) && (constants[6] > constants[18]);
    computedConstants[22] = -constants[1] && (constants[2] > constants[6]);
    computedConstants[23] = pow(constants[1], constants[2]) && (constants[6] > constants[18]);
    computedConstants[24] = pow(constants[1], 1.0/constants[2]) && (constants[6] > constants[18]);
    computedConstants[25] = (constants[1] < constants[2]) && (constants[6]+constants[18]);
    computedConstants[26] = (constants[1] < constants[2]) && constants[6];
    computedConstants[27] = (constants[1] < constants[2]) && (constants[6]-constants[18]);
    computedConstants[28] = (constants[1] < constants[2]) && -constants[6];
    computedConstants[29] = (constants[1] < constants[2]) && pow(constants[6], constants[18]);
    computedConstants[30] = (constants[1] < constants[2]) && pow(constants[6], 1.0/constants[18]);
    computedConstants[31] = constants[1]/(constants[2] && constants[6]);
    computedConstants[32] = constants[1] || constants[2];
    computedConstants[33] = constants[1] || constants[2] || constants[6];
    computedConstants[34] = (constants[1] < constants[2]) || (constants[6] > constants[18]);
    computedConstants[35] = (constants[1]+constants[2]) || (constants[6] > constants[18]);
    computedConstants[36] = constants[1] || (constants[2] > constants[6]);
    computedConstants[37] = (constants[1]-constants[2]) || (constants[6] > constants[18]);
    computedConstants[38] = -constants[1] || (constants[2] > constants[6]);
    computedConstants[39] = pow(constants[1], constants[2]) || (constants[6] > constants[18]);
    computedConstants[40] = pow(constants[1], 1.0/constants[2]) || (constants[6] > constants[18]);
    computedConstants[41] = (constants[1] < constants[2]) || (constants[6]+constants[18]);
    computedConstants[42] = (constants[1] < constants[2]) || constants[6];
    computedConstants[43] = (constants[1] < constants[2]) || (constants[6]-constants[18]);
    computedConstants[44] = (constants[1] < constants[2]) || -constants[6];
    computedConstants[45] = (constants[1] < constants[2]) || pow(constants[6], constants[18]);
    computedConstants[46] = (constants[1] < constants[2]) || pow(constants[6], 1.0/constants[18]);
    computedConstants[47] = constants[1]/(constants[2] || constants[6]);
    computedConstants[48] = xor(constants[1], constants[2]);
    computedConstants[49] = xor(constants[1], xor(constants[2], constants[6]));
    computedConstants[50] = xor(constants[1] < constants[2], constants[6] > constants[18]);
    computedConstants[51] = xor(constants[1]+constants[2], constants[6] > constants[18]);
    computedConstants[52] = xor(constants[1], constants[2] > constants[6]);
    computedConstants[53] = xor(constants[1]-constants[2], constants[6] > constants[18]);
    computedConstants[54] = xor(-constants[1], constants[2] > constants[6]);
    computedConstants[55] = xor(pow(constants[1], constants[2]), constants[6] > constants[18]);
    computedConstants[56] = xor(pow(constants[1], 1.0/constants[2]), constants[6] > constants[18]);
    computedConstants[57] = xor(constants[1] < constants[2], constants[6]+constants[18]);
    computedConstants[58] = xor(constants[1] < constants[2], constants[6]);
    computedConstants[59] = xor(constants[1] < constants[2], constants[6]-constants[18]);
    computedConstants[60] = xor(constants[1] < constants[2], -constants[6]);
    computedConstants[61] = xor(constants[1] < constants[2], pow(constants[6], constants[18]));
    computedConstants[62] = xor(constants[1] < constants[2], pow(constants[6], 1.0/constants[18]));
    computedConstants[63] = constants[1]/xor(constants[2], constants[6]);
    computedConstants[64] = !constants[1];
    computedConstants[65] = constants[1]+constants[2];
    computedConstants[66] = constants[1]+constants[2]+constants[6];
    computedConstants[67] = (constants[1] < constants[2])+(constants[6] > constants[18]);
    computedConstants[68] = constants[1];
    computedConstants[69] = constants[1]-constants[2];
    computedConstants[70] = (constants[1] < constants[2])-(constants[6] > constants[18]);
    computedConstants[71] = (constants[1] < constants[2])-(constants[6]+constants[18]);
    computedConstants[72] = (constants[1] < constants[2])-constants[6];
    computedConstants[73] = constants[1]-(-constants[2]);
    computedConstants[74] = constants[1]-(-constants[2]*constants[6]);
    computedConstants[75] = -constants[1];
    computedConstants[76] = -(constants[1] < constants[2]);
    computedConstants[77] = constants[1]*constants[2];
    computedConstants[78] = constants[1]*constants[2]*constants[6];
    computedConstants[79] = (constants[1] < constants[2])*(constants[6] > constants[18]);
    computedConstants[80] = (constants[1]+constants[2])*(constants[6] > constants[18]);
    computedConstants[81] = constants[1]*(constants[2] > constants[6]);
    computedConstants[82] = (constants[1]-constants[2])*(constants[6] > constants[18]);
    computedConstants[83] = -constants[1]*(constants[2] > constants[6]);
    computedConstants[84] = (constants[1] < constants[2])*(constants[6]+constants[18]);
    computedConstants[85] = (constants[1] < constants[2])*constants[6];
    computedConstants[86] = (constants[1] < constants[2])*(constants[6]-constants[18]);
    computedConstants[87] = (constants[1] < constants[2])*-constants[6];
    computedConstants[88] = constants[1]/constants[2];
    computedConstants[89] = (constants[1] < constants[2])/(constants[18] > constants[6]);
    computedConstants[90] = (constants[1]+constants[2])/(constants[18] > constants[6]);
    computedConstants[91] = constants[1]/(constants[6] > constants[2]);
    computedConstants[92] = (constants[1]-constants[2])/(constants[18] > constants[6]);
    computedConstants[93] = -constants[1]/(constants[6] > constants[2]);
    computedConstants[94] = (constants[1] < constants[2])/(constants[6]+constants[18]);
    computedConstants[95] = (constants[1] < constants[2])/constants[6];
    computedConstants[96] = (constants[1] < constants[2])/(constants[6]-constants[18]);
    computedConstants[97] = (constants[1] < constants[2])/-constants[6];
    computedConstants[98] = (constants[1] < constants[2])/(constants[6]*constants[18]);
    computedConstants[99] = (constants[1] < constants[2])/(constants[6]/constants[18]);
    computedConstants[100] = sqrt(constants[1]);
    computedConstants[101] = pow(constants[1], 2.0);
    computedConstants[102] = pow(constants[1], 3.0);
    computedConstants[103] = pow(constants[1], constants[2]);
    computedConstants[104] = pow(constants[1] <= constants[2], constants[6] >= constants[18]);
    computedConstants[105] = pow(constants[1]+constants[2], constants[6] >= constants[18]);
    computedConstants[106] = pow(constants[1], constants[2] >= constants[6]);
    computedConstants[107] = pow(constants[1]-constants[2], constants[6] >= constants[18]);
    computedConstants[108] = pow(-constants[1], constants[2] >= constants[6]);
    computedConstants[109] = pow(constants[1]*constants[2], constants[6] >= constants[18]);
    computedConstants[110] = pow(constants[1]/constants[2], constants[6] >= constants[18]);
    computedConstants[111] = pow(constants[1] <= constants[2], constants[6]+constants[18]);
    computedConstants[112] = pow(constants[1] <= constants[2], constants[6]);
    computedConstants[113] = pow(constants[1] <= constants[2], constants[6]-constants[18]);
    computedConstants[114] = pow(constants[1] <= constants[2], -constants[6]);
    computedConstants[115] = pow(constants[1] <= constants[2], constants[6]*constants[18]);
    computedConstants[116] = pow(constants[1] <= constants[2], constants[6]/constants[18]);
    computedConstants[117] = pow(constants[1] <= constants[2], pow(constants[6], constants[18]));
    computedConstants[118] = pow(constants[1] <= constants[2], pow(constants[6], 1.0/constants[18]));
    computedConstants[119] = sqrt(constants[1]);
    computedConstants[120] = sqrt(constants[1]);
    computedConstants[121] = pow(constants[1], 1.0/3.0);
    computedConstants[122] = pow(constants[1], 1.0/constants[2]);
    computedConstants[123] = pow(constants[1] < constants[2], 1.0/(constants[18] > constants[6]));
    computedConstants[124] = pow(constants[1]+constants[2], 1.0/(constants[18] > constants[6]));
    computedConstants[125] = pow(constants[1], 1.0/(constants[6] > constants[2]));
    computedConstants[126] = pow(constants[1]-constants[2], 1.0/(constants[18] > constants[6]));
    computedConstants[127] = pow(-constants[1], 1.0/(constants[6] > constants[2]));
    computedConstants[128] = pow(constants[1]*constants[2], 1.0/(constants[18] > constants[6]));
    computedConstants[129] = pow(constants[1]/constants[2], 1.0/(constants[18] > constants[6]));
    computedConstants[130] = pow(constants[1] < constants[2], 1.0/(constants[6]+constants[18]));
    computedConstants[131] = pow(constants[1] < constants[2], 1.0/constants[6]);
    computedConstants[132] = pow(constants[1] < constants[2], 1.0/(constants[6]-constants[18]));
    computedConstants[133] = pow(constants[1] < constants[2], 1.0/-constants[6]);
    computedConstants[134] = pow(constants[1] < constants[2], 1.0/(constants[6]*constants[18]));
    computedConstants[135] = pow(constants[1] < constants[2], 1.0/(constants[6]/constants[18]));
    computedConstants[136] = pow(constants[1] < constants[2], 1.0/pow(constants[6], constants[18]));
    computedConstants[137] = pow(constants[1] < constants[2], 1.0/pow(constants[6], 1.0/constants[18]));
    computedConstants[138] = fabs(constants[1]);
    computedConstants[139] = exp(constants[1]);
    computedConstants[140] = log(constants[1]);
    computedConstants[141] = log10(constants[1]);
    computedConstants[142] = log(constants[1])/log(2.0);
    computedConstants[143] = log10(constants[1]);
    computedConstants[144] = log(constants[1])/log(constants[2]);
    computedConstants[145] = ceil(constants[1]);
    computedConstants[146] = floor(constants[1]);
    computedConstants[147] = min(constants[1], constants[2]);
    computedConstants[148] = min(constants[1], min(constants[2], constants[6]));
    computedConstants[149] = max(constants[1], constants[2]);
    computedConstants[150] = max(constants[1], max(constants[2], constants[6]));
    computedConstants[151] = fmod(constants[1], constants[2]);
    computedConstants[152] = sin(constants[1]);
    computedConstants[153] = cos(constants[1]);
    computedConstants[154] = tan(constants[1]);
    computedConstants[155] = sec(constants[1]);
    computedConstants[156] = csc(constants[1]);
    computedConstants[157] = cot(constants[1]);
    computedConstants[158] = sinh(constants[1]);
    computedConstants[159] = cosh(constants[1]);
    computedConstants[160] = tanh(constants[1]);
    computedConstants[161] = sech(constants[1]);
    computedConstants[162] = csch(constants[1]);
    computedConstants[163] = coth(constants[1]);
    computedConstants[164] = asin(constants[1]);
    computedConstants[165] = acos(constants[1]);
    computedConstants[166] = atan(constants[1]);
    computedConstants[167] = asec(constants[1]);
    computedConstants[168] = acsc(constants[1]);
    computedConstants[169] = acot(constants[1]);
    computedConstants[170] = asinh(constants[1]);
    computedConstants[171] = acosh(constants[1]);
    computedConstants[172] = atanh(constants[1]/2.0);
    computedConstants[173] = asech(constants[1]);
    computedConstants[174] = acsch(constants[1]);
    computedConstants[175] = acoth(2.0*constants[1]);
    computedConstants[176] = (constants[1] > constants[2])?constants[1]:NAN;
    computedConstants[177] = (constants[1] > constants[2])?constants[1]:constants[6];
    computedConstants[178] = (constants[1] > constants[2])?constants[1]:(constants[6] > constants[18])?constants[6]:(constants[179] > constants[180])?constants[179]:NAN;
    computedConstants[181] = (constants[1] > constants[2])?constants[1]:(constants[6] > constants[18])?constants[6]:(constants[179] > constants[180])?constants[179]:constants[182];
    computedConstants[183] = 123.0+((constants[1] > constants[2])?constants[1]:NAN);
    computedConstants[188] = constants[1];
    computedConstants[195] = (constants[1] && constants[2])+((constants[6] > constants[18])?constants[2]:NAN)+constants[179]+(constants[180] && constants[182]);
    computedConstants[196] = (constants[1] && constants[2])-(((constants[6] > constants[18])?constants[2]:NAN)-(constants[179]-((constants[6] > constants[18])?constants[2]:NAN)))-(constants[180] && constants[182]);
    computedConstants[197] = (constants[1] && constants[2])*((constants[6] > constants[18])?constants[2]:NAN)*constants[179]*((constants[6] > constants[18])?constants[2]:NAN)*(constants[180] && constants[182]);
    computedConstants[198] = (constants[1] && constants[2])/(((constants[6] > constants[18])?constants[2]:NAN)/(constants[179]/((constants[6] > constants[18])?constants[2]:NAN)));
    computedConstants[199] = (constants[1] || constants[2]) && xor(constants[1], constants[2]) && ((constants[6] > constants[18])?constants[2]:NAN) && constants[179] && ((constants[6] > constants[18])?constants[2]:NAN) && xor(constants[1], constants[2]) && (constants[1] || constants[2]);
    computedConstants[200] = (constants[1] && constants[2]) || xor(constants[1], constants[2]) || ((constants[6] > constants[18])?constants[2]:NAN) || constants[179] || ((constants[6] > constants[18])?constants[2]:NAN) || xor(constants[1], constants[2]) || (constants[1] && constants[2]);
    computedConstants[201] = xor(constants[1] && constants[2], xor(constants[1] || constants[2], xor((constants[6] > constants[18])?constants[2]:NAN, xor(xor(xor(constants[179], (constants[6] > constants[18])?constants[2]:NAN), constants[1] || constants[2]), constants[1] && constants[2]))));
    computedConstants[202] = pow(constants[1] && constants[2], pow((constants[6] > constants[18])?constants[2]:NAN, pow(pow(constants[179], (constants[6] > constants[18])?constants[2]:NAN), constants[1] && constants[2])));
    computedConstants[203] = pow(pow(pow(constants[1] && constants[2], 1.0/pow((constants[6] > constants[18])?constants[2]:NAN, 1.0/constants[179])), 1.0/((constants[6] > constants[18])?constants[2]:NAN)), 1.0/(constants[1] && constants[2]));
    computedConstants[204] = -(constants[1] && constants[2])+-((constants[6] > constants[18])?constants[2]:NAN);
}

void computeRates(double voi, double *states, double *rates, double *constants, double *computedConstants, double *algebraic)
{
    rates[0] = 1.0;
}

void computeVariables(double voi, double *states, double *rates, double *constants, double *computedConstants, double *algebraic)
{
    findRoot0(voi, states, rates, variables);
}

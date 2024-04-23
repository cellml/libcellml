/* The content of this file was generated using a modified C profile of libCellML 0.5.0. */

#include "model.h"

#include <math.h>
#include <stdlib.h>

const char VERSION[] = "0.5.0.post0";
const char LIBCELLML_VERSION[] = "0.5.0";

const size_t STATE_COUNT = 1;
const size_t VARIABLE_COUNT = 220;

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
    {"eqnXorCoverageParentheses", "dimensionless", "my_component", ALGEBRAIC},
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
    {"eqnRootSqr", "dimensionless", "my_component", COMPUTED_CONSTANT},
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
    {"eqnPiecewise", "dimensionless", "my_component", COMPUTED_CONSTANT},
    {"eqnPiecewisePiece", "dimensionless", "my_component", COMPUTED_CONSTANT},
    {"eqnPiecewisePiece2", "dimensionless", "my_component", COMPUTED_CONSTANT},
    {"eqnPiecewiseOtherwise", "dimensionless", "my_component", COMPUTED_CONSTANT},
    {"eqnPiecewisePieceOtherwise", "dimensionless", "my_component", COMPUTED_CONSTANT},
    {"eqnPiecewisePiecePiecePiece", "dimensionless", "my_component", COMPUTED_CONSTANT},
    {"q", "dimensionless", "my_component", CONSTANT},
    {"r", "dimensionless", "my_component", CONSTANT},
    {"eqnPiecewisePiecePiecePiece2", "dimensionless", "my_component", COMPUTED_CONSTANT},
    {"eqnPiecewisePiecePiecePieceOtherwise", "dimensionless", "my_component", COMPUTED_CONSTANT},
    {"s", "dimensionless", "my_component", CONSTANT},
    {"eqnWithPiecewise", "dimensionless", "my_component", COMPUTED_CONSTANT},
    {"eqnWithPiecewise2", "dimensionless", "my_component", COMPUTED_CONSTANT},
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
    {"eqnCoverageForPlusOperator2", "dimensionless", "my_component", COMPUTED_CONSTANT},
    {"eqnCoverageForMinusOperator", "dimensionless", "my_component", COMPUTED_CONSTANT},
    {"eqnCoverageForMinusOperator2", "dimensionless", "my_component", COMPUTED_CONSTANT},
    {"eqnCoverageForTimesOperator", "dimensionless", "my_component", COMPUTED_CONSTANT},
    {"eqnCoverageForTimesOperator2", "dimensionless", "my_component", COMPUTED_CONSTANT},
    {"eqnCoverageForDivideOperator", "dimensionless", "my_component", COMPUTED_CONSTANT},
    {"eqnCoverageForDivideOperator2", "dimensionless", "my_component", COMPUTED_CONSTANT},
    {"eqnCoverageForAndOperator", "dimensionless", "my_component", COMPUTED_CONSTANT},
    {"eqnCoverageForOrOperator", "dimensionless", "my_component", COMPUTED_CONSTANT},
    {"eqnCoverageForXorOperator", "dimensionless", "my_component", COMPUTED_CONSTANT},
    {"eqnCoverageForPowerOperator", "dimensionless", "my_component", COMPUTED_CONSTANT},
    {"eqnCoverageForRootOperator", "dimensionless", "my_component", COMPUTED_CONSTANT},
    {"eqnCoverageForMinusUnary", "dimensionless", "my_component", COMPUTED_CONSTANT},
    {"eqnCoverageForMinusUnary2", "dimensionless", "my_component", COMPUTED_CONSTANT},
    {"eqnNlaVariable1", "dimensionless", "my_component", ALGEBRAIC},
    {"eqnNlaVariable2", "dimensionless", "my_component", ALGEBRAIC},
    {"eqnComputedConstant1", "dimensionless", "my_component", COMPUTED_CONSTANT},
    {"eqnComputedConstant2", "dimensionless", "my_component", COMPUTED_CONSTANT}
};

double xor(double x, double y)
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

    variables[216] = u[0];
    variables[217] = u[1];

    f[0] = variables[216]+variables[217]+states[0]-0.0;
    f[1] = variables[216]-variables[217]-(variables[218]+variables[219]);
}

void findRoot0(double voi, double *states, double *rates, double *variables)
{
    RootFindingInfo rfi = { voi, states, rates, variables };
    double u[2];

    u[0] = variables[216];
    u[1] = variables[217];

    nlaSolve(objectiveFunction0, u, 2, &rfi);

    variables[216] = u[0];
    variables[217] = u[1];
}

void initialiseVariables(double *states, double *rates, double *variables)
{
    variables[1] = 1.0;
    variables[2] = 2.0;
    variables[6] = 3.0;
    variables[18] = 4.0;
    variables[183] = 5.0;
    variables[184] = 6.0;
    variables[187] = 7.0;
    variables[216] = 1.0;
    variables[217] = 2.0;
    variables[177] = NAN;
    variables[190] = 123.0;
    variables[191] = 123.456789;
    variables[192] = 123.0e99;
    variables[193] = 123.456789e99;
    variables[195] = 1.0;
    variables[196] = 0.0;
    variables[197] = 2.71828182845905;
    variables[198] = 3.14159265358979;
    variables[199] = INFINITY;
    variables[200] = NAN;
    variables[218] = 1.0;
    variables[219] = 3.0;
    states[0] = 0.0;
}

void computeComputedConstants(double *variables)
{
    variables[0] = variables[1] == variables[2];
    variables[3] = variables[1]/(variables[2] == variables[2]);
    variables[4] = variables[1] != variables[2];
    variables[5] = variables[1]/(variables[2] != variables[6]);
    variables[7] = variables[1] < variables[2];
    variables[8] = variables[1]/(variables[2] < variables[6]);
    variables[9] = variables[1] <= variables[2];
    variables[10] = variables[1]/(variables[2] <= variables[6]);
    variables[11] = variables[1] > variables[2];
    variables[12] = variables[1]/(variables[6] > variables[2]);
    variables[13] = variables[1] >= variables[2];
    variables[14] = variables[1]/(variables[6] >= variables[2]);
    variables[15] = variables[1] && variables[2];
    variables[16] = variables[1] && variables[2] && variables[6];
    variables[17] = (variables[1] < variables[2]) && (variables[6] > variables[18]);
    variables[19] = (variables[1]+variables[2]) && (variables[6] > variables[18]);
    variables[20] = variables[1] && (variables[2] > variables[6]);
    variables[21] = (variables[1]-variables[2]) && (variables[6] > variables[18]);
    variables[22] = -variables[1] && (variables[2] > variables[6]);
    variables[23] = pow(variables[1], variables[2]) && (variables[6] > variables[18]);
    variables[24] = pow(variables[1], 1.0/variables[2]) && (variables[6] > variables[18]);
    variables[25] = (variables[1] < variables[2]) && (variables[6]+variables[18]);
    variables[26] = (variables[1] < variables[2]) && variables[6];
    variables[27] = (variables[1] < variables[2]) && (variables[6]-variables[18]);
    variables[28] = (variables[1] < variables[2]) && -variables[6];
    variables[29] = (variables[1] < variables[2]) && pow(variables[6], variables[18]);
    variables[30] = (variables[1] < variables[2]) && pow(variables[6], 1.0/variables[18]);
    variables[31] = variables[1]/(variables[2] && variables[6]);
    variables[32] = variables[1] || variables[2];
    variables[33] = variables[1] || variables[2] || variables[6];
    variables[34] = (variables[1] < variables[2]) || (variables[6] > variables[18]);
    variables[35] = (variables[1]+variables[2]) || (variables[6] > variables[18]);
    variables[36] = variables[1] || (variables[2] > variables[6]);
    variables[37] = (variables[1]-variables[2]) || (variables[6] > variables[18]);
    variables[38] = -variables[1] || (variables[2] > variables[6]);
    variables[39] = pow(variables[1], variables[2]) || (variables[6] > variables[18]);
    variables[40] = pow(variables[1], 1.0/variables[2]) || (variables[6] > variables[18]);
    variables[41] = (variables[1] < variables[2]) || (variables[6]+variables[18]);
    variables[42] = (variables[1] < variables[2]) || variables[6];
    variables[43] = (variables[1] < variables[2]) || (variables[6]-variables[18]);
    variables[44] = (variables[1] < variables[2]) || -variables[6];
    variables[45] = (variables[1] < variables[2]) || pow(variables[6], variables[18]);
    variables[46] = (variables[1] < variables[2]) || pow(variables[6], 1.0/variables[18]);
    variables[47] = variables[1]/(variables[2] || variables[6]);
    variables[48] = xor(variables[1], variables[2]);
    variables[49] = xor(variables[1], xor(variables[2], variables[6]));
    variables[50] = xor(variables[1] < variables[2], variables[6] > variables[18]);
    variables[51] = xor(variables[1]+variables[2], variables[6] > variables[18]);
    variables[52] = xor(variables[1], variables[2] > variables[6]);
    variables[53] = xor(variables[1]-variables[2], variables[6] > variables[18]);
    variables[54] = xor(-variables[1], variables[2] > variables[6]);
    variables[55] = xor(pow(variables[1], variables[2]), variables[6] > variables[18]);
    variables[56] = xor(pow(variables[1], 1.0/variables[2]), variables[6] > variables[18]);
    variables[57] = xor(variables[1] < variables[2], variables[6]+variables[18]);
    variables[58] = xor(variables[1] < variables[2], variables[6]);
    variables[59] = xor(variables[1] < variables[2], variables[6]-variables[18]);
    variables[60] = xor(variables[1] < variables[2], -variables[6]);
    variables[61] = xor(variables[1] < variables[2], pow(variables[6], variables[18]));
    variables[62] = xor(variables[1] < variables[2], pow(variables[6], 1.0/variables[18]));
    variables[64] = !variables[1];
    variables[65] = variables[1]+variables[2];
    variables[66] = variables[1]+variables[2]+variables[6];
    variables[67] = (variables[1] < variables[2])+(variables[6] > variables[18]);
    variables[68] = variables[1];
    variables[69] = variables[1]-variables[2];
    variables[70] = (variables[1] < variables[2])-(variables[6] > variables[18]);
    variables[71] = (variables[1] < variables[2])-(variables[6]+variables[18]);
    variables[72] = (variables[1] < variables[2])-variables[6];
    variables[73] = variables[1]-(-variables[2]);
    variables[74] = variables[1]-(-variables[2]*variables[6]);
    variables[75] = -variables[1];
    variables[76] = -(variables[1] < variables[2]);
    variables[77] = variables[1]*variables[2];
    variables[78] = variables[1]*variables[2]*variables[6];
    variables[79] = (variables[1] < variables[2])*(variables[6] > variables[18]);
    variables[80] = (variables[1]+variables[2])*(variables[6] > variables[18]);
    variables[81] = variables[1]*(variables[2] > variables[6]);
    variables[82] = (variables[1]-variables[2])*(variables[6] > variables[18]);
    variables[83] = -variables[1]*(variables[2] > variables[6]);
    variables[84] = (variables[1] < variables[2])*(variables[6]+variables[18]);
    variables[85] = (variables[1] < variables[2])*variables[6];
    variables[86] = (variables[1] < variables[2])*(variables[6]-variables[18]);
    variables[87] = (variables[1] < variables[2])*-variables[6];
    variables[88] = variables[1]/variables[2];
    variables[89] = (variables[1] < variables[2])/(variables[18] > variables[6]);
    variables[90] = (variables[1]+variables[2])/(variables[18] > variables[6]);
    variables[91] = variables[1]/(variables[6] > variables[2]);
    variables[92] = (variables[1]-variables[2])/(variables[18] > variables[6]);
    variables[93] = -variables[1]/(variables[6] > variables[2]);
    variables[94] = (variables[1] < variables[2])/(variables[6]+variables[18]);
    variables[95] = (variables[1] < variables[2])/variables[6];
    variables[96] = (variables[1] < variables[2])/(variables[6]-variables[18]);
    variables[97] = (variables[1] < variables[2])/-variables[6];
    variables[98] = (variables[1] < variables[2])/(variables[6]*variables[18]);
    variables[99] = (variables[1] < variables[2])/(variables[6]/variables[18]);
    variables[100] = sqrt(variables[1]);
    variables[101] = pow(variables[1], 2.0);
    variables[102] = pow(variables[1], 3.0);
    variables[103] = pow(variables[1], variables[2]);
    variables[104] = pow(variables[1] <= variables[2], variables[6] >= variables[18]);
    variables[105] = pow(variables[1]+variables[2], variables[6] >= variables[18]);
    variables[106] = pow(variables[1], variables[2] >= variables[6]);
    variables[107] = pow(variables[1]-variables[2], variables[6] >= variables[18]);
    variables[108] = pow(-variables[1], variables[2] >= variables[6]);
    variables[109] = pow(variables[1]*variables[2], variables[6] >= variables[18]);
    variables[110] = pow(variables[1]/variables[2], variables[6] >= variables[18]);
    variables[111] = pow(variables[1] <= variables[2], variables[6]+variables[18]);
    variables[112] = pow(variables[1] <= variables[2], variables[6]);
    variables[113] = pow(variables[1] <= variables[2], variables[6]-variables[18]);
    variables[114] = pow(variables[1] <= variables[2], -variables[6]);
    variables[115] = pow(variables[1] <= variables[2], variables[6]*variables[18]);
    variables[116] = pow(variables[1] <= variables[2], variables[6]/variables[18]);
    variables[117] = pow(variables[1] <= variables[2], pow(variables[6], variables[18]));
    variables[118] = pow(variables[1] <= variables[2], pow(variables[6], 1.0/variables[18]));
    variables[119] = sqrt(variables[1]);
    variables[120] = sqrt(variables[1]);
    variables[121] = pow(variables[1], 1.0/0.5);
    variables[122] = pow(variables[1], 1.0/3.0);
    variables[123] = pow(variables[1], 1.0/variables[2]);
    variables[124] = pow(variables[1] < variables[2], 1.0/(variables[18] > variables[6]));
    variables[125] = pow(variables[1]+variables[2], 1.0/(variables[18] > variables[6]));
    variables[126] = pow(variables[1], 1.0/(variables[6] > variables[2]));
    variables[127] = pow(variables[1]-variables[2], 1.0/(variables[18] > variables[6]));
    variables[128] = pow(-variables[1], 1.0/(variables[6] > variables[2]));
    variables[129] = pow(variables[1]*variables[2], 1.0/(variables[18] > variables[6]));
    variables[130] = pow(variables[1]/variables[2], 1.0/(variables[18] > variables[6]));
    variables[131] = pow(variables[1] < variables[2], 1.0/(variables[6]+variables[18]));
    variables[132] = pow(variables[1] < variables[2], 1.0/variables[6]);
    variables[133] = pow(variables[1] < variables[2], 1.0/(variables[6]-variables[18]));
    variables[134] = pow(variables[1] < variables[2], 1.0/-variables[6]);
    variables[135] = pow(variables[1] < variables[2], 1.0/(variables[6]*variables[18]));
    variables[136] = pow(variables[1] < variables[2], 1.0/(variables[6]/variables[18]));
    variables[137] = pow(variables[1] < variables[2], 1.0/pow(variables[6], variables[18]));
    variables[138] = pow(variables[1] < variables[2], 1.0/pow(variables[6], 1.0/variables[18]));
    variables[139] = fabs(variables[1]);
    variables[140] = exp(variables[1]);
    variables[141] = log(variables[1]);
    variables[142] = log10(variables[1]);
    variables[143] = log(variables[1])/log(2.0);
    variables[144] = log10(variables[1]);
    variables[145] = log(variables[1])/log(variables[2]);
    variables[146] = ceil(variables[1]);
    variables[147] = floor(variables[1]);
    variables[148] = fmin(variables[1], variables[2]);
    variables[149] = fmin(variables[1], fmin(variables[2], variables[6]));
    variables[150] = fmax(variables[1], variables[2]);
    variables[151] = fmax(variables[1], fmax(variables[2], variables[6]));
    variables[152] = fmod(variables[1], variables[2]);
    variables[153] = sin(variables[1]);
    variables[154] = cos(variables[1]);
    variables[155] = tan(variables[1]);
    variables[156] = sec(variables[1]);
    variables[157] = csc(variables[1]);
    variables[158] = cot(variables[1]);
    variables[159] = sinh(variables[1]);
    variables[160] = cosh(variables[1]);
    variables[161] = tanh(variables[1]);
    variables[162] = sech(variables[1]);
    variables[163] = csch(variables[1]);
    variables[164] = coth(variables[1]);
    variables[165] = asin(variables[1]);
    variables[166] = acos(variables[1]);
    variables[167] = atan(variables[1]);
    variables[168] = asec(variables[1]);
    variables[169] = acsc(variables[1]);
    variables[170] = acot(variables[1]);
    variables[171] = asinh(variables[1]);
    variables[172] = acosh(variables[1]);
    variables[173] = atanh(variables[1]/2.0);
    variables[174] = asech(variables[1]);
    variables[175] = acsch(variables[1]);
    variables[176] = acoth(2.0*variables[1]);
    variables[178] = (variables[1] > variables[2])?variables[1]:NAN;
    variables[179] = (variables[1] < variables[2])?variables[1]:NAN;
    variables[180] = variables[1];
    variables[181] = (variables[1] > variables[2])?variables[1]:variables[6];
    variables[182] = (variables[1] > variables[2])?variables[1]:(variables[6] > variables[18])?variables[6]:(variables[183] > variables[184])?variables[183]:NAN;
    variables[185] = (variables[1] < variables[2])?variables[1]:(variables[6] > variables[18])?variables[6]:(variables[183] > variables[184])?variables[183]:NAN;
    variables[186] = (variables[1] > variables[2])?variables[1]:(variables[6] > variables[18])?variables[6]:(variables[183] > variables[184])?variables[183]:variables[187];
    variables[188] = 123.0+((variables[1] > variables[2])?variables[1]:NAN);
    variables[189] = 123.0+((variables[1] < variables[2])?variables[1]:NAN);
    variables[194] = variables[1];
    variables[201] = (variables[1] && variables[2])+((variables[6] > variables[18])?variables[2]:NAN)+variables[183]+(variables[184] && variables[187]);
    variables[202] = (variables[1] && variables[2])+((variables[6] < variables[18])?variables[2]:NAN)+variables[183]+(variables[184] && variables[187]);
    variables[203] = (variables[1] && variables[2])-(((variables[6] > variables[18])?variables[2]:NAN)-(variables[183]-((variables[6] > variables[18])?variables[2]:NAN)))-(variables[184] && variables[187]);
    variables[204] = (variables[1] && variables[2])-(((variables[6] < variables[18])?variables[2]:NAN)-(variables[183]-((variables[6] < variables[18])?variables[2]:NAN)))-(variables[184] && variables[187]);
    variables[205] = (variables[1] && variables[2])*((variables[6] > variables[18])?variables[2]:NAN)*variables[183]*((variables[6] > variables[18])?variables[2]:NAN)*(variables[184] && variables[187]);
    variables[206] = (variables[1] && variables[2])*((variables[6] < variables[18])?variables[2]:NAN)*variables[183]*((variables[6] < variables[18])?variables[2]:NAN)*(variables[184] && variables[187]);
    variables[207] = (variables[1] && variables[2])/(((variables[6] > variables[18])?variables[2]:NAN)/(variables[183]/((variables[6] > variables[18])?variables[2]:NAN)));
    variables[208] = (variables[1] && variables[2])/(((variables[6] < variables[18])?variables[2]:NAN)/(variables[183]/((variables[6] < variables[18])?variables[2]:NAN)));
    variables[209] = (variables[1] || variables[2]) && xor(variables[1], variables[2]) && ((variables[6] > variables[18])?variables[2]:NAN) && variables[183] && ((variables[6] > variables[18])?variables[2]:NAN) && xor(variables[1], variables[2]) && (variables[1] || variables[2]);
    variables[210] = (variables[1] && variables[2]) || xor(variables[1], variables[2]) || ((variables[6] > variables[18])?variables[2]:NAN) || variables[183] || ((variables[6] > variables[18])?variables[2]:NAN) || xor(variables[1], variables[2]) || (variables[1] && variables[2]);
    variables[211] = xor(variables[1] && variables[2], xor(variables[1] || variables[2], xor((variables[6] > variables[18])?variables[2]:NAN, xor(xor(xor(variables[183], (variables[6] > variables[18])?variables[2]:NAN), variables[1] || variables[2]), variables[1] && variables[2]))));
    variables[212] = pow(variables[1] && variables[2], pow((variables[6] > variables[18])?variables[2]:NAN, pow(pow(variables[183], (variables[6] > variables[18])?variables[2]:NAN), variables[1] && variables[2])));
    variables[213] = pow(pow(pow(variables[1] && variables[2], 1.0/pow((variables[6] > variables[18])?variables[2]:NAN, 1.0/variables[183])), 1.0/((variables[6] > variables[18])?variables[2]:NAN)), 1.0/(variables[1] && variables[2]));
    variables[214] = -(variables[1] && variables[2])+-((variables[6] > variables[18])?variables[2]:NAN);
    variables[215] = -(variables[1] && variables[2])+-((variables[6] < variables[18])?variables[2]:NAN);
}

void computeRates(double voi, double *states, double *rates, double *variables)
{
    rates[0] = 1.0;
}

void computeVariables(double voi, double *states, double *rates, double *variables)
{
    variables[63] = variables[1]/xor(variables[2], states[0]);
    findRoot0(voi, states, rates, variables);
}

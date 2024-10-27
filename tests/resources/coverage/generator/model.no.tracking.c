/* The content of this file was generated using the C profile of libCellML 0.6.0. */

#include "model.h"

#include <math.h>
#include <stdlib.h>

const char VERSION[] = "0.6.0";
const char LIBCELLML_VERSION[] = "0.6.0";

const size_t STATE_COUNT = 1;
const size_t CONSTANT_COUNT = 0;
const size_t COMPUTED_CONSTANT_COUNT = 0;
const size_t ALGEBRAIC_COUNT = 0;

const VariableInfo VOI_INFO = {"t", "second", "my_component"};

const VariableInfo STATE_INFO[] = {
    {"x", "dimensionless", "my_component"}
};

const VariableInfo CONSTANT_INFO[] = {
};

const VariableInfo COMPUTED_CONSTANT_INFO[] = {
};

const VariableInfo ALGEBRAIC_INFO[] = {
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

    algebraic[0] = u[0];
    algebraic[1] = u[1];

    f[0] = my_component_eqnNlaVariable1+my_component_eqnNlaVariable2+states[0]-0.0;
    f[1] = my_component_eqnNlaVariable1-my_component_eqnNlaVariable2-(my_component_eqnComputedConstant1+my_component_eqnComputedConstant2);
}

void findRoot0(double voi, double *states, double *rates, double *constants, double *computedConstants, double *algebraic)
{
    RootFindingInfo rfi = { voi, states, rates, constants, computedConstants, algebraic };
    double u[2];

    u[0] = algebraic[0];
    u[1] = algebraic[1];

    nlaSolve(objectiveFunction0, u, 2, &rfi);

    algebraic[0] = u[0];
    algebraic[1] = u[1];
}

void initialiseVariables(double *states, double *rates, double *constants, double *computedConstants, double *algebraic)
{
    states[0] = 0.0;
    double my_component_eqnCnInteger = 123.0;
    double my_component_eqnCnDouble = 123.456789;
    double my_component_eqnCnIntegerWithExponent = 123.0e99;
    double my_component_eqnCnDoubleWithExponent = 123.456789e99;
    double my_component_eqnTrue = 1.0;
    double my_component_eqnFalse = 0.0;
    double my_component_eqnExponentiale = 2.71828182845905;
    double my_component_eqnPi = 3.14159265358979;
    double my_component_eqnInfinity = INFINITY;
    double my_component_eqnNotanumber = NAN;
    double my_component_eqnComputedConstant1 = 1.0;
    double my_component_eqnComputedConstant2 = 3.0;
}

void computeComputedConstants(double *constants, double *computedConstants)
{
}

void computeRates(double voi, double *states, double *rates, double *constants, double *computedConstants, double *algebraic)
{
    rates[0] = 1.0;
}

void computeVariables(double voi, double *states, double *rates, double *constants, double *computedConstants, double *algebraic)
{
    double my_component_m = 1.0;
    double my_component_n = 2.0;
    double my_component_eqnEq = my_component_m == my_component_n;
    double my_component_eqnEqCoverageParentheses = my_component_m/(my_component_n == my_component_n);
    double my_component_eqnNeq = my_component_m != my_component_n;
    double my_component_o = 3.0;
    double my_component_eqnNeqCoverageParentheses = my_component_m/(my_component_n != my_component_o);
    double my_component_eqnLt = my_component_m < my_component_n;
    double my_component_eqnLtCoverageParentheses = my_component_m/(my_component_n < my_component_o);
    double my_component_eqnLeq = my_component_m <= my_component_n;
    double my_component_eqnLeqCoverageParentheses = my_component_m/(my_component_n <= my_component_o);
    double my_component_eqnGt = my_component_m > my_component_n;
    double my_component_eqnGtCoverageParentheses = my_component_m/(my_component_n > my_component_o);
    double my_component_eqnGeq = my_component_m >= my_component_n;
    double my_component_eqnGeqCoverageParentheses = my_component_m/(my_component_n >= my_component_o);
    double my_component_eqnAnd = my_component_m && my_component_n;
    double my_component_eqnAndMultiple = my_component_m && my_component_n && my_component_o;
    double my_component_p = 4.0;
    double my_component_eqnAndParentheses = (my_component_m < my_component_n) && (my_component_o > my_component_p);
    double my_component_eqnAndParenthesesLeftPlusWith = (my_component_m+my_component_n) && (my_component_o > my_component_p);
    double my_component_eqnAndParenthesesLeftPlusWithout = my_component_m && (my_component_n > my_component_o);
    double my_component_eqnAndParenthesesLeftMinusWith = (my_component_m-my_component_n) && (my_component_o > my_component_p);
    double my_component_eqnAndParenthesesLeftMinusWithout = -my_component_m && (my_component_n > my_component_o);
    double my_component_eqnAndParenthesesLeftPower = pow(my_component_m, my_component_n) && (my_component_o > my_component_p);
    double my_component_eqnAndParenthesesLeftRoot = pow(my_component_m, 1.0/my_component_n) && (my_component_o > my_component_p);
    double my_component_eqnAndParenthesesRightPlusWith = (my_component_m < my_component_n) && (my_component_o+my_component_p);
    double my_component_eqnAndParenthesesRightPlusWithout = (my_component_m < my_component_n) && my_component_o;
    double my_component_eqnAndParenthesesRightMinusWith = (my_component_m < my_component_n) && (my_component_o-my_component_p);
    double my_component_eqnAndParenthesesRightMinusWithout = (my_component_m < my_component_n) && -my_component_o;
    double my_component_eqnAndParenthesesRightPower = (my_component_m < my_component_n) && pow(my_component_o, my_component_p);
    double my_component_eqnAndParenthesesRightRoot = (my_component_m < my_component_n) && pow(my_component_o, 1.0/my_component_p);
    double my_component_eqnAndCoverageParentheses = my_component_m/(my_component_n && my_component_o);
    double my_component_eqnOr = my_component_m || my_component_n;
    double my_component_eqnOrMultiple = my_component_m || my_component_n || my_component_o;
    double my_component_eqnOrParentheses = (my_component_m < my_component_n) || (my_component_o > my_component_p);
    double my_component_eqnOrParenthesesLeftPlusWith = (my_component_m+my_component_n) || (my_component_o > my_component_p);
    double my_component_eqnOrParenthesesLeftPlusWithout = my_component_m || (my_component_n > my_component_o);
    double my_component_eqnOrParenthesesLeftMinusWith = (my_component_m-my_component_n) || (my_component_o > my_component_p);
    double my_component_eqnOrParenthesesLeftMinusWithout = -my_component_m || (my_component_n > my_component_o);
    double my_component_eqnOrParenthesesLeftPower = pow(my_component_m, my_component_n) || (my_component_o > my_component_p);
    double my_component_eqnOrParenthesesLeftRoot = pow(my_component_m, 1.0/my_component_n) || (my_component_o > my_component_p);
    double my_component_eqnOrParenthesesRightPlusWith = (my_component_m < my_component_n) || (my_component_o+my_component_p);
    double my_component_eqnOrParenthesesRightPlusWithout = (my_component_m < my_component_n) || my_component_o;
    double my_component_eqnOrParenthesesRightMinusWith = (my_component_m < my_component_n) || (my_component_o-my_component_p);
    double my_component_eqnOrParenthesesRightMinusWithout = (my_component_m < my_component_n) || -my_component_o;
    double my_component_eqnOrParenthesesRightPower = (my_component_m < my_component_n) || pow(my_component_o, my_component_p);
    double my_component_eqnOrParenthesesRightRoot = (my_component_m < my_component_n) || pow(my_component_o, 1.0/my_component_p);
    double my_component_eqnOrCoverageParentheses = my_component_m/(my_component_n || my_component_o);
    double my_component_eqnXor = xor(my_component_m, my_component_n);
    double my_component_eqnXorMultiple = xor(my_component_m, xor(my_component_n, my_component_o));
    double my_component_eqnXorParentheses = xor(my_component_m < my_component_n, my_component_o > my_component_p);
    double my_component_eqnXorParenthesesLeftPlusWith = xor(my_component_m+my_component_n, my_component_o > my_component_p);
    double my_component_eqnXorParenthesesLeftPlusWithout = xor(my_component_m, my_component_n > my_component_o);
    double my_component_eqnXorParenthesesLeftMinusWith = xor(my_component_m-my_component_n, my_component_o > my_component_p);
    double my_component_eqnXorParenthesesLeftMinusWithout = xor(-my_component_m, my_component_n > my_component_o);
    double my_component_eqnXorParenthesesLeftPower = xor(pow(my_component_m, my_component_n), my_component_o > my_component_p);
    double my_component_eqnXorParenthesesLeftRoot = xor(pow(my_component_m, 1.0/my_component_n), my_component_o > my_component_p);
    double my_component_eqnXorParenthesesRightPlusWith = xor(my_component_m < my_component_n, my_component_o+my_component_p);
    double my_component_eqnXorParenthesesRightPlusWithout = xor(my_component_m < my_component_n, my_component_o);
    double my_component_eqnXorParenthesesRightMinusWith = xor(my_component_m < my_component_n, my_component_o-my_component_p);
    double my_component_eqnXorParenthesesRightMinusWithout = xor(my_component_m < my_component_n, -my_component_o);
    double my_component_eqnXorParenthesesRightPower = xor(my_component_m < my_component_n, pow(my_component_o, my_component_p));
    double my_component_eqnXorParenthesesRightRoot = xor(my_component_m < my_component_n, pow(my_component_o, 1.0/my_component_p));
    double my_component_eqnXorCoverageParentheses = my_component_m/xor(my_component_n, my_component_o);
    double my_component_eqnNot = !my_component_m;
    double my_component_eqnPlus = my_component_m+my_component_n;
    double my_component_eqnPlusMultiple = my_component_m+my_component_n+my_component_o;
    double my_component_eqnPlusParentheses = (my_component_m < my_component_n)+(my_component_o > my_component_p);
    double my_component_eqnPlusUnary = my_component_m;
    double my_component_eqnMinus = my_component_m-my_component_n;
    double my_component_eqnMinusParentheses = (my_component_m < my_component_n)-(my_component_o > my_component_p);
    double my_component_eqnMinusParenthesesPlusWith = (my_component_m < my_component_n)-(my_component_o+my_component_p);
    double my_component_eqnMinusParenthesesPlusWithout = (my_component_m < my_component_n)-my_component_o;
    double my_component_eqnMinusParenthesesDirectUnaryMinus = my_component_m-(-my_component_n);
    double my_component_eqnMinusParenthesesIndirectUnaryMinus = my_component_m-(-my_component_n*my_component_o);
    double my_component_eqnMinusUnary = -my_component_m;
    double my_component_eqnMinusUnaryParentheses = -(my_component_m < my_component_n);
    double my_component_eqnTimes = my_component_m*my_component_n;
    double my_component_eqnTimesMultiple = my_component_m*my_component_n*my_component_o;
    double my_component_eqnTimesParentheses = (my_component_m < my_component_n)*(my_component_o > my_component_p);
    double my_component_eqnTimesParenthesesLeftPlusWith = (my_component_m+my_component_n)*(my_component_o > my_component_p);
    double my_component_eqnTimesParenthesesLeftPlusWithout = my_component_m*(my_component_n > my_component_o);
    double my_component_eqnTimesParenthesesLeftMinusWith = (my_component_m-my_component_n)*(my_component_o > my_component_p);
    double my_component_eqnTimesParenthesesLeftMinusWithout = -my_component_m*(my_component_n > my_component_o);
    double my_component_eqnTimesParenthesesRightPlusWith = (my_component_m < my_component_n)*(my_component_o+my_component_p);
    double my_component_eqnTimesParenthesesRightPlusWithout = (my_component_m < my_component_n)*my_component_o;
    double my_component_eqnTimesParenthesesRightMinusWith = (my_component_m < my_component_n)*(my_component_o-my_component_p);
    double my_component_eqnTimesParenthesesRightMinusWithout = (my_component_m < my_component_n)*-my_component_o;
    double my_component_eqnDivide = my_component_m/my_component_n;
    double my_component_eqnDivideParentheses = (my_component_m < my_component_n)/(my_component_p > my_component_o);
    double my_component_eqnDivideParenthesesLeftPlusWith = (my_component_m+my_component_n)/(my_component_p > my_component_o);
    double my_component_eqnDivideParenthesesLeftPlusWithout = my_component_m/(my_component_o > my_component_n);
    double my_component_eqnDivideParenthesesLeftMinusWith = (my_component_m-my_component_n)/(my_component_p > my_component_o);
    double my_component_eqnDivideParenthesesLeftMinusWithout = -my_component_m/(my_component_o > my_component_n);
    double my_component_eqnDivideParenthesesRightPlusWith = (my_component_m < my_component_n)/(my_component_o+my_component_p);
    double my_component_eqnDivideParenthesesRightPlusWithout = (my_component_m < my_component_n)/my_component_o;
    double my_component_eqnDivideParenthesesRightMinusWith = (my_component_m < my_component_n)/(my_component_o-my_component_p);
    double my_component_eqnDivideParenthesesRightMinusWithout = (my_component_m < my_component_n)/-my_component_o;
    double my_component_eqnDivideParenthesesRightTimes = (my_component_m < my_component_n)/(my_component_o*my_component_p);
    double my_component_eqnDivideParenthesesRightDivide = (my_component_m < my_component_n)/(my_component_o/my_component_p);
    double my_component_eqnPowerSqrt = sqrt(my_component_m);
    double my_component_eqnPowerSqr = pow(my_component_m, 2.0);
    double my_component_eqnPowerCube = pow(my_component_m, 3.0);
    double my_component_eqnPowerCi = pow(my_component_m, my_component_n);
    double my_component_eqnPowerParentheses = pow(my_component_m <= my_component_n, my_component_o >= my_component_p);
    double my_component_eqnPowerParenthesesLeftPlusWith = pow(my_component_m+my_component_n, my_component_o >= my_component_p);
    double my_component_eqnPowerParenthesesLeftPlusWithout = pow(my_component_m, my_component_n >= my_component_o);
    double my_component_eqnPowerParenthesesLeftMinusWith = pow(my_component_m-my_component_n, my_component_o >= my_component_p);
    double my_component_eqnPowerParenthesesLeftMinusWithout = pow(-my_component_m, my_component_n >= my_component_o);
    double my_component_eqnPowerParenthesesLeftTimes = pow(my_component_m*my_component_n, my_component_o >= my_component_p);
    double my_component_eqnPowerParenthesesLeftDivide = pow(my_component_m/my_component_n, my_component_o >= my_component_p);
    double my_component_eqnPowerParenthesesRightPlusWith = pow(my_component_m <= my_component_n, my_component_o+my_component_p);
    double my_component_eqnPowerParenthesesRightPlusWithout = pow(my_component_m <= my_component_n, my_component_o);
    double my_component_eqnPowerParenthesesRightMinusWith = pow(my_component_m <= my_component_n, my_component_o-my_component_p);
    double my_component_eqnPowerParenthesesRightMinusWithout = pow(my_component_m <= my_component_n, -my_component_o);
    double my_component_eqnPowerParenthesesRightTimes = pow(my_component_m <= my_component_n, my_component_o*my_component_p);
    double my_component_eqnPowerParenthesesRightDivide = pow(my_component_m <= my_component_n, my_component_o/my_component_p);
    double my_component_eqnPowerParenthesesRightPower = pow(my_component_m <= my_component_n, pow(my_component_o, my_component_p));
    double my_component_eqnPowerParenthesesRightRoot = pow(my_component_m <= my_component_n, pow(my_component_o, 1.0/my_component_p));
    double my_component_eqnRootSqrt = sqrt(my_component_m);
    double my_component_eqnRootSqrtOther = sqrt(my_component_m);
    double my_component_eqnRootCube = pow(my_component_m, 1.0/3.0);
    double my_component_eqnRootCi = pow(my_component_m, 1.0/my_component_n);
    double my_component_eqnRootParentheses = pow(my_component_m < my_component_n, 1.0/(my_component_p > my_component_o));
    double my_component_eqnRootParenthesesLeftPlusWith = pow(my_component_m+my_component_n, 1.0/(my_component_p > my_component_o));
    double my_component_eqnRootParenthesesLeftPlusWithout = pow(my_component_m, 1.0/(my_component_o > my_component_n));
    double my_component_eqnRootParenthesesLeftMinusWith = pow(my_component_m-my_component_n, 1.0/(my_component_p > my_component_o));
    double my_component_eqnRootParenthesesLeftMinusWithout = pow(-my_component_m, 1.0/(my_component_o > my_component_n));
    double my_component_eqnRootParenthesesLeftTimes = pow(my_component_m*my_component_n, 1.0/(my_component_p > my_component_o));
    double my_component_eqnRootParenthesesLeftDivide = pow(my_component_m/my_component_n, 1.0/(my_component_p > my_component_o));
    double my_component_eqnRootParenthesesRightPlusWith = pow(my_component_m < my_component_n, 1.0/(my_component_o+my_component_p));
    double my_component_eqnRootParenthesesRightPlusWithout = pow(my_component_m < my_component_n, 1.0/my_component_o);
    double my_component_eqnRootParenthesesRightMinusWith = pow(my_component_m < my_component_n, 1.0/(my_component_o-my_component_p));
    double my_component_eqnRootParenthesesRightMinusWithout = pow(my_component_m < my_component_n, 1.0/-my_component_o);
    double my_component_eqnRootParenthesesRightTimes = pow(my_component_m < my_component_n, 1.0/(my_component_o*my_component_p));
    double my_component_eqnRootParenthesesRightDivide = pow(my_component_m < my_component_n, 1.0/(my_component_o/my_component_p));
    double my_component_eqnRootParenthesesRightPower = pow(my_component_m < my_component_n, 1.0/pow(my_component_o, my_component_p));
    double my_component_eqnRootParenthesesRightRoot = pow(my_component_m < my_component_n, 1.0/pow(my_component_o, 1.0/my_component_p));
    double my_component_eqnAbs = fabs(my_component_m);
    double my_component_eqnExp = exp(my_component_m);
    double my_component_eqnLn = log(my_component_m);
    double my_component_eqnLog = log10(my_component_m);
    double my_component_eqnLog2 = log(my_component_m)/log(2.0);
    double my_component_eqnLog10 = log10(my_component_m);
    double my_component_eqnLogCi = log(my_component_m)/log(my_component_n);
    double my_component_eqnCeiling = ceil(my_component_m);
    double my_component_eqnFloor = floor(my_component_m);
    double my_component_eqnMin = min(my_component_m, my_component_n);
    double my_component_eqnMinMultiple = min(my_component_m, min(my_component_n, my_component_o));
    double my_component_eqnMax = max(my_component_m, my_component_n);
    double my_component_eqnMaxMultiple = max(my_component_m, max(my_component_n, my_component_o));
    double my_component_eqnRem = fmod(my_component_m, my_component_n);
    double my_component_eqnSin = sin(my_component_m);
    double my_component_eqnCos = cos(my_component_m);
    double my_component_eqnTan = tan(my_component_m);
    double my_component_eqnSec = sec(my_component_m);
    double my_component_eqnCsc = csc(my_component_m);
    double my_component_eqnCot = cot(my_component_m);
    double my_component_eqnSinh = sinh(my_component_m);
    double my_component_eqnCosh = cosh(my_component_m);
    double my_component_eqnTanh = tanh(my_component_m);
    double my_component_eqnSech = sech(my_component_m);
    double my_component_eqnCsch = csch(my_component_m);
    double my_component_eqnCoth = coth(my_component_m);
    double my_component_eqnArcsin = asin(my_component_m);
    double my_component_eqnArccos = acos(my_component_m);
    double my_component_eqnArctan = atan(my_component_m);
    double my_component_eqnArcsec = asec(my_component_m);
    double my_component_eqnArccsc = acsc(my_component_m);
    double my_component_eqnArccot = acot(my_component_m);
    double my_component_eqnArcsinh = asinh(my_component_m);
    double my_component_eqnArccosh = acosh(my_component_m);
    double my_component_eqnArctanh = atanh(my_component_m/2.0);
    double my_component_eqnArcsech = asech(my_component_m);
    double my_component_eqnArccsch = acsch(my_component_m);
    double my_component_eqnArccoth = acoth(2.0*my_component_m);
    double my_component_eqnPiecewisePiece = (my_component_m > my_component_n)?my_component_m:NAN;
    double my_component_eqnPiecewisePieceOtherwise = (my_component_m > my_component_n)?my_component_m:my_component_o;
    double my_component_q = 5.0;
    double my_component_r = 6.0;
    double my_component_eqnPiecewisePiecePiecePiece = (my_component_m > my_component_n)?my_component_m:(my_component_o > my_component_p)?my_component_o:(my_component_q > my_component_r)?my_component_q:NAN;
    double my_component_s = 7.0;
    double my_component_eqnPiecewisePiecePiecePieceOtherwise = (my_component_m > my_component_n)?my_component_m:(my_component_o > my_component_p)?my_component_o:(my_component_q > my_component_r)?my_component_q:my_component_s;
    double my_component_eqnWithPiecewise = 123.0+((my_component_m > my_component_n)?my_component_m:NAN);
    double my_component_eqnCi = my_component_m;
    double my_component_eqnCoverageForPlusOperator = (my_component_m && my_component_n)+((my_component_o > my_component_p)?my_component_n:NAN)+my_component_q+(my_component_r && my_component_s);
    double my_component_eqnCoverageForMinusOperator = (my_component_m && my_component_n)-(((my_component_o > my_component_p)?my_component_n:NAN)-(my_component_q-((my_component_o > my_component_p)?my_component_n:NAN)))-(my_component_r && my_component_s);
    double my_component_eqnCoverageForTimesOperator = (my_component_m && my_component_n)*((my_component_o > my_component_p)?my_component_n:NAN)*my_component_q*((my_component_o > my_component_p)?my_component_n:NAN)*(my_component_r && my_component_s);
    double my_component_eqnCoverageForDivideOperator = (my_component_m && my_component_n)/(((my_component_o > my_component_p)?my_component_n:NAN)/(my_component_q/((my_component_o > my_component_p)?my_component_n:NAN)));
    double my_component_eqnCoverageForAndOperator = (my_component_m || my_component_n) && xor(my_component_m, my_component_n) && ((my_component_o > my_component_p)?my_component_n:NAN) && my_component_q && ((my_component_o > my_component_p)?my_component_n:NAN) && xor(my_component_m, my_component_n) && (my_component_m || my_component_n);
    double my_component_eqnCoverageForOrOperator = (my_component_m && my_component_n) || xor(my_component_m, my_component_n) || ((my_component_o > my_component_p)?my_component_n:NAN) || my_component_q || ((my_component_o > my_component_p)?my_component_n:NAN) || xor(my_component_m, my_component_n) || (my_component_m && my_component_n);
    double my_component_eqnCoverageForXorOperator = xor(my_component_m && my_component_n, xor(my_component_m || my_component_n, xor((my_component_o > my_component_p)?my_component_n:NAN, xor(xor(xor(my_component_q, (my_component_o > my_component_p)?my_component_n:NAN), my_component_m || my_component_n), my_component_m && my_component_n))));
    double my_component_eqnCoverageForPowerOperator = pow(my_component_m && my_component_n, pow((my_component_o > my_component_p)?my_component_n:NAN, pow(pow(my_component_q, (my_component_o > my_component_p)?my_component_n:NAN), my_component_m && my_component_n)));
    double my_component_eqnCoverageForRootOperator = pow(pow(pow(my_component_m && my_component_n, 1.0/pow((my_component_o > my_component_p)?my_component_n:NAN, 1.0/my_component_q)), 1.0/((my_component_o > my_component_p)?my_component_n:NAN)), 1.0/(my_component_m && my_component_n));
    double my_component_eqnCoverageForMinusUnary = -(my_component_m && my_component_n)+-((my_component_o > my_component_p)?my_component_n:NAN);
    findRoot0(voi, states, rates, constants, computedConstants, algebraic);
}

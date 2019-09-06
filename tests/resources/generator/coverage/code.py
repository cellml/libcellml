# The contents of this file was generated from version 0.2.0 of libCellML.
from math import *


__version__ = "0.2.0"

STATE_VECTOR_SIZE = 1
VARIABLE_VECTOR_SIZE = 185
VOI = {"component": "my_component", "name": "t", "units": "second"}

STATE_VECTOR_INFORMATION_ARRAY = [
    {"component": "my_component", "name": "x", "units": "dimensionless"},
]

VARIABLE_VECTOR_INFORMATION_ARRAY = [
    {"component": "my_component", "name": "m", "units": "dimensionless"},
    {"component": "my_component", "name": "n", "units": "dimensionless"},
    {"component": "my_component", "name": "o", "units": "dimensionless"},
    {"component": "my_component", "name": "p", "units": "dimensionless"},
    {"component": "my_component", "name": "q", "units": "dimensionless"},
    {"component": "my_component", "name": "r", "units": "dimensionless"},
    {"component": "my_component", "name": "s", "units": "dimensionless"},
    {"component": "my_component", "name": "eqnCnInteger", "units": "dimensionless"},
    {"component": "my_component", "name": "eqnCnDouble", "units": "dimensionless"},
    {"component": "my_component", "name": "eqnCnIntegerWithExponent", "units": "dimensionless"},
    {"component": "my_component", "name": "eqnCnDoubleWithExponent", "units": "dimensionless"},
    {"component": "my_component", "name": "eqnTrue", "units": "dimensionless"},
    {"component": "my_component", "name": "eqnFalse", "units": "dimensionless"},
    {"component": "my_component", "name": "eqnExponentiale", "units": "dimensionless"},
    {"component": "my_component", "name": "eqnPi", "units": "dimensionless"},
    {"component": "my_component", "name": "eqnInfinity", "units": "dimensionless"},
    {"component": "my_component", "name": "eqnNotanumber", "units": "dimensionless"},
    {"component": "my_component", "name": "eqnEqEq", "units": "dimensionless"},
    {"component": "my_component", "name": "eqnEqEqCoverageParentheses", "units": "dimensionless"},
    {"component": "my_component", "name": "eqnNeq", "units": "dimensionless"},
    {"component": "my_component", "name": "eqnNeqCoverageParentheses", "units": "dimensionless"},
    {"component": "my_component", "name": "eqnLt", "units": "dimensionless"},
    {"component": "my_component", "name": "eqnLeq", "units": "dimensionless"},
    {"component": "my_component", "name": "eqnGt", "units": "dimensionless"},
    {"component": "my_component", "name": "eqnGeq", "units": "dimensionless"},
    {"component": "my_component", "name": "eqnAnd", "units": "dimensionless"},
    {"component": "my_component", "name": "eqnAndMultiple", "units": "dimensionless"},
    {"component": "my_component", "name": "eqnAndParentheses", "units": "dimensionless"},
    {"component": "my_component", "name": "eqnAndParenthesesLeftPlusWith", "units": "dimensionless"},
    {"component": "my_component", "name": "eqnAndParenthesesLeftPlusWithout", "units": "dimensionless"},
    {"component": "my_component", "name": "eqnAndParenthesesLeftMinusWith", "units": "dimensionless"},
    {"component": "my_component", "name": "eqnAndParenthesesLeftMinusWithout", "units": "dimensionless"},
    {"component": "my_component", "name": "eqnAndParenthesesLeftPower", "units": "dimensionless"},
    {"component": "my_component", "name": "eqnAndParenthesesLeftRoot", "units": "dimensionless"},
    {"component": "my_component", "name": "eqnAndParenthesesRightPlusWith", "units": "dimensionless"},
    {"component": "my_component", "name": "eqnAndParenthesesRightPlusWithout", "units": "dimensionless"},
    {"component": "my_component", "name": "eqnAndParenthesesRightMinusWith", "units": "dimensionless"},
    {"component": "my_component", "name": "eqnAndParenthesesRightMinusWithout", "units": "dimensionless"},
    {"component": "my_component", "name": "eqnAndParenthesesRightPower", "units": "dimensionless"},
    {"component": "my_component", "name": "eqnAndParenthesesRightRoot", "units": "dimensionless"},
    {"component": "my_component", "name": "eqnOr", "units": "dimensionless"},
    {"component": "my_component", "name": "eqnOrMultiple", "units": "dimensionless"},
    {"component": "my_component", "name": "eqnOrParentheses", "units": "dimensionless"},
    {"component": "my_component", "name": "eqnOrParenthesesLeftPlusWith", "units": "dimensionless"},
    {"component": "my_component", "name": "eqnOrParenthesesLeftPlusWithout", "units": "dimensionless"},
    {"component": "my_component", "name": "eqnOrParenthesesLeftMinusWith", "units": "dimensionless"},
    {"component": "my_component", "name": "eqnOrParenthesesLeftMinusWithout", "units": "dimensionless"},
    {"component": "my_component", "name": "eqnOrParenthesesLeftPower", "units": "dimensionless"},
    {"component": "my_component", "name": "eqnOrParenthesesLeftRoot", "units": "dimensionless"},
    {"component": "my_component", "name": "eqnOrParenthesesRightPlusWith", "units": "dimensionless"},
    {"component": "my_component", "name": "eqnOrParenthesesRightPlusWithout", "units": "dimensionless"},
    {"component": "my_component", "name": "eqnOrParenthesesRightMinusWith", "units": "dimensionless"},
    {"component": "my_component", "name": "eqnOrParenthesesRightMinusWithout", "units": "dimensionless"},
    {"component": "my_component", "name": "eqnOrParenthesesRightPower", "units": "dimensionless"},
    {"component": "my_component", "name": "eqnOrParenthesesRightRoot", "units": "dimensionless"},
    {"component": "my_component", "name": "eqnXor", "units": "dimensionless"},
    {"component": "my_component", "name": "eqnXorMultiple", "units": "dimensionless"},
    {"component": "my_component", "name": "eqnXorParentheses", "units": "dimensionless"},
    {"component": "my_component", "name": "eqnXorParenthesesLeftPlusWith", "units": "dimensionless"},
    {"component": "my_component", "name": "eqnXorParenthesesLeftPlusWithout", "units": "dimensionless"},
    {"component": "my_component", "name": "eqnXorParenthesesLeftMinusWith", "units": "dimensionless"},
    {"component": "my_component", "name": "eqnXorParenthesesLeftMinusWithout", "units": "dimensionless"},
    {"component": "my_component", "name": "eqnXorParenthesesLeftPower", "units": "dimensionless"},
    {"component": "my_component", "name": "eqnXorParenthesesLeftRoot", "units": "dimensionless"},
    {"component": "my_component", "name": "eqnXorParenthesesRightPlusWith", "units": "dimensionless"},
    {"component": "my_component", "name": "eqnXorParenthesesRightPlusWithout", "units": "dimensionless"},
    {"component": "my_component", "name": "eqnXorParenthesesRightMinusWith", "units": "dimensionless"},
    {"component": "my_component", "name": "eqnXorParenthesesRightMinusWithout", "units": "dimensionless"},
    {"component": "my_component", "name": "eqnXorParenthesesRightPower", "units": "dimensionless"},
    {"component": "my_component", "name": "eqnXorParenthesesRightRoot", "units": "dimensionless"},
    {"component": "my_component", "name": "eqnNot", "units": "dimensionless"},
    {"component": "my_component", "name": "eqnPlus", "units": "dimensionless"},
    {"component": "my_component", "name": "eqnPlusMultiple", "units": "dimensionless"},
    {"component": "my_component", "name": "eqnPlusParentheses", "units": "dimensionless"},
    {"component": "my_component", "name": "eqnPlusUnary", "units": "dimensionless"},
    {"component": "my_component", "name": "eqnMinus", "units": "dimensionless"},
    {"component": "my_component", "name": "eqnMinusParentheses", "units": "dimensionless"},
    {"component": "my_component", "name": "eqnMinusParenthesesPlusWith", "units": "dimensionless"},
    {"component": "my_component", "name": "eqnMinusParenthesesPlusWithout", "units": "dimensionless"},
    {"component": "my_component", "name": "eqnMinusUnary", "units": "dimensionless"},
    {"component": "my_component", "name": "eqnMinusUnaryParentheses", "units": "dimensionless"},
    {"component": "my_component", "name": "eqnTimes", "units": "dimensionless"},
    {"component": "my_component", "name": "eqnTimesMultiple", "units": "dimensionless"},
    {"component": "my_component", "name": "eqnTimesParentheses", "units": "dimensionless"},
    {"component": "my_component", "name": "eqnTimesParenthesesLeftPlusWith", "units": "dimensionless"},
    {"component": "my_component", "name": "eqnTimesParenthesesLeftPlusWithout", "units": "dimensionless"},
    {"component": "my_component", "name": "eqnTimesParenthesesLeftMinusWith", "units": "dimensionless"},
    {"component": "my_component", "name": "eqnTimesParenthesesLeftMinusWithout", "units": "dimensionless"},
    {"component": "my_component", "name": "eqnTimesParenthesesRightPlusWith", "units": "dimensionless"},
    {"component": "my_component", "name": "eqnTimesParenthesesRightPlusWithout", "units": "dimensionless"},
    {"component": "my_component", "name": "eqnTimesParenthesesRightMinusWith", "units": "dimensionless"},
    {"component": "my_component", "name": "eqnTimesParenthesesRightMinusWithout", "units": "dimensionless"},
    {"component": "my_component", "name": "eqnDivide", "units": "dimensionless"},
    {"component": "my_component", "name": "eqnDivideParentheses", "units": "dimensionless"},
    {"component": "my_component", "name": "eqnDivideParenthesesLeftPlusWith", "units": "dimensionless"},
    {"component": "my_component", "name": "eqnDivideParenthesesLeftPlusWithout", "units": "dimensionless"},
    {"component": "my_component", "name": "eqnDivideParenthesesLeftMinusWith", "units": "dimensionless"},
    {"component": "my_component", "name": "eqnDivideParenthesesLeftMinusWithout", "units": "dimensionless"},
    {"component": "my_component", "name": "eqnDivideParenthesesRightPlusWith", "units": "dimensionless"},
    {"component": "my_component", "name": "eqnDivideParenthesesRightPlusWithout", "units": "dimensionless"},
    {"component": "my_component", "name": "eqnDivideParenthesesRightMinusWith", "units": "dimensionless"},
    {"component": "my_component", "name": "eqnDivideParenthesesRightMinusWithout", "units": "dimensionless"},
    {"component": "my_component", "name": "eqnDivideParenthesesRightTimes", "units": "dimensionless"},
    {"component": "my_component", "name": "eqnDivideParenthesesRightDivide", "units": "dimensionless"},
    {"component": "my_component", "name": "eqnPowerSqrt", "units": "dimensionless"},
    {"component": "my_component", "name": "eqnPowerSqr", "units": "dimensionless"},
    {"component": "my_component", "name": "eqnPowerCube", "units": "dimensionless"},
    {"component": "my_component", "name": "eqnPowerCi", "units": "dimensionless"},
    {"component": "my_component", "name": "eqnPowerParentheses", "units": "dimensionless"},
    {"component": "my_component", "name": "eqnPowerParenthesesLeftPlusWith", "units": "dimensionless"},
    {"component": "my_component", "name": "eqnPowerParenthesesLeftPlusWithout", "units": "dimensionless"},
    {"component": "my_component", "name": "eqnPowerParenthesesLeftMinusWith", "units": "dimensionless"},
    {"component": "my_component", "name": "eqnPowerParenthesesLeftMinusWithout", "units": "dimensionless"},
    {"component": "my_component", "name": "eqnPowerParenthesesLeftTimes", "units": "dimensionless"},
    {"component": "my_component", "name": "eqnPowerParenthesesLeftDivide", "units": "dimensionless"},
    {"component": "my_component", "name": "eqnPowerParenthesesRightPlusWith", "units": "dimensionless"},
    {"component": "my_component", "name": "eqnPowerParenthesesRightPlusWithout", "units": "dimensionless"},
    {"component": "my_component", "name": "eqnPowerParenthesesRightMinusWith", "units": "dimensionless"},
    {"component": "my_component", "name": "eqnPowerParenthesesRightMinusWithout", "units": "dimensionless"},
    {"component": "my_component", "name": "eqnPowerParenthesesRightTimes", "units": "dimensionless"},
    {"component": "my_component", "name": "eqnPowerParenthesesRightDivide", "units": "dimensionless"},
    {"component": "my_component", "name": "eqnPowerParenthesesRightPower", "units": "dimensionless"},
    {"component": "my_component", "name": "eqnPowerParenthesesRightRoot", "units": "dimensionless"},
    {"component": "my_component", "name": "eqnRootSqrt", "units": "dimensionless"},
    {"component": "my_component", "name": "eqnRootSqrtOther", "units": "dimensionless"},
    {"component": "my_component", "name": "eqnRootCube", "units": "dimensionless"},
    {"component": "my_component", "name": "eqnRootCi", "units": "dimensionless"},
    {"component": "my_component", "name": "eqnRootParentheses", "units": "dimensionless"},
    {"component": "my_component", "name": "eqnRootParenthesesLeftPlusWith", "units": "dimensionless"},
    {"component": "my_component", "name": "eqnRootParenthesesLeftPlusWithout", "units": "dimensionless"},
    {"component": "my_component", "name": "eqnRootParenthesesLeftMinusWith", "units": "dimensionless"},
    {"component": "my_component", "name": "eqnRootParenthesesLeftMinusWithout", "units": "dimensionless"},
    {"component": "my_component", "name": "eqnRootParenthesesLeftTimes", "units": "dimensionless"},
    {"component": "my_component", "name": "eqnRootParenthesesLeftDivide", "units": "dimensionless"},
    {"component": "my_component", "name": "eqnRootParenthesesRightPlusWith", "units": "dimensionless"},
    {"component": "my_component", "name": "eqnRootParenthesesRightPlusWithout", "units": "dimensionless"},
    {"component": "my_component", "name": "eqnRootParenthesesRightMinusWith", "units": "dimensionless"},
    {"component": "my_component", "name": "eqnRootParenthesesRightMinusWithout", "units": "dimensionless"},
    {"component": "my_component", "name": "eqnRootParenthesesRightTimes", "units": "dimensionless"},
    {"component": "my_component", "name": "eqnRootParenthesesRightDivide", "units": "dimensionless"},
    {"component": "my_component", "name": "eqnRootParenthesesRightPower", "units": "dimensionless"},
    {"component": "my_component", "name": "eqnRootParenthesesRightRoot", "units": "dimensionless"},
    {"component": "my_component", "name": "eqnAbs", "units": "dimensionless"},
    {"component": "my_component", "name": "eqnExp", "units": "dimensionless"},
    {"component": "my_component", "name": "eqnLn", "units": "dimensionless"},
    {"component": "my_component", "name": "eqnLog", "units": "dimensionless"},
    {"component": "my_component", "name": "eqnLog2", "units": "dimensionless"},
    {"component": "my_component", "name": "eqnLog10", "units": "dimensionless"},
    {"component": "my_component", "name": "eqnLogCi", "units": "dimensionless"},
    {"component": "my_component", "name": "eqnCeiling", "units": "dimensionless"},
    {"component": "my_component", "name": "eqnFloor", "units": "dimensionless"},
    {"component": "my_component", "name": "eqnMin", "units": "dimensionless"},
    {"component": "my_component", "name": "eqnMinMultiple", "units": "dimensionless"},
    {"component": "my_component", "name": "eqnMax", "units": "dimensionless"},
    {"component": "my_component", "name": "eqnMaxMultiple", "units": "dimensionless"},
    {"component": "my_component", "name": "eqnRem", "units": "dimensionless"},
    {"component": "my_component", "name": "eqnSin", "units": "dimensionless"},
    {"component": "my_component", "name": "eqnCos", "units": "dimensionless"},
    {"component": "my_component", "name": "eqnTan", "units": "dimensionless"},
    {"component": "my_component", "name": "eqnSec", "units": "dimensionless"},
    {"component": "my_component", "name": "eqnCsc", "units": "dimensionless"},
    {"component": "my_component", "name": "eqnCot", "units": "dimensionless"},
    {"component": "my_component", "name": "eqnSinh", "units": "dimensionless"},
    {"component": "my_component", "name": "eqnCosh", "units": "dimensionless"},
    {"component": "my_component", "name": "eqnTanh", "units": "dimensionless"},
    {"component": "my_component", "name": "eqnSech", "units": "dimensionless"},
    {"component": "my_component", "name": "eqnCsch", "units": "dimensionless"},
    {"component": "my_component", "name": "eqnCoth", "units": "dimensionless"},
    {"component": "my_component", "name": "eqnArcsin", "units": "dimensionless"},
    {"component": "my_component", "name": "eqnArccos", "units": "dimensionless"},
    {"component": "my_component", "name": "eqnArctan", "units": "dimensionless"},
    {"component": "my_component", "name": "eqnArcsec", "units": "dimensionless"},
    {"component": "my_component", "name": "eqnArccsc", "units": "dimensionless"},
    {"component": "my_component", "name": "eqnArccot", "units": "dimensionless"},
    {"component": "my_component", "name": "eqnArcsinh", "units": "dimensionless"},
    {"component": "my_component", "name": "eqnArccosh", "units": "dimensionless"},
    {"component": "my_component", "name": "eqnArctanh", "units": "dimensionless"},
    {"component": "my_component", "name": "eqnArcsech", "units": "dimensionless"},
    {"component": "my_component", "name": "eqnArccsch", "units": "dimensionless"},
    {"component": "my_component", "name": "eqnArccoth", "units": "dimensionless"},
    {"component": "my_component", "name": "eqnPiecewisePiece", "units": "dimensionless"},
    {"component": "my_component", "name": "eqnPiecewisePieceOtherwise", "units": "dimensionless"},
    {"component": "my_component", "name": "eqnPiecewisePiecePiecePiece", "units": "dimensionless"},
    {"component": "my_component", "name": "eqnPiecewisePiecePiecePieceOtherwise", "units": "dimensionless"},
    {"component": "my_component", "name": "eqnCi", "units": "dimensionless"},
]


def eq_eq_func(x, y):
    return 1.0 if x == y else 0.0


def neq_func(x, y):
    return 1.0 if x != y else 0.0


def lt_func(x, y):
    return 1.0 if x < y else 0.0


def leq_func(x, y):
    return 1.0 if x <= y else 0.0


def gt_func(x, y):
    return 1.0 if x > y else 0.0


def geq_func(x, y):
    return 1.0 if x >= y else 0.0


def and_func(x, y):
    return 1.0 if bool(x) & bool(y) else 0.0


def or_func(x, y):
    return 1.0 if bool(x) | bool(y) else 0.0


def xor_func(x, y):
    return 1.0 if bool(x) ^ bool(y) else 0.0


def not_func(x):
    return 1.0 if not bool(x) else 0.0


def min(x, y):
    return x if x < y else y


def max(x, y):
    return x if x > y else y


def sec(x):
    return 1.0/cos(x)


def csc(x):
    return 1.0/sin(x)


def cot(x):
    return 1.0/tan(x)


def sech(x):
    return 1.0/cosh(x)


def csch(x):
    return 1.0/sinh(x)


def coth(x):
    return 1.0/tanh(x)


def asec(x):
    return acos(1.0/x)


def acsc(x):
    return asin(1.0/x)


def acot(x):
    return atan(1.0/x)


def asech(x):
    one_over_x = 1.0/x

    return log(one_over_x+sqrt(one_over_x*one_over_x-1.0))


def acsch(x):
    one_over_x = 1.0/x

    return log(one_over_x+sqrt(one_over_x*one_over_x+1.0))


def acoth(x):
    one_over_x = 1.0/x

    return 0.5*log((1.0+one_over_x)/(1.0-one_over_x))


def create_state_vector():
    return [nan]*1


def create_rate_vector():
    return [nan]*1


def create_variable_vector():
    return [nan]*185


def initialize_constants(states, variables):
    states[0] = 0.0
    variables[0] = 1.0
    variables[1] = 2.0
    variables[2] = 3.0
    variables[3] = 4.0
    variables[4] = 5.0
    variables[5] = 6.0
    variables[6] = 7.0
    variables[174] = 123.0
    variables[175] = 123.456789
    variables[176] = 123.0e99
    variables[177] = 123.456789e99
    variables[179] = 1.0
    variables[180] = 0.0
    variables[181] = 2.71828182845905
    variables[182] = 3.14159265358979
    variables[183] = inf
    variables[184] = nan


def compute_computed_constants(variables):
    variables[7] = eq_eq_func(variables[0], variables[1])
    variables[8] = variables[0]/eq_eq_func(variables[1], variables[1])
    variables[9] = neq_func(variables[0], variables[1])
    variables[10] = variables[0]/neq_func(variables[1], variables[2])
    variables[11] = lt_func(variables[0], variables[1])
    variables[12] = leq_func(variables[0], variables[1])
    variables[13] = gt_func(variables[0], variables[1])
    variables[14] = geq_func(variables[0], variables[1])
    variables[15] = and_func(variables[0], variables[1])
    variables[16] = and_func(variables[0], and_func(variables[1], variables[2]))
    variables[17] = and_func(lt_func(variables[0], variables[1]), gt_func(variables[2], variables[3]))
    variables[18] = and_func(variables[0]+variables[1], gt_func(variables[2], variables[3]))
    variables[19] = and_func(variables[0], gt_func(variables[1], variables[2]))
    variables[20] = and_func(variables[0]-variables[1], gt_func(variables[2], variables[3]))
    variables[21] = and_func(-variables[0], gt_func(variables[1], variables[2]))
    variables[22] = and_func(pow(variables[0], variables[1]), gt_func(variables[2], variables[3]))
    variables[23] = and_func(pow(variables[0], 1.0/variables[1]), gt_func(variables[2], variables[3]))
    variables[24] = and_func(lt_func(variables[0], variables[1]), variables[2]+variables[3])
    variables[25] = and_func(lt_func(variables[0], variables[1]), variables[2])
    variables[26] = and_func(lt_func(variables[0], variables[1]), variables[2]-variables[3])
    variables[27] = and_func(lt_func(variables[0], variables[1]), -variables[2])
    variables[28] = and_func(lt_func(variables[0], variables[1]), pow(variables[2], variables[3]))
    variables[29] = and_func(lt_func(variables[0], variables[1]), pow(variables[2], 1.0/variables[3]))
    variables[30] = or_func(variables[0], variables[1])
    variables[31] = or_func(variables[0], or_func(variables[1], variables[2]))
    variables[32] = or_func(lt_func(variables[0], variables[1]), gt_func(variables[2], variables[3]))
    variables[33] = or_func(variables[0]+variables[1], gt_func(variables[2], variables[3]))
    variables[34] = or_func(variables[0], gt_func(variables[1], variables[2]))
    variables[35] = or_func(variables[0]-variables[1], gt_func(variables[2], variables[3]))
    variables[36] = or_func(-variables[0], gt_func(variables[1], variables[2]))
    variables[37] = or_func(pow(variables[0], variables[1]), gt_func(variables[2], variables[3]))
    variables[38] = or_func(pow(variables[0], 1.0/variables[1]), gt_func(variables[2], variables[3]))
    variables[39] = or_func(lt_func(variables[0], variables[1]), variables[2]+variables[3])
    variables[40] = or_func(lt_func(variables[0], variables[1]), variables[2])
    variables[41] = or_func(lt_func(variables[0], variables[1]), variables[2]-variables[3])
    variables[42] = or_func(lt_func(variables[0], variables[1]), -variables[2])
    variables[43] = or_func(lt_func(variables[0], variables[1]), pow(variables[2], variables[3]))
    variables[44] = or_func(lt_func(variables[0], variables[1]), pow(variables[2], 1.0/variables[3]))
    variables[45] = xor_func(variables[0], variables[1])
    variables[46] = xor_func(variables[0], xor_func(variables[1], variables[2]))
    variables[47] = xor_func(lt_func(variables[0], variables[1]), gt_func(variables[2], variables[3]))
    variables[48] = xor_func(variables[0]+variables[1], gt_func(variables[2], variables[3]))
    variables[49] = xor_func(variables[0], gt_func(variables[1], variables[2]))
    variables[50] = xor_func(variables[0]-variables[1], gt_func(variables[2], variables[3]))
    variables[51] = xor_func(-variables[0], gt_func(variables[1], variables[2]))
    variables[52] = xor_func(pow(variables[0], variables[1]), gt_func(variables[2], variables[3]))
    variables[53] = xor_func(pow(variables[0], 1.0/variables[1]), gt_func(variables[2], variables[3]))
    variables[54] = xor_func(lt_func(variables[0], variables[1]), variables[2]+variables[3])
    variables[55] = xor_func(lt_func(variables[0], variables[1]), variables[2])
    variables[56] = xor_func(lt_func(variables[0], variables[1]), variables[2]-variables[3])
    variables[57] = xor_func(lt_func(variables[0], variables[1]), -variables[2])
    variables[58] = xor_func(lt_func(variables[0], variables[1]), pow(variables[2], variables[3]))
    variables[59] = xor_func(lt_func(variables[0], variables[1]), pow(variables[2], 1.0/variables[3]))
    variables[60] = not_func(variables[0])
    variables[61] = variables[0]+variables[1]
    variables[62] = variables[0]+variables[1]+variables[2]
    variables[63] = lt_func(variables[0], variables[1])+gt_func(variables[2], variables[3])
    variables[64] = variables[0]
    variables[65] = variables[0]-variables[1]
    variables[66] = lt_func(variables[0], variables[1])-gt_func(variables[2], variables[3])
    variables[67] = lt_func(variables[0], variables[1])-(variables[2]+variables[3])
    variables[68] = lt_func(variables[0], variables[1])-variables[2]
    variables[69] = -variables[0]
    variables[70] = -lt_func(variables[0], variables[1])
    variables[71] = variables[0]*variables[1]
    variables[72] = variables[0]*variables[1]*variables[2]
    variables[73] = lt_func(variables[0], variables[1])*gt_func(variables[2], variables[3])
    variables[74] = (variables[0]+variables[1])*gt_func(variables[2], variables[3])
    variables[75] = variables[0]*gt_func(variables[1], variables[2])
    variables[76] = (variables[0]-variables[1])*gt_func(variables[2], variables[3])
    variables[77] = -variables[0]*gt_func(variables[1], variables[2])
    variables[78] = lt_func(variables[0], variables[1])*(variables[2]+variables[3])
    variables[79] = lt_func(variables[0], variables[1])*variables[2]
    variables[80] = lt_func(variables[0], variables[1])*(variables[2]-variables[3])
    variables[81] = lt_func(variables[0], variables[1])*-variables[2]
    variables[82] = variables[0]/variables[1]
    variables[83] = lt_func(variables[0], variables[1])/gt_func(variables[3], variables[2])
    variables[84] = (variables[0]+variables[1])/gt_func(variables[3], variables[2])
    variables[85] = variables[0]/gt_func(variables[2], variables[1])
    variables[86] = (variables[0]-variables[1])/gt_func(variables[3], variables[2])
    variables[87] = -variables[0]/gt_func(variables[2], variables[1])
    variables[88] = lt_func(variables[0], variables[1])/(variables[2]+variables[3])
    variables[89] = lt_func(variables[0], variables[1])/variables[2]
    variables[90] = lt_func(variables[0], variables[1])/(variables[2]-variables[3])
    variables[91] = lt_func(variables[0], variables[1])/-variables[2]
    variables[92] = lt_func(variables[0], variables[1])/(variables[2]*variables[3])
    variables[93] = lt_func(variables[0], variables[1])/(variables[2]/variables[3])
    variables[94] = sqrt(variables[0])
    variables[95] = pow(variables[0], 2.0)
    variables[96] = pow(variables[0], 3.0)
    variables[97] = pow(variables[0], variables[1])
    variables[98] = pow(lt_func(variables[0], variables[1]), gt_func(variables[2], variables[3]))
    variables[99] = pow(variables[0]+variables[1], gt_func(variables[2], variables[3]))
    variables[100] = pow(variables[0], gt_func(variables[1], variables[2]))
    variables[101] = pow(variables[0]-variables[1], gt_func(variables[2], variables[3]))
    variables[102] = pow(-variables[0], gt_func(variables[1], variables[2]))
    variables[103] = pow(variables[0]*variables[1], gt_func(variables[2], variables[3]))
    variables[104] = pow(variables[0]/variables[1], gt_func(variables[2], variables[3]))
    variables[105] = pow(lt_func(variables[0], variables[1]), variables[2]+variables[3])
    variables[106] = pow(lt_func(variables[0], variables[1]), variables[2])
    variables[107] = pow(lt_func(variables[0], variables[1]), variables[2]-variables[3])
    variables[108] = pow(lt_func(variables[0], variables[1]), -variables[2])
    variables[109] = pow(lt_func(variables[0], variables[1]), variables[2]*variables[3])
    variables[110] = pow(lt_func(variables[0], variables[1]), variables[2]/variables[3])
    variables[111] = pow(lt_func(variables[0], variables[1]), pow(variables[2], variables[3]))
    variables[112] = pow(lt_func(variables[0], variables[1]), pow(variables[2], 1.0/variables[3]))
    variables[113] = sqrt(variables[0])
    variables[114] = sqrt(variables[0])
    variables[115] = pow(variables[0], 1.0/3.0)
    variables[116] = pow(variables[0], 1.0/variables[1])
    variables[117] = pow(lt_func(variables[0], variables[1]), 1.0/gt_func(variables[3], variables[2]))
    variables[118] = pow(variables[0]+variables[1], 1.0/gt_func(variables[3], variables[2]))
    variables[119] = pow(variables[0], 1.0/gt_func(variables[2], variables[1]))
    variables[120] = pow(variables[0]-variables[1], 1.0/gt_func(variables[3], variables[2]))
    variables[121] = pow(-variables[0], 1.0/gt_func(variables[2], variables[1]))
    variables[122] = pow(variables[0]*variables[1], 1.0/gt_func(variables[3], variables[2]))
    variables[123] = pow(variables[0]/variables[1], 1.0/gt_func(variables[3], variables[2]))
    variables[124] = pow(lt_func(variables[0], variables[1]), 1.0/(variables[2]+variables[3]))
    variables[125] = pow(lt_func(variables[0], variables[1]), 1.0/variables[2])
    variables[126] = pow(lt_func(variables[0], variables[1]), 1.0/(variables[2]-variables[3]))
    variables[127] = pow(lt_func(variables[0], variables[1]), 1.0/-variables[2])
    variables[128] = pow(lt_func(variables[0], variables[1]), 1.0/(variables[2]*variables[3]))
    variables[129] = pow(lt_func(variables[0], variables[1]), 1.0/(variables[2]/variables[3]))
    variables[130] = pow(lt_func(variables[0], variables[1]), 1.0/pow(variables[2], variables[3]))
    variables[131] = pow(lt_func(variables[0], variables[1]), 1.0/pow(variables[2], 1.0/variables[3]))
    variables[132] = fabs(variables[0])
    variables[133] = exp(variables[0])
    variables[134] = log(variables[0])
    variables[135] = log10(variables[0])
    variables[136] = log(variables[0])/log(2.0)
    variables[137] = log10(variables[0])
    variables[138] = log(variables[0])/log(variables[1])
    variables[139] = ceil(variables[0])
    variables[140] = floor(variables[0])
    variables[141] = min(variables[0], variables[1])
    variables[142] = min(variables[0], min(variables[1], variables[2]))
    variables[143] = max(variables[0], variables[1])
    variables[144] = max(variables[0], max(variables[1], variables[2]))
    variables[145] = fmod(variables[0], variables[1])
    variables[146] = sin(variables[0])
    variables[147] = cos(variables[0])
    variables[148] = tan(variables[0])
    variables[149] = sec(variables[0])
    variables[150] = csc(variables[0])
    variables[151] = cot(variables[0])
    variables[152] = sinh(variables[0])
    variables[153] = cosh(variables[0])
    variables[154] = tanh(variables[0])
    variables[155] = sech(variables[0])
    variables[156] = csch(variables[0])
    variables[157] = coth(variables[0])
    variables[158] = asin(variables[0])
    variables[159] = acos(variables[0])
    variables[160] = atan(variables[0])
    variables[161] = asec(variables[0])
    variables[162] = acsc(variables[0])
    variables[163] = acot(variables[0])
    variables[164] = asinh(variables[0])
    variables[165] = acosh(variables[0])
    variables[166] = atanh(variables[0]/2.0)
    variables[167] = asech(variables[0])
    variables[168] = acsch(variables[0])
    variables[169] = acoth(2.0*variables[0])
    variables[170] = variables[0] if gt_func(variables[0], variables[1]) else nan
    variables[171] = variables[0] if gt_func(variables[0], variables[1]) else variables[2]
    variables[172] = variables[0] if gt_func(variables[0], variables[1]) else variables[2] if gt_func(variables[2], variables[3]) else variables[4] if gt_func(variables[4], variables[5]) else nan
    variables[173] = variables[0] if gt_func(variables[0], variables[1]) else variables[2] if gt_func(variables[2], variables[3]) else variables[4] if gt_func(variables[4], variables[5]) else variables[6]
    variables[178] = variables[0]


def compute_rates(voi, states, rates, variables):
    rates[0] = 1.0


def compute_variables(voi, states, rates, variables):
    pass

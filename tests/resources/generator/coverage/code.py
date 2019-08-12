from math import *


STATE_VECTOR_SIZE = 1
VARIABLE_VECTOR_SIZE = 185
VOI = {"name": "t", "units": "second"}

STATE_VECTOR_INFORMATION_ARRAY = [
    {"name": "x", "units": "dimensionless"},
]

VARIABLE_VECTOR_INFORMATION_ARRAY = [
    {"name": "m", "units": "dimensionless"},
    {"name": "n", "units": "dimensionless"},
    {"name": "o", "units": "dimensionless"},
    {"name": "p", "units": "dimensionless"},
    {"name": "q", "units": "dimensionless"},
    {"name": "r", "units": "dimensionless"},
    {"name": "s", "units": "dimensionless"},
    {"name": "eqnCnInteger", "units": "dimensionless"},
    {"name": "eqnCnDouble", "units": "dimensionless"},
    {"name": "eqnCnIntegerWithExponent", "units": "dimensionless"},
    {"name": "eqnCnDoubleWithExponent", "units": "dimensionless"},
    {"name": "eqnTrue", "units": "dimensionless"},
    {"name": "eqnFalse", "units": "dimensionless"},
    {"name": "eqnExponentiale", "units": "dimensionless"},
    {"name": "eqnPi", "units": "dimensionless"},
    {"name": "eqnInfinity", "units": "dimensionless"},
    {"name": "eqnNotanumber", "units": "dimensionless"},
    {"name": "eqnEqEq", "units": "dimensionless"},
    {"name": "eqnEqEqCoverageParentheses", "units": "dimensionless"},
    {"name": "eqnNeq", "units": "dimensionless"},
    {"name": "eqnNeqCoverageParentheses", "units": "dimensionless"},
    {"name": "eqnLt", "units": "dimensionless"},
    {"name": "eqnLeq", "units": "dimensionless"},
    {"name": "eqnGt", "units": "dimensionless"},
    {"name": "eqnGeq", "units": "dimensionless"},
    {"name": "eqnAnd", "units": "dimensionless"},
    {"name": "eqnAndMultiple", "units": "dimensionless"},
    {"name": "eqnAndParentheses", "units": "dimensionless"},
    {"name": "eqnAndParenthesesLeftPlusWith", "units": "dimensionless"},
    {"name": "eqnAndParenthesesLeftPlusWithout", "units": "dimensionless"},
    {"name": "eqnAndParenthesesLeftMinusWith", "units": "dimensionless"},
    {"name": "eqnAndParenthesesLeftMinusWithout", "units": "dimensionless"},
    {"name": "eqnAndParenthesesLeftPower", "units": "dimensionless"},
    {"name": "eqnAndParenthesesLeftRoot", "units": "dimensionless"},
    {"name": "eqnAndParenthesesRightPlusWith", "units": "dimensionless"},
    {"name": "eqnAndParenthesesRightPlusWithout", "units": "dimensionless"},
    {"name": "eqnAndParenthesesRightMinusWith", "units": "dimensionless"},
    {"name": "eqnAndParenthesesRightMinusWithout", "units": "dimensionless"},
    {"name": "eqnAndParenthesesRightPower", "units": "dimensionless"},
    {"name": "eqnAndParenthesesRightRoot", "units": "dimensionless"},
    {"name": "eqnOr", "units": "dimensionless"},
    {"name": "eqnOrMultiple", "units": "dimensionless"},
    {"name": "eqnOrParentheses", "units": "dimensionless"},
    {"name": "eqnOrParenthesesLeftPlusWith", "units": "dimensionless"},
    {"name": "eqnOrParenthesesLeftPlusWithout", "units": "dimensionless"},
    {"name": "eqnOrParenthesesLeftMinusWith", "units": "dimensionless"},
    {"name": "eqnOrParenthesesLeftMinusWithout", "units": "dimensionless"},
    {"name": "eqnOrParenthesesLeftPower", "units": "dimensionless"},
    {"name": "eqnOrParenthesesLeftRoot", "units": "dimensionless"},
    {"name": "eqnOrParenthesesRightPlusWith", "units": "dimensionless"},
    {"name": "eqnOrParenthesesRightPlusWithout", "units": "dimensionless"},
    {"name": "eqnOrParenthesesRightMinusWith", "units": "dimensionless"},
    {"name": "eqnOrParenthesesRightMinusWithout", "units": "dimensionless"},
    {"name": "eqnOrParenthesesRightPower", "units": "dimensionless"},
    {"name": "eqnOrParenthesesRightRoot", "units": "dimensionless"},
    {"name": "eqnXor", "units": "dimensionless"},
    {"name": "eqnXorMultiple", "units": "dimensionless"},
    {"name": "eqnXorParentheses", "units": "dimensionless"},
    {"name": "eqnXorParenthesesLeftPlusWith", "units": "dimensionless"},
    {"name": "eqnXorParenthesesLeftPlusWithout", "units": "dimensionless"},
    {"name": "eqnXorParenthesesLeftMinusWith", "units": "dimensionless"},
    {"name": "eqnXorParenthesesLeftMinusWithout", "units": "dimensionless"},
    {"name": "eqnXorParenthesesLeftPower", "units": "dimensionless"},
    {"name": "eqnXorParenthesesLeftRoot", "units": "dimensionless"},
    {"name": "eqnXorParenthesesRightPlusWith", "units": "dimensionless"},
    {"name": "eqnXorParenthesesRightPlusWithout", "units": "dimensionless"},
    {"name": "eqnXorParenthesesRightMinusWith", "units": "dimensionless"},
    {"name": "eqnXorParenthesesRightMinusWithout", "units": "dimensionless"},
    {"name": "eqnXorParenthesesRightPower", "units": "dimensionless"},
    {"name": "eqnXorParenthesesRightRoot", "units": "dimensionless"},
    {"name": "eqnNot", "units": "dimensionless"},
    {"name": "eqnPlus", "units": "dimensionless"},
    {"name": "eqnPlusMultiple", "units": "dimensionless"},
    {"name": "eqnPlusParentheses", "units": "dimensionless"},
    {"name": "eqnPlusUnary", "units": "dimensionless"},
    {"name": "eqnMinus", "units": "dimensionless"},
    {"name": "eqnMinusParentheses", "units": "dimensionless"},
    {"name": "eqnMinusParenthesesPlusWith", "units": "dimensionless"},
    {"name": "eqnMinusParenthesesPlusWithout", "units": "dimensionless"},
    {"name": "eqnMinusUnary", "units": "dimensionless"},
    {"name": "eqnMinusUnaryParentheses", "units": "dimensionless"},
    {"name": "eqnTimes", "units": "dimensionless"},
    {"name": "eqnTimesMultiple", "units": "dimensionless"},
    {"name": "eqnTimesParentheses", "units": "dimensionless"},
    {"name": "eqnTimesParenthesesLeftPlusWith", "units": "dimensionless"},
    {"name": "eqnTimesParenthesesLeftPlusWithout", "units": "dimensionless"},
    {"name": "eqnTimesParenthesesLeftMinusWith", "units": "dimensionless"},
    {"name": "eqnTimesParenthesesLeftMinusWithout", "units": "dimensionless"},
    {"name": "eqnTimesParenthesesRightPlusWith", "units": "dimensionless"},
    {"name": "eqnTimesParenthesesRightPlusWithout", "units": "dimensionless"},
    {"name": "eqnTimesParenthesesRightMinusWith", "units": "dimensionless"},
    {"name": "eqnTimesParenthesesRightMinusWithout", "units": "dimensionless"},
    {"name": "eqnDivide", "units": "dimensionless"},
    {"name": "eqnDivideParentheses", "units": "dimensionless"},
    {"name": "eqnDivideParenthesesLeftPlusWith", "units": "dimensionless"},
    {"name": "eqnDivideParenthesesLeftPlusWithout", "units": "dimensionless"},
    {"name": "eqnDivideParenthesesLeftMinusWith", "units": "dimensionless"},
    {"name": "eqnDivideParenthesesLeftMinusWithout", "units": "dimensionless"},
    {"name": "eqnDivideParenthesesRightPlusWith", "units": "dimensionless"},
    {"name": "eqnDivideParenthesesRightPlusWithout", "units": "dimensionless"},
    {"name": "eqnDivideParenthesesRightMinusWith", "units": "dimensionless"},
    {"name": "eqnDivideParenthesesRightMinusWithout", "units": "dimensionless"},
    {"name": "eqnDivideParenthesesRightTimes", "units": "dimensionless"},
    {"name": "eqnDivideParenthesesRightDivide", "units": "dimensionless"},
    {"name": "eqnPowerSqrt", "units": "dimensionless"},
    {"name": "eqnPowerSqr", "units": "dimensionless"},
    {"name": "eqnPowerCube", "units": "dimensionless"},
    {"name": "eqnPowerCi", "units": "dimensionless"},
    {"name": "eqnPowerParentheses", "units": "dimensionless"},
    {"name": "eqnPowerParenthesesLeftPlusWith", "units": "dimensionless"},
    {"name": "eqnPowerParenthesesLeftPlusWithout", "units": "dimensionless"},
    {"name": "eqnPowerParenthesesLeftMinusWith", "units": "dimensionless"},
    {"name": "eqnPowerParenthesesLeftMinusWithout", "units": "dimensionless"},
    {"name": "eqnPowerParenthesesLeftTimes", "units": "dimensionless"},
    {"name": "eqnPowerParenthesesLeftDivide", "units": "dimensionless"},
    {"name": "eqnPowerParenthesesRightPlusWith", "units": "dimensionless"},
    {"name": "eqnPowerParenthesesRightPlusWithout", "units": "dimensionless"},
    {"name": "eqnPowerParenthesesRightMinusWith", "units": "dimensionless"},
    {"name": "eqnPowerParenthesesRightMinusWithout", "units": "dimensionless"},
    {"name": "eqnPowerParenthesesRightTimes", "units": "dimensionless"},
    {"name": "eqnPowerParenthesesRightDivide", "units": "dimensionless"},
    {"name": "eqnPowerParenthesesRightPower", "units": "dimensionless"},
    {"name": "eqnPowerParenthesesRightRoot", "units": "dimensionless"},
    {"name": "eqnRootSqrt", "units": "dimensionless"},
    {"name": "eqnRootSqrtOther", "units": "dimensionless"},
    {"name": "eqnRootCube", "units": "dimensionless"},
    {"name": "eqnRootCi", "units": "dimensionless"},
    {"name": "eqnRootParentheses", "units": "dimensionless"},
    {"name": "eqnRootParenthesesLeftPlusWith", "units": "dimensionless"},
    {"name": "eqnRootParenthesesLeftPlusWithout", "units": "dimensionless"},
    {"name": "eqnRootParenthesesLeftMinusWith", "units": "dimensionless"},
    {"name": "eqnRootParenthesesLeftMinusWithout", "units": "dimensionless"},
    {"name": "eqnRootParenthesesLeftTimes", "units": "dimensionless"},
    {"name": "eqnRootParenthesesLeftDivide", "units": "dimensionless"},
    {"name": "eqnRootParenthesesRightPlusWith", "units": "dimensionless"},
    {"name": "eqnRootParenthesesRightPlusWithout", "units": "dimensionless"},
    {"name": "eqnRootParenthesesRightMinusWith", "units": "dimensionless"},
    {"name": "eqnRootParenthesesRightMinusWithout", "units": "dimensionless"},
    {"name": "eqnRootParenthesesRightTimes", "units": "dimensionless"},
    {"name": "eqnRootParenthesesRightDivide", "units": "dimensionless"},
    {"name": "eqnRootParenthesesRightPower", "units": "dimensionless"},
    {"name": "eqnRootParenthesesRightRoot", "units": "dimensionless"},
    {"name": "eqnAbs", "units": "dimensionless"},
    {"name": "eqnExp", "units": "dimensionless"},
    {"name": "eqnLn", "units": "dimensionless"},
    {"name": "eqnLog", "units": "dimensionless"},
    {"name": "eqnLog2", "units": "dimensionless"},
    {"name": "eqnLog10", "units": "dimensionless"},
    {"name": "eqnLogCi", "units": "dimensionless"},
    {"name": "eqnCeiling", "units": "dimensionless"},
    {"name": "eqnFloor", "units": "dimensionless"},
    {"name": "eqnMin", "units": "dimensionless"},
    {"name": "eqnMinMultiple", "units": "dimensionless"},
    {"name": "eqnMax", "units": "dimensionless"},
    {"name": "eqnMaxMultiple", "units": "dimensionless"},
    {"name": "eqnRem", "units": "dimensionless"},
    {"name": "eqnSin", "units": "dimensionless"},
    {"name": "eqnCos", "units": "dimensionless"},
    {"name": "eqnTan", "units": "dimensionless"},
    {"name": "eqnSec", "units": "dimensionless"},
    {"name": "eqnCsc", "units": "dimensionless"},
    {"name": "eqnCot", "units": "dimensionless"},
    {"name": "eqnSinh", "units": "dimensionless"},
    {"name": "eqnCosh", "units": "dimensionless"},
    {"name": "eqnTanh", "units": "dimensionless"},
    {"name": "eqnSech", "units": "dimensionless"},
    {"name": "eqnCsch", "units": "dimensionless"},
    {"name": "eqnCoth", "units": "dimensionless"},
    {"name": "eqnArcsin", "units": "dimensionless"},
    {"name": "eqnArccos", "units": "dimensionless"},
    {"name": "eqnArctan", "units": "dimensionless"},
    {"name": "eqnArcsec", "units": "dimensionless"},
    {"name": "eqnArccsc", "units": "dimensionless"},
    {"name": "eqnArccot", "units": "dimensionless"},
    {"name": "eqnArcsinh", "units": "dimensionless"},
    {"name": "eqnArccosh", "units": "dimensionless"},
    {"name": "eqnArctanh", "units": "dimensionless"},
    {"name": "eqnArcsech", "units": "dimensionless"},
    {"name": "eqnArccsch", "units": "dimensionless"},
    {"name": "eqnArccoth", "units": "dimensionless"},
    {"name": "eqnPiecewisePiece", "units": "dimensionless"},
    {"name": "eqnPiecewisePieceOtherwise", "units": "dimensionless"},
    {"name": "eqnPiecewisePiecePiecePiece", "units": "dimensionless"},
    {"name": "eqnPiecewisePiecePiecePieceOtherwise", "units": "dimensionless"},
    {"name": "eqnCi", "units": "dimensionless"},
]


def eq_eq_func(x, y):
    return 1.0 if (x == y) else 0.0


def neq_func(x, y):
    return 1.0 if (x != y) else 0.0


def lt_func(x, y):
    return 1.0 if (x < y) else 0.0


def leq_func(x, y):
    return 1.0 if (x <= y) else 0.0


def gt_func(x, y):
    return 1.0 if (x > y) else 0.0


def geq_func(x, y):
    return 1.0 if (x >= y) else 0.0


def and_func(x, y):
    return 1.0 if (bool(x) & bool(y)) else 0.0


def or_func(x, y):
    return 1.0 if (bool(x) | bool(y)) else 0.0


def xor_func(x, y):
    return 1.0 if (bool(x) ^ bool(y)) else 0.0


def not_func(x):
    return 1.0 if (not bool(x)) else 0.0


def min(x, y):
    return x if (x < y) else y


def max(x, y):
    return x if (x > y) else y


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

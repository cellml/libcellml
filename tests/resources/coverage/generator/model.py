# The content of this file was generated using the Python profile of libCellML 0.5.0.

from enum import Enum
from math import *


__version__ = "0.5.0"
LIBCELLML_VERSION = "0.5.0"

STATE_COUNT = 1
CONSTANT_COUNT = 0
COMPUTED_CONSTANT_COUNT = 0
ALGEBRAIC_COUNT = 209
EXTERNAL_COUNT = 0


class VariableType(Enum):
    VARIABLE_OF_INTEGRATION = 0
    STATE = 1
    CONSTANT = 2
    COMPUTED_CONSTANT = 3
    ALGEBRAIC = 4


VOI_INFO = {"name": "t", "units": "second", "component": "my_component", "type": VariableType.VARIABLE_OF_INTEGRATION}

STATE_INFO = [
    {"name": "x", "units": "dimensionless", "component": "my_component", "type": VariableType.STATE}
]

VARIABLE_INFO = [
    {"name": "eqnEq", "units": "dimensionless", "component": "my_component", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "m", "units": "dimensionless", "component": "my_component", "type": VariableType.CONSTANT},
    {"name": "n", "units": "dimensionless", "component": "my_component", "type": VariableType.CONSTANT},
    {"name": "eqnEqCoverageParentheses", "units": "dimensionless", "component": "my_component", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "eqnNeq", "units": "dimensionless", "component": "my_component", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "eqnNeqCoverageParentheses", "units": "dimensionless", "component": "my_component", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "o", "units": "dimensionless", "component": "my_component", "type": VariableType.CONSTANT},
    {"name": "eqnLt", "units": "dimensionless", "component": "my_component", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "eqnLtCoverageParentheses", "units": "dimensionless", "component": "my_component", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "eqnLeq", "units": "dimensionless", "component": "my_component", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "eqnLeqCoverageParentheses", "units": "dimensionless", "component": "my_component", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "eqnGt", "units": "dimensionless", "component": "my_component", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "eqnGtCoverageParentheses", "units": "dimensionless", "component": "my_component", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "eqnGeq", "units": "dimensionless", "component": "my_component", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "eqnGeqCoverageParentheses", "units": "dimensionless", "component": "my_component", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "eqnAnd", "units": "dimensionless", "component": "my_component", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "eqnAndMultiple", "units": "dimensionless", "component": "my_component", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "eqnAndParentheses", "units": "dimensionless", "component": "my_component", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "p", "units": "dimensionless", "component": "my_component", "type": VariableType.CONSTANT},
    {"name": "eqnAndParenthesesLeftPlusWith", "units": "dimensionless", "component": "my_component", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "eqnAndParenthesesLeftPlusWithout", "units": "dimensionless", "component": "my_component", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "eqnAndParenthesesLeftMinusWith", "units": "dimensionless", "component": "my_component", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "eqnAndParenthesesLeftMinusWithout", "units": "dimensionless", "component": "my_component", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "eqnAndParenthesesLeftPower", "units": "dimensionless", "component": "my_component", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "eqnAndParenthesesLeftRoot", "units": "dimensionless", "component": "my_component", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "eqnAndParenthesesRightPlusWith", "units": "dimensionless", "component": "my_component", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "eqnAndParenthesesRightPlusWithout", "units": "dimensionless", "component": "my_component", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "eqnAndParenthesesRightMinusWith", "units": "dimensionless", "component": "my_component", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "eqnAndParenthesesRightMinusWithout", "units": "dimensionless", "component": "my_component", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "eqnAndParenthesesRightPower", "units": "dimensionless", "component": "my_component", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "eqnAndParenthesesRightRoot", "units": "dimensionless", "component": "my_component", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "eqnAndCoverageParentheses", "units": "dimensionless", "component": "my_component", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "eqnOr", "units": "dimensionless", "component": "my_component", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "eqnOrMultiple", "units": "dimensionless", "component": "my_component", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "eqnOrParentheses", "units": "dimensionless", "component": "my_component", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "eqnOrParenthesesLeftPlusWith", "units": "dimensionless", "component": "my_component", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "eqnOrParenthesesLeftPlusWithout", "units": "dimensionless", "component": "my_component", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "eqnOrParenthesesLeftMinusWith", "units": "dimensionless", "component": "my_component", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "eqnOrParenthesesLeftMinusWithout", "units": "dimensionless", "component": "my_component", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "eqnOrParenthesesLeftPower", "units": "dimensionless", "component": "my_component", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "eqnOrParenthesesLeftRoot", "units": "dimensionless", "component": "my_component", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "eqnOrParenthesesRightPlusWith", "units": "dimensionless", "component": "my_component", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "eqnOrParenthesesRightPlusWithout", "units": "dimensionless", "component": "my_component", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "eqnOrParenthesesRightMinusWith", "units": "dimensionless", "component": "my_component", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "eqnOrParenthesesRightMinusWithout", "units": "dimensionless", "component": "my_component", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "eqnOrParenthesesRightPower", "units": "dimensionless", "component": "my_component", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "eqnOrParenthesesRightRoot", "units": "dimensionless", "component": "my_component", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "eqnOrCoverageParentheses", "units": "dimensionless", "component": "my_component", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "eqnXor", "units": "dimensionless", "component": "my_component", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "eqnXorMultiple", "units": "dimensionless", "component": "my_component", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "eqnXorParentheses", "units": "dimensionless", "component": "my_component", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "eqnXorParenthesesLeftPlusWith", "units": "dimensionless", "component": "my_component", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "eqnXorParenthesesLeftPlusWithout", "units": "dimensionless", "component": "my_component", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "eqnXorParenthesesLeftMinusWith", "units": "dimensionless", "component": "my_component", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "eqnXorParenthesesLeftMinusWithout", "units": "dimensionless", "component": "my_component", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "eqnXorParenthesesLeftPower", "units": "dimensionless", "component": "my_component", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "eqnXorParenthesesLeftRoot", "units": "dimensionless", "component": "my_component", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "eqnXorParenthesesRightPlusWith", "units": "dimensionless", "component": "my_component", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "eqnXorParenthesesRightPlusWithout", "units": "dimensionless", "component": "my_component", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "eqnXorParenthesesRightMinusWith", "units": "dimensionless", "component": "my_component", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "eqnXorParenthesesRightMinusWithout", "units": "dimensionless", "component": "my_component", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "eqnXorParenthesesRightPower", "units": "dimensionless", "component": "my_component", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "eqnXorParenthesesRightRoot", "units": "dimensionless", "component": "my_component", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "eqnXorCoverageParentheses", "units": "dimensionless", "component": "my_component", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "eqnNot", "units": "dimensionless", "component": "my_component", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "eqnPlus", "units": "dimensionless", "component": "my_component", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "eqnPlusMultiple", "units": "dimensionless", "component": "my_component", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "eqnPlusParentheses", "units": "dimensionless", "component": "my_component", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "eqnPlusUnary", "units": "dimensionless", "component": "my_component", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "eqnMinus", "units": "dimensionless", "component": "my_component", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "eqnMinusParentheses", "units": "dimensionless", "component": "my_component", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "eqnMinusParenthesesPlusWith", "units": "dimensionless", "component": "my_component", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "eqnMinusParenthesesPlusWithout", "units": "dimensionless", "component": "my_component", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "eqnMinusParenthesesDirectUnaryMinus", "units": "dimensionless", "component": "my_component", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "eqnMinusParenthesesIndirectUnaryMinus", "units": "dimensionless", "component": "my_component", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "eqnMinusUnary", "units": "dimensionless", "component": "my_component", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "eqnMinusUnaryParentheses", "units": "dimensionless", "component": "my_component", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "eqnTimes", "units": "dimensionless", "component": "my_component", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "eqnTimesMultiple", "units": "dimensionless", "component": "my_component", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "eqnTimesParentheses", "units": "dimensionless", "component": "my_component", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "eqnTimesParenthesesLeftPlusWith", "units": "dimensionless", "component": "my_component", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "eqnTimesParenthesesLeftPlusWithout", "units": "dimensionless", "component": "my_component", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "eqnTimesParenthesesLeftMinusWith", "units": "dimensionless", "component": "my_component", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "eqnTimesParenthesesLeftMinusWithout", "units": "dimensionless", "component": "my_component", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "eqnTimesParenthesesRightPlusWith", "units": "dimensionless", "component": "my_component", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "eqnTimesParenthesesRightPlusWithout", "units": "dimensionless", "component": "my_component", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "eqnTimesParenthesesRightMinusWith", "units": "dimensionless", "component": "my_component", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "eqnTimesParenthesesRightMinusWithout", "units": "dimensionless", "component": "my_component", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "eqnDivide", "units": "dimensionless", "component": "my_component", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "eqnDivideParentheses", "units": "dimensionless", "component": "my_component", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "eqnDivideParenthesesLeftPlusWith", "units": "dimensionless", "component": "my_component", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "eqnDivideParenthesesLeftPlusWithout", "units": "dimensionless", "component": "my_component", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "eqnDivideParenthesesLeftMinusWith", "units": "dimensionless", "component": "my_component", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "eqnDivideParenthesesLeftMinusWithout", "units": "dimensionless", "component": "my_component", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "eqnDivideParenthesesRightPlusWith", "units": "dimensionless", "component": "my_component", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "eqnDivideParenthesesRightPlusWithout", "units": "dimensionless", "component": "my_component", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "eqnDivideParenthesesRightMinusWith", "units": "dimensionless", "component": "my_component", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "eqnDivideParenthesesRightMinusWithout", "units": "dimensionless", "component": "my_component", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "eqnDivideParenthesesRightTimes", "units": "dimensionless", "component": "my_component", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "eqnDivideParenthesesRightDivide", "units": "dimensionless", "component": "my_component", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "eqnPowerSqrt", "units": "dimensionless", "component": "my_component", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "eqnPowerSqr", "units": "dimensionless", "component": "my_component", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "eqnPowerCube", "units": "dimensionless", "component": "my_component", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "eqnPowerCi", "units": "dimensionless", "component": "my_component", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "eqnPowerParentheses", "units": "dimensionless", "component": "my_component", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "eqnPowerParenthesesLeftPlusWith", "units": "dimensionless", "component": "my_component", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "eqnPowerParenthesesLeftPlusWithout", "units": "dimensionless", "component": "my_component", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "eqnPowerParenthesesLeftMinusWith", "units": "dimensionless", "component": "my_component", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "eqnPowerParenthesesLeftMinusWithout", "units": "dimensionless", "component": "my_component", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "eqnPowerParenthesesLeftTimes", "units": "dimensionless", "component": "my_component", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "eqnPowerParenthesesLeftDivide", "units": "dimensionless", "component": "my_component", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "eqnPowerParenthesesRightPlusWith", "units": "dimensionless", "component": "my_component", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "eqnPowerParenthesesRightPlusWithout", "units": "dimensionless", "component": "my_component", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "eqnPowerParenthesesRightMinusWith", "units": "dimensionless", "component": "my_component", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "eqnPowerParenthesesRightMinusWithout", "units": "dimensionless", "component": "my_component", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "eqnPowerParenthesesRightTimes", "units": "dimensionless", "component": "my_component", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "eqnPowerParenthesesRightDivide", "units": "dimensionless", "component": "my_component", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "eqnPowerParenthesesRightPower", "units": "dimensionless", "component": "my_component", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "eqnPowerParenthesesRightRoot", "units": "dimensionless", "component": "my_component", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "eqnRootSqrt", "units": "dimensionless", "component": "my_component", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "eqnRootSqrtOther", "units": "dimensionless", "component": "my_component", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "eqnRootCube", "units": "dimensionless", "component": "my_component", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "eqnRootCi", "units": "dimensionless", "component": "my_component", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "eqnRootParentheses", "units": "dimensionless", "component": "my_component", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "eqnRootParenthesesLeftPlusWith", "units": "dimensionless", "component": "my_component", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "eqnRootParenthesesLeftPlusWithout", "units": "dimensionless", "component": "my_component", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "eqnRootParenthesesLeftMinusWith", "units": "dimensionless", "component": "my_component", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "eqnRootParenthesesLeftMinusWithout", "units": "dimensionless", "component": "my_component", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "eqnRootParenthesesLeftTimes", "units": "dimensionless", "component": "my_component", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "eqnRootParenthesesLeftDivide", "units": "dimensionless", "component": "my_component", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "eqnRootParenthesesRightPlusWith", "units": "dimensionless", "component": "my_component", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "eqnRootParenthesesRightPlusWithout", "units": "dimensionless", "component": "my_component", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "eqnRootParenthesesRightMinusWith", "units": "dimensionless", "component": "my_component", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "eqnRootParenthesesRightMinusWithout", "units": "dimensionless", "component": "my_component", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "eqnRootParenthesesRightTimes", "units": "dimensionless", "component": "my_component", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "eqnRootParenthesesRightDivide", "units": "dimensionless", "component": "my_component", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "eqnRootParenthesesRightPower", "units": "dimensionless", "component": "my_component", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "eqnRootParenthesesRightRoot", "units": "dimensionless", "component": "my_component", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "eqnAbs", "units": "dimensionless", "component": "my_component", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "eqnExp", "units": "dimensionless", "component": "my_component", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "eqnLn", "units": "dimensionless", "component": "my_component", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "eqnLog", "units": "dimensionless", "component": "my_component", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "eqnLog2", "units": "dimensionless", "component": "my_component", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "eqnLog10", "units": "dimensionless", "component": "my_component", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "eqnLogCi", "units": "dimensionless", "component": "my_component", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "eqnCeiling", "units": "dimensionless", "component": "my_component", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "eqnFloor", "units": "dimensionless", "component": "my_component", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "eqnMin", "units": "dimensionless", "component": "my_component", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "eqnMinMultiple", "units": "dimensionless", "component": "my_component", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "eqnMax", "units": "dimensionless", "component": "my_component", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "eqnMaxMultiple", "units": "dimensionless", "component": "my_component", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "eqnRem", "units": "dimensionless", "component": "my_component", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "eqnSin", "units": "dimensionless", "component": "my_component", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "eqnCos", "units": "dimensionless", "component": "my_component", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "eqnTan", "units": "dimensionless", "component": "my_component", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "eqnSec", "units": "dimensionless", "component": "my_component", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "eqnCsc", "units": "dimensionless", "component": "my_component", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "eqnCot", "units": "dimensionless", "component": "my_component", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "eqnSinh", "units": "dimensionless", "component": "my_component", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "eqnCosh", "units": "dimensionless", "component": "my_component", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "eqnTanh", "units": "dimensionless", "component": "my_component", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "eqnSech", "units": "dimensionless", "component": "my_component", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "eqnCsch", "units": "dimensionless", "component": "my_component", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "eqnCoth", "units": "dimensionless", "component": "my_component", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "eqnArcsin", "units": "dimensionless", "component": "my_component", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "eqnArccos", "units": "dimensionless", "component": "my_component", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "eqnArctan", "units": "dimensionless", "component": "my_component", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "eqnArcsec", "units": "dimensionless", "component": "my_component", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "eqnArccsc", "units": "dimensionless", "component": "my_component", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "eqnArccot", "units": "dimensionless", "component": "my_component", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "eqnArcsinh", "units": "dimensionless", "component": "my_component", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "eqnArccosh", "units": "dimensionless", "component": "my_component", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "eqnArctanh", "units": "dimensionless", "component": "my_component", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "eqnArcsech", "units": "dimensionless", "component": "my_component", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "eqnArccsch", "units": "dimensionless", "component": "my_component", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "eqnArccoth", "units": "dimensionless", "component": "my_component", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "eqnPiecewisePiece", "units": "dimensionless", "component": "my_component", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "eqnPiecewisePieceOtherwise", "units": "dimensionless", "component": "my_component", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "eqnPiecewisePiecePiecePiece", "units": "dimensionless", "component": "my_component", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "q", "units": "dimensionless", "component": "my_component", "type": VariableType.CONSTANT},
    {"name": "r", "units": "dimensionless", "component": "my_component", "type": VariableType.CONSTANT},
    {"name": "eqnPiecewisePiecePiecePieceOtherwise", "units": "dimensionless", "component": "my_component", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "s", "units": "dimensionless", "component": "my_component", "type": VariableType.CONSTANT},
    {"name": "eqnWithPiecewise", "units": "dimensionless", "component": "my_component", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "eqnCnInteger", "units": "dimensionless", "component": "my_component", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "eqnCnDouble", "units": "dimensionless", "component": "my_component", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "eqnCnIntegerWithExponent", "units": "dimensionless", "component": "my_component", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "eqnCnDoubleWithExponent", "units": "dimensionless", "component": "my_component", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "eqnCi", "units": "dimensionless", "component": "my_component", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "eqnTrue", "units": "dimensionless", "component": "my_component", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "eqnFalse", "units": "dimensionless", "component": "my_component", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "eqnExponentiale", "units": "dimensionless", "component": "my_component", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "eqnPi", "units": "dimensionless", "component": "my_component", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "eqnInfinity", "units": "dimensionless", "component": "my_component", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "eqnNotanumber", "units": "dimensionless", "component": "my_component", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "eqnCoverageForPlusOperator", "units": "dimensionless", "component": "my_component", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "eqnCoverageForMinusOperator", "units": "dimensionless", "component": "my_component", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "eqnCoverageForTimesOperator", "units": "dimensionless", "component": "my_component", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "eqnCoverageForDivideOperator", "units": "dimensionless", "component": "my_component", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "eqnCoverageForAndOperator", "units": "dimensionless", "component": "my_component", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "eqnCoverageForOrOperator", "units": "dimensionless", "component": "my_component", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "eqnCoverageForXorOperator", "units": "dimensionless", "component": "my_component", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "eqnCoverageForPowerOperator", "units": "dimensionless", "component": "my_component", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "eqnCoverageForRootOperator", "units": "dimensionless", "component": "my_component", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "eqnCoverageForMinusUnary", "units": "dimensionless", "component": "my_component", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "eqnNlaVariable1", "units": "dimensionless", "component": "my_component", "type": VariableType.ALGEBRAIC},
    {"name": "eqnNlaVariable2", "units": "dimensionless", "component": "my_component", "type": VariableType.ALGEBRAIC},
    {"name": "eqnComputedConstant1", "units": "dimensionless", "component": "my_component", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "eqnComputedConstant2", "units": "dimensionless", "component": "my_component", "type": VariableType.COMPUTED_CONSTANT}
]


def eq_func(x, y):
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


def create_states_array():
    return [nan]*STATE_COUNT


def create_variables_array():
    return [nan]*VARIABLE_COUNT


from nlasolver import nla_solve


def objective_function_0(u, f, data):
    voi = data[0]
    states = data[1]
    rates = data[2]
    variables = data[3]

    algebraic[0] = u[0]
    algebraic[1] = u[1]

    f[0] = algebraic[0]+algebraic[1]+states[0]-0.0
    f[1] = algebraic[0]-algebraic[1]-(computed_constants[198]+computed_constants[199])


def find_root_0(voi, states, rates, variables):
    u = [nan]*2

    u[0] = algebraic[0]
    u[1] = algebraic[1]

    u = nla_solve(objective_function_0, u, 2, [voi, states, rates, variables])

    algebraic[0] = u[0]
    algebraic[1] = u[1]


def initialise_variables(states, rates, constants):
    constants[0] = 1.0
    constants[1] = 2.0
    constants[2] = 3.0
    constants[3] = 4.0
    constants[4] = 5.0
    constants[5] = 6.0
    constants[6] = 7.0
    algebraic[0] = 1.0
    algebraic[1] = 2.0
    computed_constants[177] = 123.0
    computed_constants[178] = 123.456789
    computed_constants[179] = 123.0e99
    computed_constants[180] = 123.456789e99
    computed_constants[182] = 1.0
    computed_constants[183] = 0.0
    computed_constants[184] = 2.71828182845905
    computed_constants[185] = 3.14159265358979
    computed_constants[186] = inf
    computed_constants[187] = nan
    computed_constants[198] = 1.0
    computed_constants[199] = 3.0
    states[0] = 0.0


def compute_computed_constants(constants, computed_constants):
    computed_constants[0] = eq_func(constants[0], constants[1])
    computed_constants[1] = constants[0]/eq_func(constants[1], constants[1])
    computed_constants[2] = neq_func(constants[0], constants[1])
    computed_constants[3] = constants[0]/neq_func(constants[1], constants[2])
    computed_constants[4] = lt_func(constants[0], constants[1])
    computed_constants[5] = constants[0]/lt_func(constants[1], constants[2])
    computed_constants[6] = leq_func(constants[0], constants[1])
    computed_constants[7] = constants[0]/leq_func(constants[1], constants[2])
    computed_constants[8] = gt_func(constants[0], constants[1])
    computed_constants[9] = constants[0]/gt_func(constants[1], constants[2])
    computed_constants[10] = geq_func(constants[0], constants[1])
    computed_constants[11] = constants[0]/geq_func(constants[1], constants[2])
    computed_constants[12] = and_func(constants[0], constants[1])
    computed_constants[13] = and_func(constants[0], and_func(constants[1], constants[2]))
    computed_constants[14] = and_func(lt_func(constants[0], constants[1]), gt_func(constants[2], constants[3]))
    computed_constants[15] = and_func(constants[0]+constants[1], gt_func(constants[2], constants[3]))
    computed_constants[16] = and_func(constants[0], gt_func(constants[1], constants[2]))
    computed_constants[17] = and_func(constants[0]-constants[1], gt_func(constants[2], constants[3]))
    computed_constants[18] = and_func(-constants[0], gt_func(constants[1], constants[2]))
    computed_constants[19] = and_func(pow(constants[0], constants[1]), gt_func(constants[2], constants[3]))
    computed_constants[20] = and_func(pow(constants[0], 1.0/constants[1]), gt_func(constants[2], constants[3]))
    computed_constants[21] = and_func(lt_func(constants[0], constants[1]), constants[2]+constants[3])
    computed_constants[22] = and_func(lt_func(constants[0], constants[1]), constants[2])
    computed_constants[23] = and_func(lt_func(constants[0], constants[1]), constants[2]-constants[3])
    computed_constants[24] = and_func(lt_func(constants[0], constants[1]), -constants[2])
    computed_constants[25] = and_func(lt_func(constants[0], constants[1]), pow(constants[2], constants[3]))
    computed_constants[26] = and_func(lt_func(constants[0], constants[1]), pow(constants[2], 1.0/constants[3]))
    computed_constants[27] = constants[0]/and_func(constants[1], constants[2])
    computed_constants[28] = or_func(constants[0], constants[1])
    computed_constants[29] = or_func(constants[0], or_func(constants[1], constants[2]))
    computed_constants[30] = or_func(lt_func(constants[0], constants[1]), gt_func(constants[2], constants[3]))
    computed_constants[31] = or_func(constants[0]+constants[1], gt_func(constants[2], constants[3]))
    computed_constants[32] = or_func(constants[0], gt_func(constants[1], constants[2]))
    computed_constants[33] = or_func(constants[0]-constants[1], gt_func(constants[2], constants[3]))
    computed_constants[34] = or_func(-constants[0], gt_func(constants[1], constants[2]))
    computed_constants[35] = or_func(pow(constants[0], constants[1]), gt_func(constants[2], constants[3]))
    computed_constants[36] = or_func(pow(constants[0], 1.0/constants[1]), gt_func(constants[2], constants[3]))
    computed_constants[37] = or_func(lt_func(constants[0], constants[1]), constants[2]+constants[3])
    computed_constants[38] = or_func(lt_func(constants[0], constants[1]), constants[2])
    computed_constants[39] = or_func(lt_func(constants[0], constants[1]), constants[2]-constants[3])
    computed_constants[40] = or_func(lt_func(constants[0], constants[1]), -constants[2])
    computed_constants[41] = or_func(lt_func(constants[0], constants[1]), pow(constants[2], constants[3]))
    computed_constants[42] = or_func(lt_func(constants[0], constants[1]), pow(constants[2], 1.0/constants[3]))
    computed_constants[43] = constants[0]/or_func(constants[1], constants[2])
    computed_constants[44] = xor_func(constants[0], constants[1])
    computed_constants[45] = xor_func(constants[0], xor_func(constants[1], constants[2]))
    computed_constants[46] = xor_func(lt_func(constants[0], constants[1]), gt_func(constants[2], constants[3]))
    computed_constants[47] = xor_func(constants[0]+constants[1], gt_func(constants[2], constants[3]))
    computed_constants[48] = xor_func(constants[0], gt_func(constants[1], constants[2]))
    computed_constants[49] = xor_func(constants[0]-constants[1], gt_func(constants[2], constants[3]))
    computed_constants[50] = xor_func(-constants[0], gt_func(constants[1], constants[2]))
    computed_constants[51] = xor_func(pow(constants[0], constants[1]), gt_func(constants[2], constants[3]))
    computed_constants[52] = xor_func(pow(constants[0], 1.0/constants[1]), gt_func(constants[2], constants[3]))
    computed_constants[53] = xor_func(lt_func(constants[0], constants[1]), constants[2]+constants[3])
    computed_constants[54] = xor_func(lt_func(constants[0], constants[1]), constants[2])
    computed_constants[55] = xor_func(lt_func(constants[0], constants[1]), constants[2]-constants[3])
    computed_constants[56] = xor_func(lt_func(constants[0], constants[1]), -constants[2])
    computed_constants[57] = xor_func(lt_func(constants[0], constants[1]), pow(constants[2], constants[3]))
    computed_constants[58] = xor_func(lt_func(constants[0], constants[1]), pow(constants[2], 1.0/constants[3]))
    computed_constants[59] = constants[0]/xor_func(constants[1], constants[2])
    computed_constants[60] = not_func(constants[0])
    computed_constants[61] = constants[0]+constants[1]
    computed_constants[62] = constants[0]+constants[1]+constants[2]
    computed_constants[63] = lt_func(constants[0], constants[1])+gt_func(constants[2], constants[3])
    computed_constants[64] = constants[0]
    computed_constants[65] = constants[0]-constants[1]
    computed_constants[66] = lt_func(constants[0], constants[1])-gt_func(constants[2], constants[3])
    computed_constants[67] = lt_func(constants[0], constants[1])-(constants[2]+constants[3])
    computed_constants[68] = lt_func(constants[0], constants[1])-constants[2]
    computed_constants[69] = constants[0]-(-constants[1])
    computed_constants[70] = constants[0]-(-constants[1]*constants[2])
    computed_constants[71] = -constants[0]
    computed_constants[72] = -lt_func(constants[0], constants[1])
    computed_constants[73] = constants[0]*constants[1]
    computed_constants[74] = constants[0]*constants[1]*constants[2]
    computed_constants[75] = lt_func(constants[0], constants[1])*gt_func(constants[2], constants[3])
    computed_constants[76] = (constants[0]+constants[1])*gt_func(constants[2], constants[3])
    computed_constants[77] = constants[0]*gt_func(constants[1], constants[2])
    computed_constants[78] = (constants[0]-constants[1])*gt_func(constants[2], constants[3])
    computed_constants[79] = -constants[0]*gt_func(constants[1], constants[2])
    computed_constants[80] = lt_func(constants[0], constants[1])*(constants[2]+constants[3])
    computed_constants[81] = lt_func(constants[0], constants[1])*constants[2]
    computed_constants[82] = lt_func(constants[0], constants[1])*(constants[2]-constants[3])
    computed_constants[83] = lt_func(constants[0], constants[1])*-constants[2]
    computed_constants[84] = constants[0]/constants[1]
    computed_constants[85] = lt_func(constants[0], constants[1])/gt_func(constants[3], constants[2])
    computed_constants[86] = (constants[0]+constants[1])/gt_func(constants[3], constants[2])
    computed_constants[87] = constants[0]/gt_func(constants[2], constants[1])
    computed_constants[88] = (constants[0]-constants[1])/gt_func(constants[3], constants[2])
    computed_constants[89] = -constants[0]/gt_func(constants[2], constants[1])
    computed_constants[90] = lt_func(constants[0], constants[1])/(constants[2]+constants[3])
    computed_constants[91] = lt_func(constants[0], constants[1])/constants[2]
    computed_constants[92] = lt_func(constants[0], constants[1])/(constants[2]-constants[3])
    computed_constants[93] = lt_func(constants[0], constants[1])/-constants[2]
    computed_constants[94] = lt_func(constants[0], constants[1])/(constants[2]*constants[3])
    computed_constants[95] = lt_func(constants[0], constants[1])/(constants[2]/constants[3])
    computed_constants[96] = sqrt(constants[0])
    computed_constants[97] = pow(constants[0], 2.0)
    computed_constants[98] = pow(constants[0], 3.0)
    computed_constants[99] = pow(constants[0], constants[1])
    computed_constants[100] = pow(leq_func(constants[0], constants[1]), geq_func(constants[2], constants[3]))
    computed_constants[101] = pow(constants[0]+constants[1], geq_func(constants[2], constants[3]))
    computed_constants[102] = pow(constants[0], geq_func(constants[1], constants[2]))
    computed_constants[103] = pow(constants[0]-constants[1], geq_func(constants[2], constants[3]))
    computed_constants[104] = pow(-constants[0], geq_func(constants[1], constants[2]))
    computed_constants[105] = pow(constants[0]*constants[1], geq_func(constants[2], constants[3]))
    computed_constants[106] = pow(constants[0]/constants[1], geq_func(constants[2], constants[3]))
    computed_constants[107] = pow(leq_func(constants[0], constants[1]), constants[2]+constants[3])
    computed_constants[108] = pow(leq_func(constants[0], constants[1]), constants[2])
    computed_constants[109] = pow(leq_func(constants[0], constants[1]), constants[2]-constants[3])
    computed_constants[110] = pow(leq_func(constants[0], constants[1]), -constants[2])
    computed_constants[111] = pow(leq_func(constants[0], constants[1]), constants[2]*constants[3])
    computed_constants[112] = pow(leq_func(constants[0], constants[1]), constants[2]/constants[3])
    computed_constants[113] = pow(leq_func(constants[0], constants[1]), pow(constants[2], constants[3]))
    computed_constants[114] = pow(leq_func(constants[0], constants[1]), pow(constants[2], 1.0/constants[3]))
    computed_constants[115] = sqrt(constants[0])
    computed_constants[116] = sqrt(constants[0])
    computed_constants[117] = pow(constants[0], 1.0/3.0)
    computed_constants[118] = pow(constants[0], 1.0/constants[1])
    computed_constants[119] = pow(lt_func(constants[0], constants[1]), 1.0/gt_func(constants[3], constants[2]))
    computed_constants[120] = pow(constants[0]+constants[1], 1.0/gt_func(constants[3], constants[2]))
    computed_constants[121] = pow(constants[0], 1.0/gt_func(constants[2], constants[1]))
    computed_constants[122] = pow(constants[0]-constants[1], 1.0/gt_func(constants[3], constants[2]))
    computed_constants[123] = pow(-constants[0], 1.0/gt_func(constants[2], constants[1]))
    computed_constants[124] = pow(constants[0]*constants[1], 1.0/gt_func(constants[3], constants[2]))
    computed_constants[125] = pow(constants[0]/constants[1], 1.0/gt_func(constants[3], constants[2]))
    computed_constants[126] = pow(lt_func(constants[0], constants[1]), 1.0/(constants[2]+constants[3]))
    computed_constants[127] = pow(lt_func(constants[0], constants[1]), 1.0/constants[2])
    computed_constants[128] = pow(lt_func(constants[0], constants[1]), 1.0/(constants[2]-constants[3]))
    computed_constants[129] = pow(lt_func(constants[0], constants[1]), 1.0/-constants[2])
    computed_constants[130] = pow(lt_func(constants[0], constants[1]), 1.0/(constants[2]*constants[3]))
    computed_constants[131] = pow(lt_func(constants[0], constants[1]), 1.0/(constants[2]/constants[3]))
    computed_constants[132] = pow(lt_func(constants[0], constants[1]), 1.0/pow(constants[2], constants[3]))
    computed_constants[133] = pow(lt_func(constants[0], constants[1]), 1.0/pow(constants[2], 1.0/constants[3]))
    computed_constants[134] = fabs(constants[0])
    computed_constants[135] = exp(constants[0])
    computed_constants[136] = log(constants[0])
    computed_constants[137] = log10(constants[0])
    computed_constants[138] = log(constants[0])/log(2.0)
    computed_constants[139] = log10(constants[0])
    computed_constants[140] = log(constants[0])/log(constants[1])
    computed_constants[141] = ceil(constants[0])
    computed_constants[142] = floor(constants[0])
    computed_constants[143] = min(constants[0], constants[1])
    computed_constants[144] = min(constants[0], min(constants[1], constants[2]))
    computed_constants[145] = max(constants[0], constants[1])
    computed_constants[146] = max(constants[0], max(constants[1], constants[2]))
    computed_constants[147] = fmod(constants[0], constants[1])
    computed_constants[148] = sin(constants[0])
    computed_constants[149] = cos(constants[0])
    computed_constants[150] = tan(constants[0])
    computed_constants[151] = sec(constants[0])
    computed_constants[152] = csc(constants[0])
    computed_constants[153] = cot(constants[0])
    computed_constants[154] = sinh(constants[0])
    computed_constants[155] = cosh(constants[0])
    computed_constants[156] = tanh(constants[0])
    computed_constants[157] = sech(constants[0])
    computed_constants[158] = csch(constants[0])
    computed_constants[159] = coth(constants[0])
    computed_constants[160] = asin(constants[0])
    computed_constants[161] = acos(constants[0])
    computed_constants[162] = atan(constants[0])
    computed_constants[163] = asec(constants[0])
    computed_constants[164] = acsc(constants[0])
    computed_constants[165] = acot(constants[0])
    computed_constants[166] = asinh(constants[0])
    computed_constants[167] = acosh(constants[0])
    computed_constants[168] = atanh(constants[0]/2.0)
    computed_constants[169] = asech(constants[0])
    computed_constants[170] = acsch(constants[0])
    computed_constants[171] = acoth(2.0*constants[0])
    computed_constants[172] = constants[0] if gt_func(constants[0], constants[1]) else nan
    computed_constants[173] = constants[0] if gt_func(constants[0], constants[1]) else constants[2]
    computed_constants[174] = constants[0] if gt_func(constants[0], constants[1]) else constants[2] if gt_func(constants[2], constants[3]) else constants[4] if gt_func(constants[4], constants[5]) else nan
    computed_constants[175] = constants[0] if gt_func(constants[0], constants[1]) else constants[2] if gt_func(constants[2], constants[3]) else constants[4] if gt_func(constants[4], constants[5]) else constants[6]
    computed_constants[176] = 123.0+(constants[0] if gt_func(constants[0], constants[1]) else nan)
    computed_constants[181] = constants[0]
    computed_constants[188] = and_func(constants[0], constants[1])+(constants[1] if gt_func(constants[2], constants[3]) else nan)+constants[4]+and_func(constants[5], constants[6])
    computed_constants[189] = and_func(constants[0], constants[1])-((constants[1] if gt_func(constants[2], constants[3]) else nan)-(constants[4]-(constants[1] if gt_func(constants[2], constants[3]) else nan)))-and_func(constants[5], constants[6])
    computed_constants[190] = and_func(constants[0], constants[1])*(constants[1] if gt_func(constants[2], constants[3]) else nan)*constants[4]*(constants[1] if gt_func(constants[2], constants[3]) else nan)*and_func(constants[5], constants[6])
    computed_constants[191] = and_func(constants[0], constants[1])/((constants[1] if gt_func(constants[2], constants[3]) else nan)/(constants[4]/(constants[1] if gt_func(constants[2], constants[3]) else nan)))
    computed_constants[192] = and_func(or_func(constants[0], constants[1]), and_func(xor_func(constants[0], constants[1]), and_func(constants[1] if gt_func(constants[2], constants[3]) else nan, and_func(and_func(and_func(constants[4], constants[1] if gt_func(constants[2], constants[3]) else nan), xor_func(constants[0], constants[1])), or_func(constants[0], constants[1])))))
    computed_constants[193] = or_func(and_func(constants[0], constants[1]), or_func(xor_func(constants[0], constants[1]), or_func(constants[1] if gt_func(constants[2], constants[3]) else nan, or_func(or_func(or_func(constants[4], constants[1] if gt_func(constants[2], constants[3]) else nan), xor_func(constants[0], constants[1])), and_func(constants[0], constants[1])))))
    computed_constants[194] = xor_func(and_func(constants[0], constants[1]), xor_func(or_func(constants[0], constants[1]), xor_func(constants[1] if gt_func(constants[2], constants[3]) else nan, xor_func(xor_func(xor_func(constants[4], constants[1] if gt_func(constants[2], constants[3]) else nan), or_func(constants[0], constants[1])), and_func(constants[0], constants[1])))))
    computed_constants[195] = pow(and_func(constants[0], constants[1]), pow(constants[1] if gt_func(constants[2], constants[3]) else nan, pow(pow(constants[4], constants[1] if gt_func(constants[2], constants[3]) else nan), and_func(constants[0], constants[1]))))
    computed_constants[196] = pow(pow(pow(and_func(constants[0], constants[1]), 1.0/pow(constants[1] if gt_func(constants[2], constants[3]) else nan, 1.0/constants[4])), 1.0/(constants[1] if gt_func(constants[2], constants[3]) else nan)), 1.0/and_func(constants[0], constants[1]))
    computed_constants[197] = -and_func(constants[0], constants[1])+-(constants[1] if gt_func(constants[2], constants[3]) else nan)


def compute_rates(voi, states, rates, constants, computed_constants, algebraic):
    rates[0] = 1.0


def compute_variables(voi, states, rates, constants, computed_constants, algebraic):
    find_root_0(voi, states, rates, variables)

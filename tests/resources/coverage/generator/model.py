# The content of this file was generated using the Python profile of libCellML 0.4.0.

from enum import Enum
from math import *


__version__ = "0.3.2"
LIBCELLML_VERSION = "0.4.0"

STATE_COUNT = 1
VARIABLE_COUNT = 203


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
    {"name": "m", "units": "dimensionless", "component": "my_component", "type": VariableType.CONSTANT},
    {"name": "n", "units": "dimensionless", "component": "my_component", "type": VariableType.CONSTANT},
    {"name": "o", "units": "dimensionless", "component": "my_component", "type": VariableType.CONSTANT},
    {"name": "p", "units": "dimensionless", "component": "my_component", "type": VariableType.CONSTANT},
    {"name": "q", "units": "dimensionless", "component": "my_component", "type": VariableType.CONSTANT},
    {"name": "r", "units": "dimensionless", "component": "my_component", "type": VariableType.CONSTANT},
    {"name": "s", "units": "dimensionless", "component": "my_component", "type": VariableType.CONSTANT}
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


def initialise_variables(states, variables):
    variables[1] = 1.0
    variables[2] = 2.0
    variables[6] = 3.0
    variables[18] = 4.0
    variables[177] = 5.0
    variables[178] = 6.0
    variables[180] = 7.0
    variables[182] = 123.0
    variables[183] = 123.456789
    variables[184] = 123.0e99
    variables[185] = 123.456789e99
    variables[187] = 1.0
    variables[188] = 0.0
    variables[189] = 2.71828182845905
    variables[190] = 3.14159265358979
    variables[191] = inf
    variables[192] = nan
    states[0] = 0.0


def compute_computed_constants(variables):
    variables[0] = eq_func(variables[1], variables[2])
    variables[3] = variables[1]/eq_func(variables[2], variables[2])
    variables[4] = neq_func(variables[1], variables[2])
    variables[5] = variables[1]/neq_func(variables[2], variables[6])
    variables[7] = lt_func(variables[1], variables[2])
    variables[8] = variables[1]/lt_func(variables[2], variables[6])
    variables[9] = leq_func(variables[1], variables[2])
    variables[10] = variables[1]/leq_func(variables[2], variables[6])
    variables[11] = gt_func(variables[1], variables[2])
    variables[12] = variables[1]/gt_func(variables[2], variables[6])
    variables[13] = geq_func(variables[1], variables[2])
    variables[14] = variables[1]/geq_func(variables[2], variables[6])
    variables[15] = and_func(variables[1], variables[2])
    variables[16] = and_func(variables[1], and_func(variables[2], variables[6]))
    variables[17] = and_func(lt_func(variables[1], variables[2]), gt_func(variables[6], variables[18]))
    variables[19] = and_func(variables[1]+variables[2], gt_func(variables[6], variables[18]))
    variables[20] = and_func(variables[1], gt_func(variables[2], variables[6]))
    variables[21] = and_func(variables[1]-variables[2], gt_func(variables[6], variables[18]))
    variables[22] = and_func(-variables[1], gt_func(variables[2], variables[6]))
    variables[23] = and_func(pow(variables[1], variables[2]), gt_func(variables[6], variables[18]))
    variables[24] = and_func(pow(variables[1], 1.0/variables[2]), gt_func(variables[6], variables[18]))
    variables[25] = and_func(lt_func(variables[1], variables[2]), variables[6]+variables[18])
    variables[26] = and_func(lt_func(variables[1], variables[2]), variables[6])
    variables[27] = and_func(lt_func(variables[1], variables[2]), variables[6]-variables[18])
    variables[28] = and_func(lt_func(variables[1], variables[2]), -variables[6])
    variables[29] = and_func(lt_func(variables[1], variables[2]), pow(variables[6], variables[18]))
    variables[30] = and_func(lt_func(variables[1], variables[2]), pow(variables[6], 1.0/variables[18]))
    variables[31] = variables[1]/and_func(variables[2], variables[6])
    variables[32] = or_func(variables[1], variables[2])
    variables[33] = or_func(variables[1], or_func(variables[2], variables[6]))
    variables[34] = or_func(lt_func(variables[1], variables[2]), gt_func(variables[6], variables[18]))
    variables[35] = or_func(variables[1]+variables[2], gt_func(variables[6], variables[18]))
    variables[36] = or_func(variables[1], gt_func(variables[2], variables[6]))
    variables[37] = or_func(variables[1]-variables[2], gt_func(variables[6], variables[18]))
    variables[38] = or_func(-variables[1], gt_func(variables[2], variables[6]))
    variables[39] = or_func(pow(variables[1], variables[2]), gt_func(variables[6], variables[18]))
    variables[40] = or_func(pow(variables[1], 1.0/variables[2]), gt_func(variables[6], variables[18]))
    variables[41] = or_func(lt_func(variables[1], variables[2]), variables[6]+variables[18])
    variables[42] = or_func(lt_func(variables[1], variables[2]), variables[6])
    variables[43] = or_func(lt_func(variables[1], variables[2]), variables[6]-variables[18])
    variables[44] = or_func(lt_func(variables[1], variables[2]), -variables[6])
    variables[45] = or_func(lt_func(variables[1], variables[2]), pow(variables[6], variables[18]))
    variables[46] = or_func(lt_func(variables[1], variables[2]), pow(variables[6], 1.0/variables[18]))
    variables[47] = variables[1]/or_func(variables[2], variables[6])
    variables[48] = xor_func(variables[1], variables[2])
    variables[49] = xor_func(variables[1], xor_func(variables[2], variables[6]))
    variables[50] = xor_func(lt_func(variables[1], variables[2]), gt_func(variables[6], variables[18]))
    variables[51] = xor_func(variables[1]+variables[2], gt_func(variables[6], variables[18]))
    variables[52] = xor_func(variables[1], gt_func(variables[2], variables[6]))
    variables[53] = xor_func(variables[1]-variables[2], gt_func(variables[6], variables[18]))
    variables[54] = xor_func(-variables[1], gt_func(variables[2], variables[6]))
    variables[55] = xor_func(pow(variables[1], variables[2]), gt_func(variables[6], variables[18]))
    variables[56] = xor_func(pow(variables[1], 1.0/variables[2]), gt_func(variables[6], variables[18]))
    variables[57] = xor_func(lt_func(variables[1], variables[2]), variables[6]+variables[18])
    variables[58] = xor_func(lt_func(variables[1], variables[2]), variables[6])
    variables[59] = xor_func(lt_func(variables[1], variables[2]), variables[6]-variables[18])
    variables[60] = xor_func(lt_func(variables[1], variables[2]), -variables[6])
    variables[61] = xor_func(lt_func(variables[1], variables[2]), pow(variables[6], variables[18]))
    variables[62] = xor_func(lt_func(variables[1], variables[2]), pow(variables[6], 1.0/variables[18]))
    variables[63] = variables[1]/xor_func(variables[2], variables[6])
    variables[64] = not_func(variables[1])
    variables[65] = variables[1]+variables[2]
    variables[66] = variables[1]+variables[2]+variables[6]
    variables[67] = lt_func(variables[1], variables[2])+gt_func(variables[6], variables[18])
    variables[68] = variables[1]
    variables[69] = variables[1]-variables[2]
    variables[70] = lt_func(variables[1], variables[2])-gt_func(variables[6], variables[18])
    variables[71] = lt_func(variables[1], variables[2])-(variables[6]+variables[18])
    variables[72] = lt_func(variables[1], variables[2])-variables[6]
    variables[73] = -variables[1]
    variables[74] = -lt_func(variables[1], variables[2])
    variables[75] = variables[1]*variables[2]
    variables[76] = variables[1]*variables[2]*variables[6]
    variables[77] = lt_func(variables[1], variables[2])*gt_func(variables[6], variables[18])
    variables[78] = (variables[1]+variables[2])*gt_func(variables[6], variables[18])
    variables[79] = variables[1]*gt_func(variables[2], variables[6])
    variables[80] = (variables[1]-variables[2])*gt_func(variables[6], variables[18])
    variables[81] = -variables[1]*gt_func(variables[2], variables[6])
    variables[82] = lt_func(variables[1], variables[2])*(variables[6]+variables[18])
    variables[83] = lt_func(variables[1], variables[2])*variables[6]
    variables[84] = lt_func(variables[1], variables[2])*(variables[6]-variables[18])
    variables[85] = lt_func(variables[1], variables[2])*-variables[6]
    variables[86] = variables[1]/variables[2]
    variables[87] = lt_func(variables[1], variables[2])/gt_func(variables[18], variables[6])
    variables[88] = (variables[1]+variables[2])/gt_func(variables[18], variables[6])
    variables[89] = variables[1]/gt_func(variables[6], variables[2])
    variables[90] = (variables[1]-variables[2])/gt_func(variables[18], variables[6])
    variables[91] = -variables[1]/gt_func(variables[6], variables[2])
    variables[92] = lt_func(variables[1], variables[2])/(variables[6]+variables[18])
    variables[93] = lt_func(variables[1], variables[2])/variables[6]
    variables[94] = lt_func(variables[1], variables[2])/(variables[6]-variables[18])
    variables[95] = lt_func(variables[1], variables[2])/-variables[6]
    variables[96] = lt_func(variables[1], variables[2])/(variables[6]*variables[18])
    variables[97] = lt_func(variables[1], variables[2])/(variables[6]/variables[18])
    variables[98] = sqrt(variables[1])
    variables[99] = pow(variables[1], 2.0)
    variables[100] = pow(variables[1], 3.0)
    variables[101] = pow(variables[1], variables[2])
    variables[102] = pow(leq_func(variables[1], variables[2]), geq_func(variables[6], variables[18]))
    variables[103] = pow(variables[1]+variables[2], geq_func(variables[6], variables[18]))
    variables[104] = pow(variables[1], geq_func(variables[2], variables[6]))
    variables[105] = pow(variables[1]-variables[2], geq_func(variables[6], variables[18]))
    variables[106] = pow(-variables[1], geq_func(variables[2], variables[6]))
    variables[107] = pow(variables[1]*variables[2], geq_func(variables[6], variables[18]))
    variables[108] = pow(variables[1]/variables[2], geq_func(variables[6], variables[18]))
    variables[109] = pow(leq_func(variables[1], variables[2]), variables[6]+variables[18])
    variables[110] = pow(leq_func(variables[1], variables[2]), variables[6])
    variables[111] = pow(leq_func(variables[1], variables[2]), variables[6]-variables[18])
    variables[112] = pow(leq_func(variables[1], variables[2]), -variables[6])
    variables[113] = pow(leq_func(variables[1], variables[2]), variables[6]*variables[18])
    variables[114] = pow(leq_func(variables[1], variables[2]), variables[6]/variables[18])
    variables[115] = pow(leq_func(variables[1], variables[2]), pow(variables[6], variables[18]))
    variables[116] = pow(leq_func(variables[1], variables[2]), pow(variables[6], 1.0/variables[18]))
    variables[117] = sqrt(variables[1])
    variables[118] = sqrt(variables[1])
    variables[119] = pow(variables[1], 1.0/3.0)
    variables[120] = pow(variables[1], 1.0/variables[2])
    variables[121] = pow(lt_func(variables[1], variables[2]), 1.0/gt_func(variables[18], variables[6]))
    variables[122] = pow(variables[1]+variables[2], 1.0/gt_func(variables[18], variables[6]))
    variables[123] = pow(variables[1], 1.0/gt_func(variables[6], variables[2]))
    variables[124] = pow(variables[1]-variables[2], 1.0/gt_func(variables[18], variables[6]))
    variables[125] = pow(-variables[1], 1.0/gt_func(variables[6], variables[2]))
    variables[126] = pow(variables[1]*variables[2], 1.0/gt_func(variables[18], variables[6]))
    variables[127] = pow(variables[1]/variables[2], 1.0/gt_func(variables[18], variables[6]))
    variables[128] = pow(lt_func(variables[1], variables[2]), 1.0/(variables[6]+variables[18]))
    variables[129] = pow(lt_func(variables[1], variables[2]), 1.0/variables[6])
    variables[130] = pow(lt_func(variables[1], variables[2]), 1.0/(variables[6]-variables[18]))
    variables[131] = pow(lt_func(variables[1], variables[2]), 1.0/-variables[6])
    variables[132] = pow(lt_func(variables[1], variables[2]), 1.0/(variables[6]*variables[18]))
    variables[133] = pow(lt_func(variables[1], variables[2]), 1.0/(variables[6]/variables[18]))
    variables[134] = pow(lt_func(variables[1], variables[2]), 1.0/pow(variables[6], variables[18]))
    variables[135] = pow(lt_func(variables[1], variables[2]), 1.0/pow(variables[6], 1.0/variables[18]))
    variables[136] = fabs(variables[1])
    variables[137] = exp(variables[1])
    variables[138] = log(variables[1])
    variables[139] = log10(variables[1])
    variables[140] = log(variables[1])/log(2.0)
    variables[141] = log10(variables[1])
    variables[142] = log(variables[1])/log(variables[2])
    variables[143] = ceil(variables[1])
    variables[144] = floor(variables[1])
    variables[145] = min(variables[1], variables[2])
    variables[146] = min(variables[1], min(variables[2], variables[6]))
    variables[147] = max(variables[1], variables[2])
    variables[148] = max(variables[1], max(variables[2], variables[6]))
    variables[149] = fmod(variables[1], variables[2])
    variables[150] = sin(variables[1])
    variables[151] = cos(variables[1])
    variables[152] = tan(variables[1])
    variables[153] = sec(variables[1])
    variables[154] = csc(variables[1])
    variables[155] = cot(variables[1])
    variables[156] = sinh(variables[1])
    variables[157] = cosh(variables[1])
    variables[158] = tanh(variables[1])
    variables[159] = sech(variables[1])
    variables[160] = csch(variables[1])
    variables[161] = coth(variables[1])
    variables[162] = asin(variables[1])
    variables[163] = acos(variables[1])
    variables[164] = atan(variables[1])
    variables[165] = asec(variables[1])
    variables[166] = acsc(variables[1])
    variables[167] = acot(variables[1])
    variables[168] = asinh(variables[1])
    variables[169] = acosh(variables[1])
    variables[170] = atanh(variables[1]/2.0)
    variables[171] = asech(variables[1])
    variables[172] = acsch(variables[1])
    variables[173] = acoth(2.0*variables[1])
    variables[174] = variables[1] if gt_func(variables[1], variables[2]) else nan
    variables[175] = variables[1] if gt_func(variables[1], variables[2]) else variables[6]
    variables[176] = variables[1] if gt_func(variables[1], variables[2]) else variables[6] if gt_func(variables[6], variables[18]) else variables[177] if gt_func(variables[177], variables[178]) else nan
    variables[179] = variables[1] if gt_func(variables[1], variables[2]) else variables[6] if gt_func(variables[6], variables[18]) else variables[177] if gt_func(variables[177], variables[178]) else variables[180]
    variables[181] = 123.0+(variables[1] if gt_func(variables[1], variables[2]) else nan)
    variables[186] = variables[1]
    variables[193] = and_func(variables[1], variables[2])+(variables[2] if gt_func(variables[6], variables[18]) else nan)+variables[177]+and_func(variables[178], variables[180])
    variables[194] = and_func(variables[1], variables[2])-((variables[2] if gt_func(variables[6], variables[18]) else nan)-(variables[177]-(variables[2] if gt_func(variables[6], variables[18]) else nan)))-and_func(variables[178], variables[180])
    variables[195] = and_func(variables[1], variables[2])*(variables[2] if gt_func(variables[6], variables[18]) else nan)*variables[177]*(variables[2] if gt_func(variables[6], variables[18]) else nan)*and_func(variables[178], variables[180])
    variables[196] = and_func(variables[1], variables[2])/((variables[2] if gt_func(variables[6], variables[18]) else nan)/(variables[177]/(variables[2] if gt_func(variables[6], variables[18]) else nan)))
    variables[197] = and_func(or_func(variables[1], variables[2]), and_func(xor_func(variables[1], variables[2]), and_func(variables[2] if gt_func(variables[6], variables[18]) else nan, and_func(and_func(and_func(variables[177], variables[2] if gt_func(variables[6], variables[18]) else nan), xor_func(variables[1], variables[2])), or_func(variables[1], variables[2])))))
    variables[198] = or_func(and_func(variables[1], variables[2]), or_func(xor_func(variables[1], variables[2]), or_func(variables[2] if gt_func(variables[6], variables[18]) else nan, or_func(or_func(or_func(variables[177], variables[2] if gt_func(variables[6], variables[18]) else nan), xor_func(variables[1], variables[2])), and_func(variables[1], variables[2])))))
    variables[199] = xor_func(and_func(variables[1], variables[2]), xor_func(or_func(variables[1], variables[2]), xor_func(variables[2] if gt_func(variables[6], variables[18]) else nan, xor_func(xor_func(xor_func(variables[177], variables[2] if gt_func(variables[6], variables[18]) else nan), or_func(variables[1], variables[2])), and_func(variables[1], variables[2])))))
    variables[200] = pow(and_func(variables[1], variables[2]), pow(variables[2] if gt_func(variables[6], variables[18]) else nan, pow(pow(variables[177], variables[2] if gt_func(variables[6], variables[18]) else nan), and_func(variables[1], variables[2]))))
    variables[201] = pow(pow(pow(and_func(variables[1], variables[2]), 1.0/pow(variables[2] if gt_func(variables[6], variables[18]) else nan, 1.0/variables[177])), 1.0/(variables[2] if gt_func(variables[6], variables[18]) else nan)), 1.0/and_func(variables[1], variables[2]))
    variables[202] = -and_func(variables[1], variables[2])+-(variables[2] if gt_func(variables[6], variables[18]) else nan)


def compute_rates(voi, states, rates, variables):
    rates[0] = 1.0


def compute_variables(voi, states, rates, variables):
    pass

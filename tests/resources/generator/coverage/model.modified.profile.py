# The content of this file was generated using a modified Python profile of libCellML 0.4.0.

from enum import Enum
from math import *


__version__ = "0.3.2.post0"
LIBCELLML_VERSION = "0.4.0"

STATE_COUNT = 1
VARIABLE_COUNT = 186


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
    {"name": "eqnEqCoverageParentheses", "units": "dimensionless", "component": "my_component", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "eqnNeq", "units": "dimensionless", "component": "my_component", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "eqnNeqCoverageParentheses", "units": "dimensionless", "component": "my_component", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "eqnLt", "units": "dimensionless", "component": "my_component", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "eqnLeq", "units": "dimensionless", "component": "my_component", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "eqnGt", "units": "dimensionless", "component": "my_component", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "eqnGeq", "units": "dimensionless", "component": "my_component", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "eqnAnd", "units": "dimensionless", "component": "my_component", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "eqnAndMultiple", "units": "dimensionless", "component": "my_component", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "eqnAndParentheses", "units": "dimensionless", "component": "my_component", "type": VariableType.COMPUTED_CONSTANT},
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
    {"name": "eqnPiecewisePiecePiecePieceOtherwise", "units": "dimensionless", "component": "my_component", "type": VariableType.COMPUTED_CONSTANT},
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


def create_states_vector():
    return [nan]*STATE_COUNT


def create_variables_array():
    return [nan]*VARIABLE_COUNT


def initialise_variables(states, variables):
    variables[179] = 1.0
    variables[180] = 2.0
    variables[181] = 3.0
    variables[182] = 4.0
    variables[183] = 5.0
    variables[184] = 6.0
    variables[185] = 7.0
    variables[168] = 123.0
    variables[169] = 123.456789
    variables[170] = 123.0e99
    variables[171] = 123.456789e99
    variables[173] = 1.0
    variables[174] = 0.0
    variables[175] = 2.71828182845905
    variables[176] = 3.14159265358979
    variables[177] = inf
    variables[178] = nan
    states[0] = 0.0


def compute_computed_constants(variables):
    variables[0] = eq_func(variables[179], variables[180])
    variables[1] = variables[179]/eq_func(variables[180], variables[180])
    variables[2] = neq_func(variables[179], variables[180])
    variables[3] = variables[179]/neq_func(variables[180], variables[181])
    variables[4] = lt_func(variables[179], variables[180])
    variables[5] = leq_func(variables[179], variables[180])
    variables[6] = gt_func(variables[179], variables[180])
    variables[7] = geq_func(variables[179], variables[180])
    variables[8] = and_func(variables[179], variables[180])
    variables[9] = and_func(variables[179], and_func(variables[180], variables[181]))
    variables[10] = and_func(lt_func(variables[179], variables[180]), gt_func(variables[181], variables[182]))
    variables[11] = and_func(variables[179]+variables[180], gt_func(variables[181], variables[182]))
    variables[12] = and_func(variables[179], gt_func(variables[180], variables[181]))
    variables[13] = and_func(variables[179]-variables[180], gt_func(variables[181], variables[182]))
    variables[14] = and_func(-variables[179], gt_func(variables[180], variables[181]))
    variables[15] = and_func(pow(variables[179], variables[180]), gt_func(variables[181], variables[182]))
    variables[16] = and_func(pow(variables[179], 1.0/variables[180]), gt_func(variables[181], variables[182]))
    variables[17] = and_func(lt_func(variables[179], variables[180]), variables[181]+variables[182])
    variables[18] = and_func(lt_func(variables[179], variables[180]), variables[181])
    variables[19] = and_func(lt_func(variables[179], variables[180]), variables[181]-variables[182])
    variables[20] = and_func(lt_func(variables[179], variables[180]), -variables[181])
    variables[21] = and_func(lt_func(variables[179], variables[180]), pow(variables[181], variables[182]))
    variables[22] = and_func(lt_func(variables[179], variables[180]), pow(variables[181], 1.0/variables[182]))
    variables[23] = or_func(variables[179], variables[180])
    variables[24] = or_func(variables[179], or_func(variables[180], variables[181]))
    variables[25] = or_func(lt_func(variables[179], variables[180]), gt_func(variables[181], variables[182]))
    variables[26] = or_func(variables[179]+variables[180], gt_func(variables[181], variables[182]))
    variables[27] = or_func(variables[179], gt_func(variables[180], variables[181]))
    variables[28] = or_func(variables[179]-variables[180], gt_func(variables[181], variables[182]))
    variables[29] = or_func(-variables[179], gt_func(variables[180], variables[181]))
    variables[30] = or_func(pow(variables[179], variables[180]), gt_func(variables[181], variables[182]))
    variables[31] = or_func(pow(variables[179], 1.0/variables[180]), gt_func(variables[181], variables[182]))
    variables[32] = or_func(lt_func(variables[179], variables[180]), variables[181]+variables[182])
    variables[33] = or_func(lt_func(variables[179], variables[180]), variables[181])
    variables[34] = or_func(lt_func(variables[179], variables[180]), variables[181]-variables[182])
    variables[35] = or_func(lt_func(variables[179], variables[180]), -variables[181])
    variables[36] = or_func(lt_func(variables[179], variables[180]), pow(variables[181], variables[182]))
    variables[37] = or_func(lt_func(variables[179], variables[180]), pow(variables[181], 1.0/variables[182]))
    variables[38] = xor_func(variables[179], variables[180])
    variables[39] = xor_func(variables[179], xor_func(variables[180], variables[181]))
    variables[40] = xor_func(lt_func(variables[179], variables[180]), gt_func(variables[181], variables[182]))
    variables[41] = xor_func(variables[179]+variables[180], gt_func(variables[181], variables[182]))
    variables[42] = xor_func(variables[179], gt_func(variables[180], variables[181]))
    variables[43] = xor_func(variables[179]-variables[180], gt_func(variables[181], variables[182]))
    variables[44] = xor_func(-variables[179], gt_func(variables[180], variables[181]))
    variables[45] = xor_func(pow(variables[179], variables[180]), gt_func(variables[181], variables[182]))
    variables[46] = xor_func(pow(variables[179], 1.0/variables[180]), gt_func(variables[181], variables[182]))
    variables[47] = xor_func(lt_func(variables[179], variables[180]), variables[181]+variables[182])
    variables[48] = xor_func(lt_func(variables[179], variables[180]), variables[181])
    variables[49] = xor_func(lt_func(variables[179], variables[180]), variables[181]-variables[182])
    variables[50] = xor_func(lt_func(variables[179], variables[180]), -variables[181])
    variables[51] = xor_func(lt_func(variables[179], variables[180]), pow(variables[181], variables[182]))
    variables[52] = xor_func(lt_func(variables[179], variables[180]), pow(variables[181], 1.0/variables[182]))
    variables[53] = not_func(variables[179])
    variables[54] = variables[179]+variables[180]
    variables[55] = variables[179]+variables[180]+variables[181]
    variables[56] = lt_func(variables[179], variables[180])+gt_func(variables[181], variables[182])
    variables[57] = variables[179]
    variables[58] = variables[179]-variables[180]
    variables[59] = lt_func(variables[179], variables[180])-gt_func(variables[181], variables[182])
    variables[60] = lt_func(variables[179], variables[180])-(variables[181]+variables[182])
    variables[61] = lt_func(variables[179], variables[180])-variables[181]
    variables[62] = -variables[179]
    variables[63] = -lt_func(variables[179], variables[180])
    variables[64] = variables[179]*variables[180]
    variables[65] = variables[179]*variables[180]*variables[181]
    variables[66] = lt_func(variables[179], variables[180])*gt_func(variables[181], variables[182])
    variables[67] = (variables[179]+variables[180])*gt_func(variables[181], variables[182])
    variables[68] = variables[179]*gt_func(variables[180], variables[181])
    variables[69] = (variables[179]-variables[180])*gt_func(variables[181], variables[182])
    variables[70] = -variables[179]*gt_func(variables[180], variables[181])
    variables[71] = lt_func(variables[179], variables[180])*(variables[181]+variables[182])
    variables[72] = lt_func(variables[179], variables[180])*variables[181]
    variables[73] = lt_func(variables[179], variables[180])*(variables[181]-variables[182])
    variables[74] = lt_func(variables[179], variables[180])*-variables[181]
    variables[75] = variables[179]/variables[180]
    variables[76] = lt_func(variables[179], variables[180])/gt_func(variables[182], variables[181])
    variables[77] = (variables[179]+variables[180])/gt_func(variables[182], variables[181])
    variables[78] = variables[179]/gt_func(variables[181], variables[180])
    variables[79] = (variables[179]-variables[180])/gt_func(variables[182], variables[181])
    variables[80] = -variables[179]/gt_func(variables[181], variables[180])
    variables[81] = lt_func(variables[179], variables[180])/(variables[181]+variables[182])
    variables[82] = lt_func(variables[179], variables[180])/variables[181]
    variables[83] = lt_func(variables[179], variables[180])/(variables[181]-variables[182])
    variables[84] = lt_func(variables[179], variables[180])/-variables[181]
    variables[85] = lt_func(variables[179], variables[180])/(variables[181]*variables[182])
    variables[86] = lt_func(variables[179], variables[180])/(variables[181]/variables[182])
    variables[87] = sqrt(variables[179])
    variables[88] = pow(variables[179], 2.0)
    variables[89] = pow(variables[179], 3.0)
    variables[90] = pow(variables[179], variables[180])
    variables[91] = pow(lt_func(variables[179], variables[180]), gt_func(variables[181], variables[182]))
    variables[92] = pow(variables[179]+variables[180], gt_func(variables[181], variables[182]))
    variables[93] = pow(variables[179], gt_func(variables[180], variables[181]))
    variables[94] = pow(variables[179]-variables[180], gt_func(variables[181], variables[182]))
    variables[95] = pow(-variables[179], gt_func(variables[180], variables[181]))
    variables[96] = pow(variables[179]*variables[180], gt_func(variables[181], variables[182]))
    variables[97] = pow(variables[179]/variables[180], gt_func(variables[181], variables[182]))
    variables[98] = pow(lt_func(variables[179], variables[180]), variables[181]+variables[182])
    variables[99] = pow(lt_func(variables[179], variables[180]), variables[181])
    variables[100] = pow(lt_func(variables[179], variables[180]), variables[181]-variables[182])
    variables[101] = pow(lt_func(variables[179], variables[180]), -variables[181])
    variables[102] = pow(lt_func(variables[179], variables[180]), variables[181]*variables[182])
    variables[103] = pow(lt_func(variables[179], variables[180]), variables[181]/variables[182])
    variables[104] = pow(lt_func(variables[179], variables[180]), pow(variables[181], variables[182]))
    variables[105] = pow(lt_func(variables[179], variables[180]), pow(variables[181], 1.0/variables[182]))
    variables[106] = sqrt(variables[179])
    variables[107] = sqrt(variables[179])
    variables[108] = pow(variables[179], 1.0/3.0)
    variables[109] = pow(variables[179], 1.0/variables[180])
    variables[110] = pow(lt_func(variables[179], variables[180]), 1.0/gt_func(variables[182], variables[181]))
    variables[111] = pow(variables[179]+variables[180], 1.0/gt_func(variables[182], variables[181]))
    variables[112] = pow(variables[179], 1.0/gt_func(variables[181], variables[180]))
    variables[113] = pow(variables[179]-variables[180], 1.0/gt_func(variables[182], variables[181]))
    variables[114] = pow(-variables[179], 1.0/gt_func(variables[181], variables[180]))
    variables[115] = pow(variables[179]*variables[180], 1.0/gt_func(variables[182], variables[181]))
    variables[116] = pow(variables[179]/variables[180], 1.0/gt_func(variables[182], variables[181]))
    variables[117] = pow(lt_func(variables[179], variables[180]), 1.0/(variables[181]+variables[182]))
    variables[118] = pow(lt_func(variables[179], variables[180]), 1.0/variables[181])
    variables[119] = pow(lt_func(variables[179], variables[180]), 1.0/(variables[181]-variables[182]))
    variables[120] = pow(lt_func(variables[179], variables[180]), 1.0/-variables[181])
    variables[121] = pow(lt_func(variables[179], variables[180]), 1.0/(variables[181]*variables[182]))
    variables[122] = pow(lt_func(variables[179], variables[180]), 1.0/(variables[181]/variables[182]))
    variables[123] = pow(lt_func(variables[179], variables[180]), 1.0/pow(variables[181], variables[182]))
    variables[124] = pow(lt_func(variables[179], variables[180]), 1.0/pow(variables[181], 1.0/variables[182]))
    variables[125] = fabs(variables[179])
    variables[126] = exp(variables[179])
    variables[127] = log(variables[179])
    variables[128] = log10(variables[179])
    variables[129] = log(variables[179])/log(2.0)
    variables[130] = log10(variables[179])
    variables[131] = log(variables[179])/log(variables[180])
    variables[132] = ceil(variables[179])
    variables[133] = floor(variables[179])
    variables[134] = min(variables[179], variables[180])
    variables[135] = min(variables[179], min(variables[180], variables[181]))
    variables[136] = max(variables[179], variables[180])
    variables[137] = max(variables[179], max(variables[180], variables[181]))
    variables[138] = fmod(variables[179], variables[180])
    variables[139] = sin(variables[179])
    variables[140] = cos(variables[179])
    variables[141] = tan(variables[179])
    variables[142] = sec(variables[179])
    variables[143] = csc(variables[179])
    variables[144] = cot(variables[179])
    variables[145] = sinh(variables[179])
    variables[146] = cosh(variables[179])
    variables[147] = tanh(variables[179])
    variables[148] = sech(variables[179])
    variables[149] = csch(variables[179])
    variables[150] = coth(variables[179])
    variables[151] = asin(variables[179])
    variables[152] = acos(variables[179])
    variables[153] = atan(variables[179])
    variables[154] = asec(variables[179])
    variables[155] = acsc(variables[179])
    variables[156] = acot(variables[179])
    variables[157] = asinh(variables[179])
    variables[158] = acosh(variables[179])
    variables[159] = atanh(variables[179]/2.0)
    variables[160] = asech(variables[179])
    variables[161] = acsch(variables[179])
    variables[162] = acoth(2.0*variables[179])
    variables[163] = variables[179] if gt_func(variables[179], variables[180]) else nan
    variables[164] = variables[179] if gt_func(variables[179], variables[180]) else variables[181]
    variables[165] = variables[179] if gt_func(variables[179], variables[180]) else variables[181] if gt_func(variables[181], variables[182]) else variables[183] if gt_func(variables[183], variables[184]) else nan
    variables[166] = variables[179] if gt_func(variables[179], variables[180]) else variables[181] if gt_func(variables[181], variables[182]) else variables[183] if gt_func(variables[183], variables[184]) else variables[185]
    variables[167] = 123.0+(variables[179] if gt_func(variables[179], variables[180]) else nan)
    variables[172] = variables[179]


def compute_rates(voi, states, rates, variables):
    rates[0] = 1.0


def compute_variables(voi, states, rates, variables):
    pass

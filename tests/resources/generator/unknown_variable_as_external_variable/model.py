# The content of this file was generated using the Python profile of libCellML 0.5.0.

from enum import Enum
from math import *


__version__ = "0.5.0"
LIBCELLML_VERSION = "0.5.0"

CONSTANT_COUNT = 0
COMPUTED_CONSTANT_COUNT = 0
ALGEBRAIC_COUNT = 10
EXTERNAL_COUNT = 0


class VariableType(Enum):
    CONSTANT = 0
    COMPUTED_CONSTANT = 1
    ALGEBRAIC = 2
    EXTERNAL = 3


VARIABLE_INFO = [
    {"name": "v", "units": "fmol_per_sec", "component": "SLC_template3_ss", "type": VariableType.ALGEBRAIC},
    {"name": "E", "units": "fmol", "component": "SLC_template3_ss", "type": VariableType.CONSTANT},
    {"name": "P_0", "units": "per_fmol_sec4", "component": "SLC_template3_ss", "type": VariableType.CONSTANT},
    {"name": "q_Ao", "units": "fmol", "component": "SLC_template3_ss", "type": VariableType.CONSTANT},
    {"name": "P_1", "units": "per_fmol_sec4", "component": "SLC_template3_ss", "type": VariableType.CONSTANT},
    {"name": "q_Ai", "units": "fmol", "component": "SLC_template3_ss", "type": VariableType.CONSTANT},
    {"name": "P_2", "units": "per_fmol_sec3", "component": "SLC_template3_ss", "type": VariableType.CONSTANT},
    {"name": "P_5", "units": "per_sec3", "component": "SLC_template3_ss", "type": VariableType.CONSTANT},
    {"name": "P_4", "units": "per_fmol2_sec3", "component": "SLC_template3_ss", "type": VariableType.CONSTANT},
    {"name": "P_3", "units": "per_fmol_sec3", "component": "SLC_template3_ss", "type": VariableType.EXTERNAL}
]


def create_variables_array():
    return [nan]*VARIABLE_COUNT


def initialise_variables(constants, external_variable):
    constants[0] = 1.1
    constants[1] = 21262500.0
    constants[2] = 150.0
    constants[3] = 3402000.0
    constants[4] = 2.0
    constants[5] = 2902500.0
    constants[6] = 810000.0
    constants[7] = 247140.0
    algebraic[1] = external_variable(variables, 1)


def compute_computed_constants(constants, computed_constants):
    pass


def compute_variables(constants, computed_constants, algebraic, external_variable):
    algebraic[1] = external_variable(variables, 1)
    algebraic[0] = constants[0]*(constants[1]*constants[2]-constants[3]*constants[4])/(constants[5]*constants[4]+algebraic[1]*constants[2]+constants[7]*constants[4]*constants[2]+constants[6])

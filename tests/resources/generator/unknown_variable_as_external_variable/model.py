# The content of this file was generated using the Python profile of libCellML 0.5.0.

from enum import Enum
from math import *


__version__ = "0.4.0"
LIBCELLML_VERSION = "0.5.0"

CONSTANT_COUNT = 0
COMPUTED_CONSTANT_COUNT = 0
ALGEBRAIC_COUNT = 10


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
    variables[1] = 1.1
    variables[2] = 21262500.0
    variables[3] = 150.0
    variables[4] = 3402000.0
    variables[5] = 2.0
    variables[6] = 2902500.0
    variables[7] = 810000.0
    variables[8] = 247140.0
    variables[9] = external_variable(variables, 9)


def compute_computed_constants(computed_constants):
    pass


def compute_variables(constants, computedConstants, algebraic, external_variable):
    variables[9] = external_variable(variables, 9)
    variables[0] = variables[1]*(variables[2]*variables[3]-variables[4]*variables[5])/(variables[6]*variables[5]+variables[9]*variables[3]+variables[8]*variables[5]*variables[3]+variables[7])

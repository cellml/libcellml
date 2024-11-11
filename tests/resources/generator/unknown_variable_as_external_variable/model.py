# The content of this file was generated using the Python profile of libCellML 0.6.3.

from enum import Enum
from math import *


__version__ = "0.4.0"
LIBCELLML_VERSION = "0.6.3"

VARIABLE_COUNT = 10


class VariableType(Enum):
    CONSTANT = 0
    COMPUTED_CONSTANT = 1
    ALGEBRAIC = 2
    EXTERNAL = 3


VARIABLE_INFO = [
    {"name": "P_5", "units": "per_sec3", "component": "SLC_template3_ss", "type": VariableType.CONSTANT},
    {"name": "q_Ao", "units": "fmol", "component": "SLC_template3_ss", "type": VariableType.CONSTANT},
    {"name": "q_Ai", "units": "fmol", "component": "SLC_template3_ss", "type": VariableType.CONSTANT},
    {"name": "P_4", "units": "per_fmol2_sec3", "component": "SLC_template3_ss", "type": VariableType.CONSTANT},
    {"name": "P_3", "units": "per_fmol_sec3", "component": "SLC_template3_ss", "type": VariableType.EXTERNAL},
    {"name": "P_2", "units": "per_fmol_sec3", "component": "SLC_template3_ss", "type": VariableType.CONSTANT},
    {"name": "P_1", "units": "per_fmol_sec4", "component": "SLC_template3_ss", "type": VariableType.CONSTANT},
    {"name": "P_0", "units": "per_fmol_sec4", "component": "SLC_template3_ss", "type": VariableType.CONSTANT},
    {"name": "E", "units": "fmol", "component": "SLC_template3_ss", "type": VariableType.CONSTANT},
    {"name": "v", "units": "fmol_per_sec", "component": "SLC_template3_ss", "type": VariableType.ALGEBRAIC}
]


def create_variables_array():
    return [nan]*VARIABLE_COUNT


def initialise_variables(variables, external_variable):
    variables[0] = 810000.0
    variables[1] = 150.0
    variables[2] = 2.0
    variables[3] = 247140.0
    variables[5] = 2902500.0
    variables[6] = 3402000.0
    variables[7] = 21262500.0
    variables[8] = 1.1
    variables[4] = external_variable(variables, 4)


def compute_computed_constants(variables):
    pass


def compute_variables(variables, external_variable):
    variables[4] = external_variable(variables, 4)
    variables[9] = variables[8]*(variables[7]*variables[1]-variables[6]*variables[2])/(variables[5]*variables[2]+variables[4]*variables[1]+variables[3]*variables[2]*variables[1]+variables[0])

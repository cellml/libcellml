# The content of this file was generated using the Python profile of libCellML 0.4.0.

from enum import Enum
from math import *


__version__ = "0.3.2"
LIBCELLML_VERSION = "0.4.0"

STATE_COUNT = 2
VARIABLE_COUNT = 15


class VariableType(Enum):
    VARIABLE_OF_INTEGRATION = 0
    STATE = 1
    CONSTANT = 2
    COMPUTED_CONSTANT = 3
    ALGEBRAIC = 4


VOI_INFO = {"name": "t", "units": "second", "component": "BG_initTest", "type": VariableType.VARIABLE_OF_INTEGRATION}

STATE_INFO = [
    {"name": "q_Ai", "units": "fmol", "component": "BG_initTest", "type": VariableType.STATE},
    {"name": "q_Ao", "units": "fmol", "component": "BG_initTest", "type": VariableType.STATE}
]

VARIABLE_INFO = [
    {"name": "mu_Ai", "units": "J_per_mol", "component": "BG_initTest", "type": VariableType.ALGEBRAIC},
    {"name": "R", "units": "J_per_K_per_mol", "component": "BG_initTest_param", "type": VariableType.CONSTANT},
    {"name": "K_Ai", "units": "per_fmol", "component": "BG_initTest_param", "type": VariableType.CONSTANT},
    {"name": "T", "units": "kelvin", "component": "BG_initTest_param", "type": VariableType.CONSTANT},
    {"name": "v_Ai", "units": "fmol_per_sec", "component": "BG_initTest", "type": VariableType.ALGEBRAIC},
    {"name": "mu_Ao", "units": "J_per_mol", "component": "BG_initTest", "type": VariableType.ALGEBRAIC},
    {"name": "K_Ao", "units": "per_fmol", "component": "BG_initTest_param", "type": VariableType.CONSTANT},
    {"name": "v_Ao", "units": "fmol_per_sec", "component": "BG_initTest", "type": VariableType.ALGEBRAIC},
    {"name": "v_Re1", "units": "fmol_per_sec", "component": "BG_initTest", "type": VariableType.ALGEBRAIC},
    {"name": "kappa_Re1", "units": "fmol_per_sec", "component": "BG_initTest_param", "type": VariableType.CONSTANT},
    {"name": "mu_Re1_in", "units": "J_per_mol", "component": "BG_initTest", "type": VariableType.ALGEBRAIC},
    {"name": "mu_Re1_out", "units": "J_per_mol", "component": "BG_initTest", "type": VariableType.ALGEBRAIC},
    {"name": "q_Ai_init", "units": "fmol", "component": "BG_initTest_param", "type": VariableType.CONSTANT},
    {"name": "q_Ao_init", "units": "fmol", "component": "BG_initTest_param", "type": VariableType.CONSTANT},
    {"name": "F", "units": "C_per_mol", "component": "BG_initTest_param", "type": VariableType.CONSTANT}
]


def create_states_array():
    return [nan]*STATE_COUNT


def create_variables_array():
    return [nan]*VARIABLE_COUNT


def initialise_variables(states, variables):
    variables[1] = 8.31
    variables[2] = 1.0
    variables[3] = 293.0
    variables[6] = 1.0
    variables[9] = 1.0
    variables[12] = 1.0
    variables[13] = 1.0
    variables[14] = 96485.0
    states[0] = variables[12]
    states[1] = variables[13]


def compute_computed_constants(variables):
    pass


def compute_rates(voi, states, rates, variables):
    variables[5] = variables[1]*variables[3]*log(variables[6]*states[1])
    variables[10] = variables[5]
    variables[0] = variables[1]*variables[3]*log(variables[2]*states[0])
    variables[11] = variables[0]
    variables[8] = variables[9]*(exp(variables[10]/(variables[1]*variables[3]))-exp(variables[11]/(variables[1]*variables[3])))
    variables[4] = variables[8]
    rates[0] = variables[4]
    variables[7] = -variables[8]
    rates[1] = variables[7]


def compute_variables(voi, states, rates, variables):
    variables[0] = variables[1]*variables[3]*log(variables[2]*states[0])
    variables[5] = variables[1]*variables[3]*log(variables[6]*states[1])
    variables[10] = variables[5]
    variables[11] = variables[0]
    variables[8] = variables[9]*(exp(variables[10]/(variables[1]*variables[3]))-exp(variables[11]/(variables[1]*variables[3])))
    variables[4] = variables[8]
    variables[7] = -variables[8]

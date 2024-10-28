# The content of this file was generated using the Python profile of libCellML 0.6.1.

from enum import Enum
from math import *


__version__ = "0.5.0"
LIBCELLML_VERSION = "0.6.1"

CONSTANT_COUNT = 8
COMPUTED_CONSTANT_COUNT = 0
ALGEBRAIC_COUNT = 1
EXTERNAL_COUNT = 1

CONSTANT_INFO = [
    {"name": "E", "units": "fmol", "component": "SLC_template3_ss"},
    {"name": "P_0", "units": "per_fmol_sec4", "component": "SLC_template3_ss"},
    {"name": "q_Ao", "units": "fmol", "component": "SLC_template3_ss"},
    {"name": "P_1", "units": "per_fmol_sec4", "component": "SLC_template3_ss"},
    {"name": "q_Ai", "units": "fmol", "component": "SLC_template3_ss"},
    {"name": "P_2", "units": "per_fmol_sec3", "component": "SLC_template3_ss"},
    {"name": "P_5", "units": "per_sec3", "component": "SLC_template3_ss"},
    {"name": "P_4", "units": "per_fmol2_sec3", "component": "SLC_template3_ss"}
]

COMPUTED_CONSTANT_INFO = [
]

ALGEBRAIC_INFO = [
    {"name": "v", "units": "fmol_per_sec", "component": "SLC_template3_ss"}
]

EXTERNAL_INFO = [
    {"name": "P_3", "units": "per_fmol_sec3", "component": "SLC_template3_ss"}
]


def create_constants_array():
    return [nan]*CONSTANT_COUNT


def create_computed_constants_array():
    return [nan]*COMPUTED_CONSTANT_COUNT


def create_algebraic_array():
    return [nan]*ALGEBRAIC_COUNT


def create_externals_array():
    return [nan]*EXTERNAL_COUNT


def initialise_variables(constants, computed_constants, algebraic):
    constants[0] = 1.1
    constants[1] = 21262500.0
    constants[2] = 150.0
    constants[3] = 3402000.0
    constants[4] = 2.0
    constants[5] = 2902500.0
    constants[6] = 810000.0
    constants[7] = 247140.0


def compute_computed_constants(constants, computed_constants):
    pass


def compute_variables(constants, computed_constants, algebraic, externals, external_variable):
    externals[0] = external_variable(constants, computed_constants, algebraic, externals, 0)
    algebraic[0] = constants[0]*(constants[1]*constants[2]-constants[3]*constants[4])/(constants[5]*constants[4]+externals[0]*constants[2]+constants[7]*constants[4]*constants[2]+constants[6])

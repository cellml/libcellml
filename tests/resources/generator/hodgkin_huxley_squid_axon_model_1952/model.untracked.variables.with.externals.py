# The content of this file was generated using the Python profile of libCellML 0.6.1.

from enum import Enum
from math import *


__version__ = "0.5.0"
LIBCELLML_VERSION = "0.6.1"

STATE_COUNT = 3
CONSTANT_COUNT = 0
COMPUTED_CONSTANT_COUNT = 0
ALGEBRAIC_COUNT = 0
EXTERNAL_COUNT = 0

VOI_INFO = {"name": "time", "units": "millisecond", "component": "environment"}

STATE_INFO = [
    {"name": "h", "units": "dimensionless", "component": "sodium_channel_h_gate"},
    {"name": "m", "units": "dimensionless", "component": "sodium_channel_m_gate"},
    {"name": "n", "units": "dimensionless", "component": "potassium_channel_n_gate"}
]

CONSTANT_INFO = [
]

COMPUTED_CONSTANT_INFO = [
]

ALGEBRAIC_INFO = [
]

EXTERNAL_INFO = [
]


def leq_func(x, y):
    return 1.0 if x <= y else 0.0


def geq_func(x, y):
    return 1.0 if x >= y else 0.0


def and_func(x, y):
    return 1.0 if bool(x) & bool(y) else 0.0


def create_states_array():
    return [nan]*STATE_COUNT


def create_constants_array():
    return [nan]*CONSTANT_COUNT


def create_computed_constants_array():
    return [nan]*COMPUTED_CONSTANT_COUNT


def create_algebraic_array():
    return [nan]*ALGEBRAIC_COUNT


def create_externals_array():
    return [nan]*EXTERNAL_COUNT


def initialise_variables(states, rates, constants, computed_constants, algebraic):
    states[0] = 0.6
    states[1] = 0.05
    states[2] = 0.325


def compute_computed_constants(constants, computed_constants):
    pass


def compute_rates(voi, states, rates, constants, computed_constants, algebraic, externals, external_variable):
    membrane_V = external_variable(voi, states, rates, constants, computed_constants, algebraic, externals, 0)
    sodium_channel_m_gate_alpha_m = 0.1*(membrane_V+25.0)/(exp((membrane_V+25.0)/10.0)-1.0)
    sodium_channel_m_gate_beta_m = 4.0*exp(membrane_V/18.0)
    rates[1] = sodium_channel_m_gate_alpha_m*(1.0-states[1])-sodium_channel_m_gate_beta_m*states[1]
    sodium_channel_h_gate_alpha_h = 0.07*exp(membrane_V/20.0)
    sodium_channel_h_gate_beta_h = 1.0/(exp((membrane_V+30.0)/10.0)+1.0)
    rates[0] = sodium_channel_h_gate_alpha_h*(1.0-states[0])-sodium_channel_h_gate_beta_h*states[0]
    potassium_channel_n_gate_alpha_n = external_variable(voi, states, rates, constants, computed_constants, algebraic, externals, 2)
    potassium_channel_n_gate_beta_n = 0.125*exp(membrane_V/80.0)
    rates[2] = potassium_channel_n_gate_alpha_n*(1.0-states[2])-potassium_channel_n_gate_beta_n*states[2]


def compute_variables(voi, states, rates, constants, computed_constants, algebraic, externals, external_variable):
    pass

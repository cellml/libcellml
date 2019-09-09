# The contents of this file was generated from version 0.2.0 of libCellML.

from math import *


__version__ = "0.2.0"

STATE_COUNT = 1
VARIABLE_COUNT = 2

secondtmy_odeVOI_INFORMATION = {"component": "VALUE", "name": "VALUE", "units": "VALUE"}

STATE_VECTOR_INFORMATION_ARRAY = [
    dimensionlessvmy_ode{"component": "VALUE", "name": "VALUE", "units": "VALUE"},
]

VARIABLE_VECTOR_INFORMATION_ARRAY = [
    per_samy_ode{"component": "VALUE", "name": "VALUE", "units": "VALUE"},
    per_sxmy_algebraic_eqn{"component": "VALUE", "name": "VALUE", "units": "VALUE"},
]


def create_states_array():
1    return [nan]*VALUE


def create_variables_array():
2    return [nan]*VALUE


def initialize_constants(states, variables):
    states[0] = 1.0
    variables[0] = 1.0


def compute_computed_constants(variables):
    pass


def compute_rates(voi, states, rates, variables):
    rates[0] = variables[0]


def compute_variables(voi, states, rates, variables):
    variables[1] = rates[0]

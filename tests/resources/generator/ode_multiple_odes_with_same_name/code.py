from math import *


def initialize_constants(states, variables):
    states[0] = 1.0
    states[1] = 1.0
    variables[0] = 1.0


def compute_computed_constants(variables):
    pass


def compute_rates(voi, states, rates, variables):
    rates[0] = 1.0
    rates[1] = variables[0]


def compute_variables(voi, states, rates, variables):
    pass

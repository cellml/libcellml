from math import *


def initialize_constants(states, variables):
    states[0] = 0.0
    states[1] = 1.0


def compute_computed_constants(variables):
    pass


def compute_rates(voi, states, rates, variables):
    rates[0] = -states[1]*1.0
    rates[1] = states[0]*1.0


def compute_variables(voi, states, rates, variables):
    variables[0] = states[1]+5.0*states[1]/3.0+1.0*exp(states[1]/2.0)
    variables[1] = 2.0*states[0]


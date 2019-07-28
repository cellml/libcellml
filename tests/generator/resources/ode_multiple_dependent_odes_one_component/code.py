from math import *

def initializeConstants(states, variables):
    states[0] = -2.0
    states[1] = 0.0
    variables[0] = 1.0

def computeComputedConstants(variables):
    pass

def computeRates(voi, states, rates, variables):
    rates[0] = states[1]*1.0
    rates[1] = (variables[0]*(1.0-pow(states[0], 2.0))*states[1]-states[0])*1.0

def computeVariables(voi, states, rates, variables):
    pass

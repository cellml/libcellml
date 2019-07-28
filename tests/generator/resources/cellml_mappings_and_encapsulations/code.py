def initializeConstants(states, variables):
    states[0] = 0.0
    states[1] = 1.0

def computeComputedConstants(variables):
    pass

def computeRates(voi, states, rates, variables):
    rates[0] = -states[1]*1.0
    rates[1] = states[0]*1.0

def computeVariables(voi, states, rates, variables):
    variables[0] = states[1]+5.0*states[1]/3.0+1.0*exp(states[1]/2.0)
    variables[1] = 2.0*states[0]

from math import *

def leqFunc(x, y):
    return 1.0 if (x <= y) else 0.0

def geqFunc(x, y):
    return 1.0 if (x >= y) else 0.0

def andFunc(x, y):
    return 1.0 if (bool(x) & bool(y)) else 0.0

def initializeConstants(states, variables):
    states[0] = 0.05
    states[1] = 0.6
    states[2] = 0.325
    states[3] = 0.0
    variables[0] = 0.3
    variables[1] = 1.0
    variables[2] = 0.0
    variables[3] = 36.0
    variables[4] = 120.0

def computeComputedConstants(variables):
    variables[6] = variables[2]-10.613
    variables[8] = variables[2]-115.0
    variables[14] = variables[2]+12.0

def computeRates(voi, states, rates, variables):
    variables[10] = 0.1*(states[3]+25.0)/(exp((states[3]+25.0)/10.0)-1.0)
    variables[11] = 4.0*exp(states[3]/18.0)
    rates[0] = variables[10]*(1.0-states[0])-variables[11]*states[0]
    variables[12] = 0.07*exp(states[3]/20.0)
    variables[13] = 1.0/(exp((states[3]+30.0)/10.0)+1.0)
    rates[1] = variables[12]*(1.0-states[1])-variables[13]*states[1]
    variables[16] = 0.01*(states[3]+10.0)/(exp((states[3]+10.0)/10.0)-1.0)
    variables[17] = 0.125*exp(states[3]/80.0)
    rates[2] = variables[16]*(1.0-states[2])-variables[17]*states[2]
    variables[5] = -20.0 if (andFunc(geqFunc(voi, 10.0), leqFunc(voi, 10.5))) else 0.0
    variables[7] = variables[0]*(states[3]-variables[6])
    variables[15] = variables[3]*pow(states[2], 4.0)*(states[3]-variables[14])
    variables[9] = variables[4]*pow(states[0], 3.0)*states[1]*(states[3]-variables[8])
    rates[3] = -(-variables[5]+variables[9]+variables[15]+variables[7])/variables[1]

def computeVariables(voi, states, rates, variables):
    variables[7] = variables[0]*(states[3]-variables[6])
    variables[9] = variables[4]*pow(states[0], 3.0)*states[1]*(states[3]-variables[8])
    variables[10] = 0.1*(states[3]+25.0)/(exp((states[3]+25.0)/10.0)-1.0)
    variables[11] = 4.0*exp(states[3]/18.0)
    variables[12] = 0.07*exp(states[3]/20.0)
    variables[13] = 1.0/(exp((states[3]+30.0)/10.0)+1.0)
    variables[15] = variables[3]*pow(states[2], 4.0)*(states[3]-variables[14])
    variables[16] = 0.01*(states[3]+10.0)/(exp((states[3]+10.0)/10.0)-1.0)
    variables[17] = 0.125*exp(states[3]/80.0)

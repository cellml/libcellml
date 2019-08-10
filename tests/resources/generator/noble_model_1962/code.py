from math import *


def initialize_constants(states, variables):
    states[0] = 0.01
    states[1] = 0.8
    states[2] = 0.01
    states[3] = -87.0
    variables[0] = -60.0
    variables[1] = 0.075
    variables[2] = 12.0
    variables[3] = 40.0
    variables[4] = 400.0


def compute_computed_constants(variables):
    pass


def compute_rates(voi, states, rates, variables):
    variables[8] = 0.1*(-states[3]-48.0)/(exp((-states[3]-48.0)/15.0)-1.0)
    variables[9] = 0.12*(states[3]+8.0)/(exp((states[3]+8.0)/5.0)-1.0)
    rates[0] = variables[8]*(1.0-states[0])-variables[9]*states[0]
    variables[10] = 0.17*exp((-states[3]-90.0)/20.0)
    variables[11] = 1.0/(1.0+exp((-states[3]-42.0)/10.0))
    rates[1] = variables[10]*(1.0-states[1])-variables[11]*states[1]
    variables[14] = 0.0001*(-states[3]-50.0)/(exp((-states[3]-50.0)/10.0)-1.0)
    variables[15] = 0.002*exp((-states[3]-90.0)/80.0)
    rates[2] = variables[14]*(1.0-states[2])-variables[15]*states[2]
    variables[6] = pow(states[0], 3.0)*states[1]*variables[4]
    variables[7] = (variables[6]+0.14)*(states[3]-variables[3])
    variables[5] = variables[1]*(states[3]-variables[0])
    variables[12] = 1.2*exp((-states[3]-90.0)/50.0)+0.015*exp((states[3]+90.0)/60.0)
    variables[13] = 1.2*pow(states[2], 4.0)
    variables[16] = (variables[12]+variables[13])*(states[3]+100.0)
    rates[3] = -(variables[7]+variables[16]+variables[5])/variables[2]


def compute_variables(voi, states, rates, variables):
    variables[5] = variables[1]*(states[3]-variables[0])
    variables[6] = pow(states[0], 3.0)*states[1]*variables[4]
    variables[7] = (variables[6]+0.14)*(states[3]-variables[3])
    variables[8] = 0.1*(-states[3]-48.0)/(exp((-states[3]-48.0)/15.0)-1.0)
    variables[9] = 0.12*(states[3]+8.0)/(exp((states[3]+8.0)/5.0)-1.0)
    variables[10] = 0.17*exp((-states[3]-90.0)/20.0)
    variables[11] = 1.0/(1.0+exp((-states[3]-42.0)/10.0))
    variables[12] = 1.2*exp((-states[3]-90.0)/50.0)+0.015*exp((states[3]+90.0)/60.0)
    variables[13] = 1.2*pow(states[2], 4.0)
    variables[14] = 0.0001*(-states[3]-50.0)/(exp((-states[3]-50.0)/10.0)-1.0)
    variables[15] = 0.002*exp((-states[3]-90.0)/80.0)
    variables[16] = (variables[12]+variables[13])*(states[3]+100.0)


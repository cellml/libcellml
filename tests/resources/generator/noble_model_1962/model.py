# The content of this file was generated using the Python profile of libCellML 0.5.0.

from enum import Enum
from math import *


__version__ = "0.5.0"
LIBCELLML_VERSION = "0.5.0"

STATE_COUNT = 4
CONSTANT_COUNT = 5
COMPUTED_CONSTANT_COUNT = 0
ALGEBRAIC_COUNT = 12

VOI_INFO = {"name": "time", "units": "millisecond", "component": "environment"}

STATE_INFO = [
    {"name": "V", "units": "millivolt", "component": "membrane"},
    {"name": "m", "units": "dimensionless", "component": "sodium_channel_m_gate"},
    {"name": "h", "units": "dimensionless", "component": "sodium_channel_h_gate"},
    {"name": "n", "units": "dimensionless", "component": "potassium_channel_n_gate"}
]

CONSTANT_INFO = [
    {"name": "Cm", "units": "microF_per_cm2", "component": "membrane"},
    {"name": "g_L", "units": "milliS_per_cm2", "component": "leakage_current"},
    {"name": "E_L", "units": "millivolt", "component": "leakage_current"},
    {"name": "g_Na_max", "units": "milliS_per_cm2", "component": "sodium_channel"},
    {"name": "E_Na", "units": "millivolt", "component": "sodium_channel"}
]

COMPUTED_CONSTANT_INFO = [
]

ALGEBRAIC_INFO = [
    {"name": "i_Na", "units": "microA_per_cm2", "component": "sodium_channel"},
    {"name": "i_Leak", "units": "microA_per_cm2", "component": "leakage_current"},
    {"name": "i_K", "units": "microA_per_cm2", "component": "potassium_channel"},
    {"name": "g_Na", "units": "milliS_per_cm2", "component": "sodium_channel"},
    {"name": "alpha_m", "units": "per_millisecond", "component": "sodium_channel_m_gate"},
    {"name": "beta_m", "units": "per_millisecond", "component": "sodium_channel_m_gate"},
    {"name": "alpha_h", "units": "per_millisecond", "component": "sodium_channel_h_gate"},
    {"name": "beta_h", "units": "per_millisecond", "component": "sodium_channel_h_gate"},
    {"name": "g_K1", "units": "milliS_per_cm2", "component": "potassium_channel"},
    {"name": "g_K2", "units": "milliS_per_cm2", "component": "potassium_channel"},
    {"name": "alpha_n", "units": "per_millisecond", "component": "potassium_channel_n_gate"},
    {"name": "beta_n", "units": "per_millisecond", "component": "potassium_channel_n_gate"}
]


def create_states_array():
    return [nan]*STATE_COUNT


def create_constants_array():
    return [nan]*CONSTANT_COUNT


def create_computed_constants_array():
    return [nan]*COMPUTED_CONSTANT_COUNT


def create_algebraic_array():
    return [nan]*ALGEBRAIC_COUNT


def initialise_variables(states, rates, constants, algebraic):
    constants[0] = 12.0
    constants[1] = 0.075
    constants[2] = -60.0
    constants[3] = 400.0
    constants[4] = 40.0
    states[0] = -87.0
    states[1] = 0.01
    states[2] = 0.8
    states[3] = 0.01


def compute_computed_constants(constants, computed_constants):
    pass


def compute_rates(voi, states, rates, constants, computed_constants, algebraic):
    algebraic[3] = pow(states[1], 3.0)*states[2]*constants[3]
    algebraic[0] = (algebraic[3]+0.14)*(states[0]-constants[4])
    algebraic[1] = constants[1]*(states[0]-constants[2])
    algebraic[8] = 1.2*exp((-states[0]-90.0)/50.0)+0.015*exp((states[0]+90.0)/60.0)
    algebraic[9] = 1.2*pow(states[3], 4.0)
    algebraic[2] = (algebraic[8]+algebraic[9])*(states[0]+100.0)
    rates[0] = -(algebraic[0]+algebraic[2]+algebraic[1])/constants[0]
    algebraic[4] = 0.1*(-states[0]-48.0)/(exp((-states[0]-48.0)/15.0)-1.0)
    algebraic[5] = 0.12*(states[0]+8.0)/(exp((states[0]+8.0)/5.0)-1.0)
    rates[1] = algebraic[4]*(1.0-states[1])-algebraic[5]*states[1]
    algebraic[6] = 0.17*exp((-states[0]-90.0)/20.0)
    algebraic[7] = 1.0/(1.0+exp((-states[0]-42.0)/10.0))
    rates[2] = algebraic[6]*(1.0-states[2])-algebraic[7]*states[2]
    algebraic[10] = 0.0001*(-states[0]-50.0)/(exp((-states[0]-50.0)/10.0)-1.0)
    algebraic[11] = 0.002*exp((-states[0]-90.0)/80.0)
    rates[3] = algebraic[10]*(1.0-states[3])-algebraic[11]*states[3]


def compute_variables(voi, states, rates, constants, computed_constants, algebraic):
    algebraic[1] = constants[1]*(states[0]-constants[2])
    algebraic[3] = pow(states[1], 3.0)*states[2]*constants[3]
    algebraic[0] = (algebraic[3]+0.14)*(states[0]-constants[4])
    algebraic[4] = 0.1*(-states[0]-48.0)/(exp((-states[0]-48.0)/15.0)-1.0)
    algebraic[5] = 0.12*(states[0]+8.0)/(exp((states[0]+8.0)/5.0)-1.0)
    algebraic[6] = 0.17*exp((-states[0]-90.0)/20.0)
    algebraic[7] = 1.0/(1.0+exp((-states[0]-42.0)/10.0))
    algebraic[8] = 1.2*exp((-states[0]-90.0)/50.0)+0.015*exp((states[0]+90.0)/60.0)
    algebraic[9] = 1.2*pow(states[3], 4.0)
    algebraic[2] = (algebraic[8]+algebraic[9])*(states[0]+100.0)
    algebraic[10] = 0.0001*(-states[0]-50.0)/(exp((-states[0]-50.0)/10.0)-1.0)
    algebraic[11] = 0.002*exp((-states[0]-90.0)/80.0)

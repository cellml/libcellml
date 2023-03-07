# The content of this file was generated using the Python profile of libCellML 0.4.0.

from enum import Enum
from math import *


__version__ = "0.3.2"
LIBCELLML_VERSION = "0.4.0"

STATE_COUNT = 4
VARIABLE_COUNT = 18


class VariableType(Enum):
    VARIABLE_OF_INTEGRATION = 0
    STATE = 1
    CONSTANT = 2
    COMPUTED_CONSTANT = 3
    ALGEBRAIC = 4


VOI_INFO = {"name": "time", "units": "millisecond", "component": "environment", "type": VariableType.VARIABLE_OF_INTEGRATION}

STATE_INFO = [
    {"name": "V", "units": "millivolt", "component": "membrane", "type": VariableType.STATE},
    {"name": "h", "units": "dimensionless", "component": "sodium_channel_h_gate", "type": VariableType.STATE},
    {"name": "m", "units": "dimensionless", "component": "sodium_channel_m_gate", "type": VariableType.STATE},
    {"name": "n", "units": "dimensionless", "component": "potassium_channel_n_gate", "type": VariableType.STATE}
]

VARIABLE_INFO = [
    {"name": "i_Stim", "units": "microA_per_cm2", "component": "membrane", "type": VariableType.ALGEBRAIC},
    {"name": "i_L", "units": "microA_per_cm2", "component": "leakage_current", "type": VariableType.ALGEBRAIC},
    {"name": "i_K", "units": "microA_per_cm2", "component": "potassium_channel", "type": VariableType.ALGEBRAIC},
    {"name": "i_Na", "units": "microA_per_cm2", "component": "sodium_channel", "type": VariableType.ALGEBRAIC},
    {"name": "Cm", "units": "microF_per_cm2", "component": "membrane", "type": VariableType.CONSTANT},
    {"name": "E_R", "units": "millivolt", "component": "membrane", "type": VariableType.CONSTANT},
    {"name": "E_L", "units": "millivolt", "component": "leakage_current", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "g_L", "units": "milliS_per_cm2", "component": "leakage_current", "type": VariableType.CONSTANT},
    {"name": "E_Na", "units": "millivolt", "component": "sodium_channel", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "g_Na", "units": "milliS_per_cm2", "component": "sodium_channel", "type": VariableType.CONSTANT},
    {"name": "alpha_m", "units": "per_millisecond", "component": "sodium_channel_m_gate", "type": VariableType.ALGEBRAIC},
    {"name": "beta_m", "units": "per_millisecond", "component": "sodium_channel_m_gate", "type": VariableType.ALGEBRAIC},
    {"name": "alpha_h", "units": "per_millisecond", "component": "sodium_channel_h_gate", "type": VariableType.ALGEBRAIC},
    {"name": "beta_h", "units": "per_millisecond", "component": "sodium_channel_h_gate", "type": VariableType.ALGEBRAIC},
    {"name": "E_K", "units": "millivolt", "component": "potassium_channel", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "g_K", "units": "milliS_per_cm2", "component": "potassium_channel", "type": VariableType.CONSTANT},
    {"name": "alpha_n", "units": "per_millisecond", "component": "potassium_channel_n_gate", "type": VariableType.ALGEBRAIC},
    {"name": "beta_n", "units": "per_millisecond", "component": "potassium_channel_n_gate", "type": VariableType.ALGEBRAIC}
]


def leq_func(x, y):
    return 1.0 if x <= y else 0.0


def geq_func(x, y):
    return 1.0 if x >= y else 0.0


def and_func(x, y):
    return 1.0 if bool(x) & bool(y) else 0.0


def create_states_array():
    return [nan]*STATE_COUNT


def create_variables_array():
    return [nan]*VARIABLE_COUNT


def objective_function_0(u, f, data):
    voi = data[0]
    states = data[1]
    rates = data[2]
    variables = data[3]

    variables[0] = u[0]

    f[0] = variables[0]-(-20.0 if and_func(geq_func(voi, 10.0), leq_func(voi, 10.5)) else 0.0)-0.0


def find_root_0(voi, states, rates, variables):
    u = [nan]*1

    u[0] = variables[0]

    nla_solve(objective_function_0, u, 1, (voi, states, rates, variables))

    variables[0] = u[0]


def objective_function_1(u, f, data):
    voi = data[0]
    states = data[1]
    rates = data[2]
    variables = data[3]

    variables[0] = u[0]

    f[0] = rates[0]--(-variables[0]+variables[3]+variables[2]+variables[1])/variables[4]-0.0


def find_root_1(voi, states, rates, variables):
    u = [nan]*1

    u[0] = variables[0]

    nla_solve(objective_function_1, u, 1, (voi, states, rates, variables))

    variables[0] = u[0]


def objective_function_2(u, f, data):
    voi = data[0]
    states = data[1]
    rates = data[2]
    variables = data[3]

    variables[6] = u[0]

    f[0] = variables[6]-(variables[5]-10.613)-0.0


def find_root_2(voi, states, rates, variables):
    u = [nan]*1

    u[0] = variables[6]

    nla_solve(objective_function_2, u, 1, (voi, states, rates, variables))

    variables[6] = u[0]


def objective_function_3(u, f, data):
    voi = data[0]
    states = data[1]
    rates = data[2]
    variables = data[3]

    variables[1] = u[0]

    f[0] = variables[1]-variables[7]*(states[0]-variables[6])-0.0


def find_root_3(voi, states, rates, variables):
    u = [nan]*1

    u[0] = variables[1]

    nla_solve(objective_function_3, u, 1, (voi, states, rates, variables))

    variables[1] = u[0]


def objective_function_4(u, f, data):
    voi = data[0]
    states = data[1]
    rates = data[2]
    variables = data[3]

    variables[8] = u[0]

    f[0] = variables[8]-(variables[5]-115.0)-0.0


def find_root_4(voi, states, rates, variables):
    u = [nan]*1

    u[0] = variables[8]

    nla_solve(objective_function_4, u, 1, (voi, states, rates, variables))

    variables[8] = u[0]


def objective_function_5(u, f, data):
    voi = data[0]
    states = data[1]
    rates = data[2]
    variables = data[3]

    variables[3] = u[0]

    f[0] = variables[3]-variables[9]*pow(states[2], 3.0)*states[1]*(states[0]-variables[8])-0.0


def find_root_5(voi, states, rates, variables):
    u = [nan]*1

    u[0] = variables[3]

    nla_solve(objective_function_5, u, 1, (voi, states, rates, variables))

    variables[3] = u[0]


def objective_function_6(u, f, data):
    voi = data[0]
    states = data[1]
    rates = data[2]
    variables = data[3]

    variables[10] = u[0]

    f[0] = variables[10]-0.1*(states[0]+25.0)/(exp((states[0]+25.0)/10.0)-1.0)-0.0


def find_root_6(voi, states, rates, variables):
    u = [nan]*1

    u[0] = variables[10]

    nla_solve(objective_function_6, u, 1, (voi, states, rates, variables))

    variables[10] = u[0]


def objective_function_7(u, f, data):
    voi = data[0]
    states = data[1]
    rates = data[2]
    variables = data[3]

    variables[11] = u[0]

    f[0] = variables[11]-4.0*exp(states[0]/18.0)-0.0


def find_root_7(voi, states, rates, variables):
    u = [nan]*1

    u[0] = variables[11]

    nla_solve(objective_function_7, u, 1, (voi, states, rates, variables))

    variables[11] = u[0]


def objective_function_8(u, f, data):
    voi = data[0]
    states = data[1]
    rates = data[2]
    variables = data[3]

    variables[2] = u[0]

    f[0] = rates[2]-(variables[10]*(1.0-states[2])-variables[11]*states[2])-0.0


def find_root_8(voi, states, rates, variables):
    u = [nan]*1

    u[0] = variables[2]

    nla_solve(objective_function_8, u, 1, (voi, states, rates, variables))

    variables[2] = u[0]


def objective_function_9(u, f, data):
    voi = data[0]
    states = data[1]
    rates = data[2]
    variables = data[3]

    variables[12] = u[0]

    f[0] = variables[12]-0.07*exp(states[0]/20.0)-0.0


def find_root_9(voi, states, rates, variables):
    u = [nan]*1

    u[0] = variables[12]

    nla_solve(objective_function_9, u, 1, (voi, states, rates, variables))

    variables[12] = u[0]


def objective_function_10(u, f, data):
    voi = data[0]
    states = data[1]
    rates = data[2]
    variables = data[3]

    variables[13] = u[0]

    f[0] = variables[13]-1.0/(exp((states[0]+30.0)/10.0)+1.0)-0.0


def find_root_10(voi, states, rates, variables):
    u = [nan]*1

    u[0] = variables[13]

    nla_solve(objective_function_10, u, 1, (voi, states, rates, variables))

    variables[13] = u[0]


def objective_function_11(u, f, data):
    voi = data[0]
    states = data[1]
    rates = data[2]
    variables = data[3]

    variables[1] = u[0]

    f[0] = rates[1]-(variables[12]*(1.0-states[1])-variables[13]*states[1])-0.0


def find_root_11(voi, states, rates, variables):
    u = [nan]*1

    u[0] = variables[1]

    nla_solve(objective_function_11, u, 1, (voi, states, rates, variables))

    variables[1] = u[0]


def objective_function_12(u, f, data):
    voi = data[0]
    states = data[1]
    rates = data[2]
    variables = data[3]

    variables[14] = u[0]

    f[0] = variables[14]-(variables[5]+12.0)-0.0


def find_root_12(voi, states, rates, variables):
    u = [nan]*1

    u[0] = variables[14]

    nla_solve(objective_function_12, u, 1, (voi, states, rates, variables))

    variables[14] = u[0]


def objective_function_13(u, f, data):
    voi = data[0]
    states = data[1]
    rates = data[2]
    variables = data[3]

    variables[2] = u[0]

    f[0] = variables[2]-variables[15]*pow(states[3], 4.0)*(states[0]-variables[14])-0.0


def find_root_13(voi, states, rates, variables):
    u = [nan]*1

    u[0] = variables[2]

    nla_solve(objective_function_13, u, 1, (voi, states, rates, variables))

    variables[2] = u[0]


def objective_function_14(u, f, data):
    voi = data[0]
    states = data[1]
    rates = data[2]
    variables = data[3]

    variables[16] = u[0]

    f[0] = variables[16]-0.01*(states[0]+10.0)/(exp((states[0]+10.0)/10.0)-1.0)-0.0


def find_root_14(voi, states, rates, variables):
    u = [nan]*1

    u[0] = variables[16]

    nla_solve(objective_function_14, u, 1, (voi, states, rates, variables))

    variables[16] = u[0]


def objective_function_15(u, f, data):
    voi = data[0]
    states = data[1]
    rates = data[2]
    variables = data[3]

    variables[17] = u[0]

    f[0] = variables[17]-0.125*exp(states[0]/80.0)-0.0


def find_root_15(voi, states, rates, variables):
    u = [nan]*1

    u[0] = variables[17]

    nla_solve(objective_function_15, u, 1, (voi, states, rates, variables))

    variables[17] = u[0]


def objective_function_16(u, f, data):
    voi = data[0]
    states = data[1]
    rates = data[2]
    variables = data[3]

    variables[3] = u[0]

    f[0] = rates[3]-(variables[16]*(1.0-states[3])-variables[17]*states[3])-0.0


def find_root_16(voi, states, rates, variables):
    u = [nan]*1

    u[0] = variables[3]

    nla_solve(objective_function_16, u, 1, (voi, states, rates, variables))

    variables[3] = u[0]


def initialise_variables(states, variables):
    variables[4] = 1.0
    variables[5] = 0.0
    variables[7] = 0.3
    variables[9] = 120.0
    variables[15] = 36.0
    states[0] = 0.0
    states[1] = 0.6
    states[2] = 0.05
    states[3] = 0.325


def compute_computed_constants(variables):
    pass


def compute_rates(voi, states, rates, variables):
    pass


def compute_variables(voi, states, rates, variables):
    find_root_0(voi, states, rates, variables)
    find_root_1(voi, states, rates, variables)
    find_root_2(voi, states, rates, variables)
    find_root_3(voi, states, rates, variables)
    find_root_4(voi, states, rates, variables)
    find_root_5(voi, states, rates, variables)
    find_root_6(voi, states, rates, variables)
    find_root_7(voi, states, rates, variables)
    find_root_8(voi, states, rates, variables)
    find_root_9(voi, states, rates, variables)
    find_root_10(voi, states, rates, variables)
    find_root_11(voi, states, rates, variables)
    find_root_12(voi, states, rates, variables)
    find_root_13(voi, states, rates, variables)
    find_root_14(voi, states, rates, variables)
    find_root_15(voi, states, rates, variables)
    find_root_16(voi, states, rates, variables)

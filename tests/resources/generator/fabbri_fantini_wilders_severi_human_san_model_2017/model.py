# The content of this file was generated using the Python profile of libCellML 0.6.3.

from enum import Enum
from math import *


__version__ = "0.5.0"
LIBCELLML_VERSION = "0.6.3"

STATE_COUNT = 33
CONSTANT_COUNT = 91
COMPUTED_CONSTANT_COUNT = 25
ALGEBRAIC_VARIABLE_COUNT = 101

VOI_INFO = {"name": "time", "units": "second", "component": "environment"}

STATE_INFO = [
    {"name": "Ca_sub", "units": "millimolar", "component": "Ca_dynamics"},
    {"name": "Nai_", "units": "millimolar", "component": "Nai_concentration"},
    {"name": "Ca_jsr", "units": "millimolar", "component": "Ca_dynamics"},
    {"name": "O", "units": "dimensionless", "component": "Ca_SR_release"},
    {"name": "R", "units": "dimensionless", "component": "Ca_SR_release"},
    {"name": "RI", "units": "dimensionless", "component": "Ca_SR_release"},
    {"name": "I", "units": "dimensionless", "component": "Ca_SR_release"},
    {"name": "Cai", "units": "millimolar", "component": "Ca_dynamics"},
    {"name": "Ca_nsr", "units": "millimolar", "component": "Ca_dynamics"},
    {"name": "fTC", "units": "dimensionless", "component": "Ca_buffering"},
    {"name": "fTMC", "units": "dimensionless", "component": "Ca_buffering"},
    {"name": "fTMM", "units": "dimensionless", "component": "Ca_buffering"},
    {"name": "fCMi", "units": "dimensionless", "component": "Ca_buffering"},
    {"name": "fCMs", "units": "dimensionless", "component": "Ca_buffering"},
    {"name": "fCQ", "units": "dimensionless", "component": "Ca_buffering"},
    {"name": "V_ode", "units": "millivolt", "component": "Membrane"},
    {"name": "y", "units": "dimensionless", "component": "i_f_y_gate"},
    {"name": "h", "units": "dimensionless", "component": "i_Na_h_gate"},
    {"name": "m", "units": "dimensionless", "component": "i_Na_m_gate"},
    {"name": "s_Kur", "units": "dimensionless", "component": "i_Kur_sKur_gate"},
    {"name": "r_Kur", "units": "dimensionless", "component": "i_Kur_rKur_gate"},
    {"name": "fCa", "units": "dimensionless", "component": "i_CaL_fCa_gate"},
    {"name": "fL", "units": "dimensionless", "component": "i_CaL_fL_gate"},
    {"name": "dL", "units": "dimensionless", "component": "i_CaL_dL_gate"},
    {"name": "fT", "units": "dimensionless", "component": "i_CaT_fT_gate"},
    {"name": "dT", "units": "dimensionless", "component": "i_CaT_dT_gate"},
    {"name": "r", "units": "dimensionless", "component": "i_to_r_gate"},
    {"name": "q", "units": "dimensionless", "component": "i_to_q_gate"},
    {"name": "piy", "units": "dimensionless", "component": "i_Kr_pi_gate"},
    {"name": "paS", "units": "dimensionless", "component": "i_Kr_pa_gate"},
    {"name": "paF", "units": "dimensionless", "component": "i_Kr_pa_gate"},
    {"name": "n", "units": "dimensionless", "component": "i_Ks_n_gate"},
    {"name": "a", "units": "dimensionless", "component": "i_KACh_a_gate"}
]

CONSTANT_INFO = [
    {"name": "ACh", "units": "millimolar", "component": "Rate_modulation_experiments"},
    {"name": "Iso_1_uM", "units": "dimensionless", "component": "Rate_modulation_experiments"},
    {"name": "Nao", "units": "millimolar", "component": "Ionic_values"},
    {"name": "Ki", "units": "millimolar", "component": "Ionic_values"},
    {"name": "Ko", "units": "millimolar", "component": "Ionic_values"},
    {"name": "Cao", "units": "millimolar", "component": "Ionic_values"},
    {"name": "F", "units": "coulomb_per_mole", "component": "Membrane"},
    {"name": "Nai_clamp", "units": "dimensionless", "component": "Nai_concentration"},
    {"name": "Km_Nap", "units": "millimolar", "component": "i_NaK"},
    {"name": "Km_Kp", "units": "millimolar", "component": "i_NaK"},
    {"name": "i_NaK_max", "units": "nanoA", "component": "i_NaK"},
    {"name": "K_NaCa", "units": "nanoA", "component": "i_NaCa"},
    {"name": "blockade_NaCa", "units": "dimensionless", "component": "i_NaCa"},
    {"name": "K3ni", "units": "millimolar", "component": "i_NaCa"},
    {"name": "Qci", "units": "dimensionless", "component": "i_NaCa"},
    {"name": "Kci", "units": "millimolar", "component": "i_NaCa"},
    {"name": "Qn", "units": "dimensionless", "component": "i_NaCa"},
    {"name": "K2ni", "units": "millimolar", "component": "i_NaCa"},
    {"name": "K1ni", "units": "millimolar", "component": "i_NaCa"},
    {"name": "Kcni", "units": "millimolar", "component": "i_NaCa"},
    {"name": "K3no", "units": "millimolar", "component": "i_NaCa"},
    {"name": "Qco", "units": "dimensionless", "component": "i_NaCa"},
    {"name": "Kco", "units": "millimolar", "component": "i_NaCa"},
    {"name": "K2no", "units": "millimolar", "component": "i_NaCa"},
    {"name": "K1no", "units": "millimolar", "component": "i_NaCa"},
    {"name": "ks", "units": "per_second", "component": "Ca_SR_release"},
    {"name": "HSR", "units": "dimensionless", "component": "Ca_SR_release"},
    {"name": "EC50_SR", "units": "millimolar", "component": "Ca_SR_release"},
    {"name": "MinSR", "units": "dimensionless", "component": "Ca_SR_release"},
    {"name": "MaxSR", "units": "dimensionless", "component": "Ca_SR_release"},
    {"name": "koCa", "units": "per_millimolar2_second", "component": "Ca_SR_release"},
    {"name": "kiCa", "units": "per_millimolar_second", "component": "Ca_SR_release"},
    {"name": "kom", "units": "per_second", "component": "Ca_SR_release"},
    {"name": "kim", "units": "per_second", "component": "Ca_SR_release"},
    {"name": "P_up_basal", "units": "millimolar_per_second", "component": "Ca_intracellular_fluxes"},
    {"name": "tau_dif_Ca", "units": "second", "component": "Ca_intracellular_fluxes"},
    {"name": "slope_up", "units": "millimolar", "component": "Ca_intracellular_fluxes"},
    {"name": "K_up", "units": "millimolar", "component": "Ca_intracellular_fluxes"},
    {"name": "tau_tr", "units": "second", "component": "Ca_intracellular_fluxes"},
    {"name": "kb_TC", "units": "per_second", "component": "Ca_buffering"},
    {"name": "kf_TC", "units": "per_millimolar_second", "component": "Ca_buffering"},
    {"name": "kb_TMC", "units": "per_second", "component": "Ca_buffering"},
    {"name": "kf_TMC", "units": "per_millimolar_second", "component": "Ca_buffering"},
    {"name": "kb_TMM", "units": "per_second", "component": "Ca_buffering"},
    {"name": "Mgi", "units": "millimolar", "component": "Ca_buffering"},
    {"name": "kf_TMM", "units": "per_millimolar_second", "component": "Ca_buffering"},
    {"name": "kb_CM", "units": "per_second", "component": "Ca_buffering"},
    {"name": "kf_CM", "units": "per_millimolar_second", "component": "Ca_buffering"},
    {"name": "kb_CQ", "units": "per_second", "component": "Ca_buffering"},
    {"name": "kf_CQ", "units": "per_millimolar_second", "component": "Ca_buffering"},
    {"name": "TC_tot", "units": "millimolar", "component": "Ca_buffering"},
    {"name": "TMC_tot", "units": "millimolar", "component": "Ca_buffering"},
    {"name": "CM_tot", "units": "millimolar", "component": "Ca_buffering"},
    {"name": "CQ_tot", "units": "millimolar", "component": "Ca_buffering"},
    {"name": "L_cell", "units": "micrometre", "component": "Cell_parameters"},
    {"name": "R_cell", "units": "micrometre", "component": "Cell_parameters"},
    {"name": "L_sub", "units": "micrometre", "component": "Cell_parameters"},
    {"name": "V_jsr_part", "units": "dimensionless", "component": "Cell_parameters"},
    {"name": "V_i_part", "units": "dimensionless", "component": "Cell_parameters"},
    {"name": "V_nsr_part", "units": "dimensionless", "component": "Cell_parameters"},
    {"name": "C", "units": "microF", "component": "Membrane"},
    {"name": "T", "units": "kelvin", "component": "Membrane"},
    {"name": "R", "units": "joule_per_kilomole_kelvin", "component": "Membrane"},
    {"name": "clamp_mode", "units": "dimensionless", "component": "Membrane"},
    {"name": "V_test", "units": "millivolt", "component": "Voltage_clamp"},
    {"name": "t_test", "units": "second", "component": "Voltage_clamp"},
    {"name": "t_holding", "units": "second", "component": "Voltage_clamp"},
    {"name": "V_holding", "units": "millivolt", "component": "Voltage_clamp"},
    {"name": "Km_f", "units": "millimolar", "component": "i_f"},
    {"name": "g_f", "units": "microS", "component": "i_f"},
    {"name": "alpha", "units": "dimensionless", "component": "i_f"},
    {"name": "blockade", "units": "dimensionless", "component": "i_f"},
    {"name": "y_shift", "units": "millivolt", "component": "i_f_y_gate"},
    {"name": "g_Na", "units": "microS", "component": "i_Na"},
    {"name": "g_Na_L", "units": "microS", "component": "i_Na"},
    {"name": "delta_m", "units": "millivolt", "component": "i_Na_m_gate"},
    {"name": "g_Kur", "units": "microS", "component": "i_Kur"},
    {"name": "P_CaL", "units": "nanoA_per_millimolar", "component": "i_CaL"},
    {"name": "k_dL", "units": "millivolt", "component": "i_CaL_dL_gate"},
    {"name": "V_dL", "units": "millivolt", "component": "i_CaL_dL_gate"},
    {"name": "k_fL", "units": "millivolt", "component": "i_CaL_fL_gate"},
    {"name": "shift_fL", "units": "millivolt", "component": "i_CaL_fL_gate"},
    {"name": "Km_fCa", "units": "millimolar", "component": "i_CaL_fCa_gate"},
    {"name": "alpha_fCa", "units": "per_second", "component": "i_CaL_fCa_gate"},
    {"name": "P_CaT", "units": "nanoA_per_millimolar", "component": "i_CaT"},
    {"name": "offset_fT", "units": "second", "component": "i_CaT_fT_gate"},
    {"name": "g_to", "units": "microS", "component": "i_to"},
    {"name": "g_Kr", "units": "microS", "component": "i_Kr"},
    {"name": "g_Ks_", "units": "microS", "component": "i_Ks"},
    {"name": "g_KACh", "units": "microS", "component": "i_KACh"},
    {"name": "ACh_on", "units": "dimensionless", "component": "i_KACh"}
]

COMPUTED_CONSTANT_INFO = [
    {"name": "RTONF", "units": "millivolt", "component": "Membrane"},
    {"name": "E_K", "units": "millivolt", "component": "Ionic_values"},
    {"name": "V_sub", "units": "millimetre3", "component": "Cell_parameters"},
    {"name": "V_i", "units": "millimetre3", "component": "Cell_parameters"},
    {"name": "Iso_increase", "units": "dimensionless", "component": "i_NaK"},
    {"name": "k34", "units": "dimensionless", "component": "i_NaCa"},
    {"name": "b_up", "units": "dimensionless", "component": "Ca_intracellular_fluxes"},
    {"name": "P_up", "units": "millimolar_per_second", "component": "Ca_intracellular_fluxes"},
    {"name": "V_nsr", "units": "millimetre3", "component": "Cell_parameters"},
    {"name": "V_jsr", "units": "millimetre3", "component": "Cell_parameters"},
    {"name": "V_cell", "units": "millimetre3", "component": "Cell_parameters"},
    {"name": "G_f", "units": "microS", "component": "i_f"},
    {"name": "G_f_K", "units": "microS", "component": "i_f"},
    {"name": "G_f_Na", "units": "microS", "component": "i_f"},
    {"name": "g_f_Na", "units": "microS", "component": "i_f"},
    {"name": "g_f_K", "units": "microS", "component": "i_f"},
    {"name": "ACh_shift", "units": "millivolt", "component": "i_f_y_gate"},
    {"name": "Iso_shift", "units": "millivolt", "component": "i_f_y_gate"},
    {"name": "Iso_increase", "units": "dimensionless", "component": "i_CaL"},
    {"name": "ACh_block", "units": "dimensionless", "component": "i_CaL"},
    {"name": "Iso_shift_dL", "units": "millivolt", "component": "i_CaL_dL_gate"},
    {"name": "Iso_slope_dL", "units": "dimensionless", "component": "i_CaL_dL_gate"},
    {"name": "g_Ks", "units": "microS", "component": "i_Ks"},
    {"name": "Iso_shift", "units": "millivolt", "component": "i_Ks_n_gate"},
    {"name": "alpha_a", "units": "per_second", "component": "i_KACh_a_gate"}
]

ALGEBRAIC_INFO = [
    {"name": "Nai", "units": "millimolar", "component": "Nai_concentration"},
    {"name": "E_Na", "units": "millivolt", "component": "Ionic_values"},
    {"name": "E_Ca", "units": "millivolt", "component": "Ionic_values"},
    {"name": "i_NaCa", "units": "nanoA", "component": "i_NaCa"},
    {"name": "i_NaK", "units": "nanoA", "component": "i_NaK"},
    {"name": "i_siNa", "units": "nanoA", "component": "i_CaL"},
    {"name": "i_fNa", "units": "nanoA", "component": "i_f"},
    {"name": "i_Na", "units": "nanoA", "component": "i_Na"},
    {"name": "V", "units": "millivolt", "component": "Membrane"},
    {"name": "x4", "units": "dimensionless", "component": "i_NaCa"},
    {"name": "x3", "units": "dimensionless", "component": "i_NaCa"},
    {"name": "x2", "units": "dimensionless", "component": "i_NaCa"},
    {"name": "x1", "units": "dimensionless", "component": "i_NaCa"},
    {"name": "k12", "units": "dimensionless", "component": "i_NaCa"},
    {"name": "k21", "units": "dimensionless", "component": "i_NaCa"},
    {"name": "k41", "units": "dimensionless", "component": "i_NaCa"},
    {"name": "k43", "units": "dimensionless", "component": "i_NaCa"},
    {"name": "k32", "units": "dimensionless", "component": "i_NaCa"},
    {"name": "k23", "units": "dimensionless", "component": "i_NaCa"},
    {"name": "k14", "units": "dimensionless", "component": "i_NaCa"},
    {"name": "di", "units": "dimensionless", "component": "i_NaCa"},
    {"name": "do", "units": "dimensionless", "component": "i_NaCa"},
    {"name": "j_SRCarel", "units": "millimolar_per_second", "component": "Ca_SR_release"},
    {"name": "diff", "units": "millimolar", "component": "Ca_SR_release"},
    {"name": "kCaSR", "units": "dimensionless", "component": "Ca_SR_release"},
    {"name": "koSRCa", "units": "per_millimolar2_second", "component": "Ca_SR_release"},
    {"name": "kiSRCa", "units": "per_millimolar_second", "component": "Ca_SR_release"},
    {"name": "P_tot", "units": "dimensionless", "component": "Ca_SR_release"},
    {"name": "j_Ca_dif", "units": "millimolar_per_second", "component": "Ca_intracellular_fluxes"},
    {"name": "j_up", "units": "millimolar_per_second", "component": "Ca_intracellular_fluxes"},
    {"name": "j_tr", "units": "millimolar_per_second", "component": "Ca_intracellular_fluxes"},
    {"name": "delta_fTC", "units": "per_second", "component": "Ca_buffering"},
    {"name": "delta_fTMC", "units": "per_second", "component": "Ca_buffering"},
    {"name": "delta_fTMM", "units": "per_second", "component": "Ca_buffering"},
    {"name": "delta_fCMi", "units": "per_second", "component": "Ca_buffering"},
    {"name": "delta_fCMs", "units": "per_second", "component": "Ca_buffering"},
    {"name": "delta_fCQ", "units": "per_second", "component": "Ca_buffering"},
    {"name": "i_CaT", "units": "nanoA", "component": "i_CaT"},
    {"name": "i_siCa", "units": "nanoA", "component": "i_CaL"},
    {"name": "i_Kur", "units": "nanoA", "component": "i_Kur"},
    {"name": "i_KACh", "units": "nanoA", "component": "i_KACh"},
    {"name": "i_CaL", "units": "nanoA", "component": "i_CaL"},
    {"name": "i_to", "units": "nanoA", "component": "i_to"},
    {"name": "i_Ks", "units": "nanoA", "component": "i_Ks"},
    {"name": "i_Kr", "units": "nanoA", "component": "i_Kr"},
    {"name": "i_f", "units": "nanoA", "component": "i_f"},
    {"name": "i_tot", "units": "nanoA", "component": "Membrane"},
    {"name": "V_clamp", "units": "millivolt", "component": "Voltage_clamp"},
    {"name": "i_fK", "units": "nanoA", "component": "i_f"},
    {"name": "tau_y", "units": "second", "component": "i_f_y_gate"},
    {"name": "y_infinity", "units": "dimensionless", "component": "i_f_y_gate"},
    {"name": "E_mh", "units": "millivolt", "component": "i_Na"},
    {"name": "i_Na_", "units": "nanoA", "component": "i_Na"},
    {"name": "i_Na_L", "units": "nanoA", "component": "i_Na"},
    {"name": "m_infinity", "units": "dimensionless", "component": "i_Na_m_gate"},
    {"name": "E0_m", "units": "millivolt", "component": "i_Na_m_gate"},
    {"name": "alpha_m", "units": "per_second", "component": "i_Na_m_gate"},
    {"name": "beta_m", "units": "per_second", "component": "i_Na_m_gate"},
    {"name": "tau_m", "units": "second", "component": "i_Na_m_gate"},
    {"name": "h_infinity", "units": "dimensionless", "component": "i_Na_h_gate"},
    {"name": "alpha_h", "units": "per_second", "component": "i_Na_h_gate"},
    {"name": "beta_h", "units": "per_second", "component": "i_Na_h_gate"},
    {"name": "tau_h", "units": "second", "component": "i_Na_h_gate"},
    {"name": "tau_r_Kur", "units": "second", "component": "i_Kur_rKur_gate"},
    {"name": "r_Kur_infinity", "units": "dimensionless", "component": "i_Kur_rKur_gate"},
    {"name": "tau_s_Kur", "units": "second", "component": "i_Kur_sKur_gate"},
    {"name": "s_Kur_infinity", "units": "dimensionless", "component": "i_Kur_sKur_gate"},
    {"name": "i_siK", "units": "nanoA", "component": "i_CaL"},
    {"name": "dL_infinity", "units": "dimensionless", "component": "i_CaL_dL_gate"},
    {"name": "beta_dL", "units": "per_second", "component": "i_CaL_dL_gate"},
    {"name": "alpha_dL", "units": "per_second", "component": "i_CaL_dL_gate"},
    {"name": "tau_dL", "units": "second", "component": "i_CaL_dL_gate"},
    {"name": "adVm", "units": "millivolt", "component": "i_CaL_dL_gate"},
    {"name": "bdVm", "units": "millivolt", "component": "i_CaL_dL_gate"},
    {"name": "fL_infinity", "units": "dimensionless", "component": "i_CaL_fL_gate"},
    {"name": "tau_fL", "units": "second", "component": "i_CaL_fL_gate"},
    {"name": "fCa_infinity", "units": "dimensionless", "component": "i_CaL_fCa_gate"},
    {"name": "tau_fCa", "units": "second", "component": "i_CaL_fCa_gate"},
    {"name": "dT_infinity", "units": "dimensionless", "component": "i_CaT_dT_gate"},
    {"name": "tau_dT", "units": "second", "component": "i_CaT_dT_gate"},
    {"name": "fT_infinity", "units": "dimensionless", "component": "i_CaT_fT_gate"},
    {"name": "tau_fT", "units": "second", "component": "i_CaT_fT_gate"},
    {"name": "q_infinity", "units": "dimensionless", "component": "i_to_q_gate"},
    {"name": "tau_q", "units": "second", "component": "i_to_q_gate"},
    {"name": "r_infinity", "units": "dimensionless", "component": "i_to_r_gate"},
    {"name": "tau_r", "units": "second", "component": "i_to_r_gate"},
    {"name": "alfapaF", "units": "per_second", "component": "i_Kr_pa_gate"},
    {"name": "betapaF", "units": "per_second", "component": "i_Kr_pa_gate"},
    {"name": "pa_infinity", "units": "dimensionless", "component": "i_Kr_pa_gate"},
    {"name": "tau_paS", "units": "second", "component": "i_Kr_pa_gate"},
    {"name": "tau_paF", "units": "second", "component": "i_Kr_pa_gate"},
    {"name": "tau_pi", "units": "second", "component": "i_Kr_pi_gate"},
    {"name": "pi_infinity", "units": "dimensionless", "component": "i_Kr_pi_gate"},
    {"name": "E_Ks", "units": "millivolt", "component": "i_Ks"},
    {"name": "n_infinity", "units": "dimensionless", "component": "i_Ks_n_gate"},
    {"name": "beta_n", "units": "per_second", "component": "i_Ks_n_gate"},
    {"name": "alpha_n", "units": "per_second", "component": "i_Ks_n_gate"},
    {"name": "tau_n", "units": "second", "component": "i_Ks_n_gate"},
    {"name": "beta_a", "units": "per_second", "component": "i_KACh_a_gate"},
    {"name": "a_infinity", "units": "dimensionless", "component": "i_KACh_a_gate"},
    {"name": "tau_a", "units": "second", "component": "i_KACh_a_gate"}
]


def eq_func(x, y):
    return 1.0 if x == y else 0.0


def lt_func(x, y):
    return 1.0 if x < y else 0.0


def gt_func(x, y):
    return 1.0 if x > y else 0.0


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


def create_algebraic_variables_array():
    return [nan]*ALGEBRAIC_VARIABLE_COUNT


def initialise_arrays(states, rates, constants, computed_constants, algebraic_variables):
    states[0] = 6.226104e-5
    states[1] = 5.0
    states[2] = 0.409551
    states[3] = 6.181512e-9
    states[4] = 0.9308
    states[5] = 0.069199
    states[6] = 4.595622e-10
    states[7] = 9.15641e-6
    states[8] = 0.435148
    states[9] = 0.017929
    states[10] = 0.259947
    states[11] = 0.653777
    states[12] = 0.217311
    states[13] = 0.158521
    states[14] = 0.138975
    states[15] = -47.787168
    states[16] = 0.009508
    states[17] = 0.003058
    states[18] = 0.447724
    states[19] = 0.845304
    states[20] = 0.011845
    states[21] = 0.844449
    states[22] = 0.846702
    states[23] = 0.001921
    states[24] = 0.020484
    states[25] = 0.268909
    states[26] = 0.014523
    states[27] = 0.430836
    states[28] = 0.709051
    states[29] = 0.283185
    states[30] = 0.011068
    states[31] = 0.1162
    states[32] = 0.00277
    constants[0] = 0.0
    constants[1] = 0.0
    constants[2] = 140.0
    constants[3] = 140.0
    constants[4] = 5.4
    constants[5] = 1.8
    constants[6] = 96485.3415
    constants[7] = 1.0
    constants[8] = 14.0
    constants[9] = 1.4
    constants[10] = 0.08105
    constants[11] = 3.343
    constants[12] = 0.0
    constants[13] = 26.44
    constants[14] = 0.1369
    constants[15] = 0.0207
    constants[16] = 0.4315
    constants[17] = 2.289
    constants[18] = 395.3
    constants[19] = 26.44
    constants[20] = 4.663
    constants[21] = 0.0
    constants[22] = 3.663
    constants[23] = 561.4
    constants[24] = 1628.0
    constants[25] = 148041085.1
    constants[26] = 2.5
    constants[27] = 0.45
    constants[28] = 1.0
    constants[29] = 15.0
    constants[30] = 10000.0
    constants[31] = 500.0
    constants[32] = 660.0
    constants[33] = 5.0
    constants[34] = 5.0
    constants[35] = 5.469e-5
    constants[36] = 5.0e-5
    constants[37] = 0.000286113
    constants[38] = 0.04
    constants[39] = 446.0
    constants[40] = 88800.0
    constants[41] = 7.51
    constants[42] = 227700.0
    constants[43] = 751.0
    constants[44] = 2.5
    constants[45] = 2277.0
    constants[46] = 542.0
    constants[47] = 1.642e6
    constants[48] = 445.0
    constants[49] = 175.4
    constants[50] = 0.031
    constants[51] = 0.062
    constants[52] = 0.045
    constants[53] = 10.0
    constants[54] = 67.0
    constants[55] = 3.9
    constants[56] = 0.02
    constants[57] = 0.0012
    constants[58] = 0.46
    constants[59] = 0.0116
    constants[60] = 5.7e-5
    constants[61] = 310.0
    constants[62] = 8314.472
    constants[63] = 0.0
    constants[64] = -35.0
    constants[65] = 0.5
    constants[66] = 0.5
    constants[67] = -45.0
    constants[68] = 45.0
    constants[69] = 0.00427
    constants[70] = 0.5927
    constants[71] = 0.0
    constants[72] = 0.0
    constants[73] = 0.0223
    constants[74] = 0.0
    constants[75] = 1.0e-5
    constants[76] = 0.1539e-3
    constants[77] = 0.4578
    constants[78] = 4.3371
    constants[79] = -16.4508
    constants[80] = 0.0
    constants[81] = 0.0
    constants[82] = 0.000338
    constants[83] = 0.0075
    constants[84] = 0.04132
    constants[85] = 0.0
    constants[86] = 3.5e-3
    constants[87] = 0.00424
    constants[88] = 0.00065
    constants[89] = 0.00345
    constants[90] = 1.0


def compute_computed_constants(constants, computed_constants):
    computed_constants[0] = constants[62]*constants[61]/constants[6]
    computed_constants[1] = computed_constants[0]*log(constants[4]/constants[3])
    computed_constants[4] = 1.2 if gt_func(constants[1], 0.0) else 1.0
    computed_constants[5] = constants[2]/(constants[20]+constants[2])
    computed_constants[6] = -0.25 if gt_func(constants[1], 0.0) else 0.7*constants[0]/(0.00009+constants[0]) if gt_func(constants[0], 0.0) else 0.0
    computed_constants[7] = constants[34]*(1.0-computed_constants[6])
    computed_constants[10] = 0.000000001*3.14159265358979*pow(constants[55], 2.0)*constants[54]
    computed_constants[2] = 0.000000001*2.0*3.14159265358979*constants[56]*(constants[55]-constants[56]/2.0)*constants[54]
    computed_constants[9] = constants[57]*computed_constants[10]
    computed_constants[3] = constants[58]*computed_constants[10]-computed_constants[2]
    computed_constants[8] = constants[59]*computed_constants[10]
    computed_constants[11] = constants[69]/(constants[4]/(constants[4]+constants[68]))
    computed_constants[12] = computed_constants[11]/(constants[70]+1.0)
    computed_constants[13] = constants[70]*computed_constants[12]
    computed_constants[14] = computed_constants[13]*constants[4]/(constants[4]+constants[68])
    computed_constants[15] = computed_constants[12]*constants[4]/(constants[4]+constants[68])
    computed_constants[16] = -1.0-9.898*pow(1.0*constants[0], 0.618)/(pow(1.0*constants[0], 0.618)+0.00122423) if gt_func(constants[0], 0.0) else 0.0
    computed_constants[17] = 7.5 if gt_func(constants[1], 0.0) else 0.0
    computed_constants[18] = 1.23 if gt_func(constants[1], 0.0) else 1.0
    computed_constants[19] = 0.31*constants[0]/(constants[0]+0.00009)
    computed_constants[20] = -8.0 if gt_func(constants[1], 0.0) else 0.0
    computed_constants[21] = -27.0 if gt_func(constants[1], 0.0) else 0.0
    computed_constants[22] = 1.2*constants[88] if gt_func(constants[1], 0.0) else constants[88]
    computed_constants[23] = -14.0 if gt_func(constants[1], 0.0) else 0.0
    computed_constants[24] = (3.5988-0.025641)/(1.0+0.0000012155/pow(1.0*constants[0], 1.6951))+0.025641


def compute_rates(voi, states, rates, constants, computed_constants, algebraic_variables):
    algebraicVariables[0] = states[1]
    algebraicVariables[47] = constants[64] if and_func(gt_func(voi, constants[66]), lt_func(voi, constants[66]+constants[65])) else constants[67]
    algebraicVariables[8] = algebraicVariables[47] if geq_func(constants[63], 1.0) else states[15]
    algebraicVariables[5] = 0.0000185*constants[77]*(algebraicVariables[8]-0.0)/(computed_constants[0]*(1.0-exp(-1.0*(algebraicVariables[8]-0.0)/computed_constants[0])))*(algebraicVariables[0]-constants[2]*exp(-1.0*(algebraicVariables[8]-0.0)/computed_constants[0]))*states[23]*states[22]*states[21]
    algebraicVariables[1] = computed_constants[0]*log(constants[2]/algebraicVariables[0])
    algebraicVariables[6] = states[16]*computed_constants[14]*(algebraicVariables[8]-algebraicVariables[1])*(1.0-constants[71])
    algebraicVariables[51] = computed_constants[0]*log((constants[2]+0.12*constants[4])/(algebraicVariables[0]+0.12*constants[3]))
    algebraicVariables[53] = constants[74]*pow(states[18], 3.0)*(algebraicVariables[8]-algebraicVariables[51])
    algebraicVariables[52] = constants[73]*pow(states[18], 3.0)*states[17]*(algebraicVariables[8]-algebraicVariables[51])
    algebraicVariables[7] = algebraicVariables[52]+algebraicVariables[53]
    algebraicVariables[4] = computed_constants[4]*constants[10]*pow(1.0+pow(constants[9]/constants[4], 1.2), -1.0)*pow(1.0+pow(constants[8]/algebraicVariables[0], 1.3), -1.0)*pow(1.0+exp(-(algebraicVariables[8]-algebraicVariables[1]+110.0)/20.0), -1.0)
    algebraicVariables[20] = 1.0+states[0]/constants[15]*(1.0+exp(-constants[14]*algebraicVariables[8]/computed_constants[0])+algebraicVariables[0]/constants[19])+algebraicVariables[0]/constants[18]*(1.0+algebraicVariables[0]/constants[17]*(1.0+algebraicVariables[0]/constants[13]))
    algebraicVariables[13] = states[0]/constants[15]*exp(-constants[14]*algebraicVariables[8]/computed_constants[0])/algebraicVariables[20]
    algebraicVariables[21] = 1.0+constants[5]/constants[22]*(1.0+exp(constants[21]*algebraicVariables[8]/computed_constants[0]))+constants[2]/constants[24]*(1.0+constants[2]/constants[23]*(1.0+constants[2]/constants[20]))
    algebraicVariables[14] = constants[5]/constants[22]*exp(constants[21]*algebraicVariables[8]/computed_constants[0])/algebraicVariables[21]
    algebraicVariables[17] = exp(constants[16]*algebraicVariables[8]/(2.0*computed_constants[0]))
    algebraicVariables[19] = algebraicVariables[0]/constants[18]*algebraicVariables[0]/constants[17]*(1.0+algebraicVariables[0]/constants[13])*exp(constants[16]*algebraicVariables[8]/(2.0*computed_constants[0]))/algebraicVariables[20]
    algebraicVariables[18] = constants[2]/constants[24]*constants[2]/constants[23]*(1.0+constants[2]/constants[20])*exp(-constants[16]*algebraicVariables[8]/(2.0*computed_constants[0]))/algebraicVariables[21]
    algebraicVariables[9] = algebraicVariables[18]*computed_constants[5]*(algebraicVariables[19]+algebraicVariables[13])+algebraicVariables[19]*algebraicVariables[14]*(computed_constants[5]+algebraicVariables[17])
    algebraicVariables[16] = algebraicVariables[0]/(constants[13]+algebraicVariables[0])
    algebraicVariables[15] = exp(-constants[16]*algebraicVariables[8]/(2.0*computed_constants[0]))
    algebraicVariables[10] = algebraicVariables[19]*algebraicVariables[16]*(algebraicVariables[18]+algebraicVariables[14])+algebraicVariables[13]*algebraicVariables[18]*(algebraicVariables[16]+algebraicVariables[15])
    algebraicVariables[11] = algebraicVariables[17]*algebraicVariables[16]*(algebraicVariables[19]+algebraicVariables[13])+algebraicVariables[15]*algebraicVariables[13]*(computed_constants[5]+algebraicVariables[17])
    algebraicVariables[12] = algebraicVariables[15]*computed_constants[5]*(algebraicVariables[18]+algebraicVariables[14])+algebraicVariables[14]*algebraicVariables[17]*(algebraicVariables[16]+algebraicVariables[15])
    algebraicVariables[3] = (1.0-constants[12])*constants[11]*(algebraicVariables[11]*algebraicVariables[14]-algebraicVariables[12]*algebraicVariables[13])/(algebraicVariables[12]+algebraicVariables[11]+algebraicVariables[10]+algebraicVariables[9])
    rates[1] = (1.0-constants[7])*-1.0*(algebraicVariables[7]+algebraicVariables[6]+algebraicVariables[5]+3.0*algebraicVariables[4]+3.0*algebraicVariables[3])/(1.0*(computed_constants[3]+computed_constants[2])*constants[6])
    algebraicVariables[24] = constants[29]-(constants[29]-constants[28])/(1.0+pow(constants[27]/states[2], constants[26]))
    algebraicVariables[25] = constants[30]/algebraicVariables[24]
    algebraicVariables[26] = constants[31]*algebraicVariables[24]
    rates[4] = constants[33]*states[5]-algebraicVariables[26]*states[0]*states[4]-(algebraicVariables[25]*pow(states[0], 2.0)*states[4]-constants[32]*states[3])
    rates[3] = algebraicVariables[25]*pow(states[0], 2.0)*states[4]-constants[32]*states[3]-(algebraicVariables[26]*states[0]*states[3]-constants[33]*states[6])
    rates[6] = algebraicVariables[26]*states[0]*states[3]-constants[33]*states[6]-(constants[32]*states[6]-algebraicVariables[25]*pow(states[0], 2.0)*states[5])
    rates[5] = constants[32]*states[6]-algebraicVariables[25]*pow(states[0], 2.0)*states[5]-(constants[33]*states[5]-algebraicVariables[26]*states[0]*states[4])
    algebraicVariables[31] = constants[40]*states[7]*(1.0-states[9])-constants[39]*states[9]
    rates[9] = algebraicVariables[31]
    algebraicVariables[32] = constants[42]*states[7]*(1.0-(states[10]+states[11]))-constants[41]*states[10]
    rates[10] = algebraicVariables[32]
    algebraicVariables[33] = constants[45]*constants[44]*(1.0-(states[10]+states[11]))-constants[43]*states[11]
    rates[11] = algebraicVariables[33]
    algebraicVariables[34] = constants[47]*states[7]*(1.0-states[12])-constants[46]*states[12]
    rates[12] = algebraicVariables[34]
    algebraicVariables[35] = constants[47]*states[0]*(1.0-states[13])-constants[46]*states[13]
    rates[13] = algebraicVariables[35]
    algebraicVariables[36] = constants[49]*states[2]*(1.0-states[14])-constants[48]*states[14]
    rates[14] = algebraicVariables[36]
    algebraicVariables[29] = computed_constants[7]/(1.0+exp((-states[7]+constants[37])/constants[36]))
    algebraicVariables[28] = (states[0]-states[7])/constants[35]
    rates[7] = 1.0*(algebraicVariables[28]*computed_constants[2]-algebraicVariables[29]*computed_constants[8])/computed_constants[3]-(constants[52]*algebraicVariables[34]+constants[50]*algebraicVariables[31]+constants[51]*algebraicVariables[32])
    algebraicVariables[22] = constants[25]*states[3]*(states[2]-states[0])
    algebraicVariables[37] = 2.0*constants[84]*algebraicVariables[8]/(computed_constants[0]*(1.0-exp(-1.0*algebraicVariables[8]*2.0/computed_constants[0])))*(states[0]-constants[5]*exp(-2.0*algebraicVariables[8]/computed_constants[0]))*states[25]*states[24]
    algebraicVariables[38] = 2.0*constants[77]*(algebraicVariables[8]-0.0)/(computed_constants[0]*(1.0-exp(-1.0*(algebraicVariables[8]-0.0)*2.0/computed_constants[0])))*(states[0]-constants[5]*exp(-2.0*(algebraicVariables[8]-0.0)/computed_constants[0]))*states[23]*states[22]*states[21]
    rates[0] = algebraicVariables[22]*computed_constants[9]/computed_constants[2]-((algebraicVariables[38]+algebraicVariables[37]-2.0*algebraicVariables[3])/(2.0*constants[6]*computed_constants[2])+algebraicVariables[28]+constants[52]*algebraicVariables[35])
    algebraicVariables[30] = (states[8]-states[2])/constants[38]
    rates[8] = algebraicVariables[29]-algebraicVariables[30]*computed_constants[9]/computed_constants[8]
    rates[2] = algebraicVariables[30]-(algebraicVariables[22]+constants[53]*algebraicVariables[36])
    algebraicVariables[39] = constants[76]*states[20]*states[19]*(algebraicVariables[8]-computed_constants[1])
    algebraicVariables[40] = constants[90]*constants[89]*(algebraicVariables[8]-computed_constants[1])*(1.0+exp((algebraicVariables[8]+20.0)/20.0))*states[32] if gt_func(constants[0], 0.0) else 0.0
    algebraicVariables[67] = 0.000365*constants[77]*(algebraicVariables[8]-0.0)/(computed_constants[0]*(1.0-exp(-1.0*(algebraicVariables[8]-0.0)/computed_constants[0])))*(constants[3]-constants[4]*exp(-1.0*(algebraicVariables[8]-0.0)/computed_constants[0]))*states[23]*states[22]*states[21]
    algebraicVariables[41] = (algebraicVariables[38]+algebraicVariables[67]+algebraicVariables[5])*(1.0-computed_constants[19])*1.0*computed_constants[18]
    algebraicVariables[42] = constants[86]*(algebraicVariables[8]-computed_constants[1])*states[27]*states[26]
    algebraicVariables[93] = computed_constants[0]*log((constants[4]+0.12*constants[2])/(constants[3]+0.12*algebraicVariables[0]))
    algebraicVariables[43] = computed_constants[22]*(algebraicVariables[8]-algebraicVariables[93])*pow(states[31], 2.0)
    algebraicVariables[44] = constants[87]*(algebraicVariables[8]-computed_constants[1])*(0.9*states[30]+0.1*states[29])*states[28]
    algebraicVariables[48] = states[16]*computed_constants[15]*(algebraicVariables[8]-computed_constants[1])*(1.0-constants[71])
    algebraicVariables[45] = algebraicVariables[6]+algebraicVariables[48]
    algebraicVariables[46] = algebraicVariables[45]+algebraicVariables[44]+algebraicVariables[43]+algebraicVariables[42]+algebraicVariables[4]+algebraicVariables[3]+algebraicVariables[7]+algebraicVariables[41]+algebraicVariables[37]+algebraicVariables[40]+algebraicVariables[39]
    rates[15] = -algebraicVariables[46]/constants[60]
    algebraicVariables[49] = 1.0/(0.36*(algebraicVariables[8]+148.8-computed_constants[16]-computed_constants[17])/(exp(0.066*(algebraicVariables[8]+148.8-computed_constants[16]-computed_constants[17]))-1.0)+0.1*(algebraicVariables[8]+87.3-computed_constants[16]-computed_constants[17])/(1.0-exp(-0.2*(algebraicVariables[8]+87.3-computed_constants[16]-computed_constants[17]))))-0.054
    algebraicVariables[50] = 0.01329+0.99921/(1.0+exp((algebraicVariables[8]+97.134-computed_constants[16]-computed_constants[17]-constants[72])/8.1752)) if lt_func(algebraicVariables[8], -(80.0-computed_constants[16]-computed_constants[17]-constants[72])) else 0.0002501*exp(-(algebraicVariables[8]-computed_constants[16]-computed_constants[17]-constants[72])/12.861)
    rates[16] = (algebraicVariables[50]-states[16])/algebraicVariables[49]
    algebraicVariables[57] = 8000.0*exp(-0.056*(algebraicVariables[8]+66.0))
    algebraicVariables[55] = algebraicVariables[8]+41.0
    algebraicVariables[56] = 2000.0 if lt_func(fabs(algebraicVariables[55]), constants[75]) else 200.0*algebraicVariables[55]/(1.0-exp(-0.1*algebraicVariables[55]))
    algebraicVariables[58] = 1.0/(algebraicVariables[56]+algebraicVariables[57])
    algebraicVariables[54] = 1.0/(1.0+exp(-(algebraicVariables[8]+42.0504)/8.3106))
    rates[18] = (algebraicVariables[54]-states[18])/algebraicVariables[58]
    algebraicVariables[61] = 2000.0/(320.0*exp(-0.1*(algebraicVariables[8]+75.0))+1.0)
    algebraicVariables[60] = 20.0*exp(-0.125*(algebraicVariables[8]+75.0))
    algebraicVariables[62] = 1.0/(algebraicVariables[60]+algebraicVariables[61])
    algebraicVariables[59] = 1.0/(1.0+exp((algebraicVariables[8]+69.804)/4.4565))
    rates[17] = (algebraicVariables[59]-states[17])/algebraicVariables[62]
    algebraicVariables[63] = 0.009/(1.0+exp((algebraicVariables[8]+5.0)/12.0))+0.0005
    algebraicVariables[64] = 1.0/(1.0+exp((algebraicVariables[8]+6.0)/-8.6))
    rates[20] = (algebraicVariables[64]-states[20])/algebraicVariables[63]
    algebraicVariables[65] = 0.59/(1.0+exp((algebraicVariables[8]+60.0)/10.0))+3.05
    algebraicVariables[66] = 1.0/(1.0+exp((algebraicVariables[8]+7.5)/10.0))
    rates[19] = (algebraicVariables[66]-states[19])/algebraicVariables[65]
    algebraicVariables[68] = 1.0/(1.0+exp(-(algebraicVariables[8]-constants[79]-computed_constants[20])/(constants[78]*(1.0+computed_constants[21]/100.0))))
    algebraicVariables[73] = -1.80001 if eq_func(algebraicVariables[8], -1.8) else algebraicVariables[8]
    algebraicVariables[69] = 0.01143*(algebraicVariables[73]+1.8)/(exp((algebraicVariables[73]+1.8)/2.5)-1.0)
    algebraicVariables[72] = -41.80001 if eq_func(algebraicVariables[8], -41.8) else 0.0 if eq_func(algebraicVariables[8], 0.0) else -6.80001 if eq_func(algebraicVariables[8], -6.8) else algebraicVariables[8]
    algebraicVariables[70] = -0.02839*(algebraicVariables[72]+41.8)/(exp(-(algebraicVariables[72]+41.8)/2.5)-1.0)-0.0849*(algebraicVariables[72]+6.8)/(exp(-(algebraicVariables[72]+6.8)/4.8)-1.0)
    algebraicVariables[71] = 0.001/(algebraicVariables[70]+algebraicVariables[69])
    rates[23] = (algebraicVariables[68]-states[23])/algebraicVariables[71]
    algebraicVariables[75] = 0.001*(44.3+230.0*exp(-pow((algebraicVariables[8]+36.0)/10.0, 2.0)))
    algebraicVariables[74] = 1.0/(1.0+exp((algebraicVariables[8]+37.4+constants[81])/(5.3+constants[80])))
    rates[22] = (algebraicVariables[74]-states[22])/algebraicVariables[75]
    algebraicVariables[76] = constants[82]/(constants[82]+states[0])
    algebraicVariables[77] = 0.001*algebraicVariables[76]/constants[83]
    rates[21] = (algebraicVariables[76]-states[21])/algebraicVariables[77]
    algebraicVariables[79] = 0.001/(1.068*exp((algebraicVariables[8]+38.3)/30.0)+1.068*exp(-(algebraicVariables[8]+38.3)/30.0))
    algebraicVariables[78] = 1.0/(1.0+exp(-(algebraicVariables[8]+38.3)/5.5))
    rates[25] = (algebraicVariables[78]-states[25])/algebraicVariables[79]
    algebraicVariables[81] = 1.0/(16.67*exp(-(algebraicVariables[8]+75.0)/83.3)+16.67*exp((algebraicVariables[8]+75.0)/15.38))+constants[85]
    algebraicVariables[80] = 1.0/(1.0+exp((algebraicVariables[8]+58.7)/3.8))
    rates[24] = (algebraicVariables[80]-states[24])/algebraicVariables[81]
    algebraicVariables[83] = 0.001*0.6*(65.17/(0.57*exp(-0.08*(algebraicVariables[8]+44.0))+0.065*exp(0.1*(algebraicVariables[8]+45.93)))+10.1)
    algebraicVariables[82] = 1.0/(1.0+exp((algebraicVariables[8]+49.0)/13.0))
    rates[27] = (algebraicVariables[82]-states[27])/algebraicVariables[83]
    algebraicVariables[85] = 0.001*0.66*1.4*(15.59/(1.037*exp(0.09*(algebraicVariables[8]+30.61))+0.369*exp(-0.12*(algebraicVariables[8]+23.84)))+2.98)
    algebraicVariables[84] = 1.0/(1.0+exp(-(algebraicVariables[8]-19.3)/15.0))
    rates[26] = (algebraicVariables[84]-states[26])/algebraicVariables[85]
    algebraicVariables[89] = 0.84655354/(4.2*exp(algebraicVariables[8]/17.0)+0.15*exp(-algebraicVariables[8]/21.6))
    algebraicVariables[88] = 1.0/(1.0+exp(-(algebraicVariables[8]+10.0144)/7.6607))
    rates[29] = (algebraicVariables[88]-states[29])/algebraicVariables[89]
    algebraicVariables[90] = 1.0/(30.0*exp(algebraicVariables[8]/10.0)+exp(-algebraicVariables[8]/12.0))
    rates[30] = (algebraicVariables[88]-states[30])/algebraicVariables[90]
    algebraicVariables[91] = 1.0/(100.0*exp(-algebraicVariables[8]/54.645)+656.0*exp(algebraicVariables[8]/106.157))
    algebraicVariables[92] = 1.0/(1.0+exp((algebraicVariables[8]+28.6)/17.1))
    rates[28] = (algebraicVariables[92]-states[28])/algebraicVariables[91]
    algebraicVariables[94] = sqrt(1.0/(1.0+exp(-(algebraicVariables[8]+0.6383-computed_constants[23])/10.7071)))
    algebraicVariables[95] = 1.0*exp(-(algebraicVariables[8]-computed_constants[23]-5.0)/25.0)
    algebraicVariables[96] = 28.0/(1.0+exp(-(algebraicVariables[8]-40.0-computed_constants[23])/3.0))
    algebraicVariables[97] = 1.0/(algebraicVariables[96]+algebraicVariables[95])
    rates[31] = (algebraicVariables[94]-states[31])/algebraicVariables[97]
    algebraicVariables[98] = 10.0*exp(0.0133*(algebraicVariables[8]+40.0))
    algebraicVariables[100] = 1.0/(computed_constants[24]+algebraicVariables[98])
    algebraicVariables[99] = computed_constants[24]/(computed_constants[24]+algebraicVariables[98])
    rates[32] = (algebraicVariables[99]-states[32])/algebraicVariables[100]


def compute_variables(voi, states, rates, constants, computed_constants, algebraic_variables):
    algebraicVariables[0] = states[1]
    algebraicVariables[1] = computed_constants[0]*log(constants[2]/algebraicVariables[0])
    algebraicVariables[2] = 0.5*computed_constants[0]*log(constants[5]/states[0])
    algebraicVariables[8] = algebraicVariables[47] if geq_func(constants[63], 1.0) else states[15]
    algebraicVariables[4] = computed_constants[4]*constants[10]*pow(1.0+pow(constants[9]/constants[4], 1.2), -1.0)*pow(1.0+pow(constants[8]/algebraicVariables[0], 1.3), -1.0)*pow(1.0+exp(-(algebraicVariables[8]-algebraicVariables[1]+110.0)/20.0), -1.0)
    algebraicVariables[20] = 1.0+states[0]/constants[15]*(1.0+exp(-constants[14]*algebraicVariables[8]/computed_constants[0])+algebraicVariables[0]/constants[19])+algebraicVariables[0]/constants[18]*(1.0+algebraicVariables[0]/constants[17]*(1.0+algebraicVariables[0]/constants[13]))
    algebraicVariables[13] = states[0]/constants[15]*exp(-constants[14]*algebraicVariables[8]/computed_constants[0])/algebraicVariables[20]
    algebraicVariables[21] = 1.0+constants[5]/constants[22]*(1.0+exp(constants[21]*algebraicVariables[8]/computed_constants[0]))+constants[2]/constants[24]*(1.0+constants[2]/constants[23]*(1.0+constants[2]/constants[20]))
    algebraicVariables[14] = constants[5]/constants[22]*exp(constants[21]*algebraicVariables[8]/computed_constants[0])/algebraicVariables[21]
    algebraicVariables[17] = exp(constants[16]*algebraicVariables[8]/(2.0*computed_constants[0]))
    algebraicVariables[19] = algebraicVariables[0]/constants[18]*algebraicVariables[0]/constants[17]*(1.0+algebraicVariables[0]/constants[13])*exp(constants[16]*algebraicVariables[8]/(2.0*computed_constants[0]))/algebraicVariables[20]
    algebraicVariables[18] = constants[2]/constants[24]*constants[2]/constants[23]*(1.0+constants[2]/constants[20])*exp(-constants[16]*algebraicVariables[8]/(2.0*computed_constants[0]))/algebraicVariables[21]
    algebraicVariables[9] = algebraicVariables[18]*computed_constants[5]*(algebraicVariables[19]+algebraicVariables[13])+algebraicVariables[19]*algebraicVariables[14]*(computed_constants[5]+algebraicVariables[17])
    algebraicVariables[16] = algebraicVariables[0]/(constants[13]+algebraicVariables[0])
    algebraicVariables[15] = exp(-constants[16]*algebraicVariables[8]/(2.0*computed_constants[0]))
    algebraicVariables[10] = algebraicVariables[19]*algebraicVariables[16]*(algebraicVariables[18]+algebraicVariables[14])+algebraicVariables[13]*algebraicVariables[18]*(algebraicVariables[16]+algebraicVariables[15])
    algebraicVariables[11] = algebraicVariables[17]*algebraicVariables[16]*(algebraicVariables[19]+algebraicVariables[13])+algebraicVariables[15]*algebraicVariables[13]*(computed_constants[5]+algebraicVariables[17])
    algebraicVariables[12] = algebraicVariables[15]*computed_constants[5]*(algebraicVariables[18]+algebraicVariables[14])+algebraicVariables[14]*algebraicVariables[17]*(algebraicVariables[16]+algebraicVariables[15])
    algebraicVariables[3] = (1.0-constants[12])*constants[11]*(algebraicVariables[11]*algebraicVariables[14]-algebraicVariables[12]*algebraicVariables[13])/(algebraicVariables[12]+algebraicVariables[11]+algebraicVariables[10]+algebraicVariables[9])
    algebraicVariables[22] = constants[25]*states[3]*(states[2]-states[0])
    algebraicVariables[23] = states[2]-states[0]
    algebraicVariables[24] = constants[29]-(constants[29]-constants[28])/(1.0+pow(constants[27]/states[2], constants[26]))
    algebraicVariables[25] = constants[30]/algebraicVariables[24]
    algebraicVariables[26] = constants[31]*algebraicVariables[24]
    algebraicVariables[27] = states[4]+states[3]+states[6]+states[5]
    algebraicVariables[28] = (states[0]-states[7])/constants[35]
    algebraicVariables[29] = computed_constants[7]/(1.0+exp((-states[7]+constants[37])/constants[36]))
    algebraicVariables[30] = (states[8]-states[2])/constants[38]
    algebraicVariables[31] = constants[40]*states[7]*(1.0-states[9])-constants[39]*states[9]
    algebraicVariables[32] = constants[42]*states[7]*(1.0-(states[10]+states[11]))-constants[41]*states[10]
    algebraicVariables[33] = constants[45]*constants[44]*(1.0-(states[10]+states[11]))-constants[43]*states[11]
    algebraicVariables[34] = constants[47]*states[7]*(1.0-states[12])-constants[46]*states[12]
    algebraicVariables[35] = constants[47]*states[0]*(1.0-states[13])-constants[46]*states[13]
    algebraicVariables[36] = constants[49]*states[2]*(1.0-states[14])-constants[48]*states[14]
    algebraicVariables[39] = constants[76]*states[20]*states[19]*(algebraicVariables[8]-computed_constants[1])
    algebraicVariables[40] = constants[90]*constants[89]*(algebraicVariables[8]-computed_constants[1])*(1.0+exp((algebraicVariables[8]+20.0)/20.0))*states[32] if gt_func(constants[0], 0.0) else 0.0
    algebraicVariables[37] = 2.0*constants[84]*algebraicVariables[8]/(computed_constants[0]*(1.0-exp(-1.0*algebraicVariables[8]*2.0/computed_constants[0])))*(states[0]-constants[5]*exp(-2.0*algebraicVariables[8]/computed_constants[0]))*states[25]*states[24]
    algebraicVariables[5] = 0.0000185*constants[77]*(algebraicVariables[8]-0.0)/(computed_constants[0]*(1.0-exp(-1.0*(algebraicVariables[8]-0.0)/computed_constants[0])))*(algebraicVariables[0]-constants[2]*exp(-1.0*(algebraicVariables[8]-0.0)/computed_constants[0]))*states[23]*states[22]*states[21]
    algebraicVariables[67] = 0.000365*constants[77]*(algebraicVariables[8]-0.0)/(computed_constants[0]*(1.0-exp(-1.0*(algebraicVariables[8]-0.0)/computed_constants[0])))*(constants[3]-constants[4]*exp(-1.0*(algebraicVariables[8]-0.0)/computed_constants[0]))*states[23]*states[22]*states[21]
    algebraicVariables[38] = 2.0*constants[77]*(algebraicVariables[8]-0.0)/(computed_constants[0]*(1.0-exp(-1.0*(algebraicVariables[8]-0.0)*2.0/computed_constants[0])))*(states[0]-constants[5]*exp(-2.0*(algebraicVariables[8]-0.0)/computed_constants[0]))*states[23]*states[22]*states[21]
    algebraicVariables[41] = (algebraicVariables[38]+algebraicVariables[67]+algebraicVariables[5])*(1.0-computed_constants[19])*1.0*computed_constants[18]
    algebraicVariables[51] = computed_constants[0]*log((constants[2]+0.12*constants[4])/(algebraicVariables[0]+0.12*constants[3]))
    algebraicVariables[53] = constants[74]*pow(states[18], 3.0)*(algebraicVariables[8]-algebraicVariables[51])
    algebraicVariables[52] = constants[73]*pow(states[18], 3.0)*states[17]*(algebraicVariables[8]-algebraicVariables[51])
    algebraicVariables[7] = algebraicVariables[52]+algebraicVariables[53]
    algebraicVariables[42] = constants[86]*(algebraicVariables[8]-computed_constants[1])*states[27]*states[26]
    algebraicVariables[93] = computed_constants[0]*log((constants[4]+0.12*constants[2])/(constants[3]+0.12*algebraicVariables[0]))
    algebraicVariables[43] = computed_constants[22]*(algebraicVariables[8]-algebraicVariables[93])*pow(states[31], 2.0)
    algebraicVariables[44] = constants[87]*(algebraicVariables[8]-computed_constants[1])*(0.9*states[30]+0.1*states[29])*states[28]
    algebraicVariables[48] = states[16]*computed_constants[15]*(algebraicVariables[8]-computed_constants[1])*(1.0-constants[71])
    algebraicVariables[6] = states[16]*computed_constants[14]*(algebraicVariables[8]-algebraicVariables[1])*(1.0-constants[71])
    algebraicVariables[45] = algebraicVariables[6]+algebraicVariables[48]
    algebraicVariables[46] = algebraicVariables[45]+algebraicVariables[44]+algebraicVariables[43]+algebraicVariables[42]+algebraicVariables[4]+algebraicVariables[3]+algebraicVariables[7]+algebraicVariables[41]+algebraicVariables[37]+algebraicVariables[40]+algebraicVariables[39]
    algebraicVariables[49] = 1.0/(0.36*(algebraicVariables[8]+148.8-computed_constants[16]-computed_constants[17])/(exp(0.066*(algebraicVariables[8]+148.8-computed_constants[16]-computed_constants[17]))-1.0)+0.1*(algebraicVariables[8]+87.3-computed_constants[16]-computed_constants[17])/(1.0-exp(-0.2*(algebraicVariables[8]+87.3-computed_constants[16]-computed_constants[17]))))-0.054
    algebraicVariables[50] = 0.01329+0.99921/(1.0+exp((algebraicVariables[8]+97.134-computed_constants[16]-computed_constants[17]-constants[72])/8.1752)) if lt_func(algebraicVariables[8], -(80.0-computed_constants[16]-computed_constants[17]-constants[72])) else 0.0002501*exp(-(algebraicVariables[8]-computed_constants[16]-computed_constants[17]-constants[72])/12.861)
    algebraicVariables[54] = 1.0/(1.0+exp(-(algebraicVariables[8]+42.0504)/8.3106))
    algebraicVariables[55] = algebraicVariables[8]+41.0
    algebraicVariables[56] = 2000.0 if lt_func(fabs(algebraicVariables[55]), constants[75]) else 200.0*algebraicVariables[55]/(1.0-exp(-0.1*algebraicVariables[55]))
    algebraicVariables[57] = 8000.0*exp(-0.056*(algebraicVariables[8]+66.0))
    algebraicVariables[58] = 1.0/(algebraicVariables[56]+algebraicVariables[57])
    algebraicVariables[59] = 1.0/(1.0+exp((algebraicVariables[8]+69.804)/4.4565))
    algebraicVariables[60] = 20.0*exp(-0.125*(algebraicVariables[8]+75.0))
    algebraicVariables[61] = 2000.0/(320.0*exp(-0.1*(algebraicVariables[8]+75.0))+1.0)
    algebraicVariables[62] = 1.0/(algebraicVariables[60]+algebraicVariables[61])
    algebraicVariables[64] = 1.0/(1.0+exp((algebraicVariables[8]+6.0)/-8.6))
    algebraicVariables[63] = 0.009/(1.0+exp((algebraicVariables[8]+5.0)/12.0))+0.0005
    algebraicVariables[66] = 1.0/(1.0+exp((algebraicVariables[8]+7.5)/10.0))
    algebraicVariables[65] = 0.59/(1.0+exp((algebraicVariables[8]+60.0)/10.0))+3.05
    algebraicVariables[68] = 1.0/(1.0+exp(-(algebraicVariables[8]-constants[79]-computed_constants[20])/(constants[78]*(1.0+computed_constants[21]/100.0))))
    algebraicVariables[73] = -1.80001 if eq_func(algebraicVariables[8], -1.8) else algebraicVariables[8]
    algebraicVariables[69] = 0.01143*(algebraicVariables[73]+1.8)/(exp((algebraicVariables[73]+1.8)/2.5)-1.0)
    algebraicVariables[72] = -41.80001 if eq_func(algebraicVariables[8], -41.8) else 0.0 if eq_func(algebraicVariables[8], 0.0) else -6.80001 if eq_func(algebraicVariables[8], -6.8) else algebraicVariables[8]
    algebraicVariables[70] = -0.02839*(algebraicVariables[72]+41.8)/(exp(-(algebraicVariables[72]+41.8)/2.5)-1.0)-0.0849*(algebraicVariables[72]+6.8)/(exp(-(algebraicVariables[72]+6.8)/4.8)-1.0)
    algebraicVariables[71] = 0.001/(algebraicVariables[70]+algebraicVariables[69])
    algebraicVariables[74] = 1.0/(1.0+exp((algebraicVariables[8]+37.4+constants[81])/(5.3+constants[80])))
    algebraicVariables[75] = 0.001*(44.3+230.0*exp(-pow((algebraicVariables[8]+36.0)/10.0, 2.0)))
    algebraicVariables[76] = constants[82]/(constants[82]+states[0])
    algebraicVariables[77] = 0.001*algebraicVariables[76]/constants[83]
    algebraicVariables[78] = 1.0/(1.0+exp(-(algebraicVariables[8]+38.3)/5.5))
    algebraicVariables[79] = 0.001/(1.068*exp((algebraicVariables[8]+38.3)/30.0)+1.068*exp(-(algebraicVariables[8]+38.3)/30.0))
    algebraicVariables[80] = 1.0/(1.0+exp((algebraicVariables[8]+58.7)/3.8))
    algebraicVariables[81] = 1.0/(16.67*exp(-(algebraicVariables[8]+75.0)/83.3)+16.67*exp((algebraicVariables[8]+75.0)/15.38))+constants[85]
    algebraicVariables[82] = 1.0/(1.0+exp((algebraicVariables[8]+49.0)/13.0))
    algebraicVariables[83] = 0.001*0.6*(65.17/(0.57*exp(-0.08*(algebraicVariables[8]+44.0))+0.065*exp(0.1*(algebraicVariables[8]+45.93)))+10.1)
    algebraicVariables[84] = 1.0/(1.0+exp(-(algebraicVariables[8]-19.3)/15.0))
    algebraicVariables[85] = 0.001*0.66*1.4*(15.59/(1.037*exp(0.09*(algebraicVariables[8]+30.61))+0.369*exp(-0.12*(algebraicVariables[8]+23.84)))+2.98)
    algebraicVariables[86] = 1.0/(1.0+exp(-(algebraicVariables[8]+23.2)/6.6))/(0.84655354/(37.2*exp(algebraicVariables[8]/11.9)+0.96*exp(-algebraicVariables[8]/18.5)))
    algebraicVariables[87] = 4.0*((37.2*exp(algebraicVariables[8]/15.9)+0.96*exp(-algebraicVariables[8]/22.5))/0.84655354-1.0/(1.0+exp(-(algebraicVariables[8]+23.2)/10.6))/(0.84655354/(37.2*exp(algebraicVariables[8]/15.9)+0.96*exp(-algebraicVariables[8]/22.5))))
    algebraicVariables[88] = 1.0/(1.0+exp(-(algebraicVariables[8]+10.0144)/7.6607))
    algebraicVariables[89] = 0.84655354/(4.2*exp(algebraicVariables[8]/17.0)+0.15*exp(-algebraicVariables[8]/21.6))
    algebraicVariables[90] = 1.0/(30.0*exp(algebraicVariables[8]/10.0)+exp(-algebraicVariables[8]/12.0))
    algebraicVariables[91] = 1.0/(100.0*exp(-algebraicVariables[8]/54.645)+656.0*exp(algebraicVariables[8]/106.157))
    algebraicVariables[92] = 1.0/(1.0+exp((algebraicVariables[8]+28.6)/17.1))
    algebraicVariables[94] = sqrt(1.0/(1.0+exp(-(algebraicVariables[8]+0.6383-computed_constants[23])/10.7071)))
    algebraicVariables[95] = 1.0*exp(-(algebraicVariables[8]-computed_constants[23]-5.0)/25.0)
    algebraicVariables[96] = 28.0/(1.0+exp(-(algebraicVariables[8]-40.0-computed_constants[23])/3.0))
    algebraicVariables[97] = 1.0/(algebraicVariables[96]+algebraicVariables[95])
    algebraicVariables[98] = 10.0*exp(0.0133*(algebraicVariables[8]+40.0))
    algebraicVariables[99] = computed_constants[24]/(computed_constants[24]+algebraicVariables[98])
    algebraicVariables[100] = 1.0/(computed_constants[24]+algebraicVariables[98])

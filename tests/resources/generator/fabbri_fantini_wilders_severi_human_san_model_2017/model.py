# The content of this file was generated using the Python profile of libCellML 0.5.0.

from enum import Enum
from math import *


__version__ = "0.5.0"
LIBCELLML_VERSION = "0.5.0"

STATE_COUNT = 33
CONSTANT_COUNT = 91
COMPUTED_CONSTANT_COUNT = 25
ALGEBRAIC_COUNT = 101

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
    {"name": "paF", "units": "dimensionless", "component": "i_Kr_pa_gate"},
    {"name": "paS", "units": "dimensionless", "component": "i_Kr_pa_gate"},
    {"name": "n", "units": "dimensionless", "component": "i_Ks_n_gate"},
    {"name": "a", "units": "dimensionless", "component": "i_KACh_a_gate"}
]

CONSTANT_INFO = [
    {"name": "ACh", "units": "millimolar", "component": "Rate_modulation_experiments"},
    {"name": "Iso_1_uM", "units": "dimensionless", "component": "Rate_modulation_experiments"},
    {"name": "Nao", "units": "millimolar", "component": "Ionic_values"},
    {"name": "Ko", "units": "millimolar", "component": "Ionic_values"},
    {"name": "Ki", "units": "millimolar", "component": "Ionic_values"},
    {"name": "Cao", "units": "millimolar", "component": "Ionic_values"},
    {"name": "Nai_clamp", "units": "dimensionless", "component": "Nai_concentration"},
    {"name": "F", "units": "coulomb_per_mole", "component": "Membrane"},
    {"name": "Km_Nap", "units": "millimolar", "component": "i_NaK"},
    {"name": "Km_Kp", "units": "millimolar", "component": "i_NaK"},
    {"name": "i_NaK_max", "units": "nanoA", "component": "i_NaK"},
    {"name": "blockade_NaCa", "units": "dimensionless", "component": "i_NaCa"},
    {"name": "K_NaCa", "units": "nanoA", "component": "i_NaCa"},
    {"name": "K3ni", "units": "millimolar", "component": "i_NaCa"},
    {"name": "Kci", "units": "millimolar", "component": "i_NaCa"},
    {"name": "Qci", "units": "dimensionless", "component": "i_NaCa"},
    {"name": "K1ni", "units": "millimolar", "component": "i_NaCa"},
    {"name": "K2ni", "units": "millimolar", "component": "i_NaCa"},
    {"name": "Qn", "units": "dimensionless", "component": "i_NaCa"},
    {"name": "Kcni", "units": "millimolar", "component": "i_NaCa"},
    {"name": "K3no", "units": "millimolar", "component": "i_NaCa"},
    {"name": "Kco", "units": "millimolar", "component": "i_NaCa"},
    {"name": "Qco", "units": "dimensionless", "component": "i_NaCa"},
    {"name": "K1no", "units": "millimolar", "component": "i_NaCa"},
    {"name": "K2no", "units": "millimolar", "component": "i_NaCa"},
    {"name": "ks", "units": "per_second", "component": "Ca_SR_release"},
    {"name": "MaxSR", "units": "dimensionless", "component": "Ca_SR_release"},
    {"name": "MinSR", "units": "dimensionless", "component": "Ca_SR_release"},
    {"name": "EC50_SR", "units": "millimolar", "component": "Ca_SR_release"},
    {"name": "HSR", "units": "dimensionless", "component": "Ca_SR_release"},
    {"name": "koCa", "units": "per_millimolar2_second", "component": "Ca_SR_release"},
    {"name": "kiCa", "units": "per_millimolar_second", "component": "Ca_SR_release"},
    {"name": "kim", "units": "per_second", "component": "Ca_SR_release"},
    {"name": "kom", "units": "per_second", "component": "Ca_SR_release"},
    {"name": "P_up_basal", "units": "millimolar_per_second", "component": "Ca_intracellular_fluxes"},
    {"name": "tau_dif_Ca", "units": "second", "component": "Ca_intracellular_fluxes"},
    {"name": "K_up", "units": "millimolar", "component": "Ca_intracellular_fluxes"},
    {"name": "slope_up", "units": "millimolar", "component": "Ca_intracellular_fluxes"},
    {"name": "tau_tr", "units": "second", "component": "Ca_intracellular_fluxes"},
    {"name": "kf_TC", "units": "per_millimolar_second", "component": "Ca_buffering"},
    {"name": "kb_TC", "units": "per_second", "component": "Ca_buffering"},
    {"name": "kf_TMC", "units": "per_millimolar_second", "component": "Ca_buffering"},
    {"name": "kb_TMC", "units": "per_second", "component": "Ca_buffering"},
    {"name": "kf_TMM", "units": "per_millimolar_second", "component": "Ca_buffering"},
    {"name": "Mgi", "units": "millimolar", "component": "Ca_buffering"},
    {"name": "kb_TMM", "units": "per_second", "component": "Ca_buffering"},
    {"name": "kf_CM", "units": "per_millimolar_second", "component": "Ca_buffering"},
    {"name": "kb_CM", "units": "per_second", "component": "Ca_buffering"},
    {"name": "kf_CQ", "units": "per_millimolar_second", "component": "Ca_buffering"},
    {"name": "kb_CQ", "units": "per_second", "component": "Ca_buffering"},
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
    {"name": "R", "units": "joule_per_kilomole_kelvin", "component": "Membrane"},
    {"name": "T", "units": "kelvin", "component": "Membrane"},
    {"name": "clamp_mode", "units": "dimensionless", "component": "Membrane"},
    {"name": "V_test", "units": "millivolt", "component": "Voltage_clamp"},
    {"name": "t_holding", "units": "second", "component": "Voltage_clamp"},
    {"name": "t_test", "units": "second", "component": "Voltage_clamp"},
    {"name": "V_holding", "units": "millivolt", "component": "Voltage_clamp"},
    {"name": "g_f", "units": "microS", "component": "i_f"},
    {"name": "Km_f", "units": "millimolar", "component": "i_f"},
    {"name": "alpha", "units": "dimensionless", "component": "i_f"},
    {"name": "blockade", "units": "dimensionless", "component": "i_f"},
    {"name": "y_shift", "units": "millivolt", "component": "i_f_y_gate"},
    {"name": "g_Na", "units": "microS", "component": "i_Na"},
    {"name": "g_Na_L", "units": "microS", "component": "i_Na"},
    {"name": "delta_m", "units": "millivolt", "component": "i_Na_m_gate"},
    {"name": "g_Kur", "units": "microS", "component": "i_Kur"},
    {"name": "P_CaL", "units": "nanoA_per_millimolar", "component": "i_CaL"},
    {"name": "V_dL", "units": "millivolt", "component": "i_CaL_dL_gate"},
    {"name": "k_dL", "units": "millivolt", "component": "i_CaL_dL_gate"},
    {"name": "shift_fL", "units": "millivolt", "component": "i_CaL_fL_gate"},
    {"name": "k_fL", "units": "millivolt", "component": "i_CaL_fL_gate"},
    {"name": "Km_fCa", "units": "millimolar", "component": "i_CaL_fCa_gate"},
    {"name": "alpha_fCa", "units": "per_second", "component": "i_CaL_fCa_gate"},
    {"name": "P_CaT", "units": "nanoA_per_millimolar", "component": "i_CaT"},
    {"name": "offset_fT", "units": "second", "component": "i_CaT_fT_gate"},
    {"name": "g_to", "units": "microS", "component": "i_to"},
    {"name": "g_Kr", "units": "microS", "component": "i_Kr"},
    {"name": "g_Ks_", "units": "microS", "component": "i_Ks"},
    {"name": "ACh_on", "units": "dimensionless", "component": "i_KACh"},
    {"name": "g_KACh", "units": "microS", "component": "i_KACh"}
]

COMPUTED_CONSTANT_INFO = [
    {"name": "RTONF", "units": "millivolt", "component": "Membrane"},
    {"name": "E_K", "units": "millivolt", "component": "Ionic_values"},
    {"name": "V_i", "units": "millimetre3", "component": "Cell_parameters"},
    {"name": "V_sub", "units": "millimetre3", "component": "Cell_parameters"},
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
    {"name": "E_Na", "units": "millivolt", "component": "Ionic_values"},
    {"name": "Nai", "units": "millimolar", "component": "Nai_concentration"},
    {"name": "E_Ca", "units": "millivolt", "component": "Ionic_values"},
    {"name": "i_Na", "units": "nanoA", "component": "i_Na"},
    {"name": "i_NaCa", "units": "nanoA", "component": "i_NaCa"},
    {"name": "i_NaK", "units": "nanoA", "component": "i_NaK"},
    {"name": "i_siNa", "units": "nanoA", "component": "i_CaL"},
    {"name": "i_fNa", "units": "nanoA", "component": "i_f"},
    {"name": "V", "units": "millivolt", "component": "Membrane"},
    {"name": "x2", "units": "dimensionless", "component": "i_NaCa"},
    {"name": "k21", "units": "dimensionless", "component": "i_NaCa"},
    {"name": "x1", "units": "dimensionless", "component": "i_NaCa"},
    {"name": "k12", "units": "dimensionless", "component": "i_NaCa"},
    {"name": "x4", "units": "dimensionless", "component": "i_NaCa"},
    {"name": "x3", "units": "dimensionless", "component": "i_NaCa"},
    {"name": "k41", "units": "dimensionless", "component": "i_NaCa"},
    {"name": "k23", "units": "dimensionless", "component": "i_NaCa"},
    {"name": "k43", "units": "dimensionless", "component": "i_NaCa"},
    {"name": "k32", "units": "dimensionless", "component": "i_NaCa"},
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
    {"name": "i_siCa", "units": "nanoA", "component": "i_CaL"},
    {"name": "i_CaT", "units": "nanoA", "component": "i_CaT"},
    {"name": "i_tot", "units": "nanoA", "component": "Membrane"},
    {"name": "i_f", "units": "nanoA", "component": "i_f"},
    {"name": "i_Kur", "units": "nanoA", "component": "i_Kur"},
    {"name": "i_KACh", "units": "nanoA", "component": "i_KACh"},
    {"name": "i_CaL", "units": "nanoA", "component": "i_CaL"},
    {"name": "i_to", "units": "nanoA", "component": "i_to"},
    {"name": "i_Ks", "units": "nanoA", "component": "i_Ks"},
    {"name": "i_Kr", "units": "nanoA", "component": "i_Kr"},
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
    {"name": "r_Kur_infinity", "units": "dimensionless", "component": "i_Kur_rKur_gate"},
    {"name": "tau_r_Kur", "units": "second", "component": "i_Kur_rKur_gate"},
    {"name": "s_Kur_infinity", "units": "dimensionless", "component": "i_Kur_sKur_gate"},
    {"name": "tau_s_Kur", "units": "second", "component": "i_Kur_sKur_gate"},
    {"name": "i_siK", "units": "nanoA", "component": "i_CaL"},
    {"name": "dL_infinity", "units": "dimensionless", "component": "i_CaL_dL_gate"},
    {"name": "tau_dL", "units": "second", "component": "i_CaL_dL_gate"},
    {"name": "alpha_dL", "units": "per_second", "component": "i_CaL_dL_gate"},
    {"name": "beta_dL", "units": "per_second", "component": "i_CaL_dL_gate"},
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
    {"name": "tau_n", "units": "second", "component": "i_Ks_n_gate"},
    {"name": "alpha_n", "units": "per_second", "component": "i_Ks_n_gate"},
    {"name": "beta_n", "units": "per_second", "component": "i_Ks_n_gate"},
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


def create_algebraic_array():
    return [nan]*ALGEBRAIC_COUNT


def initialise_variables(states, rates, constants, algebraic):
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
    states[29] = 0.011068
    states[30] = 0.283185
    states[31] = 0.1162
    states[32] = 0.00277
    constants[0] = 0.0
    constants[1] = 0.0
    constants[2] = 140.0
    constants[3] = 5.4
    constants[4] = 140.0
    constants[5] = 1.8
    constants[6] = 1.0
    constants[7] = 96485.3415
    constants[8] = 14.0
    constants[9] = 1.4
    constants[10] = 0.08105
    constants[11] = 0.0
    constants[12] = 3.343
    constants[13] = 26.44
    constants[14] = 0.0207
    constants[15] = 0.1369
    constants[16] = 395.3
    constants[17] = 2.289
    constants[18] = 0.4315
    constants[19] = 26.44
    constants[20] = 4.663
    constants[21] = 3.663
    constants[22] = 0.0
    constants[23] = 1628.0
    constants[24] = 561.4
    constants[25] = 148041085.1
    constants[26] = 15.0
    constants[27] = 1.0
    constants[28] = 0.45
    constants[29] = 2.5
    constants[30] = 10000.0
    constants[31] = 500.0
    constants[32] = 5.0
    constants[33] = 660.0
    constants[34] = 5.0
    constants[35] = 5.469e-5
    constants[36] = 0.000286113
    constants[37] = 5.0e-5
    constants[38] = 0.04
    constants[39] = 88800.0
    constants[40] = 446.0
    constants[41] = 227700.0
    constants[42] = 7.51
    constants[43] = 2277.0
    constants[44] = 2.5
    constants[45] = 751.0
    constants[46] = 1.642e6
    constants[47] = 542.0
    constants[48] = 175.4
    constants[49] = 445.0
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
    constants[61] = 8314.472
    constants[62] = 310.0
    constants[63] = 0.0
    constants[64] = -35.0
    constants[65] = 0.5
    constants[66] = 0.5
    constants[67] = -45.0
    constants[68] = 0.00427
    constants[69] = 45.0
    constants[70] = 0.5927
    constants[71] = 0.0
    constants[72] = 0.0
    constants[73] = 0.0223
    constants[74] = 0.0
    constants[75] = 1.0e-5
    constants[76] = 0.1539e-3
    constants[77] = 0.4578
    constants[78] = -16.4508
    constants[79] = 4.3371
    constants[80] = 0.0
    constants[81] = 0.0
    constants[82] = 0.000338
    constants[83] = 0.0075
    constants[84] = 0.04132
    constants[85] = 0.0
    constants[86] = 3.5e-3
    constants[87] = 0.00424
    constants[88] = 0.00065
    constants[89] = 1.0
    constants[90] = 0.00345


def compute_computed_constants(constants, computed_constants):
    computed_constants[0] = constants[61]*constants[62]/constants[7]
    computed_constants[1] = computed_constants[0]*log(constants[3]/constants[4])
    computed_constants[4] = 1.2 if gt_func(constants[1], 0.0) else 1.0
    computed_constants[5] = constants[2]/(constants[20]+constants[2])
    computed_constants[6] = -0.25 if gt_func(constants[1], 0.0) else 0.7*constants[0]/(0.00009+constants[0]) if gt_func(constants[0], 0.0) else 0.0
    computed_constants[7] = constants[34]*(1.0-computed_constants[6])
    computed_constants[10] = 0.000000001*3.14159265358979*pow(constants[55], 2.0)*constants[54]
    computed_constants[3] = 0.000000001*2.0*3.14159265358979*constants[56]*(constants[55]-constants[56]/2.0)*constants[54]
    computed_constants[9] = constants[57]*computed_constants[10]
    computed_constants[2] = constants[58]*computed_constants[10]-computed_constants[3]
    computed_constants[8] = constants[59]*computed_constants[10]
    computed_constants[11] = constants[68]/(constants[3]/(constants[3]+constants[69]))
    computed_constants[12] = computed_constants[11]/(constants[70]+1.0)
    computed_constants[13] = constants[70]*computed_constants[12]
    computed_constants[14] = computed_constants[13]*constants[3]/(constants[3]+constants[69])
    computed_constants[15] = computed_constants[12]*constants[3]/(constants[3]+constants[69])
    computed_constants[16] = -1.0-9.898*pow(1.0*constants[0], 0.618)/(pow(1.0*constants[0], 0.618)+0.00122423) if gt_func(constants[0], 0.0) else 0.0
    computed_constants[17] = 7.5 if gt_func(constants[1], 0.0) else 0.0
    computed_constants[18] = 1.23 if gt_func(constants[1], 0.0) else 1.0
    computed_constants[19] = 0.31*constants[0]/(constants[0]+0.00009)
    computed_constants[20] = -8.0 if gt_func(constants[1], 0.0) else 0.0
    computed_constants[21] = -27.0 if gt_func(constants[1], 0.0) else 0.0
    computed_constants[22] = 1.2*constants[88] if gt_func(constants[1], 0.0) else constants[88]
    computed_constants[23] = -14.0 if gt_func(constants[1], 0.0) else 0.0
    computed_constants[24] = (3.5988-0.025641)/(1.0+0.0000012155/pow(1.0*constants[0], 1.6951))+0.025641


def compute_rates(voi, states, rates, constants, computed_constants, algebraic):
    algebraic[1] = states[1]
    algebraic[51] = computed_constants[0]*log((constants[2]+0.12*constants[3])/(algebraic[1]+0.12*constants[4]))
    algebraic[47] = constants[64] if and_func(gt_func(voi, constants[65]), lt_func(voi, constants[65]+constants[66])) else constants[67]
    algebraic[8] = algebraic[47] if geq_func(constants[63], 1.0) else states[15]
    algebraic[52] = constants[73]*pow(states[18], 3.0)*states[17]*(algebraic[8]-algebraic[51])
    algebraic[53] = constants[74]*pow(states[18], 3.0)*(algebraic[8]-algebraic[51])
    algebraic[3] = algebraic[52]+algebraic[53]
    algebraic[6] = 0.0000185*constants[77]*(algebraic[8]-0.0)/(computed_constants[0]*(1.0-exp(-1.0*(algebraic[8]-0.0)/computed_constants[0])))*(algebraic[1]-constants[2]*exp(-1.0*(algebraic[8]-0.0)/computed_constants[0]))*states[23]*states[22]*states[21]
    algebraic[0] = computed_constants[0]*log(constants[2]/algebraic[1])
    algebraic[7] = states[16]*computed_constants[14]*(algebraic[8]-algebraic[0])*(1.0-constants[71])
    algebraic[5] = computed_constants[4]*constants[10]*pow(1.0+pow(constants[9]/constants[3], 1.2), -1.0)*pow(1.0+pow(constants[8]/algebraic[1], 1.3), -1.0)*pow(1.0+exp(-(algebraic[8]-algebraic[0]+110.0)/20.0), -1.0)
    algebraic[21] = 1.0+constants[5]/constants[21]*(1.0+exp(constants[22]*algebraic[8]/computed_constants[0]))+constants[2]/constants[23]*(1.0+constants[2]/constants[24]*(1.0+constants[2]/constants[20]))
    algebraic[10] = constants[5]/constants[21]*exp(constants[22]*algebraic[8]/computed_constants[0])/algebraic[21]
    algebraic[20] = 1.0+states[0]/constants[14]*(1.0+exp(-constants[15]*algebraic[8]/computed_constants[0])+algebraic[1]/constants[19])+algebraic[1]/constants[16]*(1.0+algebraic[1]/constants[17]*(1.0+algebraic[1]/constants[13]))
    algebraic[12] = states[0]/constants[14]*exp(-constants[15]*algebraic[8]/computed_constants[0])/algebraic[20]
    algebraic[17] = algebraic[1]/(constants[13]+algebraic[1])
    algebraic[18] = exp(constants[18]*algebraic[8]/(2.0*computed_constants[0]))
    algebraic[15] = exp(-constants[18]*algebraic[8]/(2.0*computed_constants[0]))
    algebraic[19] = algebraic[1]/constants[16]*algebraic[1]/constants[17]*(1.0+algebraic[1]/constants[13])*exp(constants[18]*algebraic[8]/(2.0*computed_constants[0]))/algebraic[20]
    algebraic[9] = algebraic[18]*algebraic[17]*(algebraic[19]+algebraic[12])+algebraic[15]*algebraic[12]*(computed_constants[5]+algebraic[18])
    algebraic[16] = constants[2]/constants[23]*constants[2]/constants[24]*(1.0+constants[2]/constants[20])*exp(-constants[18]*algebraic[8]/(2.0*computed_constants[0]))/algebraic[21]
    algebraic[11] = algebraic[15]*computed_constants[5]*(algebraic[16]+algebraic[10])+algebraic[10]*algebraic[18]*(algebraic[17]+algebraic[15])
    algebraic[13] = algebraic[16]*computed_constants[5]*(algebraic[19]+algebraic[12])+algebraic[19]*algebraic[10]*(computed_constants[5]+algebraic[18])
    algebraic[14] = algebraic[19]*algebraic[17]*(algebraic[16]+algebraic[10])+algebraic[12]*algebraic[16]*(algebraic[17]+algebraic[15])
    algebraic[4] = (1.0-constants[11])*constants[12]*(algebraic[9]*algebraic[10]-algebraic[11]*algebraic[12])/(algebraic[11]+algebraic[9]+algebraic[14]+algebraic[13])
    rates[1] = (1.0-constants[6])*-1.0*(algebraic[3]+algebraic[7]+algebraic[6]+3.0*algebraic[5]+3.0*algebraic[4])/(1.0*(computed_constants[2]+computed_constants[3])*constants[7])
    algebraic[24] = constants[26]-(constants[26]-constants[27])/(1.0+pow(constants[28]/states[2], constants[29]))
    algebraic[26] = constants[31]*algebraic[24]
    algebraic[25] = constants[30]/algebraic[24]
    rates[4] = constants[32]*states[5]-algebraic[26]*states[0]*states[4]-(algebraic[25]*pow(states[0], 2.0)*states[4]-constants[33]*states[3])
    rates[3] = algebraic[25]*pow(states[0], 2.0)*states[4]-constants[33]*states[3]-(algebraic[26]*states[0]*states[3]-constants[32]*states[6])
    rates[6] = algebraic[26]*states[0]*states[3]-constants[32]*states[6]-(constants[33]*states[6]-algebraic[25]*pow(states[0], 2.0)*states[5])
    rates[5] = constants[33]*states[6]-algebraic[25]*pow(states[0], 2.0)*states[5]-(constants[32]*states[5]-algebraic[26]*states[0]*states[4])
    algebraic[31] = constants[39]*states[7]*(1.0-states[9])-constants[40]*states[9]
    rates[9] = algebraic[31]
    algebraic[32] = constants[41]*states[7]*(1.0-(states[10]+states[11]))-constants[42]*states[10]
    rates[10] = algebraic[32]
    algebraic[33] = constants[43]*constants[44]*(1.0-(states[10]+states[11]))-constants[45]*states[11]
    rates[11] = algebraic[33]
    algebraic[34] = constants[46]*states[7]*(1.0-states[12])-constants[47]*states[12]
    rates[12] = algebraic[34]
    algebraic[35] = constants[46]*states[0]*(1.0-states[13])-constants[47]*states[13]
    rates[13] = algebraic[35]
    algebraic[36] = constants[48]*states[2]*(1.0-states[14])-constants[49]*states[14]
    rates[14] = algebraic[36]
    algebraic[28] = (states[0]-states[7])/constants[35]
    algebraic[29] = computed_constants[7]/(1.0+exp((-states[7]+constants[36])/constants[37]))
    rates[7] = 1.0*(algebraic[28]*computed_constants[3]-algebraic[29]*computed_constants[8])/computed_constants[2]-(constants[52]*algebraic[34]+constants[50]*algebraic[31]+constants[51]*algebraic[32])
    algebraic[22] = constants[25]*states[3]*(states[2]-states[0])
    algebraic[37] = 2.0*constants[77]*(algebraic[8]-0.0)/(computed_constants[0]*(1.0-exp(-1.0*(algebraic[8]-0.0)*2.0/computed_constants[0])))*(states[0]-constants[5]*exp(-2.0*(algebraic[8]-0.0)/computed_constants[0]))*states[23]*states[22]*states[21]
    algebraic[38] = 2.0*constants[84]*algebraic[8]/(computed_constants[0]*(1.0-exp(-1.0*algebraic[8]*2.0/computed_constants[0])))*(states[0]-constants[5]*exp(-2.0*algebraic[8]/computed_constants[0]))*states[25]*states[24]
    rates[0] = algebraic[22]*computed_constants[9]/computed_constants[3]-((algebraic[37]+algebraic[38]-2.0*algebraic[4])/(2.0*constants[7]*computed_constants[3])+algebraic[28]+constants[52]*algebraic[35])
    algebraic[30] = (states[8]-states[2])/constants[38]
    rates[8] = algebraic[29]-algebraic[30]*computed_constants[9]/computed_constants[8]
    rates[2] = algebraic[30]-(algebraic[22]+constants[53]*algebraic[36])
    algebraic[48] = states[16]*computed_constants[15]*(algebraic[8]-computed_constants[1])*(1.0-constants[71])
    algebraic[40] = algebraic[7]+algebraic[48]
    algebraic[41] = constants[76]*states[20]*states[19]*(algebraic[8]-computed_constants[1])
    algebraic[42] = constants[89]*constants[90]*(algebraic[8]-computed_constants[1])*(1.0+exp((algebraic[8]+20.0)/20.0))*states[32] if gt_func(constants[0], 0.0) else 0.0
    algebraic[67] = 0.000365*constants[77]*(algebraic[8]-0.0)/(computed_constants[0]*(1.0-exp(-1.0*(algebraic[8]-0.0)/computed_constants[0])))*(constants[4]-constants[3]*exp(-1.0*(algebraic[8]-0.0)/computed_constants[0]))*states[23]*states[22]*states[21]
    algebraic[43] = (algebraic[37]+algebraic[67]+algebraic[6])*(1.0-computed_constants[19])*1.0*computed_constants[18]
    algebraic[44] = constants[86]*(algebraic[8]-computed_constants[1])*states[27]*states[26]
    algebraic[93] = computed_constants[0]*log((constants[3]+0.12*constants[2])/(constants[4]+0.12*algebraic[1]))
    algebraic[45] = computed_constants[22]*(algebraic[8]-algebraic[93])*pow(states[31], 2.0)
    algebraic[46] = constants[87]*(algebraic[8]-computed_constants[1])*(0.9*states[29]+0.1*states[30])*states[28]
    algebraic[39] = algebraic[40]+algebraic[46]+algebraic[45]+algebraic[44]+algebraic[5]+algebraic[4]+algebraic[3]+algebraic[43]+algebraic[38]+algebraic[42]+algebraic[41]
    rates[15] = -algebraic[39]/constants[60]
    algebraic[50] = 0.01329+0.99921/(1.0+exp((algebraic[8]+97.134-computed_constants[16]-computed_constants[17]-constants[72])/8.1752)) if lt_func(algebraic[8], -(80.0-computed_constants[16]-computed_constants[17]-constants[72])) else 0.0002501*exp(-(algebraic[8]-computed_constants[16]-computed_constants[17]-constants[72])/12.861)
    algebraic[49] = 1.0/(0.36*(algebraic[8]+148.8-computed_constants[16]-computed_constants[17])/(exp(0.066*(algebraic[8]+148.8-computed_constants[16]-computed_constants[17]))-1.0)+0.1*(algebraic[8]+87.3-computed_constants[16]-computed_constants[17])/(1.0-exp(-0.2*(algebraic[8]+87.3-computed_constants[16]-computed_constants[17]))))-0.054
    rates[16] = (algebraic[50]-states[16])/algebraic[49]
    algebraic[54] = 1.0/(1.0+exp(-(algebraic[8]+42.0504)/8.3106))
    algebraic[55] = algebraic[8]+41.0
    algebraic[56] = 2000.0 if lt_func(fabs(algebraic[55]), constants[75]) else 200.0*algebraic[55]/(1.0-exp(-0.1*algebraic[55]))
    algebraic[57] = 8000.0*exp(-0.056*(algebraic[8]+66.0))
    algebraic[58] = 1.0/(algebraic[56]+algebraic[57])
    rates[18] = (algebraic[54]-states[18])/algebraic[58]
    algebraic[59] = 1.0/(1.0+exp((algebraic[8]+69.804)/4.4565))
    algebraic[60] = 20.0*exp(-0.125*(algebraic[8]+75.0))
    algebraic[61] = 2000.0/(320.0*exp(-0.1*(algebraic[8]+75.0))+1.0)
    algebraic[62] = 1.0/(algebraic[60]+algebraic[61])
    rates[17] = (algebraic[59]-states[17])/algebraic[62]
    algebraic[63] = 1.0/(1.0+exp((algebraic[8]+6.0)/-8.6))
    algebraic[64] = 0.009/(1.0+exp((algebraic[8]+5.0)/12.0))+0.0005
    rates[20] = (algebraic[63]-states[20])/algebraic[64]
    algebraic[65] = 1.0/(1.0+exp((algebraic[8]+7.5)/10.0))
    algebraic[66] = 0.59/(1.0+exp((algebraic[8]+60.0)/10.0))+3.05
    rates[19] = (algebraic[65]-states[19])/algebraic[66]
    algebraic[68] = 1.0/(1.0+exp(-(algebraic[8]-constants[78]-computed_constants[20])/(constants[79]*(1.0+computed_constants[21]/100.0))))
    algebraic[72] = -41.80001 if eq_func(algebraic[8], -41.8) else 0.0 if eq_func(algebraic[8], 0.0) else -6.80001 if eq_func(algebraic[8], -6.8) else algebraic[8]
    algebraic[70] = -0.02839*(algebraic[72]+41.8)/(exp(-(algebraic[72]+41.8)/2.5)-1.0)-0.0849*(algebraic[72]+6.8)/(exp(-(algebraic[72]+6.8)/4.8)-1.0)
    algebraic[73] = -1.80001 if eq_func(algebraic[8], -1.8) else algebraic[8]
    algebraic[71] = 0.01143*(algebraic[73]+1.8)/(exp((algebraic[73]+1.8)/2.5)-1.0)
    algebraic[69] = 0.001/(algebraic[70]+algebraic[71])
    rates[23] = (algebraic[68]-states[23])/algebraic[69]
    algebraic[74] = 1.0/(1.0+exp((algebraic[8]+37.4+constants[80])/(5.3+constants[81])))
    algebraic[75] = 0.001*(44.3+230.0*exp(-pow((algebraic[8]+36.0)/10.0, 2.0)))
    rates[22] = (algebraic[74]-states[22])/algebraic[75]
    algebraic[76] = constants[82]/(constants[82]+states[0])
    algebraic[77] = 0.001*algebraic[76]/constants[83]
    rates[21] = (algebraic[76]-states[21])/algebraic[77]
    algebraic[78] = 1.0/(1.0+exp(-(algebraic[8]+38.3)/5.5))
    algebraic[79] = 0.001/(1.068*exp((algebraic[8]+38.3)/30.0)+1.068*exp(-(algebraic[8]+38.3)/30.0))
    rates[25] = (algebraic[78]-states[25])/algebraic[79]
    algebraic[80] = 1.0/(1.0+exp((algebraic[8]+58.7)/3.8))
    algebraic[81] = 1.0/(16.67*exp(-(algebraic[8]+75.0)/83.3)+16.67*exp((algebraic[8]+75.0)/15.38))+constants[85]
    rates[24] = (algebraic[80]-states[24])/algebraic[81]
    algebraic[82] = 1.0/(1.0+exp((algebraic[8]+49.0)/13.0))
    algebraic[83] = 0.001*0.6*(65.17/(0.57*exp(-0.08*(algebraic[8]+44.0))+0.065*exp(0.1*(algebraic[8]+45.93)))+10.1)
    rates[27] = (algebraic[82]-states[27])/algebraic[83]
    algebraic[84] = 1.0/(1.0+exp(-(algebraic[8]-19.3)/15.0))
    algebraic[85] = 0.001*0.66*1.4*(15.59/(1.037*exp(0.09*(algebraic[8]+30.61))+0.369*exp(-0.12*(algebraic[8]+23.84)))+2.98)
    rates[26] = (algebraic[84]-states[26])/algebraic[85]
    algebraic[88] = 1.0/(1.0+exp(-(algebraic[8]+10.0144)/7.6607))
    algebraic[89] = 0.84655354/(4.2*exp(algebraic[8]/17.0)+0.15*exp(-algebraic[8]/21.6))
    rates[30] = (algebraic[88]-states[30])/algebraic[89]
    algebraic[90] = 1.0/(30.0*exp(algebraic[8]/10.0)+exp(-algebraic[8]/12.0))
    rates[29] = (algebraic[88]-states[29])/algebraic[90]
    algebraic[92] = 1.0/(1.0+exp((algebraic[8]+28.6)/17.1))
    algebraic[91] = 1.0/(100.0*exp(-algebraic[8]/54.645)+656.0*exp(algebraic[8]/106.157))
    rates[28] = (algebraic[92]-states[28])/algebraic[91]
    algebraic[94] = sqrt(1.0/(1.0+exp(-(algebraic[8]+0.6383-computed_constants[23])/10.7071)))
    algebraic[96] = 28.0/(1.0+exp(-(algebraic[8]-40.0-computed_constants[23])/3.0))
    algebraic[97] = 1.0*exp(-(algebraic[8]-computed_constants[23]-5.0)/25.0)
    algebraic[95] = 1.0/(algebraic[96]+algebraic[97])
    rates[31] = (algebraic[94]-states[31])/algebraic[95]
    algebraic[98] = 10.0*exp(0.0133*(algebraic[8]+40.0))
    algebraic[99] = computed_constants[24]/(computed_constants[24]+algebraic[98])
    algebraic[100] = 1.0/(computed_constants[24]+algebraic[98])
    rates[32] = (algebraic[99]-states[32])/algebraic[100]


def compute_variables(voi, states, rates, constants, computed_constants, algebraic):
    algebraic[1] = states[1]
    algebraic[0] = computed_constants[0]*log(constants[2]/algebraic[1])
    algebraic[2] = 0.5*computed_constants[0]*log(constants[5]/states[0])
    algebraic[8] = algebraic[47] if geq_func(constants[63], 1.0) else states[15]
    algebraic[5] = computed_constants[4]*constants[10]*pow(1.0+pow(constants[9]/constants[3], 1.2), -1.0)*pow(1.0+pow(constants[8]/algebraic[1], 1.3), -1.0)*pow(1.0+exp(-(algebraic[8]-algebraic[0]+110.0)/20.0), -1.0)
    algebraic[21] = 1.0+constants[5]/constants[21]*(1.0+exp(constants[22]*algebraic[8]/computed_constants[0]))+constants[2]/constants[23]*(1.0+constants[2]/constants[24]*(1.0+constants[2]/constants[20]))
    algebraic[10] = constants[5]/constants[21]*exp(constants[22]*algebraic[8]/computed_constants[0])/algebraic[21]
    algebraic[20] = 1.0+states[0]/constants[14]*(1.0+exp(-constants[15]*algebraic[8]/computed_constants[0])+algebraic[1]/constants[19])+algebraic[1]/constants[16]*(1.0+algebraic[1]/constants[17]*(1.0+algebraic[1]/constants[13]))
    algebraic[12] = states[0]/constants[14]*exp(-constants[15]*algebraic[8]/computed_constants[0])/algebraic[20]
    algebraic[17] = algebraic[1]/(constants[13]+algebraic[1])
    algebraic[18] = exp(constants[18]*algebraic[8]/(2.0*computed_constants[0]))
    algebraic[15] = exp(-constants[18]*algebraic[8]/(2.0*computed_constants[0]))
    algebraic[19] = algebraic[1]/constants[16]*algebraic[1]/constants[17]*(1.0+algebraic[1]/constants[13])*exp(constants[18]*algebraic[8]/(2.0*computed_constants[0]))/algebraic[20]
    algebraic[9] = algebraic[18]*algebraic[17]*(algebraic[19]+algebraic[12])+algebraic[15]*algebraic[12]*(computed_constants[5]+algebraic[18])
    algebraic[16] = constants[2]/constants[23]*constants[2]/constants[24]*(1.0+constants[2]/constants[20])*exp(-constants[18]*algebraic[8]/(2.0*computed_constants[0]))/algebraic[21]
    algebraic[11] = algebraic[15]*computed_constants[5]*(algebraic[16]+algebraic[10])+algebraic[10]*algebraic[18]*(algebraic[17]+algebraic[15])
    algebraic[13] = algebraic[16]*computed_constants[5]*(algebraic[19]+algebraic[12])+algebraic[19]*algebraic[10]*(computed_constants[5]+algebraic[18])
    algebraic[14] = algebraic[19]*algebraic[17]*(algebraic[16]+algebraic[10])+algebraic[12]*algebraic[16]*(algebraic[17]+algebraic[15])
    algebraic[4] = (1.0-constants[11])*constants[12]*(algebraic[9]*algebraic[10]-algebraic[11]*algebraic[12])/(algebraic[11]+algebraic[9]+algebraic[14]+algebraic[13])
    algebraic[22] = constants[25]*states[3]*(states[2]-states[0])
    algebraic[23] = states[2]-states[0]
    algebraic[24] = constants[26]-(constants[26]-constants[27])/(1.0+pow(constants[28]/states[2], constants[29]))
    algebraic[25] = constants[30]/algebraic[24]
    algebraic[26] = constants[31]*algebraic[24]
    algebraic[27] = states[4]+states[3]+states[6]+states[5]
    algebraic[28] = (states[0]-states[7])/constants[35]
    algebraic[29] = computed_constants[7]/(1.0+exp((-states[7]+constants[36])/constants[37]))
    algebraic[30] = (states[8]-states[2])/constants[38]
    algebraic[31] = constants[39]*states[7]*(1.0-states[9])-constants[40]*states[9]
    algebraic[32] = constants[41]*states[7]*(1.0-(states[10]+states[11]))-constants[42]*states[10]
    algebraic[33] = constants[43]*constants[44]*(1.0-(states[10]+states[11]))-constants[45]*states[11]
    algebraic[34] = constants[46]*states[7]*(1.0-states[12])-constants[47]*states[12]
    algebraic[35] = constants[46]*states[0]*(1.0-states[13])-constants[47]*states[13]
    algebraic[36] = constants[48]*states[2]*(1.0-states[14])-constants[49]*states[14]
    algebraic[7] = states[16]*computed_constants[14]*(algebraic[8]-algebraic[0])*(1.0-constants[71])
    algebraic[48] = states[16]*computed_constants[15]*(algebraic[8]-computed_constants[1])*(1.0-constants[71])
    algebraic[40] = algebraic[7]+algebraic[48]
    algebraic[41] = constants[76]*states[20]*states[19]*(algebraic[8]-computed_constants[1])
    algebraic[42] = constants[89]*constants[90]*(algebraic[8]-computed_constants[1])*(1.0+exp((algebraic[8]+20.0)/20.0))*states[32] if gt_func(constants[0], 0.0) else 0.0
    algebraic[38] = 2.0*constants[84]*algebraic[8]/(computed_constants[0]*(1.0-exp(-1.0*algebraic[8]*2.0/computed_constants[0])))*(states[0]-constants[5]*exp(-2.0*algebraic[8]/computed_constants[0]))*states[25]*states[24]
    algebraic[37] = 2.0*constants[77]*(algebraic[8]-0.0)/(computed_constants[0]*(1.0-exp(-1.0*(algebraic[8]-0.0)*2.0/computed_constants[0])))*(states[0]-constants[5]*exp(-2.0*(algebraic[8]-0.0)/computed_constants[0]))*states[23]*states[22]*states[21]
    algebraic[6] = 0.0000185*constants[77]*(algebraic[8]-0.0)/(computed_constants[0]*(1.0-exp(-1.0*(algebraic[8]-0.0)/computed_constants[0])))*(algebraic[1]-constants[2]*exp(-1.0*(algebraic[8]-0.0)/computed_constants[0]))*states[23]*states[22]*states[21]
    algebraic[67] = 0.000365*constants[77]*(algebraic[8]-0.0)/(computed_constants[0]*(1.0-exp(-1.0*(algebraic[8]-0.0)/computed_constants[0])))*(constants[4]-constants[3]*exp(-1.0*(algebraic[8]-0.0)/computed_constants[0]))*states[23]*states[22]*states[21]
    algebraic[43] = (algebraic[37]+algebraic[67]+algebraic[6])*(1.0-computed_constants[19])*1.0*computed_constants[18]
    algebraic[51] = computed_constants[0]*log((constants[2]+0.12*constants[3])/(algebraic[1]+0.12*constants[4]))
    algebraic[52] = constants[73]*pow(states[18], 3.0)*states[17]*(algebraic[8]-algebraic[51])
    algebraic[53] = constants[74]*pow(states[18], 3.0)*(algebraic[8]-algebraic[51])
    algebraic[3] = algebraic[52]+algebraic[53]
    algebraic[44] = constants[86]*(algebraic[8]-computed_constants[1])*states[27]*states[26]
    algebraic[93] = computed_constants[0]*log((constants[3]+0.12*constants[2])/(constants[4]+0.12*algebraic[1]))
    algebraic[45] = computed_constants[22]*(algebraic[8]-algebraic[93])*pow(states[31], 2.0)
    algebraic[46] = constants[87]*(algebraic[8]-computed_constants[1])*(0.9*states[29]+0.1*states[30])*states[28]
    algebraic[39] = algebraic[40]+algebraic[46]+algebraic[45]+algebraic[44]+algebraic[5]+algebraic[4]+algebraic[3]+algebraic[43]+algebraic[38]+algebraic[42]+algebraic[41]
    algebraic[49] = 1.0/(0.36*(algebraic[8]+148.8-computed_constants[16]-computed_constants[17])/(exp(0.066*(algebraic[8]+148.8-computed_constants[16]-computed_constants[17]))-1.0)+0.1*(algebraic[8]+87.3-computed_constants[16]-computed_constants[17])/(1.0-exp(-0.2*(algebraic[8]+87.3-computed_constants[16]-computed_constants[17]))))-0.054
    algebraic[50] = 0.01329+0.99921/(1.0+exp((algebraic[8]+97.134-computed_constants[16]-computed_constants[17]-constants[72])/8.1752)) if lt_func(algebraic[8], -(80.0-computed_constants[16]-computed_constants[17]-constants[72])) else 0.0002501*exp(-(algebraic[8]-computed_constants[16]-computed_constants[17]-constants[72])/12.861)
    algebraic[54] = 1.0/(1.0+exp(-(algebraic[8]+42.0504)/8.3106))
    algebraic[55] = algebraic[8]+41.0
    algebraic[56] = 2000.0 if lt_func(fabs(algebraic[55]), constants[75]) else 200.0*algebraic[55]/(1.0-exp(-0.1*algebraic[55]))
    algebraic[57] = 8000.0*exp(-0.056*(algebraic[8]+66.0))
    algebraic[58] = 1.0/(algebraic[56]+algebraic[57])
    algebraic[59] = 1.0/(1.0+exp((algebraic[8]+69.804)/4.4565))
    algebraic[60] = 20.0*exp(-0.125*(algebraic[8]+75.0))
    algebraic[61] = 2000.0/(320.0*exp(-0.1*(algebraic[8]+75.0))+1.0)
    algebraic[62] = 1.0/(algebraic[60]+algebraic[61])
    algebraic[63] = 1.0/(1.0+exp((algebraic[8]+6.0)/-8.6))
    algebraic[64] = 0.009/(1.0+exp((algebraic[8]+5.0)/12.0))+0.0005
    algebraic[65] = 1.0/(1.0+exp((algebraic[8]+7.5)/10.0))
    algebraic[66] = 0.59/(1.0+exp((algebraic[8]+60.0)/10.0))+3.05
    algebraic[68] = 1.0/(1.0+exp(-(algebraic[8]-constants[78]-computed_constants[20])/(constants[79]*(1.0+computed_constants[21]/100.0))))
    algebraic[72] = -41.80001 if eq_func(algebraic[8], -41.8) else 0.0 if eq_func(algebraic[8], 0.0) else -6.80001 if eq_func(algebraic[8], -6.8) else algebraic[8]
    algebraic[70] = -0.02839*(algebraic[72]+41.8)/(exp(-(algebraic[72]+41.8)/2.5)-1.0)-0.0849*(algebraic[72]+6.8)/(exp(-(algebraic[72]+6.8)/4.8)-1.0)
    algebraic[73] = -1.80001 if eq_func(algebraic[8], -1.8) else algebraic[8]
    algebraic[71] = 0.01143*(algebraic[73]+1.8)/(exp((algebraic[73]+1.8)/2.5)-1.0)
    algebraic[69] = 0.001/(algebraic[70]+algebraic[71])
    algebraic[74] = 1.0/(1.0+exp((algebraic[8]+37.4+constants[80])/(5.3+constants[81])))
    algebraic[75] = 0.001*(44.3+230.0*exp(-pow((algebraic[8]+36.0)/10.0, 2.0)))
    algebraic[76] = constants[82]/(constants[82]+states[0])
    algebraic[77] = 0.001*algebraic[76]/constants[83]
    algebraic[78] = 1.0/(1.0+exp(-(algebraic[8]+38.3)/5.5))
    algebraic[79] = 0.001/(1.068*exp((algebraic[8]+38.3)/30.0)+1.068*exp(-(algebraic[8]+38.3)/30.0))
    algebraic[80] = 1.0/(1.0+exp((algebraic[8]+58.7)/3.8))
    algebraic[81] = 1.0/(16.67*exp(-(algebraic[8]+75.0)/83.3)+16.67*exp((algebraic[8]+75.0)/15.38))+constants[85]
    algebraic[82] = 1.0/(1.0+exp((algebraic[8]+49.0)/13.0))
    algebraic[83] = 0.001*0.6*(65.17/(0.57*exp(-0.08*(algebraic[8]+44.0))+0.065*exp(0.1*(algebraic[8]+45.93)))+10.1)
    algebraic[84] = 1.0/(1.0+exp(-(algebraic[8]-19.3)/15.0))
    algebraic[85] = 0.001*0.66*1.4*(15.59/(1.037*exp(0.09*(algebraic[8]+30.61))+0.369*exp(-0.12*(algebraic[8]+23.84)))+2.98)
    algebraic[86] = 1.0/(1.0+exp(-(algebraic[8]+23.2)/6.6))/(0.84655354/(37.2*exp(algebraic[8]/11.9)+0.96*exp(-algebraic[8]/18.5)))
    algebraic[87] = 4.0*((37.2*exp(algebraic[8]/15.9)+0.96*exp(-algebraic[8]/22.5))/0.84655354-1.0/(1.0+exp(-(algebraic[8]+23.2)/10.6))/(0.84655354/(37.2*exp(algebraic[8]/15.9)+0.96*exp(-algebraic[8]/22.5))))
    algebraic[88] = 1.0/(1.0+exp(-(algebraic[8]+10.0144)/7.6607))
    algebraic[89] = 0.84655354/(4.2*exp(algebraic[8]/17.0)+0.15*exp(-algebraic[8]/21.6))
    algebraic[90] = 1.0/(30.0*exp(algebraic[8]/10.0)+exp(-algebraic[8]/12.0))
    algebraic[91] = 1.0/(100.0*exp(-algebraic[8]/54.645)+656.0*exp(algebraic[8]/106.157))
    algebraic[92] = 1.0/(1.0+exp((algebraic[8]+28.6)/17.1))
    algebraic[94] = sqrt(1.0/(1.0+exp(-(algebraic[8]+0.6383-computed_constants[23])/10.7071)))
    algebraic[96] = 28.0/(1.0+exp(-(algebraic[8]-40.0-computed_constants[23])/3.0))
    algebraic[97] = 1.0*exp(-(algebraic[8]-computed_constants[23]-5.0)/25.0)
    algebraic[95] = 1.0/(algebraic[96]+algebraic[97])
    algebraic[98] = 10.0*exp(0.0133*(algebraic[8]+40.0))
    algebraic[99] = computed_constants[24]/(computed_constants[24]+algebraic[98])
    algebraic[100] = 1.0/(computed_constants[24]+algebraic[98])

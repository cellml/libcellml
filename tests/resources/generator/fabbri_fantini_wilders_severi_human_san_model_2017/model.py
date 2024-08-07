# The content of this file was generated using the Python profile of libCellML 0.5.0.

from enum import Enum
from math import *


__version__ = "0.4.0"
LIBCELLML_VERSION = "0.5.0"

STATE_COUNT = 33
CONSTANT_COUNT = 0
COMPUTED_CONSTANT_COUNT = 0
ALGEBRAIC_COUNT = 217


class VariableType(Enum):
    VARIABLE_OF_INTEGRATION = 0
    STATE = 1
    CONSTANT = 2
    COMPUTED_CONSTANT = 3
    ALGEBRAIC = 4


VOI_INFO = {"name": "time", "units": "second", "component": "environment", "type": VariableType.VARIABLE_OF_INTEGRATION}

STATE_INFO = [
    {"name": "Ca_sub", "units": "millimolar", "component": "Ca_dynamics", "type": VariableType.STATE},
    {"name": "Nai_", "units": "millimolar", "component": "Nai_concentration", "type": VariableType.STATE},
    {"name": "Ca_jsr", "units": "millimolar", "component": "Ca_dynamics", "type": VariableType.STATE},
    {"name": "O", "units": "dimensionless", "component": "Ca_SR_release", "type": VariableType.STATE},
    {"name": "R", "units": "dimensionless", "component": "Ca_SR_release", "type": VariableType.STATE},
    {"name": "RI", "units": "dimensionless", "component": "Ca_SR_release", "type": VariableType.STATE},
    {"name": "I", "units": "dimensionless", "component": "Ca_SR_release", "type": VariableType.STATE},
    {"name": "Cai", "units": "millimolar", "component": "Ca_dynamics", "type": VariableType.STATE},
    {"name": "Ca_nsr", "units": "millimolar", "component": "Ca_dynamics", "type": VariableType.STATE},
    {"name": "fTC", "units": "dimensionless", "component": "Ca_buffering", "type": VariableType.STATE},
    {"name": "fTMC", "units": "dimensionless", "component": "Ca_buffering", "type": VariableType.STATE},
    {"name": "fTMM", "units": "dimensionless", "component": "Ca_buffering", "type": VariableType.STATE},
    {"name": "fCMi", "units": "dimensionless", "component": "Ca_buffering", "type": VariableType.STATE},
    {"name": "fCMs", "units": "dimensionless", "component": "Ca_buffering", "type": VariableType.STATE},
    {"name": "fCQ", "units": "dimensionless", "component": "Ca_buffering", "type": VariableType.STATE},
    {"name": "V_ode", "units": "millivolt", "component": "Membrane", "type": VariableType.STATE},
    {"name": "y", "units": "dimensionless", "component": "i_f_y_gate", "type": VariableType.STATE},
    {"name": "h", "units": "dimensionless", "component": "i_Na_h_gate", "type": VariableType.STATE},
    {"name": "m", "units": "dimensionless", "component": "i_Na_m_gate", "type": VariableType.STATE},
    {"name": "s_Kur", "units": "dimensionless", "component": "i_Kur_sKur_gate", "type": VariableType.STATE},
    {"name": "r_Kur", "units": "dimensionless", "component": "i_Kur_rKur_gate", "type": VariableType.STATE},
    {"name": "fCa", "units": "dimensionless", "component": "i_CaL_fCa_gate", "type": VariableType.STATE},
    {"name": "fL", "units": "dimensionless", "component": "i_CaL_fL_gate", "type": VariableType.STATE},
    {"name": "dL", "units": "dimensionless", "component": "i_CaL_dL_gate", "type": VariableType.STATE},
    {"name": "fT", "units": "dimensionless", "component": "i_CaT_fT_gate", "type": VariableType.STATE},
    {"name": "dT", "units": "dimensionless", "component": "i_CaT_dT_gate", "type": VariableType.STATE},
    {"name": "r", "units": "dimensionless", "component": "i_to_r_gate", "type": VariableType.STATE},
    {"name": "q", "units": "dimensionless", "component": "i_to_q_gate", "type": VariableType.STATE},
    {"name": "piy", "units": "dimensionless", "component": "i_Kr_pi_gate", "type": VariableType.STATE},
    {"name": "paF", "units": "dimensionless", "component": "i_Kr_pa_gate", "type": VariableType.STATE},
    {"name": "paS", "units": "dimensionless", "component": "i_Kr_pa_gate", "type": VariableType.STATE},
    {"name": "n", "units": "dimensionless", "component": "i_Ks_n_gate", "type": VariableType.STATE},
    {"name": "a", "units": "dimensionless", "component": "i_KACh_a_gate", "type": VariableType.STATE}
]

VARIABLE_INFO = [
    {"name": "ACh", "units": "millimolar", "component": "Rate_modulation_experiments", "type": VariableType.CONSTANT},
    {"name": "Iso_1_uM", "units": "dimensionless", "component": "Rate_modulation_experiments", "type": VariableType.CONSTANT},
    {"name": "E_Na", "units": "millivolt", "component": "Ionic_values", "type": VariableType.ALGEBRAIC},
    {"name": "RTONF", "units": "millivolt", "component": "Membrane", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "Nao", "units": "millimolar", "component": "Ionic_values", "type": VariableType.CONSTANT},
    {"name": "Nai", "units": "millimolar", "component": "Nai_concentration", "type": VariableType.ALGEBRAIC},
    {"name": "E_K", "units": "millivolt", "component": "Ionic_values", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "Ko", "units": "millimolar", "component": "Ionic_values", "type": VariableType.CONSTANT},
    {"name": "Ki", "units": "millimolar", "component": "Ionic_values", "type": VariableType.CONSTANT},
    {"name": "E_Ca", "units": "millivolt", "component": "Ionic_values", "type": VariableType.ALGEBRAIC},
    {"name": "Cao", "units": "millimolar", "component": "Ionic_values", "type": VariableType.CONSTANT},
    {"name": "Nai_clamp", "units": "dimensionless", "component": "Nai_concentration", "type": VariableType.CONSTANT},
    {"name": "i_Na", "units": "nanoA", "component": "i_Na", "type": VariableType.ALGEBRAIC},
    {"name": "i_NaCa", "units": "nanoA", "component": "i_NaCa", "type": VariableType.ALGEBRAIC},
    {"name": "i_NaK", "units": "nanoA", "component": "i_NaK", "type": VariableType.ALGEBRAIC},
    {"name": "i_siNa", "units": "nanoA", "component": "i_CaL", "type": VariableType.ALGEBRAIC},
    {"name": "i_fNa", "units": "nanoA", "component": "i_f", "type": VariableType.ALGEBRAIC},
    {"name": "F", "units": "coulomb_per_mole", "component": "Membrane", "type": VariableType.CONSTANT},
    {"name": "V_i", "units": "millimetre3", "component": "Cell_parameters", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "V_sub", "units": "millimetre3", "component": "Cell_parameters", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "Iso_increase", "units": "dimensionless", "component": "i_NaK", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "V", "units": "millivolt", "component": "Membrane", "type": VariableType.ALGEBRAIC},
    {"name": "Km_Nap", "units": "millimolar", "component": "i_NaK", "type": VariableType.CONSTANT},
    {"name": "Km_Kp", "units": "millimolar", "component": "i_NaK", "type": VariableType.CONSTANT},
    {"name": "i_NaK_max", "units": "nanoA", "component": "i_NaK", "type": VariableType.CONSTANT},
    {"name": "blockade_NaCa", "units": "dimensionless", "component": "i_NaCa", "type": VariableType.CONSTANT},
    {"name": "x2", "units": "dimensionless", "component": "i_NaCa", "type": VariableType.ALGEBRAIC},
    {"name": "k21", "units": "dimensionless", "component": "i_NaCa", "type": VariableType.ALGEBRAIC},
    {"name": "x1", "units": "dimensionless", "component": "i_NaCa", "type": VariableType.ALGEBRAIC},
    {"name": "k12", "units": "dimensionless", "component": "i_NaCa", "type": VariableType.ALGEBRAIC},
    {"name": "K_NaCa", "units": "nanoA", "component": "i_NaCa", "type": VariableType.CONSTANT},
    {"name": "x4", "units": "dimensionless", "component": "i_NaCa", "type": VariableType.ALGEBRAIC},
    {"name": "x3", "units": "dimensionless", "component": "i_NaCa", "type": VariableType.ALGEBRAIC},
    {"name": "k41", "units": "dimensionless", "component": "i_NaCa", "type": VariableType.ALGEBRAIC},
    {"name": "k23", "units": "dimensionless", "component": "i_NaCa", "type": VariableType.ALGEBRAIC},
    {"name": "k34", "units": "dimensionless", "component": "i_NaCa", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "k43", "units": "dimensionless", "component": "i_NaCa", "type": VariableType.ALGEBRAIC},
    {"name": "k32", "units": "dimensionless", "component": "i_NaCa", "type": VariableType.ALGEBRAIC},
    {"name": "k14", "units": "dimensionless", "component": "i_NaCa", "type": VariableType.ALGEBRAIC},
    {"name": "K3ni", "units": "millimolar", "component": "i_NaCa", "type": VariableType.CONSTANT},
    {"name": "Kci", "units": "millimolar", "component": "i_NaCa", "type": VariableType.CONSTANT},
    {"name": "Qci", "units": "dimensionless", "component": "i_NaCa", "type": VariableType.CONSTANT},
    {"name": "di", "units": "dimensionless", "component": "i_NaCa", "type": VariableType.ALGEBRAIC},
    {"name": "K1ni", "units": "millimolar", "component": "i_NaCa", "type": VariableType.CONSTANT},
    {"name": "K2ni", "units": "millimolar", "component": "i_NaCa", "type": VariableType.CONSTANT},
    {"name": "Qn", "units": "dimensionless", "component": "i_NaCa", "type": VariableType.CONSTANT},
    {"name": "Kcni", "units": "millimolar", "component": "i_NaCa", "type": VariableType.CONSTANT},
    {"name": "K3no", "units": "millimolar", "component": "i_NaCa", "type": VariableType.CONSTANT},
    {"name": "Kco", "units": "millimolar", "component": "i_NaCa", "type": VariableType.CONSTANT},
    {"name": "Qco", "units": "dimensionless", "component": "i_NaCa", "type": VariableType.CONSTANT},
    {"name": "do", "units": "dimensionless", "component": "i_NaCa", "type": VariableType.ALGEBRAIC},
    {"name": "K1no", "units": "millimolar", "component": "i_NaCa", "type": VariableType.CONSTANT},
    {"name": "K2no", "units": "millimolar", "component": "i_NaCa", "type": VariableType.CONSTANT},
    {"name": "j_SRCarel", "units": "millimolar_per_second", "component": "Ca_SR_release", "type": VariableType.ALGEBRAIC},
    {"name": "ks", "units": "per_second", "component": "Ca_SR_release", "type": VariableType.CONSTANT},
    {"name": "diff", "units": "millimolar", "component": "Ca_SR_release", "type": VariableType.ALGEBRAIC},
    {"name": "kCaSR", "units": "dimensionless", "component": "Ca_SR_release", "type": VariableType.ALGEBRAIC},
    {"name": "MaxSR", "units": "dimensionless", "component": "Ca_SR_release", "type": VariableType.CONSTANT},
    {"name": "MinSR", "units": "dimensionless", "component": "Ca_SR_release", "type": VariableType.CONSTANT},
    {"name": "EC50_SR", "units": "millimolar", "component": "Ca_SR_release", "type": VariableType.CONSTANT},
    {"name": "HSR", "units": "dimensionless", "component": "Ca_SR_release", "type": VariableType.CONSTANT},
    {"name": "koSRCa", "units": "per_millimolar2_second", "component": "Ca_SR_release", "type": VariableType.ALGEBRAIC},
    {"name": "koCa", "units": "per_millimolar2_second", "component": "Ca_SR_release", "type": VariableType.CONSTANT},
    {"name": "kiSRCa", "units": "per_millimolar_second", "component": "Ca_SR_release", "type": VariableType.ALGEBRAIC},
    {"name": "kiCa", "units": "per_millimolar_second", "component": "Ca_SR_release", "type": VariableType.CONSTANT},
    {"name": "kim", "units": "per_second", "component": "Ca_SR_release", "type": VariableType.CONSTANT},
    {"name": "kom", "units": "per_second", "component": "Ca_SR_release", "type": VariableType.CONSTANT},
    {"name": "P_tot", "units": "dimensionless", "component": "Ca_SR_release", "type": VariableType.ALGEBRAIC},
    {"name": "b_up", "units": "dimensionless", "component": "Ca_intracellular_fluxes", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "P_up", "units": "millimolar_per_second", "component": "Ca_intracellular_fluxes", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "P_up_basal", "units": "millimolar_per_second", "component": "Ca_intracellular_fluxes", "type": VariableType.CONSTANT},
    {"name": "j_Ca_dif", "units": "millimolar_per_second", "component": "Ca_intracellular_fluxes", "type": VariableType.ALGEBRAIC},
    {"name": "tau_dif_Ca", "units": "second", "component": "Ca_intracellular_fluxes", "type": VariableType.CONSTANT},
    {"name": "j_up", "units": "millimolar_per_second", "component": "Ca_intracellular_fluxes", "type": VariableType.ALGEBRAIC},
    {"name": "K_up", "units": "millimolar", "component": "Ca_intracellular_fluxes", "type": VariableType.CONSTANT},
    {"name": "slope_up", "units": "millimolar", "component": "Ca_intracellular_fluxes", "type": VariableType.CONSTANT},
    {"name": "j_tr", "units": "millimolar_per_second", "component": "Ca_intracellular_fluxes", "type": VariableType.ALGEBRAIC},
    {"name": "tau_tr", "units": "second", "component": "Ca_intracellular_fluxes", "type": VariableType.CONSTANT},
    {"name": "delta_fTC", "units": "per_second", "component": "Ca_buffering", "type": VariableType.ALGEBRAIC},
    {"name": "kf_TC", "units": "per_millimolar_second", "component": "Ca_buffering", "type": VariableType.CONSTANT},
    {"name": "kb_TC", "units": "per_second", "component": "Ca_buffering", "type": VariableType.CONSTANT},
    {"name": "delta_fTMC", "units": "per_second", "component": "Ca_buffering", "type": VariableType.ALGEBRAIC},
    {"name": "kf_TMC", "units": "per_millimolar_second", "component": "Ca_buffering", "type": VariableType.CONSTANT},
    {"name": "kb_TMC", "units": "per_second", "component": "Ca_buffering", "type": VariableType.CONSTANT},
    {"name": "delta_fTMM", "units": "per_second", "component": "Ca_buffering", "type": VariableType.ALGEBRAIC},
    {"name": "kf_TMM", "units": "per_millimolar_second", "component": "Ca_buffering", "type": VariableType.CONSTANT},
    {"name": "Mgi", "units": "millimolar", "component": "Ca_buffering", "type": VariableType.CONSTANT},
    {"name": "kb_TMM", "units": "per_second", "component": "Ca_buffering", "type": VariableType.CONSTANT},
    {"name": "delta_fCMi", "units": "per_second", "component": "Ca_buffering", "type": VariableType.ALGEBRAIC},
    {"name": "kf_CM", "units": "per_millimolar_second", "component": "Ca_buffering", "type": VariableType.CONSTANT},
    {"name": "kb_CM", "units": "per_second", "component": "Ca_buffering", "type": VariableType.CONSTANT},
    {"name": "delta_fCMs", "units": "per_second", "component": "Ca_buffering", "type": VariableType.ALGEBRAIC},
    {"name": "delta_fCQ", "units": "per_second", "component": "Ca_buffering", "type": VariableType.ALGEBRAIC},
    {"name": "kf_CQ", "units": "per_millimolar_second", "component": "Ca_buffering", "type": VariableType.CONSTANT},
    {"name": "kb_CQ", "units": "per_second", "component": "Ca_buffering", "type": VariableType.CONSTANT},
    {"name": "TC_tot", "units": "millimolar", "component": "Ca_buffering", "type": VariableType.CONSTANT},
    {"name": "TMC_tot", "units": "millimolar", "component": "Ca_buffering", "type": VariableType.CONSTANT},
    {"name": "CM_tot", "units": "millimolar", "component": "Ca_buffering", "type": VariableType.CONSTANT},
    {"name": "CQ_tot", "units": "millimolar", "component": "Ca_buffering", "type": VariableType.CONSTANT},
    {"name": "V_nsr", "units": "millimetre3", "component": "Cell_parameters", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "V_jsr", "units": "millimetre3", "component": "Cell_parameters", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "i_siCa", "units": "nanoA", "component": "i_CaL", "type": VariableType.ALGEBRAIC},
    {"name": "i_CaT", "units": "nanoA", "component": "i_CaT", "type": VariableType.ALGEBRAIC},
    {"name": "V_cell", "units": "millimetre3", "component": "Cell_parameters", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "L_cell", "units": "micrometre", "component": "Cell_parameters", "type": VariableType.CONSTANT},
    {"name": "R_cell", "units": "micrometre", "component": "Cell_parameters", "type": VariableType.CONSTANT},
    {"name": "L_sub", "units": "micrometre", "component": "Cell_parameters", "type": VariableType.CONSTANT},
    {"name": "V_jsr_part", "units": "dimensionless", "component": "Cell_parameters", "type": VariableType.CONSTANT},
    {"name": "V_i_part", "units": "dimensionless", "component": "Cell_parameters", "type": VariableType.CONSTANT},
    {"name": "V_nsr_part", "units": "dimensionless", "component": "Cell_parameters", "type": VariableType.CONSTANT},
    {"name": "i_tot", "units": "nanoA", "component": "Membrane", "type": VariableType.ALGEBRAIC},
    {"name": "i_f", "units": "nanoA", "component": "i_f", "type": VariableType.ALGEBRAIC},
    {"name": "i_Kur", "units": "nanoA", "component": "i_Kur", "type": VariableType.ALGEBRAIC},
    {"name": "i_KACh", "units": "nanoA", "component": "i_KACh", "type": VariableType.ALGEBRAIC},
    {"name": "i_CaL", "units": "nanoA", "component": "i_CaL", "type": VariableType.ALGEBRAIC},
    {"name": "i_to", "units": "nanoA", "component": "i_to", "type": VariableType.ALGEBRAIC},
    {"name": "i_Ks", "units": "nanoA", "component": "i_Ks", "type": VariableType.ALGEBRAIC},
    {"name": "i_Kr", "units": "nanoA", "component": "i_Kr", "type": VariableType.ALGEBRAIC},
    {"name": "C", "units": "microF", "component": "Membrane", "type": VariableType.CONSTANT},
    {"name": "R", "units": "joule_per_kilomole_kelvin", "component": "Membrane", "type": VariableType.CONSTANT},
    {"name": "T", "units": "kelvin", "component": "Membrane", "type": VariableType.CONSTANT},
    {"name": "V_clamp", "units": "millivolt", "component": "Voltage_clamp", "type": VariableType.ALGEBRAIC},
    {"name": "clamp_mode", "units": "dimensionless", "component": "Membrane", "type": VariableType.CONSTANT},
    {"name": "V_test", "units": "millivolt", "component": "Voltage_clamp", "type": VariableType.CONSTANT},
    {"name": "t_holding", "units": "second", "component": "Voltage_clamp", "type": VariableType.CONSTANT},
    {"name": "t_test", "units": "second", "component": "Voltage_clamp", "type": VariableType.CONSTANT},
    {"name": "V_holding", "units": "millivolt", "component": "Voltage_clamp", "type": VariableType.CONSTANT},
    {"name": "G_f", "units": "microS", "component": "i_f", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "g_f", "units": "microS", "component": "i_f", "type": VariableType.CONSTANT},
    {"name": "Km_f", "units": "millimolar", "component": "i_f", "type": VariableType.CONSTANT},
    {"name": "G_f_K", "units": "microS", "component": "i_f", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "alpha", "units": "dimensionless", "component": "i_f", "type": VariableType.CONSTANT},
    {"name": "G_f_Na", "units": "microS", "component": "i_f", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "g_f_Na", "units": "microS", "component": "i_f", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "g_f_K", "units": "microS", "component": "i_f", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "blockade", "units": "dimensionless", "component": "i_f", "type": VariableType.CONSTANT},
    {"name": "i_fK", "units": "nanoA", "component": "i_f", "type": VariableType.ALGEBRAIC},
    {"name": "ACh_shift", "units": "millivolt", "component": "i_f_y_gate", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "Iso_shift", "units": "millivolt", "component": "i_f_y_gate", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "tau_y", "units": "second", "component": "i_f_y_gate", "type": VariableType.ALGEBRAIC},
    {"name": "y_infinity", "units": "dimensionless", "component": "i_f_y_gate", "type": VariableType.ALGEBRAIC},
    {"name": "y_shift", "units": "millivolt", "component": "i_f_y_gate", "type": VariableType.CONSTANT},
    {"name": "E_mh", "units": "millivolt", "component": "i_Na", "type": VariableType.ALGEBRAIC},
    {"name": "i_Na_", "units": "nanoA", "component": "i_Na", "type": VariableType.ALGEBRAIC},
    {"name": "g_Na", "units": "microS", "component": "i_Na", "type": VariableType.CONSTANT},
    {"name": "i_Na_L", "units": "nanoA", "component": "i_Na", "type": VariableType.ALGEBRAIC},
    {"name": "g_Na_L", "units": "microS", "component": "i_Na", "type": VariableType.CONSTANT},
    {"name": "m_infinity", "units": "dimensionless", "component": "i_Na_m_gate", "type": VariableType.ALGEBRAIC},
    {"name": "E0_m", "units": "millivolt", "component": "i_Na_m_gate", "type": VariableType.ALGEBRAIC},
    {"name": "alpha_m", "units": "per_second", "component": "i_Na_m_gate", "type": VariableType.ALGEBRAIC},
    {"name": "delta_m", "units": "millivolt", "component": "i_Na_m_gate", "type": VariableType.CONSTANT},
    {"name": "beta_m", "units": "per_second", "component": "i_Na_m_gate", "type": VariableType.ALGEBRAIC},
    {"name": "tau_m", "units": "second", "component": "i_Na_m_gate", "type": VariableType.ALGEBRAIC},
    {"name": "h_infinity", "units": "dimensionless", "component": "i_Na_h_gate", "type": VariableType.ALGEBRAIC},
    {"name": "alpha_h", "units": "per_second", "component": "i_Na_h_gate", "type": VariableType.ALGEBRAIC},
    {"name": "beta_h", "units": "per_second", "component": "i_Na_h_gate", "type": VariableType.ALGEBRAIC},
    {"name": "tau_h", "units": "second", "component": "i_Na_h_gate", "type": VariableType.ALGEBRAIC},
    {"name": "g_Kur", "units": "microS", "component": "i_Kur", "type": VariableType.CONSTANT},
    {"name": "r_Kur_infinity", "units": "dimensionless", "component": "i_Kur_rKur_gate", "type": VariableType.ALGEBRAIC},
    {"name": "tau_r_Kur", "units": "second", "component": "i_Kur_rKur_gate", "type": VariableType.ALGEBRAIC},
    {"name": "s_Kur_infinity", "units": "dimensionless", "component": "i_Kur_sKur_gate", "type": VariableType.ALGEBRAIC},
    {"name": "tau_s_Kur", "units": "second", "component": "i_Kur_sKur_gate", "type": VariableType.ALGEBRAIC},
    {"name": "Iso_increase", "units": "dimensionless", "component": "i_CaL", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "P_CaL", "units": "nanoA_per_millimolar", "component": "i_CaL", "type": VariableType.CONSTANT},
    {"name": "i_siK", "units": "nanoA", "component": "i_CaL", "type": VariableType.ALGEBRAIC},
    {"name": "ACh_block", "units": "dimensionless", "component": "i_CaL", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "Iso_shift_dL", "units": "millivolt", "component": "i_CaL_dL_gate", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "Iso_slope_dL", "units": "dimensionless", "component": "i_CaL_dL_gate", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "dL_infinity", "units": "dimensionless", "component": "i_CaL_dL_gate", "type": VariableType.ALGEBRAIC},
    {"name": "V_dL", "units": "millivolt", "component": "i_CaL_dL_gate", "type": VariableType.CONSTANT},
    {"name": "k_dL", "units": "millivolt", "component": "i_CaL_dL_gate", "type": VariableType.CONSTANT},
    {"name": "tau_dL", "units": "second", "component": "i_CaL_dL_gate", "type": VariableType.ALGEBRAIC},
    {"name": "alpha_dL", "units": "per_second", "component": "i_CaL_dL_gate", "type": VariableType.ALGEBRAIC},
    {"name": "beta_dL", "units": "per_second", "component": "i_CaL_dL_gate", "type": VariableType.ALGEBRAIC},
    {"name": "adVm", "units": "millivolt", "component": "i_CaL_dL_gate", "type": VariableType.ALGEBRAIC},
    {"name": "bdVm", "units": "millivolt", "component": "i_CaL_dL_gate", "type": VariableType.ALGEBRAIC},
    {"name": "fL_infinity", "units": "dimensionless", "component": "i_CaL_fL_gate", "type": VariableType.ALGEBRAIC},
    {"name": "shift_fL", "units": "millivolt", "component": "i_CaL_fL_gate", "type": VariableType.CONSTANT},
    {"name": "k_fL", "units": "millivolt", "component": "i_CaL_fL_gate", "type": VariableType.CONSTANT},
    {"name": "tau_fL", "units": "second", "component": "i_CaL_fL_gate", "type": VariableType.ALGEBRAIC},
    {"name": "fCa_infinity", "units": "dimensionless", "component": "i_CaL_fCa_gate", "type": VariableType.ALGEBRAIC},
    {"name": "Km_fCa", "units": "millimolar", "component": "i_CaL_fCa_gate", "type": VariableType.CONSTANT},
    {"name": "tau_fCa", "units": "second", "component": "i_CaL_fCa_gate", "type": VariableType.ALGEBRAIC},
    {"name": "alpha_fCa", "units": "per_second", "component": "i_CaL_fCa_gate", "type": VariableType.CONSTANT},
    {"name": "P_CaT", "units": "nanoA_per_millimolar", "component": "i_CaT", "type": VariableType.CONSTANT},
    {"name": "dT_infinity", "units": "dimensionless", "component": "i_CaT_dT_gate", "type": VariableType.ALGEBRAIC},
    {"name": "tau_dT", "units": "second", "component": "i_CaT_dT_gate", "type": VariableType.ALGEBRAIC},
    {"name": "fT_infinity", "units": "dimensionless", "component": "i_CaT_fT_gate", "type": VariableType.ALGEBRAIC},
    {"name": "tau_fT", "units": "second", "component": "i_CaT_fT_gate", "type": VariableType.ALGEBRAIC},
    {"name": "offset_fT", "units": "second", "component": "i_CaT_fT_gate", "type": VariableType.CONSTANT},
    {"name": "g_to", "units": "microS", "component": "i_to", "type": VariableType.CONSTANT},
    {"name": "q_infinity", "units": "dimensionless", "component": "i_to_q_gate", "type": VariableType.ALGEBRAIC},
    {"name": "tau_q", "units": "second", "component": "i_to_q_gate", "type": VariableType.ALGEBRAIC},
    {"name": "r_infinity", "units": "dimensionless", "component": "i_to_r_gate", "type": VariableType.ALGEBRAIC},
    {"name": "tau_r", "units": "second", "component": "i_to_r_gate", "type": VariableType.ALGEBRAIC},
    {"name": "g_Kr", "units": "microS", "component": "i_Kr", "type": VariableType.CONSTANT},
    {"name": "alfapaF", "units": "per_second", "component": "i_Kr_pa_gate", "type": VariableType.ALGEBRAIC},
    {"name": "betapaF", "units": "per_second", "component": "i_Kr_pa_gate", "type": VariableType.ALGEBRAIC},
    {"name": "pa_infinity", "units": "dimensionless", "component": "i_Kr_pa_gate", "type": VariableType.ALGEBRAIC},
    {"name": "tau_paS", "units": "second", "component": "i_Kr_pa_gate", "type": VariableType.ALGEBRAIC},
    {"name": "tau_paF", "units": "second", "component": "i_Kr_pa_gate", "type": VariableType.ALGEBRAIC},
    {"name": "tau_pi", "units": "second", "component": "i_Kr_pi_gate", "type": VariableType.ALGEBRAIC},
    {"name": "pi_infinity", "units": "dimensionless", "component": "i_Kr_pi_gate", "type": VariableType.ALGEBRAIC},
    {"name": "g_Ks", "units": "microS", "component": "i_Ks", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "g_Ks_", "units": "microS", "component": "i_Ks", "type": VariableType.CONSTANT},
    {"name": "E_Ks", "units": "millivolt", "component": "i_Ks", "type": VariableType.ALGEBRAIC},
    {"name": "Iso_shift", "units": "millivolt", "component": "i_Ks_n_gate", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "n_infinity", "units": "dimensionless", "component": "i_Ks_n_gate", "type": VariableType.ALGEBRAIC},
    {"name": "tau_n", "units": "second", "component": "i_Ks_n_gate", "type": VariableType.ALGEBRAIC},
    {"name": "alpha_n", "units": "per_second", "component": "i_Ks_n_gate", "type": VariableType.ALGEBRAIC},
    {"name": "beta_n", "units": "per_second", "component": "i_Ks_n_gate", "type": VariableType.ALGEBRAIC},
    {"name": "ACh_on", "units": "dimensionless", "component": "i_KACh", "type": VariableType.CONSTANT},
    {"name": "g_KACh", "units": "microS", "component": "i_KACh", "type": VariableType.CONSTANT},
    {"name": "alpha_a", "units": "per_second", "component": "i_KACh_a_gate", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "beta_a", "units": "per_second", "component": "i_KACh_a_gate", "type": VariableType.ALGEBRAIC},
    {"name": "a_infinity", "units": "dimensionless", "component": "i_KACh_a_gate", "type": VariableType.ALGEBRAIC},
    {"name": "tau_a", "units": "second", "component": "i_KACh_a_gate", "type": VariableType.ALGEBRAIC}
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


def create_variables_array():
    return [nan]*VARIABLE_COUNT


def initialise_variables(states, rates, constants):
    variables[0] = 0.0
    variables[1] = 0.0
    variables[4] = 140.0
    variables[7] = 5.4
    variables[8] = 140.0
    variables[10] = 1.8
    variables[11] = 1.0
    variables[17] = 96485.3415
    variables[22] = 14.0
    variables[23] = 1.4
    variables[24] = 0.08105
    variables[25] = 0.0
    variables[30] = 3.343
    variables[39] = 26.44
    variables[40] = 0.0207
    variables[41] = 0.1369
    variables[43] = 395.3
    variables[44] = 2.289
    variables[45] = 0.4315
    variables[46] = 26.44
    variables[47] = 4.663
    variables[48] = 3.663
    variables[49] = 0.0
    variables[51] = 1628.0
    variables[52] = 561.4
    variables[54] = 148041085.1
    variables[57] = 15.0
    variables[58] = 1.0
    variables[59] = 0.45
    variables[60] = 2.5
    variables[62] = 10000.0
    variables[64] = 500.0
    variables[65] = 5.0
    variables[66] = 660.0
    variables[70] = 5.0
    variables[72] = 5.469e-5
    variables[74] = 0.000286113
    variables[75] = 5.0e-5
    variables[77] = 0.04
    variables[79] = 88800.0
    variables[80] = 446.0
    variables[82] = 227700.0
    variables[83] = 7.51
    variables[85] = 2277.0
    variables[86] = 2.5
    variables[87] = 751.0
    variables[89] = 1.642e6
    variables[90] = 542.0
    variables[93] = 175.4
    variables[94] = 445.0
    variables[95] = 0.031
    variables[96] = 0.062
    variables[97] = 0.045
    variables[98] = 10.0
    variables[104] = 67.0
    variables[105] = 3.9
    variables[106] = 0.02
    variables[107] = 0.0012
    variables[108] = 0.46
    variables[109] = 0.0116
    variables[118] = 5.7e-5
    variables[119] = 8314.472
    variables[120] = 310.0
    variables[122] = 0.0
    variables[123] = -35.0
    variables[124] = 0.5
    variables[125] = 0.5
    variables[126] = -45.0
    variables[128] = 0.00427
    variables[129] = 45.0
    variables[131] = 0.5927
    variables[135] = 0.0
    variables[141] = 0.0
    variables[144] = 0.0223
    variables[146] = 0.0
    variables[150] = 1.0e-5
    variables[157] = 0.1539e-3
    variables[163] = 0.4578
    variables[169] = -16.4508
    variables[170] = 4.3371
    variables[177] = 0.0
    variables[178] = 0.0
    variables[181] = 0.000338
    variables[183] = 0.0075
    variables[184] = 0.04132
    variables[189] = 0.0
    variables[190] = 3.5e-3
    variables[195] = 0.00424
    variables[204] = 0.00065
    variables[211] = 1.0
    variables[212] = 0.00345
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


def compute_computed_constants(computed_constants):
    variables[3] = variables[119]*variables[120]/variables[17]
    variables[6] = variables[3]*log(variables[7]/variables[8])
    variables[20] = 1.2 if gt_func(variables[1], 0.0) else 1.0
    variables[35] = variables[4]/(variables[47]+variables[4])
    variables[68] = -0.25 if gt_func(variables[1], 0.0) else 0.7*variables[0]/(0.00009+variables[0]) if gt_func(variables[0], 0.0) else 0.0
    variables[69] = variables[70]*(1.0-variables[68])
    variables[103] = 0.000000001*3.14159265358979*pow(variables[105], 2.0)*variables[104]
    variables[19] = 0.000000001*2.0*3.14159265358979*variables[106]*(variables[105]-variables[106]/2.0)*variables[104]
    variables[100] = variables[107]*variables[103]
    variables[18] = variables[108]*variables[103]-variables[19]
    variables[99] = variables[109]*variables[103]
    variables[127] = variables[128]/(variables[7]/(variables[7]+variables[129]))
    variables[130] = variables[127]/(variables[131]+1.0)
    variables[132] = variables[131]*variables[130]
    variables[133] = variables[132]*variables[7]/(variables[7]+variables[129])
    variables[134] = variables[130]*variables[7]/(variables[7]+variables[129])
    variables[137] = -1.0-9.898*pow(1.0*variables[0], 0.618)/(pow(1.0*variables[0], 0.618)+0.00122423) if gt_func(variables[0], 0.0) else 0.0
    variables[138] = 7.5 if gt_func(variables[1], 0.0) else 0.0
    variables[162] = 1.23 if gt_func(variables[1], 0.0) else 1.0
    variables[165] = 0.31*variables[0]/(variables[0]+0.00009)
    variables[166] = -8.0 if gt_func(variables[1], 0.0) else 0.0
    variables[167] = -27.0 if gt_func(variables[1], 0.0) else 0.0
    variables[203] = 1.2*variables[204] if gt_func(variables[1], 0.0) else variables[204]
    variables[206] = -14.0 if gt_func(variables[1], 0.0) else 0.0
    variables[213] = (3.5988-0.025641)/(1.0+0.0000012155/pow(1.0*variables[0], 1.6951))+0.025641


def compute_rates(voi, states, rates, constants, computedConstants, algebraic):
    variables[5] = states[1]
    variables[142] = variables[3]*log((variables[4]+0.12*variables[7])/(variables[5]+0.12*variables[8]))
    variables[121] = variables[123] if and_func(gt_func(voi, variables[124]), lt_func(voi, variables[124]+variables[125])) else variables[126]
    variables[21] = variables[121] if geq_func(variables[122], 1.0) else states[15]
    variables[143] = variables[144]*pow(states[18], 3.0)*states[17]*(variables[21]-variables[142])
    variables[145] = variables[146]*pow(states[18], 3.0)*(variables[21]-variables[142])
    variables[12] = variables[143]+variables[145]
    variables[15] = 0.0000185*variables[163]*(variables[21]-0.0)/(variables[3]*(1.0-exp(-1.0*(variables[21]-0.0)/variables[3])))*(variables[5]-variables[4]*exp(-1.0*(variables[21]-0.0)/variables[3]))*states[23]*states[22]*states[21]
    variables[2] = variables[3]*log(variables[4]/variables[5])
    variables[16] = states[16]*variables[133]*(variables[21]-variables[2])*(1.0-variables[135])
    variables[14] = variables[20]*variables[24]*pow(1.0+pow(variables[23]/variables[7], 1.2), -1.0)*pow(1.0+pow(variables[22]/variables[5], 1.3), -1.0)*pow(1.0+exp(-(variables[21]-variables[2]+110.0)/20.0), -1.0)
    variables[50] = 1.0+variables[10]/variables[48]*(1.0+exp(variables[49]*variables[21]/variables[3]))+variables[4]/variables[51]*(1.0+variables[4]/variables[52]*(1.0+variables[4]/variables[47]))
    variables[27] = variables[10]/variables[48]*exp(variables[49]*variables[21]/variables[3])/variables[50]
    variables[42] = 1.0+states[0]/variables[40]*(1.0+exp(-variables[41]*variables[21]/variables[3])+variables[5]/variables[46])+variables[5]/variables[43]*(1.0+variables[5]/variables[44]*(1.0+variables[5]/variables[39]))
    variables[29] = states[0]/variables[40]*exp(-variables[41]*variables[21]/variables[3])/variables[42]
    variables[36] = variables[5]/(variables[39]+variables[5])
    variables[37] = exp(variables[45]*variables[21]/(2.0*variables[3]))
    variables[33] = exp(-variables[45]*variables[21]/(2.0*variables[3]))
    variables[38] = variables[5]/variables[43]*variables[5]/variables[44]*(1.0+variables[5]/variables[39])*exp(variables[45]*variables[21]/(2.0*variables[3]))/variables[42]
    variables[26] = variables[37]*variables[36]*(variables[38]+variables[29])+variables[33]*variables[29]*(variables[35]+variables[37])
    variables[34] = variables[4]/variables[51]*variables[4]/variables[52]*(1.0+variables[4]/variables[47])*exp(-variables[45]*variables[21]/(2.0*variables[3]))/variables[50]
    variables[28] = variables[33]*variables[35]*(variables[34]+variables[27])+variables[27]*variables[37]*(variables[36]+variables[33])
    variables[31] = variables[34]*variables[35]*(variables[38]+variables[29])+variables[38]*variables[27]*(variables[35]+variables[37])
    variables[32] = variables[38]*variables[36]*(variables[34]+variables[27])+variables[29]*variables[34]*(variables[36]+variables[33])
    variables[13] = (1.0-variables[25])*variables[30]*(variables[26]*variables[27]-variables[28]*variables[29])/(variables[28]+variables[26]+variables[32]+variables[31])
    rates[1] = (1.0-variables[11])*-1.0*(variables[12]+variables[16]+variables[15]+3.0*variables[14]+3.0*variables[13])/(1.0*(variables[18]+variables[19])*variables[17])
    variables[56] = variables[57]-(variables[57]-variables[58])/(1.0+pow(variables[59]/states[2], variables[60]))
    variables[63] = variables[64]*variables[56]
    variables[61] = variables[62]/variables[56]
    rates[4] = variables[65]*states[5]-variables[63]*states[0]*states[4]-(variables[61]*pow(states[0], 2.0)*states[4]-variables[66]*states[3])
    rates[3] = variables[61]*pow(states[0], 2.0)*states[4]-variables[66]*states[3]-(variables[63]*states[0]*states[3]-variables[65]*states[6])
    rates[6] = variables[63]*states[0]*states[3]-variables[65]*states[6]-(variables[66]*states[6]-variables[61]*pow(states[0], 2.0)*states[5])
    rates[5] = variables[66]*states[6]-variables[61]*pow(states[0], 2.0)*states[5]-(variables[65]*states[5]-variables[63]*states[0]*states[4])
    variables[78] = variables[79]*states[7]*(1.0-states[9])-variables[80]*states[9]
    rates[9] = variables[78]
    variables[81] = variables[82]*states[7]*(1.0-(states[10]+states[11]))-variables[83]*states[10]
    rates[10] = variables[81]
    variables[84] = variables[85]*variables[86]*(1.0-(states[10]+states[11]))-variables[87]*states[11]
    rates[11] = variables[84]
    variables[88] = variables[89]*states[7]*(1.0-states[12])-variables[90]*states[12]
    rates[12] = variables[88]
    variables[91] = variables[89]*states[0]*(1.0-states[13])-variables[90]*states[13]
    rates[13] = variables[91]
    variables[92] = variables[93]*states[2]*(1.0-states[14])-variables[94]*states[14]
    rates[14] = variables[92]
    variables[71] = (states[0]-states[7])/variables[72]
    variables[73] = variables[69]/(1.0+exp((-states[7]+variables[74])/variables[75]))
    rates[7] = 1.0*(variables[71]*variables[19]-variables[73]*variables[99])/variables[18]-(variables[97]*variables[88]+variables[95]*variables[78]+variables[96]*variables[81])
    variables[53] = variables[54]*states[3]*(states[2]-states[0])
    variables[101] = 2.0*variables[163]*(variables[21]-0.0)/(variables[3]*(1.0-exp(-1.0*(variables[21]-0.0)*2.0/variables[3])))*(states[0]-variables[10]*exp(-2.0*(variables[21]-0.0)/variables[3]))*states[23]*states[22]*states[21]
    variables[102] = 2.0*variables[184]*variables[21]/(variables[3]*(1.0-exp(-1.0*variables[21]*2.0/variables[3])))*(states[0]-variables[10]*exp(-2.0*variables[21]/variables[3]))*states[25]*states[24]
    rates[0] = variables[53]*variables[100]/variables[19]-((variables[101]+variables[102]-2.0*variables[13])/(2.0*variables[17]*variables[19])+variables[71]+variables[97]*variables[91])
    variables[76] = (states[8]-states[2])/variables[77]
    rates[8] = variables[73]-variables[76]*variables[100]/variables[99]
    rates[2] = variables[76]-(variables[53]+variables[98]*variables[92])
    variables[136] = states[16]*variables[134]*(variables[21]-variables[6])*(1.0-variables[135])
    variables[111] = variables[16]+variables[136]
    variables[112] = variables[157]*states[20]*states[19]*(variables[21]-variables[6])
    variables[113] = variables[211]*variables[212]*(variables[21]-variables[6])*(1.0+exp((variables[21]+20.0)/20.0))*states[32] if gt_func(variables[0], 0.0) else 0.0
    variables[164] = 0.000365*variables[163]*(variables[21]-0.0)/(variables[3]*(1.0-exp(-1.0*(variables[21]-0.0)/variables[3])))*(variables[8]-variables[7]*exp(-1.0*(variables[21]-0.0)/variables[3]))*states[23]*states[22]*states[21]
    variables[114] = (variables[101]+variables[164]+variables[15])*(1.0-variables[165])*1.0*variables[162]
    variables[115] = variables[190]*(variables[21]-variables[6])*states[27]*states[26]
    variables[205] = variables[3]*log((variables[7]+0.12*variables[4])/(variables[8]+0.12*variables[5]))
    variables[116] = variables[203]*(variables[21]-variables[205])*pow(states[31], 2.0)
    variables[117] = variables[195]*(variables[21]-variables[6])*(0.9*states[29]+0.1*states[30])*states[28]
    variables[110] = variables[111]+variables[117]+variables[116]+variables[115]+variables[14]+variables[13]+variables[12]+variables[114]+variables[102]+variables[113]+variables[112]
    rates[15] = -variables[110]/variables[118]
    variables[140] = 0.01329+0.99921/(1.0+exp((variables[21]+97.134-variables[137]-variables[138]-variables[141])/8.1752)) if lt_func(variables[21], -(80.0-variables[137]-variables[138]-variables[141])) else 0.0002501*exp(-(variables[21]-variables[137]-variables[138]-variables[141])/12.861)
    variables[139] = 1.0/(0.36*(variables[21]+148.8-variables[137]-variables[138])/(exp(0.066*(variables[21]+148.8-variables[137]-variables[138]))-1.0)+0.1*(variables[21]+87.3-variables[137]-variables[138])/(1.0-exp(-0.2*(variables[21]+87.3-variables[137]-variables[138]))))-0.054
    rates[16] = (variables[140]-states[16])/variables[139]
    variables[147] = 1.0/(1.0+exp(-(variables[21]+42.0504)/8.3106))
    variables[148] = variables[21]+41.0
    variables[149] = 2000.0 if lt_func(fabs(variables[148]), variables[150]) else 200.0*variables[148]/(1.0-exp(-0.1*variables[148]))
    variables[151] = 8000.0*exp(-0.056*(variables[21]+66.0))
    variables[152] = 1.0/(variables[149]+variables[151])
    rates[18] = (variables[147]-states[18])/variables[152]
    variables[153] = 1.0/(1.0+exp((variables[21]+69.804)/4.4565))
    variables[154] = 20.0*exp(-0.125*(variables[21]+75.0))
    variables[155] = 2000.0/(320.0*exp(-0.1*(variables[21]+75.0))+1.0)
    variables[156] = 1.0/(variables[154]+variables[155])
    rates[17] = (variables[153]-states[17])/variables[156]
    variables[158] = 1.0/(1.0+exp((variables[21]+6.0)/-8.6))
    variables[159] = 0.009/(1.0+exp((variables[21]+5.0)/12.0))+0.0005
    rates[20] = (variables[158]-states[20])/variables[159]
    variables[160] = 1.0/(1.0+exp((variables[21]+7.5)/10.0))
    variables[161] = 0.59/(1.0+exp((variables[21]+60.0)/10.0))+3.05
    rates[19] = (variables[160]-states[19])/variables[161]
    variables[168] = 1.0/(1.0+exp(-(variables[21]-variables[169]-variables[166])/(variables[170]*(1.0+variables[167]/100.0))))
    variables[174] = -41.80001 if eq_func(variables[21], -41.8) else 0.0 if eq_func(variables[21], 0.0) else -6.80001 if eq_func(variables[21], -6.8) else variables[21]
    variables[172] = -0.02839*(variables[174]+41.8)/(exp(-(variables[174]+41.8)/2.5)-1.0)-0.0849*(variables[174]+6.8)/(exp(-(variables[174]+6.8)/4.8)-1.0)
    variables[175] = -1.80001 if eq_func(variables[21], -1.8) else variables[21]
    variables[173] = 0.01143*(variables[175]+1.8)/(exp((variables[175]+1.8)/2.5)-1.0)
    variables[171] = 0.001/(variables[172]+variables[173])
    rates[23] = (variables[168]-states[23])/variables[171]
    variables[176] = 1.0/(1.0+exp((variables[21]+37.4+variables[177])/(5.3+variables[178])))
    variables[179] = 0.001*(44.3+230.0*exp(-pow((variables[21]+36.0)/10.0, 2.0)))
    rates[22] = (variables[176]-states[22])/variables[179]
    variables[180] = variables[181]/(variables[181]+states[0])
    variables[182] = 0.001*variables[180]/variables[183]
    rates[21] = (variables[180]-states[21])/variables[182]
    variables[185] = 1.0/(1.0+exp(-(variables[21]+38.3)/5.5))
    variables[186] = 0.001/(1.068*exp((variables[21]+38.3)/30.0)+1.068*exp(-(variables[21]+38.3)/30.0))
    rates[25] = (variables[185]-states[25])/variables[186]
    variables[187] = 1.0/(1.0+exp((variables[21]+58.7)/3.8))
    variables[188] = 1.0/(16.67*exp(-(variables[21]+75.0)/83.3)+16.67*exp((variables[21]+75.0)/15.38))+variables[189]
    rates[24] = (variables[187]-states[24])/variables[188]
    variables[191] = 1.0/(1.0+exp((variables[21]+49.0)/13.0))
    variables[192] = 0.001*0.6*(65.17/(0.57*exp(-0.08*(variables[21]+44.0))+0.065*exp(0.1*(variables[21]+45.93)))+10.1)
    rates[27] = (variables[191]-states[27])/variables[192]
    variables[193] = 1.0/(1.0+exp(-(variables[21]-19.3)/15.0))
    variables[194] = 0.001*0.66*1.4*(15.59/(1.037*exp(0.09*(variables[21]+30.61))+0.369*exp(-0.12*(variables[21]+23.84)))+2.98)
    rates[26] = (variables[193]-states[26])/variables[194]
    variables[198] = 1.0/(1.0+exp(-(variables[21]+10.0144)/7.6607))
    variables[199] = 0.84655354/(4.2*exp(variables[21]/17.0)+0.15*exp(-variables[21]/21.6))
    rates[30] = (variables[198]-states[30])/variables[199]
    variables[200] = 1.0/(30.0*exp(variables[21]/10.0)+exp(-variables[21]/12.0))
    rates[29] = (variables[198]-states[29])/variables[200]
    variables[202] = 1.0/(1.0+exp((variables[21]+28.6)/17.1))
    variables[201] = 1.0/(100.0*exp(-variables[21]/54.645)+656.0*exp(variables[21]/106.157))
    rates[28] = (variables[202]-states[28])/variables[201]
    variables[207] = sqrt(1.0/(1.0+exp(-(variables[21]+0.6383-variables[206])/10.7071)))
    variables[209] = 28.0/(1.0+exp(-(variables[21]-40.0-variables[206])/3.0))
    variables[210] = 1.0*exp(-(variables[21]-variables[206]-5.0)/25.0)
    variables[208] = 1.0/(variables[209]+variables[210])
    rates[31] = (variables[207]-states[31])/variables[208]
    variables[214] = 10.0*exp(0.0133*(variables[21]+40.0))
    variables[215] = variables[213]/(variables[213]+variables[214])
    variables[216] = 1.0/(variables[213]+variables[214])
    rates[32] = (variables[215]-states[32])/variables[216]


def compute_variables(voi, states, rates, constants, computedConstants, algebraic):
    variables[5] = states[1]
    variables[2] = variables[3]*log(variables[4]/variables[5])
    variables[9] = 0.5*variables[3]*log(variables[10]/states[0])
    variables[21] = variables[121] if geq_func(variables[122], 1.0) else states[15]
    variables[14] = variables[20]*variables[24]*pow(1.0+pow(variables[23]/variables[7], 1.2), -1.0)*pow(1.0+pow(variables[22]/variables[5], 1.3), -1.0)*pow(1.0+exp(-(variables[21]-variables[2]+110.0)/20.0), -1.0)
    variables[50] = 1.0+variables[10]/variables[48]*(1.0+exp(variables[49]*variables[21]/variables[3]))+variables[4]/variables[51]*(1.0+variables[4]/variables[52]*(1.0+variables[4]/variables[47]))
    variables[27] = variables[10]/variables[48]*exp(variables[49]*variables[21]/variables[3])/variables[50]
    variables[42] = 1.0+states[0]/variables[40]*(1.0+exp(-variables[41]*variables[21]/variables[3])+variables[5]/variables[46])+variables[5]/variables[43]*(1.0+variables[5]/variables[44]*(1.0+variables[5]/variables[39]))
    variables[29] = states[0]/variables[40]*exp(-variables[41]*variables[21]/variables[3])/variables[42]
    variables[36] = variables[5]/(variables[39]+variables[5])
    variables[37] = exp(variables[45]*variables[21]/(2.0*variables[3]))
    variables[33] = exp(-variables[45]*variables[21]/(2.0*variables[3]))
    variables[38] = variables[5]/variables[43]*variables[5]/variables[44]*(1.0+variables[5]/variables[39])*exp(variables[45]*variables[21]/(2.0*variables[3]))/variables[42]
    variables[26] = variables[37]*variables[36]*(variables[38]+variables[29])+variables[33]*variables[29]*(variables[35]+variables[37])
    variables[34] = variables[4]/variables[51]*variables[4]/variables[52]*(1.0+variables[4]/variables[47])*exp(-variables[45]*variables[21]/(2.0*variables[3]))/variables[50]
    variables[28] = variables[33]*variables[35]*(variables[34]+variables[27])+variables[27]*variables[37]*(variables[36]+variables[33])
    variables[31] = variables[34]*variables[35]*(variables[38]+variables[29])+variables[38]*variables[27]*(variables[35]+variables[37])
    variables[32] = variables[38]*variables[36]*(variables[34]+variables[27])+variables[29]*variables[34]*(variables[36]+variables[33])
    variables[13] = (1.0-variables[25])*variables[30]*(variables[26]*variables[27]-variables[28]*variables[29])/(variables[28]+variables[26]+variables[32]+variables[31])
    variables[53] = variables[54]*states[3]*(states[2]-states[0])
    variables[55] = states[2]-states[0]
    variables[56] = variables[57]-(variables[57]-variables[58])/(1.0+pow(variables[59]/states[2], variables[60]))
    variables[61] = variables[62]/variables[56]
    variables[63] = variables[64]*variables[56]
    variables[67] = states[4]+states[3]+states[6]+states[5]
    variables[71] = (states[0]-states[7])/variables[72]
    variables[73] = variables[69]/(1.0+exp((-states[7]+variables[74])/variables[75]))
    variables[76] = (states[8]-states[2])/variables[77]
    variables[78] = variables[79]*states[7]*(1.0-states[9])-variables[80]*states[9]
    variables[81] = variables[82]*states[7]*(1.0-(states[10]+states[11]))-variables[83]*states[10]
    variables[84] = variables[85]*variables[86]*(1.0-(states[10]+states[11]))-variables[87]*states[11]
    variables[88] = variables[89]*states[7]*(1.0-states[12])-variables[90]*states[12]
    variables[91] = variables[89]*states[0]*(1.0-states[13])-variables[90]*states[13]
    variables[92] = variables[93]*states[2]*(1.0-states[14])-variables[94]*states[14]
    variables[16] = states[16]*variables[133]*(variables[21]-variables[2])*(1.0-variables[135])
    variables[136] = states[16]*variables[134]*(variables[21]-variables[6])*(1.0-variables[135])
    variables[111] = variables[16]+variables[136]
    variables[112] = variables[157]*states[20]*states[19]*(variables[21]-variables[6])
    variables[113] = variables[211]*variables[212]*(variables[21]-variables[6])*(1.0+exp((variables[21]+20.0)/20.0))*states[32] if gt_func(variables[0], 0.0) else 0.0
    variables[102] = 2.0*variables[184]*variables[21]/(variables[3]*(1.0-exp(-1.0*variables[21]*2.0/variables[3])))*(states[0]-variables[10]*exp(-2.0*variables[21]/variables[3]))*states[25]*states[24]
    variables[101] = 2.0*variables[163]*(variables[21]-0.0)/(variables[3]*(1.0-exp(-1.0*(variables[21]-0.0)*2.0/variables[3])))*(states[0]-variables[10]*exp(-2.0*(variables[21]-0.0)/variables[3]))*states[23]*states[22]*states[21]
    variables[15] = 0.0000185*variables[163]*(variables[21]-0.0)/(variables[3]*(1.0-exp(-1.0*(variables[21]-0.0)/variables[3])))*(variables[5]-variables[4]*exp(-1.0*(variables[21]-0.0)/variables[3]))*states[23]*states[22]*states[21]
    variables[164] = 0.000365*variables[163]*(variables[21]-0.0)/(variables[3]*(1.0-exp(-1.0*(variables[21]-0.0)/variables[3])))*(variables[8]-variables[7]*exp(-1.0*(variables[21]-0.0)/variables[3]))*states[23]*states[22]*states[21]
    variables[114] = (variables[101]+variables[164]+variables[15])*(1.0-variables[165])*1.0*variables[162]
    variables[142] = variables[3]*log((variables[4]+0.12*variables[7])/(variables[5]+0.12*variables[8]))
    variables[143] = variables[144]*pow(states[18], 3.0)*states[17]*(variables[21]-variables[142])
    variables[145] = variables[146]*pow(states[18], 3.0)*(variables[21]-variables[142])
    variables[12] = variables[143]+variables[145]
    variables[115] = variables[190]*(variables[21]-variables[6])*states[27]*states[26]
    variables[205] = variables[3]*log((variables[7]+0.12*variables[4])/(variables[8]+0.12*variables[5]))
    variables[116] = variables[203]*(variables[21]-variables[205])*pow(states[31], 2.0)
    variables[117] = variables[195]*(variables[21]-variables[6])*(0.9*states[29]+0.1*states[30])*states[28]
    variables[110] = variables[111]+variables[117]+variables[116]+variables[115]+variables[14]+variables[13]+variables[12]+variables[114]+variables[102]+variables[113]+variables[112]
    variables[139] = 1.0/(0.36*(variables[21]+148.8-variables[137]-variables[138])/(exp(0.066*(variables[21]+148.8-variables[137]-variables[138]))-1.0)+0.1*(variables[21]+87.3-variables[137]-variables[138])/(1.0-exp(-0.2*(variables[21]+87.3-variables[137]-variables[138]))))-0.054
    variables[140] = 0.01329+0.99921/(1.0+exp((variables[21]+97.134-variables[137]-variables[138]-variables[141])/8.1752)) if lt_func(variables[21], -(80.0-variables[137]-variables[138]-variables[141])) else 0.0002501*exp(-(variables[21]-variables[137]-variables[138]-variables[141])/12.861)
    variables[147] = 1.0/(1.0+exp(-(variables[21]+42.0504)/8.3106))
    variables[148] = variables[21]+41.0
    variables[149] = 2000.0 if lt_func(fabs(variables[148]), variables[150]) else 200.0*variables[148]/(1.0-exp(-0.1*variables[148]))
    variables[151] = 8000.0*exp(-0.056*(variables[21]+66.0))
    variables[152] = 1.0/(variables[149]+variables[151])
    variables[153] = 1.0/(1.0+exp((variables[21]+69.804)/4.4565))
    variables[154] = 20.0*exp(-0.125*(variables[21]+75.0))
    variables[155] = 2000.0/(320.0*exp(-0.1*(variables[21]+75.0))+1.0)
    variables[156] = 1.0/(variables[154]+variables[155])
    variables[158] = 1.0/(1.0+exp((variables[21]+6.0)/-8.6))
    variables[159] = 0.009/(1.0+exp((variables[21]+5.0)/12.0))+0.0005
    variables[160] = 1.0/(1.0+exp((variables[21]+7.5)/10.0))
    variables[161] = 0.59/(1.0+exp((variables[21]+60.0)/10.0))+3.05
    variables[168] = 1.0/(1.0+exp(-(variables[21]-variables[169]-variables[166])/(variables[170]*(1.0+variables[167]/100.0))))
    variables[174] = -41.80001 if eq_func(variables[21], -41.8) else 0.0 if eq_func(variables[21], 0.0) else -6.80001 if eq_func(variables[21], -6.8) else variables[21]
    variables[172] = -0.02839*(variables[174]+41.8)/(exp(-(variables[174]+41.8)/2.5)-1.0)-0.0849*(variables[174]+6.8)/(exp(-(variables[174]+6.8)/4.8)-1.0)
    variables[175] = -1.80001 if eq_func(variables[21], -1.8) else variables[21]
    variables[173] = 0.01143*(variables[175]+1.8)/(exp((variables[175]+1.8)/2.5)-1.0)
    variables[171] = 0.001/(variables[172]+variables[173])
    variables[176] = 1.0/(1.0+exp((variables[21]+37.4+variables[177])/(5.3+variables[178])))
    variables[179] = 0.001*(44.3+230.0*exp(-pow((variables[21]+36.0)/10.0, 2.0)))
    variables[180] = variables[181]/(variables[181]+states[0])
    variables[182] = 0.001*variables[180]/variables[183]
    variables[185] = 1.0/(1.0+exp(-(variables[21]+38.3)/5.5))
    variables[186] = 0.001/(1.068*exp((variables[21]+38.3)/30.0)+1.068*exp(-(variables[21]+38.3)/30.0))
    variables[187] = 1.0/(1.0+exp((variables[21]+58.7)/3.8))
    variables[188] = 1.0/(16.67*exp(-(variables[21]+75.0)/83.3)+16.67*exp((variables[21]+75.0)/15.38))+variables[189]
    variables[191] = 1.0/(1.0+exp((variables[21]+49.0)/13.0))
    variables[192] = 0.001*0.6*(65.17/(0.57*exp(-0.08*(variables[21]+44.0))+0.065*exp(0.1*(variables[21]+45.93)))+10.1)
    variables[193] = 1.0/(1.0+exp(-(variables[21]-19.3)/15.0))
    variables[194] = 0.001*0.66*1.4*(15.59/(1.037*exp(0.09*(variables[21]+30.61))+0.369*exp(-0.12*(variables[21]+23.84)))+2.98)
    variables[196] = 1.0/(1.0+exp(-(variables[21]+23.2)/6.6))/(0.84655354/(37.2*exp(variables[21]/11.9)+0.96*exp(-variables[21]/18.5)))
    variables[197] = 4.0*((37.2*exp(variables[21]/15.9)+0.96*exp(-variables[21]/22.5))/0.84655354-1.0/(1.0+exp(-(variables[21]+23.2)/10.6))/(0.84655354/(37.2*exp(variables[21]/15.9)+0.96*exp(-variables[21]/22.5))))
    variables[198] = 1.0/(1.0+exp(-(variables[21]+10.0144)/7.6607))
    variables[199] = 0.84655354/(4.2*exp(variables[21]/17.0)+0.15*exp(-variables[21]/21.6))
    variables[200] = 1.0/(30.0*exp(variables[21]/10.0)+exp(-variables[21]/12.0))
    variables[201] = 1.0/(100.0*exp(-variables[21]/54.645)+656.0*exp(variables[21]/106.157))
    variables[202] = 1.0/(1.0+exp((variables[21]+28.6)/17.1))
    variables[207] = sqrt(1.0/(1.0+exp(-(variables[21]+0.6383-variables[206])/10.7071)))
    variables[209] = 28.0/(1.0+exp(-(variables[21]-40.0-variables[206])/3.0))
    variables[210] = 1.0*exp(-(variables[21]-variables[206]-5.0)/25.0)
    variables[208] = 1.0/(variables[209]+variables[210])
    variables[214] = 10.0*exp(0.0133*(variables[21]+40.0))
    variables[215] = variables[213]/(variables[213]+variables[214])
    variables[216] = 1.0/(variables[213]+variables[214])

# The content of this file was generated using the Python profile of libCellML 0.2.0.

from enum import Enum
from math import *


__version__ = "0.3.0"
LIBCELLML_VERSION = "0.2.0"

STATE_COUNT = 33
VARIABLE_COUNT = 217


class VariableType(Enum):
    VARIABLE_OF_INTEGRATION = 1
    STATE = 2
    CONSTANT = 3
    COMPUTED_CONSTANT = 4
    ALGEBRAIC = 5


VOI_INFO = {"name": "time", "units": "second", "component": "environment", "type": VariableType.VARIABLE_OF_INTEGRATION}

STATE_INFO = [
    {"name": "R", "units": "dimensionless", "component": "Ca_SR_release", "type": VariableType.STATE},
    {"name": "O", "units": "dimensionless", "component": "Ca_SR_release", "type": VariableType.STATE},
    {"name": "I", "units": "dimensionless", "component": "Ca_SR_release", "type": VariableType.STATE},
    {"name": "RI", "units": "dimensionless", "component": "Ca_SR_release", "type": VariableType.STATE},
    {"name": "Ca_jsr", "units": "millimolar", "component": "Ca_dynamics", "type": VariableType.STATE},
    {"name": "fCa", "units": "dimensionless", "component": "i_CaL_fCa_gate", "type": VariableType.STATE},
    {"name": "fTC", "units": "dimensionless", "component": "Ca_buffering", "type": VariableType.STATE},
    {"name": "fTMC", "units": "dimensionless", "component": "Ca_buffering", "type": VariableType.STATE},
    {"name": "fTMM", "units": "dimensionless", "component": "Ca_buffering", "type": VariableType.STATE},
    {"name": "fCMi", "units": "dimensionless", "component": "Ca_buffering", "type": VariableType.STATE},
    {"name": "fCMs", "units": "dimensionless", "component": "Ca_buffering", "type": VariableType.STATE},
    {"name": "fCQ", "units": "dimensionless", "component": "Ca_buffering", "type": VariableType.STATE},
    {"name": "Cai", "units": "millimolar", "component": "Ca_dynamics", "type": VariableType.STATE},
    {"name": "Ca_nsr", "units": "millimolar", "component": "Ca_dynamics", "type": VariableType.STATE},
    {"name": "y", "units": "dimensionless", "component": "i_f_y_gate", "type": VariableType.STATE},
    {"name": "m", "units": "dimensionless", "component": "i_Na_m_gate", "type": VariableType.STATE},
    {"name": "h", "units": "dimensionless", "component": "i_Na_h_gate", "type": VariableType.STATE},
    {"name": "fL", "units": "dimensionless", "component": "i_CaL_fL_gate", "type": VariableType.STATE},
    {"name": "dT", "units": "dimensionless", "component": "i_CaT_dT_gate", "type": VariableType.STATE},
    {"name": "fT", "units": "dimensionless", "component": "i_CaT_fT_gate", "type": VariableType.STATE},
    {"name": "q", "units": "dimensionless", "component": "i_to_q_gate", "type": VariableType.STATE},
    {"name": "r", "units": "dimensionless", "component": "i_to_r_gate", "type": VariableType.STATE},
    {"name": "paS", "units": "dimensionless", "component": "i_Kr_pa_gate", "type": VariableType.STATE},
    {"name": "paF", "units": "dimensionless", "component": "i_Kr_pa_gate", "type": VariableType.STATE},
    {"name": "piy", "units": "dimensionless", "component": "i_Kr_pi_gate", "type": VariableType.STATE},
    {"name": "a", "units": "dimensionless", "component": "i_KACh_a_gate", "type": VariableType.STATE},
    {"name": "r_Kur", "units": "dimensionless", "component": "i_Kur_rKur_gate", "type": VariableType.STATE},
    {"name": "s_Kur", "units": "dimensionless", "component": "i_Kur_sKur_gate", "type": VariableType.STATE},
    {"name": "n", "units": "dimensionless", "component": "i_Ks_n_gate", "type": VariableType.STATE},
    {"name": "dL", "units": "dimensionless", "component": "i_CaL_dL_gate", "type": VariableType.STATE},
    {"name": "Ca_sub", "units": "millimolar", "component": "Ca_dynamics", "type": VariableType.STATE},
    {"name": "V_ode", "units": "millivolt", "component": "Membrane", "type": VariableType.STATE},
    {"name": "Nai_", "units": "millimolar", "component": "Nai_concentration", "type": VariableType.STATE}
]

VARIABLE_INFO = [
    {"name": "EC50_SR", "units": "millimolar", "component": "Ca_SR_release", "type": VariableType.CONSTANT},
    {"name": "HSR", "units": "dimensionless", "component": "Ca_SR_release", "type": VariableType.CONSTANT},
    {"name": "MaxSR", "units": "dimensionless", "component": "Ca_SR_release", "type": VariableType.CONSTANT},
    {"name": "MinSR", "units": "dimensionless", "component": "Ca_SR_release", "type": VariableType.CONSTANT},
    {"name": "kiCa", "units": "per_millimolar_second", "component": "Ca_SR_release", "type": VariableType.CONSTANT},
    {"name": "kim", "units": "per_second", "component": "Ca_SR_release", "type": VariableType.CONSTANT},
    {"name": "koCa", "units": "per_millimolar2_second", "component": "Ca_SR_release", "type": VariableType.CONSTANT},
    {"name": "kom", "units": "per_second", "component": "Ca_SR_release", "type": VariableType.CONSTANT},
    {"name": "ks", "units": "per_second", "component": "Ca_SR_release", "type": VariableType.CONSTANT},
    {"name": "CM_tot", "units": "millimolar", "component": "Ca_buffering", "type": VariableType.CONSTANT},
    {"name": "CQ_tot", "units": "millimolar", "component": "Ca_buffering", "type": VariableType.CONSTANT},
    {"name": "Mgi", "units": "millimolar", "component": "Ca_buffering", "type": VariableType.CONSTANT},
    {"name": "TC_tot", "units": "millimolar", "component": "Ca_buffering", "type": VariableType.CONSTANT},
    {"name": "TMC_tot", "units": "millimolar", "component": "Ca_buffering", "type": VariableType.CONSTANT},
    {"name": "kb_CM", "units": "per_second", "component": "Ca_buffering", "type": VariableType.CONSTANT},
    {"name": "kb_CQ", "units": "per_second", "component": "Ca_buffering", "type": VariableType.CONSTANT},
    {"name": "kb_TC", "units": "per_second", "component": "Ca_buffering", "type": VariableType.CONSTANT},
    {"name": "kb_TMC", "units": "per_second", "component": "Ca_buffering", "type": VariableType.CONSTANT},
    {"name": "kb_TMM", "units": "per_second", "component": "Ca_buffering", "type": VariableType.CONSTANT},
    {"name": "kf_CM", "units": "per_millimolar_second", "component": "Ca_buffering", "type": VariableType.CONSTANT},
    {"name": "kf_CQ", "units": "per_millimolar_second", "component": "Ca_buffering", "type": VariableType.CONSTANT},
    {"name": "kf_TC", "units": "per_millimolar_second", "component": "Ca_buffering", "type": VariableType.CONSTANT},
    {"name": "kf_TMC", "units": "per_millimolar_second", "component": "Ca_buffering", "type": VariableType.CONSTANT},
    {"name": "kf_TMM", "units": "per_millimolar_second", "component": "Ca_buffering", "type": VariableType.CONSTANT},
    {"name": "K_up", "units": "millimolar", "component": "Ca_intracellular_fluxes", "type": VariableType.CONSTANT},
    {"name": "P_up_basal", "units": "millimolar_per_second", "component": "Ca_intracellular_fluxes", "type": VariableType.CONSTANT},
    {"name": "slope_up", "units": "millimolar", "component": "Ca_intracellular_fluxes", "type": VariableType.CONSTANT},
    {"name": "tau_dif_Ca", "units": "second", "component": "Ca_intracellular_fluxes", "type": VariableType.CONSTANT},
    {"name": "tau_tr", "units": "second", "component": "Ca_intracellular_fluxes", "type": VariableType.CONSTANT},
    {"name": "L_cell", "units": "micrometre", "component": "Cell_parameters", "type": VariableType.CONSTANT},
    {"name": "L_sub", "units": "micrometre", "component": "Cell_parameters", "type": VariableType.CONSTANT},
    {"name": "R_cell", "units": "micrometre", "component": "Cell_parameters", "type": VariableType.CONSTANT},
    {"name": "V_i_part", "units": "dimensionless", "component": "Cell_parameters", "type": VariableType.CONSTANT},
    {"name": "V_jsr_part", "units": "dimensionless", "component": "Cell_parameters", "type": VariableType.CONSTANT},
    {"name": "V_nsr_part", "units": "dimensionless", "component": "Cell_parameters", "type": VariableType.CONSTANT},
    {"name": "Cao", "units": "millimolar", "component": "Ionic_values", "type": VariableType.CONSTANT},
    {"name": "Ki", "units": "millimolar", "component": "Ionic_values", "type": VariableType.CONSTANT},
    {"name": "Ko", "units": "millimolar", "component": "Ionic_values", "type": VariableType.CONSTANT},
    {"name": "Nao", "units": "millimolar", "component": "Ionic_values", "type": VariableType.CONSTANT},
    {"name": "C", "units": "microF", "component": "Membrane", "type": VariableType.CONSTANT},
    {"name": "F", "units": "coulomb_per_mole", "component": "Membrane", "type": VariableType.CONSTANT},
    {"name": "R", "units": "joule_per_kilomole_kelvin", "component": "Membrane", "type": VariableType.CONSTANT},
    {"name": "T", "units": "kelvin", "component": "Membrane", "type": VariableType.CONSTANT},
    {"name": "clamp_mode", "units": "dimensionless", "component": "Membrane", "type": VariableType.CONSTANT},
    {"name": "Nai_clamp", "units": "dimensionless", "component": "Nai_concentration", "type": VariableType.CONSTANT},
    {"name": "ACh", "units": "millimolar", "component": "Rate_modulation_experiments", "type": VariableType.CONSTANT},
    {"name": "Iso_1_uM", "units": "dimensionless", "component": "Rate_modulation_experiments", "type": VariableType.CONSTANT},
    {"name": "V_holding", "units": "millivolt", "component": "Voltage_clamp", "type": VariableType.CONSTANT},
    {"name": "V_test", "units": "millivolt", "component": "Voltage_clamp", "type": VariableType.CONSTANT},
    {"name": "t_holding", "units": "second", "component": "Voltage_clamp", "type": VariableType.CONSTANT},
    {"name": "t_test", "units": "second", "component": "Voltage_clamp", "type": VariableType.CONSTANT},
    {"name": "P_CaL", "units": "nanoA_per_millimolar", "component": "i_CaL", "type": VariableType.CONSTANT},
    {"name": "V_dL", "units": "millivolt", "component": "i_CaL_dL_gate", "type": VariableType.CONSTANT},
    {"name": "k_dL", "units": "millivolt", "component": "i_CaL_dL_gate", "type": VariableType.CONSTANT},
    {"name": "Km_fCa", "units": "millimolar", "component": "i_CaL_fCa_gate", "type": VariableType.CONSTANT},
    {"name": "alpha_fCa", "units": "per_second", "component": "i_CaL_fCa_gate", "type": VariableType.CONSTANT},
    {"name": "k_fL", "units": "millivolt", "component": "i_CaL_fL_gate", "type": VariableType.CONSTANT},
    {"name": "shift_fL", "units": "millivolt", "component": "i_CaL_fL_gate", "type": VariableType.CONSTANT},
    {"name": "P_CaT", "units": "nanoA_per_millimolar", "component": "i_CaT", "type": VariableType.CONSTANT},
    {"name": "offset_fT", "units": "second", "component": "i_CaT_fT_gate", "type": VariableType.CONSTANT},
    {"name": "ACh_on", "units": "dimensionless", "component": "i_KACh", "type": VariableType.CONSTANT},
    {"name": "g_KACh", "units": "microS", "component": "i_KACh", "type": VariableType.CONSTANT},
    {"name": "g_Kr", "units": "microS", "component": "i_Kr", "type": VariableType.CONSTANT},
    {"name": "g_Ks_", "units": "microS", "component": "i_Ks", "type": VariableType.CONSTANT},
    {"name": "g_Kur", "units": "microS", "component": "i_Kur", "type": VariableType.CONSTANT},
    {"name": "g_Na", "units": "microS", "component": "i_Na", "type": VariableType.CONSTANT},
    {"name": "g_Na_L", "units": "microS", "component": "i_Na", "type": VariableType.CONSTANT},
    {"name": "K1ni", "units": "millimolar", "component": "i_NaCa", "type": VariableType.CONSTANT},
    {"name": "K1no", "units": "millimolar", "component": "i_NaCa", "type": VariableType.CONSTANT},
    {"name": "K2ni", "units": "millimolar", "component": "i_NaCa", "type": VariableType.CONSTANT},
    {"name": "K2no", "units": "millimolar", "component": "i_NaCa", "type": VariableType.CONSTANT},
    {"name": "K3ni", "units": "millimolar", "component": "i_NaCa", "type": VariableType.CONSTANT},
    {"name": "K3no", "units": "millimolar", "component": "i_NaCa", "type": VariableType.CONSTANT},
    {"name": "K_NaCa", "units": "nanoA", "component": "i_NaCa", "type": VariableType.CONSTANT},
    {"name": "Kci", "units": "millimolar", "component": "i_NaCa", "type": VariableType.CONSTANT},
    {"name": "Kcni", "units": "millimolar", "component": "i_NaCa", "type": VariableType.CONSTANT},
    {"name": "Kco", "units": "millimolar", "component": "i_NaCa", "type": VariableType.CONSTANT},
    {"name": "Qci", "units": "dimensionless", "component": "i_NaCa", "type": VariableType.CONSTANT},
    {"name": "Qco", "units": "dimensionless", "component": "i_NaCa", "type": VariableType.CONSTANT},
    {"name": "Qn", "units": "dimensionless", "component": "i_NaCa", "type": VariableType.CONSTANT},
    {"name": "blockade_NaCa", "units": "dimensionless", "component": "i_NaCa", "type": VariableType.CONSTANT},
    {"name": "Km_Kp", "units": "millimolar", "component": "i_NaK", "type": VariableType.CONSTANT},
    {"name": "Km_Nap", "units": "millimolar", "component": "i_NaK", "type": VariableType.CONSTANT},
    {"name": "i_NaK_max", "units": "nanoA", "component": "i_NaK", "type": VariableType.CONSTANT},
    {"name": "delta_m", "units": "millivolt", "component": "i_Na_m_gate", "type": VariableType.CONSTANT},
    {"name": "Km_f", "units": "millimolar", "component": "i_f", "type": VariableType.CONSTANT},
    {"name": "alpha", "units": "dimensionless", "component": "i_f", "type": VariableType.CONSTANT},
    {"name": "blockade", "units": "dimensionless", "component": "i_f", "type": VariableType.CONSTANT},
    {"name": "g_f", "units": "microS", "component": "i_f", "type": VariableType.CONSTANT},
    {"name": "y_shift", "units": "millivolt", "component": "i_f_y_gate", "type": VariableType.CONSTANT},
    {"name": "g_to", "units": "microS", "component": "i_to", "type": VariableType.CONSTANT},
    {"name": "Nai", "units": "millimolar", "component": "Nai_concentration", "type": VariableType.ALGEBRAIC},
    {"name": "Iso_increase", "units": "dimensionless", "component": "i_NaK", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "k43", "units": "dimensionless", "component": "i_NaCa", "type": VariableType.ALGEBRAIC},
    {"name": "k34", "units": "dimensionless", "component": "i_NaCa", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "j_SRCarel", "units": "millimolar_per_second", "component": "Ca_SR_release", "type": VariableType.ALGEBRAIC},
    {"name": "diff", "units": "millimolar", "component": "Ca_SR_release", "type": VariableType.ALGEBRAIC},
    {"name": "kCaSR", "units": "dimensionless", "component": "Ca_SR_release", "type": VariableType.ALGEBRAIC},
    {"name": "koSRCa", "units": "per_millimolar2_second", "component": "Ca_SR_release", "type": VariableType.ALGEBRAIC},
    {"name": "kiSRCa", "units": "per_millimolar_second", "component": "Ca_SR_release", "type": VariableType.ALGEBRAIC},
    {"name": "P_tot", "units": "dimensionless", "component": "Ca_SR_release", "type": VariableType.ALGEBRAIC},
    {"name": "b_up", "units": "dimensionless", "component": "Ca_intracellular_fluxes", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "P_up", "units": "millimolar_per_second", "component": "Ca_intracellular_fluxes", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "j_Ca_dif", "units": "millimolar_per_second", "component": "Ca_intracellular_fluxes", "type": VariableType.ALGEBRAIC},
    {"name": "j_up", "units": "millimolar_per_second", "component": "Ca_intracellular_fluxes", "type": VariableType.ALGEBRAIC},
    {"name": "j_tr", "units": "millimolar_per_second", "component": "Ca_intracellular_fluxes", "type": VariableType.ALGEBRAIC},
    {"name": "delta_fTC", "units": "per_second", "component": "Ca_buffering", "type": VariableType.ALGEBRAIC},
    {"name": "delta_fTMC", "units": "per_second", "component": "Ca_buffering", "type": VariableType.ALGEBRAIC},
    {"name": "delta_fTMM", "units": "per_second", "component": "Ca_buffering", "type": VariableType.ALGEBRAIC},
    {"name": "delta_fCMi", "units": "per_second", "component": "Ca_buffering", "type": VariableType.ALGEBRAIC},
    {"name": "delta_fCMs", "units": "per_second", "component": "Ca_buffering", "type": VariableType.ALGEBRAIC},
    {"name": "delta_fCQ", "units": "per_second", "component": "Ca_buffering", "type": VariableType.ALGEBRAIC},
    {"name": "V_cell", "units": "millimetre3", "component": "Cell_parameters", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "V_sub", "units": "millimetre3", "component": "Cell_parameters", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "V_jsr", "units": "millimetre3", "component": "Cell_parameters", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "V_i", "units": "millimetre3", "component": "Cell_parameters", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "V_nsr", "units": "millimetre3", "component": "Cell_parameters", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "RTONF", "units": "millivolt", "component": "Membrane", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "V_clamp", "units": "millivolt", "component": "Voltage_clamp", "type": VariableType.ALGEBRAIC},
    {"name": "G_f", "units": "microS", "component": "i_f", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "G_f_K", "units": "microS", "component": "i_f", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "G_f_Na", "units": "microS", "component": "i_f", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "g_f_Na", "units": "microS", "component": "i_f", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "g_f_K", "units": "microS", "component": "i_f", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "ACh_shift", "units": "millivolt", "component": "i_f_y_gate", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "Iso_shift", "units": "millivolt", "component": "i_f_y_gate", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "E_mh", "units": "millivolt", "component": "i_Na", "type": VariableType.ALGEBRAIC},
    {"name": "Iso_increase", "units": "dimensionless", "component": "i_CaL", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "ACh_block", "units": "dimensionless", "component": "i_CaL", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "Iso_shift_dL", "units": "millivolt", "component": "i_CaL_dL_gate", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "Iso_slope_dL", "units": "dimensionless", "component": "i_CaL_dL_gate", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "fCa_infinity", "units": "dimensionless", "component": "i_CaL_fCa_gate", "type": VariableType.ALGEBRAIC},
    {"name": "tau_fCa", "units": "second", "component": "i_CaL_fCa_gate", "type": VariableType.ALGEBRAIC},
    {"name": "g_Ks", "units": "microS", "component": "i_Ks", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "E_Ks", "units": "millivolt", "component": "i_Ks", "type": VariableType.ALGEBRAIC},
    {"name": "Iso_shift", "units": "millivolt", "component": "i_Ks_n_gate", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "alpha_a", "units": "per_second", "component": "i_KACh_a_gate", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "E_Na", "units": "millivolt", "component": "Ionic_values", "type": VariableType.ALGEBRAIC},
    {"name": "E_K", "units": "millivolt", "component": "Ionic_values", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "E_Ca", "units": "millivolt", "component": "Ionic_values", "type": VariableType.ALGEBRAIC},
    {"name": "V", "units": "millivolt", "component": "Membrane", "type": VariableType.ALGEBRAIC},
    {"name": "i_fNa", "units": "nanoA", "component": "i_f", "type": VariableType.ALGEBRAIC},
    {"name": "i_fK", "units": "nanoA", "component": "i_f", "type": VariableType.ALGEBRAIC},
    {"name": "i_f", "units": "nanoA", "component": "i_f", "type": VariableType.ALGEBRAIC},
    {"name": "tau_y", "units": "second", "component": "i_f_y_gate", "type": VariableType.ALGEBRAIC},
    {"name": "y_infinity", "units": "dimensionless", "component": "i_f_y_gate", "type": VariableType.ALGEBRAIC},
    {"name": "i_Na_", "units": "nanoA", "component": "i_Na", "type": VariableType.ALGEBRAIC},
    {"name": "i_Na_L", "units": "nanoA", "component": "i_Na", "type": VariableType.ALGEBRAIC},
    {"name": "i_Na", "units": "nanoA", "component": "i_Na", "type": VariableType.ALGEBRAIC},
    {"name": "m_infinity", "units": "dimensionless", "component": "i_Na_m_gate", "type": VariableType.ALGEBRAIC},
    {"name": "E0_m", "units": "millivolt", "component": "i_Na_m_gate", "type": VariableType.ALGEBRAIC},
    {"name": "alpha_m", "units": "per_second", "component": "i_Na_m_gate", "type": VariableType.ALGEBRAIC},
    {"name": "beta_m", "units": "per_second", "component": "i_Na_m_gate", "type": VariableType.ALGEBRAIC},
    {"name": "tau_m", "units": "second", "component": "i_Na_m_gate", "type": VariableType.ALGEBRAIC},
    {"name": "h_infinity", "units": "dimensionless", "component": "i_Na_h_gate", "type": VariableType.ALGEBRAIC},
    {"name": "alpha_h", "units": "per_second", "component": "i_Na_h_gate", "type": VariableType.ALGEBRAIC},
    {"name": "beta_h", "units": "per_second", "component": "i_Na_h_gate", "type": VariableType.ALGEBRAIC},
    {"name": "tau_h", "units": "second", "component": "i_Na_h_gate", "type": VariableType.ALGEBRAIC},
    {"name": "i_Kur", "units": "nanoA", "component": "i_Kur", "type": VariableType.ALGEBRAIC},
    {"name": "r_Kur_infinity", "units": "dimensionless", "component": "i_Kur_rKur_gate", "type": VariableType.ALGEBRAIC},
    {"name": "tau_r_Kur", "units": "second", "component": "i_Kur_rKur_gate", "type": VariableType.ALGEBRAIC},
    {"name": "s_Kur_infinity", "units": "dimensionless", "component": "i_Kur_sKur_gate", "type": VariableType.ALGEBRAIC},
    {"name": "tau_s_Kur", "units": "second", "component": "i_Kur_sKur_gate", "type": VariableType.ALGEBRAIC},
    {"name": "i_siCa", "units": "nanoA", "component": "i_CaL", "type": VariableType.ALGEBRAIC},
    {"name": "i_siK", "units": "nanoA", "component": "i_CaL", "type": VariableType.ALGEBRAIC},
    {"name": "i_siNa", "units": "nanoA", "component": "i_CaL", "type": VariableType.ALGEBRAIC},
    {"name": "i_CaL", "units": "nanoA", "component": "i_CaL", "type": VariableType.ALGEBRAIC},
    {"name": "dL_infinity", "units": "dimensionless", "component": "i_CaL_dL_gate", "type": VariableType.ALGEBRAIC},
    {"name": "adVm", "units": "millivolt", "component": "i_CaL_dL_gate", "type": VariableType.ALGEBRAIC},
    {"name": "bdVm", "units": "millivolt", "component": "i_CaL_dL_gate", "type": VariableType.ALGEBRAIC},
    {"name": "fL_infinity", "units": "dimensionless", "component": "i_CaL_fL_gate", "type": VariableType.ALGEBRAIC},
    {"name": "tau_fL", "units": "second", "component": "i_CaL_fL_gate", "type": VariableType.ALGEBRAIC},
    {"name": "i_CaT", "units": "nanoA", "component": "i_CaT", "type": VariableType.ALGEBRAIC},
    {"name": "dT_infinity", "units": "dimensionless", "component": "i_CaT_dT_gate", "type": VariableType.ALGEBRAIC},
    {"name": "tau_dT", "units": "second", "component": "i_CaT_dT_gate", "type": VariableType.ALGEBRAIC},
    {"name": "fT_infinity", "units": "dimensionless", "component": "i_CaT_fT_gate", "type": VariableType.ALGEBRAIC},
    {"name": "tau_fT", "units": "second", "component": "i_CaT_fT_gate", "type": VariableType.ALGEBRAIC},
    {"name": "i_to", "units": "nanoA", "component": "i_to", "type": VariableType.ALGEBRAIC},
    {"name": "q_infinity", "units": "dimensionless", "component": "i_to_q_gate", "type": VariableType.ALGEBRAIC},
    {"name": "tau_q", "units": "second", "component": "i_to_q_gate", "type": VariableType.ALGEBRAIC},
    {"name": "r_infinity", "units": "dimensionless", "component": "i_to_r_gate", "type": VariableType.ALGEBRAIC},
    {"name": "tau_r", "units": "second", "component": "i_to_r_gate", "type": VariableType.ALGEBRAIC},
    {"name": "i_Kr", "units": "nanoA", "component": "i_Kr", "type": VariableType.ALGEBRAIC},
    {"name": "alfapaF", "units": "per_second", "component": "i_Kr_pa_gate", "type": VariableType.ALGEBRAIC},
    {"name": "betapaF", "units": "per_second", "component": "i_Kr_pa_gate", "type": VariableType.ALGEBRAIC},
    {"name": "pa_infinity", "units": "dimensionless", "component": "i_Kr_pa_gate", "type": VariableType.ALGEBRAIC},
    {"name": "tau_paS", "units": "second", "component": "i_Kr_pa_gate", "type": VariableType.ALGEBRAIC},
    {"name": "tau_paF", "units": "second", "component": "i_Kr_pa_gate", "type": VariableType.ALGEBRAIC},
    {"name": "tau_pi", "units": "second", "component": "i_Kr_pi_gate", "type": VariableType.ALGEBRAIC},
    {"name": "pi_infinity", "units": "dimensionless", "component": "i_Kr_pi_gate", "type": VariableType.ALGEBRAIC},
    {"name": "i_Ks", "units": "nanoA", "component": "i_Ks", "type": VariableType.ALGEBRAIC},
    {"name": "n_infinity", "units": "dimensionless", "component": "i_Ks_n_gate", "type": VariableType.ALGEBRAIC},
    {"name": "alpha_n", "units": "per_second", "component": "i_Ks_n_gate", "type": VariableType.ALGEBRAIC},
    {"name": "beta_n", "units": "per_second", "component": "i_Ks_n_gate", "type": VariableType.ALGEBRAIC},
    {"name": "i_KACh", "units": "nanoA", "component": "i_KACh", "type": VariableType.ALGEBRAIC},
    {"name": "beta_a", "units": "per_second", "component": "i_KACh_a_gate", "type": VariableType.ALGEBRAIC},
    {"name": "a_infinity", "units": "dimensionless", "component": "i_KACh_a_gate", "type": VariableType.ALGEBRAIC},
    {"name": "tau_a", "units": "second", "component": "i_KACh_a_gate", "type": VariableType.ALGEBRAIC},
    {"name": "i_NaK", "units": "nanoA", "component": "i_NaK", "type": VariableType.ALGEBRAIC},
    {"name": "k41", "units": "dimensionless", "component": "i_NaCa", "type": VariableType.ALGEBRAIC},
    {"name": "di", "units": "dimensionless", "component": "i_NaCa", "type": VariableType.ALGEBRAIC},
    {"name": "k32", "units": "dimensionless", "component": "i_NaCa", "type": VariableType.ALGEBRAIC},
    {"name": "do", "units": "dimensionless", "component": "i_NaCa", "type": VariableType.ALGEBRAIC},
    {"name": "alpha_dL", "units": "per_second", "component": "i_CaL_dL_gate", "type": VariableType.ALGEBRAIC},
    {"name": "beta_dL", "units": "per_second", "component": "i_CaL_dL_gate", "type": VariableType.ALGEBRAIC},
    {"name": "tau_n", "units": "second", "component": "i_Ks_n_gate", "type": VariableType.ALGEBRAIC},
    {"name": "k12", "units": "dimensionless", "component": "i_NaCa", "type": VariableType.ALGEBRAIC},
    {"name": "k14", "units": "dimensionless", "component": "i_NaCa", "type": VariableType.ALGEBRAIC},
    {"name": "k21", "units": "dimensionless", "component": "i_NaCa", "type": VariableType.ALGEBRAIC},
    {"name": "k23", "units": "dimensionless", "component": "i_NaCa", "type": VariableType.ALGEBRAIC},
    {"name": "tau_dL", "units": "second", "component": "i_CaL_dL_gate", "type": VariableType.ALGEBRAIC},
    {"name": "x1", "units": "dimensionless", "component": "i_NaCa", "type": VariableType.ALGEBRAIC},
    {"name": "x2", "units": "dimensionless", "component": "i_NaCa", "type": VariableType.ALGEBRAIC},
    {"name": "x3", "units": "dimensionless", "component": "i_NaCa", "type": VariableType.ALGEBRAIC},
    {"name": "x4", "units": "dimensionless", "component": "i_NaCa", "type": VariableType.ALGEBRAIC},
    {"name": "i_NaCa", "units": "nanoA", "component": "i_NaCa", "type": VariableType.ALGEBRAIC},
    {"name": "i_tot", "units": "nanoA", "component": "Membrane", "type": VariableType.ALGEBRAIC}
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


def initialise_states_and_constants(states, variables):
    variables[0] = 0.45
    variables[1] = 2.5
    variables[2] = 15.0
    variables[3] = 1.0
    variables[4] = 500.0
    variables[5] = 5.0
    variables[6] = 10000.0
    variables[7] = 660.0
    variables[8] = 148041085.1
    variables[9] = 0.045
    variables[10] = 10.0
    variables[11] = 2.5
    variables[12] = 0.031
    variables[13] = 0.062
    variables[14] = 542.0
    variables[15] = 445.0
    variables[16] = 446.0
    variables[17] = 7.51
    variables[18] = 751.0
    variables[19] = 1.642e6
    variables[20] = 175.4
    variables[21] = 88800.0
    variables[22] = 227700.0
    variables[23] = 2277.0
    variables[24] = 0.000286113
    variables[25] = 5.0
    variables[26] = 5.0e-5
    variables[27] = 5.469e-5
    variables[28] = 0.04
    variables[29] = 67.0
    variables[30] = 0.02
    variables[31] = 3.9
    variables[32] = 0.46
    variables[33] = 0.0012
    variables[34] = 0.0116
    variables[35] = 1.8
    variables[36] = 140.0
    variables[37] = 5.4
    variables[38] = 140.0
    variables[39] = 5.7e-5
    variables[40] = 96485.3415
    variables[41] = 8314.472
    variables[42] = 310.0
    variables[43] = 0.0
    variables[44] = 1.0
    variables[45] = 0.0
    variables[46] = 0.0
    variables[47] = -45.0
    variables[48] = -35.0
    variables[49] = 0.5
    variables[50] = 0.5
    variables[51] = 0.4578
    variables[52] = -16.4508
    variables[53] = 4.3371
    variables[54] = 0.000338
    variables[55] = 0.0075
    variables[56] = 0.0
    variables[57] = 0.0
    variables[58] = 0.04132
    variables[59] = 0.0
    variables[60] = 1.0
    variables[61] = 0.00345
    variables[62] = 0.00424
    variables[63] = 0.00065
    variables[64] = 0.1539e-3
    variables[65] = 0.0223
    variables[66] = 0.0
    variables[67] = 395.3
    variables[68] = 1628.0
    variables[69] = 2.289
    variables[70] = 561.4
    variables[71] = 26.44
    variables[72] = 4.663
    variables[73] = 3.343
    variables[74] = 0.0207
    variables[75] = 26.44
    variables[76] = 3.663
    variables[77] = 0.1369
    variables[78] = 0.0
    variables[79] = 0.4315
    variables[80] = 0.0
    variables[81] = 1.4
    variables[82] = 14.0
    variables[83] = 0.08105
    variables[84] = 1.0e-5
    variables[85] = 45.0
    variables[86] = 0.5927
    variables[87] = 0.0
    variables[88] = 0.00427
    variables[89] = 0.0
    variables[90] = 3.5e-3
    states[0] = 0.9308
    states[1] = 6.181512e-9
    states[2] = 4.595622e-10
    states[3] = 0.069199
    states[4] = 0.409551
    states[5] = 0.844449
    states[6] = 0.017929
    states[7] = 0.259947
    states[8] = 0.653777
    states[9] = 0.217311
    states[10] = 0.158521
    states[11] = 0.138975
    states[12] = 9.15641e-6
    states[13] = 0.435148
    states[14] = 0.009508
    states[15] = 0.447724
    states[16] = 0.003058
    states[17] = 0.846702
    states[18] = 0.268909
    states[19] = 0.020484
    states[20] = 0.430836
    states[21] = 0.014523
    states[22] = 0.283185
    states[23] = 0.011068
    states[24] = 0.709051
    states[25] = 0.00277
    states[26] = 0.011845
    states[27] = 0.845304
    states[28] = 0.1162
    states[29] = 0.001921
    states[30] = 6.226104e-5
    states[31] = -47.787168
    states[32] = 5.0


def compute_computed_constants(variables):
    variables[92] = 1.2 if gt_func(variables[46], 0.0) else 1.0
    variables[94] = variables[38]/(variables[72]+variables[38])
    variables[101] = -0.25 if gt_func(variables[46], 0.0) else 0.7*variables[45]/(0.00009+variables[45]) if gt_func(variables[45], 0.0) else 0.0
    variables[102] = variables[25]*(1.0-variables[101])
    variables[112] = 0.000000001*3.14159265358979*pow(variables[31], 2.0)*variables[29]
    variables[113] = 0.000000001*2.0*3.14159265358979*variables[30]*(variables[31]-variables[30]/2.0)*variables[29]
    variables[114] = variables[33]*variables[112]
    variables[115] = variables[32]*variables[112]-variables[113]
    variables[116] = variables[34]*variables[112]
    variables[117] = variables[41]*variables[42]/variables[40]
    variables[119] = variables[88]/(variables[37]/(variables[37]+variables[85]))
    variables[120] = variables[119]/(variables[86]+1.0)
    variables[121] = variables[86]*variables[120]
    variables[122] = variables[121]*variables[37]/(variables[37]+variables[85])
    variables[123] = variables[120]*variables[37]/(variables[37]+variables[85])
    variables[124] = -1.0-9.898*pow(1.0*variables[45], 0.618)/(pow(1.0*variables[45], 0.618)+0.00122423) if gt_func(variables[45], 0.0) else 0.0
    variables[125] = 7.5 if gt_func(variables[46], 0.0) else 0.0
    variables[127] = 1.23 if gt_func(variables[46], 0.0) else 1.0
    variables[128] = 0.31*variables[45]/(variables[45]+0.00009)
    variables[129] = -8.0 if gt_func(variables[46], 0.0) else 0.0
    variables[130] = -27.0 if gt_func(variables[46], 0.0) else 0.0
    variables[133] = 1.2*variables[63] if gt_func(variables[46], 0.0) else variables[63]
    variables[135] = -14.0 if gt_func(variables[46], 0.0) else 0.0
    variables[136] = (3.5988-0.025641)/(1.0+0.0000012155/pow(1.0*variables[45], 1.6951))+0.025641
    variables[138] = variables[117]*log(variables[37]/variables[36])


def compute_rates(voi, states, rates, variables):
    variables[97] = variables[2]-(variables[2]-variables[3])/(1.0+pow(variables[0]/states[4], variables[1]))
    variables[99] = variables[4]*variables[97]
    variables[98] = variables[6]/variables[97]
    rates[0] = variables[5]*states[3]-variables[99]*states[30]*states[0]-(variables[98]*pow(states[30], 2.0)*states[0]-variables[7]*states[1])
    rates[1] = variables[98]*pow(states[30], 2.0)*states[0]-variables[7]*states[1]-(variables[99]*states[30]*states[1]-variables[5]*states[2])
    rates[2] = variables[99]*states[30]*states[1]-variables[5]*states[2]-(variables[7]*states[2]-variables[98]*pow(states[30], 2.0)*states[3])
    rates[3] = variables[7]*states[2]-variables[98]*pow(states[30], 2.0)*states[3]-(variables[5]*states[3]-variables[99]*states[30]*states[0])
    variables[105] = (states[13]-states[4])/variables[28]
    variables[95] = variables[8]*states[1]*(states[4]-states[30])
    variables[111] = variables[20]*states[4]*(1.0-states[11])-variables[15]*states[11]
    rates[4] = variables[105]-(variables[95]+variables[10]*variables[111])
    variables[131] = variables[54]/(variables[54]+states[30])
    variables[132] = 0.001*variables[131]/variables[55]
    rates[5] = (variables[131]-states[5])/variables[132]
    variables[106] = variables[21]*states[12]*(1.0-states[6])-variables[16]*states[6]
    rates[6] = variables[106]
    variables[107] = variables[22]*states[12]*(1.0-(states[7]+states[8]))-variables[17]*states[7]
    rates[7] = variables[107]
    variables[108] = variables[23]*variables[11]*(1.0-(states[7]+states[8]))-variables[18]*states[8]
    rates[8] = variables[108]
    variables[109] = variables[19]*states[12]*(1.0-states[9])-variables[14]*states[9]
    rates[9] = variables[109]
    variables[110] = variables[19]*states[30]*(1.0-states[10])-variables[14]*states[10]
    rates[10] = variables[110]
    rates[11] = variables[111]
    variables[103] = (states[30]-states[12])/variables[27]
    variables[104] = variables[102]/(1.0+exp((-states[12]+variables[24])/variables[26]))
    rates[12] = 1.0*(variables[103]*variables[113]-variables[104]*variables[116])/variables[115]-(variables[9]*variables[109]+variables[12]*variables[106]+variables[13]*variables[107])
    rates[13] = variables[104]-variables[105]*variables[114]/variables[116]
    variables[118] = variables[48] if and_func(gt_func(voi, variables[49]), lt_func(voi, variables[49]+variables[50])) else variables[47]
    variables[140] = variables[118] if geq_func(variables[43], 1.0) else states[31]
    variables[145] = 0.01329+0.99921/(1.0+exp((variables[140]+97.134-variables[124]-variables[125]-variables[89])/8.1752)) if lt_func(variables[140], -(80.0-variables[124]-variables[125]-variables[89])) else 0.0002501*exp(-(variables[140]-variables[124]-variables[125]-variables[89])/12.861)
    variables[144] = 1.0/(0.36*(variables[140]+148.8-variables[124]-variables[125])/(exp(0.066*(variables[140]+148.8-variables[124]-variables[125]))-1.0)+0.1*(variables[140]+87.3-variables[124]-variables[125])/(1.0-exp(-0.2*(variables[140]+87.3-variables[124]-variables[125]))))-0.054
    rates[14] = (variables[145]-states[14])/variables[144]
    variables[149] = 1.0/(1.0+exp(-(variables[140]+42.0504)/8.3106))
    variables[150] = variables[140]+41.0
    variables[151] = 2000.0 if lt_func(fabs(variables[150]), variables[84]) else 200.0*variables[150]/(1.0-exp(-0.1*variables[150]))
    variables[152] = 8000.0*exp(-0.056*(variables[140]+66.0))
    variables[153] = 1.0/(variables[151]+variables[152])
    rates[15] = (variables[149]-states[15])/variables[153]
    variables[154] = 1.0/(1.0+exp((variables[140]+69.804)/4.4565))
    variables[155] = 20.0*exp(-0.125*(variables[140]+75.0))
    variables[156] = 2000.0/(320.0*exp(-0.1*(variables[140]+75.0))+1.0)
    variables[157] = 1.0/(variables[155]+variables[156])
    rates[16] = (variables[154]-states[16])/variables[157]
    variables[170] = 1.0/(1.0+exp((variables[140]+37.4+variables[57])/(5.3+variables[56])))
    variables[171] = 0.001*(44.3+230.0*exp(-pow((variables[140]+36.0)/10.0, 2.0)))
    rates[17] = (variables[170]-states[17])/variables[171]
    variables[173] = 1.0/(1.0+exp(-(variables[140]+38.3)/5.5))
    variables[174] = 0.001/(1.068*exp((variables[140]+38.3)/30.0)+1.068*exp(-(variables[140]+38.3)/30.0))
    rates[18] = (variables[173]-states[18])/variables[174]
    variables[175] = 1.0/(1.0+exp((variables[140]+58.7)/3.8))
    variables[176] = 1.0/(16.67*exp(-(variables[140]+75.0)/83.3)+16.67*exp((variables[140]+75.0)/15.38))+variables[59]
    rates[19] = (variables[175]-states[19])/variables[176]
    variables[178] = 1.0/(1.0+exp((variables[140]+49.0)/13.0))
    variables[179] = 0.001*0.6*(65.17/(0.57*exp(-0.08*(variables[140]+44.0))+0.065*exp(0.1*(variables[140]+45.93)))+10.1)
    rates[20] = (variables[178]-states[20])/variables[179]
    variables[180] = 1.0/(1.0+exp(-(variables[140]-19.3)/15.0))
    variables[181] = 0.001*0.66*1.4*(15.59/(1.037*exp(0.09*(variables[140]+30.61))+0.369*exp(-0.12*(variables[140]+23.84)))+2.98)
    rates[21] = (variables[180]-states[21])/variables[181]
    variables[185] = 1.0/(1.0+exp(-(variables[140]+10.0144)/7.6607))
    variables[186] = 0.84655354/(4.2*exp(variables[140]/17.0)+0.15*exp(-variables[140]/21.6))
    rates[22] = (variables[185]-states[22])/variables[186]
    variables[187] = 1.0/(30.0*exp(variables[140]/10.0)+exp(-variables[140]/12.0))
    rates[23] = (variables[185]-states[23])/variables[187]
    variables[189] = 1.0/(1.0+exp((variables[140]+28.6)/17.1))
    variables[188] = 1.0/(100.0*exp(-variables[140]/54.645)+656.0*exp(variables[140]/106.157))
    rates[24] = (variables[189]-states[24])/variables[188]
    variables[195] = 10.0*exp(0.0133*(variables[140]+40.0))
    variables[196] = variables[136]/(variables[136]+variables[195])
    variables[197] = 1.0/(variables[136]+variables[195])
    rates[25] = (variables[196]-states[25])/variables[197]
    variables[159] = 1.0/(1.0+exp((variables[140]+6.0)/-8.6))
    variables[160] = 0.009/(1.0+exp((variables[140]+5.0)/12.0))+0.0005
    rates[26] = (variables[159]-states[26])/variables[160]
    variables[161] = 1.0/(1.0+exp((variables[140]+7.5)/10.0))
    variables[162] = 0.59/(1.0+exp((variables[140]+60.0)/10.0))+3.05
    rates[27] = (variables[161]-states[27])/variables[162]
    variables[191] = sqrt(1.0/(1.0+exp(-(variables[140]+0.6383-variables[135])/10.7071)))
    variables[192] = 28.0/(1.0+exp(-(variables[140]-40.0-variables[135])/3.0))
    variables[193] = 1.0*exp(-(variables[140]-variables[135]-5.0)/25.0)
    variables[205] = 1.0/(variables[192]+variables[193])
    rates[28] = (variables[191]-states[28])/variables[205]
    variables[167] = 1.0/(1.0+exp(-(variables[140]-variables[52]-variables[129])/(variables[53]*(1.0+variables[130]/100.0))))
    variables[168] = -41.80001 if eq_func(variables[140], -41.8) else 0.0 if eq_func(variables[140], 0.0) else -6.80001 if eq_func(variables[140], -6.8) else variables[140]
    variables[203] = -0.02839*(variables[168]+41.8)/(exp(-(variables[168]+41.8)/2.5)-1.0)-0.0849*(variables[168]+6.8)/(exp(-(variables[168]+6.8)/4.8)-1.0)
    variables[169] = -1.80001 if eq_func(variables[140], -1.8) else variables[140]
    variables[204] = 0.01143*(variables[169]+1.8)/(exp((variables[169]+1.8)/2.5)-1.0)
    variables[210] = 0.001/(variables[203]+variables[204])
    rates[29] = (variables[167]-states[29])/variables[210]
    variables[163] = 2.0*variables[51]*(variables[140]-0.0)/(variables[117]*(1.0-exp(-1.0*(variables[140]-0.0)*2.0/variables[117])))*(states[30]-variables[35]*exp(-2.0*(variables[140]-0.0)/variables[117]))*states[29]*states[17]*states[5]
    variables[172] = 2.0*variables[58]*variables[140]/(variables[117]*(1.0-exp(-1.0*variables[140]*2.0/variables[117])))*(states[30]-variables[35]*exp(-2.0*variables[140]/variables[117]))*states[18]*states[19]
    variables[202] = 1.0+variables[35]/variables[76]*(1.0+exp(variables[78]*variables[140]/variables[117]))+variables[38]/variables[68]*(1.0+variables[38]/variables[70]*(1.0+variables[38]/variables[72]))
    variables[208] = variables[35]/variables[76]*exp(variables[78]*variables[140]/variables[117])/variables[202]
    variables[91] = states[32]
    variables[200] = 1.0+states[30]/variables[74]*(1.0+exp(-variables[77]*variables[140]/variables[117])+variables[91]/variables[75])+variables[91]/variables[67]*(1.0+variables[91]/variables[69]*(1.0+variables[91]/variables[71]))
    variables[206] = states[30]/variables[74]*exp(-variables[77]*variables[140]/variables[117])/variables[200]
    variables[93] = variables[91]/(variables[71]+variables[91])
    variables[201] = exp(variables[79]*variables[140]/(2.0*variables[117]))
    variables[199] = exp(-variables[79]*variables[140]/(2.0*variables[117]))
    variables[207] = variables[91]/variables[67]*variables[91]/variables[69]*(1.0+variables[91]/variables[71])*exp(variables[79]*variables[140]/(2.0*variables[117]))/variables[200]
    variables[212] = variables[201]*variables[93]*(variables[207]+variables[206])+variables[199]*variables[206]*(variables[94]+variables[201])
    variables[209] = variables[38]/variables[68]*variables[38]/variables[70]*(1.0+variables[38]/variables[72])*exp(-variables[79]*variables[140]/(2.0*variables[117]))/variables[202]
    variables[211] = variables[199]*variables[94]*(variables[209]+variables[208])+variables[208]*variables[201]*(variables[93]+variables[199])
    variables[214] = variables[209]*variables[94]*(variables[207]+variables[206])+variables[207]*variables[208]*(variables[94]+variables[201])
    variables[213] = variables[207]*variables[93]*(variables[209]+variables[208])+variables[206]*variables[209]*(variables[93]+variables[199])
    variables[215] = (1.0-variables[80])*variables[73]*(variables[212]*variables[208]-variables[211]*variables[206])/(variables[211]+variables[212]+variables[213]+variables[214])
    rates[30] = variables[95]*variables[114]/variables[113]-((variables[163]+variables[172]-2.0*variables[215])/(2.0*variables[40]*variables[113])+variables[103]+variables[9]*variables[110])
    variables[137] = variables[117]*log(variables[38]/variables[91])
    variables[141] = states[14]*variables[122]*(variables[140]-variables[137])*(1.0-variables[87])
    variables[142] = states[14]*variables[123]*(variables[140]-variables[138])*(1.0-variables[87])
    variables[143] = variables[141]+variables[142]
    variables[158] = variables[64]*states[26]*states[27]*(variables[140]-variables[138])
    variables[194] = variables[60]*variables[61]*(variables[140]-variables[138])*(1.0+exp((variables[140]+20.0)/20.0))*states[25] if gt_func(variables[45], 0.0) else 0.0
    variables[165] = 0.0000185*variables[51]*(variables[140]-0.0)/(variables[117]*(1.0-exp(-1.0*(variables[140]-0.0)/variables[117])))*(variables[91]-variables[38]*exp(-1.0*(variables[140]-0.0)/variables[117]))*states[29]*states[17]*states[5]
    variables[164] = 0.000365*variables[51]*(variables[140]-0.0)/(variables[117]*(1.0-exp(-1.0*(variables[140]-0.0)/variables[117])))*(variables[36]-variables[37]*exp(-1.0*(variables[140]-0.0)/variables[117]))*states[29]*states[17]*states[5]
    variables[166] = (variables[163]+variables[164]+variables[165])*(1.0-variables[128])*1.0*variables[127]
    variables[126] = variables[117]*log((variables[38]+0.12*variables[37])/(variables[91]+0.12*variables[36]))
    variables[146] = variables[65]*pow(states[15], 3.0)*states[16]*(variables[140]-variables[126])
    variables[147] = variables[66]*pow(states[15], 3.0)*(variables[140]-variables[126])
    variables[148] = variables[146]+variables[147]
    variables[198] = variables[92]*variables[83]*pow(1.0+pow(variables[81]/variables[37], 1.2), -1.0)*pow(1.0+pow(variables[82]/variables[91], 1.3), -1.0)*pow(1.0+exp(-(variables[140]-variables[137]+110.0)/20.0), -1.0)
    variables[177] = variables[90]*(variables[140]-variables[138])*states[20]*states[21]
    variables[134] = variables[117]*log((variables[37]+0.12*variables[38])/(variables[36]+0.12*variables[91]))
    variables[190] = variables[133]*(variables[140]-variables[134])*pow(states[28], 2.0)
    variables[182] = variables[62]*(variables[140]-variables[138])*(0.9*states[23]+0.1*states[22])*states[24]
    variables[216] = variables[143]+variables[182]+variables[190]+variables[177]+variables[198]+variables[215]+variables[148]+variables[166]+variables[172]+variables[194]+variables[158]
    rates[31] = -variables[216]/variables[39]
    rates[32] = (1.0-variables[44])*-1.0*(variables[148]+variables[141]+variables[165]+3.0*variables[198]+3.0*variables[215])/(1.0*(variables[115]+variables[113])*variables[40])


def compute_variables(voi, states, rates, variables):
    variables[91] = states[32]
    variables[93] = variables[91]/(variables[71]+variables[91])
    variables[95] = variables[8]*states[1]*(states[4]-states[30])
    variables[96] = states[4]-states[30]
    variables[97] = variables[2]-(variables[2]-variables[3])/(1.0+pow(variables[0]/states[4], variables[1]))
    variables[98] = variables[6]/variables[97]
    variables[99] = variables[4]*variables[97]
    variables[100] = states[0]+states[1]+states[2]+states[3]
    variables[103] = (states[30]-states[12])/variables[27]
    variables[104] = variables[102]/(1.0+exp((-states[12]+variables[24])/variables[26]))
    variables[105] = (states[13]-states[4])/variables[28]
    variables[106] = variables[21]*states[12]*(1.0-states[6])-variables[16]*states[6]
    variables[107] = variables[22]*states[12]*(1.0-(states[7]+states[8]))-variables[17]*states[7]
    variables[108] = variables[23]*variables[11]*(1.0-(states[7]+states[8]))-variables[18]*states[8]
    variables[109] = variables[19]*states[12]*(1.0-states[9])-variables[14]*states[9]
    variables[110] = variables[19]*states[30]*(1.0-states[10])-variables[14]*states[10]
    variables[111] = variables[20]*states[4]*(1.0-states[11])-variables[15]*states[11]
    variables[126] = variables[117]*log((variables[38]+0.12*variables[37])/(variables[91]+0.12*variables[36]))
    variables[131] = variables[54]/(variables[54]+states[30])
    variables[132] = 0.001*variables[131]/variables[55]
    variables[134] = variables[117]*log((variables[37]+0.12*variables[38])/(variables[36]+0.12*variables[91]))
    variables[137] = variables[117]*log(variables[38]/variables[91])
    variables[139] = 0.5*variables[117]*log(variables[35]/states[30])
    variables[140] = variables[118] if geq_func(variables[43], 1.0) else states[31]
    variables[141] = states[14]*variables[122]*(variables[140]-variables[137])*(1.0-variables[87])
    variables[142] = states[14]*variables[123]*(variables[140]-variables[138])*(1.0-variables[87])
    variables[143] = variables[141]+variables[142]
    variables[144] = 1.0/(0.36*(variables[140]+148.8-variables[124]-variables[125])/(exp(0.066*(variables[140]+148.8-variables[124]-variables[125]))-1.0)+0.1*(variables[140]+87.3-variables[124]-variables[125])/(1.0-exp(-0.2*(variables[140]+87.3-variables[124]-variables[125]))))-0.054
    variables[145] = 0.01329+0.99921/(1.0+exp((variables[140]+97.134-variables[124]-variables[125]-variables[89])/8.1752)) if lt_func(variables[140], -(80.0-variables[124]-variables[125]-variables[89])) else 0.0002501*exp(-(variables[140]-variables[124]-variables[125]-variables[89])/12.861)
    variables[146] = variables[65]*pow(states[15], 3.0)*states[16]*(variables[140]-variables[126])
    variables[147] = variables[66]*pow(states[15], 3.0)*(variables[140]-variables[126])
    variables[148] = variables[146]+variables[147]
    variables[149] = 1.0/(1.0+exp(-(variables[140]+42.0504)/8.3106))
    variables[150] = variables[140]+41.0
    variables[151] = 2000.0 if lt_func(fabs(variables[150]), variables[84]) else 200.0*variables[150]/(1.0-exp(-0.1*variables[150]))
    variables[152] = 8000.0*exp(-0.056*(variables[140]+66.0))
    variables[153] = 1.0/(variables[151]+variables[152])
    variables[154] = 1.0/(1.0+exp((variables[140]+69.804)/4.4565))
    variables[155] = 20.0*exp(-0.125*(variables[140]+75.0))
    variables[156] = 2000.0/(320.0*exp(-0.1*(variables[140]+75.0))+1.0)
    variables[157] = 1.0/(variables[155]+variables[156])
    variables[158] = variables[64]*states[26]*states[27]*(variables[140]-variables[138])
    variables[159] = 1.0/(1.0+exp((variables[140]+6.0)/-8.6))
    variables[160] = 0.009/(1.0+exp((variables[140]+5.0)/12.0))+0.0005
    variables[161] = 1.0/(1.0+exp((variables[140]+7.5)/10.0))
    variables[162] = 0.59/(1.0+exp((variables[140]+60.0)/10.0))+3.05
    variables[163] = 2.0*variables[51]*(variables[140]-0.0)/(variables[117]*(1.0-exp(-1.0*(variables[140]-0.0)*2.0/variables[117])))*(states[30]-variables[35]*exp(-2.0*(variables[140]-0.0)/variables[117]))*states[29]*states[17]*states[5]
    variables[164] = 0.000365*variables[51]*(variables[140]-0.0)/(variables[117]*(1.0-exp(-1.0*(variables[140]-0.0)/variables[117])))*(variables[36]-variables[37]*exp(-1.0*(variables[140]-0.0)/variables[117]))*states[29]*states[17]*states[5]
    variables[165] = 0.0000185*variables[51]*(variables[140]-0.0)/(variables[117]*(1.0-exp(-1.0*(variables[140]-0.0)/variables[117])))*(variables[91]-variables[38]*exp(-1.0*(variables[140]-0.0)/variables[117]))*states[29]*states[17]*states[5]
    variables[166] = (variables[163]+variables[164]+variables[165])*(1.0-variables[128])*1.0*variables[127]
    variables[167] = 1.0/(1.0+exp(-(variables[140]-variables[52]-variables[129])/(variables[53]*(1.0+variables[130]/100.0))))
    variables[168] = -41.80001 if eq_func(variables[140], -41.8) else 0.0 if eq_func(variables[140], 0.0) else -6.80001 if eq_func(variables[140], -6.8) else variables[140]
    variables[169] = -1.80001 if eq_func(variables[140], -1.8) else variables[140]
    variables[170] = 1.0/(1.0+exp((variables[140]+37.4+variables[57])/(5.3+variables[56])))
    variables[171] = 0.001*(44.3+230.0*exp(-pow((variables[140]+36.0)/10.0, 2.0)))
    variables[172] = 2.0*variables[58]*variables[140]/(variables[117]*(1.0-exp(-1.0*variables[140]*2.0/variables[117])))*(states[30]-variables[35]*exp(-2.0*variables[140]/variables[117]))*states[18]*states[19]
    variables[173] = 1.0/(1.0+exp(-(variables[140]+38.3)/5.5))
    variables[174] = 0.001/(1.068*exp((variables[140]+38.3)/30.0)+1.068*exp(-(variables[140]+38.3)/30.0))
    variables[175] = 1.0/(1.0+exp((variables[140]+58.7)/3.8))
    variables[176] = 1.0/(16.67*exp(-(variables[140]+75.0)/83.3)+16.67*exp((variables[140]+75.0)/15.38))+variables[59]
    variables[177] = variables[90]*(variables[140]-variables[138])*states[20]*states[21]
    variables[178] = 1.0/(1.0+exp((variables[140]+49.0)/13.0))
    variables[179] = 0.001*0.6*(65.17/(0.57*exp(-0.08*(variables[140]+44.0))+0.065*exp(0.1*(variables[140]+45.93)))+10.1)
    variables[180] = 1.0/(1.0+exp(-(variables[140]-19.3)/15.0))
    variables[181] = 0.001*0.66*1.4*(15.59/(1.037*exp(0.09*(variables[140]+30.61))+0.369*exp(-0.12*(variables[140]+23.84)))+2.98)
    variables[182] = variables[62]*(variables[140]-variables[138])*(0.9*states[23]+0.1*states[22])*states[24]
    variables[183] = 1.0/(1.0+exp(-(variables[140]+23.2)/6.6))/(0.84655354/(37.2*exp(variables[140]/11.9)+0.96*exp(-variables[140]/18.5)))
    variables[184] = 4.0*((37.2*exp(variables[140]/15.9)+0.96*exp(-variables[140]/22.5))/0.84655354-1.0/(1.0+exp(-(variables[140]+23.2)/10.6))/(0.84655354/(37.2*exp(variables[140]/15.9)+0.96*exp(-variables[140]/22.5))))
    variables[185] = 1.0/(1.0+exp(-(variables[140]+10.0144)/7.6607))
    variables[186] = 0.84655354/(4.2*exp(variables[140]/17.0)+0.15*exp(-variables[140]/21.6))
    variables[187] = 1.0/(30.0*exp(variables[140]/10.0)+exp(-variables[140]/12.0))
    variables[188] = 1.0/(100.0*exp(-variables[140]/54.645)+656.0*exp(variables[140]/106.157))
    variables[189] = 1.0/(1.0+exp((variables[140]+28.6)/17.1))
    variables[190] = variables[133]*(variables[140]-variables[134])*pow(states[28], 2.0)
    variables[191] = sqrt(1.0/(1.0+exp(-(variables[140]+0.6383-variables[135])/10.7071)))
    variables[192] = 28.0/(1.0+exp(-(variables[140]-40.0-variables[135])/3.0))
    variables[193] = 1.0*exp(-(variables[140]-variables[135]-5.0)/25.0)
    variables[194] = variables[60]*variables[61]*(variables[140]-variables[138])*(1.0+exp((variables[140]+20.0)/20.0))*states[25] if gt_func(variables[45], 0.0) else 0.0
    variables[195] = 10.0*exp(0.0133*(variables[140]+40.0))
    variables[196] = variables[136]/(variables[136]+variables[195])
    variables[197] = 1.0/(variables[136]+variables[195])
    variables[198] = variables[92]*variables[83]*pow(1.0+pow(variables[81]/variables[37], 1.2), -1.0)*pow(1.0+pow(variables[82]/variables[91], 1.3), -1.0)*pow(1.0+exp(-(variables[140]-variables[137]+110.0)/20.0), -1.0)
    variables[199] = exp(-variables[79]*variables[140]/(2.0*variables[117]))
    variables[200] = 1.0+states[30]/variables[74]*(1.0+exp(-variables[77]*variables[140]/variables[117])+variables[91]/variables[75])+variables[91]/variables[67]*(1.0+variables[91]/variables[69]*(1.0+variables[91]/variables[71]))
    variables[201] = exp(variables[79]*variables[140]/(2.0*variables[117]))
    variables[202] = 1.0+variables[35]/variables[76]*(1.0+exp(variables[78]*variables[140]/variables[117]))+variables[38]/variables[68]*(1.0+variables[38]/variables[70]*(1.0+variables[38]/variables[72]))
    variables[203] = -0.02839*(variables[168]+41.8)/(exp(-(variables[168]+41.8)/2.5)-1.0)-0.0849*(variables[168]+6.8)/(exp(-(variables[168]+6.8)/4.8)-1.0)
    variables[204] = 0.01143*(variables[169]+1.8)/(exp((variables[169]+1.8)/2.5)-1.0)
    variables[205] = 1.0/(variables[192]+variables[193])
    variables[206] = states[30]/variables[74]*exp(-variables[77]*variables[140]/variables[117])/variables[200]
    variables[207] = variables[91]/variables[67]*variables[91]/variables[69]*(1.0+variables[91]/variables[71])*exp(variables[79]*variables[140]/(2.0*variables[117]))/variables[200]
    variables[208] = variables[35]/variables[76]*exp(variables[78]*variables[140]/variables[117])/variables[202]
    variables[209] = variables[38]/variables[68]*variables[38]/variables[70]*(1.0+variables[38]/variables[72])*exp(-variables[79]*variables[140]/(2.0*variables[117]))/variables[202]
    variables[210] = 0.001/(variables[203]+variables[204])
    variables[211] = variables[199]*variables[94]*(variables[209]+variables[208])+variables[208]*variables[201]*(variables[93]+variables[199])
    variables[212] = variables[201]*variables[93]*(variables[207]+variables[206])+variables[199]*variables[206]*(variables[94]+variables[201])
    variables[213] = variables[207]*variables[93]*(variables[209]+variables[208])+variables[206]*variables[209]*(variables[93]+variables[199])
    variables[214] = variables[209]*variables[94]*(variables[207]+variables[206])+variables[207]*variables[208]*(variables[94]+variables[201])
    variables[215] = (1.0-variables[80])*variables[73]*(variables[212]*variables[208]-variables[211]*variables[206])/(variables[211]+variables[212]+variables[213]+variables[214])
    variables[216] = variables[143]+variables[182]+variables[190]+variables[177]+variables[198]+variables[215]+variables[148]+variables[166]+variables[172]+variables[194]+variables[158]

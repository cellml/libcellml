# The content of this file was generated using the Python profile of libCellML 0.5.0.

from enum import Enum
from math import *


__version__ = "0.5.0"
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
    constants[0] = 0.0
    constants[1] = 0.0
    constants[4] = 140.0
    constants[7] = 5.4
    constants[8] = 140.0
    constants[10] = 1.8
    constants[11] = 1.0
    constants[17] = 96485.3415
    constants[22] = 14.0
    constants[23] = 1.4
    constants[24] = 0.08105
    constants[25] = 0.0
    constants[30] = 3.343
    constants[39] = 26.44
    constants[40] = 0.0207
    constants[41] = 0.1369
    constants[43] = 395.3
    constants[44] = 2.289
    constants[45] = 0.4315
    constants[46] = 26.44
    constants[47] = 4.663
    constants[48] = 3.663
    constants[49] = 0.0
    constants[51] = 1628.0
    constants[52] = 561.4
    constants[54] = 148041085.1
    constants[57] = 15.0
    constants[58] = 1.0
    constants[59] = 0.45
    constants[60] = 2.5
    constants[62] = 10000.0
    constants[64] = 500.0
    constants[65] = 5.0
    constants[66] = 660.0
    constants[70] = 5.0
    constants[72] = 5.469e-5
    constants[74] = 0.000286113
    constants[75] = 5.0e-5
    constants[77] = 0.04
    constants[79] = 88800.0
    constants[80] = 446.0
    constants[82] = 227700.0
    constants[83] = 7.51
    constants[85] = 2277.0
    constants[86] = 2.5
    constants[87] = 751.0
    constants[89] = 1.642e6
    constants[90] = 542.0
    constants[93] = 175.4
    constants[94] = 445.0
    constants[95] = 0.031
    constants[96] = 0.062
    constants[97] = 0.045
    constants[98] = 10.0
    constants[104] = 67.0
    constants[105] = 3.9
    constants[106] = 0.02
    constants[107] = 0.0012
    constants[108] = 0.46
    constants[109] = 0.0116
    constants[118] = 5.7e-5
    constants[119] = 8314.472
    constants[120] = 310.0
    constants[122] = 0.0
    constants[123] = -35.0
    constants[124] = 0.5
    constants[125] = 0.5
    constants[126] = -45.0
    constants[128] = 0.00427
    constants[129] = 45.0
    constants[131] = 0.5927
    constants[135] = 0.0
    constants[141] = 0.0
    constants[144] = 0.0223
    constants[146] = 0.0
    constants[150] = 1.0e-5
    constants[157] = 0.1539e-3
    constants[163] = 0.4578
    constants[169] = -16.4508
    constants[170] = 4.3371
    constants[177] = 0.0
    constants[178] = 0.0
    constants[181] = 0.000338
    constants[183] = 0.0075
    constants[184] = 0.04132
    constants[189] = 0.0
    constants[190] = 3.5e-3
    constants[195] = 0.00424
    constants[204] = 0.00065
    constants[211] = 1.0
    constants[212] = 0.00345
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


def compute_computed_constants(constants, computed_constants):
    computed_constants[3] = constants[119]*constants[120]/constants[17]
    computed_constants[6] = computed_constants[3]*log(constants[7]/constants[8])
    computed_constants[20] = 1.2 if gt_func(constants[1], 0.0) else 1.0
    computed_constants[35] = constants[4]/(constants[47]+constants[4])
    computed_constants[68] = -0.25 if gt_func(constants[1], 0.0) else 0.7*constants[0]/(0.00009+constants[0]) if gt_func(constants[0], 0.0) else 0.0
    computed_constants[69] = constants[70]*(1.0-computed_constants[68])
    computed_constants[103] = 0.000000001*3.14159265358979*pow(constants[105], 2.0)*constants[104]
    computed_constants[19] = 0.000000001*2.0*3.14159265358979*constants[106]*(constants[105]-constants[106]/2.0)*constants[104]
    computed_constants[100] = constants[107]*computed_constants[103]
    computed_constants[18] = constants[108]*computed_constants[103]-computed_constants[19]
    computed_constants[99] = constants[109]*computed_constants[103]
    computed_constants[127] = constants[128]/(constants[7]/(constants[7]+constants[129]))
    computed_constants[130] = computed_constants[127]/(constants[131]+1.0)
    computed_constants[132] = constants[131]*computed_constants[130]
    computed_constants[133] = computed_constants[132]*constants[7]/(constants[7]+constants[129])
    computed_constants[134] = computed_constants[130]*constants[7]/(constants[7]+constants[129])
    computed_constants[137] = -1.0-9.898*pow(1.0*constants[0], 0.618)/(pow(1.0*constants[0], 0.618)+0.00122423) if gt_func(constants[0], 0.0) else 0.0
    computed_constants[138] = 7.5 if gt_func(constants[1], 0.0) else 0.0
    computed_constants[162] = 1.23 if gt_func(constants[1], 0.0) else 1.0
    computed_constants[165] = 0.31*constants[0]/(constants[0]+0.00009)
    computed_constants[166] = -8.0 if gt_func(constants[1], 0.0) else 0.0
    computed_constants[167] = -27.0 if gt_func(constants[1], 0.0) else 0.0
    computed_constants[203] = 1.2*constants[204] if gt_func(constants[1], 0.0) else constants[204]
    computed_constants[206] = -14.0 if gt_func(constants[1], 0.0) else 0.0
    computed_constants[213] = (3.5988-0.025641)/(1.0+0.0000012155/pow(1.0*constants[0], 1.6951))+0.025641


def compute_rates(voi, states, rates, constants, computed_constants, algebraic):
    algebraic[5] = states[1]
    algebraic[142] = computed_constants[3]*log((constants[4]+0.12*constants[7])/(algebraic[5]+0.12*constants[8]))
    algebraic[121] = constants[123] if and_func(gt_func(voi, constants[124]), lt_func(voi, constants[124]+constants[125])) else constants[126]
    algebraic[21] = algebraic[121] if geq_func(constants[122], 1.0) else states[15]
    algebraic[143] = constants[144]*pow(states[18], 3.0)*states[17]*(algebraic[21]-algebraic[142])
    algebraic[145] = constants[146]*pow(states[18], 3.0)*(algebraic[21]-algebraic[142])
    algebraic[12] = algebraic[143]+algebraic[145]
    algebraic[15] = 0.0000185*constants[163]*(algebraic[21]-0.0)/(computed_constants[3]*(1.0-exp(-1.0*(algebraic[21]-0.0)/computed_constants[3])))*(algebraic[5]-constants[4]*exp(-1.0*(algebraic[21]-0.0)/computed_constants[3]))*states[23]*states[22]*states[21]
    algebraic[2] = computed_constants[3]*log(constants[4]/algebraic[5])
    algebraic[16] = states[16]*computed_constants[133]*(algebraic[21]-algebraic[2])*(1.0-constants[135])
    algebraic[14] = computed_constants[20]*constants[24]*pow(1.0+pow(constants[23]/constants[7], 1.2), -1.0)*pow(1.0+pow(constants[22]/algebraic[5], 1.3), -1.0)*pow(1.0+exp(-(algebraic[21]-algebraic[2]+110.0)/20.0), -1.0)
    algebraic[50] = 1.0+constants[10]/constants[48]*(1.0+exp(constants[49]*algebraic[21]/computed_constants[3]))+constants[4]/constants[51]*(1.0+constants[4]/constants[52]*(1.0+constants[4]/constants[47]))
    algebraic[27] = constants[10]/constants[48]*exp(constants[49]*algebraic[21]/computed_constants[3])/algebraic[50]
    algebraic[42] = 1.0+states[0]/constants[40]*(1.0+exp(-constants[41]*algebraic[21]/computed_constants[3])+algebraic[5]/constants[46])+algebraic[5]/constants[43]*(1.0+algebraic[5]/constants[44]*(1.0+algebraic[5]/constants[39]))
    algebraic[29] = states[0]/constants[40]*exp(-constants[41]*algebraic[21]/computed_constants[3])/algebraic[42]
    algebraic[36] = algebraic[5]/(constants[39]+algebraic[5])
    algebraic[37] = exp(constants[45]*algebraic[21]/(2.0*computed_constants[3]))
    algebraic[33] = exp(-constants[45]*algebraic[21]/(2.0*computed_constants[3]))
    algebraic[38] = algebraic[5]/constants[43]*algebraic[5]/constants[44]*(1.0+algebraic[5]/constants[39])*exp(constants[45]*algebraic[21]/(2.0*computed_constants[3]))/algebraic[42]
    algebraic[26] = algebraic[37]*algebraic[36]*(algebraic[38]+algebraic[29])+algebraic[33]*algebraic[29]*(computed_constants[35]+algebraic[37])
    algebraic[34] = constants[4]/constants[51]*constants[4]/constants[52]*(1.0+constants[4]/constants[47])*exp(-constants[45]*algebraic[21]/(2.0*computed_constants[3]))/algebraic[50]
    algebraic[28] = algebraic[33]*computed_constants[35]*(algebraic[34]+algebraic[27])+algebraic[27]*algebraic[37]*(algebraic[36]+algebraic[33])
    algebraic[31] = algebraic[34]*computed_constants[35]*(algebraic[38]+algebraic[29])+algebraic[38]*algebraic[27]*(computed_constants[35]+algebraic[37])
    algebraic[32] = algebraic[38]*algebraic[36]*(algebraic[34]+algebraic[27])+algebraic[29]*algebraic[34]*(algebraic[36]+algebraic[33])
    algebraic[13] = (1.0-constants[25])*constants[30]*(algebraic[26]*algebraic[27]-algebraic[28]*algebraic[29])/(algebraic[28]+algebraic[26]+algebraic[32]+algebraic[31])
    rates[1] = (1.0-constants[11])*-1.0*(algebraic[12]+algebraic[16]+algebraic[15]+3.0*algebraic[14]+3.0*algebraic[13])/(1.0*(computed_constants[18]+computed_constants[19])*constants[17])
    algebraic[56] = constants[57]-(constants[57]-constants[58])/(1.0+pow(constants[59]/states[2], constants[60]))
    algebraic[63] = constants[64]*algebraic[56]
    algebraic[61] = constants[62]/algebraic[56]
    rates[4] = constants[65]*states[5]-algebraic[63]*states[0]*states[4]-(algebraic[61]*pow(states[0], 2.0)*states[4]-constants[66]*states[3])
    rates[3] = algebraic[61]*pow(states[0], 2.0)*states[4]-constants[66]*states[3]-(algebraic[63]*states[0]*states[3]-constants[65]*states[6])
    rates[6] = algebraic[63]*states[0]*states[3]-constants[65]*states[6]-(constants[66]*states[6]-algebraic[61]*pow(states[0], 2.0)*states[5])
    rates[5] = constants[66]*states[6]-algebraic[61]*pow(states[0], 2.0)*states[5]-(constants[65]*states[5]-algebraic[63]*states[0]*states[4])
    algebraic[78] = constants[79]*states[7]*(1.0-states[9])-constants[80]*states[9]
    rates[9] = algebraic[78]
    algebraic[81] = constants[82]*states[7]*(1.0-(states[10]+states[11]))-constants[83]*states[10]
    rates[10] = algebraic[81]
    algebraic[84] = constants[85]*constants[86]*(1.0-(states[10]+states[11]))-constants[87]*states[11]
    rates[11] = algebraic[84]
    algebraic[88] = constants[89]*states[7]*(1.0-states[12])-constants[90]*states[12]
    rates[12] = algebraic[88]
    algebraic[91] = constants[89]*states[0]*(1.0-states[13])-constants[90]*states[13]
    rates[13] = algebraic[91]
    algebraic[92] = constants[93]*states[2]*(1.0-states[14])-constants[94]*states[14]
    rates[14] = algebraic[92]
    algebraic[71] = (states[0]-states[7])/constants[72]
    algebraic[73] = computed_constants[69]/(1.0+exp((-states[7]+constants[74])/constants[75]))
    rates[7] = 1.0*(algebraic[71]*computed_constants[19]-algebraic[73]*computed_constants[99])/computed_constants[18]-(constants[97]*algebraic[88]+constants[95]*algebraic[78]+constants[96]*algebraic[81])
    algebraic[53] = constants[54]*states[3]*(states[2]-states[0])
    algebraic[101] = 2.0*constants[163]*(algebraic[21]-0.0)/(computed_constants[3]*(1.0-exp(-1.0*(algebraic[21]-0.0)*2.0/computed_constants[3])))*(states[0]-constants[10]*exp(-2.0*(algebraic[21]-0.0)/computed_constants[3]))*states[23]*states[22]*states[21]
    algebraic[102] = 2.0*constants[184]*algebraic[21]/(computed_constants[3]*(1.0-exp(-1.0*algebraic[21]*2.0/computed_constants[3])))*(states[0]-constants[10]*exp(-2.0*algebraic[21]/computed_constants[3]))*states[25]*states[24]
    rates[0] = algebraic[53]*computed_constants[100]/computed_constants[19]-((algebraic[101]+algebraic[102]-2.0*algebraic[13])/(2.0*constants[17]*computed_constants[19])+algebraic[71]+constants[97]*algebraic[91])
    algebraic[76] = (states[8]-states[2])/constants[77]
    rates[8] = algebraic[73]-algebraic[76]*computed_constants[100]/computed_constants[99]
    rates[2] = algebraic[76]-(algebraic[53]+constants[98]*algebraic[92])
    algebraic[136] = states[16]*computed_constants[134]*(algebraic[21]-computed_constants[6])*(1.0-constants[135])
    algebraic[111] = algebraic[16]+algebraic[136]
    algebraic[112] = constants[157]*states[20]*states[19]*(algebraic[21]-computed_constants[6])
    algebraic[113] = constants[211]*constants[212]*(algebraic[21]-computed_constants[6])*(1.0+exp((algebraic[21]+20.0)/20.0))*states[32] if gt_func(constants[0], 0.0) else 0.0
    algebraic[164] = 0.000365*constants[163]*(algebraic[21]-0.0)/(computed_constants[3]*(1.0-exp(-1.0*(algebraic[21]-0.0)/computed_constants[3])))*(constants[8]-constants[7]*exp(-1.0*(algebraic[21]-0.0)/computed_constants[3]))*states[23]*states[22]*states[21]
    algebraic[114] = (algebraic[101]+algebraic[164]+algebraic[15])*(1.0-computed_constants[165])*1.0*computed_constants[162]
    algebraic[115] = constants[190]*(algebraic[21]-computed_constants[6])*states[27]*states[26]
    algebraic[205] = computed_constants[3]*log((constants[7]+0.12*constants[4])/(constants[8]+0.12*algebraic[5]))
    algebraic[116] = computed_constants[203]*(algebraic[21]-algebraic[205])*pow(states[31], 2.0)
    algebraic[117] = constants[195]*(algebraic[21]-computed_constants[6])*(0.9*states[29]+0.1*states[30])*states[28]
    algebraic[110] = algebraic[111]+algebraic[117]+algebraic[116]+algebraic[115]+algebraic[14]+algebraic[13]+algebraic[12]+algebraic[114]+algebraic[102]+algebraic[113]+algebraic[112]
    rates[15] = -algebraic[110]/constants[118]
    algebraic[140] = 0.01329+0.99921/(1.0+exp((algebraic[21]+97.134-computed_constants[137]-computed_constants[138]-constants[141])/8.1752)) if lt_func(algebraic[21], -(80.0-computed_constants[137]-computed_constants[138]-constants[141])) else 0.0002501*exp(-(algebraic[21]-computed_constants[137]-computed_constants[138]-constants[141])/12.861)
    algebraic[139] = 1.0/(0.36*(algebraic[21]+148.8-computed_constants[137]-computed_constants[138])/(exp(0.066*(algebraic[21]+148.8-computed_constants[137]-computed_constants[138]))-1.0)+0.1*(algebraic[21]+87.3-computed_constants[137]-computed_constants[138])/(1.0-exp(-0.2*(algebraic[21]+87.3-computed_constants[137]-computed_constants[138]))))-0.054
    rates[16] = (algebraic[140]-states[16])/algebraic[139]
    algebraic[147] = 1.0/(1.0+exp(-(algebraic[21]+42.0504)/8.3106))
    algebraic[148] = algebraic[21]+41.0
    algebraic[149] = 2000.0 if lt_func(fabs(algebraic[148]), constants[150]) else 200.0*algebraic[148]/(1.0-exp(-0.1*algebraic[148]))
    algebraic[151] = 8000.0*exp(-0.056*(algebraic[21]+66.0))
    algebraic[152] = 1.0/(algebraic[149]+algebraic[151])
    rates[18] = (algebraic[147]-states[18])/algebraic[152]
    algebraic[153] = 1.0/(1.0+exp((algebraic[21]+69.804)/4.4565))
    algebraic[154] = 20.0*exp(-0.125*(algebraic[21]+75.0))
    algebraic[155] = 2000.0/(320.0*exp(-0.1*(algebraic[21]+75.0))+1.0)
    algebraic[156] = 1.0/(algebraic[154]+algebraic[155])
    rates[17] = (algebraic[153]-states[17])/algebraic[156]
    algebraic[158] = 1.0/(1.0+exp((algebraic[21]+6.0)/-8.6))
    algebraic[159] = 0.009/(1.0+exp((algebraic[21]+5.0)/12.0))+0.0005
    rates[20] = (algebraic[158]-states[20])/algebraic[159]
    algebraic[160] = 1.0/(1.0+exp((algebraic[21]+7.5)/10.0))
    algebraic[161] = 0.59/(1.0+exp((algebraic[21]+60.0)/10.0))+3.05
    rates[19] = (algebraic[160]-states[19])/algebraic[161]
    algebraic[168] = 1.0/(1.0+exp(-(algebraic[21]-constants[169]-computed_constants[166])/(constants[170]*(1.0+computed_constants[167]/100.0))))
    algebraic[174] = -41.80001 if eq_func(algebraic[21], -41.8) else 0.0 if eq_func(algebraic[21], 0.0) else -6.80001 if eq_func(algebraic[21], -6.8) else algebraic[21]
    algebraic[172] = -0.02839*(algebraic[174]+41.8)/(exp(-(algebraic[174]+41.8)/2.5)-1.0)-0.0849*(algebraic[174]+6.8)/(exp(-(algebraic[174]+6.8)/4.8)-1.0)
    algebraic[175] = -1.80001 if eq_func(algebraic[21], -1.8) else algebraic[21]
    algebraic[173] = 0.01143*(algebraic[175]+1.8)/(exp((algebraic[175]+1.8)/2.5)-1.0)
    algebraic[171] = 0.001/(algebraic[172]+algebraic[173])
    rates[23] = (algebraic[168]-states[23])/algebraic[171]
    algebraic[176] = 1.0/(1.0+exp((algebraic[21]+37.4+constants[177])/(5.3+constants[178])))
    algebraic[179] = 0.001*(44.3+230.0*exp(-pow((algebraic[21]+36.0)/10.0, 2.0)))
    rates[22] = (algebraic[176]-states[22])/algebraic[179]
    algebraic[180] = constants[181]/(constants[181]+states[0])
    algebraic[182] = 0.001*algebraic[180]/constants[183]
    rates[21] = (algebraic[180]-states[21])/algebraic[182]
    algebraic[185] = 1.0/(1.0+exp(-(algebraic[21]+38.3)/5.5))
    algebraic[186] = 0.001/(1.068*exp((algebraic[21]+38.3)/30.0)+1.068*exp(-(algebraic[21]+38.3)/30.0))
    rates[25] = (algebraic[185]-states[25])/algebraic[186]
    algebraic[187] = 1.0/(1.0+exp((algebraic[21]+58.7)/3.8))
    algebraic[188] = 1.0/(16.67*exp(-(algebraic[21]+75.0)/83.3)+16.67*exp((algebraic[21]+75.0)/15.38))+constants[189]
    rates[24] = (algebraic[187]-states[24])/algebraic[188]
    algebraic[191] = 1.0/(1.0+exp((algebraic[21]+49.0)/13.0))
    algebraic[192] = 0.001*0.6*(65.17/(0.57*exp(-0.08*(algebraic[21]+44.0))+0.065*exp(0.1*(algebraic[21]+45.93)))+10.1)
    rates[27] = (algebraic[191]-states[27])/algebraic[192]
    algebraic[193] = 1.0/(1.0+exp(-(algebraic[21]-19.3)/15.0))
    algebraic[194] = 0.001*0.66*1.4*(15.59/(1.037*exp(0.09*(algebraic[21]+30.61))+0.369*exp(-0.12*(algebraic[21]+23.84)))+2.98)
    rates[26] = (algebraic[193]-states[26])/algebraic[194]
    algebraic[198] = 1.0/(1.0+exp(-(algebraic[21]+10.0144)/7.6607))
    algebraic[199] = 0.84655354/(4.2*exp(algebraic[21]/17.0)+0.15*exp(-algebraic[21]/21.6))
    rates[30] = (algebraic[198]-states[30])/algebraic[199]
    algebraic[200] = 1.0/(30.0*exp(algebraic[21]/10.0)+exp(-algebraic[21]/12.0))
    rates[29] = (algebraic[198]-states[29])/algebraic[200]
    algebraic[202] = 1.0/(1.0+exp((algebraic[21]+28.6)/17.1))
    algebraic[201] = 1.0/(100.0*exp(-algebraic[21]/54.645)+656.0*exp(algebraic[21]/106.157))
    rates[28] = (algebraic[202]-states[28])/algebraic[201]
    algebraic[207] = sqrt(1.0/(1.0+exp(-(algebraic[21]+0.6383-computed_constants[206])/10.7071)))
    algebraic[209] = 28.0/(1.0+exp(-(algebraic[21]-40.0-computed_constants[206])/3.0))
    algebraic[210] = 1.0*exp(-(algebraic[21]-computed_constants[206]-5.0)/25.0)
    algebraic[208] = 1.0/(algebraic[209]+algebraic[210])
    rates[31] = (algebraic[207]-states[31])/algebraic[208]
    algebraic[214] = 10.0*exp(0.0133*(algebraic[21]+40.0))
    algebraic[215] = computed_constants[213]/(computed_constants[213]+algebraic[214])
    algebraic[216] = 1.0/(computed_constants[213]+algebraic[214])
    rates[32] = (algebraic[215]-states[32])/algebraic[216]


def compute_variables(voi, states, rates, constants, computed_constants, algebraic):
    algebraic[5] = states[1]
    algebraic[2] = computed_constants[3]*log(constants[4]/algebraic[5])
    algebraic[9] = 0.5*computed_constants[3]*log(constants[10]/states[0])
    algebraic[21] = algebraic[121] if geq_func(constants[122], 1.0) else states[15]
    algebraic[14] = computed_constants[20]*constants[24]*pow(1.0+pow(constants[23]/constants[7], 1.2), -1.0)*pow(1.0+pow(constants[22]/algebraic[5], 1.3), -1.0)*pow(1.0+exp(-(algebraic[21]-algebraic[2]+110.0)/20.0), -1.0)
    algebraic[50] = 1.0+constants[10]/constants[48]*(1.0+exp(constants[49]*algebraic[21]/computed_constants[3]))+constants[4]/constants[51]*(1.0+constants[4]/constants[52]*(1.0+constants[4]/constants[47]))
    algebraic[27] = constants[10]/constants[48]*exp(constants[49]*algebraic[21]/computed_constants[3])/algebraic[50]
    algebraic[42] = 1.0+states[0]/constants[40]*(1.0+exp(-constants[41]*algebraic[21]/computed_constants[3])+algebraic[5]/constants[46])+algebraic[5]/constants[43]*(1.0+algebraic[5]/constants[44]*(1.0+algebraic[5]/constants[39]))
    algebraic[29] = states[0]/constants[40]*exp(-constants[41]*algebraic[21]/computed_constants[3])/algebraic[42]
    algebraic[36] = algebraic[5]/(constants[39]+algebraic[5])
    algebraic[37] = exp(constants[45]*algebraic[21]/(2.0*computed_constants[3]))
    algebraic[33] = exp(-constants[45]*algebraic[21]/(2.0*computed_constants[3]))
    algebraic[38] = algebraic[5]/constants[43]*algebraic[5]/constants[44]*(1.0+algebraic[5]/constants[39])*exp(constants[45]*algebraic[21]/(2.0*computed_constants[3]))/algebraic[42]
    algebraic[26] = algebraic[37]*algebraic[36]*(algebraic[38]+algebraic[29])+algebraic[33]*algebraic[29]*(computed_constants[35]+algebraic[37])
    algebraic[34] = constants[4]/constants[51]*constants[4]/constants[52]*(1.0+constants[4]/constants[47])*exp(-constants[45]*algebraic[21]/(2.0*computed_constants[3]))/algebraic[50]
    algebraic[28] = algebraic[33]*computed_constants[35]*(algebraic[34]+algebraic[27])+algebraic[27]*algebraic[37]*(algebraic[36]+algebraic[33])
    algebraic[31] = algebraic[34]*computed_constants[35]*(algebraic[38]+algebraic[29])+algebraic[38]*algebraic[27]*(computed_constants[35]+algebraic[37])
    algebraic[32] = algebraic[38]*algebraic[36]*(algebraic[34]+algebraic[27])+algebraic[29]*algebraic[34]*(algebraic[36]+algebraic[33])
    algebraic[13] = (1.0-constants[25])*constants[30]*(algebraic[26]*algebraic[27]-algebraic[28]*algebraic[29])/(algebraic[28]+algebraic[26]+algebraic[32]+algebraic[31])
    algebraic[53] = constants[54]*states[3]*(states[2]-states[0])
    algebraic[55] = states[2]-states[0]
    algebraic[56] = constants[57]-(constants[57]-constants[58])/(1.0+pow(constants[59]/states[2], constants[60]))
    algebraic[61] = constants[62]/algebraic[56]
    algebraic[63] = constants[64]*algebraic[56]
    algebraic[67] = states[4]+states[3]+states[6]+states[5]
    algebraic[71] = (states[0]-states[7])/constants[72]
    algebraic[73] = computed_constants[69]/(1.0+exp((-states[7]+constants[74])/constants[75]))
    algebraic[76] = (states[8]-states[2])/constants[77]
    algebraic[78] = constants[79]*states[7]*(1.0-states[9])-constants[80]*states[9]
    algebraic[81] = constants[82]*states[7]*(1.0-(states[10]+states[11]))-constants[83]*states[10]
    algebraic[84] = constants[85]*constants[86]*(1.0-(states[10]+states[11]))-constants[87]*states[11]
    algebraic[88] = constants[89]*states[7]*(1.0-states[12])-constants[90]*states[12]
    algebraic[91] = constants[89]*states[0]*(1.0-states[13])-constants[90]*states[13]
    algebraic[92] = constants[93]*states[2]*(1.0-states[14])-constants[94]*states[14]
    algebraic[16] = states[16]*computed_constants[133]*(algebraic[21]-algebraic[2])*(1.0-constants[135])
    algebraic[136] = states[16]*computed_constants[134]*(algebraic[21]-computed_constants[6])*(1.0-constants[135])
    algebraic[111] = algebraic[16]+algebraic[136]
    algebraic[112] = constants[157]*states[20]*states[19]*(algebraic[21]-computed_constants[6])
    algebraic[113] = constants[211]*constants[212]*(algebraic[21]-computed_constants[6])*(1.0+exp((algebraic[21]+20.0)/20.0))*states[32] if gt_func(constants[0], 0.0) else 0.0
    algebraic[102] = 2.0*constants[184]*algebraic[21]/(computed_constants[3]*(1.0-exp(-1.0*algebraic[21]*2.0/computed_constants[3])))*(states[0]-constants[10]*exp(-2.0*algebraic[21]/computed_constants[3]))*states[25]*states[24]
    algebraic[101] = 2.0*constants[163]*(algebraic[21]-0.0)/(computed_constants[3]*(1.0-exp(-1.0*(algebraic[21]-0.0)*2.0/computed_constants[3])))*(states[0]-constants[10]*exp(-2.0*(algebraic[21]-0.0)/computed_constants[3]))*states[23]*states[22]*states[21]
    algebraic[15] = 0.0000185*constants[163]*(algebraic[21]-0.0)/(computed_constants[3]*(1.0-exp(-1.0*(algebraic[21]-0.0)/computed_constants[3])))*(algebraic[5]-constants[4]*exp(-1.0*(algebraic[21]-0.0)/computed_constants[3]))*states[23]*states[22]*states[21]
    algebraic[164] = 0.000365*constants[163]*(algebraic[21]-0.0)/(computed_constants[3]*(1.0-exp(-1.0*(algebraic[21]-0.0)/computed_constants[3])))*(constants[8]-constants[7]*exp(-1.0*(algebraic[21]-0.0)/computed_constants[3]))*states[23]*states[22]*states[21]
    algebraic[114] = (algebraic[101]+algebraic[164]+algebraic[15])*(1.0-computed_constants[165])*1.0*computed_constants[162]
    algebraic[142] = computed_constants[3]*log((constants[4]+0.12*constants[7])/(algebraic[5]+0.12*constants[8]))
    algebraic[143] = constants[144]*pow(states[18], 3.0)*states[17]*(algebraic[21]-algebraic[142])
    algebraic[145] = constants[146]*pow(states[18], 3.0)*(algebraic[21]-algebraic[142])
    algebraic[12] = algebraic[143]+algebraic[145]
    algebraic[115] = constants[190]*(algebraic[21]-computed_constants[6])*states[27]*states[26]
    algebraic[205] = computed_constants[3]*log((constants[7]+0.12*constants[4])/(constants[8]+0.12*algebraic[5]))
    algebraic[116] = computed_constants[203]*(algebraic[21]-algebraic[205])*pow(states[31], 2.0)
    algebraic[117] = constants[195]*(algebraic[21]-computed_constants[6])*(0.9*states[29]+0.1*states[30])*states[28]
    algebraic[110] = algebraic[111]+algebraic[117]+algebraic[116]+algebraic[115]+algebraic[14]+algebraic[13]+algebraic[12]+algebraic[114]+algebraic[102]+algebraic[113]+algebraic[112]
    algebraic[139] = 1.0/(0.36*(algebraic[21]+148.8-computed_constants[137]-computed_constants[138])/(exp(0.066*(algebraic[21]+148.8-computed_constants[137]-computed_constants[138]))-1.0)+0.1*(algebraic[21]+87.3-computed_constants[137]-computed_constants[138])/(1.0-exp(-0.2*(algebraic[21]+87.3-computed_constants[137]-computed_constants[138]))))-0.054
    algebraic[140] = 0.01329+0.99921/(1.0+exp((algebraic[21]+97.134-computed_constants[137]-computed_constants[138]-constants[141])/8.1752)) if lt_func(algebraic[21], -(80.0-computed_constants[137]-computed_constants[138]-constants[141])) else 0.0002501*exp(-(algebraic[21]-computed_constants[137]-computed_constants[138]-constants[141])/12.861)
    algebraic[147] = 1.0/(1.0+exp(-(algebraic[21]+42.0504)/8.3106))
    algebraic[148] = algebraic[21]+41.0
    algebraic[149] = 2000.0 if lt_func(fabs(algebraic[148]), constants[150]) else 200.0*algebraic[148]/(1.0-exp(-0.1*algebraic[148]))
    algebraic[151] = 8000.0*exp(-0.056*(algebraic[21]+66.0))
    algebraic[152] = 1.0/(algebraic[149]+algebraic[151])
    algebraic[153] = 1.0/(1.0+exp((algebraic[21]+69.804)/4.4565))
    algebraic[154] = 20.0*exp(-0.125*(algebraic[21]+75.0))
    algebraic[155] = 2000.0/(320.0*exp(-0.1*(algebraic[21]+75.0))+1.0)
    algebraic[156] = 1.0/(algebraic[154]+algebraic[155])
    algebraic[158] = 1.0/(1.0+exp((algebraic[21]+6.0)/-8.6))
    algebraic[159] = 0.009/(1.0+exp((algebraic[21]+5.0)/12.0))+0.0005
    algebraic[160] = 1.0/(1.0+exp((algebraic[21]+7.5)/10.0))
    algebraic[161] = 0.59/(1.0+exp((algebraic[21]+60.0)/10.0))+3.05
    algebraic[168] = 1.0/(1.0+exp(-(algebraic[21]-constants[169]-computed_constants[166])/(constants[170]*(1.0+computed_constants[167]/100.0))))
    algebraic[174] = -41.80001 if eq_func(algebraic[21], -41.8) else 0.0 if eq_func(algebraic[21], 0.0) else -6.80001 if eq_func(algebraic[21], -6.8) else algebraic[21]
    algebraic[172] = -0.02839*(algebraic[174]+41.8)/(exp(-(algebraic[174]+41.8)/2.5)-1.0)-0.0849*(algebraic[174]+6.8)/(exp(-(algebraic[174]+6.8)/4.8)-1.0)
    algebraic[175] = -1.80001 if eq_func(algebraic[21], -1.8) else algebraic[21]
    algebraic[173] = 0.01143*(algebraic[175]+1.8)/(exp((algebraic[175]+1.8)/2.5)-1.0)
    algebraic[171] = 0.001/(algebraic[172]+algebraic[173])
    algebraic[176] = 1.0/(1.0+exp((algebraic[21]+37.4+constants[177])/(5.3+constants[178])))
    algebraic[179] = 0.001*(44.3+230.0*exp(-pow((algebraic[21]+36.0)/10.0, 2.0)))
    algebraic[180] = constants[181]/(constants[181]+states[0])
    algebraic[182] = 0.001*algebraic[180]/constants[183]
    algebraic[185] = 1.0/(1.0+exp(-(algebraic[21]+38.3)/5.5))
    algebraic[186] = 0.001/(1.068*exp((algebraic[21]+38.3)/30.0)+1.068*exp(-(algebraic[21]+38.3)/30.0))
    algebraic[187] = 1.0/(1.0+exp((algebraic[21]+58.7)/3.8))
    algebraic[188] = 1.0/(16.67*exp(-(algebraic[21]+75.0)/83.3)+16.67*exp((algebraic[21]+75.0)/15.38))+constants[189]
    algebraic[191] = 1.0/(1.0+exp((algebraic[21]+49.0)/13.0))
    algebraic[192] = 0.001*0.6*(65.17/(0.57*exp(-0.08*(algebraic[21]+44.0))+0.065*exp(0.1*(algebraic[21]+45.93)))+10.1)
    algebraic[193] = 1.0/(1.0+exp(-(algebraic[21]-19.3)/15.0))
    algebraic[194] = 0.001*0.66*1.4*(15.59/(1.037*exp(0.09*(algebraic[21]+30.61))+0.369*exp(-0.12*(algebraic[21]+23.84)))+2.98)
    algebraic[196] = 1.0/(1.0+exp(-(algebraic[21]+23.2)/6.6))/(0.84655354/(37.2*exp(algebraic[21]/11.9)+0.96*exp(-algebraic[21]/18.5)))
    algebraic[197] = 4.0*((37.2*exp(algebraic[21]/15.9)+0.96*exp(-algebraic[21]/22.5))/0.84655354-1.0/(1.0+exp(-(algebraic[21]+23.2)/10.6))/(0.84655354/(37.2*exp(algebraic[21]/15.9)+0.96*exp(-algebraic[21]/22.5))))
    algebraic[198] = 1.0/(1.0+exp(-(algebraic[21]+10.0144)/7.6607))
    algebraic[199] = 0.84655354/(4.2*exp(algebraic[21]/17.0)+0.15*exp(-algebraic[21]/21.6))
    algebraic[200] = 1.0/(30.0*exp(algebraic[21]/10.0)+exp(-algebraic[21]/12.0))
    algebraic[201] = 1.0/(100.0*exp(-algebraic[21]/54.645)+656.0*exp(algebraic[21]/106.157))
    algebraic[202] = 1.0/(1.0+exp((algebraic[21]+28.6)/17.1))
    algebraic[207] = sqrt(1.0/(1.0+exp(-(algebraic[21]+0.6383-computed_constants[206])/10.7071)))
    algebraic[209] = 28.0/(1.0+exp(-(algebraic[21]-40.0-computed_constants[206])/3.0))
    algebraic[210] = 1.0*exp(-(algebraic[21]-computed_constants[206]-5.0)/25.0)
    algebraic[208] = 1.0/(algebraic[209]+algebraic[210])
    algebraic[214] = 10.0*exp(0.0133*(algebraic[21]+40.0))
    algebraic[215] = computed_constants[213]/(computed_constants[213]+algebraic[214])
    algebraic[216] = 1.0/(computed_constants[213]+algebraic[214])

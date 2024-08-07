# The content of this file was generated using the Python profile of libCellML 0.5.0.

from enum import Enum
from math import *


__version__ = "0.5.0"
LIBCELLML_VERSION = "0.5.0"

STATE_COUNT = 15
CONSTANT_COUNT = 0
COMPUTED_CONSTANT_COUNT = 0
ALGEBRAIC_COUNT = 185


class VariableType(Enum):
    VARIABLE_OF_INTEGRATION = 0
    STATE = 1
    CONSTANT = 2
    COMPUTED_CONSTANT = 3
    ALGEBRAIC = 4


VOI_INFO = {"name": "time", "units": "second", "component": "environment", "type": VariableType.VARIABLE_OF_INTEGRATION}

STATE_INFO = [
    {"name": "V", "units": "millivolt", "component": "membrane", "type": VariableType.STATE},
    {"name": "m", "units": "dimensionless", "component": "sodium_current_m_gate", "type": VariableType.STATE},
    {"name": "h1", "units": "dimensionless", "component": "sodium_current_h_gate", "type": VariableType.STATE},
    {"name": "h2", "units": "dimensionless", "component": "sodium_current_h_gate", "type": VariableType.STATE},
    {"name": "f_L", "units": "dimensionless", "component": "L_type_Ca_channel_f_gate", "type": VariableType.STATE},
    {"name": "d_L", "units": "dimensionless", "component": "L_type_Ca_channel_d_gate", "type": VariableType.STATE},
    {"name": "f_T", "units": "dimensionless", "component": "T_type_Ca_channel_f_gate", "type": VariableType.STATE},
    {"name": "d_T", "units": "dimensionless", "component": "T_type_Ca_channel_d_gate", "type": VariableType.STATE},
    {"name": "r", "units": "dimensionless", "component": "four_AP_sensitive_currents_r_gate", "type": VariableType.STATE},
    {"name": "q", "units": "dimensionless", "component": "four_AP_sensitive_currents_q_gate", "type": VariableType.STATE},
    {"name": "P_i", "units": "dimensionless", "component": "rapid_delayed_rectifying_potassium_current_P_i_gate", "type": VariableType.STATE},
    {"name": "P_af", "units": "dimensionless", "component": "rapid_delayed_rectifying_potassium_current_P_af_gate", "type": VariableType.STATE},
    {"name": "P_as", "units": "dimensionless", "component": "rapid_delayed_rectifying_potassium_current_P_as_gate", "type": VariableType.STATE},
    {"name": "xs", "units": "dimensionless", "component": "slow_delayed_rectifying_potassium_current_xs_gate", "type": VariableType.STATE},
    {"name": "y", "units": "dimensionless", "component": "hyperpolarisation_activated_current_y_gate", "type": VariableType.STATE}
]

VARIABLE_INFO = [
    {"name": "FCell", "units": "dimensionless", "component": "membrane", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "dCell", "units": "dimensionless", "component": "membrane", "type": VariableType.CONSTANT},
    {"name": "Version", "units": "dimensionless", "component": "membrane", "type": VariableType.CONSTANT},
    {"name": "FCellConstant", "units": "dimensionless", "component": "membrane", "type": VariableType.CONSTANT},
    {"name": "Cm", "units": "microF", "component": "membrane", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "CmCentre", "units": "microF", "component": "membrane", "type": VariableType.CONSTANT},
    {"name": "CmPeriphery", "units": "microF", "component": "membrane", "type": VariableType.CONSTANT},
    {"name": "i_Na", "units": "nanoA", "component": "sodium_current", "type": VariableType.ALGEBRAIC},
    {"name": "i_Ca_p", "units": "nanoA", "component": "persistent_calcium_current", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "i_p", "units": "nanoA", "component": "sodium_potassium_pump", "type": VariableType.ALGEBRAIC},
    {"name": "i_NaCa", "units": "nanoA", "component": "sodium_calcium_exchanger", "type": VariableType.ALGEBRAIC},
    {"name": "i_b_K", "units": "nanoA", "component": "potassium_background_current", "type": VariableType.ALGEBRAIC},
    {"name": "i_b_Ca", "units": "nanoA", "component": "calcium_background_current", "type": VariableType.ALGEBRAIC},
    {"name": "i_b_Na", "units": "nanoA", "component": "sodium_background_current", "type": VariableType.ALGEBRAIC},
    {"name": "i_f_K", "units": "nanoA", "component": "hyperpolarisation_activated_current", "type": VariableType.ALGEBRAIC},
    {"name": "i_f_Na", "units": "nanoA", "component": "hyperpolarisation_activated_current", "type": VariableType.ALGEBRAIC},
    {"name": "i_K_s", "units": "nanoA", "component": "slow_delayed_rectifying_potassium_current", "type": VariableType.ALGEBRAIC},
    {"name": "i_K_r", "units": "nanoA", "component": "rapid_delayed_rectifying_potassium_current", "type": VariableType.ALGEBRAIC},
    {"name": "i_sus", "units": "nanoA", "component": "four_AP_sensitive_currents", "type": VariableType.ALGEBRAIC},
    {"name": "i_to", "units": "nanoA", "component": "four_AP_sensitive_currents", "type": VariableType.ALGEBRAIC},
    {"name": "i_Ca_T", "units": "nanoA", "component": "T_type_Ca_channel", "type": VariableType.ALGEBRAIC},
    {"name": "i_Ca_L", "units": "nanoA", "component": "L_type_Ca_channel", "type": VariableType.ALGEBRAIC},
    {"name": "R", "units": "millijoule_per_mole_kelvin", "component": "membrane", "type": VariableType.CONSTANT},
    {"name": "T", "units": "kelvin", "component": "membrane", "type": VariableType.CONSTANT},
    {"name": "F", "units": "coulomb_per_mole", "component": "membrane", "type": VariableType.CONSTANT},
    {"name": "g_b_Na", "units": "microS", "component": "sodium_background_current", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "g_b_Na_Centre_Published", "units": "microS", "component": "sodium_background_current", "type": VariableType.CONSTANT},
    {"name": "g_b_Na_Periphery_Published", "units": "microS", "component": "sodium_background_current", "type": VariableType.CONSTANT},
    {"name": "g_b_Na_Centre_1DCapable", "units": "microS", "component": "sodium_background_current", "type": VariableType.CONSTANT},
    {"name": "g_b_Na_Periphery_1DCapable", "units": "microS", "component": "sodium_background_current", "type": VariableType.CONSTANT},
    {"name": "g_b_Na_Centre_0DCapable", "units": "microS", "component": "sodium_background_current", "type": VariableType.CONSTANT},
    {"name": "g_b_Na_Periphery_0DCapable", "units": "microS", "component": "sodium_background_current", "type": VariableType.CONSTANT},
    {"name": "E_Na", "units": "millivolt", "component": "reversal_and_equilibrium_potentials", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "g_b_K", "units": "microS", "component": "potassium_background_current", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "g_b_K_Centre_Published", "units": "microS", "component": "potassium_background_current", "type": VariableType.CONSTANT},
    {"name": "g_b_K_Periphery_Published", "units": "microS", "component": "potassium_background_current", "type": VariableType.CONSTANT},
    {"name": "g_b_K_Centre_1DCapable", "units": "microS", "component": "potassium_background_current", "type": VariableType.CONSTANT},
    {"name": "g_b_K_Periphery_1DCapable", "units": "microS", "component": "potassium_background_current", "type": VariableType.CONSTANT},
    {"name": "g_b_K_Centre_0DCapable", "units": "microS", "component": "potassium_background_current", "type": VariableType.CONSTANT},
    {"name": "g_b_K_Periphery_0DCapable", "units": "microS", "component": "potassium_background_current", "type": VariableType.CONSTANT},
    {"name": "E_K", "units": "millivolt", "component": "reversal_and_equilibrium_potentials", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "g_b_Ca", "units": "microS", "component": "calcium_background_current", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "g_b_Ca_Centre_Published", "units": "microS", "component": "calcium_background_current", "type": VariableType.CONSTANT},
    {"name": "g_b_Ca_Periphery_Published", "units": "microS", "component": "calcium_background_current", "type": VariableType.CONSTANT},
    {"name": "g_b_Ca_Centre_1DCapable", "units": "microS", "component": "calcium_background_current", "type": VariableType.CONSTANT},
    {"name": "g_b_Ca_Periphery_1DCapable", "units": "microS", "component": "calcium_background_current", "type": VariableType.CONSTANT},
    {"name": "g_b_Ca_Centre_0DCapable", "units": "microS", "component": "calcium_background_current", "type": VariableType.CONSTANT},
    {"name": "g_b_Ca_Periphery_0DCapable", "units": "microS", "component": "calcium_background_current", "type": VariableType.CONSTANT},
    {"name": "E_Ca", "units": "millivolt", "component": "reversal_and_equilibrium_potentials", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "k_NaCa", "units": "nanoA", "component": "sodium_calcium_exchanger", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "k_NaCa_Centre_Published", "units": "nanoA", "component": "sodium_calcium_exchanger", "type": VariableType.CONSTANT},
    {"name": "k_NaCa_Periphery_Published", "units": "nanoA", "component": "sodium_calcium_exchanger", "type": VariableType.CONSTANT},
    {"name": "k_NaCa_Centre_1DCapable", "units": "nanoA", "component": "sodium_calcium_exchanger", "type": VariableType.CONSTANT},
    {"name": "k_NaCa_Periphery_1DCapable", "units": "nanoA", "component": "sodium_calcium_exchanger", "type": VariableType.CONSTANT},
    {"name": "k_NaCa_Centre_0DCapable", "units": "nanoA", "component": "sodium_calcium_exchanger", "type": VariableType.CONSTANT},
    {"name": "k_NaCa_Periphery_0DCapable", "units": "nanoA", "component": "sodium_calcium_exchanger", "type": VariableType.CONSTANT},
    {"name": "Na_i", "units": "millimolar", "component": "ionic_concentrations", "type": VariableType.CONSTANT},
    {"name": "gamma_NaCa", "units": "dimensionless", "component": "sodium_calcium_exchanger", "type": VariableType.CONSTANT},
    {"name": "Ca_o", "units": "millimolar", "component": "ionic_concentrations", "type": VariableType.CONSTANT},
    {"name": "Na_o", "units": "millimolar", "component": "ionic_concentrations", "type": VariableType.CONSTANT},
    {"name": "Ca_i", "units": "millimolar", "component": "ionic_concentrations", "type": VariableType.CONSTANT},
    {"name": "d_NaCa", "units": "dimensionless", "component": "sodium_calcium_exchanger", "type": VariableType.CONSTANT},
    {"name": "i_p_max", "units": "nanoA", "component": "sodium_potassium_pump", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "i_p_max_Centre_Published", "units": "nanoA", "component": "sodium_potassium_pump", "type": VariableType.CONSTANT},
    {"name": "i_p_max_Periphery_Published", "units": "nanoA", "component": "sodium_potassium_pump", "type": VariableType.CONSTANT},
    {"name": "i_p_max_Centre_1DCapable", "units": "nanoA", "component": "sodium_potassium_pump", "type": VariableType.CONSTANT},
    {"name": "i_p_max_Periphery_1DCapable", "units": "nanoA", "component": "sodium_potassium_pump", "type": VariableType.CONSTANT},
    {"name": "i_p_max_Centre_0DCapable", "units": "nanoA", "component": "sodium_potassium_pump", "type": VariableType.CONSTANT},
    {"name": "i_p_max_Periphery_0DCapable", "units": "nanoA", "component": "sodium_potassium_pump", "type": VariableType.CONSTANT},
    {"name": "K_o", "units": "millimolar", "component": "ionic_concentrations", "type": VariableType.CONSTANT},
    {"name": "K_m_K", "units": "millimolar", "component": "sodium_potassium_pump", "type": VariableType.CONSTANT},
    {"name": "K_m_Na", "units": "millimolar", "component": "sodium_potassium_pump", "type": VariableType.CONSTANT},
    {"name": "i_Ca_p_max", "units": "nanoA", "component": "persistent_calcium_current", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "i_Ca_p_max_Centre_Published", "units": "nanoA", "component": "persistent_calcium_current", "type": VariableType.CONSTANT},
    {"name": "i_Ca_p_max_Periphery_Published", "units": "nanoA", "component": "persistent_calcium_current", "type": VariableType.CONSTANT},
    {"name": "i_Ca_p_max_Centre_1DCapable", "units": "nanoA", "component": "persistent_calcium_current", "type": VariableType.CONSTANT},
    {"name": "i_Ca_p_max_Periphery_1DCapable", "units": "nanoA", "component": "persistent_calcium_current", "type": VariableType.CONSTANT},
    {"name": "i_Ca_p_max_Centre_0DCapable", "units": "nanoA", "component": "persistent_calcium_current", "type": VariableType.CONSTANT},
    {"name": "i_Ca_p_max_Periphery_0DCapable", "units": "nanoA", "component": "persistent_calcium_current", "type": VariableType.CONSTANT},
    {"name": "K_i", "units": "millimolar", "component": "ionic_concentrations", "type": VariableType.CONSTANT},
    {"name": "E_K_s", "units": "millivolt", "component": "reversal_and_equilibrium_potentials", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "g_Na", "units": "microlitre_per_second", "component": "sodium_current", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "g_Na_Centre_Published", "units": "microlitre_per_second", "component": "sodium_current", "type": VariableType.CONSTANT},
    {"name": "g_Na_Periphery_Published", "units": "microlitre_per_second", "component": "sodium_current", "type": VariableType.CONSTANT},
    {"name": "g_Na_Centre_1DCapable", "units": "microlitre_per_second", "component": "sodium_current", "type": VariableType.CONSTANT},
    {"name": "g_Na_Periphery_1DCapable", "units": "microlitre_per_second", "component": "sodium_current", "type": VariableType.CONSTANT},
    {"name": "g_Na_Centre_0DCapable", "units": "microlitre_per_second", "component": "sodium_current", "type": VariableType.CONSTANT},
    {"name": "g_Na_Periphery_0DCapable", "units": "microlitre_per_second", "component": "sodium_current", "type": VariableType.CONSTANT},
    {"name": "h", "units": "dimensionless", "component": "sodium_current_h_gate", "type": VariableType.ALGEBRAIC},
    {"name": "m_infinity", "units": "dimensionless", "component": "sodium_current_m_gate", "type": VariableType.ALGEBRAIC},
    {"name": "tau_m", "units": "second", "component": "sodium_current_m_gate", "type": VariableType.ALGEBRAIC},
    {"name": "F_Na", "units": "dimensionless", "component": "sodium_current_h_gate", "type": VariableType.ALGEBRAIC},
    {"name": "h1_infinity", "units": "dimensionless", "component": "sodium_current_h_gate", "type": VariableType.ALGEBRAIC},
    {"name": "tau_h1", "units": "second", "component": "sodium_current_h_gate", "type": VariableType.ALGEBRAIC},
    {"name": "h2_infinity", "units": "dimensionless", "component": "sodium_current_h_gate", "type": VariableType.ALGEBRAIC},
    {"name": "tau_h2", "units": "second", "component": "sodium_current_h_gate", "type": VariableType.ALGEBRAIC},
    {"name": "g_Ca_L", "units": "microS", "component": "L_type_Ca_channel", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "g_Ca_L_Centre_Published", "units": "microS", "component": "L_type_Ca_channel", "type": VariableType.CONSTANT},
    {"name": "g_Ca_L_Periphery_Published", "units": "microS", "component": "L_type_Ca_channel", "type": VariableType.CONSTANT},
    {"name": "g_Ca_L_Centre_1DCapable", "units": "microS", "component": "L_type_Ca_channel", "type": VariableType.CONSTANT},
    {"name": "g_Ca_L_Periphery_1DCapable", "units": "microS", "component": "L_type_Ca_channel", "type": VariableType.CONSTANT},
    {"name": "g_Ca_L_Centre_0DCapable", "units": "microS", "component": "L_type_Ca_channel", "type": VariableType.CONSTANT},
    {"name": "g_Ca_L_Periphery_0DCapable", "units": "microS", "component": "L_type_Ca_channel", "type": VariableType.CONSTANT},
    {"name": "E_Ca_L", "units": "millivolt", "component": "L_type_Ca_channel", "type": VariableType.CONSTANT},
    {"name": "d_L_infinity", "units": "dimensionless", "component": "L_type_Ca_channel_d_gate", "type": VariableType.ALGEBRAIC},
    {"name": "tau_d_L", "units": "second", "component": "L_type_Ca_channel_d_gate", "type": VariableType.ALGEBRAIC},
    {"name": "alpha_d_L", "units": "per_second", "component": "L_type_Ca_channel_d_gate", "type": VariableType.ALGEBRAIC},
    {"name": "beta_d_L", "units": "per_second", "component": "L_type_Ca_channel_d_gate", "type": VariableType.ALGEBRAIC},
    {"name": "f_L_infinity", "units": "dimensionless", "component": "L_type_Ca_channel_f_gate", "type": VariableType.ALGEBRAIC},
    {"name": "tau_f_L", "units": "second", "component": "L_type_Ca_channel_f_gate", "type": VariableType.ALGEBRAIC},
    {"name": "alpha_f_L", "units": "per_second", "component": "L_type_Ca_channel_f_gate", "type": VariableType.ALGEBRAIC},
    {"name": "beta_f_L", "units": "per_second", "component": "L_type_Ca_channel_f_gate", "type": VariableType.ALGEBRAIC},
    {"name": "g_Ca_T", "units": "microS", "component": "T_type_Ca_channel", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "g_Ca_T_Centre_Published", "units": "microS", "component": "T_type_Ca_channel", "type": VariableType.CONSTANT},
    {"name": "g_Ca_T_Periphery_Published", "units": "microS", "component": "T_type_Ca_channel", "type": VariableType.CONSTANT},
    {"name": "g_Ca_T_Centre_1DCapable", "units": "microS", "component": "T_type_Ca_channel", "type": VariableType.CONSTANT},
    {"name": "g_Ca_T_Periphery_1DCapable", "units": "microS", "component": "T_type_Ca_channel", "type": VariableType.CONSTANT},
    {"name": "g_Ca_T_Centre_0DCapable", "units": "microS", "component": "T_type_Ca_channel", "type": VariableType.CONSTANT},
    {"name": "g_Ca_T_Periphery_0DCapable", "units": "microS", "component": "T_type_Ca_channel", "type": VariableType.CONSTANT},
    {"name": "E_Ca_T", "units": "millivolt", "component": "T_type_Ca_channel", "type": VariableType.CONSTANT},
    {"name": "d_T_infinity", "units": "dimensionless", "component": "T_type_Ca_channel_d_gate", "type": VariableType.ALGEBRAIC},
    {"name": "tau_d_T", "units": "second", "component": "T_type_Ca_channel_d_gate", "type": VariableType.ALGEBRAIC},
    {"name": "alpha_d_T", "units": "per_second", "component": "T_type_Ca_channel_d_gate", "type": VariableType.ALGEBRAIC},
    {"name": "beta_d_T", "units": "per_second", "component": "T_type_Ca_channel_d_gate", "type": VariableType.ALGEBRAIC},
    {"name": "f_T_infinity", "units": "dimensionless", "component": "T_type_Ca_channel_f_gate", "type": VariableType.ALGEBRAIC},
    {"name": "tau_f_T", "units": "second", "component": "T_type_Ca_channel_f_gate", "type": VariableType.ALGEBRAIC},
    {"name": "alpha_f_T", "units": "per_second", "component": "T_type_Ca_channel_f_gate", "type": VariableType.ALGEBRAIC},
    {"name": "beta_f_T", "units": "per_second", "component": "T_type_Ca_channel_f_gate", "type": VariableType.ALGEBRAIC},
    {"name": "g_to", "units": "microS", "component": "four_AP_sensitive_currents", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "g_to_Centre_Published", "units": "microS", "component": "four_AP_sensitive_currents", "type": VariableType.CONSTANT},
    {"name": "g_to_Periphery_Published", "units": "microS", "component": "four_AP_sensitive_currents", "type": VariableType.CONSTANT},
    {"name": "g_to_Centre_1DCapable", "units": "microS", "component": "four_AP_sensitive_currents", "type": VariableType.CONSTANT},
    {"name": "g_to_Periphery_1DCapable", "units": "microS", "component": "four_AP_sensitive_currents", "type": VariableType.CONSTANT},
    {"name": "g_to_Centre_0DCapable", "units": "microS", "component": "four_AP_sensitive_currents", "type": VariableType.CONSTANT},
    {"name": "g_to_Periphery_0DCapable", "units": "microS", "component": "four_AP_sensitive_currents", "type": VariableType.CONSTANT},
    {"name": "g_sus", "units": "microS", "component": "four_AP_sensitive_currents", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "g_sus_Centre_Published", "units": "microS", "component": "four_AP_sensitive_currents", "type": VariableType.CONSTANT},
    {"name": "g_sus_Periphery_Published", "units": "microS", "component": "four_AP_sensitive_currents", "type": VariableType.CONSTANT},
    {"name": "g_sus_Centre_1DCapable", "units": "microS", "component": "four_AP_sensitive_currents", "type": VariableType.CONSTANT},
    {"name": "g_sus_Periphery_1DCapable", "units": "microS", "component": "four_AP_sensitive_currents", "type": VariableType.CONSTANT},
    {"name": "g_sus_Centre_0DCapable", "units": "microS", "component": "four_AP_sensitive_currents", "type": VariableType.CONSTANT},
    {"name": "g_sus_Periphery_0DCapable", "units": "microS", "component": "four_AP_sensitive_currents", "type": VariableType.CONSTANT},
    {"name": "q_infinity", "units": "dimensionless", "component": "four_AP_sensitive_currents_q_gate", "type": VariableType.ALGEBRAIC},
    {"name": "tau_q", "units": "second", "component": "four_AP_sensitive_currents_q_gate", "type": VariableType.ALGEBRAIC},
    {"name": "r_infinity", "units": "dimensionless", "component": "four_AP_sensitive_currents_r_gate", "type": VariableType.ALGEBRAIC},
    {"name": "tau_r", "units": "second", "component": "four_AP_sensitive_currents_r_gate", "type": VariableType.ALGEBRAIC},
    {"name": "g_K_r", "units": "microS", "component": "rapid_delayed_rectifying_potassium_current", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "g_K_r_Centre_Published", "units": "microS", "component": "rapid_delayed_rectifying_potassium_current", "type": VariableType.CONSTANT},
    {"name": "g_K_r_Periphery_Published", "units": "microS", "component": "rapid_delayed_rectifying_potassium_current", "type": VariableType.CONSTANT},
    {"name": "g_K_r_Centre_1DCapable", "units": "microS", "component": "rapid_delayed_rectifying_potassium_current", "type": VariableType.CONSTANT},
    {"name": "g_K_r_Periphery_1DCapable", "units": "microS", "component": "rapid_delayed_rectifying_potassium_current", "type": VariableType.CONSTANT},
    {"name": "g_K_r_Centre_0DCapable", "units": "microS", "component": "rapid_delayed_rectifying_potassium_current", "type": VariableType.CONSTANT},
    {"name": "g_K_r_Periphery_0DCapable", "units": "microS", "component": "rapid_delayed_rectifying_potassium_current", "type": VariableType.CONSTANT},
    {"name": "P_a", "units": "dimensionless", "component": "rapid_delayed_rectifying_potassium_current", "type": VariableType.ALGEBRAIC},
    {"name": "P_af_infinity", "units": "dimensionless", "component": "rapid_delayed_rectifying_potassium_current_P_af_gate", "type": VariableType.ALGEBRAIC},
    {"name": "tau_P_af", "units": "second", "component": "rapid_delayed_rectifying_potassium_current_P_af_gate", "type": VariableType.ALGEBRAIC},
    {"name": "P_as_infinity", "units": "dimensionless", "component": "rapid_delayed_rectifying_potassium_current_P_as_gate", "type": VariableType.ALGEBRAIC},
    {"name": "tau_P_as", "units": "second", "component": "rapid_delayed_rectifying_potassium_current_P_as_gate", "type": VariableType.ALGEBRAIC},
    {"name": "tau_P_i", "units": "second", "component": "rapid_delayed_rectifying_potassium_current_P_i_gate", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "P_i_infinity", "units": "dimensionless", "component": "rapid_delayed_rectifying_potassium_current_P_i_gate", "type": VariableType.ALGEBRAIC},
    {"name": "g_K_s", "units": "microS", "component": "slow_delayed_rectifying_potassium_current", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "g_K_s_Centre_Published", "units": "microS", "component": "slow_delayed_rectifying_potassium_current", "type": VariableType.CONSTANT},
    {"name": "g_K_s_Periphery_Published", "units": "microS", "component": "slow_delayed_rectifying_potassium_current", "type": VariableType.CONSTANT},
    {"name": "g_K_s_Centre_1DCapable", "units": "microS", "component": "slow_delayed_rectifying_potassium_current", "type": VariableType.CONSTANT},
    {"name": "g_K_s_Periphery_1DCapable", "units": "microS", "component": "slow_delayed_rectifying_potassium_current", "type": VariableType.CONSTANT},
    {"name": "g_K_s_Centre_0DCapable", "units": "microS", "component": "slow_delayed_rectifying_potassium_current", "type": VariableType.CONSTANT},
    {"name": "g_K_s_Periphery_0DCapable", "units": "microS", "component": "slow_delayed_rectifying_potassium_current", "type": VariableType.CONSTANT},
    {"name": "alpha_xs", "units": "per_second", "component": "slow_delayed_rectifying_potassium_current_xs_gate", "type": VariableType.ALGEBRAIC},
    {"name": "beta_xs", "units": "per_second", "component": "slow_delayed_rectifying_potassium_current_xs_gate", "type": VariableType.ALGEBRAIC},
    {"name": "g_f_Na", "units": "microS", "component": "hyperpolarisation_activated_current", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "g_f_Na_Centre_Published", "units": "microS", "component": "hyperpolarisation_activated_current", "type": VariableType.CONSTANT},
    {"name": "g_f_Na_Periphery_Published", "units": "microS", "component": "hyperpolarisation_activated_current", "type": VariableType.CONSTANT},
    {"name": "g_f_Na_Centre_1DCapable", "units": "microS", "component": "hyperpolarisation_activated_current", "type": VariableType.CONSTANT},
    {"name": "g_f_Na_Periphery_1DCapable", "units": "microS", "component": "hyperpolarisation_activated_current", "type": VariableType.CONSTANT},
    {"name": "g_f_Na_Centre_0DCapable", "units": "microS", "component": "hyperpolarisation_activated_current", "type": VariableType.CONSTANT},
    {"name": "g_f_Na_Periphery_0DCapable", "units": "microS", "component": "hyperpolarisation_activated_current", "type": VariableType.CONSTANT},
    {"name": "g_f_K", "units": "microS", "component": "hyperpolarisation_activated_current", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "g_f_K_Centre_Published", "units": "microS", "component": "hyperpolarisation_activated_current", "type": VariableType.CONSTANT},
    {"name": "g_f_K_Periphery_Published", "units": "microS", "component": "hyperpolarisation_activated_current", "type": VariableType.CONSTANT},
    {"name": "g_f_K_Centre_1DCapable", "units": "microS", "component": "hyperpolarisation_activated_current", "type": VariableType.CONSTANT},
    {"name": "g_f_K_Periphery_1DCapable", "units": "microS", "component": "hyperpolarisation_activated_current", "type": VariableType.CONSTANT},
    {"name": "g_f_K_Centre_0DCapable", "units": "microS", "component": "hyperpolarisation_activated_current", "type": VariableType.CONSTANT},
    {"name": "g_f_K_Periphery_0DCapable", "units": "microS", "component": "hyperpolarisation_activated_current", "type": VariableType.CONSTANT},
    {"name": "alpha_y", "units": "per_second", "component": "hyperpolarisation_activated_current_y_gate", "type": VariableType.ALGEBRAIC},
    {"name": "beta_y", "units": "per_second", "component": "hyperpolarisation_activated_current_y_gate", "type": VariableType.ALGEBRAIC}
]


def eq_func(x, y):
    return 1.0 if x == y else 0.0


def neq_func(x, y):
    return 1.0 if x != y else 0.0


def create_states_array():
    return [nan]*STATE_COUNT


def create_variables_array():
    return [nan]*VARIABLE_COUNT


def initialise_variables(states, rates, constants):
    constants[1] = 0.0
    constants[2] = 1.0
    constants[3] = 1.0309347
    constants[5] = 2.0e-5
    constants[6] = 6.5e-5
    constants[22] = 8314.0
    constants[23] = 310.0
    constants[24] = 96845.0
    constants[26] = 5.8e-5
    constants[27] = 0.000189
    constants[28] = 5.8e-5
    constants[29] = 0.000189
    constants[30] = 5.81818e-5
    constants[31] = 0.0001888
    constants[34] = 2.52e-5
    constants[35] = 8.19e-5
    constants[36] = 2.52e-5
    constants[37] = 8.19e-5
    constants[38] = 2.523636e-5
    constants[39] = 8.1892e-5
    constants[42] = 1.32e-5
    constants[43] = 4.3e-5
    constants[44] = 1.323e-5
    constants[45] = 4.29e-5
    constants[46] = 1.3236e-5
    constants[47] = 4.2952e-5
    constants[50] = 2.7e-6
    constants[51] = 8.8e-6
    constants[52] = 2.8e-6
    constants[53] = 8.8e-6
    constants[54] = 2.7229e-6
    constants[55] = 8.83584e-6
    constants[56] = 8.0
    constants[57] = 0.5
    constants[58] = 2.0
    constants[59] = 140.0
    constants[60] = 0.0001
    constants[61] = 0.0001
    constants[63] = 0.0478
    constants[64] = 0.16
    constants[65] = 0.0478
    constants[66] = 0.16
    constants[67] = 0.04782545
    constants[68] = 0.1551936
    constants[69] = 5.4
    constants[70] = 0.621
    constants[71] = 5.64
    constants[73] = 0.0
    constants[74] = 0.0
    constants[75] = 0.0042
    constants[76] = 0.03339
    constants[77] = 0.0
    constants[78] = 0.0
    constants[79] = 140.0
    constants[82] = 0.0
    constants[83] = 1.2e-6
    constants[84] = 0.0
    constants[85] = 3.7e-7
    constants[86] = 0.0
    constants[87] = 1.204e-6
    constants[97] = 0.0058
    constants[98] = 0.0659
    constants[99] = 0.0082
    constants[100] = 0.0659
    constants[101] = 0.0057938
    constants[102] = 0.06588648
    constants[103] = 46.4
    constants[113] = 0.0043
    constants[114] = 0.0139
    constants[115] = 0.0021
    constants[116] = 0.00694
    constants[117] = 0.00427806
    constants[118] = 0.0138823
    constants[119] = 45.0
    constants[129] = 0.00491
    constants[130] = 0.03649
    constants[131] = 0.004905
    constants[132] = 0.0365
    constants[133] = 0.004905
    constants[134] = 0.036495
    constants[136] = 6.65e-5
    constants[137] = 0.0114
    constants[138] = 0.000266
    constants[139] = 0.0114
    constants[140] = 6.645504e-5
    constants[141] = 0.01138376
    constants[147] = 0.000797
    constants[148] = 0.016
    constants[149] = 0.000738
    constants[150] = 0.0208
    constants[151] = 0.00079704
    constants[152] = 0.016
    constants[161] = 0.000518
    constants[162] = 0.0104
    constants[163] = 0.000345
    constants[164] = 0.0104
    constants[165] = 0.0003445
    constants[166] = 0.0104
    constants[170] = 0.000548
    constants[171] = 0.0069
    constants[172] = 0.000437
    constants[173] = 0.0055
    constants[174] = 0.0005465
    constants[175] = 0.006875
    constants[177] = 0.000548
    constants[178] = 0.0069
    constants[179] = 0.000437
    constants[180] = 0.0055
    constants[181] = 0.0005465
    constants[182] = 0.006875
    states[0] = -39.013558536
    states[1] = 0.092361701692
    states[2] = 0.015905380261
    states[3] = 0.01445216109
    states[4] = 0.48779845203
    states[5] = 0.04804900895
    states[6] = 0.038968420558
    states[7] = 0.42074047435
    states[8] = 0.064402950262
    states[9] = 0.29760539675
    states[10] = 0.87993375273
    states[11] = 0.13034201158
    states[12] = 0.46960956028
    states[13] = 0.082293827208
    states[14] = 0.03889291759


def compute_computed_constants(constants, computed_constants):
    computed_constants[0] = 1.07*(3.0*constants[1]-0.1)/(3.0*(1.0+0.7745*exp(-(3.0*constants[1]-2.05)/0.295))) if eq_func(constants[2], 0.0) else constants[3]*constants[1]/(1.0+0.7745*exp(-(3.0*constants[1]-2.05)/0.295)) if eq_func(constants[2], 1.0) else 1.07*29.0*constants[1]/(30.0*(1.0+0.7745*exp(-(29.0*constants[1]-24.5)/1.95)))
    computed_constants[4] = constants[5]+computed_constants[0]*(constants[6]-constants[5])
    computed_constants[25] = constants[26]+computed_constants[0]*(constants[27]-constants[26]) if eq_func(constants[2], 0.0) else constants[30]+computed_constants[0]*(constants[31]-constants[30]) if eq_func(constants[2], 1.0) else constants[28]+computed_constants[0]*(constants[29]-constants[28])
    computed_constants[33] = constants[34]+computed_constants[0]*(constants[35]-constants[34]) if eq_func(constants[2], 0.0) else constants[38]+computed_constants[0]*(constants[39]-constants[38]) if eq_func(constants[2], 1.0) else constants[36]+computed_constants[0]*(constants[37]-constants[36])
    computed_constants[41] = constants[42]+computed_constants[0]*(constants[43]-constants[42]) if eq_func(constants[2], 0.0) else constants[46]+computed_constants[0]*(constants[47]-constants[46]) if eq_func(constants[2], 1.0) else constants[44]+computed_constants[0]*(constants[45]-constants[44])
    computed_constants[49] = constants[50]+computed_constants[0]*(constants[51]-constants[50]) if eq_func(constants[2], 0.0) else constants[54]+computed_constants[0]*(constants[55]-constants[54]) if eq_func(constants[2], 1.0) else constants[52]+computed_constants[0]*(constants[53]-constants[52])
    computed_constants[62] = constants[63]+computed_constants[0]*(constants[64]-constants[63]) if eq_func(constants[2], 0.0) else constants[67]+computed_constants[0]*(constants[68]-constants[67]) if eq_func(constants[2], 1.0) else constants[65]+computed_constants[0]*(constants[66]-constants[65])
    computed_constants[72] = constants[73]+computed_constants[0]*(constants[74]-constants[73]) if eq_func(constants[2], 0.0) else constants[77]+computed_constants[0]*(constants[78]-constants[77]) if eq_func(constants[2], 1.0) else constants[75]+computed_constants[0]*(constants[76]-constants[75])
    computed_constants[8] = computed_constants[72]*constants[60]/(constants[60]+0.0004)
    computed_constants[32] = constants[22]*constants[23]/constants[24]*log(constants[59]/constants[56])
    computed_constants[40] = constants[22]*constants[23]/constants[24]*log(constants[69]/constants[79])
    computed_constants[48] = constants[22]*constants[23]/(2.0*constants[24])*log(constants[58]/constants[60])
    computed_constants[80] = constants[22]*constants[23]/constants[24]*log((constants[69]+0.12*constants[59])/(constants[79]+0.12*constants[56])) if eq_func(constants[2], 0.0) else constants[22]*constants[23]/constants[24]*log((constants[69]+0.03*constants[59])/(constants[79]+0.03*constants[56]))
    computed_constants[81] = constants[82]+computed_constants[0]*(constants[83]-constants[82]) if eq_func(constants[2], 0.0) else constants[86]+computed_constants[0]*(constants[87]-constants[86]) if eq_func(constants[2], 1.0) else constants[84]+computed_constants[0]*(constants[85]-constants[84])
    computed_constants[96] = constants[97]+computed_constants[0]*(constants[98]-constants[97]) if eq_func(constants[2], 0.0) else constants[101]+computed_constants[0]*(constants[102]-constants[101]) if eq_func(constants[2], 1.0) else constants[99]+computed_constants[0]*(constants[100]-constants[99])
    computed_constants[112] = constants[113]+computed_constants[0]*(constants[114]-constants[113]) if eq_func(constants[2], 0.0) else constants[117]+computed_constants[0]*(constants[118]-constants[117]) if eq_func(constants[2], 1.0) else constants[115]+computed_constants[0]*(constants[116]-constants[115])
    computed_constants[128] = constants[129]+computed_constants[0]*(constants[130]-constants[129]) if eq_func(constants[2], 0.0) else constants[133]+computed_constants[0]*(constants[134]-constants[133]) if eq_func(constants[2], 1.0) else constants[131]+computed_constants[0]*(constants[132]-constants[131])
    computed_constants[135] = constants[136]+computed_constants[0]*(constants[137]-constants[136]) if eq_func(constants[2], 0.0) else constants[140]+computed_constants[0]*(constants[141]-constants[140]) if eq_func(constants[2], 1.0) else constants[138]+computed_constants[0]*(constants[139]-constants[138])
    computed_constants[146] = constants[147]+computed_constants[0]*(constants[148]-constants[147]) if eq_func(constants[2], 0.0) else constants[151]+computed_constants[0]*(constants[152]-constants[151]) if eq_func(constants[2], 1.0) else constants[149]+computed_constants[0]*(constants[150]-constants[149])
    computed_constants[158] = 0.002 if eq_func(constants[2], 0.0) else 0.002 if eq_func(constants[2], 1.0) else 0.006
    computed_constants[160] = constants[161]+computed_constants[0]*(constants[162]-constants[161]) if eq_func(constants[2], 0.0) else constants[165]+computed_constants[0]*(constants[166]-constants[165]) if eq_func(constants[2], 1.0) else constants[163]+computed_constants[0]*(constants[164]-constants[163])
    computed_constants[169] = constants[170]+computed_constants[0]*(constants[171]-constants[170]) if eq_func(constants[2], 0.0) else constants[174]+computed_constants[0]*(constants[175]-constants[174]) if eq_func(constants[2], 1.0) else constants[172]+computed_constants[0]*(constants[173]-constants[172])
    computed_constants[176] = constants[177]+computed_constants[0]*(constants[178]-constants[177]) if eq_func(constants[2], 0.0) else constants[181]+computed_constants[0]*(constants[182]-constants[181]) if eq_func(constants[2], 1.0) else constants[179]+computed_constants[0]*(constants[180]-constants[179])


def compute_rates(voi, states, rates, constants, computed_constants, algebraic):
    algebraic[9] = computed_constants[62]*pow(constants[56]/(constants[71]+constants[56]), 3.0)*pow(constants[69]/(constants[70]+constants[69]), 2.0)*1.6/(1.5+exp(-(states[0]+60.0)/40.0))
    algebraic[10] = computed_constants[49]*(pow(constants[56], 3.0)*constants[58]*exp(0.03743*states[0]*constants[57])-pow(constants[59], 3.0)*constants[60]*exp(0.0374*states[0]*(constants[57]-1.0)))/(1.0+constants[61]*(constants[60]*pow(constants[59], 3.0)+constants[58]*pow(constants[56], 3.0))) if eq_func(constants[2], 0.0) else computed_constants[49]*(pow(constants[56], 3.0)*constants[58]*exp(0.03743*states[0]*constants[57])-pow(constants[59], 3.0)*constants[60]*exp(0.03743*states[0]*(constants[57]-1.0)))/(1.0+constants[61]*(constants[60]*pow(constants[59], 3.0)+constants[58]*pow(constants[56], 3.0)))
    algebraic[14] = computed_constants[176]*states[14]*(states[0]-computed_constants[40]) if neq_func(constants[2], 2.0) else computed_constants[176]*states[14]*(states[0]+102.0)
    algebraic[15] = computed_constants[169]*states[14]*(states[0]-computed_constants[32]) if neq_func(constants[2], 2.0) else computed_constants[169]*states[14]*(states[0]-77.6)
    algebraic[16] = computed_constants[160]*pow(states[13], 2.0)*(states[0]-computed_constants[80])
    algebraic[18] = computed_constants[135]*states[8]*(states[0]-computed_constants[40])
    algebraic[19] = computed_constants[128]*states[9]*states[8]*(states[0]-computed_constants[40])
    algebraic[20] = computed_constants[112]*states[7]*states[6]*(states[0]-constants[119])
    algebraic[21] = computed_constants[96]*(states[4]*states[5]+0.006/(1.0+exp(-(states[0]+14.1)/6.0)))*(states[0]-constants[103])
    algebraic[91] = 0.0952*exp(-0.063*(states[0]+34.4))/(1.0+1.66*exp(-0.225*(states[0]+63.7)))+0.0869 if eq_func(constants[2], 0.0) else 0.09518*exp(-0.06306*(states[0]+34.4))/(1.0+1.662*exp(-0.2251*(states[0]+63.7)))+0.08693
    algebraic[88] = (1.0-algebraic[91])*states[2]+algebraic[91]*states[3]
    algebraic[7] = computed_constants[81]*pow(states[1], 3.0)*algebraic[88]*constants[59]*pow(constants[24], 2.0)/(constants[22]*constants[23])*(exp((states[0]-computed_constants[32])*constants[24]/(constants[22]*constants[23]))-1.0)/(exp(states[0]*constants[24]/(constants[22]*constants[23]))-1.0)*states[0]
    algebraic[11] = computed_constants[33]*(states[0]-computed_constants[40])
    algebraic[12] = computed_constants[41]*(states[0]-computed_constants[48])
    algebraic[13] = computed_constants[25]*(states[0]-computed_constants[32])
    algebraic[153] = 0.6*states[11]+0.4*states[12]
    algebraic[17] = computed_constants[146]*algebraic[153]*states[10]*(states[0]-computed_constants[40])
    rates[0] = -1.0/computed_constants[4]*(algebraic[7]+algebraic[21]+algebraic[20]+algebraic[19]+algebraic[18]+algebraic[17]+algebraic[16]+algebraic[15]+algebraic[14]+algebraic[13]+algebraic[12]+algebraic[11]+algebraic[10]+algebraic[9]+computed_constants[8])
    algebraic[89] = pow(1.0/(1.0+exp(-states[0]/5.46)), 1.0/3.0) if eq_func(constants[2], 0.0) else pow(1.0/(1.0+exp(-(states[0]+30.32)/5.46)), 1.0/3.0)
    algebraic[90] = 0.0006247/(0.832*exp(-0.335*(states[0]+56.7))+0.627*exp(0.082*(states[0]+65.01)))+4.0e-5 if eq_func(constants[2], 0.0) else 0.0006247/(0.8322166*exp(-0.33566*(states[0]+56.7062))+0.6274*exp(0.0823*(states[0]+65.0131)))+4.569e-5
    rates[1] = (algebraic[89]-states[1])/algebraic[90]
    algebraic[92] = 1.0/(1.0+exp((states[0]+66.1)/6.4))
    algebraic[93] = 3.717e-6*exp(-0.2815*(states[0]+17.11))/(1.0+0.003732*exp(-0.3426*(states[0]+37.76)))+0.0005977
    rates[2] = (algebraic[92]-states[2])/algebraic[93]
    algebraic[94] = algebraic[92]
    algebraic[95] = 3.186e-8*exp(-0.6219*(states[0]+18.8))/(1.0+7.189e-5*exp(-0.6683*(states[0]+34.07)))+0.003556
    rates[3] = (algebraic[94]-states[3])/algebraic[95]
    algebraic[104] = 1.0/(1.0+exp(-(states[0]+23.1)/6.0)) if eq_func(constants[2], 0.0) else 1.0/(1.0+exp(-(states[0]+22.3+0.8*computed_constants[0])/6.0)) if eq_func(constants[2], 1.0) else 1.0/(1.0+exp(-(states[0]+22.2)/6.0))
    algebraic[106] = -28.38*(states[0]+35.0)/(exp(-(states[0]+35.0)/2.5)-1.0)-84.9*states[0]/(exp(-0.208*states[0])-1.0) if eq_func(constants[2], 0.0) else -28.39*(states[0]+35.0)/(exp(-(states[0]+35.0)/2.5)-1.0)-84.9*states[0]/(exp(-0.208*states[0])-1.0) if eq_func(constants[2], 1.0) else -28.4*(states[0]+35.0)/(exp(-(states[0]+35.0)/2.5)-1.0)-84.9*states[0]/(exp(-0.208*states[0])-1.0)
    algebraic[107] = 11.43*(states[0]-5.0)/(exp(0.4*(states[0]-5.0))-1.0) if eq_func(constants[2], 1.0) else 11.42*(states[0]-5.0)/(exp(0.4*(states[0]-5.0))-1.0)
    algebraic[105] = 2.0/(algebraic[106]+algebraic[107])
    rates[5] = (algebraic[104]-states[5])/algebraic[105]
    algebraic[108] = 1.0/(1.0+exp((states[0]+45.0)/5.0))
    algebraic[110] = 3.75*(states[0]+28.0)/(exp((states[0]+28.0)/4.0)-1.0) if eq_func(constants[2], 1.0) else 3.12*(states[0]+28.0)/(exp((states[0]+28.0)/4.0)-1.0)
    algebraic[111] = 30.0/(1.0+exp(-(states[0]+28.0)/4.0)) if eq_func(constants[2], 1.0) else 25.0/(1.0+exp(-(states[0]+28.0)/4.0))
    algebraic[109] = (1.2-0.2*computed_constants[0])/(algebraic[110]+algebraic[111]) if eq_func(constants[2], 1.0) else 1.0/(algebraic[110]+algebraic[111])
    rates[4] = (algebraic[108]-states[4])/algebraic[109]
    algebraic[120] = 1.0/(1.0+exp(-(states[0]+37.0)/6.8))
    algebraic[122] = 1068.0*exp((states[0]+26.3)/30.0)
    algebraic[123] = 1068.0*exp(-(states[0]+26.3)/30.0)
    algebraic[121] = 1.0/(algebraic[122]+algebraic[123])
    rates[7] = (algebraic[120]-states[7])/algebraic[121]
    algebraic[124] = 1.0/(1.0+exp((states[0]+71.0)/9.0))
    algebraic[126] = 15.3*exp(-(states[0]+71.0+0.7*computed_constants[0])/83.3) if eq_func(constants[2], 1.0) else 15.3*exp(-(states[0]+71.7)/83.3)
    algebraic[127] = 15.0*exp((states[0]+71.0)/15.38) if eq_func(constants[2], 1.0) else 15.0*exp((states[0]+71.7)/15.38)
    algebraic[125] = 1.0/(algebraic[126]+algebraic[127])
    rates[6] = (algebraic[124]-states[6])/algebraic[125]
    algebraic[142] = 1.0/(1.0+exp((states[0]+59.37)/13.1))
    algebraic[143] = 0.0101+0.06517/(0.57*exp(-0.08*(states[0]+49.0)))+2.4e-5*exp(0.1*(states[0]+50.93)) if eq_func(constants[2], 0.0) else 0.001/3.0*(30.31+195.5/(0.5686*exp(-0.08161*(states[0]+39.0+10.0*computed_constants[0]))+0.7174*exp((0.2719-0.1719*computed_constants[0])*1.0*(states[0]+40.93+10.0*computed_constants[0])))) if eq_func(constants[2], 1.0) else 0.0101+0.06517/(0.5686*exp(-0.08161*(states[0]+39.0))+0.7174*exp(0.2719*(states[0]+40.93)))
    rates[9] = (algebraic[142]-states[9])/algebraic[143]
    algebraic[144] = 1.0/(1.0+exp(-(states[0]-10.93)/19.7))
    algebraic[145] = 0.001*(2.98+15.59/(1.037*exp(0.09*(states[0]+30.61))+0.369*exp(-0.12*(states[0]+23.84)))) if eq_func(constants[2], 0.0) else 0.0025*(1.191+7.838/(1.037*exp(0.09012*(states[0]+30.61))+0.369*exp(-0.119*(states[0]+23.84)))) if eq_func(constants[2], 1.0) else 0.001*(2.98+19.59/(1.037*exp(0.09012*(states[0]+30.61))+0.369*exp(-0.119*(states[0]+23.84))))
    rates[8] = (algebraic[144]-states[8])/algebraic[145]
    algebraic[154] = 1.0/(1.0+exp(-(states[0]+14.2)/10.6)) if neq_func(constants[2], 2.0) else 1.0/(1.0+exp(-(states[0]+13.2)/10.6))
    algebraic[155] = 1.0/(37.2*exp((states[0]-9.0)/15.9)+0.96*exp(-(states[0]-9.0)/22.5)) if neq_func(constants[2], 2.0) else 1.0/(37.2*exp((states[0]-10.0)/15.9)+0.96*exp(-(states[0]-10.0)/22.5))
    rates[11] = (algebraic[154]-states[11])/algebraic[155]
    algebraic[156] = algebraic[154]
    algebraic[157] = 1.0/(4.2*exp((states[0]-9.0)/17.0)+0.15*exp(-(states[0]-9.0)/21.6)) if neq_func(constants[2], 2.0) else 1.0/(4.2*exp((states[0]-10.0)/17.0)+0.15*exp(-(states[0]-10.0)/21.6))
    rates[12] = (algebraic[156]-states[12])/algebraic[157]
    algebraic[159] = 1.0/(1.0+exp((states[0]+18.6)/10.1))
    rates[10] = (algebraic[159]-states[10])/computed_constants[158]
    algebraic[167] = 14.0/(1.0+exp(-(states[0]-40.0)/9.0))
    algebraic[168] = 1.0*exp(-states[0]/45.0)
    rates[13] = algebraic[167]*(1.0-states[13])-algebraic[168]*states[13]
    algebraic[183] = 1.0*exp(-(states[0]+78.91)/26.62) if eq_func(constants[2], 0.0) else 1.0*exp(-(states[0]+78.91)/26.63)
    algebraic[184] = 1.0*exp((states[0]+75.13)/21.25)
    rates[14] = algebraic[183]*(1.0-states[14])-algebraic[184]*states[14]


def compute_variables(voi, states, rates, constants, computed_constants, algebraic):
    algebraic[13] = computed_constants[25]*(states[0]-computed_constants[32])
    algebraic[11] = computed_constants[33]*(states[0]-computed_constants[40])
    algebraic[12] = computed_constants[41]*(states[0]-computed_constants[48])
    algebraic[10] = computed_constants[49]*(pow(constants[56], 3.0)*constants[58]*exp(0.03743*states[0]*constants[57])-pow(constants[59], 3.0)*constants[60]*exp(0.0374*states[0]*(constants[57]-1.0)))/(1.0+constants[61]*(constants[60]*pow(constants[59], 3.0)+constants[58]*pow(constants[56], 3.0))) if eq_func(constants[2], 0.0) else computed_constants[49]*(pow(constants[56], 3.0)*constants[58]*exp(0.03743*states[0]*constants[57])-pow(constants[59], 3.0)*constants[60]*exp(0.03743*states[0]*(constants[57]-1.0)))/(1.0+constants[61]*(constants[60]*pow(constants[59], 3.0)+constants[58]*pow(constants[56], 3.0)))
    algebraic[9] = computed_constants[62]*pow(constants[56]/(constants[71]+constants[56]), 3.0)*pow(constants[69]/(constants[70]+constants[69]), 2.0)*1.6/(1.5+exp(-(states[0]+60.0)/40.0))
    algebraic[91] = 0.0952*exp(-0.063*(states[0]+34.4))/(1.0+1.66*exp(-0.225*(states[0]+63.7)))+0.0869 if eq_func(constants[2], 0.0) else 0.09518*exp(-0.06306*(states[0]+34.4))/(1.0+1.662*exp(-0.2251*(states[0]+63.7)))+0.08693
    algebraic[88] = (1.0-algebraic[91])*states[2]+algebraic[91]*states[3]
    algebraic[7] = computed_constants[81]*pow(states[1], 3.0)*algebraic[88]*constants[59]*pow(constants[24], 2.0)/(constants[22]*constants[23])*(exp((states[0]-computed_constants[32])*constants[24]/(constants[22]*constants[23]))-1.0)/(exp(states[0]*constants[24]/(constants[22]*constants[23]))-1.0)*states[0]
    algebraic[89] = pow(1.0/(1.0+exp(-states[0]/5.46)), 1.0/3.0) if eq_func(constants[2], 0.0) else pow(1.0/(1.0+exp(-(states[0]+30.32)/5.46)), 1.0/3.0)
    algebraic[90] = 0.0006247/(0.832*exp(-0.335*(states[0]+56.7))+0.627*exp(0.082*(states[0]+65.01)))+4.0e-5 if eq_func(constants[2], 0.0) else 0.0006247/(0.8322166*exp(-0.33566*(states[0]+56.7062))+0.6274*exp(0.0823*(states[0]+65.0131)))+4.569e-5
    algebraic[92] = 1.0/(1.0+exp((states[0]+66.1)/6.4))
    algebraic[94] = algebraic[92]
    algebraic[93] = 3.717e-6*exp(-0.2815*(states[0]+17.11))/(1.0+0.003732*exp(-0.3426*(states[0]+37.76)))+0.0005977
    algebraic[95] = 3.186e-8*exp(-0.6219*(states[0]+18.8))/(1.0+7.189e-5*exp(-0.6683*(states[0]+34.07)))+0.003556
    algebraic[21] = computed_constants[96]*(states[4]*states[5]+0.006/(1.0+exp(-(states[0]+14.1)/6.0)))*(states[0]-constants[103])
    algebraic[106] = -28.38*(states[0]+35.0)/(exp(-(states[0]+35.0)/2.5)-1.0)-84.9*states[0]/(exp(-0.208*states[0])-1.0) if eq_func(constants[2], 0.0) else -28.39*(states[0]+35.0)/(exp(-(states[0]+35.0)/2.5)-1.0)-84.9*states[0]/(exp(-0.208*states[0])-1.0) if eq_func(constants[2], 1.0) else -28.4*(states[0]+35.0)/(exp(-(states[0]+35.0)/2.5)-1.0)-84.9*states[0]/(exp(-0.208*states[0])-1.0)
    algebraic[107] = 11.43*(states[0]-5.0)/(exp(0.4*(states[0]-5.0))-1.0) if eq_func(constants[2], 1.0) else 11.42*(states[0]-5.0)/(exp(0.4*(states[0]-5.0))-1.0)
    algebraic[105] = 2.0/(algebraic[106]+algebraic[107])
    algebraic[104] = 1.0/(1.0+exp(-(states[0]+23.1)/6.0)) if eq_func(constants[2], 0.0) else 1.0/(1.0+exp(-(states[0]+22.3+0.8*computed_constants[0])/6.0)) if eq_func(constants[2], 1.0) else 1.0/(1.0+exp(-(states[0]+22.2)/6.0))
    algebraic[110] = 3.75*(states[0]+28.0)/(exp((states[0]+28.0)/4.0)-1.0) if eq_func(constants[2], 1.0) else 3.12*(states[0]+28.0)/(exp((states[0]+28.0)/4.0)-1.0)
    algebraic[111] = 30.0/(1.0+exp(-(states[0]+28.0)/4.0)) if eq_func(constants[2], 1.0) else 25.0/(1.0+exp(-(states[0]+28.0)/4.0))
    algebraic[109] = (1.2-0.2*computed_constants[0])/(algebraic[110]+algebraic[111]) if eq_func(constants[2], 1.0) else 1.0/(algebraic[110]+algebraic[111])
    algebraic[108] = 1.0/(1.0+exp((states[0]+45.0)/5.0))
    algebraic[20] = computed_constants[112]*states[7]*states[6]*(states[0]-constants[119])
    algebraic[122] = 1068.0*exp((states[0]+26.3)/30.0)
    algebraic[123] = 1068.0*exp(-(states[0]+26.3)/30.0)
    algebraic[121] = 1.0/(algebraic[122]+algebraic[123])
    algebraic[120] = 1.0/(1.0+exp(-(states[0]+37.0)/6.8))
    algebraic[126] = 15.3*exp(-(states[0]+71.0+0.7*computed_constants[0])/83.3) if eq_func(constants[2], 1.0) else 15.3*exp(-(states[0]+71.7)/83.3)
    algebraic[127] = 15.0*exp((states[0]+71.0)/15.38) if eq_func(constants[2], 1.0) else 15.0*exp((states[0]+71.7)/15.38)
    algebraic[125] = 1.0/(algebraic[126]+algebraic[127])
    algebraic[124] = 1.0/(1.0+exp((states[0]+71.0)/9.0))
    algebraic[19] = computed_constants[128]*states[9]*states[8]*(states[0]-computed_constants[40])
    algebraic[18] = computed_constants[135]*states[8]*(states[0]-computed_constants[40])
    algebraic[142] = 1.0/(1.0+exp((states[0]+59.37)/13.1))
    algebraic[143] = 0.0101+0.06517/(0.57*exp(-0.08*(states[0]+49.0)))+2.4e-5*exp(0.1*(states[0]+50.93)) if eq_func(constants[2], 0.0) else 0.001/3.0*(30.31+195.5/(0.5686*exp(-0.08161*(states[0]+39.0+10.0*computed_constants[0]))+0.7174*exp((0.2719-0.1719*computed_constants[0])*1.0*(states[0]+40.93+10.0*computed_constants[0])))) if eq_func(constants[2], 1.0) else 0.0101+0.06517/(0.5686*exp(-0.08161*(states[0]+39.0))+0.7174*exp(0.2719*(states[0]+40.93)))
    algebraic[144] = 1.0/(1.0+exp(-(states[0]-10.93)/19.7))
    algebraic[145] = 0.001*(2.98+15.59/(1.037*exp(0.09*(states[0]+30.61))+0.369*exp(-0.12*(states[0]+23.84)))) if eq_func(constants[2], 0.0) else 0.0025*(1.191+7.838/(1.037*exp(0.09012*(states[0]+30.61))+0.369*exp(-0.119*(states[0]+23.84)))) if eq_func(constants[2], 1.0) else 0.001*(2.98+19.59/(1.037*exp(0.09012*(states[0]+30.61))+0.369*exp(-0.119*(states[0]+23.84))))
    algebraic[153] = 0.6*states[11]+0.4*states[12]
    algebraic[17] = computed_constants[146]*algebraic[153]*states[10]*(states[0]-computed_constants[40])
    algebraic[154] = 1.0/(1.0+exp(-(states[0]+14.2)/10.6)) if neq_func(constants[2], 2.0) else 1.0/(1.0+exp(-(states[0]+13.2)/10.6))
    algebraic[155] = 1.0/(37.2*exp((states[0]-9.0)/15.9)+0.96*exp(-(states[0]-9.0)/22.5)) if neq_func(constants[2], 2.0) else 1.0/(37.2*exp((states[0]-10.0)/15.9)+0.96*exp(-(states[0]-10.0)/22.5))
    algebraic[156] = algebraic[154]
    algebraic[157] = 1.0/(4.2*exp((states[0]-9.0)/17.0)+0.15*exp(-(states[0]-9.0)/21.6)) if neq_func(constants[2], 2.0) else 1.0/(4.2*exp((states[0]-10.0)/17.0)+0.15*exp(-(states[0]-10.0)/21.6))
    algebraic[159] = 1.0/(1.0+exp((states[0]+18.6)/10.1))
    algebraic[16] = computed_constants[160]*pow(states[13], 2.0)*(states[0]-computed_constants[80])
    algebraic[167] = 14.0/(1.0+exp(-(states[0]-40.0)/9.0))
    algebraic[168] = 1.0*exp(-states[0]/45.0)
    algebraic[15] = computed_constants[169]*states[14]*(states[0]-computed_constants[32]) if neq_func(constants[2], 2.0) else computed_constants[169]*states[14]*(states[0]-77.6)
    algebraic[14] = computed_constants[176]*states[14]*(states[0]-computed_constants[40]) if neq_func(constants[2], 2.0) else computed_constants[176]*states[14]*(states[0]+102.0)
    algebraic[183] = 1.0*exp(-(states[0]+78.91)/26.62) if eq_func(constants[2], 0.0) else 1.0*exp(-(states[0]+78.91)/26.63)
    algebraic[184] = 1.0*exp((states[0]+75.13)/21.25)

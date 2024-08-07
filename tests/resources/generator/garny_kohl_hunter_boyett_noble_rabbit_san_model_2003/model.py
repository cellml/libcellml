# The content of this file was generated using the Python profile of libCellML 0.5.0.

from enum import Enum
from math import *


__version__ = "0.4.0"
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
    variables[1] = 0.0
    variables[2] = 1.0
    variables[3] = 1.0309347
    variables[5] = 2.0e-5
    variables[6] = 6.5e-5
    variables[22] = 8314.0
    variables[23] = 310.0
    variables[24] = 96845.0
    variables[26] = 5.8e-5
    variables[27] = 0.000189
    variables[28] = 5.8e-5
    variables[29] = 0.000189
    variables[30] = 5.81818e-5
    variables[31] = 0.0001888
    variables[34] = 2.52e-5
    variables[35] = 8.19e-5
    variables[36] = 2.52e-5
    variables[37] = 8.19e-5
    variables[38] = 2.523636e-5
    variables[39] = 8.1892e-5
    variables[42] = 1.32e-5
    variables[43] = 4.3e-5
    variables[44] = 1.323e-5
    variables[45] = 4.29e-5
    variables[46] = 1.3236e-5
    variables[47] = 4.2952e-5
    variables[50] = 2.7e-6
    variables[51] = 8.8e-6
    variables[52] = 2.8e-6
    variables[53] = 8.8e-6
    variables[54] = 2.7229e-6
    variables[55] = 8.83584e-6
    variables[56] = 8.0
    variables[57] = 0.5
    variables[58] = 2.0
    variables[59] = 140.0
    variables[60] = 0.0001
    variables[61] = 0.0001
    variables[63] = 0.0478
    variables[64] = 0.16
    variables[65] = 0.0478
    variables[66] = 0.16
    variables[67] = 0.04782545
    variables[68] = 0.1551936
    variables[69] = 5.4
    variables[70] = 0.621
    variables[71] = 5.64
    variables[73] = 0.0
    variables[74] = 0.0
    variables[75] = 0.0042
    variables[76] = 0.03339
    variables[77] = 0.0
    variables[78] = 0.0
    variables[79] = 140.0
    variables[82] = 0.0
    variables[83] = 1.2e-6
    variables[84] = 0.0
    variables[85] = 3.7e-7
    variables[86] = 0.0
    variables[87] = 1.204e-6
    variables[97] = 0.0058
    variables[98] = 0.0659
    variables[99] = 0.0082
    variables[100] = 0.0659
    variables[101] = 0.0057938
    variables[102] = 0.06588648
    variables[103] = 46.4
    variables[113] = 0.0043
    variables[114] = 0.0139
    variables[115] = 0.0021
    variables[116] = 0.00694
    variables[117] = 0.00427806
    variables[118] = 0.0138823
    variables[119] = 45.0
    variables[129] = 0.00491
    variables[130] = 0.03649
    variables[131] = 0.004905
    variables[132] = 0.0365
    variables[133] = 0.004905
    variables[134] = 0.036495
    variables[136] = 6.65e-5
    variables[137] = 0.0114
    variables[138] = 0.000266
    variables[139] = 0.0114
    variables[140] = 6.645504e-5
    variables[141] = 0.01138376
    variables[147] = 0.000797
    variables[148] = 0.016
    variables[149] = 0.000738
    variables[150] = 0.0208
    variables[151] = 0.00079704
    variables[152] = 0.016
    variables[161] = 0.000518
    variables[162] = 0.0104
    variables[163] = 0.000345
    variables[164] = 0.0104
    variables[165] = 0.0003445
    variables[166] = 0.0104
    variables[170] = 0.000548
    variables[171] = 0.0069
    variables[172] = 0.000437
    variables[173] = 0.0055
    variables[174] = 0.0005465
    variables[175] = 0.006875
    variables[177] = 0.000548
    variables[178] = 0.0069
    variables[179] = 0.000437
    variables[180] = 0.0055
    variables[181] = 0.0005465
    variables[182] = 0.006875
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


def compute_computed_constants(computed_constants):
    variables[0] = 1.07*(3.0*variables[1]-0.1)/(3.0*(1.0+0.7745*exp(-(3.0*variables[1]-2.05)/0.295))) if eq_func(variables[2], 0.0) else variables[3]*variables[1]/(1.0+0.7745*exp(-(3.0*variables[1]-2.05)/0.295)) if eq_func(variables[2], 1.0) else 1.07*29.0*variables[1]/(30.0*(1.0+0.7745*exp(-(29.0*variables[1]-24.5)/1.95)))
    variables[4] = variables[5]+variables[0]*(variables[6]-variables[5])
    variables[25] = variables[26]+variables[0]*(variables[27]-variables[26]) if eq_func(variables[2], 0.0) else variables[30]+variables[0]*(variables[31]-variables[30]) if eq_func(variables[2], 1.0) else variables[28]+variables[0]*(variables[29]-variables[28])
    variables[33] = variables[34]+variables[0]*(variables[35]-variables[34]) if eq_func(variables[2], 0.0) else variables[38]+variables[0]*(variables[39]-variables[38]) if eq_func(variables[2], 1.0) else variables[36]+variables[0]*(variables[37]-variables[36])
    variables[41] = variables[42]+variables[0]*(variables[43]-variables[42]) if eq_func(variables[2], 0.0) else variables[46]+variables[0]*(variables[47]-variables[46]) if eq_func(variables[2], 1.0) else variables[44]+variables[0]*(variables[45]-variables[44])
    variables[49] = variables[50]+variables[0]*(variables[51]-variables[50]) if eq_func(variables[2], 0.0) else variables[54]+variables[0]*(variables[55]-variables[54]) if eq_func(variables[2], 1.0) else variables[52]+variables[0]*(variables[53]-variables[52])
    variables[62] = variables[63]+variables[0]*(variables[64]-variables[63]) if eq_func(variables[2], 0.0) else variables[67]+variables[0]*(variables[68]-variables[67]) if eq_func(variables[2], 1.0) else variables[65]+variables[0]*(variables[66]-variables[65])
    variables[72] = variables[73]+variables[0]*(variables[74]-variables[73]) if eq_func(variables[2], 0.0) else variables[77]+variables[0]*(variables[78]-variables[77]) if eq_func(variables[2], 1.0) else variables[75]+variables[0]*(variables[76]-variables[75])
    variables[8] = variables[72]*variables[60]/(variables[60]+0.0004)
    variables[32] = variables[22]*variables[23]/variables[24]*log(variables[59]/variables[56])
    variables[40] = variables[22]*variables[23]/variables[24]*log(variables[69]/variables[79])
    variables[48] = variables[22]*variables[23]/(2.0*variables[24])*log(variables[58]/variables[60])
    variables[80] = variables[22]*variables[23]/variables[24]*log((variables[69]+0.12*variables[59])/(variables[79]+0.12*variables[56])) if eq_func(variables[2], 0.0) else variables[22]*variables[23]/variables[24]*log((variables[69]+0.03*variables[59])/(variables[79]+0.03*variables[56]))
    variables[81] = variables[82]+variables[0]*(variables[83]-variables[82]) if eq_func(variables[2], 0.0) else variables[86]+variables[0]*(variables[87]-variables[86]) if eq_func(variables[2], 1.0) else variables[84]+variables[0]*(variables[85]-variables[84])
    variables[96] = variables[97]+variables[0]*(variables[98]-variables[97]) if eq_func(variables[2], 0.0) else variables[101]+variables[0]*(variables[102]-variables[101]) if eq_func(variables[2], 1.0) else variables[99]+variables[0]*(variables[100]-variables[99])
    variables[112] = variables[113]+variables[0]*(variables[114]-variables[113]) if eq_func(variables[2], 0.0) else variables[117]+variables[0]*(variables[118]-variables[117]) if eq_func(variables[2], 1.0) else variables[115]+variables[0]*(variables[116]-variables[115])
    variables[128] = variables[129]+variables[0]*(variables[130]-variables[129]) if eq_func(variables[2], 0.0) else variables[133]+variables[0]*(variables[134]-variables[133]) if eq_func(variables[2], 1.0) else variables[131]+variables[0]*(variables[132]-variables[131])
    variables[135] = variables[136]+variables[0]*(variables[137]-variables[136]) if eq_func(variables[2], 0.0) else variables[140]+variables[0]*(variables[141]-variables[140]) if eq_func(variables[2], 1.0) else variables[138]+variables[0]*(variables[139]-variables[138])
    variables[146] = variables[147]+variables[0]*(variables[148]-variables[147]) if eq_func(variables[2], 0.0) else variables[151]+variables[0]*(variables[152]-variables[151]) if eq_func(variables[2], 1.0) else variables[149]+variables[0]*(variables[150]-variables[149])
    variables[158] = 0.002 if eq_func(variables[2], 0.0) else 0.002 if eq_func(variables[2], 1.0) else 0.006
    variables[160] = variables[161]+variables[0]*(variables[162]-variables[161]) if eq_func(variables[2], 0.0) else variables[165]+variables[0]*(variables[166]-variables[165]) if eq_func(variables[2], 1.0) else variables[163]+variables[0]*(variables[164]-variables[163])
    variables[169] = variables[170]+variables[0]*(variables[171]-variables[170]) if eq_func(variables[2], 0.0) else variables[174]+variables[0]*(variables[175]-variables[174]) if eq_func(variables[2], 1.0) else variables[172]+variables[0]*(variables[173]-variables[172])
    variables[176] = variables[177]+variables[0]*(variables[178]-variables[177]) if eq_func(variables[2], 0.0) else variables[181]+variables[0]*(variables[182]-variables[181]) if eq_func(variables[2], 1.0) else variables[179]+variables[0]*(variables[180]-variables[179])


def compute_rates(voi, states, rates, variables):
    variables[9] = variables[62]*pow(variables[56]/(variables[71]+variables[56]), 3.0)*pow(variables[69]/(variables[70]+variables[69]), 2.0)*1.6/(1.5+exp(-(states[0]+60.0)/40.0))
    variables[10] = variables[49]*(pow(variables[56], 3.0)*variables[58]*exp(0.03743*states[0]*variables[57])-pow(variables[59], 3.0)*variables[60]*exp(0.0374*states[0]*(variables[57]-1.0)))/(1.0+variables[61]*(variables[60]*pow(variables[59], 3.0)+variables[58]*pow(variables[56], 3.0))) if eq_func(variables[2], 0.0) else variables[49]*(pow(variables[56], 3.0)*variables[58]*exp(0.03743*states[0]*variables[57])-pow(variables[59], 3.0)*variables[60]*exp(0.03743*states[0]*(variables[57]-1.0)))/(1.0+variables[61]*(variables[60]*pow(variables[59], 3.0)+variables[58]*pow(variables[56], 3.0)))
    variables[14] = variables[176]*states[14]*(states[0]-variables[40]) if neq_func(variables[2], 2.0) else variables[176]*states[14]*(states[0]+102.0)
    variables[15] = variables[169]*states[14]*(states[0]-variables[32]) if neq_func(variables[2], 2.0) else variables[169]*states[14]*(states[0]-77.6)
    variables[16] = variables[160]*pow(states[13], 2.0)*(states[0]-variables[80])
    variables[18] = variables[135]*states[8]*(states[0]-variables[40])
    variables[19] = variables[128]*states[9]*states[8]*(states[0]-variables[40])
    variables[20] = variables[112]*states[7]*states[6]*(states[0]-variables[119])
    variables[21] = variables[96]*(states[4]*states[5]+0.006/(1.0+exp(-(states[0]+14.1)/6.0)))*(states[0]-variables[103])
    variables[91] = 0.0952*exp(-0.063*(states[0]+34.4))/(1.0+1.66*exp(-0.225*(states[0]+63.7)))+0.0869 if eq_func(variables[2], 0.0) else 0.09518*exp(-0.06306*(states[0]+34.4))/(1.0+1.662*exp(-0.2251*(states[0]+63.7)))+0.08693
    variables[88] = (1.0-variables[91])*states[2]+variables[91]*states[3]
    variables[7] = variables[81]*pow(states[1], 3.0)*variables[88]*variables[59]*pow(variables[24], 2.0)/(variables[22]*variables[23])*(exp((states[0]-variables[32])*variables[24]/(variables[22]*variables[23]))-1.0)/(exp(states[0]*variables[24]/(variables[22]*variables[23]))-1.0)*states[0]
    variables[11] = variables[33]*(states[0]-variables[40])
    variables[12] = variables[41]*(states[0]-variables[48])
    variables[13] = variables[25]*(states[0]-variables[32])
    variables[153] = 0.6*states[11]+0.4*states[12]
    variables[17] = variables[146]*variables[153]*states[10]*(states[0]-variables[40])
    rates[0] = -1.0/variables[4]*(variables[7]+variables[21]+variables[20]+variables[19]+variables[18]+variables[17]+variables[16]+variables[15]+variables[14]+variables[13]+variables[12]+variables[11]+variables[10]+variables[9]+variables[8])
    variables[89] = pow(1.0/(1.0+exp(-states[0]/5.46)), 1.0/3.0) if eq_func(variables[2], 0.0) else pow(1.0/(1.0+exp(-(states[0]+30.32)/5.46)), 1.0/3.0)
    variables[90] = 0.0006247/(0.832*exp(-0.335*(states[0]+56.7))+0.627*exp(0.082*(states[0]+65.01)))+4.0e-5 if eq_func(variables[2], 0.0) else 0.0006247/(0.8322166*exp(-0.33566*(states[0]+56.7062))+0.6274*exp(0.0823*(states[0]+65.0131)))+4.569e-5
    rates[1] = (variables[89]-states[1])/variables[90]
    variables[92] = 1.0/(1.0+exp((states[0]+66.1)/6.4))
    variables[93] = 3.717e-6*exp(-0.2815*(states[0]+17.11))/(1.0+0.003732*exp(-0.3426*(states[0]+37.76)))+0.0005977
    rates[2] = (variables[92]-states[2])/variables[93]
    variables[94] = variables[92]
    variables[95] = 3.186e-8*exp(-0.6219*(states[0]+18.8))/(1.0+7.189e-5*exp(-0.6683*(states[0]+34.07)))+0.003556
    rates[3] = (variables[94]-states[3])/variables[95]
    variables[104] = 1.0/(1.0+exp(-(states[0]+23.1)/6.0)) if eq_func(variables[2], 0.0) else 1.0/(1.0+exp(-(states[0]+22.3+0.8*variables[0])/6.0)) if eq_func(variables[2], 1.0) else 1.0/(1.0+exp(-(states[0]+22.2)/6.0))
    variables[106] = -28.38*(states[0]+35.0)/(exp(-(states[0]+35.0)/2.5)-1.0)-84.9*states[0]/(exp(-0.208*states[0])-1.0) if eq_func(variables[2], 0.0) else -28.39*(states[0]+35.0)/(exp(-(states[0]+35.0)/2.5)-1.0)-84.9*states[0]/(exp(-0.208*states[0])-1.0) if eq_func(variables[2], 1.0) else -28.4*(states[0]+35.0)/(exp(-(states[0]+35.0)/2.5)-1.0)-84.9*states[0]/(exp(-0.208*states[0])-1.0)
    variables[107] = 11.43*(states[0]-5.0)/(exp(0.4*(states[0]-5.0))-1.0) if eq_func(variables[2], 1.0) else 11.42*(states[0]-5.0)/(exp(0.4*(states[0]-5.0))-1.0)
    variables[105] = 2.0/(variables[106]+variables[107])
    rates[5] = (variables[104]-states[5])/variables[105]
    variables[108] = 1.0/(1.0+exp((states[0]+45.0)/5.0))
    variables[110] = 3.75*(states[0]+28.0)/(exp((states[0]+28.0)/4.0)-1.0) if eq_func(variables[2], 1.0) else 3.12*(states[0]+28.0)/(exp((states[0]+28.0)/4.0)-1.0)
    variables[111] = 30.0/(1.0+exp(-(states[0]+28.0)/4.0)) if eq_func(variables[2], 1.0) else 25.0/(1.0+exp(-(states[0]+28.0)/4.0))
    variables[109] = (1.2-0.2*variables[0])/(variables[110]+variables[111]) if eq_func(variables[2], 1.0) else 1.0/(variables[110]+variables[111])
    rates[4] = (variables[108]-states[4])/variables[109]
    variables[120] = 1.0/(1.0+exp(-(states[0]+37.0)/6.8))
    variables[122] = 1068.0*exp((states[0]+26.3)/30.0)
    variables[123] = 1068.0*exp(-(states[0]+26.3)/30.0)
    variables[121] = 1.0/(variables[122]+variables[123])
    rates[7] = (variables[120]-states[7])/variables[121]
    variables[124] = 1.0/(1.0+exp((states[0]+71.0)/9.0))
    variables[126] = 15.3*exp(-(states[0]+71.0+0.7*variables[0])/83.3) if eq_func(variables[2], 1.0) else 15.3*exp(-(states[0]+71.7)/83.3)
    variables[127] = 15.0*exp((states[0]+71.0)/15.38) if eq_func(variables[2], 1.0) else 15.0*exp((states[0]+71.7)/15.38)
    variables[125] = 1.0/(variables[126]+variables[127])
    rates[6] = (variables[124]-states[6])/variables[125]
    variables[142] = 1.0/(1.0+exp((states[0]+59.37)/13.1))
    variables[143] = 0.0101+0.06517/(0.57*exp(-0.08*(states[0]+49.0)))+2.4e-5*exp(0.1*(states[0]+50.93)) if eq_func(variables[2], 0.0) else 0.001/3.0*(30.31+195.5/(0.5686*exp(-0.08161*(states[0]+39.0+10.0*variables[0]))+0.7174*exp((0.2719-0.1719*variables[0])*1.0*(states[0]+40.93+10.0*variables[0])))) if eq_func(variables[2], 1.0) else 0.0101+0.06517/(0.5686*exp(-0.08161*(states[0]+39.0))+0.7174*exp(0.2719*(states[0]+40.93)))
    rates[9] = (variables[142]-states[9])/variables[143]
    variables[144] = 1.0/(1.0+exp(-(states[0]-10.93)/19.7))
    variables[145] = 0.001*(2.98+15.59/(1.037*exp(0.09*(states[0]+30.61))+0.369*exp(-0.12*(states[0]+23.84)))) if eq_func(variables[2], 0.0) else 0.0025*(1.191+7.838/(1.037*exp(0.09012*(states[0]+30.61))+0.369*exp(-0.119*(states[0]+23.84)))) if eq_func(variables[2], 1.0) else 0.001*(2.98+19.59/(1.037*exp(0.09012*(states[0]+30.61))+0.369*exp(-0.119*(states[0]+23.84))))
    rates[8] = (variables[144]-states[8])/variables[145]
    variables[154] = 1.0/(1.0+exp(-(states[0]+14.2)/10.6)) if neq_func(variables[2], 2.0) else 1.0/(1.0+exp(-(states[0]+13.2)/10.6))
    variables[155] = 1.0/(37.2*exp((states[0]-9.0)/15.9)+0.96*exp(-(states[0]-9.0)/22.5)) if neq_func(variables[2], 2.0) else 1.0/(37.2*exp((states[0]-10.0)/15.9)+0.96*exp(-(states[0]-10.0)/22.5))
    rates[11] = (variables[154]-states[11])/variables[155]
    variables[156] = variables[154]
    variables[157] = 1.0/(4.2*exp((states[0]-9.0)/17.0)+0.15*exp(-(states[0]-9.0)/21.6)) if neq_func(variables[2], 2.0) else 1.0/(4.2*exp((states[0]-10.0)/17.0)+0.15*exp(-(states[0]-10.0)/21.6))
    rates[12] = (variables[156]-states[12])/variables[157]
    variables[159] = 1.0/(1.0+exp((states[0]+18.6)/10.1))
    rates[10] = (variables[159]-states[10])/variables[158]
    variables[167] = 14.0/(1.0+exp(-(states[0]-40.0)/9.0))
    variables[168] = 1.0*exp(-states[0]/45.0)
    rates[13] = variables[167]*(1.0-states[13])-variables[168]*states[13]
    variables[183] = 1.0*exp(-(states[0]+78.91)/26.62) if eq_func(variables[2], 0.0) else 1.0*exp(-(states[0]+78.91)/26.63)
    variables[184] = 1.0*exp((states[0]+75.13)/21.25)
    rates[14] = variables[183]*(1.0-states[14])-variables[184]*states[14]


def compute_variables(voi, states, rates, variables):
    variables[13] = variables[25]*(states[0]-variables[32])
    variables[11] = variables[33]*(states[0]-variables[40])
    variables[12] = variables[41]*(states[0]-variables[48])
    variables[10] = variables[49]*(pow(variables[56], 3.0)*variables[58]*exp(0.03743*states[0]*variables[57])-pow(variables[59], 3.0)*variables[60]*exp(0.0374*states[0]*(variables[57]-1.0)))/(1.0+variables[61]*(variables[60]*pow(variables[59], 3.0)+variables[58]*pow(variables[56], 3.0))) if eq_func(variables[2], 0.0) else variables[49]*(pow(variables[56], 3.0)*variables[58]*exp(0.03743*states[0]*variables[57])-pow(variables[59], 3.0)*variables[60]*exp(0.03743*states[0]*(variables[57]-1.0)))/(1.0+variables[61]*(variables[60]*pow(variables[59], 3.0)+variables[58]*pow(variables[56], 3.0)))
    variables[9] = variables[62]*pow(variables[56]/(variables[71]+variables[56]), 3.0)*pow(variables[69]/(variables[70]+variables[69]), 2.0)*1.6/(1.5+exp(-(states[0]+60.0)/40.0))
    variables[91] = 0.0952*exp(-0.063*(states[0]+34.4))/(1.0+1.66*exp(-0.225*(states[0]+63.7)))+0.0869 if eq_func(variables[2], 0.0) else 0.09518*exp(-0.06306*(states[0]+34.4))/(1.0+1.662*exp(-0.2251*(states[0]+63.7)))+0.08693
    variables[88] = (1.0-variables[91])*states[2]+variables[91]*states[3]
    variables[7] = variables[81]*pow(states[1], 3.0)*variables[88]*variables[59]*pow(variables[24], 2.0)/(variables[22]*variables[23])*(exp((states[0]-variables[32])*variables[24]/(variables[22]*variables[23]))-1.0)/(exp(states[0]*variables[24]/(variables[22]*variables[23]))-1.0)*states[0]
    variables[89] = pow(1.0/(1.0+exp(-states[0]/5.46)), 1.0/3.0) if eq_func(variables[2], 0.0) else pow(1.0/(1.0+exp(-(states[0]+30.32)/5.46)), 1.0/3.0)
    variables[90] = 0.0006247/(0.832*exp(-0.335*(states[0]+56.7))+0.627*exp(0.082*(states[0]+65.01)))+4.0e-5 if eq_func(variables[2], 0.0) else 0.0006247/(0.8322166*exp(-0.33566*(states[0]+56.7062))+0.6274*exp(0.0823*(states[0]+65.0131)))+4.569e-5
    variables[92] = 1.0/(1.0+exp((states[0]+66.1)/6.4))
    variables[94] = variables[92]
    variables[93] = 3.717e-6*exp(-0.2815*(states[0]+17.11))/(1.0+0.003732*exp(-0.3426*(states[0]+37.76)))+0.0005977
    variables[95] = 3.186e-8*exp(-0.6219*(states[0]+18.8))/(1.0+7.189e-5*exp(-0.6683*(states[0]+34.07)))+0.003556
    variables[21] = variables[96]*(states[4]*states[5]+0.006/(1.0+exp(-(states[0]+14.1)/6.0)))*(states[0]-variables[103])
    variables[106] = -28.38*(states[0]+35.0)/(exp(-(states[0]+35.0)/2.5)-1.0)-84.9*states[0]/(exp(-0.208*states[0])-1.0) if eq_func(variables[2], 0.0) else -28.39*(states[0]+35.0)/(exp(-(states[0]+35.0)/2.5)-1.0)-84.9*states[0]/(exp(-0.208*states[0])-1.0) if eq_func(variables[2], 1.0) else -28.4*(states[0]+35.0)/(exp(-(states[0]+35.0)/2.5)-1.0)-84.9*states[0]/(exp(-0.208*states[0])-1.0)
    variables[107] = 11.43*(states[0]-5.0)/(exp(0.4*(states[0]-5.0))-1.0) if eq_func(variables[2], 1.0) else 11.42*(states[0]-5.0)/(exp(0.4*(states[0]-5.0))-1.0)
    variables[105] = 2.0/(variables[106]+variables[107])
    variables[104] = 1.0/(1.0+exp(-(states[0]+23.1)/6.0)) if eq_func(variables[2], 0.0) else 1.0/(1.0+exp(-(states[0]+22.3+0.8*variables[0])/6.0)) if eq_func(variables[2], 1.0) else 1.0/(1.0+exp(-(states[0]+22.2)/6.0))
    variables[110] = 3.75*(states[0]+28.0)/(exp((states[0]+28.0)/4.0)-1.0) if eq_func(variables[2], 1.0) else 3.12*(states[0]+28.0)/(exp((states[0]+28.0)/4.0)-1.0)
    variables[111] = 30.0/(1.0+exp(-(states[0]+28.0)/4.0)) if eq_func(variables[2], 1.0) else 25.0/(1.0+exp(-(states[0]+28.0)/4.0))
    variables[109] = (1.2-0.2*variables[0])/(variables[110]+variables[111]) if eq_func(variables[2], 1.0) else 1.0/(variables[110]+variables[111])
    variables[108] = 1.0/(1.0+exp((states[0]+45.0)/5.0))
    variables[20] = variables[112]*states[7]*states[6]*(states[0]-variables[119])
    variables[122] = 1068.0*exp((states[0]+26.3)/30.0)
    variables[123] = 1068.0*exp(-(states[0]+26.3)/30.0)
    variables[121] = 1.0/(variables[122]+variables[123])
    variables[120] = 1.0/(1.0+exp(-(states[0]+37.0)/6.8))
    variables[126] = 15.3*exp(-(states[0]+71.0+0.7*variables[0])/83.3) if eq_func(variables[2], 1.0) else 15.3*exp(-(states[0]+71.7)/83.3)
    variables[127] = 15.0*exp((states[0]+71.0)/15.38) if eq_func(variables[2], 1.0) else 15.0*exp((states[0]+71.7)/15.38)
    variables[125] = 1.0/(variables[126]+variables[127])
    variables[124] = 1.0/(1.0+exp((states[0]+71.0)/9.0))
    variables[19] = variables[128]*states[9]*states[8]*(states[0]-variables[40])
    variables[18] = variables[135]*states[8]*(states[0]-variables[40])
    variables[142] = 1.0/(1.0+exp((states[0]+59.37)/13.1))
    variables[143] = 0.0101+0.06517/(0.57*exp(-0.08*(states[0]+49.0)))+2.4e-5*exp(0.1*(states[0]+50.93)) if eq_func(variables[2], 0.0) else 0.001/3.0*(30.31+195.5/(0.5686*exp(-0.08161*(states[0]+39.0+10.0*variables[0]))+0.7174*exp((0.2719-0.1719*variables[0])*1.0*(states[0]+40.93+10.0*variables[0])))) if eq_func(variables[2], 1.0) else 0.0101+0.06517/(0.5686*exp(-0.08161*(states[0]+39.0))+0.7174*exp(0.2719*(states[0]+40.93)))
    variables[144] = 1.0/(1.0+exp(-(states[0]-10.93)/19.7))
    variables[145] = 0.001*(2.98+15.59/(1.037*exp(0.09*(states[0]+30.61))+0.369*exp(-0.12*(states[0]+23.84)))) if eq_func(variables[2], 0.0) else 0.0025*(1.191+7.838/(1.037*exp(0.09012*(states[0]+30.61))+0.369*exp(-0.119*(states[0]+23.84)))) if eq_func(variables[2], 1.0) else 0.001*(2.98+19.59/(1.037*exp(0.09012*(states[0]+30.61))+0.369*exp(-0.119*(states[0]+23.84))))
    variables[153] = 0.6*states[11]+0.4*states[12]
    variables[17] = variables[146]*variables[153]*states[10]*(states[0]-variables[40])
    variables[154] = 1.0/(1.0+exp(-(states[0]+14.2)/10.6)) if neq_func(variables[2], 2.0) else 1.0/(1.0+exp(-(states[0]+13.2)/10.6))
    variables[155] = 1.0/(37.2*exp((states[0]-9.0)/15.9)+0.96*exp(-(states[0]-9.0)/22.5)) if neq_func(variables[2], 2.0) else 1.0/(37.2*exp((states[0]-10.0)/15.9)+0.96*exp(-(states[0]-10.0)/22.5))
    variables[156] = variables[154]
    variables[157] = 1.0/(4.2*exp((states[0]-9.0)/17.0)+0.15*exp(-(states[0]-9.0)/21.6)) if neq_func(variables[2], 2.0) else 1.0/(4.2*exp((states[0]-10.0)/17.0)+0.15*exp(-(states[0]-10.0)/21.6))
    variables[159] = 1.0/(1.0+exp((states[0]+18.6)/10.1))
    variables[16] = variables[160]*pow(states[13], 2.0)*(states[0]-variables[80])
    variables[167] = 14.0/(1.0+exp(-(states[0]-40.0)/9.0))
    variables[168] = 1.0*exp(-states[0]/45.0)
    variables[15] = variables[169]*states[14]*(states[0]-variables[32]) if neq_func(variables[2], 2.0) else variables[169]*states[14]*(states[0]-77.6)
    variables[14] = variables[176]*states[14]*(states[0]-variables[40]) if neq_func(variables[2], 2.0) else variables[176]*states[14]*(states[0]+102.0)
    variables[183] = 1.0*exp(-(states[0]+78.91)/26.62) if eq_func(variables[2], 0.0) else 1.0*exp(-(states[0]+78.91)/26.63)
    variables[184] = 1.0*exp((states[0]+75.13)/21.25)

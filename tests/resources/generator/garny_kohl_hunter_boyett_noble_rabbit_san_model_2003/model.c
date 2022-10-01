/* The content of this file was generated using the C profile of libCellML 0.3.104. */

#include "model.h"

#include <math.h>
#include <stdlib.h>

const char VERSION[] = "0.3.0";
const char LIBCELLML_VERSION[] = "0.3.104";

const size_t STATE_COUNT = 15;
const size_t VARIABLE_COUNT = 185;

const VariableInfo VOI_INFO = {"time", "second", "environment", VARIABLE_OF_INTEGRATION};

const VariableInfo STATE_INFO[] = {
    {"m", "dimensionless", "sodium_current_m_gate", STATE},
    {"h1", "dimensionless", "sodium_current_h_gate", STATE},
    {"h2", "dimensionless", "sodium_current_h_gate", STATE},
    {"d_L", "dimensionless", "L_type_Ca_channel_d_gate", STATE},
    {"f_L", "dimensionless", "L_type_Ca_channel_f_gate", STATE},
    {"d_T", "dimensionless", "T_type_Ca_channel_d_gate", STATE},
    {"f_T", "dimensionless", "T_type_Ca_channel_f_gate", STATE},
    {"q", "dimensionless", "four_AP_sensitive_currents_q_gate", STATE},
    {"r", "dimensionless", "four_AP_sensitive_currents_r_gate", STATE},
    {"P_af", "dimensionless", "rapid_delayed_rectifying_potassium_current_P_af_gate", STATE},
    {"P_as", "dimensionless", "rapid_delayed_rectifying_potassium_current_P_as_gate", STATE},
    {"P_i", "dimensionless", "rapid_delayed_rectifying_potassium_current_P_i_gate", STATE},
    {"xs", "dimensionless", "slow_delayed_rectifying_potassium_current_xs_gate", STATE},
    {"y", "dimensionless", "hyperpolarisation_activated_current_y_gate", STATE},
    {"V", "millivolt", "membrane", STATE}
};

const VariableInfo VARIABLE_INFO[] = {
    {"E_Ca_L", "millivolt", "L_type_Ca_channel", CONSTANT},
    {"g_Ca_L_Centre_0DCapable", "microS", "L_type_Ca_channel", CONSTANT},
    {"g_Ca_L_Centre_1DCapable", "microS", "L_type_Ca_channel", CONSTANT},
    {"g_Ca_L_Centre_Published", "microS", "L_type_Ca_channel", CONSTANT},
    {"g_Ca_L_Periphery_0DCapable", "microS", "L_type_Ca_channel", CONSTANT},
    {"g_Ca_L_Periphery_1DCapable", "microS", "L_type_Ca_channel", CONSTANT},
    {"g_Ca_L_Periphery_Published", "microS", "L_type_Ca_channel", CONSTANT},
    {"E_Ca_T", "millivolt", "T_type_Ca_channel", CONSTANT},
    {"g_Ca_T_Centre_0DCapable", "microS", "T_type_Ca_channel", CONSTANT},
    {"g_Ca_T_Centre_1DCapable", "microS", "T_type_Ca_channel", CONSTANT},
    {"g_Ca_T_Centre_Published", "microS", "T_type_Ca_channel", CONSTANT},
    {"g_Ca_T_Periphery_0DCapable", "microS", "T_type_Ca_channel", CONSTANT},
    {"g_Ca_T_Periphery_1DCapable", "microS", "T_type_Ca_channel", CONSTANT},
    {"g_Ca_T_Periphery_Published", "microS", "T_type_Ca_channel", CONSTANT},
    {"g_b_Ca_Centre_0DCapable", "microS", "calcium_background_current", CONSTANT},
    {"g_b_Ca_Centre_1DCapable", "microS", "calcium_background_current", CONSTANT},
    {"g_b_Ca_Centre_Published", "microS", "calcium_background_current", CONSTANT},
    {"g_b_Ca_Periphery_0DCapable", "microS", "calcium_background_current", CONSTANT},
    {"g_b_Ca_Periphery_1DCapable", "microS", "calcium_background_current", CONSTANT},
    {"g_b_Ca_Periphery_Published", "microS", "calcium_background_current", CONSTANT},
    {"g_sus_Centre_0DCapable", "microS", "four_AP_sensitive_currents", CONSTANT},
    {"g_sus_Centre_1DCapable", "microS", "four_AP_sensitive_currents", CONSTANT},
    {"g_sus_Centre_Published", "microS", "four_AP_sensitive_currents", CONSTANT},
    {"g_sus_Periphery_0DCapable", "microS", "four_AP_sensitive_currents", CONSTANT},
    {"g_sus_Periphery_1DCapable", "microS", "four_AP_sensitive_currents", CONSTANT},
    {"g_sus_Periphery_Published", "microS", "four_AP_sensitive_currents", CONSTANT},
    {"g_to_Centre_0DCapable", "microS", "four_AP_sensitive_currents", CONSTANT},
    {"g_to_Centre_1DCapable", "microS", "four_AP_sensitive_currents", CONSTANT},
    {"g_to_Centre_Published", "microS", "four_AP_sensitive_currents", CONSTANT},
    {"g_to_Periphery_0DCapable", "microS", "four_AP_sensitive_currents", CONSTANT},
    {"g_to_Periphery_1DCapable", "microS", "four_AP_sensitive_currents", CONSTANT},
    {"g_to_Periphery_Published", "microS", "four_AP_sensitive_currents", CONSTANT},
    {"g_f_K_Centre_0DCapable", "microS", "hyperpolarisation_activated_current", CONSTANT},
    {"g_f_K_Centre_1DCapable", "microS", "hyperpolarisation_activated_current", CONSTANT},
    {"g_f_K_Centre_Published", "microS", "hyperpolarisation_activated_current", CONSTANT},
    {"g_f_K_Periphery_0DCapable", "microS", "hyperpolarisation_activated_current", CONSTANT},
    {"g_f_K_Periphery_1DCapable", "microS", "hyperpolarisation_activated_current", CONSTANT},
    {"g_f_K_Periphery_Published", "microS", "hyperpolarisation_activated_current", CONSTANT},
    {"g_f_Na_Centre_0DCapable", "microS", "hyperpolarisation_activated_current", CONSTANT},
    {"g_f_Na_Centre_1DCapable", "microS", "hyperpolarisation_activated_current", CONSTANT},
    {"g_f_Na_Centre_Published", "microS", "hyperpolarisation_activated_current", CONSTANT},
    {"g_f_Na_Periphery_0DCapable", "microS", "hyperpolarisation_activated_current", CONSTANT},
    {"g_f_Na_Periphery_1DCapable", "microS", "hyperpolarisation_activated_current", CONSTANT},
    {"g_f_Na_Periphery_Published", "microS", "hyperpolarisation_activated_current", CONSTANT},
    {"Ca_i", "millimolar", "ionic_concentrations", CONSTANT},
    {"Ca_o", "millimolar", "ionic_concentrations", CONSTANT},
    {"K_i", "millimolar", "ionic_concentrations", CONSTANT},
    {"K_o", "millimolar", "ionic_concentrations", CONSTANT},
    {"Na_i", "millimolar", "ionic_concentrations", CONSTANT},
    {"Na_o", "millimolar", "ionic_concentrations", CONSTANT},
    {"CmCentre", "microF", "membrane", CONSTANT},
    {"CmPeriphery", "microF", "membrane", CONSTANT},
    {"F", "coulomb_per_mole", "membrane", CONSTANT},
    {"FCellConstant", "dimensionless", "membrane", CONSTANT},
    {"R", "millijoule_per_mole_kelvin", "membrane", CONSTANT},
    {"T", "kelvin", "membrane", CONSTANT},
    {"Version", "dimensionless", "membrane", CONSTANT},
    {"dCell", "dimensionless", "membrane", CONSTANT},
    {"i_Ca_p_max_Centre_0DCapable", "nanoA", "persistent_calcium_current", CONSTANT},
    {"i_Ca_p_max_Centre_1DCapable", "nanoA", "persistent_calcium_current", CONSTANT},
    {"i_Ca_p_max_Centre_Published", "nanoA", "persistent_calcium_current", CONSTANT},
    {"i_Ca_p_max_Periphery_0DCapable", "nanoA", "persistent_calcium_current", CONSTANT},
    {"i_Ca_p_max_Periphery_1DCapable", "nanoA", "persistent_calcium_current", CONSTANT},
    {"i_Ca_p_max_Periphery_Published", "nanoA", "persistent_calcium_current", CONSTANT},
    {"g_b_K_Centre_0DCapable", "microS", "potassium_background_current", CONSTANT},
    {"g_b_K_Centre_1DCapable", "microS", "potassium_background_current", CONSTANT},
    {"g_b_K_Centre_Published", "microS", "potassium_background_current", CONSTANT},
    {"g_b_K_Periphery_0DCapable", "microS", "potassium_background_current", CONSTANT},
    {"g_b_K_Periphery_1DCapable", "microS", "potassium_background_current", CONSTANT},
    {"g_b_K_Periphery_Published", "microS", "potassium_background_current", CONSTANT},
    {"g_K_r_Centre_0DCapable", "microS", "rapid_delayed_rectifying_potassium_current", CONSTANT},
    {"g_K_r_Centre_1DCapable", "microS", "rapid_delayed_rectifying_potassium_current", CONSTANT},
    {"g_K_r_Centre_Published", "microS", "rapid_delayed_rectifying_potassium_current", CONSTANT},
    {"g_K_r_Periphery_0DCapable", "microS", "rapid_delayed_rectifying_potassium_current", CONSTANT},
    {"g_K_r_Periphery_1DCapable", "microS", "rapid_delayed_rectifying_potassium_current", CONSTANT},
    {"g_K_r_Periphery_Published", "microS", "rapid_delayed_rectifying_potassium_current", CONSTANT},
    {"g_K_s_Centre_0DCapable", "microS", "slow_delayed_rectifying_potassium_current", CONSTANT},
    {"g_K_s_Centre_1DCapable", "microS", "slow_delayed_rectifying_potassium_current", CONSTANT},
    {"g_K_s_Centre_Published", "microS", "slow_delayed_rectifying_potassium_current", CONSTANT},
    {"g_K_s_Periphery_0DCapable", "microS", "slow_delayed_rectifying_potassium_current", CONSTANT},
    {"g_K_s_Periphery_1DCapable", "microS", "slow_delayed_rectifying_potassium_current", CONSTANT},
    {"g_K_s_Periphery_Published", "microS", "slow_delayed_rectifying_potassium_current", CONSTANT},
    {"g_b_Na_Centre_0DCapable", "microS", "sodium_background_current", CONSTANT},
    {"g_b_Na_Centre_1DCapable", "microS", "sodium_background_current", CONSTANT},
    {"g_b_Na_Centre_Published", "microS", "sodium_background_current", CONSTANT},
    {"g_b_Na_Periphery_0DCapable", "microS", "sodium_background_current", CONSTANT},
    {"g_b_Na_Periphery_1DCapable", "microS", "sodium_background_current", CONSTANT},
    {"g_b_Na_Periphery_Published", "microS", "sodium_background_current", CONSTANT},
    {"d_NaCa", "dimensionless", "sodium_calcium_exchanger", CONSTANT},
    {"gamma_NaCa", "dimensionless", "sodium_calcium_exchanger", CONSTANT},
    {"k_NaCa_Centre_0DCapable", "nanoA", "sodium_calcium_exchanger", CONSTANT},
    {"k_NaCa_Centre_1DCapable", "nanoA", "sodium_calcium_exchanger", CONSTANT},
    {"k_NaCa_Centre_Published", "nanoA", "sodium_calcium_exchanger", CONSTANT},
    {"k_NaCa_Periphery_0DCapable", "nanoA", "sodium_calcium_exchanger", CONSTANT},
    {"k_NaCa_Periphery_1DCapable", "nanoA", "sodium_calcium_exchanger", CONSTANT},
    {"k_NaCa_Periphery_Published", "nanoA", "sodium_calcium_exchanger", CONSTANT},
    {"g_Na_Centre_0DCapable", "microlitre_per_second", "sodium_current", CONSTANT},
    {"g_Na_Centre_1DCapable", "microlitre_per_second", "sodium_current", CONSTANT},
    {"g_Na_Centre_Published", "microlitre_per_second", "sodium_current", CONSTANT},
    {"g_Na_Periphery_0DCapable", "microlitre_per_second", "sodium_current", CONSTANT},
    {"g_Na_Periphery_1DCapable", "microlitre_per_second", "sodium_current", CONSTANT},
    {"g_Na_Periphery_Published", "microlitre_per_second", "sodium_current", CONSTANT},
    {"K_m_K", "millimolar", "sodium_potassium_pump", CONSTANT},
    {"K_m_Na", "millimolar", "sodium_potassium_pump", CONSTANT},
    {"i_p_max_Centre_0DCapable", "nanoA", "sodium_potassium_pump", CONSTANT},
    {"i_p_max_Centre_1DCapable", "nanoA", "sodium_potassium_pump", CONSTANT},
    {"i_p_max_Centre_Published", "nanoA", "sodium_potassium_pump", CONSTANT},
    {"i_p_max_Periphery_0DCapable", "nanoA", "sodium_potassium_pump", CONSTANT},
    {"i_p_max_Periphery_1DCapable", "nanoA", "sodium_potassium_pump", CONSTANT},
    {"i_p_max_Periphery_Published", "nanoA", "sodium_potassium_pump", CONSTANT},
    {"FCell", "dimensionless", "membrane", COMPUTED_CONSTANT},
    {"Cm", "microF", "membrane", COMPUTED_CONSTANT},
    {"g_b_Na", "microS", "sodium_background_current", COMPUTED_CONSTANT},
    {"g_b_K", "microS", "potassium_background_current", COMPUTED_CONSTANT},
    {"g_b_Ca", "microS", "calcium_background_current", COMPUTED_CONSTANT},
    {"k_NaCa", "nanoA", "sodium_calcium_exchanger", COMPUTED_CONSTANT},
    {"i_NaCa", "nanoA", "sodium_calcium_exchanger", ALGEBRAIC},
    {"i_p_max", "nanoA", "sodium_potassium_pump", COMPUTED_CONSTANT},
    {"i_p", "nanoA", "sodium_potassium_pump", ALGEBRAIC},
    {"i_Ca_p_max", "nanoA", "persistent_calcium_current", COMPUTED_CONSTANT},
    {"i_Ca_p", "nanoA", "persistent_calcium_current", COMPUTED_CONSTANT},
    {"E_Na", "millivolt", "reversal_and_equilibrium_potentials", COMPUTED_CONSTANT},
    {"E_K", "millivolt", "reversal_and_equilibrium_potentials", COMPUTED_CONSTANT},
    {"E_Ca", "millivolt", "reversal_and_equilibrium_potentials", COMPUTED_CONSTANT},
    {"E_K_s", "millivolt", "reversal_and_equilibrium_potentials", COMPUTED_CONSTANT},
    {"g_Na", "microlitre_per_second", "sodium_current", COMPUTED_CONSTANT},
    {"m_infinity", "dimensionless", "sodium_current_m_gate", ALGEBRAIC},
    {"tau_m", "second", "sodium_current_m_gate", ALGEBRAIC},
    {"F_Na", "dimensionless", "sodium_current_h_gate", ALGEBRAIC},
    {"h", "dimensionless", "sodium_current_h_gate", ALGEBRAIC},
    {"h1_infinity", "dimensionless", "sodium_current_h_gate", ALGEBRAIC},
    {"h2_infinity", "dimensionless", "sodium_current_h_gate", ALGEBRAIC},
    {"tau_h1", "second", "sodium_current_h_gate", ALGEBRAIC},
    {"tau_h2", "second", "sodium_current_h_gate", ALGEBRAIC},
    {"g_Ca_L", "microS", "L_type_Ca_channel", COMPUTED_CONSTANT},
    {"i_Ca_L", "nanoA", "L_type_Ca_channel", ALGEBRAIC},
    {"alpha_d_L", "per_second", "L_type_Ca_channel_d_gate", ALGEBRAIC},
    {"beta_d_L", "per_second", "L_type_Ca_channel_d_gate", ALGEBRAIC},
    {"tau_d_L", "second", "L_type_Ca_channel_d_gate", ALGEBRAIC},
    {"d_L_infinity", "dimensionless", "L_type_Ca_channel_d_gate", ALGEBRAIC},
    {"alpha_f_L", "per_second", "L_type_Ca_channel_f_gate", ALGEBRAIC},
    {"beta_f_L", "per_second", "L_type_Ca_channel_f_gate", ALGEBRAIC},
    {"tau_f_L", "second", "L_type_Ca_channel_f_gate", ALGEBRAIC},
    {"f_L_infinity", "dimensionless", "L_type_Ca_channel_f_gate", ALGEBRAIC},
    {"g_Ca_T", "microS", "T_type_Ca_channel", COMPUTED_CONSTANT},
    {"i_Ca_T", "nanoA", "T_type_Ca_channel", ALGEBRAIC},
    {"alpha_d_T", "per_second", "T_type_Ca_channel_d_gate", ALGEBRAIC},
    {"beta_d_T", "per_second", "T_type_Ca_channel_d_gate", ALGEBRAIC},
    {"tau_d_T", "second", "T_type_Ca_channel_d_gate", ALGEBRAIC},
    {"d_T_infinity", "dimensionless", "T_type_Ca_channel_d_gate", ALGEBRAIC},
    {"alpha_f_T", "per_second", "T_type_Ca_channel_f_gate", ALGEBRAIC},
    {"beta_f_T", "per_second", "T_type_Ca_channel_f_gate", ALGEBRAIC},
    {"tau_f_T", "second", "T_type_Ca_channel_f_gate", ALGEBRAIC},
    {"f_T_infinity", "dimensionless", "T_type_Ca_channel_f_gate", ALGEBRAIC},
    {"g_to", "microS", "four_AP_sensitive_currents", COMPUTED_CONSTANT},
    {"g_sus", "microS", "four_AP_sensitive_currents", COMPUTED_CONSTANT},
    {"i_to", "nanoA", "four_AP_sensitive_currents", ALGEBRAIC},
    {"i_sus", "nanoA", "four_AP_sensitive_currents", ALGEBRAIC},
    {"q_infinity", "dimensionless", "four_AP_sensitive_currents_q_gate", ALGEBRAIC},
    {"tau_q", "second", "four_AP_sensitive_currents_q_gate", ALGEBRAIC},
    {"r_infinity", "dimensionless", "four_AP_sensitive_currents_r_gate", ALGEBRAIC},
    {"tau_r", "second", "four_AP_sensitive_currents_r_gate", ALGEBRAIC},
    {"g_K_r", "microS", "rapid_delayed_rectifying_potassium_current", COMPUTED_CONSTANT},
    {"P_a", "dimensionless", "rapid_delayed_rectifying_potassium_current", ALGEBRAIC},
    {"P_af_infinity", "dimensionless", "rapid_delayed_rectifying_potassium_current_P_af_gate", ALGEBRAIC},
    {"tau_P_af", "second", "rapid_delayed_rectifying_potassium_current_P_af_gate", ALGEBRAIC},
    {"P_as_infinity", "dimensionless", "rapid_delayed_rectifying_potassium_current_P_as_gate", ALGEBRAIC},
    {"tau_P_as", "second", "rapid_delayed_rectifying_potassium_current_P_as_gate", ALGEBRAIC},
    {"tau_P_i", "second", "rapid_delayed_rectifying_potassium_current_P_i_gate", COMPUTED_CONSTANT},
    {"P_i_infinity", "dimensionless", "rapid_delayed_rectifying_potassium_current_P_i_gate", ALGEBRAIC},
    {"g_K_s", "microS", "slow_delayed_rectifying_potassium_current", COMPUTED_CONSTANT},
    {"i_K_s", "nanoA", "slow_delayed_rectifying_potassium_current", ALGEBRAIC},
    {"alpha_xs", "per_second", "slow_delayed_rectifying_potassium_current_xs_gate", ALGEBRAIC},
    {"beta_xs", "per_second", "slow_delayed_rectifying_potassium_current_xs_gate", ALGEBRAIC},
    {"g_f_Na", "microS", "hyperpolarisation_activated_current", COMPUTED_CONSTANT},
    {"i_f_Na", "nanoA", "hyperpolarisation_activated_current", ALGEBRAIC},
    {"g_f_K", "microS", "hyperpolarisation_activated_current", COMPUTED_CONSTANT},
    {"i_f_K", "nanoA", "hyperpolarisation_activated_current", ALGEBRAIC},
    {"alpha_y", "per_second", "hyperpolarisation_activated_current_y_gate", ALGEBRAIC},
    {"beta_y", "per_second", "hyperpolarisation_activated_current_y_gate", ALGEBRAIC},
    {"i_b_Na", "nanoA", "sodium_background_current", ALGEBRAIC},
    {"i_b_K", "nanoA", "potassium_background_current", ALGEBRAIC},
    {"i_b_Ca", "nanoA", "calcium_background_current", ALGEBRAIC},
    {"i_Na", "nanoA", "sodium_current", ALGEBRAIC},
    {"i_K_r", "nanoA", "rapid_delayed_rectifying_potassium_current", ALGEBRAIC}
};

double * createStatesArray()
{
    return malloc(STATE_COUNT*sizeof(double));
}

double * createVariablesArray()
{
    return malloc(VARIABLE_COUNT*sizeof(double));
}

void deleteArray(double *array)
{
    free(array);
}

void initialiseVariables(double *states, double *variables)
{
    variables[0] = 46.4;
    variables[1] = 0.0057938;
    variables[2] = 0.0082;
    variables[3] = 0.0058;
    variables[4] = 0.06588648;
    variables[5] = 0.0659;
    variables[6] = 0.0659;
    variables[7] = 45.0;
    variables[8] = 0.00427806;
    variables[9] = 0.0021;
    variables[10] = 0.0043;
    variables[11] = 0.0138823;
    variables[12] = 0.00694;
    variables[13] = 0.0139;
    variables[14] = 1.3236e-5;
    variables[15] = 1.323e-5;
    variables[16] = 1.32e-5;
    variables[17] = 4.2952e-5;
    variables[18] = 4.29e-5;
    variables[19] = 4.3e-5;
    variables[20] = 6.645504e-5;
    variables[21] = 0.000266;
    variables[22] = 6.65e-5;
    variables[23] = 0.01138376;
    variables[24] = 0.0114;
    variables[25] = 0.0114;
    variables[26] = 0.004905;
    variables[27] = 0.004905;
    variables[28] = 0.00491;
    variables[29] = 0.036495;
    variables[30] = 0.0365;
    variables[31] = 0.03649;
    variables[32] = 0.0005465;
    variables[33] = 0.000437;
    variables[34] = 0.000548;
    variables[35] = 0.006875;
    variables[36] = 0.0055;
    variables[37] = 0.0069;
    variables[38] = 0.0005465;
    variables[39] = 0.000437;
    variables[40] = 0.000548;
    variables[41] = 0.006875;
    variables[42] = 0.0055;
    variables[43] = 0.0069;
    variables[44] = 0.0001;
    variables[45] = 2.0;
    variables[46] = 140.0;
    variables[47] = 5.4;
    variables[48] = 8.0;
    variables[49] = 140.0;
    variables[50] = 2.0e-5;
    variables[51] = 6.5e-5;
    variables[52] = 96845.0;
    variables[53] = 1.0309347;
    variables[54] = 8314.0;
    variables[55] = 310.0;
    variables[56] = 1.0;
    variables[57] = 0.0;
    variables[58] = 0.0;
    variables[59] = 0.0042;
    variables[60] = 0.0;
    variables[61] = 0.0;
    variables[62] = 0.03339;
    variables[63] = 0.0;
    variables[64] = 2.523636e-5;
    variables[65] = 2.52e-5;
    variables[66] = 2.52e-5;
    variables[67] = 8.1892e-5;
    variables[68] = 8.19e-5;
    variables[69] = 8.19e-5;
    variables[70] = 0.00079704;
    variables[71] = 0.000738;
    variables[72] = 0.000797;
    variables[73] = 0.016;
    variables[74] = 0.0208;
    variables[75] = 0.016;
    variables[76] = 0.0003445;
    variables[77] = 0.000345;
    variables[78] = 0.000518;
    variables[79] = 0.0104;
    variables[80] = 0.0104;
    variables[81] = 0.0104;
    variables[82] = 5.81818e-5;
    variables[83] = 5.8e-5;
    variables[84] = 5.8e-5;
    variables[85] = 0.0001888;
    variables[86] = 0.000189;
    variables[87] = 0.000189;
    variables[88] = 0.0001;
    variables[89] = 0.5;
    variables[90] = 2.7229e-6;
    variables[91] = 2.8e-6;
    variables[92] = 2.7e-6;
    variables[93] = 8.83584e-6;
    variables[94] = 8.8e-6;
    variables[95] = 8.8e-6;
    variables[96] = 0.0;
    variables[97] = 0.0;
    variables[98] = 0.0;
    variables[99] = 1.204e-6;
    variables[100] = 3.7e-7;
    variables[101] = 1.2e-6;
    variables[102] = 0.621;
    variables[103] = 5.64;
    variables[104] = 0.04782545;
    variables[105] = 0.0478;
    variables[106] = 0.0478;
    variables[107] = 0.1551936;
    variables[108] = 0.16;
    variables[109] = 0.16;
    states[0] = 0.092361701692;
    states[1] = 0.015905380261;
    states[2] = 0.01445216109;
    states[3] = 0.04804900895;
    states[4] = 0.48779845203;
    states[5] = 0.42074047435;
    states[6] = 0.038968420558;
    states[7] = 0.29760539675;
    states[8] = 0.064402950262;
    states[9] = 0.13034201158;
    states[10] = 0.46960956028;
    states[11] = 0.87993375273;
    states[12] = 0.082293827208;
    states[13] = 0.03889291759;
    states[14] = -39.013558536;
}

void computeComputedConstants(double *variables)
{
    variables[110] = (variables[56] == 0.0)?1.07*(3.0*variables[57]-0.1)/(3.0*(1.0+0.7745*exp(-(3.0*variables[57]-2.05)/0.295))):(variables[56] == 1.0)?variables[53]*variables[57]/(1.0+0.7745*exp(-(3.0*variables[57]-2.05)/0.295)):1.07*29.0*variables[57]/(30.0*(1.0+0.7745*exp(-(29.0*variables[57]-24.5)/1.95)));
    variables[111] = variables[50]+variables[110]*(variables[51]-variables[50]);
    variables[112] = (variables[56] == 0.0)?variables[84]+variables[110]*(variables[87]-variables[84]):(variables[56] == 1.0)?variables[82]+variables[110]*(variables[85]-variables[82]):variables[83]+variables[110]*(variables[86]-variables[83]);
    variables[113] = (variables[56] == 0.0)?variables[66]+variables[110]*(variables[69]-variables[66]):(variables[56] == 1.0)?variables[64]+variables[110]*(variables[67]-variables[64]):variables[65]+variables[110]*(variables[68]-variables[65]);
    variables[114] = (variables[56] == 0.0)?variables[16]+variables[110]*(variables[19]-variables[16]):(variables[56] == 1.0)?variables[14]+variables[110]*(variables[17]-variables[14]):variables[15]+variables[110]*(variables[18]-variables[15]);
    variables[115] = (variables[56] == 0.0)?variables[92]+variables[110]*(variables[95]-variables[92]):(variables[56] == 1.0)?variables[90]+variables[110]*(variables[93]-variables[90]):variables[91]+variables[110]*(variables[94]-variables[91]);
    variables[117] = (variables[56] == 0.0)?variables[106]+variables[110]*(variables[109]-variables[106]):(variables[56] == 1.0)?variables[104]+variables[110]*(variables[107]-variables[104]):variables[105]+variables[110]*(variables[108]-variables[105]);
    variables[119] = (variables[56] == 0.0)?variables[60]+variables[110]*(variables[63]-variables[60]):(variables[56] == 1.0)?variables[58]+variables[110]*(variables[61]-variables[58]):variables[59]+variables[110]*(variables[62]-variables[59]);
    variables[120] = variables[119]*variables[44]/(variables[44]+0.0004);
    variables[121] = variables[54]*variables[55]/variables[52]*log(variables[49]/variables[48]);
    variables[122] = variables[54]*variables[55]/variables[52]*log(variables[47]/variables[46]);
    variables[123] = variables[54]*variables[55]/(2.0*variables[52])*log(variables[45]/variables[44]);
    variables[124] = (variables[56] == 0.0)?variables[54]*variables[55]/variables[52]*log((variables[47]+0.12*variables[49])/(variables[46]+0.12*variables[48])):variables[54]*variables[55]/variables[52]*log((variables[47]+0.03*variables[49])/(variables[46]+0.03*variables[48]));
    variables[125] = (variables[56] == 0.0)?variables[98]+variables[110]*(variables[101]-variables[98]):(variables[56] == 1.0)?variables[96]+variables[110]*(variables[99]-variables[96]):variables[97]+variables[110]*(variables[100]-variables[97]);
    variables[134] = (variables[56] == 0.0)?variables[3]+variables[110]*(variables[6]-variables[3]):(variables[56] == 1.0)?variables[1]+variables[110]*(variables[4]-variables[1]):variables[2]+variables[110]*(variables[5]-variables[2]);
    variables[144] = (variables[56] == 0.0)?variables[10]+variables[110]*(variables[13]-variables[10]):(variables[56] == 1.0)?variables[8]+variables[110]*(variables[11]-variables[8]):variables[9]+variables[110]*(variables[12]-variables[9]);
    variables[154] = (variables[56] == 0.0)?variables[28]+variables[110]*(variables[31]-variables[28]):(variables[56] == 1.0)?variables[26]+variables[110]*(variables[29]-variables[26]):variables[27]+variables[110]*(variables[30]-variables[27]);
    variables[155] = (variables[56] == 0.0)?variables[22]+variables[110]*(variables[25]-variables[22]):(variables[56] == 1.0)?variables[20]+variables[110]*(variables[23]-variables[20]):variables[21]+variables[110]*(variables[24]-variables[21]);
    variables[162] = (variables[56] == 0.0)?variables[72]+variables[110]*(variables[75]-variables[72]):(variables[56] == 1.0)?variables[70]+variables[110]*(variables[73]-variables[70]):variables[71]+variables[110]*(variables[74]-variables[71]);
    variables[168] = (variables[56] == 0.0)?0.002:(variables[56] == 1.0)?0.002:0.006;
    variables[170] = (variables[56] == 0.0)?variables[78]+variables[110]*(variables[81]-variables[78]):(variables[56] == 1.0)?variables[76]+variables[110]*(variables[79]-variables[76]):variables[77]+variables[110]*(variables[80]-variables[77]);
    variables[174] = (variables[56] == 0.0)?variables[40]+variables[110]*(variables[43]-variables[40]):(variables[56] == 1.0)?variables[38]+variables[110]*(variables[41]-variables[38]):variables[39]+variables[110]*(variables[42]-variables[39]);
    variables[176] = (variables[56] == 0.0)?variables[34]+variables[110]*(variables[37]-variables[34]):(variables[56] == 1.0)?variables[32]+variables[110]*(variables[35]-variables[32]):variables[33]+variables[110]*(variables[36]-variables[33]);
}

void computeRates(double voi, double *states, double *rates, double *variables)
{
    variables[126] = (variables[56] == 0.0)?pow(1.0/(1.0+exp(-states[14]/5.46)), 1.0/3.0):pow(1.0/(1.0+exp(-(states[14]+30.32)/5.46)), 1.0/3.0);
    variables[127] = (variables[56] == 0.0)?0.0006247/(0.832*exp(-0.335*(states[14]+56.7))+0.627*exp(0.082*(states[14]+65.01)))+4.0e-5:0.0006247/(0.8322166*exp(-0.33566*(states[14]+56.7062))+0.6274*exp(0.0823*(states[14]+65.0131)))+4.569e-5;
    rates[0] = (variables[126]-states[0])/variables[127];
    variables[130] = 1.0/(1.0+exp((states[14]+66.1)/6.4));
    variables[132] = 3.717e-6*exp(-0.2815*(states[14]+17.11))/(1.0+0.003732*exp(-0.3426*(states[14]+37.76)))+0.0005977;
    rates[1] = (variables[130]-states[1])/variables[132];
    variables[131] = variables[130];
    variables[133] = 3.186e-8*exp(-0.6219*(states[14]+18.8))/(1.0+7.189e-5*exp(-0.6683*(states[14]+34.07)))+0.003556;
    rates[2] = (variables[131]-states[2])/variables[133];
    variables[139] = (variables[56] == 0.0)?1.0/(1.0+exp(-(states[14]+23.1)/6.0)):(variables[56] == 1.0)?1.0/(1.0+exp(-(states[14]+22.3+0.8*variables[110])/6.0)):1.0/(1.0+exp(-(states[14]+22.2)/6.0));
    variables[136] = (variables[56] == 0.0)?-28.38*(states[14]+35.0)/(exp(-(states[14]+35.0)/2.5)-1.0)-84.9*states[14]/(exp(-0.208*states[14])-1.0):(variables[56] == 1.0)?-28.39*(states[14]+35.0)/(exp(-(states[14]+35.0)/2.5)-1.0)-84.9*states[14]/(exp(-0.208*states[14])-1.0):-28.4*(states[14]+35.0)/(exp(-(states[14]+35.0)/2.5)-1.0)-84.9*states[14]/(exp(-0.208*states[14])-1.0);
    variables[137] = (variables[56] == 1.0)?11.43*(states[14]-5.0)/(exp(0.4*(states[14]-5.0))-1.0):11.42*(states[14]-5.0)/(exp(0.4*(states[14]-5.0))-1.0);
    variables[138] = 2.0/(variables[136]+variables[137]);
    rates[3] = (variables[139]-states[3])/variables[138];
    variables[143] = 1.0/(1.0+exp((states[14]+45.0)/5.0));
    variables[140] = (variables[56] == 1.0)?3.75*(states[14]+28.0)/(exp((states[14]+28.0)/4.0)-1.0):3.12*(states[14]+28.0)/(exp((states[14]+28.0)/4.0)-1.0);
    variables[141] = (variables[56] == 1.0)?30.0/(1.0+exp(-(states[14]+28.0)/4.0)):25.0/(1.0+exp(-(states[14]+28.0)/4.0));
    variables[142] = (variables[56] == 1.0)?(1.2-0.2*variables[110])/(variables[140]+variables[141]):1.0/(variables[140]+variables[141]);
    rates[4] = (variables[143]-states[4])/variables[142];
    variables[149] = 1.0/(1.0+exp(-(states[14]+37.0)/6.8));
    variables[146] = 1068.0*exp((states[14]+26.3)/30.0);
    variables[147] = 1068.0*exp(-(states[14]+26.3)/30.0);
    variables[148] = 1.0/(variables[146]+variables[147]);
    rates[5] = (variables[149]-states[5])/variables[148];
    variables[153] = 1.0/(1.0+exp((states[14]+71.0)/9.0));
    variables[150] = (variables[56] == 1.0)?15.3*exp(-(states[14]+71.0+0.7*variables[110])/83.3):15.3*exp(-(states[14]+71.7)/83.3);
    variables[151] = (variables[56] == 1.0)?15.0*exp((states[14]+71.0)/15.38):15.0*exp((states[14]+71.7)/15.38);
    variables[152] = 1.0/(variables[150]+variables[151]);
    rates[6] = (variables[153]-states[6])/variables[152];
    variables[158] = 1.0/(1.0+exp((states[14]+59.37)/13.1));
    variables[159] = (variables[56] == 0.0)?0.0101+0.06517/(0.57*exp(-0.08*(states[14]+49.0)))+2.4e-5*exp(0.1*(states[14]+50.93)):(variables[56] == 1.0)?0.001/3.0*(30.31+195.5/(0.5686*exp(-0.08161*(states[14]+39.0+10.0*variables[110]))+0.7174*exp((0.2719-0.1719*variables[110])*1.0*(states[14]+40.93+10.0*variables[110])))):0.0101+0.06517/(0.5686*exp(-0.08161*(states[14]+39.0))+0.7174*exp(0.2719*(states[14]+40.93)));
    rates[7] = (variables[158]-states[7])/variables[159];
    variables[160] = 1.0/(1.0+exp(-(states[14]-10.93)/19.7));
    variables[161] = (variables[56] == 0.0)?0.001*(2.98+15.59/(1.037*exp(0.09*(states[14]+30.61))+0.369*exp(-0.12*(states[14]+23.84)))):(variables[56] == 1.0)?0.0025*(1.191+7.838/(1.037*exp(0.09012*(states[14]+30.61))+0.369*exp(-0.119*(states[14]+23.84)))):0.001*(2.98+19.59/(1.037*exp(0.09012*(states[14]+30.61))+0.369*exp(-0.119*(states[14]+23.84))));
    rates[8] = (variables[160]-states[8])/variables[161];
    variables[164] = (variables[56] != 2.0)?1.0/(1.0+exp(-(states[14]+14.2)/10.6)):1.0/(1.0+exp(-(states[14]+13.2)/10.6));
    variables[165] = (variables[56] != 2.0)?1.0/(37.2*exp((states[14]-9.0)/15.9)+0.96*exp(-(states[14]-9.0)/22.5)):1.0/(37.2*exp((states[14]-10.0)/15.9)+0.96*exp(-(states[14]-10.0)/22.5));
    rates[9] = (variables[164]-states[9])/variables[165];
    variables[166] = variables[164];
    variables[167] = (variables[56] != 2.0)?1.0/(4.2*exp((states[14]-9.0)/17.0)+0.15*exp(-(states[14]-9.0)/21.6)):1.0/(4.2*exp((states[14]-10.0)/17.0)+0.15*exp(-(states[14]-10.0)/21.6));
    rates[10] = (variables[166]-states[10])/variables[167];
    variables[169] = 1.0/(1.0+exp((states[14]+18.6)/10.1));
    rates[11] = (variables[169]-states[11])/variables[168];
    variables[172] = 14.0/(1.0+exp(-(states[14]-40.0)/9.0));
    variables[173] = 1.0*exp(-states[14]/45.0);
    rates[12] = variables[172]*(1.0-states[12])-variables[173]*states[12];
    variables[178] = (variables[56] == 0.0)?1.0*exp(-(states[14]+78.91)/26.62):1.0*exp(-(states[14]+78.91)/26.63);
    variables[179] = 1.0*exp((states[14]+75.13)/21.25);
    rates[13] = variables[178]*(1.0-states[13])-variables[179]*states[13];
    variables[118] = variables[117]*pow(variables[48]/(variables[103]+variables[48]), 3.0)*pow(variables[47]/(variables[102]+variables[47]), 2.0)*1.6/(1.5+exp(-(states[14]+60.0)/40.0));
    variables[116] = (variables[56] == 0.0)?variables[115]*(pow(variables[48], 3.0)*variables[45]*exp(0.03743*states[14]*variables[89])-pow(variables[49], 3.0)*variables[44]*exp(0.0374*states[14]*(variables[89]-1.0)))/(1.0+variables[88]*(variables[44]*pow(variables[49], 3.0)+variables[45]*pow(variables[48], 3.0))):variables[115]*(pow(variables[48], 3.0)*variables[45]*exp(0.03743*states[14]*variables[89])-pow(variables[49], 3.0)*variables[44]*exp(0.03743*states[14]*(variables[89]-1.0)))/(1.0+variables[88]*(variables[44]*pow(variables[49], 3.0)+variables[45]*pow(variables[48], 3.0)));
    variables[177] = (variables[56] != 2.0)?variables[176]*states[13]*(states[14]-variables[122]):variables[176]*states[13]*(states[14]+102.0);
    variables[175] = (variables[56] != 2.0)?variables[174]*states[13]*(states[14]-variables[121]):variables[174]*states[13]*(states[14]-77.6);
    variables[171] = variables[170]*pow(states[12], 2.0)*(states[14]-variables[124]);
    variables[157] = variables[155]*states[8]*(states[14]-variables[122]);
    variables[156] = variables[154]*states[7]*states[8]*(states[14]-variables[122]);
    variables[145] = variables[144]*states[5]*states[6]*(states[14]-variables[7]);
    variables[135] = variables[134]*(states[4]*states[3]+0.006/(1.0+exp(-(states[14]+14.1)/6.0)))*(states[14]-variables[0]);
    variables[128] = (variables[56] == 0.0)?0.0952*exp(-0.063*(states[14]+34.4))/(1.0+1.66*exp(-0.225*(states[14]+63.7)))+0.0869:0.09518*exp(-0.06306*(states[14]+34.4))/(1.0+1.662*exp(-0.2251*(states[14]+63.7)))+0.08693;
    variables[129] = (1.0-variables[128])*states[1]+variables[128]*states[2];
    variables[183] = variables[125]*pow(states[0], 3.0)*variables[129]*variables[49]*pow(variables[52], 2.0)/(variables[54]*variables[55])*(exp((states[14]-variables[121])*variables[52]/(variables[54]*variables[55]))-1.0)/(exp(states[14]*variables[52]/(variables[54]*variables[55]))-1.0)*states[14];
    variables[181] = variables[113]*(states[14]-variables[122]);
    variables[182] = variables[114]*(states[14]-variables[123]);
    variables[180] = variables[112]*(states[14]-variables[121]);
    variables[163] = 0.6*states[9]+0.4*states[10];
    variables[184] = variables[162]*variables[163]*states[11]*(states[14]-variables[122]);
    rates[14] = -1.0/variables[111]*(variables[183]+variables[135]+variables[145]+variables[156]+variables[157]+variables[184]+variables[171]+variables[175]+variables[177]+variables[180]+variables[182]+variables[181]+variables[116]+variables[118]+variables[120]);
}

void computeVariables(double voi, double *states, double *rates, double *variables)
{
    variables[116] = (variables[56] == 0.0)?variables[115]*(pow(variables[48], 3.0)*variables[45]*exp(0.03743*states[14]*variables[89])-pow(variables[49], 3.0)*variables[44]*exp(0.0374*states[14]*(variables[89]-1.0)))/(1.0+variables[88]*(variables[44]*pow(variables[49], 3.0)+variables[45]*pow(variables[48], 3.0))):variables[115]*(pow(variables[48], 3.0)*variables[45]*exp(0.03743*states[14]*variables[89])-pow(variables[49], 3.0)*variables[44]*exp(0.03743*states[14]*(variables[89]-1.0)))/(1.0+variables[88]*(variables[44]*pow(variables[49], 3.0)+variables[45]*pow(variables[48], 3.0)));
    variables[118] = variables[117]*pow(variables[48]/(variables[103]+variables[48]), 3.0)*pow(variables[47]/(variables[102]+variables[47]), 2.0)*1.6/(1.5+exp(-(states[14]+60.0)/40.0));
    variables[126] = (variables[56] == 0.0)?pow(1.0/(1.0+exp(-states[14]/5.46)), 1.0/3.0):pow(1.0/(1.0+exp(-(states[14]+30.32)/5.46)), 1.0/3.0);
    variables[127] = (variables[56] == 0.0)?0.0006247/(0.832*exp(-0.335*(states[14]+56.7))+0.627*exp(0.082*(states[14]+65.01)))+4.0e-5:0.0006247/(0.8322166*exp(-0.33566*(states[14]+56.7062))+0.6274*exp(0.0823*(states[14]+65.0131)))+4.569e-5;
    variables[128] = (variables[56] == 0.0)?0.0952*exp(-0.063*(states[14]+34.4))/(1.0+1.66*exp(-0.225*(states[14]+63.7)))+0.0869:0.09518*exp(-0.06306*(states[14]+34.4))/(1.0+1.662*exp(-0.2251*(states[14]+63.7)))+0.08693;
    variables[129] = (1.0-variables[128])*states[1]+variables[128]*states[2];
    variables[130] = 1.0/(1.0+exp((states[14]+66.1)/6.4));
    variables[131] = variables[130];
    variables[132] = 3.717e-6*exp(-0.2815*(states[14]+17.11))/(1.0+0.003732*exp(-0.3426*(states[14]+37.76)))+0.0005977;
    variables[133] = 3.186e-8*exp(-0.6219*(states[14]+18.8))/(1.0+7.189e-5*exp(-0.6683*(states[14]+34.07)))+0.003556;
    variables[135] = variables[134]*(states[4]*states[3]+0.006/(1.0+exp(-(states[14]+14.1)/6.0)))*(states[14]-variables[0]);
    variables[136] = (variables[56] == 0.0)?-28.38*(states[14]+35.0)/(exp(-(states[14]+35.0)/2.5)-1.0)-84.9*states[14]/(exp(-0.208*states[14])-1.0):(variables[56] == 1.0)?-28.39*(states[14]+35.0)/(exp(-(states[14]+35.0)/2.5)-1.0)-84.9*states[14]/(exp(-0.208*states[14])-1.0):-28.4*(states[14]+35.0)/(exp(-(states[14]+35.0)/2.5)-1.0)-84.9*states[14]/(exp(-0.208*states[14])-1.0);
    variables[137] = (variables[56] == 1.0)?11.43*(states[14]-5.0)/(exp(0.4*(states[14]-5.0))-1.0):11.42*(states[14]-5.0)/(exp(0.4*(states[14]-5.0))-1.0);
    variables[138] = 2.0/(variables[136]+variables[137]);
    variables[139] = (variables[56] == 0.0)?1.0/(1.0+exp(-(states[14]+23.1)/6.0)):(variables[56] == 1.0)?1.0/(1.0+exp(-(states[14]+22.3+0.8*variables[110])/6.0)):1.0/(1.0+exp(-(states[14]+22.2)/6.0));
    variables[140] = (variables[56] == 1.0)?3.75*(states[14]+28.0)/(exp((states[14]+28.0)/4.0)-1.0):3.12*(states[14]+28.0)/(exp((states[14]+28.0)/4.0)-1.0);
    variables[141] = (variables[56] == 1.0)?30.0/(1.0+exp(-(states[14]+28.0)/4.0)):25.0/(1.0+exp(-(states[14]+28.0)/4.0));
    variables[142] = (variables[56] == 1.0)?(1.2-0.2*variables[110])/(variables[140]+variables[141]):1.0/(variables[140]+variables[141]);
    variables[143] = 1.0/(1.0+exp((states[14]+45.0)/5.0));
    variables[145] = variables[144]*states[5]*states[6]*(states[14]-variables[7]);
    variables[146] = 1068.0*exp((states[14]+26.3)/30.0);
    variables[147] = 1068.0*exp(-(states[14]+26.3)/30.0);
    variables[148] = 1.0/(variables[146]+variables[147]);
    variables[149] = 1.0/(1.0+exp(-(states[14]+37.0)/6.8));
    variables[150] = (variables[56] == 1.0)?15.3*exp(-(states[14]+71.0+0.7*variables[110])/83.3):15.3*exp(-(states[14]+71.7)/83.3);
    variables[151] = (variables[56] == 1.0)?15.0*exp((states[14]+71.0)/15.38):15.0*exp((states[14]+71.7)/15.38);
    variables[152] = 1.0/(variables[150]+variables[151]);
    variables[153] = 1.0/(1.0+exp((states[14]+71.0)/9.0));
    variables[156] = variables[154]*states[7]*states[8]*(states[14]-variables[122]);
    variables[157] = variables[155]*states[8]*(states[14]-variables[122]);
    variables[158] = 1.0/(1.0+exp((states[14]+59.37)/13.1));
    variables[159] = (variables[56] == 0.0)?0.0101+0.06517/(0.57*exp(-0.08*(states[14]+49.0)))+2.4e-5*exp(0.1*(states[14]+50.93)):(variables[56] == 1.0)?0.001/3.0*(30.31+195.5/(0.5686*exp(-0.08161*(states[14]+39.0+10.0*variables[110]))+0.7174*exp((0.2719-0.1719*variables[110])*1.0*(states[14]+40.93+10.0*variables[110])))):0.0101+0.06517/(0.5686*exp(-0.08161*(states[14]+39.0))+0.7174*exp(0.2719*(states[14]+40.93)));
    variables[160] = 1.0/(1.0+exp(-(states[14]-10.93)/19.7));
    variables[161] = (variables[56] == 0.0)?0.001*(2.98+15.59/(1.037*exp(0.09*(states[14]+30.61))+0.369*exp(-0.12*(states[14]+23.84)))):(variables[56] == 1.0)?0.0025*(1.191+7.838/(1.037*exp(0.09012*(states[14]+30.61))+0.369*exp(-0.119*(states[14]+23.84)))):0.001*(2.98+19.59/(1.037*exp(0.09012*(states[14]+30.61))+0.369*exp(-0.119*(states[14]+23.84))));
    variables[163] = 0.6*states[9]+0.4*states[10];
    variables[164] = (variables[56] != 2.0)?1.0/(1.0+exp(-(states[14]+14.2)/10.6)):1.0/(1.0+exp(-(states[14]+13.2)/10.6));
    variables[165] = (variables[56] != 2.0)?1.0/(37.2*exp((states[14]-9.0)/15.9)+0.96*exp(-(states[14]-9.0)/22.5)):1.0/(37.2*exp((states[14]-10.0)/15.9)+0.96*exp(-(states[14]-10.0)/22.5));
    variables[166] = variables[164];
    variables[167] = (variables[56] != 2.0)?1.0/(4.2*exp((states[14]-9.0)/17.0)+0.15*exp(-(states[14]-9.0)/21.6)):1.0/(4.2*exp((states[14]-10.0)/17.0)+0.15*exp(-(states[14]-10.0)/21.6));
    variables[169] = 1.0/(1.0+exp((states[14]+18.6)/10.1));
    variables[171] = variables[170]*pow(states[12], 2.0)*(states[14]-variables[124]);
    variables[172] = 14.0/(1.0+exp(-(states[14]-40.0)/9.0));
    variables[173] = 1.0*exp(-states[14]/45.0);
    variables[175] = (variables[56] != 2.0)?variables[174]*states[13]*(states[14]-variables[121]):variables[174]*states[13]*(states[14]-77.6);
    variables[177] = (variables[56] != 2.0)?variables[176]*states[13]*(states[14]-variables[122]):variables[176]*states[13]*(states[14]+102.0);
    variables[178] = (variables[56] == 0.0)?1.0*exp(-(states[14]+78.91)/26.62):1.0*exp(-(states[14]+78.91)/26.63);
    variables[179] = 1.0*exp((states[14]+75.13)/21.25);
    variables[180] = variables[112]*(states[14]-variables[121]);
    variables[181] = variables[113]*(states[14]-variables[122]);
    variables[182] = variables[114]*(states[14]-variables[123]);
    variables[183] = variables[125]*pow(states[0], 3.0)*variables[129]*variables[49]*pow(variables[52], 2.0)/(variables[54]*variables[55])*(exp((states[14]-variables[121])*variables[52]/(variables[54]*variables[55]))-1.0)/(exp(states[14]*variables[52]/(variables[54]*variables[55]))-1.0)*states[14];
    variables[184] = variables[162]*variables[163]*states[11]*(states[14]-variables[122]);
}

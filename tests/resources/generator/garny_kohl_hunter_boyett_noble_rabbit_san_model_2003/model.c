/* The content of this file was generated using the C profile of libCellML 0.5.0. */

#include "model.h"

#include <math.h>
#include <stdlib.h>

const char VERSION[] = "0.6.0";
const char LIBCELLML_VERSION[] = "0.5.0";

const size_t STATE_COUNT = 15;
const size_t CONSTANT_COUNT = 0;
const size_t COMPUTED_CONSTANT_COUNT = 0;
const size_t ALGEBRAIC_COUNT = 185;

const VariableInfo VOI_INFO = {"time", "second", "environment", VARIABLE_OF_INTEGRATION};

const VariableInfo STATE_INFO[] = {
    {"V", "millivolt", "membrane", STATE},
    {"m", "dimensionless", "sodium_current_m_gate", STATE},
    {"h1", "dimensionless", "sodium_current_h_gate", STATE},
    {"h2", "dimensionless", "sodium_current_h_gate", STATE},
    {"f_L", "dimensionless", "L_type_Ca_channel_f_gate", STATE},
    {"d_L", "dimensionless", "L_type_Ca_channel_d_gate", STATE},
    {"f_T", "dimensionless", "T_type_Ca_channel_f_gate", STATE},
    {"d_T", "dimensionless", "T_type_Ca_channel_d_gate", STATE},
    {"r", "dimensionless", "four_AP_sensitive_currents_r_gate", STATE},
    {"q", "dimensionless", "four_AP_sensitive_currents_q_gate", STATE},
    {"P_i", "dimensionless", "rapid_delayed_rectifying_potassium_current_P_i_gate", STATE},
    {"P_af", "dimensionless", "rapid_delayed_rectifying_potassium_current_P_af_gate", STATE},
    {"P_as", "dimensionless", "rapid_delayed_rectifying_potassium_current_P_as_gate", STATE},
    {"xs", "dimensionless", "slow_delayed_rectifying_potassium_current_xs_gate", STATE},
    {"y", "dimensionless", "hyperpolarisation_activated_current_y_gate", STATE}
};

const VariableInfo VARIABLE_INFO[] = {
    {"FCell", "dimensionless", "membrane", COMPUTED_CONSTANT},
    {"dCell", "dimensionless", "membrane", CONSTANT},
    {"Version", "dimensionless", "membrane", CONSTANT},
    {"FCellConstant", "dimensionless", "membrane", CONSTANT},
    {"Cm", "microF", "membrane", COMPUTED_CONSTANT},
    {"CmCentre", "microF", "membrane", CONSTANT},
    {"CmPeriphery", "microF", "membrane", CONSTANT},
    {"i_Na", "nanoA", "sodium_current", ALGEBRAIC},
    {"i_Ca_p", "nanoA", "persistent_calcium_current", COMPUTED_CONSTANT},
    {"i_p", "nanoA", "sodium_potassium_pump", ALGEBRAIC},
    {"i_NaCa", "nanoA", "sodium_calcium_exchanger", ALGEBRAIC},
    {"i_b_K", "nanoA", "potassium_background_current", ALGEBRAIC},
    {"i_b_Ca", "nanoA", "calcium_background_current", ALGEBRAIC},
    {"i_b_Na", "nanoA", "sodium_background_current", ALGEBRAIC},
    {"i_f_K", "nanoA", "hyperpolarisation_activated_current", ALGEBRAIC},
    {"i_f_Na", "nanoA", "hyperpolarisation_activated_current", ALGEBRAIC},
    {"i_K_s", "nanoA", "slow_delayed_rectifying_potassium_current", ALGEBRAIC},
    {"i_K_r", "nanoA", "rapid_delayed_rectifying_potassium_current", ALGEBRAIC},
    {"i_sus", "nanoA", "four_AP_sensitive_currents", ALGEBRAIC},
    {"i_to", "nanoA", "four_AP_sensitive_currents", ALGEBRAIC},
    {"i_Ca_T", "nanoA", "T_type_Ca_channel", ALGEBRAIC},
    {"i_Ca_L", "nanoA", "L_type_Ca_channel", ALGEBRAIC},
    {"R", "millijoule_per_mole_kelvin", "membrane", CONSTANT},
    {"T", "kelvin", "membrane", CONSTANT},
    {"F", "coulomb_per_mole", "membrane", CONSTANT},
    {"g_b_Na", "microS", "sodium_background_current", COMPUTED_CONSTANT},
    {"g_b_Na_Centre_Published", "microS", "sodium_background_current", CONSTANT},
    {"g_b_Na_Periphery_Published", "microS", "sodium_background_current", CONSTANT},
    {"g_b_Na_Centre_1DCapable", "microS", "sodium_background_current", CONSTANT},
    {"g_b_Na_Periphery_1DCapable", "microS", "sodium_background_current", CONSTANT},
    {"g_b_Na_Centre_0DCapable", "microS", "sodium_background_current", CONSTANT},
    {"g_b_Na_Periphery_0DCapable", "microS", "sodium_background_current", CONSTANT},
    {"E_Na", "millivolt", "reversal_and_equilibrium_potentials", COMPUTED_CONSTANT},
    {"g_b_K", "microS", "potassium_background_current", COMPUTED_CONSTANT},
    {"g_b_K_Centre_Published", "microS", "potassium_background_current", CONSTANT},
    {"g_b_K_Periphery_Published", "microS", "potassium_background_current", CONSTANT},
    {"g_b_K_Centre_1DCapable", "microS", "potassium_background_current", CONSTANT},
    {"g_b_K_Periphery_1DCapable", "microS", "potassium_background_current", CONSTANT},
    {"g_b_K_Centre_0DCapable", "microS", "potassium_background_current", CONSTANT},
    {"g_b_K_Periphery_0DCapable", "microS", "potassium_background_current", CONSTANT},
    {"E_K", "millivolt", "reversal_and_equilibrium_potentials", COMPUTED_CONSTANT},
    {"g_b_Ca", "microS", "calcium_background_current", COMPUTED_CONSTANT},
    {"g_b_Ca_Centre_Published", "microS", "calcium_background_current", CONSTANT},
    {"g_b_Ca_Periphery_Published", "microS", "calcium_background_current", CONSTANT},
    {"g_b_Ca_Centre_1DCapable", "microS", "calcium_background_current", CONSTANT},
    {"g_b_Ca_Periphery_1DCapable", "microS", "calcium_background_current", CONSTANT},
    {"g_b_Ca_Centre_0DCapable", "microS", "calcium_background_current", CONSTANT},
    {"g_b_Ca_Periphery_0DCapable", "microS", "calcium_background_current", CONSTANT},
    {"E_Ca", "millivolt", "reversal_and_equilibrium_potentials", COMPUTED_CONSTANT},
    {"k_NaCa", "nanoA", "sodium_calcium_exchanger", COMPUTED_CONSTANT},
    {"k_NaCa_Centre_Published", "nanoA", "sodium_calcium_exchanger", CONSTANT},
    {"k_NaCa_Periphery_Published", "nanoA", "sodium_calcium_exchanger", CONSTANT},
    {"k_NaCa_Centre_1DCapable", "nanoA", "sodium_calcium_exchanger", CONSTANT},
    {"k_NaCa_Periphery_1DCapable", "nanoA", "sodium_calcium_exchanger", CONSTANT},
    {"k_NaCa_Centre_0DCapable", "nanoA", "sodium_calcium_exchanger", CONSTANT},
    {"k_NaCa_Periphery_0DCapable", "nanoA", "sodium_calcium_exchanger", CONSTANT},
    {"Na_i", "millimolar", "ionic_concentrations", CONSTANT},
    {"gamma_NaCa", "dimensionless", "sodium_calcium_exchanger", CONSTANT},
    {"Ca_o", "millimolar", "ionic_concentrations", CONSTANT},
    {"Na_o", "millimolar", "ionic_concentrations", CONSTANT},
    {"Ca_i", "millimolar", "ionic_concentrations", CONSTANT},
    {"d_NaCa", "dimensionless", "sodium_calcium_exchanger", CONSTANT},
    {"i_p_max", "nanoA", "sodium_potassium_pump", COMPUTED_CONSTANT},
    {"i_p_max_Centre_Published", "nanoA", "sodium_potassium_pump", CONSTANT},
    {"i_p_max_Periphery_Published", "nanoA", "sodium_potassium_pump", CONSTANT},
    {"i_p_max_Centre_1DCapable", "nanoA", "sodium_potassium_pump", CONSTANT},
    {"i_p_max_Periphery_1DCapable", "nanoA", "sodium_potassium_pump", CONSTANT},
    {"i_p_max_Centre_0DCapable", "nanoA", "sodium_potassium_pump", CONSTANT},
    {"i_p_max_Periphery_0DCapable", "nanoA", "sodium_potassium_pump", CONSTANT},
    {"K_o", "millimolar", "ionic_concentrations", CONSTANT},
    {"K_m_K", "millimolar", "sodium_potassium_pump", CONSTANT},
    {"K_m_Na", "millimolar", "sodium_potassium_pump", CONSTANT},
    {"i_Ca_p_max", "nanoA", "persistent_calcium_current", COMPUTED_CONSTANT},
    {"i_Ca_p_max_Centre_Published", "nanoA", "persistent_calcium_current", CONSTANT},
    {"i_Ca_p_max_Periphery_Published", "nanoA", "persistent_calcium_current", CONSTANT},
    {"i_Ca_p_max_Centre_1DCapable", "nanoA", "persistent_calcium_current", CONSTANT},
    {"i_Ca_p_max_Periphery_1DCapable", "nanoA", "persistent_calcium_current", CONSTANT},
    {"i_Ca_p_max_Centre_0DCapable", "nanoA", "persistent_calcium_current", CONSTANT},
    {"i_Ca_p_max_Periphery_0DCapable", "nanoA", "persistent_calcium_current", CONSTANT},
    {"K_i", "millimolar", "ionic_concentrations", CONSTANT},
    {"E_K_s", "millivolt", "reversal_and_equilibrium_potentials", COMPUTED_CONSTANT},
    {"g_Na", "microlitre_per_second", "sodium_current", COMPUTED_CONSTANT},
    {"g_Na_Centre_Published", "microlitre_per_second", "sodium_current", CONSTANT},
    {"g_Na_Periphery_Published", "microlitre_per_second", "sodium_current", CONSTANT},
    {"g_Na_Centre_1DCapable", "microlitre_per_second", "sodium_current", CONSTANT},
    {"g_Na_Periphery_1DCapable", "microlitre_per_second", "sodium_current", CONSTANT},
    {"g_Na_Centre_0DCapable", "microlitre_per_second", "sodium_current", CONSTANT},
    {"g_Na_Periphery_0DCapable", "microlitre_per_second", "sodium_current", CONSTANT},
    {"h", "dimensionless", "sodium_current_h_gate", ALGEBRAIC},
    {"m_infinity", "dimensionless", "sodium_current_m_gate", ALGEBRAIC},
    {"tau_m", "second", "sodium_current_m_gate", ALGEBRAIC},
    {"F_Na", "dimensionless", "sodium_current_h_gate", ALGEBRAIC},
    {"h1_infinity", "dimensionless", "sodium_current_h_gate", ALGEBRAIC},
    {"tau_h1", "second", "sodium_current_h_gate", ALGEBRAIC},
    {"h2_infinity", "dimensionless", "sodium_current_h_gate", ALGEBRAIC},
    {"tau_h2", "second", "sodium_current_h_gate", ALGEBRAIC},
    {"g_Ca_L", "microS", "L_type_Ca_channel", COMPUTED_CONSTANT},
    {"g_Ca_L_Centre_Published", "microS", "L_type_Ca_channel", CONSTANT},
    {"g_Ca_L_Periphery_Published", "microS", "L_type_Ca_channel", CONSTANT},
    {"g_Ca_L_Centre_1DCapable", "microS", "L_type_Ca_channel", CONSTANT},
    {"g_Ca_L_Periphery_1DCapable", "microS", "L_type_Ca_channel", CONSTANT},
    {"g_Ca_L_Centre_0DCapable", "microS", "L_type_Ca_channel", CONSTANT},
    {"g_Ca_L_Periphery_0DCapable", "microS", "L_type_Ca_channel", CONSTANT},
    {"E_Ca_L", "millivolt", "L_type_Ca_channel", CONSTANT},
    {"d_L_infinity", "dimensionless", "L_type_Ca_channel_d_gate", ALGEBRAIC},
    {"tau_d_L", "second", "L_type_Ca_channel_d_gate", ALGEBRAIC},
    {"alpha_d_L", "per_second", "L_type_Ca_channel_d_gate", ALGEBRAIC},
    {"beta_d_L", "per_second", "L_type_Ca_channel_d_gate", ALGEBRAIC},
    {"f_L_infinity", "dimensionless", "L_type_Ca_channel_f_gate", ALGEBRAIC},
    {"tau_f_L", "second", "L_type_Ca_channel_f_gate", ALGEBRAIC},
    {"alpha_f_L", "per_second", "L_type_Ca_channel_f_gate", ALGEBRAIC},
    {"beta_f_L", "per_second", "L_type_Ca_channel_f_gate", ALGEBRAIC},
    {"g_Ca_T", "microS", "T_type_Ca_channel", COMPUTED_CONSTANT},
    {"g_Ca_T_Centre_Published", "microS", "T_type_Ca_channel", CONSTANT},
    {"g_Ca_T_Periphery_Published", "microS", "T_type_Ca_channel", CONSTANT},
    {"g_Ca_T_Centre_1DCapable", "microS", "T_type_Ca_channel", CONSTANT},
    {"g_Ca_T_Periphery_1DCapable", "microS", "T_type_Ca_channel", CONSTANT},
    {"g_Ca_T_Centre_0DCapable", "microS", "T_type_Ca_channel", CONSTANT},
    {"g_Ca_T_Periphery_0DCapable", "microS", "T_type_Ca_channel", CONSTANT},
    {"E_Ca_T", "millivolt", "T_type_Ca_channel", CONSTANT},
    {"d_T_infinity", "dimensionless", "T_type_Ca_channel_d_gate", ALGEBRAIC},
    {"tau_d_T", "second", "T_type_Ca_channel_d_gate", ALGEBRAIC},
    {"alpha_d_T", "per_second", "T_type_Ca_channel_d_gate", ALGEBRAIC},
    {"beta_d_T", "per_second", "T_type_Ca_channel_d_gate", ALGEBRAIC},
    {"f_T_infinity", "dimensionless", "T_type_Ca_channel_f_gate", ALGEBRAIC},
    {"tau_f_T", "second", "T_type_Ca_channel_f_gate", ALGEBRAIC},
    {"alpha_f_T", "per_second", "T_type_Ca_channel_f_gate", ALGEBRAIC},
    {"beta_f_T", "per_second", "T_type_Ca_channel_f_gate", ALGEBRAIC},
    {"g_to", "microS", "four_AP_sensitive_currents", COMPUTED_CONSTANT},
    {"g_to_Centre_Published", "microS", "four_AP_sensitive_currents", CONSTANT},
    {"g_to_Periphery_Published", "microS", "four_AP_sensitive_currents", CONSTANT},
    {"g_to_Centre_1DCapable", "microS", "four_AP_sensitive_currents", CONSTANT},
    {"g_to_Periphery_1DCapable", "microS", "four_AP_sensitive_currents", CONSTANT},
    {"g_to_Centre_0DCapable", "microS", "four_AP_sensitive_currents", CONSTANT},
    {"g_to_Periphery_0DCapable", "microS", "four_AP_sensitive_currents", CONSTANT},
    {"g_sus", "microS", "four_AP_sensitive_currents", COMPUTED_CONSTANT},
    {"g_sus_Centre_Published", "microS", "four_AP_sensitive_currents", CONSTANT},
    {"g_sus_Periphery_Published", "microS", "four_AP_sensitive_currents", CONSTANT},
    {"g_sus_Centre_1DCapable", "microS", "four_AP_sensitive_currents", CONSTANT},
    {"g_sus_Periphery_1DCapable", "microS", "four_AP_sensitive_currents", CONSTANT},
    {"g_sus_Centre_0DCapable", "microS", "four_AP_sensitive_currents", CONSTANT},
    {"g_sus_Periphery_0DCapable", "microS", "four_AP_sensitive_currents", CONSTANT},
    {"q_infinity", "dimensionless", "four_AP_sensitive_currents_q_gate", ALGEBRAIC},
    {"tau_q", "second", "four_AP_sensitive_currents_q_gate", ALGEBRAIC},
    {"r_infinity", "dimensionless", "four_AP_sensitive_currents_r_gate", ALGEBRAIC},
    {"tau_r", "second", "four_AP_sensitive_currents_r_gate", ALGEBRAIC},
    {"g_K_r", "microS", "rapid_delayed_rectifying_potassium_current", COMPUTED_CONSTANT},
    {"g_K_r_Centre_Published", "microS", "rapid_delayed_rectifying_potassium_current", CONSTANT},
    {"g_K_r_Periphery_Published", "microS", "rapid_delayed_rectifying_potassium_current", CONSTANT},
    {"g_K_r_Centre_1DCapable", "microS", "rapid_delayed_rectifying_potassium_current", CONSTANT},
    {"g_K_r_Periphery_1DCapable", "microS", "rapid_delayed_rectifying_potassium_current", CONSTANT},
    {"g_K_r_Centre_0DCapable", "microS", "rapid_delayed_rectifying_potassium_current", CONSTANT},
    {"g_K_r_Periphery_0DCapable", "microS", "rapid_delayed_rectifying_potassium_current", CONSTANT},
    {"P_a", "dimensionless", "rapid_delayed_rectifying_potassium_current", ALGEBRAIC},
    {"P_af_infinity", "dimensionless", "rapid_delayed_rectifying_potassium_current_P_af_gate", ALGEBRAIC},
    {"tau_P_af", "second", "rapid_delayed_rectifying_potassium_current_P_af_gate", ALGEBRAIC},
    {"P_as_infinity", "dimensionless", "rapid_delayed_rectifying_potassium_current_P_as_gate", ALGEBRAIC},
    {"tau_P_as", "second", "rapid_delayed_rectifying_potassium_current_P_as_gate", ALGEBRAIC},
    {"tau_P_i", "second", "rapid_delayed_rectifying_potassium_current_P_i_gate", COMPUTED_CONSTANT},
    {"P_i_infinity", "dimensionless", "rapid_delayed_rectifying_potassium_current_P_i_gate", ALGEBRAIC},
    {"g_K_s", "microS", "slow_delayed_rectifying_potassium_current", COMPUTED_CONSTANT},
    {"g_K_s_Centre_Published", "microS", "slow_delayed_rectifying_potassium_current", CONSTANT},
    {"g_K_s_Periphery_Published", "microS", "slow_delayed_rectifying_potassium_current", CONSTANT},
    {"g_K_s_Centre_1DCapable", "microS", "slow_delayed_rectifying_potassium_current", CONSTANT},
    {"g_K_s_Periphery_1DCapable", "microS", "slow_delayed_rectifying_potassium_current", CONSTANT},
    {"g_K_s_Centre_0DCapable", "microS", "slow_delayed_rectifying_potassium_current", CONSTANT},
    {"g_K_s_Periphery_0DCapable", "microS", "slow_delayed_rectifying_potassium_current", CONSTANT},
    {"alpha_xs", "per_second", "slow_delayed_rectifying_potassium_current_xs_gate", ALGEBRAIC},
    {"beta_xs", "per_second", "slow_delayed_rectifying_potassium_current_xs_gate", ALGEBRAIC},
    {"g_f_Na", "microS", "hyperpolarisation_activated_current", COMPUTED_CONSTANT},
    {"g_f_Na_Centre_Published", "microS", "hyperpolarisation_activated_current", CONSTANT},
    {"g_f_Na_Periphery_Published", "microS", "hyperpolarisation_activated_current", CONSTANT},
    {"g_f_Na_Centre_1DCapable", "microS", "hyperpolarisation_activated_current", CONSTANT},
    {"g_f_Na_Periphery_1DCapable", "microS", "hyperpolarisation_activated_current", CONSTANT},
    {"g_f_Na_Centre_0DCapable", "microS", "hyperpolarisation_activated_current", CONSTANT},
    {"g_f_Na_Periphery_0DCapable", "microS", "hyperpolarisation_activated_current", CONSTANT},
    {"g_f_K", "microS", "hyperpolarisation_activated_current", COMPUTED_CONSTANT},
    {"g_f_K_Centre_Published", "microS", "hyperpolarisation_activated_current", CONSTANT},
    {"g_f_K_Periphery_Published", "microS", "hyperpolarisation_activated_current", CONSTANT},
    {"g_f_K_Centre_1DCapable", "microS", "hyperpolarisation_activated_current", CONSTANT},
    {"g_f_K_Periphery_1DCapable", "microS", "hyperpolarisation_activated_current", CONSTANT},
    {"g_f_K_Centre_0DCapable", "microS", "hyperpolarisation_activated_current", CONSTANT},
    {"g_f_K_Periphery_0DCapable", "microS", "hyperpolarisation_activated_current", CONSTANT},
    {"alpha_y", "per_second", "hyperpolarisation_activated_current_y_gate", ALGEBRAIC},
    {"beta_y", "per_second", "hyperpolarisation_activated_current_y_gate", ALGEBRAIC}
};

double * createStatesArray()
{
    double *res = (double *) malloc(STATE_COUNT*sizeof(double));

    for (size_t i = 0; i < STATE_COUNT; ++i) {
        res[i] = NAN;
    }

    return res;
}

double * createVariablesArray()
{
    double *res = (double *) malloc(VARIABLE_COUNT*sizeof(double));

    for (size_t i = 0; i < VARIABLE_COUNT; ++i) {
        res[i] = NAN;
    }

    return res;
}

void deleteArray(double *array)
{
    free(array);
}

void initialiseVariables(double *states, double *rates, double *constants)
{
    constants[0] = 0.0;
    constants[1] = 1.0;
    constants[2] = 1.0309347;
    constants[3] = 2.0e-5;
    constants[4] = 6.5e-5;
    constants[5] = 8314.0;
    constants[6] = 310.0;
    constants[7] = 96845.0;
    constants[8] = 5.8e-5;
    constants[9] = 0.000189;
    constants[10] = 5.8e-5;
    constants[11] = 0.000189;
    constants[12] = 5.81818e-5;
    constants[13] = 0.0001888;
    constants[14] = 2.52e-5;
    constants[15] = 8.19e-5;
    constants[16] = 2.52e-5;
    constants[17] = 8.19e-5;
    constants[18] = 2.523636e-5;
    constants[19] = 8.1892e-5;
    constants[20] = 1.32e-5;
    constants[21] = 4.3e-5;
    constants[22] = 1.323e-5;
    constants[23] = 4.29e-5;
    constants[24] = 1.3236e-5;
    constants[25] = 4.2952e-5;
    constants[26] = 2.7e-6;
    constants[27] = 8.8e-6;
    constants[28] = 2.8e-6;
    constants[29] = 8.8e-6;
    constants[30] = 2.7229e-6;
    constants[31] = 8.83584e-6;
    constants[32] = 8.0;
    constants[33] = 0.5;
    constants[34] = 2.0;
    constants[35] = 140.0;
    constants[36] = 0.0001;
    constants[37] = 0.0001;
    constants[38] = 0.0478;
    constants[39] = 0.16;
    constants[40] = 0.0478;
    constants[41] = 0.16;
    constants[42] = 0.04782545;
    constants[43] = 0.1551936;
    constants[44] = 5.4;
    constants[45] = 0.621;
    constants[46] = 5.64;
    constants[47] = 0.0;
    constants[48] = 0.0;
    constants[49] = 0.0042;
    constants[50] = 0.03339;
    constants[51] = 0.0;
    constants[52] = 0.0;
    constants[53] = 140.0;
    constants[54] = 0.0;
    constants[55] = 1.2e-6;
    constants[56] = 0.0;
    constants[57] = 3.7e-7;
    constants[58] = 0.0;
    constants[59] = 1.204e-6;
    constants[60] = 0.0058;
    constants[61] = 0.0659;
    constants[62] = 0.0082;
    constants[63] = 0.0659;
    constants[64] = 0.0057938;
    constants[65] = 0.06588648;
    constants[66] = 46.4;
    constants[67] = 0.0043;
    constants[68] = 0.0139;
    constants[69] = 0.0021;
    constants[70] = 0.00694;
    constants[71] = 0.00427806;
    constants[72] = 0.0138823;
    constants[73] = 45.0;
    constants[74] = 0.00491;
    constants[75] = 0.03649;
    constants[76] = 0.004905;
    constants[77] = 0.0365;
    constants[78] = 0.004905;
    constants[79] = 0.036495;
    constants[80] = 6.65e-5;
    constants[81] = 0.0114;
    constants[82] = 0.000266;
    constants[83] = 0.0114;
    constants[84] = 6.645504e-5;
    constants[85] = 0.01138376;
    constants[86] = 0.000797;
    constants[87] = 0.016;
    constants[88] = 0.000738;
    constants[89] = 0.0208;
    constants[90] = 0.00079704;
    constants[91] = 0.016;
    constants[92] = 0.000518;
    constants[93] = 0.0104;
    constants[94] = 0.000345;
    constants[95] = 0.0104;
    constants[96] = 0.0003445;
    constants[97] = 0.0104;
    constants[98] = 0.000548;
    constants[99] = 0.0069;
    constants[100] = 0.000437;
    constants[101] = 0.0055;
    constants[102] = 0.0005465;
    constants[103] = 0.006875;
    constants[104] = 0.000548;
    constants[105] = 0.0069;
    constants[106] = 0.000437;
    constants[107] = 0.0055;
    constants[108] = 0.0005465;
    constants[109] = 0.006875;
    states[0] = -39.013558536;
    states[1] = 0.092361701692;
    states[2] = 0.015905380261;
    states[3] = 0.01445216109;
    states[4] = 0.48779845203;
    states[5] = 0.04804900895;
    states[6] = 0.038968420558;
    states[7] = 0.42074047435;
    states[8] = 0.064402950262;
    states[9] = 0.29760539675;
    states[10] = 0.87993375273;
    states[11] = 0.13034201158;
    states[12] = 0.46960956028;
    states[13] = 0.082293827208;
    states[14] = 0.03889291759;
}

void computeComputedConstants(double *constants, double *computedConstants)
{
    computedConstants[0] = (constants[1] == 0.0)?1.07*(3.0*constants[0]-0.1)/(3.0*(1.0+0.7745*exp(-(3.0*constants[0]-2.05)/0.295))):(constants[1] == 1.0)?constants[2]*constants[0]/(1.0+0.7745*exp(-(3.0*constants[0]-2.05)/0.295)):1.07*29.0*constants[0]/(30.0*(1.0+0.7745*exp(-(29.0*constants[0]-24.5)/1.95)));
    computedConstants[1] = constants[3]+computedConstants[0]*(constants[4]-constants[3]);
    computedConstants[3] = (constants[1] == 0.0)?constants[8]+computedConstants[0]*(constants[9]-constants[8]):(constants[1] == 1.0)?constants[12]+computedConstants[0]*(constants[13]-constants[12]):constants[10]+computedConstants[0]*(constants[11]-constants[10]);
    computedConstants[5] = (constants[1] == 0.0)?constants[14]+computedConstants[0]*(constants[15]-constants[14]):(constants[1] == 1.0)?constants[18]+computedConstants[0]*(constants[19]-constants[18]):constants[16]+computedConstants[0]*(constants[17]-constants[16]);
    computedConstants[7] = (constants[1] == 0.0)?constants[20]+computedConstants[0]*(constants[21]-constants[20]):(constants[1] == 1.0)?constants[24]+computedConstants[0]*(constants[25]-constants[24]):constants[22]+computedConstants[0]*(constants[23]-constants[22]);
    computedConstants[9] = (constants[1] == 0.0)?constants[26]+computedConstants[0]*(constants[27]-constants[26]):(constants[1] == 1.0)?constants[30]+computedConstants[0]*(constants[31]-constants[30]):constants[28]+computedConstants[0]*(constants[29]-constants[28]);
    computedConstants[10] = (constants[1] == 0.0)?constants[38]+computedConstants[0]*(constants[39]-constants[38]):(constants[1] == 1.0)?constants[42]+computedConstants[0]*(constants[43]-constants[42]):constants[40]+computedConstants[0]*(constants[41]-constants[40]);
    computedConstants[11] = (constants[1] == 0.0)?constants[47]+computedConstants[0]*(constants[48]-constants[47]):(constants[1] == 1.0)?constants[51]+computedConstants[0]*(constants[52]-constants[51]):constants[49]+computedConstants[0]*(constants[50]-constants[49]);
    computedConstants[2] = computedConstants[11]*constants[36]/(constants[36]+0.0004);
    computedConstants[4] = constants[5]*constants[6]/constants[7]*log(constants[35]/constants[32]);
    computedConstants[6] = constants[5]*constants[6]/constants[7]*log(constants[44]/constants[53]);
    computedConstants[8] = constants[5]*constants[6]/(2.0*constants[7])*log(constants[34]/constants[36]);
    computedConstants[12] = (constants[1] == 0.0)?constants[5]*constants[6]/constants[7]*log((constants[44]+0.12*constants[35])/(constants[53]+0.12*constants[32])):constants[5]*constants[6]/constants[7]*log((constants[44]+0.03*constants[35])/(constants[53]+0.03*constants[32]));
    computedConstants[13] = (constants[1] == 0.0)?constants[54]+computedConstants[0]*(constants[55]-constants[54]):(constants[1] == 1.0)?constants[58]+computedConstants[0]*(constants[59]-constants[58]):constants[56]+computedConstants[0]*(constants[57]-constants[56]);
    computedConstants[14] = (constants[1] == 0.0)?constants[60]+computedConstants[0]*(constants[61]-constants[60]):(constants[1] == 1.0)?constants[64]+computedConstants[0]*(constants[65]-constants[64]):constants[62]+computedConstants[0]*(constants[63]-constants[62]);
    computedConstants[15] = (constants[1] == 0.0)?constants[67]+computedConstants[0]*(constants[68]-constants[67]):(constants[1] == 1.0)?constants[71]+computedConstants[0]*(constants[72]-constants[71]):constants[69]+computedConstants[0]*(constants[70]-constants[69]);
    computedConstants[16] = (constants[1] == 0.0)?constants[74]+computedConstants[0]*(constants[75]-constants[74]):(constants[1] == 1.0)?constants[78]+computedConstants[0]*(constants[79]-constants[78]):constants[76]+computedConstants[0]*(constants[77]-constants[76]);
    computedConstants[17] = (constants[1] == 0.0)?constants[80]+computedConstants[0]*(constants[81]-constants[80]):(constants[1] == 1.0)?constants[84]+computedConstants[0]*(constants[85]-constants[84]):constants[82]+computedConstants[0]*(constants[83]-constants[82]);
    computedConstants[18] = (constants[1] == 0.0)?constants[86]+computedConstants[0]*(constants[87]-constants[86]):(constants[1] == 1.0)?constants[90]+computedConstants[0]*(constants[91]-constants[90]):constants[88]+computedConstants[0]*(constants[89]-constants[88]);
    computedConstants[19] = (constants[1] == 0.0)?0.002:(constants[1] == 1.0)?0.002:0.006;
    computedConstants[20] = (constants[1] == 0.0)?constants[92]+computedConstants[0]*(constants[93]-constants[92]):(constants[1] == 1.0)?constants[96]+computedConstants[0]*(constants[97]-constants[96]):constants[94]+computedConstants[0]*(constants[95]-constants[94]);
    computedConstants[21] = (constants[1] == 0.0)?constants[98]+computedConstants[0]*(constants[99]-constants[98]):(constants[1] == 1.0)?constants[102]+computedConstants[0]*(constants[103]-constants[102]):constants[100]+computedConstants[0]*(constants[101]-constants[100]);
    computedConstants[22] = (constants[1] == 0.0)?constants[104]+computedConstants[0]*(constants[105]-constants[104]):(constants[1] == 1.0)?constants[108]+computedConstants[0]*(constants[109]-constants[108]):constants[106]+computedConstants[0]*(constants[107]-constants[106]);
}

void computeRates(double voi, double *states, double *rates, double *constants, double *computedConstants, double *algebraic)
{
    algebraic[1] = computedConstants[10]*pow(constants[32]/(constants[46]+constants[32]), 3.0)*pow(constants[44]/(constants[45]+constants[44]), 2.0)*1.6/(1.5+exp(-(states[0]+60.0)/40.0));
    algebraic[2] = (constants[1] == 0.0)?computedConstants[9]*(pow(constants[32], 3.0)*constants[34]*exp(0.03743*states[0]*constants[33])-pow(constants[35], 3.0)*constants[36]*exp(0.0374*states[0]*(constants[33]-1.0)))/(1.0+constants[37]*(constants[36]*pow(constants[35], 3.0)+constants[34]*pow(constants[32], 3.0))):computedConstants[9]*(pow(constants[32], 3.0)*constants[34]*exp(0.03743*states[0]*constants[33])-pow(constants[35], 3.0)*constants[36]*exp(0.03743*states[0]*(constants[33]-1.0)))/(1.0+constants[37]*(constants[36]*pow(constants[35], 3.0)+constants[34]*pow(constants[32], 3.0)));
    algebraic[6] = (constants[1] != 2.0)?computedConstants[22]*states[14]*(states[0]-computedConstants[6]):computedConstants[22]*states[14]*(states[0]+102.0);
    algebraic[7] = (constants[1] != 2.0)?computedConstants[21]*states[14]*(states[0]-computedConstants[4]):computedConstants[21]*states[14]*(states[0]-77.6);
    algebraic[8] = computedConstants[20]*pow(states[13], 2.0)*(states[0]-computedConstants[12]);
    algebraic[10] = computedConstants[17]*states[8]*(states[0]-computedConstants[6]);
    algebraic[11] = computedConstants[16]*states[9]*states[8]*(states[0]-computedConstants[6]);
    algebraic[12] = computedConstants[15]*states[7]*states[6]*(states[0]-constants[73]);
    algebraic[13] = computedConstants[14]*(states[4]*states[5]+0.006/(1.0+exp(-(states[0]+14.1)/6.0)))*(states[0]-constants[66]);
    algebraic[17] = (constants[1] == 0.0)?0.0952*exp(-0.063*(states[0]+34.4))/(1.0+1.66*exp(-0.225*(states[0]+63.7)))+0.0869:0.09518*exp(-0.06306*(states[0]+34.4))/(1.0+1.662*exp(-0.2251*(states[0]+63.7)))+0.08693;
    algebraic[14] = (1.0-algebraic[17])*states[2]+algebraic[17]*states[3];
    algebraic[0] = computedConstants[13]*pow(states[1], 3.0)*algebraic[14]*constants[35]*pow(constants[7], 2.0)/(constants[5]*constants[6])*(exp((states[0]-computedConstants[4])*constants[7]/(constants[5]*constants[6]))-1.0)/(exp(states[0]*constants[7]/(constants[5]*constants[6]))-1.0)*states[0];
    algebraic[3] = computedConstants[5]*(states[0]-computedConstants[6]);
    algebraic[4] = computedConstants[7]*(states[0]-computedConstants[8]);
    algebraic[5] = computedConstants[3]*(states[0]-computedConstants[4]);
    algebraic[42] = 0.6*states[11]+0.4*states[12];
    algebraic[9] = computedConstants[18]*algebraic[42]*states[10]*(states[0]-computedConstants[6]);
    rates[0] = -1.0/computedConstants[1]*(algebraic[0]+algebraic[13]+algebraic[12]+algebraic[11]+algebraic[10]+algebraic[9]+algebraic[8]+algebraic[7]+algebraic[6]+algebraic[5]+algebraic[4]+algebraic[3]+algebraic[2]+algebraic[1]+computedConstants[2]);
    algebraic[15] = (constants[1] == 0.0)?pow(1.0/(1.0+exp(-states[0]/5.46)), 1.0/3.0):pow(1.0/(1.0+exp(-(states[0]+30.32)/5.46)), 1.0/3.0);
    algebraic[16] = (constants[1] == 0.0)?0.0006247/(0.832*exp(-0.335*(states[0]+56.7))+0.627*exp(0.082*(states[0]+65.01)))+4.0e-5:0.0006247/(0.8322166*exp(-0.33566*(states[0]+56.7062))+0.6274*exp(0.0823*(states[0]+65.0131)))+4.569e-5;
    rates[1] = (algebraic[15]-states[1])/algebraic[16];
    algebraic[18] = 1.0/(1.0+exp((states[0]+66.1)/6.4));
    algebraic[19] = 3.717e-6*exp(-0.2815*(states[0]+17.11))/(1.0+0.003732*exp(-0.3426*(states[0]+37.76)))+0.0005977;
    rates[2] = (algebraic[18]-states[2])/algebraic[19];
    algebraic[20] = algebraic[18];
    algebraic[21] = 3.186e-8*exp(-0.6219*(states[0]+18.8))/(1.0+7.189e-5*exp(-0.6683*(states[0]+34.07)))+0.003556;
    rates[3] = (algebraic[20]-states[3])/algebraic[21];
    algebraic[22] = (constants[1] == 0.0)?1.0/(1.0+exp(-(states[0]+23.1)/6.0)):(constants[1] == 1.0)?1.0/(1.0+exp(-(states[0]+22.3+0.8*computedConstants[0])/6.0)):1.0/(1.0+exp(-(states[0]+22.2)/6.0));
    algebraic[24] = (constants[1] == 0.0)?-28.38*(states[0]+35.0)/(exp(-(states[0]+35.0)/2.5)-1.0)-84.9*states[0]/(exp(-0.208*states[0])-1.0):(constants[1] == 1.0)?-28.39*(states[0]+35.0)/(exp(-(states[0]+35.0)/2.5)-1.0)-84.9*states[0]/(exp(-0.208*states[0])-1.0):-28.4*(states[0]+35.0)/(exp(-(states[0]+35.0)/2.5)-1.0)-84.9*states[0]/(exp(-0.208*states[0])-1.0);
    algebraic[25] = (constants[1] == 1.0)?11.43*(states[0]-5.0)/(exp(0.4*(states[0]-5.0))-1.0):11.42*(states[0]-5.0)/(exp(0.4*(states[0]-5.0))-1.0);
    algebraic[23] = 2.0/(algebraic[24]+algebraic[25]);
    rates[5] = (algebraic[22]-states[5])/algebraic[23];
    algebraic[26] = 1.0/(1.0+exp((states[0]+45.0)/5.0));
    algebraic[28] = (constants[1] == 1.0)?3.75*(states[0]+28.0)/(exp((states[0]+28.0)/4.0)-1.0):3.12*(states[0]+28.0)/(exp((states[0]+28.0)/4.0)-1.0);
    algebraic[29] = (constants[1] == 1.0)?30.0/(1.0+exp(-(states[0]+28.0)/4.0)):25.0/(1.0+exp(-(states[0]+28.0)/4.0));
    algebraic[27] = (constants[1] == 1.0)?(1.2-0.2*computedConstants[0])/(algebraic[28]+algebraic[29]):1.0/(algebraic[28]+algebraic[29]);
    rates[4] = (algebraic[26]-states[4])/algebraic[27];
    algebraic[30] = 1.0/(1.0+exp(-(states[0]+37.0)/6.8));
    algebraic[32] = 1068.0*exp((states[0]+26.3)/30.0);
    algebraic[33] = 1068.0*exp(-(states[0]+26.3)/30.0);
    algebraic[31] = 1.0/(algebraic[32]+algebraic[33]);
    rates[7] = (algebraic[30]-states[7])/algebraic[31];
    algebraic[34] = 1.0/(1.0+exp((states[0]+71.0)/9.0));
    algebraic[36] = (constants[1] == 1.0)?15.3*exp(-(states[0]+71.0+0.7*computedConstants[0])/83.3):15.3*exp(-(states[0]+71.7)/83.3);
    algebraic[37] = (constants[1] == 1.0)?15.0*exp((states[0]+71.0)/15.38):15.0*exp((states[0]+71.7)/15.38);
    algebraic[35] = 1.0/(algebraic[36]+algebraic[37]);
    rates[6] = (algebraic[34]-states[6])/algebraic[35];
    algebraic[38] = 1.0/(1.0+exp((states[0]+59.37)/13.1));
    algebraic[39] = (constants[1] == 0.0)?0.0101+0.06517/(0.57*exp(-0.08*(states[0]+49.0)))+2.4e-5*exp(0.1*(states[0]+50.93)):(constants[1] == 1.0)?0.001/3.0*(30.31+195.5/(0.5686*exp(-0.08161*(states[0]+39.0+10.0*computedConstants[0]))+0.7174*exp((0.2719-0.1719*computedConstants[0])*1.0*(states[0]+40.93+10.0*computedConstants[0])))):0.0101+0.06517/(0.5686*exp(-0.08161*(states[0]+39.0))+0.7174*exp(0.2719*(states[0]+40.93)));
    rates[9] = (algebraic[38]-states[9])/algebraic[39];
    algebraic[40] = 1.0/(1.0+exp(-(states[0]-10.93)/19.7));
    algebraic[41] = (constants[1] == 0.0)?0.001*(2.98+15.59/(1.037*exp(0.09*(states[0]+30.61))+0.369*exp(-0.12*(states[0]+23.84)))):(constants[1] == 1.0)?0.0025*(1.191+7.838/(1.037*exp(0.09012*(states[0]+30.61))+0.369*exp(-0.119*(states[0]+23.84)))):0.001*(2.98+19.59/(1.037*exp(0.09012*(states[0]+30.61))+0.369*exp(-0.119*(states[0]+23.84))));
    rates[8] = (algebraic[40]-states[8])/algebraic[41];
    algebraic[43] = (constants[1] != 2.0)?1.0/(1.0+exp(-(states[0]+14.2)/10.6)):1.0/(1.0+exp(-(states[0]+13.2)/10.6));
    algebraic[44] = (constants[1] != 2.0)?1.0/(37.2*exp((states[0]-9.0)/15.9)+0.96*exp(-(states[0]-9.0)/22.5)):1.0/(37.2*exp((states[0]-10.0)/15.9)+0.96*exp(-(states[0]-10.0)/22.5));
    rates[11] = (algebraic[43]-states[11])/algebraic[44];
    algebraic[45] = algebraic[43];
    algebraic[46] = (constants[1] != 2.0)?1.0/(4.2*exp((states[0]-9.0)/17.0)+0.15*exp(-(states[0]-9.0)/21.6)):1.0/(4.2*exp((states[0]-10.0)/17.0)+0.15*exp(-(states[0]-10.0)/21.6));
    rates[12] = (algebraic[45]-states[12])/algebraic[46];
    algebraic[47] = 1.0/(1.0+exp((states[0]+18.6)/10.1));
    rates[10] = (algebraic[47]-states[10])/computedConstants[19];
    algebraic[48] = 14.0/(1.0+exp(-(states[0]-40.0)/9.0));
    algebraic[49] = 1.0*exp(-states[0]/45.0);
    rates[13] = algebraic[48]*(1.0-states[13])-algebraic[49]*states[13];
    algebraic[50] = (constants[1] == 0.0)?1.0*exp(-(states[0]+78.91)/26.62):1.0*exp(-(states[0]+78.91)/26.63);
    algebraic[51] = 1.0*exp((states[0]+75.13)/21.25);
    rates[14] = algebraic[50]*(1.0-states[14])-algebraic[51]*states[14];
}

void computeVariables(double voi, double *states, double *rates, double *constants, double *computedConstants, double *algebraic)
{
    algebraic[5] = computedConstants[3]*(states[0]-computedConstants[4]);
    algebraic[3] = computedConstants[5]*(states[0]-computedConstants[6]);
    algebraic[4] = computedConstants[7]*(states[0]-computedConstants[8]);
    algebraic[2] = (constants[1] == 0.0)?computedConstants[9]*(pow(constants[32], 3.0)*constants[34]*exp(0.03743*states[0]*constants[33])-pow(constants[35], 3.0)*constants[36]*exp(0.0374*states[0]*(constants[33]-1.0)))/(1.0+constants[37]*(constants[36]*pow(constants[35], 3.0)+constants[34]*pow(constants[32], 3.0))):computedConstants[9]*(pow(constants[32], 3.0)*constants[34]*exp(0.03743*states[0]*constants[33])-pow(constants[35], 3.0)*constants[36]*exp(0.03743*states[0]*(constants[33]-1.0)))/(1.0+constants[37]*(constants[36]*pow(constants[35], 3.0)+constants[34]*pow(constants[32], 3.0)));
    algebraic[1] = computedConstants[10]*pow(constants[32]/(constants[46]+constants[32]), 3.0)*pow(constants[44]/(constants[45]+constants[44]), 2.0)*1.6/(1.5+exp(-(states[0]+60.0)/40.0));
    algebraic[17] = (constants[1] == 0.0)?0.0952*exp(-0.063*(states[0]+34.4))/(1.0+1.66*exp(-0.225*(states[0]+63.7)))+0.0869:0.09518*exp(-0.06306*(states[0]+34.4))/(1.0+1.662*exp(-0.2251*(states[0]+63.7)))+0.08693;
    algebraic[14] = (1.0-algebraic[17])*states[2]+algebraic[17]*states[3];
    algebraic[0] = computedConstants[13]*pow(states[1], 3.0)*algebraic[14]*constants[35]*pow(constants[7], 2.0)/(constants[5]*constants[6])*(exp((states[0]-computedConstants[4])*constants[7]/(constants[5]*constants[6]))-1.0)/(exp(states[0]*constants[7]/(constants[5]*constants[6]))-1.0)*states[0];
    algebraic[15] = (constants[1] == 0.0)?pow(1.0/(1.0+exp(-states[0]/5.46)), 1.0/3.0):pow(1.0/(1.0+exp(-(states[0]+30.32)/5.46)), 1.0/3.0);
    algebraic[16] = (constants[1] == 0.0)?0.0006247/(0.832*exp(-0.335*(states[0]+56.7))+0.627*exp(0.082*(states[0]+65.01)))+4.0e-5:0.0006247/(0.8322166*exp(-0.33566*(states[0]+56.7062))+0.6274*exp(0.0823*(states[0]+65.0131)))+4.569e-5;
    algebraic[18] = 1.0/(1.0+exp((states[0]+66.1)/6.4));
    algebraic[20] = algebraic[18];
    algebraic[19] = 3.717e-6*exp(-0.2815*(states[0]+17.11))/(1.0+0.003732*exp(-0.3426*(states[0]+37.76)))+0.0005977;
    algebraic[21] = 3.186e-8*exp(-0.6219*(states[0]+18.8))/(1.0+7.189e-5*exp(-0.6683*(states[0]+34.07)))+0.003556;
    algebraic[13] = computedConstants[14]*(states[4]*states[5]+0.006/(1.0+exp(-(states[0]+14.1)/6.0)))*(states[0]-constants[66]);
    algebraic[24] = (constants[1] == 0.0)?-28.38*(states[0]+35.0)/(exp(-(states[0]+35.0)/2.5)-1.0)-84.9*states[0]/(exp(-0.208*states[0])-1.0):(constants[1] == 1.0)?-28.39*(states[0]+35.0)/(exp(-(states[0]+35.0)/2.5)-1.0)-84.9*states[0]/(exp(-0.208*states[0])-1.0):-28.4*(states[0]+35.0)/(exp(-(states[0]+35.0)/2.5)-1.0)-84.9*states[0]/(exp(-0.208*states[0])-1.0);
    algebraic[25] = (constants[1] == 1.0)?11.43*(states[0]-5.0)/(exp(0.4*(states[0]-5.0))-1.0):11.42*(states[0]-5.0)/(exp(0.4*(states[0]-5.0))-1.0);
    algebraic[23] = 2.0/(algebraic[24]+algebraic[25]);
    algebraic[22] = (constants[1] == 0.0)?1.0/(1.0+exp(-(states[0]+23.1)/6.0)):(constants[1] == 1.0)?1.0/(1.0+exp(-(states[0]+22.3+0.8*computedConstants[0])/6.0)):1.0/(1.0+exp(-(states[0]+22.2)/6.0));
    algebraic[28] = (constants[1] == 1.0)?3.75*(states[0]+28.0)/(exp((states[0]+28.0)/4.0)-1.0):3.12*(states[0]+28.0)/(exp((states[0]+28.0)/4.0)-1.0);
    algebraic[29] = (constants[1] == 1.0)?30.0/(1.0+exp(-(states[0]+28.0)/4.0)):25.0/(1.0+exp(-(states[0]+28.0)/4.0));
    algebraic[27] = (constants[1] == 1.0)?(1.2-0.2*computedConstants[0])/(algebraic[28]+algebraic[29]):1.0/(algebraic[28]+algebraic[29]);
    algebraic[26] = 1.0/(1.0+exp((states[0]+45.0)/5.0));
    algebraic[12] = computedConstants[15]*states[7]*states[6]*(states[0]-constants[73]);
    algebraic[32] = 1068.0*exp((states[0]+26.3)/30.0);
    algebraic[33] = 1068.0*exp(-(states[0]+26.3)/30.0);
    algebraic[31] = 1.0/(algebraic[32]+algebraic[33]);
    algebraic[30] = 1.0/(1.0+exp(-(states[0]+37.0)/6.8));
    algebraic[36] = (constants[1] == 1.0)?15.3*exp(-(states[0]+71.0+0.7*computedConstants[0])/83.3):15.3*exp(-(states[0]+71.7)/83.3);
    algebraic[37] = (constants[1] == 1.0)?15.0*exp((states[0]+71.0)/15.38):15.0*exp((states[0]+71.7)/15.38);
    algebraic[35] = 1.0/(algebraic[36]+algebraic[37]);
    algebraic[34] = 1.0/(1.0+exp((states[0]+71.0)/9.0));
    algebraic[11] = computedConstants[16]*states[9]*states[8]*(states[0]-computedConstants[6]);
    algebraic[10] = computedConstants[17]*states[8]*(states[0]-computedConstants[6]);
    algebraic[38] = 1.0/(1.0+exp((states[0]+59.37)/13.1));
    algebraic[39] = (constants[1] == 0.0)?0.0101+0.06517/(0.57*exp(-0.08*(states[0]+49.0)))+2.4e-5*exp(0.1*(states[0]+50.93)):(constants[1] == 1.0)?0.001/3.0*(30.31+195.5/(0.5686*exp(-0.08161*(states[0]+39.0+10.0*computedConstants[0]))+0.7174*exp((0.2719-0.1719*computedConstants[0])*1.0*(states[0]+40.93+10.0*computedConstants[0])))):0.0101+0.06517/(0.5686*exp(-0.08161*(states[0]+39.0))+0.7174*exp(0.2719*(states[0]+40.93)));
    algebraic[40] = 1.0/(1.0+exp(-(states[0]-10.93)/19.7));
    algebraic[41] = (constants[1] == 0.0)?0.001*(2.98+15.59/(1.037*exp(0.09*(states[0]+30.61))+0.369*exp(-0.12*(states[0]+23.84)))):(constants[1] == 1.0)?0.0025*(1.191+7.838/(1.037*exp(0.09012*(states[0]+30.61))+0.369*exp(-0.119*(states[0]+23.84)))):0.001*(2.98+19.59/(1.037*exp(0.09012*(states[0]+30.61))+0.369*exp(-0.119*(states[0]+23.84))));
    algebraic[42] = 0.6*states[11]+0.4*states[12];
    algebraic[9] = computedConstants[18]*algebraic[42]*states[10]*(states[0]-computedConstants[6]);
    algebraic[43] = (constants[1] != 2.0)?1.0/(1.0+exp(-(states[0]+14.2)/10.6)):1.0/(1.0+exp(-(states[0]+13.2)/10.6));
    algebraic[44] = (constants[1] != 2.0)?1.0/(37.2*exp((states[0]-9.0)/15.9)+0.96*exp(-(states[0]-9.0)/22.5)):1.0/(37.2*exp((states[0]-10.0)/15.9)+0.96*exp(-(states[0]-10.0)/22.5));
    algebraic[45] = algebraic[43];
    algebraic[46] = (constants[1] != 2.0)?1.0/(4.2*exp((states[0]-9.0)/17.0)+0.15*exp(-(states[0]-9.0)/21.6)):1.0/(4.2*exp((states[0]-10.0)/17.0)+0.15*exp(-(states[0]-10.0)/21.6));
    algebraic[47] = 1.0/(1.0+exp((states[0]+18.6)/10.1));
    algebraic[8] = computedConstants[20]*pow(states[13], 2.0)*(states[0]-computedConstants[12]);
    algebraic[48] = 14.0/(1.0+exp(-(states[0]-40.0)/9.0));
    algebraic[49] = 1.0*exp(-states[0]/45.0);
    algebraic[7] = (constants[1] != 2.0)?computedConstants[21]*states[14]*(states[0]-computedConstants[4]):computedConstants[21]*states[14]*(states[0]-77.6);
    algebraic[6] = (constants[1] != 2.0)?computedConstants[22]*states[14]*(states[0]-computedConstants[6]):computedConstants[22]*states[14]*(states[0]+102.0);
    algebraic[50] = (constants[1] == 0.0)?1.0*exp(-(states[0]+78.91)/26.62):1.0*exp(-(states[0]+78.91)/26.63);
    algebraic[51] = 1.0*exp((states[0]+75.13)/21.25);
}

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
    constants[1] = 0.0;
    constants[2] = 1.0;
    constants[3] = 1.0309347;
    constants[5] = 2.0e-5;
    constants[6] = 6.5e-5;
    constants[22] = 8314.0;
    constants[23] = 310.0;
    constants[24] = 96845.0;
    constants[26] = 5.8e-5;
    constants[27] = 0.000189;
    constants[28] = 5.8e-5;
    constants[29] = 0.000189;
    constants[30] = 5.81818e-5;
    constants[31] = 0.0001888;
    constants[34] = 2.52e-5;
    constants[35] = 8.19e-5;
    constants[36] = 2.52e-5;
    constants[37] = 8.19e-5;
    constants[38] = 2.523636e-5;
    constants[39] = 8.1892e-5;
    constants[42] = 1.32e-5;
    constants[43] = 4.3e-5;
    constants[44] = 1.323e-5;
    constants[45] = 4.29e-5;
    constants[46] = 1.3236e-5;
    constants[47] = 4.2952e-5;
    constants[50] = 2.7e-6;
    constants[51] = 8.8e-6;
    constants[52] = 2.8e-6;
    constants[53] = 8.8e-6;
    constants[54] = 2.7229e-6;
    constants[55] = 8.83584e-6;
    constants[56] = 8.0;
    constants[57] = 0.5;
    constants[58] = 2.0;
    constants[59] = 140.0;
    constants[60] = 0.0001;
    constants[61] = 0.0001;
    constants[63] = 0.0478;
    constants[64] = 0.16;
    constants[65] = 0.0478;
    constants[66] = 0.16;
    constants[67] = 0.04782545;
    constants[68] = 0.1551936;
    constants[69] = 5.4;
    constants[70] = 0.621;
    constants[71] = 5.64;
    constants[73] = 0.0;
    constants[74] = 0.0;
    constants[75] = 0.0042;
    constants[76] = 0.03339;
    constants[77] = 0.0;
    constants[78] = 0.0;
    constants[79] = 140.0;
    constants[82] = 0.0;
    constants[83] = 1.2e-6;
    constants[84] = 0.0;
    constants[85] = 3.7e-7;
    constants[86] = 0.0;
    constants[87] = 1.204e-6;
    constants[97] = 0.0058;
    constants[98] = 0.0659;
    constants[99] = 0.0082;
    constants[100] = 0.0659;
    constants[101] = 0.0057938;
    constants[102] = 0.06588648;
    constants[103] = 46.4;
    constants[113] = 0.0043;
    constants[114] = 0.0139;
    constants[115] = 0.0021;
    constants[116] = 0.00694;
    constants[117] = 0.00427806;
    constants[118] = 0.0138823;
    constants[119] = 45.0;
    constants[129] = 0.00491;
    constants[130] = 0.03649;
    constants[131] = 0.004905;
    constants[132] = 0.0365;
    constants[133] = 0.004905;
    constants[134] = 0.036495;
    constants[136] = 6.65e-5;
    constants[137] = 0.0114;
    constants[138] = 0.000266;
    constants[139] = 0.0114;
    constants[140] = 6.645504e-5;
    constants[141] = 0.01138376;
    constants[147] = 0.000797;
    constants[148] = 0.016;
    constants[149] = 0.000738;
    constants[150] = 0.0208;
    constants[151] = 0.00079704;
    constants[152] = 0.016;
    constants[161] = 0.000518;
    constants[162] = 0.0104;
    constants[163] = 0.000345;
    constants[164] = 0.0104;
    constants[165] = 0.0003445;
    constants[166] = 0.0104;
    constants[170] = 0.000548;
    constants[171] = 0.0069;
    constants[172] = 0.000437;
    constants[173] = 0.0055;
    constants[174] = 0.0005465;
    constants[175] = 0.006875;
    constants[177] = 0.000548;
    constants[178] = 0.0069;
    constants[179] = 0.000437;
    constants[180] = 0.0055;
    constants[181] = 0.0005465;
    constants[182] = 0.006875;
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
    computedConstants[0] = (constants[2] == 0.0)?1.07*(3.0*constants[1]-0.1)/(3.0*(1.0+0.7745*exp(-(3.0*constants[1]-2.05)/0.295))):(constants[2] == 1.0)?constants[3]*constants[1]/(1.0+0.7745*exp(-(3.0*constants[1]-2.05)/0.295)):1.07*29.0*constants[1]/(30.0*(1.0+0.7745*exp(-(29.0*constants[1]-24.5)/1.95)));
    computedConstants[4] = constants[5]+computedConstants[0]*(constants[6]-constants[5]);
    computedConstants[25] = (constants[2] == 0.0)?constants[26]+computedConstants[0]*(constants[27]-constants[26]):(constants[2] == 1.0)?constants[30]+computedConstants[0]*(constants[31]-constants[30]):constants[28]+computedConstants[0]*(constants[29]-constants[28]);
    computedConstants[33] = (constants[2] == 0.0)?constants[34]+computedConstants[0]*(constants[35]-constants[34]):(constants[2] == 1.0)?constants[38]+computedConstants[0]*(constants[39]-constants[38]):constants[36]+computedConstants[0]*(constants[37]-constants[36]);
    computedConstants[41] = (constants[2] == 0.0)?constants[42]+computedConstants[0]*(constants[43]-constants[42]):(constants[2] == 1.0)?constants[46]+computedConstants[0]*(constants[47]-constants[46]):constants[44]+computedConstants[0]*(constants[45]-constants[44]);
    computedConstants[49] = (constants[2] == 0.0)?constants[50]+computedConstants[0]*(constants[51]-constants[50]):(constants[2] == 1.0)?constants[54]+computedConstants[0]*(constants[55]-constants[54]):constants[52]+computedConstants[0]*(constants[53]-constants[52]);
    computedConstants[62] = (constants[2] == 0.0)?constants[63]+computedConstants[0]*(constants[64]-constants[63]):(constants[2] == 1.0)?constants[67]+computedConstants[0]*(constants[68]-constants[67]):constants[65]+computedConstants[0]*(constants[66]-constants[65]);
    computedConstants[72] = (constants[2] == 0.0)?constants[73]+computedConstants[0]*(constants[74]-constants[73]):(constants[2] == 1.0)?constants[77]+computedConstants[0]*(constants[78]-constants[77]):constants[75]+computedConstants[0]*(constants[76]-constants[75]);
    computedConstants[8] = computedConstants[72]*constants[60]/(constants[60]+0.0004);
    computedConstants[32] = constants[22]*constants[23]/constants[24]*log(constants[59]/constants[56]);
    computedConstants[40] = constants[22]*constants[23]/constants[24]*log(constants[69]/constants[79]);
    computedConstants[48] = constants[22]*constants[23]/(2.0*constants[24])*log(constants[58]/constants[60]);
    computedConstants[80] = (constants[2] == 0.0)?constants[22]*constants[23]/constants[24]*log((constants[69]+0.12*constants[59])/(constants[79]+0.12*constants[56])):constants[22]*constants[23]/constants[24]*log((constants[69]+0.03*constants[59])/(constants[79]+0.03*constants[56]));
    computedConstants[81] = (constants[2] == 0.0)?constants[82]+computedConstants[0]*(constants[83]-constants[82]):(constants[2] == 1.0)?constants[86]+computedConstants[0]*(constants[87]-constants[86]):constants[84]+computedConstants[0]*(constants[85]-constants[84]);
    computedConstants[96] = (constants[2] == 0.0)?constants[97]+computedConstants[0]*(constants[98]-constants[97]):(constants[2] == 1.0)?constants[101]+computedConstants[0]*(constants[102]-constants[101]):constants[99]+computedConstants[0]*(constants[100]-constants[99]);
    computedConstants[112] = (constants[2] == 0.0)?constants[113]+computedConstants[0]*(constants[114]-constants[113]):(constants[2] == 1.0)?constants[117]+computedConstants[0]*(constants[118]-constants[117]):constants[115]+computedConstants[0]*(constants[116]-constants[115]);
    computedConstants[128] = (constants[2] == 0.0)?constants[129]+computedConstants[0]*(constants[130]-constants[129]):(constants[2] == 1.0)?constants[133]+computedConstants[0]*(constants[134]-constants[133]):constants[131]+computedConstants[0]*(constants[132]-constants[131]);
    computedConstants[135] = (constants[2] == 0.0)?constants[136]+computedConstants[0]*(constants[137]-constants[136]):(constants[2] == 1.0)?constants[140]+computedConstants[0]*(constants[141]-constants[140]):constants[138]+computedConstants[0]*(constants[139]-constants[138]);
    computedConstants[146] = (constants[2] == 0.0)?constants[147]+computedConstants[0]*(constants[148]-constants[147]):(constants[2] == 1.0)?constants[151]+computedConstants[0]*(constants[152]-constants[151]):constants[149]+computedConstants[0]*(constants[150]-constants[149]);
    computedConstants[158] = (constants[2] == 0.0)?0.002:(constants[2] == 1.0)?0.002:0.006;
    computedConstants[160] = (constants[2] == 0.0)?constants[161]+computedConstants[0]*(constants[162]-constants[161]):(constants[2] == 1.0)?constants[165]+computedConstants[0]*(constants[166]-constants[165]):constants[163]+computedConstants[0]*(constants[164]-constants[163]);
    computedConstants[169] = (constants[2] == 0.0)?constants[170]+computedConstants[0]*(constants[171]-constants[170]):(constants[2] == 1.0)?constants[174]+computedConstants[0]*(constants[175]-constants[174]):constants[172]+computedConstants[0]*(constants[173]-constants[172]);
    computedConstants[176] = (constants[2] == 0.0)?constants[177]+computedConstants[0]*(constants[178]-constants[177]):(constants[2] == 1.0)?constants[181]+computedConstants[0]*(constants[182]-constants[181]):constants[179]+computedConstants[0]*(constants[180]-constants[179]);
}

void computeRates(double voi, double *states, double *rates, double *constants, double *computedConstants, double *algebraic)
{
    algebraic[9] = computedConstants[62]*pow(constants[56]/(constants[71]+constants[56]), 3.0)*pow(constants[69]/(constants[70]+constants[69]), 2.0)*1.6/(1.5+exp(-(states[0]+60.0)/40.0));
    algebraic[10] = (constants[2] == 0.0)?computedConstants[49]*(pow(constants[56], 3.0)*constants[58]*exp(0.03743*states[0]*constants[57])-pow(constants[59], 3.0)*constants[60]*exp(0.0374*states[0]*(constants[57]-1.0)))/(1.0+constants[61]*(constants[60]*pow(constants[59], 3.0)+constants[58]*pow(constants[56], 3.0))):computedConstants[49]*(pow(constants[56], 3.0)*constants[58]*exp(0.03743*states[0]*constants[57])-pow(constants[59], 3.0)*constants[60]*exp(0.03743*states[0]*(constants[57]-1.0)))/(1.0+constants[61]*(constants[60]*pow(constants[59], 3.0)+constants[58]*pow(constants[56], 3.0)));
    algebraic[14] = (constants[2] != 2.0)?computedConstants[176]*states[14]*(states[0]-computedConstants[40]):computedConstants[176]*states[14]*(states[0]+102.0);
    algebraic[15] = (constants[2] != 2.0)?computedConstants[169]*states[14]*(states[0]-computedConstants[32]):computedConstants[169]*states[14]*(states[0]-77.6);
    algebraic[16] = computedConstants[160]*pow(states[13], 2.0)*(states[0]-computedConstants[80]);
    algebraic[18] = computedConstants[135]*states[8]*(states[0]-computedConstants[40]);
    algebraic[19] = computedConstants[128]*states[9]*states[8]*(states[0]-computedConstants[40]);
    algebraic[20] = computedConstants[112]*states[7]*states[6]*(states[0]-constants[119]);
    algebraic[21] = computedConstants[96]*(states[4]*states[5]+0.006/(1.0+exp(-(states[0]+14.1)/6.0)))*(states[0]-constants[103]);
    algebraic[91] = (constants[2] == 0.0)?0.0952*exp(-0.063*(states[0]+34.4))/(1.0+1.66*exp(-0.225*(states[0]+63.7)))+0.0869:0.09518*exp(-0.06306*(states[0]+34.4))/(1.0+1.662*exp(-0.2251*(states[0]+63.7)))+0.08693;
    algebraic[88] = (1.0-algebraic[91])*states[2]+algebraic[91]*states[3];
    algebraic[7] = computedConstants[81]*pow(states[1], 3.0)*algebraic[88]*constants[59]*pow(constants[24], 2.0)/(constants[22]*constants[23])*(exp((states[0]-computedConstants[32])*constants[24]/(constants[22]*constants[23]))-1.0)/(exp(states[0]*constants[24]/(constants[22]*constants[23]))-1.0)*states[0];
    algebraic[11] = computedConstants[33]*(states[0]-computedConstants[40]);
    algebraic[12] = computedConstants[41]*(states[0]-computedConstants[48]);
    algebraic[13] = computedConstants[25]*(states[0]-computedConstants[32]);
    algebraic[153] = 0.6*states[11]+0.4*states[12];
    algebraic[17] = computedConstants[146]*algebraic[153]*states[10]*(states[0]-computedConstants[40]);
    rates[0] = -1.0/computedConstants[4]*(algebraic[7]+algebraic[21]+algebraic[20]+algebraic[19]+algebraic[18]+algebraic[17]+algebraic[16]+algebraic[15]+algebraic[14]+algebraic[13]+algebraic[12]+algebraic[11]+algebraic[10]+algebraic[9]+computedConstants[8]);
    algebraic[89] = (constants[2] == 0.0)?pow(1.0/(1.0+exp(-states[0]/5.46)), 1.0/3.0):pow(1.0/(1.0+exp(-(states[0]+30.32)/5.46)), 1.0/3.0);
    algebraic[90] = (constants[2] == 0.0)?0.0006247/(0.832*exp(-0.335*(states[0]+56.7))+0.627*exp(0.082*(states[0]+65.01)))+4.0e-5:0.0006247/(0.8322166*exp(-0.33566*(states[0]+56.7062))+0.6274*exp(0.0823*(states[0]+65.0131)))+4.569e-5;
    rates[1] = (algebraic[89]-states[1])/algebraic[90];
    algebraic[92] = 1.0/(1.0+exp((states[0]+66.1)/6.4));
    algebraic[93] = 3.717e-6*exp(-0.2815*(states[0]+17.11))/(1.0+0.003732*exp(-0.3426*(states[0]+37.76)))+0.0005977;
    rates[2] = (algebraic[92]-states[2])/algebraic[93];
    algebraic[94] = algebraic[92];
    algebraic[95] = 3.186e-8*exp(-0.6219*(states[0]+18.8))/(1.0+7.189e-5*exp(-0.6683*(states[0]+34.07)))+0.003556;
    rates[3] = (algebraic[94]-states[3])/algebraic[95];
    algebraic[104] = (constants[2] == 0.0)?1.0/(1.0+exp(-(states[0]+23.1)/6.0)):(constants[2] == 1.0)?1.0/(1.0+exp(-(states[0]+22.3+0.8*computedConstants[0])/6.0)):1.0/(1.0+exp(-(states[0]+22.2)/6.0));
    algebraic[106] = (constants[2] == 0.0)?-28.38*(states[0]+35.0)/(exp(-(states[0]+35.0)/2.5)-1.0)-84.9*states[0]/(exp(-0.208*states[0])-1.0):(constants[2] == 1.0)?-28.39*(states[0]+35.0)/(exp(-(states[0]+35.0)/2.5)-1.0)-84.9*states[0]/(exp(-0.208*states[0])-1.0):-28.4*(states[0]+35.0)/(exp(-(states[0]+35.0)/2.5)-1.0)-84.9*states[0]/(exp(-0.208*states[0])-1.0);
    algebraic[107] = (constants[2] == 1.0)?11.43*(states[0]-5.0)/(exp(0.4*(states[0]-5.0))-1.0):11.42*(states[0]-5.0)/(exp(0.4*(states[0]-5.0))-1.0);
    algebraic[105] = 2.0/(algebraic[106]+algebraic[107]);
    rates[5] = (algebraic[104]-states[5])/algebraic[105];
    algebraic[108] = 1.0/(1.0+exp((states[0]+45.0)/5.0));
    algebraic[110] = (constants[2] == 1.0)?3.75*(states[0]+28.0)/(exp((states[0]+28.0)/4.0)-1.0):3.12*(states[0]+28.0)/(exp((states[0]+28.0)/4.0)-1.0);
    algebraic[111] = (constants[2] == 1.0)?30.0/(1.0+exp(-(states[0]+28.0)/4.0)):25.0/(1.0+exp(-(states[0]+28.0)/4.0));
    algebraic[109] = (constants[2] == 1.0)?(1.2-0.2*computedConstants[0])/(algebraic[110]+algebraic[111]):1.0/(algebraic[110]+algebraic[111]);
    rates[4] = (algebraic[108]-states[4])/algebraic[109];
    algebraic[120] = 1.0/(1.0+exp(-(states[0]+37.0)/6.8));
    algebraic[122] = 1068.0*exp((states[0]+26.3)/30.0);
    algebraic[123] = 1068.0*exp(-(states[0]+26.3)/30.0);
    algebraic[121] = 1.0/(algebraic[122]+algebraic[123]);
    rates[7] = (algebraic[120]-states[7])/algebraic[121];
    algebraic[124] = 1.0/(1.0+exp((states[0]+71.0)/9.0));
    algebraic[126] = (constants[2] == 1.0)?15.3*exp(-(states[0]+71.0+0.7*computedConstants[0])/83.3):15.3*exp(-(states[0]+71.7)/83.3);
    algebraic[127] = (constants[2] == 1.0)?15.0*exp((states[0]+71.0)/15.38):15.0*exp((states[0]+71.7)/15.38);
    algebraic[125] = 1.0/(algebraic[126]+algebraic[127]);
    rates[6] = (algebraic[124]-states[6])/algebraic[125];
    algebraic[142] = 1.0/(1.0+exp((states[0]+59.37)/13.1));
    algebraic[143] = (constants[2] == 0.0)?0.0101+0.06517/(0.57*exp(-0.08*(states[0]+49.0)))+2.4e-5*exp(0.1*(states[0]+50.93)):(constants[2] == 1.0)?0.001/3.0*(30.31+195.5/(0.5686*exp(-0.08161*(states[0]+39.0+10.0*computedConstants[0]))+0.7174*exp((0.2719-0.1719*computedConstants[0])*1.0*(states[0]+40.93+10.0*computedConstants[0])))):0.0101+0.06517/(0.5686*exp(-0.08161*(states[0]+39.0))+0.7174*exp(0.2719*(states[0]+40.93)));
    rates[9] = (algebraic[142]-states[9])/algebraic[143];
    algebraic[144] = 1.0/(1.0+exp(-(states[0]-10.93)/19.7));
    algebraic[145] = (constants[2] == 0.0)?0.001*(2.98+15.59/(1.037*exp(0.09*(states[0]+30.61))+0.369*exp(-0.12*(states[0]+23.84)))):(constants[2] == 1.0)?0.0025*(1.191+7.838/(1.037*exp(0.09012*(states[0]+30.61))+0.369*exp(-0.119*(states[0]+23.84)))):0.001*(2.98+19.59/(1.037*exp(0.09012*(states[0]+30.61))+0.369*exp(-0.119*(states[0]+23.84))));
    rates[8] = (algebraic[144]-states[8])/algebraic[145];
    algebraic[154] = (constants[2] != 2.0)?1.0/(1.0+exp(-(states[0]+14.2)/10.6)):1.0/(1.0+exp(-(states[0]+13.2)/10.6));
    algebraic[155] = (constants[2] != 2.0)?1.0/(37.2*exp((states[0]-9.0)/15.9)+0.96*exp(-(states[0]-9.0)/22.5)):1.0/(37.2*exp((states[0]-10.0)/15.9)+0.96*exp(-(states[0]-10.0)/22.5));
    rates[11] = (algebraic[154]-states[11])/algebraic[155];
    algebraic[156] = algebraic[154];
    algebraic[157] = (constants[2] != 2.0)?1.0/(4.2*exp((states[0]-9.0)/17.0)+0.15*exp(-(states[0]-9.0)/21.6)):1.0/(4.2*exp((states[0]-10.0)/17.0)+0.15*exp(-(states[0]-10.0)/21.6));
    rates[12] = (algebraic[156]-states[12])/algebraic[157];
    algebraic[159] = 1.0/(1.0+exp((states[0]+18.6)/10.1));
    rates[10] = (algebraic[159]-states[10])/computedConstants[158];
    algebraic[167] = 14.0/(1.0+exp(-(states[0]-40.0)/9.0));
    algebraic[168] = 1.0*exp(-states[0]/45.0);
    rates[13] = algebraic[167]*(1.0-states[13])-algebraic[168]*states[13];
    algebraic[183] = (constants[2] == 0.0)?1.0*exp(-(states[0]+78.91)/26.62):1.0*exp(-(states[0]+78.91)/26.63);
    algebraic[184] = 1.0*exp((states[0]+75.13)/21.25);
    rates[14] = algebraic[183]*(1.0-states[14])-algebraic[184]*states[14];
}

void computeVariables(double voi, double *states, double *rates, double *constants, double *computedConstants, double *algebraic)
{
    algebraic[13] = computedConstants[25]*(states[0]-computedConstants[32]);
    algebraic[11] = computedConstants[33]*(states[0]-computedConstants[40]);
    algebraic[12] = computedConstants[41]*(states[0]-computedConstants[48]);
    algebraic[10] = (constants[2] == 0.0)?computedConstants[49]*(pow(constants[56], 3.0)*constants[58]*exp(0.03743*states[0]*constants[57])-pow(constants[59], 3.0)*constants[60]*exp(0.0374*states[0]*(constants[57]-1.0)))/(1.0+constants[61]*(constants[60]*pow(constants[59], 3.0)+constants[58]*pow(constants[56], 3.0))):computedConstants[49]*(pow(constants[56], 3.0)*constants[58]*exp(0.03743*states[0]*constants[57])-pow(constants[59], 3.0)*constants[60]*exp(0.03743*states[0]*(constants[57]-1.0)))/(1.0+constants[61]*(constants[60]*pow(constants[59], 3.0)+constants[58]*pow(constants[56], 3.0)));
    algebraic[9] = computedConstants[62]*pow(constants[56]/(constants[71]+constants[56]), 3.0)*pow(constants[69]/(constants[70]+constants[69]), 2.0)*1.6/(1.5+exp(-(states[0]+60.0)/40.0));
    algebraic[91] = (constants[2] == 0.0)?0.0952*exp(-0.063*(states[0]+34.4))/(1.0+1.66*exp(-0.225*(states[0]+63.7)))+0.0869:0.09518*exp(-0.06306*(states[0]+34.4))/(1.0+1.662*exp(-0.2251*(states[0]+63.7)))+0.08693;
    algebraic[88] = (1.0-algebraic[91])*states[2]+algebraic[91]*states[3];
    algebraic[7] = computedConstants[81]*pow(states[1], 3.0)*algebraic[88]*constants[59]*pow(constants[24], 2.0)/(constants[22]*constants[23])*(exp((states[0]-computedConstants[32])*constants[24]/(constants[22]*constants[23]))-1.0)/(exp(states[0]*constants[24]/(constants[22]*constants[23]))-1.0)*states[0];
    algebraic[89] = (constants[2] == 0.0)?pow(1.0/(1.0+exp(-states[0]/5.46)), 1.0/3.0):pow(1.0/(1.0+exp(-(states[0]+30.32)/5.46)), 1.0/3.0);
    algebraic[90] = (constants[2] == 0.0)?0.0006247/(0.832*exp(-0.335*(states[0]+56.7))+0.627*exp(0.082*(states[0]+65.01)))+4.0e-5:0.0006247/(0.8322166*exp(-0.33566*(states[0]+56.7062))+0.6274*exp(0.0823*(states[0]+65.0131)))+4.569e-5;
    algebraic[92] = 1.0/(1.0+exp((states[0]+66.1)/6.4));
    algebraic[94] = algebraic[92];
    algebraic[93] = 3.717e-6*exp(-0.2815*(states[0]+17.11))/(1.0+0.003732*exp(-0.3426*(states[0]+37.76)))+0.0005977;
    algebraic[95] = 3.186e-8*exp(-0.6219*(states[0]+18.8))/(1.0+7.189e-5*exp(-0.6683*(states[0]+34.07)))+0.003556;
    algebraic[21] = computedConstants[96]*(states[4]*states[5]+0.006/(1.0+exp(-(states[0]+14.1)/6.0)))*(states[0]-constants[103]);
    algebraic[106] = (constants[2] == 0.0)?-28.38*(states[0]+35.0)/(exp(-(states[0]+35.0)/2.5)-1.0)-84.9*states[0]/(exp(-0.208*states[0])-1.0):(constants[2] == 1.0)?-28.39*(states[0]+35.0)/(exp(-(states[0]+35.0)/2.5)-1.0)-84.9*states[0]/(exp(-0.208*states[0])-1.0):-28.4*(states[0]+35.0)/(exp(-(states[0]+35.0)/2.5)-1.0)-84.9*states[0]/(exp(-0.208*states[0])-1.0);
    algebraic[107] = (constants[2] == 1.0)?11.43*(states[0]-5.0)/(exp(0.4*(states[0]-5.0))-1.0):11.42*(states[0]-5.0)/(exp(0.4*(states[0]-5.0))-1.0);
    algebraic[105] = 2.0/(algebraic[106]+algebraic[107]);
    algebraic[104] = (constants[2] == 0.0)?1.0/(1.0+exp(-(states[0]+23.1)/6.0)):(constants[2] == 1.0)?1.0/(1.0+exp(-(states[0]+22.3+0.8*computedConstants[0])/6.0)):1.0/(1.0+exp(-(states[0]+22.2)/6.0));
    algebraic[110] = (constants[2] == 1.0)?3.75*(states[0]+28.0)/(exp((states[0]+28.0)/4.0)-1.0):3.12*(states[0]+28.0)/(exp((states[0]+28.0)/4.0)-1.0);
    algebraic[111] = (constants[2] == 1.0)?30.0/(1.0+exp(-(states[0]+28.0)/4.0)):25.0/(1.0+exp(-(states[0]+28.0)/4.0));
    algebraic[109] = (constants[2] == 1.0)?(1.2-0.2*computedConstants[0])/(algebraic[110]+algebraic[111]):1.0/(algebraic[110]+algebraic[111]);
    algebraic[108] = 1.0/(1.0+exp((states[0]+45.0)/5.0));
    algebraic[20] = computedConstants[112]*states[7]*states[6]*(states[0]-constants[119]);
    algebraic[122] = 1068.0*exp((states[0]+26.3)/30.0);
    algebraic[123] = 1068.0*exp(-(states[0]+26.3)/30.0);
    algebraic[121] = 1.0/(algebraic[122]+algebraic[123]);
    algebraic[120] = 1.0/(1.0+exp(-(states[0]+37.0)/6.8));
    algebraic[126] = (constants[2] == 1.0)?15.3*exp(-(states[0]+71.0+0.7*computedConstants[0])/83.3):15.3*exp(-(states[0]+71.7)/83.3);
    algebraic[127] = (constants[2] == 1.0)?15.0*exp((states[0]+71.0)/15.38):15.0*exp((states[0]+71.7)/15.38);
    algebraic[125] = 1.0/(algebraic[126]+algebraic[127]);
    algebraic[124] = 1.0/(1.0+exp((states[0]+71.0)/9.0));
    algebraic[19] = computedConstants[128]*states[9]*states[8]*(states[0]-computedConstants[40]);
    algebraic[18] = computedConstants[135]*states[8]*(states[0]-computedConstants[40]);
    algebraic[142] = 1.0/(1.0+exp((states[0]+59.37)/13.1));
    algebraic[143] = (constants[2] == 0.0)?0.0101+0.06517/(0.57*exp(-0.08*(states[0]+49.0)))+2.4e-5*exp(0.1*(states[0]+50.93)):(constants[2] == 1.0)?0.001/3.0*(30.31+195.5/(0.5686*exp(-0.08161*(states[0]+39.0+10.0*computedConstants[0]))+0.7174*exp((0.2719-0.1719*computedConstants[0])*1.0*(states[0]+40.93+10.0*computedConstants[0])))):0.0101+0.06517/(0.5686*exp(-0.08161*(states[0]+39.0))+0.7174*exp(0.2719*(states[0]+40.93)));
    algebraic[144] = 1.0/(1.0+exp(-(states[0]-10.93)/19.7));
    algebraic[145] = (constants[2] == 0.0)?0.001*(2.98+15.59/(1.037*exp(0.09*(states[0]+30.61))+0.369*exp(-0.12*(states[0]+23.84)))):(constants[2] == 1.0)?0.0025*(1.191+7.838/(1.037*exp(0.09012*(states[0]+30.61))+0.369*exp(-0.119*(states[0]+23.84)))):0.001*(2.98+19.59/(1.037*exp(0.09012*(states[0]+30.61))+0.369*exp(-0.119*(states[0]+23.84))));
    algebraic[153] = 0.6*states[11]+0.4*states[12];
    algebraic[17] = computedConstants[146]*algebraic[153]*states[10]*(states[0]-computedConstants[40]);
    algebraic[154] = (constants[2] != 2.0)?1.0/(1.0+exp(-(states[0]+14.2)/10.6)):1.0/(1.0+exp(-(states[0]+13.2)/10.6));
    algebraic[155] = (constants[2] != 2.0)?1.0/(37.2*exp((states[0]-9.0)/15.9)+0.96*exp(-(states[0]-9.0)/22.5)):1.0/(37.2*exp((states[0]-10.0)/15.9)+0.96*exp(-(states[0]-10.0)/22.5));
    algebraic[156] = algebraic[154];
    algebraic[157] = (constants[2] != 2.0)?1.0/(4.2*exp((states[0]-9.0)/17.0)+0.15*exp(-(states[0]-9.0)/21.6)):1.0/(4.2*exp((states[0]-10.0)/17.0)+0.15*exp(-(states[0]-10.0)/21.6));
    algebraic[159] = 1.0/(1.0+exp((states[0]+18.6)/10.1));
    algebraic[16] = computedConstants[160]*pow(states[13], 2.0)*(states[0]-computedConstants[80]);
    algebraic[167] = 14.0/(1.0+exp(-(states[0]-40.0)/9.0));
    algebraic[168] = 1.0*exp(-states[0]/45.0);
    algebraic[15] = (constants[2] != 2.0)?computedConstants[169]*states[14]*(states[0]-computedConstants[32]):computedConstants[169]*states[14]*(states[0]-77.6);
    algebraic[14] = (constants[2] != 2.0)?computedConstants[176]*states[14]*(states[0]-computedConstants[40]):computedConstants[176]*states[14]*(states[0]+102.0);
    algebraic[183] = (constants[2] == 0.0)?1.0*exp(-(states[0]+78.91)/26.62):1.0*exp(-(states[0]+78.91)/26.63);
    algebraic[184] = 1.0*exp((states[0]+75.13)/21.25);
}

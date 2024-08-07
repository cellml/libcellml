/* The content of this file was generated using the C profile of libCellML 0.5.0. */

#include "model.h"

#include <math.h>
#include <stdlib.h>

const char VERSION[] = "0.5.0";
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
    variables[1] = 0.0;
    variables[2] = 1.0;
    variables[3] = 1.0309347;
    variables[5] = 2.0e-5;
    variables[6] = 6.5e-5;
    variables[22] = 8314.0;
    variables[23] = 310.0;
    variables[24] = 96845.0;
    variables[26] = 5.8e-5;
    variables[27] = 0.000189;
    variables[28] = 5.8e-5;
    variables[29] = 0.000189;
    variables[30] = 5.81818e-5;
    variables[31] = 0.0001888;
    variables[34] = 2.52e-5;
    variables[35] = 8.19e-5;
    variables[36] = 2.52e-5;
    variables[37] = 8.19e-5;
    variables[38] = 2.523636e-5;
    variables[39] = 8.1892e-5;
    variables[42] = 1.32e-5;
    variables[43] = 4.3e-5;
    variables[44] = 1.323e-5;
    variables[45] = 4.29e-5;
    variables[46] = 1.3236e-5;
    variables[47] = 4.2952e-5;
    variables[50] = 2.7e-6;
    variables[51] = 8.8e-6;
    variables[52] = 2.8e-6;
    variables[53] = 8.8e-6;
    variables[54] = 2.7229e-6;
    variables[55] = 8.83584e-6;
    variables[56] = 8.0;
    variables[57] = 0.5;
    variables[58] = 2.0;
    variables[59] = 140.0;
    variables[60] = 0.0001;
    variables[61] = 0.0001;
    variables[63] = 0.0478;
    variables[64] = 0.16;
    variables[65] = 0.0478;
    variables[66] = 0.16;
    variables[67] = 0.04782545;
    variables[68] = 0.1551936;
    variables[69] = 5.4;
    variables[70] = 0.621;
    variables[71] = 5.64;
    variables[73] = 0.0;
    variables[74] = 0.0;
    variables[75] = 0.0042;
    variables[76] = 0.03339;
    variables[77] = 0.0;
    variables[78] = 0.0;
    variables[79] = 140.0;
    variables[82] = 0.0;
    variables[83] = 1.2e-6;
    variables[84] = 0.0;
    variables[85] = 3.7e-7;
    variables[86] = 0.0;
    variables[87] = 1.204e-6;
    variables[97] = 0.0058;
    variables[98] = 0.0659;
    variables[99] = 0.0082;
    variables[100] = 0.0659;
    variables[101] = 0.0057938;
    variables[102] = 0.06588648;
    variables[103] = 46.4;
    variables[113] = 0.0043;
    variables[114] = 0.0139;
    variables[115] = 0.0021;
    variables[116] = 0.00694;
    variables[117] = 0.00427806;
    variables[118] = 0.0138823;
    variables[119] = 45.0;
    variables[129] = 0.00491;
    variables[130] = 0.03649;
    variables[131] = 0.004905;
    variables[132] = 0.0365;
    variables[133] = 0.004905;
    variables[134] = 0.036495;
    variables[136] = 6.65e-5;
    variables[137] = 0.0114;
    variables[138] = 0.000266;
    variables[139] = 0.0114;
    variables[140] = 6.645504e-5;
    variables[141] = 0.01138376;
    variables[147] = 0.000797;
    variables[148] = 0.016;
    variables[149] = 0.000738;
    variables[150] = 0.0208;
    variables[151] = 0.00079704;
    variables[152] = 0.016;
    variables[161] = 0.000518;
    variables[162] = 0.0104;
    variables[163] = 0.000345;
    variables[164] = 0.0104;
    variables[165] = 0.0003445;
    variables[166] = 0.0104;
    variables[170] = 0.000548;
    variables[171] = 0.0069;
    variables[172] = 0.000437;
    variables[173] = 0.0055;
    variables[174] = 0.0005465;
    variables[175] = 0.006875;
    variables[177] = 0.000548;
    variables[178] = 0.0069;
    variables[179] = 0.000437;
    variables[180] = 0.0055;
    variables[181] = 0.0005465;
    variables[182] = 0.006875;
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

void computeComputedConstants(double *computedConstants)
{
    variables[0] = (variables[2] == 0.0)?1.07*(3.0*variables[1]-0.1)/(3.0*(1.0+0.7745*exp(-(3.0*variables[1]-2.05)/0.295))):(variables[2] == 1.0)?variables[3]*variables[1]/(1.0+0.7745*exp(-(3.0*variables[1]-2.05)/0.295)):1.07*29.0*variables[1]/(30.0*(1.0+0.7745*exp(-(29.0*variables[1]-24.5)/1.95)));
    variables[4] = variables[5]+variables[0]*(variables[6]-variables[5]);
    variables[25] = (variables[2] == 0.0)?variables[26]+variables[0]*(variables[27]-variables[26]):(variables[2] == 1.0)?variables[30]+variables[0]*(variables[31]-variables[30]):variables[28]+variables[0]*(variables[29]-variables[28]);
    variables[33] = (variables[2] == 0.0)?variables[34]+variables[0]*(variables[35]-variables[34]):(variables[2] == 1.0)?variables[38]+variables[0]*(variables[39]-variables[38]):variables[36]+variables[0]*(variables[37]-variables[36]);
    variables[41] = (variables[2] == 0.0)?variables[42]+variables[0]*(variables[43]-variables[42]):(variables[2] == 1.0)?variables[46]+variables[0]*(variables[47]-variables[46]):variables[44]+variables[0]*(variables[45]-variables[44]);
    variables[49] = (variables[2] == 0.0)?variables[50]+variables[0]*(variables[51]-variables[50]):(variables[2] == 1.0)?variables[54]+variables[0]*(variables[55]-variables[54]):variables[52]+variables[0]*(variables[53]-variables[52]);
    variables[62] = (variables[2] == 0.0)?variables[63]+variables[0]*(variables[64]-variables[63]):(variables[2] == 1.0)?variables[67]+variables[0]*(variables[68]-variables[67]):variables[65]+variables[0]*(variables[66]-variables[65]);
    variables[72] = (variables[2] == 0.0)?variables[73]+variables[0]*(variables[74]-variables[73]):(variables[2] == 1.0)?variables[77]+variables[0]*(variables[78]-variables[77]):variables[75]+variables[0]*(variables[76]-variables[75]);
    variables[8] = variables[72]*variables[60]/(variables[60]+0.0004);
    variables[32] = variables[22]*variables[23]/variables[24]*log(variables[59]/variables[56]);
    variables[40] = variables[22]*variables[23]/variables[24]*log(variables[69]/variables[79]);
    variables[48] = variables[22]*variables[23]/(2.0*variables[24])*log(variables[58]/variables[60]);
    variables[80] = (variables[2] == 0.0)?variables[22]*variables[23]/variables[24]*log((variables[69]+0.12*variables[59])/(variables[79]+0.12*variables[56])):variables[22]*variables[23]/variables[24]*log((variables[69]+0.03*variables[59])/(variables[79]+0.03*variables[56]));
    variables[81] = (variables[2] == 0.0)?variables[82]+variables[0]*(variables[83]-variables[82]):(variables[2] == 1.0)?variables[86]+variables[0]*(variables[87]-variables[86]):variables[84]+variables[0]*(variables[85]-variables[84]);
    variables[96] = (variables[2] == 0.0)?variables[97]+variables[0]*(variables[98]-variables[97]):(variables[2] == 1.0)?variables[101]+variables[0]*(variables[102]-variables[101]):variables[99]+variables[0]*(variables[100]-variables[99]);
    variables[112] = (variables[2] == 0.0)?variables[113]+variables[0]*(variables[114]-variables[113]):(variables[2] == 1.0)?variables[117]+variables[0]*(variables[118]-variables[117]):variables[115]+variables[0]*(variables[116]-variables[115]);
    variables[128] = (variables[2] == 0.0)?variables[129]+variables[0]*(variables[130]-variables[129]):(variables[2] == 1.0)?variables[133]+variables[0]*(variables[134]-variables[133]):variables[131]+variables[0]*(variables[132]-variables[131]);
    variables[135] = (variables[2] == 0.0)?variables[136]+variables[0]*(variables[137]-variables[136]):(variables[2] == 1.0)?variables[140]+variables[0]*(variables[141]-variables[140]):variables[138]+variables[0]*(variables[139]-variables[138]);
    variables[146] = (variables[2] == 0.0)?variables[147]+variables[0]*(variables[148]-variables[147]):(variables[2] == 1.0)?variables[151]+variables[0]*(variables[152]-variables[151]):variables[149]+variables[0]*(variables[150]-variables[149]);
    variables[158] = (variables[2] == 0.0)?0.002:(variables[2] == 1.0)?0.002:0.006;
    variables[160] = (variables[2] == 0.0)?variables[161]+variables[0]*(variables[162]-variables[161]):(variables[2] == 1.0)?variables[165]+variables[0]*(variables[166]-variables[165]):variables[163]+variables[0]*(variables[164]-variables[163]);
    variables[169] = (variables[2] == 0.0)?variables[170]+variables[0]*(variables[171]-variables[170]):(variables[2] == 1.0)?variables[174]+variables[0]*(variables[175]-variables[174]):variables[172]+variables[0]*(variables[173]-variables[172]);
    variables[176] = (variables[2] == 0.0)?variables[177]+variables[0]*(variables[178]-variables[177]):(variables[2] == 1.0)?variables[181]+variables[0]*(variables[182]-variables[181]):variables[179]+variables[0]*(variables[180]-variables[179]);
}

void computeRates(double voi, double *states, double *rates, double *variables)
{
    variables[9] = variables[62]*pow(variables[56]/(variables[71]+variables[56]), 3.0)*pow(variables[69]/(variables[70]+variables[69]), 2.0)*1.6/(1.5+exp(-(states[0]+60.0)/40.0));
    variables[10] = (variables[2] == 0.0)?variables[49]*(pow(variables[56], 3.0)*variables[58]*exp(0.03743*states[0]*variables[57])-pow(variables[59], 3.0)*variables[60]*exp(0.0374*states[0]*(variables[57]-1.0)))/(1.0+variables[61]*(variables[60]*pow(variables[59], 3.0)+variables[58]*pow(variables[56], 3.0))):variables[49]*(pow(variables[56], 3.0)*variables[58]*exp(0.03743*states[0]*variables[57])-pow(variables[59], 3.0)*variables[60]*exp(0.03743*states[0]*(variables[57]-1.0)))/(1.0+variables[61]*(variables[60]*pow(variables[59], 3.0)+variables[58]*pow(variables[56], 3.0)));
    variables[14] = (variables[2] != 2.0)?variables[176]*states[14]*(states[0]-variables[40]):variables[176]*states[14]*(states[0]+102.0);
    variables[15] = (variables[2] != 2.0)?variables[169]*states[14]*(states[0]-variables[32]):variables[169]*states[14]*(states[0]-77.6);
    variables[16] = variables[160]*pow(states[13], 2.0)*(states[0]-variables[80]);
    variables[18] = variables[135]*states[8]*(states[0]-variables[40]);
    variables[19] = variables[128]*states[9]*states[8]*(states[0]-variables[40]);
    variables[20] = variables[112]*states[7]*states[6]*(states[0]-variables[119]);
    variables[21] = variables[96]*(states[4]*states[5]+0.006/(1.0+exp(-(states[0]+14.1)/6.0)))*(states[0]-variables[103]);
    variables[91] = (variables[2] == 0.0)?0.0952*exp(-0.063*(states[0]+34.4))/(1.0+1.66*exp(-0.225*(states[0]+63.7)))+0.0869:0.09518*exp(-0.06306*(states[0]+34.4))/(1.0+1.662*exp(-0.2251*(states[0]+63.7)))+0.08693;
    variables[88] = (1.0-variables[91])*states[2]+variables[91]*states[3];
    variables[7] = variables[81]*pow(states[1], 3.0)*variables[88]*variables[59]*pow(variables[24], 2.0)/(variables[22]*variables[23])*(exp((states[0]-variables[32])*variables[24]/(variables[22]*variables[23]))-1.0)/(exp(states[0]*variables[24]/(variables[22]*variables[23]))-1.0)*states[0];
    variables[11] = variables[33]*(states[0]-variables[40]);
    variables[12] = variables[41]*(states[0]-variables[48]);
    variables[13] = variables[25]*(states[0]-variables[32]);
    variables[153] = 0.6*states[11]+0.4*states[12];
    variables[17] = variables[146]*variables[153]*states[10]*(states[0]-variables[40]);
    rates[0] = -1.0/variables[4]*(variables[7]+variables[21]+variables[20]+variables[19]+variables[18]+variables[17]+variables[16]+variables[15]+variables[14]+variables[13]+variables[12]+variables[11]+variables[10]+variables[9]+variables[8]);
    variables[89] = (variables[2] == 0.0)?pow(1.0/(1.0+exp(-states[0]/5.46)), 1.0/3.0):pow(1.0/(1.0+exp(-(states[0]+30.32)/5.46)), 1.0/3.0);
    variables[90] = (variables[2] == 0.0)?0.0006247/(0.832*exp(-0.335*(states[0]+56.7))+0.627*exp(0.082*(states[0]+65.01)))+4.0e-5:0.0006247/(0.8322166*exp(-0.33566*(states[0]+56.7062))+0.6274*exp(0.0823*(states[0]+65.0131)))+4.569e-5;
    rates[1] = (variables[89]-states[1])/variables[90];
    variables[92] = 1.0/(1.0+exp((states[0]+66.1)/6.4));
    variables[93] = 3.717e-6*exp(-0.2815*(states[0]+17.11))/(1.0+0.003732*exp(-0.3426*(states[0]+37.76)))+0.0005977;
    rates[2] = (variables[92]-states[2])/variables[93];
    variables[94] = variables[92];
    variables[95] = 3.186e-8*exp(-0.6219*(states[0]+18.8))/(1.0+7.189e-5*exp(-0.6683*(states[0]+34.07)))+0.003556;
    rates[3] = (variables[94]-states[3])/variables[95];
    variables[104] = (variables[2] == 0.0)?1.0/(1.0+exp(-(states[0]+23.1)/6.0)):(variables[2] == 1.0)?1.0/(1.0+exp(-(states[0]+22.3+0.8*variables[0])/6.0)):1.0/(1.0+exp(-(states[0]+22.2)/6.0));
    variables[106] = (variables[2] == 0.0)?-28.38*(states[0]+35.0)/(exp(-(states[0]+35.0)/2.5)-1.0)-84.9*states[0]/(exp(-0.208*states[0])-1.0):(variables[2] == 1.0)?-28.39*(states[0]+35.0)/(exp(-(states[0]+35.0)/2.5)-1.0)-84.9*states[0]/(exp(-0.208*states[0])-1.0):-28.4*(states[0]+35.0)/(exp(-(states[0]+35.0)/2.5)-1.0)-84.9*states[0]/(exp(-0.208*states[0])-1.0);
    variables[107] = (variables[2] == 1.0)?11.43*(states[0]-5.0)/(exp(0.4*(states[0]-5.0))-1.0):11.42*(states[0]-5.0)/(exp(0.4*(states[0]-5.0))-1.0);
    variables[105] = 2.0/(variables[106]+variables[107]);
    rates[5] = (variables[104]-states[5])/variables[105];
    variables[108] = 1.0/(1.0+exp((states[0]+45.0)/5.0));
    variables[110] = (variables[2] == 1.0)?3.75*(states[0]+28.0)/(exp((states[0]+28.0)/4.0)-1.0):3.12*(states[0]+28.0)/(exp((states[0]+28.0)/4.0)-1.0);
    variables[111] = (variables[2] == 1.0)?30.0/(1.0+exp(-(states[0]+28.0)/4.0)):25.0/(1.0+exp(-(states[0]+28.0)/4.0));
    variables[109] = (variables[2] == 1.0)?(1.2-0.2*variables[0])/(variables[110]+variables[111]):1.0/(variables[110]+variables[111]);
    rates[4] = (variables[108]-states[4])/variables[109];
    variables[120] = 1.0/(1.0+exp(-(states[0]+37.0)/6.8));
    variables[122] = 1068.0*exp((states[0]+26.3)/30.0);
    variables[123] = 1068.0*exp(-(states[0]+26.3)/30.0);
    variables[121] = 1.0/(variables[122]+variables[123]);
    rates[7] = (variables[120]-states[7])/variables[121];
    variables[124] = 1.0/(1.0+exp((states[0]+71.0)/9.0));
    variables[126] = (variables[2] == 1.0)?15.3*exp(-(states[0]+71.0+0.7*variables[0])/83.3):15.3*exp(-(states[0]+71.7)/83.3);
    variables[127] = (variables[2] == 1.0)?15.0*exp((states[0]+71.0)/15.38):15.0*exp((states[0]+71.7)/15.38);
    variables[125] = 1.0/(variables[126]+variables[127]);
    rates[6] = (variables[124]-states[6])/variables[125];
    variables[142] = 1.0/(1.0+exp((states[0]+59.37)/13.1));
    variables[143] = (variables[2] == 0.0)?0.0101+0.06517/(0.57*exp(-0.08*(states[0]+49.0)))+2.4e-5*exp(0.1*(states[0]+50.93)):(variables[2] == 1.0)?0.001/3.0*(30.31+195.5/(0.5686*exp(-0.08161*(states[0]+39.0+10.0*variables[0]))+0.7174*exp((0.2719-0.1719*variables[0])*1.0*(states[0]+40.93+10.0*variables[0])))):0.0101+0.06517/(0.5686*exp(-0.08161*(states[0]+39.0))+0.7174*exp(0.2719*(states[0]+40.93)));
    rates[9] = (variables[142]-states[9])/variables[143];
    variables[144] = 1.0/(1.0+exp(-(states[0]-10.93)/19.7));
    variables[145] = (variables[2] == 0.0)?0.001*(2.98+15.59/(1.037*exp(0.09*(states[0]+30.61))+0.369*exp(-0.12*(states[0]+23.84)))):(variables[2] == 1.0)?0.0025*(1.191+7.838/(1.037*exp(0.09012*(states[0]+30.61))+0.369*exp(-0.119*(states[0]+23.84)))):0.001*(2.98+19.59/(1.037*exp(0.09012*(states[0]+30.61))+0.369*exp(-0.119*(states[0]+23.84))));
    rates[8] = (variables[144]-states[8])/variables[145];
    variables[154] = (variables[2] != 2.0)?1.0/(1.0+exp(-(states[0]+14.2)/10.6)):1.0/(1.0+exp(-(states[0]+13.2)/10.6));
    variables[155] = (variables[2] != 2.0)?1.0/(37.2*exp((states[0]-9.0)/15.9)+0.96*exp(-(states[0]-9.0)/22.5)):1.0/(37.2*exp((states[0]-10.0)/15.9)+0.96*exp(-(states[0]-10.0)/22.5));
    rates[11] = (variables[154]-states[11])/variables[155];
    variables[156] = variables[154];
    variables[157] = (variables[2] != 2.0)?1.0/(4.2*exp((states[0]-9.0)/17.0)+0.15*exp(-(states[0]-9.0)/21.6)):1.0/(4.2*exp((states[0]-10.0)/17.0)+0.15*exp(-(states[0]-10.0)/21.6));
    rates[12] = (variables[156]-states[12])/variables[157];
    variables[159] = 1.0/(1.0+exp((states[0]+18.6)/10.1));
    rates[10] = (variables[159]-states[10])/variables[158];
    variables[167] = 14.0/(1.0+exp(-(states[0]-40.0)/9.0));
    variables[168] = 1.0*exp(-states[0]/45.0);
    rates[13] = variables[167]*(1.0-states[13])-variables[168]*states[13];
    variables[183] = (variables[2] == 0.0)?1.0*exp(-(states[0]+78.91)/26.62):1.0*exp(-(states[0]+78.91)/26.63);
    variables[184] = 1.0*exp((states[0]+75.13)/21.25);
    rates[14] = variables[183]*(1.0-states[14])-variables[184]*states[14];
}

void computeVariables(double voi, double *states, double *rates, double *variables)
{
    variables[13] = variables[25]*(states[0]-variables[32]);
    variables[11] = variables[33]*(states[0]-variables[40]);
    variables[12] = variables[41]*(states[0]-variables[48]);
    variables[10] = (variables[2] == 0.0)?variables[49]*(pow(variables[56], 3.0)*variables[58]*exp(0.03743*states[0]*variables[57])-pow(variables[59], 3.0)*variables[60]*exp(0.0374*states[0]*(variables[57]-1.0)))/(1.0+variables[61]*(variables[60]*pow(variables[59], 3.0)+variables[58]*pow(variables[56], 3.0))):variables[49]*(pow(variables[56], 3.0)*variables[58]*exp(0.03743*states[0]*variables[57])-pow(variables[59], 3.0)*variables[60]*exp(0.03743*states[0]*(variables[57]-1.0)))/(1.0+variables[61]*(variables[60]*pow(variables[59], 3.0)+variables[58]*pow(variables[56], 3.0)));
    variables[9] = variables[62]*pow(variables[56]/(variables[71]+variables[56]), 3.0)*pow(variables[69]/(variables[70]+variables[69]), 2.0)*1.6/(1.5+exp(-(states[0]+60.0)/40.0));
    variables[91] = (variables[2] == 0.0)?0.0952*exp(-0.063*(states[0]+34.4))/(1.0+1.66*exp(-0.225*(states[0]+63.7)))+0.0869:0.09518*exp(-0.06306*(states[0]+34.4))/(1.0+1.662*exp(-0.2251*(states[0]+63.7)))+0.08693;
    variables[88] = (1.0-variables[91])*states[2]+variables[91]*states[3];
    variables[7] = variables[81]*pow(states[1], 3.0)*variables[88]*variables[59]*pow(variables[24], 2.0)/(variables[22]*variables[23])*(exp((states[0]-variables[32])*variables[24]/(variables[22]*variables[23]))-1.0)/(exp(states[0]*variables[24]/(variables[22]*variables[23]))-1.0)*states[0];
    variables[89] = (variables[2] == 0.0)?pow(1.0/(1.0+exp(-states[0]/5.46)), 1.0/3.0):pow(1.0/(1.0+exp(-(states[0]+30.32)/5.46)), 1.0/3.0);
    variables[90] = (variables[2] == 0.0)?0.0006247/(0.832*exp(-0.335*(states[0]+56.7))+0.627*exp(0.082*(states[0]+65.01)))+4.0e-5:0.0006247/(0.8322166*exp(-0.33566*(states[0]+56.7062))+0.6274*exp(0.0823*(states[0]+65.0131)))+4.569e-5;
    variables[92] = 1.0/(1.0+exp((states[0]+66.1)/6.4));
    variables[94] = variables[92];
    variables[93] = 3.717e-6*exp(-0.2815*(states[0]+17.11))/(1.0+0.003732*exp(-0.3426*(states[0]+37.76)))+0.0005977;
    variables[95] = 3.186e-8*exp(-0.6219*(states[0]+18.8))/(1.0+7.189e-5*exp(-0.6683*(states[0]+34.07)))+0.003556;
    variables[21] = variables[96]*(states[4]*states[5]+0.006/(1.0+exp(-(states[0]+14.1)/6.0)))*(states[0]-variables[103]);
    variables[106] = (variables[2] == 0.0)?-28.38*(states[0]+35.0)/(exp(-(states[0]+35.0)/2.5)-1.0)-84.9*states[0]/(exp(-0.208*states[0])-1.0):(variables[2] == 1.0)?-28.39*(states[0]+35.0)/(exp(-(states[0]+35.0)/2.5)-1.0)-84.9*states[0]/(exp(-0.208*states[0])-1.0):-28.4*(states[0]+35.0)/(exp(-(states[0]+35.0)/2.5)-1.0)-84.9*states[0]/(exp(-0.208*states[0])-1.0);
    variables[107] = (variables[2] == 1.0)?11.43*(states[0]-5.0)/(exp(0.4*(states[0]-5.0))-1.0):11.42*(states[0]-5.0)/(exp(0.4*(states[0]-5.0))-1.0);
    variables[105] = 2.0/(variables[106]+variables[107]);
    variables[104] = (variables[2] == 0.0)?1.0/(1.0+exp(-(states[0]+23.1)/6.0)):(variables[2] == 1.0)?1.0/(1.0+exp(-(states[0]+22.3+0.8*variables[0])/6.0)):1.0/(1.0+exp(-(states[0]+22.2)/6.0));
    variables[110] = (variables[2] == 1.0)?3.75*(states[0]+28.0)/(exp((states[0]+28.0)/4.0)-1.0):3.12*(states[0]+28.0)/(exp((states[0]+28.0)/4.0)-1.0);
    variables[111] = (variables[2] == 1.0)?30.0/(1.0+exp(-(states[0]+28.0)/4.0)):25.0/(1.0+exp(-(states[0]+28.0)/4.0));
    variables[109] = (variables[2] == 1.0)?(1.2-0.2*variables[0])/(variables[110]+variables[111]):1.0/(variables[110]+variables[111]);
    variables[108] = 1.0/(1.0+exp((states[0]+45.0)/5.0));
    variables[20] = variables[112]*states[7]*states[6]*(states[0]-variables[119]);
    variables[122] = 1068.0*exp((states[0]+26.3)/30.0);
    variables[123] = 1068.0*exp(-(states[0]+26.3)/30.0);
    variables[121] = 1.0/(variables[122]+variables[123]);
    variables[120] = 1.0/(1.0+exp(-(states[0]+37.0)/6.8));
    variables[126] = (variables[2] == 1.0)?15.3*exp(-(states[0]+71.0+0.7*variables[0])/83.3):15.3*exp(-(states[0]+71.7)/83.3);
    variables[127] = (variables[2] == 1.0)?15.0*exp((states[0]+71.0)/15.38):15.0*exp((states[0]+71.7)/15.38);
    variables[125] = 1.0/(variables[126]+variables[127]);
    variables[124] = 1.0/(1.0+exp((states[0]+71.0)/9.0));
    variables[19] = variables[128]*states[9]*states[8]*(states[0]-variables[40]);
    variables[18] = variables[135]*states[8]*(states[0]-variables[40]);
    variables[142] = 1.0/(1.0+exp((states[0]+59.37)/13.1));
    variables[143] = (variables[2] == 0.0)?0.0101+0.06517/(0.57*exp(-0.08*(states[0]+49.0)))+2.4e-5*exp(0.1*(states[0]+50.93)):(variables[2] == 1.0)?0.001/3.0*(30.31+195.5/(0.5686*exp(-0.08161*(states[0]+39.0+10.0*variables[0]))+0.7174*exp((0.2719-0.1719*variables[0])*1.0*(states[0]+40.93+10.0*variables[0])))):0.0101+0.06517/(0.5686*exp(-0.08161*(states[0]+39.0))+0.7174*exp(0.2719*(states[0]+40.93)));
    variables[144] = 1.0/(1.0+exp(-(states[0]-10.93)/19.7));
    variables[145] = (variables[2] == 0.0)?0.001*(2.98+15.59/(1.037*exp(0.09*(states[0]+30.61))+0.369*exp(-0.12*(states[0]+23.84)))):(variables[2] == 1.0)?0.0025*(1.191+7.838/(1.037*exp(0.09012*(states[0]+30.61))+0.369*exp(-0.119*(states[0]+23.84)))):0.001*(2.98+19.59/(1.037*exp(0.09012*(states[0]+30.61))+0.369*exp(-0.119*(states[0]+23.84))));
    variables[153] = 0.6*states[11]+0.4*states[12];
    variables[17] = variables[146]*variables[153]*states[10]*(states[0]-variables[40]);
    variables[154] = (variables[2] != 2.0)?1.0/(1.0+exp(-(states[0]+14.2)/10.6)):1.0/(1.0+exp(-(states[0]+13.2)/10.6));
    variables[155] = (variables[2] != 2.0)?1.0/(37.2*exp((states[0]-9.0)/15.9)+0.96*exp(-(states[0]-9.0)/22.5)):1.0/(37.2*exp((states[0]-10.0)/15.9)+0.96*exp(-(states[0]-10.0)/22.5));
    variables[156] = variables[154];
    variables[157] = (variables[2] != 2.0)?1.0/(4.2*exp((states[0]-9.0)/17.0)+0.15*exp(-(states[0]-9.0)/21.6)):1.0/(4.2*exp((states[0]-10.0)/17.0)+0.15*exp(-(states[0]-10.0)/21.6));
    variables[159] = 1.0/(1.0+exp((states[0]+18.6)/10.1));
    variables[16] = variables[160]*pow(states[13], 2.0)*(states[0]-variables[80]);
    variables[167] = 14.0/(1.0+exp(-(states[0]-40.0)/9.0));
    variables[168] = 1.0*exp(-states[0]/45.0);
    variables[15] = (variables[2] != 2.0)?variables[169]*states[14]*(states[0]-variables[32]):variables[169]*states[14]*(states[0]-77.6);
    variables[14] = (variables[2] != 2.0)?variables[176]*states[14]*(states[0]-variables[40]):variables[176]*states[14]*(states[0]+102.0);
    variables[183] = (variables[2] == 0.0)?1.0*exp(-(states[0]+78.91)/26.62):1.0*exp(-(states[0]+78.91)/26.63);
    variables[184] = 1.0*exp((states[0]+75.13)/21.25);
}

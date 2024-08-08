/* The content of this file was generated using the C profile of libCellML 0.5.0. */

#include "model.h"

#include <math.h>
#include <stdlib.h>

const char VERSION[] = "0.6.0";
const char LIBCELLML_VERSION[] = "0.5.0";

const size_t STATE_COUNT = 33;
const size_t CONSTANT_COUNT = 91;
const size_t COMPUTED_CONSTANT_COUNT = 25;
const size_t ALGEBRAIC_COUNT = 101;

const VariableInfo VOI_INFO = {"time", "second", "environment", VARIABLE_OF_INTEGRATION};

const VariableInfo STATE_INFO[] = {
    {"Ca_sub", "millimolar", "Ca_dynamics", STATE},
    {"Nai_", "millimolar", "Nai_concentration", STATE},
    {"Ca_jsr", "millimolar", "Ca_dynamics", STATE},
    {"O", "dimensionless", "Ca_SR_release", STATE},
    {"R", "dimensionless", "Ca_SR_release", STATE},
    {"RI", "dimensionless", "Ca_SR_release", STATE},
    {"I", "dimensionless", "Ca_SR_release", STATE},
    {"Cai", "millimolar", "Ca_dynamics", STATE},
    {"Ca_nsr", "millimolar", "Ca_dynamics", STATE},
    {"fTC", "dimensionless", "Ca_buffering", STATE},
    {"fTMC", "dimensionless", "Ca_buffering", STATE},
    {"fTMM", "dimensionless", "Ca_buffering", STATE},
    {"fCMi", "dimensionless", "Ca_buffering", STATE},
    {"fCMs", "dimensionless", "Ca_buffering", STATE},
    {"fCQ", "dimensionless", "Ca_buffering", STATE},
    {"V_ode", "millivolt", "Membrane", STATE},
    {"y", "dimensionless", "i_f_y_gate", STATE},
    {"h", "dimensionless", "i_Na_h_gate", STATE},
    {"m", "dimensionless", "i_Na_m_gate", STATE},
    {"s_Kur", "dimensionless", "i_Kur_sKur_gate", STATE},
    {"r_Kur", "dimensionless", "i_Kur_rKur_gate", STATE},
    {"fCa", "dimensionless", "i_CaL_fCa_gate", STATE},
    {"fL", "dimensionless", "i_CaL_fL_gate", STATE},
    {"dL", "dimensionless", "i_CaL_dL_gate", STATE},
    {"fT", "dimensionless", "i_CaT_fT_gate", STATE},
    {"dT", "dimensionless", "i_CaT_dT_gate", STATE},
    {"r", "dimensionless", "i_to_r_gate", STATE},
    {"q", "dimensionless", "i_to_q_gate", STATE},
    {"piy", "dimensionless", "i_Kr_pi_gate", STATE},
    {"paF", "dimensionless", "i_Kr_pa_gate", STATE},
    {"paS", "dimensionless", "i_Kr_pa_gate", STATE},
    {"n", "dimensionless", "i_Ks_n_gate", STATE},
    {"a", "dimensionless", "i_KACh_a_gate", STATE}
};

const VariableInfo VARIABLE_INFO[] = {
    {"ACh", "millimolar", "Rate_modulation_experiments", CONSTANT},
    {"Iso_1_uM", "dimensionless", "Rate_modulation_experiments", CONSTANT},
    {"Nao", "millimolar", "Ionic_values", CONSTANT},
    {"Ko", "millimolar", "Ionic_values", CONSTANT},
    {"Ki", "millimolar", "Ionic_values", CONSTANT},
    {"Cao", "millimolar", "Ionic_values", CONSTANT},
    {"Nai_clamp", "dimensionless", "Nai_concentration", CONSTANT},
    {"F", "coulomb_per_mole", "Membrane", CONSTANT},
    {"Km_Nap", "millimolar", "i_NaK", CONSTANT},
    {"Km_Kp", "millimolar", "i_NaK", CONSTANT},
    {"i_NaK_max", "nanoA", "i_NaK", CONSTANT},
    {"blockade_NaCa", "dimensionless", "i_NaCa", CONSTANT},
    {"K_NaCa", "nanoA", "i_NaCa", CONSTANT},
    {"K3ni", "millimolar", "i_NaCa", CONSTANT},
    {"Kci", "millimolar", "i_NaCa", CONSTANT},
    {"Qci", "dimensionless", "i_NaCa", CONSTANT},
    {"K1ni", "millimolar", "i_NaCa", CONSTANT},
    {"K2ni", "millimolar", "i_NaCa", CONSTANT},
    {"Qn", "dimensionless", "i_NaCa", CONSTANT},
    {"Kcni", "millimolar", "i_NaCa", CONSTANT},
    {"K3no", "millimolar", "i_NaCa", CONSTANT},
    {"Kco", "millimolar", "i_NaCa", CONSTANT},
    {"Qco", "dimensionless", "i_NaCa", CONSTANT},
    {"K1no", "millimolar", "i_NaCa", CONSTANT},
    {"K2no", "millimolar", "i_NaCa", CONSTANT},
    {"ks", "per_second", "Ca_SR_release", CONSTANT},
    {"MaxSR", "dimensionless", "Ca_SR_release", CONSTANT},
    {"MinSR", "dimensionless", "Ca_SR_release", CONSTANT},
    {"EC50_SR", "millimolar", "Ca_SR_release", CONSTANT},
    {"HSR", "dimensionless", "Ca_SR_release", CONSTANT},
    {"koCa", "per_millimolar2_second", "Ca_SR_release", CONSTANT},
    {"kiCa", "per_millimolar_second", "Ca_SR_release", CONSTANT},
    {"kim", "per_second", "Ca_SR_release", CONSTANT},
    {"kom", "per_second", "Ca_SR_release", CONSTANT},
    {"P_up_basal", "millimolar_per_second", "Ca_intracellular_fluxes", CONSTANT},
    {"tau_dif_Ca", "second", "Ca_intracellular_fluxes", CONSTANT},
    {"K_up", "millimolar", "Ca_intracellular_fluxes", CONSTANT},
    {"slope_up", "millimolar", "Ca_intracellular_fluxes", CONSTANT},
    {"tau_tr", "second", "Ca_intracellular_fluxes", CONSTANT},
    {"kf_TC", "per_millimolar_second", "Ca_buffering", CONSTANT},
    {"kb_TC", "per_second", "Ca_buffering", CONSTANT},
    {"kf_TMC", "per_millimolar_second", "Ca_buffering", CONSTANT},
    {"kb_TMC", "per_second", "Ca_buffering", CONSTANT},
    {"kf_TMM", "per_millimolar_second", "Ca_buffering", CONSTANT},
    {"Mgi", "millimolar", "Ca_buffering", CONSTANT},
    {"kb_TMM", "per_second", "Ca_buffering", CONSTANT},
    {"kf_CM", "per_millimolar_second", "Ca_buffering", CONSTANT},
    {"kb_CM", "per_second", "Ca_buffering", CONSTANT},
    {"kf_CQ", "per_millimolar_second", "Ca_buffering", CONSTANT},
    {"kb_CQ", "per_second", "Ca_buffering", CONSTANT},
    {"TC_tot", "millimolar", "Ca_buffering", CONSTANT},
    {"TMC_tot", "millimolar", "Ca_buffering", CONSTANT},
    {"CM_tot", "millimolar", "Ca_buffering", CONSTANT},
    {"CQ_tot", "millimolar", "Ca_buffering", CONSTANT},
    {"L_cell", "micrometre", "Cell_parameters", CONSTANT},
    {"R_cell", "micrometre", "Cell_parameters", CONSTANT},
    {"L_sub", "micrometre", "Cell_parameters", CONSTANT},
    {"V_jsr_part", "dimensionless", "Cell_parameters", CONSTANT},
    {"V_i_part", "dimensionless", "Cell_parameters", CONSTANT},
    {"V_nsr_part", "dimensionless", "Cell_parameters", CONSTANT},
    {"C", "microF", "Membrane", CONSTANT},
    {"R", "joule_per_kilomole_kelvin", "Membrane", CONSTANT},
    {"T", "kelvin", "Membrane", CONSTANT},
    {"clamp_mode", "dimensionless", "Membrane", CONSTANT},
    {"V_test", "millivolt", "Voltage_clamp", CONSTANT},
    {"t_holding", "second", "Voltage_clamp", CONSTANT},
    {"t_test", "second", "Voltage_clamp", CONSTANT},
    {"V_holding", "millivolt", "Voltage_clamp", CONSTANT},
    {"g_f", "microS", "i_f", CONSTANT},
    {"Km_f", "millimolar", "i_f", CONSTANT},
    {"alpha", "dimensionless", "i_f", CONSTANT},
    {"blockade", "dimensionless", "i_f", CONSTANT},
    {"y_shift", "millivolt", "i_f_y_gate", CONSTANT},
    {"g_Na", "microS", "i_Na", CONSTANT},
    {"g_Na_L", "microS", "i_Na", CONSTANT},
    {"delta_m", "millivolt", "i_Na_m_gate", CONSTANT},
    {"g_Kur", "microS", "i_Kur", CONSTANT},
    {"P_CaL", "nanoA_per_millimolar", "i_CaL", CONSTANT},
    {"V_dL", "millivolt", "i_CaL_dL_gate", CONSTANT},
    {"k_dL", "millivolt", "i_CaL_dL_gate", CONSTANT},
    {"shift_fL", "millivolt", "i_CaL_fL_gate", CONSTANT},
    {"k_fL", "millivolt", "i_CaL_fL_gate", CONSTANT},
    {"Km_fCa", "millimolar", "i_CaL_fCa_gate", CONSTANT},
    {"alpha_fCa", "per_second", "i_CaL_fCa_gate", CONSTANT},
    {"P_CaT", "nanoA_per_millimolar", "i_CaT", CONSTANT},
    {"offset_fT", "second", "i_CaT_fT_gate", CONSTANT},
    {"g_to", "microS", "i_to", CONSTANT},
    {"g_Kr", "microS", "i_Kr", CONSTANT},
    {"g_Ks_", "microS", "i_Ks", CONSTANT},
    {"ACh_on", "dimensionless", "i_KACh", CONSTANT},
    {"g_KACh", "microS", "i_KACh", CONSTANT},
    {"RTONF", "millivolt", "Membrane", COMPUTED_CONSTANT},
    {"E_K", "millivolt", "Ionic_values", COMPUTED_CONSTANT},
    {"V_i", "millimetre3", "Cell_parameters", COMPUTED_CONSTANT},
    {"V_sub", "millimetre3", "Cell_parameters", COMPUTED_CONSTANT},
    {"Iso_increase", "dimensionless", "i_NaK", COMPUTED_CONSTANT},
    {"k34", "dimensionless", "i_NaCa", COMPUTED_CONSTANT},
    {"b_up", "dimensionless", "Ca_intracellular_fluxes", COMPUTED_CONSTANT},
    {"P_up", "millimolar_per_second", "Ca_intracellular_fluxes", COMPUTED_CONSTANT},
    {"V_nsr", "millimetre3", "Cell_parameters", COMPUTED_CONSTANT},
    {"V_jsr", "millimetre3", "Cell_parameters", COMPUTED_CONSTANT},
    {"V_cell", "millimetre3", "Cell_parameters", COMPUTED_CONSTANT},
    {"G_f", "microS", "i_f", COMPUTED_CONSTANT},
    {"G_f_K", "microS", "i_f", COMPUTED_CONSTANT},
    {"G_f_Na", "microS", "i_f", COMPUTED_CONSTANT},
    {"g_f_Na", "microS", "i_f", COMPUTED_CONSTANT},
    {"g_f_K", "microS", "i_f", COMPUTED_CONSTANT},
    {"ACh_shift", "millivolt", "i_f_y_gate", COMPUTED_CONSTANT},
    {"Iso_shift", "millivolt", "i_f_y_gate", COMPUTED_CONSTANT},
    {"Iso_increase", "dimensionless", "i_CaL", COMPUTED_CONSTANT},
    {"ACh_block", "dimensionless", "i_CaL", COMPUTED_CONSTANT},
    {"Iso_shift_dL", "millivolt", "i_CaL_dL_gate", COMPUTED_CONSTANT},
    {"Iso_slope_dL", "dimensionless", "i_CaL_dL_gate", COMPUTED_CONSTANT},
    {"g_Ks", "microS", "i_Ks", COMPUTED_CONSTANT},
    {"Iso_shift", "millivolt", "i_Ks_n_gate", COMPUTED_CONSTANT},
    {"alpha_a", "per_second", "i_KACh_a_gate", COMPUTED_CONSTANT},
    {"E_Na", "millivolt", "Ionic_values", ALGEBRAIC},
    {"Nai", "millimolar", "Nai_concentration", ALGEBRAIC},
    {"E_Ca", "millivolt", "Ionic_values", ALGEBRAIC},
    {"i_Na", "nanoA", "i_Na", ALGEBRAIC},
    {"i_NaCa", "nanoA", "i_NaCa", ALGEBRAIC},
    {"i_NaK", "nanoA", "i_NaK", ALGEBRAIC},
    {"i_siNa", "nanoA", "i_CaL", ALGEBRAIC},
    {"i_fNa", "nanoA", "i_f", ALGEBRAIC},
    {"V", "millivolt", "Membrane", ALGEBRAIC},
    {"x2", "dimensionless", "i_NaCa", ALGEBRAIC},
    {"k21", "dimensionless", "i_NaCa", ALGEBRAIC},
    {"x1", "dimensionless", "i_NaCa", ALGEBRAIC},
    {"k12", "dimensionless", "i_NaCa", ALGEBRAIC},
    {"x4", "dimensionless", "i_NaCa", ALGEBRAIC},
    {"x3", "dimensionless", "i_NaCa", ALGEBRAIC},
    {"k41", "dimensionless", "i_NaCa", ALGEBRAIC},
    {"k23", "dimensionless", "i_NaCa", ALGEBRAIC},
    {"k43", "dimensionless", "i_NaCa", ALGEBRAIC},
    {"k32", "dimensionless", "i_NaCa", ALGEBRAIC},
    {"k14", "dimensionless", "i_NaCa", ALGEBRAIC},
    {"di", "dimensionless", "i_NaCa", ALGEBRAIC},
    {"do", "dimensionless", "i_NaCa", ALGEBRAIC},
    {"j_SRCarel", "millimolar_per_second", "Ca_SR_release", ALGEBRAIC},
    {"diff", "millimolar", "Ca_SR_release", ALGEBRAIC},
    {"kCaSR", "dimensionless", "Ca_SR_release", ALGEBRAIC},
    {"koSRCa", "per_millimolar2_second", "Ca_SR_release", ALGEBRAIC},
    {"kiSRCa", "per_millimolar_second", "Ca_SR_release", ALGEBRAIC},
    {"P_tot", "dimensionless", "Ca_SR_release", ALGEBRAIC},
    {"j_Ca_dif", "millimolar_per_second", "Ca_intracellular_fluxes", ALGEBRAIC},
    {"j_up", "millimolar_per_second", "Ca_intracellular_fluxes", ALGEBRAIC},
    {"j_tr", "millimolar_per_second", "Ca_intracellular_fluxes", ALGEBRAIC},
    {"delta_fTC", "per_second", "Ca_buffering", ALGEBRAIC},
    {"delta_fTMC", "per_second", "Ca_buffering", ALGEBRAIC},
    {"delta_fTMM", "per_second", "Ca_buffering", ALGEBRAIC},
    {"delta_fCMi", "per_second", "Ca_buffering", ALGEBRAIC},
    {"delta_fCMs", "per_second", "Ca_buffering", ALGEBRAIC},
    {"delta_fCQ", "per_second", "Ca_buffering", ALGEBRAIC},
    {"i_siCa", "nanoA", "i_CaL", ALGEBRAIC},
    {"i_CaT", "nanoA", "i_CaT", ALGEBRAIC},
    {"i_tot", "nanoA", "Membrane", ALGEBRAIC},
    {"i_f", "nanoA", "i_f", ALGEBRAIC},
    {"i_Kur", "nanoA", "i_Kur", ALGEBRAIC},
    {"i_KACh", "nanoA", "i_KACh", ALGEBRAIC},
    {"i_CaL", "nanoA", "i_CaL", ALGEBRAIC},
    {"i_to", "nanoA", "i_to", ALGEBRAIC},
    {"i_Ks", "nanoA", "i_Ks", ALGEBRAIC},
    {"i_Kr", "nanoA", "i_Kr", ALGEBRAIC},
    {"V_clamp", "millivolt", "Voltage_clamp", ALGEBRAIC},
    {"i_fK", "nanoA", "i_f", ALGEBRAIC},
    {"tau_y", "second", "i_f_y_gate", ALGEBRAIC},
    {"y_infinity", "dimensionless", "i_f_y_gate", ALGEBRAIC},
    {"E_mh", "millivolt", "i_Na", ALGEBRAIC},
    {"i_Na_", "nanoA", "i_Na", ALGEBRAIC},
    {"i_Na_L", "nanoA", "i_Na", ALGEBRAIC},
    {"m_infinity", "dimensionless", "i_Na_m_gate", ALGEBRAIC},
    {"E0_m", "millivolt", "i_Na_m_gate", ALGEBRAIC},
    {"alpha_m", "per_second", "i_Na_m_gate", ALGEBRAIC},
    {"beta_m", "per_second", "i_Na_m_gate", ALGEBRAIC},
    {"tau_m", "second", "i_Na_m_gate", ALGEBRAIC},
    {"h_infinity", "dimensionless", "i_Na_h_gate", ALGEBRAIC},
    {"alpha_h", "per_second", "i_Na_h_gate", ALGEBRAIC},
    {"beta_h", "per_second", "i_Na_h_gate", ALGEBRAIC},
    {"tau_h", "second", "i_Na_h_gate", ALGEBRAIC},
    {"r_Kur_infinity", "dimensionless", "i_Kur_rKur_gate", ALGEBRAIC},
    {"tau_r_Kur", "second", "i_Kur_rKur_gate", ALGEBRAIC},
    {"s_Kur_infinity", "dimensionless", "i_Kur_sKur_gate", ALGEBRAIC},
    {"tau_s_Kur", "second", "i_Kur_sKur_gate", ALGEBRAIC},
    {"i_siK", "nanoA", "i_CaL", ALGEBRAIC},
    {"dL_infinity", "dimensionless", "i_CaL_dL_gate", ALGEBRAIC},
    {"tau_dL", "second", "i_CaL_dL_gate", ALGEBRAIC},
    {"alpha_dL", "per_second", "i_CaL_dL_gate", ALGEBRAIC},
    {"beta_dL", "per_second", "i_CaL_dL_gate", ALGEBRAIC},
    {"adVm", "millivolt", "i_CaL_dL_gate", ALGEBRAIC},
    {"bdVm", "millivolt", "i_CaL_dL_gate", ALGEBRAIC},
    {"fL_infinity", "dimensionless", "i_CaL_fL_gate", ALGEBRAIC},
    {"tau_fL", "second", "i_CaL_fL_gate", ALGEBRAIC},
    {"fCa_infinity", "dimensionless", "i_CaL_fCa_gate", ALGEBRAIC},
    {"tau_fCa", "second", "i_CaL_fCa_gate", ALGEBRAIC},
    {"dT_infinity", "dimensionless", "i_CaT_dT_gate", ALGEBRAIC},
    {"tau_dT", "second", "i_CaT_dT_gate", ALGEBRAIC},
    {"fT_infinity", "dimensionless", "i_CaT_fT_gate", ALGEBRAIC},
    {"tau_fT", "second", "i_CaT_fT_gate", ALGEBRAIC},
    {"q_infinity", "dimensionless", "i_to_q_gate", ALGEBRAIC},
    {"tau_q", "second", "i_to_q_gate", ALGEBRAIC},
    {"r_infinity", "dimensionless", "i_to_r_gate", ALGEBRAIC},
    {"tau_r", "second", "i_to_r_gate", ALGEBRAIC},
    {"alfapaF", "per_second", "i_Kr_pa_gate", ALGEBRAIC},
    {"betapaF", "per_second", "i_Kr_pa_gate", ALGEBRAIC},
    {"pa_infinity", "dimensionless", "i_Kr_pa_gate", ALGEBRAIC},
    {"tau_paS", "second", "i_Kr_pa_gate", ALGEBRAIC},
    {"tau_paF", "second", "i_Kr_pa_gate", ALGEBRAIC},
    {"tau_pi", "second", "i_Kr_pi_gate", ALGEBRAIC},
    {"pi_infinity", "dimensionless", "i_Kr_pi_gate", ALGEBRAIC},
    {"E_Ks", "millivolt", "i_Ks", ALGEBRAIC},
    {"n_infinity", "dimensionless", "i_Ks_n_gate", ALGEBRAIC},
    {"tau_n", "second", "i_Ks_n_gate", ALGEBRAIC},
    {"alpha_n", "per_second", "i_Ks_n_gate", ALGEBRAIC},
    {"beta_n", "per_second", "i_Ks_n_gate", ALGEBRAIC},
    {"beta_a", "per_second", "i_KACh_a_gate", ALGEBRAIC},
    {"a_infinity", "dimensionless", "i_KACh_a_gate", ALGEBRAIC},
    {"tau_a", "second", "i_KACh_a_gate", ALGEBRAIC}
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
    constants[1] = 0.0;
    constants[2] = 140.0;
    constants[3] = 5.4;
    constants[4] = 140.0;
    constants[5] = 1.8;
    constants[6] = 1.0;
    constants[7] = 96485.3415;
    constants[8] = 14.0;
    constants[9] = 1.4;
    constants[10] = 0.08105;
    constants[11] = 0.0;
    constants[12] = 3.343;
    constants[13] = 26.44;
    constants[14] = 0.0207;
    constants[15] = 0.1369;
    constants[16] = 395.3;
    constants[17] = 2.289;
    constants[18] = 0.4315;
    constants[19] = 26.44;
    constants[20] = 4.663;
    constants[21] = 3.663;
    constants[22] = 0.0;
    constants[23] = 1628.0;
    constants[24] = 561.4;
    constants[25] = 148041085.1;
    constants[26] = 15.0;
    constants[27] = 1.0;
    constants[28] = 0.45;
    constants[29] = 2.5;
    constants[30] = 10000.0;
    constants[31] = 500.0;
    constants[32] = 5.0;
    constants[33] = 660.0;
    constants[34] = 5.0;
    constants[35] = 5.469e-5;
    constants[36] = 0.000286113;
    constants[37] = 5.0e-5;
    constants[38] = 0.04;
    constants[39] = 88800.0;
    constants[40] = 446.0;
    constants[41] = 227700.0;
    constants[42] = 7.51;
    constants[43] = 2277.0;
    constants[44] = 2.5;
    constants[45] = 751.0;
    constants[46] = 1.642e6;
    constants[47] = 542.0;
    constants[48] = 175.4;
    constants[49] = 445.0;
    constants[50] = 0.031;
    constants[51] = 0.062;
    constants[52] = 0.045;
    constants[53] = 10.0;
    constants[54] = 67.0;
    constants[55] = 3.9;
    constants[56] = 0.02;
    constants[57] = 0.0012;
    constants[58] = 0.46;
    constants[59] = 0.0116;
    constants[60] = 5.7e-5;
    constants[61] = 8314.472;
    constants[62] = 310.0;
    constants[63] = 0.0;
    constants[64] = -35.0;
    constants[65] = 0.5;
    constants[66] = 0.5;
    constants[67] = -45.0;
    constants[68] = 0.00427;
    constants[69] = 45.0;
    constants[70] = 0.5927;
    constants[71] = 0.0;
    constants[72] = 0.0;
    constants[73] = 0.0223;
    constants[74] = 0.0;
    constants[75] = 1.0e-5;
    constants[76] = 0.1539e-3;
    constants[77] = 0.4578;
    constants[78] = -16.4508;
    constants[79] = 4.3371;
    constants[80] = 0.0;
    constants[81] = 0.0;
    constants[82] = 0.000338;
    constants[83] = 0.0075;
    constants[84] = 0.04132;
    constants[85] = 0.0;
    constants[86] = 3.5e-3;
    constants[87] = 0.00424;
    constants[88] = 0.00065;
    constants[89] = 1.0;
    constants[90] = 0.00345;
    states[0] = 6.226104e-5;
    states[1] = 5.0;
    states[2] = 0.409551;
    states[3] = 6.181512e-9;
    states[4] = 0.9308;
    states[5] = 0.069199;
    states[6] = 4.595622e-10;
    states[7] = 9.15641e-6;
    states[8] = 0.435148;
    states[9] = 0.017929;
    states[10] = 0.259947;
    states[11] = 0.653777;
    states[12] = 0.217311;
    states[13] = 0.158521;
    states[14] = 0.138975;
    states[15] = -47.787168;
    states[16] = 0.009508;
    states[17] = 0.003058;
    states[18] = 0.447724;
    states[19] = 0.845304;
    states[20] = 0.011845;
    states[21] = 0.844449;
    states[22] = 0.846702;
    states[23] = 0.001921;
    states[24] = 0.020484;
    states[25] = 0.268909;
    states[26] = 0.014523;
    states[27] = 0.430836;
    states[28] = 0.709051;
    states[29] = 0.011068;
    states[30] = 0.283185;
    states[31] = 0.1162;
    states[32] = 0.00277;
}

void computeComputedConstants(double *constants, double *computedConstants)
{
    computedConstants[0] = constants[61]*constants[62]/constants[7];
    computedConstants[1] = computedConstants[0]*log(constants[3]/constants[4]);
    computedConstants[4] = (constants[1] > 0.0)?1.2:1.0;
    computedConstants[5] = constants[2]/(constants[20]+constants[2]);
    computedConstants[6] = (constants[1] > 0.0)?-0.25:(constants[0] > 0.0)?0.7*constants[0]/(0.00009+constants[0]):0.0;
    computedConstants[7] = constants[34]*(1.0-computedConstants[6]);
    computedConstants[10] = 0.000000001*3.14159265358979*pow(constants[55], 2.0)*constants[54];
    computedConstants[3] = 0.000000001*2.0*3.14159265358979*constants[56]*(constants[55]-constants[56]/2.0)*constants[54];
    computedConstants[9] = constants[57]*computedConstants[10];
    computedConstants[2] = constants[58]*computedConstants[10]-computedConstants[3];
    computedConstants[8] = constants[59]*computedConstants[10];
    computedConstants[11] = constants[68]/(constants[3]/(constants[3]+constants[69]));
    computedConstants[12] = computedConstants[11]/(constants[70]+1.0);
    computedConstants[13] = constants[70]*computedConstants[12];
    computedConstants[14] = computedConstants[13]*constants[3]/(constants[3]+constants[69]);
    computedConstants[15] = computedConstants[12]*constants[3]/(constants[3]+constants[69]);
    computedConstants[16] = (constants[0] > 0.0)?-1.0-9.898*pow(1.0*constants[0], 0.618)/(pow(1.0*constants[0], 0.618)+0.00122423):0.0;
    computedConstants[17] = (constants[1] > 0.0)?7.5:0.0;
    computedConstants[18] = (constants[1] > 0.0)?1.23:1.0;
    computedConstants[19] = 0.31*constants[0]/(constants[0]+0.00009);
    computedConstants[20] = (constants[1] > 0.0)?-8.0:0.0;
    computedConstants[21] = (constants[1] > 0.0)?-27.0:0.0;
    computedConstants[22] = (constants[1] > 0.0)?1.2*constants[88]:constants[88];
    computedConstants[23] = (constants[1] > 0.0)?-14.0:0.0;
    computedConstants[24] = (3.5988-0.025641)/(1.0+0.0000012155/pow(1.0*constants[0], 1.6951))+0.025641;
}

void computeRates(double voi, double *states, double *rates, double *constants, double *computedConstants, double *algebraic)
{
    algebraic[1] = states[1];
    algebraic[51] = computedConstants[0]*log((constants[2]+0.12*constants[3])/(algebraic[1]+0.12*constants[4]));
    algebraic[47] = ((voi > constants[65]) && (voi < constants[65]+constants[66]))?constants[64]:constants[67];
    algebraic[8] = (constants[63] >= 1.0)?algebraic[47]:states[15];
    algebraic[52] = constants[73]*pow(states[18], 3.0)*states[17]*(algebraic[8]-algebraic[51]);
    algebraic[53] = constants[74]*pow(states[18], 3.0)*(algebraic[8]-algebraic[51]);
    algebraic[3] = algebraic[52]+algebraic[53];
    algebraic[6] = 0.0000185*constants[77]*(algebraic[8]-0.0)/(computedConstants[0]*(1.0-exp(-1.0*(algebraic[8]-0.0)/computedConstants[0])))*(algebraic[1]-constants[2]*exp(-1.0*(algebraic[8]-0.0)/computedConstants[0]))*states[23]*states[22]*states[21];
    algebraic[0] = computedConstants[0]*log(constants[2]/algebraic[1]);
    algebraic[7] = states[16]*computedConstants[14]*(algebraic[8]-algebraic[0])*(1.0-constants[71]);
    algebraic[5] = computedConstants[4]*constants[10]*pow(1.0+pow(constants[9]/constants[3], 1.2), -1.0)*pow(1.0+pow(constants[8]/algebraic[1], 1.3), -1.0)*pow(1.0+exp(-(algebraic[8]-algebraic[0]+110.0)/20.0), -1.0);
    algebraic[21] = 1.0+constants[5]/constants[21]*(1.0+exp(constants[22]*algebraic[8]/computedConstants[0]))+constants[2]/constants[23]*(1.0+constants[2]/constants[24]*(1.0+constants[2]/constants[20]));
    algebraic[10] = constants[5]/constants[21]*exp(constants[22]*algebraic[8]/computedConstants[0])/algebraic[21];
    algebraic[20] = 1.0+states[0]/constants[14]*(1.0+exp(-constants[15]*algebraic[8]/computedConstants[0])+algebraic[1]/constants[19])+algebraic[1]/constants[16]*(1.0+algebraic[1]/constants[17]*(1.0+algebraic[1]/constants[13]));
    algebraic[12] = states[0]/constants[14]*exp(-constants[15]*algebraic[8]/computedConstants[0])/algebraic[20];
    algebraic[17] = algebraic[1]/(constants[13]+algebraic[1]);
    algebraic[18] = exp(constants[18]*algebraic[8]/(2.0*computedConstants[0]));
    algebraic[15] = exp(-constants[18]*algebraic[8]/(2.0*computedConstants[0]));
    algebraic[19] = algebraic[1]/constants[16]*algebraic[1]/constants[17]*(1.0+algebraic[1]/constants[13])*exp(constants[18]*algebraic[8]/(2.0*computedConstants[0]))/algebraic[20];
    algebraic[9] = algebraic[18]*algebraic[17]*(algebraic[19]+algebraic[12])+algebraic[15]*algebraic[12]*(computedConstants[5]+algebraic[18]);
    algebraic[16] = constants[2]/constants[23]*constants[2]/constants[24]*(1.0+constants[2]/constants[20])*exp(-constants[18]*algebraic[8]/(2.0*computedConstants[0]))/algebraic[21];
    algebraic[11] = algebraic[15]*computedConstants[5]*(algebraic[16]+algebraic[10])+algebraic[10]*algebraic[18]*(algebraic[17]+algebraic[15]);
    algebraic[13] = algebraic[16]*computedConstants[5]*(algebraic[19]+algebraic[12])+algebraic[19]*algebraic[10]*(computedConstants[5]+algebraic[18]);
    algebraic[14] = algebraic[19]*algebraic[17]*(algebraic[16]+algebraic[10])+algebraic[12]*algebraic[16]*(algebraic[17]+algebraic[15]);
    algebraic[4] = (1.0-constants[11])*constants[12]*(algebraic[9]*algebraic[10]-algebraic[11]*algebraic[12])/(algebraic[11]+algebraic[9]+algebraic[14]+algebraic[13]);
    rates[1] = (1.0-constants[6])*-1.0*(algebraic[3]+algebraic[7]+algebraic[6]+3.0*algebraic[5]+3.0*algebraic[4])/(1.0*(computedConstants[2]+computedConstants[3])*constants[7]);
    algebraic[24] = constants[26]-(constants[26]-constants[27])/(1.0+pow(constants[28]/states[2], constants[29]));
    algebraic[26] = constants[31]*algebraic[24];
    algebraic[25] = constants[30]/algebraic[24];
    rates[4] = constants[32]*states[5]-algebraic[26]*states[0]*states[4]-(algebraic[25]*pow(states[0], 2.0)*states[4]-constants[33]*states[3]);
    rates[3] = algebraic[25]*pow(states[0], 2.0)*states[4]-constants[33]*states[3]-(algebraic[26]*states[0]*states[3]-constants[32]*states[6]);
    rates[6] = algebraic[26]*states[0]*states[3]-constants[32]*states[6]-(constants[33]*states[6]-algebraic[25]*pow(states[0], 2.0)*states[5]);
    rates[5] = constants[33]*states[6]-algebraic[25]*pow(states[0], 2.0)*states[5]-(constants[32]*states[5]-algebraic[26]*states[0]*states[4]);
    algebraic[31] = constants[39]*states[7]*(1.0-states[9])-constants[40]*states[9];
    rates[9] = algebraic[31];
    algebraic[32] = constants[41]*states[7]*(1.0-(states[10]+states[11]))-constants[42]*states[10];
    rates[10] = algebraic[32];
    algebraic[33] = constants[43]*constants[44]*(1.0-(states[10]+states[11]))-constants[45]*states[11];
    rates[11] = algebraic[33];
    algebraic[34] = constants[46]*states[7]*(1.0-states[12])-constants[47]*states[12];
    rates[12] = algebraic[34];
    algebraic[35] = constants[46]*states[0]*(1.0-states[13])-constants[47]*states[13];
    rates[13] = algebraic[35];
    algebraic[36] = constants[48]*states[2]*(1.0-states[14])-constants[49]*states[14];
    rates[14] = algebraic[36];
    algebraic[28] = (states[0]-states[7])/constants[35];
    algebraic[29] = computedConstants[7]/(1.0+exp((-states[7]+constants[36])/constants[37]));
    rates[7] = 1.0*(algebraic[28]*computedConstants[3]-algebraic[29]*computedConstants[8])/computedConstants[2]-(constants[52]*algebraic[34]+constants[50]*algebraic[31]+constants[51]*algebraic[32]);
    algebraic[22] = constants[25]*states[3]*(states[2]-states[0]);
    algebraic[37] = 2.0*constants[77]*(algebraic[8]-0.0)/(computedConstants[0]*(1.0-exp(-1.0*(algebraic[8]-0.0)*2.0/computedConstants[0])))*(states[0]-constants[5]*exp(-2.0*(algebraic[8]-0.0)/computedConstants[0]))*states[23]*states[22]*states[21];
    algebraic[38] = 2.0*constants[84]*algebraic[8]/(computedConstants[0]*(1.0-exp(-1.0*algebraic[8]*2.0/computedConstants[0])))*(states[0]-constants[5]*exp(-2.0*algebraic[8]/computedConstants[0]))*states[25]*states[24];
    rates[0] = algebraic[22]*computedConstants[9]/computedConstants[3]-((algebraic[37]+algebraic[38]-2.0*algebraic[4])/(2.0*constants[7]*computedConstants[3])+algebraic[28]+constants[52]*algebraic[35]);
    algebraic[30] = (states[8]-states[2])/constants[38];
    rates[8] = algebraic[29]-algebraic[30]*computedConstants[9]/computedConstants[8];
    rates[2] = algebraic[30]-(algebraic[22]+constants[53]*algebraic[36]);
    algebraic[48] = states[16]*computedConstants[15]*(algebraic[8]-computedConstants[1])*(1.0-constants[71]);
    algebraic[40] = algebraic[7]+algebraic[48];
    algebraic[41] = constants[76]*states[20]*states[19]*(algebraic[8]-computedConstants[1]);
    algebraic[42] = (constants[0] > 0.0)?constants[89]*constants[90]*(algebraic[8]-computedConstants[1])*(1.0+exp((algebraic[8]+20.0)/20.0))*states[32]:0.0;
    algebraic[67] = 0.000365*constants[77]*(algebraic[8]-0.0)/(computedConstants[0]*(1.0-exp(-1.0*(algebraic[8]-0.0)/computedConstants[0])))*(constants[4]-constants[3]*exp(-1.0*(algebraic[8]-0.0)/computedConstants[0]))*states[23]*states[22]*states[21];
    algebraic[43] = (algebraic[37]+algebraic[67]+algebraic[6])*(1.0-computedConstants[19])*1.0*computedConstants[18];
    algebraic[44] = constants[86]*(algebraic[8]-computedConstants[1])*states[27]*states[26];
    algebraic[93] = computedConstants[0]*log((constants[3]+0.12*constants[2])/(constants[4]+0.12*algebraic[1]));
    algebraic[45] = computedConstants[22]*(algebraic[8]-algebraic[93])*pow(states[31], 2.0);
    algebraic[46] = constants[87]*(algebraic[8]-computedConstants[1])*(0.9*states[29]+0.1*states[30])*states[28];
    algebraic[39] = algebraic[40]+algebraic[46]+algebraic[45]+algebraic[44]+algebraic[5]+algebraic[4]+algebraic[3]+algebraic[43]+algebraic[38]+algebraic[42]+algebraic[41];
    rates[15] = -algebraic[39]/constants[60];
    algebraic[50] = (algebraic[8] < -(80.0-computedConstants[16]-computedConstants[17]-constants[72]))?0.01329+0.99921/(1.0+exp((algebraic[8]+97.134-computedConstants[16]-computedConstants[17]-constants[72])/8.1752)):0.0002501*exp(-(algebraic[8]-computedConstants[16]-computedConstants[17]-constants[72])/12.861);
    algebraic[49] = 1.0/(0.36*(algebraic[8]+148.8-computedConstants[16]-computedConstants[17])/(exp(0.066*(algebraic[8]+148.8-computedConstants[16]-computedConstants[17]))-1.0)+0.1*(algebraic[8]+87.3-computedConstants[16]-computedConstants[17])/(1.0-exp(-0.2*(algebraic[8]+87.3-computedConstants[16]-computedConstants[17]))))-0.054;
    rates[16] = (algebraic[50]-states[16])/algebraic[49];
    algebraic[54] = 1.0/(1.0+exp(-(algebraic[8]+42.0504)/8.3106));
    algebraic[55] = algebraic[8]+41.0;
    algebraic[56] = (fabs(algebraic[55]) < constants[75])?2000.0:200.0*algebraic[55]/(1.0-exp(-0.1*algebraic[55]));
    algebraic[57] = 8000.0*exp(-0.056*(algebraic[8]+66.0));
    algebraic[58] = 1.0/(algebraic[56]+algebraic[57]);
    rates[18] = (algebraic[54]-states[18])/algebraic[58];
    algebraic[59] = 1.0/(1.0+exp((algebraic[8]+69.804)/4.4565));
    algebraic[60] = 20.0*exp(-0.125*(algebraic[8]+75.0));
    algebraic[61] = 2000.0/(320.0*exp(-0.1*(algebraic[8]+75.0))+1.0);
    algebraic[62] = 1.0/(algebraic[60]+algebraic[61]);
    rates[17] = (algebraic[59]-states[17])/algebraic[62];
    algebraic[63] = 1.0/(1.0+exp((algebraic[8]+6.0)/-8.6));
    algebraic[64] = 0.009/(1.0+exp((algebraic[8]+5.0)/12.0))+0.0005;
    rates[20] = (algebraic[63]-states[20])/algebraic[64];
    algebraic[65] = 1.0/(1.0+exp((algebraic[8]+7.5)/10.0));
    algebraic[66] = 0.59/(1.0+exp((algebraic[8]+60.0)/10.0))+3.05;
    rates[19] = (algebraic[65]-states[19])/algebraic[66];
    algebraic[68] = 1.0/(1.0+exp(-(algebraic[8]-constants[78]-computedConstants[20])/(constants[79]*(1.0+computedConstants[21]/100.0))));
    algebraic[72] = (algebraic[8] == -41.8)?-41.80001:(algebraic[8] == 0.0)?0.0:(algebraic[8] == -6.8)?-6.80001:algebraic[8];
    algebraic[70] = -0.02839*(algebraic[72]+41.8)/(exp(-(algebraic[72]+41.8)/2.5)-1.0)-0.0849*(algebraic[72]+6.8)/(exp(-(algebraic[72]+6.8)/4.8)-1.0);
    algebraic[73] = (algebraic[8] == -1.8)?-1.80001:algebraic[8];
    algebraic[71] = 0.01143*(algebraic[73]+1.8)/(exp((algebraic[73]+1.8)/2.5)-1.0);
    algebraic[69] = 0.001/(algebraic[70]+algebraic[71]);
    rates[23] = (algebraic[68]-states[23])/algebraic[69];
    algebraic[74] = 1.0/(1.0+exp((algebraic[8]+37.4+constants[80])/(5.3+constants[81])));
    algebraic[75] = 0.001*(44.3+230.0*exp(-pow((algebraic[8]+36.0)/10.0, 2.0)));
    rates[22] = (algebraic[74]-states[22])/algebraic[75];
    algebraic[76] = constants[82]/(constants[82]+states[0]);
    algebraic[77] = 0.001*algebraic[76]/constants[83];
    rates[21] = (algebraic[76]-states[21])/algebraic[77];
    algebraic[78] = 1.0/(1.0+exp(-(algebraic[8]+38.3)/5.5));
    algebraic[79] = 0.001/(1.068*exp((algebraic[8]+38.3)/30.0)+1.068*exp(-(algebraic[8]+38.3)/30.0));
    rates[25] = (algebraic[78]-states[25])/algebraic[79];
    algebraic[80] = 1.0/(1.0+exp((algebraic[8]+58.7)/3.8));
    algebraic[81] = 1.0/(16.67*exp(-(algebraic[8]+75.0)/83.3)+16.67*exp((algebraic[8]+75.0)/15.38))+constants[85];
    rates[24] = (algebraic[80]-states[24])/algebraic[81];
    algebraic[82] = 1.0/(1.0+exp((algebraic[8]+49.0)/13.0));
    algebraic[83] = 0.001*0.6*(65.17/(0.57*exp(-0.08*(algebraic[8]+44.0))+0.065*exp(0.1*(algebraic[8]+45.93)))+10.1);
    rates[27] = (algebraic[82]-states[27])/algebraic[83];
    algebraic[84] = 1.0/(1.0+exp(-(algebraic[8]-19.3)/15.0));
    algebraic[85] = 0.001*0.66*1.4*(15.59/(1.037*exp(0.09*(algebraic[8]+30.61))+0.369*exp(-0.12*(algebraic[8]+23.84)))+2.98);
    rates[26] = (algebraic[84]-states[26])/algebraic[85];
    algebraic[88] = 1.0/(1.0+exp(-(algebraic[8]+10.0144)/7.6607));
    algebraic[89] = 0.84655354/(4.2*exp(algebraic[8]/17.0)+0.15*exp(-algebraic[8]/21.6));
    rates[30] = (algebraic[88]-states[30])/algebraic[89];
    algebraic[90] = 1.0/(30.0*exp(algebraic[8]/10.0)+exp(-algebraic[8]/12.0));
    rates[29] = (algebraic[88]-states[29])/algebraic[90];
    algebraic[92] = 1.0/(1.0+exp((algebraic[8]+28.6)/17.1));
    algebraic[91] = 1.0/(100.0*exp(-algebraic[8]/54.645)+656.0*exp(algebraic[8]/106.157));
    rates[28] = (algebraic[92]-states[28])/algebraic[91];
    algebraic[94] = sqrt(1.0/(1.0+exp(-(algebraic[8]+0.6383-computedConstants[23])/10.7071)));
    algebraic[96] = 28.0/(1.0+exp(-(algebraic[8]-40.0-computedConstants[23])/3.0));
    algebraic[97] = 1.0*exp(-(algebraic[8]-computedConstants[23]-5.0)/25.0);
    algebraic[95] = 1.0/(algebraic[96]+algebraic[97]);
    rates[31] = (algebraic[94]-states[31])/algebraic[95];
    algebraic[98] = 10.0*exp(0.0133*(algebraic[8]+40.0));
    algebraic[99] = computedConstants[24]/(computedConstants[24]+algebraic[98]);
    algebraic[100] = 1.0/(computedConstants[24]+algebraic[98]);
    rates[32] = (algebraic[99]-states[32])/algebraic[100];
}

void computeVariables(double voi, double *states, double *rates, double *constants, double *computedConstants, double *algebraic)
{
    algebraic[1] = states[1];
    algebraic[0] = computedConstants[0]*log(constants[2]/algebraic[1]);
    algebraic[2] = 0.5*computedConstants[0]*log(constants[5]/states[0]);
    algebraic[8] = (constants[63] >= 1.0)?algebraic[47]:states[15];
    algebraic[5] = computedConstants[4]*constants[10]*pow(1.0+pow(constants[9]/constants[3], 1.2), -1.0)*pow(1.0+pow(constants[8]/algebraic[1], 1.3), -1.0)*pow(1.0+exp(-(algebraic[8]-algebraic[0]+110.0)/20.0), -1.0);
    algebraic[21] = 1.0+constants[5]/constants[21]*(1.0+exp(constants[22]*algebraic[8]/computedConstants[0]))+constants[2]/constants[23]*(1.0+constants[2]/constants[24]*(1.0+constants[2]/constants[20]));
    algebraic[10] = constants[5]/constants[21]*exp(constants[22]*algebraic[8]/computedConstants[0])/algebraic[21];
    algebraic[20] = 1.0+states[0]/constants[14]*(1.0+exp(-constants[15]*algebraic[8]/computedConstants[0])+algebraic[1]/constants[19])+algebraic[1]/constants[16]*(1.0+algebraic[1]/constants[17]*(1.0+algebraic[1]/constants[13]));
    algebraic[12] = states[0]/constants[14]*exp(-constants[15]*algebraic[8]/computedConstants[0])/algebraic[20];
    algebraic[17] = algebraic[1]/(constants[13]+algebraic[1]);
    algebraic[18] = exp(constants[18]*algebraic[8]/(2.0*computedConstants[0]));
    algebraic[15] = exp(-constants[18]*algebraic[8]/(2.0*computedConstants[0]));
    algebraic[19] = algebraic[1]/constants[16]*algebraic[1]/constants[17]*(1.0+algebraic[1]/constants[13])*exp(constants[18]*algebraic[8]/(2.0*computedConstants[0]))/algebraic[20];
    algebraic[9] = algebraic[18]*algebraic[17]*(algebraic[19]+algebraic[12])+algebraic[15]*algebraic[12]*(computedConstants[5]+algebraic[18]);
    algebraic[16] = constants[2]/constants[23]*constants[2]/constants[24]*(1.0+constants[2]/constants[20])*exp(-constants[18]*algebraic[8]/(2.0*computedConstants[0]))/algebraic[21];
    algebraic[11] = algebraic[15]*computedConstants[5]*(algebraic[16]+algebraic[10])+algebraic[10]*algebraic[18]*(algebraic[17]+algebraic[15]);
    algebraic[13] = algebraic[16]*computedConstants[5]*(algebraic[19]+algebraic[12])+algebraic[19]*algebraic[10]*(computedConstants[5]+algebraic[18]);
    algebraic[14] = algebraic[19]*algebraic[17]*(algebraic[16]+algebraic[10])+algebraic[12]*algebraic[16]*(algebraic[17]+algebraic[15]);
    algebraic[4] = (1.0-constants[11])*constants[12]*(algebraic[9]*algebraic[10]-algebraic[11]*algebraic[12])/(algebraic[11]+algebraic[9]+algebraic[14]+algebraic[13]);
    algebraic[22] = constants[25]*states[3]*(states[2]-states[0]);
    algebraic[23] = states[2]-states[0];
    algebraic[24] = constants[26]-(constants[26]-constants[27])/(1.0+pow(constants[28]/states[2], constants[29]));
    algebraic[25] = constants[30]/algebraic[24];
    algebraic[26] = constants[31]*algebraic[24];
    algebraic[27] = states[4]+states[3]+states[6]+states[5];
    algebraic[28] = (states[0]-states[7])/constants[35];
    algebraic[29] = computedConstants[7]/(1.0+exp((-states[7]+constants[36])/constants[37]));
    algebraic[30] = (states[8]-states[2])/constants[38];
    algebraic[31] = constants[39]*states[7]*(1.0-states[9])-constants[40]*states[9];
    algebraic[32] = constants[41]*states[7]*(1.0-(states[10]+states[11]))-constants[42]*states[10];
    algebraic[33] = constants[43]*constants[44]*(1.0-(states[10]+states[11]))-constants[45]*states[11];
    algebraic[34] = constants[46]*states[7]*(1.0-states[12])-constants[47]*states[12];
    algebraic[35] = constants[46]*states[0]*(1.0-states[13])-constants[47]*states[13];
    algebraic[36] = constants[48]*states[2]*(1.0-states[14])-constants[49]*states[14];
    algebraic[7] = states[16]*computedConstants[14]*(algebraic[8]-algebraic[0])*(1.0-constants[71]);
    algebraic[48] = states[16]*computedConstants[15]*(algebraic[8]-computedConstants[1])*(1.0-constants[71]);
    algebraic[40] = algebraic[7]+algebraic[48];
    algebraic[41] = constants[76]*states[20]*states[19]*(algebraic[8]-computedConstants[1]);
    algebraic[42] = (constants[0] > 0.0)?constants[89]*constants[90]*(algebraic[8]-computedConstants[1])*(1.0+exp((algebraic[8]+20.0)/20.0))*states[32]:0.0;
    algebraic[38] = 2.0*constants[84]*algebraic[8]/(computedConstants[0]*(1.0-exp(-1.0*algebraic[8]*2.0/computedConstants[0])))*(states[0]-constants[5]*exp(-2.0*algebraic[8]/computedConstants[0]))*states[25]*states[24];
    algebraic[37] = 2.0*constants[77]*(algebraic[8]-0.0)/(computedConstants[0]*(1.0-exp(-1.0*(algebraic[8]-0.0)*2.0/computedConstants[0])))*(states[0]-constants[5]*exp(-2.0*(algebraic[8]-0.0)/computedConstants[0]))*states[23]*states[22]*states[21];
    algebraic[6] = 0.0000185*constants[77]*(algebraic[8]-0.0)/(computedConstants[0]*(1.0-exp(-1.0*(algebraic[8]-0.0)/computedConstants[0])))*(algebraic[1]-constants[2]*exp(-1.0*(algebraic[8]-0.0)/computedConstants[0]))*states[23]*states[22]*states[21];
    algebraic[67] = 0.000365*constants[77]*(algebraic[8]-0.0)/(computedConstants[0]*(1.0-exp(-1.0*(algebraic[8]-0.0)/computedConstants[0])))*(constants[4]-constants[3]*exp(-1.0*(algebraic[8]-0.0)/computedConstants[0]))*states[23]*states[22]*states[21];
    algebraic[43] = (algebraic[37]+algebraic[67]+algebraic[6])*(1.0-computedConstants[19])*1.0*computedConstants[18];
    algebraic[51] = computedConstants[0]*log((constants[2]+0.12*constants[3])/(algebraic[1]+0.12*constants[4]));
    algebraic[52] = constants[73]*pow(states[18], 3.0)*states[17]*(algebraic[8]-algebraic[51]);
    algebraic[53] = constants[74]*pow(states[18], 3.0)*(algebraic[8]-algebraic[51]);
    algebraic[3] = algebraic[52]+algebraic[53];
    algebraic[44] = constants[86]*(algebraic[8]-computedConstants[1])*states[27]*states[26];
    algebraic[93] = computedConstants[0]*log((constants[3]+0.12*constants[2])/(constants[4]+0.12*algebraic[1]));
    algebraic[45] = computedConstants[22]*(algebraic[8]-algebraic[93])*pow(states[31], 2.0);
    algebraic[46] = constants[87]*(algebraic[8]-computedConstants[1])*(0.9*states[29]+0.1*states[30])*states[28];
    algebraic[39] = algebraic[40]+algebraic[46]+algebraic[45]+algebraic[44]+algebraic[5]+algebraic[4]+algebraic[3]+algebraic[43]+algebraic[38]+algebraic[42]+algebraic[41];
    algebraic[49] = 1.0/(0.36*(algebraic[8]+148.8-computedConstants[16]-computedConstants[17])/(exp(0.066*(algebraic[8]+148.8-computedConstants[16]-computedConstants[17]))-1.0)+0.1*(algebraic[8]+87.3-computedConstants[16]-computedConstants[17])/(1.0-exp(-0.2*(algebraic[8]+87.3-computedConstants[16]-computedConstants[17]))))-0.054;
    algebraic[50] = (algebraic[8] < -(80.0-computedConstants[16]-computedConstants[17]-constants[72]))?0.01329+0.99921/(1.0+exp((algebraic[8]+97.134-computedConstants[16]-computedConstants[17]-constants[72])/8.1752)):0.0002501*exp(-(algebraic[8]-computedConstants[16]-computedConstants[17]-constants[72])/12.861);
    algebraic[54] = 1.0/(1.0+exp(-(algebraic[8]+42.0504)/8.3106));
    algebraic[55] = algebraic[8]+41.0;
    algebraic[56] = (fabs(algebraic[55]) < constants[75])?2000.0:200.0*algebraic[55]/(1.0-exp(-0.1*algebraic[55]));
    algebraic[57] = 8000.0*exp(-0.056*(algebraic[8]+66.0));
    algebraic[58] = 1.0/(algebraic[56]+algebraic[57]);
    algebraic[59] = 1.0/(1.0+exp((algebraic[8]+69.804)/4.4565));
    algebraic[60] = 20.0*exp(-0.125*(algebraic[8]+75.0));
    algebraic[61] = 2000.0/(320.0*exp(-0.1*(algebraic[8]+75.0))+1.0);
    algebraic[62] = 1.0/(algebraic[60]+algebraic[61]);
    algebraic[63] = 1.0/(1.0+exp((algebraic[8]+6.0)/-8.6));
    algebraic[64] = 0.009/(1.0+exp((algebraic[8]+5.0)/12.0))+0.0005;
    algebraic[65] = 1.0/(1.0+exp((algebraic[8]+7.5)/10.0));
    algebraic[66] = 0.59/(1.0+exp((algebraic[8]+60.0)/10.0))+3.05;
    algebraic[68] = 1.0/(1.0+exp(-(algebraic[8]-constants[78]-computedConstants[20])/(constants[79]*(1.0+computedConstants[21]/100.0))));
    algebraic[72] = (algebraic[8] == -41.8)?-41.80001:(algebraic[8] == 0.0)?0.0:(algebraic[8] == -6.8)?-6.80001:algebraic[8];
    algebraic[70] = -0.02839*(algebraic[72]+41.8)/(exp(-(algebraic[72]+41.8)/2.5)-1.0)-0.0849*(algebraic[72]+6.8)/(exp(-(algebraic[72]+6.8)/4.8)-1.0);
    algebraic[73] = (algebraic[8] == -1.8)?-1.80001:algebraic[8];
    algebraic[71] = 0.01143*(algebraic[73]+1.8)/(exp((algebraic[73]+1.8)/2.5)-1.0);
    algebraic[69] = 0.001/(algebraic[70]+algebraic[71]);
    algebraic[74] = 1.0/(1.0+exp((algebraic[8]+37.4+constants[80])/(5.3+constants[81])));
    algebraic[75] = 0.001*(44.3+230.0*exp(-pow((algebraic[8]+36.0)/10.0, 2.0)));
    algebraic[76] = constants[82]/(constants[82]+states[0]);
    algebraic[77] = 0.001*algebraic[76]/constants[83];
    algebraic[78] = 1.0/(1.0+exp(-(algebraic[8]+38.3)/5.5));
    algebraic[79] = 0.001/(1.068*exp((algebraic[8]+38.3)/30.0)+1.068*exp(-(algebraic[8]+38.3)/30.0));
    algebraic[80] = 1.0/(1.0+exp((algebraic[8]+58.7)/3.8));
    algebraic[81] = 1.0/(16.67*exp(-(algebraic[8]+75.0)/83.3)+16.67*exp((algebraic[8]+75.0)/15.38))+constants[85];
    algebraic[82] = 1.0/(1.0+exp((algebraic[8]+49.0)/13.0));
    algebraic[83] = 0.001*0.6*(65.17/(0.57*exp(-0.08*(algebraic[8]+44.0))+0.065*exp(0.1*(algebraic[8]+45.93)))+10.1);
    algebraic[84] = 1.0/(1.0+exp(-(algebraic[8]-19.3)/15.0));
    algebraic[85] = 0.001*0.66*1.4*(15.59/(1.037*exp(0.09*(algebraic[8]+30.61))+0.369*exp(-0.12*(algebraic[8]+23.84)))+2.98);
    algebraic[86] = 1.0/(1.0+exp(-(algebraic[8]+23.2)/6.6))/(0.84655354/(37.2*exp(algebraic[8]/11.9)+0.96*exp(-algebraic[8]/18.5)));
    algebraic[87] = 4.0*((37.2*exp(algebraic[8]/15.9)+0.96*exp(-algebraic[8]/22.5))/0.84655354-1.0/(1.0+exp(-(algebraic[8]+23.2)/10.6))/(0.84655354/(37.2*exp(algebraic[8]/15.9)+0.96*exp(-algebraic[8]/22.5))));
    algebraic[88] = 1.0/(1.0+exp(-(algebraic[8]+10.0144)/7.6607));
    algebraic[89] = 0.84655354/(4.2*exp(algebraic[8]/17.0)+0.15*exp(-algebraic[8]/21.6));
    algebraic[90] = 1.0/(30.0*exp(algebraic[8]/10.0)+exp(-algebraic[8]/12.0));
    algebraic[91] = 1.0/(100.0*exp(-algebraic[8]/54.645)+656.0*exp(algebraic[8]/106.157));
    algebraic[92] = 1.0/(1.0+exp((algebraic[8]+28.6)/17.1));
    algebraic[94] = sqrt(1.0/(1.0+exp(-(algebraic[8]+0.6383-computedConstants[23])/10.7071)));
    algebraic[96] = 28.0/(1.0+exp(-(algebraic[8]-40.0-computedConstants[23])/3.0));
    algebraic[97] = 1.0*exp(-(algebraic[8]-computedConstants[23]-5.0)/25.0);
    algebraic[95] = 1.0/(algebraic[96]+algebraic[97]);
    algebraic[98] = 10.0*exp(0.0133*(algebraic[8]+40.0));
    algebraic[99] = computedConstants[24]/(computedConstants[24]+algebraic[98]);
    algebraic[100] = 1.0/(computedConstants[24]+algebraic[98]);
}

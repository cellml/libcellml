/* The content of this file was generated using the C profile of libCellML 0.5.0. */

#include "model.h"

#include <math.h>
#include <stdlib.h>

const char VERSION[] = "0.6.0";
const char LIBCELLML_VERSION[] = "0.5.0";

const size_t STATE_COUNT = 33;
const size_t CONSTANT_COUNT = 0;
const size_t COMPUTED_CONSTANT_COUNT = 0;
const size_t ALGEBRAIC_COUNT = 217;

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
    {"E_Na", "millivolt", "Ionic_values", ALGEBRAIC},
    {"RTONF", "millivolt", "Membrane", COMPUTED_CONSTANT},
    {"Nao", "millimolar", "Ionic_values", CONSTANT},
    {"Nai", "millimolar", "Nai_concentration", ALGEBRAIC},
    {"E_K", "millivolt", "Ionic_values", COMPUTED_CONSTANT},
    {"Ko", "millimolar", "Ionic_values", CONSTANT},
    {"Ki", "millimolar", "Ionic_values", CONSTANT},
    {"E_Ca", "millivolt", "Ionic_values", ALGEBRAIC},
    {"Cao", "millimolar", "Ionic_values", CONSTANT},
    {"Nai_clamp", "dimensionless", "Nai_concentration", CONSTANT},
    {"i_Na", "nanoA", "i_Na", ALGEBRAIC},
    {"i_NaCa", "nanoA", "i_NaCa", ALGEBRAIC},
    {"i_NaK", "nanoA", "i_NaK", ALGEBRAIC},
    {"i_siNa", "nanoA", "i_CaL", ALGEBRAIC},
    {"i_fNa", "nanoA", "i_f", ALGEBRAIC},
    {"F", "coulomb_per_mole", "Membrane", CONSTANT},
    {"V_i", "millimetre3", "Cell_parameters", COMPUTED_CONSTANT},
    {"V_sub", "millimetre3", "Cell_parameters", COMPUTED_CONSTANT},
    {"Iso_increase", "dimensionless", "i_NaK", COMPUTED_CONSTANT},
    {"V", "millivolt", "Membrane", ALGEBRAIC},
    {"Km_Nap", "millimolar", "i_NaK", CONSTANT},
    {"Km_Kp", "millimolar", "i_NaK", CONSTANT},
    {"i_NaK_max", "nanoA", "i_NaK", CONSTANT},
    {"blockade_NaCa", "dimensionless", "i_NaCa", CONSTANT},
    {"x2", "dimensionless", "i_NaCa", ALGEBRAIC},
    {"k21", "dimensionless", "i_NaCa", ALGEBRAIC},
    {"x1", "dimensionless", "i_NaCa", ALGEBRAIC},
    {"k12", "dimensionless", "i_NaCa", ALGEBRAIC},
    {"K_NaCa", "nanoA", "i_NaCa", CONSTANT},
    {"x4", "dimensionless", "i_NaCa", ALGEBRAIC},
    {"x3", "dimensionless", "i_NaCa", ALGEBRAIC},
    {"k41", "dimensionless", "i_NaCa", ALGEBRAIC},
    {"k23", "dimensionless", "i_NaCa", ALGEBRAIC},
    {"k34", "dimensionless", "i_NaCa", COMPUTED_CONSTANT},
    {"k43", "dimensionless", "i_NaCa", ALGEBRAIC},
    {"k32", "dimensionless", "i_NaCa", ALGEBRAIC},
    {"k14", "dimensionless", "i_NaCa", ALGEBRAIC},
    {"K3ni", "millimolar", "i_NaCa", CONSTANT},
    {"Kci", "millimolar", "i_NaCa", CONSTANT},
    {"Qci", "dimensionless", "i_NaCa", CONSTANT},
    {"di", "dimensionless", "i_NaCa", ALGEBRAIC},
    {"K1ni", "millimolar", "i_NaCa", CONSTANT},
    {"K2ni", "millimolar", "i_NaCa", CONSTANT},
    {"Qn", "dimensionless", "i_NaCa", CONSTANT},
    {"Kcni", "millimolar", "i_NaCa", CONSTANT},
    {"K3no", "millimolar", "i_NaCa", CONSTANT},
    {"Kco", "millimolar", "i_NaCa", CONSTANT},
    {"Qco", "dimensionless", "i_NaCa", CONSTANT},
    {"do", "dimensionless", "i_NaCa", ALGEBRAIC},
    {"K1no", "millimolar", "i_NaCa", CONSTANT},
    {"K2no", "millimolar", "i_NaCa", CONSTANT},
    {"j_SRCarel", "millimolar_per_second", "Ca_SR_release", ALGEBRAIC},
    {"ks", "per_second", "Ca_SR_release", CONSTANT},
    {"diff", "millimolar", "Ca_SR_release", ALGEBRAIC},
    {"kCaSR", "dimensionless", "Ca_SR_release", ALGEBRAIC},
    {"MaxSR", "dimensionless", "Ca_SR_release", CONSTANT},
    {"MinSR", "dimensionless", "Ca_SR_release", CONSTANT},
    {"EC50_SR", "millimolar", "Ca_SR_release", CONSTANT},
    {"HSR", "dimensionless", "Ca_SR_release", CONSTANT},
    {"koSRCa", "per_millimolar2_second", "Ca_SR_release", ALGEBRAIC},
    {"koCa", "per_millimolar2_second", "Ca_SR_release", CONSTANT},
    {"kiSRCa", "per_millimolar_second", "Ca_SR_release", ALGEBRAIC},
    {"kiCa", "per_millimolar_second", "Ca_SR_release", CONSTANT},
    {"kim", "per_second", "Ca_SR_release", CONSTANT},
    {"kom", "per_second", "Ca_SR_release", CONSTANT},
    {"P_tot", "dimensionless", "Ca_SR_release", ALGEBRAIC},
    {"b_up", "dimensionless", "Ca_intracellular_fluxes", COMPUTED_CONSTANT},
    {"P_up", "millimolar_per_second", "Ca_intracellular_fluxes", COMPUTED_CONSTANT},
    {"P_up_basal", "millimolar_per_second", "Ca_intracellular_fluxes", CONSTANT},
    {"j_Ca_dif", "millimolar_per_second", "Ca_intracellular_fluxes", ALGEBRAIC},
    {"tau_dif_Ca", "second", "Ca_intracellular_fluxes", CONSTANT},
    {"j_up", "millimolar_per_second", "Ca_intracellular_fluxes", ALGEBRAIC},
    {"K_up", "millimolar", "Ca_intracellular_fluxes", CONSTANT},
    {"slope_up", "millimolar", "Ca_intracellular_fluxes", CONSTANT},
    {"j_tr", "millimolar_per_second", "Ca_intracellular_fluxes", ALGEBRAIC},
    {"tau_tr", "second", "Ca_intracellular_fluxes", CONSTANT},
    {"delta_fTC", "per_second", "Ca_buffering", ALGEBRAIC},
    {"kf_TC", "per_millimolar_second", "Ca_buffering", CONSTANT},
    {"kb_TC", "per_second", "Ca_buffering", CONSTANT},
    {"delta_fTMC", "per_second", "Ca_buffering", ALGEBRAIC},
    {"kf_TMC", "per_millimolar_second", "Ca_buffering", CONSTANT},
    {"kb_TMC", "per_second", "Ca_buffering", CONSTANT},
    {"delta_fTMM", "per_second", "Ca_buffering", ALGEBRAIC},
    {"kf_TMM", "per_millimolar_second", "Ca_buffering", CONSTANT},
    {"Mgi", "millimolar", "Ca_buffering", CONSTANT},
    {"kb_TMM", "per_second", "Ca_buffering", CONSTANT},
    {"delta_fCMi", "per_second", "Ca_buffering", ALGEBRAIC},
    {"kf_CM", "per_millimolar_second", "Ca_buffering", CONSTANT},
    {"kb_CM", "per_second", "Ca_buffering", CONSTANT},
    {"delta_fCMs", "per_second", "Ca_buffering", ALGEBRAIC},
    {"delta_fCQ", "per_second", "Ca_buffering", ALGEBRAIC},
    {"kf_CQ", "per_millimolar_second", "Ca_buffering", CONSTANT},
    {"kb_CQ", "per_second", "Ca_buffering", CONSTANT},
    {"TC_tot", "millimolar", "Ca_buffering", CONSTANT},
    {"TMC_tot", "millimolar", "Ca_buffering", CONSTANT},
    {"CM_tot", "millimolar", "Ca_buffering", CONSTANT},
    {"CQ_tot", "millimolar", "Ca_buffering", CONSTANT},
    {"V_nsr", "millimetre3", "Cell_parameters", COMPUTED_CONSTANT},
    {"V_jsr", "millimetre3", "Cell_parameters", COMPUTED_CONSTANT},
    {"i_siCa", "nanoA", "i_CaL", ALGEBRAIC},
    {"i_CaT", "nanoA", "i_CaT", ALGEBRAIC},
    {"V_cell", "millimetre3", "Cell_parameters", COMPUTED_CONSTANT},
    {"L_cell", "micrometre", "Cell_parameters", CONSTANT},
    {"R_cell", "micrometre", "Cell_parameters", CONSTANT},
    {"L_sub", "micrometre", "Cell_parameters", CONSTANT},
    {"V_jsr_part", "dimensionless", "Cell_parameters", CONSTANT},
    {"V_i_part", "dimensionless", "Cell_parameters", CONSTANT},
    {"V_nsr_part", "dimensionless", "Cell_parameters", CONSTANT},
    {"i_tot", "nanoA", "Membrane", ALGEBRAIC},
    {"i_f", "nanoA", "i_f", ALGEBRAIC},
    {"i_Kur", "nanoA", "i_Kur", ALGEBRAIC},
    {"i_KACh", "nanoA", "i_KACh", ALGEBRAIC},
    {"i_CaL", "nanoA", "i_CaL", ALGEBRAIC},
    {"i_to", "nanoA", "i_to", ALGEBRAIC},
    {"i_Ks", "nanoA", "i_Ks", ALGEBRAIC},
    {"i_Kr", "nanoA", "i_Kr", ALGEBRAIC},
    {"C", "microF", "Membrane", CONSTANT},
    {"R", "joule_per_kilomole_kelvin", "Membrane", CONSTANT},
    {"T", "kelvin", "Membrane", CONSTANT},
    {"V_clamp", "millivolt", "Voltage_clamp", ALGEBRAIC},
    {"clamp_mode", "dimensionless", "Membrane", CONSTANT},
    {"V_test", "millivolt", "Voltage_clamp", CONSTANT},
    {"t_holding", "second", "Voltage_clamp", CONSTANT},
    {"t_test", "second", "Voltage_clamp", CONSTANT},
    {"V_holding", "millivolt", "Voltage_clamp", CONSTANT},
    {"G_f", "microS", "i_f", COMPUTED_CONSTANT},
    {"g_f", "microS", "i_f", CONSTANT},
    {"Km_f", "millimolar", "i_f", CONSTANT},
    {"G_f_K", "microS", "i_f", COMPUTED_CONSTANT},
    {"alpha", "dimensionless", "i_f", CONSTANT},
    {"G_f_Na", "microS", "i_f", COMPUTED_CONSTANT},
    {"g_f_Na", "microS", "i_f", COMPUTED_CONSTANT},
    {"g_f_K", "microS", "i_f", COMPUTED_CONSTANT},
    {"blockade", "dimensionless", "i_f", CONSTANT},
    {"i_fK", "nanoA", "i_f", ALGEBRAIC},
    {"ACh_shift", "millivolt", "i_f_y_gate", COMPUTED_CONSTANT},
    {"Iso_shift", "millivolt", "i_f_y_gate", COMPUTED_CONSTANT},
    {"tau_y", "second", "i_f_y_gate", ALGEBRAIC},
    {"y_infinity", "dimensionless", "i_f_y_gate", ALGEBRAIC},
    {"y_shift", "millivolt", "i_f_y_gate", CONSTANT},
    {"E_mh", "millivolt", "i_Na", ALGEBRAIC},
    {"i_Na_", "nanoA", "i_Na", ALGEBRAIC},
    {"g_Na", "microS", "i_Na", CONSTANT},
    {"i_Na_L", "nanoA", "i_Na", ALGEBRAIC},
    {"g_Na_L", "microS", "i_Na", CONSTANT},
    {"m_infinity", "dimensionless", "i_Na_m_gate", ALGEBRAIC},
    {"E0_m", "millivolt", "i_Na_m_gate", ALGEBRAIC},
    {"alpha_m", "per_second", "i_Na_m_gate", ALGEBRAIC},
    {"delta_m", "millivolt", "i_Na_m_gate", CONSTANT},
    {"beta_m", "per_second", "i_Na_m_gate", ALGEBRAIC},
    {"tau_m", "second", "i_Na_m_gate", ALGEBRAIC},
    {"h_infinity", "dimensionless", "i_Na_h_gate", ALGEBRAIC},
    {"alpha_h", "per_second", "i_Na_h_gate", ALGEBRAIC},
    {"beta_h", "per_second", "i_Na_h_gate", ALGEBRAIC},
    {"tau_h", "second", "i_Na_h_gate", ALGEBRAIC},
    {"g_Kur", "microS", "i_Kur", CONSTANT},
    {"r_Kur_infinity", "dimensionless", "i_Kur_rKur_gate", ALGEBRAIC},
    {"tau_r_Kur", "second", "i_Kur_rKur_gate", ALGEBRAIC},
    {"s_Kur_infinity", "dimensionless", "i_Kur_sKur_gate", ALGEBRAIC},
    {"tau_s_Kur", "second", "i_Kur_sKur_gate", ALGEBRAIC},
    {"Iso_increase", "dimensionless", "i_CaL", COMPUTED_CONSTANT},
    {"P_CaL", "nanoA_per_millimolar", "i_CaL", CONSTANT},
    {"i_siK", "nanoA", "i_CaL", ALGEBRAIC},
    {"ACh_block", "dimensionless", "i_CaL", COMPUTED_CONSTANT},
    {"Iso_shift_dL", "millivolt", "i_CaL_dL_gate", COMPUTED_CONSTANT},
    {"Iso_slope_dL", "dimensionless", "i_CaL_dL_gate", COMPUTED_CONSTANT},
    {"dL_infinity", "dimensionless", "i_CaL_dL_gate", ALGEBRAIC},
    {"V_dL", "millivolt", "i_CaL_dL_gate", CONSTANT},
    {"k_dL", "millivolt", "i_CaL_dL_gate", CONSTANT},
    {"tau_dL", "second", "i_CaL_dL_gate", ALGEBRAIC},
    {"alpha_dL", "per_second", "i_CaL_dL_gate", ALGEBRAIC},
    {"beta_dL", "per_second", "i_CaL_dL_gate", ALGEBRAIC},
    {"adVm", "millivolt", "i_CaL_dL_gate", ALGEBRAIC},
    {"bdVm", "millivolt", "i_CaL_dL_gate", ALGEBRAIC},
    {"fL_infinity", "dimensionless", "i_CaL_fL_gate", ALGEBRAIC},
    {"shift_fL", "millivolt", "i_CaL_fL_gate", CONSTANT},
    {"k_fL", "millivolt", "i_CaL_fL_gate", CONSTANT},
    {"tau_fL", "second", "i_CaL_fL_gate", ALGEBRAIC},
    {"fCa_infinity", "dimensionless", "i_CaL_fCa_gate", ALGEBRAIC},
    {"Km_fCa", "millimolar", "i_CaL_fCa_gate", CONSTANT},
    {"tau_fCa", "second", "i_CaL_fCa_gate", ALGEBRAIC},
    {"alpha_fCa", "per_second", "i_CaL_fCa_gate", CONSTANT},
    {"P_CaT", "nanoA_per_millimolar", "i_CaT", CONSTANT},
    {"dT_infinity", "dimensionless", "i_CaT_dT_gate", ALGEBRAIC},
    {"tau_dT", "second", "i_CaT_dT_gate", ALGEBRAIC},
    {"fT_infinity", "dimensionless", "i_CaT_fT_gate", ALGEBRAIC},
    {"tau_fT", "second", "i_CaT_fT_gate", ALGEBRAIC},
    {"offset_fT", "second", "i_CaT_fT_gate", CONSTANT},
    {"g_to", "microS", "i_to", CONSTANT},
    {"q_infinity", "dimensionless", "i_to_q_gate", ALGEBRAIC},
    {"tau_q", "second", "i_to_q_gate", ALGEBRAIC},
    {"r_infinity", "dimensionless", "i_to_r_gate", ALGEBRAIC},
    {"tau_r", "second", "i_to_r_gate", ALGEBRAIC},
    {"g_Kr", "microS", "i_Kr", CONSTANT},
    {"alfapaF", "per_second", "i_Kr_pa_gate", ALGEBRAIC},
    {"betapaF", "per_second", "i_Kr_pa_gate", ALGEBRAIC},
    {"pa_infinity", "dimensionless", "i_Kr_pa_gate", ALGEBRAIC},
    {"tau_paS", "second", "i_Kr_pa_gate", ALGEBRAIC},
    {"tau_paF", "second", "i_Kr_pa_gate", ALGEBRAIC},
    {"tau_pi", "second", "i_Kr_pi_gate", ALGEBRAIC},
    {"pi_infinity", "dimensionless", "i_Kr_pi_gate", ALGEBRAIC},
    {"g_Ks", "microS", "i_Ks", COMPUTED_CONSTANT},
    {"g_Ks_", "microS", "i_Ks", CONSTANT},
    {"E_Ks", "millivolt", "i_Ks", ALGEBRAIC},
    {"Iso_shift", "millivolt", "i_Ks_n_gate", COMPUTED_CONSTANT},
    {"n_infinity", "dimensionless", "i_Ks_n_gate", ALGEBRAIC},
    {"tau_n", "second", "i_Ks_n_gate", ALGEBRAIC},
    {"alpha_n", "per_second", "i_Ks_n_gate", ALGEBRAIC},
    {"beta_n", "per_second", "i_Ks_n_gate", ALGEBRAIC},
    {"ACh_on", "dimensionless", "i_KACh", CONSTANT},
    {"g_KACh", "microS", "i_KACh", CONSTANT},
    {"alpha_a", "per_second", "i_KACh_a_gate", COMPUTED_CONSTANT},
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
    constants[4] = 140.0;
    constants[7] = 5.4;
    constants[8] = 140.0;
    constants[10] = 1.8;
    constants[11] = 1.0;
    constants[17] = 96485.3415;
    constants[22] = 14.0;
    constants[23] = 1.4;
    constants[24] = 0.08105;
    constants[25] = 0.0;
    constants[30] = 3.343;
    constants[39] = 26.44;
    constants[40] = 0.0207;
    constants[41] = 0.1369;
    constants[43] = 395.3;
    constants[44] = 2.289;
    constants[45] = 0.4315;
    constants[46] = 26.44;
    constants[47] = 4.663;
    constants[48] = 3.663;
    constants[49] = 0.0;
    constants[51] = 1628.0;
    constants[52] = 561.4;
    constants[54] = 148041085.1;
    constants[57] = 15.0;
    constants[58] = 1.0;
    constants[59] = 0.45;
    constants[60] = 2.5;
    constants[62] = 10000.0;
    constants[64] = 500.0;
    constants[65] = 5.0;
    constants[66] = 660.0;
    constants[70] = 5.0;
    constants[72] = 5.469e-5;
    constants[74] = 0.000286113;
    constants[75] = 5.0e-5;
    constants[77] = 0.04;
    constants[79] = 88800.0;
    constants[80] = 446.0;
    constants[82] = 227700.0;
    constants[83] = 7.51;
    constants[85] = 2277.0;
    constants[86] = 2.5;
    constants[87] = 751.0;
    constants[89] = 1.642e6;
    constants[90] = 542.0;
    constants[93] = 175.4;
    constants[94] = 445.0;
    constants[95] = 0.031;
    constants[96] = 0.062;
    constants[97] = 0.045;
    constants[98] = 10.0;
    constants[104] = 67.0;
    constants[105] = 3.9;
    constants[106] = 0.02;
    constants[107] = 0.0012;
    constants[108] = 0.46;
    constants[109] = 0.0116;
    constants[118] = 5.7e-5;
    constants[119] = 8314.472;
    constants[120] = 310.0;
    constants[122] = 0.0;
    constants[123] = -35.0;
    constants[124] = 0.5;
    constants[125] = 0.5;
    constants[126] = -45.0;
    constants[128] = 0.00427;
    constants[129] = 45.0;
    constants[131] = 0.5927;
    constants[135] = 0.0;
    constants[141] = 0.0;
    constants[144] = 0.0223;
    constants[146] = 0.0;
    constants[150] = 1.0e-5;
    constants[157] = 0.1539e-3;
    constants[163] = 0.4578;
    constants[169] = -16.4508;
    constants[170] = 4.3371;
    constants[177] = 0.0;
    constants[178] = 0.0;
    constants[181] = 0.000338;
    constants[183] = 0.0075;
    constants[184] = 0.04132;
    constants[189] = 0.0;
    constants[190] = 3.5e-3;
    constants[195] = 0.00424;
    constants[204] = 0.00065;
    constants[211] = 1.0;
    constants[212] = 0.00345;
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
    computedConstants[3] = constants[119]*constants[120]/constants[17];
    computedConstants[6] = computedConstants[3]*log(constants[7]/constants[8]);
    computedConstants[20] = (constants[1] > 0.0)?1.2:1.0;
    computedConstants[35] = constants[4]/(constants[47]+constants[4]);
    computedConstants[68] = (constants[1] > 0.0)?-0.25:(constants[0] > 0.0)?0.7*constants[0]/(0.00009+constants[0]):0.0;
    computedConstants[69] = constants[70]*(1.0-computedConstants[68]);
    computedConstants[103] = 0.000000001*3.14159265358979*pow(constants[105], 2.0)*constants[104];
    computedConstants[19] = 0.000000001*2.0*3.14159265358979*constants[106]*(constants[105]-constants[106]/2.0)*constants[104];
    computedConstants[100] = constants[107]*computedConstants[103];
    computedConstants[18] = constants[108]*computedConstants[103]-computedConstants[19];
    computedConstants[99] = constants[109]*computedConstants[103];
    computedConstants[127] = constants[128]/(constants[7]/(constants[7]+constants[129]));
    computedConstants[130] = computedConstants[127]/(constants[131]+1.0);
    computedConstants[132] = constants[131]*computedConstants[130];
    computedConstants[133] = computedConstants[132]*constants[7]/(constants[7]+constants[129]);
    computedConstants[134] = computedConstants[130]*constants[7]/(constants[7]+constants[129]);
    computedConstants[137] = (constants[0] > 0.0)?-1.0-9.898*pow(1.0*constants[0], 0.618)/(pow(1.0*constants[0], 0.618)+0.00122423):0.0;
    computedConstants[138] = (constants[1] > 0.0)?7.5:0.0;
    computedConstants[162] = (constants[1] > 0.0)?1.23:1.0;
    computedConstants[165] = 0.31*constants[0]/(constants[0]+0.00009);
    computedConstants[166] = (constants[1] > 0.0)?-8.0:0.0;
    computedConstants[167] = (constants[1] > 0.0)?-27.0:0.0;
    computedConstants[203] = (constants[1] > 0.0)?1.2*constants[204]:constants[204];
    computedConstants[206] = (constants[1] > 0.0)?-14.0:0.0;
    computedConstants[213] = (3.5988-0.025641)/(1.0+0.0000012155/pow(1.0*constants[0], 1.6951))+0.025641;
}

void computeRates(double voi, double *states, double *rates, double *constants, double *computedConstants, double *algebraic)
{
    algebraic[5] = states[1];
    algebraic[142] = computedConstants[3]*log((constants[4]+0.12*constants[7])/(algebraic[5]+0.12*constants[8]));
    algebraic[121] = ((voi > constants[124]) && (voi < constants[124]+constants[125]))?constants[123]:constants[126];
    algebraic[21] = (constants[122] >= 1.0)?algebraic[121]:states[15];
    algebraic[143] = constants[144]*pow(states[18], 3.0)*states[17]*(algebraic[21]-algebraic[142]);
    algebraic[145] = constants[146]*pow(states[18], 3.0)*(algebraic[21]-algebraic[142]);
    algebraic[12] = algebraic[143]+algebraic[145];
    algebraic[15] = 0.0000185*constants[163]*(algebraic[21]-0.0)/(computedConstants[3]*(1.0-exp(-1.0*(algebraic[21]-0.0)/computedConstants[3])))*(algebraic[5]-constants[4]*exp(-1.0*(algebraic[21]-0.0)/computedConstants[3]))*states[23]*states[22]*states[21];
    algebraic[2] = computedConstants[3]*log(constants[4]/algebraic[5]);
    algebraic[16] = states[16]*computedConstants[133]*(algebraic[21]-algebraic[2])*(1.0-constants[135]);
    algebraic[14] = computedConstants[20]*constants[24]*pow(1.0+pow(constants[23]/constants[7], 1.2), -1.0)*pow(1.0+pow(constants[22]/algebraic[5], 1.3), -1.0)*pow(1.0+exp(-(algebraic[21]-algebraic[2]+110.0)/20.0), -1.0);
    algebraic[50] = 1.0+constants[10]/constants[48]*(1.0+exp(constants[49]*algebraic[21]/computedConstants[3]))+constants[4]/constants[51]*(1.0+constants[4]/constants[52]*(1.0+constants[4]/constants[47]));
    algebraic[27] = constants[10]/constants[48]*exp(constants[49]*algebraic[21]/computedConstants[3])/algebraic[50];
    algebraic[42] = 1.0+states[0]/constants[40]*(1.0+exp(-constants[41]*algebraic[21]/computedConstants[3])+algebraic[5]/constants[46])+algebraic[5]/constants[43]*(1.0+algebraic[5]/constants[44]*(1.0+algebraic[5]/constants[39]));
    algebraic[29] = states[0]/constants[40]*exp(-constants[41]*algebraic[21]/computedConstants[3])/algebraic[42];
    algebraic[36] = algebraic[5]/(constants[39]+algebraic[5]);
    algebraic[37] = exp(constants[45]*algebraic[21]/(2.0*computedConstants[3]));
    algebraic[33] = exp(-constants[45]*algebraic[21]/(2.0*computedConstants[3]));
    algebraic[38] = algebraic[5]/constants[43]*algebraic[5]/constants[44]*(1.0+algebraic[5]/constants[39])*exp(constants[45]*algebraic[21]/(2.0*computedConstants[3]))/algebraic[42];
    algebraic[26] = algebraic[37]*algebraic[36]*(algebraic[38]+algebraic[29])+algebraic[33]*algebraic[29]*(computedConstants[35]+algebraic[37]);
    algebraic[34] = constants[4]/constants[51]*constants[4]/constants[52]*(1.0+constants[4]/constants[47])*exp(-constants[45]*algebraic[21]/(2.0*computedConstants[3]))/algebraic[50];
    algebraic[28] = algebraic[33]*computedConstants[35]*(algebraic[34]+algebraic[27])+algebraic[27]*algebraic[37]*(algebraic[36]+algebraic[33]);
    algebraic[31] = algebraic[34]*computedConstants[35]*(algebraic[38]+algebraic[29])+algebraic[38]*algebraic[27]*(computedConstants[35]+algebraic[37]);
    algebraic[32] = algebraic[38]*algebraic[36]*(algebraic[34]+algebraic[27])+algebraic[29]*algebraic[34]*(algebraic[36]+algebraic[33]);
    algebraic[13] = (1.0-constants[25])*constants[30]*(algebraic[26]*algebraic[27]-algebraic[28]*algebraic[29])/(algebraic[28]+algebraic[26]+algebraic[32]+algebraic[31]);
    rates[1] = (1.0-constants[11])*-1.0*(algebraic[12]+algebraic[16]+algebraic[15]+3.0*algebraic[14]+3.0*algebraic[13])/(1.0*(computedConstants[18]+computedConstants[19])*constants[17]);
    algebraic[56] = constants[57]-(constants[57]-constants[58])/(1.0+pow(constants[59]/states[2], constants[60]));
    algebraic[63] = constants[64]*algebraic[56];
    algebraic[61] = constants[62]/algebraic[56];
    rates[4] = constants[65]*states[5]-algebraic[63]*states[0]*states[4]-(algebraic[61]*pow(states[0], 2.0)*states[4]-constants[66]*states[3]);
    rates[3] = algebraic[61]*pow(states[0], 2.0)*states[4]-constants[66]*states[3]-(algebraic[63]*states[0]*states[3]-constants[65]*states[6]);
    rates[6] = algebraic[63]*states[0]*states[3]-constants[65]*states[6]-(constants[66]*states[6]-algebraic[61]*pow(states[0], 2.0)*states[5]);
    rates[5] = constants[66]*states[6]-algebraic[61]*pow(states[0], 2.0)*states[5]-(constants[65]*states[5]-algebraic[63]*states[0]*states[4]);
    algebraic[78] = constants[79]*states[7]*(1.0-states[9])-constants[80]*states[9];
    rates[9] = algebraic[78];
    algebraic[81] = constants[82]*states[7]*(1.0-(states[10]+states[11]))-constants[83]*states[10];
    rates[10] = algebraic[81];
    algebraic[84] = constants[85]*constants[86]*(1.0-(states[10]+states[11]))-constants[87]*states[11];
    rates[11] = algebraic[84];
    algebraic[88] = constants[89]*states[7]*(1.0-states[12])-constants[90]*states[12];
    rates[12] = algebraic[88];
    algebraic[91] = constants[89]*states[0]*(1.0-states[13])-constants[90]*states[13];
    rates[13] = algebraic[91];
    algebraic[92] = constants[93]*states[2]*(1.0-states[14])-constants[94]*states[14];
    rates[14] = algebraic[92];
    algebraic[71] = (states[0]-states[7])/constants[72];
    algebraic[73] = computedConstants[69]/(1.0+exp((-states[7]+constants[74])/constants[75]));
    rates[7] = 1.0*(algebraic[71]*computedConstants[19]-algebraic[73]*computedConstants[99])/computedConstants[18]-(constants[97]*algebraic[88]+constants[95]*algebraic[78]+constants[96]*algebraic[81]);
    algebraic[53] = constants[54]*states[3]*(states[2]-states[0]);
    algebraic[101] = 2.0*constants[163]*(algebraic[21]-0.0)/(computedConstants[3]*(1.0-exp(-1.0*(algebraic[21]-0.0)*2.0/computedConstants[3])))*(states[0]-constants[10]*exp(-2.0*(algebraic[21]-0.0)/computedConstants[3]))*states[23]*states[22]*states[21];
    algebraic[102] = 2.0*constants[184]*algebraic[21]/(computedConstants[3]*(1.0-exp(-1.0*algebraic[21]*2.0/computedConstants[3])))*(states[0]-constants[10]*exp(-2.0*algebraic[21]/computedConstants[3]))*states[25]*states[24];
    rates[0] = algebraic[53]*computedConstants[100]/computedConstants[19]-((algebraic[101]+algebraic[102]-2.0*algebraic[13])/(2.0*constants[17]*computedConstants[19])+algebraic[71]+constants[97]*algebraic[91]);
    algebraic[76] = (states[8]-states[2])/constants[77];
    rates[8] = algebraic[73]-algebraic[76]*computedConstants[100]/computedConstants[99];
    rates[2] = algebraic[76]-(algebraic[53]+constants[98]*algebraic[92]);
    algebraic[136] = states[16]*computedConstants[134]*(algebraic[21]-computedConstants[6])*(1.0-constants[135]);
    algebraic[111] = algebraic[16]+algebraic[136];
    algebraic[112] = constants[157]*states[20]*states[19]*(algebraic[21]-computedConstants[6]);
    algebraic[113] = (constants[0] > 0.0)?constants[211]*constants[212]*(algebraic[21]-computedConstants[6])*(1.0+exp((algebraic[21]+20.0)/20.0))*states[32]:0.0;
    algebraic[164] = 0.000365*constants[163]*(algebraic[21]-0.0)/(computedConstants[3]*(1.0-exp(-1.0*(algebraic[21]-0.0)/computedConstants[3])))*(constants[8]-constants[7]*exp(-1.0*(algebraic[21]-0.0)/computedConstants[3]))*states[23]*states[22]*states[21];
    algebraic[114] = (algebraic[101]+algebraic[164]+algebraic[15])*(1.0-computedConstants[165])*1.0*computedConstants[162];
    algebraic[115] = constants[190]*(algebraic[21]-computedConstants[6])*states[27]*states[26];
    algebraic[205] = computedConstants[3]*log((constants[7]+0.12*constants[4])/(constants[8]+0.12*algebraic[5]));
    algebraic[116] = computedConstants[203]*(algebraic[21]-algebraic[205])*pow(states[31], 2.0);
    algebraic[117] = constants[195]*(algebraic[21]-computedConstants[6])*(0.9*states[29]+0.1*states[30])*states[28];
    algebraic[110] = algebraic[111]+algebraic[117]+algebraic[116]+algebraic[115]+algebraic[14]+algebraic[13]+algebraic[12]+algebraic[114]+algebraic[102]+algebraic[113]+algebraic[112];
    rates[15] = -algebraic[110]/constants[118];
    algebraic[140] = (algebraic[21] < -(80.0-computedConstants[137]-computedConstants[138]-constants[141]))?0.01329+0.99921/(1.0+exp((algebraic[21]+97.134-computedConstants[137]-computedConstants[138]-constants[141])/8.1752)):0.0002501*exp(-(algebraic[21]-computedConstants[137]-computedConstants[138]-constants[141])/12.861);
    algebraic[139] = 1.0/(0.36*(algebraic[21]+148.8-computedConstants[137]-computedConstants[138])/(exp(0.066*(algebraic[21]+148.8-computedConstants[137]-computedConstants[138]))-1.0)+0.1*(algebraic[21]+87.3-computedConstants[137]-computedConstants[138])/(1.0-exp(-0.2*(algebraic[21]+87.3-computedConstants[137]-computedConstants[138]))))-0.054;
    rates[16] = (algebraic[140]-states[16])/algebraic[139];
    algebraic[147] = 1.0/(1.0+exp(-(algebraic[21]+42.0504)/8.3106));
    algebraic[148] = algebraic[21]+41.0;
    algebraic[149] = (fabs(algebraic[148]) < constants[150])?2000.0:200.0*algebraic[148]/(1.0-exp(-0.1*algebraic[148]));
    algebraic[151] = 8000.0*exp(-0.056*(algebraic[21]+66.0));
    algebraic[152] = 1.0/(algebraic[149]+algebraic[151]);
    rates[18] = (algebraic[147]-states[18])/algebraic[152];
    algebraic[153] = 1.0/(1.0+exp((algebraic[21]+69.804)/4.4565));
    algebraic[154] = 20.0*exp(-0.125*(algebraic[21]+75.0));
    algebraic[155] = 2000.0/(320.0*exp(-0.1*(algebraic[21]+75.0))+1.0);
    algebraic[156] = 1.0/(algebraic[154]+algebraic[155]);
    rates[17] = (algebraic[153]-states[17])/algebraic[156];
    algebraic[158] = 1.0/(1.0+exp((algebraic[21]+6.0)/-8.6));
    algebraic[159] = 0.009/(1.0+exp((algebraic[21]+5.0)/12.0))+0.0005;
    rates[20] = (algebraic[158]-states[20])/algebraic[159];
    algebraic[160] = 1.0/(1.0+exp((algebraic[21]+7.5)/10.0));
    algebraic[161] = 0.59/(1.0+exp((algebraic[21]+60.0)/10.0))+3.05;
    rates[19] = (algebraic[160]-states[19])/algebraic[161];
    algebraic[168] = 1.0/(1.0+exp(-(algebraic[21]-constants[169]-computedConstants[166])/(constants[170]*(1.0+computedConstants[167]/100.0))));
    algebraic[174] = (algebraic[21] == -41.8)?-41.80001:(algebraic[21] == 0.0)?0.0:(algebraic[21] == -6.8)?-6.80001:algebraic[21];
    algebraic[172] = -0.02839*(algebraic[174]+41.8)/(exp(-(algebraic[174]+41.8)/2.5)-1.0)-0.0849*(algebraic[174]+6.8)/(exp(-(algebraic[174]+6.8)/4.8)-1.0);
    algebraic[175] = (algebraic[21] == -1.8)?-1.80001:algebraic[21];
    algebraic[173] = 0.01143*(algebraic[175]+1.8)/(exp((algebraic[175]+1.8)/2.5)-1.0);
    algebraic[171] = 0.001/(algebraic[172]+algebraic[173]);
    rates[23] = (algebraic[168]-states[23])/algebraic[171];
    algebraic[176] = 1.0/(1.0+exp((algebraic[21]+37.4+constants[177])/(5.3+constants[178])));
    algebraic[179] = 0.001*(44.3+230.0*exp(-pow((algebraic[21]+36.0)/10.0, 2.0)));
    rates[22] = (algebraic[176]-states[22])/algebraic[179];
    algebraic[180] = constants[181]/(constants[181]+states[0]);
    algebraic[182] = 0.001*algebraic[180]/constants[183];
    rates[21] = (algebraic[180]-states[21])/algebraic[182];
    algebraic[185] = 1.0/(1.0+exp(-(algebraic[21]+38.3)/5.5));
    algebraic[186] = 0.001/(1.068*exp((algebraic[21]+38.3)/30.0)+1.068*exp(-(algebraic[21]+38.3)/30.0));
    rates[25] = (algebraic[185]-states[25])/algebraic[186];
    algebraic[187] = 1.0/(1.0+exp((algebraic[21]+58.7)/3.8));
    algebraic[188] = 1.0/(16.67*exp(-(algebraic[21]+75.0)/83.3)+16.67*exp((algebraic[21]+75.0)/15.38))+constants[189];
    rates[24] = (algebraic[187]-states[24])/algebraic[188];
    algebraic[191] = 1.0/(1.0+exp((algebraic[21]+49.0)/13.0));
    algebraic[192] = 0.001*0.6*(65.17/(0.57*exp(-0.08*(algebraic[21]+44.0))+0.065*exp(0.1*(algebraic[21]+45.93)))+10.1);
    rates[27] = (algebraic[191]-states[27])/algebraic[192];
    algebraic[193] = 1.0/(1.0+exp(-(algebraic[21]-19.3)/15.0));
    algebraic[194] = 0.001*0.66*1.4*(15.59/(1.037*exp(0.09*(algebraic[21]+30.61))+0.369*exp(-0.12*(algebraic[21]+23.84)))+2.98);
    rates[26] = (algebraic[193]-states[26])/algebraic[194];
    algebraic[198] = 1.0/(1.0+exp(-(algebraic[21]+10.0144)/7.6607));
    algebraic[199] = 0.84655354/(4.2*exp(algebraic[21]/17.0)+0.15*exp(-algebraic[21]/21.6));
    rates[30] = (algebraic[198]-states[30])/algebraic[199];
    algebraic[200] = 1.0/(30.0*exp(algebraic[21]/10.0)+exp(-algebraic[21]/12.0));
    rates[29] = (algebraic[198]-states[29])/algebraic[200];
    algebraic[202] = 1.0/(1.0+exp((algebraic[21]+28.6)/17.1));
    algebraic[201] = 1.0/(100.0*exp(-algebraic[21]/54.645)+656.0*exp(algebraic[21]/106.157));
    rates[28] = (algebraic[202]-states[28])/algebraic[201];
    algebraic[207] = sqrt(1.0/(1.0+exp(-(algebraic[21]+0.6383-computedConstants[206])/10.7071)));
    algebraic[209] = 28.0/(1.0+exp(-(algebraic[21]-40.0-computedConstants[206])/3.0));
    algebraic[210] = 1.0*exp(-(algebraic[21]-computedConstants[206]-5.0)/25.0);
    algebraic[208] = 1.0/(algebraic[209]+algebraic[210]);
    rates[31] = (algebraic[207]-states[31])/algebraic[208];
    algebraic[214] = 10.0*exp(0.0133*(algebraic[21]+40.0));
    algebraic[215] = computedConstants[213]/(computedConstants[213]+algebraic[214]);
    algebraic[216] = 1.0/(computedConstants[213]+algebraic[214]);
    rates[32] = (algebraic[215]-states[32])/algebraic[216];
}

void computeVariables(double voi, double *states, double *rates, double *constants, double *computedConstants, double *algebraic)
{
    algebraic[5] = states[1];
    algebraic[2] = computedConstants[3]*log(constants[4]/algebraic[5]);
    algebraic[9] = 0.5*computedConstants[3]*log(constants[10]/states[0]);
    algebraic[21] = (constants[122] >= 1.0)?algebraic[121]:states[15];
    algebraic[14] = computedConstants[20]*constants[24]*pow(1.0+pow(constants[23]/constants[7], 1.2), -1.0)*pow(1.0+pow(constants[22]/algebraic[5], 1.3), -1.0)*pow(1.0+exp(-(algebraic[21]-algebraic[2]+110.0)/20.0), -1.0);
    algebraic[50] = 1.0+constants[10]/constants[48]*(1.0+exp(constants[49]*algebraic[21]/computedConstants[3]))+constants[4]/constants[51]*(1.0+constants[4]/constants[52]*(1.0+constants[4]/constants[47]));
    algebraic[27] = constants[10]/constants[48]*exp(constants[49]*algebraic[21]/computedConstants[3])/algebraic[50];
    algebraic[42] = 1.0+states[0]/constants[40]*(1.0+exp(-constants[41]*algebraic[21]/computedConstants[3])+algebraic[5]/constants[46])+algebraic[5]/constants[43]*(1.0+algebraic[5]/constants[44]*(1.0+algebraic[5]/constants[39]));
    algebraic[29] = states[0]/constants[40]*exp(-constants[41]*algebraic[21]/computedConstants[3])/algebraic[42];
    algebraic[36] = algebraic[5]/(constants[39]+algebraic[5]);
    algebraic[37] = exp(constants[45]*algebraic[21]/(2.0*computedConstants[3]));
    algebraic[33] = exp(-constants[45]*algebraic[21]/(2.0*computedConstants[3]));
    algebraic[38] = algebraic[5]/constants[43]*algebraic[5]/constants[44]*(1.0+algebraic[5]/constants[39])*exp(constants[45]*algebraic[21]/(2.0*computedConstants[3]))/algebraic[42];
    algebraic[26] = algebraic[37]*algebraic[36]*(algebraic[38]+algebraic[29])+algebraic[33]*algebraic[29]*(computedConstants[35]+algebraic[37]);
    algebraic[34] = constants[4]/constants[51]*constants[4]/constants[52]*(1.0+constants[4]/constants[47])*exp(-constants[45]*algebraic[21]/(2.0*computedConstants[3]))/algebraic[50];
    algebraic[28] = algebraic[33]*computedConstants[35]*(algebraic[34]+algebraic[27])+algebraic[27]*algebraic[37]*(algebraic[36]+algebraic[33]);
    algebraic[31] = algebraic[34]*computedConstants[35]*(algebraic[38]+algebraic[29])+algebraic[38]*algebraic[27]*(computedConstants[35]+algebraic[37]);
    algebraic[32] = algebraic[38]*algebraic[36]*(algebraic[34]+algebraic[27])+algebraic[29]*algebraic[34]*(algebraic[36]+algebraic[33]);
    algebraic[13] = (1.0-constants[25])*constants[30]*(algebraic[26]*algebraic[27]-algebraic[28]*algebraic[29])/(algebraic[28]+algebraic[26]+algebraic[32]+algebraic[31]);
    algebraic[53] = constants[54]*states[3]*(states[2]-states[0]);
    algebraic[55] = states[2]-states[0];
    algebraic[56] = constants[57]-(constants[57]-constants[58])/(1.0+pow(constants[59]/states[2], constants[60]));
    algebraic[61] = constants[62]/algebraic[56];
    algebraic[63] = constants[64]*algebraic[56];
    algebraic[67] = states[4]+states[3]+states[6]+states[5];
    algebraic[71] = (states[0]-states[7])/constants[72];
    algebraic[73] = computedConstants[69]/(1.0+exp((-states[7]+constants[74])/constants[75]));
    algebraic[76] = (states[8]-states[2])/constants[77];
    algebraic[78] = constants[79]*states[7]*(1.0-states[9])-constants[80]*states[9];
    algebraic[81] = constants[82]*states[7]*(1.0-(states[10]+states[11]))-constants[83]*states[10];
    algebraic[84] = constants[85]*constants[86]*(1.0-(states[10]+states[11]))-constants[87]*states[11];
    algebraic[88] = constants[89]*states[7]*(1.0-states[12])-constants[90]*states[12];
    algebraic[91] = constants[89]*states[0]*(1.0-states[13])-constants[90]*states[13];
    algebraic[92] = constants[93]*states[2]*(1.0-states[14])-constants[94]*states[14];
    algebraic[16] = states[16]*computedConstants[133]*(algebraic[21]-algebraic[2])*(1.0-constants[135]);
    algebraic[136] = states[16]*computedConstants[134]*(algebraic[21]-computedConstants[6])*(1.0-constants[135]);
    algebraic[111] = algebraic[16]+algebraic[136];
    algebraic[112] = constants[157]*states[20]*states[19]*(algebraic[21]-computedConstants[6]);
    algebraic[113] = (constants[0] > 0.0)?constants[211]*constants[212]*(algebraic[21]-computedConstants[6])*(1.0+exp((algebraic[21]+20.0)/20.0))*states[32]:0.0;
    algebraic[102] = 2.0*constants[184]*algebraic[21]/(computedConstants[3]*(1.0-exp(-1.0*algebraic[21]*2.0/computedConstants[3])))*(states[0]-constants[10]*exp(-2.0*algebraic[21]/computedConstants[3]))*states[25]*states[24];
    algebraic[101] = 2.0*constants[163]*(algebraic[21]-0.0)/(computedConstants[3]*(1.0-exp(-1.0*(algebraic[21]-0.0)*2.0/computedConstants[3])))*(states[0]-constants[10]*exp(-2.0*(algebraic[21]-0.0)/computedConstants[3]))*states[23]*states[22]*states[21];
    algebraic[15] = 0.0000185*constants[163]*(algebraic[21]-0.0)/(computedConstants[3]*(1.0-exp(-1.0*(algebraic[21]-0.0)/computedConstants[3])))*(algebraic[5]-constants[4]*exp(-1.0*(algebraic[21]-0.0)/computedConstants[3]))*states[23]*states[22]*states[21];
    algebraic[164] = 0.000365*constants[163]*(algebraic[21]-0.0)/(computedConstants[3]*(1.0-exp(-1.0*(algebraic[21]-0.0)/computedConstants[3])))*(constants[8]-constants[7]*exp(-1.0*(algebraic[21]-0.0)/computedConstants[3]))*states[23]*states[22]*states[21];
    algebraic[114] = (algebraic[101]+algebraic[164]+algebraic[15])*(1.0-computedConstants[165])*1.0*computedConstants[162];
    algebraic[142] = computedConstants[3]*log((constants[4]+0.12*constants[7])/(algebraic[5]+0.12*constants[8]));
    algebraic[143] = constants[144]*pow(states[18], 3.0)*states[17]*(algebraic[21]-algebraic[142]);
    algebraic[145] = constants[146]*pow(states[18], 3.0)*(algebraic[21]-algebraic[142]);
    algebraic[12] = algebraic[143]+algebraic[145];
    algebraic[115] = constants[190]*(algebraic[21]-computedConstants[6])*states[27]*states[26];
    algebraic[205] = computedConstants[3]*log((constants[7]+0.12*constants[4])/(constants[8]+0.12*algebraic[5]));
    algebraic[116] = computedConstants[203]*(algebraic[21]-algebraic[205])*pow(states[31], 2.0);
    algebraic[117] = constants[195]*(algebraic[21]-computedConstants[6])*(0.9*states[29]+0.1*states[30])*states[28];
    algebraic[110] = algebraic[111]+algebraic[117]+algebraic[116]+algebraic[115]+algebraic[14]+algebraic[13]+algebraic[12]+algebraic[114]+algebraic[102]+algebraic[113]+algebraic[112];
    algebraic[139] = 1.0/(0.36*(algebraic[21]+148.8-computedConstants[137]-computedConstants[138])/(exp(0.066*(algebraic[21]+148.8-computedConstants[137]-computedConstants[138]))-1.0)+0.1*(algebraic[21]+87.3-computedConstants[137]-computedConstants[138])/(1.0-exp(-0.2*(algebraic[21]+87.3-computedConstants[137]-computedConstants[138]))))-0.054;
    algebraic[140] = (algebraic[21] < -(80.0-computedConstants[137]-computedConstants[138]-constants[141]))?0.01329+0.99921/(1.0+exp((algebraic[21]+97.134-computedConstants[137]-computedConstants[138]-constants[141])/8.1752)):0.0002501*exp(-(algebraic[21]-computedConstants[137]-computedConstants[138]-constants[141])/12.861);
    algebraic[147] = 1.0/(1.0+exp(-(algebraic[21]+42.0504)/8.3106));
    algebraic[148] = algebraic[21]+41.0;
    algebraic[149] = (fabs(algebraic[148]) < constants[150])?2000.0:200.0*algebraic[148]/(1.0-exp(-0.1*algebraic[148]));
    algebraic[151] = 8000.0*exp(-0.056*(algebraic[21]+66.0));
    algebraic[152] = 1.0/(algebraic[149]+algebraic[151]);
    algebraic[153] = 1.0/(1.0+exp((algebraic[21]+69.804)/4.4565));
    algebraic[154] = 20.0*exp(-0.125*(algebraic[21]+75.0));
    algebraic[155] = 2000.0/(320.0*exp(-0.1*(algebraic[21]+75.0))+1.0);
    algebraic[156] = 1.0/(algebraic[154]+algebraic[155]);
    algebraic[158] = 1.0/(1.0+exp((algebraic[21]+6.0)/-8.6));
    algebraic[159] = 0.009/(1.0+exp((algebraic[21]+5.0)/12.0))+0.0005;
    algebraic[160] = 1.0/(1.0+exp((algebraic[21]+7.5)/10.0));
    algebraic[161] = 0.59/(1.0+exp((algebraic[21]+60.0)/10.0))+3.05;
    algebraic[168] = 1.0/(1.0+exp(-(algebraic[21]-constants[169]-computedConstants[166])/(constants[170]*(1.0+computedConstants[167]/100.0))));
    algebraic[174] = (algebraic[21] == -41.8)?-41.80001:(algebraic[21] == 0.0)?0.0:(algebraic[21] == -6.8)?-6.80001:algebraic[21];
    algebraic[172] = -0.02839*(algebraic[174]+41.8)/(exp(-(algebraic[174]+41.8)/2.5)-1.0)-0.0849*(algebraic[174]+6.8)/(exp(-(algebraic[174]+6.8)/4.8)-1.0);
    algebraic[175] = (algebraic[21] == -1.8)?-1.80001:algebraic[21];
    algebraic[173] = 0.01143*(algebraic[175]+1.8)/(exp((algebraic[175]+1.8)/2.5)-1.0);
    algebraic[171] = 0.001/(algebraic[172]+algebraic[173]);
    algebraic[176] = 1.0/(1.0+exp((algebraic[21]+37.4+constants[177])/(5.3+constants[178])));
    algebraic[179] = 0.001*(44.3+230.0*exp(-pow((algebraic[21]+36.0)/10.0, 2.0)));
    algebraic[180] = constants[181]/(constants[181]+states[0]);
    algebraic[182] = 0.001*algebraic[180]/constants[183];
    algebraic[185] = 1.0/(1.0+exp(-(algebraic[21]+38.3)/5.5));
    algebraic[186] = 0.001/(1.068*exp((algebraic[21]+38.3)/30.0)+1.068*exp(-(algebraic[21]+38.3)/30.0));
    algebraic[187] = 1.0/(1.0+exp((algebraic[21]+58.7)/3.8));
    algebraic[188] = 1.0/(16.67*exp(-(algebraic[21]+75.0)/83.3)+16.67*exp((algebraic[21]+75.0)/15.38))+constants[189];
    algebraic[191] = 1.0/(1.0+exp((algebraic[21]+49.0)/13.0));
    algebraic[192] = 0.001*0.6*(65.17/(0.57*exp(-0.08*(algebraic[21]+44.0))+0.065*exp(0.1*(algebraic[21]+45.93)))+10.1);
    algebraic[193] = 1.0/(1.0+exp(-(algebraic[21]-19.3)/15.0));
    algebraic[194] = 0.001*0.66*1.4*(15.59/(1.037*exp(0.09*(algebraic[21]+30.61))+0.369*exp(-0.12*(algebraic[21]+23.84)))+2.98);
    algebraic[196] = 1.0/(1.0+exp(-(algebraic[21]+23.2)/6.6))/(0.84655354/(37.2*exp(algebraic[21]/11.9)+0.96*exp(-algebraic[21]/18.5)));
    algebraic[197] = 4.0*((37.2*exp(algebraic[21]/15.9)+0.96*exp(-algebraic[21]/22.5))/0.84655354-1.0/(1.0+exp(-(algebraic[21]+23.2)/10.6))/(0.84655354/(37.2*exp(algebraic[21]/15.9)+0.96*exp(-algebraic[21]/22.5))));
    algebraic[198] = 1.0/(1.0+exp(-(algebraic[21]+10.0144)/7.6607));
    algebraic[199] = 0.84655354/(4.2*exp(algebraic[21]/17.0)+0.15*exp(-algebraic[21]/21.6));
    algebraic[200] = 1.0/(30.0*exp(algebraic[21]/10.0)+exp(-algebraic[21]/12.0));
    algebraic[201] = 1.0/(100.0*exp(-algebraic[21]/54.645)+656.0*exp(algebraic[21]/106.157));
    algebraic[202] = 1.0/(1.0+exp((algebraic[21]+28.6)/17.1));
    algebraic[207] = sqrt(1.0/(1.0+exp(-(algebraic[21]+0.6383-computedConstants[206])/10.7071)));
    algebraic[209] = 28.0/(1.0+exp(-(algebraic[21]-40.0-computedConstants[206])/3.0));
    algebraic[210] = 1.0*exp(-(algebraic[21]-computedConstants[206]-5.0)/25.0);
    algebraic[208] = 1.0/(algebraic[209]+algebraic[210]);
    algebraic[214] = 10.0*exp(0.0133*(algebraic[21]+40.0));
    algebraic[215] = computedConstants[213]/(computedConstants[213]+algebraic[214]);
    algebraic[216] = 1.0/(computedConstants[213]+algebraic[214]);
}

/* The content of this file was generated using the C profile of libCellML 0.5.0. */

#include "model.h"

#include <math.h>
#include <stdlib.h>

const char VERSION[] = "0.6.0";
const char LIBCELLML_VERSION[] = "0.5.0";

const size_t STATE_COUNT = 33;
const size_t VARIABLE_COUNT = 217;

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

void initialiseVariables(double *states, double *rates, double *variables)
{
    variables[0] = 0.0;
    variables[1] = 0.0;
    variables[4] = 140.0;
    variables[7] = 5.4;
    variables[8] = 140.0;
    variables[10] = 1.8;
    variables[11] = 1.0;
    variables[17] = 96485.3415;
    variables[22] = 14.0;
    variables[23] = 1.4;
    variables[24] = 0.08105;
    variables[25] = 0.0;
    variables[30] = 3.343;
    variables[39] = 26.44;
    variables[40] = 0.0207;
    variables[41] = 0.1369;
    variables[43] = 395.3;
    variables[44] = 2.289;
    variables[45] = 0.4315;
    variables[46] = 26.44;
    variables[47] = 4.663;
    variables[48] = 3.663;
    variables[49] = 0.0;
    variables[51] = 1628.0;
    variables[52] = 561.4;
    variables[54] = 148041085.1;
    variables[57] = 15.0;
    variables[58] = 1.0;
    variables[59] = 0.45;
    variables[60] = 2.5;
    variables[62] = 10000.0;
    variables[64] = 500.0;
    variables[65] = 5.0;
    variables[66] = 660.0;
    variables[70] = 5.0;
    variables[72] = 5.469e-5;
    variables[74] = 0.000286113;
    variables[75] = 5.0e-5;
    variables[77] = 0.04;
    variables[79] = 88800.0;
    variables[80] = 446.0;
    variables[82] = 227700.0;
    variables[83] = 7.51;
    variables[85] = 2277.0;
    variables[86] = 2.5;
    variables[87] = 751.0;
    variables[89] = 1.642e6;
    variables[90] = 542.0;
    variables[93] = 175.4;
    variables[94] = 445.0;
    variables[95] = 0.031;
    variables[96] = 0.062;
    variables[97] = 0.045;
    variables[98] = 10.0;
    variables[104] = 67.0;
    variables[105] = 3.9;
    variables[106] = 0.02;
    variables[107] = 0.0012;
    variables[108] = 0.46;
    variables[109] = 0.0116;
    variables[118] = 5.7e-5;
    variables[119] = 8314.472;
    variables[120] = 310.0;
    variables[122] = 0.0;
    variables[123] = -35.0;
    variables[124] = 0.5;
    variables[125] = 0.5;
    variables[126] = -45.0;
    variables[128] = 0.00427;
    variables[129] = 45.0;
    variables[131] = 0.5927;
    variables[135] = 0.0;
    variables[141] = 0.0;
    variables[144] = 0.0223;
    variables[146] = 0.0;
    variables[150] = 1.0e-5;
    variables[157] = 0.1539e-3;
    variables[163] = 0.4578;
    variables[169] = -16.4508;
    variables[170] = 4.3371;
    variables[177] = 0.0;
    variables[178] = 0.0;
    variables[181] = 0.000338;
    variables[183] = 0.0075;
    variables[184] = 0.04132;
    variables[189] = 0.0;
    variables[190] = 3.5e-3;
    variables[195] = 0.00424;
    variables[204] = 0.00065;
    variables[211] = 1.0;
    variables[212] = 0.00345;
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

void computeComputedConstants(double *variables)
{
    variables[3] = variables[119]*variables[120]/variables[17];
    variables[6] = variables[3]*log(variables[7]/variables[8]);
    variables[20] = (variables[1] > 0.0)?1.2:1.0;
    variables[35] = variables[4]/(variables[47]+variables[4]);
    variables[68] = (variables[1] > 0.0)?-0.25:(variables[0] > 0.0)?0.7*variables[0]/(0.00009+variables[0]):0.0;
    variables[69] = variables[70]*(1.0-variables[68]);
    variables[103] = 0.000000001*3.14159265358979*pow(variables[105], 2.0)*variables[104];
    variables[19] = 0.000000001*2.0*3.14159265358979*variables[106]*(variables[105]-variables[106]/2.0)*variables[104];
    variables[100] = variables[107]*variables[103];
    variables[18] = variables[108]*variables[103]-variables[19];
    variables[99] = variables[109]*variables[103];
    variables[127] = variables[128]/(variables[7]/(variables[7]+variables[129]));
    variables[130] = variables[127]/(variables[131]+1.0);
    variables[132] = variables[131]*variables[130];
    variables[133] = variables[132]*variables[7]/(variables[7]+variables[129]);
    variables[134] = variables[130]*variables[7]/(variables[7]+variables[129]);
    variables[137] = (variables[0] > 0.0)?-1.0-9.898*pow(1.0*variables[0], 0.618)/(pow(1.0*variables[0], 0.618)+0.00122423):0.0;
    variables[138] = (variables[1] > 0.0)?7.5:0.0;
    variables[162] = (variables[1] > 0.0)?1.23:1.0;
    variables[165] = 0.31*variables[0]/(variables[0]+0.00009);
    variables[166] = (variables[1] > 0.0)?-8.0:0.0;
    variables[167] = (variables[1] > 0.0)?-27.0:0.0;
    variables[203] = (variables[1] > 0.0)?1.2*variables[204]:variables[204];
    variables[206] = (variables[1] > 0.0)?-14.0:0.0;
    variables[213] = (3.5988-0.025641)/(1.0+0.0000012155/pow(1.0*variables[0], 1.6951))+0.025641;
}

void computeRates(double voi, double *states, double *rates, double *variables)
{
    variables[5] = states[1];
    variables[142] = variables[3]*log((variables[4]+0.12*variables[7])/(variables[5]+0.12*variables[8]));
    variables[121] = ((voi > variables[124]) && (voi < variables[124]+variables[125]))?variables[123]:variables[126];
    variables[21] = (variables[122] >= 1.0)?variables[121]:states[15];
    variables[143] = variables[144]*pow(states[18], 3.0)*states[17]*(variables[21]-variables[142]);
    variables[145] = variables[146]*pow(states[18], 3.0)*(variables[21]-variables[142]);
    variables[12] = variables[143]+variables[145];
    variables[15] = 0.0000185*variables[163]*(variables[21]-0.0)/(variables[3]*(1.0-exp(-1.0*(variables[21]-0.0)/variables[3])))*(variables[5]-variables[4]*exp(-1.0*(variables[21]-0.0)/variables[3]))*states[23]*states[22]*states[21];
    variables[2] = variables[3]*log(variables[4]/variables[5]);
    variables[16] = states[16]*variables[133]*(variables[21]-variables[2])*(1.0-variables[135]);
    variables[14] = variables[20]*variables[24]*pow(1.0+pow(variables[23]/variables[7], 1.2), -1.0)*pow(1.0+pow(variables[22]/variables[5], 1.3), -1.0)*pow(1.0+exp(-(variables[21]-variables[2]+110.0)/20.0), -1.0);
    variables[50] = 1.0+variables[10]/variables[48]*(1.0+exp(variables[49]*variables[21]/variables[3]))+variables[4]/variables[51]*(1.0+variables[4]/variables[52]*(1.0+variables[4]/variables[47]));
    variables[27] = variables[10]/variables[48]*exp(variables[49]*variables[21]/variables[3])/variables[50];
    variables[42] = 1.0+states[0]/variables[40]*(1.0+exp(-variables[41]*variables[21]/variables[3])+variables[5]/variables[46])+variables[5]/variables[43]*(1.0+variables[5]/variables[44]*(1.0+variables[5]/variables[39]));
    variables[29] = states[0]/variables[40]*exp(-variables[41]*variables[21]/variables[3])/variables[42];
    variables[36] = variables[5]/(variables[39]+variables[5]);
    variables[37] = exp(variables[45]*variables[21]/(2.0*variables[3]));
    variables[33] = exp(-variables[45]*variables[21]/(2.0*variables[3]));
    variables[38] = variables[5]/variables[43]*variables[5]/variables[44]*(1.0+variables[5]/variables[39])*exp(variables[45]*variables[21]/(2.0*variables[3]))/variables[42];
    variables[26] = variables[37]*variables[36]*(variables[38]+variables[29])+variables[33]*variables[29]*(variables[35]+variables[37]);
    variables[34] = variables[4]/variables[51]*variables[4]/variables[52]*(1.0+variables[4]/variables[47])*exp(-variables[45]*variables[21]/(2.0*variables[3]))/variables[50];
    variables[28] = variables[33]*variables[35]*(variables[34]+variables[27])+variables[27]*variables[37]*(variables[36]+variables[33]);
    variables[31] = variables[34]*variables[35]*(variables[38]+variables[29])+variables[38]*variables[27]*(variables[35]+variables[37]);
    variables[32] = variables[38]*variables[36]*(variables[34]+variables[27])+variables[29]*variables[34]*(variables[36]+variables[33]);
    variables[13] = (1.0-variables[25])*variables[30]*(variables[26]*variables[27]-variables[28]*variables[29])/(variables[28]+variables[26]+variables[32]+variables[31]);
    rates[1] = (1.0-variables[11])*-1.0*(variables[12]+variables[16]+variables[15]+3.0*variables[14]+3.0*variables[13])/(1.0*(variables[18]+variables[19])*variables[17]);
    variables[56] = variables[57]-(variables[57]-variables[58])/(1.0+pow(variables[59]/states[2], variables[60]));
    variables[63] = variables[64]*variables[56];
    variables[61] = variables[62]/variables[56];
    rates[4] = variables[65]*states[5]-variables[63]*states[0]*states[4]-(variables[61]*pow(states[0], 2.0)*states[4]-variables[66]*states[3]);
    rates[3] = variables[61]*pow(states[0], 2.0)*states[4]-variables[66]*states[3]-(variables[63]*states[0]*states[3]-variables[65]*states[6]);
    rates[6] = variables[63]*states[0]*states[3]-variables[65]*states[6]-(variables[66]*states[6]-variables[61]*pow(states[0], 2.0)*states[5]);
    rates[5] = variables[66]*states[6]-variables[61]*pow(states[0], 2.0)*states[5]-(variables[65]*states[5]-variables[63]*states[0]*states[4]);
    variables[78] = variables[79]*states[7]*(1.0-states[9])-variables[80]*states[9];
    rates[9] = variables[78];
    variables[81] = variables[82]*states[7]*(1.0-(states[10]+states[11]))-variables[83]*states[10];
    rates[10] = variables[81];
    variables[84] = variables[85]*variables[86]*(1.0-(states[10]+states[11]))-variables[87]*states[11];
    rates[11] = variables[84];
    variables[88] = variables[89]*states[7]*(1.0-states[12])-variables[90]*states[12];
    rates[12] = variables[88];
    variables[91] = variables[89]*states[0]*(1.0-states[13])-variables[90]*states[13];
    rates[13] = variables[91];
    variables[92] = variables[93]*states[2]*(1.0-states[14])-variables[94]*states[14];
    rates[14] = variables[92];
    variables[71] = (states[0]-states[7])/variables[72];
    variables[73] = variables[69]/(1.0+exp((-states[7]+variables[74])/variables[75]));
    rates[7] = 1.0*(variables[71]*variables[19]-variables[73]*variables[99])/variables[18]-(variables[97]*variables[88]+variables[95]*variables[78]+variables[96]*variables[81]);
    variables[53] = variables[54]*states[3]*(states[2]-states[0]);
    variables[101] = 2.0*variables[163]*(variables[21]-0.0)/(variables[3]*(1.0-exp(-1.0*(variables[21]-0.0)*2.0/variables[3])))*(states[0]-variables[10]*exp(-2.0*(variables[21]-0.0)/variables[3]))*states[23]*states[22]*states[21];
    variables[102] = 2.0*variables[184]*variables[21]/(variables[3]*(1.0-exp(-1.0*variables[21]*2.0/variables[3])))*(states[0]-variables[10]*exp(-2.0*variables[21]/variables[3]))*states[25]*states[24];
    rates[0] = variables[53]*variables[100]/variables[19]-((variables[101]+variables[102]-2.0*variables[13])/(2.0*variables[17]*variables[19])+variables[71]+variables[97]*variables[91]);
    variables[76] = (states[8]-states[2])/variables[77];
    rates[8] = variables[73]-variables[76]*variables[100]/variables[99];
    rates[2] = variables[76]-(variables[53]+variables[98]*variables[92]);
    variables[136] = states[16]*variables[134]*(variables[21]-variables[6])*(1.0-variables[135]);
    variables[111] = variables[16]+variables[136];
    variables[112] = variables[157]*states[20]*states[19]*(variables[21]-variables[6]);
    variables[113] = (variables[0] > 0.0)?variables[211]*variables[212]*(variables[21]-variables[6])*(1.0+exp((variables[21]+20.0)/20.0))*states[32]:0.0;
    variables[164] = 0.000365*variables[163]*(variables[21]-0.0)/(variables[3]*(1.0-exp(-1.0*(variables[21]-0.0)/variables[3])))*(variables[8]-variables[7]*exp(-1.0*(variables[21]-0.0)/variables[3]))*states[23]*states[22]*states[21];
    variables[114] = (variables[101]+variables[164]+variables[15])*(1.0-variables[165])*1.0*variables[162];
    variables[115] = variables[190]*(variables[21]-variables[6])*states[27]*states[26];
    variables[205] = variables[3]*log((variables[7]+0.12*variables[4])/(variables[8]+0.12*variables[5]));
    variables[116] = variables[203]*(variables[21]-variables[205])*pow(states[31], 2.0);
    variables[117] = variables[195]*(variables[21]-variables[6])*(0.9*states[29]+0.1*states[30])*states[28];
    variables[110] = variables[111]+variables[117]+variables[116]+variables[115]+variables[14]+variables[13]+variables[12]+variables[114]+variables[102]+variables[113]+variables[112];
    rates[15] = -variables[110]/variables[118];
    variables[140] = (variables[21] < -(80.0-variables[137]-variables[138]-variables[141]))?0.01329+0.99921/(1.0+exp((variables[21]+97.134-variables[137]-variables[138]-variables[141])/8.1752)):0.0002501*exp(-(variables[21]-variables[137]-variables[138]-variables[141])/12.861);
    variables[139] = 1.0/(0.36*(variables[21]+148.8-variables[137]-variables[138])/(exp(0.066*(variables[21]+148.8-variables[137]-variables[138]))-1.0)+0.1*(variables[21]+87.3-variables[137]-variables[138])/(1.0-exp(-0.2*(variables[21]+87.3-variables[137]-variables[138]))))-0.054;
    rates[16] = (variables[140]-states[16])/variables[139];
    variables[147] = 1.0/(1.0+exp(-(variables[21]+42.0504)/8.3106));
    variables[148] = variables[21]+41.0;
    variables[149] = (fabs(variables[148]) < variables[150])?2000.0:200.0*variables[148]/(1.0-exp(-0.1*variables[148]));
    variables[151] = 8000.0*exp(-0.056*(variables[21]+66.0));
    variables[152] = 1.0/(variables[149]+variables[151]);
    rates[18] = (variables[147]-states[18])/variables[152];
    variables[153] = 1.0/(1.0+exp((variables[21]+69.804)/4.4565));
    variables[154] = 20.0*exp(-0.125*(variables[21]+75.0));
    variables[155] = 2000.0/(320.0*exp(-0.1*(variables[21]+75.0))+1.0);
    variables[156] = 1.0/(variables[154]+variables[155]);
    rates[17] = (variables[153]-states[17])/variables[156];
    variables[158] = 1.0/(1.0+exp((variables[21]+6.0)/-8.6));
    variables[159] = 0.009/(1.0+exp((variables[21]+5.0)/12.0))+0.0005;
    rates[20] = (variables[158]-states[20])/variables[159];
    variables[160] = 1.0/(1.0+exp((variables[21]+7.5)/10.0));
    variables[161] = 0.59/(1.0+exp((variables[21]+60.0)/10.0))+3.05;
    rates[19] = (variables[160]-states[19])/variables[161];
    variables[168] = 1.0/(1.0+exp(-(variables[21]-variables[169]-variables[166])/(variables[170]*(1.0+variables[167]/100.0))));
    variables[174] = (variables[21] == -41.8)?-41.80001:(variables[21] == 0.0)?0.0:(variables[21] == -6.8)?-6.80001:variables[21];
    variables[172] = -0.02839*(variables[174]+41.8)/(exp(-(variables[174]+41.8)/2.5)-1.0)-0.0849*(variables[174]+6.8)/(exp(-(variables[174]+6.8)/4.8)-1.0);
    variables[175] = (variables[21] == -1.8)?-1.80001:variables[21];
    variables[173] = 0.01143*(variables[175]+1.8)/(exp((variables[175]+1.8)/2.5)-1.0);
    variables[171] = 0.001/(variables[172]+variables[173]);
    rates[23] = (variables[168]-states[23])/variables[171];
    variables[176] = 1.0/(1.0+exp((variables[21]+37.4+variables[177])/(5.3+variables[178])));
    variables[179] = 0.001*(44.3+230.0*exp(-pow((variables[21]+36.0)/10.0, 2.0)));
    rates[22] = (variables[176]-states[22])/variables[179];
    variables[180] = variables[181]/(variables[181]+states[0]);
    variables[182] = 0.001*variables[180]/variables[183];
    rates[21] = (variables[180]-states[21])/variables[182];
    variables[185] = 1.0/(1.0+exp(-(variables[21]+38.3)/5.5));
    variables[186] = 0.001/(1.068*exp((variables[21]+38.3)/30.0)+1.068*exp(-(variables[21]+38.3)/30.0));
    rates[25] = (variables[185]-states[25])/variables[186];
    variables[187] = 1.0/(1.0+exp((variables[21]+58.7)/3.8));
    variables[188] = 1.0/(16.67*exp(-(variables[21]+75.0)/83.3)+16.67*exp((variables[21]+75.0)/15.38))+variables[189];
    rates[24] = (variables[187]-states[24])/variables[188];
    variables[191] = 1.0/(1.0+exp((variables[21]+49.0)/13.0));
    variables[192] = 0.001*0.6*(65.17/(0.57*exp(-0.08*(variables[21]+44.0))+0.065*exp(0.1*(variables[21]+45.93)))+10.1);
    rates[27] = (variables[191]-states[27])/variables[192];
    variables[193] = 1.0/(1.0+exp(-(variables[21]-19.3)/15.0));
    variables[194] = 0.001*0.66*1.4*(15.59/(1.037*exp(0.09*(variables[21]+30.61))+0.369*exp(-0.12*(variables[21]+23.84)))+2.98);
    rates[26] = (variables[193]-states[26])/variables[194];
    variables[198] = 1.0/(1.0+exp(-(variables[21]+10.0144)/7.6607));
    variables[199] = 0.84655354/(4.2*exp(variables[21]/17.0)+0.15*exp(-variables[21]/21.6));
    rates[30] = (variables[198]-states[30])/variables[199];
    variables[200] = 1.0/(30.0*exp(variables[21]/10.0)+exp(-variables[21]/12.0));
    rates[29] = (variables[198]-states[29])/variables[200];
    variables[202] = 1.0/(1.0+exp((variables[21]+28.6)/17.1));
    variables[201] = 1.0/(100.0*exp(-variables[21]/54.645)+656.0*exp(variables[21]/106.157));
    rates[28] = (variables[202]-states[28])/variables[201];
    variables[207] = sqrt(1.0/(1.0+exp(-(variables[21]+0.6383-variables[206])/10.7071)));
    variables[209] = 28.0/(1.0+exp(-(variables[21]-40.0-variables[206])/3.0));
    variables[210] = 1.0*exp(-(variables[21]-variables[206]-5.0)/25.0);
    variables[208] = 1.0/(variables[209]+variables[210]);
    rates[31] = (variables[207]-states[31])/variables[208];
    variables[214] = 10.0*exp(0.0133*(variables[21]+40.0));
    variables[215] = variables[213]/(variables[213]+variables[214]);
    variables[216] = 1.0/(variables[213]+variables[214]);
    rates[32] = (variables[215]-states[32])/variables[216];
}

void computeVariables(double voi, double *states, double *rates, double *variables)
{
    variables[5] = states[1];
    variables[2] = variables[3]*log(variables[4]/variables[5]);
    variables[9] = 0.5*variables[3]*log(variables[10]/states[0]);
    variables[21] = (variables[122] >= 1.0)?variables[121]:states[15];
    variables[14] = variables[20]*variables[24]*pow(1.0+pow(variables[23]/variables[7], 1.2), -1.0)*pow(1.0+pow(variables[22]/variables[5], 1.3), -1.0)*pow(1.0+exp(-(variables[21]-variables[2]+110.0)/20.0), -1.0);
    variables[50] = 1.0+variables[10]/variables[48]*(1.0+exp(variables[49]*variables[21]/variables[3]))+variables[4]/variables[51]*(1.0+variables[4]/variables[52]*(1.0+variables[4]/variables[47]));
    variables[27] = variables[10]/variables[48]*exp(variables[49]*variables[21]/variables[3])/variables[50];
    variables[42] = 1.0+states[0]/variables[40]*(1.0+exp(-variables[41]*variables[21]/variables[3])+variables[5]/variables[46])+variables[5]/variables[43]*(1.0+variables[5]/variables[44]*(1.0+variables[5]/variables[39]));
    variables[29] = states[0]/variables[40]*exp(-variables[41]*variables[21]/variables[3])/variables[42];
    variables[36] = variables[5]/(variables[39]+variables[5]);
    variables[37] = exp(variables[45]*variables[21]/(2.0*variables[3]));
    variables[33] = exp(-variables[45]*variables[21]/(2.0*variables[3]));
    variables[38] = variables[5]/variables[43]*variables[5]/variables[44]*(1.0+variables[5]/variables[39])*exp(variables[45]*variables[21]/(2.0*variables[3]))/variables[42];
    variables[26] = variables[37]*variables[36]*(variables[38]+variables[29])+variables[33]*variables[29]*(variables[35]+variables[37]);
    variables[34] = variables[4]/variables[51]*variables[4]/variables[52]*(1.0+variables[4]/variables[47])*exp(-variables[45]*variables[21]/(2.0*variables[3]))/variables[50];
    variables[28] = variables[33]*variables[35]*(variables[34]+variables[27])+variables[27]*variables[37]*(variables[36]+variables[33]);
    variables[31] = variables[34]*variables[35]*(variables[38]+variables[29])+variables[38]*variables[27]*(variables[35]+variables[37]);
    variables[32] = variables[38]*variables[36]*(variables[34]+variables[27])+variables[29]*variables[34]*(variables[36]+variables[33]);
    variables[13] = (1.0-variables[25])*variables[30]*(variables[26]*variables[27]-variables[28]*variables[29])/(variables[28]+variables[26]+variables[32]+variables[31]);
    variables[53] = variables[54]*states[3]*(states[2]-states[0]);
    variables[55] = states[2]-states[0];
    variables[56] = variables[57]-(variables[57]-variables[58])/(1.0+pow(variables[59]/states[2], variables[60]));
    variables[61] = variables[62]/variables[56];
    variables[63] = variables[64]*variables[56];
    variables[67] = states[4]+states[3]+states[6]+states[5];
    variables[71] = (states[0]-states[7])/variables[72];
    variables[73] = variables[69]/(1.0+exp((-states[7]+variables[74])/variables[75]));
    variables[76] = (states[8]-states[2])/variables[77];
    variables[78] = variables[79]*states[7]*(1.0-states[9])-variables[80]*states[9];
    variables[81] = variables[82]*states[7]*(1.0-(states[10]+states[11]))-variables[83]*states[10];
    variables[84] = variables[85]*variables[86]*(1.0-(states[10]+states[11]))-variables[87]*states[11];
    variables[88] = variables[89]*states[7]*(1.0-states[12])-variables[90]*states[12];
    variables[91] = variables[89]*states[0]*(1.0-states[13])-variables[90]*states[13];
    variables[92] = variables[93]*states[2]*(1.0-states[14])-variables[94]*states[14];
    variables[16] = states[16]*variables[133]*(variables[21]-variables[2])*(1.0-variables[135]);
    variables[136] = states[16]*variables[134]*(variables[21]-variables[6])*(1.0-variables[135]);
    variables[111] = variables[16]+variables[136];
    variables[112] = variables[157]*states[20]*states[19]*(variables[21]-variables[6]);
    variables[113] = (variables[0] > 0.0)?variables[211]*variables[212]*(variables[21]-variables[6])*(1.0+exp((variables[21]+20.0)/20.0))*states[32]:0.0;
    variables[102] = 2.0*variables[184]*variables[21]/(variables[3]*(1.0-exp(-1.0*variables[21]*2.0/variables[3])))*(states[0]-variables[10]*exp(-2.0*variables[21]/variables[3]))*states[25]*states[24];
    variables[101] = 2.0*variables[163]*(variables[21]-0.0)/(variables[3]*(1.0-exp(-1.0*(variables[21]-0.0)*2.0/variables[3])))*(states[0]-variables[10]*exp(-2.0*(variables[21]-0.0)/variables[3]))*states[23]*states[22]*states[21];
    variables[15] = 0.0000185*variables[163]*(variables[21]-0.0)/(variables[3]*(1.0-exp(-1.0*(variables[21]-0.0)/variables[3])))*(variables[5]-variables[4]*exp(-1.0*(variables[21]-0.0)/variables[3]))*states[23]*states[22]*states[21];
    variables[164] = 0.000365*variables[163]*(variables[21]-0.0)/(variables[3]*(1.0-exp(-1.0*(variables[21]-0.0)/variables[3])))*(variables[8]-variables[7]*exp(-1.0*(variables[21]-0.0)/variables[3]))*states[23]*states[22]*states[21];
    variables[114] = (variables[101]+variables[164]+variables[15])*(1.0-variables[165])*1.0*variables[162];
    variables[142] = variables[3]*log((variables[4]+0.12*variables[7])/(variables[5]+0.12*variables[8]));
    variables[143] = variables[144]*pow(states[18], 3.0)*states[17]*(variables[21]-variables[142]);
    variables[145] = variables[146]*pow(states[18], 3.0)*(variables[21]-variables[142]);
    variables[12] = variables[143]+variables[145];
    variables[115] = variables[190]*(variables[21]-variables[6])*states[27]*states[26];
    variables[205] = variables[3]*log((variables[7]+0.12*variables[4])/(variables[8]+0.12*variables[5]));
    variables[116] = variables[203]*(variables[21]-variables[205])*pow(states[31], 2.0);
    variables[117] = variables[195]*(variables[21]-variables[6])*(0.9*states[29]+0.1*states[30])*states[28];
    variables[110] = variables[111]+variables[117]+variables[116]+variables[115]+variables[14]+variables[13]+variables[12]+variables[114]+variables[102]+variables[113]+variables[112];
    variables[139] = 1.0/(0.36*(variables[21]+148.8-variables[137]-variables[138])/(exp(0.066*(variables[21]+148.8-variables[137]-variables[138]))-1.0)+0.1*(variables[21]+87.3-variables[137]-variables[138])/(1.0-exp(-0.2*(variables[21]+87.3-variables[137]-variables[138]))))-0.054;
    variables[140] = (variables[21] < -(80.0-variables[137]-variables[138]-variables[141]))?0.01329+0.99921/(1.0+exp((variables[21]+97.134-variables[137]-variables[138]-variables[141])/8.1752)):0.0002501*exp(-(variables[21]-variables[137]-variables[138]-variables[141])/12.861);
    variables[147] = 1.0/(1.0+exp(-(variables[21]+42.0504)/8.3106));
    variables[148] = variables[21]+41.0;
    variables[149] = (fabs(variables[148]) < variables[150])?2000.0:200.0*variables[148]/(1.0-exp(-0.1*variables[148]));
    variables[151] = 8000.0*exp(-0.056*(variables[21]+66.0));
    variables[152] = 1.0/(variables[149]+variables[151]);
    variables[153] = 1.0/(1.0+exp((variables[21]+69.804)/4.4565));
    variables[154] = 20.0*exp(-0.125*(variables[21]+75.0));
    variables[155] = 2000.0/(320.0*exp(-0.1*(variables[21]+75.0))+1.0);
    variables[156] = 1.0/(variables[154]+variables[155]);
    variables[158] = 1.0/(1.0+exp((variables[21]+6.0)/-8.6));
    variables[159] = 0.009/(1.0+exp((variables[21]+5.0)/12.0))+0.0005;
    variables[160] = 1.0/(1.0+exp((variables[21]+7.5)/10.0));
    variables[161] = 0.59/(1.0+exp((variables[21]+60.0)/10.0))+3.05;
    variables[168] = 1.0/(1.0+exp(-(variables[21]-variables[169]-variables[166])/(variables[170]*(1.0+variables[167]/100.0))));
    variables[174] = (variables[21] == -41.8)?-41.80001:(variables[21] == 0.0)?0.0:(variables[21] == -6.8)?-6.80001:variables[21];
    variables[172] = -0.02839*(variables[174]+41.8)/(exp(-(variables[174]+41.8)/2.5)-1.0)-0.0849*(variables[174]+6.8)/(exp(-(variables[174]+6.8)/4.8)-1.0);
    variables[175] = (variables[21] == -1.8)?-1.80001:variables[21];
    variables[173] = 0.01143*(variables[175]+1.8)/(exp((variables[175]+1.8)/2.5)-1.0);
    variables[171] = 0.001/(variables[172]+variables[173]);
    variables[176] = 1.0/(1.0+exp((variables[21]+37.4+variables[177])/(5.3+variables[178])));
    variables[179] = 0.001*(44.3+230.0*exp(-pow((variables[21]+36.0)/10.0, 2.0)));
    variables[180] = variables[181]/(variables[181]+states[0]);
    variables[182] = 0.001*variables[180]/variables[183];
    variables[185] = 1.0/(1.0+exp(-(variables[21]+38.3)/5.5));
    variables[186] = 0.001/(1.068*exp((variables[21]+38.3)/30.0)+1.068*exp(-(variables[21]+38.3)/30.0));
    variables[187] = 1.0/(1.0+exp((variables[21]+58.7)/3.8));
    variables[188] = 1.0/(16.67*exp(-(variables[21]+75.0)/83.3)+16.67*exp((variables[21]+75.0)/15.38))+variables[189];
    variables[191] = 1.0/(1.0+exp((variables[21]+49.0)/13.0));
    variables[192] = 0.001*0.6*(65.17/(0.57*exp(-0.08*(variables[21]+44.0))+0.065*exp(0.1*(variables[21]+45.93)))+10.1);
    variables[193] = 1.0/(1.0+exp(-(variables[21]-19.3)/15.0));
    variables[194] = 0.001*0.66*1.4*(15.59/(1.037*exp(0.09*(variables[21]+30.61))+0.369*exp(-0.12*(variables[21]+23.84)))+2.98);
    variables[196] = 1.0/(1.0+exp(-(variables[21]+23.2)/6.6))/(0.84655354/(37.2*exp(variables[21]/11.9)+0.96*exp(-variables[21]/18.5)));
    variables[197] = 4.0*((37.2*exp(variables[21]/15.9)+0.96*exp(-variables[21]/22.5))/0.84655354-1.0/(1.0+exp(-(variables[21]+23.2)/10.6))/(0.84655354/(37.2*exp(variables[21]/15.9)+0.96*exp(-variables[21]/22.5))));
    variables[198] = 1.0/(1.0+exp(-(variables[21]+10.0144)/7.6607));
    variables[199] = 0.84655354/(4.2*exp(variables[21]/17.0)+0.15*exp(-variables[21]/21.6));
    variables[200] = 1.0/(30.0*exp(variables[21]/10.0)+exp(-variables[21]/12.0));
    variables[201] = 1.0/(100.0*exp(-variables[21]/54.645)+656.0*exp(variables[21]/106.157));
    variables[202] = 1.0/(1.0+exp((variables[21]+28.6)/17.1));
    variables[207] = sqrt(1.0/(1.0+exp(-(variables[21]+0.6383-variables[206])/10.7071)));
    variables[209] = 28.0/(1.0+exp(-(variables[21]-40.0-variables[206])/3.0));
    variables[210] = 1.0*exp(-(variables[21]-variables[206]-5.0)/25.0);
    variables[208] = 1.0/(variables[209]+variables[210]);
    variables[214] = 10.0*exp(0.0133*(variables[21]+40.0));
    variables[215] = variables[213]/(variables[213]+variables[214]);
    variables[216] = 1.0/(variables[213]+variables[214]);
}

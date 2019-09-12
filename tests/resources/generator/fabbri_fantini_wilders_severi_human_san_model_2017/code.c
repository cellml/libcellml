/* The content of this file was generated using the C profile of libCellML 0.2.0. */

#include <math.h>
#include <stddef.h>
#include <stdlib.h>

const char LIBCELLML_VERSION[] = "0.2.0";

const size_t STATE_COUNT = 33;
const size_t VARIABLE_COUNT = 217;

struct VariableInfo {
    char name[15];
    char units[26];
    char component[28];
};

const struct VariableInfo VOI_INFO = {"time", "second", "Nai_concentration"};

const struct VariableInfo STATE_INFO[] = {
    {"R", "dimensionless", "Ca_SR_release"},
    {"O", "dimensionless", "Ca_SR_release"},
    {"I", "dimensionless", "Ca_SR_release"},
    {"RI", "dimensionless", "Ca_SR_release"},
    {"Ca_jsr", "millimolar", "Ca_dynamics"},
    {"fCa", "dimensionless", "i_CaL_fCa_gate"},
    {"fTC", "dimensionless", "Ca_buffering"},
    {"fTMC", "dimensionless", "Ca_buffering"},
    {"fTMM", "dimensionless", "Ca_buffering"},
    {"fCMi", "dimensionless", "Ca_buffering"},
    {"fCMs", "dimensionless", "Ca_buffering"},
    {"fCQ", "dimensionless", "Ca_buffering"},
    {"Cai", "millimolar", "Ca_dynamics"},
    {"Ca_nsr", "millimolar", "Ca_dynamics"},
    {"y", "dimensionless", "i_f_y_gate"},
    {"m", "dimensionless", "i_Na_m_gate"},
    {"h", "dimensionless", "i_Na_h_gate"},
    {"fL", "dimensionless", "i_CaL_fL_gate"},
    {"dT", "dimensionless", "i_CaT_dT_gate"},
    {"fT", "dimensionless", "i_CaT_fT_gate"},
    {"q", "dimensionless", "i_to_q_gate"},
    {"r", "dimensionless", "i_to_r_gate"},
    {"paS", "dimensionless", "i_Kr_pa_gate"},
    {"paF", "dimensionless", "i_Kr_pa_gate"},
    {"piy", "dimensionless", "i_Kr_pi_gate"},
    {"a", "dimensionless", "i_KACh_a_gate"},
    {"r_Kur", "dimensionless", "i_Kur_rKur_gate"},
    {"s_Kur", "dimensionless", "i_Kur_sKur_gate"},
    {"n", "dimensionless", "i_Ks_n_gate"},
    {"dL", "dimensionless", "i_CaL_dL_gate"},
    {"Ca_sub", "millimolar", "Ca_dynamics"},
    {"V_ode", "millivolt", "Membrane"},
    {"Nai_", "millimolar", "Nai_concentration"}
};

const struct VariableInfo VARIABLE_INFO[] = {
    {"EC50_SR", "millimolar", "Ca_SR_release"},
    {"HSR", "dimensionless", "Ca_SR_release"},
    {"MaxSR", "dimensionless", "Ca_SR_release"},
    {"MinSR", "dimensionless", "Ca_SR_release"},
    {"kiCa", "per_millimolar_second", "Ca_SR_release"},
    {"kim", "per_second", "Ca_SR_release"},
    {"koCa", "per_millimolar2_second", "Ca_SR_release"},
    {"kom", "per_second", "Ca_SR_release"},
    {"ks", "per_second", "Ca_SR_release"},
    {"CM_tot", "millimolar", "Ca_buffering"},
    {"CQ_tot", "millimolar", "Ca_buffering"},
    {"Mgi", "millimolar", "Ca_buffering"},
    {"TC_tot", "millimolar", "Ca_buffering"},
    {"TMC_tot", "millimolar", "Ca_buffering"},
    {"kb_CM", "per_second", "Ca_buffering"},
    {"kb_CQ", "per_second", "Ca_buffering"},
    {"kb_TC", "per_second", "Ca_buffering"},
    {"kb_TMC", "per_second", "Ca_buffering"},
    {"kb_TMM", "per_second", "Ca_buffering"},
    {"kf_CM", "per_millimolar_second", "Ca_buffering"},
    {"kf_CQ", "per_millimolar_second", "Ca_buffering"},
    {"kf_TC", "per_millimolar_second", "Ca_buffering"},
    {"kf_TMC", "per_millimolar_second", "Ca_buffering"},
    {"kf_TMM", "per_millimolar_second", "Ca_buffering"},
    {"K_up", "millimolar", "Ca_intracellular_fluxes"},
    {"P_up_basal", "millimolar_per_second", "Ca_intracellular_fluxes"},
    {"slope_up", "millimolar", "Ca_intracellular_fluxes"},
    {"tau_dif_Ca", "second", "Ca_intracellular_fluxes"},
    {"tau_tr", "second", "Ca_intracellular_fluxes"},
    {"L_cell", "micrometre", "Cell_parameters"},
    {"L_sub", "micrometre", "Cell_parameters"},
    {"R_cell", "micrometre", "Cell_parameters"},
    {"V_i_part", "dimensionless", "Cell_parameters"},
    {"V_jsr_part", "dimensionless", "Cell_parameters"},
    {"V_nsr_part", "dimensionless", "Cell_parameters"},
    {"Cao", "millimolar", "Ionic_values"},
    {"Ki", "millimolar", "Ionic_values"},
    {"Ko", "millimolar", "Ionic_values"},
    {"Nao", "millimolar", "Ionic_values"},
    {"C", "microF", "Membrane"},
    {"F", "coulomb_per_mole", "Membrane"},
    {"R", "joule_per_kilomole_kelvin", "Membrane"},
    {"T", "kelvin", "Membrane"},
    {"clamp_mode", "dimensionless", "Membrane"},
    {"Nai_clamp", "dimensionless", "Nai_concentration"},
    {"ACh", "millimolar", "Rate_modulation_experiments"},
    {"Iso_1_uM", "dimensionless", "Rate_modulation_experiments"},
    {"V_holding", "millivolt", "Voltage_clamp"},
    {"V_test", "millivolt", "Voltage_clamp"},
    {"t_holding", "second", "Voltage_clamp"},
    {"t_test", "second", "Voltage_clamp"},
    {"P_CaL", "nanoA_per_millimolar", "i_CaL"},
    {"V_dL", "millivolt", "i_CaL_dL_gate"},
    {"k_dL", "millivolt", "i_CaL_dL_gate"},
    {"Km_fCa", "millimolar", "i_CaL_fCa_gate"},
    {"alpha_fCa", "per_second", "i_CaL_fCa_gate"},
    {"k_fL", "millivolt", "i_CaL_fL_gate"},
    {"shift_fL", "millivolt", "i_CaL_fL_gate"},
    {"P_CaT", "nanoA_per_millimolar", "i_CaT"},
    {"offset_fT", "second", "i_CaT_fT_gate"},
    {"ACh_on", "dimensionless", "i_KACh"},
    {"g_KACh", "microS", "i_KACh"},
    {"g_Kr", "microS", "i_Kr"},
    {"g_Ks_", "microS", "i_Ks"},
    {"g_Kur", "microS", "i_Kur"},
    {"g_Na", "microS", "i_Na"},
    {"g_Na_L", "microS", "i_Na"},
    {"K1ni", "millimolar", "i_NaCa"},
    {"K1no", "millimolar", "i_NaCa"},
    {"K2ni", "millimolar", "i_NaCa"},
    {"K2no", "millimolar", "i_NaCa"},
    {"K3ni", "millimolar", "i_NaCa"},
    {"K3no", "millimolar", "i_NaCa"},
    {"K_NaCa", "nanoA", "i_NaCa"},
    {"Kci", "millimolar", "i_NaCa"},
    {"Kcni", "millimolar", "i_NaCa"},
    {"Kco", "millimolar", "i_NaCa"},
    {"Qci", "dimensionless", "i_NaCa"},
    {"Qco", "dimensionless", "i_NaCa"},
    {"Qn", "dimensionless", "i_NaCa"},
    {"blockade_NaCa", "dimensionless", "i_NaCa"},
    {"Km_Kp", "millimolar", "i_NaK"},
    {"Km_Nap", "millimolar", "i_NaK"},
    {"i_NaK_max", "nanoA", "i_NaK"},
    {"delta_m", "millivolt", "i_Na_m_gate"},
    {"Km_f", "millimolar", "i_f"},
    {"alpha", "dimensionless", "i_f"},
    {"blockade", "dimensionless", "i_f"},
    {"g_f", "microS", "i_f"},
    {"y_shift", "millivolt", "i_f_y_gate"},
    {"g_to", "microS", "i_to"},
    {"Iso_increase", "dimensionless", "i_NaK"},
    {"k34", "dimensionless", "i_NaCa"},
    {"b_up", "dimensionless", "Ca_intracellular_fluxes"},
    {"P_up", "millimolar_per_second", "Ca_intracellular_fluxes"},
    {"V_cell", "millimetre3", "Cell_parameters"},
    {"V_sub", "millimetre3", "Nai_concentration"},
    {"V_jsr", "millimetre3", "Ca_dynamics"},
    {"V_i", "millimetre3", "Nai_concentration"},
    {"V_nsr", "millimetre3", "Ca_dynamics"},
    {"RTONF", "millivolt", "Ionic_values"},
    {"G_f", "microS", "i_f"},
    {"G_f_K", "microS", "i_f"},
    {"G_f_Na", "microS", "i_f"},
    {"g_f_Na", "microS", "i_f"},
    {"g_f_K", "microS", "i_f"},
    {"ACh_shift", "millivolt", "i_f_y_gate"},
    {"Iso_shift", "millivolt", "i_f_y_gate"},
    {"Iso_increase", "dimensionless", "i_CaL"},
    {"ACh_block", "dimensionless", "i_CaL"},
    {"Iso_shift_dL", "millivolt", "i_CaL_dL_gate"},
    {"Iso_slope_dL", "dimensionless", "i_CaL_dL_gate"},
    {"g_Ks", "microS", "i_Ks"},
    {"Iso_shift", "millivolt", "i_Ks_n_gate"},
    {"alpha_a", "per_second", "i_KACh_a_gate"},
    {"E_K", "millivolt", "Ionic_values"},
    {"Nai", "millimolar", "Ionic_values"},
    {"k43", "dimensionless", "i_NaCa"},
    {"j_SRCarel", "millimolar_per_second", "Ca_SR_release"},
    {"diff", "millimolar", "Ca_SR_release"},
    {"kCaSR", "dimensionless", "Ca_SR_release"},
    {"koSRCa", "per_millimolar2_second", "Ca_SR_release"},
    {"kiSRCa", "per_millimolar_second", "Ca_SR_release"},
    {"P_tot", "dimensionless", "Ca_SR_release"},
    {"j_Ca_dif", "millimolar_per_second", "Ca_intracellular_fluxes"},
    {"j_up", "millimolar_per_second", "Ca_intracellular_fluxes"},
    {"j_tr", "millimolar_per_second", "Ca_intracellular_fluxes"},
    {"delta_fTC", "per_second", "Ca_buffering"},
    {"delta_fTMC", "per_second", "Ca_buffering"},
    {"delta_fTMM", "per_second", "Ca_buffering"},
    {"delta_fCMi", "per_second", "Ca_buffering"},
    {"delta_fCMs", "per_second", "Ca_buffering"},
    {"delta_fCQ", "per_second", "Ca_buffering"},
    {"V_clamp", "millivolt", "Membrane"},
    {"E_mh", "millivolt", "i_Na"},
    {"fCa_infinity", "dimensionless", "i_CaL_fCa_gate"},
    {"tau_fCa", "second", "i_CaL_fCa_gate"},
    {"E_Ks", "millivolt", "i_Ks"},
    {"E_Na", "millivolt", "Ionic_values"},
    {"E_Ca", "millivolt", "Ionic_values"},
    {"V", "millivolt", "i_NaK"},
    {"i_fNa", "nanoA", "Nai_concentration"},
    {"i_fK", "nanoA", "i_f"},
    {"i_f", "nanoA", "Membrane"},
    {"tau_y", "second", "i_f_y_gate"},
    {"y_infinity", "dimensionless", "i_f_y_gate"},
    {"i_Na_", "nanoA", "i_Na"},
    {"i_Na_L", "nanoA", "i_Na"},
    {"i_Na", "nanoA", "Nai_concentration"},
    {"m_infinity", "dimensionless", "i_Na_m_gate"},
    {"E0_m", "millivolt", "i_Na_m_gate"},
    {"alpha_m", "per_second", "i_Na_m_gate"},
    {"beta_m", "per_second", "i_Na_m_gate"},
    {"tau_m", "second", "i_Na_m_gate"},
    {"h_infinity", "dimensionless", "i_Na_h_gate"},
    {"alpha_h", "per_second", "i_Na_h_gate"},
    {"beta_h", "per_second", "i_Na_h_gate"},
    {"tau_h", "second", "i_Na_h_gate"},
    {"i_Kur", "nanoA", "Membrane"},
    {"r_Kur_infinity", "dimensionless", "i_Kur_rKur_gate"},
    {"tau_r_Kur", "second", "i_Kur_rKur_gate"},
    {"s_Kur_infinity", "dimensionless", "i_Kur_sKur_gate"},
    {"tau_s_Kur", "second", "i_Kur_sKur_gate"},
    {"i_siCa", "nanoA", "Ca_dynamics"},
    {"i_siK", "nanoA", "i_CaL"},
    {"i_siNa", "nanoA", "Nai_concentration"},
    {"i_CaL", "nanoA", "Membrane"},
    {"dL_infinity", "dimensionless", "i_CaL_dL_gate"},
    {"adVm", "millivolt", "i_CaL_dL_gate"},
    {"bdVm", "millivolt", "i_CaL_dL_gate"},
    {"fL_infinity", "dimensionless", "i_CaL_fL_gate"},
    {"tau_fL", "second", "i_CaL_fL_gate"},
    {"i_CaT", "nanoA", "Ca_dynamics"},
    {"dT_infinity", "dimensionless", "i_CaT_dT_gate"},
    {"tau_dT", "second", "i_CaT_dT_gate"},
    {"fT_infinity", "dimensionless", "i_CaT_fT_gate"},
    {"tau_fT", "second", "i_CaT_fT_gate"},
    {"i_to", "nanoA", "Membrane"},
    {"q_infinity", "dimensionless", "i_to_q_gate"},
    {"tau_q", "second", "i_to_q_gate"},
    {"r_infinity", "dimensionless", "i_to_r_gate"},
    {"tau_r", "second", "i_to_r_gate"},
    {"i_Kr", "nanoA", "Membrane"},
    {"alfapaF", "per_second", "i_Kr_pa_gate"},
    {"betapaF", "per_second", "i_Kr_pa_gate"},
    {"pa_infinity", "dimensionless", "i_Kr_pa_gate"},
    {"tau_paS", "second", "i_Kr_pa_gate"},
    {"tau_paF", "second", "i_Kr_pa_gate"},
    {"tau_pi", "second", "i_Kr_pi_gate"},
    {"pi_infinity", "dimensionless", "i_Kr_pi_gate"},
    {"i_Ks", "nanoA", "Membrane"},
    {"n_infinity", "dimensionless", "i_Ks_n_gate"},
    {"alpha_n", "per_second", "i_Ks_n_gate"},
    {"beta_n", "per_second", "i_Ks_n_gate"},
    {"i_KACh", "nanoA", "Membrane"},
    {"beta_a", "per_second", "i_KACh_a_gate"},
    {"a_infinity", "dimensionless", "i_KACh_a_gate"},
    {"tau_a", "second", "i_KACh_a_gate"},
    {"i_NaK", "nanoA", "Nai_concentration"},
    {"k41", "dimensionless", "i_NaCa"},
    {"di", "dimensionless", "i_NaCa"},
    {"k32", "dimensionless", "i_NaCa"},
    {"do", "dimensionless", "i_NaCa"},
    {"alpha_dL", "per_second", "i_CaL_dL_gate"},
    {"beta_dL", "per_second", "i_CaL_dL_gate"},
    {"tau_n", "second", "i_Ks_n_gate"},
    {"k12", "dimensionless", "i_NaCa"},
    {"k14", "dimensionless", "i_NaCa"},
    {"k21", "dimensionless", "i_NaCa"},
    {"k23", "dimensionless", "i_NaCa"},
    {"tau_dL", "second", "i_CaL_dL_gate"},
    {"x1", "dimensionless", "i_NaCa"},
    {"x2", "dimensionless", "i_NaCa"},
    {"x3", "dimensionless", "i_NaCa"},
    {"x4", "dimensionless", "i_NaCa"},
    {"i_NaCa", "nanoA", "Nai_concentration"},
    {"i_tot", "nanoA", "Membrane"}
};

double * createStatesArray()
{
    return (double *) malloc(33 * sizeof(double));
}

double * createVariablesArray()
{
    return (double *) malloc(217 * sizeof(double));
}

void deleteArray(double *array)
{
    free(array);
}

void initializeConstants(double *states, double *variables)
{
    states[0] = 0.9308;
    states[1] = 6.181512e-9;
    states[2] = 4.595622e-10;
    states[3] = 0.069199;
    states[4] = 0.409551;
    states[5] = 0.844449;
    states[6] = 0.017929;
    states[7] = 0.259947;
    states[8] = 0.653777;
    states[9] = 0.217311;
    states[10] = 0.158521;
    states[11] = 0.138975;
    states[12] = 9.15641e-6;
    states[13] = 0.435148;
    states[14] = 0.009508;
    states[15] = 0.447724;
    states[16] = 0.003058;
    states[17] = 0.846702;
    states[18] = 0.268909;
    states[19] = 0.020484;
    states[20] = 0.430836;
    states[21] = 0.014523;
    states[22] = 0.283185;
    states[23] = 0.011068;
    states[24] = 0.709051;
    states[25] = 0.00277;
    states[26] = 0.011845;
    states[27] = 0.845304;
    states[28] = 0.1162;
    states[29] = 0.001921;
    states[30] = 6.226104e-5;
    states[31] = -47.787168;
    states[32] = 5.0;
    variables[0] = 0.45;
    variables[1] = 2.5;
    variables[2] = 15.0;
    variables[3] = 1.0;
    variables[4] = 500.0;
    variables[5] = 5.0;
    variables[6] = 10000.0;
    variables[7] = 660.0;
    variables[8] = 148041085.1;
    variables[9] = 0.045;
    variables[10] = 10.0;
    variables[11] = 2.5;
    variables[12] = 0.031;
    variables[13] = 0.062;
    variables[14] = 542.0;
    variables[15] = 445.0;
    variables[16] = 446.0;
    variables[17] = 7.51;
    variables[18] = 751.0;
    variables[19] = 1.642e6;
    variables[20] = 175.4;
    variables[21] = 88800.0;
    variables[22] = 227700.0;
    variables[23] = 2277.0;
    variables[24] = 0.000286113;
    variables[25] = 5.0;
    variables[26] = 5.0e-5;
    variables[27] = 5.469e-5;
    variables[28] = 0.04;
    variables[29] = 67.0;
    variables[30] = 0.02;
    variables[31] = 3.9;
    variables[32] = 0.46;
    variables[33] = 0.0012;
    variables[34] = 0.0116;
    variables[35] = 1.8;
    variables[36] = 140.0;
    variables[37] = 5.4;
    variables[38] = 140.0;
    variables[39] = 5.7e-5;
    variables[40] = 96485.3415;
    variables[41] = 8314.472;
    variables[42] = 310.0;
    variables[43] = 0.0;
    variables[44] = 1.0;
    variables[45] = 0.0;
    variables[46] = 0.0;
    variables[47] = -45.0;
    variables[48] = -35.0;
    variables[49] = 0.5;
    variables[50] = 0.5;
    variables[51] = 0.4578;
    variables[52] = -16.4508;
    variables[53] = 4.3371;
    variables[54] = 0.000338;
    variables[55] = 0.0075;
    variables[56] = 0.0;
    variables[57] = 0.0;
    variables[58] = 0.04132;
    variables[59] = 0.0;
    variables[60] = 1.0;
    variables[61] = 0.00345;
    variables[62] = 0.00424;
    variables[63] = 0.00065;
    variables[64] = 0.1539e-3;
    variables[65] = 0.0223;
    variables[66] = 0.0;
    variables[67] = 395.3;
    variables[68] = 1628.0;
    variables[69] = 2.289;
    variables[70] = 561.4;
    variables[71] = 26.44;
    variables[72] = 4.663;
    variables[73] = 3.343;
    variables[74] = 0.0207;
    variables[75] = 26.44;
    variables[76] = 3.663;
    variables[77] = 0.1369;
    variables[78] = 0.0;
    variables[79] = 0.4315;
    variables[80] = 0.0;
    variables[81] = 1.4;
    variables[82] = 14.0;
    variables[83] = 0.08105;
    variables[84] = 1.0e-5;
    variables[85] = 45.0;
    variables[86] = 0.5927;
    variables[87] = 0.0;
    variables[88] = 0.00427;
    variables[89] = 0.0;
    variables[90] = 3.5e-3;
}

void computeComputedConstants(double *variables)
{
    variables[92] = (variables[46] > 0.0)?1.2:1.0;
    variables[94] = variables[38]/(variables[72]+variables[38]);
    variables[101] = (variables[46] > 0.0)?-0.25:(variables[45] > 0.0)?0.7*variables[45]/(0.00009+variables[45]):0.0;
    variables[102] = variables[25]*(1.0-variables[101]);
    variables[112] = 0.000000001*3.14159265358979*pow(variables[31], 2.0)*variables[29];
    variables[113] = 0.000000001*2.0*3.14159265358979*variables[30]*(variables[31]-variables[30]/2.0)*variables[29];
    variables[114] = variables[33]*variables[112];
    variables[115] = variables[32]*variables[112]-variables[113];
    variables[116] = variables[34]*variables[112];
    variables[117] = variables[41]*variables[42]/variables[40];
    variables[119] = variables[88]/(variables[37]/(variables[37]+variables[85]));
    variables[120] = variables[119]/(variables[86]+1.0);
    variables[121] = variables[86]*variables[120];
    variables[122] = variables[121]*variables[37]/(variables[37]+variables[85]);
    variables[123] = variables[120]*variables[37]/(variables[37]+variables[85]);
    variables[124] = (variables[45] > 0.0)?-1.0-9.898*pow(1.0*variables[45], 0.618)/(pow(1.0*variables[45], 0.618)+0.00122423):0.0;
    variables[125] = (variables[46] > 0.0)?7.5:0.0;
    variables[127] = (variables[46] > 0.0)?1.23:1.0;
    variables[128] = 0.31*variables[45]/(variables[45]+0.00009);
    variables[129] = (variables[46] > 0.0)?-8.0:0.0;
    variables[130] = (variables[46] > 0.0)?-27.0:0.0;
    variables[133] = (variables[46] > 0.0)?1.2*variables[63]:variables[63];
    variables[135] = (variables[46] > 0.0)?-14.0:0.0;
    variables[136] = (3.5988-0.025641)/(1.0+0.0000012155/pow(1.0*variables[45], 1.6951))+0.025641;
    variables[138] = variables[117]*log(variables[37]/variables[36]);
}

void computeRates(double voi, double *states, double *rates, double *variables)
{
    variables[97] = variables[2]-(variables[2]-variables[3])/(1.0+pow(variables[0]/states[4], variables[1]));
    variables[99] = variables[4]*variables[97];
    variables[98] = variables[6]/variables[97];
    rates[0] = variables[5]*states[3]-variables[99]*states[30]*states[0]-(variables[98]*pow(states[30], 2.0)*states[0]-variables[7]*states[1]);
    rates[1] = variables[98]*pow(states[30], 2.0)*states[0]-variables[7]*states[1]-(variables[99]*states[30]*states[1]-variables[5]*states[2]);
    rates[2] = variables[99]*states[30]*states[1]-variables[5]*states[2]-(variables[7]*states[2]-variables[98]*pow(states[30], 2.0)*states[3]);
    rates[3] = variables[7]*states[2]-variables[98]*pow(states[30], 2.0)*states[3]-(variables[5]*states[3]-variables[99]*states[30]*states[0]);
    variables[105] = (states[13]-states[4])/variables[28];
    variables[95] = variables[8]*states[1]*(states[4]-states[30]);
    variables[111] = variables[20]*states[4]*(1.0-states[11])-variables[15]*states[11];
    rates[4] = variables[105]-(variables[95]+variables[10]*variables[111]);
    variables[131] = variables[54]/(variables[54]+states[30]);
    variables[132] = 0.001*variables[131]/variables[55];
    rates[5] = (variables[131]-states[5])/variables[132];
    variables[106] = variables[21]*states[12]*(1.0-states[6])-variables[16]*states[6];
    rates[6] = variables[106];
    variables[107] = variables[22]*states[12]*(1.0-(states[7]+states[8]))-variables[17]*states[7];
    rates[7] = variables[107];
    variables[108] = variables[23]*variables[11]*(1.0-(states[7]+states[8]))-variables[18]*states[8];
    rates[8] = variables[108];
    variables[109] = variables[19]*states[12]*(1.0-states[9])-variables[14]*states[9];
    rates[9] = variables[109];
    variables[110] = variables[19]*states[30]*(1.0-states[10])-variables[14]*states[10];
    rates[10] = variables[110];
    rates[11] = variables[111];
    variables[103] = (states[30]-states[12])/variables[27];
    variables[104] = variables[102]/(1.0+exp((-states[12]+variables[24])/variables[26]));
    rates[12] = 1.0*(variables[103]*variables[113]-variables[104]*variables[116])/variables[115]-(variables[9]*variables[109]+variables[12]*variables[106]+variables[13]*variables[107]);
    rates[13] = variables[104]-variables[105]*variables[114]/variables[116];
    variables[118] = ((voi > variables[49]) && (voi < variables[49]+variables[50]))?variables[48]:variables[47];
    variables[140] = (variables[43] >= 1.0)?variables[118]:states[31];
    variables[145] = (variables[140] < -(80.0-variables[124]-variables[125]-variables[89]))?0.01329+0.99921/(1.0+exp((variables[140]+97.134-variables[124]-variables[125]-variables[89])/8.1752)):0.0002501*exp(-(variables[140]-variables[124]-variables[125]-variables[89])/12.861);
    variables[144] = 1.0/(0.36*(variables[140]+148.8-variables[124]-variables[125])/(exp(0.066*(variables[140]+148.8-variables[124]-variables[125]))-1.0)+0.1*(variables[140]+87.3-variables[124]-variables[125])/(1.0-exp(-0.2*(variables[140]+87.3-variables[124]-variables[125]))))-0.054;
    rates[14] = (variables[145]-states[14])/variables[144];
    variables[149] = 1.0/(1.0+exp(-(variables[140]+42.0504)/8.3106));
    variables[150] = variables[140]+41.0;
    variables[151] = (fabs(variables[150]) < variables[84])?2000.0:200.0*variables[150]/(1.0-exp(-0.1*variables[150]));
    variables[152] = 8000.0*exp(-0.056*(variables[140]+66.0));
    variables[153] = 1.0/(variables[151]+variables[152]);
    rates[15] = (variables[149]-states[15])/variables[153];
    variables[154] = 1.0/(1.0+exp((variables[140]+69.804)/4.4565));
    variables[155] = 20.0*exp(-0.125*(variables[140]+75.0));
    variables[156] = 2000.0/(320.0*exp(-0.1*(variables[140]+75.0))+1.0);
    variables[157] = 1.0/(variables[155]+variables[156]);
    rates[16] = (variables[154]-states[16])/variables[157];
    variables[170] = 1.0/(1.0+exp((variables[140]+37.4+variables[57])/(5.3+variables[56])));
    variables[171] = 0.001*(44.3+230.0*exp(-pow((variables[140]+36.0)/10.0, 2.0)));
    rates[17] = (variables[170]-states[17])/variables[171];
    variables[173] = 1.0/(1.0+exp(-(variables[140]+38.3)/5.5));
    variables[174] = 0.001/(1.068*exp((variables[140]+38.3)/30.0)+1.068*exp(-(variables[140]+38.3)/30.0));
    rates[18] = (variables[173]-states[18])/variables[174];
    variables[175] = 1.0/(1.0+exp((variables[140]+58.7)/3.8));
    variables[176] = 1.0/(16.67*exp(-(variables[140]+75.0)/83.3)+16.67*exp((variables[140]+75.0)/15.38))+variables[59];
    rates[19] = (variables[175]-states[19])/variables[176];
    variables[178] = 1.0/(1.0+exp((variables[140]+49.0)/13.0));
    variables[179] = 0.001*0.6*(65.17/(0.57*exp(-0.08*(variables[140]+44.0))+0.065*exp(0.1*(variables[140]+45.93)))+10.1);
    rates[20] = (variables[178]-states[20])/variables[179];
    variables[180] = 1.0/(1.0+exp(-(variables[140]-19.3)/15.0));
    variables[181] = 0.001*0.66*1.4*(15.59/(1.037*exp(0.09*(variables[140]+30.61))+0.369*exp(-0.12*(variables[140]+23.84)))+2.98);
    rates[21] = (variables[180]-states[21])/variables[181];
    variables[185] = 1.0/(1.0+exp(-(variables[140]+10.0144)/7.6607));
    variables[186] = 0.84655354/(4.2*exp(variables[140]/17.0)+0.15*exp(-variables[140]/21.6));
    rates[22] = (variables[185]-states[22])/variables[186];
    variables[187] = 1.0/(30.0*exp(variables[140]/10.0)+exp(-variables[140]/12.0));
    rates[23] = (variables[185]-states[23])/variables[187];
    variables[189] = 1.0/(1.0+exp((variables[140]+28.6)/17.1));
    variables[188] = 1.0/(100.0*exp(-variables[140]/54.645)+656.0*exp(variables[140]/106.157));
    rates[24] = (variables[189]-states[24])/variables[188];
    variables[195] = 10.0*exp(0.0133*(variables[140]+40.0));
    variables[196] = variables[136]/(variables[136]+variables[195]);
    variables[197] = 1.0/(variables[136]+variables[195]);
    rates[25] = (variables[196]-states[25])/variables[197];
    variables[159] = 1.0/(1.0+exp((variables[140]+6.0)/-8.6));
    variables[160] = 0.009/(1.0+exp((variables[140]+5.0)/12.0))+0.0005;
    rates[26] = (variables[159]-states[26])/variables[160];
    variables[161] = 1.0/(1.0+exp((variables[140]+7.5)/10.0));
    variables[162] = 0.59/(1.0+exp((variables[140]+60.0)/10.0))+3.05;
    rates[27] = (variables[161]-states[27])/variables[162];
    variables[191] = sqrt(1.0/(1.0+exp(-(variables[140]+0.6383-variables[135])/10.7071)));
    variables[192] = 28.0/(1.0+exp(-(variables[140]-40.0-variables[135])/3.0));
    variables[193] = 1.0*exp(-(variables[140]-variables[135]-5.0)/25.0);
    variables[205] = 1.0/(variables[192]+variables[193]);
    rates[28] = (variables[191]-states[28])/variables[205];
    variables[167] = 1.0/(1.0+exp(-(variables[140]-variables[52]-variables[129])/(variables[53]*(1.0+variables[130]/100.0))));
    variables[168] = (variables[140] == -41.8)?-41.80001:(variables[140] == 0.0)?0.0:(variables[140] == -6.8)?-6.80001:variables[140];
    variables[203] = -0.02839*(variables[168]+41.8)/(exp(-(variables[168]+41.8)/2.5)-1.0)-0.0849*(variables[168]+6.8)/(exp(-(variables[168]+6.8)/4.8)-1.0);
    variables[169] = (variables[140] == -1.8)?-1.80001:variables[140];
    variables[204] = 0.01143*(variables[169]+1.8)/(exp((variables[169]+1.8)/2.5)-1.0);
    variables[210] = 0.001/(variables[203]+variables[204]);
    rates[29] = (variables[167]-states[29])/variables[210];
    variables[163] = 2.0*variables[51]*(variables[140]-0.0)/(variables[117]*(1.0-exp(-1.0*(variables[140]-0.0)*2.0/variables[117])))*(states[30]-variables[35]*exp(-2.0*(variables[140]-0.0)/variables[117]))*states[29]*states[17]*states[5];
    variables[172] = 2.0*variables[58]*variables[140]/(variables[117]*(1.0-exp(-1.0*variables[140]*2.0/variables[117])))*(states[30]-variables[35]*exp(-2.0*variables[140]/variables[117]))*states[18]*states[19];
    variables[202] = 1.0+variables[35]/variables[76]*(1.0+exp(variables[78]*variables[140]/variables[117]))+variables[38]/variables[68]*(1.0+variables[38]/variables[70]*(1.0+variables[38]/variables[72]));
    variables[208] = variables[35]/variables[76]*exp(variables[78]*variables[140]/variables[117])/variables[202];
    variables[91] = states[32];
    variables[200] = 1.0+states[30]/variables[74]*(1.0+exp(-variables[77]*variables[140]/variables[117])+variables[91]/variables[75])+variables[91]/variables[67]*(1.0+variables[91]/variables[69]*(1.0+variables[91]/variables[71]));
    variables[206] = states[30]/variables[74]*exp(-variables[77]*variables[140]/variables[117])/variables[200];
    variables[93] = variables[91]/(variables[71]+variables[91]);
    variables[201] = exp(variables[79]*variables[140]/(2.0*variables[117]));
    variables[199] = exp(-variables[79]*variables[140]/(2.0*variables[117]));
    variables[207] = variables[91]/variables[67]*variables[91]/variables[69]*(1.0+variables[91]/variables[71])*exp(variables[79]*variables[140]/(2.0*variables[117]))/variables[200];
    variables[212] = variables[201]*variables[93]*(variables[207]+variables[206])+variables[199]*variables[206]*(variables[94]+variables[201]);
    variables[209] = variables[38]/variables[68]*variables[38]/variables[70]*(1.0+variables[38]/variables[72])*exp(-variables[79]*variables[140]/(2.0*variables[117]))/variables[202];
    variables[211] = variables[199]*variables[94]*(variables[209]+variables[208])+variables[208]*variables[201]*(variables[93]+variables[199]);
    variables[214] = variables[209]*variables[94]*(variables[207]+variables[206])+variables[207]*variables[208]*(variables[94]+variables[201]);
    variables[213] = variables[207]*variables[93]*(variables[209]+variables[208])+variables[206]*variables[209]*(variables[93]+variables[199]);
    variables[215] = (1.0-variables[80])*variables[73]*(variables[212]*variables[208]-variables[211]*variables[206])/(variables[211]+variables[212]+variables[213]+variables[214]);
    rates[30] = variables[95]*variables[114]/variables[113]-((variables[163]+variables[172]-2.0*variables[215])/(2.0*variables[40]*variables[113])+variables[103]+variables[9]*variables[110]);
    variables[137] = variables[117]*log(variables[38]/variables[91]);
    variables[141] = states[14]*variables[122]*(variables[140]-variables[137])*(1.0-variables[87]);
    variables[142] = states[14]*variables[123]*(variables[140]-variables[138])*(1.0-variables[87]);
    variables[143] = variables[141]+variables[142];
    variables[158] = variables[64]*states[26]*states[27]*(variables[140]-variables[138]);
    variables[194] = (variables[45] > 0.0)?variables[60]*variables[61]*(variables[140]-variables[138])*(1.0+exp((variables[140]+20.0)/20.0))*states[25]:0.0;
    variables[165] = 0.0000185*variables[51]*(variables[140]-0.0)/(variables[117]*(1.0-exp(-1.0*(variables[140]-0.0)/variables[117])))*(variables[91]-variables[38]*exp(-1.0*(variables[140]-0.0)/variables[117]))*states[29]*states[17]*states[5];
    variables[164] = 0.000365*variables[51]*(variables[140]-0.0)/(variables[117]*(1.0-exp(-1.0*(variables[140]-0.0)/variables[117])))*(variables[36]-variables[37]*exp(-1.0*(variables[140]-0.0)/variables[117]))*states[29]*states[17]*states[5];
    variables[166] = (variables[163]+variables[164]+variables[165])*(1.0-variables[128])*1.0*variables[127];
    variables[126] = variables[117]*log((variables[38]+0.12*variables[37])/(variables[91]+0.12*variables[36]));
    variables[146] = variables[65]*pow(states[15], 3.0)*states[16]*(variables[140]-variables[126]);
    variables[147] = variables[66]*pow(states[15], 3.0)*(variables[140]-variables[126]);
    variables[148] = variables[146]+variables[147];
    variables[198] = variables[92]*variables[83]*pow(1.0+pow(variables[81]/variables[37], 1.2), -1.0)*pow(1.0+pow(variables[82]/variables[91], 1.3), -1.0)*pow(1.0+exp(-(variables[140]-variables[137]+110.0)/20.0), -1.0);
    variables[177] = variables[90]*(variables[140]-variables[138])*states[20]*states[21];
    variables[134] = variables[117]*log((variables[37]+0.12*variables[38])/(variables[36]+0.12*variables[91]));
    variables[190] = variables[133]*(variables[140]-variables[134])*pow(states[28], 2.0);
    variables[182] = variables[62]*(variables[140]-variables[138])*(0.9*states[23]+0.1*states[22])*states[24];
    variables[216] = variables[143]+variables[182]+variables[190]+variables[177]+variables[198]+variables[215]+variables[148]+variables[166]+variables[172]+variables[194]+variables[158];
    rates[31] = -variables[216]/variables[39];
    rates[32] = (1.0-variables[44])*-1.0*(variables[148]+variables[141]+variables[165]+3.0*variables[198]+3.0*variables[215])/(1.0*(variables[115]+variables[113])*variables[40]);
}

void computeVariables(double voi, double *states, double *rates, double *variables)
{
    variables[91] = states[32];
    variables[93] = variables[91]/(variables[71]+variables[91]);
    variables[95] = variables[8]*states[1]*(states[4]-states[30]);
    variables[96] = states[4]-states[30];
    variables[97] = variables[2]-(variables[2]-variables[3])/(1.0+pow(variables[0]/states[4], variables[1]));
    variables[98] = variables[6]/variables[97];
    variables[99] = variables[4]*variables[97];
    variables[100] = states[0]+states[1]+states[2]+states[3];
    variables[103] = (states[30]-states[12])/variables[27];
    variables[104] = variables[102]/(1.0+exp((-states[12]+variables[24])/variables[26]));
    variables[105] = (states[13]-states[4])/variables[28];
    variables[106] = variables[21]*states[12]*(1.0-states[6])-variables[16]*states[6];
    variables[107] = variables[22]*states[12]*(1.0-(states[7]+states[8]))-variables[17]*states[7];
    variables[108] = variables[23]*variables[11]*(1.0-(states[7]+states[8]))-variables[18]*states[8];
    variables[109] = variables[19]*states[12]*(1.0-states[9])-variables[14]*states[9];
    variables[110] = variables[19]*states[30]*(1.0-states[10])-variables[14]*states[10];
    variables[111] = variables[20]*states[4]*(1.0-states[11])-variables[15]*states[11];
    variables[126] = variables[117]*log((variables[38]+0.12*variables[37])/(variables[91]+0.12*variables[36]));
    variables[131] = variables[54]/(variables[54]+states[30]);
    variables[132] = 0.001*variables[131]/variables[55];
    variables[134] = variables[117]*log((variables[37]+0.12*variables[38])/(variables[36]+0.12*variables[91]));
    variables[137] = variables[117]*log(variables[38]/variables[91]);
    variables[139] = 0.5*variables[117]*log(variables[35]/states[30]);
    variables[140] = (variables[43] >= 1.0)?variables[118]:states[31];
    variables[141] = states[14]*variables[122]*(variables[140]-variables[137])*(1.0-variables[87]);
    variables[142] = states[14]*variables[123]*(variables[140]-variables[138])*(1.0-variables[87]);
    variables[143] = variables[141]+variables[142];
    variables[144] = 1.0/(0.36*(variables[140]+148.8-variables[124]-variables[125])/(exp(0.066*(variables[140]+148.8-variables[124]-variables[125]))-1.0)+0.1*(variables[140]+87.3-variables[124]-variables[125])/(1.0-exp(-0.2*(variables[140]+87.3-variables[124]-variables[125]))))-0.054;
    variables[145] = (variables[140] < -(80.0-variables[124]-variables[125]-variables[89]))?0.01329+0.99921/(1.0+exp((variables[140]+97.134-variables[124]-variables[125]-variables[89])/8.1752)):0.0002501*exp(-(variables[140]-variables[124]-variables[125]-variables[89])/12.861);
    variables[146] = variables[65]*pow(states[15], 3.0)*states[16]*(variables[140]-variables[126]);
    variables[147] = variables[66]*pow(states[15], 3.0)*(variables[140]-variables[126]);
    variables[148] = variables[146]+variables[147];
    variables[149] = 1.0/(1.0+exp(-(variables[140]+42.0504)/8.3106));
    variables[150] = variables[140]+41.0;
    variables[151] = (fabs(variables[150]) < variables[84])?2000.0:200.0*variables[150]/(1.0-exp(-0.1*variables[150]));
    variables[152] = 8000.0*exp(-0.056*(variables[140]+66.0));
    variables[153] = 1.0/(variables[151]+variables[152]);
    variables[154] = 1.0/(1.0+exp((variables[140]+69.804)/4.4565));
    variables[155] = 20.0*exp(-0.125*(variables[140]+75.0));
    variables[156] = 2000.0/(320.0*exp(-0.1*(variables[140]+75.0))+1.0);
    variables[157] = 1.0/(variables[155]+variables[156]);
    variables[158] = variables[64]*states[26]*states[27]*(variables[140]-variables[138]);
    variables[159] = 1.0/(1.0+exp((variables[140]+6.0)/-8.6));
    variables[160] = 0.009/(1.0+exp((variables[140]+5.0)/12.0))+0.0005;
    variables[161] = 1.0/(1.0+exp((variables[140]+7.5)/10.0));
    variables[162] = 0.59/(1.0+exp((variables[140]+60.0)/10.0))+3.05;
    variables[163] = 2.0*variables[51]*(variables[140]-0.0)/(variables[117]*(1.0-exp(-1.0*(variables[140]-0.0)*2.0/variables[117])))*(states[30]-variables[35]*exp(-2.0*(variables[140]-0.0)/variables[117]))*states[29]*states[17]*states[5];
    variables[164] = 0.000365*variables[51]*(variables[140]-0.0)/(variables[117]*(1.0-exp(-1.0*(variables[140]-0.0)/variables[117])))*(variables[36]-variables[37]*exp(-1.0*(variables[140]-0.0)/variables[117]))*states[29]*states[17]*states[5];
    variables[165] = 0.0000185*variables[51]*(variables[140]-0.0)/(variables[117]*(1.0-exp(-1.0*(variables[140]-0.0)/variables[117])))*(variables[91]-variables[38]*exp(-1.0*(variables[140]-0.0)/variables[117]))*states[29]*states[17]*states[5];
    variables[166] = (variables[163]+variables[164]+variables[165])*(1.0-variables[128])*1.0*variables[127];
    variables[167] = 1.0/(1.0+exp(-(variables[140]-variables[52]-variables[129])/(variables[53]*(1.0+variables[130]/100.0))));
    variables[168] = (variables[140] == -41.8)?-41.80001:(variables[140] == 0.0)?0.0:(variables[140] == -6.8)?-6.80001:variables[140];
    variables[169] = (variables[140] == -1.8)?-1.80001:variables[140];
    variables[170] = 1.0/(1.0+exp((variables[140]+37.4+variables[57])/(5.3+variables[56])));
    variables[171] = 0.001*(44.3+230.0*exp(-pow((variables[140]+36.0)/10.0, 2.0)));
    variables[172] = 2.0*variables[58]*variables[140]/(variables[117]*(1.0-exp(-1.0*variables[140]*2.0/variables[117])))*(states[30]-variables[35]*exp(-2.0*variables[140]/variables[117]))*states[18]*states[19];
    variables[173] = 1.0/(1.0+exp(-(variables[140]+38.3)/5.5));
    variables[174] = 0.001/(1.068*exp((variables[140]+38.3)/30.0)+1.068*exp(-(variables[140]+38.3)/30.0));
    variables[175] = 1.0/(1.0+exp((variables[140]+58.7)/3.8));
    variables[176] = 1.0/(16.67*exp(-(variables[140]+75.0)/83.3)+16.67*exp((variables[140]+75.0)/15.38))+variables[59];
    variables[177] = variables[90]*(variables[140]-variables[138])*states[20]*states[21];
    variables[178] = 1.0/(1.0+exp((variables[140]+49.0)/13.0));
    variables[179] = 0.001*0.6*(65.17/(0.57*exp(-0.08*(variables[140]+44.0))+0.065*exp(0.1*(variables[140]+45.93)))+10.1);
    variables[180] = 1.0/(1.0+exp(-(variables[140]-19.3)/15.0));
    variables[181] = 0.001*0.66*1.4*(15.59/(1.037*exp(0.09*(variables[140]+30.61))+0.369*exp(-0.12*(variables[140]+23.84)))+2.98);
    variables[182] = variables[62]*(variables[140]-variables[138])*(0.9*states[23]+0.1*states[22])*states[24];
    variables[183] = 1.0/(1.0+exp(-(variables[140]+23.2)/6.6))/(0.84655354/(37.2*exp(variables[140]/11.9)+0.96*exp(-variables[140]/18.5)));
    variables[184] = 4.0*((37.2*exp(variables[140]/15.9)+0.96*exp(-variables[140]/22.5))/0.84655354-1.0/(1.0+exp(-(variables[140]+23.2)/10.6))/(0.84655354/(37.2*exp(variables[140]/15.9)+0.96*exp(-variables[140]/22.5))));
    variables[185] = 1.0/(1.0+exp(-(variables[140]+10.0144)/7.6607));
    variables[186] = 0.84655354/(4.2*exp(variables[140]/17.0)+0.15*exp(-variables[140]/21.6));
    variables[187] = 1.0/(30.0*exp(variables[140]/10.0)+exp(-variables[140]/12.0));
    variables[188] = 1.0/(100.0*exp(-variables[140]/54.645)+656.0*exp(variables[140]/106.157));
    variables[189] = 1.0/(1.0+exp((variables[140]+28.6)/17.1));
    variables[190] = variables[133]*(variables[140]-variables[134])*pow(states[28], 2.0);
    variables[191] = sqrt(1.0/(1.0+exp(-(variables[140]+0.6383-variables[135])/10.7071)));
    variables[192] = 28.0/(1.0+exp(-(variables[140]-40.0-variables[135])/3.0));
    variables[193] = 1.0*exp(-(variables[140]-variables[135]-5.0)/25.0);
    variables[194] = (variables[45] > 0.0)?variables[60]*variables[61]*(variables[140]-variables[138])*(1.0+exp((variables[140]+20.0)/20.0))*states[25]:0.0;
    variables[195] = 10.0*exp(0.0133*(variables[140]+40.0));
    variables[196] = variables[136]/(variables[136]+variables[195]);
    variables[197] = 1.0/(variables[136]+variables[195]);
    variables[198] = variables[92]*variables[83]*pow(1.0+pow(variables[81]/variables[37], 1.2), -1.0)*pow(1.0+pow(variables[82]/variables[91], 1.3), -1.0)*pow(1.0+exp(-(variables[140]-variables[137]+110.0)/20.0), -1.0);
    variables[199] = exp(-variables[79]*variables[140]/(2.0*variables[117]));
    variables[200] = 1.0+states[30]/variables[74]*(1.0+exp(-variables[77]*variables[140]/variables[117])+variables[91]/variables[75])+variables[91]/variables[67]*(1.0+variables[91]/variables[69]*(1.0+variables[91]/variables[71]));
    variables[201] = exp(variables[79]*variables[140]/(2.0*variables[117]));
    variables[202] = 1.0+variables[35]/variables[76]*(1.0+exp(variables[78]*variables[140]/variables[117]))+variables[38]/variables[68]*(1.0+variables[38]/variables[70]*(1.0+variables[38]/variables[72]));
    variables[203] = -0.02839*(variables[168]+41.8)/(exp(-(variables[168]+41.8)/2.5)-1.0)-0.0849*(variables[168]+6.8)/(exp(-(variables[168]+6.8)/4.8)-1.0);
    variables[204] = 0.01143*(variables[169]+1.8)/(exp((variables[169]+1.8)/2.5)-1.0);
    variables[205] = 1.0/(variables[192]+variables[193]);
    variables[206] = states[30]/variables[74]*exp(-variables[77]*variables[140]/variables[117])/variables[200];
    variables[207] = variables[91]/variables[67]*variables[91]/variables[69]*(1.0+variables[91]/variables[71])*exp(variables[79]*variables[140]/(2.0*variables[117]))/variables[200];
    variables[208] = variables[35]/variables[76]*exp(variables[78]*variables[140]/variables[117])/variables[202];
    variables[209] = variables[38]/variables[68]*variables[38]/variables[70]*(1.0+variables[38]/variables[72])*exp(-variables[79]*variables[140]/(2.0*variables[117]))/variables[202];
    variables[210] = 0.001/(variables[203]+variables[204]);
    variables[211] = variables[199]*variables[94]*(variables[209]+variables[208])+variables[208]*variables[201]*(variables[93]+variables[199]);
    variables[212] = variables[201]*variables[93]*(variables[207]+variables[206])+variables[199]*variables[206]*(variables[94]+variables[201]);
    variables[213] = variables[207]*variables[93]*(variables[209]+variables[208])+variables[206]*variables[209]*(variables[93]+variables[199]);
    variables[214] = variables[209]*variables[94]*(variables[207]+variables[206])+variables[207]*variables[208]*(variables[94]+variables[201]);
    variables[215] = (1.0-variables[80])*variables[73]*(variables[212]*variables[208]-variables[211]*variables[206])/(variables[211]+variables[212]+variables[213]+variables[214]);
    variables[216] = variables[143]+variables[182]+variables[190]+variables[177]+variables[198]+variables[215]+variables[148]+variables[166]+variables[172]+variables[194]+variables[158];
}

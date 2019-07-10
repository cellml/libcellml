double fact(double x)
{
     return tgamma(x+1.0);
}

double min(double x, double y)
{
     return (x < y)?x:y;
}

double max(double x, double y)
{
     return (x > y)?x:y;
}

void initializeModel(double *states, double *variables)
{
    states[0] = 0.0;
    variables[0] = 1.0;
    variables[1] = 2.0;
    variables[2] = 3.0;
    variables[3] = 4.0;
    variables[4] = 5.0;
    variables[5] = 6.0;
    variables[6] = 7.0;
    variables[177] = 123.0;
    variables[178] = 123.456789;
    variables[179] = 123.0e99;
    variables[180] = 123.456789e99;
    variables[182] = true;
    variables[183] = false;
    variables[184] = 2.71828182845905;
    variables[185] = 3.14159265358979;
    variables[186] = 1.0/0.0;
    variables[187] = sqrt(-1.0);
}

void computeConstantEquations(double *variables)
{
    variables[7] = variables[0] == variables[1];
    variables[8] = variables[0] != variables[1];
    variables[9] = variables[0] < variables[1];
    variables[10] = variables[0] <= variables[1];
    variables[11] = variables[0] > variables[1];
    variables[12] = variables[0] >= variables[1];
    variables[13] = variables[0] && variables[1];
    variables[14] = variables[0] && variables[1] && variables[2] && variables[3] && variables[4];
    variables[15] = (variables[0] < variables[1]) && (variables[2] > variables[3]);
    variables[16] = (variables[0]+variables[1]) && (variables[2] > variables[3]);
    variables[17] = variables[0] && (variables[1] > variables[2]);
    variables[18] = (variables[0]-variables[1]) && (variables[2] > variables[3]);
    variables[19] = -variables[0] && (variables[1] > variables[2]);
    variables[20] = pow(variables[0], variables[1]) && (variables[2] > variables[3]);
    variables[21] = pow(variables[0], 1.0/variables[1]) && (variables[2] > variables[3]);
    variables[22] = (variables[0] < variables[1]) && (variables[2]+variables[3]);
    variables[23] = (variables[0] < variables[1]) && variables[2];
    variables[24] = (variables[0] < variables[1]) && (variables[2]-variables[3]);
    variables[25] = (variables[0] < variables[1]) && -variables[2];
    variables[26] = (variables[0] < variables[1]) && pow(variables[2], variables[3]);
    variables[27] = (variables[0] < variables[1]) && pow(variables[2], 1.0/variables[3]);
    variables[28] = variables[0] || variables[1];
    variables[29] = variables[0] || variables[1] || variables[2] || variables[3] || variables[4];
    variables[30] = (variables[0] < variables[1]) || (variables[2] > variables[3]);
    variables[31] = (variables[0]+variables[1]) || (variables[2] > variables[3]);
    variables[32] = variables[0] || (variables[1] > variables[2]);
    variables[33] = (variables[0]-variables[1]) || (variables[2] > variables[3]);
    variables[34] = -variables[0] || (variables[1] > variables[2]);
    variables[35] = pow(variables[0], variables[1]) || (variables[2] > variables[3]);
    variables[36] = pow(variables[0], 1.0/variables[1]) || (variables[2] > variables[3]);
    variables[37] = (variables[0] < variables[1]) || (variables[2]+variables[3]);
    variables[38] = (variables[0] < variables[1]) || variables[2];
    variables[39] = (variables[0] < variables[1]) || (variables[2]-variables[3]);
    variables[40] = (variables[0] < variables[1]) || -variables[2];
    variables[41] = (variables[0] < variables[1]) || pow(variables[2], variables[3]);
    variables[42] = (variables[0] < variables[1]) || pow(variables[2], 1.0/variables[3]);
    variables[43] = variables[0]^variables[1];
    variables[44] = variables[0]^variables[1]^variables[2]^variables[3]^variables[4];
    variables[45] = (variables[0] < variables[1])^(variables[2] > variables[3]);
    variables[46] = (variables[0]+variables[1])^(variables[2] > variables[3]);
    variables[47] = variables[0]^(variables[1] > variables[2]);
    variables[48] = (variables[0]-variables[1])^(variables[2] > variables[3]);
    variables[49] = -variables[0]^(variables[1] > variables[2]);
    variables[50] = pow(variables[0], variables[1])^(variables[2] > variables[3]);
    variables[51] = pow(variables[0], 1.0/variables[1])^(variables[2] > variables[3]);
    variables[52] = (variables[0] < variables[1])^(variables[2]+variables[3]);
    variables[53] = (variables[0] < variables[1])^variables[2];
    variables[54] = (variables[0] < variables[1])^(variables[2]-variables[3]);
    variables[55] = (variables[0] < variables[1])^-variables[2];
    variables[56] = (variables[0] < variables[1])^pow(variables[2], variables[3]);
    variables[57] = (variables[0] < variables[1])^pow(variables[2], 1.0/variables[3]);
    variables[58] = !variables[0];
    variables[59] = variables[0]+variables[1];
    variables[60] = variables[0]+variables[1]+variables[2]+variables[3]+variables[4];
    variables[61] = (variables[0] < variables[1])+(variables[2] > variables[3]);
    variables[62] = variables[0];
    variables[63] = variables[0]-variables[1];
    variables[64] = (variables[0] < variables[1])-(variables[2] > variables[3]);
    variables[65] = (variables[0] < variables[1])-(variables[2]+variables[3]);
    variables[66] = (variables[0] < variables[1])-variables[2];
    variables[67] = -variables[0];
    variables[68] = -(variables[0] < variables[1]);
    variables[69] = variables[0]*variables[1];
    variables[70] = variables[0]*variables[1]*variables[2]*variables[3]*variables[4];
    variables[71] = (variables[0] < variables[1])*(variables[2] > variables[3]);
    variables[72] = (variables[0]+variables[1])*(variables[2] > variables[3]);
    variables[73] = variables[0]*(variables[1] > variables[2]);
    variables[74] = (variables[0]-variables[1])*(variables[2] > variables[3]);
    variables[75] = -variables[0]*(variables[1] > variables[2]);
    variables[76] = (variables[0] < variables[1])*(variables[2]+variables[3]);
    variables[77] = (variables[0] < variables[1])*variables[2];
    variables[78] = (variables[0] < variables[1])*(variables[2]-variables[3]);
    variables[79] = (variables[0] < variables[1])*-variables[2];
    variables[80] = variables[0]/variables[1];
    variables[81] = (variables[0] < variables[1])/(variables[2] > variables[3]);
    variables[82] = (variables[0]+variables[1])/(variables[2] > variables[3]);
    variables[83] = variables[0]/(variables[1] > variables[2]);
    variables[84] = (variables[0]-variables[1])/(variables[2] > variables[3]);
    variables[85] = -variables[0]/(variables[1] > variables[2]);
    variables[86] = (variables[0] < variables[1])/(variables[2]+variables[3]);
    variables[87] = (variables[0] < variables[1])/variables[2];
    variables[88] = (variables[0] < variables[1])/(variables[2]-variables[3]);
    variables[89] = (variables[0] < variables[1])/-variables[2];
    variables[90] = (variables[0] < variables[1])/(variables[2]*variables[3]);
    variables[91] = (variables[0] < variables[1])/(variables[2]/variables[3]);
    variables[92] = sqrt(variables[0]);
    variables[93] = sqr(variables[0]);
    variables[94] = pow(variables[0], 3.0);
    variables[95] = pow(variables[0], variables[1]);
    variables[96] = pow(variables[0] < variables[1], variables[2] > variables[3]);
    variables[97] = pow(variables[0]+variables[1], variables[2] > variables[3]);
    variables[98] = pow(variables[0], variables[1] > variables[2]);
    variables[99] = pow(variables[0]-variables[1], variables[2] > variables[3]);
    variables[100] = pow(-variables[0], variables[1] > variables[2]);
    variables[101] = pow(variables[0]*variables[1], variables[2] > variables[3]);
    variables[102] = pow(variables[0]/variables[1], variables[2] > variables[3]);
    variables[103] = pow(variables[0] < variables[1], variables[2]+variables[3]);
    variables[104] = pow(variables[0] < variables[1], variables[2]);
    variables[105] = pow(variables[0] < variables[1], variables[2]-variables[3]);
    variables[106] = pow(variables[0] < variables[1], -variables[2]);
    variables[107] = pow(variables[0] < variables[1], variables[2]*variables[3]);
    variables[108] = pow(variables[0] < variables[1], variables[2]/variables[3]);
    variables[109] = pow(variables[0] < variables[1], pow(variables[2], variables[3]));
    variables[110] = pow(variables[0] < variables[1], pow(variables[2], 1.0/variables[3]));
    variables[111] = sqrt(variables[0]);
    variables[112] = sqrt(variables[0]);
    variables[113] = pow(variables[0], 1.0/3.0);
    variables[114] = pow(variables[0], 1.0/variables[1]);
    variables[115] = pow(variables[0] < variables[1], 1.0/variables[2] > variables[3]);
    variables[116] = pow(variables[0]+variables[1], 1.0/variables[2] > variables[3]);
    variables[117] = pow(variables[0], 1.0/variables[1] > variables[2]);
    variables[118] = pow(variables[0]-variables[1], 1.0/variables[2] > variables[3]);
    variables[119] = pow(-variables[0], 1.0/variables[1] > variables[2]);
    variables[120] = pow(variables[0]*variables[1], 1.0/variables[2] > variables[3]);
    variables[121] = pow(variables[0]/variables[1], 1.0/variables[2] > variables[3]);
    variables[122] = pow(variables[0] < variables[1], 1.0/variables[2]+variables[3]);
    variables[123] = pow(variables[0] < variables[1], 1.0/variables[2]);
    variables[124] = pow(variables[0] < variables[1], 1.0/variables[2]-variables[3]);
    variables[125] = pow(variables[0] < variables[1], 1.0/-variables[2]);
    variables[126] = pow(variables[0] < variables[1], 1.0/variables[2]*variables[3]);
    variables[127] = pow(variables[0] < variables[1], 1.0/variables[2]/variables[3]);
    variables[128] = pow(variables[0] < variables[1], 1.0/pow(variables[2], variables[3]));
    variables[129] = pow(variables[0] < variables[1], 1.0/pow(variables[2], 1.0/variables[3]));
    variables[130] = fabs(variables[0]);
    variables[131] = exp(variables[0]);
    variables[132] = log(variables[0]);
    variables[133] = log10(variables[0]);
    variables[134] = log(variables[0])/log(2.0);
    variables[135] = log10(variables[0]);
    variables[136] = log(variables[0])/log(variables[1]);
    variables[137] = ceil(variables[0]);
    variables[138] = floor(variables[0]);
    variables[139] = fact(variables[0]);
    variables[140] = min(variables[0], variables[1]);
    variables[141] = min(variables[0], variables[1], variables[2], variables[3], variables[4]);
    variables[142] = max(variables[0], variables[1]);
    variables[143] = max(variables[0], variables[1], variables[2], variables[3], variables[4]);
    variables[144] = gcd(variables[0], variables[1]);
    variables[145] = gcd(variables[0], variables[1], variables[2], variables[3], variables[4]);
    variables[146] = lcm(variables[0], variables[1]);
    variables[147] = lcm(variables[0], variables[1], variables[2], variables[3], variables[4]);
    variables[148] = sin(variables[0]);
    variables[149] = cos(variables[0]);
    variables[150] = tan(variables[0]);
    variables[151] = sec(variables[0]);
    variables[152] = csc(variables[0]);
    variables[153] = cot(variables[0]);
    variables[154] = sinh(variables[0]);
    variables[155] = cosh(variables[0]);
    variables[156] = tanh(variables[0]);
    variables[157] = sech(variables[0]);
    variables[158] = csch(variables[0]);
    variables[159] = coth(variables[0]);
    variables[160] = asin(variables[0]);
    variables[161] = acos(variables[0]);
    variables[162] = atan(variables[0]);
    variables[163] = asec(variables[0]);
    variables[164] = acsc(variables[0]);
    variables[165] = acot(variables[0]);
    variables[166] = asinh(variables[0]);
    variables[167] = acosh(variables[0]);
    variables[168] = atanh(variables[0]);
    variables[169] = asech(variables[0]);
    variables[170] = acsch(variables[0]);
    variables[171] = acoth(variables[0]);
    variables[172] = fmod(variables[0], variables[1]);
    variables[173] = (variables[0] > variables[1])?variables[0]:sqrt(-1.0);
    variables[174] = (variables[0] > variables[1])?variables[0]:variables[2];
    variables[175] = (variables[0] > variables[1])?variables[0]:(variables[2] > variables[3])?variables[2]:(variables[4] > variables[5])?variables[4]:sqrt(-1.0);
    variables[176] = (variables[0] > variables[1])?variables[0]:(variables[2] > variables[3])?variables[2]:(variables[4] > variables[5])?variables[4]:variables[6];
    variables[181] = variables[0];
}

void computeRateEquations(double voi, double *states, double *rates, double *variables)
{
    rates[0] = 1.0;
}

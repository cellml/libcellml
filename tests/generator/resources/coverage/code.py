from math import *

def min(x, y):
    return x if (x < y) else y

def max(x, y):
    return x if (x > y) else y

def sec(x):
    return 1.0/cos(x)

def csc(x):
    return 1.0/sin(x)

def cot(x):
    return 1.0/tan(x)

def sech(x):
    return 1.0/cosh(x)

def csch(x):
    return 1.0/sinh(x)

def coth(x):
    return 1.0/tanh(x)

def asec(x):
    return acos(1.0/x)

def acsc(x):
    return asin(1.0/x)

def acot(x):
    return atan(1.0/x)

def asech(x):
    oneOverX = 1.0/x

    return log(oneOverX+sqrt(oneOverX*oneOverX-1.0))

def acsch(x):
    oneOverX = 1.0/x

    return log(oneOverX+sqrt(oneOverX*oneOverX+1.0))

def acoth(x):
    oneOverX = 1.0/x

    return 0.5*log((1.0+oneOverX)/(1.0-oneOverX))

def initializeConstants(states, variables):
    states[0] = 0.0
    variables[0] = 1.0
    variables[1] = 2.0
    variables[2] = 3.0
    variables[3] = 4.0
    variables[4] = 5.0
    variables[5] = 6.0
    variables[6] = 7.0
    variables[172] = 123.0
    variables[173] = 123.456789
    variables[174] = 123.0e99
    variables[175] = 123.456789e99
    variables[177] = 1.0
    variables[178] = 0.0
    variables[179] = 2.71828182845905
    variables[180] = 3.14159265358979
    variables[181] = 1.0/0.0
    variables[182] = sqrt(-1.0)

def computeComputedConstants(variables):
    variables[7] = variables[0] == variables[1]
    variables[8] = variables[0] != variables[1]
    variables[9] = variables[0] < variables[1]
    variables[10] = variables[0] <= variables[1]
    variables[11] = variables[0] > variables[1]
    variables[12] = variables[0] >= variables[1]
    variables[13] = variables[0] & variables[1]
    variables[14] = variables[0] & variables[1] & variables[2]
    variables[15] = (variables[0] < variables[1]) & (variables[2] > variables[3])
    variables[16] = (variables[0]+variables[1]) & (variables[2] > variables[3])
    variables[17] = variables[0] & (variables[1] > variables[2])
    variables[18] = (variables[0]-variables[1]) & (variables[2] > variables[3])
    variables[19] = -variables[0] & (variables[1] > variables[2])
    variables[20] = pow(variables[0], variables[1]) & (variables[2] > variables[3])
    variables[21] = pow(variables[0], 1.0/variables[1]) & (variables[2] > variables[3])
    variables[22] = (variables[0] < variables[1]) & (variables[2]+variables[3])
    variables[23] = (variables[0] < variables[1]) & variables[2]
    variables[24] = (variables[0] < variables[1]) & (variables[2]-variables[3])
    variables[25] = (variables[0] < variables[1]) & -variables[2]
    variables[26] = (variables[0] < variables[1]) & pow(variables[2], variables[3])
    variables[27] = (variables[0] < variables[1]) & pow(variables[2], 1.0/variables[3])
    variables[28] = variables[0] | variables[1]
    variables[29] = variables[0] | variables[1] | variables[2]
    variables[30] = (variables[0] < variables[1]) | (variables[2] > variables[3])
    variables[31] = (variables[0]+variables[1]) | (variables[2] > variables[3])
    variables[32] = variables[0] | (variables[1] > variables[2])
    variables[33] = (variables[0]-variables[1]) | (variables[2] > variables[3])
    variables[34] = -variables[0] | (variables[1] > variables[2])
    variables[35] = pow(variables[0], variables[1]) | (variables[2] > variables[3])
    variables[36] = pow(variables[0], 1.0/variables[1]) | (variables[2] > variables[3])
    variables[37] = (variables[0] < variables[1]) | (variables[2]+variables[3])
    variables[38] = (variables[0] < variables[1]) | variables[2]
    variables[39] = (variables[0] < variables[1]) | (variables[2]-variables[3])
    variables[40] = (variables[0] < variables[1]) | -variables[2]
    variables[41] = (variables[0] < variables[1]) | pow(variables[2], variables[3])
    variables[42] = (variables[0] < variables[1]) | pow(variables[2], 1.0/variables[3])
    variables[43] = xor(variables[0], variables[1])
    variables[44] = xor(variables[0], xor(variables[1], variables[2]))
    variables[45] = xor(variables[0] < variables[1], variables[2] > variables[3])
    variables[46] = xor(variables[0]+variables[1], variables[2] > variables[3])
    variables[47] = xor(variables[0], variables[1] > variables[2])
    variables[48] = xor(variables[0]-variables[1], variables[2] > variables[3])
    variables[49] = xor(-variables[0], variables[1] > variables[2])
    variables[50] = xor(pow(variables[0], variables[1]), variables[2] > variables[3])
    variables[51] = xor(pow(variables[0], 1.0/variables[1]), variables[2] > variables[3])
    variables[52] = xor(variables[0] < variables[1], variables[2]+variables[3])
    variables[53] = xor(variables[0] < variables[1], variables[2])
    variables[54] = xor(variables[0] < variables[1], variables[2]-variables[3])
    variables[55] = xor(variables[0] < variables[1], -variables[2])
    variables[56] = xor(variables[0] < variables[1], pow(variables[2], variables[3]))
    variables[57] = xor(variables[0] < variables[1], pow(variables[2], 1.0/variables[3]))
    variables[58] = not(variables[0])
    variables[59] = variables[0]+variables[1]
    variables[60] = variables[0]+variables[1]+variables[2]
    variables[61] = (variables[0] < variables[1])+(variables[2] > variables[3])
    variables[62] = variables[0]
    variables[63] = variables[0]-variables[1]
    variables[64] = (variables[0] < variables[1])-(variables[2] > variables[3])
    variables[65] = (variables[0] < variables[1])-(variables[2]+variables[3])
    variables[66] = (variables[0] < variables[1])-variables[2]
    variables[67] = -variables[0]
    variables[68] = -(variables[0] < variables[1])
    variables[69] = variables[0]*variables[1]
    variables[70] = variables[0]*variables[1]*variables[2]
    variables[71] = (variables[0] < variables[1])*(variables[2] > variables[3])
    variables[72] = (variables[0]+variables[1])*(variables[2] > variables[3])
    variables[73] = variables[0]*(variables[1] > variables[2])
    variables[74] = (variables[0]-variables[1])*(variables[2] > variables[3])
    variables[75] = -variables[0]*(variables[1] > variables[2])
    variables[76] = (variables[0] < variables[1])*(variables[2]+variables[3])
    variables[77] = (variables[0] < variables[1])*variables[2]
    variables[78] = (variables[0] < variables[1])*(variables[2]-variables[3])
    variables[79] = (variables[0] < variables[1])*-variables[2]
    variables[80] = variables[0]/variables[1]
    variables[81] = (variables[0] < variables[1])/(variables[2] > variables[3])
    variables[82] = (variables[0]+variables[1])/(variables[2] > variables[3])
    variables[83] = variables[0]/(variables[1] > variables[2])
    variables[84] = (variables[0]-variables[1])/(variables[2] > variables[3])
    variables[85] = -variables[0]/(variables[1] > variables[2])
    variables[86] = (variables[0] < variables[1])/(variables[2]+variables[3])
    variables[87] = (variables[0] < variables[1])/variables[2]
    variables[88] = (variables[0] < variables[1])/(variables[2]-variables[3])
    variables[89] = (variables[0] < variables[1])/-variables[2]
    variables[90] = (variables[0] < variables[1])/(variables[2]*variables[3])
    variables[91] = (variables[0] < variables[1])/(variables[2]/variables[3])
    variables[92] = sqrt(variables[0])
    variables[93] = pow(variables[0], 2.0)
    variables[94] = pow(variables[0], 3.0)
    variables[95] = pow(variables[0], variables[1])
    variables[96] = pow(variables[0] < variables[1], variables[2] > variables[3])
    variables[97] = pow(variables[0]+variables[1], variables[2] > variables[3])
    variables[98] = pow(variables[0], variables[1] > variables[2])
    variables[99] = pow(variables[0]-variables[1], variables[2] > variables[3])
    variables[100] = pow(-variables[0], variables[1] > variables[2])
    variables[101] = pow(variables[0]*variables[1], variables[2] > variables[3])
    variables[102] = pow(variables[0]/variables[1], variables[2] > variables[3])
    variables[103] = pow(variables[0] < variables[1], variables[2]+variables[3])
    variables[104] = pow(variables[0] < variables[1], variables[2])
    variables[105] = pow(variables[0] < variables[1], variables[2]-variables[3])
    variables[106] = pow(variables[0] < variables[1], -variables[2])
    variables[107] = pow(variables[0] < variables[1], variables[2]*variables[3])
    variables[108] = pow(variables[0] < variables[1], variables[2]/variables[3])
    variables[109] = pow(variables[0] < variables[1], pow(variables[2], variables[3]))
    variables[110] = pow(variables[0] < variables[1], pow(variables[2], 1.0/variables[3]))
    variables[111] = sqrt(variables[0])
    variables[112] = sqrt(variables[0])
    variables[113] = pow(variables[0], 1.0/3.0)
    variables[114] = pow(variables[0], 1.0/variables[1])
    variables[115] = pow(variables[0] < variables[1], 1.0/variables[2] > variables[3])
    variables[116] = pow(variables[0]+variables[1], 1.0/variables[2] > variables[3])
    variables[117] = pow(variables[0], 1.0/variables[1] > variables[2])
    variables[118] = pow(variables[0]-variables[1], 1.0/variables[2] > variables[3])
    variables[119] = pow(-variables[0], 1.0/variables[1] > variables[2])
    variables[120] = pow(variables[0]*variables[1], 1.0/variables[2] > variables[3])
    variables[121] = pow(variables[0]/variables[1], 1.0/variables[2] > variables[3])
    variables[122] = pow(variables[0] < variables[1], 1.0/variables[2]+variables[3])
    variables[123] = pow(variables[0] < variables[1], 1.0/variables[2])
    variables[124] = pow(variables[0] < variables[1], 1.0/variables[2]-variables[3])
    variables[125] = pow(variables[0] < variables[1], 1.0/-variables[2])
    variables[126] = pow(variables[0] < variables[1], 1.0/variables[2]*variables[3])
    variables[127] = pow(variables[0] < variables[1], 1.0/variables[2]/variables[3])
    variables[128] = pow(variables[0] < variables[1], 1.0/pow(variables[2], variables[3]))
    variables[129] = pow(variables[0] < variables[1], 1.0/pow(variables[2], 1.0/variables[3]))
    variables[130] = fabs(variables[0])
    variables[131] = exp(variables[0])
    variables[132] = log(variables[0])
    variables[133] = log10(variables[0])
    variables[134] = log(variables[0])/log(2.0)
    variables[135] = log10(variables[0])
    variables[136] = log(variables[0])/log(variables[1])
    variables[137] = ceil(variables[0])
    variables[138] = floor(variables[0])
    variables[139] = min(variables[0], variables[1])
    variables[140] = min(variables[0], min(variables[1], variables[2]))
    variables[141] = max(variables[0], variables[1])
    variables[142] = max(variables[0], max(variables[1], variables[2]))
    variables[143] = fmod(variables[0], variables[1])
    variables[144] = sin(variables[0])
    variables[145] = cos(variables[0])
    variables[146] = tan(variables[0])
    variables[147] = sec(variables[0])
    variables[148] = csc(variables[0])
    variables[149] = cot(variables[0])
    variables[150] = sinh(variables[0])
    variables[151] = cosh(variables[0])
    variables[152] = tanh(variables[0])
    variables[153] = sech(variables[0])
    variables[154] = csch(variables[0])
    variables[155] = coth(variables[0])
    variables[156] = asin(variables[0])
    variables[157] = acos(variables[0])
    variables[158] = atan(variables[0])
    variables[159] = asec(variables[0])
    variables[160] = acsc(variables[0])
    variables[161] = acot(variables[0])
    variables[162] = asinh(variables[0])
    variables[163] = acosh(variables[0])
    variables[164] = atanh(variables[0])
    variables[165] = asech(variables[0])
    variables[166] = acsch(variables[0])
    variables[167] = acoth(variables[0])
    variables[168] = variables[0] if (variables[0] > variables[1]) else sqrt(-1.0)
    variables[169] = variables[0] if (variables[0] > variables[1]) else variables[2]
    variables[170] = variables[0] if (variables[0] > variables[1]) else variables[2] if (variables[2] > variables[3]) else variables[4] if (variables[4] > variables[5]) else sqrt(-1.0)
    variables[171] = variables[0] if (variables[0] > variables[1]) else variables[2] if (variables[2] > variables[3]) else variables[4] if (variables[4] > variables[5]) else variables[6]
    variables[176] = variables[0]

def computeRates(voi, states, rates, variables):
    rates[0] = 1.0

def computeVariables(voi, states, rates, variables):
    pass

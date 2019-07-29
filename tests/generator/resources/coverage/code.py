from math import *

def eqEqFunc(x, y):
    return 1.0 if (x == y) else 0.0

def neqFunc(x, y):
    return 1.0 if (x != y) else 0.0

def ltFunc(x, y):
    return 1.0 if (x < y) else 0.0

def leqFunc(x, y):
    return 1.0 if (x <= y) else 0.0

def gtFunc(x, y):
    return 1.0 if (x > y) else 0.0

def geqFunc(x, y):
    return 1.0 if (x >= y) else 0.0

def andFunc(x, y):
    return 1.0 if (bool(x) & bool(y)) else 0.0

def orFunc(x, y):
    return 1.0 if (bool(x) | bool(y)) else 0.0

def xorFunc(x, y):
    return 1.0 if (bool(x) ^ bool(y)) else 0.0

def notFunc(x):
    return 1.0 if (not bool(x)) else 0.0

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
    variables[181] = inf
    variables[182] = nan

def computeComputedConstants(variables):
    variables[7] = eqEqFunc(variables[0], variables[1])
    variables[8] = neqFunc(variables[0], variables[1])
    variables[9] = ltFunc(variables[0], variables[1])
    variables[10] = leqFunc(variables[0], variables[1])
    variables[11] = gtFunc(variables[0], variables[1])
    variables[12] = geqFunc(variables[0], variables[1])
    variables[13] = andFunc(variables[0], variables[1])
    variables[14] = andFunc(variables[0], andFunc(variables[1], variables[2]))
    variables[15] = andFunc(ltFunc(variables[0], variables[1]), gtFunc(variables[2], variables[3]))
    variables[16] = andFunc(variables[0]+variables[1], gtFunc(variables[2], variables[3]))
    variables[17] = andFunc(variables[0], gtFunc(variables[1], variables[2]))
    variables[18] = andFunc(variables[0]-variables[1], gtFunc(variables[2], variables[3]))
    variables[19] = andFunc(-variables[0], gtFunc(variables[1], variables[2]))
    variables[20] = andFunc(pow(variables[0], variables[1]), gtFunc(variables[2], variables[3]))
    variables[21] = andFunc(pow(variables[0], 1.0/variables[1]), gtFunc(variables[2], variables[3]))
    variables[22] = andFunc(ltFunc(variables[0], variables[1]), variables[2]+variables[3])
    variables[23] = andFunc(ltFunc(variables[0], variables[1]), variables[2])
    variables[24] = andFunc(ltFunc(variables[0], variables[1]), variables[2]-variables[3])
    variables[25] = andFunc(ltFunc(variables[0], variables[1]), -variables[2])
    variables[26] = andFunc(ltFunc(variables[0], variables[1]), pow(variables[2], variables[3]))
    variables[27] = andFunc(ltFunc(variables[0], variables[1]), pow(variables[2], 1.0/variables[3]))
    variables[28] = orFunc(variables[0], variables[1])
    variables[29] = orFunc(variables[0], orFunc(variables[1], variables[2]))
    variables[30] = orFunc(ltFunc(variables[0], variables[1]), gtFunc(variables[2], variables[3]))
    variables[31] = orFunc(variables[0]+variables[1], gtFunc(variables[2], variables[3]))
    variables[32] = orFunc(variables[0], gtFunc(variables[1], variables[2]))
    variables[33] = orFunc(variables[0]-variables[1], gtFunc(variables[2], variables[3]))
    variables[34] = orFunc(-variables[0], gtFunc(variables[1], variables[2]))
    variables[35] = orFunc(pow(variables[0], variables[1]), gtFunc(variables[2], variables[3]))
    variables[36] = orFunc(pow(variables[0], 1.0/variables[1]), gtFunc(variables[2], variables[3]))
    variables[37] = orFunc(ltFunc(variables[0], variables[1]), variables[2]+variables[3])
    variables[38] = orFunc(ltFunc(variables[0], variables[1]), variables[2])
    variables[39] = orFunc(ltFunc(variables[0], variables[1]), variables[2]-variables[3])
    variables[40] = orFunc(ltFunc(variables[0], variables[1]), -variables[2])
    variables[41] = orFunc(ltFunc(variables[0], variables[1]), pow(variables[2], variables[3]))
    variables[42] = orFunc(ltFunc(variables[0], variables[1]), pow(variables[2], 1.0/variables[3]))
    variables[43] = xorFunc(variables[0], variables[1])
    variables[44] = xorFunc(variables[0], xorFunc(variables[1], variables[2]))
    variables[45] = xorFunc(ltFunc(variables[0], variables[1]), gtFunc(variables[2], variables[3]))
    variables[46] = xorFunc(variables[0]+variables[1], gtFunc(variables[2], variables[3]))
    variables[47] = xorFunc(variables[0], gtFunc(variables[1], variables[2]))
    variables[48] = xorFunc(variables[0]-variables[1], gtFunc(variables[2], variables[3]))
    variables[49] = xorFunc(-variables[0], gtFunc(variables[1], variables[2]))
    variables[50] = xorFunc(pow(variables[0], variables[1]), gtFunc(variables[2], variables[3]))
    variables[51] = xorFunc(pow(variables[0], 1.0/variables[1]), gtFunc(variables[2], variables[3]))
    variables[52] = xorFunc(ltFunc(variables[0], variables[1]), variables[2]+variables[3])
    variables[53] = xorFunc(ltFunc(variables[0], variables[1]), variables[2])
    variables[54] = xorFunc(ltFunc(variables[0], variables[1]), variables[2]-variables[3])
    variables[55] = xorFunc(ltFunc(variables[0], variables[1]), -variables[2])
    variables[56] = xorFunc(ltFunc(variables[0], variables[1]), pow(variables[2], variables[3]))
    variables[57] = xorFunc(ltFunc(variables[0], variables[1]), pow(variables[2], 1.0/variables[3]))
    variables[58] = notFunc(variables[0])
    variables[59] = variables[0]+variables[1]
    variables[60] = variables[0]+variables[1]+variables[2]
    variables[61] = ltFunc(variables[0], variables[1])+gtFunc(variables[2], variables[3])
    variables[62] = variables[0]
    variables[63] = variables[0]-variables[1]
    variables[64] = ltFunc(variables[0], variables[1])-gtFunc(variables[2], variables[3])
    variables[65] = ltFunc(variables[0], variables[1])-(variables[2]+variables[3])
    variables[66] = ltFunc(variables[0], variables[1])-variables[2]
    variables[67] = -variables[0]
    variables[68] = -ltFunc(variables[0], variables[1])
    variables[69] = variables[0]*variables[1]
    variables[70] = variables[0]*variables[1]*variables[2]
    variables[71] = ltFunc(variables[0], variables[1])*gtFunc(variables[2], variables[3])
    variables[72] = (variables[0]+variables[1])*gtFunc(variables[2], variables[3])
    variables[73] = variables[0]*gtFunc(variables[1], variables[2])
    variables[74] = (variables[0]-variables[1])*gtFunc(variables[2], variables[3])
    variables[75] = -variables[0]*gtFunc(variables[1], variables[2])
    variables[76] = ltFunc(variables[0], variables[1])*(variables[2]+variables[3])
    variables[77] = ltFunc(variables[0], variables[1])*variables[2]
    variables[78] = ltFunc(variables[0], variables[1])*(variables[2]-variables[3])
    variables[79] = ltFunc(variables[0], variables[1])*-variables[2]
    variables[80] = variables[0]/variables[1]
    variables[81] = ltFunc(variables[0], variables[1])/gtFunc(variables[3], variables[2])
    variables[82] = (variables[0]+variables[1])/gtFunc(variables[3], variables[2])
    variables[83] = variables[0]/gtFunc(variables[2], variables[1])
    variables[84] = (variables[0]-variables[1])/gtFunc(variables[3], variables[2])
    variables[85] = -variables[0]/gtFunc(variables[2], variables[1])
    variables[86] = ltFunc(variables[0], variables[1])/(variables[2]+variables[3])
    variables[87] = ltFunc(variables[0], variables[1])/variables[2]
    variables[88] = ltFunc(variables[0], variables[1])/(variables[2]-variables[3])
    variables[89] = ltFunc(variables[0], variables[1])/-variables[2]
    variables[90] = ltFunc(variables[0], variables[1])/(variables[2]*variables[3])
    variables[91] = ltFunc(variables[0], variables[1])/(variables[2]/variables[3])
    variables[92] = sqrt(variables[0])
    variables[93] = pow(variables[0], 2.0)
    variables[94] = pow(variables[0], 3.0)
    variables[95] = pow(variables[0], variables[1])
    variables[96] = pow(ltFunc(variables[0], variables[1]), gtFunc(variables[2], variables[3]))
    variables[97] = pow(variables[0]+variables[1], gtFunc(variables[2], variables[3]))
    variables[98] = pow(variables[0], gtFunc(variables[1], variables[2]))
    variables[99] = pow(variables[0]-variables[1], gtFunc(variables[2], variables[3]))
    variables[100] = pow(-variables[0], gtFunc(variables[1], variables[2]))
    variables[101] = pow(variables[0]*variables[1], gtFunc(variables[2], variables[3]))
    variables[102] = pow(variables[0]/variables[1], gtFunc(variables[2], variables[3]))
    variables[103] = pow(ltFunc(variables[0], variables[1]), variables[2]+variables[3])
    variables[104] = pow(ltFunc(variables[0], variables[1]), variables[2])
    variables[105] = pow(ltFunc(variables[0], variables[1]), variables[2]-variables[3])
    variables[106] = pow(ltFunc(variables[0], variables[1]), -variables[2])
    variables[107] = pow(ltFunc(variables[0], variables[1]), variables[2]*variables[3])
    variables[108] = pow(ltFunc(variables[0], variables[1]), variables[2]/variables[3])
    variables[109] = pow(ltFunc(variables[0], variables[1]), pow(variables[2], variables[3]))
    variables[110] = pow(ltFunc(variables[0], variables[1]), pow(variables[2], 1.0/variables[3]))
    variables[111] = sqrt(variables[0])
    variables[112] = sqrt(variables[0])
    variables[113] = pow(variables[0], 1.0/3.0)
    variables[114] = pow(variables[0], 1.0/variables[1])
    variables[115] = pow(ltFunc(variables[0], variables[1]), 1.0/gtFunc(variables[3], variables[2]))
    variables[116] = pow(variables[0]+variables[1], 1.0/gtFunc(variables[3], variables[2]))
    variables[117] = pow(variables[0], 1.0/gtFunc(variables[2], variables[1]))
    variables[118] = pow(variables[0]-variables[1], 1.0/gtFunc(variables[3], variables[2]))
    variables[119] = pow(-variables[0], 1.0/gtFunc(variables[2], variables[1]))
    variables[120] = pow(variables[0]*variables[1], 1.0/gtFunc(variables[3], variables[2]))
    variables[121] = pow(variables[0]/variables[1], 1.0/gtFunc(variables[3], variables[2]))
    variables[122] = pow(ltFunc(variables[0], variables[1]), 1.0/(variables[2]+variables[3]))
    variables[123] = pow(ltFunc(variables[0], variables[1]), 1.0/variables[2])
    variables[124] = pow(ltFunc(variables[0], variables[1]), 1.0/(variables[2]-variables[3]))
    variables[125] = pow(ltFunc(variables[0], variables[1]), 1.0/-variables[2])
    variables[126] = pow(ltFunc(variables[0], variables[1]), 1.0/(variables[2]*variables[3]))
    variables[127] = pow(ltFunc(variables[0], variables[1]), 1.0/(variables[2]/variables[3]))
    variables[128] = pow(ltFunc(variables[0], variables[1]), 1.0/pow(variables[2], variables[3]))
    variables[129] = pow(ltFunc(variables[0], variables[1]), 1.0/pow(variables[2], 1.0/variables[3]))
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
    variables[164] = atanh(variables[0]/2.0)
    variables[165] = asech(variables[0])
    variables[166] = acsch(variables[0])
    variables[167] = acoth(2.0*variables[0])
    variables[168] = variables[0] if (gtFunc(variables[0], variables[1])) else nan
    variables[169] = variables[0] if (gtFunc(variables[0], variables[1])) else variables[2]
    variables[170] = variables[0] if (gtFunc(variables[0], variables[1])) else variables[2] if (gtFunc(variables[2], variables[3])) else variables[4] if (gtFunc(variables[4], variables[5])) else nan
    variables[171] = variables[0] if (gtFunc(variables[0], variables[1])) else variables[2] if (gtFunc(variables[2], variables[3])) else variables[4] if (gtFunc(variables[4], variables[5])) else variables[6]
    variables[176] = variables[0]

def computeRates(voi, states, rates, variables):
    rates[0] = 1.0

def computeVariables(voi, states, rates, variables):
    pass

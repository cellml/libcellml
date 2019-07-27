#include <math.h>

void initializeConstants(double *states, double *variables)
{
    states[0] = 1.0;
    variables[0] = 1.0;
}

void computeComputedConstants(double *variables)
{
}

void computeRates(double voi, double *states, double *rates, double *variables)
{
    rates[0] = variables[0];
}

void computeVariables(double voi, double *states, double *rates, double *variables)
{
    variables[1] = 2.0*states[0];
}

void computeStateRateBasedVariables(double voi, double *states, double *rates, double *variables)
{
    variables[1] = 2.0*states[0];
}

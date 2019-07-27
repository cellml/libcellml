#include <math.h>

void initializeConstants(double *states, double *variables)
{
    states[0] = 1.0;
    states[1] = 1.0;
    variables[0] = 1.0;
}

void computeComputedConstants(double *variables)
{
}

void computeRates(double voi, double *states, double *rates, double *variables)
{
    rates[0] = 1.0;
    rates[1] = variables[0];
}

void computeVariables(double voi, double *states, double *rates, double *variables)
{
}

void computeStateRateBasedVariables(double voi, double *states, double *rates, double *variables)
{
}

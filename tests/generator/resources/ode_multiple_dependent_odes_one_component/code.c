#include <math.h>

void initializeModel(double *states, double *variables)
{
    states[0] = -2.0;
    states[1] = 0.0;
    variables[0] = 1.0;
}

void computeConstantEquations(double *variables)
{
}

void computeRateEquations(double voi, double *states, double *rates, double *variables)
{
    rates[0] = states[1]*1.0;
    rates[1] = (variables[0]*(1.0-pow(states[0], 2.0))*states[1]-states[0])*1.0;
}

void computeAlgebraicEquations(double voi, double *states, double *rates, double *variables)
{
}

void computeStateOrRateBasedAlgebraicEquations(double voi, double *states, double *rates, double *variables)
{
}

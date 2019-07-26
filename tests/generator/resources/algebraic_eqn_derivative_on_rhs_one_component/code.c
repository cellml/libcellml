#include <math.h>

void initializeModel(double *states, double *variables)
{
    states[0] = 1.0;
    variables[0] = 1.0;
}

void computeConstantEquations(double *variables)
{
}

void computeRateEquations(double voi, double *states, double *rates, double *variables)
{
    rates[0] = variables[0];
}

void computeAlgebraicEquations(double voi, double *states, double *rates, double *variables)
{
    variables[1] = rates[0];
}

void computeStateOrRateBasedAlgebraicEquations(double voi, double *states, double *rates, double *variables)
{
    variables[1] = rates[0];
}

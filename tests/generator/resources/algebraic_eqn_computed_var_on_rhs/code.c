#include <math.h>

void initializeModel(double *states, double *variables)
{
    variables[0] = 1.0;
}

void computeConstantEquations(double *variables)
{
    variables[1] = variables[0];
}

void computeRateEquations(double voi, double *states, double *rates, double *variables)
{
}

void computeAlgebraicEquations(double voi, double *states, double *rates, double *variables)
{
}

void computeStateOrRateBasedAlgebraicEquations(double voi, double *states, double *rates, double *variables)
{
}

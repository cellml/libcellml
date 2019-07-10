#include <math.h>

void initializeModel(double *states, double *variables)
{
    variables[0] = 1.0;
}

void computeAlgebraicEquations(double voi, double *states, double *rates, double *variables)
{
    variables[1] = variables[0];
}

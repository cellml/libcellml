void initializeModel(double *states, double *variables)
{
    states[0] = 0.0;
    states[1] = 1.0;
}

void computeRateEquations(double *states, double *rates, double *variables)
{
    rates[0] = -states[1]*1.0;
    rates[1] = states[0]*1.0;
}

void computeAlgebraicEquations(double *states, double *rates, double *variables)
{
    variables[0] = states[1]+5.0*states[1]/3.0+1.0*exp(states[1]/2.0);
    variables[1] = 2.0*states[0];
}

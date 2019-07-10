void initializeModel(double *states, double *variables)
{
    states[0] = 0.0;
}

void computeRateEquations(double voi, double *states, double *rates, double *variables)
{
    rates[0] = 1.0;
}

void computeAlgebraicEquations(double *states, double *rates, double *variables)
{
    variables[0] = 2.0*voi;
    variables[1] = 3.0*variables[0];
}

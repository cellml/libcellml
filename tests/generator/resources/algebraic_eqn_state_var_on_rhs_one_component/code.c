void initializeModel(double *states, double *variables)
{
    states[0] = 1.0;

    variables[0] = 1.0;
}

void computeRateEquations(double *states, double *rates, double *variables)
{
    rates[0] = variables[0];
}

void computeAlgebraicEquations(double *states, double *rates, double *variables)
{
    variables[1] = 2.0*states[0];
}

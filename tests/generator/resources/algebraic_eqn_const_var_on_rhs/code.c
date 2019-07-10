void initializeModel(double *states, double *variables)
{
    variables[0] = 1.0;
}

void computeConstantEquations(double *variables)
{
    variables[1] = variables[0];
}

/* The content of this file was generated using the C profile of libCellML 0.2.0. */

#include <math.h>
#include <stddef.h>
#include <stdlib.h>

const char LIBCELLML_VERSION[] = "0.2.0";

const size_t STATE_COUNT = 1;
const size_t VARIABLE_COUNT = 2;

struct VariableInfo {
    char name[3];
    char units[14];
    char component[17];
};

const struct VariableInfo VOI_INFO = {"t", "second", "my_ode"};

const struct VariableInfo STATE_INFO[] = {
    {"x", "dimensionless", "my_ode"}
};

const struct VariableInfo VARIABLE_INFO[] = {
    {"a", "per_s", "my_ode"},
    {"xx", "dimensionless", "my_algebraic_eqn"}
};

double * createStatesArray()
{
    return (double *) malloc(1 * sizeof(double));
}

double * createVariablesArray()
{
    return (double *) malloc(2 * sizeof(double));
}

void deleteArray(double *array)
{
    free(array);
}

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

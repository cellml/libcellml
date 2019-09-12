/* The content of this file was generated using the C profile of libCellML 0.2.0. */

#include <math.h>
#include <stddef.h>
#include <stdlib.h>

const char LIBCELLML_VERSION[] = "0.2.0";

const size_t STATE_COUNT = 0;
const size_t VARIABLE_COUNT = 2;

struct VariableInfo {
    char name[2];
    char units[14];
    char component[17];
};

const struct VariableInfo VOI_INFO = {"", "", ""};

const struct VariableInfo STATE_INFO[] = {
};

const struct VariableInfo VARIABLE_INFO[] = {
    {"a", "dimensionless", "my_algebraic_eqn"},
    {"x", "dimensionless", "my_algebraic_eqn"}
};

double * createStatesArray()
{
    return (double *) malloc(0 * sizeof(double));
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
    variables[0] = 1.0;
}

void computeComputedConstants(double *variables)
{
    variables[1] = variables[0];
}

void computeRates(double voi, double *states, double *rates, double *variables)
{
}

void computeVariables(double voi, double *states, double *rates, double *variables)
{
}
